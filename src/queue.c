#include "queue.h"

#include <stdlib.h>

void queue_init(Queue *queue) {
    queue->front = NULL;
    queue->rear  = NULL;
}

void queue_push(Queue *queue, void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear       = new_node;
    }
}

void *queue_pop(Queue *queue) {
    if (queue->front == NULL) {
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

void queue_destroy(Queue *queue) {
    while (queue->front != NULL) {
        Node *temp   = queue->front;
        queue->front = queue->front->next;
        free(temp->data);
        free(temp);
    }
}
