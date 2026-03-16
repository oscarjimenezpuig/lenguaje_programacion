/* LP 16-3-26 */

#include "variable.h"

Variable variable=NULL;
static int variables=0;

static struct variable_s* varfnd(Value nom) {
    /* busqueda de variable por nombre */
    struct variable_s* pv=variable;
    while(pv!=NULL) {
        if(ulaequ(nom,pv->nom)) break;
        pv=pv->nxt;
    }
    return NULL;
}

static Value varnom(char* nom) {
    char* pn=nom;
    while(*pn!=EOS) {
        if(*pn<'a' || *pn>'z') return NULL;
        pn++;
    }
    return valnew(0,nom);
}

int varset(char* nom,Value val) {
    if(!nom || !val) return 0;
    Value vnom=varnom(nom);
    struct variable_s* pv=varfnd(vnom);
    if(pv) {
        if(!ulaequ(val,pv->val)) {
            valdel(&pv->val);
            pv->val=val;
        }
        valdel(&vnom);
    } else {
        struct variable_s* nsv=malloc(sizeof(struct variable_s));
        if(nsv) {
            ++variables;
            nsv->nom=vnom;
            nsv->val=val;
            nsv->nxt=variable;
            variable=nsv;
        } else return 0;
    }
    return 1;
}

Value varget(char* nom) {
    Value ret=NULL;
    Value vnom=valnew(0,nom);
    struct variable_s* ps=varfnd(vnom);
    if(ps) ret=ps->val;
    valdel(&vnom);
    return ret;
}

void vardel() {
    struct variable_s* ps=variable;
    while(ps!=NULL) {
        valdel(&(ps->nom));
        valdel(&(ps->val));
        struct variable_s* tdel=ps;
        ps=ps->nxt;
        free(tdel);
        --variables;
    }
}

int varerr() {
    return variables;
}

/* prueba */

static void prtval(Value a) {
    printf("%s\n",a);
}

int main() {
    Value a=valnew(1,22.0);
    if(varset("hola",a)) {
        Value b=varget("hola");
        prtval(b);
        valdel(&b);
    }
    vardel();
    return valerr()+1000*varerr();
}


