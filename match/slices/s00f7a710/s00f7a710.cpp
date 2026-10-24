// EA::Swarm particle-to-vertex writer (0x00f7a710), older cParticlesEffect copy of 0x00aaf700: for every live particle it samples the
// emitter's color / alpha / scale / rotation curves at age/lifetime, builds a cTransform,
// and writes a 3x4 scaled matrix plus an rgb+alpha record into the acquired vertex stream.
#include "types.h"
#include <math.h>
#include <intrin.h>

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

// ---------------------------------------------------------------------------------------------------
// EA::Swarm::cParticlesEffect construction / destruction (retail layout, size 0x238).
// Retail offsets differ from the 2008 dev PDB, so the layout below was derived from the two
// functions themselves.  The four vtable pointers at +0..+0xc are stored as plain data because the
// object is only used through those addresses; calls that the original makes into other modules are
// issued through their literal retail addresses so no unresolved symbol is left in the object.

struct F1 { float f; };
extern F1 g16c9b28, g16c9b2c, g16c9b30;          // 0x016c9b28 / 2c / 30  (zero-initialised .data)
extern F1 g16c9b78, g16c9b7c;                    // 0x016c9b78 / 7c
extern F1 g16c9b80, g16c9b84, g16c9b88;          // 0x016c9b80 / 84 / 88
extern F1 g1485720;                              // 0x01485720  (1.0f)
extern F1 g1418f90;                              // 0x01418f90  (-10000.0f)
extern F1 g13f0620;                              // 0x013f0620  (+10000.0f)
extern double g1454410;                          // 0x01454410  (-1.0)

void operator delete(void* p);                   // 0x00f47380
struct Matrix33Ctor {
    void Assign(const void* pSrc);                           // 0x0041cb40
};
struct IntrusiveListBase {
    void Destroy();                                          // 0x00620230
};

struct F218Object {
    uint32_t mPad0;            // +0x00
    uint32_t mPad4;            // +0x04
    void*    mpVtable;         // +0x08
};

struct HeapBlock {
    int32_t  mRefCount;        // allocation header immediately before the payload
};

struct RefVertex;

struct SpVectorRefVertex {     // EA::Swarm::SpVector<EA::Swarm::RefVertex>, size 0x14
    RefVertex* mpBegin;        // +0x00
    RefVertex* mpEnd;          // +0x04
    RefVertex* mpCapacity;     // +0x08
    void*      mpAllocName;    // +0x0c
    uint32_t   mAllocFlags;    // +0x10
    void Destroy();            // 0x00a8c440
};

