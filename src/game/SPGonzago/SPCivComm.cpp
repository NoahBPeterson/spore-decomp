// src/game/SPGonzago/SPCivComm.cpp -- migrated from slice(s) s0135d100, s00cfeeb0, s00cfe160 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCivComm.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivilization.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cRelationshipManager.h"
#include "SP/cCity.h"
#include "SP/cGameData.h"
#include "SP/cPlanet.h"

// unnamed retail callees and globals (address in the comment)
extern float gField169d388;                              // 0x0169d388
extern float gField169d38c;                              // 0x0169d38c
extern float gField169d390;                              // 0x0169d390
#pragma warning(disable : 4100)

// ---- items of slice s00cfe160 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cSummarizerBase {
public:
    virtual void v000();                                 // +0x00
};
class ContentValidationSummarizer {
public:
    virtual void v000();                                 // +0x00
};
extern float gField169d388;                              // 0x0169d388
extern float gField169d38c;                              // 0x0169d38c
extern float gField169d390;                              // 0x0169d390
class cSummarizer : public cSummarizerBase, public ContentValidationSummarizer {
public:
    cSummarizer();

    int32_t  mField08;                                   // +0x08
    int32_t  mField0C;                                   // +0x0c
    int32_t  mField10;                                   // +0x10
    int32_t  mField14;                                   // +0x14
    int32_t  mField18;                                   // +0x18
    float    mField1C;                                   // +0x1c
    float    mField20;                                   // +0x20
    float    mField24;                                   // +0x24
    int32_t  mField28;                                   // +0x28
};
class cGonzagoSubsystem {
public:
    cGonzagoSubsystem();                                 // 0x00b5b960
    virtual void v000();                                 // +0x00
};
class cSecondBase {
public:
    virtual void v000();                                 // +0x00
    uint8_t mPayload[0x14];                              // +0x04 .. +0x17
};
class cGonzagoChild : public cGonzagoSubsystem, public cSecondBase {
public:
    cGonzagoChild();

    int32_t mField1C;                                    // +0x1c
    int32_t mField20;                                    // +0x20
    int32_t mField24;                                    // +0x24
};
// ---- items of slice s00cfe160 end

// ---- items of slice s00cfeeb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
enum {
    kTypeCivilization = 0x901f1362,          // cCivilization::TYPE
    kTypeCity = 0xee9b2232,                  // cCity::TYPE

    kRelationshipEventCompliment = 0x0526e4e5,
    kRelationshipEventGift = 0x0526e4f2,
    kRelationshipEventBuyCityOver = 0x0526e4f5,
    kRelationshipEventJoinedAlliance = 0x0526e4f8,
    kRelationshipEventInsult = 0x0526e4fe,
    kRelationshipEventBuyCityUnder = 0x0526e50a,
    kRelationshipEventDemandRejected = 0x0526e50e,
    kRelationshipEventDeclaredWar = 0x0526e512,
    kRelationshipEventBrokeDeal = 0x05adb0aa,

    kCommEventTable = 0xdbf385bf             // group of the follow-up comm events
};
struct cCivilization_s00cf_eeb0;
struct cGameData_s00cf_eeb0 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Cast(uint32_t type);                      // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual uint32_t GetPoliticalID();                      // +0x4c
};
struct cCity_s00cf_eeb0 : cGameData_s00cf_eeb0 {
    cCivilization_s00cf_eeb0* GetCivilization();                       // 0x00bd9bf0
    void* SetPlayerRelation(uint32_t empire);               // 0x00bdf9e0
    void ChangeAllegiance(uint32_t empire, int kind, int a, int b);   // 0x00be9cb0
};
struct cCivProfile { char pad[0x504]; char mProfile504[1]; };
struct cCivilization_s00cf_eeb0 : cGameData_s00cf_eeb0 {
    uint32_t pad04[0xf];
    uint32_t mPoliticalID;                                  // +0x40
    uint32_t pad44[0x15];
    float mMoney;                                           // +0x98
    uint32_t pad9c[0xea];
    int mLastPurchasePrice;                                 // +0x444
    float mCityValue;                                       // +0x448

