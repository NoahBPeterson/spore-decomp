// Slice s00cecf10 -- SP::cBuildingTuning::SetValues
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /GS- /fp:fast
#include "types.h"
#include <string.h>
#include <intrin.h>

struct Property {
    char pad0[0x12];
    short type;                 // +0x12
    float* GetFloat();                   // 0x41ea70 (property -> float storage)
    int*   GetInt();                     // 0x41e990
};

struct PropList {                        // refcounted property list
    virtual void v0();
    virtual void Release();              // +4
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(unsigned id, Property** out);   // +0x24
};

struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual bool GetPropertyList(unsigned id, PropList** out);   // +0x30
};

PropertyManager* __cdecl PropertyManager_Get();    // 0x67de30 (SP::PropertyManager)
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* file, int line);
void  __cdecl operator_delete__(void* p);

extern PropList* g_propList;             // 0x169c1e4

struct EStr {                            // eastl::basic_string<char, allocator>
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAlloc;
    void assign(const char* b, const char* e);       // 0x454cb0
};

template <unsigned N>
struct TmpStr {                          // temporary built from a literal
    char* b; char* e; char* c; int al;
    TmpStr(const char (&s)[N]) {
        b = (char*)operator_new(N, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memcpy(b, s, N - 1);
        e = b + N - 1;
        c = b + N;
        *e = 0;
    }
    void Free() { if (c - b > 1 && b) operator_delete__(b); }
};

#define SETSTR(field, lit) do { TmpStr<sizeof(lit)> t(lit); \
    if ((EStr*)&t != &(field)) (field).assign(t.b, t.e); _ReadWriteBarrier(); t.Free(); } while (0)

struct cBuildingTuning {
    float kSleepEnergyDelta, kSleepCost, kSleepCostSpace;
    int kSleepCapacity, kRoomsPerHouse;
    float kSleepMinStay, kSleepMaxStay;
    EStr kSleepBuildingName;
    float kEntertainmentDelta, kEntertainmentCost, kEntertainmentCostSpace;
    int kEntertainmentCapacity, kRoomsPerEntertainment;
    float kEntertainmentMinStay, kEntertainmentMaxStay;
    EStr kEntertainmentBuildingName;
    float kCultureCost;
    int kCultureCapacity;
    float kCultureMinStay, kCultureMaxStay;
    EStr kCulturalBuildingName;
    float kIndustryMoneyDeltaCity, kIndustryMoneyDeltaCiv, kIndustryMoneyTime;
    float kIndustryCost, kIndustryCostSpace;
    int kIndustryCapacity;
    float kIndustryMinStay, kIndustryMaxStay;
    EStr kIndustryBuildingName;
    float kFarmFoodPerCreatureDeltaCity, kFarmFoodPerCreatureDeltaCiv, kFarmCost;
    int kFarmCapacity;
    float kFarmMinStay, kFarmMaxStay;
    EStr kFoodBuildingName;
    float kDiplomaticCost, kDiplomaticMinStay, kDiplomaticMaxStay;
    int kDiplomaticCapacity;
    EStr kDiplomaticBuildingName;
    float kMarketBundleSellPriceCity, kMarketBundleSellPriceCiv, kMarketBuyFoodCost;
    int kMarketNumNPCsPerWorker, kMarketFoodBundleCapacity, kMarketGoodsBundleCapacity;
    float kMarketCost;
    int kMarketCapacity;
    float kMarketMinStay, kMarketMaxStay, kMarketMoneyTime, kMarketMoneyDeltaCity, kMarketMoneyDeltaCiv;
    float kMilitaryCost;
    EStr kMilitaryBuildingName;
    float kDefenseCost, kDefenseCostSpace;
    EStr kDefenseBuildingName;
    float kMissionCost;
    EStr kMissionBuildingName;
    float kBuildingPadBorderSize, kCivicObjectCost;

    void SetValues();
};

#define F(id, field) do { Property* p; if (g_propList && g_propList->GetProperty(id, &p) && p->type == 0xd) (field) = *p->GetFloat(); } while (0)
#define I(id, field) do { Property* p; if (g_propList && g_propList->GetProperty(id, &p) && p->type == 9) (field) = *p->GetInt(); } while (0)

