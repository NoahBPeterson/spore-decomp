// src/game/SPEngine/SPGraphicsChartPacker.cpp -- migrated from slice(s) s006e0030, s006deee0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsChartPacker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cClusterRect.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void  FreeMem(void* p);                                                  // 0xf47380
extern "C" void* AllocMem(unsigned n, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern "C" void  VecPushBackSlow(void* end, const void* value);                                          // 0x6ec4a0

// ---- items of slice s006deee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedExchange(volatile long*, long);
namespace SP {
struct cSPVector2 { float x, y; };
}
namespace SP {
struct cClusterRect_s006d_eee0 {
    uint  mStartIndices;   // +0x00
    uint  mEndIndices;     // +0x04
    float mArea;           // +0x08
    uint  mMeshIndex;      // +0x0c
    cSPVector2 mMinUV;     // +0x10
    cSPVector2 mMaxUV;     // +0x18
    cSPVector2 mTexBound;  // +0x20
    float mAreaWeight;     // +0x28
    int   mRectID;         // +0x2c
    float mLinearScale;    // +0x30

    cClusterRect_s006d_eee0() {}
    cClusterRect_s006d_eee0(const cClusterRect_s006d_eee0& o)
        : mStartIndices(o.mStartIndices), mEndIndices(o.mEndIndices), mArea(o.mArea),
          mMeshIndex(o.mMeshIndex), mMinUV(o.mMinUV), mMaxUV(o.mMaxUV), mTexBound(o.mTexBound),
          mAreaWeight(o.mAreaWeight), mRectID(o.mRectID), mLinearScale(o.mLinearScale) {}
};
}
struct cRectAreaSort {
    bool operator()(const SP::cClusterRect_s006d_eee0& a, const SP::cClusterRect_s006d_eee0& b) const {
        return *(const uint*)&a.mArea > *(const uint*)&b.mArea;
    }
};
template <typename T, typename Compare>
const T& Median3(const T& a, const T& b, const T& c, const Compare& compare) {
    if (compare(a, b)) {
        if (compare(b, c)) return b;
        else if (compare(a, c)) return c;
        else return a;
    } else {
        if (compare(a, c)) return a;
        else if (compare(b, c)) return c;
        else return b;
    }
}
struct SortKeyObj { uint mPad; uint mKey; };
struct SortKeyGreater {
    bool operator()(const SortKeyObj* a, const SortKeyObj* b) const { return a->mKey > b->mKey; }
};
struct SortKeyLess {
    bool operator()(const SortKeyObj* a, const SortKeyObj* b) const { return a->mKey < b->mKey; }
};
struct IRefObj {                        // vtable[0]=AddRef, vtable[1]=Release
    virtual void AddRef();
    virtual void Release();
};
struct IntrusiveRef {
    IRefObj* mpObject;                  // +0x0
    IntrusiveRef& operator=(const IntrusiveRef& x) {
        IRefObj* src = x.mpObject;
        IRefObj* old = mpObject;
        if (src != old) {
            if (src)
                src->AddRef();
            mpObject = src;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct Elem16 {
    uint32_t f0;      // +0x0
    uint32_t f4;      // +0x4
    uint16_t f8;      // +0x8
    uint16_t fa;      // +0xa
    IntrusiveRef ref; // +0xc
};
struct RefCountObj {
    virtual void Delete(int flags);
    int mnRefCount;                     // +0x4
};
struct RefPtr {
    RefCountObj* mpObject;              // +0x0
    RefPtr& AssignRefPtr(const RefPtr* x);
    RefPtr& operator=(const RefPtr& x) {
        RefCountObj* src = x.mpObject;
        RefCountObj* old = mpObject;
        if (src != old) {
            if (src)
                _InterlockedIncrement((volatile long*)&src->mnRefCount);
            mpObject = src;
            if (old) {
                volatile long* p = (volatile long*)&old->mnRefCount;
                long n = _InterlockedDecrement(p);
                if (n == 0) {
                    _InterlockedExchange(p, 1);
                    old->Delete(1);
                }
            }
        }
        return *this;
    }
};
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void  FreeMem(void* p);                                                  // 0xf47380
extern "C" void* AllocMem(unsigned n, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern "C" void  AdjustHeapCR(SP::cClusterRect_s006d_eee0* first, int top, int size, int pos, SP::cClusterRect_s006d_eee0 value, const cRectAreaSort* cmp);  // 0x6dea60
extern "C" void  SortHeapCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort* cmp);  // 0x6df220
extern "C" void  InsertionSortCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort* cmp);  // 0x6dede0
extern "C" void  AdjustHeapKeyGT(SortKeyObj** first, int top, int size, int pos, SortKeyObj* value, const SortKeyGreater* cmp);  // 0x6de980
extern "C" void  AdjustHeapKeyLT(SortKeyObj** first, int top, int size, int pos, SortKeyObj* value, const SortKeyLess* cmp);  // 0x6de9f0
extern "C" void  MakeHeapKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);       // 0x6df050
extern "C" void  MakeHeapKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);          // 0x6df0e0
extern "C" void  SortHeapKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);       // 0x6df090
extern "C" void  SortHeapKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);          // 0x6df120
extern "C" void  Elem16Fill(Elem16* first, Elem16* last, const Elem16* value);                          // 0x6de8f0
extern "C" void  Elem16MoveBack(Elem16* first, Elem16* last, void* dest, void* destEnd, Elem16* p);     // 0x6de850
extern "C" void  VecPushBackSlow(void* end, const void* value);                                          // 0x6ec4a0
struct Elem16Vector {
    Elem16* mpBegin;    // +0x00
    Elem16* mpEnd;      // +0x04
    Elem16* mpCapacity; // +0x08
    void*   mpPad;      // +0x0c
    void*   mpInline;   // +0x10
    void Destroy();
    int Elem16VecEraseRange(int dest, int from);
    void Elem16VecInsert(int position, uint n, Elem16* value);
};
struct Elem58 {
    void* mpData;      // +0x00
    uint  mPad[3];     // +0x04
    void* mpInline;    // +0x10
    uint  mPad2[0x11]; // +0x14 .. +0x58
};
struct ClusterMapAdder { void AddCluster(int* rect); };
struct ClusterMap {
    bool     mFlag;        // +0x000
    void*    mpPad1;       // +0x004
    void*    mpPad2;       // +0x008
    void*    mpPad3;       // +0x00c
    char     mPad10[0x8];  // +0x010
    void*    mpVecBegin;   // +0x018
    void*    mpVecEnd;     // +0x01c
    void*    mpInlineAlloc;// +0x020
    char     mPad24[0x4];  // +0x024
    void*    mpVecCap;     // +0x028
    char     mPad2c[0x204];// +0x02c
    float    mArea;        // +0x230
    int**    mpListBegin;  // +0x234
    int**    mpListEnd;    // +0x238
    int**    mpListCap;    // +0x23c
    char     mPad240[0x8]; // +0x240
    void*    mpVec2Begin;  // +0x248
    void*    mpVec2End;    // +0x24c
    void*    mpVec2Cap;    // +0x250
    char     mPad254[0x8]; // +0x254
    void*    mpVec3Begin;  // +0x25c
    void*    mpVec3End;    // +0x260
    void*    mpVec3Cap;    // +0x264
    void Init();
};
// ---- items of slice s006deee0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void  AdjustHeapCR(SP::cClusterRect_s006d_eee0* first, int top, int size, int pos, SP::cClusterRect_s006d_eee0 value, const cRectAreaSort* cmp);  // 0x6dea60
extern "C" void  SortHeapCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort* cmp);  // 0x6df220
extern "C" void  InsertionSortCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort* cmp);  // 0x6dede0
extern "C" void  AdjustHeapKeyGT(SortKeyObj** first, int top, int size, int pos, SortKeyObj* value, const SortKeyGreater* cmp);  // 0x6de980
extern "C" void  AdjustHeapKeyLT(SortKeyObj** first, int top, int size, int pos, SortKeyObj* value, const SortKeyLess* cmp);  // 0x6de9f0
extern "C" void  MakeHeapKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);       // 0x6df050
extern "C" void  MakeHeapKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);          // 0x6df0e0
extern "C" void  SortHeapKeyGT(SortKeyObj** first, SortKeyObj** last, const SortKeyGreater* cmp);       // 0x6df090
extern "C" void  SortHeapKeyLT(SortKeyObj** first, SortKeyObj** last, const SortKeyLess* cmp);          // 0x6df120
extern "C" void  Elem16Fill(Elem16* first, Elem16* last, const Elem16* value);                          // 0x6de8f0
extern "C" void  Elem16MoveBack(Elem16* first, Elem16* last, void* dest, void* destEnd, Elem16* p);     // 0x6de850

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void InsertionSortSimpleCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort& compare);  // 0x006deee0 (stays in the slice: not this object's)
void MakeHeapCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort& compare);  // 0x006df170 (stays in the slice: not this object's)
Elem16* CopyElem16(Elem16* first, Elem16* last, Elem16* dest);  // 0x006df2d0 (stays in the slice: not this object's)
Elem16* CopyBackwardElem16(Elem16* first, Elem16* last, Elem16* destEnd);  // 0x006df340 (stays in the slice: not this object's)

