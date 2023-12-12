#include "pelicula.h"

Pelicula * leerPeliculas (int *num_peliculas) {
	FILE *f = NULL;
	Pelicula *p = NULL;
	int i = 0;

	f = fopen ("peliculas.txt", "r");
	if (f == NULL) {
		*num_peliculas = 0;
	}
	else {
		fscanf (f, "%d", num_peliculas);
		p = (Pelicula *)malloc(sizeof(Pelicula) * (*num_peliculas));
		
		while (i < *num_peliculas) {
			fscanf (f, "%s", p[i].titulo);	
			fscanf (f, "%s", p[i].director);	
			fscanf (f, "%s", p[i].categoria);	
			fscanf (f, "%f", &p[i].ano);	
			fscanf (f, "%f", &p[i].precio);	
			i++;
		}
	}
	
	return p;
}

int peliculaExiste (Pelicula *p, int num_peliculas, char nombre[MAX_CHAR_SIMPLE]) {
	int i = 0, found = 0;
	
	while (i < num_peliculas) {
		if (!strcmp(p[i].titulo, p->titulo)) {
			found = 1;
		}
		i++;
	}
	
	return found;
}

/***********************************************
*
* @Finalidad: Anadir una pelicula a la base de datos..
* @Parametros: ----.
* @Retorno: ---.
* 
************************************************/
void anadirPelicula() {
	Pelicula p;
	int num_peliculas;
	Pelicula *pelis;

	printf ("Introduce los datos de la pelicula: \n");
	solicitarPalabra("\tNombre de la pelicula: ", p.titulo, NOMBRE);
	solicitarPalabra("\tDirector de la pelicula: ", p.director, NOMBRE);
	p.ano = solicitarFloat("\tAño de creacion: ");
	solicitarPalabra("\tCategoria de la pelicula: ", p.categoria, CATEGORIA);
	p.precio = solicitarFloat("\tPrecio de la pelicula: ");

	pelis = leerPeliculas(&num_peliculas);
	
	if (!peliculaExiste(pelis, num_peliculas, p.titulo)) {
		num_peliculas++;
		pelis = realloc(pelis, sizeof(Pelicula) * num_peliculas);
		pelis[num_peliculas - 1] = p;	
	}
	printf ("Peliculas: %s\n", pelis[0].titulo);
}
