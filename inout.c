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


