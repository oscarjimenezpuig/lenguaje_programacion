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

Execute execute=NULL;

int prcnew() {
    //TODO Crear el nuevo procedimiento a ejecutar */
