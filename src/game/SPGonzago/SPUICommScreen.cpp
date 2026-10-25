// src/game/SPGonzago/SPUICommScreen.cpp -- migrated from slice(s) s00dd30d0, s00dd2240, s00dd1280 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUICommScreen.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocation.h"
#include "SP/cRelationshipManager.h"
#include "SP/cStarManager.h"
#include "SP/cString.h"
#include "SP/cCity.h"
#include <intrin.h>   // _ReadWriteBarrier (scheduling barrier, emits no code)
#pragma warning(disable : 4100)

// ---- items of slice s00dd1280 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct tUiKey {
    uint32_t mId;                                      // +0x00
    uint32_t mGroup;                                   // +0x04
    uint32_t mName;                                    // +0x08
};
}
namespace SP {
void* __cdecl GetPlayerEmpire();                        // 0x01021300
}
namespace SP {
struct cPlayerEmpire {
    uint8_t pad00[0x84];
    uint32_t mEmpireId;                                 // +0x84
};
}
namespace SP {
void* __stdcall RelationshipManager(cPlayerEmpire* pA, cPlayerEmpire* pB, int c);   // 0x00b3d2c0
}
namespace SP {
float __fastcall FUN_00d00a10(void* pRelationship);     // 0x00d00a10
}
namespace SP {
bool __fastcall FUN_00c313c0(cPlayerEmpire* pEmpire);   // 0x00c313c0
}
namespace SP {
struct cUiString {
    uint8_t pad00[0x04];
    wchar_t* GetText();                                 // 0x006b55c0
};
}
namespace SP {
void* __cdecl FUN_00bf0f40();                            // 0x00bf0f40
}
namespace SP {
int   __cdecl FUN_00bef920(void* p);                     // 0x00bef920
}
namespace SP {
int   __cdecl FUN_00bf1e20();                            // 0x00bf1e20
}
namespace SP {
static tUiKey sSpaceKeys[3];                             // 0x016a011c
}
namespace SP {
static tUiKey sGalaxyKeys[3];                            // 0x016a0140
}
namespace SP {
static tUiKey sToolKeys[1];                              // 0x016a0164
}
namespace SP {
static int32_t sKeyInitFlags;                            // 0x016a0170
}
namespace SP {
struct tBanState {
    uint8_t  pad00[0x58];
    int32_t  mState;                                    // +0x58
};
}
namespace SP {
struct cBanRelationText {
    uint8_t  pad00[0x58];
    cUiString mNeutralText;                             // +0x58
    uint8_t  pad5c[0x6c - 0x5c];
    cUiString mHostileText;                             // +0x6c

    bool GetRelationText(cPlayerEmpire* pEmpire, const wchar_t** pOut);
};
}
// ---- items of slice s00dd1280 end

