// Slice s00ee6880 (gold4 #86).
// SP::cSPUIAssetGrid: asset-grid editor UI pane. Constructor/destructor, the layout Init
// (window/layout setup + colour-picker wiring), the message handler, the refresh pass,
// the window visibility toggle, the window-find walker and the small id tables used by
// the paint picker.
// Layout notes: retail offsets come from the disassembly; stub classes carry only what is read.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------
// external data (address in the comment)
extern void*    DAT_016c7aa4;         // 0x16c7aa4 (app / message context)
extern void*    DAT_015fd918;         // 0x15fd918 app property list (also 0x15ac72c key)
extern u32      DAT_0148aac0[15];     // 0x148aac0
extern u32      DAT_0148aafc[15];     // 0x148aafc
extern u32      DAT_0148aa40[5];      // 0x148aa40 message ids
extern const char DAT_013f6b3c[];     // 0x13f6b3c allocator name

// ---------------------------------------------------------------------------
// engine helpers (address in the comment)
// thiscall member helpers (the receiver is in ecx, as in the original code)
typedef void* (__thiscall* FnT_p_v)(void*);                                  // () -> void*
typedef void  (__thiscall* FnT_v_v)(void*);                                  // () -> void
typedef void  (__thiscall* FnT_v_p)(void*, void*);                           // (void*)
typedef void* (__thiscall* FnT_p_p)(void*, void*);                           // (void*) -> void*
typedef void* (__thiscall* FnT_pip)(void*, u32, int);                        // (u32,int) -> void*
typedef void  (__thiscall* FnT_v_pi)(void*, void*, int);                     // (void*,int)
typedef void  (__thiscall* FnT_v_pu)(void*, void*, u32);                     // (void*,u32)
typedef void  (__thiscall* FnT_v_ip)(void*, int, void*);                     // (int,void*)
typedef void* (__thiscall* FnT_p_u)(void*, u32);                             // (u32) -> void*
typedef void  (__thiscall* FnT_v_i)(void*, int);                             // (int)
typedef void* (__thiscall* FnT_p_pf)(void*, void*, float*);                  // (void*,float*) -> void*
typedef bool  (__thiscall* FnT_b_p)(void*, void*);                           // (void*) -> bool
typedef void  (__thiscall* FnT_v_u)(void*, u32);                             // (u32)
typedef void  (__thiscall* FnT_v_pip)(void*, void*, u32, int, int);          // (void*,u32,int,int)
typedef void  (__thiscall* FnT_v_f)(void*, float*);                          // (float*)

