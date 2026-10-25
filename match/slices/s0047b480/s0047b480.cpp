// Slice s0047b480: eastl vector range helpers (copy/uninitialized_copy/move), sort helpers,
// basic_string::resize and an element copy ctor. Built /Od /Ob1 /MD /Gy /TP.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>

typedef unsigned int uint;
// Fills the frame with the dead local slots the original's inlined helpers leave behind.
template <int N> inline void ScratchSlots() { unsigned int slots[N]; }
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380

struct Counted { char pad[0x40]; int mRefCount; void Release(); };
struct E16 { float a, b, c, d; };
struct E29 { char pad[0x294]; Counted* m298; };
struct M33 { float m[12]; };
struct Big { uint a, b, c, d, e; M33 mat; Big* CopyBig(const Big* src); };

// out-of-line helpers
void  MoveBig(void* dst, void* src);                     // copy-construct a 0x29c element (0x0047bbf0)
void  CopyElems29(void* first, void* last, void* dest);  // @ 0x0047c980
void  Move16(void* p);                                   // @ 0x00401b80
void  CopyElems16(void* first, void* last, void* dest);  // @ 0x0047d3f0
void  ReleaseBig(void* p);                               // @ 0x0047c... (element release)
extern "C" void __cdecl FUN_0041cb40(void* dst, const void* src); // cSPMatrix3::Assign
extern "C" void __cdecl FUN_0047c600(void* self, uint n);          // basic_string reserve
extern "C" void* __cdecl FUN_011e073e(void* p, int c, uint n);     // memset

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
Big* Big::CopyBig(const Big* src)
{
    Big* dst = this;
    dst->a = src->a; dst->b = src->b; dst->c = src->c; dst->d = src->d; dst->e = src->e;
    ((void(__thiscall*)(void*, const void*))FUN_0041cb40)(&dst->mat, &src->mat);
    return dst;
}

