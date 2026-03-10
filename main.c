#include <stdio.h>
#include <stdlib.h>

#include "euler.h"
#include "graphs.h"
#include "mst.h"
#include "pathfinding.h"

int get_vertex_count(FILE* file){
    char vertex_count_str[64];
    if(!fgets(vertex_count_str, sizeof(vertex_count_str), file)){
        fprintf(stderr, "Failed to read vertex count\n");
        exit(1);
    }
    int v = atoi(vertex_count_str);
    printf("Vertex count string: %s", vertex_count_str);
    printf("Converted vertex count: %d\n", v);
    return v;
}   

int is_check(FILE* file){
    char is_check_str[64];
    if(!fgets(is_check_str, sizeof(is_check_str), file)){
        fprintf(stderr, "Failed to read is_check flag\n");
        exit(1);
    }
    int is_check = atoi(is_check_str);
    printf("Is check string: %s", is_check_str);
    printf("Converted is_check: %d\n", is_check);
    return is_check;
}

int** read_adjacency_matrix(FILE* file, int vertex_count){
    int** adj_matrix = malloc(sizeof(int*) * vertex_count);
    CHECK_ALLOC(adj_matrix);
    char* line = malloc(sizeof(char) * (vertex_count + 2));
    CHECK_ALLOC(line);
    for(int i = 0; i < vertex_count; i++){
        adj_matrix[i] = malloc(sizeof(int) * vertex_count);
        CHECK_ALLOC(adj_matrix[i]);
        if(!fgets(line, vertex_count + 2, file)){
            break;
        }
        for(int j = 0; j < vertex_count; j++){
            adj_matrix[i][j] = line[j] - '0';
        }
    }
    free(line);
    return adj_matrix;
}

void print_adj_matrix(int** matrix, int vertex_count){
    for(int i = 0; i < vertex_count; i++){
        for(int j = 0; j < vertex_count; j++){
            printf("%d, ", matrix[i][j]);
        }
        printf("\n");
    }
}

graph_t* read_file(char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Not able to open the file.\n");
        return NULL;
    }

    int vertex_count = get_vertex_count(file);
    int is_directed_flag = is_check(file);
    int is_weighted_flag = is_check(file);
    int** adj_matrix = read_adjacency_matrix(file, vertex_count);
    printf("vertex count: %d\n", vertex_count);
    print_adj_matrix(adj_matrix, vertex_count);
    
    fclose(file);
    
    graph_t* graph = create_graph(adj_matrix, vertex_count, is_directed_flag, is_weighted_flag);
    return graph;
}


void graph_tests(char* filename){
    graph_t* graph = read_file(filename);
    printf("\nOriginal graph:\n");
    print_graph(graph);

    printf("is eulerian: %d\n", is_eulerian(graph));
    printf("is cyclical: %d\n", is_cyclical(graph));

    graph_t* topologically_sorted_graph = topological_sort(graph);
    printf("\nTopologically sorted graph:\n");
    print_graph(topologically_sorted_graph);

    printf("\nIs reachable test: %d\n", is_reachable(graph, get_vertex(graph, 4), get_vertex(graph, 9)));

    graph = free_graph(graph);
    topologically_sorted_graph = free_graph(topologically_sorted_graph);
    return;
}

void minimal_spanning_tree_test(){
    graph_t* graph = create_random_filled_graph();
    printf("\nOriginal graph:\n");
    print_graph(graph);
    graph_t* mst = build_mst(graph);
    printf("\nMST:\n");
    print_graph(mst);
    graph = free_graph(graph);
    mst = free_graph(mst);  
}

void pathfinding_tests(char* filename){
    graph_t* graph = read_file(filename);
    printf("\nOriginal graph:\n");
    print_graph(graph);

    vertex_t* start = get_vertex(graph, 5);
    printf("Start vertex: %d\n", start->value);
    vertex_t* end = get_vertex(graph, 2);
    printf("End vertex: %d\n", end->value);
    route_t* dfs_route_result = dfs_route(graph, start, end);

    print_route(dfs_route_result);

    graph = free_graph(graph);
    dfs_route_result = free_route(dfs_route_result);
}

int main(){
    // graph_tests("../graphs_adj_matrix/wd_graph.txt");
    // minimal_spanning_tree_test();
    pathfinding_tests("../graphs_adj_matrix/graph.txt");
    return 0;
}