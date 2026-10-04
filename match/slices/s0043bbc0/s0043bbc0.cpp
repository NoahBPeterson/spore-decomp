// Slice s0043bbc0: small members of SP::cSPEditorBlock (retail layout; flag bitset at +0xdc8,
// mDeformationHandles = eastl::vector<AutoRefCount<cSPEditorHandleDeform>> at +0x6cc). Unoptimized module.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
// Function names are unknown (FUN_ in the image); F_<va> placeholders.
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
// @ 0x0043bbc0
bool cSPEditorBlock::F_43bbc0(int) { return mField3c9 || mFlags.test(8); }
// @ 0x0043bc40
void cSPEditorBlock::F_43bc40(float v) { F_43bc70(mPosition[0], v); }
// @ 0x0043bcf0
bool cSPEditorBlock::F_43bcf0(float a, float b) { float t = fabsf(a); return mTolB * mScale * b > t; }
// @ 0x0043bd50
void cSPEditorBlock::F_43bd50(cSPVector3 v, float s) { F_43bc70(v[0], s); }
// @ 0x0043bf20
bool cSPEditorBlock::F_43bf20(uint32_t out)
{
    if (mPropList && mPropList->HasProperty(0xf9efbb))
        return GetPropertyAsKey(mPropList, 0xf9efbb, out);
    return false;
}
// @ 0x0043bf90
void cSPEditorBlock::F_43bf90(uint32_t bit, bool on)
{
    if (mModel) mModel->mGroups.set(bit, on);
}
// @ 0x0043c040
int cSPEditorBlock::F_43c040()
{
    if (mModel) return mDeformationHandles.size();
    return mSavedHandleDeltas.size();
}
// @ 0x0043c0a0
int cSPEditorBlock::F_43c0a0()
{
    for (int i = 0, size = mDeformationHandles.size(); i < size; i++)
        if (mDeformationHandles[i]->mAnimationID == 0x9310d4c0) return i;
    return 0;
}
// @ 0x0043c120
int cSPEditorBlock::F_43c120(uint32_t id)
{
    for (int i = 0, size = mDeformationHandles.size(); i < size; i++)
        if (mDeformationHandles[i]->mAnimationID == id) return i;
    return -1;
}
// @ 0x0043c1a0
cSPEditorHandleDeform* cSPEditorBlock::F_43c1a0() { if (mHandleIndex[0] == -1) return F_43c270(0); else return F_43c270(mHandleIndex[0]); }
// @ 0x0043c1e0
cSPEditorHandleDeform* cSPEditorBlock::F_43c1e0() { if (mHandleIndex[1] == -1) return 0; else return F_43c270(mHandleIndex[1]); }
// @ 0x0043c210
cSPEditorHandleDeform* cSPEditorBlock::F_43c210() { if (mHandleIndex[2] == -1) return 0; else return F_43c270(mHandleIndex[2]); }
// @ 0x0043c240
cSPEditorHandleDeform* cSPEditorBlock::F_43c240() { if (mHandleIndex[3] == -1) return 0; else return F_43c270(mHandleIndex[3]); }
// @ 0x0043c270
cSPEditorHandleDeform* cSPEditorBlock::F_43c270(int i) { if (i < mDeformationHandles.size() && i >= 0) return mDeformationHandles[i].get(); else return 0; }
// @ 0x0043c2d0
float cSPEditorBlock::F_43c2d0(uint32_t i)
{
    if (i < (uint32_t)F_43c040()) {
        if (mModel) return mDeformationHandles[i]->mDelta;
        return mSavedHandleDeltas[i];
    }
    return 0.0f;
}
// @ 0x0043c340
uint32_t cSPEditorBlock::F_43c340(uint32_t i)
{
    if (i < (uint32_t)F_43c040()) {
        if (mModel) return mDeformationHandles[i]->mAnimationID;
        else if (i < (uint32_t)mSavedHandleAnimIDs.size()) return mSavedHandleAnimIDs.mpBegin[i];
    }
    return 0;
}
// @ 0x0043c3d0
int cSPEditorBlock::F_43c3d0(cSPEditorHandleDeform* c)
{
    if (c) {
        int res = -1;
        for (int i = 0, n = mDeformationHandles.size(); i < n; i++)
            if (mDeformationHandles[i].get() == c) return i;
    }
    return -1;
}
// @ 0x0043c450
bool cSPEditorBlock::F_43c450(cSPEditorHandleDeform* c, float f, float* a, bool b)
{
    if (mModel && c) {
        int idx = F_43c3d0(c);
        if (idx != -1) {
            F_43d690(idx, f, a, b, true);
            if (mEditorModel && mEditorModel->Func4adc40() && mSymmetricBlock)
                mSymmetricBlock->F_43d690(idx, f, a, b, true);
            return true;
        }
    }
    return false;
}
// @ 0x0043c510
bool cSPEditorBlock::F_43c510()
{
    if (mFlags.test(11)) {
        if (!mChildBlockList.Func526430()) {
            for (int i = 0, n = mChildBlockList.size(); i < n; i++)
                if (mChildBlockList[i]->mFlags.test(44)) return mFlags.test(0);
            return false;
        } else return mFlags.test(0);
    } else return mFlags.test(0);
}
// @ 0x0043c710
void cSPEditorBlock::F_43c710()
{
    bool ok = false, value = false, ret = false;
    if (mEditorModel) { ok = mEditorModel->Func4adb80(); value = mEditorModel->Func4adbc0(); }
    void* obj = GetCurrentThing();
    if (obj) {
        if (!mFlags.test(25)) {
            for (int i = 0; i < 3; i++) {
                if (mRotationRingHandles[i] && (!mRotationRingHandles[i]->IsHidden() || ok)) {
                    mRotationRingHandles[i]->Update();
                    ret = true;
                }
            }
            if (mRotationBallHandle) { mRotationBallHandle->Update(); ret = true; }
        }
        if (!mFlags.test(24)) {
            int n = mDeformationHandles.size();
            int idx = (mFlags.test(11) && !value) ? mHandleIndex[0] : -1;
            for (int i = 0, count = mDeformationHandles.size(); i < count; i++) {
                if (i == idx) continue;
                if (mDeformationHandles[i]->mIsHiddenHandle && !ok) continue;
                mDeformationHandles[i]->Update();
                ret = true;
            }
        }
        if (ret) PostMessageId(0xa95d8242);
    }
}
// @ 0x0043ca10
bool cSPEditorBlock::F_43ca10() { return !mFlags.test(7) && !mFlags.test(20); }

