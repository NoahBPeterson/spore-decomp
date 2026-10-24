// src/game/SPEngine/SPGraphicsHierGrid.cpp -- migrated from slice(s) s00703700, s00702980, s00701a00, s00700da0, s006ffe00 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsHierGrid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "SP/cHierGrid.h"
#include "SP/cGrid.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned short g_cellTable[];   // 0x15352a8, 32 ushort entries

// ---- items of slice s006ffe00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned short g_cellTable[];   // 0x15352a8, 32 ushort entries
// ---- items of slice s006ffe00 end

// ---- items of slice s00700da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint16_t g_mortonTable[32]; // 0x015352a8
#pragma warning(disable:4035)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void  operator delete(void* p);                                                  // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
inline void* operator new(size_t, void* p) { return p; }
void* __cdecl EA_new(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
unsigned __cdecl CellMaskHash(unsigned cellID);                              // 0x00700c00
void     __cdecl ChildCellIDs(unsigned cellID, unsigned* out8);              // 0x00700bb0
// eastl hashtable<unsigned, cCellInfo>::find (0x00a3b2c0) is a member: ECX = the table, the two-word
// iterator comes back through a hidden return slot, the key by reference; `ret 8`.
struct cFrustumCullStub { unsigned TestSphere(const float* a, const float* b, unsigned flags); }; // 0x00700120
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}
struct cGrid {                 // size 0x44
    float mCellSize;           // +0x00
    float mHalfCellSize;       // +0x04
    float mInvCellSize;        // +0x08
    float mCellRadius;         // +0x0c
    float mCentreOriginX;      // +0x10
    float mCentreOriginY;      // +0x14
    float mCentreOriginZ;      // +0x18
    char  mCells[0x20];        // +0x1c (eastl hash_map<unsigned, cCellInfo>)
    unsigned char* mMask;      // +0x3c
    unsigned char* mChildMask; // +0x40
};
struct ObjListNode { ObjListNode* pNext; ObjListNode* pPrev; void* mObj; };
struct CellInfo { ObjListNode mHead; unsigned char mOctantFlags; char _pad[3]; };
struct CellNode { unsigned mKey; CellInfo mInfo; CellNode* mpNext; };   // next at +0x14
struct cHierGrid {                       // size 0x78
    float mOriginX, mOriginY, mOriginZ;  // +0x00
    float mSize;                         // +0x0c
    float mInvSize;                      // +0x10
    int   mMaxLevel;                     // +0x14
    int   mTopLevel;                     // +0x18
    int   mLeafLevel;                    // +0x1c
    int   mNumObjects;                   // +0x20
    cGrid* mGridBegin;                   // +0x24
    cGrid* mGridEnd;                     // +0x28
    cGrid* mGridCap;                     // +0x2c
    int   mGridAlloc;                    // +0x30
    char  mOutOfGrid[0x10];              // +0x34 (eastl::list<void*>)
    void** mQueryListIt;                 // +0x44
    void** mQueryListEnd;                // +0x48
    char  _pad4c[0x0c];                  // +0x4c
    char  mObjInfoSlots[0x1c];           // +0x58
    bool  mDebugDraw;                    // +0x74

    unsigned CellFromPos(float px, float py, float pz, unsigned char level);
    bool     CullCellList(void* frustum, unsigned clipFlags, unsigned cellID, int level);
    float*   QueryCells(float radius, float* pos);
};
struct HashTable;
struct HashIterator { CellNode* mpNode; void** mpBucket; };

struct HashTable {                  // the eastl hashtable embedded in cGrid::mCells
    int _m0;                        // +0x00
    void** mpBuckets;               // +0x04 (mpBuckets[mnBucketCount] is the end node)
    unsigned mnBucketCount;         // +0x08
    unsigned mnSize;                // +0x0c (checked as "table empty" before a lookup)
    HashIterator Find(const unsigned& key) const;                // 0x00a3b2c0
};
static CellNode* FindCellNode(HashTable* t, unsigned key)
{
    unsigned bucket = key % t->mnBucketCount;
    void** buckets = t->mpBuckets;
    void* end = buckets[t->mnBucketCount];
    CellNode* first = (CellNode*)buckets[bucket];
    CellNode* node = (first ? first : (CellNode*)end);
    if (node == (CellNode*)end && first != end)
        node = first;
    // eastl walks the bucket chain; the bucket array's last entry is the end node.
    for (CellNode* n = (CellNode*)buckets[bucket]; n != 0 && n != (CellNode*)end; n = n->mpNext) {
        if (n->mKey == key)
            return n;
    }
    return 0;
}
static unsigned BuildCellID(unsigned x, unsigned y, unsigned z)
{
    unsigned v = (g_mortonTable[x >> 5]
                | ((g_mortonTable[z >> 5] * 2 | g_mortonTable[y >> 5]) * 2)) << 0xd;
    v = (v | g_mortonTable[z & 0x1f]) * 2 | g_mortonTable[y & 0x1f];
    v = v * 2 | g_mortonTable[x & 0x1f];
    return v;
}
struct SlotVectorBase {
    void** mBlocks;                      // simple_deque::mBlocks.mpBegin
    unsigned destroy(unsigned index);
};
struct ListNode { ListNode* pNext; ListNode* pPrev; void* mValue; };
struct ListIterator { ListNode* mpNode; };
struct ObjList { ObjListNode* pNext; ObjListNode* pPrev; void CopyFrom(const ObjList& other); };
// ---- items of slice s00700da0 end

// ---- items of slice s00701a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_spApp; // 0x015fd918
void __cdecl FUN_007075e0(void* p);            // 0x007075e0
struct HashIter { void* mpNode; void* mpBucket; };
struct HashTable_s0070_1a00 {
    void* mpBuckets;       // +0x04
    unsigned mnBucketCount;// +0x08
    unsigned mnSize;       // +0x0c
    HashIter* erase(HashIter* out, CellNode* node, void** bucket);
};
struct cHierGrid_s0070_1a00 {
    float mOriginX, mOriginY, mOriginZ;  // +0x00
    float mSize;                         // +0x0c
    float mInvSize;                      // +0x10
    int   mMaxLevel;                     // +0x14
    int   mTopLevel;                     // +0x18
    int   mLeafLevel;                    // +0x1c
    int   mNumObjects;                   // +0x20
    cGrid* mGridBegin;                   // +0x24
    cGrid* mGridEnd;                     // +0x28
    cGrid* mGridCap;                     // +0x2c
    int   mGridAlloc;                    // +0x30
    int   _pad34;                        // +0x34
    ObjListNode mOutOfGrid;              // +0x38 (embedded sentinel)
    void** mQueryListIt;                 // +0x44
    void** mQueryListEnd;                // +0x48
    char  _pad4c[0x34];                  // +0x4c..0x7f
    bool  mDebugDraw;                    // +0x80

    bool CullCellList(void* frustum, unsigned clipFlags, unsigned cellID, int level);  // 0x007011d0 (cHierGrid::CullCellList)
    void QueryCells(float radius, float* pos);  // 0x007014c0 (cHierGrid::QueryCells)
    void QuerySegment(float* p0, float* p1);
    void Query3(float* p0, float* p1, float r);

