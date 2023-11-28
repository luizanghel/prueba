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

int revisarMedida (char palabra[MAX_CHAR_SIMPLE], int medida, int option);
int esMinuscula (char letra);
int esMajuscula (char letra);
int revisarCaracteresCorrectos (char palabra[MAX_CHAR_SIMPLE], int option);
int revisarParametrosPropias (char palabra[MAX_CHAR_SIMPLE], int tipo);
void solicitarPalabra (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE], int tipo);
int option2AsNumber (int *option, int min, int max);

#endif
