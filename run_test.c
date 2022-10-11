#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// CSE 3318 - Brennan Ziadeh 1001773667

int main() {

	int N,k,i;
	char fname[501];
	int debug = 0;
	struct heap_struct heapS;
	printf("This program will call the heap functions.\n");   
   

	N = 3;
	int *arr = (int*) calloc(N, sizeof(int) );
	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 43;

    heapS = make_heap(N, arr);         
	print_heap(heapS);

	printf("removed: %6d\n", poll(&heapS) );	
	print_heap(heapS);

	printf("peek:    %6d\n", peek(heapS) );
	print_heap(heapS);
	
	printf("add:     %6d\n", 17);	
	add(&heapS, 17);
	print_heap(heapS);
	
	printf("removed: %6d\n", poll(&heapS) );	
	print_heap(heapS);

	printf("removed: %6d\n", poll(&heapS) );	
	print_heap(heapS);
    return 0;
}