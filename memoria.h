/*
============================================================
  Fichero: memoria.h
  Creado: 30-04-2025
  Ultima Modificacion: dimecres, 7 de maig de 2025, 16:36:46
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

//flags
#define FZER 1 //se conecta si tras operacion el resultado es 0
#define FNEG 2 //se conecta si el resultado de operacion es negativo
#define FCRR 4 //se conecta si hay bit de acarreo despues de operacion
#define FAUE 8 //flags auxiliares
#define FAUD 16
#define FAUC 32
#define FAUB 64
#define FAUA 128

//dimensiones
#define MEMDIM 65536 //dimension de la memoria
#define STBDIM 1024 //dimension del stack de bytes
#define STDDIM (STBDIM*2) //dimension del stack de direcciones
#define CICDIM 4 //numero de bytes destinados a contar los ciclos
#define INPDIM 1024 //dimension del input
#define OUTDIM 1024 //dimension del output

//distribucion memoria
#define INTREG 0 //inicio registros
#define RA INTREG //
#define RB (RA+1)
#define RR (RB+1)
#define RP (RR+1)
#define RS (RP+2)
#define RF (RS+2)
#define ENDREG (RF+1) //final registros
#define INTSTB ENDREG //inicio stack de bytes
#define STBPTR INTSTB //puntero del stack
#define STBFRT (STBPTR+2) //inicio del stack de bytes
#define ENDSTB (STBFRT+STBDIM) //final (no contemplado) del stack de bytes
#define INTSTD  ENDSTB //inicio del stack de direcciones
#define STDPTR INTSTD //puntero del stack de direcciones
#define STDFRT (STDPTR+2) //inicio del stack de direcciones
#define ENDSTD (STDFRT+STDDIM) //final (no contemplado) del stack de direcciones
#define CICCNT ENDSTD //contador de ciclos
#define INOUTINIT (CICCNT+CICDIM) //inicio del input/output
#define INPUT INOUTINIT //input
#define OUTPUT (INPUT+INPDIM) //output
#define INOUTEND (OUTPUT+OUTDIM) //final del input/output
#define PGRINIT INOUTEND //inicio del programa
#define PGRPTR PGRINIT //direccion que se trata en el programa
#define PGRFL //primera linea del programa
#define VARINIT (MEMDIM-1) //primera linea de variables

//instrucciones
#define NUL 0 //instruccion que no hace nada
#define LDB 1 //cargar una direccion con un byte (u2,u1)
#define LDD 2 //cargar una direccion con una direccion (u2,u2)
#define MVL 3 //copiar el contenido de una direccion a otra (u2,u2)
#define MVD 4 //copiar en una direccion el contenido de la direccion destino (u2,u2)
#define MVP 5 //copiar en una direccion el contenido de la direccion de la principal (u2)
#define JNC 6 //salto no condicional (u2)
#define JCP 7 //salto de condicion positiva (u1,u2) (el primero se refiere al flag)
#define JCN 8 //salto de condicion negativa (u1,u2)
#define ADD 9 //suma de los registros
#define SUB 10 //resta de los registros
#define AND 11 //and entre registros
#define OR 12 //or entre registros 
#define XOR 13 //xor entre registros
#define NOT 14 //not del registro A
#define INC 15 //incremento de la direccion principal
#define DEC 16 //decremento de la direccion principal
#define PSB 17 //push de bytes del registro A
#define PPB 18 //pop de bytes a registro S
#define PSD 19 //push de direcciones del registro principal
#define PPD 20 //pop de direcciones, se guarda en el principal
#define SWB 21 //swap entre direcciones (un byte) (u2,u2)
#define SWD 22 //swap entre direcciones (dos bytes) (u2,u2)

//tipos
typedef unsigned char u1;
typedef unsigned short u2;

//variables
extern u2 VAREND; //ultima linea de las variables

//funciones
void memprt(u2 init,u2 end);
//impresion de la memoria entre dos direcciones





