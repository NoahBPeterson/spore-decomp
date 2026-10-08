// Slice s00aed700: planet/empire interaction flag builder (fills a 5-dword condition bitset).
// Flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (gives the fcompi float compare).
#include "types.h"

typedef unsigned int uint;

// ---- opaque / stub types ---------------------------------------------------------------------
struct StarRef;                      // opaque star handle (empire +0x84)
struct cPlanetRecord;
struct cPlanetRef;

struct BitsetFlags {
    uint mWord;
    bool test(uint bit) const { return ((mWord >> bit) & 1) != 0; }
};

struct cEmpire {
    char        pad0[0x50];
    BitsetFlags mFlags;              // +0x50
    int         mTrait;              // +0x54
    int         mArchetype;          // +0x58
    char        pad1[0x84 - 0x5c];
    StarRef*    mpStar;              // +0x84
    cPlanetRef* GetHomePlanet();         // 0x00c31730
    int         GetMoney();              // 0x00c30cb0
    bool        IsMilitaryEmpire();      // 0x00c313c0
    uint        GetWeaponryLevel();      // 0x00c317a0
};

struct cSPMissionObj204 {            // object returned by cSPMission::Cast(0x422227c)
    char pad[0x204];
    int  mnIndex;                    // +0x204
};
struct cSPMissionObj1f5 {            // object returned by cSPMission::Cast(0x35988ee)
    char pad[0x1f5];
    char mbFlag;                     // +0x1f5
    bool Check();                    // 0x00c609d0
};

struct cSPMission {
    // vtable: slot 3 (+0xc) = Cast, slot 78 (+0x138), slot 79 (+0x13c)
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* Cast(uint id);
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual bool vFlagA();           // +0x138
    virtual bool vFlagB();           // +0x13c
    char pad[0x184 - 4];
    int  mnLimitA;                   // +0x184
    int  mnLimitB;                   // +0x188
    cEmpire* GetOwnerEmpire();       // 0x00c451e0
    int  GetStateA();                // 0x00bddd00
    int  GetStateB();                // 0x00c44f10
};

struct cPlanetRef {
    char pad[0x184];
    int  mCommContext;               // +0x184
    int  GetCommContext();           // 0x00ce6950
    int  GetStarRecord();            // 0x00b8d8f0
};

struct cSPMissionManager {
    bool  IsPlanetARaidTarget(cPlanetRef* planet, int* pOut);                  // 0x00fee590
    void* GetActiveMissionForEmpire(cEmpire* e, cPlanetRef* planet);           // 0x00fee4f0
    int   HasMissionConversationWith(StarRef* star, int ctx);                  // 0x00fee6b0
    bool  HasPendingA(cEmpire* e, cPlanetRef* planet);                         // 0x00fee730
    bool  HasPendingB();                                                       // 0x00fee820
    bool  CountA();                                                            // 0x00feebb0
    bool  CountB();                                                            // 0x00feec30
    bool  CountC();                                                            // 0x00feecb0
};

struct cSPSimulatorSpaceGameInv {
    char  pad[0x508];
    struct IMeter { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual float Get(); } mMeter;   // +0x508, Get = slot 22 (+0x58)
    char  pad2[0x540 - 0x508 - 4];
    float mfValue;                   // +0x540
};
struct cSPSimulatorSpaceGame {
    cSPSimulatorSpaceGameInv* GetPlayerInventory();                           // 0x00a1ad60
    bool  PlayerHasStarOf(cEmpire* e);                                         // 0x00fff270
};
struct cTerrainSphere {
    char pad[0x124c];
    int  mnA;                        // +0x124c
    int  mnB;                        // +0x1250
    bool HasFlag(uint id);                                                     // 0x00c772c0
};
struct cTerrainEditor {
    char pad[0x74];
    cTerrainSphere* mpSphere;        // +0x74
    cTerrainSphere* GetCurrentTerrainSphere();                                // 0x00f67d90
};
struct RelationshipManager {
    bool  HasContact(StarRef* a, StarRef* b);                                  // 0x00d01b50
    uint  GetRelationLevel(StarRef* a, StarRef* b, int mode);                  // 0x00d00a70
    float GetRelationValue(StarRef* a, StarRef* b, int mode);                  // 0x00d00a10
    bool  IsAllied(cEmpire* a, cEmpire* b);                                    // 0x00d01f50
    bool  IsAtWar(cEmpire* a, cEmpire* b);                                     // 0x00d01ff0
};
struct cStarManager {
    int   LookupPlanetRecord(cPlanetRecord* r);                                // 0x00ba6dc0
    struct TradeInfo* GetTradeInfo();                                          // 0x00ba6490
};
struct TradeInfo {
    bool  CanTradeWith(int star, StarRef* s);                                  // 0x01037d30
    float SystemHasTradeRouteWithPlayer(int star, StarRef* s);                 // 0x01037dd0
};
struct cSPSpaceEconomyTuning {
    int   CalcAttackRequestCost(int rec);                                      // 0x01030650
    int   GetTradeCaptureOfferPrice(int i);                                    // 0x0102fa30
    int   GetPeaceOfferPrice(int i, cEmpire* e);                               // 0x01030930
};
struct cSPRelationshipTuning {
    char  pad[0x78];
    int   mnLimit0;                  // +0x78
    int   mnLimit1;                  // +0x7c
    int   mnLimit2;                  // +0x80
    int   GetTradeLimit(cEmpire* e);                                           // 0x010407d0
};
struct cPlayerTribe {
    uint  GetKind();                                                           // 0x00fe42a0
};
struct cSpaceGame {
    cPlayerTribe* GetPlayerTribe();                                           // 0x00bfc5f0
    char pad[0x70];
    cPlayerTribe* mpTribe;
};
struct cSimulatorUniverse {
    bool  CanSeePlanet(cPlanetRef* planet, cEmpire* e);                        // 0x0100e730
};
struct cAttackRequestPlanets {
    cPlanetRecord** mpBegin;         // 0x016decac
    cPlanetRecord** mpEnd;           // 0x016decb0
};

