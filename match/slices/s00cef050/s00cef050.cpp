// Slice s00cef050: the single function in this slice is
//   0x00CEF050  SP::cCityGameTuning::Init   (7320 bytes, __thiscall, no stack args)
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Init() obtains the city-game tuning property list (group 0xB6A5C63D) from the
// global PropertyManager and copies ~124 named scalar properties into the
// members of cCityGameTuning (dev-PDB layout, size 0x214).  Most reads use the
// inlined helpers GetPropertyAsFloat/Int/UInt (PropertyList::GetProperty at
// slot +0x24, type tag at Property::mnType(+0x12)); a few use the free helpers
// GetPropertyAsVector3 (0x6A1110) and GetPropertyAsKeyInstance (0x6A12A0).
// Ten members are scaled by 1000.0f in place; two are read into an
// UNINITIALISED local float (the original falls back to stale stack on a failed
// lookup), scaled by 1000 and converted: +0x80 to unsigned (fistp qword) and
// +0x180 to int (cvttss2si).
//
// Complete: the read order, property ids, member offsets and helper kinds were
// checked against the disassembly one-for-one.  Not byte-exact: the original
// has an 8-byte-aligned frame (`and esp,-8`), which shifts every esp-relative
// slot by 4 bytes, so nearly every instruction differs in its displacement.
// NOTE: retail types differ from the PDB for several members (see comments).
#include "types.h"

namespace App {

struct Property {
    char     pad_0[0x12];
    uint16_t mnType;                 // +0x12
    float*   GetValueFloat();        // 0x0041EA70
    int*     GetValueInt32();        // 0x0041E990
    uint32_t* GetValueUInt32();      // 0x0041EA00
};

class PropertyList {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& pResult);   // +0x24
};

class PropertyManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual bool GetPropertyList(uint32_t groupID, PropertyList** ppList);   // +0x30
};

}  // namespace App

