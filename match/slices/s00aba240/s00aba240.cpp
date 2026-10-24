// s00aba240: 00aba3f0 -- per-frame update of a trail/ribbon of points (stub class "Trail").
// Points are kept in mPoints (newest first); a new point is inserted when the head has moved
// further than mParams->segmentLength from the newest stored point, otherwise only the
// per-point decay values fade. Optionally each point is displaced by a field object.
#include <xmmintrin.h>
#include <math.h>
#include <string.h>
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
    uint32_t flags;           // +0x08: bit 6 = keep a second (colour) track, bit 9 = displace points,
                              //        bit 4 = animated progress, bit 8 = clamp instead of stop
    char pad1[0xec - 0x0c];
    float segmentLength;      // +0xec
    char pad2[0x120 - 0xf0];
    Vec3  mVec120;            // +0x120: velocity bias from the parameters
    float mScalar12c;         // +0x12c: direction scale
    float mScalar130;         // +0x130: speed scale
    char pad3[0x148 - 0x134];
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
    void Insert(float* pos, unsigned n, const float* v); // 00aba040
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

// ---------------------------------------------------------------------------
// The 00aba240/00ababd0 methods belong to the base subobject that sits 4 bytes
// into the Trail object (the call to Update passes ecx = this - 4).  Its field
// layout is the Trail layout shifted down by 4 bytes, plus the extra members
// that the update path touches.
// ---------------------------------------------------------------------------

struct Elem0C { float x, y, z; };

struct Vec0C {                 // eastl::vector<rw::math::fpu::Vector3Template<float,0>, sp_vector_allocator>
    Elem0C* mpBegin; Elem0C* mpEnd; Elem0C* mpCap;
    Elem0C* erase(Elem0C* first, Elem0C* last);   // 0x009e0480
};

struct TrailBaseVtbl {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(int);                        // +0x0c: stop/refresh notification
};

struct IField2 {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18();
    virtual void f1c(int index);                       // +0x1c
    virtual void f20(int index, Vec3* bounds, float v); // +0x20
    virtual void f24(int index, uint8_t b);             // +0x24
};

struct RefObj {
    virtual void r00();       // +0x00
    virtual void Release();   // +0x04
    virtual void r08();       // +0x08
    virtual void Destroy();   // +0x0c
};

struct Emit18 {               // object reached through TrailBase+0x18
    char pad0[0xbc];
    float mBC, mC0, mC4;      // +0xbc direction
    char pad2[0xd8 - 0xc8];
    float mD8, mDC, mE0;      // +0xd8 direction
    char pad3[0x120 - 0xe4];
    Vec3  mVec120;            // +0x120 offset
};

struct CardTarget30 {
    char pad[0x30];
    int mField30;             // +0x30
};

struct BoundsXform {          // this = six floats (min xyz, max xyz)
    float m[6];
    void Apply(void* xform);  // 0x006e95a0
};

struct TrailBase : TrailBaseVtbl {
    uint8_t pad04[8];         // +0x04 .. +0x0b
    uint8_t mbFlag0c;         // +0x0c
    uint8_t mByte0d;          // +0x0d
    uint8_t pad0e[2];         // +0x0e .. +0x0f
    TrailParams* mParams;     // +0x10
    IField2* mpField;         // +0x14
    Emit18* mpEmit;           // +0x18
    char pad1c[0x24 - 0x1c];
    float mTime;              // +0x24
    float mTimeMax;           // +0x28
    char pad2c[0x30 - 0x2c];
    float m30;                // +0x30
    int m34;                  // +0x34
    float m38;                // +0x38
    float m3c;                // +0x3c
    float m40;                // +0x40
    float m44;                // +0x44
    Vec3 mMin;                // +0x48
    Vec3 mMax;                // +0x54
    Vec3 mHead;               // +0x60
    char pad6c[0xb0 - 0x6c];
    uint8_t mXformFlags;      // +0xb0
    char padb1[3];
    Vec3 mOffset;             // +0xb4
    float mScale;             // +0xc0
    float mM[9];              // +0xc4
    char padE8[4];            // +0xe8 .. +0xeb
    Vec3 mVel;                // +0xec
    float mF8;                // +0xf8
    float mFC;                // +0xfc
    float m100, m104, m108, m10c, m110, m114;  // +0x100
    char pad118[0x124 - 0x118];
    int mIndex;               // +0x124
    char pad128[0x130 - 0x128];
    Vec0C mPoints;            // +0x130
    char pad13c[0x538 - 0x13c];
    Vec0C mPoints2;           // +0x538
    char pad544[0x568 - 0x544];
    float mDecayRate;         // +0x568
    FloatVector mDecay;       // +0x56c
    char pad578[0x6d4 - 0x578];
    RefObj* mpObj6d4;         // +0x6d4
    RefObj* mpObj6d8;         // +0x6d8

    void Cleanup();                               // 00aba240
    void UpdateEx(float dt, float t, void* p4);   // 00ababd0
};

