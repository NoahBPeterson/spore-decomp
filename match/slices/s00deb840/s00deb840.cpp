// Slice s00deb840 -- Spore galaxy-game-entry ("GGE") UI module, Simulator app mode.
//
//  00deb840  cGalaxyGameEntryUIStateMachine::SpawnBehaviorMessage   (registers a UI::BehaviorMessage)
//  00deb930  cGalaxyGameEntryUIStateMachine::StartGame             (apply the chosen game settings)
//  00debe30  cGalaxyGameEntryUIStateMachine::OnMessageCloseZoom    (close the zoom modal)
//  00debec0  cGalaxyGameEntryUIStateMachine::EnterPlanet           (build path, post load message)
//  00dec020  cGalaxyGameEntryUIStateMachine::StartNewGameZoom
//  00dec170  cGalaxyGameEntryUIStateMachine::Update                (per-tick state machine step)
//  00dec360  close the asset browser / hide the global UI
//  00dec3b0  show the global UI, refresh the "asset browser open" flag
//  00dec3f0  refresh the navigation controls when everything is idle
//  00dec430  queue a window mask update unless the id is deferred
//  00dec460  ResetGameUI      (restore the five asset-selection windows)
//  00dec4a0  CanPlay          (game settings consistent with the chosen state)
//  00dec500  ResetButtons     (ResetGameUI + disable the six asset buttons)
//  00dec540  IsAssetWindowOn
//  00dec570  UpdateLocks
//  00dec6d0  ShowSkin
//  00dec770  QueueEditorLaunch
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the wstring locals carry no unwind
// frame; same module as s00de1710 / s00df3be0).
#include "types.h"
#include <intrin.h>
#include <string.h>

void* operator new(unsigned int size, const char* name, int flags, unsigned int align,
                   const char* file, int line);            // 0x00f473a0
void operator delete[](void* p);                            // 0x00f47380

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

// ---------------------------------------------------------------------------------------------
// UTFWin window / layout stubs (slot indices only; the real declarations live in the migrated
// UTFWin headers).
struct IWindow {
    PV8 PV2 PV
    virtual uint32_t GetState();                        // +0x2c
    PV8 PV8 PV2 PV
    virtual void SetFlag(int flag, int value);          // +0x7c
    virtual void SetParam(const void* param);            // +0x80
};

class cSPUILayout {
public:
    uint32_t pad[3];
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    void SetVisibility(bool visible);                       // 0x00810590
};

class cSPUIGlobalUI {
public:
    uint32_t pad[3];
    void SetVisibility(bool visible);                       // 0x00e01350
};

// a ref-counted object: +0x04 Release, +0x08 SetFlag(int), +0x0c with one int argument
class IRefObj {
public:
    virtual void vf0();                                 // +0x00
    virtual void Release();                             // +0x04
    virtual void SetFlag(int value);                    // +0x08
    virtual IRefObj* vf3(int value);                    // +0x0c
    void Zoom(float seconds);                           // 0x00dde900
};

// the effect store reached through ggpGGE +0x15c
class IEffectStore {
public:
    virtual void vf0();                                 // +0x00
    virtual void vf1();                                 // +0x04
    virtual void Find(uint32_t id, int flags, IRefObj** out);   // +0x08
};

struct EffectPtrVector {
    IRefObj** mpBegin;      // +0x00
    IRefObj** mpEnd;        // +0x04
    IRefObj** mpCapacity;   // +0x08
    void DoFree(IRefObj** begin, IRefObj** end);        // 0x00533500
};

struct IMessageServer {
    PV4
    virtual void v4();                                       // +0x10
    virtual void Send(uint32_t id, const void* payload, int arg);  // +0x14
    virtual void Send2(uint32_t id, const void* payload, int a, int b); // +0x18
};

// ---------------------------------------------------------------------------------------------
// EASTL wide string (retail: 0x10 bytes, allocator tag at +0x0c).
class WString {
public:
    WString(const wchar_t* psz, bool* pOk);                 // 0x0041df50
    WString(const wchar_t* psz) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        RangeInitialize(psz);                              // 0x00579a90
    }
    WString(const WString& other) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        uint32_t count = (uint32_t)(other.mpEnd - other.mpBegin);
        AllocateSelf(count + 1);                           // 0x00429760
        memcpy(mpBegin, other.mpBegin, count * sizeof(wchar_t));
        mpEnd = mpBegin + count;
        *mpEnd = 0;
    }
    ~WString() { DeallocateSelf(); }
    WString& operator=(const WString& other)
    {
        if (this != &other)
            assign(other.mpBegin, other.mpEnd);            // 0x00423650
        return *this;
    }
    void DeallocateSelf()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            ::operator delete[]((char*)mpBegin);
    }
    void AllocateSelf(uint32_t n);                          // 0x00429760
    void RangeInitialize(const wchar_t* psz);               // 0x00579a90
    void assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    uint32_t mAllocator;    // +0x0c
};

