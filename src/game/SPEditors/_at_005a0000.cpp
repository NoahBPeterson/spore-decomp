// src/game/SPEditors/_at_005a0000.cpp -- migrated from slice(s) s005a8d20, s005a7d00, s005a6e60, s005a5ec0, s005a1920 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_005a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocalInputState.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double __cdecl fabs(double);
extern float kOne_1485720;
extern float kHalf_1471064;
extern float k0_1_1488874;
extern float kDiv_150f2c4;
extern float k0_52_13f69b0;
extern float k0_1_150f2c8;
extern char vtbl_5a2300_a;
extern char vtbl_5a2300_b;
#include <math.h>
#include "EA/UTFWin/IWindow.h"
#include "SP/cPropertyList.h"
#include "cSPColorRGB.h"
#include "cSPColorRGBA.h"
#include "SP/cSPColorSwatch.h"
#include "SP/cSPEditorColorPicker.h"
#include <string.h>
#include <xmmintrin.h>
#include "SP/cPropertyManager.h"
#include "SP/cSPEditorComplexityMeter.h"
#include "SP/cSPEditorEconomy.h"
#include "cSPUILayout.h"
#include "cSPVerbIconRollover.h"
#include "SP/cString.h"
#include "SP/cIModelWorld.h"
#include "SP/cMWModel.h"
#include "cSPBoundingBox.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorHandleSpine.h"
#include "SP/cSPEditorLimbJoint.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include <intrin.h>
#pragma intrinsic(fabs)

// ---- items of slice s005a1920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
inline float Abs(float x) { float r = (float)fabs(x); return r; }
struct Vec3 { float x, y, z; };
struct cLocalInputState {
    char pad[0x40];
    bool OnKeyDown(int key, int x);         // 0x00697a50
    bool OnKeyUp(int key, int x);           // 0x00697a80
    bool OnMouseUp(int a, float x, float y, int b);   // 0x00697af0
    unsigned int OnMouseWheel(int a, float b, float x, int y);  // 0x00697b40
};
struct Cam {
    char  pad0[0x14];
    float m14;          // +0x14
    char  pad18[0x2c - 0x18];
    char  m2c;          // +0x2c
    char  pad2d[0x30 - 0x2d];
    float m30;          // +0x30
    char  pad34[0x38 - 0x34];
    float m38;          // +0x38
    float m3c;          // +0x3c
    float m40;          // +0x40
    float m44, m48, m4c, m50, m54;   // +0x44..0x58
    float m58;          // +0x58
    float m5c;          // +0x5c
    char  pad60[0x74 - 0x60];
    Vec3  m74;          // +0x74
    Vec3  m80;          // +0x80
    float m8c;          // +0x8c
    char  pad90[0x9c - 0x90];
    char  m9c;          // +0x9c
    char  pad9d[0xa0 - 0x9d];
    cLocalInputState mInput;   // +0xa0

    void SetSomething(Vec3 v, bool immediate);                       // 0x005a2010
    bool OnKeyDown(int key, int x);                                  // 0x005a2080
    bool OnKeyUp(int key, int x);                                    // 0x005a2120
    bool OnMouseUp(int a, float x, float y, int b);                  // 0x005a21c0
    void ZoomBy(float factor);                                       // 0x005a2200
    void AddAngle(float d);                                          // 0x005a2240
    void ComputeView(float* a, float* b, float* c, float* out);      // 0x005a2260
    void UpdatePitch();                                              // 0x005a22d0
    void ClearVtables();                                             // 0x005a2300
    bool OnMouseWheel(int a, float b, float x, int y);               // 0x005a2580
};
extern float kOne_1485720;
extern float kHalf_1471064;
extern float k0_1_1488874;
extern float kDiv_150f2c4;
extern float k0_52_13f69b0;
extern float k0_1_150f2c8;
extern char vtbl_5a2300_a;
extern char vtbl_5a2300_b;
// ---- items of slice s005a1920 end

// ---- items of slice s005a5ec0 begin
#pragma intrinsic(sqrt)
// ---- items of slice s005a5ec0 end

