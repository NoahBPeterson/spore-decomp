// src/game/SPGonzago/_at_00e40000.cpp -- migrated from slice(s) s00e4c9e0, s00e49a40, s00e48bb0, s00e47930, s00e47520, s00e46600, s00e45760, s00e44d20, s00e44200 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e40000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cConfigManager.h"
#include "SP/cSPPaletteItem.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/RenderContext.h"
#include "SP/cCameraManager.h"
#include "SP/cString.h"
#include "EA/Variant.h"
#include "cSPUIAnimator.h"
#include "SP/cSPMission.h"
#include "SP/cTypeDef.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern uint8_t gForceTimelineMode;                         // @ 0x16acdf0

// ---- items of slice s00e44200 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector4 { float x, y, z, w; };
struct Object {
    virtual int  AddRef();                                 // +0x00
    virtual int  Release();                                // +0x04
    virtual void Delete();                                 // +0x08
};
#define IOFF(n) virtual void v##n();
struct IWindow : Object {
    IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void BeforeRelease();                          // +0x20
    virtual void Unload();                                 // +0x24
    IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c) IOFF(40)
    IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void SetShadeColor(uint32_t color);            // +0x5c
    virtual void SetLayoutData(const Vector4* data);       // +0x60
    IOFF(64) IOFF(68) IOFF(6c) IOFF(70) IOFF(74) IOFF(78)
    virtual void SetVisible(int visible, int recursive);   // +0x7c
    IOFF(80) IOFF(84) IOFF(88) IOFF(8c) IOFF(90) IOFF(94) IOFF(98) IOFF(9c)
    IOFF(a0) IOFF(a4) IOFF(a8) IOFF(ac) IOFF(b0) IOFF(b4) IOFF(b8) IOFF(bc)
    IOFF(c0) IOFF(c4) IOFF(c8) IOFF(cc) IOFF(d0) IOFF(d4) IOFF(d8) IOFF(dc)
    IOFF(e0) IOFF(e4) IOFF(e8) IOFF(ec) IOFF(f0) IOFF(f4) IOFF(f8) IOFF(fc)
    IOFF(100) IOFF(104)
    virtual void SetParent(void* parent);                  // +0x108
};
class cSPUILayout_s00e4_4200 : public IWindow {
public:
    bool      IsVisible();                                 // 0x00810070
    void      SetVisibility(int visible);                  // 0x00810590
    IWindow*  FindWindowByID(uint32_t id, bool recursive); // 0x008105b0
    void      Shutdown(int everything);                    // 0x00811ad0
};
struct cSPPaletteItem : Object {
    void Shutdown();                                       // 0x005c6710
};
struct RefCountBase {
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
};
struct cTwoBaseObj {
    virtual int  AddRef();                                 // +0x00
    virtual int  Release();                                // +0x04
    virtual void Delete();                                 // +0x08
    uint32_t     mPad04[3];                                // +0x04 .. +0x0f
    RefCountBase mSecond;                                  // +0x10
};
struct IFlaggedRelease {
    virtual void Release(int keep);                        // +0x00
};
struct IEffectsHandler {
    virtual void pad00();                                  // +0x00
    virtual void Release();                                // +0x04
    virtual void Delete(int unused);                       // +0x08
    virtual void SetEnabled(int enabled);                  // +0x0c
};
struct KeyVec {
    void* mpBegin;                                         // +0x00
    void* mpEnd;                                           // +0x04
    void* mpCap;                                           // +0x08
    void  DoCopy(void* first, void* last);                 // 0x0050f740
};
struct cNotifier67dd50 {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c)
    IOFF(40) IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void SetNotificationA(uint32_t id, int value); // +0x5c
    virtual void SetNotificationB(uint32_t id, int value); // +0x60
};
struct cConfigManager {                                    // 0x0067dd30
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c)
    virtual int GetChoice(uint32_t id);                    // +0x30
};
struct cRenderTargetUser;
struct cHSM67de40 {                                        // 0x0067de40
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual cRenderTargetUser* GetRenderTargets();         // +0x20
};
struct cRenderTargetUser {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void SetCallbackTarget(void* target);          // +0x20
};
cConfigManager* SP_ConfigManager();                        // 0x0067dd30
void EA_Messaging_RemoveHandler(void* handler, void* owner, void* ids,
                                void* extra, unsigned flags); // 0x00571db0
extern "C" cNotifier67dd50* FUN_0067dd50();                // 0x0067dd50
extern "C" cHSM67de40*      FUN_0067de40();                // 0x0067de40
extern uint8_t gForceTimelineMode;                         // @ 0x16acdf0
struct cSPUITimeline {
    uint32_t         mVtbl;                                // +0x00
    uint32_t         mSelfWindow;                          // +0x04 head of the embedded window subobject
    uint32_t         mPad08[3];                            // +0x08 .. +0x13
    void*            mpCallbackTarget;                     // +0x14 handed to the render targets
    uint32_t         mPad18;                               // +0x18
    IFlaggedRelease* mpAnimatorA;                          // +0x1c
    cSPUILayout_s00e4_4200*     mpLayoutA;                            // +0x20
    cSPUILayout_s00e4_4200*     mpLayoutB;                            // +0x24
    IWindow*         mpWindowA;                            // +0x28
    IWindow*         mpWindowB;                            // +0x2c
    cSPUILayout_s00e4_4200*     mpLayout;                             // +0x30 the timeline layout Show() drives
    uint32_t         mPad34;                               // +0x34
    IWindow*         mpModalOwner;                         // +0x38
    IWindow*         mpCreatureWindow;                     // +0x3c
    uint32_t         mPad40;                               // +0x40
    IWindow*         mpTribeWindow;                        // +0x44
    uint32_t         mPad48;                               // +0x48
    IWindow*         mpCivWindow;                          // +0x4c
    uint32_t         mPad50[2];                            // +0x50 .. +0x57
    IWindow*         mpCreatureButton;                     // +0x58
    uint32_t         mPad5c;                               // +0x5c
    IWindow*         mpTribeButton;                        // +0x60
    uint32_t         mPad64[0x56];                         // +0x64 .. +0x1bb
    cSPPaletteItem*  mpPaletteItem;                        // +0x1bc
    Object*          mpPaletteInfo;                        // +0x1c0
    IWindow*         mpPaletteRollover;                    // +0x1c4
    IWindow*         mpEventRollover;                      // +0x1c8
    uint32_t         mPad1cc[0x28];                        // +0x1cc .. +0x26b
    bool             mbCreatureWindowShown;                // +0x26c
    bool             mbTribeWindowShown;                   // +0x26d
    uint8_t          mPad26e[0x0e];                        // +0x26e .. +0x27b
    bool             mbPanelReady;                         // +0x27c
    uint8_t          mPad27d[3];                           // +0x27d .. +0x27f
    int              mnPanelState;                         // +0x280
    int              mnShowMode;                           // +0x284
    uint32_t         mPad288[3];                           // +0x288 .. +0x293
    int              mnGameLevel;                          // +0x294
    uint32_t         mPad298[0x23];                        // +0x298 .. +0x323
    void*            mpMsgServer;                          // +0x324
    void*            mpMsgOwner;                           // +0x328
    void*            mpMsgIDs;                             // +0x32c
    IEffectsHandler* mpEffectsHandler;                     // +0x330
    unsigned         mMsgFlags;                            // +0x334
    cSPUILayout_s00e4_4200*     mpLayoutC;                            // +0x338
    cSPUILayout_s00e4_4200*     mpLayoutD;                            // +0x33c
    uint32_t         mPad340[9];                           // +0x340 .. +0x363
    IWindow*         mpRowWindows[10];                     // +0x364
    IWindow*         mpRowIcons[10];                       // +0x38c
    cTwoBaseObj*     mpRowData;                            // +0x3b4
    IWindow*         mpRowExtras[10];                      // +0x3b8
    uint32_t         mPad3e0[26];                          // +0x3e0 .. +0x447
    IFlaggedRelease* mpAnimatorB;                          // +0x448
    uint32_t         mPad44c;                              // +0x44c
    KeyVec           mCellKeys;                            // +0x450
    uint32_t         mPad45c[2];                           // +0x45c .. +0x463
    KeyVec           mCreatureKeys;                        // +0x464

    IWindow* Self() { return (IWindow*)&mSelfWindow; }     // the embedded window at +0x04

    void Show(int show);                                   // 0x00e44200
    bool HandleTimelineMessage(uint32_t msgID, void* payload); // 0x00e449b0
    void FUN_00e37910();                                   // 0x00e37910
    void FUN_00e3e7f0();                                   // 0x00e3e7f0
    void FUN_00e42100();                                   // 0x00e42100
    void FUN_00e43280();                                   // 0x00e43280
};
struct cSPUITimelineShutdown {
    uint32_t         mPad00;                               // +0x00 (body +0x00)
    uint32_t         mPad04;                               // +0x04 (body +0x04)
    uint32_t         mPad08[5];                            // +0x08 .. +0x1b (body +0x00 .. +0x13)
    void*            mpCallbackTarget;                     // +0x1c (body +0x14)
    uint32_t         mPad20;                               // +0x20 (body +0x18)
    IFlaggedRelease* mpAnimatorA;                          // +0x24 (body +0x1c)
    cSPUILayout_s00e4_4200*     mpLayoutA;                            // +0x28 (body +0x20)
    cSPUILayout_s00e4_4200*     mpLayoutB;                            // +0x2c (body +0x24)
    IWindow*         mpWindowA;                            // +0x30 (body +0x28)
    IWindow*         mpWindowB;                            // +0x34 (body +0x2c)
    uint32_t         mPad38[3];                            // +0x38 .. +0x43 (body +0x30 .. +0x3b)
    IWindow*         mpCreatureWindow;                     // +0x44 (body +0x3c)
    uint32_t         mPad48;                               // +0x48 (body +0x40)
    IWindow*         mpTribeWindow;                        // +0x4c (body +0x44)
    uint32_t         mPad50[0x5d];                         // +0x50 .. +0x1c3 (body +0x48 .. +0x1bb)
    cSPPaletteItem*  mpPaletteItem;                        // +0x1c4 (body +0x1bc)
    Object*          mpPaletteInfo;                        // +0x1c8 (body +0x1c0)
    IWindow*         mpPaletteRollover;                    // +0x1cc (body +0x1c4)
    IWindow*         mpEventRollover;                      // +0x1d0 (body +0x1c8)
    uint32_t         mPad1d4[0x56];                        // +0x1d4 .. +0x32b (body +0x1cc .. +0x323)
    void*            mpMsgServer;                          // +0x32c (body +0x324)
    void*            mpMsgOwner;                           // +0x330 (body +0x328)
    void*            mpMsgIDs;                             // +0x334 (body +0x32c)
    IEffectsHandler* mpEffectsHandler;                     // +0x338 (body +0x330)
    unsigned         mMsgFlags;                            // +0x33c (body +0x334)
    cSPUILayout_s00e4_4200*     mpLayoutC;                            // +0x340 (body +0x338)
    cSPUILayout_s00e4_4200*     mpLayoutD;                            // +0x344 (body +0x33c)
    uint32_t         mPad348[9];                           // +0x348 .. +0x36b (body +0x340 .. +0x363)
    IWindow*         mpRowWindows[10];                     // +0x36c (body +0x364)
    IWindow*         mpRowIcons[10];                       // +0x394 (body +0x38c)
    cTwoBaseObj*     mpRowData;                            // +0x3bc (body +0x3b4)
    IWindow*         mpRowExtras[10];                      // +0x3c0 (body +0x3b8)
    uint32_t         mPad3e8[26];                          // +0x3e8 .. +0x44f (body +0x3e0 .. +0x447)
    IFlaggedRelease* mpAnimatorB;                          // +0x450 (body +0x448)
    uint32_t         mPad454;                              // +0x454 (body +0x44c)
    KeyVec           mCellKeys;                            // +0x458 (body +0x450)
    uint32_t         mPad464[2];                           // +0x464 .. +0x46b (body +0x45c .. +0x463)
    KeyVec           mCreatureKeys;                        // +0x46c (body +0x464)

    __forceinline cSPUITimeline* Body() { return (cSPUITimeline*)((char*)this - 8); }
    __forceinline void* SelfOrNull() {
        cSPUITimeline* b = Body();
        return b ? (void*)b->Self() : (void*)0;
    }

    void Destroy();                                        // 0x00e44a30
};
// ---- items of slice s00e44200 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" cNotifier67dd50* FUN_0067dd50();                // 0x0067dd50
extern "C" cHSM67de40*      FUN_0067de40();                // 0x0067de40

// ---- items of slice s00e44d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gkHalf;                                   // 0x01471064  (0.5f)
extern const float gkSettleTime;                             // 0x01486374  (0.8f)
extern const float gkHoldTime;                               // 0x01481ca8  (0.2f)
typedef unsigned char uchar;
extern uchar gPendingUpgrade;                                // 0x015a5a84
struct TimedPropertyPart {
    char mPad000[0x18];

    float GetElapsedTimeFloat();                             // 0x005ff1a0
    void  SetBoolProperty();                                 // 0x0093a2e0
    void  Restart();                                         // 0x00571e80
};
const int kEqualConstraint = 0;
struct Constraint {
    int mKey;                                                // +0x00
    int mType;                                               // +0x04
    int mValue;                                              // +0x08

    Constraint(int key, int type, int value);                // 0x00558960
    ~Constraint();                                           // 0x006066f0
};
struct ConstraintNode {
    Constraint mConstraint;                                  // +0x00
    char mPad00c[0x24 - 0x0c];

    ConstraintNode(const Constraint& value);                 // 0x00606880
};
struct ConstraintVector {
    Constraint* mpBegin;                                     // +0x00
    Constraint* mpEnd;                                       // +0x04
    Constraint* mpCap;                                       // +0x08

    int  Count() const { return (int)(mpEnd - mpBegin); }
    void PushBack(const Constraint& value);                  // 0x004e18e0
};
struct ConstraintNodeVector {
    ConstraintNode* mpBegin;                                 // +0x00
    ConstraintNode* mpEnd;                                   // +0x04
    ConstraintNode* mpCap;                                   // +0x08

    void PushBack(const Constraint& value);                  // 0x004e38d0 / 0x004e39d0
};
typedef Constraint TemplateKey;
struct TemplateKeyVector {
    TemplateKey* mpBegin;                                    // +0x00
    TemplateKey* mpEnd;                                      // +0x04
    TemplateKey* mpCap;                                      // +0x08
};
struct ObjectTemplateDB {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    // vtable +0x24: collect the templates matching one constraint round
    virtual void QueryMatchingParts(TemplateKeyVector* pOut, int round, ConstraintNodeVector* pPending);
};
extern ObjectTemplateDB* gObjectTemplateDB;                  // 0x015a5a90
extern "C" void __cdecl CollectUpgradeHead(ConstraintVector* pSlots);      // 0x00e434a0
extern "C" void __cdecl CollectUpgradeBody(ConstraintVector* pSlots);      // 0x00e435c0
extern "C" void __cdecl CollectUpgradeLimb(ConstraintVector* pSlots);      // 0x00e3ede0
extern "C" void __cdecl CollectUpgradeCreature(ConstraintVector* pSlots);  // 0x00e43710
struct EditorValidity {
    char mPad000[0x3f0];
    int  mState;                                             // +0x3f0
    char mPad3f4[0x450 - 0x3f4];
    float mField450;                                         // +0x450
    uchar mDone;                                             // +0x454
    char mPad455[0x45c - 0x455];
    int  mCell;                                              // +0x45c
    ConstraintVector mUpgradeSlots;                          // +0x460
    char mPad46c[0x474 - 0x46c];
    TemplateKey* mpOutBegin;                                 // +0x474
    TemplateKey* mpOutEnd;                                   // +0x478
    char mPad47c[0x494 - 0x47c];
    float mField494;                                         // +0x494
    float mField498;                                         // +0x498
    uchar mCancelled;                                        // +0x49c
    char mPad49d[0x4f0 - 0x49d];
    TimedPropertyPart mPart4f0;                              // +0x4f0
    uchar mField508;                                         // +0x508
    char mPad509[0x510 - 0x509];
    TimedPropertyPart mPart510;                              // +0x510
    uchar mField528;                                         // +0x528
    char mPad529[0x530 - 0x529];
    TimedPropertyPart mPart530;                              // +0x530
    TimedPropertyPart mPart548;                              // +0x548

    bool UpdateA();                                          // 0x00e36cd0
    bool UpdateB();                                          // 0x00e36d30
    bool UpdateC();                                          // 0x00e36d80
    bool StepBack();                                         // 0x00e38bb0
    bool Step();                                             // 0x00e38c90
    void StartFadeOut();                                     // 0x00e390d0
    void ShowValidity();                                     // 0x00e39200
    bool PushUpgrade();                                      // 0x00e3b0b0
    void RefreshLayout();                                    // 0x00e40420

    void CommitUpgradeSlots();                               // 0x004f6b70.. (slot range commit)
    void AddCellUpgradeParts(int cell);                      // 0x00e44d20
    void Tick();                                             // 0x00e45460
};
const int kMaxUpgradeParts = 15;
const int kCellUpgradeHead     = 0x1654c00;
const int kCellUpgradeHeadAlt  = 0x1654c01;
const int kCellUpgradeBody     = 0x1654c02;
const int kCellUpgradeLimb     = 0x1654c04;
const int kCellUpgradeCreature = 0x1654c05;
// ---- items of slice s00e44d20 end