WString __cdecl PathJoin(const WString& name, const wchar_t* pBase);  // 0x0057cba0
WString __cdecl PathPick(const WString& a, const WString& b);         // 0x00688f00

// ---------------------------------------------------------------------------------------------
// The module-wide GGE GUI object (0x016a1344 points at it).
struct GGEGlobal {
    uint8_t pad000[0xef];
    bool mbEF;                  // +0xef
    uint8_t padF0[4];
    bool mbF4;                  // +0xf4
    uint8_t padF5[0x0b];
    bool mb100;                 // +0x100
    bool mb101;                 // +0x101
    bool mb102;                 // +0x102
    uint8_t pad103;
    uint32_t mu104;             // +0x104
    uint32_t mu108;             // +0x108
    uint32_t mu10c;             // +0x10c
    uint8_t pad110[0x30];
    bool mb140;                 // +0x140
    uint8_t pad141[3];
    cSPUILayout mLayout;        // +0x144
    uint8_t pad150[0x0c];
    IEffectStore* mpEffectStore;    // +0x15c
    uint8_t pad160[0x24];
    cSPUIGlobalUI* mpGlobalUI;      // +0x184
    uint8_t pad188[0x10];
    IRefObj* mp198;                 // +0x198 (zoom helper object)
    IRefObj* mp19c;                 // +0x19c
    uint8_t pad1a0;
    IRefObj* mp1a4;                 // +0x1a4
    uint8_t pad1a8[0x30];
    EffectPtrVector mEffects;       // +0x1d8
    uint8_t pad1e4[0x0c];
    bool mb1f0;                     // +0x1f0

    void MoveTo(bool mode);                         // 0x00de53d0
    void NotifyStateChange(int mode, bool flag);    // 0x00de86d0
    void PopModeStack();                            // 0x00de52d0
};
extern GGEGlobal* gpGGE;                            // 0x016a1344

// ---------------------------------------------------------------------------------------------
// SP::cGameInfo (retail layout, only the members this slice touches).
struct cAvatarProfile {
    uint8_t pad000[0x4ec];
    float mf4ec;                // +0x4ec
    float mf4f0;                // +0x4f0
    float mf4f4;                // +0x4f4
};

struct ResourceKey {
    uint32_t mnInstanceID;      // +0x00
    uint32_t mnTypeID;          // +0x04
    uint32_t mnGroupID;         // +0x08
};

struct Vector3 {
    float x, y, z;
};

struct cStarName;

struct cStarRecord {
    uint8_t pad00[0x58];
    uint32_t m58;               // +0x58
    uint8_t pad5c[0x50];
    bool mbAC;                  // +0xac
    uint32_t Get58();                   // 0x00989360
    void Measure(int flags);            // 0x00bbaa80
    cStarName* GetName(int index);      // 0x00bbaa60
    void SetKey(const ResourceKey* pKey);   // 0x00bb9b90
};

struct cStarName {
    uint8_t pad00[0x18];
    WString mName;              // +0x18
    uint8_t pad28[0x17c];
    Vector3 mPos;               // +0x1a4
    Vector3* GetPosition();     // 0x00b8d8e0
};

struct cGameInfo {
    WString mPath;              // +0x00
    uint8_t pad10[0x10];
    WString mName;              // +0x20
    uint8_t pad30[0x18];
    cAvatarProfile* mpAvatar;   // +0x48
    ResourceKey mKey4C;         // +0x4c
    ResourceKey mKey58;         // +0x58
    ResourceKey mKey64;         // +0x64
    ResourceKey mKey70;         // +0x70
    uint32_t mnStarID;          // +0x7c
    uint8_t pad80[0x0c];
    uint32_t m8C;               // +0x8c
    uint32_t m90;               // +0x90
    uint8_t pad94[0x10];
    uint32_t mA4;               // +0xa4
    uint32_t mA8;               // +0xa8
    bool mbAC;                  // +0xac
    uint8_t padAD[0x0b];
    cSPUILayout* mpLayout;      // +0xb8
    cStarRecord* GetStarRecord();   // 0x00de4610
};

