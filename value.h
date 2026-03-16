/* LP 14-3-26 */

/* Un valor es una cadena de caracteres donde se guardan dos caracters por byte */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define EOS '\0' /* indicativo del final de string */

#define VALNUL "" /* valor nulo de los valores */ 

typedef char* Value;

Value valnew(char tip_num,...);
/* se crea un valor nuevo a partir de un tipo numerico o un string */

Value valcpy(Value val);
/* copia un valor en otro */

void valdel(Value* val);
/* se libera el valor */

double valtonum(Value val);
/* se transforma el valor en un numero (si lo es, si no devuelve 0) */

int valisfalse(Value val);
/* devuelve 1 si el valor es falso (un solo caracter que es el 0) */

int valerr();
/* control del error de valores para ver si estan destruidos (devuelve 0 si todo correcto) */
