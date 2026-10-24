// Slice s00ffb180: the planet-system tick of the high-detail planet simulator - the UFO harvest pass
// (clear the planet-buster flags, count fleets/visitors, respawn the drawn UFO, erode/refresh the
// replacement timers), the city-destruction sweep, the per-frame tick that drives all of it, the UFO
// player object's serializer/initialiser/timer, the terrain-sphere reset and the UFO data replacement.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380

extern char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern char g_szEastlFile[];        // 0x013ebb38 ".../EASTL/allocator.h"

// noun-list selectors handed to cGameNounManager::GetGameDataVector
void __cdecl FUN_00cd7d10();           // 0x00cd7d10
void __cdecl FUN_00d3d420();           // 0x00d3d420
void __cdecl FUN_00acdff0();           // 0x00acdff0
void __cdecl FUN_00ad48b0();           // 0x00ad48b0
void __cdecl FUN_00b1e500();           // 0x00b1e500
void __cdecl FUN_00ae7060();           // 0x00ae7060 VecT_clear_cb
void __cdecl FUN_00ae7080();           // 0x00ae7080 CollectSubsystemA
void __cdecl FUN_00b1e520();           // 0x00b1e520

extern char g_nounListPlanet[];        // 0x018c43e8
extern char g_nounListUFO[];           // 0x018ebadc
extern char g_nounListHarvest[];       // 0x0142db2a

extern uint32_t g_planetBusterKey[3];  // 0x016db5c4 planet-buster bomb key
extern uint32_t g_missionPreventKey;   // 0x016db434
extern float    g_defaultVector[3];    // 0x016db418
extern char     g_szUFOString[];       // 0x015b60ec
extern char     g_varListUFO[];        // 0x015b6378
extern void*    g_slotMessageVtable[]; // 0x013eb844
extern void*    g_slotMessageBaseVtable[]; // 0x013eb90c
extern void*    g_ufoListenerVtable[]; // 0x014950d0
extern uint32_t g_gameModeGalaxy;      // 0x01654c05
extern uint32_t g_ufoMessageKey;       // 0x019d6324

class cOutStream;
class cSimGameData;
class cSimPlanet;
class cCityHall;
class tEffectHandle;
class tUFOObject;
class tUFOData;
class tInventory;
class tNodeObj;

// ---------------------------------------------------------------------------------------------
// the noun manager and its game-data vector
// ---------------------------------------------------------------------------------------------
struct tPtrVector {
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
};

struct tGameDataList {
    void*      mPad00;              // +0x00
    tPtrVector mData;               // +0x04
    void*      mPad0c;              // +0x0c
    void*      mPad10;              // +0x10
};

class cGameNounManager {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mpAvatar;               // +0x054

    tGameDataList* GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4, void* pAlloc); // 0x00b21340
    void*          GetCurrentTerrainSphere();                                                  // 0x00f67d90
    tUFOData*      CreateNoun(void* pNoun);                                                    // 0x00b20c60
    void*          GetAvatar();                                                                // 0x00b1fdb0
};

cGameNounManager* __cdecl NounManager();        // 0x00b3d300

// the ref-counted base every noun shares
class tRefObject {
public:
    virtual void AddRef();                      // +0x00
    virtual void Release();                     // +0x04
};

// ---------------------------------------------------------------------------------------------
// the planet / owner record (also the object hanging off a planet as its owner)
// ---------------------------------------------------------------------------------------------
class cPlanetRecord {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mp54;                   // +0x054
    uint8_t mPad58[0xd0];           // +0x058
    float   mf128;                  // +0x128 replacement timer
    float   mf12c;                  // +0x12c ping timer
    uint8_t mPad130[0x0c];          // +0x130
    cPlanetRecord* mp13c;           // +0x13c the owning record
    uint8_t mPad140[0x14];          // +0x140
    int32_t mn154;                  // +0x154
    uint8_t mPad158[0x2c];          // +0x158
    int32_t mn184;                  // +0x184
    uint8_t mPad188[0x0c];          // +0x188
    int32_t mn194;                  // +0x194 noun type

    int32_t        GetNounType();           // 0x00b8dab0
    cPlanetRecord* GetOwnerRecord();        // 0x00b8de30
    void*          GetAvatar();             // 0x00b1fdb0
    cPlanetRecord* FUN_00c71e30();          // 0x00c71e30
    int32_t        FUN_00c70e00();          // 0x00c70e00
    int32_t        FUN_008414c0();          // 0x008414c0
};

cPlanetRecord* __cdecl GetActivePlanet();   // 0x01021260
void*          __cdecl GetPlayerEmpire();   // 0x01021300
int32_t        __cdecl GetPlayerEmpireID(); // 0x01021090
bool           __cdecl IsHostileToAll(cPlanetRecord* pPlanet);        // 0x0102c600
bool           __cdecl IsMissionActiveAtPlanet(cPlanetRecord* pPlanet); // 0x0102adf0

// ---------------------------------------------------------------------------------------------
// the game-data nouns (cities and UFOs share the same record)
// ---------------------------------------------------------------------------------------------
class tCityObj {                    // a polymorphic sub-object embedded in a noun
public:
    virtual void  v00();            // +0x00
    virtual void  v04();            // +0x04
    virtual void  v08();            // +0x08
    virtual void  v0c();            // +0x0c
    virtual void  v10();            // +0x10
    virtual void  v14();            // +0x14
    virtual void  v18();            // +0x18
    virtual void  v1c();            // +0x1c
    virtual void  v20();            // +0x20
    virtual void  v24();            // +0x24
    virtual void  v28();            // +0x28
    virtual void* v2c();            // +0x2c
    virtual void* v30();            // +0x30