// the planet editing sphere NounManager hands out
struct cTerrainSphere {
    uint8_t pad000[0x68c];
    uint32_t mu68c;             // +0x68c
    uint32_t mu690;             // +0x690
    uint32_t mu694;             // +0x694
    uint8_t pad698[0xa64];
    uint32_t mu10fc;            // +0x10fc
    uint32_t mu1100;            // +0x1100
    uint32_t mu1104;            // +0x1104
    uint32_t mu1108;            // +0x1108
    uint8_t pad110c[0x44];
    uint32_t mu1150;            // +0x1150
    uint32_t mu1154;            // +0x1154
    uint32_t mu1158;            // +0x1158
    uint32_t mu115c;            // +0x115c
    uint32_t mu1160;            // +0x1160
    uint32_t mu1164;            // +0x1164
    uint32_t mu1168;            // +0x1168
    uint32_t mu116c;            // +0x116c
    uint32_t mu1170;            // +0x1170
    uint32_t mu1174;            // +0x1174
};

// SP::cGalaxyGameEntryUIStateMachine (retail layout; only the members this slice touches).
struct cGalaxyGameEntryUIStateMachine {
    uint8_t pad00[8];
    int mCountdown;             // +0x08
    cGameInfo* mpGameInfo;      // +0x0c
    uint8_t pad10[0x18];
    cSPUILayout mLayout;        // +0x28
    uint8_t pad34[0x50];
    struct PlayEntry {
        uint8_t pad00[0xac];
        uint32_t mAC;           // +0xac
        uint32_t mB0;           // +0xb0
        uint32_t mB4;           // +0xb4
        uint8_t padB8[8];
    };
    PlayEntry mEntries[6];      // +0x84
    uint32_t mu504;             // +0x504
    uint32_t mu508;             // +0x508
    uint32_t mu50c;             // +0x50c
    uint32_t mu510;             // +0x510
    uint8_t pad514[0xd0];
    uint32_t mu5e4;             // +0x5e4
    uint8_t pad5e8[0x40];
    cGameInfo* mpGameInfo628;   // +0x628

    void SpawnBehaviorMessage(cGameInfo* gameInfo);     // 0x00deb840
    void StartGame();                                   // 0x00deb930
    bool OnMessageCloseZoom(uint32_t id, int arg);      // 0x00debe30
    void EnterPlanet(const WString& name);              // 0x00debec0
    void StartNewGameZoom();                            // 0x00dec020
    void Update(int arg);                               // 0x00dec170
    void RefreshWhenIdle(int arg);                      // 0x00dec3f0
    void SetDeferredWindow(uint32_t id, void* param);   // 0x00dec430 -> 0x00e00650
    void ResetGameUI();                                 // 0x00dec460
    bool CanPlay();                                     // 0x00dec4a0
    void ResetButtons();                                // 0x00dec500
    bool IsAssetWindowOn(uint32_t id);                  // 0x00dec540
    void UpdateLocks();                                 // 0x00dec570
    void ShowSkin(uint32_t id);                         // 0x00dec6d0
    void QueueEditorLaunch(uint32_t id, const uint32_t* key); // 0x00dec770

    void StopZoomTransition();                          // 0x00deb5d0
    void SetupTerrainFromGame(cGameInfo* gameInfo);     // 0x00deb770
    void SetWindowParam(uint32_t id, void* param);      // 0x00e00650
};

// ---------------------------------------------------------------------------------------------
// UI message posted when the game settings are applied (UI::BehaviorMessage).
extern void* vtbl_RefBaseA22[];         // 0x013eb90c
extern void* vtbl_UIBehaviorMessage[];  // 0x013eb844

struct UIBehaviorMessage {
    void** mpVfptr;             // +0x00
    uint32_t mnRefCount;        // +0x04
    const char* mpStateName;    // +0x08
    uint32_t pad0c;
    uint32_t mu10;              // +0x10
    uint32_t pad14[7];
    uint32_t mnMessageID;       // +0x30
    uint32_t mu34;              // +0x34
    uint32_t mu38;              // +0x38
    uint32_t mu3c;              // +0x3c

