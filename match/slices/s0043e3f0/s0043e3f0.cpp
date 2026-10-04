// Slice s0043e3f0: more SP::cSPEditorBlock members (deform-handle animation, fade controller at
// +0xdd0, bounding box) plus cSPBoundingBox::Add / GetCorner. Unoptimized module.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"
#include <math.h>
#include <xmmintrin.h>   // also switches /arch:SSE scalar float codegen to SSE at /Od

namespace eastl {
template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N) return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
    __forceinline void set(uint32_t i, bool value) {
        if (i < N) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};
}
namespace EA {
template<class T> struct AutoRefCount {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
using eastl::vector;
using eastl::bitset;
using EA::AutoRefCount;

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b);   // 0x41db10
float Length(const cSPVector3& v);                                // VectorLength 0x40ae50

struct cSPMatrix3 {                      // rw::math::fpu::Matrix33Template<float,0>
    cSPVector3 r[3];
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& o);     // Matrix3::Assign (0x41cb40), out of line
    const cSPVector3& operator[](int i) const { return r[i]; }
};

struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    cSPBoundingBox();                                  // BoundingBox_Reset 0x409c00
    cSPBoundingBox(const cSPBoundingBox& o);           // 0x511140
    void Extend(const cSPVector3& p);                  // BoundingBox::Extend 0x41bd50
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
    void Add(const cSPBoundingBox& o);                 // 0x43f050
    cSPVector3 GetCorner(uint32_t mask) const;         // 0x43f290
};

namespace SP {
struct cPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);
};
bool GetPropertyAsKey(cPropertyList* p, uint32_t id, uint32_t out);
struct cMWModel { char pad[0x44]; bitset<64> mGroups; };
struct cSPEditorModel {
    float GetScale();       // 0x4adaa0
    bool Func4adb80();      // 0x4adb80
    bool Func4adbc0();      // 0x4adbc0
    bool Func4adc40();      // 0x4adc40 (symmetry enabled?)
};
struct cSPEditorHandle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Update();                 // vtable +0x2c
};
struct cSPEditorHandleRotationRing : cSPEditorHandle {
    char pad[0x92 - 4]; bool mbHidden;     // +0x92
    bool IsHidden() const { return mbHidden; }
};
struct cSPEditorHandleRotationBall : cSPEditorHandle {};
struct cSPEditorHandleDeform : cSPEditorHandle {
    char pad04[0x8c - 4];
    uint32_t mAnimationID;                 // +0x8c  (mData.mAnimationID)
    cSPVector3 mStartPt;                   // +0x90
    cSPVector3 mEndPt;                     // +0x9c
    char padA8[0x180 - 0xa8];
    float mDelta;                          // +0x180
    char pad184[0x1d4 - 0x184];
    bool mIsHiddenHandle;                  // +0x1d4
    bool mDoNotPlaceHandle;                // +0x1d5
    float GetDelta() const { return mDelta; }
};
struct cSPEditorBlock;
struct BlockList : vector<AutoRefCount<cSPEditorBlock> > { bool Func526430(); };  // SP::GetResourceTypeFromModelType (folded)
struct cSPFadeController {               // at +0xdd0
    bool IsActive();                     // FadeController::IsActive 0x4340c0
    void Stop();                         // FadeController::Stop 0x434120
    void Start(uint32_t a, float t);     // 0x4342f0
};
}
using namespace SP;
void* GetCurrentThing();                  // 0x401060
void PostMessageId(uint32_t id);          // 0x4a88d0
cSPMatrix3 MatA(cSPEditorBlock* o, cSPMatrix3 m);   // 0x49e880
cSPMatrix3 MatB(cSPEditorBlock* o);                 // 0x494270
extern const float kMinTolerance;         // 0.01f
extern const float kMaxTolerance;         // 0.13f
float Vec3Dist(const cSPVector3& a, const cSPVector3& b);   // 0x454aa0
extern float g_15d257c;

