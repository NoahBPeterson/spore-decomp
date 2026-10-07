// slice s00752620 -- SP::cModelWorld::Update (retail layout).
//
// Per-frame model-world update: re-composes group element transforms, then for
// every model in the world list updates its hier-grid cell, lighting-info
// sphere, instance animation, effect transforms/visibility, light positions,
// listener notifications and the render-fade value; then advances the
// highlight pulse (sin wave or keyed curve) and compacts the 16 preload
// vectors (loaded models move to the matching "loaded" vector).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (fsin/fabs inline, SSE scalar math)

#include "types.h"
#include <math.h>
typedef uint16_t uint16; typedef uint32_t uint32;

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }

struct Matrix3 {
    Vector3 r[3];
    Vector3 Row(int i) const { return r[i]; }
    Matrix3(const Matrix3& m) { r[0] = m.Row(0); r[1] = m.Row(1); r[2] = m.Row(2); }
};

struct cSPTransform {
    uint16 mFlags;
    uint16 mModificationCount;
    Vector3 mOffset;
    float mScale;
    Matrix3 mRotation;
    cSPTransform(const cSPTransform& o)
        : mFlags(o.mFlags), mModificationCount(o.mModificationCount), mOffset(o.mOffset),
          mScale(o.mScale), mRotation(o.mRotation) {}
    cSPTransform& operator=(const cSPTransform& o);    // 0x537dc0
    void Accumulate(const cSPTransform& child);        // 0x40ccb0
};

inline Vector3 operator*(const Vector3& v, const Matrix3& m)
{
    return Vector3((m.r[2].x * v.z + m.r[1].x * v.y) + v.x * m.r[0].x,
                   (m.r[0].y * v.x + m.r[2].y * v.z) + m.r[1].y * v.y,
                   (m.r[0].z * v.x + m.r[2].z * v.z) + m.r[1].z * v.y);
}

struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA() {}
    ColorRGBA(float x, float y, float z, float w) : r(x), g(y), b(z), a(w) {}
};

// x87/SSE helper from the original headers: clamp into [0, hi] with maxss/minss.
inline float Saturate(float value, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}

struct bitset32 {
    uint32 mWord;
    bool test(uint32 n) const { return (mWord >> n) & 1; }
    void set(uint32 n, bool v) { if (v) mWord |= (1u << n); else mWord &= ~(1u << n); }
    bitset32& operator^=(const bitset32& o) { mWord ^= o.mWord; return *this; }
};
inline bitset32 operator^(const bitset32& a, const bitset32& b) { bitset32 r(a); r ^= b; return r; }

// --- effects / lights / instances ----------------------------------------
struct IEffect {
    virtual void v00(); virtual void v04();
    virtual void Start(int);                  // +8
    virtual void Stop(int);                   // +0xc
    virtual void v10(); virtual void v14();
    virtual void SetTransform(const cSPTransform& t); // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void SetHidden(int hidden);       // +0x30
};

struct cEffectEntry {                         // 0x48 bytes
    IEffect* mpEffect;
    cSPTransform mTransform;                  // +4
    bool mbActive;                            // +0x3c
    char pad[0x48 - 0x3d];
};

struct cEffectInfo {
    char pad[8];
    cEffectEntry mEntries[1];                 // +8, terminated by a null effect
};

struct cMWLightInfo {
    int mCount;                               // +0
    float* mIntensities;                      // +4
    Vector3* mColors;                         // +8
    float* mRadii;                            // +0xc
    Vector3* mOffsets;                        // +0x10
    int mIDs[1];                              // +0x14
};

struct ILightManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual int AddLight(const Vector3* pos, const Vector3* color, float intensity, float radius); // +0xc
    virtual void MoveLight(int id, const Vector3* pos);   // +0x10
    virtual void v14();
    virtual void* AddSphere(float radius, const Vector3* pos);           // +0x18
    virtual void UpdateSphere(float radius, const Vector3* pos, void* s); // +0x1c
};

struct cModelInstance { void Animate(float dt); };    // 0x73afb0

struct cMWModel;
struct IModelListener {
    virtual void v00(); virtual void v04();
    virtual void OnTransformChanged(cMWModel* m);         // +8
    virtual void OnVisibilityChanged(cMWModel* m, bool v); // +0xc
};

struct ListenerVector {
    IModelListener** mpBegin;
    IModelListener** mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
};
struct cModelManager {
    char pad[0x4c];
    ListenerVector mListeners;                // +0x4c
};

struct cMWModel {                             // base subobject at internal+8
    void* mpVT;
    bitset32 mFlags;                          // +4
    cSPTransform mTransform;                  // +8
};

