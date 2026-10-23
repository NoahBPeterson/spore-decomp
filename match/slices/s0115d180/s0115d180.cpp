// match/slices/s0115d180/s0115d180.cpp
// Slice s0115d180 -- EAWebKit EA::Text::DelayLine / run-scheduler helpers
// (SporeApp.exe 0x0115d180..0x0115de1f).
//
//  0115d180  DelayLine::read                 ring-buffer read, either via the callback at +0x14 or via
//                                            the raw eastl-vector<bool> block copy path
//  0115d3f0  run-cursor advance              bump +0x1c9, wrap at +0x1ca, reload the +0x1a0..+0x1ac triple
//  0115d470  emit block (scale)              table-driven per-entry FUN_011342c0 emit * param_3
//  0115d500  emit block (ramp)               table-driven per-entry FUN_011600e0 emit with a ramp
//  0115d5c0  set source                      rotate +0x28 into +0x2c, mark dirty at +0x38
//  0115d600  min(+0x20, +0xc)
//  0115d610  zero the two output blocks
//  0115d730  build the next block            (eastl vector<bool> DoInsertValue copies)
//  0115d8e0  read one block                  CalcChannelPointers + FUN_0115d730 + FUN_0115d610
//  0115d990  run the whole request           per-row block loop, then advance the +0x20/+0x24/+0x34 cursors
//  0115dc10  rotate a 16-float block by a per-run angle pair
//  0115ddd0  byte-swap 16 bytes at a time (MMX psrlw/psllw/por)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"
#include <intrin.h>

extern unsigned char DAT_014dd46a[];        // 0x014dd46a  per-entry [first,last] byte pair
extern unsigned char DAT_014dd46b[];        // 0x014dd46b
extern unsigned char DAT_014dd4c0[];        // 0x014dd4c0  per-entry packed channel/mix index
extern float         DAT_014dd46c[];        // 0x014dd46c  per-entry gain
extern float         DAT_014ce8ec;          // 0x014ce8ec  ramp scale

void __cdecl FUN_011342c0(int, int, float, int);        // 0x011342c0
void __cdecl FUN_011600e0(int, int, float, float, int); // 0x011600e0
void* __cdecl VectorBool_DoInsertValue(void* dst, const void* src, unsigned bytes);

struct D {
    void  FUN_0115d180(int param_2, unsigned param_3);
    void  FUN_0115d5c0(int param_2);
    void  FUN_0115d610(int param_2, int param_3, int param_4);
    void* FUN_0115d730(void* param_2, int* param_3, unsigned param_4);
    int   FUN_0115d8e0(int param_2, int param_3, int param_4, int param_5);
    void  FUN_0115d990(int param_2, int param_3, int param_4, int param_5);
    void  FUN_0115dc10(float* param_2, short* param_3, float* param_4);
    void  FUN_0114d9f0(void* dst, int param_2, int param_4);
    void* FUN_0114da40(int param_2);
};

