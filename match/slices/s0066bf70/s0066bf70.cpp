// Slice s0066bf70: SP::cSPUIFeedListItem-adjacent feed-card/layout helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"
#include <intrin.h>
#include <stdio.h>

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void  __cdecl EASTL_allocator_deallocate(void* p);   // 0x00f47380
void* __cdecl SP_AppSystem();                        // 0x0067dd00
void  __cdecl FUN_00571db0(void* h, void* a, void* b, void* c, void* d);

extern int gVt140075c;   // 0x0140075c
extern int gVt13ef094;   // 0x013ef094
extern int gVt14007a4;   // 0x014007a4
extern int gVt1400794;   // 0x01400794
extern int gVt1400788;   // 0x01400788
extern int gVt1400770;   // 0x01400770
extern int gVt1400760;   // 0x01400760
extern int gVt13ec458;   // 0x013ec458
extern int gVt13eb394;   // 0x013eb394
extern int gVt13eb938;   // 0x013eb938
extern int gVt13eb384;   // 0x013eb384
extern int gVt1400744;   // 0x01400744

struct RefObj {
    virtual void v0();
    virtual int  Release();
    virtual void Release2();
};

class cSPUILayout { public:
    virtual void s0();
    virtual void s1();
    virtual int  Release();
    void Shutdown(bool);
};

struct Sub54 { void FUN_0054eac0(int); };
struct Sub64 { void FUN_006571e0(int, int, int); };
// release helper: the original passes the object in ecx and pushes nothing
// (0x0066c3b8 `mov ecx,[esi+0x54]; call 0xf47040`, no `add esp` afterwards)
struct Sub70 { void FUN_00f47040(); };               // 0x00f47040

struct Cb70 {
    Cb70* FUN_0066cb70(unsigned flags);
};

// -----------------------------------------------------------------------------
// @ 0x0066cb70  scalar deleting destructor
// -----------------------------------------------------------------------------
Cb70* Cb70::FUN_0066cb70(unsigned flags) {
    *(void**)this = &gVt140075c;
    _ReadWriteBarrier();
    void* p;
    p = *(void**)((char*)this + 0x14); if (p) ((RefObj*)p)->Release();
    p = *(void**)((char*)this + 0x10); if (p) ((RefObj*)p)->Release();
    p = *(void**)((char*)this + 0xc);  if (p) ((RefObj*)p)->Release();
    p = *(void**)((char*)this + 8);    if (p) ((RefObj*)p)->Release();
    *(void**)this = &gVt13ef094;
    if (flags & 1) EASTL_allocator_deallocate(this);
    return this;
}

// -----------------------------------------------------------------------------
// @ 0x0066c370  shutdown / release all owned sub-objects
// -----------------------------------------------------------------------------
void __fastcall FUN_0066c370(void* self) {
    if (*(uint8_t*)((char*)self + 0xac)) {
        *(uint8_t*)((char*)self + 0xac) = 0;
        void* app = SP_AppSystem();
        ((FnVoidI)VT(app)[16])(app, 0);
    }
    *(uint8_t*)((char*)self + 0x9e) = 0;
    void* p;
    p = *(void**)((char*)self + 0xc);
    if (p) {
        ((cSPUILayout*)p)->Shutdown(true);
        if (p) { *(void**)((char*)self + 0xc) = 0; ((RefObj*)p)->Release2(); }
    }
    p = *(void**)((char*)self + 0x54);
    if (p) {
        ((Sub70*)p)->FUN_00f47040();
        if (p) { *(void**)((char*)self + 0x54) = 0; ((RefObj*)p)->Release(); }
    }
    p = *(void**)((char*)self + 0x58);
    if (p) {
        ((Sub70*)p)->FUN_00f47040();
        if (p) { *(void**)((char*)self + 0x58) = 0; ((RefObj*)p)->Release(); }
    }
    p = *(void**)((char*)self + 0x64);
    if (p) ((Sub64*)p)->FUN_006571e0(0, 0, 0);
    p = *(void**)((char*)self + 0x68);
    if (p) { *(void**)((char*)self + 0x68) = 0; ((RefObj*)((char*)p + 0x10))->Release(); }
    p = *(void**)((char*)self + 0x6c);
    if (p) { *(void**)((char*)self + 0x6c) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0x7c);
    if (p) { *(void**)((char*)self + 0x7c) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0xb0);
    if (p) {
        void* a = *(void**)((char*)self + 0xb4);
        void* b = *(void**)((char*)self + 0xb8);
        void* c = *(void**)((char*)self + 0xbc);
        void* d = *(void**)((char*)self + 0xc0);
        *(void**)((char*)self + 0xb0) = 0;
        FUN_00571db0(p, a, b, c, d);
    }
    p = *(void**)((char*)self + 0x14);
    if (p) ((FnVoidI)VT(p)[0x1e])(p, 0x1002);
}

