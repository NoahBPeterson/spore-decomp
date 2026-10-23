// Slice s00ee7990 — SPUI asset/palette editor UI object: destructors, layout
// init/shutdown, message handlers and category helpers.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#pragma once

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

struct Rect { float x, y, w, h; };
struct P3 { u32 a, b, c; };

// ---------------------------------------------------------------------------
// Object interfaces reached through the object's raw pointer fields. Each is a
// pure declaration: the original only ever dispatches through its vtable.
// ---------------------------------------------------------------------------
struct VI                       // generic refcounted object
{
    virtual void v00();          // +0x00 AddRef
    virtual void v01();          // +0x04 Release
    virtual void v02();          // +0x08 Destroy
    virtual void v03(int);       // +0x0c
    virtual void v04(int);       // +0x10
    virtual void v05();          // +0x14
    virtual void v06(int);       // +0x18
    virtual void v07(int);       // +0x1c
    virtual void v08(int);       // +0x20
    virtual void v09();          // +0x24
    virtual void v10();
    virtual void v11();
};

struct VIN                      // same object, every slot takes no arguments
{
    virtual void n00();          // +0x00
    virtual void n01();          // +0x04
    virtual void n02();          // +0x08
    virtual void n03();          // +0x0c
    virtual void n04();          // +0x10
    virtual void n05();          // +0x14
    virtual void n06();          // +0x18
    virtual void n07();          // +0x1c
    virtual void n08();          // +0x20
    virtual void n09();          // +0x24
    virtual void n10();
    virtual void n11();
};

struct XWin                     // UTFWin::IWindow-like window
{
    virtual void  w00();  virtual void  w01();  virtual void  w02();  virtual void  w03(int);
    virtual void  w04(int); virtual void  w05(); virtual void  w06(int); virtual void  w07();
    virtual void  w08(int); virtual void  w09(); virtual void  w10(); virtual void  w11();
    virtual void  w12();  virtual void  w13();  virtual Rect* w14();  virtual void  w15();
    virtual void  w16();  virtual void  w17();  virtual void* w18(int); virtual void  w19();
    virtual void  w20(int); virtual void w21(); virtual void  w22();  virtual void  w23();
    virtual void  w24();  virtual void  w25();  virtual void  w26();  virtual void  w27(Rect*);
    virtual void  w28();  virtual void  w29();  virtual void  w30();  virtual void  w31(int, int);
    virtual void  w32();  virtual void  w33();  virtual void  w34();  virtual void  w35();
    virtual void  w36();  virtual void  w37();  virtual void  w38();  virtual void  w39();
    virtual void  w40();  virtual void  w41();  virtual void  w42();  virtual void  w43();
    virtual void  w44();  virtual void  w45();  virtual void  w46();  virtual void  w47();
    virtual void  w48();  virtual void  w49();  virtual void  w50();  virtual void  w51();
    virtual void  w52();  virtual void  w53();  virtual void  w54();  virtual void  w55();
    virtual void  w56();  virtual void  w57();  virtual void  w58();  virtual void  w59();
    virtual void* w60(int, int); virtual void w61(); virtual u8 w62(int); virtual void w63();
    virtual void  w64();  virtual void  w65(void*);
};

struct XW2                     // object stored at +0x170
{
    virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03();
    virtual void x04(); virtual void x05(); virtual void x06(); virtual int  x07();
};

struct XMsgSrv                 // SP::MessageServer
{
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(void*, u32); virtual void m10();
    virtual void m11(void*, u32, int);
};

// ---------------------------------------------------------------------------
// Concrete collaborators (all declared, never defined: their bodies live in
// other translation units of the original program).
// ---------------------------------------------------------------------------
struct XLayout                  // cSPUILayout
{
    bool  Init(const void* key, bool a, u32 flags);              // 0x8120d0
    void  Shutdown(u32 flags);                                   // 0x811ad0
    void* FindWindowByID(u32 id);                                // 0x8105b0
    void* FindWindowByID(u32 id, bool a);                        // 0x8105b0
    void* FindWindowByID(u32 id, bool a, void* out);             // 0x8105b0
    bool  SetParentWin(void* parent, bool a, u32 flags);         // 0x8121b0
    bool  IsVisible();                                           // 0x810070
    void* GetWin();                                              // 0x810570
};

struct XPaletteUI               // cSPPaletteUI
{
    void UpdateCategories(void* arg);                            // 0x5ca980
    int  FindCategoryIndex();                                    // 0x5ca9c0
    int  FindCategoryIndex(int b);                               // 0x5ca9c0
    void Shutdown();                                             // 0x5cba90
};

struct XSub                     // 0x70-byte sub-object at +0x18/+0x88/+0xf8
{
    void  Ctor();                                                // 0xe0a390
    void  Dtor();                                                // 0xe0a400
    void  Reset();                                               // 0xe0a5c0
    bool  Check(void* w);                                        // 0xe0a4c0
    bool  CheckKey(const void* key, int n);                      // 0xe0a780
    void* Get(int i);                                            // 0xe09c90
};

