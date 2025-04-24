/**
 * This Program runs the APSP algorithm on a graph and outputs the time required to run the algorithm
 * on that graph. The program utilizes a variable number of threads which must be specified along with
 * the path to the .gr graph file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"
#include "adjlist.h"

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
    printf("%f\n", elapsed);
    return 0;
}