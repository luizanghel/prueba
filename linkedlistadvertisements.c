#include "linkedlistadvertisements.h"

/****************************************************************************
 * Función: LINKEDLISTadvertisements_create
 ****************************************************************************/
LinkedListAd LINKEDLISTANUNCIOS_create() {
    LinkedListAd list;

    // Request a Node. This node will be the auxiliary "Phantom" node.
    // The list's head now is the phantom node.
    list.head = (Node5*)malloc(sizeof(Node5));
    if (NULL != list.head) {
        // There is no one after the phantom node, so next is NULL.
        list.head->next = NULL;
        // We set the previous pointer to the phantom node. Now the point
        //  of view is after the last valid element in the list (there are
        //  no valid elements as the list is empty).
        list.previous = list.head;

        // Everything was fine, so we set the error code to NO_ERROR
        list.error = LIST_NO_ERROR;
    }
    else {
        // Could not get dynamic memory for the phantom node, so we set the
        //  error to malloc error code.
        list.error = LIST_ERROR_MALLOC;
    }

    return list;
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_add
 ****************************************************************************/
void LINKEDLISTANUNCIOS_add(LinkedListAd* list, Anuncio element) {
    // 1- Create a new node to store the new element.
    Node5* new_node = (Node5*)malloc(sizeof(Node5));
    if (NULL != new_node) {
        // 2- Set the element field in the new node with the provided element.
        new_node->element = element;
        // 3- Set the next field in the new node.
        //    The next node will be the node in the point of view.
        new_node->next = list->previous->next;

        // 4- Link the new node to the list. The new node will go before the
        //    point of view, so
        list->previous->next = new_node;
        // 5- Move the previous pointer.
        list->previous = new_node;

        // As everything was fine, set the error code to NO_ERROR
        list->error = LIST_NO_ERROR;
    }
    else {
        // Could not get dynamic memory for the new node, so we set the
        //  error to malloc error code.
        list->error = LIST_ERROR_MALLOC;
    }
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_remove
 ****************************************************************************/
void LINKEDLISTANUNCIOS_remove(LinkedListAd* list) {
    Node5* aux = NULL;
    // We cannot remove an element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is no one after PREVIOUS).
    if (LINKEDLISTANUNCIOS_isAtEnd(*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // We need to set an auxiliary pointer to point the element we want
        //  to remove (the POV).
        aux = list->previous->next;

        // "Remove" the POV. The element after the PREVIOUS node will be the
        //  element after the POV.
        list->previous->next = list->previous->next->next;

        // Free the POV. Remove the element.
        free(aux);

        // If there are no errors, set the error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_get
 ****************************************************************************/
Element5 LINKEDLISTANUNCIOS_get(LinkedListAd* list) {
    Element5 element;

    // We cannot return an element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is no one after PREVIOUS).
    if (LINKEDLISTANUNCIOS_isAtEnd(*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // The element to return is the element stored in the POV.
        element = list->previous->next->element;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }

    return element;
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_isEmpty
 ****************************************************************************/
int LINKEDLISTANUNCIOS_isEmpty(LinkedListAd list) {
    // The list will be empty if there are no nodes after the phantom node.
    return NULL == list.head->next;
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_goToHead
 ****************************************************************************/
void LINKEDLISTANUNCIOS_goToHead(LinkedListAd* list) {
    // To move the POV to the first element in the list, we need to point
    //  whoever is before the first element. That is the phantom node.
    list->previous = list->head;
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_next
 ****************************************************************************/
void LINKEDLISTANUNCIOS_next(LinkedListAd* list) {
    // We cannot move to the next element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is no one after PREVIOUS).
    if (LINKEDLISTANUNCIOS_isAtEnd(*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // Move the POV to the next element.
        list->previous = list->previous->next;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_isAtEnd
 ****************************************************************************/
int LINKEDLISTANUNCIOS_isAtEnd(LinkedListAd list) {
    // To check if the list is at the end (POV after the last element) we
    //  need to check if there is any Node after the previous pointer.
    return NULL == list.previous->next;
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_destroy
 ****************************************************************************/
void LINKEDLISTANUNCIOS_destroy(LinkedListAd* list) {
    Node5* aux;
    // While there are still NODEs in the list.
    while (NULL != list->head) {
        // Take the first node.
        aux = list->head;
        // Now the first node is the next node.
        list->head = list->head->next;
        // Free who was the first node;
        free(aux);
    }
    // Set the pointers to NULL (best practice).
    list->head = NULL;
    list->previous = NULL;
}

/****************************************************************************
 * Función: LINKEDLISTadvertisements_getErrorCode
 ****************************************************************************/
int LINKEDLISTANUNCIOS_getErrorCode(LinkedListAd list) {
    return list.error;
}
