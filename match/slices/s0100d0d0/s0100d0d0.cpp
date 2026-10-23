// Slice s0100d0d0 -- SP::cSPSimulatorSpaceGame per-tick update path plus the
// cSimulatorUniverse event serializers and the space-game sort/selection helpers.
//
//  0100d0d0  cSPSimulatorSpaceGame::GalaxyUpdate        (galaxy-mode tick + UFO transition test)
//  0100d230  cSPSimulatorSpaceGame::GameUpdate          (dispatch on the living-universe context)
//  0100d2a0  cSPSimulatorSpaceGame::OnTick              (full tick: tick sub-updates, event ageing)
//  0100d410  cSPSimulatorSpaceGame::GetTimerSeconds     (elapsed timer in seconds)
//  0100d500  ProbabilityFromRatio                       (1 - e^(value/max * log10(0.5)))
//  0100d560  cSimulatorUniverse::Write                  (event-frequency fields + var list)
//  0100d790  cSimulatorUniverse::Read
//  0100d960  CompareProtectorDistances                  (anonymous namespace compare)
//  0100d9f0  cGrobShockSelection::Reset                 (two dwords)
//  0100da10  cGrobShockSelection::Get                   (checked dword read-out)
//  0100da40  sCompareGrobShockData                      (anonymous namespace, timer compare)
//  0100daa0  DestroyTimerRange                          (destroys cGonzagoTimer in [first,last))
//  0100dae0  SumOfOtherCivValues                        (sum over the available-civ list)
//  0100db40  BioProtectorSort::operator()               (closer of two cities to a position)
//  0100dc20  BioProtectorSort::CompareAndCheck          (occupancy gate + city distance test)
//  0100dd40  AverageEmpireDistance                      (weighted relation average, clamped)
//  0100dfb0  SP::WarAttackEvent::GetEventFrequency
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no unwind frames in this slice).
#include "types.h"
#include <algorithm>
#include <intrin.h>
#include <math.h>
#include <new>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// ---------------------------------------------------------------------------------------------
// Small interfaces shared by the update path.
struct cStreamObj {
    PV4 PV2
    virtual cStreamObj* GetStream();        // +0x18
};

// The output stream handed to the serializers.
struct cOutStream {
    PV8
    virtual cStreamObj* GetStreamObj();     // +0x20
};

struct cAppSystem {
    PV16 PV4
    virtual void* GetSubSystem();           // +0x50
};

struct cSubSystem {
    PV8 PV4 PV2
    virtual void* GetService();             // +0x38
};

struct cServiceHost {
    PV2 PV
    virtual void* Find(uint32_t id);        // +0x0c
};

struct cEffectHost {
    PV16 PV4 PV2 PV
    virtual float GetRadius();              // +0x5c
    uint8_t pad04[0xd1];
    uint8_t mbD5;                           // +0xd5
};

// The supplied game-time manager: +0x48 holds the pause/step bits.
struct cGameTimeManager {
    uint8_t pad00[0x48];
    uint8_t mb48;                           // +0x48
};

// The UFO simulator and its player inventory (inventory has a busy flag at +0x74c).
struct cPlayerInventory {
    uint8_t pad000[0x74c];
    uint8_t mb74c;                          // +0x74c
};

struct cUFOSimulator {
    cPlayerInventory* GetPlayerInventory(); // 0x00a1ad60
    float GetMaxTravelDistance();           // 0x00ffbfc0
};

// The app-mode object used for the galaxy -> solar transition.
struct cAppModeSpace {
    void TransitionFromGalaxyToSolar();     // 0x00fdd5a0
};

// Timers: 64-bit elapsed time in timer units (milliseconds).
class cSPTimer {
public:
    uint64_t GetElapsedTime();              // 0x00bc3190
};

class cGonzagoTimer {
public:
    uint8_t pad00[8];
    void Destroy();                         // 0x00b638b0
};

