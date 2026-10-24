// Slice s00c1e460 -- SP::cSPCreatureBase::Attack (0x00c1e460, 742 bytes).
// Picks the animation for the attack/tool the caller asked for and hands it to the animation
// system: the ability record (vtable slot 0xb4, GetAbility) decides between the "rush" setup
// (range at +0xf4 with a dedicated anim at +0xf8), a distance test against the target for
// ability kind 0x2b, or a random animation out of the ability's anim-id list at +0x48 (with an
// override hook at +0xe84). Target-kind dependent anims (tribe tool / hut) are picked up
// afterwards, and for kinds 0x1e/0x21 a variant id is rolled from the species' anim list or an
// animation context-target query; the resulting animation id is returned through the out
// parameter while the ability index itself is returned (after cancelling the attack animation).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
#include "types.h"
#include <stddef.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define CHECK_OFFSET(T, m, off) typedef char PVCAT(check_, __COUNTER__)[offsetof(T, m) == (off) ? 1 : -1]

extern const float kZero;    // 0x01485378 (0.0f)
extern float g_1582ef0;      // 0x01582ef0 (attack range slack)
extern float g_1582ef4;      // 0x01582ef4

float __cdecl FUN_00d38a30(int nWhich, void* pCreature);            // 0x00d38a30
float __cdecl FUN_00d99ac0(void* pA, void* pB, bool bFlags);        // 0x00d99ac0 (distance)
extern "C" unsigned int FUN_00c0b380(void* pCreature, void* pAbility);   // 0x00c0b380

// Animation context-target query: fills pOut with up to nMax noun ids of the records that match
// the 16-byte query record, returns how many were written.
extern "C" int FUN_009b2340(void* pOut, int nMax, unsigned int nModel, void* pRecord,
                            int nA, int nB);                        // 0x009b2340

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t nLimit);                  // 0x00a68fb0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;            // 0x01601760

// Four-character animation result tags / noun ids reached through the target.
enum {
    kNounTribeTool = 0x018c8f0c,
    kNounTribeHut  = 0x01e4daae,
};

enum {
    kAnimNone = 0x02c39370,
};

struct cIdVector {
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    int* mpCapacity;   // +0x08
};

// 16-byte animation context query record handed to EvaluateContextTargetQuery.
struct ContextQueryRecord {
    unsigned int mKind;      // +0x00
    unsigned int mTag;       // +0x04
    unsigned int mField08;   // +0x08
    unsigned int mField0c;   // +0x0c
};

class cGameData {
public:
    PV8
    virtual uint32_t GetNounID();                                   // 0x20
};

// The spatial/locomotive sub-object living at +0xc0 of a creature.
class cSpatialObject {
public:
    PV16 PV2
    virtual bool CanAttack();                                       // 0x48
};

// Target interface held at +0xe7c.
class IQueryTarget {
public:
    PV2
    virtual void* ToSpatialObject();                                // 0x08
    virtual cGameData* ToGameData();                                // 0x0c
    PV16 PV2 PV
    virtual void* Query(unsigned int nID);                          // 0x5c
};

// Animated-creature payload at +0xb54 (only the model pointer is needed here).
class cAnimatedCreature {
public:
    char pad00[0x17c];
    void* mpModel;     // +0x17c
};

// The per-frame ability record returned by GetAbility() (vtable slot 0xb4).
class cCreatureAbility {
public:
    unsigned int GetAnimationID(unsigned int nIndex);               // 0x004d3cd0
    /* +0x00 */ char pad00[8];
    /* +0x08 */ int mType;
    /* +0x0c */ char pad0c[0x48 - 0x0c];
    /* +0x48 */ cIdVector mAnimIds;
    /* +0x54 */ char pad54[0x78 - 0x54];
    /* +0x78 */ unsigned int mTribeAnimationID;
    /* +0x7c */ char pad7c[0xa8 - 0x7c];
    /* +0xa8 */ float mRangeA8;
    /* +0xac */ char padac[0xf4 - 0xac];
    /* +0xf4 */ float mRangeF4;
    /* +0xf8 */ unsigned int mAnimationID;
    /* +0xfc */ char padfc[0x100 - 0xfc];
    /* +0x100 */ unsigned char mbFlags100;
};
CHECK_OFFSET(cCreatureAbility, mType, 0x08);
CHECK_OFFSET(cCreatureAbility, mAnimIds, 0x48);
CHECK_OFFSET(cCreatureAbility, mRangeA8, 0xa8);
CHECK_OFFSET(cCreatureAbility, mRangeF4, 0xf4);
CHECK_OFFSET(cCreatureAbility, mAnimationID, 0xf8);
CHECK_OFFSET(cCreatureAbility, mbFlags100, 0x100);