// ---- items of slice s006e0030 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   DAT_01532b94;      // grid resolution
extern float DAT_01532da4;
extern float _DAT_01532da0;
extern "C" void  FUN_004746c0(int n, void* p);
extern "C" void  FUN_007b00d0();
extern "C" void  FUN_007b0fa0(int a, int b);
extern "C" int   FUN_007b1e70(int a, int b);
extern "C" int   FUN_0071ddc0(int a, int b, int c, int d, int e);
extern "C" void  FUN_006dec60(int obj, float f);
extern "C" char  FUN_006de710(int obj);
extern "C" char  FUN_006de5e0(int obj);
extern "C" void  FUN_006dfa00();
extern "C" void  FUN_006dfa80(void* a, void* b, int c);
extern "C" void  VecBoolDoInsertValue(void* a, void* b, int c);
extern "C" void  ThreadSleep(void* p);
extern "C" void  operator_delete__(void* p);
extern "C" void  QuickSortCRExtern(void* first, void* last, int cmp);
typedef unsigned short ushort;
struct Vertex2 { float x, y; };
struct Cluster {
    int       mIndex;        // +0x00
    int       m04;           // +0x04
    float     m08;           // +0x08
    int       mBegin;        // +0x0c
    int       mEnd;          // +0x10
    Vertex2*  mVertBegin;    // +0x14
    Vertex2*  mVertEnd;      // +0x18
    int       m1c;           // +0x1c
    int       m20;           // +0x20
    int       m24;           // +0x24
    float     m28;           // +0x28
    float     m2c;           // +0x2c
    char      mFlag30;       // +0x30
    char      pad31[4];      // +0x31
    int*      mArr34;        // +0x34
    int*      mArrEnd38;     // +0x38
    int       m3c;           // +0x3c
    int       m40;           // +0x40
    int       m44;           // +0x44
    int*      mArr48;        // +0x48
    int*      mArrEnd4c;     // +0x4c
    int       m50;           // +0x50
    int       m54;           // +0x54
    int       m58;           // +0x58
    int       mMax5c;        // +0x5c
    float     m60;           // +0x60
    float     m64;           // +0x64
};
extern "C" void  FUN_004cea40(void* dst, uint n, void* value);
extern "C" void  FUN_006e0030(Cluster* c);
struct ChartSet { int RectPackCharts(int flag); void FillVertices(int* list); };
struct Elem16VecMem {
void Insert(int position, int n, void* value);   // 0x006dfd90
void Erase(int position, int end);               // 0x006dfca0
void Resize(uint n);
};
struct Elem16_s006e_0030 {
    uint32_t f0; uint32_t f4; uint16_t f8; uint16_t fa; void* ref;
};
// ---- items of slice s006e0030 end

