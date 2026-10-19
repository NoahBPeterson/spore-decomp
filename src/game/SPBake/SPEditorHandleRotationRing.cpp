// src/game/SPBake/SPEditorHandleRotationRing.cpp -- migrated from slice(s) s00484e40, s00483f10, s004834d0, s0047e4b0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorHandleRotationRing.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorHandleRotationRing.h"
#include "cSPVector3.h"
#include "SP/cMWModel.h"
#include "cSPTransform.h"
#include "SP/cIModelWorld.h"
#include "SP/cMWObject.h"
#include "cSPBoundingBox.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorModel.h"
#include "cSPMatrix3.h"
#include "SP/cSPEditorLimbJoint.h"

// ---- items of slice s0047e4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
struct Bitset32 {
    uint32_t mWord[1];
    void set(int i, bool value)
    {
        if (i < 32) {
            if (value)
                mWord[i / 32] |= (1u << (i % 32));
            else
                mWord[i / 32] &= ~(1u << (i % 32));
        }
    }
    bool test(int i) const { return (mWord[i / 32] & (1u << (i % 32))) != 0; }
};
struct Vector3 { float x, y, z; };
struct cPropertyList;
struct cSPEditorBlock;
struct cPropertyList {
    void** vptr;
};
struct cSPTransform_s0047_e4b0 {
    uint16_t pad0;                 // +0x00
    uint16_t mModificationCount;   // +0x02
    char     pad4[0x0c];
    float    mScale;               // +0x10
};
struct cMWModel {
    void* mWorld;                 // +0x00
    Bitset32 mFlags;              // +0x04
    cSPTransform_s0047_e4b0 mTransform;      // +0x08
    uint32_t pad1c[9];            // +0x1c
    int    mRefCount;             // +0x40
    uint32_t pad44[2];            // +0x44
    Vector3 mColor;               // +0x4c
    float  mAlpha;                // +0x58
    void AddRef() { mRefCount = mRefCount + 1; }
    void Release();
    void SetFlag(bool b);         // @ 0x00437f70
};
struct cSPEditorHandle {
    void** vptr;                  // +0x00
    void** vptr2;                 // +0x04
    int    mUnk8;                 // +0x08
    cPropertyList* mPropList;     // +0x0c
    cSPEditorBlock* mBlock;       // +0x10
    cMWModel* mModel;             // +0x14
    cMWModel* mOverdrawModel;     // +0x18
    int    mCurrentState;         // +0x1c
    float  mFadeInTime;           // +0x20
    float  mFadeOutTime;          // +0x24
    float  mAnimateInTime;        // +0x28
    float  mAnimateOutTime;       // +0x2c
    uint32_t mDefaultModelKey[3]; // +0x30
    uint32_t mDefaultOverdrawKey[3]; // +0x3c
    bool   mHasOverdraw;          // +0x48
    float  mDefaultScale;         // +0x4c

    uint32_t SetModelFlags(bool flag, uint8_t highlight);
    void* GetPosition(void* out);
    void* GetZeroVector(void* out);
    float GetHandleAlphaForState(int state);
    float GetOverdrawHandleAlphaForState(int state);
    void* GetHandleColorForState(void* out, int state);
    void* GetOverdrawHandleColorForState(void* out, int state);
    bool IsFlagSet();
    void SetStateFlags();
    uint32_t SetScale(float s);
    void SetState(int state, bool animate);
    cMWModel* GetModel() { return mModel; }
    cMWModel* GetOverdrawModel() { return mOverdrawModel; }
    void BaseConstruct();
    cSPEditorHandle* ConstructDerived();
};
struct cSPEditorBlock {
    char pad[0x48];
    float mPosX, mPosY, mPosZ;    // +0x48
};
// ---- items of slice s0047e4b0 end