// ---- items of slice s00dd2240 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kClampMax;                                    // 0x013ec4d0
extern uint8_t     kGameModeA;                                   // 0x01654c04
extern uint8_t     kGameModeB;                                   // 0x01654c05
extern uint32_t    gAnimFlags;                                   // 0x016a025c
extern char*       gAnimBase;                                    // 0x01440aec
extern float       kAudioPos[3];                                 // 0x016a0260
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
struct SList { SList* mpNext; };
namespace SP {
class IWin {
 public:
    virtual void  AddRef();                                  // +0x00
    virtual void  Release();                                 // +0x04
    virtual void  pv02();                                    // +0x08
    virtual void* pv03(int id);                              // +0x0c
    virtual void* pv04();                                    // +0x10
    virtual void  pv05();                                    // +0x14
    virtual void  pv06();                                    // +0x18
    virtual void  pv07(int a);                               // +0x1c
    virtual void  pv08();                                    // +0x20
    virtual void  pv09(void* p);                             // +0x24
    virtual void  pv10();                                    // +0x28
    virtual char  pv11(int id, int a, void* out);            // +0x2c
    virtual void  pv12(void* p);                             // +0x30
    virtual void* pv13();                                    // +0x34
    virtual void  pv14();                                    // +0x38
    virtual void  pv15();                                    // +0x3c
    virtual void  pv16();                                    // +0x40
    virtual void  pv17();                                    // +0x44
    virtual void  pv18();                                    // +0x48
    virtual void  pv19();                                    // +0x4c
    virtual void  pv20();                                    // +0x50
    virtual void  pv21();                                    // +0x54
    virtual void  pv22();                                    // +0x58
    virtual void  pv23();                                    // +0x5c
    virtual void  pv24(void* p);                             // +0x60
    virtual void  pv25(float a, float b);                    // +0x64
    virtual void  pv26();                                    // +0x68
    virtual void  pv27();                                    // +0x6c
    virtual void  pv28();                                    // +0x70
    virtual void  pv29();                                    // +0x74
    virtual void  pv30();                                    // +0x78
    virtual void  pv31(int a, int b);                        // +0x7c
    virtual void  pv32(void* a);                             // +0x80
    virtual void  pv33();                                    // +0x84
    virtual void  pv34();                                    // +0x88
    virtual void  pv35();                                    // +0x8c
    virtual void  pv36();                                    // +0x90
    virtual void  pv37();                                    // +0x94
    virtual void  pv38();                                    // +0x98
    virtual void  pv39();                                    // +0x9c
    virtual void  pv40();                                    // +0xa0
    virtual void  pv41();                                    // +0xa4
    virtual void  pv42();                                    // +0xa8
    virtual void  pv43();                                    // +0xac
    virtual void  pv44();                                    // +0xb0
    virtual void  pv45();                                    // +0xb4
    virtual void  pv46();                                    // +0xb8
    virtual void  pv47();                                    // +0xbc
    virtual void  pv48();                                    // +0xc0
    virtual void  pv49();                                    // +0xc4
    virtual void  pv50();                                    // +0xc8
    virtual void* pv51(void* p);                             // +0xcc
    virtual void  pv52(void* p);                             // +0xd0
    virtual void  pv53();                                    // +0xd4
    virtual void  pv54();                                    // +0xd8
    virtual void  pv55();                                    // +0xdc
    virtual void  pv56();                                    // +0xe0
    virtual void  pv57();                                    // +0xe4
    virtual void  pv58(void* p);                             // +0xe8
};
}
namespace SP {
class IEffectWin {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    virtual void SetVisible(int a);                          // +0x08
};
}
namespace SP {
class IEffectNode {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Apply(float t);                             // +0x04
};
}
namespace SP {
class cSPUILayout {
 public:
    IWin* FindWindowByID(int id, int flags);                 // 0x008105b0
    bool  SetParentWin(IWin* win, bool b, int id);           // 0x008121b0
};
}
namespace SP {
class cSPUIGlobalUI {
 public:
    void* FindWindowByID(int id);                            // 0x00e012b0
};
}
namespace SP {
class cUIHints {
 public:
    int   SetFlag(int a, int b);                             // 0x0067c420
};
}
namespace SP {
class cDatabasePackedFile {
 public:
    void* GetLocation();                                     // 0x00a42730
};
}
namespace SP {
class cLocation_s00dd_2240 {
 public:
    uint8_t pad00[0x0c];
    int     mKind_0c;                                        // +0x0c
    void*   FUN_006c0200();                                  // 0x006c0200
};
}
namespace SP {
class cEmpire_s00dd_2240 {
 public:
    void* GetHomePlanet();                                   // 0x00c31730
    int   FUN_00c30cb0();                                    // 0x00c30cb0
    uint8_t pad00[0x84];
    void*   mp_84;                                           // +0x84
};
}
namespace SP {
class cStarManager_s00dd_2240 {
 public:
    int   GetEmpireByID(void* id);                           // 0x00ba9370
    void* FUN_00885c90();                                    // 0x00885c90
    void* FUN_00bce4c0();                                    // 0x00bce4c0
};
}
namespace SP {
class cRelationshipManager_s00dd_2240 {
 public:
    char  FUN_00d01b50(void* a, void* b);                    // 0x00d01b50
    void* FUN_00d00a70(void* a, void* b, int c);             // 0x00d00a70
};
}
namespace SP {
class cGameNounManager_s00dd_2240 {
 public:
    int   GetPlayerCivilization();                           // 0x00b25fb0
    void* FUN_00b25f40();                                    // 0x00b25f40
};
}
namespace SP {
class cUFO {
 public:
    void* GetPlayerInventory();                              // 0x00a1ad60
};
}
namespace SP {
class cString_s00dd_2240 {
 public:
    const wchar_t* GetText();                                // 0x006b55c0
    uint8_t mData_00[0x14];
};
}
namespace SP {
class cInventory {
 public:
    uint8_t pad7f4[0x7f4];
    float   mValue_7f4;                                      // +0x7f4
    float   mValue_7f8;                                      // +0x7f8
};
}
namespace SP {
class cCreature {
 public:
    void* FUN_00c71e30();                                    // 0x00c71e30
    uint8_t pad84[0x84];
    void*   mp_84;                                           // +0x84
    uint8_t pad88[0x13c - 0x88];
    void*   mp_13c;                                          // +0x13c
};
}
namespace SP {
class cAppObj {
 public:
    void* FUN_01068330();                                    // 0x01068330
    uint8_t pad224[0x224];
    cSPUIGlobalUI* mpGlobalUI_224;                           // +0x224
};
}
namespace SP {
class cCivModeStrategy {
 public:
    void* FUN_00cf7500();                                    // 0x00cf7500
};
}
namespace SP {
class cCivModeB {
 public:
    void* FUN_00ce8db0();                                    // 0x00ce8db0
};
}
namespace SP {
class cEffectsManager {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual char AddEffect(int id, int a, void** out);       // +0x2c
};
}
namespace SP {
class cAudioSystem {
 public:
    PV(0) PV(1) PV(2) PV(3)
    virtual void* pv04(int a);                               // +0x10
};
}
namespace SP {
class cMessageServer {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual void RegisterHandler(void* a, void* b);          // +0x24
};
}
namespace SP {
class cMissionCardPanel {
 public:
    void SetCardsVisibility(bool b);                         // 0x00e14c10
};
}
namespace SP {
class cPanelB {
 public:
    void FUN_00e2f270(int a);                                // 0x00e2f270
};
}
namespace SP {
class W1da0 {
 public:
    void f(void* p);                                         // 0x007b1da0
};
}
namespace SP {
class cPlanetView {
 public:
    void* FUN_00bf0f40();                                    // 0x00bf0f40
    void* FUN_00bf1e20();                                    // 0x00bf1e20
    void  FUN_00bf0f90();                                    // 0x00bf0f90
};
}
namespace SP {
class cKindObj {
 public:
    uint8_t pad58[0x58];
    int     mKind_58;                                        // +0x58
};
}
namespace SP {
struct AnimRow { uint32_t a, b, c; };
}
namespace SP {
extern AnimRow gAnimTableA[9];                               // 0x016a01f0
}
namespace SP {
extern AnimRow gAnimTableB[10];                              // 0x016a0178
}
namespace SP {
void*  NounManager();                                        // 0x00b3d300
}
namespace SP {
void*  StarManager();                                        // 0x00b3d2a0
}
namespace SP {
void*  RelationshipManager();                                // 0x00b3d2c0
}
namespace SP {
void*  CommManager();                                        // 0x00b3d4a0
}
namespace SP {
void*  MessageServer();                                      // 0x0067dcc0
}
namespace SP {
void*  EffectsManagerPtr();                                  // 0x0067ddd0
}
namespace SP {
void*  FUN_0067ddc0();                                       // 0x0067ddc0
}
namespace SP {
void*  FUN_0067cac0();                                       // 0x0067cac0
}
namespace SP {
void*  FUN_00ae9da0();                                       // 0x00ae9da0
}
namespace SP {
void*  FUN_01021300();                                       // 0x01021300
}
namespace SP {
void*  GetUFOSimulator();                                    // 0x00ffbe50
}
namespace SP {
void*  GetCurrentGameMode();                                 // 0x00b5b800
}
namespace SP {
void*  FUN_00b3d400();                                       // 0x00b3d400
}
namespace SP {
void*  FUN_00b3d4f0();                                       // 0x00b3d4f0
}
namespace SP {
void*  FUN_00a206f0();                                       // 0x00a206f0
}
namespace SP {
cCivModeStrategy* FUN_00cf74c0();                            // 0x00cf74c0
}
namespace SP {
cAppObj* FUN_010666a0();                                     // 0x010666a0
}
namespace SP {
float  FUN_00bd80d0(void* p);                                // 0x00bd80d0
}
namespace SP {
void   FUN_00e2e6e0(void* p, void* q);                       // 0x00e2e6e0
}
namespace SP {
void   FUN_006572f0(void* a, void* b);                       // 0x006572f0
}
namespace SP {
void   FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0
}
namespace SP {
void   FUN_00dd1c50(void* a, void* b);                       // 0x00dd1c50
}
namespace SP {
void   FUN_00807690(void* a, int b);                         // 0x00807690
}
namespace SP {
void*  FUN_00bef920_s00dd_2240(void* a);                                // 0x00bef920
}
namespace SP {
float* SPUIHelpers_GetBoundingScreenRect(float* out, void* win, char a); // 0x00808d20
}
namespace SP {
class cSPUICommScreen {
 public:
    void  Show();                                            // 0x00dd2e80
    void  SetSpeakerText(void* text);                        // 0x00dd2ad0
    void  GetMainCreatureScreen();                           // 0x00dd2cf0
    void  FUN_00dd2820();                                    // 0x00dd2820
    void  FUN_00dd2a10();                                    // 0x00dd2a10
    void  FUN_00dd2c60(int index, void* a, void* b);         // 0x00dd2c60
    void  FUN_00dd2d00();                                    // 0x00dd2d00
    void  FUN_00dd2d30();                                    // 0x00dd2d30
    void  FUN_00dd27c0();                                    // 0x00dd27c0
    void  FUN_00dd2800(void* w);                             // 0x00dd2800
    void  FUN_00dd2780(int kind, int count);                 // 0x00dd2780
    IWin* FUN_00dd2320(cKindObj* obj, void* other);          // 0x00dd2320
    char  FUN_00dd2650(cCreature* param_2, void** out);      // 0x00dd2650
    void* FUN_00dd1ce0(int a, int b);                        // 0x00dd1ce0

