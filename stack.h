/* LP 17-3-26 */

#include "variable.h"

#define INSNUL 0 /* instruccion nula */

typedef unsigned char Instruction;

int vspush(Value val);
/* insercion de un valor en el stack de valores */

Value vspop();
/* extraccion de valores en stack de valores */

void vsdel();
/* se libera espacio total del stack de valores */

int ispush(Instruction ins);
/* insercion de una instruccion */

Instruction ispop();
/* extraccion de una instruccion */

void isdel();
/* se libera el espacio total del stack de instrucciones */

int stkerr();
/* da error si no se libera el espacio */