// Ability override record (kept at +0xe84).
class cAbilityOverride {
public:
    char pad00[0x388];
    unsigned char mbFlags388;   // +0x388
};

class SpeciesData {
public:
    cIdVector* GetAnimationList(void* pAnimContext);                 // 0x004d9030
};

namespace SP {

class cSPCreatureBase {
public:
    PV16 PV16 PV8 PV4
    virtual int GetAbilitiesCount();                                          // 0xb0
    virtual cCreatureAbility* GetAbility(int nIndex);                         // 0xb4

    int  BeginAttack(unsigned int nIndex, bool bA, bool bB);                  // 0x00c196a0
    void CancelAttackAnimation(int nIndex);                                   // 0x00c073a0
    unsigned int InterruptAnimation(unsigned int nAnimationID, int nA, int nB);   // 0x00c12310
    unsigned int InterruptAnimationWithTarget(unsigned int nAnimationID, void* pTarget,
                                              int nA, int nB);                // 0x00c149c0

    /* +0x000 */ char pad000[0xc0 - 0x04];
    /* +0x0c0 */ cSpatialObject mBody;
    /* +0x0c4 */ char pad0c4[0xb20 - 0x0c4];
    /* +0xb20 */ SpeciesData* mpSpecies;
    /* +0xb24 */ char pad0b24[0xb4c - 0xb24];
    /* +0xb4c */ void* mpBehaviorData;
    /* +0xb50 */ char pad0b50[4];
    /* +0xb54 */ cAnimatedCreature* mpAnimatedCreature;
    /* +0xb58 */ unsigned int mGeneralFlags;
    /* +0xb5c */ unsigned char mbFlags5c;
    /* +0xb5d */ char pad0b5d[0xe7c - 0xb5d];
    /* +0xe7c */ IQueryTarget* mpTargetHolder;
    /* +0xe80 */ char pad0e80[0xe84 - 0xe80];
    /* +0xe84 */ cAbilityOverride* mpOverride;
    /* +0xe88 */ char pad0e88[0xe8c - 0xe88];
    /* +0xe8c */ unsigned int mCurrentAttackIdx;
    /* +0xe90 */ unsigned int mCurrentAttackAnimId;
    /* +0xe94 */ float mRushDistanceLeft;
    /* +0xe98 */ char pad0e98[0xeac - 0xe98];
    /* +0xeac */ int mAttackState;

