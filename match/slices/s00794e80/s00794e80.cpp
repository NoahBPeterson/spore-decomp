// SP::RotateZHToSHAdd (non-template) -- zonal-to-spherical-harmonics rotation
// for the ambient-lighting pipeline. 4138 bytes of hand-vectorized (SSE + x87)
// code generated from a template expansion; reproduced here verbatim from the
// Ghidra decompilation so every path and store of the original is present.
//
// The float constants live in the module's read-only data section (masked as
// relocations when diffing), so they are modelled as extern globals.

extern const float DAT_01634104;
extern const float DAT_016340dc;
extern const float DAT_01634078;
extern const float _DAT_016340cc;
extern const float DAT_016341e0;
extern const float DAT_016341b0;
extern const float DAT_01634150;
extern const float DAT_016340b0;
extern const float DAT_016340fc;
extern const float _DAT_0163409c;
extern const float DAT_016341dc;
extern const float DAT_016340d4;
extern const float DAT_01634130;
extern const float DAT_016340e8;
extern const float DAT_01634074;
extern const float DAT_016340ec;
extern const float DAT_016340f8;
extern const float _DAT_01634134;
extern const float _DAT_0163410c;
extern const float _DAT_01634168;
extern const float _DAT_016340e4;
extern const float _DAT_016340a8;
extern const float _DAT_01634064;
extern const float _DAT_0163405c;
extern const float _DAT_0163407c;

namespace SP
{
// Force one intermediate through single-precision memory, matching an SSE mulss/mulps
// rounding step.  The original is hand-vectorised: every product is rounded to float
// before the next operation, so a tiny product underflows to a signed zero there instead
// of surviving in x87 extended precision until the final store (which flips the sign of a
// zero result under /O2's x87 codegen).
static __forceinline float R32(float x)
{
    volatile float t = x;
    return t;
}

// @ 0x00794e80
float *RotateZHToSHAdd(float *param_1, int param_2, float *param_3, float *param_4, float *param_5)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float *pfVar7;
    int iVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float local_114[16];
    float local_d4[52];

