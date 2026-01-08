#include "set.h"

void add_vertex_to_set(set_t* set, vertex_t* new_vertex){
    int found = 0;
    for(int i = 0; i < set->count; i++){
        if(set->elements[i]->value = new_vertex->value){
            found = 1;
            break;
        }
    }
    if(!found){
        set->elements = realloc(set->elements, set->count + 1);
        set->elements[set->count] = new_vertex;
        set->count++;
    }
}