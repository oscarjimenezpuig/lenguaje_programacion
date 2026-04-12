/* LP 14-3-26 */

#include "value.h"

static int values=0;

static size_t len(char* str) {
    char* p=str;
    while(*p++!=EOS);
    return p-str;
}

static Value valfromstrnew(char* str) {
    size_t lstr=len(str);
    Value v=malloc(lstr*sizeof(char));
    if(v) {
        ++values;
        char* ps=str;
        Value pv=v;
        while(*ps!=EOS) {
            *pv++=*ps++;
        }
        *pv=EOS;
    }
    return v;
}

static void zeroout(char* str) {
    char* ps=str;
    char dec=0;
    while(*ps!=EOS) {
        if(*ps=='.') dec=1;
        ps++;
    }
    if(dec) {
        ps--;
        while(*ps=='0') {
            *ps=EOS;
            ps--;
        }
        if(*ps=='.') *ps=EOS;
    }
}

Value valnew(char in,...) {
    va_list list;
    va_start(list,in);
    char* str;
    char stru[40];
    if(in) {
        double n=va_arg(list,double);
        sprintf(stru,"%lf",n);
        zeroout(stru);
        str=stru+0;
    } else {
        str=va_arg(list,char*);
    }
    va_end(list);
    return valfromstrnew(str);
}

Value valcpy(Value a) {
    size_t alen=len(a);
    Value v=malloc(sizeof(unsigned char)*alen);
    if(v) {
        ++values;
        Value pa=a;
        Value pv=v;
        int c=alen;
        while(c-->0) {
            *pv++=*pa++;
        }
    }
    return v;
}

void valdel(Value* v) {
    if(v && *v) {
        free(*v);
        *v=NULL;
        --values;
    }
}

double valtonum(Value v) {
    double r=0;
    if(v) sscanf(v,"%lf",&r);      
    return r;
}

int valisfalse(Value v) {
    double dv=valtonum(v);
    if(dv==0) return 1;
    return 0;
}

int valequ(Value v,Value w) {
    char* pv=v;
    char* pw=w;
    while(*pv!=EOS) {
        if(*pv!=*pw) return 0;
        pv++;
        pw++;
    }
    return (*pw==EOS);
}   

void valprt(Value v) {
    printf(v);
}

int valerr() {
    return values;
}


