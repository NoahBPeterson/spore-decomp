// Slice s00cfd3a0: SP::cCivModeStrategy::HandleMessage (0x00cfd3a0, 3516 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), like the rest of cCivModeStrategy
// (see s00cfbc10, whose retail field offsets are reused here).
//
// HandleMessage overrides the message-listener base at +0x24, so `this` is that subobject:
// strategy fields appear at offset-0x24 and strategy methods are called with this-0x24.
#include "types.h"

enum {
    kGameCiv = 0x1654C04,
    kGameCivNoTutorial = 0x1654C05
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------- game objects
struct ISpatialObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                       // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual void* GetModel();                                   // +0xac
};
struct cCityHall {
    uint32_t pad0[13];
    ISpatialObject mSpatial;               // +0x34
};
struct cCity {
    void* vftable;
    uint32_t pad04[0x120 / 4 - 1];
    ISpatialObject mSpatial;               // +0x120
    cCityHall* GetCityHall();              // 0x00bd9b40
    void GetCameraSetup(Vector3& pos, float& distance);   // 0x00bd7f70
};

struct cSpeciesProfile {
    uint32_t pad0[0x504 / 4];
    uint32_t mEffectAnchor;                // +0x504
};
struct cTribeList {
    int* mpBegin;
    int* mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
};
struct cCivFlagsTarget {
    uint8_t pad0[0x2e0];
    bool mbFlag0;                          // +0x2e0
    bool mbFlag1;                          // +0x2e1
    bool mbFlag2;                          // +0x2e2
    bool mbFlag3;                          // +0x2e3
    bool mbFlag4;                          // +0x2e4
    bool mbFlag5;                          // +0x2e5
    bool mbFlag6;                          // +0x2e6
    void FUN_be88d0(void* p);              // 0x00be88d0
    void FUN_bd7e40();                     // 0x00bd7e40
    void FUN_bd9060(struct cCivilization* civ);   // 0x00bd9060
    void FUN_bd9140(struct cCivilization* civ);   // 0x00bd9140
    void FUN_bd7ea0();                     // 0x00bd7ea0
    void FUN_bdb0b0();                     // 0x00bdb0b0
    void FUN_be4b30(struct cCivilization* civ);   // 0x00be4b30
};
struct cCivilization {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void* GetFocus(int a, int b);  // +0x4c
    uint32_t pad04[(0x44c - 4) / 4];
    cCivFlagsTarget* mpFlagsTarget;        // +0x44c
    cTribeList* GetTribes();               // 0x00bef6c0
    cSpeciesProfile* GetProfile();         // 0x00bef950
    int GetTool(uint32_t id);              // 0x00bef980
    bool HasTool(int tool);                // 0x00bef970
};
struct cGameNounManager {
    void* GetCurrentTerrainSphere();       // 0x00f67d90
    cCity* GetPlayerCity();                // 0x00b25c30
    cCivilization* GetPlayerCivilization();   // 0x00b25fb0
};
cGameNounManager* NounManager();           // 0x00b3d300
uint32_t GetCurrentGameMode();             // 0x00b5b800

struct cTerrainSphereHelper { void SetSpecies(const ResourceKey* key); };   // 0x00cf6dc0

struct cGonzagoModelWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0();
    virtual void SetModelVisible(void* model, int visible);     // +0xb4
    virtual void SetModelLOD(void* model, float distance);      // +0xb8
    virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void SetModelEffect(void* model, uint32_t id, float* value, int a, int b);   // +0xc8
};
cGonzagoModelWorld* GonzagoModelWorld();   // 0x00b3d520

struct cCameraManager {
    uint8_t pad0[0x364];
    bool mbLocked;                         // +0x364
};
cCameraManager* CameraManager();           // 0x00b3d280

struct cGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetHandler(void* handler, int a, int b);       // +0x20
    uint8_t pad04[0x110 - 4];
    int mLockCount;                        // +0x110
};
cGameInputManager* GameInputManager();     // 0x00b3d250

