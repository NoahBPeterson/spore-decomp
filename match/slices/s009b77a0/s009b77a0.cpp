// @ 0x009b77a0 .. slice s009b77a0  (batch gold1, slices 64-67)
// Target module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Context: nSPCreatureAnim::creature_instance_data gait / style-weight helpers.
#include "types.h"

// --- externals (names irrelevant to byte comparison: call rel32 is masked) ----------
extern "C" int DAT_01485720;      // 0x01485720  (float 1.0)
extern "C" int DAT_014471fc;      // 0x014471fc  (float eps)
extern "C" int DAT_01550d60;      // 0x01550d60  (float)
extern "C" int DAT_0166c1d8;      // 0x0166c1d8  (float)
extern "C" int DAT_01550c34;      // 0x01550c34  (float)
extern "C" int DAT_01550b1c;      // 0x01550b1c  (float)
extern "C" char DAT_013eb8b0[];   // 0x013eb8b0  (16-byte sign mask)
extern "C" int DAT_013f27a8[];    // 0x013f27a8  ("default")
extern "C" double sqrt(double);
extern "C" double exp(double);

int* __fastcall GetPoliticalID(int this_);                       // 0x0097e850
int* __fastcall FUN_00a09f50(int this_);                         // 0x00a09f50
int* __fastcall FUN_00ff3ba0(int this_);                         // 0x00ff3ba0
extern "C" void* FUN_0099c310(void* out, void* a, void* b);      // 0x0099c310
extern "C" void  FUN_009b4ba0(void* out, void* q, void* v);      // 0x009b4ba0
extern "C" void* FUN_009a49d0(void* out, void* v, int f);        // 0x009a49d0
int  __fastcall FUN_009ce410(int this_);                         // 0x009ce410
extern "C" void  Sprintf8(void* buf, const char* fmt);           // 0x00938470
char __fastcall FUN_009b78c0(int this_, int dummy, int param_2, int param_3, int param_4);
char __fastcall FUN_009b3850(int a, int dummy, void* b, void* c, int d);   // ComposeGaitFileName
int  __fastcall FUN_009e5b40(int a, int dummy, void* b, int c, int d);
int  __fastcall FUN_009e18c0(int a, int dummy, void* b, int c, int d);     // LoadGaitFile
int  __fastcall FUN_009dbe10(int a, int dummy, int b, int c, int d);
int  __fastcall FUN_009e4350(int a, int dummy, int b, int c);
int  __fastcall FUN_009e3790(int a, int dummy, void* b);
int  __fastcall FUN_009e4450(int a, int dummy, float f, int b, int c, int d);
int  __fastcall FUN_009d24c0(int a, int dummy, int b, int c, int d, int e, int f);
float __fastcall FUN_009dc7a0(int a, int dummy, void* b);
int  __fastcall FUN_009d0c80(int a);
int  __fastcall FUN_009dfc40(int a);
int  __fastcall FUN_009d1050(int a);

// ===========================================================================
// 0x009b77a0  project a point onto a circle of radius (speed*scale) around a bone
// ===========================================================================
// @ 0x009b77a0
void FUN_009b77a0(float* param_1, int param_2, int param_3, float* param_4, char* param_5)
{
    int iVar4 = *(int*)(param_2 + 0x2e4);
    float fVar1 = *(float*)(iVar4 + 0x18);
    float fVar2 = *(float*)(iVar4 + 0x10);
    float fVar3 = *(float*)(iVar4 + 0x14);
    float fVar5 = *(float*)(*(int*)(param_3 * 700 + iVar4) + 0x36c) * *(float*)(param_2 + 0x70);
    float fVar7 = param_4[2] - fVar1;
    float fVar9 = *param_4 - fVar2;
    float fVar6 = param_4[1] - fVar3;
    float fVar8 = (fVar9 * fVar9 + fVar7 * fVar7) + fVar6 * fVar6;
    if (fVar5 * fVar5 < fVar8) {
        fVar8 = (float)(1.0 / sqrt((double)fVar8));
        if (param_5 != 0) *param_5 = 1;
        *param_1 = (fVar8 * fVar9) * fVar5 + fVar2;
        param_1[1] = (fVar6 * fVar8) * fVar5 + fVar3;
        param_1[2] = (fVar8 * fVar7) * fVar5 + fVar1;
        return;
    }
    if (param_5 != 0) *param_5 = 0;
    *param_1 = *param_4;
    param_1[1] = param_4[1];
    param_1[2] = param_4[2];
}

