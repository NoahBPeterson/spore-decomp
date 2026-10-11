// @ 0x009a7810 .. slice s009a7810  (batch gold1, slices 64-67)
// Target module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Context: nSPCreatureAnim event dispatch (HandleEvent/HandleEvents/HandleAnimationEvents),
//          event-version converters and the deform/property lookup tables.
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers / globals from the rest of the image.
// ---------------------------------------------------------------------------
extern "C" void  operator_new__(void* p, int a, int b);   // 0x011e073e (lib_crt placement init)
extern "C" uint32_t FUN_009a4660(uint32_t a, uint32_t b); // 0x009a4660 BitMatch (defined in s009a4c70)
extern "C" uint32_t FUN_009a5860(uint32_t a0, void* a1, int a2, int a3, void* creature,
                                 uint32_t index, uint32_t defaultValue, int a7); // 0x009a5860
extern "C" char FUN_0099c710(uint32_t a, uint32_t b, uint32_t c);
extern "C" uint32_t FUN_0099d2b0(uint32_t a, int b, int c);
struct CppRandom { double GenerateDouble(); };
extern "C" double FUN_009362d0();

void FUN_009a7810(int, int, int, int, int*, uint32_t, int, uint32_t*, int);
void FUN_009a7d90(uint32_t*, int, int, uint32_t*, int, int, int, int, int, int, uint32_t, float, int);

extern uint32_t DAT_015506c8[];   // deform rbtree overload table
extern char DAT_015507a8[];       // property-name table (0x1c stride, 20 entries)

namespace nSPCreatureAnim {
    namespace converters {
        void ConvertEvent_v11_v12(uint32_t* src, uint32_t* dst);
        void ConvertEvent_v9_v10(uint32_t* src, uint32_t* dst);
    }
    uint32_t ComputeAnimationStaticDataSizeBytesForVersion(int p);
    uint32_t ComputeEventLocationData(uint32_t flags, uint32_t* p2, uint32_t p3, uint32_t* owner,
                                      uint32_t p5, int p6, int* outLoc, int* outLoc2, uint8_t* outByte);
    void ComputeEventLocationState(int a0, uint32_t flags, uint32_t a2, uint32_t a3, int a4,
                                   uint32_t a5, uint32_t a6, void* a7, void* a8, void* a9,
                                   void* a10, void* a11, void* a12, void* a13, int a14);
    uint8_t ContextFilterEventLocationData(uint32_t a0, uint32_t a1, int* buf, uint32_t a3, uint32_t a4);
    int* GetAvailableDeformsForContextTarget(uint32_t* p, uint32_t* out);
}

// ===========================================================================
// 0x009a7810  nSPCreatureAnim::HandleEvent
// ===========================================================================
extern "C" void FUN_009a6e60(int a0, int a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5,
                              uint32_t a6, uint32_t a7, void* a8, void* a9, void* a10, uint32_t a11,
                              void* a12, int a13, int a14, uint32_t a15, int* a16, int a17, int a18,
                              uint32_t* a19, int a20);

// A "location candidate set": count followed by up to 254 candidate ids.
struct LocData { int count; int items[254]; };

