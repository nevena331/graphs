#pragma once 
#include "set.h"

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