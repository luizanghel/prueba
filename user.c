#include "user.h"
#include <time.h>

/***********************************************
*
* @Finalidad: Solicitar un DNI para un usuario.
* @Parametros:	in: texto[] = Texto que se mostrara para la solicitud.
* @Retorno: Devuelve el conjunto del DNI del usuario.
* 
************************************************/
Dni solicitarDni (char texto[MAX_CHAR_SIMPLE]) {
    char palabra[MAX_CHAR_SIMPLE];
    Dni dni;
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
* @Finalidad: Solicitar los campos para poder iniciar el registro de un usuario.
* @Parametros: ----.
* @Retorno: Devuelve un tipo persona con los campos rellenados.
*
************************************************/
Persona requestData () {
    Persona p;

    printf ("Registro: Rellena todos los campos que aparecen a continuación:\n");
    solicitarPalabra("Nombre: ", p.nombre, 0);
    solicitarPalabra("Primer apellido: ", p.apellido1, 1);
    solicitarPalabra("Segundo apellido: ", p.apellido2, 2);
    p.dni = solicitarDni("DNI: ");
    solicitarCorreo("Correo: ", p.correo);
    solicitarContrasena("Contraseña: ", p.password);
    p.telefono = solicitarTelefono("Numero de telefono: ", 9);
    strcpy(p.tarjeta.titular, "-");
    p.tarjeta.numero = 0;
    p.tarjeta.pin = 0;

    return p;
}

/***********************************************
*
* @Finalidad: Leer el contenido del tipo persona.
* @Parametros: in: p = Tipo persona completo.
* @Retorno: Muestra por pantalla el contenido del tipo persona.
*
************************************************/
void leerPersona (Persona p) {
    printf("Nombre: %s.\n", p.nombre);
    printf("Apellido: %s.\n", p.apellido1);
    printf("Apellido 2: %s.\n", p.apellido2);
    printf("Correo: %s.\n", p.correo);
    printf("Contrasena: %s.\n", p.password);
    printf("Telefon: %d.\n", p.telefono);
    printf("DNI: %d%c.\n", p.dni.numeros, p.dni.letra);
    printf ("Titular de tarjeta: %s.\n", p.tarjeta.titular);
    printf ("Numero tarjeta: %d\n", p.tarjeta.numero);
    printf ("PIN: %d\n", p.tarjeta.pin);
}

/***********************************************
*
* @Finalidad: Muestra el contenido de una lista.
* @Parametros: in: usuarios = Lista a mostrar.
* @Retorno: ----.
*
************************************************/
void mostrarLista(LinkedList usuarios) {
    Persona p;
    int n_clients = 0;
    LINKEDLIST_goToHead(&usuarios);
    while (!LINKEDLIST_isAtEnd(usuarios)) {
        p =	LINKEDLIST_get(&usuarios);
        if (p.tipus == 0) {
            n_clients++;
            printf ("-CLIENTE %d-\n", n_clients);
            printf ("\tNombre: %s\n", p.nombre);
            printf ("\tPrimer apellido: %s\n", p.apellido1);
            printf ("\tSegundo apellido: %s\n", p.apellido2);
            printf ("\tCorreo: %s\n", p.correo);
            printf ("\tContraseña: %s\n", p.password);
        }

        LINKEDLIST_next(&usuarios);
    }
    printf ("Hay %d clientes registrados.\n", n_clients);
}

/***********************************************
*
* @Finalidad: Crear una LinkedList a partir de la informacion procedente de un fichero.
* @Parametros: ----.
* @Retorno: Retorna la LinkedList con la informacion del fichero..
*
************************************************/
LinkedList ficheroALista () {
    LinkedList users_list;
    FILE *users = NULL;
    char aux;
    Persona p;

    users_list = LINKEDLIST_create();
    users = fopen("clients.txt", "r");
    if (users == NULL) {
	
	}
    else {
        fscanf(users, "%d", &p.dni.numeros);
        while (!feof(users)) {
            fscanf(users, "%c", &p.dni.letra);
            fscanf(users, "%c", &aux);
            fgets(p.nombre, MAX_CHAR_SIMPLE, users);
            p.nombre[strlen(p.nombre) - 1] = '\0';
            fgets(p.apellido1, MAX_CHAR_SIMPLE, users);
            p.apellido1[strlen(p.apellido1) - 1] = '\0';
            fgets(p.apellido2, MAX_CHAR_SIMPLE, users);
            p.apellido2[strlen(p.apellido2) - 1] = '\0';
            fgets(p.correo, MAX_CHAR_SIMPLE, users);
            p.correo[strlen(p.correo) - 1] = '\0';
            fscanf(users, "%s", p.password);
            fscanf (users, "%c", &aux);
            fgets(p.tarjeta.titular, MAX_CHAR_SIMPLE, users);
            p.tarjeta.titular[strlen(p.tarjeta.titular) - 1] = '\0';
            fscanf(users, "%d", &p.tarjeta.numero);
            fscanf(users, "%d", &p.tarjeta.pin);
            fscanf(users, "%d", &p.telefono);
            fscanf(users, "%d", &p.tipus);
            /*printf ("DNI: %d%c\n", p.dni.numeros, p.dni.letra);
            printf ("Nombre: %s\n", p.nombre);
            printf ("Primer apellido: %s\n", p.apellido1);
            printf ("Segundo apellido: %s\n", p.apellido2);
            printf ("Correo: %s\n", p.correo);
            printf ("Contraseña: %s\n", p.password);
            printf ("Titular tarjeta: %s\n", p.tarjeta.titular);
            printf ("Numero tarjeta: %d\n", p.tarjeta.numero);
            printf ("PIN tarjeta: %d\n", p.tarjeta.pin);
            */
            LINKEDLIST_add(&users_list, p);
            fscanf(users, "%d", &p.dni.numeros);
        }
        fclose(users);
    }
    return users_list;
}

/***********************************************
*
* @Finalidad: Verificar si no hay registrados correos iguales.
* @Parametros: 	in: correo[] = Correo a comprobar
*				in: *usuarios = Lista donde se busca el resto de correos.
* @Retorno: Retorna un 1 en caso que el correo sea unico, mientras que retorna un 0 si no lo es.
*
************************************************/
int esPersonaUnica (char correo[MAX_CHAR_SIMPLE], LinkedList *usuarios) {
    Persona p;
    int error = 0;

    LINKEDLIST_goToHead(usuarios);
    while (!LINKEDLIST_isAtEnd(*usuarios) && !error) {
        p =	LINKEDLIST_get(usuarios);
        if (!strcmp(p.correo, correo)) {
            error = 1;
        }
        else {
            LINKEDLIST_next(usuarios);
        }
    }
    return error;
}

/***********************************************
*
* @Finalidad: Verificar si un usuario es cliente o productor.
* @Parametros: in: dni = Dato que identifica si un usuario es cliente o productor.
* @Retorno: Retorna un 1 en caso que sea un productor y un 0 si es un cliente.
*
************************************************/
int tipoUsuario (Dni dni) {
    FILE *id_productores = NULL;
    int numero, tipo = 0;
    char letra, aux;

    id_productores = fopen("productors.txt", "r");
    if (id_productores == NULL) {
		tipo = 0;
	}
    else {
        fscanf(id_productores, "%d", &numero);
        while (!feof(id_productores)) {
            fscanf (id_productores, "%c", &letra);
            if (numero == dni.numeros && letra == dni.letra) {
                tipo = 1;
            }
            fscanf (id_productores, "%c", &aux);
            fscanf (id_productores, "%d", &numero);
        }
        fclose(id_productores);
    }
    return tipo;
}

/***********************************************
*
* @Finalidad: Escribir el contenido de una lista en un fichero.
* @Parametros: in: usuarios = Lista de donde saca la informacion.
* @Retorno: ----.
*
************************************************/
void actualizarFichero (LinkedList usuarios) {
    FILE *actualizado = NULL;
    Persona p;

    actualizado = fopen("nuevo.txt", "w");
    if (actualizado == NULL) {
        printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
    	exit(0);
	}
    else {
        LINKEDLIST_goToHead(&usuarios);
        while (!LINKEDLIST_isAtEnd(usuarios)) {
            p = LINKEDLIST_get(&usuarios);
            fprintf(actualizado, "%d%c\n", p.dni.numeros, p.dni.letra);
            fprintf(actualizado, "%s\n", p.nombre);
            fprintf(actualizado, "%s\n", p.apellido1);
            fprintf(actualizado, "%s\n", p.apellido2);
            fprintf(actualizado, "%s\n", p.correo);
            fprintf(actualizado, "%s\n", p.password);
            fprintf(actualizado, "%s\n", p.tarjeta.titular);
            fprintf(actualizado, "%d\n", p.tarjeta.numero);
            fprintf(actualizado, "%d\n", p.tarjeta.pin);
            fprintf(actualizado, "%d\n", p.telefono);
            fprintf(actualizado, "%d\n", p.tipus);
            LINKEDLIST_next(&usuarios);
        }
        fclose(actualizado);
        remove("clients.txt");
        rename("nuevo.txt", "clients.txt");
    }

}

/***********************************************
*
* @Finalidad: Solicita los datos del usuario para proceder con el registro..
* @Parametros: ----.
* @Retorno: ----.
*
************************************************/
Persona registerUser (int *completado) {
    Persona p;
    int error = 0;
    LinkedList usuarios;

    p = requestData();
    usuarios = ficheroALista();
    error = esPersonaUnica(p.correo, &usuarios);
    if (!error) {
        p.tipus = tipoUsuario(p.dni);
        LINKEDLIST_add(&usuarios, p);
        actualizarFichero(usuarios);
        *completado = 1;
        printf ("\n¡Registro completado!. Bienvenido/a %s.\n", p.nombre);
    }
    else {
        printf ("\nEl correo ya esta en uso. Vuelva a intentarlo o inicie sesión.\n");
    }

    return p;
}

/***********************************************
*
* @Finalidad: Verifica si existe el usuario.
* @Parametros: 	in: correo[] = Correo a verificar.
				in: password[] = Contraseña a verificar.
				out: *existe = Indica si la persona ha sido encontrada o no.
* @Retorno: Retorna los datos completos en caso que el usuario exista. Sino, se ignoran.
*
************************************************/
Persona existeUsuario(char correo[MAX_CHAR_SIMPLE], char password[MAX_CHAR_SIMPLE], int *existe) {
    Persona p;
    LinkedList usuarios;

    *existe = 0;
    usuarios = ficheroALista();
    LINKEDLIST_goToHead(&usuarios);
    while (!LINKEDLIST_isAtEnd(usuarios) && !*existe) {
        p = LINKEDLIST_get(&usuarios);
        if (!strcmp(correo, p.correo) && !strcmp(password, p.password)) {
            *existe = 1;
        }
        else {
            LINKEDLIST_next(&usuarios);
        }
    }
    return p;
}

/***********************************************
*
* @Finalidad: Iniciar sesion en el sistema.
* @Parametros: ----.
* @Retorno: Los datos de la persona.
*
************************************************/
Persona iniciarSesion(int *existe) {
    Persona p, usuario;

    *existe = 0;

    printf ("Registro: Rellena todos los campos que aparecen a continuación:\n");
    solicitarCorreo("Introduce correo: ", p.correo);
    solicitarContrasena("Introduce contraseña: ", p.password);
    usuario = existeUsuario(p.correo, p.password, existe);
    if (*existe) {
        printf ("\n¡Inicio de sesion completado!. Bienvenido/a %s.\n", usuario.nombre);
    }
    else {
        printf ("\nEl correo electronico o la contraseña son incorrectos. Vuelva a intentarlo o registrese.\n");
    }

    return usuario;
}

int menuProductorClientes () {
    int option, error = 0;

    do {
        printf ("\t1- Visualizar clientes\n");
        printf ("\t2- Modificar clientes\n");
        printf ("\t3- Eliminar clientes\n");
        printf ("\t4- Salir\n");
        printf ("\tEnter option: ");
        error = optionAsNumber(&option, 1, 4);
    } while (error);

    return option;
}

int menuModificacion() {
    int option, error = 0;

    do {

        printf ("\tQue deseas modificar?\n");
        printf ("\t  1- Nombre\n");
        printf ("\t  2- Primer apellido\n");
        printf ("\t  3- Segundo apellido\n");
        printf ("\t  4- Correo\n");
        printf ("\t  5- Contraseña\n");
        printf ("\t  6- Numero de telefono\n");
        printf ("\t  7- Salir\n");
        printf ("\t  Enter option: ");
        error = optionAsNumber(&option, 1, 7);

    } while (error);

    return option;
}

void runOption (int option, Persona *p) {
    char cambio[MAX_CHAR_SIMPLE];
    int numero;

    switch (option) {
        case 1:
            printf ("Su nombre actual es %s.", p->nombre);
            solicitarPalabra("Introduce nombre a modificar: ", cambio, option--);
            strcpy(p->nombre, cambio);
            break;
        case 2:
            printf ("Su primer apellido actual es %s.", p->apellido1);
            solicitarPalabra("Introduce primer apellido a modificar: ", cambio, option--);
            strcpy(p->apellido1, cambio);
            break;
        case 3:
            printf ("Su segundo apellido actual es %s.", p->apellido2);
            solicitarPalabra("Introduce segundo apellido a modificar: ", cambio, option--);
            strcpy(p->apellido2, cambio);
            break;
        case 4:
            printf ("Su correo actual es %s.", p->correo);
            solicitarCorreo("Introduce correo a modificar: ", cambio);
            strcpy(p->correo, cambio);
            break;
        case 5:
            printf ("Su contraseña actual es %s.", p->password);
            solicitarContrasena("Introduce contraseña a modificar: ", cambio);
            strcpy(p->password, cambio);
            break;
        case 6:
            printf ("Su numero de telefono actual es %d.", p->telefono);
            numero = solicitarTelefono("Introduce telefono a modificar: ", 9);
            p->telefono = numero;
            break;
    }
}

void modificarClientes (LinkedList *users) {
    int option, found;
    Persona p;
    char correo[MAX_CHAR_SIMPLE], tipo[6][MAX_CHAR_SIMPLE] = {"nombre", "primer apellido", "segundo apellido", "correo", "contraseña", "numero de telefono"};

    do {
        mostrarLista(*users);
        option = menuModificacion();
        if (option != 7) {
            solicitarCorreo("Introduce el correo del usuario: ", correo);
            found = 0;
            LINKEDLIST_goToHead(users);
            while (!LINKEDLIST_isAtEnd(*users) && !found) {
                p = LINKEDLIST_get(users);
                if (!strcmp(p.correo, correo) && p.tipus == 0) {
                    found = 1;
                    runOption(option, &p);
                    LINKEDLIST_remove(users);
                    LINKEDLIST_add(users, p);
                }
                else {
                    LINKEDLIST_next(users);
                }
            }
            if (!found) {
                printf ("ERROR (No se ha encontrado ningun usuario con este correo).\n");
            }
            else {
                actualizarFichero(*users);
                printf ("El %s de %s ha sido modificado correctamente.\n", tipo[option-1], correo);

            }
        }
    } while (option != 7);
}

void eliminarClientes () {
    LinkedList users;
    int found = 0;
    Persona p;
    char correo[MAX_CHAR_SIMPLE];

    solicitarCorreo("Introduce el correo del usuario a eliminar: ", correo);
    users = ficheroALista();
    LINKEDLIST_goToHead(&users);
    while (!LINKEDLIST_isAtEnd(users) && !found) {
        p = LINKEDLIST_get(&users);
        if (!strcmp(p.correo, correo) && p.tipus == 0) {
            LINKEDLIST_remove(&users);
            found = 1;
        }
        LINKEDLIST_next(&users);
    }
    if (!found) {
        printf ("\tNo se ha encontrado ningun cliente con el correo que ha adjuntado.\n");
    }
    else {
        printf ("Se he eliminado correctamente el usuario adscrito al correo %s.\n", correo);
        actualizarFichero(users);
    }
}

void modoProductorClientes() {
    int option, quit = 0;
    LinkedList clients;

    do {

        option = menuProductorClientes();
        clients = ficheroALista();

        switch (option) {
            case 1:
                mostrarLista(clients);
                break;
            case 2:
                modificarClientes(&clients);
                break;
            case 3:
                eliminarClientes();
                break;
            case 4:
                quit = 1;
                break;
        }
    } while (!quit);
}

int menuProductorGeneral() {
    int option, error = 0;

    do {
        printf ("Bienvenido al MENU PRODUCTOR. ¿Que deseas realizar?\n");
        printf ("1- Gestionar clientes\n");
        printf ("2- Gestionar canales\n");
        printf ("3- Gestionar actores\n");
        printf ("4- Gestionar peliculas\n");
        printf ("5- Gestionar anuncios\n");
        printf ("6- Cerrar sesión\n");
        printf ("Entra opcion: ");
        error = optionAsNumber(&option, 1, 6);
    } while (error);

    return option;
}

int menuPeliculas () {
    int option, error = 0;

    do {
        printf ("\t1- Añadir peliculas\n");
        printf ("\t2- Eliminar peliculas\n");
        printf ("\t3- Visualizar peliculas\n");
        printf ("\t4- Salir\n");
        printf ("\tEntra opcion: ");
        error = optionAsNumber(&option, 1, 4);
    } while (error);

    return option;
}

void modoProductorPeliculas () {
	int option;

	do {
		
		option = menuPeliculas();
		switch (option) {
			case 1:
				anadirPelicula();
				break;
			case 2:
				eliminarPelicula();
				break;
			case 3:
				listarPeliculas();
				break;
		}

	} while (option != 4);
}

int solicitarVerificacion () {
	int quit = 0;
	char confirmacion[MAX_CHAR_SIMPLE];
	do {
		printf ("Esta seguro que quiere cerrar sesion? ");
		fgets(confirmacion, MAX_CHAR_SIMPLE, stdin);
		confirmacion[strlen(confirmacion) - 1] = '\0';
		todoAMinusculas(confirmacion);
	} while (strcmp(confirmacion, "si") && strcmp(confirmacion, "no"));

	if (!strcmp(confirmacion, "si")) {
		printf ("Se estan guardando los datos...Cerrando sesion...\n");
		quit = 1;
	}
	return quit;
}

void modoProductor () {
	int option, quit = 0;
	
	do {
		option = menuProductorGeneral();
		switch (option) {
			case 1:
				modoProductorClientes();
				break;
			case 2:
				menuCanales();
				break;
			case 3:
				menuActors();
				break;
			case 4:
				modoProductorPeliculas();
				break;
			case 6:
				quit = solicitarVerificacion();
				break;
		} 
	} while (!quit);
}

int menuCliente () {
    int error = 0, option;

    do {
        printf ("Bienvenido al MENU CLIENTE. ¿Que desea realizar?\n");
        printf ("1- Registrar tarjeta\n");
        printf ("2- Listar programas de un canal\n");
		printf ("3- Visualizar canales por audiencia\n");
		printf ("4- Listar programas que el  usuario esta suscrito\n");
		printf ("5- Buscar programa por nombre\n");
		printf ("6- Suscribirse a un canal\n");
		printf ("7- Cancelar suscripcion a un canal\n");
		printf ("8- Visualizar programacion\n");
		printf ("9- Descargar programacion de un canal\n");
        printf ("10- Visualizar peliculas\n");
        printf ("11- Comprar la pelicula\n");
      	printf ("12- Eliminar cuenta\n");
		printf ("13- Salir\n");
		//printf ("14- Solicita la verificación\n");
		printf ("Entra opcion: ");
        error = optionAsNumber(&option, 1, 13);
    } while (error);

    return option;
}

void registroTarjeta(Persona *p) {
    LinkedList users;
    Persona estructura;
    users = ficheroALista();
    int found = 0;

    if (p->tarjeta.numero != 0) {
        printf ("\tERROR (Ya tienes una tarjeta asignada)\n\n)");
    }
    else {
        printf ("\tInserta titular de la tarjeta: ");
        fgets(p->tarjeta.titular, MAX_CHAR_SIMPLE, stdin);
        p->tarjeta.titular[strlen(p->tarjeta.titular) - 1] = '\0';
        p->	tarjeta.numero = solicitarTelefono("\tIntroduce numero de tarjeta: ", 10);
        p->tarjeta.pin = solicitarTelefono("\tPIN: ", 4);
        LINKEDLIST_goToHead(&users);
        while (!LINKEDLIST_isAtEnd(users) && !found) {
            estructura = LINKEDLIST_get(&users);
            if (p->dni.numeros == estructura.dni.numeros && p->dni.letra == estructura.dni.letra) {
                found = 1;
                LINKEDLIST_remove(&users);
                LINKEDLIST_add(&users, *p);
            }
            LINKEDLIST_next(&users);
        }
        actualizarFichero(users);
        printf ("La tarjeta se ha añadido correctamente!\n");
    }
}

void listarprogramas(char canal[50]){
    FILE *f;
    LinkedList4 programa;
    Programa p;
    int i=0;

    f=fopen("programas.txt", "r");
    if (f==NULL){
        printf("ERROR, no existe este archivo\n");
    }else{
        programa=programaFileToList();
        LINKEDLISTPROGRAMA_goToHead(&programa);
        while (!LINKEDLISTPROGRAMA_isAtEnd(programa)){
            p=LINKEDLISTPROGRAMA_get(&programa);
            if (strcmp(p.cadena, canal)==0){
                if (i==0){
                    printf("Los programas de este canal son:\n");
                }
                i=1;
                printf("Nom: %s Categoria: %s Hora: %s\n", p.nom, p.categoria, p.emisio);
            }
            LINKEDLISTPROGRAMA_next(&programa);
        }
        if (i==0){
            printf("No hay programas registrados en este canal\n");
        }
        fclose(f);
    }
}

void mostrarprog(){
    char canal[50];
    int trobat=0;
    FILE *f;
    LinkedList3 canales;
    Canal c;

    solicitarPalabra("Que canal quieres mostrar? ", canal, NOMBRE_CANAL);

    f= fopen("canales.txt", "r");
    if (f==NULL){
        printf("ERROR, no existe este archivo\n");
    }else{
        canales = canalesFileToList(&trobat);
        trobat = 0;
        LINKEDLISTCANALES_goToHead(&canales);
        while (!LINKEDLISTCANALES_isAtEnd(canales) && !trobat){
            c = LINKEDLISTCANALES_get(&canales);
            if (strcmp(c.nombre, canal)==0){
                trobat=1;
                listarprogramas(canal);
            }
            else {
                LINKEDLISTCANALES_next(&canales);
            }
        }
        if (!trobat){
            printf("Este canal no existe\n");
        }
        fclose(f);
    }

}

/***********************************************
*
* @Finalidad: Listar el nombre de canales por orden alfabetico.
* @Parametros: ----.
* @Retorno: ----.
*
************************************************/
void visualizarCanales () {
    int num_canales;
    Canal *c;

    c = listaAArrayDinamico(&num_canales);
    selectionSort(c, num_canales);
}

/***********************************************
*
* @Finalidad: Suscribir un nombre a un canal.
* @Parametros: in: p = Persona a suscribir.
* @Retorno: ----.
*
************************************************/
void suscribirseACanal (Persona p) {
    char canal[MAX_CHAR_SIMPLE], opcion;
    Canal c;
    int pin;

    printf ("--Canales disponibles--\n");
    mostrarCanales();
    solicitarPalabra("\nIntroduce canal a suscribirte: ", canal, 0);
    if (canalUnico(canal, &c)) {
        printf ("El coste de suscripcion del canal '%s' es de %.2f\n", c.nombre, c.coste_suscripcion);

        if (p.tarjeta.numero != 0) {

            do {
                pin = solicitarTelefono("Introduce pin de la tarjeta: ", 4);
            } while (pin != p.tarjeta.pin);

            printf ("Esta seguro que quiere suscribirse al canal '%s' con un coste de %.2f? La transaccion se efectuara en la tarjeta %d.\n", c.nombre, c.coste_suscripcion, p.tarjeta.numero);
            opcion = solicitarCaracter("Introduce una de las posibles opciones (S/N): ");

            if (opcion == 'S') {

                asignarUsuarioACanal(c.nombre, p.correo);
            }
            else {
                printf ("Se ha cancelado la transaccion.\n");
            }
        }
        else {
            printf ("\tERROR (Antes de suscribirte a un canal, debes tener una tarjeta registrada)\n");
        }
    }
    else {
        printf ("\tERROR (El canal que ha introducido no existe)\n");
    }
}

void eliminarSuscripcion (Persona p) {
    char canal[MAX_CHAR_SIMPLE];
    Canal c;

    solicitarPalabra("Introduzca el nombre del canal donde quiere cancelar la suscripcion: ", canal, NOMBRE_CANAL);
    if (canalUnico(canal, &c)) {
        retirarUsuarioDeCanal(canal, p.correo);
    }
    else {
        printf ("\tERROR (El nombre del canal que ha introducido no existe)\n");
    }
}

/***********************************************
 * @Finalidad: Buscar un programa por nombre en el canal al que está suscrito el usuario.
 * @Parametros:  in: usuario = Correo del usuario.
 * @Retorno: ----.
 ************************************************/
void buscarPrograma(char usuario[MAX_CHAR_SIMPLE]) {
    char nombrePrograma[MAX_CHAR_SIMPLE];
    LinkedList3 canales;
	LinkedList4 programas;
	Programa p;
    Canal c;
    int encontrado = 0;
	int num_canales,i;

   	solicitarPalabra("Introduce el nombre del programa a buscar: ", nombrePrograma, MAX_CHAR_SIMPLE);
    
	canales = canalesFileToList(&num_canales);
    programas = programaFileToList();

    LINKEDLISTCANALES_goToHead(&canales);

    while (!LINKEDLISTCANALES_isAtEnd(canales)) {
        c = LINKEDLISTCANALES_get(&canales);
        if (usuarioAsignado(c, usuario, &i)) { // Verificar si el usuario está suscrito al canal
            LINKEDLISTPROGRAMA_goToHead(&programas);
            while (!LINKEDLISTPROGRAMA_isAtEnd(programas)) {
                p = LINKEDLISTPROGRAMA_get(&programas);
                if (strcmp(p.nom, nombrePrograma) == 0) {
                    encontrado = 1;
                    printf("Programa encontrado en el canal '%s':\n", c.nombre);
                    printf("Nombre: %s\n", p.nom);
                    printf("Categoria: %s\n", p.categoria);
                    printf("Hora de emisión: %s\n", p.emisio);
                    break;
                }
                LINKEDLISTPROGRAMA_next(&programas);
            }
       }
       LINKEDLISTCANALES_next(&canales);
    }
   	LINKEDLISTPROGRAMA_destroy(&programas); // Liberar memoria de la lista de programaºs
    LINKEDLISTCANALES_destroy(&canales); // Liberar memoria de la lista de canales

    if (!encontrado) {
        printf("Programa no encontrado en los canales a los que estás suscrito.\n");
    }
}

void descargarProgramacion (Persona p) {
    char canal[MAX_CHAR_SIMPLE];
    Canal c;
    int i;
    solicitarPalabra("Introduce canal: ", canal, NOMBRE_CANAL);
    if (canalUnico(canal, &c)) {
        if (usuarioAsignado(c, p.correo, &i)) {
            LINKEDLISTPROGRAMA_goToHead(&c.programas);
            if (!LINKEDLISTPROGRAMA_isAtEnd(c.programas)) {
                generarProgramacion(c);
            }
            else {
                printf ("\tERROR (El canal seleccionado no dispone de programas actualmente)\n");
            }
        }
        else {
            printf ("\tERROR (Para descargar la programacion de un canal, debes estar suscrito)\n");
        }
    }
    else {
        printf ("\tERROR (El canal que ha introducido no existe)\n");
    }
}

void verProgramario() {
    char canalName[100];
    printf("Ingrese nombre del canal: ");
    fgets(canalName, 100, stdin);
    canalName[strcspn(canalName, "\n")] = '\0';

    char tiempo[100];
    printf("Ingrese la hora actual (HH:mm): ");
    fgets(tiempo, 100, stdin);
    tiempo[strcspn(tiempo, "\n")] = '\0';

    int horaActual, minutoActual;
    sscanf(tiempo, "%d:%d", &horaActual, &minutoActual);
    LinkedList4 programa;
    programa = programaFileToList();
    Programa p;


    LINKEDLISTPROGRAMA_goToHead(&programa);
    while (!LINKEDLISTPROGRAMA_isAtEnd(programa)) {
        p = LINKEDLISTPROGRAMA_get(&programa);

        int tiempoActual, tiempoPrograma, minutoPrograma, horaPrograma;
        tiempoActual = 60*horaActual + minutoActual;
        sscanf(p.emisio, "%d:%d", &horaPrograma, &minutoPrograma);
        tiempoPrograma = 60*horaPrograma + minutoPrograma;
        if(strcmp(p.cadena, canalName) == 0 && tiempoActual <= tiempoPrograma) {
            printf("\nNombre: %s\n", p.nom);
            printf("Canal: %s\n", p.cadena);
            printf("Categoria: %s\n", p.categoria);
            printf("Emision: %s\n", p.emisio);
            for (int i = 0; i < 3; i++) {
                printf("Actor -> [Numero: %d.] | [Letra: %c.]\n", p.actorID[i].num, p.actorID[i].letra);
            }
        }
        LINKEDLISTPROGRAMA_next(&programa);
    }
    printf("\n");
}

void ordenacionPeliculas () {
	Pelicula *peli = NULL;
	int num_peliculas;
	
	peli = leerPeliculas(&num_peliculas);
	if (num_peliculas != 0) {
		selectionSortPelicula(peli, num_peliculas);
	}
	else {
		printf ("\tERROR (No hay peliculas disponible actualmente)\n");
	}
}

void comprarPelicula (Persona p) {
	char peli[MAX_CHAR_SIMPLE];
	int num_peliculas, posicion;
	Pelicula *peliculas = leerPeliculas(&num_peliculas);
	
	solicitarPalabra("\nIntroduce pelicula que desea adquirir: ", peli, NOMBRE);
	if (peliculaExiste(peliculas, num_peliculas, peli, &posicion)) {
		asignarUsuarioAPelicula(posicion, p.correo);
	}
	else {	
		printf ("\tERROR (La pelicula introducida no existe)\n");
	}
}
void eliminarcuenta(Persona p){
    LinkedList c;
    Persona p1;
    int found=0;

    c = ficheroALista(&c);

    LINKEDLIST_goToHead(&c);
    while (!LINKEDLIST_isAtEnd(c) && !found){
        p1=LINKEDLIST_get(&c);
        if (strcmp(p1.correo, p.correo)==0){
            found=1;
            LINKEDLIST_remove(&c);
        }
        LINKEDLIST_next(&c);
    }
    actualizarFichero(c);
    printf("Se ha eliminado la cuenta correctamente!\n");
}



void listarProgramasUsuario(char usuario[MAX_CHAR_SIMPLE]){
    int trobat=0;
    FILE *f;
    LinkedList3 canales;

//	Programa p;
	Canal c;
	int i;
//CAPTURA DE HORA
	time_t tiempoActual;
	struct tm* infoTiempo;
	time(&tiempoActual);
	infoTiempo= localtime(&tiempoActual);
	
	int hora = infoTiempo->tm_hour;
	int minutos = infoTiempo->tm_min;
	printf("Hora actual: %02d:%02d\n",hora, minutos);

    f= fopen("canales.txt", "r");
    if (f==NULL){
        printf("ERROR, no existe este archivo\n");
    }else{
        canales = canalesFileToList(&trobat);
        trobat = 0;
        LINKEDLISTCANALES_goToHead(&canales);
        while (!LINKEDLISTCANALES_isAtEnd(canales)){
            c = LINKEDLISTCANALES_get(&canales);
			 if (usuarioAsignado(c, usuario, &i)) { // Verificar si el usuario está suscrito al canal
            //	LINKEDLISTPROGRAMA_goToHead(&programas);
            	//while (!LINKEDLISTPROGRAMA_isAtEnd(programas)) {
              	//  p = LINKEDLISTPROGRAMA:;_get(&programas);
                //  encontrado = 1;
				  listarprogramas(c.nombre);
                //  printf("Programa encontrado en el canal '%s':\n", c.nombre);
                //  printf("Nombre: %s\n", p.nom);
                //  printf("Categoria: %s\n", p.categoria);
                //  printf("Hora de emisión: %s\n", p.emisio);
                //	LINKEDLISTPROGRAMA_next(&programas);
           	 //	}
      	 }

                LINKEDLISTCANALES_next(&canales);
      }

      if (!trobat){
            printf("Este canal no existe\n");
      }

      fclose(f);
    }

}



/***********************************************
*
* @Finalidad: Mostrar un menu y ejecutar la opcion introducida por el usuario.
* @Parametros: in/out: p = Perfil de persona que se ha registrado/iniciado sesion.
* @Retorno: ----.
*
************************************************/
void modoCliente (Persona p) {
	int option, quit = 0;

    do {
        option = menuCliente();
        switch (option) {
            case 1:
                // Registro tarjeta
                registroTarjeta(&p);
                break;
            case 2:
                mostrarprog();
				break;
			case 3:
				visualizarCanales();
				break;
			case 4:
				listarProgramasUsuario(p.correo);
				break;
			case 5:
				buscarPrograma(p.correo);
				break;
			case 6:		
				suscribirseACanal(p);
				break;
			case 7:
				eliminarSuscripcion(p);
				break;
			case 8:
				verProgramario();
				break;
			case 9:
				descargarProgramacion(p);
				break;
			case 10:
				ordenacionPeliculas();
				break;
			case 11:
				comprarPelicula(p);
				break;
            case 12:
                eliminarcuenta(p);
                option=12;
			case 13:
				printf ("¡Hasta pronto!\n");
				break;
			case 14:
				quit = solicitarVerificacion();
				break;
		}
	} while (!quit);

}
