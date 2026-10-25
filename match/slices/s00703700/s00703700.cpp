// Slice s00703700: SP::cHierGrid construction / lifetime and cGrid-vector helpers (retail build).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <string.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void  operator delete(void* p); // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- masked external callees ----
char __cdecl ReadInt32(void* stream, void* dst, int count, int flag);     // 0x0093a780
char __cdecl WriteUint32(void* stream, void* src, int count, int flag);   // 0x0093aa70
char __cdecl ReadBlocks(void* stream, int n, int flag);                   // 0x0093a890
char __cdecl ReadInto(void* stream, void* dst, int n);                    // 0x0093a6c0
void __cdecl SlotVectorGrow(void* self);                                  // 0x00702e00
void __cdecl SlotVectorDestroy(void* self, unsigned index);               // 0x00700ff0
// spstl slot_vector_base::create(void const*) — 0x00703470, this = &cHierGrid::mObjInfoSlots
struct SlotVectorStub { unsigned create(const void* value); };
void __cdecl HashMapFindIdx(void* self, void* key);                       // 0x00703360
// SP::cHierGrid::CellFromPos(position, level) — 0x00700da0, `this` in ecx.
struct CellFromPosT { unsigned calc(float x, float y, float z, unsigned char level); };

// ---- layouts ----
struct ObjListNode { ObjListNode* pNext; ObjListNode* pPrev; void* mObj; };
struct CellInfo { ObjListNode mHead; unsigned char mOctantFlags; char _pad[3]; };
struct Vec3 { float x, y, z; };

struct CellMap;                 // eastl map embedded at cGrid+0x1c (0x20 bytes)

struct cGrid {
    float mCellSize;         // +0x00
    float mHalfCellSize;     // +0x04
    float mInvCellSize;      // +0x08
    float mCellRadius;       // +0x0c
    float mCentreOriginX;    // +0x10
    float mCentreOriginY;    // +0x14
    float mCentreOriginZ;    // +0x18
    char  mCellMap[0x20];    // +0x1c
    unsigned char* mMask;    // +0x3c
    unsigned char* mChildMask; // +0x40
    void Destroy();
    cGrid* CopyConstruct(const cGrid& src);
};

// Intrusive list head used by the per-cell object lists and the out-of-grid list.
struct ListHead { void* mpNext; void* mpPrev; };

// Cell map entry: the object list head, the node pointer and the octant-propagation bytes.
struct CellInfo_s0070_2980 {
    ListHead mHead;           // +0x00  self-linked when the cell exists
    void*    mNode;           // +0x08
    unsigned char mFlags;     // +0x0c
    char     _pad0[3];
    unsigned char mOctant;    // +0x10  per-octant "child present" mask
};

// CellMap::Assign(CellMap const&) — 0x00702f60
struct CellMap {
    void*    mpSomething;      // +0x00
    void**   mpBuckets;        // +0x04
    unsigned mBucketCount;     // +0x08
    void*    mpEnd;            // +0x0c (guess; unused here)
    char     raw[0x10];        // +0x10
    CellMap& Assign(const CellMap& src);
    CellInfo_s0070_2980* Index(unsigned* pKey);   // 0x00703360  find-or-insert the cell entry
};

// Intrusive-list insert: allocate a 0xc-byte node holding `*obj` and splice it in before `pos`;
// returns the node through `out`.  Callee cleans the stack (`ret 0xc`).
void __stdcall list_insert_before(void** out, void* pos, void** obj);      // 0x00701050

struct GridVec {                 // eastl::vector<cGrid,sp_vector_allocator> at cHierGrid+0x24
    cGrid* mpBegin;
    cGrid* mpEnd;
    cGrid* mpCap;
    cGrid* erase(cGrid* first, cGrid* last);              // 0x703da0
    void   insert(cGrid* pos, unsigned n, const cGrid* value); // 0x703df0
    void   destroy(cGrid* first, cGrid* last);            // 0x7035a0
};

struct cHierGrid {
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

    cHierGrid();
    void  Add(unsigned index, float radius, const Vec3& pos, unsigned extra);
    void  Update(unsigned index, float radius, const Vec3& pos);
    unsigned CreateEntry(float c, const Vec3* b, unsigned a);
    bool  Shutdown();
    void  Resize(unsigned n);
    bool  Init(const Vec3& origin, float size, int maxLevel);
};