    int32_t FUN_008e7f80();         // 0x008e7f80
};

class tCityInner {
public:
    uint8_t  mPad00[0x5fc];         // +0x000
    uint32_t mn5fc;                 // +0x5fc visibility/flag word
};

class cCityHall {
public:
    uint8_t    mPad00[0x120];       // +0x000
    tCityObj   mObj120;             // +0x120
    uint8_t    mPad124[0x38];       // +0x124
    int32_t    mn15c;               // +0x15c owning empire
};

class cSimGameData : public tRefObject {    // vptr +0x00, AddRef +0x00, Release +0x04
public:
    virtual void    v08();          // +0x08
    virtual void    v0c();          // +0x0c
    virtual void    v10();          // +0x10
    virtual void    v14();          // +0x14
    virtual void    v18();          // +0x18
    virtual void    v1c();          // +0x1c
    virtual void    v20();          // +0x20
    virtual void    v24();          // +0x24
    virtual void    v28();          // +0x28
    virtual void    v2c();          // +0x2c
    virtual void    v30();          // +0x30
    virtual void    v34();          // +0x34
    virtual void    v38();          // +0x38
    virtual void    v3c();          // +0x3c
    virtual void    v40();          // +0x40
    virtual void    v44();          // +0x44
    virtual void    v48();          // +0x48
    virtual int32_t v4c();          // +0x4c owning empire

    uint8_t        mPad04[0x30];    // +0x004
    tCityObj       mObj34;          // +0x034
    uint8_t        mPad38[0xe8];    // +0x038
    tCityObj       mObj120;         // +0x120
    uint8_t        mPad124[0xfc];   // +0x124
    float          mf220;           // +0x220
    uint8_t        mPad224[0x48c];  // +0x224
    int32_t        mn6b0;           // +0x6b0
    uint8_t        mPad6b4[0x14];   // +0x6b4
    tCityInner*    mp6c8;           // +0x6c8
    uint8_t        mPad6cc[0x48];   // +0x6cc
    int32_t        mn714;           // +0x714 noun type

    cCityHall* GetCityHall();                               // 0x00bd9b40
    bool       FUN_00c38990(int32_t nIndex);                // 0x00c38990
    void       FUN_00c38740(float fA, double fB);           // 0x00c38740
    void       FUN_00bdbf10();                              // 0x00bdbf10
};

void* __cdecl FUN_00829110(void** ppOut, void** pBegin, void** pEnd, void** pDst, int32_t nHint); // 0x00829110

// ---------------------------------------------------------------------------------------------
// empires
// ---------------------------------------------------------------------------------------------
class cStarManager {
public:
    void* GetEmpireByID(void* pAvatar);     // 0x00ba9370
};
cStarManager* __cdecl StarManager();        // 0x00b3d2a0

class cEmpire {
public:
    uint8_t mPad00[0x54];                   // +0x000
    void*   mp54;                           // +0x054 avatar

    bool IsHostileToPlayer();               // 0x00c309e0
};

class cRelationshipManager {
public:
    void RecordEvent(uint32_t nKey, void* pFrom, void* pTo, float fValue);   // 0x00d06240
};
cRelationshipManager* __cdecl RelationshipManager();    // 0x00b3d2c0

class cSPMissionManager {
public:
    bool DoMissionsPreventHostility(cPlanetRecord* pPlanet, void* pKey);   // 0x00fedea0
};
cSPMissionManager* __cdecl GetMissionManager();         // 0x00feb9f0

class tGameTimeManager {
public:
    uint64_t FUN_00b316c0();                // 0x00b316c0
};
tGameTimeManager* __cdecl GameTimeManager();   // 0x00b3d380

class tRandom {
public:
    uint32_t RandomUint32Uniform(uint32_t nMax);   // 0x00a68fb0
};
extern tRandom g_mathRandom;                // 0x01601760

// ---------------------------------------------------------------------------------------------
// the space-combat tunables
// ---------------------------------------------------------------------------------------------
class tProperty {
public:
    uint8_t  mPad00[0x12];          // +0x00
    uint16_t mnType;                // +0x12

    float*   GetFloat();            // 0x0041ea70
    int32_t* GetInt();              // 0x0041e990
};

class tPropertyMap {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual void v18();             // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual bool v24(uint32_t nKey, tProperty** ppProperty);   // +0x24
};

class cSPSpaceCombatTuning {
public:
    uint8_t       mPad00[0x08];     // +0x00
    tPropertyMap* mp08;             // +0x08
};
cSPSpaceCombatTuning* __cdecl GetSpaceCombatTuning();   // 0x01029940

// ---------------------------------------------------------------------------------------------
// effects, timers and messaging
// ---------------------------------------------------------------------------------------------
class tEffectHandle {
public:
    virtual void v00();             // +0x00
    virtual void Release();         // +0x04
    virtual void v08(int32_t nValue);   // +0x08
    virtual void v0c(int32_t nValue);   // +0x0c
};

class tEffectsManager {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual void v18();             // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24();             // +0x24
    virtual void v28();             // +0x28
    virtual bool v2c(uint32_t nKey, int32_t nFlags, tEffectHandle** ppEffect);   // +0x2c
};
tEffectsManager* __cdecl EffectsManagerPtr();       // 0x0067ddd0