// @ 0x006df420
SortKeyObj** GetPartitionKeyGT(SortKeyObj** first, SortKeyObj** last, SortKeyObj* pivotValue, const SortKeyGreater& compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        SortKeyObj* temp = *first;
        *first = *last;
        *last = temp;
    }
}

// @ 0x006df470
void PartialSortKeyGT(SortKeyObj** first, SortKeyObj** middle, SortKeyObj** last, const SortKeyGreater& compare)
{
    MakeHeapKeyGT(first, middle, &compare);
    for (SortKeyObj** i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            SortKeyObj* temp = *i;
            *i = *first;
            AdjustHeapKeyGT(first, 0, (int)(middle - first), 0, temp, &compare);
        }
    }
    SortHeapKeyGT(first, middle, &compare);
}

// @ 0x006df4e0
SortKeyObj** GetPartitionKeyLT(SortKeyObj** first, SortKeyObj** last, SortKeyObj* pivotValue, const SortKeyLess& compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        SortKeyObj* temp = *first;
        *first = *last;
        *last = temp;
    }
}

// @ 0x006df530
void PartialSortKeyLT(SortKeyObj** first, SortKeyObj** middle, SortKeyObj** last, const SortKeyLess& compare)
{
    MakeHeapKeyLT(first, middle, &compare);
    for (SortKeyObj** i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            SortKeyObj* temp = *i;
            *i = *first;
            AdjustHeapKeyLT(first, 0, (int)(middle - first), 0, temp, &compare);
        }
    }
    SortHeapKeyLT(first, middle, &compare);
}

// @ 0x006df5a0
void PartialSortCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* middle, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort& compare)
{
    MakeHeapCR(first, middle, compare);
    for (SP::cClusterRect_s006d_eee0* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const SP::cClusterRect_s006d_eee0 temp(*i);
            *i = *first;
            AdjustHeapCR(first, 0, (int)(middle - first), 0, temp, &compare);
        }
    }
    SortHeapCR(first, middle, &compare);
}

// @ 0x006df700
RefPtr* CopyRefPtr(RefPtr* first, RefPtr* last, RefPtr* dest)
{
    if (first == last)
        return dest;
    do {
        *dest = *first;
        ++first;
        ++dest;
    } while (first != last);
    return dest;
}

// @ 0x006df770
void QuickSortImplKeyGT(SortKeyObj** first, SortKeyObj** last, int kRecursionCount, const SortKeyGreater& compare)
{
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        SortKeyObj** mid = first + (last - first) / 2;
        SortKeyObj** lastm1 = last - 1;
        SortKeyObj* const& pivot = Median3(*first, *mid, *lastm1, compare);
        SortKeyObj** position = GetPartitionKeyGT(first, last, pivot, compare);
        QuickSortImplKeyGT(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortKeyGT(first, last, last, compare);
}

// @ 0x006df830
void QuickSortImplKeyLT(SortKeyObj** first, SortKeyObj** last, int kRecursionCount, const SortKeyLess& compare)
{
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        SortKeyObj** mid = first + (last - first) / 2;
        SortKeyObj** lastm1 = last - 1;
        SortKeyObj* const& pivot = Median3(*first, *mid, *lastm1, compare);
        SortKeyObj** position = GetPartitionKeyLT(first, last, pivot, compare);
        QuickSortImplKeyLT(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortKeyLT(first, last, last, compare);
}

// @ 0x006df8f0
SP::cClusterRect_s006d_eee0* GetPartitionCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, SP::cClusterRect_s006d_eee0 pivotValue, const cRectAreaSort& compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const SP::cClusterRect_s006d_eee0 temp(*first);
        *first = *last;
        *last = temp;
    }
}

