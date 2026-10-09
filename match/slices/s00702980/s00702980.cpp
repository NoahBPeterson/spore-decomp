// Slice s00702980: SP::cHierGrid / SP::cGrid container helpers (retail build).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void  operator delete(void* p); // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- thiscall stubs for callees in other slices ----
struct SwapStub { void swapWith(SwapStub* other); };                 // 0x00dc8ba0
struct GrowStub { void grow(); };                                    // 0x00702e00
struct SlotVecStub { void* mBlocks; unsigned destroy(unsigned index); }; // 0x00700ff0
struct SlotVectorStub { char pad[0x18]; unsigned create(const void* value); }; // 0x00703470
struct ListStub { void CopyFrom(ListStub* other); };                 // 0x00701170

// ---- masked external callees ----
void __stdcall HashTable_ClearBuckets(void** buckets, unsigned count); // 0x00702660
struct HashTableStub { void clearBuckets(void** buckets, unsigned count); };
void __cdecl GetParentChildInfo(unsigned cellID, unsigned* parent, unsigned* child); // 0x00700b70
unsigned __cdecl CellMaskHash(unsigned cellID);                       // 0x00700c00
void __cdecl HashFind_Cell(void* out, const unsigned* key);           // 0x00a3b2c0
void __cdecl memset0(void* dst, int v, unsigned n);                   // 0x011e073e

// ---- layouts ----
struct ObjListNode { ObjListNode* pNext; ObjListNode* pPrev; void* mObj; };
struct CellInfo { ObjListNode mHead; unsigned char mOctantFlags; char _pad[3]; };
struct CellNode { unsigned mKey; CellInfo mInfo; CellNode* mpNext; };  // next at +0x14

struct CellMap {
    unsigned m0;             // +0x00
    void**   mpBuckets;      // +0x04
    unsigned mnBucketCount;  // +0x08
    unsigned mnElementCount; // +0x0c
    unsigned m10, m14, m18;  // +0x10..0x18

    void* CloneEntry(CellNode* src);          // 0x702980
    void CopyConstruct(const CellMap& src);   // 0x702a10
    CellMap& Assign(const CellMap& src);      // 0x702f60
    CellInfo* Index(unsigned* key);           // 0x703360
};

struct cGrid {
    float mCellSize;         // +0x00
    float mHalfCellSize;     // +0x04
    float mInvCellSize;      // +0x08
    float mCellRadius;       // +0x0c
    float mCentreOriginX;    // +0x10
    float mCentreOriginY;    // +0x14
    float mCentreOriginZ;    // +0x18
    CellMap mCells;          // +0x1c
    int     mPad38;          // +0x38
    unsigned char* mMask;    // +0x3c
    unsigned char* mChildMask; // +0x40

    cGrid* CopyConstruct(const cGrid& src);     // 0x703050
    void Destroy();                           // 0x702ff0
};

struct HierGridStub {
    char pad0[0x20];
    int mNumObjects;                          // +0x20
    char pad24[0x60 - 0x24];
    SlotVecStub mSlots;                       // +0x60
    char pad64[0x78 - 0x64];
    unsigned mSlotFree;                       // +0x78
    unsigned mSlotNext;                       // +0x7c
    int  Clear(unsigned index);               // 0x702af0
    void Remove(unsigned index);              // 0x702da0
};

extern unsigned g_emptyBucket[1]; // 0x0154df28

