// match/slices/s00de1710/s00de1710.cpp
// Slice s00de1710 -- Spore SP::cGalaxyGameEntryUIStateMachine UI state helpers
// (SporeApp.exe 0x00de1710..0x00de2399).
//
//  00de1710  cGalaxyGameEntryUIStateMachine::Enter        reset + wire up the galaxy-game-entry UI
//  00de1a90  cGalaxyGameEntryUIStateMachine::OnExit0      teardown the pending effect if +0x38 is set
//  00de1ae0  cGalaxyGameEntryUIStateMachine::OnMessage    the 0x287259f6 message dispatch switch
//  00de1e50  cGalaxyGameEntryUIStateMachine::RefreshSet   walk the +0x24 tree, refresh the selection set
//  00de20e0  cGalaxyGameEntryUIStateMachine::SelectItem   walk the +0x24 tree, highlight param_2
//  00de2180  cGalaxyGameEntryUIStateMachine::Refresh      refresh the +4 tree and update +0x6c/+0x68
//  00de2350  delete the singly-linked cString lists in an array (helper)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"
#include <intrin.h>

extern int* kGUI_PanelIDs;                  // 0x016a1344  the GUI panel base pointer
extern int* sAppPreferences;                // 0x015fd91c  SP::_sAppPreferences

// --- the cSPUILayout / cSPUIGlobalUI singles used at the call sites --------------------------------------
struct Layout {
    int* FindWindowByID(int id, int flag);          // 0x008105b0  __thiscall
};
struct GlobalUI {
    int* FindWindowByID(int id);                    // 0x00e012b0  __thiscall
    void SetVisibility(int v);                      // 0x00e01350  __thiscall
};

// --- free helpers -----------------------------------------------------------------------------------------
void  __cdecl FUN_00de11a0_call(int);                       // 0x00de11a0  (ecx = this)
void  __cdecl SP_cSPUISpace_KillSetiEffects(int, int);      // 0x00435ed0
void  __cdecl SP_cSPUIAssetBrowser_AdvancedLaunch(void*);   // 0x0064a990
void  __cdecl FUN_00de53d0(int);                            // 0x00de53d0  (ecx = kGUI_PanelIDs)
void  __cdecl FUN_00644b10();                               // 0x00644b10
int   __cdecl FUN_00644b60();                               // 0x00644b60
char  __cdecl FUN_00685520(int);                            // 0x00685520
void  __cdecl FUN_005dd750(void*);                          // 0x005dd750
void  __cdecl FUN_00407190(void*, int, void*);              // 0x00407190  GetBoolProperty
int*  __cdecl SP_MovieSystem();                             // 0x0067cb10
int*  __cdecl SP_AppSystem();                               // 0x0067dd00
int*  __cdecl SP_GetSaveArea(int, int);                     // SP::GetSaveArea
void  __cdecl SP_SaveResource(void*, void*);                // SP::SaveResource
int*  __cdecl EA_Audio_GetSystemAT();                       // 0x00a206f0
void  __cdecl EA_Variant_Destruct(void*, int);              // EA::Variant::Destruct
void  __cdecl EA_Stopwatch_SetUnits(void*, int);            // 0x0093a1a0
void  __fastcall SP_cString_dtor(void*);                   // 0x006b5240
int*  __cdecl FUN_00dd9190(int, int);                       // 0x00dd9190  __stdcall
struct HT {
    void find(void*, void*);                                // 0x00aea1b0  eastl hashtable::find
};

struct LI { unsigned LowPart; int HighPart; };
extern "C" int __stdcall QueryPerformanceCounter(LI*);
extern "C" void __cdecl operator_delete(void*);              // 0x00f47380  ??3@YAXPAX@Z

