/* LP 18-3-26 */

#include "inout.h"

/* codigos de instrucciones */

/* main= instruccion donde marca el primer procedimiento a ejecutarse */
#define MAIN 1 /* instruccion que dirige al primer procedimiento que se evaluara (valor)*/
/* procedimiento: Todo procedimiento se abre y se cierra */
#define PRST 2 /* inicio de procedimiento(valor) */
#define PREN 3 /* fin de procedimiento */

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

int prgexe();
/* ejecucion del programa */
/* un programa se ejecuta leyendo toda la linea y poniendo los valores en el 
 * stack de valores y las instrucciones en el stack de instrucciones */ 

void prgprt();
/* impresion del programa */

void prgdel();
/* libera el espacio del programa */







