// Slice s004e1cb0 -- SP::cSpeciesArchetype implicit copy constructor (4711 bytes, /Od).
//
// Flags: /Od /Ob1 /MD /Gy /TP (no /arch:SSE: float members copy with fld/fstp; no /EHsc:
// no EH frame although string/vector members have dtors).
//
// Layout: dev-PDB SP::cSpeciesArchetype (size 0x414), adjusted to the retail binary (size
// 0x440): debugName moved to the front, one more Vector3 range (29), `type`/bAvatarRelative
// dropped, one float and one int added. Members the PDB doesn't name keep offset names.
// The constructor itself is compiler-generated: member arrays of cSPVector3 copy through
// the out-of-line cSPVector3 copy ctor (0x4098a0) in "count = 2; while (--count >= 0)"
// loops, cSPVector2 copies inline, the vectors through their copy ctor (0x50d440) and
// mpPropertyList AddRefs (vtable slot 0).

#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

namespace eastl {

struct allocator {
    allocator() {}
    allocator(const allocator&) {}
};

template <typename T>
struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;  // empty; padded to 4 (string is 16 bytes)


    basic_string(const basic_string& x)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator)
    {
        RangeInitialize(x.mpBegin, x.mpEnd);
    }
    ~basic_string();
    void RangeInitialize(const T* pBegin, const T* pEnd);  // 0x423820
};

struct sp_vector_allocator {
    uint32_t a;
    uint32_t b;
};

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    vector(const vector& x);  // 0x50d440 (identical instances folded)
    ~vector();
};

} // namespace eastl

struct cSPVector3 {
    float x, y, z;
    cSPVector3(const cSPVector3& v);  // 0x4098a0, out of line
};

struct cSPVector2 {
    float x, y;
    cSPVector2(const cSPVector2& v) : x(v.x), y(v.y) {}
};

namespace SP {

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
};

} // namespace SP

namespace EA {

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount();
};

} // namespace EA

namespace SP {

struct cSpeciesArchetype {
    eastl::basic_string<wchar_t> debugName;  // +0x0
    uint32_t archetypeID;                    // +0x10
    uint32_t archetypeQueryID;               // +0x14
    cSPVector3 costRange[2];                 // +0x18
    cSPVector3 baseGear[2];
    cSPVector3 mass[2];
    cSPVector3 height[2];
    cSPVector3 health[2];
    cSPVector3 cuteness[2];
    cSPVector3 social[2];
    cSPVector3 totalSocial[2];
    cSPVector3 numGraspers[2];
    cSPVector3 carnivore[2];
    cSPVector3 herbivore[2];
    cSPVector3 attack[2];
    cSPVector3 totalAttack[2];
    cSPVector3 meanLooking[2];
    cSPVector3 numFeet[2];
    cSPVector3 maxPartLevel[2];
    cSPVector3 averagePartLevel[2];
    cSPVector3 biteCapRange[2];
    cSPVector3 strikeCapRange[2];
    cSPVector3 chargeCapRange[2];
    cSPVector3 spitCapRange[2];
    cSPVector3 singCapRange[2];
    cSPVector3 danceCapRange[2];
    cSPVector3 gestureCapRange[2];
    cSPVector3 postureCapRange[2];
    cSPVector3 glideCapRange[2];
    cSPVector3 stealthCapRange[2];
    cSPVector3 sprintCapRange[2];
    cSPVector3 range_2b8[2];                 // +0x2b8 (retail addition)
    uint32_t modelType;                      // +0x2d0
    float slopeMin;                          // +0x2d4
    float slopeMax;
    float slopeArea;
    float altitudeMin;
    float altitudeMax;
    float waterDistanceMin;
    float waterDistanceMax;
    float numCreaturesMin;
    float numCreaturesMax;
    float creatureShortfallMin;
    float creatureShortfallMax;
    float numNestsMin;
    float numNestsMax;
    float exclusiveAreaRadiusGroupSmall;
    float exclusiveAreaRadiusGroupMedium;
    float exclusiveAreaRadiusGroupLarge;
    float respawnRate;                       // +0x314
    cSPVector2 dnaPointsEvolutionThresholds; // +0x318
    float evoPointsRewarded;                 // +0x320
    float evoPointsRewardedSocial;           // +0x324
    float field_328;                         // +0x328
    int partUnlockLevelReward;               // +0x32c
    int foodChainLevel;                      // +0x330
    bool bUseOrigin;                         // +0x334
    float scaleMultiplier;                   // +0x338
    float overrideHeight;
    float hitpointOverride;
    float damageMultiplier;
    float socialPower;
    float baseSightRadius;
    float baseSightAngle;
    float basePerceptionRadius;
    float abilityPerceptionMultiplier;
    float territoryRadius;
    float percentGuards;
    float percentBabies;
    float foodValue;                         // +0x368
    int numGuardLocations;                   // +0x36c
    int guardsPerLocation;                   // +0x370
    cSPVector2 guardLocationRadiusRange;     // +0x374
    cSPVector2 guardPositionDurationRange;   // +0x37c
    float guardLocationAreaBuffer;           // +0x384
    bool bIsEpic;                            // +0x388
    bool bIsMiniBoss;                        // +0x389
    uint32_t defaultPersonality;             // +0x38c
    uint32_t initialAvatarRelationship;      // +0x390
    cSPVector2 groupSizeRange;               // +0x394
    eastl::vector<float> originDistances;            // +0x39c
    eastl::vector<uint32_t> relatedArchetypes;       // +0x3b0
    eastl::vector<uint32_t> archetypeGenerations;    // +0x3c4
    int eggIndex;                                    // +0x3d8
    eastl::vector<uint32_t> schedulerTemplates;      // +0x3dc
    int fightGroupSize;                      // +0x3f0
    int standardAttacksPerSpecial;
    int numInGroupToStartWithSpecial;
    int numToKillForFearfulRelationship;
    int numToKillForExtinction;
    int numToImpressForCurious;
    int numToImpressForFriendly;
    int numToImpressForBestFriends;
    int relationshipCuriousReward;
    int relationshipFriendlyReward;
    int relationshipBestFriendsReward;
    int relationshipFearedReward;
    int extinctionReward;
    uint32_t numSocialProposals;             // +0x424
    float socialTimeBeforeDrain;             // +0x428
    float socialDrainRate;                   // +0x42c
    int field_430;                           // +0x430
    float attacked_SpeciesHelpRadius;        // +0x434
    int attacked_MaxSpeciesToAlert;          // +0x438
    EA::AutoRefCount<cPropertyList> mpPropertyList;  // +0x43c

    // no user copy ctor: 0x4e1cb0 is the implicit one
};

} // namespace SP

// Uses the implicit copy ctor so cl emits it (at /Ob1 it stays out of line, as in the original).
void CopyArchetype_emit(SP::cSpeciesArchetype* dst, const SP::cSpeciesArchetype& src)
{
    new (dst) SP::cSpeciesArchetype(src);
}
