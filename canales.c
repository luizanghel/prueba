#include <stdio.h>
#include <string.h>

struct canal{
	char nombre[50];
	char programacion[50];
	double costoSuscripcion;
	double costoEmpresa;
};
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

void crearNuevoCanal(struct Canal *canales, int *numCanales, struct Programa *programas, int idCanal, int i) {
		//Programas
		//char c;

		if (*numCanales < 10) {
		do {
			printf("Ingrese el nombre del nuevo Canal: ");
			scanf("%s", canales[*numCanales].nombre);
		} while(CanalExistente(canales[*numCanales].nombre, canales, *numCanales) == 1);

		printf("Ingrese el nombre de la programacion del nuevo canal: ");
		scanf("%s", canales[*numCanales].programacion);

	//	printf("Desea Crear un programa s/n: ");
	//	scanf("%s", canales[*numCanales].nombre);
	//	if ((*numCanales == 0)||(i>0)){
	//		idCanal = i;
	//	}
	//	if(( c == 's') || (c == 'S')){
	//		crearPrograma(programas, &idCanal);
	//	}

		printf("Ingrese el costo de suscripcion del nuevo canal: ");
		scanf("%lf", &canales[*numCanales].costoSuscripcion);

		canales[*numCanales].costoEmpresa = 2.0 * canales[*numCanales].costoSuscripcion;

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
			//	crearNuevoCanal(canales, &numCanales, programas, idCanal, i);
				break;
			case 3:
			//	crearNuevoCanal(canales, &numCanales, programas, idCanal, i);
				break;
			case 4:
			//	crearNuevoCanal(canales, &numCanales, programas, idCanal, i);
				break;
			case 5:
			//	crearNuevoCanal(canales, &numCanales, programas, idCanal, i);
				break;
			case 6:
			//	crearNuevoCanal(canales, &numCanales, programas, idCanal, i);
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
