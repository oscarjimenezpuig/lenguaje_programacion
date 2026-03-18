/* LP 16-3-26 */

#include "variable.h"

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

static struct variable_s* varfnd(Variable* var,Value nom) {
    /* busqueda de variable por nombre */
    struct variable_s* pv=*var;
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

Variable varnew() {
    return NULL;
}

int varset(Variable* var,char* nom,Value val) {
    if(val) {
        struct variable_s* pv=varfnd(var,nom);
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
                    nsv->nxt=*var;
                    *var=nsv;
                    return 1;
                } else {
                    valdel(&vnom);
                }
            }
        }
    }
    return 0;
}

Value varget(Variable* var,char* nom) {
    Value ret=NULL;
    struct variable_s* ps=varfnd(var,nom);
    if(ps) ret=valcpy(ps->val);
    return ret;
}

size_t varsiz(Variable var) {
    struct variable_s* pv=var;
    size_t counter=0;
    while(pv!=NULL) {
        ++counter;
        pv=pv->nxt;
    }
    return counter;
}

void vardel(Variable* var) {
    struct variable_s* ps=*var;
    while(ps!=NULL) {
        struct variable_s* tdel=ps;
        ps=tdel->nxt;
        printf("%p (%s %s)\n",tdel,tdel->nom,tdel->val);//dbg
        valdel(&(tdel->nom));
        valdel(&(tdel->val));
        free(tdel);
        --variables;
    }
    *var=NULL;
}

int varerr() {
    return variables;
}