    UIBehaviorMessage()
    {
        mnMessageID = 0;
        mpVfptr = vtbl_RefBaseA22;
        _InterlockedExchange((volatile long*)&mnRefCount, 0);
        mpVfptr = vtbl_UIBehaviorMessage;
        mu38 = 0;
        ((void (__thiscall*)(UIBehaviorMessage*))mpVfptr[1])(this);
    }
    void Release()
    {
        ((void (__thiscall*)(UIBehaviorMessage*))mpVfptr[2])(this);
    }
};

// ---------------------------------------------------------------------------------------------
// Singletons and free helpers used by this slice.
void*  __cdecl NounManager();                      // 0x00b3d300
void*  __cdecl GetGameMode();                      // 0x00b3d340
void*  __cdecl GetPlanetModel();                   // 0x00b3d350
void*  __cdecl GetTriggerMgr();                    // 0x00b3d4d0
void*  __cdecl GetSetting9();                      // 0x00401090
void*  __cdecl GetSetting3();                      // 0x00401030
void*  __cdecl GetResourceManager();               // 0x0067dcd0
void*  __cdecl AppSystem();                        // 0x0067dd00
void*  __cdecl GetSystemX();                       // 0x0067dd20
void*  __cdecl LocaleManager();                    // 0x0067de40
IMessageServer* __cdecl MessageServer();           // 0x0067dcc0
void*  __cdecl GetAux0();                          // 0x00b3d360
void*  __cdecl GetAux410();                        // 0x00b3d410
char   __cdecl IsWorldLayoutFlagSet(int flag);     // 0x00685520
void   __cdecl FUN_00de3be0(cGameInfo* gameInfo);  // 0x00de3be0
char   __cdecl FUN_00550970(void* self);           // 0x00550970 (this in ecx)
uint32_t __cdecl FUN_00556140(ResourceKey* key, uint32_t id);  // 0x00556140
void   __cdecl FUN_00e83910(ResourceKey* key, int a, int b, int c); // 0x00e83910
void   __cdecl FUN_00eebf90(void* a, void* b);     // 0x00eebf90
void   __cdecl FUN_005bf3a0(ResourceKey* key, const uint32_t* id, void** out, int flags); // 0x005bf3a0
void   __cdecl CalloutMessageBox(int a, const void* b); // 0x00809db0
void   __cdecl FUN_00b6e4b0(Vector3 v, float a, float b, Vector3* out); // 0x00b6e4b0
void   __cdecl FUN_00b6f140();                     // 0x00b6f140
void   __cdecl FUN_00b6f180();                     // 0x00b6f180

// trigger manager
struct cTriggerMgr {
    void ClearTimers();                             // 0x00adffd0
    void PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930
};

// resource manager singleton
struct cResourceManager {
    PV2 PV
    virtual bool GetResource(const ResourceKey* pKey, IRefObj** ppOut, int a, int b, int c, int d); // +0x0c
};

// game mode object (0x00b3d340)
struct cGameMode {
    PV4
    virtual void PopState(cGameInfo* gameInfo);         // +0x10
    void SavePath(const wchar_t* path);                 // 0x00b27ee0
    void AddStar(cGameInfo* gameInfo);                  // 0x00b27160
    bool QualifyName(const wchar_t* name, uint32_t* a, uint32_t* b); // 0x00b275a0
};

// LocaleManager chain used for the "asset not found" callout
struct cLocaleText {
    PV16 PV4
    virtual void SetText(const wchar_t* text, int flags);   // +0x34
};
struct cLocale {
    PV8 PV2
    virtual cLocaleText* GetCalloutText();                  // +0x20
};

// AppSystem feature query
struct cAppSystem {
    PV16 PV
    virtual bool IsFeatureEnabled();                        // +0x50
};

struct cSetting410 {
    uint8_t pad000[0x508];
    bool mb508;                 // +0x508
};

// NounManager's object: +0x74 is the current terrain sphere.
struct NounMgr {
    uint8_t pad00[0x74];
    void* mpTerrainSphere;      // +0x74
    void ResetEdits();          // 0x00b20fb0
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};

struct cPlanetModel {
    bool SetPosition(Vector3* pos, int a, int b);   // 0x00b8d8a0
};

// the object returned by 0x00b3d360 (reloads the current planet model)
struct cPlanetLoader {
    void Reset();                                   // 0x00b7dec0
};