// ---- globals and cdecl accessors ---------------------------------------------------------------------
extern cAttackRequestPlanets g_016decac;     // 0x016decac
extern int                   g_015b751c;     // 0x015b751c (mTargetPlanetIndex)
extern cSimulatorUniverse*   g_016dc798;     // 0x016dc798 (cSimulatorUniverse::sInstance)

cSPSimulatorSpaceGame*  GetUFOSimulator();           // 0x00ffbe50
cSPMissionManager*      GetMissionManager();         // 0x00feb9f0
cEmpire*                GetPlayerEmpire();           // 0x01021300
cPlanetRef*             GetPlayerHomePlanet();       // 0x01021370
cTerrainEditor*         NounManager();               // 0x00b3d300
RelationshipManager*    GetRelationshipManager();    // 0x00b3d2c0
cStarManager*           StarManager();               // 0x00b3d2a0
cSPSpaceEconomyTuning*  GetSpaceEconomyTuning();     // 0x0102f810
cSPRelationshipTuning*  GetSpaceRelationshipTuning();// 0x010407c0
cSpaceGame*             SpaceGameGet();              // 0x01002bd0
int                     GetCurrentGameMode();        // 0x00b5b800
int                     CountTargets(cPlanetRef* planet, int kind);   // 0x00c705c0