// -----------------------------------------------------------------------------
extern void* __cdecl GlobalSubsystem_401020();                        // 0x00401020

struct AppSub;                                        // fwd

// A resolved editor view object; slots 0x5a2200/0x5a2240 nudge its pan/zoom members.
struct ViewObject {
    virtual void  s0();
    virtual void  s1();
    virtual void  s2();
    virtual void* v3(const char* name);               // +0x0c
    void FUN_005a2200(float delta);                   // 0x005a2200 (thiscall, ret 4)
    void FUN_005a2240(float delta);                   // 0x005a2240 (thiscall, ret 4)
};

struct ViewSlot {                                     // one editor view reference
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual uint32_t GetFlags();                      // +0x20
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();                               // +0x38 -> returns ViewObject*
};

// The editor view manager returned by GlobalSubsystem_401020(); [+0x50] holds the view sub-system.
struct ViewManager {
    AppSub* GetViewSubSystem();                       // 0x01137690 (thiscall, ret)
};

// The view sub-system: vtable slot +0x38 yields the current view object.
struct AppSub {
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
    virtual void s12();
    virtual void s13();
    virtual ViewObject* GetViewObject();              // +0x38
};

extern uint32_t gFNegMask;                            // 0x013eb8b0: 0x80000000 sign-flip dword

struct ViewCtx {                                      // the object this call operates on
    uint8_t  mPad00[0x08];
    ViewSlot* mSlot08;                                // +0x08
    ViewSlot* mSlot0c;                                // +0x0c
    ViewSlot* mSlot10;                                // +0x10
    ViewSlot* mSlot14;                                // +0x14
    float     mF18;                                   // +0x18
    float     mF1c;                                   // +0x1c
};

// Resolves the view object the pending delta is applied to.
static __forceinline ViewObject* ResolveTarget(ViewSlot* slot) {
    if (!slot) return 0;
    if (!(slot->GetFlags() & 2)) return 0;
    ViewManager* mgr = (ViewManager*)GlobalSubsystem_401020();
    AppSub* sub = mgr->GetViewSubSystem();
    ViewObject* obj = sub->GetViewObject();
    if (!obj) return 0;
    return (ViewObject*)obj->v3((const char*)0x29da727);
}

// @ 0x0066bf70
void __fastcall FUN_0066bf70(ViewCtx* self) {
    ViewObject* t;

    t = ResolveTarget(self->mSlot08);
    if (t) {
        t->FUN_005a2200(-self->mF18);
        return;
    }

    t = ResolveTarget(self->mSlot0c);
    if (t) {
        t->FUN_005a2200(self->mF18);
        return;
    }

    t = ResolveTarget(self->mSlot10);
    if (t) {
        t->FUN_005a2240(-self->mF1c);
        return;
    }

    t = ResolveTarget(self->mSlot14);
    if (t) {
        t->FUN_005a2240(self->mF1c);
    }
}
// -----------------------------------------------------------------------------
// The editor large-asset view.  Field offsets from the disassembly of the ctor
// (0066cbd0), dtor (0066c0c0) and UnloadLayout (0066c720).
// -----------------------------------------------------------------------------
struct ViewManager;                                   // fwd (declared above)
struct ViewObject;                                    // fwd

// A generic COM-style refcounted object reached only through vtable slots.
struct Ref {
    virtual void slot00();                            // 0: deleting/unknown
    virtual int  Release();                           // 1 (0x04)
    virtual void slot08();                            // 2 (0x08)
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78(int a);
    virtual void slot7c();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9c();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108(int a);
};

