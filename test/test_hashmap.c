#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdata/datastruct/hashmap.h>

void print_key_value(const char *key, const char *value) {
    printf("Key: %s, Value: %s\n", key, value);
}

void test_hashmap_create() {
    printf("test_hashmap_create...");

    HashMap *map = hashmap_create();
    assert(map != NULL);

    for (int i = 0; i < TABLE_SIZE; i++) {
        assert(map->buckets[i] == NULL);
    }

    hashmap_free(map);
    printf("passed!\n");
}

void test_hashmap_set_get() {
    printf("test_hashmap_set_get...");

    HashMap *map = hashmap_create();

    hashmap_set(map, "name", "Alice");
    hashmap_set(map, "age", "30");
    hashmap_set(map, "city", "Wonderland");

    assert(strcmp(hashmap_get(map, "name"), "Alice") == 0);
    assert(strcmp(hashmap_get(map, "age"), "30") == 0);
    assert(strcmp(hashmap_get(map, "city"), "Wonderland") == 0);

    // Test non-existent key
    assert(hashmap_get(map, "country") == NULL);

    hashmap_free(map);
    printf("passed!\n");
}

void test_hashmap_overwrite() {
    printf("test_hashmap_overwrite...");

    HashMap *map = hashmap_create();

    hashmap_set(map, "name", "Bob");
    assert(strcmp(hashmap_get(map, "name"), "Bob") == 0);

    hashmap_set(map, "name", "Charlie");
    assert(strcmp(hashmap_get(map, "name"), "Charlie") == 0);

    hashmap_free(map);
    printf("passed!\n");
}

void test_hashmap_foreach() {
    printf("test_hashmap_foreach...");

    HashMap *map = hashmap_create();

    printf("\n");
    hashmap_set(map, "name", "reza");
    hashmap_set(map, "age", "24");
    hashmap_set(map, "city", "tehran");

    hashmap_foreach(map, print_key_value);

    hashmap_free(map);
    printf("passed!\n");
}

int main() {
    test_hashmap_create();
    test_hashmap_set_get();
    test_hashmap_overwrite();
    test_hashmap_foreach();

    printf("All tests passed successfully!\n");
    return 0;
}