struct SG {
    void  FUN_00de11a0();                                   // 0x00de11a0
    char  FUN_00de13d0(int, int);                           // 0x00de13d0
    void  FUN_00de0ae0(int);                                // 0x00de0ae0  $E441
    void  FUN_00de0670(int, int);                           // 0x00de0670
    void  FUN_00de5330(int);                                // 0x00de5330
    void  FUN_00de5260();                                   // 0x00de5260
    void  FUN_00de5300();                                   // 0x00de5300
    void  FUN_00dda090();                                   // 0x00dda090
    void  FUN_00de1a90(int);
    bool  FUN_00de1ae0(int, void*);
    void  FUN_00de1e50(float, float, int);
    void  FUN_00de20e0(int);
    void  FUN_00de2180(float, float, int);
};

// =========================================================================================================
// 00de1710
// =========================================================================================================
// @ 0x00de1710
extern "C" void __fastcall FUN_00de1710(int param_1)
{
    int* piVar4;
    int* piVar1;
    int* piVar6;
    unsigned uVar5;
    LI LStack_8;

    *(int*)(param_1 + 0x38) = 0;
    ((SG*)*(void**)((char*)kGUI_PanelIDs + 0x198))->FUN_00de0670(1, 0);
    ((SG*)kGUI_PanelIDs)->FUN_00de5330(0);
    ((SG*)kGUI_PanelIDs)->FUN_00de5260();
    piVar4 = SP_MovieSystem();
    if (piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)piVar4))[0x40 / 4])(piVar4, 1);
    }
    ((SG*)kGUI_PanelIDs)->FUN_00de5300();
    *(int*)(param_1 + 0xa8) = 0;
    *(char*)(param_1 + 0x21) = 0;
    *(char*)(param_1 + 0xd0) = 0;
    piVar4 = ((Layout*)((char*)kGUI_PanelIDs + 0x144))->FindWindowByID(0x615a5ff, 1);
    if (piVar4 != 0) {
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x7c / 4])(piVar4, 1, 0);
    }
    ((GlobalUI*)*(void**)((char*)kGUI_PanelIDs + 0x184))->SetVisibility(1);
    *(int*)(param_1 + 0x38) = 0;
    EA_Stopwatch_SetUnits((void*)(param_1 + 8), 4);
    unsigned uLow;
    if (*(int*)(param_1 + 0x18) == 1) {
        unsigned long long uVar2 = __rdtsc();
        *(int*)(param_1 + 0xc) = (int)(uVar2 >> 0x20);
        uLow = (unsigned)uVar2;
    } else {
        QueryPerformanceCounter(&LStack_8);
        *(int*)(param_1 + 0xc) = LStack_8.HighPart;
        uLow = LStack_8.LowPart;
    }
    *(unsigned*)(param_1 + 8) = uLow;
    *(int*)(param_1 + 0x10) = 0;
    *(int*)(param_1 + 0x14) = 0;
    piVar4 = EA_Audio_GetSystemAT();
    if (piVar4 == 0) {
        uVar5 = 0;
    } else {
        uVar5 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar4))[0x20 / 4])(piVar4);
    }
    piVar4 = EA_Audio_GetSystemAT();
    if (piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)piVar4))[0x38 / 4])(piVar4, 0x3475365);
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x40 / 4])(piVar4, 0x3475381,
                                                                                   0x981429e1);
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x40 / 4])(piVar4, 0x3475385,
                                                                                   (int)uVar5);
        ((void(__thiscall*)(void*))((void**)(*(int**)piVar4))[0x58 / 4])(piVar4);
    }
    piVar4 = (int*)(param_1 + 0x34);
    *(char*)((char*)kGUI_PanelIDs + 0x103) = 1;
    if ((int*)*piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)*piVar4))[0xc / 4])((void*)*piVar4, 0);
        piVar6 = (int*)*piVar4;
        if (piVar6 != 0) {
            *piVar4 = 0;
            ((void(__thiscall*)(void*))((void**)(*(int**)piVar6))[4 / 4])(piVar6);
        }
    }
    int* puVar7 = *(int**)((char*)kGUI_PanelIDs + 0x1d8);
    if (puVar7 != *(int**)((char*)kGUI_PanelIDs + 0x1dc)) {
        do {
            ((void(__thiscall*)(void*, int))((void**)(*(int**)*puVar7))[0x2c / 4])((void*)*puVar7, 1);
            puVar7 = puVar7 + 1;
        } while (puVar7 != *(int**)((char*)kGUI_PanelIDs + 0x1dc));
    }
    piVar6 = (int*)*piVar4;
    piVar1 = *(int**)((char*)kGUI_PanelIDs + 0x15c);
    if (piVar6 != 0) {
        *piVar4 = 0;
        ((void(__thiscall*)(void*))((void**)(*(int**)piVar6))[4 / 4])(piVar6);
    }
    ((void(__thiscall*)(void*, int, int, int*))((void**)(*(int**)piVar1))[8 / 4])(piVar1, 0xb0237cdc,
                                                                                    0, piVar4);
    if ((int*)*piVar4 != 0) {
        ((void(__thiscall*)(void*, int))((void**)(*(int**)*piVar4))[8 / 4])((void*)*piVar4, 0);
    }
    char cVar3 = FUN_00685520(2);
    if (cVar3 == 0) goto LAB_00de1982;
    piVar4 = ((GlobalUI*)*(void**)((char*)kGUI_PanelIDs + 0x184))->FindWindowByID(0x7a7ec60);
    if (piVar4 != 0) {
        if (*(int*)((char*)kGUI_PanelIDs + 0x1f8) == 0) {
            piVar6 = SP_AppSystem();
            uVar5 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar6))[0x54 / 4])(piVar6);
            if ((char)uVar5 != 0) goto LAB_00de1924;
        } else {
LAB_00de1924:
            uVar5 = 1;
        }
        ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x7c / 4])(piVar4, 2,
                                                                                    (int)uVar5);
    }
    piVar4 = ((GlobalUI*)*(void**)((char*)kGUI_PanelIDs + 0x184))->FindWindowByID(0x7291fb7);
    if (piVar4 == 0) goto LAB_00de1982;
    if (*(int*)((char*)kGUI_PanelIDs + 0x1f8) == 0) {
        piVar6 = SP_AppSystem();
        uVar5 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar6))[0x54 / 4])(piVar6);
        if ((char)uVar5 != 0) goto LAB_00de1971;
    } else {
LAB_00de1971:
        uVar5 = 1;
    }
    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar4))[0x7c / 4])(piVar4, 2, (int)uVar5);