extern "C" void*  EAAllocate(u32 size, const char* name, int, int, int, int);            // 0xf473a0
extern "C" void   EAFree(void* p);                                                       // 0xf47380
extern "C" void*  cConnectionDialog_ctor(void* p);                                       // 0x810000
extern "C" bool   cSPUILayout_Init(void* layout, void* key, int a, int b);               // 0x8120d0
extern "C" void   cSPUILayout_Shutdown(void* layout, int a);                             // 0x811ad0
extern "C" bool   cSPUILayout_SetParentWin(void* layout, void* win, int a, int b);       // 0x8121b0
extern "C" void   EA_Messaging_RemoveHandler(void* h, u32 a, u32 b, u32 c, u32 d);       // 0x571db0
extern "C" void*  SP_MessageServer();                                                    // 0x67dcc0
extern "C" void*  FUN_00eeab00(void* p);                                                 // 0xeeab00
extern "C" void*  FUN_005a5a50();                                                        // 0x5a5a50 (cX ctor)
extern "C" bool   FUN_006a25a0(void* props, u32 id);                                     // 0x6a25a0
extern "C" u32    FUN_00458a40(const float* rgb);                                        // 0x458a40 ColorRGBToU32
extern "C" void*  FUN_00f32330(float* out);                                              // 0xf32330
extern "C" void*  FUN_00f32390(float* out);                                              // 0xf32390
extern "C" void*  FUN_00f32360(float* out);                                              // 0xf32360
extern "C" void*  FUN_00f32300(float* out);                                              // 0xf32300
extern "C" void   FUN_00e12f80(void* win, int a);                                        // 0xe12f80
extern "C" void   FUN_00ed1350(void* win, int a);                                        // 0xed1350
extern "C" void   FUN_00eea860(int a);                                                   // 0xeea860
extern "C" bool   FUN_00f31e50(void* ctx);                                               // 0xf31e50
extern "C" u32    FUN_00f31c20(void* ctx, int a);                                        // 0xf31c20
extern "C" void   FUN_00f343a0(void* ctx, int a);                                        // 0xf343a0
extern "C" void*  FUN_00f0d3e0(void* ctx);                                               // 0xf0d3e0
extern "C" void*  FUN_00f31e40(void* ctx, void* a);                                      // 0xf31e40
extern "C" void   FUN_00eeb580(void* p, void* q);                                        // 0xeeb580
extern "C" void*  FUN_00a206f0();                                                        // 0xa206f0 Audio::GetSystemAT
extern "C" void   FUN_00435ed0(void* sys, u32 id);                                       // 0x435ed0 KissSetiEffects
extern "C" void*  FUN_00576ab0(void* out, u32 color);                                    // 0x576ab0 ColorToVector3
extern "C" void   FUN_00eeb920(void* out, void* ctx, void* p);                           // 0xeeb920
extern "C" void   FUN_00f344e0(void* ctx, void* a, void* b);                             // 0xf344e0
extern "C" void   FUN_00f34560(void* ctx);                                               // 0xf34560
extern "C" void   FUN_00f31ea0(void* ctx);                                               // 0xf31ea0 MsgSend
extern "C" void   FUN_00f33bf0(void* ctx);                                               // 0xf33bf0
extern "C" void   FUN_00f32150(void* ctx, float* v);                                     // 0xf32150
extern "C" void   FUN_00f321a0(void* ctx, float* v);                                     // 0xf321a0
extern "C" void   FUN_00f321f0(void* ctx, float* v);                                     // 0xf321f0
extern "C" void   FUN_00f32100(void* ctx, float* v);                                     // 0xf32100
extern "C" void   FUN_005ca880(u32 id, float v);                                         // 0x5ca880 SetGlobalProperty
extern "C" void   FUN_00eea910(void* ctx, void* p, float a, float b, float c);           // 0xeea910

// thiscall-equivalent direct calls: the receiver is in ecx (fastcall's first slot), the
// dummy second parameter lands in edx (unused by the callee), remaining args go on the stack.
extern "C" void   __fastcall FUN_005a6390(void* self, int);                              // 0x5a6390 Clear
extern "C" void   __fastcall FUN_005a6db0(void* self, int, void* p);                     // 0x5a6db0 Update
extern "C" void   __fastcall FUN_005a4200(void* self, int, int a);                       // 0x5a4200
extern "C" void   __fastcall FUN_005a4e20(void* self, int, const void* color);           // 0x5a4e20
extern "C" void   __fastcall FUN_005a5ec0(void* self, int, void* win, u32 a, int b, int c);// 0x5a5ec0
extern "C" void   __fastcall FUN_00b5f950(void* self, int, void* p);                     // 0xb5f950 AutoRefCount assign
extern "C" void   __fastcall FUN_00f47630(void* self, int, void* p);                     // 0xf47630
extern "C" void   __fastcall FUN_00572620(void* self, int, void* p);                     // 0x572620
extern "C" bool   __fastcall FUN_00eea8e0(void* self, int, void* p);                     // 0xeea8e0
extern "C" void*  __fastcall FUN_00eeaa90(void* self, int, void* p, float* out);         // 0xeeaa90
extern "C" void*  __fastcall cSPUILayout_FindWindowByID(void* self, int, u32 id, int a); // 0x8105b0
#define CALL_CSPUILAYOUT_FindWindowByID cSPUILayout_FindWindowByID

// virtual-slot call helpers -------------------------------------------------
static inline void vcall_void(void* o, int slot)
{
    (*(void(__thiscall**)(void*))((char*)*(void**)o + slot))(o);
}
static inline void* vcall_p(void* o, int slot)
{
    return (*(void*(__thiscall**)(void*))((char*)*(void**)o + slot))(o);
}

// ---------------------------------------------------------------------------
// the pane (offsets per the disassembly; only fields that are read are named).
// It has three polymorphic bases (vptrs at +0, +4, +8), which is what makes the
// ctor/dtor store three vtable pointers in each phase.
struct IMsgHandler      { virtual void m00(); virtual ~IMsgHandler(); };       // vptr @ +0
struct GmeEditorResBase { virtual void g00(); virtual ~GmeEditorResBase(); };  // vptr @ +4
struct RefCountBlob     { virtual void r00(); virtual ~RefCountBlob(); };      // vptr @ +8
struct PadBase          { u32 m0c; PadBase() : m0c(0) {} };                    // +0x0c

