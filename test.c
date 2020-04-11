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
size_t strlen(const char *str);
char* compare(char **a, char **b);
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
		printList(stdout, A);


		for(i = 0; i < newline + 1; i++)
		{
			printf("%s", *(arrwords + i));
			printf("\n");
		}
		printf("---------------------------------------\n");

		for (moveFront(A); index(A) >= 0; moveNext(A)) {
			printf("%d", get(A));
			fprintf(stdout, "%s\n", *(arrwords + get(A)));
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

char* compare(char **a, char **b) {
	if (strcmp(*(a), *(b)) < 0) {
		printf("String a < b\n");
		return *(a);
	}
	if (strcmp(*(a), *(b)) > 0) {
		printf("String a > b\n");
		return *(b);
	} else {
		printf("Strings are identical\n");
		return (*(a));
	}
}

void sortList(List L, char **arr, int size) {


	for (int i = 1; i < size; i++) {

		if(isEmpty(L))
		{
			prepend(L, 0);
			moveFront(L);
			printf("FRONT INITIALIZATION: %d \n", get(L));
		}

		char *cursorVar = *(arr + get(L)); //cursor element, check all cursor elements on right
										   //side for greater or less than array current element
		char *comparedVar = *(arr + i);    //array current element whose
										   //right side is checked for correct position
		int cmp; //if cmp < 0, comparedVar < cursorVar
				 //if cmp > 0, cursorVar < comparedVar
		while ((cmp = strcmp(comparedVar, cursorVar)) > 0 && index(L) != -1) {
			//printf("( %s | %s | %d | get(L)%d)\n", cursorVar, comparedVar, strcmp(comparedVar, cursorVar), get(L));
			cursorVar = *(arr + get(L));
			printf("CursorVar: %s %d", cursorVar, get(L));
			moveNext(L);
		}
		//if cursor reaches end, comparedVar > all cursor variables
		if (cmp < 0) {
			if(index(L) == -1)
			{
				moveBack(L);
				printf("CursorVar: %s %d", cursorVar, get(L));
				//printf("MOVEBACK. insert %i (%s) before cursorVar %d (%s)\n", i, comparedVar, get(L), cursorVar);
			}
			printf("----------------------------------------\n");
			//printf("***cmp < 0 *** insert %i (%s) before cursorVar %d (%s)\n", i, comparedVar, get(L), cursorVar);
			printf("CursorVar: %s %d", cursorVar, get(L));
			insertBefore(L, i);
		}
		else
		{
			printf("----------------------------------------\n");
			if(index(L) != -1)
			printf("CursorVar: %s %d\n", cursorVar, get(L));
			//printf("***APPEND *** insert: %i (%s) at end of list\n", i, comparedVar);
			append(L, i);
		}
		moveFront(L);
	}

}
