// Slice s00cfeeb0 -- SP::DoCivCommAction (0x00cfeeb0, 3740 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same Civ-mode module as s00cfbc10).
//
// Executes the player's answer in a Civilization-mode communication screen. The action id is a
// hash; per action the function charges/transfers money, records relationship events with the
// relationship manager, changes city/civilization state and then either opens the follow-up
// comm event (CommManager()->ShowCommEvent(source, city, ..., 0xdbf385bf, <reply id>, 0)) or
// closes the comm screen (CommManager()->CloseCommEvent()).
// Relationship event ids are the ModAPI kRelationshipEvent* values; most callees are only known
// by address and are modelled as small stub classes.
#include "types.h"

// ---------------------------------------------------------------- ids
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

// ---------------------------------------------------------------- game objects
struct cCivilization;

struct cGameData {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Cast(uint32_t type);                      // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual uint32_t GetPoliticalID();                      // +0x4c
};

struct cCity : cGameData {
    cCivilization* GetCivilization();                       // 0x00bd9bf0
    void* SetPlayerRelation(uint32_t empire);               // 0x00bdf9e0
    void ChangeAllegiance(uint32_t empire, int kind, int a, int b);   // 0x00be9cb0
};

struct cCivProfile { char pad[0x504]; char mProfile504[1]; };

struct cCivilization : cGameData {
    uint32_t pad04[0xf];
    uint32_t mPoliticalID;                                  // +0x40
    uint32_t pad44[0x15];
    float mMoney;                                           // +0x98
    uint32_t pad9c[0xea];
    int mLastPurchasePrice;                                 // +0x444
    float mCityValue;                                       // +0x448

    void SpendMoney(float amount);                          // 0x00bef710
    void ReceiveMoney(float amount, bool bNotify);          // 0x00befd80
    void SetCityRelation(cCity* city, int relation);        // 0x00bef800
    void DeclareWarOn(cCity* city);                         // 0x00bf0d70
    int GetCapturedCount(int kind, bool b);                 // 0x00bf01f0
    void SetTradeRoutesActive(bool b);                      // 0x00bf04c0
    void CancelPurchase();                                  // 0x00bef5f0
    cCivProfile* GetProfile();                              // 0x00bef950
    void AcceptPeace();                                     // 0x00bf07c0
};

struct cGameNounManager {
    cCivilization* GetPlayerCivilization();                 // 0x00b25fb0
    uint32_t GetPlayerEmpireOrMinus1();                     // 0x00b1f9d0
    struct CityVector { cCity** mpBegin; cCity** mpEnd; uint32_t pad[2]; }& GetCities();   // 0x00ace2c0
};
cGameNounManager* NounManager();                            // 0x00b3d300

struct cRelationshipManager {
    float RecordEvent(uint32_t politicalID, uint32_t causePoliticalID, uint32_t eventID, float scale);   // 0x00d06240
};
cRelationshipManager* RelationshipManager();                // 0x00b3d2c0

struct cStarRecordRef { void* GetCommContext(); };          // 0x00ce6950 (returns [this+0x184])
struct cPlanet { char pad[0x13c]; cStarRecordRef* mpStarRef; };   // +0x13c
cPlanet* GetActivePlanet();                                 // 0x01021260 cSPLivingUniverse::GetActivePlanet

