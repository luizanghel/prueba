#include <stdio.h>

#include "user.h"
#include "presupuesto.h"
#include "linkedlist.h"
#include "canales.h"
#include "actors.h"

/***********************************************
*
* @Finalidad: Verificar si una caracter es minuscula.
* @Parametros: in: letra = Caracter a verificar.
* @Retorno: Retorna un 1 en caso que sea minuscula y un 0 en caso que no sea..
* 
************************************************/
int esMinuscula (char letra) {
	int hoEs = 0;

	if (letra >= 'a' && letra  <= 'z' ) {
		hoEs = 1;
	}
	
	return hoEs;
}

/***********************************************
*
* @Finalidad: Verificar si una caracter es mayuscula.
* @Parametros: in: letra = Caracter a verificar.
* @Retorno: Retorna un 1 en caso que sea mayuscula y un 0 en caso que no sea..
* 
************************************************/
int esMajuscula (char letra) {
	int hoEs = 0;

	if (letra >= 'A' && letra  <= 'Z' ) {
		hoEs = 1;
	}
	
	return hoEs;
}

/***********************************************
*
* @Finalidad: Verificar si una palabra empieza por una mayuscula y el resto son minusculas.
* @Parametros: 	in: palabra[] = Conjunto de caracteres a verificar.
*				in: option = Tipo de palabra que esta recibiendo.
* @Retorno: Retorna un 1 en caso que los caracteres no sean correctos o un 0 en caso que si lo sean.
* 
************************************************/
int revisarCaracteresCorrectos (char palabra[MAX_CHAR_SIMPLE], int option) {
	int error_minusculas = 0, error_mayusculas = 0, error = 0, i = 0;
	char tipo[3][MAX_CHAR_SIMPLE] = {"del nombre", "del primer apellido", "del segundo apellido"};

	for (i = 1; palabra[i] != '\0' && !error_minusculas; i++) {
		error_minusculas = !esMinuscula(palabra[i]);
	}
	if (error_minusculas == 1) {
		printf ("\tERROR: Todos los caracteres %s excepto el primero deben ser minusculas.\n", tipo[option]);
	}

	if (!esMajuscula(palabra[0])) {
		printf ("\tERROR: El primer caracter %s debe ser mayucula.\n", tipo[option]);
		error_mayusculas = 1;
	}
	if (error_mayusculas || error_minusculas) {
		error = 1;
	}
	return error;

}

/***********************************************
*
* @Finalidad: Verificar si la medida de una palabra es la requerida.
* @Parametros: 	in: palabra[] = Palabra a verificar.
*				in: medida = Valor que define la medida del conjunto de caracteres..
*				in: option = Tipo de conjunto de caracteres que se esta verificando.
* @Retorno: Retorna un 1 en caso que la medida no sea correcta y un 0 en caso que si lo sea.
* 
************************************************/
int revisarMedida (char palabra[MAX_CHAR_SIMPLE], int medida, int option) {
	char tipo[6][MAX_CHAR_SIMPLE] = {"nombre", "primer apellido", "segundo apellido", "contraseña", "correo", "contrasena"};
	int error = 0;

	if (strlen(palabra) > medida) {
		error = 1;	
		printf ("\tERROR: El maximo de caracteres de %s son %d\n", tipo[option], medida);
	}

	return error;
}


/***********************************************
*
* @Finalidad: Verificar al completo el formato del nombre y apellidos.
* @Parametros: 	in: palabra[] = Palabra a verificar.
				in: tipo = Tipo de palabra que se esta verificando.		
* @Retorno: Retorna un 1 en caso que la palabra contenga algun error y un 0 si no tiene errores..
* 
************************************************/
int revisarParametrosPropias (char palabra[MAX_CHAR_SIMPLE], int tipo) {
	int error = 0;

	error = revisarMedida(palabra, MAX_CHAR_SIMPLE, tipo);
	if (error == 0) {
		error = revisarCaracteresCorrectos(palabra, tipo);
	}
	return error;
}

/***********************************************
*
* @Finalidad: Solicitar una palabra.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: ----.
* 
************************************************/
void solicitarPalabra (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE], int tipo) {
	int error = 0;

	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosPropias(palabra, tipo);
	} while (error);
}

