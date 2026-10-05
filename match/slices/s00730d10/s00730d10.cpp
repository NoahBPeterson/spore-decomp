// Slice s00730d10 — 0x00730d10.  Sibling of 0x00730240: blends up to four weighted palette
// transforms per vertex and writes the transformed position plus optionally two normalised
// float3 normals (the byte/colour variant is 0x00730240).  Behaviourally equivalent
// reconstruction, not byte exact.
#include "types.h"
#include <math.h>

struct EltArray
{
    int32_t  mNumElts;    // +0x00
    uint8_t* mData;       // +0x04
    uint16_t mEltSize;    // +0x08
    uint16_t mEltStride;  // +0x0a
    void*    mDataRC;     // +0x0c
};

static inline int32_t ElemU32(EltArray* a, int i)
{
    return *(int32_t*)(a->mData + (uint32_t)a->mEltStride * (uint32_t)i);
}

// @ 0x00730d10
void FUN_00730d10(EltArray* p1, EltArray* p2, uint32_t p3, EltArray* p4, EltArray* p5,
                  EltArray* p6, EltArray* p7, EltArray* p8, EltArray* p9,
                  uint8_t* p10, char p11)
{
    bool hasA = p7->mData != 0;
    bool hasB = p9->mData != 0;
    bool weighted = (p3 >= 2) && (p2->mData != 0);

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

    float inv0 = 1.0f;  // row 0 inverse squared length
    float inv1 = 1.0f;  // row 1
    float inv2 = 1.0f;  // row 2

    for (int i = 0; i < count; ++i)
    {
        uint8_t* idxp = p1->mData + (uint32_t)p1->mEltStride * (uint32_t)i;
        float m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11;

        if (weighted)
        {
            uint32_t u = (uint32_t)ElemU32(p2, i);
            float w[4];
            w[0] = (float)(u & 0xffu)          * 0.003921569f;
            w[1] = (float)((u >> 8) & 0xffu)   * 0.003921569f;
            w[2] = (float)((u >> 16) & 0xffu)  * 0.003921569f;
            w[3] = (float)((u >> 24) & 0xffu)  * 0.003921569f;

            uint8_t* p = p10 + (uint32_t)idxp[0] * 16u;
            m1  = *(float*)(p + 0x04) * w[0];
            m3  = *(float*)(p + 0x0c) * w[0];
            m2  = *(float*)(p + 0x08) * w[0];
            m4  = w[0] * *(float*)(p + 0x10);
            m7  = *(float*)(p + 0x1c) * w[0];
            m0  = w[0] * *(float*)(p + 0x00);
            m5  = *(float*)(p + 0x14) * w[0];
            m6  = *(float*)(p + 0x18) * w[0];
            m9  = *(float*)(p + 0x24) * w[0];
            m10 = *(float*)(p + 0x28) * w[0];
            m8  = *(float*)(p + 0x20) * w[0];
            m11 = *(float*)(p + 0x2c) * w[0];

            for (uint32_t k = 1; k < p3; ++k)
            {
                float f = w[k];
                uint8_t* q = p10 + (uint32_t)idxp[k] * 16u;
                m0  = f * *(float*)(q + 0x00) + m0;
                m1  = *(float*)(q + 0x04) * f + m1;
                m3  = *(float*)(q + 0x0c) * f + m3;
                m5  = m5  + *(float*)(q + 0x14) * f;
                m2  = *(float*)(q + 0x08) * f + m2;
                m6  = m6  + *(float*)(q + 0x18) * f;
                m4  = m4  + f * *(float*)(q + 0x10);
                m7  = m7  + *(float*)(q + 0x1c) * f;
                m8  = m8  + *(float*)(q + 0x20) * f;
                m9  = m9  + *(float*)(q + 0x24) * f;
                m10 = m10 + *(float*)(q + 0x28) * f;
                m11 = m11 + *(float*)(q + 0x2c) * f;
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
            inv2 = 1.0f / ((m2 * m2 + m6 * m6) + m10 * m10);
            inv1 = 1.0f / ((m1 * m1 + m5 * m5) + m9 * m9);
            inv0 = 1.0f / ((m0 * m0 + m4 * m4) + m8 * m8);
        }

        float* pin  = (float*)(p4->mData + (uint32_t)p4->mEltStride * (uint32_t)i);
        float  px = pin[0];
        float  py = pin[1];
        float  pz = pin[2];
        float* pout = (float*)(p5->mData + (uint32_t)p5->mEltStride * (uint32_t)i);
        pout[0] = ((py * m1 + px * m0) + pz * m2) + m3;
        pout[1] = ((pz * m6 + py * m5) + px * m4) + m7;
        pout[2] = ((pz * m10 + py * m9) + px * m8) + m11;

        if (hasA)
        {
            float* cin = (float*)(p6->mData + (uint32_t)p6->mEltStride * (uint32_t)i);
            float cx = cin[0];
            float cy = cin[1];
            float cz = cin[2];
            float q0 = ((cy * m1 + cx * m0) + cz * m2) * inv0;
            float q1 = ((cz * m6 + cy * m5) + cx * m4) * inv1;
            float q2 = ((cz * m10 + cy * m9) + cx * m8) * inv2;
            float r  = 1.0f / sqrtf((q1 * q1 + (q2 * q2 + q0 * q0)) + 1e-08f);
            float* out = (float*)(p7->mData + (uint32_t)p7->mEltStride * (uint32_t)i);
            out[0] = r * q0;
            out[1] = q1 * r;
            out[2] = q2 * r;
        }

        if (hasB)
        {
            float* cin = (float*)(p8->mData + (uint32_t)p8->mEltStride * (uint32_t)i);
            float cx = cin[0];
            float cy = cin[1];
            float cz = cin[2];
            float q0 = ((cy * m1 + cx * m0) + cz * m2) * inv0;
            float q1 = ((cz * m6 + cy * m5) + cx * m4) * inv1;
            float q2 = ((cz * m10 + cy * m9) + cx * m8) * inv2;
            float r  = 1.0f / sqrtf((q1 * q1 + (q2 * q2 + q0 * q0)) + 1e-08f);
            float* out = (float*)(p9->mData + (uint32_t)p9->mEltStride * (uint32_t)i);
            out[0] = r * q0;
            out[1] = q1 * r;
            out[2] = q2 * r;
        }
    }
}
