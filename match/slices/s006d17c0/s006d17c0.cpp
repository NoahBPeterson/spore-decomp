// Slice s006d17c0: bake evaluators (dot tail).
#include "../s006ccf50/s006ccf50.h"

// Local copy of the shared bake body.  The five functions in this slice read the
// core's result as res[0] (out[0]) and res[2] (out[1]); the sibling templates in
// s006ccf50.h keep evolving for other instantiations, so pin the dot tail here.
#define DEFINE_BAKE_DOT(NAME, COREID, UVN, UVT, COLMODE)                                              \
bool NAME(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,               \
          float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)                  \
{                                                                                                     \
    Elem32* base = table->mBegin;                                                                     \
    Handle hA = base[index].handle;                                                                   \
    Handle hB;                                                                                        \
    if (handleIndex >= 0)                                                                             \
        hB.Assign(&base[handleIndex].handle);                                                         \
    if (count != 0)                                                                                   \
    {                                                                                                 \
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };                                                      \
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };                                                 \
        float* o = out;                                                                               \
        BakeEntry* e = entries;                                                                       \
        int n = count;                                                                                \
        do                                                                                            \
        {                                                                                             \
            uint32_t u[4];                                                                            \
            if (UVT == 0) { uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);                             \
                u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = 0; u[3] = 0;                                 \
                if (UVN == 4) { u[2] = s[2] / 3; u[3] = s[3] / 3; } }                                 \
            else { uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);                                    \
                u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = 0; u[3] = 0;                                 \
                if (UVN == 4) { u[2] = s[2] / 3; u[3] = s[3] / 3; } }                                 \
            float color[4];                                                                           \
            if (COLMODE == 0) { uint8_t* c = (uint8_t*)(hB.b + hB.d * e->f8);                         \
                color[0] = (float)c[0] * (1.0f / 255.0f); color[1] = (float)c[1] * (1.0f / 255.0f);   \
                color[2] = (float)c[2] * (1.0f / 255.0f); color[3] = (float)c[3] * (1.0f / 255.0f); } \
            else if (COLMODE == 1) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3]; }                 \
            else if (COLMODE == 2) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = 0.0f; color[3] = 0.0f; }                 \
            else if (COLMODE == 3) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = 0.0f; }                 \
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
            o[0] = (axis[0] * res[0] + axis[2]) * scale;                                              \
            o[1] = (1.0f - (res[2] * axis[1] + axis[3])) * scale;                                     \
            o += 2;                                                                                   \
            e += 1;                                                                                   \
        } while (--n);                                                                                \
    }                                                                                                 \
    return true;                                                                                      \
}

// @ 0x006d17c0 Bake_6d17c0  uv2u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6d17c0, 3, 2, 1, 2)
// @ 0x006d1a80 Bake_6d1a80  uv4u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6d1a80, 3, 4, 1, 2)
// @ 0x006d1d80 Bake_6d1d80  uv4u8  / colour3f / dot
DEFINE_BAKE_DOT(Bake_6d1d80, 1, 4, 0, 3)
// @ 0x006d2080 Bake_6d2080  uv2u16 / colour3f / dot
DEFINE_BAKE_DOT(Bake_6d2080, 1, 2, 1, 3)
// @ 0x006d2350 Bake_6d2350  uv4u16 / colour3f / dot
DEFINE_BAKE_DOT(Bake_6d2350, 1, 4, 1, 3)
