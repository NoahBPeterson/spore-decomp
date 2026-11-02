// src/game/SPGonzago/SPUISpaceTrading.cpp -- migrated from slice(s) s01077470, s01076540, s01074bb0, s010759c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUISpaceTrading.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cEmpire.h"
#include "SP/cPlanet.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cGameNounManager.h"
#include "cSPUIAnimator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
extern "C" void operator_delete_array(void* p);                // 0x00f47380
extern "C" void FUN_008822e0(double v, void* buf, int n, int a, int b);   // 0x008822e0
extern "C" void SetNumberString(int lo, int hi, void* buf, int n);        // 0x00881ae0
extern "C" wchar_t* wcsncat_(wchar_t* dst, const wchar_t* src, unsigned n);// 0x13cc380
extern void* g_15b9448;                                        // 0x015b9448

// ---- items of slice s010759c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PAD(n) virtual void pad##n()
struct IWindow {
PAD(0);
PAD(1);
PAD(2);
    virtual void* Slot0C(unsigned key);            // +0x0c
    virtual IWindow* GetParent();                  // +0x10
    virtual void Slot14(int a);                    // +0x14
    PAD(6);
    virtual unsigned GetControlID();               // +0x1c
PAD(8);
PAD(9);
    virtual unsigned GetFlags();                   // +0x28
    virtual void* Slot2C();                        // +0x2c
    virtual void* Slot30(void* out);               // +0x30
    PAD(13);
    virtual float* Slot38();                       // +0x38  (4-float rect)
PAD(15);
PAD(16);
PAD(17);
PAD(18);
PAD(19);
PAD(20);
PAD(21);
PAD(22);
PAD(23);
PAD(24);
PAD(25);
PAD(26);
PAD(27);
PAD(28);
    virtual void Slot74(float w, float h);         // +0x74
    PAD(30);
    virtual void SetFlag(unsigned flag, int value);// +0x7c
    virtual void Slot80(void* a);                  // +0x80
PAD(33);
PAD(34);
PAD(35);
PAD(36);
PAD(37);
PAD(38);
PAD(39);
PAD(40);
PAD(41);
PAD(42);
PAD(43);
PAD(44);
PAD(45);
PAD(46);
PAD(47);
PAD(48);
PAD(49);
PAD(50);
PAD(51);
PAD(52);
PAD(53);
PAD(54);
PAD(55);
PAD(56);
PAD(57);
PAD(58);
PAD(59);
    virtual IWindow* FindWindowByID(unsigned id, int recursive);   // +0xf0
PAD(61);
PAD(62);
PAD(63);
PAD(64);
    virtual void Slot104(void* owner);             // +0x104
};
struct RefObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct RefObjA {                                   // v0 takes one argument
    virtual void v0(int a);
    virtual void v1(int a);
};
struct cSPUILayout_s0107_59c0 {
    IWindow* FindWindowByID(unsigned id, int recursive);   // 0x008105b0
    void     Shutdown(unsigned a);                          // 0x00811ad0
};
struct cUITimedTooltip {
    char  pad0[0x60];
    float mMaxWidth;                               // +0x60  (0xb0 from the panel)

    void* FindWindow(unsigned id, bool recursive); // 0x00e36650
    void  UpdateLayout();                          // 0x00e369f0
    void  Shutdown();                              // 0x00e36500
    void  UpdateTimeoutA();                        // 0x00e36540
    void  UpdateTimeoutB(IWindow* w);              // 0x00e365a0
    void  Hide();                                  // 0x00e36620
    cUITimedTooltip* Construct();                  // 0x00e36480
    void  Destroy();                               // 0x00e364d0
};
struct cString {
    char pad0[0x14];
    void Construct();                              // 0x006b5060
    void Destroy();                                // 0x006b5240
    const wchar_t* GetText();                      // 0x006b55c0
};
struct Vec3 {
    void* mpBegin;                                 // +0x00
    void* mpEnd;                                   // +0x04
    void* mpCap;                                   // +0x08
    void Destroy();                                // 0x005c7f10
};
struct TradeItem {
virtual void  p0();
virtual void  p1();
virtual void  p2();
virtual void  p3();
virtual void  p4();
virtual void  p5();
virtual void  p6();
virtual void  p7();
virtual void  p8();
virtual void  p9();
    virtual void* Slot28();                        // +0x28
    virtual void* Slot2C();                        // +0x2c
    virtual void* Slot30(void* out);               // +0x30
    char  pad0[0xc];                               // +0x04..+0x0f
    int   mCount;                                  // +0x10
    char  pad14[0x1c];                             // +0x14..+0x2f
    int   mField30;                                // +0x30
    int   Fn6C0200();                              // 0x006c0200
};
struct ItemInfo { char pad[0x10]; int mValue; };
struct cSPSpaceTrading {
    TradeItem* GetUserItem(unsigned idx);          // 0x01039ab0
    TradeItem* GetNPCItem(unsigned idx);           // 0x01039ad0
    int   Fn103B950(unsigned a, unsigned isUser, TradeItem* item, unsigned d); // 0x0103b950
    void  Fn103DBD0(unsigned a);                   // 0x0103dbd0
    void* Fn1039C00();                             // 0x01039c00
    int   Fn1039B70();                             // 0x01039b70
};
struct AudioSystem {
PAD(0);
PAD(1);
PAD(2);
PAD(3);
PAD(4);
PAD(5);
PAD(6);
PAD(7);
    virtual unsigned Slot20();                     // +0x20
PAD(9);
PAD(10);
PAD(11);
PAD(12);
PAD(13);
    virtual void Slot38(unsigned a);               // +0x38
    virtual void Slot3C(unsigned a, float b);      // +0x3c
    virtual void Slot40(unsigned a, unsigned b);   // +0x40
PAD(17);
PAD(18);
PAD(19);
PAD(20);
PAD(21);
    virtual void Slot58();                         // +0x58
};
struct MessageServerT {
PAD(0);
PAD(1);
PAD(2);
PAD(3);
PAD(4);
PAD(5);
    virtual void Slot18(unsigned a, int b, int c, int d);   // +0x18
};
struct Global16E0D08 { char pad[0x38]; int mField38; };
extern "C" cSPSpaceTrading* GetSpaceTrading(void);             // 0x00b3d3d0
extern "C" cSPUILayout_s0107_59c0*     FUN_00dd1ca0(void);                // 0x00dd1ca0 (global layout getter)
extern "C" AudioSystem*     GetSystemAT(void);                 // 0x00a206f0
extern "C" MessageServerT*  MessageServer(void);               // 0x0067dcc0
extern "C" void RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
extern "C" void operator_delete_array(void* p);                // 0x00f47380
extern "C" void SetImageFromKey(IWindow* w, void* key);        // 0x00e2f5c0
extern "C" void FUN_008822e0(double v, void* buf, int n, int a, int b);   // 0x008822e0
extern "C" void SetNumberString(int lo, int hi, void* buf, int n);        // 0x00881ae0
extern "C" wchar_t* wcsncat_(wchar_t* dst, const wchar_t* src, unsigned n);// 0x13cc380
extern Global16E0D08* g_16e0d08;                               // 0x016e0d08
extern void* g_15b9448;                                        // 0x015b9448
struct cSPUISpaceTrading {
    // The three sub-object vtable slots.  The original constructor and
    // destructor write base-then-derived (and, in the destructor,
    // derived-then-base) vtable pointers as observable stores, so they are
    // modelled as volatile: the compiler must neither drop nor reorder them.
    void* volatile mpVtbl0;                        // +0x00
    void* volatile mpVtbl1;                        // +0x04
    int   mField08;                                // +0x08
    void* volatile mpVtbl2;                        // +0x0c
    void* mField10;                                // +0x10
    void* mField14;                                // +0x14
    void* mField18;                                // +0x18
    void* mField1C;                                // +0x1c
    void* mField20;                                // +0x20
    void* mField24;                                // +0x24
    Vec3  mItems;                                  // +0x28
    char  pad34[8];                                // +0x34..+0x3b
    Vec3  mAnims;                                  // +0x3c
    char  pad48[8];                                // +0x48..+0x4f
    cUITimedTooltip mTooltip;                      // +0x50
    cString mStrB4;                                // +0xb4
    cString mStrC8;                                // +0xc8
    cString mStrDC;                                // +0xdc
    cString mStrF0;                                // +0xf0
    cSPUILayout_s0107_59c0* mLayout;                          // +0x104
    void* mHandler;                                // +0x108
    void* mH10C;                                   // +0x10c
    void* mH110;                                   // +0x110
    void* mH114;                                   // +0x114
    void* mH118;                                   // +0x118
    bool  mField11C;                               // +0x11c
    char  pad11D[3];                               // +0x11d..+0x11f
    int   mField120;                               // +0x120
    bool  mField124;                               // +0x124

