#pragma once 
#include "set.h"
#include <stdio.h>

#define CHECK_ALLOC(PTR)                  \
if (PTR == NULL)                          \
{                                         \
    printf("Memory allocation failed\n"); \
    exit(1);                              \
}

typedef struct{
    set_t vertices;
    int is_directed;
}graph_t;


typedef struct{
    int value;
    set_t neighbors;
}vertex_t;

vertex_t* create_vertex(int value);
vertex_t* get_vertex(graph_t* graph, int value);

graph_t* create_empty_graph(int is_directed);
graph_t* create_graph(int** matrix, int vertex_count, int is_directed);

int get_vertex_index(graph_t* graph, vertex_t* vertex_to_find);
int get_neighbor_index(graph_t* graph, vertex_t* curr_vertex, void* edge);

int is_cyclical(graph_t* graph);
graph_t* topological_sort(graph_t* graph);
int is_reachable(graph_t* graph, vertex_t* start_vertex, vertex_t* end_vertex);


void print_graph(graph_t* graph);
graph_t* free_graph(graph_t* graph);