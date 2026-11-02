// src/game/SPEngine/_at_00730000.cpp -- migrated from slice(s) s0073a110, s00735350, s00734380, s00733400, s00732410, s00730240, s0072f830 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00730000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/core/arena/Arena.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>
#include <intrin.h>

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_0072f830(unsigned count, void* first, void* aux, void* a3, void* a4);  // 0x0072f830 (stays in the slice: not this object's)

// ---- items of slice s00730240 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct EltArray
{
    int32_t  mNumElts;    // +0x00
    uint8_t* mData;       // +0x04
    uint16_t mEltSize;    // +0x08
    uint16_t mEltStride;  // +0x0a
    void*    mDataRC;     // +0x0c
};
static inline float Pal(uint8_t* base, int idx, int off)
{
    return *(float*)(base + (uint32_t)idx * 16u + off);
}
static inline int32_t ElemU32(EltArray* a, int i)
{
    return *(int32_t*)(a->mData + (uint32_t)a->mEltStride * (uint32_t)i);
}
// ---- items of slice s00730240 end

// ---- items of slice s00732410 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct EltArray_s0073_2410
{
    int32_t  mNumElts;    // +0x00
    uint8_t* mData;       // +0x04
    uint16_t mEltSize;    // +0x08
    uint16_t mEltStride;  // +0x0a
    void*    mRC;         // +0x0c
};
int  FUN_0071ddc0(int, int, int, int, int);
struct RefCnt
{
    virtual void AddRef();
    virtual void Release();
};
struct Mat4 { float m[16]; };
struct ContV
{
    virtual void Init(int);
    char    pad[8];
    int32_t mC;    // +0x0c
    int32_t m10;   // +0x10
    EltArray_s0073_2410* Make16(EltArray_s0073_2410* out);
    EltArray_s0073_2410* Make4(EltArray_s0073_2410* out);
};
// ---- items of slice s00732410 end

// ---- items of slice s00733400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_masks[];
extern void* g_vtblEditor;
extern void* g_vtblCreatureAbility; // 0x013ef094
extern void* g_vtblA; // 0x013ebcc8
extern void* g_vtblB; // 0x013ef8d4
struct IRefCounted { virtual void AddRef(); virtual void Release(); };  // vt[0]=AddRef, vt[1]=Release
static void RefAddRef(void* o)  { if (o) ((IRefCounted*)o)->AddRef(); }
static void RefRelease(void* o) { if (o) ((IRefCounted*)o)->Release(); }
struct EltArray_s0073_3400
{
    int32_t  mNumElts;
    uint8_t* mData;
    uint16_t mEltSize;
    uint16_t mEltStride;
    void*    mRC;
    void Assign(EltArray_s0073_3400* other);   // 0x00424F70 (thiscall, ret 4) — addrefs other->mRC
};
struct StreamEntry
{
    int      mIndexFmt;   // +0x00
    int      mField04;    // +0x04
    int      mFormat;     // +0x08
    int      mField0c;    // +0x0c
    EltArray_s0073_3400 mSrc;        // +0x10
};
struct StreamVec
{
    int          mField00;   // +0x00
    int          mField04;   // +0x04
    StreamEntry* mBegin;     // +0x08
    StreamEntry* mEnd;       // +0x0c
};
struct VecHolder
{
    int* mBegin; int* mEnd; int* mCap;
    int* ZeroFill(int param_2, int param_3);
    void Insert(void* param_2, void* param_3);
    void FUN_006fa770(int param_2, int param_3);   // 006FA770 DoAllocate (thiscall, ret 8)
};
void  FUN_00733070(int, void*);
void  FUN_006a4600(int, void*);
void  FUN_007c7a40(int, void*);
void  FUN_0047cae0(int, int, void*, int);
int   FUN_00a11310(int, int, int);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);
void  FUN_00733a50_ext(void*);   // 0x00733A50 (external view of the same callee)
void  FUN_00733f20(void*);
int   FUN_0071ddc0(void*, int, int, int, int);
struct CtorObj
{
    void* mVT0;
    void* mVT1;
    int   mRef;      // +0x08
    int   mArr;      // +0x0c
    int   mArrEnd;   // +0x10
    int   mPad[3];
    int   mLast;     // +0x20

    void ctor_c0(int arg);
    void ctor_640(int arg);
    void ctor_6e0(int arg);
    void ctor_760(int arg);
    EltArray_s0073_3400* MakeChartRef(EltArray_s0073_3400* tmp);   // 0x007217C0
    EltArray_s0073_3400* Make16(EltArray_s0073_3400* tmp);         // 0x00732FB0
    EltArray_s0073_3400* Make4(EltArray_s0073_3400* tmp);          // 0x00732FF0
    EltArray_s0073_3400* GetHandle(EltArray_s0073_3400* tmp);      // 0x006C32F0
};
// ---- items of slice s00733400 end