// A space-game event entry (0x1c bytes): aged by the tick.
struct cSpaceEvent {
    void* mv00;                 // +0x00
    void* mv04;                 // +0x04
    void* mv08;                 // +0x08
    uint32_t mu0C;              // +0x0c
    uint32_t mu10;              // +0x10
    float mf14;                 // +0x14
    uint32_t mu18;              // +0x18
};

// The editor-side helper hung off cSPSimulatorSpaceGame::mp14 and its current object.
struct cSimObject {
    void Update();              // 0x00e0e1a0
};
struct cEditorHelper {
    cSimObject* GetSimObject(); // 0x01067e60
};

// The optional per-system updater behind +0x54.
struct cSpaceUpdater {
    PV4
    virtual void Update(uint32_t arg0, uint32_t arg1);   // +0x10
};

// cSPSimulatorSpaceGame (only the members this slice touches).
struct cSPSimulatorSpaceGame {
    uint8_t pad00[0x14];
    cEditorHelper* mp14;        // +0x14 (editor-side helper object)
    uint8_t pad18[0x3c];
    cSpaceUpdater* mp54;        // +0x54 (optional per-system updater)
    uint8_t pad58[0x70];
    cSpaceEvent* mpEventsC8;    // +0xc8 (event vector begin)
    cSpaceEvent* mpEventsCC;    // +0xcc (event vector end)
    uint8_t padD0[0xc8];
    cSPTimer mTimer;            // +0x198

    void GalaxyUpdate(uint32_t elapsedMS);      // 0x0100d0d0
    void GameUpdate(uint32_t arg);              // 0x0100d230
    void OnTick(uint32_t arg0, uint32_t arg1);  // 0x0100d2a0
    float GetTimerSeconds();                    // 0x0100d410
    void AdvanceTimer(float seconds);           // 0x01008e60
    void OnPreTick();                           // 0x01006370
    static int GetUniverseContext();            // 0x01021080
    bool IsZoomedOut();                         // 0x00b18e40
    void SolarSystemUpdate(uint32_t arg);       // 0x01009df0
    void UpdateUFOStatusEffects();              // 0x0100a080
    void GalaxyUpdateNPC_UFOs(uint32_t elapsedMS);  // 0x0100b430
    void GalaxyTestForIntercept();              // 0x01008910
    void UpdateEmpireHud(uint32_t arg0, uint32_t arg1);  // 0x0100a160
};

// cSimulatorUniverse: the serialized event frequencies (only the members this slice touches).
struct cVarList;
class cVarListSerializer {
public:
    cVarListSerializer(cVarList* pList, const char* pName, uint32_t id);   // 0x00692f90
    bool Serialize(cOutStream* pOut);                                      // 0x00692900
    bool SerializeRead(cOutStream* pOut);                                  // 0x00693e10
    uint8_t mBuffer[0xa00];     // inline stream buffer (object size pinned by the frame)
};

struct cSimulatorUniverse {
    uint8_t pad00[0x40];
    uint64_t mFirstEvent;       // +0x40
    uint64_t mSecondEvent;      // +0x58
    uint64_t mThirdEvent;       // +0x70
    uint64_t mFourthEvent;      // +0x88
    uint64_t mFifthEvent;       // +0xa0
    uint32_t mRaidFrequency;    // +0xb0
    uint32_t padB4[6];
    uint32_t mEventCount;       // +0xcc
    uint32_t padD0[2];
    float mfD8;                 // +0xd8
    uint32_t padDC[2];
    float mfE4;                 // +0xe4

    void Write(cOutStream* pOut);   // 0x0100d560
    void Read(cOutStream* pOut);    // 0x0100d790
};

// SP::WarAttackEvent: the raid timer the event frequency is derived from.
struct WarAttackEvent {
    uint8_t pad00[8];
    uint64_t mTimeSinceLastRaid;    // +0x08
    float GetEventFrequency(float deltaSeconds, uint32_t deltaHi);   // 0x0100dfb0
};

// The two-dword selection object behind 0x0100d9f0 / 0x0100da10.
struct cGrobShockSelection {
    uint8_t pad000[0x110];
    uint32_t mu110;             // +0x110
    uint32_t mu114;             // +0x114
    void Reset();                       // 0x0100d9f0
    bool Get(uint32_t* pOut);           // 0x0100da10
};

