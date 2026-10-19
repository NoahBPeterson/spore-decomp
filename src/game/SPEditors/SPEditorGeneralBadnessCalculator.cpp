// src/game/SPEditors/SPEditorGeneralBadnessCalculator.cpp -- migrated from slice(s) s005a7d00, s005a6e60 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorGeneralBadnessCalculator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorComplexityMeter.h"
#include "SP/cSPEditorEconomy.h"
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
#include <math.h>

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
    float mValues[27];   // +0xc .. +0x74
    cSPEditorGeneralBadnessCalculator();
    ~cSPEditorGeneralBadnessCalculator();
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
namespace SP {
struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} cSPVector3(const cSPVector3& c) : x(c.x), y(c.y), z(c.z) {} };
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
extern cSPVector3 gSymmetryPlaneNormal;  // 0x015e7a68
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

// @ 0x005a7920
namespace SP {
cSPEditorGeneralBadnessCalculator::~cSPEditorGeneralBadnessCalculator()
{}
}  // namespace SP

// @ 0x005a7930
void FUN_005a7930()
{}

// @ 0x005a7d00
void SP::cSPEditorGeneralBadnessCalculator_s005a_7d00::CalculateValues(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c)
{
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
    cSPEditorLimbJoint_s005a_7d00* j2 = j->GetOtherJoint();
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