extern void* __cdecl SP_ModelManager();               // 0x0067dd80
extern void* __cdecl SP_MessageServer();              // 0x0067dcc0
extern void* __cdecl SP_PropertyManager();            // 0x0067de30
extern int   __cdecl RemapTypeId(int);                // 0x00432f10
extern bool  __cdecl FUN_004eb930(const void*, const void*); // 0x004eb930
extern void  __cdecl FUN_005f0a60(void*);             // 0x005f0a60
extern void  __cdecl FUN_00572020(int key, int val);  // 0x00572020
extern void  __cdecl FUN_00809db0(int a, const void* b);    // 0x00809db0 UI::CalloutMessageBox
extern void  __cdecl FUN_005f2d00_(unsigned img, bool u);   // 0x005f2d00

struct Key { uint32_t a, b, c; };                     // EA::ResourceMan::Key

extern Key  gData014006a8[2];                         // 0x014006a8 (2 entries)
extern Key  gData014006b0[9];                         // 0x014006b0
extern Key  gData014006d4[9];                         // 0x014006d4
extern Key  gData014006f8[10];                        // 0x014006f8
extern Key  gData01400720[9];                         // 0x01400720
extern uint32_t gDefaultKey1527da4;                   // 0x01527da4 (ResourceManager default key)
extern float gFloat1471064;                           // 0x01471064 (initial mFb0 = 0.5f)
extern float gHKRealZero;                             // 0x01485378

// The cSPUILargeAssetView singleton body.  Only the members referenced below are named.
// The class is deliberately NOT polymorphic (it stores its own vtable pointers as data).
class cSPUILargeAssetView {
public:
    void   FUN_0066c0c0();                            // destructor body
    bool   DoMessage(uint32_t message, int* data);    // 0066c490
    void   UnloadLayout();                            // 0066c720
    void   FUN_0066c9e0();                            // random image pick
    cSPUILargeAssetView* FUN_0066cbd0(bool flag);     // constructor body (returns this)
    // member layout (offsets from the ctor/dtor)
    void*   m00_vptr;            // 0x00..0x14 vtable pointers (5 bases)
    void*   m04_vptr;
    void*   m08_vptr;
    void*   m0c_vptr;
    void*   m10_vptr;
    void*   m14;                                      // 0x14
    Ref*    m18;                                      // 0x18
    Ref*    m1c;                                      // 0x1c
    Ref*    m20;                                      // 0x20
    Ref*    m24;                                      // 0x24
    Ref*    m28;                                      // 0x28
    Ref*    m2c;                                      // 0x2c
    Ref*    m30;                                      // 0x30
    Ref*    m34;                                      // 0x34
    Ref*    m38;                                      // 0x38
    Ref*    m3c;                                      // 0x3c
    Ref*    m40;                                      // 0x40
    Ref*    m44;                                      // 0x44
    Ref*    m48;                                      // 0x48
    Ref*    m4c;                                      // 0x4c
    Ref*    m50;                                      // 0x50
    Ref*    m54;                                      // 0x54
    Ref*    m58;                                      // 0x58
    Ref*    m5c;                                      // 0x5c
    Ref*    m60;                                      // 0x60
    Ref*    m64;                                      // 0x64
    Ref*    m68;                                      // 0x68
    Ref*    m6c;                                      // 0x6c
    Ref*    m70;                                      // 0x70
    Ref*    m74;                                      // 0x74
    Ref*    m78;                                      // 0x78
    Ref*    m7c;                                      // 0x7c (cSPSwatch)
    Ref*    m80;                                      // 0x80
    Ref*    m84;                                      // 0x84
    Ref*    m88;                                      // 0x88
    Ref*    m8c;                                      // 0x8c
    Ref*    m90;                                      // 0x90
    bool    m94;                                      // 0x94
    uint8_t mPad95[3];                                // 0x95
    float   m98, m9c, ma0, ma4;                       // 0x98..0xa8
    bool    ma8;                                      // 0xa8
    bool    ma9;                                      // 0xa9
    uint8_t mPadAA;                                   // 0xaa
    bool    mab;                                      // 0xab
    bool    mac;                                      // 0xac
    uint8_t mPadAD[3];                                // 0xad
    float   mb0;                                      // 0xb0
    uint32_t mb4;                                     // 0xb4
    bool    mb8;                                      // 0xb8
    uint8_t mPadB9[3];                                // 0xb9
    void*   mbc;                                      // 0xbc (handler)
    uint8_t mPadC0[0x10];                             // 0xc0..0xcc handler args
};

