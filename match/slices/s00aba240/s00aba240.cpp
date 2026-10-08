// s00aba240: 00aba3f0 -- per-frame update of a trail/ribbon of points (stub class "Trail").
// Points are kept in mPoints (newest first); a new point is inserted when the head has moved
// further than mParams->segmentLength from the newest stored point, otherwise only the
// per-point decay values fade. Optionally each point is displaced by a field object.
#include <xmmintrin.h>
#include <math.h>
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
};

extern const float kFltMax;   // 0x01565760 (FLT_MAX), loaded from memory
extern const float kEpsilon;  // 0x013f11c8 (1e-6f), loaded from memory

struct TrailParams {
    char pad0[8];
    uint32_t flags;           // +0x08: bit 6 = keep a second (colour) track, bit 9 = displace points
    char pad1[0xec - 0x0c];
    float segmentLength;      // +0xec
    char pad2[0x148 - 0xf0];
    float fieldStrength;      // +0x148
};

struct Vec3Vector {           // eastl::vector<Vec3>
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCap;
    void resize(unsigned n);                       // 00ab9f70
    void resize(unsigned n, const Vec3& v);        // 00ab9fe0
};

struct FloatVector {          // eastl::vector<float>
    float* mpBegin; float* mpEnd; float* mpCap;
    void resize(unsigned n);                       // 00aba330
    void resize(unsigned n, const float& v);       // 00aba390
};

struct IField {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual bool Query(Vec3* p);                   // +0x18
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual void Normal(Vec3* out, const Vec3* p); // +0x28
};

// max(0, x) as the original's asm helper (maxss with a memory operand)
static __forceinline float Max0(float x)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        movss x, xmm0
    }
    return x;
}

static inline bool Bit(uint32_t v, int n) { return ((v >> n) & 1) != 0; }

struct Trail {
    char pad0[0x12];
    bool mbFull;                    // +0x12
    char pad1[1];
    TrailParams* mParams;           // +0x14
    char pad2[0x38 - 0x18];
    int mMaxPoints;                 // +0x38
    char pad3[0x4c - 0x3c];
    Vec3 mMin;                      // +0x4c
    Vec3 mMax;                      // +0x58
    Vec3 mHead;                     // +0x64
    Vec3 mHead2;                    // +0x70
    char pad4[0xb4 - 0x7c];
    uint8_t mXformFlags;            // +0xb4
    char pad5[3];
    Vec3 mOffset;                   // +0xb8
    float mScale;                   // +0xc4
    float m[9];                     // +0xc8
    char padm[4];
    Vec3 mVelocity;                 // +0xf0
    char pad6[0x134 - 0xfc];
    Vec3Vector mPoints;             // +0x134
    char pad7[0x53c - 0x140];
    Vec3Vector mPoints2;            // +0x53c
    char pad8[0x56c - 0x548];
    float mDecayRate;               // +0x56c
    FloatVector mDecay;             // +0x570
    char pad9[0x6d8 - 0x57c];
    IField* mField;                 // +0x6d8
    char pad10[4];
    bool mbXform;                   // +0x6e0

    void Update(float dt);
};

