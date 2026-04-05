/* LP 5/4/26 */

#include "program.h"

#define 

struct node_s {
    Value val;
    struct node_s* prv;
};

typedef struct node_s* Stack;

int stkpsh(Stack* s,Value v);
/* insercion de un valor en el stack */

Value stkpop(Stack* s);
/* extraccion de un valor del stack, si no existe, NULL */

void stkdel(Stack* s);
/* se libera el espacio de memoria del stack libera tambien los valores */

int stkerr();
/* numero de nodos no liberados */

struct prcexe_s {
    Token ini,act; /* describe el token inicial del procedimiento y el actual */
    Variable var;
    struct prcexe_s* prv;
};

typedef struct prcexe_s* Prgexe;

extern Prgexe execute;

int prgmain();
/* se inicia el procedimiento main, que es el primero de todos, si no esta iniciado no se podran abrir otros procedimientos*/

int tokexe(Value* a);
/* se ejecuta el token actual de procedimiento */
