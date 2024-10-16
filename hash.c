#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

typedef struct Node {
  char *key;
  char *value;
  struct Node *next;
} Node;

typedef struct HashTable {
  Node *buckets[TABLE_SIZE];
} HashTable;

// MurmurHash3
uint32_t murmurhash(const char *key, uint32_t len, uint32_t seed) {
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  uint32_t r1 = 15;
  uint32_t r2 = 13;
  uint32_t m = 5;
  uint32_t n = 0xe6546b64;

  uint32_t hash = seed;
  const int nblocks = len / 4;
  const uint32_t *blocks = (const uint32_t *)(key);
  for (int i = 0; i < nblocks; i++) {
    uint32_t k = blocks[i];
    k *= c1;
    k = (k << r1) | (k >> (32 - r1));
    k *= c2;

    hash ^= k;
    hash = (hash << r2) | (hash >> (32 - r2));
    hash = hash * m + n;
  }

  const uint8_t *tail = (const uint8_t *)(key + nblocks * 4);
  uint32_t k1 = 0;

  switch (len & 3) {
  case 3:
    k1 ^= tail[2] << 16;
  case 2:
    k1 ^= tail[1] << 8;
  case 1:
    k1 ^= tail[0];
    k1 *= c1;
    k1 = (k1 << r1) | (k1 >> (32 - r1));
    k1 *= c2;
    hash ^= k1;
  }

  hash ^= len;
  hash ^= (hash >> 16);
  hash *= 0x85ebca6b;
  hash ^= (hash >> 13);
  hash *= 0xc2b2ae35;
  hash ^= (hash >> 16);

  return hash;
}

Node *create_node(const char *key, const char *value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->key = strdup(key);
  new_node->value = strdup(value);
  new_node->next = NULL;
  return new_node;
}

HashTable *create_table() {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  for (int i = 0; i < TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

void set(HashTable *table, const char *key, const char *value) {
  uint32_t hash = murmurhash(key, strlen(key), 0);
  int index = hash % TABLE_SIZE;

  Node *new_node = create_node(key, value);

  if (table->buckets[index] == NULL) {
    table->buckets[index] = new_node;
  } else {
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
  }
}

char *get(HashTable *table, const char *key) {
  uint32_t hash = murmurhash(key, strlen(key), 0);
  int index = hash % TABLE_SIZE;

  Node *current = table->buckets[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->value;
    }
    current = current->next;
  }
  return NULL;
}

void foreach (HashTable *table, void (*callback)(const char *, const char *)) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Node *current = table->buckets[i];
    while (current != NULL) {
      callback(current->key, current->value);
      current = current->next;
    }
  }
}

void free_table(HashTable *table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Node *current = table->buckets[i];
    while (current != NULL) {
      Node *temp = current;
      current = current->next;
      free(temp->key);
      free(temp->value);
      free(temp);
    }
  }
  free(table);
}

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
