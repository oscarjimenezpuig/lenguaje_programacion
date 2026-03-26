/* LP 18-3-26 */

#include "program.h"

/* insercion de programa */

Program program=NULL;

static int tokens=0;

#define PRCI 1
#define LINI 2
#define MANI 4

static struct token_s* lastprg() {
    if(program) {
        struct token_s* pp=program;
        while(pp->nxt) pp=pp->nxt;
        return pp;
    }
    return NULL;
}

int toknew(Flag typ,...) {
    static Flag ini=0;
    if(!(ini & MANI) && !(typ & SMAN)) return -1; /* inicio de programa no realizado */
    else if((typ & SMAN)) {
        typ|=(SPRC|SLIN);
        ini|=(MANI|PRCI);
        return 0;
    }
    if((typ & SPRC) && (ini & PRCI)) return -2; /* procedimiento ya iniciado */
    else if((typ & SPRC)) {
        ini|=PRCI;
        typ|=(SPRC|SLIN);
    }
    if((typ & SLIN) && (ini & LINI)) return -3; /* linea ya iniciada */
    if((typ & EMAN) && !(ini & MANI)) return -4; /* programa no iniciado */
    else if(typ & EMAN) {
        typ|=(EPRC|ELIN);
        ini&=~(MANI|PRCI|LINI);
    }
    if((typ & EPRC) && !(ini & PRCI)) return -6; /* procedimiento no iniciado */
    else if(typ & EPRC) {
        typ|=ELIN;
        ini&=~(PRCI|LINI);
   }
    if((typ & ELIN) && !(ini & LINI)) return -5; /* linea no iniciada */
    else if(typ & ELIN) ini&=~LINI;
    struct token_s* tok=malloc(sizeof(struct token_s));
    if(tok) {
        ++tokens;
        tok->typ=typ;
        va_list list;
        va_start(list,typ);
        if((typ & (SPRC|TVAL))) {
            tok->val=va_arg(list,Value);
        } else if ((typ & TINS)) {
            tok->ins=va_arg(list,int);
        }
        va_end(list);
        struct token_s* ant=lastprg();
        if(ant) ant->nxt=tok;
        else program=tok;
        return 0;
   } else return -1000; /* error de memoria */
}

static void tokprt(struct token_s* tok) {
    if(tok) {
        Flag typ=tok->typ;
        if(typ & SMAN) printf("Program\n");
        else if(typ & EMAN) printf("End program\n");
        else if(typ & SPRC) printf("   Procedure: %s\n",tok->val);
        else if (typ & EPRC) printf("   End procedure");
        else if(typ & SLIN) printf("     ");
        if(typ & TINS) printf("I(%i) ",tok->ins);
        else if(typ & TVAL) printf("V(%s) ",tok->val);
        if(typ & ELIN) printf("\n");
    }
}

void prgprt() {
    struct token_s* pt=program;
    while(pt) {
        tokprt(pt);
        pt=pt->nxt;
    }
}

struct token_s* prcfnd(Value nom) {
    struct token_s* pt=program;
    while(pt) {
        if((pt->typ & SPRC) && (valequ(pt->val,nom))) return pt;
        pt=pt->nxt;
    }
    return NULL;
}

struct token_s* linnxt(struct token_s* tok) {
    struct token_s* pt=tok;
    if(pt && pt->nxt) {
        while(pt && (pt->typ & SLIN)==0) {
            pt=pt->nxt;
        }
        return pt;
    }
    return NULL;
}

static void tokdel(struct token_s* tok) {
    if(tok) {
        tokdel(tok->nxt);
        free(tok);
        --tokens;
    }
}

void prgdel() {
    tokdel(program);
}

int prgerr() {
    return tokens;
}
  
/* ejecucion del programa */

static int procedures=0;

Execute execute=NULL; /* pila de ejecucion */

static int jmp(Stack* sval,struct token_s** lin) {
    /* orden jmp a la linea dicha */
    Value nlab=vspop(sval);
    *lin=NULL;
    if(nlab) {
        struct token_s* ptok=execute->ini;
        int find=0;
        while(ptok && !find) {
            if((ptok->typ & TINS) && ptok->ins==LAB) {
                struct token_s* ntok=ptok->nxt;
                if((ntok->typ & TVAL) && (valequ(ntok->val,nlab))) {
                    find=1;
                    *lin=ptok;
                }
            }
        }
        if(find) {
            execute->nnl=1;
            return 0;
        } else return -11;
    } else return -8;
}

static int lab(Stack* sval) {
    /* orden label (no hace nada) */
    vspop(sval);
    return 0;
}