// A civ object (cCivData) with its city position.
struct cCivData {
    float* GetCities();                 // 0x005c65e0
    void* GetAvatar();                  // 0x00b1fdb0
};

// A noun: the civ behind it and its placed objects.
struct cGameNoun {
    cCivData* GetCivData();             // 0x00b8de30
    bool HasPlace(uint32_t place);      // 0x00b8e040
};

// The star manager and its trade-route manager.
struct cSpaceTradeRouteManager {
    void Update(uint32_t elapsedMS);    // 0x01038410
};
struct cStarManager {
    void* GetEmpireByID(void* pNoun);   // 0x00ba9370
    cSpaceTradeRouteManager* GetTradeRoutes();   // 0x00ba6490
};

// A relationship between two empires.
struct cRelationship {
    bool IsFriend(void* pEmpire, void* pOther); // 0x00d01ff0
    bool IsEnemy(void* pEmpire, void* pOther);  // 0x00d01f50
};

// The living-universe player state (empty-list check at +0x5c/+0x60).
struct cPlayerEmpire {
    uint8_t pad00[0x5c];
    void* mp5c;                 // +0x5c
    void* mp60;                 // +0x60
};

// A simulator-universe tunable store and one float tunable.
struct cSimProperty {
    uint8_t pad00[0x12];
    uint16_t mw12;                      // +0x12
    float* GetFloat();                  // 0x0041ea70
};
struct cPropertyStore {
    PV8 PV
    virtual bool Find(uint32_t id, cSimProperty** ppOut);   // +0x24
};
struct cSimUniverseStore {
    uint8_t pad00[0x10];
    cPropertyStore* mp10;               // +0x10
};

// A terrain sphere owned by the noun manager.
struct cTerrainSphere {
    float GetValue(uint32_t id);        // 0x00c75c30
    void UpdateA();                     // 0x00c7ada0
    void UpdateB(uint32_t elapsedMS);   // 0x00c774b0
};
struct cNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();  // 0x00f67d90
};

// The space game and its available-civ list.
struct cAvailableCivList {
    cCivData** mp00;            // +0x00 (begin)
    cCivData** mp04;            // +0x04 (end)
};
struct cCivEntryList {
    uint8_t pad00[0x2c];
    cCivData** mp2c;            // +0x2c (begin)
    cCivData** mp30;            // +0x30 (end)
};
struct cSpaceGame {
    uint8_t pad00[0x30];
    cCivEntryList* mp30;        // +0x30
};

// The space tool.
struct cSpaceTool {
    void Advance(uint32_t arg0, uint32_t arg1); // 0x00aea8e0
};

// The terraforming manager.
struct cTerraformingManager {
    void UpdatePlanetFaceLevelPartitioning(uint32_t arg);   // 0x00bbd0a0
};

