// slice s009dfc40 -- eastl::vector<T> helper instantiations used by the retail
// nSPCreatureAnim / gait subsystem of SporeApp.exe (32-bit, MSVC 2008 SP1 /O2).
//
//   @ 0x009dfc40  container destructor          (vector of 0x40 at +0x20, buffer at +0x0c)
//   @ 0x009dfc90  container destructor          (vector of 0x40 at +0x13c, buffers +0xd4/.e8/.fc/.128)
//   @ 0x009dfd30  container destructor          (scalars +0xac/+0xb0, vector of 0x40 at +0x28, buffer +0x14)
//   @ 0x009dfda0  eastl::vector<0x44,...>::operator=
//   @ 0x009dffe0  eastl::vector<0x1c,...>::operator=
//   @ 0x009e0110  eastl::vector<0x44,...>::DoInsertValue
//   @ 0x009e0230  eastl::vector<0x58,...>::DoInsertValue
//   @ 0x009e0330  eastl::vector<0x1c,...>::DoInsertValue
//   @ 0x009e0480  eastl::vector<0x0c,...>::erase          (rw::math::fpu::Vector3Template<float,0>)
//   @ 0x009e04e0  eastl::vector<0x0c,...>::DoInsertValue  (rw::math::fpu::Vector3Template<float,0>)
//   @ 0x009e06a0  eastl::vector<0x0c,...>::DoInsertValue  ({float,float,bool})
//   @ 0x009e07d0  destruct-range (returns end iterator)   for the 0xa4-stride entry
//   @ 0x009e0940  eastl::vector<0x44,...>::clear
//   @ 0x009e0980  eastl::vector<0x58,...>::clear
//   @ 0x009e09c0  eastl::vector<0x1c,...>::clear
//   @ 0x009e0a00  eastl::vector<0x0c,...>::resize(n, value)
//   @ 0x009e0b20  eastl::vector<0x0c,...>::insert(pos, value)
//   @ 0x009e0b90  destruct-range (count form)             for the 0xa4-stride entry
//   @ 0x009e0cd0  eastl::copy (forward)                   for the 0x40-stride entry
//   @ 0x009e0d30  eastl::copy_backward                    for the 0x40-stride entry
//
// Build: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

// ------------------------------------------------------------------ external code

void  operator delete[](void* p);                                     // 0x00f47380
void* operator_new(unsigned size, const char* name, int flags, int align,
                   const char* file, int line);                       // 0x00f473a0

extern const char g_alloc_name_anim_gait[];                           // 0x014479f4 "Anim/gait/untagged"
extern const char g_alloc_file_eastl[];                               // 0x013ebb38 ".../EASTL/allocator.h"

// ------------------------------------------------------------------ element types (forward)

struct Elem0C;      // 0x0c
struct Elem0CS;     // 0x0c
struct Elem1C;      // 0x1c
struct Elem14;      // 0x14
struct Elem44;      // 0x44
struct Elem58;      // 0x58
struct Elem40;      // 0x40
struct ElemA4;      // 0xa4

// ------------------------------------------------------------------ external primitives

void  CopyA(Elem44* first, Elem44* last, Elem44* result);             // 0x009dc230
void  CopyB(Elem58* first, Elem58* last, Elem58* result);             // 0x009dc270
void  CopyC(Elem1C* first, Elem1C* last, Elem1C* result);             // 0x009dc2b0
Elem0CS* Copy0CS(Elem0CS* first, Elem0CS* last, Elem0CS* result);     // 0x009dc300

void  CopyBackA(Elem44* first, Elem44* last, Elem44* result);         // 0x009dc340
void  CopyBackB(Elem58* first, Elem58* last, Elem58* result);         // 0x009dc380
void  CopyBackC(Elem1C* first, Elem1C* last, Elem1C* result);         // 0x009dc3c0

Elem44* UninitCopyA(Elem44* first, Elem44* last, Elem44* result);     // 0x009dc0f0
Elem58* UninitCopyB(Elem58* first, Elem58* last, Elem58* result);     // 0x009dc160
Elem1C* UninitCopyC(Elem1C* first, Elem1C* last, Elem1C* result);     // 0x009dc1d0