struct cGameTimeManager {
    void IncPauseGate(uint32_t reason);    // 0x00b32220
};
cGameTimeManager* GameTimeManager();       // 0x00b3d380
__forceinline void PauseForHint()
{
    cGameTimeManager* timeManager = GameTimeManager();
    timeManager->IncPauseGate(0x4bf38a7);
}

struct cPreloadParams {
    uint32_t mTypeID;
    uint16_t mPriority;
    uint16_t mFlags;
};
struct cResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool IsLoaded(const ResourceKey* key);               // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Preload(const ResourceKey* key, const cPreloadParams* params);   // +0x4c
};
cResourceManager* ResourceManager();       // 0x00401010

struct cKeyVector {                        // eastl::vector<ResourceKey, sp_vector_allocator>
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cEventLog { void FUN_dd6d70(); };   // 0x00dd6d70
cEventLog* EventLog();                     // 0x00b3d3e0

// 0x30-byte camera/locator message (ctor 0x00ad7a30 / 0x00ad79d0, dtor 0x00ad7ad0).
struct cCameraMessage {
    uint32_t data[8];
    float mDistance;                       // +0x20
    uint32_t pad24[3];
    cCameraMessage(void* target);          // 0x00ad7a30
    cCameraMessage(const Vector3& pos, void* from);   // 0x00ad79d0
    ~cCameraMessage();                     // 0x00ad7ad0
    void* GetTarget();                     // 0x00ad7b70
};
void* MakeCameraTarget(void* p);           // 0x00b18e00
void* FindNearestReachableCommodity(void* target, int a);   // 0x00dcd720

struct cMessageManager {
    void PostMessage(uint32_t id, void* msg, int a);     // 0x00ae09b0
    void PostString(const char* name, int a, int b, int c, int d, int e);   // 0x00ae0930
    uint32_t GetTransitionID(const char* name);          // 0x00ad7db0
};
cMessageManager* MessageManager();         // 0x00b3d4d0

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Post(uint32_t id, int a, int b);                 // +0x14
    virtual void PostDelayed(uint32_t id, void* msg, int a, int b);   // +0x18
};
IMessageServer* MessageServer();           // 0x0067dcc0

struct cConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual uint32_t GetConfig(uint32_t id);                    // +0x30
};
cConfigManager* ConfigManager();           // 0x0067dd30

struct cMissionHooks { void FUN_b27170(); };   // 0x00b27170
cMissionHooks* MissionHooks();             // 0x00b3d340

struct cTutorialSystem {
    void StartModeTutorial(int a, uint32_t mode, int b);  // 0x00e3e350
};
cTutorialSystem* TutorialSystem();         // 0x00b3d410

struct cCivUIResult {
    uint32_t pad0[3];
    uint8_t* mpData;                       // +0x0c
    void FUN_7eb820(int a);                // 0x007eb820
};
struct cCivUI {
    cCivUIResult* ShowPanel(int id, Vector3 pos);   // 0x00ae37c0
    void FUN_ae5930();                     // 0x00ae5930
    void FUN_ae3b30(int a, int b);         // 0x00ae3b30
    void UpdateMinimapCityIcon(uint32_t a);   // 0x00ae4ec0
    void FUN_ae59a0();                     // 0x00ae59a0
};
cCivUI* CivUI();                           // 0x00b26930

struct cHintData;
struct cHintManager {
    void ShowHint(Vector3 pos, cHintData* data, int a, float ox, float oy, float oz, int b, int c);   // 0x0067aaf0
};
cHintManager* GetHintManager();            // 0x0067caf0
struct cHintsB { void Set(uint32_t id, uint32_t* anchor); };   // 0x0060d860
cHintsB* GetHintsB();                      // 0x0067cb30

struct cAchievementsController {
    void Trigger(uint32_t id, int a, int b);   // 0x00676ed0
};
cAchievementsController* AchievementsController();   // 0x00675250

