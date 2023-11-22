#include <stdio.h>

#include <string.h>

#include "presupuesto.h"
/***********************************************
*
* @Finalidad: Añadir ingreso a el fichero y a el presupuesto
* @Parametros: float presupuesto: viene del main.c, float ingreso: el ingreso que quieres añadir a el presupuesto, char descripcion: breve descripcion del ingreso
* @Retorno: presupuesto.
*
************************************************/
float actualizaringreso(float presupuesto, float ingreso, char descripcion[100]){
    FILE *f;

    f=fopen ("ingresos.txt", "a");
    if(f==NULL){
        printf("ERROR");
    }else{
        fprintf(f, "%s\n", descripcion);
        fprintf(f,"%f\n", ingreso);
        fclose(f);
        presupuesto=presupuesto-ingreso;
    }

    return presupuesto;
}
/***********************************************
*
* @Finalidad: Añadir ingreso a el fichero y a el presupuesto
* @Parametros: float presupuesto: viene del main.c, float perdida: la perdida que quieres añadir a el presupuesto, char descripcion: breve descripcion de la perdida
* @Retorno: presupuesto.
*
************************************************/
float actualizarperdida(float presupuesto, float perdida, char descripcion[100]){
    FILE *f;

    f=fopen ("perdidas.txt", "a");
    if(f==NULL){
        printf("ERROR");
    }else{
        fprintf(f, "%s\n", descripcion);
        fprintf(f,"%f\n", perdida);
        fclose(f);
        presupuesto=presupuesto-perdida;
    }

    return presupuesto;
}
/***********************************************
*
* @Finalidad: Listar los ingresos de la empresa
* @Parametros: ----.
* @Retorno: ---.
*
************************************************/
void listaringresos(){
    float totalingresos=0;
    FILE *f;
    char descripcion[100];
    float ingreso;
    char aux;

    f=fopen("ingresos.txt", "r");

    if (f==NULL){
        printf("No hay ningun ingreso\n");
    }else{
        printf("\nLista de ingresos:\n");
        fgets(descripcion, 100, f);
        descripcion[strlen(descripcion) - 1] = '\0';
        while (!feof(f)){
            fscanf(f, "%f", &ingreso);
            fscanf(f, "%c", &aux);
            printf("%s->%.1f€\n", descripcion, ingreso);
            printf("-----------------------------\n");
            fgets(descripcion, 100, f);
            descripcion[strlen(descripcion) - 1] = '\0';
            totalingresos=totalingresos+ingreso;
        }
        printf("Total ingresos: %.1f€\n", totalingresos);
        fclose(f);
    }
}
/***********************************************
*
* @Finalidad: Listar los perdidas de la empresa
* @Parametros: ----.
* @Retorno: ---.
*
************************************************/
void listarperdidas(){
    float totalperdidas=0;
    FILE *f;
    char descripcion[100];
    float perdida;
    char aux;

    f=fopen("perdidas.txt", "r");
    if (f==NULL){
        printf("No hay ninguna perdida\n");
    }else{
        printf("\nLista de perdidas:\n");
        fgets(descripcion, 100, f);
        descripcion[strlen(descripcion) - 1] = '\0';
        while (!feof(f)){
            fscanf(f, "%f", &perdida);
            fscanf(f, "%c", &aux);
            printf("%s->%.1f€\n", descripcion, perdida);
            printf("-----------------------------\n");
            fgets(descripcion, 100, f);
            descripcion[strlen(descripcion) - 1] = '\0';
            totalperdidas=totalperdidas+perdida;
        }
        printf("Total perdidas: %.1f€\n", totalperdidas);
        fclose(f);
    }
}
/***********************************************
*
* @Finalidad: Menu opciones presupuesto
* @Parametros: presupuesto de la empresa que viene desde el main.c
* @Retorno: ---.
*
************************************************/
void comprobarpresupuesto(float presupuesto){
    int opcion, quit=0;

    do {
        printf("\nQue deseas comprobar? \n");
        printf("1- Listar ingresos\n");
        printf("2- Listar perdidas\n");
        printf("3- Comprobar total presupuesto\n");
        printf("Enter option: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                listaringresos();
                break;
            case 2:
                listarperdidas();
                break;
            case 3:
                printf("El presupuesto total es de %.1f\n", presupuesto);
                break;
            case 4:
                quit=1;
                break;
        }
    }while (!quit);

}
