//-----------------------------------------------------------------------------
// Arithmetic.c
// Client for BigInteger ADT
// Stephanie Lu, sqlu
// 2020 Spring CSE101 PA1
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "List.h"
#include "BigInteger.h"
#define MAX_LEN 300
#define LINE 4

int main(int argc, char *argv[]) {

	//checks for correct number of arguments
	if (argc != 3) {
		printf("Please only enter: Arithmetic <input file> <output file>\n");
		fprintf(stderr, "Wrong input. Exiting program\n");
		exit(EXIT_FAILURE);
	}
	FILE *in, *out;
	int line_count, word_count;
	char line[MAX_LEN];
	char *token;
	char arrnum[LINE][MAX_LEN];
	char bigInt1[MAX_LEN];
	char bigInt2[MAX_LEN];

	//if first precondition is passed, reads user input for files
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	//if input file cannot be found, exit program
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if (out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	line_count = 0;
	word_count = 0;
	while (fgets(line, MAX_LEN, in) != NULL) {
		word_count++;
		token = strtok(line, "\n");

		while (token != NULL) { // we have a token
			strcpy(arrnum[line_count], token);
			if (line_count == 1) {
				strcpy(bigInt1, token);
			}
			if (line_count == 3) {
				strcpy(bigInt2, token);
			}
			// get next token
			token = strtok(NULL, "\n");
		}
		line_count++;
	}

	/*BigInteger B = newBigInteger();
	 B = stringToBigInteger(bigInt1);
	 printBigInteger(stdout, B);*/

	/*puts(bigInt1);
	 char arr1[100];
	 for(int i = 0; i < 9; i++)
	 {
	 arr1[i] = bigInt1[i];
	 }
	 long x = atoi(arr1);
	 printf("X EQUALS: %ld\n", x);*/
	/*int i = 0;
	 while (i < strlen(bigInt1)) {
	 printf("%s", bigInt1[i]);
	 //fputs(arrnum[i], stdout);
	 printf("\n");
	 i++;
	 }

	 int size = strlen("");
	 printf("SIZE BIGINT2: %u\n", size);

	 char* c = bigInt2[0];
	 long si = atoi(c);
	 printf("SIZE: %lu\n", si);*/

	/*************TEST*****************/

	printf("First letter: %c\n", bigInt1[8]);

	printf("WANT: \n");
	puts(bigInt1);
	printf("************\n");

	int len = strlen(bigInt1);
	long temp;

	if (len == 0) {
		printf("Error: Passing empty string argument\n");
		exit(EXIT_FAILURE);
	}

	if (atoi(bigInt1) == 0) {
		temp = 0;
	} else if (bigInt1[0] == '-') {
		memmove(bigInt1, bigInt1 + 1, strlen(bigInt1));
	} else if (bigInt1[0] == '+') {
		memmove(bigInt1, bigInt1 + 1, strlen(bigInt1));
	} else
		printf("HAVE: \n");

	int POWER = 9;
	char * arr = malloc (POWER+1 * sizeof(char));
	len = strlen(bigInt1);
	if (len > POWER) {
		int j = 0;
		for (int i = 0; i < len; i++) {
			arr[j] = bigInt1[i];
			j++;
			if ((i+1) % POWER == 0) {
				arr[j] = '\0';
				temp = atoi(arr);
				printf("FIRST COND %ld     ", temp);
				j = 0;
			}
			else if ((len - i) < POWER) {
				int dif = len - i;
				for (j = 0; j < dif; j++) {
					arr[j] = bigInt1[i];
					i++;
				}
				arr[j] = '\0';
				temp = atoi(arr);
				printf("SECOND COND %ld     ", temp);
				break;
			}
		}
	} else {
		temp = atoi(bigInt1);
		printf("%ld     ", temp);
	}

	/***********************************/

	free(arr);
	fclose(in);
	fclose(out);

}