struct cMissionLog { void FUN_e2f270(int a); };   // 0x00e2f270
cMissionLog* MissionLog();                 // 0x00b3d4f0

struct cSimulator {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void SetEnabled(int a, int b);                      // +0x10
};
cSimulator* FUN_00bd83e0();

struct cTerrainCursor {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    virtual void Refresh();                                     // +0x64
};
cTerrainCursor* GetGameTerrainCursor();    // 0x00b30d70

float GetElapsedSeconds();                 // 0x00805080

struct cHintGlobal { void FUN_cfa3b0(); }; // 0x00cfa3b0

extern Vector3 kHintPosSea;                // 0x01581b60
extern Vector3 kHintPosA;                  // 0x01581b18
extern Vector3 kHintPosB;                  // 0x01581b24
extern Vector3 kHintPosC;                  // 0x01581b30
extern cHintData kHintDataA;               // 0x01581bcc
extern cHintData kHintDataSea;             // 0x01581bd0
extern cHintData kHintDataC;               // 0x01581bd8
extern cHintGlobal kHintGlobal;            // 0x01581bdc

// ---------------------------------------------------------------- messages
struct cEditorResult {
    virtual void v00(); virtual void v04();
    virtual void Release();                // +0x08
    uint32_t mEditorID;                    // +0x0c
    uint32_t pad10;
    uint32_t mExitReason;                  // +0x14
    ResourceKey mSpeciesKey;               // +0x18
    uint32_t pad24[8];
    bool mbCancelled;                      // +0x44
};
struct cEditorResultPtr {                  // AutoRefCount<cEditorResult>
    cEditorResult* mpObject;
    cEditorResultPtr& operator=(cEditorResult* p);   // 0x00572620
};

// generic message: parameters in 8-byte slots starting at +8
struct cMessage {
    void* vftable;
    uint32_t pad04;
    union { uint32_t mParam0; float mfParam0; cCity* mpCity; };   // +0x08
    uint32_t pad0c;
    void* mpParam1;                        // +0x10
    uint32_t pad14;
    float mfParam2;                        // +0x18
    uint32_t pad1c;
    float mfParam3;                        // +0x20
    uint32_t pad24;
    float mfParam4;                        // +0x28
};

// ---------------------------------------------------------------- the strategy
struct cCityInputStrategy {
    uint32_t pad0;
    uint8_t mHandler[4];                   // +0x04 (input handler subobject)
    void SetMode(uint32_t mode);           // 0x00cf4c00
};
struct cCityDisplayStrategy {
    void OnCityMessage(uint32_t a);        // 0x00ce8de0
};
struct cCivModeStrategyRaw {
    uint8_t pad0[0xe8];
    struct { uint8_t pad[0x134]; bool mbFlag; }* mpInputStrategy;   // +0xe8
};
extern cCivModeStrategyRaw* gCivModeStrategy;   // 0x0169d2c8

namespace SP {

struct cGonzagoSubsystem {
    virtual void s00();
    uint32_t pad04[8];
};
struct IMessageListener {
    virtual bool HandleMessage(uint32_t messageID, void* message);
};

struct cCivModeStrategy : public cGonzagoSubsystem, public IMessageListener {
    bool mbReturningFromEditor;            // +0x28
    uint8_t pad29[3];
    uint32_t pad2c[10];
    cKeyVector mOptionalBakedItems;        // +0x54
    uint32_t pad68[32];
    cCityInputStrategy* mpInputStrategy;   // +0xe8
    cCityDisplayStrategy* mpDisplayStrategy;  // +0xec
    uint32_t padf0[4];
    cEditorResultPtr mEditorResult;        // +0x100
    uint32_t pad104[7];
    bool mbTutorialPending;                // +0x120
    bool mbTutorialRequested;              // +0x121
    uint8_t pad122[0x148 - 0x122];
    bool mbIntroPending;                   // +0x148

