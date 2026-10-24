// Slice s00d8dcc0: the lounge-group tick.
//
// Target: 00d8dcc0  SP::LOUNGE_Tick  (3079 bytes, __cdecl, returns bool)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// One function.  It is the per-frame driver for a creature that has joined a
// lounge/guard group: if the creature is idle and not yet in the group it
// walks it over to the group's spot, otherwise it runs the four-state idle
// animation machine (look-around, spice, social) and plays the chosen
// animation, aiming it at a partner when the partner exposes an animation id.
//
// Layouts are recovered by role.  Every field the code touches is named; the
// two virtual slots with no typed owner (the locomotive speed accessor at 0x74
// and the creature's 0xc0b780 classifier) are called through VSLOT() so the
// emitted code keeps the original `call dword ptr [reg + off]` shape.

#include "types.h"

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;

struct Vec3 { float x, y, z; };

// Vtable call: VSLOT(<thiscall fn ptr type>, pObject, <byte offset>)(args...)
#define VSLOT(fnptr, obj, off) ((fnptr)((obj)->mpVtbl_00[(off) / 4]))

// 0x4472a59 is the group type that carries a world position (the tribe site);
// every other group type is approached without a facing target.
static const u32 kGroupTypeTribe = 0x4472a59;

// LOUNGE_memory_block::mState_000 values.
enum LoungeState {
    kLook1  = 0,
    kLook2  = 1,
    kSpice  = 2,
    kSocial = 3
};

// The idle animation ids bake the pose variants into the low bits; the social
// case adds a random index to a base id.
static const u32 kIdleAnimSetA    = 0x731ea3ea;   // used when 0xc0b780 is true
static const u32 kIdleAnimSetB    = 0xb31eb92c;   // used when 0xc0b780 is false
static const u32 kIdleAnimLook4   = 0xf31ea59c;
static const u32 kIdleAnimLook8   = 0x051c689b;
static const u32 kIdleAnimSpiceTailA = 0x6e04c29a;
static const u32 kIdleAnimSpiceTailB = 0x6e04c340;
static const u32 kIdleAnimSpiceBase  = 0x519e154;
static const u32 kIdleAnimSocialBase22 = 0x42a1ca0;
static const u32 kIdleAnimSocialBase23 = 0x42a1caa;
static const u32 kIdleAnimSocialBase24 = 0x42a1ca5;
static const u32 kIdleAnimSocialBase25 = 0x42a1caf;

// The lounge "idle playback" object, eight bytes into the actor part.
struct cIdleAnimator {
    void** mpVtbl_00;
    // SP::cSPCreatureBase::PlayIdleAnimation 0x00bc96a0 (ret 8)
    u32 Play(u32 nFlags, u32 nArg);
};

struct LOUNGE_Group {
    u8  mPad_000[8];
    u32 mType_008;                       // kGroupTypeTribe for the tribe site
};

// The object hanging off cSPCreatureBase+0xb4c; only the animator at +8 and
// the current group pointer at +0x600 are read here.
struct LOUNGE_Actor {
    u8  mPad_000[8];
    cIdleAnimator mIdle_008;
    u8  mPad_00c[0x600 - 0x0c];
    LOUNGE_Group* mpGroup_600;
};

struct cNearNoun {
    u8  mPad_000[0x15c];
    u32 mMode_15c;                       // 4 / 8 select the "look" anim family
    const Vec3* GetPosition();           // 0x00c6acc0
};

struct cSPCreatureBase;

// The locomotive sub-object at cSPCreatureBase+0xc0.
struct cLocomotiveObject {
    void** mpVtbl_00;
    // Slot 0x74: the creature's movement speed scale.  The original calls it
    // twice per move, once for the half speed and once for the full speed.
    float GetSpeed()
    {
        return VSLOT(float (__thiscall*)(cLocomotiveObject*), this, 0x74)(this);
    }
    bool IsNearGoal();                   // 0x00c42e20
};

// The senses / animation-tuning block at cSPCreatureBase+0xb20.
struct cCreatureSenses {
    u8  mPad_000[0x5ac];
    float mSocialTimer_5ac;              // > 0 picks the social state
    u8  mPad_5b0[0x5e4 - 0x5b0];
    u32 mAnimCount_5e4;                  // social kind 0x25
    u32 mAnimCount_5e8;                  // social kind 0x22
    u32 mAnimCount_5ec;                  // social kind 0x24
    u32 mAnimCount_5f0;                  // social kind 0x23
    u8  mPad_5f4[0x620 - 0x5f4];
    u32 mSocialKind_620;                 // 0x22..0x25
};

struct LOUNGE_memory_block {
    u32  mState_000;                     // LoungeState
    Vec3 mMyPosition_004;                // the group spot this block stands on
    u32  mAnimHandle_010;                // last animation handle handed out
    u8   mbOnlyGuard_014;                // restrict the group search to guards

