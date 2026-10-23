// match/slices/s01151ec0/s01151ec0.cpp
// Slice s01151ec0 -- EAWebKit EA::Text::Typesetter glyph-run transform builders
// (SporeApp.exe 0x01151ec0..0x01152b63).
//
//  01151ec0  Typesetter::updateRunTransforms  rotation/scale for the run: wrap the angle, sin/cos it,
//                                             build the per-mode basis columns at +0xd4..+0xe8, then
//                                             normalise the 5-vector (mode 2 takes a shortcut)
//  011523c0  Typesetter::emitRunDeltas        per-glyph position deltas (* 0.015625), dispatched on the
//                                             mode byte 4/6/other into FUN_01160300 emit calls
//  011526a0  Typesetter::layoutRun            cache check, rebuild the run, double-buffer swap, returns 1
//  011529d0  Typesetter::advanceRun           subtract the per-row step from the run float array, swap the
//                                             buffers, returns 1
//  01152b50  Typesetter::setGlyphCount        store the 16-bit count at +0x160, returns 0
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (EAWebKit, SSE scalar + x87 transcendentals)
#include "types.h"
#include <math.h>

double iat_floor(double);                            // 0x011e0906  ?iat_floor@@YANN@Z
void   FUN_01160300(int, int, float, float, int);    // 0x01160300
void   FUN_01134260(int, int, float, int);           // 0x01134260
void __fastcall FUN_01151e10(int self);              // 0x01151e10

struct TS;

// =========================================================================================================
// 01151ec0
// =========================================================================================================
// @ 0x01151ec0
extern "C" void __fastcall FUN_01151ec0(int param_1)
{
    float fVar1 = *(float*)(param_1 + 0x30);
    float fVar8 = *(float*)(param_1 + 0x28) * 0.017453292f;
    char  cVar5 = *(char*)(param_1 + 0x21);
    float fVar2 = *(float*)(param_1 + 0x38);
    float fVar3 = *(float*)(param_1 + 0x40);

    if (cVar5 != 2) {
        float fVar10 = *(float*)(param_1 + 0x6c);
        float fVar9  = (fVar10 + fVar8) * 0.15915494f;
        fVar8 = sqrtf(1.0f - fVar1 * fVar1);
        *(float*)(param_1 + 0xd4) = *(float*)(param_1 + 0xbc) * fVar8;
        *(float*)(param_1 + 0xd8) = *(float*)(param_1 + 0xc0) * fVar8;
        *(float*)(param_1 + 0xdc) = *(float*)(param_1 + 0xc4) * fVar8;
        *(float*)(param_1 + 0xe0) = *(float*)(param_1 + 0xc8) * fVar8;
        *(float*)(param_1 + 0xe4) = fVar8 * *(float*)(param_1 + 0xcc);
        *(int*)(param_1 + 0xe8)   = *(int*)(param_1 + 0x48);

        double dVar11 = iat_floor((double)fVar9);
        float fVar6 = (float)(((double)fVar9 - dVar11) * 6.2831855 - (double)fVar10);
        float fVar4;
        {
            float s = (float)sin((double)fVar6);
            fVar9 = s;
            float c = (float)cos((double)fVar6);
            fVar4 = c;
        }
        if (fVar10 <= fVar6) {
            if (*(float*)(param_1 + 0x70) <= fVar6) {
                if (6.2831855f - *(float*)(param_1 + 0x70) <= fVar6) {
                    fVar8  = *(float*)(param_1 + 0xb0) * fVar4 + *(float*)(param_1 + 0xac) * fVar9;
                    fVar10 = *(float*)(param_1 + 0xb8) * fVar4 + *(float*)(param_1 + 0xb4) * fVar9;
                    fVar2 = 1.0f / sqrtf(fVar8 * fVar8 + fVar10 * fVar10);
                    *(float*)(param_1 + 0xdc) = (fVar8 * fVar2) * fVar1 + *(float*)(param_1 + 0xdc);
                    *(float*)(param_1 + 0xd4) = (fVar10 * fVar2) * fVar1 + *(float*)(param_1 + 0xd4);
                } else {
                    fVar8  = *(float*)(param_1 + 0xa0) * fVar4 + *(float*)(param_1 + 0x9c) * fVar9;
                    fVar10 = *(float*)(param_1 + 0xa8) * fVar4 + *(float*)(param_1 + 0xa4) * fVar9;
                    fVar2 = 1.0f / sqrtf(fVar8 * fVar8 + fVar10 * fVar10);
                    *(float*)(param_1 + 0xe0) = (fVar8 * fVar2) * fVar1 + *(float*)(param_1 + 0xe0);
                    *(float*)(param_1 + 0xdc) = (fVar10 * fVar2) * fVar1 + *(float*)(param_1 + 0xdc);
                }
            } else {
                fVar8  = *(float*)(param_1 + 0x90) * fVar4 + *(float*)(param_1 + 0x8c) * fVar9;
                fVar10 = *(float*)(param_1 + 0x98) * fVar4 + *(float*)(param_1 + 0x94) * fVar9;
                fVar2 = 1.0f / sqrtf(fVar8 * fVar8 + fVar10 * fVar10);
                *(float*)(param_1 + 0xd8) = (fVar8 * fVar2) * fVar1 + *(float*)(param_1 + 0xd8);
                *(float*)(param_1 + 0xe0) = (fVar10 * fVar2) * fVar1 + *(float*)(param_1 + 0xe0);
            }
        } else {
            float local_14 = *(float*)(param_1 + 0x80) * fVar4 + *(float*)(param_1 + 0x7c) * fVar9;
            float local_10 = *(float*)(param_1 + 0x88) * fVar4 + *(float*)(param_1 + 0x84) * fVar9;
            float local_c  = 0.0f;
            if (cVar5 == 6) {
                local_c = local_10;
                if (local_14 < local_10) {
                    local_c = local_14;
                }
                local_c = local_c * fVar2;
                local_14 = local_14 - local_c;
                local_10 = local_10 - local_c;
                local_c = *(float*)(param_1 + 0x74) * local_c;
            }
            fVar2 = 1.0f / sqrtf(local_14 * local_14 + (local_10 * local_10 + local_c * local_c));
            *(float*)(param_1 + 0xd4) = (local_14 * fVar2) * fVar1 + *(float*)(param_1 + 0xd4);
            *(float*)(param_1 + 0xd8) = (local_10 * fVar2) * fVar1 + *(float*)(param_1 + 0xd8);
            *(float*)(param_1 + 0xe4) = fVar1 * (fVar2 * local_c) + *(float*)(param_1 + 0xe4);
        }

        fVar1  = *(float*)(param_1 + 0xe0);
        fVar9  = *(float*)(param_1 + 0xe4);
        fVar2  = *(float*)(param_1 + 0xd8);
        fVar8  = *(float*)(param_1 + 0xd4);
        fVar10 = *(float*)(param_1 + 0xdc);
        fVar3 = (1.0f / sqrtf(fVar10 * fVar10 +
                              (fVar8 * fVar8 + (fVar2 * fVar2 + (fVar9 * fVar9 + fVar1 * fVar1))))) *
                fVar3;
        *(float*)(param_1 + 0xe4) = fVar3 * fVar9;
        *(float*)(param_1 + 0xd4) = fVar8 * fVar3;
        *(float*)(param_1 + 0xd8) = fVar2 * fVar3;
        *(float*)(param_1 + 0xdc) = fVar10 * fVar3;
        *(float*)(param_1 + 0xe0) = fVar1 * fVar3;
        return;
    }

    float s = (float)sin((double)fVar8);
    float c = (s + 1.0f) * 0.5f;
    float fVar7 = fVar3;
    *(float*)(param_1 + 0xd4) = sqrtf(1.0f - c) * fVar7;
    *(float*)(param_1 + 0xd8) = sqrtf(c) * fVar7;
}

