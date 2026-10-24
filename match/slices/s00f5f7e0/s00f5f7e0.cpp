// EA::Swarm particle-to-vertex writer (0x00f5f7e0), another cParticlesEffect copy of 0x00aaf700 / 0x00f7a710 (different member offsets): for every live particle it samples the
// emitter's color / alpha / scale / rotation curves at age/lifetime, builds a cTransform,
// and writes a 3x4 scaled matrix plus an rgb+alpha record into the acquired vertex stream.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix3 {
    Vector3 row[3];
    Matrix3() {}
    Matrix3(const Matrix3& o) { row[0] = o.row[0]; row[1] = o.row[1]; row[2] = o.row[2]; }
};
struct RawMatrix3 { float f[9]; };
struct OutRow { Vector3 v; float w; };

extern Matrix3 g_Identity3;       // 0x016c9440
extern float g_RadiansScale;      // 0x016c949c

struct cTransform {               // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    void RotateZ(float angle);                         // 0x007d1ac0
    void PostTransformBy(const cTransform& parent);    // 0x00a8a140
    void InverseTransformPoint(Vector3& v) const;      // 0x007cda70
};

void __cdecl BuildBasisMode2(const Vector3* dir, Matrix3* out);   // 0x00a81a20
void __cdecl BuildBasisMode3(const Vector3* dir, Matrix3* out);   // 0x00a818f0
void __cdecl BuildBasisMode4(const Vector3* dir, Matrix3* out);   // 0x00a81b80

struct FloatVec { float* mpBegin; float* mpEnd; float* mpCap; };
struct Vec3Vec { Vector3* mpBegin; Vector3* mpEnd; Vector3* mpCap; };

struct Particle {
    Particle* mpNext;      // +0x00
    uint32_t pad04;
    float mAge;            // +0x08
    float mLifetime;       // +0x0c
    Vector3 mPos;          // +0x10
    Vector3 mDir;          // +0x1c
    float mSize;           // +0x28
    uint32_t pad2c;
    float mSpin;           // +0x30
    float mAlpha;          // +0x34
    float mColorMul[3];    // +0x38
};

struct EmitterInfo {
    uint32_t pad0[33];
    FloatVec mScaleCurve;      // +0x84
    uint32_t pad90[9];
    FloatVec mSpinCurve;       // +0xb4
    uint32_t padc0[3];
    float mSpinBase;           // +0xcc
    Vec3Vec mColorCurve;       // +0xd0
    uint32_t paddc[5];
    FloatVec mAlphaCurve;      // +0xf0
    uint32_t padfc[12];
    uint8_t mOrientMode;       // +0x12c
};

struct IVertexStream {
    virtual int Acquire(int count, char** ppBuf, int* pStride);  // +0
    virtual void Commit();                                       // +4
};

inline float EvalCurve(const FloatVec& v, uint32_t n, float t)
{
    if (n == 0)
        return v.mpBegin[0];
    int i = (int)((float)n * t);
    float frac = (float)n * t - (float)i;
    if (frac > 0.0f) {
        float a = v.mpBegin[i];
        return (v.mpBegin[i + 1] - a) * frac + a;
    }
    return v.mpBegin[i];
}

inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}
inline Vector3 operator*(const Vector3& a, float s)
{
    Vector3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r;
}
inline Vector3 operator+(const Vector3& a, const Vector3& b)
{
    Vector3 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r;
}

inline Vector3 EvalColorCurve(const Vec3Vec& v, uint32_t n, float t)
{
    if (n == 0)
        return v.mpBegin[0];
    int i = (int)((float)n * t);
    float frac = (float)n * t - (float)i;
    if (frac > 0.0f) {
        Vector3 d = v.mpBegin[i + 1] - v.mpBegin[i];
        return v.mpBegin[i] + d * frac;
    }
    return v.mpBegin[i];
}

struct cSwarmWriterB {
    uint32_t pad0[5];
    Particle* mpHead;          // +0x14
    uint32_t pad18;
    int mRemaining;            // +0x1c
    EmitterInfo* mpInfo;       // +0x20
    uint32_t pad24[56];
    cTransform mWorld;         // +0x104
    uint32_t pad13c[3];
    uint16_t mFrame;           // +0x148
    uint16_t pad14a;
    uint32_t pad14c[19];
    float mSizeMul;            // +0x198
    float mAlphaMul;           // +0x19c
    uint32_t pad1a0;
    float mColorMul[3];        // +0x1a4
    uint32_t pad1b0[35];
    uint8_t mColorOffset;      // +0x23c (matrix record offset)
    uint8_t mAlphaOffset;      // +0x23d
    void Write(IVertexStream* pStream);
};