struct Pane : IMsgHandler, GmeEditorResBase, RefCountBlob, PadBase {
    Pane();
    virtual ~Pane();
    u8        mb10;                 // +0x10
    u8        pad11[3];
    void*     mp14;                 // +0x14  window (AutoRefCount)
    void*     mp18;                 // +0x18  layout
    void*     mp1c;                 // +0x1c  sub control
    void*     mp20;                 // +0x20  colour picker
    void*     mp24;                 // +0x24
    void*     mp28;                 // +0x28  handler id
    u32       m2c, m30, m34, m38;   // +0x2c..+0x38
};

// ===========================================================================
// @ 0x00ee6880
u32 __fastcall FUN_00ee6880(u32 this_, int, u32 id)
{
    u32 r;
    if (id == 0xb68dce27)
        r = this_ - 4;
    else if (id == 0xee3f516e || id == 0x2f009dd0)
        r = (this_ != 4) ? this_ : 0;
    else
        r = 0;
    return r;
}

// ===========================================================================
// @ 0x00ee68b0
u32 __fastcall FUN_00ee68b0(Pane* this_, int, void* param)
{
    void* old = this_->mp14;
    if (param != old) {
        if (param != 0)
            vcall_void(param, 0);
        this_->mp14 = param;
        if (old != 0)
            vcall_void(old, 4);
    }

    if (this_->mp14 != 0) {
        void* layout = EAAllocate(0x18, DAT_013f6b3c, 0, 0, 0, 0);
        layout = layout ? cConnectionDialog_ctor(layout) : 0;

        void* prev = this_->mp18;
        if (layout != prev) {
            if (layout != 0)
                vcall_void(layout, 4);
            this_->mp18 = layout;
            if (prev != 0)
                vcall_void(prev, 8);
        }

        if (!cSPUILayout_Init(this_->mp18, (void*)0x15ac72c, 0, 0x5b598fa)) {
            cSPUILayout_Shutdown(this_->mp18, 1);
            void* p = this_->mp18;
            if (p != 0) {
                this_->mp18 = 0;
                vcall_void(p, 8);
            }
            return 0;
        }

        cSPUILayout_SetParentWin(this_->mp18, this_->mp14, 1, 0x5b598fa);

        if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xf68dd360, 0, 1) != 0) {
            void* ctl = EAAllocate(0x5c, DAT_013f6b3c, 0, 0, 0, 0);
            ctl = ctl ? FUN_00eeab00(ctl) : 0;
            FUN_00f47630((char*)this_ + 0x1c, 0, ctl);
            void* sub = *(void**)this_->mp1c;
            void* win = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xf68dd360, 0, 1);
            (*(void(__thiscall**)(void*, void*))(*((void**)((char*)sub + 0x10))))(this_->mp1c, win);
        }

        if (FUN_006a25a0(DAT_015fd918, 0x7defc36)) {
            if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0x7defcdf, 0, 1) != 0) {
                void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0x7defcdf, 0, 1);
                if (w != 0)
                    (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 1);
            }
        }

        if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1) != 0) {
            void* pick = EAAllocate(0x50, DAT_013f6b3c, 0, 0, 0, 0);
            pick = pick ? FUN_005a5a50() : 0;
            FUN_00572620((char*)this_ + 0x20, 0, pick);
            void* win = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
            FUN_005a5ec0(this_->mp20, 0, win, 0x2b8745d6, 1, 0);
            FUN_005a4200((char*)this_ + 0x20, 0, 1);
            if (CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1) != 0) {
                void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
                if (w != 0)
                    (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 0);
            }
        }
    }

    void* srv = SP_MessageServer();
    this_->mp28 = srv;
    this_->m2c = (u32)this_;
    this_->m30 = (u32)DAT_0148aa40;
    this_->m34 = 5;
    this_->m38 = 0;
    if (srv != 0) {
        for (u32 i = 0; i < 0x14; i += 4) {
            u32 ev = *(u32*)((char*)DAT_0148aa40 + i);
            (*(void(__thiscall**)(void*, Pane*, u32))(*((void**)((char*)srv + 0x24))))(srv, this_, ev);
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00ee6b10
void __fastcall FUN_00ee6b10(Pane* this_, int, void* p)
{
    void* ctl = this_->mp1c;
    if (ctl != 0) {
        void* vt = *(void**)ctl;
        (*(void(__thiscall**)(void*, void*, int))((char*)vt + 0x18))(ctl, p, 1);
    }
    void* pick = this_->mp20;
    if (pick != 0)
        FUN_005a6db0(pick, 0, p);
}

// ===========================================================================
// @ 0x00ee6b40
void __fastcall FUN_00ee6b40(Pane* this_)
{
    vcall_void(this_, 0x1c);

    if (this_->mp1c != 0) {
        void* ctl = this_->mp1c;
        vcall_void(ctl, 0x14);
        if (this_->mp1c != 0) {
            this_->mp1c = 0;
            vcall_void(ctl, 0xc);
        }
    }
    if (this_->mp20 != 0) {
        FUN_005a6390(this_->mp20, 0);
        if (this_->mp20 != 0) {
            void* pick = this_->mp20;
            this_->mp20 = 0;
            vcall_void(pick, 8);
        }
    }
    if (this_->mp28 != 0) {
        void* h = this_->mp28;
        u32 a = this_->m2c, b = this_->m30, c = this_->m34, d = this_->m38;
        this_->mp28 = 0;
        EA_Messaging_RemoveHandler(h, a, b, c, d);
    }
    if (this_->mp14 != 0) {
        this_->mp14 = 0;
        vcall_void(this_->mp14, 4);
    }
}

// ===========================================================================
// @ 0x00ee6bd0
void __fastcall FUN_00ee6bd0(Pane* this_)
{
    if (*(void**)((char*)DAT_016c7aa4 + 0x18) == 0)
        return;

    void* ctx = *(void**)((char*)DAT_016c7aa4 + 0x18);
    static const u32 kIds[4] = { 0x7e078b0, 0x7e078b1, 0x7e078b2, 0x7e078b3 };

    for (int i = 0; i < 4; i++) {
        float rgb[3];
        float tmp[3];
        void* r;
        if (i == 0)      r = FUN_00f32330(tmp);
        else if (i == 1) r = FUN_00f32390(tmp);
        else if (i == 2) r = FUN_00f32360(tmp);
        else             r = FUN_00f32300(tmp);
        rgb[0] = ((float*)r)[0];
        rgb[1] = ((float*)r)[1];
        rgb[2] = ((float*)r)[2];
        u32 c = FUN_00458a40(rgb);
        void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kIds[i], 0, 1);
        if (w != 0)
            (*(void(__thiscall**)(void*, u32))(*((void**)((char*)w + 0x5c))))(w, c);
    }

    if (this_->mp24 != 0) {
        void* p = this_->mp24;
        this_->mp24 = 0;
        vcall_void(p, 4);
    }

    static const u32 kCtl[4] = { 0x7e07cc0, 0x7e07cc1, 0x7e07cc2, 0x7e07cc3 };
    for (int i = 0; i < 4; i++) {
        void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kCtl[i], 0, 1);
        if (w != 0) {
            void* o = (*(void*(__thiscall**)(void*, u32))(*((void**)((char*)w + 0xc))))(w, 0x8ed27e7a);
            if (o != 0)
                (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)o + 0x28))))(o, 4, 0);
        }
    }

    if (this_->mp20 != 0) {
        void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
        if (w != 0)
            (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 0);
    }

    if (this_->mp1c != 0) {
        void* a = FUN_00f0d3e0(ctx);
        void* b = FUN_00f31e40(ctx, a);
        FUN_00eeb580(this_->mp1c, b);
    }
}

