#ifndef CANALES_H
#define CANALES_H

#include "actors.h"
#include "linkedlistcanales.h"
#include "linkedlistprograma.h"
#include "dato.h"

void menuCanales();
int assignarAlPrograma(int numero, char letra);
LinkedList4 programaFileToList ();
void actualizarFicheroPrograma (LinkedList4 programas);
LinkedList3 canalesFileToList (int *numero);

/***********************************************
*
* @Finalidad: Generar una estructura dinamica con todos los canales.
* @Parametros: in/out = *num_canales = Numero de canales existentes en el sistema.
* @Retorno: Retorna un array dinamico de todos los canales.
* 
************************************************/
Canal * listaAArrayDinamico (int *num_canales);

/***********************************************
*
* @Finalidad: Ordenar alfabeticamente un array.
* @Parametros: 	in: *c = Array de canales a ordenar.
*				in: num_canales = Numero de canales a ordenar.
* @Retorno: ----.
* 
************************************************/
void selectionSort (Canal *c, int num_canales);

#endif