struct cParticlesEffect {       // size 0x238
    void*    mpVtbl0;                       // +0x000
    volatile void* mpVtbl1;                 // +0x004
    volatile void* mpVtbl2;                 // +0x008
    volatile void* mpVtbl3;                 // +0x00c
    int32_t  mF10;                          // +0x010
    bool     mStarted;                      // +0x014
    bool     mDelayedStopActive;            // +0x015
    bool     mIsVisible;                    // +0x016
    bool     mF17;                          // +0x017
    void*    mpParticlesHead;               // +0x018
    void*    mpParticlesAnchor;             // +0x01c
    int32_t  mParticleCount;                // +0x020
    void*    mpDesc;                        // +0x024
    uint32_t mCollectionIndex;              // +0x028
    void*    mpWorld;                       // +0x02c
    void*    mpGlobalParams;                // +0x030
    uint32_t mF34;                          // +0x034
    double   mOverallTime;                  // +0x038
    bool     mPreroll;                      // +0x040
    char     mPad41[7];                     // +0x041
    double   mParticleSystemTime;           // +0x048
    int32_t  mCurrentCycle;                 // +0x050
    uint32_t mF54;                          // +0x054
    double   mInverseRateCurveTime;         // +0x058
    float    mParticlesToGenerate;          // +0x060
    float    mDirectionalForcesSum[3];      // +0x064
    float    mRandomWalkNextTime;           // +0x070
    float    mRandomWalkStrengthV;          // +0x074
    float    mRandomWalkStrengthH;          // +0x078
    float    mRandomWalkTheta;              // +0x07c
    float    mF80;                          // +0x080
    float    mF84;                          // +0x084
    float    mAttractorForce;               // +0x088
    float    mAttractorLocation[3];         // +0x08c
    float    mAttractorIntensity;           // +0x098
    float    mRetriggerTime;                // +0x09c
    float    mF0a0;                         // +0x0a0
    float    mF0a4;                         // +0x0a4
    float    mF0a8;                         // +0x0a8
    float    mF0ac;                         // +0x0ac
    uint16_t mF0b0;                         // +0x0b0
    uint16_t mF0b2;                         // +0x0b2
    float    mF0b4;                         // +0x0b4
    float    mF0b8;                         // +0x0b8
    float    mF0bc;                         // +0x0bc
    float    mF0c0;                         // +0x0c0
    Matrix3  mMatrix0;                      // +0x0c4
    uint16_t mF0e8;                         // +0x0e8
    uint16_t mF0ea;                         // +0x0ea
    float    mF0ec;                         // +0x0ec
    float    mF0f0;                         // +0x0f0
    float    mF0f4;                         // +0x0f4
    float    mF0f8;                         // +0x0f8
    Matrix3  mMatrix1;                      // +0x0fc
    float    mF120;                         // +0x120
    float    mF124;                         // +0x124
    float    mF128;                         // +0x128
    uint16_t mF12c;                         // +0x12c
    uint16_t mF12e;                         // +0x12e
    float    mF130;                         // +0x130
    float    mF134;                         // +0x134
    float    mF138;                         // +0x138
    float    mF13c;                         // +0x13c
    float    mF140;                         // +0x140
    float    mF144;                         // +0x144
    float    mF148;                         // +0x148
    float    mF14c;                         // +0x14c
    float    mF150;                         // +0x150
    float    mF154;                         // +0x154
    float    mF158;                         // +0x158
    float    mF15c;                         // +0x15c
    float    mF160;                         // +0x160
    float    mF164;                         // +0x164
    uint32_t mF168;                         // +0x168
    float    mF16c;                         // +0x16c
    float    mF170;                         // +0x170
    float    mF174;                         // +0x174
    float    mF178;                         // +0x178
    float    mF17c;                         // +0x17c
    float    mF180;                         // +0x180
    float    mF184;                         // +0x184
    float    mF188;                         // +0x188
    float    mF18c;                         // +0x18c
    float    mF190;                         // +0x190
    void*    mpF194;                        // +0x194
    void*    mpF198;                        // +0x198
    void*    mpF19c;                        // +0x19c
    bool     mF1a0;                         // +0x1a0
    bool     mF1a1;                         // +0x1a1
    bool     mF1a2;                         // +0x1a2
    char     mPad1a3;                       // +0x1a3
    uint32_t mF1a4;                         // +0x1a4
    uint32_t mF1a8;                         // +0x1a8
    float    mF1ac;                         // +0x1ac
    float    mF1b0;                         // +0x1b0
    float    mF1b4;                         // +0x1b4
    float    mF1b8;                         // +0x1b8
    float    mF1bc;                         // +0x1bc
    float    mF1c0;                         // +0x1c0
    char     mPad1c4[4];                    // +0x1c4
    int32_t  mF1c8;                         // +0x1c8
    int32_t  mF1cc;                         // +0x1cc
    uint32_t mF1d0;                         // +0x1d0
    SpVectorRefVertex mRefVertices;         // +0x1d4
    bool     mF1e8;                         // +0x1e8
    char     mPad1e9[3];                    // +0x1e9
    void*    mpF1ec;                        // +0x1ec
    void*    mpF1f0;                        // +0x1f0
    void*    mpF1f4;                        // +0x1f4
    char     mPad1f8[8];                    // +0x1f8
    bool     mF200;                         // +0x200
    char     mPad201[3];                    // +0x201
    void*    mpF204;                        // +0x204
    void*    mpF208;                        // +0x208
    void*    mpF20c;                        // +0x20c
    char     mPad210[8];                    // +0x210
    F218Object* mpF218;                     // +0x218
    bool     mF21c;                         // +0x21c
    char     mPad21d[3];                    // +0x21d
    int32_t  mF220;                         // +0x220
    int32_t  mF224;                         // +0x224
    char     mPad228[6];                    // +0x228
    bool     mF22e;                         // +0x22e
    char     mPad22f[9];                    // +0x22f

    cParticlesEffect* Init(void* pDesc, uint32_t collectionIndex);
    void Destroy();
};

