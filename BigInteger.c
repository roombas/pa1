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
	if (pN == NULL)
		printf("---freeBigInteger--pN=NULL-\n");
	else if (*pN == NULL)
		printf("---freeBigInteger--*pN=NULL-\n");
	else {
		if (((*pN)->bigList) != NULL)
			freeList(&((*pN)->bigList));
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

	int lenA = length(A->bigList);
	int lenB = length(B->bigList);
	if (A->sign < B->sign)
		return (-1);
	else if (A->sign > B->sign)
		return (1);
	else if (A->sign == B->sign) {
		if (A->sign == 1) {
			if (lenA > lenB)
				return (1);
			else if (lenA < lenB)
				return (-1);
			else if (equals(A, B) == 1)
				return (0);
			else if (back(A->bigList) == back(B->bigList) && lenA != 1
					&& lenB != 1) {
				for (moveBack(A->bigList), moveBack(B->bigList);
						index(A->bigList) >= 0;
						movePrev(A->bigList), movePrev(B->bigList)) {
					long a = get(A->bigList);
					long b = get(B->bigList);
					if (a > b)
						return 1;
					if (a < b)
						return -1;
				}
			} else if (back(A->bigList) > back(B->bigList))
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
		} else
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
	N->sign = 0;

}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
	if (N == NULL) {
		printf("List Error: calling negate() on NULL BigInteger reference\n");
		exit(EXIT_FAILURE);
	}
	if (sign(N) == -1)
		N->sign = 1;
	else if (sign(N) == 1)
		N->sign = -1;
	else
		return;

}