struct cMWModelInternal {
    cMWModelInternal* mpNext;                 // +0
    cMWModelInternal* mpPrev;                 // +4
    cMWModel mModel;                          // +8 (flags +0xc, transform +0x10)
    char pad48[0x74 - 0x48];
    float mBoundingRadius;                    // +0x74
    char pad78[0x90 - 0x78];
    float mLODDistance;                       // +0x90
    float mFade;                              // +0x94
    char pad98[0xb4 - 0x98];
    cModelInstance* mModelInstance[4];        // +0xb4
    char padc4[0xdc - 0xc4];
    cEffectInfo* mEffects;                    // +0xdc
    cMWLightInfo* mLights;                    // +0xe0
    char pade4[0x11c - 0xe4];
    float mTimeScale;                         // +0x11c
    int mGridID;                              // +0x120
    float mEffectRange;                       // +0x124
    uint16 pad128;
    uint16 mLastModificationCount;            // +0x12a
    bitset32 mLastFlags;                      // +0x12c
    uint32 mLastRenderFrame;                  // +0x130
    void* mLightingInfo;                      // +0x134
    uint32 mCreateFlags;                      // +0x138
};

struct cGroupElement {                        // 0x3c bytes
    cMWModel* mpModel;
    cSPTransform mTransform;                  // +4
};

struct cMWGroupInternal {
    cMWGroupInternal* mpNext;
    cMWGroupInternal* mpPrev;
    char pad08[8];
    cSPTransform mTransform;                  // +0x10
    char pad48[4];
    cGroupElement* mElemsBegin;               // +0x4c
    cGroupElement* mElemsEnd;                 // +0x50
};

struct cHierGrid {
    int Insert(float radius, const Vector3& pos, cMWModelInternal* m);   // 0x703d50
    void Update(int id, float radius, const Vector3& pos);              // 0x703b60
};

struct cPreloadModel;
struct IModelOwner;
struct cPreloadModel {
    IModelOwner* mpOwner;                     // +0
    bitset32 mFlags;                          // +4
    char pad08[0x40 - 8];
    int mnRefCount;                           // +0x40
    void AddRef() { ++mnRefCount; }
    void Release();
};
struct IModelOwner {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void DestroyModel(cPreloadModel* m, int flag); // +0x170
};
inline void cPreloadModel::Release()
{
    if (mnRefCount > 1)
        --mnRefCount;
    else
        mpOwner->DestroyModel(this, mFlags.test(31));
}

