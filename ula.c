/* LP 14-3-26 */

#include "ula.h"

static int valget(Value* a,Value* b) {
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

static int valins(double a) {
    return vspush(valnew(1,a));
}

static int valbool(int res) {
    Value nv=(res)?valnew(0,"1"):valnew(0,"0");
    return vspush(nv);
}

#define gva valtonum(a)
#define gvb valtonum(b)

int ulaadd() {
    int r=0;
    Value a,b;
    if(valget(&a,&b)) {
        r=valins(gva+gvb);
        valfree(&a,&b);
    }
    return r;
}

int ulaop() {
    int r=0;
    Value a;
    if(valget(&a,NULL)) {
        r=valins(1*gva);
        valfree(&a,NULL);
    }
    return r;
}

int ulaprd() {
    int r=0;
    Value a,b;
    if(valget(&a,&b)) {
        r=valins(gva*gvb);
        valfree(&a,&b);
    }
    return r;
}

int ulainv() {
    int r=0;
    Value a;
    if(valget(&a,NULL)) {
        r=valins(1/gva);
        valfree(&a,NULL);
    }
    return r;
}

int ulaequ() {
    int ret=0;
    Value a,b;
    if(valget(&a,&b)) ret=valbool(valequ(a,b));
    return ret;
}

int ulagrt() {
    int ret=0;
    Value a,b;
    if(valget(&a,&b)) {
        int r=gva>gvb;
        valfree(&a,NULL);
        ret=valbool(r);
    }
    return ret;
}

#undef gva
#undef gvb



