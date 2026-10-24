// Slice s0110a0d0 -- Havok 3.1.0 hkBoxBoxCollisionDetection manifold/validation helpers.
//
// Six box-box contact-manifold builders:
//   * three per-feature-index "validation data" builders that fill a
//     hkFeaturePointCache from the detection's per-face rows,
//   * the 956-byte box-box point/normal solver (FUN_0110a600),
//   * addAdditionalEdgeHelper (FUN_0110a9c0), which validates and appends one
//     feature pair to an hkBoxBoxManifold,
//   * FUN_0110ac90, the 4-way dispatcher that packs the sign pair and calls
//     addAdditionalEdgeHelper four times with the XOR'd feature word.
#include "types.h"
#include <math.h>
#include <float.h>

// ---------------------------------------------------------------------------
// Constants.
// ---------------------------------------------------------------------------
// kSignTable @ 0x014a5ef0: 8 face-normal sign patterns, 4 floats (x,y,z,w).
static const float kSignTable[8][4] =
{
    {  1.0f,  1.0f,  1.0f, 0.0f },   // 0
    {  1.0f,  1.0f, -1.0f, 0.0f },   // 1
    {  1.0f, -1.0f,  1.0f, 0.0f },   // 2
    {  1.0f, -1.0f, -1.0f, 0.0f },   // 3
    { -1.0f,  1.0f,  1.0f, 0.0f },   // 4
    { -1.0f,  1.0f, -1.0f, 0.0f },   // 5
    { -1.0f, -1.0f,  1.0f, 0.0f },   // 6
    { -1.0f, -1.0f, -1.0f, 0.0f },   // 7
};

static inline float xorSign(float value, float fromSign)
{
    // retail: (uint)value ^ ((uint)expr & 0x80000000)
    union { float f; unsigned u; } a, b;
    a.f = value;
    b.f = fromSign;
    a.u ^= (b.u & 0x80000000u);
    return a.f;
}

// ---------------------------------------------------------------------------
// Structs (role + offset names; Havok retail types not recoverable).
// ---------------------------------------------------------------------------
struct hkFeatureContactPoint          // 4-byte box-box feature pair
{
    unsigned char  mA;       // 0x00
    unsigned char  mB;       // 0x01
    unsigned short mIndex;   // 0x02
};

struct hkFeaturePointCache           // 0x40 bytes, per-feature validation scratch
{
    float mPoint[4];     // 0x00
    float mDir[4];       // 0x10
    float mTan[4];       // 0x20
    float mScale;        // 0x30
    float mDist;         // 0x34
    float mIndexA;       // 0x38
    float mIndexB;       // 0x3c
};

struct hkProcessCdPoint              // 0x30-byte manifold point slot
{
    float          mX;          // 0x00
    float          mY;          // 0x04
    float          mZ;          // 0x08
    uint32_t       pad0c[1];    // 0x0c
    float          mNX;         // 0x10
    float          mNY;         // 0x14
    float          mNZ;         // 0x18
    uint32_t       pad1c[1];    // 0x1c
    unsigned short mIndex;      // 0x20
    uint32_t       pad22[3];    // 0x22
    unsigned short pad2e;       // 0x2e
};

struct hkPointRing                   // per-detection point ring with cursor
{
    hkProcessCdPoint* mCursor;      // 0x00
    uint32_t          pad04[11];    // 0x04 .. 0x2f
    hkProcessCdPoint  mPoints[1];   // 0x30
};

struct hkBoxBoxManifoldEntry
{
    unsigned char  mA;       // 0x00
    unsigned char  mB;       // 0x01
    unsigned short mIndex;   // 0x02
};

struct hkBoxBoxManifold
{
    hkBoxBoxManifoldEntry mEntries[8];   // 0x00
    unsigned char         mCount20;      // 0x20
    unsigned char         mCount21;      // 0x21

    void removePoint(int index);         // @ 0x010ec4a0
};

