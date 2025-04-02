#ifndef __LIST_H__
#define __LIST_H__

typedef struct List {
    void        *data;
    struct List *prev;
    struct List *next;
} List;

List *list_append(List *list, void *data);
List *list_find(List *list, void *data);
List *list_remove(List *list, void *data);
void  list_foreach(List *list, void (*func)(void *));
void  list_free(List *list, void (*free_fn)(void *));

#endif /* __LIST_H__ */
