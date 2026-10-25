// slice s00fe2ab0 -- SP::cAppModeSpace::PostGameModeTransition
//   (mode-transition interface subobject entry: this = cAppModeSpace + 8).
//
// Post-processing of a game-mode change: begin/end of the post transition, the
// space-mode pre-entry hook (test-system guard, effects preload, 20 message ids
// via EA::Messaging::AutoHandler, state-machine reload), the per-old-mode
// teardown (tribe / unknown / editor -> planet / colony) and the common tail
// (local-game refresh, app property, pick priority, world-layout flag).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include "types.h"

// ---- game mode ids -----------------------------------------------------
enum eGameModeTag {
    kModeCiv     = 0x1654c04,   // civilization
    kModeSpace   = 0x1654c05,   // space
    kModeTribe   = 0x1654c06,   // tribe
    kModeColony  = 0x1654c08,   // colony
    kModeEditor  = 0xdbdba1,    // editor
    kModePlanetView = 0x1654c10,  // planet/space view (no pre-entry hook)
    kModeUnknown = 0x2ccd1d2,   // unknown / cancelled transition (-1 shares this arm)
};

// ---- record type ids ---------------------------------------------------
enum eRecordType {
    kTypeCreature = 0x66787bc,  // creature/species record
    kTypePlanetA  = 0x7ce1750,  // planet record
    kTypePlanetB  = 0x7ce3cb0,  // planet record (alternate class)
};

// ---- EA::ResourceMan::Key ---------------------------------------------
struct Key {
    uint32_t mTypeID;           // +0x00
    uint32_t mGroupID;          // +0x04
    uint32_t mInstanceID;       // +0x08
    Key() : mTypeID(0), mGroupID(0), mInstanceID(0) {}
};

// ---- messaging ---------------------------------------------------------
struct ISubsystem;                                   // cAppModeSpace +4 (cGonzagoSubsystem)

struct IMessageServer {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual void PostMSG(uint32_t id, int32_t a, int32_t b);                   // +0x14
    virtual void s18(); virtual void s1c();
    virtual void s20();
    virtual void AddListener(ISubsystem* handler, uint32_t id);                // +0x24
};

// EA::Messaging::AutoHandler (0x14 bytes)
class AutoHandler {
 public:
    __forceinline void AddHandler(IMessageServer* server, ISubsystem* handler, const uint32_t* ids, uint32_t count)
    {
        mpServer = server;
        mpHandler = handler;
        mpIdArray = ids;
        mnIdArrayCount = count;
        mnPriority = 0;
        if (mpServer && mpHandler) {
            for (uint32_t i = 0; i < count; ++i)
                mpServer->AddListener(mpHandler, mpIdArray[i]);
        }
    }

    IMessageServer* mpServer;          // +0x00
    ISubsystem* mpHandler;             // +0x04
    const uint32_t* mpIdArray;         // +0x08
    uint32_t mnIdArrayCount;           // +0x0c
    int32_t mnPriority;                // +0x10
};

// ---- cGonzagoSubsystem vtable prefix (shared by the notified subsystem) --
struct ISubsystem {
    virtual int AddRef();                                                      // +0x00
    virtual bool HandleMessage(uint32_t messageID, void* pMsg);                // +0x04
    virtual int Release();                                                     // +0x08
    virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void PostGameModeTransition(int32_t oldMode, int32_t newMode);     // +0x18
    void Fn_00ac8cd0(void* p, int32_t a);                                      // 0xac8cd0
};

// ---- managers ----------------------------------------------------------
struct IEffectsManager {
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18(); virtual void e1c();
    virtual void e20(); virtual void e24(); virtual void e28(); virtual void e2c();
    virtual void e30(); virtual void e34(); virtual void e38(); virtual void e3c();
    virtual void e40(); virtual void e44(); virtual void e48(); virtual void e4c();
    virtual void e50(); virtual void e54(); virtual void e58(); virtual void e5c();
    virtual void e60(); virtual void e64(); virtual void e68(); virtual void e6c();
    virtual void e70(); virtual void e74(); virtual void e78(); virtual void e7c();
    virtual void e80(); virtual void e84(); virtual void e88(); virtual void e8c();
    virtual void e90(); virtual void e94();
    virtual void Preload(uint32_t id, bool bWarm);                             // +0x98
};

struct IConfigManager {
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void c20(); virtual void c24(); virtual void c28(); virtual void c2c();
    virtual void* GetPropertyList(uint32_t id);                                // +0x30
};

struct IGameInputManager {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
    virtual void g30(); virtual void g34();
    virtual void SetMode(int32_t mode);                                        // +0x38
};

struct ICurMgr {
    bool FindLocal(uint32_t id);                                               // 0x801bb0
};

struct IEventLog {
    void ClearEvents();                                                        // 0xdd6d70
};

// object behind the 0xb3d410 getter (space-mode bookkeeping)
struct ISpaceModeManager {
    bool IsReady();                                                            // 0xe36fa0
    void SetPendingMode(int32_t a, int32_t b);                                 // 0xe3e350
};

