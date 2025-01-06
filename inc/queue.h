#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Node {
    void        *data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

void queue_init(Queue *queue);

void queue_push(Queue *queue, void *data);

void *queue_pop(Queue *queue);

void queue_destroy(Queue *queue);

#endif /* __QUEUE_H__ */
