// Slice s00703700: SP::cHierGrid construction / lifetime and cGrid-vector helpers (retail build).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void  operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- masked external callees ----
char __cdecl ReadInt32(void* stream, void* dst, int count, int flag);     // 0x0093a780
char __cdecl WriteUint32(void* stream, void* src, int count, int flag);   // 0x0093aa70
char __cdecl ReadBlocks(void* stream, int n, int flag);                   // 0x0093a890
char __cdecl ReadInto(void* stream, void* dst, int n);                    // 0x0093a6c0
void __cdecl SlotVectorGrow(void* self);                                  // 0x00702e00
void __cdecl SlotVectorDestroy(void* self, unsigned index);               // 0x00700ff0
void __cdecl HashMapFindIdx(void* self, void* key);                       // 0x00703360
unsigned __cdecl CellFromPos(void* self, float x, float y, float z, unsigned char level); // 0x00700da0

// ---- layouts ----
struct ObjListNode { ObjListNode* pNext; ObjListNode* pPrev; void* mObj; };
struct CellInfo { ObjListNode mHead; unsigned char mOctantFlags; char _pad[3]; };
struct Vec3 { float x, y, z; };

struct cGrid {
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
    void Destroy();
    cGrid* CopyConstruct(const cGrid& src);
};

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
    unsigned CreateEntry(unsigned a, unsigned b, float c);
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
void __cdecl grid_fill_n(unsigned n, cGrid* dst, const cGrid* value);     // fill_n
void __cdecl grid_assign_backward(cGrid* first, cGrid* last, cGrid* dstEnd); // 0x703690
cGrid* __cdecl grid_assign_fill(cGrid* first, cGrid* last, const cGrid* src); // 0x703c80

// @ 0x00703700  (insert one object into the hierarchy)
void __thiscall cHierGrid::Add(unsigned index, float radius, const Vec3& pos, unsigned extra)
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
    cGrid* g = mGrids.mpBegin + level;
    HashMapFindIdx((char*)g->mCells, &cellID);
    (void)index;
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
cGrid* __cdecl grid_assign_fill(cGrid* first, cGrid* last, const cGrid* src)
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
unsigned __thiscall cHierGrid::CreateEntry(unsigned a, unsigned b, float c)
{
    unsigned value[2] = { 0, 0 };
    unsigned id = 0;
    SlotVectorGrow(&value);
    mNumObjects += 1;
    Add(id, c, *(Vec3*)&b, a);
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
    unsigned have = (unsigned)(mpEnd - mpBegin);
    if (n > (unsigned)(mpCap - mpEnd)) {
        cGrid* newBegin = (cGrid*)operator new((have + n) * 0x44, "Graphics", 0, 0, ALLOC_FILE, 0xd1);
        cGrid* p = grid_copy_construct(mpBegin, pos, newBegin);
        cGrid* q = grid_uninit_copy(&p, pos, mpEnd, 0);
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
