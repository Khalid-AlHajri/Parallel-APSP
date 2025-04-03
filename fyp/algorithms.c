#include "algorithms.h"
#include <limits.h> // For INT_MAX

vector dijkstra(adjList* graph, int numNodes, int source) {
    vector distances;
    distances.length = numNodes;
    distances.data = malloc(sizeof(int) * numNodes);
    if (!distances.data) {
    fprintf(stderr, "Error: Memory allocation failed for distances\n");
    exit(EXIT_FAILURE);
    }


    for (int i = 0; i < numNodes; i++) {
        distances.data[i] = INT_MAX;
    }
    distances.data[source] = 0;

    BinHeap heap;
    bh_init(&heap, numNodes);

    bindij_node sourceNode = {0, source};
    bh_insert(&heap, sourceNode);

    while (heap.length > 0) {
        bindij_node current = bh_pop(&heap);
        int currentNode = current.node;
        int currentDistance = current.prio;

        if (currentDistance > distances.data[currentNode]) {
            continue;
        }

        adjList neighbors = graph[currentNode];
        for (int i = 0; i < neighbors.length; i++) {
            bindij_node edge = neighbors.data[i];
            int neighbor = edge.node;
            int weight = edge.prio;

            int newDistance = currentDistance + weight;

            if (newDistance < distances.data[neighbor]) {
                distances.data[neighbor] = newDistance;
                bindij_node neighborNode = {newDistance, neighbor};
                bh_insert(&heap, neighborNode);
            }
        }
    }

    bh_delete(&heap);

    return distances;
}
