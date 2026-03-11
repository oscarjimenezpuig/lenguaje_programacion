/* LP 10-3-26 */

/* Memoria funciona como un bloque de caracteres donde se guardan numeros y palabras en forma de caracter */
/* En cada bit se guardan dos caracteres */
/* Cada nuevo valor ira en el inicio de un bloque */

#include <stdio.h>

#define MEMSIZ 1024
/* numero de bytes de la memoria */

#define EOV 0
/* caracter que indica el fin de la memoria */

typedef unsigned short Dir; 
/* direccion de la memoria */

Dir memoset(Dir d,char* value);
/* se copia un valor en la direccion y devuelve la siguiente direccion */

int memoget(Dir d,char* value);
/* se consigue el valor almacenado y se almacena en value */

void memoprt();
/* se imprime la memoria a pares */
