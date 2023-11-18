#ifndef PRESUPUESTO_H
#define PRESUPUESTO_H

// Operaciones
float actualizaringreso(float presupuesto, float ingreso, char descripcion[100]);
float actaualizarperdida(float presupuesto, float perdida, char descripcion[100]);
void listaringresos ();
void listarperdidas ();
void comprobarpresupuesto(float presupuesto);

#endif
