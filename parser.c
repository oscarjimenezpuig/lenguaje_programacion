/* LP 26-3-26 */
#include "parser.h"

typedef struct {
    char str[WMLEN+1]; /* palabra leida */
    struct {
        char ieoi : 1; /* es final de instruccion */
        char icom : 1; /* se han abierto comillas */
        char icap : 1; /* todo son mayusculas */
        char iwem : 1; /* palabra vacia */
        char ieop : 1; /* indica que es el final de programa */
    };
} Word;

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

static char isfin(char c) {
    char* const SFIN=CFIN;
    char* ps=SFIN;
    while(*ps!=EOS) if(*ps++==c) return 1;
    return 0;
}

static Word readword(FILE* file) {
    /* lee una nueva palabra: word
     * devuelve 1 si hay que continuar leyendo o 0 si no
     */
    Word word;
    word.ieop=0;
    word.icap=1;
    word.iwem=1;
    char* pw=word.str;
    char c=0;
    char comillas=0;
    char stop=0;
    while(!stop) {
        c=fgetc(file)
        word.icap=(word.icap==0)?0:entcap(c);
        if(comillas) {  
            if(c=='"') {
                stop=1;
            }
            else {
                *pw++=c;
                word.iwem=1;
            }
        } else {
            if(c=='"') {
                comillas=1;
                word.icom=1;
            } else if(c==EOF) {
                word.ieoi=1;
                word.ieop=1;
                stop=1;
            } else if(isfin(c)) {
                word.ieoi=1;
                stop=1;
            } else if(issep(c)) {
                stop=1;
            } else {
                *pw++=c;
                word.iwem=1;
            }
        }
    }
    *pw=EOS;
    return word;
}

static Instruction isins(char* pins) {
    char* const STRINS[]=INS;
    for(int k=0;k<SINS;k++) {
        if(valequ(pins,STRINS[k])) return (k+1);
    }
    return 0;
}

static int readfile(FILE* file) {
    Word w;
    do {
        w=readword(file);
        if(w.iwem) {
            err=tokemnew(w.ieoi);
        } else {
            char isval=(w.icom) || !(w.icap);
            if(!isval) {
                Instruction ins=isins(w.str);
                if(ins) err=tokinsnew(ins,w.ieoi);
                else err=tokvalnew(w.str,w,ieoi);
            } else err=tokvalnew(w.str,w.ieoi);
        }
    }while(!w.ieop && !err);
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



        



    
    


    





