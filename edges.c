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

edge_t* get_edge(vertex_t* vertex1, vertex_t* vertex2){
    for(int i = 0; i < vertex1->neighbors.count; i++){
        edge_t* curr_edge = vertex1->neighbors.elements[i];
        if(curr_edge->vertex1 == vertex2 || curr_edge->vertex2 == vertex2){
            return curr_edge;
        }
    }
    return NULL;
}

void remove_edge(vertex_t* vertex1, vertex_t* vertex2){
    edge_t* edge_to_remove = get_edge(vertex1, vertex2);
    if(edge_to_remove != NULL){
        remove_element_from_set(&(edge_to_remove->vertex1->neighbors), edge_to_remove);
        remove_element_from_set(&(edge_to_remove->vertex2->neighbors), edge_to_remove);
        free(edge_to_remove);
    }
}


void print_edge(edge_t* edge){
    printf("v1: %d - v2: %d, direction: %d, weight: %d\n",
           edge->vertex1->value,
           edge->vertex2->value,
           edge->direction,
           edge->weight);
}