void UninitCopyBackA(void** out, Elem44* first, Elem44* last, Elem44* dstEnd, Elem44* dst);  // 0x009dd530
void UninitCopyBackB(void** out, Elem58* first, Elem58* last, Elem58* dstEnd, Elem58* dst);  // 0x009dd5b0
void UninitCopyBackC(void** out, Elem1C* first, Elem1C* last, Elem1C* dstEnd, Elem1C* dst);  // 0x009dd630

Elem0C* Copy0C(Elem0C* first, Elem0C* last, Elem0C* result);          // 0x00a11310
void*   Fill0C(Elem0C* first, Elem0C* last, const Elem0C* value);     // 0x00a177f0
void*   FillN0C(Elem0C* first, uint32 n, const Elem0C* value);        // 0x006e5760
void*   FillN0Cb(Elem0C* first, uint32 n, const Elem0C* value);       // 0x00cca0e0

// ------------------------------------------------------------------ element definitions

struct Elem0C {                                                       // size 0x0c
    float x, y, z;
};

struct Elem0CS {                                                      // size 0x0c
    float a, b;
    uint8 c;
};

struct IdBase {                                                       // the +0x04 subobject of Elem1C
    int id;
};

// The retail class is polymorphic itself but inherits a plain (non-polymorphic) IdBase,
// so MSVC lays down the vfptr first and the base subobject at +0x04.
struct Elem1C : IdBase {                                              // size 0x1c
    virtual void _never_called();
    float  f08;                        // +0x08
    uint32 f0c, f10, f14, f18;         // +0x0c .. +0x1c
    void    CopyFrom(const Elem1C& o); // 0x009dbed0 ret 4
    Elem1C& operator=(const Elem1C& o)
    {
        id  = ((IdBase*)&o)->id;
        f08 = o.f08;
        f0c = o.f0c;
        f10 = o.f10;
        f14 = o.f14;
        f18 = o.f18;
        return *this;
    }
};

struct Elem14 {                                                       // size 0x14 (opaque here)
    uint32 w[5];
};

struct Elem44 {                                                       // size 0x44
    uint32 w[0x11];
    void    CopyFrom(const Elem44& o);      // 0x009dbe30 ret 4 (copy-constructs *this)
    Elem44& operator=(const Elem44& o);     // 0x009dbfd0 ret 4
};

struct Elem58 {                                                       // size 0x58
    uint32 w[0x16];
    void    CopyFrom(const Elem58& o);      // 0x009dbe80 ret 4
    Elem58& operator=(const Elem58& o);     // 0x009dc050 ret 4
};

// ------------------------------------------------------------------ vector types

struct Vec44 {                                                          // element 0x44
    Elem44* mpBegin; Elem44* mpEnd; Elem44* mpCapacity; uint32 mPad[2];
    Vec44& operator=(const Vec44& x);                                  // 0x009dfda0 ret 4
    void   DoInsertValue(Elem44* position, const Elem44& value);       // 0x009e0110 ret 8
    void   clear();                                                    // 0x009e0940
    Elem44* DoAllocate(uint32 n, Elem44* first, Elem44* last);         // 0x009df6e0 ret 0xc
};

struct Vec58 {                                                          // element 0x58
    Elem58* mpBegin; Elem58* mpEnd; Elem58* mpCapacity; uint32 mPad[2];
    void   DoInsertValue(Elem58* position, const Elem58& value);       // 0x009e0230 ret 8
    void   clear();                                                    // 0x009e0980
    Elem58* DoAllocate(uint32 n, Elem58* first, Elem58* last);         // 0x009df740 ret 0xc
};

struct Vec1C {                                                          // element 0x1c
    Elem1C* mpBegin; Elem1C* mpEnd; Elem1C* mpCapacity; uint32 mPad[2];
    Vec1C& operator=(const Vec1C& x);                                  // 0x009dffe0 ret 4
    void   DoInsertValue(Elem1C* position, const Elem1C& value);       // 0x009e0330 ret 8
    void   clear();                                                    // 0x009e09c0
    Elem1C* DoAllocate(uint32 n, Elem1C* first, Elem1C* last);         // 0x009df7a0 ret 0xc
};

struct Vec14 {                                                          // element 0x14
    Elem14* mpBegin; Elem14* mpEnd; Elem14* mpCapacity; uint32 mPad[2];
    Vec14& operator=(const Vec14& x);                                  // 0x009dfec0 ret 4
};

