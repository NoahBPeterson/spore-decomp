// Slice s006ceb60: bake evaluators (dot tail).
#include "../s006ccf50/s006ccf50.h"

// The shared DEFINE_BAKE dot tail indexes res[1]/res[2], but the retail dot tail
// reads res[0]/res[1] (0x006cf420 / 0x006cf6f0: out0 = axis.x*res.x + axis.z,
// out1 = 1 - (res.y*axis.y + axis.w)).  Apply the corrected tail locally for the
// dot functions fixed in this slice; the other slices keep the shared macro.
#define DEFINE_BAKE_DOT(NAME, COREID, UVN)                                                            \
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
        float* o = out;                                                                               \
        BakeEntry* e = entries;                                                                       \
        int n = count;                                                                                \
        do                                                                                            \
        {                                                                                             \
            uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);                                           \
            uint32_t u[4];                                                                            \
            u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = 0; u[3] = 0;                                     \
            if (UVN == 4) { u[2] = s[2] / 3; u[3] = s[3] / 3; }                                       \
            float* c = (float*)(hB.b + hB.d * e->f8);                                                 \
            float color[4];                                                                           \
            color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = 0.0f;                       \
            float* ps = (float*)(pos->base + pos->stride * e->f0);                                    \
            float p3[3];                                                                              \
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];                                              \
            float res[3];                                                                             \
            float scratch[3];                                                                         \
            void* uvp = (UVN == 2) ? (void*)&u[0] : (void*)u;                                         \
            if (COREID == 1) FUN_006c3b90(res, scratch, p3, axisDir, color, uvp, param10);            \
            else FUN_006c3780(res, scratch, p3, axisDir, color, uvp, param10);                        \
            float scale = scaleInfo->scale;                                                           \
            o[0] = BakeMulSS(BakeAddSS(BakeMulSS(axis[0], res[0]), axis[2]), scale);                  \
            o[1] = BakeMulSS(BakeSubSS(1.0f, BakeAddSS(BakeMulSS(res[1], axis[1]), axis[3])), scale); \
            o += 2;                                                                                   \
            e += 1;                                                                                   \
        } while (--n);                                                                                \
    }                                                                                                 \
    return true;                                                                                      \
}

DEFINE_BAKE(Bake_6ceb60, 3, 2, 1, 2, 1)     // @ 0x006ceb60  uv2u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6cee20, 3, 4)          // @ 0x006cee20  uv4u16 / colour2f / dot
DEFINE_BAKE(Bake_6cf120, 1, 4, 0, 2, 1)     // @ 0x006cf120  uv4u8  / colour2f / dot
DEFINE_BAKE_DOT(Bake_6cf420, 1, 2)          // @ 0x006cf420  uv2u16 / colour2f / dot
DEFINE_BAKE_DOT(Bake_6cf6f0, 1, 4)          // @ 0x006cf6f0  uv4u16 / colour2f / dot
