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

static int issep(char c) {
    /* comprueba si el caracter es uno de los separadores */
    const char CSEP=SEP;
    char* pc=CSEP;
    while(*pc!=EOS) {
        if(*pc==c) return 1;
        pc++;
    }
    return 0;
}

static int isins() {
    /* mira si el word es instruccion Y determina cual es */
    const char STINS[]=INS;
    for(int k=0;k<=SINS;k++) {
        if(valequ(word,STINS[k])) return k+1;
    }
    return 0;
}

#define ISCAP(X) ((X)>='A' && (X)<='Z')
#define ISMIN(X) ((X)>='a' && (X)<='z')

static int chkcap() {
    /* mira si es un procedimiento=2, variable=3 o instruccion=1 */
    char* pw=word;
    int type=0;
    if(*pw!=EOS) {
        if(ISCAP(*pw)) {
            type=2;
            pw++;
            if(*pw!=EOS) if(ISCAP(*pw)) type=1;
        } else if(ISMIN(*pw)) type=3;
    }
    if(type==1) {
        while(*pw!=EOS) {
            if(!ISCAP(*pw)) return 0;
            pw++;
        }
    }
    return type;
}
        
#define ISNUM(X) ((X)>='0' && (X)<='9')

static int chknum() {
    char* pw=word;
    Flag has_punto=0;
    if(

static Flag readword()



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


