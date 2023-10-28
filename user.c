#include <stdio.h>

#include "user.h"

/***********************************************
*
* @Finalidad: Solicitar una palabra.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: ----.
* 
************************************************/
void solicitarPalabra (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]) {
	printf ("%s", texto);
	fgets(palabra, MAX_CHAR_SIMPLE, stdin);
	palabra[strlen(palabra) - 1] = '\0';
}

/***********************************************
*
* @Finalidad: Solicitar un DNI.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
* @Retorno: Devuelve el conjunto del DNI.
* 
************************************************/
Dni solicitarDni (char texto[MAX_CHAR_SIMPLE]) {
	char palabra[MAX_CHAR_SIMPLE];
	Dni dni;
	
	printf ("%s", texto);
	fgets(palabra, MAX_CHAR_SIMPLE, stdin);
	palabra[strlen(palabra) - 1] = '\0';
	
	dni.numeros = 0;
	dni.letra = 'C';

	return dni;
}

/***********************************************
*
* @Finalidad: Solicitar un correo.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve el conjunto del DNI.
* 
************************************************/
void solicitarCorreo (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]) {
	printf ("%s", texto);
	fgets(palabra, MAX_CHAR_SIMPLE, stdin);
	palabra[strlen(palabra) - 1] = '\0';
}

/***********************************************
*
* @Finalidad: Solicitar una contraseña.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve la contraseña.
* 
************************************************/
void solicitarContrasena (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]) {
	printf ("%s", texto);
	fgets(palabra, MAX_CHAR_SIMPLE, stdin);
	palabra[strlen(palabra) - 1] = '\0';
}

/***********************************************
*
* @Finalidad: Solicitar un telefono.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve el telefono.
* 
************************************************/
int solicitarTelefono (char texto[MAX_CHAR_SIMPLE]) {
	int telefono;
	char aux;

	printf ("%s", texto);
	scanf("%d", &telefono);
	scanf ("%c", &aux);

	return telefono;
}

/***********************************************
*
* @Finalidad: Solicitar los campos para poder iniciar el registro de un usuario.
* @Parametros: ----.
* @Retorno: Devuelve un tipo persona con los campos rellenados.
* 
************************************************/
Persona requestData () {
	Persona p;

	printf ("Registro: Rellena todos los campos que aparecen a continuación:\n");
	solicitarPalabra("Nombre: ", p.nombre);
	solicitarPalabra("Primer apellido: ", p.apellido1);
	solicitarPalabra("Segundo apellido: ", p.apellido2);
	p.dni = solicitarDni("DNI: ");
	solicitarCorreo("Correo: ", p.correo);
	solicitarContrasena("Contraseña: ", p.password);
	p.telefono = solicitarTelefono("Numero de telefono: ");
	
	return p;
}

/***********************************************
*
* @Finalidad: Leer el contenido del tipo persona.
* @Parametros: in: p = Tipo persona completo.
* @Retorno: Muestra por pantalla el contenido del tipo persona.
* 
************************************************/
void leerPersona (Persona p) {
	printf("Nombre: %s.\n", p.nombre);
	printf("Nombre: %s.\n", p.apellido1);
	printf("Nombre: %s.\n", p.apellido2);
	printf("Nombre: %s.\n", p.correo);
	printf("Nombre: %s.\n", p.password);
	printf("Nombre: %d.\n", p.telefono);
	printf("DNI: .%d.%c.\n", p.dni.numeros, p.dni.letra);
}


/***********************************************
*
* @Finalidad: Solicita los datos del usuario para proceder con el registro..
* @Parametros: ----.
* @Retorno: ----.
* 
************************************************/
void registerUser () {
	Persona p;

	p = requestData();
	leerPersona(p);
}
