// SP::cCreatureModeStrategy::ContinueLoading  @ 0x00d43e30
//
// ~5880-byte __thiscall loading state machine of the creature game (/O2 /arch:SSE, no EH frame).
// mLoadingState.mState (+0xa0) selects the step; mLoadingState.mPreviousMode (+0xa4) is the
// game mode the creature game was entered from:
//   0x00dbdba1  returning from the creature editor
//   0x01654c08  cell -> creature transition
//   0x01654c06  (editor-like return path)
//   0x02ccd1d2 / -1 / 0x01654c00  fresh start / load
// Every step ends by handing the handler to the game-mode manager (0x00b5e9a0).
//
//   void __thiscall ContinueLoading(cCreatureModeStrategy* this, IHandlerRC* handler)

#include "types.h"

struct Vector2 { float x, y; };
struct Vector3
{
    float x, y, z;
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };

struct IHandlerRC;
struct IMessageServer;
class cPropertyList;

// ---------------------------------------------------------------------------------------
// small polymorphic helpers (vtable slot = byte offset / 4)
class cRefCounted   // IRefCount-style: AddRef +4, Release +8
{
public:
    virtual void s00();
    virtual int AddRef();
    virtual int Release();
};

class cRefCountedV1   // AddRef +0, Release +4
{
public:
    virtual int AddRef();
    virtual int Release();
};

// --- creature-mode objects --------------------------------------------------------------
class cInputStrategyRC { public: virtual void s00(); };

class cCreatureModeInputStrategy
{
public:
    virtual void s00();
    virtual void Initialize();       // +0x04
    virtual void Reset();            // +0x08
    uint32_t pad04[(0x3c - 4) / 4];
    cInputStrategyRC mRefCount;      // +0x3c (handler interface)
    uint32_t pad40[(0x54 - 0x40) / 4];
    bool mbActive;                   // +0x54
    void Init(uint32_t config);      // 0x00d36940
    cCreatureModeInputStrategy();    // 0x00d37970
};

struct InputStrategyPtr
{
    cCreatureModeInputStrategy* mpObject;
    InputStrategyPtr& operator=(cCreatureModeInputStrategy* p);   // 0x00d38b10
};

class cCreatureDisplayStrategy
{
public:
    void UpdateAfterEditor(int a);   // 0x00d2c000
    void SetVisible(int a);          // 0x00d2c200
};

class cCreatureModeScenario
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void HandleEvent(uint32_t id, void* data);   // +0x18
};

class cSPCreatureMissionManager
{
public:
    virtual void s00();
    virtual int AddRef();            // +0x04
    virtual int Release();           // +0x08
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07();
    virtual void Start();            // +0x20
};
extern cSPCreatureMissionManager* g_CreatureMissionManager;   // 0x0169e230

class cTexturePreload { public: bool IsDone(); };   // 0x007b19c0

struct cAutoHandler   // EA::Messaging Connector
{
    uint32_t pad[5];
    void Init(IMessageServer* server, void* handler, const uint32_t* ids, int count);   // 0x004db620
};
extern const uint32_t kCreatureModeMessages[12];   // 0x0147aa64

class cEditorResultData
{
public:
    virtual void s00();
    virtual int AddRef();            // +0x04
    virtual int Release();           // +0x08
    uint32_t pad04[2];
    uint32_t mEditorID;              // +0x0c
    uint32_t pad10[2];
    uint32_t mProfile[7];            // +0x18
    int      mEvoPoints;             // +0x34
};

// --- game data ---------------------------------------------------------------------------
class cSpeciesProfile { public: char pad[0x504]; char mResource[4]; };

class cHerd
{
public:
    uint32_t pad00[0x84 / 4];
    bool     mbActive;               // +0x84
    uint32_t pad88[(0xa4 - 0x88) / 4];
    cSpeciesProfile* mpProfile;      // +0xa4
    uint32_t pada8[(0x160 - 0xa8) / 4];
    char*    mpNest;                 // +0x160
    Vector3* GetPosition();          // 0x00c6acc0
    void     Refresh();              // 0x00c6ad60
};

struct cPartRef   // RefCountTemplate-style element of the species part list
{
    struct VT { void (__thiscall* Destroy)(cPartRef*, int); };
    VT*      vtbl;
    int      mnRefCount;             // +0x04
    uint32_t mID;                    // +0x08
    char     pad0c[0x115 - 0x0c];
    bool     mbUnlocked;             // +0x115
    char     pad116[0x130 - 0x116];
    char*    mpInfo;                 // +0x130 (position at +8)
};

struct cPartRefVector { cPartRef** mpBegin; cPartRef** mpEnd; };

class cSpecies
{
public:
    char  pad0[0x58c];
    float mBonus;                    // +0x58c
    char  pad590[0x6d4 - 0x590];
    cPartRefVector mParts;           // +0x6d4
};

class cCreatureStats
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual int   GetTeam();                 // +0x2c
    virtual void s12();
    virtual float GetMaxHealth();            // +0x34
    virtual void s14(); virtual void s15();
    virtual void  SetHealth(float h);        // +0x40
};

class cCreatureEffects
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual void SetEnabled(int on);         // +0x2c
};

#define VPAD4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();
#define VPAD8(n) VPAD4(n##a) VPAD4(n##b)

class cSPCreatureBase
{
public:
    VPAD8(v00) VPAD8(v08) VPAD8(v10) VPAD8(v18)                 // slots 0..31
    virtual float GetMaxHealthFor(int a);                         // +0x80 (32)
    VPAD8(v21) virtual void v29a(); virtual void v29b();          // 33..42
    virtual void UpdateModel(int a);                              // +0xac (43)
    virtual void v2c0(); virtual void v2c1(); virtual void v2c2(); // 44..46
    virtual void Deactivate();                                    // +0xbc (47)
    virtual void v300(); virtual void v301(); virtual void v302(); // 48..50
    virtual void SetSelectable(int a);                            // +0xcc (51)
    VPAD4(v34) virtual void v38a(); virtual void v38b();          // 52..57
    virtual void SetEditorMode(int a);                            // +0xe8 (58)

