/* LP 17-3-26 */

#include "stack.h"

static int stacks=0;

static struct stack_s* stknew() {
    struct stack_s* ns=malloc(sizeof(struct stack_s));
    return ns;
}

int vspush(Stack* sval,Value val) {
    if(val &&  sval) {
        struct stack_s* n=stknew();
        if(n) {
            ++stacks;
            n->val=val;
            n->prv=*sval;
            *sval=n;
            return 1;
        }
    }
    return 0;
}

Value vspop(Stack* sval) {
    Value v=NULL;
    if(sval && *sval) {
        v=(*sval)->val;
        struct stack_s* tdel=*sval;
        *sval=(*sval)->prv;
        free(tdel);
    }
    return v;
}

void vsdel(Stack* sval) {
    if(sval) {
        struct stack_s* ps=*sval;
        while(ps) {
            valdel(&ps->val);
            struct stack_s* tdel=ps;
            ps=ps->prv;
            free(tdel);
            --stacks;
        }
        *sval=NULL;
    }
}

int ispush(Stack* sins,Instruction ins) {
    if(ins!=INSNUL && sins) {
        struct stack_s* n=stknew();
        if(n) {
            ++stacks;
            n->ins=ins;
            n->prv=*sins;
            *sins=n;
            return 1;
        }
    }
    return 0;
}

Instruction ispop(Stack* sins) {
    Instruction i=INSNUL;
    if(sins && *sins) {
        i=(*sins)->ins;
        struct stack_s* tdel=*sins;
        *sins=(*sins)->prv;
        free(tdel);
    }
    return i;
}

void isdel(Stack* sins) {
    if(sins) {
        struct stack_s* ps=*sins;
        while(ps) {
            struct stack_s* tdel=ps;
            ps=ps->prv;
            free(tdel);
            --stacks;
        }
        *sins=NULL;
    }
}

int stkerr() {
    return stacks;
}


