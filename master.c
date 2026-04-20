/* LP 7/4/26 */

#include "parser.h"

int main(int args,char* arg[]) {
    system("clear");
    prgprt();//dbg
    int err=0;
    if(args>1) {
        err=parse(arg[1]);
        if(err==0) {
            err=prgexe();
        }
    } else err=-100;
    if(err==0) printf("\nSUCCESS\n");
    else printf("\nERROR: %i\n",err);
    return err;
}

