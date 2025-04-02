#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void test_queue_init() {
    printf("test_queue_init...");

    Queue q;
    queue_init(&q);

    assert(q.front == NULL);
    assert(q.rear == NULL);

    printf("passed!\n");
}

void test_queue_push_single() {
    printf("test_queue_push_single...");

    Queue q;
    queue_init(&q);

    int data = 42;
    queue_push(&q, &data);

    assert(q.front != NULL);
    assert(q.rear != NULL);
    assert(q.front == q.rear); // Only one element
    assert(*(int *)q.front->data == data);

    queue_destroy(&q, NULL);
    printf("passed!\n");
}

void test_queue_push_multiple() {
    printf("test_queue_push_multiple...");

    Queue q;
    queue_init(&q);

    int data1 = 10, data2 = 20, data3 = 30;
    queue_push(&q, &data1);
    queue_push(&q, &data2);
    queue_push(&q, &data3);

    assert(q.front != NULL);
    assert(q.rear != NULL);
    assert(*(int *)q.front->data == data1);
    assert(*(int *)q.rear->data == data3);

    queue_destroy(&q, NULL);
    printf("passed!\n");
}

void test_queue_pop_empty() {
    printf("test_queue_pop_empty...");

    Queue q;
    queue_init(&q);

    void *result = queue_pop(&q);
    assert(result == NULL);

    printf("passed!\n");
}

void test_queue_fifo_order() {
    printf("test_queue_fifo_order...");

    Queue q;
    queue_init(&q);

    int data1 = 100, data2 = 200, data3 = 300;
    queue_push(&q, &data1);
    queue_push(&q, &data2);
    queue_push(&q, &data3);

    assert(*(int *)queue_pop(&q) == data1);
    assert(*(int *)queue_pop(&q) == data2);
    assert(*(int *)queue_pop(&q) == data3);
    assert(queue_pop(&q) == NULL); // Queue should be empty now

    printf("passed!\n");
}

void test_queue_mixed_operations() {
    printf("test_queue_mixed_operations...");

    Queue q;
    queue_init(&q);

    int values[] = {1, 2, 3, 4, 5};

    queue_push(&q, &values[0]);
    queue_push(&q, &values[1]);
    queue_push(&q, &values[2]);

    assert(*(int *)queue_pop(&q) == values[0]);
    assert(*(int *)queue_pop(&q) == values[1]);

    queue_push(&q, &values[3]);
    queue_push(&q, &values[4]);

    assert(*(int *)queue_pop(&q) == values[2]);
    assert(*(int *)queue_pop(&q) == values[3]);
    assert(*(int *)queue_pop(&q) == values[4]);
    assert(queue_pop(&q) == NULL);

    printf("passed!\n");
}

void test_queue_destroy() {
    printf("test_queue_destroy...");

    Queue q;
    queue_init(&q);

    int data1 = 5, data2 = 10;
    queue_push(&q, &data1);
    queue_push(&q, &data2);

    queue_destroy(&q, NULL);

    assert(q.front == NULL);
    assert(q.rear == NULL);

    printf("passed!\n");
}

void test_queue_different_types() {
    printf("test_queue_different_types...");

    Queue q;
    queue_init(&q);

    double d = 3.14159;
    queue_push(&q, &d);

    char *str = "test string";
    queue_push(&q, str);

    assert(*(double *)queue_pop(&q) == d);
    assert(queue_pop(&q) == str);

    queue_destroy(&q, NULL);
    printf("passed!\n");
}

int main() {
    test_queue_init();
    test_queue_push_single();
    test_queue_push_multiple();
    test_queue_pop_empty();
    test_queue_fifo_order();
    test_queue_mixed_operations();
    test_queue_destroy();
    test_queue_different_types();

    printf("All queue tests passed successfully!\n");
    return 0;
}
