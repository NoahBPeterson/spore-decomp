// slice s005a7d00 — badness calculators, cSPEditorHandleSpine ctor/dtor/Init and
// assorted editor handle helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <intrin.h>
#include <math.h>
#define sqrtf(x) ((float)sqrt((double)(x)))
#define fabsf(x) ((float)fabs((double)(x)))
#include "types.h"

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
namespace COM { class IUnknown32 { public: virtual int AddRef() = 0; virtual int Release() = 0; }; }
}

struct Vector3 { float x, y, z; };

struct S36 { int v[9]; };

class cCopy9 {
public:
    void Assign(const S36& s);
};

// @ 0x005a88a0
void cCopy9::Assign(const S36& s) {
    __movsd((unsigned long*)this, (unsigned long*)&s, 9);
}

// ---- EditorTuning accessor --------------------------------------------------
struct TuningData { char pad[0x60]; Vector3 mValue; };
TuningData* EditorTuning();  // 0x00401070

// @ 0x005a8900
Vector3* __stdcall GetEditorTuningValue(Vector3* out) {
    TuningData* t = EditorTuning();
    *(int*)&out->x = *(int*)&t->mValue.x;
    *(int*)&out->y = *(int*)&t->mValue.y;
    *(int*)&out->z = *(int*)&t->mValue.z;
    return out;
}

// ---- simple handle-ish class -----------------------------------------------
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

// @ 0x005a8a60
void cHandleish::SetState(int state) {
    if (m14 && m18) {
        m10 = (void*)state;
        v5();
    }
}

// @ 0x005a8a80
void cHandleish::SetEnabled(bool enabled) {
    if (m14 && m18 && enabled != (*(unsigned char*)((char*)m14 + 4) & 1)) {
        if (enabled) {
            v5();
            v12(3, 1);
        } else {
            v12(1, 1);
        }
    }
}

// ---- SP::cSPEditorHandle / cSPEditorHandleSpine -----------------------------
namespace SP {
struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} cSPVector3(const cSPVector3& c) : x(c.x), y(c.y), z(c.z) {} };
struct cSPMatrix3 { float m[9]; cSPMatrix3() {} cSPMatrix3(const cSPMatrix3&); void Assign(const cSPMatrix3&); };  // 0x0041cb40
extern cSPVector3 gSpineOffset;   // 0x015e7e34
extern cSPMatrix3 gSpineOrient;   // 0x015e7f64

struct cSPBBTransform {
    unsigned short flags;
    unsigned short count;
    cSPVector3 offset;
    float scale;
    cSPMatrix3 rot;
    cSPBBTransform() : flags(0), count(0), scale(1.0f), rot(gSpineOrient) {}
};
struct cSPBoundingBox {
    float v[6];
    cSPBoundingBox(const cSPBoundingBox& o) { for (int i = 0; i < 6; ++i) v[i] = o.v[i]; }
    void Transform(const cSPBBTransform& t);  // 0x00409dd0
};

class cMWModel { public: char pad[0x44]; unsigned mGroups[2]; };
class cModelManager { public: PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual unsigned GetGroupIndex(unsigned key, int flag); };  // +0x28
cModelManager* ModelManager();  // 0x0067dd80

class cSPEditorBlock {
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
class cBoundsProvider {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
    virtual float* GetBounds(unsigned id);  // +0x60
};

class cSPEditorHandle : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
public:
    cSPEditorHandle();
    virtual ~cSPEditorHandle();
    void Shutdown();  // 0x0047e2c0
    void Init(void* p, int a, int b, int c);  // 0x0047db30
    char pad[0x10 - 0xc];
    cSPEditorBlock* mBlock;     // +0x10
    cMWModel* mModel;           // +0x14
    cMWModel* mOverdrawModel;   // +0x18
    char pad2[0x50 - 0x1c];
};