    void Fn10759C0(IWindow* w, TradeItem* item, unsigned isUser);
    void Fn1075DB0();                              // destructor body 0x01075db0
    void Deactivate();
    void Fn10762D0();
    cSPUISpaceTrading* Fn10762E0();                // constructor body 0x010762e0
    void Fn10763C0();
    void UpdateMidPanel();
    void Init();
    void Fn1075810(unsigned a, TradeItem* item);   // 0x01075810
    void Fn1075510();                              // 0x01075510
    void Fn1075570();                              // 0x01075570
    void Fn1075760();                              // 0x01075760
};
// ---- items of slice s010759c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" cSPSpaceTrading* GetSpaceTrading(void);             // 0x00b3d3d0
extern "C" cSPUILayout_s0107_59c0*     FUN_00dd1ca0(void);                // 0x00dd1ca0 (global layout getter)
extern "C" AudioSystem*     GetSystemAT(void);                 // 0x00a206f0
extern "C" MessageServerT*  MessageServer(void);               // 0x0067dcc0
extern "C" void SetImageFromKey(IWindow* w, void* key);        // 0x00e2f5c0
extern Global16E0D08* g_16e0d08;                               // 0x016e0d08

// ---- items of slice s01074bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char __cdecl FUN_008076f0(void* p);        // 0x008076f0
extern "C" void* __cdecl FUN_010666a0();              // 0x010666a0
typedef unsigned int uint;
struct IWindow_s0107_4bb0 {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual IWindow_s0107_4bb0* Get10();                                        // 0x10
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
    virtual void SetVisible(int a, int b);                           // 0x7c
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sA0();
virtual void sA4();
virtual void sA8();
virtual void sAC();
virtual void sB0();
virtual void sB4();
virtual void sB8();
virtual void sBC();
virtual void sC0();
virtual void sC4();
virtual void sC8();
virtual void sCC();
virtual void sD0();
virtual void sD4();
virtual void sD8();
    virtual void FDC(void* p);                                       // 0xdc
virtual void sE0();
virtual void sE4();
virtual void sE8();
virtual void sEC();
    virtual IWindow_s0107_4bb0* F0(uint id, int flag);                          // 0xf0
virtual void sF4();
virtual void sF8();
virtual void sFC();
virtual void s100();
virtual void s104();
    virtual void F108(void* p);                                      // 0x108
};
struct cString_s0107_4bb0 {
    char d[0x14]; const wchar_t* GetText(int flags);    // 0x006b55c0 (ret 4)
    void Load(uint a, const wchar_t* b, int c);         // 0x006b54b0 (ret 0xc)
};
struct Layout {
    virtual void v00();
    virtual void v04();
    virtual void Release();                        // +0x08
    IWindow_s0107_4bb0* FindWindowByID(uint id, int flag);    // 0x008105b0 (ret 8)
};
struct RefObj_s0107_4bb0 {                                       // released through slot +0x04
    virtual void v00();
    virtual void Release();
};
struct CountedObj { char pad0[0x10]; int mCount; };    // +0x10
struct TradingGlobal {                                // *(void**)0x0167eb20
    void* F1039ab0(int id);                           // 0x01039ab0 (ret 4)
    void* F1039ad0(int id);                           // 0x01039ad0 (ret 4)
    int   F1039b70(void* item);                       // 0x01039b70 (ret 4)
    CountedObj* F1039c00(void* item);                 // 0x01039c00 (ret 4)
    int   F103b950(int a, int flag, void* item, int b); // 0x0103b950 (ret 0x10)
};
extern "C" TradingGlobal* __cdecl FUN_00b3d3d0();     // 0x00b3d3d0
struct Sender { char pad0[0x10]; int mCount; };        // +0x10
struct UIRoot61C {
    void F0E31030(uint a, uint b, int c, uint d);     // 0x00e31030 (ret 0x10)
};
struct SpaceRoot { char pad0[0x61c]; UIRoot61C* m61c; };
struct cTrading {
    char pad0[0x10];
    IWindow_s0107_4bb0* m10;            // +0x10
    void*    m14;            // +0x14
    void*    m18;            // +0x18
    IWindow_s0107_4bb0* m1c;            // +0x1c
    void*    m20;            // +0x20
    void*    m24;            // +0x24
    char pad1[0xb4 - 0x28];
    cString_s0107_4bb0  mStrB4;         // +0xb4
    cString_s0107_4bb0  mStrC8;         // +0xc8
    cString_s0107_4bb0  mStrDC;         // +0xdc
    cString_s0107_4bb0  mStrF0;         // +0xf0
    Layout*  mLayout;        // +0x104
    char pad2[0x11c - 0x108];
    char mFlag11C;           // +0x11c
    char pad3[0x120 - 0x11d];
    int  mId120;             // +0x120
    unsigned char mFlag124;  // +0x124

    int  F1075450();
    void F1075490();
    void F1075510();
    void F1075570();
    void SetMidPanel();
    void RemoveExistingItem();
    void F1075760();
    void F1075810(int flag, void* item);
    void F1075990();
};
// ---- items of slice s01074bb0 end

