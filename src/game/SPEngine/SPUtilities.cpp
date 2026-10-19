// src/game/SPEngine/SPUtilities.cpp -- migrated from slice(s) s006ba2f0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern const char    g_emptyStrC[];   // 0x1667bac

// ---- items of slice s006ba2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int UINT;
typedef void* HWND;
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(HWND, const char*, const char*, UINT);
void __cdecl EASTL_dealloc(void*);
extern const char    g_emptyStrC[];   // 0x1667bac
struct EStrC {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mpAllocator;
    EStrC() : mpBegin((char*)g_emptyStrC), mpEnd((char*)g_emptyStrC), mpCapacity((char*)g_emptyStrC + 1) {}
    ~EStrC() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
int __cdecl EStrC_sprintf(EStrC* s, const char* fmt, ...);
void __cdecl FUN_006baec0(void* path);
// ---- items of slice s006ba2f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(HWND, const char*, const char*, UINT);

// @ 0x006baec0
void __cdecl FUN_006baec0(void* path)
{
    (void)path;
}

// @ 0x006baff0
namespace SP {
void __cdecl SporeAlert(const char* msg, int line, int type)
{
    UINT uType = 0x52000;
    switch (type) {
    case 0: uType = 0x52040; break;
    case 1: uType = 0x52030; break;
    case 2: uType = 0x52010; break;
    }
    EStrC str;
    EStrC_sprintf(&str, "%s [%d]", msg, line);
    MessageBoxA(0, str.mpBegin, "Alert", uType);
}
}  // namespace SP