// @ 0x009a7810
void FUN_009a7810(int param_1, int param_2, int param_3, int param_4, int* param_5, uint32_t param_6,
                  int param_7, uint32_t* param_8, int param_9)
{
    LocData local_A, local_B, local_D;
    int local_1034 = 0;
    uint32_t local_102c;
    int local_1064;
    int local_1060;
    uint32_t local_1044 = 0, local_103c = 0, local_104c = 0;
    uint32_t local_1048, local_1050;
    char local_1066 = 0, local_1065 = 0, local_1068 = 0;
    char local_1067 = 0;
    float local_1058;
    uint32_t local_101c;
    uint32_t local_1040, local_1030, local_1038;
    uint32_t local_105c, local_1054, local_1053x;
    uint8_t local_1018[12];
    uint8_t local_100c[16];
    uint8_t local_1028[12];
    uint8_t local_ffc[12];

    local_A.count = -1; operator_new__(&local_A.items[0], 0, 0x3f8);
    local_102c = nSPCreatureAnim::ComputeEventLocationData(param_8[10], param_8 + 0xb, *param_5 + 0x88,
                                                           (uint32_t*)param_2, param_3, param_4,
                                                           &local_1034, &local_A.count, (uint8_t*)&local_1068);
    uint32_t uVar3 = param_8[1];
    if ((uVar3 != param_8[4]) || (param_8[2] != param_8[5]) || (param_8[3] != param_8[6])) {
        local_1064 = 1;
    } else {
        local_1064 = 0;
    }
    if ((uVar3 == param_8[7]) && (param_8[2] == param_8[8]) && (param_8[3] == param_8[9])) {
        local_1060 = 0;
    } else if ((param_8[4] != param_8[7]) || (param_8[5] != param_8[8]) || (param_8[6] != param_8[9])) {
        local_1060 = 2;
    } else {
        local_1060 = 1;
    }
    int iVar4 = local_1060;
    local_1044 = 0; local_103c = 0; local_104c = 0;
    local_1066 = 0; local_1065 = 0; local_1068 = 0;

    local_B.count = -1; operator_new__(&local_B.items[0], 0, 0x3f8);
    local_D.count = -1; operator_new__(&local_D.items[0], 0, 0x3f8);
    LocData local_C;
    local_C.count = -1; operator_new__(&local_C.items[0], 0, 0x3f8);

    uVar3 = nSPCreatureAnim::ComputeEventLocationData(uVar3, param_8 + 2, *param_5 + 0x88,
                                                      (uint32_t*)param_2, param_3, param_4,
                                                      (int*)&local_1044, &local_B.count, (uint8_t*)&local_1066);
    local_101c = uVar3;
    if (local_1064 == 0) {
        local_1048 = 1;
    } else {
        local_1048 = nSPCreatureAnim::ComputeEventLocationData(param_8[4], param_8 + 5, *param_5 + 0x88,
                                                               (uint32_t*)param_2, param_3, param_4,
                                                               (int*)&local_103c, &local_C.count, (uint8_t*)&local_1065);
    }
    if (iVar4 == 2) {
        local_1050 = nSPCreatureAnim::ComputeEventLocationData(param_8[7], param_8 + 8, *param_5 + 0x88,
                                                               (uint32_t*)param_2, param_3, param_4,
                                                               (int*)&local_104c, &local_D.count, (uint8_t*)&local_1068);
    } else {
        local_1050 = 1;
    }
    local_1058 = 1.0f;
    local_1040 = 0;
    if (uVar3 != 0) {
        do {
            local_105c = (uint32_t)((int*)&local_B.count)[local_1040];
            uVar3 = local_1040;
            if (local_1066 == 0) uVar3 = param_6;
            uint32_t uVar1 = param_8[1];
            char cVar2 = (char)nSPCreatureAnim::ContextFilterEventLocationData(
                             uVar1, uVar3, &local_B.count, *(uint32_t*)(param_2 + 0x2ac), local_105c);
            if (cVar2 != 0) {
                if (((*param_8 & 0x8000) == 0) || (local_1067 = 0, local_1064 == 0)) {
                    local_1067 = 1;
                }
                nSPCreatureAnim::ComputeEventLocationState(
                    1, *param_8, uVar1, param_8[0x11], param_2, local_1044, local_105c, local_1018,
                    (void*)(uint32_t)(-(uint32_t)(local_1067 != 0) & (uint32_t)local_1028),
                    (void*)(uint32_t)(~-(uint32_t)(local_1064 != 0) & (uint32_t)local_100c),
                    (void*)(uint32_t)(~-(uint32_t)(iVar4 != 0) & (uint32_t)&local_1058),
                    local_ffc, local_1018, local_1028, param_9);
                local_1030 = 0;
                if (local_1048 != 0) {
                    do {
                        if (local_1064 == 1) {
                            local_1054 = (uint32_t)((int*)&local_C.count)[local_1030];
                            uVar3 = local_1030;
                            if (local_1065 == 0) uVar3 = param_6;
                            uVar1 = param_8[4];
                            cVar2 = (char)nSPCreatureAnim::ContextFilterEventLocationData(
                                        uVar1, uVar3, &local_C.count, *(uint32_t*)(param_2 + 0x2ac), local_105c);
                            if (cVar2 != 0) {
                                nSPCreatureAnim::ComputeEventLocationState(
                                    1, *param_8, uVar1, param_8[0x11], param_2, local_103c, local_1054, 0,
                                    (void*)(uint32_t)(((local_1067 != 0) - 1) & (uint32_t)local_1028),
                                    local_100c,
                                    (void*)(uint32_t)(~-(uint32_t)(iVar4 != 1) & (uint32_t)&local_1058),
                                    0, local_1018, local_1028, param_9);
                                goto LAB_009a7c23;
                            }
                        } else {
                            local_1054 = local_105c;
LAB_009a7c23:
                            local_1038 = 0;
                            if (local_1050 != 0) {
                                do {
                                    if (iVar4 == 2) {
                                        uint32_t uVar5 = (uint32_t)((int*)&local_D.count)[local_1038];
                                        uVar3 = local_1038;
                                        if (local_1068 == 0) uVar3 = param_6;
                                        uVar1 = param_8[7];
                                        cVar2 = (char)nSPCreatureAnim::ContextFilterEventLocationData(
                                                    uVar1, uVar3, &local_D.count,
                                                    *(uint32_t*)(param_2 + 0x2ac), local_105c);
                                        iVar4 = local_1060;
                                        if (cVar2 != 0) {
                                            nSPCreatureAnim::ComputeEventLocationState(
                                                1, *param_8, uVar1, param_8[0x11], param_2, local_104c,
                                                uVar5, 0, 0, 0, &local_1058, 0, local_1018, local_1028, param_9);
                                            iVar4 = local_1060;
                                            goto LAB_009a7cc7;
                                        }
                                    } else {
                                        uint32_t uVar5 = local_1054;
                                        if (iVar4 != 1) uVar5 = local_105c;
LAB_009a7cc7:
                                        FUN_009a6e60(param_1, param_2, local_1044, local_103c, local_104c,
                                                     local_105c, local_1054, uVar5, local_1018, local_1028,
                                                     local_100c, (uint32_t)local_1058, local_ffc, local_1064,
                                                     iVar4, local_1034, &local_A.count, local_102c, param_7,
                                                     param_8, param_9);
                                    }
                                    local_1038 = local_1038 + 1;
                                } while (local_1038 < local_1050);
                            }
                        }
                        local_1030 = local_1030 + 1;
                    } while (local_1030 < local_1048);
                }
            }
            local_1040 = local_1040 + 1;
        } while (local_1040 < local_101c);
    }
}