// ---- items of slice s00734380 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct EltArray_s0073_4380
{
    int32_t  mNumElts;
    uint8_t* mData;
    uint16_t mEltSize;
    uint16_t mEltStride;
    void*    mRC;
};
struct SlotObj
{
    int32_t  m0;
    int32_t  m4;
    int32_t  m8;
    int32_t  mC;
    EltArray_s0073_4380 mElt;      // +0x10
};
struct VObj { void* vt[1]; };
#define VT(p) (((VObj*)(p))->vt)
typedef void      (__thiscall *Fn_vv)(void*);
typedef void      (__thiscall *Fn_vvp)(void*, void*);
typedef void*     (__thiscall *Fn_pvi)(void*, int);
typedef EltArray_s0073_4380* (__thiscall *Fn_pav)(void*, void*);
void  FUN_00734380(int, int, float);
int*  FUN_00733760(int);
EltArray_s0073_4380* FUN_00732ff0(void*);
void  FUN_00424f70(void*);
void* FUN_00758630(uint32_t, int, int);
void  FUN_00733920(void*, void*);
struct Vec3Vec { int m[5];
    int Emplace(int param_2, int* param_3);
    Vec3Vec* AssignInts(Vec3Vec* param_2);
    Vec3Vec* AssignRefs(Vec3Vec* param_2); };
// ---- items of slice s00734380 end

// ---- items of slice s00735350 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec
{
    int*   mBegin;   // +0x00
    int*   mEnd;     // +0x04
    int*   mCap;     // +0x08
    void*  mEmptyRef; // +0x0c (shared-empty sentinel; copied by the copy ctor)
    int    pad1;     // +0x10
    int8_t mFlag;    // +0x14

    void   copyCtor(Vec* src);          // 0x72ac10 (thiscall; builds *this from *src)
    void   assign(Vec* src);            // 0x7348a0 (thiscall; *this = *src)
    void   FUN_007353c0(Vec* other);    // 0x7353c0 (thiscall; swap-or-assign)
    int*   insertL(int* a, int* b);     // 0x735350
    int*   FUN_00734660(int* a, int* b); // 0x734660 (thiscall helper, ecx = this)
    void   FUN_00b85500(int* dst, int* src); // 0xb85500 Vertex3DVec::CopyUninit (thiscall)
    void   FUN_007346d0(int* dst, int count, int value); // 0x7346d0 fill/construct (thiscall)
    int*   FUN_007334b0(uint32_t n, int src, int srcEnd); // 0x7334b0 realloc (thiscall)
    void   FUN_00714b10(int from, int to); // 0x714b10 destroy range (thiscall)
    int*   operator=(int* other);       // 0x735dd0
    int*   findLower(int* key);         // 0x735ec0
    void   resize24(uint32_t n, int v); // 0x735f30
    void   fill(uint32_t n, int* v);   // 0x736090
    void   DoAllocate(uint32_t n, int* flags); // 0x72a1a0 (thiscall; build n-element buffer)
};
// ---- items of slice s00735350 end

// ---- items of slice s0073a110 begin (TODO(rewrite): local stubs, replace by canonical classes)
class RefObj {
public:
    virtual void vfunc0(int) = 0;   // slot 0
    virtual void vfunc1() = 0;      // slot 1
    int mnRefCount;                 // +4
};
struct RefPtr {
    RefObj* mpObj;                  // +0
    void Release();
};
struct FlagObj {
    char pad[8];
    uint32_t mFlags;                // +8
    void SetFlags(bool a, bool b);
};
struct Mat24 { int d[9]; };
struct MatOwner {
    char pad0[0x14];
    Mat24 mMat;                     // +0x14
    bool GetMat(Mat24* out);
};
struct Mat43In {
    int f0;             // +0
    union { float tx; int txBits; };    // +4
    union { float ty; int tyBits; };    // +8
    union { float tz; int tzBits; };    // +0xc
    float scale;        // +0x10
    float r[3][3];      // +0x14 (packed, stride 3)
    // +0x38 ...
};
struct Mat44Out {
    float r[3][4];      // +0..+0x2c (padded, stride 4)
    float tx, ty, tz;   // +0x30
};
// ---- items of slice s0073a110 end

// @ 0x00730210
void FUN_00730210(int* p, int param_2)
{
    int  b8    = *(int*)((char*)p + 0xb8);
    int  base  = p[6];
    int  count = (p[7] - base) >> 2;
    FUN_0072f830(count, (void*)base, (void*)b8, (void*)param_2, (void*)p);
}

