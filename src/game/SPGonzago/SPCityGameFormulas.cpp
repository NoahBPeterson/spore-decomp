// src/game/SPGonzago/SPCityGameFormulas.cpp -- migrated from slice(s) s00cedff0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityGameFormulas.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00cedff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
// ---- items of slice s00cedff0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" char  FUN_007f2240();  // 0x007f2240  LoadArithmeticaFile(hash,0,dst)
extern "C" char  g_169c340;  // 0x0169c340  tribe chance to recruit formula
extern "C" char  g_169c3d8;  // 0x0169c3d8  player recruit success formula
extern "C" char  g_169c470;  // 0x0169c470  tribe chance to raid formula
extern "C" char  g_169c508;  // 0x0169c508  player raid success formula
extern "C" char  g_169c5a0;  // 0x0169c5a0  tribe food formula
extern "C" char  g_169c2a8;  // 0x0169c2a8  recruit from tribe formula
extern "C" char  g_169c638;  // 0x0169c638  attack chance to die formula
extern "C" char  g_169c6d0;  // 0x0169c6d0  tribe attack when approached
extern "C" char  g_169c768;  // 0x0169c768  lurk formula
extern "C" char  g_169c800;  // 0x0169c800  raid farm formula
extern "C" char  g_169c930;  // 0x0169c930  vehicle stats formula
extern "C" char  g_169c898;  // 0x0169c898  wander formula
extern "C" char  g_169c9c8;  // 0x0169c9c8  (anonymous formula)

// @ 0x00ceec60
namespace SP {
namespace nCityGameFormulas {
void LoadFormulas()
{
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x76a22983, 0, &g_169c340);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xacb97b49, 0, &g_169c3d8);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x58eee579, 0, &g_169c470);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xe0fc6df9, 0, &g_169c508);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x12a50d5f, 0, &g_169c5a0);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x3d7b29fa, 0, &g_169c2a8);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xdbe48be7, 0, &g_169c638);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x027b0c3c, 0, &g_169c6d0);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xdb334a60, 0, &g_169c768);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0x2278cc41, 0, &g_169c800);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xe86722a6, 0, &g_169c930);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xfe791351, 0, &g_169c898);
    ((char(__cdecl *)(u32, u32, void *))FUN_007f2240)(0xb3a05c62, 0, &g_169c9c8);
}
}
}  // namespace SP::nCityGameFormulas
