#ifndef _PELICULA_H_
#define _PELICULA_H_

#include "dato.h"

typedef struct {
	char titulo[MAX_CHAR_SIMPLE];
	char director[MAX_CHAR_SIMPLE];
	float ano;
	char categoria[MAX_CHAR_SIMPLE];
	float precio;
	int num_usuarios;
	char **usuarios;
} Pelicula;

void listarPeliculas ();

/***********************************************
*
* @Finalidad: Asignar un usuario como comprador de una pelicula.
* @Parametros: 	in: posicion = Posicion, en el array de peliculas, donde se asignara el usuario.
*				in: correo[] = Correo del usuario (identificador unico), que sera el dato asignado a la pelicula.
* @Retorno: ----.
* 
************************************************/
void asignarUsuarioAPelicula (int posicion, char correo[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Dado un nombre de pelicula, verifica si esta se encuentra registrada.
* @Parametros: 	in: *p = Array dinamico de peliculas a verificar.
*				in: num_peliculas = Numero de peliculas que se encuentran en el array *p.
*				in: nombre[] = Nombre de la pelicula a comprobar si ya se encuentra en la base de datos.
*				in/out: Posicion de la pelicula dentro del array, en caso que se encuentre.
* @Retorno: Retorna un array dinamico con todas las peliculas..
* 
************************************************/
int peliculaExiste (Pelicula *p, int num_peliculas, char nombre[MAX_CHAR_SIMPLE], int *i);

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