struct ModelPtr {
    cPreloadModel* mpObject;
    ModelPtr& operator=(const ModelPtr& o)
    {
        cPreloadModel* p = o.mpObject;
        cPreloadModel* old = mpObject;
        if (p != old) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct ModelPtrVector {                       // eastl::vector<AutoRefCount<cMWModel>, sp_vector_allocator>
    ModelPtr* mpBegin;
    ModelPtr* mpEnd;
    ModelPtr* mpCapacity;
    int mAllocator[2];
    void DoInsertValue(ModelPtr* position, const ModelPtr& value); // 0x423c40
    void resize(int n);                                            // 0x473270
    void push_back(const ModelPtr& value)
    {
        if (mpEnd < mpCapacity) {
            ModelPtr* p = mpEnd++;
            if (p) {
                p->mpObject = value.mpObject;
                if (p->mpObject)
                    p->mpObject->AddRef();
            }
        } else
            DoInsertValue(mpEnd, value);
    }
};

struct cLoadQueue { void Update(); };        // 0x751de0

struct cDirectPropertyList { char pad[0x3c]; char* mpData; };
extern cDirectPropertyList* sAppProperties;  // 0x15fd918
extern uint32 g_FrameCounter;                // 0x16f8cf8
extern const Vector3 kDefaultLightColor;     // 0x1537ab0

namespace SP {
class cModelWorld {
public:
    void Update(float dt, float highlightDt);

    char pad00[0x18];
    cModelManager* mManager;                  // +0x18
    char pad1c;
    bool mActive;                             // +0x1d
    char pad1e[0x118 - 0x1e];
    cHierGrid mHierGrid;                      // +0x118
    char pad119[0x13c - 0x119];
    void* mGridBegin;                         // +0x13c
    void* mGridEnd;                           // +0x140
    char pad144[0x19c - 0x144];
    cMWModelInternal* mModelListFirst;        // +0x19c
    cMWModelInternal* mModelListLast;         // +0x1a0
    char pad1a4[0x1ac - 0x1a4];
    cMWGroupInternal* mGroupListFirst;        // +0x1ac
    cMWGroupInternal* mGroupListLast;         // +0x1b0
    char pad1b4[0x1cc - 0x1b4];
    ILightManager* mpLightManager;            // +0x1cc
    char pad1d0[0x2b8 - 0x1d0];
    float mLODScale;                          // +0x2b8
    char pad2bc[0x314 - 0x2bc];
    cLoadQueue mLoadQueue;                    // +0x314
    char pad315[0x5cc - 0x315];
    bool mPreloadsDirty;                      // +0x5cc
    ModelPtrVector mPreloadModels[16];        // +0x5d0
    ModelPtrVector mLoadedPreloadModels[16];  // +0x710
    ColorRGBA mHighlightColor;                // +0x850
    float mHighlightTime;                     // +0x860
    float* mHighlightCurveBegin;              // +0x864
    float* mHighlightCurveEnd;                // +0x868
    char pad86c[0x878 - 0x86c];
    float mHighlightLife;                     // +0x878
    float mHighlightAmplitude;                // +0x87c
    char pad880[4];
    uint32 mHighlightLengthMS;                // +0x884
    float mHighlightFreq;                     // +0x888
    float mHoldAmplitude;                     // +0x88c
    char pad890[0x89c - 0x890];
    int mNumModels;                           // +0x89c
};

// @ 0x00752620
void cModelWorld::Update(float dt, float highlightDt)
{
    mLoadQueue.Update();
    if (!mActive)
        return;

    for (cMWGroupInternal* group = mGroupListFirst; group != (cMWGroupInternal*)&mGroupListFirst; group = group->mpNext) {
        int count = (int)(group->mElemsEnd - group->mElemsBegin);
        for (int i = 0; i < count; i++) {
            cGroupElement& e = group->mElemsBegin[i];
            if (e.mpModel) {
                cSPTransform t(group->mTransform);
                t.Accumulate(e.mTransform);
                group->mElemsBegin[i].mpModel->mTransform = t;
            }
        }
    }

    ILightManager* lightManager = mpLightManager;
    uint32 frame = g_FrameCounter;
    float lodDistance = *(float*)(sAppProperties->mpData + 0x9c) * mLODScale;
    mNumModels = 0;
    bool hasListeners = !mManager->mListeners.empty();

    for (cMWModelInternal* model = mModelListFirst; model != (cMWModelInternal*)&mModelListFirst; model = model->mpNext) {
        mNumModels++;
        bool changed = model->mLastModificationCount != model->mModel.mTransform.mModificationCount;
        float radius = model->mBoundingRadius * model->mModel.mTransform.mScale;
        Vector3 pos(model->mModel.mTransform.mOffset);
        bitset32 changedFlags = model->mLastFlags ^ model->mModel.mFlags;

        if (mGridBegin != mGridEnd) {
            if (model->mGridID < 0)
                model->mGridID = mHierGrid.Insert(radius, pos, model);
            else if (changed)
                mHierGrid.Update(model->mGridID, radius, pos);
        }

        if (lightManager) {
            if (!model->mLightingInfo)
                model->mLightingInfo = lightManager->AddSphere(radius, &pos);
            else if (changed)
                lightManager->UpdateSphere(radius, &pos, model->mLightingInfo);
        }

        if (model->mCreateFlags & 0x40000000) {
            float animDt = model->mTimeScale * dt;
            for (int i = 0; i < 4; i++) {
                if (!model->mModelInstance[i])
                    break;
                model->mModelInstance[i]->Animate(animDt);
            }
        }

        bool visible;
        if (model->mEffectRange == 0.0f || model->mEffectRange > model->mLODDistance * lodDistance)
            visible = true;
        else
            visible = false;

        if (model->mEffects) {
            if (changed) {
                cEffectEntry* e = model->mEffects->mEntries;
                for (IEffect* effect = e->mpEffect; effect; effect = (++e)->mpEffect) {
                    cSPTransform t(model->mModel.mTransform);
                    t.Accumulate(e->mTransform);
                    effect->SetTransform(t);
                }
            }
            if (visible != model->mModel.mFlags.test(19)) {
                cEffectEntry* e = model->mEffects->mEntries;
                if (visible) {
                    for (; e->mpEffect; e++)
                        if (e->mbActive)
                            e->mpEffect->Start(1);
                } else {
                    for (; e->mpEffect; e++)
                        if (e->mbActive)
                            e->mpEffect->Stop(1);
                }
            }
            if (changedFlags.test(0)) {
                for (cEffectEntry* e = model->mEffects->mEntries; e->mpEffect; e++)
                    e->mpEffect->SetHidden(!model->mModel.mFlags.test(0));
            }
        }
        model->mModel.mFlags.set(19, visible);

        cMWLightInfo* lights = model->mLights;
        if (lights) {
            if (lights->mIDs[0] == -1) {
                Vector3 lightPos(model->mModel.mTransform.mOffset);
                float lightRadius = model->mModel.mTransform.mScale;
                for (int i = 0; i < model->mLights->mCount; i++) {
                    cMWLightInfo* li = model->mLights;
                    if (li->mOffsets) {
                        lightPos = li->mOffsets[i];
                        const cSPTransform& xf = model->mModel.mTransform;
                        float x, y, z;
                        if (xf.mFlags & 2) {
                            float vz = lightPos.z, vy = lightPos.y, vx = lightPos.x;
                            const Matrix3& m = xf.mRotation;
                            x = (m.r[2].x * vz + m.r[1].x * vy) + vx * m.r[0].x;
                            y = (m.r[0].y * vx + m.r[2].y * vz) + m.r[1].y * vy;
                            z = (m.r[0].z * vx + m.r[2].z * vz) + m.r[1].z * vy;
                        } else {
                            z = lightPos.z;
                            y = lightPos.y;
                            x = lightPos.x;
                        }
                        float s = xf.mScale;
                        x *= s;
                        y *= s;
                        z *= s;
                        lightPos.x = xf.mOffset.x + x;
                        lightPos.y = xf.mOffset.y + y;
                        lightPos.z = xf.mOffset.z + z;
                    }
                    if (li->mRadii)
                        lightRadius = li->mRadii[i] * model->mModel.mTransform.mScale;
                    float intensity = li->mIntensities ? li->mIntensities[i] : 1.0f;
                    const Vector3* color = li->mColors ? &li->mColors[i] : &kDefaultLightColor;
                    model->mLights->mIDs[i] = mpLightManager->AddLight(&lightPos, color, intensity, lightRadius);
                }
            } else if (changed) {
                for (int i = 0; i < model->mLights->mCount; i++) {
                    Vector3* offsets = model->mLights->mOffsets;
                    const Vector3& p = offsets
                        ? offsets[i] + model->mModel.mTransform.mOffset
                        : Vector3(model->mModel.mTransform.mOffset);
                    Vector3 q(p);
                    mpLightManager->MoveLight(model->mLights->mIDs[i], &q);
                }
            }
        }

        if (hasListeners) {
            if (changed) {
                for (IModelListener** it = mManager->mListeners.mpBegin, **end = mManager->mListeners.mpEnd; it != end; ++it)
                    (*it)->OnTransformChanged(&model->mModel);
            }
            if (changedFlags.test(0)) {
                bool shown = model->mModel.mFlags.test(0);
                for (IModelListener** it = mManager->mListeners.mpBegin, **end = mManager->mListeners.mpEnd; it != end; ++it)
                    (*it)->OnVisibilityChanged(&model->mModel, shown);
            }
        }

        if (changedFlags.test(15))
            model->mLastRenderFrame = frame;
        model->mFade = Saturate(((float)(uint32)(frame - model->mLastRenderFrame) - 4.0f) * (1.0f / 30.0f), 1.0f);
        model->mLastFlags = model->mModel.mFlags;
        model->mLastModificationCount = model->mModel.mTransform.mModificationCount;
    }

    float t = mHighlightTime + highlightDt;
    mHighlightTime = t;
    if (t > (float)mHighlightLengthMS)
        mHighlightAmplitude = mHoldAmplitude;
    float scale = fabsf((sinf(t * mHighlightFreq) + 1.0f) * 0.5f) * mHighlightAmplitude + 1.0f;
    if (mHighlightCurveBegin != mHighlightCurveEnd) {
        float life = mHighlightLife;
        if (t >= life) {
            float step = life / (float)(uint32)((mHighlightCurveEnd - mHighlightCurveBegin) - 1);
            mHighlightTime = life - (step + step);
        }
        int last = (int)(mHighlightCurveEnd - mHighlightCurveBegin) - 1;
        float u = mHighlightTime / life;
        if (last == 0)
            scale = mHighlightCurveBegin[0] + 1.0f;
        else {
            float f = (float)(uint32)last * u;
            int idx = (int)f;
            float frac = f - (float)idx;
            if (frac > 0.0f)
                scale = (mHighlightCurveBegin[idx + 1] - mHighlightCurveBegin[idx]) * frac + mHighlightCurveBegin[idx] + 1.0f;
            else
                scale = mHighlightCurveBegin[idx] + 1.0f;
        }
    }
    mHighlightColor = ColorRGBA(scale, scale, scale, 1.0f);

    if (mPreloadsDirty) {
        ModelPtrVector* vec = mPreloadModels;
        for (int n = 16; n != 0; n--, vec++) {
            ModelPtr* models = vec->mpBegin;
            if (models == vec->mpEnd)
                continue;
            int size = (int)(vec->mpEnd - models);
            int keep = 0;
            for (int i = 0; i < size; i++) {
                if (!models[i].mpObject->mFlags.test(14)) {
                    if (keep < i)
                        models[keep] = models[i];
                    keep++;
                } else
                    vec[16].push_back(models[i]);
            }
            vec->resize(keep);
        }
        mPreloadsDirty = false;
    }
}
} // namespace SP
