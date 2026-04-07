/* LP 5/4/26 */

#include "program.h"

struct prcexe_s {
    Token ini,act; /* describe el token inicial del procedimiento y el actual */
    Variable var;
    struct prcexe_s* prv;
};

typedef struct prcexe_s* Prgexe;

extern Prgexe execute;

int prgexe();
/* se ejecuta el programa */

int prgexeerr();
/* devuelve el numero de procedimientos no cerrados */
