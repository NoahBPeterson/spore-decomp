// src/game/Spui/SPUIMainWin.cpp -- migrated from slice(s) s00815dd0, s00815420, s008143a0, s008133f0, s008124a0, s00809700 by tools/migrate/rewrite.py
// Object file: Spui/SPUIMainWin.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "cSPUILayoutCheat.h"
#include "EA/Text/FontServer.h"
#include "cSPUILayout.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void sOnEnterEscKeys(int a, int b, int c);

// ---- items of slice s00809700 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Msg {
    int a, b;        // +0, +4
    int type;        // +8
    int fieldC;      // +0xc
    int key;         // +0x10
    int field14;     // +0x14
};
extern "C" void sOnEnterEscKeys(int a, int b, int c);
// ---- items of slice s00809700 end

// ---- items of slice s008124a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*   SP_MessageServer();
struct Mouse;
struct Rect4f { float x0, y0, x1, y1; };
struct Rect4i { int x0, y0, x1, y1; };
struct Sub {
    virtual void   s00();
    virtual void   s01();
    virtual void   s02();
    virtual void   s03();
    virtual void   s04();
    virtual Mouse* s05();
    virtual void   s06();
    virtual void   s07();
    virtual void   s08();
    virtual void   s09();
    virtual void   s0a();
    virtual void   s0b();
    virtual void   s0c();
    virtual Rect4f* s0d();
};
struct Y {
    virtual void y00(); virtual void y01(); virtual void y02(); virtual void y03();
    virtual void y04(); virtual void y05(); virtual void y06(); virtual void y07();
    virtual void y08(int);          // 0x20
    virtual void y09(int);          // 0x24
    virtual bool y10(int, int);     // 0x28
    virtual bool y11(int, int);     // 0x2c
};
struct X {
    virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03();
    virtual void x04(); virtual void x05(); virtual void x06(); virtual void x07();
    virtual void x08(); virtual void x09(); virtual void x0a();
    virtual Y*   x0b();
    virtual void x0c(); virtual void x0d();
    virtual Y*   x0e();
    virtual void x0f(); virtual void x10(); virtual void x11(); virtual void x12();
    virtual void x13();
    virtual X*   x14();
};
struct W9 {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9();
};
struct Canvas {
    virtual void  c00(); virtual void  c01(); virtual void  c02(); virtual void  c03();
    virtual void  c04(); virtual void  c05(); virtual void  c06(); virtual void  c07();
    virtual void  c08(); virtual void  c09(); virtual void  c10(); virtual void  c11();
    virtual void  c12(); virtual void  c13(); virtual void  c14(); virtual void* c15(void*);
    virtual void  c16(); virtual void  c17(); virtual void  c18(); virtual void  c19();
    virtual void  c20(); virtual void  c21(); virtual void  c22(); virtual void  c23();
    virtual void  c24(); virtual void  c25(); virtual void  c26(); virtual void  c27();
    virtual void  c28(); virtual void  c29(); virtual void  c30(); virtual void  c31(int, int);
};
extern "C" Canvas* SP_Canvas();
#define sMouseXScale (*(float*)0x15451e8)
#define sMouseYScale (*(float*)0x15451ec)
struct MainWin {
    char pad0[0x4];
    Sub  sub;                   // +0x4
    char pad1[0x260 - 0x4 - sizeof(Sub)];
    W9*  mp260;                 // +0x260
    char pad2[0x268 - 0x260 - 4];
    X*   mp268;                 // +0x268
    X*   mp26c;                 // +0x26c
    char pad3[0x284 - 0x26c - 4];
    uint8_t b284, b285, b286;   // +0x284
    char pad4[0x28d - 0x287];
    uint8_t b28d;               // +0x28d
    char pad5[0x2dc - 0x28e];
    uint8_t b2dc;               // +0x2dc

    void BaseSetup();
    unsigned GetFlags();
    void Teardown(int);
    bool BuildMouseMsg(const void* in, void* out);
    void OnMouse(bool active);
    void UpdateMouseScale();
    void SetFocusObj(X* p);
    void ApplyToFocus(int arg);
    bool RouteKey(int a, int key, int mod);
};
struct Mouse {
    void GetPositionStatic(int, int);
};
struct Property {
    char pad[0x12];
    uint16_t type;      // +0x12
    int* GetInt();
};
struct cDirectPropertyList {
    virtual bool p0(void*); virtual bool p1(void*); virtual bool p2(void*);
    virtual bool p3(void*); virtual bool p4(void*); virtual bool p5(void*);
    virtual bool p6(void*); virtual bool p7(void*); virtual bool p8(void*);
    virtual bool GetProp(uint32_t id, Property** out);
};
extern cDirectPropertyList* g_AppProperties;             // 0x15fd918
void __cdecl SetDropShadowQuality(int q, int level);     // 0x96e500
// ---- items of slice s008124a0 end

// ---- items of slice s008133f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl GetManager();
static inline void** Vtbl(void* o) { return *(void***)o; }
void* __cdecl ZoneObjectNew(int size, const char* name, int a, int b, int c, int d); // 0x926020
void* __cdecl StringManCtor(void*, void*);    // 0x999820
void  __cdecl FUN_00572680(void*);
void  __cdecl FUN_00999930();
void  __cdecl FUN_00999780(void*);
void  __cdecl FUN_00999790(void*);
struct Ref {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
    virtual void r08(); virtual void r09(); virtual void r0a(); virtual void r0b();
    virtual void r0c(); virtual void r0d(); virtual void r0e(); virtual void r0f();
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13();
    virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17();
    Ref* Ctor997f30();
    Ref* Ctor999c20();
};
struct Mgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m0a(); virtual void m0b();
    virtual void m0c(); virtual void m0d(); virtual void m0e(); virtual void m0f();
    virtual void m10(); virtual void m11();
};
struct Y3 {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a0a(); virtual void a0b();
    virtual void a0c();
    virtual bool a0d(float, float, int);   // 0x34
    virtual bool a0e(float, float, int);   // 0x38
};
struct X3 {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b0a();
    virtual Y3*  b0b();                     // 0x2c
    virtual void b0c(); virtual void b0d();
    virtual Y3*  b0e();                     // 0x38
};
struct Y4 {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c0a(); virtual void c0b();
    virtual void c0c(); virtual void c0d();
    virtual bool c0e(int, float, float, int);  // 0x38
    virtual bool c0f(int, float, float, int);  // 0x3c
};
struct X4 {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d0a();
    virtual Y4*  d0b();                     // 0x2c
    virtual void d0c(); virtual void d0d();
    virtual Y4*  d0e();                     // 0x38
};
struct MainWin_s0081_33f0;
struct WinBase { void SetArea(int); };
struct WinSub : WinBase { void SetAreaNotify(int a); };
struct MainWin_s0081_33f0 {
    char pad0[0x4];
    WinSub win;                 // +0x4
    char pad1[0x34 - 0x4 - sizeof(WinSub)];
    Ref*  mp34;                 // +0x34
    char pad2[0x218 - 0x38];
    uint8_t b218;               // +0x218
    int   i21c;                 // +0x21c
    uint8_t b220;               // +0x220
    uint8_t b221, b222, b223;   // +0x221..0x223
    char pad3[0x244 - 0x224];
    void* mp244;                // +0x244
    char pad4[0x268 - 0x248];
    void* mp268;                // +0x268
    void* mp26c;                // +0x26c
    char pad5[0x287 - 0x270];
    int   i287;                 // +0x287
    uint8_t b28b;               // +0x28b
    uint8_t b28c;               // +0x28c
    uint8_t b28d;               // +0x28d
    void* mp290;                // +0x290
    void* mp294;                // +0x294
    void* mp298;                // +0x298
    void* mp29c;                // +0x29c