// ---- items of slice s01076540 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow_s0107_6540;
struct Rect { float left, top, right, bottom; };
class cSPUILayout_s0107_6540 {
public:
    virtual void Pad0();                                     // +0x00
    virtual void AddRef();                                   // +0x04
    virtual void Release();                                  // +0x08
virtual void Pad3();
virtual void Pad4();
virtual void Pad5();
virtual void Pad6();
virtual void Pad7();
virtual void Pad8();
virtual void Pad9();
    void Shutdown(uint32_t flags);                           // 0x00811ad0 (ret 4)
    IWindow_s0107_6540* FindWindowByID(uint32_t id, int recursive);     // 0x008105b0 (ret 8)
    cSPUILayout_s0107_6540* Ctor();                                     // 0x00810000
    bool Init(const wchar_t* name, uint32_t a, uint32_t b, uint32_t c);  // 0x00812160 (ret 0x10)
};
struct ITextWindow {
PAD(0);
PAD(1);
PAD(2);
PAD(3);
PAD(4);
PAD(5);
PAD(6);
PAD(7);
PAD(8);
PAD(9);
    virtual void SetColor(uint32_t color);                    // +0x28
};
struct IWindow_s0107_6540 {
PAD(0);
PAD(1);
PAD(2);
    virtual ITextWindow* Slot0C(uint32_t key);                // +0x0c
    virtual IWindow_s0107_6540* GetParent();                             // +0x10
PAD(5);
PAD(6);
    virtual uint32_t GetControlID();                          // +0x1c
PAD(8);
PAD(9);
    virtual uint32_t GetFlags();                              // +0x28
PAD(11);
PAD(12);
PAD(13);
    virtual Rect* GetArea();                                  // +0x38
PAD(15);
PAD(16);
PAD(17);
PAD(18);
PAD(19);
    virtual void Slot50(uint32_t id);                         // +0x50
PAD(21);
PAD(22);
    virtual void Slot5C(uint32_t value);                      // +0x5c
    PAD(24);
    virtual void SetPosition(float x, float y);               // +0x64
PAD(26);
PAD(27);
PAD(28);
PAD(29);
PAD(30);
    virtual void SetFlag(uint32_t flag, int value);           // +0x7c
    virtual void Slot80(void* buffer);                        // +0x80
PAD(33);
PAD(34);
PAD(35);
PAD(36);
PAD(37);
PAD(38);
PAD(39);
PAD(40);
PAD(41);
PAD(42);
PAD(43);
PAD(44);
PAD(45);
PAD(46);
PAD(47);
PAD(48);
PAD(49);
PAD(50);
PAD(51);
PAD(52);
PAD(53);
    virtual void SlotD8(IWindow_s0107_6540* child);                      // +0xd8
    virtual void SlotDC(IWindow_s0107_6540* child);                      // +0xdc
PAD(56);
PAD(57);
PAD(58);
PAD(59);
    virtual IWindow_s0107_6540* FindWindowByID(uint32_t id, int recursive);   // +0xf0
PAD(61);
PAD(62);
PAD(63);
PAD(64);
    virtual void Slot104(void* p);                            // +0x104
};
struct Message { IWindow_s0107_6540* source; uint32_t pad4; uint32_t type; };
struct AudioSystem_s0107_6540 {
PAD(0);
PAD(1);
PAD(2);
PAD(3);
PAD(4);
PAD(5);
PAD(6);
PAD(7);
    virtual uint32_t Slot20();                                // +0x20
PAD(9);
PAD(10);
PAD(11);
PAD(12);
PAD(13);
    virtual void Slot38(uint32_t a);                          // +0x38
    virtual void Slot3C(uint32_t a, float b);                 // +0x3c
    virtual void Slot40(uint32_t a, uint32_t b);              // +0x40
PAD(17);
PAD(18);
PAD(19);
PAD(20);
PAD(21);
    virtual void Slot58();                                    // +0x58
};
AudioSystem_s0107_6540* GetSystemAT_s0107_6540();                                   // 0x00a206f0 EA::Audio::GetSystemAT
struct TradeItem_s0107_6540 {
PAD(0);
PAD(1);
PAD(2);
PAD(3);
PAD(4);
PAD(5);
PAD(6);
PAD(7);
PAD(8);
PAD(9);
PAD(10);
PAD(11);
    virtual const char* Slot30(void* buffer);                 // +0x30
    char pad04[0x10];
    uint32_t f14;                                             // +0x14
    char pad18[0x18];
    uint32_t f30;                                             // +0x30
    int Get18();                                              // 0x006c0200
};
struct TradeItemInfo { char pad[0x10]; uint32_t f10; };
struct cSPSpaceTrading_s0107_6540 {
    TradeItem_s0107_6540* GetUserItem(uint32_t idx);                     // 0x01039ab0
    TradeItem_s0107_6540* GetNPCItem(uint32_t idx);                      // 0x01039ad0
    void PerformTrade();                                      // 0x0103eff0
    void CreateNPCInventory(uint32_t planet, uint32_t arg);   // 0x0103e8e0
    uint32_t Fn103b950(uint32_t a, uint32_t isUser, TradeItem_s0107_6540* item, uint32_t d);   // 0x0103b950
    void Fn103dbd0(uint32_t a);                               // 0x0103dbd0
    TradeItemInfo* Fn1039c00(TradeItem_s0107_6540* item);                // 0x01039c00
    uint32_t Fn1039b70(TradeItem_s0107_6540* item);                      // 0x01039b70
    void* Fn103a540(TradeItem_s0107_6540* item);                         // 0x0103a540
};
cSPSpaceTrading_s0107_6540* GetSpaceTrading_s0107_6540();                           // 0x00b3d3d0
struct ObjB490 {
    void Fn(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00ae7e10 (ret 0x10)
};
ObjB490* GetB490();                                           // 0x00b3d490
struct Empire { char pad[0x58]; uint32_t f58; };
struct StarManager {
    Empire* GetEmpireByID(uint32_t id);   // 0x00ba9370
};
StarManager* GetStarManager();                                // 0x00b3d2a0
struct NounManager {
    uint32_t GetAvatar();   // 0x00b1fdb0
};
NounManager* IsArchived();                                    // 0x01021240 (SP::cSPMission::IsArchived)
struct Planet { char pad[0x13c]; uint32_t f13c; };
Planet* GetActivePlanet();                                    // 0x01021260
struct ObjAED4D0 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void Fn28(uint32_t key, uint32_t id, uint32_t* o1, uint32_t* o2);   // +0x28
};
ObjAED4D0* GetAED4D0();                                       // 0x00aed4d0
uint32_t GetRecorderState();                                  // 0x00435e90
void KillSetiEffects(uint32_t key, uint32_t state);           // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
void SetGlobalProperty(uint32_t id, float value);             // 0x005ca880
class cSPUIAnimator_s0107_6540 { public: void Update(); };                      // 0x007f63b0
struct Sub50 {
    void Fn36540();                                           // 0x00e36540
    void Fn36620();                                           // 0x00e36620
};
struct cSPUISpaceTrading_s0107_6540 {
    char pad00[0x14];
    void* mClient14;                // +0x14
    IWindow_s0107_6540* mWindow18;             // +0x18
    char pad1c[4];
    void* mClient20;                // +0x20
    IWindow_s0107_6540* mWindow24;             // +0x24
    cSPUILayout_s0107_6540** mItemsBegin;      // +0x28
    cSPUILayout_s0107_6540** mItemsEnd;        // +0x2c
    cSPUILayout_s0107_6540** mItemsCap;        // +0x30
    char pad34[8];
    cSPUIAnimator_s0107_6540** mAnimBegin;     // +0x3c
    cSPUIAnimator_s0107_6540** mAnimEnd;       // +0x40
    char pad1[0x50 - 0x44];
    Sub50 mSub50;                   // +0x50
    char pad2[0x104 - 0x50 - sizeof(Sub50)];
    cSPUILayout_s0107_6540* mLayout;           // +0x104
    char pad3[0x11d - 0x108];
    bool mTrading;                  // +0x11d
    char pad4[2];
    int mActiveItemIndex;           // +0x120
    bool mIsUserItem;               // +0x124

    bool DoMessage(IWindow_s0107_6540* win, Message* msg);               // 0x01076b80
    TradeItem_s0107_6540* GetActiveItem();                               // 0x01075450
    void Fn10759c0(IWindow_s0107_6540* w, TradeItem_s0107_6540* item, bool isUser);   // 0x010759c0 (ret 0xc)
    void SetMidPanel();                                       // 0x010755d0
    void UpdateMidPanel();                                    // 0x01075ff0
    void RemoveExistingItem();                                // 0x01075690
    void Fn10763c0();                                         // 0x010763c0
    void Fn1076b00();                                         // 0x01076b00
    void AddItem(IWindow_s0107_6540* parent, uint32_t index, uint32_t field, uint32_t type, TradeItem_s0107_6540* item);  // 0x01076540 (ret 0x14)
    void AddNPCItems();                                       // 0x01076a00
    void AddUserItems();                                      // 0x01076a60
};
char FUN_00807690(void* p, int v);                                  // 0x00807690
struct PlayerInventory {
PAD(0);
PAD(1);
PAD(2);
PAD(3);
PAD(4);
PAD(5);
PAD(6);
PAD(7);
PAD(8);
PAD(9);
PAD(10);
PAD(11);
PAD(12);
PAD(13);
PAD(14);
PAD(15);
PAD(16);
PAD(17);
PAD(18);
PAD(19);
PAD(20);
PAD(21);
PAD(22);
PAD(23);
PAD(24);
PAD(25);
PAD(26);
PAD(27);
PAD(28);
PAD(29);
PAD(30);
PAD(31);
PAD(32);
PAD(33);
PAD(34);
    virtual uint32_t GetItemCount();                           // +0x8c
};
struct SpaceGame { PlayerInventory* GetPlayerInventory(); };       // 0x00a1ad60
SpaceGame* SpaceGameGet();                                         // 0x01002bd0
static __forceinline void ItemLoop(cSPUISpaceTrading_s0107_6540* t, uint32_t flag)
{
    int n = 10;
    do {
        TradeItem_s0107_6540* item;
        int idx = t->mActiveItemIndex;
        if (idx == -1)
            item = 0;
        else if (t->mIsUserItem)
            item = GetSpaceTrading_s0107_6540()->GetUserItem(idx);
        else
            item = GetSpaceTrading_s0107_6540()->GetNPCItem(idx);
        GetSpaceTrading_s0107_6540()->Fn103b950(flag, t->mIsUserItem, item, 1);
    } while (--n);
}
// ---- items of slice s01076540 end

