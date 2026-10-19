// src/game/SPEngine/SPGraphicsFrustumCull.cpp -- migrated from slice(s) s006ffe00, s006ff170 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFrustumCull.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned char g_1628c38;    // 0x1628c38 clip-disable flag
extern int  g_planeIndices[6];     // 0x1534e4c

// ---- items of slice s006ff170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_1628c38;    // 0x1628c38 clip-disable flag
extern int  g_planeIndices[6];     // 0x1534e4c
struct VertexCtx {
    void SubClip(float d);
    int  TestClip1(const float* a, const float* b);
    int  TestClip2(const float* p, float t);
};
// ---- items of slice s006ff170 end

// @ 0x006ffaf0
int VertexCtx::TestClip1(const float* a, const float* b)
{
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float local[6];
    local[0] = a[0];
    local[1] = a[1];
    local[2] = a[2];
    local[3] = b[0];
    local[4] = b[1];
    local[5] = b[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        int i0 = *(int*)((char*)pf + 0x10);
        int i1 = *(int*)((char*)pf + 0x18);
        int i2 = *(int*)((char*)pf + 0x20);
        float dot = ((pf[2] * local[i2] + pf[1] * local[i1]) + pf[0] * local[i0]) + pf[3];
        if ((*(unsigned int*)&dot & 0x80000000) == 0) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x00700120
int __cdecl FUN_00700120(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; return 0; }
