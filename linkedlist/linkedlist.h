#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct GList {
  void         *data;
  struct GList *prev;
  struct GList *next;
} GList;

GList *g_list_append(GList *list, void *data);
GList *g_list_find(GList *list, void *data);
GList *g_list_delete_link(GList *list, GList *link);
GList *g_list_remove(GList *list, void *data);
void   g_list_foreach(GList *list, void (*func)(void *));
void   g_list_free(GList *list);

#endif /* __LINKEDLIST_H__ */
