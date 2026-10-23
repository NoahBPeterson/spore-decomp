// Slice s00aa1f40 -- EA::Swarm::cModelDescription animation-curve vector helpers
// (Swarm/ModelDescription.obj) and EA::Swarm::cModelEffect (Swarm/ModelEffect.obj).
//
// Types below are local retail-layout stubs: the dev PDB differs by the wider retail eastl
// vector (0x14 rather than 0x10 bytes), which is why several fields sit 4 bytes later.

#include <math.h>
#include <intrin.h>
typedef unsigned int uint32_t;

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

// ------------------------------------------------------------------ externs
void __cdecl operator_delete(void*);                                             // 0x00f47380
void* __cdecl EAAllocate(uint32_t size, const char* name, int flags, int align,
                         const char* file, int line);                            // 0x00f473a0
extern const char g_eastlName[];                                                 // 0x013f2150 "EASTL"
extern const char g_eastlFile[];                                                 // 0x013ebb38 allocator.h
extern const float g_one;                                                              // 0x01485720 1.0f
extern Vector3 g_defaultTranslation;                                             // 0x016791a4
extern float g_identityMatrix[9];                                                // 0x01679250
extern char g_vtbl_GmeIComponent[];                                               // 0x013f21d4
extern char g_vtbl_GmeRefCount[];                                                 // 0x013ef094
extern char g_vtbl_cModelEffect[];                                                // 0x01458ce8
extern char g_vtbl_cModelEffectRefCount[];                                        // 0x01458ce4

// ------------------------------------------------------------------ eastl vector of cAnimationCurve
struct cAnimationCurve;
struct sp_float_vector {
    float* mpBegin; float* mpEnd; float* mpCapacity; int mAllocator[2];
    void Allocate(int n, const int* alloc);                        // 0x004aa350
    sp_float_vector& operator=(const sp_float_vector& src);        // 0x0050d4e0
};
struct cAnimationCurveVector {
    cAnimationCurve* mpBegin;      // 0x00
    cAnimationCurve* mpEnd;        // 0x04
    cAnimationCurve* mpCapacity;   // 0x08
    int mAllocator[2];             // 0x0c
    void DoInsertValues(cAnimationCurve* position, uint32_t n, const cAnimationCurve& value); // 0x00aa1f40
    void resize(uint32_t n);                                                                  // 0x00aa2150
    void Erase(cAnimationCurve* first, cAnimationCurve* last);                                // 0x00aa1ef0
};

struct cAnimationCurve {                                   // size 0x28
    Vector2 mLengthRange;              // 0x00
    sp_float_vector mCurve;            // 0x08
    float mCurveVary;                  // 0x1c
    float mSpeedScale;                 // 0x20
    char mChannel;                     // 0x24
    char mMode;                        // 0x25
    cAnimationCurve() { mLengthRange.x = 0.0f; mLengthRange.y = 0.0f;
                        mCurve.mpBegin = 0; mCurve.mpEnd = 0; mCurve.mpCapacity = 0;
                        mCurveVary = 0.0f; mSpeedScale = 0.0f; mChannel = 0; mMode = 0; }
    cAnimationCurve(const cAnimationCurve& src) { CopyFrom(src); }
    cAnimationCurve* CopyFrom(const cAnimationCurve& src);     // 0x00aa1cc0
};

cAnimationCurve* __cdecl uninit_copy_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest);  // 0x00aa1d70
cAnimationCurve* __cdecl destroy_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest);      // 0x00aa1bf0
void __cdecl uninit_fill_n_curves(cAnimationCurve* first, uint32_t n, const cAnimationCurve* value);               // 0x00aa1ec0
cAnimationCurve* __cdecl copy_backward_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* destEnd); // 0x00aa1e60
void __cdecl fill_curves(cAnimationCurve* first, cAnimationCurve* last, const cAnimationCurve* value);             // 0x00aa1e10
cAnimationCurve** __cdecl uninit_copy_it_curves(cAnimationCurve** destSlot, cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest, cAnimationCurve* extra); // 0x00aa1d30

inline cAnimationCurve* uninitialized_move_curves(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dest)
{
    cAnimationCurve* d = uninit_copy_curves(first, last, dest);
    destroy_curves(first, last, dest);
    return d;
}

