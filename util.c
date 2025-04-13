#include "util.h"

void display_mat(sp_vector* mat, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            printf("%d ", mat[i].distances.data[j]);
        }
    }
}

void display_path(sp_vector* apsp_mat, int source, int dest) {
    vector sourcevec = apsp_mat[source].parent;
    int current = dest;
    printf("Path from %d to %d: ", source, dest);
    while (current != source) {
        printf("%d <- ", current);
        current = sourcevec.data[current];
    }
    printf("%d\n", source);
}