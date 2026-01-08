#include <stdlib.h>
#include "graphs.h"

vertex_t* create_vertex(int value){
    vertex_t* new_vertex = malloc(sizeof(vertex_t));
    CHECK_ALLOC(new_vertex);
    new_vertex->value = value;
    new_vertex->neighbors.count = 0;
    new_vertex->neighbors.elements = NULL;
    return new_vertex;
}