    // fields (byte offsets)
    char pad_[0xc0 - 4];
    cCreatureStats mStats;                                        // +0xc0
    char padc4[0x135 - 0xc4];
    bool mbIsInPosse;                                             // +0x135
    char pad136[0x5a8 - 0x136];
    cCreatureEffects mEffects;                                    // +0x5a8
    char pad5ac[0x5e0 - 0x5ac];
    float mAge;                                                   // +0x5e0
    char pad5e4[0xb20 - 0x5e4];
    cSpecies* mpSpecies;                                          // +0xb20
    char padb24[0xb58 - 0xb24];
    uint32_t mFlags;                                              // +0xb58
    char padb5c[0xb67 - 0xb5c];
    bool mbIsDead;                                                // +0xb67

    void CheckCreatureModel(int a, int b);   // 0x00c21bf0
    void UpdateAnimations();                 // 0x00c0bbe0
    void UpdateCollision();                  // 0x00c21090
    void ResetState(int a);                  // 0x00c02c20
    void UpdatePosition();                   // 0x00c02e80
    void UpdateBehavior();                   // 0x00c042e0
    void UpdateEffects();                    // 0x00c0b950
    ResourceKey* GetSpeciesKey();            // 0x00c0bc00
    cHerd* GetHerd();                        // 0x00c04590
};
void FUN_00c0d3a0(cSPCreatureBase* c);

struct cCreatureVector { cSPCreatureBase** mpBegin; cSPCreatureBase** mpEnd; };
struct cHerdVector { cHerd** mpBegin; cHerd** mpEnd; };

struct cGameData { char pad[0x28]; uint32_t mType; };   // +0x28
struct cGameDataVector
{
    uint32_t pad0;
    cGameData** mpBegin;             // +0x04
    cGameData** mpEnd;               // +0x08
    uint32_t pad0c;
    char     mAllocator[4];          // +0x10
};
struct cCreatureDataVector { uint32_t pad0; cSPCreatureBase** mpBegin; cSPCreatureBase** mpEnd; };

typedef void (*GameDataFn)();
void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00ace0f0(); void FUN_00b1e500(); void FUN_00b2d1d0();

class cTerrainSphere
{
public:
    char  pad0[0x10e8];
    void* mpPlanetRecord;            // +0x10e8
    int   mPendingEvoPoints;         // +0x10ec
    uint32_t pad10f0;
    float mTimeScale;                // +0x10f4
    uint32_t pad10f8;
    uint32_t mTerrainKeys[4];        // +0x10fc
};

class cGameNounManager
{
public:
    cSPCreatureBase* GetAvatar();                                   // 0x00b1fdb0
    void AddHerd(cHerd* herd);                                      // 0x00b1fdc0
    cTerrainSphere* GetCurrentTerrainSphere();                      // 0x00f67d90
    cHerd* GetPlayerHerd();                                         // 0x00989360
    cCreatureVector* GetCreatures();                                // 0x00ace2f0
    cHerdVector* GetHerds();                                        // 0x00acda00
    void* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, uint32_t type); // 0x00b21340
    void DestroyGameData(cGameData* d);                             // 0x00b225d0
};

class cPlanetRecordHolder { public: void* GetRecord(int a, int b); };   // 0x00c713e0
class cPlanetModel
{
public:
    void SetPlanet(void* record);                                   // 0x00b8d8a0
    void sInitMinimap(IHandlerRC* handler, int a, int b);           // 0x00b8c330
    bool DirectionToSurfacePosition(Vector3* out, const Vector3* dir); // 0x00b815a0
};
extern const Vector3 kDefaultSpawnDirection;   // 0x01583008

class cUniverse { public: cPropertyList* GetPropertyList(); };    // 0x00c8b370

class cPropertyManager
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual bool GetPropertyList(cPropertyList* list, uint32_t key, cPropertyList** out);   // +0x2c
};

struct PropertyListPtr
{
    cRefCountedV1* mpObject;
    cPropertyList** AsPPTypeParam();   // 0x00a16f40
};

class cAchievementsController
{
public:
    void AutoTest(uint32_t id, int a);                  // 0x00676e90
    void Trigger(uint32_t id, int a, int b);            // 0x00676ed0
};

class cGameModeManager
{
public:
    VPAD8(v0) virtual void v8a(); virtual void v8b(); virtual void v8c();   // 0..10
    virtual void Activate(IHandlerRC* h);       // +0x2c
    virtual void Deactivate(IHandlerRC* h);     // +0x30
    virtual void v13();
    virtual void SetInputHandler(void* handler, int a);   // +0x38
    void Update(IHandlerRC* h);                 // 0x00b5e9a0
    void PostEvent(uint32_t id);                // 0x00b5cde0
};

class cInputManager
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void LoadTriggerConfig(const char* name, int a, int b);   // +0x10
};

struct wstring16 { uint32_t pad[4]; };
bool operator==(const wstring16& a, const wchar_t* b);   // 0x006ab760
class cLocaleManager
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual const wstring16* GetLanguage();                 // +0x14
};

class cConfigManager
{
public:
    VPAD8(v0) VPAD4(v8)
    virtual uint32_t GetValue(uint32_t key);                // +0x30
};

class cCursorManager
{
public:
    void SetLocalCursor(uint32_t id);   // 0x00801bb0
    void ShowCursor(int a);             // 0x00801930
};

class cResettable { public: void Reset(); void Shutdown(); };   // 0x00b3d7a0 / 0x00b3d7c0

class cSimTicker
{
public:
    VPAD8(v0) VPAD8(v8) VPAD4(v10)
    virtual void AddSimulator(void* sim);                   // +0x50
};

class cSimulator
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual void Initialize();                              // +0x1c
};
class cPosseSimulator : public cSimulator { public: void SetMode(int a); };   // 0x00d52e40
class cAnimalSimulator { public: void Initialize(); };                       // 0x00ae7350

