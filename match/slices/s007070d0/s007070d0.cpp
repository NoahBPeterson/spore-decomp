// slice s007070d0
#include <new>
#include "types.h"
#include <xmmintrin.h>

void* __cdecl EastlAlloc8(uint32_t n, uint32_t align, int a, const char* name, int b, int c,
                          const char* file, int line);
void* __cdecl EastlAlloc6(uint32_t n, const char* name, int a, int b, const char* file, int line);
void  __cdecl EastlFree(void* p); // 0x00f47380

struct Vector4 { float f[4]; };
struct cSPVector3 { float x, y, z; };

Vector4* CopyVec4(Vector4* first, Vector4* last, Vector4* result);
Vector4* CopyBackVec4(Vector4* first, Vector4* last, Vector4* resultEnd);
Vector4* UninitCopyVec4(Vector4* first, Vector4* last, Vector4* result);

// ===========================================================================
// eastl::vector<Vector4, sp_vector_allocator>
// ===========================================================================
struct Vec4 {
    Vector4* mpBegin;
    Vector4* mpEnd;
    Vector4* mpCapacity;
    Vector4* DoRealloc(uint32_t n, const Vector4* first, const Vector4* last);
    Vec4& operator=(const Vec4& x);
    void DoInsertValues(Vector4* position, Vector4* source);
    void InsertValuesAt(Vector4* position, uint32_t n, const Vector4* value);
};

