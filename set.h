#pragma once
#include<stdlib.h>

typedef struct {
    void** elements;
    int count;
}set_t;

set_t* create_empty_set();
void add_element_to_set(set_t* set, void* new_element);
void remove_element_from_set(set_t* set, void* element_to_delete);