// Slice s0110c160 -- Havok 3.1.0 hkGsk / hkCollideTriangleUtil support region.
//
// Five functions:
//   0110c160  triangle halfspace vertex-index resolver (local, __fastcall)
//   0110c330  hkGsk::checkTriangleBoundaries   (995 bytes, x87-heavy)
//   0110c720  hkGsk triangle/segment contact solver (1497 bytes, x87-heavy)
//   0110cd00  per-face min/median/max vertex-index sorter (local, __thiscall)
//   0110cde0  hkGsk::convertFeatureToClosestDistance (221 bytes)
//
// The two large contact solvers are x87-register-juggling routines; their
// source is reproduced behaviourally.  The two small index helpers are the
// tractable byte-exact candidates.
#include "types.h"

// ---------------------------------------------------------------------------
// Local stub types.
// ---------------------------------------------------------------------------
struct hkVector4 {
    float x, y, z, w;
};

// Output record of convertFeatureToClosestDistance: the input vector (x,y,z,w),
// the chosen plane distance vector at +0x10, the input w replicated at +0x20,
// and the blend factor at +0x24.
struct hkGskOut {
    hkVector4 mVector_00;   // 0x00
    hkVector4 mPlane_10;    // 0x10
    float     mInW_20;      // 0x20
    float     mFactor_24;   // 0x24
};

// The hkGsk support object touched by these functions.
struct hkGsk {
    int mCountA_00;             // 0x00
    int mCountB_04;             // 0x04
    char pad_08[0xc];
    int mFlag_14;               // 0x14
    char pad_18[8];
    hkVector4 mPlaneA_20;       // 0x20
    char pad_30[0x70];
    hkVector4 mPlaneB_a0;       // 0xa0
    char pad_b0[0x70];
    hkVector4 mNormal_120;      // 0x120
    hkVector4 mPlaneC_130;      // 0x130
    float     mA_160;           // 0x160
    float     mB_164;           // 0x164
    float     mC_168;           // 0x168
    int       mD_16c;           // 0x16c
    int       mE_170;           // 0x170

    // 0x00c330
    unsigned char checkTriangleBoundaries(const float* point, float* tri, int supportType);
    // 0x00c720
    int subdivideTriangle(float* tri, float* scratch, int* pA, int* pB, char flag,
                          int param7);
    // 0x00cde0
    void convertFeatureToClosestDistance(const hkVector4& in, hkGskOut& out);
};

// One 8-entry ushort feature record (16 bytes); only the leading index is read
// by the sort helper, the rest are the remaining face/vertex slots.
struct hkFeatureEntry {
    unsigned short idx[8];       // 16 bytes
};

// The triangle util object operated on by 0110cd00:
//   +0   int   countA        (also read as a char for the output header)
//   +4   int   countB
//   +0x2c/+0x3c/+0x4c  feature entries A0/A1/A2
//   +0xec/+0xfc/+0x10c feature entries B0/B1/B2
struct hkTriangleUtil {
    int  mCountA_00;             // 0x00
    int  mCountB_04;             // 0x04
    char pad_08[0x24];
    hkFeatureEntry mFeatA0_2c;   // 0x2c
    hkFeatureEntry mFeatA1_3c;   // 0x3c
    hkFeatureEntry mFeatA2_4c;   // 0x4c
    char pad_5c[0x90];
    hkFeatureEntry mFeatB0_ec;   // 0xec
    hkFeatureEntry mFeatB1_fc;   // 0xfc
    hkFeatureEntry mFeatB2_10c;  // 0x10c

    void sortFeatureIndices(void* out);   // 0x00cd00
};

// Output record of sortFeatureIndices: three sorted ushort indices, then the
// two per-block counts as bytes.
struct hkFeatureIndexOut {
    unsigned short a;            // 0x0  min
    unsigned short b;            // 0x2  median
    unsigned short c;            // 0x4  max
    unsigned short field_6;      // 0x6
    char           countA;       // 0x8
    char           countB;       // 0x9
};

