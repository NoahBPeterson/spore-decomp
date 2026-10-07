// slice s00a721a0: 0x00a721a0, an EA::Swarm effects-world update (dev-PDB caller hint:
// EA::Swarm::cEffectsWorld::DoUpdate; the class/field names below are Claude-coined).
// Pass 1 picks each active effect's LOD state (from distance or a view/direction score) and the blend
// inside it; pass 2 bends the three view lights toward each visible effect, then updates it.
// Passes repeat over effects appended while updating (0x00a711c0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    float Dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
};

// SSE clamp helper written in inline asm in the original (memory operands, no 16-byte frame alignment)
inline float Clamp(float v, float lo, float hi) {
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

inline bool IsNaN(float f) {
    return (*(uint32_t*)&f & 0x7fffffff) > 0x7f800000;
}

struct EffectDesc {
    uint32_t mFlags;            // 0x00
    uint32_t mGroupMask;        // 0x04
    char pad8[0x1c - 8];
    float* mLodBegin;           // 0x1c  eastl::vector<float> LOD thresholds
    float* mLodEnd;             // 0x20
    char pad24[0x30 - 0x24];
    float mViewWeight;          // 0x30
    float mFacingWeight;        // 0x34
    float mDistWeight;          // 0x38
};

struct EffectUpdater {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Update(float t, float dt, int* count);   // 0x14
};

struct ViewLight {   // 0x1c
    Vector3 mDir;    // 0x00
    float mBend;     // 0x0c
    Vector3 mPos;    // 0x10
};

struct EffectView {   // 0x120 bytes, copied whole from the settings
    char pad0[0x14];
    int mMaxEffects;          // 0x14
    char pad18[0x68 - 0x18];
    Vector3 mViewDir;         // 0x68
    char pad74[0x8c - 0x74];
    Vector3 mCameraPos;       // 0x8c
    char pad98[0xb0 - 0x98];
    bool mbLit;               // 0xb0
    char padb1[0xbc - 0xb1];
    ViewLight mLights[3];     // 0xbc
    char pad110[0x120 - 0x110];
};

struct EffectSettings {
    char pad0[0x4c];
    int mTransitionMode;      // 0x4c
    char pad50[0x64 - 0x50];
    float mLodScale;          // 0x64
    uint32_t mGroupsVersion;  // 0x68
    char pad6c[0xd0 - 0x6c];
    EffectView mView;         // 0xd0
};

struct Effect {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool IsVisible();                                   // 0x10
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual void SetParameter(int id, const void* value, int type);   // 0x40
    EffectUpdater mUpdater;      // 0x04
    char pad8[0x24 - 8];
    int mStartMode;              // 0x24
    EffectDesc* mpDesc;          // 0x28
    uint32_t mFlags;             // 0x2c
    Vector3 mPosition;           // 0x30
    Vector3 mDirection;          // 0x3c
    int mLod;                    // 0x48
    float mLodBlend;             // 0x4c
    float mLodMin;               // 0x50
    float mLodMax;               // 0x54
    float mLodBias;              // 0x58
    void UpdateTransforms();     // 0x00a82d90
};

struct EffectSink {
    virtual void v0(); virtual void v1();
    virtual void Prepare(EffectView* view);   // 0x08
};

struct cEffectsWorld {
    char pad0[0x10];
    int mMode;                   // 0x10
    EffectSettings* mpSettings;  // 0x14
    EffectView* mpView;          // 0x18
    EffectSink* mpSink;          // 0x1c
    int mState;                  // 0x20
    char pad24[4];
    int mTimeSource;             // 0x28
    uint32_t mGroupsVersion;     // 0x2c
    Effect** mpEffects;          // 0x30
    char pad34[0x44 - 0x34];
    int* mPendingBegin;          // 0x44
    int* mPendingEnd;            // 0x48
    char pad4c[0x58 - 0x4c];
    int* mActiveBegin;           // 0x58
    int* mActiveEnd;             // 0x5c
    char pad60[0x80 - 0x60];
    int mGlobalLod;              // 0x80
    char pad84[4];
    float mGlobalLodPos;         // 0x88
    char pad8c[4];
    int mUpdatedCount;           // 0x90

    void UpdateView();                                  // 0x00a6ff50
    void SetEffectLod(Effect* e, int lod, int mode);    // 0x00a71a00
    void AddPendingEffects(int flag);                   // 0x00a711c0
    void FinishUpdate();                                // 0x00a70a40

    __forceinline int TransitionMode(Effect* e) {
        uint32_t f = e->mpDesc->mFlags;
        if (f & 0x100000) return 1;
        if (f & 0x200000) return 0;
        return mpSettings->mTransitionMode;
    }
    __forceinline int LodTransitionMode(Effect* e) {
        if (e->mLod == 0) return e->mStartMode;
        return TransitionMode(e);
    }
    __forceinline int ActiveCount() {
        int n = (int)(mActiveEnd - mActiveBegin);
        int max = mpView->mMaxEffects;
        if (max > 0 && n > max) n = max;
        return n;
    }
    void Update(float t1, float t2, int* count);
};

static inline void BendLight(ViewLight& l, const Vector3& base, const Vector3& pos) {
    Vector3 d = l.mPos - pos;
    float inv = 1.0f / (float)sqrt(d.x * d.x + d.z * d.z + d.y * d.y + 1e-8f);
    l.mDir = base + d * inv * l.mBend;
}

void cEffectsWorld::Update(float t1, float t2, int* count) {
    if (mState == 5 || mState == 3 || mState == 2)
        return;
    if (mpSink && (mMode & 6))
        mpSink->Prepare(mpView);
    if (mMode == 0)
        *mpView = mpSettings->mView;
    else
        UpdateView();

    uint32_t changed = mpSettings->mGroupsVersion ^ mGroupsVersion;
    if (changed) {
        for (int* it = mActiveBegin; it != mActiveEnd; ++it) {
            Effect* e = mpEffects[*it];
            EffectDesc* d = e->mpDesc;
            if (d && (d->mGroupMask & changed))
                SetEffectLod(e, e->mLod, TransitionMode(e));
        }
        mGroupsVersion = mpSettings->mGroupsVersion;
    }
    if (mPendingBegin != mPendingEnd)
        AddPendingEffects(0);

    float t = (mTimeSource == 1) ? t1 : t2;
    float globalBlend = mGlobalLodPos - (float)mGlobalLod;
    int start = 0;
    int n = ActiveCount();
    while (start < n) {
        for (int i = start; i < n; i++) {
            Effect* e = mpEffects[mActiveBegin[i]];
            if (!e->mpDesc)
                continue;
            if (e->mFlags & 4)
                e->UpdateTransforms();
            if (!(e->mFlags & 0x800)) {
                if (mGlobalLod != e->mLod)
                    SetEffectLod(e, mGlobalLod, LodTransitionMode(e));
                e->mLodBlend = globalBlend;
                continue;
            }
            EffectDesc* desc = e->mpDesc;
            float score;
            if (!(desc->mFlags & 0x80000)) {
                score = (mpView->mCameraPos - e->mPosition).Length();
            } else {
                Vector3 d = mpView->mCameraPos - e->mPosition;
                float len2 = d.x * d.x + d.z * d.z + d.y * d.y;
                float inv = 1.0f / ((float)sqrt(len2) + 1e-6f);
                float view = (mpView->mViewDir.z * d.z + mpView->mViewDir.y * d.y + d.x * mpView->mViewDir.x);
                float facing = (e->mDirection.z * d.z + e->mDirection.y * d.y + e->mDirection.x * d.x);
                score = desc->mDistWeight * (inv * len2) +
                        desc->mFacingWeight * (0.5f - facing * inv * 0.5f) +
                        (view * inv + 1.0f) * 0.5f * desc->mViewWeight;
            }
            float v = mpSettings->mLodScale * e->mLodBias * score;
            if (v >= e->mLodMin && v < e->mLodMax) {
                e->mLodBlend = Clamp((v - e->mLodMin) / (e->mLodMax - e->mLodMin), 0.0f, 1.0f);
            } else {
                float* lods = desc->mLodBegin;
                int last = (int)(desc->mLodEnd - lods) - 1;
                int lod = 1;
                for (; lod < last; lod++)
                    if (lods[lod] > v)
                        break;
                if (lod != e->mLod)
                    SetEffectLod(e, lod, LodTransitionMode(e));
                lods = desc->mLodBegin;
                e->mLodBlend = Clamp((v - lods[lod - 1]) / (lods[lod] - lods[lod - 1]), 0.0f, 1.0f);
                e->mLodMin = desc->mLodBegin[lod - 1];
                e->mLodMax = desc->mLodBegin[lod];
            }
            if (IsNaN(e->mLodBlend))
                e->mLodBlend = 0.0f;
        }

        Vector3 saved0 = mpView->mLights[0].mDir;
        Vector3 saved1 = mpView->mLights[1].mDir;
        Vector3 saved2 = mpView->mLights[2].mDir;
        for (int i = start; i < n; i++) {
            Effect* e = mpEffects[mActiveBegin[i]];
            if (!e->mpDesc || (e->mFlags & 0x20) || !e->IsVisible())
                continue;
            float et;
            if (!(e->mFlags & 1)) {
                BendLight(mpView->mLights[0], saved0, e->mPosition);
                BendLight(mpView->mLights[1], saved1, e->mPosition);
                BendLight(mpView->mLights[2], saved2, e->mPosition);
                if (mpView->mbLit && (e->mpDesc->mFlags & 0x100))
                    e->SetParameter(0xb, (char*)mpView + 0x98, 2);
                uint32_t f = e->mpDesc->mFlags;
                if (f & 0x1000)
                    et = t1;
                else if (f & 0x2000)
                    et = t2;
                else
                    et = t;
            } else if (e->mFlags & 0x100) {
                et = 0.0f;
            } else {
                continue;
            }
            e->mUpdater.Update(et, 0.0f, count);
        }
        mpView->mLights[0].mDir = saved0;
        mpView->mLights[1].mDir = saved1;
        mpView->mLights[2].mDir = saved2;

        if (mPendingBegin != mPendingEnd)
            AddPendingEffects(0);
        start = n;
        n = ActiveCount();
    }
    FinishUpdate();
    *count += mUpdatedCount;
}
