#include "set.h"
#include "edges.h"

set_t* create_empty_set(){
    set_t* set = malloc(sizeof(set_t));
    CHECK_ALLOC(set);
    set->elements = NULL;
    set->count = 0;
    return set;
}

void add_element_to_set(set_t* set, void* new_element){
    int found = 0;
    for(int i = 0; i < set->count; i++){
        if(set->elements[i] = new_element){
            found = 1;
            break;
        }
    }
    if(!found){
        set->elements = realloc(set->elements, (set->count + 1)*sizeof(void*));
        set->elements[set->count] = new_element;
        set->count++;
    }
}