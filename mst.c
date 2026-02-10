#include "mst.h"

#include "edges.h"
#include "euler.h"

#include "stdlib.h"
#include "time.h"

static void create_random_neighbor_edges(graph_t* graph, vertex_t* vertex){
    for(int i = rand() % 3; i < graph->vertices.count;){
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
    int connected_component_only = 1;
    for(int i = 0; i < new_graph->vertices.count; i++){
        if(visited[i] == 0){
            connected_component_only = 0;
            break;
        }
    }
    if(connected_component_only){
        return new_graph;
    }else{
        return create_random_filled_graph();
    }
}

static int get_neighbor_index(graph_t* graph, vertex_t* curr_vertex, edge_t* edge){
    if(edge->vertex1 == curr_vertex){
        return get_vertex_index(graph, edge->vertex2);
    }else if(edge->vertex2 == curr_vertex){
        return get_vertex_index(graph, edge->vertex1);
    }else{
        return -1;
    }
}

static edge_t* find_min_weight_edge(graph_t* graph, int* visited){
    edge_t* min_weight_edge = NULL;
    for(int i = 0; i < graph->vertices.count; i++){
        if(visited[i] == 0){
            continue;
        }
        vertex_t* curr_graph_vertex = graph->vertices.elements[i];
        for(int j = 0; j < curr_graph_vertex->neighbors.count; j++){
            edge_t* curr_edge = curr_graph_vertex->neighbors.elements[j];
            if(!visited[get_neighbor_index(graph, curr_graph_vertex, curr_edge)]){
                if(min_weight_edge == NULL){
                    min_weight_edge = curr_edge;
                    continue;
                }
                if(curr_edge->weight < min_weight_edge->weight){
                    min_weight_edge = curr_edge;
                }
            }
        }
    }
    return min_weight_edge;
}

graph_t* build_mst(graph_t* graph){
    graph_t* mst = create_empty_graph(0);
    if(graph == NULL || graph->vertices.count == 0){
        return mst;
    }
    for(int i = 0; i < graph->vertices.count; i++){
        vertex_t* new_vertex = create_vertex(((vertex_t*)graph->vertices.elements[i])->value);
        add_element_to_set(&mst->vertices, new_vertex);
    }
    int* visited = calloc(mst->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    visited[0] = 1;
    int edges_added = 0;
    while(tree_like_connected_component_only(mst, mst->vertices.elements[0]) == 0 && edges_added < graph->vertices.count - 1){
        edge_t* graph_min_weight_edge = find_min_weight_edge(graph, visited);
        vertex_t* vertex1 = get_vertex(mst, graph_min_weight_edge->vertex1->value);
        vertex_t* vertex2 = get_vertex(mst, graph_min_weight_edge->vertex2->value);
        add_edge(vertex1, vertex2, 0, graph_min_weight_edge->weight);
        visited[get_vertex_index(mst, vertex1)] = 1;
        visited[get_vertex_index(mst, vertex2)] = 1;
        edges_added++;
    }
    free(visited);
    return mst;
}