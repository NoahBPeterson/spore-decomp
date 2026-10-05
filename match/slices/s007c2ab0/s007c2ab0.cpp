// Slice s007c2ab0 — DXT/GIF conversion routines plus a 64-byte aligned struct copy.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// @ 0x007c3b70  64-byte (4x __m128) aligned copy, this=dst, arg=src, ret 4
// ---------------------------------------------------------------------------
struct Mat4 {
    __m128 a, b, c, d;                 // 4 x 16 bytes
    void CopyMat4(const Mat4* src);
};

void Mat4::CopyMat4(const Mat4* src)
{
    a = src->a;
    b = src->b;
    c = src->c;
    d = src->d;
}

// ---------------------------------------------------------------------------
// remaining routines (skeletons)
// ---------------------------------------------------------------------------
void ConvertDXT3ToARGB8888(void* a) { (void)a; }
void FUN_007c2ee0(void* a) { (void)a; }
void WriteAnimatedCSAGIF(void* a) { (void)a; }
void FUN_007c3910() {}
void FUN_007c3af0(void* a) { (void)a; }
