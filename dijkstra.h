#pragma once

#include "graphs.h"
#include "linked_list.h"

typedef struct{
    l_list* route;
    int distance;
}dijkstra_route_t;

dijkstra_route_t* dijkstra(graph_t* g,  vertex_t* start_vertex, vertex_t* end_vertex);
void print_dijkstra_route(dijkstra_route_t* route);
dijkstra_route_t* free_dijkstra_route(dijkstra_route_t* route);