// -----------------------------------------------------------------------------
// @ 0x0066c0c0  destructor body
// -----------------------------------------------------------------------------
void cSPUILargeAssetView::FUN_0066c0c0() {    m00_vptr = &gVt14007a4;                           // 0x14007a4
    m04_vptr = &gVt1400794;                           // 0x1400794
    m08_vptr = &gVt1400788;                           // 0x1400788
    m0c_vptr = &gVt1400770;                           // 0x1400770
    m10_vptr = &gVt1400760;                           // 0x1400760

    if (mb8) {
        mb8 = false;
        void* app = SP_AppSystem();
        ((FnVoidI)VT(app)[0x10])(app, 0);             // AppSystem vtbl +0x40
    }
    if (mbc) {
        void* h = mbc;
        void* a = *(void**)((char*)this + 0xc0);
        void* b = *(void**)((char*)this + 0xc4);
        void* c = *(void**)((char*)this + 0xc8);
        void* d = *(void**)((char*)this + 0xcc);
        mbc = 0;
        FUN_00571db0(h, a, b, c, d);
    }

    // Descending release chain from +0x90 down to +0x18.
    if (m90) m90->slot08();                           // slot 8
    if (m8c) m8c->Release();                          // slot 4
    if (m88) m88->Release();
    if (m84) m84->Release();
    if (m80) {                                        // inline refcount object at +0x80
        int n = *(int*)((char*)m80 + 4) - 1;
        *(int*)((char*)m80 + 4) = n;
        if (n == 0) {
            *(int*)((char*)m80 + 4) = 1;
            (*(void(__thiscall**)(void*, int))VT(m80)[0])(m80, 1);
        }
    }
    if (m7c) m7c->Release();
    if (m78) m78->Release();
    if (m74) ((Ref*)((char*)m74 + 0x10))->Release();  // object at +0x10 of the slot
    if (m70) m70->Release();
    if (m6c) m6c->Release();
    if (m68) m68->Release();
    if (m64) m64->Release();
    if (m60) m60->Release();
    if (m5c) m5c->Release();
    if (m58) m58->Release();
    if (m54) m54->Release();
    if (m50) m50->Release();
    if (m4c) m4c->Release();
    if (m48) m48->Release();
    if (m44) m44->Release();
    if (m40) m40->Release();
    if (m3c) m3c->Release();
    if (m38) m38->Release();
    if (m34) m34->Release();
    if (m30) m30->Release();
    if (m2c) m2c->Release();
    if (m28) m28->Release();
    if (m24) m24->Release();
    if (m20) m20->Release();
    if (m1c) m1c->Release();
    if (m18) m18->slot08();                           // slot 8

    m10_vptr = &gVt13ec458;                           // 0x13ec458
    m04_vptr = &gVt13eb394;                           // 0x13eb394
    m00_vptr = &gVt13eb938;                           // 0x13eb938
}

// -----------------------------------------------------------------------------
// Deeper vtable stubs used by the message handler and layout code.
// -----------------------------------------------------------------------------
struct RefMid {                                       // slots up to 0x54
    virtual void q0();  virtual void q1();  virtual void q2();  virtual void q3();
    virtual void q4();  virtual void q5();  virtual void q6();  virtual void q7();
    virtual void q8();  virtual void q9();  virtual void q10(); virtual void q11();
    virtual void q12(); virtual void q13(); virtual void q14(); virtual void q15();
    virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19();
    virtual void q20(); virtual uint64_t q21();                    // +0x54
    virtual void q22();
    virtual void q23();  virtual void q24(); virtual void q25(); virtual void q26();
    virtual void q27();  virtual void q28(); virtual void q29(); virtual void q30();
    virtual void q31();                                           // +0x7c
};

struct RefKey {                                       // slot 0x40 returns pointer to 3 dwords
    virtual void r0();  virtual void r1();  virtual void r2();  virtual void r3();
    virtual void r4();  virtual void r5();  virtual void r6();  virtual void r7();
    virtual void r8();  virtual void r9();  virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
    virtual void* Get3();                                         // +0x40
};

struct RefName {
    virtual void  n0();
    virtual void  n1();
    virtual void  n2();
    virtual int   Find(int tag);                                  // +0x0c
    virtual uint32_t GetType();                                   // +0x10
};