// ===========================================================================
// 0x009a7d90  nSPCreatureAnim::HandleEvents
// ===========================================================================
// @ 0x009a7d90
void FUN_009a7d90(uint32_t* param_1, int param_2, int param_3, uint32_t* param_4, int param_5,
                  int param_6, int param_7, int param_8, int param_9, int param_10, uint32_t param_11,
                  float param_12, int param_13)
{
    bool bVar2 = false;
    for (;;) {
        if (param_2 == 0) return;
        if (((param_10 == 0) || ((*param_1 & 8) == 0)) &&
            (((*param_1 & 0x1000000) == 0) ||
             (FUN_0099c710(*param_4, param_1[0x14], param_1[0x15]) != 0))) {
            uint32_t uVar8 = *param_1;
            uint8_t bVar6 = 0;
            uint8_t bVar1 = 1;
            uint32_t uVar4 = 0x20007;
            while ((uVar8 != 0) && (uVar4 != 0)) {
                uint32_t uVar7 = (uVar4 - 1) & uVar4;
                uVar4 = uVar7 ^ uVar4;
                bVar6 = (uint8_t)(bVar6 | (uint8_t)(-(uint32_t)((uVar4 & uVar8) != 0) & bVar1));
                uVar8 = uVar8 & ~uVar4;
                bVar1 = (uint8_t)(bVar1 * 2);
                uVar4 = uVar7;
            }
            if ((param_12 < (float)(int)param_1[0x12]) || ((param_11 & (1u << (bVar6 & 0x1f))) != 0)) {
                uint32_t uVar9 = param_1[0xd];
                if (uVar9 != 0) {
                    if (uVar9 == param_4[0xaa]) {
                        bVar2 = true;
                    } else if ((uVar9 != 0xffffffff) || (param_4[0xaa] == 0)) {
                        if (!bVar2) goto LAB_009a7ef7;
                    } else {
                        goto LAB_009a7ef7;
                    }
                }
                if ((*param_1 & 0x2000000) != 0) {
                    float fVar5 = (float)FUN_009a5860(*param_1, param_1 + 0x13, 1, 0, (void*)param_4,
                                                      0, 0x3f800000u, param_13);
                    double fVar9 = ((CppRandom*)0x166b4b8)->GenerateDouble();
                    if ((double)fVar5 < fVar9) goto LAB_009a7ef7;
                }
                FUN_009a7810(param_3, (int)param_4, param_5, param_6, (int*)param_7, param_8, param_9,
                             param_1, param_13);
            }
        }
LAB_009a7ef7:
        param_1 = param_1 + 0x18;
        param_2 = param_2 - 1;
    }
}

