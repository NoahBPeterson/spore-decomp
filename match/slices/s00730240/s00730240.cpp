// Slice s00730240 — 0x00730240.  A per-vertex skinning/normal-combining routine used by the
// morph/dynamic-draw path (SP::cDynamicDraw).  It walks a vertex range, blends up to 4 weighted
// transforms from a palette, transforms the input position into the output position stream and
// optionally writes two packed-normal/colour streams.  Behaviourally equivalent reconstruction
// (not byte exact: the original keeps a dozen values live on the x87 stack and reuses slots).
#include "types.h"
#include <math.h>

// SP::cEltArrayRef (32-bit layout) as recovered from the dev-build PDB; retail reads only the
// first four fields here.
struct EltArray
{
    int32_t  mNumElts;    // +0x00
    uint8_t* mData;       // +0x04
    uint16_t mEltSize;    // +0x08
    uint16_t mEltStride;  // +0x0a
    void*    mDataRC;     // +0x0c
};

// The palette transform base: a 16-byte-strided record holding 12 floats (0x00..0x2c).
static inline float Pal(uint8_t* base, int idx, int off)
{
    return *(float*)(base + (uint32_t)idx * 16u + off);
}

static inline int32_t ElemU32(EltArray* a, int i)
{
    return *(int32_t*)(a->mData + (uint32_t)a->mEltStride * (uint32_t)i);
}