// ---- items of slice s01077470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int DAT_0149c5c4[3] = {0, 0, 0}; // 0x0149c5c4  NPC message list
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Obj;
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_piii)(void*, int, int, int);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_ppi)(void*, void*, int);
typedef void  (__thiscall *Fn_v_pff)(void*, float, float);
typedef Obj*  (__thiscall *Fn_p_p)(void*);
extern "C" u32 DAT_015b9550 = 0;    // 0x015b9550  tooltip window id
extern "C" u32 DAT_015b9554 = 0;    // 0x015b9554  tooltip layout id
extern "C" u32 DAT_015b9558 = 0;    // 0x015b9558  tooltip style id
struct cScrollElem {
    void* mpObj;         // +0x00
    float mField4;       // +0x04
    u8    mByte8;        // +0x08
    u8    mPad9[3];
};
struct cUITimedTooltip_s0107_7470 {
    u8   mPad00[0x30];
    char Init(u32 a1, u32 a2, u32 a3, u32 a4, int a5, int a6); // 0x00e36b30
    Obj* FindWindow(int id, bool flag);                          // 0x00e36650
};
struct cTerrainEditor {
    bool  FUN_00c772c0(int id);     // 0x00c772c0
    void  FUN_00c77bf0(int id);     // 0x00c77bf0
    Obj*  GetCurrentTerrainSphere(); // 0x00f67d90
};
struct cSPSpaceTrading_s0107_7470 {
    void* CreateNPCInventory();     // 0x0103e8e0
};
struct TradeCtl {
    void* FUN_0067aaf0();           // 0x0067aaf0
};
struct TradeId  { u32 a, b, c; };
struct TradePos { float x, y, z; };
void* __cdecl FUN_00807600(const wchar_t* name, void* pOut, int flag); // 0x00807600
bool  __cdecl FUN_00807690_s0107_7470(void* p, int flag);                         // 0x00807690
Obj*  __cdecl SP_GetActivePlanet();                                    // 0x01021260
Obj*  __cdecl SP_MessageServer();                                      // 0x0067dcc0
void* __cdecl SP_NounManager();                                        // 0x00b3d300
void* __stdcall FUN_00b3d3d0(void* a, void* b);                        // 0x00b3d3d0
void* __cdecl FUN_0067caf0(TradeId ids, int a, int b, TradePos pos, int c, int d); // 0x0067caf0
namespace SP {
struct cSPUISpaceTrading_s0107_7470 {
    u8    mPad00[0x0c];
    void* mpField0C;             // +0x00c  message-handler target (&mField0C)
    void* mpField10;             // +0x010  NPC scroll container
    void* mpScroll14;            // +0x014  NPC scroll frame (FUN_01077470)
    void* mpOwner18;             // +0x018  NPC scroll frame owner slot
    void* mpField1C;             // +0x01c  user scroll container
    void* mpField20;             // +0x020  user scroll frame (FUN_01077550)
    void* mpField24;             // +0x024  user scroll frame owner slot
    void* mpField28;             // +0x028
    void* mpField2C;             // +0x02c  window collection
    cScrollElem* mpVec30;        // +0x030  cell vector begin
    cScrollElem* mpVecEnd34;     // +0x034  cell vector end
    u8    mPad38[0x50 - 0x38];
    cUITimedTooltip_s0107_7470 mTooltip;    // +0x050
    u32   mField80;              // +0x080  layout tag (0x120ad1fb)
    u32   mPad84;
    int   mField88;              // +0x088  divisor
    int   mField8C;              // +0x08c  divisor
    u32   mPad90;
    float mField94;              // +0x094  cell pitch x
    float mField98;              // +0x098  cell pitch y
    u8    mByte9C;               // +0x09c  "use window index" flag
    u8    mPad9D[0xac - 0x9d];
    float mFieldAC;              // +0x0ac  tooltip row height (empty)
    float mFieldB0;              // +0x0b0  tooltip row height
    float mFieldB4;              // +0x0b4  cell width
    float mFieldB8;              // +0x0b8  cell height
    float mFieldBC;              // +0x0bc
    float mFieldC0;              // +0x0c0
    u8    mPadC4[0xe0 - 0xc4];
    float mFieldE0;              // +0x0e0  scroll extent (x)
    float mFieldE4;              // +0x0e4  scroll extent (y)
    u8    mByteE8;               // +0x0e8  NPC panel visible
    u8    mByteE9;               // +0x0e9  user panel visible
    u8    mPadEA[2];
    void* mpHandlerEC;           // +0x0ec  registered message handler
    void* mArgsF0[4];            // +0x0f0  handler arguments
    union {
        struct { void* h; void* a1; void* a2; void* a3; void* a4; } mBlk100;
        struct { u32 p0; u32 p1; void* h; void* a1; void* a2; void* a3; void* a4; } mBlk108;
    };
    u8    mByte11C;              // +0x11c
    u8    mByte11D;              // +0x11d
    u16   mPad11E;
    int   mField120;             // +0x120
    u32   mPad124;
    void* mpHandler128;          // +0x128  registered message handler
    void* mArgs12C[4];           // +0x12c  handler arguments

    void  Init();                          // 0x01076180
    void  SetMidPanel();                   // 0x010755d0
    void  FUN_01076a00();                  // 0x01076a00
    void  FUN_01076a60();                  // 0x01076a60
    void* FUN_010666a0(void* p);           // 0x010666a0
    void* FUN_0106edc0(void* p);           // 0x0106edc0 (on FUN_010666a0 result)

    void  FUN_01077470();
    void  FUN_01077550();
    void  FUN_01077630();
    bool  FUN_01077830(void* p);
    int   FUN_01077860(float a, float b);
    u8    FUN_01077900(void* p);
    u32   FUN_01077960(void* p);
    void  FUN_01077990(void* p);  // 0x01077990 (SP::cSPUISpaceTrading::FUN_01077990)
    void  FUN_010779e0();  // 0x010779e0 (SP::cSPUISpaceTrading::FUN_010779e0)
    bool  FUN_01077b70(void* a1, u32* pOut);  // 0x01077b70 (SP::cSPUISpaceTrading::FUN_01077b70)
    void  FUN_01077bf0(void* a1);
    void  FUN_01077ce0(void* a1);
    void  FUN_01077d30();
    void  FUN_01077e20();
};  // namespace SP
}
// ---- items of slice s01077470 end

// @ 0x01075450
int cTrading::F1075450()
{
    int id = mId120;
    if (id == -1)
        return 0;
    if (mFlag124)
        return (int)FUN_00b3d3d0()->F1039ab0(id);
    return (int)FUN_00b3d3d0()->F1039ad0(id);
}

// @ 0x01075510
void cTrading::F1075510()
{
    if (m14)
    {
        if (m10)
            m10->FDC(m14);
        FUN_008076f0(m14);
        if (m14)
        {
            void* p = m14;
            m14 = 0;
            ((RefObj_s0107_4bb0*)p)->Release();
        }
        if (m18)
        {
            void* p = m18;
            m18 = 0;
            ((RefObj_s0107_4bb0*)p)->Release();
        }
    }
}

// @ 0x01075570
void cTrading::F1075570()
{
    if (m20)
    {
        if (m1c)
            m1c->FDC(m20);
        FUN_008076f0(m20);
        if (m20)
        {
            void* p = m20;
            m20 = 0;
            ((RefObj_s0107_4bb0*)p)->Release();
        }
        if (m24)
        {
            void* p = m24;
            m24 = 0;
            ((RefObj_s0107_4bb0*)p)->Release();
        }
    }
}

