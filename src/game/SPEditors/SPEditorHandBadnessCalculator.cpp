// src/game/SPEditors/SPEditorHandBadnessCalculator.cpp -- migrated from slice(s) s005a8d20, s005a7d00 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorHandBadnessCalculator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
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
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"

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
extern cSPVector3 gHandAxis;             // 0x015e7d34
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
class cSPEditorGeneralBadnessCalculator : public cISPEditorBadnessCalculator, public EA::RefCountVTemplate_s005a_7d00<int> {
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
namespace SP {
class cSPEditorHandBadnessCalculator : public cSPEditorGeneralBadnessCalculator {
public:
    virtual float CalculateBadness(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c);  // 0x005a85f0
};
}
// ---- items of slice s005a7d00 end

// ---- items of slice s005a8d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchange)
namespace SP {
class cSPEditorHandBadnessCalculator_s005a_8d20 {
public:
    void* AsInterface(uint32_t typeID);  // 0x005a8e10 (SP::cSPEditorHandBadnessCalculator::AsInterface)
};
}
// ---- items of slice s005a8d20 end

// @ 0x005a85f0
float SP::cSPEditorHandBadnessCalculator::CalculateBadness(cSPEditorLimbJoint_s005a_7d00* j, cSPVector3 a, cSPVector3 b, cSPVector3 c)
{
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

// @ 0x005a8e10
void* SP::cSPEditorHandBadnessCalculator_s005a_8d20::AsInterface(uint32_t typeID)
{
    return (typeID == 0xee3f516e || typeID == 0x212d6eb) ? this : 0;
}
