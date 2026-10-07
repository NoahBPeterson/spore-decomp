// Slice s00ab7720 -- 0x00ab7720: ribbon/trail geometry builder (~3.9 KB, /O2 /arch:SSE, cdecl).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast  (inline fsqrt and x87 math kept in registers, as in the original)
// Unnamed in the PDB. Locks a vertex sink (param_2) for N quads of 4 vertices each, then for every
// step along the trail samples alpha/color/width curves (effect data at +0x14), the path
// (self+0x134) and a fade curve (self+0x570), optionally transforms the point (Transform at
// self+0xb4), builds the perpendicular from cross(delta, up) and writes position/uv/color of
// 4 vertices (prevL, prevR, curR, curL) at the sink's stride, then unlocks.
// Stack slot facts (from the asm): vertex cursor and stride are the sink's two out params; the
// vertex field offsets (position, color, uv) are the bytes at self+0x12c, +0x12d, +0x12e.
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

struct Vec3f { float x, y, z; };

// Curve data ("effect") referenced from self+0x14.
struct TrailCurves {
    uint32_t pad0[10];           // 0x00
    float*   widthBeg;           // 0x28 (float curve, element count = (end-beg)/4)
    float*   widthEnd;           // 0x2c
    uint32_t pad1[0x70 / 4 - 0x30 / 4 - 0];
    Vec3f*   colorBeg;           // 0x70 (Vec3f curve)
    Vec3f*   colorEnd;           // 0x74
    uint32_t pad2[(0x84 - 0x78) / 4];
    float*   alphaBeg;           // 0x84 (float curve)
    float*   alphaEnd;           // 0x88
    uint32_t pad3[(0xec - 0x8c) / 4];
    float    lengthScale;        // 0xec
    uint32_t pad4[(0x11c - 0xf0) / 4];
    float    uvLength;           // 0x11c
};

struct TrailEmitter {            // object at self+0x1c; only the "up" vector is used
    uint32_t pad[0x68 / 4];
    Vec3f    up;                 // 0x68
};

struct XformObj {                // self+0xb4
    uint32_t flags;              // 0xb4: bit 1 = has rotation
    Vec3f    offset;             // 0xb8
    float    scale;              // 0xc4
    float    m[3][3];            // 0xc8: column-major rotation (m[col][row])
    void __thiscall TransformPoint(Vec3f* p);   // FUN_007cdee0 (in-place point transform)
};

struct TrailData {
    uint8_t       pad0[0x12];
    uint8_t       fixedUvStep;   // 0x12 (nonzero: use path step for the uv/curve parameter)
    uint8_t       pad1;
    TrailCurves*  curves;        // 0x14
    uint32_t      pad2;
    TrailEmitter* emitter;       // 0x1c
    uint32_t      pad3[(0x38 - 0x20) / 4];
    int           quadCount;     // 0x38
    uint32_t      pad4;
    float         uStart;        // 0x40
    uint32_t      pad5[(0x64 - 0x44) / 4];
    Vec3f         pos;           // 0x64
    uint32_t      pad6[(0xb4 - 0x70) / 4];
    XformObj      xf;            // 0xb4 (size 0x28 -> 0xdc... matrix ends at 0xec)
    uint32_t      pad7[(0xfc - 0xec) / 4];
    float         alphaScale;    // 0xfc
    float         sizeScale;     // 0x100
    uint32_t      pad8[(0x11c - 0x104) / 4];
    Vec3f         tint;          // 0x11c
    uint32_t      pad9[(0x12c - 0x128) / 4];
    uint8_t       posOff;        // 0x12c
    uint8_t       colOff;        // 0x12d
    uint8_t       uvOff;         // 0x12e
    uint8_t       pad10;
    uint32_t      pad11;
    Vec3f*        pathBeg;       // 0x134
    Vec3f*        pathEnd;       // 0x138
    uint32_t      pad12[(0x570 - 0x13c) / 4];
    float*        fade;          // 0x570
};

struct VertexSink {              // vtable slot 0 = Lock, slot 2 = Unlock
    virtual int  __thiscall Lock(unsigned count, char** outCursor, int* outStride) = 0;
    virtual void __thiscall Reserved() = 0;
    virtual void __thiscall Unlock() = 0;
};

