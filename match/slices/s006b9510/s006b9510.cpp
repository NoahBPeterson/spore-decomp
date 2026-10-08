// Slice s006b9510: array transform kernels.
// 0x006b9510: apply a (optional 3x3 matrix) * scale + translation transform in place to `count`
// 3-float points spaced `stride` bytes apart (manually 4x unrolled, remainder loop).
// 0x006b9dc0 is still a skeleton (partial).
#include "types.h"

struct XformKernel
{
    uint16_t flags;     // bit1: has matrix, bit2: has translation
    uint16_t pad;
    float    t[3];      // +4 translation
    float    s;         // +0x10 uniform scale
    float    m[9];      // +0x14 3x3 matrix (columns gathered as m[i], m[3+i], m[6+i])
};

static inline void RotElem(const XformKernel* xf, float* p)
{
    float x = p[0];
    float y = p[1];
    float z = p[2];
    p[0] = (xf->m[3] * y + xf->m[6] * z) + x * xf->m[0];
    p[1] = (xf->m[1] * x + xf->m[4] * y) + xf->m[7] * z;
    p[2] = (xf->m[2] * x + xf->m[5] * y) + xf->m[8] * z;
}

static inline void FullElem(const XformKernel* xf, float* p)
{
    if (xf->flags & 2)
        RotElem(xf, p);
    float s = xf->s;
    float z = p[2];
    p[0] = s * p[0];
    p[1] = s * p[1];
    p[2] = s * z;
    float t2 = xf->t[2];
    float t1 = xf->t[1];
    p[0] = xf->t[0] + p[0];
    p[1] = p[1] + t1;
    p[2] = t2 + s * z;
}

static inline uint8_t Bit(uint16_t f, int n) { uint8_t b = (uint8_t)f; b >>= n; return b; }

static inline float* Adv(float* p, int stride) { return (float*)((char*)p + stride); }

// @ 0x006b9510
void __cdecl FUN_006b9510(const XformKernel* xf, int count, float* p, int stride)
{
    uint16_t f = xf->flags;
    if (Bit(f, 1) & 1)
    {
        for (int i = 0; i < count; i++)
        {
            FullElem(xf, p);
            p = Adv(p, stride);
        }
        return;
    }
    float s = xf->s;
    if (s != 1.0f && Bit(f, 2) & 1)
    {
        float t0 = xf->t[0], t1 = xf->t[1], t2 = xf->t[2];
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] * s + t0;
            p[1] = p[1] * s + t1;
            p[2] = s * p[2] + t2;
            p = Adv(p, stride);
        }
    }
    else if (s != 1.0f)
    {
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] * s;
            p[1] = p[1] * s;
            p[2] = s * p[2];
            p = Adv(p, stride);
        }
    }
    else if (Bit(f, 2) & 1)
    {
        float t0 = xf->t[0], t1 = xf->t[1], t2 = xf->t[2];
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] + t0;
            p[1] = p[1] + t1;
            p[2] = t2 + p[2];
            p = Adv(p, stride);
        }
    }
}

// @ 0x006b9dc0
int __cdecl FUN_006b9dc0(const void* xform, float* dst, const float* src, int count, int stride)
{
    (void)xform; (void)dst; (void)src; (void)count; (void)stride;
    return 0;
}