// ---------------------------------------------------------------------------------------------
// Free helpers / singletons.
cUFOSimulator* __cdecl GetUFOSimulator();           // 0x00ffbe50
cGameTimeManager* __cdecl GameTimeManager();        // 0x00b3d380
void* __cdecl App();                                // 0x0067dd10
void* __cdecl FUN_01021230();                       // 0x01021230
float __cdecl FUN_01017030(int arg);                // 0x01017030
cAppModeSpace* __cdecl FUN_00fd9c60();              // 0x00fd9c60
cTerraformingManager* __cdecl TerraformingManager();   // 0x00b3d430
void  __cdecl UpdateSound();                        // 0x010033a0
cSpaceGame* __cdecl SpaceGameGet();                 // 0x01002bd0
void* __cdecl GetPlayerHomePlanet();                // 0x01021370
int   __cdecl GetCivValue(cCivData* pCiv);          // 0x00c702f0
void* __cdecl FUN_01021300();                       // 0x01021300
void* __cdecl FUN_00c30c60(void* p);                // 0x00c30c60
cStarManager* __cdecl StarManager();                // 0x00b3d2a0
cRelationship* __cdecl RelationshipManager();       // 0x00b3d2c0
float __cdecl GetCityDistance(float* pA, float* pB);   // 0x010434e0
cNounManager* __cdecl NounManager();                // 0x00b3d300
void  __cdecl FUN_01041c50(void* p, uint32_t a, uint32_t b);      // 0x01041c50
cSpaceEvent* __cdecl FUN_01006280(cSpaceEvent* dst, cSpaceEvent* end, cSpaceEvent* src); // 0x01006280
cSpaceTool* __cdecl CommManager();                  // 0x00b3d4a0
bool  __cdecl EA_IO_WriteUint32(cStreamObj* pStream, const uint32_t* value, int count, int flags); // 0x0093aa70
bool  __cdecl EA_IO_WriteUint64(cStreamObj* pStream, const uint64_t* value, int count, int flags); // 0x0093ab10
bool  __cdecl EA_IO_ReadUint32(cStreamObj* pStream, uint32_t* value, int count, int flags);        // 0x0093a780
bool  __cdecl EA_IO_ReadBlock(cStreamObj* pStream, void* value, int count, int flags);             // 0x0093a800

extern const float kfMillisecondsPerUnit;   // 0x013f9428
extern const float kfDistanceEpsilon;       // 0x01495390
extern const float kfThree;                 // 0x013eb95c
extern const float kfHalfLog;               // 0x013fdf1c
extern const float kfHalfLogPerUnit;        // 0x01495720
extern const float kfThousand;              // 0x013ec5b4
extern const uint32_t kPlaceBioProtector;   // 0x016dca94
extern const char kSimulatorUniverseName[]; // 0x015b6b38
extern cSimUniverseStore* gpSimUniverse;    // 0x016dc798

// =============================================================================================
// @ 0x0100d0d0
// =============================================================================================
void cSPSimulatorSpaceGame::GalaxyUpdate(uint32_t elapsedMS)
{
    cPlayerInventory* pInventory = GetUFOSimulator()->GetPlayerInventory();
    bool bPaused = (GameTimeManager()->mb48 & 1) != 0;

    void* pService = ((cSubSystem*)((cAppSystem*)App())->GetSubSystem())->GetService();
    if (!pService)
        return;
    cEffectHost* pEffect = (cEffectHost*)((cServiceHost*)pService)->Find(0x303154cc);
    if (!pEffect || bPaused)
        return;

    float fRadius = pEffect->GetRadius();
    if (!IsZoomedOut() && pEffect->mbD5 != 0 && FUN_01021230() != 0 &&
        pInventory->mb74c != 0 &&
        fRadius - kfDistanceEpsilon <= FUN_01017030(2)) {
        FUN_00fd9c60()->TransitionFromGalaxyToSolar();
        return;
    }

    AdvanceTimer((float)std::min<uint64_t>(elapsedMS, 100) * kfMillisecondsPerUnit);
    GalaxyUpdateNPC_UFOs(elapsedMS);
    if (pInventory->mb74c == 0)
        GalaxyTestForIntercept();
}

// =============================================================================================
// @ 0x0100d230
// =============================================================================================
void cSPSimulatorSpaceGame::GameUpdate(uint32_t arg)
{
    switch (GetUniverseContext()) {
    case 0:
        TerraformingManager()->UpdatePlanetFaceLevelPartitioning(arg);
        break;
    case 1:
        SolarSystemUpdate(arg);
        UpdateUFOStatusEffects();
        UpdateSound();
        return;
    case 2:
        GalaxyUpdate(arg);
        UpdateUFOStatusEffects();
        UpdateSound();
        return;
    }
    UpdateUFOStatusEffects();
    UpdateSound();
}

