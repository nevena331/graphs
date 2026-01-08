#include "graphs.h"
#include "set.h"
#include <stdlib.h>

vertex_t* create_vertex(int value){
    vertex_t* new_vertex = malloc(sizeof(vertex_t));
    CHECK_ALLOC(new_vertex);
    new_vertex->value = value;
}

void add_neighbor(vertex_t* vertex, vertex_t* neighbor){
    add_vertex_to_set(&(vertex->neighbors), neighbor);
}