// ---------------------------------------------------------------------------
// Constants.
// ---------------------------------------------------------------------------
extern float _HK_REAL_ZERO;   // 0x01485378

// hkCollideTriangleUtil::closestLineSegLineSeg @ 0x01105940 -- returns the
// closest-point result for two line segments (32-byte result struct).
void __cdecl FUN_01105940(const float* a0, const float* a1, const float* b0,
                          const float* b1, void* result);

// ---------------------------------------------------------------------------
// 0110c160 -- triangle halfspace vertex resolver.
//   ecx   : unused (this)
//   edx   : param_2, triangle vertex block (4 hkVector4s)
//   [ebp+8]  : param_3, query point
//   [ebp+0xc]: param_4, per-vertex out array (float[3])
// For each of 3 halfspace axes, compares the signed distance of the two
// vertices selected by the tables at 0x014a5e72 / 0x014a5e70 and marks the
// losing one with -1.0f.  Returns the surviving vertex index, or -1.
// ---------------------------------------------------------------------------
extern const signed char DAT_014a5e72[];
extern const signed char DAT_014a5e70[];

// @ 0x0110c160
int __fastcall TriangleHalfspaceResolve(int /*unused*/, float* tri,
                                        const float* point, float* out) {
    float* pfVar11 = tri + 2;
    for (int i = 0; i < 3; i++, pfVar11 += 4) {
        int iA = (int)(char)DAT_014a5e72[i];
        int iB = (int)(char)DAT_014a5e70[i];
        if (!(out[iA] < 0.0f) && !(out[iB] < 0.0f)) {
            float ax = tri[iA * 4 + 0] - pfVar11[-2];
            float ay = tri[iA * 4 + 1] - pfVar11[-1];
            float az = tri[iA * 4 + 2] - pfVar11[0];
            float bx = tri[iB * 4 + 0] - pfVar11[-2];
            float by = tri[iB * 4 + 1] - pfVar11[-1];
            float bz = tri[iB * 4 + 2] - pfVar11[0];
            float cx = tri[0xc] - pfVar11[-2];
            float cy = tri[0xd] - pfVar11[-1];
            float cz = tri[0xe] - pfVar11[0];
            float px = point[0] - pfVar11[-2];
            float py = point[1] - pfVar11[-1];
            float pz = point[2] - pfVar11[0];
            if ((cx * ax + (cy * ay + cz * az)) * (px * bx + (py * by + pz * bz))
                <= (px * ax + (py * ay + pz * az)) * (cx * bx + (cy * by + cz * bz))) {
                out[iA] = -1.0f;
            } else {
                out[iB] = -1.0f;
            }
        }
    }
    if (0.0f < out[0]) return 0;
    if (0.0f < out[1]) return 1;
    if (out[2] <= 0.0f) return -1;
    return 2;
}

