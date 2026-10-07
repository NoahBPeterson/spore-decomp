// SP::cCreatureModeStrategy::HandleMessage  @ 0x00d42ea0
//
// ~2.9 KB message handler of the creature game (/O2 /arch:SSE, no EH frame). It is the
// IMessageListener override, so `this` is the listener subobject at +4 of the strategy and every
// field offset in the asm is (full offset - 4).
//
//   bool __thiscall HandleMessage(IMessageListener* this, uint32_t messageID, void* msg)  (ret 8)
//
// Messages: open the creature editor from the planet (0x4471c60), editor results (0x30c11c7),
// reload hot-key (0xf62def), game-event triggers (0x44f1189: tutorial/hint layers per event name),
// go-to-editor (0x4d9686f), hatch at nest (0x4f60b92), meteor impact (0x51b93cd), mark posse
// members (0x6566531), herd refresh (0x6555abc), input config reload (0x679c40d) and the
// UI enable/disable pair (0x533b6aa4 / 0xd33b6aa2).

#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);   // 0x00f473a0

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

// --- reference counting --------------------------------------------------------------------
class cRefCounted   // AddRef +4, Release +8
{
public:
    virtual void s00();
    virtual int AddRef();
    virtual int Release();
};

// eastl::intrusive_ptr-like holder; the T* ctor is shared out of line (0x0061df40).
template <class T>
struct RefPtr
{
    T* mpObject;
    __declspec(noinline) RefPtr(T* p) : mpObject(p) { if (p) p->AddRef(); }   // 0x0061df40
    ~RefPtr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};

// --- editor launch -------------------------------------------------------------------------
struct UIntVector   // eastl::vector<uint32_t, sp_vector_allocator>
{
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t  mAllocator;
    void push_back(const uint32_t& v);   // 0x00454860
};

struct PlanetRecordRef   // AutoRefCount<cPlanetRecord>
{
    void* mpObject;
    PlanetRecordRef& operator=(void* p);   // 0x00b5f950
};

class cEditorLaunchData : public cRefCounted
{
public:
    uint32_t pad04[2];
    uint32_t mEditorID;            // +0x0c
    ResourceKey mSpeciesKey;       // +0x10
    uint32_t pad1c[(0x34 - 0x1c) / 4];
    bool mbFlag34;                 // +0x34
    bool mbFlag35;
    bool mbFlag36;                 // +0x36
    bool mbFlag37;                 // +0x37
    bool mbFlag38;                 // +0x38
    bool mbFlag39;                 // +0x39
    bool mbFlag3a;
    bool mbFlag3b;                 // +0x3b
    bool mbFlag3c;                 // +0x3c
    bool mbFlag3d;                 // +0x3d
    uint16_t pad3e;
    uint32_t pad40[(0x70 - 0x40) / 4];
    UIntVector mTerrainKeys;       // +0x70
    uint32_t pad80[(0x90 - 0x80) / 4];
    uint32_t mReturnMode;          // +0x90
    PlanetRecordRef mpPlanet;      // +0x94
    uint32_t pad98;
    cEditorLaunchData();           // 0x005a9080
};

namespace SP { namespace Editor { void Launch(cEditorLaunchData* data); } }   // 0x005a9200

class cPlanetRecord { public: uint32_t GetID(); };   // 0x00596e60

class SlotMessage : public cRefCounted
{
public:
    uint32_t pad04;
    uint32_t mValue;               // +0x08
    uint32_t pad0c[(0x30 - 0x0c) / 4];
    uint32_t mID;                  // +0x30
    uint32_t pad34[3];
    SlotMessage(int a);            // 0x00421c80
};

class cMessageServer
{
public:
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void PostMessage(uint32_t id, void* msg, int a, int b);   // +0x18
};
cMessageServer* MessageServer();   // 0x0067dcc0
extern bool g_bEditorLaunchedFromPlanet;   // 0x01686af0

// --- game objects --------------------------------------------------------------------------
class cTerrainSphere
{
public:
    char  pad0[0x10e8];
    cPlanetRecord* mpPlanetRecord; // +0x10e8
    uint32_t pad10ec[(0x10fc - 0x10ec) / 4];
    uint32_t mTerrainKeys[4];      // +0x10fc
};

class cCombatant
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual bool IsAlive();        // +0x58
};

class cPosseTarget
{
public:
    char pad0[0xc0];
    cCombatant mCombatant;         // +0xc0
};

