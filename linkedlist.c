#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Value {
  int id;
  char name[10];
} Value;

typedef struct GList {
  void *data;
  struct GList *prev;
  struct GList *next;
} GList;

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

void print_num(void *data) {
  int value = *((int *)data);
  printf("%d ->", value);
}

void print_value(void *data) {
  Value value = *((Value *)data);
  printf("{ .id = %d, .name = %s} ->", value.id, value.name);
}

int main() {

  // ================ number ==============

  GList *list = NULL;

  int data1 = 10, data2 = 20, data3 = 30;
  list = g_list_append(list, &data1);
  list = g_list_append(list, &data2);
  list = g_list_append(list, &data3);

  g_list_foreach(list, print_num);
  printf("\n");

  list = g_list_remove(list, &data2);
  g_list_foreach(list, print_num);
  printf("\n");

  g_list_free(list);

  // ================ Value ==============

  list = NULL;

  Value *v1 = (Value *)malloc(sizeof(Value));
  v1->id = 10;
  strcpy(v1->name, "Alice");

  Value *v2 = (Value *)malloc(sizeof(Value));
  v2->id = 10;
  strcpy(v2->name, "Bob");

  Value *v3 = (Value *)malloc(sizeof(Value));
  v3->id = 10;
  strcpy(v3->name, "Charlie");

  list = g_list_append(list, v1);
  list = g_list_append(list, v2);
  list = g_list_append(list, v3);

  g_list_foreach(list, print_value);
  printf("\n");

  list = g_list_remove(list, v2);

  g_list_foreach(list, print_value);
  printf("\n");

  g_list_free(list);

  return 0;
}
