#pragma once
#include<stdlib.h>
#include "graphs.h"

typedef struct {
    vertex_t** elements;
    int count;
}set_t;

void add_vertex_to_set(set_t* set, vertex_t* new_vertex);