// s00b90480: 23 functions, 0x00b90480..0x00b90ea0, Spore editor plant/mission + planet-cell helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (no /EHsc)
#include "types.h"
#include <math.h>

#pragma warning(disable: 4100)

typedef unsigned int uint;

// ---- external helpers -------------------------------------------------------
void* FUN_00401090();                                               // species manager getter
void  FUN_004cea40(char* buf, int n, int* ctx);
int   GetMatchingPlantProfiles(void* mgr, void** out, int n, unsigned id);
void  FUN_00b900a0(int);
void  operator_delete__(void*);
int   WrapCubeFace(unsigned face, int* a, int* b, int* c, int d, int e);
double RandomDoubleUniform(void* rng);                              // 0x00ac?? RNG
char  FUN_00ac0730(int a, const int* b);
int   FUN_00b88590(int h);
struct Obj342 { void Notify(bool b); };
int   FUN_00685450(int a, int* b, int c, void* out);
void  VectorBoolDoInsert(void* a, void* b, int c);
void  VectorKeyDoInsert(void* end, const void* val);

extern char  DAT_016888e8;          // RNG state
extern char  DAT_0156c064;          // enabled flag
extern int   DAT_0156c084;          // dim
extern int   DAT_0156c094;          // base pointer
extern int   DAT_016888ec;          // list begin
extern int   DAT_016888f0;          // list end
extern const unsigned char kCellBasis[];   // 0x01465948 byte table

struct Obj90480 { void F(); };
// @ 0x00b90480
void Obj90480::F()
{
    int param_1 = (int)this;
    if (*(char*)(param_1 + 0x38) == '\0') {
        *(char*)(param_1 + 0x38) = 1;
        void* local_428 = FUN_00401090();
        uint uVar3 = 0;
        unsigned local_424[4];
        local_424[0] = 0xbcd73e89;
        local_424[1] = 0xb8669ec9;
        local_424[2] = 0x37148141;
        int local_42c = 0;
        char local_400[1024];
        do {
            unsigned puVar2 = local_424[uVar3];
            char* buf = local_400;
            FUN_004cea40(buf, 100, &local_42c);
            int iVar1 = GetMatchingPlantProfiles(local_428, (void**)&buf, 100, puVar2);
            int iVar4 = 0;
            if (0 < iVar1) {
                do {
                    if (*(int*)(buf + iVar4 * 4) != 0) {
                        FUN_00b900a0(*(int*)(buf + iVar4 * 4));
                    }
                    iVar4 = iVar4 + 1;
                } while (iVar4 < iVar1);
            }
            uVar3 = uVar3 + 1;
        } while (uVar3 < 3);
    }
}