// ---- items of slice s00e45760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  __cdecl SP_WindowManager();                                       // 0x0067caa0
extern "C" void*  __cdecl SP_MessageServer();                                       // 0x0067dcc0
extern "C" void*  __cdecl SP_GetCurrentGameMode();                                  // 0x00b5b800
extern "C" void   __cdecl SP_GetPropertyAsKeyInstance(int obj, int key, void* out); // 0x006a12a0
extern "C" void   __cdecl SP_GetPropertyAsText(int obj, int key, void* out);        // 0x006a1360
extern "C" bool   __cdecl GetBoolProperty(int obj, int key, void* out);             // 0x00407190
extern "C" void   __cdecl SetGlobalProperty(int key, float v);                      // 0x005ca880
extern "C" float  __cdecl FUN_005a6e00(float v);                                   // 0x005a6e00 Clamp01
extern "C" void*  __cdecl f_b3d410(int a);                                          // 0x00b3d410
extern "C" void   __cdecl FUN_00808b20(void* a, void* b, char c);                   // 0x00808b20
extern "C" void   __cdecl FUN_005e4560(void* a, void* b);                           // 0x005e4560
extern "C" void*  __cdecl FUN_005e2cb0(void* a);                                    // 0x005e2cb0
extern "C" void   __cdecl FUN_005e2ca0(void* a);                                    // 0x005e2ca0
extern "C" void   __cdecl CPL_ctor(void* self);                                     // 0x008286d0
extern "C" void   __cdecl FUN_00e3b390(void* evt, int a, int b);                    // 0x00e3b390
extern uint8_t DAT_015a5a85;                                // 0x015a5a85
extern float   DAT_015a5a88;                                // 0x015a5a88
extern float   DAT_015a5a8c;                                // 0x015a5a8c
extern float   DAT_015a5a90;                                // 0x015a5a90
extern int     DAT_015a5b30;                                // 0x015a5b30
typedef unsigned int uintptr_t;
struct Object_s00e4_5760 {
    virtual int  AddRef();                 // +0x00 0x00432a50
    virtual int  Release();                // +0x04
    virtual void ScalarDeletingDtor();     // +0x08
};
struct Rect  { float x, y, z, w; };
struct Point { float x; float y; };
struct IWindow_s00e4_5760 : Object_s00e4_5760 {
    virtual void pad0c();                              // +0x0c
    virtual IWindow_s00e4_5760* GetParent();                      // +0x10
    virtual void pad14();                              // +0x14
    virtual void pad18();                              // +0x18
    virtual void pad1c();                              // +0x1c
    virtual void pad20();                              // +0x20
    virtual void pad24();                              // +0x24
    virtual void pad28();                              // +0x28
    virtual void pad2c();                              // +0x2c
    virtual void pad30();                              // +0x30
    virtual const Rect* GetArea();                     // +0x34
    virtual const Rect* GetRealArea();                 // +0x38
    virtual void pad3c();                              // +0x3c
    virtual void pad40();                              // +0x40
    virtual void pad44();                              // +0x44
    virtual void pad48();                              // +0x48
    virtual void pad4c();                              // +0x4c
    virtual void pad50();                              // +0x50
    virtual void pad54();                              // +0x54
    virtual void pad58();                              // +0x58
    virtual void SetShadeColor(uint32_t c);            // +0x5c
    virtual void pad60();                              // +0x60
    virtual void pad64();                              // +0x64
    virtual void pad68();                              // +0x68
    virtual void SetLayoutArea(const Rect& r);         // +0x6c
    virtual void SetLayoutLocation(float x, float y);  // +0x70
    virtual void pad74();                              // +0x74
    virtual void pad78();                              // +0x78
    virtual void SetEnabled(int a, int b);             // +0x7c
    virtual void pad80();                              // +0x80
    virtual void pad84();                              // +0x84
    virtual void pad88();                              // +0x88
    virtual void pad8c();                              // +0x8c
    virtual void pad90();                              // +0x90
    virtual void pad94();                              // +0x94
    virtual void pad98();                              // +0x98
    virtual void pad9c();                              // +0x9c
    virtual void padA0();                              // +0xa0
    virtual void padA4();                              // +0xa4
    virtual void padA8();                              // +0xa8
    virtual void padAc();                              // +0xac
    virtual void padB0();                              // +0xb0
    virtual void padB4();                              // +0xb4
    virtual void padB8();                              // +0xb8
    virtual void padBc();                              // +0xbc
    virtual Point ToGlobalCoordinates(Point p);        // +0xc0
    virtual Point ToLocalCoordinates(Point p);         // +0xc4
    virtual void padC8();                              // +0xc8
    virtual void padCc();                              // +0xcc
    virtual void padD0();                              // +0xd0
    virtual void padD4();                              // +0xd4
    virtual void AddWindow(IWindow_s00e4_5760* w);                // +0xd8
    virtual void RemoveWindow(IWindow_s00e4_5760* w);             // +0xdc
};
struct IRectOwner : IWindow_s00e4_5760 {
    // vtable +0x38 is IWindow::GetRealArea
};
class cSPUILayout_s00e4_5760 : public Object_s00e4_5760 { public:
    IWindow_s00e4_5760* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    bool     Init();                                        // 0x00828250
    void     FUN_00827fa0(int key, int val);                // 0x00827fa0
    void*    AsInterface(int id);                           // 0x00828020
    IWindow_s00e4_5760* GetRootWindow();                               // 0x00828100
};
class cSPUIPropertyLayout_s00e4_5760 : public cSPUILayout_s00e4_5760 { public:
    void SetRootWindowId(uint32_t id);                      // 0x00c87bc0
    char InitLayout(int* param);                            // 0x00e462c0
    uint32_t OnLayoutMessage(int a, int* msg);              // 0x00e463d0
};
struct AnimatorS { void Update(); };                        // 0x007f63b0
struct LimitStopwatch {
    bool IsTimeUp();                                        // 0x005ff1c0
};
struct cCameraManager {
    int ActiveControllerIndex();                            // 0x0098f940
};
struct RenderCtx {
    void* Begin2D(void* mode);                              // 0x0095bc10
    void  End2D();                                          // 0x0095bb20
};
struct IntVector { uint8_t pad00[0x0c]; int* begin; int* end; int* cap; void resize(uint32_t n); };
struct cSPUITimeline_s00e4_5760 {
    uint8_t       pad000[0x0c];             // +0x00
    cSPUILayout_s00e4_5760*  mpLayout0c;               // +0x0c
    cSPUIPropertyLayout_s00e4_5760* mpLayout10;        // +0x10
    cSPUIPropertyLayout_s00e4_5760* mpLayout14;        // +0x14
    uint8_t       pad018[0x08];             // +0x18
    IWindow_s00e4_5760*      mpWin20;                  // +0x20
    uint8_t       pad024[0x14];             // +0x24
    IWindow_s00e4_5760*      mpWindow1;                // +0x38
    uint8_t       pad03c[0x0c];             // +0x3c
    IWindow_s00e4_5760*      mpWindow2;                // +0x48
    uint8_t       pad04c[0x04];             // +0x4c
    void*         mpField50;                // +0x50
    IRectOwner*   mpView54;                 // +0x54
    IRectOwner*   mpView58;                 // +0x58
    uint8_t       pad05c[0x28];             // +0x5c
    float         m_f84;                    // +0x84
    float         m_f88;                    // +0x88
    uint8_t       pad08c[0x1c];             // +0x8c
    uint32_t      m_fieldA8;                // +0xa8
    uint8_t       pad0ac[0x30];             // +0xac
    float         m_f_dc;                   // +0xdc
    uint8_t       mb_e0;                    // +0xe0
    uint8_t       pad0e1[0x03];             // +0xe1
    uint32_t      m_fieldE4;                // +0xe4
    uint8_t       pad0e8[0x20];             // +0xe8
    uint8_t       mb108;                    // +0x108
    uint8_t       pad109[0x77];             // +0x109
    int*          mpArr180;                 // +0x180
    int*          mpArr184;                 // +0x184
    uint8_t       pad188[0xbd];             // +0x188
    uint8_t       mb245;                    // +0x245
    uint8_t       pad246[0x02];             // +0x246
    float         m_f248;                   // +0x248
    uint8_t       pad24c[0x1c];             // +0x24c
    uint8_t       mb268;                    // +0x268
    uint8_t       mb269;                    // +0x269
    uint8_t       pad26a[0x02];             // +0x26a
    float         m_f26c;                   // +0x26c
    float         m_f270;                   // +0x270
    uint8_t       pad274[0xd8];             // +0x274
    LimitStopwatch m_stopwatch;             // +0x34c
    uint8_t       pad350[0x1c];             // +0x350
    uint8_t       mb36c;                    // +0x36c
    uint8_t       mb36d;                    // +0x36d
    uint8_t       pad36e[0xe6];             // +0x36e
    AnimatorS*    mpAnimator;               // +0x454
    uint8_t       pad458[0x30];             // +0x458
    uint8_t       mb488;                    // +0x488

    bool  DoMessage(int cmd, int* msg);                     // 0x00e45760
    float FUN_00e460d0();                                   // 0x00e460d0
    void  FUN_00e46140(void* out);                          // 0x00e46140
    void  FUN_00e46180(void* out);                          // 0x00e46180
    void  GetItemColor(void* out, uint32_t idx);            // 0x00e461c0
    void  SetItemColor(uint32_t idx, unsigned char on);    // 0x00e46210
};
struct cTimelinePanel {
    void  BeginCloseTimeline();                             // 0x00e37970
    bool  FUN_00e37750();                                   // 0x00e37750
    void  FUN_00e37f90(void* out, int idx, int which);      // 0x00e37f90
    void* FUN_00e37e50(int idx, int which);                 // 0x00e37e50
    void  FUN_00e400f0(float v);                            // 0x00e400f0
    bool  FUN_00e3c1a0(void* a, void* b, void* c, void* d,
                       int e, int f, int g, float h);       // 0x00e3c1a0
    void  FUN_00e423a0(int a);                              // 0x00e423a0
    void  FUN_00e45460();                                   // 0x00e45460
    void  FUN_00e3afb0();                                   // 0x00e3afb0
    void  FUN_00e38240();                                   // 0x00e38240
    void  Show(int a);                                      // 0x00e44200
    void  FUN_00e3b390(void* evt, int a, int b);            // 0x00e3b390
    void  FUN_00e37d70(float v);                            // 0x00e37d70
};
static inline cTimelinePanel* BASE(cSPUITimeline_s00e4_5760* self) {
    return (cTimelinePanel*)((char*)self - 4);
}
struct VecContainer;                                        // 0x00e45fe0 (member: IsMember)
struct VisNode;                                             // 0x00e46020 (member: SetVisibleRecursive)
void FUN_00e45e90(int a1, IntVector* out, uint32_t key, int obj);  // 0x00e45e90
struct PropLayoutCtor;                                     // 0x00e46260 (member: Construct)
struct Vector3  { float x, y, z; };
struct VecContainer {
    bool IsMember(int id);                                  // 0x00e45fe0
};
struct VisNode {
    void SetVisibleRecursive(char on);                      // 0x00e46020
};
struct PropLayoutCtor {
    cSPUIPropertyLayout_s00e4_5760* Construct();                       // 0x00e46260
};
// ---- items of slice s00e45760 end

// ---- items of slice s00e46600 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier(void);
extern "C" __declspec(dllimport) double __cdecl ceil(double x);
extern "C" void* PTR_AddRef_01482370;   // 0x1482370
extern "C" void* PTR_FUN_01482360;      // 0x1482360
extern "C" void* PTR_AddRef_014823a8;   // 0x14823a8
extern "C" void* PTR_FUN_01482398;      // 0x1482398
extern "C" void* PTR_AddRef_013ec458;   // 0x13ec458
extern "C" void* PTR_AddRef_013eb938;   // 0x13eb938
extern "C" float  DAT_013f4fd0;         // 0x13f4fd0
extern "C" float  DAT_013f6a30;         // 0x13f6a30
extern "C" float  DAT_01485720;         // 0x1485720
extern "C" float  DAT_01471064;         // 0x1471064
extern "C" void*  gEmptyString16;       // 0x1667bac
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
void  __cdecl operator_delete(void* p);                                      // 0xf47380  ??3
struct CPL { void dtor(); };                                                 // 0x828670  ??1CPL
struct Helper4b { void dtor(); };                                            // 0x4b5440
struct EaVector { int dtor(); };                                             // 0xae6970
struct PropObj {
    u8* GetBool();      // 0x41e920  Property::GetBool
};
struct GmeGlobal {                                                           // 0xe37f30 (thiscall, 1 arg, ret 4)
    float FUN_00e37f30(void* arg);
};
struct CString {
    u32 a, b, c, d, e;
    void  ctor();                                        // 0x6b5060
    void  dtor();                                        // 0x6b5240
    int   Load(u32 a, u32 b, int c);                     // 0x6b54b0
    u16*  GetText();                                     // 0x6b55c0
};
struct WString {
    void Assign(const u16* begin, const u16* end);       // 0x423650
};
void* __cdecl SP_GlobalGet();                                                // 0xb3d410 (returns *(void**)0x167eb28)
void* __cdecl cSPUILayout_FindWindowByID(void* layout, u32 id, int b);       // 0x8105b0
struct Vec2 { float x, y; };
extern "C" u32    DAT_01667bae;         // 0x1667bae
struct Timeline;
struct Timeline {
    u8  pad00[0x10];
    void* p10;      // +0x10  layout A
    void* p14;      // +0x14  layout B
    u8  pad18[4];
    void* p1c;      // +0x1c
    void* p20;      // +0x20
    u8  pad24[0x44];
    u32 id68;       // +0x68
    u8  b6c;        // +0x6c
    u8  b6d;        // +0x6d
    u8  pad6e[2];
    float f70;      // +0x70
    float f74;      // +0x74
    float f78;      // +0x78
    float f7c;      // +0x7c
    float f80;      // +0x80
    float f84;      // +0x84
    void* p88;      // +0x88
    void* p8c;      // +0x8c
    u32   u90;      // +0x90
    u8  pad94[0x14];
    void* pa8;      // +0xa8
    u8  padac[0x14];
    void* pc0;      // +0xc0   vector begin
    void* pc4;      // +0xc4   vector end
    u32   ucc;      // +0xc8
    u8  padd0[8];
    u32   ud4;      // +0xd4
    u32   ud8;      // +0xd8
    float fdc;      // +0xdc
    u8  be0;        // +0xe0
    u8  pade1[3];
    u32   ue4;      // +0xe4
    u32   ue8;      // +0xe8
    u8  bec;        // +0xec
    u8  bed;        // +0xed
    u8  padee[2];
    u32   uf0;      // +0xf0
    u8  bf4;        // +0xf4
    u8  padf5[3];
    float ff8;      // +0xf8
    float ffc;      // +0xfc
    float f100;     // +0x100
    float f104;     // +0x104
    u8  b108;       // +0x108
    u8  b109;       // +0x109

    void FUN_00e46600(void* p2, int p3, u32 p4, u32 p5);
    void FUN_00e46880(int p2);
    void FUN_00e46d80(float a, float b, bool c, float d, float e, bool f);
    void* FUN_00e470a0(void* out);
    bool  FUN_00e47100(void* out);
    void  FUN_00e47460();
    float FUN_00e460d0();   // 0xe460d0
    void  FUN_00e48fa0(void* a, float b, u32 c, float d);   // 0xe48fa0
};
struct SPUIPropertyLayout {
    void* vtbl0;    // +0x00
    void* vtbl1;    // +0x04
    u32   u08;      // +0x08
    u32   u0c;      // +0x0c
    u32   u10;      // +0x10
    u32   u14;      // +0x14
    u32   u18;      // +0x18
    u32   u1c;      // +0x1c
    u32   u20;      // +0x20
    u32   u24;      // +0x24
    u32   u28;      // +0x28
    u32   u2c;      // +0x2c
    u32   u30;      // +0x30
    u8    pad34[8];
    u32   u3c;      // +0x3c
    u32   u40;      // +0x40
    u32   u44;      // +0x44
    u8    pad48[8];
    u32   u50;      // +0x50
    u32   u54;      // +0x54
    u32   u58;      // +0x58
    u8    pad5c[8];
    u32   u64;      // +0x64
    u32   u68;      // +0x68
    u8    b6c;      // +0x6c
    u8    b6d;      // +0x6d
    u8    pad6e[2];
    float f70;      // +0x70
    float f74;      // +0x74
    u8    pad78[0x10];
    u32   u88;      // +0x88
    u32   u8c;      // +0x8c
    u32   u90;      // +0x90
    u8    pad94[4];
    u32   u98;      // +0x98
    u32   u9c;      // +0x9c
    u32   ua0;      // +0xa0
    u32   ua4;      // +0xa4
    u32   ua8;      // +0xa8
    u32   uac;      // +0xac
    u32   ub0;      // +0xb0
    u32   ub4;      // +0xb4
    u8    padb8[8];
    u32   uc0;      // +0xc0
    u32   uc4;      // +0xc4
    u32   uc8;      // +0xc8
    u8    padcc[8];
    u32   ud4;      // +0xd4
    u32   ud8;      // +0xd8
    float fdc;      // +0xdc
    u8    be0;      // +0xe0
    u8    pade1[3];
    u32   ue4;      // +0xe4
    u8    padf0[4];
    u8    bec;      // +0xec
    u8    bed;      // +0xed
    u8    padee[2];
    u32   uf0;      // +0xf0
    u8    bf4;      // +0xf4
    u8    padf5[0x13];
    u8    b108;     // +0x108
    u8    b109;     // +0x109

    void* FUN_00e471e0();           // ctor body (returns this in eax)
    void  FUN_00e47300();           // dtor body
    void* FUN_00e47180(u8 flags);   // deleting destructor
};
#define VTOBJ(o)  (*(void***)(o))
// ---- items of slice s00e46600 end

// ---- items of slice s00e47520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char DAT_013f6b3c[];                                // 0x13f6b3c "UI"
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct IWindow_s00e4_7520 {
    PV8 PV4 PV2                              // +0x00..+0x34  slots 0..13
    virtual float* Rect();                   // +0x38  slot 14 -> {x,y,w,h}
    PV8 PV4 PV2                              // +0x3c..+0x70  slots 15..28
    virtual void   Resize(float w, float h); // +0x74  slot 29
    PV                                       // +0x78  slot 30
    virtual void   Slot7C(int a, int b);     // +0x7c  slot 31
};
struct WString_s00e4_7520 {                             // eastl::basic_string<wchar_t>
    const wchar_t* mBegin;                   // +0x00
    const wchar_t* mEnd;                     // +0x04
    const wchar_t* mCapacity;                // +0x08
    void RangeInitialize(const wchar_t* s);  // 0x579a90
};
struct cString {                             // SP::cString
    void* mData[9];                          // 0x24 bytes
    cString();                               // 0x6b5060
    ~cString();                              // 0x6b5240
    const wchar_t* GetText();                // 0x6b55c0
};
struct Variant {                             // EA::Variant
    char          mPad[0x10];                // +0x00..+0x0f
    unsigned char mFlags;                    // +0x10
    char          mPad2[3];                  // +0x11..+0x13
    Variant(const WString_s00e4_7520& src);             // 0x5a74a0
    void Destruct(bool free);                // 0x93db80
};
struct A8Inner {                             // descriptor reached through +0xa8
    int   m00;                               // +0x00
    float m04;                               // +0x04
};
struct ObjA8 {                               // per-property timeline entry
    char     mPad[0x0c];                     // +0x00..+0x0b
    A8Inner* m0C;                            // +0x0c
};
struct PtrVec {                              // SPVector<ObjA8*> at +0xac
    ObjA8** mBegin;                          // +0x00
    ObjA8** mEnd;                            // +0x04
    ObjA8** mCap;                            // +0x08
    void assignSlow(const PtrVec& src);      // 0xb8ef40
};
struct PL;                                   // cSPUIPropertyLayout
struct ARVec {                               // SPVector<AutoRefCount> at +0xc0
    PL** mBegin;                             // +0x00
    PL** mEnd;                               // +0x04
    PL** mCap;                               // +0x08
    void DoInsertPtr(PL** pos, PL* const& v); // 0xaea5d0
};
struct PL {
    virtual void AddRef();                   // +0x00  slot 0
    virtual void Release();                  // +0x04  slot 1

    char     mPad04[0x18];                   // +0x04..+0x1b
    void*    m1c;                            // +0x1c
    void*    m20;                            // +0x20
    char     mPad24[0x44];                   // +0x24..+0x67
    int      m68;                            // +0x68
    char     mPad6c[0x0c];                   // +0x6c..+0x77
    IWindow_s00e4_7520* m78;                            // +0x78
    IWindow_s00e4_7520* m7c;                            // +0x7c
    IWindow_s00e4_7520* m80;                            // +0x80
    char     mPad84[0x24];                   // +0x84..+0xa7
    ObjA8*   mA8;                            // +0xa8
    PtrVec   mVec;                           // +0xac..+0xb7
    char     mPadB8[0x08];                   // +0xb8..+0xbf
    ARVec    mRefs;                          // +0xc0..+0xcb
    char     mPadCC[0x08];                   // +0xcc..+0xd3
    int      mD4;                            // +0xd4
    char     mPadD8[0x04];                   // +0xd8..+0xdb
    float    mDC;                            // +0xdc
    char     mE0;                            // +0xe0
    char     mPadE1[0x03];                   // +0xe1..+0xe3
    int      mE4;                            // +0xe4
    char     mPadE8[0x05];                   // +0xe8..+0xec
    char     mED;                            // +0xed

    void   SetFlag(int v);                                  // 0x828020
    void   func20h();                                       // 0x828740
    void   Fn828c30(void* key, Variant* v, int a, int b);   // 0x828c30
    void   Fn46600(void* timeline, int e, unsigned a, unsigned b); // 0xe46600
    PL*    Fn471e0();                                       // 0xe471e0
    float  Fn460d0();                                       // 0xe460d0
    char   Fn46140(cString* s);                             // 0xe46140
    char   Fn46180(cString* s);                             // 0xe46180
    void   Fn3cf60(PL* t);                                  // 0xe3cf60
    double Fn37d70(float f);                                // 0xe37d70

