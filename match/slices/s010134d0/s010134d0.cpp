// Slice s010134d0 -- SP::cSimulatorUniverse::UpdateEmpireAlliancesAndWars.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The simulator updates the player's relationship record with every other
// empire.  Depending on whether the pair is at war / allied and on the current
// relationship value against the relationship simulator's tuning values, it
// posts a relationship event and then writes the new value back into the
// universe's per-empire float map at +0x198.
#include "types.h"

struct cEmpire;
struct cRelationshipManager;

struct cEmpire {
    uint8_t  mPad_00[0x84];                 // 0x00
    uint32_t mId_84;                        // 0x84
    // Trivial accessor for mId_84.  Spelling the id reads as `empire->GetId()`
    // rather than `empire->mId_84` keeps the same instructions but shifts
    // cl 15's whole-function scratch-register rotation onto retail's picks
    // (eax/ecx instead of ecx/edx, and the 5-byte `mov eax, ds:[global]`).
    uint32_t GetId() const { return mId_84; }
    void*    GetHomePlanet();               // 0x00c31730
};

class cRelationshipManager {
public:
    float GetRelationship(uint32_t a, uint32_t b, int32_t c); // 0x00d00a10
    bool  IsAtWar(cEmpire* a, cEmpire* b);                    // 0x00d01ff0
    bool  IsAllied(cEmpire* a, cEmpire* b);                   // 0x00d01f50
    void  EndAlliance(cEmpire* a, cEmpire* b);                // 0x00d01e30
    void  FUN_00d065a0(cEmpire* a, cEmpire* b);               // 0x00d065a0
    bool  GetFlag8(uint32_t a, uint32_t b);                   // 0x00d038a0
    void  SetFlag8(uint32_t a, uint32_t b, bool value);       // 0x00d03860
    void  StartPeace(cEmpire* a, cEmpire* b);                 // 0x00d038e0
};

struct cTimeManager {
    float FUN_01040840();                   // 0x01040840
    float FUN_01040850();                   // 0x01040850
    float FUN_00cbcaf0();                   // 0x00cbcaf0
    float FUN_00b7e0a0();                   // 0x00b7e0a0
};

struct cFloatMap {
    float* Index(const uint32_t* key);      // 0x00c8c550
};

struct cEventContext {
    uint8_t  mPad_00[0x1c];                 // 0x00
    cEmpire* mpEmpire_1c;                   // 0x1c
};

struct cEventRecord {
    void Post();                            // 0x00dd8640
};

struct cNounManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void Notify(uint32_t, uint32_t, uint32_t, uint32_t);
};

struct cTerrainSphere {
    bool FUN_00c75650();                    // 0x00c75650
};

struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere(); // 0x00f67d90
};

struct cRelationshipPlanet {
    void* GetCommContext();                 // 0x00ce6950
};

struct cSomeObject {
    void FUN_00fe5430(int32_t a, int32_t b); // 0x00fe5430
};

struct cSomeSingleton {
    cSomeObject* FUN_00bfc5f0();             // 0x00bfc5f0
};

struct tAllianceSnapshot {
    uint32_t m00;                           // 0x00
    uint32_t m04;                           // 0x04
    uint32_t m08;                           // 0x08
    uint32_t m0c;                           // 0x0c
    uint32_t m10;                           // 0x10
    uint32_t m14;                           // 0x14
    uint32_t m18;                           // 0x18
    uint32_t m1c;                           // 0x1c
    uint32_t m20;                           // 0x20
    uint32_t m24;                           // 0x24
    uint32_t m28;                           // 0x28
    uint32_t m2c;                           // 0x2c
};

extern cEventContext* g_16e0d08;             // the relationship event context

cRelationshipManager* __cdecl RelationshipManager();       // 0x00b3d2c0
cTimeManager*         __cdecl TimeManager_010407c0();      // 0x010407c0
cEventRecord* __stdcall EventLog(uint32_t eventId, uint32_t text,
                                 uint32_t a, uint32_t b,
                                 uint32_t c, uint32_t d);  // 0x00b3d3e0
