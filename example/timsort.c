#include <stdio.h>

#include "timsort.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void print_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 21, 7, 23, 19, 10, 15, 3, 12, 4};

    int n = ARRAY_SIZE(arr);

    printf("origin array:\n");
    print_array(arr, n);

    timsort(arr, n);

    printf("sorted array:\n");
    print_array(arr, n);

    return 0;
}
