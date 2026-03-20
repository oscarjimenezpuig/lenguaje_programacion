/* LP 18-3-26 */

#include "program.h"

Program program=NULL;

int prginslin() {
    struct line_s* nl=malloc(sizeof(struct line_s));
    if(nl) {
        nl->tok=NULL;
        nl->nxt=NULL;
        if(!program) program=nl;
        else {
            struct line_s* pl=program;
            while(pl->nxt) {
                pl=pl->nxt;
            }
            pl->nxt=nl;
        }
        return 1;
    }
    return 0;
}

int prginstok(type_e t,...) {
    if(program) {
        struct line_s* pl=program;
        while(pl->nxt) pl=pl->nxt;
        struct token_s* tn=malloc(sizeof(struct token_s));
        if(tn) {
            tn->typ=t;
            tn->nxt=NULL;
            va_list list;
            va_start(list,t);
            if(t==TINS) tn->ins=va_arg(list,int);
            else tn->val=va_arg(list,Value);
            va_end(list);
            if(pl->tok) {
                struct token_s* pt=pl->tok;
                while(pt->nxt) pt=pt->nxt;
                pt->nxt=tn;
            } else pl->tok=tn;
            return 1;
        }
    }
    return 0;
}

static void linprt(struct line_s* l) {
    struct token_s* pt=l->tok;
    while(pt) {
        if(pt->typ==TINS) printf("I:(%i) ",pt->ins);
        else {
            printf("V:(");
            valprt(pt->val);
            printf(") ");
        }
        pt=pt->nxt;
    }
    printf("\n");
}

static struct line_s* findmain() {
    /* buscamos la instruccion main */
    struct line_s* pl=program;
    while(pl) {
        struct token_s* pt=pl->tok;
        while(pt) {
            if(pt->typ==TINS && pt->ins==MAIN) return pl;
            pt=pt->nxt;
        }
        pl=pl->nxt;
    }
}

static void linestart(struct line_s* line) {
    /* inserta una linea en los stacks para ejecutarse */
    struct token_s* ps=pl->tok;
    while(ps) {
        if(ps->typ==TINS) ispush(ps->ins);
        else if(ps->typ==TVAL) vspush(valcpy(ps->val));
        ps=ps->nxt;
    }
}

int prgexe() {
    static struct line_s* actual=NULL;
    /* si no hay linea actual buscamos main */
    if(!actual) actual=findmain();
    while(actual) {
        linestart(actual);
        //TODO Continuar

        
    

void prgprt() {
    struct line_s* pl=program;
    while(pl) {
        linprt(pl);
        pl=pl->nxt;
    }
}

static void lindel(struct line_s* l) {
    struct token_s* pt=l->tok;
    while(pt) {
        struct token_s* tdel=pt;
        pt=pt->nxt;
        if(tdel->typ==TVAL) valdel(&tdel->val);
        free(tdel);
    }
}

void prgdel() {
    struct line_s* pl=program;
    while(pl) {
        struct line_s* tdel=pl;
        pl=pl->nxt;
        lindel(tdel);
        free(tdel);
    }
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