// ===========================================================================
// 0x009a7f10  nSPCreatureAnim::HandleAnimationEvents
// ===========================================================================
// @ 0x009a7f10
void FUN_009a7f10(int param_1, int param_2, int* param_3, int param_4, int param_5)
{
    uint64_t uVar10 = 1ull << (uint32_t)param_3[3];
    uint32_t uVar6 = (uint32_t)((param_3[0x33] - param_3[0x32]) >> 3);
    int iVar3 = (*(int*)(param_3[2] + 0x20) - *(int*)(param_3[2] + 0x1c)) >> 4;
    uint8_t local_400[1024];
    uint32_t local_424 = 0;
    if (uVar6 != 0) {
        do {
            uint32_t iVar1 = *(uint32_t*)(param_3[0x32] + 4 + local_424 * 8);
            uint32_t uVar8 = (uint32_t)*(uint16_t*)(param_3[0x32] + local_424 * 8);
            int iVar7 = 0;
            if (iVar3 != 0) {
                int local_428 = 0;
                int local_420 = iVar3;
                do {
                    uint32_t* puVar5 = (uint32_t*)(*(int*)(param_3[2] + 0x1c) + local_428);
                    if ((((*puVar5 & (uint32_t)uVar10) != 0) || ((puVar5[1] & (uint32_t)(uVar10 >> 0x20)) != 0)) &&
                        ((*(uint8_t*)((int)puVar5 + 0xf) & 4) == 0)) {
                        char cVar2 = (char)puVar5[3];
                        if (cVar2 == -1) cVar2 = 0;
                        uint32_t local_418;
                        if (*(uint8_t*)((int)puVar5 + 0xe) == 0xff) local_418 = 0xffffffff;
                        else local_418 = (uint32_t)*(uint8_t*)((int)puVar5 + 0xe);
                        if (uVar8 == (uint32_t)*(uint8_t*)((int)puVar5 + 0xd)) {
                            int* piVar9 = (int*)(uVar8 * 0x1f0 + param_3[5]);
                            int iVar4 = (int)FUN_0099d2b0((uint32_t)*piVar9, 0, -1);
                            iVar4 = *(int*)(iVar4 + 0xc) * (int)iVar1 + *(int*)(*piVar9 + 0xd8) + *(int*)(iVar4 + 8);
                            *(int*)(piVar9[0x77] + (int)iVar1 * 4) = param_3[0x30];
                            FUN_009a7d90((uint32_t*)((uint32_t)*(uint16_t*)(iVar4 + 8) * 0x60 + *(int*)(*param_3 + 0x140)),
                                         *(uint8_t*)(iVar4 + 10), param_1, (uint32_t*)param_2, cVar2, (int)local_418,
                                         (int)piVar9, iVar7, param_3[4], param_3[0x31], param_4, (float)param_5,
                                         (int)(size_t)&local_400[0]);
                            iVar7 = iVar7 + 1;
                        }
                    }
                    local_428 = local_428 + 0x10;
                    local_420 = local_420 - 1;
                } while (local_420 != 0);
            }
            local_424 = local_424 + 1;
        } while (local_424 < uVar6);
    }
    (void)local_400;
}

