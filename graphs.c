#include <stdlib.h>
#include "graphs.h"
#include "edges.h"

static vertex_t* get_vertex(set_t* graph, int value){
    vertex_t* vertex = NULL;
    for(int i = 0; i < graph->count; i++){
        if(((vertex_t*)graph->elements[i])->value == value){
            vertex = graph->elements[i];
            break;
        }
    }
    return vertex;
}


vertex_t* create_vertex(int value){
    vertex_t* new_vertex = malloc(sizeof(vertex_t));
    CHECK_ALLOC(new_vertex);
    new_vertex->value = value;
    new_vertex->neighbors.count = 0;
    new_vertex->neighbors.elements = NULL;
    return new_vertex;
}

set_t* create_graph(int matrix[VERTEX_COUNT][VERTEX_COUNT]){
    set_t* graph = create_empty_set();
    for(int i = 0; i < VERTEX_COUNT; i++){
        vertex_t* new_vertex = create_vertex(i);
        add_element_to_set(graph, new_vertex);
        for(int j = 0; j < i + 1; j++){
            vertex_t* neighbor = get_vertex(graph, j);
            if(matrix[i][j]){
                if(matrix[j][i]){
                    add_edge(new_vertex, neighbor, 0, 1);
                }else{
                    add_edge(new_vertex, neighbor, 2, 1);
                }
            }
            if(matrix[j][i]){
                add_edge(new_vertex, neighbor, 1, 1);
            }
        }
    }
    return graph;
}