    int FrustumQuery(void* frustum, int count, void** buffer);
    int QuerySphereResult(float radius, float* pos, int count, void** buffer);
    int QuerySegmentResult(float* p0, float* p1, int count, void** buffer);
    int Query3Result(float* p0, float* p1, float r, int count, void** buffer);
};
struct EhLocal { int mState; EhLocal() { mState = 0; } ~EhLocal(); };
struct PtrVec { void** mpBegin; void** mpEnd; void** mpCap; void insert(void** pos, void** value); };
void* __cdecl Vec_DoInsertValue(void* dst, void* src, int n);    // 0x011e0744
static CellNode* FindKey(HashTable_s0070_1a00* ht, unsigned key)
{
    void** buckets = (void**)ht->mpBuckets;
    unsigned bc = ht->mnBucketCount;
    void* end = buckets[bc];
    for (CellNode* n = (CellNode*)buckets[key % bc]; n != 0 && n != (CellNode*)end; n = n->mpNext) {
        if (n->mKey == key)
            return n;
    }
    return 0;
}
static __forceinline void CellRange(float a, float b, float m, float inv, int n, int& lo, int& hi)
{
    lo = FloorToInt((a - m) * inv);
    hi = CeilToInt((b + m) * inv);
    if (hi > 0) {
        if (lo >= n) {
            lo = n;
            hi = n;
        } else {
            if (lo < 0) lo = 0;
            if (hi >= n) hi = n;
        }
    } else {
        hi = 0;
        lo = 0;
    }
}
static __forceinline void SlabInterval(float d, int idx, float cs, float s, float& t0, float& t1)
{
    t0 = 0.0f;
    t1 = 1.0f;
    if (fabsf(d) > 0.0f) {
        float inv = 1.0f / d;
        float lo = (float)idx * cs;
        float hi = lo + cs;
        float ta = (lo - s) * inv;
        float tb = (hi - s) * inv;
        if (ta > tb) { float t = ta; ta = tb; tb = t; }
        if (0.0f > tb) {
            t1 = 0.0f;
        } else if (ta > 1.0f) {
            t0 = 1.0f;
        } else {
            if (ta > 0.0f) t0 = ta;
            if (1.0f > tb) t1 = tb;
        }
    }
}
static __forceinline void NarrowInterval(float d, int idx, float cs, float s, float a0, float a1, float& t0, float& t1)
{
    t0 = a0;
    t1 = a1;
    if (fabsf(d) > 0.0f) {
        float inv = 1.0f / d;
        float lo = (float)idx * cs;
        float hi = lo + cs;
        float ta = (lo - s) * inv;
        float tb = (hi - s) * inv;
        if (ta > tb) { float t = ta; ta = tb; tb = t; }
        if (a0 > tb) {
            t1 = a0;
        } else if (ta > a1) {
            t0 = a1;
        } else {
            if (ta > a0) t0 = ta;
            if (a1 > tb) t1 = tb;
        }
    }
}
// ---- items of slice s00701a00 end

// ---- items of slice s00702980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_emptyBucket[1]; // 0x0154df28
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct SwapStub { void swapWith(SwapStub* other); };                 // 0x00dc8ba0
struct GrowStub { void grow(); };                                    // 0x00702e00
struct SlotVecStub { void* mBlocks; unsigned destroy(unsigned index); }; // 0x00700ff0
struct SlotVectorStub { char pad[0x18]; unsigned create(const void* value); }; // 0x00703470
struct ListStub { void CopyFrom(ListStub* other); };                 // 0x00701170
void __stdcall HashTable_ClearBuckets(void** buckets, unsigned count); // 0x00702660
struct HashTableStub { void clearBuckets(void** buckets, unsigned count); };
void __cdecl GetParentChildInfo(unsigned cellID, unsigned* parent, unsigned* child); // 0x00700b70
void __cdecl memset0(void* dst, int v, unsigned n);                   // 0x011e073e
struct CellInfo_s0070_2980 {
    ObjListNode mHead;
    unsigned char mOctantFlags;
    CellInfo_s0070_2980() { mHead.pNext = &mHead; mHead.pPrev = &mHead; mOctantFlags = 0; }
    ~CellInfo_s0070_2980() {
        ObjListNode* p = mHead.pNext;
        while (p != &mHead) {
            ObjListNode* n = p->pNext;
            operator delete(p);
            p = n;
        }
    }
};
struct CellNode_s0070_2980 { unsigned mKey; CellInfo_s0070_2980 mInfo; CellNode_s0070_2980* mpNext; };  // next at +0x14
struct HashIter_s0070_2980 { CellNode_s0070_2980* mpNode; void** mpBucket; unsigned char mFlag; };
struct CellMap {
    unsigned m0;             // +0x00
    void**   mpBuckets;      // +0x04
    unsigned mnBucketCount;  // +0x08
    unsigned mnElementCount; // +0x0c
    unsigned m10, m14, m18;  // +0x10..0x18

    void* CloneEntry(CellNode_s0070_2980* src);          // 0x702980
    void CopyConstruct(const CellMap& src);   // 0x702a10
    CellMap& Assign(const CellMap& src);      // 0x702f60
    CellInfo_s0070_2980* Index(unsigned* key);           // 0x703360
    void Find(HashIter_s0070_2980* out, const unsigned* key);                 // 0x00a3b2c0
    CellNode_s0070_2980* Insert(HashIter_s0070_2980* out, CellNode_s0070_2980* node, bool growFlag);// 0x00702ea0
    HashIter_s0070_2980* Erase(HashIter_s0070_2980* out, CellNode_s0070_2980* node, void** bucket); // 0x007028e0
};
struct cGrid_s0070_2980 {
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

    cGrid_s0070_2980* CopyConstruct(const cGrid_s0070_2980& src);     // 0x703050
    void Destroy();                           // 0x702ff0
};
struct HierGridStub {
    char pad0[0x18];
    int mTopLevel;                            // +0x18
    int mLeafLevel;                           // +0x1c
    int mNumObjects;                          // +0x20
    cGrid_s0070_2980* mGrids;                            // +0x24
    char pad28[0x60 - 0x28];
    SlotVecStub mSlots;                       // +0x60
    char pad64[0x78 - 0x64];
    unsigned mSlotFree;                       // +0x78
    unsigned mSlotNext;                       // +0x7c
    int  Clear(unsigned index);               // 0x702af0
    void Remove(unsigned index);              // 0x702da0
};
struct SlotRec {            // 0x10-byte slot record, +4 of the slot (slot link word is at +0)
    int      mGrid;         // +0x04
    unsigned mKey;          // +0x08   (0xffffffff when the slot is free)
    void*    mPtr;          // +0x0c
};
struct Vec3 { float x, y, z; };
namespace __equiv_ann1 {
struct SlotVecStub {
    void destroy();   // 0x00700ff0 (equiv t2)
};
}
// ---- items of slice s00702980 end

// ---- items of slice s00703700 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __cdecl SlotVectorGrow(void* self);                                  // 0x00702e00
void __cdecl SlotVectorDestroy(void* self, unsigned index);               // 0x00700ff0
void __cdecl HashMapFindIdx(void* self, void* key);                       // 0x00703360
unsigned __cdecl CellFromPos(void* self, float x, float y, float z, unsigned char level); // 0x00700da0
struct cGrid_s0070_3700 {
    float mCellSize;         // +0x00
    float mHalfCellSize;     // +0x04
    float mInvCellSize;      // +0x08
    float mCellRadius;       // +0x0c
    float mCentreOriginX;    // +0x10
    float mCentreOriginY;    // +0x14
    float mCentreOriginZ;    // +0x18
    char  mCells[0x20];      // +0x1c
    unsigned char* mMask;    // +0x3c
    unsigned char* mChildMask; // +0x40
    void Destroy();  // 0x00702ff0 (cGrid::Destroy)
    cGrid_s0070_3700* CopyConstruct(const cGrid_s0070_3700& src);  // 0x00703050 (cGrid::CopyConstruct)
};
struct GridVec {                 // eastl::vector<cGrid,sp_vector_allocator> at cHierGrid+0x24
    cGrid_s0070_3700* mpBegin;
    cGrid_s0070_3700* mpEnd;
    cGrid_s0070_3700* mpCap;
    cGrid_s0070_3700* erase(cGrid_s0070_3700* first, cGrid_s0070_3700* last);              // 0x703da0
    void   insert(cGrid_s0070_3700* pos, unsigned n, const cGrid_s0070_3700* value); // 0x703df0
    void   destroy(cGrid_s0070_3700* first, cGrid_s0070_3700* last);            // 0x7035a0
};
struct cHierGrid_s0070_3700 {
    float mOriginX, mOriginY, mOriginZ; // +0x00
    float mSize;                        // +0x0c
    float mInvSize;                     // +0x10
    int   mMaxLevel;                    // +0x14
    int   mTopLevel;                    // +0x18
    int   mLeafLevel;                   // +0x1c
    int   mNumObjects;                  // +0x20
    GridVec mGrids;                     // +0x24
    int   m30, m34;                     // +0x30,0x34
    ObjListNode mOutOfGrid;             // +0x38 (embedded sentinel)
    void** mQueryListIt;                // +0x44
    void** mQueryListEnd;               // +0x48
    int   m4c, m50, m54;                // +0x4c (mCellStack)
    int   m58, m5c;                     // +0x58
    int   m60, m64, m68, m6c, m70, m74; // +0x60 (mObjInfoSlots)
    int   m78, m7c;                     // +0x78
    char  mDebug;                       // +0x80