// Direct thiscall callees (named by target hex so difftest can resolve them).
struct TC_contactPoint
{
    void FUN_01108a10(hkProcessCdPoint&, const hkFeatureContactPoint&, const hkFeaturePointCache&);  // faceAVertexB
    void FUN_01108b80(hkProcessCdPoint&, const hkFeatureContactPoint&, const hkFeaturePointCache&);  // faceBVertexA
    void FUN_01108c30(hkProcessCdPoint&, const hkFeatureContactPoint&, const hkFeaturePointCache&);  // edgeEdge
};

struct TC_manifold
{
    int FUN_010ec540(void* a, void* b, void* c);   // hkBoxBoxManifold::addPoint
};

void FUN_01108750(void* out, void* a, void* b);    // hkBoxBoxUtils::hkPackSigns2

struct hkBoxBoxCollisionDetection
{
    void*        m00;         // 0x00
    void*        m04;         // 0x04
    void*        m08;         // 0x08
    void*        mVtObj;      // 0x0c  object whose vtable slot 2 is queried
    hkPointRing* mRing;       // 0x10  manifold point ring
    float*       mMatA;       // 0x14
    float*       mMatB;       // 0x18
    uint32_t     pad1c[1];    // 0x1c
    float        mRow[6][4];  // 0x20 .. 0x7f
    uint32_t     pad80[12];   // 0x80 .. 0xaf
    float        mB0;         // 0xb0
    float        mB4;         // 0xb4
    uint32_t     padB8[2];    // 0xb8
    float        mC[4];       // 0xc0
    float        mD[4];       // 0xd0

    void  faceAVertexBValidationDataFromFeatureIndex(hkFeaturePointCache& c, float featureIndex) const;  // 0x0110a0d0
    void  faceBVertexAValidationDataFromFeatureIndex(hkFeaturePointCache& c, int featureIndex) const;    // 0x0110a2b0
    void  edgeEdgeValidationDataFromFeatureIndex(hkFeaturePointCache& c) const;                           // 0x0110a4b0
    void  addAdditionalEdgeHelper(hkBoxBoxManifold& m, hkFeatureContactPoint& p, float f) const;          // 0x0110a9c0
    char* FUN_0110a600(char* outFlag, hkFeaturePointCache& cache) const;                                  // 0x0110a600
    void  FUN_0110ac90(hkBoxBoxManifold& m, void* a2, void* a3, int p4, int p5, void* a6, void* a7, float f); // 0x0110ac90
};

// @ 0x0110a0d0  hkBoxBoxCollisionDetection::faceAVertexBValidationDataFromFeatureIndex
void hkBoxBoxCollisionDetection::faceAVertexBValidationDataFromFeatureIndex(hkFeaturePointCache& c, float featureIndex) const
{
    int fi = (int)featureIndex;

    c.mIndexA = featureIndex;
    float fVar1 = mRow[0][fi];
    float fVar2 = mRow[1][fi];
    float fVar3 = mRow[2][fi];

    if (0.0f <= mC[fi])
    {
        c.mScale = 1.0f;
        c.mDir[0] = -mRow[5][0];
        c.mDir[1] = -mRow[5][1];
        c.mDir[2] = -mRow[5][2];
        c.mDir[3] = -mRow[5][3];
    }
    else
    {
        c.mScale = -1.0f;
        c.mDir[0] = mRow[5][0];
        c.mDir[1] = mRow[5][1];
        c.mDir[2] = mRow[5][2];
        c.mDir[3] = mRow[5][3];
    }

    float local_20 = -1e-05f;
    float local_1c = -1e-05f;
    if (0.0f < mD[0])
        local_20 = 1e-05f;
    if (0.0f < mD[1])
        local_1c = 1e-05f;
    float fVar5 = -1e-05f;
    if (0.0f < mD[2])
        fVar5 = 1e-05f;

    float fVar4 = c.mScale;
    c.mDir[0] = xorSign(c.mDir[0], local_20 * fVar4 + fVar1);
    c.mDir[1] = xorSign(c.mDir[1], local_1c * fVar4 + fVar2);
    c.mDir[2] = xorSign(c.mDir[2], fVar5 * fVar4 + fVar3);
    c.mDir[3] = xorSign(c.mDir[3], fVar4 * -1e-05f);

    fVar1 = c.mDir[0];
    fVar2 = c.mDir[1];
    fVar3 = c.mDir[2];
    c.mPoint[0] = (fVar1 * mRow[0][0] + (fVar2 * mRow[1][0] + fVar3 * mRow[2][0])) + mRow[3][0];
    c.mPoint[1] = (fVar1 * mRow[0][1] + (fVar2 * mRow[1][1] + fVar3 * mRow[2][1])) + mRow[3][1];
    c.mPoint[2] = (fVar1 * mRow[0][2] + (fVar2 * mRow[1][2] + fVar3 * mRow[2][2])) + mRow[3][2];
    c.mPoint[3] = 0.0f;
}

