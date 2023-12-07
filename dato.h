#ifndef _DATO_H_
#define _DATO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR_SIMPLE 200

/***********************************************
*
* @Finalidad: Comprobar que los parametros introducudidos por el usuario sean correctos y se encuentren dentro del rango..
* @Parametros:	out: option = Valor de la opcion del menú a interaccionar.
*				in: min = Valor minimo permitido en el menú.
*				in: max = Valor máximo permitido en el menú.
* @Retorno: Devuelve si el numero introducido se encuentra dentro del rango o no.
* 
************************************************/
int optionAsNumber (int *option, int min, int max);

/***********************************************
*
* @Finalidad: Solicitar un numero caracter.
* @Parametros:	in: texto[] = Texto que se quiere mostrar al usuario para que introduzca los datos..
* @Retorno: Devuelve el caracter, cuando se ha comprobado que es correcto.
* 
************************************************/
char solicitarCaracter (char texto[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Convertir un conjunto de caracteres todo a minusculas.
* @Parametros:	in/out: palabra = Palabra a verificar y donde finalmente estara la correcta.
* @Retorno: ----.
* 
************************************************/
void todoAMinusculas (char palabra[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Verificar si una palabra empieza por una mayuscula y el resto son minusculas.
* @Parametros: 	in: palabra[] = Conjunto de caracteres a verificar.
*				in: option = Tipo de palabra que esta recibiendo.
* @Retorno: Retorna un 1 en caso que los caracteres no sean correctos o un 0 en caso que si lo sean.
* 
************************************************/
int revisarCaracteresCorrectos (char palabra[MAX_CHAR_SIMPLE], int option);


/***********************************************
*
* @Finalidad: Verificar si la medida de una palabra es la requerida.
* @Parametros: 	in: palabra[] = Palabra a verificar.
*				in: medida = Valor que define la medida del conjunto de caracteres..
*				in: option = Tipo de conjunto de caracteres que se esta verificando.
* @Retorno: Retorna un 1 en caso que la medida no sea correcta y un 0 en caso que si lo sea.
* 
************************************************/
int revisarMedida (char palabra[MAX_CHAR_SIMPLE], int medida, int option);

/***********************************************
*
* @Finalidad: Verificar al completo el formato del nombre y apellidos.
* @Parametros: 	in: palabra[] = Palabra a verificar.
				in: tipo = Tipo de palabra que se esta verificando.		
* @Retorno: Retorna un 1 en caso que la palabra contenga algun error y un 0 si no tiene errores..
* 
************************************************/
int revisarParametrosPropias (char palabra[MAX_CHAR_SIMPLE], int tipo);

/***********************************************
*
* @Finalidad: Solicitar una palabra.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: ----.
* 
************************************************/
void solicitarPalabra (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE], int tipo);

/***********************************************
*
* @Finalidad: Verificar el formato del identificador.
* @Parametros: 	in: palabra[] = Conjunto de caracteres a verificar.
*				out: numeros = Numeros que forman el identificador.
*				out: letra = Letra que forma el identificador.
* @Retorno: Retorna un 1 en caso que el identificador contenga algun error y un 0 en caso que no exista error.
* 
************************************************/
int revisarParametrosID (char palabra[MAX_CHAR_SIMPLE], int *numeros, char *letra);

/***********************************************
*
* @Finalidad: Verificar si hay algun caracter de un conjunto que sea '@'.
* @Parametros: in: info[] = Conjunto de caracteres a verificar
* @Retorno: Retorna un 1 en caso que exista el caracter '@' y un 0 en caso que no exista..
* 
************************************************/
int existeArroba(char info[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Verificar si el correo cumple el formato adecuado.
* @Parametros: 	in: letra = Caracter a verificar.
*				in: tipo = Tipo de dato que se esta verificando.
* @Retorno: Retorna un 1 en caso que haya algun error y un 0 si no existe ningun error.
* 
************************************************/
int revisarParametrosCorreo(char palabra[MAX_CHAR_SIMPLE], int tipo);

/***********************************************
*
* @Finalidad: Solicitar un correo.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve el conjunto del DNI.
* 
************************************************/
void solicitarCorreo (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Verificar si una caracter es especial.
* @Parametros: in: letra = Caracter a verificar.
* @Retorno: Retorna un 1 en caso que sea caracter especial y un 0 en caso que no sea.
* 
************************************************/
int esCaracterEspecial (char letra);

/***********************************************
*
* @Finalidad: Verificar si una contraseña cumple el formato requerido.
* @Parametros: 	in: contra[]= Conjunto de caracteres a verificar.
*				in: option = Tipo de conjunto de caracteres que se esta tratando.
* @Retorno: Retorna un 1 en caso que sea minuscula y un 0 en caso que no sea.
* 
************************************************/
int revisarParametrosContrasena(char contra[MAX_CHAR_SIMPLE], int option);

/***********************************************
*
* @Finalidad: Solicitar una contraseña.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve la contraseña.
* 
************************************************/
void solicitarContrasena (char texto[MAX_CHAR_SIMPLE], char palabra[MAX_CHAR_SIMPLE]);

/***********************************************
*
* @Finalidad: Verificar que el telefono cumple el formato adecuado.
* @Parametros: in: telefono[] = Conjunto de caracteres a verificar.
* @Retorno: Retorna un 1 en caso que haya algun error y un 0 en caso que no exista error.
* 
************************************************/
int revisarParametrosTelefono (char telefono[MAX_CHAR_SIMPLE], int medida);

/***********************************************
*
* @Finalidad: Solicitar un telefono.
* @Parametros:	in: texto[] = Tipo de palabra que se quiere solicitar.
*				out: palabra[] = Input del usuario.
* @Retorno: Devuelve el telefono.
* 
************************************************/
int solicitarTelefono (char texto[MAX_CHAR_SIMPLE], int medida);

/***********************************************
*
* @Finalidad: Solicitar un numero decimal.
* @Parametros:	in: texto[] = Texto que se quiere mostrar al usuario para que introduzca los datos..
* @Retorno: Devuelve el numero decimal, cuando se ha comprobado que es correcto.
* 
************************************************/
float solicitarFloat (char texto[MAX_CHAR_SIMPLE]);

#endif
