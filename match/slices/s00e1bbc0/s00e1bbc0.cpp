// Slice s00e1bbc0 -- SP::cUIMissionButton::SetTracked (0x00e1bbc0, 2478 bytes): EA Spore
// mission-button refresh. Reads the mission for this button's index, updates the child windows
// (looked up by id through cSPUILayout::FindWindowByID), sets title / reward text / icons and
// (re)creates the owned sub-objects at this+0x5c, +0x60, +0x64, +0x68.
//
// Translation method: the original keeps almost all of its state in one stack frame and calls
// through vtables. To keep the stack-shifted sections exact, locals live in one frame array
// addressed by the original esp-relative offsets (FR(0x2c) is [esp+0x2c] when esp == frame base).
// Control flow follows the asm block order (see the L_ labels). All declarations are at the top
// so the gotos are legal.
//
// Calling convention: __thiscall, this in ECX, no stack parameters (Ghidra signature
// void __thiscall SetTracked(cUIMissionButton*)). Frame size 0x60, callee-saved ebx/ebp/esi/edi.
//
// Unknown helpers are called through their absolute addresses with the arity and convention seen
// in the asm. Their bodies are not part of this slice.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define FR(o) (*(int*)(fr + (o)))
#define FP(o) (*(void**)(fr + (o)))
#define SI(p, o) (*(int*)((unsigned char*)(p) + (o)))
#define SPTR(p, o) (*(void**)((unsigned char*)(p) + (o)))
#define UI(p, o) (*(unsigned*)((unsigned char*)(p) + (o)))

// Virtual calls through the vtable of SELF at byte offset OFF (slot = OFF / 4).
#define VC0(RET, SELF, OFF) (((RET(__thiscall*)(void*))((*(void***)(SELF))[(OFF) / 4]))(SELF))
#define VC1(RET, SELF, OFF, T1, A1) \
    (((RET(__thiscall*)(void*, T1))((*(void***)(SELF))[(OFF) / 4]))((SELF), (A1)))
#define VC2(RET, SELF, OFF, T1, A1, T2, A2) \
    (((RET(__thiscall*)(void*, T1, T2))((*(void***)(SELF))[(OFF) / 4]))((SELF), (A1), (A2)))

// Fixed-address helpers.
#define FIND_WIN(L, ID) (((void*(__thiscall*)(void*, unsigned, int))(0x8105b0))((L), (ID), 1))

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

