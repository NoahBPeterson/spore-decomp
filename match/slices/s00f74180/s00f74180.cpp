// Slice s00f74180 — 9 functions of the older-layout EA::Swarm cParticlesEffect object (the copy
// sitting next to the quad streamers s00f77940/s00f78a60).  For seven of them `this` is the
// cComponentBase subobject at object+8; 0xf747a0 (RenderStream, vtable slot 0 of object+0) and
// 0xf74b40 (ApplyLoopBox) take the object base.  Offsets are read off the disassembly and agree
// with the sibling slices s00f7caf0 / s00f78a60 (minus 8).  Class/field names are Claude-coined.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <math.h>
#include <xmmintrin.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed long long   s64;
typedef unsigned long long u64;

namespace EA { namespace Swarm {

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct Matrix33 { float m[3][3]; };

struct cTransform {                              // 0x38
    u16      mFlags;                             // +0x00
    u16      mModificationCount;                 // +0x02
    Vector3  mTranslation;                       // +0x04
    float    mScale;                             // +0x10
    Matrix33 mRotation;                          // +0x14
};

struct cBoundingBox { Vector3 mMin; Vector3 mMax; };

template<int N> struct bitset {
    u32 mWord[(N + 31) / 32];
    bool test(int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};

template<class T> struct vector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];
    int  size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

// The 32-byte render block the description carries at +0x110 and the command handler copies.
struct cRenderInfo {                             // 0x20
    s64 mID;                                     // +0x00
    u32 mFormat;                                 // +0x08  (byte0 render format, byte1 source format)
    u32 mField0c;                                // +0x0c
    u32 mField10;                                // +0x10
    u32 mField14;                                // +0x14
    u32 mField18;                                // +0x18
    u32 mField1c;                                // +0x1c
};

struct cParticlesDescription {                   // older layout
    void*             vftable;                   // +0x000
    u32               pad004;                    // +0x004
    bitset<32>        mFlags;                    // +0x008
    u8                pad00c[0x1c - 0x0c];       // +0x00c
    Vector2           mField1c;                  // +0x01c
    Vector2           mField24;                  // +0x024
    u8                pad02c[0x80 - 0x2c];       // +0x02c
    u16               mField080;                 // +0x080
    u8                pad082[0x110 - 0x082];     // +0x082
    cRenderInfo       mRenderInfo;               // +0x110
    u8                pad130[0x131 - 0x130];     // +0x130
    u8                mPhysicsType;              // +0x131
    u8                pad132[0x13c - 0x132];     // +0x132
    Vector3           mDirectionalForcesSum;     // +0x13c
    u8                pad148[0x184 - 0x148];     // +0x148
    vector<Vector3>   mLoopBoxColorCurve;        // +0x184
    vector<float>     mLoopBoxAlphaCurve;        // +0x198
};

class cIRenderer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void SetupFormat(int format, u8* offsets);                  // +0x10
    virtual void v14();
    virtual bool CreateTexture(void* obj, const void* info, int* id);   // +0x18
    virtual void StopTexture(int id);                                   // +0x1c
    virtual void v20();
    virtual void SetTextureVisible(int id, u8 visible);                 // +0x24
    virtual void v28();
    virtual bool CreateModel(void* obj, const void* info, int* id);     // +0x2c
    virtual void StopModel(int id);                                     // +0x30
    virtual void v34();
    virtual void SetModelVisible(int id, u8 visible);                   // +0x38
};

class cIFormat {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual u8 Choose(int a, int b, int c);                             // +0x24
};

class cIFormatSelector {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual cIFormat* GetFormat();                                      // +0x14
};

class cIEffectsWorld {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual cIRenderer* GetRenderer();                                  // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual cIFormatSelector* GetFormatSelector();                      // +0x30
};

class cEffectObject;

// The complete object: primary base at +0 (vtable 0x148ff18, RenderStream in slot 0) and the
// cParticlesEffect subobject at +8 (vtable 0x148fed8, slots 0x00..0x3c).  Defined after
// cParticlesEffect below because it holds one by value.

class cParticlesEffect;

// Virtual-only base.  The vfptr lands at +0 of cParticlesEffect, and because this base has no
// 8-byte member MSVC does not pad the vfptr out to 8, so cParticlesEffect's own fields start at
// +4 (matching the original: mRefCountBase at +4, mStarted at +0xc, mOverallTime at +0x30, ...).
class cEffectVtbl {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08(int preroll);
    virtual void v0c(int hard);
    virtual bool v10(void* a, void* b, Vector3* out, int c, float d, float e);
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool v20(int cmd, int* data, int count);
    virtual void v24();
    virtual void v28(u8 visible);
    virtual void v2c(cParticlesEffect* chain);
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
};

class cParticlesEffect : public cEffectVtbl {
public:
    virtual void v04();                                                     // 0xf747e0
    virtual void v08(int preroll);                                         // 0xf749d0
    virtual bool v10(void* a, void* b, Vector3* out, int c, float d, float e);
    virtual bool v20(int cmd, int* data, int count);                        // 0xf744c0
    virtual void v28(u8 visible);                                           // 0xf748c0
    virtual void v2c(cParticlesEffect* chain);                              // 0xf74950