// @ 0x010755d0
void cTrading::SetMidPanel()
{
    mLayout->FindWindowByID(0x4c19a88, 1)->SetVisible(1, 0);
    mLayout->FindWindowByID(0x4d149a8, 1)->SetVisible(1, 0);
    mLayout->FindWindowByID(0x4c1b588, 1)->SetVisible(1, 0);
    mLayout->FindWindowByID(0x4c1510e, 1)->SetVisible(1, 0);
    mLayout->FindWindowByID(0x4c1510a, 1)->SetVisible(2, 0);
    mLayout->FindWindowByID(0x4c1510c, 1)->SetVisible(2, 0);
}

// @ 0x01075690
void cTrading::RemoveExistingItem()
{
    if (mId120 == -1)
        return;
    Layout* lay = mLayout;
    IWindow_s0107_4bb0* w;
    if (mFlag124)
        w = lay->FindWindowByID(mId120 + 0x10000, 1);
    else
        w = lay->FindWindowByID(mId120 + 0x20000, 1);
    if (w)
    {
        IWindow_s0107_4bb0* o = w->Get10();
        IWindow_s0107_4bb0* w2 = o->F0(0x4c6f028, 1);
        if (w2)
            w2->SetVisible(1, 0);
    }
    if (mId120 != -1)
    {
        CountedObj* it = (CountedObj*)(mFlag124 ? FUN_00b3d3d0()->F1039ab0(mId120)
                                                : FUN_00b3d3d0()->F1039ad0(mId120));
        if (it)
        {
            while (it->mCount)
                FUN_00b3d3d0()->F103b950(0, mFlag124, it, 1);
        }
    }
    mId120 = -1;
}

// @ 0x01075760
void cTrading::F1075760()
{
    if (m1c)
    {
        void* p = m1c;
        m1c = 0;
        ((RefObj_s0107_4bb0*)p)->Release();
    }
    if (m10)
    {
        void* p = m10;
        m10 = 0;
        ((RefObj_s0107_4bb0*)p)->Release();
    }
    IWindow_s0107_4bb0* w = mLayout->FindWindowByID(0x5da83b8, 1);
    if (w)
    {
        w->F108(this);
        w->SetVisible(1, 0);
        IWindow_s0107_4bb0* w2 = mLayout->FindWindowByID(0x5e62a48, 1);
        w2->F108(this);
        w2->SetVisible(1, 0);
    }
    if (mLayout)
    {
        Layout* l = mLayout;
        mLayout = 0;
        l->Release();
    }
}

// @ 0x01075810
void cTrading::F1075810(int flag, void* item)
{
    int n = (flag & 0xff) ? FUN_00b3d3d0()->F1039c00(item)->mCount
                          : FUN_00b3d3d0()->F1039b70(item);
    if (item && ((Sender*)item)->mCount < n &&
        FUN_00b3d3d0()->F103b950(1, flag, item, 0) == 0)
    {
        mLayout->FindWindowByID(0x4c1510f, 1)->SetVisible(2, 1);
        mLayout->FindWindowByID(0x5db90d0, 1)->SetVisible(2, 1);
    }
    else
    {
        mLayout->FindWindowByID(0x4c1510f, 1)->SetVisible(2, 0);
        mLayout->FindWindowByID(0x5db90d0, 1)->SetVisible(2, 0);
    }
    if (item && ((Sender*)item)->mCount != 0 &&
        FUN_00b3d3d0()->F103b950(0, flag, item, 0) == 0)
    {
        mLayout->FindWindowByID(0x4c1510d, 1)->SetVisible(2, 1);
        mLayout->FindWindowByID(0x5db90d1, 1)->SetVisible(2, 1);
    }
    else
    {
        mLayout->FindWindowByID(0x4c1510d, 1)->SetVisible(2, 0);
        mLayout->FindWindowByID(0x5db90d1, 1)->SetVisible(2, 0);
    }
}

// @ 0x01075990
void cTrading::F1075990()
{
    SpaceRoot* r = (SpaceRoot*)FUN_010666a0();
    r->m61c->F0E31030(0x10000, 0x144dbf9c, 1, 0x697075e);
}

// @ 0x010759c0
void cSPUISpaceTrading::Fn10759C0(IWindow* w, TradeItem* item, unsigned isUser)
{
    TradeItem* t;
    int idx = mField120;
    if (idx == -1) {
        t = 0;
    }
    else if (mField124) {
        t = GetSpaceTrading()->GetUserItem(idx);
    }
    else {
        t = GetSpaceTrading()->GetNPCItem(idx);
    }

    int saved = 0;
    if (t != 0) {
        saved = t->mCount;
        t->mCount = 0;
    }
    int kind = GetSpaceTrading()->Fn103B950(1, isUser, item, 0);
    if (t != 0) {
        t->mCount = saved;
    }

    IWindow* w1 = (IWindow*)mTooltip.FindWindow(0x51a37b8, true);
    if (w1 != 0) {
        IWindow* child = (IWindow*)w1->Slot0C(0xf15f4bd);
        if (child != 0) {
            w1->Slot80(item->Slot28());

            float wa = w1->Slot38()[2] - w1->Slot38()[0];
            child->Slot14(0);
            float wb = w1->Slot38()[2] - w1->Slot38()[0];
            float maxw = (wb > mTooltip.mMaxWidth) ? wb : mTooltip.mMaxWidth;

            float* r = w1->Slot38();
            w1->Slot74(maxw, r[3] - r[1]);

            IWindow* w2 = (IWindow*)mTooltip.FindWindow(0x5fd4ce0, true);
            float* r2 = w2->Slot38();
            w2->Slot74((r2[2] - r2[0]) + maxw - wa, r2[3] - r2[1]);
        }
    }

    IWindow* w3 = (IWindow*)mTooltip.FindWindow(0x6565a88, true);
    if (w3 != 0) {
        w3->SetFlag(1, kind == 4);
    }
    IWindow* w4 = (IWindow*)mTooltip.FindWindow(0x6565a90, true);
    if (w4 != 0) {
        w4->SetFlag(1, kind == 2);
    }

    IWindow* w5 = (IWindow*)mTooltip.FindWindow(0x6567fa0, true);
    if (w5 != 0) {
        IWindow* child5 = (IWindow*)w5->Slot0C(0xf15f4bd);
        if (child5 != 0) {
            g_16e0d08->mField38 = item->mField30;
            switch (kind) {
            case 0:
                w5->Slot80((void*)0x13ec468);
                break;
            case 1:
                w5->Slot80((void*)mStrDC.GetText());
                break;
            case 2:
                w5->Slot80((void*)mStrB4.GetText());
                break;
            case 3:
                w5->Slot80((void*)mStrC8.GetText());
                break;
            case 4:
                w5->Slot80((void*)mStrF0.GetText());
                break;
            }
            child5->Slot14(1);
        }
    }

    IWindow* w6 = (IWindow*)mTooltip.FindWindow(0x51a37b9, true);
    if (w6 != 0) {
        IWindow* child6 = (IWindow*)w6->Slot0C(0xf15f4bd);
        if (child6 != 0) {
            w6->Slot80(item->Slot2C());
            child6->Slot14(1);
        }
    }

    IWindow* w7 = (IWindow*)mTooltip.FindWindow(0x6567ff8, true);
    IWindow* w8 = (IWindow*)mTooltip.FindWindow(0x6568000, true);
    if (w7 != 0 && w8 != 0) {
        w7->SetFlag(1, 0);
        w8->SetFlag(1, 0);
        mTooltip.UpdateLayout();
        w7->SetFlag(1, kind == 4);
        w8->SetFlag(1, kind != 4);
    }

    unsigned st = 0;
    AudioSystem* at = GetSystemAT();
    if (at != 0) {
        st = at->Slot20();
    }
    AudioSystem* at2 = GetSystemAT();
    if (at2 != 0) {
        at2->Slot38(0x3475365);
        at2->Slot40(0x3475381, 0x8821b509);
        at2->Slot40(0x3475385, st);
        at2->Slot58();
    }
    mTooltip.UpdateTimeoutB(w);
}