    void SpendMoney(float amount);                          // 0x00bef710
    void ReceiveMoney(float amount, bool bNotify);          // 0x00befd80
    void SetCityRelation(cCity_s00cf_eeb0* city, int relation);        // 0x00bef800
    void DeclareWarOn(cCity_s00cf_eeb0* city);                         // 0x00bf0d70
    int GetCapturedCount(int kind, bool b);                 // 0x00bf01f0
    void SetTradeRoutesActive(bool b);                      // 0x00bf04c0
    void CancelPurchase();                                  // 0x00bef5f0
    cCivProfile* GetProfile();                              // 0x00bef950
    void AcceptPeace();                                     // 0x00bf07c0
};
struct cGameNounManager_s00cf_eeb0 {
    cCivilization_s00cf_eeb0* GetPlayerCivilization();                 // 0x00b25fb0
    uint32_t GetPlayerEmpireOrMinus1();                     // 0x00b1f9d0
    struct CityVector { cCity_s00cf_eeb0** mpBegin; cCity_s00cf_eeb0** mpEnd; uint32_t pad[2]; }& GetCities();   // 0x00ace2c0
};
cGameNounManager_s00cf_eeb0* NounManager();                            // 0x00b3d300
struct cRelationshipManager_s00cf_eeb0 {
    float RecordEvent(uint32_t politicalID, uint32_t causePoliticalID, uint32_t eventID, float scale);   // 0x00d06240
};
cRelationshipManager_s00cf_eeb0* RelationshipManager();                // 0x00b3d2c0
struct cStarRecordRef { void* GetCommContext(); };          // 0x00ce6950 (returns [this+0x184])
struct cPlanet_s00cf_eeb0 { char pad[0x13c]; cStarRecordRef* mpStarRef; };   // +0x13c
cPlanet_s00cf_eeb0* GetActivePlanet();                                 // 0x01021260 cSPLivingUniverse::GetActivePlanet
struct cCommManager {
    void ShowCommEvent(cGameData_s00cf_eeb0* source, cCity_s00cf_eeb0* city, void* context, uint32_t group, uint32_t id, int flags);   // 0x00aeb760
    void CloseCommEvent();                                  // 0x00aea210
};
cCommManager* CommManager();                                // 0x00b3d4a0
struct cCivCommTuning { uint32_t pad[5]; int mAmounts[5]; }; // +0x14
extern cCivCommTuning* g_civCommTuning;                     // 0x0169d3c8
inline cCivCommTuning* CivCommTuning() { return g_civCommTuning; }
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
namespace SP {
cCivilization_s00cf_eeb0* AsCivilization(cGameData_s00cf_eeb0* source);            // 0x00ae9310: source ? source->Cast(cCivilization::TYPE) : 0
}
namespace SP {
cCity_s00cf_eeb0* FindTargetCity(int kind, cGameData_s00cf_eeb0* source);          // 0x00cfee00
}
namespace SP {
int GetTributeAmount(cCivilization_s00cf_eeb0* civ, cCity_s00cf_eeb0* city);       // 0x00cfe820
}
namespace SP {
bool IsAllied(cCivilization_s00cf_eeb0* civ);                           // 0x00cfe930
}
namespace SP {
void PostCivEvent(uint32_t id, char* a, char* b, const ResourceKey& key, uint32_t pa, uint32_t pb, int amount);   // 0x00e3c7c0
}
namespace SP {
static __forceinline void ShowReply(cGameData_s00cf_eeb0* source, cCity_s00cf_eeb0* city, uint32_t replyID)
{
    cStarRecordRef* pStarRef = GetActivePlanet()->mpStarRef;
    CommManager()->ShowCommEvent(source, city, pStarRef->GetCommContext(), kCommEventTable, replyID, 0);
}
}
namespace SP {
static __forceinline void RequestTargetCity(int kind, cGameData_s00cf_eeb0* source)
{
    cCity_s00cf_eeb0* target = FindTargetCity(kind, source);
    if (!target) {
        CommManager()->CloseCommEvent();
        return;
    }
    cCivilization_s00cf_eeb0* civ = AsCivilization(source);
    CivCommTuning()->mAmounts[0] = GetTributeAmount(civ, target);
    ShowReply(source, target, 0x2fc95198);
}
}
namespace SP {
#define ACTION(id) ((int)(id))
}
// ---- items of slice s00cfeeb0 end

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00572810();
extern "C" void fn_00572840();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00bca960();
extern "C" void fn_00b6f550();
extern "C" void fn_0057cde0();
extern "C" void fn_00aca060();
extern "C" void fn_00ae9e00();
extern "C" void fn_00692ff0();
extern "C" void fn_00694ee0();
extern "C" void fn_00b6e3a0();
extern "C" void fn_00ac88c0();
extern "C" void fn_006930f0();
extern "C" void fn_00695010();
extern "C" void fn_00acbba0();
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_01581d40, g_01581d7c, g_01581db8, g_01581df4, g_01581e30;
// ---- items of slice s0135d100 end

