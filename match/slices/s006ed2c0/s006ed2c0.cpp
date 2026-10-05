// Slice s006ed2c0 — SP::cEffectsRenderer texture-particle helpers and
// SP::cEffectsModel particle helpers (retail offsets).
// /O2 /MD /Gy /EHsc /TP (SSE2 float code, no frame pointer).
#include "types.h"

// ---- stub types -------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef() = 0;   // vtable +0
    virtual void Release() = 0;  // vtable +4
};

template<class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Release() { T* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
    AutoRefCount& operator=(T* p) { if (mpObject) { T* old = mpObject; mpObject = p; old->Release(); } else mpObject = p; return *this; }
};

// EASTL-style vector: out-of-line members keep the calls separate (as originally).
template<class T>
struct evec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    char mAllocator[4];
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned n) { return *(mpBegin + n); }
    void push_back(const T& v);
    void erase(T* first, T* last);
};

struct cTextureParticleSet {
    char pad0[0x48];
    bool mActive;        // +0x48
    bool mInActiveList;  // +0x49
    char pad1[0x70 - 0x4a];
};

struct cModelParticleSet {
    char pad0[0x50];
    bool mActive;            // +0x50
    char pad1[0x5c - 0x51];
    void* mpField5c;         // +0x5c
    IRefCounted* mpField60;  // +0x60
    int mField64;            // +0x64
    char pad2[0x68 - 0x68];
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
};

struct DispatchData { void* p0; void* p1; void* p2; };

// ---- SP::cEffectsModel (retail: bounding box at +0x50, refs vector at +0x70) --
class cEffectsModel {
public:
    void* mpVtable;                          // +0x00
    char padV[4];                            // +0x04
    evec<DispatchData> mDispatchData;        // +0x08
    char pad0[0x50 - 0x18];
    Vector3 mBoxMin;                         // +0x50
    Vector3 mBoxMax;                         // +0x5c
    float   mBoundingRadius;                 // +0x68
    AutoRefCount<IRefCounted> mAsyncRequest; // +0x6c
    evec<AutoRefCount<IRefCounted> > mResourceRefs;  // +0x70

    cEffectsModel(unsigned, unsigned, unsigned, const float*);   // 6ed8d0
    void AddResourceRef(IRefCounted* p);                         // 6edaa0
    void Reset();                                                // 6edb10
    void UpdateFromResource(int* res);                           // 6edbc0
    char Update();                                               // 6ee140
};

// ---- SP::cEffectsRenderer (retail offsets) ---------------------------------
class cEffectsRenderer {
public:
    char pad0[0x174];
    evec<cTextureParticleSet> mTextureParticleSets;    // +0x174
    char pad1[4];                                       // +0x184
    evec<unsigned short> mActiveTextureParticleSets;   // +0x188
    char pad2[0x1b8 - 0x198];
    cModelParticleSet* mModelBegin;      // +0x1b8
    cModelParticleSet* mModelEnd;        // +0x1bc
    evec<int> mFreeIDs;                  // +0x1cc
    IRefCounted* mSys1e0;                // +0x1e0

    void SetTextureParticleActive(int index, bool active);   // 6ed2c0
    void RemoveParticleSet(int index);                       // 6ed340
    int  ActivateByKey(unsigned int a, unsigned int b);      // 6ed440
};

// ---- 0x006ed2c0 -------------------------------------------------------------
// @ 0x006ed2c0
void cEffectsRenderer::SetTextureParticleActive(int index, bool active)
{
    if (index < 0 || index >= (int)mTextureParticleSets.size())
        return;
    cTextureParticleSet& p = mTextureParticleSets[index];
    if (p.mActive == active)
        return;
    p.mActive = active;
    if (!active)
        return;
    if (p.mInActiveList)
        return;
    mActiveTextureParticleSets.push_back((unsigned short)index);
    p.mInActiveList = 1;
}

// ---- 0x006ed340 (approximate) ----------------------------------------------
// @ 0x006ed340
void cEffectsRenderer::RemoveParticleSet(int index)
{
    if (index < 0)
        return;
    if (index >= (mModelEnd - mModelBegin) / 0x68)
        return;
    cModelParticleSet* p = mModelBegin + index;
    if (p->mpField60 == 0) {
        if (*(unsigned int*)p->pad0 != 0) {
            *(unsigned int*)p->pad0 = 0;
            p->mActive = false;
            if (p->mpField5c != 0) {
                if (mSys1e0 != 0)
                    mSys1e0->AddRef();
                p->mpField5c = 0;
            }
            mFreeIDs.push_back(index);
        }
        return;
    }
    p->mpField60->Release();
    p->mpField60 = 0;
    p->mField64 = -1;
    mFreeIDs.push_back(index);
}

// ---- 0x006ed440 (approximate) ----------------------------------------------
// @ 0x006ed440
int cEffectsRenderer::ActivateByKey(unsigned int a, unsigned int b)
{
    if (mSys1e0 == 0)
        return -1;
    if ((a & b) == 0xffffffffu)
        return -1;
    return 0;
}

// ---- 0x006ed5b0 / 0x006ed6f0 (EASTL vector inserts; approximate) ------------
struct vectorCTex {
    cTextureParticleSet* mpBegin; cTextureParticleSet* mpEnd; cTextureParticleSet* mpCapacity;
    void DoInsertValue(cTextureParticleSet* pos, const cTextureParticleSet& v);
};
struct vectorCMod {
    cModelParticleSet* mpBegin; cModelParticleSet* mpEnd; cModelParticleSet* mpCapacity;
    void DoInsertValue(cModelParticleSet* pos, const cModelParticleSet& v);
};
// @ 0x006ed5b0
void vectorCTex::DoInsertValue(cTextureParticleSet*, const cTextureParticleSet&) {}
// @ 0x006ed6f0
void vectorCMod::DoInsertValue(cModelParticleSet*, const cModelParticleSet&) {}

// ---- 0x006ed8d0 (approximate constructor) ----------------------------------
// @ 0x006ed8d0
cEffectsModel::cEffectsModel(unsigned, unsigned, unsigned, const float* box)
{
    mpVtable = 0;
    mAsyncRequest = (IRefCounted*)0;
    mBoundingRadius = 0.0f;
    if (box) {
        mBoxMin = Vector3(box[0], box[1], box[2]);
        mBoxMax = Vector3(box[3], box[4], box[5]);
    }
}

// ---- 0x006edaa0 -------------------------------------------------------------
// @ 0x006edaa0
void cEffectsModel::AddResourceRef(IRefCounted* p)
{
    AutoRefCount<IRefCounted> ref(p);
    mResourceRefs.push_back(ref);
}

// ---- 0x006edb10 -------------------------------------------------------------
// @ 0x006edb10
void cEffectsModel::Reset()
{
    const float f = 3.402823466e38f;
    Vector3 v(f, f, f);
    mBoxMin = v;
    mBoxMax = -v;
    mBoundingRadius = 0.0f;
    mAsyncRequest.Release();
    mDispatchData.erase(mDispatchData.mpBegin, mDispatchData.mpEnd);
    mResourceRefs.erase(mResourceRefs.mpBegin, mResourceRefs.mpEnd);
}

// ---- 0x006edbc0 (skeleton) --------------------------------------------------
// @ 0x006edbc0
void cEffectsModel::UpdateFromResource(int* res)
{
    (void)res;
}

// ---- 0x006ee140 (skeleton) --------------------------------------------------
// @ 0x006ee140
char cEffectsModel::Update()
{
    return 0;
}