class cSPEditorHandleSpine : public cSPEditorHandle {
public:
    cSPVector3 mOffset;   // +0x50
    cSPMatrix3 mOrient;   // +0x5c
    cSPEditorHandleSpine();
    virtual ~cSPEditorHandleSpine() { Shutdown(); }
    void Init(void* param, const cSPVector3* offset, const cSPMatrix3* orient);  // 0x005a8970
    cSPVector3* GetAttachPoint(cSPVector3* out);  // 0x005a8b20
};
}

// ---- badness calculators -----------------------------------------------------
namespace SP {
class cSPEditorBlock2 { public: char pad[0xdc8]; unsigned mFlags; float GetMaxLimbLength(); float GetMinLimbLength(); };  // 0x0043a500 / 0x0043a460
class cSPEditorLimbJoint {
public:
    cSPEditorBlock2* mJointBlock;  // +0
    char pad[0x34 - 4];
    cSPVector3 mOriginalPosition;  // +0x34
    void GetUpperDirection(cSPVector3* out, int n);  // 0x00487e90
    void GetLowerDirection(cSPVector3* out, int n);  // 0x004878e0
    cSPEditorLimbJoint* GetOtherJoint();             // 0x00485900
};
extern cSPVector3 gSymmetryPlaneNormal;  // 0x015e7a68
extern cSPVector3 gHandAxis;             // 0x015e7d34
extern cSPVector3 gGeneralAxis;          // 0x015e7abc
extern float gAxisZero;                  // 0x01485378
inline bool BitSet(unsigned v, int n) { return ((v >> n) & 1) != 0; }

class cISPEditorBadnessCalculator {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual unsigned GetMode() = 0;  // +0x14
    virtual void pv6() = 0;
    virtual void CalculateValues(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) = 0;  // +0x1c
    virtual void SetMode(unsigned m) = 0;  // +0x20
    virtual float CalculateBadness(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) = 0;  // +0x24
};

class cSPEditorGeneralBadnessCalculator : public cISPEditorBadnessCalculator, public EA::RefCountVTemplate<int> {
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
    virtual void CalculateValues(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c);  // 0x005a7d00
    virtual float CalculateBadness(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c);  // 0x005a83d0
};
class cSPEditorHandBadnessCalculator : public cSPEditorGeneralBadnessCalculator {
public:
    virtual float CalculateBadness(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c);  // 0x005a85f0
};
}

// @ 0x005a8ad0
SP::cSPEditorHandleSpine::cSPEditorHandleSpine() : mOffset(SP::gSpineOffset) {
    mOrient.Assign(SP::gSpineOrient);
}


