/* LP 18-3-26 */

#include "program.h"

/* program set */

struct token_s {
    struct {
        char isi : 1; /* dice que el token es del tipo instruccion */
        char isv : 1; /* dice que el token es del tipo valor */
        char eol : 1; /* el token indica un salto de linea */
    };  
    union {
        Instruction ins; /* instuccion almacenada */
        Value val; /* valor almacenado */
    };
    struct token_s* nxt;
};

typedef struct token_s* Token;

typedef struct {
    Token frt;
    Token lst;
} Program;

static Program program={NULL,NULL};

static int tokens=0;

static Token toknew() {
    Token nt=malloc(sizeof(struct token_s));
    if(nt) {
        nt->isi=nt->eol=nt->isv=0;
        nt->nxt=NULL;
        ++tokens;
    }
    return nt;
}

static void tokset(Token tok) {
    if(!program.frt) {
        program.frt=program.lst=tok;
    } else {
        program.lst->nxt=tok;
        program.lst=tok;
    }
}

int tokins(Instruction i) {
    Token nt=toknew();
    if(nt) {
        nt->isi=1;
        nt->ins=i;
        tokset(nt);
        return 0;
    }
    return -1000;
}

int tokval(char* str) {
    Token nt=toknew();
    if(nt) {
        nt->val=valnew(0,str);
        nt->isv=1;
        tokset(nt);
        return 0;
    }
    return -1000;
}

int tokeol() {
    Token nt=toknew();
    if(nt) {
        nt->eol=1;
        tokset(nt);
        return 0;
    }
    return -1000;
}

static void tokdel(Token t) {
    if(t) {
        tokdel(t->nxt);
        if(t->isi==0) valdel(&(t->val));
        free(t);
        --tokens;
    }
}

void prgdel() {
    tokdel(program.frt);
    program.frt=program.lst=NULL;
}

int prgerr() {
    return tokens;
}

/* program exe */

struct prcexe_s{
    Token ini,act; /* token donde se inicia el procedimiento y donde esta actualmente */
    Variable var; /* almacen de variables */
    Stack sin,sva; /* pilas */
    struct prcexe_s* prv; /* apunta al procedimiento previo */
};

typedef struct prcexe_s* Prcexe;

Prcexe prcexe=NULL;
Prcexe prcmain=NULL;

static int prcexes=0;

static int prcnew(char ismain) {
    /* creacion de un nuevo procedimiento */
    Prcexe np=malloc(sizeof(struct prcexe_s));
    if(np) {
        np->ini=np->act=NULL;
        np->var=NULL;
        np->sin=np->sva=NULL;
        np->prv=prcexe;
        prcexe=np;
        if(ismain) prcmain=np;
        ++prcexes;
        return 0;
    }
    return -1000;
}

static void prcdel(Prcexe* p) {
    if(p && *p) {
        prcdel(&((*p)->prv));
        varsdel(&((*p)->var));
        vsdel(&((*p)->sva));
        isdel(&((*p)->sin));
        *p=NULL;
        --prcexes;
    }
}

static Token tokfnd(Instruction ins,Value val,Token ini) {
    /* desde el token del inicio busca la instruccion demandada con valor demandado */
    Token p=ini;
    char cont=1;
    while(cont) {
        if(p->isi) {
            if((ins==PRG && p->ins==PRG)) return p;
            else if(ins==p->ins) {
                p=p->nxt;
                if(p->isv && valequ(p->val,val)) return p;
            } else if(p->ins==GRP || p->ins==CRP) cont=0;
        }
        p=p->nxt;
    }
    return NULL;
}

static Token nxtlin(Token ini) {
    /* busca la siguiente linea a partir del inicio */
    Token p=ini;
    while(p && p->eol==0) p=p->nxt;
    return p->nxt;
}

