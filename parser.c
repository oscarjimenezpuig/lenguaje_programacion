/* LP 26-3-26 */
#include "parser.h"

#define EOW ' '
#define EOL '\n'

#define entnum(A) ((A)>='0' && (A)<='9')
#define entcap(A) ((A)>='A' && (A)<='Z')
#define entlow(A) ((A)>='a' && (A)<='z')

typedef struct {
    char str[WMLEN]; /* cadena que representa el word */
    char end; /* nos dice el caracter final espacio,EOS o EOF */
    Flag typ; /* tipo TVAL o TINS o 0*/
    Flag ins; /* numero de instruccion en caso de que sea instruccion */
} Word;

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

static int issep(char c) {
    char* const SEP=CSEP;
    char* ps=SEP;
    while(*ps!=EOS) if(*ps++==c) return 1;
    return 0;
}

static int isnum(char* str) {
    int punto;
    int numero=0;
    char* p=str;
    if((punto=(*p=='.')) || *p=='-' || (numero=entnum(*p))) {
        p++;
        while(*p!=EOS) {
            if(*p=='.') {
                if(punto) return 0;
                else punto=1;
            } else if((numero=entnum(*p))==0) return 0;
            p++;
        }
    }
    return numero;
}
        
static int strequ(char* a,char* b) {
    char* pa=a;
    char* pb=b;
    while(*pa!=EOS) {
        if(*pa++!=*pb++) return 0;
    }
    return (*pb==EOS);
}       

static int isins(char* str) {
    char* const CSINS[]=INS;
    for(int k=0;k<SINS;k++) {
        if(strequ(str,CSINS[k])) return k+1;
    }
    return 0;
}

static int islow(char* str) {
    char* p=str;
    ++p;
    while(*p!=EOS) {
        if(!entlow(*p)) return 0;
    }
    return 1;
}

static void wordprt(Word w) {
    printf("type->%i word->%s ins->%i end->%i\n",w.typ,w.str,w.ins,w.end) ;
}

static Word wordget(FILE* file) {
    /* lee una palabra entera y la clasifica */
    Word w;
    w.typ=0;
    w.end=2;
    w.ins=0;
    Flag hcom=0;
    char* pw=w.str;
    while(w.end==2) {
        char c=fgetc(file);
        if(c=='"') {
            if(hcom==0) hcom=1;
            else if(hcom==1) {
                w.end=EOW;
                w.typ=TVAL;
            }
        } else if(c==EOL || c==EOF) {
            if(hcom) w.typ=TVAL;
            w.end=c;
        } else if(issep(c)) {
            if(hcom) *pw++=c;
            else w.end=EOW;
        } else {
            *pw++=c;
        }
    }
    *pw=EOS;
    if(w.typ==0 && *(w.str)!=EOS) {
        if(isnum(w.str)) w.typ=TVAL;
        else if((w.ins=isins(w.str))) w.typ=TINS;
        else if(islow(w.str)) w.typ=TVAL;
    }
    return w;
}

static void wordins(Word word) {
    /* introduce la palabra en el programa */
    wordprt(word); //dbg
    Flag type=word.typ;
    if(word.end==EOL || word.end==EOF) type|=ELIN;
    if((type & TINS)) {
        if(word.ins==PRC) type|=SPRC;
        else if(word.ins==CRP) type|=EPRC;
        else if(word.ins==PGR) type|=SMAN;
        else if(word.ins==RGP) type|=EMAN;
    }
    if(type) printf("-->program type=%i ins=%i word=%s\n",type,word.ins,word.str);//dbg
    if((type & TVAL)) {
        toknew(type,word.str);
    } else if((type & TINS)) {
        toknew(type,word.ins);
    } else if(type) {
        toknew(type);
    }
    if(type & ELIN) {
        toknew(SLIN);
        printf("-->newline\n"); //dbg
    }

}

static int parse(char* name) {
    /* transforma el codigo del archivo en un programa */
    FILE* file=openfile(name);
    if(file) {
        Word w;
        do {
            wordins((w=wordget(file)));
        } while(w.end!=EOF);
        closefile(&file);
        prgprt();
        return 0;
    }
    return -13;
}


static int exe() {
    /* ejecucion del programa y final */
    int err=prgexe();
    if(err==0) {
        err=valerr() + varerr() + stkerr() + prgerr() + exeerr();
    }
    return err;
}

int make(char* name) {
    int err=0;
    if((err=parse(name))) {
        err=exe();
    }
    return err;
}

int main(int args,char* arg[]) {
    if(args>1) {
       return make(arg[1]);
    } else return -13;
}







    





