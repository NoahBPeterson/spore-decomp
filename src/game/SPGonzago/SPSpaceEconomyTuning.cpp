// src/game/SPGonzago/SPSpaceEconomyTuning.cpp -- migrated from slice(s) s0102f0d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceEconomyTuning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"

// unnamed retail callees and globals (address in the comment)
extern float g_1;        // 0x01485720
extern float g_0;        // 0x01485378
extern float g_0_01;     // 0x013eb960
extern float g_0_04;     // 0x013ef53c

// ---- items of slice s0102f0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Prop {
    char pad[0x12];
    unsigned short type;                    // +0x12
    int*   GetInt();                        // 0x0041e990
    float* GetFloat();                      // 0x0041ea70
};
struct GetsProperty {
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
    virtual void q8();
    virtual bool GetProperty(uint id, void** out);       // +0x24
};
struct cPropertyList : GetsProperty {};
bool GetPropertyAsIntArray(cPropertyList* list, uint id, int* count, int** data);       // 0x006a07d0
bool GetPropertyAsFloatArray(cPropertyList* list, uint id, int* count, float** data);   // 0x006a08b0
struct cEmpire;
struct Tribe { int GetUniverse(); };                    // 0x00fe42a0
struct cGameData { Tribe* GetPlayerTribe(); };          // 0x00bfc5f0
void* SpaceGameGet();                                   // 0x01002bd0
struct cStarRecordVec { int* mpBegin; int* mpEnd; int* mpCapacity; };
struct cEmpire {
    char pad[0x84];
    cStarRecordVec mStars;                  // +0x84
    int GetHomePlanet();                    // 0x00c31730
    bool CanContact(cEmpire* other);        // 0x00c31bc0
};
extern float g_1;        // 0x01485720
extern float g_0;        // 0x01485378
extern float g_0_01;     // 0x013eb960
extern float g_0_04;     // 0x013ef53c
struct VtableDtor2 {
    virtual void e00();
    virtual void e04();
};
void           operator_delete_(void* p);              // 0x00f47380
struct cSPSpaceEconomyTuning {
    char pad0[8];
    cPropertyList* mPropList;                             // +8
    int   GetTradeCaptureOfferPrice(int index);           // 0x0102fa30
    int   GetHomeWorldBuildingMultiplier();               // 0x0102fb70
    int   GetEnergyRechargeDelayMS();                     // 0x0102fbf0
    float GetEnergyRechargePerMS();                       // 0x0102fc60
    int   GetTradeCaptureCostForPlanet(int index);        // 0x01030000
    int   CalcAttackRequestCost(float place);             // 0x01030650
    int   GetPeaceOfferPrice(int index, cEmpire* e);      // 0x01030930
    int   GetPeaceBadOfferDelta(cEmpire* e);              // 0x010309c0
    int   GetPeaceVeryBadOfferDelta(cEmpire* e);          // 0x01030a30
    int   GetPeaceGoodOfferDelta(cEmpire* e);             // 0x01030aa0
    float f0102f8c0(int index);                           // 0x0102f8c0
};
void  GetTurretAndBuildingCounts(float place, int* turrets, int* buildings);   // 0x00c70380
void* __stdcall GetStarManagerForEmpire(cEmpire* e);     // 0x00b3d2a0, ret 4
struct StarManagerObj { void* GetHomeStar(); };          // 0x00baf700, thiscall(ecx=mgr)
float RandomFloatRange(float lo, float hi);              // 0x00572a10
float f010307a0(void* props, uint idA, uint idB);        // 0x010307a0
// ---- items of slice s0102f0d0 end

// @ 0x0102fa30
int cSPSpaceEconomyTuning::GetTradeCaptureOfferPrice(int index)
{
    cPropertyList* pl = mPropList;
    int  count = 0;
    int* data = 0;
    if (GetPropertyAsIntArray(pl, 0x55565b4, &count, &data))
        return data[index];
    return 0;
}

// @ 0x0102fb70
int cSPSpaceEconomyTuning::GetHomeWorldBuildingMultiplier()
{
    cPropertyList* pl = mPropList;
    Prop* prop;
    if (pl && pl->GetProperty(0x4ab4745, (void**)&prop) && prop->type == 9)
        return *prop->GetInt();
    return 0;
}

// @ 0x0102fbf0
int cSPSpaceEconomyTuning::GetEnergyRechargeDelayMS()
{
    cPropertyList* pl = mPropList;
    float value = g_1;
    Prop* prop;
    if (pl && pl->GetProperty(0x5b14971, (void**)&prop) && prop->type == 0xd)
        return (int)(*prop->GetFloat() * 1000.0f);
    return (int)(value * 1000.0f);
}

// @ 0x0102fc60
float cSPSpaceEconomyTuning::GetEnergyRechargePerMS()
{
    cPropertyList* pl = mPropList;
    float value = 0.0f;
    Prop* prop;
    if (pl) {
        if (pl->GetProperty(0x5b14955, (void**)&prop) && prop->type == 0xd)
            value = *prop->GetFloat();
    }
    return value * 0.001f;
}