namespace {

inline float LerpF(const float* a, unsigned cnt, float t)
{
    if (cnt == 0)
        return a[0];
    float f = (float)cnt * t;
    int i = (int)f;
    float fr = f - (float)i;
    if (fr > 0.0f)
        return (a[i + 1] - a[i]) * fr + a[i];
    return a[i];
}

inline void LerpV(const Vec3f* a, unsigned cnt, float t, Vec3f* out)
{
    if (cnt == 0) {
        *out = a[0];
        return;
    }
    float f = (float)cnt * t;
    int i = (int)f;
    float fr = f - (float)i;
    if (fr > 0.0f) {
        out->x = a[i].x + (a[i + 1].x - a[i].x) * fr;
        out->y = a[i].y + (a[i + 1].y - a[i].y) * fr;
        out->z = a[i].z + (a[i + 1].z - a[i].z) * fr;
    } else {
        *out = a[i];
    }
}

inline float Clamp01(float v)
{
    float r = (0.0f <= v) ? v : 0.0f;
    if (1.0f <= r)
        r = 1.0f;
    return r;
}

inline uint32_t ToByte(float v)
{
    float x = (0.0f <= v) ? v : 0.0f;
    x = x * 255.0f;
    if (255.0f <= x)
        x = 255.0f;
    return (uint32_t)_mm_cvtss_si32(_mm_set_ss(x)) & 0xff;
}

inline uint32_t PackArgb(float a, float r, float g, float b)
{
    return (((ToByte(a) << 8 | ToByte(r)) << 8 | ToByte(g)) << 8) | ToByte(b);
}

}