LAB_00de1982:
    ((SG*)param_1)->FUN_00de11a0();
    int* pTmp = FUN_00dd9190(2, 0);
    ((SG*)pTmp)->FUN_00dda090();
}

// =========================================================================================================
// 00de1a90
// =========================================================================================================
// @ 0x00de1a90
void SG::FUN_00de1a90(int param_2)
{
    int self = (int)this;
    if (*(int*)(self + 0x38) != 0) {
        void* piVar1 = EA_Audio_GetSystemAT();
        int uVar5 = (piVar1 != 0)
                        ? ((int(__thiscall*)(void*))((void**)(*(int**)piVar1))[0x20 / 4])(piVar1)
                        : 0;
        SP_cSPUISpace_KillSetiEffects(0x8e82b51c, uVar5);
        ((SG*)self)->FUN_00de13d0(*(int*)(self + 0x38), param_2);
    }
}

// =========================================================================================================
// 00de1ae0
// =========================================================================================================
// @ 0x00de1ae0
bool SG::FUN_00de1ae0(int param_2, void* param_3)
{
    int self = (int)this;
    int* piVar1;
    int* piVar2;
    unsigned uVar4;
    unsigned char acStack_7f[3];
    int uStack_7c;
    int uStack_78;
    int uStack_74;
    unsigned long long VStack_70;
    unsigned long long VStack_5c;
    int uStack_48;
    int iStack_44;
    int* puStack_18;
    int iStack_10;
    int p = 0;

    if (((int*)param_3)[2] != 0x287259f6) goto caseD_4096dd1;
    p = ((int(__thiscall*)(void*))((void**)(*(int**)*(int**)param_3))[0x1c / 4])(
        *(void**)param_3);
    piVar1 = sAppPreferences;
    uStack_7c = 0;
    uStack_78 = 0;
    uStack_74 = 0;
    if (p < 0x62afb0e) {
        if (p != 0x62afb0d) {
            if (p < 0x4656453) {
                if (p != 0x4656452) {
                    switch (p) {
                        case 0x4096dd0:
                        case 0x4096dd3:
                        case 0x4096dd7:
                        case 0x4096dda:
                            break;
                        default:
                            goto caseD_4096dd1;
                    }
                }
            } else if (p < 0x6285661) {
                if (p < 0x628565e) {
                    if (p < 0x625cd50) goto caseD_4096dd1;
                    if (0x625cd54 < p) {
                        if (p == 0x6260bc8) {
                            ((SG*)self)->FUN_00de1a90((int)&uStack_7c);
                            *(int*)((char*)kGUI_PanelIDs + 0x108) = 3;
                            *(int*)((char*)kGUI_PanelIDs + 0x10c) = 3;
                            return false;
                        }
                        goto caseD_4096dd1;
                    }
                }
            } else {
                if (p < 0x629c446) goto caseD_4096dd1;
                if (0x629c448 < p) return false;
            }
        }
    caseD_4096dd0:;
    } else {
        if (0x7a7ec60 < p) {
            if (p < 0x7a7f79a) {
                if (p == 0x7a7f799) {
                    FUN_00de53d0(0);
                    FUN_00644b10();
                    iStack_10 = (int)kGUI_PanelIDs;
                    uStack_48 = 0x7edf94a2;
                    *(int*)(self + 0x38) = 0x7a7f799;
                } else {
                    if (p != 0x7a7f798) goto caseD_4096dd1;
                    FUN_00de53d0(0);
                    FUN_00644b10();
                    iStack_10 = (int)kGUI_PanelIDs;
                    uStack_48 = 0x8f6443b2;
                    *(int*)(self + 0x38) = 0x7a7f798;
                }
                puStack_18 = (int*)0x00ad0e52;
                iStack_44 = self;
                SP_cSPUIAssetBrowser_AdvancedLaunch(&uStack_48);
                uVar4 = (unsigned)FUN_00644b60();
                return (uVar4 & 0xffffff00) != 0;
            }
            if (p < 0x1628565e || 0x16285660 < p) goto caseD_4096dd1;
            goto caseD_4096dd0;
        }
        if (p == 0x7a7ec60) {
            acStack_7f[0] = 0;
            FUN_00407190(sAppPreferences, 0x80d8470, acStack_7f);
            if (acStack_7f[0] == 0) {
                piVar2 = ((GlobalUI*)*(void**)((char*)kGUI_PanelIDs + 0x184))
                             ->FindWindowByID(0x809b111);
                if (piVar2 != 0) {
                    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x7c / 4])(
                        piVar2, 1, 0);
                }
                acStack_7f[2] = 1;
                FUN_005dd750(acStack_7f + 2);
                ((void(__thiscall*)(void*, int, unsigned long long*))(
                    (void**)(*(int**)piVar1))[0x14 / 4])(piVar1, 0x80d8470, &VStack_70);
                if (((unsigned char)VStack_70 & 4) != 0) {
                    EA_Variant_Destruct(&VStack_70, 0);
                }
                int* uVar3 = SP_GetSaveArea(0x11ac192, 0);
                SP_SaveResource(piVar1, uVar3);
            }
            p = 0x7a7ec60;
        } else {
            if (p < 0x6526b7e) {
                if (p != 0x6526b7d && p != 0x62afb1c && p != 0x62afb2b) {
                    return false;
                }
                goto caseD_4096dd0;
            }
            if (p != 0x7291fb7) goto caseD_4096dd1;
            acStack_7f[0] = 0;
            FUN_00407190(sAppPreferences, 0x80d8460, acStack_7f);
            if (acStack_7f[0] == 0) {
                piVar2 = ((GlobalUI*)*(void**)((char*)kGUI_PanelIDs + 0x184))
                             ->FindWindowByID(0x7a7ee50);
                if (piVar2 != 0) {
                    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x7c / 4])(
                        piVar2, 1, 0);
                }
                acStack_7f[1] = 1;
                FUN_005dd750(acStack_7f + 1);
                ((void(__thiscall*)(void*, int, unsigned long long*))(
                    (void**)(*(int**)piVar1))[0x14 / 4])(piVar1, 0x80d8460, &VStack_5c);
                if (((unsigned char)VStack_5c & 4) != 0) {
                    EA_Variant_Destruct(&VStack_5c, 0);
                }
                int* uVar3 = SP_GetSaveArea(0x11ac192, 0);
                SP_SaveResource(piVar1, uVar3);
            }
            p = 0x7291fb7;
        }
    }
    ((SG*)self)->FUN_00de0ae0(p);
