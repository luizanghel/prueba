#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "user.h"


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
	int option, quit = 0, completado = 0;
	Persona p;
    //float presupuesto=10000;
	do {
		option = showMenu ();
		switch (option) {
			case 1:
				p = iniciarSesion(&completado);
				break;
			case 2:
				p = registerUser(&completado);
				break;
			case 3:
				quit = 1;
				printf ("¡Hasta pronto!\n");
				break;
		}
		if (completado) {
			completado = 0;
			switch(p.tipus) {
				case 0:
					// Modo cliente
					modoCliente(p);
					break;
				case 1:
					// Modo productor
					modoProductor();
					break;
			}
		}
	} while(!quit);
	
	return 0;
}
