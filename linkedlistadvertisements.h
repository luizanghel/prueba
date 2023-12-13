#ifndef _LINKEDLISTADVERTISEMENTS_H
#define _LINKEDLISTADVERTISEMENTS_H

// Libraries
#include <stdlib.h>	// To use dynamic memory.

// Constants to manage the list's error codes.
#define LIST_NO_ERROR 0
#define LIST_ERROR_FULL 1		// Error, the list is full.
#define LIST_ERROR_EMPTY 2		// Error, the list is empty.
#define LIST_ERROR_MALLOC 3		// Error, a malloc failed.
#define LIST_ERROR_END 4		// Error, the POV is at the end.


typedef struct {
    char marca[50];
    int duracion;
    float probExito;
    float precio;
} Anuncio;

// Data types
typedef Anuncio Element5;

/*
 * Node is a recursive structure that will contain each one of the elements.
 * A node has two main fields, the element to store and a pointer to the next
 *  node in the Linear Data Structure.
 * The structure is recursively defined (a Node has a pointer to another node),
 *  so we need to define a new type (typedef) from a structure (struct _Node5).
 */
typedef struct _Node5 {
    Element5 element;
    struct _Node5* next;
} Node5;

/*
 * A linked list is a linear data structure, in which the elements are not
 *  stored at contiguous memory locations. The elements in a linked list
 *  are stored inside Nodes that are linked using pointers.
 *
 *  +---+----+     +---+----+     +----+----+
 *  | 1 |  o-|---> | 2 |  o-|---> | 3  |NULL|
 *  +---+----+     +---+----+     +----+----+
 *
 * This implementation of the linked list will be using an auxiliary Node
 *  we call the "phantom node". This auxiliary node will help us with the
 *  different operations from the list. It solves the problem of the list
 *  being empty (empty == no nodes) and let us assume that we will always
 *  have one node in the list.
 *
 * Example of an empty list:
 *
 *               Phantom node
 *       +---+   +---+----+
 *  head | o-|-->|   |NULL|
 *       +---+   +---+----+
 *
 * The linked list will have a "Point of View" (POV). This point of view is the
 *  element (Node) we are visiting at the moment from the list. Whenever
 *  we decide to add, remove, or get an element, we will work from the point
 *  of view. This point of view is represented by the "previous" pointer in
 *  the LinkedList type. This previous pointer will always point to "the
 *  element before the point of view". That is why is called previous. We need
 *  to point to the element before the point of view to be able to add new
 *  elements before the first element.
 *
 *        +---+
 *   head | o-|---------
 *        +---+         |
 *   prev | o-|---------|-----------
 *        +---+         |           |
 *                      v           v          Point of View
 *                    +---+---+   +---+---+     +---+---+     +---+----+
 *                    |   | o-|-->| 1 | o-|--X->| 2 | o-|---->| 3 |NULL|
 *                    +---+---+   +---+---+ |   +---+---+     +---+----+
 *
 */
typedef struct {
    int error;        // Error code to keep track of failing operations;
    Node5* head;	 	// Head/First element or Phantom node;
    Node5* previous; 	// Previous node before the point of view;
} LinkedListAd;

// Procedures & Functions

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
LinkedListAd LINKEDLISTANUNCIOS_create();

/****************************************************************************
 *
 * @Objective: Inserts the specified element in this list before the element
 *			    who is the current point of view. Shifts the point of view
 *				element (if any) and any subsequent elements to the right.
 *			   If the list fails to create the new node to store the element,
 *				it will set	the error code to LIST_ERROR_MALLOC.
 *
 *        +---+
 *   head | o-|---------
 *        +---+         |
 *   prev | o-|---------|-----------  Will point to 4.
 *        +---+         |           |
 *                      v           v          Point of View
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
void LINKEDLISTANUNCIOS_add(LinkedListAd* list, Element5 element);

/****************************************************************************
 *
 * @Objective: Removes the element currently at the point of view in this
 *				list. Shifts any subsequent elements to the left.
 *			   This operation will fail if the POV is after the last valid
 *				element of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *				LIST_ERROR_END.
  *
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
void LINKEDLISTANUNCIOS_remove(LinkedListAd* list);

/****************************************************************************
 *
 * @Objective: Returns the element currently at the point of view in this list.
 *			   This operation will fail if the POV is after the last valid
 *				element of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *				LIST_ERROR_END.
 * @Parameters: (in/out) list = the linked list where to get the element.
 *								in/out because we need to set the error code.
 * @Return: ---
 *
 ****************************************************************************/
Element5 LINKEDLISTANUNCIOS_get(LinkedListAd* list);

/****************************************************************************
 *
 * @Objective: Returns true (!0) if this list contains no elements.
 * @Parameters: (in)     list = the linked list to check
 * @Return: true (!0) if this list contains no elements, false (0) otherwise
 *
 ****************************************************************************/
int LINKEDLISTANUNCIOS_isEmpty(LinkedListAd list);

/****************************************************************************
 *
 * @Objective: Moves the point of view to the first element in the list.
 * @Parameters: (in/out) list = the linked list to move the POV.
 * @Return: ---
 *
 ****************************************************************************/
void LINKEDLISTANUNCIOS_goToHead(LinkedListAd* list);

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
void LINKEDLISTANUNCIOS_next(LinkedListAd* list);

/****************************************************************************
 *
 * @Objective: Returns true (!0) if the POV is after the last element in the
 *				list.
 * @Parameters: (in)     list = the linked to check.
 * @Return: true (!0) if the POV is after the last element in the list
 *
 ****************************************************************************/
int LINKEDLISTANUNCIOS_isAtEnd(LinkedListAd list);

/****************************************************************************
 *
 * @Objective: Removes all the elements from the list and frees any dynamic
 *				memory block the list was using. The list must be created
 *				again before usage.
 * @Parameters: (in/out) list = the linked list to destroy.
 * @Return: ---
 *
 ****************************************************************************/
void LINKEDLISTANUNCIOS_destroy(LinkedListAd* list);

/****************************************************************************
 *
 * @Objective: This function returns the error code provided by the last
 *				operation run. The operations that update the error code are:
 *				Create, Add, Remove, and Get.
 * @Parameters: (in)     list = the linked list to check.
 * @Return: an error code from the list of constants defined.
 *
 ****************************************************************************/
int LINKEDLISTANUNCIOS_getErrorCode(LinkedListAd list);

#endif