struct Elem40 {                                                         // size 0x40
    uint32 id;                         // +0x00
    Vec44  v04;                        // +0x04
    Vec14  v18;                        // +0x18
    Vec1C  v2c;                        // +0x2c
    Elem40& operator=(const Elem40& o)
    {
        if (this != &o) {
            id = o.id;
            v04 = o.v04;
            v18 = o.v18;
            v2c = o.v2c;
        }
        return *this;
    }
};

struct Vec40 {                                                          // element 0x40
    Elem40* mpBegin; Elem40* mpEnd; Elem40* mpCapacity; uint32 mPad[2];
    void DestroyRange(Elem40* first, Elem40* last);                    // 0x009de770 ret 8
};

struct Vec0C {                                                          // element 0x0c
    Elem0C* mpBegin; Elem0C* mpEnd; Elem0C* mpCapacity; uint32 mPad[2];
    Elem0C* erase(Elem0C* first, Elem0C* last);                        // 0x009e0480 ret 8
    void    DoInsertValue(Elem0C* position, const Elem0C& value);      // 0x009e04e0 ret 8
    void    resize(uint32 n, const Elem0C& value);                     // 0x009e0a00 ret 8
    void    Construct(uint32 n, const Elem0C* value, void* alloc);     // 0x009df8b0 ret 0xc
    void    Swap(Vec0C& o);                                            // 0x009e0610 ret 4
};

struct Vec0CS {                                                         // element 0x0c
    Elem0CS* mpBegin; Elem0CS* mpEnd; Elem0CS* mpCapacity; uint32 mPad[2];
    void     DoInsertValue(Elem0CS* position, const Elem0CS& value);   // 0x009e06a0 ret 8
    Elem0CS* insert(Elem0CS* position, const Elem0CS& value);          // 0x009e0b20 ret 8
};

struct ElemA4 {                                                         // size 0xa4
    uint32 f00[4];                     // +0x00
    Vec40  v10;                        // +0x10  (items)
    Vec40  v24;                        // +0x24  (gaits)
    uint32 f38[0x1b];                  // +0x38 .. +0xa4
};

// ------------------------------------------------------------------ container layouts

struct AnimA {                          // destructor @ 0x009dfc40
    uint32 pad_000[3];                 // +0x00
    void*  p0c;                        // +0x0c
    uint32 pad_010[4];                 // +0x10
    Vec40  v20;                        // +0x20
    ~AnimA();
};

struct AnimB {                          // destructor @ 0x009dfc90
    uint32 pad_000[0x35];              // +0x00 .. +0xd4
    void*  p0d4;                       // +0x0d4
    uint32 pad_0d8[4];                 // +0x0d8
    void*  p0e8;                       // +0x0e8
    uint32 pad_0ec[4];                 // +0x0ec
    void*  p0fc;                       // +0x0fc
    uint32 pad_100[0x0a];              // +0x100
    void*  p128;                       // +0x128
    uint32 pad_12c[4];                 // +0x12c
    Vec40  v13c;                       // +0x13c
    ~AnimB();
};

struct AnimC {                          // destructor @ 0x009dfd30
    uint32 pad_000[5];                 // +0x00
    void*  p014;                       // +0x14
    uint32 pad_018[4];                 // +0x18
    Vec40  v28;                        // +0x28
    uint32 pad_03c[0x1c];              // +0x3c .. +0xac
    void*  p0ac;                       // +0xac
    void*  p0b0;                       // +0xb0
    ~AnimC();
};

// ------------------------------------------------------------------ @ 0x009dfc40

// @ 0x009dfc40
AnimA::~AnimA()
{
    v20.DestroyRange(v20.mpBegin, v20.mpEnd);
    if (v20.mpBegin && ((int*)v20.mpBegin)[-1] != 0)
        operator delete[](v20.mpBegin);
    if (p0c && ((int*)p0c)[-1] != 0)
        operator delete[](p0c);
}

// ------------------------------------------------------------------ @ 0x009dfc90

// @ 0x009dfc90
AnimB::~AnimB()
{
    v13c.DestroyRange(v13c.mpBegin, v13c.mpEnd);
    if (v13c.mpBegin && ((int*)v13c.mpBegin)[-1] != 0)
        operator delete[](v13c.mpBegin);
    if (p128 && ((int*)p128)[-1] != 0)
        operator delete[](p128);
    if (p0fc && ((int*)p0fc)[-1] != 0)
        operator delete[](p0fc);
    if (p0e8 && ((int*)p0e8)[-1] != 0)
        operator delete[](p0e8);
    if (p0d4 && ((int*)p0d4)[-1] != 0)
        operator delete[](p0d4);
}