    void FUN_00e47520(int flag, PL* t);
    void FUN_00e47700(PtrVec* src);
};
struct AutoRef {
    PL* mpObject;
    AutoRef(PL* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0xf473a0
void  __cdecl FUN_00806e40(void* win, int a, int b);             // 0x806e40
PL*   __cdecl FUN_00b3d410();                                    // 0xb3d410
// ---- items of slice s00e47520 end

// ---- items of slice s00e47930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t* g_015a5b30;
extern wchar_t* g_015a5b50;
void* operator new(unsigned int, const char*, int, int, int, int);
void operator delete[](void*);   // 0x00f47380
struct IWinProc { virtual void wp0(); };
struct Key3 { uint32_t a, b, c; };
struct KeyPtr { int a, b, c; void* d; };
struct V3 { float x, y, z; };
template <class T> struct AutoRef_s00e4_7930 {
    T* p;
    void Set(T* n) { T* o = p; if (n != o) { if (n) n->AddRef(); p = n; if (o) o->Release(); } }
    void Clear() { T* o = p; if (o) { p = 0; o->Release(); } }
};
struct Prop {
    void* data;
    char pad[0xc];
    uint16_t flags;    // +0x10
    int16_t type;      // +0x12
};
struct IPropList;
struct IWindow_s00e4_7930 {
    virtual void AddRef();
    virtual void Release();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
    virtual float* GetRect();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
    virtual void SetColor(uint32_t c);
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
    virtual void SetPos(float x, float y);
    virtual void SetSize(float w, float h);
    virtual void p30();
    virtual void SetFlag(int f, bool v);
    virtual void SetCaption(const wchar_t* s);
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
virtual void p47();
virtual void p48();
virtual void p49();
virtual void p50();
virtual void p51();
virtual void p52();
virtual void p53();
virtual void p54();
virtual void p55();
virtual void p56();
virtual void p57();
virtual void p58();
virtual void p59();
    virtual IWindow_s00e4_7930* FindChild(uint32_t id, bool b);
virtual void p61();
virtual void p62();
virtual void p63();
virtual void p64();
    virtual void AddWinProc(IWinProc* p);
};
class cSPUILayout_s00e4_7930 { public:
    virtual void p0();
    virtual void AddRef();
    virtual void Release();
    cSPUILayout_s00e4_7930();                                  // 0x00810000
    IWindow_s00e4_7930* FindWindowByID(uint32_t id, int b);   // 0x008105b0
    void Init(Key3* k, int a, uint32_t b);          // 0x008120d0
    void SetParentWin(void* w, int a, uint32_t b);  // 0x008121b0
};
struct IPropList {
    virtual void AddRef();
    virtual void Release();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
    virtual bool GetProperty(uint32_t id, Prop** out);
};
struct IPropMgr {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
    virtual bool Get(uint32_t a, uint32_t b, AutoRef_s00e4_7930<IPropList>* out);
};
struct IEffectCtl {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
    virtual IWinProc* GetWinProc();
    virtual void p5();
    virtual void SetDuration(float f);
    virtual void p7();
    virtual void SetA(int a);
    virtual void p9();
    virtual void SetXY(float x, float y);
    virtual void p11();
    virtual void SetB(int a);
    virtual void p13();
    virtual void SetC(float f);
};
struct Effect {
    virtual void AddRef();
    virtual void Release();
};
struct InflateEffect : Effect {
    char padA[8];
    IEffectCtl ctl;            // +0x0c (embedded interface with its own vptr)
    char pad[0x60 - 0x10];
    IEffectCtl ctl2;           // +0x60
    char pad2[0xb8 - 0x64];
    InflateEffect* Construct();   // 0x0097e690
};
struct FadeEffect : Effect {
    char padA[8];
    IEffectCtl ctl;            // +0x0c
    char pad[0x60 - 0x10];
    FadeEffect* Construct();      // 0x0096f060
};
struct Effect2 {               // 0xa0 bytes
    virtual void AddRef();
    virtual void Release();
    char pad[0xa0 - 4];
    Effect2();                                       // 0x006775f0
    void Setup(IWindow_s00e4_7930* w, int a, int b);            // 0x00677220
    void Apply(int a, Key3* k, int b);               // 0x00677700
};
struct AssetData {
    virtual void p0();
    virtual void Init(KeyPtr* k);
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
    virtual int Check();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
    virtual void SetFlag(int a);
    virtual void SetKind(uint32_t k);
    struct RefIface { virtual void AddRef(); virtual void Release(); };
    char pad[0xc];
    RefIface ref;              // +0x10
    char pad2[0xb0 - 0x14];
    AssetData();               // 0x00dd0ca0 / 0x00dd0da0
};
struct AssetDataRef {
    AssetData* p;
    void Assign(AssetData* d);   // 0x006428c0
};
struct AssetView {
    virtual void AddRef();
    virtual void Release();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
    virtual void Init(IWindow_s00e4_7930* w, AssetData* d, int a, int b);
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
    virtual void Fn(int a, int b);
    char pad[0x28 - 4];
    IWindow_s00e4_7930* sub;              // +0x28
    AssetView();               // 0x00657f70
};
struct DataHelper {
    void Fn5950(void* mgr, void* entry, int idx);   // 0x005e5950
};
struct VerbIconData {
    virtual void AddRef();
    virtual void Release();
    virtual void p2();
    virtual DataHelper* Get(uint32_t k);
    virtual void Set(IPropList* p);
    char pad[0xa8 - 4];
    Key3 key;                  // +0xa8
    VerbIconData();            // 0x005e5b60
};
struct Rollover { void SetVisibility(uint32_t a, int b); };            // 0x006052c0
struct VerbIcon {
    virtual void AddRef();
    virtual void Release();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
    virtual void Init(IWindow_s00e4_7930* w, Key3 key, VerbIconData* d, int a, int b, uint32_t c, int d2, int e);
    VerbIcon();                // 0x005e2000
    IWindow_s00e4_7930* GetIconWindow();  // 0x007f54d0
    float Fn2910(int a);       // 0x005e2910
    Rollover* Fn2cb0();        // 0x005e2cb0
};
struct ResObj {
    const wchar_t* Fn0880();   // 0x00550880
    const wchar_t* Fn4e10();   // 0x00414e10
};
struct IResult {
    virtual void AddRef();
    virtual void Release();
    virtual void p2();
    virtual ResObj* Find(uint32_t id);
};
struct IResMan {
virtual void p0();
virtual void p1();
virtual void p2();
    virtual bool Get(Key3* k, AutoRef_s00e4_7930<IResult>* out, int a, int b, int c, int d);
};
struct cString_s00e4_7930 {
    uint32_t b[4];
    cString_s00e4_7930();                 // 0x006b5060
    ~cString_s00e4_7930();                // 0x006b5240
    const wchar_t* GetText();  // 0x006b55c0
};
template <class T> struct RefVec {
    T** begin; T** end; T** cap;
    void DoInsertValue(T** pos, T** val);
    void push(T*& v) {
        T** e = end;
        if (e < cap) { end = e + 1; if (e) { *e = v; if (v) v->AddRef(); } }
        else DoInsertValue(e, &v);
    }
};
struct V3Vec {
    V3* begin; V3* end; V3* cap;
    V3* Erase(V3* a, V3* b);                 // 0x009e0480
    void DoInsertValue(V3* pos, V3* v);      // 0x004b5ad0
};
struct OwnerInfo {
    char pad[0x2c];
    uint32_t colA;     // +0x2c
    uint32_t colB;     // +0x30
    char pad2[0x64 - 0x34];
    uint32_t resKey;   // +0x64
    uint32_t imgBase;  // +0x68
};
struct Owner { char pad[0xc]; OwnerInfo* info; };
struct cEditorVerbIconPanel;
struct UIMgr {
    char pad[0x48];
    void* f48;
    uint32_t GetModeId();                       // 0x00e3b5d0
    bool IsReady(cEditorVerbIconPanel* p);      // 0x00e3cf60
    const uint32_t* GetColor(int n);            // 0x00e36fb0
    void SetImage(IWindow_s00e4_7930* w, Key3* k);         // 0x00e3b2a0
    void* FindParent(uint32_t id);              // 0x00e40670
};
struct SpeciesEntry { char pad[0x130]; IPropList* props; };
struct SpeciesMgr { char pad[0x6d4]; SpeciesEntry** begin; SpeciesEntry** end; };
struct SpeciesRoot { SpeciesMgr* Get(); };     // 0x004df550
struct DT { void Set(int a); };                // 0x0092e3d0
struct TLocal : DT { uint32_t dt2[2]; void* arr; void* e; void* c; };
UIMgr* GetUIMgr();                                                  // 0x00b3d410
IPropMgr* PropertyManager();                                        // 0x0067de30
IResMan* GetManager();                                              // 0x0067dcd0
bool GetArrayKeys(IPropList* p, uint32_t id, int* count, Key3** keys);   // 0x006a0ae0
bool TryGetUIntProperty(IPropList* p, uint32_t id, uint32_t* out);  // 0x00410370
bool GetPropertyAsText(IPropList* p, uint32_t id, cString_s00e4_7930* s);      // 0x006a1360
bool GetPropertyAsKeyInstance(IPropList* p, uint32_t id, uint32_t* out);  // 0x006a12a0
bool GetPropertyAsKey(IPropList* p, uint32_t id, Key3* out);        // 0x006a1250
bool GetPropertyAsColorRGB(IPropList* p, uint32_t id, V3* out);     // 0x006a11b0
void SetNumberString(int64_t v, wchar_t* buf, int n);               // 0x00881ae0
void SetWindowImage(IWindow_s00e4_7930* w, Key3* k, int a);                    // 0x00807bb0
void SetWindowScale(IWindow_s00e4_7930* w, float s);                           // 0x00808210
void SetImageFromLayout(IWindow_s00e4_7930* w, cSPUILayout_s00e4_7930* l, uint32_t id, int a);   // 0x00806a60
uint32_t ColorFromId(uint32_t id);                                  // 0x00b6f0d0
SpeciesRoot* GetSpeciesRoot(KeyPtr* k);                             // 0x00401090
void FillTimelineData(Owner* o, TLocal* t, uint32_t inst, IPropList* p);  // 0x00e45e90
void FillKey(Owner* o, int a, Key3* k);                             // 0x00e39420
void* GetAlloc();                                                   // 0x009512c0
void* EAAlloc(unsigned int size, int align, const char* name, void* alloc);   // 0x009512d0
struct cEditorVerbIconPanel {
    char pad0[0xc];
    AutoRef_s00e4_7930<cSPUILayout_s00e4_7930> mLayout;       // +0x0c
    AutoRef_s00e4_7930<cSPUILayout_s00e4_7930> mLayoutB;      // +0x10
    AutoRef_s00e4_7930<cSPUILayout_s00e4_7930> mLayoutA;      // +0x14
    char pad18[4];
    uint32_t mParentId;                 // +0x1c
    AutoRef_s00e4_7930<IWindow_s00e4_7930> mWinIcon;          // +0x20
    AutoRef_s00e4_7930<IWindow_s00e4_7930> mWinText;          // +0x24
    RefVec<IWindow_s00e4_7930> mWindows;           // +0x28
    char pad34[8];
    RefVec<Effect2> mEffects;           // +0x3c
    char pad48[8];
    V3Vec mColors;                      // +0x50
    char pad5c[8];
    AutoRef_s00e4_7930<IPropList> mProps;          // +0x64
    uint32_t mId;                       // +0x68
    char pad6c[4];
    float mW;                           // +0x70
    float mH;                           // +0x74
    char pad78[0x10];
    const wchar_t* mCaption;            // +0x88
    char pad8c[0xc];
    AutoRef_s00e4_7930<AssetView> mView;           // +0x98
    AssetDataRef mData;                 // +0x9c
    AutoRef_s00e4_7930<VerbIconData> mIconData;    // +0xa0
    AutoRef_s00e4_7930<VerbIcon> mIcon;            // +0xa4
    Owner* mOwner;                      // +0xa8
    char padac[0x28];
    int mCountA;                        // +0xd4
    int mCountB;                        // +0xd8
    char paddc[8];
    uint32_t mE4;                       // +0xe4
    uint32_t mE8;                       // +0xe8
    char padec[4];
    uint32_t mF0;                       // +0xf0

    void RefreshUI();                   // 0x00e47930
    void Fn7100(KeyPtr* k);             // 0x00e47100
};
// ---- items of slice s00e47930 end

// ---- items of slice s00e48bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint32_t u32_s00e4_8bb0;
struct Key3_s00e4_8bb0 { u32_s00e4_8bb0 a, b, c; };
struct V2 { float x, y; };
struct CSpuiLayout {
    void Shutdown(u32_s00e4_8bb0 flag);                                     // 0x811ad0
    bool Init(const Key3_s00e4_8bb0* k, int a, u32_s00e4_8bb0 b);                      // 0x8120d0
    bool SetParentWin(void* w, int a, u32_s00e4_8bb0 b);                    // 0x8121b0
    void SetReloadCallback(void (*fn)(void*, void*), void* self); // 0x810090
};
struct LayoutRef { CSpuiLayout* p; void Set(CSpuiLayout*); };    // 0x572620
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef char   (__thiscall *VFC2)(void*, int, void*);
typedef char   (__thiscall *VFC3)(void*, int, void*, void*);
typedef float* (__thiscall *VFR0)(void*);
#define VTP(p) (*(void***)(p))
#define CALL0(p, i)           ((VF0)VTP(p)[(i)])((void*)(p))
#define CALL1(p, i, a)        ((VF1)VTP(p)[(i)])((void*)(p), (int)(a))
#define CALL2(p, i, a, b)     ((VF2)VTP(p)[(i)])((void*)(p), (int)(a), (int)(b))
#define CALL3(p, i, a, b, c)  ((VF3)VTP(p)[(i)])((void*)(p), (int)(a), (int)(b), (int)(c))
#define CALLG2(p, i, a, b)    ((VFC2)VTP(p)[(i)])((void*)(p), (int)(a), (void*)(b))
#define CALLG3(p, i, a, b, c) ((VFC3)VTP(p)[(i)])((void*)(p), (int)(a), (void*)(b), (void*)(c))
#define CALLR0(p, i)          ((VFR0)VTP(p)[(i)])((void*)(p))
struct PtrSlot {
    void* p;
    void Release()
    {
        if (p) {
            void* q = p;
            p = 0;
            CALL0(q, 1);
        }
    }
};
struct PtrVec_s00e4_8bb0 {  // 0xe25bd0
    void* begin;
    void* end;
    void* cap;
    void Erase(void*, void*);
};
struct SpVecF { float* begin; float* end; float* cap; void resize(int); };      // 0x4afc80
void* __cdecl EAAllocate(u32_s00e4_8bb0 size, const char* name, int a, int b,
                         const char* file, int line);            // 0xf473a0
void* __cdecl VecInsert(void* dst, const void* src, u32_s00e4_8bb0 n);      // 0x11e0744
void* __cdecl memmove_(void* d, const void* s, u32_s00e4_8bb0 n);
void* __cdecl PropertyManager_s00e4_8bb0();                                 // 0x67de30
void* __cdecl MessageServer();                                   // 0x67dcc0
void* __cdecl GetGlobal();                                       // 0xb3d410
void* __fastcall LayoutCtor(void* p);                             // 0x810000
void  __cdecl FillKey(void* a, int b, void* out);                // 0xe39420
void  __cdecl SetImageOnWin(void* w, void* img, int idx);        // 0x8068d0
bool  __cdecl GetPropertyAsKeyInstance(void* p, u32_s00e4_8bb0 id, void* out); // 0x6a12a0
bool  __cdecl GetPropertyAsText(void* p, u32_s00e4_8bb0 id, void* out);     // 0x6a1360
void  __cdecl FormatNum(double v, void* buf, int n, const wchar_t* fmt, int x); // 0x8822e0
void  __cdecl ReloadCB(void* a, void* b);                        // 0xe48da0
extern "C" u32_s00e4_8bb0 g_015a5b30_s00e4_8bb0;
struct Prop_s00e4_8bb0 {
    float* GetFloat();                                           // 0x41ea70
    u32_s00e4_8bb0*   GetUInt();                                            // 0x41ea00
    int*   GetInt();                                             // 0x41e990
};
struct CString_s00e4_8bb0 {
    u32_s00e4_8bb0 d[5];
    void ctor();                                                 // 0x6b5060
    void dtor();                                                 // 0x6b5240
    const wchar_t* GetText();                                    // 0x6b55c0
};
struct Timeline_s00e4_8bb0 {
    void FUN_00e46600(void* key, int a, int b, int c);           // 0xe46600
    void FUN_00e46d80(float a, float b, int c, float d, float e, int f); // 0xe46d80
};
struct TexWrap {
    int GetWidth(int h);                                         // 0x8332a0
    int GetHeight(float a, float b, float c, float d, int e);    // 0x8332d0
};
struct ImageObj {
    void* Construct(void* src, int w, int h);                    // 0x9579f0
};
struct ImageBase {
    ImageBase* Construct(void* parent);                          // 0x8333b0
};
struct AbilHost {
    void SetVehicle(Key3_s00e4_8bb0 k);                                     // 0x59ece0
    void LayoutAbilitiesCompact(void* obj, int b, void* out);    // 0x5a1920
};
struct KeyMgr { void* Resolve(void* key); };                     // 0xe3ec20
struct LayoutObj { void* GetF1(void* out, void* child); };       // 0xe40010
struct C;
struct C {
    void Shutdown();                                             // 0xe48bb0
    void Setup();                                                // 0xe48dc0
    void Load(int a, int b, int c, int d);                       // 0xe48eb0
    void SetOwner(int a, int b, int c, int d);                   // 0xe48f30
    void ShutdownRecursive();                                    // 0xe48f60
    void LayoutChildren(void* v2, int a, int b, float f);        // 0xe48fa0
    void Close();                                                // 0xe492d0
    void SetX(void* p);                                          // 0xe49360
    void RefreshBig(int a, int b, int c);                        // 0xe493c0
    void LoadParams();                                           // 0xe496d0
    void RefreshUI();                                            // 0xe47930
    void SetVisibleRecursive(u8 vis);                            // 0xe46020
};
struct BlkVec {
    int   base;
    u32_s00e4_8bb0   cap;
    int   pad08;
    int   firstObj;
    int   firstEnd;
    int   cur;
    int   pad18;
    int   lastObj;
    int   lastEnd;
    int   end;
    void InsertRange(u32_s00e4_8bb0 n, int atEnd);
    void Init(u32_s00e4_8bb0 n);
};
template <class T> const T& maxref(const T& a, const T& b)
{
    return a < b ? b : a;
}
// ---- items of slice s00e48bb0 end

// ---- items of slice s00e49a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_15a5b54;                // 0x015a5b54: rotation angle
extern float g_15a5b58;                // 0x015a5b58: extra rotation offset
extern char g_vtbl_01482478[];      // 0x01482478 primary vtable of the panel
extern char g_vtbl_01482468[];      // 0x01482468 secondary vtable of the panel
extern char g_vtbl_013eb394[];      // 0x013eb394 PaintSystem vtable (first base)
extern char g_vtbl_013ec458[];      // 0x013ec458 cContentValidationSummarizer vtable (second base)
extern void* __cdecl FUN_00f473a0(int size, const char* tag, int a, int b, const char* file, int line);  // 0x00f473a0 operator_new
extern void  __cdecl FUN_00f47380(void* p);                                                 // 0x00f47380 operator_delete
struct Key12 { uint32_t a, b, c; };
struct Vec4 {
    float x, y, z, w;
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct IWindow_s00e4_9a40 {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
    virtual const float* GetOffset();                   // +0x34 (two floats)
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
    virtual void SetAnchor(float x, float y);           // +0x70
virtual void w29();
virtual void w30();
    virtual void SetFlag(int flag, bool value);         // +0x7c
};
struct IReleasable { virtual void w0(); virtual void Release(); };   // Release at +4
struct cModel {                                         // result of cMission::GetModel
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
    virtual int GetKind();                              // +0x60
};
struct cMission {
    cModel*  GetModel();                                // 0x00c45ce0
    IWindow_s00e4_9a40* GetPanelWindow();                          // 0x00ff35d0
};
struct cModelPanel {                                    // FUN_00e19cf0(model)
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
    virtual void Notify();                              // +0x78
};
cModelPanel* __cdecl FUN_00e19cf0(cModel* model);       // 0x00e19cf0
struct cSink {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
    virtual void SetActive(int on);                     // +0x28
};
extern cSink* g_169e230;                                // 0x0169e230
struct cImage { uint32_t pad0; uint8_t flags; };        // flags at +4, bit 0 = loaded
struct cResourceManager {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
    virtual cImage* GetImage(Key12 key, int flags);     // +0x1c
};
cResourceManager* __cdecl FUN_0067dd60();               // 0x0067dd60
int __cdecl GetCurrentGameMode();                       // 0x00b5b800
struct cImageRef {
    cImage* p;
    void Set(cImage* img);                              // 0x00576650
};
struct AnimBuf {
    uint32_t d[0x80 / 4];
    void Destroy();                                     // 0x0059a1e0: ~cSPUIWindowAnimation
};
struct cAnimator {
    void RemoveAnimation(IWindow_s00e4_9a40* win, int channel);    // 0x007f6210
    void AddAnimation(AnimBuf* anim, IWindow_s00e4_9a40* win, int flags);   // 0x007f8d10
    void Update();                                      // 0x007f63b0
};
AnimBuf* __cdecl SPUICreateWindowAnimationRotation(AnimBuf* out, IWindow_s00e4_9a40* win, Vec4 rot,
                                                   float duration, float from, int type);   // 0x007f8140
float __cdecl GetElapsedSeconds();                      // 0x00805080
struct Quat { float x, y, z, w; };
void __cdecl SetWindowRotation(IWindow_s00e4_9a40* win, const Quat* quat);   // 0x00808230
struct cSubPanel { void FUN_00e49db0(); };              // 0x00e49db0
struct cMissionPanel {
    char       pad0[0xc];
    char       mbFlag;            // +0x0c
    char       pad1[0x18 - 0xd];
    cMission*  mpMission;         // +0x18
    cImageRef  mImage;            // +0x1c
    IWindow_s00e4_9a40*   mpWindow;          // +0x20
    char       pad2[0x38 - 0x24];
    cSubPanel  mSub;              // +0x38
    char       pad3[0x40 - 0x39];
    Key12*     mpTarget;          // +0x40
    char       pad4[0x50 - 0x44];
    Key12*     mpShown;           // +0x50
    char       pad5[0x88 - 0x54];
    int        mState;            // +0x88
    float      mTimer;            // +0x8c
    cAnimator* mpAnimator;        // +0x90
    float      mDuration;         // +0x94
    float      mDuration2;        // +0x98
    float      mDuration3;        // +0x9c

    void FUN_00e493c0(Key12 key);                       // 0x00e493c0
    void Update(float dt);                              // 0x00e49f80
};
struct Vec4P { float x, y, z, w; };                    // POD vector (Vec4 above has constructors)
struct Key { uint32_t mTypeId, mGroupId, mInstanceId; };                        // EA::ResourceMan::Key
struct IRefCounted {                                    // AddRef +0x00, Release +0x04
    virtual void AddRef();
    virtual void Release();
};
struct IRefCounted2 {                                   // AddRef +0x04, Release +0x08
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
};
struct IWindowRef {                                     // the panel's windows
    virtual void AddRef();                                              // +0x00
    virtual void Release();                                             // +0x04
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
    virtual const Vec4P* GetPosition();                                 // +0x38
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
    virtual void w30();                                                 // +0x78
    virtual void SetFlag(int flag, bool value);                         // +0x7c
};
template <class T> struct RefPtr {                      // ref-counted pointer assignment
    T* mp;
    void Set(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p != 0) p->AddRef();
            mp = p;
            if (old != 0) old->Release();
        }
    }
};
struct cSPUILayout_s00e4_9a40 : IRefCounted2 {
    cSPUILayout_s00e4_9a40* Construct();                                           // 0x00810000 (thiscall, returns this)
    bool Init(const Key& key, bool b, uint32_t id);                     // 0x008120d0 (ret 0xc)
    IWindowRef* FindWindowByID(uint32_t id, bool recursive) const;       // 0x008105b0 (ret 8)
};
struct cVehicleAbilities : IRefCounted2 {
    cVehicleAbilities* Init(int mode);                                  // 0x0059f9e0 (ret 4)
};
struct cMissionCardAnimator {
    cMissionCardAnimator* Init();                                       // 0x007f83e0 (returns this)
};
struct cMessage {                                       // event object handed to FUN_00e49d80
    uint32_t mpad00[6];                                                 // +0x00
    uint32_t mEventType;                                                // +0x18
};
struct IMessageServer {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
    virtual void AddHandler(void* handler, uint32_t id);                // +0x20
};
namespace SP {
 IMessageServer* MessageServer_s00e4_9a40();   // 0x0067dcc0
}
struct cKeyQueue {                                      // +0x38: deque of Key12, pages of 16 items (0xc0 bytes)
    Key12**  mppBase;                                   // +0x00  page map
    int32_t  mnCapacity;                                // +0x04  page map size
    Key12*   mpCur;                                     // +0x08
    Key12*   mpCurPage;                                 // +0x0c
    Key12*   mpCurEnd;                                  // +0x10
    Key12**  mppCurSlot;                                // +0x14
    Key12*   mpBack;                                    // +0x18
    Key12*   mpBackPage;                                // +0x1c
    Key12*   mpBackEnd;                                 // +0x20
    Key12**  mppBackSlot;                               // +0x24
    void FUN_00e49950(int n);                           // 0x00e49950 (ret 4)      constructor
    void FUN_00e49820(int a, int b);                    // 0x00e49820 (ret 8)      grow the page map
    void Destroy();                                     // 0x00996640
    void FUN_00e49db0();
    void FUN_00e49df0(Key12* key);
};
struct cRefBlock {                                      // object at +0x1c: vtable, then its reference count
    void*   mpVtbl;                                     // +0x00
    int32_t mf04;                                       // +0x04
    volatile long mnRefCount;                           // +0x08
};
struct cUnlockPanel {
    void*        mpVtbl;                                // +0x00  PaintSystem vtable
    void*        mpVtbl2;                               // +0x04  cContentValidationSummarizer vtable
    int32_t      mf08;                                  // +0x08  (a member of the second base)
    bool         mbNoMission;                           // +0x0c
    uint8_t      mpad0d[3];                             // +0x0d
    RefPtr<IRefCounted2> mLayout;                       // +0x10
    RefPtr<IRefCounted2> mAbilities;                    // +0x14
    RefPtr<IRefCounted>  mMission;                      // +0x18
    cRefBlock*   mpImage;                               // +0x1c
    RefPtr<IWindowRef> mW20;                            // +0x20
    RefPtr<IWindowRef> mW24;                            // +0x24
    RefPtr<IWindowRef> mW28;                            // +0x28
    RefPtr<IWindowRef> mW2c;                            // +0x2c
    RefPtr<IWindowRef> mW30;                            // +0x30
    RefPtr<IWindowRef> mW34;                            // +0x34
    cKeyQueue    mQueue;                                // +0x38
    uint32_t     mf60;                                  // +0x60
    Vec4P        mPosA;                                 // +0x64  position of mW30
    Vec4P        mPosB;                                 // +0x74  position of mW20
    float        mWidth;                                // +0x84  width difference of the two positions
    int32_t      mState;                                // +0x88
    float        mTimer;                                // +0x8c
    cMissionCardAnimator* mpAnimator;                   // +0x90
    float        mDuration;                             // +0x94
    float        mDuration2;                            // +0x98
    float        mDuration3;                            // +0x9c