// ---------------------------------------------------------------------------
// 0110c330 -- hkGsk::checkTriangleBoundaries(const hkVector4& point,
//            hkVector4* tri, SupportTypes supportType).
// Computes three signed plane values from the triangle edges / query point and
// stores them into this+0x160..0x168; when supportType != 0 it also caches the
// triangle's edge normals.  Returns a 3-bit "outside" mask.
//   this       : ecx
//   [ebp+8]    : point
//   [ebp+0xc]  : tri (6 hkVector4 -> 24 floats)
//   [ebp+0x10] : supportType
// ---------------------------------------------------------------------------
// @ 0x0110c330
unsigned char hkGsk::checkTriangleBoundaries(const float* point, float* tri, int supportType) {
    float e20 = tri[8] - tri[4];
    float e24 = tri[9] - tri[5];
    float e25 = tri[10] - tri[6];
    float e26 = tri[0] - tri[8];
    float e27 = tri[1] - tri[9];
    float e28 = tri[2] - tri[10];

    float n0 = e28 * e24 - e27 * e25;
    float n1 = e26 * e25 - e28 * e20;
    float n2 = e27 * e20 - e24 * e26;

    float d26 = point[0] - tri[8];
    float d27 = point[1] - tri[9];
    float d28 = point[2] - tri[10];
    float d60 = point[0] - tri[4];
    float d64 = point[1] - tri[5];
    float d68 = point[2] - tri[6];
    float d40 = point[0] - tri[0];
    float d44 = point[1] - tri[1];
    float d48 = point[2] - tri[2];

    float v160 = (d64 * e25 - d68 * e24) * n0 +
                 ((d68 * e20 - e25 * d60) * n1 +
                 (e24 * d60 - d64 * e20) * n2);

    float v164;
    {
        float da0 = point[0] - tri[8];
        float da1 = point[1] - tri[9];
        float da2 = point[2] - tri[10];
        float x1 = point[1] - tri[5];
        float x2 = point[2] - tri[6];
        float y0 = point[0] - tri[4];
        v164 = (x1 * e28 - x2 * e27) * n0 +
               ((x2 * e26 - e28 * (da0)) * n1 +
               (e27 * (da0) - x1 * e26) * n2);
        (void)da1; (void)da2;
    }

    float v168;
    {
        float A1 = point[1] - tri[5];
        float A2 = point[2] - tri[6];
        float B0 = point[0] - tri[4];
        v168 = (A1 * (tri[6] - tri[2]) - A2 * (tri[5] - tri[1])) * n0 +
               ((A2 * (tri[4] - tri[0]) - (tri[6] - tri[2]) * B0) * n1 +
               ((tri[5] - tri[1]) * B0 - A1 * (tri[4] - tri[0])) * n2);
    }

    mA_160 = v160;
    mB_164 = v164;
    mC_168 = v168;
    mD_16c = 0;

    unsigned char mask = (unsigned char)(((v168 < 0.0f) << 1) |
                                         ((v164 < 0.0f) << 2) |
                                         (((v160 < 0.0f) ? (unsigned)-8 : 0u)));
    mask &= 0xe;

    if (supportType != 0) {
        mNormal_120.x = n0;
        mNormal_120.y = n1;
        mNormal_120.z = n2;
        mNormal_120.w = 0.0f;
        if (mask == 0xe) {
            float dot = n0 * (mPlaneA_20.x - mPlaneB_a0.x) +
                        ((mPlaneA_20.y - mPlaneB_a0.y) * n1 +
                        n2 * (mPlaneA_20.z - mPlaneB_a0.z));
            if (dot < 0.0f) {
                mNormal_120.w = 0.0f;
                mNormal_120.x = -n0;
                mNormal_120.y = -n1;
                mNormal_120.z = -n2;
                float t;
                t = tri[0]; tri[0] = tri[4]; tri[4] = t;
                t = tri[1]; tri[1] = tri[5]; tri[5] = t;
                t = tri[2]; tri[2] = tri[6]; tri[6] = t;
                t = tri[3]; tri[3] = tri[7]; tri[7] = t;
                t = tri[0x10]; tri[0x10] = tri[0x14]; tri[0x14] = t;
                t = tri[0x11]; tri[0x11] = tri[0x15]; tri[0x15] = t;
                t = tri[0x12]; tri[0x12] = tri[0x16]; tri[0x16] = t;
                t = tri[0x13]; tri[0x13] = tri[0x17]; tri[0x17] = t;
                t = mA_160; mA_160 = mB_164; mB_164 = t;
                mFlag_14 = 1;
            }
        }
    }
    return mask;
}