// object behind the 0xb3d230 getter
struct IMgr230 {
    void Fn_00b5cde0(uint32_t id);                                             // 0xb5cde0
};

// object behind the 0xb3d320 getter
struct IMgr320 {
    void Fn_00b1dfc0();                                                        // 0xb1dfc0
};

// ---- space game state (cAppModeSpace +0x15c) ---------------------------
struct cSpaceEffect {
    void Fn_010727e0(int32_t a, int32_t b);                                    // 0x10727e0
};

struct cSpaceUI {
    char pad00[0x204];
    int32_t mnState;                           // +0x204
};

// ref-counted selection record (type id + resource key)
struct cSelection {
    virtual void v00();                        // +0x00
    virtual void v04();                        // +0x04
    virtual int Release();                     // +0x08
    char pad04[0x0c - 0x04];
    uint32_t mnType;                           // +0x0c
    char pad10[0x18 - 0x10];
    Key mKey;                                  // +0x18
    char pad24[0x44 - 0x24];
    bool mbHandled;                            // +0x44
};

struct cSpaceGameState {
    char pad00[0x14];
    cSpaceEffect* mpEffect;                    // +0x14
    char pad18[0x20 - 0x18];
    cSpaceUI* mpUI;                            // +0x20
    cSelection* mpSelection;                   // +0x24
    void Fn_010030c0();                        // 0x10030c0
};

struct PtrVector {
    void** mpBegin;                            // +0x00
    void** mpEnd;                              // +0x04
};

struct ICivilization {
    void Fn_00bebdd0(const Key& key);                                          // 0xbebdd0
};

struct cGameNounManager {
    ICivilization* GetPlayerCivilization();                                    // 0xb25fb0
    PtrVector* Fn_00ace2c0();                                                  // 0xace2c0
};

struct IEmpire {
    void Fn_00c30fa0();                                                        // 0xc30fa0
};

struct ISpeciesManager {
    void SetAvatarSpecies(const Key& key);                                     // 0x4df310
};

// ---- cTestSystem (0x15fd928) -------------------------------------------
namespace SP {
struct cTestSystem {
    struct ListNode { ListNode* mpNext; ListNode* mpPrev; };
    char pad00[0x70];
    ListNode mTests;                           // +0x70
    bool IsTestingInProgress() const { return mTests.mpNext != &mTests; }
};

struct cAppProperties {
    char pad00[0x00];
    void SetBoolProperty(uint32_t id, bool bValue);                            // 0x6a17e0
};

extern cTestSystem* sTestSystem;               // 0x15fd928
extern cAppProperties* sAppProperties;         // 0x15fd918
extern const uint32_t kHandlerIDs[];           // 0x1494170 20 message ids

// ---- callees -----------------------------------------------------------
ISubsystem* __cdecl Subsystem1();              // 0xb3d460
ISubsystem* __cdecl Subsystem2();              // 0xb3d480
ISubsystem* __cdecl StarManager();             // 0xb3d2a0
ISpaceModeManager* __cdecl SpaceModeManager(); // 0xb3d410
IMgr230* __cdecl Fn_00b3d230();                // 0xb3d230
IMgr320* __cdecl Fn_00b3d320();                // 0xb3d320
cGameNounManager* __cdecl NounManager();       // 0xb3d300
IEventLog* __cdecl EventLog();                 // 0xb3d3e0
IGameInputManager* __cdecl GameInputManager(); // 0xb3d250
IEffectsManager* __cdecl EffectsManager();     // 0x67ddd0
IMessageServer* __cdecl MessageServer();       // 0x67dcc0
IConfigManager* __cdecl ConfigManager();       // 0x67dd30
ICurMgr* __cdecl CurMgr();                     // 0x67cab0
bool __cdecl IsWorldLayoutFlagSet(int32_t flag);          // 0x685520
void __cdecl Fn_00bf55d0();                    // 0xbf55d0
void __cdecl Fn_00ba5650(const Key* key, int32_t a);       // 0xba5650
void __cdecl Fn_00ba5bc0(void* p);             // 0xba5bc0
IEmpire* __cdecl GetPlayerEmpire(int32_t index);           // 0x1021300
IEmpire* __cdecl GetPlayerEmpire(const Key& key);          // 0x1021300
ISpeciesManager* __cdecl SpeciesManager();     // 0x401090
void __cdecl CommEvent(uint32_t id, void* p, const Key& a, const Key& b,
                       void* ctx, int32_t c, const Key& d, const Key& f); // 0xe39ab0
}

// ---- the mode-transition interface (cAppModeSpace +8) ------------------
class cModeTransition {
 public:
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual int32_t GetPostModeTransitionState();                              // +0x20
    virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void t30(); virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40();
    virtual void BeginPostGameModeTransition(int32_t newMode);                 // +0x44
    virtual void t48();
    virtual void EndPostGameModeTransition();                                  // +0x4c

    void PostGameModeTransition(int32_t oldMode, int32_t newMode);             // 0xfe2ab0
};

struct IModeStrategy {
    virtual void m00();                        // +0x00
};