namespace SP {

struct float4 { float x, y, z, w; };

// ---- engine UI interfaces (only the vtable slots and methods this slice calls) ----

class cSPUILayout;
class cSPUIFeedList;
class cSPUIFeedCategory;
class cScrollFrameVertical;
class IWinWindow;
class IMessageServer;

class IRefObj {                                     // intrusive ref count in slots 0 / 4
public:
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
};

class IRefObjB {                                    // intrusive ref count in slots 8 / 0xc
public:
    PV2
    virtual void AddRef();                          // +0x08
    virtual void Release();                         // +0x0c
};

class IObj5c {                                      // second release path in slot 8
public:
    PV2
    virtual void ReleaseB();                        // +0x08
};

class IObj60 : public IObj5c {
public:
    void Stop();                                    // 0x00e2ed40
};

class IObj64 {                                      // slot 8 + a ref-counted member at +0x10
public:
    PV                                              // +0x00
    PV                                              // +0x04
    virtual void Detach();                          // +0x08
    uint32_t mPad04[3];                             // +0x04 .. +0x0f
    IRefObj mSub10;                                 // +0x10
};

class IObj68 {                                      // stop (slot 0x20) + release (slot 4)
public:
    PV                                              // +0x00
    virtual void Release();                         // +0x04
    PV PV PV PV PV PV                               // +0x08 .. +0x1c
    virtual void Stop();                            // +0x20
};

// Mission-panel window interface: window operations used by the panel setup.
class IWinWindow {
public:
    virtual void Attach();                          // +0x00
    virtual void Release();                         // +0x04
    PV2                                             // +0x08, +0x0c
    virtual void* GetContent();                     // +0x10
    virtual void Activate();                        // +0x14
    PV8                                             // +0x18 .. +0x34
    virtual float4* GetRect();                      // +0x38
    PV8 PV4                                         // +0x3c .. +0x68
    virtual void SetRect(void* pRect);              // +0x6c
    virtual void SetPosition(float x, float y);     // +0x70
    PV2                                             // +0x74, +0x78
    virtual void SetSize(int w, int h);             // +0x7c
    PV8 PV8 PV4 PV2                                 // +0x80 .. +0xd4
    virtual void SetParent(void* pParent);          // +0xd8
    virtual void SetOwner(void* pOwner);            // +0xdc
    PV8 PV2                                         // +0xe0 .. +0x104
    virtual void SetHandler(void* pHandler);        // +0x108
};

class IMessageServer {
public:
    PV8 PV                                          // +0x00 .. +0x20
    virtual void Subscribe(void* pHandler, uint32_t messageId);   // +0x24
};

class cSPUIFeedList {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    void* Ctor();                                                    // 0x00663040
    void AddWindow(void* pWindow, uint32_t id, void* a, void* b);    // 0x00663860
    void* FindEntry(uint32_t id);                                    // 0x00662a40
    void Shutdown();                                                 // 0x006628d0
    void SetEnabled(bool b);                                         // 0x00662920
};

class cSPUIFeedCategory : public IRefObjB {
public:
    void ShutdownChildren();                                         // 0x006657a0
};

class cScrollFrameVertical {
public:
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
    PV                                              // +0x08
    PV                                              // +0x0c
    uint32_t mPad04[3];                             // +0x04 .. +0x0f
    IWinWindow* mpObj10;                            // +0x10
    uint32_t mPad14;                                // +0x14
    IWinWindow* mpObj18;                            // +0x18
    void* Ctor();                                   // 0x0082a040 (returns this)
    bool Create(uint32_t id, int a, int b);         // 0x0082a140
    float GetScrollOffset();                        // 0x0082a4e0
    void Shutdown();                                // 0x0082a450
};

class cStarRecordList {                             // eastl vector of star records at +0x44
public:
    void* mpBegin;                                  // +0x44
    void* mpEnd;                                    // +0x48
    void* mpCapacity;                               // +0x4c
    void erase(void* first, void* last);            // 0x00e25bd0
    ~cStarRecordList();                             // 0x00ae6970
};

class cUIHints {
public:
    int SetFlag(int flag, int value);               // 0x0067c420
};
cUIHints* FUN_0067cac0();                           // 0x0067cac0

class cSPUILayout {
public:
    IWinWindow* FindWindowByID(uint32_t id, int a); // 0x008105b0
};

IMessageServer* MessageServer();                    // 0x0067dcc0
void* operator_new(unsigned size, const char* pFile, int a, int b, int c, int d);   // 0x00f473a0
void FUN_00e1c8b0(void* a, void* b, void* c);                                       // 0x00e1c8b0
extern const uint32_t g_missionMessageIds[5];                                       // 0x014802b0

namespace EA { namespace Messaging {
void RemoveHandler(IMessageServer* pServer, void* pHandler, const uint32_t* pIds,
                   uint32_t count, uint32_t flags);                                 // 0x00571db0
}}

// The mission card panel the button is a part of (its methods are reached by a tail call).
class cUIMissionCardPanel {
public:
    void OnNotify(void* p1, void* p2, void* p3, void* p4);   // 0x00e186d0
    void ShutdownCard();                                     // 0x00e18810
    void DestroyMembers();                                   // 0x00e18980
    void ShutdownA();                                        // 0x00e18a30
};

class cUIMissionButton {
public:
    void SetTracked();
    void Shutdown();                                                     // 0x00e1ca30
    void Destroy();                                                      // 0x00e1cba0
    void CreateMissionButton(void* p1, void* p2, void* p3, void* p4);    // 0x00e1cc80
    void ShutdownList();                                                 // 0x00e1cfb0

