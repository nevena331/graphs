#include <stdio.h>
#include <stdlib.h>

#include "euler.h"
#include "graphs.h"
#include "mst.h"

//this below is for graphs and euler implementation
// int get_vertex_count(FILE* file){
//     char vertex_count_str[64];
//     if(!fgets(vertex_count_str, sizeof(vertex_count_str), file)){
//         fprintf(stderr, "Failed to read vertex count\n");
//         exit(1);
//     }
//     int v = atoi(vertex_count_str);
//     printf("Vertex count string: %s", vertex_count_str);
//     printf("Converted vertex count: %d\n", v);
//     return v;
// }   

// int is_directed(FILE* file, int vertex_count){
//     char is_directed_str[64];
//     if(!fgets(is_directed_str, sizeof(is_directed_str), file)){
//         fprintf(stderr, "Failed to read is_directed flag\n");
//         exit(1);
//     }
//     int is_directed = atoi(is_directed_str);
//     printf("Is directed string: %s", is_directed_str);
//     printf("Converted is_directed: %d\n", is_directed);
//     return is_directed;
// }

// int** read_adjacency_matrix(FILE* file, int vertex_count){
//     int** adj_matrix = malloc(sizeof(int*) * vertex_count);
//     CHECK_ALLOC(adj_matrix);
//     char* line = malloc(sizeof(char) * (vertex_count + 2));
//     CHECK_ALLOC(line);
//     for(int i = 0; i < vertex_count; i++){
//         adj_matrix[i] = malloc(sizeof(int) * vertex_count);
//         CHECK_ALLOC(adj_matrix[i]);
//         if(!fgets(line, vertex_count + 2, file)){
//             break;
//         }
//         for(int j = 0; j < vertex_count; j++){
//             adj_matrix[i][j] = line[j] - '0';
//         }
//     }
//     free(line);
//     return adj_matrix;
// }

// void print_adj_matrix(int** matrix, int vertex_count){
//     for(int i = 0; i < vertex_count; i++){
//         for(int j = 0; j < vertex_count; j++){
//             printf("%d, ", matrix[i][j]);
//         }
//         printf("\n");
//     }
// }

// int main (){
//     FILE* file = fopen("../undirected_raph3.txt", "r");
//     if(file == NULL) {
//         printf("Not able to open the file.\n");
//         return 1;
//     }

//     int vertex_count = get_vertex_count(file);
//     int is_directed_flag = is_directed(file, vertex_count);
//     int** adj_matrix = read_adjacency_matrix(file, vertex_count);
//     printf("vertex count: %d\n", vertex_count);
//     print_adj_matrix(adj_matrix, vertex_count);
    
//     fclose(file);
    
//     graph_t* graph = create_graph(adj_matrix, vertex_count, is_directed_flag);
//     print_graph(graph);

//     printf("is eulerian: %d\n", is_eulerian(graph));

//     return 0;
// }


//this below is for minimal spanning tree

int main(){
    graph_t* graph = create_random_filled_graph();
    printf("\nOriginal graph:\n");
    print_graph(graph);
    graph_t* mst = build_mst(graph);
    printf("\nMST:\n");
    print_graph(mst);
    graph = free_graph(graph);
    mst = free_graph(mst);  
    return 0;
}