    void FUN_00e496d0();                                // 0x00e496d0
    void FUN_00e49a40(IRefCounted* mission);
    bool FUN_00e49d80(int type, cMessage* msg);
    void FUN_00e49e80();
    cUnlockPanel* FUN_00e4a6e0();
    void FUN_00e4a790(Key12 key);
};
// ---- items of slice s00e49a40 end

// ---- items of slice s00e4c9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
int   FUN_008d61e0(void* s);                            // 0x008d61e0 (stdcall, ret 4)
unsigned EA_Hash_FNV1_String16(const void* s, unsigned basis, int a); // 0x00932f30
// ---- items of slice s00e4c9e0 end

// @ 0x00e449b0
bool cSPUITimeline::HandleTimelineMessage(uint32_t msgID, void* payload)
{
    if (msgID != 0x6123dbe) {
        if (msgID == 0x6256b62 && payload != 0) {
            int* data = (int*)payload;
            int kind = data[2];
            mnGameLevel = data[4];
            if (gForceTimelineMode || kind == 1)
                mnShowMode = SP_ConfigManager()->GetChoice(0x4ea96cb) ? 1 : 2;
            Show(1);
            return true;
        }
    } else {
        FUN_0067dd50()->SetNotificationA(0x16, 2);
    }
    return true;
}

// @ 0x00e44a30
void cSPUITimelineShutdown::Destroy()
{
    Body()->Show(0);

    cSPUITimeline* body = Body();
    void* callback = body ? (void*)&mpCallbackTarget : (void*)0;
    cRenderTargetUser* targets = FUN_0067de40()->GetRenderTargets();
    targets->SetCallbackTarget(callback);

    if (IFlaggedRelease* animator = mpAnimatorA) {
        animator->Release(1);
        mpAnimatorA = 0;
    }

    mCellKeys.DoCopy(mCellKeys.mpBegin, mCellKeys.mpEnd);
    mCreatureKeys.DoCopy(mCreatureKeys.mpBegin, mCreatureKeys.mpEnd);

    if (IFlaggedRelease* animator = mpAnimatorB) {
        animator->Release(1);
        mpAnimatorB = 0;
    }

    if (mpTribeWindow)
        mpTribeWindow->SetParent(body ? body->Self() : 0);
    if (mpWindowB)
        mpWindowB->SetParent(body ? body->Self() : 0);
    if (mpCreatureWindow)
        mpCreatureWindow->SetParent(body ? body->Self() : 0);
    if (mpWindowA)
        mpWindowA->SetParent(body ? body->Self() : 0);

    if (mpPaletteItem) {
        mpPaletteItem->Shutdown();
        if (cSPPaletteItem* item = mpPaletteItem) {
            mpPaletteItem = 0;
            item->Delete();
        }
    }
    if (Object* info = mpPaletteInfo) {
        mpPaletteInfo = 0;
        info->Delete();
    }
    if (IWindow* rollover = mpPaletteRollover) {
        rollover->Unload();
        if (IWindow* released = mpPaletteRollover) {
            mpPaletteRollover = 0;
            released->Release();
        }
    }
    if (IWindow* rollover = mpEventRollover) {
        rollover->Unload();
        if (IWindow* released = mpEventRollover) {
            mpEventRollover = 0;
            released->Release();
        }
    }
    if (cTwoBaseObj* rowData = mpRowData) {
        rowData->Delete();
        if (cTwoBaseObj* released = mpRowData) {
            mpRowData = 0;
            released->mSecond.Release();
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (mpRowWindows[i]) {
            if (IWindow* window = mpRowWindows[i]) {
                mpRowWindows[i] = 0;
                window->Release();
            }
        }
        if (mpRowIcons[i]) {
            if (IWindow* icon = mpRowIcons[i]) {
                mpRowIcons[i] = 0;
                icon->Release();
            }
        }
        if (IWindow* extra = mpRowExtras[i]) {
            extra->BeforeRelease();
            if (IWindow* released = mpRowExtras[i]) {
                mpRowExtras[i] = 0;
                released->Release();
            }
        }
    }

    if (cSPUILayout_s00e4_4200* layout = mpLayoutB) {
        layout->Shutdown(1);
        if (cSPUILayout_s00e4_4200* released = mpLayoutB) {
            mpLayoutB = 0;
            released->Delete();
        }
    }
    if (cSPUILayout_s00e4_4200* layout = mpLayoutA) {
        layout->Shutdown(1);
        if (cSPUILayout_s00e4_4200* released = mpLayoutA) {
            mpLayoutA = 0;
            released->Delete();
        }
    }
    if (cSPUILayout_s00e4_4200* layout = mpLayoutC) {
        layout->Shutdown(1);
        if (cSPUILayout_s00e4_4200* released = mpLayoutC) {
            mpLayoutC = 0;
            released->Delete();
        }
    }
    if (cSPUILayout_s00e4_4200* layout = mpLayoutD) {
        layout->Shutdown(1);
        if (cSPUILayout_s00e4_4200* released = mpLayoutD) {
            mpLayoutD = 0;
            released->Delete();
        }
    }

    if (mpMsgServer) {
        void* server = mpMsgServer;
        mpMsgServer = 0;
        EA_Messaging_RemoveHandler(server, mpMsgOwner, mpMsgIDs, mpEffectsHandler,
                                   mMsgFlags);
    }
}

// @ 0x00e44d20
void EditorValidity::AddCellUpgradeParts(int cell)
{
    ConstraintNodeVector pending = { 0, 0, 0 };
    int rounds = 0;

    switch (cell) {
    case kCellUpgradeHead:
        CollectUpgradeHead(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0xdfad9f51));
        rounds = 1;
        break;

    case kCellUpgradeHeadAlt:
        CollectUpgradeHead(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x9ea3031a));
        rounds = 1;
        break;

    case kCellUpgradeBody:
        CollectUpgradeBody(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x372e2c04));
        rounds = 2;
        break;

    case kCellUpgradeLimb:
        CollectUpgradeLimb(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x24682294));
        rounds = 3;
        break;

    case kCellUpgradeCreature:
        CollectUpgradeCreature(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x476a98c7));
        rounds = 3;
        break;

    default:
        return;
    }

    int missing = kMaxUpgradeParts - mUpgradeSlots.Count();
    for (int round = 0; round < rounds && round < missing; ++round) {
        pending.PushBack(Constraint(0x3cc89b1, kEqualConstraint, 0x913b23be));

        TemplateKeyVector keys = { 0, 0, 0 };
        gObjectTemplateDB->QueryMatchingParts(&keys, round, &pending);
        for (TemplateKey* pKey = keys.mpBegin; pKey != keys.mpEnd; ++pKey)
            mUpgradeSlots.PushBack(*pKey);

        // the cell's own fallback constraint is repeated on the first two rounds
        if (cell == kCellUpgradeBody) {
            if (round == 0)
                pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x372e2c04));
        } else if (cell == kCellUpgradeLimb) {
            if (round == 0)
                pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0xccc35c46));
            else if (round == 1)
                pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x2399be55));
        } else if (cell == kCellUpgradeCreature) {
            if (round == 0)
                pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x65672ade));
            else if (round == 1)
                pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x2399be55));
        }
    }

    CommitUpgradeSlots();
}

// @ 0x00e45460
void EditorValidity::Tick()
{
    switch (mState) {
    case 1:
        if (gkHalf < mPart4f0.GetElapsedTimeFloat()) {
            mPart4f0.SetBoolProperty();
            StartFadeOut();
            mState = 2;
        }
        return;

    case 2:
        if (gkHalf < mPart530.GetElapsedTimeFloat()) {
            mPart530.SetBoolProperty();
            mPart548.Restart();
            mState = 3;
        }
        return;

    case 3:
        if (gkSettleTime < mPart548.GetElapsedTimeFloat()) {
            mPart548.SetBoolProperty();
            ShowValidity();
            mState = 4;
        }
        return;

    case 4:
        if (gkHalf < mPart530.GetElapsedTimeFloat()) {
            mPart530.SetBoolProperty();
            mField508 = 1;
            mState = 5;
        }
        return;

    case 5:
        mField494 = mField498 * gkHalf;
        mDone = 0;
        mCancelled = 0;
        gPendingUpgrade = 1;
        PushUpgrade();
        mState = 6;
        return;

    case 6:
        if (UpdateA() && StepBack())
            mState = 8;
        return;

    case 8:
        if (gPendingUpgrade != 0) {
            AddCellUpgradeParts(mCell);
            gPendingUpgrade = 0;
        }
        if (UpdateC()) {
            RefreshLayout();
            mState = 7;
        }
        return;

    case 7:
        if (UpdateC()) {
            if (PushUpgrade()) {
                mState = 6;
            } else {
                mDone = 1;
                mState = 0;
            }
        }
        return;

    case 9:
        if (mCancelled != 0) {
            mDone = 1;
            mState = 0;
            return;
        }
        if (mUpgradeSlots.Count() == 0)
            AddCellUpgradeParts(mCell);
        if (UpdateB()) {
            mField450 = gkHoldTime;
            if (StepBack())
                mState = 11;
        }
        return;

    case 11:
        if (UpdateC()) {
            RefreshLayout();
            mState = 10;
        }
        return;

    case 10:
        if (UpdateC()) {
            if (Step()) {
                mState = 9;
            } else {
                mDone = 1;
                mState = 0;
            }
        }
        return;

    case 12:
        if (gkHalf < mPart510.GetElapsedTimeFloat()) {
            mPart510.SetBoolProperty();
            mField528 = 1;
            mState = 0;
        }
        return;
    }
}

// @ 0x00e45760
bool cSPUITimeline_s00e4_5760::DoMessage(int cmd, int* msg)
{
    cTimelinePanel* base = BASE(this);
    uint32_t uVar10 = *(uint32_t*)((char*)msg + 8);
    bool bVar11;

    if (uVar10 < 7) {
        if (uVar10 == 6) {
            if (*(int*)((char*)msg + 0x18) != 1000)
                return false;
            if (base->FUN_00e37750())
                return false;
            if (cmd == (int)(uintptr_t)mpWindow1) {
                m_f270 = *(float*)((char*)msg + 0xc);
                int* piVar2 = (int*)SP_WindowManager();
                ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x58))(piVar2, 1, (int)(uintptr_t)mpWindow1);
                mb268 = 1;
                return false;
            }
            if (cmd != (int)(uintptr_t)mpWindow2)
                return false;
            {
                int* piVar2 = (int*)SP_WindowManager();
                ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x58))(piVar2, 1, (int)(uintptr_t)mpWindow2);
                Point p = *(Point*)((char*)msg + 0xc);
                Point* r = ((Point*(__thiscall*)(void*, Point))*(void**)(*(int*)mpWindow2 + 0xc4))(mpWindow2, p);
                base->FUN_00e400f0(r->x);
                mb269 = 1;
                return false;
            }
        }
        if (uVar10 != 1)
            return false;
        if (*(int*)((char*)msg + 0x10) != 0x1b && *(int*)((char*)msg + 0x10) != 0x54)
            return false;
        if (*(int*)((char*)msg + 0x14) != 0)
            return false;
        bVar11 = mb36d == 0;
    } else {
        if (uVar10 > 0x287259f6u)
            return false;
        if (uVar10 != 0x287259f6u) {
            switch (uVar10 - 7) {
            case 0:
                goto code_r0x00e45bff;
            case 1:
                if (base->FUN_00e37750())
                    return false;
                if (mb268 != 0 && cmd == (int)(uintptr_t)mpWindow1) {
                    m_f26c = (m_f270 - *(float*)((char*)msg + 0xc)) + m_f26c;
                    m_f270 = *(float*)((char*)msg + 0xc);
                }
                if (mb269 == 0)
                    return false;
                if (cmd != (int)(uintptr_t)mpWindow2)
                    return false;
                {
                    Point p = *(Point*)((char*)msg + 0xc);
                    Point* r = ((Point*(__thiscall*)(void*, Point))*(void**)(*(int*)mpWindow2 + 0xc4))(mpWindow2, p);
                    base->FUN_00e400f0(r->x);
                    return false;
                }
            case 2:
                if (base->FUN_00e37750())
                    return false;
                if (cmd != (int)(uintptr_t)mpWindow1 && cmd != (int)(uintptr_t)mpWindow2)
                    return false;
                m_f26c = (float)*(int*)((char*)msg + 0x18) + m_f26c;
                return false;
            case 5:
                if (cmd == (int)(uintptr_t)mpWindow1) {
                    uint8_t* gm = (uint8_t*)SP_GetCurrentGameMode();
                    if (gm != (uint8_t*)0x01654c00)
                        return false;
                    base->FUN_00e423a0(0x14);
                    return false;
                }
                if (mb36c != 0) {
                    if (mb488 == 0) {
                        base->FUN_00e38240();
                        return false;
                    }
                    base->FUN_00e45460();
                    base->FUN_00e3afb0();
                    mpAnimator->Update();
                    return false;
                }
                if (mb36d == 0)
                    return false;
                if (!m_stopwatch.IsTimeUp())
                    return false;
                mb36d = 0;
                base->Show(0);
                {
                    int* ms = (int*)SP_MessageServer();
                    ((void(__thiscall*)(int*, int, int, int))*(void**)(*ms + 0x14))(ms, 0x4471c60, 0, 0);
                }
                {
                    int* ms = (int*)SP_MessageServer();
                    ((void(__thiscall*)(int*, int, int, int))*(void**)(*ms + 0x14))(ms, 0x445f729, 0, 0);
                }
                return false;
            case 6:
                break;   // big body below
            default:
                return false;
            }

            // case 6 -- 0x00e4587b
            if (cmd != (int)(uintptr_t)mpField50)
                return false;
            if (mpField50 == 0)
                return false;
            if (mb36d != 0)
                return false;

            {
                int* piVar2 = (int*)SP_WindowManager();
                int* p2 = (int*)((int*(__thiscall*)(int*))*(void**)(*piVar2 + 4))(piVar2);
                float* pfVar4 = (float*)((float*(__thiscall*)(int*))*(void**)(*p2 + 0x38))(p2);
                float fStack_4c = pfVar4[2] - pfVar4[0];
                mb245 = 0;

                int iVar8 = (int)(mpArr184 - mpArr180);
                uint32_t uStack_58 = (uint32_t)iVar8;
                int iStack_54 = 0;
                if (iVar8 > 0) {
                    uint32_t u = 0;
                    do {
                        int iVar5 = ((cCameraManager*)mpArr180[u])->ActiveControllerIndex();
                        if (iVar5 != 0) {
                            float fStack_38;
                            base->FUN_00e37f90(&fStack_38, u, 0);
                            if (0.0f <= fStack_38) {
                                int* wm = (int*)SP_WindowManager();
                                int* wp = (int*)((int*(__thiscall*)(int*))*(void**)(*wm + 4))(wm);
                                float* rf = (float*)((float*(__thiscall*)(int*))*(void**)(*wp + 0x38))(wp);
                                if (fStack_38 <= rf[2] - rf[0]) {
                                    if ((int)u < (int)uStack_58)
                                        uStack_58 = u;
                                    if (iStack_54 < (int)u)
                                        iStack_54 = (int)u;
                                }
                            }
                        }
                        ++u;
                    } while ((int)u < iVar8);
                }

                float fStack_34 = 0.0f;
                if (mpView58 != 0) {
                    int* pv = (int*)mpView58;
                    float* pfVar4b = (float*)((float*(__thiscall*)(void*, int, int))*(void**)(*pv + 0xc0))(pv, 0, 0);
                    fStack_34 = pfVar4b[1];
                    float fStack_38 = pfVar4b[0];
                    SetGlobalProperty(0x2f304a54, (m_f84 - fStack_38) / fStack_4c);
                    m_f84 = fStack_38;
                    m_f88 = fStack_34;
                }

                RenderCtx* pRVar9 = *(RenderCtx**)((char*)msg + 0x18);
                void* uStack_50 = pRVar9->Begin2D(0);
                int iStack_48 = iStack_54 + 1;
                int j = (int)uStack_58 - 1;
                if (j <= iStack_48) {
                    do {
                        if (j > 0 && j < (int)(mpArr184 - mpArr180)) {
                            int iVar5 = ((cCameraManager*)mpArr180[j])->ActiveControllerIndex();
                            DAT_015a5a85 = iVar5 != 0 ? 1 : 0;
                        }
                        if (DAT_015a5a85 != 0) {
                            float fStack_54 = 1.0f;
                            cCameraManager* pcVar6 = (cCameraManager*)base->FUN_00e37e50(j, 0);
                            if (pcVar6 != 0 && *(int*)((char*)pcVar6 + 0xe4) == (int)0xbeb528cb) {
                                int idx = ((cCameraManager*)pcVar6)->ActiveControllerIndex();
                                if (idx != 0) {
                                    fStack_54 = (float)FUN_005a6e00(*(float*)(*(int*)(idx + 0xc) + 100));
                                }
                            }
                            float fStack_3c, fStack_40, fStack_38;
                            base->FUN_00e37f90(&fStack_38, j, -2);
                            base->FUN_00e37f90(&fStack_3c, j, -1);
                            base->FUN_00e37f90(&uStack_50, j, 0);
                            base->FUN_00e37f90(&fStack_40, j, 1);
                            if (fStack_38 == fStack_40) {
                                fStack_40 = fStack_40 + 300.0f;
                                fStack_3c = fStack_34;
                            }
                            bool cVar1 = base->FUN_00e3c1a0(&fStack_38, &fStack_38, &fStack_38, &fStack_40,
                                                            (int)(uintptr_t)uStack_50, 1, (int)uStack_58, fStack_54);
                            if (cVar1 != 0) {
                                base->FUN_00e3c1a0(&fStack_38, &fStack_38, &fStack_38, &fStack_40,
                                                   (int)(uintptr_t)uStack_50, 0, (int)uStack_58, fStack_54);
                            }
                        }
                        ++j;
                    } while (j <= iStack_48);
                }
                pRVar9->End2D();

                if (mpView58 == 0)
                    return false;
                if (mpView54 == 0)
                    return false;
                if (mb245 != 0)
                    return false;
                {
                    int* pv = (int*)mpView54;
                    float* pfVar4c = (float*)((float*(__thiscall*)(void*))*(void**)(*pv + 0x38))(pv);
                    if (*pfVar4c <= fStack_4c * 0.5f)
                        return false;
                }
                {
                    int* p58 = *(int**)&mpView58;
                    int iVar8b = *p58;
                    float* puVar3 = (float*)((float*(__thiscall*)(int*))*(void**)(iVar8b + 0x38))(p58);
                    ((void(__thiscall*)(void*, float, float))*(void**)(iVar8b + 0x70))(p58, puVar3[0], m_f248);
                }
                return false;
            }
        }
        bVar11 = *(int*)((char*)msg + 0xc) == 0x446e560;
    }
    if (!bVar11)
        return false;
    base->BeginCloseTimeline();
    return true;

