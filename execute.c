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

static int instab(Value* a) {
    for(int k=0;k<TABSPC;k++) printf(" ");
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
                    valdel(&sdim);
                }
            } else dim=1;
            if(dim) {
                err=varnew(&(execute->var),nov,dim);
                *a=VNUL;
                err=nxtin();
            }  else err=-12;
        }
        valdel(&nov);
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
                    valdel(&spos);
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
                } else {
                    *a=val;
                }
            } else {
                err=-13;
            }
        }
        valdel(&nov);
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
                    valdel(&spos);
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
                            if(prcm==execute || !varset(&(prcm->var),nov,pos,val)) {
                                err=-16;
                            }
                        }
                        if(!err) {
                            *a=VNUL;
                            err=nxtin();
                        }
                    }
                }
            } else err=-13;
        }
        valdel(&nov);
    }
    return err;
}

static int mod(double da,double db) {
    int ia=(int) da;
    int ib=(int) db;
    if(ib!=0) {
        return ia%ib;
    } else return 0;
}

static int rnd(double da,double db) {
    int ia=(int)da;
    int ib=(int)db;
    int g=(ia>ib)?ia:ib;
    int p=(g==ia)?ib:ia;
    int dif=g-p+1;
    return (rand()%dif)+p;
}

static double bopnum(char op,Value a,Value b) {
    /* operaciones numericas */
    double da=valtonum(a);
    double db=valtonum(b);
    switch(op) {
        case '+':
            return da+db;
        case '*':
            return da*db;
        case '%':
            return mod(da,db);
        case 'r':
            return rnd(da,db);
    }
    return 0;
}

static char bopbol(char op,Value a,Value b) {
    int da=valisfalse(a)?0:1;
    int db=valisfalse(b)?0:1;
    switch(op) {
        case '&':
            return (da & db)?'1':'0';
        case '|':
            return (da | db)?'1':'0';
    }
    return '0';
}

static double bopcmp(char op,Value a,Value b) {
    if(op=='=') {
        return valequ(a,b)?1:0;
    } else {
        if(op=='>') {
            double da=valtonum(a);
            double db=valtonum(b);
            return (da>db)?1:0;
        } else return 0;
    }
}

static int insbin(Instruction i,Value* a) {
    /* evaluacion de operaciones binarias */
    Value pv,sv;
    int err=0;
    *a=VNUL;
    if(!(err=tokup()) && !(err=tokexe(&pv)) && !(err=tokup()) && !(err=tokexe(&sv))) {
        switch(i) {
            case ADD:
                *a=valnew(1,bopnum('+',pv,sv));
                break;
            case PRD:
                *a=valnew(1,bopnum('*',pv,sv));
                break;
            case MOD:
                *a=valnew(1,bopnum('%',pv,sv));
                break;
            case RND:
                *a=valnew(1,bopnum('r',pv,sv));
                break;
            case AND:
                *a=valnew(1,bopbol('&',pv,sv));
                break;
            case OR:
                *a=valnew(1,bopbol('|',pv,sv));
                break;
            case EQU:
                *a=valnew(1,bopcmp('=',pv,sv));
                break;
            case GRT:
                *a=valnew(1,bopcmp('>',pv,sv));
                break;
        }
        valdel(&pv);
        valdel(&sv);
    }
    return err;
}

static double uopnum(char op,Value a) {
    double da=valtonum(a);
    switch(op) {
        case '-':
            return -da;
        case '/':
            return 1/da;
    }
    return 0;
}

static double uopbol(char op,Value a) {
    int da=valtonum(a);
    switch(op) {
        case '~':
            return (da)?0:1;
    }
    return 0;
}

static int insuni(Instruction i,Value* a) {
    /* evaluacion de operaciones unarias */
    Value val;
    int err=0;
    *a=VNUL;
    if(!(err=tokup()) && !(err=tokexe(&val))) {
        switch(i) {
            case OP:
                *a=valnew(1,uopnum('-',val));
                break;
            case INV:
                *a=valnew(1,uopnum('/',val));
                break;
            case NOT:
                *a=valnew(1,uopbol('~',val));
                break;
        }
        valdel(&val);
    }
    return err;
}

static int inslab(Value* a) {
    /* instruccion label (no hace nada) */
    *a=VNUL;
    int err=nxtin();
    return err;
}

