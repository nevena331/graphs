#include "euler.h"
#include <assert.h>

static vertex_t* get_neighbor(vertex_t* vertex, int edge_index){
    edge_t* edge = (edge_t*)vertex->neighbors.elements[edge_index];
    if(edge->vertex1 == vertex){
        return edge->vertex2;
    }else{
        return edge->vertex1;
    }
    return NULL;
}

static void connected_component_only_internal(set_t* graph, vertex_t* first_vertex, int* visited){
    int index = get_vertex_index(graph, first_vertex);
    assert(index != -1);
    if(visited[index] == 1){
        return;
    }
    visited[index] = 1;
    for(int i = 0; i < first_vertex->neighbors.count; i++){
        vertex_t* neighbor = get_neighbor(first_vertex, i);
        if(neighbor != NULL){
            connected_component_only_internal(graph, neighbor, visited);
        }
    }
}

static int connected_component_and_singles_only(set_t* graph){
    int* visited = calloc(graph->count, sizeof(int));
    CHECK_ALLOC(visited);
    if(graph->count == 0){
        return 1;
    }
    connected_component_only_internal(graph, (vertex_t*)graph->elements[0], visited);
    
    for(int i = 0; i < graph->count; i++){
        if(visited[i] == 0 && ((vertex_t*)graph->elements[i])->neighbors.count > 0){
            free(visited);
            return 0;
        }
    }
    free(visited);
    return 1;
}

int is_eulerian_undirected(set_t* graph){
    if(!connected_component_and_singles_only(graph)){
        return 0;
    }
    int odd_degree_vertex_count = 0;
    for (int i = 0; i < graph->count; i++){
        if(((vertex_t*)graph->elements[i])->neighbors.count % 2 != 0){
            odd_degree_vertex_count++;
        }
    }
    if(odd_degree_vertex_count == 2){
        return 1;
    }
    if(odd_degree_vertex_count == 0){
        return 2;
    }
    return 0;
}