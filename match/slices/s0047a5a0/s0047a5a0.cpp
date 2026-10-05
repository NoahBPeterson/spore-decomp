// Slice s0047a5a0: eastl::vector<T> insert(n,value) for Matrix44 and 16-byte (vtable) elements.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0

struct Matrix44 {
    float m[16];
    Matrix44() {}
    Matrix44(const Matrix44& o) { for (int i = 0; i < 16; ++i) m[i] = o.m[i]; }
};
struct P16 { uint a, b, c, d; };

// out-of-line helpers (relocations masked)
void  ConstructM44(void* dst, uint n, const void* v);          // @ 0x0047cbe0
void  ShiftM44(void* out, void* first, void* last, void* dest); // @ 0x0047cb60
void* CopyM44(const void* first, const void* last, void* dest); // @ 0x0047a9a0
void  Construct16(void* dst, uint n, const void* v);            // @ 0x0047ccc0
void  Shift16(void* out, void* first, void* last, void* dest);  // @ 0x0047cc40
void* Copy16(const void* first, const void* last, void* dest);  // @ 0x0047c240

// @ 0x0047a9a0
Matrix44* CopyM44Range(Matrix44* first, Matrix44* last, Matrix44* dest)
{
    Matrix44* d = dest;
    for (Matrix44* s = first; s != last; s += 1) {
        if (d) *d = *s;
        d += 1;
    }
    for (Matrix44* q = first; q != last; q += 1) {}
    return d;
}

// @ 0x0047a5a0
void InsertM44(Matrix44*& mpBegin, Matrix44*& mpEnd, Matrix44*& mpCapacity,
               Matrix44* position, uint n, const Matrix44& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x40 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x40;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        Matrix44* pNew = newSize ? (Matrix44*)EASTL_Allocate(mpCapacity, newSize * 0x40, 4, 0) : 0;
        Matrix44* p = CopyM44Range(mpBegin, position, pNew);
        ConstructM44(p, n, &value);
        Matrix44* pNewEnd = CopyM44Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_Allocate(mpBegin, 0, 0, 0);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Matrix44 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x40;
        if (n < tail) {
            ShiftM44(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            Matrix44* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (Matrix44* w = position; w != position + n; ++w) *w = v;
        } else {
            ConstructM44(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            CopyM44(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (Matrix44* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047aa40
void Insert16(P16*& mpBegin, P16*& mpEnd, P16*& mpCapacity,
              P16* position, uint n, const P16& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x10 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x10;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P16* pNew = newSize ? (P16*)EASTL_Allocate(mpCapacity, newSize * 0x10, 4, 0) : 0;
        P16* p = pNew;
        P16* pNewEnd = pNew + oldSize + n;
        (void)p;
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P16 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x10;
        if (n < tail) {
            Shift16(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P16* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P16* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct16(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy16(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P16* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047ae60
void Insert16b(P16*& mpBegin, P16*& mpEnd, P16*& mpCapacity,
               P16* position, uint n, const P16& value)
{
    Insert16(mpBegin, mpEnd, mpCapacity, position, n, value);
}

// @ 0x0047b3d0
void InsertM44b(Matrix44*& mpBegin, Matrix44*& mpEnd, Matrix44*& mpCapacity,
                Matrix44* position, uint n, const Matrix44& value)
{
    InsertM44(mpBegin, mpEnd, mpCapacity, position, n, value);
}