// @ 0x0110a2b0  hkBoxBoxCollisionDetection::faceBVertexAValidationDataFromFeatureIndex
void hkBoxBoxCollisionDetection::faceBVertexAValidationDataFromFeatureIndex(hkFeaturePointCache& c, int featureIndex) const
{
    c.mIndexA = (float)(featureIndex + 4);

    const float* pf = &mRow[featureIndex + 2][0];
    float fVar1 = pf[0];
    float fVar2 = pf[1];
    float fVar3 = pf[2];
    float fVar4 = pf[3];

    if (0.0f <= mD[featureIndex])
    {
        c.mScale = 1.0f;
        c.mPoint[0] = mRow[4][0];
        c.mPoint[1] = mRow[4][1];
        c.mPoint[2] = mRow[4][2];
        c.mPoint[3] = mRow[4][3];
    }
    else
    {
        c.mScale = -1.0f;
        c.mPoint[0] = -mRow[4][0];
        c.mPoint[1] = -mRow[4][1];
        c.mPoint[2] = -mRow[4][2];
        c.mPoint[3] = -mRow[4][3];
    }

    float local_20 = 1e-05f;
    float local_1c = 1e-05f;
    if (0.0f < mC[0])
        local_20 = -1e-05f;
    if (0.0f < mC[1])
        local_1c = -1e-05f;
    float fVar5 = 1e-05f;
    if (0.0f < mC[2])
        fVar5 = -1e-05f;

    float fVar6 = -c.mScale;
    c.mPoint[0] = xorSign(c.mPoint[0], fVar1 + local_20 * fVar6);
    c.mPoint[1] = xorSign(c.mPoint[1], fVar2 + local_1c * fVar6);
    c.mPoint[2] = xorSign(c.mPoint[2], fVar3 + fVar5 * fVar6);
    c.mPoint[3] = xorSign(c.mPoint[3], fVar4 + fVar6 * 1e-05f);

    fVar1 = c.mPoint[0] - mRow[3][0];
    fVar3 = c.mPoint[1] - mRow[3][1];
    fVar2 = c.mPoint[2] - mRow[3][2];
    c.mDir[0] = fVar1 * mRow[0][0] + (fVar3 * mRow[0][1] + fVar2 * mRow[0][2]);
    c.mDir[1] = fVar1 * mRow[1][0] + (fVar3 * mRow[1][1] + fVar2 * mRow[1][2]);
    c.mDir[2] = fVar1 * mRow[2][0] + (fVar3 * mRow[2][1] + fVar2 * mRow[2][2]);
    c.mDir[3] = 0.0f;
}

// @ 0x0110a4b0  hkBoxBoxCollisionDetection::edgeEdgeValidationDataFromFeatureIndex
void hkBoxBoxCollisionDetection::edgeEdgeValidationDataFromFeatureIndex(hkFeaturePointCache& c) const
{
    const float* pf = &mRow[(int)c.mIndexB + 2][0];

    float local_20[3];
    local_20[2] = 0.0f;
    local_20[1] = 0.0f;
    local_20[0] = 0.0f;
    local_20[(int)c.mIndexA] = 1.0f;

    float fVar10 = pf[2] * local_20[1] - pf[1] * local_20[2];
    float fVar11 = pf[0] * local_20[2] - pf[2] * local_20[0];
    local_20[2] = pf[1] * local_20[0] - pf[0] * local_20[1];

    if (fVar10 * mC[0] + (fVar11 * mC[1] + local_20[2] * mC[2]) < 0.0f)
    {
        fVar10 = -fVar10;
        fVar11 = -fVar11;
        local_20[2] = -local_20[2];
    }

    c.mPoint[2] = local_20[2];
    c.mPoint[3] = 0.0f;
    c.mPoint[0] = fVar10;
    c.mPoint[1] = fVar11;
    c.mDir[0] = fVar10 * mRow[0][0] + (fVar11 * mRow[0][1] + local_20[2] * mRow[0][2]);
    c.mDir[1] = fVar10 * mRow[1][0] + (fVar11 * mRow[1][1] + local_20[2] * mRow[1][2]);
    c.mDir[2] = fVar10 * mRow[2][0] + (fVar11 * mRow[2][1] + local_20[2] * mRow[2][2]);
    c.mDir[3] = 0.0f;
}

