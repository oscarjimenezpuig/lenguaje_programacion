/* LP 14-3-26 */

#include "ula.h"

static int valget(Stack* stk,Value* a,Value* b) {
    int err=0;
    if(a) {
        *a=vspop();
        err=(*a==NULL);
    }
    if(!err && b) {
        *b=vspop();
        err=(*b==NULL);
    }
    return (err==0);
}

static void valfree(Value* a,Value* b) {
    if(*a) valdel(a);
    if(*b) valdel(b);
}

static int valins(Stack* stk,double a) {
    return vspush(stk,valnew(1,a));
}

static int valbool(Stack* stk,int res) {
    Value nv=(res)?valnew(0,"1"):valnew(0,"0");
    return vspush(stk,nv);
}

#define gva valtonum(a)
#define gvb valtonum(b)

int ulaadd(Stack* stk) {
    int r=0;
    Value a,b;
    if(valget(stk,&a,&b)) {
        r=valins(stk,gva+gvb);
        valfree(&a,&b);
    }
    return r;
}

int ulaop(Stack* stk) {
    int r=0;
    Value a;
    if(valget(stk,&a,NULL)) {
        r=valins(stk,1*gva);
        valfree(&a,NULL);
    }
    return r;
}

int ulaprd(Stack* stk) {
    int r=0;
    Value a,b;
    if(valget(stk,&a,&b)) {
        r=valins(stk,gva*gvb);
        valfree(&a,&b);
    }
    return r;
}

int ulainv(Stack* stk) {
    int r=0;
    Value a;
    if(valget(stk,&a,NULL)) {
        r=valins(stk,1/gva);
        valfree(&a,NULL);
    }
    return r;
}

int ulaequ(Stack* stk) {
    int ret=0;
    Value a,b;
    if(valget(stk,&a,&b)) ret=valbool(stk,valequ(a,b));
    return ret;
}

int ulagrt(Stack* stk) {
    int ret=0;
    Value a,b;
    if(valget(stk,&a,&b)) {
        int r=gva>gvb;
        valfree(&a,NULL);
        ret=valbool(stk,r);
    }
    return ret;
}

#undef gva
#undef gvb

int out(Stack* stk) {
    Value val=vspop(stk);
    if(val) {
        printf(val);
        valdel(&val);
        return 1;
    }
    return 0;
}

int in(Stack* stk) {
    char entrada[INSTLEN];
    char* pe=entrada;
    char c=0;
    while(((c=getchar())!='\n' && pe-entrada<INSTLEN-1)) {
        *pe++=c;
    }
    *pe=EOS;
    Value nv=valnew(0,entrada);
    return vspush(stk,nv);
}

void nln() {
    printf("\n");
}

void tab() {
    for(int k=0;k<TABSPC;k++) printf(" ");
}

//TODO Como decir si una variable es publica o privada???

int let(Variable* var,Stack* stk) {
}


