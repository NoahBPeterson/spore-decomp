// Slice s00731620 — vertex-blend / normal output family plus small index helpers.
// 0x00731620 is the float-weight sibling of 0x00730d10; 0x00731e70 dispatches between the
// three vertex routines.  The small helpers are the surrounding element-array bookkeeping.
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

// ---- callees defined in other slices (masked relocations) --------------------------------
void FUN_00730240(EltArray*, EltArray*, uint32_t, EltArray*, EltArray*, EltArray*, EltArray*,
                  EltArray*, EltArray*, uint8_t*, char);
void FUN_00730d10(EltArray*, EltArray*, uint32_t, EltArray*, EltArray*, EltArray*, EltArray*,
                  EltArray*, EltArray*, uint8_t*, char);
void FUN_007200f0(void*);                       // element destructor helper
int  FUN_0071ddc0(int, int, int, int, int);     // descriptor lookup
void FUN_00698650(float*);                      // matrix normalise helper
uint8_t* GetPropertyAsKeyArray(void);           // SP::GetPropertyAsKeyArray

struct IPropList
{
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual char Get(int key, int* out);        // slot 9 (+0x24)
};
extern IPropList* g_sAppProperties;             // [0x015fd918]

// @ 0x00731620
void FUN_00731620(EltArray* p1, EltArray* p2, uint32_t p3, EltArray* p4, EltArray* p5,
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

    int32_t count = p4->mNumElts;
    if (count <= 0)
        return;

    float inv0 = 1.0f;
    float inv1 = 1.0f;
    float inv2 = 1.0f;

    for (int i = 0; i < count; ++i)
    {
        uint16_t* puVar9 = (uint16_t*)(p1->mData + (uint32_t)p1->mEltStride * (uint32_t)i);
        float m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11;

        if (weighted)
        {
            float w[6];
            if (p3 != 0)
            {
                float* src = (float*)(p2->mData + (uint32_t)p2->mEltStride * (uint32_t)i);
                for (uint32_t k = 0; k < p3; ++k)
                    w[k] = src[k];
            }
            uint8_t* p = p10 + (uint32_t)puVar9[0] * 16u;
            m3  = *(float*)(p + 0x0c) * w[0];
            m5  = *(float*)(p + 0x14) * w[0];
            m7  = *(float*)(p + 0x1c) * w[0];
            m9  = *(float*)(p + 0x24) * w[0];
            m0  = w[0] * *(float*)(p + 0x00);
            m1  = *(float*)(p + 0x04) * w[0];
            m11 = *(float*)(p + 0x2c) * w[0];
            m10 = *(float*)(p + 0x28) * w[0];
            m2  = *(float*)(p + 0x08) * w[0];
            m4  = w[0] * *(float*)(p + 0x10);
            m6  = *(float*)(p + 0x18) * w[0];
            m8  = *(float*)(p + 0x20) * w[0];

            for (uint32_t k = 1; k < p3; ++k)
            {
                float f = w[k];
                uint8_t* q = p10 + (uint32_t)puVar9[k] * 16u;
                m3  = *(float*)(q + 0x0c) * f + m3;
                m2  = *(float*)(q + 0x08) * f + m2;
                m1  = *(float*)(q + 0x04) * f + m1;
                m0  = f * *(float*)(q + 0x00) + m0;
                m6  = *(float*)(q + 0x18) * f + m6;
                m7  = *(float*)(q + 0x1c) * f + m7;
                m8  = *(float*)(q + 0x20) * f + m8;
                m4  = m4 + f * *(float*)(q + 0x10);
                m5  = *(float*)(q + 0x14) * f + m5;
                m9  = *(float*)(q + 0x24) * f + m9;
                m10 = *(float*)(q + 0x28) * f + m10;
                m11 = *(float*)(q + 0x2c) * f + m11;
            }
        }
        else
        {
            uint8_t* p = p10 + (uint32_t)puVar9[0] * 16u;
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
            inv0 = 1.0f / ((m0 * m0 + m4 * m4) + m8 * m8);
            inv1 = 1.0f / ((m1 * m1 + m5 * m5) + m9 * m9);
            inv2 = 1.0f / ((m2 * m2 + m6 * m6) + m10 * m10);
        }

        float* pin = (float*)(p4->mData + (uint32_t)p4->mEltStride * (uint32_t)i);
        float px = pin[0];
        float py = pin[1];
        float pz = pin[2];
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
            float r = 1.0f / sqrtf((q1 * q1 + (q2 * q2 + q0 * q0)) + 1e-08f);
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
            float r = 1.0f / sqrtf((q1 * q1 + (q2 * q2 + q0 * q0)) + 1e-08f);
            float* out = (float*)(p9->mData + (uint32_t)p9->mEltStride * (uint32_t)i);
            out[0] = r * q0;
            out[1] = q1 * r;
            out[2] = q2 * r;
        }
    }
}

