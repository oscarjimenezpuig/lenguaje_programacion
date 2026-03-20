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

Variable varsnew() {
    return NULL;
}

size_t varssiz(Variable var) {
    struct variable_s* pv=var;
    size_t counter=0;
    while(pv!=NULL) {
        ++counter;
        pv=pv->nxt;
    }
    return counter;
}

void varsprt(Variable var) {
    struct variable_s* pv=var;
    while(pv) {
        if(pv->nom) printf(pv->nom);
        else printf("<-");
        if(pv->val) printf("=%s\n",pv->val);
        else printf("=NULLVAL\n");
        pv=pv->nxt;
    }
}

void varsdel(Variable* var) {
    struct variable_s* ps=*var;
    while(ps!=NULL) {
        struct variable_s* tdel=ps;
        ps=tdel->nxt;
        valdel(&(tdel->nom));
        valdel(&(tdel->val));
        free(tdel);
        --variables;
    }
    *var=NULL;
}

static int varnewone(Variable* var,Value nom) {
    struct variable_s* nsv=malloc(sizeof(struct variable_s));
    if(nsv) {
        if(nom) nsv->nom=nom;
        else nsv->nom=NULL;
        nsv->val=NULL;
        nsv->nxt=*var;
        *var=nsv;
        ++variables;
        return 1;
    }
    return 0;
}

int varnew(Variable* var,char* nom,unsigned int dim) {
    if(var && nom && dim) {
        struct variable_s* pv=varfnd(var,nom);
        if(!pv) {
            Value vnom=varnom(nom);
            if(vnom) {
                int nerr=1;
                for(int k=dim;k>1 && nerr;k--) nerr=varnewone(var,NULL);
                if(nerr) return varnewone(var,vnom);
            }
        }
    }
    return 0;
}

int varset(Variable* var,char* nom,unsigned int pos,Value val) {
    struct variable_s* pv=NULL;
    if(var && nom && val && (pv=varfnd(var,nom))) {
        int counter=0;
        while(counter++!=pos && pv) pv=pv->nxt;
        if(pv) {
            valdel(&pv->val);
            pv->val=val;
            return 1;
        }
    }
    return 0;
}

Value varget(Variable* var,char* nom,unsigned int pos) {
    Value ret=NULL;
    struct variable_s* pv=NULL;
    if(var && nom && pv) {
        int counter=0;
        while(counter++!=pos && pv) pv=pv->nxt;
        if(pv) ret=pv->val;
    }
    return ret;
}

int varerr() {
    return variables;
}


