// src/game/SPEngine/SPUtilities.cpp -- migrated from slice(s) s006ba2f0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cTransform.h"

// unnamed retail callees and globals (address in the comment)
extern const char    g_emptyStrC[];                                 // 0x1667bac
extern const wchar_t gEmptyString16[];                              // 0x1667bac
extern const wchar_t DAT_01409f64[];                                // 0x1409f64

// ---- items of slice s006ba2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int UINT;
typedef void* HWND;
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(HWND, const char*, const char*, UINT);
void __cdecl EASTL_dealloc(void*);                                  // 0x00f47380
extern const char    g_emptyStrC[];                                 // 0x1667bac
extern const wchar_t gEmptyString16[];                              // 0x1667bac
extern const wchar_t DAT_01409f64[];                                // 0x1409f64
struct EStrC {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mpAllocator;
    EStrC() : mpBegin((char*)g_emptyStrC), mpEnd((char*)g_emptyStrC), mpCapacity((char*)g_emptyStrC + 1) {}
    ~EStrC() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
int __cdecl EStrC_sprintf(EStrC* s, const char* fmt, ...);
bool  __cdecl FUN_009322b0(const void*);                            // 0x009322b0  EA::IO::Directory::Exists
struct EStrWInsert {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mpAllocator;
    void insert(wchar_t* dst, const wchar_t* first, const wchar_t* last);   // 0x005f7da0
};
// ---- items of slice s006ba2f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(HWND, const char*, const char*, UINT);

// @ 0x006baec0
void __cdecl FUN_006baec0(void* path)
{
    EStrWInsert* str = (EStrWInsert*)path;
    EStrWInsert local;
    local.mpBegin = (wchar_t*)gEmptyString16;
    local.mpEnd = (wchar_t*)gEmptyString16;
    local.mpCapacity = (wchar_t*)gEmptyString16 + 1;

    bool found = false;
    if (FUN_009322b0(str->mpBegin)) {
        found = true;
    } else {
        for (;;) {
            const wchar_t* first = DAT_01409f64;
            const wchar_t* last = first;
            while (*last != 0) ++last;
            local.insert(local.mpBegin, first, last);

            if (!FUN_009322b0(local.mpBegin)) break;

            first = DAT_01409f64;
            last = first;
            while (*last != 0) ++last;
            str->insert(str->mpBegin, first, last);

            if (FUN_009322b0(str->mpBegin)) { found = true; break; }
        }
    }
    (void)found;

    if ((local.mpCapacity - local.mpBegin) > 1 && local.mpBegin != 0)
        EASTL_dealloc(local.mpBegin);
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