// =========================================================================================================
// 0115d180
// =========================================================================================================
// @ 0x0115d180
void D::FUN_0115d180(int param_2, unsigned param_3)
{
    int self = (int)this;
    unsigned uVar4 = 0;
    if (*(char*)(self + 0x33) == 0) {
        if ((int)param_3 > 0) {
            do {
                int iVar5 = *(int*)(self + *(unsigned char*)(self + 0x31) * 0x14 + *(int*)(self + 0x24) + 0xc);
                if (iVar5 == 0) {
                    return;
                }
                iVar5 = iVar5 - *(int*)(self + 0x1c);
                int iVar2 = param_3 - uVar4;
                if (iVar5 <= (int)(param_3 - uVar4)) {
                    iVar2 = iVar5;
                }
                (*(void(__thiscall**)(int, int, int))(self + 0x14))(self, param_2, iVar2);
                *(int*)(self + 0x1c) = *(int*)(self + 0x1c) + iVar2;
                iVar5 = self + *(unsigned char*)(self + 0x31) * 0x14 + *(int*)(self + 0x24);
                uVar4 = uVar4 + iVar2;
                if (*(int*)(self + 0x1c) == *(int*)(iVar5 + 0xc)) {
                    *(int*)(iVar5 + 0xc) = 0;
                    *(char*)(self + 0x31) = *(char*)(self + 0x31) + 1;
                    if (*(unsigned char*)(self + 0x32) <= *(unsigned char*)(self + 0x31)) {
                        *(char*)(self + 0x31) = 0;
                    }
                    *(int*)(self + 0x1c) =
                        *(int*)(self + *(unsigned char*)(self + 0x31) * 0x14 + 8 + *(int*)(self + 0x24));
                }
            } while ((int)uVar4 < (int)param_3);
        }
    } else {
        unsigned short uVar1 = *(unsigned short*)(self + 0x2c);
        int iVar5 = *(int*)(self + 0x28) + self;
        if (uVar1 != 0) {
            uVar4 = uVar1;
            if ((int)param_3 <= (int)(unsigned)uVar1) {
                uVar4 = param_3;
            }
            unsigned uVar6 = 0;
            if (*(char*)(self + 0x2e) != 0) {
                do {
                    VectorBool_DoInsertValue(
                        (void*)(*(int*)(param_2 + 4) + *(unsigned short*)(param_2 + 0xe) * uVar6 * 4),
                        (void*)(*(int*)(iVar5 + 4) +
                                ((*(unsigned short*)(iVar5 + 0xe) * uVar6 -
                                  (unsigned)*(unsigned short*)(self + 0x2c)) +
                                 (unsigned)*(unsigned short*)(iVar5 + 0xc)) * 4),
                        uVar4 * 4);
                    uVar6 = uVar6 + 1;
                } while (uVar6 < *(unsigned char*)(self + 0x2e));
            }
            *(int*)(self + 0x1c) = *(int*)(self + 0x1c) + uVar4;
            *(short*)(self + 0x2c) = *(short*)(self + 0x2c) - (short)uVar4;
            int iVar2 = self + *(unsigned char*)(self + 0x31) * 0x14 + *(int*)(self + 0x24);
            if (*(int*)(self + 0x1c) == *(int*)(iVar2 + 0xc)) {
                *(int*)(iVar2 + 0xc) = 0;
                *(char*)(self + 0x31) = *(char*)(self + 0x31) + 1;
                if (*(unsigned char*)(self + 0x32) <= *(unsigned char*)(self + 0x31)) {
                    *(char*)(self + 0x31) = 0;
                }
                *(int*)(self + 0x1c) =
                    *(int*)(self + *(unsigned char*)(self + 0x31) * 0x14 + 8 + *(int*)(self + 0x24));
            }
        }
        if ((int)uVar4 < (int)param_3) {
            while (true) {
                int iVar2 = self + *(unsigned char*)(self + 0x31) * 0x14 + *(int*)(self + 0x24);
                if (*(int*)(iVar2 + 0xc) == 0) {
                    break;
                }
                unsigned uVar6 = param_3 - uVar4;
                int iVar3 = (*(int(__thiscall**)(int, int, unsigned))(self + 0x14))(self, iVar5, uVar6);
                iVar2 = *(int*)(iVar2 + 0xc) - *(int*)(self + 0x1c);
                if (iVar2 <= iVar3) {
                    iVar3 = iVar2;
                }
                *(short*)(self + 0x2c) = (short)iVar3;
                *(short*)(iVar5 + 0xc) = (short)iVar3;
                if ((int)(unsigned)*(unsigned short*)(self + 0x2c) < (int)uVar6) {
                    uVar6 = (unsigned)*(unsigned short*)(self + 0x2c);
                }
                unsigned uVar7 = 0;
                if (*(char*)(self + 0x2e) != 0) {
                    do {
                        VectorBool_DoInsertValue(
                            (void*)(*(int*)(param_2 + 4) +
                                    (*(unsigned short*)(param_2 + 0xe) * uVar7 + uVar4) * 4),
                            (void*)(*(int*)(iVar5 + 4) + *(unsigned short*)(iVar5 + 0xe) * uVar7 * 4),
                            uVar6 * 4);
                        uVar7 = uVar7 + 1;
                    } while (uVar7 < *(unsigned char*)(self + 0x2e));
                }
                *(short*)(self + 0x2c) = *(short*)(self + 0x2c) - (short)uVar6;
                *(int*)(self + 0x1c) = *(int*)(self + 0x1c) + uVar6;
                iVar2 = self + *(unsigned char*)(self + 0x31) * 0x14 + *(int*)(self + 0x24);
                uVar4 = uVar4 + uVar6;
                if (*(int*)(self + 0x1c) == *(int*)(iVar2 + 0xc)) {
                    *(int*)(iVar2 + 0xc) = 0;
                    *(char*)(self + 0x31) = *(char*)(self + 0x31) + 1;
                    if (*(unsigned char*)(self + 0x32) <= *(unsigned char*)(self + 0x31)) {
                        *(char*)(self + 0x31) = 0;
                    }
                    *(int*)(self + 0x1c) =
                        *(int*)(self + *(unsigned char*)(self + 0x31) * 0x14 + 8 + *(int*)(self + 0x24));
                }
                if ((int)param_3 <= (int)uVar4) {
                    return;
                }
            }
        }
    }
}