    // 0x00d8d820
    void JoinGroup(cSPCreatureBase* pCreature, LOUNGE_Group* pGroup);
};

struct cSPCreatureBase {
    u8  mPad_000[0xc0];
    cLocomotiveObject mLocomotive_0c0;
    u8  mPad_0c4[0xb20 - 0x0c4];
    cCreatureSenses* mpSenses_0b20;
    u8  mPad_0b24[0xb4c - 0x0b24];
    LOUNGE_Actor* mpLounge_0b4c;
    void* mpAnimOwner_0b54;              // partner animation-list owner
    u8  mPad_0b58[0xf90 - 0x0b58];
    u8  mbLoungeGoalSet_f90;             // gate for the animation state machine

    void d0c0(u32 nMode, char cArg);                                  // 0x00c0d0c0
    cNearNoun* GetNoun();                                             // 0x00c04590
    bool FUN_00c0b780();                                              // 0x00c0b780
    u32 PlayAnimation(u32 nAnimId, s32 nArg1, s32 nArg2);              // 0x00c12190
    u32 PlayAnimationWithTarget(u32 nAnimId, const void* pTarget,
                                u32 nTargetId, s32 nArg);             // 0x00c14940
    bool AnimationFinished(u32 nAnimHandle);                          // 0x00c12400
    void MoveToPointAtSpeed(u32 nMode, const Vec3* pPoint,
                            float fHalfSpeed, float fSpeed);          // 0x00c1c1d0
    void MoveToPointAndFacingAtSpeed(u32 nMode, const Vec3* pPoint,
                                     const Vec3& vDirection, float fHalfSpeed,
                                     float fSpeed);                   // 0x00c1c5c0
};

// The range object returned by 0x004d9030: a bare begin/end pair of ids.
struct IntRange {
    s32* mpBegin_00;
    s32* mpEnd_04;
};

IntRange* FUN_004d9030(void* pOwner);                                        // 0x004d9030
cSPCreatureBase* FUN_00d7bcb0(LOUNGE_memory_block* pBlock, LOUNGE_Group* pGroup,
                              cSPCreatureBase* pCreature);                   // 0x00d7bcb0
LOUNGE_Group* FindGuardOrLoungeGroup(cSPCreatureBase* pCreature, u8 bOnlyGuard); // 0x00d82040
Vec3 normalized_safe(const Vec3& v);                                         // 0x00449c20

struct cRandomLinearCongruential {
    // EA::Random::RandomLinearCongruential::RandomUint32Uniform 0x00a68fb0
    u32 RandomUint32Uniform(u32 nMax);
};
extern cRandomLinearCongruential gRandom_1601760;                            // 0x01601760