// @ 0x007077f0
Vec4& Vec4::operator=(const Vec4& x)
{
    if (this != &x) {
        const Vector4* first = x.mpBegin;
        const Vector4* last = x.mpEnd;
        const uint32_t n = (uint32_t)(last - first);
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            Vector4* pNewData = DoRealloc(n, first, last);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                EastlFree(mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewData + n;
            mpCapacity = mpEnd;
        } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
            CopyVec4((Vector4*)first, (Vector4*)last, mpBegin);
            mpEnd = mpBegin + n;
        } else {
            const Vector4* position = first + (mpEnd - mpBegin);
            CopyVec4((Vector4*)first, (Vector4*)position, mpBegin);
            UninitCopyVec4((Vector4*)position, (Vector4*)last, mpEnd);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// @ 0x00707a00
void Vec4::DoInsertValues(Vector4* position, Vector4* source)
{
    Vector4* pEnd = mpEnd;
    for (; source != pEnd; ++source, ++position)
        *(__m128*)position = *(const __m128*)source;
    mpEnd += position - source;
}

// ===========================================================================
// allocator helper
// ===========================================================================
// @ 0x00707720
struct Buf28 {
    char pad0[0x28];
    void* mpBlock;
    char pad2[0xc];
    void* mpDefault;
    void Free();
};

void Buf28::Free()
{
    void* p = mpBlock;
    if (p && p != mpDefault)
        EastlFree(p);
}

// ===========================================================================
// eastl::rbtree<...>::DoNukeSubtree
// ===========================================================================
struct VObj {
    virtual void slot0();
    virtual void slot1();
};

struct NukeNode {
    VObj* mpObj;
    char pad0[0xa4];
    void* mpA8;
    char pad1[0x10];
    void* mpBC;
    char pad2[0x144 - 0xc0];
};

struct Rbtree {
    void DoNukeSubtree(NukeNode* first, NukeNode* last);
};

// @ 0x00707690
void Rbtree::DoNukeSubtree(NukeNode* first, NukeNode* last)
{
    for (; first < last; first = (NukeNode*)((char*)first + 0x144)) {
        if (first->mpBC && ((int*)first->mpBC)[-1] != 0)
            EastlFree(first->mpBC);
        if (first->mpA8 && ((int*)first->mpA8)[-1] != 0)
            EastlFree(first->mpA8);
        if (first->mpObj)
            first->mpObj->slot1();
    }
}

// ===========================================================================
// spstl::slot_vector_base helpers
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

// @ 0x00707540
void SlotVec28::Release(uint32_t idx)
{
    uint32_t* slot = (uint32_t*)((idx & 0x7f) * 0x1f0 + *(int*)((char*)mpBlocks + (idx >> 7) * 4));
    *slot = (*slot & 0xc0000000) | (mField1c & 0x3fffffff) | 0x80000000;
    mField1c = idx;
    if (mField18 == idx)
        mField18 = Next(idx);
}

// @ 0x00707590
void SlotVec28::ReleaseDestroy(uint32_t idx)
{
    uint32_t* slot = (uint32_t*)((idx & 0x7f) * 0x1e0 + *(int*)((char*)mpBlocks + (idx >> 7) * 4));
    *slot = (*slot & 0xc0000000) | (mField1c & 0x3fffffff) | 0x80000000;
    mField1c = idx;
    if (mField18 == idx)
        mField18 = DestroyNext(idx);
}

// @ 0x00707ed0
struct SlotVecC4 {
    int* mpBlocks;
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t Next(uint32_t idx);
    void DestroyEntry(uint32_t idx);
};

void SlotVecC4::DestroyEntry(uint32_t idx)
{
    uint32_t* slot = (uint32_t*)((idx & 0x7f) * 0xc4 + *(int*)((char*)mpBlocks + (idx >> 7) * 4));
    void* p = *(void**)((char*)slot + 0x2c);
    if (p && p != *(void**)((char*)slot + 0x3c))
        EastlFree(p);
    *slot = (mField1c & 0x3fffffff) | (*slot & 0xc0000000) | 0x80000000;
    mField1c = idx;
    if (mField18 == idx)
        mField18 = Next(idx);
}

// ===========================================================================
// element-array destroy helper (destroy last element, then unwind)
// ===========================================================================
struct Allocator {
    void Destroy(void* p);
};
extern Allocator* g_pAlloc;     // 0x016c8b44

struct SlotDeque {
    void** mpBegin;
    void** mpEnd;
    char pad8[0xc];
    int mField14;
    void DestroyAll(int unused);
};

// @ 0x007075e0
void SlotDeque::DestroyAll(int)
{
    while (mpBegin != mpEnd) {
        if (mField14 == 0) {
            g_pAlloc->Destroy(mpEnd[-1]);
            mpEnd -= 1;
            mField14 = 0x7f;
        } else {
            --mField14;
        }
    }
}

// ===========================================================================
// cLightingWorld
// ===========================================================================
struct cShaderDataLightingInfo {
    char pad[0x1c0];
    cShaderDataLightingInfo& operator=(const cShaderDataLightingInfo& x);
};

struct EnvEntry {
    cShaderDataLightingInfo mShaderData;   // +0x000
    cSPVector3 mPosition;                  // +0x1c0
    int mPad1cc;                           // +0x1cc
    uint32_t mCelStrength;                 // +0x1d0
};

struct IntrusiveList { ~IntrusiveList(); };

struct Elem38 {
    int mTag;               // +0x00
    void* mp4;              // +0x04
    char pad8[0x10];
    void* mp18;             // +0x18
    char pad1c[0x14];
    IntrusiveList mList;    // +0x30
};

struct Deque38 {
    char pad0[4];
    void* mpData;           // +0x04
    char pad8[0xc];
    int mIndex14;           // +0x14
    void PopDestroy();
};

struct cLightingWorld {
    char pad[0x1000];
    void CreateEnvLightSample(EnvEntry* pEntry, const cSPVector3* pPos, uint32_t celStrength);
    void UpdateEnvLightSample(EnvEntry* pEntry);
    void GetLocalShaderData(void* e);
    void ReleaseLocalCache(void* e);
    void UpdateLightPosition(uint32_t id, const cSPVector3* pos);
    void RemoveLightFromList(uint32_t id, int index, int* list);
    void UpdateLocalLightSample(int* info);
};

// @ 0x007074e0
void cLightingWorld::CreateEnvLightSample(EnvEntry* pEntry, const cSPVector3* pPos, uint32_t celStrength)
{
    pEntry->mPosition = *pPos;
    pEntry->mShaderData = *(cShaderDataLightingInfo*)((char*)this + 0x260);
    pEntry->mPad1cc = 0;
    pEntry->mCelStrength = celStrength;
    UpdateEnvLightSample(pEntry);
}

// @ 0x00707740
void cLightingWorld::GetLocalShaderData(void* e)
{
    int idx = *(int*)((char*)e + 0x28);
    if (idx >= 0)
        *(void**)e = (void*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)idx >> 7) * 4)
                             + 0x10 + (idx & 0x7f) * 0x1f0);
    else
        *(void**)e = (char*)this + 0x260;
    ((SlotVec28*)((char*)this + 0x608))->ReleaseDestroy(*(uint32_t*)((char*)e + 0x24));
    *(int*)((char*)e + 0x24) = -1;
}