// @ 0x00cecf10
void cBuildingTuning::SetValues()
{
    PropertyManager* pm = PropertyManager_Get();
    if (g_propList) {
        PropList* old = g_propList;
        g_propList = 0;
        old->Release();
    }
    if (!pm->GetPropertyList(0xb7e0ff19, &g_propList))
        return;

    F(0x15a4cb4, kSleepEnergyDelta);
    F(0x15a4cc9, kSleepCost);
    F(0x15a4cca, kSleepCostSpace);
    I(0x15a4cd6, kSleepCapacity);
    I(0x15a4cfa, kRoomsPerHouse);
    F(0x15a4cde, kSleepMinStay);
    kSleepMinStay = kSleepMinStay * 1000.0f;
    F(0x15a4ce7, kSleepMaxStay);
    kSleepMaxStay = kSleepMaxStay * 1000.0f;
    SETSTR(kSleepBuildingName, "House");

    F(0x282ce9c, kBuildingPadBorderSize);
    F(0x1a821c5, kEntertainmentDelta);
    F(0x1a821c9, kEntertainmentCost);
    F(0x1a821ca, kEntertainmentCostSpace);
    I(0x1a821cd, kEntertainmentCapacity);
    I(0x1a821d1, kRoomsPerEntertainment);
    F(0x1a821d4, kEntertainmentMinStay);
    kEntertainmentMinStay = kEntertainmentMinStay * 1000.0f;
    F(0x1a821d9, kEntertainmentMaxStay);
    kEntertainmentMaxStay = kEntertainmentMaxStay * 1000.0f;
    SETSTR(kEntertainmentBuildingName, "That's Entertainment!");

    F(0x15a4d88, kCultureCost);
    I(0x15a4d8f, kCultureCapacity);
    F(0x15a4d98, kCultureMinStay);
    kCultureMinStay = kCultureMinStay * 1000.0f;
    F(0x15a4d9f, kCultureMaxStay);
    kCultureMaxStay = kCultureMaxStay * 1000.0f;
    SETSTR(kCulturalBuildingName, "Culture");

    F(0x15a4dc8, kIndustryMoneyDeltaCity);
    F(0x1ba40e0, kIndustryMoneyDeltaCiv);
    F(0x15a4dce, kIndustryMoneyTime);
    kIndustryMoneyTime = kIndustryMoneyTime * 1000.0f;
    F(0x15a4db7, kIndustryCost);
    F(0x15a4db8, kIndustryCostSpace);
    I(0x15a4dbf, kIndustryCapacity);
    F(0x15a4dd5, kIndustryMinStay);
    kIndustryMinStay = kIndustryMinStay * 1000.0f;
    F(0x15a4ddb, kIndustryMaxStay);
    kIndustryMaxStay = kIndustryMaxStay * 1000.0f;
    SETSTR(kIndustryBuildingName, "Factory");

    F(0x15a4e37, kFarmFoodPerCreatureDeltaCity);
    F(0x1d34ec9, kFarmFoodPerCreatureDeltaCiv);
    F(0x15a4e27, kFarmCost);
    I(0x15a4e2f, kFarmCapacity);
    F(0x15a4e3d, kFarmMinStay);
    kFarmMinStay = kFarmMinStay * 1000.0f;
    F(0x15a4e45, kFarmMaxStay);
    kFarmMaxStay = kFarmMaxStay * 1000.0f;
    SETSTR(kFoodBuildingName, "Farm");

    F(0x2af772f, kCivicObjectCost);
    I(0x15a4e64, kMarketFoodBundleCapacity);
    F(0x15a4e6d, kMarketCost);
    I(0x15a4e74, kMarketCapacity);
    F(0x15a4e7c, kMarketMinStay);
    kMarketMinStay = kMarketMinStay * 1000.0f;
    F(0x15a4e82, kMarketMaxStay);
    kMarketMaxStay = kMarketMaxStay * 1000.0f;
    F(0x1a7f10c, kMarketBundleSellPriceCity);
    F(0x1ba4aee, kMarketBundleSellPriceCiv);
    F(0x1a81ba1, kMarketBuyFoodCost);
    I(0x1abd40f, kMarketNumNPCsPerWorker);
    F(0x1cb9d21, kMarketMoneyTime);
    kMarketMoneyTime = kMarketMoneyTime * 1000.0f;
    F(0x1cb9d08, kMarketMoneyDeltaCity);
    F(0x1cb9d1a, kMarketMoneyDeltaCiv);
    F(0x1b7e1a2, kDiplomaticCost);
    F(0x1b7e1ac, kDiplomaticMinStay);
    F(0x1b7e1b4, kDiplomaticMaxStay);
    I(0x1b7e7ef, kDiplomaticCapacity);
    SETSTR(kDiplomaticBuildingName, "Diplomacy Building");

    F(0x15a4e89, kMilitaryCost);
    SETSTR(kMilitaryBuildingName, "Military Base");

    F(0x1ba5251, kDefenseCost);
    F(0x1ba5252, kDefenseCostSpace);
    SETSTR(kDefenseBuildingName, "Defense");
    SETSTR(kMissionBuildingName, "Mission");
}
