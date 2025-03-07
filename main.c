/*
 *  This is a Final Year Project developed to obtain the shortest paths between every pair of vertices in a 
 *  positive-weight graph in a parallel manner.;
 *  It uses Dijkstra's algorithm on each node on separate run on a different thread.
*/

#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int length;
    int* data;
} vector;


int main(int argc, char* argv[]) {



}