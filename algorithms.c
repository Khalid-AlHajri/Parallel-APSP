#include "algorithms.h"
#include <limits.h> // For INT_MAX

sp_vector dijkstra(adjList* graph, int numNodes, int source) {
    sp_vector res;
    res.distances.length = numNodes;
    res.parent.length = numNodes;

    // Allocate memory for distances and parent arrays
    res.distances.data = malloc(sizeof(int) * numNodes);
    res.parent.data = malloc(sizeof(int) * numNodes);

    if (!res.distances.data || !res.parent.data) {
        // Handle memory allocation failure
        free(res.distances.data);
        free(res.parent.data);
        res.distances.data = NULL;
        res.parent.data = NULL;
        return res;
    }

    // Initialize distances to INT_MAX and parents to -1
    for (int i = 0; i < numNodes; i++) {
        res.distances.data[i] = INT_MAX;
        res.parent.data[i] = -1;
    }
    res.distances.data[source] = 0;
    res.parent.data[source] = source;

    // Initialize the binary heap
    BinHeap heap;
    if (!bh_init(&heap, numNodes)) {
        // Handle heap initialization failure
        free(res.distances.data);
        free(res.parent.data);
        res.distances.data = NULL;
        res.parent.data = NULL;
        return res;
    }

    // Insert the source node into the heap
    bindij_node sourceNode = {0, source};
    bh_insert(&heap, sourceNode);
    int visited[numNodes];
    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0; // Initialize visited array
    }
    // Process the heap
    while (heap.length > 0) {
        // Extract the node with the smallest distance
        bindij_node current = bh_pop(&heap);
        int currentNode = current.node;
        int currentDistance = current.prio;
        
        // Skip if a better distance to this node was already found
        if (currentDistance > res.distances.data[currentNode]) {
            continue;
        }

        // Iterate over the neighbors of the current node
        adjList neighbors = graph[currentNode];
        for (int i = 0; i < neighbors.length; i++) {
            bindij_node edge = neighbors.data[i];
            int neighbor = edge.node;
            int weight = edge.prio;

            // Calculate the new distance to the neighbor
            int newDistance = currentDistance + weight;

            // If the new distance is shorter, update it and add the neighbor to the heap
            if (newDistance < res.distances.data[neighbor]) {
                res.distances.data[neighbor] = newDistance;
                res.parent.data[neighbor] = currentNode;
                bindij_node neighborNode = {newDistance, neighbor};
                bh_insert(&heap, neighborNode);
            }
        }
    }

    // Clean up the heap
    bh_delete(&heap);

    return res;
}

void* dijkstra_thread(void* args) {
    // Cast the argument to the correct type
    DijkstraThreadArgs* threadArgs = (DijkstraThreadArgs*)args;

    adjList* graph = threadArgs->graph;
    int numNodes = threadArgs->numNodes;
    int startNode = threadArgs->startNode;
    int numNodesToProcess = threadArgs->numNodesToProcess;
    sp_vector* apsp_matrix = threadArgs->apsp_matrix;

    // Perform Dijkstra's algorithm for each node in the range
    for (int i = startNode; i < startNode + numNodesToProcess; i++) {
        if (i >= numNodes) {
            break; // Ensure we don't go out of bounds
        }
        apsp_matrix[i] = dijkstra(graph, numNodes, i);
    }

    return NULL; // Thread function must return NULL
}

sp_vector* apsp_dijkstra(adjList* graph, int numNodes, int nThreads) {
    // Allocate memory for the distances matrix
    sp_vector* apsp_matrix = malloc(sizeof(sp_vector) * numNodes);
    if (!apsp_matrix) {
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
    threadArgs[0].apsp_matrix = apsp_matrix;

    currentStartNode += threadArgs[0].numNodesToProcess;

    // Create additional threads
    for (int i = 1; i < nThreads; i++) {
        threadArgs[i].graph = graph;
        threadArgs[i].numNodes = numNodes;
        threadArgs[i].startNode = currentStartNode;
        threadArgs[i].numNodesToProcess = nodesPerThread + (i < remainingNodes ? 1 : 0); // Distribute remaining nodes
        threadArgs[i].apsp_matrix = apsp_matrix;

        pthread_create(&threads[i - 1], NULL, dijkstra_thread, &threadArgs[i]);

        currentStartNode += threadArgs[i].numNodesToProcess;
    }

    // Main thread performs its assigned work
    dijkstra_thread(&threadArgs[0]);

    // Wait for additional threads to finish
    for (int i = 0; i < nThreads - 1; i++) {
        pthread_join(threads[i], NULL);
    }

    return apsp_matrix;
}