#include "linkedlistadvertisements.h"


LinkedListAd LINKEDLISTANUNCIOS_create() {
    LinkedListAd list;

    list.head = (Node5*)malloc(sizeof(Node5));
    if (NULL != list.head) {
        list.head->next = NULL;
        list.previous = list.head;
        list.error = LIST_NO_ERROR;
    }
    else {
        list.error = LIST_ERROR_MALLOC;
    }

    return list;
}

void LINKEDLISTANUNCIOS_add(LinkedListAd* list, Anuncio element) {

    Node5* new_node = (Node5*)malloc(sizeof(Node5));
    if (NULL != new_node) {

        new_node->element = element;
        new_node->next = list->previous->next;
        list->previous->next = new_node;
        list->previous = new_node;
        list->error = LIST_NO_ERROR;
    }
    else {
        list->error = LIST_ERROR_MALLOC;
    }
}

void LINKEDLISTANUNCIOS_remove(LinkedListAd* list) {
    Node5* aux = NULL;

    if (LINKEDLISTANUNCIOS_isAtEnd(*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        aux = list->previous->next;
        list->previous->next = list->previous->next->next;
        free(aux);
        list->error = LIST_NO_ERROR;
    }
}

Element5 LINKEDLISTANUNCIOS_get(LinkedListAd* list) {
    Element5 element;
    if (LINKEDLISTANUNCIOS_isAtEnd(*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        element = list->previous->next->element;
        list->error = LIST_NO_ERROR;
    }

    return element;
}

int LINKEDLISTANUNCIOS_isEmpty(LinkedListAd list) {
    return NULL == list.head->next;
}

void LINKEDLISTANUNCIOS_goToHead(LinkedListAd* list) {
    list->previous = list->head;
}

void LINKEDLISTANUNCIOS_next(LinkedListAd* list) {
    if (LINKEDLISTANUNCIOS_isAtEnd(*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        list->previous = list->previous->next;
        list->error = LIST_NO_ERROR;
    }
}

int LINKEDLISTANUNCIOS_isAtEnd(LinkedListAd list) {
    return NULL == list.previous->next;
}

void LINKEDLISTANUNCIOS_destroy(LinkedListAd* list) {
    Node5* aux;
    while (NULL != list->head) {

        aux = list->head;
        list->head = list->head->next;
        free(aux);
    }
    list->head = NULL;
    list->previous = NULL;
}

int LINKEDLISTANUNCIOS_getErrorCode(LinkedListAd list) {
    return list.error;
}
