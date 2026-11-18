// Slice s00c44610 -- SP::cLocomotiveObject::UpdateSteeringForMovementStyle (0x00c44610).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (module builds with /arch:SSE: the float
// distance still comes back in st(0), and the compare against the module threshold is
// the fcomip form `fld [thr]; fxch st(1); fcompi st(1); fstp st(0)`).
//
// Flow: bail out on a null object, on a missing creature interface, and while the
// creature's +0xb58 flag bit 9 is set.  When the creature's +0xb64 byte is set and the
// squared distance to the goal exceeds the module threshold, the steering id
// 0x00b49a50 is registered once.  Otherwise, if it is registered, it is removed and the
// goal state at +0x190/+0x19c is reset.
#include "types.h"

struct Vec3 {
    float x, y, z;
};

// Creature interface returned by the object query (only the pieces this function
// touches are modelled).
struct cCreatureBase {
    uint8_t  mPadB58[0xb58];                                 // +0x000 .. +0xb57
    uint32_t mFlagsB58;                                      // +0xb58
    uint8_t  mPadB5C[0xb64 - 0xb5c];                         // +0xb5c .. +0xb63
    uint8_t  mFlagB64;                                       // +0xb64 (via 0x00c0b700)

    // The +0xb58 bit 9 test comes out as `shr ecx,9; test cl,1` when the masked bit is
    // carried through a bool temporary, as an inlined accessor returning bool does.
    bool IsSteeringBlocked() const { return (mFlagsB58 >> 9) & 1; }

    bool GetFlagB64();                                       // 0x00c0b700
};

struct cLocomotiveObject {
    uint8_t  mPad000[0x190];                                 // +0x000 .. +0x18f
    Vec3     mGoalPosition;                                  // +0x190
    uint8_t  mbGoalFlag;                                     // +0x19c

    float DistanceSquaredToGoal();                           // 0x00c422c0
    bool  HasId(uint32_t id);                                // 0x00c426e0
    void  RemoveId(uint32_t id);                             // 0x00c42140
    void  InsertUnique(uint32_t id);                         // 0x00c43fe0
    void  UpdateSteeringForMovementStyle();                  // 0x00c44610
};

extern Vec3  kZeroGoalPosition;        // 0x0168e7e4 / 0x0168e7e8 / 0x0168e7ec
extern float g_GoalDistanceThreshold;  // 0x01574244

// @ 0x00c44610
void cLocomotiveObject::UpdateSteeringForMovementStyle()
{
    if (!this)
        return;

    typedef void* (__thiscall* tQuery)(void*, uint32_t);
    cCreatureBase* creature =
        (cCreatureBase*)((tQuery)(*(void***)this)[0xb8 / 4])(this, 0xce9f6639);
    if (!creature)
        return;

    if (creature->IsSteeringBlocked())
        return;

    if (creature->GetFlagB64()) {
        if (this->DistanceSquaredToGoal() > g_GoalDistanceThreshold) {
            if (this->HasId(0x00b49a50))
                return;
            this->InsertUnique(0x00b49a50);
            return;
        }
    }

    if (this->HasId(0x00b49a50)) {
        this->RemoveId(0x00b49a50);
        this->mbGoalFlag = 0;
        this->mGoalPosition = kZeroGoalPosition;
    }
}