// @ 0x0110a600  hkBoxBoxCollisionDetection::FUN_0110a600  (box-box point/normal solver)
char* hkBoxBoxCollisionDetection::FUN_0110a600(char* outFlag, hkFeaturePointCache& cache) const
{
    unsigned uVar12 = ((unsigned)cache.mIndexB) & 0xf;
    unsigned uVar10 = ((unsigned)cache.mIndexA) & 0xf;
    unsigned uVar11 = (((unsigned char)cache.mIndexA) >> 1) & 0x70;
    unsigned uVar8  = (((unsigned char)cache.mIndexB) >> 1) & 0x70;

    const float* tA = kSignTable[uVar11 >> 4];
    const float* tB = kSignTable[uVar8 >> 4];

    float local_40[4];
    float local_50[4];
    float local_30[4];
    float local_20[7];

    local_40[0] = tA[0] * mRow[4][0];
    local_40[1] = mRow[4][1] * tA[1];
    local_40[2] = mRow[4][2] * tA[2];
    local_40[3] = mRow[4][3] * tA[3];

    float fVar2 = mRow[5][0] * tB[0];
    float fVar3 = mRow[5][1] * tB[1];
    local_20[2] = mRow[5][2] * tB[2];

    const float* pfVar9 = &mRow[uVar12 + 2][0];
    float fVar1 = mRow[5][uVar12];
    fVar1 = fVar1 + fVar1;
    local_50[0] = fVar1 * pfVar9[0];
    local_50[1] = fVar1 * pfVar9[1];
    local_50[2] = fVar1 * pfVar9[2];
    local_50[3] = fVar1 * pfVar9[3];

    local_20[0] = (fVar2 * mRow[0][0] + (fVar3 * mRow[1][0] + local_20[2] * mRow[2][0])) + mRow[3][0];
    local_30[0] = local_20[0] - local_40[0];
    local_30[1] = ((fVar2 * mRow[0][1] + (fVar3 * mRow[1][1] + local_20[2] * mRow[2][1])) + mRow[3][1]) - local_40[1];
    local_30[2] = ((fVar2 * mRow[0][2] + (fVar3 * mRow[1][2] + local_20[2] * mRow[2][2])) + mRow[3][2]) - local_40[2];
    local_30[3] = -local_40[3];

    fVar2 = mRow[4][uVar10] * -2.0f;
    fVar3 = fVar2 * local_50[uVar10];
    fVar1 = mRow[5][uVar12];
    fVar1 = (fVar1 * fVar1) * 4.0f;
    float fVar4 = local_30[0] * local_50[0] + (local_30[1] * local_50[1] + local_30[2] * local_50[2]);
    float fVar5 = (float)fabsf((fVar2 * fVar2) * fVar1 - fVar3 * fVar3);
    float fVar6 = (fVar2 * local_30[uVar10]) * fVar1 - fVar4 * fVar3;

    if (FLT_EPSILON * fVar5 < fVar6 &&
        !((1.0f - FLT_EPSILON) * fVar5 < fVar6))
    {
        float fVar7 = (1.0f - FLT_EPSILON) * fVar5;
        (void)fVar7;
        fVar4 = (fVar6 / fVar5) * fVar3 - fVar4;
        if (!(fVar4 < FLT_EPSILON * fVar1) && (fVar4 < (1.0f - FLT_EPSILON) * fVar1))
        {
            local_20[2] = 0.0f;
            local_20[1] = 0.0f;
            local_20[0] = 0.0f;
            local_40[uVar10] = (fVar6 / fVar5) * fVar2 + local_40[uVar10];
            local_20[uVar10] = fVar2 * 0.5f;

            fVar1 = local_20[1] * local_50[2] - local_20[2] * local_50[1];
            fVar3 = local_20[2] * local_50[0] - local_50[2] * local_20[0];
            local_50[2] = local_50[1] * local_20[0] - local_20[1] * local_50[0];
            fVar2 = (float)sqrtf(fVar1 * fVar1 + (fVar3 * fVar3 + local_50[2] * local_50[2]));
            local_50[3] = 1.0f / fVar2;
            local_50[0] = fVar1 * local_50[3];
            local_50[1] = fVar3 * local_50[3];
            local_50[2] = local_50[2] * local_50[3];
            local_50[3] = local_50[3] * 0.0f;

            if (mB4 <= fVar2)
            {
                if (local_50[0] * tA[0] + (local_50[2] * tA[2] + local_50[1] * tA[1]) < 0.0f)
                {
                    local_50[0] = -local_50[0];
                    local_50[1] = -local_50[1];
                    local_50[2] = -local_50[2];
                    local_50[3] = -local_50[3];
                }
                fVar1 = local_50[0] * local_30[0] + (local_50[1] * local_30[1] + local_50[2] * local_30[2]);
                if (fVar1 <= mB0)
                {
                    cache.mPoint[0] = local_40[0];
                    cache.mPoint[3] = local_40[3];
                    cache.mPoint[1] = local_40[1];
                    cache.mPoint[2] = local_40[2];
                    cache.mTan[0] = -local_50[0];
                    cache.mTan[1] = -local_50[1];
                    cache.mTan[2] = -local_50[2];
                    cache.mTan[3] = -local_50[3];
                    cache.mDist = fVar1;
                    *outFlag = 1;
                    return outFlag;
                }
            }
        }
    }

    *outFlag = 0;
    return outFlag;
}

