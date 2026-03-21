/* LP 18-3-26 */

#include "program.h"

Program program={NULL,NULL};

static struct procedure_s* pactual=NULL;
static struct line_s* lactual=NULL;

int prgprcmain(Value nom) {
    struct procedure_s* pp=program.prc;
    while(pp) {
        if(valequ(nom,pp->nom)) {
            program.frs=pp;
            return 1;
        }
        pp=pp->nxt;
    }
    return 0;
}

#define ALOC(A) malloc(sizeof(A))

int prgprcnew(Value nom) {
    if(pactual==NULL) {
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
    if(pactual) {
        pactual=NULL;
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