// @ 0x00aed700
uint* __stdcall BuildPlanetFlags(uint* out, cEmpire* a, cEmpire* b, cPlanetRef* planet, cSPMission* mission)
{
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;

    cSPSimulatorSpaceGameInv* inv = GetUFOSimulator()->GetPlayerInventory();
    if (inv) {
        float fCur = inv->mfValue;
        if (fCur < inv->mMeter.Get())
            out[0] |= 0x80;
    }
    if (planet) {
        if (CountTargets(planet, 0) > 0)
            out[0] |= 0x10;
        int tmp;
        if (GetMissionManager()->IsPlanetARaidTarget(planet, &tmp))
            out[0] |= 0x100;
        else
            out[0] &= ~0x100u;
    }
    cEmpire* player = GetPlayerEmpire();
    if (a) {
        if (b) {
            int n = (int)(g_016decac.mpEnd - g_016decac.mpBegin);
            if (n >= 1) out[4] |= 0x1000;
            if (n >= 2) out[4] |= 0x2000;
            if (n >= 3) out[4] |= 0x4000;
            if (n >= 4) out[4] |= 0x8000;
            if (g_016decac.mpBegin != g_016decac.mpEnd && g_015b751c != -1) {
                cPlanetRecord* rec = g_016decac.mpBegin[g_015b751c];
                int cost = GetSpaceEconomyTuning()->CalcAttackRequestCost(StarManager()->LookupPlanetRecord(rec));
                if (cost <= player->GetMoney())
                    out[4] |= 0x10000;
            }
            if (b == a) {
                out[0] |= 2;
                if (planet) {
                    if (planet == b->GetHomePlanet())
                        out[0] |= 4;
                    else
                        out[0] |= 8;
                }
            }
            RelationshipManager* rm = GetRelationshipManager();
            if (a != b) {
                if (rm->HasContact(a->mpStar, b->mpStar)) {
                    switch (rm->GetRelationLevel(a->mpStar, b->mpStar, 1)) {
                    case 0:
                        out[1] |= 0x80000000;
                        out[2] |= 0x380;
                        break;
                    case 1:
                        out[2] |= 0x391;
                        break;
                    case 2:
                        out[2] |= 0x332;
                        break;
                    case 3:
                        out[2] |= 0x274;
                        break;
                    case 4:
                        out[2] |= 0x78;
                        break;
                    }
                }
                if (GetRelationshipManager()->IsAllied(a, b))
                    out[0] |= 0x40;
                if (GetRelationshipManager()->IsAtWar(a, b))
                    out[0] |= 0x20;
            }
            cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
            if (sphere->mnA > 0 && sphere->mnA > sphere->mnB)
                out[3] |= 0x20000;
            if (GetUFOSimulator()->PlayerHasStarOf(a))
                out[3] |= 0x10000;
            if (a != player && a->mFlags.test(6))
                out[1] |= 8;
            if (planet) {
                if (GetCurrentGameMode() == 0x1654c05 && g_016dc798) {
                    if (g_016dc798->CanSeePlanet(planet, a))
                        out[1] |= 0x10;
                    else
                        out[1] &= ~0x10u;
                }
                if (StarManager()->GetTradeInfo()->CanTradeWith(planet->GetStarRecord(), a->mpStar))
                    out[3] |= 0x40000;
                float fTrade = StarManager()->GetTradeInfo()->SystemHasTradeRouteWithPlayer(planet->GetStarRecord(), a->mpStar);
                if (100.0f <= fTrade)
                    out[3] |= 0x80000;
            }
            if (player) {
                int money = player->GetMoney();
                if (money >= GetSpaceEconomyTuning()->GetTradeCaptureOfferPrice(0)) out[3] |= 0x100000;
                if (money >= GetSpaceEconomyTuning()->GetTradeCaptureOfferPrice(1)) out[3] |= 0x200000;
                if (money >= GetSpaceEconomyTuning()->GetTradeCaptureOfferPrice(2)) out[3] |= 0x400000;
                if (money >= GetSpaceEconomyTuning()->GetTradeCaptureOfferPrice(3)) out[3] |= 0x800000;
                if (money >= GetSpaceEconomyTuning()->GetTradeCaptureOfferPrice(4)) out[3] |= 0x1000000;
                if (money >= GetSpaceEconomyTuning()->GetPeaceOfferPrice(0, a)) out[3] |= 0x2000000;
                if (money >= GetSpaceEconomyTuning()->GetPeaceOfferPrice(1, a)) out[3] |= 0x4000000;
                if (money >= GetSpaceEconomyTuning()->GetPeaceOfferPrice(2, a)) out[3] |= 0x8000000;
                if (money >= GetSpaceEconomyTuning()->GetPeaceOfferPrice(3, a)) out[3] |= 0x10000000;
                if (money >= GetSpaceEconomyTuning()->GetPeaceOfferPrice(4, a)) out[3] |= 0x20000000;
                if (money >= GetSpaceRelationshipTuning()->GetTradeLimit(a)) out[3] |= 0x40000000;
            }
        }
        if (a != GetPlayerEmpire()) {
            switch (a->mArchetype) {
            case 0: case 9: case 18:
                out[0] |= 0x10200;
                break;
            case 1: case 10:
                out[0] |= 0x24000;
                break;
            case 2: case 11:
                out[0] |= 0x41000;
                break;
            case 3: case 12:
                out[0] |= 0x80400;
                break;
            case 4: case 13:
                out[0] |= 0x102000;
                break;
            case 5: case 14:
                out[0] |= 0x200200;
                break;
            case 6: case 15: case 17:
                out[0] |= 0x400800;
                break;
            case 7: case 16:
                out[0] |= 0x801000;
                break;
            case 8:
                out[0] |= 0x1008000;
                break;
            }
        }
        RelationshipManager* rm2 = GetRelationshipManager();
        if (a->IsMilitaryEmpire()) {
            if (a == player || 0.0f < rm2->GetRelationValue(a->mpStar, player->mpStar, 0))
                out[1] |= 0x20;
        }
        switch (a->mTrait) {
        case 1: out[1] |= 0x200; break;
        case 2: out[1] |= 0x400; break;
        case 3: out[1] |= 0x800; break;
        }
        switch (a->GetWeaponryLevel()) {
        case 0: case 1: case 2:
            out[4] |= 0x400000;
            break;
        case 3:
            out[4] |= 0x200000;
            break;
        case 4: case 5:
            out[4] |= 0x100000;
            break;
        }
        cTerrainSphere* sphere2 = NounManager()->GetCurrentTerrainSphere();
        if (a != player && sphere2->HasFlag(0x5f1f0bc) && !sphere2->HasFlag(0x5f1f0ca))
            out[1] |= 0x1000;
        else
            out[1] &= ~0x1000u;
        if (a == player && planet == GetPlayerHomePlanet()) {
            if (GetMissionManager()->CountA())
                out[4] |= 0x800000;
            if (GetMissionManager()->CountB())
                out[4] |= 0x1000000;
            if (GetMissionManager()->CountC())
                out[4] |= 0x2000000;
        }
    }
    if (NounManager() && NounManager()->GetCurrentTerrainSphere()
        && NounManager()->GetCurrentTerrainSphere()->HasFlag(0x5f1f0cb))
        out[3] |= 0x80000000;
    if (mission) {
        cEmpire* owner = mission->GetOwnerEmpire();
        if (owner) {
            switch (owner->mArchetype) {
            case 0: out[0] |= 0x2000000; break;
            case 1: out[0] |= 0x4000000; break;
            case 2: out[0] |= 0x8000000; break;
            case 3: out[0] |= 0x10000000; break;
            case 4: out[0] |= 0x20000000; break;
            case 5: out[0] |= 0x40000000; break;
            case 6: out[0] |= 0x80000000; break;
            case 7: out[1] |= 1; break;
            case 8: out[1] |= 2; break;
            }
            if (owner == player)
                out[1] |= 4;
        }
        switch (mission->GetStateA()) {
        case 0: out[1] |= 0x8000; break;
        case 1: out[1] |= 0x4000; break;
        }
        switch (mission->GetStateB()) {
        case 0: out[1] |= 0x10000; break;
        case 1: out[1] |= 0x20000; break;
        }
        if (mission->vFlagA())
            out[1] |= 0x1000000;
        else
            out[1] &= ~0x1000000u;
        if (mission->vFlagB())
            out[1] |= 0x2000000;
        else
            out[1] &= ~0x2000000u;
        cSPMissionObj204* o204 = (cSPMissionObj204*)mission->Cast(0x422227c);
        if (o204 && o204->mnIndex >= 0) {
            uint bit = o204->mnIndex + 0x3a;
            if (bit < 0x9a)
                out[bit >> 5] |= 1u << (bit & 0x1f);
        }
        cSPMissionObj1f5* o1f5 = (cSPMissionObj1f5*)mission->Cast(0x35988ee);
        if (o1f5) {
            if (o1f5->Check())
                out[4] |= 0x20000;
            else
                out[4] &= ~0x20000u;
            if (o1f5->mbFlag)
                out[4] |= 0x40000;
            else
                out[4] &= ~0x40000u;
        }
        int limA = mission->mnLimitA;
        if (limA <= GetPlayerEmpire()->GetMoney())
            out[1] |= 0x100000;
        else
            out[1] &= ~0x100000u;
        int limB = mission->mnLimitB;
        if (limB <= GetPlayerEmpire()->GetMoney())
            out[1] |= 0x200000;
        else
            out[1] &= ~0x200000u;
    }
    if (a && planet) {
        if (GetMissionManager()->GetActiveMissionForEmpire(a, planet))
            out[1] |= 0x80000;
        else
            out[1] &= ~0x80000u;
        StarRef* star = a->mpStar;
        if (GetMissionManager()->HasMissionConversationWith(star, planet->GetCommContext()) > 0)
            out[1] |= 0x40000;
        else
            out[1] &= ~0x40000u;
        if (GetMissionManager()->HasPendingA(a, planet))
            out[1] |= 0x400000;
        else
            out[1] &= ~0x400000u;
        if (GetMissionManager()->HasPendingB())
            out[1] |= 0x800000;
        else
            out[1] &= ~0x800000u;
    }
    if (player) {
        int money2 = player->GetMoney();
        if (money2 >= GetSpaceRelationshipTuning()->mnLimit0) out[1] |= 0x40;
        if (money2 >= GetSpaceRelationshipTuning()->mnLimit1) out[1] |= 0x80;
        if (money2 >= GetSpaceRelationshipTuning()->mnLimit2) out[1] |= 0x100;
    }
    switch (SpaceGameGet()->GetPlayerTribe()->GetKind()) {
    case 0:  out[4] |= 1; break;
    case 1:  out[4] |= 2; break;
    case 2:  out[4] |= 4; break;
    case 3:  out[4] |= 8; break;
    case 4:  out[4] |= 0x10; break;
    case 5:  out[4] |= 0x20; break;
    case 6:  out[4] |= 0x40; break;
    case 7:  out[4] |= 0x80; break;
    case 8:  out[4] |= 0x100; break;
    case 9:  out[4] |= 0x200; break;
    case 10: out[4] |= 0x400; break;
    }
    if (NounManager()->GetCurrentTerrainSphere()->HasFlag(0x4ed001a))
        out[4] |= 0x800;
    return out;
}
