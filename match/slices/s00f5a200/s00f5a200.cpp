// Draw/effect parameter builder  @ 0x00f5a200  (6560 bytes, /O2, SSE).
//
// Reconstructed from the Ghidra decompile.  Fills a parameter record (position frame,
// tint and tile metrics) from an effect object, choosing the frame according to the
// object's mode byte (+0x12c).  Behaviorally-equivalent; NOT byte-exact (the original
// /O2 body inlines ~1460 SSE instructions; see nonmatching.txt).

#include "../../include/types.h"
#include <math.h>

// ---------------------------------------------------------------- helpers
static float g_a0;   // DAT_016c94a0
static float g_a4;   // DAT_016c94a4
static float g_a8;   // DAT_016c94a8
static float g_ac;   // DAT_016c94ac
static float g_b0;   // DAT_016c94b0
static float g_b4;   // DAT_016c94b4
static float g_b8;   // DAT_016c94b8
static float g_bc;   // DAT_016c94bc
static float g_c0;   // DAT_016c94c0

// Output record (sizes/offsets taken from the original's float indexing).
struct DrawParams {
    float v0, v1, v2;         // +0x00  origin
    float v3, v4, v5;         // +0x0c  second frame vector
    float colorR, colorG, colorB, colorA; // +0x18
    uint8_t flag28;           // +0x28
    uint8_t pad29[3];
    float invW, invH;         // +0x2c
    int   wMinus1, hMinus1;   // +0x34
    int   log2W;              // +0x3c
    uint8_t alpha40;          // +0x40
};

// Effect object subset used by this function.
struct EffectObject {
    char pad0[0x28];
    float x0, y0, z0;         // +0x28
    float x1, y1, z1;         // +0x34
    char pad40[0x12c - 0x40];
    uint8_t mode;             // +0x12c
};

// Orientation/mirror transform at param_1+0xd0 and param_1+0x108.
struct VecXform {
    void Apply(float* v);     // 0x00a7d6b0
};

// @ 0x00f5a200
extern "C" void BuildDrawParams(int param_1, EffectObject* p, DrawParams* out) {
    char* c = (char*)p;
    float* o = (float*)out;

    switch (p->mode) {
    case 1:
    case 5: {
        float c[3];
        c[0] = (p->x1 + p->x0) * 0.5f;
        c[1] = (p->y1 + p->y0) * 0.5f;
        c[2] = (p->z1 + p->z0) * 0.5f;
        if (p->mode == 1) {
            ((VecXform*)((char*)param_1 + 0xd0))->Apply(c);
            ((VecXform*)((char*)param_1 + 0x108))->Apply(c);
        }
        float d = c[1] * g_a8 - c[2] * g_a4;
        float e = c[2] * g_a0 - c[0] * g_a8;
        float f = c[0] * g_a4 - c[1] * g_a0;
        float len = (float)sqrt((double)(f * f + e * e + d * d));
        if (len <= 0.0001f) {
            out->v0 = g_ac; out->v1 = g_b0; out->v2 = g_b4;
            out->v3 = g_b8; out->v4 = g_bc;
            len = g_c0;
        } else {
            float inv = 1.0f / len;
            float nx = inv * d;
            float ny = e * inv;
            o[0] = nx;
            float nz = f * inv;
            o[1] = ny;
            o[2] = nz;
            float bx = o[2] * g_a4 - o[1] * g_a8;
            float by = o[0] * g_a8 - o[2] * g_a0;
            float bz = o[1] * g_a0 - o[0] * g_a4;
            o[3] = bx;
            o[4] = by;
            len = bz;
        }
        o[5] = len;
        if (p->mode == 5) {
            ((VecXform*)((char*)param_1 + 0xd0))->Apply(o);
            ((VecXform*)((char*)param_1 + 0xd0))->Apply(o + 3);
            ((VecXform*)((char*)param_1 + 0x108))->Apply(o);
            ((VecXform*)((char*)param_1 + 0x108))->Apply(o + 3);
        }
        break;
    }
    case 6: {
        float* b = o + 3;
        b[0] = g_a0; b[1] = g_a4; b[2] = g_a8;
        ((VecXform*)((char*)param_1 + 0xd0))->Apply(b);
        ((VecXform*)((char*)param_1 + 0x108))->Apply(b);
        float* pa = *(float**)((char*)param_1 + 0x34);
        o[0] = pa[0x68 / 4]; o[1] = pa[0x6c / 4]; o[2] = pa[0x70 / 4];
        float fy = o[1], fx = o[0];
        o[0] = o[5] * fy - o[4] * o[2];
        o[1] = b[0] * o[2] - o[5] * fx;
        o[2] = o[4] * fx - b[0] * fy;
        float inv = 1.0f / ((float)sqrt((double)(o[0] * o[0] + o[1] * o[1] + o[2] * o[2])) + 0.1f);
        o[0] *= inv; o[1] *= inv; o[2] *= inv;
        break;
    }
    case 7: {
        float* pd = *(float**)((char*)param_1 + 0x34);
        o[3] = pd[0xf4 / 4]; o[4] = pd[0xf8 / 4]; o[5] = pd[0xfc / 4];
        float* pa = *(float**)((char*)param_1 + 0x34);
        o[0] = pa[0x68 / 4]; o[1] = pa[0x6c / 4]; o[2] = pa[0x70 / 4];
        float fy = o[1], fx = o[0];
        o[0] = o[5] * fy - o[4] * o[2];
        o[1] = o[3] * o[2] - o[5] * fx;
        o[2] = o[4] * fx - o[3] * fy;
        float inv = 1.0f / ((float)sqrt((double)(o[0] * o[0] + o[1] * o[1] + o[2] * o[2])) + 0.1f);
        o[0] *= inv; o[1] *= inv; o[2] *= inv;
        break;
    }
    default: {
        float* pf = *(float**)((char*)param_1 + 0x34);
        o[0] = pf[0x5c / 4]; o[1] = pf[0x60 / 4]; o[2] = pf[100 / 4];
        pf = *(float**)((char*)param_1 + 0x34);
        o[3] = pf[0x74 / 4]; o[4] = pf[0x78 / 4]; o[5] = pf[0x7c / 4];
        break;
    }
    }

    if (c[0x178] != 0 || c[0x17a] != 0) {
        o[6] = (float)(uint8_t)c[0x179] * 0.003921569f;
        o[7] = (float)(uint8_t)c[0x178] * 0.0627451f;
        o[8] = (float)(uint8_t)c[0x17b] * 0.003921569f;
        o[9] = (float)(uint8_t)c[0x17a] * 0.0627451f;
        ((uint8_t*)o)[0x40] = (uint8_t)c[0x17c];
    }

    uint8_t flag = ((uint8_t)c[0x12a] < 2 && (uint8_t)c[0x12b] < 2) ? 0 : 1;
    ((uint8_t*)o)[0x28] = flag;
    o[0x0b] = 1.0f / (float)(uint8_t)c[0x12a];
    o[0x0c] = 1.0f / (float)(uint8_t)c[0x12b];
    out->wMinus1 = (int)(uint8_t)c[0x12a] - 1;
    out->hMinus1 = (int)(uint8_t)c[0x12b] - 1;
    out->log2W = 0;

    uint32_t n = (uint8_t)c[0x12a];
    if (n > 1) {
        int log2 = 0;
        do {
            n >>= 1;
            ++log2;
        } while (n > 1);
        out->log2W = log2;
    }
}