// @ 0x00f7afd0
cParticlesEffect* cParticlesEffect::Init(void* pDesc, uint32_t collectionIndex)
{
    float zero = 0.0f;
    float one;
    void* anchor;

    mpVtbl1 = (void*)0x140b5a0;
    mpVtbl3 = (void*)0x13ef094;
    mF10 = 0;
    mpVtbl2 = (void*)0x13f21d4;
    mpVtbl3 = (void*)0x13f2194;
    mpVtbl0 = (void*)0x148ff18;
    mpVtbl1 = (void*)0x148ff14;
    mpVtbl2 = (void*)0x148fed8;
    mpVtbl3 = (void*)0x148fed4;
    mStarted = false;
    mDelayedStopActive = false;
    mIsVisible = true;
    mF17 = false;
    anchor = (void*)&mpParticlesHead;
    mpParticlesAnchor = anchor;
    mpParticlesHead = anchor;
    mOverallTime = 0.0;
    mParticleSystemTime = 0.0;
    mpDesc = pDesc;
    mCollectionIndex = collectionIndex;
    mInverseRateCurveTime = g1454410;
    mParticlesToGenerate = zero;
    mParticleCount = 0;
    mpWorld = 0;
    mpGlobalParams = 0;
    mPreroll = false;
    mCurrentCycle = 0;

    mDirectionalForcesSum[0] = g16c9b28.f;
    mDirectionalForcesSum[1] = g16c9b2c.f;
    mDirectionalForcesSum[2] = g16c9b30.f;
    mRandomWalkNextTime = zero;
    mRandomWalkStrengthV = g16c9b28.f;
    mRandomWalkStrengthH = g16c9b2c.f;
    mRandomWalkTheta = g16c9b30.f;
    mF80 = zero;
    mF84 = zero;
    mAttractorForce = zero;
    mAttractorLocation[0] = zero;
    mAttractorLocation[1] = zero;
    mAttractorLocation[2] = zero;
    mAttractorIntensity = zero;
    mRetriggerTime = zero;
    mF0a0 = zero;
    mF0a4 = g16c9b28.f;
    mF0a8 = g16c9b2c.f;
    mF0ac = g16c9b30.f;
    mF0b0 = 0;
    mF0b2 = 0;
    mF0b4 = g16c9b28.f;
    mF0b8 = g16c9b2c.f;
    mF0bc = g16c9b30.f;
    one = g1485720.f;
    mF0c0 = one;

    ((Matrix33Ctor*)&mMatrix0)->Assign((const void*)0x16c9b34);

    mF0e8 = 0;
    mF0ea = 0;
    mF0ec = g16c9b28.f;
    mF0f0 = g16c9b2c.f;
    mF0f4 = g16c9b30.f;
    one = g1485720.f;
    mF0f8 = one;

    ((Matrix33Ctor*)&mMatrix1)->Assign((const void*)0x16c9b34);

    mF120 = g16c9b28.f;
    mF124 = g16c9b2c.f;
    mF128 = g16c9b30.f;
    mF12c = 0;
    mF12e = 0;
    mF130 = g16c9b78.f;
    mF134 = g16c9b7c.f;
    mF138 = g16c9b78.f;
    mF13c = g16c9b7c.f;
    mF140 = g16c9b78.f;
    mF144 = g16c9b7c.f;
    one = g1485720.f;
    mF148 = one;
    mF14c = one;
    mF150 = one;
    mF154 = one;
    mF158 = one;
    mF15c = g16c9b80.f;
    mF160 = g16c9b84.f;
    mF164 = g16c9b88.f;
    mF168 = 0;
    mF16c = g1418f90.f;
    mF170 = g13f0620.f;
    mF174 = one;
    mF178 = one;
    mF17c = one;
    mF180 = one;
    mF184 = one;
    mF188 = g16c9b80.f;
    mF18c = g16c9b84.f;
    mF190 = g16c9b88.f;
    mpF194 = 0;
    mpF198 = 0;
    mpF19c = 0;
    mF1a0 = false;
    mF1a1 = false;
    mF1a2 = false;
    mF1a4 = 0;
    mF1a8 = 0;
    mF1ac = 0.0f;
    mF1b0 = 0.0f;
    mF1b4 = 0.0f;
    mF1b8 = 0.0f;
    mF1bc = 0.0f;
    mF1c0 = 0.0f;
    mF1c8 = -1;
    mF1cc = -1;
    mF1d0 = 0;
    mRefVertices.mpBegin = 0;
    mRefVertices.mpEnd = 0;
    mRefVertices.mpCapacity = 0;
    mF1e8 = false;
    mpF1ec = 0;
    mpF1f0 = 0;
    mpF1f4 = 0;
    mF200 = false;
    mpF204 = 0;
    mpF208 = 0;
    mpF20c = 0;
    mpF218 = 0;
    mF220 = -1;
    mF224 = -1;
    mF21c = false;
    mF22e = false;
    return this;
}

// @ 0x00f7b460
void cParticlesEffect::Destroy()
{
    mpVtbl0 = (void*)0x148ff18;
    mpVtbl1 = (void*)0x148ff14;
    mpVtbl2 = (void*)0x148fed8;
    mpVtbl3 = (void*)0x148fed4;
    _ReadWriteBarrier();
    if (mpF218) {
        void* obj = (void*)&mpF218->mpVtable;
        void** vt = *(void***)obj;
        ((void (__thiscall*)(void*))vt[0x38 / 4])(obj);
    }
    if (mpF204 && ((HeapBlock*)mpF204)[-1].mRefCount != 0)
        operator delete(mpF204);
    if (mpF1ec && ((HeapBlock*)mpF1ec)[-1].mRefCount != 0)
        operator delete(mpF1ec);
    mRefVertices.Destroy();
    if (mpF19c) {
        void** vt = *(void***)mpF19c;
        ((void (__thiscall*)(void*))vt[1])(mpF19c);
    }
    if (mpF198) {
        void** vt = *(void***)mpF198;
        ((void (__thiscall*)(void*))vt[1])(mpF198);
    }
    if (mpF194) {
        void** vt = *(void***)mpF194;
        ((void (__thiscall*)(void*))vt[1])(mpF194);
    }
    ((IntrusiveListBase*)&mpParticlesHead)->Destroy();
    mpVtbl2 = (void*)0x13f21d4;
    mpVtbl3 = (void*)0x13ef094;
}
