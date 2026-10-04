// Slice s00484e40: SP::cSPEditorHandleRotationRing (retail layout) and an editor handle-tree node.
// Module flags: /Od /Ob1 /arch:SSE (unoptimized, small helpers inlined).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3 : Matrix33T {
    static const cSPMatrix3 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
};

Vector3T operator*(const Vector3T& v, const Matrix33T& m);   // @ 0x41daf0
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T& operator+=(Vector3T& a, const Vector3T& b);        // @ 0x41ddb0
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
inline float Length(const Vector3T& v) { return VectorLength(v); }

inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // @ 0x409930
    const cSPMatrix3& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void PreRotate(const Vector3T& axis, float angle);       // @ 0x6baba0
};

// ---- ref counting ----
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

namespace SP {

struct cMWObject {
    struct cIModelWorld* mWorld;
    uint32_t mFlags;
    cSPTransform mTransform;                    // +0x08
    int mRefCount;                              // +0x40
    void AddRef() { mRefCount++; }
    cSPTransform& GetTransform() { return mTransform; }
};
struct cMWModel : cMWObject { };

#define PV(n) virtual void _v##n();
struct cIModelWorld {
    virtual int AddRef();                                                                   // 0x00
    PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual void SetAnimTime(cMWModel* model, uint32_t animID, float time, int flags);      // 0x74
    PV(30) PV(31)
    virtual void GetAnimRange(cMWModel* model, uint32_t animID, float* start, float* end, int flags); // 0x80
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60)
    PV(61) PV(62) PV(63) PV(64) PV(65) PV(66)
    virtual void UpdateModel(cMWModel* model, int flags);                                   // 0x10c
};

struct cSPEditorModel {
    float GetScale();                                                                       // @ 0x4adaa0
};

struct cSPEditorBlock {
    char pad0[0x18];
    AutoRefCount<cIModelWorld> mModelWorld;     // +0x18
    char pad1[0x28 - 0x1c];
    cSPEditorModel* mEditorModel;               // +0x28
    char pad2[0x60 - 0x2c];
    cSPMatrix3 mOrientation;                    // +0x60
    char pad3[0x1d8 - 0x84];
    float mScale;                               // +0x1d8
    const cSPMatrix3& GetOrientation() const { return mOrientation; }
    cSPEditorModel* GetEditorModel() const { return mEditorModel; }
    cIModelWorld* GetModelWorld() const { return mModelWorld; }
    float GetScale() const { return mScale; }
    float GetModelScale();                                                                  // @ 0x435c00
};

struct cAnimManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void StartAnim(AutoRefCount<cMWModel> model, int type, float time);            // 0x18
    PV(7)
    virtual void QueueAnim(AutoRefCount<cMWModel> model, AutoRefCount<cIModelWorld> world,
                           uint32_t animID, float start, float end, int type);             // 0x20
};
cAnimManager* GetAnimManager();                                                             // @ 0x401060

struct cSPEditorHandle {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual float GetStateTime(int state, float time, bool b);                              // 0x38
    void* mpVtbl2;                              // +0x04
    int mRefCount;                              // +0x08
    void* mPropList;                            // +0x0c
    cSPEditorBlock* mBlock;                     // +0x10
    AutoRefCount<cMWModel> mModel;              // +0x14
    AutoRefCount<cMWModel> mOverdrawModel;      // +0x18
    int mCurrentState;                          // +0x1c
    float mFadeInTime;                          // +0x20
    float mFadeOutTime;                         // +0x24
    float mAnimateInTime;                       // +0x28
    float mAnimateOutTime;                      // +0x2c
    char mKeys[0x48 - 0x30];
    bool mHasOverdraw;                          // +0x48
    float mDefaultScale;                        // +0x4c

    void SetState(int state, bool b);                                                       // @ 0x47ec40
    bool IsVisible();                                                                       // @ 0x47f290
    void Shutdown();                                                                        // @ 0x47e2c0
};

