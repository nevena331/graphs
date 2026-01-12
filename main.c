#include <stdio.h>
#include <stdlib.h>

#include "graphs.h"


int main (){
    int adj_matrix[VERTEX_COUNT][VERTEX_COUNT] = {
        {0, 1, 0, 1, 0, 1}, 
        {1, 0, 1, 0, 0, 0}, 
        {0, 1, 0, 0, 0, 1}, 
        {1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 1}, 
        {1, 0, 1, 1, 1, 0}
    };

    set_t* graph = create_graph(adj_matrix);
    print_graph(graph);
}