// ---- items of slice s005a6e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cBadnessBase1 { public: virtual ~cBadnessBase1() {} virtual int v0(); };
}
namespace SP {
class cBadnessBase2 {
public:
    cBadnessBase2() : m80(0) {}
    virtual ~cBadnessBase2() {}
    virtual int v0();
    int m80;
};
}
namespace SP {
class cSPEditorGeneralBadnessCalculator : public cBadnessBase1, public cBadnessBase2 {
public:
    float mDistanceFromOriginalPosition;            // +0x0c
    float mChangeInUpperLimb;                       // +0x10
    float mChangeInLowerLimb;                       // +0x14
    float mArmAngleChange;                          // +0x18
    float mUpperLimbLength;                         // +0x1c
    float mDistanceFromCameraPlane;                 // +0x20
    float mChangeInDistanceFromParallelPlane;       // +0x24
    float mArmAngle;                                // +0x28
    float mChangeInDistanceFromSymmetryPlane;       // +0x2c
    float mPlaneOfSymmetryAlignment;                // +0x30
    float mLowerLimbLength;                         // +0x34
    float mInvalidLength;                           // +0x38
    float mCameraAngle;                             // +0x3c
    bool  mSnapToCardinalOrientations;              // +0x40
    char  pad41[0x37];                              // +0x41.. (keeps the retail size)

    cSPEditorGeneralBadnessCalculator();
    ~cSPEditorGeneralBadnessCalculator();

    void SetTuningValues(void* group);              // va 005a7930
};
}
// ---- items of slice s005a6e60 end