// ===========================================================================
// 0x009b78c0  nSPCreatureAnim::creature_instance_data::LoadGaitRecord
// ===========================================================================
// @ 0x009b78c0
char __fastcall FUN_009b78c0(int param_1, int dummy, int param_2, int param_3, int param_4)
{
    (void)dummy;
    int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
    piVar2 = (int*)(param_2 * 0x104 + *piVar2);
    int iVar4 = *piVar2;
    char* local_1a8;
    if ((iVar4 < 0) || (7 < iVar4)) local_1a8 = 0;
    else local_1a8 = (char*)*(int*)(0x01550c0c + iVar4 * 4);
    char local_1a0[416];
    int local_1a4;
    if (iVar4 == 7) {
        Sprintf8(local_1a0, "default");
        local_1a4 = FUN_009e5b40(param_1 + 0x2f8, 0, local_1a0, (int)piVar2, param_4);
    } else {
        char cVar1 = FUN_009b3850(param_1, 0, local_1a0, local_1a8, param_3);
        if (cVar1 != 0) {
            int uVar3 = FUN_009ce410((int)piVar2);
            local_1a4 = FUN_009e18c0(param_1 + 0x2f8, 0, local_1a0, uVar3, param_4);
            if (local_1a4 != 0) goto LAB_009b79ca;
        }
        cVar1 = FUN_009b3850(param_1, 0, local_1a0, local_1a8, 0);
        if (cVar1 == 0) return 0;
        int uVar3 = FUN_009ce410((int)piVar2);
        local_1a4 = FUN_009e18c0(param_1 + 0x2f8, 0, local_1a0, uVar3, param_4);
    }
    if (local_1a4 == 0) return 0;
LAB_009b79ca:
    {
        int iVar5 = *(int*)(param_1 + param_2 * 4 + 0x2fc);
        if (param_4 == iVar5) *(int*)(param_1 + param_2 * 4 + 0x2fc) = iVar5 + 1;
        if (param_4 == 0) *(int*)(param_1 + (param_4 + param_2 * 4) * 4 + 0x374) = 0x3f800000;
        else *(int*)(param_1 + (param_4 + param_2 * 4) * 4 + 0x374) = 0;
        int uVar3 = FUN_009ce410((int)piVar2);
        iVar5 = FUN_009dbe10(param_1 + 0x2f8, 0, local_1a4, uVar3, param_4);
        if (iVar5 != 0) {
            *(int*)(param_1 + 0x434) = param_2 + 1;
            int uVar4 = FUN_009d0c80((int)piVar2);
            int inner[45];
            FUN_009e4350((int)inner, 0, *piVar2, uVar4);
            int index = param_4 + param_2 * 4;
            int dest = param_1 + 0x440 + index * 0xb4;
            FUN_009e3790(dest, 0, inner);
            FUN_009dfc40((int)inner);
            float fVar5 = FUN_009dc7a0(param_1 + 0x2f8, 0, (void*)(param_1 + 0x264));
            float fVar6 = 1.0f;
            if (1e-06f < *(float*)(param_1 + 0x70)) fVar6 = 1.0f / *(float*)(param_1 + 0x70);
            FUN_009e4450(param_1 + 0x2f8, 0, fVar6 * fVar5, param_4, 0, 0);
            int a = *(int*)(param_1 + param_2 * 4 + 0x2fc);
            int b = param_1 + param_2 * 0x10 + 0x374;
            int c = param_1 + param_2 * 0x10 + 0x3d4;
            int d = param_1 + param_2 * 0x2d0 + 0x438;
            int e = param_1 + 0x434;
            FUN_009d24c0((int)piVar2, 0, a, b, c, d, e);
            FUN_009d1050((int)piVar2);
        }
    }
    return 1;
}

// ===========================================================================
// 0x009b7b10  iterate all groups, loading gait records
// ===========================================================================
// @ 0x009b7b10
char __fastcall FUN_009b7b10(int param_1, int dummy, int param_2, int param_3)
{
    (void)dummy;
    int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
    int iVar1 = (piVar2[1] - *piVar2) / 0x104;
    int iVar4 = 0;
    char uVar3 = 1;
    if (0 < iVar1) {
        do {
            uVar3 = FUN_009b78c0(param_1, 0, iVar4, param_2, param_3);
            iVar4 = iVar4 + 1;
        } while (iVar4 < iVar1);
    }
    return uVar3;
}

