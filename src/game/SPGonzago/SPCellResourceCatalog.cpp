// src/game/SPGonzago/SPCellResourceCatalog.cpp -- migrated from slice(s) s00e819b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCellResourceCatalog.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int* gListSentinel;        // 0x016b44f0

// ---- items of slice s00e819b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int* gListSentinel;        // 0x016b44f0
int   DebugNameFromSPID(int a, int b, int c);  // 0x00e4bf30
void  FUN_00e84e40(const char* fmt, ...); // 0x00e84e40
int   EA_ResourceMan_GetManager();        // 0x0067dcd0 (returns ptr)
int   FUN_00e823e0();                     // 0x00e823e0
void  FUN_00f47380(void* p);              // operator delete
// ---- items of slice s00e819b0 end

// @ 0x00e82140
bool SP_sCellResourceLoadFailure(int param_1, int* param_2)
{
    struct { int a; int b; int c; } k;
    k.b = *(int*)(param_1 + 8);
    k.a = 0x7a638526;
    k.c = 0;
    int* mgr = (int*)EA_ResourceMan_GetManager();
    if (((bool(*)(void*,int*,int,int,int,int))mgr[7])(&k, param_2, 0, 0, 0, 0) == 0)
        return false;
    if (*(int*)(param_1 + 0x20) != 0) {
        if (*param_2 != 0) {
            int* o = (int*)(*(int(**)(int))(*(int*)*param_2 + 0xc))(0x2269ed1);
            ((void(*)(int))*(int*)(param_1 + 0x20))(*(int*)((char*)o + 0x14));
            return true;
        }
        ((void(*)(int))*(int*)(param_1 + 0x20))(*(int*)0x14);
    }
    return true;
}

// @ 0x00e821d0
bool FUN_00e821d0(unsigned id, int param_2, int* param_3)
{
    if (id == 0 || id == 0xffffffff)
        return false;
    struct { unsigned a; int b; int c; } k;
    k.a = id;
    k.b = *(int*)(param_2 + 8);
    k.c = 0;
    int* mgr = (int*)EA_ResourceMan_GetManager();
    if (!((bool(*)(void*,int*))mgr[5])(&k, param_3)) {
        int* mgr2 = (int*)EA_ResourceMan_GetManager();
        if (!((bool(*)(void*,int*,int,int,int,int))mgr2[3])(&k, param_3, 0, 0, 0, 0))
            return false;
        int iVar3 = 0;
        if (*param_3 != 0)
            iVar3 = (*(int(**)(int))(*(int*)*param_3 + 0xc))(0x2269ed1);
        if (*(void(**)(int))(param_2 + 0x20) != 0)
            (*(void(**)(int))(param_2 + 0x20))(*(int*)(iVar3 + 0x14));
    }
    return true;
}

// @ 0x00e82280
void FUN_00e82280()
{
    int* p = (int*)*gListSentinel;
    if (p != gListSentinel) {
        do {
            int* q = (int*)p[4];
            if (q != 0) {
                p[4] = 0;
                (*(void(__thiscall*)(void*))(*(void**)((char*)*q + 4)))(q);
            }
            p = (int*)*p;
        } while (p != gListSentinel);
    }
}

// @ 0x00e822c0
namespace SP {
void LoadResource(int* param_1)
{
    int* piVar2 = (int*)param_1[2];
    int* piVar1 = param_1 + 2;
    if (piVar2 != 0) {
        *piVar1 = 0;
        (*(void(__thiscall*)(void*))(*(void**)((char*)*piVar2 + 4)))(piVar2);
    }
    char c = FUN_00e821d0((unsigned)*param_1, param_1[1], piVar1) ? 1 : 0;
    if (c == 0) {
        int uVar4 = DebugNameFromSPID(*param_1, *param_1, *(int*)param_1[1]);
        FUN_00e84e40("cannot load asset id:%s (0x%X), type:%s", uVar4);
        int* piVar2b = (int*)*piVar1;
        if (piVar2b != 0) {
            *piVar1 = 0;
            (*(void(__thiscall*)(void*))(*(void**)((char*)*piVar2b + 4)))(piVar2b);
        }
        SP_sCellResourceLoadFailure(param_1[1], piVar1);
    }
}
}  // namespace SP

// @ 0x00e823a0
int FUN_00e823a0(int param_1, int* param_2)
{
    *param_2 = param_1;
    (*(int*)(param_1 + 0xc))++;
    if (*(int*)(param_1 + 8) == 0)
        SP::LoadResource((int*)param_1);
    if (*(int*)(param_1 + 8) != 0) {
        int iVar1 = (*(int(**)(int))(**(int**)(param_1 + 8) + 0xc))(0x2269ed1);
        return *(int*)(iVar1 + 0x14);
    }
    return *(int*)0x14;
}

// @ 0x00e824d0
void FUN_00e824d0()
{
    FUN_00e82280();
    int iVar1 = (int)gListSentinel;
    if (gListSentinel != 0) {
        FUN_00e823e0();
        FUN_00f47380((void*)iVar1);
    }
}