static int insjmp(Value* a) {
    /* salto */
    Value nol;
    int err=tokup();
    if(!err) {
        err=tokexe(&nol);
        if(!err) {
            Token jmp=NULL;
            Token pt=execute->ini;
            while(pt) {
                if(pt->isi) {
                    if(pt->ins==CRP || pt->ins==GRP) pt=NULL;
                    else if(pt->ins==LAB) {
                        pt=pt->nxt;
                        if(pt && pt->isv) {
                            if(valequ(pt->val,nol)) {
                                jmp=pt->prv;
                            }
                        } else {
                            err=-19;
                        }
                    }
                }
                if(pt) pt=pt->nxt;
            }
            if(!jmp) err=-18;
            else {
                execute->act=jmp;
                *a=VNUL;
            }
        }
        valdel(&nol);
    }
    return err;
}

static int insfi(Value* a) {
    /* se encuentra final de condicional, no hace nada */
    *a=VNUL;
    int err=nxtin();
    return err;
}

static int insif(Value* a) {
    /* se encuentra condicional */
    Value cnd=NULL;
    int err=0;
    *a=VNUL;
    if(!(err=tokup()) && !(err=tokexe(&cnd))) {
        if(valisfalse(cnd)) {
            int conds=1;
            Token pt=execute->act;
            Token jmp=NULL;
            while(pt && !jmp) {
                if(pt->isi) {
                    if(pt->ins==IF) ++conds;
                    else if(pt->ins==FI) {
                        --conds;
                        if(conds==0) {
                            jmp=pt;
                        }
                    } else if(pt->ins==CRP || pt->ins==GRP) pt=NULL;
                }
                if(pt) pt=pt->nxt;
            }
            if(jmp) {
                execute->act=jmp;
            } else {
                err=-20;
            }
        } else {
            err=nxtin();
        }
        valdel(&cnd);
    }
    return err;
}

static int inspol(Value* a) {
    /* fin de la instruccion loop, regresa al condicional de inicio*/
    int err=0;
    int cond=0;
    Token pt=execute->act;
    do {
        if(pt) {
            if(pt->isi) {
                if(pt->ins==PRC || pt->ins==PRG) err=-22;
                else if(pt->ins==POL) ++cond;
                else if(pt->ins==LOP) {
                    --cond;
                    if(cond==0) {
                        execute->act=pt;
                        *a=VNUL;
                    }
                }
            }
            pt=pt->prv;
        } else err=-22;
    }while(cond && !err);
    return err;
}

static int inslop(Value* a) {
    /* instruccion loop, requiere valor booleano */
    *a=VNUL;
    int err=0;
    Value cnd;
    if((err=tokup())==0 && (err=tokexe(&cnd))==0) {
        if(valisfalse(cnd)) {
            int cond=1;
            Token pt=execute->act;
            while(cond && !err) {
                if(pt) {
                    if(pt->isi) {
                        if(pt->ins==CRP || pt->ins==GRP) err=-21;
                        else if(pt->ins==LOP) ++cond;
                        else if(pt->ins==POL) {
                            --cond;
                            if(cond==0) {
                                execute->act=pt;
                                err=nxtin();
                            }
                        }
                    }
                    pt=pt->nxt;
                } else err=-21;
            }
        } else {
            err=nxtin();
        }
        valdel(&cnd);
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
        case TAB:
            err=instab(a);
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
        case ADD:
        case PRD:
        case AND:
        case OR:
        case EQU:
        case GRT:
        case MOD:
        case RND:
            err=insbin(i,a);
            break;
        case OP:
        case INV:
        case NOT:
            err=insuni(i,a);
            break;
        case LAB:
            err=inslab(a);
            break;
        case JMP:
            err=insjmp(a);
            break;
        case IF:
            err=insif(a);
            break;
        case FI:
            err=insfi(a);
            break;
        case LOP:
            err=inslop(a);
            break;
        case POL:
            err=inspol(a);
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

static int frees() {
    int a[4]={valerr(),varerr(),prgerr(),prgexeerr()};
    int total=0;
    for(int k=0;k<4;k++) total+=a[k];
    if(total>0) printf("NO LIBERADOS Val=%i Var=%i Prg=%i Exe=%i\n",a[0],a[1],a[2],a[3]);
    return total;
}

int prgexe() {
    int err=prgmain();
    while(!endexe && !err) {
        Value a=NULL;
        err=tokexeins(&a);
        if(a) {
            valdel(&a);
            err=-17; /* si llega un valor diferente al nulo, error */
        }
    }
    prgexedel();
    prgdel();
    int ndm=frees();
    if(ndm>0) err=ndm;
    return err;
}

int prgexeerr() {
    return prcexes;
}
            

        