    void* mpVtbl00;                        // +0x00
    uint32_t mPad04;                       // +0x04
    void* mpVtbl08;                        // +0x08
    void* mpVtbl0c;                        // +0x0c
    uint32_t mTag10;                       // +0x10
    void* mpSelf14;                        // +0x14
    cSPUILayout* mpLayout;                 // +0x18
    uint32_t mPad1c;                       // +0x1c
    void* mpMission;                       // +0x20
    void* mpParent;                        // +0x24
    void* mpItem;                          // +0x28
    uint32_t mPad2c[5];                    // +0x2c
    void* mpVtbl40;                        // +0x40
    cStarRecordList mStars;                // +0x44
    uint32_t mPad50[2];                    // +0x50
    cScrollFrameVertical* mpScrollFrame;   // +0x58
    IObj5c* mpObj5c;                       // +0x5c
    IObj60* mpObj60;                       // +0x60
    IObj64* mpObj64;                       // +0x64
    IObj68* mpObj68;                       // +0x68
    cSPUIFeedList* mpFeedList;             // +0x6c
    cSPUIFeedCategory* mpCategoryA;        // +0x70
    cSPUIFeedCategory* mpCategoryB;        // +0x74
    IMessageServer* mpMessageServer;       // +0x78
    void* mpHandlerArg;                    // +0x7c
    const uint32_t* mpMessageIds;          // +0x80
    uint32_t mMessageIdCount;              // +0x84
    uint32_t mHandlerFlags;                // +0x88
    uint32_t mWindowId;                    // +0x8c
    int mIndex;                            // +0x90
};

// @ 0x00e1bbc0
void cUIMissionButton::SetTracked()
{
    unsigned char* self;
    unsigned char fr[0x68];
    void* item;
    void* w;
    void* w2;
    void* t;
    void* s;
    void* t2;
    void* wnd;
    void* wnd2;
    void* wnd3;
    void* wnd4;
    void* wnd5;
    void* esi;
    void* ebp;
    void* ebx_;
    void* edi;
    void* mgr;
    void* empire;
    void* home;
    void* r;
    void* r2;
    void* obj;
    void* ownA;
    void* ownB;
    void* m;
    void* x;
    void* newp;
    void* o68;
    void* obj64;
    void* ecx5c;
    void* esiA;
    void* esiB;
    void* sel;
    void* newS;
    unsigned char al;
    unsigned f;
    int idx;
    int a;
    int b;
    int c;
    int kind;
    float fv;
    unsigned tag;

    self = (unsigned char*)this;
    FR(0x14) = (int)self;
    if (SPTR(self, 0x18) == 0) return;

    // Item for this button's index: array of pointers at +0x44 .. +0x48 (end).
    idx = SI(self, 0x90);
    item = 0;
    if (idx >= 0 && idx < ((SI(self, 0x48) - SI(self, 0x44)) >> 2))
        item = ((void**)SPTR(self, 0x44))[idx];

    FP(0x28) = item;
    FP(0x20) = 0;   // mission
    FP(0x10) = 0;   // sel
    FR(0x1c) = 0;   // ownB
    FP(0x24) = 0;   // ownA

    tag = UI(self, 0x10);
    if (tag == 0x1654c05) {
        if (item) FP(0x20) = VC1(void*, item, 0xc, unsigned, 0x2aa5ada);
    } else if (item) {
        FP(0x10) = VC1(void*, item, 0xc, unsigned, 0x14066ce5);
        if (FP(0x10)) {
            VC0(void, FP(0x10), 0x80);
            VC0(void, FP(0x10), 0x84);
            FP(0x24) = VC1(void*, FP(0x10), 0xc, unsigned, 0x7406a570);
            FR(0x1c) = (int)VC1(void*, FP(0x10), 0xc, unsigned, 0x34364118);
        }
    }

    // ---- window 0x51d2fb8: mission-type toggle ----
    w = FIND_WIN(SPTR(self, 0x18), 0x51d2fb8);
    if (w) {
        w2 = VC1(void*, w, 0xc, unsigned, 0x8ed27e7a);
        if (w2) {
            if (FP(0x20) == 0) {
                t = VC0(void*, w2, 0x10);
                VC2(void, t, 0x7c, int, 1, int, 0);
            } else {
                t = VC0(void*, w2, 0x10);
                VC2(void, t, 0x7c, int, 1, int, 1);
                VC2(void, w2, 0x28, int, 1, int, 1);
                mgr = ((void*(__stdcall*)(void*, int))(0xfeb9f0))(FP(0x20), 0);
                al = ((unsigned char(__thiscall*)(void*))(0xfebe50))(mgr);
                VC2(void, w2, 0x28, int, 4, int, (int)al);
            }
        }
    }

    // ---- window 0x3c4925e: enable flags ----
    s = FIND_WIN(SPTR(self, 0x18), 0x3c4925e);
    if (s) {
        if (FP(0x20) == 0) {
            VC2(void, s, 0x7c, int, 1, int, 0);
        } else {
            VC2(void, s, 0x7c, int, 1, int, 1);
            f = UI(FP(0x20), 0x130);
            if (((f >> 4) & 1) || (f & 1))
                VC2(void, s, 0x7c, int, 2, int, 0);
            else
                VC2(void, s, 0x7c, int, 2, int, 1);
        }
    }

    // ---- window 0x519cac8: title text ----
    t = FIND_WIN(SPTR(self, 0x18), 0x519cac8);
    if (t == 0) goto L_wnd_f3ec;
    VC2(void, t, 0x7c, int, 2, int, 1);
    FR(0x2c) = 0;   // wstring at 0x2c (begin), 0x30 (end), 0x34 (cap)
    FR(0x30) = 0;
    FR(0x34) = 0;
    ((void(__thiscall*)(void*, const wchar_t*))(0x579a90))(&FR(0x2c), (const wchar_t*)0x13ec468);
    if (FP(0x20) != 0) {
        VC1(void, FP(0x20), 0xc4, void*, &FR(0x2c));
    } else if (FP(0x10) != 0) {
        VC1(void, FP(0x10), 0x9c, void*, &FR(0x2c));
    } else if (FR(0x1c) != 0) {
        VC1(void, (void*)FR(0x1c), 0x9c, void*, &FR(0x2c));
    } else {
        ((void(__thiscall*)(void*, unsigned, unsigned, int))(0x6b5770))(&FR(0x3c), 0x8b96f855, 0x667c672, 0);
        obj = ((void*(__thiscall*)(void*))(0x6b55c0))(&FR(0x3c));
        ((void(__thiscall*)(void*, void*))(0x5c3d90))(&FR(0x2c), obj);
        ((void(__thiscall*)(void*))(0x6b5240))(&FR(0x3c));
    }
    VC1(void, t, 0x80, int, FR(0x2c));
    r = VC1(void*, t, 0xc, unsigned, 0xf15f4bd);
    if (r) VC1(void, r, 0x1c, int, 1);
    if (SPTR(self, 0x58)) ((void(__stdcall*)(int))(0x82a500))(1);
    if (((FR(0x34) - FR(0x2c)) & ~1) > 2 && FR(0x2c) != 0)
        ((void(__cdecl*)(void*))(0xf47380))((void*)FR(0x2c));

L_wnd_f3ec:
    // ---- window 0xf3ec5429: rewards text ----
    t2 = FIND_WIN(SPTR(self, 0x18), 0xf3ec5429);
    if (t2 == 0) goto L_release68;
    VC2(void, t2, 0x7c, int, 2, int, 1);
    FR(0x2c) = 0;
    FR(0x30) = 0;
    FR(0x34) = 0;
    ((void(__thiscall*)(void*, const wchar_t*))(0x579a90))(&FR(0x2c), (const wchar_t*)0x13ec468);
    if (FP(0x20) != 0) {
        ((void(__thiscall*)(void*, void*))(0xc48c20))(FP(0x20), &FR(0x2c));
    } else {
        m = FP(0x10);
        if (m != 0 && VC0(int, m, 0xa4)) {
            VC1(void, m, 0xa8, void*, &FR(0x2c));
        } else {
            m = (void*)FR(0x1c);
            if (m != 0 && VC0(int, m, 0xa4))
                VC1(void, m, 0xa8, void*, &FR(0x2c));
        }
    }
    VC1(void, t2, 0x80, int, FR(0x2c));
    if (((FR(0x34) - FR(0x2c)) & ~1) > 2 && FR(0x2c) != 0)
        ((void(__cdecl*)(void*))(0xf47380))((void*)FR(0x2c));

L_release68:
    // ---- release this+0x68 and this+0x64 ----
    if (SPTR(self, 0x68)) VC0(void, SPTR(self, 0x68), 0x20);
    if (SPTR(self, 0x64)) VC0(void, SPTR(self, 0x64), 0x8);

    // ---- window 0x519ccf8 + date/time ----
    ebx_ = FIND_WIN(SPTR(self, 0x18), 0x519ccf8);
    ((void(__thiscall*)(void*, int))(0x92e3d0))(&FR(0x50), 2);
    esi = 0;
    FR(0x5c) = 0;
    FR(0x60) = 0;
    FR(0x64) = 0;
    FR(0x18) = 0;
    if (ebx_ == 0) goto L_236;
    VC2(void, ebx_, 0x7c, int, 1, int, 0);
    if (FP(0x20) == 0) goto L_07f;
    empire = ((void*(__thiscall*)(void*))(0xc451e0))(FP(0x20));
    if (empire == 0) goto L_236;
    esi = ((void*(__thiscall*)(void*))(0xc30c80))(empire);
    if (esi == 0) goto L_236;
    ((void(__thiscall*)(void*, int))(0x7eb820))(&FR(0x50), 0xc);
    SI((void*)FR(0x5c), 4) = SI(esi, 0x508);
    SI((void*)FR(0x5c), 8) = SI(esi, 0x504);
    SI((void*)FR(0x5c), 0xc) = SI(esi, 0x50c);
    home = ((void*(__thiscall*)(void*))(0xc31730))(empire);
    if (home) SI((void*)FR(0x5c), 0x14) = (int)((void*(__thiscall*)(void*))(0xce6950))(home);
    SI((void*)FR(0x5c), 0x18) = 5;
    SI((void*)FR(0x5c), 0x1c) = SI(empire, 0x10);
    SI((void*)FR(0x5c), 0x24) = SI(empire, 0x84);
    SI((void*)FR(0x5c), 0x28) = 0;
    FR(0x18) = (int)&FR(0x50);
    goto L_159;

L_07f:
    if (FP(0x10) == 0) goto L_236;
    if (((void*(__cdecl*)())(0x67de90))() == 0) goto L_236;
    ownA = FP(0x24);
    if (ownA != 0 && ((void*(__thiscall*)(void*))(0xc2e780))(ownA) != 0) {
        r = ((void*(__thiscall*)(void*))(0xc2e780))(ownA);
        a = SI(r, 0x504);
        b = SI(r, 0x508);
        c = SI(r, 0x50c);
        obj = ((void*(__stdcall*)(int, int, int, int))(0x67de90))(8, a, b, c);
        goto L_ba54;
    }
    ownB = (void*)FR(0x1c);
    if (ownB == 0) goto L_236;
    if (((void*(__thiscall*)(void*))(0xc2f680))(ownB) == 0) goto L_236;
    FR(0x2c) = 0;
    FR(0x30) = 0;
    FR(0x34) = 0;
    r2 = ((void*(__thiscall*)(void*, int*))(0xc2f680))(ownB, &FR(0x2c));
    al = ((unsigned char(__thiscall*)(void*))(0xc8eb50))(r2);
    if (al == 0) goto L_236;
    a = FR(0x2c);
    b = FR(0x30);
    c = FR(0x34);
    kind = (UI(self, 0x10) != 0x1654c02) ? 10 : 9;
    obj = ((void*(__stdcall*)(int, int, int, int))(0x67de90))(kind, a, b, c);

L_ba54:
    FR(0x18) = (int)((void*(__thiscall*)(void*))(0xba54f0))(obj);
    if (FR(0x18) == 0) goto L_236;

L_159:
    // ---- stash the 0x18 object's sub-fields, then the this+0x64 / +0x68 objects ----
    esi = self + 0x64;
    FR(0x48) = FR(0x18);
    ecx5c = SPTR((void*)FR(0x18), 0xc);
    FR(0x3c) = SI(ecx5c, 8);
    FR(0x44) = SI(ecx5c, 0xc);
    FR(0x40) = SI(ecx5c, 4);
    if (SPTR(esi, 0) == 0) {
        newp = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0x9c, (const char*)0x1480298, 0, 0, 0, 0);
        if (newp) newp = ((void*(__thiscall*)(void*))(0xdd0da0))(newp);
        ((void(__thiscall*)(void*, void*))(0x6428c0))(esi, newp);
    }
    obj64 = SPTR(esi, 0);
    VC1(void, obj64, 0x4, void*, &FR(0x3c));
    ebp = self + 0x68;
    if (SPTR(ebp, 0) == 0) {
        newp = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0x108, (const char*)0x1480280, 0, 0, 0, 0);
        if (newp) newp = ((void*(__thiscall*)(void*))(0x657f70))(newp);
        ((void*(__thiscall*)(void*, void*))(0xb5f950))(ebp, newp);
    }
    o68 = SPTR(ebp, 0);
    ((void(__thiscall*)(void*, void*, void*, int, int))((*(void***)(o68))[0x1c / 4]))(o68, ebx_, SPTR(esi, 0), 0, 0);
    VC2(void, o68, 0x30, int, 0, int, 0);
    VC1(void, o68, 0x28, int, 1);
    VC2(void, ebx_, 0x7c, int, 1, int, 1);
    esi = 0;

