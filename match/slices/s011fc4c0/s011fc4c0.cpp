// Slice s011fc4c0 -- 0x11fxxxx region (attribute-mask helpers with per-letter
// dispatch tables).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

typedef unsigned int  uint;
typedef unsigned char byte;

// @ 0x011fcde0 -- FUN_011fcde0
// Walks the NUL-terminated letter list at param_1+0x11 and invokes the
// per-letter handler at &DAT_01719d08 when the letter's mask at &DAT_0171a108
// intersects param_2, passing the parallel dword at param_1+0x34.
void __cdecl FUN_011fcde0(void* param_1, uint param_2) {
    byte* pbVar3 = (byte*)((char*)param_1 + 0x11);
    int* puVar4 = (int*)((char*)param_1 + 0x34);
    do {
        byte bVar1 = *pbVar3;
        uint uVar2 = (uint)bVar1;
        if ((*(uint*)(0x171a108 + uVar2 * 4) & param_2) != 0) {
            (*(void(__cdecl**)(uint, uint, int))(0x1719d08 + uVar2 * 4))(uVar2, param_2, *puVar4);
        }
        puVar4 = puVar4 + 1;
        pbVar3 = pbVar3 + 1;
    } while (*pbVar3 != 0);
}

// @ 0x011fcee0 -- FUN_011fcee0
// Same walk as FUN_011fcde0, but against the &DAT_0171b538 mask table and the
// &DAT_0171b938 handlers, reading the parallel dword at param_1+0x20.
void __cdecl FUN_011fcee0(byte* param_1, uint param_2) {
    int* pbVar3 = (int*)(param_1 + 0x20);
    byte bVar1 = *param_1;
    do {
        uint uVar2 = (uint)bVar1;
        if ((*(uint*)(0x171b538 + uVar2 * 4) & param_2) != 0) {
            (*(void(__cdecl**)(uint, uint, int))(0x171b938 + uVar2 * 4))(uVar2, param_2, *pbVar3);
        }
        bVar1 = param_1[1];
        pbVar3 = pbVar3 + 1;
        param_1 = param_1 + 1;
    } while (bVar1 != 0);
}

// @ 0x011fce20 -- FUN_011fce20
// Intersects the letter list at param_1 with the candidate string param_2,
// accumulating the matched masks in param_1+0xa0 and returning the mask of the
// letters that matched a different payload.
uint __cdecl FUN_011fce20(byte* param_1, byte* param_2) {
    byte* pbVar3 = param_2;
    byte bVar4 = *param_1;
    uint uVar8 = 0;
    byte* pbVar7 = param_1 + 1;
    if (*param_2 != 0) {
        byte* param_2b = param_1 + 0x20;
        uint local_4 = 0;
        do {
            uint uVar5 = *(uint*)(0x171b538 + (uint)bVar4 * 4);
            if (uVar5 != 0) {
                uVar8 = uVar8 | uVar5;
                int iVar6 = 0;
                byte bVar2 = *pbVar3;
                while (bVar4 != bVar2 && bVar2 != 0) {
                    int iVar1 = iVar6 + 1;
                    iVar6 = iVar6 + 1;
                    bVar2 = pbVar3[iVar1];
                }
                if (pbVar3[iVar6] == 0 || *(int*)param_2b != *(int*)(pbVar3 + iVar6 * 4 + 0x20)) {
                    local_4 = local_4 | uVar5;
                }
            }
            bVar4 = *pbVar7;
            param_2b = param_2b + 4;
            pbVar7 = pbVar7 + 1;
        } while (bVar4 != 0);
        *(uint*)(param_1 + 0xa0) = uVar8;
        return local_4;
    }
    do {
        uint uVar5 = (uint)bVar4;
        bVar4 = *pbVar7;
        uVar8 = uVar8 | *(uint*)(0x171b538 + uVar5 * 4);
        pbVar7 = pbVar7 + 1;
    } while (bVar4 != 0);
    *(uint*)(param_1 + 0xa0) = uVar8;
    return uVar8;
}

void __cdecl FUN_011fca60(float* out, const float* in);

// @ 0x011fcbc0 -- FUN_011fcbc0
// Picks the first active light (scanning &DAT_016f6570 for the first non-null
// entry, stopping after 8), transforms its 4-float colour through FUN_011fca60
// (or zeroes it) and pushes it to the D3D9 device constant slot.
void __cdecl FUN_011fcbc0(void* param_1, void* param_2, int param_3) {
    float local_30[4];
    float local_20[4];
    unsigned uVar2 = 0;
    int* lightArray = (int*)0x16f6570;
    if (lightArray[0] == 0) {
        do {
            int* piVar1 = lightArray + uVar2;
            uVar2 = uVar2 + 1;
            if (*piVar1 != 0) break;
        } while (true);
        if (uVar2 < 8) goto LAB_011fcbe6;
    } else {
LAB_011fcbe6:
        int* piVar1 = (int*)lightArray[uVar2];
        if (piVar1 != 0 && *piVar1 != 1 && *piVar1 != 3) {
            local_20[0] = ((float*)piVar1)[8];
            local_20[1] = ((float*)piVar1)[9];
            local_20[2] = ((float*)piVar1)[10];
            local_20[3] = ((float*)piVar1)[0xb];
            FUN_011fca60(local_30, local_20);
            goto LAB_011fcc3c;
        }
    }
    local_30[0] = 0.0f;
    local_30[1] = 0.0f;
    local_30[2] = 0.0f;
    local_30[3] = 0.0f;
LAB_011fcc3c:
    if (param_3 != 0) {
        (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x178))(
            *(void**)0x16f89d0, param_1, local_30, 1);
        return;
    }
    (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x1b4))(
        *(void**)0x16f89d0, param_1, local_30, 1);
}

// @ 0x011fcc70 -- FUN_011fcc70
// Copies the 4x4 matrix at &DAT_016fa5b8 to the stack, transforms its third row
// through FUN_011fca60, forces w = 1 and pushes the result to the device.
void __cdecl FUN_011fcc70(void* param_1, void* param_2, int param_3) {
    float m[16];
    float out70[4];
    float arg[4];
    for (int i = 0; i < 16; i++) {
        m[i] = ((float*)0x16fa5b8)[i];
    }
    FUN_011fca60(out70, m + 8);
    arg[0] = out70[0];
    arg[1] = out70[1];
    arg[2] = out70[2];
    arg[3] = 1.0f;
    if (param_3 != 0) {
        (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x178))(
            *(void**)0x16f89d0, param_1, arg, 1);
        return;
    }
    (*(void(__cdecl**)(void*, void*, void*, int))(*(int*)0x16f89d0 + 0x1b4))(
        *(void**)0x16f89d0, param_1, arg, 1);
}
