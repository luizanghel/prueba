#include "linkedlistactores.h"

/****************************************************************************
 *
 * @Objective: Creates an empty linked list.
 *			   If the list fails to create the phantom node, it will set
 *				the error code to LIST_ERROR_MALLOC.
 *
 *        +---+
 *   head | o-|---------
 *        +---+         |
 *   prev | o-|---------|--
 *        +---+         | |
 *                      v v          Point of View (After the last element)
 *                    +---+----+
 *                    |   |NULL|
 *                    +---+----+
 *
 * @Parameters: ---
 * @Return: An empty linked list
 *
 ****************************************************************************/
LinkedList2 LINKEDLISTactors_create () {
    LinkedList2 list;

    // Request a Node. This node will be the auxiliary "Phantom" node.
    // The list's head now is the phantom node.
    list.head = (Node2*) malloc(sizeof(Node2));
    if (NULL != list.head) {
        // There is noone after the phantom node, so next is NULL.
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
 *
 * @Objective: Inserts the specified element in this list before the element
<<<<<<< HEAD
 *			   who is the current point of view. Shifts the point of view
=======
 *			    who is the current point of view. Shifts the point of view
>>>>>>> 4b80b16e942da54a0773813d7298aa5f2e1d93b1
 *				element (if any) and any subsequent elements to the right.
 *			   If the list fails to create the new node to store the element,
 *				it will set	the error code to LIST_ERROR_MALLOC.
 *
 *        +---+
 *   head | o-|---------
 *        +---+         |
 *   prev | o-|---------|-----------  Will point to 4.
 *        +---+         |           |
 *                      v           v          Point ov View
 *                    +---+---+   +---+---+     +---+---+     +---+----+
 *                    |   | o-|-->| 1 | o-|--X->| 2 | o-|---->| 3 |NULL|
 *                    +---+---+   +---+---+ |   +---+---+     +---+----+
 *										    |         ^
 *										    |         |
 *											|   +---+-|-+
 *										     -->| 4 | o | New Node
 *											    +---+---+
 *
 * @Parameters: (in/out) list    = the linked list where to add the new element
 *				(in)     element = the element to add to the list
 * @Return: ---
 *
 ****************************************************************************/
void 	LINKEDLISTactors_add (LinkedList2 * list, Element2 element) {
    // 1- Create a new node to store the new element.
    Node2 * new_node = (Node2*) malloc (sizeof(Node2));
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
 *
 * @Objective: Removes the element currently at the point of view in this
 *				list. Shifts any subsequent elements to the left.
 *			   This operation will fail if the POV is after the last valid
 *				element of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *				LIST_ERROR_END.
 *        +---+
 *   head | o-|---------                        aux (free aux!)
 *        +---+         |                        |
 *   prev | o-|---------|-----------             |
 *        +---+         |           |            |
 *                      v           v          	 v  POV         NEW POV
 *                    +---+---+   +---+---+     +---+---+     +---+----+
 *                    |   | o-|-->| 1 | o-|--X->| 2 | o-|---->| 3 |NULL|
 *                    +---+---+   +---+---+ |   +---+---+     +---+----+
 *										    |                   ^
 *										    |                   |
 *										     -------------------
 *
 * @Parameters: (in/out) list = the linked list where to remove the element
 * @Return: ---
 *
 ****************************************************************************/
void 	LINKEDLISTactors_remove (LinkedList2 * list) {
    Node2 * aux = NULL;
    // We cannot remove an element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is noone after PREVIOUS).
    if (LINKEDLISTactors_isAtEnd (*list)) {
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

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}


/****************************************************************************
 *
 * @Objective: Returns the element currently at the point of view in this list.
 *			   If the list is empty, this function will set the list's error
 *				to LIST_ERROR_EMPTY and the element returned will be undefined.
 * @Parameters: (in/out) list = the linked list where to get the element
 * @Return: ---
 *
 ****************************************************************************/
Element2 LINKEDLISTactors_get (LinkedList2 * list) {
    Element2 element;

    // We cannot return an element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is noone after PREVIOUS).
    if (LINKEDLISTactors_isAtEnd (*list)) {
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
 *
 * @Objective: Returns true (!0) if this list contains no elements.
 * @Parameters: (in)     list = the linked list to check
 * @Return: true (!0) if this list contains no elements, false (0) otherwise
 *
 ****************************************************************************/
int 	LINKEDLISTactors_isEmpty (LinkedList2 list) {
    // The list will be empty if there are no nodes after the phantom node.
    return NULL == list.head->next;
}


/****************************************************************************
 *
 * @Objective: Moves the point of view to the first element in the list.
 * @Parameters: (in/out) list = the linked list to move the POV.
 * @Return: ---
 *
 ****************************************************************************/
void 	LINKEDLISTactors_goToHead (LinkedList2 * list) {
    // To move the POV to the first element in the list, we need to point
    //  whoever is before the first element. That is the phantom node.
    list->previous = list->head;
}


/****************************************************************************
 *
 * @Objective: Moves the point of view to the next element in the list.
 *				If the POV is after the last element in the list (or when
 *				the list is empty), this function will set the list's error
 *				to LIST_ERROR_END.
 * @Parameters: (in/out) list = the linked list to move the POV.
 * @Return: ---
 *
 ****************************************************************************/
void 	LINKEDLISTactors_next (LinkedList2 * list) {
    // We cannot move to the next element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is noone after PREVIOUS).
    if (LINKEDLISTactors_isAtEnd (*list)) {
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
 *
 * @Objective: Returns true (!0) if the POV is after the last element in the
 *				list.
 * @Parameters: (in)     list = the linked to check.
 * @Return: true (!0) if the POV is after the last element in the list
 *
 ****************************************************************************/
int 	LINKEDLISTactors_isAtEnd (LinkedList2 list) {
    // To check if the list is at the end (POV after the last element) we
    //  need to check if there is any Node after the previous pointer.
    return NULL == list.previous->next;
}


/****************************************************************************
 *
 * @Objective: Removes all the elements from the list and frees any dynamic
 *				memory block the list was using. The list must be created
 *				again before usage.
 * @Parameters: (in/out) list = the linked list to destroy.
 * @Return: ---
 *
 ****************************************************************************/
void 	LINKEDLISTactors_destroy (LinkedList2 * list) {
    Node2 * aux;
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

/*
 * Another implementation of the destroy.
 *

void LINKEDLIST_destroy (LinkedList * list) {
	LINKEDLIST_goToHead(list);
	while(!LINKEDLIST_isEmpty(*list)) {
		LINKEDLIST_remove(list);
	}
	free(list->head);
	list->head = NULL;
	list->previous = NULL;
}

*/

/****************************************************************************
 *
 * @Objective: This function returns the error code provided by the last
 *				operation run. The operations that update the error code are:
 *				Create, Add, Remove and Get.
 * @Parameters: (in)     list = the linked list to check.
 * @Return: an error code from the list of constants defined.
 *
 ****************************************************************************/
int		LINKEDLISTactors_getErrorCode (LinkedList2 list) {
    return list.error;
}