    cHierGrid_s0070_3700();
    void  Add(unsigned index, float radius, const Vec3& pos, unsigned extra);
    void  Update(unsigned index, float radius, const Vec3& pos);
    unsigned CreateEntry(unsigned a, unsigned b, float c);
    bool  Shutdown();  // 0x00704060 (cHierGrid::Shutdown)
    void  Resize(unsigned n);
    bool  Init(const Vec3& origin, float size, int maxLevel);  // 0x00704260 (cHierGrid::Init)
};
cGrid_s0070_3700* __cdecl grid_assign_forward(cGrid_s0070_3700* first, cGrid_s0070_3700* last, cGrid_s0070_3700* dst); // 0x703620
void __cdecl grid_destroy_count(cGrid_s0070_3700* first, cGrid_s0070_3700* last);               // 0x7035a0
cGrid_s0070_3700* __cdecl grid_uninit_copy(cGrid_s0070_3700** out, cGrid_s0070_3700* first, cGrid_s0070_3700* last, const cGrid_s0070_3700* value); // 0x7030a0
void __cdecl grid_fill_count(unsigned n, cGrid_s0070_3700* dst, const cGrid_s0070_3700* value); // 0x703160
cGrid_s0070_3700* __cdecl grid_copy_construct(cGrid_s0070_3700* first, cGrid_s0070_3700* last, cGrid_s0070_3700* dst); // 0x703210
cGrid_s0070_3700* __cdecl grid_destroy_range(cGrid_s0070_3700* first, cGrid_s0070_3700* last, cGrid_s0070_3700* ended); // 0x7032e0
void __cdecl grid_fill_n(unsigned n, cGrid_s0070_3700* dst, const cGrid_s0070_3700* value);     // fill_n
void __cdecl grid_assign_backward(cGrid_s0070_3700* first, cGrid_s0070_3700* last, cGrid_s0070_3700* dstEnd); // 0x703690
cGrid_s0070_3700* __cdecl grid_assign_fill(cGrid_s0070_3700* first, cGrid_s0070_3700* last, const cGrid_s0070_3700* src); // 0x703c80
// ---- items of slice s00703700 end

// @ 0x00700b70
void GetParentChildInfo(unsigned a, unsigned* p2, unsigned* p3)
{
    *p3 = (((a >> 9) & 0x800) | (a & 0x400)) >> 9 | (a & 1);
    *p2 = (a >> 1) & 0x7ff7fdff;
}

// @ 0x00700bb0
void ChildCellIDs(unsigned a, int* p)
{
    int v = (int)(a & 0xfff7fdff) * 2;
    p[0] = v;
    p[1] = v + 1;
    p[2] = v + 0x400;
    p[3] = v + 0x401;
    p[4] = v + 0x100000;
    p[5] = v + 0x100001;
    p[6] = v + 0x100400;
    p[7] = v + 0x100401;
}

// @ 0x00700c00
unsigned int __cdecl FUN_00700c00(unsigned int a)
{
    unsigned int hi = a >> 20;
    unsigned int mid = a >> 10;
    return (((((g_cellTable[(hi >> 5) & 0x1f] * 2 | g_cellTable[(mid >> 5) & 0x1f]) * 2 |
               g_cellTable[(a >> 5) & 0x1f]) << 13 | g_cellTable[hi & 0x1f]) * 2 |
             g_cellTable[mid & 0x1f]) * 2) | g_cellTable[a & 0x1f];
}

// @ 0x00700c80
float __cdecl FUN_00700c80(float* a, float* b, float* c, float d)
{
    (void)a; (void)b; (void)c; (void)d;
    return 0.0f;
}

// @ 0x00700da0
unsigned __thiscall cHierGrid::CellFromPos(float px, float py, float pz, unsigned char level)
{
    float dx  = (px - mOriginX) * mInvSize;
    float dy  = (py - mOriginY) * mInvSize;
    float dz  = (pz - mOriginZ) * mInvSize;
    int   n   = 1 << level;
    float fn  = (float)n;
    float vx  = dx * fn;
    int   ix  = FloorToInt(vx);
    if (ix < 0 || ix >= n)
        return 0xffffffff;
    float vy = dy * fn;
    int   iy = FloorToInt(vy);
    if (iy < 0 || iy >= n)
        return 0xffffffff;
    float vz = dz * fn;
    int   iz = FloorToInt(vz);
    if (iz < 0 || iz >= n)
        return 0xffffffff;
    return ((iz & 0x3ff) << 10 | (iy & 0x3ff)) << 10 | (ix & 0x3ff);
}

// @ 0x00700ed0
void __fastcall free_holder(void** holder)
{
    if (*holder)
        operator delete(*holder);
}

// @ 0x00700f90
void __fastcall list_free_anchor0(ObjListNode* self)
{
    ObjListNode* n = self->pNext;
    if (n == self)
        return;
    do {
        ObjListNode* cur = n;
        n = n->pNext;
        operator delete(cur);
    } while (n != self);
}

// @ 0x00700fc0
void __fastcall list_free_anchor4(void* self)
{
    ObjListNode* n = *(ObjListNode**)((char*)self + 4);
    ObjListNode* anchor = (ObjListNode*)((char*)self + 4);
    if (n == anchor)
        return;
    do {
        ObjListNode* cur = n;
        n = n->pNext;
        operator delete(cur);
    } while (n != anchor);
}

// @ 0x00700ff0
unsigned __thiscall SlotVectorBase::destroy(unsigned index)
{
    char* blocks = (char*)*(void**)this;
    unsigned info;
    do {
        info = *(unsigned*)(*(char**)(blocks + (index >> 7) * 4) + (index & 0x7f) * 0x10);
        if ((info >> 30) & 1)
            return 0x3fffffff;
        index++;
        info = *(unsigned*)(*(char**)(blocks + (index >> 7) * 4) + (index & 0x7f) * 0x10);
    } while ((int)info < 0);
    return index;
}