struct cCommManager {
    void ShowCommEvent(cGameData* source, cCity* city, void* context, uint32_t group, uint32_t id, int flags);   // 0x00aeb760
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
cCivilization* AsCivilization(cGameData* source);            // 0x00ae9310: source ? source->Cast(cCivilization::TYPE) : 0
cCity* FindTargetCity(int kind, cGameData* source);          // 0x00cfee00
int GetTributeAmount(cCivilization* civ, cCity* city);       // 0x00cfe820
bool IsAllied(cCivilization* civ);                           // 0x00cfe930
void PostCivEvent(uint32_t id, char* a, char* b, const ResourceKey& key, uint32_t pa, uint32_t pb, int amount);   // 0x00e3c7c0


static __forceinline void ShowReply(cGameData* source, cCity* city, uint32_t replyID)
{
    cStarRecordRef* pStarRef = GetActivePlanet()->mpStarRef;
    CommManager()->ShowCommEvent(source, city, pStarRef->GetCommContext(), kCommEventTable, replyID, 0);
}

static __forceinline void RequestTargetCity(int kind, cGameData* source)
{
    cCity* target = FindTargetCity(kind, source);
    if (!target) {
        CommManager()->CloseCommEvent();
        return;
    }
    cCivilization* civ = AsCivilization(source);
    CivCommTuning()->mAmounts[0] = GetTributeAmount(civ, target);
    ShowReply(source, target, 0x2fc95198);
}

#define ACTION(id) ((int)(id))

// @ 0x00cfeeb0
void DoCivCommAction(const int& action, cGameData* source, cCity* city)
{
    int buyIndex = -1;

    switch (action) {
    // ------------------------------------------------ stop trading
    case ACTION(0x96508a98):
    case ACTION(0xbf3b803a):
        {
            cCivilization* player = NounManager()->GetPlayerCivilization();
            player->SetTradeRoutesActive(false);
        }
        CommManager()->CloseCommEvent();
        return;

    // ------------------------------------------------ pay the other civ to declare war on a city
    case ACTION(0x91386d6c): {
        cCivilization* civ = AsCivilization(source);
        cCivilization* cityCiv = city->GetCivilization();
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
        cCivilization* civ = AsCivilization(source);
        cCivilization* cityCiv = city->GetCivilization();
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
        cCivilization* civ = AsCivilization(source);
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
        cCivilization* civ = AsCivilization(source);
        cCivilization* cityCiv = city->GetCivilization();
        cGameNounManager::CityVector& cities = NounManager()->GetCities();
        int n = cities.mpEnd - cities.mpBegin;
        for (int i = 0; i < n; i++) {
            cCity* other = cities.mpBegin[i];
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
            cCivilization* civ = AsCivilization(source);
            civ->SetCityRelation(city, 1);
        }
        CommManager()->CloseCommEvent();
        return;

    // ------------------------------------------------ break an alliance (penalty 4000)
    case ACTION(0xe7977907): {
        cCivilization* civ = AsCivilization(source);
        cCivilization* cityCiv = city->GetCivilization();
        cGameNounManager::CityVector& cities = NounManager()->GetCities();
        int n = cities.mpEnd - cities.mpBegin;
        for (int i = 0; i < n; i++) {
            cCity* other = cities.mpBegin[i];
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
            cCivilization* civ = AsCivilization(source);
            civ->SetCityRelation(city, 2);
        }
        CommManager()->CloseCommEvent();
        return;

    case ACTION(0x0764c336): {
        cCivilization* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDemandRejected, 1.0f);
        ShowReply(source, city, 0x1c18780b);
        return;
    }

    case ACTION(0x18646f36): {
        cCity* target = FindTargetCity(7, source);
        if (!target) {
            CommManager()->CloseCommEvent();
            return;
        }
        cCivilization* civ = source ? (cCivilization*)source->Cast(kTypeCivilization) : 0;
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
        cCivilization* civ = source ? (cCivilization*)source->Cast(kTypeCivilization) : 0;
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
        cCivilization* civ = AsCivilization(source);
        cCivilization* player = NounManager()->GetPlayerCivilization();
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
        cGameNounManager::CityVector& cities = NounManager()->GetCities();
        int n = cities.mpEnd - cities.mpBegin;
        for (int i = 0; i < n; i++) {
            cCity* c = cities.mpBegin[i];
            if (c->GetCivilization() == civ)
                c->ChangeAllegiance(NounManager()->GetPlayerEmpireOrMinus1(), kind, 1, 1);
        }
        CommManager()->CloseCommEvent();
        return;
    }

    case ACTION(0x26b14441): {
        cCivilization* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventInsult, 1.0f);
        ShowReply(source, city, 0xcf16a127);
        return;
    }

    case ACTION(0x24e1525d): {
        cCivilization* civ = AsCivilization(source);
        cCivilization* cityCiv = city->GetCivilization();
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventJoinedAlliance, 5.0f);
        RelationshipManager()->RecordEvent(cityCiv->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDeclaredWar, 1.0f);
        ShowReply(source, city, 0x1c89b8da);
        return;
    }

    case ACTION(0x6ba64250): {
        CommManager()->CloseCommEvent();
        cCivilization* civ = source ? (cCivilization*)source->Cast(kTypeCivilization) : 0;
        if (!civ) {
            cCity* srcCity = source ? (cCity*)source->Cast(kTypeCity) : 0;
            civ = srcCity->GetCivilization();
        }
        civ->AcceptPeace();
        return;
    }

    // ------------------------------------------------ resume trading
    case ACTION(0x8650bd5b):
    case ACTION(0x6668560e):
        {
            cCivilization* player = NounManager()->GetPlayerCivilization();
            player->SetTradeRoutesActive(true);
        }
        CommManager()->CloseCommEvent();
        return;

    case ACTION(0x70c14c34): {
        cCivilization* civ = source ? (cCivilization*)source->Cast(kTypeCivilization) : 0;
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
        cCivilization* civ = AsCivilization(source);
        cCivilization* player = NounManager()->GetPlayerCivilization();
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
        cCivilization* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDemandRejected, 1.0f);
        ShowReply(source, city, 0xe8835715);
        return;
    }
    case ACTION(0x789418dc): {
        cCivilization* civ = AsCivilization(source);
        RelationshipManager()->RecordEvent(civ->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), kRelationshipEventDemandRejected, 1.0f);
        ShowReply(source, city, 0x4db1ba15);
        return;
    }
    }
}
}  // namespace SP
