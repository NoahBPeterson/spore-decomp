// src/game/SPGonzago/SPTribeMissionManager.cpp -- migrated from slice(s) s0135d100 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeMissionManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00cd36c0();
extern "C" void fn_00bca960();
extern "C" void fn_00b6f550();
extern "C" void fn_00cd37b0();
extern "C" void fn_00b6fc90();
extern "C" void fn_00cd36f0();
extern "C" void fn_00cd3920();

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_0157ee90, g_0157eecc;
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00cd36c0();
extern "C" void fn_00bca960();
extern "C" void fn_00b6f550();
extern "C" void fn_00cd37b0();
extern "C" void fn_00b6fc90();
extern "C" void fn_00cd36f0();
extern "C" void fn_00cd3920();
// ---- items of slice s0135d100 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern T g_0157ee90, g_0157eecc;

// @ 0x0135d720
void FUN_0135d720()
{
    g_0157ee90 = T("mpTribeToTribeMission", 0xb43c938eu, 0x74, fn_00692ca0, fn_00cd36c0, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157eecc = T("mTribeToTribeMissionMap", 0x743c9504u, 0x78, fn_00692ca0, fn_00cd37b0, fn_00b6fc90, fn_00c2e4e0, fn_00692fb0, fn_00cd36f0, fn_00cd3920);
}