// ===========================================================================
// @ 0x00ee6e80
Pane::Pane() : mb10(0), mp14(0), mp18(0), mp1c(0), mp20(0), mp24(0), mp28(0),
               m2c(0), m30(0), m34(0), m38(0)
{
}

// ===========================================================================
// @ 0x00ee6ef0
Pane::~Pane()
{
    if (mp28 != 0) {
        void* h = mp28;
        mp28 = 0;
        EA_Messaging_RemoveHandler(h, m2c, m30, m34, m38);
    }
    if (mp24 != 0)
        vcall_void(mp24, 4);
    if (mp20 != 0)
        vcall_void(mp20, 8);
    if (mp1c != 0)
        vcall_void(mp1c, 0xc);
    if (mp18 != 0)
        vcall_void(mp18, 8);
    if (mp14 != 0)
        vcall_void(mp14, 4);
}

// ===========================================================================
// @ 0x00ee6f90
void __fastcall FUN_00ee6f90(Pane* this_, int, char b)
{
    if (b)
        FUN_00ee6bd0(this_);

    if (this_->mp18 != 0) {
        static const u32 kIds[6] = { 0x9694210d, 0x7defcdf, 0x7e07cc0, 0x7e07cc1, 0x7e07cc2, 0x7e07cc3 };
        for (int i = 0; i < 6; i++) {
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kIds[i], 0, 1);
            if (w != 0) {
                int slot = b ? 0x104 : 0x108;
                (*(void(__thiscall**)(void*, void*))(*((void**)((char*)w + slot))))(w, (char*)this_ + 4);
            }
        }
    }
    if (this_->mp1c != 0)
        (*(void(__thiscall**)(void*, char))(*((void**)((char*)this_->mp1c + 0x1c))))(this_->mp1c, b);
}