L_236:
    // ---- window 0x94095992 ----
    wnd2 = FIND_WIN(SPTR(self, 0x18), 0x94095992);
    if (wnd2) VC2(void, wnd2, 0x7c, int, 1, int, 0);

    // ---- window 0xaaa0012: relationship strip ----
    wnd3 = FIND_WIN(SPTR(self, 0x18), 0xaaa0012);
    if (wnd3 == 0) goto L_370;
    VC2(void, wnd3, 0x7c, int, 1, int, 0);
    if (FR(0x18) != 0) goto L_370;
    FR(0x18) = 0;
    if (FP(0x20) != 0) {
        ((void(__thiscall*)(void*, int*))(0xc45ca0))(FP(0x20), &FR(0x2c));
        if (FR(0x18) != 0) {
            ecx5c = (void*)FR(0x18);
            FR(0x18) = 0;
            VC0(void, ecx5c, 0x4);
        }
        ((void(__cdecl*)(void*, void*, int, int, int))(0x806230))(&FR(0x2c), &FR(0x18), 0, -1, -1);
    } else {
        sel = FP(0x10);
        if (sel == 0) goto L_370;
        esiA = ((void*(__thiscall*)(void*))(0xa16f40))(&FR(0x18));
        VC1(void, sel, 0xb0, void*, esiA);
    }
    if (FR(0x18) == 0) goto L_370;
    if (wnd2) VC2(void, wnd2, 0x7c, int, 1, int, 1);
    VC2(void, wnd3, 0x7c, int, 1, int, 1);
    r = VC0(void*, wnd3, 0xa8);
    if (r) {
        r2 = VC1(void*, r, 0xc, unsigned, 0xef3c47cf);
        if (r2) VC1(void, r2, 0x14, int, FR(0x18));
    }
    VC0(void, wnd3, 0x90);
    if (FR(0x18)) VC0(void, (void*)FR(0x18), 0x4);

