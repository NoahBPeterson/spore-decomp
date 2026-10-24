// Slice s00dd1280 -- SPUIBanningContent.obj: the "ban a creature / save / planet" side panel.
//
// The panel keeps a lazily created layout (cSPUILayout), two windows found by id inside it, and a
// 3-dword "ban key" (id, group, name) that identifies whatever the user is currently pointing at.
// Almost everything here is either a message handler plumbing call into SP::MessageServer, or a
// translation of a numeric "bannability" state into one of the UI text keys declared at the bottom.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct IEmpty {};

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t, eastl::allocator>
// ---------------------------------------------------------------------------------------------
extern wchar_t gEmptyString16[];                       // 0x01667bac `?gEmptyString16@eastl@@3PA_WA`
void __cdecl FreeArray(void* block);                   // 0x00f47380 operator delete[]

struct WString {
    wchar_t* mpBegin;                                  // +0x00
    wchar_t* mpEnd;                                    // +0x04
    wchar_t* mpCapacity;                               // +0x08
    uint32_t mAllocatorState;                          // +0x0c

    WString()
    {
        mpBegin = gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void Release()
    {
        if (((int32_t)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2) {
            if (mpBegin)
                FreeArray(mpBegin);
        }
    }
};

// ---------------------------------------------------------------------------------------------
// (id, group, name) triples -- the key of a piece of UI text
// ---------------------------------------------------------------------------------------------
struct tUiKey {
    uint32_t mId;                                      // +0x00
    uint32_t mGroup;                                   // +0x04
    uint32_t mName;                                    // +0x08
};

struct tNoKey {                                        // the all-zero "nothing selected" key
    uint32_t mId;
    uint32_t mGroup;
    uint32_t mName;
    tNoKey()
    {
        mId = 0;
        mGroup = 0;
        mName = 0;
    }
};

// ---------------------------------------------------------------------------------------------
// reference counted helpers
// ---------------------------------------------------------------------------------------------
struct IRefCounted {
    virtual int AddRef();                              // +0x00
    virtual int Release();                             // +0x04
};

template <class T> class AutoRefCount {
public:
    T* mpObject;                                       // +0x00

    AutoRefCount() : mpObject(0) {}
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    void operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
    }
};

// ---------------------------------------------------------------------------------------------
// EA::UTFWin windows
// ---------------------------------------------------------------------------------------------
struct IWinX {
    virtual int AddRef();                              // +0x00
    virtual int Release();                             // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);        // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void vbc(); virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0();
    virtual void ve4(); virtual void ve8(); virtual void vec(); virtual void vf0(); virtual void vf4();
    virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(void* pWinProc);           // +0x104
};

// cSPUILayout: refcount at vtable +4 / +8, so slot 0 is not AddRef
class cSPUILayout {
public:
    virtual void v00();
    virtual int  AddRef();                             // +0x04
    virtual int  Release();                            // +0x08
    cSPUILayout* CenterWindowInRect();                 // 0x006abf70
    bool         Init(const tUiKey* pKey, int mode, uint32_t id);   // 0x008120d0
    void         SetVisibility(int visible);           // 0x0080...
    void         Shutdown(int force);                  // 0x00811ad0
    IWinX*       FindWindowByID(uint32_t id, bool recursive);       // 0x008105b0
};

struct LayoutPtr {                                     // AddRef at vtable +4, Release at +8
    cSPUILayout* mpObject;
    LayoutPtr() : mpObject(0) {}
    cSPUILayout* get() const { return mpObject; }
    cSPUILayout* operator->() const { return mpObject; }
    void operator=(cSPUILayout* pObject)
    {
        if (pObject != mpObject) {
            cSPUILayout* pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
    }
};

// cursor table -- the single global cursor manager
class cCursorTable {
public:
    void AddCursor(uint32_t id, const wchar_t* pName, int a, int b, int c);   // 0x00802050
    void SetCursor(uint32_t id);                                             // 0x00801bb0
};
cCursorTable* __cdecl CursorManager();                 // 0x0067cab0

void* AllocLayoutObject(uint32_t size);                 // 0x006abeb0
void AutoSizeWindowForText(IWinX* pWindow, int a, int b);   // 0x00806600

// ---------------------------------------------------------------------------------------------
// message server
// ---------------------------------------------------------------------------------------------
struct IMessageServer {
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();
    virtual void Send(uint32_t message, int a, int b);                 // +0x14
    virtual void Broadcast(uint32_t message, int a, int b, int c);     // +0x18
    virtual void v1c();
    virtual void SendTo(void* target, uint32_t message);               // +0x20
    virtual void v24();  virtual void v28();
    virtual void Dispatch(void* target, uint32_t message, int error);  // +0x2c
};
IMessageServer* __cdecl MessageServer();               // 0x0067dcc0

// ---------------------------------------------------------------------------------------------
// game objects addressed through their interface query (vtable +0x0c)
// ---------------------------------------------------------------------------------------------
struct IQueryable {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void* QueryInterface(uint32_t iid);        // +0x0c
};

struct IKeyHolderSlots : VPad<38, IEmpty> {             // object holding an (id, group, name) key
    virtual int* GetKey();                             // +0x98
};
struct IKeyName : VPad<29, IEmpty> {                    // object returning its localized name
    virtual const wchar_t* GetUiName();                 // +0x74
};

class cSpeciesProfile {
public:
    uint8_t pad000[0x504];
    tUiKey  mBanKey;                                   // +0x504
    void    GetUiName(WString* pOut);                  // 0x004da330
};

class cSPCreatureBase : public IQueryable {
public:
    cSpeciesProfile* GetSpeciesProfile();               // 0x00c0bbd0
};

// an object whose sub-object at +0x34 answers GetKey/+0x98 style queries
struct cKeyRefObject {
    uint8_t      pad00[0x34];
    IKeyHolderSlots mKeyHolder;                        // +0x34
};

// object exposing a localized name at +0xcc8
struct cNamedObjectA {
    uint8_t   pad00[0x34];
    IKeyHolderSlots mKeyHolder;                        // +0x34
    uint8_t   padcc[0xcc8 - 0xcc];
    wchar_t*  mpName;                                  // +0xcc8
};

// player inventory exposing the key at +0x780 and a name at +0x7e0
struct cPlayerInventory {
    uint8_t   pad00[0x780];
    tUiKey    mKey;                                    // +0x780
    uint8_t   pad78c[0x7e0 - 0x78c];
    wchar_t*  mpName;                                  // +0x7e0
};

struct cSpaceGameAnchor {
    uint8_t pad00[0x34];
    IKeyHolderSlots mKeyHolder;                        // +0x34
};

class cSPSimulatorSpaceGame {
public:
    cPlayerInventory* GetPlayerInventory();            // 0x00...
};

// ---------------------------------------------------------------------------------------------
// modals
// ---------------------------------------------------------------------------------------------
bool __cdecl CalloutMessageBox(void* pOwner, const tUiKey* pKey);   // 0x00809db0
class cDirectPropertyList {
public:
    bool GetDescription(uint32_t id);                  // 0x006a25a0
};
extern cDirectPropertyList* gAppProperties;             // 0x015fd918

struct cUIPropertyList {                                // 0x18 bytes, built on the stack
    uint32_t mPropertyId;                              // +0x00
    uint8_t  pad04[0x14];
};
void __fastcall FUN_00644b10(cUIPropertyList* pList);   // ctor
void __fastcall FUN_00644b60(cUIPropertyList* pList);   // dtor
void __cdecl    FUN_0064a990(cUIPropertyList* pList);   // submit

// ---------------------------------------------------------------------------------------------
// audio
// ---------------------------------------------------------------------------------------------
struct IAudioSystem {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void SetFloatProperty(uint32_t id);        // +0x38
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void SetFloatProperty2(uint32_t id, float v);  // +0x40
};
struct IAudioSystemVtbl {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34();
    virtual void SetFloatProperty(uint32_t id);        // +0x38
    virtual void a3c();
    virtual void SetProperty(uint32_t id, uint32_t v); // +0x40
    virtual void a44(); virtual void a48(); virtual void a4c(); virtual void a50(); virtual void a54();
    virtual void StartStream();                        // +0x58
};
IAudioSystemVtbl* __cdecl GetAudioSystemAT();           // 0x00a206f0

// ---------------------------------------------------------------------------------------------
// globals owned by this file
// ---------------------------------------------------------------------------------------------
bool              gbBanCursorsRegistered;               // 0x015a28f8
bool              gbBanModeActive;                      // 0x015a2911
uint32_t          gBanModeState;                        // 0x015a290c
extern char       gBanModeWinProc;                      // 0x015a28e8
extern char       gBanDialogTarget;                     // 0x015a28ec
extern tUiKey     gBanDialogTitle;                      // 0x015a28e4
extern tUiKey     gBanSpaceOk;                          // 0x015a2914
extern tUiKey     gBanSpaceBanned;                      // 0x015a2920
extern tUiKey     gBanGalaxyOk;                         // 0x015a292c
extern tUiKey     gBanGalaxyBanned;                     // 0x015a2938
extern tUiKey     gBanNotAllowed;                       // 0x015a2944
extern tUiKey     gBanMaxReached;                       // 0x015a2950
extern char       gSpaceGameMode;                       // 0x01654c10

LayoutPtr         gBanLayout;
AutoRefCount<IWinX> gBanModeWindowRef;
AutoRefCount<IWinX> gBanContentWindowRef;
AutoRefCount<IWinX> gBanDialogWindowRef;                // 0x015a2908

void* __cdecl GetCurrentGameMode();                     // 0x00b5b800
class cGameTimeManager {
public:
    void IncPauseGate(uint32_t reason);                 // 0x00b32220
    void DecPauseGate(uint32_t reason);                 // 0x00b3...
};
cGameTimeManager* __cdecl GameTimeManager();            // 0x00b3d380
void* __cdecl GetPlayerEmpire();                        // 0x01021300

// ---------------------------------------------------------------------------------------------
// ban state evaluation
// ---------------------------------------------------------------------------------------------
int  __cdecl FUN_00552300(int* pKey);                   // 0x00552300
void __cdecl FUN_00401090();                            // 0x00401090
void* __cdecl FUN_004df420();                           // 0x004df420
void* __cdecl FUN_00ffbe50();                           // 0x00ffbe50
bool __cdecl FUN_00c328c0(int* pKey);                   // 0x00c328c0
void __cdecl FUN_00b3d2a0(int* pKey);                   // 0x00b3d2a0
bool __cdecl FUN_00ba9f80(int* pKey);                   // 0x00ba9f80

struct cPlayerProfile {
    uint8_t pad000[0x504];
    tUiKey  mBanKey;                                    // +0x504
};

struct cPlayerEmpire {
    uint8_t pad00[0x84];
    uint32_t mEmpireId;                                 // +0x84
};

void* __stdcall RelationshipManager(cPlayerEmpire* pA, cPlayerEmpire* pB, int c);   // 0x00b3d2c0
float __fastcall FUN_00d00a10(void* pRelationship);     // 0x00d00a10
bool __fastcall FUN_00c313c0(cPlayerEmpire* pEmpire);   // 0x00c313c0

bool __cdecl FUN_00b5ca70();                            // 0x00b5ca70

class cObjectTemplateDB {
public:
    void AddKey(tUiKey* pKey, int mode);                // +0x78
};
cObjectTemplateDB* __cdecl ObjectTemplateDB();          // 0x0067cb40

struct cTextSetter {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20();
    virtual struct cSentence* GetSomething();           // +0x20
};
struct cSentence {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30();
    virtual void AddText(const wchar_t* pText, int arg);   // +0x34
};
cTextSetter* __cdecl FUN_0067de40();                    // 0x0067de40

struct cUiString {
    uint8_t pad00[0x04];
    wchar_t* GetText();                                 // 0x006b55c0
};

void* __cdecl FUN_00bf0f40();                            // 0x00bf0f40
int   __cdecl FUN_00bef920(void* p);                     // 0x00bef920
int   __cdecl FUN_00bf1e20();                            // 0x00bf1e20

} // namespace SP

using namespace SP;

// =============================================================================================
// SP::cUIBanningContent
// =============================================================================================
namespace SP {

struct cUIBanningContent {
    bool HandleMessage(uint32_t unknown, uint32_t message);
    void Init();
    void Shutdown();
    static void SetModeWindows(bool show);
    static int  GetBannabilityState(int* pKey);
    static int* GetKey(IQueryable* pObject);
    static void ToggleBanningContent(bool playSound);
    static void EndBanMode(bool playSound);
    static bool GetBannability(IQueryable* pObject);
    static int  GetBanMode(int* pKey);
    static const wchar_t* GetName(IQueryable* pObject);
    void ShowConfirmationDialog(IQueryable* pObject);
};

// ---------------------------------------------------------------------------------------------
// @ 0xdd1280 cUIBanningContent::HandleMessage
// ---------------------------------------------------------------------------------------------
bool cUIBanningContent::HandleMessage(uint32_t message, uint32_t unknown)
{
    if (message != 0x44dae7f)
        return false;
    if (gBanModeState == 0x1510d07) {
        MessageServer()->Broadcast(0x44dae7f, 0, 0, 0);
        return true;
    }
    MessageServer()->Dispatch((void*)(-(uint32_t)(unknown != 8) & unknown), 0x44dae7f, -10000);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd12f0 cUIBanningContent::Init
// ---------------------------------------------------------------------------------------------
void cUIBanningContent::Init()
{
    if (!gbBanCursorsRegistered) {
        gbBanCursorsRegistered = true;
        CursorManager()->AddCursor(0x5ecbdffd, L"cursor-ban-mode", 1, 0, 0);
        CursorManager()->AddCursor(0xf212a38b, L"cursor-ban-content", 1, 0, 0);
    }
    if (!gBanLayout.get()) {
        cSPUILayout* pLayout;
        void* pMemory = AllocLayoutObject(0x18);
        if (pMemory)
            pLayout = ((cSPUILayout*)pMemory)->CenterWindowInRect();
        else
            pLayout = 0;
        gBanLayout = pLayout;
        if (!gBanLayout.get())
            return;
    }

    tUiKey key;
    key.mId = 0xa1b9359;
    key.mGroup = 0x510a95b;
    key.mName = 0x40464100;
    gBanLayout.get()->Init(&key, 1, 0x5f1bfc10);
    gBanLayout.get()->SetVisibility(0);

    IWinX* pModeWindow = gBanLayout.get()->FindWindowByID(0x452bd20, true);
    gBanModeWindowRef = pModeWindow;
    if (gBanModeWindowRef.get())
        gBanModeWindowRef.get()->AddWinProc(&gBanModeWinProc);

    IWinX* pContentWindow = gBanLayout.get()->FindWindowByID(0xffffffff, true);
    gBanContentWindowRef = pContentWindow;
    if (gBanContentWindowRef.get())
        gBanContentWindowRef.get()->SetFlag(0x10, true);

    IWinX* pText = gBanLayout.get()->FindWindowByID(0x452c168, true);
    if (pText)
        AutoSizeWindowForText(pText, 1, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd14b0 cUIBanningContent::Shutdown
// ---------------------------------------------------------------------------------------------
void cUIBanningContent::Shutdown()
{
    gBanModeWindowRef = 0;
    gBanContentWindowRef = 0;
    if (gBanLayout.get()) {
        gBanLayout.get()->Shutdown(1);
        if (gBanLayout.get()) {
            cSPUILayout* pOld = gBanLayout.mpObject;
            gBanLayout.mpObject = 0;
            pOld->Release();
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1520 SP::cUIBanningContent::SetModeWindows
// ---------------------------------------------------------------------------------------------
void cUIBanningContent::SetModeWindows(bool show)
{
    if (!gBanModeWindowRef.get())
        return;
    gBanModeWindowRef.get()->SetFlag(1, show);
    if (GetCurrentGameMode() != &gSpaceGameMode)
        return;
    IWinX* pPlanetName = gBanLayout.get()->FindWindowByID(0x7d8ccf0, true);
    IWinX* pHint = gBanLayout.get()->FindWindowByID(0x7d8ccc8, true);
    if (!pPlanetName || !pHint)
        return;
    pPlanetName->SetFlag(1, !show);
    pHint->SetFlag(1, show);
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd15a0 SP::cUIBanningContent::GetBannabilityState
// ---------------------------------------------------------------------------------------------
int cUIBanningContent::GetBannabilityState(int* pKey)
{
    int result = 1;
    if (pKey[0] == 0)
        return 1;

    int reason = FUN_00552300(pKey);
    if (reason != 0) {
        if (reason == 1)
            result = 2;
        else if (reason == 2)
            result = 0;
    }

    FUN_00401090();
    cPlayerProfile* pProfile = (cPlayerProfile*)FUN_004df420();
    if (pProfile && pKey[0] == (int)pProfile->mBanKey.mId &&
        pKey[1] == (int)pProfile->mBanKey.mGroup && pKey[2] == (int)pProfile->mBanKey.mName)
        result = 3;

    if (GetCurrentGameMode() == &gSpaceGameMode) {
        cSPSimulatorSpaceGame* pSpaceGame = (cSPSimulatorSpaceGame*)FUN_00ffbe50();
        cPlayerInventory* pInventory = pSpaceGame->GetPlayerInventory();
        bool bSame = pInventory->mKey.mId == (uint32_t)pKey[0] &&
                     pInventory->mKey.mGroup == (uint32_t)pKey[1] &&
                     pInventory->mKey.mName == (uint32_t)pKey[2];
        if (!bSame) {
            GetPlayerEmpire();
            if (!FUN_00c328c0(pKey))
                goto evaluate;
        }
        result = 3;
    }
evaluate:
    FUN_00b3d2a0(pKey);
    if (FUN_00ba9f80(pKey))
        return 3;
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1670 FUN_00dd1670
// ---------------------------------------------------------------------------------------------
extern char gBanObjectVtbl0[];   // 0x0147cd2c
extern char gBanObjectVtbl1[];   // 0x0147cd10
extern char gBanObjectVtbl2[];   // 0x0147cd00
extern char gBanObjectVtbl3[];   // 0x0147ccfc
extern char gBanObjectBase0[];   // 0x013ef094
extern char gBanObjectBase1[];   // 0x013eb394
extern char gBanObjectBase2[];   // 0x013eb938

struct cBanUiObject {
    void* mpVtbl0;                                     // +0x00
    void* mpVtbl1;                                     // +0x04
    void* mpVtbl2;                                     // +0x08
    void* mpVtbl3;                                     // +0x0c
    uint32_t mPad10;                                   // +0x10
    uint32_t mPad14;                                   // +0x14
    cSPUILayout* mpFirst;                              // +0x18 (Release lives at vtable +8)
    IRefCounted* mpSecond;                             // +0x1c
    IRefCounted* mpThird;                              // +0x20
    IRefCounted* mpFourth;                             // +0x24
};

// @ 0xdd1670 FUN_00dd1670
void __fastcall FUN_00dd1670(cBanUiObject* pObject)
{
    pObject->mpVtbl0 = gBanObjectVtbl0;
    pObject->mpVtbl1 = gBanObjectVtbl1;
    pObject->mpVtbl2 = gBanObjectVtbl2;
    pObject->mpVtbl3 = gBanObjectVtbl3;
    if (pObject->mpFirst) {
        pObject->mpFirst = 0;
        pObject->mpSecond = 0;
        pObject->mpThird = 0;
    }
    if (pObject->mpFourth)
        pObject->mpFourth->Release();
    if (pObject->mpThird)
        pObject->mpThird->Release();
    if (pObject->mpSecond)
        pObject->mpSecond->Release();
    if (pObject->mpFirst)
        pObject->mpFirst->Release();
    pObject->mpVtbl3 = gBanObjectBase0;

    pObject->mpVtbl2 = gBanObjectBase1;
    pObject->mpVtbl1 = gBanObjectBase2;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1730 cUIBanningContent::GetKey
// ---------------------------------------------------------------------------------------------
int* cUIBanningContent::GetKey(IQueryable* pObject)
{
    if (pObject) {
        cSPCreatureBase* pCreature = (cSPCreatureBase*)pObject->QueryInterface(0xce9f6639);
        if (pCreature) {
            cSpeciesProfile* pProfile = pCreature->GetSpeciesProfile();
            if (pProfile)
                return (int*)&pProfile->mBanKey;
        }
        cKeyRefObject* pKeyRef = (cKeyRefObject*)pObject->QueryInterface(0xe9cb8ba);
        if (pKeyRef)
            return pKeyRef->mKeyHolder.GetKey();
        cNamedObjectA* pNamed = (cNamedObjectA*)pObject->QueryInterface(0x137e8e0);
        if (pNamed)
            return pNamed->mKeyHolder.GetKey();
        cPlayerInventory* pInventory = (cPlayerInventory*)pObject->QueryInterface(0xb033b403);
        if (pInventory)
            return (int*)&pInventory->mKey;
    }
    static tNoKey sNoKey;                               // 0x016a00ac, lazily zeroed
    return (int*)&sNoKey;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd17f0 cUIBanningContent::ToggleBanningContent
// ---------------------------------------------------------------------------------------------
void cUIBanningContent::ToggleBanningContent(bool playSound)
{
    gbBanModeActive = true;
    if (playSound)
        CursorManager()->SetCursor(0x5ecbdffd);
    SetModeWindows(true);
    if (gBanContentWindowRef.get())
        gBanContentWindowRef.get()->SetFlag(1, true);
    cGameTimeManager* pGameTime = GameTimeManager();
    pGameTime->IncPauseGate(0x4bf38a7);
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1840 cUIBanningContent::EndBanMode
// ---------------------------------------------------------------------------------------------
void cUIBanningContent::EndBanMode(bool playSound)
{
    if (playSound)
        CursorManager()->SetCursor(0x1002);
    SetModeWindows(false);
    if (gBanContentWindowRef.get())
        gBanContentWindowRef.get()->SetFlag(1, false);
    cGameTimeManager* pGameTime = GameTimeManager();
    pGameTime->DecPauseGate(0x4bf38a7);
    gbBanModeActive = false;
    MessageServer()->Send(0x5d1536c, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd18b0 cUIBanningContent::GetBannability
// ---------------------------------------------------------------------------------------------
bool cUIBanningContent::GetBannability(IQueryable* pObject)
{
    return GetBannabilityState(GetKey(pObject)) == 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd18d0 cUIBanningContent::GetBanMode
// ---------------------------------------------------------------------------------------------
int cUIBanningContent::GetBanMode(int* pKey)
{
    int state = GetBannabilityState(pKey);
    if (state != 0 && state != 2)
        return 0;
    return 1;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1910 FUN_00dd1910
// ---------------------------------------------------------------------------------------------
void __stdcall FUN_00dd1910(IQueryable* pObject)
{
    int* pKey = cUIBanningContent::GetKey(pObject);
    tUiKey key;
    key.mId = (uint32_t)pKey[0];
    key.mGroup = (uint32_t)pKey[1];
    key.mName = (uint32_t)pKey[2];
    if (key.mId) {
        cObjectTemplateDB* pTemplateDB = ObjectTemplateDB();
        pTemplateDB->AddKey(&key, 1);
        if (FUN_00b5ca70()) {
            MessageServer()->Send(0x4715068, 0, 0);
            return;
        }
        MessageServer()->Send(0x452e0ca, 0, 0);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd19c0 cUIBanningContent::GetName
// ---------------------------------------------------------------------------------------------
const wchar_t* cUIBanningContent::GetName(IQueryable* pObject)
{
    if (pObject) {
        cSPCreatureBase* pCreature = (cSPCreatureBase*)pObject->QueryInterface(0xce9f6639);
        if (pCreature) {
            cSpeciesProfile* pProfile = pCreature->GetSpeciesProfile();
            if (pProfile) {
                static WString sBanName;                // 0x016a00bc, lazily constructed
                pProfile->GetUiName(&sBanName);
                return sBanName.mpBegin;
            }
        }
        IKeyName* pRef = (IKeyName*)pObject->QueryInterface(0xe9cb8ba);
        if (pRef)
            return pRef->GetUiName();
        cNamedObjectA* pNamed = (cNamedObjectA*)pObject->QueryInterface(0x137e8e0);
        if (pNamed)
            return pNamed->mpName;
        cPlayerInventory* pInventory = (cPlayerInventory*)pObject->QueryInterface(0xb033b403);
        if (pInventory)
            return pInventory->mpName;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1aa0 cUIBanningContent::ShowConfirmationDialog
// ---------------------------------------------------------------------------------------------
void cUIBanningContent::ShowConfirmationDialog(IQueryable* pObject)
{
    const wchar_t* pName = GetName(pObject);
    int* pKey = GetKey(pObject);
    if (!pName || pKey[0] == 0)
        return;

    if (gAppProperties->GetDescription(0x9e076129)) {
        cUIPropertyList list;
        FUN_00644b10(&list);
        list.mPropertyId = 0x578c04fa;
        tUiKey subKey;
        subKey.mId = (uint32_t)pKey[0];
        subKey.mGroup = (uint32_t)pKey[1];
        subKey.mName = (uint32_t)pKey[2];
        FUN_0064a990(&list);
        FUN_00644b60(&list);
        return;
    }

    FUN_0067de40()->GetSomething()->AddText(pName, 0);
    MessageServer()->SendTo(&gBanDialogTarget, 0x44dae7f);

    int state = GetBannabilityState(pKey);
    if (state == 0 || state == 2) {
        tUiKey* pMessage;
        if (GetCurrentGameMode() == &gSpaceGameMode)
            pMessage = state ? &gBanSpaceBanned : &gBanSpaceOk;
        else
            pMessage = state ? &gBanGalaxyBanned : &gBanGalaxyOk;

        if (!CalloutMessageBox(&gBanDialogTitle, pMessage))
            gBanModeState = 0x5107b19;
        gBanDialogWindowRef.mpObject = (IWinX*)pObject;
    } else {
        tUiKey* pMessage = (state == 3) ? &gBanMaxReached : &gBanNotAllowed;
        CalloutMessageBox(&gBanDialogTitle, pMessage);
        gBanModeState = 0xfffffff1;
    }
    MessageServer()->Broadcast(0x44dae7f, 0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1c50 FUN_00dd1c50
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00dd1c50(uint32_t a, uint32_t b)
{
    IAudioSystemVtbl* pAudio = GetAudioSystemAT();
    if (!pAudio)
        return;
    pAudio->SetFloatProperty(0x673a543);
    pAudio->SetProperty(0x4362049, a);
    pAudio->SetProperty(0x3475385, b);
    pAudio->StartStream();
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1ce0 FUN_00dd1ce0
// ---------------------------------------------------------------------------------------------
static tUiKey sSpaceKeys[3];                             // 0x016a011c
static tUiKey sGalaxyKeys[3];                            // 0x016a0140
static tUiKey sToolKeys[1];                              // 0x016a0164
static int32_t sKeyInitFlags;                            // 0x016a0170

tUiKey* __stdcall FUN_00dd1ce0(int mode, int variant)
{
    switch (mode) {
    case 0:
        if ((sKeyInitFlags & 1) == 0) {
            sKeyInitFlags |= 1;
            sSpaceKeys[0].mId = 0x4f2bd27;
            sSpaceKeys[0].mGroup = 0x2f7d0004;
            sSpaceKeys[0].mName = 0x354663b;
            sSpaceKeys[1].mId = 0xbf4a63b8;
            sSpaceKeys[1].mGroup = 0x2f7d0004;
            sSpaceKeys[1].mName = 0x354663b;
            sSpaceKeys[2].mId = 0x24c6341d;
            sSpaceKeys[2].mGroup = 0x2f7d0004;
            sSpaceKeys[2].mName = 0x354663b;
        }
        switch (variant) {
        case 1:
            return &sSpaceKeys[1];
        case 2:
            return &sSpaceKeys[2];
        }
        return &sSpaceKeys[0];
    case 1:
        if ((sKeyInitFlags & 2) == 0) {
            sKeyInitFlags |= 2;
            sGalaxyKeys[0].mId = 0xca3e01b3;
            sGalaxyKeys[0].mGroup = 0x2f7d0004;
            sGalaxyKeys[0].mName = 0x354663b;
            sGalaxyKeys[1].mId = 0x29dab11f;
            sGalaxyKeys[1].mGroup = 0x2f7d0004;
            sGalaxyKeys[1].mName = 0x354663b;
            sGalaxyKeys[2].mId = 0xfd35de13;
            sGalaxyKeys[2].mGroup = 0x2f7d0004;
            sGalaxyKeys[2].mName = 0x354663b;
        }
        switch (variant) {
        case 1:
            return &sGalaxyKeys[1];
        case 2:
            return &sGalaxyKeys[2];
        }
        return &sGalaxyKeys[0];
    default:
        if ((sKeyInitFlags & 4) == 0) {
            sKeyInitFlags |= 4;
            sToolKeys[0].mId = 0x8db5cd1f;
            sToolKeys[0].mGroup = 0x2f7d0004;
            sToolKeys[0].mName = 0x354663b;
        }
        return &sToolKeys[0];
    }
}

// ---------------------------------------------------------------------------------------------
// object state that selects the ban verb text
// ---------------------------------------------------------------------------------------------
struct tBanState {
    uint8_t  pad00[0x58];
    int32_t  mState;                                    // +0x58
};

// ---------------------------------------------------------------------------------------------
// @ 0xdd1e30 FUN_00dd1e30
// ---------------------------------------------------------------------------------------------
uint32_t __stdcall FUN_00dd1e30(tBanState* pState, int unused)
{
    if (pState) {
        switch (pState->mState) {
        case 0:
        case 9:
            return 0xda1ea6be;
        case 1:
        case 10:
            return 0x640de9b4;
        case 2:
        case 11:
            return 0x276bc752;
        case 3:
        case 12:
            return 0xd405ce46;
        case 4:
        case 13:
            return 0x34362b79;
        case 5:
        case 14:
            return 0x7f672cad;
        case 6:
        case 15:
            return 0x45ae2034;
        case 7:
        case 16:
            return 0x1a45c621;
        case 8:
        case 18:
            return 0x388199a4;
        default:
            return 0xbe7dc896;
        }
    }

    int value = FUN_00bef920(FUN_00bf0f40());
    if (value == 0) {
        int sub = FUN_00bf1e20();
        if (sub == 1)
            return 0xda1ea6be;
        if (sub != 2)
            return 0x3de749f9;
        return 0xd9e246f7;
    }
    if (value != 1)
        return 0x5f1d97d7;
    int sub = FUN_00bf1e20();
    if (sub != 1) {
        if (sub != 2)
            return 0xed4fdb0d;
        return 0x34362b79;
    }
    return 0x7f672cad;
}

// ---------------------------------------------------------------------------------------------
// @ 0xdd1f70 FUN_00dd1f70
// ---------------------------------------------------------------------------------------------
void __stdcall FUN_00dd1f70(tUiKey* pOut, tBanState* pState)
{
    if (pState) {
        switch (pState->mState) {
        case 0:
        case 9:
            pOut->mName = 0;
            pOut->mId = 0xf0329031;
            pOut->mGroup = 0xb1b104;
            return;
        case 1:
        case 10:
            pOut->mName = 0;
            pOut->mId = 0x128b5d9;
            pOut->mGroup = 0xb1b104;
            return;
        case 2:
        case 11:
            pOut->mName = 0;
            pOut->mId = 0x210a32f5;
            pOut->mGroup = 0xb1b104;
            return;
        case 3:
        case 12:
            pOut->mName = 0;
            pOut->mId = 0x78c9bfc3;
            pOut->mGroup = 0xb1b104;
            return;
        case 4:
        case 13:
            pOut->mName = 0;
            pOut->mId = 0xcea2087c;
            pOut->mGroup = 0xb1b104;
            return;
        case 5:
        case 14:
            pOut->mName = 0;
            pOut->mId = 0xd7768f78;
            pOut->mGroup = 0xb1b104;
            return;
        case 6:
        case 15:
            pOut->mName = 0;
            pOut->mId = 0xfbd4828b;
            pOut->mGroup = 0xb1b104;
            return;
        case 7:
        case 16:
            pOut->mName = 0;
            pOut->mId = 0x9a1d6482;
            pOut->mGroup = 0xb1b104;
            return;
        case 8:
            pOut->mName = 0;
            pOut->mId = 0xba12eed9;
            pOut->mGroup = 0xb1b104;
            return;
        case 18:
            pOut->mName = 0;
            pOut->mId = 0x83d35c0e;
            pOut->mGroup = 0xb1b104;
            return;
        default:
            pOut->mName = 0;
            pOut->mId = 0xea286137;
            pOut->mGroup = 0xb1b104;
            return;
        }
    }

    int value = FUN_00bef920(FUN_00bf0f40());
    if (value == 0) {
        int sub = FUN_00bf1e20();
        if (sub == 1) {
            pOut->mName = 0;
            pOut->mId = 0xf0329031;
            pOut->mGroup = 0xb1b104;
            return;
        }
        pOut->mGroup = 0xb1b104;
        pOut->mName = 0;
        if (sub != 2) {
            pOut->mId = 0x626123cc;
            return;
        }
        pOut->mId = 0x83d35c0e;
        return;
    }
    if (value != 1) {
        pOut->mName = 0;
        pOut->mId = 0x958c8d5e;
        pOut->mGroup = 0xb1b104;
        return;
    }
    int sub = FUN_00bf1e20();
    if (sub != 1) {
        pOut->mGroup = 0xb1b104;
        pOut->mName = 0;
        if (sub != 2) {
            pOut->mId = 0x432ef40a;
            return;
        }
        pOut->mId = 0xcea2087c;
        return;
    }
    pOut->mName = 0;
    pOut->mId = 0xd7768f78;
    pOut->mGroup = 0xb1b104;
}

// ---------------------------------------------------------------------------------------------
// ban relation text of the empire panel
// ---------------------------------------------------------------------------------------------
struct cBanRelationText {
    uint8_t  pad00[0x58];
    cUiString mNeutralText;                             // +0x58
    uint8_t  pad5c[0x6c - 0x5c];
    cUiString mHostileText;                             // +0x6c

    bool GetRelationText(cPlayerEmpire* pEmpire, const wchar_t** pOut);
};

// @ 0xdd21c0 cBanRelationText::GetRelationText
bool cBanRelationText::GetRelationText(cPlayerEmpire* pEmpire, const wchar_t** pOut)
{
    bool result = false;
    cPlayerEmpire* pPlayerEmpire = (cPlayerEmpire*)GetPlayerEmpire();
    if (!FUN_00c313c0(pEmpire)) {
        *pOut = mNeutralText.GetText();
        return result;
    }
    if (pEmpire != pPlayerEmpire) {
        void* pRelationship = RelationshipManager(pEmpire, pPlayerEmpire, 0);
        float strength = FUN_00d00a10(pRelationship);
        if (0.0f < strength) {
            *pOut = mHostileText.GetText();
            return result;
        }
    }
    return true;
}

} // namespace SP