// @ 0x00cfeb40
void __cdecl FUN_00cfeb40()
{
}

// @ 0x00cfec10
__thiscall cSummarizer::cSummarizer()
{
    mField08 = 0;
    mField0C = 0;
    mField10 = 0;
    mField14 = -1;
    mField18 = -1;
    mField1C = gField169d388;
    mField20 = gField169d38c;
    mField24 = gField169d390;
    mField28 = 0;
}

// @ 0x00cfecc0
__thiscall cGonzagoChild::cGonzagoChild()
{
    mField1C = 0;
    mField20 = 0;
    mField24 = 0;
}

// @ 0x00cfee00
void __cdecl FindTargetCity()
{
}

// @ 0x00cfeeb0
namespace SP {
void DoCivCommAction(const int& action, cGameData_s00cf_eeb0* source, cCity_s00cf_eeb0* city)
{
    int buyIndex = -1;

    switch (action) {
    // ------------------------------------------------ stop trading
    case ACTION(0x96508a98):
    case ACTION(0xbf3b803a):
        {
            cCivilization_s00cf_eeb0* player = NounManager()->GetPlayerCivilization();
            player->SetTradeRoutesActive(false);
        }
        CommManager()->CloseCommEvent();
        return;

    // ------------------------------------------------ pay the other civ to declare war on a city
    case ACTION(0x91386d6c): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* cityCiv = city->GetCivilization();
        float cost = (float)g_civCommTuning->mAmounts[0];
        if (NounManager()->GetPlayerCivilization()->mMoney >= cost) {
            NounManager()->GetPlayerCivilization()->SpendMoney(cost);
            civ->ReceiveMoney(cost, true);
            civ->DeclareWarOn(city);
            RelationshipManager()->RecordEvent(cityCiv->GetPoliticalID(), civ->GetPoliticalID(), kRelationshipEventDeclaredWar, 1.0f);
            ShowReply(source, city, 0x1583d650);
            return;
        }
        CommManager()->CloseCommEvent();
        return;
    }

    // ------------------------------------------------ the other civ pays to join the alliance against a city
    case ACTION(0x9f0ff4cb): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* cityCiv = city->GetCivilization();
        civ->SpendMoney(2000.0f);
        NounManager()->GetPlayerCivilization()->ReceiveMoney(2000.0f, true);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventJoinedAlliance, 1.0f);
        RelationshipManager()->RecordEvent(cityCiv->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDeclaredWar, 1.0f);
        ShowReply(source, city, 0x92c5ebbc);
        return;
    }

    case ACTION(0xa51b201d):
        RequestTargetCity(9, source);
        return;

    // ------------------------------------------------ gifts of a fixed amount
    case ACTION(0xd648ed4d):
    case ACTION(0x410c4a65):
    case ACTION(0x5ea6d3ed): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        int amount;
        if (action == ACTION(0xd648ed4d))
            amount = 4000;
        else if (action == ACTION(0x5ea6d3ed))
            amount = 2000;
        else
            amount = 1000;
        float famount = (float)amount;
        if (NounManager()->GetPlayerCivilization()->mMoney >= famount) {
            NounManager()->GetPlayerCivilization()->SpendMoney(famount);
            civ->ReceiveMoney(famount, true);
            if (IsAllied(civ))
                amount /= 3;
            RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventGift, (float)(amount / 100));
            uint32_t civID = civ->mPoliticalID;
            PostCivEvent(0x9140a2e7, NounManager()->GetPlayerCivilization()->GetProfile()->mProfile504,
                         civ->GetProfile()->mProfile504, ResourceKey(),
                         NounManager()->GetPlayerCivilization()->mPoliticalID, civID, amount);
        }
        ShowReply(source, city, 0xd297847d);
        return;
    }

    // ------------------------------------------------ alliance against a city: the city's civ is told
    case ACTION(0xd50a1a6d): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* cityCiv = city->GetCivilization();
        cGameNounManager_s00cf_eeb0::CityVector& cities = NounManager()->GetCities();
        int n = cities.mpEnd - cities.mpBegin;
        for (int i = 0; i < n; i++) {
            cCity_s00cf_eeb0* other = cities.mpBegin[i];
            if (other->GetPoliticalID() == cityCiv->GetPoliticalID())
                other->SetPlayerRelation(NounManager()->GetPlayerEmpireOrMinus1());
        }
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventJoinedAlliance, 2.0f);
        RelationshipManager()->RecordEvent(cityCiv->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventBrokeDeal, 1.0f);
        ShowReply(source, city, 0x16952a08);
        return;
    }

    case ACTION(0xcadac8a0):
        {
            cCivilization_s00cf_eeb0* civ = AsCivilization(source);
            civ->SetCityRelation(city, 1);
        }
        CommManager()->CloseCommEvent();
        return;

    // ------------------------------------------------ break an alliance (penalty 4000)
    case ACTION(0xe7977907): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* cityCiv = city->GetCivilization();
        cGameNounManager_s00cf_eeb0::CityVector& cities = NounManager()->GetCities();
        int n = cities.mpEnd - cities.mpBegin;
        for (int i = 0; i < n; i++) {
            cCity_s00cf_eeb0* other = cities.mpBegin[i];
            uint32_t cityCivID = cityCiv->GetPoliticalID();
            uint32_t otherID = other->GetPoliticalID();
            if (otherID == cityCivID)
                other->SetPlayerRelation(NounManager()->GetPlayerEmpireOrMinus1());
        }
        civ->SpendMoney(4000.0f);
        NounManager()->GetPlayerCivilization()->ReceiveMoney(4000.0f, true);
        RelationshipManager()->RecordEvent(cityCiv->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventBrokeDeal, 1.0f);
        ShowReply(source, city, 0x9c22b3ae);
        return;
    }

    case ACTION(0x1125d6a9):
        {
            cCivilization_s00cf_eeb0* civ = AsCivilization(source);
            civ->SetCityRelation(city, 2);
        }
        CommManager()->CloseCommEvent();
        return;

    case ACTION(0x0764c336): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDemandRejected, 1.0f);
        ShowReply(source, city, 0x1c18780b);
        return;
    }

    case ACTION(0x18646f36): {
        cCity_s00cf_eeb0* target = FindTargetCity(7, source);
        if (!target) {
            CommManager()->CloseCommEvent();
            return;
        }
        cCivilization_s00cf_eeb0* civ = source ? (cCivilization_s00cf_eeb0*)source->Cast(kTypeCivilization) : 0;
        CivCommTuning()->mAmounts[0] = GetTributeAmount(civ, target);
        ShowReply(source, target, 0x2fc95198);
        return;
    }
    case ACTION(0x18646f3f): RequestTargetCity(0, source); return;
    case ACTION(0x18646f3c): RequestTargetCity(1, source); return;
    case ACTION(0x18646f3d): RequestTargetCity(2, source); return;
    case ACTION(0x18646f3a): RequestTargetCity(3, source); return;
    case ACTION(0x18646f3b): RequestTargetCity(4, source); return;
    case ACTION(0x18646f38): RequestTargetCity(5, source); return;
    case ACTION(0x18646f39): RequestTargetCity(6, source); return;
    case ACTION(0x18646f37): RequestTargetCity(8, source); return;

    // ------------------------------------------------ gift of the tuned amount
    case ACTION(0x23a2d684): {
        int amount = g_civCommTuning->mAmounts[0];
        cCivilization_s00cf_eeb0* civ = source ? (cCivilization_s00cf_eeb0*)source->Cast(kTypeCivilization) : 0;
        float famount = (float)amount;
        if (NounManager()->GetPlayerCivilization()->mMoney >= famount) {
            NounManager()->GetPlayerCivilization()->SpendMoney(famount);
            civ->ReceiveMoney(famount, true);
            if (IsAllied(civ))
                amount /= 2;
            RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventGift, (float)(amount / 400));
        }
        ShowReply(source, city, 0xfd02ed1b);
        return;
    }

    // ------------------------------------------------ hand over the cities of the source civ
    case ACTION(0x3ef09234): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* player = NounManager()->GetPlayerCivilization();
        int c0 = player->GetCapturedCount(0, false);
        int c1 = player->GetCapturedCount(1, false);
        int c2 = player->GetCapturedCount(2, false);
        int kind = 0;
        int best = c0;
        if (c1 > c0) {
            best = c1;
            kind = 1;
        }
        if (c2 > best)
            kind = 2;
        cGameNounManager_s00cf_eeb0::CityVector& cities = NounManager()->GetCities();
        int n = cities.mpEnd - cities.mpBegin;
        for (int i = 0; i < n; i++) {
            cCity_s00cf_eeb0* c = cities.mpBegin[i];
            if (c->GetCivilization() == civ)
                c->ChangeAllegiance(NounManager()->GetPlayerEmpireOrMinus1(), kind, 1, 1);
        }
        CommManager()->CloseCommEvent();
        return;
    }

    case ACTION(0x26b14441): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventInsult, 1.0f);
        ShowReply(source, city, 0xcf16a127);
        return;
    }

    case ACTION(0x24e1525d): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* cityCiv = city->GetCivilization();
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventJoinedAlliance, 5.0f);
        RelationshipManager()->RecordEvent(cityCiv->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDeclaredWar, 1.0f);
        ShowReply(source, city, 0x1c89b8da);
        return;
    }

    case ACTION(0x6ba64250): {
        CommManager()->CloseCommEvent();
        cCivilization_s00cf_eeb0* civ = source ? (cCivilization_s00cf_eeb0*)source->Cast(kTypeCivilization) : 0;
        if (!civ) {
            cCity_s00cf_eeb0* srcCity = source ? (cCity_s00cf_eeb0*)source->Cast(kTypeCity) : 0;
            civ = srcCity->GetCivilization();
        }
        civ->AcceptPeace();
        return;
    }

    // ------------------------------------------------ resume trading
    case ACTION(0x8650bd5b):
    case ACTION(0x6668560e):
        {
            cCivilization_s00cf_eeb0* player = NounManager()->GetPlayerCivilization();
            player->SetTradeRoutesActive(true);
        }
        CommManager()->CloseCommEvent();
        return;

    case ACTION(0x70c14c34): {
        cCivilization_s00cf_eeb0* civ = source ? (cCivilization_s00cf_eeb0*)source->Cast(kTypeCivilization) : 0;
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventCompliment, 1.0f);
        ShowReply(source, city, 0xcb8b690e);
        return;
    }

    // ------------------------------------------------ buy a city
    case ACTION(0x758330b8): buyIndex = 0; goto buy;
    case ACTION(0x758330bb): buyIndex = 1; goto buy;
    case ACTION(0x758330ba): buyIndex = 2; goto buy;
    case ACTION(0x758330bd): buyIndex = 3; goto buy;
    case ACTION(0x758330bc): buyIndex = 4;
    case ACTION(0xa3c1d501):
    buy: {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        cCivilization_s00cf_eeb0* player = NounManager()->GetPlayerCivilization();
        if (buyIndex != -1) {
            int price = g_civCommTuning->mAmounts[buyIndex];
            float value = player->mCityValue;
            float fprice = (float)price;
            if (!(fprice > player->mMoney)) {
                player->mLastPurchasePrice = price;
                uint32_t replyID;
                if (fprice >= value - 120.0f && value + 1200.0f > fprice) {
                    replyID = 0xe095755f;
                } else if (value > fprice && fprice >= value - 1200.0f) {
                    replyID = 0xccd90d2a;
                    RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventBuyCityUnder, -1.0f);
                } else if (value - 1200.0f > fprice) {
                    replyID = 0x28a66e39;
                    RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventBuyCityUnder, -3.0f);
                } else {
                    replyID = 0x647f97ad;
                    RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventBuyCityOver, 2.0f);
                }
                ShowReply(source, city, replyID);
                return;
            }
        }
        player->CancelPurchase();
        CommManager()->CloseCommEvent();
        return;
    }

    case ACTION(0x764ea37c): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDemandRejected, 1.0f);
        ShowReply(source, city, 0xe8835715);
        return;
    }
    case ACTION(0x789418dc): {
        cCivilization_s00cf_eeb0* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDemandRejected, 1.0f);
        ShowReply(source, city, 0x4db1ba15);
        return;
    }
    }
}
}  // namespace SP

// @ 0x01361ef0
void FUN_01361ef0()
{
    g_01581d40 = T("mpSource", 0x4473680u, 0xc, fn_00692ca0, fn_00aca060, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, (fp)0xac8050);
    g_01581d7c = T("mpTarget", 0x4473681u, 0x10, fn_00692ca0, fn_00ae9e00, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_01581db8 = T("mCommFileID", 0x4473682u, 0x14, fn_00692ca0, fn_00572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, fn_0057cde0);
    g_01581df4 = T("mCommGroupID", 0x4473683u, 0x18, fn_00692ca0, fn_00572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, fn_0057cde0);
    g_01581e30 = T("mPosition", 0x44dd929u, 0x1c, fn_00692ca0, fn_00b6e3a0, fn_00ac88c0, fn_006930f0, fn_00695010, fn_00b1fbf0, fn_00acbba0);
}
