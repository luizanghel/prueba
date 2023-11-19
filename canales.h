#ifndef CANALES_H
#define CANALES_H


typedef struct{
	char nombre[50];
	char programacion[50];
	double costoSuscripcion;
	double costoEmpresa;
} Canal;

typedef struct{
	char nombre[50];
	char cadenaEmision[50];
	char categoria[20];
	char horaEmision[10];
	int duracionMinutos;
	char actores[3][30];
	int idCanal;
} Programa;

void menuCanales();
/*void crearNuevoCanal();
void listarCanal();
void modificarCanal();
void eliminarCanal();
void crearPrograma();
*/

#endif

