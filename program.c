/* LP 18-3-26 */

#include "program.h"

Program program={NULL,NULL};

static struct procedure_s* pactual=NULL;
static struct line_s* lactual=NULL;


#define ALOC(A) malloc(sizeof(A))

int prgprczernew() {
    if(pactual==NULL) {
        struct procedure_s* np=ALOC(struct procedure_s);
        if(np) {
            np->lin=NULL;
            np->nxt=NULL;
            program.zer=np;
            pactual=np;
            return 1;
        }
    }
    return 0;
}

int prgprczerend() {
    if(pactual!=NULL && pactual==program.zer) {
        pactual=NULL;
        return 1;
    }
    return 0;
}

int prgprcnew(Value nom) {
    if(pactual!=NULL && pactual==program.zer) {
        struct procedure_s* np=ALOC(struct procedure_s);
        if(np) {
            np->nom=nom;
            np->lin=NULL;
            np->nxt=program.prc;
            program.prc=np;
            pactual=np;
            return 1;
        }
    }
    return 0;
}

int prgprcend() {
    if(pactual!=program.zer) {
        pactual=program.zer;
        return 1;
    }
    return 0;
}

int prglinnew() {
    if(lactual==NULL && pactual) {
        struct line_s* ln=ALOC(struct line_s);
        if(ln) {
            ln->tok=NULL;
            ln->nxt=NULL;
            if(pactual->lin) {
                struct line_s* pl=pactual->lin;
                while(pl->nxt) pl=pl->nxt;
                pl->nxt=ln;
            } else {
                pactual->lin=ln;
            }
            return 1;
        }
    }
    return 0;
}

int prglinend() {
    if(lactual) {
        lactual=NULL;
        return 1;
    }
    return 0;
}

int prgtoknew(type_e t,...) {
    if(lactual) {
        struct token_s* tn=ALOC(struct token_s);
        if(tn) {
            tn->typ=t;
            tn->nxt=NULL;
            va_list list;
            va_start(list,t);
            if(t==TINS) tn->ins=va_arg(list,int);
            else tn->val=va_arg(list,Value);
            va_end(list);
            if(lactual->tok) {
                struct token_s* pt=lactual->tok;
                while(pt->nxt) pt=pt->nxt;
                pt->nxt=tn;
            } else lactual->tok=tn;
            return 1;
        }
    }
    return 0;
}

static void tokprt(struct token_s t) {
    if(t.typ==TINS) {
        printf("I(%i) ",t.ins);
    } else {
        printf("V(");
        valprt(t.val);
        printf(") ");
    }
}

static void linprt(struct line_s l) {
    struct token_s* t=l.tok;
    while(t) {
        tokprt(*t);
        t=t->nxt;    
    }
    printf("\n");
}

static void prcprt(struct procedure_s p) {
    printf("Procedure: %s\n",p.nom);
    struct line_s* l=p.lin;
    while(l) {
        linprt(*l);
        l=l->nxt;
    }
    printf("End: %s\n",p.nom);
}

void prgprt() {
    struct procedure_s* p=program.prc;
    while(p) {
        prcprt(*p);
        p=p->nxt;
    }
} 

static void tokdel(struct token_s* tok) {
    if(tok) {
        tokdel(tok->nxt);
        if(tok->typ==TVAL) {
            valdel(&(tok->val));
        }
        free(tok);
    }
}

static void lindel(struct line_s* lin) {
    if(lin) {
        lindel(lin->nxt);
        tokdel(lin->tok);
        free(lin);
    }
}

static void prcdel(struct procedure_s* prc) {
    if(prc) {
        prcdel(prc->nxt);
        lindel(prc->lin);
        valdel(&(prc->nom));
        free(prc);
    }
}

void prgdel() {
    prcdel(program.prc);
    program=(Program){NULL,NULL};
}

/* EJECUCION DEL PROGRAMA */

struct prcexe_s {
    struct procedure_s* prc; /* procedimiento que se ejecuta */
    struct line_s* lin; /* linea que se ejecuta del procedimiento */
    Variable var;
    Stack sval;
    Stack sins;
    struct prcexe_s* prv;
};

struct prgexe_s {
    Variable var;
    struct prcexe_s* zex;
    struct prcexe_s* pex;
};

static struct pgrgexe_s prgexe={NULL,NULL};

static int prcexenew(struct procedure_s* prc) {
    if(prc) {
        struct prcexe_s* pen=ALOC(struct prcexe_s);
        if(pen) {
            pen->prc=prc;
            pen->lin=prc->lin;
            pen->var=NULL;
            pen->sval=pen->sins=NULL;
            if(program->zer==prc) {
                zer=pen;
            } else {
                pen->prv=prgexe->pex;
                prgexe->pex=pen;
            }
            return 1;
        }
    }
    return 0;
}

static void prcexedel(struct prcexe_s* pex) {
    /* se libera un procedimiento, el ultimo de la cola y el penultimo es el que se ejecuta */
    if(pex) {
        varsdel(&pex->var);
        stkdel(&pex->sval);
        stkdel(&pex->sins);
        prgexe->pex=pex->prv;
        free(pex);
    }
}

#define SVAL (&(pex->sval))

static int linexe(struct prcexe_s* pex) {
    /* ejecucion de una linea, introduciendo todos los valores que encontramos en las pilas */
    /* introduccion de valores e instrucciones en los Stack */
    struct token_s* tok=lin->tok;
    while(tok) {
        if(tok->typ==TINS) ispush(&pex->sins,tok->ins);
        else vspush(&pex->sval,tok->val);
        tok=tok->nxt;
    }
    /* lectura de las instrucciones almacenadas en el stack */
    Instruction ins=NUI;
    int nerr=1;
    while(nerr && (ins=ispop(&(pex->sins)))) {
        switch(ins) {
            case ADD:
                nerr=add(SVAL);
                break;
            case OP:
                nerr=op(SVAL);
                break;
            case PRD:
                nerr=prd(SVAL);
                break;
            case INV:
                nerr=inv(SVAL);
                break;
            case EQU:
                nerr=equ(SVAL);
                break;
            case GRT:
                nerr=equ(SVAL);
                break;
            case LET:
                nerr=
                
        
       
            



int prgexe() {
}


/* prueba */

static int end() {
    vsdel();
    isdel();
    return valerr()+varerr()+stkerr();
}

int main() {
    Value a=valnew(1,22.34);
    Variable v=varsnew();
    varnew(&v,"radio",1);
    varnew(&v,"potencia",3);
    varset(&v,"potencia",2,a);
    varsprt(v);
    varsdel(&v);
    return end();
}



