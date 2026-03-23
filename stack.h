/* LP 17-3-26 */

#include "variable.h"

typedef unsigned char Instruction;

struct stack_s {
    union {
        Value val;
        Instruction ins;
    };
    struct stack_s* prv;
};

typedef struct stack_s* Stack;

int vspush(Stack* sval,Value val);
/* insercion de un valor en el stack de valores */

Value vspop(Stack* sval;);
/* extraccion de valores en stack de valores */

void vsdel(Stack* sval);
/* se libera espacio total del stack de valores */

int ispush(Stack* sins,Instruction ins);
/* insercion de una instruccion */

Instruction ispop(Stack* sins);
/* extraccion de una instruccion */

void isdel(Stack* sins);
/* se libera el espacio total del stack de instrucciones */

int stkerr();
/* da error si no se libera el espacio */
