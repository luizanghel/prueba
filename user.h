#ifndef _USER_H_
#define _USER_H_

// Librerias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedlist.h"
#include "canales.h"
#include "actors.h"

// Constantes 
#define MAX_CHAR_SIMPLE 100

// Tipo
typedef struct {
	int numeros;
	char letra;
} Dni;

typedef struct {
	Dni dni;
	char nombre[MAX_CHAR_SIMPLE];
	char apellido1[MAX_CHAR_SIMPLE];
	char apellido2[MAX_CHAR_SIMPLE];
	char correo[MAX_CHAR_SIMPLE];
	char password[MAX_CHAR_SIMPLE];
	int telefono;
	int tipus;			// 0-Client | 1-Productor
} Persona;

// Operaciones
Persona registerUser ();
Persona iniciarSesion ();
void modoProductor ();
void leerPersona(Persona p);

#endif