class cPosseMember
{
public:
    char pad0[0x1e8];
    int  mState;                   // +0x1e8
    uint32_t pad1ec;
    int  mbAttack;                 // +0x1f0
    char pad1f4[0x218 - 0x1f4];
    cPosseTarget* mpTarget;        // +0x218
};

struct cHerd
{
    char pad0[0x54];
    cPosseMember** mpBegin;        // +0x54
    cPosseMember** mpEnd;          // +0x58
    char pad5c[0x160 - 0x5c];
    class cNest* mpNest;           // +0x160
};

class cSPPaletteItemRollover;
class cNest { public: void SetSwatch(cSPPaletteItemRollover* swatch); };   // 0x00c69bb0

class cSPCreatureBase
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void Hatch();          // +0x90
    const ResourceKey* GetSpeciesKey();   // 0x00c0bc00
    cHerd* GetHerd();                     // 0x00c04590
};

class cGameNounManager
{
public:
    cSPCreatureBase* GetAvatar();                  // 0x00b1fdb0
    cTerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
    cHerd* GetPlayerHerd();                        // 0x00989360
};
namespace SP { cGameNounManager* NounManager(); }   // 0x00b3d300

class cGameTimeManager
{
public:
    bool IsPaused();                           // 0x00ad7150
    void TogglePauseGate(uint32_t id);         // 0x00b32280
    void IncPauseGate(uint32_t id);            // 0x00b32220
};
namespace SP { cGameTimeManager* GameTimeManager(); }   // 0x00b3d380
namespace SP { uint32_t GetCurrentGameMode(); }         // 0x00b5b800

class cConfigManager
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual uint32_t GetValue(uint32_t key);   // +0x30
};
namespace SP { cConfigManager* ConfigManager(); }   // 0x0067dd30

class cGameState
{
public:
    uint32_t GetEventID(const char* name);   // 0x00ad7db0
    void ResetEvents();                      // 0x00ad7dc0
    void FadeFromBlack();                    // 0x00adda70
};
cGameState* GameState();   // 0x00b3d4d0

class cTutorialManager { public: void Show(int a, uint32_t mode, int b); };   // 0x00e3e350
cTutorialManager* TutorialManager();   // 0x00b3d410
void* GetPlanetMgr();                  // 0x00b3d320

class cHintManager
{
public:
    void AddLayer(ResourceKey key, void* handler, int a, float x, float y, float z, int b, int c);   // 0x0067aaf0
};
cHintManager* HintManager();   // 0x0067caf0

class cUIHints { public: void Activate(uint32_t id); };   // 0x0067c830
cUIHints* UIHints();   // 0x0067cac0

class cCursorManager
{
public:
    void ShowCursor(int a);              // 0x00801930
    void SetLocalCursor(uint32_t id);    // 0x00801bb0
};
cCursorManager* CursorManager();   // 0x0067cab0

class cAppWindow
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual void* GetMainWindow();       // +0x38
};
class cApp
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual cAppWindow* GetWindowManager();   // +0x50
};
namespace SP { cApp* App(); }   // 0x0067dd10

class cCameraController { public: void SetMinDistance(float f); };   // 0x00d25ca0
cCameraController* GetCameraController(void* window);   // 0x00b60a50
extern float g_CreatureCameraMinDistance;   // 0x01582f30

class cEditorLauncher
{
public:
    class cEditorEntry* Find(uint32_t id);   // 0x00b6fa60
    void Select(uint32_t id);                // 0x00b707a0
};
class cEditorEntry
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual int GetState();                  // +0x60
};
cEditorLauncher* EditorLauncher();   // 0x00d37cb0

class cSPPaletteItemRollover;
class cSPDramaManager
{
public:
    void HandleMeteorImpact(void* msg);                // 0x00d4cb70
    cSPPaletteItemRollover* GetSwatchRollover();       // 0x0113ae10
};
cSPDramaManager* CreatureSimulator();   // 0x00d51660

namespace { void MarkEventAsOccurred(uint32_t id); }   // 0x00d387c0
namespace SP { void SetupHatchAtNest(); }               // 0x00d40ff0