// ===========================================================================
// @ 0x00ee70e0
u32 __fastcall FUN_00ee70e0(Pane* this_, int, void* ev, void* arg)
{
    u32 ret = (u32)DAT_016c7aa4;
    void* ctx = *(void**)((char*)DAT_016c7aa4 + 0x18);

    u32* pev = (u32*)ev;
    if (pev[2] == 0x287259f6) {
        u32 msg = pev[3];
        if (msg == 0x9694210d) {
            if (ctx != 0) {
                if (FUN_00f31e50(ctx)) {
                    return FUN_00f31c20(ctx, (int)arg) & 0xffffff00;
                }
                FUN_00f343a0(ctx, 1);
                FUN_00f31c20(ctx, 1);
                FUN_00ee6bd0(this_);
                ret = 0;
            }
        }
        else if (msg + 0xf81f8340 < 4) {
            void* sys = FUN_00a206f0();
            void* at = sys ? (*(void*(__thiscall**)(void*))(*((void**)((char*)sys + 0x20))))(sys) : 0;
            FUN_00435ed0(at, 0xe76c9b4f);
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp14, msg, 0, 1);
            FUN_00b5f950((char*)this_ + 0x20, 0, w);
            if (this_->mp1c != 0 && this_->mp20 != 0) {
                void* dlg = CALL_CSPUILAYOUT_FindWindowByID(this_->mp14, 0xd68f3fd2, 0, 1);
                FUN_00e12f80(dlg, 1);
                void* o = CALL_CSPUILAYOUT_FindWindowByID(this_->mp14, msg - 0x410, 0, 1);
                u32 col = (*(u32(__thiscall**)(void*))(*((void**)((char*)o + 0x30))))(o);
                float v[3];
                FUN_00576ab0(v, col);
                FUN_005a4e20(this_->mp20, 0, v);
            }
            if (this_->mp18 != 0) {
                FUN_00eea860(0);
                ret = 0;
            }
        }
    }
    return ret & 0xffffff00;
}

