#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "user.h"

#define MAX_CHAR_SIMPLE 100

/***********************************************
*
* @Finalidad: Comprobar que los parametros introducudidos por el usuario sean correctos y se encuentren dentro del rango..
* @Parametros:	out: option = Valor de la opcion del menú a interaccionar.
*				in: min = Valor minimo permitido en el menú.
*				in: max = Valor máximo permitido en el menú.
* @Retorno: Devuelve si el numero introducido se encuentra dentro del rango o no.
* 
************************************************/
int optionAsNumber (int *option, int min, int max) {
	char option_char[MAX_CHAR_SIMPLE];
	int error = 0;

	fgets (option_char, MAX_CHAR_SIMPLE, stdin);
	option_char[strlen(option_char) - 1] = '\0';	
	*option = atoi(option_char);				
	
	if (*option < min || *option > max) {
		printf ("\n\tERROR: Debes introducir una de las opciones posibles.\n\n");
		error = 1;
	}
	return error;
}

/***********************************************
*
* @Finalitat: Mostrar menú.
* @Parametres: ----.
* @Retorn: Devuelve la opcion que el usuario ha decidido interaccionar.
* 
************************************************/
int showMenu () {
	int option, error = 0;
	
	do {
		printf ("\t1. Iniciar sessión\n");
		printf ("\t2. Registrarse\n");
		printf ("\t3. Salir\n");
		printf ("Accedir: ");
		error = optionAsNumber(&option, 1, 3);
	
	} while (error);

	return option;

}

int main () {
	int option, quit = 0;

	do {
		option = showMenu ();
		switch (option) {
			case 1:
				iniciarSesion();
				break;
			case 2:
				registerUser();
				break;
			case 3:
				quit = 1;
				printf ("¡Hasta pronto!\n");
				break;
		}

	} while(!quit);
	
	return 0;
}
