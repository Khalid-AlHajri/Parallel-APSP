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
    h->array[h->length - 1] = v;
    int i = h->length - 1;
    while ((i - 1) / 2 > 0) {
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
    bindij_node res = h->array[0];
    h->array[0] = h->array[h->length - 1];
    h->length--;
    if (h->length == 0) return res;

    int i = 0;
    while (i * 2 + 1 < h->length) {
        int j = i * 2 + 1;
        if (i * 2 + 2 < h->length && h->array[j+1].prio < h->array[j].prio) {
            j = j + 1;
        }
        bindij_node tmp = h->array[i];
        h->array[i] = h->array[j];
        h->array[j] = tmp;
        i = j;
    }

    return res;
}

int bh_delete(BinHeap* h) {
    if (h->array == NULL) return 1;
    free(h->array);
    h->array = NULL;
    return 1;
}