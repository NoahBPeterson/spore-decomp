// src/game/SPEngine/SPGraphicsShader.cpp -- migrated from slice(s) s007776f0, s00776730 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsShader.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/ActiveState.h"
#include "rw/graphics/CompiledState.h"
#include "SP/cShaderBase.h"
#include "SP/cTextureInstance.h"
#include "SP/cViewer.h"
#include <xmmintrin.h>

// unnamed retail callees and globals that name local stubs (address in the comment)
extern char g_vsProfile[];   // 0x01539eb8 ("vs_x_x")

// ---- items of slice s007776f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_psProfile[];   // 0x01539ec0 ("ps_x_x")
// ---- items of slice s007776f0 end

// @ 0x007776c0
namespace SP {
char * VSProfileFromVersion(unsigned int version)
{
    int lo = (int)(version & 0xff);
    g_vsProfile[3] = (char)(version >> 8) + '0';
    char c = (char)lo;
    if (lo < 10)
        c = c + '0';
    g_vsProfile[5] = c;
    return g_vsProfile;
}
}  // namespace SP

// @ 0x007776f0
namespace SP {
char * PSProfileFromVersion(unsigned int version)
{
    int lo = (int)(version & 0xff);
    g_psProfile[3] = (char)(version >> 8) + '0';
    char c = (char)lo;
    if (lo < 10)
        c = c + '0';
    g_psProfile[5] = c;
    return g_psProfile;
}
}  // namespace SP

// @ 0x00777720
void FUN_00777720(int* a, int b, int c)
{ (void)a; (void)b; (void)c; }

// @ 0x00777740
int FUN_00777740(int* a)
{ (void)a; return 0; }

// @ 0x00777760
int FUN_00777760(int a, int b)
{ (void)a; (void)b; return 1; }
