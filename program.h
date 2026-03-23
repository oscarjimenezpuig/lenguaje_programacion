/* LP 18-3-26 */

#include "ula.h"

/* INSERCION */

typedef enum {TINS,TVAL} type_e;

struct token_s {
    type_e typ;
    union {
        Instruction ins;
        Value val;
    };
    struct token_s* nxt;
};

struct line_s {
    struct token_s* tok;
    struct line_s* nxt;
};

struct procedure_s {
    Value nom;
    struct line_s* lin;
    struct procedure_s* nxt;
};

typedef struct {
    struct procedure_s* prc;
    struct procedure_s* zer;
} Program;

extern Program program;

/* el procedimiento zero es el procedimiento publico */

int prgprczernew();
/* establece el procedimiento zero y lo pone como actual*/

int prgprczerend();
/* finalizacion del procedimiento zero y final de programa */

int prgprcnew(Value nom);
/* se crea un nuevo procedimiento con el nombre concreto */

int prgprcend();
/* finaliza el procedimiento actual, necesario para establecer uno nuevo */

int prglinnew();
/* se crea una nueva linea en el procedimiento */

int prglinend();
/* cierra una linea, necesario para abrir otra */

int prgtoknew(type_e typ,...);
/* se crea un nuevo token, del tipo valor o instruccion */

void prgprt();
/* impresion del programa */

void prgdel();
/* libera el espacio del programa */

/* EJECUCION */

struct prcexe_s {
    struct procedure_s* prc; /* procedimiento que se ejecuta */
    struct line_s* lin; /* linea que se ejecuta del procedimiento */
    Variable var;
    Stack sval;
    Stack sins;
    struct prcexe_s* prv;
};

struct prgexe_s {
    Variable var;
    struct prcexe_s* zex;
    struct prcexe_s* pex;
};

extern struct prgexe_s prgexe;

int prgexe();
/* ejecucion del programa */
/* un programa se ejecuta leyendo toda la linea y poniendo los valores en el 
 * stack de valores y las instrucciones en el stack de instrucciones */ 