// ---- items of slice s004834d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_ringVtbl0;
extern void*  g_ringVtbl1;
struct cSPTransform_s0048_34d0 {
    uint16_t pad0;              // +0x00
    uint16_t mModificationCount;// +0x02
    char     pad4[0x0c];
    float    mScale;            // +0x10
};
struct cMWModel_s0048_34d0 {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    cSPTransform_s0048_34d0 mTransform;   // +0x08
    int mRefCount;             // +0x40
};
struct RotationRing {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    void*  mBlock;             // +0x10
    cMWModel_s0048_34d0* mModel;          // +0x14
    cMWModel_s0048_34d0* mOverdrawModel;  // +0x18
    char   pad1c[0x34];        // +0x1c .. +0x4f
    int    mUnk50;             // +0x50
    Vector3 mVec54;            // +0x54
    Vector3 mVec60;            // +0x60 (pad +0x6c/0x70 ints)
    int    mUnk6c;             // +0x6c
    int    mUnk70;             // +0x70
    int    mUnk74;             // +0x74
    float  mUnk78;             // +0x78
    char   pad7c[0x0c];
    float  mUnk88;             // +0x88
    float  mUnk8c;             // +0x8c
    uint8_t mUnk90;            // +0x90
    uint8_t mUnk91;            // +0x91

    void SetScale2(float s);   // 0x483cc0
    void Shutdown();           // 0x483d10
    RotationRing* Construct(); // 0x483d40
    void Destroy();            // 0x483e90
    void* AsInterface(uint32_t id); // 0x483ec0
    void Resume();             // 0x4834d0, partial
    void Big();                // 0x4837f0, partial

    void BaseConstruct();                               // @ 0x0047d6a0
    void BaseDestroy();                                 // @ 0x0047d870
    void BaseShutdown();                                // @ 0x0047e2c0
    void RingShutdown();                                // @ 0x004858b0
};
// ---- items of slice s004834d0 end

