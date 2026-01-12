#include "edges.h"

static edge_t* create_edge(vertex_t* vertex1, vertex_t* vertex2, int direction, int weight){
    edge_t* new_edge = malloc(sizeof(edge_t));
    CHECK_ALLOC(new_edge);
    new_edge->vertex1 = vertex1;
    new_edge->vertex2 = vertex2;
    new_edge->direction = direction;
    new_edge->weight = weight;
    return new_edge;
}

edge_t* add_edge(vertex_t* vertex1, vertex_t* vertex2, int direction, int weight){
    edge_t* new_edge = create_edge(vertex1, vertex2, direction, weight);
    add_element_to_set(&((new_edge->vertex1)->neighbors), new_edge);
    add_element_to_set(&((new_edge->vertex2)->neighbors), new_edge);
    return new_edge;
}

void print_edge(edge_t* edge){
    printf("v1: %d -> v2 %d, direction: %d, weight: %d\n",
           edge->vertex1->value,
           edge->vertex2->value,
           edge->direction,
           edge->weight);
}