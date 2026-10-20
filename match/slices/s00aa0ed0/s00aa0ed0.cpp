// Slice s00aa0ed0 -- EA::Swarm::cMetaParticlesEffect emission/update core and the
// cModelDescription animation-curve helpers (Swarm/MetaParticlesEffect.obj).
//
// Types are local retail-layout stubs: the dev PDB layout differs by the wider retail
// eastl vector (0x14 rather than 0x10), which is why several fields sit 4 bytes later.

typedef unsigned int uint32_t;

#pragma warning(disable:4035)
static __forceinline int CeilToInt(float x)
{
    __asm {
        movss xmm0, x
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov ecx, eax
        add ecx, 1
        ucomiss xmm1, xmm0
        cmovb eax, ecx
    }
}
static __forceinline int FloorToInt(float x)
{
    __asm {
        movss xmm0, x
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov ecx, eax
        sub ecx, 1
        ucomiss xmm0, xmm1
        cmovb eax, ecx
    }
}

// ------------------------------------------------------------------ external helpers
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);  // 0x011e0744
void __cdecl operator_delete(void*);                                 // 0x00f47380

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

struct cGlobalParams {
    char pad[0xbc];
    Vector3 mWind;                 // 0xbc
    char pad_c8[0x10];             // 0xc8..0xd7
    Vector3 mAmbient;              // 0xd8
};

struct cEffectParams {
    char pad[0x24];
    int mParticleCount;            // 0x24
};

// The retail eastl vector is 0x14 bytes (the allocator is 8 bytes wide).
template <class T>
struct sp_vector {
    T* mpBegin;                    // 0x00
    T* mpEnd;                      // 0x04
    T* mpCapacity;                 // 0x08
    int mAllocator[2];             // 0x0c
    void Allocate(int n, const int* alloc);                       // 0x004aa350
    sp_vector<T>& operator=(const sp_vector<T>&);                 // 0x0050d4e0
};

struct cAnimationCurve;
struct sp_vector_curve {
    cAnimationCurve* mpBegin;
    cAnimationCurve* mpEnd;
    cAnimationCurve* mpCapacity;
    int mAllocator[2];
    void DestroyRange(cAnimationCurve*, cAnimationCurve*);        // 0x00aa1c30
};

struct cAnimationCurve {                                       // size 0x28
    Vector2 mLengthRange;              // 0x00
    sp_vector<float> mCurve;           // 0x08
    float mCurveVary;                  // 0x1c
    float mSpeedScale;                 // 0x20
    char mChannel;                     // 0x24
    char mMode;                        // 0x25
    char pad26[2];
    cAnimationCurve* CopyFrom(const cAnimationCurve&);            // 0x00aa1cc0
    cAnimationCurve& operator=(const cAnimationCurve& src)
    {
        mLengthRange = src.mLengthRange;
        mCurve = src.mCurve;
        mCurveVary = src.mCurveVary;
        mSpeedScale = src.mSpeedScale;
        mChannel = src.mChannel;
        mMode = src.mMode;
        return *this;
    }
};

// Description: retail offsets observed in this slice.
struct cMetaParticlesDescription {
    void* mpVtbl;                      // 0x00
    int mRefCount;                     // 0x04
    uint32_t mFlags;                   // 0x08 (low 32 bits of bitset<40>)
    uint32_t mFlagsHi;                 // 0x0c
    Vector2 mParticleLifetime;         // 0x10
    float mPrerollTime;                // 0x18
    char pad1c[8];
    Vector2 mEmitRetrigger;            // 0x24
    char pad2c[0x3c];
    sp_vector<float> mRateCurve;       // 0x68
    float mRateCurveTime;              // 0x7c
    uint32_t mRateCurveCycles;         // 0x80
    char pad84[0xb4];
    Vector3 mGlobalForcesSum;          // 0x138
    char pad144[0xc];
    float mWindStrength;               // 0x150
    char pad154[0x12c];
    Vector3 mAttractorOrigin;          // 0x280
};

