/* LP 16-3-26 */

/* Una variable es un nombre (solo con caracteres minuscula) y un valor */

#include "ula.h"

struct variable_s {
    Value nom, val;
    struct variable_s* nxt;
};

typedef struct variable_s* Variable;

extern Variable variable;

int varset(char* nom,Value val);
/* se establece un valor a una variable (si no existe, se crea) */

Value varget(char* nom);
/* se busca una variable con el nom concreto */

void vardel();
/* se liberan todas la variables */

int varerr();
/* cuenta el numero de variables que se han creado */