// ---- items of slice s005a7d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define sqrtf(x) ((float)sqrt((double)(x)))
#define fabsf(x) ((float)fabs((double)(x)))
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_7d00 {
public:
    RefCountVTemplate_s005a_7d00() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s005a_7d00() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
}
namespace EA {
namespace COM {
 class IUnknown32_s005a_7d00 {
     public: virtual int AddRef() = 0;
     virtual int Release() = 0;
 };
}
}
struct Vector3 { float x, y, z; };
struct S36 { int v[9]; };
class cCopy9 {
public:
    S36 m;
    cCopy9* Assign(const S36& s);
};
struct TuningData { char pad[0x60]; Vector3 mValue; };
TuningData* EditorTuning();  // 0x00401070
class cHandleish {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void v5();                 // +0x14
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void v12(int, int);        // +0x30
    char  pad0[0xc];
    void* m10;    // +0x10
    void* m14;    // +0x14
    void* m18;    // +0x18
    void SetState(int state);   // 0x005a8a60
    void SetEnabled(bool enabled);  // 0x005a8a80
};
namespace SP {
struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} cSPVector3(const cSPVector3& c) : x(c.x), y(c.y), z(c.z) {} };
}
namespace SP {
struct cSPMatrix3 { float m[9]; cSPMatrix3() {} cSPMatrix3(const cSPMatrix3&); void Assign(const cSPMatrix3&); };  // 0x0041cb40
}
namespace SP {
extern cSPVector3 gSpineOffset;   // 0x015e7e34
}
namespace SP {
extern cSPMatrix3 gSpineOrient;   // 0x015e7f64
}
namespace SP {
struct cSPBBTransform {
    unsigned short flags;
    unsigned short count;
    cSPVector3 offset;
    float scale;
    cSPMatrix3 rot;
    cSPBBTransform() : flags(0), count(0), scale(1.0f), rot(gSpineOrient) {}
};
}
namespace SP {
struct cSPBoundingBox {
    float v[6];
    cSPBoundingBox(const cSPBoundingBox& o) { for (int i = 0; i < 6; ++i) v[i] = o.v[i]; }
    void Transform(const cSPBBTransform& t);  // 0x00409dd0
};
}
namespace SP {
struct cMWModel_s005a_7d00 { private: public: char pad[0x44]; unsigned mGroups[2]; };
}
namespace SP {
class cSPEditorBlock_s005a_7d00 {
public:
    char pad0[0x10];
    unsigned mId;               // +0x10
    char pad1[4];
    class cBoundsProvider* mProvider;  // +0x18
    char pad2[0x48 - 0x1c];
    cSPVector3 mPos;            // +0x48
    char pad3[0x60 - 0x54];
    cSPMatrix3 mRot;            // +0x60
};
}
namespace SP {
class cBoundsProvider {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
    virtual float* GetBounds(unsigned id);  // +0x60
};
}
namespace SP {
class cSPEditorHandle_s005a_7d00 : public EA::COM::IUnknown32_s005a_7d00, public EA::RefCountVTemplate_s005a_7d00<int> {
public:
    cSPEditorHandle_s005a_7d00();
    virtual ~cSPEditorHandle_s005a_7d00();
    void Shutdown();  // 0x0047e2c0
    void Init(void* p, int a, int b, int c);  // 0x0047db30
    char pad[0x10 - 0xc];
    cSPEditorBlock_s005a_7d00* mBlock;     // +0x10
    cMWModel_s005a_7d00* mModel;           // +0x14
    cMWModel_s005a_7d00* mOverdrawModel;   // +0x18
    char pad2[0x50 - 0x1c];
};
}
namespace SP {
class cSPEditorHandleSpine_s005a_7d00 : public cSPEditorHandle_s005a_7d00 {
public:
    cSPVector3 mOffset;   // +0x50
    cSPMatrix3 mOrient;   // +0x5c
    cSPEditorHandleSpine_s005a_7d00();
    virtual ~cSPEditorHandleSpine_s005a_7d00() { Shutdown(); }
    void Init(void* param, const cSPVector3* offset, const cSPMatrix3* orient);  // 0x005a8970
    cSPVector3* GetAttachPoint(cSPVector3* out);  // 0x005a8b20
};
}
namespace SP {
class cSPEditorBlock2 { public: char pad[0xdc8]; unsigned mFlags; float GetMaxLimbLength(); float GetMinLimbLength(); };  // 0x0043a500 / 0x0043a460
}
namespace SP {
class cSPEditorLimbJoint_s005a_7d00 {
public:
    cSPEditorBlock2* mJointBlock;  // +0
    char pad[0x34 - 4];
    cSPVector3 mOriginalPosition;  // +0x34
    void GetUpperDirection(cSPVector3* out, int n);  // 0x00487e90
    void GetLowerDirection(cSPVector3* out, int n);  // 0x004878e0
    cSPEditorLimbJoint_s005a_7d00* GetOtherJoint();             // 0x00485900
};
}
namespace SP {
extern cSPVector3 gGeneralAxis;          // 0x015e7abc
}
namespace SP {
extern float gAxisZero;                  // 0x01485378
}
namespace SP {
inline bool BitSet(unsigned v, int n) { return ((v >> n) & 1) != 0; }
}
namespace SP {
class cISPEditorBadnessCalculator {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual unsigned GetMode() = 0;  // +0x14
    virtual void pv6() = 0;
    virtual void CalculateValues(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) = 0;  // +0x1c
    virtual void SetMode(unsigned m) = 0;  // +0x20
    virtual float CalculateBadness(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) = 0;  // +0x24
};
}
namespace SP {
class cSPEditorGeneralBadnessCalculator_s005a_7d00 : public cISPEditorBadnessCalculator, public EA::RefCountVTemplate_s005a_7d00<int> {
public:
    float mDistanceFromOriginalPositionTuning;  // +0xc
    float mChangeInUpperLimbTuning;  // +0x10
    float mChangeInLowerLimbTuning;  // +0x14
    float mUpperLimbLengthTuning;  // +0x18
    float mLowerLimbLengthTuning;  // +0x1c
    float mDistanceFromCameraPlaneTuning;  // +0x20
    float mChangeInDistanceFromParallelPlaneTuning;  // +0x24
    float mArmAngleTuning;  // +0x28
    float mChangeInDistanceFromSymmetryPlaneTuning;  // +0x2c
    float mPlaneOfSymmetryAlignmentTuning;  // +0x30
    float mInvalidLengthTuning;  // +0x34
    float mCameraAngleTuning;  // +0x38
    float mArmAngleChangeTuning;  // +0x3c
    bool mSnapToCardinalOrientations;  // +0x40
    float mDistanceFromOriginalPosition;  // +0x44
    float mUpperLimbLength;  // +0x48
    float mLowerLimbLength;  // +0x4c
    float mChangeInUpperLimb;  // +0x50
    float mChangeInLowerLimb;  // +0x54
    float mDistanceFromCameraPlane;  // +0x58
    float mChangeInDistanceFromParallelPlane;  // +0x5c
    float mArmAngle;  // +0x60
    float mChangeInDistanceFromSymmetryPlane;  // +0x64
    float mPlaneOfSymmetryAlignment;  // +0x68
    float mInvalidLength;  // +0x6c
    float mCameraAngle;  // +0x70
    float mArmAngleChange;  // +0x74
    virtual void CalculateValues(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c);  // 0x005a7d00
    virtual float CalculateBadness(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c);  // 0x005a83d0
};
}
// ---- items of slice s005a7d00 end