// hint layer keys and handlers
extern const ResourceKey kHintTargeted;        // 0x01583248
extern const ResourceKey kHintTargeted2;       // 0x01583254
extern const ResourceKey kHintCLG2CRG_a;       // 0x01583230
extern const ResourceKey kHintCLG2CRG_b;       // 0x0158323c
extern const ResourceKey kHintCLG2CRG_c;       // 0x01583218
extern const ResourceKey kHintBrainUpgrade1;   // 0x01583224
extern const ResourceKey kHintBrainUpgrade4a;  // 0x0158326c
extern const ResourceKey kHintBrainUpgrade4b;  // 0x01583260
extern const ResourceKey kHintSpeciesMigrate;  // 0x01583278
extern const ResourceKey kHintFirstPartUnlock; // 0x01583284
extern char g_HintHandler;                     // 0x01583290
extern char g_HintHandler2;                    // 0x01583294

// --- the strategy --------------------------------------------------------------------------
class cCreatureModeInputStrategy
{
public:
    char pad0[0x54];
    bool mbActive;                 // +0x54
    void Init(uint32_t config);    // 0x00d36940
};

class cCreatureDisplayStrategy
{
public:
    void SetVisible(int a);                   // 0x00d2c200
    void SetPartVisible(uint32_t id, int a);  // 0x00d2b6e0
};

class cEditorResultData;
struct EditorResultPtr   // AutoRefCount<cEditorResultData>
{
    cEditorResultData* mpObject;
    EditorResultPtr& operator=(cEditorResultData* p);   // 0x00572620
};

struct EditorResultMessage
{
    uint32_t pad0[3];
    uint32_t mType;                // +0x0c
    uint32_t pad10[(0x44 - 0x10) / 4];
    bool mbCancelled;              // +0x44
};

class cCreatureModeActionHandler
{
public:
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void HandleAction(uint32_t id, void* data);   // +0x18
};

struct ActionData { uint32_t a; uint32_t b; uint32_t id; uint32_t pad[3]; };

struct Stopwatch
{
    uint32_t pad[6];
    void SetUnits(int units);      // 0x0093a1a0
    void Restart();                // 0x00571e80
};

class IGameMode { public: virtual void g0(); };
class IMessageListener
{
public:
    virtual int AddRef();
    virtual int Release();
    virtual bool HandleMessage(uint32_t messageID, void* msg);
};

namespace SP {

class cCreatureModeStrategy : public IGameMode, public IMessageListener
{
public:
    uint32_t pad08[(0x60 - 0x08) / 4];
    EditorResultPtr mEditorResult;                       // +0x60
    cCreatureModeInputStrategy* mpInputStrategy;         // +0x64
    cCreatureDisplayStrategy* mpDisplayStrategy;         // +0x68
    uint32_t pad6c[(0x88 - 0x6c) / 4];
    Stopwatch mReloadStopwatch;                          // +0x88
    uint32_t padA0;
    uint32_t mLoadingState;                              // +0xa4
    uint32_t padA8[(0xbc - 0xa8) / 4];
    cCreatureModeActionHandler** mActionHandlersBegin;   // +0xbc
    cCreatureModeActionHandler** mActionHandlersEnd;     // +0xc0
    uint32_t padC4[(0xdc - 0xc4) / 4];
    bool mbDisplayingEvolutionButton;                    // +0xdc
    bool field_DD;
    bool mbCanEnterEditor;                               // +0xde
    bool field_DF;
    uint32_t mAllPartsUnlockedColumn;                    // +0xe0
    bool mbWaitingForEditor;                             // +0xe4
    bool field_E5;
    bool mbEditorReturned;                               // +0xe6

    virtual bool HandleMessage(uint32_t messageID, void* msg);

