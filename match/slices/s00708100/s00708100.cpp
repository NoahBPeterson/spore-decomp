// slice s00708100: SP::cLightingWorld / cLightingManager continuation and the
// EASTL container algorithms used by the lighting config.  /O2 + SSE region.
#include <new>
#include <string.h>
#include "types.h"

void __cdecl EastlFree(void* p);                      // 0x00F47380
void ReleaseElem(void* p);                            // 0x007610F0

// free-list vector at cLightingWorld + 0x478 (fixed_vector<int,128>)
struct LightFreeVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void DoInsertValue(void** position, void* const& value);  // 0x006C1570
};

// ===========================================================================
// geometry / element types
// ===========================================================================
struct CellInfo { int x, y; };
struct V32 { union { float f[8]; uint32_t u[8]; }; };

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
    void ReleaseDestroy(uint32_t idx)
    {
        uint32_t* e = (uint32_t*)((char*)mpBlocks[idx >> 7] + (idx & 0x7f) * 0x1e0);
        *e = (*e & 0xc0000000u) | (mField1c & 0x3fffffffu) | 0x80000000u;
        mField1c = idx;
        if (mField18 == idx)
            mField18 = Next(idx);
    }
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
        Erase(mpBegin + n * 8, mpEnd);
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
    mpEnd -= ((uint32_t)(mpEnd - mid) >> 4) * 0x10;
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
struct IdVec {
    uint32_t* mpBegin;       // +0x00
    uint32_t* mpEnd;         // +0x04
    uint32_t* mpCapacity;    // +0x08
    void DoInsertValue(uint32_t* position, const uint32_t& value);  // 0x4558a0
};

struct SampleVec {
    V32* mpBegin;            // +0x00
    V32* mpEnd;              // +0x04
    V32* mpCapacity;         // +0x08
    char pad0c[8];
    IdVec mIds;              // +0x14
    char pad20[8];
    int mCount;              // +0x28
    void DoInsertValue(V32* position, const V32* value);   // 0x707a50
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
    char* entry = (char*)(*(int*)(*(int*)((char*)this + 0x428) + ((uint32_t)id >> 7) * 4))
                  + 4 + (id & 0x7f) * 0xc4;
    *(int*)(*(int*)(entry + 0x28) + 4 + index * 8) =
        (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) >> 5);
    V32* p = vec->mpEnd;
    if (p < vec->mpCapacity) {
        vec->mpEnd = p + 1;
    } else {
        V32 tmp;
        vec->DoInsertValue(p, &tmp);
    }
    V32* dst = (V32*)((char*)vec->mpEnd - 0x20);
    const V32* src = (const V32*)entry;
    dst->u[0] = src->u[0];
    dst->u[1] = src->u[1];
    dst->u[2] = src->u[2];
    dst->u[3] = src->u[7];
    dst->u[4] = src->u[4];
    dst->u[5] = src->u[5];
    dst->u[6] = src->u[6];
    dst->u[7] = src->u[3];
    uint32_t* ip = vec->mIds.mpEnd;
    if (ip < vec->mIds.mpCapacity) {
        vec->mIds.mpEnd = ip + 1;
        if (ip)
            *ip = id;
    } else {
        uint32_t local = id;
        vec->mIds.DoInsertValue(ip, local);
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
    LightFreeVec* freeList = (LightFreeVec*)((char*)this + 0x478);
    void** p = freeList->mpEnd;
    if (p < freeList->mpCapacity) {
        freeList->mpEnd = p + 1;
        if (p) {
            *p = e;
            return;
        }
    } else {
        freeList->DoInsertValue(p, e);
    }
}

static inline void* NodeFromLink(void* link)
{
    return link ? (void*)((char*)link - 4) : 0;
}