// @ 0x00707790
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

// @ 0x00707f40
void Deque38::PopDestroy()
{
    Elem38* elem = (Elem38*)(*(int*)((char*)mpData - 4) + mIndex14 * 0x38);
    if (((elem->mTag >> 31) & 1) == 0) {
        elem->mList.~IntrusiveList();
        if (elem->mp18 && ((int*)elem->mp18)[-1] != 0)
            EastlFree(elem->mp18);
        if (elem->mp4 && ((int*)elem->mp4)[-1] != 0)
            EastlFree(elem->mp4);
    }
    if (mIndex14 == 0) {
        g_pAlloc->Destroy((void*)*(int*)((char*)mpData - 4));
        mpData = (char*)mpData - 4;
        mIndex14 = 0x7f;
        return;
    }
    --mIndex14;
}

// ===========================================================================
// eastl::vector<Vector4>::DoInsertValues(position, n, value)   (insert range)
// ===========================================================================
void FillVec4(Vector4* first, Vector4* last, const Vector4* value);        // 0x705e90
void UninitFillVec4(Vector4* first, uint32_t n, const Vector4* value);     // 0x705ec0

// @ 0x00707b70
void Vec4::InsertValuesAt(Vector4* position, uint32_t n, const Vector4* value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const Vector4 temp = *value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            if (n < nExtra) {
                UninitCopyVec4(mpEnd - n, mpEnd, mpEnd);
                CopyBackVec4(position, mpEnd - n, mpEnd);
                FillVec4(position, position + n, &temp);
            } else {
                UninitFillVec4(mpEnd, n - nExtra, &temp);
                UninitCopyVec4(position, mpEnd, mpEnd + (n - nExtra));
                FillVec4(position, mpEnd, &temp);
            }
            mpEnd += n;
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrowSize = nPrevSize * 2;
        if (nPrevSize == 0) nGrowSize = 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize) nNewSize = nGrowSize;
        Vector4* pNewData = nNewSize ? (Vector4*)EastlAlloc8(nNewSize * 0x10, 0x10, 0, "Graphics", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5)
                              : 0;
        Vector4* pNewEnd = UninitCopyVec4(mpBegin, position, pNewData);
        UninitFillVec4(pNewEnd, n, value);
        pNewEnd = UninitCopyVec4(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ===========================================================================
// eastl::vector<SP::cSHObject, sp_vector_allocator>   (0x24-byte elements)
// ===========================================================================
struct SHObject { char pad[0x24]; };
void CopySHO(SHObject* first, SHObject* last, SHObject* result);                 // 0x707630
void UninitCopySHO5(SHObject** out, SHObject* src, SHObject* dst, SHObject* dstEnd, SHObject* srcEnd); // 0x706c80

struct VecSHO {
    SHObject* mpBegin;      // +0x00
    SHObject* mpEnd;        // +0x04
    SHObject* mpCapacity;   // +0x08
    SHObject* mpInline;     // +0x10
    SHObject* DoRealloc(uint32_t n, SHObject* first, SHObject* last);   // 0x7079a0
    VecSHO& operator=(const VecSHO& x);
};

// @ 0x00707fd0
VecSHO& VecSHO::operator=(const VecSHO& x)
{
    if (this != &x) {
        const uint32_t n = (uint32_t)((x.mpEnd - x.mpBegin) / 0x24);
        if (n > (uint32_t)((mpCapacity - mpBegin) / 0x24)) {
            SHObject* pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                EastlFree(mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewData + n;
            mpCapacity = mpEnd;
        } else {
            const uint32_t nSize = (uint32_t)((mpEnd - mpBegin) / 0x24);
            if (n <= nSize) {
                CopySHO(x.mpBegin, x.mpEnd, mpBegin);
                mpEnd = mpBegin + n;
            } else {
                CopySHO(x.mpBegin, x.mpBegin + nSize, mpBegin);
                SHObject* out = x.mpEnd;
                UninitCopySHO5(&out, x.mpBegin + nSize, mpEnd, mpEnd, x.mpEnd);
                mpEnd = mpBegin + n;
            }
        }
    }
    return *this;
}

// ===========================================================================
// 8-byte element vector insertion
// ===========================================================================
struct Vec8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    char* mpInline;
    void DoInsertValues(char* position, uint32_t n, const void* value);
};

void MoveElems8(char* dst, char* src, uint32_t n);          // 0x76ffd0
void CopyElems8(char* first, char* last, char* dst);        // 0x73fe50
void UninitFill8(char* dst, uint32_t n, const void* value); // 0xa52da0
void* UninitCopy8(char* first, char* last, char* dst);      // 0x006ac440
void CopyAssign8(char* first, char* last, char* dst);       // 0x0099efa0

// @ 0x00707d10
void Vec8::DoInsertValues(char* position, uint32_t n, const void* value)
{
    if (n <= (uint32_t)((mpCapacity - mpEnd) >> 3)) {
        if (n != 0) {
            char* pEnd = mpEnd;
            const char* v = (const char*)value;
            const uint32_t nExtra = (uint32_t)((pEnd - position) >> 3);
            if (n < nExtra) {
                MoveElems8(pEnd, pEnd - n * 8, n * 8);
                CopyElems8(position, pEnd - n * 8, pEnd);
                UninitFill8(position, n, v);
            } else {
                UninitFill8(pEnd, n - nExtra, v);
                UninitCopy8(position, pEnd, pEnd + (n - nExtra) * 8);
                CopyAssign8(position, pEnd, (char*)v);
            }
            mpEnd += n * 8;
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)((mpEnd - mpBegin) >> 3);
        uint32_t nGrowSize = nPrevSize * 2;
        if (nPrevSize == 0) nGrowSize = 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nNewSize < nGrowSize) nNewSize = nGrowSize;
        char* pNewData = nNewSize
            ? (char*)EastlAlloc6(nNewSize * 8, "Graphics", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
            : 0;
        char* pNewEnd = (char*)UninitCopy8(mpBegin, position, pNewData);
        UninitFill8(pNewEnd, n, value);
        pNewEnd = (char*)UninitCopy8(position, mpEnd, pNewEnd + n * 8);
        if (mpBegin && mpBegin != mpInline)
            EastlFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize * 8;
    }
}

// ===========================================================================
// cLightingWorld lighting update entry points
// ===========================================================================
struct cLightingManager {
    void slot0();
    void slot1();
    void slot2();
    void slot3();
    void slot4();
    void slot5(void* p);
};

// @ 0x007070d0
void cLightingWorld::UpdateLightPosition(uint32_t id, const cSPVector3* pos)
{
    int iVar7 = (id & 0x7f) * 0xc4;
    int iVar5 = ((uint32_t)id >> 7) * 4;
    int iVar6 = *(int*)(*(int*)((char*)this + 0x428) + iVar5);
    char* entry = (char*)iVar6 + 4 + iVar7;
    if (entry[0x24] != 0) {
        int cell = *(int*)(*(int*)(entry + 0x28) + 4) * 0x20;
        float* p = (float*)(*(int*)((char*)this + 0x5d4) + cell + 0x10);
        p[0] = pos->x;
        p[1] = pos->y;
        p[2] = pos->z;
        ++*(int*)((char*)this + 0x5fc);
        *(char*)((char*)this + 0x660) = 1;
    }
    int* p20 = *(int**)(entry + 0x20);
    if (p20) {
        if (*(int*)(*(int*)((char*)this + 0x428) + 0x20) == 0) {
            *(int*)(entry + 0x20) = 0;
        } else {
            p20[1] = *(int*)&pos->x;
            p20[2] = *(int*)&pos->y;
            *(uint16_t*)p20 |= 4;
            ++*(uint16_t*)((char*)p20 + 2);
            p20[3] = *(int*)&pos->z;
            void* mgr = *(void**)((char*)this + 0x448);
            ((void(__thiscall*)(void*, int*))(*(void***)mgr)[5])(mgr, p20);
        }
    }
    float* out = (float*)(*(int*)(*(int*)((char*)this + 0x428) + iVar5) + 0x14 + iVar7);
    out[0] = pos->x;
    out[1] = pos->y;
    out[2] = pos->z;
}

// @ 0x00707270
void cLightingWorld::RemoveLightFromList(uint32_t id, int index, int* list)
{
    int iVar3 = *(int*)((char*)this + 0x428);
    char* entry = (char*)(*(int*)(iVar3 + ((uint32_t)id >> 7) * 4) + 4 + (id & 0x7f) * 0xc4);
    uint32_t uVar4 = *(uint32_t*)(list[6] - 4);
    if (uVar4 != id) {
        int* piVar1 = (int*)(*(int*)(entry + 0x28) + index * 8);
        int iVar5 = *piVar1;
        int iVar6 = piVar1[1];
        char* other = (char*)(*(int*)(iVar3 + (uVar4 >> 7) * 4) + 4 + (uVar4 & 0x7f) * 0xc4);
        int count = (*(int*)(other + 0x2c) - *(int*)(other + 0x28)) >> 3;
        for (int i = 0; i < count; ++i) {
            if (*(int*)(*(int*)(other + 0x28) + i * 8) == iVar5)
                *(int*)(*(int*)(other + 0x28) + i * 8 + 4) = iVar6;
        }
        int* dst = (int*)(*(int*)(list[0]) + iVar6 * 0x20);
        int* src = (int*)(list[1] - 0x20);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3];
        dst[4] = src[4]; dst[5] = src[5]; dst[6] = src[6]; dst[7] = src[7];
        *(int*)(list[5] + iVar6 * 4) = *(int*)(list[6] - 4);
    }
    list[1] -= 0x20;
    list[6] -= 4;
    ++list[10];
    *(int*)(*(int*)(entry + 0x28) + index * 8) = -1;
    *(int*)(*(int*)(entry + 0x28) + index * 8 + 4) = -1;
}

