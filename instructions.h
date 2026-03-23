/* LP 23-3-26 */

#include "ula.h"

/* codigos de instrucciones */

/* main= instruccion donde marca el primer procedimiento a ejecutarse */
#define MAIN 1 /* instruccion que dirige al primer procedimiento que se evaluara (valor)*/
/* procedimiento: Todo procedimiento se abre y se cierra */
#define PRST 2 /* inicio de procedimiento(valor) */
#define PREN 3 /* fin de procedimiento */
#define OUT 4 /* imprime el valor en el stack */
#define IN 5 /* almacena un valor en el stack */
#define NLN 6 /* salto de linea */
#define TAB 7 /* tabulacion */
#define ADD 8 /* suma */
#define OP 9 /* opuesto */
#define PRD 10 /* producto */
#define INV 11 /* inverso */
#define EQU 12 /* igualdad */
#define GRT 13 /* mayor que*/
#define ENDINS 14 /* marca el final de las instrucciones */
#define LET 15 /* creacion de una variable de un nombre*/
#define SET 16 /* asignacion de un valor */
#define GET 17 /* se consigue un valor */
#define DIM 18 /* creacion de una matriz de cierta dimension */
#define SETP 19 /* se define el valor de una determinada posicion de la matriz */
#define GETP 20 /* se consigue el valor de una determinada posicion de la matriz */


#define INS {MAIN,PRST,PREN,OUT,IN,NLN,TAB,ADD,OP,PRD,INV,EQU,GRT} /* matriz de codigos de instrucciones */
#define SINS (ENDINS-1) /* numero de instrucciones */