// @ 0x0047b7b0
float* InsertionSort8F(float* first, float* last)
{
    if (first == last || first + 2 == last) return first;
    float* cur = first;
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
    return last;
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
    Str8* resize(uint n, char c);
};
void StrSetCapacity(Str8* s, uint n);       // @ 0x0047d240
extern char gEmptyString[];
Str8* Str8::resize(uint n, char c)
{
    const uint cur = (uint)(mpEnd - mpBegin);
    const uint cap = (uint)(mpCapacity - mpBegin) - 1;
    if (cur + n > cap) {
        const uint target = cur + n;
        const uint cap2 = cap > 8 ? cap * 2 : 8;
        const uint chosen = cap2 >= target ? cap2 : target;
        ((void(__thiscall*)(void*, uint))FUN_0047c600)(this, chosen);
    }
    if (n) {
        FUN_011e073e(mpEnd + 1, (unsigned char)c, n - 1);
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return this;
}

// ---------------------------------------------------------------------------
// 0x38-byte element (cSPTransform) and the vector that owns it.
// ---------------------------------------------------------------------------
struct cSPMatrix3 {                                     // 0x24 bytes
    float m[9];
    cSPMatrix3() {}
    // Inline copy ctor: reserves the frame slots the original leaves behind, then
    // delegates the actual copy to the out-of-line assignment helper.
    cSPMatrix3(const cSPMatrix3& o) { ScratchSlots<11>(); Assign(o); }
    void Assign(const cSPMatrix3& o);                   // 0x0041cb40
};

struct cSPTransform {                                   // 0x38 bytes
    unsigned short mFlags;                              // +0x00
    unsigned short mModCount;                           // +0x02
    float mTranslation[3];                              // +0x04
    float mScale;                                       // +0x10
    float mRotation[9];                                 // +0x14
    cSPTransform& operator=(const cSPTransform& o);     // 0x00537dc0
};

void EAFreeArray(void* p);                                                              // 0x00f47380
cSPTransform* UninitializedCopy56(const cSPTransform* first, const cSPTransform* last,
                                  cSPTransform* dest);                                  // 0x0042e510

struct RandomAccessTag { };

struct TransformVec {                                   // begin, end, capacity, allocator
    cSPTransform* mpBegin;                              // +0x00
    cSPTransform* mpEnd;                                // +0x04
    cSPTransform* mpCapacity;                           // +0x08
    uint32_t mAllocator;                                // +0x0c

    cSPTransform* DoRealloc(uint n, const cSPTransform* first,
                            const cSPTransform* last);                              // 0x0042e4b0
    static cSPTransform* CopyImpl(const cSPTransform* first, const cSPTransform* last,
                                  cSPTransform* dest, bool b0, bool b1, bool b2)
    {
        for (; first != last; ++dest, ++first)
            *dest = *first;
        return dest;
    }
    static cSPTransform* Copy(const cSPTransform* first, const cSPTransform* last,
                              cSPTransform* dest)
    {
        bool b2 = false, b0 = false, b1 = false;
        return CopyImpl(first, last, dest, b0, b1, b2);
    }
    static void DoDestroyValues(cSPTransform* first, cSPTransform* last)
    {
        for (; first < last; ++first) {}
    }
    void DoFree(cSPTransform* p, uint)
    {
        if (p && ((int*)p)[-1] != 0) {
            void* q = p;
            EAFreeArray(q);
        }
    }
    void DoAssignFromIterator(const cSPTransform* first, const cSPTransform* last,
                              RandomAccessTag tag);
};

// @ 0x0047b480
void TransformVec::DoAssignFromIterator(const cSPTransform* first,
                                        const cSPTransform* last,
                                        RandomAccessTag)
{
    const uint n = (uint)(last - first);

    if (n > (uint)(mpCapacity - mpBegin)) {
        cSPTransform* const pNewData = DoRealloc(n, first, last);
        ScratchSlots<10>();
        DoDestroyValues(mpBegin, mpEnd);
        DoFree(mpBegin, (uint)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    }
    else if (n <= (uint)(mpEnd - mpBegin)) {
        cSPTransform* const pNewEnd = Copy(first, last, mpBegin);
        DoDestroyValues(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
    }
    else {
        const cSPTransform* position = first + (mpEnd - mpBegin);
        Copy(first, position, mpBegin);
        mpEnd = UninitializedCopy56(position, last, mpEnd);
    }
    ScratchSlots<14>();
}

// ---------------------------------------------------------------------------
// 8-byte sort key: the introspective quick sort of eastl, comparing element [0].
// ---------------------------------------------------------------------------
struct SortKey {
    float mKey[2];
    SortKey(const SortKey& o) { mKey[0] = o.mKey[0]; mKey[1] = o.mKey[1]; }
    float& operator[](int i) { return mKey[i]; }
    const float& operator[](int i) const { return mKey[i]; }
};

struct KeyLess {
    bool operator()(const SortKey& a, const SortKey& b) const { return a[0] < b[0]; }
};

SortKey* GetPartition(SortKey* first, SortKey* last, SortKey pivot, KeyLess pred);  // 0x0047c400
void     PartialSort(SortKey* first, SortKey* middle, SortKey* last, KeyLess pred); // 0x0047c4e0

// @ 0x0047c2c0
const SortKey& Median(const SortKey& a, const SortKey& b, const SortKey& c, KeyLess pred)
{
    if (pred(a, b)) {
        if (pred(b, c)) return b;
        else if (pred(a, c)) return c;
        else return a;
    }
    else if (pred(a, c)) return a;
    else if (pred(b, c)) return c;
    return b;
}

// @ 0x0047b6d0
void QuickSortImpl(SortKey* first, SortKey* last, int depth, KeyLess pred)
{
    while ((last - first) > 28 && depth > 0) {
        SortKey* position = GetPartition(first, last,
            Median(*first, *(first + (last - first) / 2), *(last - 1), pred), pred);
        --depth;
        QuickSortImpl(position, last, depth, pred);
        last = position;
    }
    if (depth == 0) {
        ScratchSlots<14>();
        PartialSort(first, last, last, pred);
    }
}

// ---------------------------------------------------------------------------
// 0x8c-byte element copy constructor.
// ---------------------------------------------------------------------------
struct Vec3f {                                         // user copy ctor/assign: inline pointer temps
    float v[3];
    Vec3f() {}
    Vec3f(const Vec3f& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
    void operator=(const Vec3f& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
};
struct Vec4f {
    float v[4];
    Vec4f() {}
    Vec4f(const Vec4f& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; v[3] = o.v[3]; }
};
struct Quad4f { float x, y, z, w; };                    // trivial copy ctor

struct Obj8C {                                          // 0x8c bytes
    uint16_t mFlags0;                                   // +0x00
    uint16_t mCount2;                                   // +0x02
    uint16_t m4;                                        // +0x04
    uint16_t m6;                                        // +0x06
    uint16_t m8;                                        // +0x08
    uint8_t mA;                                         // +0x0a
    uint8_t mB;                                         // +0x0b
    uint16_t mC;                                        // +0x0c
    uint16_t mE;                                        // +0x0e
    uint8_t m10;                                        // +0x10
    uint8_t m11;                                        // +0x11
    uint16_t m12;                                       // +0x12
    Vec3f mV14;                                         // +0x14
    Vec3f mV20;                                         // +0x20
    float m2C;                                          // +0x2c
    cSPMatrix3 mRot30;                                  // +0x30
    Vec3f mV54;                                         // +0x54
    Vec3f mV60;                                         // +0x60
    float m6C, m70, m74, m78;                           // +0x6c
    float m7C;                                          // +0x7c
    uint32_t m80;                                       // +0x80
    uint32_t m84;                                       // +0x84
    uint32_t m88;                                       // +0x88
    Obj8C(const Obj8C& o);
};

// @ 0x0047b950
Obj8C::Obj8C(const Obj8C& o)
    : mFlags0(o.mFlags0), mCount2(o.mCount2), m4(o.m4), m6(o.m6), m8(o.m8),
      mA(o.mA), mB(o.mB), mC(o.mC), mE(o.mE), m10(o.m10), m11(o.m11), m12(o.m12),
      mV14(o.mV14), mV20(o.mV20), m2C(o.m2C), mRot30(o.mRot30),
      mV54(o.mV54), mV60(o.mV60), m6C(o.m6C), m70(o.m70), m74(o.m74), m78(o.m78),
      m7C(o.m7C), m80(o.m80), m84(o.m84), m88(o.m88)
{
}

// ---------------------------------------------------------------------------
// 0x29c-byte element copy constructor.
// ---------------------------------------------------------------------------
struct Blk40D { uint32_t m[0x28]; };                    // 160 bytes
struct Blk10D { uint32_t m[0x0a]; };                    //  40 bytes
struct Blk64D { uint32_t m[0x40]; };                    // 256 bytes
struct Blk16D { uint32_t m[0x10]; };                    //  64 bytes

struct RefObj40 {                                       // refcount at +0x40
    uint32_t mPad[0x10];
    int mRefCount;                                      // +0x40
    void AddRef() { ++mRefCount; }
};

struct ObjPtr298 {                                      // AutoRefCount-style member
    RefObj40* mpObj;
    ObjPtr298(const ObjPtr298& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
};

struct Obj29C {                                         // 0x29c bytes
    uint32_t m0;                                        // +0x000
    Blk40D m4;                                          // +0x004
    Blk10D mA4;                                         // +0x0a4
    uint32_t mCC;                                       // +0x0cc
    uint32_t mD0;                                       // +0x0d0
    uint32_t mD4;                                       // +0x0d4
    uint32_t mD8;                                       // +0x0d8
    uint32_t mDC;                                       // +0x0dc
    Vec3f mE0;                                          // +0x0e0
    uint32_t mEC;                                       // +0x0ec
    Vec3f mF0;                                          // +0x0f0
    Vec3f mFC;                                          // +0x0fc
    Vec3f m108;                                         // +0x108
    Vec4f m114;                                         // +0x114
    Vec3f m124;                                         // +0x124
    Vec3f m130;                                         // +0x130
    float m13C;                                         // +0x13c
    float m140;                                         // +0x140
    uint32_t m144;                                      // +0x144
    uint32_t m148;                                      // +0x148
    uint32_t m14C;                                      // +0x14c
    uint32_t m150;                                      // +0x150
    uint32_t m154;                                      // +0x154
    Blk64D m158;                                        // +0x158
    Blk16D m258;                                        // +0x258
    ObjPtr298 mObj298;                                  // +0x298
    Obj29C(const Obj29C& o);
};

// @ 0x0047bbf0
Obj29C::Obj29C(const Obj29C& o)
    : m0(o.m0), m4(o.m4), mA4(o.mA4), mCC(o.mCC), mD0(o.mD0), mD4(o.mD4), mD8(o.mD8), mDC(o.mDC),
      mE0(o.mE0), mEC(o.mEC), mF0(o.mF0), mFC(o.mFC), m108(o.m108), m114(o.m114), m124(o.m124),
      m130(o.m130), m13C(o.m13C), m140(o.m140), m144(o.m144), m148(o.m148), m14C(o.m14C),
      m150(o.m150), m154(o.m154), m158(o.m158), m258(o.m258), mObj298(o.mObj298)
{
}

void MoveBig(void* dst, void* src)
{
    new (dst) Obj29C(*(const Obj29C*)src);
}
