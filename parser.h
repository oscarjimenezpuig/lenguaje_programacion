/* LP 26-3-26 */
#include "execute.h"

/* reglas
 * Instrucciones en todo MAYUSCULAS
 * Variables empiezan en minusculas
 * Procedimientos empiezan por mayuscula y siguen en minuscula
 */

/* cadenas de instrucciones*/
#define SPRG "PROGRAM"
#define SGRP "END_PROGRAM"
#define SCLL "CALL"
#define SSPR "PROCEDURE"
#define SEPR "END_PROCEDURE"
#define SOUT "PRINT"
#define SIN "INPUT"
#define SNLN "NEW_LINE"
#define STAB "TAB"
#define SADD "ADD"
#define SOP "OP"
#define SPRD "PRD"
#define SINV "INV"
#define SEQU "EQUAL"
#define SGRT "GRT"
#define SLET "LET"
#define SSET "SET"
#define SGET "GET"
#define SARL "ALET"
#define SARS "ASET"
#define SARG "AGET"
#define SJMP "JUMP"
#define SLAB "LABEL"
#define SIF "IF"
#define SFI "END_IF"
#define SLOP "LOOP_IF"
#define SPOL "END_LOOP"
#define SREM "REM"
#define SAND "AND"
#define SOR "OR"
#define SNOT "NOT"
#define SMOV "MOVE"
#define SINC "INC"
#define SDEC "DEC"
#define SMOD "MOD"
#define SRND "RND"
#define SCLR "CLEAR"

#define INS {SPRG,SGRP,SCLL,SSPR,SEPR,SOUT,SIN,SNLN,STAB,SADD,SOP,SPRD,SINV,SEQU,SGRT,SLET,SSET,SGET,SARL,SARS,SARG,SJMP,SLAB,SIF,SFI,SLOP,SPOL,SREM,SAND,SOR,SNOT,SMOD,SRND,SCLR}

#define CSEP " ,[](){}\t" /* separadores */
#define CFIN ":\n" /* caracteres de fin de instruccion */

#define WMLEN 2048 /* maxima dimension de la palabra descargada */

int parse(char* name);
/* lee el file y crea el programa */
