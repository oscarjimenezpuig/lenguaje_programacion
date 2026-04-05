/* LP 5/4/26 */

#include "execute.h"

Prgexe execute=NULL;

static int nodes=0;
static int prcexes=0;

static int endexe=0;

int stkpsh(Stack* s,Value v) {
    struct node_s* nn=malloc(sizeof(struct node_s));
    if(nn) {
        nn->val=v;
        nn->prv=*s;
        *s=nn;
        ++nodes;
        return 0;
    } else  return -1;
}

Value stkpop(Stack* s) {
    Value v=NULL;
    if(s && *s) {
        struct node_s* td=*s;
        *s=td->prv;
        v=td->val;
        free(td);
        --nodes;
    }
    return v;
}

static void nodel(struct node_s* n) {
    if(n) {
        nodel(n->prv);
        valdel(&(n->val));
        free(n);
    }
}

void stkdel(Stack* s) {
    nodel(*s);
    *s=NULL;
}

static int prgexenew(Token t) {
    Prgexe pn=malloc(sizeof(struct prcexe_s));
    if(pn) {
        pn->ini=pn->act=t;
        pn->stk=NULL;
        pn->var=NULL;
        pn->prv=execute;
        execute=pn;
        ++prcexes;
        return 0;
    } else return -1;
}

int prgmain() {
    Token pt=program;
    while(pt) {
        if(pt->isi && pt->ins==PRG) {
            return prgexenew(pt);
        }
        pt=pt->nxt;
    }
    return -2;
}

#define TOKUP (execute->act=execute->act->nxt) /* avanza el token estudiado */
#define VTRUE valnew(1,1) /* valor true */

static int inscall(Value* a) {
    /* ejecucion de la instruccion inscall */
    Value nop;
    TOKUP;
    int err=tokexe(&nop);
    if(!err) {
        if(nop && *nop!=EOS) {
            Token pt=program;
            err=-5;
            while(pt && err) {
                if(pt->isi && pt->ins==PRC) {
                    Token ptn=pt->nxt;
                    if(ptn->isv && valequ(nop,ptn->val)) {
                        err=prgexenew(ptn->nxt);
                        *a=VTRUE;
                    }
                }
                pt=pt->nxt;
            }
        } else err=-4;
    }
    return err;
}

static int insendprc(Value* a) {
    /* se cierra el procedimiento actual */
    int err=0;
    Prgexe todel=execute;
    if(todel) {
        execute=todel->prv;
        varsdel(&(todel->var));
        free(todel);
        --prcexes;
        *a=VTRUE;
    } else err=-6;
    return err;
}

static int insendmain(Value* a) {
    /* se cierra el procedimiento main */
    if(execute && !execute->prv) {
        err=endprc(a);
        if(err==0) endexe=1;
    } else err=-7;
    return err;
}

static int insout(Value* a) {
    Value vtp;
    TOKUP;
    int err=tokexe(&vtp);
    if(!err) {
        if(vtp) {
            printf("%s",vtp);
            valdel(&vtp);
            *a=VTRUE;
            TOKUP;
        } else err=-8;
    }
    return err;
}

static int insin(Value* a) {
    Value soi;
    TOKUP;
    int err=tokexe(&soi);
    if(!err) {
        if(soi) {
            int ssoi=(int)valtonum(soi);
            valdel(&soi);
            char str[ssoi+1];
            char ps=str;
            char c=0;
            while(ps-str<ssoi && (c=getc())!='\n') {
                *ps++=c;
            }
            *ps=EOS;
            *a=valnew(str);
            TOKUP;
        } else err=-9;
    }
    return err;
}

static int insnln(Value* a) {
    printf("\n");
    *a=VTRUE;
    TOKUP;
    return 0;
}

static int insexe(Instruction i,Value* a) {
    /* ejecucion de todas las instrucciones */
    int err=0;
    switch(i) {
        case CLL:
            err=inscall(a);
            break;
        case CRP:
            err=insendprc(a);
            break;
        case GRP:
            err=insendmain(a);
            break;
        case IN:
            err=insin(a);
            break;
        case OUT:
            err=insout(a);
            break;
        case NLN:
            err=insnln(a);
            break;
    }
    return err;
}

static int valexe(Value o,Value* a) {
    /* ejecucion de un token tipo valor, copiando el valor del token */
    *a=valcpy(o);
    return 0;
}

int tokexe(Value* a) {
     int err=0;
     if(execute) {
         Token t=execute->act;
         if(t) {
             if(t->isi) err=insexe(t->ins,a);
             else if(t->isv) err=valexe(t->val,a);
         } else err=-3;
     }
     return err;
 }

