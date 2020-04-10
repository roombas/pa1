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
char* compare(char **a, char **b);
void sortList(List L, char **arr, int size);
void swapNodes(List L, int newdata);

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
		for (int x = 0; x < MAX_LENGTH; x++) {
			arrwords[x] = malloc(sizeof(int*));
		}

		//if first precondition is passed, reads user input for files
		in = fopen(argv[1], "r");
		out = fopen(argv[2], "r+");

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
		}

		//reads txt file and places string pointers into array
		while (fgets(line, WORD_LENGTH, in) != NULL) {
			//doubles size of array if reaching max length
			if (MAX_LENGTH < count) {
				arrwords = (char**) realloc(arrwords, MAX_LENGTH * 2);
				MAX_LENGTH = MAX_LENGTH * 2;
			}
			arrwords[i] = strndup(line, WORD_LENGTH);
			i++;
		}

		/*if (newline == 0) {
			printf("%s", *arrwords);
		} else {
			for (int j = 0; j < newline + 1; j++)
				printf("%s", *(arrwords + j));
		}
		printf("\n");*/

		//create new linked list, insert pointers into list alphabetically
		List A = newList();
		//printf("%s", compare((arrwords), (arrwords + 1)));

		sortList(A, arrwords, newline + 1);

		printf("\n");
		if (newline == 0) {
			printf("%s", *arrwords);
		} else {
			for (int j = 0; j < newline + 1; j++)
				printf("%s", *(arrwords + j));
		}
		printf("\n");

		//free memory, close files
		for (int x = 0; x < MAX_LENGTH; x++) {
			free(arrwords[x]);
		}
		free(arrwords);
		fclose(in);
		fclose(out);
		return (0);
	}
}

char* compare(char **a, char **b) {
	if (strcmp(*(a), *(b)) < 0) {
		printf("String a > b\n");
		return *(a);
	}
	if (strcmp(*(a), *(b)) > 0) {
		printf("String a < b\n");
		return *(b);
	} else {
		printf("Strings are identical\n");
		return (*(a));
	}
}

void sortList(List L, char **arr, int size) {

	int x = 0;
	while (length(L) < size) {
		append(L, x);
		printf("%d\n", length(L) - 1);
		printf("%s\n", *(arr + x));
		x++;
	}
	printList(stdout, L);
	moveFront(L);

	/*	for(int i = 1; i < size; i++)
	 {
	 char * key = *(arr + i);
	 int j = i - 1;
	 while(j >= 0 && strcmp(key, *(arr + j)) < 0)
	 {
	 *(arr + (j + 1)) = *(arr + j);
	 j--;
	 }
	 *(arr + (j + 1)) = key;
	 }*/
}

 void swapNodes(List L, int newdata)
 {
	 insertBefore(L, newdata);
	 int size = index(L);
	 delete(L);
	 moveFront(L);
	 for(int i = 0; i < size; i++)
	 {
		 moveNext(L);
	 }
 }
