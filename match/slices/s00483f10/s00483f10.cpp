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
struct Vec3Op : Vector3T {
    Vec3Op() {}
    Vec3Op& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& o);                        // Matrix3::Assign @ 0x41cb40, out of line
    static const cSPMatrix3 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPTransform;
struct Vec3C : Vector3T {                       // Vector3 with an out-of-line copy ctor
    Vec3C(const Vector3T& v);                               // @ 0x4098a0
};
struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    void Transform(const cSPTransform& t);                  // @ 0x409dd0
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
    Vector3T mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // @ 0x409930
    const cSPMatrix3& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetTranslation(const Vector3T& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    float GetScale() const { return mScale; }
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

#define PV(n) virtual void _v##n();
namespace SP {

struct cMWObject {
    struct cIModelWorld* mWorld;
    uint32_t mFlags;
    cSPTransform mTransform;                    // +0x08
    int mRefCount;                              // +0x40
    void AddRef() { mRefCount++; }
    cSPTransform& GetTransform() { return mTransform; }
};
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    __forceinline void set(uint32_t n, bool value) {
        if (n < N) {
            if (value) {
                uint32_t* pWord = &mWord[n >> 5];
                *pWord |= 1u << (n % 32);
            } else {
                uint32_t* pWord = &mWord[n >> 5];
                *pWord &= ~(1u << (n % 32));
            }
        }
    }
};
struct cMWModel : cMWObject {
    bitset<64> mGroups;                         // +0x44
    cSPVector3 mColor;                          // +0x4c
    float mAlpha;                               // +0x58
    char pad5c[0x70 - 0x5c];
    cSPBoundingBox mBoundingBox;                // +0x70
};
struct IModelManager {
    virtual int AddRef(); virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual int GetGroupFlag(uint32_t groupID, int arg);                                    // 0x28
};

struct cIModelWorld {
    virtual int AddRef();                                                                   // 0x00
    PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    virtual int GetAnimCount(cMWModel* model, int flags);                                   // 0x68
    virtual void GetAnimIDs(cMWModel* model, uint32_t* ids, int flags);                     // 0x6c
    PV(28)
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
    char pad2[0x48 - 0x2c];
    Vector3T mPosition;                         // +0x48
    char pad2b[0x60 - 0x54];
    cSPMatrix3 mOrientation;                    // +0x60
    char pad3[0x1d8 - 0x84];
    float mScale;                               // +0x1d8
    const cSPMatrix3& RawOrientation() const { return mOrientation; }
    const Vector3T& RawPosition() const { return mPosition; }
    const cSPMatrix3& GetOrientation() const { const cSPMatrix3& r = RawOrientation(); return r; }
    const Vector3T& GetPosition() const { const Vector3T& r = RawPosition(); return r; }
    cSPEditorModel* GetEditorModel() const { return mEditorModel; }
    cIModelWorld* GetModelWorld() const { return mModelWorld; }
    float GetScale() const { return mScale; }
    float GetModelScale();                                                                  // @ 0x435c00
    cSPBoundingBox GetBBox(int mode, bool a, bool b);                                       // @ 0x44ae00
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
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual void OnInitFailed();                                                            // 0x1c
    PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
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
    void Init(cSPEditorBlock* block, bool loadProps, uint32_t modelKey, uint32_t overdrawKey); // @ 0x47db30
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
    bool mUnk92;                                // +0x92
    float mDistanceFromBoundingBox;             // +0x94 (retail: read back by GetRadius)
    float mBallOffset;                          // +0x98

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

    cSPVector3 GetHandlePosition();                                                         // 0x4845d0 (see RotationRing below)
    void Update();                                                                     // @ 0x483f10
    void Resume(IModelManager* modelMgr, cSPEditorBlock* block, uint32_t modelKey, uint32_t axisID,
              uint32_t placement, float angleDeg, float offset, float scale, bool hidden, bool loadProps); // @ 0x4849e0
    void CalculateBallOffset();                                                             // @ 0x484820
};

extern const cSPVector3 kZeroVec;      // @ 0x15d5a38
extern const cSPVector3 kAxisA;        // @ 0x15d58d0
extern const cSPVector3 kAxisB;        // @ 0x15d5888
extern const cSPVector3 kAxisC;        // @ 0x15d5954
extern const cSPVector3 kModelColor;   // @ 0x15d59f8
bool IntersectRayBox(const Vector3T& end, const Vector3T& origin, const cSPBoundingBox& box, float* t); // @ 0x6989d0
Vector3T operator*(const Vector3T& v, const float& s);                                     // @ 0x41dca0

// @ 0x484640
float cSPEditorHandleRotationRing::GetHandleRadiusBasedOnBoundingBox()
{
    if (!mModel || !mBlock) return 0.0f;
    cSPBoundingBox val = mBlock->GetBBox(2, false, false);
    cSPTransform ok;
    ok.SetRotation(cSPMatrix3::IDENTITY);
    ok.SetTranslation(kZeroVec);
    ok.SetScale(1.0f);
    val.Transform(ok);
    ScratchSlots<40>();
    cSPVector3 t12 = GetHandleDirection(false);
    cSPVector3 p22 = kZeroVec;
    float v40 = 100.0f;
    cSPVector3 res = t12 * v40;
    float v15 = mCustomScale;
    float q;
    if (IntersectRayBox(res, p22, val, &q))
        v15 = (1.0f - q) * v40;
    float p30 = v15 + mBallOffset;
    return p30;
}

// @ 0x484820
void cSPEditorHandleRotationRing::CalculateBallOffset()
{
    if (mBlock) {
        cSPBoundingBox chunk = mBlock->GetBBox(2, false, false);
        cSPTransform p15;
        p15.SetRotation(cSPMatrix3::IDENTITY);
        p15.SetTranslation(kZeroVec);
        p15.SetScale(1.0f);
        chunk.Transform(p15);
        ScratchSlots<40>();
        cSPVector3 v32 = GetHandleDirection(false);
        float tmp = 100.0f;
        cSPVector3 n25 = kZeroVec;
        cSPVector3 u = v32 * tmp;
        float v4;
        if (IntersectRayBox(u, n25, chunk, &v4))
            mBallOffset = mCustomScale - (1.0f - v4) * tmp;
        else
            mBallOffset = 0.0f;
    }
}

// @ 0x483f10
void cSPEditorHandleRotationRing::Update()
{
    if (!mModel) return;
    cSPMatrix3 hash(mBlock->GetOrientation());
    float t25 = mBlock->mScale;
    cSPBoundingBox v26 = mBlock->GetBBox(2, false, false);
    cSPTransform v13;
    v13.SetRotation(cSPMatrix3::IDENTITY);
    v13.SetTranslation(kZeroVec);
    v13.SetScale(t25);
    v26.Transform(v13);
    Vec3C v1(mBlock->GetPosition());
    Vec3C p4(kZeroVec);
    cSPMatrix3 chunk(hash);
    int n31 = 0;
    switch (mRotationAxisID) {
    case 0x67489dc:
        n31 = 0;
        chunk.xAxis = -hash.yAxis;
        chunk.yAxis = hash.xAxis;
        chunk.zAxis = hash.zAxis;
        p4[0] = mOffset * t25;
        break;
    case 0x3bc16bcd:
        n31 = 1;
        chunk.xAxis = hash.xAxis;
        chunk.yAxis = hash.yAxis;
        chunk.zAxis = hash.zAxis;
        p4[1] = mOffset * t25;
        break;
    case 0x1d369ee:
        n31 = 2;
        chunk.xAxis = hash.xAxis;
        chunk.yAxis = hash.zAxis;
        chunk.zAxis = -hash.yAxis;
        p4[2] = mOffset * t25;
        break;
    }
    float v37 = v26.mMin[n31];
    float mem = v26.mMax[n31];
    float v34 = mModel->mBoundingBox.mMin[1] * mModel->GetTransform().GetScale();
    float v16 = mModel->mBoundingBox.mMax[1] * mModel->GetTransform().GetScale();
    float p18 = (v34 + v16) / 2.0f;
    switch (mHandlePlacement) {
    case 0xe864ba60: p4[n31] += (v37 - v34); break;
    case 0x76822486: p4[n31] += ((mem + v37) / 2.0f - p18); break;
    case 0x406ccc4a: p4[n31] += (mem - v16); break;
    }
    cSPVector3 buf = p4 * hash;
    v1 += buf;
    ScratchSlots<40>();
    cSPTransform p30;
    p30.SetRotation(chunk);
    p30.PreRotate(GetRotationAxis(true), mHandleRotation);
    mModel->GetTransform().SetRotation(p30.mRotation);
    mModel->GetTransform().SetTranslation(v1);
}

// @ 0x4849e0
void cSPEditorHandleRotationRing::Resume(IModelManager* modelMgr, cSPEditorBlock* block, uint32_t modelKey,
                                       uint32_t axisID, uint32_t placement, float angleDeg, float offset,
                                       float scale, bool hidden, bool loadProps)
{
    cSPEditorHandle::Init(block, loadProps, modelKey, 0);
    if (!mBlock) return;
    mIsHiddenHandle = hidden;
    cSPBoundingBox n12 = mBlock->GetBBox(1, false, false);
    int p30 = 0;
    switch (axisID) {
    case 0x67489dc:
        p30 = 0;
        mRotationAxis = kAxisA;
        mForwardVector = kAxisB;
        break;
    case 0x3bc16bcd:
        p30 = 1;
        mRotationAxis = kAxisC;
        mForwardVector = kAxisB;
        break;
    case 0x1d369ee:
        p30 = 2;
        mRotationAxis = kAxisB;
        mForwardVector = kAxisC;
        break;
    }
    mRotationAxisID = axisID;
    mHandlePlacement = placement;
    mOffset = offset;
    mCustomScale = scale;
    mModelInstance = modelKey;
    mHandleRotation = 0.017453292f * angleDeg;
    mCurrentAnimTime = -1.0f;
    mActLikeBall = true;
    mUnk92 = false;
    if (mIsHiddenHandle) CalculateBallOffset();
    if (mModel) {
        mModel->mGroups.set(modelMgr->GetGroupFlag(0x31390732, 0), true);
        mModel->GetTransform().SetScale(0.5f);
        mModel->mColor = kModelColor;
        cIModelWorld* n12 = mBlock->mModelWorld;
        if (n12->GetAnimCount(mModel, 0) == 1)
            n12->GetAnimIDs(mModel, &mAnimID, 0);
        else
            mActLikeBall = false;
        float t29 = 0.0f;
        float z = 0.0f;
        n12->GetAnimRange(mModel, mAnimID, &t29, &z, 0);
        float p30 = (z - t29) * 0.1f + t29;
        n12->SetAnimTime(mModel, mAnimID, p30, 0);
    } else {
        mActLikeBall = false;
    }
    if (!mActLikeBall) OnInitFailed();
}

}  // namespace SP

