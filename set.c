#include "set.h"
#include "edges.h"

void add_element_to_set(set_t* set, set_type new_element){
    int found = 0;
    for(int i = 0; i < set->count; i++){
        if(set->elements[i] = new_element){
            found = 1;
            break;
        }
    }
    if(!found){
        set->elements = realloc(set->elements, set->count + 1);
        set->elements[set->count] = new_element;
        set->count++;
    }
}