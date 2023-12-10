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

/***********************************************
*
* @Finalidad: Ordenar alfabeticamente un array.
* @Parametros: 	in: *c = Array de canales a ordenar.
*				in: num_peliculas = Numero de canales a ordenar.
* @Retorno: ----.
* 
************************************************/
void selectionSortPelicula (Pelicula *c, int num_peliculas);

/***********************************************
*
* @Finalidad: Leer el fichero que contiene todas las peliculas.
* @Parametros: 	in/out: *num_peliculas = Numero de peliculas.
* @Retorno: Retorna un array dinamico con todas las peliculas..
* 
************************************************/
Pelicula * leerPeliculas (int *num_peliculas);

#endif 
