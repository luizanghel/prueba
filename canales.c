#include "canales.h"

/***********************************************
*
* @Finalidad: Actualizar 'canales.txt' para que se encuentren todos los canales registrados.
* @Parametros: in: canal = LinkedList de canales.
* @Retorno: ----.
* 
************************************************/
void actualizarFicheroCanales (LinkedList3 canal) {
    FILE *actualizado = NULL;

    actualizado = fopen("nuevo.txt", "w");
    if (actualizado == NULL) {
        printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
    	exit(0);
	}
    else {
        Canal c;

        LINKEDLISTCANALES_goToHead(&canal);
        while (!LINKEDLISTCANALES_isAtEnd(canal)) {
            c = LINKEDLISTCANALES_get(&canal);
            fprintf(actualizado, "%s\n", c.nombre);
            fprintf(actualizado, "%f\n", c.coste_suscripcion);
            fprintf(actualizado, "%d\n", c.num_suscriptores);
            for (int i = 0; i < c.num_suscriptores; i++) {
                fprintf(actualizado, "%s\n", c.suscriptores[i]);
            }
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

    solicitarPalabra("Introduce nombre del canal: ", c.nombre, NOMBRE_CANAL);
    c.coste_suscripcion = solicitarFloat("Introduce coste de suscripcion: ", COSTE_SUSCRIPCION);
    c.num_suscriptores = 0;

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

    lista = LINKEDLISTPROGRAMA_create();
    f = fopen ("programas.txt", "r");
    if (f == NULL) {
    }
    else {
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
	char suscriptor[MAX_CHAR_SIMPLE];

	*num_canales = 0;

	canales = LINKEDLISTCANALES_create();
	f = fopen ("canales.txt", "r");
	if (f == NULL) {
	
	}
	else {
		programas = programaFileToList();
		fgets(c.nombre, MAX_CHAR_SIMPLE, f);
		while (!feof(f)) {
			c.nombre[strlen(c.nombre) - 1] = '\0';
			fscanf(f, "%f", &c.coste_suscripcion);
			fscanf(f, "%c", &aux);
			fscanf(f, "%d", &c.num_suscriptores);
			fscanf(f, "%c", &aux);
			c.suscriptores = (char **)malloc(sizeof(char *) * c.num_suscriptores);
			if (c.suscriptores == NULL) {
				printf ("\tERROR (El sistema ha caído. Contacte con un administrador en la mayor brevedad posible)\n");
				exit(0);
			}
			else {
				for (int i = 0; i < c.num_suscriptores; i++) {
					fscanf(f, "%s", suscriptor);
					fscanf(f, "%c", &aux);
					c.suscriptores[i] = (char *)malloc((strlen(suscriptor) + 1) * sizeof(char));
					strcpy(c.suscriptores[i], suscriptor);
				}
			}
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
    printf("\tIntroduce hora emision del programa (HH:mm): ");
    fgets(p.emisio, MAX_CHAR_SIMPLE, stdin);
	p.emisio[strlen(p.emisio) - 1] = '\0';
    p.duracio = solicitarFloat("\tIntroduce duracion del programa: ", MINUTOS);

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
    int option, error = 0;
	
	do {
    	printf ("\t1- Crear nuevo canal\n");
    	printf ("\t2- Modificar canal\n");
		printf ("\t3- Eliminar programa\n");
  	 	printf ("\t4- Eliminar canal\n");
    	printf ("\t5- Mostrar canales\n");
		printf ("\t6- Mostrar canales por suscriptores\n");
    	printf ("\t7- Añadir programa\n");
	    printf ("\t8- Mostrar programas\n");
    	printf ("\t9- Volver\n");
	    printf ("\tEnter option: ");
    	error = optionAsNumber(&option, 1, 9);
	} while (error);

    return option;
}

/***********************************************
*
* @Finalidad: Mostrar los canales registrados.
* @Parametros: in: canales = Lista de canales.
* @Retorno: ----.
*
************************************************/
void mostrarCanales () {
    Canal c;
    LinkedList3 canales;
    int num_canales;

    canales = canalesFileToList(&num_canales);
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

    solicitarPalabra("Introduce nombre del programa: ", nombre, NOMBRE_PROGRAMA);
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
PLANNER_Date convertirFormato (char emision[MAX_CHAR_SIMPLE]) {
	PLANNER_Date pd;

	char subHora[3];
    strncpy(subHora, emision, 2);
    subHora[2] = '\0'; // Agregar el carácter nulo al final para formar un string válido

    // Obtener los minutos (posición 3 a 4)
    char subMinuto[3];
    strncpy(subMinuto, emision + 3, 2);
    subMinuto[2] = '\0'; // Agregar el carácter nulo al final para formar un string válido

    // Convertir las subcadenas a enteros usando atoi
    printf ("Hora: %d | Minuto: %d\n", atoi(subHora), atoi(subMinuto));
	pd.hour = atoi(subHora);
	pd.minutes = atoi(subMinuto);	

	return pd;
}

int programasSeSolapan (char nombreCanal[MAX_CHAR_SIMPLE], int duracion, char emision[MAX_CHAR_SIMPLE]) {
	LinkedList4 programa = programaFileToList();
	Programa p;
	PLANNER_Date newPd, oldPd;

	LINKEDLISTPROGRAMA_goToHead(&programa);
	while (!LINKEDLISTPROGRAMA_isAtEnd(programa)) {
		p = LINKEDLISTPROGRAMA_get(&programa);
		if (!strcmp(p.cadena, nombreCanal)) {
	    	newPd = convertirFormato(emision);
			oldPd = convertirFormato(p.emisio);	
			if (PLANNER_isOverlapping(PLANNER_getSeconds(newPd), duracion, PLANNER_getSeconds(oldPd), p.duracio)) {
				return 1;
			}
		}
	}
	return 0;
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
    if (canalUnico(p.cadena, &c)) {
		if (nombreUnico(p.nom, &aux)) {
			if (!programasSeSolapan (p.nom, p.duracio, p.emisio)) {
				printf ("Si\n");
			}	
			for (int i = 0; i < 3; i++) {
    	        p.actorID[i].num = 0;
       		    p.actorID[i].letra = 'a';
	       	}
	        programa = programaFileToList();
			LINKEDLISTPROGRAMA_add(&programa, p);
        	actualizarFicheroPrograma(programa);
	        LINKEDLISTCANALES_add(canales, c);
   		    printf ("Se ha añadido el programa correctamente\n");
		} else {
			printf ("Ya hay un programa con este canal.\n");
		}
	} else {
        printf ("No existe ningun canal con este nombre.\n");
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
	solicitarPalabra("Introduce el nombre del canal a eliminar: ", nombre, NOMBRE);
    eliminarC(&lista, nombre);

}

void eliminarPrograma(LinkedList3 *canales) {
    char nombreCanal[MAX_CHAR_SIMPLE];
    char nombrePrograma[MAX_CHAR_SIMPLE];
	int hay = 0;

    solicitarPalabra("Introduce el nombre del canal: ", nombreCanal, NOMBRE_CANAL);
    solicitarPalabra("Introduce el nombre del programa a eliminar: ", nombrePrograma, NOMBRE_PROGRAMA);

    LINKEDLISTCANALES_goToHead(canales);
    while (!LINKEDLISTCANALES_isAtEnd(*canales)) {
        Canal c = LINKEDLISTCANALES_get(canales);
        if (strcmp(c.nombre, nombreCanal) == 0) {

            LINKEDLISTPROGRAMA_goToHead(&c.programas);
            while (!LINKEDLISTPROGRAMA_isAtEnd(c.programas)) {
                Programa p = LINKEDLISTPROGRAMA_get(&c.programas);
                if (strcmp(p.nom, nombrePrograma) == 0) {
					for (int i = 0; i < 3; i++) {
						if (p.actorID[i].num != 0) {
							hay = 1;
						}
					}
	                if (!hay) {  
						LINKEDLISTPROGRAMA_remove(&c.programas);
    	                printf("Programa \"%s\" eliminado del canal \"%s\".\n", nombrePrograma, nombreCanal);
        	            actualizarFicheroPrograma(c.programas);
            	        return;
                	} else {
						printf ("Hay actores contratados.\n");
						return;
					}
				}
                LINKEDLISTPROGRAMA_next(&c.programas);
            }
            printf("No se encontró el programa \"%s\" en el canal \"%s\".\n", nombrePrograma, nombreCanal);
            return;
        }
        LINKEDLISTCANALES_next(canales);
    }

    printf("No se encontró el canal \"%s\".\n", nombreCanal);
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
* @Finalidad: Ordenar por numero descendente un array.
* @Parametros: 	in: *c = Array de canales a ordenar.
*				in: num_canales = Numero de canales a ordenar.
* @Retorno: ----.
*
************************************************/
void selectionSortSusciptores (Canal *c, int num_canales) {
    Canal minim;
    int i, j, posminim;
    for (j = 0; j < (num_canales - 1); j++) {
        minim = c[j];
        posminim = j;
        for (i = j+1; i < num_canales; i++) {
            if (c[i].num_suscriptores <=  minim.num_suscriptores) {
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
    	printf ("Num suscriptores: %d\n", c[i].num_suscriptores);
	}
}

/***********************************************
*
* @Finalidad: Listar el nombre de canales por orden alfabetico.
* @Parametros: ----.
* @Retorno: ----.
*
************************************************/
void visualizarCanalesPorSuscriptores () {
    int num_canales;
    Canal *c;

    c = listaAArrayDinamico(&num_canales);
    selectionSortSusciptores(c, num_canales);
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
            array[i].num_suscriptores = c.num_suscriptores;
			i++;
            LINKEDLISTCANALES_next(&canales);
        }
    }
    return array;
}

/***********************************************
*
* @Finalidad: Verificar si un usuario se encuentra suscrito a un canal.
* @Parametros:	in: c = Canal a verificar la suscripcion.
*				in: usuario[] = Correo del usuario a verificar.
* @Retorno: Retorna un 1 si el usuario se encuentra suscrito al canal y un 0 si no lo esta.
*
************************************************/
int usuarioAsignado (Canal c, char usuario[MAX_CHAR_SIMPLE], int *i) {

    for (*i = 0; *i < c.num_suscriptores; (*i)++) {
        if (!strcmp(c.suscriptores[*i], usuario)) {
            return 1;
        }
    }

    return 0;
}

/***********************************************
*
* @Finalidad: Asignar el correo de un usuario como suscriptor de un canal.
* @Parametros:	in: canal[] = Nombre del canal a asignar el usuario.
*				in: usuario[] = Correo del usuario a asignar.
* @Retorno: ----.
*
************************************************/
void asignarUsuarioACanal(char canal[MAX_CHAR_SIMPLE], char usuario[MAX_CHAR_SIMPLE]) {
    LinkedList3 canales;
    int num_canales, found = 0, i;
    Canal c;

    canales = canalesFileToList(&num_canales);
    LINKEDLISTCANALES_goToHead(&canales);
    while (!LINKEDLISTCANALES_isAtEnd(canales) && !found) {
        c = LINKEDLISTCANALES_get(&canales);
        if (!strcmp(c.nombre, canal)) {
            found = 1;
            if (!usuarioAsignado(c, usuario, &i)) {
                c.num_suscriptores++;
                c.suscriptores = realloc(c.suscriptores, sizeof(char *) * c.num_suscriptores);
                c.suscriptores[c.num_suscriptores - 1] = (char *)malloc(sizeof(char) * (strlen(usuario) + 1));
                strcpy(c.suscriptores[c.num_suscriptores - 1], usuario);
                LINKEDLISTCANALES_remove(&canales);
                LINKEDLISTCANALES_add(&canales, c);
                actualizarFicheroCanales(canales);
                printf ("La suscripcion se ha efectuado correctamente. Ya tiene acceso a todos los programas de %s.\n", c.nombre);
            }
            else {
                printf ("\tERROR (Ya hay una suscripcion activa a este canal con esta cuenta)\n");
            }
        }
        else {
            LINKEDLISTCANALES_next(&canales);
        }
    }

}

/***********************************************
*
* @Finalidad: Eliminar el correo de un usuario como suscriptor de un canal.
* @Parametros:	in: canal[] = Nombre del canal a eliminar el usuario.
*				in: usuario[] = Correo del usuario a eliminar.
* @Retorno: ----.
*
************************************************/
void retirarUsuarioDeCanal (char canal[MAX_CHAR_SIMPLE], char usuario[MAX_CHAR_SIMPLE]) {
    LinkedList3 canales;
    int num_canales, found = 0, i;
    Canal c;

    canales = canalesFileToList(&num_canales);
    LINKEDLISTCANALES_goToHead(&canales);
    while (!LINKEDLISTCANALES_isAtEnd(canales) && !found) {
        c = LINKEDLISTCANALES_get(&canales);
        if (!strcmp(c.nombre, canal)) {
            found = 1;
            if (usuarioAsignado(c, usuario, &i)) {
                free(c.suscriptores[i]);
                c.num_suscriptores--;
                LINKEDLISTCANALES_remove(&canales);
                LINKEDLISTCANALES_add(&canales, c);
                actualizarFicheroCanales(canales);
            }
            else {
                printf ("\tERROR (No hay una suscripcion activa a '%s' con esta cuenta)\n", canal);
            }
        }
    }
}

/***********************************************
*
* @Finalidad: Genera la programacion de un canal.
* @Parametros:	in: c = Estructura canal de donde extraer la programacion.
* @Retorno: ----.
*
************************************************/
void generarProgramacion (Canal c) {
	FILE *f;
	Programa p;
	int i;
	char nombre[MAX_CHAR_SIMPLE] = "programacion";
		
	strcat(nombre, c.nombre);
	strcat(nombre, ".txt");
	f = fopen (nombre, "w");	
	if (f == NULL) {
		printf ("\tERROR (La programacion no se ha podido descargar correctamente)\n");
	}
	else {
		fprintf (f, "\t\tPROGRAMACION %s\n", c.nombre);
		fprintf (f, "----------------------------------------------\n");
		LINKEDLISTPROGRAMA_goToHead(&c.programas);
		while (!LINKEDLISTPROGRAMA_isAtEnd(c.programas)) {
			p = LINKEDLISTPROGRAMA_get(&c.programas);
			fprintf (f, "Hora de emision: %s\n", p.emisio);
			fprintf (f, "Nombre del programa: %s\n", p.nom);
			fprintf (f, "Categoria: %s\n", p.categoria);
			fprintf (f, "Duracio: %d minutos\n", p.duracio);
			for (i = 0; i < 2; i++) {
				fprintf (f, "\n");
			}
			LINKEDLISTPROGRAMA_next(&c.programas);
		}
		fclose(f);
	}
}

void modificarCanal (LinkedList3 *canales) {
	char nombre[MAX_CHAR_SIMPLE], nombreNuevo[MAX_CHAR_SIMPLE];
	float nuevoPrecio;
	int error, option;

	Canal c, aux;
	solicitarPalabra("Introduce nombre del canal a modificar: ", nombre, NOMBRE);
	if (canalUnico(nombre, &aux)) {
		do {	
			printf ("1- Modificar nombre\n");
			printf ("2- Modificar coste\n");
			printf ("3- Atras\n");
			printf ("Entra opcion: ");
			error =	optionAsNumber(&option, 1, 3);
		} while (error);
		switch (option) {
			case 1: 
				printf ("El nombre actual es %s\n", aux.nombre);
				solicitarPalabra("Introduce el nombre del canal: ", nombreNuevo, NOMBRE);
				if (strcmp(nombreNuevo, nombre) != 0) {
					if (!canalUnico(nombreNuevo, &aux)) {
						LINKEDLISTCANALES_goToHead(canales);
						while (!LINKEDLISTCANALES_isAtEnd(*canales)) {
							c = LINKEDLISTCANALES_get(canales);
							if (!strcmp(c.nombre, nombre)) {
								strcpy(c.nombre, nombreNuevo);
								LINKEDLISTCANALES_remove(canales);
								LINKEDLISTCANALES_add(canales, c);
								actualizarFicheroCanales(*canales);
								printf ("Se ha actualizado el nombre correctamente.\n");
								break;
							} else {
								LINKEDLISTCANALES_next(canales);
							}
						}
					}
					else {
						printf ("El nombre introducido ya pertenece a otro canal.\n");
					}
				}
				else {
					printf ("Debes introducir un nombre diferente al anterior.\n");
				}
				break;
			case 2:
				printf ("El precio de suscripcion actual del canal es %.2f euros.\n", aux.coste_suscripcion);
				do {
					nuevoPrecio = solicitarFloat("Introduce nuevo costo: ", COSTE_SUSCRIPCION);
					if (nuevoPrecio < 0) {
						printf ("ERROR: Debes introducir un numero positivo.\n");
					}
				} while (nuevoPrecio < 0);
					LINKEDLISTCANALES_goToHead(canales);
					while (!LINKEDLISTCANALES_isAtEnd(*canales)) {
						c = LINKEDLISTCANALES_get(canales);
						if (!strcmp(c.nombre, nombre)) {
							c.coste_suscripcion = nuevoPrecio;
							LINKEDLISTCANALES_remove(canales);
							LINKEDLISTCANALES_add(canales, c);
							actualizarFicheroCanales(*canales);
							printf ("Se ha actualizado el coste de suscripcion correctamente.\n");
							break;
						} else {
							LINKEDLISTCANALES_next(canales);
						}
					}
		}
	}
	else {
		printf ("ERROR: El canal introducido no existe.\n");
	}
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
	LinkedList4 programa = programaFileToList();
    canales = canalesFileToList(&num_canales);
    switch (option) {
        case 1:
            crearCanal(&canales);
            break;
		case 2:
			modificarCanal(&canales);
			break;
        case 3:
            eliminarPrograma(&canales);
            break;
        case 4:
            eliminarCanal();
            break;
        case 5:
            mostrarCanales();
            break;
		case 6:
			visualizarCanalesPorSuscriptores();
        	break;
		case 7:
            anadirProgramaACanal(&canales);
            break;
        case 8:
            mostraProgramas(programa);
            break;
        case 9:
            *quit = 1;
            break;
    }

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
