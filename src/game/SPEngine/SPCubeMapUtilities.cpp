// src/game/SPEngine/SPCubeMapUtilities.cpp -- migrated from slice(s) s00683f80 by tools/migrate/rewrite.py
// Object file: SPEngine/SPCubeMapUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char g_1402d55[];

// ---- items of slice s00683f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_1402d55[];
// ---- items of slice s00683f80 end

// @ 0x00684bf0
int* __cdecl SP_CoordToIndex(int* out, int n, float* c)
{
    out[2] = ((int*)c)[2];
    int x = (int)((float)n * c[0]);
    out[0] = x;
    int y = (int)(c[1] * (float)n);
    out[1] = y;
    if (x == n)
        out[0] = x - 1;
    if (y == n)
        out[1] = y - 1;
    return out;
}

// @ 0x00684ca0
int __cdecl SP_WrapCubeFace(int n, uint32_t* face, uint32_t* x, int* y, int* u, int* v)
{
    uint32_t p = *face & 1;
    uint32_t q = p ^ 1;
    int s = p * -2 + 1;
    uint32_t xv = *x;
    int ns = -s;
    if ((int)xv < 0) {
        *x = xv + n;
        uint32_t nm1 = n - 1;
        *x = *y * ns + nm1 * q;
        *y = nm1 * p + (xv + n) * s;
        *face = q + (uint32_t)(uint8_t)g_1402d55[((int)*face >> 1) * 4] * 2;
        if (u) {
            int t = *u;
            *u = *v * ns;
            *v = t * s;
        }
        if ((*x & ~nm1) == 0)
            return 1;
    } else if ((int)xv < n) {
        int yv = *y;
        if (yv < 0) {
            *y = yv + n;
            uint32_t xc = *x;
            *x = (yv + n) * ns + (n - 1) * q;
            *y = (n - 1) * p + xc * s;
            *face = (uint32_t)(uint8_t)g_1402d55[1 + ((int)*face >> 1) * 4] * 2 + 1;
        } else if (yv < n) {
            return 0;
        } else {
            *y = yv - n;
            uint32_t xc = *x;
            *x = (yv - n) * ns + (n - 1) * q;
            *y = (n - 1) * p + xc * s;
            *face = (uint32_t)(uint8_t)g_1402d55[1 + ((int)*face >> 1) * 4] * 2;
        }
        if (!u)
            return 1;
        int t = *u;
        *u = *v * ns;
        *v = t * s;
        return 1;
    } else {
        *x = xv - n;
        uint32_t nm1 = n - 1;
        *x = *y * s + nm1 * p;
        *y = nm1 * q + (xv - n) * ns;
        *face = p + (uint32_t)(uint8_t)g_1402d55[((int)*face >> 1) * 4] * 2;
        if (u) {
            int t = *u;
            *u = *v * s;
            *v = t * ns;
        }
        if ((*x & ~nm1) == 0)
            return 1;
    }
    return SP_WrapCubeFace(n, face, x, y, u, v) + 1;
}