void __cdecl AddSphereLighting(Vector4* dst, void* base, int count, Vector4 value); // 0x7961d0

// @ 0x00707370
void cLightingWorld::UpdateLocalLightSample(int* info)
{
    float* pfVar1 = (float*)(*(int*)(*(int*)((char*)this + 0x608) + ((uint32_t)info[9] >> 7) * 4)
                             + 0x10 + (info[9] & 0x7f) * 0x1e0);
    float* pSrc;
    if (info[10] < 0)
        pSrc = (float*)((char*)this + 0x260);
    else
        pSrc = (float*)(*(int*)(*(int*)((char*)this + 0x594) + ((uint32_t)info[10] >> 7) * 4)
                        + 0x10 + (info[10] & 0x7f) * 0x1f0);
    for (int k = 0; k < 0x70; ++k)
        pfVar1[k] = pSrc[k];
    *((uint8_t*)pfVar1 + 1) = *(uint8_t*)((char*)this + 0x38);
    float fVar7;
    if (*(char*)((char*)this + 0x424) != 0)
        fVar7 = pfVar1[0xb];
    else
        fVar7 = 1.0f;
    fVar7 = *(float*)&info[7] * fVar7;
    if (0.0f < fVar7) {
        int uVar3 = *(int*)((char*)this + 0x5d4);
        if (uVar3 != *(int*)((char*)this + 0x5d8)) {
            Vector4 val;
            val.f[0] = *(float*)&info[3];
            val.f[1] = *(float*)&info[4];
            val.f[2] = *(float*)&info[5];
            val.f[3] = fVar7;
            AddSphereLighting((Vector4*)(pfVar1 + 3), (void*)uVar3,
                              (*(int*)((char*)this + 0x5d8) - uVar3) >> 5, val);
        }
        int li = info[8];
        if (li >= 0) {
            int* piVar2 = (int*)(*(int*)(*(int*)((char*)this + 0x63c) + ((uint32_t)li >> 7) * 4)
                                 + 4 + (li & 0x7f) * 0x38);
            int base = piVar2[0];
            Vector4 val;
            val.f[0] = *(float*)&info[3];
            val.f[1] = *(float*)&info[4];
            val.f[2] = *(float*)&info[5];
            val.f[3] = fVar7;
            AddSphereLighting((Vector4*)(pfVar1 + 3), (void*)base, (piVar2[1] - base) >> 5, val);
        }
    }
    *info = (int)pfVar1;
}