    fVar3 = *param_3;
    fVar4 = param_3[1];
    fVar5 = param_3[2];
    fVar6 = param_3[3];
    fVar11 = *param_4;
    *param_5 = fVar11 * fVar3 + *param_5;
    param_5[1] = fVar11 * fVar4 + param_5[1];
    param_5[2] = fVar11 * fVar5 + param_5[2];
    param_5[3] = fVar11 * fVar6 + param_5[3];
    if (param_2 < 2)
        return param_5;
    if (1 < param_2) {
        fVar11 = param_4[1];
        fVar9 = param_1[1];
        fVar1 = param_1[2];
        fVar2 = *param_1;
        fVar10 = R32(fVar11 * fVar9);
        param_5[4] = R32(fVar10 * fVar3) + param_5[4];
        param_5[5] = R32(fVar10 * fVar4) + param_5[5];
        param_5[6] = R32(fVar10 * fVar5) + param_5[6];
        param_5[7] = R32(fVar10 * fVar6) + param_5[7];
        fVar10 = R32(fVar11 * fVar1);
        fVar11 = R32(fVar11 * fVar2);
        param_5[8] = R32(fVar10 * fVar3) + param_5[8];
        param_5[9] = R32(fVar10 * fVar4) + param_5[9];
        param_5[10] = R32(fVar10 * fVar5) + param_5[10];
        param_5[0xb] = R32(fVar10 * fVar6) + param_5[0xb];
        param_5[0xc] = R32(fVar11 * fVar3) + param_5[0xc];
        param_5[0xd] = R32(fVar11 * fVar4) + param_5[0xd];
        param_5[0xe] = R32(fVar11 * fVar5) + param_5[0xe];
        param_5[0xf] = R32(fVar11 * fVar6) + param_5[0xf];
        if (param_2 < 3)
            return param_5 + 4;
        if (2 < param_2) {
            local_114[0] = ((fVar2 * fVar9) * 2.0) * DAT_01634104;
            local_114[1] = ((fVar1 * fVar9) * 2.0) * DAT_01634104;
            local_114[2] = fVar1 * fVar1 - (fVar9 * fVar9 + fVar2 * fVar2) * DAT_016340dc;
            local_114[4] = (fVar2 * fVar2 - fVar9 * fVar9) * DAT_01634104;
            fVar11 = param_4[2];
            local_114[3] = ((fVar2 * fVar1) * 2.0) * DAT_01634104;
            iVar8 = 0;
            pfVar7 = param_5 + 0x10;
            do {
                fVar10 = R32(local_114[iVar8] * fVar11);
                iVar8 = iVar8 + 1;
                *pfVar7 = fVar10 * fVar3 + *pfVar7;
                pfVar7[1] = fVar10 * fVar4 + pfVar7[1];
                pfVar7[2] = fVar10 * fVar5 + pfVar7[2];
                pfVar7[3] = fVar10 * fVar6 + pfVar7[3];
                pfVar7 = pfVar7 + 4;
            } while (iVar8 < 5);
            if (param_2 < 4)
                return param_5 + 0x10;
            if (3 < param_2) {
                local_d4[0] = (local_114[4] * fVar9 + local_114[0] * fVar2) * DAT_01634078;
                local_d4[1] = ((local_114[1] * fVar2 + local_114[0] * fVar1) + local_114[3] * fVar9) *
                              _DAT_016340cc;
                local_d4[2] = ((DAT_016341e0 * local_114[1]) * fVar1 -
                              (local_114[0] * fVar2 - local_114[4] * fVar9) * DAT_016341b0) +
                              (DAT_01634150 * local_114[2]) * fVar9;
                local_d4[3] = local_114[2] * fVar1 -
                              (local_114[1] * fVar9 + local_114[3] * fVar2) * DAT_016340b0;
                local_d4[4] = ((DAT_01634150 * local_114[2]) * fVar2 -
                              (local_114[0] * fVar9 + local_114[4] * fVar2) * DAT_016341b0) +
                              (DAT_016341e0 * local_114[3]) * fVar1;
                local_d4[6] = (local_114[4] * fVar2 - local_114[0] * fVar9) * DAT_01634078;
                local_d4[5] = ((local_114[4] * fVar1 + local_114[3] * fVar2) - local_114[1] * fVar9) *
                              _DAT_016340cc;
                fVar11 = param_4[3];
                iVar8 = 0;
                pfVar7 = param_5 + 0x24;
                do {
                    fVar10 = R32(local_d4[iVar8] * fVar11);
                    iVar8 = iVar8 + 1;
                    *pfVar7 = fVar10 * fVar3;
                    pfVar7[1] = fVar10 * fVar4;
                    pfVar7[2] = fVar10 * fVar5;
                    pfVar7[3] = fVar10 * fVar6;
                    pfVar7 = pfVar7 + 4;
                } while (iVar8 < 7);
                if (param_2 < 5)
                    return param_5 + 0x24;
                if (4 < param_2) {
                    local_114[0] = (local_d4[6] * fVar9 + local_d4[0] * fVar2) * DAT_016340fc;
                    local_114[1] = (local_d4[5] * fVar9 + local_d4[1] * fVar2) * _DAT_0163409c +
                                   (DAT_016341dc * local_d4[0]) * fVar1;
                    local_114[2] = ((local_d4[2] * fVar2 + local_d4[4] * fVar9) * DAT_016340d4 -
                                   (local_d4[0] * fVar2 - local_d4[6] * fVar9) * DAT_01634130) +
                                   (DAT_01634104 * local_d4[1]) * fVar1;
                    local_114[3] = ((DAT_016340e8 * local_d4[2]) * fVar1 -
                                   (local_d4[1] * fVar2 - local_d4[5] * fVar9) * DAT_01634074) +
                                   (DAT_016340ec * local_d4[3]) * fVar9;
                    local_114[4] = local_d4[3] * fVar1 -
                                   (local_d4[2] * fVar9 + local_d4[4] * fVar2) * DAT_016340f8;
                    local_114[5] = ((DAT_016340ec * local_d4[3]) * fVar2 -
                                   (local_d4[1] * fVar9 + local_d4[5] * fVar2) * DAT_01634074) +
                                   (DAT_016340e8 * local_d4[4]) * fVar1;
                    local_114[6] = ((local_d4[4] * fVar2 - local_d4[2] * fVar9) * DAT_016340d4 -
                                   (local_d4[0] * fVar9 + local_d4[6] * fVar2) * DAT_01634130) +
                                   (DAT_01634104 * local_d4[5]) * fVar1;
                    fVar11 = param_4[4];
                    local_114[8] = (local_d4[6] * fVar2 - local_d4[0] * fVar9) * DAT_016340fc;
                    local_114[7] = (local_d4[5] * fVar2 - local_d4[1] * fVar9) * _DAT_0163409c +
                                   (DAT_016341dc * local_d4[6]) * fVar1;
                    iVar8 = 0;
                    pfVar7 = param_5 + 0x40;
                    do {
                        fVar10 = R32(local_114[iVar8] * fVar11);
                        iVar8 = iVar8 + 1;
                        *pfVar7 = fVar10 * fVar3;
                        pfVar7[1] = fVar10 * fVar4;
                        pfVar7[2] = fVar10 * fVar5;
                        pfVar7[3] = fVar10 * fVar6;
                        pfVar7 = pfVar7 + 4;
                    } while (iVar8 < 9);
                    if (param_2 < 6)
                        return param_5 + 0x40;
                    if (5 < param_2) {
                        local_d4[0] = (local_114[8] * fVar9 + local_114[0] * fVar2) * 0.94868329805051377;
                        local_d4[1] = (fVar1 * local_114[0]) * 0.6 +
                                      (local_114[7] * fVar9 + local_114[1] * fVar2) * _DAT_01634134;
                        local_d4[2] = (local_114[1] * fVar1) * 0.8 +
                                      ((local_114[6] * fVar9 + local_114[2] * fVar2) * _DAT_0163410c -
                                      (local_114[0] * fVar2 - local_114[8] * fVar9) * _DAT_01634168);
                        local_d4[3] = (local_114[2] * fVar1) * 0.91651513899116799 +
                                      ((local_114[5] * fVar9 + local_114[3] * fVar2) * _DAT_016340e4 -
                                      (local_114[1] * fVar2 - local_114[7] * fVar9) * _DAT_016340a8);
                        local_d4[4] = (local_114[3] * fVar1) * 0.97979589711327120 +
                                      ((local_114[4] * _DAT_01634064) * fVar9 -
                                      (local_114[2] * fVar2 - local_114[6] * fVar9) * _DAT_0163405c);
                        local_d4[5] = local_114[4] * fVar1 -
                                      (local_114[3] * fVar9 + local_114[5] * fVar2) * 0.63245553203367588;
                        local_d4[6] = (local_114[5] * fVar1) * 0.97979589711327120 +
                                      ((local_114[4] * _DAT_01634064) * fVar2 -
                                      (local_114[2] * fVar9 + local_114[6] * fVar2) * _DAT_0163405c);
                        local_d4[7] = (local_114[6] * fVar1) * 0.91651513899116799 +
                                      ((local_114[5] * fVar2 - local_114[3] * fVar9) * _DAT_016340e4 -
                                      (local_114[1] * fVar9 + local_114[7] * fVar2) * _DAT_016340a8);
                        local_d4[8] = (local_114[7] * fVar1) * 0.8 +
                                      ((local_114[6] * fVar2 - local_114[2] * fVar9) * _DAT_0163410c -
                                      (local_114[0] * fVar9 + local_114[8] * fVar2) * _DAT_01634168);
                        fVar11 = param_4[5];
                        iVar8 = 0;
                        local_d4[9] = (local_114[8] * fVar1) * 0.6 +
                                      (local_114[7] * fVar2 - local_114[1] * fVar9) * _DAT_01634134;
                        local_d4[10] = (local_114[8] * fVar2 - local_114[0] * fVar9) * 0.94868329805051377;
                        pfVar7 = param_5 + 100;
                        do {
                            fVar10 = R32(local_d4[iVar8] * fVar11);
                            iVar8 = iVar8 + 1;
                            *pfVar7 = fVar10 * fVar3;
                            pfVar7[1] = fVar10 * fVar4;
                            pfVar7[2] = fVar10 * fVar5;
                            pfVar7[3] = fVar10 * fVar6;
                            pfVar7 = pfVar7 + 4;
                        } while (iVar8 < 0xb);
                        if (param_2 < 7) {
                            return param_5 + 100;
                        }
                        local_114[0] = (local_d4[0] * fVar2 + local_d4[10] * fVar9) * 0.95742710775633810;
                        local_114[1] = (local_d4[0] * fVar1) * 0.55277079839256671 +
                                       (local_d4[9] * fVar9 + local_d4[1] * fVar2) * 0.87400737347512625;
                        local_114[2] = ((local_d4[1] * _DAT_016340cc) * fVar1 +
                                       (local_d4[8] * fVar9 + local_d4[2] * fVar2) * DAT_016340ec) -
                                       (local_d4[0] * fVar2 - local_d4[10] * fVar9) * 0.11785113019775792;
                        local_114[3] = (local_d4[2] * DAT_01634104) * fVar1 +
                                       ((local_d4[3] * fVar2 + local_d4[7] * fVar9) * 0.70710678118654757 -
                                       (local_d4[1] * fVar2 - local_d4[9] * fVar9) * 0.20412414523193151);
                        local_114[4] = (local_d4[3] * DAT_016341e0) * fVar1 +
                                       ((local_d4[6] * fVar9 + local_d4[4] * fVar2) * 0.62360956446232352 -
                                       (local_d4[2] * fVar2 - local_d4[8] * fVar9) * _DAT_0163407c);
                        local_114[5] = fVar9 * (local_d4[5] * 0.76376261582597338) +
                                       ((local_d4[4] * fVar1) * 0.98601329718326935 -
                                       (local_d4[3] * fVar2 - local_d4[7] * fVar9) * 0.37267799624996495);
                        local_114[6] = local_d4[5] * fVar1 -
                                       (local_d4[4] * fVar9 + local_d4[6] * fVar2) * 0.64549722436790280;
                        local_114[7] = (local_d4[6] * fVar1) * 0.98601329718326935 +
                                       (fVar2 * (local_d4[5] * 0.76376261582597338) -
                                       (local_d4[3] * fVar9 + local_d4[7] * fVar2) * 0.37267799624996495);
                        fVar11 = param_4[6];
                        iVar8 = 0;
                        local_114[8] = (local_d4[7] * DAT_016341e0) * fVar1 +
                                       ((local_d4[6] * fVar2 - local_d4[4] * fVar9) * 0.62360956446232352 -
                                       (local_d4[2] * fVar9 + local_d4[8] * fVar2) * _DAT_0163407c);
                        local_114[9] = (local_d4[8] * DAT_01634104) * fVar1 +
                                       ((local_d4[7] * fVar2 - local_d4[3] * fVar9) * 0.70710678118654757 -
                                       (local_d4[1] * fVar9 + local_d4[9] * fVar2) * 0.20412414523193151);
                        local_114[10] =
                             ((local_d4[9] * _DAT_016340cc) * fVar1 +
                             (local_d4[8] * fVar2 - local_d4[2] * fVar9) * DAT_016340ec) -
                             (local_d4[0] * fVar9 + local_d4[10] * fVar2) * 0.11785113019775792;
                        local_114[0xb] =
                             (local_d4[10] * fVar1) * 0.55277079839256671 +
                             (local_d4[9] * fVar2 - local_d4[1] * fVar9) * 0.87400737347512625;
                        local_114[0xc] = (local_d4[10] * fVar2 - local_d4[0] * fVar9) * 0.95742710775633810;
                        pfVar7 = param_5 + 0x90;
                        do {
                            fVar10 = R32(local_114[iVar8] * fVar11);
                            iVar8 = iVar8 + 1;
                            *pfVar7 = fVar10 * fVar3;
                            pfVar7[1] = fVar10 * fVar4;
                            pfVar7[2] = fVar10 * fVar5;
                            pfVar7[3] = fVar10 * fVar6;
                            pfVar7 = pfVar7 + 4;
                        } while (iVar8 < 0xd);
                        if (param_2 < 8)
                            return param_5 + 0x90;
                        if (7 < param_2) {
                            local_d4[0] = (local_114[0] * fVar2 + local_114[0xc] * fVar9) * 0.96362411165943151;
                            local_d4[1] = (local_114[0] * fVar1) * 0.51507875363771283 +
                                          (local_114[1] * fVar2 + local_114[0xb] * fVar9) * 0.89214257119977114;
                            local_d4[2] = (local_114[1] * fVar1) * 0.69985421222376520 +
                                          ((local_114[2] * fVar2 + local_114[10] * fVar9) * 0.82065180664828974 -
                                          (local_114[0] * fVar2 - local_114[0xc] * fVar9) * 0.10101525445522107);
                            local_d4[3] = (local_114[2] * fVar1) * 0.82065180664828974 +
                                          ((local_114[9] * fVar9 + local_114[3] * fVar2) * 0.74914917726439390 -
                                          (local_114[1] * fVar2 - local_114[0xb] * fVar9) * 0.17496355305594130);
                            local_d4[4] = (local_114[3] * fVar1) * 0.90350790290525129 +
                                          ((local_114[8] * fVar9 + local_114[4] * fVar2) * 0.67763092717893847 -
                                          (local_114[2] * fVar2 - local_114[10] * fVar9) * 0.24743582965269675);
                            local_d4[5] = (local_114[4] * fVar1) * 0.95831484749990992 +
                                          ((local_114[7] * fVar9 + local_114[5] * fVar2) * 0.60609152673132649 -
                                          (local_114[3] * fVar2 - local_114[9] * fVar9) * 0.31943828249996997);
                            local_d4[6] = fVar9 * (local_114[6] * 0.75592894601845440) +
                                          ((local_114[5] * fVar1) * 0.98974331861078702 -
                                          (local_114[4] * fVar2 - local_114[8] * fVar9) * 0.39123039821797578);
                            local_d4[7] = local_114[6] * fVar1 -
                                          (local_114[5] * fVar9 + local_114[7] * fVar2) * 0.65465367070797709;
                            local_d4[8] = (local_114[7] * fVar1) * 0.98974331861078702 +
                                          (fVar2 * (local_114[6] * 0.75592894601845440) -
                                          (local_114[4] * fVar9 + local_114[8] * fVar2) * 0.39123039821797578);
                            local_d4[9] = (fVar1 * local_114[8]) * 0.95831484749990992 +
                                          ((local_114[7] * fVar2 - local_114[5] * fVar9) * 0.60609152673132649 -
                                          (local_114[3] * fVar9 + local_114[9] * fVar2) * 0.31943828249996997);
                            local_d4[10] = (local_114[9] * fVar1) * 0.90350790290525129 +
                                           ((local_114[8] * fVar2 - local_114[4] * fVar9) * 0.67763092717893847 -
                                           (local_114[2] * fVar9 + local_114[10] * fVar2) * 0.24743582965269675);
                            fVar11 = param_4[7];
                            iVar8 = 0;
                            local_d4[0xb] =
                                 (fVar1 * local_114[10]) * 0.82065180664828974 +
                                 ((local_114[9] * fVar2 - local_114[3] * fVar9) * 0.74914917726439390 -
                                 (local_114[1] * fVar9 + local_114[0xb] * fVar2) * 0.17496355305594130);
                            local_d4[0xc] =
                                 (local_114[0xb] * fVar1) * 0.69985421222376520 +
                                 ((local_114[10] * fVar2 - local_114[2] * fVar9) * 0.82065180664828974 -
                                 (local_114[0] * fVar9 + local_114[0xc] * fVar2) * 0.10101525445522107);
                            local_d4[0xd] =
                                 (local_114[0xc] * fVar1) * 0.51507875363771283 +
                                 (local_114[0xb] * fVar2 - local_114[1] * fVar9) * 0.89214257119977114;
                            local_d4[0xe] = (local_114[0xc] * fVar2 - local_114[0] * fVar9) * 0.96362411165943151;
                            pfVar7 = param_5 + 0xc4;
                            do {
                                fVar9 = R32(local_d4[iVar8] * fVar11);
                                iVar8 = iVar8 + 1;
                                *pfVar7 = fVar9 * fVar3;
                                pfVar7[1] = fVar9 * fVar4;
                                pfVar7[2] = fVar9 * fVar5;
                                pfVar7[3] = fVar9 * fVar6;
                                pfVar7 = pfVar7 + 4;
                            } while (iVar8 < 0xf);
                            return param_5 + 0x100;
                        }
                    }
                }
            }
        }
    }
    return param_5 + 0x90;
}
} // namespace SP
