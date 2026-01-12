#pragma once 
#include "set.h"

#define VERTEX_COUNT 6

#define CHECK_ALLOC(PTR)                  \
if (PTR == NULL)                          \
{                                         \
    printf("Memory allocation failed\n"); \
    exit(1);                              \
}


typedef struct vertex{
    int value;
    set_t neighbors;
}vertex_t;

vertex_t* create_vertex(int value);
set_t* create_graph(int matrix[VERTEX_COUNT][VERTEX_COUNT]);