// =========================================================================================================
// 0115d3f0
// =========================================================================================================
// @ 0x0115d3f0
extern "C" void __fastcall FUN_0115d3f0(int param_1)
{
    *(char*)(param_1 + 0x1c9) = *(char*)(param_1 + 0x1c9) + 1;
    if (*(char*)(param_1 + 0x1c9) == *(char*)(param_1 + 0x1ca)) {
        *(char*)(param_1 + 0x1c9) = 0;
    }
    int iVar1 = (unsigned)*(unsigned char*)(param_1 + 0x1c9) * 0x30 +
                (unsigned)*(unsigned short*)(param_1 + 0x1c4) + param_1;
    *(int*)(param_1 + 0x1a8) = 0;
    *(int*)(param_1 + 0x1ac) = 0;
    int cVar = *(unsigned char*)(iVar1 + 0x2a);
    if (cVar != 4 && cVar != 0) {
        *(int*)(param_1 + 0x1a8) = 0;
        *(float*)(param_1 + 0x1a0) = *(float*)(iVar1 + 0xc);
        *(float*)(param_1 + 0x1a4) = *(float*)(iVar1 + 0x10);
        *(int*)(param_1 + 0x1ac) = *(int*)(iVar1 + 0x14);
    }
}

// =========================================================================================================
// 0115d470
// =========================================================================================================
// @ 0x0115d470
extern "C" void __cdecl FUN_0115d470(int param_1, int param_2, float param_3, int param_4, int param_5,
                                     int param_6)
{
    param_4 = param_4 + param_5 * 6;
    unsigned uVar2 = (unsigned char)DAT_014dd46a[param_4 * 2];
    if (uVar2 <= (unsigned char)DAT_014dd46b[param_4 * 2]) {
        do {
            unsigned char bVar1 = DAT_014dd4c0[uVar2];
            FUN_011342c0(*(int*)(param_1 + (unsigned)(bVar1 >> 5) * 4),
                         *(int*)(param_2 + (bVar1 >> 2 & 7) * 4),
                         DAT_014dd46c[bVar1 & 3] * param_3, param_6);
            uVar2 = uVar2 + 1;
        } while (uVar2 <= (unsigned char)DAT_014dd46b[param_4 * 2]);
    }
}

// =========================================================================================================
// 0115d500
// =========================================================================================================
// @ 0x0115d500
extern "C" void __cdecl FUN_0115d500(int param_1, int param_2, float param_3, float param_4, int param_5,
                                     int param_6, int param_7)
{
    param_5 = param_5 + param_6 * 6;
    unsigned uVar2 = (unsigned char)DAT_014dd46a[param_5 * 2];
    if (uVar2 <= (unsigned char)DAT_014dd46b[param_5 * 2]) {
        do {
            unsigned char bVar1 = DAT_014dd4c0[uVar2];
            FUN_011600e0(*(int*)(param_1 + (unsigned)(bVar1 >> 5) * 4),
                         *(int*)(param_2 + (bVar1 >> 2 & 7) * 4),
                         DAT_014dd46c[bVar1 & 3] * param_4,
                         DAT_014dd46c[bVar1 & 3] * ((param_3 - param_4) * DAT_014ce8ec),
                         param_7);
            uVar2 = uVar2 + 1;
        } while (uVar2 <= (unsigned char)DAT_014dd46b[param_5 * 2]);
    }
}

