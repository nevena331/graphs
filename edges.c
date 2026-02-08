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

void remove_edge(vertex_t* vertex1, vertex_t* vertex2, edge_t* edge){
    if(edge != NULL){
        remove_element_from_set(&(edge->vertex1->neighbors), edge);
        remove_element_from_set(&(edge->vertex2->neighbors), edge);
        free(edge);
        return;
    }
    
    edge_t* edge_to_delete = NULL;
    for(int i = 0; i < vertex1->neighbors.count; i++){
        edge_t* current_edge = vertex1->neighbors.elements[i];
        if(current_edge->vertex1 == vertex2 || current_edge->vertex2 == vertex2){
            edge_to_delete = current_edge;
            remove_element_from_set(&(vertex1->neighbors), edge_to_delete);
            remove_element_from_set(&(vertex2->neighbors), edge_to_delete);
            free(edge_to_delete);
            return;
        }
    }
}

void print_edge(edge_t* edge){
    printf("v1: %d - v2: %d, direction: %d, weight: %d\n",
           edge->vertex1->value,
           edge->vertex2->value,
           edge->direction,
           edge->weight);
}