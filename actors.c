#include "actors.h"

/***********************************************
*
* @Finalidad: Solicitar un DNI para un actor.
* @Parametros:	in: texto[] = Texto que se mostrara para la solicitud.
* @Retorno: Devuelve el conjunto del DNI del actor.
* 
************************************************/
DniActor solicitarDniActor (char texto[MAX_CHAR_SIMPLE]) {
	char palabra[MAX_CHAR_SIMPLE];
	DniActor dni;
	int error = 0;

	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosID(palabra, &dni.numeros, &dni.letra);
	} while (error);

	return dni;
}

/***********************************************
*
* @Finalidad: Mostrar actores que no esten contratados.
* @Parametros:	in: list = Lista de actores contradados/no contratados.
* @Retorno: ----.
* 
************************************************/
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

/***********************************************
*
* @Finalidad: Leer el contenido de un fichero y retornar una lista con la informacion.
* @Parametros: ----.
* @Retorno: Lista de actores.
* 
************************************************/
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

Actor solicitarDatosActor () {
	Actor actor;

	actor.dni = solicitarDniActor("Introduce el DNI del actor: ");
   	solicitarPalabra("Introduce el nombre del actor: ", actor.nombre, NOMBRE); 
  	solicitarPalabra("Introduce el primer apellido del actor: ", actor.apellido1, PRIMER_APELLIDO); 
   	solicitarPalabra("Introduce el segundo apellido del actor: ", actor.apellido2, SEGUNDO_APELLIDO); 
    actor.telefono = solicitarTelefono("Introduce el nombre del actor: ", 9);
  	actor.salari = solicitarFloat("Introduce el salario del actor: ");	
   	actor.contractat = 0; 

	return actor;
}

