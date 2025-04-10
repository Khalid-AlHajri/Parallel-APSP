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


int main(int argc, char* argv[]) {
    int nodes = 0;
    FILE* file = fopen("tests/graph.gr", "r");
    adjList* graph = read_adjlist_from_gr(file, &nodes);

    int tcount = 2;
    if (argc == 2) tcount = atoi(argv[1]);
    vector* res = apsp_dijkstra(graph, nodes, tcount);

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            printf("%d, ", res[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}