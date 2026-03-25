/* LP 14-3-26 */

#include "stack.h"

/* OPERADORES */

int binary(Stack* stk,char op);
/* operaciones binarias: + add, * prd*/

int unary(Stack* stk,char op);
/* operaciones unarias: - op, / inv */

int comp(Staci* stk,char op);
/* comparacion = igualdad, > primero mayor que segundo */

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

int arl(Variable* var,Stack* stk);
/* creamos una matriz de valores */

int ars(Variable* var,Stack* stk);
/* asignamos el valor de una matriz en una determinada posicion */

int arg(Variable* var,Stack* stk);
/* conseguimos el valor de una determinada matriz en una posicon */