// ------------------------------------------------------------------ @ 0x009dfd30

// @ 0x009dfd30
AnimC::~AnimC()
{
    if (p0ac != 0)
        p0ac = 0;
    if (p0b0 != 0)
        p0b0 = 0;
    Vec40* v = &v28;
    v->DestroyRange(v->mpBegin, v->mpEnd);
    if (v->mpBegin && ((int*)v->mpBegin)[-1] != 0)
        operator delete[](v->mpBegin);
    if (p014 && ((int*)p014)[-1] != 0)
        operator delete[](p014);
}

// ------------------------------------------------------------------ @ 0x009dfda0

// @ 0x009dfda0
Vec44& Vec44::operator=(const Vec44& x)
{
    if (this != &x) {
        uint32 n = (uint32)(x.mpEnd - x.mpBegin);
        if (n > (uint32)(mpCapacity - mpBegin)) {
            Elem44* p = DoAllocate(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                operator delete[](mpBegin);
            mpBegin = p;
            mpCapacity = p + n;
        } else {
            uint32 s = (uint32)(mpEnd - mpBegin);
            if (n > s) {
                CopyA(x.mpBegin, x.mpBegin + s, mpBegin);
                Elem44* tmp;
                UninitCopyBackA((void**)&tmp, x.mpBegin + s, x.mpEnd, mpEnd, x.mpEnd);
            } else {
                CopyA(x.mpBegin, x.mpEnd, mpBegin);
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ------------------------------------------------------------------ @ 0x009dffe0

// @ 0x009dffe0
Vec1C& Vec1C::operator=(const Vec1C& x)
{
    if (this != &x) {
        uint32 n = (uint32)(x.mpEnd - x.mpBegin);
        if (n > (uint32)(mpCapacity - mpBegin)) {
            Elem1C* p = DoAllocate(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                operator delete[](mpBegin);
            mpBegin = p;
            mpCapacity = p + n;
        } else {
            uint32 s = (uint32)(mpEnd - mpBegin);
            if (n > s) {
                CopyC(x.mpBegin, x.mpBegin + s, mpBegin);
                Elem1C* tmp;
                UninitCopyBackC((void**)&tmp, x.mpBegin + s, x.mpEnd, mpEnd, x.mpEnd);
            } else {
                CopyC(x.mpBegin, x.mpEnd, mpBegin);
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ------------------------------------------------------------------ @ 0x009e0110

// @ 0x009e0110
void Vec44::DoInsertValue(Elem44* position, const Elem44& value)
{
    if (mpEnd != mpCapacity) {
        Elem44* pv = (Elem44*)&value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd != 0)
            mpEnd->CopyFrom(*(mpEnd - 1));
        CopyBackA(position, mpEnd - 1, mpEnd);
        *position = *pv;
        ++mpEnd;
        return;
    }

    uint32 n = (uint32)(mpEnd - mpBegin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    Elem44* p = n ? (Elem44*)operator_new(n * 0x44, g_alloc_name_anim_gait, 0, 0,
                                          g_alloc_file_eastl, 0xd1) : (Elem44*)0;
    Elem44* i = UninitCopyA(mpBegin, position, p);
    if (i != 0)
        i->CopyFrom(value);
    Elem44* j = UninitCopyA(position, mpEnd, i + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete[](mpBegin);
    mpEnd = j;
    mpBegin = p;
    mpCapacity = p + n;
}

// ------------------------------------------------------------------ @ 0x009e0230

// @ 0x009e0230
void Vec58::DoInsertValue(Elem58* position, const Elem58& value)
{
    if (mpEnd != mpCapacity) {
        Elem58* pv = (Elem58*)&value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd != 0)
            mpEnd->CopyFrom(*(mpEnd - 1));
        CopyBackB(position, mpEnd - 1, mpEnd);
        *position = *pv;
        ++mpEnd;
        return;
    }

    uint32 n = (uint32)(mpEnd - mpBegin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    Elem58* p = n ? (Elem58*)operator_new(n * 0x58, g_alloc_name_anim_gait, 0, 0,
                                          g_alloc_file_eastl, 0xd1) : (Elem58*)0;
    Elem58* i = UninitCopyB(mpBegin, position, p);
    if (i != 0)
        i->CopyFrom(value);
    Elem58* j = UninitCopyB(position, mpEnd, i + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete[](mpBegin);
    mpBegin = p;
    mpEnd = j;
    mpCapacity = p + n;
}

// ------------------------------------------------------------------ @ 0x009e0330

// @ 0x009e0330
void Vec1C::DoInsertValue(Elem1C* position, const Elem1C& value)
{
    if (mpEnd != mpCapacity) {
        Elem1C* pv = (Elem1C*)&value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd != 0)
            mpEnd->CopyFrom(*(mpEnd - 1));
        CopyBackC(position, mpEnd - 1, mpEnd);
        *position = *pv;
        ++mpEnd;
        return;
    }

    uint32 n = (uint32)(mpEnd - mpBegin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    Elem1C* p = n ? (Elem1C*)operator_new(n * 0x1c, g_alloc_name_anim_gait, 0, 0,
                                          g_alloc_file_eastl, 0xd1) : (Elem1C*)0;
    Elem1C* i = UninitCopyC(mpBegin, position, p);
    if (i != 0)
        i->CopyFrom(value);
    Elem1C* j = UninitCopyC(position, mpEnd, i + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete[](mpBegin);
    mpEnd = j;
    mpBegin = p;
    mpCapacity = p + n;
}

// ------------------------------------------------------------------ @ 0x009e0480

// @ 0x009e0480
Elem0C* Vec0C::erase(Elem0C* first, Elem0C* last)
{
    Elem0C* end = mpEnd;
    Elem0C* dst = first;
    for (Elem0C* src = last; src != end; ++src, ++dst)
        *dst = *src;
    mpEnd -= (last - first);
    return first;
}

// ------------------------------------------------------------------ @ 0x009e04e0

// @ 0x009e04e0
void Vec0C::DoInsertValue(Elem0C* position, const Elem0C& value)
{
    if (mpEnd != mpCapacity) {
        Elem0C* pv = (Elem0C*)&value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd != 0)
            *mpEnd = *(mpEnd - 1);
        Elem0C* src = mpEnd - 1;
        Elem0C* dst = mpEnd;
        while (src != position) {
            --src;
            --dst;
            *dst = *src;
        }
        *position = *pv;
        ++mpEnd;
        return;
    }

    uint32 n = (uint32)(mpEnd - mpBegin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    Elem0C* p = n ? (Elem0C*)operator_new(n * 0xc, g_alloc_name_anim_gait, 0, 0,
                                          g_alloc_file_eastl, 0xd1) : (Elem0C*)0;
    Elem0C* i = Copy0C(mpBegin, position, p);
    if (i != 0)
        *i = value;
    Elem0C* j = Copy0C(position, mpEnd, i + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete[](mpBegin);
    mpBegin = p;
    mpEnd = j;
    mpCapacity = p + n;
}

// ------------------------------------------------------------------ @ 0x009e06a0

// @ 0x009e06a0
void Vec0CS::DoInsertValue(Elem0CS* position, const Elem0CS& value)
{
    if (mpEnd != mpCapacity) {
        Elem0CS* pv = (Elem0CS*)&value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd != 0) {
            mpEnd->a = (mpEnd - 1)->a;
            mpEnd->b = (mpEnd - 1)->b;
            mpEnd->c = (mpEnd - 1)->c;
        }
        Elem0CS* src = mpEnd - 1;
        Elem0CS* dst = mpEnd;
        while (src != position) {
            --src;
            --dst;
            *dst = *src;
        }
        *position = *pv;
        ++mpEnd;
        return;
    }

    uint32 n = (uint32)(mpEnd - mpBegin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    Elem0CS* p = n ? (Elem0CS*)operator_new(n * 0xc, g_alloc_name_anim_gait, 0, 0,
                                            g_alloc_file_eastl, 0xd1) : (Elem0CS*)0;
    Elem0CS* i = Copy0CS(mpBegin, position, p);
    if (i != 0) {
        i->a = value.a;
        i->b = value.b;
        i->c = value.c;
    }
    Elem0CS* j = Copy0CS(position, mpEnd, i + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete[](mpBegin);
    mpBegin = p;
    mpEnd = j;
    mpCapacity = p + n;
}

// ------------------------------------------------------------------ @ 0x009e07d0

// @ 0x009e07d0
ElemA4* DestroyRangeA4(ElemA4* first, ElemA4* last, ElemA4* result)
{
    while (first != last) {
        first->v24.DestroyRange(first->v24.mpBegin, first->v24.mpEnd);
        if (first->v24.mpBegin && ((int*)first->v24.mpBegin)[-1] != 0)
            operator delete[](first->v24.mpBegin);
        if (first->v10.mpBegin && ((int*)first->v10.mpBegin)[-1] != 0)
            operator delete[](first->v10.mpBegin);
        ++first;
        ++result;
    }
    return result;
}

// ------------------------------------------------------------------ @ 0x009e0940

// @ 0x009e0940
void Vec44::clear()
{
    Elem44* first = mpBegin;
    Elem44* last = mpEnd;
    CopyA(last, mpEnd, first);
    mpEnd -= (last - first);
}

// ------------------------------------------------------------------ @ 0x009e0980

// @ 0x009e0980
void Vec58::clear()
{
    Elem58* first = mpBegin;
    Elem58* last = mpEnd;
    CopyB(last, mpEnd, first);
    mpEnd -= (last - first);
}

// ------------------------------------------------------------------ @ 0x009e09c0

// @ 0x009e09c0
void Vec1C::clear()
{
    Elem1C* first = mpBegin;
    Elem1C* last = mpEnd;
    CopyC(last, mpEnd, first);
    mpEnd -= (last - first);
}

// ------------------------------------------------------------------ @ 0x009e0a00

// @ 0x009e0a00
void Vec0C::resize(uint32 n, const Elem0C& value)
{
    if (n > (uint32)(mpCapacity - mpBegin)) {
        Vec0C tmp;
        tmp.Construct(n, &value, &mPad[0]);
        Swap(tmp);
        if (tmp.mpBegin && ((int*)tmp.mpBegin)[-1] != 0)
            operator delete[](tmp.mpBegin);
        return;
    }
    if (n > (uint32)(mpEnd - mpBegin)) {
        Fill0C(mpBegin, mpEnd, &value);
        FillN0C(mpEnd, n - (uint32)(mpEnd - mpBegin), &value);
        mpEnd += (n - (uint32)(mpEnd - mpBegin));
        return;
    }
    FillN0Cb(mpBegin, n, &value);
    erase(mpBegin + n, mpEnd);
}

// ------------------------------------------------------------------ @ 0x009e0b20

// @ 0x009e0b20
Elem0CS* Vec0CS::insert(Elem0CS* position, const Elem0CS& value)
{
    int i = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        Elem0CS* p = mpEnd;
        mpEnd = mpEnd + 1;
        if (p != 0) {
            p->a = value.a;
            p->b = value.b;
            p->c = value.c;
        }
        return mpBegin + i;
    }
    DoInsertValue(position, value);
    return mpBegin + i;
}

// ------------------------------------------------------------------ @ 0x009e0b90

// @ 0x009e0b90
void __stdcall DestroyRangeA4n(ElemA4* first, ElemA4* last)
{
    if (first >= last)
        return;
    uint32 count = ((uint32)((char*)last - (char*)first) - 1) / 0xa4 + 1;
    do {
        first->v24.DestroyRange(first->v24.mpBegin, first->v24.mpEnd);
        if (first->v24.mpBegin && ((int*)first->v24.mpBegin)[-1] != 0)
            operator delete[](first->v24.mpBegin);
        if (first->v10.mpBegin && ((int*)first->v10.mpBegin)[-1] != 0)
            operator delete[](first->v10.mpBegin);
        ++first;
        --count;
    } while (count != 0);
}

// ------------------------------------------------------------------ @ 0x009e0cd0

// @ 0x009e0cd0
Elem40* Copy40(Elem40* first, Elem40* last, Elem40* result)
{
    for (; first != last; ++first, ++result) {
        if (result != first)
            *result = *first;
    }
    return result;
}

// ------------------------------------------------------------------ @ 0x009e0d30

// @ 0x009e0d30
Elem40* CopyBack40(Elem40* first, Elem40* last, Elem40* result)
{
    while (last != first) {
        --last;
        --result;
        if (result != last)
            *result = *last;
    }
    return result;
}