// ===========================================================================
// 0x009b7b70  nSPCreatureAnim::creature_instance_data::SetStyleWeightForAllGroups
// ===========================================================================
namespace nSPCreatureAnim {
struct creature_instance_data {
    void SetStyleWeightForAllGroups(int param_2, int param_3, float param_4);
};
}

// @ 0x009b7b70
void nSPCreatureAnim::creature_instance_data::SetStyleWeightForAllGroups(int param_2, int param_3, float param_4)
{
    int iVar4 = 0;
    if (0 < *(int*)((char*)this + 0x2f8)) {
        float* local_4 = (float*)((char*)this + 0x3d4);
        int* pcVar6 = (int*)((char*)this + 0x2fc);
        float* pcVar5 = (float*)((char*)this + param_3 * 4 + 0x374);
        do {
            if (*(int*)((char*)pcVar5 - 0x60) == 0) {
                FUN_009b78c0((int)this, 0, iVar4, param_2, param_3);
            }
            int iVar3 = 0;
            float* pcVar2 = local_4;
            if (0 < *pcVar6) {
                do {
                    iVar3 = iVar3 + 1;
                    *pcVar2 = *(float*)((char*)pcVar2 - 0x60);
                    pcVar2 = pcVar2 + 1;
                } while (iVar3 < *pcVar6);
            }
            local_4 = local_4 + 4;
            *(int*)((char*)this + 0x434) = 5;
            *pcVar5 = param_4;
            iVar4 = iVar4 + 1;
            pcVar5 = pcVar5 + 4;
            pcVar6 = pcVar6 + 1;
        } while (iVar4 < *(int*)((char*)this + 0x2f8));
    }
}

// ===========================================================================
// 0x009b7c00  blend a target velocity into the accumulated displacement
// ===========================================================================
// @ 0x009b7c00
void* __fastcall FUN_009b7c00(int param_1, int dummy, float param_2, float* param_3, float param_4)
{
    (void)dummy;
    float fVar1 = *param_3;
    float fVar2 = param_3[2];
    float fVar6 = 1.0f / param_2;
    float fVar7;
    if (*(float*)&DAT_01550d60 * param_2 <= -(*(float*)&DAT_0166c1d8)) {
        fVar7 = (float)exp((double)(-(*(float*)&DAT_01550d60 * param_2)));
    } else {
        fVar7 = 0.0f;
    }
    float fVar5 = 1.0f - fVar7;
    *(float*)(param_1 + 0x1674) =
        *(float*)(param_1 + 0x1674) * fVar7 + ((*(float*)(param_1 + 0x1664) - param_3[1]) * fVar6) * fVar5;
    *(float*)(param_1 + 0x1670) =
        *(float*)(param_1 + 0x1670) * fVar7 + ((*(float*)(param_1 + 0x1660) - fVar1) * fVar6) * fVar5;
    *(float*)(param_1 + 0x1678) =
        *(float*)(param_1 + 0x1678) * fVar7 + ((*(float*)(param_1 + 0x1668) - fVar2) * fVar6) * fVar5;
    *(float*)(param_1 + 0x167c) =
        fVar5 * ((*(float*)(param_1 + 0x166c) - param_4) * fVar6) + fVar7 * *(float*)(param_1 + 0x167c);
    float d = *(float*)&DAT_01550c34;
    if ((*(float*)(param_1 + 0x1670) * *(float*)(param_1 + 0x1670) +
         *(float*)(param_1 + 0x1674) * *(float*)(param_1 + 0x1674)) +
        *(float*)(param_1 + 0x1678) * *(float*)(param_1 + 0x1678) < d) {
        *(float*)(param_1 + 0x1670) = 0.0f;
        *(float*)(param_1 + 0x1674) = 0.0f;
        *(float*)(param_1 + 0x1678) = 0.0f;
    }
    if (*(float*)(param_1 + 0x167c) * *(float*)(param_1 + 0x167c) < d) {
        *(float*)(param_1 + 0x167c) = 0.0f;
    }
    return param_3;
}

