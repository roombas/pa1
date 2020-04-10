//-----------------------------------------------------------------------------
// List.c
// List ADT
// Stephanie Lu
// sqlu
// pa1
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "List.h"
//contains definitions of all exported functions
//private

// structs ---------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
	int data;
	struct NodeObj *next;
	struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

//newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList() {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL) {
	if (pL != NULL && *pL != NULL) {
		while (!isEmpty(*pL)) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

//length()
// Returns the number of elements in L
int length(List L) {
	if (L == NULL) {
		printf("List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->length);
}

//index()
//returns index of cursor element if defined, -1 otherwise
int index(List L) {
	if (L == NULL) {
		return (-1);
	}
	if (isEmpty(L)) {
		return (-1);
	}
	if (L->cursor == NULL) {
		return (-1);
	}
	return (L->index);
	//code for returning index of cursor element
}

//get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
	if (L->cursor == NULL) {
		return (-1);
	} else {
		return (L->cursor->data);
	}
}

//equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B) {
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	eq = (A->length == B->length);
	N = A->front;
	M = B->front;
	while (eq && N != NULL) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

//front()
// Returns front element of L. Pre: length()>0
int front(List L) {
	if (L == NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling front() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->front->data);
}

//back()
// Returns back element of L. Pre: length()>0
int back(List L) {
	if (L == NULL) {
		printf("List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling back() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->back->data);
}

//isEmpty()
//returns true (1) if L is empty, otherwise returns false(0)
int isEmpty(List L) {
	if (L == NULL) {
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->length == 0);
}

// Manipulation procedures ----------------------------------------------------

//clear()
// Resets L to its original empty state.
void clear(List L) {
	if (L == NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling clear() on empty List\n");
		exit(EXIT_FAILURE);
	}

	while (L->front != NULL) {
		deleteBack(L);
	}
}

//moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
	if (L != NULL && !isEmpty(L)) {
		L->cursor = L->front;
		L->index = 0;
	}
	else
		return;
}

//moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
	if (L != NULL && !isEmpty(L)) {
		L->cursor = L->back;
		L->index = L->length;
	}
	else
		return;
}

//movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->cursor != NULL && L->cursor != L->front) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
}

//moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->cursor != NULL && L->cursor != L->back) {
		L->cursor = L->cursor->next;
		L->index++;
	}
}

//prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
	Node N = newNode(data);

	if (L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		L->front = L->back = N;
	} else {
		N->prev = NULL;
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	L->length++;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
	Node N = newNode(data);

	if (L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		L->front = L->back = N;
	} else {
		N->next = NULL;
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
}

//insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
	Node N = newNode(data);
	if (L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling insertBefore() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1 || L->cursor == NULL) {
		printf("List Error: calling insertBefore() while cursor is undefined\n");
		exit(EXIT_FAILURE);
	} else {
		N->prev = L->cursor->prev;
		L->cursor->prev = N;
		N->next = L->cursor;

		if (N->prev != NULL) {
			N->prev->next = N;
		} else {
			L->front = N;
		}
		L->length++;
	}
}

//insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
	Node N = newNode(data);
	if (L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling insertAfter() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1 || L->cursor == NULL) {
		printf("List Error: calling insertAfter() while cursor is undefined\n");
		exit(EXIT_FAILURE);
	} else {
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->prev = L->cursor;
		if (N->next != NULL)
		{
			N->next->prev = N;
		}
		L->length++;
	}
}

//deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	N = L->front;
	if (length(L) > 1) {
		L->front = L->front->next;
	} else {
		L->front = L->back = NULL;
	}
	L->length--;
	freeNode(&N);
}

//deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling deleteBack() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	N = L->back;
	if (length(L) > 1) {
		L->back = L->back->prev;
	} else {
		L->back = L->front = NULL;
	}
	L->length--;
	freeNode(&N);
}

//delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling delete() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		printf("List Error: calling delete() on undefined cursor element\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		N = L->front;
		while(N != L->cursor)
		{
			N = N->next;
		}
		if(index(L) == 1)
		{
			deleteFront(L);
		}
		if(index(L) == length(L))
		{
			deleteBack(L);
		}
		else if(N == L->cursor)
		{
			N->prev->next = N->next;
			N->next->prev = N->prev;
			freeNode(&N);
		}
	}
	L->cursor = NULL;
	L->index = -1;
	L->length--;
}

// Other operations -----------------------------------------------------------

//printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	for (N = L->front; N != NULL; N = N->next) {
		fprintf(out, "%d ", N->data);
	}
	printf("\n");

}

//copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {

	if (L == NULL) {
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	List L2 = L;
	L2->cursor = NULL;
	L2->index = -1;
	return L2;
}
