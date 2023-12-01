#include <string.h>
#include <stdio.h>


#include "canales.h"

#define MAX_CHAR_SIMPLE 	  200
#define MAX_ACTORES_PROGRAMA	3

/***********************************************
*
* @Finalidad: Actualizar 'canales.txt' para que se encuentren todos los canales registrados.
* @Parametros: in: canal = LinkedList de canales.
* @Retorno: ----.
* 
************************************************/
void actualizarFicheroCanales (LinkedList3 canal) {
	FILE *actualizado = NULL;
	Canal c;

	actualizado = fopen("nuevo.txt", "w");
	if (actualizado == NULL) {
		printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
	}
	else {
		LINKEDLISTCANALES_goToHead(&canal);
		while (!LINKEDLISTCANALES_isAtEnd(canal)) {
			c = LINKEDLISTCANALES_get(&canal);
			fprintf(actualizado, "%s\n", c.nombre);
	   		fprintf(actualizado, "%f\n", c.coste_suscripcion);
			LINKEDLISTCANALES_next(&canal);
		}
		fclose(actualizado);
		remove("canales.txt");
		rename("nuevo.txt", "canales.txt");
	}
}

/***********************************************
*
* @Finalidad: Solicitar campos relevantes al usuario para la creacion del canal.
* @Parametros: ----.
* @Retorno: Retorna una estructura de tipo canal, con los datos introducidos por el usuario.
* 
************************************************/
Canal solicitarDatosCanal () {
	Canal c;

	printf ("Entra nombre canal: ");
	scanf ("%s", c.nombre);

	printf ("Entra coste suscripcion: ");
	scanf ("%f", &c.coste_suscripcion);
		
	return c;
}


/***********************************************
*
* @Finalidad: Mostrar todos los programas.
* @Parametros: in: programa = LinkedList de programas a mostrar.
* @Retorno: ----.
* 
************************************************/
void mostraProgramas (LinkedList4 programa) {
	Programa p;

	LINKEDLISTPROGRAMA_goToHead(&programa);
	while (!LINKEDLISTPROGRAMA_isAtEnd(programa)) {
		p = LINKEDLISTPROGRAMA_get(&programa);
		printf ("Nombre: %s\n", p.nom);
		printf ("Canal: %s\n", p.cadena);
		printf ("Categoria: %s\n", p.categoria);
		printf ("Emision: %s\n", p.emisio);
		for (int i = 0; i <3; i++) {
			printf ("Actor -> [Numero: %d.] | [Letra: %c.]\n", p.actorID[i].num, p.actorID[i].letra);
		}
		LINKEDLISTPROGRAMA_next(&programa);
	}
}

/***********************************************
*
* @Finalidad: Mostrar todos los programas.
* @Parametros: ----.
* @Retorno: Retorna una linkedlist con todos los programas registrados.
* 
************************************************/
LinkedList4 programaFileToList () {
	FILE *f = NULL;
	LinkedList4 lista;
	Programa p;
	char aux;

	f = fopen ("programas.txt", "r");
	if (f == NULL) {
		printf ("Error!\n");
	}
	else {
		lista = LINKEDLISTPROGRAMA_create();
		fgets(p.cadena, MAX_CHAR_SIMPLE, f);
		while (!feof(f)) {
			p.cadena[strlen(p.cadena) - 1] = '\0';
			fgets(p.nom, MAX_CHAR_SIMPLE, f);
			p.nom[strlen(p.nom) - 1] = '\0';
			fgets(p.categoria, MAX_CHAR_SIMPLE, f);
			p.categoria[strlen(p.categoria) - 1] = '\0';
			fgets(p.emisio, MAX_CHAR_SIMPLE, f);
			p.emisio[strlen(p.emisio) - 1] = '\0';
			fscanf(f, "%d", &p.duracio);
			fscanf (f, "%c", &aux);
				
			// Actores asignados
			for (int i = 0; i < 3; i++) {
				fscanf(f, "%d", &p.actorID[i].num);
				fscanf(f, "%c", &p.actorID[i].letra);	// Enter
				fscanf (f, "%c", &aux);
			}
			LINKEDLISTPROGRAMA_add(&lista, p);
			fgets(p.cadena, MAX_CHAR_SIMPLE, f);
		}
		fclose(f);
	}

	return lista;
}

