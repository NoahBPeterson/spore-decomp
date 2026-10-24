// Slice s00734380 — mesh/refcount container helpers: a refcounted element builder, two vector
// insert/assign operations and their wrappers.  The two large functions are left as skeletons.
#include "types.h"
#include <string.h>

struct EltArray
{
    int32_t  mNumElts;
    uint8_t* mData;
    uint16_t mEltSize;
    uint16_t mEltStride;
    void*    mRC;
};

// 0x20-byte descriptor slot: 4 dwords followed by the element range descriptor.
struct SlotObj
{
    int32_t  m0;
    int32_t  m4;
    int32_t  m8;
    int32_t  mC;
    EltArray mElt;      // +0x10
};

// 0x14-byte element of the auxiliary table vector.
struct Elt5 { int32_t m[5]; };

// Local scratch vectors (begin/end/cap) passed by address to eastl helpers.
struct Vec5 { Elt5* mBegin; Elt5* mEnd; Elt5* mCap; };
struct VecI { int*  mBegin; int*  mEnd; int*  mCap; };

struct VObj { void* vt[1]; };
#define VT(p) (((VObj*)(p))->vt)

typedef void      (__thiscall *Fn_vv)(void*);
typedef void      (__thiscall *Fn_vvp)(void*, void*);
typedef void      (__thiscall *Fn_vvpp)(void*, void*, void*);
typedef void*     (__thiscall *Fn_pvi)(void*, int);
typedef void*     (__thiscall *Fn_pviii)(void*, uint32_t, int, int);
typedef EltArray* (__thiscall *Fn_pav)(void*, void*);

// Store an element-range handle back into a slot with the reference swap.
#define WRITE_HANDLE(dst, src) do {                                       \
    (dst)->mNumElts   = (src).mNumElts;                                   \
    (dst)->mData      = (src).mData;                                      \
    (dst)->mEltSize   = (src).mEltSize;                                   \
    (dst)->mEltStride = (src).mEltStride;                                 \
    void* _oldrc = (dst)->mRC; void* _newrc = (src).mRC;                   \
    if (_oldrc != _newrc) {                                               \
        if (_newrc != 0) ((Fn_vv)VT(_newrc)[0])(_newrc);                  \
        (dst)->mRC = _newrc;                                              \
        if (_oldrc != 0) ((Fn_vv)VT(_oldrc)[1])(_oldrc);                  \
    }                                                                     \
} while (0)

// The original resets a scratch range with a zero-length memcpy followed by an end=begin store;
// keep the call (size read from a volatile so it is not folded away).
#define RESET_RANGE(v) do {                                              \
    volatile uint32_t _z0 = 0;                                            \
    memcpy((v).mBegin, (v).mEnd, _z0);                                    \
    (v).mEnd = (v).mBegin;                                                \
} while (0)

// external callees (masked relocations / other slices)
void  FUN_00734380(int, int, float);
int   FUN_0071ddc0(int, int, int, int, int);
void* EAAlloc(int, const char*, int, int, const char*, int);
void  EAFree(void*);
int*  FUN_00733760(int);
EltArray* FUN_00732ff0(void*);
void  FUN_00424f70(void*);
void* FUN_00733310(int, int, int);
void  FUN_00733230(int, int, int, int);
void  FUN_00733140(int*, int, int, int, int);
void* FUN_00758630(uint32_t, int, int);
void* FUN_007b0920(uint32_t, int, int);
void  FUN_00b007f0(int, int);
void* FUN_007b0040(void*, int, int, int, int);
void  FUN_00b85090(int, int, int);
void  FUN_00b7f6a0(int, int, void*);
void* FUN_006782c0(void*, void*, void*);
void  FUN_00733920(void*, void*);
struct Vec3Vec { int m[5];
    int Emplace(int param_2, int* param_3);
    Vec3Vec* AssignInts(Vec3Vec* param_2);
    Vec3Vec* AssignRefs(Vec3Vec* param_2); };
void  FUN_00733a50(void*);
void  FUN_00733f20(void*);
// callees of the two container routines
int   FUN_0071dd80(int, int);
void  FUN_00720070(void*);
void  FUN_0071fd60(void*, int, int, void*, void*);
void  FUN_00428900(void*, void*, void*);
void  FUN_00715120(void*, void*);
void  FUN_0071ec20(int, int*, int, int, int);
void  FUN_007201d0(void*, void*);
void  FUN_006b9510(uint8_t*, int, int, int);
void  FUN_006ba2f0(uint8_t*, int, int, int);
void  FUN_006b9dc0(uint8_t*, int, int, int);
void  FUN_00733e90(int, int, void*);
void  FUN_0041cb40(void*, void*);