code_r0x00e45bff:
    if (*(int*)((char*)msg + 0x18) != 1000)
        return false;
    if (base->FUN_00e37750())
        return false;
    if (cmd == (int)(uintptr_t)mpWindow1) {
        int* piVar2 = (int*)SP_WindowManager();
        ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x5c))(piVar2, 1, (int)(uintptr_t)mpWindow1);
        mb268 = 0;
        return false;
    }
    if (cmd != (int)(uintptr_t)mpWindow2)
        return false;
    {
        int* piVar2 = (int*)SP_WindowManager();
        ((void(__thiscall*)(int*, int, int))*(void**)(*piVar2 + 0x5c))(piVar2, 1, (int)(uintptr_t)mpWindow2);
        mb269 = 0;
        return false;
    }
}

// @ 0x00e45e90
void FUN_00e45e90(int a1, IntVector* out, uint32_t key, int obj)
{
    uint8_t* self = (uint8_t*)a1;
    bool bVar2 = (key == 0x1e4cfa6d) || (key == 0x94995d55u);
    uint32_t uVar1 = *(uint32_t*)(*(int*)(self + 0xc) + 0x2c + (uint32_t)(bVar2 ? 0 : 1) * 4);
    uint32_t uVar4 = 0;
    uint32_t param_3 = 0;
    SP_GetPropertyAsKeyInstance(obj, 0x91ad064, &param_3);

    int param_1 = (int)uVar1;
    if (param_3 < 0xad56080du) {
        if (param_3 == 0xad56080cu) {
            uVar4 = 1;
        } else if (param_3 == 0x2db6dad3u) {
            uVar4 = 5;
        }
    } else if (param_3 == 0xbeb528cbu) {
        uVar4 = 4;
    } else if (param_3 == 0xf71fa311u) {
        uVar4 = 2;
        if (**(int**)(self + 0xc) == 0x7ae0330d) {
            param_1 = 2;
            uVar4 = 1;
        }
    }

    out->resize(0xc);
    int step = (-(uint32_t)bVar2 & 0xfffffffd);
    *(uint32_t*)((char*)out->begin + 0x00) = *(uint32_t*)(*(int*)(self + 0xc) + 8);
    *(uint32_t*)((char*)out->begin + 0x04) = *(uint32_t*)(*(int*)(self + 0xc) + (step + 6) * 4);
    *(uint32_t*)((char*)out->begin + 0x08) = *(uint32_t*)(*(int*)(self + 0xc) + (step + 7) * 4);
    *(uint32_t*)((char*)out->begin + 0x0c) = *(uint32_t*)(*(int*)(self + 0xc) + (step + 8) * 4);
    *(uint32_t*)((char*)out->begin + 0x10) = 0;
    *(uint32_t*)((char*)out->begin + 0x14) = *(uint32_t*)(*(int*)(self + 0xc) + 100);
    *(uint32_t*)((char*)out->begin + 0x18) = uVar4;
    *(uint32_t*)((char*)out->begin + 0x1c) = (uint32_t)param_1;
    *(uint32_t*)((char*)out->begin + 0x20) = 0xffffffffu;
    *(uint32_t*)((char*)out->begin + 0x24) = *(uint32_t*)(*(int*)(self + 0xc) + ((bVar2 ? 0 : 1) + 9) * 4);
}

// @ 0x00e45fe0
bool VecContainer::IsMember(int id)
{
    int* self = (int*)this;
    int n = (*(int*)((char*)self + 0xc4) - *(int*)((char*)self + 0xc0)) >> 2;
    for (int i = 0; i < n; ++i) {
        if (*(int*)(*(int*)((char*)self + 0xc0) + i * 4) == id)
            return true;
    }
    return false;
}

// @ 0x00e46020
void VisNode::SetVisibleRecursive(char on)
{
    char* self = (char*)this;
    self[0x6c] = on;
    uint32_t flag = (*(int*)(self + 0xc0) == *(int*)(self + 0xc4)) ? (uint32_t)(uint8_t)on : 0u;
    int* p20 = *(int**)(self + 0x20);
    if (p20 != 0)
        ((void(__thiscall*)(int*, int, uint32_t))*(void**)(*p20 + 0x7c))(p20, 1, flag);
    cSPUILayout_s00e4_5760* p10 = *(cSPUILayout_s00e4_5760**)(self + 0x10);
    if (p10 != 0) {
        int* w = (int*)p10->FindWindowByID(0x55541be1, true);
        if (w != 0)
            ((void(__thiscall*)(int*, int, uint32_t))*(void**)(*w + 0x7c))(w, 1, flag);
    }
    cSPUILayout_s00e4_5760* p14 = *(cSPUILayout_s00e4_5760**)(self + 0x14);
    if (p14 != 0) {
        int* w = (int*)p14->FindWindowByID(0x355430a0, true);
        if (w != 0)
            ((void(__thiscall*)(int*, int, uint32_t))*(void**)(*w + 0x7c))(w, 1, flag);
    }
    int count = (int)(*(int*)(self + 0xc4) - *(int*)(self + 0xc0)) >> 2;
    int i = 0;
    if (count > 0) {
        int* arr = *(int**)(self + 0xc0);
        do {
            ((VisNode*)*(char**)(arr + i * 4))->SetVisibleRecursive(on);
            ++i;
        } while (i < count);
    }
}

// @ 0x00e460d0
float cSPUITimeline_s00e4_5760::FUN_00e460d0()
{
    if (mb_e0 != 0)
        return m_f_dc;
    float v;
    if (*(int*)((char*)this + 0xa8) == 0)
        v = 0.0f;
    else
        v = *(float*)(*(int*)(*(int*)((char*)this + 0xa8) + 0xc) + 4);

    int iVar1 = (int)f_b3d410(0);
    if (iVar1 != 0 && *(int*)((char*)this + 0xe4) != (int)0xbeb528cb) {
        f_b3d410(0);
        ((cTimelinePanel*)this)->FUN_00e37d70(v);
    }
    return v;
}

// @ 0x00e46140
void cSPUITimeline_s00e4_5760::FUN_00e46140(void* out)
{
    int obj = *(int*)((char*)this + 0x64);
    if (obj != 0) {
        if (mb108 != 0) {
            SP_GetPropertyAsText(obj, 0xd5624e29, out);
            return;
        }
        SP_GetPropertyAsText(obj, 0x66e8f2d2, out);
    }
}

// @ 0x00e46180
void cSPUITimeline_s00e4_5760::FUN_00e46180(void* out)
{
    int obj = *(int*)((char*)this + 0x64);
    if (obj != 0) {
        if (mb108 != 0) {
            SP_GetPropertyAsText(obj, 0xd5624e2a, out);
            return;
        }
        SP_GetPropertyAsText(obj, 0x74f7a11b, out);
    }
}

// @ 0x00e461c0
void cSPUITimeline_s00e4_5760::GetItemColor(void* outv, uint32_t idx)
{
    float* out = (float*)outv;
    out[0] = DAT_015a5a88;
    out[1] = DAT_015a5a8c;
    out[2] = DAT_015a5a90;
    if (idx <= 2) {
        Vector3* p = (Vector3*)(*(int*)((char*)this + 0x50) + idx * 0xc);
        *(Vector3*)out = *p;
    }
}

// @ 0x00e46210
void cSPUITimeline_s00e4_5760::SetItemColor(uint32_t idx, unsigned char on)
{
    if (idx <= 2 && *(int*)((char*)this + 0xc) != 0) {
        cSPUILayout_s00e4_5760* lay = *(cSPUILayout_s00e4_5760**)((char*)this + 0xc);
        int* w = (int*)lay->FindWindowByID(idx + 0x6527160, true);
        if (w != 0) {
            uint32_t n = (uint32_t)(-(int32_t)(on ? 1 : 0));
            uint32_t color = (n & 0x8c8c8cu) + 0xff737373u;
            ((void(__thiscall*)(int*, uint32_t))*(void**)(*w + 0x5c))(w, color);
        }
    }
}

// @ 0x00e46260
cSPUIPropertyLayout_s00e4_5760* PropLayoutCtor::Construct()
{
    cSPUIPropertyLayout_s00e4_5760* self = (cSPUIPropertyLayout_s00e4_5760*)this;
    CPL_ctor(self);
    *(uint32_t*)((char*)self + 0x00) = 0x1482370;
    *(uint32_t*)((char*)self + 0x04) = 0x1482360;
    *(uint32_t*)((char*)self + 0x78) = 0;
    *(uint32_t*)((char*)self + 0x7c) = 0;
    *(uint32_t*)((char*)self + 0x80) = 0;
    self->FUN_00827fa0(0x5adf0be7, DAT_015a5b30);
    self->SetRootWindowId(0x94e2c6d2);
    return self;
}

// @ 0x00e462c0
char cSPUIPropertyLayout_s00e4_5760::InitLayout(int* param)
{
    cSPUIPropertyLayout_s00e4_5760* self = this;
    char c = self->Init();
    if (c != 0) {
        self->AsInterface(0);
        cSPUILayout_s00e4_5760* lay = (cSPUILayout_s00e4_5760*)((char*)self + 0xc);
        int* w;
        int* old;

        w = (int*)lay->FindWindowByID(0x94e2c6d2, true);
        old = *(int**)((char*)self + 0x78);
        if (w != old) {
            if (w != 0)
                ((void(__thiscall*)(int*))*(void**)*w)(w);
            *(int**)((char*)self + 0x78) = w;
            if (old != 0)
                ((void(__thiscall*)(int*))*(void**)(*old + 4))(old);
        }
        if (*(int**)((char*)self + 0x78) != 0 && param != 0) {
            int* p78 = *(int**)((char*)self + 0x78);
            int r = ((int(__thiscall*)(int*))*(void**)(*p78 + 0x10))(p78);
            if (r == 0)
                ((void(__thiscall*)(int*, int))*(void**)(*param + 0xd8))(param, (int)(uintptr_t)p78);
        }
        w = (int*)lay->FindWindowByID(0x674b828, true);
        old = *(int**)((char*)self + 0x7c);
        if (w != old) {
            if (w != 0)
                ((void(__thiscall*)(int*))*(void**)*w)(w);
            *(int**)((char*)self + 0x7c) = w;
            if (old != 0)
                ((void(__thiscall*)(int*))*(void**)(*old + 4))(old);
        }
        if (*(int**)((char*)self + 0x7c) != 0) {
            int* p7c = *(int**)((char*)self + 0x7c);
            ((void(__thiscall*)(int*, int, int))*(void**)(*p7c + 0x7c))(p7c, 1, 0);
        }

        w = (int*)lay->FindWindowByID(0x60c6eb8, true);
        old = *(int**)((char*)self + 0x80);
        if (w != old) {
            if (w != 0)
                ((void(__thiscall*)(int*))*(void**)*w)(w);
            *(int**)((char*)self + 0x80) = w;
            if (old != 0)
                ((void(__thiscall*)(int*))*(void**)(*old + 4))(old);
        }
    }
    return c;
}

// @ 0x00e463d0
uint32_t cSPUIPropertyLayout_s00e4_5760::OnLayoutMessage(int a, int* msg)
{
    uint8_t* self = (uint8_t*)this;
    uint32_t result = 0;
    switch (*(uint32_t*)((char*)msg + 8)) {
    case 6: case 7: case 8: case 9: {
        int v = (int)f_b3d410(0);
        if (*(int*)(v + 0x3c) == 0)
            break;
        int uVar2 = *(int*)((char*)msg + 0xc);
        int* piVar3 = *(int**)(self + 0x20);
        int uVar1 = *(int*)((char*)msg + 0x10);
        int iVar7 = (int)f_b3d410(0);
        int* piVar4 = *(int**)(iVar7 + 0x3c);
        uint32_t loc[8];
        ((void(__thiscall*)(int*, uint32_t*, int, int))*(void**)(*piVar3 + 0xc0))(piVar3, loc, uVar2, uVar1);
        uint32_t loc2[8];
        ((void(__thiscall*)(int*, uint32_t*))*(void**)(*piVar4 + 0xc4))(piVar4, loc2);
        for (int i = 0; i < 7; ++i)
            loc2[i] = *(uint32_t*)((char*)msg + i * 4);
        int iVar8 = (int)f_b3d410(0);
        result = ((uint32_t(__thiscall*)(int*, int, uint32_t*))*(void**)(*(int*)(iVar8 + 4) + 0x18))(*(int**)(iVar8 + 4), *(int*)(iVar8 + 0x3c), loc2);
        break;
    }
    case 0x1b: {
        uint8_t flag = 0;
        result = (uint32_t)GetBoolProperty(*(int*)(self + 0x64), 0x95503503, &flag);
        if ((char)result != 0 && flag != 0) {
            if (*(int*)(self + 0xa4) == 0) {
                int* p1 = *(int**)((char*)msg + 4);
                int v = ((int(__thiscall*)(int*))*(void**)(*p1 + 0x1c))(p1);
                if (v == 0x94e2c6d2) {
                    int* eax = (int*)f_b3d410(1);
                    FUN_00e3b390(eax, (int)(uintptr_t)self, (int)(uintptr_t)p1);
                }
            } else {
                FUN_005e4560(*(void**)(self + 0xa4), *(void**)(self + 0x20));
                cSPUIPropertyLayout_s00e4_5760* pcVar6 = (cSPUIPropertyLayout_s00e4_5760*)FUN_005e2cb0(*(void**)(self + 0xa4));
                if (pcVar6 != 0) {
                    void* root = pcVar6->GetRootWindow();
                    FUN_00808b20(*(void**)(self + 0x20), root, 0);
                }
            }
        }
        result &= 0xffffff00u;
        break;
    }
    case 0x1c: {
        uint8_t flag = 0;
        result = (uint32_t)GetBoolProperty(*(int*)(self + 0x64), 0x95503503, &flag);
        if ((char)result != 0 && flag != 0) {
            if (*(int*)(self + 0xa4) != 0) {
                FUN_005e2ca0(*(void**)(self + 0xa4));
                result &= 0xffffff00u;
                break;
            }
            int* p1 = *(int**)((char*)msg + 4);
            int v = ((int(__thiscall*)(int*))*(void**)(*p1 + 0x1c))(p1);
            if (v == 0x94e2c6d2) {
                int* eax = (int*)f_b3d410(0);
                FUN_00e3b390(eax, (int)(uintptr_t)self, (int)(uintptr_t)p1);
            }
        }
        result &= 0xffffff00u;
        break;
    }
    default:
        result &= 0xffffff00u;
        break;
    }
    return result & 0xffffff00u;
}

// @ 0x00e46880
void Timeline::FUN_00e46880(int param_2)
{
    float fStack_34 = this->ff8;
    float fVar10 = this->ffc;
    if (this->p20 != 0) {
        float* pf = (float*)((void* (*)(void*))VTOBJ(this->p20)[0x38 / 4])(this->p20);
        fStack_34 = pf[0];
        fVar10 = pf[1];
    }
    float fVar1 = (float)param_2;
    if (param_2 < 0)
        fVar1 = fVar1 + DAT_013f4fd0;
    float local_10 = 0.0f;
    if (0.0f <= fVar1 * DAT_013f6a30)
        local_10 = fVar1 * DAT_013f6a30;
    if (DAT_01485720 <= local_10)
        local_10 = DAT_01485720;
    fStack_34 = (this->ff8 - fStack_34) * local_10 + fStack_34;
    ceil((double)((this->ffc - fVar10) * local_10 + fVar10));
    ceil((double)fStack_34);
    float fStack_20 = this->ff8;
    float fStack_1c = this->ffc;
    if (this->p20 != 0) {
        ((void (*)(void*, float, float))VTOBJ(this->p20)[0x70 / 4])(this->p20, fStack_20, fStack_1c);
    }
    if (this->p10 != 0) {
        if (SP_GlobalGet() != 0) {
            void* piVar4 = cSPUILayout_FindWindowByID(this->p10, 0x55541be1, 1);
            if (this->p20 != 0) {
                if (piVar4 != 0) {
                    if (((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4) != 0) {
                        void* piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                        ((void (*)(void*))VTOBJ(piVar5)[0xe8 / 4])(piVar5);
                        piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                        int iVar3 = ((int (*)(void*))VTOBJ(piVar5)[0x38 / 4])(piVar5);
                        fStack_20 = *(float*)(iVar3 + 4);
                        float fStack_18 = *(float*)(iVar3 + 0xc);
                        float* pf = (float*)((void* (*)(void*))VTOBJ(this->p20)[0x38 / 4])(this->p20);
                        float unaff_EBX = pf[0];
                        float fStack_30 = pf[2];
                        pf = (float*)((void* (*)(void*))VTOBJ(piVar4)[0x38 / 4])(piVar4);
                        fVar10 = pf[2];
                        fVar1 = pf[0];
                        local_10 = 0.0f;
                        float fStack_8 = fStack_18 - fStack_20;
                        float fStack_24 = (fStack_30 + unaff_EBX) * DAT_01471064;
                        void* uVar6 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                        void* g = SP_GlobalGet();
                        float fVar9 = ((GmeGlobal*)g)->FUN_00e37f30(uVar6);
                        float fStack_14 = fStack_24 - (fVar10 - fVar1) * DAT_01471064 + fVar9;
                        float fStack_c = fStack_14 + (fVar10 - fVar1);
                        ((void (*)(void*, float*))VTOBJ(piVar4)[0x6c / 4])(piVar4, &fStack_14);
                        (void)fStack_c;
                    }
                }
            }
        }
    }
    if (this->p14 != 0) {
        void* piVar4 = cSPUILayout_FindWindowByID(this->p14, 0x355430a0, 1);
        if (this->p20 != 0) {
            if (((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20) != 0) {
                if (piVar4 != 0) {
                    if (((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4) != 0) {
                        if (SP_GlobalGet() != 0) {
                            void* piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                            int iVar3 = ((int (*)(void*))VTOBJ(piVar5)[0x38 / 4])(piVar5);
                            fStack_1c = *(float*)(iVar3 + 4);
                            float* pf = (float*)((void* (*)(void*))VTOBJ(this->p20)[0x38 / 4])(this->p20);
                            local_10 = pf[0];
                            float fStack_8 = pf[2];
                            pf = (float*)((void* (*)(void*))VTOBJ(piVar4)[0x38 / 4])(piVar4);
                            fVar10 = pf[2];
                            fVar1 = pf[0];
                            iVar3 = ((int (*)(void*))VTOBJ(piVar4)[0x38 / 4])(piVar4);
                            fStack_34 = *(float*)(iVar3 + 0xc) - *(float*)(iVar3 + 4);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20);
                            iVar3 = ((int (*)(void*))VTOBJ(piVar5)[0x38 / 4])(piVar5);
                            float fStack_24 = fStack_1c - *(float*)(iVar3 + 4);
                            fStack_20 = (fStack_8 + local_10) * DAT_01471064 - (fVar10 - fVar1) * DAT_01471064;
                            fStack_34 = fStack_20 + (fVar10 - fVar1);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20);
                            u32* puVar7 = (u32*)((void* (*)(void*, float*, float, float))VTOBJ(piVar5)[0xc0 / 4])(piVar5, &local_10, fStack_20, fStack_24);
                            u32 uStack_2c = puVar7[0];
                            u32 uStack_28 = puVar7[1];
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(this->p20)[0x10 / 4])(this->p20);
                            ((void (*)(void*, float*, float, float))VTOBJ(piVar5)[0xc0 / 4])(piVar5, &fStack_1c, 0.0f, fStack_8);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                            ((void (*)(void*, u32*, float, float))VTOBJ(piVar5)[0xc4 / 4])(piVar5, &uStack_28, 0.0f, fStack_34);
                            piVar5 = (void*)((void* (*)(void*))VTOBJ(piVar4)[0x10 / 4])(piVar4);
                            iVar3 = ((int (*)(void*, float*, float, float))VTOBJ(piVar5)[0xc4 / 4])(piVar5, &fStack_34, 0.0f, fVar10);
                            fStack_34 = *(float*)(iVar3 + 4);
                            ((void (*)(void*, float*))VTOBJ(piVar4)[0x6c / 4])(piVar4, &fStack_34);
                            (void)uStack_2c;
                        }
                    }
                }
            }
        }
    }
    {
        int iVar3 = (*(int*)((char*)this + 0xc4) - *(int*)((char*)this + 0xc0)) >> 2;
        for (int i = 0; i < iVar3; i++) {
            Timeline* c = *(Timeline**)(*(int*)((char*)this + 0xc0) + i * 4);
            c->FUN_00e46880(param_2);
        }
    }
}