    uint8_t  pad00[0x0c];
    cSPUILayout* mLayout_0c;                                 // +0x0c
    IWin*    mScrollRoot_10;                                 // +0x10
    void*    pad14;                                          // +0x14
    IWin*    mpObj18;                                        // +0x18
    void*    mpObj1c;                                        // +0x1c
    IWin*    mTextScroll_20;                                 // +0x20
    IWin*    mpObj24;                                        // +0x24
    IWin*    mpComm_28;                                      // +0x28
    IWin*    mpButtons_2c;                                   // +0x2c
    IWin*    mpObj30;                                        // +0x30
    uint8_t  pad34[0x0c];                                    // +0x34
    uint8_t  mbShown_40;                                     // +0x40
    uint8_t  pad41[0x80 - 0x41];                             // +0x41
    cString_s00dd_2240  mStr_80;                                        // +0x80
    uint8_t  pad94[0xa8 - 0x94];                             // +0x94
    cString_s00dd_2240  mStr_a8;                                        // +0xa8
    IWin*    mpObjBc;                                        // +0xbc
    IWin*    mpObjC0;                                        // +0xc0
    uint8_t  padc4[0xd8 - 0xc4];                             // +0xc4
    void*    mpMsg_d8;                                       // +0xd8
    void*    mpMsgDc;                                        // +0xdc
    void*    mMsg_e0;                                        // +0xe0
    uint32_t mMsg_e4;                                        // +0xe4
    void*    mMsg_e8;                                        // +0xe8
};
}
namespace SP {
void __stdcall FUN_00dd2240(void* obj, void* civ);          // 0x00dd2240
}
namespace SP {
void* FUN_00dd22f0();                                        // 0x00dd22f0
}
// ---- items of slice s00dd2240 end

// ---- items of slice s00dd30d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_01654c05;
struct Vector4 { float x, y, z, w; };
struct cRGB    { unsigned char r, g, b, a; };
class cUIWindow;
class cCity;
class cSPUILayout_s00dd_30d0;
class cUIWindow {
public:
    virtual void v00();                                          // +0x00
    virtual void Release();                                      // +0x04
    virtual void FUN_0008(int flag);                             // +0x08
    virtual void* FUN_000c(unsigned int id);                     // +0x0c
    virtual cUIWindow* v10();                                    // +0x10
    virtual void v14(int v);                                     // +0x14
    virtual void v18();                                          // +0x18
    virtual void v1c();                                          // +0x1c
    virtual void v20();                                          // +0x20
    virtual void v24();                                          // +0x24
    virtual void v28();                                          // +0x28
    virtual bool FUN_002c(unsigned int id, int arg, void* out);  // +0x2c
    virtual void v30();                                          // +0x30
    virtual const Vector4* GetPos();                             // +0x34
    virtual void v38();                                          // +0x38
    virtual void v3c();                                          // +0x3c
    virtual void v40();                                          // +0x40
    virtual void FUN_0044();                                     // +0x44
    virtual void v48();                                          // +0x48
    virtual void v4c();                                          // +0x4c
    virtual void v50();                                          // +0x50
    virtual void v54();                                          // +0x54
    virtual void v58();                                          // +0x58
    virtual void FUN_005c(unsigned int v);                       // +0x5c
    virtual void SetPos(const Vector4* p);                       // +0x60
    virtual void SetSub(float a, float b);                       // +0x64
    virtual void v68();                                          // +0x68
    virtual void v6c();                                          // +0x6c
    virtual void v70();                                          // +0x70
    virtual void v74();                                          // +0x74
    virtual void v78();                                          // +0x78
    virtual void SetState(int a, bool b);                        // +0x7c
    virtual void SetText(const void* text);                      // +0x80
    virtual void v84();                                          // +0x84
    virtual void v88();                                          // +0x88
    virtual void v8c();                                          // +0x8c
    virtual void v90();                                          // +0x90
    virtual void v94();                                          // +0x94
    virtual void v98();                                          // +0x98
    virtual void v9c();                                          // +0x9c
    virtual void vA0();                                          // +0xa0
    virtual void vA4();                                          // +0xa4
    virtual void vA8();                                          // +0xa8
    virtual void FUN_00ac(unsigned int color);                   // +0xac
    virtual void vB0();                                          // +0xb0
    virtual void vB4();                                          // +0xb4
    virtual void vB8();                                          // +0xb8
    virtual void vBC();                                          // +0xbc
    virtual void vC0();                                          // +0xc0
    virtual void vC4();                                          // +0xc4
    virtual void vC8();                                          // +0xc8
    virtual void vCC();                                          // +0xcc
    virtual void vD0();                                          // +0xd0
    virtual void vD4();                                          // +0xd4
    virtual void vD8();                                          // +0xd8
    virtual void vDC();                                          // +0xdc
    virtual void vE0();                                          // +0xe0
    virtual void vE4();                                          // +0xe4
    virtual void vE8();                                          // +0xe8
    virtual void vEC();                                          // +0xec
    virtual cUIWindow* vF0(unsigned int id, int flag);           // +0xf0

    void SetCardsVisibility(bool flag);                          // 0x00e14c10
    void FUN_00e2f270();                                         // 0x00e2f270
    void clear();                                                // 0x007b1950
};
class cSPUILayout_s00dd_30d0 {
public:
    virtual void v00();                                          // +0x00
    virtual void Release();                                      // +0x04
    virtual void FUN_0008();                                     // +0x08

    cUIWindow* FindWindowByID(unsigned int id, int flag);        // 0x008105b0
    bool       SetParentWin(cUIWindow* w, bool flag, int id);    // 0x008121b0
    void       Shutdown(unsigned int flag);                      // 0x00811ad0
};
class cUIWindowFinder {
public:
    cUIWindow* FindWindowByID(unsigned int id);                  // 0x00e012b0
};
struct cListNode {
    cListNode* mpNext;      // +0x00
    cListNode* mpPrev;      // +0x04
    cUIWindow* mpObj;       // +0x08
};
class cUIList {
public:
    void erase();                                            // 0x0075f3f0
    cListNode* mpNext;                                       // +0x34
    cListNode* mpPrev;                                       // +0x38
};
class cString {
public:
    void Destroy();                                          // 0x006b5240
    unsigned char mData[0x14];
};
class cUIHints_s00dd_30d0 {
public:
    void SetFlag(char flag, int value);                      // 0x0067c420
};
class cUIWindowPtr {
public:
    cUIWindowPtr() { mPtr = 0; }
    ~cUIWindowPtr() { if (mPtr != 0) mPtr->Release(); }
    cUIWindow** GetPtrRef()
    {
        if (mPtr != 0) {
            cUIWindow* p = mPtr;
            mPtr = 0;
            p->Release();
        }
        return &mPtr;
    }
    cUIWindow* mPtr;                                         // +0x00
};
struct cRBNode {
    unsigned char mPad00[0x14];
    unsigned int  mValue;                                    // +0x14
};
class cRBTree {
public:
    cRBNode** find(cRBNode** pOut, const unsigned int& key);   // 0x00e5c780
};
class cCity {
public:
    int  FUN_00bf0f40();                                     // 0x00bf0f40
    int  FUN_00bf1e20();                                     // 0x00bf1e20
    const cRGB* FUN_00bd99e0();                              // 0x00bd99e0
    cCity* GetCivilization();                                // 0x00bd9bf0

    unsigned char mPad00[0x44];
    cRBTree       mTree44;                                   // +0x44
    unsigned char mPad48[0xc4 - 0x48];
    cRGB          mColorC4;                                  // +0xc4
};
class cGlobalUI {
public:
    void FUN_01068300();                                     // 0x01068300
    unsigned char mPad00[0x224];
    cUIWindowFinder* mpFinder224;                            // +0x224
};
class ITracerBase {
public:
    virtual ~ITracerBase() {}
    virtual void v04() {}
};
class cPaintSystem {
public:
    virtual ~cPaintSystem() {}
    virtual void v04() {}
};
class cSPUICommScreen_s00dd_30d0 : public ITracerBase, public cPaintSystem {
public:
    virtual ~cSPUICommScreen_s00dd_30d0();

