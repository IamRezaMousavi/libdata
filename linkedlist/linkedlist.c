#include <stdlib.h>

#include "linkedlist.h"

GList *g_list_alloc(void *data) {
  GList *new_node = (GList *)malloc(sizeof(GList));
  new_node->data = data;
  new_node->prev = NULL;
  new_node->next = NULL;
  return new_node;
}

GList *g_list_append(GList *list, void *data) {
  GList *new_node = g_list_alloc(data);

  if (list == NULL) return new_node;

  GList *last = list;
  while (last->next != NULL)
	last = last->next;

  last->next = new_node;
  new_node->prev = last;

  return list;
}

GList *g_list_find(GList *list, void *data) {
  GList *current = list;

  while (current != NULL) {
	if (current->data == data) return current;
	current = current->next;
  }

  return NULL;
}

GList *g_list_delete_link(GList *list, GList *link) {
  if (link == NULL) return list;

  if (link == list) list = link->next;

  if (link->prev != NULL) link->prev->next = link->next;

  if (link->next != NULL) link->next->prev = link->prev;

  free(link);
  return list;
}

GList *g_list_remove(GList *list, void *data) {
  GList *link = g_list_find(list, data);
  if (link != NULL) return g_list_delete_link(list, link);
  return list;
}

void g_list_foreach(GList *list, void (*func)(void *)) {
  GList *current = list;
  while (current != NULL) {
	func(current->data);
	current = current->next;
  }
}

void g_list_free(GList *list) {
  GList *current = list;

  while (current != NULL) {
	GList *next = current->next;
	free(current);
	current = next;
  }
}