// @ 0x00702980
void* __thiscall CellMap::CloneEntry(CellNode* src)
{
    void* node = operator new(0x18, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
    if (node) {
        *(unsigned*)node = src->mKey;
        ((ListStub*)((char*)node + 4))->CopyFrom((ListStub*)&src->mInfo.mHead);
        *(unsigned char*)((char*)node + 0x10) = src->mInfo.mOctantFlags;
    }
    *(unsigned*)((char*)node + 0x14) = 0;
    return node;
}

// @ 0x00702a10
void __thiscall CellMap::CopyConstruct(const CellMap& src)
{
    m0 = src.m0;
    mnBucketCount = src.mnBucketCount;
    mnElementCount = src.mnElementCount;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    if (mnElementCount != 0) {
        unsigned sz = mnBucketCount * 4;
        void* dst = operator new(sz + 4, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        memset0(dst, 0, sz);
        *(unsigned*)((char*)dst + sz) = 0xffffffff;
        mpBuckets = (void**)dst;
        unsigned i = 0;
        if (mnBucketCount != 0) {
            do {
                CellNode* cur = (CellNode*)src.mpBuckets[i];
                int* p = (int*)((char*)mpBuckets + i * 4);
                for (; cur != 0; cur = cur->mpNext) {
                    void* e = CloneEntry(cur);
                    *p = (int)e;
                    p = (int*)((char*)e + 0x14);
                }
                i++;
            } while (i < mnBucketCount);
        }
    } else {
        mnBucketCount = 1;
        mpBuckets = (void**)g_emptyBucket;
        mnElementCount = 0;
        m18 = 0;
    }
}

// @ 0x00702af0
int __thiscall HierGridStub::Clear(unsigned index)
{
    int result = 0;
    (void)index;
    return result;
}

// @ 0x00702da0
void __thiscall HierGridStub::Remove(unsigned index)
{
    void* deb = *(void**)&mSlots;
    unsigned char* entry = (unsigned char*)deb + (index >> 7) * 4;
    entry = (unsigned char*)(*(void**)entry) + (index & 0x7f) * 0x10;
    unsigned* slot = (unsigned*)entry;
    unsigned old = mSlotNext;
    *slot = (old & 0x3fffffff) | (*slot & 0xc0000000) | 0x80000000;
    mSlotNext = index;
    if (mSlotFree == index)
        mSlotFree = mSlots.destroy(index);
    mNumObjects -= 1;
    Clear(index);
}

// @ 0x00702f60
CellMap& __thiscall CellMap::Assign(const CellMap& src)
{
    if (this != &src) {
        CellMap tmp;
        tmp.CopyConstruct(src);
        ((SwapStub*)this)->swapWith((SwapStub*)&tmp);
        HashTable_ClearBuckets((void**)tmp.mpBuckets, tmp.mnBucketCount);
        tmp.m18 = 0;
        if (tmp.mnBucketCount > 1)
            operator delete(tmp.mpBuckets);
    }
    return *this;
}

// @ 0x00702ff0
void __thiscall cGrid::Destroy()
{
    if (mMask) {
        operator delete(mMask);
        operator delete(mChildMask);
        mMask = 0;
        mChildMask = 0;
    }
    CellMap* c = &mCells;
    ((HashTableStub*)c)->clearBuckets(c->mpBuckets, c->mnBucketCount);
    c->mnElementCount = 0;
    if (c->mnBucketCount > 1)
        operator delete(c->mpBuckets);
}

// @ 0x00703050
cGrid* __thiscall cGrid::CopyConstruct(const cGrid& src)
{
    mCellSize = src.mCellSize;
    mHalfCellSize = src.mHalfCellSize;
    mInvCellSize = src.mInvCellSize;
    mCellRadius = src.mCellRadius;
    mCentreOriginX = src.mCentreOriginX;
    mCentreOriginY = src.mCentreOriginY;
    mCentreOriginZ = src.mCentreOriginZ;
    mCells.CopyConstruct(src.mCells);
    mMask = src.mMask;
    mChildMask = src.mChildMask;
    return this;
}

// @ 0x007030a0
cGrid* __cdecl grid_uninit_copy(cGrid* first, cGrid* last, cGrid* dst)
{
    cGrid* out = dst;
    for (; first != last; first += 1) {
        out->CopyConstruct(*first);
        out += 1;
    }
    return out;
}

// @ 0x00703160
void __cdecl grid_fill_n(unsigned n, cGrid* dst, const cGrid* value)
{
    for (; n != 0; n--) {
        dst->CopyConstruct(*value);
        dst += 1;
    }
}

// @ 0x00703210
struct Vec3 { float x, y, z; };
cGrid* __cdecl grid_copy_forward(cGrid* first, cGrid* last, cGrid* dst)
{
    for (; first != last; first += 1, dst += 1) {
        dst->mCellSize = first->mCellSize;
        dst->mHalfCellSize = first->mHalfCellSize;
        dst->mInvCellSize = first->mInvCellSize;
        dst->mCellRadius = first->mCellRadius;
        *(Vec3*)&dst->mCentreOriginX = *(Vec3*)&first->mCentreOriginX;
        dst->mCells.CopyConstruct(first->mCells);
        dst->mMask = first->mMask;
        dst->mChildMask = first->mChildMask;
    }
    return dst;
}

// @ 0x007032e0
cGrid* __cdecl grid_destroy_range(cGrid* first, cGrid* last, cGrid* ended)
{
    for (; first != last; first += 1)
        first->Destroy();
    return ended;
}

// @ 0x00703360
CellInfo* __thiscall CellMap::Index(unsigned* key)
{
    char local[8];
    HashFind_Cell(local, key);
    return 0;
}

// @ 0x00703470
unsigned __thiscall SlotVectorStub::create(const void* value)
{
    char* self = (char*)this;
    unsigned index = *(unsigned*)(self + 0x1c);
    if (index == 0x3fffffff) {
        unsigned a = *(unsigned*)((char*)value + 8);
        unsigned b = *(unsigned*)value;
        unsigned c = *(unsigned*)((char*)value + 4);
        index = ((*(int*)((char*)self + 4) - *(int*)self) >> 2) * 0x80 - 0x7f + *(int*)((char*)self + 0x14);
        ((GrowStub*)self)->grow();
        void* e = (void*)(*(int*)((char*)self + 0x14) * 0x10 + *(int*)(*(int*)((char*)self + 4) - 4));
        if (e)
            *(unsigned*)e = 0x80000000;
        if (index != 0) {
            unsigned* p = (unsigned*)(((index - 1) & 0x7f) * 0x10 + *(int*)(*(int*)self + (((index - 1) >> 7) * 4)));
            *p &= 0xbfffffff;
        }
        unsigned* p2 = (unsigned*)(*(int*)(*(int*)self + (index >> 7) * 4) + (index & 0x7f) * 0x10);
        *p2 |= 0x40000000;
        *p2 &= 0x7fffffff;
        unsigned* slot = (unsigned*)((char*)p2 + 4);
        if (slot) {
            slot[0] = b;
            slot[1] = c;
            slot[2] = a;
        }
    } else {
        unsigned* p = (unsigned*)((index & 0x7f) * 0x10 + *(int*)(*(int*)self + (index >> 7) * 4));
        *(unsigned*)((char*)self + 0x1c) = *p & 0x3fffffff;
        *p &= 0x7fffffff;
        unsigned* slot = (unsigned*)((char*)p + 4);
        if (slot) {
            slot[0] = *(unsigned*)value;
            slot[1] = *(unsigned*)((char*)value + 4);
            slot[2] = *(unsigned*)((char*)value + 8);
        }
    }
    if (index < *(unsigned*)((char*)self + 0x18))
        *(unsigned*)((char*)self + 0x18) = index;
    return index;
}

// @ 0x007035a0
void __stdcall grid_destroy_count(cGrid* first, cGrid* last)
{
    if ((unsigned)first < (unsigned)last) {
        unsigned n = (((unsigned)last - (unsigned)first) - 1) / 0x44 + 1;
        cGrid* g = first;
        do {
            g->Destroy();
            g += 1;
            n--;
        } while (n != 0);
    }
}

// @ 0x00703620
cGrid* __cdecl grid_assign_forward(cGrid* first, cGrid* last, cGrid* dst)
{
    if (first == last)
        return dst;
    do {
        dst->mCellSize = first->mCellSize;
        dst->mHalfCellSize = first->mHalfCellSize;
        dst->mInvCellSize = first->mInvCellSize;
        dst->mCellRadius = first->mCellRadius;
        dst->mCentreOriginX = first->mCentreOriginX;
        dst->mCentreOriginY = first->mCentreOriginY;
        dst->mCentreOriginZ = first->mCentreOriginZ;
        dst->mCells.Assign(first->mCells);
        dst->mMask = first->mMask;
        dst->mChildMask = first->mChildMask;
        first += 1;
        dst += 1;
    } while (first != last);
    return dst;
}

// @ 0x00703690
cGrid* __cdecl grid_assign_backward(cGrid* first, cGrid* last, cGrid* dstEnd)
{
    if (first == last)
        return dstEnd;
    do {
        first -= 1;
        dstEnd -= 1;
        dstEnd->mCellSize = first->mCellSize;
        dstEnd->mHalfCellSize = first->mHalfCellSize;
        dstEnd->mInvCellSize = first->mInvCellSize;
        dstEnd->mCellRadius = first->mCellRadius;
        dstEnd->mCentreOriginX = first->mCentreOriginX;
        dstEnd->mCentreOriginY = first->mCentreOriginY;
        dstEnd->mCentreOriginZ = first->mCentreOriginZ;
        dstEnd->mCells.Assign(first->mCells);
        dstEnd->mMask = first->mMask;
        dstEnd->mChildMask = first->mChildMask;
    } while (first != last);
    return dstEnd;
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct SlotVecStub {
    void destroy();   // 0x00700ff0 (equiv t2)
};
}