class cEffects {
public:
    void Tick(float fSeconds);      // 0x00ebe3e0
};

class cSPTimer {
public:
    uint64_t GetElapsedTime();      // 0x00bc3190
    void     Restart();             // 0x00bc3130
    uint32_t mPad00[8];             // +0x00
};

class tMessageServer {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14(uint32_t nKey, void* pPayload, int32_t nFlags);    // +0x14
    virtual void v18(uint32_t nKey, int32_t nA, int32_t nB, int32_t nC); // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24(void* pListener, uint32_t nKey);                   // +0x24
    virtual void v28();             // +0x28
    virtual void v2c();             // +0x2c
    virtual void v30();             // +0x30
    virtual void v34();             // +0x34
    virtual void v38();             // +0x38
    virtual void v3c();             // +0x3c
    virtual void v40();             // +0x40
    virtual void v44();             // +0x44
    virtual void v48();             // +0x48
    virtual void v4c();             // +0x4c
    virtual void v50(void* pListener);  // +0x50
};
tMessageServer* __cdecl MessageServer();            // 0x0067dcc0
namespace EA { namespace Messaging { tMessageServer* __cdecl GetServer(); } }   // 0x00883860

tMessageServer* __cdecl SimTicker();                // 0x00b3d330
uint32_t        __cdecl GetCurrentGameMode();       // 0x00b5b800

// the object a noun hands out for the planet-buster query
class tBombKey {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual uint32_t* v18();        // +0x18
};

class tSimThing {
public:
    virtual void v00();             // +0x00
    uint8_t   mPad04[0x514];        // +0x004
    tBombKey* mp518;                // +0x518
};

class tHarvestNoun {
public:
    virtual void      v00();                    // +0x00
    virtual tSimThing* v04(uint32_t nKey);      // +0x04
    uint8_t   mPad04[0x0c];         // +0x004
    bool      mb10;                 // +0x010
};

extern float g_kRealZero;           // 0x01485378

// ---------------------------------------------------------------------------------------------
// the UFO simulator / inventory objects used by the tick's message payload
// ---------------------------------------------------------------------------------------------
class tUFOObject : public tRefObject {      // vptr +0x00
public:
    virtual void  v08();            // +0x08
    virtual void  v0c();            // +0x0c
    virtual void  v10();            // +0x10
    virtual void  v14();            // +0x14
    virtual void  v18();            // +0x18
    virtual void  v1c();            // +0x1c
    virtual void  v20();            // +0x20
    virtual void  v24();            // +0x24
    virtual void  v28();            // +0x28
    virtual bool  v2c();            // +0x2c
};

class tUFOData : public tRefObject {        // vptr +0x00
public:
    virtual void  v08();            // +0x08
    virtual void* v0c(uint32_t nSub);   // +0x0c

    void Init(void* pA, void* pB);  // 0x00c3e0b0
};

class cEmpireKey {
public:
    uint32_t mn00;                  // +0x00
    void SetUFOKey(void** ppKey);   // 0x00c35740
};

class cSimInventory {
public:
    tCityObj mObj34;                // +0x034
};

class cUFOSimulator {
public:
    uint8_t        mPad00[0x30];    // +0x000
    cSimInventory* mp30;            // +0x030

    cSimInventory* GetPlayerInventory();    // 0x00a1ad60
};
cUFOSimulator* __cdecl GetUFOSimulator();   // 0x00ffbe50

struct tVector3 {
    float x;
    float y;
    float z;
};

class tDOMNode {
public:
    uint8_t  mPad00[0xc0];          // +0x000
    tCityObj mObjC0;                // +0x0c0
};

class tDOMWrapper {
public:
    bool      FUN_00a98020();       // 0x00a98020
    tDOMNode* FUN_00ff0420();       // 0x00ff0420
};
tDOMWrapper* __cdecl FUN_01015df0();    // 0x01015df0

// the eastl string16 buffer the payload builders fill in (begin / end / capacity)
struct tStringKey {
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCapacity;                   // +0x08
};

class tAppCom {
public:
    virtual void  v00();            // +0x00
    virtual void  v04();            // +0x04
    virtual void  v08();            // +0x08
    virtual void  v0c();            // +0x0c
    virtual void  v10();            // +0x10
    virtual void  v14();            // +0x14
    virtual void  v18();            // +0x18
    virtual void* v1c();            // +0x1c
};

class tApp {
public:
    virtual void    v00();          // +0x00
    virtual void    v04();          // +0x04
    virtual void    v08();          // +0x08
    virtual void    v0c();          // +0x0c
    virtual void    v10();          // +0x10
    virtual void    v14();          // +0x14
    virtual void    v18();          // +0x18
    virtual void    v1c();          // +0x1c
    virtual void    v20();          // +0x20
    virtual void    v24();          // +0x24
    virtual void    v28();          // +0x28
    virtual void    v2c();          // +0x2c
    virtual void    v30();          // +0x30
    virtual void    v34();          // +0x34
    virtual void    v38();          // +0x38
    virtual void    v3c();          // +0x3c
    virtual void    v40();          // +0x40
    virtual void    v44();          // +0x44
    virtual void    v48();          // +0x48
    virtual void    v4c();          // +0x4c
    virtual tAppCom* v50();         // +0x50
};
tApp* __cdecl App();                // 0x0067dd10