// @ 0x00aa1f40
void cAnimationCurveVector::DoInsertValues(cAnimationCurve* position, uint32_t n, const cAnimationCurve& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const cAnimationCurve temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            cAnimationCurve* const pEnd = mpEnd;
            if (n < nExtra) {
                cAnimationCurve* newEnd;
                uninit_copy_it_curves(&newEnd, mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                copy_backward_curves(position, pEnd - n, pEnd);
                fill_curves(position, position + n, &temp);
            } else {
                uninit_fill_n_curves(mpEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                uninit_copy_curves(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill_curves(position, pEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        cAnimationCurve* const pNewData = (cAnimationCurve*)EAAllocate(nNewSize * 0x28, g_eastlName, 0, 0, g_eastlFile, 0xd1);
        cAnimationCurve* pNewEnd = uninitialized_move_curves(mpBegin, position, pNewData);
        uninit_fill_n_curves(pNewEnd, n, &value);
        pNewEnd = uninitialized_move_curves(position, mpEnd, pNewEnd + n);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            operator_delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00aa2150
void cAnimationCurveVector::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        cAnimationCurve temp;
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), temp);
        if (temp.mCurve.mpBegin != 0 && *(int*)((char*)temp.mCurve.mpBegin - 4) != 0)
            operator_delete(temp.mCurve.mpBegin);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// ------------------------------------------------------------------ IO stream
struct IOStream {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void* Read(void* dst, int size);      // slot 12 (+0x30)
};

bool __cdecl ReadInt32(IOStream* is, void* dst, int count, int flag);   // 0x0093a780
bool __cdecl ReadInt64(IOStream* is, void* dst, int count, int flag);   // 0x0093a800
bool __cdecl ReadByte(IOStream* is, void* dst, int count);              // 0x0093a6c0
IOStream* __cdecl ReadFloatVector(IOStream* is, sp_float_vector* v); // 0x007d27d0
long double __cdecl RandomCurveLength(cAnimationCurve* curve);          // 0x007cdb90

// @ 0x00aa2210
IOStream* __cdecl ReadAnimationCurves(IOStream* is, cAnimationCurveVector* curves)
{
    uint32_t count;
    ReadInt32(is, &count, 1, 0);
    curves->resize(count);
    for (uint32_t i = 0; i < count; ++i) {
        cAnimationCurve* c = curves->mpBegin + i;
        is->Read(&c->mLengthRange, 8);
        ReadFloatVector(is, &c->mCurve);
        ReadInt32(is, &c->mCurveVary, 1, 0);
        ReadInt32(is, &c->mSpeedScale, 1, 0);
        ReadByte(is, &c->mChannel, 1);
        ReadByte(is, &c->mMode, 1);
    }
    return is;
}

// ------------------------------------------------------------------ cModelDescription
struct cModelDescription {
    void* mpVtbl;                     // 0x00
    uint32_t mPad04;                  // 0x04
    uint32_t mFlags;                  // 0x08
    uint32_t mPad0c;                  // 0x0c
    union {
        struct { uint32_t mResourceIDLo; uint32_t mResourceIDHi; };
        unsigned long long mResourceID;
    };                                // 0x10
    float mSize;                      // 0x18
    Vector3 mColour;                  // 0x1c
    float mAlpha;                     // 0x28
    cAnimationCurveVector mAnimationCurves; // 0x2c
    union {
        struct { uint32_t mMaterialIDLo; uint32_t mMaterialIDHi; };
        unsigned long long mMaterialID;
    };                                // 0x40
    char mOverrideSet;                // 0x48
};

// @ 0x00aa22b0
void __cdecl ReadModelDescription(IOStream* is, int unused, cModelDescription* desc)
{
    int flags;
    ReadInt32(is, &flags, 1, 0);
    desc->mFlags = (uint32_t)flags & 3;
    ReadInt64(is, &desc->mResourceIDLo, 1, 0);
    ReadInt32(is, &desc->mSize, 1, 0);
    is->Read(&desc->mColour, 0xc);
    ReadInt32(is, &desc->mAlpha, 1, 0);
    ReadAnimationCurves(is, &desc->mAnimationCurves);
    ReadInt64(is, &desc->mMaterialIDLo, 1, 0);
    ReadByte(is, &desc->mOverrideSet, 1);
}

// @ 0x00aa2340
int __cdecl CollectModelRefs(int unused, cModelDescription* desc, uint32_t* out, int maxCount)
{
    int count = 0;
    unsigned long long resID = desc->mResourceID;
    if (resID != 0xffffffffffffffffull) {
        count = 1;
        if (maxCount > 0) {
            *(unsigned long long*)out = resID;
            out[2] = 2;
            out += 4;
            maxCount--;
        }
    }
    unsigned long long matID = desc->mMaterialID;
    if (matID != 0xffffffffffffffffull) {
        count++;
        if (maxCount > 0) {
            *(unsigned long long*)out = matID;
            out[2] = 1;
        }
    }
    return count;
}

// ------------------------------------------------------------------ transforms
struct Matrix3 {
    float m[9];
    void* Assign(const void* src);                                 // 0x0041cb40
};
struct cTransform {
    unsigned short mFlags;             // 0x00
    unsigned short mModCount;          // 0x02
    Vector3 mTranslation;              // 0x04
    float mScale;                      // 0x10
    Matrix3 mRotation;                 // 0x14
    void PreTransformBy(const cTransform& src);                    // 0x00537f40
    void* Assign(const void* src);                                 // 0x00537dc0
};
struct cSPTransform : cTransform {
    cSPTransform(const cTransform& src);                           // 0x00538000
};

// ------------------------------------------------------------------ renderer
struct cIRenderer {
    virtual void AddRef();                                                     // 0x00
    virtual void Release();                                                    // 0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07();
    virtual cIRenderer* GetRenderer();                                         // 0x20 (slot 8)
    virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15();
    virtual bool BindModel(uint32_t lo, uint32_t hi, int* outID, float size);  // 0x40 (slot 16)
    virtual void ReleaseModel(int id);                                         // 0x44 (slot 17)
    virtual void SetVisible(int id, char visible);                             // 0x48 (slot 18)
    virtual void SetTransform(int id, const cTransform* xform);                // 0x4c (slot 19)
    virtual void SetColor(int id, const Vector3* colour, float alpha);         // 0x50 (slot 20)
    virtual void SetAnimParam(int id, int channel, float value);               // 0x54 (slot 21)
    virtual void SetOverride(int id, uint32_t lo, uint32_t hi);                // 0x58 (slot 22)
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28();
    virtual bool OverrideX(int a, int id, int b, int c, float* args);          // 0x74 (slot 29)
};

struct CRandom { double RandomDoubleUniform(); };                              // 0x009360d0
extern CRandom g_sRandom_Swarm;                                                // 0x016778dc
struct cEffectsWorld {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual cIRenderer* GetRenderer();                                         // slot 8 (+0x20)
};
struct cEffectParams {
    char pad[0x20];
    int mCounter;                      // 0x20
};

// ------------------------------------------------------------------ cModelEffect
struct cLODScales { float v0; float v1; float v2; };
struct cLODScalesVector {
    cLODScales* mpBegin; cLODScales* mpEnd; cLODScales* mpCapacity; int mAllocator[2];
    void resize(uint32_t n);           // 0x00a6f010
};

struct cModelEffect {
    void* mpVtbl;                      // 0x00
    void* mpRefCountVtbl;              // 0x04
    int mRefCount;                     // 0x08
    cModelDescription* mDesc;          // 0x0c
    char mActive;                      // 0x10
    char mIsVisible;                   // 0x11
    char pad12[2];
    cIRenderer* mRenderer;             // 0x14
    int mModelID;                      // 0x18
    char mModelDirty;                  // 0x1c
    char pad1d[3];
    Vector3 mModelColor;               // 0x20
    float mModelAlpha;                 // 0x2c
    float mModelScale;                 // 0x30
    cTransform mComponentXform;        // 0x34
    Vector3 mLastLocation;             // 0x6c
    char mHasLOD;                      // 0x78
    char pad79[3];
    Vector2 mLODSizeScale;             // 0x7c
    Vector2 mLODAlphaScale;            // 0x84
    cLODScalesVector mAnimationInfo;   // 0x8c
    union {
        struct { uint32_t mModelOverrideLo; uint32_t mModelOverrideHi; };
        long long mModelOverride;
    };                                 // 0xa0

    void Init(cEffectsWorld* world, int unused2, int unused3);              // 0x00aa23a0
    void Shutdown();                                                       // 0x00aa2470
    void Stop(int unused);                                                 // 0x00aa24b0
    bool SetIntParams(int flag, int* args, int nargs);                     // 0x00aa24e0
    bool SetFloatParams(int param, float* args, int unused);               // 0x00aa25f0
    void SetIsVisible(char visible);                                       // 0x00aa2800
    void ApplyEffect(float dt, float lerp, cEffectParams* params);         // 0x00aa2840
    cModelEffect(cModelDescription* desc);                                 // 0x00aa2b60
    void* Destroy(uint32_t flags);                                         // 0x00aa2c60
    void SetTransforms(const cTransform& parent, const cTransform& src);   // 0x00aa2cc0
    void Start(int unused);                                                // 0x00aa2d80
};

inline void CallVirtualStop(cModelEffect* self, int x)
{
    typedef void (__thiscall* Fn)(cModelEffect*, int);
    Fn fn = (Fn)(*(void***)self)[3];
    fn(self, x);
}

// @ 0x00aa23a0
void cModelEffect::Init(cEffectsWorld* world, int unused2, int unused3)
{
    cIRenderer* r = world->GetRenderer();
    if (r != mRenderer) {
        if (r != 0)
            r->AddRef();
        cIRenderer* old = mRenderer;
        mRenderer = r;
        if (old != 0)
            old->Release();
    }
    cModelDescription* d = mDesc;
    mModelColor = d->mColour;
    mModelAlpha = d->mAlpha;
    if (mRenderer != 0) {
        if (mRenderer->BindModel(d->mResourceIDLo, d->mResourceIDHi, &mModelID, d->mSize)) {
            mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
            if (d->mMaterialID != 0xffffffffffffffffull)
                mRenderer->SetOverride(mModelID, d->mMaterialIDLo, d->mMaterialIDHi);
        } else {
            cIRenderer* old = mRenderer;
            mRenderer = 0;
            old->Release();
        }
    }
}

// @ 0x00aa2470
void cModelEffect::Shutdown()
{
    if (mRenderer != 0) {
        if (mModelID >= 0)
            mRenderer->ReleaseModel(mModelID);
        if (mRenderer != 0) {
            cIRenderer* old = mRenderer;
            mRenderer = 0;
            old->Release();
        }
    }
}

// @ 0x00aa24b0
void cModelEffect::Stop(int unused)
{
    if (mActive) {
        mActive = 0;
        if (mRenderer != 0)
            mRenderer->SetVisible(mModelID, 0);
    }
}

// @ 0x00aa24e0
bool cModelEffect::SetIntParams(int flag, int* args, int nargs)
{
    if (flag != 0)
        return false;
    if (nargs >= 2 && (uint32_t)args[1] != (uint32_t)(unsigned char)mDesc->mOverrideSet)
        return true;
    int id = args[0];
    if (mModelOverride != (long long)id) {
        mModelOverrideLo = (uint32_t)id;
        mModelOverrideHi = 0;
        if (mRenderer != 0) {
            if (mModelID >= 0)
                mRenderer->ReleaseModel(mModelID);
            if (mRenderer->BindModel(mModelOverrideLo, mModelOverrideHi, &mModelID, mDesc->mSize)) {
                mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
                mRenderer->SetVisible(mModelID, mIsVisible);
                mRenderer->SetTransform(mModelID, &mComponentXform);
                unsigned long long matID = mDesc->mMaterialID;
                if (matID != 0xffffffffffffffffull)
                    mRenderer->SetOverride(mModelID, (uint32_t)matID, (uint32_t)(matID >> 32));
            } else {
                mModelID = -1;
            }
        }
    }
    return true;
}

// @ 0x00aa25f0
bool cModelEffect::SetFloatParams(int param, float* args, int unused)
{
    if (param == 4) {
        mModelAlpha = mDesc->mAlpha * args[0];
        mModelDirty = 1;
        return true;
    }
    if (param == 5) {
        mModelColor.x = mDesc->mColour.x * args[0];
        mModelColor.y = mDesc->mColour.y * args[1];
        mModelColor.z = mDesc->mColour.z * args[2];
        mModelDirty = 1;
        return true;
    }
    if (param == 1) {
        if (mRenderer != 0) {
            if (mModelID >= 0)
                mRenderer->ReleaseModel(mModelID);
            if (mRenderer->BindModel(mDesc->mResourceIDLo, mDesc->mResourceIDHi, &mModelID, mDesc->mSize * args[0])) {
                mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
                mRenderer->SetVisible(mModelID, mIsVisible);
                mRenderer->SetTransform(mModelID, &mComponentXform);
                if (mDesc->mMaterialID != 0xffffffffffffffffull)
                    mRenderer->SetOverride(mModelID, mDesc->mMaterialIDLo, mDesc->mMaterialIDHi);
            } else {
                mModelID = -1;
            }
        }
        return false;
    }
    if (param == 0xe) {
        if (mModelID >= 0)
            return mRenderer->OverrideX(2, mModelID, 0, unused, args);
        return false;
    }
    if (param == 0x101) {
        mLODSizeScale.x = args[1];
        mLODAlphaScale.x = args[2];
        mLODSizeScale.y = args[4];
        mLODAlphaScale.y = args[5];
        if (mLODAlphaScale.x == 1.0f && mLODAlphaScale.y == 1.0f &&
            mLODSizeScale.x == 1.0f && mLODSizeScale.y == 1.0f) {
            mHasLOD = 0;
            mModelDirty = 1;
            return true;
        }
        mHasLOD = 1;
        mModelDirty = 1;
        return true;
    }
    return false;
}

// @ 0x00aa2800
void cModelEffect::SetIsVisible(char visible)
{
    mIsVisible = visible;
    if (mActive && mRenderer != 0)
        mRenderer->SetVisible(mModelID, visible);
}

// @ 0x00aa2840
void cModelEffect::ApplyEffect(float dt, float lerp, cEffectParams* params)
{
    if (mRenderer == 0)
        return;
    if (mHasLOD) {
        if (mLODSizeScale.x != mLODSizeScale.y || mModelDirty) {
            cSPTransform xform(mComponentXform);
            xform.mFlags |= 1;
            xform.mModCount++;
            xform.mScale = ((mLODSizeScale.y - mLODSizeScale.x) * lerp + mLODSizeScale.x) * xform.mScale;
            mRenderer->SetTransform(mModelID, &xform);
        }
        mRenderer->SetColor(mModelID, &mModelColor,
                            ((mLODAlphaScale.y - mLODAlphaScale.x) * lerp + mLODAlphaScale.x) * mModelAlpha);
    } else {
        if (mModelDirty) {
            mRenderer->SetTransform(mModelID, &mComponentXform);
            mRenderer->SetColor(mModelID, &mModelColor, mModelAlpha);
        } else {
            goto anims;
        }
    }
    mModelDirty = 0;

anims:
    if (mAnimationInfo.mpBegin != mAnimationInfo.mpEnd) {
        float dx = mLastLocation.x - mComponentXform.mTranslation.x;
        float dy = mLastLocation.y - mComponentXform.mTranslation.y;
        float dz = mLastLocation.z - mComponentXform.mTranslation.z;
        float dist = (float)(sqrt((double)dx * dx + (double)dy * dy + (double)dz * dz) / (double)mComponentXform.mScale);
        uint32_t n = (uint32_t)(mAnimationInfo.mpEnd - mAnimationInfo.mpBegin);
        for (uint32_t i = 0; i < n; ++i) {
            cLODScales* info = mAnimationInfo.mpBegin + i;
            cAnimationCurve* curve = mDesc->mAnimationCurves.mpBegin + i;
            float step = dt;
            if (curve->mSpeedScale > 0.0f)
                step = curve->mSpeedScale * dist;
            float v = step * info->v1 + info->v0;
            info->v0 = v;
            if (v > 1.0f) {
                if (curve->mMode == 1) {
                    info->v0 = 1.0f;
                } else if (curve->mMode == 2) {
                    CallVirtualStop(this, 0);
                    return;
                } else {
                    info->v0 = 0.0f;
                    long double r = RandomCurveLength(curve);
                    if (r <= 0.0)
                        info->v1 = 0.0f;
                    else
                        info->v1 = 1.0f / (float)r;
                }
            }
            float sample;
            int nseg = (int)(curve->mCurve.mpEnd - curve->mCurve.mpBegin) - 1;
            if (nseg == 0) {
                sample = curve->mCurve.mpBegin[0];
            } else {
                float u = (float)nseg * info->v0;
                int idx = (int)u;
                float frac = u - (float)idx;
                if (frac <= 0.0f)
                    sample = curve->mCurve.mpBegin[idx];
                else
                    sample = (curve->mCurve.mpBegin[idx + 1] - curve->mCurve.mpBegin[idx]) * frac + curve->mCurve.mpBegin[idx];
            }
            mRenderer->SetAnimParam(mModelID, (int)curve->mChannel, info->v2 * sample);
        }
        mLastLocation = mComponentXform.mTranslation;
    }
    params->mCounter++;
}

// @ 0x00aa2b60
cModelEffect::cModelEffect(cModelDescription* desc)
{
    float one = g_one;
    mpRefCountVtbl = g_vtbl_GmeRefCount;
    mRefCount = 0;
    mpVtbl = g_vtbl_cModelEffect;
    mpRefCountVtbl = g_vtbl_cModelEffectRefCount;
    mDesc = desc;
    mActive = 0;
    mIsVisible = 1;
    mRenderer = 0;
    mModelID = -1;
    mModelDirty = 0;
    mModelColor.x = one; mModelColor.y = one; mModelColor.z = one;
    mModelAlpha = one;
    mModelScale = one;
    mComponentXform.mFlags = 0;
    mComponentXform.mModCount = 0;
    mComponentXform.mTranslation.x = g_defaultTranslation.x;
    mComponentXform.mTranslation.y = g_defaultTranslation.y;
    mComponentXform.mTranslation.z = g_defaultTranslation.z;
    mComponentXform.mScale = one;
    mComponentXform.mRotation.Assign(g_identityMatrix);
    mHasLOD = 0;
    float one2 = g_one;
    mLODSizeScale.x = one2; mLODSizeScale.y = one2;
    mAnimationInfo.mpBegin = 0; mAnimationInfo.mpEnd = 0; mAnimationInfo.mpCapacity = 0;
    mLODAlphaScale.x = one2; mLODAlphaScale.y = one2;
    mModelOverrideLo = 0xffffffffu;
    mModelOverrideHi = 0xffffffffu;
}

// @ 0x00aa2c60
void* cModelEffect::Destroy(uint32_t flags)
{
    mpVtbl = g_vtbl_cModelEffect;
    mpRefCountVtbl = g_vtbl_cModelEffectRefCount;
    _ReadWriteBarrier();
    if (mAnimationInfo.mpBegin != 0 && *(int*)((char*)mAnimationInfo.mpBegin - 4) != 0)
        operator_delete(mAnimationInfo.mpBegin);
    if (mRenderer != 0)
        mRenderer->Release();
    _ReadWriteBarrier();
    mpVtbl = g_vtbl_GmeIComponent;
    mpRefCountVtbl = g_vtbl_GmeRefCount;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00aa2cc0
void cModelEffect::SetTransforms(const cTransform& parent, const cTransform& src)
{
    cTransform tmp;
    tmp.mFlags = src.mFlags;
    tmp.mModCount = src.mModCount;
    tmp.mTranslation.x = src.mTranslation.x;
    tmp.mTranslation.y = src.mTranslation.y;
    tmp.mTranslation.z = src.mTranslation.z;
    tmp.mScale = src.mScale;
    tmp.mRotation.Assign(src.mRotation.m);
    tmp.PreTransformBy(parent);
    mComponentXform.Assign(&tmp);
    cIRenderer* r = mRenderer;
    if (r != 0)
        r->SetTransform(mModelID, &mComponentXform);
}

// @ 0x00aa2d80
void cModelEffect::Start(int unused)
{
    if (mActive)
        return;
    mActive = 1;
    int n = (int)((mDesc->mAnimationCurves.mpEnd - mDesc->mAnimationCurves.mpBegin) / 0x28);
    mAnimationInfo.resize((uint32_t)n);
    for (int i = 0; i < n; ++i) {
        cLODScales* info = mAnimationInfo.mpBegin + i;
        cAnimationCurve* curve = mDesc->mAnimationCurves.mpBegin + i;
        info->v0 = 0.0f;
        float lo = curve->mLengthRange.x;
        float hi = curve->mLengthRange.y;
        double r = g_sRandom_Swarm.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            hi = (float)v;
            if (v < lo)
                hi = lo;
        }
        if (hi <= 0.0f)
            info->v1 = 0.0f;
        else
            info->v1 = 1.0f / hi;
        float cv = curve->mCurveVary;
        double r2 = g_sRandom_Swarm.RandomDoubleUniform();
        double v2 = r2 * ((cv + 1.0) - (1.0 - cv)) + (1.0 - cv);
        float out = (float)v2;
        if (v2 < (cv + 1.0)) {
            out = (float)v2;
            if (v2 < (1.0 - cv))
                out = (float)(1.0 - cv);
        }
        info->v2 = out;
    }
    mLastLocation = mComponentXform.mTranslation;
    if (mRenderer != 0)
        mRenderer->SetVisible(mModelID, mIsVisible);
}
