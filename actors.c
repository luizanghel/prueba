#include <stdio.h>
#include "actors.h"
#include "linkedlistactores.h"

#define MAX_CHAR_SIMPLE 100

LinkedList actorsALista () {
	LinkedList lista;
	FILE *f;
	FileActor p;
	char aux;

	f = fopen ("actores.txt", "r");
	if (f == NULL) {
		printf ("Error! Debe contactar con un administrador en el menor tiempo posible\n");
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



int addActor(){
    FileActor actor, actor2;
    LinkedList lista;
    int found = 0;

    char name[100], surname1[100], surname2[100];
    int phone, salario, contract_status;
    
   		 
   	printf("Entra el numero del DNI: ");
	scanf ("%d", &actor.dni.numeros);

	printf ("Entra la letra del DNI: ");
	scanf ("%c", &actor.dni.letra);

void menuActors(){

	int option=0, error=0;
	char aux;
	
	do{
		printf("\nMenu Actores");	
		printf("\n1. Registrar actor");	
		printf("\n2. Contratar actor");	
		printf("\n3. Dar de baja a un actor");	
		printf("\n4. Listar actores");	
		printf("\n5. Gestionar actores");	
		printf("\n6. Eliminar actores");
		printf("\n7. Salir");
		printf("\nEscoge una opción: ");
		scanf("%d", &option);
		
		opcionesActores(option);

	}while(error==0);	
	return option;
}

void opcionesActores(int opcion){

	switch (opcion){
		case 1:
			//RegistrarActor();
			break;
		case 2:
			//ContratarActor();
			break;
		case 3:
			//DarDeBaja();
			break;

		case 4:
			//ListarActores();
			break;

		case 5:
			//GestionarActores();
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


void addActor(){
    FileActor actor;
    FileDni dni_pedir;
    LinkedList lista;
    lista = LINKEDLISTactors_create ();
    
    char name[100], pedir_letra[100], surname1[100], surname2[100];
    int numdni , phone, salario, contract_status;
    
    printf ("\nEnter your actor DNI number: ");
    scanf("%d", &numdni);
    
    printf ("\nEnter your actor DNI letter: ");
    scanf("%s", pedir_letra);
    
    printf ("\nEnter your actor name: ");
    scanf("%s", name);
    
    printf ("\nEnter your actor first surname: ");
    scanf("%s", surname1);
    
    printf ("\nEnter your actor second surname: ");
    scanf("%s", surname2);
    
    do{
        printf ("\nEnter your actor phone number: ");
        scanf("%d", &phone);
        if(phone > 999999999 || phone < 100000000){
            printf("\nERROR! This is not a valid phone number"); 
        }
    }while(phone > 999999999 || phone < 100000000 );
    
    printf ("\nEnter your actor salari: ");
    scanf("%d", &salario);
    
    
    do{
        printf ("\nEnter your actor contract state (0 if not contracted, 1 if cotracted): ");
        scanf("%d", &contract_status);
        if (contract_status != 0 && contract_status != 1){
            printf("\nERROR!");
        }
    }while( contract_status != 0 && contract_status != 1);
    
    strcpy (actor.nombre, name);
    strcpy (actor.apellido1, surname1);
    strcpy (actor.apellido2, surname2);

    actor.telefono = phone;
    actor.salari = salario;
    actor.contractat = contract_status; 
	
	lista = actorsALista();

    LINKEDLISTactors_goToHead(&lista);
	while (!LINKEDLISTactors_isAtEnd(lista) && !found) {
		actor2 = LINKEDLISTactors_get(&lista);
		if (actor2.dni.numeros == actor.dni.numeros && actor2.dni.letra == actor.dni.letra) {
			found = 1;
		}
		else {
			LINKEDLISTactors_next(&lista);
		}
	}

	
	if (!found) {
    	LINKEDLISTactors_add (&lista, actor);
		printf ("S'ha afegit correctament el actor %s amb identificador %d%c.\n", actor.nombre, actor.dni.numeros, actor.dni.letra);
	}
	else {
		printf ("Ya se ha encontrado un actor con este identificador.\n");
	}

	return !found;
}