// @ 0x00b90560
void FUN_00b90560(int param_1, int param_2, int param_3)
{
    unsigned uVar5 = 0xffffffff;
    if (param_1 == 0x29c388a)
        uVar5 = 0xb8669ec9;
    else if (param_1 == 0x3a8be428)
        uVar5 = 0x37148141;
    else if (param_1 == 0x6d60a1cc)
        uVar5 = 0xbcd73e89;
    void* pcVar3 = FUN_00401090();
    char local_400[1024];
    char* local_418 = local_400;
    int local_41c = 0;
    char* local_414 = local_418;
    if (param_3 == 0) {
        VectorBoolDoInsert(local_400, local_400, 0);
        local_414 = local_414 + ((int)(local_400 + -(int)local_400) >> 2) * -4;
    } else {
        FUN_004cea40(local_400, param_3, &local_41c);
    }
    int iVar4 = GetMatchingPlantProfiles(pcVar3, (void**)&local_418, param_3, uVar5);
    int iVar6 = 0;
    if (0 < iVar4) {
        do {
            int iVar1 = *(int*)(local_418 + iVar6 * 4);
            int* puVar2 = *(int**)(param_2 + 4);
            if (puVar2 < *(int**)(param_2 + 8)) {
                *(int**)(param_2 + 4) = puVar2 + 3;
                if (puVar2 != 0) {
                    puVar2[0] = *(int*)(iVar1 + 0x504);
                    puVar2[1] = *(int*)(iVar1 + 0x508);
                    puVar2[2] = *(int*)(iVar1 + 0x50c);
                }
            } else {
                VectorKeyDoInsert(puVar2, (const void*)(iVar1 + 0x504));
            }
            iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
    }
    if ((local_418 != 0) && (*(int*)(local_418 - 4) != 0))
        operator_delete__(local_418);
}

// @ 0x00b906a0
float FUN_00b906a0(float param_1, float param_2)
{
    float fVar1 = (float)(RandomDoubleUniform(&DAT_016888e8) * ((double)param_2 - (double)param_1) + (double)param_1);
    if (param_2 <= fVar1)
        return param_2;
    if (param_1 > fVar1)
        return param_1;
    return fVar1;
}

// @ 0x00b906f0
void FUN_00b906f0(unsigned param_1, int param_2, int param_3, int param_4)
{
    int iVar1;
    do {
        iVar1 = WrapCubeFace(param_1, &param_2, &param_3, &param_4, 0, 0);
    } while (iVar1 != 0);
}

// @ 0x00b90720
char* __fastcall FUN_00b90720(char* param_1)
{
    *param_1 = 0;
    return param_1;
}

// @ 0x00b90730
bool FUN_00b90730(int param_1, int param_2)
{
    return *(int*)(param_1 + 0xc) > *(int*)(param_2 + 0xc);
}

struct Cell90750 { int F(int param_2, int param_3, int param_4); };
// @ 0x00b90750
int Cell90750::F(int param_2, int param_3, int param_4)
{
    int param_1 = (int)this;
    unsigned uVar1 = *(unsigned*)(param_1 + 0x24);
    int iVar2;
    do {
        iVar2 = WrapCubeFace(uVar1, &param_2, &param_3, &param_4, 0, 0);
    } while (iVar2 != 0);
    return *(int*)(param_1 + 0x34) +
           ((*(int*)(param_1 + 0x24) * param_2 + param_4) * *(int*)(param_1 + 0x24) + param_3) * 0xc;
}

struct Cell907A0 { unsigned F(int param_2, int param_3, int param_4); };
// @ 0x00b907a0
unsigned Cell907A0::F(int param_2, int param_3, int param_4)
{
    int param_1 = (int)this;
    unsigned uVar1 = *(unsigned*)(param_1 + 0x24);
    int iVar2;
    do {
        iVar2 = WrapCubeFace(uVar1, &param_2, &param_3, &param_4, 0, 0);
    } while (iVar2 != 0);
    return *(unsigned*)(*(int*)(param_1 + 0x34) + 4 +
        ((*(int*)(param_1 + 0x24) * param_2 + param_4) * *(int*)(param_1 + 0x24) + param_3) * 0xc);
}

struct Cell907F0 { bool F(int param_2, int param_3, int param_4, int param_5); };
// @ 0x00b907f0
bool Cell907F0::F(int param_2, int param_3, int param_4, int param_5)
{
    int param_1 = (int)this;
    uint* puVar1 = (uint*)(*(int*)(param_1 + 0x34) + 4 + param_2 * 0xc);
    uint uVar2 = *puVar1;
    if ((uVar2 & 8) != 0)
        return (uVar2 & 7) == 0;
    int iVar3 = (uint)(*(int*)(param_1 + 0x38) * param_4) / *(uint*)(param_1 + 0x24) +
                (uint)(*(int*)(param_1 + 0x3c) * param_5) / *(uint*)(param_1 + 0x24) +
                *(int*)(param_1 + 0x3c) * param_3 + *(int*)(param_1 + 0x48);
    if ((int)((uint)*(unsigned short*)(*(int*)(param_1 + 0x2c) + iVar3 * 2) - *(int*)(param_1 + 0x40)) < 0)
        *puVar1 = uVar2 | 1;
    float fVar4 = (float)*(unsigned char*)(*(int*)(param_1 + 0x30) + 3 + iVar3 * 4) * 0.3921569f;
    if (fVar4 < *(float*)(param_1 + 0x28) || fVar4 == *(float*)(param_1 + 0x28))
        uVar2 = 0;
    else
        uVar2 = 2;
    *puVar1 = *puVar1 | uVar2 | 8;
    return (*puVar1 & 7) == 0;
}

// @ 0x00b908a0
bool FUN_00b908a0(int param_1, int param_2)
{
    return *(uint*)(param_1 + 0x11c) < *(uint*)(param_2 + 0x11c);
}

// @ 0x00b908c0
void FUN_00b908c0(void)
{
    if ((DAT_0156c064 != '\0') && (DAT_0156c084 * DAT_0156c084 * 6 > 0)) {
        int iVar3 = DAT_0156c084 * DAT_0156c084 * 6;
        int iVar2 = 0;
        do {
            uint* puVar1 = (uint*)(iVar2 + 4 + DAT_0156c094);
            *puVar1 = *puVar1 & 0xffffff8f;
            iVar2 = iVar2 + 0xc;
            iVar3 = iVar3 - 1;
        } while (iVar3 != 0);
    }
}

// @ 0x00b90900
struct VtThing {
    void CallABB(int a, int b);
    void CallAAA(int a);
};
void VtThing::CallABB(int a, int b)
{
    ((void (__thiscall*)(VtThing*, int, int, int))(*(void***)this)[0x10 / 4])(this, a, b, b);
}

// @ 0x00b90920
void VtThing::CallAAA(int a)
{
    ((void (__thiscall*)(VtThing*, int, int, int))(*(void***)this)[0x10 / 4])(this, a, a, a);
}

// @ 0x00b90960
int* FUN_00b90960(int* param_1, int* param_2, int param_3)
{
    while (true) {
        if (param_1 == param_2)
            return param_1;
        int uVar1 = ((int (__thiscall*)(int))(*(void***)(*param_1 + 0x34))[0x2c / 4])(*param_1 + 0x34);
        int iVar2 = FUN_00b88590(uVar1);
        if (param_3 != iVar2)
            break;
        param_1 = param_1 + 1;
    }
    return param_1;
}

// @ 0x00b909a0
int* FUN_00b909a0(int* param_1, int* param_2, int* param_3, int param_4)
{
    if (param_1 == param_2)
        return param_3;
    do {
        int uVar1 = ((int (__thiscall*)(int))(*(void***)(*param_1 + 0x34))[0x2c / 4])(*param_1 + 0x34);
        int iVar2 = FUN_00b88590(uVar1);
        if (param_4 == iVar2) {
            *param_3 = *param_1;
            param_3 = param_3 + 1;
        }
        param_1 = param_1 + 1;
    } while (param_1 != param_2);
    return param_3;
}

// @ 0x00b909f0
void FUN_00b909f0(int* param_1, int* param_2, char (*param_3)(int, int))
{
    int* puVar2 = param_1;
    if (param_1 != param_2) {
        while (puVar2 = puVar2 + 1, puVar2 != param_2) {
            int uVar1 = *puVar2;
            int* puVar4 = puVar2;
            while (puVar4 != param_1 && (*param_3)(uVar1, puVar4[-1])) {
                *puVar4 = puVar4[-1];
                puVar4 = puVar4 - 1;
            }
            *puVar4 = uVar1;
        }
    }
}

// @ 0x00b90a40
void FUN_00b90a40(int** param_1, int** param_2, char (*param_3)(int*, int*))
{
    for (; param_1 != param_2; param_1 = param_1 + 1) {
        int* piVar1 = *param_1;
        if (piVar1 != 0)
            ((void (__thiscall*)(int*))(*(void***)piVar1)[0])(piVar1);
        char cVar5 = (*param_3)(piVar1, param_1[-1]);
        int** piVar4 = param_1;
        while (cVar5 != '\0') {
            int* piVar2 = *piVar4;
            int* piVar3 = piVar4[-1];
            if (piVar3 != piVar2) {
                if (piVar3 != 0)
                    ((void (__thiscall*)(int*))(*(void***)piVar3)[0])(piVar3);
                *piVar4 = piVar3;
                if (piVar2 != 0)
                    ((void (__thiscall*)(int*))(*(void***)piVar2)[1])(piVar2);
            }
            cVar5 = (*param_3)(piVar1, piVar4[-2]);
            piVar4 = piVar4 - 1;
        }
        int* piVar2 = *piVar4;
        if (piVar1 != piVar2) {
            if (piVar1 != 0)
                ((void (__thiscall*)(int*))(*(void***)piVar1)[0])(piVar1);
            *piVar4 = piVar1;
            if (piVar2 != 0)
                ((void (__thiscall*)(int*))(*(void***)piVar2)[1])(piVar2);
        }
        if (piVar1 != 0)
            ((void (__thiscall*)(int*))(*(void***)piVar1)[1])(piVar1);
    }
}

// @ 0x00b90b10
void FUN_00b90b10(int param_1, int param_2, int param_3, int* param_4)
{
    int iVar3;
    while (iVar3 = param_3, param_2 < iVar3) {
        param_3 = (iVar3 + -1) >> 1;
        char cVar4 = FUN_00ac0730(*(int*)(param_1 + param_3 * 4), param_4);
        if (cVar4 == '\0')
            break;
        int* piVar1 = *(int**)(param_1 + iVar3 * 4);
        int* piVar2 = *(int**)(param_1 + param_3 * 4);
        if (piVar2 != piVar1) {
            if (piVar2 != 0)
                ((void (__thiscall*)(int*))(*(void***)piVar2)[0xbc / 4])(piVar2);
            *(int**)(param_1 + iVar3 * 4) = piVar2;
            if (piVar1 != 0)
                ((void (__thiscall*)(int*))(*(void***)piVar1)[0xc0 / 4])(piVar1);
        }
    }
    int* piVar1 = *(int**)(param_1 + iVar3 * 4);
    if (param_4 != piVar1) {
        if (param_4 != 0)
            ((void (__thiscall*)(int*))(*(void***)param_4)[0xbc / 4])(param_4);
        *(int**)(param_1 + iVar3 * 4) = param_4;
        if (piVar1 != 0)
            ((void (__thiscall*)(int*))(*(void***)piVar1)[0xc0 / 4])(piVar1);
    }
    if (param_4 != 0)
        ((void (__thiscall*)(int*))(*(void***)param_4)[0xc0 / 4])(param_4);
}

// @ 0x00b90bd0
int* FUN_00b90bd0(int* param_1, int* param_2, int* param_3, char (*param_4)(int, int))
{
    char cVar1 = (*param_4)(*param_1, *param_2);
    if (cVar1 == '\0') {
        cVar1 = (*param_4)(*param_1, *param_3);
        if (cVar1 != '\0')
            return param_1;
        cVar1 = (*param_4)(*param_2, *param_3);
        if (cVar1 != '\0')
            return param_3;
    } else {
        cVar1 = (*param_4)(*param_2, *param_3);
        if (cVar1 == '\0') {
            cVar1 = (*param_4)(*param_1, *param_3);
            if (cVar1 == '\0')
                return param_1;
            return param_3;
        }
    }
    return param_2;
}

// @ 0x00b90c50
void FUN_00b90c50(int param_1)
{
    int iVar1 = *(int*)(param_1 + 0x34);
    int iVar3 = *(int*)(iVar1 + 0x324);
    *(char*)(iVar3 + 0x108) = 0;
    iVar3 = ((int (__thiscall*)(int))(*(void***)(iVar3 + 0x34))[0xac / 4])(iVar3 + 0x34);
    if (iVar3 != 0)
        *(uint*)(iVar3 + 4) = *(uint*)(iVar3 + 4) | 1;
    char cVar2 = ((char (__thiscall*)(int))(*(void***)(iVar1 + 0x120))[0x58 / 4])(iVar1 + 0x120);
    if (cVar2 == '\0')
        ((Obj342*)iVar1)->Notify(*(int*)(param_1 + 0x10) != 0);
}

// @ 0x00b90cb0
bool FUN_00b90cb0(float* param_1, float param_2)
{
    int iVar1 = (DAT_016888f0 - DAT_016888ec) / 0x34;
    int iVar2 = 0;
    if (0 < iVar1) {
        float* pfVar3 = (float*)(DAT_016888ec + 8);
        do {
            if (sqrt((*param_1 - pfVar3[-2]) * (*param_1 - pfVar3[-2]) +
                     ((param_1[1] - pfVar3[-1]) * (param_1[1] - pfVar3[-1]) +
                      (param_1[2] - *pfVar3) * (param_1[2] - *pfVar3))) < pfVar3[1] + param_2)
                return true;
            iVar2 = iVar2 + 1;
            pfVar3 = pfVar3 + 0xd;
        } while (iVar2 < iVar1);
    }
    return 0;
}

// @ 0x00b90d70
int FUN_00b90d70(int* param_1, int param_2, float param_3)
{
    if (1.5258789e-05f <= param_3) {
        float fVar7 = (((float)param_1[1] + 0.5f) * (1.0f / (float)param_2)) * 2.0f - 1.0f;
        float fVar6 = (((float)*param_1 + 0.5f) * (1.0f / (float)param_2)) * 2.0f - 1.0f;
        int iVar1 = (param_1[2] >> 1) * 4;
        float fVar4 = 1.0f / (float)sqrt((double)((fVar6 * fVar6 + fVar7 * fVar7) + 1.0f));
        float fVar8 = fVar4;
        if ((param_1[2] & 1U) != 0)
            fVar8 = -fVar4;
        unsigned char bVar2 = kCellBasis[iVar1 + 1];
        unsigned char bVar3 = kCellBasis[iVar1 + 2];
        float local_c[3];
        local_c[kCellBasis[iVar1]] = fVar8 * fVar6;
        local_c[bVar2] = fVar4 * fVar7;
        local_c[bVar3] = fVar8;
        float fVar5 = (float)cos((double)((90.0f - param_3) * 0.017453292f));
        if (fVar5 <= (float)fabs((double)(((double)local_c[1] + (double)local_c[0]) * 0.0 + (double)local_c[2])))
            return 0;
    }
    return 1;
}

struct Model90EA0 { void F(float* param_2, float param_3, float param_4, float param_5); };
// @ 0x00b90ea0
void Model90EA0::F(float* param_2, float param_3, float param_4, float param_5)
{
    int param_1 = (int)this;
    float local_b0 = param_2[0];
    float local_ac = param_2[1];
    float local_a8 = param_2[2];
    float fVar9 = (float)sqrt((double)((local_a8 * local_a8 + local_ac * local_ac) + local_b0 * local_b0));
    if (1.5258789e-05f < fVar9) {
        fVar9 = 1.0f / fVar9;
        local_b0 = local_b0 * fVar9;
        local_ac = local_ac * fVar9;
        local_a8 = local_a8 * fVar9;
        float* pfVar5 = &param_4;
        if (param_4 <= param_3)
            pfVar5 = &param_3;
        if (*pfVar5 <= param_5 && param_5 != *pfVar5)
            pfVar5 = &param_5;
        float local_b4 = *pfVar5;
        int iVar6 = *(int*)(param_1 + 0x24);
        float local_a0 = fabsf(local_b0);
        float fVar12 = fabsf(local_ac);
        float local_9c = (fVar9 * param_3) * (fVar9 * param_3);
        float local_a4 = fabsf(local_a8);
        float local_94 = (fVar9 * param_4) * (fVar9 * param_4);
        float local_90 = (fVar9 * param_5) * (fVar9 * param_5);
        float fVar10 = (float)iVar6 * 0.5f;
        int local_c0, local_bc;
        unsigned local_b8;
        if ((local_a4 < local_a0) || (local_a4 < fVar12)) {
            if (fVar12 < local_a0) {
                local_c0 = (int)((local_ac / local_b0 + 1.0f) * fVar10);
                local_bc = (int)((local_a8 / local_a0 + 1.0f) * fVar10);
                local_b8 = 2;
                if (local_b0 < 0.0f)
                    local_b8 = 3;
            } else {
                local_c0 = (int)((local_a8 / local_ac + 1.0f) * fVar10);
                local_bc = (int)((local_b0 / fVar12 + 1.0f) * fVar10);
                if (local_ac < 0.0f)
                    local_b8 = 5;
                else
                    local_b8 = 4;
            }
        } else {
            local_c0 = (int)((local_b0 / local_a8 + 1.0f) * fVar10);
            local_bc = (int)((local_ac / local_a4 + 1.0f) * fVar10);
            if (local_a8 < 0.0f)
                local_b8 = 1;
            else
                local_b8 = 0;
        }
        if (local_c0 == iVar6)
            local_c0 = local_c0 - 1;
        if (local_bc == iVar6)
            local_bc = local_bc - 1;
        float local_8c0 = ((float)iVar6 * fVar9) * local_b4;
        int iVar6b = (int)(local_8c0 + 0.5f);
        if ((float)iVar6b < local_8c0)
            iVar6b = iVar6b + 1;
        int local_7c = param_1;
        int local_74[28];
        int local_c4 = FUN_00685450(*(int*)(param_1 + 0x24), &local_c0, iVar6b, local_74);
        if (0 < local_c4) {
            int* piVar7 = local_74;
            do {
                if (piVar7[1] < piVar7[3]) {
                    int iVar6c = piVar7[1];
                    uint uVar2 = (uint)piVar7[-1];
                    do {
                        int iVar8 = *piVar7;
                        if (iVar8 < piVar7[2]) {
                            do {
                                int iVar3 = *(int*)(local_7c + 0x24);
                                uint* puVar1 = (uint*)(*(int*)(local_7c + 0x34) + 4 +
                                    ((iVar3 * (int)uVar2 + iVar6c) * iVar3 + iVar8) * 0xc);
                                uint uVar4 = *puVar1;
                                if ((uVar4 & 7) == 0) {
                                    float fVar11 = (((float)iVar6c + 0.5f) * (1.0f / (float)iVar3)) * 2.0f - 1.0f;
                                    fVar10 = (((float)iVar8 + 0.5f) * (1.0f / (float)iVar3)) * 2.0f - 1.0f;
                                    int iVar3b = ((int)uVar2 >> 1) * 4;
                                    fVar9 = 1.0f / (float)sqrt((double)((fVar10 * fVar10 + fVar11 * fVar11) + 1.0f));
                                    fVar12 = fVar9;
                                    if ((uVar2 & 1) != 0)
                                        fVar12 = -fVar9;
                                    float local_8c[4];
                                    local_8c[kCellBasis[iVar3b]] = fVar12 * fVar10;
                                    local_8c[kCellBasis[iVar3b + 1]] = fVar9 * fVar11;
                                    local_8c[kCellBasis[iVar3b + 2]] = fVar12;
                                    fVar9 = ((local_8c[2] - local_a8) * (local_8c[2] - local_a8) +
                                             (local_8c[1] - local_ac) * (local_8c[1] - local_ac)) +
                                            (local_8c[0] - local_b0) * (local_8c[0] - local_b0);
                                    if ((fVar9 <= local_9c) && (0.0f < local_9c))
                                        *puVar1 = uVar4 | 0x10;
                                    if ((fVar9 <= local_94) && (0.0f < local_94))
                                        *puVar1 = *puVar1 | 0x20;
                                    if ((fVar9 <= local_90) && (0.0f < local_90))
                                        *puVar1 = *puVar1 | 0x40;
                                }
                                iVar8 = iVar8 + 1;
                            } while (iVar8 < piVar7[2]);
                        }
                        iVar6c = iVar6c + 1;
                    } while (iVar6c < piVar7[3]);
                }
                piVar7 = piVar7 + 5;
                local_c4 = local_c4 - 1;
            } while (local_c4 != 0);
        }
    }
}
