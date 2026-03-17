/* LP 16-3-26 */

#include "variable.h"

Variable variable=NULL;
static int variables=0;

static int comnom(Value vnom,char* nom) {
    if(nom) {
        char* pv=vnom;
        char* pn=nom;
        while(*pn!=EOS) {
            if(*pn!=*pv) return 0;
            pn++;
            pv++;
        }
        return (*pv==EOS);
    }
    return 0;
}

static struct variable_s* varfnd(Value nom) {
    /* busqueda de variable por nombre */
    struct variable_s* pv=variable;
    while(pv!=NULL) {
        if(comnom(pv->nom,nom)) break;
        pv=pv->nxt;
    }
    return pv;
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
    if(val) {
        struct variable_s* pv=varfnd(nom);
        if(pv) {
            if(comnom(val,pv->val)) {
                valdel(&pv->val);
                pv->val=val;
            }
            return 1;
        } else {
            Value vnom=varnom(nom);
            if(vnom) {
                struct variable_s* nsv=malloc(sizeof(struct variable_s));
                if(nsv) {
                    ++variables;
                    nsv->nom=vnom;
                    nsv->val=val;
                    nsv->nxt=variable;
                    variable=nsv;
                    return 1;
                } else {
                    valdel(&vnom);
                }
            }
        }
    }
    return 0;
}

Value varget(char* nom) {
    Value ret=NULL;
    struct variable_s* ps=varfnd(nom);
    if(ps) ret=valcpy(ps->val);
    return ret;
}

size_t varsiz() {
    struct variable_s* pv=variable;
    size_t counter=0;
    while(pv!=NULL) {
        ++counter;
        pv=pv->nxt;
    }
    return counter;
}

void vardel() {
    struct variable_s* ps=variable;
    while(ps!=NULL) {
        struct variable_s* tdel=ps;
        ps=tdel->nxt;
        printf("%p (%s %s)\n",tdel,tdel->nom,tdel->val);//dbg
        valdel(&(tdel->nom));
        valdel(&(tdel->val));
        free(tdel);
        --variables;
    }
}

int varerr() {
    return variables;
}


