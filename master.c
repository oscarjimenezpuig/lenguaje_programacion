/* LP 7/4/26 */

#include "parser.h"

#define CNF printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n")

int main(int args,char* arg[]) {
    int err=0;
    if(args>1) {
        err=parse(arg[1]);
        prgprt();//dbg
        CNF;
        if(err==0) {
            err=prgexe();
        }
        CNF;
        prgdel();
    } else err=-100;
    if(err==0) printf("SUCCESS\n");
    else printf("ERROR: %i\n",err);
    return err;
}

