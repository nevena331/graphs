#pragma once 
 

#ifndef CHECK_ALLOC
#define CHECK_ALLOC(PTR)                  \
if (PTR == NULL)                          \
{                                         \
    printf("Memory allocation failed\n"); \
    exit(1);                              \
}
#endif

typedef struct ll_node{
    void* value;
    struct ll_node * next;
}ll_node;

typedef struct l_list{
    ll_node * head;
    ll_node * tail;
}l_list;

l_list* create_list();
void add_ll_node(l_list* list, void* value);

void* get_ll_node_by_value(l_list* list, void* value);
void* get_ll_node_by_index(l_list* list, int index);

void* delete_ll_node_by_value(l_list* list, void* value);
void*delete_ll_node_by_index(l_list* list, int index);

l_list* delete_list(l_list* list);
