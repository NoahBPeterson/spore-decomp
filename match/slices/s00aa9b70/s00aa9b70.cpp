// Slice s00aa9b70 (batch big0, slice 17): unnamed per-mode basis-colour / normal
// builder. __cdecl, /O2 (no frame pointer), scalar SSE.
#include "types.h"
#include <math.h>

extern void  FUN_00a7d6b0(float* v);                       // 0xa7d6b0 helper
extern float DAT_01679444, DAT_01679448, DAT_0167944c;     // basis vectors
extern float DAT_016794a0, DAT_016794a4, DAT_016794a8, DAT_016794ac;
extern float DAT_016794b0, DAT_016794b4;

// @ 0x00aa9b70
void FUN_00aa9b70(int param_1, int param_2, float* param_3)
{
    float local_18, local_14, local_10, local_c, local_8, local_4;
    float fVar6, fVar2;
    int   iVar3;
    unsigned uVar5;
    unsigned char uVar4;

    switch (*(unsigned char*)(param_2 + 0x134)) {
    case 1:
    case 5:
        local_18 = (*(float*)(param_2 + 0x38) + *(float*)(param_2 + 0x2c)) * 0.5f;
        local_14 = (*(float*)(param_2 + 0x3c) + *(float*)(param_2 + 0x30)) * 0.5f;
        local_10 = (*(float*)(param_2 + 0x40) + *(float*)(param_2 + 0x34)) * 0.5f;
        if (*(unsigned char*)(param_2 + 0x134) == 1) {
            FUN_00a7d6b0(&local_18);
            FUN_00a7d6b0(&local_18);
        }
        local_c = local_14 * DAT_0167944c - local_10 * DAT_01679448;
        local_8 = local_10 * DAT_01679444 - local_18 * DAT_0167944c;
        local_4 = local_18 * DAT_01679448 - local_14 * DAT_01679444;
        fVar6 = sqrtf((local_4 * local_4 + local_8 * local_8) + local_c * local_c);
        if (fVar6 <= 0.0001f) {
            param_3[0] = DAT_016794a0;
            param_3[1] = DAT_016794a4;
            param_3[2] = DAT_016794a8;
            param_3[3] = DAT_016794ac;
            param_3[4] = DAT_016794b0;
            fVar6 = DAT_016794b4;
        } else {
            fVar6 = 1.0f / fVar6;
            local_18 = fVar6 * local_c;
            local_14 = local_8 * fVar6;
            param_3[0] = local_18;
            local_10 = local_4 * fVar6;
            param_3[1] = local_14;
            param_3[2] = local_10;
            local_c = param_3[2] * DAT_01679448 - param_3[1] * DAT_0167944c;
            local_8 = param_3[0] * DAT_0167944c - param_3[2] * DAT_01679444;
            local_4 = param_3[1] * DAT_01679444 - param_3[0] * DAT_01679448;
            param_3[3] = local_c;
            param_3[4] = local_8;
            fVar6 = local_4;
        }
        param_3[5] = fVar6;
        if (*(unsigned char*)(param_2 + 0x134) == 5) {
            FUN_00a7d6b0(param_3);
            FUN_00a7d6b0(param_3 + 3);
            FUN_00a7d6b0(param_3);
            FUN_00a7d6b0(param_3 + 3);
        }
        break;
    case 6: {
        float* pfVar1 = param_3 + 3;
        *pfVar1 = DAT_01679444;
        param_3[4] = DAT_01679448;
        param_3[5] = DAT_0167944c;
        FUN_00a7d6b0(pfVar1);
        FUN_00a7d6b0(pfVar1);
        iVar3 = *(int*)(param_1 + 0x30);
        param_3[0] = *(float*)(iVar3 + 0x68);
        param_3[1] = *(float*)(iVar3 + 0x6c);
        param_3[2] = *(float*)(iVar3 + 0x70);
        fVar6 = param_3[1];
        fVar2 = param_3[0];
        param_3[0] = param_3[5] * fVar6 - param_3[4] * param_3[2];
        param_3[1] = *pfVar1 * param_3[2] - param_3[5] * fVar2;
        param_3[2] = param_3[4] * fVar2 - *pfVar1 * fVar6;
        fVar6 = 1.0f / (sqrtf((param_3[0] * param_3[0] + param_3[1] * param_3[1]) +
                              (param_3[2] * param_3[2])) + 0.1f);
        param_3[0] = fVar6 * param_3[0];
        param_3[1] = param_3[1] * fVar6;
        param_3[2] = fVar6 * param_3[2];
        break;
    }
    case 7: {
        iVar3 = *(int*)(param_1 + 0x30);
        param_3[3] = *(float*)(iVar3 + 0xf4);
        param_3[4] = *(float*)(iVar3 + 0xf8);
        param_3[5] = *(float*)(iVar3 + 0xfc);
        iVar3 = *(int*)(param_1 + 0x30);
        param_3[0] = *(float*)(iVar3 + 0x68);
        param_3[1] = *(float*)(iVar3 + 0x6c);
        param_3[2] = *(float*)(iVar3 + 0x70);
        fVar6 = param_3[1];
        fVar2 = param_3[0];
        param_3[0] = param_3[5] * fVar6 - param_3[4] * param_3[2];
        param_3[1] = param_3[3] * param_3[2] - param_3[5] * fVar2;
        param_3[2] = param_3[4] * fVar2 - param_3[3] * fVar6;
        fVar6 = 1.0f / (sqrtf((param_3[0] * param_3[0] + param_3[1] * param_3[1]) +
                              (param_3[2] * param_3[2])) + 0.1f);
        param_3[0] = fVar6 * param_3[0];
        param_3[1] = param_3[1] * fVar6;
        param_3[2] = fVar6 * param_3[2];
        break;
    }
    default:
        iVar3 = *(int*)(param_1 + 0x30);
        param_3[0] = *(float*)(iVar3 + 0x5c);
        param_3[1] = *(float*)(iVar3 + 0x60);
        param_3[2] = *(float*)(iVar3 + 0x64);
        iVar3 = *(int*)(param_1 + 0x30);
        param_3[3] = *(float*)(iVar3 + 0x74);
        param_3[4] = *(float*)(iVar3 + 0x78);
        param_3[5] = *(float*)(iVar3 + 0x7c);
        break;
    }

    if (*(signed char*)(param_2 + 0x180) != 0 || *(signed char*)(param_2 + 0x182) != 0) {
        param_3[6] = (float)*(unsigned char*)(param_2 + 0x181) * 0.003921569f;
        param_3[7] = (float)*(unsigned char*)(param_2 + 0x180) * 0.0627451f;
        param_3[8] = (float)*(unsigned char*)(param_2 + 0x183) * 0.003921569f;
        param_3[9] = (float)*(unsigned char*)(param_2 + 0x182) * 0.0627451f;
    }
    fVar6 = 0.0f;
    if ((*(unsigned char*)(param_2 + 0x132) < 2) && (*(unsigned char*)(param_2 + 0x133) < 2)) {
        uVar4 = 0;
    } else {
        uVar4 = 1;
    }
    *(unsigned char*)(param_3 + 10) = uVar4;
    param_3[0xb] = 1.0f / (float)*(unsigned char*)(param_2 + 0x132);
    param_3[0xc] = 1.0f / (float)*(unsigned char*)(param_2 + 0x133);
    param_3[0xd] = (float)(*(unsigned char*)(param_2 + 0x132) - 1);
    param_3[0xe] = (float)(*(unsigned char*)(param_2 + 0x133) - 1);
    param_3[0xf] = 0.0f;
    uVar5 = (unsigned)*(unsigned char*)(param_2 + 0x132);
    if (1 < uVar5) {
        do {
            uVar5 = (int)uVar5 >> 1;
            fVar6 = (float)((int)fVar6 + 1);
        } while (1 < uVar5);
        param_3[0xf] = fVar6;
    }
}
