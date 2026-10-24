// Slice s00d7d370 -- creature behaviour-tree leaves of SPBehaviorTree.obj dealing with "interactive
// ornaments" and the holding creature: ornament event SFX selection, the StayBetween steering
// action, the "can I hold this" predicates, the holding-creature decide node and the voice/holder
// accessors.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// ---------------------------------------------------------------------------------------------
// shared engine shapes
// ---------------------------------------------------------------------------------------------
struct IVtbl {
    virtual void v00();
};

struct IPosition {
    virtual void* v00();                               // +0x00
    virtual float* GetPosition();                      // +0x04 ... retail uses +0x2c
};

typedef char VPadHelper;

struct IPositionVtbl {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28();
    virtual float* GetPosition();                      // +0x2c
    virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3c();
    virtual void p40(); virtual void p44(); virtual void p48(); virtual void p4c();
    virtual void p50(); virtual void p54(); virtual void p58(); virtual void p5c();
    virtual void p60(); virtual void p64(); virtual void p68(); virtual void p6c();
    virtual void p70();
    virtual float GetRadius();                         // +0x74
};

struct cLocation {
    IPositionVtbl* mpVtbl;                             // +0x00
};

// a creature / game object with the shared layout used by the behaviour leaves
struct cCreatureBase {
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
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void v170(); virtual void v174(); virtual void v178(); virtual void v17c();
    virtual void v180(); virtual void v184(); virtual void v188(); virtual void v18c();
    virtual void v190(); virtual void v194(); virtual void v198(); virtual void v19c();
    virtual void v1a0(); virtual void v1a4(); virtual void v1a8(); virtual void v1ac();
    virtual void v1b0(); virtual void v1b4(); virtual void v1b8(); virtual void v1bc();
    virtual void v1c0(); virtual void v1c4(); virtual void v1c8(); virtual void v1cc();
    virtual void v1d0(); virtual void v1d4(); virtual void v1d8(); virtual void v1dc();
    virtual void v1e0(); virtual void v1e4(); virtual void v1e8(); virtual void v1ec();
    virtual void v1f0(); virtual void v1f4(); virtual void v1f8(); virtual void v1fc();
    virtual void v200(); virtual void v204();
    virtual void* QueryInterface(uint32_t iid);        // +0x208 (slot 0x5c region used by callers)

    uint8_t     pad000[0xb20];                         // +0x000
    int32_t     mId;                                   // +0xb20
    uint8_t     padb24[0x4];                           // +0xb24
    uint8_t     mHoldingState[0xb28 - 0xb24];          // +0xb28 shared holding block
    uint8_t     padb4c[0xb4c - 0xb28];                 // +0xb4c
    cLocation*  mpLocomotive;                          // +0xb4c
    cCreatureBase* mpHolder;                           // +0xb50
    uint8_t     padb54[0x4];                           // +0xb54
    int32_t     mpOrnamentData;                        // +0xb54
    uint32_t    mFlags58;                              // +0xb58
    uint8_t     padb5c[0xb5e - 0xb5c];                 // +0xb5e
    uint8_t     mbDead;                                // +0xb5e
    cLocation*  mpPosition;                            // +0xc0
    uint8_t     padc4[0x1004 - 0xc4];                  // +0x1004
    void*       mpTarget;                              // +0x1004

    // called on the sub-object at +0xb4c (the locomotion component)
    uint32_t PlayIdleAnimation(uint32_t anim, int mode);
};

// ---------------------------------------------------------------------------------------------
// behaviour-tree stimulation record
// ---------------------------------------------------------------------------------------------
struct behavior_stimuli {
    uint8_t  pad00[0x0c];
    float    mDirectionX;                              // +0x0c
    float    mDirectionY;                              // +0x10
    float    mDirectionZ;                              // +0x14
    float    mRadius;                                   // +0x18
    uint8_t  pad1c[0x4];
    uint8_t  mPointers[8];                             // +0x20 (pointer array: [3] and [4] used)

