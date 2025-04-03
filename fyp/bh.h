/**
 * This file contains the implementation of a binary heap with geometric memory scaling.
*/
#ifndef BH_H
#define BH_H
#include "commonnames.h"
#include <stdlib.h>

typedef struct{
    int capacity;
    int length;
    bindij_node* array;
} BinHeap;


int bh_init(BinHeap* h, int size);
bindij_node bh_pop(BinHeap* h);
int bh_insert(BinHeap* h, bindij_node v);
int bh_delete(BinHeap* h);

#endif