    void ReloadConfig();                          // 0x00d42570
    void NotifyWantToGoToEditor(int a);           // 0x00d3c6a0
    void SwitchToMode(int mode);                  // 0x00d3af00
    static cCreatureModeStrategy* spInstance;     // 0x0169e294
};

static __forceinline void PauseGate(uint32_t id)
{
    cGameTimeManager* timeManager = GameTimeManager();
    timeManager->IncPauseGate(id);
}

static __forceinline void TogglePause(uint32_t id)
{
    cGameTimeManager* timeManager = GameTimeManager();
    timeManager->TogglePauseGate(id);
}

static __forceinline void AddHint(const ResourceKey& key, void* handler)
{
    HintManager()->AddLayer(key, handler, 0, -1.0f, -1.0f, 0.0f, 0, 0);
}

bool cCreatureModeStrategy::HandleMessage(uint32_t messageID, void* msg)
{
    switch (messageID)
    {
    case 0x4471c60:
    {
        if (GetCurrentGameMode() != 0x1654c01) return false;
        if (!mbCanEnterEditor) return false;
        if (GameTimeManager()->IsPaused())
            TogglePause(0x4bf38a8);
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        cPlanetRecord* planet = 0;
        if (sphere && sphere->mpPlanetRecord)
            planet = sphere->mpPlanetRecord;

        RefPtr<cEditorLaunchData> launchData(new("App", 0, 0, 0, 0) cEditorLaunchData());
        launchData->mEditorID = 0x465c50ba;
        launchData->mSpeciesKey = *avatar->GetSpeciesKey();
        launchData->mReturnMode = 0x64aa168;
        launchData->mpPlanet = planet;
        launchData->mbFlag34 = false;
        launchData->mbFlag36 = false;
        launchData->mbFlag38 = false;
        launchData->mbFlag37 = false;
        launchData->mbFlag39 = false;
        launchData->mbFlag3b = false;
        launchData->mbFlag3c = true;
        launchData->mbFlag3d = true;
        uint32_t terrainKey;
        terrainKey = sphere->mTerrainKeys[0];
        launchData->mTerrainKeys.push_back(terrainKey);
        terrainKey = sphere->mTerrainKeys[1];
        launchData->mTerrainKeys.push_back(terrainKey);
        terrainKey = sphere->mTerrainKeys[2];
        launchData->mTerrainKeys.push_back(terrainKey);
        terrainKey = sphere->mTerrainKeys[3];
        launchData->mTerrainKeys.push_back(terrainKey);
        Editor::Launch(launchData.get());

        if (planet)
        {
            uint32_t planetID = planet->GetID();
            RefPtr<SlotMessage> message(new("App", 0, 0, 0, 0) SlotMessage(0));
            message->mID = 0x5d02a72;
            message->mValue = planetID;
            MessageServer()->PostMessage(message->mID, message.get(), 0, 0);
        }
        g_bEditorLaunchedFromPlanet = true;
        return false;
    }

    case 0x30c11c7:
    {
        EditorResultMessage* result = (EditorResultMessage*)msg;
        if (!result) return false;
        if (result->mType == 0x12191ca)
        {
            mEditorResult = result->mbCancelled ? 0 : (cEditorResultData*)result;
            if (mLoadingState == 0x1654c00)
            {
                TutorialManager()->Show(1, 0x1654c01, 1);
                if (mbWaitingForEditor)
                    mbEditorReturned = true;
            }
        }
        else if (result->mType == 0x64aa168)
        {
            if (!result->mbCancelled)
                mEditorResult = (cEditorResultData*)result;
        }
        return false;
    }

    case 0xf62def:
    {
        uint32_t key = ((uint32_t*)msg)[4];
        if (GetPlanetMgr() && key == 0xad56080c)
        {
            ReloadConfig();
            mReloadStopwatch.SetUnits(5);
            mReloadStopwatch.Restart();
        }
        return true;
    }

    case 0x44f1189:
    {
        if (GetCurrentGameMode() != 0x1654c01) return false;
        uint32_t eventID = ((uint32_t*)msg)[2];
        if (eventID == GameState()->GetEventID("CRG_TargetedCreature"))
        {
            MarkEventAsOccurred(0x135f531f);
            if (ConfigManager()->GetValue(0x4ea96cb))
            {
                PauseGate(0x4bf38a7);
                cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
                if (sphere->mTerrainKeys[0])
                {
                    AddHint(kHintTargeted, 0);
                    AddHint(kHintTargeted2, &g_HintHandler);
                }
                else
                    AddHint(kHintTargeted, &g_HintHandler);
            }
        }
        else if (eventID == GameState()->GetEventID("CRG_LaidEgg"))
        {
            mpInputStrategy->mbActive = false;
            mpDisplayStrategy->SetVisible(0);
            CursorManager()->ShowCursor(0);
            CursorManager()->SetLocalCursor(0x1002);
        }
        else if (eventID == GameState()->GetEventID("CLG2CRG"))
        {
            cCameraController* camera =
                GetCameraController(App()->GetWindowManager()->GetMainWindow());
            if (camera)
                camera->SetMinDistance(g_CreatureCameraMinDistance);
            if (ConfigManager()->GetValue(0x4ea96cb))
            {
                PauseGate(0x4bf38a7);
                AddHint(kHintCLG2CRG_a, 0);
                AddHint(kHintCLG2CRG_b, &g_HintHandler2);
                AddHint(kHintCLG2CRG_c, &g_HintHandler);
                UIHints()->Activate(0xd624600a);
                UIHints()->Activate(0x681f7176);
            }
        }
        else if (eventID == GameState()->GetEventID("CRG_BrainUpgrade1"))
        {
            mpDisplayStrategy->SetVisible(1);
            if (ConfigManager()->GetValue(0x4ea96cb))
            {
                PauseGate(0x4bf38a7);
                AddHint(kHintBrainUpgrade1, &g_HintHandler);
            }
        }
        else if (eventID == GameState()->GetEventID("CRG_BrainUpgrade4"))
        {
            mpDisplayStrategy->SetPartVisible(0x6455b55, 1);
            mpDisplayStrategy->SetPartVisible(0x652a628, 1);
            if (ConfigManager()->GetValue(0x4ea96cb))
            {
                PauseGate(0x4bf38a7);
                AddHint(kHintBrainUpgrade4a, 0);
                AddHint(kHintBrainUpgrade4b, &g_HintHandler);
            }
        }
        else if (eventID == GameState()->GetEventID("CRG_ClaimNest"))
        {
            cEditorLauncher* launcher = EditorLauncher();
            uint32_t editors[2];
            editors[0] = 0x3a5e2b34;
            editors[1] = 0x51bc3d0;
            for (unsigned int i = 0; i < 2; i++)
            {
                uint32_t id = editors[i];
                cEditorEntry* entry = EditorLauncher()->Find(id);
                if (entry && entry->GetState() != 5)
                {
                    launcher->Select(id);
                    break;
                }
            }
        }
        else if (eventID == GameState()->GetEventID("CRG_Fade_From_Black_Egg"))
        {
            GameState()->FadeFromBlack();
        }
        else if (eventID == GameState()->GetEventID("CRG_SpeciesMigrate"))
        {
            GameState()->FadeFromBlack();
            PauseGate(0x4bf38a7);
            AddHint(kHintSpeciesMigrate, &g_HintHandler);
        }
        else if (eventID == GameState()->GetEventID("CRG_FirstPartUnlock"))
        {
            PauseGate(0x4bf38a7);
            AddHint(kHintFirstPartUnlock, &g_HintHandler);
        }

        cCreatureModeActionHandler** it = mActionHandlersBegin;
        cCreatureModeActionHandler** end = mActionHandlersEnd;
        ActionData data;
        data.a = 0;
        data.b = 0;
        data.id = eventID;
        for (; it != end; ++it)
            (*it)->HandleAction(0x55a7128, &data);
        return false;
    }

    case 0x4d9686f:
        NotifyWantToGoToEditor(1);
        GameState()->ResetEvents();
        return false;

    case 0x4f60b92:
        spInstance->SwitchToMode(0);
        NounManager()->GetAvatar()->Hatch();
        SetupHatchAtNest();
        return false;

    case 0x51b93cd:
        CreatureSimulator()->HandleMeteorImpact(msg);
        return false;

    case 0x6566531:
    {
        cHerd* herd = NounManager()->GetAvatar()->GetHerd();
        cPosseMember** it = herd->mpBegin;
        cPosseMember** end = herd->mpEnd;
        for (; it != end; ++it)
        {
            cPosseMember* member = *it;
            if (member->mpTarget && member->mpTarget->mCombatant.IsAlive() && member->mState == 5)
                member->mbAttack = 1;
        }
        return false;
    }

    case 0x6555abc:
    {
        cNest* nest = NounManager()->GetPlayerHerd()->mpNest;
        nest->SetSwatch(CreatureSimulator()->GetSwatchRollover());
        EditorLauncher();
        return false;
    }

    case 0x679c40d:
        if (GetCurrentGameMode() != 0x1654c01) return false;
    {
        cConfigManager* config = ConfigManager();
        cCreatureModeInputStrategy* input = mpInputStrategy;
        input->Init(config->GetValue(0x679b85e));
    }
        return false;

    case 0xd33b6aa2:
        if (GetCurrentGameMode() != 0x1654c01) return false;
        mpInputStrategy->mbActive = false;
        mpDisplayStrategy->SetVisible(0);
        CursorManager()->ShowCursor(0);
        CursorManager()->SetLocalCursor(0x1002);
        return false;

    case 0x533b6aa4:
        if (GetCurrentGameMode() != 0x1654c01) return false;
        mpInputStrategy->mbActive = true;
        mpDisplayStrategy->SetVisible(1);
        CursorManager()->ShowCursor(1);
        return false;
    }
    return false;
}

}   // namespace SP
