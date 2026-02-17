#pragma once

typedef struct queue_node
{
    void *value;
    struct queue_node *next;
} queue_node_t;

struct queue_t
{
    queue_node_t *front;
    queue_node_t *back;
};

typedef struct queue_t queue_t;

queue_t *queue_create();

int queue_is_empty(queue_t *q);

void queue_enqueue(queue_t *q, void *value);
void* queue_dequeue(queue_t *q);