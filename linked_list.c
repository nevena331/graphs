#include <stdlib.h>

#include "linked_list.h"

l_list* create_list(){
    l_list* linked_list = calloc(1, sizeof(l_list));
    CHECK_ALLOC(linked_list);
    linked_list->head = NULL;
    linked_list->tail = NULL;
    return linked_list;
}

void add_ll_node(l_list* list, void* value){
    if(list == NULL){
        return;
    }
    ll_node* new_node = malloc(sizeof(ll_node));
    CHECK_ALLOC(new_node);
    new_node->value = value;
    new_node->next = NULL;

    if(list->tail == NULL){
        list->head = new_node;
        list->tail = new_node;
    }else{
        list->tail = new_node;  
    }
}

void* get_ll_node_by_value(l_list* list, void* value){
    if(list == NULL){
        return NULL;
    }
    ll_node* curr_node = list->head;
    do{
        if(curr_node->value == value){
            return curr_node;
        }
        curr_node = curr_node->next;
    }while(curr_node != NULL);
    return NULL;
}

void* get_ll_node_by_index(l_list* list, int index){
    if(list == NULL){
        return NULL;
    }
    ll_node* current_node = list->head;
    for(int i = 0; i <= index; i++){
        current_node = current_node->next;
        if(current_node == NULL){
            return NULL;
        }
    }
    return current_node;
}


void* delete_ll_node_by_value(l_list* list, void* value){
    if(list == NULL){
        return NULL;
    }
    ll_node* current_node = list->head;
    ll_node* prev_node = NULL;
    while(current_node != NULL){
        if(current_node->value == value){
            if(prev_node == NULL){
                list->head = current_node->next;
            }else{
                prev_node->next = current_node->next;
            }
            if(current_node == list->tail){
                list->tail = prev_node;
            }
            void* node_value = current_node->value;
            free(current_node);
            return node_value;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }
    return NULL;
}

void*delete_ll_node_by_index(l_list* list, int index){
    if(list == NULL){
        return NULL;
    }
    ll_node* current_node = list->head;
    ll_node* prev_node = NULL;
    for(int i = 0; i <= index; i++){
        if(current_node == NULL){
            return NULL;
        }
        if(i == index){
            if(prev_node == NULL){
                list->head = current_node->next;
            }else{
                prev_node->next = current_node->next;
            }
            if(current_node == list->tail){
                list->tail = prev_node;
            }
            void* node_value = current_node->value;
            free(current_node);
            return node_value;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }
    return NULL;
}

l_list* delete_list(l_list* list){
    if(list == NULL){
        return NULL;
    }
    ll_node* current_node = list->head;
    while(current_node != NULL){
        ll_node* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
    return NULL;
}