// @ 0x00ab7720
void Trail_FillVertices(TrailData* self, VertexSink* sink)
{
    if (self->pathBeg == self->pathEnd)
        return;
    if (!(0 < self->quadCount))
        return;

    TrailCurves* cv = self->curves;
    unsigned alphaN = (unsigned)((cv->alphaEnd - cv->alphaBeg) - 1);
    unsigned colorN = (unsigned)((cv->colorEnd - cv->colorBeg) - 1);
    unsigned widthN = (unsigned)((cv->widthEnd - cv->widthBeg) - 1);
    unsigned pathN = (unsigned)((self->pathEnd - self->pathBeg) - 1);
    Vec3f up = self->emitter->up;

    float dx0 = self->pos.x - self->pathBeg[0].x;
    float dy0 = self->pos.y - self->pathBeg[0].y;
    float dz0 = self->pos.z - self->pathBeg[0].z;
    float segLen = (1.0f / cv->lengthScale) * (float)sqrt(dy0 * dy0 + (dz0 * dz0 + dx0 * dx0));

    float stepA = 0.0f;
    float invStepA = 0.0f;
    if (pathN != 0) {
        stepA = segLen / (float)pathN;
        invStepA = 1.0f / stepA;
    }

    Vec3f tint = self->tint;
    float alphaScale = self->alphaScale;
    float duStep = cv->uvLength / (float)self->quadCount;

    int pathCount = (int)((self->pathEnd - self->pathBeg) - 1);
    float invPathSegs = 1.0f / (float)pathCount;

    char* cursor;
    int stride;
    int n = sink->Lock((unsigned)pathCount, &cursor, &stride);

    float invN = invPathSegs;
    if (self->fixedUvStep == 0) {
        if (n < 2)
            invN = 1.0f;
        else
            invN = 1.0f / (((float)n + segLen) - 1.0f);
    }

    float halfW = self->xf.scale * 0.5f;
    float prevAlpha = cv->alphaBeg[0] * alphaScale;
    float prevCol[3];
    prevCol[0] = cv->colorBeg[0].x * tint.x;
    prevCol[1] = cv->colorBeg[0].y * tint.y;
    prevCol[2] = cv->colorBeg[0].z * tint.z;
    float prevSize = cv->widthBeg[0] * self->sizeScale;
    Vec3f prev = self->pos;
    float prevU = self->uStart;
    float prevFade = 1.0f;
    self->xf.TransformPoint(&prev);

    if (0 < n) {
        Vec3f prevL = { 0.0f, 0.0f, 0.0f };
        Vec3f prevR = { 0.0f, 0.0f, 0.0f };
        int i = 0;
        do {
            int j = i + 1;
            float u = (float)j * invPathSegs;
            float t = Clamp01((float)j * invN);

            float alpha = LerpF(cv->alphaBeg, alphaN, t);
            Vec3f col;
            LerpV(cv->colorBeg, colorN, t, &col);
            alpha = alpha * alphaScale;
            col.x = col.x * tint.x;
            col.y = col.y * tint.y;
            col.z = col.z * tint.z;
            float size = self->sizeScale * LerpF(cv->widthBeg, widthN, t);

            Vec3f cur;
            float fade;
            if (stepA <= u) {
                float c = Clamp01(u - stepA);
                LerpV(self->pathBeg, pathN, c, &cur);
                fade = LerpF(self->fade, pathN, c);
            } else {
                float f = t * invStepA;
                cur.x = self->pos.x + (self->pathBeg[0].x - self->pos.x) * f;
                cur.z = self->pos.z + (self->pathBeg[0].z - self->pos.z) * f;
                cur.y = self->pos.y + (self->pathBeg[0].y - self->pos.y) * f;
                fade = (self->fade[0] - 1.0f) * f + 1.0f;
            }

            if (self->xf.flags & 2) {
                float a0 = (self->xf.m[1][0] * cur.y + self->xf.m[2][0] * cur.z) + cur.x * self->xf.m[0][0];
                float a1 = (self->xf.m[1][1] * cur.y + self->xf.m[2][1] * cur.z) + self->xf.m[0][1] * cur.x;
                float a2 = (self->xf.m[1][2] * cur.y + self->xf.m[2][2] * cur.z) + self->xf.m[0][2] * cur.x;
                cur.x = a0;
                cur.y = a1;
                cur.z = a2;
            }
            float s = self->xf.scale;
            cur.z = self->xf.offset.z + s * cur.z;
            cur.x = self->xf.offset.x + s * cur.x;
            cur.y = self->xf.offset.y + s * cur.y;

            float curHalf = size * halfW;
            float prevAlphaF = prevFade * prevAlpha;
            float prevHalf = prevSize * halfW;
            uint32_t colPrev = PackArgb(prevAlphaF, prevCol[0], prevCol[1], prevCol[2]);
            float curAlphaF = fade * alpha;
            uint32_t colCur = PackArgb(curAlphaF, col.x, col.y, col.z);

            float dx = cur.x - prev.x;
            float dy = cur.y - prev.y;
            float dz = cur.z - prev.z;
            float nA = dz * up.y - dy * up.z;
            float nC = dy * up.x - dx * up.y;
            float nB = dx * up.z - dz * up.x;
            float inv = 1.0f / (float)sqrt((nA * nA + (nB * nB + nC * nC)) + 1e-08f);

            if (i == 0) {
                float ox = (inv * nA) * prevHalf;
                float oy = (nB * inv) * prevHalf;
                float oz = (nC * inv) * prevHalf;
                prevL.x = prev.x - ox;
                prevL.y = prev.y - oy;
                prevL.z = prev.z - oz;
                prevR.x = ox + prev.x;
                prevR.y = oy + prev.y;
                prevR.z = oz + prev.z;
            }

            char* p = cursor + self->posOff;
            ((Vec3f*)p)[0] = prevL;
            p += stride;
            *(Vec3f*)p = prevR;
            p += stride;
            float cx = (inv * nA) * curHalf;
            float cy = (nB * inv) * curHalf;
            float cz = (nC * inv) * curHalf;
            Vec3f curL, curR;
            curL.x = cur.x - cx;
            curL.y = cur.y - cy;
            curL.z = cur.z - cz;
            curR.x = cx + cur.x;
            curR.y = cy + cur.y;
            curR.z = cz + cur.z;
            *(Vec3f*)p = curR;
            p += stride;
            *(Vec3f*)p = curL;

            float* uv = (float*)(cursor + self->uvOff);
            uv[0] = prevU;
            uv[1] = 0.0f;
            uv = (float*)((char*)uv + stride);
            uv[0] = prevU;
            uv[1] = 1.0f;
            prevU = prevU + duStep;
            uv = (float*)((char*)uv + stride);
            uv[0] = prevU;
            uv[1] = 1.0f;
            uv = (float*)((char*)uv + stride);
            uv[0] = prevU;
            uv[1] = 0.0f;

            uint32_t* cp = (uint32_t*)(cursor + self->colOff);
            *cp = colPrev;
            cp = (uint32_t*)((char*)cp + stride);
            *cp = colPrev;
            cp = (uint32_t*)((char*)cp + stride);
            *cp = colCur;
            cp = (uint32_t*)((char*)cp + stride);
            *cp = colCur;

            cursor += stride * 4;

            prevSize = size;
            prevAlpha = alpha;
            prevFade = fade;
            prevCol[0] = col.x;
            prevCol[1] = col.y;
            prevCol[2] = col.z;
            prev = cur;
            prevL = curL;
            prevR = curR;
            i = j;
        } while (i < n);
    }
    sink->Unlock();
}

