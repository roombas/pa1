//-----------------------------------------------------------------------------
// Lex.c
// Client for List ADT
// Stephanie Lu, sqlu
// 2020 Spring CSE101 PA1
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "List.h"

char* strndup(const char *s, size_t n);
int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);
void sortList(char ** arr, int size, FILE * out);

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
		int MAX_LENGTH = 1000, WORD_LENGTH = 100;
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
		printf("NEWLINE: %d\n", newline);
		if (fseek(in, 0L, SEEK_SET) != 0) {
			printf("Repositioning error. Exiting program.\n");
			exit(EXIT_FAILURE);
		}

		//reads txt file and places string pointers into array
		while (fgets(line, WORD_LENGTH, in) != NULL) {
			//doubles size of array if reaching max length
			/*while (MAX_LENGTH < newline) {
				arrwords = (char**) realloc(arrwords, MAX_LENGTH * 2);
				MAX_LENGTH = MAX_LENGTH * 2;
			}*/
			int len = strlen(line);
			if (line[len - 1] == '\n') {
				line[len - 1] = '\0';
			}
			*(arrwords + i) = strndup(line, WORD_LENGTH);
			i++;
		}

		sortList(arrwords, newline, out);

		//free memory, close files
		for (int x = 0; x < MAX_LENGTH; x++) {
			if((*arrwords + x) != NULL)
			{
			free(*(arrwords + x));
			*(arrwords + x) = NULL;
			}
		}
		free(arrwords);
		fclose(in);
		fclose(out);
		return (0);
	}
}

void sortList(char ** arr, int size, FILE * out) {

	//create new linked list, insert pointers into list alphabetically
	List L = newList();

	prepend(L, 0);
	moveFront(L);
	printf("INITIALIZATION\n");
	for (int i = 1; i < size; i++) {

		int cmp; //if cmp < 0, comparedVar < cursorVar
				 //if cmp > 0, cursorVar < comparedVar. Continue moving next until cursorvar > comparedVar.

		//printf("BEFORE WHILE LOOP\n");
		if (length(L) != 1) {
			while ((cmp = strcmp(*(arr + i), *(arr + get(L)))) > 0
					&& index(L) != -1) {
				moveNext(L);
				if(index (L) == -1)
					break;
				//printf("%s, %d \n", *(arr + get(L)), get(L));
				//printf("LOOPING %d times, index = %d, length = %d\n", i, index(L), length(L));
			}
		}
		else if(length(L) == 1)
			(cmp = strcmp(*(arr + i), *(arr + 0)));

		if (cmp < 0) {
			//printf("cmp < 0 i( %d ) \n", i);
			if (index(L) == -1) {
				//printf("INDEX == -1 cmp < 0 i( %d ) \n", i);
				moveBack(L);
				insertBefore(L, i);

			} else {
				//printf("INDEX != -1 cmp < 0 i( %d ) \n", i);
				insertBefore(L, i);
			}
		} else if (cmp > 0) {

			if (index(L) == -1) {
				//printf("APPENDING cmp > 0 != -1 cmp < 0 i( %d ) \n", i);
s			} else {
				//printf("INSERTAFTER cmp > 0 != -1 cmp < 0 i( %d ) \n", i);
				insertAfter(L, i);
			}
		} else {
			//printf("LAST ELSE cmp > 0 != -1 cmp < 0 i( %d ) \n", i);
			insertBefore(L, i);
		}
		//printf("BEFORE MOVEFRONT");
		moveFront(L);
	}

	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		//printf("%d ", get(L));
		fprintf(out, "%s \n", *(arr + get(L)));
	}

	freeList(&L);


}
