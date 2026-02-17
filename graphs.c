#include <stdlib.h>
#include "graphs.h"
#include "edges.h"
#include "queue.h"

vertex_t* create_vertex(int value){
    vertex_t* new_vertex = malloc(sizeof(vertex_t));
    CHECK_ALLOC(new_vertex);
    new_vertex->value = value;
    new_vertex->neighbors.count = 0;
    new_vertex->neighbors.elements = NULL;
    return new_vertex;
}

vertex_t* get_vertex(graph_t* graph, int value){
    vertex_t* vertex = NULL;
    for(int i = 0; i < graph->vertices.count; i++){
        if(((vertex_t*)graph->vertices.elements[i])->value == value){
            vertex = graph->vertices.elements[i];
            break;
        }
    }
    return vertex;
}

graph_t* create_empty_graph(int is_directed){
    graph_t* graph = malloc(sizeof(graph_t));
    CHECK_ALLOC(graph);
    graph->vertices.elements = NULL;
    graph->vertices.count = 0;
    graph->is_directed = is_directed;
    return graph;
}

graph_t* create_graph(int**matrix, int vertex_count, int is_directed){
    graph_t* graph = malloc(sizeof(graph_t));
    CHECK_ALLOC(graph);
    graph->vertices.elements = NULL;
    graph->vertices.count = 0;
    graph->is_directed = is_directed;
    
    for(int i = 0; i < vertex_count; i++){
        vertex_t* new_vertex = create_vertex(i);
        add_element_to_set(&graph->vertices, new_vertex);
        for(int j = 0; j < i; j++){
            vertex_t* neighbor = get_vertex(graph, j);
            if(matrix[i][j]){
                if(matrix[j][i]){
                    if(graph->is_directed){
                        add_edge(new_vertex, neighbor, 2, 1);
                        add_edge(new_vertex, neighbor, 1, 1);
                    }else{        
                        add_edge(new_vertex, neighbor, 0, 1);
                    }
                }else{
                    add_edge(new_vertex, neighbor, 2, 1);
                }
            }else{
                if(matrix[j][i]){
                    add_edge(new_vertex, neighbor, 1, 1);
                }
            }
        }
        if(matrix[i][i]){
            add_edge(new_vertex, new_vertex, 0, 1);
        }
    }
    return graph;
}


int get_vertex_index(graph_t* graph, vertex_t* vertex_to_find){
    if(graph == NULL || vertex_to_find == NULL){
        return -1;
    }
    int index = -1;
    for(int i = 0; i < graph->vertices.count; i++){
        if(graph->vertices.elements[i] == vertex_to_find){
            index = i;
            break;
        }
    }
    return index;
}

int get_neighbor_index(graph_t* graph, vertex_t* curr_vertex, void* edge){
    edge_t* edge_ptr = (edge_t*) edge;
    if(edge_ptr->vertex1 == curr_vertex && (edge_ptr->direction == 0 || edge_ptr->direction == 2)){
        return get_vertex_index(graph, edge_ptr->vertex2);
    }else if(edge_ptr->vertex2 == curr_vertex && (edge_ptr->direction == 0 || edge_ptr->direction == 1)){
        return get_vertex_index(graph, edge_ptr->vertex1);
    }else{
        return -1;
    }
}

int is_cyclical_internal(graph_t* graph, int vertex_index, int* visited, int* curr_dfs_visited){
    visited[vertex_index] = 1;
    curr_dfs_visited[vertex_index] = 1;
    vertex_t* vertex = graph->vertices.elements[vertex_index];
    for(int i = 0; i < vertex->neighbors.count; i++){
        int neighbor_index = get_neighbor_index(graph, vertex, vertex->neighbors.elements[i]);
        if(neighbor_index == -1){
            continue;
        }
        if(!visited[neighbor_index]){
            if(is_cyclical_internal(graph, neighbor_index, visited, curr_dfs_visited)){
                return 1;
            }
        }else if(curr_dfs_visited[neighbor_index]){
            return 1;
        }
    }
    curr_dfs_visited[vertex_index] = 0;
    return 0;
}