L_370:
    // ---- window 0x94a4a6ea: sub-widget ----
    wnd4 = FIND_WIN(SPTR(self, 0x18), 0x94a4a6ea);
    if (wnd4 == 0) goto L_424;
    VC2(void, wnd4, 0x7c, int, 1, int, 0);
    ebx_ = (void*)FR(0x24);
    ebp = (void*)FR(0x1c);
    if (ebx_ == 0 && ebp == 0) goto L_424;
    edi = self + 0x60;
    if (SPTR(edi, 0) == 0) {
        newS = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0xc, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (newS) newS = ((void*(__thiscall*)(void*))(0xe2ec40))(newS);
        ((void(__thiscall*)(void*, void*))(0x572620))(edi, newS);
        ((void(__thiscall*)(void*, void*))(0xe2ec60))(SPTR(edi, 0), wnd4);
    }
    if (ebx_ != 0) {
        r = ((void*(__thiscall*)(void*))(0xc2e820))(ebx_);
        ((void(__thiscall*)(void*, void*))(0xe2ed70))(SPTR(edi, 0), r);
    } else if (ebp != 0) {
        fv = ((float(__thiscall*)(void*))(0xc2f650))(ebp);
        ((void(__thiscall*)(void*, float))(0xe2ef80))(SPTR(edi, 0), fv);
    }
    VC2(void, wnd4, 0x7c, int, 1, int, 1);

