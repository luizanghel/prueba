
#ifndef CANALES_H
#define CANALES_H

#include "actors.h"
#include "linkedlistcanales.h"
#include "linkedlistprograma.h"
#include "dato.h"

void menuCanales();
int assignarAlPrograma(int numero, char letra);
LinkedList4 programaFileToList ();
void actualizarFicheroPrograma (LinkedList4 programas);
LinkedList3 canalesFileToList ();

#endif

