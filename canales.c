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
