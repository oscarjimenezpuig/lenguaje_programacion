/* LP 18-3-26 */

#include "inout.h"

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

typedef struct line_s* Program;

extern Program program;

int prginslin();
/* crea una nueva linea en el programa */

int prginstok(type_e typ,...);
/* crea un nuevo token en la ultima linea definida */

void prgprt();
/* impresion del programa */

void prgdel();
/* libera el espacio del programa */