// @ 0x00731e70
void FUN_00731e70(uint32_t count, int selector, EltArray* a, EltArray* b,
                  EltArray* c, EltArray* d, EltArray* e, EltArray* f,
                  EltArray* g, EltArray* h, uint8_t* verts)
{
    uint8_t uVar1 = 1;
    int local_4;
    if (g_sAppProperties != 0)
    {
        if (g_sAppProperties->Get(0xece4a7a5, &local_4) != 0 &&
            *(int16_t*)(local_4 + 0x12) == 1)
        {
            uVar1 = *GetPropertyAsKeyArray();
        }
    }

    if (selector == 7)
    {
        if (e->mData != 0 && e->mEltSize == 4)
        {
            FUN_00730240(a, b, count, c, d, e, f, g, h, verts, (char)uVar1);
            return;
        }
        FUN_00730d10(a, b, count, c, d, e, f, g, h, verts, (char)uVar1);
        return;
    }
    if (selector == 8 || selector == 9)
    {
        FUN_00731620(a, b, count, c, d, e, f, g, h, verts, (char)uVar1);
    }
}

// @ 0x00731fa0
struct Sub8C
{
    char  pad0[0x14];
    int*  mBegin;   // +0x14
    int*  mEnd;     // +0x18
    char  pad1[0x8c - 0x1c];
};
struct Container1C
{
    char  pad0[0x1c];
    Sub8C* mBegin;  // +0x1c
    Sub8C* mEnd;    // +0x20
};
int FUN_00731fa0(Container1C* c, int** v)
{
    int iVar4 = (int)(v[1] - v[0]);
    int n = (int)(c->mEnd - c->mBegin);
    int idx = 0;
    if (n > 0)
    {
        Sub8C* s = c->mBegin;
        do
        {
            if ((int)(s->mEnd - s->mBegin) == iVar4)
            {
                int iVar5 = 0;
                if (iVar4 > 0)
                {
                    int* a = v[0];
                    do
                    {
                        if (*(int16_t*)&a[iVar5] != *(int16_t*)&s->mBegin[iVar5])
                            break;
                        iVar5++;
                    } while (iVar5 < iVar4);
                }
                if (iVar5 == iVar4)
                    return idx;
            }
            idx++;
            s++;
        } while (idx < n);
    }
    return -1;
}

// @ 0x00732040
struct Stream40
{
    char     pad0[8];
    int32_t  mType;     // +0x08
    char     pad1[0x14 - 0x0c];
    uint8_t* mData;     // +0x14
    char     pad2[0x1a - 0x18];
    uint16_t mStride;   // +0x1a
};
void FUN_00732040(Stream40* s, int32_t v, int start, int end)
{
    switch (s->mType)
    {
    case 7:
        for (; start < end; ++start)
        {
            char* p = (char*)(s->mData + (uint32_t)s->mStride * (uint32_t)start);
            p[0] += (char)v;
            p[1] += (char)v;
            p[2] += (char)v;
            p[3] += (char)v;
        }
        break;
    case 8:
        for (; start < end; ++start)
        {
            int16_t* p = (int16_t*)(s->mData + (uint32_t)s->mStride * (uint32_t)start);
            p[0] += (int16_t)v;
            p[1] += (int16_t)v;
        }
        break;
    case 9:
        for (; start < end; ++start)
        {
            int16_t* p = (int16_t*)(s->mData + (uint32_t)s->mStride * (uint32_t)start);
            p[0] += (int16_t)v;
            p[1] += (int16_t)v;
            p[2] += (int16_t)v;
            p[3] += (int16_t)v;
        }
        break;
    }
}

// @ 0x007320f0
struct E20   { char pad[0x20]; };
struct E10v  { char pad[0x10]; };
struct Sub8Cv { char pad0[0x44]; E10v* mBegin; E10v* mEnd; char pad1[0x8c - 0x4c]; };
struct C60
{
    char    pad0[8];
    E20*    mBegin;   // +0x08
    E20*    mEnd;     // +0x0c
    char    pad1[0xc];
    Sub8Cv* mBegin2;  // +0x1c
    Sub8Cv* mEnd2;    // +0x20
};
void FUN_007320f0(C60* c)
{
    int n = (int)(c->mEnd - c->mBegin);
    if (n > 0)
    {
        int off = 0;
        do
        {
            FUN_007200f0((char*)c->mBegin + off + 0x10);
            off += 0x20;
        } while (--n);
    }
    int m = (int)(c->mEnd2 - c->mBegin2);
    if (m > 0)
    {
        int off = 0;
        do
        {
            Sub8Cv* s = (Sub8Cv*)((char*)c->mBegin2 + off);
            FUN_007200f0(s);
            int k = (int)(s->mEnd - s->mBegin);
            if (k > 0)
            {
                int o2 = 0;
                do
                {
                    FUN_007200f0((char*)s->mBegin + o2);
                    o2 += 0x10;
                } while (--k);
            }
            off += 0x8c;
        } while (--m);
    }
}

