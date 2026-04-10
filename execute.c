/* LP 5/4/26 */

#include "execute.h"

Prgexe execute=NULL;

static int prcexes=0;

static int endexe=0;

static int tokexe(Value* a); /* predefinicion de tokexe */

static int prgexenew(Token t) {
    Prgexe pn=malloc(sizeof(struct prcexe_s));
    if(pn) {
        pn->ini=pn->act=t;
        pn->var=NULL;
        pn->prv=execute;
        execute=pn;
        ++prcexes;
        return 0;
    } else return -1;
}

static void prcdel(Prgexe prc) {
    if(prc) {
        prcdel(prc->prv);
        varsdel(&(prc->var));
        free(prc);
        --prcexes;
    }
}

static void prgexedel() {
    /* libera todos los procedimientos */
    prcdel(execute);
    execute=NULL;
}


static int prgmain() {
    /* inicio del procedimiento main */
    Token pt=program;
    while(pt) {
        if(pt->isi && pt->ins==PRG) {
            return prgexenew(pt->nxt);
        }
        pt=pt->nxt;
    }
    return -2;
}

static int tokup() {
    /* busca el siguiente token siempre y cuando no haya final de instruccion */
    Token ta=execute->act;
    if(!ta->ifi) { 
        if(ta->nxt) {
            execute->act=ta->nxt;
            return 0;
        }
    }
    return -15;
}

static int nxtin() {
    /* busca el final de la instruccion actual y comprueba que hay una nueva instruccion */
    Token t=execute->act;
    while(t && t->ifi==0) {
        t=t->nxt;
    }
    if(t && t->ifi) {
        t=t->nxt;
        if(t && t->isi) {
            execute->act=t;
            return 0;
        }
    }
    return -11;
}

#define VNUL NULL /* valor nulo */

static int inscall(Value* a) {
    /* ejecucion de la instruccion inscall */
    Value nop;
    int err=tokup();
    if(!err) {
        tokexe(&nop);
        if(!err) {
            if(nop && *nop!=EOS) {
                Token pt=program;
                err=-5;
                while(pt && err) {
                    if(pt->isi && pt->ins==PRC) {
                        Token ptn=pt->nxt;
                        if(ptn->isv && valequ(nop,ptn->val)) {
                            err=nxtin();
                            if(!err) {
                                err=prgexenew(ptn->nxt);
                                *a=VNUL;
                            }
                        }
                    }
                    pt=pt->nxt;
                }
                valdel(&nop);
            } else err=-4;
        }
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
        *a=VNUL;
    } else err=-6;
    return err;
}

static int insendmain(Value* a) {
    /* se cierra el procedimiento main */
    int err=0;
    if(execute && !execute->prv) {
        err=insendprc(a);
        if(err==0) {
            endexe=1;   
        }
    } else err=-7;
    return err;
}

static int insout(Value* a) {
    Value vtp;
    int err=tokup();
    if(!err) {
        err=tokexe(&vtp);
        if(!err) {
            if(vtp) {
                printf("%s",vtp);
                valdel(&vtp);
                *a=VNUL;
                err=nxtin();
            } else err=-8;
        }
    }
    return err;
}

static int insin(Value* a) {
    Value soi;
    int err=tokup();
    if(!err) {
        err=tokexe(&soi);
        if(!err) {
            if(soi) {
                int ssoi=(int)valtonum(soi);
                valdel(&soi);
                char str[ssoi+1];
                char* ps=str;
                char c=0;
                while(ps-str<ssoi && (c=getchar())!='\n') {
                    *ps++=c;
                }
                *ps=EOS;
                *a=valnew(0,str);
                valdel(&soi);
            } else err=-9;
        }
    }
    return err;
}

static int insnln(Value* a) {
    printf("\n");
    *a=VNUL;
    int err=nxtin();
    return err;
}

