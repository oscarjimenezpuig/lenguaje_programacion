/* LP 18-3-26 */

#include "variable.h"

/* program set */

struct token_s {
    struct {
        char isi : 1;
        char isv : 1;
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

int tokinsnew(Instruction i);
/* crea un nuevo token instruccion y lo añade al programa */

int tokvalnew(char* str);
/* crea un token valor a partir de la cadena */

void tokprt(Token token);
/* impresion de un token */

void prgprt();
/* impresion de todo el programa */

void prgdel();
/* libera el espacio del programa */

int prgerr();
/* da el nuero de tokens no liberados del programa */


