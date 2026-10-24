// EA::Swarm particle-to-vertex writer (0x00aaf700): for every live particle it samples the
// emitter's color / alpha / scale / rotation curves at age/lifetime, builds a cTransform,
// and writes a 3x4 scaled matrix plus an rgb+alpha record into the acquired vertex stream.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix3 {
    Vector3 row[3];
    Matrix3() {}
    Matrix3(const Matrix3& o) { row[0] = o.row[0]; row[1] = o.row[1]; row[2] = o.row[2]; }
};
struct RawMatrix3 { float f[9]; };

extern Matrix3 g_Identity3;       // 0x01679540
extern float g_RadiansScale;      // 0x0167952c

struct cTransform {               // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    void RotateZ(float angle);                         // 0x007d1ac0
    void PostTransformBy(const cTransform& parent);    // 0x00a8a140
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
    uint32_t pad0[34];
    FloatVec mScaleCurve;      // +0x88
    uint32_t pad94[9];
    FloatVec mSpinCurve;       // +0xb8
    uint32_t padc4[3];
    float mSpinBase;           // +0xd0
    Vec3Vec mColorCurve;       // +0xd4
    uint32_t padE0[5];
    FloatVec mAlphaCurve;      // +0xf4
    uint32_t pad100[13];
    uint8_t mOrientMode;       // +0x134
};

struct IVertexStream {
    virtual int Acquire(int count, char** ppBuf, int* pStride);  // +0
    virtual void Commit();                                       // +4
};

inline float EvalCurve(const FloatVec& v, uint32_t n, float t)
{
    if (n == 0)
        return v.mpBegin[0];
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
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
    float f = (float)n * t;
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f) {
        Vector3 d = v.mpBegin[i + 1] - v.mpBegin[i];
        return v.mpBegin[i] + d * frac;
    }
    return v.mpBegin[i];
}

struct cSwarmWriter {
    uint32_t pad0[5];
    Particle* mpHead;          // +0x14
    uint32_t pad18;
    int mRemaining;            // +0x1c
    EmitterInfo* mpInfo;       // +0x20
    uint32_t pad24[54];
    cTransform mWorld;         // +0xfc
    uint32_t pad134[3];
    uint16_t mFrame;           // +0x140
    uint16_t pad142;
    uint32_t pad144[20];
    float mSizeMul;            // +0x194
    float mAlphaMul;           // +0x198
    uint32_t pad19c;
    float mColorMul[3];        // +0x1a0
    uint32_t pad1ac[34];
    uint8_t mColorOffset;      // +0x234 (matrix record offset)
    uint8_t mAlphaOffset;      // +0x235
    void Write(IVertexStream* pStream);
};