namespace SP {
// Retail layout (much larger than the 2008 PDB's 0x548); names follow the 2008 PDB where the field
// could be identified, unknown fields are named by offset.
struct cSPEditorBlock {
    char pad00[0x0c];
    AutoRefCount<cPropertyList> mPropList;                     // +0x0c
    AutoRefCount<cMWModel> mModel;                             // +0x10
    char pad14[0x28 - 0x14];
    cSPEditorModel* mEditorModel;                              // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3 mPosition;                                      // +0x48
    char pad54[0x154 - 0x54];
    AutoRefCount<cSPEditorHandleRotationRing> mRotationRingHandles[3];   // +0x154
    AutoRefCount<cSPEditorHandleRotationBall> mRotationBallHandle;       // +0x160
    char pad164[0x1b0 - 0x164];
    int mHandleIndex[4];                                       // +0x1b0
    char pad1c0[0x1d4 - 0x1c0];
    float mField1d4;                                           // +0x1d4
    float mScale;                                              // +0x1d8
    char pad1dc[0x218 - 0x1dc];
    float mRangeMin;                                           // +0x218
    float mRangeMax;                                           // +0x21c
    float mTolA, mTolB, mTol228, mTolC;                        // +0x220
    char pad230[0x340 - 0x230];
    BlockList mChildBlockList;                                 // +0x340
    char pad350[0x3c9 - 0x350];
    bool mField3c9;                                            // +0x3c9
    char pad3ca[0x3e0 - 0x3ca];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;              // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    AutoRefCount<cSPEditorBlock> mField3ec;                    // +0x3ec
    char pad3f0[0x448 - 0x3f0];
    float mField448;                                           // +0x448
    float mField44c;                                           // +0x44c
    char pad450[0x604 - 0x450];
    uint32_t mField604;                                        // +0x604
    uint32_t mField608;                                        // +0x608
    char pad60c[0x6cc - 0x60c];
    vector<AutoRefCount<cSPEditorHandleDeform> > mDeformationHandles;   // +0x6cc
    char pad6dc[0x704 - 0x6dc];
    vector<float> mSavedHandleDeltas;                          // +0x704
    char pad714[0x73c - 0x714];
    vector<uint32_t> mSavedHandleAnimIDs;                      // +0x73c
    char pad74c[0xdc8 - 0x74c];
    bitset<60> mFlags;                                         // +0xdc8
    cSPFadeController mFader;                                  // +0xdd0
    char padfade[0xde4 - 0xdd1];
    uint32_t mFadeArg;                                         // +0xde4
    char padde8[0xdf4 - 0xde8];
    int mFadeId;                                               // +0xdf4

    float GetRangeMin() const { return mRangeMin; }
    float GetRangeMax() const { return mRangeMax; }
    cSPEditorModel* GetEditorModel() const { return mEditorModel; }

    // slice s0043bbc0
    bool F_43bbc0(int);
    void F_43bc40(float v);
    bool F_43bc70(float a, float b);
    bool F_43bcf0(float a, float b);
    void F_43bd50(cSPVector3 v, float s);
    bool F_43bd80(cSPMatrix3 m, float s);
    bool F_43bf20(uint32_t out);
    void F_43bf90(uint32_t bit, bool on);
    int F_43c040();
    int F_43c0a0();
    int F_43c120(uint32_t id);
    cSPEditorHandleDeform* F_43c1a0();
    cSPEditorHandleDeform* F_43c1e0();
    cSPEditorHandleDeform* F_43c210();
    cSPEditorHandleDeform* F_43c240();
    cSPEditorHandleDeform* F_43c270(int i);
    float F_43c2d0(uint32_t i);
    uint32_t F_43c340(uint32_t i);
    int F_43c3d0(cSPEditorHandleDeform* c);
    bool F_43c450(cSPEditorHandleDeform* c, float f, float* a, bool b);
    bool F_43c510();
    void F_43c710();
    bool F_43ca10();
    void F_43d690(int idx, float f, float* a, bool b, bool one);   // 0x43d690
    // slice s0043e3f0
    void F_43e3f0(float dt, uint32_t index);
    void F_43e760(uint32_t index);
    void F_43e7e0(uint32_t index, bool b);
    bool F_43e8d0(int id);
    bool F_43e920();
    void F_43e940(uint32_t a, uint32_t b, int id);
    void F_43e9c0();
    void F_43ea20();
    void F_43ea40(int id);
    void F_43eaa0(int id);
    void F_43eae0(float v);
    void F_43eb50(float v);
    bool F_43ebc0();
    bool F_43ecb0();
    cSPBoundingBox F_43eef0();
    float F_43f250();
    float F_43eed0();                      // 0x43eed0
    float F_43f3a0();                      // 0x43f3a0
    void F_440110(float v);                // 0x440110
    void F_440390(float v);                // 0x440390
    void F_449ce0();                       // 0x449ce0
    cSPBoundingBox GetBBox(bool a, bool b, bool c);   // SP::cSPEditorBlock::GetBBox 0x44ae00
};
}

inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// @ 0x0043e3f0
void cSPEditorBlock::F_43e3f0(float dt, uint32_t index)
{
    if (GetEditorModel()) {
        float scale = GetEditorModel()->GetScale();
        float a = 0.01f * scale;
        float b = 0.2f * scale;
        float c = 3.0f * g_15d257c;
        if (index >= 0 && index < (uint32_t)mDeformationHandles.size()) {
            mField448 += dt;
            cSPEditorHandleDeform* handle = mDeformationHandles[index];
            cSPVector3 d = handle->mEndPt - handle->mStartPt;
            float len = Length(d);
            if (b > len) len = b;
            float amp = a / len;
            float off = 0.0f;
            if (amp > mField44c) off = amp - mField44c;
            else if (amp > 1.0f - mField44c) off = -(amp - (1.0f - mField44c));
            float phase = 0.0f;
            if (off != 0.0f) phase = asinf(-off / amp);
            float v1 = sinf(mField448 * c + phase) * amp + off;
            float v0 = sinf(0.0f * c + phase) * amp + off;
            float v = Clamp(mField44c + v1, 0.0f, 1.0f);
            F_43c450(handle, v, &mField44c, true);
            F_449ce0();
        }
    }
}

// @ 0x0043e760
void cSPEditorBlock::F_43e760(uint32_t index)
{
    if (index < (uint32_t)mDeformationHandles.size() && index >= 0) {
        cSPEditorHandleDeform* handle = mDeformationHandles[index];
        mField44c = handle->mDelta;
        handle->mDoNotPlaceHandle = true;
        mField448 = 0.0f;
    }
}

// @ 0x0043e7e0
void cSPEditorBlock::F_43e7e0(uint32_t index, bool b)
{
    if (index < (uint32_t)mDeformationHandles.size() && index >= 0) {
        cSPEditorHandleDeform* handle = mDeformationHandles[index];
        mField448 = 0.0f;
        handle->mDoNotPlaceHandle = false;
        F_43d690(index, mField44c, 0, b, true);
        if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
            mSymmetricBlock->F_43d690(index, handle->mDelta, 0, b, true);
    }
}

// @ 0x0043e8d0
bool cSPEditorBlock::F_43e8d0(int id) { return mFadeId == id && mFader.IsActive(); }

// @ 0x0043e920
bool cSPEditorBlock::F_43e920() { return mFader.IsActive(); }

// @ 0x0043e940
void cSPEditorBlock::F_43e940(uint32_t a, uint32_t b, int id)
{
    mFadeId = id;
    mFadeArg = b;
    if (mFader.IsActive()) {
        if (id != 1) mFader.Start(a, 0.1f);
    } else {
        mFader.Start(a, 0.1f);
    }
}

// @ 0x0043e9c0
void cSPEditorBlock::F_43e9c0()
{
    F_43ea20();
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_43ea20();
}