// ===========================================================================
// @ 0x00ee7240
u32 __fastcall FUN_00ee7240(Pane* this_, int, u32 code, void* param)
{
    void* ctx = *(void**)((char*)DAT_016c7aa4 + 0x18);
    u32* pp = (u32*)param;

    if (code <= 0x7e1ea71) {
        if (code == 0x7e1ea71) {
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
            if (w != 0)
                (*(void(__thiscall**)(void*, int, int))(*((void**)((char*)w + 0x7c))))(w, 1, 0);
            return 0;
        }
        if (code == 0x7e19b84) {
            void* p = (void*)pp[2];
            if (p == 0)
                return 0;
            if (!FUN_00eea8e0(this_->mp1c, 0, p))
                return 0;
            if (this_->mp18 == 0)
                return 0;
            FUN_00b5f950((char*)this_ + 0x24, 0, p);

            static const u32 kCtl[4] = { 0x7e07cc0, 0x7e07cc1, 0x7e07cc2, 0x7e07cc3 };
            for (int i = 0; i < 4; i++) {
                void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, kCtl[i], 0, 1);
                FUN_00ed1350(w, 0);
            }
            if (this_->mp20 != 0) {
                void* dlg = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, 0xd68f3fd2, 0, 1);
                FUN_00e12f80(dlg, 1);
                float col[3];
                FUN_00eeaa90(this_->mp1c, 0, p, col);
                FUN_005a4e20(this_->mp20, 0, col);
            }
            return 0;
        }
        return 0;
    }

    if (code == 0x90e08f60) {
        u32 raw = pp[4];
        if (raw == 0 || ctx == 0)
            return 0;
        if ((void*)(raw - 8) != this_->mp20)
            return 0;
        u32 c = pp[2];
        float rgb[3];
        FUN_00576ab0(rgb, c);
        if (this_->mp24 != 0) {
            void* mo = this_->mp24;
            u32 id = (*(u32(__thiscall**)(void*, int))(*((void**)((char*)mo + 0x1c))))(mo, 1);
            void* w = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, id - 0x410, 0, 1);
            if (w != 0) {
                void* w2 = CALL_CSPUILAYOUT_FindWindowByID(this_->mp18, id - 0x410, 0, 1);
                (*(void(__thiscall**)(void*, u32))(*((void**)((char*)w2 + 0x5c))))(w2, c);
            }
        }
        u32 cls = (*(u32(__thiscall**)(void*, int))(*((void**)((char*)this_->mp24 + 0x1c))))(this_->mp24, 1);
        if (cls <= 0x7e099a3) {
            switch (cls - 0x7e07cc0) {
            case 0:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f32150(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x7b1794db, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            case 1:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f321a0(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x7b1794db, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            case 2:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f321f0(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x9b06d0eb, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            case 3:
                FUN_00f33bf0(ctx);
                {
                    float v[3] = { rgb[0], rgb[1], rgb[2] };
                    FUN_00f32100(ctx, v);
                }
                FUN_00f34560(ctx);
                FUN_005ca880(0x9b06d0eb, rgb[2] + rgb[1] + rgb[0]);
                return 0;
            default:
                break;
            }
        }
        else if (cls == 0x7e099a3) {
            if (FUN_00eea8e0(this_->mp1c, 0, this_->mp24))
                FUN_00eea910(this_->mp1c, this_->mp24, rgb[0], rgb[1], rgb[2]);
        }
        return 0;
    }

    if (code == 0xd69290d7) {
        FUN_00f33bf0(ctx);
        void* a = 0;
        void* b = 0;
        FUN_00eeb920(&a, ctx, 0);
        FUN_00f344e0(ctx, &a, &b);
        FUN_00f34560(ctx);
        FUN_00f31ea0(ctx);
        return 0;
    }
    if (code == 0xd69290d8) {
        void* a = 0;
        void* b = 0;
        FUN_00eeb920(&a, ctx, 0);
        FUN_00f344e0(ctx, &a, &b);
        return 0;
    }
    return 0;
}

// ===========================================================================
// @ 0x00ee7810
int __cdecl FUN_00ee7810(u32 id)
{
    if (id == 0x29c388a)
        return (int)0xb8669ec9;
    if (id == 0x3a8be428)
        return 0x37148141;
    return (id != 0x6d60a1cc ? (int)0x7a3d42b8 : 0) + (int)0xbcd73e89;
}

// ===========================================================================
// @ 0x00ee7850
int* __cdecl FUN_00ee7850(int* p)
{
    while (p != 0) {
        int n = (*(int(__thiscall**)(int*))((char*)*(void**)p + 0x1c))(p);
        if (!(8 < (u32)n + 0xf8d3d7e0u))
            break;
        p = (int*)(*(void*(__thiscall**)(int*))((char*)*(void**)p + 0x10))(p);
    }
    return p;
}

// ===========================================================================
// @ 0x00ee78c0
bool __stdcall FUN_00ee78c0(int id)
{
    int found1 = -1;
    int found2 = found1 - 1;
    for (u32 i = 0; i < 0xf; i++) {
        if (DAT_0148aafc[i] == (u32)id) {
            found1 = (int)i;
            break;
        }
    }
    for (u32 j = 0; j < 0xf; j++) {
        if (DAT_0148aac0[j] == (u32)id) {
            found2 = (int)j;
            break;
        }
    }
    return found2 != found1;
}

// ===========================================================================
// @ 0x00ee7910
char __stdcall FUN_00ee7910(int id, u32* out, u8* flag)
{
    if (out != 0 && flag != 0) {
        u32 i = 0;
        do {
            if (DAT_0148aafc[i] == (u32)id) {
                *out = i;
                *flag = 0;
                return 1;
            }
            i++;
        } while (i < 0xf);
        i = 0;
        do {
            if (DAT_0148aac0[i] == (u32)id) {
                *out = i;
                *flag = 1;
                return 1;
            }
            i++;
        } while (i < 0xf);
    }
    return 0;
}
