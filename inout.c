/* LP 17-3-26 */

#include "inout.h"

int out() {
    Value val=vspop();
    if(val) {
        printf(val);
        valdel(&val);
        return 1;
    }
    return 0;
}

int in() {
    char entrada[INSTLEN];
    char* pe=entrada;
    char c=0;
    while(((c=getchar())!='\n' && pe-entrada<INSTLEN-1)) {
        *pe++=c;
    }
    *pe=EOS;
    Value nv=valnew(0,entrada);
    return vspush(nv);
}

void nln() {
    printf("\n");
}

/* prueba */

static int end() {
    vsdel();
    isdel();
    vardel();
    return valerr()+varerr()+stkerr();
}

int main() {
    vspush(valnew(0,"Introduce dos numeros: "));
    out();
    in();
    in();
    vspush(valnew(0,"La suma de los dos es: "));
    out();
    if(!ulaadd()) puts("ERROR EN SUMA");//dbg
    out();
    nln();
    return end();
}