struct ImageData {
    char pad0[0x1c];
    int   mWidth;    // +0x1c
    int   mHeight;   // +0x20
    int   mFlags;    // +0x24
    void* mData;     // +0x28
    int   mPitch;    // +0x2c
};

struct Stream { void* mVtbl; };
typedef char (__thiscall *StreamWriteFn)(void* self, void* data, unsigned count);

// helpers from slice 32 (external)
cGrid* __cdecl grid_assign_forward(cGrid* first, cGrid* last, cGrid* dst); // 0x703620
void __cdecl grid_destroy_count(cGrid* first, cGrid* last);               // 0x7035a0
cGrid* __cdecl grid_uninit_copy(cGrid** out, cGrid* first, cGrid* last, const cGrid* value); // 0x7030a0
void __cdecl grid_fill_count(unsigned n, cGrid* dst, const cGrid* value); // 0x703160
cGrid* __cdecl grid_copy_construct(cGrid* first, cGrid* last, cGrid* dst); // 0x703210
cGrid* __cdecl grid_destroy_range(cGrid* first, cGrid* last, cGrid* ended); // 0x7032e0
void __cdecl grid_fill_n(cGrid* dst, unsigned n, const cGrid* value);   // 0x703160
void __cdecl grid_assign_backward(cGrid* first, cGrid* last, cGrid* dstEnd); // 0x703690
cGrid* __cdecl grid_assign_fill(cGrid* first, cGrid* last, const cGrid* src); // 0x703c80

// A per-object slot record inside `mObjInfoSlots`.  Blocks are `void*[128]` and each index is a
// 0x10-byte record whose first dword is unused here; the fields live at +0x04/+0x08/+0x0c.
struct SlotRec26 {
    unsigned     mUnused0;    // +0x00
    int          mLevel;      // +0x04  level the object was filed at (-1 = out of grid)
    int          mCell;       // +0x08  cell id at that level     (-1 = out of grid)
    void*        mNode;       // +0x0c  list node owning the object
    unsigned char mFlags;     // +0x10  octant propagation flag (written via +0x0c relative to mNode)
};
// The record as the original addresses it: the base pointer handed around points at +0x04, so the
// three named dwords sit at relative +0/+4/+8 and the flag byte at relative +0x0c.
struct SlotRef { int mLevel; int mCell; void* mNode; unsigned char mFlags; char _pad[3]; };

// The cell map's inlined hash-table find returns an entry whose octant mask byte lives at +0x10.
typedef CellInfo_s0070_2980 CellEntry;

short __cdecl CellHash(unsigned id);                                          // 0x00700c00