// @ 0x006df9d0
void __stdcall DestroyRange58(Elem58* first, Elem58* last)
{
    for (; first < last; ++first) {
        void* p = first->mpData;
        if (p && p != first->mpInline)
            FreeMem(p);
    }
}

// @ 0x006dfb00
void QuickSortImplCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, int kRecursionCount, const cRectAreaSort& compare)
{
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        SP::cClusterRect_s006d_eee0* mid = first + (last - first) / 2;
        SP::cClusterRect_s006d_eee0* lastm1 = last - 1;
        const SP::cClusterRect_s006d_eee0& pivot = Median3(*first, *mid, *lastm1, compare);
        SP::cClusterRect_s006d_eee0* position = GetPartitionCR(first, last, pivot, compare);
        QuickSortImplCR(position, last, --kRecursionCount, compare);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortCR(first, last, last, compare);
}

// @ 0x006dfc30
void ClusterMapAdder::AddCluster(int* rect)
{
    int* self = (int*)this;
    void* model = *(void**)(self + 6);                       // self+0x18
    if (*(void**)((char*)model + *rect * 0x10 + 4) != 0) {
        int** pEnd = (int**)((char*)self + 0x238);
        int** pCap = (int**)((char*)self + 0x23c);
        int* slot = *pEnd;
        if (*pEnd < *pCap) {
            *pEnd = slot + 1;
            if (slot)
                *slot = (int)rect;
        } else {
            VecPushBackSlow(*pEnd, &rect);
        }
        *(float*)((char*)self + 0x230) += (float)rect[2];
    }
}

// @ 0x006dfca0
int Elem16Vector::Elem16VecEraseRange(int dest, int from)
{
    int* self = (int*)this;
    Elem16* newEnd = CopyElem16((Elem16*)from, *(Elem16**)(self + 1), (Elem16*)dest);
    uint count = ((uint)*(self + 1) - (uint)newEnd) >> 4;
    if (newEnd < *(Elem16**)(self + 1)) {
        Elem16* p = newEnd;
        uint n = count;
        do {
            if (p->ref.mpObject)
                p->ref.mpObject->Release();
            ++p;
        } while (--n);
    }
    *(int*)(self + 1) = *(int*)(self + 1) + ((from - dest) >> 4) * -0x10;
    return dest;
}

// @ 0x006dfd00
void QuickSortCR(SP::cClusterRect_s006d_eee0* first, SP::cClusterRect_s006d_eee0* last, const cRectAreaSort& compare)
{
    if (first != last) {
        int n = (int)(last - first);
        int k = 0;
        for (int i = n; i != 0; i >>= 1)
            ++k;
        QuickSortImplCR(first, last, k * 2 - 2, compare);
        if (n > 28) {
            InsertionSortCR(first, first + 28, &compare);
            InsertionSortSimpleCR(first + 28, last, compare);
        } else {
            InsertionSortCR(first, last, &compare);
        }
    }
}

// @ 0x006dfd90
void Elem16Vector::Elem16VecInsert(int position, uint n, Elem16* value)
{
    int* self = (int*)this;
    uint space = (uint)((*(Elem16**)(self + 2) - *(Elem16**)(self + 1)) >> 4);
    if (space < n) {
        int size = (*(int*)(self + 1) - *self) >> 4;
        uint newCap = size * 2;
        if (size == 0)
            newCap = 1;
        uint want = size + n;
        if (want < newCap)
            want = newCap;
        Elem16* pNew = 0;
        if (want != 0)
            pNew = (Elem16*)AllocMem(want << 4, "Graphics", 0, 0,
                                     "eastl/allocator.h", 0xd1);
        Elem16* newEnd = CopyElem16((Elem16*)*self, (Elem16*)position, pNew);
        Elem16Fill(newEnd, newEnd + n, value);
        newEnd += n;
        CopyElem16((Elem16*)position, *(Elem16**)(self + 1), newEnd);
        if (*self && *self != *(int*)(self + 4))
            FreeMem((void*)*self);
        *(int*)(self + 1) = (int)(pNew + size + n);
        *self = (int)pNew;
        *(int*)(self + 2) = (int)(pNew + want);
    } else if (n != 0) {
        Elem16 local = *value;
        if (local.ref.mpObject)
            local.ref.mpObject->AddRef();
        int end = *(int*)(self + 1);
        uint tail = (uint)((end - position) >> 4);
        if (n < tail) {
            Elem16* src = (Elem16*)(end - (n << 4));
            Elem16MoveBack((Elem16*)src, (Elem16*)end, (void*)end, (void*)end, (Elem16*)0);
            CopyBackwardElem16((Elem16*)position, src, (Elem16*)end);
            *(int*)(self + 1) += n << 4;
            for (uint i = 0; i < n; ++i)
                *((Elem16*)position + i) = *value;
        } else {
            Elem16* pEnd = (Elem16*)end;
            Elem16Fill(pEnd, pEnd + (n - tail), value);
            *(int*)(self + 1) += (n - tail) << 4;
            Elem16* src = (Elem16*)(*(int*)(self + 1) - (n << 4));
            CopyElem16((Elem16*)position, src, (Elem16*)end);
            *(int*)(self + 1) += tail << 4;
            for (uint i = 0; i < tail; ++i)
                *((Elem16*)position + i) = *value;
        }
        if (local.ref.mpObject)
            local.ref.mpObject->Release();
    }
}

