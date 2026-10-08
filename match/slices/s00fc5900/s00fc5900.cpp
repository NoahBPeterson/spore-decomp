// Slice s00fc5900: SP::cWeatherManager::UpdateEffects (0x00fc5f80, name guessed; 1713 bytes,
// __thiscall, no arguments). Per-frame update of the weather visual effects.
//
// Does nothing until the weather is initialised and its effects are loaded. Then:
//  - when the temperature phase changed (or the ambient loop-box effect died) it stops the ambient
//    loop-box / screen-ambient / storm effects and re-creates the ambient loop-box effect for
//    mCurrentAmbientID (weather level 2 only);
//  - when the terraform state changed it pushes the new state (0 = ice/cold, 1 = normal, 2 = hot)
//    into every atmosphere effect and returns;
//  - otherwise it picks the cloud colour for the current temperature (darkened as the atmosphere
//    score rises above 0.5), starts / stops the evaporation or freeze transition effect when the
//    temperature moved, eases mPreviousAtmo towards the atmosphere score, and feeds transparency,
//    emit scale, particle size and map-force parameters (and the colour) into the effects.
//
// Retail layout from ModAPI Terrain/cWeatherManager.h (names from the 2008 PDB cWeatherManager).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

#pragma warning(disable : 4035)

// ---- /arch:SSE float helpers (the original used asm helpers with minss/maxss) ----
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
__forceinline float Min(float value, float maxValue)
{
    __asm {
        movss xmm0, value
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct Vec3 { float x, y, z; };
struct SVec3 : Vec3 {               // cSPVector3: user copy ctor (movss copies)
    SVec3() {}
    SVec3(const SVec3& o) { x = o.x; y = o.y; z = o.z; }
    SVec3(float a, float b, float c) { x = a; y = b; z = c; }
};

// Swarm::IVisualEffect (vtable slots from the ModAPI headers)
struct IVisualEffect {
    virtual int AddRef();                                         // +0x00
    virtual int Release();                                        // +0x04
    virtual void Start(int hard);                                 // +0x08
    virtual int Stop(int hard);                                   // +0x0c
    virtual bool IsRunning();                                      // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual bool SetVectorParams(int param, const Vec3* data, int count);   // +0x40
    virtual bool SetFloatParams(int param, const float* data, int count);   // +0x44
    virtual bool SetIntParams(int param, const int* data, int count);       // +0x48
};
struct IEffectsWorld {
    virtual void v00(); virtual void v04();
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst);   // +0x08
};

template <class T> struct ARef {                                  // EA::AutoRefCount
    T* mp;
    __forceinline void Reset()
    {
        T* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
    __declspec(noinline) T** AsPPTypeParam()                      // 0x00a16f40: releases, returns &mp
    {
        T* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
        return &mp;
    }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};

enum FloatParam { kEmitScale = 3, kTransparency = 4, kColor = 5, kParticleSizeScale = 1, kMapForceScale = 0x12 };
enum IntParam { kSelectState = 3 };

namespace SP {

class cWeatherManager {
public:
    void UpdateEffects();                                         // 0x00fc5f80
    SVec3* GetCloudColor(SVec3* out, float temperature);            // 0x00fc3e30

    uint32_t pad00[3];
    ARef<IEffectsWorld> mEffectsWorld;                            // +0x0c
    uint32_t pad10;
    ARef<IVisualEffect> mLowAtmoEffect;                           // +0x14
    ARef<IVisualEffect> mMidAtmoEffect;                           // +0x18
    ARef<IVisualEffect> mHighAtmoEffect;                          // +0x1c
    ARef<IVisualEffect> mLoopBoxAtmoEffect;                       // +0x20
    ARef<IVisualEffect> mLoopBoxGroundEffect;                     // +0x24
    ARef<IVisualEffect> mLoopBoxAmbientEffect;                    // +0x28
    uint32_t pad2c;
    ARef<IVisualEffect> mScreenAmbientEffect;                     // +0x30
    ARef<IVisualEffect> mTransitionEffect;                        // +0x34
    uint32_t pad38[(0x44 - 0x38) / 4];
    uint32_t mCurrentAmbientID;                                   // +0x44
    uint32_t pad48[(0xa0 - 0x48) / 4];
    uint32_t mTransitionEffectID;                                 // +0xa0
    uint32_t mEvaporationEffectID;                                // +0xa4
    uint32_t mFreezeEffectID;                                     // +0xa8
    bool mEffectsStarted;                                         // +0xac
    bool mIsInitialized;                                          // +0xad
    uint16_t padae;
    int mWeatherLevel;                                            // +0xb0
    uint32_t padb4[(0xec - 0xb4) / 4];
    float mTemperature;                                           // +0xec
    float mAtmoScore;                                             // +0xf0
    float mWaterLevel;                                            // +0xf4
    float mPreviousTemp;                                          // +0xf8
    float mPreviousAtmo;                                          // +0xfc
    uint32_t pad100[(0x13c - 0x100) / 4];
    int mPreviousTerraformState;                                  // +0x13c
    int mCurrentTerraformState;                                   // +0x140
    uint32_t pad144[(0x150 - 0x144) / 4];
    int mPreviousTempPhase;                                       // +0x150
    int mCurrentTempPhase;                                        // +0x154
    uint32_t pad158[(0x16c - 0x158) / 4];
    bool mControlMapsNeedUpdate;                                  // +0x16c
    bool mControlMapsInited;                                      // +0x16d
    uint16_t pad16e;
    ARef<IVisualEffect>* mStormBegin;                             // +0x170
    ARef<IVisualEffect>* mStormEnd;                               // +0x174
    uint32_t pad178[(0x190 - 0x178) / 4];
    float mAtmoTempChange;                                        // +0x190
};

static inline SVec3* Addr(SVec3& r) { return &r; }
static inline SVec3 Scale(const SVec3& c, float f)
{
    return SVec3(c.x * f, c.y * f, c.z * f);
}

static inline int TerraformStateParam(int state)
{
    int v = 1;
    if (state == 0 || state == 3 || state == 6)
        v = 0;
    else if (state == 2 || state == 5 || state == 8)
        v = 2;
    return v;
}

extern float kHalf;          // 0x01471064 (0.5)
extern float kAtmoDarken;    // 0x015b1718

// @ 0x00fc5f80
void cWeatherManager::UpdateEffects()
{
    if (!mControlMapsInited || !mIsInitialized || !mEffectsStarted)
        return;
    {
        bool needsRecreate;
        if ((mLoopBoxAmbientEffect.mp == 0 || mLoopBoxAmbientEffect->IsRunning()) && mLoopBoxAmbientEffect.mp != 0)
            needsRecreate = false;
        else
            needsRecreate = true;

        if (mPreviousTempPhase != mCurrentTempPhase || needsRecreate) {
            if (mLoopBoxAmbientEffect.mp) {
                mLoopBoxAmbientEffect->Stop(0);
                mLoopBoxAmbientEffect.Reset();
            }
            if (mScreenAmbientEffect.mp) {
                mScreenAmbientEffect->Stop(0);
                mScreenAmbientEffect.Reset();
            }
            for (ARef<IVisualEffect>* it = mStormBegin; it != mStormEnd; ++it)
                (*it)->Stop(0);
            if (mCurrentAmbientID != 0 && mWeatherLevel == 2) {
                ARef<IVisualEffect>* slot = &mLoopBoxAmbientEffect;
                IEffectsWorld* world = mEffectsWorld;
                slot->Reset();
                if (world->CreateVisualEffect(mCurrentAmbientID, 0, &slot->mp))
                    slot->mp->Start(0);
            }
        }

        int state = mCurrentTerraformState;
        if (mPreviousTerraformState != state) {
            int v = TerraformStateParam(state);
            if (mLowAtmoEffect.mp)
                mLowAtmoEffect->SetIntParams(kSelectState, &v, 1);
            if (mMidAtmoEffect.mp)
                mMidAtmoEffect->SetIntParams(kSelectState, &v, 1);
            if (mHighAtmoEffect.mp)
                mHighAtmoEffect->SetIntParams(kSelectState, &v, 1);
            if (mLoopBoxAtmoEffect.mp)
                mLoopBoxAtmoEffect->SetIntParams(kSelectState, &v, 1);
            if (mLoopBoxGroundEffect.mp)
                mLoopBoxGroundEffect->SetIntParams(kSelectState, &v, 1);
            for (ARef<IVisualEffect>* it = mStormBegin; it != mStormEnd; ++it)
                (*it)->SetIntParams(kSelectState, &v, 1);
            mPreviousTerraformState = mCurrentTerraformState;
            return;
        }

        float temp = mTemperature;
        SVec3 color(*GetCloudColor(Addr(SVec3()), temp));
        float* pAtmo = &mAtmoScore;
        float f = 1.0f - (mAtmoScore - kHalf) * kAtmoDarken;
        if (mAtmoScore > kHalf) {
            color = Scale(color, f);
        }

        if (mPreviousTemp != temp) {
            uint32_t id = mEvaporationEffectID;
            if (temp < mPreviousTemp)
                id = mFreezeEffectID;
            if (id != 0) {
                ARef<IVisualEffect>* slot = &mTransitionEffect;
                if (slot->mp == 0) {
                    IEffectsWorld* world = mEffectsWorld;
                    if (world->CreateVisualEffect(id, 0, slot->AsPPTypeParam())) {
                        slot->mp->Start(0);
                        mTransitionEffectID = id;
                    }
                } else if (id != mTransitionEffectID) {
                    slot->mp->Stop(0);
                    slot->Reset();
                    IEffectsWorld* world = mEffectsWorld;
                    if (world->CreateVisualEffect(id, 0, slot->AsPPTypeParam())) {
                        slot->mp->Start(0);
                        mTransitionEffectID = id;
                    }
                }
            }
        } else {
            if (mTransitionEffect.mp) {
                mTransitionEffect->Stop(0);
                mTransitionEffect.Reset();
            }
        }

        float atmo = *pAtmo;
        float prev = mPreviousAtmo;
        if (prev != atmo) {
            prev = (atmo - prev) * mAtmoTempChange + prev;
            mPreviousAtmo = prev;
            float half = atmo + kHalf;
            if (fabsf(atmo - prev) < 0.0001f)
                mPreviousAtmo = atmo;
            float clamped = Clamp(half, 0.0f, 1.0f);
            float twice = *pAtmo * 2.0f;
            if (mLowAtmoEffect.mp) {
                mLowAtmoEffect->SetFloatParams(kTransparency, pAtmo, 1);
                mLowAtmoEffect->SetFloatParams(kEmitScale, &clamped, 1);
                if (*pAtmo > kHalf) {
                    mLowAtmoEffect->SetFloatParams(kParticleSizeScale, &half, 1);
                    mLowAtmoEffect->SetFloatParams(kMapForceScale, &twice, 1);
                }
            }
            if (mMidAtmoEffect.mp) {
                mMidAtmoEffect->SetFloatParams(kTransparency, pAtmo, 1);
                mMidAtmoEffect->SetFloatParams(kEmitScale, &clamped, 1);
                if (*pAtmo > kHalf) {
                    mMidAtmoEffect->SetFloatParams(kParticleSizeScale, &half, 1);
                    mMidAtmoEffect->SetFloatParams(kMapForceScale, &twice, 1);
                }
            }
            if (mHighAtmoEffect.mp) {
                mHighAtmoEffect->SetFloatParams(kTransparency, pAtmo, 1);
                mHighAtmoEffect->SetFloatParams(kEmitScale, &clamped, 1);
                if (*pAtmo > kHalf) {
                    mHighAtmoEffect->SetFloatParams(kParticleSizeScale, &half, 1);
                    mHighAtmoEffect->SetFloatParams(kMapForceScale, &twice, 1);
                }
            }
            if (mLoopBoxAtmoEffect.mp) {
                mLoopBoxAtmoEffect->SetFloatParams(kTransparency, pAtmo, 1);
                mLoopBoxAtmoEffect->SetFloatParams(kEmitScale, pAtmo, 1);
            }
            if (mLoopBoxGroundEffect.mp) {
                mLoopBoxGroundEffect->SetFloatParams(kTransparency, pAtmo, 1);
                mLoopBoxGroundEffect->SetFloatParams(kEmitScale, &clamped, 1);
            }
            if (mLoopBoxAmbientEffect.mp)
                mLoopBoxAmbientEffect->SetFloatParams(kTransparency, pAtmo, 1);
            for (ARef<IVisualEffect>* it = mStormBegin; it != mStormEnd; ++it) {
                IVisualEffect* fx = it->mp;
                float v = Min(*pAtmo * 2.0f, 1.0f);
                fx->SetFloatParams(kTransparency, &v, 1);
                fx->SetFloatParams(kEmitScale, &clamped, 1);
            }
        }

        if (mLowAtmoEffect.mp)
            mLowAtmoEffect->SetVectorParams(kColor, &color, 1);
        if (mMidAtmoEffect.mp)
            mMidAtmoEffect->SetVectorParams(kColor, &color, 1);
        if (mHighAtmoEffect.mp)
            mHighAtmoEffect->SetVectorParams(kColor, &color, 1);
    }
}

}  // namespace SP
