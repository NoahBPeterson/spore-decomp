// src/game/SPEditors/_at_00ef0000.cpp -- migrated from slice(s) s00efee60, s00efdee0, s00efd020, s00efc270, s00efb4e0, s00ef9e40, s00ef8dc0, s00ef7d90, s00ef6db0, s00ef5dd0, s00ef50a0, s00ef40d0, s00ef3370, s00ef26c0, s00ef16a0, s00ef07d0, s00eef810 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00ef0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/FunctionalMatch/Constraint.h"
#include "SP/cLocalInputState.h"
#include "EA/Random/RandomLinearCongruential.h"

// unnamed retail callees and globals (address in the comment)
extern uint8_t g_15acb40;                              // 0x015ACB40
extern uint8_t g_1569ab8;                              // 0x01569AB8
extern float g_1688270;                                // 0x01688270
extern float g_156b5d4;                                // 0x0156B5D4
extern float g_156b5d8;                                // 0x0156B5D8
extern int g_15acc34;                                  // 0x015ACC34
#include <math.h>
#include <intrin.h>
#include "SP/cGameNounManager.h"
#include "SP/cMWModel.h"
#include "SP/cCombatant.h"
#include "SP/cField.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include <string.h>
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cPollinator.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "cSPUITooltipWinProc.h"
#include "EA/LimitStopwatch.h"
#include "EA/Stopwatch.h"
#include "EA/Variant.h"
#include "SP/cViewer.h"

// ---- items of slice s00eef810 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
#define ED_CAT2(a, b) a##b
#define ED_CAT(a, b) ED_CAT2(a, b)
#define V virtual void ED_CAT(ed_v, __COUNTER__)();
#define V2 V V
#define V3 V2 V
#define V4 V2 V2
#define V8 V4 V4
struct IObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
struct IObj4  { uint pad0; IObj m; };                 // IObj's vptr at +0x04
struct IObj8  { uint pad0[2]; IObj m; };              // +0x08
struct IObj38 { uint pad0[0x38 / 4]; IObj m; };       // +0x38
struct IObj3c { uint pad0[0x3c / 4]; IObj m; };       // +0x3c
struct LocalInputState {
    uint mData[0x48 / 4];                              // 0x20..0x67 of the editor
    void OnMouseDown(uint id, float x, float y, uint flags);   // 0x00697AB0
    void OnMouseUp(uint id, float x, float y, uint flags);     // 0x00697AF0
};
void __fastcall InitLocalInputState(LocalInputState* p);       // 0x00697960
class CEditor {
public:
    const void* volatile mpVtbl0;                      // +0x00
    const void* volatile mpVtbl1;                      // +0x04
    const void* volatile mpVtbl2;                      // +0x08
    uint volatile mField0c;                            // +0x0c
    IObj3c* mpField10;                                 // +0x10
    IObj* mpField14;                                   // +0x14
    IObj* mpField18;                                   // +0x18
    IObj* mpField1c;                                   // +0x1c
    LocalInputState mInput;                            // +0x20
    IObj3c* mpField68;                                 // +0x68
    IObj38* mpField6c;                                 // +0x6c
    IObj* mpField70;                                   // +0x70
    IObj8* mpField74;                                  // +0x74
    IObj4* mpField78;                                  // +0x78
    IObj* mpField7c;                                   // +0x7c
    void* mpServer80;                                  // +0x80
    uint mHandler84;                                   // +0x84
    uint mMsg88;                                       // +0x88
    uint mPrio8c;                                      // +0x8c
    uint mFlags90;                                     // +0x90
    void* mpServer94;                                  // +0x94
    uint mHandler98;                                   // +0x98
    uint mMsg9c;                                       // +0x9c
    uint mPrioA0;                                      // +0xa0
    uint mFlagsA4;                                     // +0xa4
    uint8_t mFlagA8;                                   // +0xa8
    uint mFieldAc;                                     // +0xac
    uint mFieldB0;                                     // +0xb0
    uint mFieldB4;                                     // +0xb4
    uint mFieldB8;                                     // +0xb8
    uint mFieldBc;                                     // +0xbc
    uint mFieldC0;                                     // +0xc0
    int  mFieldC4;                                     // +0xc4
    uint mFieldC8;                                     // +0xc8
    uint mFieldCc;                                     // +0xcc
    uint mFieldD0;                                     // +0xd0
    IObj4* mpFieldD4;                                  // +0xd4
    IObj* mpFieldD8;                                   // +0xd8
    uint8_t mFlagDc;                                   // +0xdc

    CEditor* Construct();                              // 0x00EF02F0
    void Destroy();                                    // 0x00EF0400
    bool OnMouseDown(uint id, float x, float y, uint flags);   // 0x00EF0670
    bool OnMouseUp(uint id, float x, float y, uint flags);     // 0x00EF0730
};
struct Entry12 { uint m0, m4, m8; };
struct ItemFlags { uint pad0; uint mFlags; };          // flags at +0x04
struct InputItem {
    V8 V8 V8 V8 V8 V2 V
    virtual ItemFlags* v0xac();                        // +0xac
};
class CUpdater {
public:
    uint8_t pad00[0x4c];
    Entry12* mpBegin;                                  // +0x4c
    Entry12* mpEnd;                                    // +0x50
    uint8_t pad54[0x0c];
    InputItem** mpItems;                               // +0x60
    InputItem** mpItemsEnd;                            // +0x64
    void UpdateTransforms();                           // 0x00EF0220
    bool CheckAll();                                   // 0x00EF02A0
};
class CToolState {
public:
    uint8_t mFlag0;                                    // +0x00
    uint8_t mActive;                                   // +0x01
    uint8_t mRelative;                                 // +0x02
    uint8_t pad03;
    uint pad04;
    float mX;                                          // +0x08
    float mY;                                          // +0x0c
    union { float f; uint u; } mDX;                    // +0x10
    union { float f; uint u; } mDY;                    // +0x14
    __declspec(noinline) void Enable();                // 0x00EEFF40
    __declspec(noinline) void Disable();               // 0x00EEFF80
    void Drag(float x, float y);                       // 0x00EEFFC0
    __declspec(noinline) void Reset();                 // 0x00EF0060
};
struct C_SomethingCtl {
    void Set40(bool b);                                // 0x008013D0
    void Set(bool b);                                  // 0x00801980
};
C_SomethingCtl* GetSomethingCtl();                     // 0x0067CAB0
struct ObjDD20 {
    V8 V2
    virtual void v28(uint id);                         // +0x28
};
ObjDD20* FUN_0067dd20();                               // 0x0067DD20
struct IProp {
    uint8_t pad[0x12];
    uint16_t mType;                                    // +0x12
    bool*  GetBool();                                  // 0x0041E920
    float* GetFloat();                                 // 0x0041EA70
};
struct DirectPropertyList {
    V8 V
    virtual bool Get(uint id, IProp** out);            // +0x24
};
extern DirectPropertyList* g_15fd918;                  // 0x015FD918
extern uint8_t g_15acb40;                              // 0x015ACB40
extern uint8_t g_1569ab8;                              // 0x01569AB8
extern float g_1688270;                                // 0x01688270
extern float g_156b5d4;                                // 0x0156B5D4
extern float g_156b5d8;                                // 0x0156B5D8
void FUN_00eed090();                                   // 0x00EED090
struct Obj401010 {
    V4 V2
    virtual bool v18(void* entry);                     // +0x18
    V8 V4
    virtual void v4c(void* entry, const void* data);   // +0x4c
};
Obj401010* FUN_00401010();                             // 0x00401010
struct IInputHost {
    V8 V2
    virtual void v28();                                // +0x28
    V4
    virtual bool v3c();                                // +0x3c
    V4
    virtual void v50(uint id, float x, float y, uint flags);  // +0x50
    virtual bool v54(uint id, float x, float y, uint flags);  // +0x54
};
struct IInputMgr {
    V8 V8 V4 V
    virtual bool v54(uint id, float x, float y, uint flags);  // +0x54
    virtual bool v58(uint id, float x, float y, uint flags);  // +0x58
};
IInputMgr* GameInputManager();                         // 0x00B3D250
extern IInputHost* g_15ad298;                          // 0x015AD298
extern int g_15acc34;                                  // 0x015ACC34
extern CToolState g_16c7b34;                           // 0x016C7B34
extern CEditor* g_16c7aa4;                             // 0x016C7AA4
extern uint g_16c7aa8;                                 // 0x016C7AA8
extern uint g_16c7aac;                                 // 0x016C7AAC
struct RayB;
struct RayA {
    uint pad00[0x60 / 4];
    uint mField60;                                     // +0x60
    uint pad64;
    RayB* mpB;                                         // +0x64
};
struct RayOwner {
    uint pad00[0x17c / 4];
    void* mpField17c;                                  // +0x17c
};
struct RayObj;
struct RayB {
    V3
    virtual RayObj* v0c(uint id);                      // +0x0c
    V4
    virtual void* v20();                               // +0x20
};
struct RayObj {
    uint pad04[(0xb54 - 4) / 4];
    RayOwner* mpOwner;                                 // +0xb54
    uint mFlags;                                       // +0xb58
    V8
    virtual uint v20();                                // +0x20
};
struct RaySource {
    RayA* mpA;                                         // +0x00
    uint pad04;
    float m08, m0c, m10, m14, m18, m1c;
};
struct Vec3 { float x, y, z; };
extern "C" Vec3* normalized_safe(Vec3* pOut, const Vec3* pIn);   // 0x00449C20
bool RayCastParts(const float* org, const float* dir, RayOwner* owner,
                  uint* pIndex, float* pT, float* pHit, float* pNormal, int extra); // 0x009B6450
void RemoveHandler(void* server, uint handler, uint msg, uint prio, uint flags); // 0x00571DB0
// ---- items of slice s00eef810 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern DirectPropertyList* g_15fd918;                  // 0x015FD918
extern IInputHost* g_15ad298;                          // 0x015AD298
extern CToolState g_16c7b34;                           // 0x016C7B34
extern CEditor* g_16c7aa4;                             // 0x016C7AA4
extern uint g_16c7aa8;                                 // 0x016C7AA8
extern uint g_16c7aac;                                 // 0x016C7AAC
extern "C" Vec3* normalized_safe(Vec3* pOut, const Vec3* pIn);   // 0x00449C20

// ---- items of slice s00ef07d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*       DAT_015ad298;      // 0x15ad298 input manager singleton
extern void*       DAT_016c7aa4;      // 0x16c7aa4 app/message context
extern void*       DAT_0167a690;      // 0x167a690 cCitySimulator singleton
extern void*       DAT_0168d824;      // 0x168d824 SimSingleton
extern "C" void*  FUN_0067dd10();                                       // 0x67dd10 SP::App
extern "C" void*  FUN_0067dcc0();                                       // 0x67dcc0 SP::MessageServer
extern "C" void*  FUN_0067ddd0();                                       // 0x67ddd0 SP::EffectsManager
extern "C" void*  FUN_0067cab0();                                       // 0x67cab0
extern "C" void*  FUN_00b3d330();                                       // 0xb3d330 SP::SimTicker
extern "C" void*  FUN_00b3d250();                                       // 0xb3d250 SP::GameInputManager
extern "C" void*  FUN_00b3d300();                                       // 0xb3d300 SP_NounManager
extern "C" void*  FUN_00b3d230();                                       // 0xb3d230 (no-arg getter)
extern "C" void*  FUN_00b3d240();                                       // 0xb3d240 (no-arg getter)
extern "C" void*  FUN_00b3d380();                                       // 0xb3d380 (no-arg getter)
extern "C" void*  FUN_00b3d400();                                       // 0xb3d400
extern "C" void*  FUN_00b3d4c0();                                       // 0xb3d4c0
extern "C" void*  FUN_00d539d0();                                       // 0xd539d0 SP::cPosseSimulator::Instance
extern "C" void   FUN_00ec94d0();                                       // 0xec94d0
extern "C" void   FUN_00f0c290();                                       // 0xf0c290
extern "C" void   FUN_00ed63a0();                                       // 0xed63a0
extern "C" void   FUN_00f03d80();                                       // 0xf03d80
extern "C" void   FUN_00ef8dc0();                                       // 0xef8dc0
extern "C" void   FUN_00f24d90();                                       // 0xf24d90
extern "C" void   FUN_00f21040();                                       // 0xf21040
extern "C" void   FUN_00ebfad0();                                       // 0xebfad0
extern "C" void   FUN_00f19010();                                       // 0xf19010
extern "C" void   FUN_00f02dd0();                                       // 0xf02dd0
extern "C" void   FUN_00f094d0();                                       // 0xf094d0
extern "C" void   FUN_00f32030();                                       // 0xf32030
extern "C" void   FUN_00f41cf0();                                       // 0xf41cf0
extern "C" void   FUN_00ebd340();                                       // 0xebd340
extern "C" void   FUN_00b0f6f0();                                       // 0xb0f6f0
extern "C" void   FUN_00b0f6f0_tc(void* r);                              // 0xb0f6f0 thiscall form
extern "C" void   FUN_00d491b0(int a);                                  // 0xd491b0
extern "C" void   FUN_00d48a00();                                       // 0xd48a00
extern "C" void   FUN_00f084a0();                                       // 0xf084a0
extern "C" void   FUN_00f20440();                                       // 0xf20440
extern "C" void   FUN_00ebfc20();                                       // 0xebfc20
extern "C" void   FUN_00f039a0(int a);                                  // 0xf039a0
extern "C" void   FUN_00b18dd0();                                       // 0xb18dd0
extern "C" void*  FUN_00b1fdb0(void* mgr);                              // 0xb1fdb0 GetAvatar
extern "C" void   FUN_00f31830(void* out, void* a, void* b);            // 0xf31830
extern "C" void   FUN_00b6c280();                                       // 0xb6c280
extern "C" void   FUN_00eeff80();                                       // 0xeeff80
extern "C" void   FUN_00ef0060();                                       // 0xef0060
extern "C" void*  FUN_00b3d3c0_0();                                     // 0xb3d3c0 (no-arg query)
extern "C" void   FUN_00b3d3c0_1(float* v, float r);                    // 0xb3d3c0 (translate helper)
extern "C" void   FUN_00b76d20(float* v, float r, int a, int b, int c); // 0xb76d20
extern float       DAT_0169e384;      // 0x169e384
extern "C" void    FUN_00d48ae0();                                       // 0xd48ae0
extern "C" void    FUN_00f24390();                                       // 0xf24390
extern "C" void    FUN_00f096c0();                                       // 0xf096c0
extern "C" void    FUN_00c2e4e0();                                       // 0xc2e4e0 (bare call form)
extern "C" void    FUN_00ef0cd0_f();                                     // 0xef0cd0 (free form)
typedef unsigned char u8;
typedef unsigned int  u32;
struct Strategy;
extern u32         DAT_015acc34;      // 0x15acc34 game mode (4 == in-game)
extern u8          DAT_015acd18;      // 0x15acd18 mouse-wheel dedup valid flag
extern u32         DAT_015acd14;      // 0x15acd14 last wheel x (float bits)
extern u32         DAT_015acd10;      // 0x15acd10 last wheel y (float bits)
extern u32         DAT_015acd0c;      // 0x15acd0c last wheel arg
extern u8          DAT_016c7b34;      // 0x16c7b34
extern u8          DAT_016c7b35;      // 0x16c7b35
extern u8          DAT_016c7b36;      // 0x16c7b36
extern u32         DAT_016c7aa8;      // 0x16c7aa8
extern u32         DAT_016c7aac;      // 0x16c7aac
extern u32         DAT_016c7b44;      // 0x16c7b44
extern u32         DAT_016c7b48;      // 0x16c7b48
extern u32         DAT_013f6b68;      // 0x13f6b68 (float bits)
extern u32         DAT_014007f4;      // 0x14007f4 (float bits)
extern u8          DAT_0169e37c;      // 0x169e37c
extern "C" u8     FUN_00805180();                                       // 0x805180 WinB0
extern "C" void   FUN_008013d0(void* a, u8 b);                          // 0x8013d0 Set40
extern "C" void   FUN_00801980(void* a, u8 b);                          // 0x801980 Set
extern "C" void*  FUN_00b3d350(u32 a);                                  // 0xb3d350 SP::PlanetModel
extern "C" void*  FUN_00f473a0(u32 size, const char* name, int, int, int, int); // 0xf473a0 EAAllocate
extern "C" void   FUN_00eff790(u32 a);                                  // 0xeff790
extern "C" void   FUN_00eeffc0(u32 a, u32 b);                           // 0xeeffc0
extern "C" void   FUN_00571db0(void* h, u32 a, u32 b, u32 c, u32 d);    // 0x571db0 EA::Messaging::RemoveHandler
extern u8          DAT_0169e380;      // 0x169e380
extern u8          DAT_0169e381;      // 0x169e381
struct CInputState {
    void __thiscall ResetIf(u32 k);                            // 0x697a10
    void __thiscall OnKeyUp(u32 a, u32 b);                     // 0x697a80
    void __thiscall OnMouseWheel(float x, float y, u32 arg);   // 0x697b20
    void __thiscall OnMouseMove(float a, float b, u32 c, u32 d); // 0x697b40
    void __thiscall Reset();                                   // 0x697980
};
struct SHandle {
    void __thiscall B2F7B0();      // 0xb2f7b0
    void __thiscall Ed4e90();      // 0xed4e90
    void __thiscall Ed6b00();      // 0xed6b00
    void __thiscall Eda9a0();      // 0xeda9a0
    void __thiscall F19010();      // 0xf19010
    void __thiscall F41cf0();      // 0xf41cf0
    void __thiscall Ebd340();      // 0xebd340
    void __thiscall Eda130();      // 0xeda130
    void __thiscall Ed6a10();      // 0xed6a10
    void __thiscall B2F7E0(u32 tag);  // 0xb2f7e0
    void __thiscall C2E4E0();         // 0xc2e4e0 (no-op; keeps ecx = receiver)
    void __thiscall B7E1D0();      // 0xb7e1d0
    void __thiscall F32440(int a); // 0xf32440
    void __thiscall Ef72b0();      // 0xef72b0
};
struct SCtrl {
    void __thiscall SetMode(int a, int b, int c);      // 0xf45fd0
    void __thiscall ResetProgress();                   // 0xf190a0
    void __thiscall F19130();                          // 0xf19130
    void __thiscall F1F180();                          // 0xf1f180
};
struct SCtrl6C {
    void __thiscall F10030(int b);                     // 0xf10030, ret 4
    void __thiscall F0F8F0();                          // 0xf0f8f0
};
struct SNounMgr {
    u8* __thiscall F67D90();                           // 0xf67d90, ret 0
    void __thiscall B20FB0();                          // 0xb20fb0, ret 0
    void __thiscall B5E9A0(u32 a);                     // 0xb5e9a0, ret 4
    void __thiscall B5CDE0(u32 a);                     // 0xb5cde0, ret 4
    void* __thiscall B1FDB0();                         // 0xb1fdb0 GetAvatar
    void __thiscall B22930(u32 a);                     // 0xb22930, ret 4
    void __thiscall B1FD50(u32 a);                     // 0xb1fd50, ret 4
    void __thiscall B225D0(u32 a);                     // 0xb225d0, ret 4
    void __thiscall B23610();                          // 0xb23610, ret 0
};
struct CCitySim {
    void __thiscall Ctor();                            // 0xae6a70, ret 0
    void __thiscall AE7350();                          // 0xae7350, ret 0
    void __thiscall AE6570();                          // 0xae6570, ret 0
};
struct CSimSingleton {
    void __thiscall F311C0();                          // 0xf311c0, ret 0
    void __thiscall C2E4E0();                          // 0xc2e4e0, no-op thiscall
};
struct SSimCtor {
    void* __thiscall F30BC0();                         // 0xf30bc0, ret 0
};
struct SScenario {
    void __thiscall B33CE0(u32 v);                     // 0xb33ce0, ret 4
    void __thiscall B33CF0(u32 v);                     // 0xb33cf0, ret 4
    void __thiscall C2E4E0();                          // 0xc2e4e0, no-op thiscall
    void __thiscall E180D0();                          // 0xe180d0, ret 0
    void __thiscall BA3310();                          // 0xba3310, ret 0
};
struct SWorld {
    int  __thiscall B320D0(u32 a);                     // 0xb320d0, ret 4
    void __thiscall B32280(u32 a);                     // 0xb32280, ret 4
    void __thiscall B32450(u32 a);                     // 0xb32450, ret 4
};
struct SAvatar {
    u32  __thiscall C04590();                          // 0xc04590, ret 0
};
struct SMovie {
    u8    m00[0x5c];
    void* mp5c;                        // +0x5c inner buffer
};
struct SWriter {
    u32 __thiscall GetBuffer2();       // 0x93b6c0
};
class Strategy {
public:
    u8        pad00[0x10];
    void*     mp10;                 // +0x10 held simulation object
    void*     mp14;                 // +0x14
    void*     mp18;                 // +0x18
    u8        pad1c[4];
    u8        mInputState[0x48];    // +0x20 embedded SP::cLocalInputState
    void*     mp68;                 // +0x68
    void*     mp6c;                 // +0x6c
    void*     mp70;                 // +0x70
    void*     mp74;                 // +0x74
    void*     mp78;                 // +0x78
    void*     mp7c;                 // +0x7c
    void*     mp80;                 // +0x80
    u32       m84, m88, m8c, m90;   // +0x84.. handler args
    u8        pad94[0x18];
    u32       mac;                  // +0xac
    u32       mb0, mb4;             // +0xb0, +0xb4
    u32       mb8, mbc, mc0, mc4;   // +0xb8.. +0xc4
    u8        padc8[4];
    u32       mcc;                  // +0xcc mode (0/1/2)
    u32       md0;                  // +0xd0
    void*     mpd4;                 // +0xd4
    void*     mpd8;                 // +0xd8

    void __thiscall FUN_00ef07d0(u32 k);
    u8   __thiscall FUN_00ef08b0(u32 a, u32 b);
    u8   __thiscall FUN_00ef0900(u32 x, u32 y, u32 arg);
    u8   __thiscall FUN_00ef09f0(u32 a, u32 b, u32 c, u32 d);
    void __thiscall FUN_00ef0a70(u32 a);
    void __thiscall FUN_00ef0b80();
    void __thiscall FUN_00ef0c80();
    void __thiscall FUN_00ef0cd0();
    u32  __thiscall FUN_00ef0dc0();
    void __thiscall FUN_00ef0de0(u32 a);
    void __thiscall FUN_00ef0ee0();
    void __thiscall FUN_00ef10c0();
    void __thiscall FUN_00ef12d0(int mode);
    void __thiscall FUN_00ef1360();
    void __thiscall FUN_00ef13b0(int dummy);
    void __thiscall FUN_00ef1400();
    void __thiscall FUN_00ef1460();
    void __thiscall FUN_00ef1660();
};
static __forceinline void FUN_00ef0bkey()
{
    void* app = FUN_0067dd10();
    void* a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* a3 = ((void*(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)a2 + 0x40))))(a2, 0xebb801);
    if (a3 != 0) {
        void* r = (void*)((u32(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)a3 + 0xc))))(a3, 0x11966ed);
        if (r != 0)
            FUN_00b0f6f0();
    }
}
// ---- items of slice s00ef07d0 end

// ---- items of slice s00ef16a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl op_delete(void* p);                                          // 0xf47380
extern "C" int*  __cdecl FUN_00eec0d0(int);                                           // 0xeec0d0
extern "C" int   __fastcall FUN_00f3be30(void*);                                      // 0xf3be30 (thiscall)
extern "C" int   __cdecl FUN_00efc520(void);                                          // 0xefc520
extern "C" void  __cdecl FUN_00efc8c0(int);                                           // 0xefc8c0
extern "C" int   __cdecl GetRecorderState(void);                                      // 0x435e90
extern "C" void  __cdecl KillSetiEffects(int, int);                                   // 0x435ed0
extern "C" int*  __fastcall FUN_006c0200(void*);                                      // 0x6c0200 (thiscall)
extern "C" void  __fastcall FUN_00ee31d0(void*);                                      // 0xee31d0 (thiscall)
extern "C" int   __cdecl FUN_00f924e0(float);                                         // 0xf924e0
extern "C" void  __fastcall FUN_00ef72c0(void*);                                      // 0xef72c0 (thiscall, no args)
extern "C" int   __cdecl VerbTray_HandleKeyPress(int key);                            // 0xd4a4a0
extern "C" void  __cdecl FUN_00ebf160(void);                                          // 0xebf160
extern "C" void* __cdecl FUN_00b60a50(int);                                           // 0xb60a50
extern "C" void  __cdecl FUN_00f09580(void);                                          // 0xf09580  CreateBubblePanels
extern "C" void  __cdecl FUN_00f08ef0(void);                                          // 0xf08ef0  CreateMarkerTextDialogs
extern "C" int   __fastcall FUN_00f1e620(void*);                                      // 0xf1e620
extern "C" void* __fastcall FUN_00f33f90_c(void*);                                    // 0xf33f90
extern "C" void* __fastcall FUN_00f1e450_c(void*);                                    // 0xf1e450
extern "C" void* __fastcall FUN_00f3fad0_c(void*);                                    // 0xf3fad0
extern "C" void* __fastcall FUN_00f0fef0_c(void*);                                    // 0xf0fef0
extern "C" void* __fastcall FUN_00f11b60_c(void*);                                    // 0xf11b60
extern "C" void* __fastcall FUN_00ef9d90_c(void*);                                    // 0xef9d90
extern "C" void* __fastcall FUN_00f04740_c(void*);                                    // 0xf04740
extern "C" void* __fastcall FUN_00edaa80_c(void*);                                    // 0xedaa80
extern "C" void* __fastcall FUN_00ed5220_c(void*);                                    // 0xed5220
extern "C" void* __fastcall FUN_00ebc120_c(void*);                                    // 0xebc120
extern "C" void  __fastcall FUN_00b5cde0(void*);                                      // 0xb5cde0 (thiscall)
extern "C" void  __cdecl FUN_00ec92b0(void);                                          // 0xec92b0
extern "C" int*  __cdecl FUN_010408b0(void);                                          // 0x10408b0
extern "C" void  __fastcall FUN_01041bc0(void*);                                      // 0x1041bc0 (thiscall)
extern "C" void  __cdecl FUN_00f02c10(void);                                          // 0xf02c10
extern "C" void  __cdecl FUN_00f20fe0(void);                                          // 0xf20fe0
extern "C" void  __cdecl FUN_00f24d30(void);                                          // 0xf24d30
extern "C" void  __cdecl LoadCreatureGameplayTuning(int, int);                        // 0xd3d870
extern "C" void* __stdcall GetTriggerMgr(int);                                        // 0xb3d4d0
extern "C" void  __cdecl FUN_00adf390(int);                                           // 0xadf390 (thiscall TriggerMgr) UNUSED
extern "C" int   __stdcall GetSetting5(int);                                          // 0x401050
extern "C" void  __cdecl FUN_0045b150(int);                                           // 0x45b150 (thiscall)
extern "C" void* __fastcall FUN_00ec4bb0_r(void*);                                    // 0xec4bb0 (ctor)
extern "C" void* __fastcall FUN_00f391c0_r(void*);                                    // 0xf391c0 (ctor)
extern "C" void  __fastcall FUN_00ec4650_f(void*);                                    // 0xec4650 (thiscall, no args)
extern "C" int   __fastcall FUN_00ff3f00_f(void*);                                    // 0xff3f00 (thiscall, no args)
extern "C" int   __cdecl LAB_00ef2330(void);                                          // 0xef2330
extern "C" void* __cdecl FUN_00b3d310(void);        // 0xb3d310
extern "C" void* __cdecl FUN_00675250(void);        // 0x675250  AchievementsController
extern "C" void* __cdecl FUN_0067dcd0(void);        // 0x67dcd0  GetManager
extern "C" void* __cdecl FUN_0067dd50(void);        // 0x67dd50
extern "C" void* __cdecl FUN_0067de40(void);        // 0x67de40
extern "C" void __fastcall FUN_00697980(void*);                      // 0x697980  cLocalInputState::Reset
extern "C" void __fastcall FUN_00676f20(void*);                      // 0x676f20  DecrementAccumulatorValue
extern "C" void __fastcall FUN_00d272e0(void*);                      // 0xd272e0  ToggleFreeCamera
extern "C" int  __fastcall FUN_00d20940(void*);                      // 0xd20940
extern "C" void __fastcall FUN_00b32220(void*, int);                 // 0xb32220  IncPauseGate
extern "C" void __fastcall FUN_00b316d0(void*, float, float, float, float); // 0xb316d0
extern "C" void __fastcall FUN_00ef9e40(void*);                      // 0xef9e40  cScenarioTutorials::Reset
extern "C" void __fastcall FUN_00f06ce0(void*);                      // 0xf06ce0  RegisterMessageHandlers
extern "C" void __fastcall FUN_00ed5d70(void*);                      // 0xed5d70
extern "C" void __fastcall FUN_00ebd220(void*);                      // 0xebd220
extern "C" char  G_15acc30[];      // 0x15acc30  the Sim singleton
extern "C" char  G_15accc8[];      // 0x15accc8  the scenario record
extern "C" int   G_15acc34;        // 0x15acc34  active mode
extern "C" int   G_15acc2c;        // 0x15acc2c
extern "C" int   G_15accec;        // 0x15accec
extern "C" int   G_15accf0;        // 0x15accf0
extern "C" int   G_15acce0;        // 0x15acce0
extern "C" char  G_15accf8[];      // 0x15accf8
extern "C" int*  G_16c7aa4;        // 0x16c7aa4
extern "C" void* G_16c7b30;        // 0x16c7b30  record factory RefPtr
extern "C" void* G_13effa8[];      // 0x13effa8  base record vtbl
extern "C" void* G_148b0b4[];      // 0x148b0b4  derived record vtbl
extern "C" float G_14853e0;        // 0x14853e0
extern "C" float G_1470f1c;        // 0x1470f1c
extern "C" void* G_148b018[];      // 0x148b018  listener id table (8 entries)
#define VFN(o, off, T) ((T)(*(void***)(o))[((off) >> 2)])
typedef void  (__thiscall *TC_v)(void*);
typedef void  (__thiscall *TC_vii)(void*, int, int);
typedef void  (__thiscall *TC_vpii)(void*, int, void*, int);
typedef void  (__thiscall *TC_vpp)(void*, void*, void*);
typedef void  (__thiscall *TC_vp)(void*, void*);
typedef void  (__thiscall *TC_vpiii)(void*, void*, int, int, int, int);
typedef void  (__thiscall *TC_viii)(void*, int, int, int);
typedef u8    (__thiscall *TC_cii)(void*, int, int);
typedef void* (__thiscall *TC_p)(void*);
typedef void* (__thiscall *TC_pi)(void*, int);
typedef float (__thiscall *TC_pf)(void*);
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int, int, int, int); // 0xf473a0
extern "C" void* __cdecl ZoneObject_new(u32 size, const char* name, int, int, int, int); // 0x926020
extern "C" void  __cdecl eastl_vector_insert(void* dst, const void* src, u32 bytes);  // 0x11e0744
extern "C" int*  __cdecl FUN_00b18e00(u32);                                           // 0xb18e00
extern "C" u8    __cdecl FUN_00401d90(void*);                                         // 0x401d90
struct Stub37f { void F(void* p); };            // 0xf37f20
struct Stub447 { void F(u8 b); };               // 0xf447f0
struct Stub660 { void F(const void* p); };      // 0x6609a0  KeyVec assign
struct Stub466 { u8 F(const void* p); };        // 0xf46630
struct Stub425 { void F(void* p); };            // 0xf42580
struct Stub12d { void F(int v); };              // 0xef12d0
struct Stub697a { void F(u32 key, u32 state); };// 0x697a50  cLocalInputState::OnKeyDown
struct StubED9E { u8 F(int a); };               // 0xed9e60
struct StubF069 { void F(int a); };             // 0xf069a0  BeginRecording
struct StubC776 { void* F(void* out, void* key); }; // 0xc77680  hashtable find
struct Stub8DF  { void F(void* a, void* b, u32 c); }; // 0x8dfcd0  insertNode3
struct Stub4E19 { void F(void* p); };           // 0x4e19a0  SpVector<FillEntry>::push_back
struct StubB966 { void F(void* pos, void* val); }; // 0xb96600  vector insert
struct HashFindOut { u32 a, b, c; };
extern "C" void* __cdecl FUN_00b3d230_s00ef_16a0(int);         // 0xb3d230
struct Sub70 { void FUN_00ebdc20(int a, float b); };  // 0xebdc20 (thiscall)
struct TriggerMgr { void FUN_00adf390(); };                           // 0xadf390 (thiscall, no args)
struct Setter    { void FUN_0045b150(); };                            // 0x45b150 (thiscall, no args)
struct GTM       { void FUN_00b316d0(float, float, float, float); void FUN_00b32220(int); };   // 0xb316d0/0xb32220 (thiscall)
struct Vec2v {                                                        // eastl vector of 4-byte elems
    void* mpBegin; void* mpEnd; void* mpCapacity; u32 mAlloc;
    void Reserve(int n);                  // 0xd01790 (thiscall, ret 4)
    void Reserve4(int n);                 // 0x41e4d0 (thiscall, ret 4)
    void Erase(void* first, void* last);  // 0x50f740 (thiscall, ret 8)
};
struct HT3 {                       // eastl hashtable, 0x20 bytes
    u32   mHead;       // +0x00
    void* mpBuckets;   // +0x04
    u32   mnElements;  // +0x08
    u32   mAlloc;      // +0x0c
    u32   pad1[4];
    void DoFreeNodes(void* buckets, u32 n);   // 0x93dc70 (thiscall, ret 8)
};
struct ModelVector {               // eastl::vector<AutoRefCount<cMWModel>>
    void* mpBegin; void* mpEnd; void* mpCapacity; u32 mAlloc;
    void DoDestroyValues(void* first, void* last);   // 0x5f3680
};
struct cSim {
    u8    b00;         // +0x00
    u8    bDirty;      // +0x01
    char  pad02[0xe];  // +0x02
    void* p10;         // +0x10
    void* p14;         // +0x14
    void* p18;         // +0x18
    void* p1c;         // +0x1c
    char  input[0xc];  // +0x20
    HT3   ht;          // +0x2c
    char  pad4c[0x14]; // +0x4c
    void* p60;         // +0x60
    char  pad64[4];    // +0x64
    void* p68;         // +0x68
    void* p6c;         // +0x6c
    void* p70;         // +0x70
    void* v74;         // +0x74
    void* v78;         // +0x78
    void* p7c;         // +0x7c
    void* p80;         // +0x80
    void* p84;         // +0x84
    void* p88;         // +0x88
    int   n8c;         // +0x8c
    int   n90;         // +0x90
    void* p94;         // +0x94
    void* p98;         // +0x98
    void* p9c;         // +0x9c
    int   nA0;         // +0xa0
    int   nA4;         // +0xa4
    char  padA8[0x24]; // +0xa8
    int   nCC;         // +0xcc
    int   nD0;         // +0xd0
    void* pD4;         // +0xd4
    void* pD8;         // +0xd8
    u8    bDC;         // +0xdc

    u8   FUN_00ef16a0(u32 key, int state);   // 0xef16a0
    void FUN_00ef1930(int a, float b);       // 0xef1930
    void FUN_00ef1ad0(void);                 // 0xef1ad0
    void FUN_00ef1b70(u32 v);                // 0xef1b70
    void FUN_00ef1c40(void);                 // 0xef1c40
    void FUN_00ef1ca0(void);                 // 0xef1ca0
    void FUN_00ef1e00(void);                 // 0xef1e00
    u8   FUN_00ef2370(int);                 // 0xef2370
    u8   FUN_00ef24d0(void);                 // 0xef24d0
    u8   FUN_00ef25a0(void);                 // 0xef25a0
};
#define SETREF(slotExpr, sz, nm, ctor, suboff, addoff, reloff)                          \
    do {                                                                                \
        void* pNew_ = EAAllocate((sz), (nm), 0, 0, 0, 0);                               \
        pNew_ = pNew_ ? ctor(pNew_) : 0;                                                \
        char* pOld_ = (char*)(slotExpr);                                                \
        if (pNew_ != pOld_) {                                                           \
            if (pNew_) VFN((char*)pNew_ + (suboff), (addoff), TC_v)((char*)pNew_ + (suboff)); \
            slotExpr = pNew_;                                                           \
            if (pOld_) VFN(pOld_ + (suboff), (reloff), TC_v)(pOld_ + (suboff));         \
        }                                                                               \
    } while (0)
extern "C" void  __cdecl CreateBubblePanels(void);                                    // 0xf09580
extern "C" void  __cdecl CreateMarkerTextDialogs(void);                               // 0xf08ef0
// ---- items of slice s00ef16a0 end

// ---- items of slice s00ef26c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cModelWorld;
struct cMWModel;
struct cScenarioNode;
struct cGameNounManager;
struct PlanetFlow;
struct PlayMode;
struct cMWModel {
    cModelWorld* mpWorld;   // +0x00
    uint32_t     mFlags;    // +0x04
    uint8_t      pad08[0x3c];
    int32_t      mRefCount; // +0x40
    inline void AddRef() { mFlags &= 0xfffffffeu; mRefCount++; }
    inline void Release();
};
inline void cMWModel::Release()
{
    if (mRefCount > 1) {
        mRefCount--;
    } else {
        typedef void (__thiscall* DF)(void*, cMWModel*, int);
        DF f = (DF)*(void**)(*(char**)mpWorld + 0x170);
        f(mpWorld, this, (int)((mFlags >> 31) & 1));
    }
}
struct AutoRefCount { cMWModel* mpObject; };
struct MWVec {
    AutoRefCount* mpBegin;      // +0x00
    AutoRefCount* mpEnd;        // +0x04
    AutoRefCount* mpCapacity;   // +0x08
    void reserve(uint32_t n);                                   // 0x4e0880
    void DoInsertValue(AutoRefCount* pos, AutoRefCount* value); // 0x423c40
};
struct ByteVec {
    uint8_t* mpBegin;      // +0x00
    uint8_t* mpEnd;        // +0x04
    uint8_t* mpCapacity;   // +0x08
    void insertFill(uint8_t* pos, uint32_t count, const uint8_t* value); // 0x5151b0
};
struct PtrVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
    void ctor(uint32_t n, const void* src);      // 0xb93c60
    void DoInsertValue(void** pos, void** value);// 0xedafd0
};
struct cModelStore {
    uint8_t  pad0000[0x2c10];
    void*    mpBegin;      // +0x2c10
    void*    mpEnd;        // +0x2c14
    uint8_t  pad218[0x2c24 - 0x2c18];
    uint32_t mIndex;       // +0x2c24
    uint8_t  pad228[0x2c50 - 0x2c28];
    int32_t  mField2c50;   // +0x2c50
};
struct cScenarioNode {
    uint8_t       pad00[0x10];
    cModelStore*  mpStore;    // +0x10
    uint8_t       mField14;   // +0x14
    uint8_t       pad15[0x84 - 0x15];
    uint8_t       mField84;   // +0x84
    void    F3C2C0();                 // 0xf3c2c0
    uint8_t F40370();                 // 0xf40370
    void    F427C0();                 // 0xf427c0
    void    F3E3B0(int);              // 0xf3e3b0
    void    F3E6B0(int);              // 0xf3e6b0
    void    F45FD0(int, int, int);    // 0xf45fd0
    uint8_t FED5330(uint32_t);        // 0xed5330
    void    FED5400(uint32_t);        // 0xed5400
    void    FED6540(int);             // 0xed6540
};
struct PlanetFlow {
    uint8_t       mFlag;      // +0x00
    uint8_t       mFlag1;     // +0x01
    uint8_t       pad02[2];
    int32_t       mStage;     // +0x04
    uint8_t       pad08[8];
    uint32_t      mCounter;   // +0x10
    cScenarioNode* mpNode;    // +0x14
    ByteVec       mPending;   // +0x18
    uint8_t       pad24[0x74 - 0x24];
    MWVec         mModels;    // +0x74

    void RebuildModels();     // 0xef26c0
    void FillPending();       // 0xef2940
    void AdvanceStage();      // 0xef2a10
    void FEF0220();           // 0xef0220
    uint8_t FEF02A0();        // 0xef02a0
    void FEF1C40();           // 0xef1c40
};
struct PlayMode {
    uint8_t       pad00[0x14];
    void*         mpField14;    // +0x14
    void*         mpField18;    // +0x18
    uint8_t       pad1c[0x6c - 0x1c];
    void*         mpMovie6c;    // +0x6c
    void*         mpEffects;    // +0x70
    void*         mpScenario74; // +0x74
    void*         mpField78;    // +0x78
    uint8_t       pad7c[0xc8 - 0x7c];
    uint8_t       mVelBlob;     // +0xc8
    uint8_t       padc9[0xcc - 0xc9];
    int32_t       mMode;        // +0xcc
    void*         mpTutorials;  // +0xd4
    void*         mpMovieD8;    // +0xd8
    uint8_t       mFieldDC;     // +0xdc

    void TickBase(int ms);          // 0xef2f70
    void TickFull(int ms);          // 0xef2f90
    void Tick(float a, float b);    // 0xef2fe0
    void FEF0DE0(int);              // 0xef0de0
    void FEF0A70(int);              // 0xef0a70
    void FEF0EE0();                 // 0xef0ee0
};
typedef void*  (__thiscall* PFN_p)(void*);
void*   __cdecl SP_NounManager();                       // 0xb3d300
void*   __cdecl SP_GameTimeManager();                   // 0xb3d380
void*   __cdecl SP_PlanetModel();                       // 0xb3d350
void*   __cdecl FUN_00401010_s00ef_26c0();                         // 0x401010
void*   __cdecl FUN_00eeca30(void* p);                  // 0xeeca30
uint32_t __cdecl FUN_00ef1990(void* first, void* last, void* self); // 0xef1990
void    __cdecl FUN_00ef0b80();                         // 0xef0b80
void    __cdecl FUN_00829110(void* a0, void* a1, void* a2, void* a3, void* a4); // 0x829110
void    __cdecl FUN_00ef2b20(float);                    // 0xef2b20
void    __cdecl FUN_011e0744(void* pos, void* last, int n); // 0x11e0744
int     __cdecl FUN_00bcc800(void* self);               // 0xbcc800
char*   __cdecl FUN_0041e920(void* p);                  // 0x41e920 Property::GetBool
void*   __cdecl FUN_005f4e10(void* first, void* last, void* out); // 0x5f4e10
void    __cdecl FUN_005f3680(void* first, void* last);  // 0x5f3680
void*   __cdecl FUN_00f47380(void* p);                  // 0xf47380 operator delete
struct NounVec {
    uint32_t mUnk0;      // +0x00
    void**   mpBegin;    // +0x04
    void**   mpEnd;      // +0x08
    uint32_t mUnk0c;     // +0x0c
    void*    mField10;   // +0x10
};
struct cGameNounManager {
    void ProcessPending();                                          // 0xb22960
    NounVec* GetGameDataVector(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e); // 0xb21340
    void RemoveNoun(void* noun);                                    // 0xb225d0
};
struct PropObj {
virtual void q00();
virtual void q01();
virtual void q02();
virtual void q03();
virtual void q04();
virtual void q05();
virtual void q06();
virtual void q07();
    virtual void q08();
    virtual uint8_t Query(uint32_t key, void** out);   // +0x24
};
struct Field18 { void F32440(int); };                    // 0xf32440
struct Bag     { void FBA3350(); };                      // 0xba3350
struct C801360 { void Show(); void Hide(); };            // 0x801360 / 0x801380
struct PlanetModel { void ComputeContinents(); };         // 0xb87dc0
struct SpaceMgr {
    uint8_t       pad00[0x14];
    cScenarioNode* mpNode;   // +0x14
    uint8_t       pad18[0x74 - 0x18];
    void*         mpStore74;  // +0x74
    uint8_t       pad78[0xcc - 0x78];
    int32_t       mMode;     // +0xcc
};
#define GMGR (*(SpaceMgr**)0x16c7aa4)
// ---- items of slice s00ef26c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00ef2c70(int ms);  // 0x00ef2c70 (stays in the slice: not this object's)

// ---- items of slice s00ef3370 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   DAT_015acd3c;                  /* 0x015acd3c */
// ---- items of slice s00ef3370 end

// ---- items of slice s00ef40d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __fastcall cString_Ctor(void* self);   // 0x006b5060
extern void __fastcall cString_Dtor(void* self);   // 0x006b5240
extern void* __cdecl SP_PropertyManager();                       // 0x0067de30
extern void* __cdecl SP_WindowManager();                         // 0x0067caa0
extern void* __cdecl SP_MessageServer();                         // 0x0067dcc0
extern void* __cdecl ResourceMan_GetManager();                   // 0x0067dcd0
extern void* __cdecl SPUIHelpers_GetImageFromLayout(void* layout, int id);   // 0x008061c0
extern __int64 __fastcall Meta_GetId(void* self);                            // 0x005508a0
extern void __fastcall AssetView_LoadLayout(void* self);                     // 0x0065a070
extern void __fastcall AssetView_RefreshDetails(void* self);                 // 0x00ef3e40
extern void __fastcall AssetView_Refresh(void* self);                        // 0x00ef3a60
extern void __fastcall cSPUIAssetVerbs_Shutdown(void* self);                 // 0x006566f0
extern void __fastcall FUN_00f47040(void* self);                             // 0x00f47040
extern void __fastcall TextZoomName_Shutdown(void* self);                    // 0x00834e30
extern void __fastcall TextZoomName_Activate(void* self, int a);             // 0x00834a00
extern void __fastcall TextZoomName_Deactivate(void* self, int a);           // 0x00834c60
extern void __fastcall Layer_Shutdown(void* self);                           // 0x006412a0
extern void __cdecl operator_delete(void* p);                                // 0x00f47380
extern void __cdecl SP_GetPropertyAsText(void* bag, int key, void* out);     // 0x006a1360
extern void __cdecl SP_GetPropertyAsKeyInstance(void* bag, int key, int* out); // 0x006a12a0
extern int VTABLE_0148b2d0;    // cLayerKeyProvider primary vtable
extern int VTABLE_0148b2c0;    // cILayer sub-object vtable
extern int VTABLE_0148b2b0;    // cContentValidationSummarizer sub-object vtable
extern int VTABLE_013f1ab0;    // cILayer base vtable
extern int VTABLE_013ec458;    // cContentValidationSummarizer base vtable
typedef unsigned char  uchar;
struct ResKey {
    uint mId;      // 0x00
    uint mType;    // 0x04
    uint mSub;     // 0x08
};
struct Pair8 {      // 8-byte register return (eax:edx)
    uint mLo;
    uint mHi;
};
inline void  WndAddRef(void* p)    { ((void  (__thiscall*)(void*))(*(void***)p)[0x00/4])(p); }
inline void  WndRelease(void* p)   { ((void  (__thiscall*)(void*))(*(void***)p)[0x04/4])(p); }
inline void  WndReleaseVt8(void* p){ ((void  (__thiscall*)(void*))(*(void***)p)[0x08/4])(p); }
inline int   WndGetHash(void* p)   { return ((int (__thiscall*)(void*))(*(void***)p)[0x24/4])(p); }
inline uint  WndGetHashU(void* p)  { return ((uint (__thiscall*)(void*))(*(void***)p)[0x24/4])(p); }
inline int   WndIsVisible(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x28/4])(p); }
inline void* WndGetArea(void* p)   { return ((void*(__thiscall*)(void*))(*(void***)p)[0x38/4])(p); }
inline void  WndSetArea(void* p, void* r) { ((void (__thiscall*)(void*, void*))(*(void***)p)[0x6c/4])(p, r); }
inline void  WndShow(void* p, int a, int b) { ((void (__thiscall*)(void*, int, int))(*(void***)p)[0x7c/4])(p, a, b); }
inline void* WndGetChild(void* p)  { return ((void*(__thiscall*)(void*))(*(void***)p)[0x10/4])(p); }
inline void* WndFindChild(void* p, int id, int recurse)
{
    return ((void*(__thiscall*)(void*, int, int))(*(void***)p)[0xf0/4])(p, id, recurse);
}
inline void  WndHookEvent(void* p, void* owner)
{
    ((void (__thiscall*)(void*, void*))(*(void***)p)[0x108/4])(p, owner);
}
inline int   WndGetSenderType(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x1c/4])(p); }
inline void* WndGetItem(void* p, void* msg, int flag)
{
    return ((void*(__thiscall*)(void*, void*, int))(*(void***)p)[0x10/4])(p, msg, flag);
}
inline void* WndGetItem1(void* p, int flag)
{
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[0x10/4])(p, flag);
}
inline void* WndGetSlot20(void* p)  { return ((void*(__thiscall*)(void*))(*(void***)p)[0x20/4])(p); }
inline void  WndSetSlot34(void* p, void* a)
{
    ((void (__thiscall*)(void*, void*))(*(void***)p)[0x34/4])(p, a);
}
inline void  WindowManager_SetCurrent(void* mgr, void* child)
{
    ((void (__thiscall*)(void*, void*))(*(void***)mgr)[0x10/4])(mgr, child);
}
inline void  MessageServer_Send(void* srv, int msg, void* data, int flag)
{
    ((void (__thiscall*)(void*, int, void*, int))(*(void***)srv)[0x14/4])(srv, msg, data, flag);
}
inline void  WndGetKey(void* p, ResKey* out)
{
    ((void (__thiscall*)(void*, ResKey*))(*(void***)p)[0x18/4])(p, out);
}
inline uchar ResourceMan_Query(void* mgr, ResKey* key, int a, int b, int c, int d, int e)
{
    return ((uchar (__thiscall*)(void*, ResKey*, int, int, int, int, int))(*(void***)mgr)[0x0c/4])
        (mgr, key, a, b, c, d, e);
}
inline uchar PropertyManager_Get(void* pm, int a, int b, void** out)
{
    return ((uchar (__thiscall*)(void*, int, int, void**))(*(void***)pm)[0x2c/4])(pm, a, b, out);
}
inline void ResetWindow(void** slot)
{
    void* p = *slot;
    if (p) {
        *slot = 0;
        WndRelease(p);
    }
}
inline void AssignWindow(void** slot, void* p)
{
    void* old = *slot;
    if (p != old) {
        if (p) WndAddRef(p);
        *slot = p;
        if (old) WndRelease(old);
    }
}
struct cSPUILayout_s00ef_40d0 {
    void* mpVtbl;                                   // 0x000
    void* FindWindowByID(int id, int recursive);    // 0x8105b0
};
extern uchar __cdecl FUN_008068d0(void* wnd, void* image, int flag);         // 0x008068d0
extern uchar __cdecl SetWindowImage(void* wnd, ResKey* key, int flag);       // 0x00807bb0
struct AutoRefCount_s00ef_40d0 {
    void* mpObject;                                     // 0x00
    AutoRefCount_s00ef_40d0& operator=(void* p);                   // 0x00b5f950
    operator void*() const { return mpObject; }
};
extern uchar __cdecl UI_CalloutMessageBox(void* self, int msg);              // 0x00809db0
extern void __cdecl SP_GetPropertyAsKey(void* bag, int key, ResKey* out);    // 0x006a1250
extern uint DAT_015acdf4;      // shared resource type hash
struct cString {
    int mStorage[5];        // 0x00..0x13
};
struct cLayerKeyProvider {
    void*    mpVtbl;        // 0x000
    int      m04;           // 0x004
    int      m08;           // 0x008
    int      m0C;           // 0x00c
    void*    mpLayerVt;     // 0x010  cILayer vtable
    void*    mpSummaryVt;   // 0x014  cContentValidationSummarizer vtable
    int      m18;           // 0x018
    cString  mName;         // 0x01c
    int      mKeyInstance;  // 0x030
    ResKey   mKeyA;         // 0x034
    ResKey   mKeyB;         // 0x040
    void LayerInit(void* param);   // 0x006412c0 (__thiscall)
};
struct AssetNoun {
    void* mpVtbl;           // 0x000
    char  mPad04[0x79 - 4]; // 0x004..0x078
    uchar m79;              // 0x079
    uchar m7A;              // 0x07a
    uchar m7B;              // 0x07b
    uchar m7C;              // 0x07c
    char  mPad7D[0x88 - 0x7d]; // 0x07d..0x087
    int   m88;              // 0x088
};
struct cField {
    void* mpVtbl;           // 0x00
};
inline void FieldSet(cField* f, int value, int id)
{
    ((void (__thiscall*)(cField*, int, int))(*(void***)f)[1])(f, value, id);
}
struct NounFlagBlock {
    int mPad[0x1a];         // 0x000..0x067
    int mFlags[4];          // 0x068
};
struct cAssetPanel {
    void*        mpVtbl0;       // 0x000
    void*        mpVtbl4;       // 0x004
    int          m08;           // 0x008
    cField       mField;        // 0x00c
    char         mPad10[0x10];  // 0x010..0x01f
    cSPUILayout_s00ef_40d0* mpViewLayout;  // 0x020  window layout used by the refresh
    char         mPad24[0x0c];  // 0x024..0x02f
    cSPUILayout_s00ef_40d0* mpLayout;      // 0x030  layout used by the image helpers
    char         mPad34[0x04];  // 0x034..0x037
    void*        mpWin38;       // 0x038
    void*        mpWin3C;       // 0x03c
    void*        mpWin40;       // 0x040
    void*        mpWin44;       // 0x044
    void*        mpWin48;       // 0x048
    void*        mpWin4C;       // 0x04c
    void*        mpWin50;       // 0x050
    void*        mpWin54;       // 0x054
    void*        mpWin58;       // 0x058
    void*        mpWinA[4];     // 0x05c..0x06b
    void*        mpWinB[4];     // 0x06c..0x07b
    void*        mpWin7C;       // 0x07c
    void*        mpWin80;       // 0x080
    void*        mpWin84;       // 0x084
    void*        mpWin88;       // 0x088
    void*        mpWin8C;       // 0x08c
    void*        mpWin90;       // 0x090
    void*        mpVerbs94;     // 0x094
    void*        mpVerbs98;     // 0x098
    void*        mpNoun9C;      // 0x09c
    void*        mpNounA0;      // 0x0a0
    NounFlagBlock* mpFlagsA4;   // 0x0a4
    void*        mpObjA8;       // 0x0a8
    void*        mpZoomAC;      // 0x0ac
    void*        mpZoomB0;      // 0x0b0
    char         mPadB4[0x0c];  // 0x0b4..0x0bf
    uchar        mC0;           // 0x0c0
    char         mPadC1[0x5f];  // 0x0c1..0x11f
    AssetNoun*   mpNoun120;     // 0x120
    void*        mpWin124;      // 0x124
    void*        mpWin128;      // 0x128
    void*        mpWin12C;      // 0x12c
    void*        mpWin130;      // 0x130
    void*        mpWin134;      // 0x134
    void*        mpWin138;      // 0x138
    void*        mpWin13C;      // 0x13c
    void*        mpWin140;      // 0x140
    void*        mpWin144;      // 0x144
    void*        mpWin148;      // 0x148
};
struct Msg {
    void* mpSender;     // 0x00
    void* mpWindow;     // 0x04
    uint  mType;        // 0x08
    int   mSub;         // 0x0c
};
inline float MinRef(float& a, float& b)
{
    return a > b ? b : a;
}
// ---- items of slice s00ef40d0 end

// ---- items of slice s00ef50a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(wcslen)
#pragma warning(disable: 4100)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                                     // 0x00f473a0
void operator delete[](void* p);                                                     // 0x00f47380
struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
};
struct Point {
    float x, y;
    Point(float ax, float ay) : x(ax), y(ay) {}
    Point(const Point& o) : x(o.x), y(o.y) {}
};
struct IWinProc { virtual void wp00(); };
struct IWindow {
    virtual int  AddRef();                                         // +0x00
    virtual int  Release();                                        // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t type);                             // +0x0c
    virtual IWindow* GetParent();                                  // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual const Rect& GetRealArea();                             // +0x38
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
    virtual void SetLocation(float x, float y);                    // +0x64
    virtual void v68();
    virtual void SetLayoutArea(const Rect& r);                     // +0x6c
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetFlag(int flag, bool value);                    // +0x7c
    virtual void SetCaption(const wchar_t* text);                  // +0x80
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
    virtual void AddWinProc(IWinProc* proc);                       // +0x104
};
struct IText {
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
    virtual IWindow* ToWindow();                                   // +0x10
    virtual void func14h(bool b);                                  // +0x14
};
static const uint32_t kITextType = 0x0f15f4bd;
struct IObject {
virtual void o00();
virtual void o04();
virtual void o08();
    virtual void* Cast(uint32_t type);                             // +0x0c
};
struct cSPAssetDataOTDB {
    bool IsLocalAsset();                                           // 0x006418e0
};
struct string16 {                                                  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    static wchar_t gEmptyString[1];                                // 0x01667bac
    string16() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
};
struct IAssetData {
virtual void a00();
virtual void a04();
virtual void a08();
    virtual const wchar_t* GetName();                              // +0x0c
    virtual const wchar_t* GetAuthorName();                        // +0x10
    virtual const wchar_t* GetDescription();                       // +0x14
virtual void a18();
virtual void a1c();
    virtual void GetTags(string16& dst);                           // +0x20
virtual void a24();
virtual void a28();
virtual void a2c();
virtual void a30();
virtual void a34();
virtual void a38();
virtual void a3c();
virtual void a40();
virtual void a44();
virtual void a48();
virtual void a4c();
virtual void a50();
virtual void a54();
virtual void a58();
virtual void a5c();
virtual void a60();
virtual void a64();
virtual void a68();
virtual void a6c();
    virtual bool IsShared();                                       // +0x70
    uint32_t pad04[3];
};
struct cAssetData : IAssetData, IObject {
};
struct cAssetMetadata_s00ef_50a0 {
    uint64_t GetAssetKey();                                        // 0x005508a0
};
class cSPUILayout_s00ef_50a0 { public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
};
namespace SPUIHelpers {
    void SetWindowAreaToParent(IWindow* w);                        // 0x00806bf0
}
namespace SPUIHelpers {
    void CenterWindow(IWindow* w, Point center);                   // 0x00806ca0
}
namespace SPUIHelpers {
    void AutoSizeWindowForText(IWindow* w, int a, int b);          // 0x00806e40
}
struct IAuthManager {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
    virtual void m20();
    virtual bool IsOffline();                                      // +0x24
virtual void m28();
virtual void m2c();
virtual void m30();
virtual void m34();
virtual void m38();
virtual void m3c();
    virtual uint64_t GetUserID();                                  // +0x40
};
namespace SP {
namespace Pollen {
 IAuthManager* AuthManager();   // 0x00607a60
}
}
struct QueueEntry {                                                // 0x70 bytes
    uint32_t pad00[4];
    uint64_t mAssetKey;                                            // +0x10
    uint32_t pad18[(0x68 - 0x18) / 4];
    int      mState;                                               // +0x68
    uint32_t pad6c;
};
struct QueueVector {                                               // eastl::vector<QueueEntry>
    QueueEntry* mpBegin;
    QueueEntry* mpEnd;
    QueueEntry* mpCapacity;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    QueueEntry& operator[](unsigned i) { return mpBegin[i]; }
};
struct cAssetQueue {
    uint32_t pad000[0xc8 / 4];
    QueueVector mEntries;                                          // +0xc8
};
cAssetQueue* AssetQueue();                                         // 0x0067cb30
struct RefCounted {
    virtual int AddRef();                                          // +0x00
    virtual int Release();                                         // +0x04
};
struct cRenderViewController : RefCounted {                        // 0x80 bytes
    cRenderViewController();                                       // 0x00f46dd0
    void Attach(IWindow* w);                                       // 0x00f46eb0
    uint32_t pad[(0x80 - 4) / 4];
};
namespace SP {
class cSPUIAssetVerbs_s00ef_50a0 : public RefCounted { public:                              // 0x5c bytes
    cSPUIAssetVerbs_s00ef_50a0();                                             // 0x00656b00
    void Init(IWindow* w);                                         // 0x00656b80
    uint32_t pad[(0x5c - 4) / 4];
};
}
struct cAssetHelperA8 : RefCounted {                               // 0xd0 bytes
    cAssetHelperA8();                                              // 0x006700d0
virtual void r08();
virtual void r0c();
virtual void r10();
virtual void r14();
virtual void r18();
virtual void r1c();
    virtual void Init(cSPUILayout_s00ef_50a0* layout, cAssetMetadata_s00ef_50a0* md);    // +0x20
    uint32_t pad[(0xd0 - 4) / 4];
};
struct ZoomOffset {
    int a, b, c;
    ZoomOffset() : a(0), b(0), c(0) {}
};
namespace UI {
struct TextZoomName {                                              // 0x78 bytes
    virtual void z00();
    virtual int  AddRef();                                         // +0x04
    virtual int  Release();                                        // +0x08
    TextZoomName();                                                // 0x008345c0
    void SetTargetWindow(IText* text, int a, int b, int c, ZoomOffset off);   // 0x00834fa0
    uint32_t pad[(0x78 - 4) / 4];
};
}
template <class T> struct AutoRefCount_s00ef_50a0 {
    T* mpObject;
    AutoRefCount_s00ef_50a0() : mpObject(0) {}
    AutoRefCount_s00ef_50a0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s00ef_50a0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s00ef_50a0& operator=(T* p)
    {
        if (p != mpObject) {
            T* const old = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
inline void ShowWindow(IWindow* w, bool show)
{
    if (w)
        w->SetFlag(1, show);
}
namespace Simulator {
struct cSPScenarioModeSporepediaLargeAssetView : IWinProc {
    uint32_t pad004[(0x30 - 4) / 4];
    cSPUILayout_s00ef_50a0* mpLayout;                                         // +0x30
    uint32_t pad034;
    AutoRefCount_s00ef_50a0<IWindow> mWinRoot;                                // +0x38 0xf3c6dc19
    AutoRefCount_s00ef_50a0<IWindow> mWinAuthor;                              // +0x3c 0x53d6fe2a
    AutoRefCount_s00ef_50a0<IWindow> mWinDescription;                         // +0x40 0xb456a483
    AutoRefCount_s00ef_50a0<IWindow> mWinTags;                                // +0x44 0xb456a47a
    uint32_t pad048;
    AutoRefCount_s00ef_50a0<IWindow> mWinEdit;                                // +0x4c 0x06135298
    AutoRefCount_s00ef_50a0<IWindow> mWin50;                                  // +0x50 0x06136d30
    AutoRefCount_s00ef_50a0<IWindow> mWin54;                                  // +0x54 0x0615c7a8
    AutoRefCount_s00ef_50a0<IWindow> mWin58;                                  // +0x58 0x07b26750
    AutoRefCount_s00ef_50a0<IWindow> mWinsA[4];                               // +0x5c 0x07cc9c40 + i
    AutoRefCount_s00ef_50a0<IWindow> mWinsB[4];                               // +0x6c 0x07ccb020 + i
    AutoRefCount_s00ef_50a0<IWindow> mWin7c;                                  // +0x7c 0x07b15fc0
    AutoRefCount_s00ef_50a0<IWindow> mWin80;                                  // +0x80 0x07b23b28
    AutoRefCount_s00ef_50a0<IWindow> mWin84;                                  // +0x84 0x07b173e8
    AutoRefCount_s00ef_50a0<IWindow> mWin88;                                  // +0x88 0x07b173f0
    AutoRefCount_s00ef_50a0<IWindow> mWinBakingIndicator;                     // +0x8c 0x3431bd1e
    AutoRefCount_s00ef_50a0<IWindow> mWinBakingForeground;                    // +0x90 0x34a0979a
    AutoRefCount_s00ef_50a0<cRenderViewController> mRenderView;               // +0x94
    AutoRefCount_s00ef_50a0<SP::cSPUIAssetVerbs_s00ef_50a0> mAssetVerbs;                 // +0x98
    cAssetData*     mpAssetData;                                   // +0x9c
    cAssetMetadata_s00ef_50a0* mpMetadata;                                    // +0xa0
    uint32_t pad0a4;
    AutoRefCount_s00ef_50a0<cAssetHelperA8> mHelperA8;                        // +0xa8
    AutoRefCount_s00ef_50a0<UI::TextZoomName> mTagsZoom;                      // +0xac
    AutoRefCount_s00ef_50a0<UI::TextZoomName> mNameZoom;                      // +0xb0
    uint32_t pad0b4[3];
    bool mIsLoaded;                                                // +0xc0

    __forceinline bool IsOwnOrInvalid()
    {
        IAuthManager* am = SP::Pollen::AuthManager();
        cAssetMetadata_s00ef_50a0* md = mpMetadata;
        return am->GetUserID() == md->GetAssetKey() || mpMetadata->GetAssetKey() == (uint64_t)-2 ||
               mpMetadata->GetAssetKey() == (uint64_t)-1;
    }
    void UpdateStats();                                            // 0x00ef4bd0
    void UpdateButtons();                                          // 0x00ef4e40
    void Load();
};
}
// ---- items of slice s00ef50a0 end

// ---- items of slice s00ef5dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t kViewMessages[3];                           // 0x0148b43c
extern uint8_t g_allocTag13f6b3c;                       // 0x013f6b3c
extern uint32_t g_dw15ace34;                            // 0x015ace34
extern const uint32_t g_textGroups[];                   // 0x0148b39c
struct Key_s00ef_5dd0 { uint32_t instanceID, typeID, groupID; };
template <class T> struct ARef {
    T* mp;
    __forceinline ARef& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    __forceinline void Reset()
    {
        T* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
    ~ARef() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};
struct IRefCounted {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};
struct IResource : IRefCounted {
    virtual void v08();
    virtual void* Cast(uint32_t type);                  // +0x0c
};
struct IWindow_s00ef_5dd0 {
virtual void AddRef();
virtual void Release();
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
    virtual uint32_t GetRealArea();                     // +0x38 (value passed on to SetLayoutArea)
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
    virtual void SetLayoutArea(uint32_t area);          // +0x6c
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetFlag(int flag, int value);          // +0x7c
    virtual void SetCaption(const wchar_t* text);       // +0x80
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
    virtual IWindow_s00ef_5dd0* FindWindowByID(uint32_t id, int recursive);   // +0xf0
};
class cSPUILayout_s00ef_5dd0 { public:
    IWindow_s00ef_5dd0* FindWindowByID(uint32_t id, int recursive);           // 0x008105b0
    bool Init(const Key_s00ef_5dd0& key, bool a, uint32_t b);                 // 0x008120d0
    bool SetParentWin(IWindow_s00ef_5dd0* parent, bool a, uint32_t b);        // 0x008121b0
    void SetReloadCallback(void (*cb)(void*, void*, bool), void* ctx);  // 0x00810090
};
struct IAssetData_s00ef_5dd0 {
virtual void a00();
virtual void a04();
virtual void a08();
virtual void a0c();
virtual void a10();
    virtual void a14();
    virtual Key_s00ef_5dd0 GetImageKey();                          // +0x18
virtual void a1c();
virtual void a20();
virtual void a24();
virtual void a28();
virtual void a2c();
virtual void a30();
virtual void a34();
virtual void a38();
virtual void a3c();
    virtual const Key_s00ef_5dd0* GetKey();                        // +0x40
virtual void a44();
virtual void a48();
virtual void a4c();
virtual void a50();
    virtual int64_t GetAuthorID();                      // +0x54
virtual void a58();
virtual void a5c();
virtual void a60();
virtual void a64();
virtual void a68();
virtual void a6c();
virtual void a70();
virtual void a74();
virtual void a78();
virtual void a7c();
virtual void a80();
virtual void a84();
virtual void a88();
virtual void a8c();
    virtual bool GetAssetID(uint64_t& dst);             // +0x90
    uint32_t pad04[3];
};
struct IObject_s00ef_5dd0 : IRefCounted {
    virtual void v08();
    virtual void* Cast(uint32_t type);                  // +0x0c
};
struct cAssetData_s00ef_5dd0 : IAssetData_s00ef_5dd0, IObject_s00ef_5dd0 {
    void AddRef() { IObject_s00ef_5dd0::AddRef(); }
    void Release() { IObject_s00ef_5dd0::Release(); }
    void* Cast(uint32_t type) { return IObject_s00ef_5dd0::Cast(type); }
    bool IsLocalAsset();                                // 0x006418e0
};
struct cAssetMetadata_s00ef_5dd0 : IRefCounted {
    uint32_t pad04[5];
    Key_s00ef_5dd0* GetAssetKeyPtr();                              // 0x005507a0: &this->mAssetKey (+0x18)
};
struct cAssetSummary : IRefCounted {                    // type 0xe742574a
    uint32_t pad04[0x19];
    int mState[4];                                      // +0x68
};
struct IResourceManager {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual bool GetResource(const Key_s00ef_5dd0* key, IResource** out, int a, int b, int c, int d);   // +0x0c
};
namespace EA {
namespace ResourceMan {
 IResourceManager* GetManager();   // 0x0067dcd0
}
}
struct IMessageListener { virtual void ml00(); };
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual void AddListener(IMessageListener* listener, uint32_t msgId);   // +0x24
};
IMessageServer* __cdecl SP_MessageServer_s00ef_5dd0();                      // 0x0067dcc0
struct IConfigManager {
virtual void v00();
virtual void v04();
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
    virtual int GetValue(uint32_t id);                           // +0x30
};
IConfigManager* __cdecl SP_ConfigManager();                      // 0x0067dd30
struct IAuthManager_s00ef_5dd0 {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
    virtual void m20();
    virtual bool IsOffline();                                    // +0x24
};
namespace SP {
namespace Pollen {
 IAuthManager_s00ef_5dd0* AuthManager_s00ef_5dd0();   // 0x00607a60
}
}
struct IWindowManager {
virtual void v00();
virtual void v04();
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
    virtual void SetFocus(int a, IWindow_s00ef_5dd0* w);                    // +0x4c
};
IWindowManager* __cdecl SP_WindowManager_s00ef_5dd0();                      // 0x0067caa0
struct cMetadataFetcher {
    bool FindMetadata(uint32_t lo, uint32_t hi, IResource** out, int flag);   // 0x00612f50
};
struct cAssetQueue_s00ef_5dd0 {
    uint32_t pad[0x5c / 4];
    cMetadataFetcher* mpFetcher;                                  // +0x5c
    void GetAssetFeedEx(uint32_t lo, uint32_t hi);                // 0x00610c20
};
cAssetQueue_s00ef_5dd0* __cdecl AssetQueue_s00ef_5dd0();                                // 0x0067cb30
struct ShowParams {
    uint32_t f0;
    bool b4, b5, b6;
    uint32_t f8;
    bool bc;
    ShowParams();                                                 // 0x006563c0
};
struct cAssetVerbs {
    void Show(int one, ShowParams* p, cAssetData_s00ef_5dd0* asset);         // 0x006571e0
};
struct cAssetHelper70 {
    void SetOnline(int flag);                                     // 0x00f47080
    void SetKey(uint32_t lo, uint32_t hi);                        // 0x00f47170
};
struct cString_s00ef_5dd0 {                                                  // SP::cString
    uint32_t mpBegin, mpEnd, mpCapacity, mAllocator;
    cString_s00ef_5dd0();                                                    // 0x006b5060
    ~cString_s00ef_5dd0();                                                   // 0x006b5240
    void Load(uint32_t id, uint32_t group, const wchar_t* dflt);  // 0x006b54b0
    const wchar_t* GetText();                                     // 0x006b55c0
};
struct cSPEditorVerbIconTray_s00ef_5dd0 {
    int pad[0x18];                    // +0x00..+0x5f
    int mTimesPlayed;                 // +0x60
    int mAdventurePoints;             // +0x64
    void SetCaption(const wchar_t* text);   // 0x00ef5da0
};
extern cSPEditorVerbIconTray_s00ef_5dd0* gAdventureTray;                     // 0x015ee298
int __cdecl AdventurePointsFor(const Key_s00ef_5dd0* k);                     // 0x00eed8c0
int __cdecl IsAssetUnlocked(const Key_s00ef_5dd0* k);                        // 0x00552300
struct PrimaryBase { virtual void p00(); };
struct Primary : PrimaryBase, IMessageListener {                  // the large asset view proper
    void ClearSelection();                                        // 0x00ef5dd0
    void ShowMetadata(IResource* r);                              // 0x00ef5e90
};
struct MsgRegistration {            // App::MessageListenerData
    IMessageServer* server;
    IMessageListener* listener;
    const uint32_t* ids;
    uint32_t count;
    uint32_t n;
};
struct AssetView {
    void* vptr;                     // +0x00
    uint32_t pad04[2];
    cSPUILayout_s00ef_5dd0* mLayout;           // +0x0c
    ARef<IRefCounted> mArg1;        // +0x10
    ARef<IWindow_s00ef_5dd0> mWinFocus;             // +0x14
    ARef<IWindow_s00ef_5dd0> mWinEnable;            // +0x18
    uint32_t pad1c[(0x34 - 0x1c) / 4];
    ARef<IWindow_s00ef_5dd0> mWinCaption;           // +0x34
    uint32_t pad38[(0x58 - 0x38) / 4];
    ARef<IWindow_s00ef_5dd0> mWinHide;              // +0x58
    uint32_t pad5c[(0x70 - 0x5c) / 4];
    cAssetHelper70* mHelper;        // +0x70
    cAssetVerbs* mVerbs;            // +0x74
    ARef<cAssetData_s00ef_5dd0> mAsset;        // +0x78   (ref-count sub-object at +0x10 of the asset)
    ARef<cAssetMetadata_s00ef_5dd0> mMetadata; // +0x7c
    ARef<cAssetSummary> mSummary;   // +0x80
    uint32_t pad84[(0x94 - 0x84) / 4];
    uint32_t mKeyLo, mKeyHi;        // +0x94, +0x98
    uint8_t pad9c;
    uint8_t mBusy;                  // +0x9d
    uint8_t mFlag9e;
    uint8_t mFlag9f;
    int* mVecBegin;                 // +0xa0
    int* mVecEnd;                   // +0xa4
    uint32_t pada8[(0xcc - 0xa8) / 4];
    MsgRegistration mReg;           // +0xcc

    Primary* GetPrimary() { return (Primary*)((char*)this - 0x24); }
    bool SetAsset(IRefCounted* a1, cAssetData_s00ef_5dd0* asset, uint32_t a3, bool a4, int a5);   // 0x00ef6700
};
struct tEmbedUI {
    void* mpVtable;                    // +0x00 (view +0x0c)
    uint32_t mn04, mn08, mn0c, mn10, mn14;   // view +0x10..+0x20
};
class cLargeAssetView {
public:
    void* mpVtbl00;                    // +0x00
    void* mpVtbl04;                    // +0x04
    void* mpVtbl08;                    // +0x08
    tEmbedUI mEmbed;                   // +0x0c
    void* mp24;                        // +0x24  (cAssetView base vptr)
    void* mp28;                        // +0x28
    int32_t mn2c;                      // +0x2c
    void* mp30;                        // +0x30  (cSPUILayout*)
    void* mp34;                        // +0x34  (parent IWindow*)
    void* mp38; void* mp3c; void* mp40; void* mp44; void* mp48;
    void* mp4c; void* mp50; void* mp54; void* mp58;
    void* map5c[4];                    // +0x5c..+0x68
    void* map6c[4];                    // +0x6c..+0x78
    void* mp7c; void* mp80; void* mp84; void* mp88; void* mp8c; void* mp90; void* mp94;
    void* mp98; void* mp9c; void* mpA0; void* mpA4; void* mpA8; void* mpAC; void* mpB0;
    int32_t mnB4;                      // +0xb4
    int32_t mnB8;                      // +0xb8
    int32_t mnBC;                      // +0xbc
    uint8_t mbC0, mbC1, mbC2, mbC3;    // +0xc0..+0xc3
    void* mpC4;                        // +0xc4
    void* mpC8;                        // +0xc8
    void* mpCC;                        // +0xcc
    uint32_t mnD0;                     // +0xd0
    void* mpD4;                        // +0xd4
    uint32_t mnD8;                     // +0xd8
    uint8_t mBuf[0x14];                // +0xdc
    uint32_t mnF0;                     // +0xf0  (message handler id)
    uint32_t mnF4, mnF8, mnFC, mn100;  // +0xf4..+0x100

    void ClearSelection();                              // 0x00ef5dd0
    void ShowMetadata(IResource* r);                    // 0x00ef5e90
    void Destroy();                                     // 0x00ef61b0
    void OnMessage(void* sender, uint32_t msgId);       // 0x00ef6650
    void Load();                                        // 0x00ef50a0
};
struct cPropertyBag {
    bool GetInt32(uint32_t id, void* out);              // 0x00613660
    bool GetFloat(uint32_t id, void* out);              // 0x006135d0
};
struct cTooltip {
    void SetText(const wchar_t* text, void* a, char b); // 0x00835ed0
};
struct tAutoRef {
    void* mp;
    void Init(void* p);                                 // 0x00572660
};
void* __cdecl AllocGame(int32_t size, const void* tag,
                        int32_t a, int32_t b, int32_t c, int32_t d);   // 0x00f473a0
void* __fastcall DialogCtor(void* pThis);               // 0x00810000
void __fastcall FUN_0066f200(void* pThis);              // 0x0066f200
void* __cdecl FUN_009512c0();                           // 0x009512c0
void* __cdecl FUN_009512d0(int32_t a, int32_t b, const char* name, void* res);  // 0x009512d0
cTooltip* __fastcall TooltipCtor(cTooltip* pThis);      // 0x00835cc0
int __cdecl FUN_00ec3ca0(float f);                      // 0x00ec3ca0
void __cdecl FUN_00ef5d80(void* a, void* b, bool c);    // 0x00ef5d80
void __cdecl operator_delete__(void* p);                // 0x00f47380
void __cdecl RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x00571db0
struct cPollinator_s00ef_5dd0 {
    void SubscribeToFeed(void* pArg);                   // 0x00610780
};
cPollinator_s00ef_5dd0* __fastcall Pollinator_Get();               // 0x0067cb30
int64_t __fastcall Meta_GetID64(void* pThis);           // 0x005508a0
void __cdecl FormatString(void* pStr, uint32_t unused, const char* fmt, int64_t value);  // 0x00472f50
// ---- items of slice s00ef5dd0 end

// ---- items of slice s00ef6db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*      gAppPreferences;     // 0x015fd91c
extern char       g_16c7b80[];         // 0x016c7b80
extern uint32_t   g_16c7b84;           // 0x016c7b84
extern char       g_16c7b60[];         // 0x016c7b60
extern int        g_15acef0;           // 0x015acef0
extern "C" int   sscanf(const char*, const char*, ...);
extern "C" void* memcpy(void*, const void*, unsigned);
extern void* gVtbl_A;   // 0x0148b59c
extern void* gVtbl_B;   // 0x0148b58c
extern void* gVtbl_C;   // 0x013eb938
extern void* gVtbl_D;   // 0x013ec458
extern void* gVtbl_E;   // 0x0148b584
struct Simulator_s00ef_6db0;
extern Simulator_s00ef_6db0* gSimulator;          // 0x016c7aa4
void __cdecl FreeNode(void*);                                // 0x00f47380
typedef int   (__thiscall *FN0_i)(void*);
typedef void  (__thiscall *FN1_i)(void*, int);
typedef void  (__thiscall *FN2_ii)(void*, int, int);
typedef void* (__thiscall *FN1_p)(void*, void*);
typedef void* (__thiscall *FN0_p)(void*);
typedef int   (__thiscall *FN1_pi)(void*, int);
typedef void  (__thiscall *FN2_ip)(void*, int, void*);
typedef int   (__thiscall *FN2_ipr)(void*, int, void*);
typedef void* (__thiscall *FN2_pi)(void*, void*, int);
struct IRefCounted_s00ef_6db0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct CSPUILayout {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    void Shutdown(int);
    void* FindWindowByID(int, int);
};
struct CPlayerInventory {
    int  FindCategoryIndex();
    void f5cb180(int);
    void f5ca910();
    CPlayerInventory* f5cae30();
    CPlayerInventory* f5cae30(int);   // 0x005cae30 (equiv t3)
    CPlayerInventory* f5c2e50();
    CPlayerInventory* GetPlayerInventory();
    CPlayerInventory* GetPlayerInventory3(int, int, int);
    CPlayerInventory* GetPlayerInventory2(int, int);
};
struct CSpaceGame {
    CPlayerInventory* GetPlayerInventory();
    CPlayerInventory* GetPlayerInventory3(int, int, int);
    CPlayerInventory* GetPlayerInventory2(int, int);
    void* f_00641770();
};
struct CResource {
    void* GetAllocator();   // 0x007f54d0 (equiv t2)
};
struct Simulator_s00ef_6db0 {
    bool f_ef00d0();
};
struct CSpaceSim {
    void* f_ed4b50(int);
};
struct CDirectPropertyList {
    void SetBoolProperty();
};
struct CAllocMgr {
    void* f_00f3be60(void*);
};
struct CAutoRef {
    void* AsPPTypeParam(int);
};
struct CString {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int   mAllocator;
    CString(unsigned, void*, int);   // 0x006b5770 (equiv t2)
    ~CString();   // 0x006b5240 (equiv t2)
    const char* GetText(int, int);
};
struct CMgrResult {
    char pad[0x84];
    int  f84;
    int  f88;
};
void* __cdecl SP_ConfigManager_s00ef_6db0();                            // 0x0067dd30
void* __cdecl SP_GetSaveArea(int, int);                      // 0x006b1f90
void  __cdecl SP_SaveResource(void*, void*);                 // 0x006b1d50
void* __cdecl FUN_0067cb30();                                // 0x0067cb30
void* __cdecl FUN_0067caf0();                                // 0x0067caf0
void* __cdecl FUN_0067aaf0();                                // 0x0067aaf0
void  __cdecl FUN_00ef5e90(void*, void*);                    // 0x00ef5e90
void* __cdecl FUN_005810a0();                                // 0x005810a0
void* __cdecl FUN_00efc520_s00ef_6db0();                                // 0x00efc520
void* __cdecl FUN_00f3e8a0(void*, void*);                    // 0x00f3e8a0
void* __cdecl FUN_004eb930(void*, int);                      // 0x004eb930
void  __cdecl RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
void* __cdecl FUN_00555a20(void*, void*, void*, uint8_t);    // 0x00555a20
char* __cdecl Property_GetBool();                            // 0x0041e920
void* __cdecl FUN_00612f50(int, int, void*, int);            // 0x00612f50
void  __cdecl SetTooltipText(void*);                         // 0x00806de0
void  __cdecl AnchorWindowToWindow(void*, void*, int, int);  // 0x00807340
void  __cdecl UI_CalloutMessageBox(int, void*);              // 0x00809db0
void  __cdecl EA_Variant_SetBool(void*, void*);              // 0x00422e20
void  __cdecl EA_Variant_Destruct(void*, int);               // 0x0093db80
struct CAssetView {
    void Reset();
    bool RemoveKey(void* key);
    bool HandleMessage(uint32_t msg, void* arg1);
    void sub_ef75b0(int category, int a, int b);
    void sub_ef7600(int category, int a, int b);
    void sub_ef7640(int category, char flag);
    void sub_ef76a0(int category, char flag);
    void sub_efa0b0(int, int);
    void sub_ef4bd0();
    void clear();
};
struct CVec {
    void* begin;        // +0x00
    void* end;          // +0x04
    void f_ef6f00(void*, void*);
    void clear();
    bool RemoveKey(void*);   // 0x00ef6ea0 (equiv t2)
};
struct Vec3f { float x, y, z; };
struct CScenarioTutorialsChecklistUI {
    void sub_ef79d0();
    void sub_ef7a00();
    void sub_ef7a80();
    void sub_ef7b00();
    void sub_ef7b40();
};
struct CHash {
    void* AllocBuckets(uint32_t n);   // 0x00ef7b90 (thiscall member: reads this, ends with `ret 4`)
    void DoRehash(uint32_t n);
};
// ---- items of slice s00ef6db0 end

// ---- items of slice s00ef7d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_simMgr;    // 0x016c7aa4
extern int g_appPrefs;  // 0x015fd91c
extern int     g_16c7b64;
extern __int64 g_deadline;         // 0x16c7b78 (LARGE_INTEGER)
extern "C" void* __cdecl EA_Audio_GetSystemAT();   // 0xa206f0
void FUN_00ef7ec0(int param_1);  // 0x00ef7ec0 (defined below; used by a stub's inline body)
struct Stub {  // generic thiscall target carrier (only conventions matter)
    void* GetPlayerInventory(int, int, int);
    void* FUN_005cae30();
    void* FUN_005c2e50();
    void* GetAllocator();
    int FUN_00f3e8a0(void*);
    void* FUN_00ed4b50(int);
    int FUN_006c0200();
    void* FUN_0067caf0(int, int, int, int, int, int, int, int, int, int);
    void* FUN_0067aaf0(int, int, int, int, int, int, int, int, int, int);
    void* FUN_0067cac0(unsigned, int);
    void* FUN_0067c8c0(unsigned, int);
    void* FindWindowByID(int, int);
    void* GetWindowByID(int);
    void* FUN_00a23d20(int*);
    void* FUN_00a23ef0(int*, int*);
    void* FUN_00ef7ec0(int);
    void* FUN_00ef7b40();
    void  SetBoolProperty();   // 0x0093a2e0 (cDirectPropertyList)
    void  SetTimeLimit(unsigned, int);   // 0x0093a480 (LimitStopwatch)
    void  ReleaseAll();        // 0x00ef7b40
    void* FUN_00ef7b90(void*);
    void* FUN_00ef7a00();
    void* FUN_00efa0b0(int, int);
    void* FUN_00ef75b0(int, int, int);
    void* FUN_00ef7640(int, int);
    void* FUN_00ef7600(int, int, int);
    void* FUN_00ef76a0(int, int);
};
struct VObj {  // polymorphic subobject (vtable slot access)
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* s3(unsigned);
    virtual void* s4();
    virtual void* s5(unsigned);
    virtual void* s6(unsigned);
    virtual void* s7(unsigned);
    virtual void* s8();
    virtual void* s9(unsigned);
    virtual void* s10(unsigned);
    virtual void* s11(unsigned);
    virtual void* s12(unsigned);
    virtual void* s13(unsigned);
    virtual void* s14(unsigned);
    virtual void* s15(unsigned);
    virtual void* s16(unsigned, unsigned);
    virtual void* s17(unsigned);
    virtual void* s18(unsigned);
    virtual void* s19(unsigned);
    virtual void* s20(unsigned);
    virtual void* s21(unsigned);
    virtual void* s22(unsigned);
    virtual void* s23(unsigned);
    virtual void* s24(unsigned);
    virtual void* s25(unsigned);
    virtual void* s26(unsigned);
    virtual void* s27(unsigned);
    virtual void* s28(unsigned);
    virtual void* s29(unsigned);
    virtual void* s30(unsigned);
    virtual void* s31(int, int);
};
struct CEditor_s00ef_7d90 {  // receiver (ECX) carrier for the hashtable/step helpers
    bool FUN_00ef8820(int);
    void FUN_00ef8860();
    bool FUN_00ef84b0();          // this+0x44 = inventory index (default 5)
    int  FUN_00ef8940(int mode);  // hashtable gap count for table mode 0/1
};
extern "C" void* __cdecl SP_ConfigManager_s00ef_7d90();   // 0x67dd30
struct ConfigMgr {              // SP::ConfigManager() result; only slot 0x30 is used here
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual int  HasProperty(unsigned id);      // +0x30
};
struct CGadget {                // receiver (ecx) of the simulator gadget toggles
    char   pad0[0x10];
    void*  mpWindow;            // +0x10  window whose children are toggled
    VObj*  mpFlash;             // +0x14  flash/video player
    char   pad1[0x28 - 0x18];
    int    m28;                 // +0x28
    char   pad2[0x34 - 0x2c];
    int    m34;                 // +0x34
    void   releaseAll();        // 0x00ef7b40
    void   Toggle(int show);    // 0x00ef8550
    void   AudioToggle(int id); // 0x00ef8600
};
struct Qpc {                       // LARGE_INTEGER
    __int64 q;                     // +0x00
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(Qpc* out);  // [0x13cc2b8]
extern int     g_16c7b60_s00ef_7d90;
struct SimManager {                // the global simulator manager (0x016c7aa4)
    char  pad0[0x14];
    Stub* mpAudio;                 // +0x14  audio/voice object
};
// ---- items of slice s00ef7d90 end

// ---- items of slice s00ef8dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gGroupTitles0[5];     // 0x0148b560
extern uint32_t gGroupTitles1[5];     // 0x0148b574
extern int gGroupCount[2];            // 0x0148b5d0
extern wchar_t gEmptyWStr[2];         // 0x01667bac
void* __cdecl operator new(unsigned size, const char* name, int flags, int debugFlags, int file, int line);   // 0x00f473a0
struct Rect_s00ef_8dc0 {
    float left, top, right, bottom;
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
class IWindow_s00ef_8dc0 {
public:
    virtual int AddRef();                                           // +0x00
    virtual int Release();                                          // +0x04
    virtual void v08();
    virtual IWindow_s00ef_8dc0* GetComponent(uint32_t id);                     // +0x0c
    virtual IWindow_s00ef_8dc0* GetParent();                                   // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void SetStateFlag(int state, bool on);                  // +0x28
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual const Rect_s00ef_8dc0* GetArea();                                  // +0x38
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void SetControlID(int id);                              // +0x50
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
    virtual void SetArea(const Rect_s00ef_8dc0* area);                         // +0x6c
    virtual void v70();
    virtual void SetSize(float width, float height);                // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                     // +0x7c
    virtual void SetCaption(const wchar_t* text);                   // +0x80
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
    virtual void AddWindow(IWindow_s00ef_8dc0* child);                         // +0xd8
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
    virtual IWindow_s00ef_8dc0* GetChildByID(int id, bool recursive);          // +0xf0
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
    virtual void AddWinProc(void* proc);                            // +0x104
};
struct WindowRef {
    IWindow_s00ef_8dc0* mp;
    IWindow_s00ef_8dc0* operator->() const { return mp; }
    operator IWindow_s00ef_8dc0*() const { return mp; }
    ~WindowRef()
    {
        if (mp)
            mp->Release();
    }
    WindowRef& operator=(IWindow_s00ef_8dc0* p)
    {
        if (p != mp) {
            IWindow_s00ef_8dc0* const pTemp = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
class cSPUILayout_s00ef_8dc0 {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
    char pad4[0x18 - 4];
    cSPUILayout_s00ef_8dc0();                                                  // 0x00810000
    ~cSPUILayout_s00ef_8dc0();                                                 // 0x00811fe0
    IWindow_s00ef_8dc0* FindWindowByID(uint32_t id, bool recursive);           // 0x008105b0
    bool Init(const ResourceKey& key, bool visible, uint32_t parentID);   // 0x008120d0
    void SetParentWin(IWindow_s00ef_8dc0* parent, bool b, uint32_t id);        // 0x008121b0
    void SetReloadCallback(void (*cb)(void*, int, char), void* user);    // 0x00810090
    void Shutdown(bool b);                                          // 0x00811ad0
};
class cString_s00ef_8dc0 {
public:
    cString_s00ef_8dc0(uint32_t tableID, uint32_t instanceID, const wchar_t* defaultText);   // 0x006b5770
    ~cString_s00ef_8dc0();                                                     // 0x006b5240
    const wchar_t* c_str();                                         // 0x006b55c0
    uint32_t pad[5];
};
struct Variant {
    char mValue[0x10];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant() { mTypeId = 10; mFlags = 2; }
    Variant& operator=(const int& v);                               // 0x00427fd0
    void Destruct(int flags);                                       // 0x0093db80
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
};
class IPropertyList {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
    virtual void SetProperty(uint32_t id, const Variant* value);    // +0x14
};
extern IPropertyList* gAppPreferences_s00ef_8dc0;                              // 0x015fd91c
struct cSaveArea;
cSaveArea* __cdecl GetSaveArea(uint32_t id);                        // 0x006b1f90 (SP::GetSaveArea)
void __cdecl SaveResource(void* props, cSaveArea* area, int flags); // 0x006b1d50 (SP::SaveResource)
void __cdecl RemoveHandler(int handler, int a, int b, int c, int d);// 0x00571db0 (EA::Messaging::RemoveHandler)
int __cdecl SetNumberString(int64_t value, wchar_t* buffer, int bufferSize);   // 0x00881ae0
namespace eastl {
struct true_type {};
}
namespace eastl {
struct prime_rehash_policy_data {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
}
namespace eastl {
struct prime_rehash_policy_s00ef_8dc0 : prime_rehash_policy_data {
    prime_rehash_policy_s00ef_8dc0(float fMaxLoadFactor = 1.f)
    {
        mfMaxLoadFactor = fMaxLoadFactor;
        mfGrowthFactor = 2.f;
        mnNextResize = 0;
    }
    uint32_t GetBucketCount(uint32_t nElementCount) const;          // 0x009213c0
};
}
namespace eastl {
uint32_t __cdecl GetPrevBucketCountOnly(uint32_t n);                // 0x00921340
}
namespace eastl {
struct Link { Link* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    fixed_pool_base() {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset);   // 0x00921260
};
}
namespace eastl {
class fixed_pool_with_overflow : public fixed_pool_base { public:
    void* mpPoolBegin;     // +8
    void* mpPoolEnd;       // +0xc
    uint32_t mnNodeSize;   // +0x10
    fixed_pool_with_overflow() {}
    void deallocate(void* p)
    {
        if ((p >= mpPoolBegin) && (p < mpPoolEnd)) {
            ((Link*)p)->mpNext = mpHead;
            mpHead = ((Link*)p);
        } else
            delete[] (char*)p;
    }
};
}
namespace eastl {
class fixed_hashtable_allocator { public:
    fixed_pool_with_overflow mPool;   // +0
    void* mpBucketBuffer;             // +0x14
    fixed_hashtable_allocator() {}
};
}
struct StepNode {
    int mKey;
    StepNode* mpNext;
};
struct StepInsertResult {
    StepNode* mpNode;
    StepNode** mpBucket;
    bool second;
    StepInsertResult() : mpNode(0), mpBucket(0), second(false) {}
};
struct StepIterator {
    StepNode* mpNode;
    StepNode** mpBucket;
    StepIterator(StepNode* n, StepNode** b) : mpNode(n), mpBucket(b) {}
    explicit StepIterator(StepNode** b) : mpNode(*b), mpBucket(b) {}
    StepIterator(const StepIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    bool operator==(const StepIterator& x) const { return mpNode == x.mpNode; }
};
struct HashFn { HashFn() {} };
struct EqFn { EqFn() {} };
struct ModRangeHashing { ModRangeHashing() {} };
struct RangedHash { RangedHash() {} };
struct UseSelf { UseSelf() {} };
struct StepSet {
    uint32_t mHashCodeBase;                  // +0
    StepNode** mpBucketArray;                // +4
    uint32_t mnBucketCount;                  // +8
    uint32_t mnElementCount;                 // +0xc
    eastl::prime_rehash_policy_data mRehashPolicy;  // +0x10
    eastl::fixed_hashtable_allocator mAllocator;    // +0x1c

    void DoRehash(uint32_t nNewBucketCount);                              // 0x00ef7c00
    void DoFreeNodes(StepNode** pNodeArray, uint32_t n);                  // 0x0068fb70
    StepInsertResult DoInsertValue(const int& key, eastl::true_type);            // 0x00ef8cc0

    void set_max_load_factor(float f)
    {
        eastl::prime_rehash_policy_s00ef_8dc0 rp(f);
        mRehashPolicy = rp;
        const uint32_t nBuckets = rp.GetBucketCount(mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }
    StepIterator end() { return StepIterator(mpBucketArray + mnBucketCount); }
    static StepNode* DoFindNode(StepNode* pNode, const int& k, uint32_t)
    {
        for (; pNode; pNode = pNode->mpNext)
            if (k == pNode->mKey)
                return pNode;
        return 0;
    }
    StepIterator find(const int& k)
    {
        const uint32_t c = (uint32_t)k;
        const uint32_t n = c % mnBucketCount;
        StepNode* const pNode = DoFindNode(mpBucketArray[n], k, c);
        return pNode ? StepIterator(pNode, mpBucketArray + n) : StepIterator(mpBucketArray + mnBucketCount);
    }
    void DoFreeBuckets(StepNode** pBucketArray, uint32_t n)
    {
        if (n > 1 && (void*)pBucketArray != mAllocator.mpBucketBuffer)
            mAllocator.mPool.deallocate(pBucketArray);
    }
    ~StepSet()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
};
struct StepSetBig;
struct StepSetSmall;
struct StepSetBig : StepSet {                // 0x33c bytes: 0x34 table + 0x108 buckets + 0x200 nodes
    StepNode* mBuckets[0x108 / 4];
    char mNodes[0x200];
    void Construct(uint32_t n, const HashFn& h, const ModRangeHashing& h2, const RangedHash& rh, const EqFn& e, const UseSelf& ek,
                   const eastl::fixed_hashtable_allocator& a);                  // 0x00ef86c0
    void HashSetCtor(uint32_t n, const HashFn& h, const EqFn& p, const eastl::fixed_hashtable_allocator& a)
    {
        Construct(n, h, ModRangeHashing(), RangedHash(), p, UseSelf(), a);
    }
    StepSetBig(const HashFn& h = HashFn(), const EqFn& e = EqFn());                                        // 0x00ef9880
    ~StepSetBig() {}
};
struct StepSetSmall : StepSet {              // 0xfc bytes: 0x34 table + 0x48 buckets + 0x80 nodes
    StepNode* mBuckets[0x48 / 4];
    char mNodes[0x80];
    void Construct(uint32_t n, const HashFn& h, const ModRangeHashing& h2, const RangedHash& rh, const EqFn& e, const UseSelf& ek,
                   const eastl::fixed_hashtable_allocator& a);                  // 0x00ef8770
    void HashSetCtor(uint32_t n, const HashFn& h, const EqFn& p, const eastl::fixed_hashtable_allocator& a)
    {
        Construct(n, h, ModRangeHashing(), RangedHash(), p, UseSelf(), a);
    }
    StepSetSmall(const HashFn& h = HashFn(), const EqFn& e = EqFn());                                      // 0x00ef9950
    ~StepSetSmall() {}
};
struct StepInfo {
    int lo;        // first step id of the group
    int hi;        // last step id of the group
    int strId;     // localized title
    int group;     // lesson group index
};
extern StepInfo gStepInfo0[12];       // 0x0148b450
extern StepInfo gStepInfo1[5];        // 0x0148b510
extern ResourceKey gKeyPage;          // 0x015ad268
extern ResourceKey gKeyGroup;         // 0x015ad274
extern ResourceKey gKeyStep;          // 0x015ad280
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;
    WString() : mpBegin(gEmptyWStr), mpEnd(gEmptyWStr), mpCapacity(gEmptyWStr + 1) {}
    void assign(const wchar_t* first, const wchar_t* last);         // 0x00423650
    WString& operator=(const wchar_t* p)
    {
        const wchar_t* pEnd = p;
        while (*pEnd)
            ++pEnd;
        assign(p, p + (pEnd - p));
        return *this;
    }
    ~WString()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
};
struct StringArg {
    uint32_t mKey;
    WString mValue;
};
class ILocalizer {
public:
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
    virtual void FormatString(cString_s00ef_8dc0* str, StringArg* args, int count);   // +0x30
};
class ILocalizerHost {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
    virtual ILocalizer* GetLocalizer();                                   // +0x20
};
ILocalizerHost* FUN_0067de40_s00ef_8dc0();                                           // 0x0067de40
class cScenarioTutorials;
struct cTutorialPage;
struct StepGroup : StepSetSmall {   // 0x14c bytes: the set plus 0x50 bytes of unknown state
    char mUnknown[0x50];
};
class IConfigManager_s00ef_8dc0 {
public:
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
    virtual int GetBool(uint32_t key);                                    // +0x30
};
IConfigManager_s00ef_8dc0* ConfigManager();                                          // 0x0067dd30 (SP::ConfigManager)
struct TutorialRoot {
    cTutorialPage* GetPage(int index);                                    // 0x00ed4b50
    int GetState();                                                       // 0x00985e40
};
struct TutorialApp {
    char pad[0x14];
    TutorialRoot* mpRoot;                 // +0x14
    char pad18[0xd4 - 0x18];
    cScenarioTutorials* mpTutorials;      // +0xd4
};
extern TutorialApp* gTutorialApp;         // 0x016c7aa4
struct cTutorialPage {
    char pad0[0xc];
    IWindow_s00ef_8dc0* mpParentWin;       // +0x0c
    cSPUILayout_s00ef_8dc0* mpLayout;      // +0x10
    WindowRef mpWindow;         // +0x14  (list root)
    WindowRef mpWindowD;        // +0x18  (caption)
    WindowRef mpWindowB;        // +0x1c
    WindowRef mpWindowC;        // +0x20
    bool mbBuilt;               // +0x24
    char pad25[3];
    int mMode;                  // +0x28
    int pad2c;
    int mStepCount;             // +0x30
    char pad34[0x44 - 0x34];

    void Rebuild();                         // 0x00ef9000 (refresh the progress labels)
    void BuildList();                       // 0x00ef9290
    void CreateLayout();                    // 0x00ef9d00
    void UpdateGroup(int group);            // 0x00ef8600
    void FUN_00ef7b40();                    // 0x00ef7b40
};
extern void FUN_00ef7a00(cTutorialPage* page);   // 0x00ef7a00 (thiscall on page)
void FUN_00ef8860();                              // 0x00ef8860
struct Stopwatch {
    char data[0x18];
    Stopwatch(int units, bool start);                                     // 0x0093a560
};
struct LimitStopwatch : Stopwatch {
    uint64_t mnEndTime;
    void SetTimeLimit(uint64_t limit);                                    // 0x0093a480
    LimitStopwatch(int units, bool start) : Stopwatch(units, start) { SetTimeLimit(0); }
};
struct MessageHandlerRef {
    int mHandler;
    int mArgs[4];
    MessageHandlerRef() : mHandler(0)
    {
        mArgs[0] = 0;
        mArgs[1] = 0;
        mArgs[2] = 0;
        mArgs[3] = 0;
    }
    void Remove()
    {
        if (mHandler) {
            int h = mHandler;
            mHandler = 0;
            RemoveHandler(h, mArgs[0], mArgs[1], mArgs[2], mArgs[3]);
        }
    }
    ~MessageHandlerRef() { Remove(); }
};
struct PaintSystem {
    virtual ~PaintSystem() {}                                             // vtbl 0x013eb394
};
struct ContentValidationSummarizer {
    virtual ~ContentValidationSummarizer() {}                             // vtbl 0x013ec458
    int mField8;
    int pad0c;
    ContentValidationSummarizer() : mField8(0) {}
};
class cScenarioTutorials : public PaintSystem, public ContentValidationSummarizer {
public:
    LimitStopwatch mTimer;     // +0x10
    int mCurStep;              // +0x30
    int mCurLesson;            // +0x34
    char pad38[3];
    char mFlag3b, mFlag3c, mFlag3d, mFlag3e, mFlag3f, mFlag40;
    char pad41[3];
    int mField44;
    MessageHandlerRef mHandler;   // +0x48 .. +0x5c
    StepSetBig mSeenSteps;     // +0x5c
    char padBig[0x4a8 - 0x5c - sizeof(StepSetBig)];
    StepGroup mGroups[2];      // +0x4a8, +0x5f4

    cScenarioTutorials();                                                 // 0x00ef9d90
    virtual ~cScenarioTutorials();                                        // 0x00ef9180
    int GetCompletedCount(int mode);                                      // 0x00ef8940
    void SavePrefs();                                                     // 0x00ef8dc0
    void OnStepDone(int step);                                            // 0x00ef9af0
};
struct Stub_s00ef_8dc0 {
    void* FUN_00ef9290();
};
// ---- items of slice s00ef8dc0 end

// ---- items of slice s00ef9e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0067cac0();           // 0x0067cac0
extern "C" void __cdecl RefreshChecklist();              // 0x00efbce0 (call with this already in ecx)
extern void*    g_AppPreferences;      // 0x015fd91c
extern uint32_t g_msgNames[11];        // 0x0148b5d8
extern int      g_catTableA[];         // 0x0148b450 {lo,hi,hash,flag} x 0x10
extern int      g_catTableB[];         // 0x0148b510
extern uint8_t  g_16c7b50[2];          // 0x016c7b50
#define SP_GetSomeMgr FUN_0067cac0
struct CatUpdate { void f(int); };                       // 0x00ef7ec0, ret 4
struct EntryUpdate { void f(int); };                     // 0x00ef9af0, ret 4
struct InputFwd  { void f(int); };                       // 0x00ef8a10, ret 4
struct CatState  { unsigned f(int); };               // 0x00ef7330, ret 4
struct CatValid  { bool f(int); };                   // 0x00ef72d0, ret 4
struct Stopwatch_s00ef_9e40 { void SetTimeLimit(int, int); };       // 0x0093a480, ret 8
struct HashFind  { void find(void*, void*); };           // 0x00a23ef0, ret 8
struct Mgr830    { void f(int); };                       // 0x0067c830, ret 4
struct PrimeRehashPolicyData {
    float mfMaxLoadFactor;   // +0
    float mfGrowthFactor;    // +4
    uint32_t mnNextResize;   // +8
};
struct HashLink { HashLink* mpNext; };
struct FixedPoolBase {
    HashLink* mpHead;        // +0
    HashLink* mpNext;        // +4
    void init(void* memory, uint32_t size, uint32_t nodeSize, uint32_t align, uint32_t offset); // 0x00921260
};
struct FixedPool : FixedPoolBase {
    void* mpPoolBegin;       // +8
    void* mpPoolEnd;         // +0c
    uint32_t mnNodeSize;     // +10
    void deallocate(void* p)
    {
        if ((p >= mpPoolBegin) && (p < mpPoolEnd)) {
            ((HashLink*)p)->mpNext = mpHead;
            mpHead = (HashLink*)p;
        } else {
            delete[] (char*)p;
        }
    }
};
struct FixedHashtableAllocator {
    FixedPool mPool;          // +0
    void* mpBucketBuffer;     // +14
};
struct StepIterator_s00ef_9e40 {
    StepNode* mpNode;
    StepNode** mpBucket;
    StepIterator_s00ef_9e40(StepNode* node, StepNode** bucket) : mpNode(node), mpBucket(bucket) {}
};
struct StepInsertResult_s00ef_9e40 {
    StepNode* mpNode;
    StepNode** mpBucket;
    bool second;
};
struct HashFn_s00ef_9e40 {};
struct EqFn_s00ef_9e40 {};
struct true_type_s00ef_9e40 {};
struct StepSetSmall_s00ef_9e40 {
    uint32_t mHashCodeBase;                 // +00
    StepNode** mpBucketArray;               // +04
    uint32_t mnBucketCount;                 // +08
    uint32_t mnElementCount;                // +0c
    PrimeRehashPolicyData mRehashPolicy;    // +10
    FixedHashtableAllocator mAllocator;     // +1c
    StepNode* mBuckets[0x48 / 4];           // +34
    char mNodes[0x80];                      // +7c

    StepSetSmall_s00ef_9e40(const HashFn_s00ef_9e40& h = HashFn_s00ef_9e40(), const EqFn_s00ef_9e40& e = EqFn_s00ef_9e40()); // 0x00ef9950

    void DoFreeNodes(StepNode** buckets, uint32_t count);              // 0x0068fb70
    void DoInsertRange(StepNode* first, StepNode** firstBucket,
                       StepNode* last, StepNode** lastBucket);         // 0x00ef9a20
    StepInsertResult_s00ef_9e40 DoInsertValue(const int& key, true_type_s00ef_9e40);         // 0x00ef8cc0

    StepIterator_s00ef_9e40 begin() const
    {
        StepNode** bucket = mpBucketArray;
        StepNode* node = *bucket;
        while (node == 0)
            node = *++bucket;
        return StepIterator_s00ef_9e40(node, bucket);
    }
    StepIterator_s00ef_9e40 end() const
    {
        StepNode** bucket = mpBucketArray + mnBucketCount;
        return StepIterator_s00ef_9e40(*bucket, bucket);
    }
    void DoFreeBuckets(StepNode** buckets, uint32_t count)
    {
        if (count > 1 && buckets != mAllocator.mpBucketBuffer)
            mAllocator.mPool.deallocate(buckets);
    }
    StepSetSmall_s00ef_9e40& operator=(const StepSetSmall_s00ef_9e40& other)
    {
        if (this != &other) {
            DoFreeNodes(mpBucketArray, mnBucketCount);
            mnElementCount = 0;
            StepIterator_s00ef_9e40 first = other.begin();
            StepIterator_s00ef_9e40 last = other.end();
            DoInsertRange(first.mpNode, first.mpBucket, last.mpNode, last.mpBucket);
        }
        return *this;
    }
    ~StepSetSmall_s00ef_9e40()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
};
struct StepGroup_s00ef_9e40 {
    StepSetSmall_s00ef_9e40 mSet;         // +000
    uint32_t mUnknown[0x50 / 4]; // +0fc
};
struct EA_Variant {
    char mValue[0x10];         // +00
    uint16_t mFlags;           // +10
    uint16_t mTypeId;          // +12
};
struct IPropertyList_s00ef_9e40 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, EA_Variant** out); // +0x24
};
struct MessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual void Register(void* owner, uint32_t name); // +0x24
};
struct MessageHandlerRef_s00ef_9e40 {
    void* mpServer;            // +00
    void* mpOwner;             // +04
    uint32_t* mpNames;         // +08
    int mnCount;               // +0c
    int mField10;              // +10
};
struct cScenarioTutorials_s00ef_9e40 {
    char pad0[0x10];
    char mTimer[0x20];         // +10
    int mCurStep;              // +30
    int mCurLesson;            // +34
    uint8_t mCurrentBits[3];   // +38
    uint8_t mFlag3b;           // +3b
    char pad3c[4];             // +3c
    uint8_t mFlag40;           // +40
    char pad41[7];             // +41
    MessageHandlerRef_s00ef_9e40 mHandler; // +48
    char mSeenSteps[0x4a8 - 0x5c];
    StepGroup_s00ef_9e40 mGroups[2];      // +4a8, +5f4

    char* self() { return (char*)this; }
    void Reset();                              // 0x00ef9e40
    void UpdateAll();                          // 0x00efa040
    void SetCategoryState(int category, char flag);   // 0x00efa0b0
    void HandleCategoryMessage(int category, int arg); // 0x00efa110
};
// ---- items of slice s00ef9e40 end

// ---- items of slice s00efb4e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
extern Vector3 gVecBase[];              // 0x015ad198  (Vector3 table used by FUN_00ef8390)
struct Simulator_s00ef_b4e0;
extern Simulator_s00ef_b4e0* gSimulator_s00ef_b4e0;
typedef int   (__thiscall *FN1_ir)(void*, int);
typedef void* (__thiscall *FN2_pii)(void*, int, int);
typedef void* (__thiscall *FN1_pi_s00ef_b4e0)(void*, int);
void  __cdecl cUIHints_Update();
void  __cdecl SetBoolProperty(void*);
void  __cdecl SetTimeLimit(void*, int, int);
bool  __cdecl LimitStopwatch_IsTimeUp(void*);
struct CUI {
    uint8_t mPad00[0x30];               // +0x000
    int     mCategory30;                // +0x030  category / checklist page
    void  f_efb4e0();
    void  f_efb9c0(int, int);
    void  f_efbbe0(int, int);
    void  f_efbc90(int, int);
    void  f_efbce0();
    void  f_efbdf0();
    void  f_efbe40(int, int);
    void  f_efbf00();
    bool  f_efc120(int, int);
    // helpers defined elsewhere in this TU
    bool  f_ef8820(int);
    void  f_ef8390(Vector3, int, int, int);
    void  f_efa0b0(int, int);
    void  f_efa110(int, int);
    void  f_ef9d00();
    void  f_ef9000();
    void  f_ef9af0(int);
    void  f_ef7a80();
    void  f_ef7a00();
    void  f_ef7b00();
    void  f_ef7b40();
    bool  f_ef76f0();
    unsigned int f_ef7330(int);
    int   f_ef72d0(int);
    void  f_ef8a10(int);
    void  f_ef7ec0(int);
    void  f_efa1b0();
    void  f_efa040();
    void  f_ef8ed0(int);
    void  f_ef8860();
};
void  __cdecl FUN_00804ed0(void*, void*);
void  __cdecl FUN_00efcae0();
void  __cdecl FUN_0067c830(int);
void  __cdecl SP_KillSetiEffects(int, int);
void* __cdecl EA_GetSystemAT();
void* __cdecl SP_ConfigManager_s00ef_b4e0();
struct MapIter { void* first; void* second; };
static __forceinline MapIter HashFind_s00ef_b4e0(char* map, int key)
{
    MapIter it;
    uint32_t count = *(uint32_t*)(map + 8);          // +0x008 bucket count
    void**   buckets = *(void***)(map + 4);          // +0x004 bucket array
    uint32_t idx = (uint32_t)key % count;
    void*    node = buckets[idx];
    while (node != 0) {
        if (*(int*)node == key) {
            it.first = node;
            it.second = &buckets[idx];
            return it;
        }
        node = *(void**)((char*)node + 4);
    }
    it.first = buckets[count];
    it.second = &buckets[count];
    return it;
}
struct CSpace { void* f_00985e40(); void* f_00ed4b50(int); };
struct cSPUILayout_s00ef_b4e0 {
    void* mpVtbl;                                       // +0x000
    void* FindWindowByID(int id, int recursive);        // 0x008105b0
};
struct CMap { void f_00a23ef0(void*, void*); void f_00a23d20(void*); };
struct CLimit { void SetTimeLimit(int, int); };
// ---- items of slice s00efb4e0 end

// ---- items of slice s00efc270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void** g_016c7b88;              // 0x016c7b88
extern uint8_t g_15ad344;              // 0x015ad344
extern uint8_t g_16c7d18;              // 0x016c7d18
extern float  g_16c7b98, g_16c7b9c, g_16c7ba0;  // Vector3 globals
extern float  g_15ad338, g_15ad33c, g_15ad340, g_15ad29c;
extern float  g_1485720, g_1471064, g_13ec4d0, g_1477fc0, g_1441a88;
extern void*  gSimulator_s00ef_c270;              // 0x016c7aa4
extern void*  g_15fd918_s00ef_c270;               // 0x015fd918
int   __cdecl SP_App();
void* __cdecl FUN_00d20430(int);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl SP_GameInputManager();
void* __cdecl FUN_00b18e00_s00ef_c270(void*);
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eebf80(void*);
void* __cdecl FUN_00f40ea0(void*, int);
void* __cdecl FUN_00f46410(void*, void*, void*);
struct TutorialsTarget {
    void Update();        // 0x00f35f70  (tail-jumped from 0x00efc850)
    void SetFlag(int on); // 0x00f38330
    void Release();       // 0x00f34560
    bool Add(int id);     // 0x00f326d0
};
typedef void  (__thiscall *FN3_iii)(void*, int, int, int);
typedef void* (__thiscall *FN1_i_s00ef_c270)(void*, int);
typedef bool  (__thiscall *TF_bp)(void*, void*);
bool          __cdecl FUN_00efc530(void*);
void          __cdecl FUN_00f33620();
void* __fastcall FUN_00f3e8a0(void*, int, int);
void* __cdecl FUN_00b3d350();
struct Vec3;
Vec3* __fastcall FUN_00b82620(void*, int, void*, void*, void*, int);
void* __fastcall FUN_00b13bb0(void*, int, void*, int);
void  __cdecl FUN_00eec2b0(void*, void*, int, void*, int);
void  __cdecl FUN_00eec8e0(void*, void*, void*);
typedef float (__thiscall *PF_t)(void*);
typedef float* (__thiscall *FN0_fp)(void*);
typedef float* (__thiscall *FN1_fp)(void*, void*);
typedef void* (__thiscall *FN_v58)(void*, int*, int*);
void* __fastcall FUN_007c4900(void*, int);
void* __cdecl FUN_00b82620(void* self, void* a, void* b, void* c, int d);
// ---- items of slice s00efc270 end

// ---- items of slice s00efd020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_15ad294;
struct VObj_s00ef_d020 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* s3(unsigned);
};
struct SelCtx {
    bool FUN_00efde90(int param_2);
};
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
struct V3_s00ef_d020 { float x, y, z; };
struct V4_s00ef_d020 { float x, y, z, w; };
struct Widget {
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
  virtual void SetTarget(void* v);   // +0x54
  void F658e0(void* a);              // 0x00c658e0 (Simulator::cMorphHandle)
  void F666f0(float a, float b);     // 0x00c666f0
  void SetTLerp(float t);            // 0x00c65b50 (cSimpleRotationRing::SetTLerp)
  void SetT(float t);                // 0x00c65af0 (cSimpleRotationRing::SetT)
  void F68ae0(void* a);              // 0x00c68ae0
};
struct Setter_s00ef_d020 {
  void F68d70(void* a, void* b);     // 0x00c68d70
  void F68850(void* a);              // 0x00c68850
};
struct Viewer {
  void GetCameraRay(V3_s00ef_d020* origin, V3_s00ef_d020* dir);                          // 0x007c4900
  void GetCameraLocationInfo(int a, V3_s00ef_d020* out, int b, int c);         // 0x007c3d30
  void F7c46f0(V3_s00ef_d020* origin, V3_s00ef_d020* dir);                                // 0x007c46f0
};
struct AppObj {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
  virtual Viewer* GetViewer();   // +0x58
};
AppObj* AppGet();                // 0x0067dd10 (SP::App)
struct Obj;
struct ThingA {                  // object wrapper used by the pick helpers
virtual void t0();
virtual void t1();
virtual void t2();
virtual void t3();
virtual void t4();
virtual void t5();
virtual void t6();
virtual void t7();
virtual void t8();
virtual void t9();
virtual void t10();
  virtual V3_s00ef_d020* GetPos();          // +0x2c
  virtual V4_s00ef_d020* GetRot();          // +0x30
};
ThingA* GetThingA(Obj* o);                       // 0x00b18e00
float* GetRefCounted18(Obj* o);                  // 0x00eebf80
V3_s00ef_d020* __cdecl FUN_0059aed0(V3_s00ef_d020* sret, const V3_s00ef_d020* a, const V3_s00ef_d020* b);   // 0x0059aed0 (hidden sret first)
struct Picker {
  bool F35bf0();                                 // 0x00b35bf0
};
Picker* __stdcall FUN_00b3d240(ThingA* t, V3_s00ef_d020* origin, V3_s00ef_d020* dir, V3_s00ef_d020* out);  // 0x00b3d240
struct UICtx {
  int idx;           // +0x00
  Obj* obj;          // +0x04
  int p8;
  int fc;            // +0x0c
  void* f10;         // +0x10
  Widget* f14;
  Widget* f18;
  Widget* f1c;
  Widget* f20;
  Widget* f24;
  Widget* f28;
  Widget* f2c;
  char setter30[0x24];   // +0x30 (Setter)
  Widget* f54;
  Widget* f58;
  char pad_5c[0x6c - 0x5c];
  V3_s00ef_d020 v6c;            // +0x6c
  char pad_78[4];
  V3_s00ef_d020 v7c;            // +0x7c
  char pad_88[4];
  char v8c[0x14];    // +0x8c
  float fa0;         // +0xa0
};
extern UICtx* g_UI;          // 0x016c7b88
struct SelState {
  int a, b, c;
  float d;
  uint32_t flags;
};
int __cdecl FUN_00eed720(float* rc, ThingA* t, SelState* st);       // 0x00eed720
float __cdecl FUN_00eec370(float* pos, int b, int* one);              // 0x00eec370
void __cdecl FUN_00eec8e0(float* rc, char* x, char* y);              // 0x00eec8e0
struct PlanetModelRes { V3_s00ef_d020* F82df0(); };                              // 0x00b82df0
PlanetModelRes* __stdcall PlanetModelCtor(V3_s00ef_d020* buf, float* pos, int b, int c, int d, int e);   // 0x00b3d350
struct Mgr { void F3da90(float* rc, int a); };                        // 0x00f3da90
struct G2 { char pad_0[0x14]; void* f14; char pad_18[0x74 - 0x18]; Mgr* f74; };
extern G2* g_G2;                                                      // 0x016c7aa4
extern char g_15acb40_s00ef_d020;
void __cdecl FUN_00eee760(float* rc, void* v8c);                      // 0x00eee760
struct Sub14 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
  virtual bool V5();             // +0x14
};
struct ObjQ {
virtual void o0();
virtual void o1();
virtual void o2();
  virtual void* Query(unsigned id);   // +0x0c
  uint32_t pad_4[4];
  Sub14* f14;                         // +0x14
};
struct ThingB;
struct Thing2 {
  char pad_0[0x54];
  struct SubQ* f54;
};
struct SubQ {
virtual void q0();
virtual void q1();
virtual void q2();
  virtual void* Query(unsigned id);   // +0x0c
};
struct ThingB {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void b7();
virtual void b8();
virtual void b9();
virtual void b10();
  virtual int V11(float f);           // +0x2c
  virtual void V12();
  virtual float V13(void* a);         // +0x34
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
virtual void c5();
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();
virtual void c26();
virtual void c27();
virtual void c28();
virtual void c29();
virtual void c30();
virtual void c31();
  virtual Thing2* V46(unsigned id);   // +0xb8
  bool F88940(unsigned id);           // 0x00c88940
  void F8b1a0(unsigned id);           // 0x00c8b1a0
  void F88a00(unsigned id, float v);  // 0x00c88a00
  void F8a020(unsigned id, float v);  // 0x00c8a020
  void F8ad30(unsigned id, int v);    // 0x00c8ad30
};
float __cdecl ResourceScaledFloat(ThingB* p);    // 0x00eec820
ThingB* GetThingB(ObjQ* o);                       // 0x00b18e00
float* GetRefCountedQ(ObjQ* o);                   // 0x00eebf80
struct Owner { void* F3e900(ObjQ* o); };          // 0x00f3e900
struct Res {                                      // object returned by Owner::F3e900
  bool F253e0();                                  // 0x00f253e0
  bool F255d0();                                  // 0x00f255d0
};
bool __cdecl IsInState2or10(void* p);             // 0x00efcfb0 (ScenarioTutorials_IsInState2or10)
struct InputMgr { virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3(); virtual void i4(); virtual void i5(); virtual bool IsKey(unsigned k); };
InputMgr* GameInputManager_s00ef_d020();                     // 0x00b3d250
bool __cdecl FUN_00f212c0(int v);                 // 0x00f212c0
struct ObjQ2 : ObjQ {
  void F5ce30(void* a, void* b, float c);         // 0x00efce30
};
struct Mgr2 { int F3dc70(Thing2* t); };           // 0x00f3dc70
struct G2b { char pad_0[0x14]; void* f14; char pad_18[0x74 - 0x18]; Mgr2* f74; };
extern G2b* g_G2b;            // 0x016c7aa4
struct Sys14 {
  void F4e90();                                   // 0x00ed4e90 (thiscall, tail call)
};
struct CtlQ {
  char pad_0[6]; bool b6; char pad_7; Owner* f8;
  void Update();
};
struct UICtx2 {
  int idx; ObjQ* obj; int p8; int fc; void* f10;
  Widget* f14; Widget* f18; Widget* f1c; Widget* f20; Widget* f24; Widget* f28; Widget* f2c;
  char setter30[0x24];
  Widget* f54; Widget* f58;
};
extern UICtx2* g_UI2;        // 0x016c7b88
// ---- items of slice s00efd020 end

// ---- items of slice s00efdee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_16c7b98, g_16c7b9c, g_16c7ba0, g_15ad29c, g_16c7b8c_unused;
extern uint8_t g_16c7b8c, g_16c7b8d, g_15ad344, g_15acb40;
extern float g_148b6e8, g_15ad2ac, g_13ec4b4, g_1471064, g_1488874;
extern void* g_15ad348;
extern char  g_15ad2b0;
extern char  g_16c7c28[];
extern int*  g_016c7b88_s00ef_dee0;               // 0x016c7b88 (checklist singleton)
extern void* gSimulator_s00ef_dee0;               // 0x016c7aa4
extern void* g_15fd918_s00ef_dee0;                // 0x015fd918
extern int*  g_15ad298_s00ef_dee0;                // 0x015ad298
typedef int  (__thiscall *FN2_ip_s00ef_dee0)(void*, int, void*);
struct PluginObj {
    void  FUN_00b5cde0(int);                            // 0x00b5cde0
    void  FUN_00b11870(void*);                          // 0x00b11870
    void  FUN_00b10760(float, float, float);            // 0x00b10760
    void  FUN_00b0f950(int);                            // 0x00b0f950
    void  FUN_00b10c40(int);                            // 0x00b10c40
    void  FUN_00b148c0(float, float, float, float);     // 0x00b148c0
    void  FUN_00b12dd0(float*, float*, int);            // 0x00b12dd0
    void  FUN_00b13bb0(float*, int);                    // 0x00b13bb0
    void  FUN_00b104c0(float);                          // 0x00b104c0
    void* FUN_00b81630(void*, void*);                   // 0x00b81630
    void* FUN_00b7f190(void*, void*);                   // 0x00b7f190
    void* FUN_00ff3f00();                               // 0x00ff3f00
    int   FUN_00f41420(void*, void*, int, int);         // 0x00f41420
    int   FUN_00f3b9e0(void*, void*, int);              // 0x00f3b9e0
    void* FUN_00f3e8a0(void*);                          // 0x00f3e8a0
    void  FUN_00f3bbd0(void*, int);                     // 0x00f3bbd0
    void  FUN_00f45970();                               // 0x00f45970
    int   FUN_00c64a70(void*);                          // 0x00c64a70
    void  FUN_00b5f950(void*);                          // 0x00b5f950
    void  FUN_00c8ad30(int, int);                       // 0x00c8ad30
    void  FUN_00efd020();                               // 0x00efd020
    void  FUN_00efbbe0(int, int);                       // 0x00efbbe0
    void  FUN_0093a480(int, int);                       // 0x0093a480
    void  FUN_0093a2e0();                               // 0x0093a2e0
    int   FUN_005ff1c0();                               // 0x005ff1c0
    void  FUN_006ffe00(void*);                          // 0x006ffe00
    void  FUN_007c40c0(void*, void*);                   // 0x007c40c0
    void* FUN_007c4010(void*);                          // 0x007c4010
    void  FUN_007c3d30(void*, void*, void*, void*);     // 0x007c3d30
    int   FUN_006ffbd0(void*, float);                   // 0x006ffbd0
    void* FUN_0041e920();                               // 0x0041e920
    int   FUN_00efc570(void*, float);                   // 0x00efc570 (sub-object in EAX)
};
struct Scene {
    void FUN_00efe8d0(int, int);
    void FUN_00efe930(void*);
    bool FUN_00efeae0(int);
    void FUN_00efebb0(void*);
    void FUN_00efec90(void*);
};
void* __cdecl FUN_00b11870(void*);
void  __cdecl FUN_00b10760(float, float, float);
void* __cdecl FUN_00b81630(void*, void*);
void* __cdecl FUN_00b7f190(void*, void*, void*);
void* __cdecl FUN_00b12dd0(void*, void*, int);
void* __cdecl FUN_00ff3f00(void*);
void* __cdecl FUN_00b13bb0(void*, int);
void* __cdecl FUN_00b104c0(float);
void* __cdecl FUN_00b148c0(int, int, int, int);
void* __cdecl SP_App_s00ef_dee0();
void* __cdecl FUN_00b18e00_s00ef_dee0(void*);
int   __cdecl FUN_00efd970(void*);
int   __cdecl FUN_00efd020();
int   __cdecl FUN_00ebf5b0();
void* __cdecl FUN_00ed54b0(void*);
void* __cdecl FUN_00ed4e90(void*);
bool  __cdecl FUN_00efe5d0(int);
void* __cdecl FUN_00c8ad30(void*, int);
void* __cdecl FUN_00eef570(void*, void*);
void* __cdecl FUN_00eef4b0(void*);
void* __cdecl FUN_00f3d780(void*);
void* __cdecl FUN_00f3b9e0(void*, void*, int);
void* __cdecl FUN_00f41420(void*, void*, int, int);
void  __cdecl FUN_006ffe00(void*);
void  __cdecl FUN_006ffbd0(void*, int);
int   __cdecl FUN_00efc930();
void* __cdecl FUN_00efcbe0(int);
int   __cdecl FUN_00efc570(void*);
int   __cdecl FUN_00efc5f0(int, float);
bool  __cdecl FUN_00efe630(int, void*);
void* __cdecl FUN_00eec3d0(void*, void*);
void* __cdecl FUN_00eece20(void*);
void  __cdecl FUN_00efe110();
void  __cdecl FUN_007c40c0(void*, void*);
void* __cdecl FUN_007c4010(void*);
// ---- items of slice s00efdee0 end

// ---- items of slice s00efee60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*    g_mgr;           // 0x016c7b88 (singleton pointer variable)
extern float   g_016c7d20;       // 0x016c7d20
extern float   g_016c7d24;       // 0x016c7d24
extern uint8_t g_016065f8;       // 0x016065f8
extern uint8_t g_015ad298[];     // 0x015ad298
extern "C" void* __cdecl FUN_00f43420(void*, void*);        // 0x00f43420
extern "C" void* __cdecl FUN_00f3e8a0(int);                 // 0x00f3e8a0
extern "C" void* __cdecl FUN_00f44370(int, void*, void*, float); // 0x00f44370
extern "C" void* __cdecl FUN_00ae66d0(void*);               // 0x00ae66d0
extern "C" void  __cdecl FUN_00efccd0();                    // 0x00efccd0
static inline void** Vt(void* p) { return *(void***)p; }
static inline void VCall0(void* p, int slot)             { ((void (__thiscall*)(void*))(*(void***)p)[slot / 4])(p); }
static inline void VCall1(void* p, int slot, int a)      { ((void (__thiscall*)(void*, int))(*(void***)p)[slot / 4])(p, a); }
static inline void VCall2I(void* p, int slot, int a, int b)   { ((void (__thiscall*)(void*, int, int))(*(void***)p)[slot / 4])(p, a, b); }
static inline void VCall2F(void* p, int slot, int a, float b) { ((void (__thiscall*)(void*, int, float))(*(void***)p)[slot / 4])(p, a, b); }
static inline bool VCallB(void* p, int slot)             { return ((bool (__thiscall*)(void*))(*(void***)p)[slot / 4])(p); }
extern "C" void* __cdecl FUN_00b3d350_s00ef_ee60(void*, void*);        // SP::PlanetModel (cdecl factory)
extern "C" void* __cdecl FUN_00b18e00_s00ef_ee60(void*);               // get object from handle
struct GObj {
    char pad0[0x1b0];
    void* p1b0;            // +0x1b0
    char pad1b4[0x400 - 0x1b4];
    void F43970();
    void BSO(void*, void*);        // 0x00b7f190 BuildSurfaceOrientation
    char FC930();                  // 0x00efc930
    char FC7D0(void*, void*);      // 0x00efc7d0
    void* F32790(void*);           // 0x00f32790 ret 4
    void F33BF0();                 // 0x00f33bf0
    void F38150(void*);            // 0x00f38150 ret 4
    void F34560();                 // 0x00f34560
    void* F336A0(void*);           // 0x00f336a0 ret 4
    void* F33640(void*);           // 0x00f33640 ret 4
    void* F329E0(void*);           // 0x00f329e0 ret 4
    void F36450(int, int, void*);  // 0x00f36450 ret 0xc
    void F38330(int);              // 0x00f38330 ret 4
    void F32410();                 // 0x00f32410
    void F427C0();                 // 0x00f427c0
    void F45970();
};
struct AudioAT {
    void v38(int);
    void v3c(int, float);
    void v40(int, int);
    void v58();
};
struct VObj_s00ef_ee60 {
    void v0();
    void v4();
    void v38(void*);
    void v3c(void*);
    void v40(float);
    void v58();                    // vtable slot +0x58
};
struct RefObj {
    void v0();
    void v4();
};
struct Handle {
    void* v0c(int);               // vtable slot 0xc
};
struct OrientationState {
    char pad0[0x58];
    float f58;     // +0x58
    float f5c;     // +0x5c
    float f60;     // +0x60
    float f64;     // +0x64
    float f68;     // +0x68
    float f6c;     // +0x6c
    float f70;     // +0x70
};
struct Object1b0 {
    char pad0[4];
    OrientationState* p4;  // +0x04
    char pad8[4];
    float value0c;         // +0x0c
};
struct PlacementView {
    char pad0[4];
    OrientationState* p4;  // +0x04
};
struct MgrState {
    char pad0[4];
    void* handle;          // +0x04
    void* p8;              // +0x08
    void* pC;              // +0x0c
    void* p10;             // +0x10
    char pad14[0x0c];
    void* p20;             // +0x20
    char pad24[0x38];
    void* p5c;             // +0x5c
    void* p60;             // +0x60
    int   f64;             // +0x64
    int   f68;             // +0x68
};
struct RotationRing {
    void SetTLerp(float value);  // 0x00c65b50 ret 4
};
struct UI_s00ef_ee60 {
    void* vtable;      // +0x00
    uint8_t f4;        // +0x04
    uint8_t b5;        // +0x05
    char pad6[2];
    GObj* pGame;       // +0x08
    void* pC;          // +0x0c
    void* p10;         // +0x10

    void SetSelectedObject();      // 0x00efe260
    void FwdC6E0(void*);           // 0x00efc6e0 ret 4
    char f_efc930();               // 0x00efc930
    char f_efc7d0(void*, void*);   // 0x00efc7d0 ret 8

    void  f_efee60(void*);         // 0x00efee60
    void* f_efeee0(int);           // 0x00efeee0
    void  f_efefe0();              // 0x00efefe0
    void  f_eff030();              // 0x00eff030
    void  f_eff0c0();              // 0x00eff0c0
    bool  f_eff1e0(int);           // 0x00eff1e0 ret 4
    void  f_eff230(void*);         // 0x00eff230
    void  f_eff280(void*);         // 0x00eff280
    void  f_eff360(void*);         // 0x00eff360
    void  f_eff3b0();              // 0x00eff3b0
    void  f_eff4c0(void*, float);  // 0x00eff4c0 ret 8
    void* f_eff590();              // 0x00eff590
    void  f_eff600(int);           // 0x00eff600 ret 4
};
void __cdecl f_eff6c0(void* obj, char flag);   // 0x00eff6c0
void __cdecl f_eff760(void* obj, char flag);   // 0x00eff760
// ---- items of slice s00efee60 end

// @ 0x00ef0060
void CToolState::Reset()
{
    if (!mActive)
        return;
    if (mRelative)
        GetSomethingCtl()->Set40(true);
    GetSomethingCtl()->Set(false);
    mDX.u = g_16c7aa8;
    mDY.u = g_16c7aac;
    mActive = 0;
}

// @ 0x00ef00b0
void FUN_00ef00b0()
{
    FUN_0067dd20()->v28(0x2ccda9c);
}

// @ 0x00ef00d0
bool FUN_00ef00d0()
{
    return g_15acc34 != 4;
}

// @ 0x00ef00e0
bool FUN_00ef00e0(RaySource* s)
{
    RayA* a = s->mpA;
    if (!a->mpB)
        return true;
    RayObj* obj = a->mpB->v0c(0x17f243b);
    if (!obj)
        return true;
    if (obj->v20() != 0x18eb45e)
        return true;
    if (a->mField60 == 0x2e72cae)
        return true;
    RayOwner* owner = obj->mpOwner;
    if (!owner)
        return true;
    if (!owner->mpField17c)
        return true;
    if (obj->mFlags & 0x200)
        return false;
    Vec3 origin;
    origin.x = s->m08;
    origin.y = s->m0c;
    origin.z = s->m10;
    Vec3 dir;
    dir.x = s->m14 - s->m08;
    dir.y = s->m18 - s->m0c;
    dir.z = s->m1c - s->m10;
    Vec3 norm;
    normalized_safe(&norm, &dir);
    uint index = 0;
    return RayCastParts(&origin.x, &norm.x, owner, &index, 0, 0, 0, 0);
}

// @ 0x00ef0220
void CUpdater::UpdateTransforms()
{
    Obj401010* obj = FUN_00401010();
    Entry12* begin = mpBegin;
    int count = (int)(mpEnd - begin);
    if (count == 0)
        return;
    int off = 0;
    do {
        char* e = (char*)begin + off;
        if (!obj->v18(e)) {
            struct { uint volatile id; uint16_t volatile a; uint16_t volatile b; } data;
            data.a = 0;
            data.b = 1;
            data.id = 0x2ea8fb98;
            obj->v4c(e, &data);
        }
        off += 12;
        --count;
    } while (count != 0);
}

// @ 0x00ef02a0
bool CUpdater::CheckAll()
{
    uint count = (uint)(mpItemsEnd - mpItems);
    for (uint i = 0; i < count; ++i) {
        ItemFlags* p = mpItems[i]->v0xac();
        if (!p)
            return false;
        uint f = p->mFlags;
        uint8_t a = (uint8_t)(f >> 0xe);
        if ((a & 1) == 0)
            return false;
        uint8_t b = (uint8_t)(f >> 0x12);
        if ((b & 1) != 0)
            return false;
    }
    return true;
}

// @ 0x00ef02f0
CEditor* CEditor::Construct()
{
    mpVtbl1 = (const void*)0x13eb394;
    mpVtbl2 = (const void*)0x13ec458;
    mField0c = 0;
    mpVtbl0 = (const void*)0x148b058;
    mpVtbl1 = (const void*)0x148b050;
    mpVtbl2 = (const void*)0x148b040;
    mpField10 = 0;
    mpField14 = 0;
    mpField18 = 0;
    mpField1c = 0;
    InitLocalInputState(&mInput);
    mpField68 = 0;
    mpField6c = 0;
    mpField70 = 0;
    mpField74 = 0;
    mpField78 = 0;
    mpField7c = 0;
    mpServer80 = 0;
    mHandler84 = 0;
    mMsg88 = 0;
    mPrio8c = 0;
    mFlags90 = 0;
    mpServer94 = 0;
    mHandler98 = 0;
    mMsg9c = 0;
    mPrioA0 = 0;
    mFlagsA4 = 0;
    mFlagA8 = 0;
    mFieldAc = 0;
    mFieldB0 = 0;
    mFieldB4 = 0;
    mFieldB8 = 0;
    mFieldBc = 0;
    mFieldC0 = 0;
    mFieldC4 = 2;
    mFieldCc = 0;
    mpFieldD4 = 0;
    mpFieldD8 = 0;
    mFlagDc = 0;
    g_16c7aa4 = this;
    return this;
}

// @ 0x00ef0400
void CEditor::Destroy()
{
    mpVtbl0 = (const void*)0x148b058;
    mpVtbl1 = (const void*)0x148b050;
    mpVtbl2 = (const void*)0x148b040;
    g_16c7aa4 = 0;
    if (mpFieldD8)
        mpFieldD8->v1();
    if (mpFieldD4)
        mpFieldD4->m.v2();
    if (mpServer94) {
        void* s = mpServer94;
        mpServer94 = 0;
        RemoveHandler(s, mHandler98, mMsg9c, mPrioA0, mFlagsA4);
    }
    if (mpServer80) {
        void* s = mpServer80;
        mpServer80 = 0;
        RemoveHandler(s, mHandler84, mMsg88, mPrio8c, mFlags90);
    }
    if (mpField7c)
        mpField7c->v2();
    if (mpField78)
        mpField78->m.v2();
    if (mpField74)
        mpField74->m.v2();
    if (mpField70)
        mpField70->v2();
    if (mpField6c)
        mpField6c->m.v1();
    if (mpField68)
        mpField68->m.v2();
    if (mpField1c)
        mpField1c->v2();
    if (mpField18)
        mpField18->v3();
    if (mpField14)
        mpField14->v2();
    if (mpField10)
        mpField10->m.v2();
    mpVtbl2 = (const void*)0x13ec458;
    mpVtbl1 = (const void*)0x13eb394;
    mpVtbl0 = (const void*)0x13eb938;
}

// @ 0x00ef0570
void FUN_00ef0570()
{
    union { IProp* p; float f; } u;
    if (g_15fd918 && g_15fd918->Get(0x7f2231b, &u.p) && u.p->mType == 1)
        g_15acb40 = *u.p->GetBool();
    g_1569ab8 = (g_15acb40 == 0);
    if (g_15fd918 && g_15fd918->Get(0xe2598dcf, &u.p) && u.p->mType == 0xd)
        g_1688270 = *u.p->GetFloat();
    u.f = 1.0f;
    IProp* prop;
    if (g_15fd918 && g_15fd918->Get(0x5908481, &prop) && prop->mType == 0xd)
        u.f = *prop->GetFloat();
    float cur = g_1688270;
    if (cur != g_156b5d4)
        g_156b5d8 = sqrtf(g_1688270 / g_156b5d4) * u.f;
    return FUN_00eed090();
}

// @ 0x00ef0670
bool CEditor::OnMouseDown(uint id, float x, float y, uint flags)
{
    if (g_15acc34 != 4)
        return 1;
    if (g_15ad298->v3c())
        g_15ad298->v28();
    mInput.OnMouseDown(id, x, y, flags);
    g_15ad298->v50(id, x, y, flags);
    bool r = GameInputManager()->v54(id, x, y, flags);
    if (flags & 0x38)
        g_16c7b34.Enable();
    return r;
}

// @ 0x00ef0730
bool CEditor::OnMouseUp(uint id, float x, float y, uint flags)
{
    if (g_15acc34 != 4)
        return 1;
    mInput.OnMouseUp(id, x, y, flags);
    g_15ad298->v54(id, x, y, flags);
    bool r = GameInputManager()->v58(id, x, y, flags);
    if ((flags & 0x38) == 0) {
        g_16c7b34.Disable();
        g_16c7b34.Reset();
    }
    return r;
}

// @ 0x00ef07d0
void __thiscall Strategy::FUN_00ef07d0(u32 k)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return;

    ((CInputState*)((char*)this_ + 0x20))->ResetIf(k);

    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)im + 0x44))))(im, k);

    void* wm = FUN_0067dcc0();
    u8 has = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)wm + 0x84))))(wm) != 0;
    u8 b = FUN_00805180();
    void* w2 = FUN_0067dcc0();
    void* p = ((void*(__thiscall*)(void*, int))(*((char**)((char*)*(void**)w2 + 0x48))))(w2, 0);
    bool hit = false;
    if (p != 0 &&
        ((u32(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)p + 0xc))))(p, 0xcf428691) != 0)
        hit = true;
    if (hit || !(u8)k || b) {
        void* gm = FUN_00b3d250();
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)gm + 0x48))))(gm, k);
    }

    if ((u8)k)
        return;

    void* im2 = DAT_015ad298;
    if (((u8(__thiscall*)(void*))(*((char**)((char*)*(void**)im2 + 0x3c))))(im2)) {
        void* im3 = DAT_015ad298;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)im3 + 0x28))))(im3);
        void* gm = FUN_00b3d250();
        ((void(__thiscall*)(void*, int))(*((char**)((char*)*(void**)gm + 0x38))))(gm, 3);
    }
    FUN_00eeff80();
    FUN_00ef0060();
}

// @ 0x00ef08b0
u8 __thiscall Strategy::FUN_00ef08b0(u32 a, u32 b)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return 1;
    ((CInputState*)((char*)this_ + 0x20))->OnKeyUp(a, b);
    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32, u32))(*((char**)((char*)*(void**)im + 0x4c))))(im, a, b);
    void* gm = FUN_00b3d250();
    return ((u32(__thiscall*)(void*, u32, u32))(*((char**)((char*)*(void**)gm + 0x50))))(gm, a, b);
}

// @ 0x00ef0900
u8 __thiscall Strategy::FUN_00ef0900(u32 x, u32 y, u32 arg)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return 1;

    if (DAT_015acd18 != 0) {
        if (*(float*)&x == *(float*)&DAT_015acd14 &&
            *(float*)&y == *(float*)&DAT_015acd10 &&
            arg == DAT_015acd0c)
            return 0;
    }

    DAT_015acd14 = x;
    DAT_015acd10 = y;
    DAT_015acd0c = arg;

    ((CInputState*)((char*)this_ + 0x20))->OnMouseWheel(x, y, arg);
    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32, u32, u32))(*((char**)((char*)*(void**)im + 0x58))))(im, x, y, arg);
    FUN_00eeffc0(arg, 0);
    void* gm = FUN_00b3d250();
    return ((u32(__thiscall*)(void*, u32, u32, u32))(*((char**)((char*)*(void**)gm + 0x5c))))(gm, x, y, arg);
}

// @ 0x00ef09f0
u8 __thiscall Strategy::FUN_00ef09f0(u32 a, u32 b, u32 c, u32 d)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return 1;
    ((CInputState*)((char*)this_ + 0x20))->OnMouseMove(a, b, c, d);
    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32, u32, u32, u32))(*((char**)((char*)*(void**)im + 0x5c))))(im, a, b, c, d);
    void* gm = FUN_00b3d250();
    return ((u32(__thiscall*)(void*, u32, u32, u32, u32))(*((char**)((char*)*(void**)gm + 0x60))))(gm, a, b, c, d);
}

// @ 0x00ef0a70
void __thiscall Strategy::FUN_00ef0a70(u32 a)
{
    Strategy* this_ = this;
    void* gm = FUN_00b3d250();
    *(u32*)((char*)gm + 0x110) += 1;

    FUN_00eff790(a);
    ((SHandle*)this_->mp10)->Eda130();
    ((SHandle*)this_->mp14)->Ed6a10();

    ((SHandle*)((char*)this_ + 0xc8))->B2F7E0(0x5e51bb6);
    FUN_00b6c280();
    ((SHandle*)FUN_00b3d350(0x8000000))->B7E1D0();
    ((SHandle*)this_->mp18)->F32440(1);
    ((SHandle*)*(void**)((char*)DAT_016c7aa4 + 0xd4))->Ef72b0();
    FUN_00ef0bkey();

    ((CInputState*)((char*)this_ + 0x20))->Reset();
}

// @ 0x00ef0b30
void __cdecl FUN_00ef0b30()
{
    FUN_00ef0bkey();
    void* gm = FUN_00b3d250();
    return ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)gm + 0x1c))))(gm);
}

// @ 0x00ef0b80
void __thiscall Strategy::FUN_00ef0b80()
{
    Strategy* this_ = this;
    FUN_00ef0bkey();
    ((CInputState*)((char*)this_ + 0x20))->Reset();

    void* gm = FUN_00b3d250();
    ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)gm + 0x1c))))(gm);
    gm = FUN_00b3d250();
    ((void(__thiscall*)(void*, int))(*((char**)((char*)*(void**)gm + 0x38))))(gm, 0);
    gm = FUN_00b3d250();
    FUN_00b18dd0();

    if (DAT_016c7b34 != 0) {
        void* wm = FUN_0067dcc0();
        void* r1 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)wm + 4))))(wm);
        void* r2 = ((void*(__thiscall*)(void*, int))(*((char**)((char*)*(void**)wm + 0x54))))(wm, 1);
        if (r2 == r1)
            ((void(__thiscall*)(void*, int, void*))(*((char**)((char*)*(void**)wm + 0x5c))))(wm, 1, r1);
        DAT_016c7b34 = 0;
    }
    if (DAT_016c7b35 != 0) {
        if (DAT_016c7b36 != 0) {
            void* c1 = FUN_0067cab0();
            FUN_008013d0(c1, 1);
        }
        void* c2 = FUN_0067cab0();
        FUN_00801980(c2, 0);
        DAT_016c7b44 = DAT_016c7aa8;
        DAT_016c7b48 = DAT_016c7aac;
        DAT_016c7b35 = 0;
    }
}

// @ 0x00ef0c80
void __thiscall Strategy::FUN_00ef0c80()
{
    Strategy* this_ = this;
    ((SHandle*)((char*)this_ + 0xc8))->B2F7B0();
    ((SHandle*)this_->mp14)->Ed4e90();
    ((SHandle*)this_->mp14)->Ed6b00();
    ((SHandle*)this_->mp10)->Eda9a0();
    FUN_00f20440();
    FUN_00ebfc20();
    FUN_00f039a0(0);
    void* gm = FUN_00b3d250();
    *(u32*)((char*)gm + 0x110) -= 1;
}

// @ 0x00ef0cd0
void __thiscall Strategy::FUN_00ef0cd0()
{
    Strategy* this_ = this;
    float cam[4];
    float facing[4];
    float up[4];
    float q[4];

    void* app = FUN_0067dd10();
    void* a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* viewer = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)a2 + 0x1c))))(a2);

    ((void(__thiscall*)(void*, void*, void*, void*, int))(*((char**)((char*)*(void**)viewer + 0xc))))
        (viewer, cam, facing, up, 0);
    FUN_00f31830(q, facing, up);

    ((SNounMgr*)FUN_00b3d230())->B5CDE0(0xb03af999);

    app = FUN_0067dd10();
    a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* cam2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)a2 + 0x38))))(a2);
    void* creature = 0;
    if (cam2 != 0)
        creature = ((void*(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)cam2 + 0xc))))(cam2, 0x2a7ecd2);

    if (viewer != 0 && creature != 0) {
        ((void(__thiscall*)(void*, void*, void*, int, int, int))(*((char**)((char*)*(void**)creature + 0x44))))
            (creature, cam, q, 0, 0, 0);
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)creature + 0x28))))(creature, DAT_013f6b68);
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)creature + 0x2c))))(creature, DAT_014007f4);
        ((void(__thiscall*)(void*, int, void*))(*((char**)((char*)*(void**)creature + 0x20))))(creature, 0, viewer);
    }
}

// @ 0x00ef0dc0
u32 __thiscall Strategy::FUN_00ef0dc0()
{
    Strategy* this_ = this;
    void* p = this_->mp6c;
    if (p != 0)
        return ((SWriter*)((SMovie*)p)->mp5c)->GetBuffer2();
    return 0;
}

// @ 0x00ef0de0
void __thiscall Strategy::FUN_00ef0de0(u32 a)
{
    Strategy* this_ = this;
    void* nm = FUN_00b3d300();
    void* avatar = FUN_00b1fdb0(nm);

    void* p = this_->mp68;
    if (p != 0)
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)p + 0x10))))(p, a);

    if (this_->mp68 != 0) {
        if (DAT_0169e381 != 0 && DAT_0169e380 != 0) {
            void* q = (char*)avatar + 0xc0;
            DAT_0169e384 = ((float(__thiscall*)(void*))(*((char**)((char*)*(void**)q + 0xc8))))(q);
        } else {
            DAT_0169e384 = 0.0f;
        }
    }

    if (avatar != 0) {
        void* s = FUN_00b3d3c0_0();
        if (s != 0) {
            void* base = (char*)avatar + 0xc0;
            float v[3];
            ((void(__thiscall*)(void*, float*))(*((char**)((char*)*(void**)base + 0x6c))))(base, v);
            float r = ((float(__thiscall*)(void*, int, int, int))(*((char**)((char*)*(void**)base + 0x70))))(base, 7, 1, 0);
            FUN_00b3d3c0_1(v, r);
            FUN_00b76d20(v, r, 7, 1, 0);
        }
    }
}

// @ 0x00ef0ee0
void __thiscall Strategy::FUN_00ef0ee0()
{
    Strategy* this_ = this;
    SNounMgr* nm = (SNounMgr*)FUN_00b3d300();
    if (nm->F67D90() == 0) {
        SNounMgr* nm2 = (SNounMgr*)FUN_00b3d300();
        nm2->B20FB0();
    }

    FUN_00ef0cd0_f();

    ((SHandle*)((char*)this_ + 0xc8))->B2F7E0(0x5e51bb6);
    FUN_00c2e4e0();
    FUN_00d48a00();
    FUN_00f084a0();
    ((SCtrl*)this_->mp78)->ResetProgress();

    { void* p = this_->mp68; ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)p + 0x1c))))(p); }

    ((SCtrl6C*)this_->mp6c)->F10030(0);
    ((SCtrl*)this_->mp78)->F1F180();

    SNounMgr* n3 = (SNounMgr*)FUN_00b3d230();
    n3->B5E9A0(0);
    FUN_00d491b0(1);

    void* tick = FUN_00b3d330();

    void* city = DAT_0167a690;
    if (city == 0) {
        void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0) {
            ((CCitySim*)p)->Ctor();
            city = p;
        } else
            city = 0;
        DAT_0167a690 = city;
    }
    ((CCitySim*)city)->AE7350();

    city = DAT_0167a690;
    if (city == 0) {
        void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0) {
            ((CCitySim*)p)->Ctor();
            city = p;
        } else
            city = 0;
        DAT_0167a690 = city;
    }
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x50))))(tick, city);

    void* sim = DAT_0168d824;
    if (sim == 0) {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0)
            sim = ((SSimCtor*)p)->F30BC0();
        else
            sim = 0;
        DAT_0168d824 = sim;
    }
    ((CSimSingleton*)sim)->C2E4E0();

    sim = DAT_0168d824;
    if (sim == 0) {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0)
            sim = ((SSimCtor*)p)->F30BC0();
        else
            sim = 0;
        DAT_0168d824 = sim;
    }
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x50))))(tick, sim);

    ((SScenario*)FUN_00b3d4c0())->C2E4E0();
    ((SScenario*)FUN_00b3d240())->B33CE0(0xd39010);
    ((SScenario*)FUN_00b3d240())->B33CF0(0xef00e0);

    void* app = FUN_0067dd10();
    void* a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* a3 = ((void*(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)a2 + 0x40))))(a2, 0xebb801);
    if (a3 != 0) {
        void* r = (void*)((u32(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)a3 + 0xc))))(a3, 0x11966ed);
        if (r != 0)
            FUN_00b0f6f0_tc(r);
    }

    ((CInputState*)((char*)this_ + 0x20))->Reset();
}

// @ 0x00ef10c0
void __thiscall Strategy::FUN_00ef10c0()
{
    Strategy* this_ = this;

    ((SScenario*)FUN_00b3d240())->B33CE0(0);
    ((SScenario*)FUN_00b3d240())->B33CF0(0);

    DAT_0169e37c = 0;

    ((SScenario*)FUN_00b3d400())->E180D0();
    FUN_00b6c280();
    ((SScenario*)FUN_00b3d4c0())->BA3310();

    {
    void* tick = FUN_00b3d330();

    void* sim = DAT_0168d824;
    if (sim == 0) {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0)
            sim = ((SSimCtor*)p)->F30BC0();
        else
            sim = 0;
        DAT_0168d824 = sim;
    }
    ((CSimSingleton*)sim)->F311C0();

    sim = DAT_0168d824;
    if (sim == 0) {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0)
            sim = ((SSimCtor*)p)->F30BC0();
        else
            sim = 0;
        DAT_0168d824 = sim;
    }
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x54))))(tick, sim);

    void* city = DAT_0167a690;
    if (city == 0) {
        void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0) {
            ((CCitySim*)p)->Ctor();
            city = p;
        } else
            city = 0;
        DAT_0167a690 = city;
    }
    ((CCitySim*)city)->AE6570();

    city = DAT_0167a690;
    if (city == 0) {
        void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p != 0) {
            ((CCitySim*)p)->Ctor();
            city = p;
        } else
            city = 0;
        DAT_0167a690 = city;
    }
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x54))))(tick, city);
    }

    ((SCtrl*)this_->mp78)->F19130();
    ((SCtrl6C*)this_->mp6c)->F0F8F0();

    { void* p = this_->mp68; ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)p + 0x20))))(p); }

    ((SHandle*)((char*)this_ + 0xc8))->B2F7B0();

    ((SNounMgr*)FUN_00b3d230())->B5CDE0(0);

    SNounMgr* nm = (SNounMgr*)FUN_00b3d300();
    void* avatar = nm->B1FDB0();

    ((SNounMgr*)FUN_00b3d300())->B22930(((SAvatar*)avatar)->C04590());
    ((SNounMgr*)FUN_00b3d300())->B1FD50(0);
    ((SNounMgr*)FUN_00b3d300())->B225D0((u32)avatar);

    FUN_00f096c0();
    FUN_00d48ae0();
    FUN_00f24390();

    if (this_->md0 != 2)
        ((SNounMgr*)FUN_00b3d300())->B23610();

    if (((SWorld*)FUN_00b3d380())->B320D0(0x4bf38a8) > 0)
        ((SWorld*)FUN_00b3d380())->B32280(0x4bf38a8);

    ((SWorld*)FUN_00b3d380())->B32450(0);

    void* fx = FUN_0067ddd0();
    void* o = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)fx + 0x5c))))(fx);
    ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0x38))))(o);
}

// @ 0x00ef12d0
void __thiscall Strategy::FUN_00ef12d0(int mode)
{
    Strategy* this_ = this;
    int cur = (int)this_->mcc;
    if (cur == mode)
        return;
    if (cur == 1 && mode == 2) {
        FUN_00ef0c80();
        this_->mcc = 2;
        ((SCtrl*)this_->mp74)->SetMode(2, 0, 0);
        FUN_00ef0ee0();
        return;
    }
    if (cur == 2 && mode == 1) {
        FUN_00ef10c0();
        this_->mcc = 1;
        ((SCtrl*)this_->mp74)->SetMode(1, 0, 0);
        FUN_00ef0a70(0);
        return;
    }
    this_->mcc = (u32)mode;
}

// @ 0x00ef1360
void __thiscall Strategy::FUN_00ef1360()
{
    Strategy* this_ = this;
    if (this_->mcc == 1)
        return;
    if (this_->mcc == 2) {
        FUN_00ef10c0();
        this_->mcc = 1;
        ((SCtrl*)this_->mp74)->SetMode(1, 0, 0);
        FUN_00ef0a70(0);
        return;
    }
    this_->mcc = 1;
}

// @ 0x00ef13b0
void __thiscall Strategy::FUN_00ef13b0(int dummy)
{
    Strategy* this_ = this;
    (void)dummy;
    if (this_->mcc == 2)
        return;
    if (this_->mcc == 1) {
        FUN_00ef0c80();
        this_->mcc = 2;
        ((SCtrl*)this_->mp74)->SetMode(2, 0, 0);
        FUN_00ef0ee0();
        return;
    }
    this_->mcc = 2;
}

// @ 0x00ef1400
void __thiscall Strategy::FUN_00ef1400()
{
    Strategy* this_ = this;
    FUN_00ef10c0();
    ((SCtrl*)this_->mp74)->SetMode(2, 0, 0);
    ((SCtrl*)this_->mp78)->ResetProgress();
    FUN_00ef0ee0();
}

// @ 0x00ef1430
u8 __stdcall FUN_00ef1430(u32 a, u32 pev)
{
    (void)a;
    if (*(int*)(pev + 8) == 0x287259f6 &&
        *(int*)(pev + 0xc) >= (int)0xbbbb0000 &&
        *(int*)(pev + 0xc) <= (int)0xbbbb0003)
        return 1;
    return 0;
}

// @ 0x00ef1460
void __thiscall Strategy::FUN_00ef1460()
{
    Strategy* this_ = this;
    void* tick = FUN_00b3d330();
    void* ps = FUN_00d539d0();
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x54))))(tick, ps);

    ps = FUN_00d539d0();
    ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)ps + 0x20))))(ps);

    if (this_->mcc != 0)
        this_->mcc = 0;
    if (this_->md0 == 0) {
        FUN_00ec94d0();
        FUN_00f0c290();
    }
    FUN_00f24d90();
    FUN_00f21040();
    FUN_00ebfad0();

    if (this_->mp10 != 0) {
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)this_->mp10 + 8))))(this_->mp10);
        if (this_->mp10 != 0) {
            void* o = this_->mp10;
            this_->mp10 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0x3c))))((char*)o + 0x3c);
        }
    }
    if (this_->mp14 != 0) {
        FUN_00ed63a0();
        void* o = this_->mp14;
        this_->mp14 = 0;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))(o);
    }
    if (this_->mpd8 != 0) {
        FUN_00f03d80();
        void* o = this_->mpd8;
        this_->mpd8 = 0;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 4))))(o);
    }
    if (this_->mpd4 != 0) {
        FUN_00ef8dc0();
        if (this_->mpd4 != 0) {
            void* o = this_->mpd4;
            this_->mpd4 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))((char*)o + 4);
        }
    }
    FUN_00f24d90();
    FUN_00f21040();
    FUN_00ebfad0();

    {
        void* w = this_->mp78;
        u32 x = *(u32*)((char*)w + 0x90);
        this_->mb8 = this_->mac;
        this_->mbc = this_->mb0;
        this_->mc0 = this_->mb4;
        this_->mc4 = x;
        if (w != 0) {
            FUN_00f19010();
            if (this_->mp78 != 0) {
                void* o = this_->mp78;
                this_->mp78 = 0;
                ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))((char*)o + 4);
            }
        }
    }
    if (this_->mp6c != 0) {
        void* o = this_->mp6c;
        this_->mp6c = 0;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 4))))((char*)o + 0x38);
    }
    {
        void* o = this_->mp68;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))(o);
        if (this_->mp68 != 0) {
            o = this_->mp68;
            this_->mp68 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))((char*)o + 0x3c);
        }
    }
    FUN_00f02dd0();
    FUN_00f094d0();
    {
        void* o = this_->mp18;
        FUN_00f32030();
        if (this_->mp18 != 0) {
            o = this_->mp18;
            this_->mp18 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))(o);
        }
    }
    {
        void* o = this_->mp74;
        FUN_00f41cf0();
        if (o != 0) {
            this_->mp74 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))((char*)o + 8);
        }
    }
    {
        void* o = this_->mp70;
        FUN_00ebd340();
        if (this_->mp70 != 0) {
            o = this_->mp70;
            this_->mp70 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))(o);
        }
    }
    if (this_->mp80 != 0) {
        u32 x = this_->m90;
        u32 y = this_->m8c;
        u32 z = this_->m88;
        u32 w = this_->m84;
        void* o = this_->mp80;
        this_->mp80 = 0;
        FUN_00571db0(o, w, z, y, x);
    }
}

// @ 0x00ef1660
void __thiscall Strategy::FUN_00ef1660()
{
    Strategy* this_ = this;
    switch (this_->mcc) {
    case 1:
        FUN_00ef0c80();
        break;
    case 2:
        FUN_00ef10c0();
        break;
    }

    void* em = FUN_0067ddd0();
    ((void(__thiscall*)(void*, int, int))(*((char**)((char*)*(void**)em + 0x98))))(em, 8, 0);
}

// @ 0x00ef16a0
u8 cSim::FUN_00ef16a0(u32 key, int state)
{
    if (G_15acc34 != 4)
        return 1;
    ((Stub697a*)((char*)this + 0x20))->F(key, state);
    void* gim = FUN_00b3d250();
    if (VFN(gim, 0x44, TC_cii)(gim, (int)key, state)) {
        if ((key == 0x48 || key == 0x42 || key == 0xbf) && *(int*)((char*)this + 0xd4))
            FUN_00ef72c0(*(void**)((char*)this + 0xd4));
        return 1;
    }
    if (*(int*)((char*)this + 0xcc) == 2) {
        bool b = false;
        switch (state) {
        case 0: b = true; break;
        case 1: b = (key == 0x10); break;
        case 2: b = (key == 0x11); break;
        case 4: b = (key == 0x12); break;
        default: b = false; break;
        }
        if (b) {
            if (VerbTray_HandleKeyPress((int)key))
                return 1;
        }
        if (key == 0x48) {
            if (state == 6) {
                void* ac = FUN_00675250();
                FUN_00676f20(ac);
                void* av = FUN_00b1fdb0(FUN_00b3d300());
                void* sub = (char*)av + 0x5a8;
                float f = VFN(sub, 0x58, TC_pf)(sub);
                FUN_00f924e0(f);
                *(float*)((char*)av + 0xe58) = *(float*)((char*)av + 0xe5c);
                return 1;
            }
        } else if (key == 0x1b) {
            int m = *(int*)((char*)*(void**)((char*)this + 0x78) + 0x90);
            if (m == 6 || m == 5 || m == 2 || m == 0)
                return 1;
        }
        if (*(int*)((char*)this + 0xd0) != 0)
            goto L1900;
        if (key == 0x43 && state == 6) {
            void* p1 = VFN(FUN_0067dd10(), 0x50, TC_p)(FUN_0067dd10());
            u32 s = (u32)VFN(p1, 0x58, TC_p)(p1);
            void* p2 = VFN(FUN_0067dd10(), 0x50, TC_p)(FUN_0067dd10());
            void* c = VFN(p2, 0x4c, TC_pi)(p2, (int)s);
            void* cam = (void*)FUN_00b60a50((int)c);
            FUN_00d272e0(cam);
            void* d = *(void**)((char*)this + 0x68);
            u32 st = (u32)FUN_00d20940(cam);
            *(u8*)((char*)d + 0x54) = (st != 2);
            return 1;
        }
    } else if (*(int*)((char*)this + 0xcc) == 1) {
        if (key == 0x53) {
            if (state == 2) {
                void* ms = FUN_0067dcc0();
                VFN(ms, 0x14, TC_viii)(ms, 0x101, 0, 0);
                return 1;
            }
        } else if (key > 0x30 && key < 0x3a && *(int*)((char*)this + 0x10) &&
                   ((StubED9E*)*(void**)((char*)this + 0x10))->F(1)) {
            u32 n1 = (u32)FUN_00f3be30(*(void**)((char*)this + 0x74));
            u32 n2 = (u32)FUN_00efc520();
            u32 k = key - 0x31;
            if (k < n1 && k != n2) {
                FUN_00efc8c0((int)k);
                KillSetiEffects(0xe10deda0, GetRecorderState());
                FUN_00ee31d0(FUN_006c0200(*(void**)((char*)this + 0x14)));
            }
        }
    }
    if (*(int*)((char*)this + 0xd0) == 0 && key == 0x43 && state == 0) {
        ((StubF069*)*(void**)((char*)this + 0xd8))->F(1);
        return 1;
    }
L1900:
    void* gim2 = FUN_00b3d250();
    return VFN(gim2, 0x4c, TC_cii)(gim2, (int)key, state);
}

// @ 0x00ef1930
void cSim::FUN_00ef1930(int a, float b)
{
    ((Sub70*)p70)->FUN_00ebdc20(a, b);
}

// @ 0x00ef1990
int FUN_00ef1990(u32* param_1, u32* param_2, u32* unused)
{
    (void)unused;
    int n = 0;
    if (param_2 != param_1) {
        do {
            u32* q;
            do {
                q = param_1;
                param_1 = q + 0x8e;
                if ((unsigned char)(*q >> 0x1e) & 1)
                    break;
            } while ((unsigned char)(*param_1 >> 0x1f) & 1);
            n++;
        } while (param_2 != param_1);
    }
    return n;
}

// @ 0x00ef19f0
int* FUN_00ef19f0(void)
{
    int* p = (int*)G_15accc8;
    int z = 0;
    p[0] = z; p[1] = z; p[2] = z; p[3] = z; p[4] = z;
    p[5] = z; p[6] = z; p[7] = z; p[8] = z;
    p[10] = z; p[12] = z; p[13] = z; p[14] = z;
    p[9] = 1;
    return p;
}

// @ 0x00ef1a50
u8 FUN_00ef1a50(void)
{
    u8* raw = (u8*)ZoneObject_new(8, "App", 0, 0, 0, 0);
    int* p;
    if (raw) {
        *(void**)raw = &G_13effa8;
        _InterlockedExchange((volatile long*)(raw + 4), 0);
        *(void**)raw = &G_148b0b4;
        p = (int*)raw;
    } else {
        p = 0;
    }
    int* old = (int*)G_16c7b30;
    if (p != old) {
        if (p)
            VFN(p, 4, TC_v)(p);
        *(int**)&G_16c7b30 = p;
        if (old)
            VFN(old, 8, TC_v)(old);
    }
    void* mgr = FUN_0067dcd0();
    VFN(mgr, 0x44, TC_vpii)(mgr, 1, G_16c7b30, 0);
    return 1;
}

// @ 0x00ef1ad0
void cSim::FUN_00ef1ad0(void)
{
    ModelVector* mv = (ModelVector*)&v74;
    mv->DoDestroyValues(v74, v78);
    if (v74 && *(int*)((char*)v74 - 4) != 0)
        op_delete(v74);
    if (p60 && *(int*)((char*)p60 - 4) != 0)
        op_delete(p60);
    void* p4c = *(void**)((char*)this + 0x4c);
    if (p4c && *(int*)((char*)p4c - 4) != 0)
        op_delete(p4c);
    ht.DoFreeNodes(ht.mpBuckets, ht.mnElements);
    ht.mAlloc = 0;
    if (ht.mnElements > 1)
        op_delete(ht.mpBuckets);
    if (p18 && *(int*)((char*)p18 - 4) != 0)
        op_delete(p18);
}

// @ 0x00ef1b70
void cSim::FUN_00ef1b70(u32 v)
{
    if (!v)
        return;
    int* rec = (int*)FUN_00b18e00(v);
    int* p98v = (int*)VFN(rec, 0x98, TC_p)(rec);
    char* ht = (char*)this + 0x2c;
    int* bucket = (int*)*(int*)((char*)this + 0x30);
    int key = bucket[*(u32*)((char*)this + 0x34)];
    HashFindOut tmp;
    if (*(int*)((StubC776*)ht)->F(&tmp, p98v) == key) {
        v &= 0xffffff00;
        ((Stub8DF*)ht)->F(&tmp, p98v, v);
        if (*p98v && !FUN_00401d90(p98v))
            ((Stub4E19*)((char*)this + 0x4c))->F(p98v);
        void** end = *(void***)((char*)this + 0x64);
        u32 cap = *(u32*)((char*)this + 0x68);
        if ((u32)end < cap) {
            void** p = end;
            *(void***)((char*)this + 0x64) = p + 1;
            if (p)
                *p = rec;
        } else {
            ((StubB966*)((char*)this + 0x60))->F(end, &rec);
        }
    }
}

// @ 0x00ef1c40
void cSim::FUN_00ef1c40(void)
{
    if (bDirty) {
        int i = 0;
        do {
            if (*(char*)(i + *(int*)((char*)this + 0x18))) {
                void* s = FUN_0067dd50();
                VFN(s, 0x5c, TC_vii)(s, i, 1);
            }
        } while (++i <= 0x1b);
        char* end = *(char**)((char*)this + 0x1c);
        char* begin = *(char**)((char*)this + 0x18);
        eastl_vector_insert(begin, end, (u32)(end - end));
        *(int*)((char*)this + 0x1c) += (int)(begin - end);
        bDirty = 0;
    }
}

// @ 0x00ef1ca0
void cSim::FUN_00ef1ca0(void)
{
    *(u32*)((char*)this + 4) = 0;
    *(u32*)((char*)this + 8) = 0xffffffff;
    *(u32*)((char*)this + 0xc) = 0xffffffff;
    *(u32*)((char*)this + 0x10) = 0;
    FUN_00ef1c40();
    *(u32*)((char*)this + 4) = 0;
    void* a = *(void**)((char*)G_16c7aa4 + 0x74);
    *(void**)((char*)this + 0x14) = a;
    char* b = (char*)*(void**)((char*)a + 0x10);
    u32 cnt = *(u32*)(b + 0x2c24);
    u32* e = (u32*)*(u32*)(b + 0x2c14);
    u32* bp;
    if (cnt < 0x3fffffff)
        bp = (u32*)(cnt * 0x238 + *(u32*)(b + 0x2c10));
    else
        bp = e;
    int n = FUN_00ef1990(bp, e, 0);
    Vec2v* v60 = (Vec2v*)((char*)this + 0x60);
    v60->Reserve(n);
    char* e60 = (char*)v60->mpEnd;
    char* b60 = (char*)v60->mpBegin;
    eastl_vector_insert(b60, e60, (u32)(e60 - e60));
    v60->mpEnd = (char*)v60->mpEnd + (int)(b60 - e60);
    Vec2v* v4c = (Vec2v*)((char*)this + 0x4c);
    v4c->Reserve4(n);
    v4c->Erase(v4c->mpBegin, v4c->mpEnd);
    ht.DoFreeNodes(ht.mpBuckets, ht.mnElements);
    ht.mAlloc = 0;
    int* v = (int*)FUN_00ff3f00_f(*(void**)((char*)this + 0x14));
    if (v) {
        void* k = FUN_00eec0d0((int)v);
        FUN_00ef1b70((u32)k);
    }
    u32 cnt2 = *(u32*)(b + 0x2c24);
    u32* end2 = (u32*)*(u32*)(b + 0x2c14);
    u32* cur;
    if (cnt2 < 0x3fffffff)
        cur = (u32*)(cnt2 * 0x238 + *(u32*)(b + 0x2c10));
    else
        cur = end2;
    u32* e2 = (u32*)*(u32*)(b + 0x2c14);
    while (e2 != cur) {
        FUN_00ef1b70((u32)FUN_00eec0d0((int)(cur + 1)));
        u32* q;
        do {
            q = cur;
            cur = q + 0x8e;
            if ((*q >> 0x1e) & 1)
                break;
        } while ((*cur >> 0x1f) & 1);
    }
}

// @ 0x00ef1e00
void cSim::FUN_00ef1e00(void)
{
    void* tick = FUN_00b3d310();
    *(u8*)((char*)tick + 0x24) = 0;
    char* base = (char*)this;
    void* self = base ? base + 4 : 0;
    void* server = FUN_0067dcc0();
    *(void**)(base + 0x80) = server;
    *(void**)(base + 0x84) = self;
    *(void**)(base + 0x88) = (void*)G_148b018;
    *(u32*)(base + 0x8c) = 8;
    *(u32*)(base + 0x90) = 0;
    if (server && self) {
        for (u32 off = 0; off < 0x20; off += 4)
            VFN(server, 0x24, TC_vpp)(server, self, *(void**)((char*)G_148b018 + off));
    }
    *(int*)(base + 0xd0) = G_15accf0;
    SETREF(*(void**)(base + 0x18), 0x1cc, "Simulator", FUN_00f33f90_c, 0, 8, 0xc);
    ((Stub37f*)*(void**)(base + 0x18))->F(G_15accc8);
    FUN_00f02c10();
    SETREF(*(void**)(base + 0x78), 0x108, "Simulator", FUN_00f1e450_c, 4, 4, 8);
    FUN_00f1e620(*(void**)(base + 0x78));
    if (*(int*)(base + 0xcc) == 0) {
        if (G_15accf0 != 0) {
            if ((u32)(G_15accf0 - 1) <= 1)
                *(int*)(base + 0xcc) = 2;
        } else {
            *(int*)(base + 0xcc) = 1;
        }
    }
    u8 empty = (*(int*)G_15accc8 == 0);
    SETREF(*(void**)(base + 0x74), 0x1fc, "Simulator", FUN_00f3fad0_c, 8, 4, 8);
    ((Stub447*)*(void**)(base + 0x74))->F(empty);
    FUN_00f20fe0();
    FUN_00f24d30();
    if (!empty) {
        ((Stub660*)((char*)*(void**)(base + 0x74) + 0x128))->F(G_15accf8);
        if (((Stub466*)*(void**)(base + 0x74))->F(G_15accc8)) {
            if (G_15acce0)
                ((Stub425*)*(void**)(base + 0x74))->F(&G_15acce0);
            ((cSim*)G_15acc30)->FUN_00ef1ca0();
        }
    }
    LoadCreatureGameplayTuning(G_15acc2c, 0x2980610e);
    FUN_00ebf160();
    void* mgr2 = FUN_00b3d230_s00ef_16a0(0);
    FUN_00b5cde0(mgr2);
    FUN_00f09580();
    SETREF(*(void**)(base + 0x6c), 0x308, "Simulator", FUN_00f0fef0_c, 0x38, 0, 4);
    SETREF(*(void**)(base + 0x68), 0x120, "Simulator", FUN_00f11b60_c, 0x3c, 4, 8);
    VFN(*(void**)(base + 0x68), 4, TC_v)(*(void**)(base + 0x68));
    if (*(int*)(base + 0xd0) == 0) {
        SETREF(*(void**)(base + 0xd4), 0x740, "Simulator/cScenarioTutorials",
               FUN_00ef9d90_c, 4, 4, 8);
        FUN_00ef9e40(*(void**)(base + 0xd4));
        SETREF(*(void**)(base + 0xd8), 0x120, "Simulator/cScenarioYouTube",
               FUN_00f04740_c, 0, 0, 4);
        FUN_00f06ce0(*(void**)(base + 0xd8));
        SETREF(*(void**)(base + 0x10), 0x70, "Simulator/cScenarioEditModeInputStrategy",
               FUN_00edaa80_c, 0x3c, 4, 8);
        VFN(*(void**)(base + 0x10), 4, TC_v)(*(void**)(base + 0x10));
        SETREF(*(void**)(base + 0x14), 0x98, "Simulator/cScenarioEditModeDisplayStrategy",
               FUN_00ed5220_c, 0, 4, 8);
        FUN_00ed5d70(*(void**)(base + 0x14));
        FUN_00f08ef0();
        FUN_00ec92b0();
    }
    if (*(int*)(base + 0x70) == 0) {
        FUN_01041bc0(FUN_010408b0());
        SETREF(*(void**)(base + 0x70), 0x68, "Simulator", FUN_00ebc120_c, 0, 4, 8);
    }
    FUN_00ebd220(*(void**)(base + 0x70));
    *(int*)(base + 0xcc) = 0;
    ((Stub12d*)base)->F(G_15accec);
    void* posse = FUN_00d539d0();
    VFN(posse, 0x1c, TC_v)(posse);
    void* ticker = FUN_00b3d330();
    void** slot = *(void***)ticker + 0x14;
    void* arg = FUN_00d539d0();
    ((TC_vp)*slot)(ticker, arg);
}

// @ 0x00ef2370
u8 cSim::FUN_00ef2370(int unused)
{
    (void)unused;
    void* o = EAAllocate(0xa8, "Simulator", 0, 0, 0, 0);
    void* n = o ? FUN_00ec4bb0_r(o) : 0;
    void* old = p1c;
    if (n != old) {
        if (n)
            VFN(n, 4, TC_v)(n);
        p1c = n;
        if (old)
            VFN(old, 8, TC_v)(old);
    }
    FUN_00ec4650_f(p1c);
    FUN_00eed090();
    void* o2 = EAAllocate(0x64, "Simulator", 0, 0, 0, 0);
    void* n2 = o2 ? FUN_00f391c0_r(o2) : 0;
    void* old2 = p7c;
    if (n2 != old2) {
        if (n2)
            VFN(n2, 4, TC_v)(n2);
        p7c = n2;
        if (old2)
            VFN(old2, 8, TC_v)(old2);
    }
    void* a = FUN_0067de40();
    void* b = VFN(a, 0x20, TC_p)(a);
    VFN(b, 0x1c, TC_vp)(b, p7c);
    void* ms = FUN_0067dcc0();
    VFN(ms, 0x28, TC_vpiii)(ms, (void*)&LAB_00ef2330, 0, 0x212d3e7, 0, -1);
    void* local[2];
    local[0] = (void*)0x4249453;
    local[1] = (void*)0x7fb11b4;
    void* self = (char*)this + 4;
    void* server = FUN_0067dcc0();
    p94 = server;
    p98 = self;
    p9c = &local[0];
    nA0 = 2;
    nA4 = 0;
    if (server && self) {
        for (u32 i = 0; i < 2; i++)
            VFN(server, 0x24, TC_vpp)(server, self, local[i]);
    }
    return 1;
}

// @ 0x00ef25a0
u8 cSim::FUN_00ef25a0(void)
{
    FUN_00697980((char*)this + 0x20);
    void* t = GetTriggerMgr(1);
    ((TriggerMgr*)t)->FUN_00adf390();
    int s = GetSetting5(0x4cf52822);
    ((Setter*)s)->FUN_0045b150();
    void* em = FUN_0067ddd0();
    VFN(em, 0x98, TC_vii)(em, 8, 1);
    ((GTM*)FUN_00b3d380())->FUN_00b316d0(1.0f, G_1470f1c, G_14853e0, G_14853e0);
    bDC = 1;
    GTM* g = (GTM*)FUN_00b3d380();
    g->FUN_00b32220(0x4bf38a7);
    ((cSim*)G_15acc30)->FUN_00ef1ca0();
    return 1;
}

// @ 0x00ef26c0
void PlanetFlow::RebuildModels()
{
    ((cGameNounManager*)SP_NounManager())->ProcessPending();

    uint8_t flag = 0;
    {
        PropObj* props = *(PropObj**)0x15fd918;
        if (props != 0) {
            void* out = 0;
            if (props->Query(0x50caab1u, &out) != 0 &&
                *(uint16_t*)((uint8_t*)out + 0x12) == 1) {
                flag = (uint8_t)*FUN_0041e920(out);
            }
        }
    }

    if (GMGR->mMode == 2 && flag != 0) {
        MWVec* v = &this->mModels;
        AutoRefCount* begin = v->mpBegin;
        AutoRefCount* end = v->mpEnd;
        void* p = FUN_005f4e10(end, end, begin);
        FUN_005f3680(p, end);
        int n = (int)((char*)end - (char*)begin);
        v->mpEnd = (AutoRefCount*)((char*)v->mpEnd + (-(n >> 2)) * 4);

        cModelStore* store = (cModelStore*)(*(void**)((uint8_t*)GMGR->mpStore74 + 0x10));
        void* start;
        if (store->mIndex < 0x3fffffffu)
            start = (uint8_t*)store->mpBegin + (uint32_t)store->mIndex * 0x238;
        else
            start = store->mpEnd;
        uint32_t cnt = FUN_00ef1990(start, store->mpEnd, this);
        v->reserve(cnt);

        void* it = start;
        void* vend = store->mpEnd;
        if (it != vend) {
            for (;;) {
                void* obj = FUN_00eeca30((uint8_t*)it + 4);
                if (obj != 0) {
                    void* model = ((PFN_p)*(void**)(*(char**)obj + 0xac))(obj);
                    if (model != 0) {
                        cMWModel* mod = (cMWModel*)model;
                        mod->AddRef();
                        AutoRefCount tmp; tmp.mpObject = mod;
                        if (v->mpEnd < v->mpCapacity) {
                            AutoRefCount* slot = v->mpEnd++;
                            if (slot != 0) { slot->mpObject = mod; mod->AddRef(); }
                        } else {
                            v->DoInsertValue(v->mpEnd, &tmp);
                        }
                        if (tmp.mpObject != 0)
                            tmp.mpObject->Release();
                    }
                }
                uint32_t f;
                do {
                    f = *(uint32_t*)it;
                    it = (uint8_t*)it + 0x238;
                } while (!(f & 0x40000000u) && *(int32_t*)it < 0);
                if (it == vend) break;
            }
        }

        this->mpNode->F45FD0(2, 0, 0);
    }

    ((PlanetModel*)SP_PlanetModel())->ComputeContinents();
    this->mpNode->F3C2C0();
    if (this->mpNode->mField14 != 0) {
        uint8_t r = this->mpNode->F40370();
        if (GMGR->mMode == 1) {
            this->mpNode->F427C0();
        } else if (GMGR->mMode == 2 && r == 0) {
            this->mpNode->F45FD0(2, 0, 0);
        }
    } else if (GMGR->mMode == 1) {
        this->mpNode->F427C0();
    }

    if (*(uint8_t*)0x15acb40 != 0) {
        cScenarioNode* node = this->mpNode;
        int32_t c = node->mpStore->mField2c50;
        if (c < 1) {
            if (c == 0) node->F3E3B0(1);
            node->mpStore->mField2c50 = 1;
            node->mField84 = 1;
        }
    }
    this->mpNode->F3E6B0(0);
}

// @ 0x00ef2940
void PlanetFlow::FillPending()
{
    ByteVec* v = &this->mPending;
    uint8_t* begin = v->mpBegin;
    uint8_t* end = v->mpEnd;
    if ((uint32_t)(end - begin) < 0x1c) {
        uint8_t value = 0;
        v->insertFill(end, 0x1c - (uint32_t)(end - begin), &value);
    } else {
        uint8_t* pos = begin + 0x1c;
        FUN_011e0744(pos, end, 0);
        v->mpEnd = end + (pos - end);
    }
    for (int i = 0; i <= 0x1b; ++i) {
        void* o = FUN_0067dd50();
        uint8_t r = ((uint8_t (__thiscall*)(void*, int, int))*(void**)(*(char**)o + 0x60))(o, i, 1);
        begin[i] = (uint8_t)(r & 1);
    }
    this->mFlag1 = 1;
}

// @ 0x00ef29c0
void GlobalMwVector_Clear()
{
    MWVec* v = (MWVec*)0x15acca4;
    AutoRefCount* begin = v->mpBegin;
    AutoRefCount* end = v->mpEnd;
    void* p = FUN_005f4e10(end, end, begin);
    FUN_005f3680(p, v->mpEnd);
    int n = -(int)(end - begin);
    v->mpEnd = (AutoRefCount*)((char*)v->mpEnd + n * 4);
}

// @ 0x00ef2a10
void PlanetFlow::AdvanceStage()
{
    switch (this->mStage) {
    case 0:
        if (this->mCounter == 0) {
            cScenarioNode* node = GMGR->mpNode;
            if (node != 0)
                this->mFlag = (node->FED5330(0x7eaf739u) == 0);
            else
                this->mFlag = 1;
            ((C801360*)FUN_0067cab0())->Show();
            this->mCounter = 1;
        }
        if ((this->mFlag != 0 && this->mCounter >= *(uint32_t*)0x15acd1c) ||
            this->mCounter > 0x1e) {
            this->FillPending();
            this->FEF0220();
            this->mStage++;
        }
        break;
    case 1: {
        void* o = FUN_00401010_s00ef_26c0();
        int r = ((int (__thiscall*)(void*))*(void**)(*(char**)o + 0x28))(o);
        if (r == 0)
            this->mStage++;
        break;
    }
    case 2:
        if (this->FEF02A0() != 0) {
            this->FEF1C40();
            this->mStage++;
        }
        break;
    case 3: {
        this->RebuildModels();
        cScenarioNode* node = GMGR->mpNode;
        if (node != 0) {
            FUN_00ef0b80();
            node->FED5400(0x7eaf739u);
            ((C801360*)FUN_0067cab0())->Hide();
            this->mStage++;
        } else {
            this->mFlag = 1;
            ((C801360*)FUN_0067cab0())->Hide();
            this->mStage++;
        }
        break;
    }
    default:
        break;
    }
}

// @ 0x00ef2b20
void FUN_00ef2b20(float)
{
    cGameNounManager* m = (cGameNounManager*)SP_NounManager();
    NounVec* src = m->GetGameDataVector(0xcd7d10, 0xd3d420, 0xef2640, 0xb1e500, 0x70703b3);

    void*  local[8];
    void** begin = local;
    void** end = local;
    void** cap = local + 8;

    int n = (int)(src->mpEnd - src->mpBegin);
    for (int i = 0; i < n; ++i) {
        void* noun = src->mpBegin[i];
        if (noun == 0) continue;
        if (((uint8_t (__thiscall*)(void*))*(void**)(*(char**)noun + 0x2c))(noun) != 0) continue;
        if (FUN_00bcc800(noun) <= *(int32_t*)0x15acb44) continue;
        ((void (__thiscall*)(void*))*(void**)(*(char**)noun + 0))(noun);
        void* item = noun;
        if (end < cap) {
            void** slot = end++;
            if (slot != 0) {
                *slot = noun;
                ((void (__thiscall*)(void*))*(void**)(*(char**)noun + 0))(noun);
            }
        } else {
            ((void (__thiscall*)(void*, void**, void**))0xedafd0)(&begin, end, &item);
        }
        if (item != 0)
            ((void (__thiscall*)(void*))*(void**)(*(char**)item + 4))(item);
    }

    int cnt = (int)(end - begin);
    for (int i = 0; i < cnt; ++i)
        ((cGameNounManager*)SP_NounManager())->RemoveNoun(begin[i]);

    for (void** p = begin; p < end; ++p) {
        if (*p != 0)
            ((void (__thiscall*)(void*))*(void**)(*(char**)*p + 4))(*p);
    }
    if (begin != 0 && begin != local)
        FUN_00f47380(begin);
}

// @ 0x00ef2e90
void FUN_00ef2e90(int ms)
{
    if (((uint8_t*)SP_GameTimeManager())[0x48] & 1) return;
    cGameNounManager* m = (cGameNounManager*)SP_NounManager();
    NounVec* v = m->GetGameDataVector(0xcd7d10, 0xd3d420, 0xace0f0, 0xb1e500, 0x18eb45e);
    int n = (int)(v->mpEnd - v->mpBegin);

    PtrVec local;
    local.ctor((uint32_t)n, &v->mField10);
    FUN_00829110(&local, v->mpBegin, v->mpEnd, local.mpEnd, local.mpBegin);

    int cnt = (int)(local.mpEnd - local.mpBegin);
    for (int i = 0; i < cnt; ++i) {
        void* p = local.mpBegin[i];
        if (p != 0 && *((uint8_t*)p + 0x135) != 0)
            ((void (__thiscall*)(void*, int))*(void**)(*(char**)p + 0x60))(p, ms);
    }
    for (void** p = local.mpBegin; p < local.mpEnd; ++p) {
        if (*p != 0)
            ((void (__thiscall*)(void*))*(void**)(*(char**)*p + 4))(*p);
    }
    if (local.mpBegin != 0 && *((int*)local.mpBegin - 1) != 0)
        FUN_00f47380(local.mpBegin);
}

// @ 0x00ef2f70
void PlayMode::TickBase(int ms)
{
    FUN_00ef2e90(ms);
    ((Field18*)this->mpField18)->F32440(0);
}

// @ 0x00ef2f90
void PlayMode::TickFull(int ms)
{
    FUN_00ef2c70(ms);
    FUN_00ef2e90(ms);
    ((Bag*)FUN_00b3d4c0())->FBA3350();
    ((Field18*)this->mpField18)->F32440(0);
}

// @ 0x00ef3930
void __stdcall FUN_00ef3930(int *__restrict param_1)
{
    param_1[0] = 0x68715e28;
    param_1[1] = 0x0510a95b;
    param_1[2] = DAT_015acd3c;
}

// @ 0x00ef40d0
void __fastcall FUN_00ef40d0(cAssetPanel* self)
{
    AssetView_LoadLayout(self);
    AssignWindow(&self->mpWin12C, self->mpViewLayout->FindWindowByID(0x7bb81c0, 1));
    AssignWindow(&self->mpWin128, self->mpViewLayout->FindWindowByID(0x7e0ba78, 1));
    AssignWindow(&self->mpWin130, self->mpViewLayout->FindWindowByID(0x7bb9c30, 1));
    AssignWindow(&self->mpWin134, self->mpViewLayout->FindWindowByID(0x7bb9c10, 1));
    AssignWindow(&self->mpWin138, self->mpViewLayout->FindWindowByID(0x7bb9c18, 1));
    AssetView_RefreshDetails(self);
    AssignWindow(&self->mpWin13C, self->mpViewLayout->FindWindowByID(0x7bfe394, 1));
    if (self->mpWin13C != 0) {
        if (WndGetHash(self->mpNoun120) != 0x24720859) {
            WndShow(self->mpWin13C, 1, self->mpNoun120->m79 == 0);
        }
    }
    AssignWindow(&self->mpWin140, self->mpViewLayout->FindWindowByID(0xb498717e, 1));
    AssignWindow(&self->mpWin144, self->mpViewLayout->FindWindowByID(0x7e0b9b0, 1));
    AssignWindow(&self->mpWin148, self->mpViewLayout->FindWindowByID(0x7ee12a8, 1));
    if (self->mpNoun120 != 0) {
        int n = self->mpNoun120->m88;
        if (n != 0x7fffffff) {
            if (n > 0) {
                WndShow(self->mpWin144, 1, 1);
            } else if (n < 0) {
                WndShow(self->mpWin148, 1, 1);
            }
        }
    }
    AssignWindow(&self->mpWin124, self->mpViewLayout->FindWindowByID(0x7cd2a58, 1));
    AssetView_Refresh(self);
    if (self->mpWinA[0] == 0) {
        return;
    }
    if (self->mpWinA[1] == 0) {
        return;
    }
    {
        AssetNoun* noun = self->mpNoun120;
        if (noun->m7C != 0) {
            WndShow(self->mpWin140, 1, 1);
            WndShow(self->mpWinA[0], 1, 0);
            WndShow(self->mpWinA[1], 1, 0);
        } else if (noun->m7B != 0) {
            WndShow(self->mpWin140, 1, 0);
            WndShow(self->mpWinA[0], 1, 0);
            WndShow(self->mpWinA[1], 1, 1);
        } else if (noun->m7A != 0) {
            WndShow(self->mpWin140, 1, 0);
            WndShow(self->mpWinA[0], 1, 1);
            WndShow(self->mpWinA[1], 1, 0);
        } else {
            WndShow(self->mpWin140, 1, 0);
            WndShow(self->mpWinA[0], 1, 0);
            WndShow(self->mpWinA[1], 1, 0);
        }
    }
}

// @ 0x00ef4440
void* __fastcall FUN_00ef4440(cLayerKeyProvider* self, void* dummy, int id)
{
    if ((id == 0x13d6b42b) || (id == 0x93d55b46)) {
        return (char*)self - 0x10;
    }
    if (id != 0xee3f516e) {
        return 0;
    }
    return ((char*)self - 0x10) ? self : 0;
}

// @ 0x00ef4490
ResKey* __fastcall FUN_00ef4490(cLayerKeyProvider* self, void* dummy, ResKey* out)
{
    uint type = self->mKeyInstance;
    if ((type == 0xdb5cad8b) || (type == 0x28c176eb) || (type == 0x15677bf)) {
        ResKey* result = *(ResKey* volatile*)&out;
        ResKey key;
        key.mId = self->mKeyB.mId;
        key.mType = 0x2f7d0004;
        key.mSub = DAT_015acdf4;
        *result = key;
        return result;
    } else {
        ResKey key = *(const ResKey*)&self->m04;
        key.mType = 0x2f7d0004;
        key.mSub = 0x65928944;
        *out = key;
        return out;
    }
}

// @ 0x00ef4520
Pair8 __fastcall FUN_00ef4520(void* self)
{
    Pair8 r;
    r.mLo = 0;
    r.mHi = 0;
    return r;
}

// @ 0x00ef4550
cLayerKeyProvider* __fastcall FUN_00ef4550(cLayerKeyProvider* self)
{
    self->m04 = 0;
    self->m08 = 0;
    self->m0C = 0;
    self->mpLayerVt = (void*)&VTABLE_013f1ab0;
    self->mpSummaryVt = (void*)&VTABLE_013ec458;
    self->m18 = 0;
    _ReadWriteBarrier();
    self->mpVtbl = (void*)&VTABLE_0148b2d0;
    self->mpLayerVt = (void*)&VTABLE_0148b2c0;
    self->mpSummaryVt = (void*)&VTABLE_0148b2b0;
    cString_Ctor(&self->mName);
    self->mKeyInstance = 0;
    self->mKeyA.mId = 0;
    self->mKeyA.mType = 0;
    self->mKeyA.mSub = 0;
    self->mKeyB.mId = 0;
    self->mKeyB.mType = 0;
    self->mKeyB.mSub = 0;
    return self;
}

// @ 0x00ef45b0
cLayerKeyProvider* __fastcall FUN_00ef45b0(cLayerKeyProvider* self, void* dummy, char flags)
{
    self->mpVtbl = (void*)&VTABLE_0148b2d0;
    self->mpLayerVt = (void*)&VTABLE_0148b2c0;
    self->mpSummaryVt = (void*)&VTABLE_0148b2b0;
    cString_Dtor(&self->mName);
    Layer_Shutdown(self);
    if (flags & 1) {
        operator_delete(self);
    }
    return self;
}

// @ 0x00ef4620
void __fastcall FUN_00ef4620(cLayerKeyProvider* self, void* dummy, void* param)
{
    void* pm;
    void* bag;

    self->LayerInit(param);
    bag = 0;
    pm = SP_PropertyManager();
    ResetWindow(&bag);
    if (PropertyManager_Get(pm, self->m04, self->m0C, &bag)) {
        SP_GetPropertyAsText(bag, 0x71e9bd1, &self->mName);
        self->mKeyInstance = 0;
        SP_GetPropertyAsKeyInstance(bag, 0x5cd8beab, &self->mKeyInstance);
        self->mKeyA.mId = 0;
        self->mKeyA.mType = 0;
        self->mKeyA.mSub = 0;
        SP_GetPropertyAsKey(bag, 0xaeb7704e, &self->mKeyA);
        self->mKeyB.mId = 0;
        self->mKeyB.mType = 0;
        self->mKeyB.mSub = 0;
        SP_GetPropertyAsKey(bag, 0xf9efbb, &self->mKeyB);
    }
    if (bag) {
        WndRelease(bag);
    }
}

// @ 0x00ef46f0
bool __fastcall FUN_00ef46f0(cAssetPanel* self, void* dummy, void* context, Msg* msg)
{
    void* w;

    switch (msg->mType) {
    case 9:
        w = msg->mpWindow;
        if (self->mpWin40 != 0) {
            if (WndGetChild(self->mpWin40) == w) {
                WindowManager_SetCurrent(SP_WindowManager(),
                                         WndGetItem(self->mpWin40, msg, 0));
            }
        }
        if (self->mpWin44 != 0) {
            if (WndGetChild(self->mpWin44) == w) {
                WindowManager_SetCurrent(SP_WindowManager(),
                                         WndGetItem(self->mpWin44, msg, 0));
            }
        }
        break;
    case 0x1b:
    case 0x1c: {
        void* obj;
        if (WndGetSenderType(msg->mpSender) == 0x53d6fe29) {
            obj = self->mpZoomB0;
        } else if (WndGetSenderType(msg->mpSender) == 0xb456a47a) {
            obj = self->mpZoomAC;
        } else {
            return false;
        }
        if (obj != 0) {
            if (msg->mType == 0x1b) {
                TextZoomName_Activate(obj, 0);
            } else {
                TextZoomName_Deactivate(obj, 0);
            }
        }
        return false;
    }
    case 0x287259f6:
        switch (msg->mSub) {
        case 0x7b69988:
            FieldSet(&self->mField, (int)self->mpLayout, 0x7ccce38);
            return true;
        case 0x6135298:
            if (self->mpNoun9C != 0) {
                void* a = WndGetSlot20(FUN_0067de40());
                void* child = WndGetItem1(self->mpNoun9C, 0);
                WndSetSlot34(a, child);
            }
            UI_CalloutMessageBox(&self->m08, 0x15aced8);
            return true;
        case 0x7b69998:
            FieldSet(&self->mField, (int)self->mpLayout, 0x7ccce30);
            return true;
        case 0x53d6fe2a:
            if (self->mpNounA0 != 0) {
                __int64 id = Meta_GetId(self->mpNounA0);
                MessageServer_Send(SP_MessageServer(), 0x6299932, &id, 0);
            }
            return true;
        case 0x74174c59:
            MessageServer_Send(SP_MessageServer(), 0x14ac4938, 0, 0);
            return true;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return false;
}

// @ 0x00ef4940
void __fastcall FUN_00ef4940(cAssetPanel* self)
{
    void* p;
    int i;

    if (self->mC0 == 0) {
        return;
    }
    p = self->mpVerbs98;
    if (p != 0) {
        cSPUIAssetVerbs_Shutdown(p);
        p = self->mpVerbs98;
        if (p != 0) {
            self->mpVerbs98 = 0;
            WndRelease(p);
        }
    }
    p = self->mpVerbs94;
    if (p != 0) {
        FUN_00f47040(p);
        p = self->mpVerbs94;
        if (p != 0) {
            self->mpVerbs94 = 0;
            WndRelease(p);
        }
    }
    if (self->mpWin38 != 0) {
        WndHookEvent(self->mpWin38, self);
    }
    if (self->mpWin40 != 0) {
        p = WndGetChild(self->mpWin40);
        if (p != 0) {
            WndHookEvent(p, self);
        }
    }
    if (self->mpWin44 != 0) {
        p = WndGetChild(self->mpWin44);
        if (p != 0) {
            WndHookEvent(p, self);
        }
    }
    p = self->mpZoomAC;
    if (p != 0) {
        TextZoomName_Shutdown(p);
        p = self->mpZoomAC;
        if (p != 0) {
            self->mpZoomAC = 0;
            WndReleaseVt8(p);
        }
    }
    p = self->mpZoomB0;
    if (p != 0) {
        TextZoomName_Shutdown(p);
        p = self->mpZoomB0;
        if (p != 0) {
            self->mpZoomB0 = 0;
            WndReleaseVt8(p);
        }
    }
    ResetWindow(&self->mpWin38);
    ResetWindow(&self->mpWin3C);
    ResetWindow(&self->mpWin40);
    ResetWindow(&self->mpWin44);
    ResetWindow(&self->mpWin48);
    ResetWindow(&self->mpWin4C);
    ResetWindow(&self->mpWin50);
    ResetWindow(&self->mpWin54);
    ResetWindow(&self->mpWin58);
    WndGetHash(self->mpObjA8);
    ResetWindow(&self->mpObjA8);
    for (i = 0; i < 4; ++i) {
        ResetWindow(&self->mpWinA[i]);
        ResetWindow(&self->mpWinB[i]);
    }
    ResetWindow(&self->mpWin7C);
    ResetWindow(&self->mpWin80);
    ResetWindow(&self->mpWin84);
    ResetWindow(&self->mpWin88);
    ResetWindow(&self->mpWin8C);
    ResetWindow(&self->mpWin90);
    self->mC0 = 0;
}

// @ 0x00ef4bd0
void __fastcall FUN_00ef4bd0(cAssetPanel* self)
{
    int i;
    for (i = 0; i < 4; ++i) {
        void* wA = self->mpWinA[i];
        void* wB = self->mpWinB[i];
        if (wA == 0) {
            continue;
        }
        if (wB == 0) {
            continue;
        }
        {
            void* imgWnd = WndFindChild(wA, 0x80834b0, 1);
            void* btnWnd = WndFindChild(wA, 0x805a361, 1);
            void* btnWnd2 = WndFindChild(wA, 0x805a360, 1);
            if (imgWnd == 0) {
                continue;
            }
            if (btnWnd == 0) {
                continue;
            }
            if (btnWnd2 == 0) {
                continue;
            }
            {
                ResKey key;
                uint sub;
                void* mgr;
                int vis;

                WndGetKey(self->mpVerbs98, &key);
                sub = key.mSub;
                sub = ((uint)(i + 1) ^ sub) & 0xff;
                key.mSub = sub ^ key.mSub;
                mgr = ResourceMan_GetManager();
                if (ResourceMan_Query(mgr, &key, 0, 0, 0, 0, 0)) {
                    SetWindowImage(imgWnd, &key, -1);
                }
                vis = WndIsVisible(imgWnd);
                if (vis) {
                    WndShow(btnWnd, 1, 1);
                } else {
                    WndShow(btnWnd, 1, 0);
                }
                WndShow(btnWnd2, 1, vis);
            }
            if (self->mpFlagsA4 != 0) {
                if (self->mpFlagsA4->mFlags[i] != 0) {
                    continue;
                }
            }
            {
                void* wins[2];
                int j;
                wins[0] = wA;
                wins[1] = wB;
                for (j = 0; j < 2; ++j) {
                    float* r = (float*)WndGetArea(wins[j]);
                    float dx = r[2] - r[0];
                    float dy = r[3] - r[1];
                    float inset;
                    float dxn;
                    float dyn;
                    float rect[4];

                    if (dx <= 0.0f) {
                        return;
                    }
                    if (dy <= 0.0f) {
                        return;
                    }
                    inset = MinRef(dx, dy);
                    dxn = (dx - inset) * 0.5f;
                    dyn = (dy - inset) * 0.5f;
                    rect[0] = r[0] + dxn;
                    rect[1] = r[1] + dyn;
                    rect[2] = r[2] - dxn;
                    rect[3] = r[3] - dyn;
                    WndSetArea(wins[j], rect);
                }
            }
        }
    }
}

// @ 0x00ef4e40
void __fastcall FUN_00ef4e40(cAssetPanel* self)
{
    void* w = self->mpLayout->FindWindowByID(0x79836c0, 1);
    if (w == 0) {
        return;
    }
    WndAddRef(w);
    AssetNoun* noun = (AssetNoun*)self->mpNoun9C;
    if (noun != 0) {
        uint imageId = 0;
        switch (WndGetHashU(noun)) {
        case 0x24720859: imageId = 0xf2801199; break;
        case 0x20790816: imageId = 0x65623b56; break;
        case 0x25a6ea6e: imageId = 0xba317a23; break;
        case 0x27818fe6: imageId = 0x8292c121; break;
        case 0x287adcdc: imageId = 0x4a2d27f7; break;
        case 0x37fd4e0d: imageId = 0x77806e4c; break;
        case 0xfb734cd1: imageId = 0xecd899dc; break;
        case 0xe27ddad4: imageId = 0x2df397e7; break;
        case 0xc34c5e14: imageId = 0x257164c3; break;
        case 0xb4707f8f: imageId = 0xbe33ecce; break;
        case 0xc422519e: imageId = 0x70eb3237; break;
        default: break;
        }
        AutoRefCount_s00ef_40d0 ref;
        void* img = 0;
        ref.mpObject = 0;
        if (imageId != 0) {
            ref = SPUIHelpers_GetImageFromLayout(self->mpLayout, imageId);
            img = ref.mpObject;
        }
        if (img != 0) {
            FUN_008068d0(w, img, -1);
            WndRelease(img);
        } else {
            FUN_008068d0(w, 0, -1);
        }
    }
    WndRelease(w);
}

// @ 0x00ef50a0
namespace Simulator {
void cSPScenarioModeSporepediaLargeAssetView::Load()
{
    if (mIsLoaded)
        return;

    mWinRoot = mpLayout->FindWindowByID(0xf3c6dc19, true);
    if (mWinRoot) {
        mWinRoot->AddWinProc(this);
        SPUIHelpers::SetWindowAreaToParent(mWinRoot);
        mRenderView = new("UI", 0, 0, 0, 0) cRenderViewController();
        mRenderView->Attach(mWinRoot);
    }

    AutoRefCount_s00ef_50a0<IWindow> renderWin(mpLayout->FindWindowByID(0x080d8270, true));
    if (mWinRoot && renderWin) {
        const Rect& a = renderWin->GetRealArea();
        Rect r = mWinRoot->GetRealArea();
        float w = a.x2 - a.x1;
        float h = a.y2 - a.y1;
        if (w > h) {
            float rw = r.x2 - r.x1;
            float nw = rw - (w - h);
            float d = (rw - nw) * 0.5f;
            r.x1 += d;
            r.x2 -= d;
        } else if (h > w) {
            float rh = r.y2 - r.y1;
            float nh = rh - (h - w);
            float d = (rh - nh) * 0.5f;
            r.y1 += d;
            r.y2 -= d;
        }
        mWinRoot->SetLayoutArea(r);
    }

    mWinEdit = mpLayout->FindWindowByID(0x06135298, true);
    if (mWinEdit && !SP::Pollen::AuthManager()->IsOffline()) {
        bool queued = false;
        if (mpMetadata) {
            QueueVector& entries = AssetQueue()->mEntries;
            unsigned n = entries.size();
            for (unsigned i = 0; i < n; ++i) {
                QueueEntry& e = entries[i];
                if (e.mState == 2 && e.mAssetKey == mpMetadata->GetAssetKey()) {
                    queued = true;
                    break;
                }
            }
        }
        mWin54 = mpLayout->FindWindowByID(0x0615c7a8, true);
        if (mWin54)
            mWin54->SetFlag(1, queued);
        mWinEdit->SetFlag(1, mpMetadata != 0 && !queued && !IsOwnOrInvalid());
    } else {
        ShowWindow(mWinEdit, false);
    }

    mWin50 = mpLayout->FindWindowByID(0x06136d30, true);
    ShowWindow(mWin50, false);

    IWindow* verbsWin = mpLayout->FindWindowByID(0x34af0c8f, true);
    if (verbsWin) {
        mAssetVerbs = new("UI", 0, 0, 0, 0) SP::cSPUIAssetVerbs_s00ef_50a0();
        mAssetVerbs->Init(verbsWin);
    }

    mWin58 = mpLayout->FindWindowByID(0x07b26750, true);
    for (int i = 0; i < 4; ++i) {
        mWinsA[i] = mpLayout->FindWindowByID(0x07cc9c40 + i, true);
        mWinsB[i] = mpLayout->FindWindowByID(0x07ccb020 + i, true);
    }
    UpdateStats();
    UpdateButtons();

    mHelperA8 = new("UI", 0, 0, 0, 0) cAssetHelperA8();
    mHelperA8->Init(mpLayout, mpMetadata);

    mWin7c = mpLayout->FindWindowByID(0x07b15fc0, true);
    mWin80 = mpLayout->FindWindowByID(0x07b23b28, true);
    mWin84 = mpLayout->FindWindowByID(0x07b173e8, true);
    mWin88 = mpLayout->FindWindowByID(0x07b173f0, true);
    mWinBakingIndicator = mpLayout->FindWindowByID(0x3431bd1e, true);
    mWinBakingForeground = mpLayout->FindWindowByID(0x34a0979a, true);
    ShowWindow(mWinBakingForeground, false);

    IWindow* nameWin = mpLayout->FindWindowByID(0x53d6fe29, true);
    if (nameWin) {
        nameWin->SetCaption(mpAssetData->GetName());
        mNameZoom = new("UI/cSPUITextZoom", 0, 0, 0, 0) UI::TextZoomName();
        mNameZoom->SetTargetWindow((IText*)nameWin->Cast(kITextType), 0, 0, 0, ZoomOffset());
    }

    mWinAuthor = mpLayout->FindWindowByID(0x53d6fe2a, true);
    if (mWinAuthor) {
        mWinAuthor->SetCaption(mpAssetData->GetAuthorName());
        SPUIHelpers::AutoSizeWindowForText(mWinAuthor, 0, 0);
        if (mWinAuthor->GetParent()) {
            Rect pr = mWinAuthor->GetParent()->GetRealArea();
            Rect a = mWinAuthor->GetRealArea();
            mWinAuthor->SetLocation((pr.x2 + pr.x1) * 0.5f - (a.x2 - a.x1) * 0.5f, a.y1);
        }
        if (mWinEdit) {
            Rect ar = mWinAuthor->GetRealArea();
            const Rect& er = mWinEdit->GetRealArea();
            mWinEdit->SetLocation(ar.x2, er.y1);
            Rect r = mWinEdit->GetRealArea();
            if (mWin50)
                SPUIHelpers::CenterWindow(mWin50, Point((r.x2 + r.x1) * 0.5f, (r.y2 + r.y1) * 0.5f));
            if (mWin54)
                SPUIHelpers::CenterWindow(mWin54, Point((r.x2 + r.x1) * 0.5f, (r.y2 + r.y1) * 0.5f));
        }
        cSPAssetDataOTDB* otdb;
        if (mpAssetData != 0 &&
            (otdb = (cSPAssetDataOTDB*)static_cast<IObject*>(mpAssetData)->Cast(0x13d55dc8)) != 0 &&
            otdb->IsLocalAsset())
            mWinAuthor->SetFlag(0x10, true);
        else
            mWinAuthor->SetFlag(0x10, false);
    }

    IWindow* sharedWin = mpLayout->FindWindowByID(0x056e3f98, true);
    if (sharedWin)
        sharedWin->SetFlag(1, mpAssetData->IsShared());

    mWinDescription = mpLayout->FindWindowByID(0xb456a483, true);
    const wchar_t* desc = mpAssetData->GetDescription();
    if (mWinDescription) {
        if (desc != 0 && wcslen(desc) != 0) {
            mWinDescription->SetCaption(desc);
            mWinDescription->GetParent()->SetFlag(1, true);
            mWinDescription->SetFlag(1, true);
        } else {
            mWinDescription->GetParent()->SetFlag(1, false);
            mWinDescription->SetFlag(1, false);
        }
    }
    if (mWinDescription && mWinDescription->GetParent())
        mWinDescription->GetParent()->AddWinProc(this);

    mWinTags = mpLayout->FindWindowByID(0xb456a47a, true);
    if (mWinTags && mpAssetData) {
        string16 tags;
        mpAssetData->GetTags(tags);
        mWinTags->SetCaption(tags.c_str());
    }
    if (mWinTags && mWinTags->GetParent())
        mWinTags->GetParent()->AddWinProc(this);

    IWindow* tagsBox = mpLayout->FindWindowByID(0x07eb4153, true);
    IText* tagsText = tagsBox ? (IText*)tagsBox->Cast(kITextType) : 0;
    if (mWinTags && tagsText) {
        Rect r = mWinTags->GetRealArea();
        tagsText->func14h(false);
        r.x1 = tagsText->ToWindow()->GetRealArea().x2;
        mWinTags->SetLayoutArea(r);
    }

    if (mWinTags) {
        mTagsZoom = new("UI/cSPUITextZoom", 0, 0, 0, 0) UI::TextZoomName();
        mTagsZoom->SetTargetWindow(mWinTags ? (IText*)mWinTags->Cast(kITextType) : 0, 0, 0, 0, ZoomOffset());
    }

    mIsLoaded = true;
}
}  // namespace Simulator

// @ 0x00ef5dd0
void cLargeAssetView::ClearSelection()
{
    {
        void* mem = AllocGame(0x18, &g_allocTag13f6b3c, 0, 0, 0, 0);
        void* pNew;
        if (mem)
            pNew = DialogCtor(mem);
        else
            pNew = 0;

        void* pOld = mp30;
        if (pNew != pOld) {
            if (pNew)
                (*(void (__thiscall**)(void*))((char*)*(void**)pNew + 4))(pNew);
            mp30 = pNew;
            if (pOld)
                (*(void (__thiscall**)(void*))((char*)*(void**)pOld + 8))(pOld);
        }

        Key_s00ef_5dd0 k;
        k.instanceID = 0x6c0fbd13;
        k.typeID = 0x0510a95b;
        k.groupID = g_dw15ace34;
        ((cSPUILayout_s00ef_5dd0*)mp30)->Init(k, true, 0x5b598fa);

        void* pEmbed = &mEmbed;
        (*(void (__thiscall**)(void*))mEmbed.mpVtable)(pEmbed);

        ((cSPUILayout_s00ef_5dd0*)mp30)->SetParentWin((IWindow_s00ef_5dd0*)mp34, true, 0x5b598fa);
        ((cSPUILayout_s00ef_5dd0*)mp30)->SetReloadCallback(FUN_00ef5d80, this);
    }
    return Load();
}

// @ 0x00ef5e90
void cLargeAssetView::ShowMetadata(IResource* r)
{
    cPropertyBag* bag = (cPropertyBag*)r;

    struct Props { int32_t nA; float fB; int32_t nC; } p;
    p.nC = 0;
    p.nA = 3;
    p.fB = 0.0f;
    if (!bag->GetInt32(0x35c95bc4, &p.nC)) return;
    if (!bag->GetInt32(0x11576eea, &p.nA)) return;
    if (!bag->GetFloat(0x190e18aa, &p.fB)) return;

    IWindow_s00ef_5dd0* p7c = (IWindow_s00ef_5dd0*)mp7c;
    if (!p7c) return;
    p7c->SetFlag(1, 1);

    uint32_t u = (uint32_t)FUN_00ec3ca0(p.fB);

    if (mp80) {
        void* pObj = (*(void* (__thiscall**)(void*, uint32_t))
                      ((char*)*(void**)mp80 + 0x0c))(mp80, 0x106f146);
        if (pObj) {
            void* pSub = (char*)pObj + 0x20c;
            (*(void (__thiscall**)(void*, uint32_t))
             ((char*)*(void**)pSub + 0x14))(pSub, u);

            {
                cTooltip* tip = (cTooltip*)FUN_009512d0(
                    0x68, 4, "UI/Tooltip", FUN_009512c0());
                if (tip) tip = TooltipCtor(tip);

                tAutoRef ref;
                ref.Init(tip);

                {
                    cString_s00ef_5dd0 s;
                    s.Load(0x6f5943eb, 0xc7647889, 0);
                    tip->SetText(s.GetText(), (void*)-1, (char)1);
                    (*(void (__thiscall**)(void*, void*))
                     ((char*)*(void**)mp80 + 0x104))(mp80, ref.mp);
                }

                if (ref.mp)
                    (*(void (__thiscall**)(void*))
                     ((char*)*(void**)ref.mp + 4))(ref.mp);
            }
        }
    }

    gAdventureTray->mTimesPlayed = p.nC;

    {
        cString_s00ef_5dd0 s2;
        s2.Load(0x6f5943eb, 0x2100001, L"*number of times played*");
        IWindow_s00ef_5dd0* p84 = (IWindow_s00ef_5dd0*)mp84;
        if (p84)
            p84->SetCaption(s2.GetText());

        if (mp88) {
            void* pObj2 = (*(void* (__thiscall**)(void*, uint32_t))
                           ((char*)*(void**)mp88 + 0x0c))(mp88, 0x106f146);
            if (pObj2) {
                void* pSub2 = (char*)pObj2 + 0x20c;

                int nMax = (*(int (__thiscall**)(void*))
                            ((char*)*(void**)pSub2 + 0x10))(pSub2);
                int n = p.nA;
                if (n < 1)
                    n = 1;
                else if (n > nMax)
                    n = nMax;
                p.nA = n;

                int n2;
                if (n >= 1) {
                    int nMax2 = (*(int (__thiscall**)(void*))
                                 ((char*)*(void**)pSub2 + 0x10))(pSub2);
                    if (n <= nMax2)
                        (*(void (__thiscall**)(void*, int))
                         ((char*)*(void**)pSub2 + 0x14))(pSub2, n - 1);

                    int c = p.nA;
                    if (c < 1)
                        n2 = 1;
                    else if (c > 5)
                        n2 = 5;
                    else
                        n2 = c;
                } else {
                    n2 = 1;
                }
                p.nA = n2;

                {
                    cString_s00ef_5dd0 s3;
                    s3.Load(0x6f5943eb, g_textGroups[n2], 0);
                    gAdventureTray->SetCaption(s3.GetText());

                    {
                        cString_s00ef_5dd0 s4;
                        s4.Load(0x6f5943eb, 0x7d86c49, 0);

                        cTooltip* tip = (cTooltip*)FUN_009512d0(
                            0x68, 4, "UI/Tooltip", FUN_009512c0());
                        if (tip) tip = TooltipCtor(tip);

                        tAutoRef ref;
                        ref.Init(tip);

                        tip->SetText(s4.GetText(), (void*)-1, (char)1);
                        (*(void (__thiscall**)(void*, void*))
                         ((char*)*(void**)mp88 + 0x104))(mp88, ref.mp);

                        if (ref.mp)
                            (*(void (__thiscall**)(void*))
                             ((char*)*(void**)ref.mp + 4))(ref.mp);
                    }
                }
            }
        }
    }
}

// @ 0x00ef61b0
void cLargeAssetView::Destroy()
{
    mpVtbl00 = (void*)0x148b3f8;
    mpVtbl04 = (void*)0x148b3e8;
    mpVtbl08 = (void*)0x148b3dc;
    mEmbed.mpVtable = (void*)0x140085c;
    mp24 = (void*)0x148b3c4;
    mp28 = (void*)0x148b3b4;

    _ReadWriteBarrier();
    if (mnF0) {
        uint32_t h = mnF0;
        mnF0 = 0;
        RemoveHandler(h, mnF4, mnF8, mnFC, mn100);
    }

    if (mpC4 && mpC4 != mpD4)
        operator_delete__(mpC4);

    if (mpB0)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpB0 + 8))(mpB0);
    if (mpAC)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpAC + 8))(mpAC);
    if (mpA8)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpA8 + 4))(mpA8);
    if (mpA4)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpA4 + 4))(mpA4);
    if (mpA0)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpA0 + 4))(mpA0);
    if (mp9c) {
        void* p = (char*)mp9c + 0x10;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    if (mp98)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp98 + 4))(mp98);
    if (mp94)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp94 + 4))(mp94);
    if (mp90)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp90 + 4))(mp90);
    if (mp8c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp8c + 4))(mp8c);
    if (mp88)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp88 + 4))(mp88);
    if (mp84)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp84 + 4))(mp84);
    if (mp80)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp80 + 4))(mp80);
    if (mp7c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp7c + 4))(mp7c);

    {
        void** pp = &map6c[4];
        int i = 3;
        do {
            void* q = *--pp;
            if (q)
                (*(void (__thiscall**)(void*))((char*)*(void**)q + 4))(q);
        } while (--i >= 0);
    }
    {
        void** pp = &map5c[4];
        int i = 3;
        do {
            void* q = *--pp;
            if (q)
                (*(void (__thiscall**)(void*))((char*)*(void**)q + 4))(q);
        } while (--i >= 0);
    }

    if (mp58)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp58 + 4))(mp58);
    if (mp54)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp54 + 4))(mp54);
    if (mp50)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp50 + 4))(mp50);
    if (mp4c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp4c + 4))(mp4c);
    if (mp48)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp48 + 4))(mp48);
    if (mp44)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp44 + 4))(mp44);
    if (mp40)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp40 + 4))(mp40);
    if (mp3c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp3c + 4))(mp3c);
    if (mp38)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp38 + 4))(mp38);
    if (mp34)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp34 + 4))(mp34);
    if (mp30)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp30 + 8))(mp30);

    mp28 = (void*)0x13ec458;
    mpVtbl04 = (void*)0x13eb394;
    mpVtbl00 = (void*)0x13eb938;
}

// @ 0x00ef64e0
cLargeAssetView* __fastcall cLargeAssetView_Ctor(cLargeAssetView* pThis)
{
    void** ppEmbed = (void**)&pThis->mEmbed;
    pThis->mpVtbl00 = (void*)0x14426a0;
    _ReadWriteBarrier();
    pThis->mpVtbl04 = (void*)0x13eb384;
    FUN_0066f200(ppEmbed);
    _ReadWriteBarrier();
    pThis->mp24 = (void*)0x1400744;
    pThis->mp28 = (void*)0x13ec458;
    _ReadWriteBarrier();
    pThis->mn2c = 0;
    _ReadWriteBarrier();
    pThis->mpVtbl00 = (void*)0x148b3f8;
    pThis->mpVtbl04 = (void*)0x148b3e8;
    pThis->mpVtbl08 = (void*)0x148b3dc;
    *ppEmbed = (void*)0x140085c;
    pThis->mp24 = (void*)0x148b3c4;
    pThis->mp28 = (void*)0x148b3b4;
    _ReadWriteBarrier();

    pThis->mp30 = 0;
    pThis->mp34 = 0;
    pThis->mp38 = 0;
    pThis->mp3c = 0;
    pThis->mp40 = 0;
    pThis->mp44 = 0;
    pThis->mp48 = 0;
    pThis->mp4c = 0;
    pThis->mp50 = 0;
    pThis->mp54 = 0;
    pThis->mp58 = 0;
    pThis->map5c[0] = 0;
    pThis->map5c[1] = 0;
    pThis->map5c[2] = 0;
    pThis->map5c[3] = 0;
    pThis->map6c[0] = 0;
    pThis->map6c[1] = 0;
    pThis->map6c[2] = 0;
    pThis->map6c[3] = 0;
    pThis->mp7c = 0;
    pThis->mp80 = 0;
    pThis->mp84 = 0;
    pThis->mp88 = 0;
    pThis->mp8c = 0;
    pThis->mp90 = 0;
    pThis->mp94 = 0;
    pThis->mp98 = 0;
    pThis->mp9c = 0;
    pThis->mpA0 = 0;
    pThis->mpA4 = 0;
    pThis->mpA8 = 0;
    pThis->mpAC = 0;
    pThis->mpB0 = 0;

    pThis->mbC0 = 0;
    pThis->mbC1 = 0;
    pThis->mbC2 = 0;
    pThis->mbC3 = 0;
    _ReadWriteBarrier();

    uint32_t minus1 = (uint32_t)-1;
    pThis->mnB8 = (int32_t)minus1;
    pThis->mnBC = (int32_t)minus1;

    void* pBuf = &pThis->mBuf[0];
    pThis->mpD4 = pBuf;
    pThis->mpC8 = pBuf;
    pThis->mpC4 = pBuf;
    pThis->mpCC = (char*)pBuf + 0x10;
    _ReadWriteBarrier();

    pThis->mnF0 = 0;
    pThis->mnF4 = 0;
    pThis->mnF8 = 0;
    pThis->mnFC = 0;
    pThis->mn100 = 0;
    return pThis;
}

// @ 0x00ef6650
void cLargeAssetView::OnMessage(void* sender, uint32_t msgId)
{
    if (msgId == 0x5107b1a) {
        cPollinator_s00ef_5dd0* poll = Pollinator_Get();
        if (poll) {
            void* p48 = mp48;
            if (p48)
                (*(void (__thiscall**)(void*, int, int))
                 ((char*)*(void**)p48 + 0x7c))(p48, 1, 1);
            void* p44 = mp44;
            if (p44)
                (*(void (__thiscall**)(void*, int, int))
                 ((char*)*(void**)p44 + 0x7c))(p44, 1, 0);

            if (mp98) {
                ((uint8_t*)&msgId)[0] = 0;      // message id with the low byte cleared
                int64_t id = Meta_GetID64(mp98);

                struct EaString { void* mpBegin; void* mpEnd; void* mpCap; uint32_t mPad; } str;
                FormatString(&str, msgId, "tag:spore.com,2006:user/%I64u", id);

                Pollinator_Get()->SubscribeToFeed(str.mpBegin);

                if ((char*)str.mpCap - (char*)str.mpBegin > 1 && str.mpBegin)
                    operator_delete__(str.mpBegin);
            }
        }
    }
}

// @ 0x00ef6700
bool AssetView::SetAsset(IRefCounted* a1, cAssetData_s00ef_5dd0* asset, uint32_t a3, bool a4, int a5)
{
    mBusy = 1;
    mAsset = asset;
    mArg1 = a1;
    mKeyLo = (uint32_t)-1;
    mKeyHi = (uint32_t)-1;
    mMetadata.Reset();

    cAssetData_s00ef_5dd0* data = 0;
    if (mAsset) {
        data = (cAssetData_s00ef_5dd0*)mAsset->Cast(0x13d55dc8);
        if (data) {
            const Key_s00ef_5dd0* k = mAsset->GetKey();
            ARef<IResource> ref;
            ref.mp = 0;
            IResourceManager* mgr = EA::ResourceMan::GetManager();
            ref.Reset();
            Key_s00ef_5dd0 key;
            key.instanceID = k->instanceID;
            key.typeID = 0x30bdee3;
            key.groupID = k->groupID;
            if (mgr->GetResource(&key, &ref.mp, 0, 0, 0, 0)) {
                cAssetMetadata_s00ef_5dd0* md = ref ? (cAssetMetadata_s00ef_5dd0*)ref->Cast(0x30bdee3) : 0;
                mMetadata = md;
            }
        }
    }
    mSummary.Reset();

    ARef<IResource> ref2;
    ref2.mp = 0;
    {
        cAssetData_s00ef_5dd0* a = mAsset;
        IResourceManager* mgr = EA::ResourceMan::GetManager();
        ref2.Reset();
        if (mgr->GetResource(a->GetKey(), &ref2.mp, 0, 0, 0, 0)) {
            cAssetSummary* s = ref2 ? (cAssetSummary*)ref2->Cast(0xe742574a) : 0;
            mSummary = s;
        }
    }

    GetPrimary()->ClearSelection();
    IMessageListener* listener = GetPrimary();
    IMessageServer* ms = SP_MessageServer_s00ef_5dd0();
    mReg.server = ms;
    mReg.listener = listener;
    mReg.ids = kViewMessages;
    mReg.count = 3;
    mReg.n = 0;
    if (ms && listener) {
        for (uint32_t i = 0; i < 12; i += 4)
            ms->AddListener(listener, *(const uint32_t*)((const char*)kViewMessages + i));
    }

    if (data && mHelper) {
        uint64_t id;
        if (!data->GetAssetID(id)) {
            mHelper->SetOnline(0);
        } else {
            mHelper->SetOnline(1);
            mHelper->SetKey((uint32_t)id, (uint32_t)(id >> 32));
        }
    }

    if (mVerbs) {
        ShowParams p;
        p.f0 = a3;
        p.b4 = false;
        p.b5 = a4;
        p.b6 = true;
        mVerbs->Show(1, &p, mAsset);
    }

    if (mWinEnable) {
        bool isLocal = data && data->IsLocalAsset();
        bool hasAuthor = data && data->GetAuthorID() != 0;
        bool offConfig = SP_ConfigManager()->GetValue(0x5de7b4a) != 0;
        bool offline = SP::Pollen::AuthManager_s00ef_5dd0()->IsOffline();
        bool enable;
        if (!offConfig && !offline && !isLocal && hasAuthor)
            enable = true;
        else
            enable = false;
        mWinEnable->SetFlag(2, enable);
        mWinEnable->SetFlag(0x10, !enable);
    }

    if (mWinCaption) {
        gAdventureTray->mAdventurePoints = AdventurePointsFor(mAsset->GetKey());
        cString_s00ef_5dd0 s;
        s.Load(0x6f5943eb, 0x2100002, L"*adventure points*");
        mWinCaption->SetCaption(s.GetText());
    }

    if (mMetadata) {
        const Key_s00ef_5dd0* k = mMetadata->GetAssetKeyPtr();
        mKeyLo = k->instanceID;
        mKeyHi = k->typeID;
    }

    if (mWinHide)
        mWinHide->SetFlag(1, 0);

    int ok = 1;
    if (mAsset)
        ok = IsAssetUnlocked(mAsset->GetKey());

    mFlag9e = 0;
    mFlag9f = 0;
    _ReadWriteBarrier();
    {
        int* first = mVecBegin;
        int* last = mVecEnd;
        memcpy(first, last, (size_t)((char*)mVecEnd - (char*)last));
        mVecEnd -= (last - first);
    }
    _ReadWriteBarrier();

    if ((mKeyLo & mKeyHi) != 0xffffffff && ok != 0) {
        if (SP::Pollen::AuthManager_s00ef_5dd0()->IsOffline()) {
            IResource* out = 0;
            cMetadataFetcher* f = AssetQueue_s00ef_5dd0()->mpFetcher;
            if (f->FindMetadata(mKeyLo, mKeyHi, &out, 0))
                GetPrimary()->ShowMetadata(out);
            if (out)
                out->Release();
        } else {
            cMetadataFetcher* f = AssetQueue_s00ef_5dd0()->mpFetcher;
            if (f->FindMetadata(mKeyLo, mKeyHi, 0, 1))
                mFlag9e = 1;
            int i = 0;
            for (uint32_t off = 0x68; off < 0x78; off += 4, ++i) {
                if (mSummary) {
                    int v = *(int*)((char*)(cAssetSummary*)mSummary + off);
                    if (v == 1 || v == 0) {
                        Key_s00ef_5dd0 img = mAsset->GetImageKey();
                        Key_s00ef_5dd0 k2;
                        k2.instanceID = img.instanceID;
                        k2.typeID = img.typeID;
                        k2.groupID = (img.groupID & 0xffffff00) | ((i + 1) & 0xff);
                        if (!EA::ResourceMan::GetManager()->GetResource(&k2, 0, 0, 0, 0, 0)) {
                            AssetQueue_s00ef_5dd0()->GetAssetFeedEx(mKeyLo, mKeyHi);
                            mFlag9f = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (ok == 0) {
        IWindow_s00ef_5dd0* w1 = mLayout->FindWindowByID(0x7ccce30, 1);
        IWindow_s00ef_5dd0* w2 = mLayout->FindWindowByID(0x7ccce38, 1);
        IWindow_s00ef_5dd0* w3 = mLayout->FindWindowByID(0x8003ed0, 1);
        IWindow_s00ef_5dd0* w4 = mLayout->FindWindowByID(0x7da34f8, 1);
        if (w1)
            w1->SetFlag(1, 0);
        if (w4)
            w4->SetFlag(1, 0);
        if (w2 && w3) {
            w2->SetLayoutArea(w3->GetRealArea());
            IWindow_s00ef_5dd0* w5 = w2->FindWindowByID(0x7b69988, 1);
            if (w5)
                w5->SetFlag(1, 0);
        }
    }

    SP_WindowManager_s00ef_5dd0()->SetFocus(0, mWinFocus.mp);
    return true;
}

// @ 0x00ef6db0
void CAssetView::Reset()
{
    char* self = (char*)this;
    *(uint8_t*)(self + 0x9d) = 0;
    void* p = *(void**)(self + 0x78);
    if (p != 0) {
        *(void**)(self + 0x78) = 0;
        ((IRefCounted_s00ef_6db0*)((char*)p + 0x10))->v1();
    }
    p = *(void**)(self + 0x7c);
    if (p != 0) {
        *(void**)(self + 0x7c) = 0;
        ((IRefCounted_s00ef_6db0*)p)->v1();
    }
    *(int*)(self + 0x94) = -1;
    *(int*)(self + 0x98) = -1;
    p = *(void**)(self + 0x80);
    if (p != 0) {
        *(void**)(self + 0x80) = 0;
        ((IRefCounted_s00ef_6db0*)p)->v1();
    }
    void* h = *(void**)(self + 0xcc);
    if (h != 0) {
        void* a0 = *(void**)(self + 0xd0);
        void* a1 = *(void**)(self + 0xd4);
        void* a2 = *(void**)(self + 0xd8);
        void* a3 = *(void**)(self + 0xdc);
        *(void**)(self + 0xcc) = 0;
        RemoveHandler(h, a0, a1, a2, a3);
    }
    *(uint8_t*)(self + 0x9e) = 0;
    *(uint8_t*)(self + 0x9f) = 0;
    uint32_t* begin = *(uint32_t**)(self + 0xa0);
    uint32_t* end   = *(uint32_t**)(self + 0xa4);
    memcpy(begin, end, 0);
    int n = (int)(end - begin);
    *(uint32_t**)(self + 0xa4) -= n;
    CSPUILayout* L = *(CSPUILayout**)(self + 0xc);
    if (L != 0) {
        L->Shutdown(1);
        L = *(CSPUILayout**)(self + 0xc);
        if (L != 0) {
            *(void**)(self + 0xc) = 0;
            L->v2();
        }
    }
}

// @ 0x00ef6ea0
bool CAssetView::RemoveKey(void* key)
{
    char* self = (char*)this;
    uint32_t* begin = *(uint32_t**)(self + 0);
    uint32_t* end   = *(uint32_t**)(self + 4);
    uint32_t* pos = (uint32_t*)FUN_00555a20(begin, end, key, *(uint8_t*)(self + 0x28));
    if (pos == end || *(uint32_t*)key < *pos)
        pos = end;
    if (pos != end) {
        uint32_t* src = pos + 1;
        if (src < end)
            memcpy(pos, src, (int)end - (int)src);
        *(int*)(self + 4) -= 4;
        return true;
    }
    return false;
}

// @ 0x00ef6f20
bool CAssetView::HandleMessage(uint32_t msg, void* arg1)
{
    char* self = (char*)this;
    CAssetView* owner = (CAssetView*)(self - 4);
    CVec* vec = (CVec*)(self + 0xc0);
    if (msg == 0x1dd7bda9) {
        char* a = (char*)arg1;
        bool flag = (*(int*)a != 1);
        void* o = *(void**)(a + 4);
        if (o == 0)
            return false;
        int id = ((FN0_i)((*(void***)o)[4]))(o);
        if (id == 0x226182d1) {
            o = *(void**)(a + 4);
            if (o == 0)
                return false;
            if (*(int*)((char*)o + 0xf0) != *(int*)(self + 0xb4) ||
                *(int*)((char*)o + 0xf4) != *(int*)(self + 0xb8))
                return false;
            if (flag) {
                *(uint8_t*)(self + 0xbf) = 0;
                vec->clear();
                return false;
            }
            vec->f_ef6f00(*(void**)((char*)o + 0xf8), *(void**)((char*)o + 0xfc));
            return false;
        }
        if (id == 0x326ffe34) {
            o = *(void**)(a + 4);
            if (o == 0)
                return false;
            void* layoutObj = *(void**)(self + 0x98);
            int r = ((FN0_i)((*(void***)layoutObj)[0x10]))(layoutObj);
            if ((char)FUN_004eb930((char*)o + 0x14, r) != 0) {
                if (flag) {
                    *(uint8_t*)(self + 0xbf) = 0;
                    vec->clear();
                    return false;
                }
                vec->RemoveKey((char*)o + 0x10);
                if (*(int*)(self + 0xc0) == *(int*)(self + 0xc4)) {
                    *(uint8_t*)(self + 0xbf) = 0;
                    owner->sub_ef4bd0();
                    return false;
                }
            }
            return false;
        }
        if (id == 0x3053c62 && *(int*)((char*)o + 0xc) == 1) {
            int64_t v = -1;
            if (sscanf(*(const char**)((char*)o + 0x1c), "tag:spore.com,2006:user/%I64u", &v) == 1 &&
                *(void**)(self + 0x98) != 0) {
                void* layoutObj = *(void**)(self + 0x98);
                int64_t cur = ((int64_t(__thiscall*)(void*))(*(void***)layoutObj)[0x15])(layoutObj);
                if (cur == v) {
                    if (*(void**)(self + 0x4c) != 0)
                        ((FN2_ii)((*(void***)*(void**)(self + 0x4c))[0x1f]))(*(void**)(self + 0x4c), 1, 0);
                    if (flag) {
                        if (*(void**)(self + 0x48) != 0)
                            ((FN2_ii)((*(void***)*(void**)(self + 0x48))[0x1f]))(*(void**)(self + 0x48), 1, 1);
                        UI_CalloutMessageBox(0, (void*)0x015acee4);
                    } else {
                        if (*(void**)(self + 0x50) != 0)
                            ((FN2_ii)((*(void***)*(void**)(self + 0x50))[0x1f]))(*(void**)(self + 0x50), 1, 1);
                        void* ms = SP_MessageServer();
                        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x53dd093, 0);
                    }
                }
            }
            return false;
        }
        return false;
    }
    if (msg == 0x7a43c598) {
        int v[3];
        v[0] = ((int*)arg1)[0];
        v[1] = ((int*)arg1)[1];
        v[2] = ((int*)arg1)[2];
        void* ms = SP_MessageServer();
        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x14ac4938, 0);
        ms = SP_MessageServer();
        ((FN2_ip)((*(void***)ms)[5]))(ms, 0xcadf3aca, (void*)v);
        return false;
    }
    if (msg == 0x9818ab6c && arg1 != 0) {
        char* a = (char*)arg1;
        if (*(int*)(self + 0xb4) == *(int*)(a + 8) && *(int*)(self + 0xb8) == *(int*)(a + 0xc)) {
            void* x = FUN_0067cb30();
            void* obj = *(void**)((char*)x + 0x5c);
            CAutoRef tmp;
            if (*(char*)a == 0) {
                void* p = tmp.AsPPTypeParam(0);
                if ((char)FUN_00612f50(*(int*)(self + 0xb4), *(int*)(self + 0xb8), p, 0) != 0) {
                    FUN_005810a0();
                    FUN_00ef5e90(owner, 0);
                }
            } else {
                void* p = tmp.AsPPTypeParam(0);
                FUN_00612f50(*(int*)(self + 0xb4), *(int*)(self + 0xb8), p, 0);
                (void)obj;
            }
            *(uint8_t*)(self + 0xbe) = 0;
        }
        return false;
    }
    return false;
}

// @ 0x00ef7280
int __cdecl FUN_00ef7280()
{
    void* cm = SP_ConfigManager_s00ef_6db0();
    return ((FN1_pi)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0;
}

// @ 0x00ef72a0
bool __fastcall FUN_00ef72a0(char* p)
{
    if (*(int*)(p + 0x30) != -1)
        return true;
    return false;
}

// @ 0x00ef72b0
void __fastcall FUN_00ef72b0(char* p)
{
    if (*(char*)(p + 0x3d) != 0) {
        *(char*)(p + 0x3e) = 1;
        *(char*)(p + 0x3d) = 0;
    }
}

// @ 0x00ef72c0
void __fastcall FUN_00ef72c0(char* p)
{
    if (*(int*)(p + 0x30) != -1)
        *(char*)(p + 0x3f) = 1;
}

// @ 0x00ef72d0
int __stdcall FUN_00ef72d0(int k)
{
    if (k == 0x2a || k == 0x38 || k == 7 || k == 0xa2 || k == 0x8d || k == 0x24 ||
        k == 0xb || k == 0x74 || k == 0x27 || k == 0x3c || k == 0x17 || k == 0x3a)
        return 0;
    return 1;
}

// @ 0x00ef7330
int __stdcall FUN_00ef7330(int k)
{
    if (k == 7 || k == 0x8d || k == 0xa2 || k == 0x38)
        return 2;
    if (k == 0x24)
        return 1;
    if (k == 0xb || k == 0x74 || k == 0x27)
        return 0x1e;
    if (k == 0x3c)
        return 2;
    if (k == 0x17)
        return 1;
    return ((k != 0x3a) - 1) & 2;
}

// @ 0x00ef73c0
void __cdecl FUN_00ef73c0()
{
    if ((g_16c7b84 & 1) == 0) {
        g_16c7b84 |= 1;
        *(void**)g_16c7b80 = &gVtbl_E;
    }
    Simulator_s00ef_6db0* sim = gSimulator;
    int mode = *(int*)((char*)sim + 0xd0);
    void* prefs = gAppPreferences;
    bool bIsSingle = (mode == 1 || mode == 2);
    bool bConfig = false;
    {
        void* cm = SP_ConfigManager_s00ef_6db0();
        bConfig = ((FN1_pi)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) != 0;
    }
    char bKey = 0;
    if (prefs != 0) {
        char aux[0xc];
        if ((char)((FN2_ipr)((*(void***)prefs)[9]))(prefs, 0x7be69ad, aux) != 0) {
            void* prop = *(void**)aux;
            if (*(short*)((char*)prop + 0x12) == 1) {
                char* b = ((char* (__thiscall*)(void*))Property_GetBool)(prop);
                bKey = *b;
            }
        }
    }
    if (bIsSingle && bConfig && bKey == 0) {
        void* gt = SP_GameTimeManager();
        ((FN1_i)((*(void***)gt)[0x10]))(gt, 0x4bf38a7);
        // four oriented marker units: position row from the 4x3 table, bookend column
        // (-1,-1,0), and for the last one the placement object instead of the bookend
        typedef void  (__thiscall *FN_MatInit)(void*, Vec3f, void*, int, Vec3f, int, int);
        const float kNegOne = *(float*)0x013eb1bc;      // -1.0f
        for (int i = 0; i < 4; ++i) {
            const Vec3f pos = *(const Vec3f*)(0x015ad21c + i * 0xc);
            const Vec3f dir = { kNegOne, kNegOne, 0.0f };
            void* obj;
            if (i == 3) obj = (void*)g_16c7b80;
            else        obj = (void*)0;
            void* base = FUN_0067caf0();
            ((FN_MatInit)FUN_0067aaf0)(base, pos, obj, 0, dir, 0, 0);
        }
    }
}

// @ 0x00ef75b0
void CAssetView::sub_ef75b0(int category, int a, int b)
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* pinv = inv->GetPlayerInventory();
        if (pinv->FindCategoryIndex() == category) {
            sub_efa0b0(a, 0);
            sub_efa0b0(b, 0);
        }
    }
}

// @ 0x00ef7600
void CAssetView::sub_ef7600(int category, int a, int b)
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    char* o = (char*)sg->f_00641770();
    if (o != 0 && *(int*)(o + 0x28) == category) {
        sub_efa0b0(a, 0);
        sub_efa0b0(b, 0);
    }
}

// @ 0x00ef7640
void CAssetView::sub_ef7640(int category, char flag)
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* pinv = inv->GetPlayerInventory();
        if (pinv->FindCategoryIndex() == category) {
            pinv = inv->GetPlayerInventory();
            if (pinv != 0) {
                pinv->f5cb180(1);
                char* x = (char*)FUN_0067caf0();
                if (*(char*)(x + 0x1a1) != 0 && flag == 0)
                    pinv->f5ca910();
            }
        }
    }
}

// @ 0x00ef76a0
void CAssetView::sub_ef76a0(int category, char flag)
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    char* o = (char*)sg->f_00641770();
    if (o != 0 && *(int*)(o + 0x28) == category) {
        CPlayerInventory* x = *(CPlayerInventory**)(o + 0x20);
        if (x != 0) {
            x->f5cb180(1);
            char* y = (char*)FUN_0067caf0();
            if (*(char*)(y + 0x1a1) != 0 && flag == 0)
                x->f5ca910();
        }
    }
}

// @ 0x00ef76f0
bool __cdecl FUN_00ef76f0()
{
    Simulator_s00ef_6db0* sim = gSimulator;
    char* s = (char*)sim;
    char r = (char)sim->f_ef00d0();
    if (r == 0) {
        int mode = *(int*)(s + 0xcc);
        if (mode == 1) {
            char* o = *(char**)(s + 0x14);
            if (o == 0 || *(char*)(o + 0x94) == 0)
                return false;
        } else if (mode == 2) {
            char* o = *(char**)(s + 0x6c);
            if (o == 0 || *(char*)(o + 0x59) == 0)
                return false;
        } else {
            return false;
        }
        return true;
    }
    return false;
}

// @ 0x00ef7740
int __cdecl FUN_00ef7740()
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* a = inv->GetPlayerInventory3(0, 0, 0);
        CPlayerInventory* b = a->f5cae30();
        CPlayerInventory* c = b->f5c2e50();
        return (int)c->f5cae30();
    }
    return 0;
}

// @ 0x00ef7780
int __fastcall FUN_00ef7780(char* p)
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        int k = *(int*)(p + 0x44);
        if (k == -1)
            k = 5;
        CPlayerInventory* a = inv->GetPlayerInventory3(0, 0, k);
        CPlayerInventory* b = a->f5cae30();
        CPlayerInventory* c = b->f5c2e50();
        return (int)c->f5cae30();
    }
    return 0;
}

// @ 0x00ef77d0
int __cdecl FUN_00ef77d0()
{
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv != 0) {
        CPlayerInventory* a = inv->GetPlayerInventory3(1, 0, 0);
        CPlayerInventory* b = a->f5cae30();
        CPlayerInventory* c = b->f5c2e50();
        return (int)c->f5cae30();
    }
    return 0;
}

// @ 0x00ef7810
void __fastcall FUN_00ef7810(char* p, char param)
{
    *(int*)(p + 0x44) = -1;
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceGame* sg = *(CSpaceGame**)((char*)sim + 0x14);
    CPlayerInventory* inv = *(CPlayerInventory**)((char*)sg + 0x14);
    if (inv == 0)
        return;
    CPlayerInventory* a = inv->GetPlayerInventory2(0, 0);
    CPlayerInventory* b = a->f5cae30();
    char* list = (char*)b->f5c2e50();
    int count = (*(int*)(list + 0x38) - *(int*)(list + 0x34)) >> 2;
    int i = (param != 0);
    while (i < count) {
        CPlayerInventory* x = b->f5cae30(i);
        int id;
        if (x == 0)
            id = 0;
        else
            id = ((FN1_pi)((*(void***)((char*)x + 0xc))[3]))((char*)x + 0xc, 0x722de63);
        void* alloc = ((CResource*)id)->GetAllocator();
        void* mgr = *(void**)((char*)gSimulator + 0x74);
        void* r = FUN_00f3e8a0(mgr, alloc);
        if (r != 0) {
            *(int*)(p + 0x44) = i;
            return;
        }
        i++;
    }
}

// @ 0x00ef78c0
int __cdecl FUN_00ef78c0()
{
    char* sim = (char*)gSimulator;
    CAllocMgr* mgr = *(CAllocMgr**)(sim + 0x74);
    void* a = FUN_00efc520_s00ef_6db0();
    CMgrResult* r = (CMgrResult*)mgr->f_00f3be60(a);
    int* q = (int*)((char*)r + 0x84);
    return (q[1] - q[0]) / 0x188;
}

// @ 0x00ef7900
unsigned __fastcall FUN_00ef7900(char* p)
{
    int z = 0;
    *(void**)(p + 4) = &gVtbl_D;
    *(int*)(p + 8) = z;
    *(void**)p = &gVtbl_A;
    *(void**)(p + 4) = &gVtbl_B;
    *(int*)(p + 0xc) = z;
    *(int*)(p + 0x10) = z;
    *(int*)(p + 0x14) = z;
    *(int*)(p + 0x18) = z;
    *(int*)(p + 0x1c) = z;
    *(int*)(p + 0x20) = z;
    *(uint8_t*)(p + 0x24) = (uint8_t)z;
    int m = -1;
    *(uint8_t*)(p + 0x25) = 1;
    *(int*)(p + 0x28) = m;
    *(int*)(p + 0x34) = m;
    return (unsigned)(size_t)p;
}

// @ 0x00ef7950
void __fastcall FUN_00ef7950(char* p)
{
    *(void**)p = &gVtbl_A;
    *(void**)(p + 4) = &gVtbl_B;
    if (*(void**)(p + 0x20) != 0)
        ((IRefCounted_s00ef_6db0*)*(void**)(p + 0x20))->v1();
    if (*(void**)(p + 0x1c) != 0)
        ((IRefCounted_s00ef_6db0*)*(void**)(p + 0x1c))->v1();
    if (*(void**)(p + 0x18) != 0)
        ((IRefCounted_s00ef_6db0*)*(void**)(p + 0x18))->v1();
    if (*(void**)(p + 0x14) != 0)
        ((IRefCounted_s00ef_6db0*)*(void**)(p + 0x14))->v1();
    if (*(void**)(p + 0x10) != 0)
        ((IRefCounted_s00ef_6db0*)*(void**)(p + 0x10))->v2();
    if (*(void**)(p + 0xc) != 0)
        ((IRefCounted_s00ef_6db0*)*(void**)(p + 0xc))->v1();
    *(void**)p = &gVtbl_C;
    *(void**)(p + 4) = &gVtbl_D;
}

// @ 0x00ef79d0
void CScenarioTutorialsChecklistUI::sub_ef79d0()
{
    char* p = (char*)this;
    CSPUILayout* L = *(CSPUILayout**)(p + 0x10);
    if (L != 0) {
        L->Shutdown(1);
        L = *(CSPUILayout**)(p + 0x10);
        if (L != 0) {
            *(void**)(p + 0x10) = 0;
            L->v2();
        }
    }
}

// @ 0x00ef7a00
void CScenarioTutorialsChecklistUI::sub_ef7a00()
{
    char* p = (char*)this;
    if (*(char*)(p + 0x25) == 0) {
        void* tray = *(void**)(p + 0x20);
        ((FN2_ii)((*(void***)tray)[10]))(tray, 4, 1);
        CString s(0xf3108302, (void*)0x07a248a0, 0);
        tray = *(void**)(p + 0x20);
        const char* t = s.GetText(-1, 1);
        void* r = ((FN1_p)((*(void***)tray)[4]))(tray, (void*)t);
        SetTooltipText(r);
        AnchorWindowToWindow(*(void**)(p + 0xc), *(void**)(p + 0x14), 0x11, 0);
        *(char*)(p + 0x25) = 1;
        s.~CString();
    }
}

// @ 0x00ef7a80
void CScenarioTutorialsChecklistUI::sub_ef7a80()
{
    char* p = (char*)this;
    if (*(char*)(p + 0x25) != 0) {
        void* tray = *(void**)(p + 0x20);
        ((FN2_ii)((*(void***)tray)[10]))(tray, 1, 1);
        CString s(0xf3108302, (void*)0x07a24898, 0);
        tray = *(void**)(p + 0x20);
        const char* t = s.GetText(-1, 1);
        void* r = ((FN1_p)((*(void***)tray)[4]))(tray, (void*)t);
        SetTooltipText(r);
        AnchorWindowToWindow(*(void**)(p + 0xc), *(void**)(p + 0x14), 0x18, 0);
        *(char*)(p + 0x25) = 0;
        s.~CString();
    }
}

// @ 0x00ef7b00
void CScenarioTutorialsChecklistUI::sub_ef7b00()
{
    char* p = (char*)this;
    void* w = *(void**)(p + 0x14);
    void* r = ((FN2_pi)((*(void***)w)[0x3c]))(w, (void*)0x07a27050, 1);
    if (r != 0)
        ((FN2_ii)((*(void***)r)[0x1f]))(r, 2, 1);
    w = *(void**)(p + 0x1c);
    ((FN2_ii)((*(void***)w)[0x1f]))(w, 1, 1);
}

// @ 0x00ef7b40
void CScenarioTutorialsChecklistUI::sub_ef7b40()
{
    char* p = (char*)this;
    int id = *(int*)(p + 0x34);
    if (id == -1)
        return;
    CSPUILayout* L = *(CSPUILayout**)(p + 0x10);
    void* w = L->FindWindowByID(id + 1000, 1);
    w = ((FN0_p)((*(void***)w)[4]))(w);
    ((FN2_ii)((*(void***)w)[0x1f]))(w, 2, 0);
    ((CDirectPropertyList*)g_16c7b60)->SetBoolProperty();
    g_15acef0 = -1;
    *(int*)(p + 0x34) = -1;
}

// @ 0x00ef7c00
void CHash::DoRehash(uint32_t n)
{
    char* self = (char*)this;
    void* buckets = AllocBuckets(n);
    uint32_t i = 0;
    while (i < *(uint32_t*)(self + 8)) {
        void** p = (void**)(*(char**)(self + 4) + i * 4);
        while (*p != 0) {
            void* node = *p;
            uint32_t h = *(uint32_t*)node;
            *p = *(void**)((char*)node + 4);
            uint32_t idx = h % n;
            *(void**)((char*)node + 4) = *(void**)((char*)buckets + idx * 4);
            *(void**)((char*)buckets + idx * 4) = node;
            p = (void**)(*(char**)(self + 4) + i * 4);
        }
        i++;
    }
    void* old = *(void**)(self + 4);
    if (*(uint32_t*)(self + 8) > 1 && old != *(void**)(self + 0x30)) {
        if (old >= *(void**)(self + 0x24) && old < *(void**)(self + 0x28)) {
            *(void**)old = *(void**)(self + 0x1c);
            *(void**)(self + 0x1c) = old;
            *(void**)(self + 4) = buckets;
            *(uint32_t*)(self + 8) = n;
            return;
        }
        FreeNode(old);
    }
    *(void**)(self + 4) = buckets;
    *(uint32_t*)(self + 8) = n;
}

// @ 0x00ef7ca0
int __cdecl FUN_00ef7ca0(int a0, int* a1, int a2)
{
    int n = 0;
    while (a0 != a2) {
        a0 = *(int*)(a0 + 4);
        while (a0 == 0) {
            a1++;
            a0 = *a1;
        }
        n++;
    }
    return n;
}

// @ 0x00ef7ce0
void __fastcall FUN_00ef7ce0(char* p)
{
    if (*(int*)(p + 4) == -1)
        return;
    Simulator_s00ef_6db0* sim = gSimulator;
    CSpaceSim* sg = *(CSpaceSim**)((char*)sim + 0x14);
    void* r = sg->f_ed4b50(*(int*)(p + 4));
    ((CScenarioTutorialsChecklistUI*)r)->sub_ef7a00();
}

// @ 0x00ef7d00
void __cdecl FUN_00ef7d00()
{
    void* prefs = gAppPreferences;
    char flag = 1;
    int64_t v;
    v = 2;
    EA_Variant_SetBool(&v, &flag);
    ((FN2_ip)((*(void***)prefs)[5]))(prefs, 0x7be69ad, &v);
    void* area = SP_GetSaveArea(0x11ac192, 0);
    SP_SaveResource(prefs, area);
    void* gt = SP_GameTimeManager();
    ((FN1_i)((*(void***)gt)[0x10]))(gt, 0x4bf38a7);
    if (((uint8_t*)&v)[8] & 4)
        EA_Variant_Destruct(&v, 0);
}

// @ 0x00ef7d90
void FUN_00ef7d90()
{
    void* prefs = *(void**)&g_appPrefs;
    void* cm = *(void**)((char*)&g_simMgr);  // ConfigManager(); placeholder
    (void)cm;
    int present = 0;
    char old = 0;
    if (prefs) {
        int* prop = 0;
        if (((VObj*)prefs)->s3(0x7d1fe81) != 0) {
            (void)prefs;
        }
        (void)prop;
    }
    if (present && old == 0)
        ;
}

// @ 0x00ef7ec0
void FUN_00ef7ec0(int param_1)
{
    (void)param_1;  // large key dispatcher; see decompile (partial)
}

// @ 0x00ef8390
void FUN_00ef8390(int param_1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    (void)param_1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7;
}

// @ 0x00ef8440
bool FUN_00ef8440()
{
    void* g = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x14);
    g = *(void**)((char*)g + 0x14);
    void* x = 0;
    if (g) {
        void* p1 = ((Stub*)g)->GetPlayerInventory(0, 0, 0);
        void* p2 = ((Stub*)p1)->FUN_005cae30();
        void* p3 = ((Stub*)p2)->FUN_005c2e50();
        void* p4 = ((Stub*)p3)->FUN_005cae30();
        if (p4)
            x = ((VObj*)((char*)p4 + 0xc))->s3(0x722de63);
    }
    void* holder = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x74);
    return ((Stub*)holder)->FUN_00f3e8a0(((Stub*)x)->GetAllocator()) == 0;
}

// @ 0x00ef84b0
bool CEditor_s00ef_7d90::FUN_00ef84b0()
{
    void* g = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x14);
    g = *(void**)((char*)g + 0x14);
    void* x = 0;
    if (g) {
        int idx = *(int*)((char*)this + 0x44);
        if (idx == -1)
            idx = 5;
        void* p1 = ((Stub*)g)->GetPlayerInventory(0, 0, idx);
        void* p2 = ((Stub*)p1)->FUN_005cae30();
        void* p3 = ((Stub*)p2)->FUN_005c2e50();
        void* p4 = ((Stub*)p3)->FUN_005cae30();
        if (p4)
            x = ((VObj*)((char*)p4 + 0xc))->s3(0x722de63);
    }
    void* holder = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x74);
    return ((Stub*)holder)->FUN_00f3e8a0(((Stub*)x)->GetAllocator()) == 0;
}

// @ 0x00ef8550
void CGadget::Toggle(int show)
{
    if ((char)show != 0) {
        if (((ConfigMgr*)SP_ConfigManager_s00ef_7d90())->HasProperty(0x4ea96cb) == 0)
            return;
    } else {
        releaseAll();
    }
    VObj* o = mpFlash;
    if (o)
        o->s31(1, show);
}

// @ 0x00ef8590
void FUN_00ef8590()
{
    if ((g_16c7b60_s00ef_7d90 | g_16c7b64) == 0)
        return;
    Qpc now;
    QueryPerformanceCounter(&now);
    if (g_deadline - now.q >= 0)
        return;
    ((Stub*)&g_16c7b60_s00ef_7d90)->SetBoolProperty();
    Stub* audio = ((SimManager*)*(void**)&g_simMgr)->mpAudio;
    Stub* r = (Stub*)audio->FUN_00ed4b50(g_15acef0);
    return r->ReleaseAll();
}

// @ 0x00ef8600
void CGadget::AudioToggle(int id)
{
    releaseAll();
    VObj* c = (VObj*)((VObj*)((Stub*)mpWindow)->FindWindowByID(id + 1000, 1))->s4();
    c->s31(2, 1);
    VObj* at = (VObj*)EA_Audio_GetSystemAT();
    void* u = at ? at->s8() : 0;
    VObj* at2 = (VObj*)EA_Audio_GetSystemAT();
    if (at2) {
        at2->s14(0x3475365);
        at2->s16(0x3475381, 0x738674d7);
        at2->s16(0x3475385, (unsigned)u);
        at2->s22(0);
    }
    ((Stub*)&g_16c7b60_s00ef_7d90)->SetTimeLimit(4, 1);
    g_15acef0 = m28;
    m34 = id;
}

// @ 0x00ef8770
void* FUN_00ef8770(int param_1, unsigned param_2, int* param_3)
{
    *(int*)(param_1 + 8) = 0;
    *(int*)(param_1 + 0xc) = 0;
    *(int*)(param_1 + 0x10) = 0x3f800000;
    *(int*)(param_1 + 0x14) = 0x40000000;
    *(int*)(param_1 + 0x18) = 0;
    int iVar1 = *param_3;
    *(int*)(param_1 + 0x1c) = 0;
    // eastl::fixed_pool_base::init(param_1+0x1c, iVar1, 0x80, 8, 4, 0)
    ((Stub*)((char*)&g_simMgr))->FUN_00ed4b50(iVar1);
    *(int*)(param_1 + 0x24) = iVar1;
    *(int*)(param_1 + 0x28) = iVar1 + 0x80;
    *(int*)(param_1 + 0x2c) = 8;
    *(int*)(param_1 + 0x30) = param_3[5];
    if (param_2 < 2) {
        *(int*)(param_1 + 0xc) = 0;
        *(int*)(param_1 + 0x18) = 0;
        *(int*)(param_1 + 8) = 1;
        *(int*)(param_1 + 4) = (int)0x154df28;
        return (void*)param_1;
    }
    unsigned v = (unsigned)((Stub*)0)->FUN_00ef7b90(0);
    *(int*)(param_1 + 8) = v;
    *(int*)(param_1 + 4) = (int)((Stub*)v)->FUN_00ef7b90((void*)(size_t)v);
    return (void*)param_1;
}

// @ 0x00ef8820
bool CEditor_s00ef_7d90::FUN_00ef8820(int param_2)
{
    int param_1 = (int)this;
    int local_8[2];
    ((Stub*)((char*)param_1 + 0x5c))->FUN_00a23ef0(local_8, &param_2);
    return local_8[0] != *(int*)(*(int*)(param_1 + 0x60) + *(int*)(param_1 + 0x64) * 4);
}

// @ 0x00ef8860
void CEditor_s00ef_7d90::FUN_00ef8860()
{
    int param_1 = (int)this;
    int iVar3 = *(int*)(param_1 + 0x30);
    if (iVar3 == -1)
        return;
    int iVar1 = *(int*)(param_1 + 0x34);
    if (iVar1 == -1)
        return;
    int* table = 0;
    if (iVar1 == 0)
        table = (int*)(0x148b450 + iVar3 * 0x10);
    else if (iVar1 == 1)
        table = (int*)(0x148b510 + iVar3 * 0x10);
    if (table) {
        int i = table[0];
        while (i <= table[1]) {
            ((Stub*)((char*)param_1 + 0x5c))->FUN_00a23d20(&i);
            ++i;
        }
        for (int k = 0; k != 0xad; ++k)
            ((Stub*)param_1)->FUN_00ef7ec0(k);
    }
    int o = (int)((Stub*)(*(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x14)))->FUN_00ed4b50(*(int*)(param_1 + 0x34));
    if (o) {
        void* sub = *(void**)(o + 0x1c);
        ((VObj*)sub)->s31(1, 0);
    }
    *(int*)(param_1 + 0x30) = -1;
    *(int*)(param_1 + 0x34) = -1;
    *(char*)(param_1 + 0x3b) = 0;
    *(char*)(param_1 + 0x3d) = 0;
    *(char*)(param_1 + 0x3e) = 0;
    *(char*)(param_1 + 0x3f) = 0;
    *(char*)(param_1 + 0x40) = 0;
    *(int*)(param_1 + 0x44) = -1;
    *(short*)(param_1 + 0x38) = 0;
    *(char*)(param_1 + 0x3a) = 0;
}

// @ 0x00ef8940
int CEditor_s00ef_7d90::FUN_00ef8940(int mode)
{
    int count = 0;
    if (mode == 0)
        count = 0xc;
    else if (mode == 1)
        count = 5;
    char* base = (char*)this + mode * 0x14c + 0x4a8;
    int stride = *(int*)(base + 8);
    int* buckets = (int*)*(int*)((char*)this + mode * 0x14c + 0x4ac);
    int* ref = (int*)buckets[stride];
    int diff = 0;
    for (int u = 0; u < count; ++u) {
        int* p = *(int**)((char*)buckets + (u % stride) * 4);
        int* found;
        while (p) {
            if (u == *p) {
                found = p;
                goto chk;
            }
            p = (int*)p[1];
        }
        found = *(int**)((char*)buckets + stride * 4);
    chk:
        if (found != ref)
            ++diff;
    }
    return diff;
}

// @ 0x00ef8a10
void FUN_00ef8a10(int param_1, unsigned param_2)
{
    switch (param_2) {
        case 0x19: ((Stub*)param_1)->FUN_00ef75b0(0, 0x1a, 0x1b); ((Stub*)param_1)->FUN_00ef7640(0, 1); break;
        case 0x27: *(char*)(param_1 + 0x38) = 1; *(char*)(param_1 + 0x3a) = 1; break;
        case 0x2b: ((Stub*)param_1)->FUN_00ef75b0(2, 0x2c, 0x2d); ((Stub*)param_1)->FUN_00ef7640(2, 1); break;
        case 0x31: ((Stub*)param_1)->FUN_00ef75b0(5, 0x32, 0x33); ((Stub*)param_1)->FUN_00ef7640(5, 1); break;
        case 0x3f: ((Stub*)param_1)->FUN_00ef75b0(0, 0x40, 0x41); ((Stub*)param_1)->FUN_00ef7640(0, 1); break;
        case 0x55: ((Stub*)param_1)->FUN_00ef75b0(1, 0x56, 0x57); ((Stub*)param_1)->FUN_00ef7640(1, 1); break;
        case 0x88: ((Stub*)param_1)->FUN_00ef7600(0, 0x89, 0x8a); ((Stub*)param_1)->FUN_00ef76a0(0, 1); break;
        case 0x8e: ((Stub*)param_1)->FUN_00ef7600(1, 0x8f, 0x90); ((Stub*)param_1)->FUN_00ef76a0(1, 1); break;
        case 0x9a: ((Stub*)param_1)->FUN_00ef7600(2, 0x9b, 0x9c); ((Stub*)param_1)->FUN_00ef76a0(2, 0); break;
        case 0x9e: ((Stub*)param_1)->FUN_00ef7600(3, 0x9f, 0xa0); ((Stub*)param_1)->FUN_00ef76a0(3, 0); break;
        case 0xa4: ((Stub*)param_1)->FUN_00ef7600(4, 0xa5, 0xa6); ((Stub*)param_1)->FUN_00ef76a0(4, 1); break;
        default: break;
    }
}

// @ 0x00ef8cc0
void FUN_00ef8cc0(int param_1, void* param_2, unsigned* param_3)
{
    (void)param_1; (void)param_2; (void)param_3;
}

// @ 0x00ef8dc0
void cScenarioTutorials::SavePrefs()
{
    mHandler.Remove();
    IPropertyList* props = gAppPreferences_s00ef_8dc0;
    int a = GetCompletedCount(0);
    Variant v1;
    v1 = a;
    props->SetProperty(0x7abf095, &v1);
    int b = GetCompletedCount(1);
    Variant v2;
    v2 = b;
    props->SetProperty(0x7abf09d, &v2);
    props = gAppPreferences_s00ef_8dc0;
    SaveResource(props, GetSaveArea(0x11ac192), 0);
}

// @ 0x00ef8ed0
void __stdcall FUN_00ef8ed0(bool enable)
{
    if (enable) {
        TutorialRoot* root = gTutorialApp->mpRoot;
        int state = root->GetState();
        if (state == 0) {
            cTutorialPage* page = gTutorialApp->mpRoot->GetPage(0);
            if (ConfigManager()->GetBool(0x4ea96cb) && page->mpWindow)
                page->mpWindow->SetFlag(1, true);
            cTutorialPage* page1 = gTutorialApp->mpRoot->GetPage(1);
            page1->FUN_00ef7b40();
            if (page1->mpWindow)
                page1->mpWindow->SetFlag(1, false);
        } else if (state == 2) {
            cTutorialPage* page = gTutorialApp->mpRoot->GetPage(0);
            page->FUN_00ef7b40();
            if (page->mpWindow)
                page->mpWindow->SetFlag(1, false);
            cTutorialPage* page1 = gTutorialApp->mpRoot->GetPage(1);
            if (ConfigManager()->GetBool(0x4ea96cb) && page1->mpWindow)
                page1->mpWindow->SetFlag(1, true);
        }
    } else {
        FUN_00ef8860();
        cTutorialPage* page = gTutorialApp->mpRoot->GetPage(0);
        page->FUN_00ef7b40();
        if (page->mpWindow)
            page->mpWindow->SetFlag(1, false);
        cTutorialPage* page1 = gTutorialApp->mpRoot->GetPage(1);
        page1->FUN_00ef7b40();
        if (page1->mpWindow)
            page1->mpWindow->SetFlag(1, false);
    }
}

// @ 0x00ef9000
void cTutorialPage::Rebuild()
{
    wchar_t completed[64];
    wchar_t total[64];
    SetNumberString(gTutorialApp->mpTutorials->GetCompletedCount(mMode), completed, 64);
    SetNumberString(mStepCount, total, 64);
    StringArg args[2];
    args[0].mKey = 0x6c7cf9;
    args[0].mValue = completed;
    args[1].mKey = 0xac24c978;
    args[1].mValue = total;
    cString_s00ef_8dc0 text(0xc49c0c72, 0x7735bdc, 0);
    FUN_0067de40_s00ef_8dc0()->GetLocalizer()->FormatString(&text, args, 2);
    mpWindowD->SetCaption(text.c_str());
}

// @ 0x00ef9290
void cTutorialPage::BuildList()
{
    if (mbBuilt)
        return;
    mpWindow = mpLayout->FindWindowByID(0x771f0a0, true);
    mpWindow->AddWinProc(this);
    mpWindowB = mpLayout->FindWindowByID(0x7a2a2d6, true);
    mpWindowB->SetFlag(1, false);
    IWindow_s00ef_8dc0* w = mpLayout->FindWindowByID(0x7732678, true);
    mpWindowC = w ? w->GetComponent(0x8ed27e7a) : 0;
    mpWindowD = mpLayout->FindWindowByID(0x771f2a8, true);
    Rebuild();

    IWindow_s00ef_8dc0* container = mpLayout->FindWindowByID(0x771f2c0, true);
    const Rect_s00ef_8dc0* cr = container->GetArea();
    float contW = cr->right - cr->left;
    float contH = cr->bottom - cr->top;
    float yAcc = 0.0f;
    for (int i = 0; i < gGroupCount[mMode]; ++i) {
        cSPUILayout_s00ef_8dc0 groupLayout;
        groupLayout.Init(gKeyGroup, false, 0x5b598fa);
        WindowRef groupWin = {0};
        groupWin = groupLayout.FindWindowByID(0x7b54408, true);
        IWindow_s00ef_8dc0* stepList = groupLayout.FindWindowByID(0x7b54370, true);
        IWindow_s00ef_8dc0* titleWin = groupLayout.FindWindowByID(0x7a6cfd8, true);
        uint32_t titleId = 0;
        if (mMode == 0)
            titleId = gGroupTitles0[i];
        else if (mMode == 1)
            titleId = gGroupTitles1[i];
        cString_s00ef_8dc0 title(0xc49c0c72, titleId, 0);
        titleWin->SetCaption(title.c_str());
        groupLayout.Shutdown(true);
        container->AddWindow(groupWin);
        {
            const Rect_s00ef_8dc0* r = groupWin->GetArea();
            groupWin->SetSize(contW, r->bottom - r->top);
        }
        const Rect_s00ef_8dc0* sr = stepList->GetArea();
        float subW = sr->right - sr->left;
        float subH = sr->bottom - sr->top;
        float yInner = 0.0f;
        for (int j = 0; j < mStepCount; ++j) {
            if (mMode == 0) {
                if (gStepInfo0[j].group != i)
                    continue;
            } else if (mMode == 1) {
                if (gStepInfo1[j].group != i)
                    continue;
            }
            cSPUILayout_s00ef_8dc0 stepLayout;
            stepLayout.Init(gKeyStep, false, 0x5b598fa);
            WindowRef stepWin = {0};
            stepWin = stepLayout.FindWindowByID(0x7731950, true);
            stepLayout.FindWindowByID(0x7732df0, true)->SetControlID(j + 1);
            stepLayout.FindWindowByID(0x7aa9b70, true)->SetControlID(j + 0x64);
            stepLayout.FindWindowByID(0x7757900, true)->SetControlID(j + 0x3e8);
            IWindow_s00ef_8dc0* captionWin = stepLayout.FindWindowByID(0x7733e00, true);
            uint32_t stepId = 0;
            if (mMode == 0)
                stepId = gStepInfo0[j].strId;
            else if (mMode == 1)
                stepId = gStepInfo1[j].strId;
            cString_s00ef_8dc0 stepText(0xc49c0c72, stepId, 0);
            captionWin->SetCaption(stepText.c_str());
            stepLayout.Shutdown(true);
            stepList->AddWindow(stepWin);
            const Rect_s00ef_8dc0* r = stepWin->GetArea();
            Rect_s00ef_8dc0 rc;
            rc.left = 0.0f;
            rc.top = yInner;
            rc.right = subW;
            rc.bottom = (r->bottom - r->top) + yInner;
            stepWin->SetArea(&rc);
            yInner = rc.bottom;
        }
        const Rect_s00ef_8dc0* gr = groupWin->GetArea();
        Rect_s00ef_8dc0 rc2;
        rc2.left = 0.0f;
        rc2.top = yAcc;
        rc2.right = contW;
        rc2.bottom = (((gr->bottom - gr->top) - subH) + yInner) + yAcc;
        groupWin->SetArea(&rc2);
        yAcc = rc2.bottom;
    }
    const Rect_s00ef_8dc0* lr = mpWindow->GetArea();
    float newH = ((lr->bottom - lr->top) - contH) + yAcc;
    mpWindow->SetSize(lr->right - lr->left, newH);
    mbBuilt = true;
}

// @ 0x00ef9830
void FUN_00ef9830(void* param_1, int param_2, char param_3)
{
    if (param_3 != 0) {
        ((Stub_s00ef_8dc0*)param_1)->FUN_00ef9290();
        return;
    }
    void* esi = param_1;
    if (*(char*)((char*)esi + 0x24) == 0)
        return;
    void* o = *(void**)((char*)esi + 0x14);
    if (o) {
        void* vt = *(void**)o;
        ((void(__thiscall*)(void*, void*)) * ((void**)vt + 0x42))(o, esi);
        o = *(void**)((char*)esi + 0x14);
        if (o) {
            *(void**)((char*)esi + 0x14) = 0;
            vt = *(void**)o;
            ((void(__thiscall*)(void*)) * ((void**)vt + 1))(o);
        }
    }
    *(char*)((char*)esi + 0x24) = 0;
}

// @ 0x00ef9880
StepSetBig::StepSetBig(const HashFn& h, const EqFn& e)
{
    {
        eastl::fixed_hashtable_allocator a;
        a.mPool.mpHead = 0;
        a.mPool.init(mNodes, 0x200, 8, 4, 0);
        a.mPool.mpPoolBegin = mNodes;
        a.mPool.mpPoolEnd = mNodes + 0x200;
        a.mPool.mnNodeSize = 8;
        a.mpBucketBuffer = mBuckets;
        uint32_t nBuckets = eastl::GetPrevBucketCountOnly(0x41);
        HashSetCtor(nBuckets, h, e, a);
    }
    set_max_load_factor(10000.0f);
}

// @ 0x00ef9950
StepSetSmall::StepSetSmall(const HashFn& h, const EqFn& e)
{
    {
        eastl::fixed_hashtable_allocator a;
        a.mPool.mpHead = 0;
        a.mPool.init(mNodes, 0x80, 8, 4, 0);
        a.mPool.mpPoolBegin = mNodes;
        a.mPool.mpPoolEnd = mNodes + 0x80;
        a.mPool.mnNodeSize = 8;
        a.mpBucketBuffer = mBuckets;
        uint32_t nBuckets = eastl::GetPrevBucketCountOnly(0x11);
        HashSetCtor(nBuckets, h, e, a);
    }
    set_max_load_factor(10000.0f);
}

// @ 0x00ef9af0
void cScenarioTutorials::OnStepDone(int step)
{
    int stepKey = step;
    mSeenSteps.DoInsertValue(stepKey, eastl::true_type());
    cTutorialPage* page = gTutorialApp->mpRoot->GetPage(mCurLesson);
    int count = 0;
    if (mCurLesson == 0)
        count = 12;
    else if (mCurLesson == 1)
        count = 5;
    for (int i = 0; i < count; ++i) {
        const StepInfo* info = 0;
        if (mCurLesson == 0)
            info = &gStepInfo0[i];
        else if (mCurLesson == 1)
            info = &gStepInfo1[i];
        int lo = info->lo;
        int hi = info->hi;
        if (step < lo || step > hi)
            continue;
        for (int k = lo; k <= hi; ++k) {
            if (mSeenSteps.find(k) == mSeenSteps.end())
                return;
        }
        int group = i;
        mGroups[mCurLesson].DoInsertValue(group, eastl::true_type());
        IWindow_s00ef_8dc0* row = page->mpLayout->FindWindowByID(0x3e8 + i, true);
        IWindow_s00ef_8dc0* mark = row ? row->GetComponent(0x8ed27e7a) : 0;
        mark->SetStateFlag(4, true);
        page->Rebuild();
        page->UpdateGroup(i);
        if (i + 1 < page->mStepCount)
            page->mpWindow->GetChildByID(i + 1 + 0x64, true)->SetFlag(1, false);
        page->mpWindowB->SetFlag(1, false);
        FUN_00ef7a00(page);
        mCurStep = -1;
        mCurLesson = -1;
        mField44 = -1;
        mFlag3b = 0;
        mFlag3d = 0;
        mFlag3e = 0;
        mFlag3f = 0;
        mFlag40 = 0;
        *(uint16_t*)&pad38[0] = 0;
        pad38[2] = 0;
        return;
    }
}

// @ 0x00ef9d00
void cTutorialPage::CreateLayout()
{
    cSPUILayout_s00ef_8dc0* layout = new ("UI", 0, 0, 0, 0) cSPUILayout_s00ef_8dc0();
    cSPUILayout_s00ef_8dc0* old = mpLayout;
    if (layout != old) {
        if (layout)
            layout->AddRef();
        mpLayout = layout;
        if (old)
            old->Release();
    }
    mpLayout->Init(gKeyPage, false, 0x5b598fa);
    mpLayout->SetParentWin(mpParentWin, true, 0x5b598fa);
    mpLayout->SetReloadCallback(FUN_00ef9830, this);
    BuildList();
}

// @ 0x00ef9d90
cScenarioTutorials::cScenarioTutorials()
: mTimer(5, false),
      mCurStep(-1), mCurLesson(-1),
      mFlag3b(0), mFlag3c(0), mFlag3d(0), mFlag3e(0), mFlag3f(0), mFlag40(0),
      mField44(-1)
{
}

// @ 0x00ef9e40
void cScenarioTutorials_s00ef_9e40::Reset()
{
    *(uint16_t*)&mCurrentBits[0] = 0;
    mCurrentBits[2] = 0;

    StepGroup_s00ef_9e40* group = mGroups;
    int n = 2;
    do {
        StepGroup_s00ef_9e40 temp;
        group->mSet = temp.mSet;
        group = (StepGroup_s00ef_9e40*)((char*)group + 0x14c);
    } while (--n != 0);

    void* ms = SP_MessageServer();
    mHandler.mpServer = ms;
    mHandler.mpOwner = this;
    mHandler.mpNames = g_msgNames;
    mHandler.mnCount = 0xb;
    mHandler.mField10 = 0;
    if (ms != 0 && this != 0) {
        for (uint32_t i = 0; i < 0xb; ++i)
            ((MessageServer*)ms)->Register(this, g_msgNames[i]);
    }

    int counts[2] = { 0, 0 };
    IPropertyList_s00ef_9e40* prefs = (IPropertyList_s00ef_9e40*)g_AppPreferences;
    if (prefs != 0) {
        EA_Variant* value;
        if (prefs->GetProperty(0x7abf095, &value) && value->mTypeId == 10) {
            if (value->mFlags & 0x30)
                value = *(EA_Variant**)value;
            counts[0] = *(int*)value;
        }
        if (prefs->GetProperty(0x7abf09d, &value) && value->mTypeId == 10) {
            if (value->mFlags & 0x30)
                value = *(EA_Variant**)value;
            counts[1] = *(int*)value;
        }
    }

    group = mGroups;
    int i = 0;
    do {
        int count = counts[i];
        g_16c7b50[i] = (count != 0);
        if (count > 0) {
            int k = 0;
            do {
                group->mSet.DoInsertValue(k, true_type_s00ef_9e40());
                k += 1;
            } while (k < count);
        }
        i += 1;
        group = (StepGroup_s00ef_9e40*)((char*)group + 0x14c);
    } while (i < 2);
}

// @ 0x00efa040
void cScenarioTutorials_s00ef_9e40::UpdateAll()
{
    char* self = (char*)this;
    int idx = *(int*)(self + 0x30);
    if (idx == -1)
        return;
    int sel = *(int*)(self + 0x34);
    int* p;
    if (sel == 0) {
        p = (int*)((char*)g_catTableA + idx * 0x10);
    } else if (sel == 1) {
        p = (int*)((char*)g_catTableB + idx * 0x10);
    }
    int i = 0;
    do {
        ((CatUpdate*)self)->f(i);
        i++;
    } while (i != 0xad);
    int e = p[0];
    if (e <= p[1]) {
        do {
            ((EntryUpdate*)self)->f(e);
            e++;
        } while (e <= p[1]);
    }
}

// @ 0x00efa0b0
void cScenarioTutorials_s00ef_9e40::SetCategoryState(int category, char flag)
{
    char* self = (char*)this;
    ((InputFwd*)self)->f(category);
    ((CatUpdate*)self)->f(category);
    unsigned state = ((CatState*)self)->f(category);
    if (state > 0) {
        ((Stopwatch_s00ef_9e40*)(self + 0x10))->SetTimeLimit(state, 1);
        *(uint8_t*)(self + 0x3b) = 1;
    }
    ((EntryUpdate*)self)->f(category);
    if (((CatValid*)self)->f(category) && *(int*)(self + 0x30) != -1 && flag != 0) {
        RefreshChecklist();
    }
}

// @ 0x00efa110
void cScenarioTutorials_s00ef_9e40::HandleCategoryMessage(int category, int arg)
{
    char* self = (char*)this;
    int local;
    int k = category;
    ((HashFind*)(self + 0x5c))->find(&local, &k);
    if (local == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 0x64) * 4)) {
        ((InputFwd*)self)->f(category);
        ((CatUpdate*)self)->f(category);
        unsigned state = ((CatState*)self)->f(category);
        if (state > 0) {
            ((Stopwatch_s00ef_9e40*)(self + 0x10))->SetTimeLimit(state, 1);
            *(uint8_t*)(self + 0x3b) = 1;
        }
        ((EntryUpdate*)self)->f(category);
    }
    if (*(uint8_t*)(self + 0x40) == 0) {
        ((Mgr830*)SP_GetSomeMgr())->f(arg);
    }
}

// @ 0x00efb4e0
void CUI::f_efb4e0()
{
    switch (mCategory30) {
    case 4:
        if (!f_ef8820(0xa4)) { f_ef8390(gVecBase[9], 0xa4, 0, 0); return; }
        if (!f_ef8820(0xa6)) { f_efa0b0(0xa5, 0); return; }
        if (!f_ef8820(0xa7)) { f_ef8390(gVecBase[10], 0xa7, 0, 0); return; }
        if (!f_ef8820(0xa9)) { f_efa0b0(0xa8, 0); return; }
        if (!f_ef8820(0xab)) { f_efa110(0xaa, 0x218e06f7); return; }
        if (!f_ef8820(0xac)) { f_efa110(0xac, 0x55f3a99b); return; }
        break;

    case 0:
        if (!f_ef8820(0x87)) { f_ef8390(gVecBase[0], 0x87, 0, 0); return; }
        if (!f_ef8820(0x88)) { f_ef8390(gVecBase[1], 0x88, 0, 0); return; }
        if (!f_ef8820(0x8a)) { f_efa0b0(0x89, 0); return; }
        if (!f_ef8820(0x8b)) { f_ef8390(gVecBase[2], 0x8b, 0, 0); return; }
        if (!f_ef8820(0x8d)) { f_efa110(0x8c, 0x4f8dbb28); return; }
        break;

    case 1:
        if (!f_ef8820(0x8e)) { f_ef8390(gVecBase[3], 0x8e, 0, 0); return; }
        if (!f_ef8820(0x90)) { f_efa0b0(0x8f, 0); return; }
        if (!f_ef8820(0x91)) { f_ef8390(gVecBase[4], 0x91, 0, 0); return; }
        if (!f_ef8820(0x93)) { f_efa110(0x92, 0x624e5aa); return; }
        if (!f_ef8820(0x95)) { f_efa110(0x94, 0x5f3e51b0); return; }
        if (!f_ef8820(0x97)) { f_efa110(0x96, 0xcacb7102); return; }
        if (!f_ef8820(0x98)) { f_ef8390(gVecBase[5], 0x98, 0, 0); return; }
        if (!f_ef8820(0x99)) { f_efa110(0x99, 0x50a2f4e4); return; }
        break;

    case 3:
        if (!f_ef8820(0x9e)) { f_ef8390(gVecBase[6], 0x9e, 0, 0); return; }
        if (!f_ef8820(0xa0)) { f_efa0b0(0x9f, 0); return; }
        if (!f_ef8820(0xa2)) { f_efa110(0xa1, 0xccbe21d); return; }
        if (!f_ef8820(0xa3)) { f_ef8390(gVecBase[7], 0xa3, 0, 0); return; }
        break;

    case 2:
        if (!f_ef8820(0x9a)) { f_ef8390(gVecBase[8], 0x9a, 0, 0); return; }
        if (!f_ef8820(0x9c)) { f_efa0b0(0x9b, 0); return; }
        if (!f_ef8820(0x9d)) { f_efa110(0x9d, 0x56221c05); return; }
        break;
    }
}

// @ 0x00efb9c0
void CUI::f_efb9c0(int param_2, int param_3)
{
    char* self = (char*)this;
    void* old = *(void**)(self + 0xc);
    if ((void*)param_2 != old) {
        if (param_2 != 0)
            ((FN0_p)((*(void***)param_2)[0]))((void*)param_2);
        *(int*)(self + 0xc) = param_2;
        if (old != 0)
            ((FN0_p)((*(void***)old)[1]))(old);
    }
    bool bVar8 = true;
    *(int*)(self + 0x28) = param_3;
    if (param_3 == 0) {
        *(int*)(self + 0x2c) = 0;
        *(int*)(self + 0x30) = 0xc;
        void* cm = SP_ConfigManager_s00ef_b4e0();
        if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0)
            bVar8 = false;
    } else if (param_3 == 1) {
        *(int*)(self + 0x2c) = 2;
        *(int*)(self + 0x30) = 5;
        bVar8 = false;
    }
    f_ef9d00();
    f_ef7a80();
    if (bVar8) {
        void* cm = SP_ConfigManager_s00ef_b4e0();
        if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0)
            goto afterWindow;
    } else {
        f_ef7b40();
    }
    if (*(void**)(self + 0x14) != 0)
        ((FN2_ii)((*(void***)*(void**)(self + 0x14))[0x1f]))(*(void**)(self + 0x14), 1, bVar8 ? 1 : 0);
afterWindow:
    if (*(int*)(self + 0x30) > 0) {
        void* w = ((FN2_pii)((*(void***)*(void**)(self + 0x14))[0x3c]))(*(void**)(self + 0x14), 100, 1);
        ((FN2_ii)((*(void***)w)[0x1f]))(w, 1, 0);
    }
    for (int i = 1; i < *(int*)(self + 0x30); i++) {
        void* w = ((FN2_pii)((*(void***)*(void**)(self + 0x14))[0x3c]))(*(void**)(self + 0x14), i + 100, 1);
        ((FN2_ii)((*(void***)w)[0x1f]))(w, 1, 1);
    }
    for (int k = 0; k < *(int*)(self + 0x30); k++) {
        char* tutorials = *(char**)((char*)gSimulator_s00ef_b4e0 + 0xd4);
        char* page = tutorials + *(int*)(self + 0x28) * 0x14c;
        MapIter it = HashFind_s00ef_b4e0(page + 0x4a8, k);
        bool changed = it.first != *(void**)(*(int*)(tutorials + 0x60) + *(int*)(tutorials + 100) * 4);
        void* w = ((cSPUILayout_s00ef_b4e0*)*(void**)(self + 0x10))->FindWindowByID(k + 1000, 1);
        void* target = 0;
        if (w != 0)
            target = ((FN1_pi_s00ef_b4e0)((*(void***)w)[3]))(w, 0x8ed27e7a);
        ((FN2_ii)((*(void***)target)[10]))(target, 4, changed ? 1 : 0);
        f_ef9000();
        if (changed && k + 1 < *(int*)(self + 0x30)) {
            void* w2 = ((FN2_pii)((*(void***)*(void**)(self + 0x14))[0x3c]))(*(void**)(self + 0x14), k + 101, 1);
            ((FN2_ii)((*(void***)w2)[0x1f]))(w2, 1, 0);
        }
    }
    (void)self;
}

// @ 0x00efbbe0
void CUI::f_efbbe0(int param_2, int param_3)
{
    char* self = (char*)this;
    int local[2];
    int a2 = param_2;
    ((CMap*)(self + 0x5c))->f_00a23ef0(local, &a2);
    if (local[0] != *(int*)(*(int*)(self + 0x60) + *(int*)(self + 100) * 4)) {
        int a3 = param_3;
        ((CMap*)(self + 0x5c))->f_00a23ef0(local, &a3);
        if (local[0] == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 100) * 4)) {
            f_ef8a10(param_3);
            f_ef7ec0(param_3);
            unsigned int st = f_ef7330(param_3);
            if (st > 0) {
                ((CLimit*)(self + 0x10))->SetTimeLimit(st, 1);
                *(uint8_t*)(self + 0x3b) = 1;
            }
            f_ef9af0(param_3);
            if (f_ef72d0(param_3)) {
                if (*(int*)(self + 0x30) != -1)
                    f_efbce0();
            }
        }
    }
}

// @ 0x00efbc90
void CUI::f_efbc90(int param_2, int param_3)
{
    char* self = (char*)this;
    int local[2];
    int key = param_2;
    ((CMap*)(self + 0x5c))->f_00a23ef0(local, &key);
    if (local[0] == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 100) * 4))
        f_efa0b0(key, param_3);
}

// @ 0x00efbce0
void CUI::f_efbce0()
{
    char* self = (char*)this;
    bool b = false;
    void* cm = SP_ConfigManager_s00ef_b4e0();
    if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) != 0 &&
        *(int*)(self + 0x30) != -1 && *(int*)(self + 0x34) != -1) {
        if (!f_ef76f0()) {
            *(uint8_t*)(self + 0x3e) = 1;
            return;
        }
        *(uint16_t*)(self + 0x38) = 0;
        *(uint8_t*)(self + 0x3a) = 0;
        if (*(char*)(self + 0x3b) != 0) {
            FUN_00efcae0();
            float a, c2;
            FUN_00804ed0(&a, &c2);
            char* sim = (char*)gSimulator_s00ef_b4e0;
            ((void (__thiscall*)(void*, int, int, float, float))(*(void***)sim)[0xc])(sim, 1000, 8, a, a); (void)c2;
            ((void (__thiscall*)(void*, int, int, float, float))(*(void***)sim)[0xc])(sim, 0x3ea, 0x20, a, a);
            ((void (__thiscall*)(void*, int, int, float, float))(*(void***)sim)[0xc])(sim, 0x3e9, 0x10, a, a);
            ((FN2_ii)((*(void***)sim)[10]))(sim, 0x10, 0);
            *(uint8_t*)(self + 0x3b) = 0;
        }
        int m = *(int*)(self + 0x34);
        if (m == 0) {
            f_efa1b0();
        } else if (m == 1) {
            f_efb4e0();
        }
    }
    (void)b;
}

// @ 0x00efbdf0
void CUI::f_efbdf0()
{
    char* self = (char*)this;
    Simulator_s00ef_b4e0* sim = gSimulator_s00ef_b4e0;
    if (sim == 0)
        return;
    char* d4 = *(char**)((char*)sim + 0xd4);
    if (d4 == 0)
        return;
    CSpace* sp = *(CSpace**)((char*)sim + 0x14);
    void* r = sp->f_00ed4b50(*(int*)(d4 + 0x34));
    ((CUI*)r)->f_ef7b00();
    int x = *(int*)(self + 4);
    if (x == 0)
        return;
    ((CUI*)*(void**)((char*)sim + 0xd4))->f_efbc90(x, 1);
}

// @ 0x00efbe40
void CUI::f_efbe40(int param_2, int param_3)
{
    char* self = (char*)this;
    void* cm = SP_ConfigManager_s00ef_b4e0();
    if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0)
        return;
    f_ef8860();
    (void)param_3;
    int* table;
    if (param_3 == 0)
        table = (int*)((char*)0x0148b450 + param_2 * 0x10);
    else if (param_3 == 1)
        table = (int*)((char*)0x0148b510 + param_2 * 0x10);
    else
        table = 0;
    if (table != 0) {
        int lo = table[0];
        int hi = table[1];
        for (int i = lo; i <= hi; i++) {
            int v = i;
            ((CMap*)(self + 0x5c))->f_00a23d20(&v);
        }
    }
    *(int*)(self + 0x34) = param_3;
    *(int*)(self + 0x30) = param_2;
    SetBoolProperty(self + 0x10);
    char* sim = (char*)gSimulator_s00ef_b4e0;
    CSpace* sp = *(CSpace**)(sim + 0x14);
    void* r = sp->f_00ed4b50(0);
    (void)r;
}

// @ 0x00efbf00
void CUI::f_efbf00()
{
    char* self = (char*)this;
    FUN_0067cac0();
    cUIHints_Update();
    void* cm = SP_ConfigManager_s00ef_b4e0();
    if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) != 0) {
        if (*(int*)(self + 0x10) != 0 || *(int*)(self + 0x14) != 0) {
            if (LimitStopwatch_IsTimeUp(self + 0x10)) {
                SetBoolProperty(self + 0x10);
                f_efbce0();
            }
        }
        if (*(char*)(self + 0x3e) != 0) {
            *(uint8_t*)(self + 0x3e) = 0;
            f_efbce0();
        }
    }
}

// @ 0x00efc120
bool CUI::f_efc120(int param_2, int param_3)
{
    char* self = (char*)this;
    char* sim = (char*)gSimulator_s00ef_b4e0;
    CSpace* sp = *(CSpace**)(sim + 0x14);
    int r = (int)sp->f_00985e40();
    if (r != *(int*)(self + 0x2c))
        return false;
    if (*(int*)(param_3 + 8) != 0x287259f6)
        return false;
    int id = *(int*)(param_3 + 0xc);
    if (id == 0x7732678) {
        if (*(char*)(self + 0x25) != 0) {
            f_ef7a80();
            void* at = EA_GetSystemAT();
            int v = 0;
            if (at != 0)
                v = ((FN0_i)((*(void***)at)[8]))(at);
            SP_KillSetiEffects(0xcc089e57, v);
        } else {
            f_ef7a00();
            void* at = EA_GetSystemAT();
            int v = 0;
            if (at != 0)
                v = ((FN0_i)((*(void***)at)[8]))(at);
            SP_KillSetiEffects(0x6e649e21, v);
        }
        return false;
    }
    if (id == 0x7a27050) {
        void* cm = SP_ConfigManager_s00ef_b4e0();
        ((FN2_ii)((*(void***)cm)[0xb]))(cm, 0x4ea96cb, 0);
        char* d4 = *(char**)(sim + 0xd4);
        ((CUI*)d4)->f_ef8ed0(0);
        FUN_0067cac0();
        FUN_0067c830(0xe56e9897);
        return false;
    }
    if (id == 0x7a291ce) {
        char* d4 = *(char**)(sim + 0xd4);
        ((CUI*)d4)->f_efa040();
        return false;
    }
    {
        int a = id - 1;
        int b = *(int*)(self + 0x28);
        char* d4 = *(char**)(sim + 0xd4);
        ((CUI*)d4)->f_efbe40(a, b);
    }
    return false;
}

// @ 0x00efc4c0
float __fastcall FUN_00efc4c0(char* self, int pad)
{
    (void)pad;
    if (*(float*)(self + 0x178) > *(float*)(self + 0x174))
        return (*(float*)(self + 0x17c) - *(float*)(self + 0x174)) /
               (*(float*)(self + 0x178) - *(float*)(self + 0x174));
    return g_1485720;
}

// @ 0x00efc520
int __cdecl FUN_00efc520()
{
    if (g_016c7b88 != 0)
        return *(int*)g_016c7b88;
    return 0;
}

// @ 0x00efc530
bool __cdecl FUN_00efc530(int* p)
{
    if (p != 0) {
        int t = ((FN0_i)((*(void***)p)[0xe]))(p);
        if (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a || t == 0x7a81824 || t == 0x7abdd8d)
            return true;
    }
    return false;
}

// @ 0x00efc570
bool __cdecl FUN_00efc570(void* a, void* self2, float f)
{
    char* esi;
    if (a == 0)
        return true;
    esi = (char*)a - 8;
    if (esi == 0)
        return true;
    if (*(int*)(esi + 0xd4) == 0)
        return true;
    float xmm0 = *(float*)(*(char**)((char*)g_15fd918_s00ef_c270 + 0x3c) + 0x9c) * f;
    float xmm1;
    if (self2 != 0)
        xmm1 = ((PF_t)((*(void***)self2)[0xd]))(self2);
    else
        xmm1 = *(float*)(esi + 0x20);
    unsigned char idx = *(unsigned char*)(esi + 0x129);
    char* tbl = *(char**)(esi + 0xd4);
    return (xmm0 / xmm1) < *(float*)(tbl + idx * 4 - 4);
}

// @ 0x00efc5f0
int __cdecl FUN_00efc5f0(void* a, float f)
{
    if (g_15ad33c > f)
        return 0;
    float xmm0;
    void* v = FUN_00eeca30(a);
    if (v != 0)
        xmm0 = ((PF_t)((*(void***)v)[0x1c]))(v);
    else
        xmm0 = g_1485720;
    float xmm1 = g_15ad29c / f * xmm0;
    return g_15ad338 > xmm1;
}

// @ 0x00efc660
bool __fastcall FUN_00efc660(char* p, int pad, int a)
{
    if (a == 0)
        return false;
    char* o = (char*)FUN_00b18e00_s00ef_c270((void*)a);
    if (o == 0 || *(char*)(o + 0x6e) != 0)
        return false;
    char r = (char)FUN_00f40ea0(*(void**)(p + 8), a);
    if (r == 0) {
        void* ms = SP_MessageServer();
        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x78c406b, 0);
    }
    return r != 0;
}

// @ 0x00efc6c0
void __fastcall FUN_00efc6c0(char* p, int pad, int v)
{
    int* q = *(int**)(p + 0xc);
    if (q != 0 && *q == v)
        *q = -1;
}

// @ 0x00efc6e0
int __stdcall FUN_00efc6e0(void* arg)
{
    char bl = 0;
    void* esi = arg;
    int matched = 0;
    if (esi != 0) {
        int t = ((FN0_i)((*(void***)esi)[0xe]))(esi);
        if (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a ||
            t == 0x7a81824 || t == 0x7abdd8d)
            matched = 1;
    }
    if (!matched) {
        void* v = FUN_00eebf80(esi);
        if (v != 0) {
            char b1 = 0, b2 = 0;
            FUN_00eec8e0(v, &b2, &b1);
            bl = (b1 != 0 || b2 != 0);
        }
    }
    unsigned ecx = *(unsigned*)((char*)gSimulator_s00ef_c270 + 0x40);
    int eax = 1;
    if (bl) {
        if (1 & (ecx >> 1))
            eax = 2;
        else if (1 & ecx)
            eax = 3;
    }
    char* g = (char*)g_016c7b88;
    if (*(int*)(g + 0x68) != eax) {
        *(char*)(g + 0x64) = 1;
        *(int*)((char*)g_016c7b88 + 0x68) = eax;
    }
    return eax;
}

// @ 0x00efc7a0
bool __fastcall FUN_00efc7a0(char* p)
{
    if (*(char*)(p + 5) != 0) {
        ((TutorialsTarget*)*(void**)(p + 8))->SetFlag(1);
        ((TutorialsTarget*)*(void**)(p + 8))->Release();
        *(char*)(p + 5) = 0;
    }
    return true;
}

// @ 0x00efc7d0
bool __fastcall FUN_00efc7d0(char* p, int pad, int a, int b)
{
    char* o = (char*)FUN_00b18e00_s00ef_c270((void*)a);
    if (o != 0 && *(char*)(o + 0x6e) != 0)
        return false;
    bool r = ((TutorialsTarget*)*(void**)(p + 8))->Add(b);
    if (!r) {
        void* ms = SP_MessageServer();
        ((FN3_iii)((*(void***)ms)[5]))(ms, 0x78c406b, 0, 0);
    }
    return r;
}

// @ 0x00efc850
void __cdecl FUN_00efc850()
{
    char* sim = (char*)gSimulator_s00ef_c270;
    char* o = *(char**)(sim + 0x18);
    ((TutorialsTarget*)o)->Update();
}

// @ 0x00efc860
void __cdecl FUN_00efc860()
{
    if (*(int*)((char*)g_016c7b88 + 0xc) != 0) {
        void* im = SP_GameInputManager();
        ((FN2_ii)((*(void***)im)[0x19]))(im, 0x96b6b02c, 1);
    }
}

// @ 0x00efc890
void __cdecl FUN_00efc890()
{
    char* g = (char*)g_016c7b88;
    int o = *(int*)(g + 0xc);
    if (o != 0) {
        char* r = (char*)FUN_00b18e00_s00ef_c270((void*)o);
        *(uint8_t*)(r + 0x6e) = 1;
        void* im = SP_GameInputManager();
        ((FN2_ii)((*(void***)im)[0x19]))(im, 0x96b6b02c, 1);
    }
}

// @ 0x00efc8c0
void __cdecl FUN_00efc8c0(int v)
{
    int* g = (int*)g_016c7b88;
    int old = *g;
    *g = v;
    if (old != v)
        FUN_00f46410((void*)1, (void*)old, (void*)v);
}

// @ 0x00efc8f0
int __cdecl FUN_00efc8f0()
{
    int r = 0;
    if (g_016c7b88 != 0 && *(int*)((char*)g_016c7b88 + 8) != 0)
        r = (int)FUN_00eebf80(*(void**)((char*)g_016c7b88 + 8));
    return r;
}

// @ 0x00efc910
int __cdecl FUN_00efc910()
{
    int r = 0;
    if (g_016c7b88 != 0)
        r = (int)FUN_00eebf80(*(void**)((char*)g_016c7b88 + 4));
    return r;
}

// @ 0x00efc930
bool __cdecl FUN_00efc930(Vec3* out)
{
    int a3, a2;
    void* app = FUN_0067dd10();
    void* x = ((FN_v58)((*(void***)app)[0x16]))(app, &a2, &a3);
    void* y = FUN_007c4900(x, 0);
    (void)y;
    void* pm = FUN_00b3d350();
    Vec3* v = (Vec3*)FUN_00b82620(pm, (void*)&a2, (void*)&a3, (void*)0, 0);
    out->x = v->x; out->y = v->y; out->z = v->z;
    return (out->x != g_16c7b98 || out->y != g_16c7b9c || out->z != g_16c7ba0);
}

// @ 0x00efc9c0
bool __cdecl FUN_00efc9c0()
{
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0;
    Vec3 v;
    void* app = FUN_0067dd10();
    void* x = ((FN_v58)((*(void***)app)[0x16]))(app, &a0, &a1);
    void* y = FUN_007c4900(x, 0);
    (void)y;
    void* pm = FUN_00b3d350();
    Vec3* r = (Vec3*)FUN_00b82620(pm, &a3, &a2, &a1, 0);
    v.x = r->x; v.y = r->y; v.z = r->z;
    if (v.x != g_16c7b98 || v.y != g_16c7b9c || v.z != g_16c7ba0)
        return 1;
    return 0;
}

// @ 0x00efca60
bool __cdecl FUN_00efca60(char* a)
{
    void* p = *(void**)(*(char**)a + 0x64);
    void* esi = 0;
    if (p != 0)
        esi = ((FN1_i_s00ef_c270)((*(void***)p)[3]))(p, 0x17f243b);
    if (((FN0_i)((*(void***)esi)[8]))(esi) == 0x2e72cae)
        return 0;
    if (*(char*)(a + 0x20) != 0) {
        if (FUN_00efc530(esi))
            return 0;
    }
    if (*(int*)0x15ad298 == 0x16c7c08) {
        if (FUN_00efc530(esi))
            return 1;
        if (((TF_bp)FUN_00f33620)(*(void**)((char*)gSimulator_s00ef_c270 + 0x18), esi) == 0)
            return 0;
    }
    return 1;
}

// @ 0x00efcae0
void __cdecl FUN_00efcae0()
{
    int app = SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))((void*)app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b != 0) {
        int o = ((FN0_i)((*(void***)b)[3]))(b);
        if (o != 0) {
            *(uint8_t*)(o + 0x315) = 0;
            FUN_00d20430(0);
            return;
        }
    }
    void* m = FUN_00b3d280();
    if (m != 0) {
        FUN_00b0f950(m, 0);
        FUN_00b10c40(m, 0);
    }
}

// @ 0x00efcb40
float __cdecl FUN_00efcb40(void* self)
{
    float base = g_1441a88;
    void* eax = FUN_00f3e8a0(*(void**)((char*)gSimulator_s00ef_c270 + 0x74), 0, *(int*)self);
    if (eax != 0) {
        int k = *(int*)((char*)eax + 4);
        if (k == 0x2399be55)      base = g_1477fc0;
        else if (k == 0x24682294) base = g_13ec4d0;
    }
    float soft;
    void* v = FUN_00eeca30(self);
    if (v != 0)
        soft = ((PF_t)((*(void***)v)[0x1c]))(v);
    else
        soft = g_1485720;
    return (g_15ad340 * soft > base) ? (g_15ad340 * soft) : base;
}

// @ 0x00efcbe0
void __cdecl FUN_00efcbe0(void* self, int arg)
{
    void* eax = FUN_0067dd10();
    eax = ((void*(__thiscall*)(void*))((*(void***)eax)[0x14]))(eax);
    eax = ((void*(__thiscall*)(void*))((*(void***)eax)[0xe]))(eax);
    if (eax == 0)
        return;
    void* edi = ((FN1_i_s00ef_c270)((*(void***)eax)[3]))(eax, 0x11966ed);
    if (edi == 0)
        return;
    float v[3];
    v[0] = ((float*)self)[0];
    v[1] = ((float*)self)[1];
    v[2] = ((float*)self)[2];
    if (g_15ad344 != 0) {
        float outA[3];
        float coords[3];
        FUN_00eec2b0(&coords, &v, 0, &outA, 1);
        float d1 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
        float d2 = outA[0] * outA[0] + outA[1] * outA[1] + outA[2] * outA[2];
        if (d2 > d1) {
            v[0] = outA[0];
            v[1] = outA[1];
            v[2] = outA[2];
        }
    }
    FUN_00b13bb0(edi, 0, v, arg);
}

// @ 0x00efccd0
void __fastcall FUN_00efccd0(char* p)
{
    if (p != 0) {
        float vx, vy, vz;
        float* f = ((FN0_fp)((*(void***)p)[0x2c / 4]))(p);
        vx = f[0];
        vy = f[1];
        vz = f[2];
        if (g_16c7d18 != 0) {
            float* m = ((FN1_fp)((*(void***)p)[0x6c / 4]))(p, &vx);
            vx = (m[0] + m[3]) * g_1471064;
            vy = (m[4] + m[1]) * g_1471064;
            vz = (m[5] + m[2]) * g_1471064;
        }
        float v[3];
        v[0] = vx; v[1] = vy; v[2] = vz;
        FUN_00efcbe0(v, 0);
    }
}

// @ 0x00efcd90
int __cdecl FUN_00efcd90()
{
    int app = SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))((void*)app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b != 0) {
        int o = ((FN0_i)((*(void***)b)[3]))(b);
        if (o != 0 && (*(char*)(o + 0x319) == 0 || *(char*)(o + 0x11) != 0))
            return 1;
    }
    return 0;
}

// @ 0x00efcde0
void __fastcall FUN_00efcde0(void* p)
{
    int r;
    if (p == 0)
        r = 0;
    else
        r = ((FN0_i)((*(void***)p)[3]))(p);
    if (*(int*)(r + 0x54) != 0) {
        void* q = *(void**)(r + 0x54);
        if (q != 0) {
            int s = ((FN0_i)((*(void***)q)[3]))(q);
            ((FN2_ii)((*(void***)s)[0x15]))((void*)s, 0, 0);
            return;
        }
        FUN_00d20430(0);
    }
}

// @ 0x00efce30
void __fastcall FUN_00efce30(void* p)
{
    int r;
    if (p == 0)
        r = 0;
    else
        r = ((FN0_i)((*(void***)p)[3]))(p);
    if (*(int*)(r + 0x54) != 0) {
        void* q = *(void**)(r + 0x54);
        int s;
        if (q == 0)
            s = 0;
        else
            s = ((FN0_i)((*(void***)q)[3]))(q);
        ((FN2_ii)((*(void***)s)[0x15]))((void*)s, 1, 0);
        void* t = (void*)FUN_00b18e00_s00ef_c270(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0xe]))(t);
        t = (void*)FUN_00b18e00_s00ef_c270(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0xf]))(t);
        t = (void*)FUN_00b18e00_s00ef_c270(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0x10]))(t);
    }
}

// @ 0x00efcfb0
bool __cdecl FUN_00efcfb0(char* p)
{
    if (p[0x4c8] != 0) {
        int n = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        int i = 0;
        if (n < 0x20)
            return 0;
        int* it = (int*)(*(int*)(p + 0x4cc) + 0x0c);
        while (1) {
            if (*it == 2 || *it == 10)
                break;
            i++;
            it += 8;
            if (i << 5 >= n)
                return 0;
        }
    } else {
        if (*(int*)(p + 0x4b8) != 4 && *(int*)(p + 0x4b8) != 6)
            return 0;
    }
    return 1;
}

// @ 0x00efd020
void CtlQ::Update()
{
  UICtx2* g = g_UI2;
  if (!g->f18)
    return;
  ObjQ* obj = g->obj;
  void *A = 0, *B = 0, *C = 0, *D = 0, *F = 0, *G = 0, *H = 0, *I = 0, *J = 0, *K = 0;
  ThingB* p = GetThingB(obj);
  if (p) {
    float* q = GetRefCountedQ(obj);
    if (q) {
      Res* r = (Res*)f8->F3e900(obj);
      g = g_UI2;
      int mode;
      if (r)
        mode = *(int*)(*(char**)((char*)r + 0x70) + g->idx * 0x4e0 + 0x4b8);
      else
        mode = 1;
      bool flag4;
      if (obj && obj->f14)
        flag4 = obj->f14->V5();
      else
        flag4 = true;
      if (!b6 && r) {
        int idx = g->idx;
        if (IsInState2or10(*(char**)((char*)r + 0x70) + idx * 0x4e0)) {
          H = p;
          ((Setter_s00ef_d020*)g->setter30)->F68d70((char*)q + 4, *(char**)((char*)q + 0x28) + idx * 0x34 + 0x1c);
        } else if (r->F253e0()) {
          g = g_UI2;
          G = p;
          g->f28->F68ae0((char*)q + 0x1e8);
          ((ObjQ2*)obj)->F5ce30((char*)q + 0x1e8, (char*)q + 0x1f4, AT(float, q, 0x204));
        }
      }
      if (obj) {
        void* X = obj->Query(0x74e0069);
        if (X) {
          if (AT(float, X, 0x178) != AT(float, X, 0x17c)) {
            J = p;
            g_UI2->f54->F658e0((char*)X + 0x18c);
            g_UI2->f54->F666f0(AT(float, X, 0x178), AT(float, X, 0x17c));
            g_UI2->f54->SetTLerp(AT(float, X, 0x164) / (AT(float, X, 0x16c) - AT(float, X, 0x168)));
          }
          if (AT(float, X, 0x180) != AT(float, X, 0x184)) {
            K = p;
            g_UI2->f58->F658e0((char*)X + 0x198);
            g_UI2->f58->F666f0(AT(float, X, 0x180), AT(float, X, 0x184));
            g_UI2->f58->SetTLerp(AT(float, X, 0x98) / (AT(float, X, 0x174) - AT(float, X, 0x170)));
          }
        }
        void* Y = obj->Query(0x7b38ba7);
        if (Y) {
          if (AT(float, Y, 0x138) != AT(float, Y, 0x13c)) {
            J = p;
            g_UI2->f54->F658e0((char*)Y + 0x150);
            g_UI2->f54->F666f0(AT(float, Y, 0x138), AT(float, Y, 0x13c));
            g_UI2->f54->SetTLerp(AT(float, Y, 0x124) / (AT(float, Y, 0x12c) - AT(float, Y, 0x128)));
          }
          if (AT(float, Y, 0x140) != AT(float, Y, 0x144)) {
            K = p;
            g_UI2->f58->F658e0((char*)Y + 0x15c);
            g_UI2->f58->F666f0(AT(float, Y, 0x140), AT(float, Y, 0x144));
            g_UI2->f58->SetTLerp(AT(float, Y, 0x98) / (AT(float, Y, 0x134) - AT(float, Y, 0x130)));
          }
        }
      }
      Thing2* t = p->V46(0x175cdc9);
      g = g_UI2;
      if (g->obj) {
        if ((g->fc == 0 || g->f10 != g->f28) && t && G)
          D = GetThingB((ObjQ*)t->f54);
        g = g_UI2;
        if (g->obj && (g->fc == 0 || g->f10 != 0)) {
          if (flag4)
            C = p;
          if (r) {
            if (flag4 && r->F255d0()) {
              F = p; A = p; B = p;
            }
            if (mode == 3) {
              float lf = ResourceScaledFloat(p);
              float* tbl = (float*)(g_UI2->idx * 0x34 + *(char**)((char*)q + 0x28));
              float v = (*tbl > lf) ? *tbl : lf;
              g_UI2->f2c->SetT(v);
              I = p;
              if (!p->F88940(0x65640a90)) {
                p->F8b1a0(0x65640a90);
                p->F88a00(0x65640a90, 1000000.0f);
              }
              p->F8a020(0x65640a90, v);
            } else {
              p->F8ad30(0x65640a90, 1);
            }
            g = g_UI2;
          }
          if (g->f10 == g->f18) {
            C = 0; B = 0; F = 0;
          } else if (g->f10 == g->f1c) {
            C = 0; A = 0; F = 0;
          } else if (g->f10 == g->f20) {
            B = 0; A = 0; F = 0;
          } else {
            if (GameInputManager_s00ef_d020()->IsKey(g_15ad294)) {
              F = 0;
            } else {
              B = 0; A = 0;
            }
          }
        }
      }
      if (G) {
        Thing2* t2 = ((ThingB*)G)->V46(0x175cdc9);
        int rv = g_G2b->f74->F3dc70(t2);
        void* sub = t2->f54 ? t2->f54->Query(0x1186577) : 0;
        ThingB* gt = (ThingB*)G;
        float fv = gt->V13((char*)rv + 0x1e8);
        int iv = gt->V11(fv);
        if (FUN_00f212c0(iv)) {
          AT(char, gt, 0x6e) = 0;
          if (sub)
            AT(char, sub, 0x6e) = 0;
        } else {
          AT(char, gt, 0x6e) = 1;
          if (sub)
            AT(char, sub, 0x6e) = 1;
        }
      }
    }
  }
  g = g_UI2;
  g->f18->SetTarget(A);
  g_UI2->f1c->SetTarget(B);
  g_UI2->f20->SetTarget(C);
  g_UI2->f14->SetTarget(D);
  g_UI2->f24->SetTarget(F);
  g_UI2->f28->SetTarget(G);
  g_UI2->f2c->SetTarget(I);
  ((Setter_s00ef_d020*)g_UI2->setter30)->F68850(H);
  g_UI2->f54->SetTarget(J);
  g_UI2->f58->SetTarget(K);
  if (!obj)
    ((Sys14*)g_G2b->f14)->F4e90();
}

// @ 0x00efd6e0
__declspec(noinline) bool RayHitPlane(const V3_s00ef_d020* plane, V3_s00ef_d020* out)
{
  V3_s00ef_d020 dir, origin, cam;
  AppGet()->GetViewer()->GetCameraRay(&origin, &dir);
  AppGet()->GetViewer()->GetCameraLocationInfo(0, &cam, 0, 0);
  float nx = -cam.x, ny = -cam.y, nz = -cam.z;
  float denom = dir.z * nz + dir.y * ny + dir.x * nx;
  float pn = -(plane->z * nz + plane->y * ny + plane->x * nx);
  if (denom == 0.0f)
    return false;
  float t = -(((origin.z * nz + origin.y * ny + origin.x * nx) + pn) / denom);
  if (t < 0.0f)
    return false;
  out->x = origin.x + dir.x * t;
  out->y = origin.y + dir.y * t;
  out->z = origin.z + dir.z * t;
  return true;
}

// @ 0x00efd830
__declspec(noinline) void ProjectHit(const V3_s00ef_d020* s, V3_s00ef_d020* hit, float* out)
{
  if (RayHitPlane(s, hit)) {
    float dx = hit->x - s->x, dy = hit->y - s->y, dz = hit->z - s->z;
    float inv = 1.0f / (float)sqrt((double)(s->x * s->x + s->y * s->y + s->z * s->z));
    *out = (s->x * inv) * dx + (inv * s->z) * dz + (s->y * inv) * dy;
  }
}

// @ 0x00efd8e0
__declspec(noinline) V3_s00ef_d020* ObjPlaneVec(Obj* obj, V3_s00ef_d020* result)
{
  ThingA* t = GetThingA(obj);
  float* rc = GetRefCounted18(obj);
  V4_s00ef_d020* src = rc ? (V4_s00ef_d020*)((char*)rc + 0x10) : t->GetRot();
  V4_s00ef_d020 q = *src;
  V3_s00ef_d020 tmp;
  V3_s00ef_d020* r = FUN_0059aed0(&tmp, &g_UI->v6c, (V3_s00ef_d020*)&q);
  result->x = r->x;
  result->y = r->y;
  result->z = r->z;
  return result;
}

// @ 0x00efd970
char PickUpdate(Obj* obj)
{
  V3_s00ef_d020 origin, dir;
  AppGet()->GetViewer()->F7c46f0(&origin, &dir);
  ThingA* t = GetThingA(obj);
  V3_s00ef_d020 q1 = *t->GetPos();
  V4_s00ef_d020 q2 = *t->GetRot();
  V3_s00ef_d020 hit;
  Picker* pk = FUN_00b3d240(t, &origin, &dir, &hit);
  bool ok = pk->F35bf0();
  if (!ok) {
    if (!RayHitPlane(&q1, &hit))
      return ok;
  }
  float* rc = GetRefCounted18(obj);
  V3_s00ef_d020 sret, delta, n;
  if (rc) {
    float px = AT(float, rc, 0x10), py = AT(float, rc, 0x14), pz = AT(float, rc, 0x18), pw = AT(float, rc, 0x1c);
    float inv = 1.0f / (((pw * pw + pz * pz) + py * py) + px * px);
    n.x = -(px * inv);
    n.y = -(py * inv);
    n.z = -(pz * inv);
    delta.x = AT(float, rc, 4) - hit.x;
    delta.y = AT(float, rc, 8) - hit.y;
    delta.z = AT(float, rc, 0xc) - hit.z;
    sret.x = q2.x; sret.y = q2.y; sret.z = q2.z;
  } else {
    float inv = 1.0f / ((((q2.z * q2.z + q2.w * q2.w) + q2.y * q2.y) + q2.x * q2.x));
    n.x = -(q2.x * inv);
    n.y = -(q2.y * inv);
    n.z = -(q2.z * inv);
    delta.x = q1.x - hit.x;
    delta.y = q1.y - hit.y;
    delta.z = q1.z - hit.z;
    sret = q1;
  }
  V3_s00ef_d020* r = FUN_0059aed0(&sret, &delta, &n);
  g_UI->v6c.x = r->x;
  g_UI->v6c.y = r->y;
  g_UI->v6c.z = r->z;
  return ok;
}

// @ 0x00efdc00
void ToolSnapUpdate()
{
  UICtx* g = g_UI;
  Obj* obj = (Obj*)g->fc;
  float* rc = GetRefCounted18(obj);
  ThingA* t = GetThingA(obj);
  const V3_s00ef_d020* s = &g_UI->v7c;
  V3_s00ef_d020 r;
  float f;
  if (RayHitPlane(s, &r)) {
    float dx = r.x - s->x, dy = r.y - s->y, dz = r.z - s->z;
    float inv = 1.0f / (float)sqrt((double)(s->x * s->x + s->y * s->y + s->z * s->z));
    f = (s->x * inv) * dx + (inv * s->z) * dz + (inv * s->y) * dy;
  }
  g = g_UI;
  f = f - g->fa0;
  float inv2 = 1.0f / (float)sqrt((double)(g->v7c.x * g->v7c.x + g->v7c.y * g->v7c.y + g->v7c.z * g->v7c.z));
  r.x = g->v7c.x + (g->v7c.x * inv2) * f;
  r.y = g->v7c.y + (g->v7c.y * inv2) * f;
  r.z = g->v7c.z + (g->v7c.z * inv2) * f;
  float* pos = rc + 1;
  AT(float, rc, 4) = r.x;
  AT(float, rc, 8) = r.y;
  AT(float, rc, 0xc) = r.z;
  SelState st;
  st.a = 2; st.b = 0; st.c = 1; st.d = 0.0f; st.flags = 0;
  FUN_00eed720(rc, t, &st);
  int b = (st.flags >> 4) & 1;
  int one = 1;
  AT(float, rc, 0x220) = FUN_00eec370(pos, b, &one);
  char bx, by;
  FUN_00eec8e0(rc, &bx, &by);
  float v = AT(float, rc, 0x220);
  if ((v > 0.0f && by == 0) || (v < 0.0f && bx == 0)) {
    V3_s00ef_d020 buf;
    V3_s00ef_d020* p = PlanetModelCtor(&buf, pos, b, 1, 1, 0)->F82df0();
    AT(float, rc, 4) = p->x;
    AT(float, rc, 8) = p->y;
    AT(float, rc, 0xc) = p->z;
    AT(float, rc, 0x220) = 0.0f;
  }
  g_G2->f74->F3da90(rc, 0);
  if (g_15acb40_s00ef_d020)
    FUN_00eee760(rc, g_UI->v8c);
}

// @ 0x00efde90
bool SelCtx::FUN_00efde90(int param_2)
{
    int* base = (int*)param_2;
    int* p = *(int**)((char*)base + 0x20);
    if (*(char*)((char*)p + 0x18) == 1) {
        int* q = (int*)((char*)p + *(int*)((char*)p + 0x10));
        if (q != 0) {
            int* piVar1 = (int*)q[3];
            if (piVar1 != 0 && *(char*)((char*)this + 4) != 0) {
                if (((VObj_s00ef_d020*)piVar1)->s3(0x137e8e0) != 0)
                    return false;
            }
        }
    }
    return true;
}

// @ 0x00efdee0
void __cdecl FUN_00efdee0()
{
    void* obj = FUN_00b3d230();
    ((PluginObj*)obj)->FUN_00b5cde0(0xebb801);

    void* app = FUN_0067dd10();
    void* a = (void*)((FN0_i)((*(void***)app)[20]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[16]))(a);

    void* target = 0;
    if (b != 0) {
        target = (void*)((FN1_ir)((*(void***)b)[3]))(b, 0x11966ed);
        if (target != 0 && *(int*)((char*)target + 0x308) != (int)g_15ad348) {
            ((PluginObj*)target)->FUN_00b11870(g_15ad348);
            ((PluginObj*)target)->FUN_00b10760(0.0f, g_15ad2ac * g_13ec4b4, g_148b6e8);
        }
    }

    char* mgr = *(char**)((char*)gSimulator_s00ef_dee0 + 0x74);
    char* base = *(char**)(mgr + 0x10);
    float posA[3];
    float orient[4];
    float radius;
    posA[0] = *(float*)(base + 0x2c30);
    posA[1] = *(float*)(base + 0x2c34);
    posA[2] = *(float*)(base + 0x2c38);
    orient[0] = *(float*)(base + 0x2c3c);
    orient[1] = *(float*)(base + 0x2c40);
    orient[2] = *(float*)(base + 0x2c44);
    orient[3] = *(float*)(base + 0x2c48);
    radius = *(float*)(base + 0x2c4c);

    if (g_16c7b98 == posA[0] && g_16c7b9c == posA[1] && g_16c7ba0 == posA[2]) {
        float vecA[3];
        float* r = (float*)((PluginObj*)FUN_00b3d350())->FUN_00b81630(vecA, &g_15ad2b0);
        posA[0] = r[0];
        posA[1] = r[1];
        posA[2] = r[2];
        float* q = (float*)((PluginObj*)FUN_00b3d350())->FUN_00b7f190(vecA, posA);
        orient[0] = q[0];
        orient[1] = q[1];
        orient[2] = q[2];
        orient[3] = q[3];
        ((PluginObj*)target)->FUN_00b12dd0(posA, orient, 1);
        void* check = ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0x74))->FUN_00ff3f00();
        if (check != 0)
            FUN_00efcbe0(1);
    } else {
        ((PluginObj*)target)->FUN_00b12dd0(posA, orient, 1);
        ((PluginObj*)target)->FUN_00b13bb0(posA, 1);
        ((PluginObj*)target)->FUN_00b104c0(radius);
    }
}

// @ 0x00efe110
void __cdecl FUN_00efe110()
{
    char* g = (char*)g_016c7b88_s00ef_dee0;
    if (*(char*)(g + 0xa5) == 0) {
        void* m = FUN_0067dd50();
        void* v = (void*)((FN0_i)((*(void***)m)[7]))(m);
        int dx = *(int*)(g + 0xa8) - *(int*)((char*)v + 8);
        int dy = *(int*)(g + 0xac) - *(int*)((char*)v + 0xc);
        *(char*)(g + 0xa5) = (char)(((dx < 0 ? -dx : dx) > 2 || (dy < 0 ? -dy : dy) > 2) ? 1 : 0);
    }
    void* app = FUN_0067dd10();
    void* viewer = (void*)((FN0_i)((*(void***)app)[22]))(app);
    float cam[2];
    char a[4];
    char b[10];
    ((PluginObj*)viewer)->FUN_007c40c0(a, cam);
    char* list = (char*)((PluginObj*)viewer)->FUN_007c4010(b);
    g_15ad29c = (float)(*(int*)(list + 0xc) - *(int*)(list + 4)) * g_1471064 * cam[0];
    ((PluginObj*)&g_16c7c28)->FUN_006ffe00((char*)viewer + 0xc0);

    char** descSlot = (char**)&cam[0];
    if (g_15fd918_s00ef_dee0 != 0
        && ((FN2_ip_s00ef_dee0)((*(void***)g_15fd918_s00ef_dee0)[9]))(g_15fd918_s00ef_dee0, 0xbc2db1cd, descSlot)
        && *(uint16_t*)(*descSlot + 0x12) == 1) {
        void* val = ((PluginObj*)*descSlot)->FUN_0041e920();
        g_16c7b8c = *(uint8_t*)val;
    }
    if (g_15fd918_s00ef_dee0 != 0
        && ((FN2_ip_s00ef_dee0)((*(void***)g_15fd918_s00ef_dee0)[9]))(g_15fd918_s00ef_dee0, 0xfd290b85, descSlot)
        && *(uint16_t*)(*descSlot + 0x12) == 1) {
        void* val = ((PluginObj*)*descSlot)->FUN_0041e920();
        g_16c7b8d = *(uint8_t*)val;
    }
}

// @ 0x00efe240
int __cdecl FUN_00efe240()
{
    FUN_00efe110();
    int* p = g_15ad298_s00ef_dee0;
    ((FN0_i)((*(void***)p)[0x10]))(p);
    return FUN_00ebf5b0();
}

// @ 0x00efe260
void __cdecl FUN_00efe260()
{
    int* p = g_15ad298_s00ef_dee0;
    ((FN0_i)((*(void***)p)[8]))(p);
    char* g = (char*)g_016c7b88_s00ef_dee0;
    void* q = *(void**)(g + 0x10);
    if (q != 0) {
        *(void**)(g + 0x10) = 0;
        ((FN0_i)((*(void***)q)[1]))(q);
    }
    void* r = FUN_00eebf80((void*)0);
    if (r != 0)
        FUN_00ed54b0(r);
    else
        FUN_00ed4e90(0);
}

// @ 0x00efe310
void __cdecl FUN_00efe310(int flag)
{
    void* app = FUN_0067dd10();
    void* a = (void*)((FN0_i)((*(void***)app)[20]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[14]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN1_ir)((*(void***)b)[3]))(b, 0x11966ed);
    if (o == 0)
        return;
    void* sim = *(void**)((char*)gSimulator_s00ef_dee0 + 0xd4);
    ((FN2_ii)((*(void***)sim)[4]))(sim, 0xf, 0x10);
    ((PluginObj*)o)->FUN_00b0f950(flag);
    void* l = (void*)g_15ad298_s00ef_dee0;
    ((FN0_i)((*(void***)l)[14]))(l);
    void* m = FUN_0067dd50();
    void* vp = (void*)((FN0_i)((*(void***)m)[7]))(m);
    char* g = (char*)g_016c7b88_s00ef_dee0;

    if ((char)flag != 0) {
        ((PluginObj*)(g + 0xb0))->FUN_0093a480(200, 1);
        g = (char*)g_016c7b88_s00ef_dee0;
        *(char*)(g + 0xa5) = 0;
        *(int*)(g + 0xa8) = *(int*)((char*)vp + 8);
        *(int*)(g + 0xac) = *(int*)((char*)vp + 0xc);
        return;
    }

    int dx = *(int*)(g + 0xa8) - *(int*)((char*)vp + 8);
    int dy = *(int*)(g + 0xac) - *(int*)((char*)vp + 0xc);
    if (*(char*)(g + 0xa5) != 0 || (dx < 0 ? -dx : dx) > 2 || (dy < 0 ? -dy : dy) > 2) {
        if ((*(int*)(g + 0xb0) | *(int*)(g + 0xb4)) == 0)
            return;
        if (((PluginObj*)(g + 0xb0))->FUN_005ff1c0() != 0)
            return;
    }

    if (FUN_00efc930() != 0) {
        ((PluginObj*)o)->FUN_00b148c0(0.0f, 0.0f, 0.0f, 0.0f);
        FUN_00efcbe0(0);
    }
    g = (char*)g_016c7b88_s00ef_dee0;
    *(char*)(g + 0xa5) = 1;
    *(int*)(g + 0xac) = 0;
    *(int*)(g + 0xa8) = 0;
    ((PluginObj*)(g + 0xb0))->FUN_0093a2e0();
}

// @ 0x00efe4a0
void __cdecl FUN_00efe4a0(int flag)
{
    void* app = (void*)SP_App_s00ef_dee0();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    if (*(char*)((char*)o + 0x319) == 0 && flag == 0) {
        void* d4 = *(void**)((char*)gSimulator_s00ef_dee0 + 0xd4);
        ((FN2_ii)((*(void***)d4)[4]))(d4, 0x13, 0x14);
    }
    FUN_00b10c40(o, flag);
}

// @ 0x00efe510
void __cdecl FUN_00efe510(float f)
{
    void* app = (void*)SP_App_s00ef_dee0();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    (void)f;
}

// @ 0x00efe5d0
__declspec(noinline) bool __cdecl FUN_00efe5d0(int v)
{
    char* g = (char*)g_016c7b88_s00ef_dee0;
    int n = (*(int*)(g + 0x90) - *(int*)(g + 0x8c)) >> 5;
    if (n > 0) {
        int* p = *(int**)(g + 0x8c);
        for (int i = 0; i < n; i++) {
            if (*p == v)
                return true;
            p += 8;
        }
    }
    return false;
}

// @ 0x00efe610
bool __cdecl FUN_00efe610(void* a)
{
    int r = (int)FUN_00eebf80(a);
    return FUN_00efe5d0(r);
}

// @ 0x00efe630
bool __cdecl FUN_00efe630(int id, void* p)
{
    if (id == (int)0xcf56099a) {
        if (p == 0)
            return false;
        int a = ((FN1_ir)((*(void***)p)[0x2e]))(p, 0x175cdc9);
        if (a == 0 || *(int*)(a + 0x38) == 0) {
            int b = ((FN1_ir)((*(void***)p)[0x2e]))(p, 0x3a25119);
            if (b == 0 || *(int*)(b + 0x134) == 0)
                return false;
        }
        return true;
    }
    if (id == (int)0xe34e8a60)
        return true;
    if (id == 0x5b3d1d0d)
        return true;
    return false;
}

// @ 0x00efe6a0
int __cdecl FUN_00efe6a0(int param)
{
    int* o = (int*)FUN_00eeca30((void*)param);
    float scale = 1.0f;
    if ((*(uint8_t*)((char*)o + 0x50) & 0x10) == 0)
        scale = ((float (__thiscall*)(void*))(*(void***)o)[28])(o);

    if (g_16c7b8c != 0 && *(uint8_t*)((char*)o + 0x78) != 0)
        return 2;

    void* app = FUN_0067dd10();
    void* viewer = (void*)((FN0_i)((*(void***)app)[22]))(app);
    float vecA[3];
    float vecB[3];
    ((PluginObj*)viewer)->FUN_007c3d30(vecA, vecB, 0, 0);

    float* pos = (float*)((FN0_i)((*(void***)o)[11]))(o);
    float dot = (vecB[2] * (pos[2] - vecA[2]) + vecB[1] * (pos[1] - vecA[1]))
              + vecB[0] * (pos[0] - vecA[0]);
    float* pos2 = (float*)((FN0_i)((*(void***)o)[11]))(o);
    if (((PluginObj*)&g_16c7c28)->FUN_006ffbd0(pos2, scale) == 0x40)
        return 2;

    void* e = (void*)((FN0_i)((*(void***)o)[43]))(o);
    int result;
    if (e == 0 || ((*(uint32_t*)((char*)e + 4) >> 14) & 1) == 0
        || ((*(uint32_t*)((char*)e + 4) >> 18) & 1) != 0) {
        result = 1;
    } else {
        result = FUN_00efc5f0(param, dot);
        if (result == 0) {
            if (((PluginObj*)o)->FUN_00efc570(e, dot) == 0)
                result = 1;
        }
    }

    char local[12];
    FUN_00eec3d0(local, (void*)param);
    int id = (int)FUN_00eece20(local);
    if (result == 1) {
        if (g_16c7b8d == 0 && !FUN_00efe630(id, o))
            return 0;
        float* pf = (float*)param;
        float dot2 = (pf[2] * vecB[1] + pf[3] * vecB[2]) + pf[1] * vecB[0];
        if (-dot2 < 0.0f)
            result = 2;
    }
    return result;
}

// @ 0x00efe870
int __cdecl FUN_00efe870(int* key)
{
    char* g = (char*)*(void**)((char*)gSimulator_s00ef_dee0 + 0x74);
    char* base = *(char**)(g + 0x10);
    int* begin = *(int**)(base + 0x2bf4);
    int* end = *(int**)(base + 0x2bf8);
    int* p = begin;
    while (p != end) {
        if (p[2] == key[0] && p[3] == key[1] && p[4] == key[2])
            return p[0];
        p = (int*)((char*)p + 0x27e8);
    }
    return -1;
}

// @ 0x00efe8d0
void Scene::FUN_00efe8d0(int a, int b)
{
    ((FN1_i)((*(void***)this)[6]))(this, b == 1);
    if (b != 2)
        ((FN1_i)((*(void***)this)[8]))(this, (b != 0) ? a : 0);
    if (b == 1 && *(int*)((char*)g_016c7b88_s00ef_dee0 + 4) != 0)
        FUN_00efd970(*(void**)((char*)g_016c7b88_s00ef_dee0 + 4));
}

// @ 0x00efe930
void Scene::FUN_00efe930(void* obj)
{
    char* g = (char*)g_016c7b88_s00ef_dee0;
    if (g == 0 || *(int*)(g + 0x20) == 0)
        return;

    if (obj == 0) {
        void* p = *(void**)(g + 0x10);
        if (p != 0) {
            *(void**)(g + 0x10) = 0;
            ((FN0_i)((*(void***)p)[1]))(p);
        }
        ((FN1_i)((*(void***)this)[6]))(this, 0);
    }

    if (FUN_00efc530(obj)) {
        g = (char*)g_016c7b88_s00ef_dee0;
        ((PluginObj*)(g + 0x10))->FUN_00b5f950(obj);
        return;
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    void* old = *(void**)(g + 4);
    bool changed = (old != obj);
    if (changed && old != 0) {
        void* o2 = FUN_00b18e00_s00ef_dee0(old);
        if (o2 != 0)
            ((PluginObj*)o2)->FUN_00c8ad30(0x65640a90, 1);
    }

    if (obj != 0) {
        void* r = (void*)((FN1_ir)((*(void***)obj)[3]))(obj, 0x175cdc9);
        if (r != 0) {
            void* v = *(void**)((char*)r + 0x50);
            if (v != 0) {
                g = (char*)g_016c7b88_s00ef_dee0;
                ((PluginObj*)(g + 4))->FUN_00b5f950(v);
                g = (char*)g_016c7b88_s00ef_dee0;
                ((PluginObj*)(g + 0x10))->FUN_00b5f950(*(void**)(g + 0x28));
                goto after;
            }
        }
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    ((PluginObj*)(g + 4))->FUN_00b5f950(obj);
    g = (char*)g_016c7b88_s00ef_dee0;
    if (*(void**)(g + 0x10) != 0) {
        void* p = *(void**)(g + 0x10);
        *(void**)(g + 0x10) = 0;
        ((FN0_i)((*(void***)p)[1]))(p);
    }

after:
    g = (char*)g_016c7b88_s00ef_dee0;
    if (obj == 0) {
        void* p8 = *(void**)(g + 8);
        if (p8 != 0) {
            *(void**)(g + 8) = 0;
            ((FN0_i)((*(void***)p8)[1]))(p8);
        }
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    void* p4 = *(void**)(g + 4);
    if (p4 != 0)
        FUN_00eef570(p4, g + 0x8c);
    else
        FUN_00eef4b0(g + 0x8c);

    ((PluginObj*)this)->FUN_00efd020();

    if (changed) {
        void* o3 = FUN_00b3d250();
        int val = (obj != 0) ? (int)0xd7614d9d : (int)0x91247de4;
        ((FN2_ii)((*(void***)o3)[25]))(o3, val, 1);
    }
}

// @ 0x00efeaa0
int __fastcall FUN_00efeaa0(char* p)
{
    if (*(int*)((char*)g_016c7b88_s00ef_dee0 + 0xc) == 0 && *(char*)(p + 5) == 0)
        return 0;
    return 1;
}

// @ 0x00efeac0
bool __stdcall FUN_00efeac0(int unused)
{
    (void)unused;
    return *(int*)((char*)g_016c7b88_s00ef_dee0 + 4) != 0;
}

// @ 0x00efeae0
bool Scene::FUN_00efeae0(int arg)
{
    char bl = 0;
    void* o = FUN_00eebf80((void*)arg);
    if (o == 0)
        return bl == 0;

    bool flag = (g_15acb40 != 0 && arg != 0 && arg == *(int*)((char*)g_016c7b88_s00ef_dee0 + 0xc));

    bl = (char)((PluginObj*)*(void**)((char*)this + 8))->FUN_00f41420(o, o, flag, 0);

    if (g_15acb40 == 0 || arg == 0)
        return bl == 0;
    char* g = (char*)g_016c7b88_s00ef_dee0;
    if (arg != *(int*)(g + 4))
        return bl == 0;

    int* p = *(int**)(g + 0x8c);
    int* end = *(int**)(g + 0x90);
    while (p != end) {
        int elem = *p;
        bl &= (char)((PluginObj*)*(void**)((char*)this + 8))->FUN_00f41420((void*)elem, o, 0, 1);
        bl &= (char)((PluginObj*)*(void**)((char*)this + 8))->FUN_00f3b9e0((void*)elem,
                 FUN_00b18e00_s00ef_dee0(FUN_00f3d780((void*)elem)), 1);
        p += 8;
    }
    return bl == 0;
}

// @ 0x00efebb0
void Scene::FUN_00efebb0(void* arg)
{
    void* ebx = ((PluginObj*)*(void**)((char*)this + 8))->FUN_00f3e8a0(*(void**)arg);

    if (arg == ((PluginObj*)*(void**)((char*)this + 8))->FUN_00ff3f00()) {
        ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(4, 5);
        return;
    }

    char local[12];
    void* r = FUN_00eec3d0(local, arg);
    if (*(int*)((char*)r + 4) == 0x2b978c46) {
        ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x1f, 0x20);
        ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x43, 0x44);
        return;
    }

    int id = (int)FUN_00eece20(ebx);
    if (id == 0xb10e526f) {
        ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x2f, 0x30);
        return;
    }
    if (id == 0xe137ff08) {
        ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x35, 0x36);
        return;
    }
    if (id == 0x5b3d1d0d || id == 0xd37c1045)
        ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x59, 0x5a);
}

// @ 0x00efec90
void Scene::FUN_00efec90(void* arg)
{
    char flag = 0;
    char* g = (char*)g_016c7b88_s00ef_dee0;

    if (arg != 0) {
        void* r = (void*)((FN1_ir)((*(void***)arg)[3]))(arg, 0x137e8e0);
        if (r != 0) {
            g = (char*)g_016c7b88_s00ef_dee0;
            if (*(void**)(g + 0x10) == *(void**)(g + 0x20))
                flag = 1;
        }
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    if (*(void**)(g + 0x10) != *(void**)(g + 0x14)
        && *(void**)(g + 0x10) != *(void**)(g + 0x28)) {
        void* p = *(void**)(g + 0x10);
        void* q = p ? (void*)((FN1_ir)((*(void***)p)[3]))(p, 0x76c67df) : 0;
        if (!((PluginObj*)(g + 0x30))->FUN_00c64a70(q)
            && *(void**)(g + 0x10) != *(void**)(g + 0x2c)
            && flag == 0
            && g_15acb40 != 0
            && *(void**)(g + 0x8c) != *(void**)(g + 0x90)) {
            ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0x74))->FUN_00f3bbd0(*(void**)(g + 4), 0);
            return;
        }
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    void* old = *(void**)(g + 0xc);
    if (arg != old) {
        if (arg != 0)
            ((FN0_i)((*(void***)arg)[0]))(arg);
        *(void**)(g + 0xc) = arg;
        if (old != 0)
            ((FN0_i)((*(void***)old)[1]))(old);
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    void* p = *(void**)(g + 0x10);
    void* q = p ? (void*)((FN1_ir)((*(void***)p)[3]))(p, 0x7a309fb) : 0;
    q = (void*)((FN0_i)((*(void***)q)[22]))(q);

    ((PluginObj*)*(void**)((char*)this + 8))->FUN_00f45970();

    g = (char*)g_016c7b88_s00ef_dee0;
    void* obj = FUN_00eebf80(*(void**)(g + 4));
    if (obj != 0) {
        char local[12];
        FUN_00eec3d0(local, obj);
        int id = (int)FUN_00eece20(local);
        if (id == 0xe137ff08) {
            g = (char*)g_016c7b88_s00ef_dee0;
            if (*(void**)(g + 0x10) == *(void**)(g + 0x20))
                ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x3b, 0x3c);
            else if (*(void**)(g + 0x10) == *(void**)(g + 0x54))
                ((PluginObj*)*(void**)((char*)gSimulator_s00ef_dee0 + 0xd4))->FUN_00efbbe0(0x39, 0x3a);
        }
    }

    g = (char*)g_016c7b88_s00ef_dee0;
    if (flag != 0)
        FUN_00eef570(*(void**)(g + 4), g + 0x8c);
    else
        FUN_00eef4b0(g + 0x8c);
}

// @ 0x00efee60
void UI_s00ef_ee60::f_efee60(void* p)
{
    GObj* g = pGame;
    void* q = *(void**)((char*)g_mgr + 0xc);
    void* e = p;
    if (q) e = q;
    if (b5) {
        b5 = 0;
        SetSelectedObject();
        FwdC6E0(e);
        return;
    }
    if (q == 0) {
        g->F45970();
        SetSelectedObject();
        if (e) {
            void* r = ((Handle*)e)->v0c(0x74e0069);
            if (r) *(uint8_t*)((char*)r + 0x12b) = 0;
        }
    }
    FwdC6E0(e);
}

// @ 0x00efeee0
void* UI_s00ef_ee60::f_efeee0(int param)
{
    char local1c[12];
    char local10[8];
    f_efc930();
    void* model = FUN_00b3d350_s00ef_ee60(local10, local1c);
    ((GObj*)model)->BSO(local10, local1c);
    void* r;
    if (param == -2) {
        r = FUN_00f43420(local1c, local10);
    } else {
        FUN_00f3e8a0(param);
        r = FUN_00f44370(param, local1c, local10, -1.0f);
    }
    pGame->F427C0();
    g_016c7d20 = (g_016c7d20 == 0.0f) ? 1.0f : 0.0f;
    AudioAT* at = (AudioAT*)EA_Audio_GetSystemAT();
    if (at) {
        at->v38(0x3cdd1a9);
        at->v40(0x34753a7, 0xcb1fdf45);
        at->v3c(0x34753aa, g_016c7d20);
        at->v58();
    }
    return r;
}

// @ 0x00efefe0
void UI_s00ef_ee60::f_efefe0()
{
    void* u = *(void**)((char*)g_mgr + 4);
    if (pGame->F32790(u) != 0) {
        pGame->F33BF0();
        ((void(__thiscall*)(void*, int)) * ((void**)vtable + 0x20 / 4))(this, 0);
        pGame->F38150(u);
        pGame->F34560();
    }
}

// @ 0x00eff030
void UI_s00ef_ee60::f_eff030()
{
    int* pc = (int*)pC;
    if (pc[0] == 0) return;
    if (!f_efc7d0((void*)pc[0], (void*)pc[1])) return;
    if (!f_efc930()) return;
    pGame->F33BF0();
    void* r = pGame->F336A0(pC);
    if (r == 0) return;
    VObj_s00ef_ee60* o = (VObj_s00ef_ee60*)FUN_00b18e00_s00ef_ee60(r);
    int local;
    o->v38(&local);
    pGame->F36450(0, 0, r);
    pGame->F38330(1);
    pGame->F34560();
}

// @ 0x00eff0c0
void UI_s00ef_ee60::f_eff0c0()
{
    void* volatile self = this;
    __declspec(align(16)) volatile float stagedLerp;
    if (((MgrState*)g_mgr)->p20 == 0) return;

    Object1b0* o = (Object1b0*)pGame->p1b0;
    void* obj = 0;
    void* firstArg = 0;
    void* secondArg = 0;

    if (o != 0) {
        void* h = ((MgrState*)g_mgr)->handle;
        if (h != 0 && (((MgrState*)g_mgr)->pC == 0 || ((MgrState*)g_mgr)->p10 != 0)) {
            obj = FUN_00b18e00_s00ef_ee60(h);

            OrientationState* s = o->p4;
            if (s->f64 > s->f60) {
                void* ring = ((MgrState*)g_mgr)->p5c;
                stagedLerp = ((float(__thiscall*)(void*))Vt(obj)[0x34 / 4])(obj);
                stagedLerp -= 3.0f;
                ((RotationRing*)ring)->SetTLerp(stagedLerp);
                firstArg = obj;
            }

            s = o->p4;
            if (s->f5c > s->f58) {
                ((RotationRing*)((MgrState*)g_mgr)->p60)->SetTLerp(o->value0c);
                secondArg = obj;
            }
        }
    }

    {
        void* p = ((MgrState*)g_mgr)->p20;
        ((void(__thiscall*)(void*, void*))Vt(p)[0x54 / 4])(p, obj);
    }
    {
        void* p = ((MgrState*)g_mgr)->p5c;
        ((void(__thiscall*)(void*, void*))Vt(p)[0x54 / 4])(p, firstArg);
    }
    {
        void* p = ((MgrState*)g_mgr)->p60;
        ((void(__thiscall*)(void*, void*))Vt(p)[0x54 / 4])(p, secondArg);
    }
    self = this;
}

// @ 0x00eff1e0
bool UI_s00ef_ee60::f_eff1e0(int)
{
    void* a = *(void**)((char*)g_mgr + 4);
    if (a == 0) return false;
    void* r = pGame->F32790(a);
    if (r == 0) return false;
    OrientationState* o = ((PlacementView*)r)->p4;
    return o->f64 > o->f60;
}

// @ 0x00eff230
void UI_s00ef_ee60::f_eff230(void* p)
{
    *(uint8_t*)((char*)g_mgr + 0x64) = 1;
    *(int*)((char*)g_mgr + 0x68) = 1;
    void** slot = (void**)((char*)g_mgr + 0xc);
    void* old = *slot;
    if (p != old) {
        if (p) ((RefObj*)p)->v0();
        *slot = p;
        if (old) ((RefObj*)old)->v4();
    }
}

// @ 0x00eff280
void UI_s00ef_ee60::f_eff280(void* p)
{
    // Snapshot the current "active placement" pointer before the game-state calls.
    void* saved = *(void**)((char*)g_mgr + 0x10);

    pGame->F33BF0();
    pGame->F36450((int)p, 0, 0);

    // Assign p into g_mgr+0x0c with refcount bookkeeping.
    void** slot = &((MgrState*)g_mgr)->pC;
    void* old = *slot;
    if (p != old) {
        if (p) VCall0(p, 0x00);
        *slot = p;
        if (old) VCall0(old, 0x04);
    }

    // Whichever of the three tracked handles was active gets its lerp refreshed and is committed.
    Object1b0* o = (Object1b0*)pGame->p1b0;
    void* cur = *(void**)((char*)g_mgr + 0x20);
    if (saved == cur) {
        VCall0(cur, 0x58);
    } else {
        void* r5c = *(void**)((char*)g_mgr + 0x5c);
        if (saved == r5c) {
            ((RotationRing*)r5c)->SetTLerp(o->p4->f70);
            VCall0(r5c, 0x58);
        } else {
            void* r60 = *(void**)((char*)g_mgr + 0x60);
            if (saved == r60) {
                ((RotationRing*)r60)->SetTLerp(o->p4->f6c);
                VCall0(r60, 0x58);
            }
        }
    }

    ((MgrState*)g_mgr)->f68 = 1;
}

// @ 0x00eff360
void UI_s00ef_ee60::f_eff360(void* p)
{
    if (b5) {
        void* u = *(void**)((char*)g_mgr + 4);
        b5 = 0;
        f_eff230(u);
        return;
    }
    pGame->F33BF0();
    pGame->F36450(0, 0, p);
    f_eff230(p);
}

// @ 0x00eff3b0
void UI_s00ef_ee60::f_eff3b0()
{
    void* entry = FUN_00b18e00_s00ef_ee60(*(void**)((char*)g_mgr + 0xc));
    GObj* g = pGame;

    if (*(uint8_t*)((char*)entry + 0x6e) == 0) {
        g->F38330(1);
        g->F34560();

        // If the current placement object is the scenario-tutorial sentinel, tell the tutorial
        // controller that the placement finished.
        void* v = p10;
        if (v != 0 && *(int*)((char*)v + 0x54) == 0x5184ae0d) {
            void* ctx = *(void**)((char*)0x016c7aa4);
            ctx = *(void**)((char*)ctx + 0xd4);
            ((void (__thiscall*)(void*, int, int))0x00efbbe0)(ctx, 0xaa, 0xab);
        }
    } else {
        // 0x00f352e0 is a thiscall on the game object (it reads this->p1b0); the singleton drop
        // that follows is a plain cdecl with no arguments.
        ((void (__thiscall*)(void*))0x00f352e0)(g);
        ((void (__cdecl*)())0x00f32410)();
    }

    // Release the tracked handle.
    void* old = *(void**)((char*)g_mgr + 0xc);
    if (old) {
        *(void**)((char*)g_mgr + 0xc) = 0;
        VCall0(old, 0x04);
    }

    // Toggle the audio mute flag and drive the placement sound.
    g_016c7d24 = (g_016c7d24 == 0.0f) ? 1.0f : 0.0f;
    float level = g_016c7d24;

    void* at = EA_Audio_GetSystemAT();
    if (at) {
        VCall1(at, 0x38, 0x3cdd1a9);
        VCall2I(at, 0x40, 0x34753a7, 0xa984aa45);
        VCall2F(at, 0x3c, 0x34753aa, level);
        VCall0(at, 0x58);
    }
}

// @ 0x00eff4c0
void UI_s00ef_ee60::f_eff4c0(void* p, float f)
{
    GObj* g = pGame;
    void* r = g->F32790(p);
    void* obj = FUN_00b18e00_s00ef_ee60(p);

    OrientationState* s = ((Object1b0*)r)->p4;
    if (s->f64 > s->f60) {
        // t = clamp(f - 3, 0, 1); the object gets 3 + t, the ring and the sound get t.
        float t = f - 3.0f;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;

        ((void (__thiscall*)(void*, float))Vt(obj)[0x40 / 4])(obj, 3.0f + t);
        ((RotationRing*)*(void**)((char*)g_mgr + 0x5c))->SetTLerp(t);
        ((void (__cdecl*)(int, float))0x005ca880)(0xfa65b8cd, t);
    }
}

// @ 0x00eff590
void* UI_s00ef_ee60::f_eff590()
{
    char local10[8];
    char local1c[12];
    f_efc930();
    void* model = FUN_00b3d350_s00ef_ee60(local10, local1c);
    ((GObj*)model)->BSO(local10, local1c);
    void* r = pGame->F33640(p10);
    VObj_s00ef_ee60* o = (VObj_s00ef_ee60*)FUN_00b18e00_s00ef_ee60(r);
    int a, b;
    o->v38(&a);
    o->v3c(&b);
    o->v40(1.0f);
    return r;
}

// @ 0x00eff600
void UI_s00ef_ee60::f_eff600(int arg)
{
    if (g_016065f8 == 0)
        return;

    void* m = *(void**)&g_015ad298;
    if (VCallB(m, 0x38))
        return;

    // Lookup chain: the intermediate results are used unguarded, exactly as in the retail code.
    void* a = FUN_0067dd10();
    void* a2 = ((void* (__thiscall*)(void*))Vt(a)[0x50 / 4])(a);
    void* w = ((void* (__thiscall*)(void*))Vt(a2)[0x38 / 4])(a2);
    if (w == 0)
        return;
    if (((void* (__thiscall*)(void*, int))Vt(w)[0x0c / 4])(w, 0x11966ed) == 0)
        return;

    void* r = pGame->F329E0((void*)arg);
    if (r == 0)
        return;

    ((void (__thiscall*)(void*, void*))Vt(this)[0x20 / 4])(this, *(void**)r);

    void* b = FUN_0067dd10();
    void* b2 = ((void* (__thiscall*)(void*))Vt(b)[0x50 / 4])(b);
    void* w2 = ((void* (__thiscall*)(void*))Vt(b2)[0x38 / 4])(b2);
    if (w2 == 0)
        return;
    if (((void* (__thiscall*)(void*, int))Vt(w2)[0x0c / 4])(w2, 0x11966ed) == 0)
        return;

    FUN_00b18e00_s00ef_ee60(*(void**)r);
    FUN_00efccd0();
}

// @ 0x00eff6c0
void __cdecl f_eff6c0(void* obj, char flag)
{
    if (obj == 0)
        return;

    void* r = FUN_00ae66d0(obj);

    // Refresh the obj-side visual state, then commit (flag set) or drop (flag clear) the tracked
    // object in the manager's +0x08 slot.
    ((void (__thiscall*)(void*, char))Vt(obj)[0x28 / 4])(obj, flag);

    if (flag != 0) {
        void** slot = &((MgrState*)g_mgr)->p8;
        void* old = *slot;
        if (r != old) {
            if (r) VCall0(r, 0x00);
            *slot = r;
            if (old) VCall0(old, 0x04);
        }
    } else {
        void* cur = *(void**)((char*)g_mgr + 8);
        if (r == cur && cur != 0) {
            *(void**)((char*)g_mgr + 8) = 0;
            VCall0(cur, 0x04);
        }
    }

    // Toggle bit 3 of the render object's flag word.
    void* x = ((void* (__thiscall*)(void*))Vt(obj)[0xac / 4])(obj);
    if (x != 0) {
        if (flag != 0)
            *(int*)((char*)x + 4) |= 8;
        else
            *(int*)((char*)x + 4) &= ~8;
    }
}

// @ 0x00eff760
void __cdecl f_eff760(void* obj, char flag)
{
    if (obj == 0)
        return;
    void* m = *(void**)&g_015ad298;
    if (VCallB(m, 0x38))
        return;
    f_eff6c0(obj, flag);
}
