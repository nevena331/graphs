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

void connected_component_only_internal(graph_t* graph, vertex_t* first_vertex, int* visited){
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

static int connected_component_and_singles_only(graph_t* graph){
    int* visited = calloc(graph->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    if(graph->vertices.count == 0){
        return 1;
    }
    connected_component_only_internal(graph, (vertex_t*)graph->vertices.elements[0], visited);

    for(int i = 0; i < graph->vertices.count; i++){
        if(visited[i] == 0 && ((vertex_t*)graph->vertices.elements[i])->neighbors.count > 0){
            free(visited);
            return 0;
        }
    }
    free(visited);
    return 1;
}

static int is_eulerian_undirected(graph_t* graph){
    if(!connected_component_and_singles_only(graph)){
        return 0;
    }
    int odd_degree_vertex_count = 0;
    for (int i = 0; i < graph->vertices.count; i++){
        if(((vertex_t*)graph->vertices.elements[i])->neighbors.count % 2 != 0){
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

static int strongly_connected_components_and_singles_only(graph_t* graph){
    int* visited = calloc(graph->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    if(graph->vertices.count == 0){
        return 1;
    }
    for(int i = 0; i < graph->vertices.count; i++){
        connected_component_only_internal(graph, (vertex_t*)graph->vertices.elements[i], visited);
        for(int j = 0; j < graph->vertices.count; j++){
            if(visited[j] == 0 && ((vertex_t*)graph->vertices.elements[j])->neighbors.count > 0){
                free(visited);
                return 0;
            }
        }
        for(int j = 0; j < graph->vertices.count; j++){
            visited[j] = 0;
        }
    }
    free(visited);
    return 1;
}

static int check_edge_direction(vertex_t* vertex, edge_t* edge){
    switch(edge->direction){
        case 1:
            if(edge->vertex2 == vertex){
                return 1;
            }else{
                return 0;
            }
            break;
        case 2:
            if(edge->vertex1 == vertex){
                return 1;
            }else{
                return 0;
            }
            break;
        default:
            return -1;
    }
}

static int is_eulerian_cycle_directed(graph_t* graph){
    if(!connected_component_and_singles_only(graph)){
        return 0;
    }
    int is_eulerian_cycle = 1;
    for(int i = 0; i < graph->vertices.count;i++){
        int in_edges = 0;
        int out_edges = 0;
        vertex_t* current_vertex = (vertex_t*)graph->vertices.elements[i];
        for(int j = 0; j < current_vertex->neighbors.count; j++){
            int direction = check_edge_direction(graph->vertices.elements[i], current_vertex->neighbors.elements[j]);
            if(direction == 0){
                out_edges++;
            }else if(direction == 1){
                in_edges++;
            }
        }
        if(in_edges != out_edges){
            is_eulerian_cycle = 0;
            break;
        }
    }
    return is_eulerian_cycle;
}

static int is_eulerian_directed(graph_t* graph){
    if(is_eulerian_cycle_directed(graph)){
        return 2;
    }
    vertex_t* beginning_vertex = NULL;
    vertex_t* end_vertex = NULL;
    for(int i = 0; i < graph->vertices.count; i++){
        vertex_t* current_vertex = graph->vertices.elements[i];
        int in_edges = 0; 
        int out_edges = 0;
        for(int j = 0; j < current_vertex->neighbors.count; j++){
            int direction = check_edge_direction(current_vertex, current_vertex->neighbors.elements[j]);
            if(direction == 0){
                out_edges++;
            }else if(direction == 1){
                in_edges++;
            }
        } 
        if(in_edges == 1 + out_edges){
            if(end_vertex == NULL){
                end_vertex = current_vertex;
            }else{
                return 0;
            }
        }else if(out_edges == 1 + in_edges){
            if(beginning_vertex == NULL){
                beginning_vertex = current_vertex;
            }else{
                return 0;
            }
        }else if(in_edges != out_edges){
            return 0;
        }
    }
    if(beginning_vertex == NULL || end_vertex == NULL){
        return 0;
    }

    add_edge(end_vertex, beginning_vertex, 2, 0);
    if(is_eulerian_cycle_directed(graph)){
        remove_edge(beginning_vertex, end_vertex);
        return 1;
    }
    remove_edge(beginning_vertex, end_vertex);
    return 0;
}

int is_eulerian(graph_t* graph){
    if(graph->is_directed){
        return is_eulerian_directed(graph);
    }else{
        return is_eulerian_undirected(graph);
    }
}