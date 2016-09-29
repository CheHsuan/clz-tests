#include <stdint.h>
#include <stdio.h>
#include "clz.h"

uint8_t clz_recursive(uint32_t x)
{
    return x ? clz_recursive(x>>1) - 1 : 32;
}

uint8_t clz_binary_recursive(uint32_t x, int shift)
{
    if(x == 0)
        return 32;
    if(shift == 0)
        return 0;
    if(x <= (0xFFFFFFFF >> shift))
        return shift + clz_binary_recursive(x << shift, shift / 2);
    else
        return clz_binary_recursive(x, shift / 2);
}

uint8_t clz_iteration(uint32_t x)
{
    int count = 0;
    while(x != 0) {
        x = x >> 1;
        count++;
    }
    return 32 - count;
}

uint8_t clz_byteshift(uint32_t x) {
    if (x == 0) return 32;
    int n = 1;
    if ((x >> 16) == 0) { n += 16; x <<= 16; }
    if ((x >> 24) == 0) { n += 8; x <<= 8; }
    if ((x >> 28) == 0) { n += 4; x <<= 4; }
    if ((x >> 30) == 0) { n += 2; x <<= 2; }
    n = n - (x >> 31);
    return n;
}

uint8_t clz_binarysearch(uint32_t x) {
    if (x == 0) return 32;
    int n = 0;
    if (x <= 0x0000FFFF) { n += 16; x <<= 16; }
    if (x <= 0x00FFFFFF) { n += 8; x <<= 8; }
    if (x <= 0x0FFFFFFF) { n += 4; x <<= 4; }
    if (x <= 0x3FFFFFFF) { n += 2; x <<= 2; }
    if (x <= 0x7FFFFFFF) { n += 1; x <<= 1; }
    return n;
}

uint8_t clz_harley(uint32_t x)
{
    static uint8_t const Table[] = {
      0xFF, 0, 0xFF, 15, 0xFF, 1, 28, 0xFF,
      16, 0xFF, 0xFF, 0xFF, 2, 21, 29, 0xFF,
      0xFF, 0xFF, 19, 17, 10, 0xFF, 12, 0xFF,
      0xFF, 3, 0xFF, 6, 0xFF, 22, 30, 0xFF,
      14, 0xFF, 27, 0xFF, 0xFF, 0xFF, 20, 0xFF,
      18, 9, 11, 0xFF, 5, 0xFF, 0xFF, 13,
      26, 0xFF, 0xFF, 8, 0xFF, 4, 0xFF, 25,
      0xFF, 7, 24, 0xFF, 23, 0xFF, 31, 0xFF,
    };

    // Propagate leftmost 1-bit to the right
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);

    // x = x * 0x6EB14F9
    x = (x << 3) - x;   // Multiply by 7.
    x = (x << 8) - x;   // Multiply by 255.
    x = (x << 8) - x;   // Again. 
    x = (x << 8) - x;   // Again. 

    return Table[x >> 26];
}
