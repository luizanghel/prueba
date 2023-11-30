#include "actors.h"


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

void eliminar (LinkedList2 *list, int dniNumber, char dniLetter) {
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

    int numdni;
    char pedir_letra;

    printf("\nEnter the DNI number to remove: ");
    scanf("%d", &numdni);

    printf("\nEnter the DNI letter to remove: ");
    scanf(" %c", &pedir_letra);

    eliminar(&lista, numdni, pedir_letra);
}

void dardebajaactor(LinkedList2 *actores){
    int numeros, found = 0, trobat=0;
    char letra;
    int i=0;
    Programa p;
    Actor a;
    LinkedList4 programas;

    printf ("Numeros dni actor: ");
    scanf ("%d", &numeros);
    printf ("Letra dni actor: ");
    scanf ("%c", &letra);
    scanf ("%c", &letra);

    programas=programaFileToList();
    LINKEDLISTPROGRAMA_goToHead (&programas);
    while (!LINKEDLISTPROGRAMA_isAtEnd (programas) && !found){
        p= LINKEDLISTPROGRAMA_get(&programas);
        i=0;
        while (i<3 && !found){
            if (p.actorID[i].num==numeros && p.actorID[i].letra==letra){
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
            if (a.dni.numeros == numeros && a.dni.letra == letra){
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

int revisarParametrosTelefonoA (char telefono[MAX_CHAR_SIMPLE],int op) {
	int error = 0, i;
	if (op == 4 && (strlen(telefono) != 9 && strlen(telefono) != 0 )) {
			error = 1;
			printf ("\tERROR (El numero de telefono unicamente puede contener 9 digitos)");	
		}

	if (!error) {
		for (i = 0; telefono[i] == '\0'; i++) {
			if (telefono[i] < '0' || telefono[i] > '9') {
				error = 1;
			}
		}
				if (op == 4 && error == 1 && strlen(telefono)!= 0){
				printf ("\tERROR (El telefono unicamente puede contener numeros).\n");
				}
				if (op == 5 && error == 1 && strlen(telefono)!= 0){
				printf ("\t ERROR (El Salario unicamente puede contener numeros).\n");
				}
	}
	return error;
}


int solicitarTelefonoA (char texto[MAX_CHAR_SIMPLE], int op) {
	int error = 0, telefono;// aux = 0;
	char palabra[MAX_CHAR_SIMPLE]; //aux2[MAX_CHAR_SIMPLE];
	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
	//	if( aux == 0){
	//		fgets(aux2, MAX_CHAR_SIMPLE, stdin);
	//		fgets(aux2, MAX_CHAR_SIMPLE, stdin);
	//	}
	//	aux++;
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosTelefonoA(palabra, op);
	} while (error);
	
	if (!error) {
		telefono = atoi(palabra);
	}
	//scanf("%c", &aux);
	return telefono;
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
		error = option2AsNumber(&option, 1, 6);
	
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
			numero = solicitarTelefonoA("Introduce telefono a modificar: ", option);
			p->telefono = numero;
			break;		
		case 5:
			printf ("Su salario actual es %d.", p->salari);
			numero = solicitarTelefonoA("Introduce el salario: ", option);
			p->salari = numero;
			break;
	}
}

void modificarActores (LinkedList2 *actors) {
	int option, found;
	int idl;
	
	Actor p;
	char  letid, aux, tipo[5][MAX_CHAR_SIMPLE] = {"nombre", "primer apellido", "segundo apellido", "numero de telefono", "salario"};
	

	mostrarActoresDisponibles(*actors);
	do {

		option = menuModificacionActores();
		if (option != 6) {

		printf("\n Introduce los numeros del DNI: ");
		scanf("%d", &idl);

		printf("\n Introduce la letra del DNI: ");
		scanf("%c", &letid);
		scanf("%c", &letid);
		scanf("%c", &aux);
			found = 0;
			LINKEDLISTactors_goToHead(actors);

			while (!LINKEDLISTactors_isAtEnd(*actors) && !found) {
				p = LINKEDLISTactors_get(actors);
				// printf("Numero Ingresado: %ld || Numero en base: %d && Letra Ingresada %c || Letra en Base %c", idl, p.dni.numeros, letid, p.dni.letra);

				if (p.dni.numeros == idl && p.dni.letra == letid) {
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
				printf ("El %s de %d%c ha sido modificado correctamente.\n", tipo[option-1], idl,letid);
			
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

