/* LP 18-3-26 */

#include "variable.h"

/* program set */

struct token_s {
    struct {
        char isi : 1; /* token es instruccion */
        char isv : 1; /* token es valor */
        char ifi : 1; /* indica final de instruccion*/
    };
    union {
        Instruction ins;
        Value val;
    };
    struct token_s *prv,*nxt;
};

typedef struct token_s* Token;

typedef Token Program;

extern Program program;

int tokinsnew(Instruction ins,char ieoi);
/* token a partir de instruccion, ieoi indica si es el final de instruccion*/

int tokvalnew(char* str,char ieoi);
/* token a partir de valor, ieoi indica que es infal de instruccion */

void tokiseoi();
/* hace que el ultimo token del programa se transforme en un fin de instruccion */

void tokprt(Token token);
/* impresion de un token */

void prgprt();
/* impresion de todo el programa */

void prgdel();
/* libera el espacio del programa */

int prgerr();
/* da el nuero de tokens no liberados del programa */