static void linfill(Prcexe prc,Token ini) {
    /* se llena el stack de todo lo que hay en la linea */
    Token p=ini;
    if(p) {
        do {
            if(p->isi) ispush(&(prc->sin),p->ins);
            else if(p->val) vspush(&(prc->sva),valcpy(p->val));
        }while(p->eol==0);
    }
}

static int calcord(Stack* sval,Instruction i) {
    /* instrucciones relativas al calculo */
    char op=0;
    switch(i) {
        case ADD:
           op='+';
           break;
        case OP:
           op='-';
           break;
        case PRD:
           op='*';
           break;
        case INV:
           op='/';
           break;
        case EQU:
           op='=';
           break;
        case GRT:
           op='>';
           break;
    }
    switch(i) {
        case ADD:
        case PRD:
            return binary(sval,op);
        case OP:
        case INV:
            return unary(sval,op);
        case EQU:
        case GRT:
            return comp(sval,op);
        default:
            return 0;
            
    }
}

static int varord(Variable* var,Stack* sval,Instruction i) {
    /* instrucciones relativas a las variables */
    Variable* vma=&(prcmain->var);
    switch(i) {
        case LET:
            return let(var,sval);
        case SET:
            return set(var,vma,sval);
        case GET:
            return get(var,vma,sval);
        case ARL:
            return arl(var,sval);
        case ARS:
            return ars(var,vma,sval);
        case ARG:
            return arg(var,vma,sval);
        default:
            return 0;
    }
}

static int inoutord(Stack* sval,Instruction i) {
    /* instrucciones relativas a la entrada y la salida */
    switch(i) {
        case IN:
            return in(sval);
        case OUT:
            return out(sval);
        case NLN:
            return nln();
        default:
            return 0;
    }
}

static int prcord(Stack* sval,Instruction i) {
    /* gestion de la rutina CALL y la destruccion de procedimientos */
    /* cuando llamamos con la instruccion NOI se crea la nueva rutina */
    /* cuando se llega al end se destruye el procedimiento */
    /* procemiento main destruido quiere decir que el programa se para */
    int err=0;
    if(i==NOI) {
        Token t=tokfnd(PRG,"",program.frt);
        if(t) {
            err=prcnew(1);
            if(!err) {
                prcexe->ini=prcexe->act=t;
            }
        } else err=-4;
    } else if(i==CLL) {
        Value val=vspop(sval);
        if(val) {
            Token t=tokfnd(PRC,val,program.frt);
            if(t) {
                err=prcnew(0);
                if(!err) {
                    prcexe->ini=prcexe->act=t;
                }
            } else err=-7;
        } else err=-8;
    } else if(i==GRP || i==CRP) {
        Prcexe tdel=prcexe;
        if(tdel) {
            prcexe=tdel->prv;
            tdel->prv=NULL;
            prcdel(&(tdel));
            if(i==GRP || !prcexe) prcmain=NULL;
        }
    }
    return err;
}

static int jmpord(Stack* sval) {
    /* orden jump */
    Value val=vspop(sval);
    if(val) {
        Token t=tokfnd(LAB,val,prcexe->ini);
        if(t) {
            prcexe->act=t;
            return 0;
        } else return -11;
    } else return -8;
}

static int condord(Stack* sval) {
    /* orden condicional */
    Value val=vspop(sval);
    if(val) {
        if(valisfalse(val)) {
            Token t=prcexe->act->nxt;
            int conds=1;
            while(t && (t->isi==0 || (t->ins!=CRP && t->ins!=GRP))) {
                if(t->isi) {
                    if(t->ins==IF) ++conds;
                    else if(t->ins==FI) {
                        --conds;
                        if(conds==0) {
                            prcexe->act=t->nxt;
                            return 0;
                        }
                    }
                }
                t=t->nxt;
            }
            return -12;
        } else {
            prcexe->act=prcexe->act->nxt;
            return 0;
        }
    } else return -8;
}

static int loopord(Stack* sval) {
    /* loop */

    







            


        



    










