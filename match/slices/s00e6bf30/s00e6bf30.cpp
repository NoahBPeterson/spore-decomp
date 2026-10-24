// Slice s00e6bf30 (batch gold1) — SP cell/poison-effect update + UI input helpers.
// Module "Spore" (VS2008 SP1). /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
// All functions here are free (__cdecl) functions.

#include "types.h"

// vtable slot fetch: obj is an object whose first dword is the vtable pointer.
static inline void* VFN(void* obj, int off) { return *(void**)(*(unsigned int*)obj + off); }

extern "C" {
    unsigned int DAT_016b3c28, DAT_016b3c2c, DAT_016b3c30;
    unsigned int DAT_016b3dac, DAT_016b3db0, DAT_016b3db4, DAT_016b3db8;
    unsigned int DAT_016b3dbc, DAT_016b3dc0, DAT_016b3dc4, DAT_016b3dc8, DAT_016b3dcc;
    unsigned int DAT_016b44c8, DAT_016b44a0, DAT_016b44a4, DAT_016b44a8, DAT_016b44ac;
    unsigned int DAT_016b44b0, DAT_016b44b4, DAT_016b44b8, DAT_016b44bc, DAT_016b44c0, DAT_016b44c4;
    unsigned int DAT_016b4498, DAT_016b449c;
    unsigned int DAT_016b3c0c;                // cLocalInputState* base (as int)
    unsigned int g_CellGame;                  // base of SP::gspCellGame
    unsigned int g_CellGfx;                   // base of SP::gspCellGfx
    extern double g_RandomState;               // 0x01601760 EA::Random singleton
}

extern "C" {
    int   FUN_00e679e0(unsigned int, unsigned int, unsigned int);
    void  SP_CreateEffectSafe(unsigned int, unsigned int, unsigned int, void*);
    char  FUN_00e5afc0(unsigned int);
    void  FUN_00e68000(unsigned int, unsigned int, void*);
    void  SP_sPartIntersectTarget(unsigned int, unsigned int, void*);
    void  FUN_00e65a00(unsigned int);
    int   FUN_00b721d0(unsigned int);
    int   FUN_00b72210(unsigned int);
    int   SP_sGetSourceLevel();
    void  FUN_0040ce80(unsigned int);
    int   FUN_00e4ce40(void*);
    void  FUN_00743b50();
    void  FUN_00e82130();
    int   FUN_00e87200(unsigned int, void*, void*, void*, unsigned int, unsigned int);
    char  FUN_00e62120(void*, unsigned int);
    char  FUN_00e6b500(void*);
    unsigned int SP_App();
    void  SP_cViewer_GetWorldRayFromScreenCoords(void*, unsigned int, unsigned int, void*, void*);
    void  SP_cLocalInputState_OnMouseDown(void*, int, unsigned int, unsigned int, unsigned int);
    void  FUN_00e643e0(unsigned int);
    char  FUN_00e85190();
    unsigned int FUN_00e510f0(char);
    void  FUN_00e82a10(unsigned int);
    void  FUN_00e50d50(unsigned int);
    void  SP_sUpdateZoomButtons(unsigned int);
    void  FUN_00e67be0(unsigned int);
    void  FUN_00e52d80(unsigned int);
    void  FUN_00e62500(unsigned int);
    void  FUN_00e58730(unsigned int);
    int   FUN_00e51430();
    float FUN_00e5bfa0();
    void  FUN_00e29da0(float, int);
    void  FUN_00e5c1a0();
    int   FUN_00b3d400();
    void  FUN_00e15e70(unsigned int);
    void  FUN_0067cae0();
    void  FUN_005fdf40();
    float FUN_00e696a0(unsigned int, unsigned int, unsigned int, unsigned int);
    float FUN_00e69740(unsigned int, unsigned int, unsigned int, unsigned int);
    int   EA_RefCountRelease(const char*, unsigned int, int);
    void  FUN_007c4900(void*, void*);
}
namespace eastl { void vector_uint_DoInsertValue(void*, void*); }

// The random helper at 0x009360d0 is a thiscall member: the original sets ecx to the
// EA::Random singleton (mov ecx, 0x1601760) before calling it.
class RandomLinearCongruential { public: double RandomDoubleUniform(); };   // 0x009360d0

