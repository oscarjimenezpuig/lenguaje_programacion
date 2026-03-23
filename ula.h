/* LP 14-3-26 */

#include "stack.h"

/* OPERADORES */

int ulaadd(Stack* stk);
/* suma */

int ulaop(Stack* stk);
/* opuesto */

int ulaprd(Stack* stk);
/* producto */

int ulainv(Stack* stk); 
/* inverso */

/* devolucion de valores booleanos */

int ulaequ(Stack* stk);
/* igualdad entre dos valores, devuelve valor booleano */

int ulagrt(Stack* stk);
/* dice si a mayor que b (punto de vista numerico) */

/* INOUT */

#define INSTLEN 256 /* longitud maxima de la entrada por teclado */
#define TABSPC 3 /* numero de espacios que representa una tabulacion */

int out(Stack* stk);
/* impresion de un valor que esta en el stack */

int in(Stack* stk);
/* entrada de un valor que se deposita en el stack */

void nln();
/* nueva linea */

void tab();
/* tabulacion */

/* VARIABLES */

int let(Variable* var,Stack* stk);
/* se crea una nueva variable */

int set(Variable* var,Stack* stk);
/* se le asigna a una variable un valor */

int get(Variable* var,Stack* stk);
/* conseguimos el valor de una variable */

int dim(Variable* var,Stack* stk);
/* creamos una matriz de valores */

int setp(Variable* var,Stack* stk);
/* asignamos el valor de una matriz en una determinada posicion */

int getp(Variable* var,Stack* stk);
/* conseguimos el valor de una determinada matriz en una posicon */




