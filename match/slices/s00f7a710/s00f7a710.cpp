// EA::Swarm particle-to-vertex writer (0x00f7a710), older cParticlesEffect copy of 0x00aaf700: for every live particle it samples the
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
struct OutRow { Vector3 v; float w; };

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

struct cSwarmWriterA {
    uint32_t pad0[5];
    Particle* mpHead;          // +0x14
    uint32_t pad18;
    int mRemaining;            // +0x1c
    EmitterInfo* mpInfo;       // +0x20
    uint32_t pad24[48];
    cTransform mWorld;         // +0xe4
    uint32_t pad11c[3];
    uint16_t mFrame;           // +0x128
    uint16_t pad12a;
    uint32_t pad12c[19];
    float mSizeMul;            // +0x178
    float mAlphaMul;           // +0x17c
    uint32_t pad180;
    float mColorMul[3];        // +0x184
    uint32_t pad190[37];
    uint8_t mColorOffset;      // +0x224 (matrix record offset)
    uint8_t mAlphaOffset;      // +0x225
    void Write(IVertexStream* pStream);
};

// @ 0x00f7a710
void cSwarmWriterA::Write(IVertexStream* pStream)
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
