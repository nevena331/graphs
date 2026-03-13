#include <stdio.h>
#include <stdlib.h>

#include "pathfinding.h"

void print_route(route_t* route){
    if(route == NULL){
        printf("No route found\n");
        return;
    }
    ll_node* current_node = route->route.head;
    while(current_node != NULL){
        vertex_t* vertex = (vertex_t*)(current_node->value);
        printf("%d, ", vertex->value);
        current_node = current_node->next;
    }
    printf("\nRoute weight: %d\n", route->weight);
}

route_t* free_route(route_t* route){
    if(route == NULL){
        return NULL;
    }
    ll_node* current_node = route->route.head;
    while(current_node != NULL){
        ll_node* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(route);
    return NULL;
}

static void add_vertex_to_route(route_t* route, vertex_t* vertex_to_add){
    int weight = get_edge((vertex_t*)(route->route.tail->value), vertex_to_add)->weight;
    route->weight += weight;
    add_ll_node(&(route->route), vertex_to_add);
}

static void remove_vertex_from_route(route_t* route){
    if(route->route.tail == NULL){
        return;
    }
    ll_node* prev_node = route->route.head;
    while(prev_node->next != route->route.tail){
        prev_node = prev_node->next;
    }
    int weight = get_edge((vertex_t*)(prev_node->value), (vertex_t*)(route->route.tail->value))->weight;
    route->weight -= weight;

    free(route->route.tail);
    route->route.tail = prev_node;
    route->route.tail->next = NULL;
}

static route_t* dfs_route_internal(graph_t* graph, route_t* route, int* visited, vertex_t* end){
    vertex_t* last_vertex = (vertex_t*)(route->route.tail->value);
    for(int i = 0; i < last_vertex->neighbors.count; i++){
        edge_t* curr_edge = last_vertex->neighbors.elements[i];
        vertex_t* curr_neighbor = get_neighbor(last_vertex, curr_edge);
        int curr_neighbor_index = get_vertex_index(graph, curr_neighbor);
        if(visited[curr_neighbor_index]){
            continue;
        }
        visited[curr_neighbor_index] = 1;
        add_vertex_to_route(route, curr_neighbor);
        if(curr_neighbor == end){
            return route;
        }

        route = dfs_route_internal(graph, route, visited, end);
        if(route != NULL){
            return route;
        }
    }
    return NULL;
}

route_t* dfs_route(graph_t* graph, vertex_t* start, vertex_t* end){
    if(!is_reachable(graph, start, end)){
        return NULL;
    }
    route_t* route = malloc(sizeof(route_t));
    CHECK_ALLOC(route);
    route->weight = 0;
    add_ll_node(&(route->route), start);
    if(start == end){
        return route;
    }
    
    int* visited = calloc(graph->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    visited[get_vertex_index(graph, start)] = 1;

    route = dfs_route_internal(graph, route, visited, end);
    free(visited);
    return route;
}

static route_t* dfs_shortest_route_internal(graph_t* graph, route_t* route, int* visited, vertex_t* end){

}

static route_t* dfs_shortest_route(graph_t* graph, vertex_t* start, vertex_t* end){
    if(!is_reachable(graph, start, end)){
        return NULL;
    }
    route_t* shortest_route = malloc(sizeof(route_t));
    CHECK_ALLOC(shortest_route);
    shortest_route->weight = 0;
    add_ll_node(&(shortest_route->route), start);
    if(start == end){
        return shortest_route;
    }

    int* visited = calloc(graph->vertices.count, sizeof(int));
    CHECK_ALLOC(visited);
    visited[get_vertex_index(graph, start)] = 1;

}
static route_t* dfs_lightest_route(graph_t* graph, vertex_t* start, vertex_t* end);

route_t* dfs_easiest_route(graph_t* graph, vertex_t* start, vertex_t* end){
    if(graph->is_weighted){
        return dfs_lightest_route(graph, start, end);
    } else {
        return dfs_shortest_route(graph, start, end);
    }
}