// @ 0x007321a0
struct E10
{
    int32_t  pad0;      // +0x00
    int32_t* mPtr;      // +0x04
    uint16_t mIdx;      // +0x08
    uint16_t mStride;   // +0x0a
    int32_t  pad1;      // +0x0c
};
struct C44
{
    char pad0[0x44];
    E10* mBegin;        // +0x44
    E10* mEnd;          // +0x48
};
extern uint32_t g_masks[];
bool FUN_007321a0(C44* c, int p2, int p3)
{
    int n = (int)(c->mEnd - c->mBegin);
    if (n > 0)
    {
        int i = 0;
        E10* e = c->mBegin;
        do
        {
            if (e->mPtr == 0)
                return false;
            uint32_t mask = g_masks[e->mIdx];
            if ((*(uint32_t*)((uint8_t*)e->mPtr + (uint32_t)e->mStride * (uint32_t)p2) & mask) !=
                (*(uint32_t*)((uint8_t*)e->mPtr + (uint32_t)e->mStride * (uint32_t)p3) & mask))
            {
                return false;
            }
            i++;
            e++;
        } while (i < n);
    }
    return true;
}

// @ 0x00732220
struct Caller220 { int f(int a, int b); };
bool FUN_00732220(Caller220* self, int* vec, int val)
{
    if (val < 0)
        return false;
    int i = 0;
    int n = (int)(vec[1] - vec[0]) >> 2;
    if (n > 0)
    {
        do
        {
            int key = *(int*)(vec[0] + i * 4);
            val = self->f(key, val);
            if (val < 0)
                return true;
            i++;
        } while (i < n);
    }
    return false;
}

// @ 0x00732270  (vertex writer: normalised 3x3 matrix into a packed stream)
void FUN_00732270(float* pm, uint16_t* out)
{
    float tmp[9];
    tmp[0] = pm[0];
    tmp[1] = pm[4];
    tmp[2] = pm[8];
    tmp[3] = pm[1];
    tmp[4] = pm[5];
    tmp[5] = pm[9];
    tmp[6] = pm[2];
    tmp[7] = pm[6];
    tmp[8] = pm[10];

    out[1] = (uint16_t)(out[1] + 1);
    *(float*)((uint8_t*)out + 0x10) =
        sqrtf((pm[9] * pm[9] + pm[5] * pm[5]) + pm[1] * pm[1]);
    FUN_00698650(tmp);
    *(uint16_t*)out |= 2;
    out[1] = (uint16_t)(out[1] + 1);
    float* dst = (float*)((uint8_t*)out + 0x14);
    for (int i = 0; i < 9; ++i)
        dst[i] = tmp[i];
    *(float*)((uint8_t*)out + 4)  = pm[3];
    *(float*)((uint8_t*)out + 8)  = pm[7];
    *(float*)((uint8_t*)out + 0xc) = pm[0xb];
    *(uint16_t*)out |= 4;
    out[1] = (uint16_t)(out[1] + 1);
}

// @ 0x00732360
bool FUN_00732360(int p)
{
    int i = FUN_0071ddc0(p, 2, -1, 0, 0xe);
    if (i >= 0)
    {
        int v = *(int*)(i * 0x20 + *(int*)(p + 8) + 8);
        if (v >= 3 && v <= 4)
            return true;
    }
    i = FUN_0071ddc0(p, 3, -1, 0, 0xe);
    if (i >= 0)
    {
        int v = *(int*)(i * 0x20 + *(int*)(p + 8) + 8);
        if (v >= 3 && v <= 4)
            return true;
    }
    i = FUN_0071ddc0(p, 10, -1, 0, 0xe);
    if (i >= 0)
    {
        int v = *(int*)(i * 0x20 + *(int*)(p + 8) + 8);
        if (v >= 1 && v <= 4)
            return true;
    }
    i = FUN_0071ddc0(p, 9, -1, 0, 0xe);
    if (i >= 0)
    {
        int v = *(int*)(i * 0x20 + *(int*)(p + 8) + 8);
        if (v == 8 || v == 9)
            return true;
    }
    return false;
}