/***********************************************
*
* @Finalidad: Verificar el formato del identificador.
* @Parametros: 	in: palabra[] = Conjunto de caracteres a verificar.
*				out: numeros = Numeros que forman el identificador.
*				out: letra = Letra que forma el identificador.
* @Retorno: Retorna un 1 en caso que el identificador contenga algun error y un 0 en caso que no exista error.
* 
************************************************/
int revisarParametrosID (char palabra[MAX_CHAR_SIMPLE], int *numeros, char *letra) {
	int error = 0, i;

	error = revisarMedida(palabra, 9, 3);
	if (error == 0) {
		for (i = 0; i < 7; i++) {
			if (palabra[i] < '0' || palabra[i] > '9') {
				error = 1;
			}
		}
		if (error == 1) {
			printf ("\tERROR (Los primeros 8 caracteres deben ser numeros).\n");
		}
		if (!esMajuscula(palabra[8])) {
			printf ("\tERROR (El ultimo caracter debe ser una letra mayuscula).\n");
			error = 1;
		}
		if (error == 0) {
			*numeros = atoi(palabra);
			*letra = palabra[8];
		}
	}

	return error;
}

/***********************************************
*
* @Finalidad: Solicitar un DNI.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
* @Retorno: Devuelve el conjunto del DNI.
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
* @Finalidad: Verificar si hay algun caracter de un conjunto que sea '@'.
* @Parametros: in: info[] = Conjunto de caracteres a verificar
* @Retorno: Retorna un 1 en caso que exista el caracter '@' y un 0 en caso que no exista..
* 
************************************************/
int existeArroba(char info[MAX_CHAR_SIMPLE]) {
	int i = 0, existe = 0;

	for (i = 0; info[i] != '\0' && !existe; i++) {
		if (info[i] == '@') {
			existe = 1;
		}
	}
	if (existe == 0) {
		printf ("\tERROR: El correo debe contener el caracter '@'\n");
	}

	return existe;
}

/***********************************************
*
* @Finalidad: Verificar si el correo cumple el formato adecuado.
* @Parametros: 	in: letra = Caracter a verificar.
*				in: tipo = Tipo de dato que se esta verificando.
* @Retorno: Retorna un 1 en caso que haya algun error y un 0 si no existe ningun error.
* 
************************************************/
int revisarParametrosCorreo(char palabra[MAX_CHAR_SIMPLE], int tipo) {
	int error = 0;
	
	error = revisarMedida(palabra, MAX_CHAR_SIMPLE, 4);
	if (!error) {
		error = !existeArroba(palabra);
	}

	return error;
}

/***********************************************
*
* @Finalidad: Solicitar un correo.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve el conjunto del DNI.
* 
************************************************/
void solicitarCorreo (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]) {
	int error = 0;

	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosCorreo(palabra, 4);
	} while (error);
}

/***********************************************
*
* @Finalidad: Verificar si una caracter es especial.
* @Parametros: in: letra = Caracter a verificar.
* @Retorno: Retorna un 1 en caso que sea caracter especial y un 0 en caso que no sea.
* 
************************************************/
int esCaracterEspecial (char letra) {
	int hoEs = 0;

	if ((letra >= '!' && letra  <= '/') || letra == '_'  || letra == '.') {
		hoEs = 1;
	}
	
	return hoEs;
}

/***********************************************
*
* @Finalidad: Verificar si una contraseña cumple el formato requerido.
* @Parametros: 	in: contra[]= Conjunto de caracteres a verificar.
*				in: option = Tipo de conjunto de caracteres que se esta tratando.
* @Retorno: Retorna un 1 en caso que sea minuscula y un 0 en caso que no sea.
* 
************************************************/
int revisarParametrosContrasena(char contra[MAX_CHAR_SIMPLE], int option) {
	int i, error = 0, majuscula = 0, minuscula = 0, especial = 0;
	
	error = revisarMedida(contra, MAX_CHAR_SIMPLE, option);
	if (error == 0) {
		for (i = 0; contra[i] != '\0' && !majuscula; i++) {
			majuscula = esMajuscula(contra[i]);
		}
		for (i = 0; contra[i] != '\0' && !minuscula; i++) {
			minuscula = esMinuscula(contra[i]);
		}
		for (i = 0; contra[i] != '\0' && !especial; i++) {
			especial = esCaracterEspecial(contra[i]);
		}

		if (!majuscula) {
			printf ("\tERROR (La contrasenya no cumple con los caracteres requeridos. Es necesario que ingreses minimo UNA mayuscula).\n");
			error = 1;
		}
		if (!minuscula) {
			printf ("\tERROR (La contrasenya no cumple con los caracteres requeridos. Es necesario que ingreses minimo UNA minuscula).\n");
			error = 1;
		}
		if (!especial) {
			printf ("\tERROR (La contrasenya no cumple con los caracteres requeridos. Es necesario que ingreses minimo UN caracter especial).\n");
			error = 1;
		}
	}

	return error;
}