// ---- items of slice s00483f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
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
struct cSPMatrix3_s0048_3f10 : Matrix33T {
    cSPMatrix3_s0048_3f10() {}
    cSPMatrix3_s0048_3f10(const cSPMatrix3_s0048_3f10& o);                        // Matrix3::Assign @ 0x41cb40, out of line
    static const cSPMatrix3_s0048_3f10 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3_s0048_3f10 : Vector3T {
    cSPVector3_s0048_3f10() {}
    cSPVector3_s0048_3f10(const Vector3T& v) : Vector3T(v) {}
    cSPVector3_s0048_3f10& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPTransform_s0048_3f10;
struct Vec3C : Vector3T {                       // Vector3 with an out-of-line copy ctor
    Vec3C(const Vector3T& v);                               // @ 0x4098a0
};
struct cSPBoundingBox_s0048_3f10 {
    cSPVector3_s0048_3f10 mMin, mMax;
    void Transform(const cSPTransform_s0048_3f10& t);                  // @ 0x409dd0
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
};
Vector3T operator*(const Vector3T& v, const Matrix33T& m);   // @ 0x41daf0
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T& operator+=(Vector3T& a, const Vector3T& b);        // @ 0x41ddb0
struct cSPTransform_s0048_3f10 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3T mTranslation;
    float mScale;
    cSPMatrix3_s0048_3f10 mRotation;
    cSPTransform_s0048_3f10();                                          // @ 0x409930
    const cSPMatrix3_s0048_3f10& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3_s0048_3f10& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetTranslation(const Vector3T& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    float GetScale() const { return mScale; }
    void PreRotate(const Vector3T& axis, float angle);       // @ 0x6baba0
};
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
#define PV(n) virtual void _v##n();
namespace SP {
struct cMWObject_s0048_3f10 {
    struct cIModelWorld_s0048_3f10* mWorld;
    uint32_t mFlags;
    cSPTransform_s0048_3f10 mTransform;                    // +0x08
    int mRefCount;                              // +0x40
    void AddRef() { mRefCount++; }
    cSPTransform_s0048_3f10& GetTransform() { return mTransform; }
};
}
namespace SP {
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
}
namespace SP {
struct cMWModel_s0048_3f10 : cMWObject_s0048_3f10 {
    bitset<64> mGroups;                         // +0x44
    cSPVector3_s0048_3f10 mColor;                          // +0x4c
    float mAlpha;                               // +0x58
    char pad5c[0x70 - 0x5c];
    cSPBoundingBox_s0048_3f10 mBoundingBox;                // +0x70
};
}
namespace SP {
struct IModelManager {
    virtual int AddRef(); virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual int GetGroupFlag(uint32_t groupID, int arg);                                    // 0x28
};
}
namespace SP {
struct cIModelWorld_s0048_3f10 {
    virtual int AddRef();                                                                   // 0x00
    PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    virtual int GetAnimCount(cMWModel_s0048_3f10* model, int flags);                                   // 0x68
    virtual void GetAnimIDs(cMWModel_s0048_3f10* model, uint32_t* ids, int flags);                     // 0x6c
    PV(28)
    virtual void SetAnimTime(cMWModel_s0048_3f10* model, uint32_t animID, float time, int flags);      // 0x74
    PV(30) PV(31)
    virtual void GetAnimRange(cMWModel_s0048_3f10* model, uint32_t animID, float* start, float* end, int flags); // 0x80
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60)
    PV(61) PV(62) PV(63) PV(64) PV(65) PV(66)
    virtual void UpdateModel(cMWModel_s0048_3f10* model, int flags);                                   // 0x10c
};
}
namespace SP {
struct cSPEditorModel_s0048_3f10 {
    float GetScale();                                                                       // @ 0x4adaa0
};
}
namespace SP {
struct cSPEditorBlock_s0048_3f10 {
    char pad0[0x18];
    AutoRefCount<cIModelWorld_s0048_3f10> mModelWorld;     // +0x18
    char pad1[0x28 - 0x1c];
    cSPEditorModel_s0048_3f10* mEditorModel;               // +0x28
    char pad2[0x48 - 0x2c];
    Vector3T mPosition;                         // +0x48
    char pad2b[0x60 - 0x54];
    cSPMatrix3_s0048_3f10 mOrientation;                    // +0x60
    char pad3[0x1d8 - 0x84];
    float mScale;                               // +0x1d8
    const cSPMatrix3_s0048_3f10& RawOrientation() const { return mOrientation; }
    const Vector3T& RawPosition() const { return mPosition; }
    const cSPMatrix3_s0048_3f10& GetOrientation() const { const cSPMatrix3_s0048_3f10& r = RawOrientation(); return r; }
    const Vector3T& GetPosition() const { const Vector3T& r = RawPosition(); return r; }
    cSPEditorModel_s0048_3f10* GetEditorModel() const { return mEditorModel; }
    cIModelWorld_s0048_3f10* GetModelWorld() const { return mModelWorld; }
    float GetScale() const { return mScale; }
    float GetModelScale();                                                                  // @ 0x435c00
    cSPBoundingBox_s0048_3f10 GetBBox(int mode, bool a, bool b);                                       // @ 0x44ae00
};
}
namespace SP {
struct cSPEditorHandle_s0048_3f10 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual void OnInitFailed();                                                            // 0x1c
    PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual float GetStateTime(int state, float time, bool b);                              // 0x38
    void* mpVtbl2;                              // +0x04
    int mRefCount;                              // +0x08
    void* mPropList;                            // +0x0c
    cSPEditorBlock_s0048_3f10* mBlock;                     // +0x10
    AutoRefCount<cMWModel_s0048_3f10> mModel;              // +0x14
    AutoRefCount<cMWModel_s0048_3f10> mOverdrawModel;      // +0x18
    int mCurrentState;                          // +0x1c
    float mFadeInTime;                          // +0x20
    float mFadeOutTime;                         // +0x24
    float mAnimateInTime;                       // +0x28
    float mAnimateOutTime;                      // +0x2c
    char mKeys[0x48 - 0x30];
    bool mHasOverdraw;                          // +0x48
    float mDefaultScale;                        // +0x4c

    void SetState(int state, bool b);                                                       // @ 0x47ec40
    void Init(cSPEditorBlock_s0048_3f10* block, bool loadProps, uint32_t modelKey, uint32_t overdrawKey); // @ 0x47db30
    bool IsVisible();                                                                       // @ 0x47f290
    void Shutdown();                                                                        // @ 0x47e2c0
};
}
namespace SP {
struct cSPEditorHandleRotationRing_s0048_3f10 : cSPEditorHandle_s0048_3f10 {
    uint32_t mModelInstance;                    // +0x50
    cSPVector3_s0048_3f10 mRotationAxis;                   // +0x54
    cSPVector3_s0048_3f10 mForwardVector;                  // +0x60
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