caseD_4096dd1:
    return false;
}

// =========================================================================================================
// 00de1e50
// =========================================================================================================
// @ 0x00de1e50
void SG::FUN_00de1e50(float param_2, float param_3, int param_4)
{
    int self = (int)this;
    int iVar1;
    char cVar2;
    int* piVar3;
    unsigned uVar4;
    int uVar5;
    int* puVar6;
    unsigned uVar7;
    int local_14;
    int uStack_10;
    int* local_c;
    float local_8[2];

    *(char*)(self + 0x60) = 0;
    local_14 = 0;
    if (*(int*)(self + 0x70) != 0) {
        local_c = *(int**)(self + 0x24);
        puVar6 = (int*)*local_c;
        if (puVar6 == 0) {
            local_c = local_c + 1;
            iVar1 = (int)*local_c;
            while (iVar1 == 0) {
                local_c = local_c + 1;
                iVar1 = (int)*local_c;
            }
            puVar6 = (int*)*local_c;
        }
        if (puVar6 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4)) {
            do {
                piVar3 = ((Layout*)*(void**)(self + 0x70))->FindWindowByID(*puVar6, 1);
                if (piVar3 != 0) {
                    ((void(__thiscall*)(void*, float, float, float*))(
                        (void**)(*(int**)piVar3))[200 / 4])(piVar3, param_2, param_3, local_8);
                    cVar2 = ((char(__thiscall*)(void*, float, float))(
                        (void**)(*(int**)piVar3))[0xbc / 4])(piVar3, local_8[0], local_8[1]);
                    if (cVar2 == 0 || *(char*)(self + 0x60) != 0) {
                        uVar7 = 0;
                        uVar4 = (unsigned)((puVar6[2] - puVar6[1]) >> 2);
                        if (uVar4 != 0) {
                            do {
                                piVar3 = ((Layout*)*(void**)(self + 0x70))
                                             ->FindWindowByID(*(int*)(puVar6[1] + uVar7 * 4), 1);
                                if (piVar3 != 0) {
                                    ((void(__thiscall*)(void*, int, int))(
                                        (void**)(*(int**)piVar3))[0x7c / 4])(piVar3, 1, 0);
                                }
                                uVar7 = uVar7 + 1;
                            } while (uVar7 < uVar4);
                        }
                    } else {
                        uVar4 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x28 / 4])(
                            piVar3);
                        if ((uVar4 & 1) != 0) {
                            local_14 = ((int(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x1c / 4])(
                                piVar3);
                        }
                        uVar4 = 0;
                        uVar7 = (unsigned)((puVar6[2] - puVar6[1]) >> 2);
                        if (uVar7 != 0) {
                            do {
                                if (*(int*)(puVar6[1] + uVar4 * 4) != 0 &&
                                    (piVar3 = ((Layout*)*(void**)(self + 0x70))
                                                  ->FindWindowByID(*(int*)(puVar6[1] + uVar4 * 4), 1),
                                     piVar3 != 0)) {
                                    ((void(__thiscall*)(void*, int, int))(
                                        (void**)(*(int**)piVar3))[0x7c / 4])(piVar3, 1, 1);
                                    *(char*)(self + 0x60) = 1;
                                }
                                uVar4 = uVar4 + 1;
                            } while (uVar4 < uVar7);
                        }
                    }
                }
                puVar6 = (int*)puVar6[6];
                while (puVar6 == 0) {
                    int** piVarTmp = (int**)(local_c + 1);
                    local_c = local_c + 1;
                    puVar6 = (int*)*piVarTmp;
                }
            } while (puVar6 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4));
        }
        if (*(char*)(self + 0x60) == 0 && param_4 != 0) {
            ((HT*)(self + 0x20))->find(local_8, &param_4);
            puVar6 = (int*)*(int*)local_8;
            if ((int)puVar6 != *(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4)) {
                uVar4 = 0;
                uVar7 = (unsigned)((puVar6[2] - puVar6[1]) >> 2);
                if (uVar7 != 0) {
                    do {
                        piVar3 = ((Layout*)*(void**)(self + 0x70))
                                     ->FindWindowByID(*(int*)(puVar6[1] + uVar4 * 4), 1);
                        if (piVar3 != 0) {
                            ((void(__thiscall*)(void*, int, int))(
                                (void**)(*(int**)piVar3))[0x7c / 4])(piVar3, 1, 1);
                            *(char*)(self + 0x60) = 1;
                        }
                        uVar4 = uVar4 + 1;
                    } while (uVar4 < uVar7);
                }
            }
        }
    }
    if (local_14 != *(int*)(self + 100) && local_14 != 0) {
        piVar3 = EA_Audio_GetSystemAT();
        if (piVar3 == 0) {
            uVar5 = 0;
        } else {
            uVar5 = ((int(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x20 / 4])(piVar3);
        }
        piVar3 = EA_Audio_GetSystemAT();
        if (piVar3 != 0) {
            ((void(__thiscall*)(void*, int))((void**)(*(int**)piVar3))[0x38 / 4])(piVar3, 0x3475365);
            ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar3))[0x40 / 4])(
                piVar3, 0x3475381, 0xd607a5a7);
            ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar3))[0x40 / 4])(
                piVar3, 0x3475385, uVar5);
            ((void(__thiscall*)(void*))((void**)(*(int**)piVar3))[0x58 / 4])(piVar3);
        }
    }
    *(int*)(self + 100) = local_14;
}