// =========================================================================================================
// 0115d5c0
// =========================================================================================================
// @ 0x0115d5c0
void D::FUN_0115d5c0(int param_2)
{
    int self = (int)this;
    if (param_2 != *(int*)(self + 0x28)) {
        *(int*)(self + 0x2c) = *(int*)(self + 0x28);
        *(int*)(self + 0x28) = param_2;
        *(char*)(self + 0x38) = 1;
    }
}

// =========================================================================================================
// 0115d600
// =========================================================================================================
// @ 0x0115d600
extern "C" int __fastcall FUN_0115d600(int param_1)
{
    int iVar1 = *(int*)(param_1 + 0x20);
    int iVar2 = *(int*)(param_1 + 0xc);
    if (iVar1 >= iVar2) {
        iVar1 = iVar2;
    }
    return iVar1;
}

// =========================================================================================================
// 0115d610
// =========================================================================================================
// @ 0x0115d610
void D::FUN_0115d610(int param_2, int param_3, int param_4)
{
    int self = (int)this;
    if (*(int*)(self + 0x24) < *(int*)(self + 0x14)) {
        unsigned uVar1 = param_2 - 1 + *(int*)(self + 0x10);
        unsigned uVar2 = (*(int*)(self + 0x28) - *(int*)(self + 0x24)) - param_3;
        if ((int)uVar1 <= (int)uVar2) {
            uVar2 = uVar1;
        }
        uVar2 = ((int)uVar2 < 1) - 1 & uVar2;
        int iVar3 = 0;
        if ((int)uVar2 > 3) {
            do {
                *(int*)(*(int*)(param_4 + 4) + iVar3 * 4) = 0;
                *(int*)(*(int*)(param_4 + 4) + 4 + iVar3 * 4) = 0;
                *(int*)(*(int*)(param_4 + 4) + 8 + iVar3 * 4) = 0;
                *(int*)(*(int*)(param_4 + 4) + 0xc + iVar3 * 4) = 0;
                iVar3 = iVar3 + 4;
            } while (iVar3 < (int)(uVar2 - 3));
        }
        for (; iVar3 < (int)uVar2; iVar3 = iVar3 + 1) {
            *(int*)(*(int*)(param_4 + 4) + iVar3 * 4) = 0;
        }
        if (*(int*)(param_4 + 8) != 0) {
            uVar2 = (*(int*)(self + 0x2c) - param_3) - *(int*)(self + 0x24);
            uVar1 = *(int*)(self + 0x10) + 0x7f;
            if ((int)uVar1 <= (int)uVar2) {
                uVar2 = uVar1;
            }
            uVar1 = *(int*)(self + 0x10) + -1 + param_2;
            if ((int)uVar1 <= (int)uVar2) {
                uVar2 = uVar1;
            }
            uVar2 = uVar2 & ((int)uVar2 < 1) - 1;
            iVar3 = 0;
            if ((int)uVar2 > 3) {
                do {
                    *(int*)(*(int*)(param_4 + 8) + iVar3 * 4) = 0;
                    *(int*)(*(int*)(param_4 + 8) + 4 + iVar3 * 4) = 0;
                    *(int*)(*(int*)(param_4 + 8) + 8 + iVar3 * 4) = 0;
                    *(int*)(*(int*)(param_4 + 8) + 0xc + iVar3 * 4) = 0;
                    iVar3 = iVar3 + 4;
                } while (iVar3 < (int)(uVar2 - 3));
            }
            for (; iVar3 < (int)uVar2; iVar3 = iVar3 + 1) {
                *(int*)(*(int*)(param_4 + 8) + iVar3 * 4) = 0;
            }
        }
    }
}

