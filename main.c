/*
 *  This is a Final Year Project developed to obtain the shortest paths between every pair of vertices in a 
 *  positive-weight graph in a parallel manner.;
 *  It uses Dijkstra's algorithm on each node on separate run on a different thread.
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "adjlist.h"
#include "algorithms.h"
#include <time.h>
#include "util.h"

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 0
#endif

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s thread_count graph_file", argv[0]);
        exit(-1);
    }
    int nodes = 0;
    struct timespec start, end;
    FILE* file = fopen(argv[2], "r");
    adjList* graph = read_adjlist_from_gr(file, &nodes);

    int tcount = atoi(argv[1]);

    clock_gettime(CLOCK_MONOTONIC, &start);
    sp_vector* res = apsp_dijkstra(graph, nodes, tcount);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %f seconds\n", elapsed);
    return 0;
}