    void UpdateMouseScale();       // 0x8131b0
    bool FocusKey2(float a, float b, int c);         // 0x813630
    bool FocusKey4(float a, float b, int c, int d);  // 0x8136b0
    bool InitHitMaskFactory();     // 0x813760
    bool InitStringFactories();    // 0x8137f0
    bool ShutdownStringFactories();// 0x8138e0
    bool InitTitleScreen();        // 0x813980
    void DoMessage(int* msg);      // 0x813e70
    bool KeyRouted(int a, int b, int c, int d);   // 0x8133f0
    bool FocusInput(int a, int b, int c, int d);  // 0x813550
    void Dtor();                   // 0x813ca0
};
Ref* Ctor997f30(Ref*);   // 0x997f30
Ref* Ctor999c20(Ref*);   // 0x999c20
bool MainWin_s0081_33f0::KeyRouted(int a, int b, int c, int d) {
    if (b28d) return true;
    if (mp268) {
        // capture / release then route
    }
    return false;
}
bool MainWin_s0081_33f0::FocusInput(int a, int b, int c, int d) {
    if (b28d) return true;
    if (mp268) {
        void* q = ((void*(__thiscall*)(void*))Vtbl(mp268)[0x2c / 4])(mp268);
        if (q) return true;
    }
    return false;
}
void* __cdecl CtorConnectionDialog(void*);        // 0x810000
bool  __cdecl LayoutInit(void*, const wchar_t*, int, int, int); // 0x812160
void* __cdecl LayoutFindByID(void*, int, int);    // 0x8105b0
void  __cdecl GetMainWindowArea(void*);           // 0x805ea0
void  __cdecl SP_Pollinator(void*, void*);        // 0x806d10
void* __cdecl AddBoundingBox(void*, int, int);    // 0x67cad0
void  __cdecl SP_Renderer(void*, int, int);       // 0x80d710
void __cdecl SetBoolProperty(void*);            // 0x93a2e0
void __cdecl FUN_008e2b20(void*);
void __cdecl FUN_00962740(void*);
void  __cdecl StopwatchCtor(void*, int, int);   // 0x93a560
void* __cdecl CtorWindowPlaceholder(void*);     // 0x962a10 UI::Window::Window
static void ReleaseSlot(void* p, int slot) {
    if (p) ((void(__thiscall*)(void*))Vtbl(p)[slot / 4])(p);
}
// ---- items of slice s008133f0 end

// ---- items of slice s008143a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_AppSystem();
extern "C" void* __cdecl SP_MovieSystem();
struct Elem {
    virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
    virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
    virtual void e08(); virtual void e09();
    void OnWindowClosed();   // 0x816990
};
struct Vec {
    void* mBegin;   // +0
    void* mEnd;     // +4
    void* mCap;     // +8
    void erase(void* first, void* last);
    void Grow(void* pos, void** val);  // 0x814a30
};
void __cdecl CopyImpl(void* first, void* last, void* dst);   // 0x6782c0
struct WinSub_s0081_43a0 : WinBase {};
struct MainWin_s0081_43a0 {
    char pad0[0x4];
    WinSub_s0081_43a0 win;                 // +0x4
    char pad1[0x220 - 0x4 - sizeof(WinSub_s0081_43a0)];
    uint8_t b220;               // +0x220
    uint8_t b221;               // +0x221
    char pad2[0x268 - 0x222];
    void* mp268;                // +0x268
    void* mp26c;                // +0x26c
    char pad3[0x28d - 0x270];
    uint8_t b28d;               // +0x28d
    char pad4[0x2a8 - 0x28e];
    Vec   mVec;                 // +0x2a8

    void OnKeyDown();                  // 0x8143a0
    void MovieToggle();                // 0x8145d0
    bool SaveReadme(int);              // 0x8148b0
    bool KeyHandler2(int a, int key, int mod);  // 0x814d50
    void HandleMessage(unsigned id, int* msg);  // 0x814e40
    void RemoveElem(int val);          // 0x815310
    void AddElem(Elem* p);             // 0x815370
    void CloseAll();                   // 0x8153e0
};
struct Y2 {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08();
    virtual bool a09(int, int);   // 0x24
    virtual bool a0a(int, int);   // 0x28
};
struct X2 {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
    virtual void b08(); virtual void b09(); virtual void b0a();
    virtual Y2*  b0b();           // 0x2c
    virtual void b0c(); virtual void b0d();
    virtual Y2*  b0e();           // 0x38
};
void* __cdecl FUN_0067de00();
void __cdecl FUN_0067dd50();
void* __cdecl FUN_00688cd0();
bool __cdecl sOnEnterEscKeys_s0081_43a0(int, int, int);   // 0x80a310
// ---- items of slice s008143a0 end