/***********************************************
*
* @Finalidad: Mostrar los canales con sus respectivos programas.
* @Parametros: in: canales = Lista con todos los canales, que incluyen sus programas.
* @Retorno: ----.
* 
************************************************/
void leerCanalesYProgramas (LinkedList3 canales) {
	Programa p;
	Canal c;

	LINKEDLISTCANALES_goToHead(&canales);
	while (!LINKEDLISTCANALES_isAtEnd(canales)) {
		c = LINKEDLISTCANALES_get(&canales);
		printf ("Nombre: %s\n", c.nombre);
		printf ("Coste suscripcion: %f\n", c.coste_suscripcion);
		LINKEDLISTPROGRAMA_goToHead(&c.programas);
		while (!LINKEDLISTPROGRAMA_isAtEnd(c.programas)) {
			p = LINKEDLISTPROGRAMA_get(&c.programas);
			printf ("Nombre programa: %s\n", p.nom);
			LINKEDLISTPROGRAMA_next(&c.programas);
		}
		LINKEDLISTCANALES_next(&canales);
	}
}

/***********************************************
*
* @Finalidad: Crear una estructura, mediante listas, de los canales y programas..
* @Parametros: ----.
* @Retorno: Retorna una lista con todos los canales y programas.
* 
************************************************/
LinkedList3 canalesFileToList (int *num_canales) {
	FILE *f = NULL;
	Canal c;
	LinkedList3 canales;
	char aux;
	LinkedList4 programas;
	Programa p;
	
	*num_canales = 0;

	f = fopen ("canales.txt", "r");
	if (f == NULL) {
		printf ("ERROR\n");
	}
	else {
		programas = programaFileToList();
		canales = LINKEDLISTCANALES_create();
		fgets(c.nombre, MAX_CHAR_SIMPLE, f);
		while (!feof(f)) {
			c.nombre[strlen(c.nombre) - 1] = '\0';
			fscanf(f, "%f", &c.coste_suscripcion);
			fscanf(f, "%c", &aux);
			c.programas = LINKEDLISTPROGRAMA_create();
			(*num_canales)++;
			LINKEDLISTPROGRAMA_goToHead(&programas);
			while (!LINKEDLISTPROGRAMA_isAtEnd(programas)) {
				p = LINKEDLISTPROGRAMA_get(&programas);
				if (!strcmp(p.cadena, c.nombre)) {
					LINKEDLISTPROGRAMA_add(&c.programas, p);
				}
				LINKEDLISTPROGRAMA_next(&programas);
			}

			LINKEDLISTCANALES_add(&canales, c);
			fgets(c.nombre, MAX_CHAR_SIMPLE, f);
		}
		LINKEDLISTPROGRAMA_destroy(&programas);
	}

	return canales;
}



/***********************************************
*
* @Finalidad: Solicitar los datos necesarios para el registro de un programa nuevo.
* @Parametros: ----.
* @Retorno: Retorna una estructura programa con los datos introducidos por el usuario.
* 
************************************************/
Programa solicitarDatosPrograma () {
	Programa p;

	solicitarPalabra("\tIntroduce nombre del programa: ", p.nom, 0);
	solicitarPalabra("\tIntroduce cadena del programa: ", p.cadena, 0);
	solicitarPalabra("\tIntroduce categoria del programa: ", p.categoria, 0);
	solicitarPalabra("\tIntroduce hora emision del programa: ", p.emisio, 0);
	p.duracio = solicitarFloat("\tIntroduce duracion del programa: ");
	
	return p;
}

/***********************************************
*
* @Finalidad: Plasmar la lista en un documento 'programas.txt'.
* @Parametros: in: programas = Lista de programas.
* @Retorno: ----.
* 
************************************************/
void actualizarFicheroPrograma (LinkedList4 programas) {
	FILE *cambio = NULL;
	Programa p;

	cambio = fopen("nuevo.txt", "a");
	if (cambio == NULL) {
		printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
	}
	else {
		LINKEDLISTPROGRAMA_goToHead(&programas);
		while (!LINKEDLISTPROGRAMA_isAtEnd(programas)) {
			p = LINKEDLISTPROGRAMA_get(&programas);
			fprintf(cambio, "%s\n", p.cadena);
	   		fprintf(cambio, "%s\n", p.nom);
	   		fprintf(cambio, "%s\n", p.categoria);
		 	fprintf(cambio, "%s\n", p.emisio);
	   		fprintf(cambio, "%d\n", p.duracio);
			
			for (int i = 0; i < 3; i++) {
				fprintf(cambio, "%d%c\n", p.actorID[i].num, p.actorID[i].letra);
			}
			LINKEDLISTPROGRAMA_next(&programas);
		}
		fclose(cambio);
		remove("programas.txt");
		rename("nuevo.txt", "programas.txt");	
	}

}

