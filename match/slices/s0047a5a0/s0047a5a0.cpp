// Slice s0047a5a0: eastl::vector<T> insert(n,value) for Matrix44 and 16-byte (vtable) elements.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  FUN_00f47380(void* p);                                           // @ 0x00f47380

struct Matrix44 {
    float m[16];
    Matrix44() {}
    Matrix44(const Matrix44& o) { for (int i = 0; i < 16; ++i) m[i] = o.m[i]; }
};
struct P16 { uint a, b, c, d; };
struct VM44 { Matrix44* mpBegin; Matrix44* mpEnd; Matrix44* mpCapacity; void Insert(Matrix44* position, uint n, const Matrix44& value); };
struct V16 { P16* mpBegin; P16* mpEnd; P16* mpCapacity; void Insert(P16* position, uint n, const P16& value); };

// out-of-line helpers (relocations masked)
void  ConstructM44(void* dst, uint n, const void* v);          // @ 0x0047cbe0
void  ShiftM44(void* out, void* first, void* last, void* dest); // @ 0x0047cb60
void* CopyM44(const void* first, const void* last, void* dest); // @ 0x0047a9a0
void* UninitCopyM44(const void* first, const void* last, void* dest); // @ 0x0045dc00
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
void VM44::Insert(Matrix44* position, uint n, const Matrix44& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x40 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x40;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        // the empty allocator subobject is at this+0xc (0x0047a870: `lea eax,[edx+0xc]; push eax`)
        Matrix44* pNew = newSize ? (Matrix44*)EASTL_Allocate((char*)this + 0xc, newSize * 0x40, 4, 0) : 0;
        Matrix44* p = CopyM44Range(mpBegin, position, pNew);
        ConstructM44(p, n, &value);
        Matrix44* pNewEnd = CopyM44Range(position, mpEnd, p + n);
        // deallocate through the shared allocator, only when the block header dword is set
        // (0x0047a941: `cmp dword [eax-4],0 / je skip`, then call 0x00f47380)
        if (mpBegin && ((uint*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Matrix44 v = value;
        Matrix44* oldEnd = mpEnd;
        uint tail = (uint)((char*)oldEnd - (char*)position) / 0x40;
        if (n < tail) {
            // 0x0047cb60 writes its result pointer through its first argument (and returns it):
            // the original passes a stack local (`lea edx,[ebp-0x64]`, the discarded return slot),
            // never `position` - writing the helper's out value into the element array corrupted
            // the vector contents the caller passed in (memory pool mismatch at position + n*0x40).
            Matrix44* shifted;
            ShiftM44(&shifted, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            Matrix44* p = mpEnd - n;
            while (p != position) { --p; p[n] = *p; }
            for (Matrix44* w = position; w != position + n; ++w) *w = v;
        } else {
            ConstructM44(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            // the n >= tail path uses the generic uninitialized_copy (0x0045dc00), not vec::Copy
            UninitCopyM44(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            // bound is the old end (`cmp ecx,[ebp-0x4]` at 0x0047a7db), not position + n:
            // only the elements that were already present get overwritten with the value
            for (Matrix44* w = position; w != oldEnd; ++w) *w = v;
        }
    }
}

// @ 0x0047aa40
void V16::Insert(P16* position, uint n, const P16& value)
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

// ---------------------------------------------------------------------------
// 0x0047b3d0: uninitialized copy of a run of 0x14-byte POD elements. Returns the
// end of the destination run. The trailing no-op loop is what the original emits.
// ---------------------------------------------------------------------------
struct Elem20
{
    uint32_t w0, w1, w2, w3, w4;
    Elem20& operator=(const Elem20& o)
    {
        w0 = o.w0; w1 = o.w1; w2 = o.w2; w3 = o.w3; w4 = o.w4;
        return *this;
    }
};

// @ 0x0047b3d0
Elem20* Copy20Range(Elem20* first, Elem20* last, Elem20* dest)
{
    Elem20* d = dest;
    Elem20* s = first;
    while (s != last) {
        if (d) *d = *s;
        ++s;
        ++d;
    }
    for (Elem20* q = first, * r = dest; q != last; ++q, ++r) {}
    return d;
}

// ---------------------------------------------------------------------------
// 0x0047ae60: eastl::vector<Elem32>::insert(position, n, value). Elem32 is a
// 0x20-byte record (four words + a 0x10-byte ref-counted Handle) whose copy
// constructor and assignment operator live out of line (0x00423080 / 0x00424f10).
// ---------------------------------------------------------------------------
struct Elem32
{
    uint32_t w0, w1, w2, w3;
    uint32_t h0, h1, h2, h3;                 // 0x10-byte Handle
    Elem32(const Elem32& src);               // 0x00423080
    Elem32& operator=(const Elem32& src);    // 0x00424f10
};

struct Vec32Alloc { uint32_t mPad; };        // empty EASTL allocator, occupies 4 bytes

void    Construct32(Elem32* dst, uint n, const Elem32& value);            // 0x0047cd20
void    ShiftUp32(void** out, Elem32* first, Elem32* last, Elem32* dest); // 0x0047b290
Elem32* UninitMove32(Elem32* first, Elem32* last, Elem32* dest);          // 0x0042a730

struct Vec32
{
    Elem32*    mpBegin;
    Elem32*    mpEnd;
    Elem32*    mpCapacity;
    Vec32Alloc mAllocator;

    void DoInsertValues(Elem32* position, uint n, const Elem32& value);
};

// @ 0x0047ae60
void Vec32::DoInsertValues(Elem32* position, uint n, const Elem32& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x20 < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x20;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        Elem32* pNew = newSize ? (Elem32*)EASTL_Allocate(&mAllocator, newSize * 0x20, 4, 0) : 0;
        Elem32* p = UninitMove32(mpBegin, position, pNew);
        Construct32(p, n, value);
        p = UninitMove32(position, mpEnd, p + n);
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
        mpBegin = pNew;
        mpEnd = p;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Elem32 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x20;
        Elem32* oldEnd = mpEnd;
        if (n < tail) {
            Elem32* out;
            ShiftUp32((void**)&out, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            Elem32* s = oldEnd;
            Elem32* d = oldEnd - n;
            while (d != position) { d -= 1; s -= 1; *s = *d; }
            for (Elem32* w = position; w != position + n; ++w) *w = v;
        } else {
            Elem32* out;
            Construct32(mpEnd, n - tail, v);
            mpEnd += n - tail;
            ShiftUp32((void**)&out, position, oldEnd, mpEnd);
            mpEnd += tail;
            for (Elem32* w = position; w != oldEnd; ++w) *w = v;
        }
    }
}