void Trail::Update(float dt)
{
    uint32_t flags = mParams->flags;
    bool displace = Bit(flags, 9);
    Vec3Vector* pts = &mPoints;

    if (pts->mpBegin == pts->mpEnd) {
        mbFull = false;
        pts->resize(2, mHead);
        float one = 1.0f;
        mDecay.resize(2, one);
        mMin = mHead;
        mMax = mHead;
        mPoints2.resize(2, mHead2);
    } else {
        float d = mDecayRate * dt;
        double dx = (double)mHead.x - (double)pts->mpBegin->x;
        double dy = (double)mHead.y - (double)pts->mpBegin->y;
        double dz = (double)mHead.z - (double)pts->mpBegin->z;
        if (sqrt((dx * dx + dy * dy) + dz * dz) >= mParams->segmentLength) {
            float big = kFltMax;
            mMin = Vec3(big, big, big);
            big = -big;
            mMax = Vec3(big, big, big);
            int n = (int)(pts->mpEnd - pts->mpBegin);
            if (n <= mMaxPoints) {
                pts->resize(n + 1);
                mDecay.resize(n + 1);
                if (Bit(flags, 6))
                    mPoints2.resize(n + 1);
            } else {
                n--;
                mbFull = true;
            }
            for (int i = n; i > 0; i--) {
                Vec3* p = &pts->mpBegin[i - 1];
                if (p->x < mMin.x) mMin.x = p->x;
                if (p->x > mMax.x) mMax.x = p->x;
                if (p->y < mMin.y) mMin.y = p->y;
                if (p->y > mMax.y) mMax.y = p->y;
                if (p->z < mMin.z) mMin.z = p->z;
                if (p->z > mMax.z) mMax.z = p->z;
                pts->mpBegin[i] = pts->mpBegin[i - 1];
                mDecay.mpBegin[i] = Max0(mDecay.mpBegin[i - 1] - d);
                if (Bit(mParams->flags, 6))
                    mPoints2.mpBegin[i] = mPoints2.mpBegin[i - 1];
            }
            pts->mpBegin[0] = mHead;
            mPoints2.mpBegin[0] = mHead2;
            mDecay.mpBegin[0] = 1.0f;
        } else {
            int n = (int)(mDecay.mpEnd - mDecay.mpBegin);
            for (int i = 0; i < n; i++)
                mDecay.mpBegin[i] = Max0(mDecay.mpBegin[i] - d);
        }
    }

    if (displace) {
        int count = (int)(pts->mpEnd - pts->mpBegin);
        for (int i = 0; i < count; i++) {
            Vec3* p = &pts->mpBegin[i];
            Vec3 dv(mVelocity.x * dt, mVelocity.y * dt, mVelocity.z * dt);
            p->x = p->x + dv.x;
            p->y = p->y + dv.y;
            p->z = p->z + dv.z;
            if (mField) {
                Vec3 q;
                Vec3* pp = &pts->mpBegin[i];
                q.x = pp->x;
                q.y = pp->y;
                q.z = pp->z;
                if (mbXform) {
                    if (mXformFlags & 2)
                        q = Vec3((m[6] * q.z + m[3] * q.y) + m[0] * q.x,
                                 (m[7] * q.z + m[4] * q.y) + m[1] * q.x,
                                 (m[8] * q.z + m[5] * q.y) + m[2] * q.x);
                    q.x = mOffset.x + mScale * q.x;
                    q.y = mOffset.y + q.y * mScale;
                    q.z = mOffset.z + q.z * mScale;
                }
                if (mField->Query(&q)) {
                    Vec3 n;
                    mField->Normal(&n, &q);
                    if (mbXform) {
                        if (mScale != 1.0f) {
                            float inv = 1.0f / mScale;
                            n.x = n.x * inv;
                            n.y = n.y * inv;
                            n.z = n.z * inv;
                        }
                        if (mXformFlags & 2)
                            n = Vec3((m[2] * n.z + m[1] * n.y) + m[0] * n.x,
                                     (m[5] * n.z + m[4] * n.y) + n.x * m[3],
                                     (m[8] * n.z + m[7] * n.y) + n.x * m[6]);
                    }
                    float k = mParams->fieldStrength;
                    Vec3* r = &pts->mpBegin[i];
                    r->x = r->x + k * n.x;
                    r->y = k * n.y + r->y;
                    r->z = k * n.z + r->z;
                }
            }
        }
        int n = (int)(pts->mpEnd - pts->mpBegin);
        if (!mbFull) n--;
        if (n > 1) {
            for (int i = 1; i < n; i++) {
                Vec3* p = &pts->mpBegin[i];
                Vec3* q = p - 1;
                double ex = (double)p->x - (double)q->x;
                double ey = (double)p->y - (double)q->y;
                double ez = (double)p->z - (double)q->z;
                float s = (float)(mParams->segmentLength / (sqrt((ez * ez + ey * ey) + ex * ex) + kEpsilon));
                *p = Vec3(q->x + (p->x - q->x) * s, q->y + (p->y - q->y) * s, q->z + (p->z - q->z) * s);
            }
        }
        if (!mbFull) {
            Vec3* p = &pts->mpBegin[n];
            *p = *(p - 1);
        }
    }
}