// ---- items of slice s00815420 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SP_ConfigManager();
extern "C" void* __cdecl SP_WindowManager();
extern "C" void* __cdecl EA_Text_GetFontServer(int);
extern "C" void* __cdecl EA_Text_GetStyleManager(int);
extern "C" void* __cdecl FUN_00805510(int);
extern void* g_164d348;   // 0x164d348
void* __cdecl EAlloc(int size, int tag, int a, int b, int c, int d);   // 0xf473a0
void  __cdecl ArgScript_Output(void* parser, const char* fmt);          // 0x841000
struct Inner { void Method(int, int); };   // 0x83b9d0
struct Outer {
    char pad0[0x4];
    int f4;                 // +0x4
    char pad1[0x10 - 0x8];
    Inner inner;            // +0x10
    void Wrap(int);         // 0x815b30
    void ExecuteColor(int); // 0x815a50
    char pad2[0xd8 - 0x10 - sizeof(Inner)];
    uint8_t bD8;            // +0xd8
};
void  __cdecl cString_SetColorLocalized(int);   // 0x6b5030
struct Mgr_s0081_5420 {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m0a();
    virtual void v2c(int, int);         // 0x2c
    virtual int  v30(int);              // 0x30
    virtual void p34(); virtual void p38();
    virtual void v3c();                 // 0x3c
};
struct Args {
    void MainArguments(void*, int, int);
};
struct Cheat {
    char pad0[0x4];
    void* mParser;          // +0x4
    void Execute(Args* args);   // 0x815990
};
struct FontServer {
    virtual void f00(); virtual void f04();
    virtual void f08(int, int);
    virtual void f0c(); virtual void f10(); virtual void f14(); virtual void f18();
    virtual void f1c(); virtual void f20(); virtual void f24(); virtual void f28();
    virtual void f2c(); virtual void f30(); virtual void f34();
    virtual void f38(const wchar_t*, const wchar_t*);
    void* Init(void*);
};
struct StyleManager {
    void* Init(void*);
};
void __cdecl FUN_00885b00(void*);   // 0x885b00
void __cdecl FUN_00885af0(void*);   // 0x885af0
bool __cdecl LoadTextStyles(int, int);   // 0x815bd0
void __cdecl EastlDealloc(void*);          // 0xf47380
struct HashtableStub { void DoFreeNodes(void** buckets, unsigned n); };
struct TextStyleReaderStub { void Dtor(); };
// ---- items of slice s00815420 end

// ---- items of slice s00815dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00956d90();
extern "C" void  FUN_0096ef80();
extern "C" void  FUN_0082f760();
extern "C" void  FUN_0067cba0(void*);
extern "C" void  FUN_0067cbb0(void*);
extern "C" void  FUN_0067cbd0(void*);
extern "C" void  FUN_00957f40(void*);
extern "C" int   FUN_0067cab0();
extern "C" void  FUN_008085d0(void*, void*, int, int, void*);
extern "C" void  FUN_008129c0();       // RegisterLayoutCheat
extern "C" void* FUN_00f473a0(unsigned int, const char*, int, int, int, int);  // operator new (heap)
extern "C" void* FUN_00926020(unsigned int, const char*, int, int, int, int);  // ZoneObject::operator new
extern "C" void  FUN_00813b20();       // cSPUITooltipManager::Init
extern "C" void  FUN_00813120();
extern "C" void  FUN_008005f0();       // UTFWin::RegisterUIBehaviors
extern "C" void* FUN_006895b0();
extern "C" void* FUN_0067dcc0();       // SP::MessageServer
extern "C" void* FUN_0067dcd0();       // GetManager
extern "C" void* FUN_0067de20();       // SP::CheatManager
extern "C" void* FUN_0067de40();
extern "C" void* FUN_0067dce0();
extern "C" void* FUN_0067caa0();       // SP::WindowManager
extern "C" void* FUN_0080fee0();
extern "C" char  FUN_0080ff20();
extern "C" void  FUN_0080a700();       // cSPUIImageAtlasMap::Init
extern "C" void  FUN_007f4850();
extern "C" bool  FUN_006ab760(const void* str, const wchar_t* lit);
extern "C" void  FUN_00989650(void (*)());
extern "C" void  FUN_006b5030(int);
extern "C" void  FUN_00813c60();
extern "C" void  FUN_00812c90();
extern "C" void  FUN_00812d00();
extern "C" void  FUN_0083bcd0(void* spec, ...);
extern float g_015451e8, g_015451ec;     // mouse scale
typedef unsigned int      u32;
typedef unsigned char     u8;
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void  Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void  Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void  Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
struct RawObj {
    void* Fn958cf0();            // 0x00958cf0 WindowMgr ctor (size 0x838)
    void* Fn80edb0();            // 0x0080edb0 LayerManager ctor (0x98)
    void* Fn8352d0();            // 0x008352d0 TooltipManager ctor (0x30)
    void* Fn999520();            // 0x00999520 SerializationService ctor (0x34)
    void* Fn833790();            // 0x00833790 (0xc)
    void* Fn8320d0();            // 0x008320d0 cSPUIDebugConsole ctor (0x214)
    void* Fn997b60();            // 0x00997b60 (0x20)
    void* Fn998df0(void* wm);    // 0x00998df0 (0x98)
    void  Fn811f20();            // 0x00811f20 cSPUILayoutManager ctor (0x44)
    void* Fn8025e0();            // 0x008025e0 cSPUICursorManager ctor (0x5c)
    void* Fn81e2b0();            // 0x0081e2b0 PropertyEditor ctor (0x14)
    void* Fn803020();            // 0x00803020 cSPUIStringBinder ctor (0x50)
    void* Fn810000();            // 0x00810000 cConnectionDialog ctor (0x18)
    void* Fn817a40();            // 0x00817a40 (0x88)
    void  Fn83c800();            // 0x0083c800 ArgScript command base ctor
    void  Fn83a9f0(int);         // 0x0083a9f0 cArgumentSpec ctor
    void  Fn80f530();            // 0x0080f530 LayerManager::Init
    void  Fn835610();            // 0x00835610 TooltipManager::LoadProps
    void  Fn802160();            // 0x00802160 cursor AddStandardCursors
    void  Fn823a00();            // 0x00823a00 PropertyEditor::Init
    void  Fn802cd0();            // 0x00802cd0 console Init
    void  Fn802a20(int);         // 0x00802a20
    void  Fn802a30(int);         // 0x00802a30 console Show
    void  Fn812160(const wchar_t*, u32, int, u32); // 0x00812160 cSPUILayout::Init
    void  Fn810590(int);         // 0x00810590 SetVisibility
    void* Fn8105b0(u32, int);    // 0x008105b0 FindWindowByID
    void  Fn8178b0(int);         // 0x008178b0
    void  Fn8115a0();            // 0x008115a0 cSPUILayoutManager::InitMessaging
    int   Fn92b300(const wchar_t*, int, int, int); // 0x0092b300 EA::CommandLine::FindSwitch
};
extern "C" void* FUN_0067dd50_s0081_5dd0();
extern u32 g_01545188, g_01545198, g_0154519c;
extern RawObj* g_015fd920;               // command-line object
extern u8 g_0164d211;                    // zh-cn flag
class cSPUIMainWin { public:
    char  pad_00[4];
    u32   sub4_vt;
    char  pad_08[0x214 - 8];
    u32   listener;       // +0x214 (message-listener subobject)
    bool  mInitialized;   // +0x218
    char  pad_219[3];
    u8    flags21c;       // +0x21c
    char  pad_21d[0x260 - 0x21d];
    void* mpWindowMgr;    // +0x260
    void* mpSerial;       // +0x264
    char  pad_268[0x270 - 0x268];
    void* mpLayer;        // +0x270
    void* mpTooltip;      // +0x274
    char  pad_278[0x27c - 0x278];
    void* mpMsgBox;       // +0x27c
    void* mpStringMgr;    // +0x280
    char  pad_284[0x2a4 - 0x284];
    void* mpCursor;       // +0x2a4
    char  pad_2a8[0x2d0 - 0x2a8];
    void* mpPropEditor;   // +0x2d0
    bool  mPropEditorInit;// +0x2d4
    char  pad_2d5[3];
    void* mpDebugConsole; // +0x2d8