// =========================================================================================================
// 011523c0
// =========================================================================================================
// @ 0x011523c0
struct TS {
    void FUN_011523c0(int param_2, int param_3, float* param_4);
    int  FUN_011529d0(int param_2);
};

void TS::FUN_011523c0(int param_2, int param_3, float* param_4)
{
    int   self = (int)this;
    float afStack_18[6];
    unsigned char bVar2 = *(unsigned char*)(self + 0x21);
    unsigned uVar5 = 0;
    if (bVar2 > 3) {
        float* pfVar7 = (float*)(self + 0xd8);
        float* pfVar4 = param_4 + 2;
        do {
            afStack_18[uVar5]     = (pfVar7[-1] - pfVar4[-2]) * 0.015625f;
            afStack_18[uVar5 + 1] = (*pfVar7    - pfVar4[-1]) * 0.015625f;
            afStack_18[uVar5 + 2] = (pfVar7[1]  - *pfVar4)    * 0.015625f;
            afStack_18[uVar5 + 3] = (pfVar7[2]  - pfVar4[1])  * 0.015625f;
            uVar5 += 4;
            pfVar7 += 4;
            pfVar4 += 4;
        } while (uVar5 < bVar2 - 3);
    }
    unsigned uVar6 = *(unsigned char*)(self + 0x21);
    if (uVar5 < uVar6) {
        float* pfVar4 = (float*)(self + 0xd4 + uVar5 * 4);
        do {
            afStack_18[uVar5] = (*pfVar4 - param_4[uVar5]) * 0.015625f;
            uVar5++;
            pfVar4++;
        } while (uVar5 < uVar6);
    }
    int uVar3 = *(int*)(param_3 + 4);
    float uVar1 = *param_4;
    if (uVar6 != 6) {
        if (uVar6 != 4) {
            FUN_01160300(*(int*)(param_2 + 4), uVar3, uVar1, afStack_18[0], 0x100);
            FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 4, uVar3, param_4[1],
                         afStack_18[1], 0x100);
            return;
        }
        FUN_01160300(*(int*)(param_2 + 4), uVar3, uVar1, afStack_18[0], 0x100);
        FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 4, uVar3, param_4[1],
                     afStack_18[1], 0x100);
        FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 8, uVar3, param_4[2],
                     afStack_18[2], 0x100);
        FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 0xc, uVar3, param_4[3],
                     afStack_18[3], 0x100);
        return;
    }
    FUN_01160300(*(int*)(param_2 + 4), uVar3, uVar1, afStack_18[0], 0x100);
    FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 4, uVar3, param_4[4],
                 afStack_18[4], 0x100);
    FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 8, uVar3, param_4[1],
                 afStack_18[1], 0x100);
    FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 0xc, uVar3, param_4[2],
                 afStack_18[2], 0x100);
    FUN_01160300(*(unsigned short*)(param_2 + 0xe) * 0x10 + *(int*)(param_2 + 4), uVar3, param_4[3],
                 afStack_18[3], 0x100);
    FUN_01160300(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * 0x14, uVar3, param_4[5],
                 afStack_18[5], 0x100);
}

