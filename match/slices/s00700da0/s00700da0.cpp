// Slice s00700da0: SP::cHierGrid octree culling / cell-query helpers (retail build).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void  operator delete(void* p);                                                  // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
inline void* operator new(size_t, void* p) { return p; }
void* __cdecl EA_new(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0

// ---- masked external callees ----
unsigned __cdecl CellMaskHash(unsigned cellID);                              // 0x00700c00
void     __cdecl ChildCellIDs(unsigned cellID, unsigned* out8);              // 0x00700bb0
void     __cdecl HashFind_Cell(void* out, const unsigned* key);              // 0x00a3b2c0 (eastl hashtable<...>::find)
struct cFrustumCullStub { unsigned TestSphere(const float* a, const float* b, unsigned flags); }; // 0x00700120

#pragma warning(disable:4035)
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

// ---- layouts (retail offsets verified against the disassembly) ----
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
    void     QueryCells(float radius, float* pos);
};

extern const uint16_t g_mortonTable[32]; // 0x015352a8

struct HashTable { int _m0; void** mpBuckets; unsigned mnBucketCount; unsigned mnSize; };

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
struct SlotVectorBase {
    void** mBlocks;                      // simple_deque::mBlocks.mpBegin
    unsigned destroy(unsigned index);
};
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

// @ 0x00701050  (list node insert before position; returns the out iterator)
struct ListNode { ListNode* pNext; ListNode* pPrev; void* mValue; };
struct ListIterator { ListNode* mpNode; };

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

// @ 0x007010b0  (list::insert(pos, first, last, tag): copy [first,last) before pos)
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

// @ 0x00701110  (eastl hashtable: is the bucket for *key non-empty)
bool __fastcall hashtable_bucket_nonempty(HashTable* t, const unsigned* key)
{
    void* end  = t->mpBuckets[t->mnBucketCount];
    void* head = t->mpBuckets[*key % t->mnBucketCount];
    void* node = end;
    if (head != 0)
        node = head;
    return node != end;
}

// @ 0x00701170  (copy-construct a circular object list from `other`)
struct ObjList { ObjListNode* pNext; ObjListNode* pPrev; void CopyFrom(const ObjList& other); };
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
        float cs = grid->mCellSize;
        float cx = (float)(cellID & 0x3ff) * cs + mOriginX - cs;
        float cy = (float)((cellID >> 10) & 0x3ff) * cs + mOriginY - cs;
        float cz = (float)((cellID >> 20) & 0x3ff) * cs + mOriginZ - cs;
        float r  = cs * 3.0f;
        float ex = cx + r;
        float ey = cy + r;
        float ez = cz + r;
        flags = ((cFrustumCullStub*)frustum)->TestSphere(&cx, &ex, flags);
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
        void* found[2];
        HashFind_Cell(found, &cellID);
        HashTable* ht = (HashTable*)g->mCells;
        void* end = ht->mpBuckets[ht->mnBucketCount];
        if (found[0] != end) {
            CellInfo* ci = (CellInfo*)((char*)found[0] + 4);
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
void __thiscall cHierGrid::QueryCells(float radius, float* pos)
{
    int level = mTopLevel;
    if (level > mLeafLevel)
        return;
    float cx = pos[0], cy = pos[1], cz = pos[2];
    int off = level * 0x44;
    for (;;) {
        cGrid* grid = (cGrid*)((char*)mGridBegin + off);
        if (*(int*)((char*)grid + 0x28) != 0 && *(int*)((char*)grid + 0x3c) != 0) {
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
            int maxz = CeilToInt(dz + r2);
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
                        unsigned char* cm = grid->mChildMask;
                        if ((grid->mMask[h] & bit) != 0) {
                            HashTable* ht = (HashTable*)grid->mCells;
                            unsigned key = ((unsigned)z << 10 | (unsigned)y) << 10 | (unsigned)x;
                            CellNode* node = FindCellNode(ht, key);
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
                                            return;
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
                break;
        }
        level++;
        off += 0x44;
        if (level > mLeafLevel)
            break;
    }
}
