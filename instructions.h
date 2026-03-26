/* LP 23-3-26 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* codigos de instrucciones */

/* main= instruccion donde marca el primer procedimiento a ejecutarse */
#define NOI 0 /* instruccion nula */
#define PGR 1 /* inicio del programa*/
#define RGP 2 /* final del programa */
#define CLL 3 /* llamada a un procedimiento */
#define PRC 4 /* inicio de procedimiento */
#define CRP 5 /* fin del procedimiento */
#define OUT 6 /* imprime el valor en el stack */
#define IN 7 /* almacena un valor en el stack */
#define NLN 8 /* salto de linea */
#define TAB 9 /* tabulacion */
#define ADD 10 /* suma */
#define OP 11 /* opuesto */
#define PRD 12 /* producto */
#define INV 13 /* inverso */
#define EQU 14 /* igualdad */
#define GRT 15 /* mayor que*/
#define LET 16 /* creacion de una variable de un nombre*/
#define SET 17 /* asignacion de un valor */
#define GET 18 /* se consigue un valor */
#define ARL 19 /* creacion de una matriz de cierta dimension */
#define ARS 20 /* se define el valor de una determinada posicion de la matriz */
#define ARG 21 /* se consigue el valor de una determinada posicion de la matriz */
#define JMP 22 /* salto hacia el label que tiene el mismo nombre */
#define LAB 23 /* label, lugar hacia donde saltara una instruccion */
#define IF 24 /* inicio del condicional */
#define FI 25 /* fin del condicional */

#define ENDINS 25 /* marca el final de las instrucciones */

/* cadenas de instrucciones*/
#define PRG "PROGRAM"
#define RGP "END_PROGRAM"
#define CLL "CALL"
#define PRC "PROCEDURE"
#define CRP "END_PROCEDURE"
#define OUT "PRINT"
#define IN "INPUT"
#define NLN "NEWLINE"
#define TAB "TAB"
#define ADD "+"
#define OP "-"
#define PRD "*"
#define INV "/"
#define EQU "="
#define GRT ">"
#define LET "LET"
#define SET "SET"
#define GET "GET"
#define ARL "ARRAY"
#define ARS "ARRAY_SET"
#define ARG "ARRAY_GET"
#define JMP "JUMP"
#define LAB "LABEL"
#define IF "IF"
#define FI "END_IF"


#define SINS (ENDINS-1) /* numero de instrucciones */