// ---- items of slice s005a8d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchange)
struct Vector3_s005a_8d20 {
    float x, y, z;
    Vector3_s005a_8d20() {}
    Vector3_s005a_8d20(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s005a_8d20 operator-(const Vector3_s005a_8d20& b) const { return Vector3_s005a_8d20(x - b.x, y - b.y, z - b.z); }
    float Dot(const Vector3_s005a_8d20& b) const { return x * b.x + y * b.y + z * b.z; }
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3& SetRotation(const Quaternion& q);   // 0x0041CB40
};
Matrix3 operator*(const Matrix3& a, const Matrix3& b);   // 0x0041DE20
struct Transform {
    uint16_t mnFlags;            // +0x0
    uint16_t mnTransformCount;   // +0x2
    Vector3_s005a_8d20  mOffset;            // +0x4
    float    mfScale;            // +0x10
    Matrix3  mRotation;          // +0x14
    void SetOffset(const Vector3_s005a_8d20& offset)
    {
        mOffset = offset;
        mnFlags |= 4;
        mnTransformCount++;
    }
    void SetRotation(const Matrix3& rotation)
    {
        mnFlags |= 2;
        mnTransformCount++;
        mRotation = rotation;
    }
};
namespace SP {
struct cSPModelObject {
    char      pad_0[8];
    Transform mTransform;   // +0x8
};
}
namespace SP {
class cSPEditorRigblockModel {
public:
virtual void Unk0();
virtual void Unk1();
virtual void Unk2();
virtual void Unk3();
virtual void Unk4();
virtual void Unk5();
virtual void Unk6();
virtual void Unk7();
    virtual void Unk8();
    virtual Vector3_s005a_8d20 GetPosition();   // slot 9
    void UpdateModelTransforms();

