#ifndef _PELICULA_H_
#define _PELICULA_H_

#define MAX_CHAR_SIMPLE 100

typedef struct {
	char titulo[MAX_CHAR_SIMPLE];
	char director[MAX_CHAR_SIMPLE];
	int ano;
	char categoria[MAX_CHAR_SIMPLE];
	float precio;
} Pelicula;

#endif 
