/* LP 23-3-26 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* codigos de instrucciones */

/* main= instruccion donde marca el primer procedimiento a ejecutarse */
#define NOI 0 /* instruccion nula */
#define PGR 1 /* inicio del programa*/
#define RGP 2 /* final del programa */
#define CALL 3 /* llamada a un procedimiento */
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

#define ENDINS 12 /* marca el final de las instrucciones */

#define INS {PRG,GRP,CALL,PRC,CRP,OUT,IN,NLN,TAB,ADD,OP,PRD,INV,EQU,GRT,LET,SET,GET,ARL,ARS,ARG} /* matriz de codigos de instrucciones */
#define SINS (ENDINS-1) /* numero de instrucciones */

