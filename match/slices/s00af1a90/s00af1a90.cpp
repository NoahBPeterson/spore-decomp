// Slice s00af1a90 (batch big0, slice 12): single large SSE/x87 steering /
// collision-solve function FUN_00af1a90.
// Behavioural transcription of the Ghidra decompile (full path coverage).
// The prologue is `sub esp,0x10c` with no frame pointer and scalar SSE
// (movss/subss) plus x87 sqrtf, so the module is /O2 with /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

// --- masked callees (relocations): names from the PDB / slice symbols --------
extern float* normalized_safe(float* out, const float* v);                    // 0x449c20
extern char   FUN_004232c0(const float* a, const float* b);                   // 0x4232c0 Vector3Equal
extern void   FUN_00436ce0(float* out, const float* v);                       // 0x436ce0 Vector3_Normalize
extern float* FUN_00699800(float* out, const float* a, float r,
                           const float* b, const float* c);                   // 0x699800
extern void   FUN_00466320(void* self, float* out);                           // 0x466320
// 0x167ae24/28/2c is the constant 3-vector compared against; 0x167ae78/7c/80
// is a 3-float matrix/axis used by the edge solver.
extern float       DAT_0167ae24, DAT_0167ae28, DAT_0167ae2c;
extern const float DAT_0167ae78, DAT_0167ae7c, DAT_0167ae80;

#define OF(off) (*(float*)((char*)p + (off)))
#define OI(off) (*(int*)((char*)p + (off)))
#define OB(off) (*(unsigned char*)((char*)p + (off)))

// process one mesh sample through the 3x3 transform and keep the extremal
// point along the search direction (case 1 loop body).
#define PROC_SAMPLE(px, py, pz)                                                  \
    {                                                                            \
        float _x = (px), _y = (py), _z = (pz);                                   \
        fVar20 = (fVar13 * _y + fVar16 * _x) + fVar19 * _z;                      \
        fVar21 = (fVar15 * _y + fVar10 * _x) + fVar11 * _z;                      \
        float _r = (fVar12 * _y + fVar17 * _x) + fVar9 * _z;                     \
        fVar14 = (fVar20 * local_e0 + fVar21 * local_dc) + _r * local_d8;        \
        fVar20 = fVar20 - fVar14 * local_e0;                                     \
        fVar21 = fVar21 - local_dc * fVar14;                                     \
        if (0.0f < -(((local_fc - local_cc) * (fVar21 - local_c8) -              \
                       (fVar20 - local_cc) * (local_f8 - local_c8)) * param_4)) {\
            local_fc = fVar20;                                                   \
            local_f8 = fVar21;                                                   \
            local_f4 = _r - local_d8 * fVar14;                                   \
        }                                                                        \
    }

// winding tests (case 2): x = sample.x, y = sample.y
#define WTEST1(x, y)                                                             \
    (0.0f < -(((y - fVar13) * (local_f0 - fVar19) -                              \
               (local_ec - fVar13) * (x - fVar19)) * param_4))
#define WTEST2(x, y)                                                             \
    (0.0f < -(((y - fVar13) * (local_fc - fVar19) -                              \
               (x - fVar19) * (local_f8 - fVar13)) * param_4))