namespace SP {

// @ 0x00d8dcc0
bool LOUNGE_Tick(cSPCreatureBase* pCreature, u32 nArg1, u32 nArg2, u32 nFlags,
                 u32 nArg4, LOUNGE_memory_block* pBlock)
{
    LOUNGE_Actor* pLounge = pCreature->mpLounge_0b4c;
    LOUNGE_Group* pGroup = pLounge->mpGroup_600;
    if (pGroup == 0)
        return false;

    // A running idle animation means the creature is already busy: skip the
    // approach step and fall through to the animation state machine.
    if (pLounge->mIdle_008.Play(0x40000000, 0) == 0) {
        LOUNGE_Group* pDestination =
            FindGuardOrLoungeGroup(pCreature, pBlock->mbOnlyGuard_014);
        if (pDestination != 0 && pDestination != pGroup) {
            pCreature->d0c0(6, 1);
            pBlock->JoinGroup(pCreature, pDestination);

            if (pDestination->mType_008 == kGroupTypeTribe) {
                const Vec3* pTargetPos = pCreature->GetNoun()->GetPosition();

                Vec3 vDelta;
                vDelta.x = pBlock->mMyPosition_004.x - pTargetPos->x;
                vDelta.y = pBlock->mMyPosition_004.y - pTargetPos->y;
                vDelta.z = pBlock->mMyPosition_004.z - pTargetPos->z;

                // The two GetSpeed() calls are made in this order on purpose:
                // the full speed is pushed first, the halved one second.
                pCreature->MoveToPointAndFacingAtSpeed(
                    2, &pBlock->mMyPosition_004, normalized_safe(vDelta),
                    pCreature->mLocomotive_0c0.GetSpeed() * 0.5f,
                    pCreature->mLocomotive_0c0.GetSpeed());
            } else {
                pCreature->MoveToPointAtSpeed(
                    2, &pBlock->mMyPosition_004,
                    pCreature->mLocomotive_0c0.GetSpeed() * 0.5f,
                    pCreature->mLocomotive_0c0.GetSpeed());
            }
            return true;
        }
    }

    // --- animation state machine -------------------------------------------
    if (pCreature->mbLoungeGoalSet_f90 == 0 && (nFlags & 0x180000) == 0)
        return true;
    if (!pCreature->mLocomotive_0c0.IsNearGoal())
        return true;
    if (pBlock->mAnimHandle_010 != 0 &&
        !pCreature->AnimationFinished(pBlock->mAnimHandle_010))
        return true;

    const bool bLookMode   = (pCreature->GetNoun()->mMode_15c == 4);
    const bool bSocialMode = (pCreature->GetNoun()->mMode_15c == 8);

    u32 nAnimId;
    if (pCreature->FUN_00c0b780()) {
        switch (pBlock->mState_000) {
        case kLook1:
            if (pCreature->mpSenses_0b20->mSocialTimer_5ac > 0.0f)
                pBlock->mState_000 = kSocial;
            else
                pBlock->mState_000 = kLook2;
            nAnimId = kIdleAnimSetA;
            break;

        case kLook2:
            pBlock->mState_000 = kSpice;
            nAnimId = kIdleAnimSetA;
            break;

        case kSpice: {
            pBlock->mState_000 = kLook1;
            const u32 nRoll = gRandom_1601760.RandomUint32Uniform(8);
            if (bLookMode && nRoll < 2)
                nAnimId = kIdleAnimLook4;
            else if (bSocialMode && nRoll < 2)
                nAnimId = kIdleAnimLook8;
            else
                nAnimId = ((nRoll >= 4) ? kIdleAnimSpiceTailA : 0) + kIdleAnimSpiceBase;
            break;
        }

        case kSocial:
            pBlock->mState_000 = kLook2;
            switch (pCreature->mpSenses_0b20->mSocialKind_620) {
            case 0x22:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5e8) + kIdleAnimSocialBase22;
                break;
            case 0x23:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5f0) + kIdleAnimSocialBase23;
                break;
            case 0x24:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5ec) + kIdleAnimSocialBase24;
                break;
            case 0x25:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5e4) + kIdleAnimSocialBase25;
                break;
            default:
                return true;
            }
            break;

        default:
            return true;
        }
    } else {
        switch (pBlock->mState_000) {
        case kLook1:
            if (pCreature->mpSenses_0b20->mSocialTimer_5ac > 0.0f)
                pBlock->mState_000 = kSocial;
            else
                pBlock->mState_000 = kLook2;
            nAnimId = kIdleAnimSetB;
            break;

        case kLook2:
            pBlock->mState_000 = kSpice;
            nAnimId = kIdleAnimSetB;
            break;

        case kSpice: {
            pBlock->mState_000 = kLook1;
            const u32 nRoll = gRandom_1601760.RandomUint32Uniform(8);
            if (bLookMode && nRoll < 2)
                nAnimId = kIdleAnimLook4;
            else if (bSocialMode && nRoll < 2)
                nAnimId = kIdleAnimLook8;
            else
                nAnimId = ((nRoll >= 4) ? kIdleAnimSpiceTailB : 0) + kIdleAnimSpiceBase;
            break;
        }

        case kSocial:
            pBlock->mState_000 = kLook2;
            switch (pCreature->mpSenses_0b20->mSocialKind_620) {
            case 0x22:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5e8) + kIdleAnimSocialBase22;
                break;
            case 0x23:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5f0) + kIdleAnimSocialBase23;
                break;
            case 0x24:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5ec) + kIdleAnimSocialBase24;
                break;
            case 0x25:
                nAnimId = gRandom_1601760.RandomUint32Uniform(
                              pCreature->mpSenses_0b20->mAnimCount_5e4) + kIdleAnimSocialBase25;
                break;
            default:
                return true;
            }
            break;

        default:
            return true;
        }
    }

    // A random index that ran past the table leaves the sentinel behind.
    if (nAnimId == 0xffffffff)
        return true;

    // Prefer an animation aimed at the group partner when one is available.
    cSPCreatureBase* pPartner = FUN_00d7bcb0(pBlock, pGroup, pCreature);
    if (pPartner != 0 && pPartner->mpAnimOwner_0b54 != 0 && pPartner->mpSenses_0b20 != 0) {
        IntRange* pIds = FUN_004d9030(pPartner->mpAnimOwner_0b54);
        if (pIds->mpBegin_00 != pIds->mpEnd_04) {
            pIds = FUN_004d9030(pPartner->mpAnimOwner_0b54);
            const s32 nTargetId = *pIds->mpBegin_00;
            if (nTargetId != -1) {
                pBlock->mAnimHandle_010 = pCreature->PlayAnimationWithTarget(
                    nAnimId, &pPartner->mLocomotive_0c0, (u32)nTargetId, -1);
                return true;
            }
        }
    }

    pBlock->mAnimHandle_010 = pCreature->PlayAnimation(nAnimId, 1, -1);
    return true;
}

} // namespace SP