struct cTransform {
    unsigned short mFlags;             // 0x00
    unsigned short mModCount;          // 0x02
    Vector3 mTranslation;              // 0x04
    float mScale;                      // 0x10
    float mRotation[9];                // 0x14
    void TransformVector(Vector3*) const;                        // 0x007cdee0
};

struct cRWState {
    char pad[0x18];
    void AccumulateForce(Vector3*);                                // 0x00a79300
};

struct cSurfaceHandler {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
    virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7();
    virtual void h8(void*, cTransform*, cTransform*, unsigned char*);
};
struct cSurfaceRec {
    cSurfaceHandler* mpHandler;        // 0x00
    void* mpArg;                       // 0x04
    char pad08[4];
    int mOffset;                       // 0x0c
    char pad10[8];                     // 0x10
};

struct cMetaParticle {
    cMetaParticle* mpNext;             // 0x00
    cMetaParticle* mpPrev;             // 0x04
};

// cEffectsWorld: only the slots used here (0x2c = GetGlobalParams, 0x30 = GetWorld).
struct cEffectsWorld {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9(); virtual void w10();
    virtual cGlobalParams* GetGlobalParams();                      // slot 11, +0x2c
    virtual cEffectsWorld* GetWorld();                             // slot 12, +0x30
};

struct CRandom {
    double RandomDoubleUniform();                                  // 0x009360d0
};
extern CRandom g_sRandom_Swarm;                                    // 0x016778dc
extern void* g_vtbl_GmeRefCount[];                                 // 0x013ef094

#pragma pack(push, 4)
class cMetaParticlesEffect {
public:
    virtual void v0();  virtual void v1();  virtual void v2();
    virtual void Stop(int);                                        // slot 3, +0x0c
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();

    // data at observed retail offsets
    char pad04[8];
    cMetaParticlesDescription* mDesc;      // 0x0c
    int mCollectionIndex;                  // 0x10
    cEffectsWorld* mWorld;                 // 0x14
    cGlobalParams* mGlobalParams;          // 0x18
    cEffectParams* mParentParams;          // 0x1c
    bool mIsRunning;                       // 0x20
    bool mDelayedStopActive;               // 0x21
    bool mIsVisible;                       // 0x22
    char pad23[1];
    cMetaParticle mParticles;              // 0x24 (head node)
    int mParticleCount;                    // 0x2c
    cTransform mSourceTransform;           // 0x30
    cTransform mRigidTransform;            // 0x68
    double mOverallTime;                   // 0xa0
    bool mPreroll;                         // 0xa8
    char padA9[7];
    double mParticleSystemTime;            // 0xb0
    uint32_t mCurrentCycle;                // 0xb8
    char padBC[4];
    double mInverseRateCurveTime;          // 0xc0
    float mParticlesToGenerate;            // 0xc8
    Vector3 mDirectionalForcesSum;         // 0xcc
    cRWState mRandomWalkStates[2];         // 0xd8
    bool mRWHasPreferredDirection;         // 0x108
    char pad109[3];
    float mRWPrefTheta;                    // 0x10c
    float mRWPrefGamma;                    // 0x110
    Vector3 mAttractorLocation;            // 0x114
    float mAttractorIntensity;             // 0x120
    char pad124[8];
    float mRetriggerTime;                  // 0x12c
    char pad130[0x10];
    float mParamEmitScale;                 // 0x140
    char pad144[4];
    float mParamSizeScale;                 // 0x148
    float mParamAlphaScale;                // 0x14c
    Vector3 mParamColorScale;              // 0x150
    char pad15c[8];
    Vector2 mLODEmitScale;                 // 0x164
    Vector2 mLODSizeScale;                 // 0x16c
    Vector2 mLODAlphaScale;                // 0x174
    float mCurrentEmitScale;               // 0x17c
    float mCurrentSizeScale;               // 0x180
    float mCurrentAlphaScale;              // 0x184
    Vector3 mCurrentColorScale;            // 0x188
    char pad194[0x28];
    cSurfaceRec* mSurfaceRecsBegin;        // 0x1bc
    cSurfaceRec* mSurfaceRecsEnd;          // 0x1c0
    char pad1c4[0xc];
    bool mSurfaceStateDataValid;           // 0x1d0
    char pad1d1[3];
    unsigned char* mSurfaceStateDataBegin; // 0x1d4
    unsigned char* mSurfaceStateDataEnd;   // 0x1d8
    char pad1dc[0x6c];
    cMetaParticlesEffect* mChainSystem;    // 0x248
    bool mSuppressEmission;                // 0x24c
    char pad24d[3];
    void** mSpawnedEffectsBegin;           // 0x250
    void** mSpawnedEffectsEnd;             // 0x254

