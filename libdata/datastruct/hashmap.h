#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#define TABLE_SIZE 101

typedef struct Node {
    char        *key;
    char        *value;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node *buckets[TABLE_SIZE];
} HashMap;

HashMap *hashmap_create();
void     hashmap_set(HashMap *table, const char *key, const char *value);
char    *hashmap_get(HashMap *table, const char *key);
void     hashmap_foreach(HashMap *table, void (*callback)(const char *, const char *));
void     hashmap_free(HashMap *table);

#endif /* __HASHMAP_H__ */