// the global object reached through 0x0067dd20 (its slot +0x28 takes a message id)
struct cSystemX {
    PV8 PV2
    virtual void PostMessage(uint32_t id);          // +0x28
};

// The AssetBrowser singleton returned by GetSetting3().
struct AssetBrowser {
    uint8_t pad00[0x1c];
    bool mb1c;                  // +0x1c
    bool CloneModelAsset(ResourceKey key, ResourceKey* pOut, uint32_t id, bool flag); // 0x00646370
};

struct cSetting9 {
    cAvatarProfile* GetAvatarProfile();   // 0x004df420
};

extern const char gStateNameTable[];            // 0x01654c00
extern const uint32_t kResetWindowIDs[5];       // 0x0147e51c
extern const uint32_t kButtonWindowIDs[6];      // 0x0147e4d8
extern const uint32_t kWindowFlagParam;         // 0x013ec468
extern const float kfZoomDuration;              // 0x015a2df4
extern const wchar_t* const gpSporePathBegin;   // 0x015689a8
extern const uint32_t kAssetKey;                // 0x015a3e90
extern const uint32_t kNotFoundText;            // 0x015a3dc8
extern uint32_t gDeferredWindowMask[];          // 0x016a1848
extern void* gpTestSystem;                      // 0x015fd928

// =============================================================================================
// @ 0x00deb840
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::SpawnBehaviorMessage(cGameInfo* gameInfo)
{
    if (!gameInfo)
        return;

    const char* name = (const char*)-1;
    switch (gameInfo->mA4) {
    case 0:
        name = &gStateNameTable[0];
        break;
    case 1:
        name = &gStateNameTable[1];
        break;
    case 2:
        name = &gStateNameTable[2];
        break;
    case 3:
    case 4:
        name = &gStateNameTable[4];
        break;
    case 5:
        name = &gStateNameTable[5];
        break;
    }

    UIBehaviorMessage* msg = new ("Simulator", 0, 0, 0, 0) UIBehaviorMessage();
    msg->mnMessageID = 0x4b719d4;
    msg->mpStateName = name;
    msg->mu10 = gameInfo->GetStarRecord()->Get58();
    MessageServer()->Send2(msg->mnMessageID, msg, 0, 0);
    msg->Release();
}

