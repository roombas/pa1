//-----------------------------------------------------------------------------
// List.c
// List ADT
// Stephanie Lu, sqlu
// 2020 Spring CSE101 PA2
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "List.h"

//contains definitions of all exported functions
//private

// structs ---------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
	type data;
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
Node newNode(type data) {
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
	L->front = L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL) {
	int i = 0;
	if (pL != NULL && *pL != NULL) {
		while (!isEmpty(*pL)) {
			printf("calling deleteFront %d\n", i);
			deleteFront(*pL);
			i++;
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
		printf("List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		return (L->index = -1);
	}
	if (L->cursor == NULL) {
		return (L->index = -1);
	} else
		return (L->index);
	//code for returning index of cursor element
}

//get()
// Returns cursor element of L. Pre: length()>0, index()>=0
type get(List L) {
	if (L == NULL) {
		printf("Cursor Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		printf("Cursor Error: cursor is undefined");
		exit(EXIT_FAILURE);
	}
	return (L->cursor->data);
}

//listEquals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int listEquals(List A, List B) {
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if (A == NULL || B == NULL) {
		printf("List Error: calling listEquals() on NULL List reference\n");
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
	L->index = -1;
}

//moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
	if (isEmpty(L)) {
		return;
	} else {
		L->cursor = L->front;
		L->index = 0;
	}
}

//moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
	if (isEmpty(L)) {
		return;
	} else {
		L->cursor = L->back;
		L->index = L->length;
	}

}

//movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
	if (L == NULL) {
		printf("Cursor Error: calling movePrev() on NULL List.\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor != NULL && L->index != 0) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
	if (L->cursor != NULL && L->index == 0) {
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->cursor == NULL) {
		return;
	}
}

//moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
	if (L == NULL) {
		printf("Cursor Error: calling moveNext() on NULL List.\n");
		exit(EXIT_FAILURE);
	} else if (L->cursor != NULL && L->index != L->length) {
		L->cursor = L->cursor->next;
		L->index++;
	} else if (L->cursor != NULL && L->cursor->next == NULL) {
		L->cursor = NULL;
		L->index = -1;
	} else
		return;
}

//prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, type data) {
	Node N = newNode(data);

	if (L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		L->front = L->back = N;
	} else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
		if (L->index != -1) {
			L->index++;
		}
	}
	L->length++;
	freeNode(&N);
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, type data) {
	Node N = newNode(data);

	if (L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		L->front = L->back = N;
	} else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
	freeNode(&N);
}

//insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, type data) {
	Node N = newNode(data);
	if (L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling insertBefore() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		printf(
				"List Error: calling insertBefore() while cursor is undefined\n");
		exit(EXIT_FAILURE);
	} else {
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor->prev = N;
		if (N->prev != NULL) {
			N->prev->next = N;
		} else {
			L->front = N;
		}
	}
	if (L->index != -1) {
		L->index++;
	}
	L->length++;

}

//insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, type data) {
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
		N->prev = L->cursor;
		if (N->next != NULL) {
			N->next->prev = N;
		}
		else
			L->back = N;
		L->cursor->next = N;
	}
	L->length++;
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
	if (length(L) > 1) {
		N = L->front;
		if (L->cursor == L->front) {
			L->cursor = NULL;
			L->index = -1;
		}
		else if(L->cursor != NULL)
			 L->index--;
		L->front = N->next;
	} else{
		N = L->back;
		L->front = N = NULL;
	}
	printf("Calling freeNode\n");
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
	if (L->length > 1) {
		if (L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		}
		L->back = L->back->prev;
	} else {
		L->back = L->front = L->cursor = NULL;
	}
	L->length--;
	freeNode(&N);
}


// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, long x)
{
	if (L == NULL) {
		printf("List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(L)) {
		printf("List Error: calling set() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (!isEmpty(L) && L->index == -1) {
		printf("List Error: calling set() on undefined cursor element\n");
		exit(EXIT_FAILURE);
	}
	else {
		L->cursor->data = x;
	}

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
	if (!isEmpty(L) && L->index == -1) {
		printf("List Error: calling delete() on undefined cursor element\n");
		exit(EXIT_FAILURE);
	} else {
		N = L->front;
		while (N != L->cursor) {
			N = N->next;
		}
		if (L->index == 0) {
			deleteFront(L);
		} else if (L->index == L->length) {
			deleteBack(L);
		} else if (N == L->cursor) {
			N->prev->next = N->next;
			N->next->prev = N->prev;
		}
		freeNode(&N);
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
	printf("PRINTING\n");

	for (N = L->front; N != NULL; N = N->next) {
		fprintf(out, "%ld ", N->data);
		printf("PRINTING\n");
		sleep(2);
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