// =========================================================================================================
// 00de20e0
// =========================================================================================================
// @ 0x00de20e0
void SG::FUN_00de20e0(int param_2)
{
    int self = (int)this;
    if (*(int*)(self + 0x70) != 0) {
        int* piVar4 = *(int**)(self + 0x24);
        int* piVar3 = (int*)*piVar4;
        if (piVar3 == 0) {
            piVar4 = piVar4 + 1;
            int iVar1 = (int)*piVar4;
            while (iVar1 == 0) {
                piVar4 = piVar4 + 1;
                iVar1 = (int)*piVar4;
            }
            piVar3 = (int*)*piVar4;
        }
        if (piVar3 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4)) {
            do {
                int* piVar2 = ((Layout*)*(void**)(self + 0x70))->FindWindowByID(*piVar3, 1);
                if (piVar2 != 0 &&
                    (piVar2 = (int*)((int(__thiscall*)(void*, int))(
                        (void**)(*(int**)piVar2))[0xc / 4])(piVar2, 0x8ed27e7a),
                     piVar2 != 0)) {
                    bool bEq = (*piVar3 == param_2);
                    ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x28 / 4])(
                        piVar2, 4, bEq);
                }
                piVar3 = (int*)piVar3[6];
                while (piVar3 == 0) {
                    piVar3 = (int*)*(piVar4 + 1);
                    piVar4 = piVar4 + 1;
                }
            } while (piVar3 != (int*)*(int*)(*(int*)(self + 0x24) + *(int*)(self + 0x28) * 4));
        }
    }
}

