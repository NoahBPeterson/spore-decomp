// Slice s00e695f0 (frozen batch spcg1): object SPGonzago/SPCellGame.obj.
// Creature "cell game" attachment entry points, HUD tooltip helpers and
// per-role state queries. Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern uint8_t* g_CellGame;                 // cCellGame*   at 0x16b3c04

extern "C" float g_13eb1bc;                 // -1.0f
extern "C" float g_1485378;                 //  0.0f
extern "C" float g_1485720;                 //  1.0f
extern "C" float g_14007f4;                 // 15.0f
extern "C" float g_16b3c28, g_16b3c2c, g_16b3c30;
extern "C" int   g_16b4494, g_16b4490, g_16b448c, g_16b4488;
extern "C" uint8_t g_16b3dac;

struct ObjRef { int a, b, c; };

extern "C" void* __cdecl FUN_00e52910(int);
extern "C" void* __cdecl FUN_00e679e0(ObjRef);
extern "C" int   __cdecl FUN_00e4cce0(int);
extern "C" void  __cdecl FUN_00e57a10(int, int);
extern "C" void  __cdecl FUN_00e82be0(int, int);
extern "C" char  __cdecl FUN_00e67aa0();
extern "C" void* __cdecl FUN_0067cac0();
extern "C" void  __cdecl FUN_00e59cc0(int*, int*, int*, float, int, int, int, int, int);
extern "C" int   __cdecl FUN_00e57340(int);
extern "C" int   __cdecl EA_Hash_FNV1_String8(const char*, unsigned, int);   // 0x932e80
extern "C" void  __cdecl FUN_00e41cb40(void*, const void*);                  // Matrix3 assign
extern "C" void  __cdecl FUN_00e68000(int, int, void*);
extern "C" void  __cdecl FUN_00e5f4d0(int, float, float, void*);
extern "C" void  __cdecl FUN_00e62380(int, int, int, void*, float);
extern "C" void  __cdecl FUN_00e59200(int);
extern "C" void  __cdecl FUN_00409930(void*);
extern "C" void* __cdecl FUN_00b721d0(int);

struct cSPTransform {
    uint16_t mFlags; uint16_t mModCount;
    float mTranslation[3]; float mScale; float mRotation[9];
    cSPTransform& operator=(const cSPTransform&);
};
struct UIHints { void Update(); };

// ================================================================ 00e695f0
// @ 0x00e695f0
double FUN_00e695f0(int param_1, ObjRef ref) {
    int iVar2 = *(int*)(*(int*)(g_CellGame + 0x5190) + 0x7c);
    int* piVar1;
    switch (iVar2) {
    case 0:
        piVar1 = (int*)(param_1 + 0x248);
        if (*piVar1 != -1) goto use;
        break;
    case 1:
        break;
    case 2:
        piVar1 = (int*)(param_1 + 0x194);
        if (*piVar1 != -1) goto use;
        break;
    default:
        break;
    }
    piVar1 = (int*)(param_1 + 0xe0);
use:
    float minus1 = -1.0f;
    float f = *(float*)((char*)piVar1 + 0xac);
    if (f == minus1) {
        int iVar3 = (int)FUN_00e52910(param_1);
        f = *(float*)(iVar3 + 0xa8);
        if (f == minus1 && ref.a != 0) {
            int iVar4 = (int)FUN_00e679e0(ref);
            f = *(float*)(iVar4 + 0x125c);
        }
    }
    return f;
}

// ================================================================ 00e696a0
// @ 0x00e696a0
double FUN_00e696a0(int param_1, ObjRef ref) {
    int iVar2 = *(int*)(*(int*)(g_CellGame + 0x5190) + 0x7c);
    int* piVar1;
    switch (iVar2) {
    case 0:
        piVar1 = (int*)(param_1 + 0x248);
        if (*piVar1 != -1) goto use;
        break;
    case 1:
        break;
    case 2:
        piVar1 = (int*)(param_1 + 0x194);
        if (*piVar1 != -1) goto use;
        break;
    default:
        break;
    }
    piVar1 = (int*)(param_1 + 0xe0);
use:
    float f = *(float*)((char*)piVar1 + 0xa8);
    if (f == -1.0f && ref.a != 0) {
        int iVar3 = (int)FUN_00e679e0(ref);
        f = *(float*)(iVar3 + 0x1260);
    }
    return f;
}

