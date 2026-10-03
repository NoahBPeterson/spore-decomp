// EASTL-style vector support (unoptimized module: /Od /Ob1, frame pointers, every local in memory).
//   - VecPair : vector of 0x18-byte elements (two Vector3 values): DoInsertValue + free
//   - VecVec3 : vector of 0x0c-byte Vector3 elements: DoInsertValue + free
//   - VecFloat: vector<float> fill-insert (built /arch:SSE)
//   - Str16   : small string/value object ctor/assign (0x004279d0)
// Layout of every container: { T* mBegin; T* mEnd; T* mCapacity; Allocator mAllocator; [T* mInlineBuffer] }.

#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

struct Allocator { const char* mpName; };

template<int N> inline void ScratchSlots() { uint32_t s[N]; }
template<> inline void ScratchSlots<0>() {}

struct TagA { char c; TagA() : c(0) {} };
struct TagB { char c; TagB() : c(0) {} };
struct TagC { char c; TagC() : c(0) {} };

void* __cdecl AllocatorAllocate(Allocator* alloc, uint32_t size, uint32_t align, uint32_t offset);  // FUN_0042dee0
void  __cdecl AllocatorDeallocate(void* block);                                                    // EASTL_allocator_deallocate

template <typename T>
struct CopyBackwardAlgo
{
    static T* CopyBackward(T* first, T* last, T* destEnd)
    {
        TagB tb = TagB(); TagA ta = TagA(); TagC tc = TagC();
        return CopyBackwardImpl(first, last, destEnd);
    }
    static T* CopyBackwardImpl(T* first, T* last, T* dest)
    {
        while (last != first)
        {
            --last;
            --dest;
            *dest = *last;
        }
        return dest;
    }
};

// ---------------------------------------------------------------------------------------------
// VecPair
// ---------------------------------------------------------------------------------------------
struct V3i { uint32_t x, y, z; V3i(const V3i& s); };    // Vector3_CopyCtor at 0x004098a0
struct ElemPair;
struct ElemPairX { uint32_t w[6]; ElemPairX(const ElemPairX& s); };   // same layout; out-of-line copy ctor FUN_00511140
struct ElemPair
{
    V3i a;
    V3i b;
    ElemPair(const ElemPair& s) : a(s.a), b(s.b) { ScratchSlots<1>(); }
    ElemPair& operator=(const ElemPair& s) { b = s.b; a = s.a; return *this; }
};
ElemPair* __cdecl MoveRangePair1(ElemPair* first, ElemPair* pos, ElemPair* dest);   // FUN_00424340
ElemPair* __cdecl MoveRangePair2(ElemPair* first, ElemPair* last, ElemPair* dest); // FUN_00512000

inline ElemPair* UninitMovePair(ElemPair* first, ElemPair* last, ElemPair* dest)
{
    ElemPair *d, *f;
    char tb, ta;
    ScratchSlots<4>();
    ElemPair* r;
    ScratchSlots<8>();
    ta = 0;
    r = MoveRangePair2(first, last, dest);
    tb = 0;
    d = dest;
    f = first;
    for (; f != last; ++f, ++d) {}
    return r;
}

struct VecPair
{
    ElemPair* mBegin;
    ElemPair* mEnd;
    ElemPair* mCapacity;
    Allocator mAllocator;
    ElemPair* mInline;

    void DoFreeRange(ElemPair* p, uint32_t /*n*/)
    {
        if (p)
        {
            if (p != mInline)
            {
                void* q = p;
                AllocatorDeallocate(q);
            }
        }
    }
    void DoInsertValue(ElemPair* pos, const ElemPair* value);
    void Free();
};

// @ 0x00427640
void VecPair::DoInsertValue(ElemPair* pos, const ElemPair* value)
{
    if (mEnd != mCapacity)
    {
        const ElemPair* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        new (mEnd) ElemPair(*(mEnd - 1));
        CopyBackwardAlgo<ElemPair>::CopyBackward(pos, mEnd - 1, mEnd);
        *pos = *v;
        ++mEnd;
    }
    else
    {
        uint32_t prevCount = mEnd - mBegin;
        uint32_t newCount = prevCount > 0 ? prevCount * 2 : 1;
        ElemPair* result = newCount ? (ElemPair*)AllocatorAllocate(&mAllocator, newCount * sizeof(ElemPair), 4, 0) : 0;
        ElemPair* nCount = MoveRangePair1(mBegin, pos, result);
        new (nCount) ElemPairX(*(const ElemPairX*)value);   // FUN_00511140
        nCount = nCount + 1;
        nCount = UninitMovePair(pos, mEnd, nCount);
        DoFreeRange(mBegin, mCapacity - mBegin);
        mBegin = result;
        mEnd = nCount;
        mCapacity = result + newCount;
    }
}