struct RefSetImage {                                  // slot 0x78 / 0x7c take (int,int)
    virtual void u0();  virtual void u1();  virtual void u2();  virtual void u3();
    virtual void u4();  virtual void u5();  virtual void u6();  virtual void u7();
    virtual void u8();  virtual void u9();  virtual void u10(); virtual void u11();
    virtual void u12(); virtual void u13(); virtual void u14(); virtual void u15();
    virtual void u16(); virtual void u17(); virtual void u18(); virtual void u19();
    virtual void u20(); virtual void u21(); virtual void u22(); virtual void u23();
    virtual void u24(); virtual void u25(); virtual void u26(); virtual void u27();
    virtual void u28(); virtual void u29();                       // +0x74
    virtual void u30();                                           // +0x78
    virtual void u31(int a, int b);                               // +0x7c
};

struct RefBroadcast {                                 // slot 0x14 -> Post(msg,arg,arg)
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
    virtual void b4();                                            // +0x10
    virtual void Post(int msg, const void* a, int b);             // +0x14
};

extern void* __cdecl SP_MessageServer();              // 0x0067dcc0

// @ 0x0066c490  message handler
bool cSPUILargeAssetView::DoMessage(uint32_t message, int* data) {
    if (message < 0x1dd7bdaa) {
        if (message == 0x1dd7bda9) {
            int kind = data[0];
            RefName* n = (RefName*)data[1];
            if (n && n->GetType() == 0x3053c62 && data[3] == 1) {
                uint32_t user[2] = { 0xffffffffu, 0xffffffffu };
                if (sscanf((const char*)data[7], "tag:spore.com,2006:user/%I64u", user) == 1
                    && m70 && ((RefMid*)m70)->q21() == *(uint64_t*)user) {
                    if (m50) ((RefSetImage*)m50)->u31(1, 0);
                    if (kind != 1) {
                        if (m4c) ((RefSetImage*)m4c)->u31(1, 1);
                        FUN_00809db0(0, (const void*)0x01527f38);
                        return true;
                    }
                    if (m54) ((RefSetImage*)m54)->u31(1, 1);
                    ((RefBroadcast*)SP_MessageServer())->Post(0x53dd093, 0, 0);
                    return true;
                }
            }
        } else if (message == 0x4aca143) {
            RefName* q = (RefName*)data[2];
            int matched = q ? q->Find(0x4aa3b42) : 0;
            if (*(int*)((char*)this + 0x64) == matched && m78 && data[0]) {
                int idx = *(int*)((char*)data[0] + 0x28);
                if (idx != -1) {
                    (*(void(__thiscall**)(void*, uint32_t, int))VT(m7c)[0x7c / 4])(m7c, (uint32_t)idx, 0);
                    return true;
                }
            }
        } else if (message == 0x695e243) {
            if (m70) {
                uint32_t* src = (uint32_t*)(((RefKey*)m70)->Get3());
                // compare two 3-dword key descriptors (block at data[2] vs src)
                uint32_t a[3] = { src[0], src[1], src[2] };
                uint32_t b[3] = { (uint32_t)data[2], (uint32_t)data[4], (uint32_t)data[6] };
                if (FUN_004eb930(a, b)) {
                    if (m1c) m1c->slot78(0x1002);
                    if (m44) ((RefSetImage*)m44)->u31(1, 0);
                    if (m28) { ((RefSetImage*)m28)->u31(1, 1); return true; }
                }
            }
        }
    } else if (message == 0x7a43c598) {
        int block[3] = { data[0], data[1], data[2] };
        RefBroadcast* ms = (RefBroadcast*)SP_MessageServer();
        ms->Post(0x14ac4938, 0, 0);
        ms = (RefBroadcast*)SP_MessageServer();
        ms->Post(0xcadf3aca, block, 0);
    }
    return true;
}

// -----------------------------------------------------------------------------
// @ 0x0066c720  UnloadLayout: release every layout resource
// -----------------------------------------------------------------------------
extern void* __cdecl SP_ModelManager();               // 0x0067dd80
extern void  __cdecl FUN_0066bf20(void*);             // 0x0066bf20
extern void  __cdecl FUN_00834e30(void*);             // 0x00834e30 UI::TextZoomName::Shutdown
extern void  __cdecl cSPUIAssetVerbs_Shutdown(void*); // 0x006566f0
extern void  __cdecl FUN_00401020_void(void*);        // 0x00401020 wrapper (takes value)

struct RefImage : Ref {
    virtual void slot24();
};