// @ 0x00e46d80
void Timeline::FUN_00e46d80(float a, float b, bool c, float d, float e, bool f)
{
    float fVar5;
    this->ff8 = a;
    if (this->p1c == 0) {
        fVar5 = 0.0f;
    } else {
        int iVar2 = ((int (*)(void*))VTOBJ(this->p1c)[0x38 / 4])(this->p1c);
        fVar5 = *(float*)(iVar2 + 0xc) - *(float*)(iVar2 + 4);
    }
    float fVar4 = this->FUN_00e460d0();
    u32 uVar1 = (u32)c;
    float fVar7 = *(float*)((char*)this + 0x70);
    float fVar6 = fVar7 * DAT_01471064;
    float fVar8 = fVar4 * fVar5 * DAT_01471064 + fVar5 * DAT_01471064 - fVar6;
    if (*(int*)((char*)this + 0xa8) == 0 || *(char*)((char*)this + 0xec) == 0) {
        this->ffc  = b;
        this->f100 = *(float*)((char*)this + 0x74) * DAT_01471064 + this->ff8;
        this->f104 = fVar6 + b;
    } else {
        this->f100 = *(float*)((char*)this + 0x74) * DAT_01471064 + this->ff8;
        this->f104 = fVar6 + fVar8;
        if (!f) {
            float t2 = (fVar5 - fVar7) - (*(float*)((char*)this + 0x84) - fVar7);
            float t1 = fVar8;
            float neg7c = -*(float*)((char*)this + 0x7c);
            if (t1 <= neg7c)
                t1 = neg7c;
            if (t2 <= t1)
                t1 = t2;
            this->ffc = t1;
        } else {
            this->ffc = fVar8;
        }
    }
    this->ff8 += d;
    this->ffc += e;
    if (c && this->p20 != 0) {
        ((void (*)(void*, float, float))VTOBJ(this->p20)[0x70 / 4])(this->p20, this->ff8, this->ffc);
    }
    if (*(int*)((char*)this + 0x68) == 0x6701aff5) {
        this->FUN_00e48fa0(&a, fVar4, uVar1, fVar8);
        return;
    }
    {
        int iVar2 = (*(int*)((char*)this + 0xc4) - *(int*)((char*)this + 0xc0)) >> 2;
        if (iVar2 > 0) {
            float fVar7b = (float)(iVar2 - 1) * DAT_01471064;
            float fVar7c = ((float)(iVar2 - 1) * -DAT_01471064) * *(float*)((char*)this + 0x70) + fVar8;
            float fVar8b = ((float)iVar2 - fVar7b) * *(float*)((char*)this + 0x70) + fVar8;
            float local_38 = 0.0f;
            if (0.0f <= fVar7c) {
                if (fVar5 < fVar8b)
                    local_38 = fVar5 - fVar8b;
            } else {
                local_38 = -fVar7c;
            }
            for (int i = 0; i < iVar2; i++) {
                Timeline* el = *(Timeline**)(*(int*)((char*)this + 0xc0) + i * 4);
                el->FUN_00e46d80(a, b, c, 0.0f, ((float)i - fVar7b) * *(float*)((char*)this + 0x70) + local_38, true);
            }
        }
    }
}

// @ 0x00e470a0
void* Timeline::FUN_00e470a0(void* out)
{
    Vec2* o = (Vec2*)out;
    o->x = this->f100;
    o->y = this->f104;
    void* c = this->p1c;
    if (c != 0) {
        Vec2 v = *o;
        Vec2 tmp;
        ((void (__thiscall*)(void*, Vec2*, Vec2))(*(void***)c)[0xc0 / 4])(c, &tmp, v);
        *o = v;
    }
    return out;
}

// @ 0x00e47100
bool Timeline::FUN_00e47100(void* out)
{
    u32* o = (u32*)out;
    void* c = *(void**)((char*)this + 0x64);
    void* prop;
    if (c != 0
        && *(u32*)((char*)this + 0xa8) != 0
        && ((char (__thiscall*)(void*, u32, void*))(*(void***)c)[0x24 / 4])(c, 0xb5147b8c, &prop)
        && *(u16*)((char*)prop + 0x12) == 1
        && *((PropObj*)prop)->GetBool() != 0) {
        o[0] = *(u32*)((char*)*(void**)((char*)*(void**)((char*)this + 0xa8) + 0xc) + 0x10);
        o[2] = *(u32*)((char*)*(void**)((char*)*(void**)((char*)this + 0xa8) + 0xc) + 0x14);
        o[1] = *(u32*)((char*)*(void**)((char*)*(void**)((char*)this + 0xa8) + 0xc) + 0xc);
        return true;
    }
    return false;
}

// @ 0x00e47180
void* SPUIPropertyLayout::FUN_00e47180(u8 flags)
{
    *(volatile void**)((char*)this + 0) = &PTR_AddRef_01482370;
    *(volatile void**)((char*)this + 4) = &PTR_FUN_01482360;
    _ReadWriteBarrier();
    void* c;
    c = *(void**)((char*)this + 0x80);
    if (c != 0) {
        ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    c = *(void**)((char*)this + 0x7c);
    if (c != 0) {
        ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    c = *(void**)((char*)this + 0x78);
    if (c != 0) {
        ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    ((CPL*)this)->dtor();
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00e471e0
void* SPUIPropertyLayout::FUN_00e471e0()
{
    u32 z = 0;
    *(volatile void**)((char*)this + 4) = &PTR_AddRef_013ec458;
    _ReadWriteBarrier();
    *(u32*)((char*)this + 8) = z;
    *(void**)((char*)this + 0) = &PTR_AddRef_014823a8;
    *(void**)((char*)this + 4) = &PTR_FUN_01482398;
    *(u32*)((char*)this + 0x0c) = z;
    *(u32*)((char*)this + 0x10) = z;
    *(u32*)((char*)this + 0x14) = z;
    *(u32*)((char*)this + 0x18) = z;
    *(u32*)((char*)this + 0x1c) = z;
    *(u32*)((char*)this + 0x20) = z;
    *(u32*)((char*)this + 0x24) = z;
    *(u32*)((char*)this + 0x28) = z;
    *(u32*)((char*)this + 0x2c) = z;
    *(u32*)((char*)this + 0x30) = z;
    *(u32*)((char*)this + 0x3c) = z;
    *(u32*)((char*)this + 0x40) = z;
    *(u32*)((char*)this + 0x44) = z;
    *(u32*)((char*)this + 0x50) = z;
    *(u32*)((char*)this + 0x54) = z;
    *(u32*)((char*)this + 0x58) = z;
    *(u32*)((char*)this + 0x64) = z;
    *(u32*)((char*)this + 0x68) = z;
    *(u8*)((char*)this + 0x6c) = 1;
    *(u8*)((char*)this + 0x6d) = 0;
    *(float*)((char*)this + 0x70) = 0.0f;
    *(float*)((char*)this + 0x74) = 0.0f;
    *(u32*)((char*)this + 0x90) = (u32)&DAT_01667bae;
    *(void**)((char*)this + 0x88) = &gEmptyString16;
    *(void**)((char*)this + 0x8c) = &gEmptyString16;
    *(u32*)((char*)this + 0x98) = z;
    *(u32*)((char*)this + 0x9c) = z;
    *(u32*)((char*)this + 0xa0) = z;
    *(u32*)((char*)this + 0xa4) = z;
    *(u32*)((char*)this + 0xa8) = z;
    *(u32*)((char*)this + 0xac) = z;
    *(u32*)((char*)this + 0xb0) = z;
    *(u32*)((char*)this + 0xb4) = z;
    *(u32*)((char*)this + 0xc0) = z;
    *(u32*)((char*)this + 0xc4) = z;
    *(u32*)((char*)this + 0xc8) = z;
    *(u32*)((char*)this + 0xd4) = z;
    *(u32*)((char*)this + 0xd8) = z;
    *(float*)((char*)this + 0xdc) = 0.0f;
    *(u8*)((char*)this + 0xe0) = 0;
    *(u32*)((char*)this + 0xe4) = z;
    *(u8*)((char*)this + 0xec) = 0;
    *(u8*)((char*)this + 0xed) = 0;
    *(u32*)((char*)this + 0xf0) = z;
    *(u8*)((char*)this + 0xf4) = 0;
    *(u8*)((char*)this + 0x108) = 0;
    *(u8*)((char*)this + 0x109) = 0;
    return this;
}

// @ 0x00e47300
void SPUIPropertyLayout::FUN_00e47300()
{
    *(volatile void**)((char*)this + 0) = &PTR_AddRef_014823a8;
    *(volatile void**)((char*)this + 4) = &PTR_FUN_01482398;
    ((EaVector*)((char*)this + 0xc0))->dtor();
    {
        u32 v = *(u32*)((char*)this + 0xac);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete((void*)v);
    }
    {
        void* c = *(void**)((char*)this + 0xa4);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0xa0);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        u32 v = *(u32*)((char*)this + 0x9c);
        if (v != 0) {
            void* c = (void*)(v + 0x10);
            ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
        }
    }
    {
        void* c = *(void**)((char*)this + 0x98);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        u32 a = *(u32*)((char*)this + 0x88);
        u32 b = *(u32*)((char*)this + 0x90);
        u32 d = (b - a) & 0xfffffffe;
        if ((int)d > 2 && a != 0)
            operator_delete((void*)a);
    }
    {
        void* c = *(void**)((char*)this + 0x64);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        u32 v = *(u32*)((char*)this + 0x50);
        if (v != 0 && *(int*)(v - 4) != 0)
            operator_delete((void*)v);
    }
    ((EaVector*)((char*)this + 0x3c))->dtor();
    ((Helper4b*)((char*)this + 0x28))->dtor();
    {
        void* c = *(void**)((char*)this + 0x24);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x20);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x1c);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x14);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[2])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x10);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[2])(c);
    }
    {
        void* c = *(void**)((char*)this + 0x0c);
        if (c != 0) ((void (__thiscall*)(void*))(*(void***)c)[2])(c);
    }
    *(volatile void**)((char*)this + 0) = &PTR_AddRef_013eb938;
    _ReadWriteBarrier();
    *(volatile void**)((char*)this + 4) = &PTR_AddRef_013ec458;
}

// @ 0x00e47460
void Timeline::FUN_00e47460()
{
    CString cs;
    cs.ctor();
    u32 k = *(u32*)((char*)this + 0xe8);
    switch (k) {
    case 0x976f6445:
        cs.Load(0x8c509d6c, 0x555450a5, 0);
        break;
    case 0xb0ef13a6:
        cs.Load(0x8c509d6c, 0x555450a6, 0);
        break;
    }
    {
        u16* t = cs.GetText();
        u16* e = t;
        while (*e)
            e++;
        int n = (int)(e - t);
        ((WString*)((char*)this + 0x88))->Assign(t, t + n);
    }
    {
        int n = (*(int*)((char*)this + 0xc4) - *(int*)((char*)this + 0xc0)) >> 2;
        for (int i = 0; i < n; i++) {
            Timeline* c = *(Timeline**)(*(int*)((char*)this + 0xc0) + i * 4);
            c->FUN_00e47460();
        }
    }
    cs.dtor();
}

// @ 0x00e47520
void PL::FUN_00e47520(int flag, PL* t)
{
    if (m78 == 0)
        return;
    SetFlag(flag);
    if (m7c != 0)
        m7c->Slot7C(1, flag);
    if ((char)flag == 0)
        return;
    if (t == 0)
        return;

    cString s;
    char b = t->Fn46140(&s);
    if ((t->mD4 > 1 && t->Fn46180(&s)) || b) {
        FUN_00b3d410()->Fn3cf60(t);

        WString_s00e4_7520 vec = { 0, 0, 0 };
        vec.RangeInitialize(s.GetText());

        Variant var(vec);
        Fn828c30((void*)0x60c6eb8, &var, 1, 0);
        if (var.mFlags & 4)
            var.Destruct(false);
        if (((((int)vec.mCapacity - (int)vec.mBegin) & ~1) > 2) && vec.mBegin != 0)
            operator_delete((void*)vec.mBegin);

        func20h();
        if (m80 != 0) {
            float* r1 = m80->Rect();
            float a = r1[3] - r1[1];
            FUN_00806e40(m80, 0, 1);
            float* r2 = m80->Rect();
            float b2 = (r2[3] - r2[1]) - a;
            float* r3 = m78->Rect();
            m78->Resize(r3[2] - r3[0], (r3[3] - r3[1]) + b2);
        }
    } else {
        SetFlag(0);
    }
    FUN_00808b20(t->m20, m78, 1);
}

// @ 0x00e47700
void PL::FUN_00e47700(PtrVec* src)
{
    mVec.assignSlow(*src);
    if (mED == 0)
        return;

    PL* p = (PL*)operator_new(0x10c, DAT_013f6b3c, 0, 0, 0, 0);
    if (p != 0)
        p = p->Fn471e0();
    p->mA8 = mA8;
    if (p->mA8 != 0) {
        int e = p->mA8->m0C->m00;
        p->m68 = e;
        p->Fn46600(m1c, e, 1, 0);
    }
    p->mE0 = 1;
    p->mDC = Fn460d0();
    {
        AutoRef ref(p);
        if (mRefs.mEnd < mRefs.mCap) {
            PL** slot = mRefs.mEnd++;
            if (slot != 0) {
                *slot = p;
                p->AddRef();
            }
        } else {
            mRefs.DoInsertPtr(mRefs.mEnd, ref.mpObject);
        }
    }

    int n = (int)(mVec.mEnd - mVec.mBegin);
    for (int i = 0; i < n; ++i) {
        PL* q = (PL*)operator_new(0x10c, DAT_013f6b3c, 0, 0, 0, 0);
        if (q != 0)
            q = q->Fn471e0();
        ObjA8* w = mVec.mBegin[i];
        q->mA8 = w;
        if (q->mA8 != 0) {
            int e = q->mA8->m0C->m00;
            q->m68 = e;
            q->Fn46600(m1c, e, 1, 0);
        }
        q->mE0 = 1;
        if (mE0 != 0) {
            q->mDC = mDC;
        } else {
            float v;
            if (mA8 != 0)
                v = mA8->m0C->m04;
            else
                v = 0.0f;
            if (FUN_00b3d410() != 0 && mE4 != 0xbeb528cb)
                v = (float)FUN_00b3d410()->Fn37d70(v);
            q->mDC = v;
        }

        AutoRef ref(q);
        if (mRefs.mEnd < mRefs.mCap) {
            PL** slot = mRefs.mEnd++;
            if (slot != 0) {
                *slot = q;
                q->AddRef();
            }
        } else {
            mRefs.DoInsertPtr(mRefs.mEnd, ref.mpObject);
        }
    }
}