// BigInteger Arithmetic operations -----------------------------------------------

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

	//condition to see if s = 0 and if it is + or -
	if (atoi(s) == 0) {
		printf("Is zero\n");
		b->sign = 0;
	} else if (s[0] == '-') {
		memmove(s, s + 1, strlen(s));
		b->sign = -1;
	} else if (s[0] == '+') {
		memmove(s, s + 1, strlen(s));
		b->sign = 1;
	} else
		b->sign = 1;

	//condition to remove all beginning 0's
	while (s[0] == '0') {
		memmove(s, s + 1, strlen(s));
	}

	len = strlen(s);
	char *arr = malloc(POWER + 1 * sizeof(char));

	int j = POWER - 1;
	if (len > POWER) {
		for (int i = len - 1; i >= 0; i--) {
			arr[j] = s[i];
			j--;
			if (((len - i) % POWER) == 0) {
				arr[POWER] = '\0';
				temp = atoi(arr);
				append(b->bigList, temp);
				j = POWER - 1;
			}
		}
		if (j != POWER - 1) {
			int remainder = POWER - (len % POWER);
			memmove(arr, arr + remainder, strlen(arr));
			arr[len % POWER] = '\0';
			temp = atoi(arr);
			append(b->bigList, temp);
		}
	} else {
		s[len] = '\0';
		temp = atoi(s);
		append(b->bigList, temp);
	}

	free(arr);
	return (b);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
	BigInteger pN2 = newBigInteger();
	pN2->sign = N->sign;
	freeList(&(pN2->bigList));
	pN2->bigList = copyList(N->bigList);
	return (pN2);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
	//use cursor, iterate through current S->bigList. Append after until every node of (A+B)
	//is iterated through
	BigInteger temp = sum(A, B);
	if (length(temp->bigList) >= length(S->bigList)) {
		for (moveFront(temp->bigList), moveFront(S->bigList);
				index(temp->bigList) >= 0; moveNext(temp->bigList)) {
			if (index(S->bigList) >= 0) {
				set(S->bigList, get(temp->bigList));
				moveNext(S->bigList);
			} else
				append(S->bigList, get(temp->bigList));
		}
	} else {
		for (moveFront(temp->bigList), moveFront(S->bigList);
				index(temp->bigList) >= 0;
				moveNext(temp->bigList), moveNext(S->bigList)) {
			set(S->bigList, get(temp->bigList));
		}
		int remainingLoop = length(S->bigList) - (index(S->bigList) - 1);
		for (int i = 0; i < remainingLoop; i++) {
			deleteBack(S->bigList);
		}
	}
	S->sign = temp->sign;
	freeBigInteger(&temp);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B) {
	if (A == NULL || B == NULL || isEmpty(A->bigList) || isEmpty(B->bigList)) {
		printf("Error: calling sum() on NULL BigInteger or empty List");
		exit(EXIT_FAILURE);
	}
	BigInteger S = newBigInteger();
	long carryover = 0;
	long temp = 0, _A_INT = 1, _B_INT = 1, signA = 1, signB = 1;

	// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
	if (sign(A) < 0 && sign(B) < 0) { // (-A) + (-B)
		signA = (-1) * sign(A); //negate(A);
		signB = (-1) * sign(B); //negate(B);
		S->sign = -1;
	} else if (sign(A) < 0 && sign(B) >= 0) { //(-A) + (B) or 0
		negate(A);
		if (compare(A, B) == 1) {
			signB = (-1) * sign(B); //negate(B);
			S->sign = -1;
		} else {
			signA = (-1) * sign(A); //negate(A);
			S->sign = 1;
		}
		negate(A);
	} else if (sign(A) >= 0 && sign(B) < 0) { //(A) or 0 + (-B)
		negate(B);
		if (compare(A, B) == -1) {
			signA = (-1) * sign(A); //negate(A);
			S->sign = -1;
		} else {
			signB = (-1) * sign(B); //negate(B);
			S->sign = 1;
		}
		negate(B);
	} else
		S->sign = 1;

	//if length(A) == length(B)
	if (length(A->bigList) == length(B->bigList)) {
		for (moveFront(A->bigList), moveFront(B->bigList);
				index(A->bigList) >= 0;
				moveNext(A->bigList), moveNext(B->bigList)) {
			_A_INT = signA * get(A->bigList);
			_B_INT = signB * get(B->bigList);
			temp = _A_INT + _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp > BASE) {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			} else {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			}
		}
		if (carryover != 0) {
			append(S->bigList, carryover);
		}

		//if length(A) > length(B)
	} else if (length(A->bigList) > length(B->bigList)) {
		for (moveFront(A->bigList), moveFront(B->bigList);
				index(B->bigList) >= 0;
				moveNext(A->bigList), moveNext(B->bigList)) {
			_A_INT = signA * get(A->bigList);
			_B_INT = signB * get(B->bigList);
			temp = _A_INT + _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
		}
		int remaining = length(A->bigList) - index(A->bigList);
		for (int i = remaining; i > 0; i--) {
			_A_INT = signA * get(A->bigList);
			temp = _A_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;

			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
			if (index(A->bigList) != (length(A->bigList) - 1))
				moveNext(A->bigList);
		}
		//if length(A) < length(B)
	} else {
		for (moveFront(A->bigList), moveFront(B->bigList);
				index(A->bigList) >= 0;
				moveNext(A->bigList), moveNext(B->bigList)) {
			_A_INT = signA * get(A->bigList);
			_B_INT = signB * get(B->bigList);
			temp = _A_INT + _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
		}
		int remaining = length(B->bigList) - index(B->bigList);
		for (int i = remaining; i > 0; i--) {
			_B_INT = signB * get(B->bigList);
			temp = _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
			if (index(B->bigList) != (length(B->bigList) - 1))
				moveNext(B->bigList);
		}

	}
	return (S);
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
	makeZero(D);
	BigInteger temp = diff(A, B);
	for (moveFront(temp->bigList); index(temp->bigList) >= 0;
			moveNext(temp->bigList)) {
		append(D->bigList, get(temp->bigList));
	}
	D->sign = temp->sign;
	freeBigInteger(&temp);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
	if (A == NULL || B == NULL || isEmpty(A->bigList) || isEmpty(B->bigList)) {
		printf("Error: calling diff() on NULL BigInteger or empty List");
		exit(EXIT_FAILURE);
	}
	BigInteger S = newBigInteger();
	long carryover = 0, signA = 1, signB = 1;
	long temp = 0, _A_INT = 1, _B_INT = 1;

	// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
	if (sign(A) >= 0 && sign(B) >= 0) { //A - B = A + (-B)
		if (compare(A, B) == -1) { // if A < B, make (-A) + B = -S
			signA = (-1) * sign(A); //negate(A);
			S->sign = -1;
		} else if (compare(A, B) == 1) {
			signB = (-1) * sign(B);
			S->sign = 1;
		}
	} else if (sign(A) >= 0 && sign(B) < 0) { //A or 0 - (-B) = A + B
		signB = (-1) * sign(B); //negate(B);
		S->sign = 1;
	} else if (sign(A) < 0 && sign(B) >= 0) { //(-A)-(B) or 0 = (-A)+(-B) = -1(A+B)
		signA = (-1) * sign(A); //negate(A);
		S->sign = -1;
	} else if (sign(A) < 0 && sign(B) < 0) { //(-A) - (-B) = -A + B = B + (-A)
		negate(A);
		negate(B);
		if (compare(A, B) == 1) {
			signB = (-1) * sign(B); //negate(B);
			S->sign = -1;
		} else if (compare(A, B) == -1) {
			signA = (-1) * sign(A); //negate(A);
			S->sign = 1;
		} else {
			signA = 1;
			signB = -1;
		}
		negate(A);
		negate(B);
	}

	if (length(A->bigList) == length(B->bigList)) {
		for (moveFront(A->bigList), moveFront(B->bigList);
				index(A->bigList) >= 0;
				moveNext(A->bigList), moveNext(B->bigList)) {
			_A_INT = signA * get(A->bigList);
			_B_INT = signB * get(B->bigList);
			temp = _A_INT + _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp > BASE) {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			} else {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			}
		}
		if (carryover != 0) {
			append(S->bigList, carryover);
		}

		//if length(A) > length(B)
	} else if (length(A->bigList) > length(B->bigList)) {
		for (moveFront(A->bigList), moveFront(B->bigList);
				index(B->bigList) >= 0;
				moveNext(A->bigList), moveNext(B->bigList)) {
			_A_INT = signA * get(A->bigList);
			_B_INT = signB * get(B->bigList);
			temp = _A_INT + _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
		}
		int remaining = length(A->bigList) - index(A->bigList);
		for (int i = remaining; i > 0; i--) {
			_A_INT = signA * get(A->bigList);
			temp = _A_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
			if (index(A->bigList) != (length(A->bigList) - 1))
				moveNext(A->bigList);
		}
		//if length(A) < length(B)
	} else {
		for (moveFront(A->bigList), moveFront(B->bigList);
				index(A->bigList) >= 0;
				moveNext(A->bigList), moveNext(B->bigList)) {
			_A_INT = signA * get(A->bigList);
			_B_INT = signB * get(B->bigList);
			temp = _A_INT + _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
		}
		int remaining = length(B->bigList) - index(B->bigList);
		for (int i = remaining; i > 0; i--) {
			_B_INT = signB * get(B->bigList);
			temp = _B_INT + carryover;
			if (temp < BASE && temp >= 0) {
				append(S->bigList, temp);
				carryover = 0;
			} else if (temp < 0) {
				temp = temp + BASE;
				carryover = -1;
				append(S->bigList, temp);
			} else {
				temp = temp - BASE;
				carryover = 1;
				append(S->bigList, temp);
			}
			if (index(B->bigList) != (length(B->bigList) - 1))
				moveNext(B->bigList);
		}

	}
	return (S);

}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {
	makeZero(P);
	BigInteger temp = prod(A, B);
	for (moveFront(temp->bigList); index(temp->bigList) >= 0;
			moveNext(temp->bigList)) {
		append(P->bigList, get(temp->bigList));
	}
	P->sign = temp->sign;
	freeBigInteger(&temp);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {
	BigInteger temp = newBigInteger();
	BigInteger temp2 = newBigInteger();
	//BigInteger finalInt = newBigInteger();
	long product;
	long insert;
	long carryOver = 0;
	int count = 0;

	append(temp2->bigList, 0);

	for (moveFront(A->bigList); index(A->bigList) >= 0; moveNext(A->bigList)) {
		if (count != 0) {
			for (int j = 0; j < count; j++) {
				append(temp->bigList, 0);
			}
		}

		for (moveFront(B->bigList); index(B->bigList) >= 0;
				moveNext(B->bigList)) {
			product = get(A->bigList) * get(B->bigList) + carryOver;
			insert = product - ((product / BASE) * BASE);
			carryOver = product / BASE;
			append(temp->bigList, insert);
		}
		if (carryOver != 0) {
			append(temp->bigList, carryOver);
		}

		add(temp2, temp, temp2);
		makeZero(temp);
		carryOver = 0;
		product = 0;
		insert = 0;
		count++;
	}
	temp2->sign = (A->sign) * (B->sign);

	return (temp2);
}

/*void reverseList(BigInteger input)
 {
 BigInteger Output = newBigInteger();
 //reverse list
 for (moveFront(temp2->bigList); index(temp2->bigList) >= 0;
 moveNext(temp2->bigList)) {
 prepend(finalInt->bigList, get(temp2->bigList));
 }
 freeBigInteger(&temp);
 freeBigInteger(&temp2);
 }*/

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE *out, BigInteger N) {

	if (N->bigList == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if (N->sign == 0) {
		fprintf(out, "%d\n\n", 0);
		return;
	}
	if (N->sign == -1)
		fprintf(out, "-");
	printList(out, N->bigList);
}
