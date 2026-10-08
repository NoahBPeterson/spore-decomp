// Slice s00732410 — mesh skinning-apply helpers: an element-array accessor builder, a bounding
// box accumulator, a 2D basis solver, a 3x4->4x4 matrix builder and several 9-dword element
// copy/fill loops.  0x00732410 itself is a large skinning applier left as a skeleton.
#include "types.h"
#include <math.h>

struct EltArray
{
    int32_t  mNumElts;    // +0x00
    uint8_t* mData;       // +0x04
    uint16_t mEltSize;    // +0x08
    uint16_t mEltStride;  // +0x0a
    void*    mRC;         // +0x0c
};

int  FUN_0071ddc0(int, int, int, int, int);

// Element array view (the 16-byte ref embedded at +0x10 of each 0x20-byte mesh element).
struct EltRef
{
    int32_t  mCount;      // +0x00
    char*    mpData;      // +0x04
    uint16_t mType;       // +0x08
    uint16_t mStride;     // +0x0a
    void*    mpOwner;     // +0x0c
};
struct MeshElt            // 0x20 bytes
{
    int32_t mKey;         // +0x00
    int32_t mPad[3];
    EltRef  mRef;         // +0x10
};
struct MeshElts
{
    char     pad00[8];
    MeshElt* mpBegin;     // +0x08
    MeshElt* mpEnd;       // +0x0c
    int count() const { return (int)(mpEnd - mpBegin); }
};

void __cdecl FUN_0071fce0(const EltRef* src, EltRef* dst, int zero);  // 0x0071fce0

// @ 0x00732410  - accumulate weighted element arrays: dst += w * src for each weighted source
// array (weights either per array, or looked up per vertex through an index array).
void FUN_00732410(MeshElts* A, MeshElts* B, int dstElt, int idxElt, int srcElt, int key,
                  const float* weights, int numWeights)
{
    if (dstElt < 0)
        return;
    EltRef* dst = &B->mpBegin[dstElt].mRef;
    if (srcElt < 0)
        return;
    FUN_0071fce0(&A->mpBegin[dstElt].mRef, dst, 0);
    if (idxElt >= 0)
    {
        if (srcElt >= A->count())
            return;
        int j = 0;
        for (;;)
        {
            MeshElt* src = &A->mpBegin[srcElt + j];
            if (src->mKey != key)
                return;
            MeshElt* idx = &A->mpBegin[idxElt + j];
            int n = dst->mCount;
            for (int i = 0; i < n; ++i)
            {
                int wi = *(int*)(idx->mRef.mpData + idx->mRef.mStride * i);
                if (wi >= 0 && wi < numWeights)
                {
                    float w = weights[wi];
                    const float* s = (const float*)(src->mRef.mpData + src->mRef.mStride * i);
                    float* d = (float*)(dst->mpData + dst->mStride * i);
                    d[0] += w * s[0];
                    d[1] += s[1] * w;
                    d[2] += s[2] * w;
                }
            }
            ++j;
            if (srcElt + j >= A->count())
                return;
        }
    }
    else
    {
        for (int j = 0; j < numWeights; ++j)
        {
            if (srcElt + j >= A->count())
                return;
            MeshElt* src = &A->mpBegin[srcElt + j];
            if (src->mKey != key)
                return;
            float w = weights[j];
            if (w != 0.0f)
            {
                int n = dst->mCount;
                for (int i = 0; i < n; ++i)
                {
                    const float* s = (const float*)(src->mRef.mpData + src->mRef.mStride * i);
                    float* d = (float*)(dst->mpData + dst->mStride * i);
                    d[0] += w * s[0];
                    d[1] += s[1] * w;
                    d[2] += s[2] * w;
                }
            }
        }
    }
}

// @ 0x00732a30
struct RefCnt
{
    virtual void AddRef();
    virtual void Release();
};
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