// @ 0x006dffc0
void ClusterMap::Init()
{
    void* inlineBuf = (char*)this + 0x30;
    mFlag = false;
    mpPad1 = 0;
    mpPad2 = 0;
    mpPad3 = 0;
    mpVecEnd = inlineBuf;
    mpVecBegin = inlineBuf;
    mpInlineAlloc = (char*)this + 0x230;
    mpVecCap = inlineBuf;
    mArea = 0.0f;
    mpListBegin = 0;
    mpListEnd = 0;
    mpListCap = 0;
    mpVec2Begin = 0;
    mpVec2End = 0;
    mpVec2Cap = 0;
    mpVec3Begin = 0;
    mpVec3End = 0;
    mpVec3Cap = 0;
}

// @ 0x006e0030
int ChartBuildSpans(Cluster* self)
{
    float f = (float)DAT_01532b94 * self->m28;
    int local_98 = (int)(f + 0.5f);
    if (f < (float)local_98)
        local_98 = local_98 - 1;
    float local_90 = (float)DAT_01532b94 * self->m2c;

    int* end4c = self->mArrEnd4c;
    int* begin48 = self->mArr48;
    VecBoolDoInsertValue(begin48, end4c, 0);
    self->mArrEnd4c = (int*)((int)self->mArrEnd4c + (((int)end4c - (int)begin48) >> 2) * -4);
    int* end38 = self->mArrEnd38;
    int* begin34 = self->mArr34;
    VecBoolDoInsertValue(begin34, end38, 0);
    self->mArrEnd38 = (int*)((int)self->mArrEnd38 + (((int)end38 - (int)begin34) >> 2) * -4);

    int n = local_98 + 1;
    FUN_004746c0(n, &DAT_01532b94);
    int zero = 0;
    FUN_004746c0(n, &zero);

    int i = 0;
    self->mMax5c = 0;
    int count = (int)(self->mVertEnd - self->mVertBegin);
    if (0 < count) {
        do {
            Vertex2* v = self->mVertBegin;
            float a = v[i].x;
            float c = v[i].y;
            i = i + 1;
            float b = v[i % count].x;
            float d = v[i % count].y;
            float lo = b, hi = a, loY = d, hiY = c;
            if (b <= a) {
                lo = a; a = b; loY = c; c = d;
                (void)lo; (void)loY;
            }
            // (the swap above mirrors the decompile's register shuffling)
            float mn = a, mx = b;
            float mnY = c, mxY = d;
            if (b <= a) {
                mn = b; mx = a; mnY = d; mxY = c;
            }
            int i0 = (int)((float)DAT_01532b94 * mn + 0.5f);
            if ((float)DAT_01532b94 * mn < (float)i0)
                i0 = i0 - 1;
            int i1 = (int)((float)DAT_01532b94 * mx + 0.5f);
            if ((float)DAT_01532b94 * mx < (float)i1)
                i1 = i1 - 1;
            if (i0 < 0)
                i0 = 0;
            if (local_98 <= i1)
                i1 = local_98;

            if (0.0001f <= (mx - mn < 0 ? mn - mx : mx - mn)) {
                float slope = (mxY - mnY) / (mx - mn);
                float base = (mnY - mn * slope) * (float)DAT_01532b94;
                for (int k = i0; k <= i1; ++k) {
                    float y0 = (k == i0) ? (float)DAT_01532b94 * mnY
                                         : (float)k * slope + base;
                    float y1 = (k == i1) ? (float)DAT_01532b94 * mxY
                                         : (float)(k + 1) * slope + base;
                    int lo2, hi2;
                    if (mxY <= mnY) {
                        hi2 = (int)(y1 + 0.5f);
                        if (y1 < (float)hi2) hi2 -= 1;
                        lo2 = (int)(y0 + 0.5f);
                        if ((float)lo2 < y0) lo2 += 1;
                    } else {
                        hi2 = (int)(y0 + 0.5f);
                        if (y0 < (float)hi2) hi2 -= 1;
                        lo2 = (int)(y1 + 0.5f);
                        if ((float)lo2 < y1) lo2 += 1;
                    }
                    if (*(int*)((char*)self->mArr34 + k * 4) < hi2)
                        *(int*)((char*)self->mArr34 + k * 4) = hi2;
                    if (lo2 < *(int*)((char*)self->mArr48 + k * 4))
                        *(int*)((char*)self->mArr48 + k * 4) = lo2;
                }
            } else {
                for (; i0 <= i1; ++i0) {
                    int lo2, hi2;
                    if (mxY <= mnY) {
                        float t = (float)DAT_01532b94 * mxY;
                        hi2 = (int)(t + 0.5f);
                        if (t < (float)hi2) hi2 -= 1;
                        float u = (float)DAT_01532b94 * mnY;
                        lo2 = (int)(u + 0.5f);
                        if ((float)lo2 < u) lo2 += 1;
                    } else {
                        float t = (float)DAT_01532b94 * mnY;
                        hi2 = (int)(t + 0.5f);
                        if (t < (float)hi2) hi2 -= 1;
                        float u = (float)DAT_01532b94 * mxY;
                        lo2 = (int)(u + 0.5f);
                        if ((float)lo2 < u) lo2 += 1;
                    }
                    if (*(int*)((char*)self->mArr34 + i0 * 4) < hi2)
                        *(int*)((char*)self->mArr34 + i0 * 4) = hi2;
                    if (lo2 < *(int*)((char*)self->mArr48 + i0 * 4))
                        *(int*)((char*)self->mArr48 + i0 * 4) = lo2;
                }
            }
        } while (i < count);
    }

    i = 0;
    int n2 = (int)(self->mArrEnd38 - self->mArr34);
    if (0 < n2) {
        do {
            int v = *(int*)((char*)self->mArr34 + i * 4);
            if (self->mMax5c < v)
                self->mMax5c = v;
            if (*(int*)((char*)self->mArr48 + i * 4) == DAT_01532b94)
                *(int*)((char*)self->mArr48 + i * 4) = 0;
            i = i + 1;
        } while (i < n2);
    }
    (void)local_90;
    return 1;
}