tVector3* __cdecl FUN_0095df60(void* pString, void* pKey, uint32_t nValue);  // 0x0095df60
tVector3* __cdecl FUN_0059aed0(void* pString, void* pKey, uint32_t nValue);  // 0x0059aed0

// the slot message posted at the end of a tick (vtable + payload pointers)
struct tSlotMessage {
    void*      mpVtable;            // +0x00
    uint32_t   mnRefCount;          // +0x04
    tVector3*  mpPosition;          // +0x08
    uint32_t   mn0c;                // +0x0c
    tVector3*  mpSize;              // +0x10
    uint32_t   mPad14[0x07];        // +0x14
    uint32_t   mnKey;               // +0x30
    uint32_t   mn34;                // +0x34
    uint32_t   mn38;                // +0x38

    void Destruct();                // 0x00421cf0
};

class tMessageThing {
public:
    void* FUN_01067e60();           // 0x01067e60
    void  FUN_01065d20();           // 0x01065d20
};
tMessageThing* __cdecl FUN_010666a0();  // 0x010666a0

class tTickHook {
public:
    void FUN_00e0df70(cSimGameData* pNoun, void* pValue);   // 0x00e0df70
};

// the terrain sphere and the planet model
class cTerrainSphere {
public:
    void FUN_00c77bf0(uint32_t nKey);   // 0x00c77bf0
    bool Check();                       // 0x00c75650
};

// the planet sub-object cPlanetModel hands out at +0x24 (only its +0x50 gate is used here)
class tPlanetGate {
public:
    virtual void v00();             // +0x00
    virtual void v04();             // +0x04
    virtual void v08();             // +0x08
    virtual void v0c();             // +0x0c
    virtual void v10();             // +0x10
    virtual void v14();             // +0x14
    virtual void v18();             // +0x18
    virtual void v1c();             // +0x1c
    virtual void v20();             // +0x20
    virtual void v24();             // +0x24
    virtual void v28();             // +0x28
    virtual void v2c();             // +0x2c
    virtual void v30();             // +0x30
    virtual void v34();             // +0x34
    virtual void v38();             // +0x38
    virtual void v3c();             // +0x3c
    virtual void v40();             // +0x40
    virtual void v44();             // +0x44
    virtual void v48();             // +0x48
    virtual void v4c();             // +0x4c
    virtual bool v50();             // +0x50
};

class cPlanetModel {
public:
    uint8_t      mPad00[0x24];      // +0x000
    tPlanetGate* mp24;              // +0x024 planet gate object

    float GetWaterHeight();                                         // 0x00b7e390
    tVector3* DirectionToSurfacePosition(tVector3* pOut, void* pID); // 0x00b815a0
};
cPlanetModel* __cdecl PlanetModel();    // 0x00b3d350

class tEffectsGlobal {
public:
    uint8_t       mPad00[0x4c];     // +0x000
    tEffectsManager* mp4c;          // +0x04c
    bool FUN_0067c8c0(uint32_t nKey, int32_t nValue);   // 0x0067c8c0
};
tEffectsGlobal* __cdecl FUN_0067cac0();     // 0x0067cac0

// the render consumer the tick forwards the frame time to
class tRenderConsumer {
public:
    virtual void v00();                             // +0x00
    virtual void v04();                             // +0x04
    virtual void v08();                             // +0x08
    virtual void v0c();                             // +0x0c
    virtual void v10(uint32_t nTimeLo, uint32_t nTimeHi, void* pValue);   // +0x10
};

// ---------------------------------------------------------------------------------------------
// the high-detail planet simulator (the `this` of every function in this slice)
// ---------------------------------------------------------------------------------------------
class cSPSimPlanetHighLOD {
public:
    uint8_t      mPad00[0x28];      // +0x000
    tRenderConsumer* mp28;          // +0x028 render consumer (v10)
    void*        mp2c;              // +0x02c drawn UFO / message-server handle
    void*        mp30;              // +0x030 message listener
    void*        mp34;              // +0x034 listener vtable
    int32_t      mn38;              // +0x038
    int32_t      mn3c;              // +0x03c
    tUFOData*    mp40;              // +0x040 UFO game data
    uint8_t      mPad44[0x3c];      // +0x044
    cSPTimer     mTimer80;          // +0x080
    int32_t      mnA0;              // +0x0a0
    uint8_t      mPadA4[0xb4];      // +0x0a4
    bool         mb158;             // +0x158
    uint8_t      mPad159[0x57];     // +0x159
    cEffects*    mp1b0;             // +0x1b0
    uint8_t      mPad1b4[0x04];     // +0x1b4
    int32_t      mn1b8;             // +0x1b8 threshold
    tEffectHandle* mp1bc;           // +0x1bc terrain effect
    uint8_t      mPad1c0[0x1c];     // +0x1c0
    tEffectHandle* mp1dc;           // +0x1dc
    bool         mb1e0;             // +0x1e0