// ===========================================================================
// 0x009a80e0  hashtable equal_range walk
// ===========================================================================
extern "C" void FUN_009c8900();

// @ 0x009a80e0
void FUN_009a80e0(int param_1)
{
    if (*(int*)(param_1 + 4) != 0) {
        int local_10;
        int local_c;
        int local_8;
        int param = *(int*)(param_1 + 0x10);
        // eastl hashtable equal_range(&local_10, &param)  -- not reproduced, unresolved helper.
        FUN_009c8900();
        (void)local_10; (void)local_c; (void)local_8;
    }
}

// ===========================================================================
// 0x009a8170  mask/select bit combine (BitMatch variant)
// ===========================================================================
// @ 0x009a8170
uint32_t FUN_009a8170(uint32_t param_1, uint32_t param_2)
{
    uint32_t uVar2 = 0;
    uint32_t uVar1 = 1;
    while ((param_2 != 0) && (param_1 != 0)) {
        uint32_t uVar3 = param_1 - 1 & param_1;
        uVar2 = uVar2 | (uint32_t)(-(int32_t)((uVar1 & param_2) != 0) & (uVar3 ^ param_1));
        param_2 = param_2 & ~uVar1;
        uVar1 = uVar1 * 2;
        param_1 = uVar3;
    }
    return uVar2;
}

// ===========================================================================
// 0x009a81b0  nSPCreatureAnim::converters::ConvertEvent_v11_v12
// ===========================================================================
// @ 0x009a81b0
void nSPCreatureAnim::converters::ConvertEvent_v11_v12(uint32_t* param_1, uint32_t* param_2)
{
    *param_2 = *param_1;
    uint32_t uVar1 = param_1[2] & 0xfffeefff;
    param_2[10] = uVar1;
    if ((param_1[2] & 0x1000) != 0) param_2[10] = uVar1 | 0x1000;
    param_2[0xb] = param_1[5];
    param_2[0xc] = param_1[6];
    param_2[0xd] = param_1[7];
    param_2[0xe] = param_1[8];
    param_2[0xf] = param_1[9];
    param_2[0x10] = param_1[10];
    param_1[10] = 0;
    param_2[0x11] = param_1[0xb];
    param_2[0x13] = 0; param_2[0x14] = 0; param_2[0x15] = 0; param_2[0x16] = 0; param_2[0x17] = 0;
    *param_2 = *param_2 & 0xffffa7ff;
    if ((*param_1 & 0x800) != 0) *param_2 = *param_2 | 0x4800;
    if ((*param_1 & 0x1800) != 0) *param_2 = *param_2 | 0x1000;
    uVar1 = param_1[1] & 0xfffeefff;
    if ((param_1[1] & 0x1000) != 0) uVar1 = uVar1 | 0x1000;
    param_2[7] = uVar1; param_2[4] = uVar1; param_2[1] = uVar1;
    param_2[8] = param_1[3]; param_2[9] = param_1[4];
    param_2[5] = param_1[3]; param_2[6] = param_1[4];
    param_2[2] = param_1[3]; param_2[3] = param_1[4];
}