struct cSPEditorHandleRotationRing : cSPEditorHandle {
    uint32_t mModelInstance;                    // +0x50
    cSPVector3 mRotationAxis;                   // +0x54
    cSPVector3 mForwardVector;                  // +0x60
    uint32_t mRotationAxisID;                   // +0x6c
    uint32_t mHandlePlacement;                  // +0x70
    uint32_t mAnimID;                           // +0x74
    float mUnscaledRadius;                      // +0x78
    float mHandleRotation;                      // +0x7c
    float mOffset;                              // +0x80
    float mCustomScale;                         // +0x84
    float mCurrentAnimTime;                     // +0x88
    float mTargetAnimTime;                      // +0x8c
    bool mActLikeBall;                          // +0x90
    bool mIsHiddenHandle;                       // +0x91
    float mDistanceFromBoundingBox;             // +0x94

    cSPVector3 GetRotationAxis(bool inWorld);
    cSPVector3 GetForwardVector(bool inWorld);
    cSPVector3 GetHandleDirection(bool useBlock);
    float GetRadius();
    void SetBoundingBox(const cSPBoundingBox& box);
    float CalculateAnimTime();
    void ApplyAnimTime();
    void UpdateAnimTime();
    void SetState(int state, bool b);
    void AnimateOn();
    void SetModelScale(float scale);
    void Shutdown();
    float GetHandleRadiusBasedOnBoundingBox();                                              // @ 0x484640
};

// @ 0x484e40
cSPVector3 cSPEditorHandleRotationRing::GetRotationAxis(bool inWorld)
{
    if (mBlock && inWorld) return mRotationAxis * mBlock->GetOrientation();
    else return mRotationAxis;
}

// @ 0x484ee0
cSPVector3 cSPEditorHandleRotationRing::GetForwardVector(bool inWorld)
{
    if (mBlock && inWorld) return mForwardVector * mBlock->GetOrientation();
    else return mForwardVector;
}

// @ 0x484f80
cSPVector3 cSPEditorHandleRotationRing::GetHandleDirection(bool useBlock)
{
    cSPTransform t; ScratchSlots<1>();
    if (useBlock) t.SetRotation(mBlock->GetOrientation());
    else t.SetRotation(cSPMatrix3::IDENTITY);
    t.PreRotate(GetRotationAxis(true), mHandleRotation);
    switch (mRotationAxisID) {
    case 0x67489dc: return -t.mRotation.yAxis;
    case 0x3bc16bcd: return t.GetRotation().xAxis;
    case 0x1d369ee: return t.GetRotation().xAxis;
    default: return t.GetRotation().xAxis;
    }
}

// @ 0x485110
float cSPEditorHandleRotationRing::GetRadius()
{
    if (!mIsHiddenHandle) {
        float scale = 1.0f;
        if (mBlock->GetEditorModel())
            scale = (mBlock->GetEditorModel()->GetScale() != 0.0f) ? mBlock->GetEditorModel()->GetScale() * 0.5f : 1.0f;
        return (0.05f * scale + mUnscaledRadius) * mBlock->GetScale() * mCustomScale;
    } else {
        return mDistanceFromBoundingBox * mBlock->GetScale();
    }
}

// @ 0x485200
void cSPEditorHandleRotationRing::SetBoundingBox(const cSPBoundingBox& box)
{
    if (!box.IsEmpty()) {
        cSPVector3 p15(box.mMin);
        cSPVector3 p12(box.mMax);
        switch (mRotationAxisID) {
        case 0x67489dc: p15[0] = 0.0f; p12[0] = 0.0f; break;
        case 0x3bc16bcd: p15[1] = 0.0f; p12[1] = 0.0f; break;
        case 0x1d369ee: p15[2] = 0.0f; p12[2] = 0.0f; break;
        }
        ScratchSlots<2>();
        float v18 = Length(p12);
        float n35 = Length(p15);
        mUnscaledRadius = Max(v18, n35);
    } else {
        mUnscaledRadius = 0.0f;
    }
    if (0.0f >= mUnscaledRadius || mUnscaledRadius > 100.0f)
        mUnscaledRadius = 0.0f;
    mDistanceFromBoundingBox = GetHandleRadiusBasedOnBoundingBox();
    UpdateAnimTime();
    if (IsVisible()) ApplyAnimTime();
    else mCurrentAnimTime = -1.0f;
}