// @ 0x00aaf700
void cSwarmWriter::Write(IVertexStream* pStream)
{
    EmitterInfo* info = mpInfo;
    Particle* p = mpHead;
    uint32_t nColor = (uint32_t)(info->mColorCurve.mpEnd - info->mColorCurve.mpBegin) - 1;
    uint32_t nScale = (uint32_t)(info->mScaleCurve.mpEnd - info->mScaleCurve.mpBegin) - 1;
    uint32_t nAlpha = (uint32_t)(info->mAlphaCurve.mpEnd - info->mAlphaCurve.mpBegin) - 1;
    uint32_t offMatrix = mColorOffset;
    uint32_t offColor = mAlphaOffset;
    int remaining = mRemaining;
    while (remaining > 0) {
        char* buf;
        int stride;
        int n = pStream->Acquire(remaining, &buf, &stride);
        remaining -= n;
        if (n > 0) {
            do {
                float t = p->mAge / p->mLifetime;
                cTransform xf;
                xf.mTranslation = p->mPos;
                Vector3 c = EvalColorCurve(mpInfo->mColorCurve, nColor, t);
                float cr = (mColorMul[0]) * (p->mColorMul[0] * c.x);
                float cg = (mColorMul[1] * c.y) * mColorMul[1];
                float cb = (mColorMul[2] * c.z) * mColorMul[2];
                float alpha = (p->mAlpha * mAlphaMul) * EvalCurve(mpInfo->mAlphaCurve, nAlpha, t);
                float scale = EvalCurve(mpInfo->mScaleCurve, nScale, t);
                xf.mRotation = Matrix3(g_Identity3);
                xf.mModificationCount = 2;
                xf.mFlags = 4;
                scale = (p->mSize * mSizeMul) * scale;
                xf.mScale = scale;
                uint8_t mode = mpInfo->mOrientMode;
                if (mode >= 2 && mode <= 4) {
                    Vector3 dir;
                    dir.x = p->mDir.x;
                    dir.y = p->mDir.y;
                    dir.z = p->mDir.z;
                    Matrix3 m(g_Identity3);
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
                float* d = (float*)(buf + offMatrix);
                float s = xf.mScale;
                float m0 = xf.mRotation.row[0].x * s;
                float m1 = xf.mRotation.row[0].y * s;
                d[0] = m0;
                float m2 = xf.mRotation.row[0].z * s;
                d[1] = m1;
                d[2] = m2;
                float m3 = xf.mRotation.row[1].x * s;
                d[4] = m3;
                float m4 = xf.mRotation.row[1].y * s;
                d[5] = m4;
                float m5 = xf.mRotation.row[1].z * s;
                d[6] = m5;
                float m6 = xf.mRotation.row[2].x * s;
                d[8] = m6;
                float m7 = xf.mRotation.row[2].y * s;
                d[9] = m7;
                float m8 = xf.mRotation.row[2].z * s;
                d[10] = m8;
                d[12] = xf.mTranslation.x;
                d[13] = xf.mTranslation.y;
                d[14] = xf.mTranslation.z;
                float* e = (float*)(buf + offColor);
                e[0] = cr;
                e[1] = cg;
                e[2] = cb;
                e[3] = alpha;
                buf += stride;
                p = p->mpNext;
            } while (--n != 0);
        }
        pStream->Commit();
    }
    ++mFrame;
}

// Slice s00aaf700: EA::Swarm particle-effect opcode/parameter setter.
// this = effect component view (the complete effect object is this - 8, so every
// particle helper below receives ecx = this-8).  Layout comments are this-relative.
// Built /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

struct SwarmVec3
{
    float x, y, z;
};

// 0x38-byte rigid transform (0x007D5590 multiplies two of these).
struct SwarmXform
{
    u16 mFlags;                                             // +0x00
    u16 mModificationCount;                                 // +0x02
    SwarmVec3 mTranslation;                                   // +0x04
    float mScale;                                           // +0x10
    float mRotation[9];                                     // +0x14
    void __thiscall InverseTransformPoint(SwarmVec3& v) const;   // 0x007CDA70
};

// Intrusive particle node.  A node's mppPrev points at the previous node's
// mpNext slot (the list head slot for the first node).
struct cParticle
{
    cParticle* mpNext;                                      // +0x00
    cParticle** mppPrev;                                    // +0x04
    u32 mPad08[2];                                          // +0x08
    SwarmVec3 mField10;                                       // +0x10
    u32 mPad1C[7];                                          // +0x1C
    SwarmVec3 mField38;                                       // +0x38
};

struct cParticleList
{
    cParticle* mpHead;                                      // +0x00
    cParticle* mpTail;                                      // +0x04
    cParticle** __thiscall Remove(cParticle** out, cParticle* node);   // 0x00AA8EA0
};

struct cParticlesDescription
{
    u32 mPad00[2];                                          // +0x00
    i32 mField08;                                           // +0x08
    u8  mPad0C[0x44 - 0x0C];                                // +0x0C
    float mField44;                                         // +0x44
    u8  mPad48[0x131 - 0x48];                               // +0x48
    u8  mByte131;                                           // +0x131
};

struct cParticleStream;

struct cIEffectsWorld
{
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0C() = 0;
    virtual void v10() = 0;
    virtual void v14() = 0;
    virtual void v18() = 0;
    virtual void v1C() = 0;
    virtual cParticleStream* GetStream() = 0;               // +0x20
};

struct cParticleStream
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

// Particle helpers are members of the complete effect object (this - 8).
struct cParticlesEffectCore
{
    cParticle* AllocParticle();                             // 0x00AAF630
    bool InitParticle(cParticle* p);                        // 0x00AAEB90
    void F58620(cParticle* p);                              // 0x00F58620
    void DestroyParticle(cParticle* p);                     // 0x00AAF670
    void SetPath(const float* data);                        // 0x00AA89D0
};

float __cdecl Dot3(const SwarmVec3* a, const SwarmVec3* b);                     // 0x0053C480
SwarmXform* __cdecl MultiplyTransforms(SwarmXform* out, const SwarmXform* a, const SwarmXform* b);  // 0x007D5590
void __cdecl BuildPath(int count, const SwarmVec3* data, float speed, const void* opts, void* samples);   // 0x00A7AB40

struct cParticlesEffectView
{
    u32 mPad00[4];                                          // +0x00
    cParticleList mParticles;                               // +0x10
    i32 mParticleCount;                                     // +0x18
    cParticlesDescription* mDesc;                           // +0x1C
    u32 mPad20;                                             // +0x20
    cIEffectsWorld* mWorld;                                 // +0x24
    u32 mPad28[(0x84 - 0x28) / 4];                          // +0x28
    SwarmVec3 mField84;                                       // +0x84
    float mField90;                                         // +0x90
    u32 mPad94[(0xB4 - 0x94) / 4];                          // +0x94
    SwarmVec3 mFieldB4;                                       // +0xB4
    SwarmXform mXform0;                                     // +0xC0
    SwarmXform mXform1;                                     // +0xF8
    u32 mPad130[(0x140 - 0x130) / 4];                       // +0x130
    float mField140;                                        // +0x140
    float mField144;                                        // +0x144
    float mField148;                                        // +0x148
    float mField14C;                                        // +0x14C
    float mField150;                                        // +0x150
    float mField154;                                        // +0x154
    float mField158;                                        // +0x158
    float mField15C;                                        // +0x15C
    float mField160;                                        // +0x160
    float mField164;                                        // +0x164
    float mField168;                                        // +0x168
    SwarmVec3 mField16C;                                      // +0x16C
    float mField178;                                        // +0x178
    u32 mPad17C;                                            // +0x17C
    float mField180;                                        // +0x180
    float mField184;                                        // +0x184
    u32 mPad188[(0x1D8 - 0x188) / 4];                       // +0x188
    const float* mField1D8;                                 // +0x1D8
    u32 mPad1DC[(0x20C - 0x1DC) / 4];                       // +0x1DC
    u8 mSamples[0x1C];                                      // +0x20C (cSampleVec)
    i32 mField228;                                          // +0x228
    i32 mField22C;                                          // +0x22C

    bool SetParameter(int opcode, const float* data, int count);
};

// @ 0x00AAFFD0
bool __thiscall cParticlesEffectView::SetParameter(int opcode, const float* data, int count)
{
    switch (opcode)
    {
    case 0:
        mField158 = data[0];
        return true;
    case 1:
        if (count == 1)
            mField164 = data[0];
        return true;
    case 2:
        mField160 = data[0];
        return true;
    case 3:
        mField15C = data[0];
        return true;
    case 4:
        mField168 = data[0];
        return true;
    case 0x12:
        mField178 = data[0];
        return true;
    case 5:
    {
        SwarmVec3 v;
        v.x = data[0];
        v.y = data[1];
        v.z = data[2];
        mField16C = v;
        return true;
    }
    case 6:
    {
        const int target = count / 3;
        cParticlesEffectCore* core = (cParticlesEffectCore*)((char*)this - 8);

        while (mParticleCount < target)
        {
            cParticle* p = core->AllocParticle();
            if (core->InitParticle(p))
                core->F58620(p);
        }

        cParticle* p = mParticles.mpHead;
        while (mParticleCount > target)
        {
            cParticle* next = p->mpNext;
            *p->mppPrev = next;
            next->mppPrev = p->mppPrev;
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
            p->mField38 = *(const SwarmVec3*)d;
            d += 3;
            p = p->mpNext;
        }
        return true;
    }
    case 0x10:
        if (count != 2)
        {
            int v = (int)data[2];
            if (v != (int)mDesc->mByte131)
                return false;
        }
        mField180 = data[0];
        mField184 = data[1];
        return true;
    case 7:
        mField1D8 = data;
        ((cParticlesEffectCore*)((char*)this - 8))->SetPath(data);
        return true;
    case 9:
        mField84 = *(const SwarmVec3*)data;
        return true;
    case 0xA:
        mField90 = data[0];
        return true;
    case 0xB:
    {
        const float z0 = data[2];
        const SwarmVec3* dir = (const SwarmVec3*)(data + 3);
        SwarmVec3 v;
        v.x = mFieldB4.x - data[0];
        v.y = mFieldB4.y - data[1];
        v.z = mFieldB4.z - z0;
        float num = dir->x * v.x + dir->y * v.y + dir->z * v.z;
        float scale = num / Dot3(dir, dir);
        v.x = data[0] + dir->x * scale;
        v.y = data[1] + dir->y * scale;
        v.z = z0 + dir->z * scale;
        mField84 = v;
        mField90 = (scale <= 0.0f) ? 1.0f : 0.0f;
        mXform1.InverseTransformPoint(mField84);
        return true;
    }
    case 0xE:
        if (mField22C >= 0)
        {
            cParticleStream* stream = mWorld->GetStream();
            return stream->v74(0, mField22C, 0, count, data);
        }
        if (mField228 >= 0)
        {
            cParticleStream* stream = mWorld->GetStream();
            return stream->v74(1, mField228, 0, count, data);
        }
        return false;
    case 0xD:
    {
        const int target = count / 3;
        if (mDesc->mField08 < 0)
        {
            SwarmXform xf;
            BuildPath(target, (const SwarmVec3*)data, mDesc->mField44,
                      MultiplyTransforms(&xf, &mXform0, &mXform1), mSamples);
            return true;
        }

        cParticlesEffectCore* core = (cParticlesEffectCore*)((char*)this - 8);
        while (mParticleCount < target)
        {
            cParticle* p = core->AllocParticle();
            if (core->InitParticle(p))
                core->F58620(p);
        }

        cParticle* p = mParticles.mpHead;
        while (mParticleCount > target)
        {
            cParticle* next;
            mParticles.Remove(&next, p);
            --mParticleCount;
            core->DestroyParticle(p);
            p = next;
        }

        p = mParticles.mpHead;
        const float* d = data;
        for (int i = 0; i < target; ++i)
        {
            p->mField10 = *(const SwarmVec3*)d;
            d += 3;
            p = p->mpNext;
        }
        return true;
    }
    case 0x101:
        mField140 = data[0];
        mField148 = data[1];
        mField150 = data[2];
        mField144 = data[3];
        mField14C = data[4];
        mField154 = data[5];
        return true;
    default:
        return false;
    }
}