// ===========================================================================
// 0x009a8290  nSPCreatureAnim::converters::ConvertEvent_v9_v10
// ===========================================================================
// @ 0x009a8290
void nSPCreatureAnim::converters::ConvertEvent_v9_v10(uint32_t* param_1, uint32_t* param_2)
{
    uint32_t* puVar1 = param_1;
    uint32_t* puVar2 = param_2;
    operator_new__(param_2, 0, 0x60);
    param_2[7] = param_1[1];
    param_2[9] = param_1[2];
    param_2[10] = param_1[3];
    uint32_t uVar7 = *param_1;
    param_1[3] = 0;
    uint32_t acc = 0;
    uint32_t bit = 1;
    uint32_t uVar3 = 0x420;
    while ((uVar7 != 0) && (uVar3 != 0)) {
        uint32_t uVar5 = (uVar3 - 1) & uVar3;
        uVar3 = uVar5 ^ uVar3;
        uint32_t uVar6 = (uint32_t)(-(uint32_t)((uVar3 & uVar7) != 0) & bit);
        bit = bit << 1;
        acc = acc | uVar6;
        uVar7 = uVar7 & ~uVar3;
        uVar3 = uVar5;
    }
    uint32_t res = 0;
    uint32_t bit2 = 1;
    uVar3 = 0xc0;
    while ((acc != 0) && (uVar3 != 0)) {
        uint32_t uVar5 = (uVar3 - 1) & uVar3;
        res = res | (uint32_t)(-(uint32_t)((bit2 & acc) != 0) & (uVar5 ^ uVar3));
        acc = acc & ~bit2;
        bit2 = bit2 * 2;
        uVar3 = uVar5;
    }
    *puVar2 = *puVar2 | res;
    uVar7 = *puVar2;
    if ((*puVar1 & 0x201) == 0x201) {
        if ((*puVar1 & 0x800) != 0) {
            puVar2[0xb] = puVar1[4];
            *puVar2 = uVar7 | 0x200;
        }
    } else {
        puVar2[0xb] = puVar1[5];
        uint32_t uVar4 = FUN_009a4660(0x6000, *puVar1);
        uVar3 = FUN_009a8170(0x300, uVar4);
        *puVar2 = uVar3 | uVar7;
    }
    if ((*puVar1 & 0xc0) == 0) {
        *puVar2 = *puVar2 | 0x20;
    } else if ((*puVar1 & 0xc0) == 0x80) {
        *puVar2 = *puVar2 | 0x10;
    }
    if ((*puVar1 & 0x100) != 0) *puVar2 = *puVar2 | 8;
    if ((*puVar1 & 0x10000) != 0) *puVar2 = *puVar2 | 0x400;
    uVar7 = *puVar1 & 0x201;
    if (0x200 < uVar7) {
        if (uVar7 != 0x201) return;
        *puVar2 = *puVar2 | 3;
        puVar2[1] = puVar2[1] | 0x12;
        puVar2[2] = puVar2[2] | 0x4015;
        return;
    }
    if (uVar7 == 0x200) {
        *puVar2 = *puVar2 | 2;
LAB_009a84a4:
        puVar2[1] = puVar2[1] | 2;
        return;
    }
    if (uVar7 == 0) goto LAB_009a84a4;
    if (uVar7 != 1) return;
    *puVar2 = *puVar2 | 1;
    switch (*puVar1 & 6) {
    case 0:
        puVar2[1] = puVar2[1] | 9;
        if ((*puVar1 & 0x1000) == 0) return;
        puVar2[1] = puVar2[1] | 0x180;
        return;
    case 2:
        goto code_r0x009a8432;
    case 4:
        puVar2[1] = puVar2[1] | 0x15;
        uVar7 = puVar2[1];
        if ((*puVar1 & 0x8008) == 8) goto LAB_009a8478;
        if ((*puVar1 & 0x8008) == 0x8000) { uVar7 = uVar7 | 0x400; goto LAB_009a847d; }
        goto LAB_009a8480;
    case 6:
        break;
    default:
        goto LAB_009a84c2;
    }
    puVar2[1] = puVar2[1] | 0x2000;
code_r0x009a8432:
    puVar2[1] = puVar2[1] | 2;
    uVar7 = puVar2[1];
    if ((*puVar1 & 0x8008) == 8) {
LAB_009a8478:
        uVar7 = uVar7 | 0x200;
LAB_009a847d:
        puVar2[1] = uVar7;
    } else if ((*puVar1 & 0x8008) == 0x8000) {
        uVar7 = uVar7 | 0x400;
        goto LAB_009a847d;
    }
LAB_009a8480:
    if ((*puVar1 & 0x1000) != 0) puVar2[1] = puVar2[1] | 0x180;
    if ((*puVar1 & 0x10) != 0) { *puVar2 = *puVar2 | 0x800; return; }
LAB_009a84c2:
    return;
}

