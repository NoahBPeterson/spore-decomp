// Slice s00733400 — EASTL container helpers (vector reserve/fill/insert), four EH/unwind
// constructors for a resource object, and two stream-entry reformat/build routines (0x733a50/0x733f20).
#include "types.h"
#include <string.h>

struct IRefCounted { virtual void AddRef(); virtual void Release(); };  // vt[0]=AddRef, vt[1]=Release

static void RefAddRef(void* o)  { if (o) ((IRefCounted*)o)->AddRef(); }
static void RefRelease(void* o) { if (o) ((IRefCounted*)o)->Release(); }

struct EltArray
{
    int32_t  mNumElts;
    uint8_t* mData;
    uint16_t mEltSize;
    uint16_t mEltStride;
    void*    mRC;
    void Assign(EltArray* other);   // 0x00424F70 (thiscall, ret 4) — addrefs other->mRC
};

// 0x20-byte stream entry: 4 ints then an embedded EltArray at +0x10.
struct StreamEntry
{
    int      mIndexFmt;   // +0x00
    int      mField04;    // +0x04
    int      mFormat;     // +0x08
    int      mField0c;    // +0x0c
    EltArray mSrc;        // +0x10
};

// model object holding the stream-entry array at +0x08..+0x0c (stride 0x20).
struct StreamVec
{
    int          mField00;   // +0x00
    int          mField04;   // +0x04
    StreamEntry* mBegin;     // +0x08
    StreamEntry* mEnd;       // +0x0c
};

extern uint32_t g_masks[];

struct VecHolder
{
    int* mBegin; int* mEnd; int* mCap;
    int* ZeroFill(int param_2, int param_3);
    void Insert(void* param_2, void* param_3);
    void FUN_006fa770(int param_2, int param_3);   // 006FA770 DoAllocate (thiscall, ret 8)
};

// external callees (masked relocations)
void  FUN_00733070(int, void*);
void  FUN_006a46a0(int, void*);
void  FUN_006a4600(int, void*);
void  FUN_007c7a40(int, void*);
void  FUN_0047cae0(int, int, void*, int);
int   FUN_00a11310(int, int, int);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);
void  FUN_00733a50(void*);
void  FUN_00733a50_ext(void*);   // 0x00733A50 (external view of the same callee)
void  FUN_00733f20(void*);
void  FUN_006c2690(int, void*);
int   FUN_0071ddc0(void*, int, int, int, int);

// @ 0x00733400
int* VecHolder::ZeroFill(int param_2, int param_3)
{
    int* p1 = (int*)this;
    FUN_006fa770(param_2, param_3);
    int zeros[7] = { 0, 0, 0, 0, 0, 0, 0 };
    int* dst = (int*)*p1;
    for (int n = param_2; n != 0; --n)
    {
        if (dst)
        {
            for (int k = 0; k < 7; ++k)
                dst[k] = zeros[k];
        }
        dst += 7;
    }
    p1[1] = *p1 + param_2 * 0x1c;
    return p1;
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

// --- EH/unwind constructors (vtable + cookie).  Vtable addresses are relocations; the EH
//     prolog is approximated with a plain prolog, so these are not byte-exact. --------------
extern void* g_vtblEditor;
extern void* g_vtblCreatureAbility; // 0x013ef094
extern void* g_vtblA; // 0x013ebcc8
extern void* g_vtblB; // 0x013ef8d4

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
    EltArray* MakeChartRef(EltArray* tmp);   // 0x007217C0
    EltArray* Make16(EltArray* tmp);         // 0x00732FB0
    EltArray* Make4(EltArray* tmp);          // 0x00732FF0
    EltArray* GetHandle(EltArray* tmp);      // 0x006C32F0
};

