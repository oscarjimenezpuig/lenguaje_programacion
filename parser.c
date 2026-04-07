/* LP 26-3-26 */
#include "parser.h"

typedef char Word[WMLEN+1];

#define entcap(A) ((A)>='A' && (A)<='Z')

static FILE* openfile(char* name) {
    /* se abre archivo */
    FILE* file=NULL;
    if(name) file=fopen(name,"r");
    return file;
}

static void closefile(FILE** file) {
    /* se cierra archivo */
    fclose(*file);
    *file=NULL;
}

static char issep(char c) {
    char* const SEPS=CSEP;
    char* ps=SEPS;
    while(*ps!=EOS) if(*ps++==c) return 1;
    return 0;
}

static char readword(FILE* file,char* cap,Word word) {
    /* lee una palabra, devuelve 0 si hay final de archivo o 1 si no lo hay */
    /* si capital es 1 es posible instruccion si no es valor */
    char ret=-1;
    *cap=1;
    char* pw=word;
    char c=0;
    char comillas=0;
    while(ret==-1) {
        c=fgetc(file);
        if(c=='"') {
            if(comillas) ret=1;
            else comillas=1;
        }else if(c==EOF) {
            ret=0;
        }else if(issep(c) && !comillas) {
            ret=1;
        } else {
            if(!comillas && entcap(c)) *cap=(*cap==0)?0:1;
            *pw++=c;
        }
    }
    *pw=EOS;
    return ret;
}

static unsigned char isins(Word word) {
    char* const STRINS[]=INS;
    for(int k=0;k<SINS;k++) {
        if(valequ(word,STRINS[k])) return (k+1);
    }
    return 0;
}

static int readfile(FILE* file) {
    char notend=0;
    int err=0;
    Word word;
    do {
        char cap=0;
        notend=readword(file,&cap,word);
        if(*word!=EOS) {
            if(cap) {
                Instruction ins=0;
                if((ins=isins(word))) {
                    err=tokinsnew(ins);
                    continue;
                }
            }
            err=tokvalnew(word);
        }
    }while(notend && !err);
    return err;
}

int parse(char* name) {
    int err=0;
    FILE* file=NULL;
    if((file=openfile(name))) {
        err=readfile(file);
        closefile(&file);
    } else err=-101;
    return err;
}



        



    
    


    