// @ 0x0043ea20
void cSPEditorBlock::F_43ea20() { mFader.Stop(); }

// @ 0x0043ea40
void cSPEditorBlock::F_43ea40(int id)
{
    F_43eaa0(id);
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_43eaa0(id);
}

// @ 0x0043eaa0
void cSPEditorBlock::F_43eaa0(int id)
{
    if (mField604) F_43e940(mField604, mField608, id);
}

// @ 0x0043eae0
void cSPEditorBlock::F_43eae0(float v)
{
    F_440390(v);
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_440390(v);
}

// @ 0x0043eb50
void cSPEditorBlock::F_43eb50(float v)
{
    F_440110(v);
    if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
        mSymmetricBlock->F_440110(v);
}

// @ 0x0043ebc0
bool cSPEditorBlock::F_43ebc0()
{
    bool result = false;
    if (F_43c210()) {
        if (GetRangeMax() > GetRangeMin()) {
            float t = (mField1d4 - GetRangeMin()) / (GetRangeMax() - GetRangeMin());
            float cur = F_43c210()->mDelta;
            if (t != cur) {
                F_43c450(F_43c210(), t, 0, true);
                result = true;
            }
        }
    }
    return result;
}

// @ 0x0043ecb0
bool cSPEditorBlock::F_43ecb0()
{
    bool result = false;
    if (F_43c1e0()) {
        cSPEditorBlock* best = 0;
        for (int i = 0, n = mChildBlockList.size(); i < n; i++) {
            if (mChildBlockList[i]->mField3ec) {
                if (!best || best->F_43eed0() < mChildBlockList[i]->F_43eed0())
                    best = mChildBlockList[i];
            }
        }
        if (best) {
            float v = best->F_43eed0();
            if (GetRangeMin() > v) v = mRangeMin;
            else if (v > GetRangeMax()) v = mRangeMax;
            if (GetRangeMax() > GetRangeMin()) {
                float t = (v - GetRangeMin()) / (GetRangeMax() - GetRangeMin());
                float cur = F_43c1e0()->mDelta;
                if (t != cur) {
                    F_43c450(F_43c1e0(), t, 0, true);
                    result = true;
                }
            }
        }
    }
    return result;
}

// @ 0x0043eef0
cSPBoundingBox cSPEditorBlock::F_43eef0()
{
    cSPBoundingBox box;
    float r = F_43f3a0();
    box.Extend(cSPVector3(r, 0.0f, 0.0f));
    box.Extend(cSPVector3(-r, 0.0f, 0.0f));
    if (!mFlags.test(11) && !mFlags.test(20))
        box.Add(GetBBox(true, false, false));
    return box;
}

// @ 0x0043f050
void cSPBoundingBox::Add(const cSPBoundingBox& o)
{
    if (IsEmpty()) {
        mMin = o.mMin;
        mMax = o.mMax;
    } else {
        if (mMin[0] > o.mMin[0]) mMin[0] = o.mMin[0];
        if (mMax[0] < o.mMax[0]) mMax[0] = o.mMax[0];
        if (mMin[1] > o.mMin[1]) mMin[1] = o.mMin[1];
        if (mMax[1] < o.mMax[1]) mMax[1] = o.mMax[1];
        if (mMin[2] > o.mMin[2]) mMin[2] = o.mMin[2];
        if (mMax[2] < o.mMax[2]) mMax[2] = o.mMax[2];
    }
}

// @ 0x0043f250
float cSPEditorBlock::F_43f250()
{
    cSPBoundingBox box = F_43eef0();
    return Length(box.GetCorner(0)) / 2.0f;
}

// @ 0x0043f290
cSPVector3 cSPBoundingBox::GetCorner(uint32_t mask) const
{
    cSPVector3 v;
    v[0] = (mask & 1) ? mMax[0] : mMin[0];
    v[1] = (mask & 2) ? mMax[1] : mMin[1];
    v[2] = (mask & 4) ? mMax[2] : mMin[2];
    return v;
}