// ---------------------------------------------------------------------------
// 0110c720 -- hkGsk triangle/segment contact solver.
//   this      : ecx
//   [ebp+8]   : tri (float*, 6 hkVector4)
//   [ebp+0xc] : other (float*, vertex arrays)
//   [ebp+0x10]: int* counterA
//   [ebp+0x14]: int* counterB
//   [ebp+0x18]: char flag
//   [ebp+0x1c]: int  param7
// ---------------------------------------------------------------------------
// @ 0x0110c720
int hkGsk::subdivideTriangle(float* tri, float* other, int* pA, int* pB, char flag,
                             int param7) {
    float local_b0, local_ac, local_a8, local_a4;
    float local_90, local_8c, local_88, local_84;
    float local_80, local_7c, local_78, local_74;
    float local_50, local_20;
    float seg0[8];
    float seg1[8];

    if (flag != '\0') {
        float* pfVar6 = tri + 8;
        local_90 = tri[4] - pfVar6[0];
        local_8c = tri[5] - tri[9];
        local_88 = tri[6] - tri[10];
        local_84 = tri[7] - tri[0xb];
        local_80 = tri[0] - pfVar6[0];
        local_7c = tri[1] - tri[9];
        local_78 = tri[2] - tri[10];
        local_74 = tri[3] - tri[0xb];
        float fVar1 = local_78 * local_8c - local_7c * local_88;
        float fVar3 = local_88 * local_80 - local_78 * local_90;
        float fVar2 = local_7c * local_90 - local_8c * local_80;
        local_b0 = other[4] - tri[0];
        local_ac = other[5] - tri[1];
        local_a8 = other[6] - tri[2];
        float v94 = (other[1] - tri[1]) * fVar3 +
                    ((other[2] - tri[2]) * fVar2 + fVar1 * (other[0] - tri[0]));
        float v2 = local_ac * fVar3 + (local_a8 * fVar2 + fVar1 * local_b0);
        int iVar8, iVar5;
        if (0.0f <= v94) iVar8 = 0; else iVar8 = 8;
        if (0.0f <= v2)  iVar5 = 0; else iVar5 = 8;
        if (iVar8 == iVar5) {
            float a94 = v94 < 0.0f ? -v94 : v94;
            float a2 = v2 < 0.0f ? -v2 : v2;
            if (a2 < a94) {
                float t;
                t = other[0]; other[0] = other[4]; other[4] = t;
                t = other[1]; other[1] = other[5]; other[5] = t;
                t = other[2]; other[2] = other[6]; other[6] = t;
                t = other[3]; other[3] = other[7]; other[7] = t;
                t = other[0x10]; other[0x10] = other[0x14]; other[0x14] = t;
                t = other[0x11]; other[0x11] = other[0x15]; other[0x15] = t;
                t = other[0x12]; other[0x12] = other[0x16]; other[0x16] = t;
                t = other[0x13]; other[0x13] = other[0x17]; other[0x17] = t;
            }
            iVar8 = checkTriangleBoundaries(other, tri, 8);
            if (iVar8 == 0xe) {
                *pA = *pA - 1;
                return 0;
            }
        } else {
            float fVar1b = v94 / (v94 - v2);
            float fVar2b = 1.0f - fVar1b;
            local_b0 = fVar1b * other[4] + fVar2b * other[0];
            local_ac = fVar2b * other[1] + fVar1b * other[5];
            local_a8 = fVar2b * other[2] + fVar1b * other[6];
            local_a4 = fVar2b * other[3] + fVar1b * other[7];
            iVar8 = checkTriangleBoundaries(&local_b0, tri, 0);
            if (iVar8 == 0xe) {
                return 1;
            }
        }
        local_b0 = other[4] - other[0];
        local_ac = other[5] - other[1];
        local_a8 = other[6] - other[2];
        local_a4 = other[7] - other[3];
        FUN_01105940(other, &local_b0, pfVar6, &local_90, seg0);
        FUN_01105940(other, &local_b0, pfVar6, &local_80, seg1);
        unsigned int uVar7 = (unsigned int)(local_20 < local_50);
        tri[uVar7 * 4] = pfVar6[0];
        tri[uVar7 * 4 + 1] = tri[9];
        tri[uVar7 * 4 + 2] = tri[10];
        tri[uVar7 * 4 + 3] = tri[0xb];
        pfVar6 = tri + (uVar7 + 4) * 4;
        pfVar6[0] = tri[0x18];
        pfVar6[1] = tri[0x19];
        pfVar6[2] = tri[0x1a];
        pfVar6[3] = tri[0x1b];
        *pB = *pB - 1;
        return 2;
    }

    float* pfVar6 = tri + 4;
    local_90 = mA_160;
    local_8c = mB_164;
    local_88 = mC_168;
    local_84 = *(float*)&mD_16c;

    float fVar1 = (tri[4] - other[0]) * mNormal_120.x +
                  ((tri[5] - other[1]) * mNormal_120.y +
                  (tri[6] - other[2]) * mNormal_120.z);
    float fVar2 = (tri[0] - other[0]) * mNormal_120.x +
                  ((tri[1] - other[1]) * mNormal_120.y +
                  (tri[2] - other[2]) * mNormal_120.z);
    if (fVar2 * fVar1 < 0.0f) {
        fVar2 = fVar2 / (fVar2 - fVar1);
        fVar1 = 1.0f - fVar2;
        local_b0 = fVar2 * pfVar6[0] + fVar1 * tri[0];
        local_ac = fVar1 * tri[1] + fVar2 * tri[5];
        local_a8 = fVar1 * tri[2] + fVar2 * tri[6];
        local_a4 = fVar2 * tri[7] + fVar1 * tri[3];
        int iVar8 = checkTriangleBoundaries(&local_b0, tri, 0);
        if (iVar8 == 0xe) {
            return 1;
        }
    }
    int iVar8 = checkTriangleBoundaries(pfVar6, tri, 0);
    if (iVar8 == 0xe) {
        *pA = *pA - 1;
        tri[0] = pfVar6[0];
        tri[1] = tri[5];
        tri[2] = tri[6];
        tri[3] = tri[7];
        tri[0x10] = tri[0x14];
        tri[0x11] = tri[0x15];
        tri[0x12] = tri[0x16];
        tri[0x13] = tri[0x17];
        mE_170 = param7;
        return 0;
    }
    if (iVar8 == 6) goto LAB_ccb7;
    if (iVar8 == 10) {
LAB_cc74:
        *pB = *pB - 1;
        tri[4] = tri[8];
        tri[5] = tri[9];
        tri[6] = tri[10];
        tri[7] = tri[0xb];
        tri[0x14] = tri[0x18];
        tri[0x15] = tri[0x19];
        tri[0x16] = tri[0x1a];
        tri[0x17] = tri[0x1b];
        return 2;
    }
    if (iVar8 != 0xc) {
        if (iVar8 != 8) {
            if (iVar8 == 4) {
                if ((mC_168 - local_88) * local_90 <= (mA_160 - local_90) * local_88)
                    goto LAB_cc37;
            } else if (iVar8 == 2 &&
                       ((mB_164 - local_8c) * local_90 < (mA_160 - local_90) * local_8c)) {
                goto LAB_cc74;
            }
LAB_ccb7:
            *pB = *pB - 1;
            tri[0] = tri[8];
            tri[1] = tri[9];
            tri[2] = tri[10];
            tri[3] = tri[0xb];
            tri[0x10] = tri[0x18];
            tri[0x11] = tri[0x19];
            tri[0x12] = tri[0x1a];
            tri[0x13] = tri[0x1b];
            return 2;
        }
        if ((mB_164 - local_8c) * local_88 <= (mC_168 - local_88) * local_8c)
            goto LAB_cc74;
    }
LAB_cc37:
    *pB = *pB - 1;
    return 2;
}

