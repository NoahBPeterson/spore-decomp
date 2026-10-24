// Slice s00d5ccf0: 0x00D5CCF0..0x00D5D8A0.
//  0x00d5ccf0  SP::cCityVisualizer::AddNearbySentient                 (728 B)
//  0x00d5cfd0  FUN_00d5cfd0                                          (897 B)
//  0x00d5d360  SP::cAbandonedCitizenVisualizer::MakeCitizensAbandonVehicle (204 B)
//  0x00d5d430  FUN_00d5d430                                          (113 B)
//  0x00d5d4b0  SP::cActionCircle::operator=                           (127 B)
//  0x00d5d5b0  SP::cCityVisualizer::ActivateWorshipPosture           (718 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef long double float10;

struct tVec3 { float x, y, z; };
struct tQuat { float x, y, z, w; };

// ---------------------------------------------------------------- 0x00d5d4b0 types

struct VecAgents { char m[0x14]; VecAgents& operator=(const VecAgents& o); };
struct VecSlots  { char m[0x0c]; VecSlots&  operator=(const VecSlots&  o); };

struct cActionCircle {
    tVec3 mFacing;        // +0x00
    float mRadius;        // +0x0c
    float mSlotRadius;    // +0x10
    tVec3 mCenter;        // +0x14
    float mAltitude;      // +0x20
    int   mPacking;       // +0x24
    bool  mbRelative;     // +0x28
    char  pad29[3];
    tQuat mOrientation;   // +0x2c
    VecAgents mAgents;    // +0x3c
    VecSlots  mSlots;     // +0x50
    cActionCircle& operator=(const cActionCircle& o);
};

// ---------------------------------------------------------------- 0x00d5ccf0

// @ 0x00d5ccf0
void FUN_00d5ccf0(void) {}

// ---------------------------------------------------------------- 0x00d5cfd0

// @ 0x00d5cfd0
void FUN_00d5cfd0(void) {}

// ---------------------------------------------------------------- 0x00d5d360

// @ 0x00d5d360
void FUN_00d5d360(void) {}

// ---------------------------------------------------------------- 0x00d5d430

// @ 0x00d5d430
void FUN_00d5d430(void) {}

// ---------------------------------------------------------------- 0x00d5d4b0

// @ 0x00d5d4b0
cActionCircle& cActionCircle::operator=(const cActionCircle& o)
{
    mFacing = o.mFacing;
    mRadius = o.mRadius;
    mSlotRadius = o.mSlotRadius;
    mCenter = o.mCenter;
    mAltitude = o.mAltitude;
    mPacking = o.mPacking;
    mbRelative = o.mbRelative;
    mOrientation = o.mOrientation;
    mAgents = o.mAgents;
    mSlots = o.mSlots;
    return *this;
}

// ---------------------------------------------------------------- 0x00d5d5b0

// @ 0x00d5d5b0
void FUN_00d5d5b0(void) {}