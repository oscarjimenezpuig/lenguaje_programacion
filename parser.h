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
#define SADD "+"
#define SOP "-"
#define SPRD "*"
#define SINV "/"
#define SEQU "="
#define SGRT ">"
#define SLET "LET"
#define SSET "SET"
#define SGET "GET"
#define SARL "ARRAY"
#define SARS "ARRAY_SET"
#define SARG "ARRAY_GET"
#define SJMP "JUMP"
#define SLAB "LABEL"
#define SIF "IF"
#define SFI "END_IF"
#define SLOP "LOOP"
#define SPOL "END_LOOP"
#define SREM "REM"

#define INS {SPRG,SGRP,SCLL,SSPR,SEPR,SOUT,SIN,SNLN,STAB,SADD,SOP,SPRD,SINV,SEQU,SGRT,SLET,SSET,SGET,SARL,SARS,SARG,SJMP,SLAB,SIF,SFI,SLOP,SPOL,SREM}

#define CSEP " ,[](){}\t" /* separadores */
#define CFIN ":\n" /* caracteres de fin de instruccion */

#define WMLEN 2048 /* maxima dimension de la palabra descargada */

int parse(char* name);
/* lee el file y crea el programa */