// Sorts countA leading feature indices into (min, median, max) and repeats the
// block starting at +0x3b (B1) when countB > 1.
// ---------------------------------------------------------------------------
// @ 0x0110cd00
void hkTriangleUtil::sortFeatureIndices(void* outv) {
    hkFeatureIndexOut* out = (hkFeatureIndexOut*)outv;
    unsigned short* arr = (unsigned short*)outv;

    out->countA = (char)mCountA_00;
    out->countB = (char)mCountB_04;

    int cntA = mCountA_00;
    unsigned short uVar1 = mFeatA0_2c.idx[0];      // ax
    if (cntA >= 2) {
        unsigned short uVar3 = mFeatA1_3c.idx[0];  // dx
        int flag = 0;                              // bx
        if (uVar3 > uVar1) {
            unsigned short t = uVar3; uVar3 = uVar1; uVar1 = t; flag = 1;
        }
        if (cntA > 2) {
            unsigned short uVar4 = mFeatA2_4c.idx[0];  // si
            if (uVar4 > uVar1) {
                unsigned short t = uVar4; uVar4 = uVar1; uVar1 = t; flag++;
            }
            if (flag == 1) {
                unsigned short t = uVar4; uVar4 = uVar3; uVar3 = t;
            }
            arr[2] = uVar4;
        }
        arr[1] = uVar3;
    }
    arr[0] = uVar1;

    int cntB = mCountB_04;
    uVar1 = mFeatB0_ec.idx[0];
    if (cntB >= 2) {
        unsigned short uVar3 = mFeatB1_fc.idx[0];
        int flag = 0;
        if (uVar3 > uVar1) {
            unsigned short t = uVar3; uVar3 = uVar1; uVar1 = t; flag = 1;
        }
        if (cntB > 2) {
            unsigned short uVar4 = mFeatB2_10c.idx[0];
            if (uVar4 > uVar1) {
                unsigned short t = uVar4; uVar4 = uVar1; uVar1 = t; flag++;
            }
            if (flag == 1) {
                unsigned short t = uVar4; uVar4 = uVar3; uVar3 = t;
            }
            arr[mCountA_00 + 2] = uVar4;
        }
        arr[mCountA_00 + 1] = uVar3;
        arr[mCountA_00] = uVar1;
        return;
    }
    arr[mCountA_00] = uVar1;
}

