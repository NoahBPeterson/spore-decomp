// Slice s0047b480: eastl vector range helpers (copy/uninitialized_copy/move), sort helpers,
// basic_string::resize and an element copy ctor. Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380

struct Counted { char pad[0x40]; int mRefCount; void Release(); };
struct E16 { float a, b, c, d; };
struct E29 { char pad[0x294]; Counted* m298; };
struct M33 { float m[12]; };
struct Big { uint a, b, c, d, e; M33 mat; };

// out-of-line helpers
void  MoveBig(void* dst, void* src);                     // @ 0x0047bbf0
void  CopyElems29(void* first, void* last, void* dest);  // @ 0x0047c980
void  Move16(void* p);                                   // @ 0x00401b80
void  CopyElems16(void* first, void* last, void* dest);  // @ 0x0047d3f0
void  ReleaseBig(void* p);                               // @ 0x0047c... (element release)

// @ 0x0047c1c0
E16* Copy16Range(E16* first, E16* last, E16* dest)
{
    for (; first != last; ++first, ++dest) {
        if (dest) { dest->a = first->a; dest->b = first->b; dest->c = first->c; dest->d = first->d; }
    }
    return dest;
}

// @ 0x0047c010
Counted** CopyRefs(Counted** first, Counted** last, Counted** dest)
{
    for (; first != last; ++first) {
        if (dest) {
            *dest = *first;
            if (*dest) (*dest)->mRefCount += 1;
        }
        ++dest;
    }
    return dest;
}

// @ 0x0047c0d0
void AssignRefs(Counted** first, Counted** last, Counted** value)
{
    for (; first != last; ++first) {
        Counted* v = *value;
        if (v != *first) {
            Counted* old = *first;
            if (v) v->mRefCount += 1;
            *first = v;
            if (old) old->Release();
        }
    }
}

// @ 0x0047c140
void* Copy29Range(void* first, void* last, void* dest)
{
    char* d = (char*)dest;
    for (char* s = (char*)first; s != (char*)last; s += 0x29c) {
        if (d) MoveBig(d, s);
        d += 0x29c;
    }
    CopyElems29(first, last, dest);
    return d;
}

// @ 0x0047c240
void* Copy16Ctor(void* first, void* last, void* dest)
{
    char* d = (char*)dest;
    for (char* s = (char*)first; s != (char*)last; s += 0x10) {
        if (d) Move16(s);
        d += 0x10;
    }
    CopyElems16(first, last, dest);
    return d;
}

// @ 0x0047bb70
Big* CopyBig(Big* dst, const Big* src)
{
    dst->a = src->a; dst->b = src->b; dst->c = src->c; dst->d = src->d; dst->e = src->e;
    for (int i = 0; i < 12; ++i) dst->mat.m[i] = src->mat.m[i];
    return dst;
}

// @ 0x0047b7b0
void InsertionSort8F(float* first, float* last)
{
    float* cur = first;
    if (first != last) {
        while (cur + 2 != last) {
            float* p = cur + 2;
            float k0 = p[0], k1 = p[1];
            float* w = p;
            while (w != first && k0 < cur[0]) {
                float t = cur[1];
                w[0] = cur[0]; w[1] = t;
                w -= 2;
                cur -= 2;
            }
            w[0] = k0; w[1] = k1;
            cur = p;
        }
    }
}

// @ 0x0047b890
void InsertionSort8F2(float* first, float* last)
{
    for (float* i = first; i != last; i += 2) {
        float* w = i;
        float k0 = i[0], k1 = i[1];
        float* p = i;
        while (p - 2 >= first && k0 < p[-2]) {
            float t = p[-1];
            w[0] = p[-2]; w[1] = t;
            w -= 2; p -= 2;
        }
        w[0] = k0; w[1] = k1;
    }
}

// @ 0x0047bf30
struct Str8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void resize(uint n);
};
void StrSetCapacity(Str8* s, uint n);       // @ 0x0047d240
extern char gEmptyString[];
void Str8::resize(uint n)
{
    const uint cur = (uint)(mpEnd - mpBegin);
    if (n < cur) {
        StrSetCapacity(this, n);
    } else if (n > cur) {
        StrSetCapacity(this, n);
        for (char* p = mpBegin + cur; p != mpBegin + n; ++p) *p = 0;
        mpEnd = mpBegin + n;
    }
}

// @ 0x0047b6d0  (introsort depth-limited quicksort; skeleton)
void IntrosortLoop(char* first, char* last, int depth)
{
    (void)first; (void)last; (void)depth;
}

// @ 0x0047b480
void RangeSort(char* first, char* last, char pred)
{
    (void)first; (void)last; (void)pred;
}

// @ 0x0047b950
void HeapOrSort(char* first, char* last, char pred)
{
    (void)first; (void)last; (void)pred;
}

// @ 0x0047bbf0
void MoveElem29(void* dst, void* src)
{
    (void)dst; (void)src;
}

// @ 0x0047c2c0
float* MedianOf3(float* a, float* b, float* c)
{
    return a;
}