// 0x24-byte element vector used by the insert helper below.
struct Mat33 { int32_t m[9]; };
struct Mat33Vec { int32_t m[3];
    void FUN_007346d0(int pos, uint32_t n, int value); };

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

    EltArray* ea = ((Fn_pav)FUN_00732ff0)(obj, f3);

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

// @ 0x007346d0
void Mat33Vec::FUN_007346d0(int pos, uint32_t n, int value)
{
    int* v = m;
    uint32_t cap = (uint32_t)((v[2] - v[1]) / 0x24);
    if (n <= cap)
    {
        if (n == 0) return;

        Mat33 local;
        ((Fn_vvp)FUN_0041cb40)(&local, (void*)value);
        int end = v[1];
        uint32_t tail = (uint32_t)(v[1] - pos) / 0x24;
        if (n < tail)
        {
            int src = end - (int)n * 0x24;
            FUN_00733140(&value, src, end, end, pos);
            v[1] = v[1] + (int)n * 0x24;
            FUN_00b85090(pos, src, end);
            FUN_00b7f6a0(pos, pos + (int)n * 0x24, &local);
            return;
        }
        FUN_00733230(end, (int)(n - tail), (int)&local, pos);
        v[1] = v[1] + (int)(n - tail) * 0x24;
        FUN_00733140(&pos, pos, end, v[1], pos);
        v[1] = v[1] + (int)tail * 0x24;
        FUN_00b7f6a0(pos, end, &local);
        return;
    }

    int size = (v[1] - v[0]) / 0x24;
    uint32_t cap2 = (uint32_t)size * 2;
    if (size == 0) cap2 = 1;
    uint32_t newcap = (uint32_t)size + n;
    if (newcap < cap2) newcap = cap2;
    int nbuf = 0;
    if (newcap != 0)
        nbuf = (int)EAAlloc((int)(newcap * 0x24), "Graphics", 0, 0,
                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                            0xd1);
    int iVar3 = (int)FUN_00733310(v[0], pos, nbuf);
    FUN_00733230(iVar3, (int)n, value, pos);
    int end2 = (int)FUN_00733310(value, v[1], iVar3 + (int)n * 0x24);
    int old = v[0];
    if (old != 0 && *(int*)(old - 4) != 0) EAFree((void*)old);
    v[0] = nbuf;
    v[1] = end2;
    v[2] = nbuf + (int)newcap * 0x24;
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

// @ 0x00734970
void FUN_00734970(int param_1)
{
    int local_58 = FUN_0071dd80(param_1, 8);
    if (local_58 == 0)
    {
        int iVar2 = (*(int*)(param_1 + 0x34) - *(int*)(param_1 + 0x30)) / 0x14;
        local_58 = 0;
        if (iVar2 > 0)
        {
            int* p = (int*)(*(int*)(param_1 + 0x30) + 0x10);
            do {
                if (local_58 < *p) local_58 = *p;
                p += 5;
                iVar2--;
            } while (iVar2 != 0);
        }
        local_58++;
    }

    Vec5 vec;
    vec.mBegin = 0; vec.mEnd = 0; vec.mCap = 0;
    Elt5* vEnd = vec.mEnd;
    int local_48 = (*(int*)(param_1 + 0x20) - *(int*)(param_1 + 0x1c)) / 0x8c;
    int local_60 = 0;
    if (local_48 > 0)
    {
        int local_50 = 0;
        do {
            EltArray* rec = (EltArray*)(*(int*)(param_1 + 0x1c) + local_50);
            EltArray h;
            h.mNumElts   = rec->mNumElts;
            h.mData      = rec->mData;
            h.mEltSize   = rec->mEltSize;
            h.mEltStride = rec->mEltStride;
            h.mRC        = rec->mRC;
            if (h.mRC != 0) ((Fn_vv)VT(h.mRC)[0])(h.mRC);
            FUN_00720070(&h);

            int iStack_64 = 0;
            int iStack_30 = local_60;
            int iStack_68 = 0;
            do {
                bool bVar1 = (iStack_68 == 1 || iStack_68 == 2 || iStack_68 == 4 || iStack_68 == 7);
                int iStack_5c = 0;
                if (local_58 > 0)
                {
                    do {
                        int iVar2 = (*(int*)(param_1 + 0x34) - *(int*)(param_1 + 0x30)) / 0x14;
                        int iVar9 = iStack_64;
                        int iVar6 = iStack_5c;
                        if (iVar2 > 0)
                        {
                            int iVar5 = 0;
                            int iStack_4c = iVar2;
                            do {
                                int* piVar3 = (int*)(*(int*)(param_1 + 0x30) + iVar5);
                                if (piVar3[1] == local_60 && *piVar3 == iStack_68 &&
                                    piVar3[4] == iStack_5c)
                                {
                                    FUN_0071fd60(rec, piVar3[2], piVar3[3], &h, &iStack_64);
                                    if (!bVar1 && iVar9 < iStack_64)
                                    {
                                        int val[5];
                                        val[0] = iStack_68; val[1] = iStack_30;
                                        val[2] = iVar9;     val[3] = iStack_64;
                                        val[4] = iVar6;
                                        if (vEnd < vec.mCap)
                                        {
                                            Elt5* slot = vEnd;
                                            vec.mEnd = vEnd + 1;
                                            vEnd = vec.mEnd;
                                            if (slot != 0) memcpy(slot, val, 0x14);
                                        }
                                        else
                                        {
                                            ((Fn_vvpp)FUN_00428900)(&vec, vEnd, val);
                                            iVar6 = val[4]; iVar9 = val[2];
                                            vEnd = vec.mEnd;
                                        }
                                    }
                                }
                                iVar5 += 0x14;
                                iStack_4c--;
                            } while (iStack_4c != 0);
                        }
                        if (bVar1 && iVar9 < iStack_64)
                        {
                            int val[5];
                            val[0] = iStack_68; val[1] = iStack_30;
                            val[2] = iVar9;     val[3] = iStack_64;
                            val[4] = iVar6;
                            if (vEnd < vec.mCap)
                            {
                                Elt5* slot = vEnd;
                                vec.mEnd = vEnd + 1;
                                vEnd = vec.mEnd;
                                if (slot != 0) memcpy(slot, val, 0x14);
                            }
                            else
                            {
                                ((Fn_vvpp)FUN_00428900)(&vec, vEnd, val);
                                vEnd = vec.mEnd;
                            }
                        }
                        iStack_5c++;
                    } while (iStack_5c < local_58);
                }
                iStack_68++;
            } while (iStack_68 < 10);

            WRITE_HANDLE(rec, h);
            if (h.mRC != 0) ((Fn_vv)VT(h.mRC)[1])(h.mRC);

            local_50 += 0x8c;
            local_60++;
        } while (local_60 < local_48);
    }

    Elt5* oldBegin = vec.mBegin;
    ((Fn_vvp)FUN_00715120)((void*)(param_1 + 0x30), &vec);
    if (oldBegin != 0 && *(int*)((uint8_t*)oldBegin - 4) != 0) EAFree((void*)oldBegin);
}

// @ 0x00734d00
void FUN_00734d00(uint8_t* param_1, int param_2)
{
    if (!(*(float*)(param_1 + 0x10) != 1.0f || (*param_1 & 6) != 0))
        return;

    VecI vec;
    vec.mBegin = 0; vec.mEnd = 0; vec.mCap = 0;
    FUN_0071ec20(param_2, (int*)&vec, 1, 3, 0xe);
    FUN_0071ec20(param_2, (int*)&vec, 1, 4, 0xe);

    int iVar6 = (int)(vec.mEnd - vec.mBegin);
    int local_3c = 0;
    if (iVar6 > 0)
    {
        do {
            EltArray local;
            local.mNumElts = 0; local.mData = 0;
            local.mEltSize = 0xc; local.mEltStride = 0xc; local.mRC = 0;
            EltArray* elt = (EltArray*)(vec.mBegin[local_3c] * 0x20 + 0x10 + *(int*)(param_2 + 8));
            FUN_007201d0(elt, &local);
            FUN_006b9510(param_1, local.mNumElts, (int)local.mData, local.mEltStride);
            WRITE_HANDLE(elt, local);
            if (local.mRC != 0) ((Fn_vv)VT(local.mRC)[1])(local.mRC);
            local_3c++;
        } while (local_3c < iVar6);
    }

    if (((*param_1 >> 1) & 1) != 0)
    {
        RESET_RANGE(vec);
        FUN_0071ec20(param_2, (int*)&vec, 2, 7, 0xe);
        FUN_0071ec20(param_2, (int*)&vec, 3, 7, 0xe);
        if (vec.mBegin != vec.mEnd)
        {
            FUN_00733e90(param_2, (int)(vec.mEnd - vec.mBegin), vec.mBegin);
            RESET_RANGE(vec);
        }
        FUN_0071ec20(param_2, (int*)&vec, 2, 3, 0xe);
        FUN_0071ec20(param_2, (int*)&vec, 3, 3, 0xe);
        iVar6 = (int)(vec.mEnd - vec.mBegin);
        local_3c = 0;
        if (iVar6 > 0)
        {
            do {
                EltArray local;
                local.mNumElts = 0; local.mData = 0;
                local.mEltSize = 0xc; local.mEltStride = 0xc; local.mRC = 0;
                EltArray* elt = (EltArray*)(vec.mBegin[local_3c] * 0x20 + 0x10 + *(int*)(param_2 + 8));
                FUN_007201d0(elt, &local);
                FUN_006ba2f0(param_1, local.mNumElts, (int)local.mData, local.mEltStride);
                WRITE_HANDLE(elt, local);
                if (local.mRC != 0) ((Fn_vv)VT(local.mRC)[1])(local.mRC);
                local_3c++;
            } while (local_3c < iVar6);
        }
    }

    if ((((*param_1 >> 1) & 1) != 0) || *(float*)(param_1 + 0x10) != 1.0f)
    {
        RESET_RANGE(vec);
        FUN_0071ec20(param_2, (int*)&vec, 0xd, 7, 0xe);
        if (vec.mBegin != vec.mEnd)
        {
            int n = (int)(vec.mEnd - vec.mBegin);
            for (int i = 0; i < n; i++)
                FUN_00733a50((void*)(vec.mBegin[i] * 0x20 + *(int*)(param_2 + 8)));
            RESET_RANGE(vec);
        }
        FUN_0071ec20(param_2, (int*)&vec, 0xc, 3, 0xe);
        FUN_0071ec20(param_2, (int*)&vec, 0xd, 3, 0xe);
        iVar6 = (int)(vec.mEnd - vec.mBegin);
        local_3c = 0;
        if (iVar6 > 0)
        {
            do {
                EltArray local;
                local.mNumElts = 0; local.mData = 0;
                local.mEltSize = 0xc; local.mEltStride = 0xc; local.mRC = 0;
                EltArray* elt = (EltArray*)(vec.mBegin[local_3c] * 0x20 + 0x10 + *(int*)(param_2 + 8));
                FUN_007201d0(elt, &local);
                FUN_006b9dc0(param_1, local.mNumElts, (int)local.mData, local.mEltStride);
                WRITE_HANDLE(elt, local);
                if (local.mRC != 0) ((Fn_vv)VT(local.mRC)[1])(local.mRC);
                local_3c++;
            } while (local_3c < iVar6);
        }
    }

    if (vec.mBegin != 0 && *(int*)((uint8_t*)vec.mBegin - 4) != 0)
        EAFree((void*)vec.mBegin);
}

// @ 0x00735260
Vec3Vec* Vec3Vec::AssignRefs(Vec3Vec* p2)
{
    int* param_1 = (int*)this; int* param_2 = (int*)p2;
    if (param_2 != param_1)
    {
        int iVar1 = *param_2;
        int iVar4 = *param_1;
        int iVar2 = param_2[1];
        uint32_t uVar7 = (uint32_t)(iVar2 - iVar1) >> 2;
        if ((uint32_t)(param_1[2] - iVar4) >> 2 < uVar7)
        {
            int nv = (int)((Fn_pviii)FUN_007b0920)((void*)param_1, uVar7, iVar1, iVar2);
            ((Fn_vvpp)FUN_00b007f0)((void*)param_1, (void*)param_1[0], (void*)param_1[1]);
            int t = *param_1;
            if (t != 0 && *(int*)(t - 4) != 0)
                EAFree((void*)t);
            param_1[2] = nv + uVar7 * 4;
            param_1[1] = nv + uVar7 * 4;
            *param_1 = nv;
            return (Vec3Vec*)param_1;
        }
        uint32_t uVar6 = (uint32_t)(param_1[1] - iVar4) >> 2;
        if (uVar6 < uVar7)
        {
            FUN_006782c0((void*)iVar1, (void*)(iVar1 + uVar6 * 4), (void*)iVar4);
            FUN_007b0040(&param_2, *param_2 + ((param_1[1] - *param_1) >> 2) * 4, param_2[1],
                         param_1[1], (int)param_2);
            param_1[1] = *param_1 + uVar7 * 4;
            return (Vec3Vec*)param_1;
        }
        int p = (int)FUN_006782c0((void*)iVar1, (void*)iVar2, (void*)iVar4);
        ((Fn_vvpp)FUN_00b007f0)((void*)param_1, (void*)p, (void*)param_1[1]);
        param_1[1] = *param_1 + uVar7 * 4;
    }
    return (Vec3Vec*)param_1;
}
