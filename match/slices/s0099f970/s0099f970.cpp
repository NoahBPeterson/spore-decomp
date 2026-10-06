// Keyframe track evaluation (Hermite spline over float channels, slerp-style blend for quaternion channels).
#include "types.h"

typedef uint32_t u32;
typedef uint8_t u8;

struct TrackDesc {
    char pad0[0x118];
    u8 flags118;          // bit 3: looping
    char pad119[7];
    float wrapTime;       // +0x120
};

struct Channel {          // 0x20 bytes
    u32 flags;            // low 4 bits: type, 0x10: enabled, 0x20: no clamp
    u32 keyed;            // +4
    u32 offset;           // +8
    u32 stride;           // +0xc
    u32 slot;             // +0x10 index into g_channelSlotTable
    u32 pad[3];
};

struct Track {
    void* vtbl;
    TrackDesc* desc;                // +4
    char pad8[0xd4 - 8];
    int keyCount;                   // +0xd4
    char* data;                     // +0xd8
    u32 channelCount;               // +0xdc
    Channel* channels;              // +0xe0
};

struct SlotEntry { int offset; int pad[7]; };
extern SlotEntry g_channelSlotTable[];   // 0x01446cc0
extern int g_quatBlendFlag;              // 0x015504f8

void FindNeighbours(Track* t, int* upper, int* prev, int* lower, int* next);        // 0x99c9f0
float* QuatBlend(float* out, const float* a, const float* b, float t);               // 0x99cc70
float* QuatMul(float* out, const float* a, const float* b);                          // 0x99cba0
float* QuatNormalize(float* out, const float* in, float* lenOut);                    // 0x99cae0
void CopyFixedKey(int stride, char* data, Channel* chans, u32 count, u32* out);      // 0x99f900

static inline float Fwd(u32 a, u32 b, float W)
{
    if (a < b) {
        return W - (float)b;
    }
    return (float)(a - b);
}

static inline float Nxt(u32 a, u32 b)
{
    u32 u = b;
    if (a <= u) {
        u = u - a;
    }
    return (float)u;
}

static inline float TanOut(u32 mode, float v0, float v1, float v2, float tn, float d01, float d12)
{
    if (mode == 0) {
        return ((v2 - v0) / (d12 + d01)) * d12;
    }
    if (mode == 1) {
        return v2 - v1;
    }
    if (mode == 3) {
        return tn * d12;
    }
    return 0.0f;
}

static inline float TanIn(u32 mode, float v1, float v2, float v3, float tn, float d21, float d23)
{
    if (mode == 0) {
        return ((v3 - v1) / (d23 + d21)) * d21;
    }
    if (mode == 1) {
        return v2 - v1;
    }
    if (mode == 3) {
        return tn * d21;
    }
    return 0.0f;
}

static inline float Clamp01(float f)
{
    if (0.0f < f) {
        if (1.0f < f) {
            f = 1.0f;
        }
        return f;
    }
    return 0.0f;
}

#define F(p, off) (*(float*)((char*)(p) + (off)))
#define B(p, off) (*(u8*)((char*)(p) + (off)))

