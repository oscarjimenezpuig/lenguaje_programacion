/* LP 17-3-26 */

#include "stack.h"

struct stack_s {
    union {
        Value val;
        Instruction ins;
    };
    struct stack_s* prv;
};

typedef struct stack_s* Stack;

static Stack valstk=NULL;

static Stack insstk=NULL;

static struct stack_s* stknew() {
    return malloc(sizeof(struct stack_s));
}

int vspush(Value val) {
    if(val) {
        struct stack_s* n=stknew();
        if(n) {
            n->val=val;
            n->prv=valstk;
            valstk=n;
            return 1;
        }
    }
    return 0;
}

Value vspop() {
    Value v=NULL;
    if(valstk) {
        v=valstk->val;
        struct stack_s* tdel=valstk;
        valstk=valstk->prv;
        free(tdel);
    }
    return v;
}

void vsdel() {
    struct stack_s* ps=valstk;
    while(ps) {
        valdel(&ps->val);
        struct stack_s* tdel=ps;
        ps=ps->prv;
        free(tdel);
    }
    valstk=NULL;
}

int ispush(Instruction ins) {
    if(ins!=INSNUL) {
        struct stack_s* n=stknew();
        if(n) {
            n->ins=ins;
            n->prv=insstk;
            insstk=n;
            return 1;
        }
    }
    return 0;
}

Instruction ispop() {
    Instruction i=INSNUL;
    if(insstk) {
        i=insstk->ins;
        struct stack_s* tdel=insstk;
        insstk=insstk->prv;
        free(tdel);
    }
    return i;
}

void isdel() {
    struct stack_s* ps=insstk;
    while(ps) {
        struct stack_s* tdel=ps;
        ps=ps->prv;
        free(tdel);
    }
    insstk=NULL;
}

int stkerr() {
    return (insstk || valstk);
}