int is_cyclical(graph_t* graph){
    if(graph == NULL){
        return -1;
    }
    if(graph->vertices.count == 0){
        return 0;
    }
    int* visited = calloc(graph->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    int* curr_dfs_visited = calloc(graph->vertices.count, sizeof(int));
    CHECK_ALLOC(curr_dfs_visited);
    for(int i = 0; i < graph->vertices.count; i++){
        if(!visited[i]){
            if(is_cyclical_internal(graph, i, visited, curr_dfs_visited)){
                free(visited);
                free(curr_dfs_visited);
                return 1;
            }
        }
    }
    free(visited);
    free(curr_dfs_visited);
    return 0;
}

static int get_in_degree(graph_t* graph, vertex_t* vertex){
    int in_degree = 0;
    for(int i = 0; i < vertex->neighbors.count; i++){
        edge_t* edge = vertex->neighbors.elements[i];
        if(edge->vertex1 == vertex && (edge->direction == 0 || edge->direction == 1)){
            in_degree++;
        }else if(edge->vertex2 == vertex && (edge->direction == 0 || edge->direction == 2)){
            in_degree++;
        }
    }
    return in_degree;
}

graph_t* topological_sort(graph_t* graph){
    if(graph == NULL || is_cyclical(graph)){
        return NULL;
    }

    graph_t* new_graph = create_empty_graph(1);
    queue_t* queue = queue_create();

    int* in_degrees = calloc(graph->vertices.count, sizeof(int));
    for(int i = 0; i < graph->vertices.count; i++){
        vertex_t* vertex = graph->vertices.elements[i];
        in_degrees[i] = get_in_degree(graph, vertex);
        if(in_degrees[i] == 0){
            queue_enqueue(queue, vertex);
        }
    }
    while(!queue_is_empty(queue)){
        vertex_t* vertex = queue_dequeue(queue);
        vertex_t* new_vertex = create_vertex(vertex->value);
        add_element_to_set(&new_graph->vertices, new_vertex);
        for(int j = 0; j < vertex->neighbors.count; j++){
            int neigbor_index = get_neighbor_index(graph, vertex, vertex->neighbors.elements[j]);
            if(neigbor_index == -1){
                continue;
            }
            in_degrees[neigbor_index]--;
            if(in_degrees[neigbor_index] == 0){
                queue_enqueue(queue, graph->vertices.elements[neigbor_index]);
            }
        }
    }
    for(int i = 0; i < graph->vertices.count; i++){
        vertex_t* vertex = graph->vertices.elements[i];
        for(int j = 0; j < vertex->neighbors.count; j++){
            int neighbor_index = get_neighbor_index(graph, vertex, vertex->neighbors.elements[j]);
            if(neighbor_index == -1){
                continue;
            }
            vertex_t* new_graph_vertex = get_vertex(new_graph, vertex->value);
            vertex_t* new_graph_neighbor = get_vertex(new_graph, ((vertex_t*)(graph->vertices.elements[neighbor_index]))->value);
            add_edge(new_graph_vertex, new_graph_neighbor, 2, 1);
        }
    }
    free(in_degrees);
    return new_graph;
}


void print_graph(graph_t* graph){
    if(graph == NULL){
        return;
    }
    for(int i = 0; i < graph->vertices.count; i++){
        vertex_t* vertex = graph->vertices.elements[i];
        printf("Vertex %d:\n", vertex->value);
        for(int j = 0; j < vertex->neighbors.count; j++){
            print_edge(vertex->neighbors.elements[j]);
        }
        printf("\n");
    }
}

static void free_vertex(vertex_t* vertex){
    if(vertex->neighbors.elements != NULL){
        for(int i = 0; i < vertex->neighbors.count; i++){
            remove_edge(NULL, NULL, vertex->neighbors.elements[i]);
            i--;
        }
    }
    free(vertex->neighbors.elements);
    free(vertex);
}

graph_t* free_graph(graph_t* graph){
    if(graph == NULL){
        return NULL;
    }
    for(int i = 0; i < graph->vertices.count; i++){
        free_vertex(graph->vertices.elements[i]);
        graph->vertices.elements[i] = NULL;
    }
    free(graph->vertices.elements);
    free(graph);
    graph = NULL;
    return graph;
}