// The inlined eastl::hashtable find the original performs when walking ancestor levels: look the
// key up in the map's bucket chain and return the entry, or 0 when absent. Node layout: the key
// is the first dword after the intrusive links and the cell entry follows it.
struct CellMapNode {
    CellMapNode* mpNext;   // +0x00
    unsigned*    mpBucket; // +0x04
    unsigned     mKey;     // +0x08
    CellEntry    mEntry;   // +0x0c
};
inline CellEntry* FindCell(CellMap* map, unsigned key)
{
    unsigned idx = key % map->mBucketCount;
    CellMapNode* n = (CellMapNode*)map->mpBuckets[idx];
    CellMapNode* end = (CellMapNode*)map->mpBuckets[map->mBucketCount];
    while (n != end) {
        if (n->mKey == key)
            return &n->mEntry;
        n = n->mpNext;
    }
    return 0;
}
// @ 0x00703700  (insert one object into the hierarchy)
void __thiscall cHierGrid::Add(unsigned index, float radius, const Vec3& pos, unsigned extra)
{
    float thresh = (*(const float*)0x1535500 * radius) * 2.0f;
    int level = 0;
    if (mGrids.mpBegin[0].mHalfCellSize > thresh) {
        // Walk up while the next level's half-cell size still exceeds the radius threshold; the
        // grid the object lands in is the first level that is fine enough (at most mMaxLevel).
        while (level < mMaxLevel && mGrids.mpBegin[level + 1].mHalfCellSize > thresh)
            level++;
    }
    unsigned cellID = ((CellFromPosT*)this)->calc(pos.x, pos.y, pos.z, (unsigned char)level);
    int   iLevel = level;

    unsigned block = *(unsigned*)((char*)m60 + (index >> 7) * 4);
    // The record is the 0x10-byte slot starting 4 bytes into the block-resident record; the three
    // named dwords (level / cell / node) therefore land at block offsets +0x04/+0x08/+0x0c.
    SlotRef* slot = (SlotRef*)(block + (index & 0x7f) * 0x10 + 4);

    if ((int)cellID == -1) {
        // Out-of-grid object: record the -1 sentinel and append the object to the out-of-grid list.
        slot->mLevel = -1;
        slot->mCell  = -1;
        void* obj = (void*)(uintptr_t)extra;
        void* out = 0;
        list_insert_before(&out, (void*)&mOutOfGrid, &obj);
        slot->mNode = out;
        return;
    }

    slot->mLevel = iLevel;
    slot->mCell  = (int)cellID;

    cGrid* g = mGrids.mpBegin + iLevel;
    CellInfo_s0070_2980* entry = ((CellMap*)g->mCellMap)->Index(&cellID);
    bool created = (*((void**)&entry->mHead) == (void*)entry);
    void* obj = (void*)(uintptr_t)extra;
    void* out = 0;
    list_insert_before(&out, entry, &obj);
    slot->mNode = out;

    if (!created)
        return;

    if ((int)iLevel > mLeafLevel) mLeafLevel = iLevel;
    if ((int)iLevel < mTopLevel)  mTopLevel  = iLevel;

    if (iLevel < 7) {
        if (g->mMask == 0) {
            unsigned sz = (iLevel == 0) ? 4u
                        : (((1u << ((iLevel * 3 - 3) & 0x1f)) + 3u) & ~3u);
            g->mMask      = (unsigned char*)operator new(sz, "Graphics", 0, 0, 0, 0);
            memset(g->mMask, 0, sz);
            g->mChildMask = (unsigned char*)operator new(sz, "Graphics", 0, 0, 0, 0);
            memset(g->mChildMask, 0, sz);

            for (int j = iLevel - 1; j >= 0; --j) {
                if (mGrids.mpBegin[j].mMask != 0)
                    break;
                unsigned s2 = (j == 0) ? 4u
                            : (((1u << ((j * 3 - 3) & 0x1f)) + 3u) & ~3u);
                mGrids.mpBegin[j].mMask      = (unsigned char*)operator new(s2, "Graphics", 0, 0, 0, 0);
                mGrids.mpBegin[j].mChildMask = (unsigned char*)operator new(s2, "Graphics", 0, 0, 0, 0);
                memset(mGrids.mpBegin[j].mMask, 0, s2);
                memset(mGrids.mpBegin[j].mChildMask, 0, s2);
            }
        }

        short h = CellHash(cellID);
        unsigned byteIdx = (unsigned)h >> 3;
        unsigned char bit = (unsigned char)(1u << (h & 7));
        bool wasUnset = (g->mMask[byteIdx] == 0) && (g->mChildMask[byteIdx] == 0);
        g->mMask[byteIdx] |= bit;

        if (wasUnset) {
            int j = iLevel - 1;
            int bi = (int)byteIdx;
            bool probe = true;
            while (probe && j >= 0) {
                cGrid* gp = mGrids.mpBegin + j;
                if (gp->mMask == 0)
                    break;
                unsigned i2 = (unsigned)(bi >> 3);
                unsigned char b2 = (unsigned char)(1u << (bi & 7));
                probe = (gp->mMask[i2] == 0) && (gp->mChildMask[i2] == 0);
                gp->mChildMask[i2] |= b2;
                --j;
            }
        }
    }

    // Propagate the cell into the ancestor levels: walk one grid up at a time and, for each
    // ancestor whose cell map does not already contain this cell, set the octant bit on the
    // parent cell entry (and record the propagation flag on this level's slot).
    unsigned octantIdx = (unsigned)(((cellID >> 18) & 4u) | ((cellID >> 9) & 1u) | (cellID & 1u));
    for (int lv = iLevel - 1; lv >= 0; --lv) {
        cGrid* gp = mGrids.mpBegin + lv;
        CellInfo_s0070_2980* found = FindCell((CellMap*)gp->mCellMap, cellID);
        if (found == 0)
            break;
        unsigned char b = (unsigned char)(1u << (octantIdx & 7));
        if ((int)iLevel < mLeafLevel && (found->mOctant & b) != 0) {
            entry->mFlags = 0xff;
            found->mOctant |= b;
            return;
        }
        entry->mFlags = 0;
        found->mOctant |= b;
    }
    (void)thresh;
}

