/* LP 26-3-26 */
#include "parser.h"

#define NOTHING 0
#define INSTRUCTION 1
#define VALUE 2

static char word[WMLEN];

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

static int essep(char c) {
    /* comprueba si el caracter es uno de los separadores */
    const char CSEP=SEP;
    char* pc=CSEP;
    while(*pc!=EOS) {
        if(*pc==c) return 1;
        pc++;
    }
    return 0;
}

static int esins() {
    /* mira si el word es instruccion Y determina cual es */


static int readword() {
    char* pw=word;
    int hay_com=0;
    int com_ab=0;

    char c=0;
    while((c=fgetc(file)) && c!=EOF && (com_ab || !essep(c))) {
        if(c=='"') {
            hay_com=1;
            com_ab=!com_ab;
        }
        *pw++=c;
    }
    *pw=EOS;
    return (C!=EOF);
}   


