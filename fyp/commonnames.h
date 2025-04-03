#ifndef COMMONNAMES_H
#define COMMONNAMES_H
// The node to be used for the binary heap structure to keep track of priorty nodes in binary heap.
#include <stdio.h> // Needed for error messages
typedef struct{
    int prio;
    int node;
} bindij_node;

typedef struct vector {
    int length;
    int* data;
} vector;

typedef struct adjList{
    int length;
    bindij_node* data;
} adjList;

#endif
