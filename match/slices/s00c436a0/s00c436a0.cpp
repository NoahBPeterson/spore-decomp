// match/slices/s00c436a0/s00c436a0.cpp -- SP::cLocomotiveObject::ClearGoalAndStop (0x00c436a0)
//
// Retail puts SetDesiredSpeed at vtable +0xc4 and SetGoal at +0xdc, the offsets the hand-written
// stubs in SPCityVisualizer.cpp / SPWeapons.cpp record; the canonical header lists the developer
// PDB declaration order (+0x94 / +0xac).  The "no goal" request is built the same way
// SPCityVisualizer.cpp builds it, since SP::tNavigationGoal has no retail constructor body.
#include "game/types.h"
#include "SP/cLocomotiveObject.h"

namespace SP {

extern float gDefaultDstX;   // 0x0168e7e4
extern float gDefaultDstY;   // 0x0168e7e8
extern float gDefaultDstZ;   // 0x0168e7ec

struct Waypoint;
struct RequestVec3 { float x, y, z; };

// Retail layout of a navigation-goal request (SP::tNavigationGoal, 0x74 bytes).
struct LocRequest {
    Waypoint*     mpBegin;                 // +0x00  waypoint vector
    Waypoint*     mpEnd;                   // +0x04
    Waypoint*     mpCapacity;              // +0x08
    char          pad0c[0x14 - 0x0c];
    RequestVec3   mDst;                    // +0x14  current waypoint destination
    float         mGoalStopDistance;       // +0x20
    int           mWaypointType;           // +0x24  next waypoint type
    char          pad28[0x4c - 0x28];
    unsigned char mWaypointFlags;          // +0x4c  next waypoint flags
    char          pad4d[0x50 - 0x4d];
    RequestVec3   mFacing;                 // +0x50  reference direction
    int           mType;                   // +0x5c  (0 none, 1/3 follow, 2 hold)
    float         mAcceptableStopDistance; // +0x60
    float         mField64;                // +0x64  (alignment threshold)
    float         mPrevDistance;           // +0x68
    float         mElapsed;                // +0x6c
    int           mField70;                // +0x70

    ~LocRequest()   // the waypoint vector's block is freed through its array cookie
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
};

// cLocomotiveObject with the retail virtual order (only the slots this function calls are named).
class cLocomotiveObjectRetail {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0();
    virtual void SetDesiredSpeed(float speed, int flag);   // +0xc4
    virtual void vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void vd8();
    virtual void SetGoal(const LocRequest& goal);          // +0xdc

    char         mPad04[0x270 - 0x04];
    unsigned int mMoveStatusFlags;                         // +0x270
};

// @ 0x00c436a0
void cLocomotiveObject::ClearGoalAndStop()
{
    cLocomotiveObjectRetail* loco = (cLocomotiveObjectRetail*)this;
    {
        LocRequest goal;
        goal.mpBegin = 0;
        goal.mpEnd = 0;
        goal.mpCapacity = 0;
        goal.mDst.x = gDefaultDstX;
        goal.mDst.y = gDefaultDstY;
        goal.mDst.z = gDefaultDstZ;
        goal.mGoalStopDistance = 1.0f;
        goal.mWaypointType = 0;
        goal.mWaypointFlags = 0;
        goal.mFacing.x = 0.0f;
        goal.mFacing.y = 0.0f;
        goal.mFacing.z = 0.0f;
        goal.mType = 0;
        goal.mAcceptableStopDistance = 2.0f;
        goal.mField64 = 0.9f;
        goal.mPrevDistance = 3.402823466e+38f;
        goal.mElapsed = 0.0f;
        goal.mField70 = 0;
        loco->SetGoal(goal);
    }
    loco->SetDesiredSpeed(0.0f, 1);
    loco->mMoveStatusFlags = 0;
}

}  // namespace SP