/***********************************************
*
* @Finalidad: Mostrar de canales para los productores.
* @Parametros: ----.
* @Retorno: Retorna la opcion seleccionada por el usuario.
* 
************************************************/
int mostrarMenuCanales () {
	int option;
	char aux;
	
	printf ("\t1- Crear nuevo canal\n");
	printf ("\t2- Modificar canal\n");
	printf ("\t3- Eliminar canal\n");
	printf ("\t4- Mostrar canales\n");
	printf ("\t5- Añadir programa\n");
	printf ("\t6- Mostrar programas\n");
	printf ("\t7- Salir\n");
	printf ("\tEnter option: ");
	scanf ("%d", &option);
	scanf ("%c", &aux);

	return option;
}

/***********************************************
*
* @Finalidad: Mostrar los canales registrados.
* @Parametros: in: canales = Lista de canales.
* @Retorno: ----.
* 
************************************************/
void mostrarCanales (LinkedList3 canales) {
	Canal c;

	LINKEDLISTCANALES_goToHead(&canales);
	while (!LINKEDLISTCANALES_isAtEnd(canales)) {
		c = LINKEDLISTCANALES_get(&canales);	
		printf ("Nombre canal: %s\n", c.nombre);
		printf ("Coste suscripcion: %f€\n", c.coste_suscripcion);
		printf ("Coste empresa: %f€\n", 2 *c.coste_suscripcion);
		LINKEDLISTCANALES_next(&canales);
	}	

}

/***********************************************
*
* @Finalidad: Verifica si el nombre de un canal es unico.
* @Parametros:  in: nombre[] = Nombre de canal a verificar si es unico.
*				out: *c = En caso que se detecte un canal con el nombre, lo devuelve en esta variable.
* @Retorno: ----.
* 
************************************************/
int canalUnico (char nombre[100], Canal *c) {
	LinkedList3 canales;
	int found;

	canales = canalesFileToList(&found);
	found = 0;
	LINKEDLISTCANALES_goToHead(&canales);
	while (!LINKEDLISTCANALES_isAtEnd(canales) && !found) {
		*c = LINKEDLISTCANALES_get(&canales);
		if (!strcmp(c->nombre, nombre)) {
			found = 1;
		}
		LINKEDLISTCANALES_next(&canales);
	}

	return found;
}

/***********************************************
*
* @Finalidad: Verificar si el nombre de un canal es unico.
* @Parametros: in: nombre[] = Nombre a verificar.
* @Retorno: Retorna un 1 en caso que el nombre sea unico y un 0 en caso que no..
* 
************************************************/
int nombreUnico (char nombre[100], Programa *p) {
	int found = 0;
	LinkedList3 canales;
	Canal c;

	canales = canalesFileToList(&found);
	found = 0;
	LINKEDLISTCANALES_goToHead(&canales);
	while (!LINKEDLISTCANALES_isAtEnd(canales)) {
		c = LINKEDLISTCANALES_get(&canales);	
		LINKEDLISTPROGRAMA_goToHead(&c.programas);
		while (!LINKEDLISTPROGRAMA_isAtEnd(c.programas) && !found) {
			*p = LINKEDLISTPROGRAMA_get(&c.programas);
			if (!strcmp(p->nom, nombre)) {
				found = 1;
			}
			else {
				LINKEDLISTPROGRAMA_next(&c.programas);
			}
		}
		LINKEDLISTCANALES_next(&canales);
	}

	return !found;
}

/***********************************************
*
* @Finalidad: Verificar si un programa puede contratar a mas actores.
* @Parametros:  in: *p = Estructura programa a verificar.
*				out: *posicion = Posicion libre para contratar.
* @Retorno: Retorna si hay espacio o no.
* 
************************************************/
int espacioDisponible(Programa *p, int *posicion) {
	int found = 0, i;
	
	for (i = 0; i < MAX_ACTORES_PROGRAMA && !found; i++) {
		if (p->actorID[i].num == 0) {
			found = 1;
			*posicion = i;
		}
	}

	return found;

}