    void GetAny(void* pOther);
};

// ---------------------------------------------------------------------------------------------
// engine entry points
// ---------------------------------------------------------------------------------------------
float    __cdecl GravityRadius();                       // DAT_01582e04
float    __cdecl InteractionRadius();                   // DAT_01582f90
int      __cdecl FUN_00c0f510(uint32_t index);
bool     __cdecl FUN_00d7d020(cCreatureBase* pCreature); // declared below
void*    __cdecl NounManager();                          // 0x00c04590
void*    __cdecl FUN_00b23a40(void* pManager);
void*    __cdecl FUN_00989360();
void*    __cdecl FUN_00c04590();
void*    __cdecl FUN_00c6acc0();
void*    __cdecl GetPlayerEmpireUniverse();
void*    __cdecl FUN_004df420();
void     __cdecl FUN_00401090();
void*    __cdecl FUN_00d99420(void* pBlock, int kind);
void*    __cdecl FUN_00d99500(void* pInterface);
void*    __cdecl FUN_00d99470(void* pInterface);
void     __cdecl FUN_00b3d4c0(void* pBlock, void* pSelf, void* pOther);
int      __cdecl FUN_00ba3f90(void* pBlock, void* pSelf, void* pOther);
void     __cdecl FUN_00c0b9d0(void* pAnim);
bool     __cdecl FUN_00c0b770();
void     __cdecl FUN_00c0ee60();
void*    __cdecl FUN_00c0ee90();
void     __cdecl FUN_00c0f780();
void*    __cdecl FUN_00c0f8a0(void* p);
void*    __cdecl FUN_00c0f780b();
void*    __cdecl PlanetModel();
void*    __cdecl DirectionToSurfacePosition();
void*    __cdecl FUN_00436ce0(void* a, void* b);
void     __cdecl MoveToPointAtSpeed(cCreatureBase* pCreature, int mode, float* pPos, float speed, float turn);
void*    __cdecl WatchMemoryBlock(uint32_t id);
extern uint8_t gLastAnimationBlock[];                    // 0x01687a0c

struct cCommunity {
    void* GetLeader();
};

struct cGameNounManager {
    void* GetAvatar();
};

template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vp() {} };
template <class B> struct VPad<0, B> : B {};
struct IEmpty {};

struct ICombatant : VPad<46, IEmpty> {               // slot +0xb8 queries the creature interface
    virtual void* QueryInterface(uint32_t iid);      // +0xb8
};

struct cCombatantList {
    uint32_t     FindFirstValid();                    // 0x00c0f780
    ICombatant*  GetAt(uint32_t index);               // 0x00c0f8a0
    float        FUN_00d7dca0();                      // @0xd7dca0
};

} // namespace SP

using namespace SP;

namespace SP {
namespace {

// ---------------------------------------------------------------------------------------------
// @ 0xd7d540 StayBetween
// ---------------------------------------------------------------------------------------------
void StayBetween(cCreatureBase* pCreature, float distance, int* pFrom, int* pTo)
{
    cCommunity* pCommunity = (cCommunity*)FUN_00b23a40(NounManager());
    if (!pCommunity)
        return;
    cCreatureBase* pLeader = (cCreatureBase*)pCommunity->GetLeader();
    if (!pLeader || pLeader->mbDead)
        return;

    float* pLeaderPos = pLeader->mpPosition->mpVtbl->GetPosition();
    float* pSelfPos = pCreature->mpPosition->mpVtbl->GetPosition();
    float dx = pSelfPos[0] - pLeaderPos[0];
    float dy = pSelfPos[1] - pLeaderPos[1];
    float dz = pSelfPos[2] - pLeaderPos[2];
    float dist = dx * dx + dy * dy + dz * dz;
    if (distance * distance < dist)
        return;

    float target[3];
    target[0] = pLeaderPos[0];
    target[1] = pLeaderPos[1];
    target[2] = pLeaderPos[2];
    FUN_00436ce0(target, target);
    MoveToPointAtSpeed(pCreature, 2, target, 1.0f, 2.0f);
}

} // anonymous namespace
} // namespace SP

