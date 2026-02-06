#include "mst.h"

#include "edges.h"
#include "euler.h"

#include "stdlib.h"
#include "time.h"

static void create_random_neighbor_edges(graph_t* graph, vertex_t* vertex){
    for(int i = 0; i < graph->vertices.count;){
        if(vertex != graph->vertices.elements[i]){
            int weight = vertex->value + (((vertex_t*)(graph->vertices.elements[i]))->value) - 10;
            if(weight < 0){
                weight = 0 - weight;
            }else if(weight == 0){
                weight = 3;
            }
            add_edge(vertex, graph->vertices.elements[i], 0, weight);
        }
        int num_to_add = rand() % 3 + 1;
        i+= num_to_add;
    }
}
/*the function below creates an undireced graph with 
1 to 10 nodes, all connected with random edges between
them with random weights
without loops
*/
graph_t* create_random_filled_graph(){
    srand(time(NULL));
    graph_t* new_graph = (graph_t*)calloc(1, sizeof(graph_t));
    CHECK_ALLOC(new_graph);
    new_graph->is_directed = 0;
    for(int i = 0; i < 20; i++){
        vertex_t* new_vertex = (vertex_t*)calloc(1, sizeof(vertex_t));
        CHECK_ALLOC(new_vertex);
        new_vertex->value = rand() % 10;
        if(get_vertex(new_graph, new_vertex->value) == NULL){
            add_element_to_set(&(new_graph->vertices), new_vertex);
            create_random_neighbor_edges(new_graph, new_vertex);
        }
    }
    int* visited = calloc(new_graph->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    connected_component_only_internal(new_graph, new_graph->vertices.elements[0], visited);
    return new_graph;
}

