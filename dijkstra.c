#include "dijkstra.h"
#include "graphs.h"
#include "edges.h"

typedef struct{
    vertex_t* curr_vertex;
    int visited;
    int distance;
    vertex_t* previous_vertex;
}table_entry_t;

static table_entry_t* create_table(graph_t* graph, vertex_t* start_vertex){
    table_entry_t* table = malloc(sizeof(table_entry_t) * graph->vertices.count);
    CHECK_ALLOC(table);
    for (int i = 0; i < graph->vertices.count; i++)
    {
        vertex_t* vertex = graph->vertices.elements[i];
        table[i].curr_vertex = vertex;
        table[i].visited = 0;
        table[i].distance = __INT_MAX__;
        table[i].previous_vertex = NULL;
        if (vertex == start_vertex)
        {
            table[i].distance = 0;
        }
    }
    return table;
}

static int get_table_entry_index(table_entry_t* table, graph_t* graph, vertex_t* vertex){
    for (int i = 0; i < graph->vertices.count; i++)
    {
        if (table[i].curr_vertex == vertex)
        return i;
    }
    return -1;
}

static int all_visited(table_entry_t* table, graph_t* graph){
    for (int i = 0; i < graph->vertices.count; i++)
    {
        if (table[i].visited == 0)
        return 0;
    }
    return 1;
}

dijkstra_route_t* create_route(vertex_t* end_vertex, graph_t* graph, table_entry_t* table){
    dijkstra_route_t* route = (dijkstra_route_t*)malloc(sizeof(dijkstra_route_t));
    CHECK_ALLOC(route);
    route->route = create_list();
    
    vertex_t* curr_vertex = end_vertex;
    table_entry_t* curr_vertex_table_entry = &table[get_table_entry_index(table, graph, curr_vertex)];
    
    route->distance = curr_vertex_table_entry->distance;
    
    if (route->distance == __INT_MAX__) {
        free(route);
        return NULL;
    }
    
    while(curr_vertex != NULL){
        push_front_ll_node(route->route, curr_vertex);
        curr_vertex = curr_vertex_table_entry->previous_vertex;
        if (curr_vertex != NULL) {
            curr_vertex_table_entry = &table[get_table_entry_index(table, graph, curr_vertex)];
        }
    }
    return route;
}

dijkstra_route_t* dijkstra(graph_t* g, vertex_t* start_vertex, vertex_t* end_vertex){
    vertex_t* curr_vertex = start_vertex;
    table_entry_t* table = create_table(g, start_vertex);

    while (curr_vertex != NULL)
    {
        int curr_vertex_index = get_table_entry_index(table, g, curr_vertex);
        if (curr_vertex_index < 0) {
            break;
        }

        table[curr_vertex_index].visited = 1;

        for (int i = 0; i < curr_vertex->neighbors.count; i++)
        {
            edge_t* edge = curr_vertex->neighbors.elements[i];
            vertex_t* neighbor = get_neighbor(curr_vertex, edge);
            int neighbor_index = get_table_entry_index(table, g, neighbor);
            if (neighbor_index < 0 || table[neighbor_index].visited)
                continue;

            int edge_weight = edge->weight;
            int new_distance = table[curr_vertex_index].distance + edge_weight;
            if (new_distance < table[neighbor_index].distance)
            {
                table[neighbor_index].distance = new_distance;
                table[neighbor_index].previous_vertex = curr_vertex;
            }
        }

        int min_distance = __INT_MAX__;
        vertex_t* next_vertex = NULL;
        for (int i = 0; i < g->vertices.count; i++)
        {
            if (table[i].visited == 0 && table[i].distance < min_distance)
            {
                min_distance = table[i].distance;
                next_vertex = table[i].curr_vertex;
            }
        }

        curr_vertex = next_vertex;
    }

    dijkstra_route_t* route = create_route(end_vertex, g, table);
    free(table);
    return route;
}

void print_dijkstra_route(dijkstra_route_t* route){
    if (route == NULL)
    {
        printf("No route found.\n");
        return;
    }
    printf("Distance: %d\n", route->distance);
    printf("Route: ");
    ll_node* curr_node = route->route->head;
    while(curr_node != NULL){
        vertex_t* vertex = (vertex_t*)curr_node->value;
        printf("%d ", vertex->value);
        curr_node = curr_node->next;
    }
    printf("\n");
}

dijkstra_route_t* free_dijkstra_route(dijkstra_route_t* route){
    if(route == NULL){
        return route;
    }
    delete_list(route->route);
    free(route);
    return NULL;
}