// =========================================================================================================
// 00de2180
// =========================================================================================================
// @ 0x00de2180
void SG::FUN_00de2180(float param_2, float param_3, int param_4)
{
    int self = (int)this;
    char cVar1;
    int* piVar2;
    unsigned uVar3;
    int iVar4;
    unsigned uVar5;
    int* piVar6;
    int* puVar7;
    int uVar8;
    int* local_c;
    float local_8[2];

    ((SG*)self)->FUN_00de1e50(param_2, param_3, param_4);
    ((SG*)self)->FUN_00de20e0(param_4);
    param_4 = 0;
    if (*(int*)(self + 0x70) != 0) {
        piVar2 = *(int**)(self + 4);
        puVar7 = (int*)*piVar2;
        local_c = piVar2;
        if (puVar7 == 0) {
            local_c = piVar2 + 1;
            iVar4 = (int)*local_c;
            while (iVar4 == 0) {
                local_c = local_c + 1;
                iVar4 = (int)*local_c;
            }
            puVar7 = (int*)*local_c;
        }
        iVar4 = 0;
        piVar6 = local_c;
        if (puVar7 != (int*)piVar2[*(int*)(self + 8)]) {
            do {
                piVar2 = ((Layout*)*(void**)(self + 0x70))->FindWindowByID(*puVar7, 1);
                if (piVar2 != 0) {
                    ((void(__thiscall*)(void*, float, float, float*))(
                        (void**)(*(int**)piVar2))[200 / 4])(piVar2, param_2, param_3, local_8);
                    cVar1 = ((char(__thiscall*)(void*, float, float))(
                        (void**)(*(int**)piVar2))[0xbc / 4])(piVar2, local_8[0], local_8[1]);
                    if (cVar1 == 0) {
                        uVar3 = 0;
                        uVar5 = (unsigned)((puVar7[2] - puVar7[1]) >> 2);
                        piVar6 = local_c;
                        if (uVar5 != 0) {
                            do {
                                piVar2 = ((Layout*)*(void**)(self + 0x70))
                                             ->FindWindowByID(*(int*)(puVar7[1] + uVar3 * 4), 1);
                                if (piVar2 != 0) {
                                    ((void(__thiscall*)(void*, int, int))(
                                        (void**)(*(int**)piVar2))[0x7c / 4])(piVar2, 1, 0);
                                }
                                uVar3 = uVar3 + 1;
                            } while (uVar3 < uVar5);
                        }
                    } else if ((int)((puVar7[2] - puVar7[1]) >> 2) != 0) {
                        piVar2 = ((Layout*)*(void**)(self + 0x70))->FindWindowByID((int)puVar7[1], 1);
                        uVar3 = ((unsigned(__thiscall*)(void*))((void**)(*(int**)piVar2))[0x28 / 4])(
                            piVar2);
                        if ((uVar3 & 1) != 0) {
                            param_4 = (int)puVar7[1];
                            *(int*)(self + 0x6c) = param_4;
                        }
                    }
                }
                puVar7 = (int*)puVar7[6];
                while (puVar7 == 0) {
                    int** piVarTmp = (int**)(piVar6 + 1);
                    piVar6 = piVar6 + 1;
                    local_c = piVar6;
                    puVar7 = (int*)*piVarTmp;
                }
                iVar4 = param_4;
            } while (puVar7 != (int*)*(int*)(*(int*)(self + 4) + *(int*)(self + 8) * 4));
        }
        if (*(int*)(self + 0x68) != 0 &&
            (piVar2 = ((Layout*)*(void**)(self + 0x70))->FindWindowByID(*(int*)(self + 0x68), 1),
             piVar2 != 0)) {
            if (iVar4 == 0 || iVar4 == *(int*)(self + 0x68)) {
                uVar8 = 1;
            } else {
                uVar8 = 0;
            }
            ((void(__thiscall*)(void*, int, int))((void**)(*(int**)piVar2))[0x7c / 4])(piVar2, 1,
                                                                                        uVar8);
        }
    }
}

// =========================================================================================================
// 00de2350
// =========================================================================================================
// @ 0x00de2350
extern "C" void __stdcall FUN_00de2350(int* param_1, unsigned param_2)
{
    for (unsigned uVar3 = 0; uVar3 < param_2; uVar3++) {
        int iVar2 = param_1[uVar3];
        while (iVar2 != 0) {
            int iVar1 = iVar2;
            iVar2 = *(int*)(iVar1 + 0x18);
            SP_cString_dtor((void*)(iVar1 + 4));
            operator_delete((void*)iVar1);
        }
        param_1[uVar3] = 0;
    }
}