// @ 0x005a7d00  cSPEditorGeneralBadnessCalculator::CalculateValues
void SP::cSPEditorGeneralBadnessCalculator::CalculateValues(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) {
    if (!j) return;
    SetMode(GetMode());
    cSPVector3 U, L;
    j->GetUpperDirection(&U, 3);
    j->GetLowerDirection(&L, 3);
    mUpperLimbLength = sqrtf((a.x - U.x) * (a.x - U.x) + (a.y - U.y) * (a.y - U.y) + (a.z - U.z) * (a.z - U.z));
    mLowerLimbLength = sqrtf((a.x - L.x) * (a.x - L.x) + (a.y - L.y) * (a.y - L.y) + (a.z - L.z) * (a.z - L.z));
    cSPVector3 d1(j->mOriginalPosition.x - U.x, j->mOriginalPosition.y - U.y, j->mOriginalPosition.z - U.z);
    cSPVector3 d2(j->mOriginalPosition.x - L.x, j->mOriginalPosition.y - L.y, j->mOriginalPosition.z - L.z);
    float maxLen = j->mJointBlock->GetMaxLimbLength();
    float minLen = j->mJointBlock->GetMinLimbLength();
    float dx = a.x - j->mOriginalPosition.x, dy = a.y - j->mOriginalPosition.y, dz = a.z - j->mOriginalPosition.z;
    float up = mUpperLimbLength;
    mInvalidLength = 0.0f;
    mDistanceFromOriginalPosition = sqrtf(dx * dx + dy * dy + dz * dz);
    mChangeInUpperLimb = fabsf(up - sqrtf(d1.x * d1.x + d1.y * d1.y + d1.z * d1.z));
    float lo = mLowerLimbLength;
    mChangeInLowerLimb = fabsf(lo - sqrtf(d2.x * d2.x + d2.y * d2.y + d2.z * d2.z));
    if (maxLen < up || maxLen < lo || up < minLen || lo < minLen)
        mInvalidLength = fabsf(lo * 10.0f + up);
    cSPVector3 P(j->mOriginalPosition.x, j->mOriginalPosition.y, j->mOriginalPosition.z);
    cSPEditorLimbJoint* j2 = j->GetOtherJoint();
    float nx = -c.x, ny = -c.y, nz = -c.z;
    float d = -((U.y * ny + nx * U.x) + nz * U.z);
    float cp = ((nx * a.x + nz * a.z) + ny * a.y) + d;
    mDistanceFromCameraPlane = cp;
    mChangeInDistanceFromParallelPlane = fabsf((((nz * P.z + ny * P.y) + nx * P.x) + d) - cp);
    float arm;
    if (!j2) {
        arm = 0.0f;
    } else {
        float ax = a.x - U.x, ay = a.y - U.y, az = a.z - U.z;
        float i1 = 1.0f / sqrtf(ax * ax + (ay * ay + az * az));
        float bx = j2->mOriginalPosition.x - U.x, by = j2->mOriginalPosition.y - U.y, bz = j2->mOriginalPosition.z - U.z;
        float i2 = 1.0f / sqrtf(by * by + (bz * bz + bx * bx));
        arm = ((i2 * bx) * (i1 * ax) + (i2 * bz) * (i1 * az)) + (i2 * by) * (i1 * ay);
    }
    mArmAngle = arm;
    float qx = b.x - U.x, qy = b.y - U.y, qz = b.z - U.z;
    float iq = 1.0f / sqrtf(qx * qx + (qy * qy + qz * qz));
    float rx = P.x - U.x, ry = P.y - U.y, rz = P.z - U.z;
    float ir = 1.0f / sqrtf(rx * rx + (ry * ry + rz * rz));
    mCameraAngle = ((ir * rz) * (iq * qz) + (ir * ry) * (iq * qy)) + (ir * rx) * (iq * qx);
    const cSPVector3& G = gSymmetryPlaneNormal;
    float sd = -(U.z * G.z + (U.y * G.y + U.x * G.x));
    float ex = b.x - P.x, ey = b.y - P.y, ez = b.z - P.z;
    mChangeInDistanceFromSymmetryPlane =
        fabsf(((P.z * G.z + (P.y * G.y + P.x * G.x)) + sd) - ((G.y * a.y + (G.z * a.z + a.x * G.x)) + sd));
    float ie = 1.0f / sqrtf(ey * ey + (ez * ez + ex * ex));
    mPlaneOfSymmetryAlignment = ((ie * ex) * G.x + (ie * ey) * G.y) + (ie * ez) * G.z;
    if (j2) {
        float ux = j2->mOriginalPosition.x - U.x, uy = j2->mOriginalPosition.y - U.y, uz = j2->mOriginalPosition.z - U.z;
        float i3 = 1.0f / sqrtf(ry * ry + (rz * rz + rx * rx));
        float i4 = 1.0f / sqrtf(ux * ux + (uy * uy + uz * uz));
        mArmAngleChange = fabsf((((uz * i4) * (i3 * rz) + (uy * i4) * (i3 * ry)) + (i4 * ux) * (i3 * rx)) - mArmAngle);
    } else {
        mArmAngleChange = fabsf(0.0f - mArmAngle);
    }
}

