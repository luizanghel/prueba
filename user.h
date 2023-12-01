#ifndef _USER_H_
#define _USER_H_

// Librerias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedlist.h"
#include "canales.h"
#include "dato.h"
#include "actors.h"
#include "linkedlistcanales.h"

// Constantes 

// Tipo
typedef struct {
	int numeros;
	char letra;
} Dni;

typedef struct {
	char titular[MAX_CHAR_SIMPLE];
	int numero;
	int pin;
} Tarjeta;

typedef struct {
	Dni dni;
	char nombre[MAX_CHAR_SIMPLE];
	char apellido1[MAX_CHAR_SIMPLE];
	char apellido2[MAX_CHAR_SIMPLE];
	char correo[MAX_CHAR_SIMPLE];
	char password[MAX_CHAR_SIMPLE];
	Tarjeta tarjeta;
	int telefono;
	int tipus;			// 0-Client | 1-Productor
} Persona;

// Operaciones
Persona registerUser ();
Persona iniciarSesion ();
void modoProductor ();
void modoCliente();


void leerPersona(Persona p);
LinkedList FicheroALista();
void mostrarLista(LinkedList l);
int revisarMedida (char palabra[MAX_CHAR_SIMPLE], int medida, int option);
int esMinuscula (char letra);
int esMajuscula (char letra);
int revisarCaracteresCorrectos (char palabra[MAX_CHAR_SIMPLE], int option);
int revisarParametrosPropias (char palabra[MAX_CHAR_SIMPLE], int tipo);
void solicitarPalabra (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE], int tipo);
int option2AsNumber (int *option, int min, int max);

#endif
