/* LP 18-3-26 */

#include "program.h"

/* program set */

Program program=NULL;
static Token prglast=NULL;

static int tokens=0;

static Token toknew() {
    /* crea un nuevo apuntador a token */
    Token nt=malloc(sizeof(struct token_s));
    if(nt) {
        ++tokens;
        nt->isi=nt->isv=0;
        nt->ins=0;
        nt->nxt=NULL;
        nt->prv=prglast;
        if(!prglast) {
            program=nt;
        } else {
            prglast->nxt=nt;
        }
        prglast=nt;
        }
    return nt;
}

int tokinsnew(Instruction i) {
    Token nt=toknew();
    if(nt) {
        nt->isi=1;
        nt->ins=i;
        return 0;
    } else return -1;
}

int tokvalnew(char* str) {
    Token nt=toknew();
    if(nt) {
        nt->isv=1;
        nt->val=valnew(0,str);
        return 0;
    } else return -1;
}

static void tokdel(Token* t) {
    if(t && *t) {
        Token tt=*t;
        tokdel(&(tt->nxt));
        if(tt->isv) valdel(&(tt->val));
        free(tt);
        *t=NULL;
        --tokens;
    }
}

void prgdel() {
    tokdel(&program);
    program=prglast=NULL;
}

int prgerr() {
    return tokens;
}