    cSPVector3_s0048_3f10 GetRotationAxis(bool inWorld);
    cSPVector3_s0048_3f10 GetForwardVector(bool inWorld);
    cSPVector3_s0048_3f10 GetHandleDirection(bool useBlock);  // 0x00484f80 (SP::cSPEditorHandleRotationRing::GetHandleDirection)
    float GetRadius();
    void SetBoundingBox(const cSPBoundingBox_s0048_3f10& box);
    float CalculateAnimTime();
    void ApplyAnimTime();
    void UpdateAnimTime();
    void SetState(int state, bool b);  // 0x00485690 (SP::cSPEditorHandleRotationRing::SetState)
    void AnimateOn();  // 0x004856d0 (SP::cSPEditorHandleRotationRing::AnimateOn)
    void SetModelScale(float scale);
    void Shutdown();  // 0x004858b0 (SP::cSPEditorHandleRotationRing::Shutdown)
    float GetHandleRadiusBasedOnBoundingBox();                                              // @ 0x484640

    cSPVector3_s0048_3f10 GetHandlePosition();                                                         // 0x4845d0 (see RotationRing below)
    void Update();                                                                     // @ 0x483f10
    void Resume(IModelManager* modelMgr, cSPEditorBlock_s0048_3f10* block, uint32_t modelKey, uint32_t axisID,
              uint32_t placement, float angleDeg, float offset, float scale, bool hidden, bool loadProps); // @ 0x4849e0
    void CalculateBallOffset();                                                             // @ 0x484820
};
}
namespace SP {
extern const cSPVector3_s0048_3f10 kZeroVec;      // @ 0x15d5a38
}
namespace SP {
extern const cSPVector3_s0048_3f10 kAxisA;        // @ 0x15d58d0
}
namespace SP {
extern const cSPVector3_s0048_3f10 kAxisB;        // @ 0x15d5888
}
namespace SP {
extern const cSPVector3_s0048_3f10 kAxisC;        // @ 0x15d5954
}
namespace SP {
extern const cSPVector3_s0048_3f10 kModelColor;   // @ 0x15d59f8
}
namespace SP {
bool IntersectRayBox(const Vector3T& end, const Vector3T& origin, const cSPBoundingBox_s0048_3f10& box, float* t); // @ 0x6989d0
}
namespace SP {
Vector3T operator*(const Vector3T& v, const float& s);                                     // @ 0x41dca0
}
struct cMWModel_s0048_3f10 {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    char pad08[0x3c];
    int mRefCount;             // +0x40
};
struct RotationRing_s0048_3f10 {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    void*  mBlock;             // +0x10
    cMWModel_s0048_3f10* mModel;          // +0x14
    cMWModel_s0048_3f10* mOverdrawModel;  // +0x18
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
// ---- items of slice s00483f10 end

// ---- items of slice s00484e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPMatrix3_s0048_4e40 : Matrix33T {
    static const cSPMatrix3_s0048_4e40 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3_s0048_4e40 : Vector3T {
    cSPVector3_s0048_4e40() {}
    cSPVector3_s0048_4e40(const Vector3T& v) : Vector3T(v) {}
    cSPVector3_s0048_4e40& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox_s0048_4e40 {
    cSPVector3_s0048_4e40 mMin, mMax;
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
};
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
inline float Length(const Vector3T& v) { return VectorLength(v); }
inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }
inline float Abs(float x) { float r = (float)fabs(x); return r; }
struct cSPTransform_s0048_4e40 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3_s0048_4e40 mTranslation;
    float mScale;
    cSPMatrix3_s0048_4e40 mRotation;
    cSPTransform_s0048_4e40();                                          // @ 0x409930
    const cSPMatrix3_s0048_4e40& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3_s0048_4e40& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void PreRotate(const Vector3T& axis, float angle);       // @ 0x6baba0
};
namespace SP {
struct cMWObject_s0048_4e40 {
    struct cIModelWorld_s0048_4e40* mWorld;
    uint32_t mFlags;
    cSPTransform_s0048_4e40 mTransform;                    // +0x08
    int mRefCount;                              // +0x40
    void AddRef() { mRefCount++; }
    cSPTransform_s0048_4e40& GetTransform() { return mTransform; }
};
}
namespace SP {
struct cMWModel_s0048_4e40 : cMWObject_s0048_4e40 { };
}
namespace SP {
#define PV(n) virtual void _v##n();
}
namespace SP {
struct cIModelWorld_s0048_4e40 {
    virtual int AddRef();                                                                   // 0x00
    PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual void SetAnimTime(cMWModel_s0048_4e40* model, uint32_t animID, float time, int flags);      // 0x74
    PV(30) PV(31)
    virtual void GetAnimRange(cMWModel_s0048_4e40* model, uint32_t animID, float* start, float* end, int flags); // 0x80
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60)
    PV(61) PV(62) PV(63) PV(64) PV(65) PV(66)
    virtual void UpdateModel(cMWModel_s0048_4e40* model, int flags);                                   // 0x10c
};
}
namespace SP {
struct cSPEditorModel_s0048_4e40 {
    float GetScale();                                                                       // @ 0x4adaa0
};
}
namespace SP {
struct cSPEditorBlock_s0048_4e40 {
    char pad0[0x18];
    AutoRefCount<cIModelWorld_s0048_4e40> mModelWorld;     // +0x18
    char pad1[0x28 - 0x1c];
    cSPEditorModel_s0048_4e40* mEditorModel;               // +0x28
    char pad2[0x60 - 0x2c];
    cSPMatrix3_s0048_4e40 mOrientation;                    // +0x60
    char pad3[0x1d8 - 0x84];
    float mScale;                               // +0x1d8
    const cSPMatrix3_s0048_4e40& GetOrientation() const { return mOrientation; }
    cSPEditorModel_s0048_4e40* GetEditorModel() const { return mEditorModel; }
    cIModelWorld_s0048_4e40* GetModelWorld() const { return mModelWorld; }
    float GetScale() const { return mScale; }
    float GetModelScale();                                                                  // @ 0x435c00
};
}
namespace SP {
struct cAnimManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void StartAnim(AutoRefCount<cMWModel_s0048_4e40> model, int type, float time);            // 0x18
    PV(7)
    virtual void QueueAnim(AutoRefCount<cMWModel_s0048_4e40> model, AutoRefCount<cIModelWorld_s0048_4e40> world,
                           uint32_t animID, float start, float end, int type);             // 0x20
};
}
namespace SP {
cAnimManager* GetAnimManager();                                                             // @ 0x401060
}
namespace SP {
struct cSPEditorHandle_s0048_4e40 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual float GetStateTime(int state, float time, bool b);                              // 0x38
    void* mpVtbl2;                              // +0x04
    int mRefCount;                              // +0x08
    void* mPropList;                            // +0x0c
    cSPEditorBlock_s0048_4e40* mBlock;                     // +0x10
    AutoRefCount<cMWModel_s0048_4e40> mModel;              // +0x14
    AutoRefCount<cMWModel_s0048_4e40> mOverdrawModel;      // +0x18
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
}
namespace SP {
struct cSPEditorHandleRotationRing_s0048_4e40 : cSPEditorHandle_s0048_4e40 {
    uint32_t mModelInstance;                    // +0x50
    cSPVector3_s0048_4e40 mRotationAxis;                   // +0x54
    cSPVector3_s0048_4e40 mForwardVector;                  // +0x60
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

