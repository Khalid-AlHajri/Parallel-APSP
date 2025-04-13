#ifndef COMMONNAMES_H
#define COMMONNAMES_H
// The node to be used for the binary heap structure to keep track of priorty nodes in binary heap. 
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

// A vector that contains the shortest distance to node[i] and can be used to build that path to that node.
typedef struct sp_vector{
    vector distances;
    vector parent; // parent[i] is the node that leads to node i.
} sp_vector;

#endif