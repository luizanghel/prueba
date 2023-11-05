#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct canal{
	char nombre[50];
	char programacion[50];
	double costoSuscripcion;
	double costoEmpresa;
};

struct Programa {
	char nombre[50];
	char cadenaEmision[50];
	char categoria[20];
	char horaEmision[10];
	int duracionMinutos;
	char actores[3][30];
	int idCanal;
};

void crearPrograma(struct Programa *programas, int *idCanal){
	if (*idCanal < 20){
		printf("Ingrese el nomnbre del Programa: ");
		scanf("%s", programas[*idCanal].nombre);

		printf("Ingrese el nomnbre de la cadena de Emision: ");
		scanf("%s", programas[*idCanal].cadenaEmision);

		printf("Ingrese la categoria del Programa: ");
		scanf("%s", programas[*idCanal].categoria);

		printf("Ingrese la hora de emision en el formato de 24 horas HH:MM : ");
		scanf("%s", programas[*idCanal].horaEmision);

		printf("Ingrese la duracion del programa en Minutos: ");
		scanf("%d", &programas[*idCanal].duracionMinutos);

		printf("Ingrese hasta 3 Actores para el nuevo Programa: ");
		for (int i = 0; i < 3; ++i){
			printf("Actor %d:", i+1);
			scanf("%s", programas[*idCanal].actores[i]);
		}

		FILE *archivop = fopen("programas.txt", "a");

		if (archivop != NULL) {
			fprintf(archivop, "Canal al que pertenece el programa %d \n", *idCanal + 1);
			fprintf(archivop, "Nombre del Programa: %s\n", programas[*idCanal].nombre);
			fprintf(archivop, "Cadena de Emision: %s\n", programas[*idCanal].cadenaEmision);
			fprintf(archivop, "Categoria: %s\n", programas[*idCanal].categoria);
			fprintf(archivop, "Hombre Emision HH:MM: %s\n", programas[*idCanal].horaEmision);
			fprintf(archivop, "Duracion en Minutos: %d\n", programas[*idCanal].duracionMinutos);

			for (int i = 0; i < 3; ++i){
				fprintf(archivop, "Actor %d: %s\n", i+1, programas[*idCanal].actores[i]);
			}
				fprintf(archivop, "\n");

			fclose(archivop);
		} else {
		
		printf("No se pueden crear mas Programas");
		}
	}
}


int myStricmp(const char *s1, const char *s2){
	while (*s1 && *s2){
		if(tolower(*s1) != tolower(*s2)) {
			return *s1 - *s2;
		}
		s1++;
		s2++;
	}
	return tolower(*s1)- tolower(*s2);
}

int CanalExistente(const char *nombre, const struct Canal *canales, int numCanales){
		for (int i = 0; i < numCanales; i++){
			if (myStricmp(nombre, canales[i].nombre) == 0){
				return 1;
			}
		}

		FILE *archivo = fopen("canales.txt", "r");
		if (archivo != NULL){
			char linea[100];
			while (fgets(linea, sizeof(linea), archivo) != NULL){
				if (strstr(linea, nombre) != NULL){
					fclose(archivo);
					return 1;
				}
			}
		}

		return 0;
}

/*****************************************
*
* @
* @
* @
*
*****************************************/
void limpiarBuffer(){
	int c
	while((c = getchar()) != '\n' && c != EOF);
}

void crearNuevoCanal(struct Canal *canales, int *numCanales, struct Programa *programas, int idCanal, int i) {
		//Programas
		//char c;

		if (*numCanales < 10) {
		do {
			printf("Ingrese el nombre del nuevo Canal: ");
			scanf("%s", canales[*numCanales].nombre);
		} while(CanalExistente(canales[*numCanales].nombre, canales, *numCanales) == 1);


		limpiarBuffer();
		printf("Ingrese el nombre de la programacion del nuevo canal: ");
		fgets(canales[*numCanales].programacion, sizeof(canales[*numCanales].programacion), stdin);
        canales[*numCanales].programacion[strcspn(canales[*numCanales].programacion, "\n")] = '\0';

	//	scanf("%s", canales[*numCanales].programacion);

	//	printf("Desea Crear un programa s/n: ");
	//	scanf("%s", canales[*numCanales].nombre);
	//	if ((*numCanales == 0)||(i>0)){
	//		idCanal = i;
	//	}
	//	if(( c == 's') || (c == 'S')){
	//		crearPrograma(programas, &idCanal);
	//	}
		
		do{
			printf("Ingrese el costo de suscripcion del nuevo canal: ");
			while (scanf("%lf", &canales[*numCanales].costoSuscripcion) != 1){
				printf("Entrada no valida. Por favor, Ingrese un numero: ");
				scanf("%*[^\n]");
				scanf("%*c");
			}
			canales[*numCanales].costoEmpresa = 2.0 * canales[*numCanales].costoSuscripcion;
		}while ((getchar()) != '\n');

		// Info del Canal Creado

		printf("\nNuevo canal creado:\n");
		printf("Nombre: %s\n", canales[*numCanales].nombre);
		printf("Programacion: %s\n", canales[*numCanales].programacion);
		printf("Costo de suscripcion: %.2lf\n", canales[*numCanales].costoSuscripcion);
		printf("Costo para la empresa: %.2lf\n", canales[*numCanales].costoEmpresa);
		(*numCanales)++;


		FILE *archivo = fopen("canales.txt", "a");

		if (archivo != NULL){

			fprintf(archivo, "Canal N°%d \n", *numCanales);
			fprintf(archivo, "Nombre: %s\n", canales[*numCanales - 1].nombre);
			fprintf(archivo, "Programacion: %s\n", canales[*numCanales - 1].programacion);
			fprintf(archivo, "Costo de suscripcion: %.2lf\n", canales[*numCanales - 1].costoSuscripcion);
			fprintf(archivo, "Costo para la empresa: %.2lf\n", canales[*numCanales - 1].costoEmpresa);
			fprintf(archivo, "\n");

			fclose(archivo);
		} else {

		printf("No se pueden crear mas canales. Se alcanzo el limite.\n");
		}

	}
}