    bool GetFrame(void* unused, void* param, Vector3* dir, Vector4* out, float a, float b);

    u32    mRefCountBase[2];                     // +0x04
    bool   mStarted;                             // +0x0c
    bool   mDelayedStopActive;                   // +0x0d
    u8     mIsVisible;                           // +0x0e
    u8     pad00f;                               // +0x0f
    u32    pad010[3];                            // +0x10
    cParticlesDescription* mDesc;                // +0x1c
    u32    pad020;                               // +0x20
    cIEffectsWorld* mWorld;                      // +0x24
    u32    pad028[2];                            // +0x28
    double mOverallTime;                         // +0x30
    bool   mPreroll;                             // +0x38
    u8     pad039[7];                            // +0x39
    double mParticleSystemTime;                  // +0x40
    u32    mCurrentCycle;                        // +0x48
    u32    pad04c[3];                            // +0x4c
    float  mParticlesToGenerate;                 // +0x58
    Vector3 mDirectionalForcesSum;               // +0x5c
    u32    pad068[5];                            // +0x68
    float  mAttractorForce;                      // +0x7c
    u32    pad080[10];                           // +0x80
    cTransform mSourceTransform;                 // +0xa8
    u32    pad0e0[14];                           // +0xe0
    Vector3 mLastEmitLocation;                   // +0x118
    u16    mRenderCount;                         // +0x124
    u16    mLastRenderCount;                     // +0x126
    u32    pad128[14];                           // +0x128
    u32    mField160;                            // +0x160
    u32    pad164[10];                           // +0x164
    void*  mParamA;                              // +0x18c
    void*  mParamB;                              // +0x190
    void*  mParamC;                              // +0x194
    u32    pad198[3];                            // +0x198
    cBoundingBox mEmissionVolume;                // +0x1a4
    s64    mOverrideID;                          // +0x1c0
    u32    pad1c8[18];                           // +0x1c8
    cEffectObject* mChainSystem;                 // +0x210
    u8     mSuppressEmission;                    // +0x214
    u8     pad215[3];                            // +0x215
    int    mModelParticlesID;                    // +0x218
    int    mTextureParticlesID;                  // +0x21c
    u8     mOffsets[5];                          // +0x220
    u8     pad225;                               // +0x225
    u8     mCurrentFormat;                       // +0x226
    u8     pad227;                               // +0x227
};

class cEffectObject {
public:
    virtual void RenderStream(void* param);      // slot 0 -> 0xf747a0
    cParticlesEffect mBase;                      // +0x08
};

struct cParam {                                  // cIParam, only the virtuals used here
    virtual void p00(); virtual void p04(); virtual void p08();
    virtual void p0c();
};

// Command manager passed to the AddCommands free functions.
class cCommandManager {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10();
    virtual void AddDescription(const char* name, void* cmd);   // +0x14
    virtual void AddEffect(const char* name, void* cmd);        // +0x18
};

// ---- callees -------------------------------------------------------------------------
float SP_RandomInRange(const Vector2& range);                    // 0x004df2d0
Vector4 SP_QuatMul(const Vector4& a, const Vector4& b);          // 0x007dcb00
void* CreateParticlesDescriptionCommand(void* param);            // 0x00aa6bf0
void* CreateParticlesEffectCommand(int param);                   // 0x00aa32b0

typedef void (*StreamCommand)(cEffectObject* obj, void* param, u8* offsets);
extern StreamCommand gStreamCommands[256];                       // 0x016c9aa0

// ---- math helpers --------------------------------------------------------------------

static __forceinline float Min(float a, float b)
{
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Max(float a, float b)
{
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Clamp(float v, float lo, float hi)
{
    return Min(Max(lo, v), hi);
}

static __forceinline int FloatToInt(float v)          // cvtss2si (current rounding mode)
{
    return _mm_cvt_ss2si(_mm_set_ss(v));
}

static __forceinline int FloorToInt(float v)
{
    int i = FloatToInt(v);
    if (v < (float)i)
        i = i - 1;
    return i;
}

static __forceinline float SampleCurve(const float* curve, unsigned int last, float t)
{
    if (last == 0)
        return curve[0];
    float f = (float)last * t;
    int i = (int)f;
    float frac = f - (float)i;
    if (frac > 0.0f)
        return (curve[i + 1] - curve[i]) * frac + curve[i];
    return curve[i];
}

static __forceinline Vector3 SampleCurve(const Vector3* curve, unsigned int last, float t)
{
    Vector3 v;
    if (last == 0) {
        v = curve[0];
    } else {
        float f = (float)last * t;
        int i = (int)f;
        float frac = f - (float)i;
        const Vector3& a = curve[i];
        if (frac > 0.0f) {
            const Vector3& b = curve[i + 1];
            v.x = a.x + (b.x - a.x) * frac;
            v.y = a.y + (b.y - a.y) * frac;
            v.z = a.z + (b.z - a.z) * frac;
        } else {
            v = a;
        }
    }
    return v;
}

// Wraps a particle into the effect's emission volume and modulates its colour/alpha by the
// loop-box curves (dev: `anonymous namespace'::ApplyLoopBox).
// @ 0x00f74b40
void ApplyLoopBox(cEffectObject* effect, cParticlesDescription* desc, Vector3* pos,
                  Vector3* color, float* alpha)
{
    const Vector3& origin = effect->mBase.mSourceTransform.mTranslation;
    const cBoundingBox& box = effect->mBase.mEmissionVolume;

    float ux = ((pos->x - origin.x) - box.mMin.x) / (box.mMax.x - box.mMin.x);
    float uy = ((pos->y - origin.y) - box.mMin.y) / (box.mMax.y - box.mMin.y);
    float uz = ((pos->z - origin.z) - box.mMin.z) / (box.mMax.z - box.mMin.z);

    float fx = ux - (float)FloorToInt(ux);
    float fy = uy - (float)FloorToInt(uy);
    float fz = uz - (float)FloorToInt(uz);

    const Matrix33& rot = effect->mBase.mSourceTransform.mRotation;
    float t = rot.m[1][2] * (fz - 0.5f) + rot.m[1][1] * (fy - 0.5f)
            + rot.m[1][0] * (fx - 0.5f) + 0.5f;
    t = Clamp(t, 0.0f, 1.0f);

    if (!desc->mLoopBoxColorCurve.empty()) {
        Vector3 c = SampleCurve(desc->mLoopBoxColorCurve.mpBegin,
                                desc->mLoopBoxColorCurve.size() - 1, t);
        color->x = c.x * color->x;
        color->y = c.y * color->y;
        color->z = c.z * color->z;
    }
    if (!desc->mLoopBoxAlphaCurve.empty())
        *alpha = SampleCurve(desc->mLoopBoxAlphaCurve.mpBegin,
                             desc->mLoopBoxAlphaCurve.size() - 1, t) * *alpha;

    pos->x = origin.x + (box.mMin.x + (box.mMax.x - box.mMin.x) * fx);
    pos->y = origin.y + (box.mMin.y + (box.mMax.y - box.mMin.y) * fy);
    pos->z = origin.z + (box.mMin.z + (box.mMax.z - box.mMin.z) * fz);
}

// @ 0x00f74480
void GroundCoverAddCommands(void* unused, cCommandManager* mgr)
{
    mgr->AddDescription("groundCover", CreateParticlesDescriptionCommand((void*)0x2c));
    mgr->AddEffect("groundCover", CreateParticlesEffectCommand(0x2c));
}

// @ 0x00f747a0
void cEffectObject::RenderStream(void* param)
{
    StreamCommand fn = gStreamCommands[mBase.mCurrentFormat];
    if (fn)
        fn(this, param, mBase.mOffsets);
    ++mBase.mRenderCount;
}

// @ 0x00f74180
bool cParticlesEffect::GetFrame(void* unused, void* param, Vector3* dir, Vector4* out,
                                float a, float b)
{
    Vector3 buf;
    if (!v10(unused, param, &buf, 0, a, b))
        return false;

    float len = sqrtf(buf.x * buf.x + (buf.z * buf.z + buf.y * buf.y));
    if (len > 1e-6f) {
        Vector3 A;
        A.x = buf.y * b - buf.z * a;
        A.y = buf.z * 0.0f - b * buf.x;
        A.z = a * buf.x - buf.y * 0.0f;
        Vector3 B;
        B.x = A.z * a - A.y * b;
        B.y = A.x * 0.0f - a * A.z;
        B.z = b * A.x - A.y * 0.0f;
        float lenB = sqrtf(B.z * B.z + (B.y * B.y + B.x * B.x));
        if (lenB > 1e-6) {
            if (out) {
                Vector3 n;
                n.z = buf.z * lenB + B.z * len;
                n.x = buf.x * lenB + B.x * len;
                n.y = buf.y * lenB + B.y * len;
                float inv = 1.0f / (sqrtf(n.y * n.y + (n.z * n.z + n.x * n.x)) * len);
                n.y = n.y * inv;
                n.x = inv * n.x;
                n.z = n.z * inv;
                Vector4 q;
                q.x = buf.y * n.z - buf.z * n.y;
                q.y = buf.z * n.x - n.z * buf.x;
                q.z = n.y * buf.x - buf.y * n.x;
                q.w = (buf.x * n.x + buf.z * n.z) + buf.y * n.y;                *out = SP_QuatMul(q, *out);
            }
            float s = len / lenB;
            dir->x = B.x * s;
            dir->y = B.y * s;
            dir->z = B.z * s;
        }
    }
    return true;
}

// @ 0x00f747e0
void cParticlesEffect::v04()
{
    if (mStarted)
        v0c(1);
    if (mModelParticlesID >= 0)
        mWorld->GetRenderer()->StopModel(mModelParticlesID);
    if (mTextureParticlesID >= 0)
        mWorld->GetRenderer()->StopTexture(mTextureParticlesID);
    if (mParamA) {
        ((cParam*)mParamA)->p0c();
        if (mParamA) {
            cParam* p = (cParam*)mParamA;
            mParamA = 0;
            p->p04();
        }
    }
    if (mParamB) {
        ((cParam*)mParamB)->p0c();
        if (mParamB) {
            cParam* p = (cParam*)mParamB;
            mParamB = 0;
            p->p04();
        }
    }
    if (mParamC) {
        ((cParam*)mParamC)->p0c();
        if (mParamC) {
            cParam* p = (cParam*)mParamC;
            mParamC = 0;
            p->p04();
        }
    }
    mDesc = 0;
    mWorld = 0;
}

// @ 0x00f748c0
void cParticlesEffect::v28(u8 visible)
{
    mIsVisible = visible;
    if (visible)
        mLastEmitLocation = mSourceTransform.mTranslation;
    if (mStarted) {
        if (mTextureParticlesID >= 0)
            mWorld->GetRenderer()->SetTextureVisible(mTextureParticlesID, mIsVisible);
        else if (mModelParticlesID >= 0)
            mWorld->GetRenderer()->SetModelVisible(mModelParticlesID, mIsVisible);
    }
}

// @ 0x00f74950
void cParticlesEffect::v2c(cParticlesEffect* p)
{
    cEffectObject* chain = p ? (cEffectObject*)((u8*)p - 8) : 0;
    cEffectObject* old = mChainSystem;
    if (chain != old) {
        if (chain)
            chain->mBase.v34();
        mChainSystem = chain;
        if (old)
            old->mBase.v38();
    }
    mChainSystem->mBase.mSuppressEmission = 1;
}

// @ 0x00f749d0
void cParticlesEffect::v08(int preroll)
{
    if (preroll == 0 || mDesc->mField080 <= 0 || mDesc->mFlags.test(2) || mDesc->mFlags.test(28)) {
        if (!mStarted || mDelayedStopActive) {
            mDelayedStopActive = 0;
            mStarted = 1;
        }
        mParticleSystemTime = 0;
        mOverallTime = 0;
        mCurrentCycle = 0;
        mParticlesToGenerate = 0;
        mLastEmitLocation = mSourceTransform.mTranslation;
        mDirectionalForcesSum = mDesc->mDirectionalForcesSum;
        Vector2 v;
        if (mDesc->mField1c.x >= 0.0f) {
            const Vector2& r = mDesc->mField1c;
            v.x = r.x;
            v.y = r.y;
            mAttractorForce = SP_RandomInRange(v);
        } else if (mDesc->mField24.x >= 0.0f) {
            const Vector2& r = mDesc->mField24;
            v.x = r.x;
            v.y = r.y;
            mAttractorForce = SP_RandomInRange(v);
        } else {
            mAttractorForce = 0.0f;
        }
        mPreroll = (preroll != 0);
        if (mTextureParticlesID >= 0)
            mWorld->GetRenderer()->SetTextureVisible(mTextureParticlesID, mIsVisible);
        else if (mModelParticlesID >= 0)
            mWorld->GetRenderer()->SetModelVisible(mModelParticlesID, mIsVisible);
    }
}

// @ 0x00f744c0
bool cParticlesEffect::v20(int cmd, int* data, int count)
{
    cIRenderer* r;
    cRenderInfo info;

    if (cmd == 0) {
        if (count >= 2 && data[1] != mDesc->mPhysicsType)
            return true;
        s64 id = (s64)*data;
        if (mOverrideID == id)
            return true;
        mOverrideID = id;
        if (mModelParticlesID < 0)
            return true;
        r = mWorld->GetRenderer();
        r->StopModel(mModelParticlesID);
        info = mDesc->mRenderInfo;
        info.mID = mOverrideID;
        int fmt = (info.mFormat >> 8) & 0xff;
        if (fmt == 0xf) {
            cIFormat* f = mWorld->GetFormatSelector()->GetFormat();
            info.mFormat = (info.mFormat & 0xffffff00u) | f->Choose(info.mField18, info.mField1c, 9);
        } else {
            info.mFormat = (info.mFormat & 0xffffff00u) | 9;
        }
        if (r->CreateModel((void*)((u8*)this - 4), &info, &mModelParticlesID)) {
            r->SetupFormat((u8)info.mFormat, mOffsets);
            mCurrentFormat = (u8)info.mFormat;
            if (mStarted && mIsVisible)
                r->SetModelVisible(mModelParticlesID, 1);
        } else {
            mModelParticlesID = -1;
        }
        return true;
    }
    if (cmd == 1) {
        if (count >= 2 && data[1] != mDesc->mPhysicsType)
            return true;
        s64 id = (s64)*data;
        if (mOverrideID == id)
            return true;
        mOverrideID = id;
        if (mTextureParticlesID < 0)
            return true;
        r = mWorld->GetRenderer();
        r->StopTexture(mTextureParticlesID);
        info = mDesc->mRenderInfo;
        info.mID = mOverrideID;
        int fmt = (info.mFormat >> 8) & 0xff;
        if (fmt == 0xf) {
            info.mFormat = (info.mFormat & 0xffffff00u) | 0x10;
            mOffsets[0] = 0;
            mOffsets[1] = 0x10;
            mOffsets[2] = 0x20;
            mOffsets[3] = 0x24;
            mOffsets[4] = 0x28;
        } else {
            info.mFormat = info.mFormat & 0xffffff00u;
            r->SetupFormat(0, mOffsets);
        }
        if (r->CreateTexture((void*)((u8*)this - 8), &info, &mTextureParticlesID)) {
            mCurrentFormat = (u8)info.mFormat;
            if (mStarted && mIsVisible)
                r->SetTextureVisible(mTextureParticlesID, 1);
        } else {
            mTextureParticlesID = -1;
        }
        return true;
    }
    if (cmd == 2) {
        mField160 = *data;
        return true;
    }
    return false;
}

}} // namespace EA::Swarm