// @ 0x00732cb0
void FUN_00732cb0(float* param_1, float* param_2, float* param_3, float* param_4, float* param_5,
                  float* param_6, float* param_7)
{
    float fVar4 = *param_3 - *param_1;
    float fVar5 = *param_2 - *param_1;
    float fVar1 = param_3[2] - param_1[2];
    float fVar6 = param_2[1] - param_1[1];
    float fVar8 = param_3[1] - param_1[1];
    float fVar7 = param_2[2] - param_1[2];
    float fVar3 = param_5[1] - param_4[1];
    float fVar2 = param_6[1] - param_4[1];
    float local_24, local_20, local_1c;
    local_1c = fVar2 * (*param_5 - *param_4) - fVar3 * (*param_6 - *param_4);
    if (local_1c <= 1e-06f)
    {
        local_24 = 1.0f;
        local_20 = 0.0f;
        local_1c = 0.0f;
    }
    else
    {
        local_1c = 1.0f / local_1c;
        local_24 = (fVar2 * fVar5 - fVar3 * fVar4) * local_1c;
        local_20 = (fVar2 * fVar6 - fVar3 * fVar8) * local_1c;
        local_1c = (fVar2 * fVar7 - fVar3 * fVar1) * local_1c;
    }
    *param_7 = local_24;
    param_7[1] = local_20;
    param_7[6] = fVar1 * fVar6 - fVar8 * fVar7;
    param_7[2] = local_1c;
    param_7[7] = fVar7 * fVar4 - fVar1 * fVar5;
    param_7[8] = fVar8 * fVar5 - fVar6 * fVar4;
}

// @ 0x00732eb0
void FUN_00732eb0(float* m, float* out)
{
    float tmp[16];
    tmp[0] = m[0];
    tmp[1] = m[4];
    tmp[2] = m[8];
    tmp[3] = 0.0f;
    tmp[4] = m[1];
    tmp[5] = m[5];
    tmp[6] = m[9];
    tmp[7] = 0.0f;
    tmp[8] = m[2];
    tmp[9] = m[6];
    tmp[10] = m[10];
    tmp[11] = 0.0f;
    tmp[12] = 0.0f;
    tmp[13] = 0.0f;
    tmp[14] = 0.0f;
    tmp[15] = 1.0f;
    for (int i = 0; i < 16; ++i)
        out[i] = tmp[i];
    out[0xc] = m[3];
    out[0xd] = m[7];
    out[0xe] = m[0xb];
    out[0xf] = 1.0f;
}

// @ 0x00732fb0
struct ContV
{
    virtual void Init(int);
    char    pad[8];
    int32_t mC;    // +0x0c
    int32_t m10;   // +0x10
    EltArray* Make16(EltArray* out);
    EltArray* Make4(EltArray* out);
};
// @ 0x00732fb0
EltArray* ContV::Make16(EltArray* out)
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

// @ 0x00732ff0
EltArray* ContV::Make4(EltArray* out)
{
    int iVar1 = mC;
    int iVar2 = m10;
    out->mData = (uint8_t*)iVar1;
    out->mNumElts = (iVar2 - iVar1) >> 2;
    out->mEltStride = 4;
    out->mEltSize = 4;
    out->mRC = this;
    Init(0);
    return out;
}

// @ 0x007330d0
int FUN_007330d0(int param_1, int param_2, int* param_3)
{
    int iVar4 = (param_2 - param_1) / 0xc;
    if (iVar4 > 0)
    {
        int iVar3;
        do
        {
            iVar3 = iVar4 >> 1;
            int iVar2 = *(int*)(param_1 + iVar3 * 0xc);
            int iVar1 = param_1 + iVar3 * 0xc;
            if ((iVar2 < *param_3) || (iVar2 <= *param_3 && *(int*)(iVar1 + 4) < param_3[1]))
            {
                param_1 = iVar1 + 0xc;
                iVar3 = iVar4 + (-1 - iVar3);
            }
            iVar4 = iVar3;
        } while (iVar3 > 0);
    }
    return param_1;
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
void FUN_00733230(float* param_1, int param_2, float* param_3)
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