// @ 0x006e04d0
int ChartSet::RectPackCharts(int flag)
{
    int* self = (int*)this;
    float fVar12 = 0.0f, fVar13 = 0.0f, fVar15 = 0.0f;
    float fVar14 = 1.0f / *(float*)((char*)self + 0x230);
    int n = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
    int step = 0;
    if (1 < n) {
        int* p = *(int**)((char*)self + 0x234);
        int m = ((n - 2) >> 1) + 1;
        step = m * 2;
        do {
            int a = p[0];
            int b = p[1];
            fVar12 = ((*(float*)(a + 8) * fVar14) * *(float*)(a + 0x2c)) * *(float*)(a + 0x28) + fVar12;
            p += 2;
            m = m - 1;
            fVar13 = ((*(float*)(b + 8) * fVar14) * *(float*)(b + 0x2c)) * *(float*)(b + 0x28) + fVar13;
        } while (m != 0);
    }
    if (step < n) {
        int o = *(int*)(*(int*)((char*)self + 0x234) + step * 4);
        fVar15 = ((*(float*)(o + 8) * fVar14) * *(float*)(o + 0x2c)) * *(float*)(o + 0x28);
    }
    n = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
    int k = 0;
    fVar12 = DAT_01532da4 / ((fVar12 + fVar13) + fVar15);
    if (0 < n) {
        do {
            int o = *(int*)(*(int*)((char*)self + 0x234) + k * 4);
            FUN_006dec60(o, (*(float*)(o + 8) * fVar14) * fVar12);
            k = k + 1;
        } while (k < n);
    }

    uint local_c = 0;
    if (flag == 0)
        FUN_006dfa00();
    else
        FUN_006dfa80(*(void**)((char*)self + 0x234), *(void**)((char*)self + 0x238), (int)local_c);

    local_c = 0;
    int local_8 = 0;
    char local_d = 1;
    do {
        void* end = *(void**)((char*)self + 0x260);
        void* beg = *(void**)((char*)self + 0x25c);
        VecBoolDoInsertValue(beg, end, 0);
        *(int*)((char*)self + 0x260) =
            *(int*)((char*)self + 0x260) + (((int)end - (int)beg) >> 2) * -4;
        void* e2 = *(void**)((char*)self + 0x260);
        int b2 = *(int*)((char*)self + 0x25c);
        uint have = ((int)e2 - b2) >> 2;
        if (have < (uint)DAT_01532b94) {
            FUN_004cea40(e2, DAT_01532b94 - have, &local_8);
        } else {
            void* pos = (void*)(b2 + DAT_01532b94 * 4);
            VecBoolDoInsertValue(pos, e2, 0);
            *(int*)((char*)self + 0x260) =
                *(int*)((char*)self + 0x260) + (((int)e2 - (int)pos) >> 2) * -4;
        }
        int i = 0;
        int cnt = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
        uint lim = (uint)DAT_01532b94;
        int local_4 = cnt;
        if (0 < cnt) {
            do {
                int o = *(int*)(*(int*)((char*)self + 0x234) + i * 4);
                if ((*(char*)(o + 0x30) == '\0') && (i < (int)(lim * lim))) {
                    FUN_006e0030((Cluster*)o);
                    char cv = (flag == 0) ? FUN_006de710(o) : FUN_006de5e0(o);
                    local_d = (cv == '\0');
                    cnt = local_4;
                    lim = (uint)DAT_01532b94;
                    if (local_d)
                        break;
                }
                i = i + 1;
            } while (i < cnt);
        }
        int sleepArg = 0;
        local_4 = 0;
        ThreadSleep(&sleepArg);
        local_c = local_c + 1;
        if (local_d == '\0')
            break;
        int i2 = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
        if (0 < i2) {
            int j = 0;
            do {
                FUN_006dec60(*(int*)(*(int*)((char*)self + 0x234) + j * 4), _DAT_01532da0);
                j = j + 1;
            } while (j < i2);
        }
    } while ((int)local_c < 0x20);

    int ncl = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
    uint c2 = 0;
    if (0 < ncl) {
        do {
            int* cl = *(int**)(*(int*)((char*)self + 0x234) + c2 * 4);
            if (((char)cl[0xc] == '\0') && ((int)c2 < (int)(DAT_01532b94 * DAT_01532b94))) {
                float inv = 1.0f / (float)(int)DAT_01532b94;
                float du = (float)cl[0x18] * inv;
                float dv = (float)cl[0x19] * inv;
                float su = 1.0f, sv = 1.0f;
                if ((float)cl[10] < inv) su = inv / (float)cl[10];
                if ((float)cl[0xb] < inv) sv = inv / (float)cl[0xb];
                int v = cl[3];
                int model = *cl * 0x10 + *(int*)((char*)self + 0x18);
                if (v < cl[4]) {
                    do {
                        char* base = (char*)((uint)*(ushort*)(model + 10) * v + *(int*)(model + 4));
                        float* p = (float*)base;
                        p[1] = sv * p[1];
                        *p = *p * su;
                        p = (float*)((uint)*(ushort*)(model + 10) * v + *(int*)(model + 4));
                        *p = *p + du;
                        p[1] = dv + p[1];
                        int off = (uint)*(ushort*)(model + 10) * v;
                        *(uint*)(off + 4 + *(int*)(model + 4)) =
                            *(uint*)(off + 4 + *(int*)(model + 4)) ^ 0x80000000;
                        p = (float*)((uint)*(ushort*)(model + 10) * v + *(int*)(model + 4));
                        v = v + 1;
                        *p = 1.0f - *p;
                    } while (v < cl[4]);
                }
                int u = 0;
                int uvN = (cl[6] - cl[5]) >> 3;
                if (3 < uvN) {
                    do {
                        int o = u * 8;
                        float* q = (float*)(cl[5] + o);
                        *q = du + *q; q[1] = dv + q[1];
                        q = (float*)(cl[5] + 8 + o);
                        *q = du + *q; q[1] = dv + q[1];
                        q = (float*)(o + 0x10 + cl[5]);
                        *q = du + *q; q[1] = dv + q[1];
                        q = (float*)(cl[5] + o + 0x18);
                        *q = du + *q;
                        u = u + 4;
                        q[1] = dv + q[1];
                    } while (u < uvN - 3);
                }
                for (; u < uvN; u = u + 1) {
                    float* q = (float*)(cl[5] + u * 8);
                    *q = du + *q;
                    q[1] = dv + q[1];
                }
            } else {
                int v = cl[3];
                int model = *cl * 0x10 + *(int*)((char*)self + 0x18);
                if (v < cl[4]) {
                    do {
                        *(int*)((uint)*(ushort*)(model + 10) * v + 4 + *(int*)(model + 4)) = 0;
                        int off = (uint)*(ushort*)(model + 10) * v;
                        v = v + 1;
                        *(int*)(off + *(int*)(model + 4)) = 0;
                    } while (v < cl[4]);
                }
            }
            c2 = c2 + 1;
        } while ((int)c2 < ncl);
    }
    return 1;
}

