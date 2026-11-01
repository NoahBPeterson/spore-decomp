// src/game/SPBake/_at_00480000.cpp -- migrated from slice(s) s0048a4e0, s00489530, s00488600, s00487850, s00486910, s00484e40, s004834d0, s00482670 by tools/migrate/rewrite.py
// Object file: SPBake/_at_00480000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorTrianglePinningInfo.h"
#include "cSPVector3.h"
#include "SP/cMWModel.h"
#include "cSPBoundingBox.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorHandleDeform.h"
#include "cSPMatrix3.h"
#include "cSPTransform.h"
#include "SP/cSPEditorHandleRotationBall.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_ballVtbl0;
extern void* g_ballVtbl1;

// ---- items of slice s00482670 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _v##n();
struct Vector3 { float x, y, z;                  // rw::math::fpu::Vector3Template<float,0>
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s0048_2670 : Vector3 {                       // cSPVector3 (12 bytes)
    cSPVector3_s0048_2670() {}
    cSPVector3_s0048_2670(const Vector3& v) : Vector3(v) {}
    cSPVector3_s0048_2670& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3_s0048_2670 { Vector3 xAxis, yAxis, zAxis; }; // 36 bytes, copied with rep movsd
void* EditorTuning();          // @ 0x00401070
extern Vector3 g_offset;
Vector3 operator*(const Vector3& v, const float& s);        // @ 0x41dca0
Vector3 operator/(const Vector3& v, const float& s);        // @ 0x453880
struct cSPTransform_s0048_2670 {                               // 0x38 bytes
    uint16_t mFlags;                                // +0x00
    uint16_t mModificationCount;                    // +0x02
    Vector3 mTranslation;                           // +0x04
    float mScale;                                   // +0x10
    cSPMatrix3_s0048_2670 mRotation;                           // +0x14
    cSPTransform_s0048_2670();                                 // @ 0x409930
    void SetRotation(const cSPMatrix3_s0048_2670& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetTranslation(const Vector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};
struct cSPBoundingBox_s0048_2670 {                             // 0x18 bytes
    cSPVector3_s0048_2670 mMin, mMax;
    void Transform(const cSPTransform_s0048_2670& t);          // @ 0x409dd0
};
template<int N> struct bitset {                     // eastl::bitset<N>
    uint32_t mWord[(N + 31) / 32];
    __forceinline uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t n, bool value) {
        if (n < N) {
            if (value)
                DoGetWord(n) |= 1u << (n % 32);
            else
                DoGetWord(n) &= ~(1u << (n % 32));
        }
    }
};
template<class T> struct AutoRefCount {             // EA::AutoRefCount<T>: one pointer
    T* mpObject;
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cIModelWorld;                                // only used as a pointer here
struct cSPEditorBlock {
    char pad00[0x18];
    AutoRefCount<cIModelWorld> mModelWorld;         // +0x18
    cSPBoundingBox_s0048_2670 GetBBox(int mode, bool a, bool b);   // @ 0x44ae00
};
#define PV_s0048_2670(n) virtual void _v##n();
struct IModelManager {
virtual int AddRef();
virtual int Release();
    PV_s0048_2670(2) PV_s0048_2670(3) PV_s0048_2670(4) PV_s0048_2670(5) PV_s0048_2670(6) PV_s0048_2670(7) PV_s0048_2670(8) PV_s0048_2670(9)
    virtual unsigned int GetGroupFlag(uint32_t groupID, int arg);   // +0x28
};
struct cMWModel {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    char pad08[0x38];
    int mRefCount;             // +0x40
    bitset<64> mGroups;        // +0x44
};
struct RotationBall {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    cSPEditorBlock* mBlock;    // +0x10
    AutoRefCount<cMWModel> mModel;  // +0x14
    cMWModel* mOverdrawModel;  // +0x18
    char   pad1c[0x34];        // +0x1c .. +0x4f
    cSPVector3_s0048_2670 mOffset;        // +0x50
    bool   mExists;            // +0x5c
    bool   mIsHidden;          // +0x5d
    char   pad5e[2];
    float  mDistanceFromBoundingBox;  // +0x60

    RotationBall* Construct();
    void Destroy();
    void* AsInterface(uint32_t id);
    void UpdateOffset();
    void CalculateBallOffset();
    void Init(IModelManager* o, cSPEditorBlock* block, cSPVector3_s0048_2670 offset, bool flag);
    Vector3* GetTuningOffset(Vector3* out);

    // base-class entry points (defined in other slices; masked relocations)
    void BaseConstruct();                               // @ 0x0047d6a0
    void BaseDestroy();                                 // @ 0x0047d870
    void BaseInit(void*, bool, uint32_t, uint32_t);     // @ 0x0047db30
    void BallCleanup();                                 // @ 0x00483d10
};
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
struct Vec3R : Vec3 {};                 // cSPVector3R: result type of the out-of-line operators
Vec3R operator-(const Vec3& a, const Vec3& b);              // 0x0041db10
Vec3R operator+(const Vec3& a, const Vec3& b);              // 0x0041dc10
Vec3R operator*(const Vec3& a, const float& s);             // 0x0041dca0
// ---- items of slice s00482670 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s004834d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_negOne;
extern float  g_zeroC;
extern void*  g_ringVtbl0;
extern void*  g_ringVtbl1;
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vector3T {                       // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);        // 0x004098A0, out of line
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
typedef Vector3T Vector3_s0048_34d0;
struct cSPVector3_s0048_34d0 : Vector3T {
    cSPVector3_s0048_34d0() {}
    cSPVector3_s0048_34d0(const cSPVector3_s0048_34d0& v) : Vector3T(v) {}
    cSPVector3_s0048_34d0(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix33T {                      // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);      // 0x0041CB40, out of line
};
struct cSPMatrix3_s0048_34d0 : Matrix33T {
    cSPMatrix3_s0048_34d0() {}
    cSPMatrix3_s0048_34d0(const cSPMatrix3_s0048_34d0& m) : Matrix33T(m) {}
};
Vector3T operator*(const Vector3T& v, const float& s);     // 0x0041DCA0
Vector3T operator/(const Vector3T& v, const float& s);     // 0x00453880
Vector3T operator-(const Vector3T& a, const Vector3T& b);  // 0x0041DB10
Vector3T operator+(const Vector3T& a, const Vector3T& b);  // 0x0041DC10
Vector3T operator*(const Vector3T& v, const Matrix33T& m); // 0x0041DAF0
float VectorLength(const Vector3T& v);                     // 0x0040AE50
cSPVector3_s0048_34d0 Normalize(const Vector3T& v);                   // 0x00436CE0
struct cSPTransform_s0048_34d0 {                   // 0x38 bytes
    uint16_t mFlags;                    // +0x00
    uint16_t mModificationCount;        // +0x02
    Vector3T mTranslation;              // +0x04
    float    mScale;                    // +0x10
    cSPMatrix3_s0048_34d0 mRotation;               // +0x14
    cSPTransform_s0048_34d0();                                          // 0x00409930
    void SetRotation(const cSPMatrix3_s0048_34d0& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetTranslation(const Vector3T& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};
struct cMWModel_s0048_34d0 {
    void*    mWorld;                    // +0x00
    uint32_t mFlags;                    // +0x04
    cSPTransform_s0048_34d0 mTransform;            // +0x08
    int      mRefCount;                 // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
};
struct cIModelWorld_s0048_34d0;
template<class T> struct AutoRefCount_s0048_34d0 {
    T* mpObject;
    AutoRefCount_s0048_34d0(T* p) : mpObject(p) {}
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPBoundingBox_s0048_34d0 {                 // 0x18 bytes
    cSPVector3_s0048_34d0 mMin, mMax;
    void Transform(const cSPTransform_s0048_34d0& t);  // 0x00409DD0
};
struct cSPEditorBlock_s0048_34d0 {
    uint32_t pad00[0x18 / 4];           // +0x00
    AutoRefCount_s0048_34d0<cIModelWorld_s0048_34d0> mModelWorld;  // +0x18
    uint32_t pad1c[(0x48 - 0x1c) / 4];  // +0x1c
    Vector3T mPosition;                 // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];  // +0x54
    cSPMatrix3_s0048_34d0 mOrientation;            // +0x60
    uint32_t pad84[(0x1d8 - 0x84) / 4]; // +0x84
    float    mScale;                    // +0x1d8
    cSPBoundingBox_s0048_34d0 GetBBox(int mode, bool a, bool b);  // 0x0044AE00
};
namespace SP {
bool SegmentBoxIntersect(const Vector3T& dir, const Vector3T& origin,
                         const cSPBoundingBox_s0048_34d0& box, float* t);  // 0x006989D0
}
void BuildOrientation(Matrix33T* out, const Vector3T* a, const Vector3T* b);  // 0x004A89E0
extern Vector3T g_zeroVector;            // 0x015D5508
extern const cSPMatrix3_s0048_34d0 g_ballRotation;  // 0x015D53D8
extern const Vector3T g_ballUp;          // 0x015D5358
struct ModelRef {                        // EA::AutoRefCount<cMWModel> by value
    cMWModel_s0048_34d0* p;
    ModelRef(cMWModel_s0048_34d0* m) : p(m) { if (p) p->AddRef(); }
    ModelRef(const ModelRef& r) : p(r.p) { if (p) p->AddRef(); }
};
struct AnimMgr { void** vptr; };
AnimMgr* GetSetting6();                  // 0x00401060
typedef void (__thiscall *AnimFn)(void*, ModelRef, int, float, float, int);
#define PLAY_ANIM(mgr, model, prop, value, time, flag) \
    ((AnimFn)(*(void***)(mgr))[6])((mgr), ModelRef(model), (prop), (value), (time), (flag))
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
    Vector3_s0048_34d0 mVec54;            // +0x54
    Vector3_s0048_34d0 mVec60;            // +0x60 (pad +0x6c/0x70 ints)
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

    void BaseConstruct();                               // @ 0x0047d6a0
    void BaseDestroy();                                 // @ 0x0047d870
    void BaseShutdown();                                // @ 0x0047e2c0
    void RingShutdown();                                // @ 0x004858b0
};
extern Vector3_s0048_34d0 g_ringVecA;
extern Vector3_s0048_34d0 g_ringVecB;
struct RotationBall_s0048_34d0 {
    void** vptr;                       // +0x00
    void** vptr2;                      // +0x04
    int    mUnk8;                      // +0x08
    void*  mPropList;                  // +0x0c
    cSPEditorBlock_s0048_34d0* mBlock;            // +0x10
    cMWModel_s0048_34d0* mModel;                  // +0x14
    cMWModel_s0048_34d0* mOverdrawModel;          // +0x18
    uint32_t pad1c[(0x28 - 0x1c) / 4]; // +0x1c
    float  mAnimateInTime;             // +0x28
    uint32_t pad2c[(0x50 - 0x2c) / 4]; // +0x2c
    cSPVector3_s0048_34d0 mOffset;                // +0x50
    bool   mExists;                    // +0x5c
    bool   mIsHidden;                  // +0x5d
    uint8_t pad5e[2];
    float  mDistanceFromBoundingBox;   // +0x60

    cSPVector3_s0048_34d0 Resume();                   // 0x4834d0 (hidden cSPVector3 return)
    void Update();                         // 0x4837f0
};
// ---- items of slice s004834d0 end

// ---- items of slice s00484e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
struct Vector3T_s0048_4e40 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s0048_4e40() {}
    Vector3T_s0048_4e40(const Vector3T_s0048_4e40& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s0048_4e40 {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T_s0048_4e40 xAxis, yAxis, zAxis;
};
struct cSPMatrix3_s0048_4e40 : Matrix33T_s0048_4e40 {
    static const cSPMatrix3_s0048_4e40 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3_s0048_4e40 : Vector3T_s0048_4e40 {
    cSPVector3_s0048_4e40() {}
    cSPVector3_s0048_4e40(const Vector3T_s0048_4e40& v) : Vector3T_s0048_4e40(v) {}
    cSPVector3_s0048_4e40& operator=(const Vector3T_s0048_4e40& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s0048_4e40 operator*(const Vector3T_s0048_4e40& v, const Matrix33T_s0048_4e40& m);   // @ 0x41daf0
Vector3T_s0048_4e40 operator-(const Vector3T_s0048_4e40& v);                       // @ 0x422020
Vector3T_s0048_4e40 operator+(const Vector3T_s0048_4e40& a, const Vector3T_s0048_4e40& b);    // @ 0x41dc10
Vector3T_s0048_4e40& operator+=(Vector3T_s0048_4e40& a, const Vector3T_s0048_4e40& b);        // @ 0x41ddb0
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
    void PreRotate(const Vector3T_s0048_4e40& axis, float angle);       // @ 0x6baba0
};
template<class T> struct AutoRefCount_s0048_4e40 {
    T* mpObject;
    AutoRefCount_s0048_4e40(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s0048_4e40(const AutoRefCount_s0048_4e40& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
namespace SP {
struct cMWObject_s0048_4e40 {
    class cIModelWorld_s0048_4e40* mWorld;
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
class cIModelWorld_s0048_4e40 { public:
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
class cSPEditorModel_s0048_4e40 { public:
    float GetScale();                                                                       // @ 0x4adaa0
};
}
namespace SP {
class cSPEditorBlock_s0048_4e40 { public:
    char pad0[0x18];
    AutoRefCount_s0048_4e40<cIModelWorld_s0048_4e40> mModelWorld;     // +0x18
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
template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];   // retail: 0x14 bytes
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};
}
namespace SP {
class cSPEditorLimbJoint_s0048_4e40 { public:
    cSPEditorBlock_s0048_4e40* mJointBlock;                // +0x00
    cSPEditorLimbJoint_s0048_4e40* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint_s0048_4e40*> mLowerJoints;   // +0x08
    cSPVector3_s0048_4e40 mTargetPosition;                 // +0x1c
    cSPVector3_s0048_4e40 mOriginalPosition;               // +0x28

    cSPEditorLimbJoint_s0048_4e40* GetUpperUpperJoint();
    void SetTargetPosition(cSPVector3_s0048_4e40 pos);
    void Move(cSPVector3_s0048_4e40 delta, bool relative);
    void MoveLowerJoints(cSPVector3_s0048_4e40 delta);
    void Translate(cSPVector3_s0048_4e40 delta);
};
}
// ---- items of slice s00484e40 end

// ---- items of slice s00486910 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0048_6910 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s0048_6910() {}
    Vector3T_s0048_6910(const Vector3T_s0048_6910& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s0048_6910 : Vector3T_s0048_6910 {
    cSPVector3_s0048_6910() {}
    cSPVector3_s0048_6910(const Vector3T_s0048_6910& v) : Vector3T_s0048_6910(v) {}
    cSPVector3_s0048_6910& operator=(const Vector3T_s0048_6910& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s0048_6910 operator-(const Vector3T_s0048_6910& a, const Vector3T_s0048_6910& b);    // @ 0x41db10
Vector3T_s0048_6910 operator+(const Vector3T_s0048_6910& a, const Vector3T_s0048_6910& b);    // @ 0x41dc10
Vector3T_s0048_6910 operator*(const Vector3T_s0048_6910& v, const float& s);       // @ 0x41dca0
bool operator!=(const Vector3T_s0048_6910& a, const Vector3T_s0048_6910& b);       // @ 0x41dd30
inline float Abs(float x) { float r = (float)fabs(x); return r; }
inline float SignOf(float v)
{
    float s;
    if (v < -0.001f) s = -1.0f;
    else if (v > 0.001f) s = 1.0f;
    else s = 0.0f;
    return s;
}
template<class T> struct vector_s0048_6910 {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];   // +0x14
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
    void push_back(const T& v);                  // @ 0x454860
    void eraseOne(T* it);                        // @ 0x48c720
};
template<int N> struct bitset_s0048_6910 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) return (mWord[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};
namespace SP {
class cSPEditorBlock_s0048_6910;
}
namespace SP {
class cSPEditorLimbJoint_s0048_6910;
}
namespace SP {
class cSPEditorModel_s0048_6910 { public:
    char pad0[0x38];
    float mScale;                               // +0x38
    float mX3c;                                 // +0x3c
    float mX40;                                 // +0x40
    float mX44;                                 // +0x44
    float GetScale();                           // @ 0x4adaa0
    float F_7f9410();                           // @ 0x7f9410
    float F_4adb00();                           // @ 0x4adb00
    float F_4adb40();                           // @ 0x4adb40
    cSPEditorBlock_s0048_6910* FindNearestFlag7Block(cSPVector3_s0048_6910 pos);          // @ 0x4ac480
};
}
namespace SP {
class cSPEditorBlock_s0048_6910 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x28 - 4];
    cSPEditorModel_s0048_6910* mEditorModel;               // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3_s0048_6910 mPosition;                       // +0x48
    char pad2[0x33c - 0x54];
    cSPEditorBlock_s0048_6910* mLink33c;                   // +0x33c
    char pad3[0xdc8 - 0x340];
    bitset_s0048_6910<60> mFlags;                          // +0xdc8

    bool IsLimbPart();                                                   // @ 0x435c80
    void SetFlag(int index, bool value);                                 // @ 0x435a10
    float GetRadius();                                                   // @ 0x43f250
    void RefreshLinks(cSPEditorBlock_s0048_6910* e);                                // @ 0x438700
    void RefreshLinked(cSPEditorBlock_s0048_6910* e);                               // @ 0x438a40
    void F_43f5b0(cSPVector3_s0048_6910* out, cSPVector3_s0048_6910 pos, cSPEditorLimbJoint_s0048_6910* invalid); // @ 0x43f5b0
};
}
namespace SP {
class cSPEditorLimbJoint_s0048_6910 { public:
    cSPEditorBlock_s0048_6910* mJointBlock;                // +0x00
    cSPEditorLimbJoint_s0048_6910* mUpperJoint;            // +0x04
    vector_s0048_6910<cSPEditorLimbJoint_s0048_6910*> mLowerJoints;   // +0x08
    cSPVector3_s0048_6910 mTargetPosition;                 // +0x1c
    cSPVector3_s0048_6910 mOriginalPosition;               // +0x28
    cSPVector3_s0048_6910 mPositionAtCreation;             // +0x34
    cSPVector3_s0048_6910 mTargetOffset;                   // +0x40
    cSPVector3_s0048_6910 mOriginalOffset;                 // +0x4c
    cSPVector3_s0048_6910 mCreationOffset;                 // +0x58

    bool UpdateLength(bool b);                                          // @ 0x486910
    bool IsValid();                                                     // @ 0x486d40
    bool Fix(cSPEditorLimbJoint_s0048_6910* invalid);                              // @ 0x486e70
    void F_486f50(cSPVector3_s0048_6910 pos);                                      // @ 0x486f50
    void AddLowerJoint(cSPEditorLimbJoint_s0048_6910* child);                      // @ 0x487040
    void RemoveLowerJoint(cSPEditorLimbJoint_s0048_6910* child);                   // @ 0x487090
    void F_487140(cSPEditorLimbJoint_s0048_6910* child);                           // @ 0x487140
    void F_487290(cSPEditorLimbJoint_s0048_6910* child);                           // @ 0x487290
    float GetLength();                                                  // @ 0x4873d0
    int Sign(bool recurse);                                             // @ 0x4874c0
    int SignFromBlock(bool recurse);                                    // @ 0x4876b0
    void SetTargetPosition(cSPVector3_s0048_6910 pos);                             // @ 0x485930
    void Move(cSPVector3_s0048_6910 delta, bool relative);                         // @ 0x485960
    void Translate(cSPVector3_s0048_6910 delta);                                   // @ 0x485af0
    void F_485b90(cSPVector3_s0048_6910* out);                                     // @ 0x485b90
};
}
// ---- items of slice s00486910 end

// ---- items of slice s00487850 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_015d5f68;                                   // @ 0x15d5f68
extern float DAT_015d5f6c;                                   // @ 0x15d5f6c
extern float DAT_015d5f70;                                   // @ 0x15d5f70
struct Vector3T_s0048_7850 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s0048_7850() {}
    Vector3T_s0048_7850(const Vector3T_s0048_7850& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s0048_7850 {
    Vector3T_s0048_7850 xAxis, yAxis, zAxis;
};
struct cSPVector3_s0048_7850 : Vector3T_s0048_7850 {
    cSPVector3_s0048_7850() {}
    cSPVector3_s0048_7850(const Vector3T_s0048_7850& v) : Vector3T_s0048_7850(v) {}
    cSPVector3_s0048_7850& operator=(const Vector3T_s0048_7850& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s0048_7850 operator-(const Vector3T_s0048_7850& v);                        // @ 0x422020 (negate)
Vector3T_s0048_7850 operator-(const Vector3T_s0048_7850& a, const Vector3T_s0048_7850& b);    // @ 0x41db10
Vector3T_s0048_7850 operator+(const Vector3T_s0048_7850& a, const Vector3T_s0048_7850& b);    // @ 0x41dc10
Vector3T_s0048_7850 operator*(const Vector3T_s0048_7850& v, const float& s);       // @ 0x41dca0
extern cSPVector3_s0048_7850 DAT_015d5db8;                              // @ 0x15d5db8
template<class T> struct vector_s0048_7850 {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
};
template<int N> struct bitset_s0048_7850 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) return (mWord[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};
namespace SP {
class cSPEditorBlock_s0048_7850;
}
namespace SP {
class cSPEditorLimbJoint_s0048_7850;
}
namespace SP {
class cSPEditorBlock_s0048_7850 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x28 - 4];
    void* mEditorModel;                         // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3_s0048_7850 mPosition;                       // +0x48
    char pad2[0x60 - 0x54];
    Matrix33T_s0048_7850 mOrientation;                     // +0x60
    char pad3[0x33c - 0x84];
    cSPEditorBlock_s0048_7850* mLink33c;                   // +0x33c
    char pad4[0xdc8 - 0x340];
    bitset_s0048_7850<60> mFlags;                          // +0xdc8
    bool F_44c030();                            // @ 0x44c030
    cSPVector3_s0048_7850 F_43e080();                      // @ 0x43e080
};
}
namespace SP {
class cSPEditorLimbJoint_s0048_7850 { public:
    cSPEditorBlock_s0048_7850* mJointBlock;                // +0x00
    cSPEditorLimbJoint_s0048_7850* mUpperJoint;            // +0x04
    vector_s0048_7850<cSPEditorLimbJoint_s0048_7850*> mLowerJoints;   // +0x08
    cSPVector3_s0048_7850 mTargetPosition;                 // +0x1c
    cSPVector3_s0048_7850 mOriginalPosition;               // +0x28
    cSPVector3_s0048_7850 mPositionAtCreation;             // +0x34

    cSPEditorLimbJoint_s0048_7850* FindFirstLimbLowerJoint();      // @ 0x487850
    cSPVector3_s0048_7850 GetLowerDirection(int mode);             // @ 0x4878e0
    cSPVector3_s0048_7850 GetUpperDirection(int mode);             // @ 0x487e90
    cSPVector3_s0048_7850 GetUpVector(bool b);                     // @ 0x488100
    int Sign(bool recurse);                             // @ 0x4874c0 (slice 76)
};
}
// ---- items of slice s00487850 end

// ---- items of slice s00488600 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0048_8600 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s0048_8600() {}
    Vector3T_s0048_8600(const Vector3T_s0048_8600& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s0048_8600 {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T_s0048_8600 xAxis, yAxis, zAxis;
};
struct cSPMatrix3_s0048_8600 : Matrix33T_s0048_8600 {
    static const cSPMatrix3_s0048_8600 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3_s0048_8600 : Vector3T_s0048_8600 {
    cSPVector3_s0048_8600() {}
    cSPVector3_s0048_8600(const Vector3T_s0048_8600& v) : Vector3T_s0048_8600(v) {}
    cSPVector3_s0048_8600& operator=(const Vector3T_s0048_8600& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s0048_8600 operator*(const Vector3T_s0048_8600& v, const Matrix33T_s0048_8600& m);   // @ 0x41daf0
Vector3T_s0048_8600 operator-(const Vector3T_s0048_8600& v);                       // @ 0x422020
Vector3T_s0048_8600 operator+(const Vector3T_s0048_8600& a, const Vector3T_s0048_8600& b);    // @ 0x41dc10
Vector3T_s0048_8600& operator+=(Vector3T_s0048_8600& a, const Vector3T_s0048_8600& b);        // @ 0x41ddb0
template<class T> struct AutoRefCount_s0048_8600 {
    T* mpObject;
    ~AutoRefCount_s0048_8600() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct CtorSlots { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount_s0048_8600;
template<class T> struct CtorSlots<AutoRefCount_s0048_8600<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };
template<class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots<T>::Reserve(); }
    ~VectorBase();                                           // @ 0x425990 (shared)
};
template<class T> struct vector_s0048_8600 : VectorBase<T> {
    vector_s0048_8600() {}
    ~vector_s0048_8600() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};
template<int N> struct bitset_s0048_8600 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
namespace SP {
class cSPEditorBlock_s0048_8600 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3_s0048_8600 mPosition;                       // +0x48
    char pad1[0x33c - 0x54];
    AutoRefCount_s0048_8600<cSPEditorBlock_s0048_8600> mParentBlock;  // +0x33c
    char pad2[0xdc8 - 0x340];
    bitset_s0048_8600<60> mFlags;                          // +0xdc8

    const cSPVector3_s0048_8600& GetPosition() const { return mPosition; }
    cSPEditorBlock_s0048_8600* GetParent() const { return mParentBlock; }
    bool IsLimbPart();                                       // @ 0x435c80
    int CalculateSymmetrySign();                             // @ 0x44f240
    void SetSymmetrySign(int sign);                          // @ 0x44e980
    int GetSymmetryCount();                                  // @ 0x44f220
};
}
namespace SP {
Vector3T_s0048_8600 operator-(const Vector3T_s0048_8600& a, const Vector3T_s0048_8600& b);                                 // @ 0x41db10
}
namespace SP {
class cSPEditorLimbStructure_s0048_8600;
}
namespace SP {
void BuildPileList(cSPEditorBlock_s0048_8600* block, cSPEditorLimbStructure_s0048_8600* limb, int depth);       // @ 0x48c790
}
namespace SP {
class cSPEditorLimbJoint_s0048_8600 { public:
    cSPEditorBlock_s0048_8600* mJointBlock;                // +0x00
    cSPEditorLimbJoint_s0048_8600* mUpperJoint;            // +0x04
    vector_s0048_8600<cSPEditorLimbJoint_s0048_8600*> mLowerJoints;   // +0x08
    cSPVector3_s0048_8600 mTargetPosition;                 // +0x1c
    cSPVector3_s0048_8600 mOriginalPosition;               // +0x28
    cSPVector3_s0048_8600 mPositionAtCreation;             // +0x34
    int mJointType;                             // +0x40
    void* mSkin;                                // +0x44

    cSPMatrix3_s0048_8600 GetOrientation(int mode);
    cSPVector3_s0048_8600 GetLowerDirection(int i);                     // @ 0x4878e0
    cSPVector3_s0048_8600 GetUpperDirection(int i);                     // @ 0x487e90
    cSPVector3_s0048_8600 GetUpVector(bool b);                          // @ 0x488100
    cSPEditorLimbJoint_s0048_8600* FindInvalidJoint(bool b);            // @ 0x4874c0
};
}
namespace SP {
class cSPEditorLimbStructure_s0048_8600 { public:
    vector_s0048_8600<AutoRefCount_s0048_8600<cSPEditorBlock_s0048_8600> > mPileList;    // +0x00
    cSPEditorBlock_s0048_8600* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint_s0048_8600* mBaseJoint;             // +0x18
    cSPEditorBlock_s0048_8600* mLastBone;                  // +0x1c
    cSPEditorBlock_s0048_8600* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector_s0048_8600<cSPEditorLimbJoint_s0048_8600*> mFeet;          // +0x2c
    vector_s0048_8600<cSPEditorLimbJoint_s0048_8600*> mHands;         // +0x40

    cSPEditorLimbStructure_s0048_8600();
    ~cSPEditorLimbStructure_s0048_8600();
    void Clear();
    void UpdateSymmetry();
    cSPEditorLimbJoint_s0048_8600* FindInvalidJoint();
    void DeleteJoint(cSPEditorLimbJoint_s0048_8600* joint);
    void UpdateTargetPositions(bool relative);
    void UpdateTargetPositions(cSPEditorLimbJoint_s0048_8600* joint, bool relative);
    void MoveToBlock(cSPEditorBlock_s0048_8600* block);
    void Translate(cSPEditorLimbJoint_s0048_8600* joint, cSPVector3_s0048_8600 delta);
    void RelocateTargets(cSPEditorLimbJoint_s0048_8600* joint, cSPEditorLimbJoint_s0048_8600* anchor);
    void Refresh(bool relative);
    void Init(cSPEditorBlock_s0048_8600* block, bool isBase, bool b);
    void MirrorOriginal(cSPEditorLimbJoint_s0048_8600* joint, float f);
    void MirrorCreation(cSPEditorLimbJoint_s0048_8600* joint, float f);
    void CollectBlocks(cSPEditorBlock_s0048_8600* block);               // @ 0x489900
    void SortPileList();                                     // @ 0x489bc0
    cSPEditorLimbJoint_s0048_8600* FindJoint(cSPEditorBlock_s0048_8600* block);    // @ 0x48b2c0
    cSPEditorLimbJoint_s0048_8600* BuildJoints(cSPEditorBlock_s0048_8600* block, cSPEditorLimbJoint_s0048_8600* upper, bool b); // @ 0x48c0f0
};
}
// ---- items of slice s00488600 end

// ---- items of slice s00489530 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0048_9530 {
    float x, y, z;
    Vector3T_s0048_9530() {}
    Vector3T_s0048_9530(const Vector3T_s0048_9530& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s0048_9530 { Vector3T_s0048_9530 xAxis, yAxis, zAxis; };
struct RwMat33 { Vector3T_s0048_9530 m[3];
    RwMat33() {}
    RwMat33(const RwMat33& o);                                // @ 0x41cb40 (out-of-line copy ctor)
    Vector3T_s0048_9530& operator[](int i) { return m[i]; }
};
struct cSPVector3_s0048_9530 : Vector3T_s0048_9530 {
    cSPVector3_s0048_9530() {}
    cSPVector3_s0048_9530(const Vector3T_s0048_9530& v) : Vector3T_s0048_9530(v) {}
    cSPVector3_s0048_9530& operator=(const Vector3T_s0048_9530& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s0048_9530 operator-(const Vector3T_s0048_9530& a, const Vector3T_s0048_9530& b);    // @ 0x41db10
Vector3T_s0048_9530 operator+(const Vector3T_s0048_9530& a, const Vector3T_s0048_9530& b);    // @ 0x41dc10
Vector3T_s0048_9530 operator-(const Vector3T_s0048_9530& v);                       // @ 0x422020
float VectorLength(const Vector3T_s0048_9530& v);                       // @ 0x40ae50
template<class T> struct vector_s0048_9530 {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
    void erase(T* first, T* last);               // @ 0x454280 (erase(first,last))
};
template<int N> struct bitset_s0048_9530 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) return (mWord[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};
namespace SP {
class cSPEditorBlock_s0048_9530;
}
namespace SP {
class cSPEditorLimbJoint_s0048_9530;
}
namespace SP {
class cSPEditorBlock_s0048_9530 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x28 - 4];
    void* mEditorModel;                         // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3_s0048_9530 mPosition;                       // +0x48
    char pad2[0x60 - 0x54];
    Matrix33T_s0048_9530 mOrientation;                     // +0x60
    char pad3[0xa8 - 0x84];
    RwMat33 mTorsoOrientation;                  // +0xa8
    char pad3b[0x33c - 0xcc];
    cSPEditorBlock_s0048_9530* mLink33c;                   // +0x33c
    char pad4[0x3f0 - 0x340];
    struct LinkData { char pad[0xc]; cSPVector3_s0048_9530 mPos; cSPVector3_s0048_9530& GetPos() { return mPos; } }* mLinkData;  // +0x3f0
    char pad4b[0xc0c - 0x3f4];
    vector_s0048_9530<void*> mVec0c0c;                     // +0xc0c
    char pad5[0xdc8 - 0xc20];
    bitset_s0048_9530<60> mFlags;                          // +0xdc8

    cSPVector3_s0048_9530& GetPosition() { return mPosition; }
    RwMat33& GetTorsoOrientation() { return mTorsoOrientation; }
    cSPEditorBlock_s0048_9530* GetLink() { return mLink33c; }
    LinkData* GetLinkData() { return mLinkData; }
    bool IsLimbPart();                          // @ 0x435c80
    int CalculateSymmetrySign();                // @ 0x44f240
};
}
namespace SP {
class cSPEditorLimbJoint_s0048_9530 { public:
    cSPEditorBlock_s0048_9530* mJointBlock;                // +0x00
    cSPEditorLimbJoint_s0048_9530* mUpperJoint;            // +0x04
    vector_s0048_9530<cSPEditorLimbJoint_s0048_9530*> mLowerJoints;   // +0x08
    cSPVector3_s0048_9530 mTargetPosition;                 // +0x1c
    cSPVector3_s0048_9530 mOriginalPosition;               // +0x28
    cSPVector3_s0048_9530 mPositionAtCreation;             // +0x34

    int Sign(bool recurse);                     // @ 0x4874c0
    RwMat33 GetBasis(int mode);                 // @ 0x488600
    cSPEditorLimbJoint_s0048_9530* FindFirstLimbLowerJoint();  // @ 0x487850
};
}
namespace SP {
class cSPEditorLimbStructure_s0048_9530 { public:
    vector_s0048_9530<cSPEditorBlock_s0048_9530*> mPileList;          // +0x00
    cSPEditorBlock_s0048_9530* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint_s0048_9530* mBaseJoint;             // +0x18
    cSPEditorBlock_s0048_9530* mLastBone;                  // +0x1c
    cSPEditorBlock_s0048_9530* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector_s0048_9530<cSPEditorLimbJoint_s0048_9530*> mFeet;          // +0x2c
    vector_s0048_9530<cSPEditorLimbJoint_s0048_9530*> mHands;         // +0x40

    void MirrorTargets(cSPEditorLimbJoint_s0048_9530* joint, vector_s0048_9530<cSPEditorLimbJoint_s0048_9530*>* list);  // @ 0x489530
    void MirrorTargetsOffset(cSPEditorLimbJoint_s0048_9530* joint, float f);                      // @ 0x489640
    void RefreshTargets(vector_s0048_9530<cSPEditorLimbJoint_s0048_9530*>* list, bool b);                    // @ 0x489710
    void RefreshBlockTargets(cSPEditorBlock_s0048_9530* block, bool b);                           // @ 0x4897b0
    void Rebuild(cSPEditorBlock_s0048_9530* block);                                               // @ 0x4898a0
    void CollectBlocks(cSPEditorBlock_s0048_9530* block);                                         // @ 0x489900
    void FixAllJoints();                                                               // @ 0x489ae0
    void UpdateLimbScale();                                                            // @ 0x489bc0
    void FinalizeJoints(cSPEditorLimbJoint_s0048_9530* joint, bool b);                            // @ 0x489c60
    void RepinJoint(cSPEditorLimbJoint_s0048_9530* joint);                                        // @ 0x489cf0

    // out-of-line members of this class (original callees, thiscall)
    cSPVector3_s0048_9530 GetLimbOriginalPosition();                                              // @ 0x48c610
    void Refresh(bool relative);                                                       // @ 0x4890e0
    void MirrorOriginal(cSPEditorLimbJoint_s0048_9530* joint, float f);                           // @ 0x4893f0
    void MirrorCreation(cSPEditorLimbJoint_s0048_9530* joint, float f);                           // @ 0x489490
    void UpdateSymmetry();                                                             // @ 0x488a50
    void FUN_0048bdd0();                                                               // @ 0x48bdd0
    void FUN_0048bf70(cSPEditorLimbJoint_s0048_9530* joint, int i);                               // @ 0x48bf70
    void FUN_0048bae0(int i);                                                          // @ 0x48bae0
    void SetUIStateBlock(void* arg);                                                   // @ 0x48a560
};
}
namespace SP {
void BuildPileList(cSPEditorBlock_s0048_9530* block, cSPEditorLimbStructure_s0048_9530* limb, int depth); // @ 0x48c790
}
// ---- items of slice s00489530 end

// ---- items of slice s0048a4e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix33T_s0048_a4e0 {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPVector3_s0048_a4e0 : Vector3T {
    cSPVector3_s0048_a4e0() {}
    cSPVector3_s0048_a4e0(const cSPVector3_s0048_a4e0& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0048_a4e0(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0048_a4e0& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T operator*(const Vector3T& v, const Matrix33T_s0048_a4e0& m);   // @ 0x41daf0
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
template<class T> struct AutoRefCount_s0048_a4e0 {
    T* mpObject;
    ~AutoRefCount_s0048_a4e0() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct CtorSlots_s0048_a4e0 { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount_s0048_a4e0;
template<class T> struct CtorSlots_s0048_a4e0<AutoRefCount_s0048_a4e0<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };
template<class T> struct VectorBase_s0048_a4e0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase_s0048_a4e0() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots_s0048_a4e0<T>::Reserve(); }
    ~VectorBase_s0048_a4e0();                                           // @ 0x425990 (shared)
};
template<class T> struct vector_s0048_a4e0 : VectorBase_s0048_a4e0<T> {
    vector_s0048_a4e0() {}
    ~vector_s0048_a4e0() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots_s0048_a4e0<T>::ReserveClear(); }
    void push_back(const T& value);                          // @ 0x454860
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};
namespace SP {
class cSPEditorBlock_s0048_a4e0 { public:
    virtual void _v0();
    virtual int Release();
    char pad0[0x33c - 4];
    AutoRefCount_s0048_a4e0<cSPEditorBlock_s0048_a4e0> mParentBlock;  // +0x33c
    vector_s0048_a4e0<AutoRefCount_s0048_a4e0<cSPEditorBlock_s0048_a4e0> > mSymmetricBlocks;   // +0x340
    char pad1[0x3e0 - 0x354];
    int mUIState;                               // +0x3e0

    int GetUIState() const { return mUIState; }
    bool IsLimbPart();                                       // @ 0x435c80
    int CalculateSymmetrySign();                             // @ 0x44f240
    void SetModelBasedOnSymmetrySign(int sign, bool a, bool b, bool c, int d);   // @ 0x439110
    void UpdateLimbModel();                                  // @ 0x449ce0
};
}
namespace SP {
Vector3T operator-(const Vector3T& a, const Vector3T& b);                 // @ 0x41db10
}
namespace SP {
Vector3T operator*(const float& s, const Vector3T& v);                    // @ 0x41de40
}
namespace SP {
Vector3T operator*(const Vector3T& v, const float& s);                    // @ 0x41dca0
}
namespace SP {
class cSPEditorLimbJoint_s0048_a4e0 { public:
    cSPEditorBlock_s0048_a4e0* mJointBlock;                // +0x00
    cSPEditorLimbJoint_s0048_a4e0* mUpperJoint;            // +0x04
    vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*> mLowerJoints;   // +0x08
    cSPVector3_s0048_a4e0 mTargetPosition;                 // +0x1c
    cSPVector3_s0048_a4e0 mOriginalPosition;               // +0x28
    cSPVector3_s0048_a4e0 mPositionAtCreation;             // +0x34
    int mJointType;                             // +0x40
    void* mSkin;                                // +0x44

    cSPEditorLimbJoint_s0048_a4e0* FindInvalidJoint(bool b);            // @ 0x4874c0
    bool UpdateLength(bool b);                               // @ 0x486910
    bool IsValid();                                          // @ 0x486d40
    bool Fix(cSPEditorLimbJoint_s0048_a4e0* invalid);                   // @ 0x486e70
    float GetLength();                                       // @ 0x4873d0
    void MoveTarget(Vector3T pos);                           // @ 0x486f50
};
}
namespace SP {
class cSPEditorLimbStructure_s0048_a4e0 { public:
    vector_s0048_a4e0<AutoRefCount_s0048_a4e0<cSPEditorBlock_s0048_a4e0> > mPileList;    // +0x00
    cSPEditorBlock_s0048_a4e0* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint_s0048_a4e0* mBaseJoint;             // +0x18
    cSPEditorBlock_s0048_a4e0* mLastBone;                  // +0x1c
    cSPEditorBlock_s0048_a4e0* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*> mFeet;          // +0x2c
    vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*> mHands;         // +0x40

    void UpdateLimbModels(cSPEditorLimbJoint_s0048_a4e0* joint);
    void SetUIState(int state);
    void SetUIState(cSPEditorLimbJoint_s0048_a4e0* joint, int state);
    void SetJointTarget(cSPEditorLimbJoint_s0048_a4e0* joint, cSPVector3_s0048_a4e0 pos);
    void AdjustJoint(cSPEditorLimbJoint_s0048_a4e0* joint, cSPEditorLimbJoint_s0048_a4e0* anchor, cSPEditorLimbJoint_s0048_a4e0* skip, bool flattenX);
    void UpdateSymmetryModels(cSPEditorLimbJoint_s0048_a4e0* joint, bool a, bool b);
    void UpdateSymmetryModels(bool a, bool b);
    bool AreJointsValid(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* joints);
    bool FixJoints(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* joints);
    bool FixJoint(cSPEditorLimbJoint_s0048_a4e0* joint);
    bool UpdateLengths(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* joints);
    void FixZeroLengthJoints(cSPEditorLimbJoint_s0048_a4e0* joint);
    void CollectLimbJoints(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* out);
    void CollectLimbJoints(cSPEditorLimbJoint_s0048_a4e0* joint, vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* out);
    cSPEditorLimbJoint_s0048_a4e0* FindJoint(cSPEditorBlock_s0048_a4e0* block);
    cSPEditorLimbJoint_s0048_a4e0* FindJoint(cSPEditorBlock_s0048_a4e0* block, cSPEditorLimbJoint_s0048_a4e0* joint);
    cSPEditorLimbJoint_s0048_a4e0* FindInvalidJoint();                  // @ 0x488b30
};
}
// ---- items of slice s0048a4e0 end

// @ 0x00482f90
RotationBall* RotationBall::Construct()
{
    this->BaseConstruct();
    this->vptr = &g_ballVtbl0;
    this->vptr2 = &g_ballVtbl1;
    Vector3& o = this->mOffset;
    o.x = g_offset.x;
    o.y = g_offset.y;
    o.z = g_offset.z;
    this->mExists = false;
    return this;
}

// @ 0x00483040
void RotationBall::Destroy()
{
    this->vptr = &g_ballVtbl0;
    this->vptr2 = &g_ballVtbl1;
    this->BallCleanup();
    this->BaseDestroy();
}

// @ 0x00483070
void* RotationBall::AsInterface(uint32_t id)
{
    switch (id) {
    case 0xee3f516e: return this;
    case 0x050a1fe5: return this;
    case 0x050a510e: return this;
    }
    return 0;
}

// @ 0x004830c0
void RotationBall::UpdateOffset()
{
    if (this->mModel) {
        char local[12];
        void* r = ((void*(__thiscall*)(RotationBall*, void*))this->vptr[9])(this, local);
        *(Vector3*)((char*)(cMWModel*)this->mModel + 0xc) = *(Vector3*)r;
        *(uint16_t*)((char*)(cMWModel*)this->mModel + 8) |= 4;
        ++*(uint16_t*)((char*)(cMWModel*)this->mModel + 0xa);
    }
}

// @ 0x00483490
Vector3* RotationBall::GetTuningOffset(Vector3* out)
{
    char* t = (char*)EditorTuning();
    *(Vector3*)out = *(Vector3*)(t + 0x9c);
    return out;
}

// @ 0x004834d0
cSPVector3_s0048_34d0 RotationBall_s0048_34d0::Resume()
{
    cMWModel_s0048_34d0* model = this->mModel;
    if (model == 0 || this->mBlock == 0) {
        return g_zeroVector;
    }
    cSPBoundingBox_s0048_34d0 box = this->mBlock->GetBBox(2, false, false);
    cSPTransform_s0048_34d0 t;
    t.SetRotation(g_ballRotation);
    t.SetTranslation(g_zeroVector);
    t.SetScale(1.0f);
    box.Transform(t);
    ScratchSlots<40>();
    float len = VectorLength(this->mOffset);
    cSPVector3_s0048_34d0 dir = this->mOffset / len;
    Vector3T zero(g_zeroVector);
    float hundred = 100.0f;
    cSPVector3_s0048_34d0 u = dir * hundred;
    float dist = len;
    float tval;
    if (SP::SegmentBoxIntersect(u, zero, box, &tval))
        dist = (1.0f - tval) * hundred;
    float off = (dist + this->mDistanceFromBoundingBox) * this->mBlock->mScale;
    cSPVector3_s0048_34d0 res = this->mBlock->mPosition + (dir * off) * this->mBlock->mOrientation;
    return res;
}

// @ 0x004837f0
void RotationBall_s0048_34d0::Update()
{
    cMWModel_s0048_34d0* model = this->mModel;
    if (model == 0)
        return;
    AnimMgr* mgr = GetSetting6();
    cIModelWorld_s0048_34d0* world = this->mBlock->mModelWorld;
    if (mgr == 0 || world == 0)
        return;
    cSPMatrix3_s0048_34d0 orient = this->mBlock->mOrientation;
    float scale = this->mBlock->mScale;
    cSPVector3_s0048_34d0 pos = this->mBlock->mPosition;
    cSPVector3_s0048_34d0 dir = Normalize(this->mOffset);
    cSPVector3_s0048_34d0 v = dir * orient;
    cSPMatrix3_s0048_34d0 buildOri;
    BuildOrientation(&buildOri, &v, &g_ballUp);
    cSPVector3_s0048_34d0 out = ((cSPVector3_s0048_34d0 (__thiscall*)(RotationBall_s0048_34d0*))this->vptr[0x24 / 4])(this);
    float k = 0.4f;
    cSPVector3_s0048_34d0 newPos = pos + (this->mOffset - dir * k) * scale * orient;
    this->mModel->mTransform.SetTranslation(newPos);
    this->mModel->mTransform.SetRotation(buildOri);
    PLAY_ANIM(mgr, this->mModel, 5, out.x, this->mAnimateInTime, 3);
    PLAY_ANIM(mgr, this->mModel, 6, out.y, this->mAnimateInTime, 3);
    PLAY_ANIM(mgr, this->mModel, 7, out.z, this->mAnimateInTime, 3);
    float alpha = ((float (__thiscall*)(RotationBall_s0048_34d0*, int))this->vptr[0x38 / 4])(this, 3);
    PLAY_ANIM(mgr, this->mModel, 4, alpha, this->mAnimateInTime, 1);
}

// @ 0x00483cc0
void SP::cSPEditorHandleRotationBall::SetScale(float s)
{
    if (this->mModel) {
        cSPTransform& x = this->mModel->mTransform;
        x.mScale = s;
        ++x.mModificationCount;
    }
}

// @ 0x00483d10
void RotationRing::Shutdown()
{
    this->BaseShutdown();
    *(uint8_t*)((char*)this + 0x5c) = 0;
}

// @ 0x00483d40
RotationRing* RotationRing::Construct()
{
    this->BaseConstruct();
    this->vptr = &g_ringVtbl0;
    this->vptr2 = &g_ringVtbl1;
    this->mUnk50 = 0;
    Vector3_s0048_34d0& a = this->mVec54;
    a.x = g_ringVecA.x;
    a.y = g_ringVecA.y;
    a.z = g_ringVecA.z;
    Vector3_s0048_34d0& b = this->mVec60;
    b.x = g_ringVecB.x;
    b.y = g_ringVecB.y;
    b.z = g_ringVecB.z;
    this->mUnk6c = 0x3bc16bcd;
    this->mUnk70 = 0xe864ba60;
    this->mUnk78 = g_zeroC;
    this->mUnk88 = g_negOne;
    this->mUnk8c = g_negOne;
    this->mUnk90 = 0;
    this->mUnk91 = 0;
    return this;
}

// @ 0x00485900
namespace SP {
cSPEditorLimbJoint_s0048_4e40* cSPEditorLimbJoint_s0048_4e40::GetUpperUpperJoint()
{
    if (mUpperJoint) return mUpperJoint->mUpperJoint;
    else return 0;
}
}  // namespace SP

// @ 0x00485930
namespace SP {
void cSPEditorLimbJoint_s0048_4e40::SetTargetPosition(cSPVector3_s0048_4e40 pos)
{
    mTargetPosition = pos;
}
}  // namespace SP

// @ 0x00485960
namespace SP {
void cSPEditorLimbJoint_s0048_4e40::Move(cSPVector3_s0048_4e40 delta, bool relative)
{
    if (relative) mTargetPosition += delta;
    else mTargetPosition = mOriginalPosition + delta;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Move(delta, relative);
}
}  // namespace SP

// @ 0x00485a60
namespace SP {
void cSPEditorLimbJoint_s0048_4e40::MoveLowerJoints(cSPVector3_s0048_4e40 delta)
{
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Move(delta, true);
}
}  // namespace SP

// @ 0x00485af0
namespace SP {
void cSPEditorLimbJoint_s0048_4e40::Translate(cSPVector3_s0048_4e40 delta)
{
    mOriginalPosition += delta;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Translate(delta);
}
}  // namespace SP

// @ 0x00486e70
namespace SP {
bool cSPEditorLimbJoint_s0048_6910::Fix(cSPEditorLimbJoint_s0048_6910* invalid)
{
    bool changed = false;
    if (invalid && mUpperJoint) {
        if (!mJointBlock->IsLimbPart()) {
            cSPVector3_s0048_6910 out;
            mJointBlock->F_43f5b0(&out, mTargetPosition, invalid);
            if (out != mTargetPosition) {
                SetTargetPosition(out);
                changed = true;
            }
        }
    }
    return changed;
}
}  // namespace SP

// @ 0x00486f50
namespace SP {
void cSPEditorLimbJoint_s0048_6910::F_486f50(cSPVector3_s0048_6910 pos)
{
    mTargetPosition = pos;
    cSPVector3_s0048_6910 delta = mTargetPosition - mOriginalPosition;
    for (int i = 0, n = mLowerJoints.size(); i < n; i++)
        mLowerJoints[i]->Move(delta, false);
}
}  // namespace SP

// @ 0x00487040
namespace SP {
void cSPEditorLimbJoint_s0048_6910::AddLowerJoint(cSPEditorLimbJoint_s0048_6910* child)
{
    if (child->mUpperJoint) child->mUpperJoint->RemoveLowerJoint(child);
    mLowerJoints.push_back(child);
    mJointBlock->RefreshLinks(child->mJointBlock);
    child->mUpperJoint = this;
    ScratchSlots<2>();
}
}  // namespace SP

// @ 0x00487090
namespace SP {
void cSPEditorLimbJoint_s0048_6910::RemoveLowerJoint(cSPEditorLimbJoint_s0048_6910* child)
{
    cSPEditorLimbJoint_s0048_6910** pEnd = mLowerJoints.end();
    cSPEditorLimbJoint_s0048_6910** it = mLowerJoints.begin();
    while (it != pEnd && *it != child) ++it;
    if (it != mLowerJoints.end()) {
        mLowerJoints.eraseOne(it);
        if (child->mJointBlock->mLink33c)
            child->mJointBlock->mLink33c->RefreshLinked(child->mJointBlock);
        child->mUpperJoint = 0;
    }
}
}  // namespace SP

// @ 0x00487140
namespace SP {
void cSPEditorLimbJoint_s0048_6910::F_487140(cSPEditorLimbJoint_s0048_6910* child)
{
    cSPEditorLimbJoint_s0048_6910** pEnd = mLowerJoints.end();
    cSPEditorLimbJoint_s0048_6910** it = mLowerJoints.begin();
    while (it != pEnd && *it != child) ++it;
    if (it != mLowerJoints.end()) {
        child->mTargetOffset = child->mTargetPosition - mTargetPosition;
        child->mOriginalOffset = child->mOriginalPosition - mOriginalPosition;
        child->mCreationOffset = child->mPositionAtCreation - mPositionAtCreation;
        mLowerJoints.eraseOne(it);
    }
}
}  // namespace SP

// @ 0x00487290
namespace SP {
void cSPEditorLimbJoint_s0048_6910::F_487290(cSPEditorLimbJoint_s0048_6910* child)
{
    AddLowerJoint(child);
    cSPVector3_s0048_6910 t1 = mTargetPosition + child->mTargetOffset;
    cSPVector3_s0048_6910 t2 = mOriginalPosition + child->mOriginalOffset;
    child->Move(t1 - child->mTargetPosition, true);
    child->Translate(t2 + child->mOriginalPosition);
}
}  // namespace SP

// @ 0x004873d0
namespace SP {
float cSPEditorLimbJoint_s0048_6910::GetLength()
{
    cSPEditorLimbJoint_s0048_6910* p = mUpperJoint;
    if (!p) p = this;
    float a = (float)p->Sign(false);
    float av = p->mTargetPosition[0];
    if (Abs(av) < 0.001f) a = 0.0f;
    float b = (float)this->Sign(false);
    float bv = mTargetPosition[0];
    if (Abs(bv) < 0.001f) b = 0.0f;
    if (a != b && a != 0.0f) b = a;
    return b;
}
}  // namespace SP

// @ 0x004874c0
namespace SP {
int cSPEditorLimbJoint_s0048_6910::Sign(bool recurse)
{
    float v = mTargetPosition[0];
    int sign = (int)SignOf(v);
    if (recurse && sign == 0 && !mLowerJoints.empty()) {
        cSPVector3_s0048_6910 d = mLowerJoints[0]->mTargetPosition - mTargetPosition;
        sign = (int)SignOf(d[0]);
        if (sign == 0) {
            for (int i = 0, n = mLowerJoints.size(); i < n; i++) {
                int r = mLowerJoints[i]->Sign(recurse);
                if (r != 0) { sign = r; break; }
            }
        }
    }
    return sign;
}
}  // namespace SP

// @ 0x004876b0
namespace SP {
int cSPEditorLimbJoint_s0048_6910::SignFromBlock(bool recurse)
{
    float v = mJointBlock->mPosition[0];
    int sign = (int)SignOf(v);
    if (recurse && sign == 0 && !mLowerJoints.empty()) {
        cSPVector3_s0048_6910 d = mLowerJoints[0]->mJointBlock->mPosition - mJointBlock->mPosition;
        sign = (int)SignOf(d[0]);
    }
    return sign;
}
}  // namespace SP

// @ 0x00487850
namespace SP {
cSPEditorLimbJoint_s0048_7850* cSPEditorLimbJoint_s0048_7850::FindFirstLimbLowerJoint()
{
    if (!mLowerJoints.empty()) {
        for (int i = 0, n = mLowerJoints.size(); i < n; i++) {
            if (mLowerJoints[i]->mJointBlock->F_44c030())
                return mLowerJoints[i];
        }
    }
    return 0;
}
}  // namespace SP

// @ 0x004878e0
namespace SP {
cSPVector3_s0048_7850 cSPEditorLimbJoint_s0048_7850::GetLowerDirection(int mode)
{
    if (mLowerJoints.empty()) {
        if (mJointBlock->mFlags.test(0xb))
            return mJointBlock->mPosition + mJointBlock->F_43e080();
        if (mode == 1) return mOriginalPosition + DAT_015d5db8 * 0.1f;
        if (mode == 3) return mPositionAtCreation + DAT_015d5db8 * 0.1f;
        if (mode == 2) return mJointBlock->mPosition + DAT_015d5db8 * 0.1f;
        if (mode == 0) return mTargetPosition + DAT_015d5db8 * 0.1f;
    } else {
        cSPEditorLimbJoint_s0048_7850* p = FindFirstLimbLowerJoint();
        if (p) {
            if (mode == 1) return p->mOriginalPosition;
            if (mode == 3) return p->mPositionAtCreation;
            if (mode == 2) return p->mJointBlock->mPosition;
            if (mode == 0) return p->mTargetPosition;
        }
    }
    if (mode == 1) return mOriginalPosition;
    if (mode == 3) return mPositionAtCreation;
    if (mode == 2) return mJointBlock->mPosition;
    if (mode == 0) return mTargetPosition;
    cSPVector3_s0048_7850 d;
    d.x = DAT_015d5f68; d.y = DAT_015d5f6c; d.z = DAT_015d5f70;
    return d;
}
}  // namespace SP

// @ 0x00487e90
namespace SP {
cSPVector3_s0048_7850 cSPEditorLimbJoint_s0048_7850::GetUpperDirection(int mode)
{
    if (mUpperJoint == 0) {
        if (mJointBlock->mLink33c == 0) return mJointBlock->mPosition;
        else return mJointBlock->mLink33c->mPosition;
    }
    if (mode == 1) return mUpperJoint->mOriginalPosition;
    if (mode == 3) return mUpperJoint->mPositionAtCreation;
    if (mode == 0) return mUpperJoint->mTargetPosition;
    if (mode == 2) {
        if (mUpperJoint->mJointBlock->mFlags.test(0x1f))
            return mUpperJoint->mJointBlock->mPosition;
        else return mJointBlock->mPosition;
    }
    cSPVector3_s0048_7850 d;
    d.x = DAT_015d5f68; d.y = DAT_015d5f6c; d.z = DAT_015d5f70;
    return d;
}
}  // namespace SP

// @ 0x00488a50
namespace SP {
void cSPEditorLimbStructure_s0048_8600::UpdateSymmetry()
{
    BuildPileList(mBaseBlock, this, 0);
    mBaseBlock->SetSymmetrySign(mBaseBlock->CalculateSymmetrySign());
    for (int i = 0, n = mPileList.size(); i < n; i++)
        mPileList[i]->SetSymmetrySign(mPileList[i]->CalculateSymmetrySign());
    if (mEndBlock) mSymmetrySign = (float)mEndBlock->GetSymmetryCount();
    else mSymmetrySign = (float)mBaseBlock->GetSymmetryCount();
}
}  // namespace SP

// @ 0x00488b30
namespace SP {
cSPEditorLimbJoint_s0048_8600* cSPEditorLimbStructure_s0048_8600::FindInvalidJoint()
{
    cSPEditorLimbJoint_s0048_8600* result = mBaseJoint->FindInvalidJoint(true);
    if (!result) {
        for (int i = 0, n = mFeet.size(); i < n; i++) {
            cSPEditorLimbJoint_s0048_8600* j = mFeet[i]->FindInvalidJoint(true);
            if (j) { result = j; break; }
        }
        if (!result) {
            for (int i = 0, n = mHands.size(); i < n; i++) {
                cSPEditorLimbJoint_s0048_8600* j = mHands[i]->FindInvalidJoint(true);
                if (j) { result = j; break; }
            }
        }
    }
    return result;
}
}  // namespace SP

// @ 0x00488c30
namespace SP {
void cSPEditorLimbStructure_s0048_8600::DeleteJoint(cSPEditorLimbJoint_s0048_8600* joint)
{
    if (joint) {
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            DeleteJoint(joint->mLowerJoints.mpBegin[i]);
        delete joint;
    }
}
}  // namespace SP

// @ 0x00488d00
namespace SP {
void cSPEditorLimbStructure_s0048_8600::UpdateTargetPositions(bool relative)
{
    UpdateTargetPositions(mBaseJoint, relative);
}
}  // namespace SP

// @ 0x00488d30
namespace SP {
void cSPEditorLimbStructure_s0048_8600::UpdateTargetPositions(cSPEditorLimbJoint_s0048_8600* joint, bool relative)
{
    if (joint && joint->mJointBlock) {
        if (joint != mBaseJoint && relative) {
            cSPVector3_s0048_8600 d = joint->mOriginalPosition - mBaseJoint->mOriginalPosition;
            joint->mTargetPosition = mBaseJoint->mJointBlock->GetPosition() + d;
        } else {
            joint->mTargetPosition = joint->mJointBlock->mPosition;
        }
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            UpdateTargetPositions(joint->mLowerJoints.mpBegin[i], true);
    }
}
}  // namespace SP

// @ 0x00488e80
namespace SP {
void cSPEditorLimbStructure_s0048_8600::MoveToBlock(cSPEditorBlock_s0048_8600* block)
{
    cSPEditorLimbJoint_s0048_8600* joint = FindJoint(block);
    if (joint) {
        cSPVector3_s0048_8600 d = block->mPosition - joint->mOriginalPosition;
        Translate(joint, d);
    }
}
}  // namespace SP

// @ 0x00488f20
namespace SP {
void cSPEditorLimbStructure_s0048_8600::Translate(cSPEditorLimbJoint_s0048_8600* joint, cSPVector3_s0048_8600 delta)
{
    if (joint && joint->mJointBlock) {
        joint->mOriginalPosition += delta;
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            Translate(joint->mLowerJoints[i], delta);
    }
}
}  // namespace SP

// @ 0x00488fe0
namespace SP {
void cSPEditorLimbStructure_s0048_8600::RelocateTargets(cSPEditorLimbJoint_s0048_8600* joint, cSPEditorLimbJoint_s0048_8600* anchor)
{
    if (joint) {
        if (joint != anchor) {
            cSPVector3_s0048_8600 d = joint->mOriginalPosition - anchor->mOriginalPosition;
            joint->mTargetPosition = anchor->mTargetPosition + d;
        }
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            RelocateTargets(joint->mLowerJoints.mpBegin[i], anchor);
    }
}
}  // namespace SP

// @ 0x004890e0
namespace SP {
void cSPEditorLimbStructure_s0048_8600::Refresh(bool relative)
{
    UpdateTargetPositions(mBaseJoint, relative);
    cSPVector3_s0048_8600 d = mBaseJoint->mJointBlock->GetPosition() - mBaseJoint->mOriginalPosition;
    Translate(mBaseJoint, d);
    UpdateSymmetry();
}
}  // namespace SP

// @ 0x004898a0
namespace SP {
void cSPEditorLimbStructure_s0048_9530::Rebuild(cSPEditorBlock_s0048_9530* block)
{
    CollectBlocks(block);
    UpdateLimbScale();
    mPileList.erase(mPileList.begin(), mPileList.end());
    BuildPileList(mBaseBlock, this, 0);
    Refresh(true);
}
}  // namespace SP

// @ 0x00489bc0
namespace SP {
void cSPEditorLimbStructure_s0048_9530::UpdateLimbScale()
{
    cSPVector3_s0048_9530 p = GetLimbOriginalPosition();
    Vector3T_s0048_9530 basePos;
    basePos.x = mBaseBlock->mPosition.x;
    basePos.y = mBaseBlock->mPosition.y;
    basePos.z = mBaseBlock->mPosition.z;
    cSPVector3_s0048_9530 d = p - basePos;
    mLimbOriginalScale = VectorLength(d);
}
}  // namespace SP

// @ 0x00489c60
namespace SP {
void cSPEditorLimbStructure_s0048_9530::FinalizeJoints(cSPEditorLimbJoint_s0048_9530* joint, bool b)
{
    if (joint == 0) joint = mBaseJoint;
    if (b) FUN_0048bf70(joint, 0);
    FUN_0048bae0(0);
    RepinJoint(mBaseJoint);
    SetUIStateBlock(joint->mJointBlock);
    UpdateSymmetry();
}
}  // namespace SP

// @ 0x0048a4e0
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::UpdateLimbModels(cSPEditorLimbJoint_s0048_a4e0* joint)
{
    if (joint) {
        if (joint->mJointBlock) joint->mJointBlock->UpdateLimbModel();
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            UpdateLimbModels(joint->mLowerJoints.mpBegin[i]);
    }
}
}  // namespace SP

// @ 0x0048a560
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::SetUIState(int state)
{
    SetUIState(mBaseJoint, state);
}
}  // namespace SP

// @ 0x0048a650
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::SetJointTarget(cSPEditorLimbJoint_s0048_a4e0* joint, cSPVector3_s0048_a4e0 pos)
{
    if (joint) {
        joint->mTargetPosition = pos;
        AdjustJoint(joint, joint, 0, true);
    }
}
}  // namespace SP

// @ 0x0048ad20
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::UpdateSymmetryModels(cSPEditorLimbJoint_s0048_a4e0* joint, bool a, bool b)
{
    cSPEditorLimbJoint_s0048_a4e0* invalid = joint->FindInvalidJoint(true);
    if (!joint->mJointBlock->IsLimbPart()) {
        vector_s0048_a4e0<AutoRefCount_s0048_a4e0<cSPEditorBlock_s0048_a4e0> >& syms = joint->mJointBlock->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            int sign = syms[i]->CalculateSymmetrySign();
            syms[i]->SetModelBasedOnSymmetrySign(sign, b, a, true, 0);
        }
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        UpdateSymmetryModels(joint->mLowerJoints.mpBegin[i], false, false);
}
}  // namespace SP

// @ 0x0048ae30
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::UpdateSymmetryModels(bool a, bool b)
{
    UpdateSymmetryModels(mBaseJoint, a, b);
}
}  // namespace SP

// @ 0x0048ae60
namespace SP {
bool cSPEditorLimbStructure_s0048_a4e0::AreJointsValid(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* joints)
{
    bool changed = false;
    if (joints && !joints->empty()) {
        for (int i = 0, n = joints->size(); i < n; i++) {
            bool r = (*joints)[i]->IsValid();
            changed = r || changed;
        }
    }
    return changed;
}
}  // namespace SP

// @ 0x0048af00
namespace SP {
bool cSPEditorLimbStructure_s0048_a4e0::FixJoints(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* joints)
{
    bool changed = false;
    if (joints && !joints->empty()) {
        for (int i = 0, n = joints->size(); i < n; i++) {
            bool r = (*joints)[i]->Fix((*joints)[i]->FindInvalidJoint(false));
            changed = r || changed;
        }
    }
    return changed;
}
}  // namespace SP

// @ 0x0048afc0
namespace SP {
bool cSPEditorLimbStructure_s0048_a4e0::FixJoint(cSPEditorLimbJoint_s0048_a4e0* joint)
{
    bool changed = false;
    if (joint) {
        changed = joint->Fix(joint->FindInvalidJoint(false));
        for (int y = 0, p11 = joint->mLowerJoints.size(); y < p11; y++) {
            bool r = FixJoint(joint->mLowerJoints[y]);
            changed = r || changed;
        }
    }
    return changed;
}
}  // namespace SP

// @ 0x0048b080
namespace SP {
bool cSPEditorLimbStructure_s0048_a4e0::UpdateLengths(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* joints)
{
    bool changed = false;
    if (joints && !joints->empty()) {
        for (int i = 0, n = joints->size(); i < n; i++) {
            bool r = (*joints)[i]->UpdateLength(false);
            changed = r || changed;
        }
    }
    return changed;
}
}  // namespace SP

// @ 0x0048b120
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::FixZeroLengthJoints(cSPEditorLimbJoint_s0048_a4e0* joint)
{
    float len = joint->GetLength();
    if (len != 0.0f) {
        bool valid = joint->IsValid();
        if (!valid) joint->Fix(FindInvalidJoint());
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        FixZeroLengthJoints(joint->mLowerJoints.mpBegin[i]);
}
}  // namespace SP

// @ 0x0048b1e0
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::CollectLimbJoints(vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* out)
{
    CollectLimbJoints(mBaseJoint, out);
}
}  // namespace SP

// @ 0x0048b200
namespace SP {
void cSPEditorLimbStructure_s0048_a4e0::CollectLimbJoints(cSPEditorLimbJoint_s0048_a4e0* joint, vector_s0048_a4e0<cSPEditorLimbJoint_s0048_a4e0*>* out)
{
    if (joint->mJointBlock->IsLimbPart()) {
        out->push_back(joint);
        ScratchSlots<2>();
    } else {
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++) {
            if (joint->mLowerJoints[i]->mJointBlock->IsLimbPart())
                { out->push_back(joint->mLowerJoints.mpBegin[i]); ScratchSlots<2>(); }
            else
                CollectLimbJoints(joint->mLowerJoints.mpBegin[i], out);
        }
    }
}
}  // namespace SP

// @ 0x0048b2c0
namespace SP {
cSPEditorLimbJoint_s0048_a4e0* cSPEditorLimbStructure_s0048_a4e0::FindJoint(cSPEditorBlock_s0048_a4e0* block)
{
    return FindJoint(block, mBaseJoint);
}
}  // namespace SP

// @ 0x0048b2e0
namespace SP {
cSPEditorLimbJoint_s0048_a4e0* cSPEditorLimbStructure_s0048_a4e0::FindJoint(cSPEditorBlock_s0048_a4e0* block, cSPEditorLimbJoint_s0048_a4e0* joint)
{
    if (!joint || joint->mJointBlock == block) return joint;
    else {
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++) {
            cSPEditorLimbJoint_s0048_a4e0* found = FindJoint(block, joint->mLowerJoints[i]);
            if (found) return found;
        }
        return 0;
    }
}
}  // namespace SP