/***********************************************
*
* @Finalidad: Asignar, si el nombre existe, hay espacio (<3) y se introduce un identificador de actor valido, a un programa.
* @Parametros: in: nombre[] = Nombre a verificar.ç+
* @Retorno: Retorna un 1 en caso que el nombre sea unico y un 0 en caso que no.
* 
************************************************/
int assignarAlPrograma(int numeros, char letra) {
	char nombre[MAX_CHAR_SIMPLE];
	Programa p;
	int correcto = 0, posicion;
	LinkedList4 programas;
	
	printf ("Introduce nombre de programa: ");
	scanf ("%s", nombre);
	programas = programaFileToList();
	LINKEDLISTPROGRAMA_goToHead(&programas);
	while (!LINKEDLISTPROGRAMA_isAtEnd(programas)) {
		p = LINKEDLISTPROGRAMA_get(&programas);
		if (!strcmp(p.nom, nombre)) {
			if (espacioDisponible(&p, &posicion)) {
				p.actorID[posicion].num = numeros;
				p.actorID[posicion].letra = letra;
				LINKEDLISTPROGRAMA_remove(&programas);
				LINKEDLISTPROGRAMA_add(&programas, p);
				actualizarFicheroPrograma(programas);
				printf ("Se ha asignado correctamente\n");
				correcto = 1;
			}
			else {
				printf ("\tERROR (El programa tiene el maximo de actores contratados (%d))\n", MAX_ACTORES_PROGRAMA);
			}
		}
		LINKEDLISTPROGRAMA_next(&programas);
	}

	return correcto;
}


/***********************************************
*
* @Finalidad: Añadir un programa a un canal.
* @Parametros: in: canales = Lista que engloba todos los canales y programas registrados.
* @Retorno: ----.
* 
************************************************/
void anadirProgramaACanal (LinkedList3 * canales) {
	Canal c;
	Programa p, aux; 
	LinkedList4 programa;

	p = solicitarDatosPrograma();
	if (canalUnico(p.cadena, &c) && nombreUnico(p.nom, &aux)) {
		for (int i = 0; i < 3; i++) {
			p.actorID[i].num = 0;
			p.actorID[i].letra = 'a';
		}	
		programa = programaFileToList();
		LINKEDLISTPROGRAMA_add(&programa, p);
		actualizarFicheroPrograma(programa);
		LINKEDLISTCANALES_add(canales, c);
		printf ("Se ha añadido el programa correctamente\n");
	}
	else {
		printf ("No existe ningun canal con este nombre o ya hay un programa con este nombre.\n");
	}
}

/***********************************************
*
* @Finalidad: Crear un canal nuevo.
* @Parametros: in/out: *canales = Lista que engloba todos los programas y canales registrados.
* @Retorno: ----.
* 
************************************************/
void crearCanal (LinkedList3 *canales) {
	Canal c, aux;

	c = solicitarDatosCanal();
	if (!canalUnico(c.nombre, &aux)) {
		LINKEDLISTCANALES_add(canales, c);
		actualizarFicheroCanales(*canales);
		printf ("Se ha creado un canal correctamente\n");	
	}
	else {
		printf ("Se ha detectado un canal con el mismo nombre\n");
	}

}

/***********************************************
*
* @Finalidad: Eliminar el canal si este te lo permitw
* @Parametros: in/out: *list = Lista que engloba todos los canales registrados.
			   in/out: char nombreCanal = El nombre del canal que el productor quiere eliminar.
* @Retorno: ----.
* 
************************************************/