// @ 0x485420
float cSPEditorHandleRotationRing::CalculateAnimTime()
{
    float count = 0.85714287f;
    cIModelWorld* p = mBlock->GetModelWorld();
    if (p && mModel) {
        float t30 = (mBlock->GetModelScale() != 0.0f) ? mBlock->GetModelScale() * 0.5f : 1.0f;
        float t9 = 0.0f;
        float src = 0.0f;
        p->GetAnimRange(mModel, mAnimID, &t9, &src, 0);
        float n28 = GetRadius();
        float dst = (src - t9) * n28 * 0.333f * (1.0f / t30) * count + t9;
        return dst;
    } else {
        return 0.0f;
    }
}

// @ 0x485550
void cSPEditorHandleRotationRing::ApplyAnimTime()
{
    cIModelWorld* pWorld = mBlock->GetModelWorld();
    if (pWorld && mAnimID) {
        float target = mTargetAnimTime;
        if (Abs(target - mCurrentAnimTime) > 1.5258789e-05f) {
            if (IsVisible()) {
                mCurrentAnimTime = target;
                pWorld->SetAnimTime(mModel, mAnimID, target, 0);
                pWorld->UpdateModel(mModel, 0);
            } else {
                mCurrentAnimTime = -1.0f;
            }
        }
    }
}

// @ 0x485650
void cSPEditorHandleRotationRing::UpdateAnimTime()
{
    cIModelWorld* pWorld = mBlock->GetModelWorld();
    if (pWorld && mAnimID)
        mTargetAnimTime = CalculateAnimTime();
}

// @ 0x485690
void cSPEditorHandleRotationRing::SetState(int state, bool b)
{
    cSPEditorHandle::SetState(state, b);
    if (IsVisible()) ApplyAnimTime();
}

// @ 0x4856d0
void cSPEditorHandleRotationRing::AnimateOn()
{
    if (!mModel) return;
    cAnimManager* t15 = GetAnimManager();
    cIModelWorld* ptr = mBlock->GetModelWorld();
    if (t15 && ptr) {
        float h = CalculateAnimTime();
        float elem = 0.0f;
        float p33 = 0.0f;
        ptr->GetAnimRange(mModel, mAnimID, &elem, &p33, 0);
        ApplyAnimTime();
        t15->QueueAnim(mModel, ptr, mAnimID, elem, h, 3);
        t15->StartAnim(mModel, 4, GetStateTime(3, mAnimateInTime, true));
    }
}

// @ 0x485850
void cSPEditorHandleRotationRing::SetModelScale(float scale)
{
    if (mModel && mActLikeBall)
        mModel->GetTransform().SetScale(scale);
}

// @ 0x4858b0
void cSPEditorHandleRotationRing::Shutdown()
{
    cSPEditorHandle::Shutdown();
    mActLikeBall = false;
    mModelInstance = 0;
    mCurrentAnimTime = -1.0f;
}

// ---- limb joints: tree of joints, each with a target / original position ----
template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];   // retail: 0x14 bytes
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28

    cSPEditorLimbJoint* GetUpperUpperJoint();
    void SetTargetPosition(cSPVector3 pos);
    void Move(cSPVector3 delta, bool relative);
    void MoveLowerJoints(cSPVector3 delta);
    void Translate(cSPVector3 delta);
};

// @ 0x485900
cSPEditorLimbJoint* cSPEditorLimbJoint::GetUpperUpperJoint()
{
    if (mUpperJoint) return mUpperJoint->mUpperJoint;
    else return 0;
}

// @ 0x485930
void cSPEditorLimbJoint::SetTargetPosition(cSPVector3 pos)
{
    mTargetPosition = pos;
}

// @ 0x485960
void cSPEditorLimbJoint::Move(cSPVector3 delta, bool relative)
{
    if (relative) mTargetPosition += delta;
    else mTargetPosition = mOriginalPosition + delta;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Move(delta, relative);
}

// @ 0x485a60
void cSPEditorLimbJoint::MoveLowerJoints(cSPVector3 delta)
{
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Move(delta, true);
}

// @ 0x485af0
void cSPEditorLimbJoint::Translate(cSPVector3 delta)
{
    mOriginalPosition += delta;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Translate(delta);
}

}  // namespace SP
