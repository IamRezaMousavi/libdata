#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>

#define PRINT_U128(x) printf("%16lx%16lx\n", (uint64_t)(x >> 64), (uint64_t)x)
#define s6_addr16     __in6_u.__u6_addr16

typedef unsigned __int128 uint128_t;

int main() {
    uint16_t a[8] = {0x1020, 0x3040, 0x5060, 0x7080, 0x90A0, 0xB0C0, 0xD0E0, 0xF00D};

    struct in6_addr addr;
    for (int i = 0; i < 8; i++) {
        addr.s6_addr16[i] = htons(a[i]);
    }
    char str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &addr, str, INET6_ADDRSTRLEN);
    printf("IPv6 Address: %s\n", str);

    uint128_t x = 0;
    for (int i = 0; i < 8; i++) {
        x = (x << 16) | ntohs(addr.s6_addr16[i]);
    }
    PRINT_U128(x);

    uint128_t num = ((uint128_t)0x1020304050607080ULL << 64) + 0x90A0B0C0D0E0F00DULL;
    PRINT_U128(num);

    return 0;
}