// =============================================================================================
// @ 0x0100d2a0
// =============================================================================================
void cSPSimulatorSpaceGame::OnTick(uint32_t arg0, uint32_t arg1)
{
    if (mp14) {
        cSimObject* pObject = mp14->GetSimObject();
        if (pObject)
            pObject->Update();
    }
    GameUpdate(arg0);

    if (GetUniverseContext() == 0) {
        OnPreTick();
        if (mp54)
            mp54->Update(arg0, arg1);
    }

    StarManager()->GetTradeRoutes()->Update(arg0);
    cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
    pSphere->UpdateA();
    pSphere->UpdateB(arg0);
    CommManager()->Advance(arg0, arg1);

    cSpaceEvent* pEvent = mpEventsC8;
    if (pEvent != mpEventsCC) {
        float delta = (float)(((uint64_t)arg1 << 32) | arg0);
        do {
            pEvent->mf14 = pEvent->mf14 - delta;
            if (pEvent->mf14 <= 0.0f) {
                FUN_01041c50(pEvent->mv00, pEvent->mu10, pEvent->mu18);
                if (pEvent + 1 < mpEventsCC)
                    FUN_01006280(pEvent + 1, mpEventsCC, pEvent);
                mpEventsCC = mpEventsCC - 1;
                cSpaceEvent* pFree = mpEventsCC;
                if ((char*)pFree->mv08 - (char*)pFree->mv00 > 1 && pFree->mv00 != 0)
                    ::operator delete[](pFree->mv00);
            } else {
                ++pEvent;
            }
        } while (pEvent != mpEventsCC);
    }

    if (GetUniverseContext() == 2)
        UpdateEmpireHud(arg0, arg1);
}

// =============================================================================================
// @ 0x0100d410
// =============================================================================================
float cSPSimulatorSpaceGame::GetTimerSeconds()
{
    return (float)mTimer.GetElapsedTime() * kfMillisecondsPerUnit;
}

// =============================================================================================
// @ 0x0100d500
// =============================================================================================
float ProbabilityFromRatio(float value, float max)
{
    if (!(max > 0.0f))
        return 0.0f;
    double ratio = (double)(value / max);
    return 1.0f - (float)exp(ratio * kfHalfLog);
}

// =============================================================================================
// @ 0x0100d560
// =============================================================================================
void cSimulatorUniverse::Write(cOutStream* pOut)
{
    uint32_t header = 0x2a8c0c0;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), &header, 1, 0);

    uint64_t v0 = mFirstEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v0, 1, 0);
    uint64_t v1 = mSecondEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v1, 1, 0);
    uint64_t v2 = mThirdEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v2, 1, 0);
    uint64_t v3 = mFourthEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v3, 1, 0);
    uint64_t v4 = mFifthEvent;
    EA_IO_WriteUint64(pOut->GetStreamObj()->GetStream(), &v4, 1, 0);

    uint32_t count = mEventCount;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), &count, 1, 0);

    float f0 = mfD8;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&f0, 1, 0);

    uint32_t freq = mRaidFrequency;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), &freq, 1, 0);

    float f1 = mfE4;
    EA_IO_WriteUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&f1, 1, 0);

    cVarListSerializer serializer((cVarList*)((char*)this - 8), kSimulatorUniverseName, 0x1a80d26);
    serializer.Serialize(pOut);
}

// =============================================================================================
// @ 0x0100d790
// =============================================================================================
void cSimulatorUniverse::Read(cOutStream* pOut)
{
    uint32_t header;
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), &header, 1, 0);

    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mFirstEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mSecondEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mThirdEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mFourthEvent, 1, 0);
    EA_IO_ReadBlock(pOut->GetStreamObj()->GetStream(), &mFifthEvent, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), &mEventCount, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&mfD8, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), &mRaidFrequency, 1, 0);
    EA_IO_ReadUint32(pOut->GetStreamObj()->GetStream(), (uint32_t*)&mfE4, 1, 0);

    cVarListSerializer serializer((cVarList*)((char*)this - 8), kSimulatorUniverseName, 0x1a80d26);
    serializer.SerializeRead(pOut);
}

