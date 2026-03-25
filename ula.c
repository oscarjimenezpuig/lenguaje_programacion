/* LP 14-3-26 */

#include "ula.h"

static int valget(Stack* stk,Value* f,Value* s) {
    int err=0;
    if(s) {
        *s=vspop(stk);
        err=(*s==NULL);
    }
    if(!err && f) {
        *f=vspop(stk);
        err=(*f==NULL);
    }
    return (err==0)?0:-8;
}

static void valfree(Value* f,Value* s) {
    if(*f) valdel(f);
    if(*s) valdel(s);
}

static int valins(Stack* stk,double a) {
    if(vspush(stk,valnew(1,a))) return 0;
    else return -1000;
}

static int valbool(Stack* stk,int res) {
    Value nv=(res)?valnew(0,"1"):valnew(0,"0");
    if(vspush(stk,nv)) return 0;
    else return -1000;
}

#define gvf valtonum(f)
#define gvs valtonum(s)


int binary(Stack* stk,char op) {
    int err=0;
    Value f,s;
    if((err=valget(stk,&f,&s))==0) {
        if(op=='+') err=valins(stk,gvf+gvs);
        else if(op=='*') err=valins(stk,gvf*gvs);
        valfree(&f,&s);
    }
    return err;
}

int unary(Stack* stk,char op) {
    int r=0;
    Value f;
    if((err=valget(stk,&f,NULL))==0) {
        if(op=='-') err=valins(stk,(-1)*gvf);
        else if(op=='/') err=valins(stk,1/gvf);
        valfree(&f,NULL);
    }
    return err;
}

int comp(Stack* stk,char op) {
    int err=0;
    Value f,s;
    if((err=valget(stk,&f,&s))==0) {
        if(op=='=') err=valbool(stk,valequ(f,s));
        else if(op=='>') err=valbool(stk,gvf>gvs);
        valfree(&f,&s);
    }
    return err;
}


#undef gvf
#undef gvs

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

int let(Variable* var,Stack* stk) {
    Value nom=vspop(stk);
    if(nom) return varnew(var,nom,1);
    return 0;
}

int set(Variable* var,Stack*stk) {
    Value nom=vspop(stk);
    if(nom) {
        Value val=vspop(stk);
        if(val) {
            return varset(var,nom,0,val);
        }
    }
    return 0;
}

int get(Variable* var,Stack* stk) {
    Value nom=vspop(stk);
    if(nom) {
        Value val=varget(var,nom,0);
        if(val) return vspush(stk,val);
    }
    return 0;
}

int arl(Variable* var,Stack* stk) {
    Value nom=vspop(stk);
    if(nom) {
        Value val=vspop(stk);
        if(val) {
            int num=valtonum(val);
            return varnew(var,nom,num);
        }
    }
    return 0;
}

int ars(Variable* var,Stack* stk) {
    Value nom=vspop(stk);
    if(nom) {
        Value vnum=vspop(stk);
        if(vnum) {
            int num=valtonum(vnum);
            Value val=vspop(stk);
            if(val) return varset(var,nom,num,val);
        }
    }
    return 0;
}

int arg(Variable* var,Stack* stk) {
    Value nom=vspop(stk);
    if(nom) {
        Value vnum=vspop(stk);
        if(vnum) {
            int num=valtonum(vnum);
            Value val=varget(var,nom,num);
            if(val) return vspush(stk,val);
        }
    }
    return 0;
}



