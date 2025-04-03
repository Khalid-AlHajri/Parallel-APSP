#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bh.h"
#include "algorithms.h"
#include "adjlist.h"

#define GRAPH_FILE "test2.gr"


int main(int argc, char* argv[]) {
    int numNodes = 0;
    adjList* graph = read_adjlist_from_gr(GRAPH_FILE, &numNodes);
    if (!graph) {
        printf("Failed to load graph from %s\n", GRAPH_FILE);
        return 1;
    }

    int source = 0; // Set your desired source node (0-based indexing)
    vector distances = dijkstra(graph, numNodes, source);

    printf("Shortest distances from node %d:\n", source + 1);
    for (int i = 0; i < numNodes; i++) {
        printf("Node %d: %d\n", i + 1, distances.data[i]); // Convert back to 1-based index
    }

    // Free memory
    free(distances.data);
    for (int i = 0; i < numNodes; i++) {
        free(graph[i].data);
    }
    free(graph);

    return 0;
}
