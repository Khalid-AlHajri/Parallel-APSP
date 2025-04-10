#include <stdio.h>
#include <stdlib.h>
#include "adjlist.h"

/**
 * Reads a graph from a .gr file and constructs an adjacency list.
 */
adjList* read_adjlist_from_gr(FILE* file, int* numNodes) {

    int numEdges;
    if (fscanf(file, "p sp %d %d\n", numNodes, &numEdges) != 2) {
        perror("Error: Incorrect file format (missing 'p sp N M').\n");
        fclose(file);
        return NULL;
    }

    adjList* graph = malloc((*numNodes) * sizeof(adjList));
    if (!graph) {
        perror("Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    // Initialize adjacency list
    for (int i = 0; i < *numNodes; i++) {
        graph[i].length = 0;
        graph[i].data = NULL;
    }

    int from, to, weight;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'a') {
            int from, to, weight;
            if (sscanf(line, "a %d %d %d", &from, &to, &weight) == 3) {
                from--; to--;  // Convert to 0-based indexing

                graph[from].data = realloc(graph[from].data, (graph[from].length + 1) * sizeof(bindij_node));
                graph[from].data[graph[from].length] = (bindij_node){weight, to};
                graph[from].length++;
            }
        }
    }

    fclose(file);
    return graph;
}