    bool Init();
    void InitFonts();             // 0x00815ce0
    void InitHitMaskFactory();    // 0x00813760
    void InitStringFactories();   // 0x008137f0
    void UpdateMouseScale();      // 0x008131b0
    void InitTitleScreen();       // 0x00813980
};
static inline void Vv3(void* p, int off, int a, int b, int c) {
    ((void(__thiscall*)(void*, int, int, int))(*(void***)p)[off / 4])(p, a, b, c);
}
static __forceinline void AssignRef(void** slot, void* nv, int addIdx, int relIdx) {
    void* old = *slot;
    if (nv != old) {
        if (nv) Vv0(nv, addIdx);
        *slot = nv;
        if (old) Vv0(old, relIdx);
    }
}
#define NEWOBJ(var, size, name, ctorcall) \
    do { void* _m = FUN_00f473a0(size, name, 0, 0, 0, 0); var = _m ? ((RawObj*)_m)->ctorcall : 0; } while (0)
// ---- items of slice s00815dd0 end

// @ 0x0080a1a0
void sOnEnterEscKeys()
{ /* not reconstructed */ }






// @ 0x0080a320
bool __stdcall FUN_0080a320(void* a, Msg* m)
{
    switch (m->type) {
    case 1:
        if (m->fieldC == 0 && (m->key == 0x1b || m->key == 0xd) && m->field14 == 0)
            sOnEnterEscKeys(0, m->key, 0);
        return true;
    case 2:
    case 5:
        return true;
    case 10:
        return false;
    default:
        return false;
    }
}





// @ 0x008130c0
void MainWin::OnMouse(bool active)
{
    if (active) {
        if (b2dc) return;
        b2dc = 1;
        void* s = SP_MessageServer();
        typedef void (__thiscall *MsgSendFn)(void*, unsigned, int, int, int);
        ((MsgSendFn*)(*(void**)s))[0x18 / 4](s, 0x61205e6, 0, 0, 0);
        return;
    }
    if (sub.s05()) {
        Mouse* m = sub.s05();
        m->GetPositionStatic(0, 0);
    }
}





// @ 0x00813120
void sInitDropShadowQuality()
{
    cDirectPropertyList* props = g_AppProperties;
    Property* p;
    int q;
    if (props && props->GetProp(0xe30a842c, &p) && p->type == 9)
        q = *p->GetInt();
    SetDropShadowQuality(q, 0);
    if (props && props->GetProp(0xa5bbb508, &p) && p->type == 9)
        q = *p->GetInt();
    SetDropShadowQuality(q, 1);
}





// @ 0x008131b0
void MainWin::UpdateMouseScale()
{
    Rect4i local;
    Canvas* c = SP_Canvas();
    Rect4i* r = (Rect4i*)c->c15(&local);
    sMouseXScale = (float)(r->x1 - r->x0);
    if (sMouseXScale > 0.0f) {
        Rect4f* s = sub.s0d();
        sMouseXScale = (s->x1 - s->x0) / sMouseXScale;
    }
    Canvas* c2 = SP_Canvas();
    Rect4i* r2 = (Rect4i*)c2->c15(&local);
    sMouseYScale = (float)(r2->y1 - r2->y0);
    if (sMouseYScale > 0.0f) {
        Rect4f* s = sub.s0d();
        sMouseYScale = (s->y1 - s->y0) / sMouseYScale;
    }
}





// @ 0x00813260
void MainWin::SetFocusObj(X* p)
{
    X* old = mp268;
    if (p != old) {
        if (p) p->x00();
        mp268 = p;
        if (old) old->x01();
    }
    if (mp268 != 0) {
        X* q = mp268->x14();
        X* o = mp26c;
        if (q != o) {
            if (q) q->x02();
            mp26c = q;
            if (o) o->x03();
        }
    } else {
        X* o = mp26c;
        if (o) { mp26c = 0; o->x03(); }
    }
}





// @ 0x00813300
void MainWin::ApplyToFocus(int arg)
{
    X* p = mp268;
    if (p && p->x0b()) {
        p->x0b()->y08(arg);
    }
    X* o = mp26c;
    if (o && p && p->x14()) {
        o->x0e()->y09(arg);
    }
}





// @ 0x00813370
bool MainWin::RouteKey(int, int key, int mod)
{
    if (b28d) return true;
    if (mod == 0 && (key == 0x43 || key == 0x56)) return true;
    if (mp268) {
        if (mp268->x0b()->y10(key, mod)) return true;
    }
    if (mp26c) {
        if (mp26c->x0e()->y11(key, mod)) return true;
    }
    return false;
}




// @ 0x00813630
bool MainWin_s0081_33f0::FocusKey2(float a, float b, int c)
{
    X3* p = (X3*)mp268;
    if (p && p->b0b()->a0d(a, b, c)) return true;
    X3* q = (X3*)mp26c;
    if (q && q->b0e()->a0e(a, b, c)) return true;
    return false;
}




// @ 0x008136b0
bool MainWin_s0081_33f0::FocusKey4(float a, float b, int c, int d)
{
    X4* p = (X4*)mp268;
    if (p && p->d0b()->c0e(d, a, b, c)) return true;
    X4* q = (X4*)mp26c;
    if (q && q->d0e()->c0f(d, a, b, c)) return true;
    return false;
}