// =========================================================================================================
// 011526a0
// =========================================================================================================
// @ 0x011526a0
extern "C" int __cdecl FUN_011526a0(int param_1, int param_2, char param_3)
{
    float local_28[10];

    if (param_3 != 0) {
        FUN_01151e10(param_1);
        FUN_01151ec0(param_1);
    }
    float fVar11 = *(float*)(param_1 + 0x28) * 0.017453292f;
    int local_1c = *(int*)(param_2 + 0x3000c);
    int iVar3    = *(int*)(param_2 + 0x30010);
    float fVar1  = *(float*)(param_1 + 0x30);
    local_28[0] = *(float*)(param_1 + 0x38);
    local_28[1] = *(float*)(param_1 + 0x40);
    local_28[2] = *(float*)(param_1 + 0x48);
    unsigned uVar9 = *(unsigned char*)(param_1 + 0x21);

    if (fVar11 == *(float*)(param_1 + 0x50) && fVar1 == *(float*)(param_1 + 0x54) &&
        local_28[0] == *(float*)(param_1 + 0x58) &&
        local_28[1] == *(float*)(param_1 + 0x5c) && local_28[2] == *(float*)(param_1 + 0x60)) {
        int uVar2 = *(int*)(param_1 + 0xd4);
        int uVar4 = *(int*)(local_1c + 4);
        if (uVar9 == 6) {
            FUN_01134260(*(int*)(iVar3 + 4), uVar4, *(float*)(param_1 + 0xd4), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 4, uVar4,
                         *(float*)(param_1 + 0xe4), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 8, uVar4,
                         *(float*)(param_1 + 0xd8), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 0xc, uVar4,
                         *(float*)(param_1 + 0xdc), 0x100);
            FUN_01134260(*(unsigned short*)(iVar3 + 0xe) * 0x10 + *(int*)(iVar3 + 4), uVar4,
                         *(float*)(param_1 + 0xe0), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 0x14, uVar4,
                         *(float*)(param_1 + 0xe8), 0x100);
        } else if (uVar9 == 4) {
            FUN_01134260(*(int*)(iVar3 + 4), uVar4, *(float*)(param_1 + 0xd4), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 4, uVar4,
                         *(float*)(param_1 + 0xd8), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 8, uVar4,
                         *(float*)(param_1 + 0xdc), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 0xc, uVar4,
                         *(float*)(param_1 + 0xe0), 0x100);
        } else {
            FUN_01134260(*(int*)(iVar3 + 4), uVar4, *(float*)(param_1 + 0xd4), 0x100);
            FUN_01134260(*(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * 4, uVar4,
                         *(float*)(param_1 + 0xd8), 0x100);
        }
    } else {
        if (local_28[0] != *(float*)(param_1 + 0x58)) {
            FUN_01151e10(param_1);
            uVar9 = *(unsigned char*)(param_1 + 0x21);
        }
        unsigned uVar5 = 0;
        if ((int)uVar9 > 3) {
            unsigned uVar6 = uVar5;
            float* pfVar7 = (float*)(param_1 + 0xd8);
            do {
                uVar5 = uVar6 + 4;
                local_28[uVar5]     = pfVar7[-1];
                local_28[uVar6 + 5] = *pfVar7;
                local_28[uVar6 + 6] = pfVar7[1];
                local_28[uVar6 + 7] = pfVar7[2];
                uVar6 = uVar5;
                pfVar7 += 4;
            } while (uVar5 < uVar9 - 3);
        }
        if (uVar5 < uVar9) {
            float* pfVar7  = (float*)(param_1 + 0xd4 + uVar5 * 4);
            float* pfVar10 = local_28 + uVar5 + 4;
            for (int iVar8 = uVar9 - uVar5; iVar8 != 0; iVar8--) {
                *pfVar10 = *pfVar7;
                pfVar7++;
                pfVar10++;
            }
        }
        FUN_01151ec0(param_1);
        *(float*)(param_1 + 0x50) = fVar11;
        *(float*)(param_1 + 0x54) = fVar1;
        *(float*)(param_1 + 0x58) = local_28[0];
        *(float*)(param_1 + 0x5c) = local_28[1];
        *(float*)(param_1 + 0x60) = local_28[2];
        ((TS*)param_1)->FUN_011523c0(iVar3, local_1c, local_28 + 4);
    }
    int uVar2 = *(int*)(param_2 + 0x30010);
    *(int*)(param_2 + 0x30010) = *(int*)(param_2 + 0x3000c);
    *(int*)(param_2 + 0x3000c) = uVar2;
    return 1;
}

// =========================================================================================================
// 011529d0
// =========================================================================================================
// @ 0x011529d0
int TS::FUN_011529d0(int param_2)
{
    int self = (int)this;
    int iVar3 = *(int*)(param_2 + 0x30010);
    float* pfVar5 = (float*)(*(unsigned short*)(self + 0x162) + self);
    unsigned uVar6 = *(unsigned char*)(self + 0x166);
    if (*(unsigned short*)(self + 0x160) <= (unsigned short)*(unsigned char*)(self + 0x166)) {
        uVar6 = *(unsigned short*)(self + 0x160);
    }
    unsigned local_8 = 0;
    if (*(char*)(self + 0x21) != 0) {
        do {
            int iVar1 = *(int*)(iVar3 + 4) + *(unsigned short*)(iVar3 + 0xe) * local_8 * 4;
            unsigned uVar8 = 0;
            float fVar10 = *pfVar5 / (float)*(unsigned char*)(self + 0x166);
            if (uVar6 > 3) {
                int iVar9 = ((uVar6 - 4) >> 2) + 1;
                float* pfVar7 = (float*)(iVar1 + 8);
                uVar8 = iVar9 * 4;
                do {
                    float fVar2 = *pfVar5;
                    *pfVar5 = fVar2 - fVar10;
                    pfVar7[-2] = fVar2 - fVar10;
                    fVar2 = *pfVar5;
                    *pfVar5 = fVar2 - fVar10;
                    pfVar7[-1] = fVar2 - fVar10;
                    fVar2 = *pfVar5;
                    *pfVar5 = fVar2 - fVar10;
                    *pfVar7 = fVar2 - fVar10;
                    fVar2 = *pfVar5;
                    *pfVar5 = fVar2 - fVar10;
                    pfVar7[1] = fVar2 - fVar10;
                    pfVar7 += 4;
                    iVar9--;
                } while (iVar9 != 0);
            }
            for (; uVar8 < uVar6; uVar8++) {
                float fVar2 = *pfVar5;
                *pfVar5 = fVar2 - fVar10;
                *(float*)(iVar1 + uVar8 * 4) = fVar2 - fVar10;
            }
            local_8++;
            pfVar5++;
        } while (local_8 < *(unsigned char*)(self + 0x21));
    }
    *(char*)(self + 0x166) = *(char*)(self + 0x166) - (char)uVar6;
    int uVar4 = *(int*)(param_2 + 0x3000c);
    *(int*)(param_2 + 0x3000c) = *(int*)(param_2 + 0x30010);
    *(int*)(param_2 + 0x30010) = uVar4;
    *(unsigned char*)(param_2 + 0x3002c) = *(unsigned char*)(self + 0x21);
    *(int*)(param_2 + 0x30024) = *(int*)(self + 0x15c);
    *(unsigned*)(param_2 + 0x30020) = uVar6;
    if (*(char*)(self + 0x166) == 0) {
        *(unsigned char*)(self + 0x165) = 0;
    }
    return 1;
}

// =========================================================================================================
// 01152b50
// =========================================================================================================
// @ 0x01152b50
extern "C" int __cdecl FUN_01152b50(int param_1, int param_2, int param_3, short param_4)
{
    *(short*)(param_1 + 0x160) = param_4;
    return 0;
}