// @ 0x00af1a90
int FUN_00af1a90(float* param_1, float* param_2, float* param_3, float param_4,
                 float param_5, void* p)
{
    char  cVar2;
    float *pfVar3, *pfVar8;
    int   iVar1, iVar4, iVar5, iVar6, iVar7;
    float fVar9, fVar10, fVar11, fVar12, fVar13, fVar14, fVar15, fVar16,
          fVar17, fVar18, fVar19, fVar20, fVar21;
    float local_108, local_104, local_100;
    float local_fc, local_f8, local_f4, local_f0, local_ec, local_e8;
    int   local_e4;
    float local_e0, local_dc, local_d8, local_d4, local_d0, local_cc, local_c8;
    int   local_c4;
    float local_c0, local_bc, local_b4, local_b0, local_ac;
    float local_a8[3], local_9c[3], local_90[3], local_84[3], local_78[3], local_6c[3];

    switch (OI(0x24)) {
    case 0: {
        local_108 = OF(0x28) - param_1[0];
        local_104 = OF(0x2c) - param_1[1];
        local_100 = OF(0x30) - param_1[2];
        pfVar3 = (float*)((char*)p + 0x28);
        pfVar8 = normalized_safe(local_6c, &local_108);
        local_fc = pfVar8[0];
        local_f8 = pfVar8[1];
        local_f4 = pfVar8[2];
        pfVar8 = normalized_safe(local_a8, pfVar3);
        local_f0 = (pfVar8[2] * local_f8 - pfVar8[1] * local_f4) * param_4;
        local_ec = (pfVar8[0] * local_f4 - local_fc * pfVar8[2]) * param_4;
        local_e8 = (local_fc * pfVar8[1] - pfVar8[0] * local_f8) * param_4;
        pfVar8 = FUN_00699800(local_84, pfVar3, OF(0x54), param_1, &local_f0);
        param_3[0] = pfVar8[0];
        param_3[1] = pfVar8[1];
        param_3[2] = pfVar8[2];
        if (((param_3[0] == DAT_0167ae24) && (param_3[1] == DAT_0167ae28)) &&
            (param_3[2] == DAT_0167ae2c)) {
            fVar19 = OF(0x54);
            fVar13 = OF(0x2c);
            fVar16 = OF(0x30);
            param_3[0] = pfVar3[0] - local_fc * fVar19;
            param_3[1] = fVar13 - fVar19 * local_f8;
            param_3[2] = fVar16 - fVar19 * local_f4;
            cVar2 = FUN_004232c0(param_3, &DAT_0167ae24);
            if (cVar2 != 0)
                return 0;
        }
        fVar19 = param_1[2];
        fVar13 = param_1[1];
        fVar15 = param_3[2] - fVar19;
        fVar11 = param_3[1] - fVar13;
        fVar16 = param_3[0] - param_1[0];
        if ((fVar15 * fVar15 + fVar11 * fVar11) + fVar16 * fVar16 < 1.5258789e-05f) {
            fVar16 = OF(0x54);
            param_3[0] = local_f0 * fVar16 + param_1[0];
            param_3[1] = fVar16 * local_ec + fVar13;
            param_3[2] = fVar16 * local_e8 + fVar19;
        }
        if (1.5258789e-05f < param_5) {
            fVar19 = param_3[0];
            local_d4 = param_3[1];
            local_c0 = param_3[2];
            local_108 = fVar19 - pfVar3[0];
            local_104 = local_d4 - OF(0x2c);
            local_100 = local_c0 - OF(0x30);
            pfVar3 = normalized_safe(local_9c, &local_108);
            fVar13 = pfVar3[1];
            fVar16 = pfVar3[2];
            param_3[0] = pfVar3[0] * param_5 + fVar19;
            param_3[1] = local_d4 + fVar13 * param_5;
            param_3[2] = local_c0 + fVar16 * param_5;
            return 1;
        }
        break;
    }
    case 1: {
        pfVar3 = (float*)((char*)p + 0x28);
        FUN_00436ce0(&local_e0, pfVar3);
        local_c8 = param_1[1] - OF(0x2c);
        fVar19 = OF(0x48);
        fVar16 = (local_d8 * (param_1[2] - OF(0x30)) + local_dc * local_c8) +
                 (param_1[0] - pfVar3[0]) * local_e0;
        local_cc = (param_1[0] - pfVar3[0]) - local_e0 * fVar16;
        fVar13 = OF(0x4c);
        local_c8 = local_c8 - local_dc * fVar16;
        fVar16 = OF(0x50);
        local_108 = (OF(0x84) * fVar19 + OF(0x9c) * fVar16) + OF(0x90) * fVar13;
        local_104 = (fVar16 * OF(0xa0) + fVar13 * OF(0x94)) + OF(0x88) * fVar19;
        local_100 = (OF(0x8c) * fVar19 + fVar16 * OF(0xa4)) + fVar13 * OF(0x98);
        fVar19 = (local_108 * local_e0 + local_104 * local_dc) + local_100 * local_d8;
        local_108 = local_108 - fVar19 * local_e0;
        local_104 = local_104 - local_dc * fVar19;
        local_100 = local_100 - local_d8 * fVar19;
        float m[24];
        FUN_00466320((char*)p + 0x58, m);
        local_fc = local_108;
        local_f8 = local_104;
        local_f4 = local_100;
        fVar19 = OF(0x9c);
        fVar13 = OF(0x90);
        fVar16 = OF(0x84);
        fVar11 = OF(0xa0);
        fVar15 = OF(0x94);
        fVar10 = OF(0x88);
        fVar9 = OF(0xa4);
        fVar12 = OF(0x98);
        fVar17 = OF(0x8c);
        pfVar8 = m + 1;
        iVar7 = 2;
        do {
            PROC_SAMPLE(pfVar8[-1], pfVar8[0], pfVar8[1]);
            PROC_SAMPLE(pfVar8[2], pfVar8[3], pfVar8[4]);
            PROC_SAMPLE(pfVar8[5], pfVar8[6], pfVar8[7]);
            PROC_SAMPLE(pfVar8[8], pfVar8[9], pfVar8[10]);
            pfVar8 += 12;
            iVar7 = iVar7 - 1;
        } while (iVar7 != 0);
        local_fc = pfVar3[0] + local_fc;
        local_f8 = OF(0x2c) + local_f8;
        local_f4 = OF(0x30) + local_f4;
        param_3[0] = local_fc;
        param_3[1] = local_f8;
        param_3[2] = local_f4;
        if (1.5258789e-05f < param_5) {
            fVar9 = param_1[0] - pfVar3[0];
            fVar11 = param_1[2] - OF(0x30);
            fVar16 = param_1[1] - OF(0x2c);
            fVar12 = local_fc - pfVar3[0];
            fVar10 = local_f4 - OF(0x30);
            fVar15 = local_f8 - OF(0x2c);
            fVar19 = 1.0f / sqrtf((fVar16 * fVar16 + (fVar11 * fVar11 + fVar9 * fVar9)) + 1e-08f);
            fVar13 = 1.0f / sqrtf((fVar15 * fVar15 + (fVar10 * fVar10 + fVar12 * fVar12)) + 1e-08f);
            fVar9 = fVar13 * fVar12 + fVar19 * fVar9;
            fVar11 = fVar10 * fVar13 + fVar11 * fVar19;
            fVar13 = fVar15 * fVar13 + fVar16 * fVar19;
            fVar19 = 1.0f / sqrtf((fVar13 * fVar13 + (fVar11 * fVar11 + fVar9 * fVar9)) + 1e-08f);
            param_3[1] = (fVar13 * fVar19) * param_5 + local_f8;
            param_3[2] = (fVar11 * fVar19) * param_5 + local_f4;
            param_3[0] = (fVar19 * fVar9) * param_5 + local_fc;
            return 1;
        }
        break;
    }
    case 2: {
        float* base = (float*)(size_t)OI(0xb8);
        int    cnt  = OI(0xb4);
        fVar19 = OF(0xbc);
        local_f0 = OF(0x48);
        fVar13 = OF(0xc0);
        fVar16 = OF(0xc4);
        local_ec = OF(0x4c);
        local_e8 = OF(0x50);
        local_e4 = -1;
        if (((fVar19 == local_f0) && (fVar13 == local_ec)) && (fVar16 == local_e8)) {
            iVar5 = cnt;
            fVar11 = 3.402823466e+38f;
            iVar7 = 0;
            if (3 < iVar5) {
                pfVar3 = base + 3;
                iVar4 = (iVar5 - 4U >> 2) + 1;
                iVar7 = iVar4 * 4;
                do {
                    fVar15 = ((pfVar3[-3] - fVar19) * (pfVar3[-3] - fVar19) +
                              (pfVar3[-1] - fVar16) * (pfVar3[-1] - fVar16)) +
                             (pfVar3[-2] - fVar13) * (pfVar3[-2] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[-2];
                        local_f0 = pfVar3[-3];
                        local_e8 = pfVar3[-1];
                        fVar11 = fVar15;
                    }
                    fVar15 = ((pfVar3[0] - fVar19) * (pfVar3[0] - fVar19) +
                              (pfVar3[2] - fVar16) * (pfVar3[2] - fVar16)) +
                             (pfVar3[1] - fVar13) * (pfVar3[1] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[1];
                        local_f0 = pfVar3[0];
                        local_e8 = pfVar3[2];
                        fVar11 = fVar15;
                    }
                    fVar15 = ((pfVar3[3] - fVar19) * (pfVar3[3] - fVar19) +
                              (pfVar3[5] - fVar16) * (pfVar3[5] - fVar16)) +
                             (pfVar3[4] - fVar13) * (pfVar3[4] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[4];
                        local_f0 = pfVar3[3];
                        local_e8 = pfVar3[5];
                        fVar11 = fVar15;
                    }
                    fVar15 = ((pfVar3[6] - fVar19) * (pfVar3[6] - fVar19) +
                              (pfVar3[8] - fVar16) * (pfVar3[8] - fVar16)) +
                             (pfVar3[7] - fVar13) * (pfVar3[7] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[7];
                        local_f0 = pfVar3[6];
                        local_e8 = pfVar3[8];
                        fVar11 = fVar15;
                    }
                    pfVar3 += 12;
                    iVar4 = iVar4 - 1;
                } while (iVar4 != 0);
            }
            if (iVar7 < iVar5) {
                iVar5 = iVar5 - iVar7;
                pfVar3 = base + iVar7 * 3;
                do {
                    fVar15 = ((pfVar3[0] - fVar19) * (pfVar3[0] - fVar19) +
                              (pfVar3[2] - fVar16) * (pfVar3[2] - fVar16)) +
                             (pfVar3[1] - fVar13) * (pfVar3[1] - fVar13);
                    if (fVar15 < fVar11) {
                        local_ec = pfVar3[1];
                        local_f0 = pfVar3[0];
                        local_e8 = pfVar3[2];
                        fVar11 = fVar15;
                    }
                    pfVar3 += 3;
                    iVar5 = iVar5 - 1;
                } while (iVar5 != 0);
            }
        }
        iVar7 = 0;
        fVar16 = local_f0;
        if (3 < cnt) {
            pfVar3 = base + 3;
            iVar5 = 2;
            pfVar8 = base + 7;
            do {
                if (WTEST1(pfVar3[-3], pfVar3[-2])) {
                    fVar16 = pfVar3[-3];
                    local_ec = pfVar3[-2];
                    local_e8 = pfVar3[-1];
                    local_f0 = fVar16;
                    local_e4 = iVar7;
                }
                if (WTEST1(pfVar3[0], pfVar3[1])) {
                    fVar16 = pfVar3[0];
                    local_ec = pfVar3[1];
                    local_e8 = pfVar3[2];
                    local_e4 = iVar5 - 1;
                    local_f0 = fVar16;
                }
                if (WTEST1(pfVar3[3], pfVar3[4])) {
                    fVar16 = pfVar3[3];
                    local_ec = pfVar3[4];
                    local_e8 = pfVar3[5];
                    local_f0 = fVar16;
                    local_e4 = iVar5;
                }
                if (WTEST1(pfVar3[6], pfVar3[7])) {
                    fVar16 = pfVar3[6];
                    local_ec = pfVar3[7];
                    local_e8 = pfVar3[8];
                    local_e4 = iVar5 + 1;
                    local_f0 = fVar16;
                }
                (void)pfVar8;
                iVar7 = iVar7 + 4;
                pfVar3 += 12;
                pfVar8 += 12;
                iVar5 = iVar5 + 4;
            } while (iVar7 < cnt - 3);
        }
        iVar5 = cnt;
        if (iVar7 < iVar5) {
            pfVar3 = base + iVar7 * 3;
            do {
                if (WTEST1(pfVar3[0], pfVar3[1])) {
                    fVar16 = pfVar3[0];
                    local_ec = pfVar3[1];
                    local_e8 = pfVar3[2];
                    local_e4 = iVar7;
                    local_f0 = fVar16;
                }
                iVar7 = iVar7 + 1;
                pfVar3 += 3;
            } while (iVar7 < iVar5);
        }
        if (local_e4 == -1) {
            local_fc = OF(0xa8);
            local_f8 = OF(0xac);
            iVar7 = 0;
            if (3 < iVar5) {
                pfVar3 = base + 3;
                iVar5 = 2;
                pfVar8 = base + 7;
                do {
                    if (WTEST2(pfVar3[-3], pfVar3[-2])) {
                        local_fc = pfVar3[-3];
                        local_f8 = pfVar3[-2];
                        local_f4 = pfVar3[-1];
                        local_e4 = iVar7;
                    }
                    if (WTEST2(pfVar3[0], pfVar3[1])) {
                        local_fc = pfVar3[0];
                        local_f8 = pfVar3[1];
                        local_f4 = pfVar3[2];
                        local_e4 = iVar5 - 1;
                    }
                    if (WTEST2(pfVar3[3], pfVar3[4])) {
                        local_fc = pfVar3[3];
                        local_f8 = pfVar3[4];
                        local_f4 = pfVar3[5];
                        local_e4 = iVar5;
                    }
                    if (WTEST2(pfVar3[6], pfVar3[7])) {
                        local_fc = pfVar3[6];
                        local_f8 = pfVar3[7];
                        local_f4 = pfVar3[8];
                        local_e4 = iVar5 + 1;
                    }
                    (void)pfVar8;
                    iVar7 = iVar7 + 4;
                    pfVar3 += 12;
                    pfVar8 += 12;
                    iVar5 = iVar5 + 4;
                } while (iVar7 < cnt - 3);
            }
            if (iVar7 < cnt) {
                pfVar3 = base + iVar7 * 3;
                do {
                    if (WTEST2(pfVar3[0], pfVar3[1])) {
                        local_fc = pfVar3[0];
                        local_f8 = pfVar3[1];
                        local_f4 = pfVar3[2];
                        local_e4 = iVar7;
                    }
                    iVar7 = iVar7 + 1;
                    pfVar3 += 3;
                } while (iVar7 < cnt);
            }
            if (local_e4 == -1)
                return 0;
        }
        param_3[0] = fVar16;
        param_3[1] = local_ec;
        param_3[2] = local_e8;
        iVar4 = (local_e4 - 1 + cnt) % cnt;
        local_d0 = 0.0f;
        float* pcur = base + local_e4 * 3;
        pfVar3 = base + iVar4 * 3;
        fVar19 = pcur[0] - pfVar3[0];
        fVar16 = pcur[2] - pfVar3[2];
        fVar13 = pcur[1] - pfVar3[1];
        fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        for (; (fVar19 < 1.5258789e-05f && ((int)local_d0 < cnt));
             local_d0 = (float)((int)local_d0 + 1)) {
            iVar4 = (iVar4 - 1 + cnt) % cnt;
            pfVar3 = base + iVar4 * 3;
            fVar19 = pcur[0] - pfVar3[0];
            fVar16 = pcur[2] - pfVar3[2];
            fVar13 = pcur[1] - pfVar3[1];
            fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        }
        iVar6 = (local_e4 + 1) % cnt;
        local_d0 = 0.0f;
        pfVar3 = base + iVar6 * 3;
        fVar19 = pcur[0] - pfVar3[0];
        fVar16 = pcur[2] - pfVar3[2];
        fVar13 = pcur[1] - pfVar3[1];
        fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        for (; (fVar19 < 1.5258789e-05f && ((int)local_d0 < cnt));
             local_d0 = (float)((int)local_d0 + 1)) {
            iVar6 = (iVar6 + 1) % cnt;
            pfVar3 = base + iVar6 * 3;
            fVar19 = pcur[0] - pfVar3[0];
            fVar16 = pcur[2] - pfVar3[2];
            fVar13 = pcur[1] - pfVar3[1];
            fVar19 = (fVar19 * fVar19 + fVar16 * fVar16) + fVar13 * fVar13;
        }
        fVar19 = pcur[0];
        fVar13 = pcur[1];
        fVar16 = pcur[2];
        local_bc = OF(0x54);
        pfVar3 = pcur;
        float* pa = base + iVar4 * 3;
        fVar11 = pa[0];
        local_d4 = pa[1];
        local_b0 = pa[2];
        float* pb = base + iVar6 * 3;
        local_c0 = pb[1];
        local_ac = pb[0];
        local_d0 = pb[2];
        local_b4 = local_ac - fVar19;
        fVar15 = local_bc + param_5;
        if ((local_b4 * (fVar11 - fVar19) + (local_d0 - fVar16) * (local_b0 - fVar16)) +
                (local_c0 - fVar13) * (local_d4 - fVar13) <= 0.0f) {
            fVar13 = pcur[1] - local_d4;
            local_b0 = pcur[2] - local_b0;
            fVar10 = fVar13 * DAT_0167ae80 - local_b0 * DAT_0167ae7c;
            fVar13 = (fVar19 - fVar11) * DAT_0167ae7c - fVar13 * DAT_0167ae78;
            fVar9 = local_b0 * DAT_0167ae78 - (fVar19 - fVar11) * DAT_0167ae80;
            fVar13 = 1.0f / sqrtf((fVar9 * fVar9 + (fVar13 * fVar13 + fVar10 * fVar10)) + 1e-08f);
            local_d0 = local_d0 - pcur[2];
            fVar16 = local_c0 - pcur[1];
            fVar17 = fVar16 * DAT_0167ae80 - local_d0 * DAT_0167ae7c;
            fVar16 = local_b4 * DAT_0167ae7c - fVar16 * DAT_0167ae78;
            fVar12 = local_d0 * DAT_0167ae78 - local_b4 * DAT_0167ae80;
            fVar16 = 1.0f / sqrtf((fVar12 * fVar12 + (fVar16 * fVar16 + fVar17 * fVar17)) + 1e-08f);
            fVar18 = fVar15 * (fVar13 * fVar10);
            fVar10 = (fVar16 * fVar17) * fVar15;
            fVar17 = (fVar9 * fVar13) * fVar15;
            fVar15 = (fVar12 * fVar16) * fVar15;
            fVar20 = fVar10 + fVar19;
            fVar12 = fVar15 + pcur[1];
            fVar9 = fVar17 + pcur[1];
            fVar15 = (fVar15 + local_c0) - fVar12;
            fVar13 = (fVar10 + local_ac) - fVar20;
            fVar11 = fVar18 + fVar11;
            fVar10 = (fVar18 + fVar19) - fVar11;
            local_d4 = fVar17 + local_d4;
            fVar21 = fVar9 - local_d4;
            fVar16 = fVar10 * fVar15 - fVar21 * fVar13;
            fVar12 = local_d4 - fVar12;
            fVar20 = fVar11 - fVar20;
            fVar13 = fVar12 * fVar13 - fVar20 * fVar15;
            if (fVar16 <= 1.5258789e-05f) {
                if ((fVar13 == 0.0f) && (fVar12 * fVar10 - fVar20 * fVar21 == 0.0f))
                    return 0;
                param_3[0] = (fVar18 + fVar19) + fVar18;
                param_3[1] = fVar9 + fVar17;
                param_3[2] = 0.0f;
            } else {
                fVar13 = (1.0f / fVar16) * fVar13;
                param_3[0] = fVar13 * fVar10 + fVar11;
                param_3[1] = fVar13 * fVar21 + local_d4;
                param_3[2] = 0.0f;
            }
        } else {
            local_d8 = param_1[2] - OF(0x7c);
            fVar19 = param_1[0] - OF(0x74);
            fVar13 = param_1[1] - OF(0x78);
            if (OF(0x80) != 1.0f) {
                fVar16 = 1.0f / OF(0x80);
                fVar19 = fVar16 * fVar19;
                fVar13 = fVar13 * fVar16;
                local_d8 = local_d8 * fVar16;
            }
            local_e0 = fVar19;
            local_dc = fVar13;
            if ((OB(0x70) & 2) != 0) {
                local_e0 = (OF(0x8c) * local_d8 + OF(0x88) * fVar13) + fVar19 * OF(0x84);
                local_dc = (OF(0x98) * local_d8 + OF(0x94) * fVar13) + OF(0x90) * fVar19;
                local_d8 = (OF(0xa4) * local_d8 + OF(0xa0) * fVar13) + OF(0x9c) * fVar19;
            }
            fVar19 = pcur[0] - local_e0;
            local_104 = pcur[1] - local_dc;
            local_100 = pcur[2] - local_d8;
            local_108 = 1.0f / sqrtf((fVar19 * fVar19 +
                                      (local_104 * local_104 + local_100 * local_100)) + 1e-08f);
            local_100 = local_100 * local_108;
            local_104 = local_104 * local_108;
            local_108 = local_108 * fVar19;
            local_f0 = (local_104 * DAT_0167ae80 - local_100 * DAT_0167ae7c) * param_4;
            local_ec = (local_100 * DAT_0167ae78 - local_108 * DAT_0167ae80) * param_4;
            local_e8 = (local_108 * DAT_0167ae7c - local_104 * DAT_0167ae78) * param_4;
            pfVar8 = FUN_00699800(local_90, pcur, local_bc, &local_e0, &local_f0);
            param_3[0] = pfVar8[0];
            param_3[1] = pfVar8[1];
            param_3[2] = pfVar8[2];
            if (((param_3[0] == DAT_0167ae24) && (param_3[1] == DAT_0167ae28)) &&
                (param_3[2] == DAT_0167ae2c)) {
                fVar19 = OF(0x54) * param_5;
                fVar13 = pcur[0] - local_108 * fVar19;
                fVar16 = pcur[1] - local_104 * fVar19;
                fVar19 = pcur[2] - local_100 * fVar19;
                param_3[0] = fVar13;
                param_3[1] = fVar16;
                param_3[2] = fVar19;
                if (((fVar13 == DAT_0167ae24) && (fVar16 == DAT_0167ae28)) &&
                    (fVar19 == DAT_0167ae2c))
                    return 0;
            }
            if (((param_3[0] - local_e0) * (param_3[0] - local_e0) +
                 (param_3[2] - local_d8) * (param_3[2] - local_d8)) +
                    (param_3[1] - local_dc) * (param_3[1] - local_dc) < 1.5258789e-05f) {
                fVar19 = OF(0x54);
                param_3[0] = local_f0 * fVar19 + local_e0;
                param_3[1] = local_ec * fVar19 + local_dc;
                param_3[2] = local_e8 * fVar19 + local_d8;
            }
            if (1.5258789e-05f < param_5) {
                fVar11 = param_3[2] - pcur[2];
                fVar13 = param_3[0] - pcur[0];
                fVar16 = param_3[1] - pcur[1];
                fVar19 = 1.0f / sqrtf((fVar16 * fVar16 + (fVar11 * fVar11 + fVar13 * fVar13)) + 1e-08f);
                param_3[0] = (fVar19 * fVar13) * param_5 + param_3[0];
                param_3[1] = (fVar19 * fVar16) * param_5 + param_3[1];
                param_3[2] = (fVar19 * fVar11) * param_5 + param_3[2];
            }
            fVar13 = param_2[2] - OF(0x7c);
            fVar19 = param_2[0] - OF(0x74);
            local_c8 = param_2[1] - OF(0x78);
            if (OF(0x80) != 1.0f) {
                fVar16 = 1.0f / OF(0x80);
                fVar19 = fVar16 * fVar19;
                local_c8 = fVar16 * local_c8;
                fVar13 = fVar16 * fVar13;
            }
            local_cc = fVar19;
            if ((OB(0x70) & 2) != 0) {
                local_cc = (OF(0x8c) * fVar13 + OF(0x88) * local_c8) + fVar19 * OF(0x84);
                local_c8 = (OF(0x98) * fVar13 + OF(0x94) * local_c8) + fVar19 * OF(0x90);
            }
            local_108 = pcur[0] - local_cc;
            local_104 = pcur[1] - local_c8;
            local_100 = pcur[2];
            param_4 = -param_4;
            local_c4 = 0;
            fVar19 = 1.0f / sqrtf((local_108 * local_108 +
                                   (local_104 * local_104 + local_100 * local_100)) + 1e-08f);
            local_f0 = param_4 * ((local_104 * fVar19) * DAT_0167ae80 -
                                  (local_100 * fVar19) * DAT_0167ae7c);
            local_ec = ((local_100 * fVar19) * DAT_0167ae78 -
                        DAT_0167ae80 * (fVar19 * local_108)) * param_4;
            local_e8 = (DAT_0167ae7c * (fVar19 * local_108) -
                        (local_104 * fVar19) * DAT_0167ae78) * param_4;
            pfVar3 = FUN_00699800(local_78, pcur, OF(0x54), &local_cc, &local_f0);
            if (((pfVar3[0] != DAT_0167ae24) || (pfVar3[1] != DAT_0167ae28)) ||
                (pfVar3[2] != DAT_0167ae2c)) {
                fVar19 = param_3[0];
                fVar10 = fVar19 - pfVar3[0];
                fVar13 = param_3[1];
                fVar11 = fVar13 - pfVar3[1];
                fVar16 = param_3[2];
                fVar15 = fVar16 - pfVar3[2];
                local_e0 = fVar19 - local_e0;
                local_d8 = fVar16 - local_d8;
                local_dc = fVar13 - local_dc;
                fVar11 = sqrtf(fVar10 * fVar10 + (fVar11 * fVar11 + fVar15 * fVar15)) * 0.5f;
                fVar15 = 1.0f / sqrtf((local_dc * local_dc +
                                       (local_d8 * local_d8 + local_e0 * local_e0)) + 1e-08f);
                param_3[0] = fVar19 + fVar11 * (fVar15 * local_e0);
                param_3[1] = (local_dc * fVar15) * fVar11 + fVar13;
                param_3[2] = (local_d8 * fVar15) * fVar11 + fVar16;
            }
        }
        if ((OB(0x70) & 2) != 0) {
            fVar19 = param_3[2];
            fVar13 = param_3[1];
            fVar16 = param_3[0];
            fVar11 = OF(0x94);
            fVar15 = OF(0xa0);
            fVar10 = OF(0x88);
            fVar9 = OF(0xa4);
            fVar12 = OF(0x98);
            fVar17 = OF(0x8c);
            param_3[0] = (OF(0x9c) * fVar19 + OF(0x90) * fVar13) + fVar16 * OF(0x84);
            param_3[1] = (fVar15 * fVar19 + fVar11 * fVar13) + fVar10 * fVar16;
            param_3[2] = (fVar9 * fVar19 + fVar12 * fVar13) + fVar17 * fVar16;
        }
        fVar19 = OF(0x80);
        fVar13 = param_3[1];
        fVar16 = param_3[2];
        param_3[0] = fVar19 * param_3[0];
        param_3[1] = fVar19 * fVar13;
        param_3[2] = fVar19 * fVar16;
        fVar11 = OF(0x78);
        fVar15 = OF(0x7c);
        param_3[0] = OF(0x74) + param_3[0];
        param_3[1] = fVar11 + fVar19 * fVar13;
        param_3[2] = fVar15 + fVar19 * fVar16;
        return 1;
    }
    case 3: {
        if (param_4 <= 0.0f) {
            fVar19 = OF(0xd8);
            fVar13 = OF(0xdc);
            fVar16 = OF(0xe0);
        } else {
            fVar19 = OF(0xcc);
            fVar13 = OF(0xd0);
            fVar16 = OF(0xd4);
        }
        fVar19 = fVar19 - OF(0x48);
        fVar16 = fVar16 - OF(0x50);
        fVar13 = fVar13 - OF(0x4c);
        fVar11 = sqrtf(fVar13 * fVar13 + (fVar16 * fVar16 + fVar19 * fVar19));
        fVar10 = 1.0f / (fVar11 + 1.5258789e-05f);
        param_5 = (OF(0x54) + fVar11) + param_5;
        fVar11 = OF(0x48);
        fVar15 = OF(0x50);
        param_3[1] = OF(0x4c) + (fVar13 * fVar10) * param_5;
        param_3[2] = fVar15 + (fVar16 * fVar10) * param_5;
        param_3[0] = (fVar10 * fVar19) * param_5 + fVar11;
        break;
    }
    }
    return 1;
}