// @ 0x00f5f7e0
void cSwarmWriterB::Write(IVertexStream* pStream)
{
    EmitterInfo* info = mpInfo;
    Particle* p = mpHead;
    uint32_t nColor = (uint32_t)(info->mColorCurve.mpEnd - info->mColorCurve.mpBegin) - 1;
    uint32_t offColor = mAlphaOffset;
    uint32_t nScale = (uint32_t)(info->mScaleCurve.mpEnd - info->mScaleCurve.mpBegin) - 1;
    uint32_t offMatrix = mColorOffset;
    int remaining = mRemaining;
    uint32_t nAlpha = (uint32_t)(info->mAlphaCurve.mpEnd - info->mAlphaCurve.mpBegin) - 1;
    char* buf;
    int stride;
    while (remaining > 0) {
        int n = pStream->Acquire(remaining, &buf, &stride);
        remaining -= n;
        if (n > 0) {
            do {
                float t = p->mAge / p->mLifetime;
                cTransform xf;
                xf.mTranslation = Vector3(p->mPos);
                Vector3 c = EvalColorCurve(mpInfo->mColorCurve, nColor, t);
                Vector3 col;
                col.x = mColorMul[0] * (p->mColorMul[0] * c.x);
                col.y = (p->mColorMul[1] * c.y) * mColorMul[1];
                col.z = (p->mColorMul[2] * c.z) * mColorMul[2];
                float alpha = (p->mAlpha * mAlphaMul) * EvalCurve(mpInfo->mAlphaCurve, nAlpha, t);
                float scale = EvalCurve(mpInfo->mScaleCurve, nScale, t);
                xf.mRotation.row[0] = Vector3(g_Identity3.row[0]);
                xf.mRotation.row[1] = Vector3(g_Identity3.row[1]);
                xf.mRotation.row[2] = Vector3(g_Identity3.row[2]);
                xf.mModificationCount = 2;
                xf.mFlags = 4;
                scale = (p->mSize * mSizeMul) * scale;
                xf.mScale = scale;
                uint8_t mode = mpInfo->mOrientMode;
                if (mode >= 2 && mode <= 4) {
                    Vector3 dir(p->mDir);
                    Matrix3 m;
                    m.row[0] = Vector3(g_Identity3.row[0]);
                    m.row[1] = Vector3(g_Identity3.row[1]);
                    m.row[2] = Vector3(g_Identity3.row[2]);
                    float len = (float)sqrt((dir.z * dir.z + dir.y * dir.y) + dir.x * dir.x);
                    if (0.0f < len) {
                        float inv = 1.0f / len;
                        dir.x = inv * dir.x;
                        dir.y = dir.y * inv;
                        dir.z = dir.z * inv;
                    }
                    switch (mpInfo->mOrientMode) {
                    case 2: BuildBasisMode2(&dir, &m); break;
                    case 3: BuildBasisMode3(&dir, &m); break;
                    case 4: BuildBasisMode4(&dir, &m); break;
                    }
                    *(RawMatrix3*)&xf.mRotation = *(RawMatrix3*)&m;
                    xf.mFlags = 6;
                    xf.mModificationCount = 3;
                }
                float rot = EvalCurve(mpInfo->mSpinCurve,
                                      (uint32_t)(mpInfo->mSpinCurve.mpEnd - mpInfo->mSpinCurve.mpBegin) - 1, t);
                xf.RotateZ((p->mSpin * rot + mpInfo->mSpinBase) * g_RadiansScale);
                xf.PostTransformBy(mWorld);
                float s = xf.mScale;
                OutRow* d = (OutRow*)(buf + offMatrix);
                d[0].v = xf.mRotation.row[0] * s;
                d[1].v = xf.mRotation.row[1] * s;
                d[2].v = xf.mRotation.row[2] * s;
                d[3].v = xf.mTranslation;
                OutRow* e = (OutRow*)(buf + offColor);
                e->v = col;
                e->w = alpha;
                buf += stride;
                p = p->mpNext;
            } while (--n != 0);
        }
        pStream->Commit();
    }
    ++mFrame;
}

// ---------------------------------------------------------------------------
// 0x00f600a0: particle-effect opcode / parameter setter (sibling of the
// 0x00aaffd0 setter in slice s00aaf700, shifted member offsets).
// this is the effect component view; the complete effect object starts 8 bytes
// before it, so every particle helper below receives ecx = this - 8.
// Layout comments are this-relative.