L_424:
    if (FP(0x10) == 0) goto L_54f;
    sel = FP(0x10);
    x = ((void*(__thiscall*)(void*))(0xc2ec80))(sel);
    esi = self;
    if (x == 0) goto L_523;
    wnd5 = FIND_WIN(SPTR(self, 0x18), (unsigned)x);
    if (wnd5 == 0) goto L_542;
    FR(0x2c) = 0;
    FR(0x30) = 0;
    FR(0x34) = 0;
    al = ((unsigned char(__thiscall*)(void*, int*))(0xc2e4f0))(sel, &FR(0x2c));
    if (al == 0) goto L_542;
    esiA = self + 0x5c;
    ecx5c = SPTR(esiA, 0);
    if (ecx5c != 0) {
        ((void(__thiscall*)(void*, int, int, int))(0x8121b0))(ecx5c, 0, 1, 0x5b598fa);
        ((void(__thiscall*)(void*, int))(0x811ad0))(SPTR(esiA, 0), 1);
        ecx5c = SPTR(esiA, 0);
        if (ecx5c != 0) {
            SPTR(esiA, 0) = 0;
            VC0(void, ecx5c, 0x8);
        }
    }
    newS = ((void*(__cdecl*)(unsigned, const char*, int, int, int, int))(0xf473a0))(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (newS) newS = ((void*(__thiscall*)(void*))(0x810000))(newS);
    ((void(__thiscall*)(void*, void*))(0x572620))(esiA, newS);
    ((void(__thiscall*)(void*, int*, int, int))(0x8120d0))(SPTR(esiA, 0), &FR(0x2c), 1, 0x5b598fa);
    ((void(__thiscall*)(void*, void*, int, int))(0x8121b0))(SPTR(esiA, 0), wnd5, 1, 0x5b598fa);
    VC0(void, wnd5, 0x94);
    VC2(void, wnd5, 0x7c, int, 1, int, 1);
    ((void(__cdecl*)(void*, void*))(0xe2e790))(SPTR(esiA, 0), item);
    goto L_542;

L_523:
    esiA = self + 0x5c;
    if (SPTR(esiA, 0) == 0) goto L_542;
    ((void(__thiscall*)(void*, int))(0x811ad0))(SPTR(esiA, 0), 1);
    ecx5c = SPTR(esiA, 0);
    if (ecx5c == 0) goto L_542;
    SPTR(esiA, 0) = 0;
    VC0(void, ecx5c, 0x8);

L_542:
    VC0(void, sel, 0x88);

L_54f:
    if (FR(0x5c) != 0 && *(int*)(FR(0x5c) - 4) != 0)
        ((void(__cdecl*)(void*))(0xf47380))((void*)FR(0x5c));
}

// The four vtables the object installs while it is being torn down. Only their addresses are
// stored, so their contents never matter here.
extern const uint32_t g_missionButtonVtbl00[];
extern const uint32_t g_missionButtonVtbl08[];
extern const uint32_t g_missionButtonVtbl0c[];
extern const uint32_t g_missionButtonVtbl40[];

