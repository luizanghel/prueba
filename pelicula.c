#include "pelicula.h"

/***********************************************
*
* @Finalidad: Ordenar alfabeticamente un array.
* @Parametros: 	in: *c = Array de canales a ordenar.
*				in: num_peliculas = Numero de canales a ordenar.
* @Retorno: ----.
* 
************************************************/
void selectionSortPelicula (Pelicula *c, int num_peliculas) {
	Pelicula minim;
	int i, j, posminim;
		for (j = 0; j < (num_peliculas - 1); j++) {
			minim = c[j];
			posminim = j;
			for (i = j+1; i < num_peliculas; i++) {
				if (c[i].ano <= minim.ano) {
					minim = c[i];
					posminim = i;
				}
			}
			c[posminim] = c[j];
			c[j] = minim;
		}

	for (i = 0; i < num_peliculas; i++) {
		printf ("Título: %s\n", c[i].titulo);
		printf ("Director: %s\n", c[i].director);
		printf ("Categoria: %s\n", c[i].categoria);
		printf ("Año: %f\n", c[i].ano);
		printf ("Precio: %f\n", c[i].precio);
	}
}

/***********************************************
*
* @Finalidad: Leer el fichero que contiene todas las peliculas.
* @Parametros: 	in/out: *num_peliculas = Numero de peliculas.
* @Retorno: Retorna un array dinamico con todas las peliculas..
* 
************************************************/
Pelicula * leerPeliculas (int *num_peliculas) {
	FILE *f = NULL;
	Pelicula *p = NULL;
	int i = 0, j;
	char aux, usuario[MAX_CHAR_SIMPLE];

	f = fopen ("peliculas.txt", "r");
	if (f == NULL) {
		*num_peliculas = 0;
	}
	else {
		fscanf (f, "%d", num_peliculas);
		fscanf (f, "%c", &aux);
		p = (Pelicula *)malloc(sizeof(Pelicula) * (*num_peliculas));
		
		while (i < *num_peliculas) {
			fscanf (f, "%s", p[i].titulo);	
			fscanf (f, "%c", &aux);
			fscanf (f, "%s", p[i].director);	
			fscanf (f, "%c", &aux);
			fscanf (f, "%s", p[i].categoria);	
			fscanf (f, "%c", &aux);
			fscanf (f, "%f", &p[i].ano);	
			fscanf (f, "%c", &aux);
			fscanf (f, "%f", &p[i].precio);	
			fscanf (f, "%c", &aux);
			fscanf (f, "%d", &p[i].num_usuarios);
			fscanf (f, "%c", &aux);
			p[i].usuarios = (char **)malloc(sizeof(char *) * p[i].num_usuarios);
			if (p[i].usuarios == NULL) {
				printf ("\tERROR (El sistema ha caído. Contacte con un administrador en la mayor brevedad posible)\n");
			}
			else {
				for (j = 0; j < p[i].num_usuarios; j++) {
					fscanf(f, "%s", usuario);
					fscanf(f, "%c", &aux);
					p[i].usuarios[j] = (char *)malloc((strlen(usuario) + 1) * sizeof(char));
					strcpy(p[i].usuarios[j], usuario);
				}
			}
			i++;
		}
		fclose(f);
	}
	
	return p;
}

int peliculaExiste (Pelicula *p, int num_peliculas, char nombre[MAX_CHAR_SIMPLE], int *i) {
	
	*i = 0;
	while (*i < num_peliculas) {
		if (!strcmp(p[*i].titulo, nombre)) {
			return 1;
		}
		(*i)++;

	}
	
	return 0;
}

void actualizacionFicheroPeliculas (Pelicula *p, int num_peliculas) {
	FILE *f = NULL;
	int i = 0, j;

	f = fopen ("peliculas.txt", "w");
	if (f == NULL) {
		printf ("ERROR!\n");
	}
	else {
		fprintf (f, "%d\n", num_peliculas);
		while (i < num_peliculas) {
			fprintf (f, "%s\n", p[i].titulo);
			fprintf (f, "%s\n", p[i].categoria);
			fprintf (f, "%s\n", p[i].titulo);
			fprintf (f, "%f\n", p[i].ano);
			fprintf (f, "%f\n", p[i].precio);
			fprintf (f, "%d\n", p[i].num_usuarios);
			for (j = 0; j < p[i].num_usuarios; j++) {
				fprintf (f, "%s\n", p[i].usuarios[j]);
			}
			i++;
		}
		fclose(f);
	}
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
	int num_peliculas, i;
	Pelicula *pelis;

	printf ("Introduce los datos de la pelicula: \n");
	solicitarPalabra("\tNombre de la pelicula: ", p.titulo, NOMBRE);
	solicitarPalabra("\tDirector de la pelicula: ", p.director, NOMBRE);
	p.ano = solicitarFloat("\tAño de creacion: ");
	solicitarPalabra("\tCategoria de la pelicula: ", p.categoria, CATEGORIA);
	p.precio = solicitarFloat("\tPrecio de la pelicula: ");
	p.num_usuarios = 0;
	p.usuarios = NULL;

	pelis = leerPeliculas(&num_peliculas);
	if (!peliculaExiste(pelis, num_peliculas, p.titulo, &i)) {
		num_peliculas++;
		pelis = realloc(pelis, sizeof(Pelicula) * num_peliculas);
		pelis[num_peliculas - 1] = p;	
		actualizacionFicheroPeliculas(pelis, num_peliculas);
		printf ("Se ha registrado la pelicula correctamente.\n");
	}
	else {
		printf ("\tERROR (La pelicula introducida ya se encuentra registrada en la base de datos)\n");
	}
}

void listarPeliculas () {
	int i = 0, num_peliculas;
	Pelicula *pelis = NULL;

	pelis = leerPeliculas(&num_peliculas);
	while (i < num_peliculas) {
		printf ("Nombre: %s\n", pelis[i].titulo);
		printf ("Director: %s\n", pelis[i].director);
		printf ("Precio: %f\n", pelis[i].precio);
		for (int j = 0; j < pelis[i].num_usuarios; j++) {
			printf ("Nombre: %s\n", pelis[i].usuarios[j]);
		}
		i++;
	}
}

void eliminarPelicula () {
	Pelicula *pelis = NULL;
	int num_peliculas, i, eliminar;
	char nombre[MAX_CHAR_SIMPLE];
	
	pelis = leerPeliculas(&num_peliculas);
	if (num_peliculas != 0) {
		solicitarPalabra("Introduce pelicula a eliminar: ", nombre, NOMBRE);
		if (peliculaExiste(pelis, num_peliculas, nombre, &eliminar)) {
			for (i = eliminar; i < num_peliculas - 1; i++) {
        		pelis[i] = pelis[i + 1];
    		}
  		  	num_peliculas--;
    		pelis = realloc(pelis, sizeof(Pelicula) * num_peliculas);
			actualizacionFicheroPeliculas(pelis, num_peliculas);
		}
		else {
			printf ("\tERROR (La pelicula introducida no existe)\n");
		}
	}
	else {
		printf ("\tERROR (No hay peliculas registradas para eliminar)\n");
	}
}