// ================================================================ 00e69740
// @ 0x00e69740
double FUN_00e69740(int param_1, ObjRef ref) {
    int iVar2 = *(int*)(*(int*)(g_CellGame + 0x5190) + 0x7c);
    int* piVar1;
    switch (iVar2) {
    case 0:
        piVar1 = (int*)(param_1 + 0x248);
        if (*piVar1 != -1) goto use;
        break;
    case 1:
        break;
    case 2:
        piVar1 = (int*)(param_1 + 0x194);
        if (*piVar1 != -1) goto use;
        break;
    default:
        break;
    }
    piVar1 = (int*)(param_1 + 0xe0);
use:
    float f = *(float*)((char*)piVar1 + 0xb0);
    if (f == 0.0f && ref.a != 0) {
        int iVar3 = (int)FUN_00e679e0(ref);
        f = *(float*)(iVar3 + 0x1264);
    }
    return f;
}

// ================================================================ 00e697e0
// @ 0x00e697e0
void FUN_00e697e0(float param_1) {
    if ((g_16b4494 & 1) == 0) {
        g_16b4494 |= 1;
        g_16b4490 = EA_Hash_FNV1_String8("clg-move", 0x811c9dc5, 1);
    }
    if ((g_16b4494 & 2) == 0) {
        g_16b4494 |= 2;
        g_16b448c = EA_Hash_FNV1_String8("clg-carnivore", 0x811c9dc5, 1);
    }
    if ((g_16b4494 & 4) == 0) {
        g_16b4494 |= 4;
        g_16b4488 = EA_Hash_FNV1_String8("clg-herbivore", 0x811c9dc5, 1);
    }
    int uVar5;
    if (*(char*)(*(int*)(g_CellGame + 0x5190) + 0xe0) == 0) {
        float f = param_1 + *(float*)(g_CellGame + 0x51c4);
        *(float*)(g_CellGame + 0x51c4) = f;
        uVar5 = (f > g_14007f4) ? 1 : 0;
    } else {
        uVar5 = 0;
    }
    FUN_00e82be0(g_16b4490, uVar5);
    if (*(char*)(*(int*)(g_CellGame + 0x5190) + 0xe1) == 0 &&
        *(char*)(*(int*)(g_CellGame + 0x5190) + 0xe0) == 1) {
        float f2 = *(float*)(g_CellGame + 0x51c8) + param_1;
        *(float*)(g_CellGame + 0x51c8) = f2;
        if (f2 > g_14007f4) {
            char c1 = FUN_00e67aa0();
            int a = c1 ? g_16b448c : g_16b4488;
            char c2 = FUN_00e67aa0();
            int b = c2 ? g_16b4488 : g_16b448c;
            FUN_00e82be0(a, 1);
            FUN_00e82be0(b, 0);
        } else {
            FUN_00e82be0(g_16b448c, 0);
            FUN_00e82be0(g_16b4488, 0);
        }
        ((UIHints*)FUN_0067cac0())->Update();
        return;
    }
    FUN_00e82be0(g_16b448c, 0);
    FUN_00e82be0(g_16b4488, 0);
    ((UIHints*)FUN_0067cac0())->Update();
}

// ================================================================ 00e699b0
// @ 0x00e699b0
bool FUN_00e699b0(int* param_1, int param_2) {
    if (*param_1 == 0) return false;
    int iVar1 = (int)FUN_00e679e0(*(ObjRef*)param_1);
    return 0 < *(int*)(iVar1 + 0x1204 + param_2 * 4);
}

// ================================================================ 00e699f0
// @ 0x00e699f0
void FUN_00e699f0(int param_1, int param_2, int param_3, cSPTransform* param_4) {
    cSPTransform local;
    local.mFlags = 0;
    local.mModCount = 0;
    local.mTranslation[0] = g_16b3c28;
    local.mTranslation[1] = g_16b3c2c;
    local.mTranslation[2] = g_16b3c30;
    local.mScale = g_1485720;
    FUN_00e41cb40(local.mRotation, &g_16b3dac);
    FUN_00e68000(param_1, param_2, &local);
    *param_4 = local;
    param_4->mModCount++;
    param_4->mScale = g_1485720;
}

// ================================================================ 00e69a90
// @ 0x00e69a90
int FUN_00e69a90(int param_1, int param_2, int param_3, float param_4, float param_5) {
    int iVar1 = (int)FUN_00b721d0(param_1);
    if (!iVar1 || *(char*)(iVar1 + 0x112) != 0) return 0;
    int uVar3 = (param_3 == 2) ? 0xc : 0xb;
    switch (*(int*)(iVar1 + 0x18c)) {
        case 0: case 1: case 2: case 3: case 0x12: case 0x13: case 0x14:
        case 0x15: case 0x16: case 0x18: case 0x19: case 0x1a: case 0x1b:
        case 0x1d: case 0x28: case 0x30: case 0x32: case 0x33:
            *(int*)(iVar1 + 0x18c) = uVar3;
            FUN_00e57a10(iVar1, param_1);
    }
    int puVar2 = (int)FUN_00b721d0(param_2);
    if (puVar2) {
        cSPTransform local;
        FUN_00409930(&local);
        *(uint8_t*)(iVar1 + 0x178) = 1;
        *(uint8_t*)(puVar2 + 0x179) = 1;
        *(uint8_t*)(puVar2 + 0x17f) = 1;
        FUN_00e68000(iVar1, param_1, &local);
        if (0.0f < param_4) {
            if (*(int*)(puVar2 + 0x370)) FUN_00e59200(*(int*)(puVar2 + 0x370));
            *(uint8_t*)(puVar2 + 4) = 1;
            FUN_00e5f4d0(*(int*)puVar2, param_5, param_4 + param_5, 0);
            *(int*)(iVar1 + 0x170) = param_2;
            return 1;
        }
        *(uint8_t*)(puVar2 + 4) = 1;
        FUN_00e62380(iVar1, param_1, puVar2, &local, param_5);
    }
    return 1;
}

