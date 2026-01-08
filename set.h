#pragma once
#include<stdlib.h>
#include "graphs.h"
#include "edges.h"

typedef edge_t* set_type;

typedef struct {
    set_type* elements;
    int count;
}set_t;

void add_element_to_set(set_t* set, set_type new_element);