struct cSwarmParticle
{
    cSwarmParticle* mpNext;        // +0x00
    cSwarmParticle** mppPrev;      // +0x04
    uint32_t mPad08[2];            // +0x08
    Vector3 mField10;              // +0x10
    uint32_t mPad1C[7];            // +0x1C
    Vector3 mField38;              // +0x38
};

struct cSwarmParticleList
{
    cSwarmParticle* mpHead;        // +0x00
    cSwarmParticle* mpTail;        // +0x04
    cSwarmParticle** Remove(cSwarmParticle** out, cSwarmParticle* node);   // 0x00aa8ea0
};

struct cSwarmInfo
{
    uint32_t mPad00[2];            // +0x00
    int32_t  mField08;             // +0x08
    uint8_t  mPad0C[0x40 - 0x0C];  // +0x0C
    float    mField40;             // +0x40
    uint8_t  mPad44[0x129 - 0x44]; // +0x44
    uint8_t  mByte129;             // +0x129
};

struct cSwarmStream
{
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0C() = 0;
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1C() = 0;
    virtual void v20() = 0;
    virtual void v24() = 0;
    virtual void v28() = 0;
    virtual void v2C() = 0;
    virtual void v30() = 0;
    virtual void v34() = 0;
    virtual void v38() = 0;
    virtual void v3C() = 0;
    virtual void v40() = 0;
    virtual void v44() = 0;
    virtual void v48() = 0;
    virtual void v4C() = 0;
    virtual void v50() = 0;
    virtual void v54() = 0;
    virtual void v58() = 0;
    virtual void v5C() = 0;
    virtual void v60() = 0;
    virtual void v64() = 0;
    virtual void v68() = 0;
    virtual void v6C() = 0;
    virtual void v70() = 0;
    virtual bool v74(int mode, int id, int zero, int count, const float* data) = 0;   // +0x74
};

struct cSwarmWorld
{
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0C() = 0;
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1C() = 0;
    virtual cSwarmStream* GetStream() = 0;                    // +0x20
};

// Particle helpers are members of the complete effect object (this - 8).
struct cSwarmEffectCore
{
    cSwarmParticle* AllocParticle();                          // 0x00f5a1c0
    bool InitParticle(cSwarmParticle* p);                     // 0x00f5ebf0
    void F58620(cSwarmParticle* p);                           // 0x00f58620
    void DestroyParticle(cSwarmParticle* p);                  // 0x00f5f770
    void SetPath(const float* data);                          // 0x00f58b70
};

cTransform* __cdecl MultiplySwarmTransforms(cTransform* out, const cTransform* a, const cTransform* b);   // 0x007d5590
void __cdecl BuildSwarmPath(int count, const Vector3* data, float speed, const void* opts, void* samples); // 0x00a7ab40

struct cSwarmParamView
{
    uint32_t mPad00[4];                                       // +0x00
    cSwarmParticleList mParticles;                            // +0x10
    int32_t mParticleCount;                                   // +0x18
    cSwarmInfo* mDesc;                                        // +0x1C
    uint32_t mPad20;                                          // +0x20
    uint32_t mPad24;                                          // +0x24
    cSwarmWorld* mWorld;                                      // +0x28
    uint32_t mPad2C[(0x8C - 0x2C) / 4];                       // +0x2C
    Vector3 mField8C;                                         // +0x8C
    float mField98;                                           // +0x98
    uint32_t mPad9C[(0xBC - 0x9C) / 4];                       // +0x9C
    Vector3 mFieldBC;                                         // +0xBC
    cTransform mXform0;                                       // +0xC8
    cTransform mXform1;                                       // +0x100
    uint32_t mPad138[(0x148 - 0x138) / 4];                    // +0x138
    float mField148;                                          // +0x148
    float mField14C;                                          // +0x14C
    float mField150;                                          // +0x150
    float mField154;                                          // +0x154
    float mField158;                                          // +0x158
    float mField15C;                                          // +0x15C
    float mField160;                                          // +0x160
    float mField164;                                          // +0x164
    float mField168;                                          // +0x168
    float mField16C;                                          // +0x16C
    float mField170;                                          // +0x170
    Vector3 mField174;                                        // +0x174
    float mField180;                                          // +0x180
    float mField184;                                          // +0x184
    float mField188;                                          // +0x188
    uint32_t mPad18C[(0x1A0 - 0x18C) / 4];                    // +0x18C
    Vector3 mField1A0;                                        // +0x1A0
    uint32_t mPad1AC[(0x1E0 - 0x1AC) / 4];                    // +0x1AC
    const float* mField1E0;                                   // +0x1E0
    uint32_t mPad1E4[(0x214 - 0x1E4) / 4];                    // +0x1E4
    uint8_t mSamples[0x1C];                                   // +0x214
    int32_t mField230;                                        // +0x230
    int32_t mField234;                                        // +0x234