void cSPUILargeAssetView::UnloadLayout() {
    if (!ma8) return;

    if (m80) {
        FUN_0066bf20(m80);
        Ref* p = m80;
        if (p) {
            m80 = 0;
            int n = *(int*)((char*)p + 4) - 1;
            *(int*)((char*)p + 4) = n;
            if (n == 0) {
                *(int*)((char*)p + 4) = 1;
                (*(void(__thiscall**)(Ref*, int))VT(p)[0])(p, 1);
            }
        }
    }
    if (m84) {
        m84->slot24();
        Ref* p = m84;
        if (p) { m84 = 0; p->Release(); }
    }
    if (m7c) {
        void* mm = SP_ModelManager();
        (*(void(__thiscall**)(void*, int, int))VT(mm)[0x24 / 4])(mm, (int)(uintptr_t)m88, 0);
        void* sw = m7c;
        FUN_00401020_void(sw);
        FUN_005f0a60(sw);
        Ref* p = m7c;
        if (p) { m7c = 0; p->Release(); }
    }
    if (m68) {
        m68->slot18();
        Ref* p = m68;
        if (p) { m68 = 0; p->Release(); }
    }
    if (m70) {
        cSPUIAssetVerbs_Shutdown(m70);
        Ref* p = m70;
        if (p) { m70 = 0; p->Release(); }
    }
    if (m60) {
        ((Sub70*)m60)->FUN_00f47040();
        Ref* p = m60;
        if (p) { m60 = 0; p->Release(); }
    }
    if (m64) {
        ((Sub70*)m64)->FUN_00f47040();
        Ref* p = m64;
        if (p) { m64 = 0; p->Release(); }
    }
    if (m90) {
        FUN_00834e30(m90);
        Ref* p = m90;
        if (p) { m90 = 0; p->slot08(); }
    }
    if (m20) m20->slot108((int)(uintptr_t)this);
    if (m3c) {
        void* sub = (void*)(*(void*(__thiscall**)(void*))VT(m3c)[0x10 / 4])(m3c);
        if (sub)
            (*(void(__thiscall**)(void*, int))VT(sub)[0x108 / 4])(sub, (int)(uintptr_t)this);
    }
    if (m40) {
        void* sub = (void*)(*(void*(__thiscall**)(void*))VT(m40)[0x10 / 4])(m40);
        if (sub)
            (*(void(__thiscall**)(void*, int))VT(sub)[0x108 / 4])(sub, (int)(uintptr_t)this);
    }
    if (m20) { Ref* p = m20; m20 = 0; p->Release(); }
    if (m2c) { Ref* p = m2c; m2c = 0; p->Release(); }
    if (m30) { Ref* p = m30; m30 = 0; p->Release(); }
    if (m48) { Ref* p = m48; m48 = 0; p->Release(); }
    if (m34) { Ref* p = m34; m34 = 0; p->Release(); }
    if (m38) { Ref* p = m38; m38 = 0; p->Release(); }
    if (m44) { Ref* p = m44; m44 = 0; p->Release(); }
    if (m3c) { Ref* p = m3c; m3c = 0; p->Release(); }
    if (m40) { Ref* p = m40; m40 = 0; p->Release(); }
    if (m5c) { Ref* p = m5c; m5c = 0; p->Release(); }
    ma8 = false;
    if (m50) { Ref* p = m50; m50 = 0; p->Release(); }
    if (m54) { Ref* p = m54; m54 = 0; p->Release(); }
    if (m8c) {
        m8c->slot24();
        Ref* p = m8c;
        if (p) { m8c = 0; p->Release(); }
    }
    FUN_00572020(0x5d2b737, 0);
}

// -----------------------------------------------------------------------------
// @ 0x0066c9e0  pick a random variation image for the feed card
// -----------------------------------------------------------------------------
extern uint32_t __cdecl RandomUint32Uniform(uint32_t max);   // 0x00a68fb0
extern uint32_t SetImage(void* swatch, uint32_t img, bool u);// 0x005f2d00

extern uint32_t gKeys06a8[2];                          // 0x014006a8
extern uint32_t gKeys06b0[9];                          // 0x014006b0
extern uint32_t gKeys06d4[9];                          // 0x014006d4
extern uint32_t gKeys06f8[10];                         // 0x014006f8
extern uint32_t gKeys0720[9];                          // 0x01400720

// Object whose vtable slot 0x24 yields the selected variation id.
struct RefVar {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();
    virtual uint32_t GetVariation();                              // +0x24
};