// @ 0x01075db0
void cSPUISpaceTrading::Fn1075DB0()
{
    mpVtbl0 = (void*)0x149c590;
    mpVtbl1 = (void*)0x149c580;
    mpVtbl2 = (void*)0x149c578;

    if (mHandler != 0) {
        void* h = mHandler;
        mHandler = 0;
        RemoveHandler(h, mH10C, mH110, mH114, mH118);
    }
    if (mLayout != 0) {
        ((RefObj*)mLayout)->v2();
    }
    mStrF0.Destroy();
    mStrDC.Destroy();
    mStrC8.Destroy();
    mStrB4.Destroy();
    mTooltip.Destroy();

    if (mAnims.mpBegin != 0) {
        if (*(int*)((char*)mAnims.mpBegin - 4) != 0) {
            operator_delete_array(mAnims.mpBegin);
        }
    }
    mItems.Destroy();
    if (mField24 != 0) ((RefObj*)mField24)->v1();
    if (mField20 != 0) ((RefObj*)mField20)->v1();
    if (mField1C != 0) ((RefObj*)mField1C)->v1();
    if (mField18 != 0) ((RefObj*)mField18)->v1();
    if (mField14 != 0) ((RefObj*)mField14)->v1();
    if (mField10 != 0) ((RefObj*)mField10)->v1();

    mpVtbl2 = (void*)0x13eb394;
    mpVtbl1 = (void*)0x13ec458;
    mpVtbl0 = (void*)0x13eb938;
}

// @ 0x01075ef0
void cSPUISpaceTrading::Deactivate()
{
    mField11C = 0;
    mField120 = -1;

    if (mHandler != 0) {
        void* h = mHandler;
        mHandler = 0;
        RemoveHandler(h, mH10C, mH110, mH114, mH118);
    }

    GetSpaceTrading()->Fn103DBD0(1);

    while (mItems.mpBegin != mItems.mpEnd) {
        ((cSPUILayout_s0107_59c0**)mItems.mpEnd)[-1]->Shutdown(1);
        mItems.mpEnd = (char*)mItems.mpEnd - 4;
        void* o = *(void**)mItems.mpEnd;
        if (o != 0) {
            ((RefObj*)o)->v2();
        }
    }
    while (mAnims.mpBegin != mAnims.mpEnd) {
        void* o = *(void**)((char*)mAnims.mpEnd - 4);
        if (o != 0) {
            ((RefObjA*)o)->v0(1);
        }
        mAnims.mpEnd = (char*)mAnims.mpEnd - 4;
    }

    Fn1075510();
    Fn1075570();
    Fn1075760();
    mTooltip.Shutdown();

    MessageServer()->Slot18(0x4c70ce5, 0, 0, 0);
}

// @ 0x01075ff0
void cSPUISpaceTrading::UpdateMidPanel()
{
    if (mField120 != -1) {
        TradeItem* item = mField124 ? GetSpaceTrading()->GetUserItem(mField120)
                                    : GetSpaceTrading()->GetNPCItem(mField120);
        if (item != 0) {
            wchar_t money[0x18];
            wchar_t num[0x18];
            int v = item->Fn6C0200() * item->mCount;
            money[0] = 0;
            FUN_008822e0((double)v, money, 0x10, (int)g_15b9448, (int)0x149c570);

            IWindow* w1 = mLayout->FindWindowByID(0x4c1b588, 1);
            w1->SetFlag(1, 1);
            w1->Slot80(money);

            Fn1075810(mField124, item);

            SetNumberString(item->mCount, item->mCount >> 31, num, 0x10);
            num[0xf] = 0;
            wcsncat_(money, L"/", 0xf);

            int n;
            if (mField124) {
                void* p = GetSpaceTrading()->Fn1039C00();
                n = (p != 0) ? ((ItemInfo*)p)->mValue : 0;
            }
            else {
                n = GetSpaceTrading()->Fn1039B70();
            }
            wchar_t num2[0x18];
            SetNumberString(n, n >> 31, num2, 0x10);
            num2[0xf] = 0;
            wcsncat_(money, num2, 0xf);

            IWindow* w2 = mLayout->FindWindowByID(0x4c1510e, 1);
            w2->SetFlag(1, 1);
            w2->Slot80(money);
        }
    }
}

// @ 0x01076180
void cSPUISpaceTrading::Init()
{
    cSPUILayout_s0107_59c0* q = *(cSPUILayout_s0107_59c0**)((char*)FUN_00dd1ca0() + 0xc);
    cSPUILayout_s0107_59c0* old = mLayout;
    if (q != old) {
        if (q != 0) ((RefObj*)q)->v1();
        mLayout = q;
        if (old != 0) ((RefObj*)old)->v2();
    }

    IWindow* w1 = mLayout->FindWindowByID(0x5da83b8, 1);
    w1->Slot104(this);
    w1->SetFlag(1, 1);

    IWindow* w2 = mLayout->FindWindowByID(0x5e62a48, 1);
    w2->Slot104(this);
    w2->SetFlag(1, 1);

    IWindow* w3 = mLayout->FindWindowByID(0x5da83b9, 1);
    void* old3 = mField1C;
    if (w3 != old3) {
        if (w3 != 0) ((RefObj*)w3)->v0();
        mField1C = w3;
        if (old3 != 0) ((RefObj*)old3)->v1();
    }

    IWindow* w4 = mLayout->FindWindowByID(0x5da83b8, 1);
    void* old4 = mField10;
    if (w4 != old4) {
        if (w4 != 0) ((RefObj*)w4)->v0();
        mField10 = w4;
        if (old4 != 0) ((RefObj*)old4)->v1();
    }

    IWindow* w5 = mLayout->FindWindowByID(0x5e3c090, 1);
    w5->SetFlag(1, 0);

    IWindow* w6 = mLayout->FindWindowByID(0x4c19a88, 1);
    w6->Slot104(this);
}

// @ 0x010762d0
void cSPUISpaceTrading::Fn10762D0()
{
    if (mField11C != 0) {
        Deactivate();
    }
}

// @ 0x010762e0
cSPUISpaceTrading* cSPUISpaceTrading::Fn10762E0()
{
    mpVtbl1 = (void*)0x13ec458;
    mField08 = 0;
    mpVtbl2 = (void*)0x13eb394;
    mpVtbl0 = (void*)0x149c590;
    mpVtbl1 = (void*)0x149c580;
    mpVtbl2 = (void*)0x149c578;

    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1C = 0;
    mField20 = 0;
    mField24 = 0;
    mItems.mpBegin = 0;
    mItems.mpEnd = 0;
    mItems.mpCap = 0;
    mAnims.mpBegin = 0;
    mAnims.mpEnd = 0;
    mAnims.mpCap = 0;

    mTooltip.Construct();
    mStrB4.Construct();
    mStrC8.Construct();
    mStrDC.Construct();
    mStrF0.Construct();

    mLayout = 0;
    mHandler = 0;
    mH10C = 0;
    mH110 = 0;
    mH114 = 0;
    mH118 = 0;
    mField11C = 0;
    mField120 = -1;
    return this;
}

