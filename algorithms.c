#include "algorithms.h"
#include <limits.h> // For INT_MAX

vector dijkstra(adjList* graph, int numNodes, int source) {
    vector distances;
    distances.length = numNodes;
    distances.data = malloc(sizeof(int) * numNodes);

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

void* dijkstra_thread(void* args) {
    // Cast the argument to the correct type
    DijkstraThreadArgs* threadArgs = (DijkstraThreadArgs*)args;

    adjList* graph = threadArgs->graph;
    int numNodes = threadArgs->numNodes;
    int startNode = threadArgs->startNode;
    int numNodesToProcess = threadArgs->numNodesToProcess;
    vector* distancesArray = threadArgs->distancesArray;

    // Perform Dijkstra's algorithm for each node in the range
    for (int i = startNode; i < startNode + numNodesToProcess; i++) {
        if (i >= numNodes) {
            break; // Ensure we don't go out of bounds
        }
        distancesArray[i] = dijkstra(graph, numNodes, i);
    }

    return NULL; // Thread function must return NULL
}

vector* apsp_dijkstra(adjList* graph, int numNodes, int nThreads) {
    // Allocate memory for the distances matrix
    vector* distancesArray = malloc(sizeof(vector) * numNodes);
    if (!distancesArray) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Initialize thread-related variables
    pthread_t threads[nThreads - 1]; // Only create nThreads - 1 additional threads
    DijkstraThreadArgs threadArgs[nThreads];

    // Calculate the number of nodes each thread will process
    int nodesPerThread = numNodes / nThreads;
    int remainingNodes = numNodes % nThreads; // Handle uneven division

    int currentStartNode = 0;

    // Assign work to the main thread
    threadArgs[0].graph = graph;
    threadArgs[0].numNodes = numNodes;
    threadArgs[0].startNode = currentStartNode;
    threadArgs[0].numNodesToProcess = nodesPerThread + (remainingNodes > 0 ? 1 : 0); // Distribute remaining nodes
    threadArgs[0].distancesArray = distancesArray;

    currentStartNode += threadArgs[0].numNodesToProcess;

    // Create additional threads
    for (int i = 1; i < nThreads; i++) {
        threadArgs[i].graph = graph;
        threadArgs[i].numNodes = numNodes;
        threadArgs[i].startNode = currentStartNode;
        threadArgs[i].numNodesToProcess = nodesPerThread + (i < remainingNodes ? 1 : 0); // Distribute remaining nodes
        threadArgs[i].distancesArray = distancesArray;

        pthread_create(&threads[i - 1], NULL, dijkstra_thread, &threadArgs[i]);

        currentStartNode += threadArgs[i].numNodesToProcess;
    }

    // Main thread performs its assigned work
    dijkstra_thread(&threadArgs[0]);

    // Wait for additional threads to finish
    for (int i = 0; i < nThreads - 1; i++) {
        pthread_join(threads[i], NULL);
    }

    return distancesArray;
}