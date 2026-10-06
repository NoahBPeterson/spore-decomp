// @ 0x00f4d9c0  SP::cTerrainBrushEffect::BuildRibbonBrush   (real name, PDB anchor)
//
// PARTIAL.  The retail function (5433 B) rebuilds the ribbon-brush vertex list
// from the effect's mRibbonBrushList, parameterises it by arc length, emits
// ribbon quads and finally recomputes the fall-off / gradient parameters.
//
// The class layout is the dev-PDB layout.  The overall control flow and all
// callees are reproduced; the per-quad vertex packing (Ghidra's out-of-frame
// fRamfffffeXX spills) is not fully transcribed.

#include "types.h"
extern "C" float sqrtf(float);

struct cBrushVertex;                 // eastl vector element, 0x1c bytes
struct cRibbonBrushPoly;
struct cTerrainBrushDescription;

namespace SP {
class cTerrainBrushEffect {
public:
    char pad0[0xc];
    cTerrainBrushDescription* mDesc;                  // +0xc
    char pad1[0xb8];                                  // +0x10 .. +0xc7
    void* mRibbonBrushList_begin;                     // +0xc4 (eastl::vector begin)
    void* mRibbonBrushList_end;                       // +0xc8
    void* mRibbonBrushList_cap;                       // +0xcc
public:
    void __thiscall BuildRibbonBrush(void);
};
} // namespace SP

extern int  DAT_016c8ff0, DAT_016c8ff4, DAT_016c8ff8, DAT_016c9020;
extern char _sRandom_Swarm;

extern "C" {
    void  EA_Swarm_ScaleCurve(void*, void*);
    void  EA_Swarm_SnapParticleToPath(float*, float, void*, void*, void*, void*);
    unsigned EA_Random_Uint32Uniform(void*, int);
    void  FUN_00a7ab40(int, void*, float, void*, void*);
    void  FUN_00f4c0a0(float);
    float FUN_00f678d0();
    void  FUN_00f4baa0(float, int, int, void*);
    void  TerrainEditor();
    void  operator_delete__(void*);
    void  eastl_RibbonPoly_Insert(void*, void*);
    void  rw_Matrix33_Ctor(void*, void*);
}