// @ 0x010763c0
void cSPUISpaceTrading::Fn10763C0()
{
    if (mField120 != -1) {
        TradeItem* item = mField124 ? GetSpaceTrading()->GetUserItem(mField120)
                                    : GetSpaceTrading()->GetNPCItem(mField120);
        if (item != 0) {
            item->Slot28();

            bool flag = true;
            int kind = GetSpaceTrading()->Fn103B950(1, mField124, item, 1);
            if (kind - 1 == 0 || kind - 2 == 0 || kind - 3 == 0) {
                flag = false;
            }

            IWindow* w1 = mLayout->FindWindowByID(0x4c19a88, 1);
            w1->SetFlag(1, 1);
            void* key;
            SetImageFromKey(w1, item->Slot30(&key));

            UpdateMidPanel();

            IWindow* w2 = mLayout->FindWindowByID(0x4d149a8, 1);
            w2->SetFlag(1, 1);
            w2->Slot80(item->Slot28());

            IWindow* w3 = mLayout->FindWindowByID(0x4c1510a, 1);
            IWindow* w4 = mLayout->FindWindowByID(0x4c1510c, 1);
            if (mField124) {
                w3->SetFlag(2, flag);
                w4->SetFlag(2, 0);
            }
            else {
                w3->SetFlag(2, 0);
                w4->SetFlag(2, flag);
            }
        }
    }
}

// @ 0x01076a00
void cSPUISpaceTrading_s0107_6540::AddNPCItems()
{
    int i = 0;
    while (GetSpaceTrading_s0107_6540()->GetUserItem(i) != 0) {
        TradeItem_s0107_6540* item = GetSpaceTrading_s0107_6540()->GetUserItem(i);
        TradeItemInfo* info = GetSpaceTrading_s0107_6540()->Fn1039c00(item);
        AddItem(mWindow18, i, info->f10, 0x10000, item);
        ++i;
    }
}

// @ 0x01076a60
void cSPUISpaceTrading_s0107_6540::AddUserItems()
{
    int i = 0;
    while (GetSpaceTrading_s0107_6540()->GetNPCItem(i) != 0) {
        TradeItem_s0107_6540* item = GetSpaceTrading_s0107_6540()->GetNPCItem(i);
        uint32_t value = GetSpaceTrading_s0107_6540()->Fn1039b70(item);
        AddItem(mWindow24, i, value, 0x20000, item);
        ++i;
    }
    PlayerInventory* inv = SpaceGameGet()->GetPlayerInventory();
    uint32_t n = inv->GetItemCount();
    if (n > 0) {
        uint32_t k = n;
        do {
            AddItem(mWindow24, i, 0, 0x20000, 0);
            ++i;
        } while (--k);
    }
}

// @ 0x01076b00
void cSPUISpaceTrading_s0107_6540::Fn1076b00()
{
    while (((uint32_t)((char*)mItemsEnd - (char*)mItemsBegin)) & 0xfffffffc) {
        mItemsEnd[-1]->Shutdown(1);
        --mItemsEnd;
        cSPUILayout_s0107_6540* old = *mItemsEnd;
        if (old)
            old->Release();
    }
    AddUserItems();
    AddNPCItems();
    if (mActiveItemIndex != -1)
        UpdateMidPanel();
    FUN_00807690(mClient14, 0);
    FUN_00807690(mClient20, 0);
}

// @ 0x01076b80
bool cSPUISpaceTrading_s0107_6540::DoMessage(IWindow_s0107_6540* win, Message* msg)
{
    if (msg->type == 0xc) {
        uint32_t n = mAnimEnd - mAnimBegin;
        for (uint32_t i = 0; i < n; i++)
            mAnimBegin[i]->Update();
        mSub50.Fn36540();
    }

    if (msg->type == 0x1b) {
        if (win->GetControlID() >= 0x10000 && win->GetControlID() <= 0x21000) {
            IWindow_s0107_6540* parent = win->GetParent();
            if (parent) {
                bool isUser;
                TradeItem_s0107_6540* item;
                if (win->GetControlID() >= 0x10000 && win->GetControlID() <= 0x11000) {
                    isUser = true;
                    item = GetSpaceTrading_s0107_6540()->GetUserItem(win->GetControlID() - 0x10000);
                } else {
                    isUser = false;
                    item = GetSpaceTrading_s0107_6540()->GetNPCItem(win->GetControlID() - 0x20000);
                }
                IWindow_s0107_6540* w = parent->FindWindowByID(0x64bb040, 1);
                if (item) {
                    w->SetFlag(1, 1);
                    Fn10759c0(parent, (TradeItem_s0107_6540*)item, isUser);
                } else {
                    w->SetFlag(1, 0);
                    mSub50.Fn36620();
                }
            }
        }
    }

    if (msg->type == 0x1c) {
        IWindow_s0107_6540* parent = win->GetParent();
        if (parent && win->GetControlID() >= 0x10000 && win->GetControlID() <= 0x21000) {
            parent->FindWindowByID(0x64bb040, 1)->SetFlag(1, 0);
            mSub50.Fn36620();
        }
    }

    if (msg->type != 0x17)
        return false;

    switch (msg->source->GetControlID()) {
    case 0x4c1510a:
        KillSetiEffects(0x23d6523e, GetRecorderState());
        mTrading = true;
        GetSpaceTrading_s0107_6540()->PerformTrade();
        mTrading = false;
        SetMidPanel();
        mActiveItemIndex = -1;
        SetGlobalProperty(0x8952a239, 1.0f);
        {
            Empire* e = GetStarManager()->GetEmpireByID(IsArchived()->GetAvatar());
            uint32_t a, b;
            GetAED4D0()->Fn28(0x55125425, e->f58, &b, &a);
            GetB490()->Fn(b, a, 0, 1);
        }
        GetSpaceTrading_s0107_6540()->Fn103dbd0(0);
        {
            uint32_t planet = GetActivePlanet()->f13c;
            GetSpaceTrading_s0107_6540()->CreateNPCInventory(planet, 0);
        }
        Fn1076b00();
        return false;
    case 0x4c1510c:
        KillSetiEffects(0x2fd72b7e, GetRecorderState());
        mTrading = true;
        GetSpaceTrading_s0107_6540()->PerformTrade();
        mTrading = false;
        SetMidPanel();
        mActiveItemIndex = -1;
        SetGlobalProperty(0x3ec6f5f7, 1.0f);
        {
            Empire* e = GetStarManager()->GetEmpireByID(IsArchived()->GetAvatar());
            uint32_t a, b;
            GetAED4D0()->Fn28(0x55125425, e->f58, &b, &a);
            GetB490()->Fn(b, a, 0, 1);
        }
        GetSpaceTrading_s0107_6540()->Fn103dbd0(0);
        {
            uint32_t planet = GetActivePlanet()->f13c;
            GetSpaceTrading_s0107_6540()->CreateNPCInventory(planet, 0);
        }
        Fn1076b00();
        return false;
    case 0x4c1510d:
        KillSetiEffects(0xc16d25b1, GetRecorderState());
        GetSpaceTrading_s0107_6540()->Fn103b950(0, mIsUserItem, GetActiveItem(), 1);
        UpdateMidPanel();
        SetGlobalProperty(0xa63b066b, 1.0f);
        return false;
    case 0x4c1510f:
        KillSetiEffects(0xc16d25b1, GetRecorderState());
        GetSpaceTrading_s0107_6540()->Fn103b950(1, mIsUserItem, GetActiveItem(), 1);
        UpdateMidPanel();
        SetGlobalProperty(0xa84a842c, 1.0f);
        return false;
    case 0x5db90d0: {
        {
            AudioSystem_s0107_6540* a0 = GetSystemAT_s0107_6540();
            KillSetiEffects(0xc16d25b1, a0 ? a0->Slot20() : 0);
        }
        ItemLoop(this, 1);
        UpdateMidPanel();
        AudioSystem_s0107_6540* at = GetSystemAT_s0107_6540();
        if (at) {
            at->Slot38(0x3cdd1a9);
            at->Slot40(0x34753a7, 0xa84a842c);
            at->Slot3C(0x34753aa, 1.0f);
            at->Slot58();
        }
        return false;
    }
    case 0x5db90d1: {
        {
            AudioSystem_s0107_6540* a0 = GetSystemAT_s0107_6540();
            KillSetiEffects(0xc16d25b1, a0 ? a0->Slot20() : 0);
        }
        ItemLoop(this, 0);
        UpdateMidPanel();
        AudioSystem_s0107_6540* at = GetSystemAT_s0107_6540();
        if (at) {
            at->Slot38(0x3cdd1a9);
            at->Slot40(0x34753a7, 0xa63b066b);
            at->Slot3C(0x34753aa, 1.0f);
            at->Slot58();
        }
        return false;
    }
    default:
        break;
    }

    uint32_t id = win->GetControlID();
    uint32_t rel = id - 0x20000;
    if (rel <= 0x1000) {
        IWindow_s0107_6540* w = mLayout->FindWindowByID(id, 1);
        bool bad;
        if (!w) {
            bad = true;
        } else {
            uint32_t fl = w->GetParent()->FindWindowByID(0x5dce858, 1)->GetFlags();
            bad = false;
            if (fl & 1) bad = true;
        }
        TradeItem_s0107_6540* item = GetSpaceTrading_s0107_6540()->GetNPCItem(rel);
        if (bad || !item)
            return false;
        if (!item->Get18())
            return false;
        RemoveExistingItem();
        mIsUserItem = false;
        mActiveItemIndex = rel;
        KillSetiEffects(0x7cd49637, GetRecorderState());
        IWindow_s0107_6540* c = w->GetParent()->FindWindowByID(0x4c6f028, 1);
        if (c) c->SetFlag(1, 1);
        Fn10763c0();
        SetGlobalProperty(0xfd1bd4f, 1.0f);
    }
    if (id - 0x10000 <= 0x1000) {
        IWindow_s0107_6540* w = mLayout->FindWindowByID(id, 1);
        bool bad;
        if (!w) {
            bad = true;
        } else {
            uint32_t fl = w->GetParent()->FindWindowByID(0x5dce858, 1)->GetFlags();
            if (fl & 1) bad = true; else bad = false;
        }
        GetSpaceTrading_s0107_6540()->GetUserItem(id - 0x10000);
        if (bad)
            return false;
        RemoveExistingItem();
        mIsUserItem = true;
        mActiveItemIndex = id - 0x10000;
        KillSetiEffects(0x7cd49637, GetRecorderState());
        IWindow_s0107_6540* c = w->GetParent()->FindWindowByID(0x4c6f028, 1);
        if (c) c->SetFlag(1, 1);
        Fn10763c0();
        SetGlobalProperty(0xfd1bd4f, 1.0f);
    }
    return false;
}

