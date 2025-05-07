/*
============================================================
  Fichero: memoria.c
  Creado: 30-04-2025
  Ultima Modificacion: dimecres, 7 de maig de 2025, 16:41:21
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memoria.h"

u2 VAREND=PRGINI;

static u1 memory[MEMDIM];

//macros

#define dob(A,B) ((A)+256*(B)) //pasar de dos bytes a direccion
#define mem(A) *(memory+(A))

//instruccion

void inc(u1* r1,u2* r2,u1 o1,u1 o2) {
	*r2=o1+1;
	if(*r1==0) *r2+=1;
	return (*r1==0 && *r2==0);
}

void ldb(u1 d1,u1 d2,u1 v) {
	u2 dir=dob(d1,d2);
	mem(dir)=v;
}

void ldd(u1 d1,u1 d2,u1 v1,u1 v2) {
	u2 dir=dob(d1,d2);
	mem(dir++)=v1;
	mem(dir)=v2;
}