// @ 0x00730240
uint32_t FUN_00730240(EltArray* p1, EltArray* p2, uint32_t p3, EltArray* p4, EltArray* p5, EltArray* p6, EltArray* p7, EltArray* p8, EltArray* p9, uint8_t* p10, char p11)
{
    bool hasA = p7->mData != 0;
    bool hasB = p9->mData != 0;

    bool weighted = (p3 > 1) && (p2->mData != 0);

    if (p11 != 0)
    {
        if (hasA)
            p11 = 1;
        else
        {
            p11 = 0;
            if (hasB)
                p11 = 1;
        }
    }

    // When exactly four influence weights are packed in one dword, drop the trailing zero
    // channels (a colour key can store fewer than four weights).
    if (weighted && p3 == 4)
    {
        uint32_t v = *(uint32_t*)p2->mData;
        uint32_t cnt;
        if ((v & 0xff000000u) == 0)
        {
            if (p2->mNumElts > 0)
            {
                uint8_t* q = p2->mData;
                int n = p2->mNumElts - 1;
                while (n--)
                {
                    q += p2->mEltStride;
                    v |= *(uint32_t*)q;
                }
            }
            cnt = ((v & 0xffu) != 0);
            if (((v >> 8) & 0xffu) != 0)  ++cnt;
            if (((v >> 16) & 0xffu) != 0) ++cnt;
            if (((v >> 24) & 0xffu) != 0) ++cnt;
        }
        else
            cnt = 4;
        if (cnt < 4)
            p3 = cnt;
        weighted = p3 > 1;
    }

    int32_t count = p4->mNumElts;
    if (count <= 0)
        return (uint32_t)count;

    // The retail routine leaves its last computed packed value in eax (the caller-visible
    // return slot): the second normal stream if it ran, else the first, else the position
    // output pointer it just stored through; an empty range returns the element count.
    uint32_t rv = 0;

    float d4 = 1.0f;  // inverse squared length, row 0
    float d0 = 1.0f;  // inverse squared length, row 1
    float cc = 1.0f;  // inverse squared length, row 2

    for (int i = 0; i < count; ++i)
    {
        uint8_t* idxp = p1->mData + (uint32_t)p1->mEltStride * (uint32_t)i;
        float m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11;

        if (weighted)
        {
            uint32_t u = *(uint32_t*)(p2->mData + (uint32_t)p2->mEltStride * (uint32_t)i);
            float w[4];
            w[0] = (float)(u & 0xffu)          * 0.003921569f;
            w[1] = (float)((u >> 8) & 0xffu)   * 0.003921569f;
            w[2] = (float)((u >> 16) & 0xffu)  * 0.003921569f;
            w[3] = (float)((u >> 24) & 0xffu)  * 0.003921569f;

            m2  = Pal(p10, idxp[0], 0x08) * w[0];
            m0  = w[0] * Pal(p10, idxp[0], 0x00);
            m1  = Pal(p10, idxp[0], 0x04) * w[0];
            m3  = Pal(p10, idxp[0], 0x0c) * w[0];
            m5  = Pal(p10, idxp[0], 0x14) * w[0];
            m7  = Pal(p10, idxp[0], 0x1c) * w[0];
            m4  = w[0] * Pal(p10, idxp[0], 0x10);
            m6  = Pal(p10, idxp[0], 0x18) * w[0];
            m8  = Pal(p10, idxp[0], 0x20) * w[0];
            m9  = Pal(p10, idxp[0], 0x24) * w[0];
            m10 = Pal(p10, idxp[0], 0x28) * w[0];
            m11 = Pal(p10, idxp[0], 0x2c) * w[0];

            for (uint32_t k = 1; k < p3; ++k)
            {
                float f = w[k];
                uint8_t* p = p10 + (uint32_t)idxp[k] * 16u;
                m0  = f * *(float*)(p + 0x00) + m0;
                m1  = *(float*)(p + 0x04) * f + m1;
                m2  = *(float*)(p + 0x08) * f + m2;
                m3  = *(float*)(p + 0x0c) * f + m3;
                m6  = m6  + *(float*)(p + 0x18) * f;
                m4  = m4  + *(float*)(p + 0x10) * f;
                m5  = m5  + *(float*)(p + 0x14) * f;
                m10 = m10 + *(float*)(p + 0x28) * f;
                m7  = m7  + *(float*)(p + 0x1c) * f;
                m9  = m9  + *(float*)(p + 0x24) * f;
                m8  = m8  + *(float*)(p + 0x20) * f;
                m11 = m11 + *(float*)(p + 0x2c) * f;
            }
        }
        else
        {
            uint8_t* p = p10 + (uint32_t)idxp[0] * 16u;
            m0  = *(float*)(p + 0x00);
            m1  = *(float*)(p + 0x04);
            m2  = *(float*)(p + 0x08);
            m3  = *(float*)(p + 0x0c);
            m4  = *(float*)(p + 0x10);
            m5  = *(float*)(p + 0x14);
            m6  = *(float*)(p + 0x18);
            m7  = *(float*)(p + 0x1c);
            m8  = *(float*)(p + 0x20);
            m9  = *(float*)(p + 0x24);
            m10 = *(float*)(p + 0x28);
            m11 = *(float*)(p + 0x2c);
        }

        if (p11 != 0)
        {
            d4 = 1.0f / ((m0 * m0 + m4 * m4) + m8 * m8);
            d0 = 1.0f / ((m1 * m1 + m5 * m5) + m9 * m9);
            cc = 1.0f / ((m2 * m2 + m6 * m6) + m10 * m10);
        }

        float* pin  = (float*)(p4->mData + (uint32_t)p4->mEltStride * (uint32_t)i);
        float  px = pin[0];
        float  py = pin[1];
        float  pz = pin[2];
        float* pout = (float*)(p5->mData + (uint32_t)p5->mEltStride * (uint32_t)i);
        pout[0] = ((px * m0 + pz * m2) + py * m1) + m3;
        pout[1] = ((m4 * px + m6 * pz) + m5 * py) + m7;
        pout[2] = ((m8 * px + m10 * pz) + m9 * py) + m11;

        if (hasA)
        {
            uint32_t u = (uint32_t)ElemU32(p6, i);
            float r = (float)(u & 0xffu)         * 0.007874016f - 1.0f;
            float g = (float)((u >> 8) & 0xffu)  * 0.007874016f - 1.0f;
            float b = (float)((u >> 16) & 0xffu) * 0.007874016f - 1.0f;
            float c8 = (r * m0 + b * m2 + g * m1) * d4;
            float c0 = (m8 * r + m10 * b + m9 * g) * cc;
            float c4 = (m4 * r + m6 * b + m5 * g) * d0;
            float inv = 1.0f / sqrtf((c4 * c4 + (c0 * c0 + c8 * c8)) + 1e-08f);
            float x = inv * c8;
            float y = c4 * inv;
            float z = c0 * inv;
            uint32_t packed =
                ((((uint32_t)(int32_t)(z * 127.0f) + 0x7fu) << 8) |
                  ((uint32_t)(int32_t)(y * 127.0f) + 0x7fu)) << 8 |
                  ((uint32_t)(int32_t)(x * 127.0f) + 0x7fu);
            *(uint32_t*)(p7->mData + (uint32_t)p7->mEltStride * (uint32_t)i) = packed;
            rv = packed;
        }

        if (!hasA)
            rv = (uint32_t)(uintptr_t)pout;

        if (hasB)
        {
            uint32_t u = (uint32_t)ElemU32(p8, i);
            float r = (float)(u & 0xffu)         * 0.007874016f - 1.0f;
            float g = (float)((u >> 8) & 0xffu)  * 0.007874016f - 1.0f;
            float b = (float)((u >> 16) & 0xffu) * 0.007874016f - 1.0f;
            float b0 = (r * m0 + b * m2 + g * m1) * d4;
            float a8 = (m8 * r + m10 * b + m9 * g) * cc;
            float ac = (m4 * r + m6 * b + m5 * g) * d0;
            float inv = 1.0f / sqrtf((b0 * b0 + (ac * ac + a8 * a8)) + 1e-08f);
            float x = inv * b0;
            float y = ac * inv;
            float z = a8 * inv;
            uint32_t packed =
                ((((uint32_t)(int32_t)(z * 127.0f) + 0x7fu) << 8) |
                  ((uint32_t)(int32_t)(y * 127.0f) + 0x7fu)) << 8 |
                  ((uint32_t)(int32_t)(x * 127.0f) + 0x7fu);
            *(uint32_t*)(p9->mData + (uint32_t)p9->mEltStride * (uint32_t)i) = packed;
            rv = packed;
        }
    }

    return rv;
}