// @ 0x0043bc70
bool cSPEditorBlock::F_43bc70(float a, float b)
{
    float x = fabsf(a);
    float tmp = mTolA * mScale;
    __asm {
        movss xmm0, tmp
        maxss xmm0, kMinTolerance
        minss xmm0, kMaxTolerance
        movss tmp, xmm0
    }
    float hi = tmp;
    return x < hi * b;
}
// @ 0x0043bd80
// Not byte-exact: the original keeps the outgoing-argument esp in a stack slot ([ebp-0x90]) before
// copy-constructing the by-value cSPMatrix3 argument; every other instruction matches.
bool cSPEditorBlock::F_43bd80(cSPMatrix3 m, float s)
{
    cSPMatrix3 p15(m);
    cSPVector3 tmp(mPosition);
    cSPMatrix3 n25 = MatA(this, m);
    cSPMatrix3 u = MatB(this);
    int v32 = 0;
    if (fabsf(u.r[0][0]) > 0.0) v32 = 0;
    else if (fabsf(u.r[1][0]) > 0.0) v32 = 1;
    else if (fabsf(u.r[2][0]) > 0.0) v32 = 2;
    float chunk = Vec3Dist(m[v32], n25[v32]);
    float v4 = mTolC;
    if (v4 * s > chunk) return true;
    else return false;
}