// @ 0x00e6bf30
void SP_sUpdatePoisonReleaseEffect(unsigned int param_1, int* param_2, unsigned int param_3,
                                   unsigned int* param_4, unsigned int param_5, int param_6,
                                   char param_7, char param_8, char param_9)
{
    unsigned int uVar5 = 0;
    if (param_7 != 0)
    {
        int local_6c = FUN_00e679e0(param_4[0], param_4[1], param_4[2]);
        int local_78 = 0;
        if (0 < *(int*)(local_6c + 0x1274))
        {
            unsigned int* local_7c = (unsigned int*)(local_6c + 0x1278);
            do
            {
                unsigned int local_70 = *local_7c;
                int* local_80 = (int*)0;
                if (uVar5 < (unsigned int)((param_2[1] - *param_2) >> 2))
                {
                    int* piVar2 = *(int**)(*param_2 + uVar5 * 4);
                    if (piVar2 != 0)
                    {
                        ((void(__thiscall*)(void*))VFN(piVar2, 0))(piVar2);
                        local_80 = piVar2;
                    }
                }
                else
                {
                    if (param_8 != 0)
                        SP_CreateEffectSafe(param_1, 0x54c94a74u, 0, &local_80);
                    int* piVar2 = local_80;
                    if (param_9 == 0)
                    {
                        if (local_80 != 0)
                        {
                            local_80 = 0;
                            ((void(__thiscall*)(void*))VFN(piVar2, 4))(piVar2);
                        }
                        SP_CreateEffectSafe(param_1, 0x9cfd5e8au, 0, &local_80);
                        char cVar4 = FUN_00e5afc0(param_3);
                        if (cVar4 != 0)
                            ((void(__thiscall*)(void*, int, const char*, int))VFN(local_80, 0x44))
                                (local_80, 4, "333?333@cell_ending", 1);
                    }
                    else if (param_6 == 1)
                    {
                        if (local_80 != 0) { local_80 = 0; ((void(__thiscall*)(void*))VFN(piVar2, 4))(piVar2); }
                        SP_CreateEffectSafe(param_1, 0xf8eb2d4du, 0, &local_80);
                    }
                    else if (param_6 == 2)
                    {
                        if (local_80 != 0) { local_80 = 0; ((void(__thiscall*)(void*))VFN(piVar2, 4))(piVar2); }
                        SP_CreateEffectSafe(param_1, 0x71877630u, 0, &local_80);
                    }
                    else if (param_6 == 3)
                    {
                        if (local_80 != 0) { local_80 = 0; ((void(__thiscall*)(void*))VFN(piVar2, 4))(piVar2); }
                        SP_CreateEffectSafe(param_1, 0xa3572f53u, 0, &local_80);
                    }
                    ((void(__thiscall*)(void*, int))VFN(local_80, 8))(local_80, 1);
                    ((void(__thiscall*)(void*))VFN((void*)param_4, 0))((void*)param_4);
                    unsigned int* puVar1 = (unsigned int*)param_2[1];
                    int* piStack_74 = local_80;
                    if (puVar1 < (unsigned int*)param_2[2])
                    {
                        param_2[1] = (int)(puVar1 + 1);
                        if (puVar1 != 0) *puVar1 = (unsigned int)local_80;
                    }
                    else
                    {
                        eastl::vector_uint_DoInsertValue(puVar1, &piStack_74);
                    }
                }

                unsigned char target[0x40];
                *(unsigned int*)(target + 0x04) = DAT_016b3c28;
                *(unsigned int*)(target + 0x08) = DAT_016b3c2c;
                *(float*)(target + 0x0c) = *(float*)&DAT_016b3c30;
                *(unsigned int*)(target + 0x10) = 0x3f800000u;
                *(unsigned int*)(target + 0x14) = DAT_016b3dac;
                *(unsigned int*)(target + 0x18) = DAT_016b3db0;
                *(unsigned int*)(target + 0x1c) = DAT_016b3db4;
                *(unsigned int*)(target + 0x20) = DAT_016b3db8;
                *(unsigned int*)(target + 0x24) = DAT_016b3dbc;
                *(unsigned int*)(target + 0x28) = DAT_016b3dc0;
                *(unsigned int*)(target + 0x2c) = DAT_016b3dc4;
                *(unsigned int*)(target + 0x30) = DAT_016b3dc8;
                *(unsigned int*)(target + 0x34) = DAT_016b3dcc;
                *(unsigned short*)(target + 0x00) = 0;
                *(unsigned short*)(target + 0x02) = 0;

                FUN_00e68000(param_3, local_70, target);
                *(unsigned int*)(target + 0x24) = *(unsigned int*)(target + 0x04);
                float fVar3 = (float)(int)uVar5;
                *(unsigned int*)(target + 0x28) = *(unsigned int*)(target + 0x08);
                if ((int)uVar5 < 0) fVar3 = fVar3 + 4.2949673e+09f;
                *(short*)(target + 0x02) = *(short*)(target + 0x02) + 1;
                *(float*)(target + 0x0c) = fVar3 * 0.1f + *(float*)(target + 0x0c);
                *(unsigned short*)(target + 0x00) = *(unsigned short*)(target + 0x00) | 4;
                local_70 = uVar5;
                SP_sPartIntersectTarget((unsigned int)local_80, param_5, target);
                uVar5 = uVar5 + 1;
                if (local_80 != 0)
                    ((void(__thiscall*)(void*))VFN(local_80, 4))(local_80);
                local_7c = local_7c + 1;
                local_78 = local_78 + 1;
            } while (local_78 < *(int*)(local_6c + 0x1274));
        }
    }
    int iVar6 = (param_2[1] - *param_2) >> 2;
    while (iVar6 = iVar6 - 1, (int)uVar5 <= iVar6)
    {
        FUN_00e65a00(*param_2 + iVar6 * 4);
        param_2[1] = param_2[1] - 4;
    }
}

