#include "queue.h"
#include "stdlib.h"

queue_t *queue_create()
{
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    q->front = NULL;
    q->back = NULL;
    return q;
}

static int queue_is_empty(queue_t *q)
{
    return q->front == NULL;
}

void queue_enqueue(queue_t *q, void *value)
{
    queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
    new_node->value = value;
    new_node->next = NULL;

    if (q->back != NULL)
    {
        q->back->next = new_node;
    }
    q->back = new_node;

    if (q->front == NULL)
    {
        q->front = new_node;
    }
}

void *queue_dequeue(queue_t *q)
{
    if (queue_is_empty(q))
    {
        return NULL;
    }

    queue_node_t *front_node = q->front;
    void *value = front_node->value;
    q->front = front_node->next;

    if (q->front == NULL)
    {
        q->back = NULL;
    }

    free(front_node);
    return value;
}