class cModelWorldLoader
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void SetWorld(void* w);                         // +0x10
    virtual void s5();
    virtual void AddModelWorld(void* w, int a);             // +0x18
    virtual void SetLayer(void* layer, uint32_t flags);     // +0x1c
    virtual void s8(); virtual void s9();
    virtual void SetEnabled(int a);                         // +0x28
    virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void SetGroup(uint32_t id);                     // +0x48
};

class cModelManager
{
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual void* GetModelWorld(uint32_t id);               // +0x1c
};

class cRenderer
{
public:
    VPAD8(v0) VPAD4(v8)
    virtual void SetRenderMode(uint32_t id);                // +0x30
};
extern cRenderer* g_Renderer;   // 0x0167ea54

class cTerrainCursor
{
public:
    VPAD8(v00) VPAD8(v08) VPAD8(v10) VPAD8(v18) VPAD8(v20)    // 0..39
    VPAD4(v28) virtual void v2ca(); virtual void v2cb();       // 40..45
    virtual void SetVisible(int a);                            // +0xb8 (46)
};

class cSpeciesManager
{
public:
    cSpeciesProfile* GetAvatarProfile();                       // 0x004df420
    void UpdateProfile(cSpecies* species, void* profile);      // 0x004dfb50
};

class cStatsHolder { public: void SetAvatar(cSPCreatureBase* avatar); };   // 0x00ba4f30

class cTimeOfDay
{
public:
    uint32_t pad[9];
    float mDayLength;                                // +0x24
    static cTimeOfDay* Instance();                   // 0x00bc30b0
    void SetTime(float t, int team);                 // 0x00bc2f00
};
extern float g_CreatureTimeOfDay;    // 0x01582e74

class cAppWindow { public: VPAD8(v0) VPAD4(v8) virtual void v12(); virtual void v13();
                   virtual void* GetMainWindow(); };   // +0x38
class cApp { public: VPAD8(v0) VPAD8(v8) VPAD4(v10) virtual cAppWindow* GetWindowManager(); };   // +0x50
class cLoadingScreen { public: void SetProgress(float p); };   // 0x00d25ca0
cLoadingScreen* FUN_00b60a50(void* window);
extern float g_LoadingProgress;     // 0x01582f30

struct cEditorLaunchData
{
    void**   vtbl;
    uint32_t pad04[2];
    uint32_t mEditorID;              // +0x0c
    ResourceKey mSpeciesKey;         // +0x10
    uint32_t pad1c[6];
    bool     mb34; bool mb35; bool mb36; bool mb37;
    bool     mb38; bool mb39; bool mb3a; bool mb3b;
    bool     mb3c; bool mb3d;
    char     pad3e[0x6c - 0x3e];
    bool     mb6c;
    char     pad6d[3];
    struct UIntVector { uint32_t pad[4]; void push_back(const uint32_t& v); } mTerrainKeys;   // +0x70 (0x00454860)
    uint32_t pad80[4];
    uint32_t mMode;                  // +0x90
    struct RefPtr { void* p; RefPtr& operator=(void* v); } mpPlanetRecord;  // +0x94 (0x00b5f950)
    cEditorLaunchData();             // 0x005a9080
};
struct EditorLaunchDataPtr
{
    cEditorLaunchData* mpObject;
    EditorLaunchDataPtr(cEditorLaunchData* p);   // 0x0061df40
    ~EditorLaunchDataPtr() { ((cRefCounted*)mpObject)->Release(); }
};
namespace Editor { void Launch(cEditorLaunchData* data); }   // 0x005a9200

class cGameTimeManager { public: void Pause(uint32_t id); };   // 0x00b32250
class cHabitatMap { public: void SetCenter(Vector3* pos, Vector2 size); };   // 0x00acc700

class cAudioManager
{
public:
    VPAD8(v0) VPAD8(v8) VPAD4(v10) virtual void v14a(); virtual void v14b(); virtual void v14c();
    virtual void Lock(int a, int b);     // +0x5c (23)
    virtual void Unlock(int a, int b);   // +0x60 (24)
};

class cProgressManager
{
public:
    VPAD8(v0) virtual void v8(); virtual void v9();
    virtual int  GetPendingCount();          // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual bool IsLoading(void* resource);  // +0x3c
};

class cModelWorld { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                    virtual int GetPendingCount(); };   // +0x10

class cAppSystem
{
public:
    VPAD8(v0) VPAD8(v8)
    virtual void SetBusy(bool b);    // +0x40
    virtual bool IsBusy();           // +0x44
};
extern bool g_LoadingFlagA;   // 0x0167ece0
extern bool g_LoadingFlagB;   // 0x0167ecdb

class cTutorialManager
{
public:
    bool IsReady();                              // 0x00e36fa0
    void Start();                                // 0x00e36de0
    void Show(int a, uint32_t mode, int b);      // 0x00e3e350
    bool IsFinished();                           // 0x00e36dd0
    void Advance();                              // 0x00e3b1f0
    bool IsClosed();                             // 0x00e36e10
};

struct cTransitionMessage
{
    uint32_t data[8];
    cTransitionMessage* Init(void* nest, int a);   // 0x00ad7a30
    void Destroy();                                // 0x00ad7ad0
};
class cUIEventManager
{
public:
    void SetState(int a);                                        // 0x00adf390
    void Send(uint32_t id, cTransitionMessage* msg);             // 0x00ae09b0
    void StartTransition(const char* name, int a, int b, int c, int d, int e);   // 0x00ae0930
    bool IsTransitionDone();                                     // 0x00ac80f0
};

struct cGamePlanetData { char pad[0x1e5f0]; void** mpBegin; void** mpEnd; };   // +0x1e5f0
struct cCivList { char pad[0x70]; void* mpNext; };                             // +0x70 (list head)
extern cCivList* g_CivData;   // 0x015fd928

