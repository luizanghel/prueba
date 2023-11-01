#include <stdio.h>
#include <string.h>

struct canal{
	char nombre[50];
	char programacion[50];
	double costoSuscripcion;
	double costoEmpresa;
};

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

		printf("Ingrese el nombre del nuevo Canal: ");
		scanf("%s", canales[*numCanales].nombre);

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