// @ 0x01077470
void SP::cSPUISpaceTrading_s0107_7470::FUN_01077470()
{
    if (mpOwner18 != 0) {
        Obj* old = (Obj*)mpOwner18;
        mpOwner18 = 0;
        ((Fn_v_p)VTSLOT(old, 4))(old);
    }
    Obj* nw = (Obj*)FUN_00807600(L"ScrollFrameVerticalGeneric", &mpOwner18, 1);
    Obj* prev = (Obj*)mpScroll14;
    if (nw != prev) {
        if (nw != 0)
            ((Fn_v_p)VTSLOT(nw, 0))(nw);
        mpScroll14 = nw;
        if (prev != 0)
            ((Fn_v_p)VTSLOT(prev, 4))(prev);
    }
    if (((Fn_p_p)VTSLOT(mpScroll14, 0x10))(mpScroll14) != 0) {
        Obj* t = ((Fn_p_p)VTSLOT(mpScroll14, 0x10))(mpScroll14);
        ((Fn_v_pp)VTSLOT(t, 0xdc))(t, mpScroll14);
    }
    ((Fn_v_pp)VTSLOT(mpField10, 0xd8))(mpField10, mpScroll14);
    Obj* child = ((Fn_p_p)VTSLOT(mpField10, 0x38))(mpField10);
    ((Fn_v_pp)VTSLOT(mpScroll14, 0x60))(mpScroll14, child);
    ((Fn_v_pff)VTSLOT(mpScroll14, 0x64))(mpScroll14, 0.0f, 0.0f);
    FUN_01076a00();
    FUN_00807690_s0107_7470(mpScroll14, 0);
}

// @ 0x01077550
void SP::cSPUISpaceTrading_s0107_7470::FUN_01077550()
{
    if (mpField24 != 0) {
        Obj* old = (Obj*)mpField24;
        mpField24 = 0;
        ((Fn_v_p)VTSLOT(old, 4))(old);
    }
    Obj* nw = (Obj*)FUN_00807600(L"ScrollFrameVerticalGeneric", &mpField24, 1);
    Obj* prev = (Obj*)mpField20;
    if (nw != prev) {
        if (nw != 0)
            ((Fn_v_p)VTSLOT(nw, 0))(nw);
        mpField20 = nw;
        if (prev != 0)
            ((Fn_v_p)VTSLOT(prev, 4))(prev);
    }
    if (((Fn_p_p)VTSLOT(mpField20, 0x10))(mpField20) != 0) {
        Obj* t = ((Fn_p_p)VTSLOT(mpField20, 0x10))(mpField20);
        ((Fn_v_pp)VTSLOT(t, 0xdc))(t, mpField20);
    }
    ((Fn_v_pp)VTSLOT(mpField1C, 0xd8))(mpField1C, mpField20);
    Obj* child = ((Fn_p_p)VTSLOT(mpField1C, 0x38))(mpField1C);
    ((Fn_v_pp)VTSLOT(mpField20, 0x60))(mpField20, child);
    ((Fn_v_pff)VTSLOT(mpField20, 0x64))(mpField20, 0.0f, 0.0f);
    FUN_01076a60();
    FUN_00807690_s0107_7470(mpField20, 0);
}

// @ 0x01077630
void SP::cSPUISpaceTrading_s0107_7470::FUN_01077630()
{
    u8 local[0x14];
    Obj* planet = SP_GetActivePlanet();
    ((cUITimedTooltip_s0107_7470*)&mTooltip)->Init(DAT_015b9550, DAT_015b9554, DAT_015b9558,
                                        0x5fd4ce0, 200, 0xfa);
    Obj* w = ((cUITimedTooltip_s0107_7470*)&mTooltip)->FindWindow(0x51a37b8, true);
    float* r = (float*)((Fn_p_p)VTSLOT(w, 0x38))(w);
    mFieldB0 = r[2] - r[0];
    Init();
    mByte11C = 1;
    mField120 = -1;
    mByte11D = 0;
    cSPSpaceTrading_s0107_7470* inv =
        (cSPSpaceTrading_s0107_7470*)FUN_00b3d3d0(*(void**)((char*)planet + 0x13c), local);
    inv->CreateNPCInventory();
    FUN_01077550();
    FUN_01077470();
    SetMidPanel();
    Obj* ms = SP_MessageServer();
    ((Fn_v_piii)VTSLOT(ms, 0x14))(ms, 0x4c70cc0, 0, 0);
    void* target = &mpField0C;
    Obj* ms2 = SP_MessageServer();
    mBlk108.h = ms2;
    mBlk108.a1 = target;
    mBlk108.a2 = (void*)DAT_0149c5c4;
    mBlk108.a3 = (void*)3;
    mBlk108.a4 = 0;
    if (ms2 != 0 && target != 0) {
        u8* ids = (u8*)DAT_0149c5c4;
        for (u32 o = 0; o < 0xc; o += 4)
            ((Fn_v_ppi)VTSLOT(ms2, 0x24))(ms2, target, *(int*)(ids + o));
    }
    cTerrainEditor* te = (cTerrainEditor*)SP_NounManager();
    Obj* ts = te->GetCurrentTerrainSphere();
    if (ts != 0) {
        if (te->FUN_00c772c0(0x670c73c) == false) {
            te->FUN_00c77bf0(0x670c73c);
            TradeId ids;
            ids.a = 0x8af87c97;
            ids.b = 0xb1b104;
            ids.c = 0x3629f036;
            TradePos pos;
            pos.x = -1.0f;
            pos.y = -1.0f;
            pos.z = 0.0f;
            TradeCtl* t = (TradeCtl*)FUN_0067caf0(ids, 0, 0, pos, 0, 0);
            t->FUN_0067aaf0();
        }
    }
}