void cSPUILargeAssetView::FUN_0066c9e0() {
    if (!m74 || !m7c) return;

    uint32_t kind = ((RefVar*)m74)->GetVariation();
    RefSetImage* sw = (RefSetImage*)m7c;
    uint32_t key = 0;
    bool done = false;

    switch (kind) {
    case 0x9ea3031a:
        key = gKeys06b0[RandomUint32Uniform(0x7fffffff) % 9];
        done = true; break;
    case 0x4178b8e8:
    case 0x65672ade:
        key = gKeys0720[RandomUint32Uniform(0x7fffffff) % 9];
        done = true; break;
    case 0x37148141:
        key = 0x5da8e82;
        done = true; break;
    case 0x372e2c04:
        key = gKeys06d4[RandomUint32Uniform(0x7fffffff) % 9];
        done = true; break;
    case 0xccc35c46:
        key = gKeys06f8[RandomUint32Uniform(0x7fffffff) % 10];
        done = true; break;
    case 0xb8669ec9:
    case 0xbcd73e89:
        key = 0x5da8e82;
        done = true; break;
    case 0xdfad9f51:
        key = gKeys06a8[RandomUint32Uniform(0x7fffffff) & 1];
        done = true; break;
    default:
        break;
    }

    if (!done) return;
    mb4 = SetImage(sw, key, 1);
}

// -----------------------------------------------------------------------------
// @ 0x0066cbd0  constructor body
// -----------------------------------------------------------------------------
cSPUILargeAssetView* cSPUILargeAssetView::FUN_0066cbd0(bool flag) {
    m04_vptr = &gVt13eb384;                           // 0x13eb384    m0c_vptr = &gVt1400744;                           // 0x1400744
    m10_vptr = &gVt13ec458;                           // 0x13ec458
    m14 = 0;

    m00_vptr = &gVt14007a4;                           // 0x14007a4
    m04_vptr = &gVt1400794;                           // 0x1400794
    m08_vptr = &gVt1400788;                           // 0x1400788
    m0c_vptr = &gVt1400770;                           // 0x1400770
    m10_vptr = &gVt1400760;                           // 0x1400760

    m18 = 0; m1c = 0; m20 = 0; m24 = 0; m28 = 0; m2c = 0;
    m30 = 0; m34 = 0; m38 = 0; m3c = 0; m40 = 0; m44 = 0; m48 = 0;
    m4c = 0; m50 = 0; m54 = 0; m58 = 0; m5c = 0; m60 = 0; m64 = 0;

    m68 = 0;
    m6c = 0;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m7c = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;
    m8c = 0;
    m90 = 0;
    m94 = flag;
    m98 = 0.0f; m9c = 0.0f; ma0 = 0.0f; ma4 = 0.0f;
    ma8 = false; ma9 = false; mab = false; mac = false;
    mb0 = gFloat1471064;
    mb4 = 0;
    mb8 = false;
    mbc = 0;
    *(uint32_t*)((char*)this + 0xc0) = 0;
    *(uint32_t*)((char*)this + 0xc4) = 0;
    *(uint32_t*)((char*)this + 0xc8) = 0;
    *(uint32_t*)((char*)this + 0xcc) = 0;
    return this;
}
// -----------------------------------------------------------------------------
// @ 0x0066cd20 SP::GetVerbIconKeysForLargeCard(eModelType, Key&, Key&)
// -----------------------------------------------------------------------------
struct PropKey { uint32_t a, b, c; };

struct PropAccess {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8(); virtual void q9(); virtual void q10();
    virtual void GetKeys(int type, void* owner, void** out);          // +0x2c
};

extern void GetPropertyAsKey_(void* props, uint32_t id, void* out);   // 0x006a1250
extern void*   gOwner1527da4;                                     // 0x01527da4

void __cdecl SP_GetVerbIconKeysForLargeCard(int modelType, PropKey* keyA, PropKey* keyB) {
    int remapped = RemapTypeId(modelType);
    if (remapped == -1) return;

    void* slot = 0;
    PropAccess* pm = (PropAccess*)SP_PropertyManager();

    pm->GetKeys(remapped, &gOwner1527da4, &slot);

    if (!slot) return;

    PropKey tmp; tmp.a = 0; tmp.b = 0; tmp.c = 0;
    GetPropertyAsKey_(slot, 0x4aa3989, keyA);
    GetPropertyAsKey_(slot, 0xb457c766, keyB);
    GetPropertyAsKey_(slot, 0xd56e0289, &tmp);

    ((Ref*)slot)->Release();
}