static int insrem(Value* a) {
    /* salta todos los valores del rem hasta la siguiente instruccion y los elimina */
    int err=nxtin();
    *a=VNUL;
    return err;
}

static int inslet(Value* a,char isarr) {
    Value nov;
    int err=tokup();
    if(!err) {
        err=tokexe(&nov);
        if(!err) {
            unsigned int dim=0;
            if(isarr) {
                Value sdim;
                err=tokup();
                if(!err) {
                    err=tokexe(&sdim);
                    if(!err) dim=valtonum(sdim);
                }
            } else dim=1;
            if(dim) {
                err=varnew(&(execute->var),nov,dim);
                *a=VNUL;
                err=nxtin();
            }  else err=-12;
        }
    }
    return err;
}

static Prgexe findmain() {
    Prgexe pp=execute;
    while(pp->prv) {
        pp=pp->prv;
    }
    return pp;
}

static int insget(Value* a,char isarr) {
    Value nov;
    int err=tokup();
    if(!err) {
        int pos=-1;
        err=tokexe(&nov);
        if(!err) {
            if(isarr) {
                Value spos;
                err=tokup();
                if(!err) {
                    err=tokexe(&spos);
                    if(!err) {
                        pos=valtonum(spos);
                    }
                }
            }  
        } else pos=0;
        if(pos>=0) {
            Value val=varget(&(execute->var),nov,pos);
            if(!val) {
                Prgexe prcm=findmain();
                val=varget(&(prcm->var),nov,pos);
                if(!val) {
                    err=-14;
                } else {
                    *a=val;
                    err=nxtin();
                }
            }
        } else {
            err=-13;
        }
    }
    return err;
}

static int insset(Value* a,char isarr) {
    Value nov;
    int err=tokup();
    if(!err) {
        int pos=-1;
        err=tokexe(&nov);
        if(!err) {
            if(isarr) {
                Value spos;
                err=tokup();
                if(!err) {
                    err=tokexe(&spos);
                    if(!err) {
                        pos=valtonum(spos);
                    }
                }
            }
        } else pos=0;
        if(pos>=0) {
            Value val;
            int err=tokup();
            if(!err) {
                err=tokexe(&val);
                if(!err) {
                    if(!varset(&(execute->var),nov,pos,val)) {
                        Prgexe prcm=findmain();
                        if(!varset(&(prcm->var),nov,pos,val)) {
                            err=-16;
                        }
                        *a=VNUL;
                        err=nxtin();

                    }
                }
            }
        }
    }
    return err;
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
        case REM:
            err=insrem(a);
            break;
        case LET:
            err=inslet(a,0);
            break;
        case ARL:
            err=inslet(a,1);
            break;
        case GET:
            err=insget(a,0);
            break;
        case SET:
            err=insset(a,0);
            break;
        case ARG:
            err=insget(a,1);
            break;
        default:
            err=-11;
    }
    return err;
}

static int valexe(Value o,Value* a) {
    /* ejecucion de un token tipo valor, copiando el valor del token */
    *a=valcpy(o);
    return 0;
}

static int tokexe(Value* a) {
    /* se ejecuta el actual token del procedimiento */
    int err=0;
    if(execute) {
        Token t=execute->act;
        if(t) {
            if(t->isi) err=insexe(t->ins,a);
            else if(t->isv) err=valexe(t->val,a);
        } else err=-3;
    } else err=-10;
    return err;
}

static int tokexeins(Value* a) {
    /* se ejecuta el token que obligatoriamente ha de ser instruccion */
    int err=0;
    if(execute) {
        Token t=execute->act;
        if(t) {
            if(t->isi) err=insexe(t->ins,a);
            else err=-11;
        } else err=-3;
    } else err=-10;
    return err;
}

int prgexe() {
    int err=prgmain();
    while(!endexe && !err) {
        Value a=NULL;
        err=tokexeins(&a);
        valdel(&a);
    }
    prgexedel();
    return err;
}

int prgexeerr() {
    return prcexes;
}
            

        