    void Hide();                                             // 0x00dd30d0
    void LayoutCommButtons();                                // 0x00dd32a0
    void SetCivilizationInfo(cCity* city);                   // 0x00dd35c0
    void SetCityInfoForWindow(cCity* city);                  // 0x00dd3810
    void SetSourceAndTarget(cUIWindow* source, cCity* target);  // 0x00dd3a00
    void Shutdown();                                         // 0x00dd3d30

    void FUN_00dd2a10();                                     // 0x00dd2a10
    int  FUN_00dd1ce0(int a, int b);                         // 0x00dd1ce0
    void FUN_00dd2240(cUIWindow* w, cCity* city);            // 0x00dd2240
    int  FUN_00dd2d30();                                     // 0x00dd2d30

    __forceinline void SendSlotMessage(unsigned int id, void* value);  // 0x00dd3a00 (cSPUICommScreen::SendSlotMessage)

    cCity*        mpCity;          // +0x08
    cSPUILayout_s00dd_30d0*  mpLayout;        // +0x0c
    cUIWindow*    mp10;            // +0x10
    cUIWindow*    mp14;            // +0x14
    cUIWindow*    mp18;            // +0x18
    cUIWindow*    mp1c;            // +0x1c
    cUIWindow*    mp20;            // +0x20
    cUIWindow*    mp24;            // +0x24
    cUIWindow*    mp28;            // +0x28
    cUIWindow*    mp2c;            // +0x2c
    cUIWindow*    mp30;            // +0x30
    cUIList       mList;           // +0x34
    unsigned char mPad3c[4];       // +0x3c
    unsigned char mbShown40;       // +0x40
    unsigned char mPad41[3];       // +0x41
    cString       mStr44;          // +0x44
    cString       mStr58;          // +0x58
    cString       mStr6c;          // +0x6c
    cString       mStr80;          // +0x80
    cString       mStr94;          // +0x94
    cString       mStrA8;          // +0xa8
    cUIWindow*    mpBc;            // +0xbc
    cUIWindow*    mpC0;            // +0xc0
    int           mHandlerC4;      // +0xc4
    int           mHandlerC8;      // +0xc8
    int           mHandlerCc;      // +0xcc
    int           mHandlerD0;      // +0xd0
    int           mHandlerD4;      // +0xd4
    int           mHandlerD8;      // +0xd8
    int           mHandlerDc;      // +0xdc
    int           mHandlerE0;      // +0xe0
    int           mHandlerE4;      // +0xe4
    int           mHandlerE8;      // +0xe8
    unsigned short* mpArrayEc;     // +0xec
    unsigned short* mpArrayF0;     // +0xf0
    unsigned short* mpArrayF4;     // +0xf4
};
void*        GetCurrentGameMode();                          // 0x00b5b800
cUIHints_s00dd_30d0*    FUN_0067cac0_s00dd_30d0();                                // 0x0067cac0
cGlobalUI*   FUN_010666a0_s00dd_30d0();                                // 0x010666a0
cUIWindow*   FUN_00b3d400_s00dd_30d0();                                // 0x00b3d400
cUIWindow*   __stdcall FUN_00b3d4f0(int flag);              // 0x00b3d4f0
cUIWindow*   FUN_0067ddc0_s00dd_30d0();                                // 0x0067ddc0
cUIWindow*   EffectsManager();                              // 0x0067ddd0
int          FUN_00bef920(int v);                           // 0x00bef920
void         FUN_00807690(void* obj, int flag);             // 0x00807690
void         FUN_008076f0(void* obj);                       // 0x008076f0
void         SetImageFromKey(cUIWindow* w, int key);        // 0x00e2f5c0
unsigned int ColorRGBToU32(const void* color);              // 0x00458a40
void         FUN_00f47380(void* p);                         // 0x00f47380
void         EA_Messaging_RemoveHandler(int id, int a, int b, int c, int d);  // 0x00571db0
void cSPUICommScreen_s00dd_30d0::SetSourceAndTarget(cUIWindow* source, cCity* target)
{
    cCity* src = 0;
    cCity* other = 0;
    if (source != 0) {
        src   = (cCity*)source->FUN_000c(0x901f1362);
        other = (cCity*)source->FUN_000c(0xee9b2232);
    }

    mpLayout->FindWindowByID(0x4501222, 1);

    if (src != 0) {
        SetCivilizationInfo(src);
        SendSlotMessage(0x58b8f28, src);
    } else if (other != 0) {
        SetCityInfoForWindow(other);
        SendSlotMessage(0x58b8189, other);
    }

    cCity* dst = target;
    if (dst == 0) return;
    if (other != 0 && dst == other) return;
    if (src != 0 && dst->GetCivilization() == src) return;

    SendSlotMessage(0x58b817b, dst);
}
// ---- items of slice s00dd30d0 end

// @ 0x00dd1ce0
namespace SP {
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
}  // namespace SP

// @ 0x00dd1e30
namespace SP {
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
}  // namespace SP

// @ 0x00dd1f70
namespace SP {
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
}  // namespace SP

// @ 0x00dd21c0
namespace SP {
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
}  // namespace SP

// @ 0x00dd2240
namespace SP {
void __stdcall FUN_00dd2240(void* param_1, void* param_2)
{
    IWin* obj = (IWin*)param_1;
    int civ = ((cGameNounManager_s00dd_2240*)NounManager())->GetPlayerCivilization();
    obj->pv31(1, civ != (int)param_2);
    if (civ != (int)param_2)
    {
        float v = FUN_00bd80d0(param_2);
        IEffectNode* node = (IEffectNode*)obj->pv03(0x10edf11);
        if (node != 0)
        {
            float t = v;
            if (t <= 0.0f) t = 0.0f;
            if (t >= kClampMax) t = kClampMax;
            node->Apply(t);
        }
    }
}
}  // namespace SP

// @ 0x00dd22f0
namespace SP {
void* FUN_00dd22f0()
{
    if (GetCurrentGameMode() == &kGameModeB)
        return FUN_010666a0()->mpGlobalUI_224->FindWindowByID(0x64e7368);
    return 0;
}
}  // namespace SP