namespace SP {

// ---------------------------------------------------------------------------------------------
// @ 0xd7d370 FUN_00d7d370
// ---------------------------------------------------------------------------------------------
uint32_t __cdecl FUN_00d7d370(cCreatureBase* pCreature, float* pPosition)
{
    uint32_t best = 0xffffffff;
    float bestDistance = 3.402823466e+38f;

    int count = (int)((char*)pCreature->mpHolder - (char*)pCreature->mHoldingState) / 0x24;
    for (int i = 0; i < count; ++i) {
        if (!FUN_00c0f510((uint32_t)i))
            continue;
        float position[3];
        uint32_t part = pCreature->PlayIdleAnimation(0, i);
        float dx = position[0] - pPosition[0];
        float dy = position[1] - pPosition[1];
        float dz = position[2] - pPosition[2];
        float distance = dx * dx + dy * dy + dz * dz;
        if (distance < bestDistance) {
            bestDistance = distance;
            best = part;
        }
    }
    return best;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7d4a0 SP::ManageInteractiveOrnamentEventSFX
// ---------------------------------------------------------------------------------------------
void __cdecl ManageInteractiveOrnamentEventSFX(int* pEvent, uint8_t* pObject)
{
    if (!pEvent || !pObject)
        return;
    int32_t* pData = *(int32_t**)(pObject + 0xb54);
    if (!pData)
        return;

    switch (pEvent[0x110 / 4]) {
    case 1:
        pData[0x170 / 4] = 0x72776c66;
        return;
    case 2:
        pData[0x170 / 4] = 0x656e6f62;
        return;
    case 3:
        pData[0x170 / 4] = 0x6b697473;
        return;
    case 4:
        pData[0x170 / 4] = 0x69757266;
        return;
    case 5:
        pData[0x170 / 4] = 0x6b636f72;
        return;
    case 6:
        pData[0x170 / 4] = 0x6c6c6873;
        return;
    default:
        pData[0x170 / 4] = 0x746c6664;
        return;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7d720 FUN_00d7d720
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7d720(cCreatureBase* pCreature)
{
    if (FUN_00d7d020(pCreature))
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7d740 FUN_00d7d740
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7d740(int* pCreature, behavior_stimuli* pStimuli)
{
    cCommunity* pCommunity = (cCommunity*)FUN_00b23a40(NounManager());
    if (!pCommunity)
        return 0.0f;

    cCreatureBase* pLeader = (cCreatureBase*)pCommunity->GetLeader();
    if (!pLeader || pLeader->mbDead)
        return 0.0f;

    float radius = GravityRadius();
    float* pLeaderPos = pLeader->mpPosition->mpVtbl->GetPosition();
    float* pSelfPos = ((cCreatureBase*)pCreature)->mpPosition->mpVtbl->GetPosition();
    float dx = pSelfPos[0] - pLeaderPos[0];
    float dy = pSelfPos[1] - pLeaderPos[1];
    float dz = pSelfPos[2] - pLeaderPos[2];
    if (!(radius * radius < dx * dx + dy * dy + dz * dz))
        return 0.0f;

    if (pStimuli) {
        pStimuli->GetAny(pCreature);
        *((float*)pStimuli->mPointers + 3) = radius * 0.5f;
        *((int*)pStimuli->mPointers + 4) = 0;
    }
    return 1.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7d840 FUN_00d7d840
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7d840(cCreatureBase* pCreature)
{
    if (!pCreature->mpTarget)
        return 0.0f;

    cLocation* pLocation = pCreature->mpPosition;
    float radius = pLocation->mpVtbl->GetRadius();
    void* pOwner = NounManager();
    cCreatureBase* pHolder = (cCreatureBase*)pOwner;
    if (pOwner && *(void**)((char*)pOwner + 0x160) != 0) {
        void* pBlock = *(void**)((char*)pOwner + 0x160);
        radius = radius + (*(IPositionVtbl**)((char*)pBlock + 0x34))->GetRadius();
    }
    float* pTarget = (float*)FUN_00c6acc0();
    float* pSelf = pLocation->mpVtbl->GetPosition();
    float dx = pSelf[0] - pTarget[0];
    float dy = pSelf[1] - pTarget[1];
    float dz = pSelf[2] - pTarget[2];
    return (dx * dx + dy * dy + dz * dz < radius * radius) ? 1.0f : 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7d910 FUN_00d7d910
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7d910(int* pCreature)
{
    uint32_t id = ((cCreatureBase*)((char*)*(int**)((char*)pCreature + 0xb4c) + 8))->PlayIdleAnimation(0x40000, 0);
    cCreatureBase* pAnim = (cCreatureBase*)WatchMemoryBlock(id);
    if (pAnim && ((pAnim->mFlags58 >> 9) & 1) != 0 && pAnim->mId != pCreature[0xb20 / 4] &&
        (pAnim->mpHolder == 0 || pAnim->mpHolder == (cCreatureBase*)pCreature)) {
        FUN_00c0b9d0(gLastAnimationBlock);
        return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7d980 FUN_00d7d980
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7d980(cCreatureBase* pCreature, int mode, int arg3, uint32_t flags,
                           behavior_stimuli* pStimuli, void* pContext)
{
    if (flags & 0x1000)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    NounManager();
    void* pObject = FUN_00989360();
    if (!pObject)
        return 0.0f;

    float* pOther = (float*)FUN_00c6acc0();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    float radius = InteractionRadius();
    if (!(dx * dx + dy * dy + dz * dz < radius * radius))
        return 0.0f;

    uint32_t id = ((cCreatureBase*)((char*)*(int**)((char*)pCreature + 0xb4c) + 8))->PlayIdleAnimation(0x400, 0);
    cCreatureBase* pAnim = (cCreatureBase*)WatchMemoryBlock(id);
    if (!pAnim || ((pAnim->mFlags58 >> 9) & 1) == 0)
        return 0.0f;

    FUN_00c0ee60();
    return 1.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7da70 SP::HOLDING_CREATURE_Decide
// ---------------------------------------------------------------------------------------------
float __cdecl HOLDING_CREATURE_Decide(int* pCreature)
{
    int* pBlock = (int*)FUN_00d99420((char*)*(int**)((char*)pCreature + 0xb4c) + 0x1d0, 0);
    void* pInterface = 0;
    if (pBlock && *pBlock)
        pInterface = *(void**)*pBlock;

    cCreatureBase* pTarget = (cCreatureBase*)FUN_00d99500(pInterface);
    if (!pTarget)
        return 0.0f;

    FUN_00401090();
    void* pPlayerProfile = FUN_004df420();
    if ((void*)pTarget->mId != pPlayerProfile)
        return 0.0f;
    if (!FUN_00c0b770())
        return 0.0f;

    void* pHolding = (char*)pCreature + 0xb28;
    FUN_00b3d4c0(pHolding, pCreature, pTarget);
    int result = FUN_00ba3f90(pHolding, pCreature, pTarget);
    if (result != 2 && result != 5)
        return 0.0f;

    return 1.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7db30 FUN_00d7db30
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7db30(int* pCreature)
{
    cGameNounManager* pManager = (cGameNounManager*)NounManager();
    void* pAvatar = pManager->GetAvatar();
    cCreatureBase* pTarget = (cCreatureBase*)FUN_00d99500(pAvatar);
    if (!pTarget || pTarget->mbDead)
        return 0.0f;

    void* pOwner = FUN_00c04590();
    void* pBlock = *(void**)((char*)pOwner + 0x160);
    if (!pBlock)
        return 0.0f;
    int32_t kind = *(int32_t*)((char*)pTarget->mpLocomotive + 0x1d8);
    if (kind != 0x2d852f0 && kind != (int32_t)0xd23fe7cau)
        return 0.0f;

    float radius = (*(IPositionVtbl**)((char*)pBlock + 0x34))->GetRadius();
    float* pSelf = pTarget->mpPosition->mpVtbl->GetPosition();
    float* pOther = (float*)FUN_00c6acc0();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    radius = pTarget->mpPosition->mpVtbl->GetRadius();
    return (dx * dx + dy * dy + dz * dz < radius * radius) ? 1.0f : 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7dca0 FUN_00d7dca0
// ---------------------------------------------------------------------------------------------
float cCombatantList::FUN_00d7dca0()
{
    ICombatant* pCombatant = GetAt(FindFirstValid());
    if (!pCombatant)
        return 0.0f;
    if (pCombatant->QueryInterface(0xce9f6639))
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7dd00 FUN_00d7dd00
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7dd00(cCreatureBase* pCreature)
{
    void* pOwner = FUN_00c04590();
    float limit = *(float*)((char*)pOwner + 0x108);
    if (((pCreature->mFlags58 >> 8) & 1) != 0 || !(0.0f < limit))
        return 0.0f;

    float* pOther = (float*)FUN_00c6acc0();
    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    if (!(limit * limit < dx * dx + dy * dy + dz * dz))
        return 0.0f;

    cCreatureBase* pAnim = (cCreatureBase*)FUN_00c0ee90();
    if (!pAnim || ((pAnim->mFlags58 >> 9) & 1) == 0)
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7ddd0 FUN_00d7ddd0
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7ddd0(cCreatureBase* pCreature)
{
    uint32_t id = ((cCreatureBase*)((char*)*(int**)((char*)pCreature + 0xb4c) + 8))->PlayIdleAnimation(0x2000000, 0);
    behavior_stimuli* pStimuli = (behavior_stimuli*)WatchMemoryBlock(id);
    cCreatureBase* pAnim = (cCreatureBase*)FUN_00d99470(pStimuli);
    if (!pAnim || pAnim == pCreature)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float dx = pStimuli->mDirectionX - pSelf[0];
    float dy = pStimuli->mDirectionY - pSelf[1];
    float dz = pStimuli->mDirectionZ - pSelf[2];
    float radius = pCreature->mpPosition->mpVtbl->GetRadius() + pStimuli->mRadius;
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7df00 FUN_00d7df00
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7df00(cCreatureBase* pCreature, int* pContext)
{
    if (!pCreature || pCreature->mbDead)
        return 0.0f;
    cCreatureBase* pHolder = pCreature->mpHolder;
    if (!pHolder || pHolder == pCreature)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float* pOther = pHolder->mpPosition->mpVtbl->GetPosition();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    float radius = pCreature->mpPosition->mpVtbl->GetRadius() + pHolder->mpPosition->mpVtbl->GetRadius();
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0xd7e090 FUN_00d7e090
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d7e090(cCreatureBase* pCreature, int* pContext)
{
    if (!pCreature || pCreature->mbDead)
        return 0.0f;
    cCreatureBase* pTarget = pCreature->mpHolder;
    if (!pTarget || pTarget == pCreature)
        return 0.0f;
    if (pCreature->mId == pTarget->mId)
        return 0.0f;

    float* pSelf = pCreature->mpPosition->mpVtbl->GetPosition();
    float* pOther = pTarget->mpPosition->mpVtbl->GetPosition();
    float dx = pSelf[0] - pOther[0];
    float dy = pSelf[1] - pOther[1];
    float dz = pSelf[2] - pOther[2];
    float radius = pCreature->mpPosition->mpVtbl->GetRadius();
    if (dx * dx + dy * dy + dz * dz < radius * radius)
        return 1.0f;
    return 0.0f;
}

} // namespace SP