    virtual bool HandleMessage(uint32_t messageID, void* message);

    void NotifyDataDestroyed(void* p);     // 0x00cf8860
    void FUN_cfd220(void* p);              // 0x00cfd220
    void FinishMaxLoad();                  // 0x00cfb660
    void SendVehicleToCommodity();         // 0x00cf9ba0
    bool StartTechLevelUpgradeHintIfAppropriate();   // 0x00cfa0c0
    bool FUN_cf78d0();                     // 0x00cf78d0
    bool CanBuildSeaVehicles();            // 0x00cf75d0
    void FUN_cf8e00();                     // 0x00cf8e00
    void FUN_cf7520();                     // 0x00cf7520
    void FUN_cfa120();                     // 0x00cfa120
    void ShowIntro();                      // 0x00cf7ad0
    void* GetCameraTarget(int a);          // 0x00cf7d40
};

// @ 0x00cfd3a0 ?HandleMessage@cCivModeStrategy@SP@@
bool cCivModeStrategy::HandleMessage(uint32_t messageID, void* message)
{
    cMessage* msg = (cMessage*)message;
    switch (messageID) {
    case 0x1a0219e: {
        void* p = msg->mpParam1;
        if (p) {
            switch (msg->mParam0) {
            case 1:
                GetCurrentGameMode();
                return false;
            case 3:
                FUN_cfd220(p);
                return false;
            case 4:
                NotifyDataDestroyed(p);
                return false;
            }
        }
        break;
    }

    case 0x164b4eb: {
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        if (civ && civ->GetTribes()->empty()) {
            if (GetCurrentGameMode() == kGameCivNoTutorial)
                break;
            if (msg) {
                MessageServer()->PostDelayed(0x6130eb9, 0, 0, 0);
                cCity* city = msg->mpCity;
                cCityHall* hall = city->GetCityHall();
                cCameraMessage target(hall ? &hall->mSpatial : 0);
                float distance;
                Vector3 pos;
                city->GetCameraSetup(pos, distance);
                cCameraMessage locator(pos, target.GetTarget());
                locator.mDistance = distance;
                MessageManager()->PostMessage(0x115fa309, &target, 0);
                MessageManager()->PostMessage(0x1ad5e415, &locator, 0);
                MessageManager()->PostString("CVG_Lose", 1, 0, 0, 0, 0);
                CivUI()->ShowPanel(9, city->mSpatial.GetPosition());
                GetHintsB()->Set(0x5ab74e7a, &NounManager()->GetPlayerCivilization()->GetProfile()->mEffectAnchor);
            }
            AchievementsController()->Trigger(0xd456d958, 8, 1);
            return false;
        }
        cCityDisplayStrategy* display = mpDisplayStrategy;
        if (display) {
            display->OnCityMessage(msg->mParam0);
            return false;
        }
        break;
    }

    case 0x30c11c7: {
        cEditorResult* result = (cEditorResult*)message;
        if (!result)
            break;
        if (result->mEditorID == 0x66787bb) {
            mEditorResult = result->mbCancelled ? 0 : result;
            return false;
        }
        if (result->mEditorID != 0x116d51d)
            break;
        if (mbReturningFromEditor) {
            if (result->mExitReason == 0x98e03c0d) {
                mEditorResult = result->mbCancelled ? 0 : result;
                if (!result->mbCancelled) {
                    ((cTerrainSphereHelper*)NounManager()->GetCurrentTerrainSphere())->SetSpecies(&result->mSpeciesKey);
                    TutorialSystem()->StartModeTutorial(1, kGameCivNoTutorial, 1);
                    if (mbTutorialPending)
                        mbTutorialRequested = true;
                }
            }
            return true;
        }
        mEditorResult = result->mbCancelled ? 0 : result;
        return false;
    }

    case 0x5356bb5: {
        float start = msg->mfParam0;
        if (1.5f > GetElapsedSeconds() - start) {
            MessageServer()->PostDelayed(0x5356bb5, msg, 0, 0);
            return false;
        }
        FinishMaxLoad();
        return false;
    }

    case 0x44f1189: {
        if (GetCurrentGameMode() != kGameCiv)
            break;
        uint32_t id = msg->mParam0;
        if (id == MessageManager()->GetTransitionID("TRG2CVG_CivStart")) {
            if (!NounManager()->GetPlayerCity())
                CivUI()->FUN_ae5930();
            cGonzagoModelWorld* world = GonzagoModelWorld();
            ISpatialObject* hall = &NounManager()->GetPlayerCity()->GetCityHall()->mSpatial;
            world->SetModelVisible(hall->GetModel(), -1);
            world->SetModelLOD(hall->GetModel(), -1.0f);
            float value = 1.0f;
            world->SetModelEffect(hall->GetModel(), 0x13, &value, 1, 0);
            for (int i = 0; i < mOptionalBakedItems.size(); i++) {
                ResourceKey key = mOptionalBakedItems.mpBegin[i];
                if (key.instanceID != 0 && !ResourceManager()->IsLoaded(&key)) {
                    cPreloadParams params;
                    params.mTypeID = 0x2ea8fb98;
                    params.mPriority = 0;
                    params.mFlags = 2;
                    ResourceManager()->Preload(&key, &params);
                }
            }
            MessageServer()->PostDelayed(0x6270d2f, 0, 0, 0);
            return true;
        }
        if (id == MessageManager()->GetTransitionID("CVG_SendVehicleToCommodity")) {
            SendVehicleToCommodity();
            return false;
        }
        if (id == MessageManager()->GetTransitionID("CVG_PRE_NewCityAppears")) {
            if (ConfigManager()->GetConfig(0x4ea96cb) > 0) {
                cCivilization* civ = NounManager()->GetPlayerCivilization();
                if (civ->HasTool(civ->GetTool(0x756d422)) || civ->HasTool(civ->GetTool(0x45cdf1a)) ||
                    civ->HasTool(civ->GetTool(0xc0617b2f))) {
                    PauseForHint();
                    GetHintManager()->ShowHint(kHintPosSea, &kHintDataSea, 0, -1.0f, -1.0f, 0.0f, 0, 0);
                    return false;
                }
            }
            break;
        }
        if (id == MessageManager()->GetTransitionID("CVG_Capture") ||
            id == MessageManager()->GetTransitionID("CVG_Capture_Nuked")) {
            cCivilization* civ = NounManager()->GetPlayerCivilization();
            cCivFlagsTarget* target = civ->mpFlagsTarget;
            if (target->mbFlag0)
                target->FUN_be88d0(civ->GetFocus(0, 0));
            if (StartTechLevelUpgradeHintIfAppropriate() || FUN_cf78d0())
                return true;
            if (CanBuildSeaVehicles()) {
                FUN_cf8e00();
                FUN_cf7520();
                return true;
            }
            FUN_cfa120();
            return true;
        }
        if (id != MessageManager()->GetTransitionID("CVG_UnlockSea") &&
            id != MessageManager()->GetTransitionID("CVG_UnlockAir")) {
            if (id == MessageManager()->GetTransitionID("CVG_UnlockUFO")) {
                gCivModeStrategy->mpInputStrategy->mbFlag = true;
                PauseForHint();
                GameInputManager()->mLockCount++;
                cCameraManager* camera = CameraManager();
                if (camera)
                    camera->mbLocked = false;
                MessageServer()->Post(0x445f729, 0, 0);
                GetGameTerrainCursor()->Refresh();
                return false;
            }
            if (id == MessageManager()->GetTransitionID("CVG_Lose")) {
                MissionHooks()->FUN_b27170();
                EventLog()->FUN_dd6d70();
                PauseForHint();
                return false;
            }
            break;
        }
        PauseForHint();
        kHintGlobal.FUN_cfa3b0();
        return false;
    }

    case 0x53836de: {
        uint32_t id = msg->mParam0;
        bool flag = msg->mpParam1 != 0;
        Vector3 pos(msg->mfParam2, msg->mfParam3, msg->mfParam4);
        if (!id) {
            CivUI()->ShowPanel(0xb, pos);
            return false;
        }
        cCivUIResult* panel = CivUI()->ShowPanel(flag ? 0xc : 0xd, pos);
        panel->FUN_7eb820(10);
        *(uint32_t*)(panel->mpData + 0x24) = id;
        return false;
    }

    case 0x56cfe69: {
        void* commodity = FindNearestReachableCommodity(((cCivModeStrategy*)gCivModeStrategy)->GetCameraTarget(0), 0);
        if (!commodity)
            break;
        cCameraMessage target(MakeCameraTarget(commodity));
        MessageManager()->PostMessage(0x9b464f84, &target, 0);
        return false;
    }

    case 0x5668f43:
        CivUI()->FUN_ae3b30(0, 0);
        return false;

    case 0x5badd9f:
        CivUI()->UpdateMinimapCityIcon(msg->mParam0);
        return false;

    case 0x5bff9c8:
        CivUI()->FUN_ae59a0();
        return false;

    case 0x5dbc31e: {
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag0) {
            target->FUN_be88d0(civ->GetFocus(0, 0));
            return false;
        }
        break;
    }

    case 0x5dfb77f: {
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag2) {
            target->FUN_be4b30(civ);
            return false;
        }
        break;
    }