// @ 0x00427970
void VecPair::Free()
{
    void* q;
    if (mBegin)
    {
        int bytes = (int)(mCapacity - mBegin) * (int)sizeof(ElemPair);
        ElemPair* p = mBegin;
        (void)bytes;
        if (p != mInline)
        {
            q = p;
            AllocatorDeallocate(q);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// VecVec3
// ---------------------------------------------------------------------------------------------
struct ElemV3 { float x, y, z; ElemV3(const ElemV3& s) : x(s.x), y(s.y), z(s.z) {} };
ElemV3* __cdecl MoveRangeV3a(ElemV3* first, ElemV3* pos, ElemV3* dest);   // FUN_004b66b0
ElemV3* __cdecl MoveRangeV3b(ElemV3* first, ElemV3* last, ElemV3* dest); // FUN_004b6bf0

inline ElemV3* UninitMoveV3(ElemV3* first, ElemV3* last, ElemV3* dest)
{
    ElemV3 *d, *f;
    char tb;
    ScratchSlots<4>();
    ElemV3* r;
    ScratchSlots<8>();
    r = MoveRangeV3b(first, last, dest);
    tb = 0;
    d = dest;
    f = first;
    for (; f != last; ++f, ++d) {}
    return r;
}

struct VecV3
{
    ElemV3* mBegin;
    ElemV3* mEnd;
    ElemV3* mCapacity;
    Allocator mAllocator;
    ElemV3* mInline;

    void DoFreeRange(ElemV3* p, uint32_t /*n*/)
    {
        if (p)
        {
            if (p != mInline)
            {
                void* q = p;
                AllocatorDeallocate(q);
            }
        }
    }
    void DoInsertValue(ElemV3* pos, const ElemV3* value);
    void Free();
};

// @ 0x00427c70
void VecV3::DoInsertValue(ElemV3* pos, const ElemV3* value)
{
    if (mEnd != mCapacity)
    {
        const ElemV3* v = value;
        if (v >= pos && v < mEnd)
            ++v;

        new (mEnd) ElemV3(*(mEnd - 1));
        CopyBackwardAlgo<ElemV3>::CopyBackward(pos, mEnd - 1, mEnd);
        *pos = *v;
        ++mEnd;
    }
    else
    {
        uint32_t prevCount = mEnd - mBegin;
        uint32_t newCount = prevCount > 0 ? prevCount * 2 : 1;
        ElemV3* result = newCount ? (ElemV3*)AllocatorAllocate(&mAllocator, newCount * sizeof(ElemV3), 4, 0) : 0;
        ElemV3* nCount = MoveRangeV3a(mBegin, pos, result);
        new (nCount) ElemV3(*value);
        nCount = nCount + 1;
        nCount = UninitMoveV3(pos, mEnd, nCount);
        DoFreeRange(mBegin, mCapacity - mBegin);
        mBegin = result;
        mEnd = nCount;
        mCapacity = result + newCount;
    }
}

// @ 0x00427f70
void VecV3::Free()
{
    void* q;
    if (mBegin)
    {
        int bytes = (int)(mCapacity - mBegin) * (int)sizeof(ElemV3);
        ElemV3* p = mBegin;
        (void)bytes;
        if (p != mInline)
        {
            q = p;
            AllocatorDeallocate(q);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// VecFloat: vector<float>::DoAssignValues-style fill (built /Od /Ob1 /arch:SSE)
// ---------------------------------------------------------------------------------------------
struct FillTag { uint32_t c; };
struct TempBuf
{
    float* mpData;
    TempBuf* Init(uint32_t n, Allocator* alloc);    // FUN_0042f2e0
    void Free();                                    // FUN_004c0b80
};
void __cdecl UninitFill(FillTag* tag, float* dest, uint32_t n, const float* value);  // FUN_0042efc0
void __cdecl AssignFill(float* dest, uint32_t n, const float* value);                // FUN_0042b5b0

inline void FillRange(float* first, float* last, const float& value)
{
    float* cur = first;
    float v = value;
    for (; cur != last; ++cur)
        *cur = v;
}

inline void UninitFillN(float* dest, uint32_t n, const float& value)
{
    FillTag tag;
    float* d = dest;
    float* d2 = d;
    UninitFill(&tag, d2, n, &value);
}

struct VecFloat
{
    float* mBegin;
    float* mEnd;
    float* mCapacity;
    Allocator mAllocator;

    void SwapIn(TempBuf* buf);                      // FUN_004c2100
    void Erase(float* first, float* last);          // FUN_004769b0
    void DoAssign(uint32_t n, const float* value);
};

// @ 0x00427a50
void VecFloat::DoAssign(uint32_t n, const float* value)
{
    if (n > (uint32_t)(mCapacity - mBegin))
    {
        TempBuf tmp;
        tmp.Init(n, &mAllocator);
        float* a = tmp.mpData;
        float* b = a;
        float* c = b;
        FillTag t;
        UninitFill(&t, c, n, value);
        float* newEnd = tmp.mpData + n;
        SwapIn(&tmp);
        for (float* p = tmp.mpData; p < newEnd; ++p) {}
        tmp.Free();
    }
    else if (n > (uint32_t)(mEnd - mBegin))
    {
        FillRange(mBegin, mEnd, *value);
        UninitFillN(mEnd, n - (uint32_t)(mEnd - mBegin), *value);
        mEnd = mEnd + (n - (uint32_t)(mEnd - mBegin));
    }
    else
    {
        AssignFill(mBegin, n, value);
        Erase(mBegin + n, mEnd);
    }
}

// ---------------------------------------------------------------------------------------------
// Variant (16 data bytes + flags + type); assignment from another variant, always takes the generic path
// because the small-inline condition is a compile-time false.
// ---------------------------------------------------------------------------------------------
struct Variant
{
    char data[16];
    uint16_t flags;
    uint16_t type;
    void Clear(int);                                                    // FUN_0093db80
    void CopyInline(uint32_t a, uint32_t b);                            // FUN_00423650
    void Init(int type, int fl, const Variant* src, int size, int x);   // FUN_0093dd80
    Variant* Assign(const Variant* o);
};

// @ 0x004279d0
Variant* Variant::Assign(const Variant* o)
{
    if (flags & 4)
        Clear(1);
    if (sizeof(Variant) <= 4)
    {
        if (o != this)
            CopyInline(*(const uint32_t*)o, *((const uint32_t*)o + 1));
        type = 0x13;
        flags = (flags & 2) | 9;
    }
    else
        Init(0x13, 9, o, 0x10, 1);
    return this;
}
