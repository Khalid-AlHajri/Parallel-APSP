
#ifndef ADJLIST_H
#define ADJLIST_H

#include "commonnames.h"
// Function to read a graph from a .gr file into an adjacency list
adjList* read_adjlist_from_gr(const char* filename, int* numNodes);

#endif