// @ 0x00e6c330
void FUN_00e6c330(void)
{
    int iVar2 = FUN_00b721d0(*(unsigned int*)(g_CellGame + 0x411c));
    if (iVar2 == 0)
        return;

    if ((DAT_016b44c8 & 1) == 0)
    {
        DAT_016b44c8 |= 1;
        DAT_016b44a0 = EA_RefCountRelease("cell_hero_L1_decorations", 0x811c9dc5u, 1);
        DAT_016b44a4 = EA_RefCountRelease("cell_hero_L2_decorations", 0x811c9dc5u, 1);
        DAT_016b44a8 = EA_RefCountRelease("cell_hero_L4_decorations", 0x811c9dc5u, 1);
        DAT_016b44ac = EA_RefCountRelease("cell_hero_L10_decorations", 0x811c9dc5u, 1);
        DAT_016b44b0 = EA_RefCountRelease("cell_hero_L20_decorations", 0x811c9dc5u, 1);
        DAT_016b44b4 = EA_RefCountRelease("cell_hero_L40_decorations", 0x811c9dc5u, 1);
        DAT_016b44b8 = EA_RefCountRelease("cell_hero_L100_decorations", 0x811c9dc5u, 1);
        DAT_016b44bc = EA_RefCountRelease("cell_hero_L200_decorations", 0x811c9dc5u, 1);
        DAT_016b44c0 = EA_RefCountRelease("cell_hero_L400_decorations", 0x811c9dc5u, 1);
        DAT_016b44c4 = EA_RefCountRelease("cell_hero_L400_decorations", 0x811c9dc5u, 1);
    }
    if ((DAT_016b44c8 & 2) == 0)
    {
        DAT_016b44c8 |= 2;
        DAT_016b449c = EA_RefCountRelease("cell_hero_NoEyes", 0x811c9dc5u, 1);
    }
    if ((DAT_016b44c8 & 4) == 0)
    {
        DAT_016b44c8 |= 4;
        DAT_016b4498 = EA_RefCountRelease("cell_hero_OnePairEyes", 0x811c9dc5u, 1);
    }

    int iVar3 = SP_sGetSourceLevel();
    unsigned char s1[0x38];
    unsigned char s2[0x40];
    unsigned int uVar7;
    void* puVar9;

    if (*(int*)(g_CellGfx + 0x16258) == iVar3 && *(int*)(g_CellGfx + 0x164) != 0)
    {
        void* p = *(void**)(g_CellGfx + 0x164);
        char cVar1 = ((char(__thiscall*)(void*))VFN(p, 0x10))(p);
        if (cVar1 == 0)
            ((void(__thiscall*)(void*, int))VFN(*(void**)(g_CellGfx + 0x164), 8))(*(void**)(g_CellGfx + 0x164), 0);
        FUN_0040ce80(iVar2 + 0xc0);
        *(unsigned int*)(s1 + 0x10) = 0x3f800000u;
        FUN_0040ce80(iVar2 + 0x48);
        uVar7 = *(unsigned int*)(g_CellGfx + 0x164);
        puVar9 = s1;
        (void)s2;
    }
    else
    {
        *(int*)(g_CellGfx + 0x16258) = iVar3;
        int iVar4 = FUN_00e679e0(*(unsigned int*)(iVar2 + 0xfc), *(unsigned int*)(iVar2 + 0x100),
                                 *(unsigned int*)(iVar2 + 0x104));
        FUN_00743b50();
        unsigned char la[4];
        int iVar5 = FUN_00e4ce40(la);
        iVar5 = *(int*)(iVar5 + 0xe4);
        FUN_00e82130();
        uVar7 = DAT_016b449c;
        void* piVar6;
        if (iVar5 == 0)
        {
            if (*(int*)(iVar4 + 0x1230) == 0)
                piVar6 = *(void**)(g_CellGfx + 0x164);
            else
            {
                uVar7 = (&DAT_016b449c)[iVar3];
                piVar6 = *(void**)(g_CellGfx + 0x164);
            }
        }
        else
        {
            if (*(int*)(iVar4 + 0x1230) != 0 && (uVar7 = DAT_016b4498, 2 < *(int*)(iVar4 + 0x1230)))
                uVar7 = (&DAT_016b449c)[iVar3];
            piVar6 = *(void**)(g_CellGfx + 0x164);
        }
        if (piVar6 != 0)
        {
            ((void(__thiscall*)(void*, int))VFN(piVar6, 0xc))(piVar6, 1);
            piVar6 = *(void**)(g_CellGfx + 0x164);
            if (piVar6 != 0)
            {
                *(unsigned int*)(g_CellGfx + 0x164) = 0;
                ((void(__thiscall*)(void*))VFN(piVar6, 4))(piVar6);
            }
        }
        piVar6 = *(void**)(g_CellGfx + 0x164);
        unsigned int* puVar8 = (unsigned int*)(g_CellGfx + 0x164);
        if (piVar6 != 0)
        {
            *puVar8 = 0;
            ((void(__thiscall*)(void*))VFN(piVar6, 4))(piVar6);
        }
        SP_CreateEffectSafe(*(unsigned int*)(g_CellGfx + 0x161c8), uVar7, 0, puVar8);
        ((void(__thiscall*)(void*, int))VFN(*(void**)(g_CellGfx + 0x164), 8))(*(void**)(g_CellGfx + 0x164), 0);

        *(unsigned short*)(s1 + 0x00) = *(unsigned short*)(iVar2 + 0xc0);
        *(short*)(s1 + 0x02) = *(short*)(iVar2 + 0xc2);
        *(unsigned int*)(s1 + 0x04) = *(unsigned int*)(iVar2 + 0xc4);
        *(unsigned int*)(s1 + 0x08) = *(unsigned int*)(iVar2 + 200);
        *(unsigned int*)(s1 + 0x0c) = *(unsigned int*)(iVar2 + 0xcc);
        *(unsigned int*)(s1 + 0x10) = *(unsigned int*)(iVar2 + 0xd0);
        *(unsigned int*)(s1 + 0x10) = 0x3f800000u;
        *(short*)(s1 + 0x02) = *(short*)(s1 + 0x02) + 1;

        *(unsigned int*)(s2 + 0x04) = *(unsigned int*)(iVar2 + 0x4c);
        *(unsigned short*)(s2 + 0x00) = *(unsigned short*)(iVar2 + 0x48);
        *(short*)(s2 + 0x02) = *(short*)(iVar2 + 0x4a);
        *(unsigned int*)(s2 + 0x08) = *(unsigned int*)(iVar2 + 0x50);
        *(unsigned int*)(s2 + 0x0c) = *(unsigned int*)(iVar2 + 0x54);
        uVar7 = *(unsigned int*)(g_CellGfx + 0x164);
        puVar9 = s1;
    }
    *(short*)(s2 + 0x02) = *(short*)(s2 + 0x02) + 1;
    *(unsigned int*)(s2 + 0x10) = 0x3f800000u;
    SP_sPartIntersectTarget(uVar7, (unsigned int)puVar9, s2);
}

