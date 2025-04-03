/**
 * This file contains an implementation for the binary heap data structure to be used by Dijkstra's algorithm. 
 */
#include "bh.h"


int bh_init(BinHeap* h, int size) {
    if (size <= 0) size = 1;
    h->array = malloc(sizeof(bindij_node) * size);
    if (h->array == NULL) return 0;
    h->length = 0;
    h->capacity = size;
    return 1;
}

int bh_insert(BinHeap* h, bindij_node v) {
    if (h->capacity == h->length) return -1; // No resize for now.
    h->length++;
    h->array[h->length - 1] = v;
    int i = h->length - 1;
    while (i > 0) {
        if (h->array[i].prio <  h->array[(i - 1) / 2].prio) {
            h->array[i] = h->array[(i-1)/2];
            h->array[(i-1)/2] = v;
            i = (i - 1) / 2;
        } 
        else break;
    }
    return 1;
}

bindij_node bh_pop(BinHeap* h) {
    if (h->length == 0) return (bindij_node){-1, -1}; // Error value.
    bindij_node min = h->array[0];
    h->length--;
    h->array[0] = h->array[h->length];
    int i = 0;
    while (i < h->length) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < h->length && h->array[left].prio < h->array[smallest].prio) {
            smallest = left;
        }
        if (right < h->length && h->array[right].prio < h->array[smallest].prio) {
            smallest = right;
        }
        if (smallest != i) {
            bindij_node temp = h->array[i];
            h->array[i] = h->array[smallest];
            h->array[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return min;
}

int bh_delete(BinHeap* h) {
    if (h->array == NULL) return 1;
    free(h->array);
    h->array = NULL;
    return 1;
}