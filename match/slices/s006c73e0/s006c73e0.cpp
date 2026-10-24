// Slice s006c73e0: per-vertex bake helpers (cBakedArenaResource).
// The original is /arch:SSE scalar codegen: float add/sub/mul/div use SSE1,
// square root falls back to x87 (fsqrt) because SSE1 has no scalar sqrt.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"
#include <math.h>
#include <xmmintrin.h>

struct RefObject {
    virtual void AddRef();       // vtable slot 0
    virtual void Release();      // vtable slot 1
};

// 0x10-byte block descriptor: base/stride pair plus an intrusive reference.
struct Handle {
    uint32_t a;                  // +0x00
    uint32_t b;                  // +0x04  base of the per-vertex array
    uint16_t c;                  // +0x08
    uint16_t d;                  // +0x0a  element stride
    RefObject* mpRef;            // +0x0c
    Handle* Assign(const Handle* src);   // 0x00424f70
};

// Vertex-source descriptor (5th argument).
struct VertexStream {
    uint32_t w0;                 // +0x00
    int base;                    // +0x04
    uint16_t w1;                 // +0x08
    uint16_t stride;             // +0x0a
};

// Block transforms (slices s006c2cd0 .. s006c3b90).
void FUN_006c4200(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout);
void FUN_006c3550(float* outA, float* outB, const float* base, const float* dir,
                  const float* s, const int* idx, int layout);

enum ColorFormat {
    COL_BYTE4,                   // four packed bytes, each divided by 3
    COL_USHORT2,                 // two 16-bit channels, upper two are zero
    COL_USHORT4                  // four 16-bit channels
};

// Single-precision SSE1 helpers: the original never lets an x87 temporary
// carry excess precision through the per-vertex math.
static inline float SseAdd(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static inline float SseSub(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static inline float SseMul(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static inline float SseDiv(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

// POINT variants use the point transform (0x006c3550), feed a fixed {1,0,0,0}
// row instead of the float4 behind the assigned block's base pointer, and read
// the transform's axis triple in the rotated order it writes it.
template <int COLFMT, bool POINT>
static void BakeCore(float* out, int count, int res, const int* data, const VertexStream* vtx,
                     const float* scalePair, const float* params, int blockIdx, int assignIdx,
                     int layout)
{
    const char* table = (const char*)*(int*)(res + 8);
    const Handle* blk = (const Handle*)(table + blockIdx * 0x20 + 0x10);
    Handle copy = *blk;
    if (copy.mpRef)
        copy.mpRef->AddRef();

    // The assigned block is copied into a zeroed temporary; when assignIdx is
    // negative the temporary keeps its zero fields.
    Handle tmp = { 0, 0, 0, 0, 0 };
    if (assignIdx >= 0)
        tmp.Assign((const Handle*)(table + assignIdx * 0x20 + 0x10));

    float dir[3] = { 1.0f, 0.0f, 0.0f };
    float s[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    for (unsigned n = (unsigned)count; n != 0; --n) {
        const unsigned char* cb = (const unsigned char*)(copy.b + copy.d * data[3]);
        int col[4];
        if (COLFMT == COL_BYTE4) {
            col[3] = cb[3] / 3;
            col[2] = cb[2] / 3;
            col[1] = cb[1] / 3;
            col[0] = cb[0] / 3;
        } else if (COLFMT == COL_USHORT2) {
            const unsigned short* cu = (const unsigned short*)cb;
            col[1] = cu[1] / 3;
            col[0] = cu[0] / 3;
            col[2] = 0;
            col[3] = 0;
        } else {
            const unsigned short* cu = (const unsigned short*)cb;
            col[3] = cu[3] / 3;
            col[2] = cu[2] / 3;
            col[1] = cu[1] / 3;
            col[0] = cu[0] / 3;
        }

        if (!POINT) {
            const float* src = (const float*)(tmp.b + tmp.d * data[2]);
            s[0] = src[0];
            s[1] = src[1];
            s[2] = src[2];
            s[3] = src[3];
        }

        const float* p = (const float*)(vtx->base + vtx->stride * data[0]);
        float base[3];
        base[0] = p[0];
        base[1] = p[1];
        base[2] = p[2];

        float outA[3], outB[3];
        if (POINT)
            FUN_006c3550(outA, outB, base, dir, s, col, layout);
        else
            FUN_006c4200(outA, outB, base, dir, s, col, layout);

        // Keep the scalar chain in single precision (SSE1), like the original:
        // an x87 chain would round differently in the last bit.
        float a0 = POINT ? outA[2] : outA[1];
        float a1 = POINT ? outA[0] : outA[2];
        float a2 = POINT ? outA[1] : outA[0];
        float dy = SseSub(a0, scalePair[2]);
        float dz = SseSub(a1, scalePair[3]);
        float sq = SseAdd(SseMul(dy, dy), SseMul(dz, dz));
        float len = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(sq)));
        float ang = acosf(SseDiv(dy, len));
        float k = params[4];
        out[0] = SseMul(SseMul(SseMul(scalePair[0], ang), 1.2732406f), k);
        out[1] = SseMul(SseSub(1.0f, SseMul(scalePair[1], a2)), k);

        data += 6;
        out += 2;
    }

    if (tmp.mpRef)
        tmp.mpRef->Release();
    if (copy.mpRef)
        copy.mpRef->Release();
}

// @ 0x006c73e0
bool FUN_006c73e0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore<COL_BYTE4, false>(out, count, res, data, (const VertexStream*)vtx, scalePair,
                             (const float*)params, blockIdx, assignIdx, layout);
  return true;
}

// @ 0x006c7740
bool FUN_006c7740(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore<COL_USHORT2, false>(out, count, res, data, (const VertexStream*)vtx, scalePair,
                               (const float*)params, blockIdx, assignIdx, layout);
  return true;
}

// @ 0x006c7a60
bool FUN_006c7a60(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore<COL_USHORT4, false>(out, count, res, data, (const VertexStream*)vtx, scalePair,
                               (const float*)params, blockIdx, assignIdx, layout);
  return true;
}

// @ 0x006c7dc0
bool FUN_006c7dc0(float* out, int count, int res, int* data, int vtx, const float* scalePair,
                  const char* params, int blockIdx, int assignIdx, int layout) {
  BakeCore<COL_BYTE4, true>(out, count, res, data, (const VertexStream*)vtx, scalePair,
                           (const float*)params, blockIdx, assignIdx, layout);
  return true;
}
