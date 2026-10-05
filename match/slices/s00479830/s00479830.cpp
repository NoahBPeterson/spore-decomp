// Slice s00479830: eastl::vector<T> insert(n,value) for 8-byte and 16-byte elements plus range
// copy helpers. Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0

struct P8  { uint a, b; };
struct P16 { uint a, b, c, d; };

// out-of-line helpers
void  Construct8 (void* dst, uint n, const void* v);          // @ 0x0047ca70
void* Copy8Range (const void* first, const void* last, void* dest);  // @ 0x00476290
void  Shift8Range(void* out, void* first, void* last, void* dest);   // @ 0x00479c00
void  Construct16(void* dst, uint n, const void* v);          // @ 0x0052c8f0
void* Copy16Range(const void* first, const void* last, void* dest);
void  Shift16Range(void* out, void* first, void* last, void* dest);  // @ 0x00541450

// @ 0x00479c00
void Shift8Out(P8** out, P8* first, P8* last, P8* dest)
{
    P8* d = dest;
    for (; first != last; ++first) {
        if (d) { *d = *first; }
        ++d;
    }
    *out = d;
}

// @ 0x00479830
void Insert8(P8*& mpBegin, P8*& mpEnd, P8*& mpCapacity, P8* position, uint n, const P8& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 8 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 8;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P8* pNew = newSize ? (P8*)EASTL_Allocate(mpCapacity, newSize * 8, 4, 0) : 0;
        P8* p = (P8*)Copy8Range(mpBegin, position, pNew);
        Construct8(p, n, &value);
        P8* pNewEnd = (P8*)Copy8Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_Allocate(mpBegin, 0, 0, 0);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P8 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 8;
        if (n < tail) {
            Shift8Range(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P8* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P8* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct8(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy8Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P8* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x00479c80
void Insert8b(P8*& mpBegin, P8*& mpEnd, P8*& mpCapacity, P8* position, uint n, const P8& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 8 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 8;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        P8* pNew = newSize ? (P8*)EASTL_Allocate(mpCapacity, newSize * 8, 2, 0) : 0;
        P8* p = (P8*)Copy8Range(mpBegin, position, pNew);
        Construct16(p, n, &value);
        P8* pNewEnd = (P8*)Copy8Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_Allocate(mpBegin, 0, 0, 0);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        P8 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 8;
        if (n < tail) {
            Shift16Range(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P8* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P8* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct16(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy16Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P8* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047a040
void Insert16(P16*& mpBegin, P16*& mpEnd, P16*& mpCapacity, P16* position, uint n, const P16& value)
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
            Shift16Range(position, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            P16* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (P16* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct16(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Copy16Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (P16* w = position; w != position + n; ++w) *w = v;
        }
    }
}

// @ 0x0047a500  (eastl::uninitialized_copy for a non-trivial 16-byte element)
struct Elem16Iter { P16* mIterator; Elem16Iter(P16* p) : mIterator(p) {} };
struct false_type2 { false_type2() {} };
Elem16Iter UninitializedCopy_Elem16(Elem16Iter first, Elem16Iter last, Elem16Iter dest, false_type2)
{
    P16* p = dest.mIterator;
    for (P16* s = first.mIterator; s != last.mIterator; ++s, ++p) {
        if (p) *p = *s;
    }
    for (P16* q = first.mIterator; q != last.mIterator; ++q) {}
    return Elem16Iter(p);
}