// @ 0x005a83d0  cSPEditorGeneralBadnessCalculator::CalculateBadness
float SP::cSPEditorGeneralBadnessCalculator::CalculateBadness(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) {
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

// @ 0x005a85f0  cSPEditorHandBadnessCalculator::CalculateBadness
float SP::cSPEditorHandBadnessCalculator::CalculateBadness(cSPEditorLimbJoint* j, cSPVector3 a, cSPVector3 b, cSPVector3 c) {
    if (j) {
        CalculateValues(j, a, b, c);
        float s1 = mCameraAngleTuning * mCameraAngle + mInvalidLengthTuning * mInvalidLength + mPlaneOfSymmetryAlignmentTuning * mPlaneOfSymmetryAlignment
            + mChangeInDistanceFromSymmetryPlaneTuning * mChangeInDistanceFromSymmetryPlane + mArmAngleTuning * mArmAngle
            + mChangeInDistanceFromParallelPlaneTuning * mChangeInDistanceFromParallelPlane + mDistanceFromCameraPlaneTuning * mDistanceFromCameraPlane
            + mLowerLimbLengthTuning * mLowerLimbLength + mChangeInLowerLimbTuning * mChangeInLowerLimb
            + mUpperLimbLengthTuning * mUpperLimbLength + mChangeInUpperLimbTuning * mChangeInUpperLimb
            + mDistanceFromOriginalPositionTuning * mDistanceFromOriginalPosition + mArmAngleChangeTuning * mArmAngleChange;
        SetMode(0x14e0be29);
        float f = mCameraAngle;
        float s2 = f * mCameraAngleTuning + mInvalidLengthTuning * mInvalidLength + mPlaneOfSymmetryAlignmentTuning * mPlaneOfSymmetryAlignment
            + mChangeInDistanceFromSymmetryPlaneTuning * mChangeInDistanceFromSymmetryPlane + mArmAngleTuning * mArmAngle
            + mChangeInDistanceFromParallelPlaneTuning * mChangeInDistanceFromParallelPlane + mDistanceFromCameraPlaneTuning * mDistanceFromCameraPlane
            + mLowerLimbLengthTuning * mLowerLimbLength + mChangeInLowerLimbTuning * mChangeInLowerLimb
            + mUpperLimbLengthTuning * mUpperLimbLength + mChangeInUpperLimbTuning * mChangeInUpperLimb
            + mDistanceFromOriginalPositionTuning * mDistanceFromOriginalPosition + mArmAngleChangeTuning * mArmAngleChange;
        float b2 = (s2 - s1) * f + s1;
        if (BitSet(j->mJointBlock->mFlags, 15)) {
            float inv = 1.0f / sqrtf(c.x * c.x + c.y * c.y);
            float nx = inv * c.x, ny = inv * c.y, nz = inv * gAxisZero;
            float t = fabsf(-a.x) * 10.0f;
            float dot = fabsf(nx * gHandAxis.x + (nz * gHandAxis.z + ny * gHandAxis.y));
            return (b2 - t) * dot + t;
        }
        return b2;
    }
    return 1000000.0f;
}

// @ 0x005a8970  cSPEditorHandleSpine::Init
void SP::cSPEditorHandleSpine::Init(void* param, const cSPVector3* offset, const cSPMatrix3* orient) {
    cSPEditorHandle::Init(param, 1, 0, 0);
    if (mBlock) {
        cMWModel* model = mModel;
        *(int*)&mOffset.x = *(const int*)&offset->x;
        *(int*)&mOffset.y = *(const int*)&offset->y;
        *(int*)&mOffset.z = *(const int*)&offset->z;
        mOrient = *orient;
        if (model) {
            cModelManager* mgr = ModelManager();
            cMWModel* m = mModel;
            unsigned i = mgr->GetGroupIndex(0x31390734, 0);
            if (i < 0x40) m->mGroups[i >> 5] |= 1u << (i & 0x1f);
        }
        if (mOverdrawModel) {
            cModelManager* mgr = ModelManager();
            cMWModel* m = mOverdrawModel;
            unsigned i = mgr->GetGroupIndex(0x31390735, 0);
            if (i < 0x40) m->mGroups[i >> 5] |= 1u << (i & 0x1f);
            mgr = ModelManager();
            m = mOverdrawModel;
            i = mgr->GetGroupIndex(0x22fff11, 0);
            if (i < 0x40) m->mGroups[i >> 5] |= 1u << (i & 0x1f);
        }
    }
}

// @ 0x005a8b20
SP::cSPVector3* SP::cSPEditorHandleSpine::GetAttachPoint(cSPVector3* out) {
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