// @ 0x00dd2320
namespace SP {
IWin* cSPUICommScreen::FUN_00dd2320(cKindObj* obj, void* other)
{
    if (obj != 0)
    {
        uint32_t f = gAnimFlags;
        if ((f & 1) == 0)
        {
            f |= 1;
            gAnimFlags = f;
            gAnimTableA[0].a = 0xbf4a63b8; gAnimTableA[0].b = 0x2f7d0004; gAnimTableA[0].c = 0x0354663b;
            gAnimTableA[1].a = 0xc69009ce; gAnimTableA[1].b = 0x2f7d0004; gAnimTableA[1].c = 0x0354663b;
            gAnimTableA[2].a = 0xea3a7080; gAnimTableA[2].b = 0x2f7d0004; gAnimTableA[2].c = 0x0354663b;
            gAnimTableA[3].a = 0x85888400; gAnimTableA[3].b = 0x2f7d0004; gAnimTableA[3].c = 0x0354663b;
            gAnimTableA[4].a = 0xfd35de13; gAnimTableA[4].b = 0x2f7d0004; gAnimTableA[4].c = 0x0354663b;
            gAnimTableA[5].a = 0x29dab11f; gAnimTableA[5].b = 0x2f7d0004; gAnimTableA[5].c = 0x0354663b;
            gAnimTableA[6].a = 0xf9852530; gAnimTableA[6].b = 0x2f7d0004; gAnimTableA[6].c = 0x0354663b;
            gAnimTableA[7].a = 0x2845e1fb; gAnimTableA[7].b = 0x2f7d0004; gAnimTableA[7].c = 0x0354663b;
            gAnimTableA[8].a = 0xb865a25e; gAnimTableA[8].b = 0x2f7d0004; gAnimTableA[8].c = 0x0354663b;
        }
        if ((f & 2) == 0)
        {
            f |= 2;
            gAnimFlags = f;
            gAnimTableB[0].a = 0xbf4a63b8; gAnimTableB[0].b = 0x2f7d0004; gAnimTableB[0].c = 0x0354663b;
            gAnimTableB[1].a = 0xc69009ce; gAnimTableB[1].b = 0x2f7d0004; gAnimTableB[1].c = 0x0354663b;
            gAnimTableB[2].a = 0xea3a7080; gAnimTableB[2].b = 0x2f7d0004; gAnimTableB[2].c = 0x0354663b;
            gAnimTableB[3].a = 0x85888400; gAnimTableB[3].b = 0x2f7d0004; gAnimTableB[3].c = 0x0354663b;
            gAnimTableB[4].a = 0xfd35de13; gAnimTableB[4].b = 0x2f7d0004; gAnimTableB[4].c = 0x0354663b;
            gAnimTableB[5].a = 0x29dab11f; gAnimTableB[5].b = 0x2f7d0004; gAnimTableB[5].c = 0x0354663b;
            gAnimTableB[6].a = 0xf9852530; gAnimTableB[6].b = 0x2f7d0004; gAnimTableB[6].c = 0x0354663b;
            gAnimTableB[7].a = 0x2845e1fb; gAnimTableB[7].b = 0x2f7d0004; gAnimTableB[7].c = 0x0354663b;
            gAnimTableB[8].a = 0x24c6341d; gAnimTableB[8].b = 0x2f7d0004; gAnimTableB[8].c = 0x0354663b;
            gAnimTableB[9].a = 0x3e17e328; gAnimTableB[9].b = 0x2f7d0004; gAnimTableB[9].c = 0x0354663b;
        }
        switch (obj->mKind_58)
        {
        case 0:  return (IWin*)&gAnimTableA[0];
        case 1:  return (IWin*)&gAnimTableA[1];
        case 2:  return (IWin*)&gAnimTableA[2];
        case 3:  return (IWin*)&gAnimTableA[3];
        case 4:  return (IWin*)&gAnimTableA[4];
        case 5:  return (IWin*)&gAnimTableA[5];
        case 6:  return (IWin*)&gAnimTableA[6];
        case 7:  return (IWin*)&gAnimTableA[7];
        case 8:  return (IWin*)&gAnimTableA[8];
        case 9:  return (IWin*)&gAnimTableB[0];
        case 10: return (IWin*)&gAnimTableB[1];
        case 0xb: return (IWin*)&gAnimTableB[2];
        case 0xc: return (IWin*)&gAnimTableB[3];
        case 0xd: return (IWin*)&gAnimTableB[4];
        case 0xe: return (IWin*)&gAnimTableB[5];
        case 0xf: return (IWin*)&gAnimTableB[6];
        case 0x10: return (IWin*)&gAnimTableB[7];
        case 0x12: return (IWin*)&gAnimTableB[8];
        default: return (IWin*)&gAnimTableB[9];
        }
    }

    cPlanetView* pv = (cPlanetView*)other;
    void* a = pv->FUN_00bf0f40();
    void* b = FUN_00bef920_s00dd_2240(a);
    void* c = pv->FUN_00bf1e20();
    return (IWin*)FUN_00dd1ce0((int)b, (int)c);
}
}  // namespace SP

// @ 0x00dd2650
namespace SP {
char cSPUICommScreen::FUN_00dd2650(cCreature* param_2, void** param_3)
{
    char flag = 0;
    cCreature* a = (cCreature*)param_2->FUN_00c71e30();
    cEmpire_s00dd_2240* empire = (cEmpire_s00dd_2240*)FUN_01021300();
    cInventory* inv = (cInventory*)((cUFO*)GetUFOSimulator())->GetPlayerInventory();

    if (a != 0)
    {
        cStarManager_s00dd_2240* sm = (cStarManager_s00dd_2240*)StarManager();
        if (a->mp_84 == sm->FUN_00885c90())
        {
            cRelationshipManager_s00dd_2240* rm = (cRelationshipManager_s00dd_2240*)RelationshipManager();
            if (rm->FUN_00d01b50(a->mp_84, empire->mp_84))
            {
                void* u = rm->FUN_00d00a70(a->mp_84, empire->mp_84, 1);
                if (u == 0 || u == (void*)1)
                    return flag;
            }
        }
    }

    if (((cEmpire_s00dd_2240*)FUN_01021300())->FUN_00c30cb0() == 0)
    {
        if (param_2->mp_13c != empire->GetHomePlanet())
        {
            *param_3 = (void*)mStr_80.GetText();
            return flag;
        }
    }

    if (inv->mValue_7f4 == inv->mValue_7f8)
    {
        *param_3 = (void*)mStr_a8.GetText();
        return flag;
    }
    return 1;
}
}  // namespace SP

// @ 0x00dd2780
namespace SP {
void cSPUICommScreen::FUN_00dd2780(int kind, int count)
{
    if (kind == 2 && count > 0)
        count = 1;
    for (int i = 0; i < count; i++)
    {
        void* r = FUN_00dd1ce0(kind, i);
        ((W1da0*)mpObj30)->f(r);
    }
}
}  // namespace SP

// @ 0x00dd27c0
namespace SP {
void cSPUICommScreen::FUN_00dd27c0()
{
    IWin* w = mLayout_0c->FindWindowByID(0x4a4504f, 1);
    if (w != 0)
    {
        cLocation_s00dd_2240* loc = (cLocation_s00dd_2240*)((cDatabasePackedFile*)CommManager())->GetLocation();
        if (loc != 0)
        {
            FUN_00e2e6e0(loc->FUN_006c0200(), w);
        }
    }
}
}  // namespace SP

// @ 0x00dd2800
namespace SP {
void cSPUICommScreen::FUN_00dd2800(void* w)
{
    if (mLayout_0c != 0)
        mLayout_0c->SetParentWin((IWin*)w, true, 0x5b598fa);
}
}  // namespace SP