/***********************************************
*
* @Finalidad: Solicitar una contraseña.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve la contraseña.
* 
************************************************/
void solicitarContrasena (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]) {
	int error = 0;

	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosContrasena(palabra, 3);
	} while (error);
}

/***********************************************
*
* @Finalidad: Verificar que el telefono cumple el formato adecuado.
* @Parametros: in: telefono[] = Conjunto de caracteres a verificar.
* @Retorno: Retorna un 1 en caso que haya algun error y un 0 en caso que no exista error.
* 
************************************************/
int revisarParametrosTelefono (char telefono[MAX_CHAR_SIMPLE]) {
	int error = 0, i;

	if (strlen(telefono) != 9) {
		error = 1;
		printf ("\tERROR (El numero de telefono unicamente puede contener 9 digitos).\n");
	}

	if (!error) {
		for (i = 0; telefono[i] == '\0'; i++) {
			if (telefono[i] < '0' || telefono[i] > '9') {
				error = 1;
				printf ("\tERROR (El telefono unicamente puede contener numeros).\n");
			}	
		}
	}
	return error;
}

/***********************************************
*
* @Finalidad: Solicitar un telefono.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve el telefono.
* 
************************************************/
int solicitarTelefono (char texto[MAX_CHAR_SIMPLE]) {
	int error = 0, telefono;
	char palabra[MAX_CHAR_SIMPLE]; // aux;
	
	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosTelefono(palabra);
	} while (error);
	
	if (!error) {
		telefono = atoi(palabra);
	}
	//scanf("%c", &aux);
	return telefono;
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
	p.telefono = solicitarTelefono("Numero de telefono: ");

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
	printf("Nombre: %s.\n", p.apellido1);
	printf("Nombre: %s.\n", p.apellido2);
	printf("Nombre: %s.\n", p.correo);
	printf("Nombre: %s.\n", p.password);
	printf("Nombre: %d.\n", p.telefono);
	printf("DNI: %d%c.\n", p.dni.numeros, p.dni.letra);
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
	FilePersona p;

	users = fopen("clients.txt", "r");
	if (users == NULL) {
		printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
	}
	else {
		users_list = LINKEDLIST_create();
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
			fscanf(users, "%d", &p.telefono);
			fscanf(users, "%d", &p.tipus);
			LINKEDLIST_add(&users_list, p);
			fscanf(users, "%d", &p.dni.numeros);
		}
		fclose(users);
		
	}
	return users_list;
}

