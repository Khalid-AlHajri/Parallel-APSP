/**
 * This program runs the APSP algorithm on a graph and outputs the resulting apsp matrix to standard
 * output. The main purpose of this program is to be used by external programs to test the correctness 
 * of the apsp algorithm. It takes as input parameters the path to the graph file to calculate APSP for,
 * and an arbitrary number of threads, preferably suitable to the number of availabe CPUs.
 */

#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"
#include "adjlist.h"
#include "util.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s thread_count path_to_graph", argv[0]);
        exit(-1);
    }
    int thread_count = atoi(argv[1]);
    if (thread_count <= 0) {
        printf("Invalid thread count.");
        exit(-1);
    }
    FILE* file = fopen(argv[2], "r");
    int numNodes;
    adjList* graph = read_adjlist_from_gr(file, &numNodes);
    sp_vector* res_mat = apsp_dijkstra(graph, numNodes, thread_count);
    display_mat(res_mat, numNodes);
    printf("\n");
    return 0;
}