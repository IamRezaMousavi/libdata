#include "list.h"

#include <stdlib.h>

static List *list_new(void *data) {
    List *new_node = (List *)malloc(sizeof(List));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

List *list_append(List *list, void *data) {
    List *new_node = list_new(data);

    if (list == NULL)
        return new_node;

    List *last = list;
    while (last->next != NULL)
        last = last->next;

    last->next     = new_node;
    new_node->prev = last;

    return list;
}

List *list_find(List *list, void *data) {
    List *current = list;

    while (current != NULL) {
        if (current->data == data)
            return current;
        current = current->next;
    }

    return NULL;
}

static List *list_delete_link(List *list, List *link) {
    if (link == NULL)
        return list;

    if (link == list)
        list = link->next;

    if (link->prev != NULL)
        link->prev->next = link->next;

    if (link->next != NULL)
        link->next->prev = link->prev;

    free(link);
    return list;
}

List *list_remove(List *list, void *data) {
    List *link = list_find(list, data);
    if (link != NULL)
        return list_delete_link(list, link);
    return list;
}

void list_foreach(List *list, void (*func)(void *)) {
    List *current = list;
    while (current != NULL) {
        func(current->data);
        current = current->next;
    }
}

void list_free(List *list, void (*free_fn)(void *)) {
    List *current = list;

    while (current != NULL) {
        List *next = current->next;
        if (free_fn)
            free_fn(current->data);
        free(current);
        current = next;
    }
}
