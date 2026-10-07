// Slice s004da440: SP::cSpeciesArchetype::cSpeciesArchetype() (default constructor), 0x004DA440.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc: no EH frame although members have dtors).
//
// Retail layout (0x440 bytes; the dev PDB's SP::cSpeciesArchetype is 0x414 and orders some members differently):
// the debug-name string moved to +0, the PDB's int `type` after modelType is gone, one float (+0x328) and one int
// (+0x430) are new, and the sp_vector_allocator vectors are 0x14 bytes.  Member names follow the PDB in order;
// the ones marked "(retail, name guessed)" have no PDB counterpart.
#include "types.h"
#pragma pack(push, 4)

namespace SP {

struct cSPVector3
{
	float x, y, z;
	cSPVector3() {}
};

struct cSPVector2
{
	float x, y;
	cSPVector2(float _x, float _y) : x(_x), y(_y) {}
};

static const float kMaxFloat = 3.402823466e+38F;   // FLT_MAX (named constant: /Od copies it into the inline ctor's params)

extern wchar_t gEmptyWString[];                 // 0x01667BAC (eastl empty-string sentinel)

// eastl::allocator (4 bytes; inline empty constructor)
struct SpAllocatorTag { SpAllocatorTag() {} };
struct StringAllocator
{
	explicit StringAllocator(const SpAllocatorTag&) {}
	uint32_t mData;
};

// eastl::basic_string<wchar_t, eastl::allocator> (16 bytes)
struct WString
{
	wchar_t* mpBegin;
	wchar_t* mpEnd;
	wchar_t* mpCapacity;
	StringAllocator mAllocator;
	explicit WString(const SpAllocatorTag& tag) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(tag)
	{
		mpBegin = gEmptyWString;
		mpEnd = mpBegin;
		mpCapacity = mpBegin + 1;
	}
};

// eastl::sp_vector_allocator (8 bytes in retail); constructed out of line from an empty tag.
struct SpVectorAllocator
{
	SpVectorAllocator(const SpAllocatorTag& tag);   // 0x00429360
	uint32_t mData[2];
};

template <class T>
struct SpVector                                 // eastl::vector<T, eastl::sp_vector_allocator>, 0x14 bytes
{
	T* mpBegin;
	T* mpEnd;
	T* mpCapacity;
	SpVectorAllocator mAllocator;
	explicit SpVector(const SpAllocatorTag& tag) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(tag) {}
};

class cPropertyList;
template <class T>
struct AutoRefCount
{
	T* mpObject;
	AutoRefCount() : mpObject(0) {}
};

class cSpeciesArchetype
{
public:
	cSpeciesArchetype();