    void FUN_00ffb180();                                            // 0x00ffb180
    void SolarSystemUpdateNPC_UFOs(uint32_t nElapsedMS);            // 0x00ffb270
    void CheckForCityDestruction();                                 // 0x00ffb830
    void OnTick(uint32_t nTimeLo, uint32_t nTimeHi);                // 0x00ffbb20
    void Init();                                                    // 0x00ffbf60
    bool FUN_00ffbfe0();                                            // 0x00ffbfe0
    void FUN_00ffc030();                                            // 0x00ffc030
    bool CheckAndReplaceData(void* pKey, void* pB, void* pC);       // 0x00ffc160
    void CreateReplacement();                                       // 0x00ffa780
    void FUN_00ff8ad0();                                            // 0x00ff8ad0
    void FUN_00ffabc0();                                            // 0x00ffabc0
    void FUN_00ffaf20(uint32_t nTimeLo);                            // 0x00ffaf20
    void FUN_00ffa690();                                            // 0x00ffa690
    void FUN_00ffab60();                                            // 0x00ffab60
    void FUN_00ff7530(uint32_t nTimeLo, uint32_t nTimeHi);          // 0x00ff7530
    void FUN_00ffa900(cSimGameData* pNoun, int32_t nEmpire);        // 0x00ffa900
};

// the UFO player object serialized by the game-data writer
class cSPSimulatorPlayerUFO {
public:
    bool Write(cOutStream* pStream);    // 0x00ffbe60
};

// the vector the destroyed cities are collected in
class tCityVector {
public:
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void** mpCapacity;              // +0x08

    tCityVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(void** pEnd, void* const& pValue);   // 0x00aea5d0
    void DoDestroy();                                       // 0x00ae6970
};

// the stream every game-data object serializes itself into
class tIStream {
public:
    virtual void v00();                                     // +0x00
};

class tStreamInner {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual tIStream* v18();                                // +0x18
};

class cOutStream {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual tStreamInner* v20();                            // +0x20
};

class cVarListSerializer {
public:
    uint32_t mPad00[0x05];                                          // +0x00
    void Construct(void* pOwner, void* pVarList, int32_t nLine);    // 0x00692f90
    bool Serialize(cOutStream* pStream);                            // 0x00692900
};

struct tVarListFrame {
    uint32_t            mnValue;            // +0x000
    cVarListSerializer  mSerializer;        // +0x004
    uint32_t            mPad18[0x280];      // +0x018
};

bool __cdecl EA_IO_WriteUint32(tIStream* pStream, const uint32_t* pValue, int32_t nCount, int32_t nFlags); // 0x0093aa70