// @ 0x0110a9c0  hkBoxBoxCollisionDetection::addAdditionalEdgeHelper
void hkBoxBoxCollisionDetection::addAdditionalEdgeHelper(hkBoxBoxManifold& manifold, hkFeatureContactPoint& feat, float f) const
{
    int iVar8 = (int)manifold.mCount21 - 1;
    if (iVar8 >= 0)
    {
        do
        {
            if (manifold.mEntries[iVar8].mA == feat.mA &&
                manifold.mEntries[iVar8].mB == feat.mB)
                return;
            iVar8 = iVar8 - 1;
        } while (iVar8 >= 0);
    }

    unsigned local_18 = (unsigned)feat.mA;
    unsigned local_14 = (unsigned)feat.mB;
    (void)local_18;
    (void)local_14;

    char flag;
    hkFeaturePointCache cache;
    FUN_0110a600(&flag, cache);
    if (flag == 0)
        return;

    if (!(f * 0.999f < cache.mDist))
        return;

    float fVar2;
    float fVar6;
    float fVar3;
    float d0;
    float d1;
    float d2;

    if (feat.mA < 7)
    {
        if (feat.mA < 3)
        {
            const float* pfVar10 = mMatB;
            d0 = cache.mDir[0];
            d1 = cache.mDir[1];
            d2 = cache.mDir[2];
            fVar2 = (d0 * pfVar10[0] + (d1 * pfVar10[4] + d2 * pfVar10[8])) + pfVar10[0xc];
            fVar6 = (d0 * pfVar10[1] + (d1 * pfVar10[5] + d2 * pfVar10[9])) + pfVar10[0xd];
            fVar3 = d1 * pfVar10[6] + d2 * pfVar10[10];
        }
        else
        {
            const float* pfVar10 = mMatA;
            d0 = cache.mPoint[0];
            d1 = cache.mPoint[1];
            d2 = cache.mPoint[2];
            fVar2 = (d0 * pfVar10[0] + (d1 * pfVar10[4] + d2 * pfVar10[8])) + pfVar10[0xc];
            fVar6 = (d0 * pfVar10[1] + (d1 * pfVar10[5] + d2 * pfVar10[9])) + pfVar10[0xd];
            fVar3 = d1 * pfVar10[6] + d2 * pfVar10[10];
        }

        float local_58 = (d0 * mMatA[2] + fVar3) + mMatA[0xe];
        (void)local_58;

        if (manifold.mCount21 != 0)
        {
            int i = 0;
            do
            {
                if (manifold.mEntries[i].mA < 7)
                {
                    float dx = fVar2 - mRing->mPoints[i].mX;
                    float dy = fVar6 - mRing->mPoints[i].mY;
                    float dz = local_58 - mRing->mPoints[i].mZ;
                    if (dx * dx + (dy * dy + dz * dz) <= mB0 * mB0 + FLT_EPSILON)
                        return;
                }
                i = i + 1;
            } while (i < (int)manifold.mCount21);
        }
    }

    if (manifold.mCount21 >= 8)
        return;

    int idx = ((TC_manifold*)&manifold)->FUN_010ec540(m00, m04, &cache);
    if (idx < 0)
        return;

    hkProcessCdPoint* cur = mRing->mCursor;

    if (feat.mA <= 2)
        ((TC_contactPoint*)this)->FUN_01108a10(*cur, feat, cache);
    else if (feat.mA <= 6)
        ((TC_contactPoint*)this)->FUN_01108b80(*cur, feat, cache);
    else
        ((TC_contactPoint*)this)->FUN_01108c30(*cur, feat, cache);

    if (manifold.mCount21 > 1)
    {
        hkProcessCdPoint* prev = mRing->mCursor - 1;
        float dot = prev->mNX * cur->mNX + (prev->mNY * cur->mNY + prev->mNZ * cur->mNZ);
        if (dot <= 0.0f)
        {
            manifold.removePoint(idx);
            return;
        }
    }

    {
        typedef short (__thiscall *VtSlot2)(void*, void*, void*, void*, void*);
        void** vtbl = *(void***)mVtObj;
        short result = ((VtSlot2)vtbl[2])(mVtObj, m00, m04, m08, cur);
        manifold.mEntries[idx].mIndex = (unsigned short)result;
        if (result == -1)
        {
            manifold.removePoint(idx);
            return;
        }

        mRing->mCursor = mRing->mCursor + 1;
        feat.mIndex = manifold.mEntries[idx].mIndex;
        cur->mIndex = manifold.mEntries[idx].mIndex;

        if (feat.mA > 6)
            return;
        manifold.mCount20 = (unsigned char)(manifold.mCount20 + 1);
    }
}