static int ifs(Stack* sval,struct token_s** lin) {
    /* condicion if si se cumple, sigue a la linea siguiente */
    Value val=vspop(sval);
    if(val) {
        if(valisfalse(val)) {
            struct token_s* ptok=*lin;
            int nifs=0;
            do {
                if((ptok->typ & TINS)) {
                    if(ptok->ins==IF) ++nifs;
                    else if(ptok->ins==FI)--nifs;
                }
                ptok=ptok->nxt;
            }while(ptok && nifs>0);
            if(nifs==0) {
                *lin=ptok;
                execute->nnl=1;
                return 0;
            }
            else return -12; 
        } else return 0;
    } else return -8;
}

static int ife(Stack* sval) {
    /* clausula final del condicional (no hace nada) */
    return 0;
}

static int call(Stack* sval) {
    /* llamada a un nuevo procedimiento */
    Value npn=vspop(sval);
    if(npn) return prccll(npn);
    else return -8;
}   

#define sval (&(execute->val))
#define lvar (&(execute->var))

static int linexe(struct token_s** lin) {
    /* almacenamiento y ejecucion de una pila */
    int err=0;
    if(*lin) {
        if(((*lin)->typ & (SPRC|SMAN))==0) {
            struct token_s* tok=*lin;
            while(tok && (tok->typ & (ELIN|EMAN|EPRC))==0) {
                if((tok->typ & TVAL)) {
                    vspush(&(execute->val),valcpy(tok->val));
                } else if((tok->typ & TINS)) {
                    ispush(&(execute->ins),tok->ins);
                }
                tok=tok->nxt;
            }
        }
        Instruction i=NOI;
        while(err==0 && (i=ispop(&(execute->ins)))!=NOI) {
            switch(i) {
                case(ADD):
                    err=binary(sval,'+');
                    break;
                case(OP):
                    err=unary(sval,'-');
                    break;
                case(PRD):
                    err=binary(sval,'*');
                    break;
                case(INV):
                    err=unary(sval,'/');
                    break;
                case(EQU):
                    err=comp(sval,'=');
                    break;
                case(GRT):
                    err=comp(sval,'>');
                    break;
                case(OUT):
                    err=out(sval);
                    break;
                case(IN):
                    err=in(sval);
                    break;
                case(NLN):
                    err=nln();
                    break;
                case(TAB):
                    err=tab();
                    break;
                case(LET):
                    err=let(lvar,sval);
                    break;
                case(SET):
                    err=set(lvar,sval);
                    break;
                case(GET):
                    err=get(lvar,sval);
                    break;
                case(ARL):
                    err=arl(lvar,sval);
                    break;
                case(ARS):
                    err=ars(lvar,sval);
                    break;
                case(ARG):
                    err=arg(lvar,sval);
                    break;
                case(JMP):
                    err=jmp(sval,lin);
                    break;
                case(LAB):
                    err=lab(sval);
                    break;
                case(IF):
                    err=ifs(sval,lin);
                    break;
                case(FI):
                    err=ife(sval);
                    break;
                case(CLL):
                    err=call(sval);
                    break;
            }
        }           
    }
    return err;
}

#undef sval
#undef lvar

static int prcexe() {
    /* ejecucion del ultimo procedimiento de la pila */
    int err=0;
    if(execute) {
        struct token_s* pl=execute->lin;
        while(pl && err==0) {
            err=linexe(&pl);
            if(!execute->nnl) pl=linnxt(pl);
            else execute->nnl=0;
        }
    }
    return err;
}           

static int prcnew(struct token_s* tok) {
    /* se crea un nuevo procedimiento */
    if(tok) {
        struct procedure_s* prc=malloc(sizeof(struct procedure_s));
        if(prc) {
            ++procedures;
            prc->ini=prc->lin=tok;
            prc->var=NULL;
            prc->nnl=0;
            prc->prv=execute;
            execute=prc;
            return 0;
        } else return -1000;
    } else return -7; /* procedimiento no encontrado */
}

static int prcdel() {
    /* borrado del ultimo procedimiento de la pila */
    if(execute) {
        --procedures;
        struct procedure_s* tdel=execute;
        execute=execute->prv;
        varsdel(&(tdel->var));
        vsdel(&(tdel->val));
        isdel(&(tdel->ins));
        free(tdel);
        return 1;
    }
    return 0;
}
    
int prccll(Value nom) {
    int err=0;
    if((err=prcnew(prcfnd(nom)))==0) {
        err=prcexe();
        prcdel();
    }
    return err;
}

int prgexe() {
    int err=0;
    if((err=prcnew(program))==0) {
        err=prcexe();
        prcdel();
    }
    return err;
}

int exeerr() {
    return procedures;
}