// The Ghidra/card "function" at 0x00ab7720 is 6899 bytes because it also covers the second routine
// below (0x00ab86d0): the triangle-strip variant of the same builder. It locks (pathN+1) vertices,
// emits 2 vertices (curR, curL) per step for steps 0..n inclusive with no per-quad previous state,
// and does not call Unlock when the locked count is <= 1.
// @ 0x00ab86d0
void Trail_FillStrip(TrailData* self, VertexSink* sink)
{
    if (self->pathBeg == self->pathEnd)
        return;
    if (!(0 < self->quadCount))
        return;

    TrailCurves* cv = self->curves;
    unsigned colorN = (unsigned)((cv->colorEnd - cv->colorBeg) - 1);
    unsigned widthN = (unsigned)((cv->widthEnd - cv->widthBeg) - 1);
    unsigned pathN = (unsigned)((self->pathEnd - self->pathBeg) - 1);
    unsigned alphaN = (unsigned)((cv->alphaEnd - cv->alphaBeg) - 1);
    Vec3f up = self->emitter->up;

    float dx0 = self->pos.x - self->pathBeg[0].x;
    float dy0 = self->pos.y - self->pathBeg[0].y;
    float dz0 = self->pos.z - self->pathBeg[0].z;
    float segLen = (1.0f / cv->lengthScale) * (float)sqrt(dy0 * dy0 + (dz0 * dz0 + dx0 * dx0));

    float stepA = 0.0f;
    float invStepA = 0.0f;
    if (pathN != 0) {
        stepA = segLen / (float)pathN;
        invStepA = 1.0f / stepA;
    }

    Vec3f tint = self->tint;
    float alphaScale = self->alphaScale;
    float duStep = cv->uvLength / (float)self->quadCount;
    float invPathSegs = 1.0f / (float)(int)pathN;

    char* cursor;
    int stride;
    int n = sink->Lock(pathN + 1, &cursor, &stride) - 1;
    if (!(0 < n))
        return;

    float invN = invPathSegs;
    if (self->fixedUvStep == 0) {
        if (n < 2)
            invN = 1.0f;
        else
            invN = 1.0f / (((float)n + segLen) - 1.0f);
    }

    float halfW = self->xf.scale * 0.5f;
    Vec3f prev = self->pos;

    int i = 0;
    do {
        float u = (float)i * invPathSegs;
        float t = Clamp01((float)i * invN);

        float alpha = LerpF(cv->alphaBeg, alphaN, t);
        Vec3f col;
        LerpV(cv->colorBeg, colorN, t, &col);
        alpha = alpha * alphaScale;
        col.x = col.x * tint.x;
        col.y = col.y * tint.y;
        col.z = col.z * tint.z;
        float size = self->sizeScale * LerpF(cv->widthBeg, widthN, t);

        Vec3f cur;
        float fade;
        if (stepA <= u) {
            float c = Clamp01(u - stepA);
            LerpV(self->pathBeg, pathN, c, &cur);
            fade = LerpF(self->fade, pathN, c);
        } else {
            float f = t * invStepA;
            cur.x = self->pos.x + (self->pathBeg[0].x - self->pos.x) * f;
            cur.z = self->pos.z + (self->pathBeg[0].z - self->pos.z) * f;
            cur.y = self->pos.y + (self->pathBeg[0].y - self->pos.y) * f;
            fade = (self->fade[0] - 1.0f) * f + 1.0f;
        }

        if (self->xf.flags & 2) {
            float a0 = (self->xf.m[1][0] * cur.y + self->xf.m[2][0] * cur.z) + cur.x * self->xf.m[0][0];
            float a1 = (self->xf.m[1][1] * cur.y + self->xf.m[2][1] * cur.z) + self->xf.m[0][1] * cur.x;
            float a2 = (self->xf.m[1][2] * cur.y + self->xf.m[2][2] * cur.z) + self->xf.m[0][2] * cur.x;
            cur.x = a0;
            cur.y = a1;
            cur.z = a2;
        }
        float s = self->xf.scale;
        cur.z = self->xf.offset.z + s * cur.z;
        cur.x = self->xf.offset.x + s * cur.x;
        cur.y = self->xf.offset.y + s * cur.y;

        float half = size * halfW;
        uint32_t color = PackArgb(fade * alpha, col.x, col.y, col.z);

        float dx = cur.x - prev.x;
        float dy = cur.y - prev.y;
        float dz = cur.z - prev.z;
        float nA = dz * up.y - dy * up.z;
        float nC = dy * up.x - dx * up.y;
        float nB = dx * up.z - dz * up.x;
        float inv = 1.0f / (float)sqrt((nA * nA + (nB * nB + nC * nC)) + 1e-08f);

        float ox = (inv * nA) * half;
        float oy = (nB * inv) * half;
        float oz = (nC * inv) * half;

        char* p = cursor + self->posOff;
        Vec3f* v = (Vec3f*)p;
        v->x = ox + cur.x;
        v->y = oy + cur.y;
        v->z = oz + cur.z;
        v = (Vec3f*)(p + stride);
        v->x = cur.x - ox;
        v->y = cur.y - oy;
        v->z = cur.z - oz;

        float uCur = (float)i * duStep + self->uStart;
        float* uv = (float*)(cursor + self->uvOff);
        uv[0] = uCur;
        uv[1] = 1.0f;
        uv = (float*)((char*)uv + stride);
        uv[0] = uCur;
        uv[1] = 0.0f;

        uint32_t* cp = (uint32_t*)(cursor + self->colOff);
        *cp = color;
        *(uint32_t*)((char*)cp + stride) = color;

        cursor += stride * 2;
        prev = cur;
        ++i;
    } while (i <= n);
    sink->Unlock();
}
