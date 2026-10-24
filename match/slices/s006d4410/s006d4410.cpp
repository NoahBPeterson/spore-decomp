// Slice s006d4410: bake evaluators (dot tail).
#include "../s006ccf50/s006ccf50.h"
#include <xmmintrin.h>

// ----------------------------------------------------------------------------------------------
// Local copy of the shared DEFINE_BAKE body (see ../s006ccf50/s006ccf50.h), keeping the retail
// channel handling of these instantiations:
//   * UVN == 2 reads only the two 16-bit uv components and passes the remaining two channels as
//     zero (the original never touches uv[2]/uv[3] for the 2-channel records), and
//   * COLMODE == 2 reads only colour[0..1] and zeroes colour[2..3] (the original leaves the
//     tail channels at 0.0f instead of loading the third float of the record).
// It also tests the count unsigned like the original (count <= 0 skips the loop).
// ----------------------------------------------------------------------------------------------
#define DEFINE_BAKE_DOT(NAME, COREID, UVN, UVT, COLMODE, TAIL)                                        \
bool NAME(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,               \
          float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)                  \
{                                                                                                     \
    Elem32* base = table->mBegin;                                                                     \
    Handle hA = base[index].handle;                                                                   \
    Handle hB;                                                                                        \
    if (handleIndex >= 0)                                                                             \
        hB.Assign(&base[handleIndex].handle);                                                         \
    if (count > 0)                                                                                    \
    {                                                                                                 \
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };                                                      \
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };                                                 \
        float* o = out;                                                                               \
        BakeEntry* e = entries;                                                                       \
        int n = count;                                                                                \
        do                                                                                            \
        {                                                                                             \
            uint32_t u[4];                                                                            \
            if (UVN == 2) {                                                                           \
                u[2] = 0; u[3] = 0;                                                                   \
                if (UVT == 0) { uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);                         \
                    u[0] = s[0] / 3; u[1] = s[1] / 3; }                                               \
                else { uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);                                \
                    u[0] = s[0] / 3; u[1] = s[1] / 3; } }                                             \
            else if (UVT == 0) { uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);                        \
                u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3; }                 \
            else { uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);                                    \
                u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3; }                 \
            float color[4];                                                                           \
            if (COLMODE == 0) { uint8_t* c = (uint8_t*)(hB.b + hB.d * e->f8);                         \
                color[0] = (float)c[0] * (1.0f / 255.0f); color[1] = (float)c[1] * (1.0f / 255.0f);   \
                color[2] = (float)c[2] * (1.0f / 255.0f); color[3] = (float)c[3] * (1.0f / 255.0f); } \
            else if (COLMODE == 1) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3]; }                 \
            else if (COLMODE == 2) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = 0.0f; }                 \
            else if (COLMODE == 4) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = 0.0f; color[3] = 0.0f; }                 \
            else { color[0] = white[0]; color[1] = white[1]; color[2] = white[2]; color[3] = white[3]; }\
            float* ps = (float*)(pos->base + pos->stride * e->f0);                                    \
            float p3[3];                                                                              \
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];                                              \
            float res[3];                                                                             \
            float scratch[3];                                                                         \
            void* uvp = (UVN == 2) ? (void*)&u[0] : (void*)u;                                         \
            if (COREID == 0) FUN_006c4200(res, scratch, p3, axisDir, color, uvp, param10);            \
            else if (COREID == 1) FUN_006c3b90(res, scratch, p3, axisDir, color, uvp, param10);       \
            else if (COREID == 2) FUN_006c3550(res, scratch, p3, axisDir, color, uvp, param10);       \
            else FUN_006c3780(res, scratch, p3, axisDir, color, uvp, param10);                        \
            float scale = scaleInfo->scale;                                                           \
            if (TAIL == 1)                                                                            \
            {                                                                                         \
                /* retail consumes the 2nd and 3rd component of the core result (res[0] unused) */    \
                __m128 v0 = _mm_mul_ss(_mm_set_ss(res[1]), _mm_set_ss(axis[0]));                       \
                v0 = _mm_add_ss(v0, _mm_set_ss(axis[2]));                                              \
                __m128 v1 = _mm_mul_ss(_mm_set_ss(res[2]), _mm_set_ss(axis[1]));                       \
                v1 = _mm_add_ss(v1, _mm_set_ss(axis[3]));                                              \
                v1 = _mm_sub_ss(_mm_set_ss(1.0f), v1);                                                 \
                __m128 sc = _mm_set_ss(scale);                                                         \
                o[0] = _mm_cvtss_f32(_mm_mul_ss(v0, sc));                                              \
                o[1] = _mm_cvtss_f32(_mm_mul_ss(v1, sc));                                              \
            }                                                                                         \
            else                                                                                      \
            {                                                                                         \
                float dx = res[0] - axis[2];                                                          \
                float dy = res[1] - axis[3];                                                          \
                float len = (float)sqrt(dx * dx + dy * dy);                                           \
                float angle = (float)acos(dx / len);                                                  \
                float weight = (TAIL == 0) ? axis[1] * res[2] : axis[1] * len;                        \
                o[0] = ((axis[0] * angle) * 1.2732406f) * scale;                                      \
                o[1] = (1.0f - weight) * scale;                                                       \
            }                                                                                         \
            o += 2;                                                                                   \
            e += 1;                                                                                   \
        } while (--n);                                                                                \
    }                                                                                                 \
    return true;                                                                                      \
}

DEFINE_BAKE_DOT(Bake_6d4410, 3, 2, 1, 4, 1)   // @ 0x006d4410  uv2u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6d46d0, 3, 4, 1, 4, 1)   // @ 0x006d46d0  uv4u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6d49d0, 1, 4, 0, 2, 1)   // @ 0x006d49d0  uv4u8  / colour2f / dot
DEFINE_BAKE_DOT(Bake_6d4cd0, 1, 2, 1, 2, 1)   // @ 0x006d4cd0  uv2u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6d4fa0, 1, 4, 1, 2, 1)   // @ 0x006d4fa0  uv4u16 / colour2f / dot