// @ 0x00703b60
void __thiscall cHierGrid::Update(unsigned index, float radius, const Vec3& pos)
{
    char* blocks = (char*)m60;
    char* entry = (char*)(*(void**)(blocks + (index >> 7) * 4)) + (index & 0x7f) * 0x10;
    char* data = entry + 4;
    if (*(int*)(data + 4) == -1)
        return;
    int level = *(int*)data;
    cGrid* g = mGrids.mpBegin + level;
    float thresh = (*(const float*)0x1535500 * radius) * 2.0f;
    if ((g->mHalfCellSize > thresh) || (mMaxLevel <= level)) {
        if ((thresh < g->mCellSize) || (level < 1)) {
            unsigned id = ((CellFromPosT*)this)->calc(pos.x, pos.y, pos.z, (unsigned char)level);
            if (*(int*)(data + 4) == (int)id)
                return;
        }
    }
    // re-insertion path
    SlotVectorDestroy((char*)this + 0x60, index);
    Add(index, radius, pos, 0);
}

// @ 0x00703c80
cGrid* __cdecl grid_assign_fill(cGrid* first, cGrid* last, const cGrid* src)
{
    for (; first != last; first += 1) {
        first->mCellSize = src->mCellSize;
        first->mHalfCellSize = src->mHalfCellSize;
        first->mInvCellSize = src->mInvCellSize;
        first->mCellRadius = src->mCellRadius;
        *(Vec3*)&first->mCentreOriginX = *(Vec3*)&src->mCentreOriginX;
        ((CellMap*)first->mCellMap)->Assign(*(const CellMap*)src->mCellMap);
        first->mMask = src->mMask;
        first->mChildMask = src->mChildMask;
    }
    return first;
}

// @ 0x00703ce0
cHierGrid::cHierGrid()
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
unsigned __thiscall cHierGrid::CreateEntry(float c, const Vec3* b, unsigned a)
{
    unsigned value[3];
    value[2] = 0;
    unsigned id = ((SlotVectorStub*)((char*)this + 0x60))->create(value);
    mNumObjects += 1;
    Add(id, c, *b, a);
    return id;
}

// @ 0x00703da0
cGrid* __thiscall GridVec::erase(cGrid* first, cGrid* last)
{
    cGrid* newEnd = grid_assign_forward(last, mpEnd, first);
    destroy(newEnd, mpEnd);
    mpEnd = mpEnd - (last - first);
    return first;
}

// @ 0x00703df0  (vector<cGrid>::insert)
void __thiscall GridVec::insert(cGrid* pos, unsigned n, const cGrid* value)
{
    if ((unsigned)(mpCap - mpEnd) < n) {
        // ---- grow path ----
        unsigned len = (unsigned)(mpEnd - mpBegin);
        unsigned doubled = len * 2;
        if (len == 0)
            doubled = 1;
        unsigned total = len + n;
        if (total < doubled)
            total = doubled;
        cGrid* buf = total
            ? (cGrid*)operator new(total * 0x44, "Graphics", 0, 0, ALLOC_FILE, 0xd1)
            : 0;
        cGrid* oldBegin = mpBegin;
        cGrid* p = grid_copy_construct(oldBegin, pos, buf);
        grid_destroy_range(oldBegin, pos, buf);
        grid_fill_n(p, n, value);
        cGrid* mid = p + n;
        cGrid* oldEnd = mpEnd;
        cGrid* q = grid_copy_construct(pos, oldEnd, mid);
        grid_destroy_range(pos, oldEnd, mid);
        if (oldBegin != 0 && *(int*)((char*)oldBegin - 4) != 0)
            operator delete(oldBegin);
        mpEnd = q;
        mpBegin = buf;
        mpCap = buf + total;
    } else if (n != 0) {
        // ---- in-place path ----
        cGrid tmp;
        tmp.CopyConstruct(*value);
        unsigned tail = (unsigned)(mpEnd - pos);
        if (n < tail) {
            cGrid* src = mpEnd - n;
            cGrid* out = 0;
            grid_uninit_copy(&out, src, mpEnd, mpEnd);
            mpEnd += n;
            grid_assign_backward(pos, src, mpEnd);
            grid_assign_fill(pos, pos + n, &tmp);
        } else {
            grid_fill_n(mpEnd, n - tail, &tmp);
            mpEnd += n - tail;
            cGrid* out = 0;
            grid_uninit_copy(&out, pos, mpEnd - (n - tail), &tmp);
            mpEnd += tail;
            grid_assign_fill(pos, mpEnd - tail, &tmp);
        }
        tmp.Destroy();
    }
}

