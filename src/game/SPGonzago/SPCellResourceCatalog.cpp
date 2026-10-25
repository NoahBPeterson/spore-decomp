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
// ---- items of slice s00e819b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool SP_sCellResourceLoadFailure(int param_1, int* param_2);  // 0x00e82140 (stays in the slice: not this object's)
bool FUN_00e821d0(unsigned id, int param_2, int* param_3);  // 0x00e821d0 (stays in the slice: not this object's)

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