// @ 0x00e6c780
int FUN_00e6c780(void)
{
    int* piVar2 = (int*)SP_App();
    unsigned char local_818[12];
    unsigned char local_80c[12];
    unsigned int auStack_800[512];

    ((void(__thiscall*)(void*, void*, void*))VFN(piVar2, 0x58))(piVar2, local_818, local_80c);
    FUN_007c4900(local_818, local_80c);
    int iVar3 = FUN_00e87200(*(unsigned int*)(g_CellGame + 0x40fc), local_818, local_80c,
                             auStack_800, 0x200, 0x7f7fffff);
    int iVar4 = 0;
    if (0 < iVar3)
    {
        do
        {
            int* piVar2b = (int*)FUN_00b72210(auStack_800[iVar4]);
            if (*piVar2b != *(int*)(g_CellGame + 0x411c) && *(char*)((char*)piVar2b + 0x112) == 0)
            {
                char cVar1 = FUN_00e62120(piVar2b, DAT_016b3c0c + 0x910);
                if (cVar1 != 0)
                    return *piVar2b;
                cVar1 = FUN_00e6b500(piVar2b);
                if (cVar1 != 0)
                    return *piVar2b;
            }
            iVar4 = iVar4 + 1;
        } while (iVar4 < iVar3);
    }
    return 0;
}