// ===========================================================================
// 32-byte element vector insertion (eastl::vector<32-byte T>)
// ===========================================================================
struct __declspec(align(16)) V32 { float f[8]; };
V32* UninitCopy32(V32* first, V32* last, V32* result);      // 0x7051e0
V32* CopyBack32(V32* first, V32* last, V32* resultEnd);     // 0x705220

struct Vec32 {
    V32* mpBegin;
    V32* mpEnd;
    V32* mpCapacity;
    void DoInsertValue(V32* position, const V32* value);
};

// @ 0x00707a50
void Vec32::DoInsertValue(V32* position, const V32* value)
{
    V32* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        const V32* v = value;
        if (v >= position && v < pEnd)
            v = (const V32*)((const char*)v + 0x20);
        if (pEnd)
            *pEnd = pEnd[-1];
        CopyBack32(position, pEnd - 1, pEnd);
        *position = *v;
        ++mpEnd;
    } else {
        uint32_t n = (uint32_t)(pEnd - mpBegin);
        if (n == 0) n = 1;
        else n *= 2;
        V32* pNewData = n ? (V32*)EastlAlloc8(n * 0x20, 0x10, 0, "Graphics", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5)
                          : 0;
        V32* q = UninitCopy32(mpBegin, position, pNewData);
        if (q)
            *q = *value;
        V32* q2 = UninitCopy32(position, mpEnd, q + 1);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EastlFree(mpBegin);
        mpCapacity = pNewData + n;
        mpBegin = pNewData;
        mpEnd = q2;
    }
}

// ===========================================================================
// algorithm bodies (defined late so calls stay out of line)
// ===========================================================================
// @ 0x00707660
Vector4* CopyVec4(Vector4* first, Vector4* last, Vector4* result)
{
    for (; first != last; ++first, ++result)
        *(__m128*)result = *(const __m128*)first;
    return result;
}

// @ 0x007076f0
Vector4* CopyBackVec4(Vector4* first, Vector4* last, Vector4* resultEnd)
{
    while (last != first)
        *(__m128*)--resultEnd = *(const __m128*)--last;
    return resultEnd;
}

// @ 0x00706ab0
Vector4* UninitCopyVec4(Vector4* first, Vector4* last, Vector4* result)
{
    Vector4* p = result;
    for (; first != last; ++first, ++p)
        *(__m128*)p = *(const __m128*)first;
    return p;
}
// --- equivalence checker address annotations
    void EastlFree(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