/*****************************************
*
* @
* @
* @
*
*****************************************/

void listarCanal(struct Canal *canales, int numCanales){
	FILE *archivo = fopen("canales.txt", "r");
		if(archivo != NULL){
			char linea[200];
			
			while(fgets(linea, sizeof(linea), archivo) != NULL){
				printf("%s",linea);
			}

			fclose(archivo);
		}else {
			printf("No se pudo abrir el archivo. \n");
		}
}

void modificarCanal(struct Canal *canales, int numCanales){
	int numeroActual = 0;

	if (numCanales > 0){
		int opcion;
		int op;

		printf("Seleccione el numero del canal a modificar: ");
		scanf("%d", &opcion);

		if (opcion >= 1 && opcion <= numCanales){
			do {
				printf("\n Ingrese la opcion a modificar \n");
				printf("1. Nombre del Canal\n");
				printf("2. Programacion del Canal\n");
				printf("3. Costo de Suscripcion del Canal\n");
				printf("0. Salir\n");
				printf("Seleccione una opcion\n");
				scanf("%d", &op);

				switch (op) {
				
					case 1:
						printf("Ingrese el nuevo nombre para el canal %s: ", canales[opcion - 1].nombre);
						scanf("%s", canales[opcion - 1].nombre;
						break;
					case 2:
						printf("Ingrese la nueva programacion para el canal %s: ", canales[opcion - 1].nombre);
						scanf("%s", canales[opcion - 1].programacion;
						break;
					case 3:
						printf("Ingrese el nuevo coste de suscripcion para el canal %s: ", canales[opcion - 1].nombre);
						scanf("%lf", &canales[opcion - 1].costoSuscripcion);
						canales[opcion - 1].costoEmpresa = 2.0 * canales[opcion - 1].costoSuscripcion;
						break;
					case 0:
						printf("Saliendo del programa.\n");
						break;
					default:
						printf("Opcion no valida. Intentelo de nuevo.\n");

				}
		} while (op != 0);

		FILE *archivo = fopen("canales.txt", "r");
		FILE *temporal = fopen("temporal.txt", "w");

		if (archivo == NULL || temporal == NULL){
			printf("Error al abrir el archivo. \n");
			return;
		}

		char linea[200];

		while (fgets(linea, sizeof(linea), archivo) != NULL) {
			if (strstr(linea, "Canal N°") != NULL){
			    sscanf(linea, "Canal N°%d", &numeroActual);
			}

			if (numeroActual == opcion){
				fprintf(temporal, "Canal N°%d\n", opcion);
				fprintf(temporal, "Nombre: %s\n", canales[opcion - 1].nombre);
				fprintf(temporal, "Programacion: %s\n", canales[opcion - 1].programacion);
				fprintf(temporal, "Costo de suscripcion: %.2lf\n", canales[opcion - 1].costoSuscripcion);
				fprintf(temporal, "Costo para la empresa: %.2lf\n", canales[opcion - 1].costoEmpresa);
				fprintf(temporal, "\n");
				numeroActual++;
			} else{
				fprintf(temporal, "%s", linea);
			}

		fclose(archivo);
		fclose(temporal);

		remove("canales.txt");
		rename("temporal.txt", "canales.txt");
		} else {
			printf("Opcion no valida. \n");
		}
	}
}


/*****************************************
*
* @Finalidad: Menu para Canales 
* @Parametros:
* @Retorno: -
*
*****************************************/

void menuCanales(){
	
	struct Canal Canales[10];
	struct Programa Programas[20];
	int numCanales = 0;
	int idCanal = 0;
	int i = 0;

	int opcion;

	FILE *archivo = fopen("canales.txt","r");
	if (archivo == NULL){
		numCanales = 0;
	} else{
		char linea[200];

		while (fgets(linea, sizeof(linea),archivo) != NULL){
			if (strstr(linea, "Canal N°") != NULL) {
				sscanf(linea, "Canal N°%d", &numCanales);
			}
		}
	}

	idCanal = numCanales;

	do{
        printf("\nMenu\n");
        printf("1. Crear nuevo canal \n");
        printf("2. Listar canales \n");
        printf("3. Modificar canal \n");
        printf("4. Eliminar canal \n");
        printf("5. Crear programa \n");
        printf("6. Eliminar programa \n");
        printf("0. Salir \n");
        printf("Seleccione una opcion\n");
		scanf("%d", opcion);

		switch (opcion){

			case 1:
				crearNuevoCanal(canales, &numCanales, programas, idCanal, i);
				i++;
				break;
			case 2:
				listarCanal(canales, numCanales);
				break;
			case 3:
				modificarCanal(canales, numCanales);
				break;
			case 4:
			//	eliminarCanal();
				break;
			case 5:
				printf("Ingrese el Id del Canal al que pertenece el Programa \n");
				scanf("%d", &idCanal);
				crearPrograma(programas, idCanal - 1);
				break;
			case 6:
			//	eliminarPrograma();
				break;
			case 0:
				printf("Saliendo del Programa.\n");
				break;
			default:
				printf("Opcion no valida.  Intentelo de nuevo.\n")
				break;
		}

	}while (opcion != 0);

}