struct XDialog                  // cConnectionDialog
{
    XDialog* Ctor();                                             // 0x810000
};

struct XObj3c                   // object allocated with size 0x3c
{
    void* Init();                                                // 0xee6e80
};

struct XHint                    // UI::cScenarioTutorialsChecklistUI
{
    void ToggleHint(u32 a, u32 b);                               // 0xefbbe0
};

struct XUniv                    // SP::cSPLivingUniverse
{
    void F33bf0();                                               // 0xf33bf0
    void F352c0(u32 v);                                          // 0xf352c0
    void F34560();                                               // 0xf34560
    void F31ea0();                                               // 0xf31ea0
    void F36380();                                               // 0xf36380
    void F363c0();                                               // 0xf363c0
};

struct XSpecMgr                 // SP::cPlantSpeciesManager
{
    void* GetAt(u32 elem);                                       // 0xb90410
};

struct XSpecies
{
    u32 GetID();                                                 // 0xb8f860
};

struct XCat
{
    u8   FindCategory(u32 id, int* outCat, u8* outFlag);         // 0xee7910
    bool IsInTable(u32 id);                                      // 0xee78c0
    void Refresh(u8 which);                                      // 0xee8240
};

struct XLaunchCtx               // 0x48-byte launch context
{
    u32 v[18];
    void Ctor();                                                 // 0x644b10
    void Dtor();                                                 // 0x644b60
};

struct XGObj                    // object whose address is 0x16c7c08
{
    void Add(u32 v);                                             // 0xf01090
};

// ---------------------------------------------------------------------------
// The editor object. Field names are raw offsets (hex/4), because the same
// storage is reinterpreted by several layers of the original class hierarchy.
// ---------------------------------------------------------------------------
struct SpuEd
{
    u32 o000; u32 o004; u32 o008; u32 o00c; u32 o010; u32 o014; u32 o018; u32 o01c;
    u32 o020; u32 o024; u32 o028; u32 o02c; u32 o030; u32 o034; u32 o038; u32 o03c;
    u32 o040;
    u32 pad44[70];
    u32 o15c; u32 o160; u32 o164; u32 o168; u32 o16c; u32 o170;

    void  BaseDtor();                                            // 0x00ee7990
    void  DtorDerived();                                         // 0x00ee7a50
    void  SetMode(int mode, u8 on);                              // 0x00ee7b40
    void  Update(void* arg);                                     // 0x00ee7c60
    SpuEd* Ctor();                                               // 0x00ee7da0
    void  Dtor3();                                               // 0x00ee7e50
    u8    InitLayout(void* parent);                              // 0x00ee7f00
    void  ShutdownLayout();                                      // 0x00ee8110
    u8    OnMsg2(u32 msg, void* p);                              // 0x00ee8180
    void  UpdateCategory(u32 sel);                               // 0x00ee82c0
    void  SetObject(void* obj);                                  // 0x00ee83a0
    void  Select(void* win);                                     // 0x00ee8460
    void  Dtor4();                                               // 0x00ee8570
    void  Enable2(u8 on);                                        // 0x00ee85e0
    u8    OnMsg3(u32 msg, void* p);                              // 0x00ee86c0
    u8    SetSource(void* src);                                  // 0x00ee8720
    void  Close();                                               // 0x00ee87f0
};

// ---------------------------------------------------------------------------
// Free functions.
// ---------------------------------------------------------------------------
int  __cdecl FindPlanetSlot(u32 id, int* outA, int* outB);       // 0x00ee7cb0
void __cdecl Fn1350(void* win, u8 flag);                         // 0x00ed1350
void __cdecl Fn2fa0(void* win, u32 arg);                         // 0x00e12fa0
void __cdecl LaunchCtx(XLaunchCtx* ctx);                         // 0x64a990

extern "C" {
// 0x0067dcc0 — SP::MessageServer()
XMsgSrv* __cdecl MessageServer();                                 // 0x67dcc0
// 0x0067caa0 — SP::WindowManager()
XWin* __cdecl WindowManager();                                    // 0x67caa0
// 0x00571db0 — EA::Messaging::RemoveHandler(server, handler, id, a, b)
void  __cdecl RemoveHandler(void* server, void* handler, u32 id, int a, int b); // 0x571db0
// 0x00f473a0 — EAAllocate(size, name, 0, 0, file, line)
void* __cdecl EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
// 0x0010212a0 — active planet record
void* __cdecl GetPlanetRec();                                     // 0x10212a0
// 0x00b3d420 — active species manager accessor
void* __cdecl GetSpeciesMgr();                                    // 0xb3d420
extern void* g_universe;                                          // 0x16c7aa4
extern u32   g_univ18;                                            // 0x16c7c18
extern XGObj g_launchObj;                                         // 0x16c7c08
extern const u32 g_catA[];                                        // 0x148aac0
extern const u32 g_catB[];                                        // 0x148aafc
}
