// src/game/SPGonzago/SPUIBanningContent.cpp -- migrated from slice(s) s00e094f0, s00dd1280, s00dd0230 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIBanningContent.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "SP/cCity.h"
#include "SP/cCombatant.h"
#include "SP/cMilitaryAttackCityOrder.h"
#include "SP/cSpatialObject.h"
#include "SP/cString.h"
#include "SP/cVehicle.h"
#include "SP/cVehicleGroupOrder.h"
#include <math.h>
#include <new>
#include "SP/cDirectPropertyList.h"
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"
#include "SP/cSpeciesProfile.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cGrid.h"

// ---- items of slice s00dd0230 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl GetMessageServer67dcc0();                 // 0x0067dcc0 (SP::MessageServer)
struct SomeMessage {
    char pad00[0xc];
    uint32_t mType_0c;                                  // +0x0c
};
// ---- items of slice s00dd0230 end

// ---- items of slice s00dd1280 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
}
namespace SP {
template <class B> struct VPad<0, B> : B {};
}
namespace SP {
struct IEmpty {};
}
namespace SP {
extern wchar_t gEmptyString16[];                       // 0x01667bac `?gEmptyString16@eastl@@3PA_WA`
}
namespace SP {
void __cdecl FreeArray(void* block);                   // 0x00f47380 operator delete[]
}
namespace SP {
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
}
namespace SP {
struct tUiKey {
    uint32_t mId;                                      // +0x00
    uint32_t mGroup;                                   // +0x04
    uint32_t mName;                                    // +0x08
};
}
namespace SP {
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
}
namespace SP {
struct IRefCounted {
    virtual int AddRef();                              // +0x00
    virtual int Release();                             // +0x04
};
}
namespace SP {
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
}
namespace SP {
struct IWinX {
    virtual int AddRef();                              // +0x00
    virtual int Release();                             // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetFlag(int flag, bool value);        // +0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
virtual void vf0();
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
    virtual void AddWinProc(void* pWinProc);           // +0x104
};
}
namespace SP {
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
}
namespace SP {
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
}
namespace SP {
class cCursorTable {
public:
    void AddCursor(uint32_t id, const wchar_t* pName, int a, int b, int c);   // 0x00802050
    void SetCursor(uint32_t id);                                             // 0x00801bb0
};
}
namespace SP {
cCursorTable* __cdecl CursorManager();                 // 0x0067cab0
}
namespace SP {
void* AllocLayoutObject(uint32_t size);                 // 0x006abeb0
}
namespace SP {
void AutoSizeWindowForText(IWinX* pWindow, int a, int b);   // 0x00806600
}
namespace SP {
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void Send(uint32_t message, int a, int b);                 // +0x14
    virtual void Broadcast(uint32_t message, int a, int b, int c);     // +0x18
    virtual void v1c();
    virtual void SendTo(void* target, uint32_t message);               // +0x20
virtual void v24();
virtual void v28();
    virtual void Dispatch(void* target, uint32_t message, int error);  // +0x2c
};
}
namespace SP {
IMessageServer* __cdecl MessageServer();               // 0x0067dcc0
}
namespace SP {
struct IQueryable {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void* QueryInterface(uint32_t iid);        // +0x0c
};
}
namespace SP {
struct IKeyHolderSlots : VPad<38, IEmpty> {             // object holding an (id, group, name) key
    virtual int* GetKey();                             // +0x98
};
}
namespace SP {
struct IKeyName : VPad<29, IEmpty> {                    // object returning its localized name
    virtual const wchar_t* GetUiName();                 // +0x74
};
}
namespace SP {
class cSpeciesProfile_s00dd_1280 {
public:
    uint8_t pad000[0x504];
    tUiKey  mBanKey;                                   // +0x504
    void    GetUiName(WString* pOut);                  // 0x004da330
};
}
namespace SP {
class cSPCreatureBase_s00dd_1280 : public IQueryable {
public:
    cSpeciesProfile_s00dd_1280* GetSpeciesProfile();               // 0x00c0bbd0
};
}
namespace SP {
struct cKeyRefObject {
    uint8_t      pad00[0x34];
    IKeyHolderSlots mKeyHolder;                        // +0x34
};
}
namespace SP {
struct cNamedObjectA {
    uint8_t   pad00[0x34];
    IKeyHolderSlots mKeyHolder;                        // +0x34
    uint8_t   padcc[0xcc8 - 0xcc];
    wchar_t*  mpName;                                  // +0xcc8
};
}
namespace SP {
struct cPlayerInventory {
    uint8_t   pad00[0x780];
    tUiKey    mKey;                                    // +0x780
    uint8_t   pad78c[0x7e0 - 0x78c];
    wchar_t*  mpName;                                  // +0x7e0
};
}
namespace SP {
class cSPSimulatorSpaceGame {
public:
    cPlayerInventory* GetPlayerInventory();            // 0x00...
};
}
namespace SP {
bool __cdecl CalloutMessageBox(void* pOwner, const tUiKey* pKey);   // 0x00809db0
}
namespace SP {
class cDirectPropertyList_s00dd_1280 {
public:
    bool GetDescription(uint32_t id);                  // 0x006a25a0
};
}
namespace SP {
extern cDirectPropertyList_s00dd_1280* gAppProperties;             // 0x015fd918
}
namespace SP {
struct cUIPropertyList {                                // 0x18 bytes, built on the stack
    uint32_t mPropertyId;                              // +0x00
    uint8_t  pad04[0x14];
};
}
namespace SP {
void __fastcall FUN_00644b10(cUIPropertyList* pList);   // ctor
}
namespace SP {
void __fastcall FUN_00644b60(cUIPropertyList* pList);   // dtor
}
namespace SP {
void __cdecl    FUN_0064a990(cUIPropertyList* pList);   // submit
}
namespace SP {
bool              gbBanCursorsRegistered;               // 0x015a28f8
}
namespace SP {
bool              gbBanModeActive;                      // 0x015a2911
}
namespace SP {
uint32_t          gBanModeState;                        // 0x015a290c
}
namespace SP {
extern char       gBanModeWinProc;                      // 0x015a28e8
}
namespace SP {
extern char       gBanDialogTarget;                     // 0x015a28ec
}
namespace SP {
extern tUiKey     gBanDialogTitle;                      // 0x015a28e4
}
namespace SP {
extern tUiKey     gBanSpaceOk;                          // 0x015a2914
}
namespace SP {
extern tUiKey     gBanSpaceBanned;                      // 0x015a2920
}
namespace SP {
extern tUiKey     gBanGalaxyOk;                         // 0x015a292c
}
namespace SP {
extern tUiKey     gBanGalaxyBanned;                     // 0x015a2938
}
namespace SP {
extern tUiKey     gBanNotAllowed;                       // 0x015a2944
}
namespace SP {
extern tUiKey     gBanMaxReached;                       // 0x015a2950
}
namespace SP {
extern char       gSpaceGameMode;                       // 0x01654c10
}
namespace SP {
LayoutPtr         gBanLayout;
}
namespace SP {
AutoRefCount<IWinX> gBanModeWindowRef;
}
namespace SP {
AutoRefCount<IWinX> gBanContentWindowRef;
}
namespace SP {
AutoRefCount<IWinX> gBanDialogWindowRef;                // 0x015a2908
}
namespace SP {
void* __cdecl GetCurrentGameMode();                     // 0x00b5b800
}
namespace SP {
class cGameTimeManager {
public:
    void IncPauseGate(uint32_t reason);                 // 0x00b32220
    void DecPauseGate(uint32_t reason);                 // 0x00b3...
};
}
namespace SP {
cGameTimeManager* __cdecl GameTimeManager();            // 0x00b3d380
}
namespace SP {
void* __cdecl GetPlayerEmpire();                        // 0x01021300
}
namespace SP {
int  __cdecl FUN_00552300(int* pKey);                   // 0x00552300
}
namespace SP {
void __cdecl FUN_00401090();                            // 0x00401090
}
namespace SP {
void* __cdecl FUN_004df420();                           // 0x004df420
}
namespace SP {
void* __cdecl FUN_00ffbe50();                           // 0x00ffbe50
}
namespace SP {
bool __cdecl FUN_00c328c0(int* pKey);                   // 0x00c328c0
}
namespace SP {
void __cdecl FUN_00b3d2a0(int* pKey);                   // 0x00b3d2a0
}
namespace SP {
bool __cdecl FUN_00ba9f80(int* pKey);                   // 0x00ba9f80
}
namespace SP {
struct cPlayerProfile {
    uint8_t pad000[0x504];
    tUiKey  mBanKey;                                    // +0x504
};
}
namespace SP {
bool __cdecl FUN_00b5ca70();                            // 0x00b5ca70
}
namespace SP {
class cObjectTemplateDB {
public:
    void AddKey(tUiKey* pKey, int mode);                // +0x78
};
}
namespace SP {
cObjectTemplateDB* __cdecl ObjectTemplateDB();          // 0x0067cb40
}
namespace SP {
struct cTextSetter {
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
    virtual void t20();
    virtual struct cSentence* GetSomething();           // +0x20
};
}
namespace SP {
struct cSentence {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
    virtual void s30();
    virtual void AddText(const wchar_t* pText, int arg);   // +0x34
};
}
namespace SP {
cTextSetter* __cdecl FUN_0067de40();                    // 0x0067de40
}
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
}
namespace SP {
extern char gBanObjectVtbl0[];   // 0x0147cd2c
}
namespace SP {
extern char gBanObjectVtbl1[];   // 0x0147cd10
}
namespace SP {
extern char gBanObjectVtbl2[];   // 0x0147cd00
}
namespace SP {
extern char gBanObjectVtbl3[];   // 0x0147ccfc
}
namespace SP {
extern char gBanObjectBase0[];   // 0x013ef094
}
namespace SP {
extern char gBanObjectBase1[];   // 0x013eb394
}
namespace SP {
extern char gBanObjectBase2[];   // 0x013eb938
}
namespace SP {
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
}
// ---- items of slice s00dd1280 end