// Releases every sub-object the button created, stops listening to the message server, drops the
// layout callback and finally lets the panel shut the card down.
// @ 0x00e1ca30
void cUIMissionButton::Shutdown()
{
    if (mpMessageServer != 0)
    {
        IMessageServer* pServer = mpMessageServer;
        mpMessageServer = 0;
        EA::Messaging::RemoveHandler(pServer, mpHandlerArg, mpMessageIds, mMessageIdCount, mHandlerFlags);
    }
    if (mpCategoryA != 0)
    {
        mpCategoryA->ShutdownChildren();
        if (mpCategoryA != 0)
        {
            cSPUIFeedCategory* pOld = mpCategoryA;
            mpCategoryA = 0;
            pOld->Release();
        }
    }
    if (mpCategoryB != 0)
    {
        mpCategoryB->ShutdownChildren();
        if (mpCategoryB != 0)
        {
            cSPUIFeedCategory* pOld = mpCategoryB;
            mpCategoryB = 0;
            pOld->Release();
        }
    }
    if (mpObj68 != 0)
    {
        mpObj68->Stop();
        if (mpObj68 != 0)
        {
            IObj68* pOld = mpObj68;
            mpObj68 = 0;
            pOld->Release();
        }
    }
    if (mpObj64 != 0)
    {
        mpObj64->Detach();
        if (mpObj64 != 0)
        {
            IObj64* pOld = mpObj64;
            mpObj64 = 0;
            pOld->mSub10.Release();
        }
    }
    if (mpObj60 != 0)
    {
        mpObj60->Stop();
        if (mpObj60 != 0)
        {
            IObj60* pOld = mpObj60;
            mpObj60 = 0;
            pOld->ReleaseB();
        }
    }
    mStars.erase(mStars.mpBegin, mStars.mpEnd);
    if (mpFeedList != 0)
    {
        mpFeedList->Shutdown();
        if (mpFeedList != 0)
        {
            cSPUIFeedList* pOld = mpFeedList;
            mpFeedList = 0;
            pOld->Release();
        }
    }
    if (mpScrollFrame != 0)
    {
        mpScrollFrame->Shutdown();
        if (mpScrollFrame != 0)
        {
            cScrollFrameVertical* pOld = mpScrollFrame;
            mpScrollFrame = 0;
            pOld->Release();
        }
    }
    if (mpLayout != 0)
    {
        IWinWindow* pHandlerWindow = mpLayout->FindWindowByID(0x5ee1ee0, 1);
        if (pHandlerWindow != 0)
            pHandlerWindow->SetHandler(&mpVtbl08);
    }
    reinterpret_cast<cUIMissionCardPanel*>(this)->ShutdownCard();
}

// Three-argument forwarder to the shared layout helper.
// @ 0x00e1cb80
void FUN_00e1cb80(void* p1, void* p2, void* p3)
{
    FUN_00e1c8b0(p1, p2, p3);
}

// Destructor body: restore the four vtables, run the shutdown pass, then release every remaining
// sub-object and destroy the star record vector.
// @ 0x00e1cba0
void cUIMissionButton::Destroy()
{
    mpVtbl00 = (void*)&g_missionButtonVtbl00;
    mpVtbl08 = (void*)&g_missionButtonVtbl08;
    mpVtbl0c = (void*)&g_missionButtonVtbl0c;
    mpVtbl40 = (void*)&g_missionButtonVtbl40;

    Shutdown();

    // The original repeats the message-handler removal here (it is already done by Shutdown, so
    // this copy never runs; it is kept because the retail body contains it).
    if (mpMessageServer != 0)
    {
        IMessageServer* pServer = mpMessageServer;
        mpMessageServer = 0;
        EA::Messaging::RemoveHandler(pServer, mpHandlerArg, mpMessageIds, mMessageIdCount, mHandlerFlags);
    }

    if (mpCategoryB != 0)
        mpCategoryB->Release();
    if (mpCategoryA != 0)
        mpCategoryA->Release();
    if (mpFeedList != 0)
        mpFeedList->Release();
    if (mpObj68 != 0)
        mpObj68->Release();
    if (mpObj64 != 0)
        mpObj64->mSub10.Release();
    if (mpObj60 != 0)
        mpObj60->ReleaseB();
    if (mpObj5c != 0)
        mpObj5c->ReleaseB();
    if (mpScrollFrame != 0)
        mpScrollFrame->Release();

    mStars.~cStarRecordList();

    reinterpret_cast<cUIMissionCardPanel*>(this)->DestroyMembers();
}