// @ 0x007085a0
void cLightingWorld::RemoveLight(uint32_t id)
{
    int* block = (int*)(*(int**)((char*)this + 0x428))[id >> 7];
    char* entry = (char*)block + (id & 0x7f) * 0xc4 + 4;
    if (entry[0x24] != 0) {
        int* list = (int*)((char*)this + 0x5d4);
        RemoveLightFromList(id, 0, list);
        if (list[0] == *(int*)((char*)this + 0x5d8)) {
            char* node = (char*)NodeFromLink(*(void**)((char*)this + 0x600));
            char* end = (char*)NodeFromLink((char*)this + 0x600);
            for (; node != end; node = (char*)NodeFromLink(*(void**)(node + 4))) {
                int cache = *(int*)(node + 0x28);
                if (cache >= 0)
                    *(void**)node = (char*)(*(int*)(*(int*)((char*)this + 0x594)
                                                      + ((uint32_t)cache >> 7) * 4))
                                     + 0x10 + (cache & 0x7f) * 0x1f0;
                else
                    *(void**)node = (char*)this + 0x260;
                ((SlotVecC4*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)(node + 0x24));
                *(int*)(node + 0x24) = -1;
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
// cLightingConfig: memberwise copy ctor (0x00708100) and operator= (0x007089a0)
// ===========================================================================
typedef void (__thiscall *FnV)(void*);

struct Light { float f[7]; Light(const Light&); };
struct RectF { float x1, y1, x2, y2; RectF(const RectF&); };
struct F8 {
    float f[8];
    F8() {}
    F8(const F8& s) { for (int i = 0; i < 8; ++i) f[i] = s.f[i]; }
};
struct F3 {
    float f[3];
    F3() {}
    F3(const F3& s) { for (int i = 0; i < 3; ++i) f[i] = s.f[i]; }
};
struct F4 {
    float f[4];
    F4() {}
    F4(const F4& s) { for (int i = 0; i < 4; ++i) f[i] = s.f[i]; }
};
struct AutoRef {
    void* p;
    AutoRef(const AutoRef& s) : p(s.p)
    {
        if (p)
            ((FnV)(*(void***)p)[0])(p);
    }
    AutoRef& operator=(const AutoRef& s)
    {
        void* o = p;
        void* n = s.p;
        if (n != o) {
            if (n)
                ((FnV)(*(void***)n)[0])(n);
            p = n;
            if (o)
                ((FnV)(*(void***)o)[1])(o);
        }
        return *this;
    }
    ~AutoRef();
};
struct VecSHO {
    void* a, *b, *c;
    char alloc[8];
    VecSHO(const VecSHO&);
    VecSHO& operator=(const VecSHO&);
    ~VecSHO();
};
void* __cdecl UninitCopyVec4(void* first, void* last, void* dst);
struct Vec4 {
    void* a, *b, *c;
    char alloc[8];
    void init(int, int);
    Vec4(const Vec4& s)
    {
        init((int)(((char*)s.b - (char*)s.a) >> 4), (int)&s.alloc);
        b = UninitCopyVec4(s.a, s.b, a);
    }
    Vec4& operator=(const Vec4&);
    ~Vec4();
};

// 00708100 cLightingConfig::cLightingConfig (implicit memberwise copy ctor emitted for ForceCopy)
struct cLightingConfig {
    AutoRef mOwner;          // +0x00
    int mFlags;              // +0x04
    Light mLights[4];        // +0x08
    F8 m78;                  // +0x78
    F3 m98;                  // +0x98
    unsigned char mA4;       // +0xa4
    VecSHO mA8;              // +0xa8
    Vec4 mBC;                // +0xbc
    float mD0, mD4, mD8, mDC, mE0;                 // +0xd0..0xe0
    RectF mRects[3];         // +0xe4
    float m114, m118, m11c, m120;                  // +0x114
    F4 m124;                 // +0x124
    unsigned char m134;      // +0x134
    float m138, m13c, m140;  // +0x138..0x140
};

__declspec(noinline) void ForceCopy(cLightingConfig* d, const cLightingConfig* s)
{
    new (d) cLightingConfig(*s);
}

__declspec(noinline) void ForceAssign(cLightingConfig* d, const cLightingConfig* s)
{
    *d = *s;
}

// @ 0x00708500
cLightingConfig* CopyConstructRange(const cLightingConfig* first, const cLightingConfig* last,
                                    cLightingConfig* dst)
{
    for (; first != last; ++first, ++dst)
        ::new (dst) cLightingConfig(*first);
    return dst;
}

// ===========================================================================
// 0x00708df0: fixed-vector constructor with the inline 0x400-byte buffer
// ===========================================================================
struct Vector4 { float x, y, z, w; };

struct PoolBase {
    Vector4* mpBegin;
    ~PoolBase();
};

struct ScratchVec : PoolBase {
    Vector4* mpEnd;
    Vector4* mpCap;
    unsigned pad0c;
    Vector4* mpPoolBegin;
    unsigned pad14[3];
    Vector4 mBuf[64];
    void assign(const Vector4* first, const Vector4* last, const Vector4* extra);
    ScratchVec(const Vector4* first, const Vector4* last);
};

// @ 0x00708df0
ScratchVec::ScratchVec(const Vector4* first, const Vector4* last)
    : PoolBase()
{
    Vector4* p = mBuf;
    mpPoolBegin = p;
    mpEnd = p;
    mpBegin = p;
    mpCap = p + 64;
    assign(first, last, last);
}

// ===========================================================================
// 0x00708900: cLightingManager destructor
// ===========================================================================
struct CfgVec {
    int a, b, c, d, e;
    ~CfgVec();
};

struct WorldMap {
    char pad0[0xc];
    void* mRoot;
    void clear(void*);
    ~WorldMap() { clear(mRoot); }
};

struct BaseA { virtual ~BaseA() {} virtual void a0(); virtual void a1(); };
struct BaseB { virtual ~BaseB() {} virtual void b0(); };
struct BaseC { virtual ~BaseC() {} virtual void c0(); };

struct cLightingManager : BaseA, BaseB, BaseC {
    int mC, m10, m14;
    CfgVec mVec;
    WorldMap mMap;
    virtual ~cLightingManager();
};

// @ 0x00708900
cLightingManager::~cLightingManager() {}

// force out-of-line emission of otherwise-unreferenced members
void (Vec8b::*volatile g_pResize8)(uint32_t) = &Vec8b::resize;
void (Vec16::*volatile g_pResize16)(uint32_t) = &Vec16::resize;
