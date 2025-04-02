#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha-256.h"

// Helper function to print hash as hex
void print_hash(const uint8_t hash[SIZE_OF_SHA_256_HASH]) {
    for (int i = 0; i < SIZE_OF_SHA_256_HASH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void test_empty_string() {
    printf("test_empty_string...");

    const char *input = "";
    uint8_t     hash[SIZE_OF_SHA_256_HASH];
    char        hash_str[SIZE_OF_SHA_256_HASH_STRING];

    // Known SHA-256 hash of empty string
    const uint8_t expected_hash[SIZE_OF_SHA_256_HASH]
        = {0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
           0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c, 0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55};

    calc_sha_256(hash, input, strlen(input));
    assert(memcmp(hash, expected_hash, SIZE_OF_SHA_256_HASH) == 0);

    hash_to_string(hash_str, hash);
    assert(strcmp(hash_str, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") == 0);

    printf("passed!\n");
}

void test_simple_string() {
    printf("test_simple_string...");

    const char *input = "hello world";
    uint8_t     hash[SIZE_OF_SHA_256_HASH];
    char        hash_str[SIZE_OF_SHA_256_HASH_STRING];

    // Known SHA-256 hash of "hello world"
    const uint8_t expected_hash[SIZE_OF_SHA_256_HASH]
        = {0xb9, 0x4d, 0x27, 0xb9, 0x93, 0x4d, 0x3e, 0x08, 0xa5, 0x2e, 0x52, 0xd7, 0xda, 0x7d, 0xab, 0xfa,
           0xc4, 0x84, 0xef, 0xe3, 0x7a, 0x53, 0x80, 0xee, 0x90, 0x88, 0xf7, 0xac, 0xe2, 0xef, 0xcd, 0xe9};

    calc_sha_256(hash, input, strlen(input));
    assert(memcmp(hash, expected_hash, SIZE_OF_SHA_256_HASH) == 0);

    hash_to_string(hash_str, hash);
    assert(strcmp(hash_str, "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9") == 0);

    printf("passed!\n");
}

void test_binary_data() {
    printf("test_binary_data...");

    uint8_t binary_data[3] = {0x01, 0x02, 0x03};
    uint8_t hash[SIZE_OF_SHA_256_HASH];
    char    hash_str[SIZE_OF_SHA_256_HASH_STRING];

    calc_sha_256(hash, binary_data, sizeof(binary_data));

    // Convert to string and verify against known good value
    hash_to_string(hash_str, hash);
    assert(strcmp(hash_str, "039058c6f2c0cb492c533b0a4d14ef77cc0f78abccced5287d84a1a2011cfb81") == 0);

    printf("passed!\n");
}

void test_hash_to_string() {
    printf("test_hash_to_string...");

    uint8_t hash[SIZE_OF_SHA_256_HASH] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
                                          0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f, 0x70, 0x81, 0x92, 0xa3, 0xb4, 0xc5, 0xd6, 0xe7, 0xf8, 0x09};
    char    hash_str[SIZE_OF_SHA_256_HASH_STRING];

    hash_to_string(hash_str, hash);
    assert(strcmp(hash_str, "aabbccddeeff001122334455667788991a2b3c4d5e6f708192a3b4c5d6e7f809") == 0);

    printf("passed!\n");
}

void test_hash_check() {
    printf("test_hash_check...");

    const char *input        = "test string";
    const char *correct_hash = "d5579c46dfcc7f18207013e65b44e4cb4e2c2298f4ac457ba8f82743f31e930b";
    const char *wrong_hash   = "0000000000000000000000000000000000000000000000000000000000000000";

    assert(hash_check(input, correct_hash) == 1);
    assert(hash_check(input, wrong_hash) == 0);

    // Test with empty strings
    assert(hash_check("", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") == 1);
    assert(hash_check("", wrong_hash) == 0);

    printf("passed!\n");
}

void test_large_input() {
    printf("test_large_input...");

    // Create a 1MB buffer filled with 'a'
    const size_t size        = 1024 * 1024;
    char        *large_input = malloc(size);
    memset(large_input, 'a', size);

    uint8_t hash[SIZE_OF_SHA_256_HASH];
    char    hash_str[SIZE_OF_SHA_256_HASH_STRING];

    calc_sha_256(hash, large_input, size);
    hash_to_string(hash_str, hash);

    // Known SHA-256 hash of 1MB of 'a's
    assert(strcmp(hash_str, "9bc1b2a288b26af7257a36277ae3816a7d4f16e89c1e7e77d0a5c48bad62b360") == 0);

    free(large_input);
    printf("passed!\n");
}

int main() {
    test_empty_string();
    test_simple_string();
    test_binary_data();
    test_hash_to_string();
    test_hash_check();
    test_large_input();

    printf("All SHA-256 tests passed successfully!\n");
    return 0;
}
