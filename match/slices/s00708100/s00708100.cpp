// slice s00708100: SP::cLightingWorld / cLightingManager continuation and the
// EASTL container algorithms used by the lighting config.  /O2 + SSE region.
#include <new>
#include <string.h>
#include "types.h"

void __cdecl EastlFree(void* p);                      // 0x00F47380
void PushPtr(void* pos, void* val);                   // 0x006C1570
void ReleaseElem(void* p);                            // 0x007610F0

// ===========================================================================
// geometry / element types
// ===========================================================================
struct CellInfo { int x, y; };
struct V32 { float f[8]; };

// ===========================================================================
// spstl slot-vector base helpers (0x1f0 / 0x1e0 / 0xc4 strided slots)
// ===========================================================================
struct SlotVec28 {
    int* mpBlocks;
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t Next(uint32_t idx);
    uint32_t DestroyNext(uint32_t idx);
    void Release(uint32_t idx);
    void ReleaseDestroy(uint32_t idx);
};

struct SlotVecC4 {
    int* mpBlocks;
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t Next(uint32_t idx);
    void DestroyEntry(uint32_t idx);
};

// ===========================================================================
// eastl::vector<cCellInfo, fixed_vector_allocator<8,16,4,0,1>>::assign
// ===========================================================================
struct VecCell {
    CellInfo* mpBegin;      // +0x00
    CellInfo* mpEnd;        // +0x04
    CellInfo* mpCapacity;   // +0x08
    char pad_c[4];
    CellInfo* mpInline;     // +0x10
    CellInfo* DoRealloc(uint32_t n, const CellInfo* first, const CellInfo* last);  // 0x754f80
    void assign(const CellInfo* first, const CellInfo* last, int tag);
};

void* MoveRange5(void** out, const CellInfo* first, const CellInfo* last, CellInfo* dst,
                 const CellInfo* end);               // 0x76ffd0

// @ 0x00708340
void VecCell::assign(const CellInfo* first, const CellInfo* last, int)
{
    const uint32_t n = (uint32_t)(last - first);
    CellInfo* p = mpBegin;
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        CellInfo* pNew = DoRealloc(n, first, last);
        if (mpBegin && mpBegin != mpInline)
            EastlFree(mpBegin);
        mpBegin = pNew;
        mpCapacity = pNew + n;
        mpEnd = pNew + n;
        return;
    }
    if (n <= (uint32_t)(mpEnd - p)) {
        for (; first != last; ++first, ++p)
            *p = *first;
        mpEnd = p;
        return;
    }
    const CellInfo* mid = first + (mpEnd - mpBegin);
    for (; first != mid; ++first, ++p)
        *p = *first;
    CellInfo* newEnd;
    MoveRange5((void**)&newEnd, mid, last, mpEnd, last);
    mpEnd = newEnd;
}

// ===========================================================================
// 8-byte element vector
// ===========================================================================
struct Vec8b {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void resize(uint32_t n);
    void DoInsertValues(char* position, uint32_t n, const void* value);  // 0x707d10
    void Erase(char* first, char* last);                                 // 0xd018d0
};

// @ 0x00708d90
void Vec8b::resize(uint32_t n)
{
    const uint32_t size = (uint32_t)((mpEnd - mpBegin) >> 3);
    if (n > size) {
        uint64_t z = 0;
        DoInsertValues(mpEnd, n - size, &z);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// ===========================================================================
// 16-byte element vector
// ===========================================================================
struct Vec16 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void resize(uint32_t n);
    void DoInsertValues16(char* position, uint32_t n, const void* value);  // 0x77d510
};

void Copy16(char* first, char* last, char* result);    // 0x705250

// @ 0x00708e60
void Vec16::resize(uint32_t n)
{
    const uint32_t size = (uint32_t)((mpEnd - mpBegin) >> 4);
    if (n > size) {
        uint32_t buf[4];
        DoInsertValues16(mpEnd, n - size, buf);
        return;
    }
    char* mid = mpBegin + n * 0x10;
    Copy16(mpEnd, mpEnd, mid);
    mpEnd = (char*)(mpEnd - (mpEnd - mid));
}

// ===========================================================================
// vector-like clear (destroys each element then drops the range)
// ===========================================================================
struct ClearVec {
    char pad0[0x4c];
    void** mpBegin;     // +0x4c
    void** mpEnd;       // +0x50
    char pad54[0xc];
    void* mpExtra;      // +0x60
    void clear();
};

// @ 0x007087a0
void ClearVec::clear()
{
    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i)
        ReleaseElem(mpBegin[i]);
    memcpy(mpBegin, mpEnd, 0);
    mpEnd -= mpEnd - mpBegin;
    if (mpExtra) {
        ReleaseElem(mpExtra);
        mpExtra = 0;
    }
}

