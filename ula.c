/* LP 14-3-26 */

#include "ula.h"

#define gva valtonum(a)
#define gvb valtonum(b)

Value ulaadd(Value a,Value b) {
    return valnew(1,gva+gvb);
}

Value ulaop(Value a) {
    return valnew(1,-1*gva);
}

Value ulaprd(Value a,Value b) {
    return valnew(1,gva*gvb);
}

Value ulainv(Value a) {
    return valnew(1,1/gva);
}

Value ulaequ(Value a,Value b) {
    char* pa=a;
    char* pb=b;
    char r=1;
    while(r && *pa!=EOS) {
        if(*pa!=*pb) r=0;
        pa++;
        pb++;
    }
    if(r && *pb!=EOS) r=0;
    if(r) return valnew(0,"1");
    else return valnew(0,"0");
}

Value ulagrt(Value a,Value b) {
    if(gva>gvb) return valnew(0,"1");
    else return valnew(0,"0");
}

#undef gva
#undef gvb