// @ 0x00813740
void WinSub::SetAreaNotify(int a)
{
    SetArea(a);
    ((MainWin_s0081_33f0*)((char*)this - 4))->UpdateMouseScale();
}




// @ 0x00813760
bool MainWin_s0081_33f0::InitHitMaskFactory()
{
    Mgr* m = (Mgr*)GetManager();
    if (m) {
        Ref* p = (Ref*)ZoneObjectNew(8, "UI/HitMaskFactory", 0, 0, 0, 0);
        if (p) p = p->Ctor997f30();
        else p = 0;
        Ref* old = (Ref*)mp298;
        if (p != old) {
            if (p) p->r01();
            mp298 = p;
            if (old) old->r02();
        }
        if (mp298) {
            ((Ref*)mp298)->r04();
            ((void(__thiscall*)(Mgr*, int, void*, int))Vtbl(m)[0x44 / 4])(m, 1, mp298, 0);
        }
    }
    return true;
}




// @ 0x008137f0
bool MainWin_s0081_33f0::InitStringFactories()
{
    Mgr* m = (Mgr*)GetManager();
    if (m) {
        Ref* p = (Ref*)ZoneObjectNew(0x10, "UI/FactoryStringTableXml", 0, 0, 0, 0);
        if (p) p = p->Ctor999c20();
        else p = 0;
        Ref* old = (Ref*)mp290;
        if (p != old) {
            if (p) p->r01();
            mp290 = p;
            if (old) old->r02();
        }
        if (mp290) {
            ((void(__thiscall*)(Mgr*, int, void*, int))Vtbl(m)[0x44 / 4])(m, 1, mp290, 0);
            char local[8];
            ((void(__thiscall*)(void*, void*, int))Vtbl(mp290)[0x2c / 4])(mp290, local, 8);
            void* sm = ZoneObjectNew(0x14, "UI/StringMan", 0, 0, 0, 0);
            if (sm) sm = StringManCtor(sm, m);
            else sm = 0;
            FUN_00572680(sm);
            FUN_00999930();
            FUN_00999780(*(void**)((char*)this + 0x29c));
        }
    }
    return true;
}




// @ 0x008138e0
bool MainWin_s0081_33f0::ShutdownStringFactories()
{
    Mgr* m = (Mgr*)GetManager();
    if (mp29c) {
        FUN_00999780(0);
        FUN_00999790(mp29c);
        Ref* p = (Ref*)mp29c;
        if (p) {
            mp29c = 0;
            int n = *(int*)((char*)p + 4);
            *(int*)((char*)p + 4) = n - 1;
            if (n - 1 == 0) {
                *(int*)((char*)p + 4) = 1;
                ((void(__thiscall*)(Ref*, int))Vtbl(p)[0])(p, 1);
            }
        }
    }
    if (m && mp290) {
        ((void(__thiscall*)(Mgr*, int, void*, int))Vtbl(m)[0x44 / 4])(m, 0, mp290, 0);
        ((Ref*)mp290)->r05();
        Ref* p = (Ref*)mp290;
        if (p) { mp290 = 0; p->r02(); }
    }
    return true;
}




// @ 0x00813980
bool MainWin_s0081_33f0::InitTitleScreen()
{
    void* p = ZoneObjectNew(0x18, "UI/TitleScreen", 0, 0, 0, 0);
    if (p) p = CtorConnectionDialog(p);
    else p = 0;
    void* old = *(void**)((char*)this + 0x244);
    if (p != old) {
        if (p) ((Ref*)p)->r01();
        *(void**)((char*)this + 0x244) = p;
        if (old) ((Ref*)old)->r02();
    }
    void* layout = *(void**)((char*)this + 0x244);
    LayoutInit(layout, L"TitleScreen", 0x40464100, 1, 0x5b598fa);
    if (LayoutFindByID(layout, 0x362c790, 1)) {
        int area[4];
        GetMainWindowArea(area);
        void* w = LayoutFindByID(layout, 0x362c790, 1);
        ((void(__thiscall*)(void*, void*))Vtbl(w)[0x60 / 4])(w, area);
        void* w2 = LayoutFindByID(layout, 0x362d0b0, 1);
        float f = ((float(__thiscall*)(void*))Vtbl(w2)[0x34 / 4])(w2);
        (void)f;
        SP_Pollinator(w2, area);
        void* w3 = LayoutFindByID(layout, 0x362c790, 1);
        void* bb = AddBoundingBox(w3, 1, 1);
        SP_Renderer(bb, 1, 1);
    }
    return true;
}




// @ 0x00813c20
int LowerBoundUShort(int a, int b, unsigned short* key)
{
    int n = b - a >> 1;
    if (n > 0) {
        int step;
        do {
            step = n >> 1;
            if (!(*key < *(unsigned short*)(a + step * 2))) {
                a = a + 2 + step * 2;
                n = n + (-1 - step);
            } else {
                n = step;
            }
        } while (n > 0);
    }
    return a;
}




// @ 0x00813ca0
void MainWin_s0081_33f0::Dtor()
{
    char* t = (char*)this;
    *(uint32_t*)(t + 0x0) = 0x1418838;
    *(uint32_t*)(t + 0x4) = 0x1418718;
    *(uint32_t*)(t + 0x20c) = 0x1418708;
    *(uint32_t*)(t + 0x214) = 0x14186f8;
    SetBoolProperty(t + 0x228);
    ReleaseSlot(*(void**)(t + 0x2d8), 4);
    ReleaseSlot(*(void**)(t + 0x2d0), 0xc);
    FUN_008e2b20(t + 0x2a8);
    ReleaseSlot(*(void**)(t + 0x2a4), 8);
    ReleaseSlot(*(void**)(t + 0x2a0), 0xc);
    // mp29c refcount release
    void* p = *(void**)(t + 0x29c);
    if (p) {
        int n = *(int*)((char*)p + 4);
        *(int*)((char*)p + 4) = n - 1;
        if (n - 1 == 0) {
            *(int*)((char*)p + 4) = 1;
            ((void(__thiscall*)(void*, int))Vtbl(p)[0])(p, 1);
        }
    }
    ReleaseSlot(*(void**)(t + 0x298), 8);
    ReleaseSlot(*(void**)(t + 0x294), 8);
    ReleaseSlot(*(void**)(t + 0x290), 8);
    ReleaseSlot(*(void**)(t + 0x280), 4);
    ReleaseSlot(*(void**)(t + 0x27c), 8);
    ReleaseSlot(*(void**)(t + 0x274), 8);
    ReleaseSlot(*(void**)(t + 0x26c), 0xc);
    ReleaseSlot(*(void**)(t + 0x268), 4);
    ReleaseSlot(*(void**)(t + 0x244), 8);
    *(uint32_t*)(t + 0x214) = 0x13eb394;
    *(uint32_t*)(t + 0x20c) = 0x13ec458;
    FUN_00962740(t);
}