// @ 0x00730240
void FUN_00730240(EltArray* p1, EltArray* p2, uint32_t p3, EltArray* p4, EltArray* p5,
                  EltArray* p6, EltArray* p7, EltArray* p8, EltArray* p9,
                  uint8_t* p10, char p11)
{
    bool hasA = p7->mData != 0;
    bool hasB = p9->mData != 0;

    bool weighted = (p3 > 1) && (p2->mData != 0);

    if (p11 != 0)
    {
        if (hasA)
            p11 = 1;
        else
        {
            p11 = 0;
            if (hasB)
                p11 = 1;
        }
    }

    // When exactly four influence weights are packed in one dword, drop the trailing zero
    // channels (a colour key can store fewer than four weights).
    if (weighted && p3 == 4)
    {
        uint32_t v = *(uint32_t*)p2->mData;
        uint32_t cnt;
        if ((v & 0xff000000u) == 0)
        {
            if (p2->mNumElts > 0)
            {
                uint8_t* q = p2->mData;
                int n = p2->mNumElts - 1;
                while (n--)
                {
                    q += p2->mEltStride;
                    v |= *(uint32_t*)q;
                }
            }
            cnt = ((v & 0xffu) != 0);
            if (((v >> 8) & 0xffu) != 0)  ++cnt;
            if (((v >> 16) & 0xffu) != 0) ++cnt;
            if (((v >> 24) & 0xffu) != 0) ++cnt;
        }
        else
            cnt = 4;
        if (cnt < 4)
            p3 = cnt;
        weighted = p3 > 1;
    }

    int32_t count = p4->mNumElts;
    if (count <= 0)
        return;

    float d4 = 1.0f;  // inverse squared length, row 0
    float d0 = 1.0f;  // inverse squared length, row 1
    float cc = 1.0f;  // inverse squared length, row 2

    for (int i = 0; i < count; ++i)
    {
        uint8_t* idxp = p1->mData + (uint32_t)p1->mEltStride * (uint32_t)i;
        float m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11;

        if (weighted)
        {
            uint32_t u = *(uint32_t*)(p2->mData + (uint32_t)p2->mEltStride * (uint32_t)i);
            float w[4];
            w[0] = (float)(u & 0xffu)          * 0.003921569f;
            w[1] = (float)((u >> 8) & 0xffu)   * 0.003921569f;
            w[2] = (float)((u >> 16) & 0xffu)  * 0.003921569f;
            w[3] = (float)((u >> 24) & 0xffu)  * 0.003921569f;

            m2  = Pal(p10, idxp[0], 0x08) * w[0];
            m0  = w[0] * Pal(p10, idxp[0], 0x00);
            m1  = Pal(p10, idxp[0], 0x04) * w[0];
            m3  = Pal(p10, idxp[0], 0x0c) * w[0];
            m5  = Pal(p10, idxp[0], 0x14) * w[0];
            m7  = Pal(p10, idxp[0], 0x1c) * w[0];
            m4  = w[0] * Pal(p10, idxp[0], 0x10);
            m6  = Pal(p10, idxp[0], 0x18) * w[0];
            m8  = Pal(p10, idxp[0], 0x20) * w[0];
            m9  = Pal(p10, idxp[0], 0x24) * w[0];
            m10 = Pal(p10, idxp[0], 0x28) * w[0];
            m11 = Pal(p10, idxp[0], 0x2c) * w[0];

            for (uint32_t k = 1; k < p3; ++k)
            {
                float f = w[k];
                uint8_t* p = p10 + (uint32_t)idxp[k] * 16u;
                m0  = f * *(float*)(p + 0x00) + m0;
                m1  = *(float*)(p + 0x04) * f + m1;
                m2  = *(float*)(p + 0x08) * f + m2;
                m3  = *(float*)(p + 0x0c) * f + m3;
                m6  = m6  + *(float*)(p + 0x18) * f;
                m4  = m4  + *(float*)(p + 0x10) * f;
                m5  = m5  + *(float*)(p + 0x14) * f;
                m10 = m10 + *(float*)(p + 0x28) * f;
                m7  = m7  + *(float*)(p + 0x1c) * f;
                m9  = m9  + *(float*)(p + 0x24) * f;
                m8  = m8  + *(float*)(p + 0x20) * f;
                m11 = m11 + *(float*)(p + 0x2c) * f;
            }
        }
        else
        {
            uint8_t* p = p10 + (uint32_t)idxp[0] * 16u;
            m0  = *(float*)(p + 0x00);
            m1  = *(float*)(p + 0x04);
            m2  = *(float*)(p + 0x08);
            m3  = *(float*)(p + 0x0c);
            m4  = *(float*)(p + 0x10);
            m5  = *(float*)(p + 0x14);
            m6  = *(float*)(p + 0x18);
            m7  = *(float*)(p + 0x1c);
            m8  = *(float*)(p + 0x20);
            m9  = *(float*)(p + 0x24);
            m10 = *(float*)(p + 0x28);
            m11 = *(float*)(p + 0x2c);
        }

        if (p11 != 0)
        {
            d4 = 1.0f / ((m0 * m0 + m4 * m4) + m8 * m8);
            d0 = 1.0f / ((m1 * m1 + m5 * m5) + m9 * m9);
            cc = 1.0f / ((m2 * m2 + m6 * m6) + m10 * m10);
        }

        float* pin  = (float*)(p4->mData + (uint32_t)p4->mEltStride * (uint32_t)i);
        float  px = pin[0];
        float  py = pin[1];
        float  pz = pin[2];
        float* pout = (float*)(p5->mData + (uint32_t)p5->mEltStride * (uint32_t)i);
        pout[0] = ((px * m0 + pz * m2) + py * m1) + m3;
        pout[1] = ((m4 * px + m6 * pz) + m5 * py) + m7;
        pout[2] = ((m8 * px + m10 * pz) + m9 * py) + m11;

        if (hasA)
        {
            uint32_t u = (uint32_t)ElemU32(p6, i);
            float r = (float)(u & 0xffu)         * 0.007874016f - 1.0f;
            float g = (float)((u >> 8) & 0xffu)  * 0.007874016f - 1.0f;
            float b = (float)((u >> 16) & 0xffu) * 0.007874016f - 1.0f;
            float c8 = (r * m0 + b * m2 + g * m1) * d4;
            float c0 = (m8 * r + m10 * b + m9 * g) * cc;
            float c4 = (m4 * r + m6 * b + m5 * g) * d0;
            float inv = 1.0f / sqrtf((c4 * c4 + (c0 * c0 + c8 * c8)) + 1e-08f);
            float x = inv * c8;
            float y = c4 * inv;
            float z = c0 * inv;
            *(uint32_t*)(p7->mData + (uint32_t)p7->mEltStride * (uint32_t)i) =
                ((((uint32_t)(int32_t)(z * 127.0f) + 0x7fu) << 8) |
                  ((uint32_t)(int32_t)(y * 127.0f) + 0x7fu)) << 8 |
                  ((uint32_t)(int32_t)(x * 127.0f) + 0x7fu);
        }

        if (hasB)
        {
            uint32_t u = (uint32_t)ElemU32(p8, i);
            float r = (float)(u & 0xffu)         * 0.007874016f - 1.0f;
            float g = (float)((u >> 8) & 0xffu)  * 0.007874016f - 1.0f;
            float b = (float)((u >> 16) & 0xffu) * 0.007874016f - 1.0f;
            float b0 = (r * m0 + b * m2 + g * m1) * d4;
            float a8 = (m8 * r + m10 * b + m9 * g) * cc;
            float ac = (m4 * r + m6 * b + m5 * g) * d0;
            float inv = 1.0f / sqrtf((b0 * b0 + (ac * ac + a8 * a8)) + 1e-08f);
            float x = inv * b0;
            float y = ac * inv;
            float z = a8 * inv;
            *(uint32_t*)(p9->mData + (uint32_t)p9->mEltStride * (uint32_t)i) =
                ((((uint32_t)(int32_t)(z * 127.0f) + 0x7fu) << 8) |
                  ((uint32_t)(int32_t)(y * 127.0f) + 0x7fu)) << 8 |
                  ((uint32_t)(int32_t)(x * 127.0f) + 0x7fu);
        }
    }
}