// ================================================================ 00e69c10
// @ 0x00e69c10
int FUN_00e69c10(int param_1, int param_2, int param_3, float param_4, float param_5) {
    int* puVar1 = (int*)FUN_00b721d0(param_1);
    if (!puVar1 || *(char*)((int)puVar1 + 0x112) != 0) return 0;
    int* puVar2 = (int*)FUN_00b721d0(param_2);
    if (!puVar2 || *(char*)((int)puVar2 + 0x112) != 0) return 0;
    *(uint8_t*)(puVar1 + 0x5e) = 1;
    puVar1[0x61] = *puVar2;
    *(uint8_t*)(puVar2 + 0x5e) = 1;
    *(uint8_t*)((int)puVar2 + 0x17b) = 1;
    *(uint8_t*)((int)puVar2 + 0x17f) = 1;
    *(uint8_t*)(puVar2 + 0x5f) = 1;
    puVar2[0x61] = *puVar1;
    *(uint8_t*)((int)puVar2 + 0x179) = 1;
    *(uint8_t*)(puVar2 + 0x62) = 1;
    switch (puVar1[99]) {
        case 0: case 0xb: case 0xc: case 0xd: case 0x12: case 0x13:
        case 0x14: case 0x15: case 0x16: case 0x1d: case 0x30: case 0x32: case 0x33:
            puVar1[99] = 0xd;
            FUN_00e57a10((int)puVar1, param_3);
    }
    switch (puVar2[99]) {
        case 0: case 0xb: case 0xc: case 0xd: case 0x12: case 0x13: case 0x14:
        case 0x15: case 0x16: case 0x1a: case 0x1d: case 0x20: case 0x21: case 0x30:
            *(uint8_t*)(puVar2 + 1) = 1;
            puVar2[99] = 0x20;
    }
    cSPTransform local;
    FUN_00409930(&local);
    FUN_00e699f0((int)puVar1, param_3, (int)puVar2, &local);
    if (0.0f < param_4) {
        puVar1[0x5c] = param_2;
        FUN_00e5f4d0(*puVar2, param_5, param_4 + param_5, 0);
        return 1;
    }
    FUN_00e62380((int)puVar1, param_3, (int)puVar2, &local, param_5);
    return 1;
}

// ================================================================ 00e69e00
// @ 0x00e69e00
int FUN_00e69e00(int param_1, int param_2, int param_3, float param_4, float param_5) {
    int iVar1 = (int)FUN_00b721d0(param_1);
    if (!iVar1 || *(char*)(iVar1 + 0x112) != 0) return 0;
    int puVar2 = (int)FUN_00b721d0(param_2);
    if (!puVar2) return 0;
    *(uint8_t*)(iVar1 + 0x178) = 1;
    *(uint8_t*)(puVar2 + 0x17b) = 1;
    *(uint8_t*)(puVar2 + 0x17f) = 1;
    *(uint8_t*)(puVar2 + 0x179) = 1;
    switch (*(int*)(iVar1 + 0x18c)) {
        case 0: case 0x12: case 0x15: case 0x16: case 0x1d: case 0x30: case 0x32: case 0x33:
            *(int*)(iVar1 + 0x18c) = 0xd;
            FUN_00e57a10(iVar1, param_3);
    }
    cSPTransform local;
    FUN_00409930(&local);
    FUN_00e699f0(iVar1, param_3, puVar2, &local);
    if (0.0f < param_4) {
        if (*(int*)(puVar2 + 0x370)) FUN_00e59200(*(int*)(puVar2 + 0x370));
        *(int*)(iVar1 + 0x170) = param_2;
        FUN_00e5f4d0(*(int*)puVar2, param_5, param_4 + param_5, 0);
        return 1;
    }
    FUN_00e62380(iVar1, param_3, puVar2, &local, param_5);
    return 1;
}