    case 0x5dfb3c8: {
        cCivFlagsTarget* target = NounManager()->GetPlayerCivilization()->mpFlagsTarget;
        if (target && target->mbFlag1) {
            target->FUN_bd7e40();
            return false;
        }
        break;
    }

    case 0x5dfb782: {
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag3) {
            target->FUN_bd9060(civ);
            return false;
        }
        break;
    }

    case 0x5f4d02a: {
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        cCivFlagsTarget* target = civ->mpFlagsTarget;
        if (target && target->mbFlag5) {
            target->FUN_bd9140(civ);
            return false;
        }
        break;
    }

    case 0x5dfb786: {
        if (GetCurrentGameMode() != kGameCiv)
            break;
        cCivFlagsTarget* target = NounManager()->GetPlayerCivilization()->mpFlagsTarget;
        if (target && target->mbFlag4) {
            target->FUN_bd7ea0();
            return false;
        }
        break;
    }

    case 0x604bf01: {
        cCivFlagsTarget* target = NounManager()->GetPlayerCivilization()->mpFlagsTarget;
        if (target && target->mbFlag6) {
            target->FUN_bdb0b0();
            return false;
        }
        break;
    }

    case 0x66e0e11:
        FUN_00bd83e0()->SetEnabled(1, 0);
        return false;

    case 0x6270d2f:
        if (ConfigManager()->GetConfig(0x4ea96cb) > 0) {
            PauseForHint();
            GetHintManager()->ShowHint(kHintPosA, &kHintDataA, 0, -1.0f, -1.0f, 0.0f, 0, 0);
            GetHintManager()->ShowHint(kHintPosB, &kHintDataA, 0, -1.0f, -1.0f, 0.0f, 0, 0);
            GetHintManager()->ShowHint(kHintPosC, &kHintDataC, 0, -1.0f, -1.0f, 0.0f, 0, 0);
            MissionLog()->FUN_e2f270(1);
            return false;
        }
        break;

    case 0x670eccd:
        if (ConfigManager()->GetConfig(0x4ea96cb) == 0 && mbIntroPending) {
            ShowIntro();
            return false;
        }
        break;

    case 0x679c40d:
        if (GetCurrentGameMode() == kGameCiv) {
            mpInputStrategy->SetMode(ConfigManager()->GetConfig(0x679b873));
            GameInputManager()->SetHandler(mpInputStrategy->mHandler, 0, 0);
        }
        break;
    }
    return false;
}

}  // namespace SP