// cAppModeSpace: cIModeStrategy(+0), cGonzagoSubsystem(+4), transition interface(+8)
class cAppModeSpace : public IModeStrategy, public ISubsystem, public cModeTransition {
 public:
    void TransitionFromEditorToPlanet();       // 0xfdc800
    void Fn_00fdb9a0();                        // 0xfdb9a0
    void SetDefaultPickPriority();             // 0xfddba0
    void LoadStateMachine(void* pProperties);   // 0xfe1a20

    char pad0c[0x8c - 0x0c];
    AutoHandler mAutoHandler;                  // +0x8c
    char pad_a0[0x131 - 0xa0];
    bool mbFlag131;                            // +0x131
    char pad132[0x15c - 0x132];
    cSpaceGameState* mpSpaceState;             // +0x15c
    char pad160[0x18e - 0x160];
    bool mbFlag18e;                            // +0x18e
    bool mbFlag18f;                            // +0x18f
    bool mbFlag190;                            // +0x190
    bool mbFlag191;                            // +0x191
    bool mbFlag192;                            // +0x192
};

// @ 0x00fe2ab0
void cModeTransition::PostGameModeTransition(int32_t oldMode, int32_t newMode)
{
    if (GetPostModeTransitionState() == newMode)
        return;

    BeginPostGameModeTransition(newMode);

    cAppModeSpace* space = static_cast<cAppModeSpace*>(this);

    if (!(SP::sTestSystem && SP::sTestSystem->IsTestingInProgress())) {
        if (newMode == kModeSpace && oldMode != kModeEditor && oldMode != kModePlanetView) {
            if (space->mbFlag18e) {
                if (SP::SpaceModeManager()->IsReady()) {
                    space->mbFlag18f = true;
                    space->mbFlag190 = false;
                    space->mbFlag191 = false;
                    space->mbFlag192 = false;
                    goto transitioned;
                }
            }
            SP::SpaceModeManager()->SetPendingMode(0, kModeSpace);
        }
    }
transitioned:
    SP::Subsystem1()->PostGameModeTransition(oldMode, newMode);
    SP::Subsystem2()->PostGameModeTransition(oldMode, newMode);

    if (newMode == kModeSpace) {
        SP::EffectsManager()->Preload(0xc, true);
        space->mAutoHandler.AddHandler(SP::MessageServer(), static_cast<ISubsystem*>(space),
                                       SP::kHandlerIDs, 20);
        space->LoadStateMachine(SP::ConfigManager()->GetPropertyList(0x679b880));

        switch (oldMode) {
        case kModeTribe:
            SP::Fn_00b3d230()->Fn_00b5cde0(0x1103193);
            space->mpSpaceState->Fn_010030c0();
            break;

        case -1:
        case kModeUnknown:
            SP::Fn_00bf55d0();
            break;

        case kModeEditor: {
            space->TransitionFromEditorToPlanet();
            cSelection* selection = space->mpSpaceState->mpSelection;
            if (selection) {
                switch (selection->mnType) {
                case kTypeCreature:
                    if (!selection->mbHandled) {
                        SP::SpeciesManager()->SetAvatarSpecies(selection->mKey);
                        ICivilization* civ = SP::NounManager()->GetPlayerCivilization();
                        if (civ)
                            civ->Fn_00bebdd0(selection->mKey);
                        space->Fn_00fdb9a0();
                        PtrVector* list = SP::NounManager()->Fn_00ace2c0();
                        for (void** it = list->mpBegin; it != list->mpEnd; ++it)
                            SP::Subsystem2()->Fn_00ac8cd0(*it, 0);
                        Key key1, key2, key3, key4;
                        SP::CommEvent(0x9fd41912, 0, key4, key3, 0, 0, key2, key1);
                        SP::Fn_00ba5bc0(SP::GetPlayerEmpire(7));
                    }
                    break;

                case kTypePlanetA:
                case kTypePlanetB:
                    if (!selection->mbHandled) {
                        SP::GetPlayerEmpire(selection->mKey)->Fn_00c30fa0();
                        SP::Fn_00ba5650(&selection->mKey, 8);
                    }
                    space->mpSpaceState->mpEffect->Fn_010727e0(1, selection->mnType);
                    break;
                }
                space->mpSpaceState->mpSelection = 0;
                selection->Release();
            }
            SP::Fn_00b3d320()->Fn_00b1dfc0();
            if (space->mpSpaceState->mpUI->mnState == 1) {
                SP::MessageServer()->PostMSG(0x71d4dfc9, 0, 0);
                SP::GameInputManager()->SetMode(3);
            }
            break;
        }

        case kModeColony:
            SP::StarManager()->PostGameModeTransition(kModeColony, kModeSpace);
            break;
        }

        SP::CurMgr()->FindLocal(0x1002);
        SP::sAppProperties->SetBoolProperty(0x28, true);
        space->Fn_00fdb9a0();
        if (oldMode == kModeCiv || oldMode == kModeUnknown)
            SP::EventLog()->ClearEvents();
        space->SetDefaultPickPriority();
        space->mbFlag131 = SP::IsWorldLayoutFlagSet(2);
    }

    EndPostGameModeTransition();
}
