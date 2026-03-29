/* LP 26-3-26 */
#include "parser.h"

#define entnum(A) ((A)>='0' && (A)>='9')
#define entcap(A) ((A)>='A' && (A)<='Z')
#define entlow(A) ((A)>='a' && (A)<='z')

typedef char Word[WMLEN];

typedef enum {NOS,SEP,EOL,EOP} Signal;
typedef enum {NOT,NUM,LOW,MED,CAP} Type;

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

static int essep(char c) {
    char* const SEP=CSEP;
    char* ps=SEP;
    while(*ps!=EOS) if(*ps++==c) return 1;
    return 0;
}

static Signal wordset(FILE* file,Word word) {
    /* lee una palabra entera del fichero */
    char* pw=word;
    Signal s=NOS;
    while(s==NOS) {
        char c=fgetc(file);
        if(essep(c)) s=SEP;
        else if(c==FDL) s=EOL;
        else if(c==EOF) s=EOP;
        else *pw++=c;
    }
    *pw=EOS;
    return s;
}

static int isnum(Word word) {
    char* pw=word;
    int point=0;
    while(*pw!=EOS) {
        if(*pw=='-' && pw!=word) return 0;
        else if(*pw=='.') {
            if(point) return 0;
            point=1;
        } else if(!entnum(*pw)) return 0;
        pw++;
    }
    return 1;
}

static Type capchk(Word word) {
    char* pw=(word+1);
    int iscap=-1;
    if(*pw!=EOS) {
        iscap=(entcap(*pw))?1:(entlow(*pw))?-1:0;
    }
    while(*pw!=EOS && iscap) {
        if(entcap(*pw) && iscap!=1) return NOT;
        else if(entlow(*pw) && iscap!=-1) return NOT;
        pw++;
    }
    if(iscap==1) return CAP;
    else if(iscap==-1) return MED;
    else return NOT;
}

static int islow(Word word) {
    char* pw=word;
    while(*pw!=EOS) {
        if(!entlow(*pw++)) return 0;
    }
    return 1;
}

static int isins(Word word) {
    char* const CSINS[]=INS;
    for(int k=0;k<SINS;k++) {
        if(valequ(word,CSINS[k])) return k+1;
    }
    return 0;
}

static void wordins(Signal signal,Word word) {
    /* classifica una palabra y la pone en el programa */
    Flag tt=(signal==EOL)?ELIN:0;
    Type t=NOT;
    if(*word=='-' || *word=='.' || entnum(*word)) {
        t=isnum(word)?NUM:NOT;
    } else if(entcap(*word)) {
        t=capchk(word);
    } else if(entlow(*word)) {
        t=islow(word)?LOW:NOT;
    }
    if(t==NUM || t==LOW || t==MED) {
        tt|=TVAL;
        toknew(tt,word);
    } else if(t==CAP) {
        Instruction ins=isins(word);
        if(ins) {
            tt|=TINS;
            switch(ins) {
                case PGR:
                    tt|=SMAN;
                    break;
                case RGP:
                    tt|=EMAN;
                    break;
                case PRC:
                    tt|=SPRC;
                    break;
                case CRP:
                    tt|=EPRC;
                    break;
            }
            toknew(tt,ins);
        }
    }
    if(tt & ELIN) toknew(SLIN);
}

static int programset(char* name) {
    FILE* file=openfile(name);
    if(file) {
        Word word;
        Signal sig=NOS;
        while(sig!=EOP) {
            sig=wordset(file,word);
            wordins(sig,word);
        }
        closefile(&file);
        prgprt(); /* dbg de impresion de programa */
        return 0;
    } 
    return -13;
}

static int programexe() {
    /* ejecucion del programa y final */
    int err=prgexe();
    if(err==0) {
        err=valerr() + varerr() + stkerr() + prgerr() + exeerr();
    }
    return err;
}

int make(char* name) {
    int err=0;
    if((err=programset(name))) {
        err=programexe();
    }
    return err;
}

int main(int args,char* arg[]) {
    if(args>1) {
       return make(arg[1]);
    } else return -13;
}







    





