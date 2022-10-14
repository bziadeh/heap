#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// CSE 3318 - Brennan Ziadeh 1001773667

int main() {
	printf("This program will create a max-heap and perform operations on it based on data from a file.\n\n");

	char fname[501];
	printf("Enter a file name: ");
	scanf("%s", fname);

	// attempt to load the file from the user	
	// notify if not found
	FILE *file = fopen(fname, "r");
	if(!file) {
		printf("The specified file could not be found.\n");
		return 0;
	}

	int size;
	fscanf(file, "%d", &size);

	int *items = calloc(size, sizeof(int));
	int data;

	// load the array from the file and 
	// create a heap using the data
	for(int i = 0; i < size; i++) {
		fscanf(file, "%d", &data);
		items[i] = data; 
	}
	struct heap_struct heap = make_heap(size, items);
	print_heap(heap);

	// parse the operations from the file
	// and execute them on the heap
	int operations_size;
	fscanf(file, "%d", &operations_size);

	char operation[10];
	for(int i = 0; i < operations_size; i++) {
		fscanf(file, "%s", operation);

		printf("Operation number %d, string: %s\n", i+1, operation);
		if(operation[0] == 'P' || operation[0] == 'p') {
			
			// only take the largest value from the heap
			// without removing it
			int value = peek(heap);
			printf("peek:  %d\n", value);
			
		} else if(operation[0] == '*') {
			
			// remove the largest value from the heap and
			// reorganize the values
			int value = poll(&heap);
			printf("removed:  %d\n", value);

		} else {

			int value = atoi(operation);
			add(&heap, value);
			printf("added:  %d\n", value);
		}

		// print the heap after every operation
		// is executed to see the new result
		print_heap(heap);
	}

	destroy(&heap);
	fclose(file);
    return 0;
}