    cSPVector3_s0048_4e40 GetRotationAxis(bool inWorld);
    cSPVector3_s0048_4e40 GetForwardVector(bool inWorld);
    cSPVector3_s0048_4e40 GetHandleDirection(bool useBlock);  // 0x00484f80 (SP::cSPEditorHandleRotationRing::GetHandleDirection)
    float GetRadius();
    void SetBoundingBox(const cSPBoundingBox_s0048_4e40& box);
    float CalculateAnimTime();
    void ApplyAnimTime();
    void UpdateAnimTime();
    void SetState(int state, bool b);  // 0x00485690 (SP::cSPEditorHandleRotationRing::SetState)
    void AnimateOn();  // 0x004856d0 (SP::cSPEditorHandleRotationRing::AnimateOn)
    void SetModelScale(float scale);
    void Shutdown();  // 0x004858b0 (SP::cSPEditorHandleRotationRing::Shutdown)
    float GetHandleRadiusBasedOnBoundingBox();                                              // @ 0x484640
};
}
// ---- items of slice s00484e40 end

// @ 0x0047e4b0
uint32_t cSPEditorHandle::SetModelFlags(bool flag, uint8_t highlight)
{
    if (this->mModel) {
        this->mModel->mFlags.set(3, flag);
        *(uint8_t*)((char*)this->mModel + 0x5c) = highlight;
    }
    if (this->mOverdrawModel) {
        this->mOverdrawModel->mFlags.set(3, flag);
        *(uint8_t*)((char*)this->mOverdrawModel + 0x5c) = highlight;
    }
    uint32_t eax = (uint32_t)(uintptr_t)this;
    if (this->mModel || this->mOverdrawModel)
        eax = (eax & 0xFFFFFF00u) | highlight;
    return eax;
}

