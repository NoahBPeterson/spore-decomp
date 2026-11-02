// src/game/mix/smixhip.cpp.cpp -- migrated from slice(s) s01156960 by tools/migrate/rewrite.py
// Object file: mix/smixhip.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// ---- items of slice s01156960 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef unsigned int   u32;
struct System {
    void* Alloc(int size, const char* name, int align, int flags);  // 0x112c820
    void  Free(void* p, int flags);                                 // 0x112c850
};
void  FUN_01168580(void* p);                                    // 0x1168580
void  FUN_011685b0(void* p, void* params);                      // 0x11685b0
void  FUN_011596d0(void* dst, void* src);                       // 0x11596d0
void  FUN_01159710(void* dst, void* src);                       // 0x1159710
// ---- items of slice s01156960 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" System* g_system;      // 0x016e61a8
extern "C" char g_mixvoices;      // 0x016e8174
extern "C" char g_strHighpass[];  // 0x014ce814

// @ 0x01156a60
namespace  {
void MIX_sethighpass(int voice, int cutoff)
{
    char* v = (char*)&g_mixvoices + voice * 0x5c;
    if (cutoff > 0) {
        if (*(void**)(v + 0x58) == 0) {
            char* st = (char*)g_system->Alloc(0x58, g_strHighpass, 0x10, 0);
            *(void**)(v + 0x58) = st;
            *(u32*)(st + 4) = 0;
            *(u16*)(st + 0x18) = 0x50;
            st[0x1a] = 0;
            FUN_01168580(st);
            FUN_011596d0(v + 0x40, *(void**)(v + 0x58));
        }
        int params[2];
        params[0] = cutoff << 8;
        params[1] = (int)(*(float*)((char*)g_system + 0xc0)) << 8;
        FUN_011685b0(*(void**)(v + 0x58), params);
        return;
    }
    if (*(void**)(v + 0x58) != 0) {
        FUN_01159710(v + 0x40, *(void**)(v + 0x58));
        g_system->Free(*(void**)(v + 0x58), 0);
        *(void**)(v + 0x58) = 0;
    }
}
}  // namespace 