// @ 0x0110ac90  hkBoxBoxCollisionDetection::FUN_0110ac90  (4-way edge dispatcher)
void hkBoxBoxCollisionDetection::FUN_0110ac90(hkBoxBoxManifold& manifold, void* a2, void* a3, int p4, int p5, void* a6, void* a7, float f)
{
    hkFeatureContactPoint feat;
    feat.mA = 0;
    feat.mB = 0;
    feat.mIndex = 0;

    FUN_01108750(&feat, a2, a3);
    (void)a6;
    (void)a7;

    addAdditionalEdgeHelper(manifold, feat, f);

    int cVar1;
    if (p4 == 0)
        cVar1 = 3;
    else
        cVar1 = (p4 == 1) + 1;

    unsigned char bVar4 = (unsigned char)(1u << (cVar1 + 4));
    feat.mA = (unsigned char)(feat.mA ^ bVar4);
    addAdditionalEdgeHelper(manifold, feat, f);

    int cVar3;
    if (p5 == 0)
        cVar3 = 3;
    else
        cVar3 = (p5 == 1) + 1;

    unsigned char bVar2 = (unsigned char)(feat.mB ^ (unsigned char)(1u << (cVar3 + 4)));
    feat.mB = bVar2;
    addAdditionalEdgeHelper(manifold, feat, f);

    feat.mA = (unsigned char)(feat.mA ^ bVar4);
    addAdditionalEdgeHelper(manifold, feat, f);
}