/* LP 16-3-26 */

/* Una variable es un nombre (solo con caracteres minuscula) y un valor */

#include "value.h"

struct variable_s {
    Value nom, val;
    struct variable_s* nxt;
};

typedef struct variable_s* Variable;

extern Variable variable;

Variable varsnew();
/* creacion de un nuevo sistema de variables */

size_t varssiz(Variable variable);
/* da la dimension del varsis */

void varsdel(Variable* variable);
/* se liberan todas la variables */

int varnew(Variable* variable,char* nom,unsigned int dim);
/* creacion de una nueva variable de dimension dim */

int varset(Variable* variable,char* nom,unsigned int pos,Value val);
/* a una determinada variable en una determinada posicion asignamos un valor */ 

Value varget(Variable* variable,char* nom,unsigned int pos);
/* se busca una variable con el nombre y la posicion concreta */

int varerr();
/* cuenta el numero de variables que se han creado */