// @ 0x00732a30
void FUN_00732a30(int param_1, float* param_2)
{
    int iVar4 = FUN_0071ddc0(param_1, 1, 0, 3, 0xe);
    if (iVar4 < 0)
        return;
    int iVar2 = *(int*)(param_1 + 8);
    iVar4 = iVar4 * 0x20;
    int iVar6 = *(int*)(iVar4 + 0x10 + iVar2);
    uint16_t uVar1 = *(uint16_t*)(iVar4 + 0x1a + iVar2);
    iVar2 = iVar4 + 0x10 + iVar2;
    RefCnt* piVar3 = *(RefCnt**)(iVar2 + 0xc);
    int iVar4b = *(int*)(iVar2 + 4);
    if (piVar3 != 0)
        piVar3->AddRef();

    float fVar8 = 0.0f;
    float local_10 = 0.0f;
    if (iVar6 > 0)
    {
        float* pfVar5 = (float*)(iVar4b + 4);
        do
        {
            float fVar7 = *pfVar5 * *pfVar5 + pfVar5[-1] * pfVar5[-1];
            if (fVar8 < fVar7)
                fVar8 = fVar7;
            if (*param_2 <= param_2[3])
            {
                fVar7 = pfVar5[-1];
                if (*param_2 <= fVar7)
                {
                    if (param_2[3] < fVar7)
                        param_2[3] = fVar7;
                }
                else
                {
                    *param_2 = fVar7;
                }
                fVar7 = *pfVar5;
                if (param_2[1] <= fVar7)
                {
                    if (param_2[4] <= fVar7 && fVar7 != param_2[4])
                        param_2[4] = fVar7;
                }
                else
                {
                    param_2[1] = fVar7;
                }
                fVar7 = pfVar5[1];
                if (param_2[2] <= fVar7)
                {
                    if (param_2[5] <= fVar7 && fVar7 != param_2[5])
                        param_2[5] = fVar7;
                }
                else
                {
                    param_2[2] = fVar7;
                }
            }
            else
            {
                *param_2 = pfVar5[-1];
                param_2[1] = *pfVar5;
                param_2[2] = pfVar5[1];
                param_2[3] = pfVar5[-1];
                param_2[4] = *pfVar5;
                param_2[5] = pfVar5[1];
            }
            pfVar5 = (float*)((uint8_t*)pfVar5 + uVar1);
            iVar6 = iVar6 - 1;
            local_10 = fVar8;
        } while (iVar6 != 0);
    }
    local_10 = sqrtf(local_10);
    if (*param_2 <= param_2[3])
    {
        if (*param_2 <= local_10)
        {
            if (param_2[3] < local_10)
                param_2[3] = local_10;
        }
        else
        {
            *param_2 = local_10;
        }
        if (param_2[1] <= 0.0f) { if (param_2[4] <= 0.0f && param_2[4] != 0.0f) param_2[4] = 0.0f; }
        else                    { param_2[1] = 0.0f; }
        if (param_2[2] <= 0.0f) { if (param_2[5] <= 0.0f && param_2[5] != 0.0f) param_2[5] = 0.0f; }
        else                    { param_2[2] = 0.0f; }
    }
    else
    {
        *param_2 = local_10;
        param_2[3] = local_10;
        param_2[1] = 0.0f;
        param_2[4] = 0.0f;
        param_2[2] = 0.0f;
        param_2[5] = 0.0f;
    }
    local_10 = -local_10;
    if (*param_2 <= param_2[3])
    {
        if (*param_2 <= local_10)
        {
            if (param_2[3] < local_10)
                param_2[3] = local_10;
        }
        else
        {
            *param_2 = local_10;
        }
        if (param_2[1] <= 0.0f) { if (param_2[4] <= 0.0f && param_2[4] != 0.0f) param_2[4] = 0.0f; }
        else                    { param_2[1] = 0.0f; }
        if (param_2[2] <= 0.0f) { if (param_2[5] <= 0.0f && param_2[5] != 0.0f) param_2[5] = 0.0f; }
        else                    { param_2[2] = 0.0f; }
    }
    else
    {
        *param_2 = local_10;
        param_2[3] = local_10;
        param_2[1] = 0.0f;
        param_2[4] = 0.0f;
        param_2[2] = 0.0f;
        param_2[5] = 0.0f;
    }
    if (piVar3 != 0)
        piVar3->Release();
}

