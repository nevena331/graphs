#pragma once
#include "graphs.h"

typedef struct{
    vertex_t* vertex1;
    vertex_t* vertex2;
    int direction;//0 for both, 1 for towards vertex1, 2 for towards vertex2
    int weight;
}edge_t;

edge_t* add_edge(vertex_t* vertex1, vertex_t* vertex2, int direction, int weight);