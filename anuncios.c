#include "anuncios.h"

LinkedListAd anunciosALista() {
    LinkedListAd ad;
    FILE *f;

    f = fopen("anuncios.txt", "r");
    if (f == NULL) {
        printf("No hay anuncios.\n");
        ad = LINKEDLISTANUNCIOS_create();
    } else {
        ad = LINKEDLISTANUNCIOS_create();
        Anuncio a;

        while (fscanf(f, "%49s %d %f %f", a.marca, &a.duracion, &a.probExito, &a.precio) == 4) {
            LINKEDLISTANUNCIOS_add(&ad, a);
        }

        fclose(f);
    }

    return ad;
}

void actualizarFicheroAnuncios(LinkedListAd *anuncios) {
    FILE *actualizado = fopen("nuevo_anuncios.txt", "w");
    if (actualizado == NULL) {
        printf("\tERROR DE SISTEMA (El sistema ha caído. Póngase en contacto con un administrador en la mayor brevedad posible).\n");
    } else {
        LINKEDLISTANUNCIOS_goToHead(anuncios);
        while (!LINKEDLISTANUNCIOS_isAtEnd(*anuncios)) {
            Anuncio a = LINKEDLISTANUNCIOS_get(anuncios);
            fprintf(actualizado, "%s %d %f %f\n", a.marca, a.duracion, a.probExito, a.precio);
            LINKEDLISTANUNCIOS_next(anuncios);
        }
        fclose(actualizado);
        remove("anuncios.txt");
        rename("nuevo_anuncios.txt", "anuncios.txt");
    }
}

Anuncio solicitarDatosAnuncio() {
    Anuncio a;
    printf("Introduce marca del anuncio: ");
    fgets(a.marca, sizeof(a.marca), stdin);
    a.marca[strcspn(a.marca, "\n")] = '\0';

    printf("Introduce duración del anuncio: ");
    scanf("%d", &a.duracion);
    printf("Introduce probabilidad de éxito del anuncio (0-100): ");
    scanf("%f", &a.probExito);
    printf("Introduce precio del anuncio: ");
    scanf("%f", &a.precio);

    return a;
}



void mostrarAnuncios(LinkedListAd anuncios) {
    LINKEDLISTANUNCIOS_goToHead(&anuncios);
    while (!LINKEDLISTANUNCIOS_isAtEnd(anuncios)) {
        Anuncio a = LINKEDLISTANUNCIOS_get(&anuncios);
        printf("\nMarca: %s\n", a.marca);
        printf("Duracion: %d segundos\n", a.duracion);
        printf("Probabilidad de éxito: %.2f\n", a.probExito);
        printf("Precio: %.2f\n", a.precio);
        LINKEDLISTANUNCIOS_next(&anuncios);
    }
}

void anadirAnuncio(LinkedListAd *anuncios) {
    Anuncio a = solicitarDatosAnuncio();
    LINKEDLISTANUNCIOS_add(anuncios, a);
    actualizarFicheroAnuncios(anuncios);
    printf("Se ha añadido el anuncio correctamente\n");
}

void eliminarAnuncio(LinkedListAd *anuncios) {
    char marcaEliminar[50];
    solicitarPalabra("Introduce la marca del anuncio a eliminar: ", marcaEliminar, sizeof(marcaEliminar));

    LINKEDLISTANUNCIOS_goToHead(anuncios);
    while (!LINKEDLISTANUNCIOS_isAtEnd(*anuncios)) {
        Anuncio a = LINKEDLISTANUNCIOS_get(anuncios);
        if (strcmp(a.marca, marcaEliminar) == 0) {
            LINKEDLISTANUNCIOS_remove(anuncios);
            actualizarFicheroAnuncios(anuncios);
            printf("Anuncio con marca %s eliminado correctamente.\n", marcaEliminar);
            return;
        }
        LINKEDLISTANUNCIOS_next(anuncios);
    }

    printf("No se encontró un anuncio con la marca %s.\n", marcaEliminar);
}

void menuAnuncios() {
    int opcion;
    LinkedListAd anuncios = anunciosALista();

    do {
        printf("\nGestión de Anuncios\n");
        printf("1. Mostrar Anuncios\n");
        printf("2. Añadir Anuncio\n");
        printf("3. Eliminar Anuncio\n");
        printf("4. Volver al Menú Principal\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                mostrarAnuncios(anuncios);
                break;
            case 2:
                anadirAnuncio(&anuncios);
                break;
            case 3:
                eliminarAnuncio(&anuncios);
                break;
            case 4:
                break;
            default:
                printf("Opción no válida. Por favor, selecciona una opción válida.\n");
        }
    } while (opcion != 4);
}