// ---------------------------------------------------------------------------
// 0110cde0 -- __thiscall(this = hkGsk support, in, out).
// Copies the input vector, then selects one of three plane-distance vectors:
//   * countA == 1 -> plane at +0x20, blend factor 1.0
//   * countB == 1 -> plane at +0xa0, offset by in.w * (vector at +0), factor 0.0
//   * otherwise   -> plane at +0x130, factor 0.5
// ---------------------------------------------------------------------------
// @ 0x0110cde0
void hkGsk::convertFeatureToClosestDistance(const hkVector4& in, hkGskOut& out) {
    out.mInW_20 = in.w;
    out.mVector_00.x = in.x;
    out.mVector_00.y = in.y;
    out.mVector_00.z = in.z;
    out.mVector_00.w = in.w;

    if (mCountA_00 == 1) {
        out.mPlane_10.x = mPlaneA_20.x;
        out.mPlane_10.y = mPlaneA_20.y;
        out.mPlane_10.z = mPlaneA_20.z;
        out.mPlane_10.w = mPlaneA_20.w;
        out.mFactor_24 = 1.0f;
        return;
    }
    int cntB = mCountB_04;
    if (cntB == 1) {
        float f = in.w;
        out.mPlane_10.x = mPlaneB_a0.x;
        out.mPlane_10.y = mPlaneB_a0.y;
        out.mPlane_10.z = mPlaneB_a0.z;
        out.mPlane_10.w = mPlaneB_a0.w;
        out.mPlane_10.x = f * out.mVector_00.x + out.mPlane_10.x;
        out.mPlane_10.y = f * out.mVector_00.y + out.mPlane_10.y;
        out.mPlane_10.z = f * out.mVector_00.z + out.mPlane_10.z;
        out.mPlane_10.w = f * out.mVector_00.w + out.mPlane_10.w;
        out.mFactor_24 = 0.0f;
        return;
    }
    out.mPlane_10.x = mPlaneC_130.x;
    out.mPlane_10.y = mPlaneC_130.y;
    out.mPlane_10.z = mPlaneC_130.z;
    out.mPlane_10.w = mPlaneC_130.w;
    out.mFactor_24 = 0.5f;
}
