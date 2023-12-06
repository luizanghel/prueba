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
* @Finalidad: Asignar el correo de un usuario como suscriptor de un canal.
* @Parametros:	in: canal[] = Nombre del canal a asignar el usuario.
*				in: usuario[] = Correo del usuario a asignar.
* @Retorno: ----.
* 
************************************************/
void asignarUsuarioACanal(char canal[MAX_CHAR_SIMPLE], char usuario[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Mostrar los canales registrados.
* @Parametros: in: canales = Lista de canales.
* @Retorno: ----.
* 
************************************************/
void mostrarCanales ();

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

/***********************************************
*
* @Finalidad: Verifica si el nombre de un canal es unico.
* @Parametros:  in: nombre[] = Nombre de canal a verificar si es unico.
*				out: *c = En caso que se detecte un canal con el nombre, lo devuelve en esta variable.
* @Retorno: ----.
* 
************************************************/
int canalUnico (char nombre[100], Canal *c);

#endif