// @ 0x00dd2820
namespace SP {
void cSPUICommScreen::FUN_00dd2820()
{
    cLocation_s00dd_2240* loc = (cLocation_s00dd_2240*)((cDatabasePackedFile*)CommManager())->GetLocation();
    IWin* piVar5;
    if (loc->mKind_0c == 1)
    {
        IWin* p = (IWin*)FUN_00ae9da0();
        IWin* old = mpObjBc;
        if (p != old)
        {
            if (p) p->AddRef();
            mpObjBc = p;
            if (old) old->Release();
        }
        piVar5 = *(IWin**)((char*)mpObjBc + 0x274);
    }
    else
    {
        void* u = loc->FUN_006c0200();
        piVar5 = 0;
        cStarManager_s00dd_2240* sm = (cStarManager_s00dd_2240*)StarManager();
        int i = sm->GetEmpireByID(u);
        cGameNounManager_s00dd_2240* nm = (cGameNounManager_s00dd_2240*)NounManager();
        IWin* p = (IWin*)nm->FUN_00b25f40();
        IWin* old = mpObjBc;
        if (p != old)
        {
            if (p) p->AddRef();
            mpObjBc = p;
            if (old) old->Release();
        }
        if (i != 0)
            piVar5 = (IWin*)sm->FUN_00bce4c0();
    }
    {
        IWin* old = mpObjC0;
        if (piVar5 != old)
        {
            if (piVar5) piVar5->AddRef();
            mpObjC0 = piVar5;
            if (old) old->Release();
        }
    }

    Vec3 vec;
    void* sys = FUN_00a206f0();
    if (sys != 0)
    {
        float* p = (float*)((cAudioSystem*)sys)->pv04(0);
        vec.x = p[0]; vec.y = p[1]; vec.z = p[2];
    }
    else
    {
        vec.x = kAudioPos[0]; vec.y = kAudioPos[1]; vec.z = kAudioPos[2];
    }

    if (mpObjBc == 0)
    {
        if (mpObjC0 != 0) mpObjC0->pv09(&vec);
    }
    else
    {
        if (mpObjC0 != 0) mpObjC0->pv12(&vec);
    }

    if (mpObjC0 != 0)
        FUN_006572f0((void*)0xedf69848, mpObjC0->pv13());

    void* msg = MessageServer();
    mpMsg_d8 = msg;
    mpMsgDc = (char*)this + 4;
    mMsg_e0 = (void*)0x15a2b2c;
    mMsg_e4 = 1;
    mMsg_e8 = 0;
    if (msg != 0 && mpMsgDc != 0)
        ((cMessageServer*)msg)->RegisterHandler(mpMsgDc, mMsg_e0);
}
}  // namespace SP

// @ 0x00dd2a10
namespace SP {
void cSPUICommScreen::FUN_00dd2a10()
{
    void* h = mpMsg_d8;
    if (h != 0)
    {
        mpMsg_d8 = 0;
        FUN_00571db0(h, mpMsgDc, mMsg_e0, (void*)mMsg_e4, mMsg_e8);
    }
    if (mpObjC0 != 0)
        FUN_00dd1c50((void*)0xedf69848, mpObjC0->pv13());

    if (mpObjBc != 0)
    {
        ((cPlanetView*)mpObjBc)->FUN_00bf0f90();
    }
    else
    {
        if (mpObjC0 != 0) mpObjC0->pv10();
    }

    IWin* p = mpObjBc;
    if (p != 0)
    {
        mpObjBc = 0;
        p->Release();
    }
    IWin* q = mpObjC0;
    if (q != 0)
    {
        mpObjC0 = 0;
        q->Release();
    }
}
}  // namespace SP

// @ 0x00dd2ad0
namespace SP {
void cSPUICommScreen::SetSpeakerText(void* text)
{
    IWin* edi;
    if (mpComm_28 == 0) edi = 0;
    else edi = (IWin*)mpComm_28->pv03(0xf15f4bd);

    mpComm_28->pv32(text);

    {
        float* a = (float*)mTextScroll_20->pv13();
        float ax = a[0], az = a[2];
        float* b = (float*)mpComm_28->pv13();
        float b0 = b[0];
        float v[4];
        v[0] = b[0]; v[1] = b[1]; v[2] = b[2]; v[3] = b[3];
        v[2] = (az - ax) + b0;
        mpComm_28->pv24(v);
    }
    mpComm_28->pv25(0.0f, 0.0f);
    edi->pv07(1);
    FUN_00807690(mpObj1c, 1);

    {
        float* a = (float*)mTextScroll_20->pv13();
        float ax = a[0], az = a[2];
        float* b = (float*)mpComm_28->pv13();
        float b0 = b[0];
        float v[4];
        v[0] = b[0]; v[1] = b[1]; v[2] = b[2]; v[3] = b[3];
        v[2] = (az - ax) + b0;
        mpComm_28->pv24(v);
    }
    mpComm_28->pv25(0.0f, 0.0f);
    edi->pv07(1);
    FUN_00807690(mpObj1c, 1);
}
}  // namespace SP

// @ 0x00dd2c60
namespace SP {
void cSPUICommScreen::FUN_00dd2c60(int index, void* a, void* b)
{
    int i = 0;
    SList* begin;
    SList* local;
    mpObj24->pv52(&begin);
    SList* cur = *(SList**)mpObj24->pv51(&local);
    if (cur != begin)
    {
        for (;;)
        {
            if (i == index) break;
            cur = cur->mpNext;
            i++;
            if (cur == begin) return;
        }
        IWin* node = (IWin*)(gAnimBase + (uint32_t)cur);
        node->pv32(a);
        node->pv31(2, (int)b);
    }
}
}  // namespace SP

// @ 0x00dd2cf0
namespace SP {
void cSPUICommScreen::GetMainCreatureScreen()
{
    mLayout_0c->FindWindowByID(0x3619a7e, 1);
}
}  // namespace SP

// @ 0x00dd2d00
namespace SP {
void cSPUICommScreen::FUN_00dd2d00()
{
    IWin* w = mLayout_0c->FindWindowByID(-1, 1);
    IWin* c = (IWin*)w->pv04();
    c->pv58(w);
}
}  // namespace SP

// @ 0x00dd2d30
namespace SP {
void cSPUICommScreen::FUN_00dd2d30()
{
    if (mpObj24 == 0) return;
    if (mpObj18 == 0) return;
    if (mpObj18->pv04() == 0) return;

    float rect[4];
    SPUIHelpers_GetBoundingScreenRect(rect, mpObj18->pv04(), 0);

    SList* begin;
    SList* local;
    mpObj24->pv52(&begin);
    SList* cur = *(SList**)mpObj24->pv51(&local);
    if (cur == begin) return;

    for (;;)
    {
        float r2[4];
        IWin* node = (IWin*)(gAnimBase + (uint32_t)cur);
        SPUIHelpers_GetBoundingScreenRect(r2, node, 0);

        bool vis;
        if (rect[2] <= r2[0] || rect[0] <= r2[2] || rect[3] <= r2[1] || rect[1] <= r2[3])
        {
            r2[1] = 0.0f; r2[3] = 0.0f; r2[2] = 0.0f; r2[0] = 0.0f;
            vis = false;
        }
        else
        {
            if (r2[0] <= r2[2]) r2[0] = r2[2];
            if (r2[1] <= r2[3]) r2[1] = r2[3];
            if (rect[0] <= r2[2]) r2[2] = rect[0];
            if (rect[1] <= r2[3]) r2[3] = rect[1];
            vis = true;
        }
        node->pv31(0x10, !vis);
        cur = cur->mpNext;
        if (cur == begin) break;
    }
}
}  // namespace SP

