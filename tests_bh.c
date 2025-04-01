#include <assert.h>
#include <stdio.h>
#include "bh.h"


void test() {
    BinHeap heap;
    bh_init(&heap, 20);
    bh_insert(&heap, (bindij_node){3, 3});
    bh_insert(&heap, (bindij_node){5, 5});
    bh_insert(&heap, (bindij_node){10, 10});
    int arr[3];
    for (int i = 0; i < 3; i++) {
        arr[i] = bh_pop(&heap).node;
        printf("%d, ", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < 2; i++) {
        assert(arr[i] > arr[i-1]);
    }
    bh_delete(&heap);
}

int main(int argc, char* argv[]) {
    test();
}