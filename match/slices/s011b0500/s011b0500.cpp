#include "types.h"

// Square of a 256-bit little-endian integer (8 x 32-bit words) into a 512-bit
// result (16 words). The original is a fully unrolled column-wise (comba)
// squaring built from 16x16-bit partial products; this is the same arithmetic.
// @ 0x011b0500
void __cdecl lib_cblock_Square8(uint32_t* out, const uint32_t* a)
{
    uint32_t r[16];
    int i, j;
    for (i = 0; i < 16; ++i)
        r[i] = 0;
    for (i = 0; i < 8; ++i) {
        uint32_t carry = 0;
        for (j = i + 1; j < 8; ++j) {
            uint64_t t = (uint64_t)a[i] * a[j] + r[i + j] + carry;
            r[i + j] = (uint32_t)t;
            carry = (uint32_t)(t >> 32);
        }
        r[i + 8] = carry;
    }
    // double the cross terms
    uint32_t top = 0;
    for (i = 0; i < 16; ++i) {
        uint32_t v = r[i];
        r[i] = (v << 1) | top;
        top = v >> 31;
    }
    // add the squares
    uint32_t carry = 0;
    for (i = 0; i < 8; ++i) {
        uint64_t sq = (uint64_t)a[i] * a[i];
        uint64_t lo = (uint64_t)r[2 * i] + (uint32_t)sq + carry;
        r[2 * i] = (uint32_t)lo;
        uint64_t hi = (uint64_t)r[2 * i + 1] + (uint32_t)(sq >> 32) + (uint32_t)(lo >> 32);
        r[2 * i + 1] = (uint32_t)hi;
        carry = (uint32_t)(hi >> 32);
    }
    for (i = 0; i < 16; ++i)
        out[i] = r[i];
}