// =========================================================================================================
// 0115d730
// =========================================================================================================
// @ 0x0115d730
void* D::FUN_0115d730(void* param_2, int* param_3, unsigned param_4)
{
    int iVar1;
    int iVar2;
    void* pvVar3;
    unsigned uVar4;
    unsigned uVar5;
    void* _Dst;
    unsigned uVar6;
    int* local_c;
    int local_4;

    local_c = param_3 + 2;
    *local_c = 0;
    if (param_4 == 2) {
        if (*param_3 < param_3[4]) {
            *local_c = 1;
            param_3[6] = 0;
        } else {
            *local_c = 0;
            param_3[6] = 1;
        }
    }
    _Dst = *(void**)((int)this + 8);
    if ((int)param_4 > 0) {
        local_4 = param_4;
        uVar4 = param_3[*local_c * 4] + 0x1fU & 0xffffffe0;
        do {
            iVar1 = *local_c;
            uVar6 = param_3[iVar1 * 4] + 0x1fU & 0xffffffe0;
            iVar2 = uVar6 - param_3[iVar1 * 4];
            uVar5 = param_3[iVar1 * 4 + 1] + 0x1f + iVar2 & 0xffffffe0;
            if ((int)uVar4 < (int)uVar6) {
                param_3[iVar1 * 4 + 3] = (int)((int)_Dst + ((iVar2 - uVar6) + uVar4) * 4);
                uVar6 = uVar4 - (uVar6 - uVar5);
                uVar6 = ((int)uVar6 < 0) - 1 & uVar6;
                if (uVar6 == 0) {
                    uVar6 = 0;
                } else {
                    if ((int)uVar4 <= (int)uVar6) {
                        uVar6 = uVar4;
                    }
                    pvVar3 = FUN_0114da40((int)param_2);
                    uVar5 = *(int*)((int)param_2 + 4) - (int)pvVar3 >> 2;
                    param_4 = uVar6;
                    if ((int)uVar5 <= (int)uVar6) {
                        param_4 = uVar5;
                    }
                    VectorBool_DoInsertValue(_Dst, pvVar3, param_4 * 4);
                    VectorBool_DoInsertValue((void*)(param_4 * 4 + (int)_Dst),
                                             (void*)*(int*)param_2, (uVar6 - param_4) * 4);
                }
                _Dst = (void*)((int)_Dst + uVar6 * 4);
                uVar6 = uVar4 + uVar6;
            } else {
                param_3[iVar1 * 4 + 3] = (int)((int)_Dst + iVar2 * 4);
                if (uVar5 != 0) {
                    if ((int)uVar6 <= (int)uVar5) {
                        uVar5 = uVar6;
                    }
                    pvVar3 = FUN_0114da40((int)param_2);
                    uVar4 = *(int*)((int)param_2 + 4) - (int)pvVar3 >> 2;
                    param_4 = uVar5;
                    if ((int)uVar4 <= (int)uVar5) {
                        param_4 = uVar4;
                    }
                    VectorBool_DoInsertValue(_Dst, pvVar3, param_4 * 4);
                    VectorBool_DoInsertValue((void*)(param_4 * 4 + (int)_Dst),
                                             (void*)*(int*)param_2, (uVar5 - param_4) * 4);
                    uVar6 = uVar6 - uVar5;
                    _Dst = (void*)((int)_Dst + uVar5 * 4);
                }
            }
            local_c = local_c + 4;
            local_4 = local_4 + -1;
            uVar4 = uVar6;
        } while (local_4 != 0);
    }
    return _Dst;
}

