/* LP 18-3-26 */

#include "program.h"

Program program=NULL;

#define PRCI 1
#define LINI 2
#define MANI 4

int toknew(Flag typ,...) {
    static Flag ini=0;
    if(!(ini & MANI) && !(typ & SMAN)) return -1;
    else if((typ & SMAN)) {
        ini|=MANI;
        return 0;
    }
    if((typ & SPRC) && (ini & PRCINI)) return -2;
    else if((typ & SPRC)) {
        ini|=PRCINI;
        typ|=(SPRC|SLIN);
    }
    if((typ & SLIN) && (ini & LINI)) return -3;
    if((typ & EMAN) && !(ini & MANI)) return -4;
    else if(typ & EMAN) ini&=~(MANI);
    if((typ & ELIN) && !(ini & LINI)) return -5;
    else if(typ & ELIN) ini&=~LINI;
    if((typ & EPRC) && !(ini & PRCI)) return -6;
    else (typ & EPRC) ini&=~PRCI;
    //TODO : Programar la malloc del token y bajar los datos.
}

   
