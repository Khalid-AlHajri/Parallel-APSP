#include <assert.h>
#include <stdio.h>
#include "bh.h"
#include "algorithms.h"

void test_read_gr(int argc, char* argv[]) {
    int numNodes = 0;
    adjList* graph = read_adjlist_from_gr(GRAPH_FILE, &numNodes);
    assert(graph != NULL);
    // Check graph is correct somehow

    // Free memory
    free(distances.data);
    for (int i = 0; i < numNodes; i++) {
        free(graph[i].data);
    }
    free(graph);

    return 0;
}

void test_binaryheap() {
    BinHeap heap;
    bh_init(&heap, 20);
    bh_insert(&heap, (bindij_node){5, 5});
    bh_insert(&heap, (bindij_node){3, 3});
    bh_insert(&heap, (bindij_node){10, 10});
    bh_insert(&heap, (bindij_node){10, 10});
    bh_insert(&heap, (bindij_node){5, 5});
    bh_insert(&heap, (bindij_node){9, 9});
    int arr[3];
    for (int i = 0; i < 3; i++) {
        arr[i] = bh_pop(&heap).node;
    }
    for (int i = 1; i < 3; i++) {
        assert(arr[i] >= arr[i-1]);
    }
    bh_delete(&heap);
}

void test_dijkstra() {
    adjList graph[3];
    graph[0].length = 2;
    graph[0].data = malloc(sizeof(bindij_node) * 2);
    graph[0].data[0] = (bindij_node){1, 1};
    graph[0].data[1] = (bindij_node){4, 2};

    graph[1].length = 2;
    graph[1].data = malloc(sizeof(bindij_node) * 2);
    graph[1].data[0] = (bindij_node){2, 0};
    graph[1].data[1] = (bindij_node){2, 2};

    graph[2].length = 2;
    graph[2].data = malloc(sizeof(bindij_node) * 2);
    graph[2].data[0] = (bindij_node){4, 0};
    graph[2].data[1] = (bindij_node){5, 1};

    vector result = dijkstra(graph, 3, 0);
    vector expected;
    expected.length = 3;
    expected.data = malloc(sizeof(int) * 3);
    expected.data[0] = 0;
    expected.data[1] = 1;
    expected.data[2] = 3;
    for (int i = 0; i < expected.length; i++) {
        assert(result.data[i] == expected.data[i]);
    }

    free(expected.data);
    free(graph[0].data);
    free(graph[1].data);
    free(graph[2].data);
    free(result.data);
}

int main(int argc, char* argv[]) {
    test_binaryheap();
    test_dijkstra();
    test_read_gr();
    return 0;
}