// Rebuilds the button's contents for the current mission: feed list, the two feed categories,
// the scroll frame with its content window, the notify window, and re-registers the messages.
// @ 0x00e1cc80
void cUIMissionButton::CreateMissionButton(void* p1, void* p2, void* p3, void* p4)
{
    ((IWinWindow*)this)->Activate();
    reinterpret_cast<cUIMissionCardPanel*>(this)->OnNotify(p1, p2, p3, p4);
    if (mpLayout == 0)
        return;

    void* pRawFeed = operator_new(0x6c, (const char*)0x13f6b3c, 0, 0, 0, 0);
    cSPUIFeedList* pNewFeed = pRawFeed != 0 ? (cSPUIFeedList*)((cSPUIFeedList*)pRawFeed)->Ctor() : 0;
    {
        cSPUIFeedList* pOldFeed = mpFeedList;
        if (pNewFeed != pOldFeed)
        {
            if (pNewFeed != 0)
                pNewFeed->AddRef();
            mpFeedList = pNewFeed;
            if (pOldFeed != 0)
                pOldFeed->Release();
        }
    }

    cSPUIFeedList* pFeed = mpFeedList;
    pFeed->AddWindow(mpLayout->FindWindowByID(0x519ab80, 1), 0x215ee951, 0, 0);

    {
        void* pNewCatA = mpFeedList->FindEntry(0x9e5ecccf);
        cSPUIFeedCategory* pOldCatA = mpCategoryA;
        if (pNewCatA != pOldCatA)
        {
            if (pNewCatA != 0)
                ((IRefObjB*)pNewCatA)->AddRef();
            mpCategoryA = (cSPUIFeedCategory*)pNewCatA;
            if (pOldCatA != 0)
                pOldCatA->Release();
        }
    }
    {
        void* pNewCatB = mpFeedList->FindEntry(0x897576da);
        cSPUIFeedCategory* pOldCatB = mpCategoryB;
        if (pNewCatB != pOldCatB)
        {
            if (pNewCatB != 0)
                ((IRefObjB*)pNewCatB)->AddRef();
            mpCategoryB = (cSPUIFeedCategory*)pNewCatB;
            if (pOldCatB != 0)
                pOldCatB->Release();
        }
    }

    IWinWindow* pScroll = mpLayout->FindWindowByID(0x519cac8, 1);
    if (pScroll != 0)
    {
        pScroll->Attach();

        void* pRawSfv = operator_new(0x48, "UI/cSPUIScrollFrameVertical", 0, 0, 0, 0);
        cScrollFrameVertical* pNewSfv =
            pRawSfv != 0 ? (cScrollFrameVertical*)((cScrollFrameVertical*)pRawSfv)->Ctor() : 0;
        {
            cScrollFrameVertical* pOldSfv = mpScrollFrame;
            if (pNewSfv != pOldSfv)
            {
                if (pNewSfv != 0)
                    pNewSfv->AddRef();
                mpScrollFrame = pNewSfv;
                if (pOldSfv != 0)
                    pOldSfv->Release();
            }
        }

        if (mpScrollFrame->Create(0xaef7d6ba, 1, 0))
        {
            IWinWindow* pContent = (IWinWindow*)pScroll->GetContent();
            IWinWindow* pObj10 = mpScrollFrame->mpObj10;
            IWinWindow* pObj18 = mpScrollFrame->mpObj18;
            pContent->SetParent(pObj10);

            float4* pRect = pScroll->GetRect();
            float4 rect;
            rect.x = pRect->x;
            rect.y = pRect->y;
            rect.z = pRect->z;
            rect.w = pRect->w;
            rect.z += mpScrollFrame->GetScrollOffset();
            pObj10->SetRect(&rect);

            pContent->SetOwner(pScroll);
            pObj18->SetParent(pScroll);
            pScroll->SetPosition(0.0f, 0.0f);
        }
    }

    IWinWindow* pWindow = mpLayout->FindWindowByID(0x67a2ae0, 1);
    if (pWindow != 0)
    {
        pWindow->Attach();
        pWindow->SetSize(4, 1);
        mWindowId = 0x67a2ae0;
    }

    if (mpCategoryA != 0)
        mpCategoryA->ShutdownChildren();
    if (mpCategoryB != 0)
        mpCategoryB->ShutdownChildren();
    mStars.erase(mStars.mpBegin, mStars.mpEnd);
    SetTracked();

    void* pHandlerArg = &mpVtbl0c;
    IMessageServer* pServer = MessageServer();
    mpMessageServer = pServer;
    mpHandlerArg = pHandlerArg;
    mpMessageIds = g_missionMessageIds;
    mMessageIdCount = 5;
    mHandlerFlags = 0;
    if (pServer != 0 && pHandlerArg != 0)
    {
        uint32_t offset = 0;
        do
        {
            pServer->Subscribe(pHandlerArg, *(const uint32_t*)((const char*)g_missionMessageIds + offset));
            offset += 4;
        } while (offset < 0x14);
    }

    if (pWindow != 0)
        pWindow->Release();
    if (pScroll != 0)
        pScroll->Release();
}

// Empties the feed list and refreshes the button, then asks the hint system for a UI hint update.
// @ 0x00e1cfb0
void cUIMissionButton::ShutdownList()
{
    if (mpFeedList != 0)
        mpFeedList->SetEnabled(false);
    if (mpCategoryA != 0)
        mpCategoryA->ShutdownChildren();
    if (mpCategoryB != 0)
        mpCategoryB->ShutdownChildren();
    mStars.erase(mStars.mpBegin, mStars.mpEnd);
    SetTracked();
    cUIHints* pHints = FUN_0067cac0();
    if (pHints != 0)
        FUN_0067cac0()->SetFlag(1, 1);
    reinterpret_cast<cUIMissionCardPanel*>(this)->ShutdownA();
}

}  // namespace SP
