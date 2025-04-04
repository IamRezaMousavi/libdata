#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

typedef struct Node {
    void        *data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

void queue_init(Queue *queue);

bool queue_isempty(Queue *queue);

void queue_push(Queue *queue, void *data);

void *queue_pop(Queue *queue);

void queue_destroy(Queue *queue, void (*free_fn)(void *));

#endif /* __QUEUE_H__ */
