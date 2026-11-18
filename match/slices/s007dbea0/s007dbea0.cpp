// @ 0x007dbea0
#include "game/types.h"
#include "cSPVector3.h"

namespace SP {
struct tLerpScalar {
    float mCurrent, mTarget;
    uint32_t mSteps;
    float mMinChange;
};
struct tLerpVector3 {
    cSPVector3 mCurrent, mTarget;
    uint32_t mSteps;
    float mMinChange;
};
struct tSavedCameraPosition {
    bool mValid;
    int mCurrentZoomLevel;
    float mDistance;
    int mCurrentOrientation;
    float mHeading, mNearClip, mFarClip, mFOV, mPitchParam;
    cSPVector3 mSubjectPosition;
    int mFloorLevel, mWallMode;
};
class cSmoothCameraController {
public:
    char mPad00[0x28];
    int mCurrentZoomLevel;
    char mPad2c[0x6c];
    tLerpScalar mBufferedHeading;
    tLerpScalar mBufferedDistanceAlongCurve;
    tLerpScalar mBufferedNearClip;
    tLerpScalar mBufferedFarClip;
    tLerpScalar mBufferedFOV;
    tLerpScalar mBufferedPitchParam;
    tLerpVector3 mBufferedSubjectPosition;
    char mPad118[0x48];
    int mCurrentOrientation;
    char mPad164[0xa4];
    tSavedCameraPosition mCameraPositions[7];
    void SaveCameraPosition(int index);
};

void cSmoothCameraController::SaveCameraPosition(int index)
{
    if ((unsigned int)index > 6)
        return;
    tSavedCameraPosition* p = &mCameraPositions[index];
    p->mValid = true;
    p->mCurrentZoomLevel = mCurrentZoomLevel;
    p->mDistance = mBufferedDistanceAlongCurve.mCurrent;
    p->mCurrentOrientation = mCurrentOrientation;
    p->mHeading = mBufferedHeading.mCurrent;
    p->mNearClip = mBufferedNearClip.mCurrent;
    p->mFarClip = mBufferedFarClip.mCurrent;
    p->mFOV = mBufferedFOV.mCurrent;
    p->mPitchParam = mBufferedPitchParam.mCurrent;
    p->mSubjectPosition = mBufferedSubjectPosition.mCurrent;
}
}
