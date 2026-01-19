#include <stdio.h>
#include <stdlib.h>

#include "euler.h"
#include "graphs.h"

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

int main (){
    FILE* file = fopen("../undirected_graph2.txt", "r");
    if(file == NULL) {
        printf("Not able to open the file.");
    }

    int vertex_count = get_vertex_count(file);
    int** adj_matrix = read_adjacency_matrix(file, vertex_count);
    printf("vertex count: %d\n", vertex_count);
    print_adj_matrix(adj_matrix, vertex_count);
    
    fclose(file);
    
    // int adj_matrix[5][5] = {
    //     {0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1},
    //     {0, 1, 0, 1, 0},
    //     {1, 0, 1, 0, 1},
    //     {0, 1, 0, 1, 0}
    // };

    set_t* graph = create_graph(adj_matrix, vertex_count);
    print_graph(graph);

    printf("is euleran: %d\n", is_eulerian_undirected(graph));

    return 0;
}