// =========================================================================================================
// 0115d8e0
// =========================================================================================================
// @ 0x0115d8e0
int D::FUN_0115d8e0(int param_2, int param_3, int param_4, int param_5)
{
    int self = (int)this;
    unsigned char local_30[16];
    int local_20;
    int local_1c;
    int local_14;
    int local_10;
    int local_c;
    unsigned local_4;

    FUN_0114d9f0(local_30, param_2, param_4);
    local_20 = *(int*)(self + 0x28);
    local_1c = *(int*)(self + 0x10) + -1 + param_3;
    unsigned uVar1 = 1;
    local_14 = 0;
    if (*(char*)(self + 0x38) != 0) {
        local_10 = *(int*)(self + 0x2c);
        local_c = param_3;
        if (param_3 > 0x7f) {
            local_c = 0x80;
        }
        local_c = *(int*)(self + 0x10) + -1 + local_c;
        local_4 = 0;
        uVar1 = 2;
    }
    uVar1 = (unsigned)FUN_0115d730(&local_20, &local_1c, uVar1);
    *(int*)(param_5 + 0x10) = uVar1;
    *(int*)(param_5 + 4) = local_14;
    *(unsigned*)(param_5 + 8) = -(unsigned)(*(char*)(self + 0x38) != 0) & local_4;
    FUN_0115d610(param_3, param_4, param_5);
    return param_3;
}

// =========================================================================================================
// 0115d990
// =========================================================================================================
// @ 0x0115d990
void D::FUN_0115d990(int param_2, int param_3, int param_4, int param_5)
{
    int self = (int)this;
    int iVar1;
    int iVar2;
    int iVar3;
    void* _Dst;
    int iVar4;
    void* _Src;
    float fVar5;
    int local_238;
    int local_234;
    int iStack_230;
    int local_22c;
    float* local_228;
    int iStack_224;
    int local_220;
    int iStack_21c;
    int local_218;
    unsigned sStack_214;
    void* pvStack_210;
    int iStack_20c;
    float local_200[128];

    if (*(char*)(self + 0x38) != 0) {
        fVar5 = 0.9921875f;
        iVar2 = 0;
        do {
            local_200[iVar2] = fVar5;
            iVar2 = iVar2 + 1;
            fVar5 = fVar5 - 0.0078125f;
        } while (iVar2 < 0x80);
    }
    local_218 = 0;
    if (*(int*)(self + 0x30) > 0) {
        do {
            iVar2 = 0;
            local_234 = *(int*)(param_3 + 4) + (unsigned)*(unsigned short*)(param_3 + 0xe) * local_218 * 4;
            local_220 = *(int*)(param_4 + 4) + (unsigned)*(unsigned short*)(param_4 + 0xe) * local_218 * 4;
            local_22c = 0;
            local_228 = 0;
            local_238 = 0;
            if (*(char*)(self + 0x38) != 0) {
                local_228 = local_200;
                local_238 = 0x80;
            }
            iVar4 = local_218;
            if (param_2 > 0) {
                do {
                    iVar3 = FUN_0115d8e0(iVar4, param_2, iVar2, (int)&local_234);
                    if (local_238 != 0) {
                        iVar4 = local_238;
                        if (iVar3 <= local_238) {
                            iVar4 = iVar3;
                        }
                        local_228 = local_200;
                        (*(void(__thiscall**)(int, int, int, int, int))(self + 4))
                            (*(int*)(self + 4), iVar4, param_5, local_218, (int)&local_234);
                        local_238 = local_238 - iVar4;
                        iVar1 = iVar4 * 4;
                        local_234 = local_234 + iVar1;
                        iStack_230 = iStack_230 + iVar1;
                        local_22c = local_22c + iVar1;
                        local_228 = (float*)((int)local_228 + iVar1);
                        iStack_224 = iStack_224 + iVar1;
                        iVar2 = iVar2 + iVar4;
                        iVar3 = iVar3 - iVar4;
                        local_220 = local_220 + iVar1;
                        iVar4 = local_218;
                    }
                    if (iVar3 != 0) {
                        local_22c = 0;
                        local_228 = 0;
                        (*(void(__thiscall**)(int, int, int, int, int))(self + 4))
                            (*(int*)(self + 4), iVar3, param_5, iVar4, (int)&local_234);
                        iVar1 = iVar3 * 4;
                        local_234 = local_234 + iVar1;
                        iStack_230 = iStack_230 + iVar1;
                        local_22c = local_22c + iVar1;
                        local_228 = (float*)((int)local_228 + iVar1);
                        iStack_224 = iStack_224 + iVar1;
                        iVar2 = iVar2 + iVar3;
                        local_220 = local_220 + iVar1;
                    }
                    FUN_0114d9f0(&pvStack_210, iVar4, 0);
                    _Src = (void*)(iStack_224 + iVar2 * -4);
                    _Dst = FUN_0114da40((int)&pvStack_210);
                    if (iVar2 < iStack_20c - (int)pvStack_210 >> 2) {
                        iVar3 = iStack_20c - (int)_Dst >> 2;
                        iStack_21c = iVar2;
                        if (iVar3 <= iVar2) {
                            iStack_21c = iVar3;
                        }
                        sStack_214 = iStack_21c * 4;
                        VectorBool_DoInsertValue(_Dst, _Src, sStack_214);
                        VectorBool_DoInsertValue(pvStack_210, (void*)(sStack_214 + (int)_Src),
                                                 (iVar2 - iStack_21c) * 4);
                    }
                } while (iVar2 < param_2);
            }
            local_218 = iVar4 + 1;
        } while (local_218 < *(int*)(self + 0x30));
    }
    iVar2 = *(int*)(self + 0x14);
    iVar3 = (*(int*)(self + 0x34) + param_2) % iVar2;
    *(int*)(self + 0x34) = iVar3;
    iVar4 = *(int*)(self + 0x18);
    if (*(int*)(self + 0x18) < iVar3) {
        iVar4 = iVar3;
    }
    *(int*)(self + 0x34) = iVar4;
    iVar4 = *(int*)(self + 0x24) + param_2;
    if (iVar2 <= iVar4) {
        iVar4 = iVar2;
    }
    *(int*)(self + 0x24) = iVar4;
    param_2 = param_2 + *(int*)(self + 0x20);
    *(char*)(self + 0x38) = 0;
    if (iVar2 <= param_2) {
        *(int*)(self + 0x20) = iVar2;
        return;
    }
    *(int*)(self + 0x20) = param_2;
}

