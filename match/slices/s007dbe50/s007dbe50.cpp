// @ 0x007dbe50
#include "game/types.h"
#include "cSPVector3.h"

// Only the interpolation state used by StopMotion is needed here.
namespace SP2 {
struct tLerpScalar {
    float mCurrent;
    float mTarget;
    uint32_t mSteps;
    float mMinChange;
};
struct tLerpVector3 {
    cSPVector3 mCurrent;
    cSPVector3 mTarget;
    uint32_t mSteps;
    float mMinChange;
};
}

class cSmoothCameraController {
public:
    char mCameraState[0x98];
    SP2::tLerpScalar mBufferedHeading;
    SP2::tLerpScalar mBufferedDistanceAlongCurve;
    SP2::tLerpScalar mBufferedNearClip;
    SP2::tLerpScalar mBufferedFarClip;
    SP2::tLerpScalar mBufferedFOV;
    SP2::tLerpScalar mBufferedPitchParam;
    SP2::tLerpVector3 mBufferedSubjectPosition;

    void StopMotion();
};

void cSmoothCameraController::StopMotion()
{
    mBufferedHeading.mCurrent = mBufferedHeading.mTarget;
    mBufferedDistanceAlongCurve.mCurrent = mBufferedDistanceAlongCurve.mTarget;
    mBufferedNearClip.mCurrent = mBufferedNearClip.mTarget;
    mBufferedFarClip.mCurrent = mBufferedFarClip.mTarget;
    mBufferedFOV.mCurrent = mBufferedFOV.mTarget;
    mBufferedPitchParam.mCurrent = mBufferedPitchParam.mTarget;
    mBufferedSubjectPosition.mCurrent = mBufferedSubjectPosition.mTarget;
}