// @ 0x006e09d0
void SP_RectPackCharts(int* param_1, int* param_2, float param_3, int param_4)
{
    uint local_74 = 0;
    int local_48 = 0;
    int local_34 = 0;
    FUN_007b00d0();
    float fVar17 = (float)param_4;
    FUN_007b0fa0(param_4, param_4);

    int first = *param_2;
    param_3 = 1.0f / param_3;
    float fVar18 = 0.0f, fVar20 = 0.0f, fVar19 = 0.0f;
    uint local_70 = (param_2[1] - first) / 0x34;
    uint uVar13 = 0;
    int local_7c = 0;
    bool bVar6 = false;
    if (1 < (int)local_70) {
        int m = ((int)(local_70 - 2) >> 1) + 1;
        char* p = (char*)(first + 0x58);
        uVar13 = m * 2;
        do {
            fVar19 = ((*(float*)(p - 0x50) * param_3) * *(float*)(p - 0x38)) * *(float*)(p - 0x34) + fVar19;
            float* pf1 = (float*)(p - 0x1c);
            float* pf2 = (float*)(p - 4);
            float f16 = *(float*)p;
            p += 0x68;
            m = m - 1;
            fVar20 = ((*pf1 * param_3) * *pf2) * f16 + fVar20;
        } while (m != 0);
    }
    if (uVar13 < local_70) {
        int o = (int)(uVar13 * 0x34) + first;
        fVar18 = ((*(float*)((int)(uVar13 * 0x34) + 8 + first) * param_3) *
                  *(float*)(o + 0x24)) * *(float*)(o + 0x20);
    }
    if (3 < (int)local_70) {
        int off = 0;
        uint m = (((int)local_70 - 4) >> 2) + 1;
        local_74 = m * 4;
        do {
            *(float*)(*param_2 + off + 0x28) = *(float*)(*param_2 + 8 + off) * param_3;
            *(float*)(*param_2 + off + 0x5c) = *(float*)(*param_2 + 0x3c + off) * param_3;
            int o = off + 0x9c;
            *(float*)(off + *param_2 + 0x90) = *(float*)(off + 0x70 + *param_2) * param_3;
            off = off + 0xd0;
            m = m - 1;
            *(float*)(*param_2 + o + 0x28) = *(float*)(*param_2 + 8 + o) * param_3;
        } while (m != 0);
    }
    if (local_74 < local_70) {
        uint off = local_74 * 0x34;
        uint m = local_70 - local_74;
        do {
            int o = *param_2 + off;
            off = off + 0x34;
            m = m - 1;
            *(float*)(o + 0x28) = *(float*)(o + 8) * param_3;
        } while (m != 0);
    }

    local_74 &= 0xffffff00;
    QuickSortCRExtern((void*)*param_2, (void*)param_2[1], (int)local_74);

    do {
        float f16 = (float)local_7c;
    retry:
        if (0.9f <= f16 * 0.01f)
            goto done;
        local_7c = local_7c + 1;
        local_74 = 0;
        if (local_70 != 0) {
            uint off = 0;
            do {
                int o = *param_2 + off;
                float sc = *(float*)(o + 0x28) *
                           ((0.9f - f16 * 0.01f) / ((fVar19 + fVar20) + fVar18));
                *(float*)(o + 0x30) = sc;
                int r = FUN_007b1e70(
                    (int)(((*(float*)(o + 0x18) - *(float*)(o + 0x10)) * sc) * fVar17 + 0.5f),
                    (int)(((*(float*)(o + 0x1c) - *(float*)(o + 0x14)) * fVar17) * sc + 0.5f));
                *(int*)(o + 0x2c) = r;
                if (r < 0) {
                    bVar6 = false;
                    goto retry;
                }
                if (local_74 == local_70 - 1)
                    bVar6 = true;
                off = off + 0x34;
                local_74 = local_74 + 1;
            } while (local_74 < local_70);
        }
    } while (!bVar6);

    if (local_70 != 0) {
        uint off = 0;
        do {
            uint* pu = (uint*)(*param_2 + off);
            int* pi = (int*)(pu[0xb] * 0x20 + local_48);
            int i12 = *pi;
            int i11 = pi[1];
            int i9 = FUN_0071ddc0(*(int*)(*param_1 + pu[3] * 4), 8, 1, 2, 0xe);
            int i7 = *(int*)(*(int*)(*param_1 + pu[3] * 4) + 8);
            i9 = i9 * 0x20;
            int* pi8 = *(int**)(i7 + 0x1c + i9);
            int i4 = *(int*)(i7 + 0x14 + i9);
            ushort u3 = *(ushort*)(i7 + i9 + 0x1a);
            if (pi8 != 0)
                (**(void(***)())pi8)();
            uint u13 = *pu;
            if (u13 < pu[1]) {
                uint u14 = u3;
                float* pf = (float*)(u14 * u13 + i4);
                do {
                    float w = (float)pu[0xc];
                    *pf = 1.0f - (w * *pf + (float)i12 * (1.0f / fVar17));
                    pf[1] = -(w * pf[1] + (float)i11 * (1.0f / fVar17));
                    u13 = u13 + 1;
                    pf = (float*)((int)pf + u14);
                } while (u13 < pu[1]);
            }
            if (pi8 != 0)
                (*(void(**)(int))((int*)pi8)[1])(0);
            off = off + 0x34;
            local_70 = local_70 - 1;
        } while (local_70 != 0);
    }

done:
    if (local_34 != 0 && *(int*)(local_34 - 4) != 0)
        operator_delete__((void*)local_34);
    if (local_48 != 0 && *(int*)(local_48 - 4) != 0)
        operator_delete__((void*)local_48);
}

// @ 0x006e0e00
void Elem16VecMem::Resize(uint n)
{
    int* self = (int*)this;
    int begin = *self;
    if ((uint)(self[1] - begin >> 4) < n) {
        Elem16_s006e_0030 proto;
        proto.f0 = 0; proto.f4 = 0; proto.f8 = 8; proto.fa = 8; proto.ref = 0;
        Insert(self[1], n - (self[1] - begin >> 4), (void*)&proto);
        return;
    }
    Erase((int)(n * 0x10 + begin), self[1]);
}