// ===========================================================================
// cLightingWorld
// ===========================================================================
struct SampleVec {
    V32* mpBegin;            // +0x00
    V32* mpEnd;              // +0x04
    V32* mpCapacity;         // +0x08
    char pad0c[8];
    uint32_t* mpIdsBegin;    // +0x14
    uint32_t* mpIdsEnd;      // +0x18
    uint32_t* mpIdsCapacity; // +0x1c
    char pad20[8];
    int mCount;              // +0x28
    void DoInsertValue(V32* position, const V32* value);   // 0x707a50
    void PushIdRange(uint32_t* first, uint32_t* last, uint32_t* dst);  // 0x4558a0
};

struct cLightingWorld {
    void RemoveLight(uint32_t id);
    void RemoveLightFromList(uint32_t id, int index, int* list);
    void DestroyLightingInfo(void* e);
    void ReleaseLocalCache(void* e);
    void AddLocalSample(uint32_t id, int index, SampleVec* vec);
};

// @ 0x00708810
void cLightingWorld::AddLocalSample(uint32_t id, int index, SampleVec* vec)
{
    char* entry = (char*)(*(int*)((char*)this + 0x428) + ((uint32_t)id >> 7) * 4)
                  + 4 + (id & 0x7f) * 0xc4;
    *(int*)(*(int*)(entry + 0x28) + 4 + index * 8) = (int)((vec->mpEnd - vec->mpBegin) >> 5);
    V32* p = vec->mpEnd;
    if (p < vec->mpCapacity) {
        vec->mpEnd = p + 1;
    } else {
        V32 tmp;
        vec->DoInsertValue(p, &tmp);
    }
    V32* dst = (V32*)((char*)vec->mpEnd - 0x20);
    const float* src = (const float*)entry;
    dst->f[0] = src[0];
    dst->f[1] = src[1];
    dst->f[2] = src[2];
    dst->f[3] = src[3];
    dst->f[4] = src[4];
    dst->f[5] = src[5];
    dst->f[6] = src[6];
    dst->f[7] = src[7];
    uint32_t* ip = vec->mpIdsEnd;
    if (ip < vec->mpIdsCapacity) {
        vec->mpIdsEnd = ip + 1;
        if (ip)
            *ip = id;
    } else {
        uint32_t local = id;
        vec->PushIdRange(&local, &local + 1, ip);
    }
    ++vec->mCount;
}

// @ 0x00707790 (re-defined here so this TU can call it)
void cLightingWorld::ReleaseLocalCache(void* e)
{
    int idx = *(int*)((char*)e + 0x28);
    char* p = (char*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)idx >> 7) * 4)
                      + 0x10 + (idx & 0x7f) * 0x1f0);
    if (--*(int*)(p + 0x1cc) == 0) {
        int g = *(int*)(p + 0x1d0);
        if (g >= 0) {
            int* grid = *(int**)((char*)this + 0x5b4);
            grid[g] = -1;
        }
        ((SlotVec28*)((char*)this + 0x594))->Release(*(uint32_t*)((char*)e + 0x28));
    }
    *(int*)((char*)e + 0x28) = -1;
}

// @ 0x00708710
void cLightingWorld::DestroyLightingInfo(void* e)
{
    if (e == (char*)this + 0x420)
        return;
    if (*(int*)((char*)e + 0x28) >= 0)
        ReleaseLocalCache(e);
    if (*(int*)((char*)e + 0x24) >= 0) {
        ((SlotVec28*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)((char*)e + 0x24));
        *(int*)((char*)e + 0x24) = -1;
    }
    *(int*)((char*)e + 0x20) = -1;
    int* next = *(int**)((char*)e + 8);
    int prev = *(int*)((char*)e + 4);
    *next = prev;
    *(int**)(prev + 4) = next;
    *(int*)((char*)e + 4) = 0;
    *(int*)((char*)e + 8) = 0;
    char* v = (char*)this + 0x478;
    int* p = *(int**)(v + 4);
    if (p < *(int**)(v + 8)) {
        *(int**)(v + 4) = p + 1;
        if (p) {
            *p = (int)e;
            return;
        }
    } else {
        PushPtr(p, e);
    }
}

