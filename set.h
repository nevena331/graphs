#pragma once
#include<stdlib.h>
#include "graphs.h"
#include "edges.h"

typedef struct {
    void** elements;
    int count;
}set_t;

set_t* create_empty_set();
void add_element_to_set(set_t* set, void* new_element);