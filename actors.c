#include <stdio.h>

#include "actors.h"
#include "canales.h"

#define MAX_CHAR_SIMPLE 100

void mostrarActoresDisponibles (LinkedList2 list) {
	Actor actor;
	int i = 1;

	LINKEDLISTactors_goToHead(&list);
	while (!LINKEDLISTactors_isAtEnd(list)) {
		actor = LINKEDLISTactors_get(&list);
		if (!actor.contractat) {
			printf ("--Actor numero %d--\n", i++);
			printf ("  Identificador: %d%c\n", actor.dni.numeros, actor.dni.letra);
			printf ("  Nombre y apellidos: %s %s %s\n", actor.nombre, actor.apellido1, actor.apellido2);
			printf ("  Numero de telefono: %d\n", actor.telefono);
			printf ("  Salario: %d€\n", actor.salari);
		}
		LINKEDLISTactors_next(&list);
	}

	
}


LinkedList2 actorsALista () {
	LinkedList2 lista;
	FILE *f;
	Actor p;
	char aux;

	f = fopen ("actors.txt", "r");
	if (f == NULL) {
		printf ("No hay actores registrados.\n");
	}
	else {
		lista = LINKEDLISTactors_create();
		fscanf(f, "%d", &p.dni.numeros);
		while (!feof(f)) {
			fscanf(f, "%c", &p.dni.letra);
			fscanf(f, "%c", &aux);
			fgets(p.nombre, MAX_CHAR_SIMPLE, f);
			p.nombre[strlen(p.nombre) - 1] = '\0';
			fgets(p.apellido1, MAX_CHAR_SIMPLE, f);
			p.apellido1[strlen(p.apellido1) - 1] = '\0';
			fgets(p.apellido2, MAX_CHAR_SIMPLE, f);
			p.apellido2[strlen(p.apellido2) - 1] = '\0';	
			fscanf(f, "%d", &p.telefono);
			fscanf(f, "%d", &p.salari);
			fscanf(f, "%d", &p.contractat);
			LINKEDLISTactors_add(&lista, p);
			fscanf(f, "%d", &p.dni.numeros);
		}
		fclose(f);
			
	}

	return lista;
}


/***********************************************
*
* @Finalidad: Escribir el contenido de una lista en un fichero.
* @Parametros: in: usuarios = Lista de donde saca la informacion.
* @Retorno: ----.
* 
************************************************/
void actualizarFicheroActors (LinkedList2 usuarios) {
	FILE *actualizado = NULL;
	Actor p;

	actualizado = fopen("nuevo.txt", "w");
	if (actualizado == NULL) {
		printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
		
	}
	else {
		LINKEDLISTactors_goToHead(&usuarios);
		while (!LINKEDLISTactors_isAtEnd(usuarios)) {
			p = LINKEDLISTactors_get(&usuarios);
			fprintf(actualizado, "%d%c\n", p.dni.numeros, p.dni.letra);
	   		fprintf(actualizado, "%s\n", p.nombre);
	   		fprintf(actualizado, "%s\n", p.apellido1);
	   	 	fprintf(actualizado, "%s\n", p.apellido2);
	    	fprintf(actualizado, "%d\n", p.telefono);
	    	fprintf(actualizado, "%d\n", p.salari);
		    fprintf(actualizado, "%d\n", p.contractat);
			LINKEDLISTactors_next(&usuarios);
		}
		fclose(actualizado);
		remove("actors.txt");
		rename("nuevo.txt", "actors.txt");
	}

}

void addActor(LinkedList2 *lista){
   	Actor actor, actor2;
   	int found = 0;

    printf ("\nEnter your actor DNI number: ");
    scanf("%d", &actor.dni.numeros);
    
    printf ("\nEnter your actor DNI letter: ");
    scanf("%c", &actor.dni.letra);
    scanf("%c", &actor.dni.letra);
    
    printf ("\nEnter your actor name: ");
    scanf("%s", actor.nombre);
    
    printf ("\nEnter your actor first surname: ");
    scanf("%s", actor.apellido1);
    
    printf ("\nEnter your actor second surname: ");
    scanf("%s", actor.apellido2);
    
    do{
        printf ("\nEnter your actor phone number: ");
        scanf("%d", &actor.telefono);
        if(actor.telefono > 999999999 || actor.telefono < 100000000){
            printf("\nERROR! This is not a valid phone number"); 
        }
    }while(actor.telefono > 999999999 || actor.telefono < 100000000 );
    
    printf ("\nEnter your actor salari: ");
    scanf("%d", &actor.salari);
    
    
   	actor.contractat = 0; 

    LINKEDLISTactors_goToHead(lista);
	while (!LINKEDLISTactors_isAtEnd(*lista) && !found) {
		actor2 = LINKEDLISTactors_get(lista);
		if (actor2.dni.numeros == actor.dni.numeros && actor2.dni.letra == actor.dni.letra) {
			found = 1;
		}
		else {
			LINKEDLISTactors_next(lista);
		}
	}

	
	if (!found) {
    	LINKEDLISTactors_add (lista, actor);
		printf ("S'ha afegit correctament el actor %s amb identificador %d%c.\n\n", actor.nombre, actor.dni.numeros, actor.dni.letra);
		actualizarFicheroActors(*lista);
	}
	else {
		printf ("Ya se ha encontrado un actor con este identificador.\n");
	}
	

}