    unsigned int Attack(unsigned int nAttackIndex, unsigned int* pnAnimationID);
};
CHECK_OFFSET(cSPCreatureBase, mBody, 0xc0);
CHECK_OFFSET(cSPCreatureBase, mpSpecies, 0xb20);
CHECK_OFFSET(cSPCreatureBase, mpAnimatedCreature, 0xb54);
CHECK_OFFSET(cSPCreatureBase, mbFlags5c, 0xb5c);
CHECK_OFFSET(cSPCreatureBase, mpTargetHolder, 0xe7c);
CHECK_OFFSET(cSPCreatureBase, mpOverride, 0xe84);
CHECK_OFFSET(cSPCreatureBase, mCurrentAttackAnimId, 0xe90);
CHECK_OFFSET(cSPCreatureBase, mRushDistanceLeft, 0xe94);
CHECK_OFFSET(cSPCreatureBase, mAttackState, 0xeac);

// @ 0x00c1e460
unsigned int cSPCreatureBase::Attack(unsigned int nAttackIndex, unsigned int* pnAnimationID)
{
    unsigned int nAbilityIndex = BeginAttack(nAttackIndex, true, false);
    if (nAbilityIndex != (unsigned int)-1) {
        int nVariant;
        IQueryTarget* pTarget = mpTargetHolder;
        cCreatureAbility* pAbility = GetAbility(nAbilityIndex);

        if (pAbility->mRangeF4 > kZero && pAbility->mAnimationID != (unsigned int)-1) {
            mCurrentAttackAnimId = pAbility->mAnimationID;
            float fScale = FUN_00d38a30(0, this);
            mRushDistanceLeft = (pAbility->mRangeA8 + pAbility->mRangeF4) * fScale;
            mRushDistanceLeft += g_1582ef0;
            mRushDistanceLeft += g_1582ef4;
            mbFlags5c = pAbility->mbFlags100;
        } else if (pAbility->mType == 0x2b) {
            if (pTarget == NULL)
                goto done;
            {
                void* pSpatial = pTarget->ToSpatialObject();
                float fDistance = FUN_00d99ac0(&mBody, pSpatial, true);
                if (FUN_00d38a30(0, this) * pAbility->mRangeF4 < fDistance) {
                    mCurrentAttackAnimId = kAnimNone;
                    goto done;
                }
            }
            {
                unsigned int nCount =
                    (unsigned int)(pAbility->mAnimIds.mpEnd - pAbility->mAnimIds.mpBegin);
                if (nCount > 0) {
                    unsigned int nIndex = sMathRandom.RandomUint32Uniform(nCount);
                    mCurrentAttackAnimId = pAbility->GetAnimationID(nIndex);
                } else {
                    unsigned int nIndex = 0;
                    mCurrentAttackAnimId = pAbility->GetAnimationID(nIndex);
                }
            }
        } else {
            if (mpOverride != NULL && mpOverride->mbFlags388 != 0) {
                mCurrentAttackAnimId = FUN_00c0b380(this, pAbility);
                goto done;
            }
            {
                unsigned int nCount =
                    (unsigned int)(pAbility->mAnimIds.mpEnd - pAbility->mAnimIds.mpBegin);
                unsigned int nIndex = (nCount > 0) ? sMathRandom.RandomUint32Uniform(nCount) : 0;
                mCurrentAttackAnimId = pAbility->GetAnimationID(nIndex);
            }
            if (pTarget == NULL)
                goto done;
        }
        {
            cGameData* pGameData = pTarget->ToGameData();
            unsigned int nNounID = pGameData->GetNounID();
            if ((nNounID == kNounTribeTool || nNounID == kNounTribeHut)
                && pAbility->mTribeAnimationID != 0)
                mCurrentAttackAnimId = pAbility->mTribeAnimationID;
        }

    done:
        {
            nVariant = -1;
            if (mBody.CanAttack() && mAttackState == 2) {
                int nType = pAbility->mType;
                switch (nType) {
                case 0x1e: {
                    cIdVector* pAnimList = mpSpecies->GetAnimationList(mpAnimatedCreature);
                    unsigned int nCount =
                        (unsigned int)(pAnimList->mpEnd - pAnimList->mpBegin);
                    nVariant = pAnimList->mpBegin[sMathRandom.RandomUint32Uniform(nCount)];
                    break;
                }
                case 0x21: {
                    unsigned int aResults[0xff];
                    ContextQueryRecord record = { 0, 0x73726b73, 0, 0 };
                    unsigned int nFound = FUN_009b2340(aResults, 0xff,
                                                       *(unsigned int*)mpAnimatedCreature->mpModel,
                                                       &record, 0, 0);
                    if (nFound > 0)
                        nVariant = aResults[sMathRandom.RandomUint32Uniform(nFound)];
                    break;
                }
                }
            }

            unsigned int nResult;
            void* pQueryResult = (pTarget != NULL) ? pTarget->Query(0x1186577) : NULL;
            if (pQueryResult != NULL)
                nResult = InterruptAnimationWithTarget(mCurrentAttackAnimId, pQueryResult, -1, nVariant);
            else
                nResult = InterruptAnimation(mCurrentAttackAnimId, nVariant, 0);

            if (pnAnimationID != NULL)
                *pnAnimationID = nResult;
            CancelAttackAnimation(nAbilityIndex);
        }
    }
    return nAbilityIndex;
}

}  // namespace SP
