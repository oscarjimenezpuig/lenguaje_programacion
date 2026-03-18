/* LP 16-3-26 */

/* Una variable es un nombre (solo con caracteres minuscula) y un valor */

#include "value.h"

struct variable_s {
    Value nom, val;
    struct variable_s* nxt;
};

typedef struct variable_s* Variable;

extern Variable variable;

Variable varnew();
/* creacion de un nuevo sistema de variables */

int varset(Variable* variable,char* nom,Value val);
/* se establece un valor a una variable (si no existe, se crea) */

Value varget(Variable* variable,char* nom);
/* se busca una variable con el nom concreto */

size_t varsiz(Variable variable);
/* da el numero de variables actuales guardadas */

void vardel(Variable* variable);
/* se liberan todas la variables */

int varerr();
/* cuenta el numero de variables que se han creado */




