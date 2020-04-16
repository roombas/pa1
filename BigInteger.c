//-----------------------------------------------------------------------------
// BigInteger.c
// BigInteger ADT
// Stephanie Lu, sqlu
// 2020 Spring CSE101 PA2
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "BigInteger.h"
#include "List.h"
#define POWER 9
#define BASE 1000000000

// structs ---------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj {
	int sign;
	List bigList;
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger() {
	BigInteger b;
	b = malloc(sizeof(BigIntegerObj));
	b->sign = 0;
	b->bigList = newList();
	return (b);
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger *pN) {
	/*if (*(*pN)->bigList != NULL) {
	 freeList(&(*(*pN)->bigList));
	 }*/
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N) {
	if (N == NULL) {
		printf("List Error: calling sign() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(N->bigList)) {
		return (N->sign = 0);
	}
	return (N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B) {
	if (A == NULL || B == NULL || A->bigList == NULL || B->bigList == NULL) {
		printf(
				"List Error: calling compare() on NULL BigInteger or List reference\n");
		exit(EXIT_FAILURE);
	}
	if (isEmpty(A->bigList) || isEmpty(B->bigList)) {
		printf("List Error: calling compare() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->sign < B->sign)
		return (-1);
	else if (A->sign > B->sign)
		return (1);
	else if (A->sign == B->sign) {
		if (A->sign == 1) {
			if (length(A->bigList) > length(B->bigList))
				return (1);
			else if (length(A->bigList) < length(B->bigList))
				return (-1);
			else if (equals(A, B) == 1)
				return (0);
			else if (back(A->bigList) > back(B->bigList))
				return (1);
			else
				return (-1);
		} else if (A->sign == -1) {
			if (length(A->bigList) > length(B->bigList))
				return (-1);
			else if (length(A->bigList) < length(B->bigList))
				return (1);
			else if (equals(A, B) == 1)
				return (0);
			else if (back(A->bigList) > back(B->bigList))
				return (-1);
			else
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
	if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	if ((A->sign == B->sign) && length(A->bigList) == length(B->bigList)) {
		return (listEquals(A->bigList, B->bigList));
	} else
		return (0);
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N) {
	if (N == NULL) {
		printf("List Error: calling makeZero() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	if (!isEmpty(N->bigList)) {
		clear(N->bigList);
	}
	N->bigList = 0;

}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
	if (N == NULL) {
		printf("List Error: calling negate() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	if (N->sign == -1)
		N->sign = 1;
	if (N->sign == 1)
		N->sign = -1;
	else
		return;

}

// BigInteger Arithmetic operations -----------------------------------------------

//normalize()
//return -1 if negative, 1 if positive, 0 if =0
int normalize(List L) {
	if (L == NULL) {
		printf("List Error: calling normalize() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (front(L) < 0) {
		return (-1);
	}
	if (front(L) > 0) {
		return (1);
	} else
		return (0);
}

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char *s) {
	BigInteger b = newBigInteger();
	int len = strlen(s);
	long temp;

	if (len == 0) {
		printf("Error: Passing empty string argument\n");
		exit(EXIT_FAILURE);
	}

	if (atoi(s) == 0) {
		temp = 0;
		prepend(b->bigList, temp);
		b->sign = 0;
	} else if (s[0] == '-') {
		memmove(s, s + 1, strlen(s));
		b->sign = -1;
	} else if (s[0] == '+') {
		memmove(s, s + 1, strlen(s));
		b->sign = 1;
	} else
		b->sign = 1;

	len = strlen(s);
	char arr[POWER];

	int j = 0;
	if (len > POWER) {
		for (int i = 0; i < len; i++) {

			if (i % POWER == 0) {
				j = 0;
				temp = atoi(arr);
				append(b->bigList, temp);
			}
			arr[j] = s[i];
			j++;

			if ((len - i) < POWER) {
				int dif = len - i;
				for (j = 0; j < dif; j++) {
					arr[j] = s[i];
					i++;
				}
				temp = atoi(arr);
				append(b->bigList, temp);
			}
		}
	} else {
		temp = atoi(s);
		append(b->bigList, temp);
	}
	return (b);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
	BigInteger N2 = N;
	return (N2);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B);

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B);

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B);

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B);

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B);

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE *out, BigInteger N) {

	printf("PRINTING BIG INT\n");
	if (N->bigList == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	printList(out, N->bigList);
	printf("\n");
}