// @ 0x008141b0
void* MainWin_Ctor(MainWin_s0081_33f0* self)
{
    char* t = (char*)self;
    // base Window ctor (relocation)
    CtorWindowPlaceholder(t);
    *(uint32_t*)(t + 0x20c) = 0x13ec458;
    *(uint32_t*)(t + 0x210) = 0;
    *(uint32_t*)(t + 0x214) = 0x13eb384;
    *(uint32_t*)(t + 0x0) = 0x1418838;
    *(uint32_t*)(t + 0x4) = 0x1418718;
    *(uint32_t*)(t + 0x20c) = 0x1418708;
    *(uint32_t*)(t + 0x214) = 0x14186f8;
    *(uint8_t*)(t + 0x218) = 0;
    *(uint32_t*)(t + 0x21c) = 0;
    *(uint8_t*)(t + 0x220) = 1;
    *(uint8_t*)(t + 0x221) = 0;
    *(uint8_t*)(t + 0x222) = 0;
    *(uint8_t*)(t + 0x223) = 1;
    StopwatchCtor(t + 0x228, 5, 0);
    for (int off = 0x240; off <= 0x280; off += 4) *(uint32_t*)(t + off) = 0;
    *(uint8_t*)(t + 0x284) = 0;
    *(uint8_t*)(t + 0x285) = 0;
    *(uint8_t*)(t + 0x286) = 0;
    *(uint8_t*)(t + 0x28d) = 0;
    for (int off = 0x290; off <= 0x2a4; off += 4) *(uint32_t*)(t + off) = 0;
    return self;
}



// @ 0x008143a0
void MainWin_s0081_43a0::OnKeyDown()
{
    void* p = FUN_0067de00();
    if (!p) return;
    FUN_0067dd50();
    // heavy Date/time + sprintf naming flow summarised
}



// @ 0x008145d0
void MainWin_s0081_43a0::MovieToggle()
{
    void* ms = SP_MovieSystem();
    if (!ms) return;
    if (((bool(__thiscall*)(void*))Vtbl(ms)[0x30 / 4])(ms)) {
        ((void(__thiscall*)(void*))Vtbl(ms)[0x38 / 4])(ms);
        return;
    }
    // movie-area property flow summarised
}



// @ 0x008148b0
bool MainWin_s0081_43a0::SaveReadme(int mode)
{
    if (mode != 0) return false;
    void* f = FUN_00688cd0();
    (void)f;
    return true;
}



// @ 0x008149c0
void* StringConstruct(void* self, void* str, unsigned idx)
{
    return self;
}



// @ 0x00814b80
void sTextStyleCallback(int n, void* args, void* p)
{
    if (n < 2) return;
}



// @ 0x00814d50
bool MainWin_s0081_43a0::KeyHandler2(int a, int key, int mod)
{
    if (b28d) return true;
    if ((key == 0x1b || key == 0xd) && mod == 0 && sOnEnterEscKeys_s0081_43a0(a, key, 0)) return true;
    if (key == 0x56) {
        if (mod == 0) { MovieToggle(); return true; }
    } else if (key == 0x70) {
        void* as = SP_AppSystem();
        if (((bool(__thiscall*)(void*))Vtbl(as)[0x54 / 4])(as) && SaveReadme(mod)) return true;
    }
    if (b220) {
        if (mp268) {
            X2* p = (X2*)mp268;
            if (p->b0b()->a09(key, mod)) return true;
        }
        if (mp26c) {
            X2* q = (X2*)mp26c;
            if (q->b0e()->a0a(key, mod)) return true;
        }
    }
    if (key == 0x43 && mod == 0) { OnKeyDown(); return true; }
    return false;
}



// @ 0x00814e40
void MainWin_s0081_43a0::HandleMessage(unsigned id, int* msg)
{
    (void)id; (void)msg;
}



// @ 0x00815310
void MainWin_s0081_43a0::RemoveElem(int val)
{
    Vec* v = &mVec;
    Elem** pi = (Elem**)v->mBegin;
    Elem** end = (Elem**)v->mEnd;
    for (; pi != end; ++pi) {
        if ((int)*pi == val) {
            if (pi + 1 < (Elem**)v->mEnd) CopyImpl(pi + 1, v->mEnd, pi);
            v->mEnd = (char*)v->mEnd - 4;
            Elem* last = *(Elem**)v->mEnd;
            if (last) last->e01();
            return;
        }
    }
}



// @ 0x00815370
void MainWin_s0081_43a0::AddElem(Elem* p)
{
    b221 = 0;
    if (p) p->e00();
    Elem* tmp = p;
    if (mVec.mEnd < mVec.mCap) {
        Elem** slot = (Elem**)mVec.mEnd;
        mVec.mEnd = (char*)mVec.mEnd + 4;
        if (slot) {
            *slot = p;
            if (p) p->e00();
        }
    } else {
        mVec.Grow(mVec.mEnd, (void**)&tmp);
    }
    if (tmp) tmp->e01();
}



// @ 0x008153e0
void MainWin_s0081_43a0::CloseAll()
{
    Vec* v = &mVec;
    Elem** i = (Elem**)mVec.mBegin;
    Elem** end = (Elem**)mVec.mEnd;
    for (; i != end; ++i) (*i)->OnWindowClosed();
    v->erase(mVec.mBegin, mVec.mEnd);
}


// @ 0x00815420
void __cdecl FUN_00815420_partial()
{
}


// @ 0x00815990
void Cheat::Execute(Args* args)
{
    int captured;
    args->MainArguments(&captured, 0, 0x7fffffff);
    Mgr_s0081_5420* cm = (Mgr_s0081_5420*)SP_ConfigManager();
    int v = cm->v30(0x631621a);
    cm = (Mgr_s0081_5420*)SP_ConfigManager();
    cm->v2c(0x631621a, v == 0);
    cm = (Mgr_s0081_5420*)SP_ConfigManager();
    cm->v3c();
    if (v != 0) {
        ArgScript_Output(mParser, "capture UI is off\n");
        return;
    }
    ArgScript_Output(mParser, "capture UI is on (captures at game resolution)\n");
}