// ---------------------------------------------------------------------------------------
// global accessors
cGameModeManager* GameModeManager();          // 0x00b3d230
cSimTicker*       SimTicker();                // 0x00b3d330
cGameNounManager* NounManager();              // 0x00b3d300
cResettable*      CameraManager();            // 0x00b3d310
cPlanetModel*     PlanetModel();              // 0x00b3d350
cGameTimeManager* GameTimeManager();          // 0x00b3d380
cTutorialManager* TutorialManager();          // 0x00b3d410
cGamePlanetData*  GamePlanetData();           // 0x00b3d440
cHabitatMap*      HabitatMap();               // 0x00b3d480
cStatsHolder*     StatsHolder();              // 0x00b3d4c0
cUIEventManager*  UIEventManager();           // 0x00b3d4d0
cModelWorld*      GonzagoModelWorld();        // 0x00b3d520
cInputManager*    GameInputManager();         // 0x00b3d250
cTerrainCursor*   GetGameTerrainCursor();     // 0x00b30d70
cLocaleManager*   LocaleManager();            // 0x0067de40
cConfigManager*   ConfigManager();            // 0x0067dd30
cPropertyManager* PropertyManager();          // 0x0067de30
cCursorManager*   CursorManager();            // 0x0067cab0
cApp*             App();                      // 0x0067dd10
cAppSystem*       AppSystem();                // 0x0067dd00
cAudioManager*    AudioManager();             // 0x0067dd50
cModelManager*    ModelManager();             // 0x0067dd80
cModelWorldLoader* ModelWorldLoader();        // 0x0067ddc0
void*             DefaultLayer();             // 0x0067de00
cAchievementsController* AchievementsController();   // 0x00675250
cSpeciesManager*  SpeciesManager();           // 0x00401090
cProgressManager* ProgressManager();          // 0x00401010
cPosseSimulator*  PosseSimulator();           // 0x00d539d0
cSimulator*       TribeSimulator();           // 0x00d51660
cAnimalSimulator* AnimalSimulator();          // 0x00bd83e0
cUniverse*        CurrentUniverse();          // 0x01021230
cPlanetRecordHolder* GetActivePlanet();       // 0x01021260
IMessageServer*   GetMessageServer();         // 0x00883860

// free helpers
uint32_t FNV1_String8(const char* s, uint32_t seed, int lower);   // 0x00932e80
bool  GetPropertyAsUint32(cPropertyList* list, uint32_t key, uint32_t* out);   // 0x004af210
void  FUN_00d1c610(uint32_t id, int a);                                      // gameplay-marker cast
void  FUN_00b98f00(void* scratch, void** out);
cHerd* InterfaceCastHerd(void* p);                                           // 0x00b90940
void  SpawnHerd(Vector3* pos, void* profile, int a, cHerd* herd, int b, int c);   // 0x00c099e0
void  FUN_00d2e980(); void FUN_00d2e720(); void FUN_00d2e580();
void  AddEvoPoints(float points);                                            // 0x00d2e480
float GetEvoProgress(int a);                                                 // 0x00d2e800
void  FUN_00b99530(int a, int b, int c);
void  FUN_00d48a00();
void  FUN_00d391d0(int fromCell);
void  FUN_00d3c430();
void  FUN_00d3c3b0();
void  FUN_00d3a830();
bool  FUN_00d397c0(uint32_t id, cPartRefVector* parts);
void  SendCreatureEvent(uint32_t id, const ResourceKey* key, const Vector3& a, const Vector3& b, const Vector3& c);   // 0x00e39710
void  SetupHatchAtNest();                                                    // 0x00d40ff0
void  FUN_00ba1c60(uint32_t mode);
void  GetPropertyVector2(Vector2* out, cPropertyList* list, uint32_t key, Vector2 def);   // 0x00ac8f00
extern float g_SimSpeed[4];          // 0x01582e38..0x01582e44
extern float g_HatchAgeLimit;        // 0x0147aaac
extern float kHabitatSize[2];        // 0x013ec4d0 / 0x014763b8

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);
void* operator new[](unsigned int size, const char* name, int a, int b, int c, int d);

// Local list of part references (RefCountTemplate elements, released inline).
struct cPartRefList
{
    cPartRef** mpBegin;
    cPartRef** mpEnd;
    cPartRef** mpCapacity;
    uint32_t   mAllocator[2];
    uint32_t   mOverflow;
    cPartRef*  mBuffer[20];

    __forceinline cPartRefList() : mOverflow(0)
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 20;
    }
    __forceinline ~cPartRefList()
    {
        for (cPartRef** it = mpBegin; it < mpEnd; ++it)
        {
            cPartRef* p = *it;
            if (p)
            {
                if (--p->mnRefCount == 0)
                {
                    p->mnRefCount = 1;
                    p->vtbl->Destroy(p, 1);
                }
            }
        }
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    cPartRefList& operator=(const cPartRefVector& src);   // 0x00d3c970
    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    __forceinline cPartRef* operator[](uint32_t i) const { return mpBegin[i]; }
};

// Temporary array of game data references (released through IRefCount::Release).
struct cGameDataArray
{
    cGameData** mpBegin;
    uint32_t pad[4];
    void Allocate(uint32_t count, void* allocator);   // 0x00b93c60
};
void CopyGameData(cGameData*** outEnd, cGameData** first, cGameData** last, cGameData** dest, cGameNounManager* nm);   // 0x00829110

// ---------------------------------------------------------------------------------------
namespace SP
{
struct cAvatarEvent { void* mpAvatar; void* mpOther; int mValue; };

class cCreatureModeStrategy
{
public:
    void*    vtbl;                                 // +0x00
    char     mHandler[0x49 - 4];                   // +0x04 IHandlerRC subobject ...
    bool     mbReturningFromEditor;                // +0x49
    char     pad4a[2];
    char     mEvolutionTracker[0x14];              // +0x4c
    cEditorResultData*          mEditorResult;     // +0x60
    cCreatureModeInputStrategy* mpInputStrategy;   // +0x64
    cCreatureDisplayStrategy*   mpDisplayStrategy; // +0x68
    bool     mbRegisteredForMessages;              // +0x6c
    char     pad6d[3];
    cAutoHandler mMessageRegistration;             // +0x70
    char     pad84[0xa0 - 0x84];
    uint32_t mState;                               // +0xa0  (cLoadingState)
    uint32_t mPreviousMode;                        // +0xa4
    uint32_t mCurrentMode;                         // +0xa8
    uint32_t mFrames;                              // +0xac
    int      mGameMode;                            // +0xb0
    cPropertyList* mpCreaturePropList;             // +0xb4
    cPropertyList* mpCreatureVerbPropList;         // +0xb8
    cCreatureModeScenario** mScenariosBegin;       // +0xbc
    cCreatureModeScenario** mScenariosEnd;         // +0xc0
    uint32_t padc4[3];
    cSPCreatureMissionManager* mCreatureMissionManager;   // +0xd0
    cTexturePreload* mTexturePreload;              // +0xd4
    uint32_t padd8;
    bool     mbHatchPending;                       // +0xdc
    bool     mbFirstLoad;                          // +0xdd
    bool     mbSkipHatch;                          // +0xde
    char     paddf;
    int      mSimulatorsRegistered;                // +0xe0
    bool     mbShowTutorial;                       // +0xe4
    bool     mbTutorialFromIntro;                  // +0xe5

