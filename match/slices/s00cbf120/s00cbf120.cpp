// @ 0x00cbf120  SP::FindProjectilePath   (PDB candidate, caller-scored)
//
// Reconstruction of the retail function at 0x00cbf120 (5597 bytes, /O2 /MD /TP,
// mixed SSE/x87).  This is a large trajectory-sampling routine: given a launch
// object (pA), an optional target (pB), a launch offset, a mode and a spread it
// builds a list of Vec3 points and, in some modes, queries the world for
// candidate ballistic arcs.
//
// Every branch and callee of the original is present.  Names of locals follow the
// Ghidra decompile where the value is a plain temporary.

#include "types.h"

extern "C" float sqrtf(float);
extern "C" float sinf(float);
extern "C" float cosf(float);

struct Vec3 { float x, y, z; };

// ---- globals (addresses are relocations and are masked by the verifier) ----
extern float g_0157e904, g_0157e900, g_0169aa28, g_013ec4b8, g_013ec480;
extern float g_01471064, g_01470f1c, g_0140e964, g_01485378, g_01485720;
extern char  g_desc_pos[], g_desc_type[];
extern char  g_game_mode[];

// ---- engine object with the vtable slots the original calls ----
// Slot index = byte offset / 4 (0x2c=11, 0x30=12, 0x4c=19, 0x68=26, 0x70=28,
// 0xb8=46, 0xc0=48).  Unused slots are placeholders that keep the offsets right.
struct IObj {
    virtual void  p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void  p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void  p08(); virtual void p09(); virtual void p10();
    virtual Vec3* GetPosition();                 // 0x2c
    virtual Vec3* GetOrientedPosition(...);      // 0x30 (0 args) / (out*)
    virtual void  p13(); virtual void p14(); virtual void p15();
    virtual void  p16(); virtual void p17(); virtual void p18();
    virtual void  Query(Vec3*, Vec3*, void**, int); // 0x4c
    virtual void  p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void  p24(); virtual void p25();
    virtual void* GetOrient(...);                // 0x68
    virtual void  p27();
    virtual void  Notify();                      // 0x70
    virtual void  p29(); virtual void p30(); virtual void p31(); virtual void p32();
    virtual void  p33(); virtual void p34(); virtual void p35(); virtual void p36();
    virtual void  p37(); virtual void p38(); virtual void p39(); virtual void p40();
    virtual void  p41(); virtual void p42(); virtual void p43(); virtual void p44();
    virtual void  p45();
    virtual int   IsType(int);                   // 0xb8
    virtual void  p47();
    virtual void  Release();                     // 0xc0
};

struct VecList { Vec3* begin; Vec3* end; Vec3* cap; };

// ---- callees (relocations are masked; signatures are descriptive) ----
struct cPlanetModel {
    Vec3* MakeRandomWorldPosition(Vec3*, Vec3*, float, float);
    void  DirectionToSurfacePosition(Vec3*, Vec3*);
};
extern "C" {
    IObj*  FUN_00b3d240();
    char   FUN_00cbd620(IObj*, IObj*, VecList*, float, float, float);
    float  FUN_00b7e4d0();
    char   FUN_00cbcde0(float, float, float, float, float, float, VecList*);
    void   FUN_00466320(void*);
    void   FUN_00409930();
    void   FUN_0044d4f0(Vec3*);
    void   FUN_00722c60(float*);
    void   FUN_00cb3f80(float*, float*, float*, float*, float*, float*);
    void   FUN_00cbcc40(float, float, float, float, float, float, VecList*);
    char   FUN_00b35bf0(IObj*, Vec3*, Vec3*, Vec3*);
    void   FUN_004b5ad0(Vec3*, Vec3*);      // eastl::vector<Vec3>::DoInsertValue
    void   operator_delete__(void*);
    void   eastl_copy_range(void*, void*);
    void*  GetCurrentGameMode();
    void   Matrix3FromQuaternion(float*, Vec3*);
    float  RandomDoubleUniform(void*);
    cPlanetModel* PlanetModelCtor2(Vec3*, Vec3*);
    cPlanetModel* PlanetModelCtor4(Vec3*, Vec3*, float, float);
    void   PlanetModelDtor();
    Vec3*  normalized_safe(Vec3*, Vec3*);
}

// helper: append a point, growing through the vector's DoInsertValue path.
static inline void AppendPoint(VecList* v, const Vec3& p)
{
    if (v->end < v->cap) {
        *v->end = p;
        v->end = v->end + 1;
    } else {
        FUN_004b5ad0(v->end, (Vec3*)&p);
    }
}