// @ 0x00e47930
void cEditorVerbIconPanel::RefreshUI()
{
    if (!mLayout.p) return;

    mWinIcon.Set(mLayout.p->FindWindowByID(0x94e2c6d2, 1));
    if (mWinIcon.p) {
        mWinIcon.p->AddWinProc((IWinProc*)this);
        mWinIcon.p->SetFlag(1, false);

        void* al = GetAlloc();
        void* mem = EAAlloc(0xb8, 8, "UI/InflateEffect", al);
        InflateEffect* inflate = mem ? ((InflateEffect*)mem)->Construct() : 0;
        if (inflate) {
            inflate->AddRef();
            IEffectCtl* c = &inflate->ctl;
            c->SetDuration(0.2f);
            c->SetXY(0.5f, 0.5f);
            c->SetB(2);
            c->SetC(15.0f);
            c->SetA(1);
            IEffectCtl* c2 = &inflate->ctl2;
            c2->SetDuration(0.1f);
            IWindow_s00e4_7930* wi = mWinIcon.p;
            wi->AddWinProc(c->GetWinProc());
        }
        al = GetAlloc();
        mem = EAAlloc(0x60, 8, "UI/FadeEffect", al);
        FadeEffect* fade = mem ? ((FadeEffect*)mem)->Construct() : 0;
        if (fade) {
            fade->AddRef();
            IEffectCtl* c = &fade->ctl;
            c->SetDuration(0.2f);
            c->SetXY(0.0f, 0.0f);
            c->SetB(0);
            c->SetA(1);
            IWindow_s00e4_7930* wi = mWinIcon.p;
            wi->AddWinProc(c->GetWinProc());
        }
        mWinIcon.p->SetFlag(1, true);
        if (fade) fade->Release();
        if (inflate) inflate->Release();
    }

    mWinText.Set(mLayout.p->FindWindowByID(0x60c6ca8, 1));

    uint32_t sel = 0xffffffff;
    if (mId == 0x99f0d1da || mId == 0xaaf6aaac || mId == 0xdca976d0) {
        uint32_t a = GetUIMgr()->GetModeId();
        if (a != 0xeca9947e) {
            IPropMgr* pm = PropertyManager();
            mProps.Clear();
            pm->Get(a, 0xe1d7164f, &mProps);
            if (a == 0xa7a9e952) {
                if (mF0 == 0xa35d0f5) sel = 0;
                else if (mF0 == 0x3360727f) sel = 2;
                else if (mF0 == 0x6aeb96a1) sel = 1;
            } else if (a == 0x2500e82c) {
                if (mF0 == 0xa35d0f5) sel = 1;
                else if (mF0 == 0x3360727f) sel = 0;
                else if (mF0 == 0x6aeb96a1) sel = 2;
            }
        }
    }

    int count = 0;
    Key3* keys;
    if (GetArrayKeys(mProps.p, 0x65263b4, &count, &keys)) {
        if (mWinIcon.p) mWinIcon.p->SetSize(mH, mW);
        if (sel == 0xffffffff) TryGetUIntProperty(mProps.p, 0x65263c8, &sel);
        mColors.Erase(mColors.begin, mColors.end);
        if (count > 0) {
            uint32_t id = 0x6527160;
            do {
                uint32_t i = id - 0x6527160;
                if (i < 3 && mLayout.p) {
                    IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(id, 1);
                    if (w) w->SetColor(i != sel ? 0xff737373u : 0xffffffffu);
                }
                IWindow_s00e4_7930* w2 = mLayout.p->FindWindowByID(id, 1);
                if (w2) w2->AddRef();
                mWindows.push(w2);
                if (w2) w2->Release();

                if (mWindows.begin[i]) {
                    Effect2* e = new ("UI/Effect2", 0, 0, 0, 0) Effect2;
                    e->Setup(mWindows.begin[i], 1, 1);
                    Key3 k = { keys[i].a, 0xb1b104, 0xf865c777 };
                    e->Apply(1, &k, 0);
                    if (e) e->AddRef();
                    mEffects.push(e);
                    if (e) e->Release();
                    if (sel != 0xffffffff) {
                        mWindows.begin[i]->SetFlag(2, false);
                        mWindows.begin[i]->SetFlag(0x10, true);
                    }
                }
                AutoRef_s00e4_7930<IPropList> pr;
                pr.p = 0;
                IPropMgr* pm = PropertyManager();
                pr.Clear();
                if (pm->Get(keys[i].a, 0xf865c777, &pr)) {
                    V3 col;
                    if (GetPropertyAsColorRGB(pr.p, 0xd4f639cd, &col)) {
                        V3* e = mColors.end;
                        if (e < mColors.cap) {
                            mColors.end = e + 1;
                            if (e) { e->x = col.x; e->y = col.y; e->z = col.z; }
                        } else {
                            mColors.DoInsertValue(e, &col);
                        }
                    }
                }
                if (pr.p) pr.p->Release();
            } while ((int)(++id - 0x6527160) < count);
        }
        } else {
        if (GetUIMgr()->IsReady(this)) {
            if (mWinText.p) {
                cString_s00e4_7930 s;
                if (GetPropertyAsText(mProps.p, 0x60b3e8e, &s))
                    mWinText.p->SetCaption(s.GetText());
            }
            IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(0x34f77eef, 1);
            if (w) {
                if (mCountA > 1 || mCountB >= 1) {
                    w->SetFlag(1, true);
                    int n = mCountB;
                    if (n < 1) n = mCountA;
                    if (n == 0) {
                        w->SetCaption(L"");
                    } else {
                        wchar_t buf[64];
                        SetNumberString((int64_t)n, buf, 0x40);
                        w->SetCaption(buf);
                    }
                } else {
                    w->SetCaption(L"");
                }
            }
            w = mLayout.p->FindWindowByID(0x1562b7e4, 1);
            if (w) w->SetColor(ColorFromId(mOwner->info->colA));
            w = mLayout.p->FindWindowByID(0x15302964, 1);
            if (w) w->SetColor(ColorFromId(mOwner->info->colB));

            uint32_t inst = 0;
            if (GetPropertyAsKeyInstance(mProps.p, 0x60b3e90, &inst)) {
                uint32_t col[3];
                col[0] = col[1] = col[2] = 0;
                int n = -1;
                switch (inst) {
                case 0x78f7bdcd: n = 0; break;
                case 0x251b2c0: n = 5; break;
                case 0x25a7ca68: n = 1; break;
                case 0x2b022d18: n = 2; break;
                case 0x86a510bc: n = 3; break;
                case 0xe50a3d1a: n = 6; break;
                case 0xf2451b0b: n = 4; break;
                }
                if (n >= 0) {
                    const uint32_t* c = GetUIMgr()->GetColor(n);
                    col[0] = c[0]; col[1] = c[1]; col[2] = c[2];
                }
                IWindow_s00e4_7930* iw = mLayout.p->FindWindowByID(0x60c6db0, 1);
                if (iw) {
                    iw->SetFlag(1, col[0] != 0);
                    SetWindowImage(iw, (Key3*)col, -1);
                }
            }
        }
        Key3 k = { 0, 0, 0 };
        if (GetPropertyAsKey(mProps.p, 0x60b3e8d, &k)) {
            IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(0x60c6db8, 1);
            GetUIMgr()->SetImage(w, &k);
        }
    }

    // Property-driven visibility flags.
    if (mProps.p) {
        Prop* pp;
        if (mProps.p->GetProperty(0x60def8e, &pp) && pp->type == 1) {
            char* v = (char*)pp;
            if (pp->flags & 0x30) v = *(char**)pp;
            bool b = *v != 0;
            IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(0x60df097, 1);
            if (w) w->SetFlag(1, b);
        }
    }
    if (mProps.p) {
        Prop* pp;
        if (mProps.p->GetProperty(0x60def8f, &pp) && pp->type == 1) {
            char* v = (char*)pp;
            if (pp->flags & 0x30) v = *(char**)pp;
            bool b = *v != 0;
            IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(0x60df098, 1);
            if (w) w->SetFlag(1, b);
        }
    }

    // Dialog layouts.
    if (GetUIMgr()) {
        bool doParent = false;
        if (mE8 == 0x976f6445 || mE8 == 0xb0ef13a6) {
            cSPUILayout_s00e4_7930* l = new ("UI/Layout", 0, 0, 0, 0) cSPUILayout_s00e4_7930;
            mLayoutA.Set(l);
            Key3 k;
            k.a = (mE8 != 0x976f6445 ? 0x878404b0u : 0u) + 0x429ae500u;
            k.b = 0x510a95b;
            k.c = (uint32_t)g_015a5b30;
            mLayoutA.p->Init(&k, 1, 0x5b598fa);
            mLayoutA.p->SetParentWin(GetUIMgr()->f48, 1, 0x5b598fa);
            IWindow_s00e4_7930* w = mLayoutA.p->FindWindowByID(0x755431d4, 1);
            if (w) w->SetCaption(mCaption);
            doParent = true;
        } else if (mE8 == 0xc0764a83) {
            doParent = true;
        }
        if (doParent) {
            void* parent = GetUIMgr()->FindParent(mParentId);
            if (parent) {
                cSPUILayout_s00e4_7930* l = new ("UI/Layout", 0, 0, 0, 0) cSPUILayout_s00e4_7930;
                mLayoutB.Set(l);
                Key3 k;
                k.a = 0x88d8120c;
                k.b = 0x510a95b;
                k.c = (uint32_t)g_015a5b30;
                mLayoutB.p->Init(&k, 1, 0x5b598fa);
                mLayoutB.p->SetParentWin(parent, 1, 0x5b598fa);
            }
        }
    }

    // Timeline / sporepedia data.
    uint32_t inst2 = 0;
    if (GetPropertyAsKeyInstance(mProps.p, 0x608db3f, &inst2)) {
        TLocal tl;
        tl.Set(2);
        tl.arr = 0; tl.e = 0; tl.c = 0;
        FillTimelineData(mOwner, &tl, inst2, mProps.p);
        KeyPtr kp = { 0, 0, 0, &tl };
        if (inst2 == 0x94995d55 || inst2 == 0x1e73d4fa) {
            AssetData* d = new ("UI/TimelineEventSporepediaData", 0, 0, 0, 0) AssetData;
            AssetData* o = mData.p;
            if (d != o) {
                if (d) d->ref.AddRef();
                mData.p = d;
                if (o) o->ref.Release();
            }
        } else {
            AssetData* d = new ("UI/TimelineEventSporepediaData", 0, 0, 0, 0) AssetData;
            mData.Assign(d);
        }
        AssetData* data = mData.p;
        data->Init(&kp);
        data->SetFlag(1);
        if (!data->Check()) {
            uint32_t v = 0;
            switch (mE4) {
            case 0xbeb528cb: v = 0xccc35c46; break;
            case 0xa426730b: v = 0xdfad9f51; break;
            case 0xad56080c: v = 0x9ea3031a; break;
            case 0xf71fa311: v = 0x372e2c04; break;
            case 0x2db6dad3: v = 0x65672ade; break;
            }
            data->SetKind(v);
        }
        IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(0x608a509, 1);
        if (w) {
            AssetView* view = new ("UI/TimelineEventSporepediaView", 0, 0, 0, 0) AssetView;
            mView.Set(view);
            mView.p->Init(w, mData.p, 0, 0);
            mView.p->Fn(0, 0);
            IWindow_s00e4_7930* sub = mView.p->sub;
            if (sub) {
                float* r = w->GetRect();
                sub->SetSize(r[2] - r[0], r[3] - r[1]);
            }
        }
        if (tl.arr && ((int*)tl.arr)[-1] != 0) operator delete[](tl.arr);
    }

    // Verb icon (editor / creature).
    if (mId == 0x278e6ca8 || mId == 0x246ba26c) {
        KeyPtr kp = { 0, 0, 0, 0 };
        Key3 kk = { 0, 0, 0 };
        Fn7100(&kp);
        FillKey(mOwner, 0x10, &kk);
        AutoRef_s00e4_7930<IPropList> pr;
        pr.p = 0;
        IPropMgr* pm = PropertyManager();
        pr.Clear();
        pm->Get(kk.a, kk.c, &pr);
        SpeciesMgr* sm = GetSpeciesRoot(&kp)->Get();
        if (sm) {
            int n = (int)(sm->end - sm->begin);
            if (n > 0) {
                SpeciesEntry** it = sm->begin;
                int i = 0;
                do {
                    if ((*it)->props == pr.p) {
                        VerbIconData* d = new ("UI/TimelineEventEditorVerbIconData", 0, 0, 0, 0) VerbIconData;
                        mIconData.Set(d);
                        DataHelper* h = mIconData.p ? mIconData.p->Get(0x4ac90b5) : 0;
                        h->Fn5950(sm, sm->begin[i], i);
                        break;
                    }
                    i++;
                    it++;
                } while (i < n);
            }
        }
        if (!mIconData.p) {
            VerbIconData* d = new ("UI/TimelineEventEditorVerbIconData", 0, 0, 0, 0) VerbIconData;
            mIconData.Set(d);
            mIconData.p->Set(pr.p);
        }
        if (mIconData.p->key.a != 0) {
            IWindow_s00e4_7930* w = mLayout.p->FindWindowByID(0x60c6db0, 1);
            if (w) {
                VerbIcon* ic = new ("UI/TimelineEventEditorVerbIcon", 0, 0, 0, 0) VerbIcon;
                mIcon.Set(ic);
                mIcon.p->Init(w, mIconData.p->key, mIconData.p, 0, 1, 0xe816f049, 0, 0);
                IWindow_s00e4_7930* iw = mIcon.p->GetIconWindow();
                if (iw) {
                    float* r1 = w->GetRect();
                    float* r2 = iw->GetRect();
                    iw->SetPos(((r2[2] - r2[0]) - (r1[2] - r1[0])) * -0.5f,
                               ((r2[3] - r2[1]) - (r1[3] - r1[1])) * -0.5f);
                    float* r = w->GetRect();
                    float h = r[3] - r[1];
                    float q = h / mIcon.p->Fn2910(0);
                    float one = 1.0f;
                    float* ps = &q;
                    if (1.0 <= q) ps = &one;
                    SetWindowScale(w, *ps);
                }
                Rollover* ro = mIcon.p->Fn2cb0();
                if (ro && mId == 0x246ba26c) ro->SetVisibility(0x4d97708, 0);
                IWindow_s00e4_7930* iw2 = mIcon.p->GetIconWindow();
                if (iw2) {
                    IWindow_s00e4_7930* x = iw2->FindChild(0x6283c92, true);
                    if (x) x->SetFlag(0x10, true);
                }
            }
        }
        if (pr.p) pr.p->Release();
    }

    IWindow_s00e4_7930* w7 = mLayout.p->FindWindowByID(0x7f214c0, 1);
    if (w7 && mOwner && mId == 0xbbc2a4ef)
        SetImageFromLayout(w7, mLayout.p, mOwner->info->imgBase + 0x7d21870, -1);

    IWindow_s00e4_7930* w1 = mLayout.p->FindWindowByID(0x53d6fe2a, 1);
    IWindow_s00e4_7930* w2 = mLayout.p->FindWindowByID(0x53d6fe30, 1);
    if (w2 && w1 && mOwner && mId == 0x1af2f7b7) {
        Key3 k;
        k.a = mOwner->info->resKey;
        k.b = 0x30bdee3;
        k.c = (uint32_t)g_015a5b50;
        AutoRef_s00e4_7930<IResult> out;
        out.p = 0;
        IResMan* rm = GetManager();
        out.Clear();
        if (rm->Get(&k, &out, 0, 0, 0, 0)) {
            if (!out.p) return;
            ResObj* o = out.p->Find(0x30bdee3);
            if (o) {
                w1->SetCaption(o->Fn0880());
                w2->SetCaption(o->Fn4e10());
            }
        }
        if (out.p) out.p->Release();
    }
}

// @ 0x00e48bb0
void C::Shutdown()
{
    *(u8*)((char*)this + 0x6d) = 0;

    void* p = *(void**)((char*)this + 0x98);
    if (p) {
        CALL0(p, 8);
        if (*(void**)((char*)this + 0x98)) {
            *(void**)((char*)this + 0x98) = 0;
            CALL0(p, 1);
        }
    }

    p = *(void**)((char*)this + 0x9c);
    if (p) {
        CALL0(p, 2);
        p = *(void**)((char*)this + 0x9c);
        if (p) {
            *(void**)((char*)this + 0x9c) = 0;
            CALL0((char*)p + 0x10, 1);
        }
    }

    p = *(void**)((char*)this + 0xa4);
    if (p) {
        CALL0(p, 10);
        if (*(void**)((char*)this + 0xa4)) {
            *(void**)((char*)this + 0xa4) = 0;
            CALL0(p, 1);
        }
    }

    p = *(void**)((char*)this + 0xa0);
    if (p) {
        CALL0(p, 5);
        if (*(void**)((char*)this + 0xa0)) {
            *(void**)((char*)this + 0xa0) = 0;
            CALL0(p, 1);
        }
    }

    p = *(void**)((char*)this + 0x20);
    if (p) {
        CALL1(p, 0x42, this);
        if (*(void**)((char*)this + 0x20)) {
            *(void**)((char*)this + 0x20) = 0;
            CALL0(p, 1);
        }
    }

    CSpuiLayout* lay = *(CSpuiLayout**)((char*)this + 0x10);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0x10);
        if (lay) {
            *(void**)((char*)this + 0x10) = 0;
            CALL0(lay, 2);
        }
    }

    lay = *(CSpuiLayout**)((char*)this + 0x14);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0x14);
        if (lay) {
            *(void**)((char*)this + 0x14) = 0;
            CALL0(lay, 2);
        }
    }

    lay = *(CSpuiLayout**)((char*)this + 0xc);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0xc);
        if (lay) {
            *(void**)((char*)this + 0xc) = 0;
            CALL0(lay, 2);
        }
    }

    int n = (*(int**)((char*)this + 0x40) - *(int**)((char*)this + 0x3c));
    for (int i = 0; i < n; i++) {
        void* e = (void*)(*(int**)((char*)this + 0x3c))[i];
        CALL0(e, 9);
    }
    {
        PtrVec_s00e4_8bb0* v = (PtrVec_s00e4_8bb0*)((char*)this + 0x3c);
        v->Erase(v->begin, v->end);
    }
    {
        PtrVec_s00e4_8bb0* v = (PtrVec_s00e4_8bb0*)((char*)this + 0x28);
        v->Erase(v->begin, v->end);
    }

    // Re-append the 12-byte triple vector to itself (matches the inlined copy).
    {
        char* b = *(char**)((char*)this + 0x50);
        char* e = *(char**)((char*)this + 0x54);
        char* d = b;
        char* s = e;
        if (s != e) {
            do {
                *(int*)(d + 0) = *(int*)(s + 0);
                *(int*)(d + 4) = *(int*)(s + 4);
                *(int*)(d + 8) = *(int*)(s + 8);
                d += 12; s += 12;
            } while (s != e);
        }
        int cnt = (int)(e - b) / 12;
        *(char**)((char*)this + 0x54) = e + cnt * 12;
    }

    int n2 = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    for (int i = 0; i < n2; i++) {
        C* child = (C*)(*(int**)((char*)this + 0xc0))[i];
        child->Shutdown();
    }
}

// @ 0x00e48dc0
void C::Setup()
{
    if (!*(u8*)((char*)this + 0x6d)) {
        if (*(void**)((char*)this + 0x1c) && *(void**)((char*)this + 0x18)) {
            void* mem = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
            CSpuiLayout* lay = mem ? (CSpuiLayout*)LayoutCtor(mem) : 0;
            ((LayoutRef*)((char*)this + 0xc))->Set(lay);

            Key3_s00e4_8bb0 k;
            k.a = *(u32_s00e4_8bb0*)((char*)this + 0x18);
            k.b = 0x510a95b;
            k.c = g_015a5b30_s00e4_8bb0;
            (*(CSpuiLayout**)((char*)this + 0xc))->Init(&k, 1, 0x5b598fa);
            (*(CSpuiLayout**)((char*)this + 0xc))->SetParentWin(
                *(void**)((char*)this + 0x1c), 1, 0x5b598fa);
            (*(CSpuiLayout**)((char*)this + 0xc))->SetReloadCallback(&ReloadCB, this);
            RefreshUI();
        }
        *(u8*)((char*)this + 0x6d) = 1;
    }

    int n = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    for (int i = 0; i < n; i++) {
        C* child = (C*)(*(int**)((char*)this + 0xc0))[i];
        child->Setup();
    }
    SetVisibleRecursive(*(u8*)((char*)this + 0x6c));
}

// @ 0x00e48eb0
void C::Load(int a, int b, int c, int d)
{
    void* pm = PropertyManager_s00e4_8bb0();
    void** slot = (void**)((char*)this + 0x64);
    void* old = *slot;
    if (old) {
        *slot = 0;
        CALL0(old, 1);
    }
    CALLG3(pm, 11, b, (int)0xe1d7164f, slot);
    GetPropertyAsKeyInstance(*slot, 0x91ad064, (void*)((char*)this + 0xe4));
    void* k = *(void**)((KeyMgr*)a)->Resolve((void*)((char*)this + 0xe4));
    ((Timeline_s00e4_8bb0*)this)->FUN_00e46600(k, b, c, d);
}

// @ 0x00e48f30
void C::SetOwner(int a, int b, int c, int d)
{
    *(int*)((char*)this + 0xa8) = b;
    if (b) {
        b = *(int*)(*(int*)(b + 0xc));
        *(int*)((char*)this + 0x68) = b;
        Load(a, b, c, d);
        return;
    }
}

// @ 0x00e48f60
void C::ShutdownRecursive()
{
    Shutdown();
    int n = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    for (int i = 0; i < n; i++) {
        C* child = (C*)(*(int**)((char*)this + 0xc0))[i];
        child->ShutdownRecursive();
    }
}

// @ 0x00e48fa0
void C::LayoutChildren(void* v2, int a, int b, float f)
{
    int count = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    if (count <= 0)
        return;
    if (!GetGlobal())
        return;

    float limit = *(float*)((char*)this + 0x70) + f;
    float pos = f;
    float avail = 0.0f;
    if (*(void**)((char*)this + 0x1c)) {
        float* r = CALLR0(*(void**)((char*)this + 0x1c), 14);
        avail = r[3] - r[1];
    }

    int used1 = 0, used2 = 0;

    SpVecF vec;
    vec.begin = 0;
    vec.end = 0;
    vec.cap = 0;
    vec.resize(count);

    if (count > 0) {
        int i = 0;
        do {
            C* ch = (C*)(*(int**)((char*)this + 0xc0))[i];
            float off = 0.0f;
            if (*(u32_s00e4_8bb0*)((char*)ch + 0x68) != 0x6701aff5 && *(void**)((char*)ch + 0xa8)) {
                Key3_s00e4_8bb0 kk;
                kk.a = kk.b = kk.c = 0;
                FillKey(*(void**)((char*)ch + 0xa8), 0x10, &kk);

                void* props = 0;
                void* pm = PropertyManager_s00e4_8bb0();
                if (props) { props = 0; CALL0(props, 1); }
                CALLG3(pm, 11, kk.a, kk.c, &props);

                int kind = 0;
                if (props) {
                    void* pr = 0;
                    if (CALLG2(props, 9, 0x1ef3be2, &pr) &&
                        *(short*)((char*)pr + 0x12) == 9) {
                        kind = *((Prop_s00e4_8bb0*)pr)->GetInt();
                    }
                }

                V2 sz;
                sz.x = sz.y = 0.0f;
                ((LayoutObj*)GetGlobal())->GetF1(&sz, ch);
                float s = sz.y;

                if (kind == 1) {
                    float t = (float)used1 + 0.5f;
                    used1++;
                    limit = (float)used1 * s + *(float*)((char*)this + 0x70) + f;
                    off = t * s + *(float*)((char*)this + 0x70) * 0.5f;
                } else {
                    off = (*(float*)((char*)this + 0x70) * -0.5f - s * 0.5f) - (float)used2 * s;
                    used2++;
                    pos = f - (float)used2 * s;
                }

                if (props) CALL0(props, 1);
            }
            vec.begin[i] = off;
            i++;
        } while (i < count);
    }

    float delta = 0.0f;
    if (!(0.0f <= pos)) {
        delta = -pos;
    } else if (limit > avail) {
        delta = avail - limit;
    }

    if (count > 0) {
        int i = 0;
        do {
            C* ch = (C*)(*(int**)((char*)this + 0xc0))[i];
            float o = vec.begin[i] + delta;
            ((Timeline_s00e4_8bb0*)ch)->FUN_00e46d80(((V2*)v2)->x, ((V2*)v2)->y,
                                          b, 0.0f, o, 1);
            i++;
        } while (i < count);
    }

    if (vec.begin && ((int*)vec.begin)[-1])
        operator_delete(vec.begin);
}

// @ 0x00e492d0
void C::Close()
{
    void* ms = MessageServer();
    CALL3(ms, 11, this, 0xf62def, 0xffffd8f1);

    void* p = *(void**)((char*)this + 0x90);
    if (p) {
        CALL1(p, 0, 1);
        *(void**)((char*)this + 0x90) = 0;
    }

    p = *(void**)((char*)this + 0x14);
    if (p) {
        CALL0(p, 5);
        p = *(void**)((char*)this + 0x14);
        if (p) {
            *(void**)((char*)this + 0x14) = 0;
            CALL0(p, 2);
        }
    }

    CSpuiLayout* lay = *(CSpuiLayout**)((char*)this + 0x10);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0x10);
        if (lay) {
            *(void**)((char*)this + 0x10) = 0;
            CALL0(lay, 2);
        }
    }
}

// @ 0x00e49360
void C::SetX(void* p)
{
    if (!p) {
        void* o = *(void**)((char*)this + 0x18);
        if (o) {
            *(void**)((char*)this + 0x18) = 0;
            CALL0(o, 1);
        }
        *(u8*)((char*)this + 0xc) = 1;
        return;
    }
    void* o = *(void**)((char*)this + 0x18);
    if (p != o) {
        CALL0(p, 0);
        *(void**)((char*)this + 0x18) = p;
        if (o)
            CALL0(o, 1);
    }
    *(u8*)((char*)this + 0xc) = 0;
}