// @ 0x00483e90
void RotationRing::Destroy()
{
    this->vptr = &g_ringVtbl0;
    this->vptr2 = &g_ringVtbl1;
    this->RingShutdown();
    this->BaseDestroy();
}

// @ 0x00483ec0
void * SP::cSPEditorHandleRotationRing::AsInterface(EA::COM::InterfaceId id)
{
    switch (id) {
    case 0x050a2ed2: return this;
    case 0x050a1fe5: return this;
    case 0xee3f516e: return this;
    }
    return 0;
}

// @ 0x00483f10
namespace SP {
void cSPEditorHandleRotationRing_s0048_3f10::Update()
{
    if (!mModel) return;
    cSPMatrix3_s0048_3f10 hash(mBlock->GetOrientation());
    float t25 = mBlock->mScale;
    cSPBoundingBox_s0048_3f10 v26 = mBlock->GetBBox(2, false, false);
    cSPTransform_s0048_3f10 v13;
    v13.SetRotation(cSPMatrix3_s0048_3f10::IDENTITY);
    v13.SetTranslation(kZeroVec);
    v13.SetScale(t25);
    v26.Transform(v13);
    Vec3C v1(mBlock->GetPosition());
    Vec3C p4(kZeroVec);
    cSPMatrix3_s0048_3f10 chunk(hash);
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
    cSPVector3_s0048_3f10 buf = p4 * hash;
    v1 += buf;
    ScratchSlots<40>();
    cSPTransform_s0048_3f10 p30;
    p30.SetRotation(chunk);
    p30.PreRotate(GetRotationAxis(true), mHandleRotation);
    mModel->GetTransform().SetRotation(p30.mRotation);
    mModel->GetTransform().SetTranslation(v1);
}
}  // namespace SP

// @ 0x004845d0
Vector3* RotationRing_s0048_3f10::GetHandlePosition(Vector3* out)
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

// @ 0x00484640
namespace SP {
float cSPEditorHandleRotationRing_s0048_3f10::GetHandleRadiusBasedOnBoundingBox()
{
    if (!mModel || !mBlock) return 0.0f;
    cSPBoundingBox_s0048_3f10 val = mBlock->GetBBox(2, false, false);
    cSPTransform_s0048_3f10 ok;
    ok.SetRotation(cSPMatrix3_s0048_3f10::IDENTITY);
    ok.SetTranslation(kZeroVec);
    ok.SetScale(1.0f);
    val.Transform(ok);
    ScratchSlots<40>();
    cSPVector3_s0048_3f10 t12 = GetHandleDirection(false);
    cSPVector3_s0048_3f10 p22 = kZeroVec;
    float v40 = 100.0f;
    cSPVector3_s0048_3f10 res = t12 * v40;
    float v15 = mCustomScale;
    float q;
    if (IntersectRayBox(res, p22, val, &q))
        v15 = (1.0f - q) * v40;
    float p30 = v15 + mBallOffset;
    return p30;
}
}  // namespace SP

// @ 0x00484820
namespace SP {
void cSPEditorHandleRotationRing_s0048_3f10::CalculateBallOffset()
{
    if (mBlock) {
        cSPBoundingBox_s0048_3f10 chunk = mBlock->GetBBox(2, false, false);
        cSPTransform_s0048_3f10 p15;
        p15.SetRotation(cSPMatrix3_s0048_3f10::IDENTITY);
        p15.SetTranslation(kZeroVec);
        p15.SetScale(1.0f);
        chunk.Transform(p15);
        ScratchSlots<40>();
        cSPVector3_s0048_3f10 v32 = GetHandleDirection(false);
        float tmp = 100.0f;
        cSPVector3_s0048_3f10 n25 = kZeroVec;
        cSPVector3_s0048_3f10 u = v32 * tmp;
        float v4;
        if (IntersectRayBox(u, n25, chunk, &v4))
            mBallOffset = mCustomScale - (1.0f - v4) * tmp;
        else
            mBallOffset = 0.0f;
    }
}
}  // namespace SP