// ===========================================================================
// 0x009b7da0  compute the accumulated root motion displacement / heading
// ===========================================================================
// @ 0x009b7da0
void __fastcall FUN_009b7da0(int param_1, int dummy, float param_2)
{
    (void)dummy;
    float fVar6 = 1.0f / *(float*)(param_1 + 0x70);
    float out[3];
    float vec[3];
    float quat[4];
    float zero[3];
    float rot[4];
    float scaled[3];
    float dir[3];
    if (*(char*)(param_1 + 0x263) == '\0') {
        if (param_2 <= 1e-06f) param_2 = 0.0f;
        else param_2 = 1.0f / param_2;
        float* pfVar3 = (float*)(param_1 + 0x1660);
        *pfVar3 = (*(float*)(param_1 + 0x18) - *(float*)(param_1 + 0x1644)) * param_2;
        *(float*)(param_1 + 0x1664) = (*(float*)(param_1 + 0x1c) - *(float*)(param_1 + 0x1648)) * param_2;
        *(float*)(param_1 + 0x1668) = (*(float*)(param_1 + 0x20) - *(float*)(param_1 + 0x164c)) * param_2;
        float fVar5 = *(float*)(param_1 + 0xd8);
        if (0.0f < fVar5) {
            *pfVar3 = *pfVar3 - (fVar5 * *(float*)(param_1 + 0xdc)) * param_2;
            *(float*)(param_1 + 0x1664) = *(float*)(param_1 + 0x1664) - (*(float*)(param_1 + 0xe0) * fVar5) * param_2;
            *(float*)(param_1 + 0x1668) = *(float*)(param_1 + 0x1668) - (*(float*)(param_1 + 0xe4) * fVar5) * param_2;
        }
        float* pfVar4 = (float*)FUN_0099c310(out, (float*)(param_1 + 0x3c), pfVar3);
        *pfVar3 = pfVar4[0];
        *(float*)(param_1 + 0x1664) = pfVar4[1];
        *(float*)(param_1 + 0x1668) = pfVar4[2];
        *(float*)(param_1 + 0x1668) = 0.0f;
        *pfVar3 = *pfVar3 * fVar6;
        *(float*)(param_1 + 0x1664) = *(float*)(param_1 + 0x1664) * fVar6;
        float g0 = *(float*)(param_1 + 0x3c);
        float g1 = *(float*)(param_1 + 0x40);
        float g2 = *(float*)(param_1 + 0x44);
        float h0 = -*(float*)(param_1 + 0x1650);
        float h1 = -*(float*)(param_1 + 0x1654);
        float h2 = -*(float*)(param_1 + 0x1658);
        float g3 = *(float*)(param_1 + 0x48);
        quat[0] = ((g0 * *(float*)(param_1 + 0x165c) + g3 * h0) - g2 * h1) + g1 * h2;
        quat[1] = ((g1 * *(float*)(param_1 + 0x165c) + g3 * h1) + g2 * h0) - g0 * h2;
        quat[2] = ((g2 * *(float*)(param_1 + 0x165c) - g1 * h0) + g0 * h1) + g3 * h2;
        quat[3] = ((g3 * *(float*)(param_1 + 0x165c) - g0 * h0) - g1 * h1) - g2 * h2;
        zero[0] = 0.0f;
        zero[1] = 0.0f;
        zero[2] = 0.0f;
        FUN_009b4ba0(rot, quat, zero);
        rot[3] = rot[3] * param_2;
        scaled[0] = rot[0] * rot[3];
        scaled[1] = rot[1] * rot[3];
        scaled[2] = rot[2] * rot[3];
        dir[1] = 0.0f;
        float fVar10 = 1.0f, fVar5b = 0.0f, fVar6b = 0.0f;
        if ((*(char**)(param_1 + 0x1688) != 0) && (**(char**)(param_1 + 0x1688) != '\0')) {
            fVar5b = *(float*)(param_1 + 0x18);
            if ((fVar5b * fVar5b + *(float*)(param_1 + 0x1c) * *(float*)(param_1 + 0x1c)) +
                *(float*)(param_1 + 0x20) * *(float*)(param_1 + 0x20) <= 0.01f) {
                fVar5b = 0.0f;
            } else {
                float* pfVar3b = (float*)FUN_009a49d0(dir, (float*)(param_1 + 0x18), 0);
                fVar6b = pfVar3b[0];
                fVar5b = pfVar3b[1];
                fVar10 = pfVar3b[2];
            }
        }
        fVar6 = (fVar10 * scaled[2] + fVar5b * scaled[1]) + fVar6b * scaled[0];
    } else {
        vec[0] = *(float*)(param_1 + 0x264) * fVar6;
        vec[1] = *(float*)(param_1 + 0x268) * fVar6;
        vec[2] = 0.0f;
        float* puVar2 = (float*)FUN_0099c310(out, (void*)(param_1 + 0x3c), vec);
        *(float*)(param_1 + 0x1660) = puVar2[0];
        *(float*)(param_1 + 0x1664) = puVar2[1];
        *(float*)(param_1 + 0x1668) = puVar2[2];
        *(float*)(param_1 + 0x1668) = 0.0f;
        float fVar1 = *(float*)(param_1 + 0x18);
        float fVar10 = 1.0f, fVar6b = 0.0f, fVar5b = 0.0f;
        if (((*(char**)(param_1 + 0x1688) != 0) && (**(char**)(param_1 + 0x1688) != '\0')) &&
            (0.01f < (fVar1 * fVar1 + *(float*)(param_1 + 0x1c) * *(float*)(param_1 + 0x1c)) +
                      *(float*)(param_1 + 0x20) * *(float*)(param_1 + 0x20))) {
            float* pfVar3b = (float*)FUN_009a49d0(dir, (float*)(param_1 + 0x18), 0);
            fVar6b = pfVar3b[0];
            fVar5b = pfVar3b[1];
            fVar10 = pfVar3b[2];
        }
        fVar6 = (fVar5b + fVar6b) * 0.0f + *(float*)(param_1 + 0x26c) * fVar10;
    }
    *(float*)(param_1 + 0x166c) = fVar6;
    if (!(fVar6 > -6.2831855f)) fVar6 = -6.2831855f;
    else if (!(fVar6 <= 6.2831855f)) fVar6 = 6.2831855f;
    *(float*)(param_1 + 0x166c) = fVar6;
}