// @ 0x00815a50
void Outer::ExecuteColor(int arg)
{
    inner.Method(arg, f4);
    void* wm = SP_WindowManager();
    if (wm) {
        ((void(__thiscall*)(void*, int))Vtbl(wm)[0x90 / 4])(wm, bD8);
        cString_SetColorLocalized(bD8);
    }
}


// @ 0x00815aa0
void HashtableStub::DoFreeNodes(void** buckets, unsigned n)
{
    char* s = (char*)this;
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)buckets[i];
        while (node) {
            char* next = *(char**)(node + 0x24);
            void* str = *(void**)node;
            int cap = *(int*)(node + 8) - *(int*)node;
            if (cap > 1 && str && str != *(void**)(node + 0x10))
                EastlDealloc(str);
            if (node != *(char**)(s + 0x30)) {
                if (node < *(char**)(s + 0x24) || node >= *(char**)(s + 0x28))
                    EastlDealloc(node);
                else { *(void**)node = *(void**)(s + 0x1c); *(void**)(s + 0x1c) = node; }
            }
            node = next;
        }
        buckets[i] = 0;
    }
}


// @ 0x00815b30
void Outer::Wrap(int arg)
{
    inner.Method(arg, f4);
}


// @ 0x00815b50
void TextStyleReaderStub::Dtor()
{
    char* t = (char*)this;
    ((HashtableStub*)(t + 0x44))->DoFreeNodes(*(void***)(t + 0x48), *(unsigned*)(t + 0x4c));
    void* b = *(void**)(t + 0x48);
    *(int*)(t + 0x50) = 0;
    if (*(int*)(t + 0x4c) > 1 && b && b != *(void**)(t + 0x60))
        EastlDealloc(b);
    void* v = *(void**)(t + 0x34);
    if (*(int*)(t + 0x3c) - (int)v > 1 && v) EastlDealloc(v);
    void* m = *(void**)(t + 0x10);
    if (*(int*)(t + 0x18) - (int)m > 1 && m) EastlDealloc(m);
}


// @ 0x00815bd0
__declspec(noinline) bool LoadTextStyles(int resId, int mode)
{
    EA_Text_GetFontServer(1);
    void* sm = EA_Text_GetStyleManager(1);
    (void)sm; (void)resId; (void)mode;
    return true;
}


// @ 0x00815ce0
bool cSPUIMainWin_InitFonts()
{
    FontServer* fs = (FontServer*)EAlloc(0x2fd0, 0x13f6b3c, 0, 0, 0, 0);
    if (fs) fs = (FontServer*)fs->Init(FUN_00805510(1));
    else fs = 0;
    fs->f04();
    fs->f08(2, 1);
    FUN_00885b00(fs);
    fs->f38(L"web-default", L"Palatino Sans Infl Com");
    fs->f38(L"monospace", L"Lucida Console");
    StyleManager* sm = (StyleManager*)EAlloc(0x120, 0x13f6b3c, 0, 0, 0, 0);
    void* smp;
    if (sm) smp = sm->Init(FUN_00805510(1));
    else smp = 0;
    *(void**)((char*)g_164d348 + 0x10) = smp;
    FUN_00885af0(smp);
    LoadTextStyles(0x94da47e5, 0);
    LoadTextStyles(0x94da47e5, 1);
    return true;
}