namespace SP {

class cPropertyList;   // (same object; using App::PropertyList below)

bool GetPropertyAsVector3(App::PropertyList* pList, uint32_t id, void* pValue);       // 0x006A1110
bool GetPropertyAsKeyInstance(App::PropertyList* pList, uint32_t id, uint32_t* pValue); // 0x006A12A0

inline bool GetPropertyAsFloat(App::PropertyList* pList, uint32_t id, float& value)
{
    App::Property* pProp;
    if (pList && pList->GetProperty(id, pProp) && pProp->mnType == 0xd) {
        value = *pProp->GetValueFloat();
        return true;
    }
    return false;
}

inline bool GetPropertyAsInt(App::PropertyList* pList, uint32_t id, int& value)
{
    App::Property* pProp;
    if (pList && pList->GetProperty(id, pProp) && pProp->mnType == 9) {
        value = *pProp->GetValueInt32();
        return true;
    }
    return false;
}

inline bool GetPropertyAsUInt(App::PropertyList* pList, uint32_t id, uint32_t& value)
{
    App::Property* pProp;
    if (pList && pList->GetProperty(id, pProp) && pProp->mnType == 0xa) {
        value = *pProp->GetValueUInt32();
        return true;
    }
    return false;
}

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPointerRef() {
        if (mpObject) { T* pTemp = mpObject; mpObject = 0; pTemp->Release(); }
        return &mpObject;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct cSPVector3 { float x, y, z; };

// Layout is tools/pdb_type.py cCityGameTuning (0x214), with member types taken
// from the disassembly where retail differs from the dev PDB.
class cCityGameTuning {
public:
    void Init();

    cSPVector3 kInitialCameraPolarCoords;        // +0x00
    int        kInitialWealth;                   // +0x0c
    int        kInitialCreatures;                // +0x10
    int        kInitialCreaturesPerTribe;        // +0x14
    int        kInitialTribes;                   // +0x18
    float      kCityHallMoney;                   // +0x1c
    float      kCityHallMoneyTime;               // +0x20
    float      mRefundFraction;                  // +0x24
    float      kMaxCityUpgradeLevel;             // +0x28 (retail float)
    float      kCityUpgradeCosts[2];             // +0x2c (retail [0] float, [1] int)
    float      kHappinessTotalTimeForCalculation;// +0x34
    float      kHappinessUnitTimeForCalculation; // +0x38
    float      kHappinessBarRange;               // +0x3c
    float      kEventLogTimeoutInMS_Red;         // +0x40 (retail float)
    float      kEventLogTimeoutInMS_Blue;        // +0x44 (retail float)
    int        kEventLogTimeoutInMS_Yellow;      // +0x48
    int        kPlumpDistance;                   // +0x4c (retail int)
    int        kRaidRelationshipEffect;          // +0x50 (retail int)
    float      kTradeRelationshipEffect;         // +0x54
    float      kRecruitRelationshipEffect;       // +0x58
    float      kGiftRelationshipEffect;          // +0x5c
    float      kVehicleGiftRelationshipEffect;   // +0x60
    float      kVehicleTradeRelationshipEffect;  // +0x64
    float      kVehicleGiftCost;                 // +0x68
    float      kFailedMissionRelationshipEffect; // +0x6c
    float      kCivAttackRelationshipEffect;     // +0x70
    float      kCivAttackTradePartnerRelationshipEffect; // +0x74
    float      kTimeBetweenAttacksForRelationshipPenalty;// +0x78 (retail float)
    float      kHappyIdleThreshold;              // +0x7c
    uint32_t   kProductivityThreshold;           // +0x80 (retail: unsigned, fistp qword)
    float      kEntertainmentThreshold;          // +0x84
    float      kProtestDuration;                 // +0x88
    float      kLurkDuration;                    // +0x8c
    float      kLurkDetectRadius;                // +0x90
    float      kWanderDuration;                  // +0x94
    float      kMaxDistanceForInteractWithTribes;// +0x98
    float      kGiftAmountPerCreature;           // +0x9c
    float      kPartySupplyTime;                 // +0xa0
    float      kSmallPartyAttractChance;         // +0xa4
    float      kSmallPartyAttractRadius;         // +0xa8
    float      kSmallPartyCost;                  // +0xac (retail float)
    float      kSmallPartyCapacity;              // +0xb0 (retail float)
    int        kSmallPartySupplies;              // +0xb4
    int        kPartyBonusHappiness;             // +0xb8 (retail int)
    int        kPartyBonusDuration;              // +0xbc (retail int)
    float      kMinDistanceBetweenCities;        // +0xc0
    float      kMinDistBetweenTribes;            // +0xc4
    float      kProtestGroupAngle;               // +0xc8
    float      kSleepingGroupAngle;              // +0xcc
    float      kIdleGroupAngle;                  // +0xd0
    float      kHappyIdleGroupAngle;             // +0xd4
    float      kIdleAtCityHallMinDistance;       // +0xd8 (retail float)
    float      kIdleAtCityHallMaxDistance;       // +0xdc (retail float)
    float      kRadiusFromCityHall;              // +0xe0
    float      kRoadCost;                        // +0xe4 (retail float)
    float      kRoadRefundFraction;              // +0xe8
    float      kRoadSpeedMultiplier;             // +0xec
    float      kRoadInitialWidth;                // +0xf0
    float      kEstablishTempleSingTime;         // +0xf4
    float      kCounterConversionInterval;       // +0xf8
    float      kVehicleCapPerCity;               // +0xfc (retail float)
    float      kHarvesterCapPerCity;             // +0x100 (retail float)
    int        kWallBuildingBuffer;              // +0x104 (retail int)
    int        kMinNumWallSegments;              // +0x108 (retail int)
    float      kDistBetweenWallPosts;            // +0x10c
    float      kCityGameSpeeds[4];               // +0x110
    float      kCivGameSpeeds[4];                // +0x120
    float      kCityHappinessForFood;            // +0x130
    float      kCityHappinessForHousing;         // +0x134
    float      kCityHappinessForStructure;       // +0x138
    float      kCityHappinessForLifestyle;       // +0x13c
    float      kCityHappinessForCivicObject;     // +0x140
    float      kCityHappinessForParty;           // +0x144
    float      kHappinessForFood;                // +0x148
    float      kHappinessForHousing;             // +0x14c
    float      kHappinessForStructure;           // +0x150
    float      kHappinessForLifestyle;           // +0x154
    float      kHappinessForCivicObject;         // +0x158
    float      kMaxProtestorFraction;            // +0x15c
    float      kPopulationFedPerFarmWorker;      // +0x160 (retail float)
    float      kPopulationHappyPerEntertainmentBuilding; // +0x164 (retail float)
    int        kPopulationHappyPerCivicObject;   // +0x168
    int        kSecondsHappyAfterParty;          // +0x16c
    int        kMoneyPerIndustryWorkerPerSecond; // +0x170 (retail int)
    int        kMoneyPerMarketWorkerPerSecond;   // +0x174 (retail int)
    float      kTimeInConverted;                 // +0x178 (retail float)
    float      kConvertCitizenRelationshipDelta; // +0x17c
    int        kConvertVehicleRelationshipDelta; // +0x180 (retail int)
    float      kBribeVehicleRelationshipDelta;   // +0x184
    float      kSoundGateConvertingPosId1;       // +0x188 (float here)
    float      kSoundGateConvertingPosId2;       // +0x18c (float here)
    uint32_t   kSoundGateConvertingPosId3;       // +0x190
    uint32_t   kSoundGateConvertingNegId1;       // +0x194
    uint32_t   kSoundGateConvertingNegId2;       // +0x198
    uint32_t   kSoundGateConvertingNegId3;       // +0x19c
    uint32_t   kResourceRegenerationPerSecond;   // +0x1a0 (key here)
    uint32_t   kCostToBuyCityModifier;           // +0x1a4 (key here)
    float      kConversionGroupPowerModifier;    // +0x1a8
    float      kConversionGroupSizeModifier;     // +0x1ac
    float      kBaseConversionStrength;          // +0x1b0
    float      kCrowdReationModifier;            // +0x1b4
    float      kCrowdReationOffset;              // +0x1b8
    float      kCrowdDPSOffset;                  // +0x1bc
    float      kCrowdDPSModifier;                // +0x1c0
    float      kCrowdDPSBase;                    // +0x1c4
    float      kCrowdConvertOffset;              // +0x1c8
    float      kHarvestMinLoad;                  // +0x1cc
    float      kHarvestMaxLoad;                  // +0x1d0
    float      kHarvestResourceLoss;             // +0x1d4
    float      kMilitaryProb;                    // +0x1d8
    float      kCulturalProb;                    // +0x1dc
    float      kMilitaryProbMajorNPC;            // +0x1e0
    float      kCulturalProbMajorNPC;            // +0x1e4
    float      kMilitaryProbMinorNPC;            // +0x1e8
    float      kCulturalProbMinorNPC;            // +0x1ec
    float      kSecondsNextCityEarly;            // +0x1f0
    float      kSecondsNextCityLate;             // +0x1f4
    float      kEarlyLateCityThreshold;          // +0x1f8
    float      kCityHappyIncome;                 // +0x1fc
    float      kCityBoredIncome;                 // +0x200
    float      kCityTiredIncome;                 // +0x204
    uint32_t   kRelationshipSpaceDecayPeriod;    // +0x208
    uint32_t   kRelationshipCivDecayPeriod;      // +0x20c
    uint32_t   kRelationshipTribeDecayPeriod;    // +0x210
};

class cCityGameTuning;   // fwd

App::PropertyManager* PropertyManager();   // 0x0067DE30

// @ 0x00CEF050
void cCityGameTuning::Init()
{
    AutoRefCount<App::PropertyList> pList;
    if (!PropertyManager()->GetPropertyList(0xb6a5c63d, pList.AsPointerRef()))
        return;
    {
        GetPropertyAsVector3(pList, 0x3f6af12, &kInitialCameraPolarCoords);

        GetPropertyAsFloat(pList, 0x1ca5c7a, kTradeRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc7f0, kCityHallMoney);
        GetPropertyAsFloat(pList, 0x1abc7f1, kCityHallMoneyTime);
        kCityHallMoneyTime *= 1000.0f;
        GetPropertyAsFloat(pList, 0x64be077, mRefundFraction);
        GetPropertyAsFloat(pList, 0x64be078, kMaxCityUpgradeLevel);
        GetPropertyAsFloat(pList, 0x64be079, kCityUpgradeCosts[0]);
        GetPropertyAsFloat(pList, 0x1abc7f5, kHappinessBarRange);
        kHappinessBarRange *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc7f6, kEventLogTimeoutInMS_Red);
        kEventLogTimeoutInMS_Red *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc7f7, kEventLogTimeoutInMS_Blue);
        GetPropertyAsFloat(pList, 0x1abc7fc, kEntertainmentThreshold);
        GetPropertyAsFloat(pList, 0x1abc7fd, kProtestDuration);
        GetPropertyAsFloat(pList, 0x1abc7fe, kLurkDuration);
        GetPropertyAsFloat(pList, 0x1abc7ff, kLurkDetectRadius);
        kLurkDetectRadius *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc800, kWanderDuration);
        kWanderDuration *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc801, kMaxDistanceForInteractWithTribes);
        GetPropertyAsFloat(pList, 0x1abc802, kGiftAmountPerCreature);
        kGiftAmountPerCreature *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc803, kPartySupplyTime);
        GetPropertyAsFloat(pList, 0x1abc804, kSmallPartyAttractRadius);
        kSmallPartyAttractRadius *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc805, kSmallPartyCost);
        GetPropertyAsFloat(pList, 0x1abc806, kSmallPartyCapacity);
        GetPropertyAsFloat(pList, 0x1abc80f, kMinDistanceBetweenCities);
        GetPropertyAsFloat(pList, 0x1abc810, kMinDistBetweenTribes);
        kMinDistBetweenTribes *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1abc816, kProtestGroupAngle);
        GetPropertyAsFloat(pList, 0x1abc817, kSleepingGroupAngle);
        GetPropertyAsFloat(pList, 0x1abc818, kIdleGroupAngle);
        GetPropertyAsFloat(pList, 0x1abc819, kHappyIdleGroupAngle);
        GetPropertyAsFloat(pList, 0x1abc81a, kIdleAtCityHallMinDistance);
        GetPropertyAsFloat(pList, 0x1abc81b, kIdleAtCityHallMaxDistance);
        GetPropertyAsFloat(pList, 0x1abc81e, kRoadRefundFraction);
        GetPropertyAsFloat(pList, 0x1abc825, kRoadInitialWidth);
        GetPropertyAsFloat(pList, 0x1abc826, kEstablishTempleSingTime);
        GetPropertyAsFloat(pList, 0x2c1e020, kCounterConversionInterval);
        GetPropertyAsFloat(pList, 0x1abc82a, kVehicleCapPerCity);
        GetPropertyAsFloat(pList, 0x1abc82b, kHarvesterCapPerCity);
        kHarvesterCapPerCity *= 1000.0f;
        GetPropertyAsFloat(pList, 0x1ac5a97, kCityGameSpeeds[1]);
        GetPropertyAsFloat(pList, 0x1ac582b, kCityGameSpeeds[0]);
        GetPropertyAsFloat(pList, 0x1abc82e, kDistBetweenWallPosts);
        GetPropertyAsFloat(pList, 0x1abc82f, kRecruitRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc830, kGiftRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc831, kVehicleGiftRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc832, kVehicleTradeRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc833, kVehicleGiftCost);
        GetPropertyAsFloat(pList, 0x1abc834, kFailedMissionRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc835, kCivAttackRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc836, kCivAttackTradePartnerRelationshipEffect);
        GetPropertyAsFloat(pList, 0x1abc837, kTimeBetweenAttacksForRelationshipPenalty);
        GetPropertyAsFloat(pList, 0x1b9777b, kHappyIdleThreshold);

        GetPropertyAsInt(pList, 0x1abc7ea, kInitialWealth);
        GetPropertyAsInt(pList, 0x1abc7ec, kInitialCreatures);
        GetPropertyAsInt(pList, 0x1abc7ed, kInitialCreaturesPerTribe);
        GetPropertyAsInt(pList, 0x1abc7ee, kInitialTribes);
        GetPropertyAsInt(pList, 0x1abc7f8, *reinterpret_cast<int*>(&kCityUpgradeCosts[1]));
        GetPropertyAsInt(pList, 0x1abc7f9, kEventLogTimeoutInMS_Yellow);
        GetPropertyAsInt(pList, 0x1abc7fa, kPlumpDistance);
        GetPropertyAsInt(pList, 0x1abc7fb, kRaidRelationshipEffect);
        GetPropertyAsInt(pList, 0x1abc809, kSmallPartySupplies);
        GetPropertyAsInt(pList, 0x1abc80d, kPartyBonusHappiness);
        GetPropertyAsInt(pList, 0x1abc80e, kPartyBonusDuration);
        GetPropertyAsInt(pList, 0x1abc81c, *reinterpret_cast<int*>(&kRadiusFromCityHall));
        GetPropertyAsInt(pList, 0x1abc81d, *reinterpret_cast<int*>(&kRoadCost));
        GetPropertyAsInt(pList, 0x1abc824, *reinterpret_cast<int*>(&kRoadSpeedMultiplier));

        GetPropertyAsFloat(pList, 0x1fb2b46, kCityGameSpeeds[2]);
        GetPropertyAsFloat(pList, 0x1fb2b47, kCityGameSpeeds[3]);
        GetPropertyAsFloat(pList, 0x1fb2b48, kCivGameSpeeds[0]);
        GetPropertyAsFloat(pList, 0x1fb2b49, kCivGameSpeeds[1]);
        GetPropertyAsFloat(pList, 0x1fb2b4a, kCivGameSpeeds[2]);
        GetPropertyAsFloat(pList, 0x1fb2b4b, kCivGameSpeeds[3]);
        GetPropertyAsFloat(pList, 0x1fb2b4c, kCityHappinessForFood);
        GetPropertyAsFloat(pList, 0x1fb2b4d, kCityHappinessForHousing);

        {
            float v;                                         // original leaves it uninitialised
            GetPropertyAsFloat(pList, 0x1abc838, v);
            kProductivityThreshold = (uint32_t)(v * 1000.0f);
        }

        GetPropertyAsFloat(pList, 0x1abd3f2, kHappinessTotalTimeForCalculation);
        GetPropertyAsFloat(pList, 0x1abd3f3, kHappinessUnitTimeForCalculation);
        GetPropertyAsFloat(pList, 0x90a2f18c, kSmallPartyAttractChance);
        GetPropertyAsInt(pList, 0x2cb589b, kWallBuildingBuffer);
        GetPropertyAsInt(pList, 0x3ecb7c0, kMinNumWallSegments);
        GetPropertyAsFloat(pList, 0x20c2988, kHappinessForStructure);
        GetPropertyAsFloat(pList, 0x20c2989, kHappinessForLifestyle);
        GetPropertyAsFloat(pList, 0x20c298a, kHappinessForCivicObject);
        GetPropertyAsFloat(pList, 0x20c298b, kMaxProtestorFraction);
        GetPropertyAsFloat(pList, 0x2afaddf, kPopulationFedPerFarmWorker);
        GetPropertyAsFloat(pList, 0x20c298c, kPopulationHappyPerEntertainmentBuilding);
        GetPropertyAsInt(pList, 0x20c298d, kPopulationHappyPerCivicObject);
        GetPropertyAsInt(pList, 0x20c298e, kSecondsHappyAfterParty);
        GetPropertyAsInt(pList, 0x2afb20c, kMoneyPerIndustryWorkerPerSecond);
        GetPropertyAsInt(pList, 0x2afb212, kMoneyPerMarketWorkerPerSecond);
        GetPropertyAsFloat(pList, 0x20c298f, kTimeInConverted);
        GetPropertyAsFloat(pList, 0x20c2990, kConvertCitizenRelationshipDelta);
        GetPropertyAsFloat(pList, 0x2b0c627, kCityHappinessForStructure);
        GetPropertyAsFloat(pList, 0x2b0c62e, kCityHappinessForLifestyle);
        GetPropertyAsFloat(pList, 0x2b0c633, kCityHappinessForCivicObject);
        GetPropertyAsFloat(pList, 0x2b0c639, kCityHappinessForParty);
        GetPropertyAsFloat(pList, 0x2b0c63e, kHappinessForFood);
        GetPropertyAsFloat(pList, 0x2b0c642, kHappinessForHousing);

        {
            float v;
            GetPropertyAsFloat(pList, 0x3f13617, v);
            kConvertVehicleRelationshipDelta = (int)(v * 1000.0f);
        }

        GetPropertyAsFloat(pList, 0x404213f, kBribeVehicleRelationshipDelta);
        GetPropertyAsFloat(pList, 0x4042140, kSoundGateConvertingPosId1);
        GetPropertyAsFloat(pList, 0x4042141, kSoundGateConvertingPosId2);

        GetPropertyAsKeyInstance(pList, 0x3f6937c, &kSoundGateConvertingPosId3);
        GetPropertyAsKeyInstance(pList, 0x3f6937d, &kSoundGateConvertingNegId1);
        GetPropertyAsKeyInstance(pList, 0x3f6937e, &kSoundGateConvertingNegId2);
        GetPropertyAsKeyInstance(pList, 0x3f6937f, &kSoundGateConvertingNegId3);
        GetPropertyAsKeyInstance(pList, 0x3f69380, &kResourceRegenerationPerSecond);
        GetPropertyAsKeyInstance(pList, 0x3f69381, &kCostToBuyCityModifier);

        GetPropertyAsFloat(pList, 0x3fd0826, kConversionGroupPowerModifier);
        GetPropertyAsFloat(pList, 0x4cd6efe, kConversionGroupSizeModifier);
        GetPropertyAsFloat(pList, 0x4cd7226, kBaseConversionStrength);
        GetPropertyAsFloat(pList, 0x4cd7227, kCrowdReationModifier);
        GetPropertyAsFloat(pList, 0x4cd7228, kCrowdReationOffset);
        GetPropertyAsFloat(pList, 0x4cd7229, kCrowdDPSOffset);
        GetPropertyAsFloat(pList, 0x4cd722a, kCrowdDPSModifier);
        GetPropertyAsFloat(pList, 0x4cd722b, kCrowdDPSBase);
        GetPropertyAsFloat(pList, 0x4cd722c, kCrowdConvertOffset);
        GetPropertyAsFloat(pList, 0x4cd722d, kHarvestMinLoad);
        GetPropertyAsFloat(pList, 0x4cd722e, kHarvestMaxLoad);
        GetPropertyAsFloat(pList, 0x4cd86a3, kHarvestResourceLoss);
        GetPropertyAsFloat(pList, 0x4cd86a4, kMilitaryProb);
        GetPropertyAsFloat(pList, 0x4cd86a5, kCulturalProb);
        GetPropertyAsFloat(pList, 0x4cda095, kMilitaryProbMajorNPC);
        GetPropertyAsFloat(pList, 0x4cda096, kCulturalProbMajorNPC);
        GetPropertyAsFloat(pList, 0x4cda097, kMilitaryProbMinorNPC);
        GetPropertyAsFloat(pList, 0x4cda098, kCulturalProbMinorNPC);
        GetPropertyAsFloat(pList, 0x4cda099, kSecondsNextCityEarly);
        GetPropertyAsFloat(pList, 0x4cda09a, kSecondsNextCityLate);
        GetPropertyAsFloat(pList, 0x4cdad7d, kEarlyLateCityThreshold);
        GetPropertyAsFloat(pList, 0x4ce8c24, kCityHappyIncome);
        GetPropertyAsFloat(pList, 0x4ce8c25, kCityBoredIncome);
        GetPropertyAsFloat(pList, 0x4ce8c26, kCityTiredIncome);

        GetPropertyAsUInt(pList, 0x51c61a5, kRelationshipSpaceDecayPeriod);
        GetPropertyAsUInt(pList, 0x51c61c2, kRelationshipCivDecayPeriod);
        GetPropertyAsUInt(pList, 0x53194f7, kRelationshipTribeDecayPeriod);
    }
}

}  // namespace SP