void __cdecl FindProjectilePath(IObj* param_1, IObj* param_2, VecList* param_3,
                                float param_4, float param_5, float param_6,
                                int param_7, float param_8)
{
    // ---- exact scalar temporaries used by the original (names from Ghidra) ----
    float fStack_3ac = 0, fStack_3a8 = 0, fStack_3a4 = 0, fStack_3a0 = 0;
    float fStack_39c = 0, fStack_398 = 0, fStack_394 = 0, fStack_378 = 0;
    float fStack_374 = 0, fStack_370 = 0, local_36c = 0, fStack_368 = 0;
    float fStack_364 = 0, fStack_360 = 0, fStack_35c = 0;
    float fStack_358 = 0, fStack_354 = 0, fStack_350 = 0;
    float fStack_34c = 0, fStack_348 = 0, fStack_344 = 0;
    float fStack_340 = 0, fStack_33c = 0, fStack_338 = 0;
    float fStack_334 = 0, fStack_330 = 0, fStack_32c = 0, fStack_328 = 0;
    float fStack_324 = 0, fStack_320 = 0, fStack_31c = 0;
    float fStack_318 = 0, fStack_314 = 0, fStack_310 = 0, fStack_30c = 0;
    float f37c, f380, f384, f388, f38c, f390;
    float f2dc = 0, f2d8 = 0, f2d4 = 0;
    float u2f0 = 0, u2ec = 0, u2e8 = 0, f2e4 = 0;
    unsigned short u2e0 = 0; short s2de = 0;
    float a2cc[9] = {0}, a2a8[9] = {0};
    float af34[12] = {0};
    float afbuf[14] = {0};
    float f17, f18, f19, f20, f21, f22;
    float fVar14, fVar15;
    int *piVar4, *piVar1, *piVar2;
    int *piStack_308, *piStack_304 = 0, *piStack_300 = 0;
    float uStack_2fc = 0;
    unsigned char *puVar12 = 0, *puStack_284, *puStack_280, *puStack_27c, *puStack_274;
    unsigned char auStack_26c[512] = {0}, auStack_6c[56] = {0};
    float dummy[8] = {0};

    eastl_copy_range(param_3->begin, param_3->end);
    piVar4 = (int*)FUN_00b3d240();
    local_36c = (float)(int)piVar4;
    if (piVar4 == 0) {           // Ghidra: if (local_36c == 0.0) return;
        return;
    }
    if (param_7 == 3) {
        if (FUN_00cbd620(param_1, param_2, param_3, param_4, param_5, param_6) != 0) {
            return;
        }
        param_7 = 1;
    }

    // ---- launch position ----
    if (param_1 == 0) {
        piVar4 = 0;
    } else {
        piVar4 = (int*)param_1->IsType((int)g_desc_pos);
    }
    {
        float* pf;
        if (piVar4 == 0) {
            pf = (float*)param_1->GetPosition();
        } else {
            pf = (float*)((IObj*)piVar4)->GetOrientedPosition((Vec3*)&f38c);
        }
        f384 = pf[0]; f380 = pf[1]; f37c = pf[2];
    }

    // ---- target / offset position ----
    if (param_2 == 0) {
        f390 = param_4; f38c = param_5; f388 = param_6;
    } else {
        float* pf = (float*)param_2->GetPosition();
        f390 = pf[0] + param_4;
        f38c = pf[1] + param_5;
        f388 = pf[2] + param_6;
    }
    fStack_32c = f38c;
    fStack_330 = f390;
    fStack_328 = f388;

    // ---- mode specific setup ----
    if (param_7 == 4) {
        Vec3 vA, vB;
        vA.x = fStack_330; vA.y = fStack_32c; vA.z = fStack_328;   // target
        vB.x = f390;      vB.y = f38c;      vB.z = f388;            // dst
        f18 = g_0157e904;
        f17 = g_0157e904 + 1.0f;
        cPlanetModel* pm = PlanetModelCtor4(&vB, &vA, g_0157e904, f17);
        float* pf = (float*)pm->MakeRandomWorldPosition(&vB, &vA, f18, f17);
        f384 = pf[0]; f380 = pf[1]; f37c = pf[2];
        PlanetModelDtor();
        fVar14 = (float)FUN_00b7e4d0();
        f18 = fVar14 * g_0157e900;
        f17 = 1.0f / sqrtf((f384 * f384 + (f380 * f380 + f37c * f37c)) + 1e-8f);
        f384 = (f17 * f384) * f18;
        f380 = (f380 * f17) * f18;
        f37c = (f17 * f37c) * f18;
    } else if (param_7 == 5 &&
               FUN_00cbcde0(f384, f380, f37c, f390, f38c, f388, param_3) == 0) {
        param_7 = 1;
    }

    // ---- build the local coordinate frame at the arc midpoint ----
    {
        float dx = fStack_330 - f384;
        float dy = fStack_32c - f380;
        float dz = fStack_328 - f37c;
        fStack_3a0 = sqrtf((dx * dx + dy * dy) + dz * dz);
        f18 = 1.0f / fStack_3a0;
        float ux = f18 * dx, uy = f18 * dy, uz = f18 * dz;
        fStack_378 = fStack_3a0 * 0.5f;
        float mx = fStack_358 = ux * fStack_378 + f384;
        float my = fStack_338 = f380 + uy * fStack_378;
        float mz = fStack_394 = f37c + uz * fStack_378;
        (void)mx; (void)mz;
        fStack_368 = 1.0f / sqrtf(((fStack_358 * fStack_358 + fStack_338 * fStack_338) +
                                   fStack_394 * fStack_394) + 1e-8f);
        f20 = fStack_368 * fStack_394;
        fStack_318 = fStack_368 * fStack_358;
        fStack_368 = fStack_368 * fStack_338;
        local_36c = f20 * uy - fStack_368 * uz;       // cross(n, u).x
        f18      = fStack_318 * uz - f20 * ux;        // .y
        f19      = fStack_368 * ux - fStack_318 * uy; // .z
        f17 = 1.0f / sqrtf(((local_36c * local_36c + f18 * f18) + f19 * f19) + 1e-8f);
        local_36c = f17 * local_36c;
        f18 = f17 * f18;
        f17 = f17 * f19;
        fStack_334 = f17 * fStack_368 - f18 * f20;
        fStack_354 = local_36c * f20 - f17 * fStack_318;
        f19 = f18 * fStack_318 - local_36c * fStack_368;
        fStack_350 = 1.0f / sqrtf(((fStack_334 * fStack_334 + fStack_354 * fStack_354) +
                                   f19 * f19) + 1e-8f);
        fStack_334 = fStack_350 * fStack_334;
        fStack_354 = fStack_350 * fStack_354;
        fStack_350 = fStack_350 * f19;
        fStack_39c = f37c - fStack_394;
        fStack_3a4 = (f384 - fStack_358) * fStack_334 + (f380 - fStack_338) * fStack_354;
        fStack_314 = fStack_3a4 + fStack_39c * fStack_350;
        fStack_310 = ((f384 - fStack_358) * fStack_318 + (f380 - fStack_338) * fStack_368) +
                     fStack_39c * f20;
        fStack_340 = ((fStack_330 - fStack_358) * fStack_334 + (fStack_32c - fStack_338) * fStack_354) +
                     (fStack_328 - fStack_394) * fStack_350;
        fStack_33c = ((fStack_330 - fStack_358) * fStack_318 + (fStack_32c - fStack_338) * fStack_368) +
                     (fStack_328 - fStack_394) * f20;
    }

    if (param_7 == 2 || param_7 == 5) {
        goto LAB_00cc0229;
    }

    // ---- collect candidate objects around the launch point ----
    {
        Vec3 P, Q;
        Vec3* pf;
        Vec3 sV, tV;
        sV.x = f384; sV.y = f380; sV.z = f37c;          // launch position
        tV.x = fStack_330; tV.y = fStack_32c; tV.z = fStack_328; // target
        P.x = f384; P.y = f380; P.z = f37c;
        Q.x = fStack_330; Q.y = fStack_32c; Q.z = fStack_328;
        piStack_304 = 0;
        piStack_300 = 0;
        uStack_2fc = 0;
        PlanetModelCtor2(&P, &sV)->DirectionToSurfacePosition(&P, &sV);
        PlanetModelCtor2(&Q, &tV)->DirectionToSurfacePosition(&Q, &tV);
        Vec3 dvec; dvec.x = f390; dvec.y = f38c; dvec.z = f388;
        pf = normalized_safe(&dvec, &P);
        P.x = pf->x * 2.0f + P.x;
        P.y = P.y + pf->y * 2.0f;
        P.z = P.z + pf->z * 2.0f;
        pf = normalized_safe(&dvec, &Q);
        Q.x = pf->x * 2.0f + Q.x;
        Q.y = Q.y + pf->y * 2.0f;
        Q.z = Q.z + pf->z * 2.0f;

        piVar4 = (int*)FUN_00b3d240();
        ((IObj*)piVar4)->Query(&P, &Q, (void**)&piStack_304, 1);

        puStack_27c = auStack_6c;
        puStack_274 = auStack_26c;
        puStack_280 = auStack_26c;
        puStack_284 = auStack_26c;
        piStack_308 = piStack_300;
        piVar4 = piStack_304;
        if (piStack_304 != piStack_300) {
            do {
                piVar1 = (int*)*piVar4;
                piVar2 = 0;
                if (piVar1 != (int*)param_2 && piVar1 != (int*)param_1 &&
                    ((IObj*)piVar1)->IsType((int)0xce9f6639) == 0 &&
                    ((IObj*)piVar1)->IsType((int)0x2e71a5a) == 0 &&
                    ((IObj*)piVar1)->IsType((int)g_desc_type) == 0) {
                    float* pf2 = (float*)((IObj*)piVar1)->GetOrient();
                    if (pf2[0] < pf2[3] || pf2[0] == pf2[3]) {
                        float* pos = (float*)((IObj*)piVar1)->GetPosition();
                        f390 = pos[0]; f38c = pos[1]; f388 = pos[2];
                        ((IObj*)piVar1)->Notify();
                        puVar12 = auStack_6c;
                        ((IObj*)piVar1)->GetOrient(puVar12);
                        FUN_00466320(puVar12);
                        float* q = (float*)((IObj*)piVar1)->GetOrientedPosition();
                        u2f0 = q[0]; u2ec = q[1]; u2e8 = q[2]; f2e4 = q[3];
                        FUN_00409930();
                        Matrix3FromQuaternion(a2a8, (Vec3*)&u2f0);
                        for (int i = 0; i < 9; ++i) a2cc[i] = a2a8[i];
                        f2dc = f390; u2e0 = (unsigned short)(u2e0 | 6);
                        f2d8 = f38c; s2de = (short)(s2de + 2);
                        f2d4 = f388;
                        float* ap = &afbuf[2];
                        for (int k = 4; k != 0; --k) {
                            fStack_34c = ap[-2];
                            fStack_348 = ap[-1];
                            fStack_344 = ap[0];
                            FUN_0044d4f0((Vec3*)&fStack_34c);
                            f19 = (local_36c * (fStack_34c - fStack_358) +
                                   f18 * (fStack_348 - fStack_338)) +
                                  f17 * (fStack_344 - fStack_394);
                            fStack_34c = fStack_358 + ((fStack_34c - fStack_358) - local_36c * f19);
                            fStack_348 = fStack_338 + ((fStack_348 - fStack_338) - f18 * f19);
                            fStack_344 = fStack_394 + ((fStack_344 - fStack_394) - f17 * f19);
                            fStack_39c = (fStack_334 * (fStack_34c - fStack_358) +
                                          fStack_354 * (fStack_348 - fStack_338)) +
                                         fStack_350 * (fStack_344 - fStack_394);
                            fStack_398 = (fStack_318 * (fStack_34c - fStack_358) +
                                          fStack_368 * (fStack_348 - fStack_338)) +
                                         f20 * (fStack_344 - fStack_394);
                            if (fStack_314 < fStack_39c && fStack_39c < fStack_340) {
                                FUN_00722c60(&fStack_39c);
                            }
                            ap += 3;
                        }
                    }
                }
                piVar4 += 1;
            } while (piVar4 != piStack_308);
        }

        if (param_7 == 1) {
            void* gm = GetCurrentGameMode();
            local_36c = fStack_33c * 1.1f;
            float* psel = &fStack_378;
            if (gm == (void*)g_game_mode) {
                fStack_378 = fStack_3a0 * 0.1f;
                if (fStack_3a0 * 0.1f <= local_36c) psel = &local_36c;
                fStack_374 = *psel;
                fStack_378 = fStack_340 * 0.5f;
            } else {
                if (fStack_378 <= local_36c) psel = &local_36c;
                fStack_374 = *psel;
                fStack_378 = fStack_340 * 0.5f;
            }
LAB_00cbfd19:
            FUN_00722c60(&fStack_378);
        } else if (param_7 == 4) {
            fStack_374 = fStack_310 * 0.3f;
            fStack_378 = fStack_314 * 0.0f;
            goto LAB_00cbfd19;
        }
    }

    // ---- fit the arc and emit points ----
    puVar12 = puStack_284;
    if (puStack_284 != puStack_280) {
        int n = (int)(puStack_280 - puStack_284) >> 3;
        int i = 0;
        fStack_3a8 = 3.4028234e38f;
        if (0 < n) {
            do {
                fStack_30c = *(float*)(puVar12 + i * 8);
                FUN_00cb3f80(&fStack_314, &fStack_340, &fStack_30c, &fStack_378, &local_36c, dummy);
                if (fStack_378 < 0.0f) {
                    f17 = -(local_36c / (fStack_378 * 2.0f));
                    f17 = (f17 * fStack_378 + local_36c) * f17 + f18;
                    if (f17 < fStack_3a8) {
                        int j = 0;
                        do {
                            if ((*(float*)(puVar12 + j * 8) * fStack_378 + local_36c) *
                                *(float*)(puVar12 + j * 8) + f18 <
                                *(float*)(puVar12 + j * 8 + 4)) {
                                if (j < n) goto LAB_00cbfe57;
                                break;
                            }
                            j = j + 1;
                        } while (j < n);
                        fStack_3a4 = fStack_378;
                        fStack_39c = local_36c;
                        fStack_3a8 = f17;
                        fStack_3a0 = f18;
                    }
                }
LAB_00cbfe57:
                i = i + 1;
            } while (i < n);

            if (fStack_3a8 != 3.4028234e38f) {
                fStack_378 = 64.0f;
                local_36c = fStack_33c * 1.1f;
                float* psel = &fStack_378;
                if (64.0f <= fStack_33c * 1.1f) psel = &local_36c;
                if (*psel < fStack_3a8) {
                    fStack_30c = -(fStack_39c / (fStack_3a4 * 2.0f));
                    FUN_00cb3f80(&fStack_314, &fStack_340, &fStack_30c, &fStack_3a4, &fStack_39c,
                                 &fStack_3a0);
                }
                fStack_378 = (fStack_340 - fStack_314) * 0.03125f;
                fStack_3a8 = fStack_378 + fStack_314;
                {
                    Vec3 p;
                    p.x = (fStack_358 + fStack_334 * fStack_314) + fStack_318 * fStack_310;
                    p.y = (fStack_338 + fStack_354 * fStack_314) + fStack_368 * fStack_310;
                    p.z = (fStack_394 + fStack_350 * fStack_314) + f20 * fStack_310;
                    AppendPoint(param_3, p);
                }
                for (int k = 0x1f; k != 0; --k) {
                    f18 = (fStack_3a8 * fStack_3a4 + fStack_39c) * fStack_3a8 + fStack_3a0;
                    Vec3 p;
                    p.x = (fStack_358 + fStack_334 * fStack_3a8) + fStack_318 * f18;
                    p.y = (fStack_338 + fStack_354 * fStack_3a8) + fStack_368 * f18;
                    p.z = (fStack_394 + fStack_350 * fStack_3a8) + f20 * f18;
                    AppendPoint(param_3, p);
                    fStack_3a8 = fStack_3a8 + fStack_378;
                }
                {
                    Vec3 p;
                    p.x = (fStack_358 + fStack_334 * fStack_340) + fStack_318 * fStack_33c;
                    p.y = (fStack_338 + fStack_354 * fStack_340) + fStack_368 * fStack_33c;
                    p.z = (fStack_394 + fStack_350 * fStack_340) + f20 * fStack_33c;
                    AppendPoint(param_3, p);
                }
            }
        }
    }

    // ---- release the candidate list ----
    piVar4 = piStack_304;
    piVar1 = piStack_300;
    if (puVar12 != 0 && puVar12 != puStack_274) {
        operator_delete__(puVar12);
        piVar4 = piStack_304;
        piVar1 = piStack_300;
    }
    for (; piVar4 < piStack_300; piVar4 += 1) {
        (void)piVar1;
        if (*piVar4 != 0) {
            ((IObj*)*piVar4)->Release();
        }
    }
    if (piStack_304 != 0 && piStack_304[-1] != 0) {
        operator_delete__(piStack_304);
    }

LAB_00cc0229:
    if (param_3->begin == param_3->end) {
        eastl_copy_range(param_3->begin, param_3->end);
        Vec3 a, b, c;
        a.x = f384; a.y = f380; a.z = f37c;   // source
        b.x = fStack_330; b.y = fStack_32c; b.z = fStack_328; // target
        // If pB is null, or FUN_00b35bf0 fails, use the target as the end point.
        if (param_2 == 0 || FUN_00b35bf0(param_2, &a, &b, &c) == 0) {
            c = b;
        }
        FUN_00cbcc40(a.x, a.y, a.z, c.x, c.y, c.z, param_3);
    }

    // ---- apply spread / random perturbation along the path ----
    if (0.0f < param_8) {
        fVar14 = RandomDoubleUniform((void*)0);
        fStack_3ac = fVar14 * g_0169aa28;
        fVar14 = RandomDoubleUniform((void*)0);
        fVar15 = fStack_3ac;
        fStack_394 = param_8;
        fStack_368 = param_8 * 0.5f;
        {
            int i = 1;
            int off = 0xc;
            do {
                int base = (int)param_3->begin;
                fStack_364 = *(float*)(base + off);
                fStack_35c = *(float*)(base + 8 + off);
                fStack_360 = *(float*)(base + 4 + off);
                f388 = *(float*)(base + 0x14 + off) - fStack_35c;
                float* pf = (float*)(base + off);
                f390 = *(float*)(base + 0xc + off) - fStack_364;
                f38c = *(float*)(base + 0x10 + off) - fStack_360;
                f17 = 1.0f / sqrtf((f38c * f38c +
                                    (f388 * f388 + f390 * f390)) + 1e-8f);
                f20 = f388 * f17;
                f19 = f38c * f17;
                f17 = f17 * f390;
                fVar15 = sinf(fVar15 * 0.5f);
                f18 = fVar15;
                fVar15 = cosf(fVar15 * 0.5f);
                f21 = f19 * f18;
                f22 = f20 * f18;
                f18 = f18 * f17;
                f2e4 = fVar15;
                fStack_3a0 = 1.0f / sqrtf((fStack_364 * fStack_364 +
                                           (fStack_360 * fStack_360 + fStack_35c * fStack_35c)) + 1e-8f);
                fStack_324 = fStack_3a0 * fStack_364;
                fStack_320 = fStack_360 * fStack_3a0;
                fStack_31c = fStack_35c * fStack_3a0;
                fStack_348 = (f20 * fStack_324 - fStack_31c * f17) * fStack_394;
                fStack_34c = (fStack_31c * f19 - fStack_320 * f20) * fStack_394;
                fStack_3a4 = f18 * f18;
                fStack_344 = (fStack_320 * f17 - f19 * fStack_324) * fStack_394;
                fStack_39c = f2e4 * f21;
                fStack_370 = 1.0f - (f22 * f22 + fStack_3a4) * 2.0f;
                pf[0] = (((f21 * f18 - f2e4 * f22) * fStack_348 +
                          (fStack_39c + f22 * f18) * fStack_344) * 2.0f +
                         (1.0f - (f22 * f22 + f21 * f21) * 2.0f) * fStack_34c) + pf[0];
                pf[1] = (((f2e4 * f22 + f21 * f18) * fStack_34c +
                          (f22 * f21 - f2e4 * f18) * fStack_344) * 2.0f +
                         fStack_370 * fStack_348) + pf[1];
                pf[2] = (((f22 * f18 - fStack_39c) * fStack_34c +
                          (f2e4 * f18 + f22 * f21) * fStack_348) * 2.0f +
                         (1.0f - (f21 * f21 + fStack_3a4) * 2.0f) * fStack_344) + pf[2];
                fVar15 = RandomDoubleUniform((void*)0);
                fVar15 = (fVar15 + 1.0f) * 0.2f;
                if (0.5f <= fVar14) {
                    fVar15 = fStack_3ac - fVar15;
                    fStack_3ac = fVar15;
                    if (fVar15 < 0.0f) {
                        fStack_3ac = fStack_3ac + g_0169aa28;
                        goto LAB_00cc06b1;
                    }
                } else {
                    fVar15 = fVar15 + fStack_3ac;
                    fStack_3ac = fVar15;
                    if (g_0169aa28 < fVar15) {
                        fStack_3ac = fStack_3ac - g_0169aa28;
LAB_00cc06b1:
                        fVar15 = fStack_3ac;
                    }
                }
                if (i < 0x11) {
                    fStack_394 = fStack_368 + fStack_394;
                } else {
                    fStack_394 = fStack_394 - fStack_368;
                }
                off += 0xc;
                i = i + 1;
            } while (off < 0x174);
        }
    }
    return;
}
