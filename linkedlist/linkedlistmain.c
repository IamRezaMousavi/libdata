#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

typedef struct Value {
  int  id;
  char name[10];
} Value;

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
  v1->id    = 10;
  strcpy(v1->name, "Alice");

  Value *v2 = (Value *)malloc(sizeof(Value));
  v2->id    = 10;
  strcpy(v2->name, "Bob");

  Value *v3 = (Value *)malloc(sizeof(Value));
  v3->id    = 10;
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