// ===========================================================================
// 0x009b8250  propagate a style weight to all bone-instance speed limits
// ===========================================================================
// @ 0x009b8250
void __fastcall FUN_009b8250(int param_1, int dummy, float param_2)
{
    (void)dummy;
    int* piVar3 = FUN_00a09f50(param_1 + 0x15b8);
    unsigned n = (unsigned)((piVar3[1] - *piVar3) / 0x108);
    for (unsigned i = 0; i < n; i++) {
        int eax = *(int*)(*piVar3 + 0x58 + i * 0x108) * 700 + *(int*)(param_1 + 0x2e4);
        float fVar1 = *(float*)(eax + 0x48);
        if (fVar1 < param_2) *(float*)(eax + 0x4c) = param_2 - fVar1;
    }
}

// ===========================================================================
// 0x009b83b0  blend per-group style weights and apply them
// ===========================================================================
// @ 0x009b83b0
void __fastcall FUN_009b83b0(int param_1, int dummy, float param_2)
{
    (void)dummy;
    int iVar2;
    int* piVar4;
    int* piVar5;
    float fVar9;
    float fVar10;
    float fVar11;
    piVar4 = FUN_00a09f50(param_1 + 0x15b8);
    int iVar8 = *piVar4;
    fVar10 = 0.0f;
    fVar11 = 0.0f;
    unsigned uVar3 = (piVar4[1] - iVar8) / 0x108;
    unsigned uVar6 = 0;
    if (1 < (int)uVar3) {
        int iVar7 = (uVar3 - 2 >> 1) + 1;
        uVar6 = iVar7 * 2;
        piVar4 = (int*)(iVar8 + 0x160);
        do {
            iVar2 = *piVar4;
            fVar10 = *(float*)(*(int*)(param_1 + 0x2e4) + 0x4c + piVar4[-0x42] * 700) + fVar10;
            piVar4 = piVar4 + 0x84;
            iVar7 = iVar7 + -1;
            fVar11 = *(float*)(*(int*)(param_1 + 0x2e4) + 0x4c + iVar2 * 700) + fVar11;
        } while (iVar7 != 0);
    }
    if (uVar6 < uVar3) {
        fVar9 = *(float*)(*(int*)(uVar6 * 0x108 + 0x58 + iVar8) * 700 + 0x4c + *(int*)(param_1 + 0x2e4));
    } else {
        fVar9 = 0.0f;
    }
    fVar9 = (fVar10 + fVar11) + fVar9;
    if (uVar3 != 0) {
        fVar10 = (float)(int)uVar3;
        if ((int)uVar3 < 0) fVar10 = fVar10 + 4.2949673e+09f;
        fVar9 = fVar9 / fVar10;
    }
    if (1e-06f < fVar9) {
        iVar8 = *(int*)(param_1 + 0x2e4);
        if (param_2 <= 1e-06f) fVar10 = 0.0f;
        else fVar10 = fVar9 / param_2;
        fVar10 = (1.0f - fVar10) * *(float*)&DAT_01550b1c + (1.0f - *(float*)&DAT_01550b1c);
        fVar11 = *(float*)(iVar8 + 0x48) * fVar10;
        *(float*)(iVar8 + 0x48) = fVar11;
        *(float*)(iVar8 + 0x4c) = param_2 - fVar11;
        *(float*)(iVar8 + 0x88) = *(float*)(iVar8 + 0x88) * fVar10;
        *(float*)(iVar8 + 0x9c) = *(float*)(iVar8 + 0x9c) * fVar10;
        piVar4 = FUN_00a09f50(param_1 + 0x15b8);
        piVar5 = GetPoliticalID(param_1 + 0x15b8);
        iVar8 = (piVar5[1] - *piVar5) / 0x104;
        if (iVar8 != 0) {
            int iVar7 = 0;
            do {
                piVar5 = GetPoliticalID(param_1 + 0x15b8);
                iVar2 = *piVar5;
                uVar6 = (unsigned)(*(int*)(iVar2 + 8 + iVar7) + *(int*)(iVar2 + 4 + iVar7)) >> 1;
                if (uVar6 != *(unsigned*)(iVar2 + iVar7 + 0xc)) {
                    iVar2 = *(int*)(uVar6 * 0x30 + 4 + *piVar4);
                    if (param_2 <= 1e-06f) fVar10 = 0.0f;
                    else fVar10 = fVar9 / param_2;
                    fVar10 = (1.0f - fVar10) * *(float*)&DAT_01550b1c + (1.0f - *(float*)&DAT_01550b1c);
                    fVar11 = *(float*)(iVar2 + 0x48) * fVar10;
                    *(float*)(iVar2 + 0x48) = fVar11;
                    *(float*)(iVar2 + 0x4c) = param_2 - fVar11;
                    *(float*)(iVar2 + 0x88) = *(float*)(iVar2 + 0x88) * fVar10;
                    *(float*)(iVar2 + 0x9c) = *(float*)(iVar2 + 0x9c) * fVar10;
                }
                iVar7 = iVar7 + 0x104;
                iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
        }
    }
}

// ===========================================================================
// 0x009b8650  set a shared speed limit across all groups of all political IDs
// ===========================================================================
// @ 0x009b8650
void __fastcall FUN_009b8650(int param_1, int dummy, float param_2)
{
    (void)dummy;
    param_2 = param_2 - *(float*)(*(int*)(param_1 + 0x2e4) + 0x48);
    if (1e-06f < param_2) {
        *(float*)(*(int*)(param_1 + 0x2e4) + 0x4c) = param_2;
        int* piVar2 = GetPoliticalID(param_1 + 0x15b8);
        int iVar1 = (piVar2[1] - *piVar2) / 0x104;
        int ebp = 0;
        while (iVar1 != 0) {
            int esi = *GetPoliticalID(param_1 + 0x15b8) + ebp;
            int* piVar2b = FUN_00ff3ba0(esi);
            int iVar3 = (piVar2b[1] - *piVar2b) / 0x38;
            if (iVar3 != 0) {
                int iVar4 = 0;
                do {
                    piVar2b = FUN_00ff3ba0(esi);
                    int* p = (int*)(iVar4 + *piVar2b);
                    iVar4 = iVar4 + 0x38;
                    iVar3 = iVar3 + -1;
                    *(float*)(*p + 0x4c) = param_2;
                } while (iVar3 != 0);
            }
            ebp = ebp + 0x104;
            iVar1 = iVar1 + -1;
        }
    }
}
