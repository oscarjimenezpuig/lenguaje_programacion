/* LP 10-3-26 */

#include "memoria.h"

#define EOS '\0'

static Byte memoria[MEMSIZ];

Bool memoset(Dir d,char* v) {
    if(d<MEMSIZ) {
        Byte par=0;
        char* pv=v;
        Byte pb=memoria+d
        while(*pv!=EOS && pb<memoria+MEMSIZ) {
            *pb=*pv*(par*128);
            if(par==0) par=1;
            else {
                par=0;
                pb++;
            }
        }
        if(par==1) pb++;
        return pb-memoria;
    }
    return MEMSIZ;
}

//TODO Acabar de programar la copia de la variable
    
void memoprt() {
    Byte* pm=memoria;
    while(pm!=memoria + MEMSIZ) {
        char a=*pm%128;
        char b=*pm/128;
        printf("%c%c ",a,b);
        pm++;
    }
}

int main() {
    memoset(0,"HOLAS");
    memoprt();
}
