// Slice s00701a00: SP::cHierGrid query wrappers and container helpers (retail build).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void  operator delete(void* p);                                                  // 0x00f47380

// ---- masked external callees ----
void __cdecl FUN_007075e0(void* p);            // 0x007075e0

// ---- layouts ----
struct ObjListNode { ObjListNode* pNext; ObjListNode* pPrev; void* mObj; };
struct CellInfo { ObjListNode mHead; unsigned char mOctantFlags; char _pad[3]; };
struct CellNode { unsigned mKey; CellInfo mInfo; CellNode* mpNext; };  // next at +0x14

struct cGrid {
    float mCellSize;           // +0x00
    float mHalfCellSize;       // +0x04
    float mInvCellSize;        // +0x08
    float mCellRadius;         // +0x0c
    float mCentreOriginX;      // +0x10
    float mCentreOriginY;      // +0x14
    float mCentreOriginZ;      // +0x18
    char  mCells[0x20];        // +0x1c
    unsigned char* mMask;      // +0x3c
    unsigned char* mChildMask; // +0x40
};

struct HashIter { void* mpNode; void* mpBucket; };
struct HashTable {
    void* mpBuckets;       // +0x04
    unsigned mnBucketCount;// +0x08
    unsigned mnSize;       // +0x0c
    HashIter* erase(HashIter* out, CellNode* node, void** bucket);
};

struct cHierGrid {
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

    bool CullCellList(void* frustum, unsigned clipFlags, unsigned cellID, int level);
    void QueryCells(float radius, float* pos);
    void QuerySegment(float* p0, float* p1);
    void Query3(float* p0, float* p1, float r);

    int FrustumQuery(void* frustum, int count, void** buffer);
    int QuerySphereResult(float radius, float* pos, int count, void** buffer);
    int QuerySegmentResult(float* p0, float* p1, int count, void** buffer);
    int Query3Result(float* p0, float* p1, float r, int count, void** buffer);
};

extern void* g_spApp; // 0x015fd918

// @ 0x00702500
struct EhLocal { int mState; EhLocal() { mState = 0; } ~EhLocal(); };
void __fastcall list_dtor_with_eh(int* p)
{
    EhLocal local;
    FUN_007075e0(p);
    if (*p)
        operator delete((void*)*p);
}

// @ 0x00702550  (vector<_Ty>::insert, 4-byte elements)
struct PtrVec { void** mpBegin; void** mpEnd; void** mpCap; void insert(void** pos, void** value); };
void __cdecl Vec_DoInsertValue(void* dst, void* src, int n);     // 0x011e0744
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
    int cap = (int)((char*)end - (char*)mpBegin) >> 2;
    if (cap == 0)
        cap = 1;
    else
        cap *= 2;
    void* dst = (void*)operator new(cap * 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int off = (int)((char*)pos - (char*)mpBegin);
    mpBegin = (void**)dst;
    mpEnd = (void**)((char*)dst + off);
    mpCap = (void**)((char*)dst + cap * 4);
}

// @ 0x00702660  (free every bucket chain of a hash table's bucket array)
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
int __thiscall cHierGrid::FrustumQuery(void* frustum, int count, void** buffer)
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
int __thiscall cHierGrid::QuerySphereResult(float radius, float* pos, int count, void** buffer)
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
int __thiscall cHierGrid::QuerySegmentResult(float* p0, float* p1, int count, void** buffer)
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
int __thiscall cHierGrid::Query3Result(float* p0, float* p1, float r, int count, void** buffer)
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
HashIter* __thiscall HashTable::erase(HashIter* out, CellNode* node, void** bucket)
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

// ---- helpers for the range queries ----
static CellNode* FindKey(HashTable* ht, unsigned key)
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

extern const uint16_t g_mortonTable[32]; // 0x015352a8

static unsigned BuildCellID(unsigned x, unsigned y, unsigned z)
{
    unsigned v = (g_mortonTable[x >> 5]
                | ((g_mortonTable[z >> 5] * 2 | g_mortonTable[y >> 5]) * 2)) << 0xd;
    v = (v | g_mortonTable[z & 0x1f]) * 2 | g_mortonTable[y & 0x1f];
    v = v * 2 | g_mortonTable[x & 0x1f];
    return v;
}

// @ 0x00701a00  (range query over two world-space endpoints; no radius filter)
void __thiscall cHierGrid::QuerySegment(float* p0, float* p1)
{
    float x0 = p0[0], y0 = p0[1], z0 = p0[2];
    float x1 = p1[0], y1 = p1[1], z1 = p1[2];
    float ox = mOriginX, oy = mOriginY, oz = mOriginZ;
    int level = mTopLevel;
    if (level > mLeafLevel)
        return;
    int off = level * 0x44;
    for (;;) {
        cGrid* grid = (cGrid*)((char*)mGridBegin + off);
        if (*(int*)((char*)grid + 0x28) != 0 && *(int*)((char*)grid + 0x3c) != 0) {
            float inv = grid->mInvCellSize;
            float cr = grid->mCellRadius;
            unsigned n = 1u << level;
            int minx = (int)((x0 - ox - cr) * inv);
            int maxx = (int)((x1 - ox + cr) * inv);
            int miny = (int)((y0 - oy - cr) * inv);
            int maxy = (int)((y1 - oy + cr) * inv);
            int minz = (int)((z0 - oz - cr) * inv);
            int maxz = (int)((z1 - oz + cr) * inv);
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
                            HashTable* ht = (HashTable*)grid->mCells;
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
                break;
        }
        level++;
        off += 0x44;
        if (level > mLeafLevel)
            break;
    }
}

// @ 0x00701e40  (three-argument volume query)
// PARTIAL: only the entry guard and per-level scan skeleton are reconstructed; the
// per-cell slab intersection and morton accumulation are not yet reproduced.
void __thiscall cHierGrid::Query3(float* p0, float* p1, float r)
{
    if (mTopLevel > mLeafLevel)
        return;
    (void)p0; (void)p1; (void)r;
}