// @ 0x00704060
bool __thiscall cHierGrid::Shutdown()
{
    mOriginX = 0.0f; mOriginY = 0.0f; mOriginZ = 0.0f;
    mSize = 0.0f;
    mInvSize = 0.0f;
    mLeafLevel = -1;
    mTopLevel = -1;
    cGrid* begin = mGrids.mpBegin;
    cGrid* end = mGrids.mpEnd;
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
void __thiscall cHierGrid::Resize(unsigned n)
{
    unsigned have = (unsigned)(mGrids.mpEnd - mGrids.mpBegin);
    if (n > have) {
        cGrid value;
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
bool __thiscall cHierGrid::Init(const Vec3& origin, float size, int maxLevel)
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
        cGrid* g = mGrids.mpBegin + i;
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

// @ 0x007043b0
struct PropStub { int r0, r4, r8, rC, r10; void Get(int* a, int* b, int* c); };
void __thiscall PropStub::Get(int* a, int* b, int* c)
{
    *a = r4;
    *b = r8;
    *c = r10;
}

// @ 0x007043d0
extern char g_vtblA[], g_vtblB[], g_vtblC[];
void __fastcall PropDtor(void* self)
{
    *(void**)self = g_vtblA;
    *(void**)((char*)self + 0x18) = g_vtblB;
    operator delete(*(void**)((char*)self + 0x28));
    *(void**)self = g_vtblC;
}

// @ 0x00704400
bool __cdecl Image_Read(void* stream, ImageData* d)
{
    int v = 0;
    if (!ReadInt32(stream, &v, 1, 0) || v != 0)
        return false;
    if (!ReadInt32(stream, &d->mWidth, 1, 0)) return false;
    if (!ReadInt32(stream, &d->mHeight, 1, 0)) return false;
    int flags = 0;
    if (!ReadInt32(stream, &flags, 1, 0)) return false;
    d->mFlags = flags;
    int n = 0;
    if (!ReadInt32(stream, &n, 1, 0)) return false;
    if (!ReadBlocks(stream, n, 1)) return false;
    if (d->mData)
        operator delete(d->mData);
    d->mData = operator new(n, "Graphics/cImageData", 0, 0, 0, 0);
    return ReadInto(stream, d->mData, n) != 0;
}

// @ 0x00704500
bool __cdecl Image_Write(void* stream, ImageData* d, unsigned count)
{
    unsigned v = 0;
    if (!WriteUint32(stream, &v, 1, 0)) return false;
    v = (unsigned)d->mWidth;
    if (!WriteUint32(stream, &v, 1, 0)) return false;
    v = (unsigned)d->mHeight;
    if (!WriteUint32(stream, &v, 1, 0)) return false;
    v = (unsigned)d->mFlags;
    if (!WriteUint32(stream, &v, 1, 0)) return false;
    v = count;
    if (!WriteUint32(stream, &v, 1, 0)) return false;
    Stream* st = (Stream*)stream;
    void* vtbl = st->mVtbl;
    void* data = d->mData;
    StreamWriteFn fn = (StreamWriteFn)(*(void**)((char*)vtbl + 0x38));
    return fn(st, data, count);
}

// @ 0x007045d0
bool __cdecl Image_ReadV2(void* stream, ImageData* d)
{
    if (!Image_Read(stream, d))
        return false;
    return ReadInt32(stream, &d->mPitch, 1, 0);
}

// @ 0x00704620
bool __cdecl Image_WriteV1(void* stream, ImageData* d)
{
    unsigned n = (unsigned)(d->mHeight * d->mPitch);
    if (!Image_Write(stream, d, n))
        return false;
    unsigned pitch = (unsigned)d->mPitch;
    return WriteUint32(stream, &pitch, 1, 0);
}

// @ 0x00704670
bool __cdecl Image_WriteV2(void* stream, ImageData* d)
{
    unsigned n = (unsigned)(d->mHeight * d->mPitch) * 6;
    if (!Image_Write(stream, d, n))
        return false;
    unsigned pitch = (unsigned)d->mPitch;
    return WriteUint32(stream, &pitch, 1, 0);
}

// @ 0x007046c0
bool __cdecl Image_WriteV0(void* stream, ImageData* d)
{
    return Image_Write(stream, d, (unsigned)(d->mHeight * d->mWidth));
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct cGrid {
    void Destroy(); // 0x00702ff0
};
}
