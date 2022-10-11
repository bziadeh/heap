#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "heap.h"  

#define DEBUG 1

// CSE 3318 - Brennan Ziadeh 1001773667

struct heap_struct make_heap_empty(int cap) {
    struct heap_struct empty;
    empty.capacity = cap;
    empty.N = 0;
    empty.items = calloc(cap, sizeof(int));
    return empty;
}

void add(struct heap_struct * heapP, int new_item) {
    int size = heapP->N;
    bool resize = (size == heapP->capacity);
    if(resize) {
        heapP->capacity *= 2;
        int *increase = realloc(heapP->items, heapP->capacity * sizeof(int));
        if(increase) {
            heapP->items = increase;     
        }
    }
    int *items = heapP->items;
    items[size] = new_item;

    size++;
    heapP->N = size;
    for(int p = ((heapP->N-2)/2); p >= 0; p--) {
        sink_down(p, heapP->N, heapP->items);
    }
}

struct heap_struct make_heap(int N, int * arr) { 
    struct heap_struct heap;
    heap.capacity = N;
    heap.N = N;
    heap.items = arr;
    
    if(DEBUG) {
        printf("in function make_heap, in DEBUG MODE, printing array BEFORE it gets turned into a heap\n");
        print_heap(heap);
    }
    
    for(int p = ((N-2)/2); p >= 0; p--) {
        sink_down(p, N, arr);

        if(DEBUG) {
            printf("in fuction make_heap, in DEBUG MODE, printing array after sink_down at index %d\n", p);
            print_heap(heap);
        }
    }
    
    return heap;
}

void destroy(struct heap_struct * heapP) {
    if(heapP->items) {
        free(heapP->items);
    }
}

void print_heap(struct heap_struct heapS) {
    int size = heapS.N;
    int capacity = heapS.capacity;
    
    printf("Heap:  size: %d, capacity: %d\n", size, capacity);
    printf("indexes:   ");
    for(int i = 0; i < size; i++) {
        printf("  %3d,", i);
    }

    int *items = heapS.items;
    printf("\nvalues:    ");
    for(int i = 0; i < size; i++) {
        printf("  %3d,", items[i]);
    }
    
    printf("\n\n");
}

int index_max_value(int *arr, int N, int p) {
    int imv = p;
    int left = (p * 2) + 1;
    int right = (p * 2) + 2;

    if((left < N) && (arr[left]>arr[imv]))  imv = left;
    if((right < N) && (arr[right]>arr[imv]))  imv = right;

    return imv;
}

void sink_down(int i, int N, int * arr) {
    int p = i;
    int imv = index_max_value(arr, N, p);

    while((imv != p) && (imv < N)) {
        int at_imv = arr[imv];
        arr[imv] = arr[p];
        arr[p] = at_imv;
        p = imv;
        imv = index_max_value(arr, N, p);
    }
}

void swim_up(int idx, int * arr) {
    while((idx > 0) && (arr[idx]>arr[idx/2])) {
        int at_idx = arr[idx];
        arr[idx] = arr[idx/2];
        arr[idx/2] = at_idx;
    }
}

int poll(struct heap_struct * heapP) {
    if(heapP->N == 0) {
        printf("Empty heap. No remove performed.\n");
        return 0;
    }
    int *arr = heapP->items;
    int *N = &(heapP->N);

    int max = arr[0];
    int last_index = (*N) - 1;

    arr[0] = arr[(last_index)];
    (*N) = (*N) - 1;
    sink_down(0, *N, arr);
    return max;
}

int peek(struct heap_struct heapS) {
    return heapS.items[0];
}