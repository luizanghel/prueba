#include "dato.h"

/***********************************************
*
* @Finalidad: Verificar si una caracter es minuscula.
* @Parametros: in: letra = Caracter a verificar.
* @Retorno: Retorna un 1 en caso que sea minuscula y un 0 en caso que no sea..
* 
************************************************/
int esMinuscula (char letra) {
	int hoEs = 0;

	if (letra >= 'a' && letra  <= 'z') {
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
int revisarParametrosTelefono (char telefono[MAX_CHAR_SIMPLE], int medida) {
	int error = 0, i;

	if (strlen(telefono) != medida) {
		error = 1;
		printf ("\tERROR (El numero de telefono unicamente puede contener %d digitos).\n", medida);
	}

	if (!error) {
		for (i = 0; telefono[i] == '\0'; i++) {
			if (telefono[i] < '0' || telefono[i] > medida) {
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
int solicitarTelefono (char texto[MAX_CHAR_SIMPLE], int medida) {
	int error = 0, telefono;
	char palabra[MAX_CHAR_SIMPLE]; // aux;
	
	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = revisarParametrosTelefono(palabra, medida);
	} while (error);
	
	if (!error) {
		telefono = atoi(palabra);
	}
	//scanf("%c", &aux);
	return telefono;
}

/***********************************************
*
* @Finalidad: Solicitar un numero caracter.
* @Parametros:	in: texto[] = Texto que se quiere mostrar al usuario para que introduzca los datos..
* @Retorno: Devuelve el caracter, cuando se ha comprobado que es correcto.
* 
************************************************/
char solicitarCaracter (char texto[MAX_CHAR_SIMPLE]) {
	int error = 0;
	char palabra[MAX_CHAR_SIMPLE];
	
	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		
		if (palabra[1] != '\0' && palabra[0] != 'S' && palabra[0] != 'N') {
			error = 1;
			printf ("\tERROR (Debes introducir un caracter valido)\n");
		}
		else {
			error = 0;
		}

	} while (error);
	
	return palabra[0];
}

/***********************************************
*
* @Finalidad: Solicitar un numero decimal.
* @Parametros:	in: texto[] = Texto que se quiere mostrar al usuario para que introduzca los datos..
* @Retorno: Devuelve el numero decimal, cuando se ha comprobado que es correcto.
* 
************************************************/
float solicitarFloat (char texto[MAX_CHAR_SIMPLE]) {
	int i, error;
	char palabra[MAX_CHAR_SIMPLE];
	float numero;

	do {
		printf ("%s", texto);
		fgets(palabra, MAX_CHAR_SIMPLE, stdin);
		palabra[strlen(palabra) - 1] = '\0';
		error = 0;

		for (i = 0; palabra[i] != '\0' && !error; i++) {
			if (palabra[i] < '0' || palabra[i] > '9') {
				printf ("\tERROR (Debes introducir un numero que indique los minutos)\n");
				error = 1;
			}
		}

	} while (error);
	
	if (!error) {
		numero = atoi(palabra);
	}
	
	return numero;
}

/***********************************************
*
* @Finalidad: Convertir un conjunto de caracteres todo a minusculas.
* @Parametros:	in/out: palabra = Palabra a verificar y donde finalmente estara la correcta.
* @Retorno: ----.
* 
************************************************/
void todoAMinusculas (char palabra[MAX_CHAR_SIMPLE]) {
	int i = 0;

	for (i = 0; palabra[i] != '\0'; i++) {
		if (palabra[i] >= 'A' && palabra[i] <= 'Z') {
            palabra[i] = palabra[i] + ('a' - 'A');
        }
	}
}