// ===========================================================================
// 0x009a84f0  eastl::rbtree<...>::find
// ===========================================================================
// @ 0x009a84f0
int* rbtree_find(int* param_1, uint32_t param_2, int param_3, uint32_t* param_4)
{
    uint32_t uVar3 = 0;
    int* piVar1 = param_1;
    if (param_2 != 0) {
        do {
            if (*piVar1 == param_3) {
                if (param_4 == 0) return param_1 + uVar3 * 7 + 1;
                uint32_t uVar2 = 0;
                int* q = param_1 + uVar3 * 7 + 1;
                do {
                    if (*q == 0) break;
                    uVar2++;
                    q++;
                } while (uVar2 < 6);
                *param_4 = uVar2;
                return param_1 + uVar3 * 7 + 1;
            }
            uVar3++;
            piVar1 += 7;
        } while (uVar3 < param_2);
    }
    if (param_4 != 0) *param_4 = 0;
    return 0;
}

// ===========================================================================
// 0x009a8560  nSPCreatureAnim::GetAvailableDeformsForContextTarget
// ===========================================================================
// @ 0x009a8560
int* nSPCreatureAnim::GetAvailableDeformsForContextTarget(uint32_t* param_1, uint32_t* param_2)
{
    if ((*param_1 & 0x101c03) == 0) {
        return rbtree_find((int*)&DAT_015506c8, 8, (int)param_1[1], param_2);
    }
    if ((*param_1 & 0x100003) == 1) {
        return rbtree_find((int*)&DAT_015506c8, 8, 0x746f6f72, param_2);
    }
    if (param_2 != 0) *param_2 = 0;
    return 0;
}

// ===========================================================================
// 0x009a85c0  property-name table lookup (stride 0x1c, 20 entries)
// ===========================================================================
// @ 0x009a85c0
int FUN_009a85c0(uint32_t* param_1, uint32_t* param_2)
{
    uint32_t key = *param_1 & 0x100003;
    switch (key) {
    case 0:
        key = param_1[1];
        break;
    case 1:
        key = 0x746f6f72;
        break;
    default:
        goto LAB_009a8613;
    }
    {
        uint32_t m = *param_1 & 0x801c00;
        if ((m == 0x1800) || (m == 0x1c00)) key = param_1[2];
    }
    {
        uint32_t off = 0;
        int i = 0;
        do {
            if (*(uint32_t*)((DAT_015507a8) + off) == key) {
                if (param_2 == 0) goto LAB_009a8650;
                uint32_t c = 0;
                int* q = (int*)(i * 0x1c + 0x15507ac);
                do {
                    if (*q == 0) break;
                    c++;
                    q++;
                } while (c < 6);
                *param_2 = c;
LAB_009a8650:
                return i * 0x1c + 0x15507ac;
            }
            off += 0x1c;
            i++;
        } while (off < 0x230);
    }
LAB_009a8613:
    if (param_2 != 0) *param_2 = 0;
    return 0;
}

// ===========================================================================
// 0x009a8670  nSPCreatureAnim::ComputeAnimationStaticDataSizeBytesForVersion
// ===========================================================================
// @ 0x009a8670
uint32_t nSPCreatureAnim::ComputeAnimationStaticDataSizeBytesForVersion(int param_1)
{
    uint32_t uVar2 = *(uint32_t*)(param_1 + 4);
    uint32_t uVar1 = *(uint32_t*)(param_1 + 8);
    if (uVar1 >= 0xe) return uVar2;
    if (uVar1 <= 9) {
        uVar2 = (*(int*)(param_1 + 0x13c) * 0x60 + 3 + uVar2) & 0xfffffffc;
    }
    if (uVar1 <= 0xd) {
        uVar2 = (uVar2 + 0x203) & 0xfffffffc;
    }
    return uVar2;
}
