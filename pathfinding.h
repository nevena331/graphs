#pragma once

#include "graphs.h"
#include "edges.h"
#include "linked_list.h"

typedef struct route{
    l_list route;
    int weight; //if weighted actual weight, if not number of edges
}route_t;

void print_route(route_t* route);
route_t* free_route(route_t* route);

route_t* dfs_route(graph_t* graph, vertex_t* start, vertex_t* end);
route_t* dfs_shortest_route(graph_t* graph, vertex_t* start, vertex_t* end);
route_t* dfs_lightest_route(graph_t* graph, vertex_t* start, vertex_t* end);

route_t* bfs_route(graph_t* graph, vertex_t* start, vertex_t* end);
route_t* bfs_shortest_route(graph_t* graph, vertex_t* start, vertex_t* end);
route_t* bfs_lightest_route(graph_t* graph, vertex_t* start, vertex_t* end);