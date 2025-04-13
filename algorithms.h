#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <stdlib.h>
#include "commonnames.h"
#include <pthread.h>
#include "bh.h"

sp_vector dijkstra(adjList* graph, int numNodes, int source);

typedef struct {
    adjList* graph;
    int numNodes;
    int startNode;
    int numNodesToProcess;
    sp_vector* apsp_matrix;
} DijkstraThreadArgs;

void* dijkstra_thread(void* args);

sp_vector* apsp_dijkstra(adjList* graph, int numNodes, int nThreads);

#endif