// ---------------------------------------------------------------------------------------------
// @ 0x00ffb180
// ---------------------------------------------------------------------------------------------
void cSPSimPlanetHighLOD::FUN_00ffb180()
{
    cGameNounManager* pManager = NounManager();
    tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00ae7060,
                                                       (void*)FUN_00ae7080, (void*)FUN_00b1e520,
                                                       g_nounListHarvest);
    tPtrVector* pNouns = &pList->mData;
    void** pCur = pNouns->mpBegin;
    void** pEnd = pNouns->mpEnd;
    if (pCur != pEnd)
    {
        do
        {
            tHarvestNoun* pNoun = (tHarvestNoun*)*pCur;
            if (pNoun != 0)
            {
                tSimThing* pThing = pNoun->v04(0x024270c4);
                if (pThing != 0)
                {
                    tBombKey* pKey = pThing->mp518;
                    if (pKey != 0)
                    {
                        uint32_t* pValue = pKey->v18();
                        if (pValue[0] == g_planetBusterKey[0] && pValue[1] == g_planetBusterKey[1] &&
                            pValue[2] == g_planetBusterKey[2])
                        {
                            pNoun->mb10 = false;
                        }
                    }
                }
            }
            ++pCur;
        } while (pCur != pEnd);
    }

    MessageServer()->v18(0x04f4d25e, 0, 0, 0);
    mb1e0 = false;
    if (mp1dc != 0)
    {
        mp1dc->v0c(1);
        if (mp1dc != 0)
        {
            tEffectHandle* pOld = mp1dc;
            mp1dc = 0;
            pOld->Release();
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffb270
// ---------------------------------------------------------------------------------------------
void cSPSimPlanetHighLOD::SolarSystemUpdateNPC_UFOs(uint32_t nElapsedMS)
{
    cGameNounManager* pManager = NounManager();
    float fElapsed = (float)nElapsedMS * 0.001f;

    bool bHostileToAll = IsHostileToAll(GetActivePlanet());
    bool bMissionsPrevent = GetMissionManager()->DoMissionsPreventHostility(GetActivePlanet(), &g_missionPreventKey);
    bool bMissionActive = IsMissionActiveAtPlanet(GetActivePlanet());

    int32_t nFleets = 0;
    int32_t nVisitors = 0;
    bool bHostile = false;

    tGameDataList* pList = NounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                           (void*)FUN_00ad48b0, (void*)FUN_00b1e500,
                                                           g_nounListUFO);
    void** pCur = pList->mData.mpBegin;
    void** pEnd = pList->mData.mpEnd;
    while (pCur != pEnd)
    {
        cSimGameData* pNoun = (cSimGameData*)*pCur;
        int32_t nType = pNoun->mn714;
        if (nType == 6)
        {
            ++nFleets;
        }
        else if (nType == 8)
        {
            ++nVisitors;
            if (bHostile == false)
            {
                cEmpire* pEmpire = (cEmpire*)StarManager()->GetEmpireByID((void*)pNoun->v4c());
                if (pEmpire != 0 && pEmpire->IsHostileToPlayer())
                    bHostile = true;
            }
        }
        ++pCur;
    }

    tTickHook* pTickHook = (tTickHook*)FUN_010666a0()->FUN_01067e60();

    if (mp2c == 0)
    {
        tGameDataList* pUFOs = NounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                               (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                               g_nounListPlanet);
        void** pBegin = pUFOs->mData.mpBegin;
        void** pLast = pUFOs->mData.mpEnd;
        if (pBegin != pLast)
        {
            uint32_t nPick = g_mathRandom.RandomUint32Uniform((uint32_t)(pLast - pBegin));
            tUFOObject* pNew = (tUFOObject*)pBegin[nPick];
            tUFOObject* pOld = (tUFOObject*)mp2c;
            if (pNew != pOld)
            {
                if (pNew != 0)
                    pNew->AddRef();
                mp2c = pNew;
                if (pOld != 0)
                    pOld->Release();
            }
        }
    }

    if (mp2c != 0 && ((tUFOObject*)mp2c)->v2c())
    {
        tUFOObject* pOld = (tUFOObject*)mp2c;
        if (pOld != 0)
        {
            mp2c = 0;
            pOld->Release();
        }
    }

    cPlanetRecord* pOwner = GetActivePlanet()->mp13c;
    if (pOwner->GetNounType() == 5 && NounManager()->GetAvatar() != (void*)GetPlayerEmpireID())
    {
        uint64_t nNow = GameTimeManager()->FUN_00b316c0();
        float fNow = (float)nNow * 0.001f;

        if (nFleets < mn1b8)
        {
            float fReplaceDist = 30.0f;
            tPropertyMap* pMap = GetSpaceCombatTuning()->mp08;
            if (pMap != 0)
            {
                tProperty* pProperty = 0;
                if (pMap->v24(0x05c2cbc5, &pProperty) && pProperty->mnType == 13)
                    fReplaceDist = *pProperty->GetFloat();
            }
            if (fNow - pOwner->mf128 > fReplaceDist)
            {
                pOwner->mf128 = fNow;
                CreateReplacement();
            }
        }
        else
        {
            pOwner->mf128 = fNow;
        }

        if (pOwner->mf12c > g_kRealZero)
        {
            float fPingDist = 30.0f;
            tPropertyMap* pMap = GetSpaceCombatTuning()->mp08;
            if (pMap != 0)
            {
                tProperty* pProperty = 0;
                if (pMap->v24(0x05c2cbd6, &pProperty) && pProperty->mnType == 13)
                    fPingDist = *pProperty->GetFloat();
            }
            int32_t nExtra = 3;
            tPropertyMap* pMap2 = GetSpaceCombatTuning()->mp08;
            if (pMap2 != 0)
            {
                tProperty* pProperty = 0;
                if (pMap2->v24(0x05c2cc0e, &pProperty) && pProperty->mnType == 9)
                    nExtra = *pProperty->GetInt();
            }
            if (fNow - pOwner->mf12c > fPingDist)
            {
                if (nVisitors + nFleets < mn1b8 + nExtra)
                {
                    pOwner->mf12c = -pOwner->mf12c;
                    FUN_00ff8ad0();
                }
                else
                {
                    pOwner->mf12c = 0.0f;
                }
            }
        }
    }

    tGameDataList* pUFOList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                          (void*)FUN_00ad48b0, (void*)FUN_00b1e500,
                                                          g_nounListUFO);
    int32_t nCount = (int32_t)(pUFOList->mData.mpEnd - pUFOList->mData.mpBegin);
    void** pNew = 0;
    if (nCount != 0)
        pNew = (void**)operator_new((uint32_t)nCount * 4, g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
    void* pNewEnd = 0;
    FUN_00829110(&pNewEnd, pUFOList->mData.mpBegin, pUFOList->mData.mpEnd, pNew, bHostile ? 1 : 0);
    int32_t nCopied = (int32_t)((void**)pNewEnd - pNew);
    int32_t i = 0;
    int32_t nIndex = 0;
    if (nCopied > 0)
    {
        do
        {
            cSimGameData* pNoun = (cSimGameData*)pNew[i];
            if (pTickHook != 0)
                pTickHook->FUN_00e0df70(pNoun, pNoun->mObj34.v2c());
            if (pNoun->mn714 != 0 && !pNoun->FUN_00c38990(0))
            {
                if (bHostileToAll)
                    pNoun->mp6c8->mn5fc |= 0x1000;
                else
                    pNoun->mp6c8->mn5fc &= ~0x1000u;
                if (bMissionsPrevent)
                    pNoun->mp6c8->mn5fc |= 0x2000;
                else
                    pNoun->mp6c8->mn5fc &= ~0x2000u;
                if (bMissionActive)
                    pNoun->mp6c8->mn5fc |= 0x4000;
                else
                    pNoun->mp6c8->mn5fc &= ~0x4000u;
                if (bHostile)
                    pNoun->mp6c8->mn5fc |= 0x8000;
                else
                    pNoun->mp6c8->mn5fc &= ~0x8000u;
                if (pNoun->mn714 == 3)
                {
                    pNoun->mn6b0 = nIndex;
                    ++nIndex;
                }
                uint64_t nNow = GameTimeManager()->FUN_00b316c0();
                pNoun->FUN_00c38740(fElapsed, (double)nNow * 0.001);
            }
            ++i;
        } while (i < nCopied);
    }

    void** pSlot = pNew;
    while (pSlot < (void**)pNewEnd)
    {
        if (*pSlot != 0)
            ((tRefObject*)*pSlot)->Release();
        ++pSlot;
    }
    if (pNew != 0 && ((int32_t*)pNew)[-1] != 0)
        operator_delete_array(pNew);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffb830
// ---------------------------------------------------------------------------------------------
void cSPSimPlanetHighLOD::CheckForCityDestruction()
{
    float fWater = PlanetModel()->GetWaterHeight();
    float fWater2 = fWater * fWater;
    tCityVector cities;
    GetActivePlanet();
    if (!PlanetModel()->mp24->v50())
    {
        cities.DoDestroy();
        return;
    }

    int32_t nEmpire = -1;
    cGameNounManager* pManager = NounManager();
    tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                       (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                       g_nounListPlanet);
    tPtrVector* pNouns = &pList->mData;
    int32_t nCount = (int32_t)(pNouns->mpEnd - pNouns->mpBegin);
    for (int32_t i = 0; i < nCount; ++i)
    {
        cSimGameData* pCity = (cSimGameData*)pNouns->mpBegin[i];
        cCityHall* pHall = pCity->GetCityHall();
        tVector3 vPos;
        PlanetModel()->DirectionToSurfacePosition(&vPos, pCity->mObj120.v2c());
        bool bInside = vPos.x * vPos.x + vPos.y * vPos.y + vPos.z * vPos.z < fWater2;

        bool bDamaged = pHall->mObj120.FUN_008e7f80() != 0;
        if (bDamaged)
        {
            nEmpire = pHall->mn15c;
        }
        else
        {
            if (!bInside)
                continue;
            nEmpire = -1;
        }

        cSimGameData* pRef = pCity;
        if (pCity != 0)
            pCity->AddRef();
        if (cities.mpEnd < cities.mpCapacity)
        {
            *cities.mpEnd = pCity;
            ++cities.mpEnd;
            if (pCity != 0)
                pCity->AddRef();
        }
        else
        {
            cities.DoInsertValue(cities.mpEnd, pRef);
        }
        if (pRef != 0)
            pRef->Release();

        if (GetCurrentGameMode() == (uint32_t)g_gameModeGalaxy)
        {
            if (bInside)
            {
                if (pCity->v4c() != GetPlayerEmpireID())
                {
                    RelationshipManager()->RecordEvent(0x0526e5cf, (void*)GetPlayerEmpireID(),
                                                       (void*)(uint32_t)pCity->v4c(), 1.0f);
                }
            }
            if (pCity->mf220 > g_kRealZero)
            {
                tGameDataList* pList2 = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                                    (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                                    g_nounListPlanet);
                tPtrVector* pNouns2 = &pList2->mData;
                int32_t nCount2 = (int32_t)(pNouns2->mpEnd - pNouns2->mpBegin);
                for (int32_t k = 0; k < nCount2; ++k)
                {
                    cSimGameData* pOther = (cSimGameData*)pNouns2->mpBegin[k];
                    if ((void*)pOther->v4c() == (void*)pCity->v4c())
                        pOther->FUN_00bdbf10();
                }
            }
        }
    }

    void** pSlot = cities.mpBegin;
    while (pSlot != cities.mpEnd)
    {
        FUN_00ffa900((cSimGameData*)*pSlot, nEmpire);
        ++pSlot;
    }
    pSlot = cities.mpBegin;
    while (pSlot < cities.mpEnd)
    {
        if (*pSlot != 0)
            ((tRefObject*)*pSlot)->Release();
        ++pSlot;
    }
    if (cities.mpBegin != 0 && ((int32_t*)cities.mpBegin)[-1] != 0)
        operator_delete_array(cities.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffbb20
// ---------------------------------------------------------------------------------------------
void cSPSimPlanetHighLOD::OnTick(uint32_t nTimeLo, uint32_t nTimeHi)
{
    FUN_00ffabc0();
    SolarSystemUpdateNPC_UFOs(nTimeLo);
    CheckForCityDestruction();

    cPlanetRecord* pPlanet = GetActivePlanet();
    void* pEmpire = pPlanet->FUN_00c71e30();
    if (pEmpire != 0 && pEmpire != GetPlayerEmpire())
    {
        NounManager()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
                                         (void*)FUN_00b1e500, g_nounListPlanet);
    }

    FUN_00ffaf20(nTimeLo);
    FUN_00ffa690();

    uint64_t nTime = ((uint64_t)nTimeHi << 32) | nTimeLo;
    mp1b0->Tick((float)nTime * 0.001f);

    if (pPlanet->FUN_00c70e00() == 5)
        mp28->v10(nTimeLo, nTimeHi, (void*)pPlanet->FUN_008414c0());

    if (pPlanet->FUN_00c70e00() == 5 || pPlanet->FUN_00c70e00() == 4)
        FUN_00ffab60();

    cTerrainSphere* pSphere = (cTerrainSphere*)NounManager()->GetCurrentTerrainSphere();
    if (pSphere->Check())
    {
        if (mp1bc == 0)
        {
            tEffectsManager* pEffects = EffectsManagerPtr();
            if (mp1bc != 0)
            {
                tEffectHandle* pOld = mp1bc;
                mp1bc = 0;
                pOld->Release();
            }
            if (pEffects->v2c(0x20caebfa, 0, &mp1bc))
                mp1bc->v08(0);
        }
    }
    else
    {
        if (mp1bc != 0)
        {
            mp1bc->v0c(1);
            if (mp1bc != 0)
            {
                tEffectHandle* pOld = mp1bc;
                mp1bc = 0;
                pOld->Release();
            }
        }
    }

    if (GetCurrentGameMode() == (uint32_t)g_gameModeGalaxy && mb158)
        FUN_00ff7530(nTimeLo, nTimeHi);

    tVector3 vPos;
    vPos.x = g_defaultVector[0];
    vPos.y = g_defaultVector[1];
    vPos.z = g_defaultVector[2];
    tVector3 vSize;

    tSlotMessage msg;
    msg.mpVtable = g_slotMessageBaseVtable;
    msg.mnRefCount = 0;
    msg.mpVtable = g_slotMessageVtable;
    msg.mnKey = g_ufoMessageKey;
    msg.mn38 = 0;
    FUN_01015df0();

    tDOMWrapper* pNode = (tDOMWrapper*)0;
    tStringKey nString;
    tVector3* pComputed;
    if (pNode != 0 && pNode->FUN_00a98020() && pNode->FUN_00ff0420() != 0)
    {
        tVector3* pv = (tVector3*)pNode->FUN_00ff0420()->mObjC0.v2c();
        vPos.x = pv->x;
        vPos.y = pv->y;
        vPos.z = pv->z;
        pComputed = FUN_0095df60(&nString, g_szUFOString, (uint32_t)App()->v50()->v1c());
    }
    else
    {
        cSimInventory* pInventory = GetUFOSimulator()->GetPlayerInventory();
        tVector3* pv = (tVector3*)pInventory->mObj34.v2c();
        vPos.x = pv->x;
        vPos.y = pv->y;
        vPos.z = pv->z;
        cSimInventory* pInventory2 = GetUFOSimulator()->GetPlayerInventory();
        pComputed = FUN_0059aed0(&nString, g_szUFOString, (uint32_t)pInventory2->mObj34.v30());
    }
    vSize = *pComputed;

    msg.mpPosition = &vPos;
    msg.mpSize = &vSize;
    EA::Messaging::GetServer()->v14(msg.mnKey, &msg, 0);
    msg.Destruct();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffbe60
// ---------------------------------------------------------------------------------------------
bool cSPSimulatorPlayerUFO::Write(cOutStream* pStream)
{
    tVarListFrame frame;
    frame.mnValue = 0x02f011e8;
    tIStream* pSink = pStream->v20()->v18();
    EA_IO_WriteUint32(pSink, &frame.mnValue, 1, 0);
    frame.mSerializer.Construct((void*)((char*)this - 8), g_varListUFO, 0x1a80d26);
    return frame.mSerializer.Serialize(pStream);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffbf60
// ---------------------------------------------------------------------------------------------
void cSPSimPlanetHighLOD::Init()
{
    void* pListener = this != 0 ? (void*)((uint8_t*)this + 0x10) : 0;
    tMessageServer* pServer = EA::Messaging::GetServer();
    mp2c = (void*)pServer;
    mp30 = pListener;
    mp34 = g_ufoListenerVtable;
    mn38 = 1;
    mn3c = 0;
    if (pServer != 0 && pListener != 0)
        pServer->v24(pListener, 0x057f3749);
    SimTicker()->v50(this);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffbfe0
// ---------------------------------------------------------------------------------------------
bool cSPSimPlanetHighLOD::FUN_00ffbfe0()
{
    uint64_t nElapsed = mTimer80.GetElapsedTime();
    return nElapsed > (uint64_t)mnA0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffc030
// ---------------------------------------------------------------------------------------------
void cSPSimPlanetHighLOD::FUN_00ffc030()
{
    cTerrainSphere* pSphere = (cTerrainSphere*)NounManager()->GetCurrentTerrainSphere();
    pSphere->FUN_00c77bf0(0x05c2d1ab);
    tEffectsGlobal* pEffects = FUN_0067cac0();
    if (pEffects->mp4c != 0 && ((uint32_t*)pEffects->mp4c)[2] == (uint32_t)0x43c18587)
    {
        pEffects->FUN_0067c8c0(0x43c18587, 1);
        FUN_010666a0()->FUN_01065d20();
    }
    mTimer80.Restart();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ffc160
// ---------------------------------------------------------------------------------------------
bool cSPSimPlanetHighLOD::CheckAndReplaceData(void* pKey, void* pB, void* pC)
{
    cEmpireKey* pOwnKey = (cEmpireKey*)GetPlayerEmpire();
    if (pKey != 0)
        pOwnKey->SetUFOKey(&pKey);

    tUFOData* pNoun = NounManager()->CreateNoun(g_nounListUFO);
    tUFOData* pNew = pNoun != 0 ? (tUFOData*)pNoun->v0c(0xb033b403) : 0;

    tUFOData* pOld = mp40;
    if (pNew != pOld)
    {
        if (pNew != 0)
            pNew->AddRef();
        mp40 = pNew;
        if (pOld != 0)
            pOld->Release();
    }

    tUFOData* pData = mp40;
    pData->Init(0, GetPlayerEmpire());
    SimTicker()->v50(this);

    void* pListener = (void*)((uint8_t*)this + 0x10);
    tMessageServer* pServer = EA::Messaging::GetServer();
    mp2c = (void*)pServer;
    mp30 = pListener;
    mp34 = g_ufoListenerVtable;
    mn38 = 1;
    mn3c = 0;
    if (pServer != 0 && pListener != 0)
        pServer->v24(pListener, 0x057f3749);
    return true;
}