// @ 0x007085a0
void cLightingWorld::RemoveLight(uint32_t id)
{
    int iVar7 = (id & 0x7f) * 0xc4;
    int iVar1 = *(int*)(*(int*)((char*)this + 0x428) + ((uint32_t)id >> 7) * 4);
    char* entry = (char*)iVar1 + iVar7 + 4;
    if (*(char*)(iVar1 + 0x28 + iVar7) != 0) {
        char* cells = (char*)this + 0x5d4;
        RemoveLightFromList(id, 0, (int*)cells);
        if (*(int*)cells == *(int*)((char*)this + 0x5d8)) {
            char* head = (char*)this + 0x600;
            void* node = *(void**)((char*)this + 0x600);
            void* end = *(void**)head ? (void*)(*(int*)((char*)this + 0x600) - 4) : 0;
            void* tail = *(void**)head ? (void*)(head - 4) : 0;
            (void)tail;
            void* last = *(void**)((char*)this + 0x600);
            void* stop = last ? (void*)(*(int*)((char*)this + 0x600) - 4) : 0;
            while (node != stop) {
                char* e = (char*)node;
                int cacheId = *(int*)(e + 0x28);
                if (cacheId >= 0)
                    *(void**)e = (void*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)cacheId >> 7) * 4)
                                         + 0x10 + (cacheId & 0x7f) * 0x1f0);
                else
                    *(void**)e = (char*)this + 0x260;
                ((SlotVec28*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)(e + 0x24));
                *(int*)(e + 0x24) = -1;
                int* nx = *(int**)(e + 4);
                node = nx ? (void*)(nx - 1) : 0;
                if (node == end)
                    break;
            }
            *(char*)((char*)this + 0x660) = 1;
        }
    }
    --*(int*)((char*)this + 0x5d0);
    int* mgr = *(int**)((char*)this + 0x448);
    if (mgr) {
        int v = *(int*)(entry + 0x20);
        if (v)
            ((void(__thiscall*)(void*, int))(*(void***)mgr)[6])(mgr, v);
    }
    ((SlotVecC4*)((char*)this + 0x428))->DestroyEntry(id);
}

// ===========================================================================
// cLightingConfig-like full-structure copies
// ===========================================================================
struct cLightingConfig {
    cLightingConfig& operator=(const cLightingConfig& x);
};

void release(void* p);

// @ 0x007089a0
cLightingConfig& cLightingConfig::operator=(const cLightingConfig& x)
{
    if (this != &x) {
        const char* s = (const char*)&x;
        char* d = (char*)this;
        for (int i = 0; i < 0xa4; ++i) d[i] = s[i];
        d[0xa4] = s[0xa4];
        release(d + 0x18);
        for (int i = 0xb0; i < 0x13c; ++i) d[i] = s[i];
    }
    return *this;
}

// ===========================================================================
// small placement / construction helpers marked incomplete
// ===========================================================================
// @ 0x00708100  (EH construct-range helper)
void* ConstructRange(void* self, void* src)
{
    (void)self;
    (void)src;
    return self;
}

// @ 0x00708500  (EH uninitialized-copy helper)
void* CopyConstructRange(void* first, void* last, void* dst)
{
    (void)first;
    (void)last;
    return dst;
}

// @ 0x00708df0
void* ConstructVec(int* self, int a, int b)
{
    (void)a;
    (void)b;
    return self;
}

// @ 0x00708900
void DestroyLightingManager(int* self)
{
    (void)self;
}

// force out-of-line emission of otherwise-unreferenced members
void (Vec8b::*volatile g_pResize8)(uint32_t) = &Vec8b::resize;
void (Vec16::*volatile g_pResize16)(uint32_t) = &Vec16::resize;