    // callees (other translation units / later in the object)
    void ClearParticles();                                         // 0x00aa0a90
    cMetaParticle* NewParticle();                                  // 0x00aa09e0
    bool InitParticle(cMetaParticle*);                             // 0x00a9ddd0
    bool UpdateParticle(cMetaParticle*, float);                    // 0x00a9dc00
    void FreeParticle(cMetaParticle*);                             // 0x00aa06b0
    void UpdateParticles(float, float, cEffectParams*);            // 0x00a9f170
    void FinishParticles();                                        // 0x00aa0600
    void UpdateAge(float);                                         // 0x00a9ae00
    void RebindWorld(cEffectsWorld*);                              // 0x00aa0ba0

    void Init(cEffectsWorld*, cEffectsWorld*, cEffectParams*);     // 0x00aa15c0
    void SetDescription(cMetaParticlesDescription*);               // 0x00aa15f0
    void ApplyEffect(float, float, cEffectParams*);                // 0x00aa1610
    void EmitDefault(float);                                       // 0x00aa0ed0
    void EmitRate(float);                                          // 0x00aa1290
    void EmitBurst(float);                                         // 0x00aa14f0
    void InsertParticle(cMetaParticle*);
    void SpawnOne(float);
};
#pragma pack(pop)

// cModelDescription destructor owner (vector of curves at +0x2c).
struct cModelDescription {
    void* mpVtbl;                          // 0x00
    char pad04[0x28];
    sp_vector_curve mAnimationCurves;      // 0x2c
    void* Destroy(unsigned int flags);     // 0x00aa1c70
};

// ------------------------------------------------------------------ particle helpers
void cMetaParticlesEffect::InsertParticle(cMetaParticle* p)
{
    p->mpNext = mParticles.mpNext;
    p->mpPrev = &mParticles;
    mParticles.mpNext = p;
    p->mpNext->mpPrev = p;
    ++mParticleCount;
}

void cMetaParticlesEffect::SpawnOne(float t)
{
    cMetaParticle* p = NewParticle();
    if (!InitParticle(p) || !UpdateParticle(p, t)) {
        FreeParticle(p);
    } else {
        InsertParticle(p);
    }
}

// @ 0x00aa15c0
void cMetaParticlesEffect::Init(cEffectsWorld* world, cEffectsWorld* concrete, cEffectParams* params)
{
    mWorld = world;
    mGlobalParams = world->GetGlobalParams();
    mParentParams = params;
    RebindWorld(concrete);
}

// @ 0x00aa15f0
void cMetaParticlesEffect::SetDescription(cMetaParticlesDescription* desc)
{
    mDesc = desc;
    RebindWorld(mWorld->GetWorld());
}