// ---- legacy-layout section (kept: GetPropListKey is byte-exact) ----
struct Vector3 { float x, y, z; };

struct cMWModel {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    char pad08[0x3c];
    int mRefCount;             // +0x40
};

struct RotationRing {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    void*  mBlock;             // +0x10
    cMWModel* mModel;          // +0x14
    cMWModel* mOverdrawModel;  // +0x18
    char   pad1c[0x64];        // +0x1c .. +0x7f
    float  mUnk80;             // +0x80
    float  mCustomScale;       // +0x84
    char   pad88[0x08];

    Vector3* GetHandlePosition(Vector3* out);           // 0x4845d0
    Vector3* GetPropListKey(Vector3* out);               // 0x484e00
    void     GetHandleDirection(Vector3* out, bool flag); // 0x484f80
};

Vector3* VMul(Vector3* out, const Vector3* v, const float* s);  // @ 0x0041dca0
void*    EditorTuning();                                        // @ 0x00401070

// @ 0x004845d0
Vector3* RotationRing::GetHandlePosition(Vector3* out)
{
    Vector3 dir;
    this->GetHandleDirection(&dir, false);
    float scale = this->mCustomScale;
    Vector3 r;
    VMul(&r, &dir, &scale);
    out->x = r.x;
    out->y = r.y;
    out->z = r.z;
    return out;
}

// @ 0x00484e00
Vector3* RotationRing::GetPropListKey(Vector3* out)
{
    char* t = (char*)EditorTuning();
    *(Vector3*)out = *(Vector3*)(t + 0xa8);
    return out;
}

