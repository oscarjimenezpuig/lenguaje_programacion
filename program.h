/* LP 18-3-26 */

#include "ula.h"

#define SLIN 1 /* inicio de linea */
#define ELIN 2 /* final de linea */
#define SPRC 4 /* inicio de procedimiento */
#define EPRC 8 /* final de procedimiento */
#define SMAN 16 /* inicio del procedimiento principal */
#define EMAN 32 /* final procedimiento principal */
#define TVAL 64 /* valor */
#define TINS 128 /* instruccion */

typedef unsigned char Flag;

/* insercion de programa */

struct token_s {
    Flag typ;
    union {
        Value val; /* guarda valor o nombre de procedimiento */
        Instruction ins; /* guarda la instruccion */
    };
    struct token_s* nxt;
};

typedef struct token_s* Program;

extern Program program;

int toknew(unsigned char typ,...);
/* insercion de un nuevo token */

void prgprt();
/* impresion de todo el programa introducido como lista de tokens */

struct token_s* prcfnd(Value nom);
/* da puntero al inicio del procedimiento */

void prgdel();
/* libera el espacio de todo el programa */

int prgerr();
/* da el error de los tokens sin cerrar */

/* ejecucion de programa */

struct procedure_s {
    struct token_s* lin; /* puntero a la linea que se ejecuta */
    Variable var; /* variables del procedimiento */
    struct procedure_s* prv;
};

typedef struct procedure_s* Execute;

extern Execute execute;

int prcnew();




