#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdata/datastruct/list.h>

// Helper function for printing integers
void print_int(void *data) {
    printf("%d ", *(int *)data);
}

// Helper function for freeing strings
void free_string(void *data) {
    free(data);
}

void test_append_to_empty() {
    printf("test_append_to_empty...");

    List *list = NULL;
    int   data = 42;

    list = list_append(list, &data);

    assert(list != NULL);
    assert(list->data == &data);
    assert(list->prev == NULL);
    assert(list->next == NULL);

    list_free(list, NULL);
    printf("passed!\n");
}

void test_append_multiple() {
    printf("test_append_multiple...");

    List *list  = NULL;
    int   data1 = 1, data2 = 2, data3 = 3;

    list = list_append(list, &data1);
    list = list_append(list, &data2);
    list = list_append(list, &data3);

    assert(list != NULL);
    assert(*(int *)list->data == data1);
    assert(*(int *)list->next->data == data2);
    assert(*(int *)list->next->next->data == data3);
    assert(list->next->next->next == NULL);

    // Test prev pointers
    assert(list->next->prev == list);
    assert(list->next->next->prev == list->next);

    list_free(list, NULL);
    printf("passed!\n");
}

void test_list_find() {
    printf("test_list_find...");

    List *list  = NULL;
    int   data1 = 10, data2 = 20, data3 = 30;

    list = list_append(list, &data1);
    list = list_append(list, &data2);
    list = list_append(list, &data3);

    List *found = list_find(list, &data2);
    assert(found != NULL);
    assert(found->data == &data2);

    // Test non-existent item
    int not_in_list = 99;
    assert(list_find(list, &not_in_list) == NULL);

    list_free(list, NULL);
    printf("passed!\n");
}

void test_list_remove() {
    printf("test_list_remove...");

    List *list  = NULL;
    int   data1 = 100, data2 = 200, data3 = 300;

    list = list_append(list, &data1);
    list = list_append(list, &data2);
    list = list_append(list, &data3);

    // Remove middle item
    list = list_remove(list, &data2);
    assert(list_find(list, &data2) == NULL);
    assert(list->next->data == &data3);
    assert(list->next->prev == list);

    // Remove first item
    list = list_remove(list, &data1);
    assert(list->data == &data3);
    assert(list->prev == NULL);

    // Remove last item
    list = list_remove(list, &data3);
    assert(list == NULL);

    printf("passed!\n");
}

void test_list_foreach() {
    printf("test_list_foreach...");

    List *list   = NULL;
    int   data[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        list = list_append(list, &data[i]);
    }

    printf("\n");
    printf("Expected output: 1 2 3 4 5\n");
    printf("  Actual output: ");
    list_foreach(list, print_int);

    list_free(list, NULL);
    printf("passed!\n");
}

void test_list_free_with_fn() {
    printf("test_list_free_with_fn...");

    List *list = NULL;

    // Allocate strings dynamically
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    char *str3 = strdup("Test");

    list = list_append(list, str1);
    list = list_append(list, str2);
    list = list_append(list, str3);

    // This should free all strings
    list_free(list, free_string);
    printf("passed!\n");
}

void test_remove_nonexistent() {
    printf("test_remove_nonexistent...");

    List *list = NULL;
    int   data = 42;

    list = list_append(list, &data);
    list = list_remove(list, (void *)0xDEADBEEF); // Some address that's not in list

    assert(list != NULL);
    assert(list->data == &data);

    list_free(list, NULL);
    printf("passed!\n");
}

// Test circular references (should not be circular)
void test_non_circular() {
    printf("test_non_circular...");

    List *list  = NULL;
    int   data1 = 1, data2 = 2;

    list = list_append(list, &data1);
    list = list_append(list, &data2);

    assert(list->next->next == NULL);
    assert(list->prev == NULL);

    list_free(list, NULL);
    printf("passed!\n");
}

int main() {
    test_append_to_empty();
    test_append_multiple();
    test_list_find();
    test_list_remove();
    test_list_foreach();
    test_list_free_with_fn();
    test_remove_nonexistent();
    test_non_circular();

    printf("All list tests passed successfully!\n");
    return 0;
}