// @ 0x00e6c860
unsigned int FUN_00e6c860(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    SP_cLocalInputState_OnMouseDown((void*)DAT_016b3c0c, param_1, param_2, param_3, param_4);
    if ((param_4 & 3) != 0)
    {
        int* piVar3 = (int*)SP_App();
        unsigned char auStack_818[12];
        unsigned char auStack_80c[12];
        float afStack_800[512];
        void* pcVar4 = (void*)((void*(__thiscall*)(void*, unsigned int, unsigned int, void*, void*))
                                    VFN(piVar3, 0x58))(piVar3, param_2, param_3, auStack_80c, auStack_818);
        SP_cViewer_GetWorldRayFromScreenCoords(pcVar4, param_2, param_3, auStack_80c, auStack_818);
        int iVar2 = FUN_00e87200(*(unsigned int*)(g_CellGame + 0x40fc), auStack_80c, auStack_818,
                                 afStack_800, 0x200, 0x7f7fffff);
        if (iVar2 != 0)
            *(float*)(DAT_016b3c0c + 0x40) = afStack_800[0];
        return 1;
    }
    unsigned int uVar1 = FUN_00e6c780();
    if (param_1 == 1000 && uVar1 != 0)
        FUN_00e643e0(uVar1);
    FUN_00743b50();
    unsigned char auStack_81c[4];
    int iVar2 = FUN_00e4ce40(auStack_81c);
    iVar2 = *(int*)(iVar2 + 0xd4);
    FUN_00e82130();
    if (iVar2 == 1)
    {
        if ((param_1 == 1000 || param_1 == 0x3ea) && uVar1 != 0)
        {
            *(unsigned int*)(DAT_016b3c0c + 0x40) = uVar1;
            return 1;
        }
    }
    else if (iVar2 == 2 && param_1 == 1000 && uVar1 != 0)
    {
        *(unsigned int*)(DAT_016b3c0c + 0x40) = uVar1;
        return 1;
    }
    *(unsigned int*)(DAT_016b3c0c + 0x40) = 0;
    return 0;
}

// @ 0x00e6c9f0  (SP::sUpdateUI)
void FUN_00e6c9f0(unsigned int param_1)
{
    char uVar1 = FUN_00e85190();
    unsigned int uVar2 = FUN_00e510f0(uVar1);
    FUN_00e82a10(uVar2);
    FUN_00e50d50(param_1);
    SP_sUpdateZoomButtons(param_1);
    FUN_00e67be0(param_1);
    FUN_00e52d80(param_1);
    FUN_00e62500(param_1);
    FUN_00e58730(param_1);
    int iVar3 = FUN_00e51430();
    float fVar4 = FUN_00e5bfa0();
    FUN_00e29da0(fVar4, iVar3 - *(int*)(*(int*)(g_CellGame + 0x5190) + 0x2c));
    FUN_00e5c1a0();
    int iVar3b = FUN_00b3d400();
    if (iVar3b != 0)
        FUN_00e15e70(param_1);
    FUN_0067cae0();
    FUN_005fdf40();
}

// @ 0x00e6cad0
void FUN_00e6cad0(unsigned int param_1, unsigned int param_2, unsigned int param_3,
                  unsigned int param_4, float* param_5, float* param_6)
{
    double fVar1 = FUN_00e696a0(param_1, param_2, param_3, param_4);
    if (fVar1 == 0.0)
    {
        *param_5 = 0.0f;
        *param_6 = 0.0f;
        return;
    }
    double fVar2 = FUN_00e69740(param_1, param_2, param_3, param_4);
    double fVar3 = ((RandomLinearCongruential*)&g_RandomState)->RandomDoubleUniform();
    fVar1 = fVar2 + fVar1;
    fVar3 = fVar3 * fVar1;
    if (fVar3 < fVar1)
    {
        fVar1 = fVar3;
        if (fVar3 < 0.0)
            fVar1 = 0.0;
    }
    if (fVar1 <= fVar2)
    {
        *param_5 = 0.0f;
        *param_6 = (float)fVar1;
        return;
    }
    *param_5 = (float)(fVar1 - fVar2);
    *param_6 = 0.0f;
}