// =============================================================================================
// @ 0x0100d960
// =============================================================================================
bool CompareProtectorDistances(cGameNoun* a, cGameNoun* b)
{
    float* pCitiesA = a->GetCivData()->GetCities();
    float fA = pCitiesA[0] * pCitiesA[0] + pCitiesA[1] * pCitiesA[1] + pCitiesA[2] * pCitiesA[2];
    float* pCitiesB = b->GetCivData()->GetCities();
    float fB = pCitiesB[0] * pCitiesB[0] + pCitiesB[1] * pCitiesB[1] + pCitiesB[2] * pCitiesB[2];
    return fB > fA;
}

// =============================================================================================
// @ 0x0100d9f0
// =============================================================================================
void cGrobShockSelection::Reset()
{
    mu110 = 0xffffffff;
    mu114 = 0;
}

// =============================================================================================
// @ 0x0100da10
// =============================================================================================
bool cGrobShockSelection::Get(uint32_t* pOut)
{
    if (mu114 <= 0)
        return false;
    *pOut = mu110;
    return true;
}

// =============================================================================================
// @ 0x0100da40
// =============================================================================================
bool sCompareGrobShockData(void* a, void* b)
{
    uint64_t tA = ((cSPTimer*)((char*)a + 8))->GetElapsedTime();
    uint64_t tB = ((cSPTimer*)((char*)b + 8))->GetElapsedTime();
    return tA < tB;
}

// =============================================================================================
// @ 0x0100daa0
// =============================================================================================
void* DestroyTimerRange(void* first, void* last, void* dest)
{
    while (first != last) {
        ((cGonzagoTimer*)((char*)first + 8))->Destroy();
        first = (char*)first + 0x28;
        dest = (char*)dest + 0x28;
    }
    return dest;
}

// =============================================================================================
// @ 0x0100dae0
// =============================================================================================
int SumOfOtherCivValues()
{
    int total = 0;
    cCivEntryList* pList = SpaceGameGet()->mp30;
    int count = (int)(pList->mp30 - pList->mp2c);
    cCivData* pHome = (cCivData*)GetPlayerHomePlanet();
    if (count <= 0)
        return 0;
    for (int i = 0; i < count; ++i) {
        cCivData* pCiv = pList->mp2c[i];
        if (pCiv != pHome)
            total += GetCivValue(pCiv);
    }
    return total;
}

// =============================================================================================
// @ 0x0100db40
// =============================================================================================
struct BioProtectorSort {
    float mPos[3];              // +0x00
    bool operator()(cGameNoun* a, cGameNoun* b);        // 0x0100db40
    bool CompareAndCheck(cGameNoun* a, cGameNoun* b);   // 0x0100dc20
};

bool BioProtectorSort::operator()(cGameNoun* a, cGameNoun* b)
{
    float* pCitiesA = a->GetCivData()->GetCities();
    float dxA = pCitiesA[0] - mPos[0];
    float dyA = pCitiesA[1] - mPos[1];
    float dzA = pCitiesA[2] - mPos[2];
    float* pCitiesB = b->GetCivData()->GetCities();
    return dxA * dxA + dyA * dyA + dzA * dzA <
           (pCitiesB[0] - mPos[0]) * (pCitiesB[0] - mPos[0]) +
           (pCitiesB[1] - mPos[1]) * (pCitiesB[1] - mPos[1]) +
           (pCitiesB[2] - mPos[2]) * (pCitiesB[2] - mPos[2]);
}

// =============================================================================================
// @ 0x0100dc20
// =============================================================================================
bool BioProtectorSort::CompareAndCheck(cGameNoun* a, cGameNoun* b)
{
    bool bA = a->HasPlace(kPlaceBioProtector);
    bool bB = b->HasPlace(kPlaceBioProtector);
    if (bA == bB) {
        float* pCitiesA = a->GetCivData()->GetCities();
        float dxA = pCitiesA[0] - mPos[0];
        float dyA = pCitiesA[1] - mPos[1];
        float dzA = pCitiesA[2] - mPos[2];
        float* pCitiesB = b->GetCivData()->GetCities();
        return dxA * dxA + dyA * dyA + dzA * dzA <
               (pCitiesB[2] - mPos[2]) * (pCitiesB[2] - mPos[2]) +
               (pCitiesB[1] - mPos[1]) * (pCitiesB[1] - mPos[1]) +
               (pCitiesB[0] - mPos[0]) * (pCitiesB[0] - mPos[0]);
    }
    return !bA;
}