void eliminarC(LinkedList3 *list, char  nombreCanal[]){
	int found = 0;
	Canal currentCanal;
	int programas = 0;

	LINKEDLISTCANALES_goToHead(list);
	while(!LINKEDLISTCANALES_isAtEnd(*list) && !found){
		currentCanal = LINKEDLISTCANALES_get(list);
		if(!strcmp(nombreCanal, currentCanal.nombre)){
			found = 1;
			LINKEDLISTPROGRAMA_goToHead(&currentCanal.programas);
			if (LINKEDLISTPROGRAMA_isAtEnd(currentCanal.programas)) {
				LINKEDLISTCANALES_remove(list);
				actualizarFicheroCanales(*list);
				printf("Canal with name %s removed succesfully.\n", nombreCanal);
			}
			else {
				programas = 1;
			}
		}
		else {
			LINKEDLISTCANALES_next(list);
		}
	}
		
	if (programas) {
		printf ("El canal que esta intentndo eliminar contiene programas.\n");
	}
	if(!found){
		printf("Canal with name %s not found.\n", nombreCanal);
	}
	
}

/***********************************************
*
* @Finalidad: Nombrar el canal que se desea eliminar.
* @Parametros: ----.
* @Retorno: ----.
* 
************************************************/
void eliminarCanal(){
	LinkedList3 lista;
	int num_canales;
	char nombre[MAX_CHAR_SIMPLE]; 
	
	lista = canalesFileToList(&num_canales);
	printf("\nEnter the canal name to remove: ");
	scanf("%s", nombre);
	printf ("%s\n", nombre);
	eliminarC(&lista, nombre);
		
}

/***********************************************
*
* @Finalidad: Ejecutar las opciones del menu.
* @Parametros: 	in: option = Opcion a ejecutar.
*				out: *quit = Flag que indica la salida del menu.
* @Retorno: ----.
* 
************************************************/
void runOptionCanales (int option, int *quit) {
	LinkedList3 canales;
	int num_canales;

	canales = canalesFileToList(&num_canales);
	switch (option) {
		case 1:
			crearCanal(&canales);
			break;
		case 2:
			// modificarCanal();
			break;
		case 3: 
			 eliminarCanal();
			break;
		case 4:
			mostrarCanales(canales);			
			break;
		case 5: 
			anadirProgramaACanal(&canales);
			break;
		case 6:
			//mostraProgramas(programa);
			break;
		case 7:
			*quit = 1;
			break;
	}

}

/***********************************************
*
* @Finalidad: Ordenar alfabeticamente un array.
* @Parametros: 	in: *c = Array de canales a ordenar.
*				in: num_canales = Numero de canales a ordenar.
* @Retorno: ----.
* 
************************************************/
void selectionSort (Canal *c, int num_canales) {
	Canal minim;
	int i, j, posminim;
		for (j = 0; j < (num_canales - 1); j++) {
			minim = c[j];
			posminim = j;
			for (i = j+1; i < num_canales; i++) {
				if (strcmp(c[i].nombre, minim.nombre) < 0) {
					minim = c[i];
					posminim = i;
				}
			}
			c[posminim] = c[j];
			c[j] = minim;
		}

	for (i = 0; i < num_canales; i++) {
		printf ("Nombre canal: %s\n", c[i].nombre);
		printf ("Coste suscripcion%f\n", c[i].coste_suscripcion);
	}
}

/***********************************************
*
* @Finalidad: Generar una estructura dinamica con todos los canales.
* @Parametros: in/out = *num_canales = Numero de canales existentes en el sistema.
* @Retorno: Retorna un array dinamico de todos los canales.
* 
************************************************/
Canal * listaAArrayDinamico (int *num_canales) {
	LinkedList3 canales;
	Canal c, *array;;
	int i = 0;

	canales = canalesFileToList(num_canales);
	LINKEDLISTCANALES_goToHead(&canales);
	if (LINKEDLISTCANALES_isAtEnd(canales)) {
		printf ("\tERROR (No hay canales en el sistema)\n");
	}
	else {
		array = (Canal *)malloc(sizeof(Canal) * (*num_canales));
		while (!LINKEDLISTCANALES_isAtEnd(canales)) {
			c = LINKEDLISTCANALES_get(&canales);
			todoAMinusculas(c.nombre);
			strcpy (array[i].nombre, c.nombre);
			array[i].coste_suscripcion = c.coste_suscripcion;
			i++;
			LINKEDLISTCANALES_next(&canales);
		}
	}
	return array;
}

/***********************************************
*
* @Finalidad: Conjunto de interacciones de los canales.
* @Parametros: ----.
* @Retorno: ----.
* 
************************************************/
void menuCanales () {
	int option, quit = 0;
	do {
		option = mostrarMenuCanales();
		runOptionCanales(option, &quit);
	} while (!quit);
}
