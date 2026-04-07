/* LP 7/4/26 */

#include "parser.h"

int main(int args,char* arg[]) {
    int err=0;
    if(args>1) {
        err=parse(arg[1]);
        prgprt();//dbg
        if(err==0) {
            err=prgexe();
        }
        prgdel();
    } else err=-100;
    return err;
}