// ---- items of slice s00e094f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool         g_bSpyglassCursors;                      // 0x015a4bbc
extern bool         g_bSpyglassActive;                       // 0x015a4bd5
extern uint32_t     g_SpyglassMode;                          // 0x015a4bd0
extern uint32_t     g_SpyglassTextTarget;                    // 0x015a4bac
#define PV(n) virtual void pv##n();
namespace SP {
    void* GameTimeManager_s00e0_94f0();                                // 0x00b3d380
}
namespace SP {
    void* App();                                            // 0x0067dd10
}
void* __cdecl FUN_0067cab0();                               // 0x0067cab0  cursor table singleton
void* __cdecl FUN_006abeb0(uint32_t size);                   // 0x006abeb0  operator new
void* __cdecl FUN_00bcc330();                                // 0x00bcc330  (callers pass this in ecx)
void  __cdecl FUN_00806e40(void* window, int32_t a, int32_t b); // 0x00806e40 AutoSizeWindowForText
struct cAssetLaunchParams;
void  __cdecl FUN_0064a990(cAssetLaunchParams* params);      // 0x0064a990
struct cSPUIWindow;
struct cSPUILayout_s00e0_94f0;
extern cSPUILayout_s00e0_94f0* g_pSpyglassLayout;                       // 0x015a4bc0
extern cSPUIWindow* g_pSpyglassTopWindow;                    // 0x015a4bc4
extern cSPUIWindow* g_pSpyglassTextWindow;                   // 0x015a4bc8
struct cRefObject {                                          // refcounted object, release at +0x04
    PV(0)
    virtual void Release();                                  // +0x04
};
struct cRefObject2 {                                         // refcounted object, addref +0x04/release +0x08
    PV(0)
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
};
struct cResourceKey {                                        // EA::ResourceMan::Key
    uint32_t mId;                                            // +0x00
    uint32_t mType;                                          // +0x04
    uint32_t mGroup;                                         // +0x08
};
struct cSPUIWindow {
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
    virtual void v31(int32_t value, int32_t animate);         // +0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51)
    PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
    PV(62) PV(63) PV(64)
    virtual void v65(void* target);                          // +0x104
};
struct cSPUILayout_s00e0_94f0 {
    PV(0)
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
    bool Init(const cResourceKey& key, bool b, uint32_t value);   // 0x008120d0
    void SetVisibility(int32_t visible);                     // 0x00810590
    cSPUIWindow* FindWindowByID(uint32_t id, bool searchChildren); // 0x008105b0
    void Shutdown(uint32_t mode);                            // 0x00811ad0
    void* FUN_00810000();                                    // 0x00810000  ctor, returns this
};
struct CursorTable {
    uint32_t AddCursor(uint32_t id, const wchar_t* name, int32_t a, int32_t b, int32_t c); // 0x00802050
    bool FindLocal(uint32_t id);                             // 0x00801bb0
};
struct cAppObject {                                          // SP::App() result
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13)
    virtual void* v14();                                      // +0x38
};
struct MessageServer_s00e0_94f0 {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void v5(uint32_t id, void* a, void* b);           // +0x14
    virtual void v6(uint32_t id, void* a, void* b, void* c);  // +0x18
    PV(7) PV(8) PV(9) PV(10)
    virtual void v11(void* value, uint32_t id, int32_t code); // +0x2c
};
struct MessageServer_s00e0_94f0* GetMessageServer();                    // 0x0067dcc0
struct cGameTimeManager_s00e0_94f0 {
    void IncPauseGate(uint32_t gate);                         // 0x00b32220
    void DecPauseGate(uint32_t gate);                         // 0x00b32250
};
struct cGameObject {                                          // the caller's object (slot +0x0c query)
    PV(0) PV(1) PV(2)
    virtual void* v3(uint32_t kind);                          // +0x0c
};
struct cSPCreatureBase_s00e0_94f0 {
    void* GetSpeciesProfile();                                // 0x00c0bbd0
};
struct cCreatureOrWhatever {                                  // second kind queried by 0x00e09910
    void* FUN_00bcc330();                                     // 0x00bcc330 (thiscall, returns pointer)
};
struct cThirdKindBase {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual void* v38();                                      // +0x98
};
struct cStaticOwner {                                         // 12-byte function-local static in 0x00e09910
    void* mField00;                                           // +0x00
    void* mField04;                                           // +0x04
    void* mField08;                                           // +0x08
    cStaticOwner() : mField00(0), mField04(0), mField08(0) {}
};
struct cAssetLaunchParams {                                   // 0x48-byte launch descriptor
    uint32_t mId;                                             // +0x00
    void*    mApp;                                            // +0x04
    uint8_t  mPad08[0x0b];                                    // +0x08
    uint8_t  mFlag13;                                         // +0x13
    uint32_t mPad14;                                          // +0x14
    void*    mOwner0;                                         // +0x18
    void*    mOwner1;                                         // +0x1c
    void*    mOwner2;                                         // +0x20
    uint8_t  mFlag24;                                         // +0x24
    uint8_t  mPad25[0x23];                                    // +0x25
    void Construct();                                         // 0x00644b10
    void Destroy();                                           // 0x00644b60
};
template <class T>
inline void AssignRef(T*& dst, T* src)
{
    if (src != dst) {
        T* old = dst;
        if (src != 0) {
            src->AddRef();
        }
        dst = src;
        if (old != 0) {
            old->Release();
        }
    }
}
struct cSpyglassMsgFilter {
    uint32_t mPad00;
    uint32_t mPad04;
    uint32_t mPad08;
    uint32_t mType;                                           // +0x0c
};
struct cFourBaseObject {
    void* mField00;                                           // +0x00
    void* mField04;                                           // +0x04
    void* mField08;                                           // +0x08
    void* mField0C;                                           // +0x0c
    uint32_t mPad10[2];                                       // +0x10
    void* mField18;                                           // +0x18
    void* mField1C;                                           // +0x1c
    void* mField20;                                           // +0x20
    void* mField24;                                           // +0x24
    void Destroy();                                           // 0x00e09830
};
// ---- items of slice s00e094f0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
const wchar_t* __cdecl FUN_00e09b10(cGameObject* obj);  // 0x00e09b10 (stays in the slice: not this object's)

