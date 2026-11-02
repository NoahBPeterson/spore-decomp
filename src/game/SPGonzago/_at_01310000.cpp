// src/game/SPGonzago/_at_01310000.cpp -- migrated from slice(s) s01318c70 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01310000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t    g_167dae0;   // 0x0167dae0
extern void*       g_vtable_145e9a8;  // 0x0145e9a8
extern "C" int atexit(void (*pfn)(void));   // 0x011e07ef

// ---- items of slice s01318c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Obj_167c988
{
    void* vptr;                 // 0x00
    void Ctor();                // 0x00b63bd0
};
extern Obj_167c988 g_167c988;   // 0x0167c988
extern uint32_t    g_167dae0;   // 0x0167dae0
extern void*       g_vtable_145e9a8;  // 0x0145e9a8
void FUN_013c1ff0();            // 0x013c1ff0
extern "C" int atexit(void (*pfn)(void));   // 0x011e07ef
// ---- items of slice s01318c70 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Obj_167c988 g_167c988;   // 0x0167c988

// @ 0x0131aa90
void InitGlobal_167c988()
{
    g_167c988.Ctor();
    g_167c988.vptr = &g_vtable_145e9a8;
    g_167dae0 = 0;
    atexit(FUN_013c1ff0);
}
