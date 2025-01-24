#include <stdio.h>
#include <string.h>

#include "sha-256.h"

int main(int argc, const char *argv[]) {
    char    shastring[SIZE_OF_SHA_256_HASH_STRING]  = "3e3f78c759feb24db09c48204f5923314727982c4bca981399ccf3fdf884fcaf";
    char    word[]                                  = "libdata";
    char    hashstring[SIZE_OF_SHA_256_HASH_STRING] = "";
    uint8_t hash[SIZE_OF_SHA_256_HASH];

    calc_sha_256(hash, "libdata", strlen("libdata"));
    hash_to_string(hashstring, hash);
    if (strcmp(shastring, hashstring) == 0) {
        printf("[OK] Hash Calculate is ok!\n");
    } else {
        printf("[ERR] Hash Calculate is wrong!\n");
    }

    int result = hash_check(word, shastring);
    if (result == 0) {
        printf("[OK] Check word hash is ok!\n");
    } else {
        printf("[ERR] Check word hash is wrong!\n");
    }

    return 0;
}
