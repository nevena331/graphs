#pragma once
#include "graphs.h"
#include "edges.h"

void connected_component_only_internal(graph_t* graph, vertex_t* first_vertex, int* visited);
int is_eulerian(graph_t* graph);