	WString debugName;                          // +0x00
	unsigned int archetypeID;                   // +0x10
	unsigned int archetypeQueryID;              // +0x14
	cSPVector3 costRange[2];                    // +0x18
	cSPVector3 baseGear[2];                     // +0x30
	cSPVector3 mass[2];                         // +0x48
	cSPVector3 height[2];                       // +0x60
	cSPVector3 health[2];                       // +0x78
	cSPVector3 cuteness[2];                     // +0x90
	cSPVector3 social[2];                       // +0xa8
	cSPVector3 totalSocial[2];                  // +0xc0
	cSPVector3 numGraspers[2];                  // +0xd8
	cSPVector3 carnivore[2];                    // +0xf0
	cSPVector3 herbivore[2];                    // +0x108
	cSPVector3 attack[2];                       // +0x120
	cSPVector3 totalAttack[2];                  // +0x138
	cSPVector3 meanLooking[2];                  // +0x150
	cSPVector3 numFeet[2];                      // +0x168
	cSPVector3 maxPartLevel[2];                 // +0x180
	cSPVector3 averagePartLevel[2];             // +0x198
	cSPVector3 biteCapRange[2];                 // +0x1b0
	cSPVector3 strikeCapRange[2];               // +0x1c8
	cSPVector3 chargeCapRange[2];               // +0x1e0
	cSPVector3 spitCapRange[2];                 // +0x1f8
	cSPVector3 singCapRange[2];                 // +0x210
	cSPVector3 danceCapRange[2];                // +0x228
	cSPVector3 gestureCapRange[2];              // +0x240
	cSPVector3 postureCapRange[2];              // +0x258
	cSPVector3 glideCapRange[2];                // +0x270
	cSPVector3 stealthCapRange[2];              // +0x288
	cSPVector3 sprintCapRange[2];               // +0x2a0
	cSPVector3 senseCapRange[2];                // +0x2b8 (retail, name guessed from the cheat's -senseCapRange)
	unsigned int modelType;                     // +0x2d0
	float slopeMin;                             // +0x2d4
	float slopeMax;                             // +0x2d8
	float slopeArea;                            // +0x2dc
	float altitudeMin;                          // +0x2e0
	float altitudeMax;                          // +0x2e4
	float waterDistanceMin;                     // +0x2e8
	float waterDistanceMax;                     // +0x2ec
	float numCreaturesMin;                      // +0x2f0
	float numCreaturesMax;                      // +0x2f4
	float creatureShortfallMin;                 // +0x2f8
	float creatureShortfallMax;                 // +0x2fc
	float numNestsMin;                          // +0x300
	float numNestsMax;                          // +0x304
	float exclusiveAreaRadiusGroupSmall;        // +0x308
	float exclusiveAreaRadiusGroupMedium;       // +0x30c
	float exclusiveAreaRadiusGroupLarge;        // +0x310
	float respawnRate;                          // +0x314
	cSPVector2 dnaPointsEvolutionThresholds;    // +0x318
	float evoPointsRewarded;                    // +0x320
	float evoPointsRewardedSocial;              // +0x324
	float evoPointsRewardedOther;               // +0x328 (retail, name guessed)
	int partUnlockLevelReward;                  // +0x32c
	int foodChainLevel;                         // +0x330
	bool bUseOrigin;                            // +0x334
	bool bAvatarRelative;                       // +0x335 (not initialized by the constructor)
	float scaleMultiplier;                      // +0x338
	float overrideHeight;                       // +0x33c
	float hitpointOverride;                     // +0x340
	float damageMultiplier;                     // +0x344
	float socialPower;                          // +0x348
	float baseSightRadius;                      // +0x34c
	float baseSightAngle;                       // +0x350
	float basePerceptionRadius;                 // +0x354
	float abilityPerceptionMultiplier;          // +0x358
	float territoryRadius;                      // +0x35c
	float percentGuards;                        // +0x360
	float percentBabies;                        // +0x364
	float foodValue;                            // +0x368
	int numGuardLocations;                      // +0x36c
	int guardsPerLocation;                      // +0x370
	cSPVector2 guardLocationRadiusRange;        // +0x374
	cSPVector2 guardPositionDurationRange;      // +0x37c
	float guardLocationAreaBuffer;              // +0x384
	bool bIsEpic;                               // +0x388
	bool bIsMiniBoss;                           // +0x389 (not initialized by the constructor)
	unsigned int defaultPersonality;            // +0x38c
	unsigned int initialAvatarRelationship;     // +0x390
	cSPVector2 groupSizeRange;                  // +0x394
	SpVector<float> originDistances;            // +0x39c
	SpVector<unsigned int> relatedArchetypes;   // +0x3b0
	SpVector<unsigned int> archetypeGenerations;   // +0x3c4
	int eggIndex;                               // +0x3d8
	SpVector<unsigned int> schedulerTemplates;  // +0x3dc
	int fightGroupSize;                         // +0x3f0
	int standardAttacksPerSpecial;              // +0x3f4
	int numInGroupToStartWithSpecial;           // +0x3f8
	int numToKillForFearfulRelationship;        // +0x3fc
	int numToKillForExtinction;                 // +0x400
	int numToImpressForCurious;                 // +0x404
	int numToImpressForFriendly;                // +0x408
	int numToImpressForBestFriends;             // +0x40c
	int relationshipCuriousReward;              // +0x410
	int relationshipFriendlyReward;             // +0x414
	int relationshipBestFriendsReward;          // +0x418
	int relationshipFearedReward;               // +0x41c
	int extinctionReward;                       // +0x420
	unsigned int numSocialProposals;            // +0x424
	float socialTimeBeforeDrain;                // +0x428
	float socialDrainRate;                      // +0x42c
	int socialProposalLimit;                    // +0x430 (retail, name guessed)
	float attacked_SpeciesHelpRadius;           // +0x434
	int attacked_MaxSpeciesToAlert;             // +0x438
	AutoRefCount<cPropertyList> mpPropertyList; // +0x43c
};

// @ 0x004DA440
cSpeciesArchetype::cSpeciesArchetype()
	: debugName(SpAllocatorTag())
	, archetypeID(0)
	, archetypeQueryID(0)
	, modelType(0)
	, slopeMin(0.0f)
	, slopeMax(0.0f)
	, slopeArea(0.0f)
	, altitudeMin(0.0f)
	, altitudeMax(0.0f)
	, waterDistanceMin(0.0f)
	, waterDistanceMax(0.0f)
	, numCreaturesMin(0.0f)
	, numCreaturesMax(0.0f)
	, creatureShortfallMin(0.0f)
	, creatureShortfallMax(0.0f)
	, numNestsMin(0.0f)
	, numNestsMax(0.0f)
	, exclusiveAreaRadiusGroupSmall(0.0f)
	, exclusiveAreaRadiusGroupMedium(0.0f)
	, exclusiveAreaRadiusGroupLarge(0.0f)
	, respawnRate(0.0f)
	, dnaPointsEvolutionThresholds(kMaxFloat, kMaxFloat)
	, evoPointsRewarded(0.0f)
	, evoPointsRewardedSocial(0.0f)
	, evoPointsRewardedOther(0.0f)
	, partUnlockLevelReward(-1)
	, foodChainLevel(0)
	, bUseOrigin(false)
	, scaleMultiplier(0.0f)
	, overrideHeight(0.0f)
	, hitpointOverride(0.0f)
	, damageMultiplier(0.0f)
	, socialPower(0.0f)
	, baseSightRadius(0.0f)
	, baseSightAngle(0.0f)
	, basePerceptionRadius(0.0f)
	, abilityPerceptionMultiplier(1.0f)
	, territoryRadius(1.0f)
	, percentGuards(1.0f)
	, percentBabies(1.0f)
	, foodValue(1.0f)
	, numGuardLocations(1)
	, guardsPerLocation(1)
	, guardLocationRadiusRange(10.0f, 15.0f)
	, guardPositionDurationRange(60.0f, 160.0f)
	, guardLocationAreaBuffer(1.25f)
	, bIsEpic(false)
	, defaultPersonality(0)
	, initialAvatarRelationship(0)
	, groupSizeRange(1.0f, 1.0f)
	, originDistances(SpAllocatorTag())
	, relatedArchetypes(SpAllocatorTag())
	, archetypeGenerations(SpAllocatorTag())
	, eggIndex(0)
	, schedulerTemplates(SpAllocatorTag())
	, fightGroupSize(4)
	, standardAttacksPerSpecial(2)
	, numInGroupToStartWithSpecial(0)
	, numToKillForFearfulRelationship(1)
	, numToKillForExtinction(5)
	, numToImpressForCurious(1)
	, numToImpressForFriendly(3)
	, numToImpressForBestFriends(6)
	, relationshipCuriousReward(0)
	, relationshipFriendlyReward(0)
	, relationshipBestFriendsReward(0)
	, relationshipFearedReward(0)
	, extinctionReward(0)
	, numSocialProposals(0)
	, socialTimeBeforeDrain(0.0f)
	, socialDrainRate(0.0f)
	, socialProposalLimit(1)
	, attacked_SpeciesHelpRadius(0.0f)
	, attacked_MaxSpeciesToAlert(0)
{
}

} // namespace SP