    bool SetParameter(int opcode, const float* data, int count);
};

// @ 0x00f600a0
bool cSwarmParamView::SetParameter(int opcode, const float* data, int count)
{
    switch (opcode)
    {
    case 0:
        mField160 = data[0];
        return true;
    case 1:
        mField168 = data[0];
        return true;
    case 3:
        mField164 = data[0];
        return true;
    case 4:
        mField16C = data[0];
        return true;
    case 0x12:
        mField170 = data[0];
        return true;
    case 5:
    {
        Vector3 v(data[0], data[1], data[2]);
        mField174 = v;
        mField1A0 = v;
        return true;
    }
    case 6:
    {
        cSwarmEffectCore* core = (cSwarmEffectCore*)((char*)this - 8);
        const int target = count / 3;

        while (mParticleCount < target)
        {
            cSwarmParticle* p = core->AllocParticle();
            if (core->InitParticle(p))
                core->F58620(p);
        }

        cSwarmParticle* p = mParticles.mpHead;
        while (mParticleCount > target)
        {
            cSwarmParticle** pp = p->mppPrev;
            cSwarmParticle* next = p->mpNext;
            *pp = next;
            next->mppPrev = pp;
            p->mpNext = 0;
            p->mppPrev = 0;
            --mParticleCount;
            core->DestroyParticle(p);
            p = next;
        }

        p = mParticles.mpHead;
        const float* d = data;
        for (int i = 0; i < target; ++i)
        {
            p->mField38 = *(const Vector3*)d;
            d += 3;
            p = p->mpNext;
        }
        return true;
    }
    case 0x10:
        if (count != 2)
        {
            int v = (int)data[2];
            if (v != (int)mDesc->mByte129)
                return false;
        }
        mField184 = data[0];
        mField188 = data[1];
        return true;
    case 7:
        mField1E0 = data;
        ((cSwarmEffectCore*)((char*)this - 8))->SetPath(data);
        return true;
    case 9:
        mField8C = *(const Vector3*)data;
        return true;
    case 0xA:
        mField98 = data[0];
        return true;
    case 0xB:
    {
        const float z0 = data[2];
        const Vector3* dir = (const Vector3*)(data + 3);
        Vector3 v;
        v.x = mFieldBC.x - data[0];
        v.y = mFieldBC.y - data[1];
        v.z = mFieldBC.z - z0;
        float num = dir->x * v.x + dir->y * v.y + dir->z * v.z;
        float scale = num / (dir->x * dir->x + dir->y * dir->y + dir->z * dir->z);
        v.x = data[0] + dir->x * scale;
        v.y = data[1] + dir->y * scale;
        v.z = z0 + dir->z * scale;
        mField8C = v;
        mField98 = (float)(scale >= 0.0f);
        mXform1.InverseTransformPoint(mField8C);
        return true;
    }
    case 0xE:
        if (mField234 >= 0)
        {
            cSwarmStream* stream = mWorld->GetStream();
            return stream->v74(0, mField234, 0, count, data);
        }
        if (mField230 >= 0)
        {
            cSwarmStream* stream = mWorld->GetStream();
            return stream->v74(1, mField230, 0, count, data);
        }
        return false;
    case 0xD:
    {
        const int target = count / 3;
        if (mDesc->mField08 < 0)
        {
            cTransform xf;
            BuildSwarmPath(target, (const Vector3*)data, mDesc->mField40,
                           MultiplySwarmTransforms(&xf, &mXform0, &mXform1), mSamples);
            return true;
        }

        cSwarmEffectCore* core = (cSwarmEffectCore*)((char*)this - 8);
        while (mParticleCount < target)
        {
            cSwarmParticle* p = core->AllocParticle();
            if (core->InitParticle(p))
                core->F58620(p);
        }

        cSwarmParticle* p = mParticles.mpHead;
        while (mParticleCount > target)
        {
            cSwarmParticle* next;
            mParticles.Remove(&next, p);
            --mParticleCount;
            core->DestroyParticle(p);
            p = next;
        }

        p = mParticles.mpHead;
        const float* d = data;
        for (int i = 0; i < target; ++i)
        {
            p->mField10 = *(const Vector3*)d;
            d += 3;
            p = p->mpNext;
        }
        return true;
    }
    case 0x101:
        mField148 = data[0];
        mField150 = data[1];
        mField158 = data[2];
        mField14C = data[3];
        mField154 = data[4];
        mField15C = data[5];
        return true;
    default:
        return false;
    }
}