cNounManager*         __cdecl NounManager_0067dcc0();      // 0x0067dcc0
cTerrainEditor*       __cdecl NounManager_00b3d300();      // 0x00b3d300
cSomeSingleton*       __cdecl GetSomeSingleton_01002bd0(); // 0x01002bd0
void __cdecl FUN_00e39ab0(uint32_t key, cEmpire* empire,
                          void* a, void* b, void* context,
                          uint32_t zero, void* c, void* d); // 0x00e39ab0

struct cSimulatorUniverse {
    uint8_t   mPad_00[0x198];               // 0x00
    cFloatMap mRelationshipMap_198;         // 0x198

    cEmpire* GetPlayerEmpire();             // 0x01021300
    void UpdateEmpireAlliancesAndWars(cEmpire* empire, float dt); // 0x010134d0
};

// @ 0x010134d0
void cSimulatorUniverse::UpdateEmpireAlliancesAndWars(cEmpire* empire, float dt)
{
    (void)dt;

    cEmpire* player = GetPlayerEmpire();
    if (empire == player)
        return;

    uint32_t empireId = empire->GetId();
    uint32_t relationshipKey = empireId;
    float first;
    cRelationshipManager* rel = RelationshipManager();
    float value = rel->GetRelationship(empireId, player->GetId(), 0);

    if (rel->IsAtWar(empire, player)) {
        first = TimeManager_010407c0()->FUN_01040840();
        float second = TimeManager_010407c0()->FUN_01040850();
        if (second > value) {
            g_16e0d08->mpEmpire_1c = empire;
            EventLog(0x4ca76fbdu, 0x131a9f54u, 0, 0, 1, 0)->Post();
            rel->EndAlliance(empire, player);
            NounManager_0067dcc0()->Notify(0x43f2585u, 0, 0, 0);
        } else if (first > value) {
            float* slot = mRelationshipMap_198.Index(&relationshipKey);
            if (*slot >= first) {
                g_16e0d08->mpEmpire_1c = empire;
                EventLog(0x2194609du, 0x131a9f54u, 0, 0, 1, 0)->Post();
            }
        }
    }

    bool allied = rel->IsAllied(empire, player);
    float rate = TimeManager_010407c0()->FUN_00cbcaf0();

    if (!allied) {
        if (rate > value) {
            rel->FUN_00d065a0(empire, player);
            NounManager_0067dcc0()->Notify(0x43f2585u, 0, 0, 0);

            if (!rel->GetFlag8(empire->GetId(), player->GetId())) {
                cSomeObject* object = GetSomeSingleton_01002bd0()->FUN_00bfc5f0();
                if (object)
                    object->FUN_00fe5430(5, 1);
            }

            tAllianceSnapshot snapshot;
            snapshot.m00 = 0;
            snapshot.m04 = 0;
            snapshot.m08 = 0;
            snapshot.m0c = 0;
            snapshot.m10 = 0;
            snapshot.m14 = 0;
            snapshot.m18 = 0;
            snapshot.m1c = 0;
            snapshot.m20 = 0;
            snapshot.m24 = 0;
            snapshot.m28 = 0;
            snapshot.m2c = 0;

            FUN_00e39ab0(0xafd2b265u, empire, &snapshot.m24, &snapshot.m18,
                         ((cRelationshipPlanet*)empire->GetHomePlanet())
                             ->GetCommContext(),
                         0, &snapshot.m0c, &snapshot.m00);
        }
    } else {
        float threshold = TimeManager_010407c0()->FUN_00b7e0a0();
        if (value > threshold) {
            g_16e0d08->mpEmpire_1c = empire;
            EventLog(0xbdfd6ec3u, 0x131a9f54u, 0, 0, 1, 0)->Post();
            RelationshipManager()->StartPeace(empire, player);
            if (NounManager_00b3d300()->GetCurrentTerrainSphere()->FUN_00c75650())
                rel->SetFlag8(empire->GetId(), player->GetId(), true);
        }
    }

    // The original emits this terrain check after the allied block, i.e. as a
    // second `if (!allied)` at function scope.  cl folds the redundant test
    // (`allied` is known false on every path that reaches it), which is what
    // reproduces retail's block order exactly.
    if (!allied) {
        if (!NounManager_00b3d300()->GetCurrentTerrainSphere()->FUN_00c75650())
            rel->SetFlag8(empire->GetId(), player->GetId(), false);
    }

    *mRelationshipMap_198.Index(&relationshipKey) = value;
}