// @ 0x00732eb0
unsigned FUN_00732eb0(const float* src, Mat4* out)
{
    float tmp[16];
    tmp[0] = src[0];
    tmp[1] = src[4];
    tmp[2] = src[8];
    tmp[3] = 0.0f;
    tmp[4] = src[1];
    tmp[5] = src[5];
    tmp[6] = src[9];
    tmp[7] = 0.0f;
    tmp[8] = src[2];
    tmp[9] = src[6];
    tmp[10] = src[10];
    tmp[11] = 0.0f;
    tmp[12] = 0.0f;
    tmp[13] = 0.0f;
    tmp[14] = 0.0f;
    tmp[15] = 1.0f;
    memcpy(out->m, tmp, sizeof(tmp));
    out->m[0xc] = src[3];
    out->m[0xd] = src[7];
    out->m[0xe] = src[0xb];
    out->m[0xf] = 1.0f;
    // retail leaves src[0xb] in eax (the last dword it stores into the matrix)
    return *(const unsigned*)&src[0xb];
}

// @ 0x00732fb0
EltArray_s0073_2410* ContV::Make16(EltArray_s0073_2410* out)
{
    int iVar1 = mC;
    int iVar2 = m10;
    out->mData = (uint8_t*)iVar1;
    out->mNumElts = (iVar2 - iVar1) >> 4;
    out->mEltStride = 0x10;
    out->mEltSize = 0x10;
    out->mRC = this;
    Init(0);
    return out;
}

// @ 0x00733140
void FUN_00733140(int* param_1, float* param_2, float* param_3, float* param_4)
{
    *param_1 = (int)param_4;
    if (param_2 != param_3)
    {
        do
        {
            if (param_4 != 0)
            {
                param_4[0] = param_2[0];
                param_4[1] = param_2[1];
                param_4[2] = param_2[2];
                param_4[3] = param_2[3];
                param_4[4] = param_2[4];
                param_4[5] = param_2[5];
                param_4[6] = param_2[6];
                param_4[7] = param_2[7];
                param_4[8] = param_2[8];
            }
            param_2 += 9;
            param_4 += 9;
        } while (param_2 != param_3);
        *param_1 = (int)param_4;
    }
}

// @ 0x00733230
float* FUN_00733230(float* param_1, int param_2, float* param_3)
{
    for (; param_2 != 0; param_2 = param_2 + -1)
    {
        if (param_1 != 0)
        {
            param_1[0] = param_3[0];
            param_1[1] = param_3[1];
            param_1[2] = param_3[2];
            param_1[3] = param_3[3];
            param_1[4] = param_3[4];
            param_1[5] = param_3[5];
            param_1[6] = param_3[6];
            param_1[7] = param_3[7];
            param_1[8] = param_3[8];
        }
        param_1 += 9;
    }
    return param_1;
}

// @ 0x00733310
void FUN_00733310(float* param_1, float* param_2, float* param_3)
{
    if (param_1 != param_2)
    {
        do
        {
            if (param_3 != 0)
            {
                param_3[0] = param_1[0];
                param_3[1] = param_1[1];
                param_3[2] = param_1[2];
                param_3[3] = param_1[3];
                param_3[4] = param_1[4];
                param_3[5] = param_1[5];
                param_3[6] = param_1[6];
                param_3[7] = param_1[7];
                param_3[8] = param_1[8];
            }
            param_1 += 9;
            param_3 += 9;
        } while (param_1 != param_2);
    }
}

// @ 0x00733510
void* FUN_00733510(int* param_1, int* param_2, int* param_3, int* param_4, int* param_5, int param_6)
{
    while (param_1 != param_2 && param_3 != param_4)
    {
        uint32_t mask = g_masks[*(uint16_t*)(param_6 + 8)];
        uint32_t a = *(uint32_t*)(*param_3 * (uint32_t)*(uint16_t*)(param_6 + 10) + *(int*)(param_6 + 4));
        uint32_t b = *(uint32_t*)(*(int*)(param_6 + 4) + *param_1 * (uint32_t)*(uint16_t*)(param_6 + 10));
        if ((a & mask) < (b & mask))
        {
            int v = *param_3;
            param_3++;
            *param_5 = v;
        }
        else
        {
            *param_5 = *param_1;
            param_1++;
        }
        param_5++;
    }
    int n1 = (int)param_2 - (int)param_1;
    void* r = memcpy(param_5, param_1, n1);
    int n2 = (int)param_4 - (int)param_3;
    r = memcpy((char*)r + (n1 >> 2) * 4, param_3, n2);
    return (char*)r + (n2 >> 2) * 4;
}

