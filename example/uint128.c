#include <stdint.h>
#include <stdio.h>

#define PRINT_U128(x) printf("%lx%lx\n", (uint64_t)(x >> 64), (uint64_t)x)

int main() {
    uint16_t a[8] = {0x1020, 0x3040, 0x5060, 0x7080, 0x90A0, 0xB0C0, 0xD0E0, 0xF00D};

    unsigned __int128 x = 0;
    for (int i = 0; i < 8; i++) {
        x = (x << 16) | a[i];
    }
    PRINT_U128(x);

    unsigned __int128 num = ((unsigned __int128)0x1020304050607080ULL << 64) + 0x90A0B0C0D0E0F00DULL;
    PRINT_U128(num);

    return 0;
}
