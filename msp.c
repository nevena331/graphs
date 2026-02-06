#include "msp.h"

#include "edges.h"

#include "stdlib.h"
#include "time.h"

static void create_random_neighbor_edges(graph_t* graph, vertex_t* vertex){
    srand(time(NULL));
    for(int i = 0; i < graph->vertices.count;){
        int weight = rand() % 10;
        add_edge(vertex, &(graph->vertices.elements[i]), 0, weight);
        int num_to_add = rand() % 3 + 1;
        i+= num_to_add;
    }
}

graph_t* create_random_filled_graph(){
    srand(time(NULL));
    graph_t* new_graph = (graph_t*)calloc(1, sizeof(graph_t));
    new_graph->is_directed = 0;
    for(int i = 0; i < 10; i++){
        vertex_t* new_vertex = (vertex_t*)calloc(1, sizeof(vertex_t));
        new_vertex->value = rand() % 10;
        if(get_vertex(new_graph, new_vertex->value) == NULL){
            add_element_to_set(&(new_graph->vertices), new_vertex);
            create_random_neighbor_edges(new_graph, new_vertex);
        }
    }
}