    void ContinueLoading(IHandlerRC* handler);
    void SwitchToMode(int mode);                   // 0x00d3af00
    void SignalCreatureEvent(uint32_t id);         // 0x00d3cdc0
    void SetupCreatureGame();                      // 0x00d42570
    void RegisterSimulators();                     // 0x00d392f0
    void SkipToGame();                             // 0x00d3aea0

    __forceinline void BroadcastToScenarios(uint32_t id, cAvatarEvent* ev)
    {
        for (cCreatureModeScenario** it = mScenariosBegin; it != mScenariosEnd; ++it)
            (*it)->HandleEvent(id, ev);
    }
    static __forceinline bool IsFreshStart(uint32_t mode)
    {
        return mode == 0x2ccd1d2 || mode == 0xffffffff || mode == 0x1654c00;
    }
};
}

class cEvoTracker { public: void Init(); };   // 0x00ba06a0

enum
{
    kModeFromEditor   = 0x00dbdba1,
    kModeFromCell     = 0x01654c08,
    kModeEditorReturn = 0x01654c06,
    kModeCreatureGame = 0x01654c00,
};

static __forceinline bool CivListEmpty()
{
    cCivList* civ = g_CivData;
    return civ == 0 || civ->mpNext == &civ->mpNext;
}

// @ 0x00d43e30
void SP::cCreatureModeStrategy::ContinueLoading(IHandlerRC* handler)
{
    uint32_t prevMode = mPreviousMode;

    switch (mState)
    {
    case 0:
    {
        cGameModeManager* gameModes = GameModeManager();
        cSimTicker* ticker = SimTicker();
        cPartRefList oldParts;

        if (!mbRegisteredForMessages)
        {
            mMessageRegistration.Init(GetMessageServer(), mHandler, kCreatureModeMessages, 12);
            mbRegisteredForMessages = true;
        }
        SetupCreatureGame();

        float timeScale = g_SimSpeed[3] + g_SimSpeed[2] + g_SimSpeed[1] + g_SimSpeed[0];
        NounManager()->GetCurrentTerrainSphere()->mTimeScale = timeScale;

        GameInputManager()->LoadTriggerConfig("TriggerConfigCreatureGame", 0, 1);
        const char* wasd = "TriggerConfigWASD";
        if (*LocaleManager()->GetLanguage() == L"fr-fr")
            wasd = "TriggerConfigWASD_fr-fr";
        GameInputManager()->LoadTriggerConfig(wasd, 0, 0);

        if (mpInputStrategy == 0)
        {
            cCreatureModeInputStrategy* strategy =
                new ("Simulator", 0, 0, 0, 0) cCreatureModeInputStrategy();
            *(InputStrategyPtr*)&mpInputStrategy = strategy;   // AutoRefCount::operator= (0x00d38b10)
            mpInputStrategy->Initialize();
        }
        mpInputStrategy->Reset();
        mpInputStrategy->mbActive = false;
        cCreatureModeInputStrategy* input = mpInputStrategy;
        input->Init(ConfigManager()->GetValue(0x679b85e));
        gameModes->SetInputHandler(mpInputStrategy ? &mpInputStrategy->mRefCount : 0, 1);
        CursorManager()->SetLocalCursor(0x1002);

        if (prevMode == kModeFromEditor)
        {
            SwitchToMode(0);
            if (mbHatchPending == true && !mbSkipHatch)
            {
                cAvatarEvent ev;
                ev.mpAvatar = NounManager()->GetAvatar();
                ev.mpOther = 0;
                ev.mValue = 0;
                BroadcastToScenarios(0x53f0369, &ev);
            }
            CameraManager()->Reset();
        }
        else
        {
            mGameMode = 0;
            if (!IsFreshStart(prevMode))
            {
                CameraManager()->Reset();
            }
            else
            {
                cUniverse* universe = CurrentUniverse();
                cPlanetRecordHolder* planet = GetActivePlanet();
                mbFirstLoad = ConfigManager()->GetValue(0x4ea96cb) == 0;
                ((cEvoTracker*)mEvolutionTracker)->Init();
                AchievementsController()->Trigger(0x838a3cf4, -1, 0);

                if (universe->GetPropertyList() != 0)
                {
                    PropertyListPtr markerList;
                    markerList.mpObject = 0;
                    uint32_t markerID = 0;
                    cPropertyManager* pm = PropertyManager();
                    if (pm->GetPropertyList(universe->GetPropertyList(), 0xe38475d9, markerList.AsPPTypeParam()))
                        GetPropertyAsUint32((cPropertyList*)markerList.mpObject, 0x64c82c8c, &markerID);

                    PlanetModel()->SetPlanet(planet->GetRecord(1, 1));

                    if (markerID != 0)
                    {
                        FUN_00d1c610(markerID, 1);
                        uint32_t scratch[6];
                        void* nest = 0;
                        FUN_00b98f00(scratch, &nest);
                        cHerd* herd = InterfaceCastHerd((char*)nest + 0x1a4);
                        NounManager()->AddHerd(herd);
                        herd->mbActive = true;
                        SpawnHerd(herd->GetPosition(), herd->mpProfile, 1, herd, 1, 0);
                    }
                    if (markerList.mpObject)
                        markerList.mpObject->Release();
                }

                cSPCreatureBase* avatar = NounManager()->GetAvatar();
                cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
                if (avatar != 0)
                {
                    FUN_00d2e980();
                    FUN_00d2e720();
                    FUN_00d2e580();
                    avatar->mEffects.SetEnabled(1);
                    if (avatar->mpSpecies->mBonus > 0.0f)
                        AchievementsController()->AutoTest(0x6e36e67f, 1);
                    if (sphere != 0)
                    {
                        AddEvoPoints((float)sphere->mPendingEvoPoints);
                        sphere->mPendingEvoPoints = 0;
                        cAvatarEvent ev;
                        ev.mpAvatar = avatar;
                        ev.mpOther = sphere;
                        ev.mValue = 0;
                        BroadcastToScenarios(0x61b1320, &ev);
                    }
                }

                cTimeOfDay* tod = cTimeOfDay::Instance();
                if (tod != 0 && NounManager()->GetAvatar() != 0)
                {
                    float t = g_CreatureTimeOfDay * 0.041666668f;
                    float lo = 0.0f;
                    float hi = 1.0f;
                    t = t > lo ? t : lo;
                    t = t < hi ? t : hi;
                    float dayLength = cTimeOfDay::Instance()->mDayLength;
                    int team = NounManager()->GetAvatar()->mStats.GetTeam();
                    tod->SetTime(t * dayLength, team);
                }
            }
        }

        // simulators
        uint32_t mode = prevMode;
        if (mode != kModeFromEditor && mode != kModeFromCell)
        {
            PosseSimulator()->Initialize();
            ticker->AddSimulator(PosseSimulator());
            TribeSimulator()->Initialize();
            ticker->AddSimulator(TribeSimulator());
            AnimalSimulator()->Initialize();
            ticker->AddSimulator(AnimalSimulator());
            RegisterSimulators();
            mSimulatorsRegistered = 1;
        }

        cRenderer* renderer = g_Renderer;
        renderer->SetRenderMode(FNV1_String8("Planet_Creature", 0x811c9dc5, 1));

        cModelWorldLoader* loader = ModelWorldLoader();
        if (loader != 0)
        {
            loader->SetWorld(g_Renderer);
            loader->AddModelWorld(GonzagoModelWorld(), 3);
            void* world = ModelManager()->GetModelWorld(0x3fbae24);
            if (world != 0)
                loader->AddModelWorld(world, 0);
            loader->SetLayer(DefaultLayer(), 0x20007);
            loader->SetGroup(0x5e51bb6);
            loader->SetEnabled(1);
        }

        if (mode != kModeEditorReturn && mode != kModeFromEditor)
        {
            GetGameTerrainCursor()->SetVisible(0);
            cPlanetModel* planetModel = PlanetModel();
            cGameNounManager* nm = NounManager();
            if (nm->GetAvatar() == 0)
            {
                cSpeciesManager* species = SpeciesManager();
                Vector3 spawnPos;
                planetModel->DirectionToSurfacePosition(&spawnPos, &kDefaultSpawnDirection);
                cHerd* herd = nm->GetPlayerHerd();
                if (herd != 0)
                {
                    Vector3* p = herd->GetPosition();
                    spawnPos.x = p->x;
                    spawnPos.y = p->y;
                    spawnPos.z = p->z;
                }
                SpawnHerd(&spawnPos, species->GetAvatarProfile(), 1, herd, 1, 0);
            }
        }
        else
        {
            cGameNounManager* nm = NounManager();
            cSPCreatureBase* avatar = nm->GetAvatar();
            cPosseSimulator* posse = PosseSimulator();
            oldParts = avatar->mpSpecies->mParts;

            if (mEditorResult != 0)
            {
                float progressBefore = GetEvoProgress(0);
                SpeciesManager()->UpdateProfile(avatar->mpSpecies, mEditorResult->mProfile);
                avatar->UpdateModel(0);
                FUN_00d2e720();
                float progressAfter = GetEvoProgress(0);
                if (avatar->mpSpecies->mBonus > 0.0f)
                    AchievementsController()->AutoTest(0x6e36e67f, 1);
                AddEvoPoints((float)mEditorResult->mEvoPoints);

                if (!mbReturningFromEditor)
                {
                    if (mEditorResult->mEditorID == 0x64aa168)
                        avatar->SetEditorMode(1);
                    else
                        avatar->SetEditorMode(0);
                }
                avatar->mStats.SetHealth(avatar->GetMaxHealthFor(0));
                avatar->CheckCreatureModel(1, 1);
                avatar->UpdateAnimations();
                avatar->UpdateCollision();
                avatar->ResetState(0);

                float ratio = progressAfter / progressBefore;
                cCreatureVector* creatures = nm->GetCreatures();
                for (cSPCreatureBase** it = creatures->mpBegin; it != creatures->mpEnd; ++it)
                {
                    cSPCreatureBase* c = *it;
                    if (c->mbIsDead && !c->mbIsInPosse)
                        continue;
                    if (c->mpSpecies == avatar->mpSpecies && c != avatar)
                    {
                        c->mStats.SetHealth(c->mStats.GetMaxHealth() * ratio);
                        c->UpdateModel(0);
                        c->CheckCreatureModel(1, 1);
                        c->UpdateAnimations();
                        c->UpdateCollision();
                    }
                    c->UpdatePosition();
                    FUN_00c0d3a0(c);
                    c->UpdateBehavior();
                    if (((c->mFlags >> 9) & 1) || ((c->mFlags >> 8) & 1))
                    {
                        c->mEffects.SetEnabled(1);
                        c->UpdateEffects();
                    }
                }

                if (!mbReturningFromEditor)
                {
                    if (mEditorResult->mEditorID == 0x64aa168)
                        posse->SetMode(1);
                    else
                        posse->SetMode(0);
                    cSpeciesProfile* profile = SpeciesManager()->GetAvatarProfile();
                    cHerdVector* herds = nm->GetHerds();
                    for (cHerd** it = herds->mpBegin; it != herds->mpEnd; ++it)
                    {
                        if ((*it)->mpProfile == profile)
                            (*it)->Refresh();
                    }
                    FUN_00b99530(1, 0, 0);
                }

                if (cEditorResultData* result = mEditorResult)
                {
                    mEditorResult = 0;
                    result->Release();
                }
            }

            cCreatureDataVector* posseMembers = (cCreatureDataVector*)nm->GetGameDataVector(
                FUN_00cd7d10, FUN_00d3d420, FUN_00ace0f0, FUN_00b1e500, 0x18eb45e);
            uint32_t count = (uint32_t)(posseMembers->mpEnd - posseMembers->mpBegin);
            for (uint32_t i = 0; i < count; ++i)
            {
                cSPCreatureBase* member = posseMembers->mpBegin[i];
                if (member->mbIsInPosse)
                {
                    member->SetSelectable(0);
                    member->Deactivate();
                }
            }
        }

        StatsHolder()->SetAvatar(NounManager()->GetAvatar());

        uint32_t from = prevMode;
        if (from == kModeFromEditor)
        {
            mpDisplayStrategy->UpdateAfterEditor(0);
            mpDisplayStrategy->SetVisible(1);
        }
        else
        {
            FUN_00d48a00();
            FUN_00d391d0(from == kModeFromCell);
            FUN_00d3c430();
            if (from == kModeFromCell)
            {
                PosseSimulator()->Initialize();

                cSPCreatureMissionManager* newMgr = g_CreatureMissionManager;
                cSPCreatureMissionManager* oldMgr = mCreatureMissionManager;
                if (newMgr != oldMgr)
                {
                    if (newMgr)
                        newMgr->AddRef();
                    mCreatureMissionManager = newMgr;
                    if (oldMgr)
                        oldMgr->Release();
                }
                mCreatureMissionManager->Start();

                cSPCreatureBase* avatar = NounManager()->GetAvatar();
                if (mbHatchPending)
                {
                    cAvatarEvent ev;
                    ev.mpAvatar = avatar;
                    ev.mpOther = 0;
                    ev.mValue = 0;
                    BroadcastToScenarios(0x53f0369, &ev);
                }
                if (avatar != 0 && g_HatchAgeLimit > avatar->mAge)
                {
                    cAvatarEvent ev;
                    ev.mpAvatar = avatar;
                    ev.mpOther = 0;
                    ev.mValue = 2;
                    BroadcastToScenarios(0x6ca7a75, &ev);
                }

                cGameNounManager* nm = NounManager();
                cGameDataVector* data = (cGameDataVector*)nm->GetGameDataVector(
                    FUN_00cd7d10, FUN_00d3d420, FUN_00b2d1d0, FUN_00b1e500, 0x2a8fb3f);
                cGameDataArray copy;
                copy.Allocate((uint32_t)(data->mpEnd - data->mpBegin), data->mAllocator);
                cGameData** first = copy.mpBegin;
                cGameData** last;
                CopyGameData(&last, data->mpBegin, data->mpEnd, first, nm);
                uint32_t n = (uint32_t)(last - first);
                for (uint32_t i = 0; i < n; ++i)
                {
                    if (first[i]->mType == 0x69793182)
                        nm->DestroyGameData(first[i]);
                }
                for (cGameData** it = first; it < last; ++it)
                {
                    if (*it)
                        ((cRefCountedV1*)*it)->Release();
                }
                if (first && ((int*)first)[-1] != 0)
                    operator delete[](first);
            }
        }

        if (mbReturningFromEditor)
        {
            mpInputStrategy->mbActive = false;
            mpDisplayStrategy->SetVisible(0);
            CursorManager()->ShowCursor(0);
            CursorManager()->SetLocalCursor(0x1002);
        }
        else if (prevMode == kModeFromEditor && !mbSkipHatch)
        {
            mpInputStrategy->mbActive = false;
            CursorManager()->ShowCursor(0);
            CursorManager()->SetLocalCursor(0x1002);
            SetupHatchAtNest();
            SignalCreatureEvent(0x135f21b5);

            cSPCreatureBase* avatar = NounManager()->GetAvatar();
            if (avatar != 0)
            {
                // Parts that were unlocked before the edit and are missing (or new) now.
                cPartRefVector* parts = &avatar->mpSpecies->mParts;
                uint32_t oldCount = oldParts.size();
                for (uint32_t i = 0; i < oldCount; ++i)
                {
                    cPartRef* part = oldParts[i];
                    if (part != 0 && part->mbUnlocked && !FUN_00d397c0(part->mID, parts))
                    {
                        Vector3 a, b;
                        SendCreatureEvent(0x246ba26c, avatar->GetSpeciesKey(), b,
                                          *(Vector3*)(part->mpInfo + 8), a);
                    }
                }
                uint32_t newCount = (uint32_t)(parts->mpEnd - parts->mpBegin);
                for (uint32_t i = 0; i < newCount; ++i)
                {
                    cPartRef* part = parts->mpBegin[i];
                    if (part == 0 || !part->mbUnlocked)
                        continue;
                    uint32_t k;
                    uint32_t oldN = oldParts.size();
                    for (k = 0; k < oldN; ++k)
                    {
                        if (oldParts[k]->mID == part->mID)
                            break;
                    }
                    if (k < oldN)
                        continue;
                    Vector3 a, b;
                    SendCreatureEvent(0x278e6ca8, avatar->GetSpeciesKey(), b,
                                      *(Vector3*)(part->mpInfo + 8), a);
                }
            }
            Vector3 a, b, c;
            SendCreatureEvent(0x6701aff5, avatar->GetSpeciesKey(), c, b, a);
        }

        GameModeManager()->PostEvent(0xb03af999);
        if (cEditorResultData* result = mEditorResult)
        {
            mEditorResult = 0;
            result->Release();
        }
        if (IsFreshStart(prevMode))
        {
            mState = 1;
            mFrames = 0;
        }
        else
        {
            mState = 2;
        }
        break;
    }

    case 1:
    {
        PlanetModel()->sInitMinimap(handler, 0, 0);
        cGamePlanetData* planetData = GamePlanetData();
        if (planetData->mpBegin == planetData->mpEnd && mFrames <= 1000)
            break;
        FUN_00ba1c60(0x1654c01);
        mState = 2;
        if (prevMode == kModeCreatureGame && CivListEmpty())
            mState = 3;
        break;
    }

    case 2:
    {
        mState = 5;
        mFrames = 0;
        cLoadingScreen* screen = FUN_00b60a50(App()->GetWindowManager()->GetMainWindow());
        if (screen != 0)
            screen->SetProgress(g_LoadingProgress);
        break;
    }

    case 3:
    {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        ResourceKey* speciesKey = NounManager()->GetAvatar()->GetSpeciesKey();
        EditorLaunchDataPtr launch(new ("App", 0, 0, 0, 0) cEditorLaunchData());
        cEditorLaunchData* data = launch.mpObject;
        data->mEditorID = 0xfd4902bd;
        data->mSpeciesKey = *speciesKey;
        data->mMode = 0x12191ca;
        data->mpPlanetRecord = sphere->mpPlanetRecord;
        data->mb34 = false;
        data->mb36 = false;
        data->mb38 = false;
        data->mb37 = false;
        data->mb39 = false;
        data->mb3b = false;
        data->mb3c = true;
        data->mb3d = true;
        data->mb6c = true;
        uint32_t key;
        key = sphere->mTerrainKeys[0];
        data->mTerrainKeys.push_back(key);
        key = sphere->mTerrainKeys[1];
        data->mTerrainKeys.push_back(key);
        key = sphere->mTerrainKeys[2];
        data->mTerrainKeys.push_back(key);
        key = sphere->mTerrainKeys[3];
        data->mTerrainKeys.push_back(key);
        Editor::Launch(data);
        GameTimeManager()->Pause(0x4bf38a7);
        mState = 4;
        break;
    }

    case 4:
        break;

    case 5:
    {
        if (mFrames > 5)
            mState = 6;
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        if (avatar != 0 && avatar->GetHerd() != 0)
        {
            Vector2 def;
            def.x = kHabitatSize[0];
            def.y = kHabitatSize[1];
            Vector2 size;
            GetPropertyVector2(&size, mpCreaturePropList, 0x509beb7, def);
            HabitatMap()->SetCenter(avatar->GetHerd()->GetPosition(), size);
        }
        GameModeManager()->Activate(handler);
        GameModeManager()->Deactivate(handler);
        break;
    }

    case 6:
    {
        AudioManager()->Lock(0x16, 2);
        CameraManager()->Shutdown();
        int pending = ProgressManager()->GetPendingCount();
        int worldPending = GonzagoModelWorld()->GetPendingCount();
        bool flag = g_LoadingFlagA || g_LoadingFlagB;
        cSpeciesProfile* profile = SpeciesManager()->GetAvatarProfile();
        if (ProgressManager()->IsLoading(profile->mResource) || pending > 0 || worldPending > 0 || flag)
        {
            if (!AppSystem()->IsBusy())
                AppSystem()->SetBusy(true);
            break;
        }
        if (AppSystem()->IsBusy() == true)
            AppSystem()->SetBusy(false);
        AudioManager()->Unlock(0x16, 2);
        GameTimeManager()->Pause(0x4bf38a7);
        mState = 0xd;
        mpInputStrategy->mbActive = true;
        FUN_00d3a830();

        if (CivListEmpty() && (IsFreshStart(prevMode) || mbReturningFromEditor))
        {
            mState = 7;
            mFrames = 0;
        }
        else if (CivListEmpty() && prevMode != kModeFromEditor)
        {
            if (TutorialManager()->IsReady())
            {
                if (mbShowTutorial)
                {
                    TutorialManager()->Start();
                    mState = 0xa;
                    mbTutorialFromIntro = false;
                }
                else
                {
                    TutorialManager()->Show(0, 0x1654c01, 1);
                }
            }
        }
        mbReturningFromEditor = false;
        if (mbSkipHatch)
        {
            SkipToGame();
            mState = 0xc;
        }
        FUN_00d3c3b0();
        break;
    }

    case 7:
        if (mTexturePreload != 0 && !mTexturePreload->IsDone())
            break;
        mFrames = 0;
        if (mbShowTutorial && TutorialManager()->IsReady())
        {
            TutorialManager()->Start();
            mState = 0xa;
            mbTutorialFromIntro = true;
            break;
        }
        mState = 8;
        break;

    case 8:
    {
        if (mFrames <= 1)
            break;
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        {
            Vector3 a, b, c;
            SendCreatureEvent(0xade76cce, avatar->GetSpeciesKey(), c, b, a);
        }
        mState = 9;
        mFrames = 0;
        AchievementsController()->Trigger(0xd082675a, 2, 1);
        UIEventManager()->SetState(1);
        char* nest = avatar->GetHerd()->mpNest;
        cTransitionMessage msg;
        cTransitionMessage* m = msg.Init(nest ? nest + 0x34 : 0, 0);
        UIEventManager()->Send(0x6049a108, m);
        msg.Destroy();
        UIEventManager()->StartTransition("CLG2CRG", 1, 0, 0, 0, 0);
        break;
    }

    case 9:
        if (!UIEventManager()->IsTransitionDone() && mFrames <= 10)
            break;
        if (TutorialManager()->IsReady())
            TutorialManager()->Show(0, 0x1654c01, 1);
        mState = 0xd;
        break;

    case 10:
        if (TutorialManager()->IsFinished())
        {
            TutorialManager()->Advance();
            mState = 0xb;
        }
        break;

    case 11:
        if (TutorialManager()->IsClosed())
        {
            if (mbTutorialFromIntro)
            {
                mState = 8;
                break;
            }
            if (TutorialManager()->IsReady())
                TutorialManager()->Show(0, 0x1654c01, 1);
            mState = 0xd;
        }
        break;

    case 12:
    default:
        mState = 0xd;
        break;
    }

    GameModeManager()->Update(handler);
}
