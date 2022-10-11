#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "heap.h"  

#define DEBUG 1

// CSE 3318 - Brennan Ziadeh 1001773667

struct heap_struct make_heap_empty(int cap) {
    struct heap_struct *empty = malloc(sizeof(struct heap_struct));
    empty->capacity = cap;
    empty->N = 0;
    empty->items = malloc(sizeof(int) * cap);
    return *empty;
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
}

struct heap_struct make_heap(int N, int * arr) { 
    struct heap_struct heap = make_heap_empty(N);

    heap.N++;
    sink_down(N, N, arr);

    for(int p = (N/2); p >= 0; p--) {
        heap.N++;
        sink_down(p, N, arr);
    }

    heap.items = arr;
    return heap;
}

void destroy(struct heap_struct * heapP) {
    if(heapP) {
        if(heapP->items) {
            free(heapP->items);
        }
        free(heapP);
    }
}

void print_heap(struct heap_struct heapS) {
    int size = heapS.N;
    int capacity = heapS.capacity;
    
    printf("Heap:  size: %d, capacity: %d\n", size, capacity);
    printf("indexes:   ");
    for(int i = 0; i < size; i++) {
        printf("%d,   ", i);
    }

    int *items = heapS.items;
    printf("\nvalues:    ");
    for(int i = 0; i < size; i++) {
        printf("%d,   ", items[i]);
    }
    
    printf("\n\n");
}

int index_max_value(int *arr, int parent, int left, int right, int N) {
    int imv = parent;

    if((left < N) && (arr[left]>arr[imv]))
        imv = left;
    
    if((right < N) && (arr[right]>arr[imv]))
        imv = right;

    return imv;
}

void sink_down(int i, int N, int * arr) {
    int left = 2 * i;
    int right = (2 * i) + 1;
    int imv = index_max_value(arr, i, left, right, N);

    while((imv != i) && (imv <= N)) {
        int at_imv = arr[imv];
        arr[imv] = arr[i];
        arr[i] = at_imv;
        i = imv;
        left = 2 * i;
        right = (2 * i) + 1;
        imv = index_max_value(arr, i, left, right, N);
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