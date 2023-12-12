#ifndef _PELICULA_H_
#define _PELICULA_H_

#include "dato.h"

typedef struct {
	char titulo[MAX_CHAR_SIMPLE];
	char director[MAX_CHAR_SIMPLE];
	float ano;
	char categoria[MAX_CHAR_SIMPLE];
	float precio;
} Pelicula;

void listarPeliculas ();

void eliminarPelicula ();
/***********************************************
*
* @Finalidad: Anadir una pelicula a la base de datos..
* @Parametros: ----.
* @Retorno: ---.
* 
************************************************/
void anadirPelicula();

#endif 