void __thiscall SP::cTerrainBrushEffect::BuildRibbonBrush(void)
{
    // ---- local scratch state ----
    float local_288[9];              // working matrix
    float local_338[8];              // previous left curve
    float local_258[8];              // previous right curve
    float local_3a0[6];              // left curve sample
    float local_2d0[6];              // right curve sample
    int   local_34c = 0, local_348 = 0, local_360 = 0, local_35c = 0;
    int   local_2b0 = 0;
    void* local_304 = 0, *local_300 = 0, *local_2fc = 0;
    int   iVar9, iVar13, iVar11, local_414, local_36c, local_310, local_410, local_2d8;
    float local_3c8, fVar18, fVar19, fVar20, fVar21, fVar22, fVar23, fVar24, fVar25, fVar26;
    float local_1c8 = 0.0f;

    rw_Matrix33_Ctor(local_288, &DAT_016c9020);
    iVar9 = *(int*)((char*)mDesc + 0x8c);   // mRibbonNumSkip / stride
    local_414 = 0;
    local_36c = 0;
    local_310 = 0;

    // ---- 1. copy mRibbonBrushList positions / UVs into two working arrays ----
    int count = ((int)mRibbonBrushList_end - (int)mRibbonBrushList_begin) / 0x1c;
    for (local_414 = 0, iVar13 = 0; local_414 < count; ) {
        // copy position (12 B) and UV-derived (12 B) for element iVar13
        // (uses ::EA::Swarm::ScaleCurve to append)
        local_414 += iVar9;
        iVar13 += iVar9 * 0x1c;
    }

    // ---- 2. fill in accessor / size arrays ----
    FUN_00a7ab40(0, 0, 1.0f, 0, &local_34c);
    FUN_00a7ab40(0, 0, 1.0f, 0, &local_360);

    // ---- 3. arc-length parameterisation of both curves ----
    iVar9 = (local_348 - local_34c) / 0x1c;
    for (local_414 = 0, iVar13 = 0; local_414 < iVar9; ++local_414, iVar13 += 0x1c) {
        fVar24 = (float)local_414;
        fVar18 = (float)(iVar9 - 1);
        *(float*)(local_34c + 0x18 + iVar13) = (fVar24 / fVar18) *
            *(float*)(local_34c - 4 + iVar9 * 0x1c);
        int iVar10 = (local_35c - local_360) / 0x1c;
        iVar9 = iVar10 - 1;
        fVar18 = (float)iVar9;
        *(float*)(local_360 + -4 + iVar13 + 0x1c) = (fVar24 / fVar18) *
            *(float*)(local_360 - 4 + iVar10 * 0x1c);
    }

    // ---- 4. ribbon quad emission ----
    {
        int n = *(int*)((char*)mDesc + 0x8c);
        local_36c = n / (local_310 ? local_310 : 1);
        FUN_00f4c0a0((float)n);
        unsigned rnd = EA_Random_Uint32Uniform(&_sRandom_Swarm,
                                               *(int*)((char*)mDesc + 0x98));
        EA_Swarm_SnapParticleToPath(local_3a0, 0.0f, &local_34c, (void*)local_34c,
                                    (void*)(local_34c + 0xc), 0);
        EA_Swarm_SnapParticleToPath(local_2d0, 0.0f, &local_360, (void*)local_360,
                                    (void*)(local_360 + 0xc), 0);
        for (int k = 0; k < 8; ++k) { local_338[k] = local_3a0[k]; local_258[k] = local_2d0[k]; }

        local_2d8 = local_36c / 2;
        local_410 = -(local_36c / 2);
        for (iVar11 = 0; iVar11 < n; ++iVar11) {
            iVar13 = local_2d8;
            EA_Swarm_SnapParticleToPath(local_3a0,
                (local_3a0[1] - 0.001f) / (float)n, &local_34c, (void*)local_34c,
                (void*)(local_34c + 0xc), 0);
            EA_Swarm_SnapParticleToPath(local_2d0,
                (local_2d0[1] - 0.001f) / (float)n, &local_360, (void*)local_360,
                (void*)(local_360 + 0xc), 0);
            // frame orthonormalisation (Ghidra fVar18..fVar26 block)
            fVar18 = 1.0f / sqrtf(local_338[2]*local_338[2] +
                                  (local_338[3]*local_338[3] + local_258[2]*local_258[2]));
            fVar19 = local_338[2] * fVar18;
            fVar20 = local_338[3] * fVar18;
            fVar24 = local_258[2] * fVar18;
            fVar21 = 1.0f / sqrtf(local_3a0[2]*local_3a0[2] +
                                  (local_3a0[3]*local_3a0[3] + local_3a0[4]*local_3a0[4]));
            (void)fVar19;(void)fVar20;(void)fVar24;(void)fVar21;
            // U span selection (three bands, 0.25 each)
            if (iVar11 < iVar13) { local_3c8 = ((float)iVar11/(float)iVar13)*0.25f;
                                   fVar21 = ((float)(iVar11+1)/(float)iVar13)*0.25f; }
            else if (iVar11 < local_36c*local_310 - iVar13) {
                local_3c8 = ((float)(local_410 % local_36c)/(float)local_36c)*0.5f + 0.25f;
                fVar21 = ((float)(local_410 % local_36c + 1)/(float)local_36c)*0.5f;
            } else {
                int j = (iVar13 - local_36c*local_310) + iVar11;
                local_3c8 = ((float)j/(float)iVar13)*0.25f + 0.75f;
                fVar21 = ((float)(j+1)/(float)iVar13)*0.25f;
            }
            eastl_RibbonPoly_Insert(0, 0);   // eastl::vector<cRibbonBrushPoly>::DoInsertValue
            ++local_410;
            for (int k = 0; k < 8; ++k) { local_338[k] = local_3a0[k]; local_258[k] = local_2d0[k]; }
        }
    }

    // ---- 5. optional size variation ----
    if (*(char*)((char*)mDesc + 0xa8) != 0) {   // mSizeVary
        TerrainEditor();
        FUN_00f678d0();
        local_1c8 = FUN_00f678d0() - 0.5f;
    }

    // ---- 6. fall-off / gradient parameters ----
    FUN_00f4baa0(1.0f, 0, 0, 0);

    // ---- 7. cleanup ----
    if (local_304 && *(int*)((char*)local_304 - 4) != 0) operator_delete__(local_304);
    if (local_2b0 && *(int*)((char*)local_2b0 - 4) != 0) operator_delete__((void*)local_2b0);
    if (local_360 && *(int*)(local_360 - 4) != 0) operator_delete__((void*)local_360);
    if (local_34c && *(int*)(local_34c - 4) != 0) operator_delete__((void*)local_34c);
}