// @ 0x00aba330
void FloatVector::resize(unsigned n)
{
    float* end = mpEnd;
    float* begin = mpBegin;
    unsigned count = (unsigned)(end - begin);
    if (n > count) {
        float zero = 0.0f;
        Insert(end, n - count, &zero);
        return;
    }
    float* first = begin + n;
    memcpy(first, end, (char*)mpEnd - (char*)end);
    mpEnd -= (end - first);
}

// @ 0x00aba240
void TrailBase::Cleanup()
{
    if (mbFlag0c)
        v0c(1);
    if (mIndex >= 0)
        mpField->f1c(mIndex);
    if (mpObj6d4) {
        mpObj6d4->Destroy();
        RefObj* p = mpObj6d4;
        if (p) {
            mpObj6d4 = 0;
            p->Release();
        }
    }
    if (mpObj6d8) {
        mpObj6d8->Destroy();
        RefObj* p = mpObj6d8;
        if (p) {
            mpObj6d8 = 0;
            p->Release();
        }
    }
    mPoints.erase(mPoints.mpBegin, mPoints.mpEnd);
    mPoints2.erase(mPoints2.mpBegin, mPoints2.mpEnd);
    {
        float* end = mDecay.mpEnd;
        float* begin = mDecay.mpBegin;
        memcpy(begin, end, (char*)mDecay.mpEnd - (char*)end);
        mDecay.mpEnd -= (end - begin);
    }
    mParams = 0;
    mpField = 0;
}

// @ 0x00ababd0
void TrailBase::UpdateEx(float dt, float t, void* p4)
{
    ((CardTarget30*)p4)->mField30 += m34;
    if (mIndex >= 0)
        mpField->f24(mIndex, mByte0d);

    mF8 = ((m104 - m100) * t + m100) * m110;
    mFC = ((m10c - m108) * t + m108) * m114;

    if (((mParams->flags >> 4) & 1) != 0) {
        if (mPoints.mpBegin == mPoints.mpEnd) {
            m38 = 0.0f;
        } else if (m40 != -999.0f) {
            m38 = m40 * dt + m38;
        } else {
            int count = (int)(mPoints.mpEnd - mPoints.mpBegin);
            float fc = (float)(unsigned)count;
            m38 = (dt * 30.0f) / fc + m38;
        }
        if (m38 >= 1.0f)
            m38 = (float)fmod((double)m38, 1.0);
    }

    m3c = m44 * dt + m3c;

    float s = mParams->mScalar130;
    Emit18* e = mpEmit;
    mVel.x = s * e->mD8;
    mVel.y = e->mDC * s;
    mVel.z = e->mE0 * s;
    float k = mParams->mScalar12c;
    mVel.x = k * e->mBC + mVel.x;
    mVel.y = mVel.y + e->mC0 * k;
    mVel.z = mVel.z + e->mC4 * k;

    if (mScale != 1.0f) {
        float inv = 1.0f / mScale;
        mVel.x = mVel.x * inv;
        mVel.y = inv * mVel.y;
        mVel.z = inv * mVel.z;
    }
    if (mXformFlags & 2) {
        float z = mVel.z, y = mVel.y, x = mVel.x;
        mVel.x = (mM[2] * z + mM[1] * y) + x * mM[0];
        mVel.y = (mM[5] * z + mM[4] * y) + x * mM[3];
        mVel.z = (mM[8] * z + mM[7] * y) + x * mM[6];
    }
    mVel.x += mParams->mVec120.x;
    mVel.y += mParams->mVec120.y;
    mVel.z += mParams->mVec120.z;

    mTime = mTime + dt;
    if (mTime > mTimeMax) {
        if (((mParams->flags >> 8) & 1) == 0)
            v0c(1);
        else
            mTime = mTimeMax;
    }

    if ((mParams->flags & 1) == 0) {
        ((Trail*)((char*)this - 4))->Update(dt);
        if (mMin.x > mHead.x) mMin.x = mHead.x;
        if (mHead.x > mMax.x) mMax.x = mHead.x;
        if (mMin.y > mHead.y) mMin.y = mHead.y;
        if (mHead.y > mMax.y) mMax.y = mHead.y;
        if (mMin.z > mHead.z) mMin.z = mHead.z;
        if (mHead.z > mMax.z) mMax.z = mHead.z;
    } else {
        int n = (int)(mDecay.mpEnd - mDecay.mpBegin);
        for (int i = 0; i < n; i++) {
            float v = mDecay.mpBegin[i] - mDecayRate * dt;
            mDecay.mpBegin[i] = Max0(v);
        }
    }

    float bounds[6];
    bounds[0] = mMin.x; bounds[1] = mMin.y; bounds[2] = mMin.z;
    bounds[3] = mMax.x; bounds[4] = mMax.y; bounds[5] = mMax.z;

    float v = m30 * mFC * 2.0f;
    ((BoundsXform*)bounds)->Apply((char*)this + 0xb0);
    mpField->f20(mIndex, (Vec3*)bounds, mScale * v);
}
