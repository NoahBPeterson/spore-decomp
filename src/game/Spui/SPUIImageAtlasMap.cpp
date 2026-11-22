// src/game/Spui/SPUIImageAtlasMap.cpp -- migrated from slice(s) s0080a700, s00809700 by tools/migrate/rewrite.py
// Object file: Spui/SPUIImageAtlasMap.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIMessageBox.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* dbgnew(unsigned size, const void* data, int a, int b, const char* file, int line); // 0x00f473a0
extern char g_data_13f6b3c;

// ---- items of slice s00809700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* dbgnew(unsigned size, const void* data, int a, int b, const char* file, int line); // 0x00f473a0
extern char g_data_13f6b3c;
struct Blob {
    int i0, i1, i2, i3, i4, i5;
    float f0, f1, f2, f3;
    int i6, i7;
};
// ---- items of slice s00809700 end

// @ 0x0080a470
void __stdcall FUN_0080a470(Blob* src)
{
    Blob* p = (Blob*)dbgnew(0x34, &g_data_13f6b3c, 0, 0,
                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                            0xd1);
    if (p) {
        p->i0 = src->i0; p->i1 = src->i1; p->i2 = src->i2; p->i3 = src->i3;
        p->i4 = src->i4; p->i5 = src->i5;
        p->f0 = src->f0; p->f1 = src->f1; p->f2 = src->f2; p->f3 = src->f3;
        p->i6 = src->i6; p->i7 = src->i7;
    }
    *(int*)((char*)p + 0x30) = 0;
}

// @ 0x0080a700
void cSPUIImageAtlasMap_Init()
{ /* atlas map load; not reconstructed */ }
