#include "queue.h"

#include <stdlib.h>

void queue_init(Queue *queue) {
    queue->front = NULL;
    queue->rear  = NULL;
}

bool queue_isempty(Queue *queue) {
    return queue->front == NULL;
}

void queue_push(Queue *queue, void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (queue_isempty(queue)) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear       = new_node;
    }
}

void *queue_pop(Queue *queue) {
    if (queue_isempty(queue)) {
        return NULL;
    }

    Node *temp   = queue->front;
    void *data   = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

void queue_destroy(Queue *queue, void (*free_fn)(void *)) {
    while (queue->front != queue->rear) {
        Node *temp   = queue->front;
        queue->front = queue->front->next;
        if (free_fn)
            free_fn(temp->data);
        free(temp);
    }
    free(queue->front);
    queue->front = queue->rear = NULL;
}