    char pad_4[0x10 - 0x4];
    cSPEditorRigblockModel* mpParent;   // +0x10
    cSPModelObject*         mpModel;    // +0x14
    cSPModelObject*         mpModelLOD; // +0x18
    char pad_1c[0x5c - 0x1c];
    Quaternion              mOrientation;   // +0x5c
    char pad_6c[0x60 + 0x5c - 0x6c];
};
}
// ---- items of slice s005a8d20 end

// @ 0x005a2010
void Cam::SetSomething(Vec3 v, bool immediate)
{
    m80 = v;
    if (immediate)
        m74 = v;
}

// @ 0x005a2080
bool Cam::OnKeyDown(int key, int x)
{
    switch (key) {
    case 0x6b: case 0x6d: case 0xbb: case 0xbc: case 0xbd: case 0xbe:
        mInput.OnKeyDown(key, x);
        return true;
    default:
        return false;
    }
}

// @ 0x005a2120
bool Cam::OnKeyUp(int key, int x)
{
    switch (key) {
    case 0x6b: case 0x6d: case 0xbb: case 0xbc: case 0xbd: case 0xbe:
        mInput.OnKeyUp(key, x);
        return true;
    default:
        return false;
    }
}

// @ 0x005a21c0
bool Cam::OnMouseUp(int a, float x, float y, int b)
{
    mInput.OnMouseUp(a, x, y, b);
    m2c = 0;
    return true;
}

// @ 0x005a2200
void Cam::ZoomBy(float factor)
{
    float one = kOne_1485720;
    float f = (factor + one) * m38;
    m38 = f;
    float t = m5c;
    if (f > t)
        m38 = t;
    else {
        t = m58;
        if (t > f)
            m38 = t;
    }
    m9c = 1;
}

// @ 0x005a2240
void Cam::AddAngle(float d)
{
    m30 = k0_1_150f2c8 * d + m30;
}

// @ 0x005a2260
void Cam::ComputeView(float* a, float* b, float* c, float* out)
{
    float angle = m4c;
    float scale = k0_52_13f69b0 / m8c;
    *a = m44;
    *b = m48;
    *c = m4c;
    out[0] = -((m50 * scale) * angle);
    out[1] = -angle;
    out[2] = (m54 * scale) * angle;
}

// @ 0x005a22d0
void Cam::UpdatePitch()
{
    m54 = (k0_1_1488874 - (Abs(m48) / kDiv_150f2c4) * kHalf_1471064) * m8c + m40;
}

// @ 0x005a2300
void Cam::ClearVtables()
{
    *(void**)((char*)this + 4) = &vtbl_5a2300_a;
    *(void**)this = &vtbl_5a2300_b;
}

// @ 0x005a6e00
float FUN_005a6e00(float x)
{
    double d = x;
    if (d > 1.0 || !(d <= 1.0)) d = 1.0;
    else if (d < 0.0) d = 0.0;
    return (float)d;
}

// @ 0x005a7900
namespace SP {
cSPEditorGeneralBadnessCalculator::cSPEditorGeneralBadnessCalculator()
{}
}  // namespace SP

// @ 0x005a83d0
float SP::cSPEditorGeneralBadnessCalculator_s005a_7d00::CalculateBadness(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c)
{
    if (j) {
        CalculateValues(j, a, b, c);
        float s = mArmAngleChange * mArmAngleChangeTuning + mCameraAngle * mCameraAngleTuning + mInvalidLength * mInvalidLengthTuning
            + mPlaneOfSymmetryAlignment * mPlaneOfSymmetryAlignmentTuning + mChangeInDistanceFromSymmetryPlane * mChangeInDistanceFromSymmetryPlaneTuning
            + mArmAngle * mArmAngleTuning + mChangeInDistanceFromParallelPlane * mChangeInDistanceFromParallelPlaneTuning
            + mDistanceFromCameraPlane * mDistanceFromCameraPlaneTuning + mChangeInLowerLimb * mChangeInLowerLimbTuning
            + mChangeInUpperLimb * mChangeInUpperLimbTuning + mDistanceFromOriginalPosition * mDistanceFromOriginalPositionTuning;
        if (BitSet(j->mJointBlock->mFlags, 15)) {
            float inv = 1.0f / sqrtf(c.x * c.x + c.y * c.y);
            float nx = inv * c.y, ny = inv * c.x, nz = inv * gAxisZero;
            float t = fabsf(-a.x) * 10.0f;
            float dot = fabsf(nx * gGeneralAxis.x + (nz * gGeneralAxis.z + ny * gGeneralAxis.y));
            return (s - t) * dot + t;
        }
        return s;
    }
    return 100000.0f;
}

// @ 0x005a88a0
cCopy9* cCopy9::Assign(const S36& s)
{
    m = s;
    return this;
}

// @ 0x005a8900
Vector3* __stdcall GetEditorTuningValue(Vector3* out)
{
    TuningData* t = EditorTuning();
    *(int*)&out->x = *(int*)&t->mValue.x;
    *(int*)&out->y = *(int*)&t->mValue.y;
    *(int*)&out->z = *(int*)&t->mValue.z;
    return out;
}

// @ 0x005a8a60
void cHandleish::SetState(int state)
{
    if (m14 && m18) {
        m10 = (void*)state;
        v5();
    }
}

// @ 0x005a8a80
void cHandleish::SetEnabled(bool enabled)
{
    if (m14 && m18 && enabled != (*(unsigned char*)((char*)m14 + 4) & 1)) {
        if (enabled) {
            v5();
            v12(3, 1);
        } else {
            v12(1, 1);
        }
    }
}

// @ 0x005a8ad0
SP::cSPEditorHandleSpine_s005a_7d00::cSPEditorHandleSpine_s005a_7d00()
: mOffset(SP::gSpineOffset) {
    mOrient.Assign(SP::gSpineOrient);
}

// @ 0x005a8b20
SP::cSPVector3* SP::cSPEditorHandleSpine_s005a_7d00::GetAttachPoint(cSPVector3* out)
{
    if (mModel && mBlock) {
        unsigned id = mBlock->mId;
        float* bp = mBlock->mProvider->GetBounds(id);
        cSPBoundingBox bb(*(cSPBoundingBox*)bp);
        cSPBBTransform t;
        t.flags |= 4;
        t.offset = mBlock->mPos;
        t.count += 1;
        t.rot = mBlock->mRot;
        t.count += 1;
        t.flags |= 2;
        bb.Transform(t);
        const float* M = mBlock->mRot.m;
        float ox = mOffset.x, oy = mOffset.y, oz = mOffset.z;
        float rx = (M[3] * oy + M[6] * oz) + M[0] * ox;
        float ry = (M[1] * ox + M[4] * oy) + M[7] * oz;
        float rz = (M[2] * ox + M[5] * oy) + M[8] * oz;
        out->x = (bb.v[3] + bb.v[0]) * 0.5f + rx;
        out->y = (bb.v[4] + bb.v[1]) * 0.5f + ry;
        out->z = (bb.v[5] + bb.v[2]) * 0.5f + rz;
        return out;
    }
    float x = gSpineOffset.x; out->x = x;
    float y = gSpineOffset.y; out->y = y;
    float z = gSpineOffset.z; out->z = z;
    return out;
}

// @ 0x005a8d20
void SP::cSPEditorRigblockModel::UpdateModelTransforms()
{
    if (mpModel && mpModelLOD) {
        Vector3_s005a_8d20 position = GetPosition();
        mpModel->mTransform.SetOffset(position);
        mpModelLOD->mTransform.SetOffset(position);
        Matrix3 rotation;
        rotation.SetRotation(mOrientation);
        if (mpParent)
            rotation = rotation * *(Matrix3*)((char*)mpParent + 0x60);
        mpModel->mTransform.SetRotation(rotation);
        mpModelLOD->mTransform.SetRotation(rotation);
    }
}
