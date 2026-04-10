/* LP 18-3-26 */

#include "program.h"

/* program set */

Program program=NULL;
static Token prglast=NULL;

static int tokens=0;

static Token toknew(char ieoi) {
    /* crea un nuevo apuntador a token */
    Token nt=malloc(sizeof(struct token_s));
    if(nt) {
        ++tokens;       
        nt->isi=nt->isv=0;
        nt->ifi=ieoi;
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

int tokinsnew(Instruction i,char iei) {
    Token nt=toknew(iei);
    if(nt) {
        nt->isi=1;
        nt->ins=i;
        return 0;
    } else return -1;
}

int tokvalnew(char* str,char iei) {
    Token nt=toknew(iei);
    if(nt) {
        nt->isv=1;
        nt->val=valnew(0,str);
        return 0;
    } else return -1;
}

int tokempnew(char iei) {
    if(toknew(iei)) return 0;
    else return -1;
}   

void tokprt(Token t) {
    printf("Token= ");
    if(t) {
        if(t->isi) printf("I(%i)",t->ins);
        else if(t->isv) printf("V(%s)",t->val);
        if(t->ifi) printf("\n");
        else printf(" -> ");
    } else printf("Null");
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

void prgprt() {
    Token t=program;
    while(t) {
        tokprt(t);
        t=t->nxt;
    }
    printf("\n");
}
    
void prgdel() {
    tokdel(&program);
    program=prglast=NULL;
}

int prgerr() {
    return tokens;
}

