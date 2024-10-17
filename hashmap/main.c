#include <stdio.h>

#include "hashmap.h"

void print_key_value(const char *key, const char *value) {
  printf("Key: %s, Value: %s\n", key, value);
}

int main() {
  HashTable *table = create_table();

  set(table, "name", "reza");
  set(table, "age", "24");
  set(table, "city", "tehran");

  printf("name:   %s\n", get(table, "name"));
  printf("age:    %s\n", get(table, "age"));
  printf("city:   %s\n", get(table, "city"));
  printf("home:   %s\n", get(table, "home"));

  printf("=============\n");

  foreach (table, print_key_value)
	;

  printf("=============\n");

  free_table(table);

  return 0;
}