// @ 0x00815dd0
bool cSPUIMainWin::Init()
{
    if (mInitialized) return true;
    mInitialized = true;

    FUN_00813b20();
    FUN_00813120();
    FUN_00956d90();
    FUN_0096ef80();
    FUN_008005f0();
    InitFonts();
    InitHitMaskFactory();
    InitStringFactories();
    FUN_0082f760();

    NEWOBJ(mpWindowMgr, 0x838, "UI/WindowManager", Fn958cf0());
    {
        void* disp = FUN_0067dd50_s0081_5dd0();
        struct R8 { int a[8]; };
        R8 rect = *(R8*)Vcp0(disp, 0x1c);
        ((void(__thiscall*)(void*, float, float))(*(void***)mpWindowMgr)[0x0c / 4])
            (mpWindowMgr, (float)rect.a[2], (float)rect.a[1]);
    }
    Vv0(mpWindowMgr, 0x24);
    ((void(__thiscall*)(void*, int))(*(void***)&sub4_vt)[0x50 / 4])(&sub4_vt, -0x10);
    Vv2(mpWindowMgr, 0x08, (int)&sub4_vt, 1);
    UpdateMouseScale();
    if (g_015451e8 < 0.001) g_015451e8 = 1.0f;
    if (g_015451ec < 0.001) g_015451ec = 1.0f;
    FUN_00957f40(mpWindowMgr);
    FUN_0067cba0(mpWindowMgr);

    NEWOBJ(mpLayer, 0x98, "UI/LayerManager", Fn80edb0());
    Vv0(mpLayer, 0x00);
    ((RawObj*)mpLayer)->Fn80f530();
    FUN_0067cbd0(mpLayer);

    {
        void* tm;
        NEWOBJ(tm, 0x30, "UI/TooltipManager", Fn8352d0());
        AssignRef(&mpTooltip, tm, 4, 8);
    }
    ((RawObj*)mpTooltip)->Fn835610();

    NEWOBJ(mpSerial, 0x34, "UI/SerializationService", Fn999520());
    {
        void* o;
        NEWOBJ(o, 0x0c, "", Fn833790());
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        void* o;
        NEWOBJ(o, 0x214, "", Fn8320d0());
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        void* o;
        NEWOBJ(o, 0x20, "", Fn997b60());
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        // inline-constructed two-base ref-counted service: vptrs at +0 and +4, count at +8
        u32* o = (u32*)FUN_00f473a0(0x0c, "", 0, 0, 0, 0);
        if (o) {
            ((volatile u32*)o)[1] = 0x13ef094;
            ((volatile u32*)o)[2] = 0;
            ((volatile u32*)o)[0] = 0x14188c4;
            ((volatile u32*)o)[1] = 0x14188c0;
        }
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        void* o = FUN_00f473a0(0x98, "", 0, 0, 0, 0);
        if (o) o = ((RawObj*)o)->Fn998df0(mpWindowMgr);
        Vv1(mpSerial, 0x04, (int)o);
    }

    void* ms = FUN_0067dcc0();
    void* lst = &listener;
    Vv2(ms, 0x20, (int)lst, 0xf62def);
    Vv2(ms, 0x20, (int)lst, 0x1ee1001);
    Vv2(ms, 0x20, (int)lst, 0x1ee1003);
    Vv2(ms, 0x20, (int)lst, 0x1ee100d);
    Vv2(ms, 0x20, (int)lst, 0x1ee1006);
    Vv2(ms, 0x20, (int)lst, 0x1ee1007);
    Vv2(ms, 0x20, (int)lst, 0x1ee1010);
    Vv2(ms, 0x20, (int)lst, 0x1ee1011);
    Vv2(ms, 0x20, (int)lst, 0x1ee1008);
    Vv2(ms, 0x20, (int)lst, 0x1ee1002);
    Vv2(ms, 0x20, (int)lst, 0x546bbb8);
    Vv2(ms, 0x20, (int)lst, 0x61205e6);
    Vv2(FUN_006895b0(), 0x20, (int)&g_01545188, 1);
    Vv2(ms, 0x20, (int)lst, (int)g_01545188);

    {
        void* lm = FUN_00f473a0(0x44, "", 0, 0, 0, 0);
        if (lm) ((RawObj*)lm)->Fn811f20();
    }
    Vv0(FUN_0080fee0(), 0x08);
    ((RawObj*)FUN_0080fee0())->Fn8115a0();
    FUN_008129c0();

    {
        // UI/SPUILayoutResourceFactory: inline ctor (vptr, atomic-zero refcount, final vptr)
        u32* res = (u32*)FUN_00926020(8, "UI/SPUILayoutResourceFactory", 0, 0, 0, 0);
        if (res) {
            ((volatile u32*)res)[0] = 0x13effa8;
            _InterlockedExchange((volatile long*)&res[1], 0);
            ((volatile u32*)res)[0] = 0x14186c4;
        }
        Vv3(FUN_0067dcd0(), 0x44, 1, (int)res, 0);
    }
    if (FUN_0080ff20()) FUN_0080a700();

    {
        void* cur = 0;
        void* m = FUN_00926020(0x5c, "UI/WindowManager", 0, 0, 0, 0);
        if (m) cur = ((RawObj*)m)->Fn8025e0();
        AssignRef(&mpCursor, cur, 4, 8);
        FUN_0067cbb0(mpCursor);
        void* mgr = FUN_0067dcd0();
        char ok = ((char(__thiscall*)(void*, int, int, int))(*(void***)mgr)[0x44 / 4])(mgr, 1, FUN_0067cab0(), 0);
        ((RawObj*)mpCursor)->Fn802160();
        if (ok) {
            void* c = mpCursor;
            Vv1(mpWindowMgr, 0x38, c ? (int)((char*)c + 8) : 0);
        }
    }
    ((void(__thiscall*)(void*, int))(*(void***)&sub4_vt)[0x78 / 4])(&sub4_vt, 0x1002);

    if (!mPropEditorInit) {
        mPropEditorInit = true;
        void* pe;
        NEWOBJ(pe, 0x14, "UI/PropertyEditor", Fn81e2b0());
        AssignRef(&mpPropEditor, pe, 8, 12);
        ((RawObj*)mpPropEditor)->Fn823a00();
    }

    {
        void* sb;
        NEWOBJ(sb, 0x50, "", Fn803020());
        AssignRef(&mpDebugConsole, sb, 0, 4);
        ((RawObj*)mpDebugConsole)->Fn802cd0();
        ((RawObj*)mpDebugConsole)->Fn802a20(0xc350);
        ((RawObj*)mpDebugConsole)->Fn802a30(0);
        Vv1(FUN_0067de20(), 0x30, (int)mpDebugConsole);
    }

    // ArgScript cheat commands (command object = base + vptr + cArgumentSpec at +0x10)
    {
        char* c = (char*)FUN_00f473a0(0xd8, "App", 0, 0, 0, 0);
        if (c) {
            ((RawObj*)c)->Fn83c800();
            *(volatile u32*)c = 0x1418abc;
            ((RawObj*)(c + 0x10))->Fn83a9f0(1);
            FUN_0083bcd0(c + 0x10, "Show pause screen", "<bool>", &g_01545198, "show or hide", 0);
        }
    }
    FUN_0067de20();
    {
        char* c = (char*)FUN_00f473a0(0xd8, "App", 0, 0, 0, 0);
        if (c) {
            ((RawObj*)c)->Fn83c800();
            ((RawObj*)(c + 0x10))->Fn83a9f0(1);
            *(volatile u32*)c = 0x14189e4;
            FUN_0083bcd0(c + 0x10, "toggles UI for image capture", 0);
        }
        Vv3(FUN_0067de20(), 0x18, (int)g_0154519c, (int)c, 0);
    }
    {
        char* c = (char*)FUN_00f473a0(0xdc, "App", 0, 0, 0, 0);
        if (c) {
            ((RawObj*)c)->Fn83c800();
            ((RawObj*)(c + 0x10))->Fn83a9f0(1);
            *(volatile u32*)c = 0x1418a80;
            FUN_0083bcd0(c + 0x10, "Enable localized text colorize", "<bool>", c + 0xd8, "enable or disable", 0);
        }
    }
    FUN_0067de20();

    if (g_015fd920 && g_015fd920->Fn92b300(L"colorLocalized", 0, 0, 0) != -1) {
        void* wmn = FUN_0067caa0();
        if (wmn) {
            Vv1(wmn, 0x90, 1);
            FUN_006b5030(1);
        }
    }

    if (flags21c & 1) {
        InitTitleScreen();
        Vv2(ms, 0x20, (int)lst, 0x366b9aa);
    }

    {
        void* cd;
        NEWOBJ(cd, 0x18, "", Fn810000());
        AssignRef(&mpMsgBox, cd, 4, 8);
        ((RawObj*)mpMsgBox)->Fn812160(L"GlobalUIPause", 0x40464100, 1, 0xa01a43c8);
        ((RawObj*)mpMsgBox)->Fn810590(0);
        void* w = ((RawObj*)mpMsgBox)->Fn8105b0(0x3868d60, 1);
        FUN_008085d0(w, (void*)FUN_00812d00, 1, 0, this);
    }
    FUN_007f4850();
    g_0164d211 = FUN_006ab760(Vcp0(FUN_0067de40(), 0x14), L"zh-cn");
    FUN_00989650(FUN_00813c60);
    Vv3(FUN_0067dce0(), 0x2c, 7, (int)FUN_00812c90, 0);

    if (flags21c & 2) {
        void* st;
        NEWOBJ(st, 0x88, "", Fn817a40());
        AssignRef(&mpStringMgr, st, 0, 4);
        ((RawObj*)mpStringMgr)->Fn8178b0(0);
    }
    return true;
}
