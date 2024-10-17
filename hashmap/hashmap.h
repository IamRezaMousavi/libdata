#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#define TABLE_SIZE 101

typedef struct Node {
  char *key;
  char *value;
  struct Node *next;
} Node;

typedef struct HashTable {
  Node *buckets[TABLE_SIZE];
} HashTable;

HashTable *create_table();
void set(HashTable *table, const char *key, const char *value);
char *get(HashTable *table, const char *key);
void foreach (HashTable *table, void (*callback)(const char *, const char *));
void free_table(HashTable *table);

#endif /* __HASHMAP_H__ */