// =============================================================================================
// @ 0x00deb930
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::StartGame()
{
    cGameInfo* gi = mpGameInfo;

    ((NounMgr*)NounManager())->ResetEdits();
    cTerrainSphere* sphere = ((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    gpGGE->mb1f0 = false;

    ResourceKey query = gi->mKey4C;
    query.mnTypeID = 0x30bdee3;

    IRefObj* pResource = 0;
    cResourceManager* pManager = (cResourceManager*)GetResourceManager();
    if (pResource) {
        pResource = 0;
        pResource->Release();
    }

    if (pManager->GetResource(&query, &pResource, 0, 0, 0, 0)) {
        IRefObj* pPart = 0;
        if (pResource)
            pPart = pResource->vf3(0x30bdee3);
        if (pPart)
            pPart->vf0();
        bool bOK = FUN_00550970(pPart) != 0;
        if (pPart)
            pPart->Release();
        if (bOK) {
            switch (gi->mA4) {
            case 5:
                sphere->mu1108 = FUN_00556140(&gi->mKey4C, 0xbeb528cb);
            case 4:
                sphere->mu1104 = FUN_00556140(&gi->mKey4C, 0xf71fa311);
            case 2:
                sphere->mu1100 = FUN_00556140(&gi->mKey4C, 0xad56080c);
            case 1:
                sphere->mu10fc = FUN_00556140(&gi->mKey4C, 0xa426730b);
            }
        }
    }

    if (gi->mA4 == 5 && IsWorldLayoutFlagSet(2)) {
        ((AssetBrowser*)GetSetting3())->CloneModelAsset(gi->mKey4C, &gi->mKey58, 0x4178b8e8, true);
        void* pOut = 0;
        FUN_005bf3a0(&gi->mKey58, &kAssetKey, &pOut, 0);
        FUN_00eebf90(pOut, &gi->mName);
        MessageServer()->Send(0x73e46f6, &gi->mKey58, 0);
        if (pOut)
            ((IRefObj*)pOut)->Release();
    }

    if (gi->mA8 == 0) {
        sphere->mu68c = gi->mKey4C.mnInstanceID;
        sphere->mu690 = gi->mKey4C.mnTypeID;
        sphere->mu694 = gi->mKey4C.mnGroupID;
    } else if (gi->mKey4C.mnTypeID == 0x3d97a8e4) {
        FUN_00e83910(&gi->mKey4C, 0, 0, 0);
    } else {
        SetupTerrainFromGame(gi);
    }

    gi->mpAvatar = ((cSetting9*)GetSetting9())->GetAvatarProfile();
    if (((cAppSystem*)AppSystem())->IsFeatureEnabled()) {
        if (gi->GetStarRecord()->mbAC)
            gi->GetStarRecord()->Measure(1);
    }

    cTerrainSphere* sphere2 = ((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    sphere2->mu1150 = gi->mKey70.mnInstanceID;
    sphere2->mu1154 = gi->mKey70.mnTypeID;
    sphere2->mu1158 = gi->mKey70.mnGroupID;

    gi->GetStarRecord()->SetKey(&gi->mKey4C);

    uint32_t* pDest = 0;
    if (gi->mA4 == 5) {
        pDest = &sphere->mu1168;
    } else if (gi->mA4 == 4) {
        cAvatarProfile* pAvatar = gi->mpAvatar;
        Vector3 v;
        v.x = pAvatar->mf4ec;
        v.y = pAvatar->mf4f0;
        v.z = pAvatar->mf4f4;
        Vector3 out;
        FUN_00b6e4b0(v, 0.5f, 0.5f, &out);
        FUN_00b6f140();
        FUN_00b6f180();
        sphere->mu1174 = gi->m90;
        pDest = &sphere->mu115c;
    }
    if (pDest) {
        pDest[0] = gi->mKey64.mnInstanceID;
        pDest[1] = gi->mKey64.mnTypeID;
        pDest[2] = gi->mKey64.mnGroupID;
    }

    SpawnBehaviorMessage(gi);

    if (gi->mA4 == 0 && (gpTestSystem == 0 || *(void**)((char*)gpTestSystem + 0x70) == (char*)gpTestSystem + 0x70)) {
        ((cTriggerMgr*)GetTriggerMgr())->ClearTimers();
        ((cGameMode*)GetGameMode())->AddStar(gi);
        if (gi->GetStarRecord()->mbAC) {
            cStarName* pName = gi->GetStarRecord()->GetName(0);
            Vector3 pos = *pName->GetPosition();
            pName->mName = gi->mPath;
            ((cPlanetModel*)GetPlanetModel())->SetPosition(&pos, 0, 1);
            ((cSystemX*)GetSystemX())->PostMessage(0x7b023a50);
            ((cTriggerMgr*)GetTriggerMgr())->PostTrigger("GGE2CLG", 1, 0, 0, 0, 0);
        }
    } else {
        if (gi->GetStarRecord()->mbAC) {
            cStarName* pName = gi->GetStarRecord()->GetName(0);
            pName->mName = gi->mPath;
            ((cGameMode*)GetGameMode())->PopState(gi);
        }
    }

    gpGGE->mp198->SetFlag(0);
    mpGameInfo = 0;
    if (pResource)
        pResource->Release();
}

// =============================================================================================
// @ 0x00debe30
// =============================================================================================
bool cGalaxyGameEntryUIStateMachine::OnMessageCloseZoom(uint32_t id, int arg)
{
    (void)arg;
    if (id == 0x4360e14) {
        if (gpGGE->mb1f0) {
            ((cTriggerMgr*)GetTriggerMgr())->ClearTimers();
            IRefObj* pZoom = gpGGE->mp1a4;
            if (pZoom) {
                gpGGE->mp1a4 = 0;
                pZoom->Release();
            }
            IRefObj* pBlur = gpGGE->mp19c;
            if (pBlur) {
                gpGGE->mp19c = 0;
                pBlur->Release();
            }
            gpGGE->mb100 = false;
            StartGame();
        }
        return true;
    }
    return false;
}

// =============================================================================================
// @ 0x00debec0
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::EnterPlanet(const WString& name)
{
    WString str(name);
    str = PathPick(str, gpSporePathBegin);
    MessageServer()->Send(0x680c633, str.mpBegin, 0);
    ((cPlanetLoader*)GetAux0())->Reset();
    ((cGameMode*)GetGameMode())->SavePath(str.mpBegin);
    gpGGE->mp198->SetFlag(0);
    if (!gpGGE->mbF4)
        StopZoomTransition();
}

// =============================================================================================
// @ 0x00dec020
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::StartNewGameZoom()
{
    ((cPlanetLoader*)GetAux0())->Reset();
    gpGGE->MoveTo(0);
    mpGameInfo->mpLayout->SetVisibility(false);

    for (IRefObj** it = gpGGE->mEffects.mpBegin; it != gpGGE->mEffects.mpEnd; ++it)
        (*it)->vf3(1);
    gpGGE->mEffects.DoFree(gpGGE->mEffects.mpBegin, gpGGE->mEffects.mpEnd);

    // the zoom effects live in AutoRefCount handles: the slot outlives the calls
    IRefObj** ppZoom = &gpGGE->mp1a4;
    IEffectStore* pStore = gpGGE->mpEffectStore;
    IRefObj* pZoom = *ppZoom;
    if (pZoom) {
        *ppZoom = 0;
        pZoom->Release();
    }
    pStore->Find(0x61ebc5d1, 0, ppZoom);
    if (gpGGE->mp1a4)
        gpGGE->mp1a4->SetFlag(0);

    ((cTriggerMgr*)GetTriggerMgr())->PostTrigger("GGE_zoom_modal", 0, 0, 0, 0, 0);
    gpGGE->mp198->Zoom(kfZoomDuration);

    IRefObj* pEffect = 0;
    gpGGE->mpEffectStore->Find(0xdc4678a3, 0, &pEffect);
    if (pEffect)
        pEffect->SetFlag(0);
    gpGGE->mb1f0 = true;
    if (pEffect)
        pEffect->Release();
}

// =============================================================================================
// @ 0x00dec170
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::Update(int arg)
{
    (void)arg;
    cGameInfo* gi = mpGameInfo;
    if (!gi || gpGGE->mb1f0)
        return;

    if (mCountdown > 0) {
        if (gi->mbAC) {
            if (mCountdown == 2) {
                StopZoomTransition();
                --mCountdown;
                return;
            }
        } else {
            if (mCountdown == 2) {
                FUN_00de3be0(gi);
                --mCountdown;
                return;
            }
        }
        if (mCountdown == 1 && !gpGGE->mb140 && gi->mA8 != 0) {
            if (!((cSetting410*)GetAux410())->mb508)
                mCountdown = 2;
        }
        --mCountdown;
        return;
    }

    if (gpGGE->mb140) {
        gpGGE->NotifyStateChange(2, false);
        ((cGameMode*)GetGameMode())->PopState(gi);
        return;
    }

    if (gi->mbAC) {
        SpawnBehaviorMessage(gi);
        bool bOk;
        WString path(gi->mPath.mpBegin, &bOk);
        path = PathJoin(path, gpSporePathBegin);
        uint32_t a;
        uint32_t b;
        if (!((cGameMode*)GetGameMode())->QualifyName(path.mpBegin, &a, &b) && a == 0 && b == 0)
            gi->m8C = 3;
        if (gi->m8C == 3) {
            ((cLocale*)LocaleManager())->GetCalloutText()->SetText(path.mpBegin, 0);
            CalloutMessageBox(0, &kNotFoundText);
            gpGGE->NotifyStateChange(2, false);
            return;
        }
        EnterPlanet(path);
        return;
    }

    if (gi->mA8 != 0)
        StartGame();
    else
        StartNewGameZoom();
}

// =============================================================================================
// @ 0x00dec360
// =============================================================================================
void CloseAssetBrowserUI()
{
    IWindow* pWindow = gpGGE->mLayout.FindWindowByID(0x615a5ff, true);
    if (pWindow)
        pWindow->SetFlag(1, 0);
    gpGGE->MoveTo(1);
    gpGGE->mpGlobalUI->SetVisibility(false);
}

// =============================================================================================
// @ 0x00dec3b0
// =============================================================================================
void ShowGlobalUI()
{
    gpGGE->mpGlobalUI->SetVisibility(true);
    bool bBrowserOpen = GetSetting3() && ((AssetBrowser*)GetSetting3())->mb1c;
    gpGGE->MoveTo(bBrowserOpen);
}

// =============================================================================================
// @ 0x00dec3f0
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::RefreshWhenIdle(int arg)
{
    (void)arg;
    if (gpGGE->mu108 == 10 && gpGGE->mu10c == 10 && !gpGGE->mbEF && !gpGGE->mb102 && !gpGGE->mb101)
        gpGGE->PopModeStack();
}

// =============================================================================================
// @ 0x00dec430
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::SetDeferredWindow(uint32_t id, void* param)
{
    if (((gDeferredWindowMask[id >> 5] >> (id & 31)) & 1) == 0)
        SetWindowParam(id, param);
}

// =============================================================================================
// @ 0x00dec460
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ResetGameUI()
{
    for (uint32_t i = 0; i < 5; ++i) {
        IWindow* pWindow = mLayout.FindWindowByID(kResetWindowIDs[i], true);
        if (pWindow)
            pWindow->SetParam(&kWindowFlagParam);
    }
}

// =============================================================================================
// @ 0x00dec4a0
// =============================================================================================
bool cGalaxyGameEntryUIStateMachine::CanPlay()
{
    cGameInfo* gi = mpGameInfo628;
    if (!gi || gi->mA4 == 6)
        return false;
    PlayEntry* pEntry = &mEntries[gi->mA4];
    if (pEntry->mAC != 0 && gi->mKey4C.mnInstanceID == 0)
        return false;
    if (pEntry->mB0 != 0 && gi->mKey70.mnInstanceID == 0)
        return false;
    if (pEntry->mB4 != 0 && gi->mKey64.mnInstanceID == 0)
        return false;
    return true;
}

// =============================================================================================
// @ 0x00dec500
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ResetButtons()
{
    ResetGameUI();
    for (uint32_t i = 0; i < 6; ++i)
        mLayout.FindWindowByID(kButtonWindowIDs[i], true)->SetFlag(2, 0);
}

// =============================================================================================
// @ 0x00dec540
// =============================================================================================
bool cGalaxyGameEntryUIStateMachine::IsAssetWindowOn(uint32_t id)
{
    IWindow* pWindow = mLayout.FindWindowByID(id, true);
    if (pWindow)
        return (pWindow->GetState() >> 2) & 1;
    return false;
}

// =============================================================================================
// @ 0x00dec570
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::UpdateLocks()
{
    switch (mpGameInfo628->mA8) {
    case 0:
    case 1:
    case 2:
        mLayout.FindWindowByID(0x59461b1, true)->SetFlag(1, 0);
        mLayout.FindWindowByID(0x59461b0, true)->SetFlag(1, 0);
        mLayout.FindWindowByID(0x59461b2, true)->SetFlag(1, 0);
        break;
    case 4:
    case 5:
        mLayout.FindWindowByID(0x59461b1, true)->SetFlag(1, 1);
        mLayout.FindWindowByID(0x59461b0, true)->SetFlag(1, 1);
        mLayout.FindWindowByID(0x59461b2, true)->SetFlag(1, 1);
        break;
    }
    if (mpGameInfo628->mKey4C.mnInstanceID == 0)
        mLayout.FindWindowByID(0x59461b1, true)->SetFlag(1, 0);
    if (mpGameInfo628->mKey64.mnInstanceID == 0)
        mLayout.FindWindowByID(0x59461b0, true)->SetFlag(1, 0);
    if (mpGameInfo628->mKey70.mnInstanceID == 0)
        mLayout.FindWindowByID(0x59461b2, true)->SetFlag(1, 0);
}

// =============================================================================================
// @ 0x00dec6d0
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::ShowSkin(uint32_t id)
{
    const uint32_t skins[5] = {0x5b218d1, 0x5b218c9, 0x5adf8e2, 0x5b8a143, 0x5b218d9};
    for (uint32_t i = 0; i < 5; ++i) {
        if (mLayout.FindWindowByID(skins[i], true))
            mLayout.FindWindowByID(skins[i], true)->SetFlag(1, 0);
    }
    if (id) {
        if (mLayout.FindWindowByID(id, true))
            mLayout.FindWindowByID(id, true)->SetFlag(1, 1);
    }
}

// =============================================================================================
// @ 0x00dec770
// =============================================================================================
void cGalaxyGameEntryUIStateMachine::QueueEditorLaunch(uint32_t id, const uint32_t* key)
{
    mu504 = id;
    mu5e4 = 10;
    mu508 = key[0];
    mu50c = key[1];
    mu510 = key[2];
    MessageServer()->Send2(0x5b5c746, 0, 0, 0);
}