// @ 0x00dd2e80
namespace SP {
void cSPUICommScreen::Show()
{
    if (mbShown_40 != 0) return;

    ((cUIHints*)FUN_0067cac0())->SetFlag(0, 1);
    IWin* ebx = mLayout_0c->FindWindowByID(0x1c3bb0c, 1);
    if (ebx == 0) return;

    mbShown_40 = 1;
    cEffectsManager* em = (cEffectsManager*)EffectsManagerPtr();
    if (mpButtons_2c != 0)
    {
        IWin* t = mpButtons_2c;
        mpButtons_2c = 0;
        t->Release();
    }
    if (em->AddEffect(0x4c4ba0a9, 0, (void**)&mpButtons_2c))
        ((IEffectWin*)mpButtons_2c)->SetVisible(0);

    ((IWin*)FUN_0067ddc0())->pv16();
    ((IWin*)FUN_0067ddc0())->pv10();

    void* mode = GetCurrentGameMode();
    void* win = 0;
    if (mode == &kGameModeB)
    {
        win = FUN_010666a0()->mpGlobalUI_224->FindWindowByID(0x5e66e88);
        FUN_010666a0()->FUN_01068330();
    }
    else if (mode == &kGameModeA)
    {
        win = ((cCivModeB*)FUN_00cf74c0()->FUN_00cf7500())->FUN_00ce8db0();
    }

    if (mLayout_0c != 0)
        mLayout_0c->SetParentWin((IWin*)win, true, 0x5b598fa);

    if (FUN_00b3d400() != 0)
        ((cMissionCardPanel*)FUN_00b3d400())->SetCardsVisibility(false);

    ((cPanelB*)FUN_00b3d4f0())->FUN_00e2f270(1);

    ebx->pv31(1, 1);

    IWin* w = mLayout_0c->FindWindowByID(0x5e4e5f8, 1);
    if (w != 0) w->pv31(1, 1);
    w = mLayout_0c->FindWindowByID(0x5e4e5f0, 1);
    if (w != 0) w->pv31(1, 1);
    w = mLayout_0c->FindWindowByID(0x6429c80, 1);
    if (w != 0) w->pv31(1, 1);
    w = mLayout_0c->FindWindowByID(0x5e3c090, 1);
    if (w != 0) w->pv31(1, 0);

    void* out2 = 0;
    cEffectsManager* em2 = (cEffectsManager*)EffectsManagerPtr();
    if (out2 != 0)
    {
        IWin* t = (IWin*)out2;
        out2 = 0;
        t->Release();
    }
    if (em2->AddEffect(0x3d6f608, 0, &out2))
        ((IEffectWin*)out2)->SetVisible(0);

    cEffectsManager* em3 = (cEffectsManager*)EffectsManagerPtr();
    if (mScrollRoot_10 != 0)
    {
        IWin* t = mScrollRoot_10;
        mScrollRoot_10 = 0;
        t->Release();
    }
    if (em3->AddEffect(0x3d6f60b, 0, (void**)&mScrollRoot_10))
        ((IEffectWin*)mScrollRoot_10)->SetVisible(0);

    FUN_00dd2820();

    if (out2 != 0)
        ((IWin*)out2)->Release();
}
}  // namespace SP

// @ 0x00dd30d0
void cSPUICommScreen_s00dd_30d0::Hide()
{
    if (mbShown40 != 0) {
        FUN_0067cac0_s00dd_30d0()->SetFlag(1, 1);

        if (GetCurrentGameMode() == &g_01654c05) {
            FUN_010666a0_s00dd_30d0()->FUN_01068300();
        }

        if (FUN_00b3d400_s00dd_30d0() != 0) {
            FUN_00b3d400_s00dd_30d0()->SetCardsVisibility(true);
        }

        FUN_00b3d4f0(0)->FUN_00e2f270();

        mpCity = 0;

        cUIWindow* w = mpLayout->FindWindowByID(0x5e4e5f8, 1);
        if (w != 0) w->SetState(1, 0);
        w = mpLayout->FindWindowByID(0x5e4e5f0, 1);
        if (w != 0) w->SetState(1, 0);
        w = mpLayout->FindWindowByID(0x6429c80, 1);
        if (w != 0) w->SetState(1, 0);

        if (GetCurrentGameMode() == &g_01654c05) {
            cUIWindow* g = FUN_010666a0_s00dd_30d0()->mpFinder224->FindWindowByID(0x64e7368);
            if (g != 0) g->v10()->SetState(1, 0);
        }

        w = mpLayout->FindWindowByID(0x1c3bb0c, 1);
        if (w != 0) {
            mbShown40 = 0;
            w->SetState(1, 0);

            if (mp2c != 0) {
                mp2c->FUN_000c(1);
                if (mp2c != 0) {
                    cUIWindow* old = mp2c;
                    mp2c = 0;
                    old->Release();
                }
            }

            if (mp10 != 0) {
                mp10->FUN_000c(0);
                if (mp10 != 0) {
                    cUIWindow* old = mp10;
                    mp10 = 0;
                    old->Release();
                }
            }

            FUN_0067ddc0_s00dd_30d0()->FUN_0044();

            FUN_00dd2a10();

            cUIWindowPtr effect;
            cUIWindow* mgr = EffectsManager();
            if (mgr->FUN_002c(0x3d6f60f, 0, effect.GetPtrRef())) {
                effect.mPtr->FUN_0008(0);
            }
        }
    }
}

// @ 0x00dd32a0
void cSPUICommScreen_s00dd_30d0::LayoutCommButtons()
{
    const Vector4* pa = mp18->GetPos();
    float ax = pa->x;
    float az = pa->z;
    const Vector4* pb = mp24->GetPos();
    Vector4 v;
    v.x = pb->x;
    v.y = pb->y;
    v.w = pb->w;
    float dz = az - ax;
    v.z = dz + pb->x;
    mp24->SetPos(&v);
    mp24->SetSub(0.0f, 0.0f);

    cListNode* head = (cListNode*)&mList;
    float total = 0.0f;
    for (cListNode* e = head->mpNext; e != head; e = e->mpNext) {
        cUIWindow* obj = e->mpObj;
        cUIWindow* inner = obj->v10();
        Vector4 w;
        w.x = 0.0f;
        w.y = 0.0f;
        w.z = dz;
        w.w = 18.0f;
        inner->SetPos(&w);
        obj->v14(1);
        const Vector4* ip = inner->GetPos();
        total += (ip->w - ip->y) + 2.0f;
    }

    v.w = v.y + total;
    mp24->SetPos(&v);
    mp24->SetSub(0.0f, 0.0f);
    FUN_00807690(mp14, 1);

    const Vector4* pi = mp18->GetPos();
    v.z = (pi->z - pi->x) + v.x;
    total = 0.0f;
    for (cListNode* e = head->mpNext; e != head; e = e->mpNext) {
        cUIWindow* obj = e->mpObj;
        cUIWindow* inner = obj->v10();
        const Vector4* ip = inner->GetPos();
        Vector4 w;
        w.x = ip->x;
        w.y = ip->y;
        w.w = ip->w;
        w.z = (v.z - v.x) + ip->x;
        inner->SetPos(&w);
        inner->SetSub(0.0f, total);
        obj->v14(1);
        const Vector4* iq = inner->GetPos();
        w.x = iq->x;
        w.y = iq->y;
        w.w = iq->w;
        w.z = (v.z - v.x) + iq->x;
        inner->SetPos(&w);
        total += (w.w - w.y) + 2.0f;
    }

    v.w = v.y + total;
    mp24->SetPos(&v);
    mp24->SetSub(0.0f, 0.0f);
    FUN_00807690(mp14, 1);
    FUN_00dd2d30();
}