void addActor(LinkedList2 *lista){
   	Actor actor, actor2;
   	int found = 0;

    actor = solicitarDatosActor();
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
	Actor a;
	DniActor input;
	int found = 0;
	
	input = solicitarDniActor("Introduce DNI del actor: ");	
	LINKEDLISTactors_goToHead(actores);
	while (!LINKEDLISTactors_isAtEnd(*actores) && !found) {
		a = LINKEDLISTactors_get(actores);
		if (a.dni.numeros == input.numeros && a.dni.letra == input.letra) {
			found = 1;
			if (!a.contractat) {
				if (assignarAlPrograma(input.numeros, input.letra)) {
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

void eliminarActor (LinkedList2 *list, int dniNumber, char dniLetter) {
	int found = 0;
	Actor currentActor;

    LINKEDLISTactors_goToHead(list);
    while (!LINKEDLISTactors_isAtEnd(*list) && !found) {
        currentActor = LINKEDLISTactors_get(list);
        if (currentActor.dni.numeros == dniNumber && currentActor.dni.letra == dniLetter) {
			found = 1;
			if (!currentActor.contractat) {
				LINKEDLISTactors_remove(list);
    	        printf("Actor with DNI %d%c removed successfully.\n", dniNumber, dniLetter);
				actualizarFicheroActors(*list);
        	}
			else {
				printf ("ERROR (El actor que se esta intentando eliminar se encuentra contratado. Para borrarlo del sistema, es necesario darlo de baja previamente)\n");
			}
		}

        LINKEDLISTactors_next(list);
    }
	if (!found) {
    	printf("Actor with DNI %d%c not found.\n", dniNumber, dniLetter);
	}
}
			
void removeActorByDNI() {
    LinkedList2 lista;
    lista = LINKEDLISTactors_create();
	DniActor input;
	
	input = solicitarDniActor("Introduce el DNI del actor: ");

    eliminarActor(&lista, input.numeros, input.letra);
}

void dardebajaactor(LinkedList2 *actores){
    int found = 0, trobat=0;
    int i=0;
    Programa p;
    Actor a;
    LinkedList4 programas;
	DniActor input;

	input = solicitarDniActor("Introduce DNI del actor: ");
    programas=programaFileToList();
    LINKEDLISTPROGRAMA_goToHead (&programas);
    while (!LINKEDLISTPROGRAMA_isAtEnd (programas) && !found){
        p= LINKEDLISTPROGRAMA_get(&programas);
        i=0;
        while (i<3 && !found){
            if (p.actorID[i].num == input.numeros && p.actorID[i].letra == input.letra){
                found=1;
                p.actorID[i].num=0;
                p.actorID[i].letra='a';
                LINKEDLISTPROGRAMA_remove(&programas);
                LINKEDLISTPROGRAMA_add(&programas, p);
                actualizarFicheroPrograma(programas);
            }
            i++;
        }
        LINKEDLISTPROGRAMA_next(&programas);
    }
    if (!found){
        printf("Este actor no esta contratado en ningun programa!\n");
    }else{
        LINKEDLISTactors_goToHead(actores);
        while (!LINKEDLISTactors_isAtEnd(*actores) && !trobat){
            a = LINKEDLISTactors_get(actores);
            if (a.dni.numeros == input.numeros && a.dni.letra == input.letra){
                a.contractat = 0;
                LINKEDLISTactors_remove(actores);
                LINKEDLISTactors_add(actores, a);
                actualizarFicheroActors(*actores);
                printf ("\tEl actor se ha dado de baja correctamente\n\n");
            }
            LINKEDLISTactors_next(actores);
        }
    }

}

int menuModificacionActores() {
	int option, error = 0;

	do {
		printf ("\tQue deseas modificar?\n");
		printf ("\t  1- Nombre\n");
		printf ("\t  2- Primer Apellido\n");
		printf ("\t  3- Segundo Apellido\n");
		printf ("\t  4- Numero de telefono\n");
		printf ("\t  5- Salario\n");
		printf ("\t  6- Salir\n");
		printf ("\t  Enter option: ");
		error = optionAsNumber(&option, 1, 6);
	
	} while (error);

	return option;
}


void runOptionA(int option, Actor *p) {
	char cambio[MAX_CHAR_SIMPLE];
	int numero;
	
	switch (option) {
		case 1:
			printf ("El nombre actual del Actor es %s.", p->nombre);
			solicitarPalabra("Introduce nombre a modificar: ", cambio, option--);
			strcpy(p->nombre, cambio);
			break;
		case 2:
			printf ("El primer apellido del Actor actual es %s.", p->apellido1);
			solicitarPalabra("Introduce primer apellido a modificar: ", cambio, option--);
			strcpy(p->apellido1, cambio);
			break;
		case 3:
			printf ("El segundo apellido actual del Actor es %s.", p->apellido2);
			solicitarPalabra("Introduce segundo apellido a modificar: ", cambio, option--);
			strcpy(p->apellido2, cambio);
			break;
		case 4:
			printf ("Su numero de telefono actual es %d.", p->telefono);
			numero = solicitarTelefono("Introduce telefono a modificar: ", option);
			p->telefono = numero;
			break;		
		case 5:
			printf ("Su salario actual es %d.", p->salari);
			numero = solicitarTelefono("Introduce el salario: ", option);
			p->salari = numero;
			break;
	}
}

void modificarActores (LinkedList2 *actors) {
	int option, found;
	DniActor dni;
	Actor p;
	char tipo[5][MAX_CHAR_SIMPLE] = {"nombre", "primer apellido", "segundo apellido", "numero de telefono", "salario"};
	

	mostrarActoresDisponibles(*actors);
	do {

		option = menuModificacionActores();
		if (option != 6) {

			dni = solicitarDniActor("Introduce DNI del actor: ");
			found = 0;
			LINKEDLISTactors_goToHead(actors);

			while (!LINKEDLISTactors_isAtEnd(*actors) && !found) {
				p = LINKEDLISTactors_get(actors);
				// printf("Numero Ingresado: %ld || Numero en base: %d && Letra Ingresada %c || Letra en Base %c", idl, p.dni.numeros, letid, p.dni.letra);

				if (p.dni.numeros == dni.numeros && p.dni.letra == dni.letra) {
					found = 1;
					runOptionA(option, &p);
					LINKEDLISTactors_remove(actors);
					LINKEDLISTactors_add(actors, p);
				}
				else {
					LINKEDLISTactors_next(actors);
				}
			}
			if (!found) {
				printf ("ERROR (No se ha encontrado ningun Actor con este ID).\n");
			}
			else {
				actualizarFicheroActors(*actors);
				printf ("El %s de %d%c ha sido modificado correctamente.\n", tipo[option-1], dni.numeros, dni.letra);
			
			}
		}
	} while (option != 6);
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
			dardebajaactor(&actors);
			break;

		case 4:
			mostrarActoresDisponibles(actors);
			break;

		case 5:
			modificarActores(&actors);
			break;
			
		case 6:
			removeActorByDNI(&actors);
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