// @ 0x00dd1250
bool __stdcall SomeObj_DoMessage(void* pUnused, SomeMessage* pMsg)
{
    (void)pUnused;
    if (pMsg->mType_0c != 0x452c168u)
        return false;
    void* pServer = GetMessageServer67dcc0();
    ((void(__thiscall*)(void*, uint32_t, int, int))((void**)*(void**)pServer)[5])(pServer, 0x452e0cau, 0, 0);
    return true;
}

// @ 0x00dd1280
namespace SP {
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
}  // namespace SP

// @ 0x00dd12f0
namespace SP {
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
}  // namespace SP

// @ 0x00dd14b0
namespace SP {
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
}  // namespace SP

// @ 0x00dd1520
namespace SP {
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
}  // namespace SP

// @ 0x00dd15a0
namespace SP {
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
}  // namespace SP

// @ 0x00dd1670
namespace SP {
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
}  // namespace SP

// @ 0x00dd1730
namespace SP {
int* cUIBanningContent::GetKey(IQueryable* pObject)
{
    if (pObject) {
        cSPCreatureBase_s00dd_1280* pCreature = (cSPCreatureBase_s00dd_1280*)pObject->QueryInterface(0xce9f6639);
        if (pCreature) {
            cSpeciesProfile_s00dd_1280* pProfile = pCreature->GetSpeciesProfile();
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
}  // namespace SP

// @ 0x00dd17f0
namespace SP {
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
}  // namespace SP

// @ 0x00dd1840
namespace SP {
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
}  // namespace SP

// @ 0x00dd18b0
namespace SP {
bool cUIBanningContent::GetBannability(IQueryable* pObject)
{
    return GetBannabilityState(GetKey(pObject)) == 0;
}
}  // namespace SP

// @ 0x00dd18d0
namespace SP {
int cUIBanningContent::GetBanMode(int* pKey)
{
    int state = GetBannabilityState(pKey);
    if (state != 0 && state != 2)
        return 0;
    return 1;
}
}  // namespace SP

// @ 0x00dd1910
namespace SP {
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
}  // namespace SP

// @ 0x00dd19c0
namespace SP {
const wchar_t* cUIBanningContent::GetName(IQueryable* pObject)
{
    if (pObject) {
        cSPCreatureBase_s00dd_1280* pCreature = (cSPCreatureBase_s00dd_1280*)pObject->QueryInterface(0xce9f6639);
        if (pCreature) {
            cSpeciesProfile_s00dd_1280* pProfile = pCreature->GetSpeciesProfile();
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
}  // namespace SP

// @ 0x00dd1aa0
namespace SP {
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
}  // namespace SP

// @ 0x00e09560
bool __stdcall FUN_00e09560(void* unused, cSpyglassMsgFilter* msg)
{
    if (msg->mType != 0x452c168) {
        return false;
    }
    GetMessageServer()->v5(0x0620271c, 0, 0);
    return true;
}

// @ 0x00e09590
bool __fastcall FUN_00e09590(void* modeValue, void* unused, uint32_t msgType, int32_t code)
{
    if (msgType == 0x044dae7f) {
        if (g_SpyglassMode == 0x01510d07) {
            GetMessageServer()->v6(0x044dae7f, 0, 0, 0);
            return true;
        }
        GetMessageServer()->v11(modeValue == (void*)8 ? modeValue : 0, 0x044dae7f, 0xffffd8f1);
        return true;
    }
    return false;
}

// @ 0x00e09600
void __cdecl FUN_00e09600()
{
    if (!g_bSpyglassCursors) {
        g_bSpyglassCursors = true;
        ((CursorTable*)FUN_0067cab0())->AddCursor(0x5ecbdffd, L"cursor-ban-mode", 1, 0, 0);
        ((CursorTable*)FUN_0067cab0())->AddCursor(0xf6879190, L"cursor_spyglass", 1, 0, 0);
    }
    if (g_pSpyglassLayout == 0) {
        void* mem = FUN_006abeb0(0x18);
        cSPUILayout_s00e0_94f0* created = (mem != 0)
                                   ? (cSPUILayout_s00e0_94f0*)((cSPUILayout_s00e0_94f0*)mem)->FUN_00810000()
                                   : 0;
        AssignRef(g_pSpyglassLayout, created);
        if (g_pSpyglassLayout == 0) {
            return;
        }
    }
    cResourceKey key;
    key.mId = 0x7edb17fd;
    key.mType = 0x0510a95b;
    key.mGroup = 0x40464100;
    g_pSpyglassLayout->Init(key, true, 0x5f1bfc10);
    g_pSpyglassLayout->SetVisibility(0);

    cSPUIWindow* top = g_pSpyglassLayout->FindWindowByID(0x0452bd20, true);
    AssignRef(g_pSpyglassTopWindow, top);
    if (g_pSpyglassTopWindow != 0) {
        g_pSpyglassTopWindow->v65(&g_SpyglassTextTarget);
    }

    cSPUIWindow* text = g_pSpyglassLayout->FindWindowByID(0xffffffff, true);
    AssignRef(g_pSpyglassTextWindow, text);
    if (g_pSpyglassTextWindow != 0) {
        g_pSpyglassTextWindow->v31(0x10, 1);
    }

    cSPUIWindow* label = g_pSpyglassLayout->FindWindowByID(0x0452c168, true);
    if (label != 0) {
        FUN_00806e40(label, 1, 0);
    }
}

// @ 0x00e097c0
void __cdecl FUN_00e097c0()
{
    cSPUIWindow* top = g_pSpyglassTopWindow;
    if (top != 0) {
        g_pSpyglassTopWindow = 0;
        top->Release();
    }
    cSPUIWindow* text = g_pSpyglassTextWindow;
    if (text != 0) {
        g_pSpyglassTextWindow = 0;
        text->Release();
    }
    if (g_pSpyglassLayout != 0) {
        g_pSpyglassLayout->Shutdown(1);
        if (g_pSpyglassLayout != 0) {
            cSPUILayout_s00e0_94f0* layout = g_pSpyglassLayout;
            g_pSpyglassLayout = 0;
            layout->Release();
        }
    }
}

// @ 0x00e09830
void cFourBaseObject::Destroy()
{
    mField00 = (void*)0x0147f5f4;
    mField04 = (void*)0x0147f5d8;
    mField08 = (void*)0x0147f5c8;
    mField0C = (void*)0x0147f5c4;
    if (mField18 != 0) {
        mField18 = 0;
        mField1C = 0;
        mField20 = 0;
    }
    if (mField24 != 0) {
        ((cRefObject*)mField24)->Release();
    }
    if (mField20 != 0) {
        ((cRefObject*)mField20)->Release();
    }
    if (mField1C != 0) {
        ((cRefObject*)mField1C)->Release();
    }
    if (mField18 != 0) {
        ((cRefObject2*)mField18)->Release();
    }
    mField0C = (void*)0x013ef094;
    mField08 = (void*)0x013eb394;
    mField04 = (void*)0x013eb938;
}

// @ 0x00e09910
cStaticOwner* __cdecl FUN_00e09910(cGameObject* obj)
{
    if (obj != 0) {
        void* creature = obj->v3(0xce9f6639);
        if (creature != 0) {
            void* profile = ((cSPCreatureBase_s00e0_94f0*)creature)->GetSpeciesProfile();
            if (profile != 0) {
                return (cStaticOwner*)((char*)profile + 0x504);
            }
        }
        void* plain = obj->v3(0xe9cb8ba);
        if (plain != 0) {
            return (cStaticOwner*)((cCreatureOrWhatever*)plain)->FUN_00bcc330();
        }
        void* third = obj->v3(0x137e8e0);
        if (third != 0) {
            return (cStaticOwner*)((cThirdKindBase*)((char*)third + 0x34))->v38();
        }
        void* fourth = obj->v3(0xb033b403);
        if (fourth != 0) {
            return (cStaticOwner*)((char*)fourth + 0x780);
        }
    }
    static cStaticOwner s_Default;
    return &s_Default;
}

// @ 0x00e099d0
void __cdecl FUN_00e099d0(int8_t refreshCursor)
{
    g_bSpyglassActive = true;
    if (refreshCursor != 0) {
        ((CursorTable*)FUN_0067cab0())->FindLocal(0x5ecbdffd);
    }
    if (g_pSpyglassTopWindow != 0) {
        g_pSpyglassTopWindow->v31(1, 1);
    }
    if (g_pSpyglassTextWindow != 0) {
        g_pSpyglassTextWindow->v31(1, 1);
    }
    cGameTimeManager_s00e0_94f0* timeManager = (cGameTimeManager_s00e0_94f0*)SP::GameTimeManager_s00e0_94f0();
    timeManager->IncPauseGate(0x04bf38a7);
    GetMessageServer()->v5(0x0691a1c3, 0, 0);
}

// @ 0x00e09a50
void __cdecl FUN_00e09a50(int8_t refreshCursor)
{
    if (refreshCursor != 0) {
        ((CursorTable*)FUN_0067cab0())->FindLocal(0x1002);
    }
    if (g_pSpyglassTopWindow != 0) {
        g_pSpyglassTopWindow->v31(1, 0);
    }
    if (g_pSpyglassTextWindow != 0) {
        g_pSpyglassTextWindow->v31(1, 0);
    }
    cGameTimeManager_s00e0_94f0* timeManager = (cGameTimeManager_s00e0_94f0*)SP::GameTimeManager_s00e0_94f0();
    timeManager->DecPauseGate(0x04bf38a7);
    g_bSpyglassActive = false;
    GetMessageServer()->v5(0x06202731, 0, 0);
}

// @ 0x00e09ad0
bool __cdecl FUN_00e09ad0(cGameObject* obj)
{
    cStaticOwner* owner = FUN_00e09910(obj);
    return owner->mField00 != 0;
}

// @ 0x00e09bf0
void __cdecl FUN_00e09bf0(cGameObject* obj)
{
    const wchar_t* name = FUN_00e09b10(obj);
    cStaticOwner* owner = FUN_00e09910(obj);
    if (name != 0 && owner->mField00 != 0) {
        cAssetLaunchParams params;
        params.Construct();
        void* app = ((cAppObject*)SP::App())->v14();
        params.mOwner0 = owner->mField00;
        params.mApp = app;
        params.mId = 0x578c04fa;
        params.mOwner1 = owner->mField04;
        params.mOwner2 = owner->mField08;
        params.mFlag24 = 1;
        params.mFlag13 = 0;
        FUN_0064a990(&params);
        params.Destroy();
    }
}