// @ 0x007335c0
void CtorObj::ctor_c0(int arg)
{
    mVT0 = g_vtblEditor;
    mVT1 = g_vtblCreatureAbility;
    mRef = 0;
    mVT0 = g_vtblA;
    mVT1 = g_vtblB;
    FUN_006a46a0(arg, &arg);
    mLast = 0;
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

// @ 0x00733a50  (reformat an element stream: index remap into a chartref handle, or unpack packed
//                colour into float4/float2; each path re-tags the entry's mFormat.)
void FUN_00733a50(void* p)
{
    StreamEntry* e = (StreamEntry*)p;
    switch (e->mFormat)
    {
    case 7:
    case 10:
    {
        if ((uint32_t)(e->mIndexFmt - 2) <= 2)
        {
            // index path: 3-dword elements, remap each index through FUN_006c2690 into a handle array.
            CtorObj* res = (CtorObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
            if (res)
                res->ctor_c0(e->mSrc.mNumElts);
            else
                res = 0;
            for (int i = 0; i < e->mSrc.mNumElts; ++i)
            {
                uint32_t h = *(uint32_t*)((char*)e->mSrc.mData + e->mSrc.mEltStride * i);
                FUN_006c2690((int)h, (void*)(res->mArr + 0xc * i));
            }
            e->mFormat = 3;
            EltArray tmp;
            EltArray* h = res->MakeChartRef(&tmp);
            e->mSrc.Assign(h);
            if (tmp.mRC)
                RefRelease(tmp.mRC);
        }
        else
        {
            // byte colour path: expand each packed byte4 into float4.
            float scale = 1.0f;
            if (e->mFormat == 10)
                scale = 0.003921569f;    // 1/255
            CtorObj* res = (CtorObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
            if (res)
                res->ctor_640(e->mSrc.mNumElts);
            else
                res = 0;
            float* dst = (float*)res->mArr;
            for (int i = 0; i < e->mSrc.mNumElts; ++i)
            {
                uint32_t v = *(uint32_t*)((char*)e->mSrc.mData + e->mSrc.mEltStride * i);
                dst[0] = (float)(v & 0xff) * scale;
                dst[1] = (float)((v >> 8) & 0xff) * scale;
                dst[2] = (float)((v >> 16) & 0xff) * scale;
                dst[3] = (float)(v >> 24) * scale;
                dst += 4;
            }
            e->mFormat = 4;
            EltArray tmp;
            EltArray* h = res->Make16(&tmp);
            e->mSrc.Assign(h);
            if (tmp.mRC)
                RefRelease(tmp.mRC);
        }
        break;
    }
    case 8:
    case 11:
    {
        // int16 pair -> float2
        CtorObj* res = (CtorObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
        if (res)
            res->ctor_6e0(e->mSrc.mNumElts);
        else
            res = 0;
        float scale = 1.0f;
        if (e->mFormat == 11)
            scale = 3.051851e-05f;       // 1/32768
        float* dst = (float*)res->mArr;
        for (int i = 0; i < e->mSrc.mNumElts; ++i)
        {
            uint32_t v = *(uint32_t*)((char*)e->mSrc.mData + e->mSrc.mEltStride * i);
            dst[0] = (float)(int)(short)v * scale;
            dst[1] = (float)(int)(short)(v >> 16) * scale;
            dst += 2;
        }
        EltArray tmp;
        EltArray* h = res->GetHandle(&tmp);
        e->mSrc.Assign(h);
        if (tmp.mRC)
            RefRelease(tmp.mRC);
        e->mFormat = 2;
        return;
    }
    case 9:
    case 12:
    {
        // two int16 pairs -> float4
        CtorObj* res = (CtorObj*)EAAlloc(0x24, "Graphics", 0, 0, 0, 0);
        if (res)
            res->ctor_640(e->mSrc.mNumElts);
        else
            res = 0;
        float scale = 1.0f;
        if (e->mFormat == 12)
            scale = 3.051851e-05f;
        float* dst = (float*)res->mArr;
        for (int i = 0; i < e->mSrc.mNumElts; ++i)
        {
            int off = e->mSrc.mEltStride * i;
            uint32_t a = *(uint32_t*)((char*)e->mSrc.mData + off);
            uint32_t b = *(uint32_t*)((char*)e->mSrc.mData + off + 4);
            dst[0] = (float)(int)(short)a * scale;
            dst[1] = (float)(int)(short)(a >> 16) * scale;
            dst[2] = (float)(int)(short)b * scale;
            dst[3] = (float)(int)(short)(b >> 16) * scale;
            dst += 4;
        }
        EltArray tmp;
        EltArray* h = res->Make16(&tmp);
        e->mSrc.Assign(h);
        if (tmp.mRC)
            RefRelease(tmp.mRC);
        e->mFormat = 4;
        break;
    }
    }
}

// @ 0x00733f20  (build the derived index (10) and index (9) streams from a model's source streams.)
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
            EltArray* tmp = (EltArray*)ftmp;
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

            EltArray* h = res->Make4(tmp);
            int f04 = e->mField04;
            int f0c = e->mField0c;
            EltArray localSrc = *h;
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
            EltArray* tmp = (EltArray*)ftmp;
            EltArray* h = res->Make4(tmp);
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
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
