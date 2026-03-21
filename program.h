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

struct procedure_s {
    Value nom;
    struct line_s* lin;
    struct procedure_s* nxt;
};

typedef struct {
    struct procedure_s* prc;
    struct procedure_s* frs;
} Program;

extern Program program;

int prgprcmain(Value nom);
/* establece, de todos los procedimientos quien es el main */

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

int prgexe();
/* ejecucion del programa */
/* un programa se ejecuta leyendo toda la linea y poniendo los valores en el 
 * stack de valores y las instrucciones en el stack de instrucciones */ 

void prgdel();
/* libera el espacio del programa */