// @ 0x01030000
int cSPSpaceEconomyTuning::GetTradeCaptureCostForPlanet(int index)
{
    cPropertyList* pl = mPropList;
    int result = 0;
    uint keys[4] = { 0x56778c1, 0x56778c3, 0x56778c5, 0x56778c6 };
    Prop* prop;
    if (pl) {
        if (pl->GetProperty(keys[index], (void**)&prop) && prop->type == 9)
            result = *prop->GetInt();
    }
    return result;
}

// @ 0x01030650
int cSPSpaceEconomyTuning::CalcAttackRequestCost(float place)
{
    int turrets = 0;
    int buildings = 0;
    GetTurretAndBuildingCounts(place, &turrets, &buildings);

    float turretMul = g_1;
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* prop;
        if (pl->GetProperty(0x5d4db2b, (void**)&prop) && prop->type == 0xd)
            turretMul = *prop->GetFloat();
    }

    float buildingMul = g_1;
    pl = mPropList;
    if (pl) {
        Prop* prop;
        if (pl->GetProperty(0x5d4db30, (void**)&prop) && prop->type == 0xd)
            buildingMul = *prop->GetFloat();
    }

    int base = (int)(((float)buildings * buildingMul + (float)turrets * turretMul) * g_0_04);

    float add = g_1;
    pl = mPropList;
    if (pl) {
        Prop* prop;
        if (pl->GetProperty(0x5d64754, (void**)&prop) && prop->type == 0xd)
            add = *prop->GetFloat();
    }
    return base * 0x19 + (int)add;
}

// @ 0x010307a0
float f010307a0(void* props, uint idA, uint idB)
{
    float value = g_1;
    if (props == 0)
        return value;
    int tribe = ((cGameData*)SpaceGameGet())->GetPlayerTribe()->GetUniverse();
    int   countA = 0; float* dataA = 0;
    int   countB = 0; float* dataB = 0;
    float a = 0.0f, b = 0.0f;
    GetPropertyAsFloatArray((cPropertyList*)props, idA, &countA, &dataA);
    if (countA == 0xb)
        a = dataA[tribe];
    GetPropertyAsFloatArray((cPropertyList*)props, idB, &countB, &dataB);
    if (countB == 0xb)
        b = dataB[tribe];
    float* sel1 = &a;
    if (a <= g_0)
        sel1 = &g_0;
    float hi = *sel1;
    float* sel2 = &b;
    if (b <= hi)
        sel2 = &hi;
    float lo = *sel2;
    if (hi < lo)
        return RandomFloatRange(hi, lo);
    return hi;
}

// @ 0x010308d0
void* f010308d0(int* self, char flags)
{
    *(void**)self = (void*)0x14996d4;
    int* p = (int*)self[2];
    if (p) {
        self[2] = 0;
        ((VtableDtor2*)p)->e04();
    }
    int* q = (int*)self[3];
    if (q != 0) {
        if (*(int*)((char*)q - 4) != 0)
            operator_delete_(q);
    }
    int* r = (int*)self[2];
    if (r)
        ((VtableDtor2*)r)->e04();
    *(void**)self = (void*)0x1416f14;
    if (flags & 1)
        operator_delete_(self);
    return self;
}

// @ 0x01030930
int cSPSpaceEconomyTuning::GetPeaceOfferPrice(int index, cEmpire* e)
{
    cPropertyList* pl = mPropList;
    int  count = 0;
    int* data = 0;
    if (GetPropertyAsIntArray(pl, 0x5655ab5, &count, &data)) {
        void* star = ((StarManagerObj*)GetStarManagerForEmpire(e))->GetHomeStar();
        float f = f010307a0(star, 0x686e2a4, 0x686e2a8);
        float scaled = (float)data[index] * f;
        return (int)(scaled * g_0_01) * 100;
    }
    return 0;
}

// @ 0x010309c0
int cSPSpaceEconomyTuning::GetPeaceBadOfferDelta(cEmpire* e)
{
    int value = 0x63;
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* prop;
        if (pl->GetProperty(0x565605e, (void**)&prop) && prop->type == 9)
            value = *prop->GetInt();
        void* star = ((StarManagerObj*)GetStarManagerForEmpire(e))->GetHomeStar();
        float f = f010307a0(star, 0x686e2a4, 0x686e2a8);
        return (int)(f * value);
    }
    return value;
}

// @ 0x01030a30
int cSPSpaceEconomyTuning::GetPeaceVeryBadOfferDelta(cEmpire* e)
{
    int value = 0x63;
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* prop;
        if (pl->GetProperty(0x5656063, (void**)&prop) && prop->type == 9)
            value = *prop->GetInt();
        void* star = ((StarManagerObj*)GetStarManagerForEmpire(e))->GetHomeStar();
        float f = f010307a0(star, 0x686e2a4, 0x686e2a8);
        return (int)(f * value);
    }
    return value;
}

// @ 0x01030aa0
int cSPSpaceEconomyTuning::GetPeaceGoodOfferDelta(cEmpire* e)
{
    int value = 0x63;
    cPropertyList* pl = mPropList;
    if (pl) {
        Prop* prop;
        if (pl->GetProperty(0x5656066, (void**)&prop) && prop->type == 9)
            value = *prop->GetInt();
        void* star = ((StarManagerObj*)GetStarManagerForEmpire(e))->GetHomeStar();
        float f = f010307a0(star, 0x686e2a4, 0x686e2a8);
        return (int)(f * value);
    }
    return value;
}