// @ 0x00e493c0
void C::RefreshBig(int p2, int p3, int p4)
{
    void* mem = EAAllocate(0x14, (const char*)0x13f6b3c, 0, 0, 0, 0);
    ImageBase* base = mem ? ((ImageBase*)mem)->Construct(*(void**)((char*)this + 0x1c)) : 0;

    mem = EAAllocate(0x2c, "UI/Image", 0, 0, 0, 0);
    ImageObj* img = 0;
    if (mem) {
        int h = ((TexWrap*)base)->GetHeight(0.0f, 0.0f, 1.0f, 1.0f, 0);
        int w = ((TexWrap*)base)->GetWidth(h);
        img = (ImageObj*)((ImageObj*)mem)->Construct(base, w, h);
        if (img)
            CALL0(img, 0);
    }
    SetImageOnWin(*(void**)((char*)this + 0x2c), img, -1);

    void* props = 0;
    void* pm = PropertyManager_s00e4_8bb0();
    if (props) { props = 0; CALL0(props, 1); }
    CALLG3(pm, 11, p2, p4, &props);

    if (props) {
        if (*(void**)((char*)this + 0x24)) {
            CString_s00e4_8bb0 s;
            s.ctor();
            GetPropertyAsText(props, 0x8f6fc401, &s);
            void* w = *(void**)((char*)this + 0x24);
            CALL1(w, 0x20, s.GetText());
            s.dtor();
        }
        if (*(void**)((char*)this + 0x28)) {
            int n = 0;
            void* pr = 0;
            if (CALLG2(props, 9, 0x2166464, &pr) &&
                *(short*)((char*)pr + 0x12) == 9) {
                n = *((Prop_s00e4_8bb0*)pr)->GetInt();
            }
            wchar_t buf[0x30];
            *(short*)buf = 0;
            if (n != 0)
                FormatNum((double)n, buf, 0x28, L"%-F%-p", 0x268b);
            CALL1(*(void**)((char*)this + 0x28), 0x20, buf);
        }
        CALL1(*(void**)((char*)this + 0x30), 0x1b, (char*)this + 0x64);

        Key3_s00e4_8bb0 k;
        k.a = (u32_s00e4_8bb0)p2;
        k.b = (u32_s00e4_8bb0)p3;
        k.c = (u32_s00e4_8bb0)p4;
        ((AbilHost*)*(void**)((char*)this + 0x14))->SetVehicle(k);

        u32_s00e4_8bb0 out = 0;
        ((AbilHost*)*(void**)((char*)this + 0x14))->LayoutAbilitiesCompact(
            *(void**)((char*)this + 0x30), 0, &out);

        bool flag = *(u32_s00e4_8bb0*)((char*)this + 0xa0) < out;
        CALL2(*(void**)((char*)this + 0x34), 0x1f, 1, flag);

        float* r = CALLR0(*(void**)((char*)this + 0x30), 14);
        float y0 = *(float*)((char*)this + 0x78);
        float x0 = *(float*)((char*)this + 0x74);
        float y1 = *(float*)((char*)this + 0x7c);
        float rx = (r[2] - r[0]) + *(float*)((char*)this + 0x84);
        if (y1 - x0 < rx)
            y1 = rx + x0;
        float ry = ((r[3] - r[1]) -
                    (*(float*)((char*)this + 0x70) - *(float*)((char*)this + 0x68))) +
                   (*(float*)((char*)this + 0x80) - *(float*)((char*)this + 0x78)) + y0;
        float box[4] = { x0, y0, y1, ry };
        if (*(void**)((char*)this + 0x20))
            CALL1(*(void**)((char*)this + 0x20), 0x1b, &box[0]);
    }
    if (img)
        CALL0(img, 1);
}

// @ 0x00e496d0
void C::LoadParams()
{
    void* props = 0;
    void* pm = PropertyManager_s00e4_8bb0();
    ((PtrSlot*)&props)->Release();
    char ok = CALLG2(pm, 12, 0x5c770db7, &props);
    if (ok) {
        if (props) {
            void* pr;
            if (CALLG2(props, 9, 0x332d8d35, &pr) &&
                *(short*)((char*)pr + 0x12) == 0xd) {
                *(float*)((char*)this + 0x94) = *((Prop_s00e4_8bb0*)pr)->GetFloat();
            }
            if (props) {
                if (CALLG2(props, 9, (int)0xe451b420, &pr) &&
                    *(short*)((char*)pr + 0x12) == 0xd) {
                    *(float*)((char*)this + 0x98) = *((Prop_s00e4_8bb0*)pr)->GetFloat();
                }
                if (props) {
                    if (CALLG2(props, 9, (int)0xdc26347c, &pr) &&
                        *(short*)((char*)pr + 0x12) == 0xd) {
                        *(float*)((char*)this + 0x9c) = *((Prop_s00e4_8bb0*)pr)->GetFloat();
                    }
                    if (props) {
                        if (CALLG2(props, 9, 0x925d9d2, &pr) &&
                            *(short*)((char*)pr + 0x12) == 0xa) {
                            *(u32_s00e4_8bb0*)((char*)this + 0xa0) = *((Prop_s00e4_8bb0*)pr)->GetUInt();
                        }
                    }
                }
            }
        }
        if (*(void**)((char*)this + 0x14))
            *(u32_s00e4_8bb0*)(*(char**)((char*)this + 0x14) + 0x64) = *(u32_s00e4_8bb0*)((char*)this + 0xa0);
    }
    if (props)
        CALL0(props, 1);
}

// @ 0x00e49820
void BlkVec::InsertRange(u32_s00e4_8bb0 n, int atEnd)
{
    char* curp = *(char**)((char*)this + 0x14);
    char* endp = *(char**)((char*)this + 0x24);
    int bytes = (int)(endp - curp);
    int slots = (bytes >> 2) + 1;
    int total = slots + (int)n;
    u32_s00e4_8bb0 capv = *(u32_s00e4_8bb0*)((char*)this + 4);
    int* dst;

    if (capv <= (u32_s00e4_8bb0)(total * 2)) {
        u32_s00e4_8bb0 base = maxref(*(u32_s00e4_8bb0*)((char*)this + 4), n);
        u32_s00e4_8bb0 at = atEnd ? 0 : n;
        u32_s00e4_8bb0 newcap = base + *(u32_s00e4_8bb0*)((char*)this + 4) + 2;
        int* nb = (int*)EAAllocate(newcap * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        int* src = *(int**)((char*)this + 0x14);
        dst = (int*)((char*)nb + ((((int)src - *(int*)this) >> 2) + (int)at) * 4);
        if (*(int*)this)
            VecInsert(dst, src, (*(int*)((char*)this + 0x24) - (int)src) + 4);
        if (*(int*)this)
            operator_delete(*(void**)this);
        *(int*)this = (int)nb;
        *(u32_s00e4_8bb0*)((char*)this + 4) = newcap;
    } else {
        u32_s00e4_8bb0 extra = atEnd ? 0 : n;
        dst = (int*)(*(int*)this + (((capv - (u32_s00e4_8bb0)total) >> 1) + extra) * 4);
        if ((char*)dst < curp) {
            VecInsert(dst, curp, bytes + 4);
        } else {
            memmove_(dst + (slots - ((bytes + 4) >> 2)),
                     curp, bytes + 4);
        }
    }

    *(int**)((char*)this + 0x14) = dst;
    int v = *dst;
    *(int*)((char*)this + 0xc) = v;
    *(int*)((char*)this + 0x10) = v + 0xc0;
    int* last = dst + slots - 1;
    *(int**)((char*)this + 0x24) = last;
    v = *last;
    *(int*)((char*)this + 0x1c) = v;
    *(int*)((char*)this + 0x20) = v + 0xc0;
}

// @ 0x00e49950
void BlkVec::Init(u32_s00e4_8bb0 n)
{
    int cnt = (int)(n >> 4) + 1;
    u32_s00e4_8bb0 want = (u32_s00e4_8bb0)cnt + 2;
    u32_s00e4_8bb0 eight = 8;
    u32_s00e4_8bb0 capv = maxref(want, eight);
    *(u32_s00e4_8bb0*)((char*)this + 4) = capv;

    int* buf = (int*)EAAllocate(*(u32_s00e4_8bb0*)((char*)this + 4) * 4, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* start = (int*)((char*)buf +
        (((*(u32_s00e4_8bb0*)((char*)this + 4) - (u32_s00e4_8bb0)cnt) >> 1)) * 4);
    int* end = start + cnt;
    *(int*)this = (int)buf;

    for (int* p = start; p < end; p++) {
        *p = (int)EAAllocate(0xc0, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }

    *(int**)((char*)this + 0x14) = start;
    int v = *start;
    *(int*)((char*)this + 0xc) = v;
    *(int*)((char*)this + 0x10) = v + 0xc0;
    *(int*)((char*)this + 8) = *(volatile int*)((char*)this + 0xc);
    *(int**)((char*)this + 0x24) = end - 1;
    v = end[-1];
    *(int*)((char*)this + 0x1c) = v;
    *(int*)((char*)this + 0x20) = v + 0xc0;
    *(int*)((char*)this + 0x18) =
        *(volatile int*)((char*)this + 0x1c) + (int)(n & 0xf) * 0xc;
}

// @ 0x00e49a40
void cUnlockPanel::FUN_00e49a40(IRefCounted* mission)
{
    mMission.Set(mission);
    mbNoMission = (mMission.mp == 0);
    bool inSpace = (GetCurrentGameMode() == 0x1654c00);
    if (mLayout.mp == 0) {
        cSPUILayout_s00e4_9a40* layout = (cSPUILayout_s00e4_9a40*)FUN_00f473a0(0x18, "Simulator", 0, 0, 0, 0);
        layout = layout != 0 ? layout->Construct() : 0;
        mLayout.Set(layout);
        Key key;
        key.mTypeId = 0x2d2eb184;
        key.mGroupId = 0x0510a95b;
        key.mInstanceId = 0x40464100;
        ((cSPUILayout_s00e4_9a40*)mLayout.mp)->Init(key, true, 0xec2fd2c3);
    }
    if (mAbilities.mp == 0) {
        cVehicleAbilities* abilities = (cVehicleAbilities*)FUN_00f473a0(0x70, "UI", 0, 0, 0, 0);
        abilities = abilities != 0
                  ? abilities->Init(0x9ea3031a + (inSpace ? 0x410a9c37 : 0))
                  : 0;
        mAbilities.Set(abilities);
    }
    if (mpAnimator == 0) {
        cMissionCardAnimator* animator =
            (cMissionCardAnimator*)FUN_00f473a0(0x20, "UI/UnlockCardAnimator", 0, 0, 0, 0);
        mpAnimator = animator != 0 ? animator->Init() : 0;
    }
    cSPUILayout_s00e4_9a40* layout = (cSPUILayout_s00e4_9a40*)mLayout.mp;
    mW20.Set(layout->FindWindowByID(0x9554487e, true));
    mW24.Set(layout->FindWindowByID(0xf554489d, true));
    mW28.Set(layout->FindWindowByID(0x3554489e, true));
    mW2c.Set(layout->FindWindowByID(0x9554489f, true));
    mW30.Set(layout->FindWindowByID(0x755448a0, true));
    mW34.Set(layout->FindWindowByID(0x755ab697, true));
    mW20.mp->SetFlag(1, false);
    const Vec4P* posA = mW30.mp->GetPosition();
    mPosA.x = posA->x;
    mPosA.y = posA->y;
    mPosA.z = posA->z;
    mPosA.w = posA->w;
    const Vec4P* posB = mW20.mp->GetPosition();
    mPosB.x = posB->x;
    mPosB.y = posB->y;
    mPosB.z = posB->z;
    mPosB.w = posB->w;
    mWidth = (mPosB.z - mPosB.x) - (mPosA.z - mPosA.x);
    IMessageServer* server = SP::MessageServer_s00e4_9a40();
    server->AddHandler(this, 0xf62def);
    FUN_00e496d0();
}

// @ 0x00e49d80
bool cUnlockPanel::FUN_00e49d80(int type, cMessage* msg)
{
    if (type == 0xf62def && msg->mEventType == 0x5c770db7)
        FUN_00e496d0();
    return false;
}

// @ 0x00e49db0
void cKeyQueue::FUN_00e49db0()
{
    Key12* next = mpCur + 1;
    if (next == mpCurEnd) {
        if (mpCurPage != 0)
            FUN_00f47380(mpCurPage);
        Key12** slot = mppCurSlot + 1;
        mppCurSlot = slot;
        mpCurPage = *slot;
        mpCurEnd = mpCurPage + 16;
        next = mpCurPage;
    }
    mpCur = next;
}

// @ 0x00e49df0
void cKeyQueue::FUN_00e49df0(Key12* key)
{
    Key12 copy = *key;
    if ((mppBackSlot - mppBase) + 1 >= mnCapacity)
        FUN_00e49820(1, 1);
    Key12* page = (Key12*)FUN_00f473a0(0xc0, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    mppBackSlot[1] = page;
    if (mpBack != 0) *mpBack = copy;
    Key12** slot = mppBackSlot + 1;
    mppBackSlot = slot;
    mpBackPage = *slot;
    mpBackEnd = mpBackPage + 16;
    mpBack = mpBackPage;
}

// @ 0x00e49e80
void cUnlockPanel::FUN_00e49e80()
{
    // the two stores the compiler emits for a destructor of a two-base class
    mpVtbl = g_vtbl_01482478;
    mpVtbl2 = g_vtbl_01482468;
    mQueue.Destroy();
    IWindowRef* window = mW34.mp;
    if (window != 0) window->Release();
    window = mW30.mp;
    if (window != 0) window->Release();
    window = mW2c.mp;
    if (window != 0) window->Release();
    window = mW28.mp;
    if (window != 0) window->Release();
    window = mW24.mp;
    if (window != 0) window->Release();
    window = mW20.mp;
    if (window != 0) window->Release();
    if (mpImage != 0) {                                 // inlined EA::RefCountTemplate<int>::Release
        volatile long* count = &mpImage->mnRefCount;
        _InterlockedDecrement(count);
        if (_InterlockedExchangeAdd(count, 0) < 1)
            _InterlockedExchangeAdd(count, 1);
        else
            _InterlockedExchangeAdd(count, 0);
    }
    if (mMission.mp != 0) mMission.mp->Release();
    if (mAbilities.mp != 0) mAbilities.mp->Release();
    if (mLayout.mp != 0) mLayout.mp->Release();
    // and the two base-class stores at the end of a destructor
    mpVtbl2 = g_vtbl_013ec458;
    mpVtbl = g_vtbl_013eb394;
}

// @ 0x00e49f80
void cMissionPanel::Update(float dt)
{
    AnimBuf animA, animB, animC, animD, animE;
    Key12 key;
    Quat qB, qC;
    IWindow_s00e4_9a40* panelWin = 0;
    mpWindow->SetAnchor(4.0f, 10.0f);
    if (mpMission != 0) {
        panelWin = mpMission->GetPanelWindow();
        if (panelWin != 0) {
            const float* off = panelWin->GetOffset();
            mpWindow->SetAnchor(off[0], off[1]);
        }
    }
    mTimer = dt + mTimer;

    switch (mState)
    {
    case 0:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mbFlag) {
            cMission* m = mpMission;
            if (m != 0) {
                mpMission = 0;
                ((IReleasable*)m)->Release();
            }
            mbFlag = 1;
        }
        if (mpTarget != mpShown) {
            if (mbFlag != 1) {
                if (mpMission->GetModel()->GetKind() == 5) break;
            }
            key = *mpTarget;
            key.b = 0x2f7d0004;
            key.c = (GetCurrentGameMode() != 0x1654c00) ? 0x02231c8b : 0xb1b0f42e;
            mImage.Set(FUN_0067dd60()->GetImage(key, 0));
            if (mImage.p != 0) mState = 1;
            else               mSub.FUN_00e49db0();
        }
        break;

    case 1:
        if (panelWin) panelWin->SetFlag(1, true);
        if (!(mImage.p->flags & 1)) break;
        if (mbFlag != 0) {
            FUN_00e493c0(*mpTarget);
            mSub.FUN_00e49db0();
            mpAnimator->RemoveAnimation(mpWindow, -1);
            qB.x = 0.0f; qB.y = 1.0f; qB.z = 0.0f; qB.w = g_15a5b54 + g_15a5b58;
            SetWindowRotation(mpWindow, &qB);
            mpWindow->SetFlag(1, true);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animB, mpWindow, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 2),
                mpWindow, 0);
            animB.Destroy();
            mTimer = 0.0f;
            mState = 3;
        } else {
            mpAnimator->RemoveAnimation(panelWin, -1);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animA, panelWin, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 1),
                panelWin, 0);
            animA.Destroy();
            mTimer = 0.0f;
            mState = 2;
        }
        break;

    case 2:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration) {
            FUN_00e493c0(*mpTarget);
            mSub.FUN_00e49db0();
            mpAnimator->RemoveAnimation(mpWindow, -1);
            qC.x = 0.0f; qC.y = 1.0f; qC.z = 0.0f; qC.w = g_15a5b54 + g_15a5b58;
            SetWindowRotation(mpWindow, &qC);
            mpWindow->SetFlag(1, true);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animC, mpWindow, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 2),
                mpWindow, 0);
            animC.Destroy();
            mTimer = 0.0f;
            mState = 3;
        }
        break;

    case 3:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration) {
            mTimer = 0.0f;
            mState = 4;
        }
        break;

    case 4:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration2) {
            mpAnimator->RemoveAnimation(mpWindow, -1);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animD, mpWindow, Vec4(0.0f, 1.0f, 0.0f, -g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 1),
                mpWindow, 0);
            animD.Destroy();
            mTimer = 0.0f;
            mState = 5;
        }
        break;

    case 5:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration) {
            if (mbFlag == 0) {
                mpWindow->SetFlag(1, false);
                mpAnimator->RemoveAnimation(panelWin, -1);
                mpAnimator->AddAnimation(
                    SPUICreateWindowAnimationRotation(&animE, panelWin, Vec4(0.0f, 1.0f, 0.0f, -g_15a5b54),
                                                      GetElapsedSeconds(), mDuration, 2),
                    panelWin, 0);
                animE.Destroy();
                mTimer = 0.0f;
                mState = 6;
            } else {
                mState = 0;
            }
        }
        break;

    case 6:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration) {
            mTimer = 0.0f;
            mState = 7;
            cModel* model = mpMission->GetModel();
            if (model->GetKind() == 4) {
                cModelPanel* panel = FUN_00e19cf0(model);
                if (panel != 0) {
                    panel->Notify();
                    if (GetCurrentGameMode() == 0x1654c01)
                        g_169e230->SetActive(0);
                }
            }
        }
        break;

    case 7:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration3) {
            mTimer = 0.0f;
            mState = 0;
            mImage.Set(0);
        }
        break;
    }
    mpAnimator->Update();
}

// @ 0x00e4a6e0
cUnlockPanel* cUnlockPanel::FUN_00e4a6e0()
{
    // the base-class constructor and the two derived-class stores of the real constructor
    mpVtbl2 = g_vtbl_013ec458;
    mf08 = 0;
    mpVtbl = g_vtbl_01482478;
    mpVtbl2 = g_vtbl_01482468;
    mbNoMission = false;
    mLayout.mp = 0;
    mAbilities.mp = 0;
    mMission.mp = 0;
    mpImage = 0;
    mW20.mp = 0;
    mW24.mp = 0;
    mW28.mp = 0;
    mW2c.mp = 0;
    mW30.mp = 0;
    mW34.mp = 0;
    cKeyQueue* queue = &mQueue;
    queue->mppBase = 0;
    queue->mnCapacity = 0;
    queue->mpCur = 0;
    queue->mpCurPage = 0;
    queue->mpCurEnd = 0;
    queue->mppCurSlot = 0;
    queue->mpBack = 0;
    queue->mpBackPage = 0;
    queue->mpBackEnd = 0;
    queue->mppBackSlot = 0;
    queue->FUN_00e49950(0);
    mTimer = 0.0f;
    mDuration = 0.5f;
    mDuration2 = 5.0f;
    mDuration3 = 2.0f;
    mState = 0;
    mpAnimator = 0;
    return this;
}

// @ 0x00e4a790
void cUnlockPanel::FUN_00e4a790(Key12 key)
{
    cKeyQueue* queue = &mQueue;
    Key12* slot = queue->mpBack;
    if (slot + 1 != queue->mpBackEnd) {
        queue->mpBack = slot + 1;
        if (slot != 0) *slot = key;
    } else {
        queue->FUN_00e49df0(&key);
    }
}

// @ 0x00e4cc10
void __stdcall FUN_00e4cc10(short* s)
{
    int v = ((int(__stdcall*)(void*))FUN_008d61e0)(s);
    if (v == -1) {
        if (*s == 0x2e) s += 1;
        EA_Hash_FNV1_String16(s, 0x811c9dc5, 1);
    }
}
