//-----------------------------------------------------------------------------
// Lex.c
// Client for List ADT
// Stephanie Lu
// sqlu
// pa1
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "List.h"

char* strndup(const char *s, size_t n);
int strcmp(const char *str1, const char *str2);
char* strcpy(char* destination, const char* source);
size_t strlen(const char *str);
void sortList(List L, char **arr, int size);

int main(int argc, char *argv[]) {

	//checks for correct number of arguments
	if (argc != 3) {
		printf("Please only enter: Lex <input file> <output file>\n");
		fprintf(stderr, "Wrong input. Exiting program\n");
		exit(EXIT_FAILURE);
	} else {
		FILE *in;
		FILE *out;
		int space = 0, newline = 0, count = 0, i = 0;
		int MAX_LENGTH = 100, WORD_LENGTH = 100;
		char line[WORD_LENGTH];

		//dynamic array of pointers
		char **arrwords = malloc(MAX_LENGTH * sizeof(int*));

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

		printf("File opened\n");

		//counts all characters in file
		int c = fgetc(in);
		while (c != EOF) {
			if (c != '\n')
				count++;
			if (c == ' ')
				space++;
			if (c == '\n')
				newline++;
			c = fgetc(in);
		}
		printf("Spaces: %d\n", space);
		printf("Newlines: %d\n", newline);
		printf("Characters: %d\n", count);
		if (fseek(in, 0L, SEEK_SET) != 0) {
			printf("Repositioning error. Exiting program.\n");
			exit(EXIT_FAILURE);
		}

		//reads txt file and places string pointers into array
		while (fgets(line, WORD_LENGTH, in) != NULL) {
			//doubles size of array if reaching max length
			if (MAX_LENGTH < newline + 1) {
				arrwords = (char**) realloc(arrwords, MAX_LENGTH * 2);
				MAX_LENGTH = MAX_LENGTH * 2;
			}
			int len = strlen(line);
			if (line[len - 1] == '\n') {
				line[len - 1] = '\0';
			}
			arrwords[i] = strndup(line, WORD_LENGTH);
			i++;
		}

		//create new linked list, insert pointers into list alphabetically
		List A = newList();
		sortList(A, arrwords, newline + 1);

		/*for(i = 0; i < newline + 1; i++)
		 {
		 printf("%s", *(arrwords + i));
		 printf("\n");
		 }
		 printf("---------------------------------------\n");*/

		for (moveFront(A); index(A) >= 0; moveNext(A)) {
			printf("%d ", get(A));
			fprintf(stdout, "%s \n", *(arrwords + get(A)));
		}

		//free memory, close files
		for (int x = 0; x < MAX_LENGTH; x++) {
			free(arrwords[x]);
		}
		free(arrwords);
		freeList(&A);
		fclose(in);
		fclose(out);
		return (0);
	}
}

void sortList(List L, char **arr, int size) {

	prepend(L, 0);
	moveFront(L);
	printf("FRONT INITIALIZATION: %d \n", get(L));
	for (int i = 1; i < size; i++) {

		int cmp; //if cmp < 0, comparedVar < cursorVar
				 //if cmp > 0, cursorVar < comparedVar. Continue moving next until cursorvar > comparedVar.

		char *cursorVar = *(arr + get(L)); //cursor element, check all cursor elements on right
										   //side for greater or less than array current element
		char *comparedVar = *(arr + i);    //array current element whose
										   //right side is checked for correct position

		char string1[100];
		char string2[100];
		strcpy(string1, *(arr+i));
		strcpy(string2, *(arr + get(L)));
		cmp = strcmp(string1, string2);
		printf("%s, %s, %d\n", string1, string2, cmp );

		while ((cmp = strcmp(string1, string2)) > 0 && index(L) != -1) {
			cursorVar = *(arr + get(L));
			printf("LOOP ComparedVar: %s %d| CursorVar: %s %d | cmp: %d\n",
					*(arr + i), i, cursorVar, get(L), cmp);
			moveNext(L);
		}
		if (index(L) != -1)
			cursorVar = *(arr + get(L));

		if ((cmp = strcmp(*(arr + i), cursorVar)) < 0) {
			//GOOD CONDITION
			if (index(L) == -1) {
				moveBack(L);
				cursorVar = *(arr + get(L));
				printf(
						"***MOVEBACK cmp %d < 0 index == -1*** insert %i (%s) before cursorVar %d (%s)\n",
						cmp, i, *(arr + i), get(L), cursorVar);
				insertBefore(L, i);


				//CHECK CONDITION
			} else {
				cursorVar = *(arr + get(L));

				printf("--------------------cmp < 0 insertBefore--------------------\n");
				printf(
						"***cmp %d < 0 *** insert %i (%s) before cursorVar %d (%s)\n",
						cmp, i, *(arr + i), get(L), cursorVar);
				insertBefore(L, i);
			}
		} else if ((cmp = strcmp(*(arr + i), cursorVar)) > 0) {

			printf("ELSE STATEMENT END INDEX: %d ", index(L));
			//printf("--------------------else APPEND--------------------\n");
			if (index(L) == -1) {
				printf("index == -1 ELSE STATEMENT\n");
				//cursorVar = *(arr + get(L));
				//printf("*** index != -1 && cmp = %d*** CursorVar: %s %d\n",
				//		cmp, cursorVar, get(L));
				append(L, i);
			} else {
				printf(
						"***APPEND *** cmp = %d insert: %i (%s) at end of list\n",
						cmp, i, *(arr + i));
				insertAfter(L, i);
			}
		} else {
			printf("LAST OPTION-----------------\n");
			insertBefore(L,i);
		}
		moveFront(L);
	}

}