// @ 0x00dd35c0
void cSPUICommScreen_s00dd_30d0::SetCivilizationInfo(cCity* city)
{
    mpCity = city;

    mpLayout->FindWindowByID(0x5dff098, 1)->SetState(1, 0);
    mpLayout->FindWindowByID(0x5e4f778, 1)->SetState(1, 0);
    mpLayout->FindWindowByID(0x5e4f788, 1)->SetState(1, 0);
    mpLayout->FindWindowByID(0x5e4f770, 1)->SetState(1, 0);

    cUIWindow* main = mpLayout->FindWindowByID(0x4501222, 1)->v10();
    cUIWindow* panel = main->vF0(0x49382e8, 1);
    cUIWindow* img = mpLayout->FindWindowByID(0x5edff88, 1);

    SetImageFromKey(img, FUN_00dd1ce0(FUN_00bef920(city->FUN_00bf0f40()),
                                      city->FUN_00bf1e20()));

    cUIWindow* colorWin = mpLayout->FindWindowByID(0x6243260, 1);
    if (colorWin != 0) {
        colorWin->FUN_00ac(ColorRGBToU32(&city->mColorC4));
    }

    panel->SetState(1, 1);

    union { unsigned int mKey; cRBNode* mpNode; } scratch;
    scratch.mKey = 1;
    cRBNode** res = city->mTree44.find(&scratch.mpNode, scratch.mKey);
    panel->SetText((const void*)(*res)->mValue);

    main->vF0(0x2cf324c, 1)->FUN_005c(ColorRGBToU32(&city->mColorC4));

    int tier = FUN_00bef920(city->FUN_00bf0f40());
    main->vF0(0x2cf2f30, 1)->SetState(1, tier == 2);
    main->vF0(0x2cf2f34, 1)->SetState(1, tier == 1);
    main->vF0(0x2cf2f38, 1)->SetState(1, tier == 0);

    FUN_00dd2240(mpLayout->FindWindowByID(0x4a4504f, 1), city);
}

// @ 0x00dd3810
void cSPUICommScreen_s00dd_30d0::SetCityInfoForWindow(cCity* city)
{
    cUIWindow* main = mpLayout->FindWindowByID(0x4501222, 1)->v10();
    cUIWindow* img  = mpLayout->FindWindowByID(0x5edff88, 1);

    bool shown = (city != 0);
    img->SetState(1, shown);

    if (city != 0) {
        cCity* civ = city->GetCivilization();
        mpCity = civ;

        SetImageFromKey(img, FUN_00dd1ce0(FUN_00bef920(civ->FUN_00bf0f40()),
                                          civ->FUN_00bf1e20()));

        cUIWindow* colorWin = mpLayout->FindWindowByID(0x6243260, 1);
        if (colorWin != 0) {
            colorWin->FUN_00ac(ColorRGBToU32(city->FUN_00bd99e0()));
        }

        mpLayout->FindWindowByID(0x5dff098, 1)->SetState(1, 0);
        mpLayout->FindWindowByID(0x5e4f778, 1)->SetState(1, 0);
        mpLayout->FindWindowByID(0x5e4f788, 1)->SetState(1, 0);
        mpLayout->FindWindowByID(0x5e4f770, 1)->SetState(1, 0);

        cUIWindow* panel = main->vF0(0x49382e8, 1);
        panel->SetState(1, 1);

        union { unsigned int mKey; cRBNode* mpNode; } scratch;
        scratch.mKey = 1;
        cRBNode** res = mpCity->mTree44.find(&scratch.mpNode, scratch.mKey);
        panel->SetText((const void*)(*res)->mValue);

        main->vF0(0x2cf324c, 1)->FUN_005c(ColorRGBToU32(city->FUN_00bd99e0()));

        cUIWindow* last = mpLayout->FindWindowByID(0x4a4504f, 1);
        if (last != 0) {
            FUN_00dd2240(last, mpCity);
        }
    }
}

// @ 0x00dd3b60
cSPUICommScreen_s00dd_30d0::~cSPUICommScreen_s00dd_30d0()
{
    _ReadWriteBarrier();   // retail keeps the two vptr stores at the very top
    if (((int)(((char*)mpArrayF4 - (char*)mpArrayEc) & 0xfffffffe) > 2)
        && mpArrayEc != 0) {
        FUN_00f47380(mpArrayEc);
    }

    if (mHandlerD8 != 0) {
        int id = mHandlerD8;
        mHandlerD8 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerDc, mHandlerE0, mHandlerE4, mHandlerE8);
    }
    if (mHandlerC4 != 0) {
        int id = mHandlerC4;
        mHandlerC4 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerC8, mHandlerCc, mHandlerD0, mHandlerD4);
    }

    if (mpC0 != 0) mpC0->Release();
    if (mpBc != 0) mpBc->Release();

    mStrA8.Destroy();
    mStr94.Destroy();
    mStr80.Destroy();
    mStr6c.Destroy();
    mStr58.Destroy();
    mStr44.Destroy();

    mList.erase();

    if (mp30 != 0) mp30->Release();
    if (mp2c != 0) mp2c->Release();
    if (mp28 != 0) mp28->Release();
    if (mp24 != 0) mp24->Release();
    if (mp20 != 0) mp20->Release();
    if (mp1c != 0) mp1c->Release();
    if (mp18 != 0) mp18->Release();
    if (mp14 != 0) mp14->Release();
    if (mp10 != 0) mp10->Release();
    if (mpLayout != 0) mpLayout->FUN_0008();
}

// @ 0x00dd3d30
void cSPUICommScreen_s00dd_30d0::Shutdown()
{
    if (mbShown40 != 0) {
        Hide();
    }

    if (mHandlerC4 != 0) {
        int id = mHandlerC4;
        mHandlerC4 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerC8, mHandlerCc, mHandlerD0, mHandlerD4);
    }
    if (mHandlerD8 != 0) {
        int id = mHandlerD8;
        mHandlerD8 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerDc, mHandlerE0, mHandlerE4, mHandlerE8);
    }

    cListNode* head = (cListNode*)&mList;
    mList.erase();
    head->mpNext = head;
    head->mpPrev = head;
    mpCity = 0;
    _ReadWriteBarrier();   // retail loads [this+0x24] only after the store above

    {
        cUIWindow* p = mp24;
        if (p != 0) { mp24 = 0; p->Release(); }
    }
    {
        cUIWindow* p = mp28;
        if (p != 0) { mp28 = 0; p->Release(); }
    }

    FUN_008076f0(mp14);
    {
        cUIWindow* p = mp14;
        if (p != 0) { mp14 = 0; p->Release(); }
    }
    {
        cUIWindow* p = mp18;
        if (p != 0) { mp18 = 0; p->Release(); }
    }
    FUN_008076f0(mp1c);
    {
        cUIWindow* p = mp1c;
        if (p != 0) { mp1c = 0; p->Release(); }
    }
    {
        cUIWindow* p = mp20;
        if (p != 0) { mp20 = 0; p->Release(); }
    }

    if (mp30 != 0) {
        mp30->clear();
        cUIWindow* p = mp30;
        if (p != 0) { mp30 = 0; p->Release(); }
    }

    if (mpLayout != 0) {
        mpLayout->SetParentWin(0, true, 0x5b598fa);
        mpLayout->Shutdown(1);
        cSPUILayout_s00dd_30d0* p = mpLayout;
        if (p != 0) { mpLayout = 0; p->FUN_0008(); }
    }

    if (mp10 != 0) {
        mp10->FUN_000c(0);
        cUIWindow* p = mp10;
        if (p != 0) { mp10 = 0; p->Release(); }
    }

    if (mp2c != 0) {
        mp2c->FUN_000c(0);
        cUIWindow* p = mp2c;
        if (p != 0) { mp2c = 0; p->Release(); }
    }
}
