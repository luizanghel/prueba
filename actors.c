#include <stdio.h>
#include "actors.h"
#include "linkedlistactores.h"

void addActor(){
    FileActor actor;
    FileDni dni_pedir;
    LinkedList lista;
    lista = LINKEDLISTactors_create ();
    
    char name[100], pedir_letra[100], surname1[100], surname2[100];
    int numdni , phone, salario, contract_status;
    
    printf ("\nEnter your actor DNI number: ");
    scanf("%d", &numdni);
    
    printf ("\nEnter your actor DNI letter: ");
    scanf("%s", pedir_letra);
    
    printf ("\nEnter your actor name: ");
    scanf("%s", name);
    
    printf ("\nEnter your actor first surname: ");
    scanf("%s", surname1);
    
    printf ("\nEnter your actor second surname: ");
    scanf("%s", surname2);
    
    do{
        printf ("\nEnter your actor phone number: ");
        scanf("%d", &phone);
        if(phone > 999999999 || phone < 100000000){
            printf("\nERROR! This is not a valid phone number"); 
        }
    }while(phone > 999999999 || phone < 100000000 );
    
    printf ("\nEnter your actor salari: ");
    scanf("%d", &salario);
    
    
    do{
        printf ("\nEnter your actor contract state (0 if not contracted, 1 if cotracted): ");
        scanf("%d", &contract_status);
        if (contract_status != 0 && contract_status != 1){
            printf("\nERROR!");
        }
    }while( contract_status != 0 && contract_status != 1);
    
    strcpy (actor.nombre, name);
    strcpy (actor.apellido1, surname1);
    strcpy (actor.apellido2, surname2);
    
    actor.telefono = phone;
    actor.salari = salario;
    actor.contract = contract_status;
    
    dni_pedir.numeros = numdni;
    dni_pedir.letra = pedir_letra;
    
    actor.dni = dni_pedir;
    LINKEDLISTactors_add (lista, actor);
}