/***********************************************
*
* @Finalidad: Muestra el contenido de una lista.
* @Parametros: in: usuarios = Lista a mostrar.
* @Retorno: ----.
* 
************************************************/
void mostrarLista(LinkedList usuarios) {
	FilePersona p;

	LINKEDLIST_goToHead(&usuarios);
	while (!LINKEDLIST_isAtEnd(usuarios)) {
		p =	LINKEDLIST_get(&usuarios);
		if (p.tipus == 0) {
			printf ("--CLIENTE--\n");
			printf ("\tNombre: %s\n", p.nombre);
			printf ("\tPrimer apellido: %s\n", p.apellido1);
			printf ("\tSegundo apellido: %s\n", p.apellido2);
			printf ("\tCorreo: %s\n", p.correo);
			printf ("\tContraseña: %s\n", p.password);
		}
		
		LINKEDLIST_next(&usuarios);
	}
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
	FilePersona p;
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
		printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
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
* @Finalidad: Convertir el tipo de los datos al tipo de la lista.
* @Parametros: in: p = Tipo persona del dato.c/dato.h.
* @Retorno: Retorna el tipo convertido asociado a la linkedlist.
* 
************************************************/
FilePersona userFileToList (Persona p) {
	FilePersona p2;

	strcpy(p2.nombre, p.nombre);
	strcpy(p2.apellido1, p.apellido1);
	strcpy(p2.apellido2, p.apellido2);
	strcpy(p2.correo, p.correo);
	strcpy(p2.password, p.password);
	p2.telefono = p.telefono;
	p2.dni.numeros = p.dni.numeros;
	p2.dni.letra = p.dni.letra;
	p2.tipus = p.tipus;

	return p2;

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
	FilePersona p;

	actualizado = fopen("nuevo.txt", "w");
	if (actualizado == NULL) {
		printf ("\tERROR DE SISTEMA (El sistema ha caído. Pongase en contacto con un administrador en la mayor brevedad posible).\n");
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
		    fprintf(actualizado, "%d\n", p.telefono);
		    fprintf(actualizado, "%d\n", p.tipus);
			LINKEDLIST_next(&usuarios);
		}
		fclose(actualizado);
		LINKEDLIST_destroy(&usuarios);
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
Persona registerUser () {
	Persona p;
	FilePersona registrada;
	int error = 0;
	LinkedList usuarios;

	p = requestData();
	usuarios = ficheroALista();
	error = esPersonaUnica(p.correo, &usuarios);
	if (!error) {
		p.tipus = tipoUsuario(p.dni);
		registrada = userFileToList(p);
		LINKEDLIST_add(&usuarios, registrada);
		actualizarFichero(usuarios);
		printf ("\n¡Registro completado!. Bienvenido/a %s.\n", registrada.nombre);
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
FilePersona existeUsuario(char correo[MAX_CHAR_SIMPLE], char password[MAX_CHAR_SIMPLE], int *existe) {
	FilePersona p;
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
* @Finalidad: Convierte una estructura FilePersona a una Persona..
* @Parametros:	in: p = Tipo a convertir.
* @Retorno: Retorna el tipo convertido.
* 
************************************************/
Persona desdeListaAFile (FilePersona p) {
	Persona p2;

	strcpy(p2.nombre, p.nombre);
	strcpy(p2.apellido1, p.apellido1);
	strcpy(p2.apellido2, p.apellido2);
	strcpy(p2.correo, p.correo);
	strcpy(p2.password, p.password);
	p2.telefono = p.telefono;
	p2.dni.numeros = p.dni.numeros;
	p2.dni.letra = p.dni.letra;
	p2.tipus = p.tipus;

	return p2;
}


/***********************************************
*
* @Finalidad: Iniciar sesion en el sistema.
* @Parametros: ----.
* @Retorno: Los datos de la persona.
* 
************************************************/
Persona iniciarSesion() {
	FilePersona p, usuario;
	int existe = 0;

	printf ("Registro: Rellena todos los campos que aparecen a continuación:\n");
	solicitarCorreo("Introduce correo: ", p.correo);
	solicitarContrasena("Introduce contraseña: ", p.password);
	usuario = existeUsuario(p.correo, p.password, &existe);
	if (existe) {
		printf ("\n¡Inicio de sesion completado!. Bienvenido/a %s.\n", usuario.nombre);
	}
	else {
		printf ("\nEl correo electronico o la contraseña son incorrectos. Vuelva a intentarlo o registrese.\n");
	}

	return desdeListaAFile(usuario);
}

int menuProductor () {
	int option;
	char aux;
	do{
		printf ("Bienvenido al MODO PRODUCTOR. ¿Que desea realizar?\n");
		printf ("1- Menú clientes\n");
		printf ("2- Menú actores\n");
		printf ("3- Menú canales\n");
    	printf ("4- Comprobar presupuesto\n");
		printf ("5- Salir\n");
		printf ("Enter option: ");
		scanf ("%d", &option);
		scanf ("%c", &aux);
		
		switch(option){

			case 1:
				ficheroALista();		
			break;

			case 2:
				//menuActores();
			break;

			case 3:
				//menuCanales();
			break;

			case 4:
				//comprobarpresupuesto();
			break;

			case 5:
				//menu();
			break;

			default:
				printf("Opción no válida, intentalo de nuevo\n");
			break;
			
		}

	}while(option !=0);
	return option;

}

void eliminarClientes () {
	LinkedList users;
	int found = 0;
	FilePersona p;
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


void modoProductor (float *presupuesto) {
	int option, quit = 0;
	LinkedList clients;


	do {
	
		option = menuProductor();
		clients = ficheroALista();

		switch (option) {
			case 1:
				mostrarLista(clients);
				break;
			case 2:
				// modificarClientes();
				break;
			case 3:
				eliminarClientes();
				break;
			case 4:
                comprobarpresupuesto(*presupuesto);
                break;
            case 5:
				quit = 1;
				break;
		}
	} while (!quit);
}