// =========================================================================================================
// 0115dc10
// =========================================================================================================
// @ 0x0115dc10
void D::FUN_0115dc10(float* param_2, short* param_3, float* param_4)
{
    int iVar3 = *(int*)((int)this + 0x44);
    float fVar26 = 1.0f / (float)(int)*param_3;
    if (iVar3 > 0) {
        unsigned long long uVar1 = *(unsigned long long*)(param_3 + 8);
        unsigned long long uVar2 = *(unsigned long long*)(param_3 + 0xc);
        int iVar18 = (int)(short)(uVar1 >> 0x20);
        int iVar19 = (int)(short)(uVar1 >> 0x30);
        int iVar16 = (int)(short)uVar1;
        int iVar17 = (int)(short)(uVar1 >> 0x10);
        int iVar22 = (int)(short)(uVar2 >> 0x20);
        int iVar23 = (int)(short)(uVar2 >> 0x30);
        int iVar20 = (int)(short)uVar2;
        int iVar21 = (int)(short)(uVar2 >> 0x10);
        short* psVar12 = param_3 + 8;
        float* pfVar15 = param_4;
        float* pfVar14 = pfVar15;
        float* pfVar13 = param_2;
        do {
            pfVar14 = pfVar15;
            pfVar13 = param_2;
            float fVar27 = (float)iVar18;
            float fVar28 = (float)iVar19;
            float fVar24 = (float)iVar16;
            float fVar25 = (float)iVar17;
            float fVar31 = (float)iVar22;
            float fVar32 = (float)iVar23;
            float fVar29 = (float)iVar20;
            float fVar30 = (float)iVar21;
            uVar1 = *(unsigned long long*)(psVar12 + 8);
            uVar2 = *(unsigned long long*)(psVar12 + 0xc);
            float fVar4 = pfVar13[0];
            float fVar5 = pfVar13[1];
            float fVar6 = pfVar13[2];
            float fVar7 = pfVar13[3];
            float fVar8 = pfVar13[4];
            float fVar9 = pfVar13[5];
            float fVar10 = pfVar13[6];
            float fVar11 = pfVar13[7];
            iVar18 = (int)(short)(uVar1 >> 0x20);
            iVar19 = (int)(short)(uVar1 >> 0x30);
            iVar16 = (int)(short)uVar1;
            iVar17 = (int)(short)(uVar1 >> 0x10);
            iVar22 = (int)(short)(uVar2 >> 0x20);
            iVar23 = (int)(short)(uVar2 >> 0x30);
            iVar20 = (int)(short)uVar2;
            iVar21 = (int)(short)(uVar2 >> 0x10);
            pfVar14[0] = pfVar14[0] + (fVar4 * (fVar24 * fVar26) - fVar5 * (fVar25 * fVar26));
            pfVar14[1] = pfVar14[1] + (fVar5 * (fVar24 * fVar26) + fVar4 * (fVar25 * fVar26));
            pfVar14[2] = pfVar14[2] + (fVar6 * (fVar27 * fVar26) - fVar7 * (fVar28 * fVar26));
            pfVar14[3] = pfVar14[3] + (fVar7 * (fVar27 * fVar26) + fVar6 * (fVar28 * fVar26));
            pfVar14[4] = pfVar14[4] + (fVar8 * (fVar29 * fVar26) - fVar9 * (fVar30 * fVar26));
            pfVar14[5] = pfVar14[5] + (fVar9 * (fVar29 * fVar26) + fVar8 * (fVar30 * fVar26));
            pfVar14[6] = pfVar14[6] + (fVar10 * (fVar31 * fVar26) - fVar11 * (fVar32 * fVar26));
            pfVar14[7] = pfVar14[7] + (fVar11 * (fVar31 * fVar26) + fVar10 * (fVar32 * fVar26));
            pfVar15 = pfVar14 + 8;
            psVar12 = psVar12 + 8;
            param_2 = pfVar13 + 8;
        } while (pfVar15 != param_4 + iVar3 + -8);
        float fVar4 = pfVar13[8];
        float fVar5 = pfVar13[9];
        float fVar6 = pfVar13[10];
        float fVar7 = pfVar13[0xb];
        float fVar8 = pfVar13[0xc];
        float fVar9 = pfVar13[0xd];
        float fVar10 = pfVar13[0xe];
        float fVar11 = pfVar13[0xf];
        pfVar15[0] = pfVar15[0] + (fVar4 * ((float)iVar16 * fVar26) - fVar5 * ((float)iVar17 * fVar26));
        pfVar14[9] = pfVar14[9] + (fVar5 * ((float)iVar16 * fVar26) + fVar4 * ((float)iVar17 * fVar26));
        pfVar14[10] = pfVar14[10] + (fVar6 * ((float)iVar18 * fVar26) - fVar7 * ((float)iVar19 * fVar26));
        pfVar14[0xb] = pfVar14[0xb] + (fVar7 * ((float)iVar18 * fVar26) + fVar6 * ((float)iVar19 * fVar26));
        pfVar14[0xc] = pfVar14[0xc] + (fVar8 * ((float)iVar20 * fVar26) - fVar9 * ((float)iVar21 * fVar26));
        pfVar14[0xd] = pfVar14[0xd] + (fVar9 * ((float)iVar20 * fVar26) + fVar8 * ((float)iVar21 * fVar26));
        pfVar14[0xe] = pfVar14[0xe] + (fVar10 * ((float)iVar22 * fVar26) - fVar11 * ((float)iVar23 * fVar26));
        pfVar14[0xf] = pfVar14[0xf] + (fVar11 * ((float)iVar22 * fVar26) + fVar10 * ((float)iVar23 * fVar26));
    }
}

// =========================================================================================================
// 0115ddd0
// =========================================================================================================
// @ 0x0115ddd0
extern "C" void __cdecl FUN_0115ddd0(__m64* param_1, int param_2)
{
    __m64* puVar1 = (__m64*)((int)param_1 + param_2 * 2);
    do {
        __m64 uVar2 = param_1[0];
        __m64 uVar3 = param_1[1];
        param_1[0] = _mm_or_si64(_mm_srli_pi16(uVar2, 8), _mm_slli_pi16(uVar2, 8));
        param_1[1] = _mm_or_si64(_mm_srli_pi16(uVar3, 8), _mm_slli_pi16(uVar3, 8));
        param_1 = param_1 + 2;
    } while (param_1 != puVar1);
    _mm_empty();
}