// @ 0x0099f970
bool EvaluateTrack(float time, int upper, Track* trk, u32* out, int* outIndex)
{
    if (trk->keyCount == 0) {
        return false;
    }

    int prevIdx, lowerIdx, nextIdx;
    FindNeighbours(trk, &upper, &prevIdx, &lowerIdx, &nextIdx);

    u32 count = trk->channelCount;
    float W = trk->desc->wrapTime - 1.0f;

    // first enabled key channel
    Channel* kc = 0;
    {
        Channel* c = trk->channels;
        for (u32 i = 0; i < count; i++, c++) {
            if ((c->flags & 0xf) == 0 && c->keyed != 0) {
                kc = c;
                break;
            }
        }
    }

    char* data = trk->data;
    char* K1 = data + kc->stride * lowerIdx + kc->offset;   // lower key
    char* K2 = data + kc->stride * upper + kc->offset;      // upper key
    int lower = lowerIdx;

    if (lowerIdx == upper) {
        CopyFixedKey(lowerIdx, trk->data, trk->channels, count, out);
    } else {
        u32 t1 = *(u32*)K1;
        char* K0 = data + kc->stride * prevIdx + kc->offset;
        char* K3 = data + kc->stride * nextIdx + kc->offset;
        u32 t2 = *(u32*)K2;
        u32 t0 = *(u32*)K0;
        u32 t3 = *(u32*)K3;

        float s = (time - (float)t1) / (float)(t2 - t1);
        float s2 = s * s;
        float s3 = s2 * s;
        float h01 = s2 * 3.0f - s3 * 2.0f;
        float h00 = (1.0f - s2 * 3.0f) + s3 * 2.0f;
        float h10 = (s - s2 * 2.0f) + s3;
        float h11 = s3 - s2;

        float d01 = Fwd(t1, t0, W);
        float d12 = Nxt(t1, t2);
        float d21 = Fwd(t2, t1, W);
        float d23 = Nxt(t2, t3);

        for (u32 ci = 0; ci < count; ci++) {
            Channel* ch = &trk->channels[ci];
            if ((ch->flags & 0x10) == 0) {
                continue;
            }
            u32 type = ch->flags & 0xf;
            char* base = trk->data;
            u32 stride = ch->stride;
            u32 off = ch->offset;
            char* v1 = base + stride * lowerIdx + off;
            char* v2 = base + stride * upper + off;
            char* v0 = base + stride * prevIdx + off;
            char* v3 = base + stride * nextIdx + off;

            if (type == 1) {
                float* dst = (float*)(out + 5);
                for (int c = 0; c < 3; c++) {
                    int o = 0x10 * c;
                    float a = TanOut(B(v1, 0x19 + o) & 3, F(v0, 4 * c), F(v1, 4 * c), F(v2, 4 * c),
                                     F(v1, 0x14 + o), d01, d12);
                    float b = TanIn(B(v2, 0x18 + o) & 3, F(v1, 4 * c), F(v2, 4 * c), F(v3, 4 * c),
                                    F(v2, 0x10 + o), d21, d23);
                    dst[c] = ((F(v1, 4 * c) * h00 + F(v2, 4 * c) * h01) + b * h11) + a * h10;
                }
                {
                    float a = TanOut(B(v1, 0x49) & 3, F(v0, 0xc), F(v1, 0xc), F(v2, 0xc), F(v1, 0x44), d01, d12);
                    float b = TanIn(B(v2, 0x48) & 3, F(v1, 0xc), F(v2, 0xc), F(v3, 0xc), F(v2, 0x40), d21, d23);
                    float r = ((F(v2, 0xc) * h01 + F(v1, 0xc) * h00) + b * h11) + a * h10;
                    *(float*)&out[8] = Clamp01(r);
                }
            } else if (type == 2) {
                float q1[4], q2[4], q0[4], q3[4];
                for (int i = 0; i < 4; i++) {
                    q1[i] = F(v1, 4 * i);
                    q2[i] = F(v2, 4 * i);
                }
                u32 m1 = B(v1, 0x1d) & 3;
                if (m1 == 1) {
                    float tmp[4];
                    float* r = QuatBlend(tmp, q1, q2, -1.0f);
                    for (int i = 0; i < 4; i++) q0[i] = r[i];
                } else {
                    for (int i = 0; i < 4; i++) q0[i] = q2[i];
                    if (m1 != 2) {
                        for (int i = 0; i < 4; i++) q0[i] = F(v0, 4 * i);
                    }
                }
                u32 m2 = B(v2, 0x1c) & 3;
                if (m2 == 1) {
                    float tmp[4];
                    float* r = QuatBlend(tmp, q2, q1, -1.0f);
                    for (int i = 0; i < 4; i++) q3[i] = r[i];
                } else if (m2 == 2) {
                    for (int i = 0; i < 4; i++) q3[i] = q1[i];
                } else {
                    for (int i = 0; i < 4; i++) q3[i] = F(v3, 4 * i);
                }

                float* res;
                if (g_quatBlendFlag == 0) {
                    float a0[4], d0[4], c0[4], n90[4], nb0[4], r10[4];
                    float sp1 = s + 1.0f;
                    QuatBlend(a0, q0, q1, sp1);
                    QuatBlend(d0, q1, q2, s);
                    QuatBlend(c0, q2, q3, s - 1.0f);
                    QuatBlend(n90, a0, d0, sp1 * 0.5f);
                    QuatBlend(nb0, d0, c0, s * 0.5f);
                    res = QuatBlend(r10, n90, nb0, s);
                } else {
                    float sp1 = s + 1.0f;
                    float f0[4], n1[4], n2[4], n3[4], e30[4], e40[4], e70[4], e50[4], w[4], x[4], f130[4], res4[4];
                    QuatBlend(f0, q0, q1, sp1);
                    float oms = 1.0f - s;
                    for (int i = 0; i < 4; i++) {
                        w[i] = q2[i] * s;
                        x[i] = q1[i] * oms;
                    }
                    QuatNormalize(n1, QuatMul(e30, x, w), 0);
                    QuatBlend(f130, q2, q3, s - 1.0f);
                    float h = sp1 * 0.5f;
                    float omh = 1.0f - h;
                    float w2[4], x2[4];
                    for (int i = 0; i < 4; i++) {
                        w2[i] = n1[i] * h;
                        x2[i] = f0[i] * omh;
                    }
                    QuatNormalize(n2, QuatMul(e40, x2, w2), 0);
                    float hs = s * 0.5f;
                    float oms2 = 1.0f - hs;
                    float w3[4], x3[4];
                    for (int i = 0; i < 4; i++) {
                        w3[i] = f130[i] * hs;
                        x3[i] = n1[i] * oms2;
                    }
                    QuatNormalize(n3, QuatMul(e70, x3, w3), 0);
                    float w4[4], x4[4];
                    for (int i = 0; i < 4; i++) {
                        w4[i] = n3[i] * s;
                        x4[i] = n2[i] * oms;
                    }
                    res = QuatNormalize(res4, QuatMul(e50, x4, w4), 0);
                }
                out[0x19] = ((u32*)res)[0];
                out[0x1a] = ((u32*)res)[1];
                out[0x1b] = ((u32*)res)[2];
                out[0x1c] = ((u32*)res)[3];

                float a = TanOut(B(v1, 0x5d) & 3, F(v0, 0x10), F(v1, 0x10), F(v2, 0x10), F(v1, 0x58), d01, d12);
                float b = TanIn(B(v2, 0x5c) & 3, F(v1, 0x10), F(v2, 0x10), F(v3, 0x10), F(v2, 0x54), d21, d23);
                float r = ((F(v2, 0x10) * h01 + F(v1, 0x10) * h00) + b * h11) + a * h10;
                *(float*)&out[0x1d] = Clamp01(r);
            } else if (type == 3) {
                float* dst = (float*)((char*)out + g_channelSlotTable[ch->slot].offset);
                for (int c = 0; c < 2; c++) {
                    int o = 0x10 * c;
                    float a = TanOut(B(v1, 0x11 + o) & 3, F(v0, 4 * c), F(v1, 4 * c), F(v2, 4 * c),
                                     F(v1, 0xc + o), d01, d12);
                    float b = TanIn(B(v2, 0x10 + o) & 3, F(v1, 4 * c), F(v2, 4 * c), F(v3, 4 * c),
                                    F(v2, 0x8 + o), d21, d23);
                    float r = ((F(v1, 4 * c) * h00 + F(v2, 4 * c) * h01) + b * h11) + a * h10;
                    float f = r;
                    if ((ch->flags & 0x20) == 0) {
                        f = Clamp01(r);
                    }
                    dst[c] = f;
                }
            }
        }
        out[0] = *(u32*)K1;
        out[1] = ((u32*)K1)[1];
        out[2] = ((u32*)K1)[2];
        out[3] = ((u32*)K1)[3];
        out[4] = ((u32*)K1)[4];
    }

    float f1 = (float)*(u32*)K1;
    if (time != f1) {
        float f2 = (float)*(u32*)K2;
        if (time != f2) {
            if (outIndex) {
                *outIndex = -1;
            }
            return false;
        }
        if (outIndex) {
            *outIndex = upper;
        }
        return true;
    }
    if (outIndex) {
        *outIndex = lower;
    }
    return true;
}