// @ 0x00aa1c70
void* cModelDescription::Destroy(unsigned int flags)
{
    mAnimationCurves.DestroyRange(mAnimationCurves.mpBegin, mAnimationCurves.mpEnd);
    cAnimationCurve* p = mAnimationCurves.mpBegin;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        operator_delete(p);
    *(void**)this = g_vtbl_GmeRefCount;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00aa1cc0
cAnimationCurve* cAnimationCurve::CopyFrom(const cAnimationCurve& src)
{
    mLengthRange.x = src.mLengthRange.x;
    mLengthRange.y = src.mLengthRange.y;
    int n = (int)(src.mCurve.mpEnd - src.mCurve.mpBegin);
    mCurve.Allocate(n, src.mCurve.mAllocator);
    unsigned int bytes = (unsigned int)((char*)src.mCurve.mpEnd - (char*)src.mCurve.mpBegin);
    mCurve.mpEnd = (float*)memmove(mCurve.mpBegin, src.mCurve.mpBegin, bytes) + n;
    mCurveVary = src.mCurveVary;
    mSpeedScale = src.mSpeedScale;
    mChannel = src.mChannel;
    mMode = src.mMode;
    return this;
}

// @ 0x00aa1db0
cAnimationCurve* CopyCurveRange(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dst)
{
    while (first != last) {
        *dst = *first;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00aa1e10
void FillCurveRange(cAnimationCurve* first, cAnimationCurve* last, const cAnimationCurve* value)
{
    while (first != last) {
        *first = *value;
        ++first;
    }
}

// @ 0x00aa1e60
cAnimationCurve* CopyCurveRangeBackward(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dstEnd)
{
    while (last != first) {
        --last;
        --dstEnd;
        *dstEnd = *last;
    }
    return dstEnd;
}

// ------------------------------------------------------------------ emission modes
// @ 0x00aa14f0
void cMetaParticlesEffect::EmitBurst(float dt)
{
    double t = (double)dt * mInverseRateCurveTime + mParticleSystemTime;
    mParticleSystemTime = t;
    if ((double)mCurrentCycle > t)
        return;

    float rate = mDesc->mRateCurve.mpBegin[0];
    int n = CeilToInt(rate) - mParticleCount;

    while (n > 0) {
        SpawnOne(dt);
        --n;
    }
}

// @ 0x00aa1290
void cMetaParticlesEffect::EmitRate(float dt)
{
    double t = (double)dt * mInverseRateCurveTime + mParticleSystemTime;
    mParticleSystemTime = t;
    if ((double)mCurrentCycle > t)
        return;

    float rate = mCurrentEmitScale * mDesc->mRateCurve.mpBegin[0];
    int count = CeilToInt(rate);

    if ((double)mCurrentCycle <= mParticleSystemTime) {
        for (;;) {
            if ((mDesc->mFlags >> 30) & 1)
                ClearParticles();

            float cycleTime = (float)((mParticleSystemTime - (double)mCurrentCycle) *
                                      (double)mDesc->mRateCurveTime);
            if (cycleTime < mDesc->mParticleLifetime.y && count > 0) {
                int i = count;
                do {
                    SpawnOne(cycleTime);
                } while (--i);
            }

            ++mCurrentCycle;
            if (mDesc->mRateCurveCycles != 0 && mCurrentCycle >= mDesc->mRateCurveCycles) {
                if ((mDesc->mFlags >> 31) & 1)
                    return;
                Stop(0);
                return;
            }

            if (mDesc->mEmitRetrigger.x >= 0.0f) {
                double lo = mDesc->mEmitRetrigger.x;
                double hi = mDesc->mEmitRetrigger.y;
                double r = g_sRandom_Swarm.RandomDoubleUniform();
                double vary = r * (hi - lo) + lo;
                if (vary < hi) {
                    hi = vary;
                    if (vary < lo)
                        hi = lo;
                }
                mParticleSystemTime -= hi * mInverseRateCurveTime;
                if (mParticleSystemTime < (double)mCurrentCycle) {
                    mRetriggerTime = (float)(((double)mCurrentCycle - mParticleSystemTime) *
                                             (double)mDesc->mRateCurveTime);
                    mParticleSystemTime = (double)mCurrentCycle;
                    return;
                }
            }

            if (mParticleSystemTime < (double)mCurrentCycle)
                return;
        }
    }
}

// @ 0x00aa0ed0
void cMetaParticlesEffect::EmitDefault(float dt)
{
    uint32_t flags = mDesc->mFlags;
    float emitScale = mCurrentEmitScale;
    float s = mSourceTransform.mScale;
    if ((flags >> 8) & 1)
        emitScale = s * emitScale;
    else if ((flags >> 9) & 1)
        emitScale = (s * s) * emitScale;
    else if ((flags >> 10) & 1)
        emitScale = ((s * s) * s) * emitScale;

    bool retriggered = false;
    float remaining = dt;
    for (;;) {
        float step = remaining;
        if (step > 0.06666667f)
            step = 0.06666667f;

        uint32_t nextCycle = mCurrentCycle + 1;
        double t = (double)step * mInverseRateCurveTime + mParticleSystemTime;
        mParticleSystemTime = t;

        if ((double)nextCycle < t) {
            mCurrentCycle = nextCycle;
            if (flags & (1u << 30))
                ClearParticles();

            if (mDesc->mRateCurveCycles != 0 && mCurrentCycle == mDesc->mRateCurveCycles) {
                if (flags & (1u << 2)) {
                    mCurrentCycle = mDesc->mRateCurveCycles - 1;
                    mParticleSystemTime = (double)((float)mDesc->mRateCurveCycles - 1e-6f);
                } else {
                    if ((int)flags < 0)
                        return;
                    Stop(0);
                    return;
                }
            } else if (mDesc->mEmitRetrigger.x >= 0.0f) {
                retriggered = true;
                remaining = (float)((double)step -
                                    (mParticleSystemTime - (double)mCurrentCycle) *
                                    (double)mDesc->mRateCurveTime);
                mParticleSystemTime = (double)mCurrentCycle;
            }
        }

        int segments = (int)(mDesc->mRateCurve.mpEnd - mDesc->mRateCurve.mpBegin) - 1;
        float curve;
        if (segments == 0) {
            curve = mDesc->mRateCurve.mpBegin[0];
        } else {
            float u = ((float)mParticleSystemTime - (float)mCurrentCycle) * (float)segments;
            int idx = (int)u;
            float frac = u - (float)idx;
            if (frac <= 0.0f)
                curve = mDesc->mRateCurve.mpBegin[idx];
            else
                curve = (mDesc->mRateCurve.mpBegin[idx + 1] - mDesc->mRateCurve.mpBegin[idx]) * frac +
                        mDesc->mRateCurve.mpBegin[idx];
        }

        float acc = (curve * step) * emitScale + mParticlesToGenerate;
        mParticlesToGenerate = acc;
        int n = FloorToInt(acc);
        mParticlesToGenerate = acc - (float)n;

        float age = dt;
        if (n > 0) {
            float sub = step / (float)n;
            int i = n;
            do {
                SpawnOne(age);
                age -= sub;
            } while (--i);
        }

        remaining -= step;

        if (retriggered) {
            float x = mDesc->mEmitRetrigger.x;
            float y = mDesc->mEmitRetrigger.y;
            double r = g_sRandom_Swarm.RandomDoubleUniform();
            float vary = (float)(r * (double)(y - x) + (double)x);
            if (vary < x)
                vary = x;
            else if (vary > y)
                vary = y;
            remaining -= vary;
            if (remaining < 0.0f) {
                mRetriggerTime = -remaining;
                return;
            }
        }

        if (remaining <= 0.0f)
            return;
    }
}

// @ 0x00aa1610
void cMetaParticlesEffect::ApplyEffect(float dt, float lerp, cEffectParams* params)
{
    if (mPreroll) {
        dt += mDesc->mPrerollTime;
        mPreroll = false;
    }

    if (((mDesc->mFlags >> 31) & 1) && !mDelayedStopActive) {
        float maxDt = (float)((1.0 - mParticleSystemTime) * (double)mDesc->mRateCurveTime - 0.01f);
        if (maxDt > 0.0f) {
            if (dt > maxDt)
                dt = maxDt;
        } else {
            dt = 0.0f;
        }
    }

    mOverallTime = (double)(dt + (float)mOverallTime);

    mCurrentEmitScale = ((mLODEmitScale.y - mLODEmitScale.x) * lerp +
                         mLODEmitScale.x) * mParamEmitScale;
    mCurrentSizeScale = ((mLODSizeScale.y - mLODSizeScale.x) * lerp +
                         mLODSizeScale.x) * mParamSizeScale;
    mCurrentAlphaScale = ((mLODAlphaScale.y - mLODAlphaScale.x) * lerp +
                          mLODAlphaScale.x) * mParamAlphaScale;
    mCurrentColorScale = mParamColorScale;

    if ((mDesc->mFlags >> 24) & 1) {
        mAttractorLocation = mDesc->mAttractorOrigin;
        mSourceTransform.TransformVector(&mAttractorLocation);
        mAttractorIntensity = 1.0f;
    }

    float wind = mDesc->mWindStrength;
    mDirectionalForcesSum.x = mGlobalParams->mWind.x * wind;
    mDirectionalForcesSum.y = mGlobalParams->mWind.y * wind;
    mDirectionalForcesSum.z = mGlobalParams->mWind.z * wind;

    if (mRigidTransform.mScale != 1.0f) {
        float inv = 1.0f / mRigidTransform.mScale;
        mDirectionalForcesSum.x *= inv;
        mDirectionalForcesSum.y *= inv;
        mDirectionalForcesSum.z *= inv;
    }

    if (mRigidTransform.mFlags & 2) {
        float x = mDirectionalForcesSum.x;
        float y = mDirectionalForcesSum.y;
        float z = mDirectionalForcesSum.z;
        mDirectionalForcesSum.x = mRigidTransform.mRotation[0] * x +
                                  (mRigidTransform.mRotation[1] * y + mRigidTransform.mRotation[2] * z);
        mDirectionalForcesSum.y = mRigidTransform.mRotation[3] * x +
                                  (mRigidTransform.mRotation[4] * y + mRigidTransform.mRotation[5] * z);
        mDirectionalForcesSum.z = mRigidTransform.mRotation[6] * x +
                                  (mRigidTransform.mRotation[7] * y + mRigidTransform.mRotation[8] * z);
    }

    mDirectionalForcesSum.x += mDesc->mGlobalForcesSum.x;
    mDirectionalForcesSum.y += mDesc->mGlobalForcesSum.y;
    mDirectionalForcesSum.z += mDesc->mGlobalForcesSum.z;

    if ((mDesc->mFlags >> 19) & 1) {
        mRandomWalkStates[0].AccumulateForce(&mDirectionalForcesSum);
        mRandomWalkStates[1].AccumulateForce(&mDirectionalForcesSum);
    }

    if (mSurfaceStateDataBegin != mSurfaceStateDataEnd && !mSurfaceStateDataValid) {
        for (cSurfaceRec* rec = mSurfaceRecsBegin; rec != mSurfaceRecsEnd; ++rec)
            rec->mpHandler->h8(rec->mpArg, &mSourceTransform, &mRigidTransform,
                               mSurfaceStateDataBegin + rec->mOffset);
        mSurfaceStateDataValid = true;
    }

    cMetaParticle* p = mParticles.mpNext;
    while (p != &mParticles) {
        if (UpdateParticle(p, dt)) {
            p = p->mpNext;
        } else {
            cMetaParticle* next = p->mpNext;
            p->mpPrev->mpNext = p->mpNext;
            p->mpNext->mpPrev = p->mpPrev;
            p->mpNext = 0;
            p->mpPrev = 0;
            FreeParticle(p);
            --mParticleCount;
            p = next;
        }
    }

    if (!mDelayedStopActive && !mSuppressEmission) {
        float local = dt;
        if (mRetriggerTime > 0.0f) {
            local = mRetriggerTime - dt;
            mRetriggerTime = local;
            if (local > 0.0f)
                goto tail;
            local = -local;
        }
        float preroll = mDesc->mPrerollTime;
        if (preroll > 0.01f) {
            preroll -= 0.01f;
            if (local > preroll)
                local = preroll;
        }
        if ((mDesc->mFlags >> 1) & 1)
            EmitBurst(local);
        else if (mDesc->mFlags & 1)
            EmitRate(local);
        else
            EmitDefault(local);
    }

tail:
    UpdateParticles(dt, lerp, params);
    FinishParticles();

    if (mDelayedStopActive && mParticleCount == 0 && mSpawnedEffectsBegin == mSpawnedEffectsEnd) {
        mIsRunning = false;
        if (mChainSystem != 0) {
            mChainSystem->Stop(0);
            return;
        }
        return;
    }

    if ((mDesc->mFlags >> 19) & 1)
        UpdateAge(dt);
    params->mParticleCount += mParticleCount;
}