void contratarActor (LinkedList2 *actores) {
	int numeros, found = 0;
	char letra;
	Actor a;

	printf ("Numeros dni actor: ");
	scanf ("%d", &numeros);
	printf ("Letra dni actor: ");
	scanf ("%c", &letra);
	scanf ("%c", &letra);
	
	LINKEDLISTactors_goToHead(actores);
	while (!LINKEDLISTactors_isAtEnd(*actores) && !found) {
		a = LINKEDLISTactors_get(actores);
		if (a.dni.numeros == numeros && a.dni.letra == letra) {
			found = 1;
			if (!a.contractat) {
				if (assignarAlPrograma(numeros, letra)) {
					a.contractat = 1;
					LINKEDLISTactors_remove(actores);
					LINKEDLISTactors_add(actores, a);
					actualizarFicheroActors(*actores);
					printf ("\tEl actor se ha contratado correctamente\n");
				}
				else {
					printf ("El programa no existe\n");
				}
			}
			else {
				printf ("\tERROR (El actor ya ha sido contratado)\n");
			}
		}
		LINKEDLISTactors_next(actores);
	}
	if (!found) {
		printf ("\tERROR (No se ha encontrado ningun actor con el identificador)\n");
	}
}

void ModificarActores(LinkedList2 *actors){
	int option, found;
	Actor p;
	char id[MAX_CHAR_SIMPLE],tipo [5] [MAX_CHAR_SIMPLE]= {"nombre", "primer apellido", "segundo apellido", "numero de telefono", "salario"}
		
	do {
		option = menuModificationActores();
		if(option != 6){
			solicitarDni("Introduce el id  del Actor a modificar: ", correo);
			found=0
			mostrarActoresDisponible(*actors);
			LINKEDLISTactors_goToHead(actors);
			while (!LINKEDLISTactors_isAtEnd(*actors) && !found){
				p = LINKEDLISTactors_get(actors);
				if(!strcmp(p.dni.numeros+p.dni.letr, id)) {
					found=1;
					runOption(option, &p);
					LINKEDLISTactors_remove(actors);
					LINKEDLISTactors_add(actors, p);
				}else{
					LINKEDLISTactors_next(actors);	
				}
			
			}
			if (!found){
				printf("ERROR (No se ha encontrado ningun actor con este id).\n");
			}else{
				actualitzarFicheroActors(*actors);
				printf ("El %s de %s ha sido modificado correctamente.\n", tipo[option-1, id]);
			}
		}

	}while(option != 7);
	
}


void opcionesActores(int opcion){
	LinkedList2 actors;
	actors = actorsALista();
		
	switch (opcion){
		case 1:
			addActor(&actors);
			break;
		case 2:
			contratarActor(&actors);
			break;
		case 3:
			//DarDeBaja();
			break;

		case 4:
			mostrarActoresDisponibles(actors);
			break;

		case 5:
			//EditarActores();
			break;
			
		case 6:
			//EliminarActores();
			break;

		case 7:
			//quit();
			break;

		default:
			printf("\nOpcion no válida. Prueba otra vez.");
			break;
	}

}


void menuActors(){
	int option=0, error=0;
	char aux;
	
	do {
		do{
			printf("\t1- Registrar actor\n");	
			printf("\t2- Contratar actor\n");	
			printf("\t3- Dar de baja a un actor\n");	
			printf("\t4- Listar actores\n");	
			printf("\t5- Editar actores\n");	
			printf("\t6- Eliminar actores\n");
			printf("\t7- Salir\n");
			printf("\tEscoge una opción: ");
			scanf("%d", &option);
			scanf("%c", &aux);	
			if (option < 1 || option > 7) {
				printf ("ERROR: Introduce una opcion entre el 1 y el 7\n");
			}
		} while(error);	
	
		opcionesActores(option);
	} while (option != 7);

}