// @ 0x00733640
void CtorObj::ctor_640(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    char buf[16];
    FUN_007c7a40(arg, &arg);
    FUN_0047cae0(mArr, arg, buf, arg);
    mArrEnd = arg * 0x10 + mArr;
    mLast = 0;
}

// @ 0x007336e0
void CtorObj::ctor_6e0(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    FUN_006a4600(arg, &arg);
    mLast = 0;
}

// @ 0x00733760
void CtorObj::ctor_760(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    FUN_00733070(arg, &arg);
    int* p = (int*)mArr;
    for (int n = arg; n != 0; --n)
    {
        if (p)
            *p = 0;
        p++;
    }
    mArrEnd = mArr + arg * 4;
    mLast = 0;
}

// @ 0x00733920
void VecHolder::Insert(void* param_2, void* param_3)
{
    int* param_1 = (int*)this;
    int* puVar3 = (int*)param_1[1];
    if (puVar3 != (int*)param_1[2])
    {
        if ((param_2 <= param_3) && (param_3 < puVar3))
            param_3 = (char*)param_3 + 0xc;
        if (puVar3 != 0)
        {
            puVar3[0] = puVar3[-3];
            puVar3[1] = puVar3[-2];
            puVar3[2] = puVar3[-1];
        }
        puVar3 = (int*)param_1[1];
        int* puVar1 = (int*)param_1[1];
        while (puVar1 - 3 != param_2)
        {
            puVar3[-3] = puVar1[-6];
            puVar3[-2] = puVar1[-5];
            puVar3[-1] = puVar1[-4];
            puVar3 -= 3;
            puVar1 -= 3;
        }
        *(int*)param_2 = *(int*)param_3;
        ((int*)param_2)[1] = ((int*)param_3)[1];
        ((int*)param_2)[2] = ((int*)param_3)[2];
        param_1[1] = param_1[1] + 0xc;
        return;
    }
    int iVar5 = ((int)puVar3 - *param_1) / 0xc;
    int iVar2;
    if (iVar5 == 0)
    {
        iVar5 = 1;
        iVar2 = (int)EAAlloc(iVar5 * 0xc, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    else
    {
        iVar5 = iVar5 * 2;
        if (iVar5 == 0)
            iVar2 = 0;
        else
            iVar2 = (int)EAAlloc(iVar5 * 0xc, "Graphics", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    puVar3 = (int*)FUN_00a11310(*param_1, (int)param_2, iVar2);
    if (puVar3 != 0)
    {
        puVar3[0] = *(int*)param_3;
        puVar3[1] = ((int*)param_3)[1];
        puVar3[2] = ((int*)param_3)[2];
    }
    int iVar4 = FUN_00a11310((int)param_2, param_1[1], (int)(puVar3 + 3));
    if (*param_1 != 0)
        EAFree((void*)*param_1);
    *param_1 = iVar2;
    param_1[1] = iVar4;
    param_1[2] = iVar2 + iVar5 * 0xc;
}

// @ 0x00733e90
void FUN_00733e90(int param_1, int param_2, int param_3)
{
    for (int i = 0; i < param_2; i++)
        FUN_00733a50_ext((void*)(*(int*)(param_3 + i * 4) * 0x20 + *(int*)(param_1 + 8)));
}

// @ 0x00733ed0
void FUN_00733ed0(int param_1)
{
    int count = (*(int*)(param_1 + 0xc) - *(int*)(param_1 + 8)) >> 5;
    for (int i = 0; i < count; ++i)
    {
        int v = *(int*)(*(int*)(param_1 + 8) + i * 0x20);
        if (((v == 8) || (v == 2)) || (v == 3) || (v == 10))
            FUN_00733a50_ext((void*)(*(int*)(param_1 + 8) + i * 0x20));
    }
}

// @ 0x00733f20
void FUN_00733f20(void* pm)
{
    StreamVec* model = (StreamVec*)pm;
    int gatherCount = 4;    // component count of the index-10 stream (defaults to 4)

    int idx10 = FUN_0071ddc0(pm, 10, -1, 0, 0xe);
    if (idx10 >= 0)
    {
        StreamEntry* e = (StreamEntry*)((char*)model->mBegin + idx10 * 0x20);
        if (e->mFormat > 0 && e->mFormat < 5)
        {
            uint32_t count = (uint32_t)e->mSrc.mNumElts;
            CtorObj* res = (CtorObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
            if (res)
                res->ctor_760((int)count);
            else
                res = 0;
            if (res)
                RefAddRef(res);

            gatherCount = e->mFormat;
            float ftmp[4];
            EltArray_s0073_3400* tmp = (EltArray_s0073_3400*)ftmp;
            ftmp[1] = 0.0f;
            ftmp[2] = 0.0f;
            ftmp[3] = 0.0f;
            for (uint32_t v = 0; v < count; ++v)
            {
                if (gatherCount != 0)
                {
                    float* src = (float*)((char*)e->mSrc.mData + e->mSrc.mEltStride * v);
                    for (int k = 0; k < gatherCount; ++k)
                        ftmp[k] = src[k];
                }
                float g = ftmp[1] * 255.0f;
                float b = ftmp[2] * 255.0f;
                float a = ftmp[3] * 255.0f;
                *(uint32_t*)(res->mArr + 4 * (int)v) =
                    ((((int)a << 8 | (int)b) << 8 | (int)g) << 8) |
                    ((0xff - (int)a) - (int)b) - (int)g;
            }

            EltArray_s0073_3400* h = res->Make4(tmp);
            int f04 = e->mField04;
            int f0c = e->mField0c;
            EltArray_s0073_3400 localSrc = *h;
            if (localSrc.mRC)
                RefAddRef(localSrc.mRC);

            e->mIndexFmt = 10;
            e->mField04 = f04;
            e->mFormat = 10;
            e->mField0c = f0c;
            e->mSrc.Assign(&localSrc);

            if (localSrc.mRC)
                RefRelease(localSrc.mRC);
            if (tmp->mRC)
                RefRelease(tmp->mRC);
            if (res)
                RefRelease(res);
        }
    }

    int idx9 = FUN_0071ddc0(pm, 9, -1, 0, 0xe);
    if (idx9 >= 0)
    {
        StreamEntry* e = (StreamEntry*)((char*)model->mBegin + idx9 * 0x20);
        if (e->mFormat == 8 || e->mFormat == 9)
        {
            uint32_t count = (uint32_t)e->mSrc.mNumElts;
            CtorObj* res = (CtorObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
            if (res)
                res->ctor_760((int)count);
            else
                res = 0;
            if (res)
                RefAddRef(res);

            for (uint32_t v = 0; v < count; ++v)
            {
                uint32_t stride = e->mSrc.mEltStride;
                int data = (int)e->mSrc.mData;
                uint32_t acc = 0;
                for (uint32_t k = 0; k < (uint32_t)gatherCount; ++k)
                    ((uint8_t*)&acc)[k] = *(uint8_t*)(stride * v + data + k * 2);
                *(uint32_t*)(res->mArr + 4 * (int)v) = acc;
            }

            float ftmp[4];
            EltArray_s0073_3400* tmp = (EltArray_s0073_3400*)ftmp;
            EltArray_s0073_3400* h = res->Make4(tmp);
            int f04 = e->mField04;
            int f0c = e->mField0c;
            e->mIndexFmt = 9;
            e->mField04 = f04;
            e->mFormat = 7;
            e->mField0c = f0c;
            e->mSrc.mNumElts = h->mNumElts;
            e->mSrc.mData = h->mData;
            e->mSrc.mEltSize = h->mEltSize;
            e->mSrc.mEltStride = h->mEltStride;
            void* newRC = h->mRC;
            void* oldRC = e->mSrc.mRC;
            if (newRC != oldRC)
            {
                if (newRC)
                    RefAddRef(newRC);
                e->mSrc.mRC = newRC;
                if (oldRC)
                    RefRelease(oldRC);
            }
            if (newRC)
                RefRelease(newRC);
            if (tmp->mRC)
                RefRelease(tmp->mRC);
            if (res)
                RefRelease(res);
        }
    }
}

// @ 0x00734380
void FUN_00734380(int param_1, int param_2, float fac)
{
    (void)fac;
    float f3[3];
    int idx = FUN_0071ddc0(param_1, param_2, -1, 0, 0xe);
    if (idx < 0) return;

    SlotObj* slot = (SlotObj*)(*(int*)(param_1 + 8) + idx * 0x20);
    if (!(slot->m8 > 2 && slot->m8 < 5)) return;

    uint32_t n = (uint32_t)slot->mElt.mNumElts;
    uint8_t* src = slot->mElt.mData;
    uint16_t stride = slot->mElt.mEltStride;

    void* mem = EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
    void* obj;
    if (mem != 0) obj = ((Fn_pvi)FUN_00733760)(mem, (int)n);
    else          obj = 0;

    if (obj != 0) ((Fn_vv)VT(obj)[0])(obj);

    if (n != 0)
    {
        int* out = (int*)((void**)obj)[3];
        for (uint32_t i = 0; i < n; i++)
        {
            float* s = (float*)(src + i * stride);
            float x = s[0], y = s[1], z = s[2];
            int r = (int)(x * 127.0f) + 0x7f;
            int g = (int)(y * 127.0f) + 0x7f;
            int b = (int)(z * 127.0f) + 0x7f;
            out[i] = (((b << 8) | g) << 8) | r;
            f3[0] = x; f3[1] = y; f3[2] = z;
        }
    }

    EltArray_s0073_4380* ea = ((Fn_pav)FUN_00732ff0)(obj, f3);

    SlotObj tmp;
    tmp.m0     = param_2;
    tmp.m4     = slot->m4;
    tmp.m8     = 7;
    tmp.mC     = slot->mC;
    tmp.mElt   = *ea;
    if (tmp.mElt.mRC != 0) ((Fn_vv)VT(tmp.mElt.mRC)[0])(tmp.mElt.mRC);

    slot->m0 = param_2;
    slot->m8 = 7;
    ((Fn_vvp)FUN_00424f70)(&slot->mElt, &tmp.mElt);

    if (tmp.mElt.mRC != 0) ((Fn_vv)VT(tmp.mElt.mRC)[1])(tmp.mElt.mRC);
    void* h30 = 0;              // original reads an unwritten frame slot here
    if (h30 != 0) ((Fn_vv)VT(h30)[1])(h30);
    if (obj != 0) ((Fn_vv)VT(obj)[1])(obj);
}

// @ 0x007345c0
void FUN_007345c0(int param_1)
{
    FUN_00734380(param_1, 3, 0.5f);
    FUN_00734380(param_1, 2, 0.5f);
}

// @ 0x00734660
int Vec3Vec::Emplace(int param_2, int* param_3)
{
    int* param_1 = (int*)this;
    int* puVar1 = (int*)param_1[1];
    int iVar2 = (param_2 - *param_1) / 0xc;
    if ((param_2 == (int)puVar1) && (puVar1 != (int*)param_1[2]))
    {
        param_1[1] = (int)(puVar1 + 3);
        if (puVar1 != 0)
        {
            puVar1[0] = param_3[0];
            puVar1[1] = param_3[1];
            puVar1[2] = param_3[2];
            return *param_1 + iVar2 * 0xc;
        }
    }
    else
    {
        FUN_00733920((void*)param_2, param_3);
    }
    return *param_1 + iVar2 * 0xc;
}

// @ 0x007348a0
Vec3Vec* Vec3Vec::AssignInts(Vec3Vec* p2)
{
    int* param_1 = (int*)this; int* param_2 = (int*)p2;
    if (param_2 != param_1)
    {
        int pvVar1 = *param_2;
        int _Dst = *param_1;
        int iVar2 = param_2[1];
        uint32_t uVar5 = (uint32_t)(iVar2 - pvVar1) >> 2;
        if ((uint32_t)(param_1[2] - _Dst) >> 2 < uVar5)
        {
            int iVar3 = (int)FUN_00758630(uVar5, pvVar1, iVar2);
            int t = *param_1;
            if (t != 0 && t != param_1[4])
                EAFree((void*)t);
            *param_1 = iVar3;
            param_1[2] = iVar3 + uVar5 * 4;
            param_1[1] = iVar3 + uVar5 * 4;
            return (Vec3Vec*)param_1;
        }
        uint32_t uVar4 = (uint32_t)(param_1[1] - _Dst) >> 2;
        if (uVar4 < uVar5)
        {
            memcpy((void*)_Dst, (void*)pvVar1, uVar4 * 4);
            int src = *param_2 + ((param_1[1] - *param_1) >> 2) * 4;
            memcpy((void*)param_1[1], (void*)src, param_2[1] - src);
            param_1[1] = *param_1 + uVar5 * 4;
            return (Vec3Vec*)param_1;
        }
        memcpy((void*)_Dst, (void*)pvVar1, iVar2 - pvVar1);
        param_1[1] = *param_1 + uVar5 * 4;
    }
    return (Vec3Vec*)param_1;
}

// @ 0x007353c0
void Vec::FUN_007353c0(Vec* other)
{
    // SSO fast path: both share the inline sentinel, so swap the three pointers.
    if ((char*)this + 0xc == (char*)other + 0xc) {
        int* t = mBegin;   mBegin = other->mBegin;   other->mBegin = t;
        t = mEnd;          mEnd = other->mEnd;       other->mEnd = t;
        t = mCap;          mCap = other->mCap;       other->mCap = t;
        return;
    }
    Vec tmp;
    tmp.copyCtor(this);
    this->assign(other);
    other->assign(&tmp);
    if (tmp.mBegin != 0 && tmp.mBegin != (int*)tmp.mEmptyRef)
        EAFree(tmp.mBegin);
}

// @ 0x0073a7a0
bool MatOwner::GetMat(Mat24* out)
{
    for (int i = 0; i < 9; ++i)
        out->d[i] = 0;
    for (int i = 0; i < 9; ++i)
        out->d[i] = mMat.d[i];
    return true;
}

// @ 0x0073a800
void FlagObj::SetFlags(bool a, bool b)
{
    if (a)
        mFlags |= 1;
    if (b)
        mFlags |= 2;
}

// @ 0x0073a820
void RefPtr::Release()
{
    RefObj* p = mpObj;
    if (p != 0) {
        int n = (*(volatile int*)&p->mnRefCount += -1);
        if (n == 0) {
            (*(volatile int*)&p->mnRefCount) = 1;
            _ReadWriteBarrier();
            p->vfunc0(1);
        }
    }
}

// @ 0x0073a850
int ScaleMat(const Mat43In* src, Mat44Out* dst)
{
    const float s = src->scale;
    dst->r[0][0] = src->r[0][0] * s;
    dst->r[0][1] = src->r[0][1] * s;
    dst->r[0][2] = src->r[0][2] * s;
    dst->r[1][0] = src->r[1][0] * s;
    dst->r[1][1] = src->r[1][1] * s;
    dst->r[1][2] = src->r[1][2] * s;
    dst->r[2][0] = src->r[2][0] * s;
    dst->r[2][1] = src->r[2][1] * s;
    dst->r[2][2] = src->r[2][2] * s;
    dst->tx = src->tx;
    dst->ty = src->ty;
    const int tz = src->tzBits;     // eax is left holding the last copied word
    dst->tz = src->tz;
    return tz;
}