// =============================================================================================
// @ 0x0100dd40
// =============================================================================================
static float Clamp01(float v)
{
    if (!(v > 0.0f))
        return 0.0f;
    if (v > 1.0f)
        return 1.0f;
    return v;
}

float AverageEmpireDistance(void* pNoun, void* pCivList, bool bIncludeEnemies)
{
    float fTotal = 0.0f;
    float fMax = GetUFOSimulator()->GetMaxTravelDistance();
    if (fMax == 0.0f)
        return 0.0f;

    cPlayerEmpire* pPlayerEmpire = (cPlayerEmpire*)FUN_01021300();
    cCivData* pPlayerCiv = (cCivData*)FUN_00c30c60(pPlayerEmpire);
    float* pCities = ((cGameNoun*)pNoun)->GetCivData()->GetCities();
    float fRange = fMax * kfThree;

    if (pNoun) {
        cAvailableCivList* pList = (cAvailableCivList*)pCivList;
        cCivData** pBegin = pList->mp00;
        int nCivs = (int)(pList->mp04 - pBegin);
        int nCount = 0;
        for (int i = 0; i < nCivs; ++i) {
            cCivData* pCiv = pBegin[i];
            if (pCiv == pPlayerCiv) {
                fTotal += Clamp01(GetCityDistance(pCiv->GetCities(), pCities) / fRange);
                ++nCount;
            } else {
                void* pEmpire = StarManager()->GetEmpireByID(pCiv->GetAvatar());
                if (RelationshipManager()->IsFriend(pEmpire, pPlayerEmpire)) {
                    fTotal += Clamp01(GetCityDistance(pCiv->GetCities(), pCities) / fRange);
                    ++nCount;
                } else if (bIncludeEnemies &&
                           RelationshipManager()->IsEnemy(pEmpire, pPlayerEmpire)) {
                    fTotal += Clamp01(1.0f - GetCityDistance(pCiv->GetCities(), pCities) / fRange);
                    ++nCount;
                }
            }
        }
        fTotal = fTotal / (float)nCount;
    }
    return Clamp01(fTotal);
}

// =============================================================================================
// @ 0x0100dfb0
// =============================================================================================
float WarAttackEvent::GetEventFrequency(float deltaSeconds, uint32_t deltaHi)
{
    mTimeSinceLastRaid += ((uint64_t)deltaHi << 32) | *(uint32_t*)&deltaSeconds;

    cPlayerEmpire* pPlayerEmpire = (cPlayerEmpire*)FUN_01021300();
    if (pPlayerEmpire->mp5c == pPlayerEmpire->mp60)
        return 0.0f;

    float fFrequency = 0.0f;
    if (gpSimUniverse->mp10) {
        cSimProperty* pProperty = 0;
        if (gpSimUniverse->mp10->Find(0x31e94b7, &pProperty) && pProperty->mw12 == 0xd)
            fFrequency = *pProperty->GetFloat();
    }

    if (fFrequency * kfThousand <= (float)mTimeSinceLastRaid)
        return 0.0f;

    if (gpSimUniverse->mp10) {
        cSimProperty* pProperty = 0;
        if (gpSimUniverse->mp10->Find(0x31e94b8, &pProperty) && pProperty->mw12 == 0xd)
            fFrequency = *pProperty->GetFloat();
    }

    float fRate = NounManager()->GetCurrentTerrainSphere()->GetValue(0xc42edf05) * fFrequency;
    if (!(fRate > 0.0f))
        return 0.0f;

    double ratio = (double)(((uint64_t)deltaHi << 32) | *(uint32_t*)&deltaSeconds) / (double)fRate;
    return 1.0f - (float)exp(ratio * kfHalfLogPerUnit);
}
