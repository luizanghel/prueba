#include "pelicula.h"

/***********************************************
*
* @Finalidad: Anadir una pelicula a la base de datos..
* @Parametros: ----.
* @Retorno: ---.
* 
************************************************/
void anadirPelicula() {
	Pelicula p;

	printf ("Introduce los datos de la pelicula: \n");
	solicitarPalabra("\tNombre de la pelicula: ", p.titulo, NOMBRE);
	solicitarPalabra("\tDirector de la pelicula: ", p.director, NOMBRE);
	p.ano = solicitarFloat("\tAño de creacion: ");
	solicitarPalabra("\tCategoria de la pelicula: ", p.categoria, CATEGORIA);
	p.precio = solicitarFloat("\tPrecio de la pelicula: ");
}