// ================================================================ 00e69f90
// @ 0x00e69f90
int FUN_00e69f90(int param_1, int param_2) {
    int iVar1 = FUN_00e4cce0(0x14);
    if (*(int*)(param_1 + 0x108) == iVar1) {
        FUN_00e679e0(*(ObjRef*)(param_1 + 0xfc));
        if (param_2 == 6) return param_1 + 0x390;
        if (param_2 == 7) return param_1 + 0x391;
    } else {
        iVar1 = FUN_00e4cce0(0x18);
        if (*(int*)(param_1 + 0x108) == iVar1) {
            switch (param_2) {
                case 8:  return param_1 + 0x392;
                case 10: return param_1 + 0x393;
                case 12: return param_1 + 0x394;
                case 9:  return param_1 + 0x395;
                case 11: return param_1 + 0x396;
                case 13: return param_1 + 0x397;
            }
        }
    }
    return 0;
}

// ================================================================ 00e6a060
// @ 0x00e6a060
bool FUN_00e6a060(int param_1, int param_2) {
    char* pcVar1 = (char*)FUN_00e69f90(param_1, param_2);
    if (!pcVar1) return false;
    return *pcVar1 == 0;
}

// ================================================================ 00e6a090
// @ 0x00e6a090
int FUN_00e6a090(int param_1, int param_2, int param_3, float param_4, float param_5) {
    int iVar1 = (int)FUN_00b721d0(param_1);
    if (!iVar1 || *(char*)(iVar1 + 0x112) != 0) return 0;
    int puVar2 = (int)FUN_00b721d0(param_2);
    if (!puVar2) return 0;
    *(uint8_t*)(iVar1 + 0x178) = 1;
    *(uint8_t*)(puVar2 + 0x17b) = 1;
    *(uint8_t*)(puVar2 + 0x17f) = 1;
    *(uint8_t*)(puVar2 + 0x179) = 1;
    switch (*(int*)(iVar1 + 0x18c)) {
        case 0: case 0x12: case 0x15: case 0x16: case 0x1d: case 0x30:
            *(int*)(iVar1 + 0x18c) = 0x3b;
            FUN_00e57a10(iVar1, param_3);
    }
    cSPTransform local;
    FUN_00409930(&local);
    FUN_00e699f0(iVar1, param_3, puVar2, &local);
    if (0.0f < param_4) {
        *(int*)(iVar1 + 0x170) = param_2;
        FUN_00e5f4d0(*(int*)puVar2, param_5, param_4 + param_5, 0);
        return 1;
    }
    FUN_00e62380(iVar1, param_3, puVar2, &local, param_5);
    return 1;
}

// ================================================================ 00e6a1f0
// @ 0x00e6a1f0
bool FUN_00e6a1f0(int param_1) {
    if (*(int*)(param_1 + 0xfc) == 0) return false;
    int iVar1 = (int)FUN_00e679e0(*(ObjRef*)(param_1 + 0xfc));
    return *(float*)(iVar1 + 0x1270) != 0.0f;
}

// ================================================================ 00e6a250
// @ 0x00e6a250
void FUN_00e6a250(int* param_1, int* param_2, int* param_3, float param_4,
                  int* param_5, int* param_6, int param_7, int param_8) {
    if (param_7 == 5) {
        char cVar1 = FUN_00e6a1f0((int)param_5);
        if (cVar1 == 0 && *param_5 != param_6[0x43] &&
            (FUN_00e4cce0(0x17) != param_5[0x42] || FUN_00e57340((int)param_5) != 4)) {
            if (param_8 != 0)
                FUN_00e59cc0(param_1, param_2, param_3, param_4, *param_5, *param_6, -1, -1, 0x11);
            else
                FUN_00e59cc0(param_1, param_2, param_3, param_4, *param_5, *param_6, -1, -1, 0x16);
            return;
        }
        if (param_1[2] < 0x16 || (param_1[2] == 0x16 && param_4 <= *(float*)&param_1[5])) {
            *param_1 = *param_5;
            param_1[1] = *param_6;
            param_1[6] = *param_2; param_1[7] = param_2[1]; param_1[8] = param_2[2];
            param_1[9] = *param_3; param_1[10] = param_3[1]; param_1[0xb] = param_3[2];
            *(float*)&param_1[5] = param_4;
            param_1[3] = -1; param_1[4] = -1; param_1[2] = 0x16;
        }
    } else {
        if (param_1[2] < 1 || (param_1[2] == 1 && param_4 <= *(float*)&param_1[5])) {
            *param_1 = *param_5;
            param_1[1] = *param_6;
            param_1[6] = *param_2; param_1[7] = param_2[1]; param_1[8] = param_2[2];
            param_1[9] = *param_3; param_1[10] = param_3[1]; param_1[0xb] = param_3[2];
            *(float*)&param_1[5] = param_4;
            param_1[3] = -1; param_1[4] = -1; param_1[2] = 1;
        }
    }
}
