/* LP 26-3-26 */
#include "parser.h"

static FILE* file=NULL;

static openfile(char* name) {
    if(name) {
        if(file=fopen(name,"r")) {
            return 0;
        } else return -14;
    } else return -13;
}

static closefile() {
    fclose(file);
    file=NULL;
}