// @ 0x00701050
ListNode** __stdcall list_insert_before(ListNode** out, ListIterator position, void** value)
{
    ListNode* node = (ListNode*)EA_new(0xc, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (&node->mValue)
        new (&node->mValue) void*(*value);
    node->pNext = position.mpNode;
    node->pPrev = position.mpNode->pPrev;
    position.mpNode->pPrev->pNext = node;
    ListNode** r = out;
    position.mpNode->pPrev = node;
    *r = node;
    return r;
}

// @ 0x007010b0
void __stdcall list_insert_range(ListNode* pos, ListIterator first, ListIterator last, int tag)
{
    for (; first.mpNode != last.mpNode; first.mpNode = first.mpNode->pNext) {
        ListNode* node = (ListNode*)EA_new(0xc, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if (&node->mValue)
            new (&node->mValue) void*(first.mpNode->mValue);
        node->pNext = pos;
        node->pPrev = pos->pPrev;
        pos->pPrev->pNext = node;
        pos->pPrev = node;
    }
}

// @ 0x00701110
bool __cdecl hashtable_bucket_nonempty(HashTable* t, const unsigned* key)
{
    unsigned bucket = *key % t->mnBucketCount;
    CellNode* head  = (CellNode*)t->mpBuckets[bucket];
    CellNode* end   = (CellNode*)t->mpBuckets[t->mnBucketCount];
    // the original materialises the begin() iterator -- {node, &bucket} -- and compares it with end()
    HashIterator it;
    if (head != 0) {
        it.mpNode   = head;
        it.mpBucket = &t->mpBuckets[bucket];
    } else {
        it.mpNode   = end;
        it.mpBucket = &t->mpBuckets[t->mnBucketCount];
    }
    return it.mpNode != end;
}

// @ 0x00701170
void __thiscall ObjList::CopyFrom(const ObjList& other)
{
    pNext = (ObjListNode*)this;
    pPrev = (ObjListNode*)this;
    list_insert_range((ListNode*)this,
                      *(ListIterator*)&other.pNext,
                      *(ListIterator*)&other,
                      0);
}

// @ 0x007011d0
bool __thiscall cHierGrid::CullCellList(void* frustum, unsigned clipFlags, unsigned cellID, int level)
{
    cGrid* grid = mGridBegin + level;
    unsigned flags = clipFlags;

    if (clipFlags & 0x100) {
        // the original passes two float[3] corners (min at +0x24, max at +0x18 of its frame); the callee
        // reads three floats through each pointer, so the corners must be real arrays here as well
        float cs = grid->mCellSize;
        float minCorner[3], maxCorner[3];
        minCorner[0] = (float)(cellID & 0x3ff) * cs + mOriginX - cs;
        minCorner[1] = (float)((cellID >> 10) & 0x3ff) * cs + mOriginY - cs;
        minCorner[2] = (float)((cellID >> 20) & 0x3ff) * cs + mOriginZ - cs;
        float r = cs * 3.0f;
        maxCorner[0] = minCorner[0] + r;
        maxCorner[1] = minCorner[1] + r;
        maxCorner[2] = minCorner[2] + r;
        flags = ((cFrustumCullStub*)frustum)->TestSphere(minCorner, maxCorner, flags);
    }

    if ((flags & 0x40) != 0 && level != 0)
        return true;

    cGrid* g = mGridBegin + level;
    unsigned char* mask = g->mMask;
    bool inCell = false;
    if (mask != 0) {
        unsigned h = CellMaskHash(cellID);
        inCell = (mask[h >> 3] & (1 << (h & 7))) != 0;
    } else {
        HashTable* ht = (HashTable*)g->mCells;
        if (ht->mnSize != 0)
            inCell = hashtable_bucket_nonempty(ht, &cellID);
    }

    if (inCell) {
        HashTable* ht = (HashTable*)g->mCells;
        HashIterator found = ht->Find(cellID);
        CellNode* end = (CellNode*)ht->mpBuckets[ht->mnBucketCount];
        if (found.mpNode != end) {
            CellInfo* ci = &found.mpNode->mInfo;
            ObjListNode* a = &ci->mHead;
            for (ObjListNode* it = a->pNext; it != a; it = it->pNext) {
                if (mQueryListIt == mQueryListEnd)
                    return true;
                *mQueryListIt = it->mObj;
                mQueryListIt++;
            }
            if (level == mLeafLevel) {
                ci->mOctantFlags = 0;
                return true;
            }
            cGrid* g2 = mGridBegin + (level + 1);
            unsigned char cf;
            if (g2->mChildMask != 0) {
                unsigned h = CellMaskHash(cellID);
                cf = g2->mMask[h] | g2->mChildMask[h];
            } else {
                cf = ci->mOctantFlags;
            }
            if (cf != 0) {
                unsigned childIDs[8];
                ChildCellIDs(cellID, childIDs);
                unsigned bit = 1;
                for (int i = 0; i < 8; i++, bit <<= 1) {
                    if (bit & cf) {
                        if (!CullCellList(frustum, flags, childIDs[i], level + 1))
                            ci->mOctantFlags &= ~(1 << i);
                    }
                }
            }
            return true;
        }
    }

    if (level == mLeafLevel)
        return false;

    unsigned childIDs[8];
    ChildCellIDs(cellID, childIDs);
    cGrid* g2 = mGridBegin + (level + 1);
    unsigned char m = 0xff;
    if (g2->mMask != 0) {
        unsigned h = CellMaskHash(cellID);
        m = g2->mChildMask[h] | g2->mMask[h];
    }
    unsigned char bits = 0;
    unsigned bit = 1;
    for (int i = 0; i < 8; i++, bit <<= 1) {
        if (((unsigned)m & bit) == 0)
            continue;
        if (CullCellList(frustum, flags, childIDs[i], level + 1))
            bits |= (1 << i);
    }
    return bits != 0;
}

// @ 0x007014c0
// The retail symbol declares this void, but EAX is live at every exit and the caller sees it as the
// return value, so each exit below returns what the original's EAX holds there (verified against
// the disassembly; equiv reports these as eax differences):
//   level > mLeafLevel at entry            -> the pos argument (0x00701510 jumps out with EAX = pos)
//   grid without mnSize/mMask, loop level over -> the address of that grid (EAX = &grid)
//   minz >= maxz (empty z range)           -> minz (the z pre-test jumps out with EAX = minz)
//   range walked, any == 0 / next level over -> maxz (EAX = the z counter, which ends at maxz)
//   query list full                        -> the current list node
float* __thiscall cHierGrid::QueryCells(float radius, float* pos)
{
    int level = mTopLevel;
    if (level > mLeafLevel)
        return pos;
    float cx = pos[0], cy = pos[1], cz = pos[2];
    for (;;) {
        int maxz = 0;
        cGrid* grid = mGridBegin + level;
        HashTable* cells = (HashTable*)grid->mCells;
        if (cells->mnSize == 0 || grid->mMask == 0) {
            level++;
            if (level > mLeafLevel)
                return (float*)grid;
            continue;
        }
        float inv = grid->mInvCellSize;
        unsigned n = 1u << level;
        float r2 = (grid->mCellRadius + radius) * inv;
        float dx = (cx - mOriginX) * inv;
        float dy = (cy - mOriginY) * inv;
        float dz = (cz - mOriginZ) * inv;
        int minx = FloorToInt(dx - r2);
        int maxx = CeilToInt(dx + r2);
        int miny = FloorToInt(dy - r2);
        int maxy = CeilToInt(dy + r2);
        int minz = FloorToInt(dz - r2);
        maxz = CeilToInt(dz + r2);
        unsigned umask = ~(n - 1);
        if ((umask & ((unsigned)maxz | (unsigned)minz | (unsigned)maxy | (unsigned)miny | (unsigned)maxx | (unsigned)minx)) != 0) {
            if (((unsigned)minx & umask) != 0) minx = 0;
            if (((unsigned)maxx & umask) != 0) maxx = (int)n;
            if (((unsigned)miny & umask) != 0) miny = 0;
            if (((unsigned)maxy & umask) != 0) maxy = (int)n;
            if (((unsigned)minz & umask) != 0) minz = 0;
            if (((unsigned)maxz & umask) != 0) maxz = (int)n;
        }

        unsigned any = 0;
        int z = minz;
        if (z >= maxz)
            return (float*)minz;
        for (; z < maxz; z++) {
            for (int y = miny; y < maxy; y++) {
                for (int x = minx; x < maxx; x++) {
                    unsigned cellID = BuildCellID((unsigned)x, (unsigned)y, (unsigned)z);
                    unsigned h = cellID >> 3;
                    unsigned bit = 1u << (cellID & 7);
                    unsigned char* cm = grid->mChildMask;
                    if ((grid->mMask[h] & bit) != 0) {
                        unsigned key = ((unsigned)z << 10 | (unsigned)y) << 10 | (unsigned)x;
                        CellNode* node = FindCellNode(cells, key);
                        if (node != 0) {
                            float ox = grid->mCellSize;
                            float sx = (float)(key & 0x3ff) * ox + grid->mCentreOriginX;
                            float sy = (float)((key >> 10) & 0x3ff) * ox + grid->mCentreOriginY;
                            float sz = (float)((key >> 20) & 0x3ff) * ox + grid->mCentreOriginZ;
                            float ddx = cx - sx, ddy = cy - sy, ddz = cz - sz;
                            float rr = grid->mCellRadius + radius;
                            if (rr * rr > ddz * ddz + ddy * ddy + ddx * ddx) {
                                CellInfo* ci = &node->mInfo;
                                ObjListNode* a = &ci->mHead;
                                for (ObjListNode* it = a->pNext; it != a; it = it->pNext) {
                                    if (mQueryListIt == mQueryListEnd)
                                        return (float*)it;
                                    *mQueryListIt = it->mObj;
                                    mQueryListIt++;
                                }
                            }
                        }
                    }
                    any |= (unsigned char)cm[h] & (unsigned char)bit;
                }
            }
        }
        if (any == 0)
            return (float*)maxz;
        level++;
        if (level > mLeafLevel)
            return (float*)maxz;
    }
}

// @ 0x00701a00
void __thiscall cHierGrid_s0070_1a00::QuerySegment(float* p0, float* p1)
{
    float x0 = p0[0] - mOriginX;
    float y0 = p0[1] - mOriginY;
    float z0 = p0[2] - mOriginZ;
    float x1 = p1[0] - mOriginX;
    int level = mTopLevel;
    if (level > mLeafLevel)
        return;
    float y1 = p1[1] - mOriginY;   // read after the level test, as the retail code does
    float z1 = p1[2] - mOriginZ;
    int off = level * 0x44;
    for (;;) {
        cGrid* grid = (cGrid*)((char*)mGridBegin + off);
        if (*(int*)((char*)grid + 0x28) != 0 && *(int*)((char*)grid + 0x3c) != 0) {
            float inv = grid->mInvCellSize;
            float cr = grid->mCellRadius;
            unsigned n = 1u << level;
            int minx = (int)((x0 - cr) * inv);
            int maxx = (int)((x1 + cr) * inv);
            int miny = (int)((y0 - cr) * inv);
            int maxy = (int)((y1 + cr) * inv);
            int minz = (int)((z0 - cr) * inv);
            int maxz = (int)((z1 + cr) * inv);
            unsigned umask = ~(n - 1);
            if ((umask & ((unsigned)maxz | (unsigned)minz | (unsigned)maxy | (unsigned)miny | (unsigned)maxx | (unsigned)minx)) != 0) {
                if (((unsigned)minx & umask) != 0) minx = 0;
                if (((unsigned)maxx & umask) != 0) maxx = (int)n;
                if (((unsigned)miny & umask) != 0) miny = 0;
                if (((unsigned)maxy & umask) != 0) maxy = (int)n;
                if (((unsigned)minz & umask) != 0) minz = 0;
                if (((unsigned)maxz & umask) != 0) maxz = (int)n;
            }
            unsigned any = 0;
            for (int z = minz; z < maxz; z++) {
                for (int y = miny; y < maxy; y++) {
                    for (int x = minx; x < maxx; x++) {
                        unsigned cellID = BuildCellID((unsigned)x, (unsigned)y, (unsigned)z);
                        unsigned h = cellID >> 3;
                        unsigned bit = 1u << (cellID & 7);
                        if ((grid->mMask[h] & bit) != 0) {
                            HashTable_s0070_1a00* ht = (HashTable_s0070_1a00*)grid->mCells;
                            unsigned key = ((unsigned)z << 10 | (unsigned)y) << 10 | (unsigned)x;
                            CellNode* node = FindKey(ht, key);
                            if (node != 0) {
                                ObjListNode* a = &node->mInfo.mHead;
                                for (ObjListNode* it = a->pNext; it != a; it = it->pNext) {
                                    if (mQueryListIt == mQueryListEnd)
                                        return;
                                    *mQueryListIt = it->mObj;
                                    mQueryListIt = mQueryListIt + 1;
                                }
                            }
                        }
                        any |= (unsigned char)grid->mChildMask[h] & (unsigned char)bit;
                    }
                }
            }
            if (any == 0)
                return;               // no child cells below this one: nothing deeper to visit
        }
        level++;
        off += 0x44;
        if (level > mLeafLevel)
            return;
    }
}

// @ 0x00701e40
void __thiscall cHierGrid_s0070_1a00::Query3(float* p0, float* p1, float r)
{
    float sx = p0[0] - mOriginX;
    float sy = p0[1] - mOriginY;
    float sz = p0[2] - mOriginZ;
    float dx = (p1[0] - mOriginX) - sx;
    float dy = (p1[1] - mOriginY) - sy;
    int level = mTopLevel;
    if (level > mLeafLevel)
        return;
    float ez = p1[2] - mOriginZ;   // read after the level test, as the retail code does
    float dz = ez - sz;
    int off = level * 0x44;
    do {
        cGrid* grid = (cGrid*)((char*)mGridBegin + off);
        if (*(int*)((char*)grid + 0x28) != 0 && grid->mMask != 0) {
            float cs = grid->mCellSize;
            float m = grid->mHalfCellSize * 2.0f;
            float inv = grid->mInvCellSize;
            int n = 1 << level;
            unsigned any = 0;
            float zlo = sz, zhi = ez;
            if (sz > ez) { zlo = ez; zhi = sz; }
            int z0, z1;
            CellRange(zlo, zhi, m, inv, n, z0, z1);
            if (z1 <= z0)
                return;
            for (int z = z0; z < z1; z++) {
                float t0, t1;
                SlabInterval(dz, z, cs, sz, t0, t1);
                float ya = dy * t0 + sy;
                float yb = dy * t1 + sy;
                if (ya > yb) { float t = ya; ya = yb; yb = t; }
                int y0, y1;
                CellRange(ya, yb, m, inv, n, y0, y1);
                for (int y = y0; y < y1; y++) {
                    float u0, u1;
                    NarrowInterval(dy, y, cs, sy, t0, t1, u0, u1);
                    float xa = dx * u0 + sx;
                    float xb = dx * u1 + sx;
                    if (xa > xb) { float t = xa; xa = xb; xb = t; }
                    int x0, x1;
                    CellRange(xa, xb, m, inv, n, x0, x1);
                    for (int x = x0; x < x1; x++) {
                        unsigned cellID = BuildCellID((unsigned)x, (unsigned)y, (unsigned)z);
                        unsigned h = cellID >> 3;
                        unsigned bit = 1u << (cellID & 7);
                        if ((grid->mMask[h] & bit) != 0) {
                            HashTable_s0070_1a00* ht = (HashTable_s0070_1a00*)grid->mCells;
                            unsigned key = ((unsigned)z << 10 | (unsigned)y) << 10 | (unsigned)x;
                            CellNode* node = FindKey(ht, key);
                            if (node != 0) {
                                ObjListNode* a = &node->mInfo.mHead;
                                for (ObjListNode* it = a->pNext; it != a; it = it->pNext) {
                                    if (mQueryListIt == mQueryListEnd)
                                        return;
                                    *mQueryListIt = it->mObj;
                                    mQueryListIt = mQueryListIt + 1;
                                }
                            }
                        }
                        any |= (unsigned char)grid->mChildMask[h] & bit;
                    }
                }
            }
            if (any == 0)
                return;
        }
        level++;
        off += 0x44;
    } while (level <= mLeafLevel);
}

// @ 0x00702500
void __fastcall list_dtor_with_eh(int* p)
{
    EhLocal local;
    FUN_007075e0(p);
    if (*p)
        operator delete((void*)*p);
}

// @ 0x00702550
void __thiscall PtrVec::insert(void** pos, void** value)
{
    void** end = mpEnd;
    if (end != mpCap) {
        if (pos <= value && value < end)
            value++;
        if (end)
            *end = *(end - 1);
        int n = (int)((char*)mpEnd - 4) - (int)pos;
        void* dst = (void*)((char*)mpEnd + ((n >> 2) * -4));
        Vec_DoInsertValue(dst, pos, n);
        *pos = *value;
        mpEnd = end + 1;
        return;
    }
    // no spare capacity: allocate a bigger buffer and splice the two halves around the
    // inserted element (eastl's DoInsertValue returns its destination, so `call + n` is the
    // end of each copied run)
    int cap = (int)((char*)end - (char*)mpBegin) >> 2;
    if (cap <= 0)
        cap = 1;
    else
        cap += cap;
    void** pNew = (void**)operator new(cap * 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int head = (int)((char*)pos - (char*)mpBegin);
    void** pEnd = (void**)((char*)Vec_DoInsertValue(pNew, mpBegin, head) + (head & ~3));
    if (pEnd)
        *pEnd = *value;
    int tail = (int)((char*)end - (char*)pos);
    void** pLast = (void**)((char*)Vec_DoInsertValue(pEnd + 1, pos, tail) + (tail & ~3));
    if (mpBegin)
        operator delete(mpBegin);
    mpBegin = pNew;
    mpEnd = pLast;
    mpCap = (void**)((char*)pNew + cap * 4);
}

// @ 0x00702660
void __stdcall HashTable_ClearBuckets(CellNode** buckets, unsigned count)
{
    for (unsigned i = 0; i < count; i++) {
        CellNode* node = buckets[i];
        while (node) {
            CellNode* next = node->mpNext;
            ObjListNode* anchor = &node->mInfo.mHead;
            ObjListNode* it = anchor->pNext;
            while (it != anchor) {
                ObjListNode* nx = it->pNext;
                operator delete(it);
                it = nx;
            }
            operator delete(node);
            node = next;
        }
        buckets[i] = 0;
    }
}

// @ 0x007026d0
int __thiscall cHierGrid_s0070_1a00::FrustumQuery(void* frustum, int count, void** buffer)
{
    if (count <= 0)
        return 0;
    void* p1 = g_spApp;
    void* p2 = *(void**)((char*)p1 + 0x3c);
    mDebugDraw = *(int*)((char*)p2 + 0x40) != 0;
    mQueryListIt = buffer;
    mQueryListEnd = buffer + count;
    CullCellList(frustum, 0x100, 0, 0);
    ObjListNode* node = mOutOfGrid.pNext;
    if (mQueryListIt < mQueryListEnd) {
        do {
            if (node == &mOutOfGrid)
                break;
            *(void**)mQueryListIt = node->mObj;
            mQueryListIt = (void**)((int)mQueryListIt + 4);
            node = node->pNext;
        } while ((unsigned)mQueryListIt < (unsigned)mQueryListEnd);
    }
    int result = (int)mQueryListIt - (int)buffer;
    mQueryListIt = 0;
    mQueryListEnd = 0;
    return result >> 2;
}

// @ 0x00702760
int __thiscall cHierGrid_s0070_1a00::QuerySphereResult(float radius, float* pos, int count, void** buffer)
{
    if (count <= 0)
        return 0;
    mQueryListIt = buffer;
    mQueryListEnd = buffer + count;
    QueryCells(radius, pos);
    ObjListNode* node = mOutOfGrid.pNext;
    if (mQueryListIt < mQueryListEnd) {
        do {
            if (node == &mOutOfGrid)
                break;
            *(void**)mQueryListIt = node->mObj;
            mQueryListIt = (void**)((int)mQueryListIt + 4);
            node = node->pNext;
        } while ((unsigned)mQueryListIt < (unsigned)mQueryListEnd);
    }
    int result = (int)mQueryListIt - (int)buffer;
    mQueryListIt = 0;
    mQueryListEnd = 0;
    return result >> 2;
}

// @ 0x007027e0
int __thiscall cHierGrid_s0070_1a00::QuerySegmentResult(float* p0, float* p1, int count, void** buffer)
{
    if (count <= 0)
        return 0;
    mQueryListIt = buffer;
    mQueryListEnd = buffer + count;
    QuerySegment(p0, p1);
    ObjListNode* node = mOutOfGrid.pNext;
    if (mQueryListIt < mQueryListEnd) {
        do {
            if (node == &mOutOfGrid)
                break;
            *(void**)mQueryListIt = node->mObj;
            mQueryListIt = (void**)((int)mQueryListIt + 4);
            node = node->pNext;
        } while ((unsigned)mQueryListIt < (unsigned)mQueryListEnd);
    }
    int result = (int)mQueryListIt - (int)buffer;
    mQueryListIt = 0;
    mQueryListEnd = 0;
    return result >> 2;
}

// @ 0x00702860
int __thiscall cHierGrid_s0070_1a00::Query3Result(float* p0, float* p1, float r, int count, void** buffer)
{
    if (count <= 0)
        return 0;
    mQueryListIt = buffer;
    mQueryListEnd = buffer + count;
    Query3(p0, p1, r);
    ObjListNode* node = mOutOfGrid.pNext;
    if (mQueryListIt < mQueryListEnd) {
        do {
            if (node == &mOutOfGrid)
                break;
            *(void**)mQueryListIt = node->mObj;
            mQueryListIt = (void**)((int)mQueryListIt + 4);
            node = node->pNext;
        } while ((unsigned)mQueryListIt < (unsigned)mQueryListEnd);
    }
    int result = (int)mQueryListIt - (int)buffer;
    mQueryListIt = 0;
    mQueryListEnd = 0;
    return result >> 2;
}

// @ 0x007028e0
HashIter* __thiscall HashTable_s0070_1a00::erase(HashIter* out, CellNode* node, void** bucket)
{
    void* next = node->mpNext;
    out->mpBucket = (void*)bucket;
    out->mpNode = next;
    while (next == 0) {
        out->mpBucket = (char*)out->mpBucket + 4;
        next = *(void**)out->mpBucket;
        out->mpNode = next;
    }
    CellNode* first = (CellNode*)*bucket;
    if (first == node) {
        *bucket = node->mpNext;
    } else {
        CellNode* prev = first;
        CellNode* n = first->mpNext;
        while (n != node) { prev = n; n = n->mpNext; }
        prev->mpNext = node->mpNext;
    }
    ObjListNode* anchor = &node->mInfo.mHead;
    ObjListNode* it = anchor->pNext;
    while (it != anchor) {
        ObjListNode* nx = it->pNext;
        operator delete(it);
        it = nx;
    }
    operator delete(node);
    mnSize += -1;
    return out;
}

// @ 0x00702980
void* __thiscall CellMap::CloneEntry(CellNode_s0070_2980* src)
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
                CellNode_s0070_2980* cur = (CellNode_s0070_2980*)src.mpBuckets[i];
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
    void** blocks = (void**)mSlots.mBlocks;
    SlotRec* s = (SlotRec*)((char*)blocks[index >> 7] + (index & 0x7f) * 0x10 + 4);

    if (s->mKey == 0xffffffffu) {
        // free slot: unlink and release the cached node, return its object count
        char* R = *(char**)&s->mPtr;
        int n = *(int*)(R + 8);
        ObjListNode* a = *(ObjListNode**)(*(char**)R + 4);
        a->pNext->pPrev = a->pPrev;
        a->pPrev->pNext = a->pNext;
        operator delete(a);
        return n;
    }

    cGrid_s0070_2980* grid = (cGrid_s0070_2980*)((char*)mGrids + s->mGrid * 0x44);
    HashIter_s0070_2980 it;
    grid->mCells.Find(&it, (unsigned*)&s->mKey);
    if (it.mpNode == (CellNode_s0070_2980*)grid->mCells.mpBuckets[grid->mCells.mnBucketCount])
        return result;

    {
        char* R = *(char**)&s->mPtr;
        result = *(int*)(R + 8);
        ObjListNode* a = *(ObjListNode**)(*(char**)R + 4);
        a->pNext->pPrev = a->pPrev;
        a->pPrev->pNext = a->pNext;
        operator delete(a);
    }

    if (it.mpNode->mInfo.mHead.pNext == &it.mpNode->mInfo.mHead) {
        if (s->mGrid > 0 && it.mpNode->mInfo.mOctantFlags == 0) {
            unsigned parent = 0;
            unsigned child = 0;
            GetParentChildInfo(s->mKey, &parent, &child);
            cGrid_s0070_2980* pg = (cGrid_s0070_2980*)((char*)mGrids + (s->mGrid - 1) * 0x44);
            HashIter_s0070_2980 it2;
            pg->mCells.Find(&it2, &parent);
            if (it2.mpNode != (CellNode_s0070_2980*)pg->mCells.mpBuckets[pg->mCells.mnBucketCount])
                it2.mpNode->mInfo.mOctantFlags &= (unsigned char)~(1 << child);
        }
        if (grid->mMask != 0) {
            unsigned h = CellMaskHash(s->mKey);
            int w = (int)(h >> 3);
            unsigned char bit = 1;
            bit <<= (h & 7);
            grid->mMask[w] &= (unsigned char)~bit;
            int lvl = s->mGrid;
            while (lvl > 0 &&
                   ((cGrid_s0070_2980*)((char*)mGrids + (lvl - 1) * 0x44))->mMask != 0 &&
                   ((cGrid_s0070_2980*)((char*)mGrids + lvl * 0x44))->mMask[w] == 0 &&
                   ((cGrid_s0070_2980*)((char*)mGrids + lvl * 0x44))->mChildMask[w] == 0) {
                lvl = lvl - 1;
                unsigned char b = (unsigned char)w;
                w = w >> 3;
                unsigned char m = (unsigned char)(1 << (b & 7));
                ((cGrid_s0070_2980*)((char*)mGrids + lvl * 0x44))->mChildMask[w] &= (unsigned char)~m;
            }
        }
        HashIter_s0070_2980 out;
        grid->mCells.Erase(&out, it.mpNode, it.mpBucket);
        if (grid->mCells.mnElementCount == 0) {
            int lvl = s->mGrid;
            int leaf = mLeafLevel;
            if (lvl == mLeafLevel) {
                if (lvl == mTopLevel) {
                    mLeafLevel = 0;
                    mTopLevel = 1000;
                    return result;
                }
            }
            if (lvl == leaf) {
                mLeafLevel = leaf - 1;
                while (mLeafLevel >= mTopLevel) {
                    if (((cGrid_s0070_2980*)((char*)mGrids + mLeafLevel * 0x44))->mCells.mnElementCount != 0)
                        return result;
                    mLeafLevel = mLeafLevel - 1;
                }
                return result;
            }
            if (lvl == mTopLevel) {
                mTopLevel = mTopLevel + 1;
                while (mTopLevel < mLeafLevel) {
                    if (((cGrid_s0070_2980*)((char*)mGrids + mTopLevel * 0x44))->mCells.mnElementCount != 0)
                        return result;
                    mTopLevel = mTopLevel + 1;
                }
            }
        }
    }
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
void __thiscall cGrid_s0070_2980::Destroy()
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
cGrid_s0070_2980* __thiscall cGrid_s0070_2980::CopyConstruct(const cGrid_s0070_2980& src)
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
cGrid_s0070_2980* __cdecl grid_uninit_copy(cGrid_s0070_2980* first, cGrid_s0070_2980* last, cGrid_s0070_2980* dst)
{
    cGrid_s0070_2980* out = dst;
    for (; first != last; first += 1) {
        out->CopyConstruct(*first);
        out += 1;
    }
    return out;
}

// @ 0x00703160
void __cdecl grid_fill_n(unsigned n, cGrid_s0070_2980* dst, const cGrid_s0070_2980* value)
{
    for (; n != 0; n--) {
        dst->CopyConstruct(*value);
        dst += 1;
    }
}

// @ 0x007032e0
cGrid_s0070_2980* __cdecl grid_destroy_range(cGrid_s0070_2980* first, cGrid_s0070_2980* last, cGrid_s0070_2980* ended)
{
    for (; first != last; first += 1)
        first->Destroy();
    return ended;
}

// @ 0x00703360
CellInfo_s0070_2980* __thiscall CellMap::Index(unsigned* key)
{
    HashIter_s0070_2980 it;
    Find(&it, key);
    if (it.mpNode != (CellNode_s0070_2980*)mpBuckets[mnBucketCount])
        return (CellInfo_s0070_2980*)((char*)it.mpNode + 4);

    CellInfo_s0070_2980 info;

    CellNode_s0070_2980 node;
    node.mKey = *key;
    ((ListStub*)&node.mInfo)->CopyFrom((ListStub*)&info);
    node.mInfo.mOctantFlags = info.mOctantFlags;

    // NB: the original spills this bool literal into the (dead) incoming `key` argument slot
    // and then reloads it as a dword, so its pushed value is (key & 0xffffff00) rather than 0.
    // The callee only tests the low byte, so the value is the same `false`.
    Insert(&it, &node, false);

    return (CellInfo_s0070_2980*)((char*)it.mpNode + 4);
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
void __stdcall grid_destroy_count(cGrid_s0070_2980* first, cGrid_s0070_2980* last)
{
    if ((unsigned)first < (unsigned)last) {
        unsigned n = (((unsigned)last - (unsigned)first) - 1) / 0x44 + 1;
        cGrid_s0070_2980* g = first;
        do {
            g->Destroy();
            g += 1;
            n--;
        } while (n != 0);
    }
}

// @ 0x00703620
cGrid_s0070_2980* __cdecl grid_copy_forward(cGrid_s0070_2980* first, cGrid_s0070_2980* last, cGrid_s0070_2980* dst)
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

// @ 0x00703690
cGrid_s0070_2980* __cdecl grid_assign_backward(cGrid_s0070_2980* first, cGrid_s0070_2980* last, cGrid_s0070_2980* dstEnd)
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

// @ 0x00703700
void __thiscall cHierGrid_s0070_3700::Add(unsigned index, float radius, const Vec3& pos, unsigned extra)
{
    float thresh = (*(const float*)0x1535500 * radius) * 2.0f;
    int level = 0;
    if (mGrids.mpBegin[0].mHalfCellSize > thresh) {
        level = 0;
        int maxl = mMaxLevel;
        while (level < maxl && mGrids.mpBegin[level].mCellRadius > thresh)
            level++;
    }
    unsigned cellID = CellFromPos(this, pos.x, pos.y, pos.z, (unsigned char)level);
    if (cellID == 0xffffffff) {
        // out-of-grid object
        ObjListNode node;
        node.pNext = &mOutOfGrid;
        node.mObj = (void*)extra;
        (void)index; (void)node;
        return;
    }
    cGrid_s0070_3700* g = mGrids.mpBegin + level;
    HashMapFindIdx((char*)g->mCells, &cellID);
    (void)index;
}

// @ 0x00703b60
void __thiscall cHierGrid_s0070_3700::Update(unsigned index, float radius, const Vec3& pos)
{
    char* blocks = (char*)m60;
    char* entry = (char*)(*(void**)(blocks + (index >> 7) * 4)) + (index & 0x7f) * 0x10;
    char* data = entry + 4;
    if (*(int*)(data + 4) == -1)
        return;
    int level = *(int*)data;
    cGrid_s0070_3700* g = mGrids.mpBegin + level;
    float thresh = (*(const float*)0x1535500 * radius) * 2.0f;
    if ((g->mHalfCellSize > thresh) || (mMaxLevel <= level)) {
        if ((thresh < g->mCellSize) || (level < 1)) {
            unsigned id = CellFromPos(this, pos.x, pos.y, pos.z, (unsigned char)level);
            if (*(int*)(data + 4) == (int)id)
                return;
        }
    }
    // re-insertion path
    SlotVectorDestroy((char*)this + 0x60, index);
    Add(index, radius, pos, 0);
}

// @ 0x00703c80
cGrid_s0070_3700* __cdecl grid_assign_fill(cGrid_s0070_3700* first, cGrid_s0070_3700* last, const cGrid_s0070_3700* src)
{
    for (; first != last; first += 1) {
        first->mCellSize = src->mCellSize;
        first->mHalfCellSize = src->mHalfCellSize;
        first->mInvCellSize = src->mInvCellSize;
        first->mCellRadius = src->mCellRadius;
        *(Vec3*)&first->mCentreOriginX = *(Vec3*)&src->mCentreOriginX;
        first->CopyConstruct(src[0]);         // mCells assignment (callee masked)
        first->mMask = src->mMask;
        first->mChildMask = src->mChildMask;
    }
    return first;
}

// @ 0x00703ce0
cHierGrid_s0070_3700::cHierGrid_s0070_3700()
{
    mOriginX = 0.0f; mOriginY = 0.0f; mOriginZ = 0.0f;
    mSize = 0.0f;
    mInvSize = 0.0f;
    mMaxLevel = 0;
    mNumObjects = 0;
    mTopLevel = -1;
    mLeafLevel = -1;
    mGrids.mpBegin = 0; mGrids.mpEnd = 0; mGrids.mpCap = 0;
    mOutOfGrid.pNext = &mOutOfGrid;
    mOutOfGrid.pPrev = &mOutOfGrid;
    mQueryListIt = 0;
    mQueryListEnd = 0;
    m4c = 0; m50 = 0; m54 = 0;
    m60 = 0; m64 = 0; m68 = 0;
    m74 = 0x7f;
    m78 = 0x3fffffff;
    m7c = 0x3fffffff;
    mDebug = 0;
}

// @ 0x00703d50
unsigned __thiscall cHierGrid_s0070_3700::CreateEntry(unsigned a, unsigned b, float c)
{
    unsigned value[2] = { 0, 0 };
    unsigned id = 0;
    SlotVectorGrow(&value);
    mNumObjects += 1;
    Add(id, c, *(Vec3*)&b, a);
    return id;
}

// @ 0x00703da0
cGrid_s0070_3700* __thiscall GridVec::erase(cGrid_s0070_3700* first, cGrid_s0070_3700* last)
{
    cGrid_s0070_3700* newEnd = grid_assign_forward(last, mpEnd, first);
    destroy(newEnd, mpEnd);
    mpEnd = mpEnd - (last - first);
    return first;
}

// @ 0x00703df0
void __thiscall GridVec::insert(cGrid_s0070_3700* pos, unsigned n, const cGrid_s0070_3700* value)
{
    unsigned have = (unsigned)(mpEnd - mpBegin);
    if (n > (unsigned)(mpCap - mpEnd)) {
        cGrid_s0070_3700* newBegin = (cGrid_s0070_3700*)operator new((have + n) * 0x44, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        cGrid_s0070_3700* p = grid_copy_construct(mpBegin, pos, newBegin);
        cGrid_s0070_3700* q = grid_uninit_copy(&p, pos, mpEnd, 0);
        grid_fill_count(n, p, value);
        grid_destroy_range(mpBegin, pos, 0);
        grid_destroy_range(pos, mpEnd, 0);
        mpBegin = newBegin;
        mpEnd = q + n;
        mpCap = newBegin + have + n;
    } else {
        unsigned tail = (unsigned)(mpEnd - pos);
        if (n < tail) {
            grid_copy_construct(mpEnd - n, mpEnd, mpEnd);
            grid_assign_backward(pos, mpEnd - n, mpEnd);
            grid_assign_fill(pos, pos + n, value);
            mpEnd += n;
        } else {
            grid_uninit_copy(&mpEnd, pos, mpEnd, value);   // extend
            grid_fill_n(n - tail, mpEnd, value);
            mpEnd += n;
            grid_assign_fill(pos, pos + tail, value);
        }
    }
}

// @ 0x00704060
bool __thiscall cHierGrid_s0070_3700::Shutdown()
{
    mOriginX = 0.0f; mOriginY = 0.0f; mOriginZ = 0.0f;
    mSize = 0.0f;
    mInvSize = 0.0f;
    mLeafLevel = -1;
    mTopLevel = -1;
    cGrid_s0070_3700* begin = mGrids.mpBegin;
    cGrid_s0070_3700* end = mGrids.mpEnd;
    grid_assign_forward(end, end, begin);
    grid_destroy_count(end, end);
    mGrids.mpEnd = end - (end - begin);
    for (ObjListNode* n = mOutOfGrid.pNext; n != &mOutOfGrid; ) {
        ObjListNode* nx = n->pNext;
        operator delete(n);
        n = nx;
    }
    mOutOfGrid.pNext = &mOutOfGrid;
    mOutOfGrid.pPrev = &mOutOfGrid;
    SlotVectorDestroy((char*)this + 0x60, 0);
    m78 = 0x3fffffff;
    m7c = 0x3fffffff;
    mNumObjects = 0;
    return true;
}

// @ 0x00704140
void __thiscall cHierGrid_s0070_3700::Resize(unsigned n)
{
    unsigned have = (unsigned)(mGrids.mpEnd - mGrids.mpBegin);
    if (n > have) {
        cGrid_s0070_3700 value;
        value.mCellSize = 0.0f; value.mHalfCellSize = 0.0f; value.mInvCellSize = 0.0f; value.mCellRadius = 0.0f;
        value.mCentreOriginX = 0.0f; value.mCentreOriginY = 0.0f; value.mCentreOriginZ = 0.0f;
        value.mMask = 0; value.mChildMask = 0;
        mGrids.insert(mGrids.mpEnd, n - have, &value);
        value.Destroy();
    } else {
        mGrids.erase(mGrids.mpBegin + n, mGrids.mpEnd);
    }
}

// @ 0x00704260
bool __thiscall cHierGrid_s0070_3700::Init(const Vec3& origin, float size, int maxLevel)
{
    mOriginX = origin.x; mOriginY = origin.y; mOriginZ = origin.z;
    mSize = size;
    mInvSize = 1.0f / size;
    mMaxLevel = maxLevel;
    if (maxLevel < 1 || maxLevel > 6)
        mMaxLevel = 6;
    mNumObjects = 0;
    mTopLevel = 1000;
    mLeafLevel = 0;
    Resize((unsigned)(mMaxLevel + 1));
    for (int i = 0; i <= mMaxLevel; i++) {
        float cells = (float)(1 << (i & 0x1f));
        float cs = mSize / cells;
        cGrid_s0070_3700* g = mGrids.mpBegin + i;
        g->mCellSize = cs;
        g->mHalfCellSize = cs * 0.5f;
        g->mInvCellSize = cells / mSize;
        g->mCellRadius = (1.7392710f + 1.0f) * cs;
        float r = g->mHalfCellSize;
        g->mCentreOriginX = mOriginX + r;
        g->mCentreOriginY = mOriginY + r;
        g->mCentreOriginZ = mOriginZ + r;
    }
    return true;
}