// @ 0x004849e0
namespace SP {
void cSPEditorHandleRotationRing_s0048_3f10::Resume(IModelManager* modelMgr, cSPEditorBlock_s0048_3f10* block, uint32_t modelKey, uint32_t axisID, uint32_t placement, float angleDeg, float offset, float scale, bool hidden, bool loadProps)
{
    cSPEditorHandle_s0048_3f10::Init(block, loadProps, modelKey, 0);
    if (!mBlock) return;
    mIsHiddenHandle = hidden;
    cSPBoundingBox_s0048_3f10 n12 = mBlock->GetBBox(1, false, false);
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
        cIModelWorld_s0048_3f10* n12 = mBlock->mModelWorld;
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

// @ 0x00484e00
Vector3* RotationRing_s0048_3f10::GetPropListKey(Vector3* out)
{
    char* t = (char*)EditorTuning();
    *(Vector3*)out = *(Vector3*)(t + 0xa8);
    return out;
}

// @ 0x00484e40
namespace SP {
cSPVector3_s0048_4e40 cSPEditorHandleRotationRing_s0048_4e40::GetRotationAxis(bool inWorld)
{
    if (mBlock && inWorld) return mRotationAxis * mBlock->GetOrientation();
    else return mRotationAxis;
}
}  // namespace SP

// @ 0x00484ee0
namespace SP {
cSPVector3_s0048_4e40 cSPEditorHandleRotationRing_s0048_4e40::GetForwardVector(bool inWorld)
{
    if (mBlock && inWorld) return mForwardVector * mBlock->GetOrientation();
    else return mForwardVector;
}
}  // namespace SP

// @ 0x00484f80
namespace SP {
cSPVector3_s0048_4e40 cSPEditorHandleRotationRing_s0048_4e40::GetHandleDirection(bool useBlock)
{
    cSPTransform_s0048_4e40 t; ScratchSlots<1>();
    if (useBlock) t.SetRotation(mBlock->GetOrientation());
    else t.SetRotation(cSPMatrix3_s0048_4e40::IDENTITY);
    t.PreRotate(GetRotationAxis(true), mHandleRotation);
    switch (mRotationAxisID) {
    case 0x67489dc: return -t.mRotation.yAxis;
    case 0x3bc16bcd: return t.GetRotation().xAxis;
    case 0x1d369ee: return t.GetRotation().xAxis;
    default: return t.GetRotation().xAxis;
    }
}
}  // namespace SP

// @ 0x00485110
namespace SP {
float cSPEditorHandleRotationRing_s0048_4e40::GetRadius()
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
}  // namespace SP

// @ 0x00485200
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::SetBoundingBox(const cSPBoundingBox_s0048_4e40& box)
{
    if (!box.IsEmpty()) {
        cSPVector3_s0048_4e40 p15(box.mMin);
        cSPVector3_s0048_4e40 p12(box.mMax);
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
}  // namespace SP

// @ 0x00485420
namespace SP {
float cSPEditorHandleRotationRing_s0048_4e40::CalculateAnimTime()
{
    float count = 0.85714287f;
    cIModelWorld_s0048_4e40* p = mBlock->GetModelWorld();
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
}  // namespace SP

// @ 0x00485550
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::ApplyAnimTime()
{
    cIModelWorld_s0048_4e40* pWorld = mBlock->GetModelWorld();
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
}  // namespace SP

// @ 0x00485650
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::UpdateAnimTime()
{
    cIModelWorld_s0048_4e40* pWorld = mBlock->GetModelWorld();
    if (pWorld && mAnimID)
        mTargetAnimTime = CalculateAnimTime();
}
}  // namespace SP

// @ 0x00485690
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::SetState(int state, bool b)
{
    cSPEditorHandle_s0048_4e40::SetState(state, b);
    if (IsVisible()) ApplyAnimTime();
}
}  // namespace SP

// @ 0x004856d0
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::AnimateOn()
{
    if (!mModel) return;
    cAnimManager* t15 = GetAnimManager();
    cIModelWorld_s0048_4e40* ptr = mBlock->GetModelWorld();
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
}  // namespace SP

// @ 0x00485850
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::SetModelScale(float scale)
{
    if (mModel && mActLikeBall)
        mModel->GetTransform().SetScale(scale);
}
}  // namespace SP

// @ 0x004858b0
namespace SP {
void cSPEditorHandleRotationRing_s0048_4e40::Shutdown()
{
    cSPEditorHandle_s0048_4e40::Shutdown();
    mActLikeBall = false;
    mModelInstance = 0;
    mCurrentAnimTime = -1.0f;
}
}  // namespace SP
