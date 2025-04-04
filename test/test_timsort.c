#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <libdata/sorting/timsort.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void print_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int is_sorted(const int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }
    return 1;
}

// Test empty array
void test_empty_array() {
    printf("test_empty_array...");

    int arr[] = {};
    timsort(arr, 0);
    assert(is_sorted(arr, 0));
    printf("passed!\n");
}

void test_single_element() {
    printf("test_single_element...");

    int arr[] = {42};
    timsort(arr, 1);
    assert(is_sorted(arr, 1));
    assert(arr[0] == 42);
    printf("passed!\n");
}

void test_already_sorted() {
    printf("test_already_sorted...");

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n     = sizeof(arr) / sizeof(arr[0]);
    int copy[n];
    memcpy(copy, arr, sizeof(arr));

    timsort(arr, n);
    assert(is_sorted(arr, n));
    assert(memcmp(arr, copy, sizeof(arr)) == 0);
    printf("passed!\n");
}

void test_reverse_sorted() {
    printf("test_reverse_sorted...");

    int arr[]      = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n          = sizeof(arr) / sizeof(arr[0]);

    timsort(arr, n);
    assert(is_sorted(arr, n));
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("passed!\n");
}

void test_with_duplicates() {
    printf("test_with_duplicates...");

    int arr[]      = {5, 2, 8, 5, 2, 3, 5, 1, 8};
    int expected[] = {1, 2, 2, 3, 5, 5, 5, 8, 8};
    int n          = sizeof(arr) / sizeof(arr[0]);

    timsort(arr, n);
    assert(is_sorted(arr, n));
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("passed!\n");
}

void test_random_array() {
    printf("test_random_array...");

    int n = 1000;
    int arr[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }

    timsort(arr, n);
    assert(is_sorted(arr, n));
    printf("passed!\n");
}

void test_all_identical() {
    printf("test_all_identical...");

    int arr[] = {7, 7, 7, 7, 7, 7, 7, 7};
    int n     = sizeof(arr) / sizeof(arr[0]);

    timsort(arr, n);
    assert(is_sorted(arr, n));
    for (int i = 0; i < n; i++) {
        assert(arr[i] == 7);
    }
    printf("passed!\n");
}

void test_stability() {
    typedef struct {
        int key;
        int value;
    } Item;

    // Dummy items with same key but different values
    Item items[] = {
        {5, 1},
        {3, 1},
        {5, 2},
        {2, 1},
        {5, 3},
        {3, 2}
    };
    int n = sizeof(items) / sizeof(items[0]);

    // Stable sort should maintain order of equal keys
    // Note: This requires modifying timsort to use a comparator function
    // and work with generic types (not implemented in this test)

    printf("Note: Stability test requires generic implementation\n");
}

void test_large_array() {
    printf("test_large_array...");

    int  n   = 1000000; // 1 million elements
    int *arr = malloc(n * sizeof(int));
    assert(arr != NULL);

    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }

    timsort(arr, n);
    assert(is_sorted(arr, n));

    free(arr);
    printf("passed!\n");
}

int main() {
    test_empty_array();
    test_single_element();
    test_already_sorted();
    test_reverse_sorted();
    test_with_duplicates();
    test_random_array();
    test_all_identical();
    test_stability();
    test_large_array();

    printf("All Timsort tests passed successfully!\n");
    return 0;
}
