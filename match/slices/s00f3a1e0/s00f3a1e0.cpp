// Slice s00f3a1e0: Sporepedia "large asset view" HUD panel (the PA_Agg dual-vtable object).
//
//  00f3a1e0  bounding-rect -> normalized NDC coords pushed into the panel's transform sink
//            (free __cdecl function: args are (win, host), ecx unused, caller cleans)
//  00f3a470  constructor (two vtables, zeroed members)
//  00f3a4e0  window id -> SetNumberString formatted number setter
//  00f3a540  "drag" window flag setup (parent slot 0x28 + 4 child slots 0x7c)
//  00f3a630  big panel setup: window manager hand-off, property reads, child window layout,
//            minimap material, button-bounce resource, layout refresh
//  00f3aa30  per-frame minimap/clock update (colour vector + "%02d:%02d" text)
//  00f3ac00  message handler (jump table over message ids 6..13 + 4 hashed ids)
//
// The object has two vftable pointers: +0 is the panel vtable, +8 is the message-handler
// subobject vtable.  Every method here except the message handler is entered with ECX == the
// object base (the layout below); 0x00f3ac00 is entered with ECX == base+8, so it works on a
// `base = this - 8` pointer and its member calls re-derive the panel `this` (`lea ecx,[esi-8]`).
//   +00 vftable1      +04 refcount owner    +08 vftable2 (message self)
//   +0c window mgr    +10 AutoRefCount asset
//   +14 float2 a      +1c float2 b          +24 float2 c
//   +2c float dragStart   +30 float dragOrigin   +34 byte dragging
//   +38 float dragRange   +3c byte dragging2
//
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define VTOF(p) (*(void***)(p))

// ---------------------------------------------------------------------------
// __thiscall vtable slot helpers (ECX == this, callee pops the stack args).
// ---------------------------------------------------------------------------
typedef char  (__thiscall *PF_Char0)(void*);
typedef void  (__thiscall *PF_Void0)(void*);
typedef void  (__thiscall *PF_Void1i)(void*, int);
typedef void  (__thiscall *PF_Void1u)(void*, unsigned);
typedef void  (__thiscall *PF_Void1f)(void*, float);
typedef void  (__thiscall *PF_Void1p)(void*, void*);
typedef void  (__thiscall *PF_Void2ii)(void*, int, int);
typedef void  (__thiscall *PF_Void2ip)(void*, int, void*);
typedef char  (__thiscall *PF_Char3uup)(void*, unsigned, unsigned, void**);
typedef unsigned (__thiscall *PF_U0)(void*);
typedef void* (__thiscall *PF_P0)(void*);
typedef void* (__thiscall *PF_P1u)(void*, unsigned);
typedef void* (__thiscall *PF_P2ii)(void*, int, int);
typedef float*(__thiscall *PF_Pf0)(void*);

// ---------------------------------------------------------------------------
// Globals referenced by this object file (byte offsets are documented at use).
// ---------------------------------------------------------------------------
extern void*  g_16c7aa4;        // 0x16c7aa4  global app object (->+18 game state)
extern float  g_15b02e0;        // 0x15b02e0  pi
extern float  g_16c87b8;        // 0x16c87b8
extern float  g_13f1164;        // 0x13f1164  24.0
extern float  g_148d25c;        // 0x148d25c  23.0
extern float  g_1466760;        // 0x1466760  1440.0
extern float  g_13ec4d0;        // 0x13ec4d0  100.0
extern float  g_13eb960;        // 0x13eb960  0.01
extern float  g_15b02d8;        // 0x15b02d8  0.5
extern void*  g_14426a0;        // 0x14426a0  base vftable
extern void*  g_148d22c;        // 0x148d22c  panel vftable
extern void*  g_148d210;        // 0x148d210  message-handler vftable
extern const char    g_147d84e; // 0x147d84e  "...itorButtonBounceDuration"
extern const wchar_t g_147fb4c; // 0x147fb4c  L"ui_material_minimap"
extern const wchar_t g_148d248; // 0x148d248  L"%02d:%02d"
extern const wchar_t g_1667bac; // 0x1667bac  eastl empty-string literal
extern const wchar_t g_1667bae; // 0x1667bae  eastl empty-string literal + 2

// ---------------------------------------------------------------------------
// External helpers.
// ---------------------------------------------------------------------------
extern "C" void*   f_0067dd50();                                   // 0x67dd50 cdecl
extern "C" float*  f_00808d20(float* out, void* win, char c);      // 0x808d20 SPUIHelpers_GetBoundingScreenRect
extern "C" void*   f_0067de30();                                   // 0x67de30 SP::PropertyManager
extern "C" bool    f_006a10c0(const void* props, unsigned key, void* out); // 0x6a10c0 SP::GetPropertyAsVector2
extern "C" void    f_00808ad0(void* win, const wchar_t* name, int a);      // 0x808ad0 SPUIHelpers_SetWindowSPMaterial
extern "C" char    f_00806230(void* ids, void** out, char a, int b, int c); // 0x806230 CreateImageFromResource2
extern "C" void    f_00957c20(int asset, int one);                 // 0x957c20 Fn00957c20
extern "C" void    f_00881ae0(int value, int hi, char* buf, unsigned size); // 0x881ae0 EA::Locale::SetNumberString
extern "C" void    f_00808230(void* win, float* v);                // 0x808230 FUN_00808230
extern "C" void    f_0041e050(void* str, const wchar_t* fmt, int a, int b); // 0x41e050 WStr_Format
extern "C" void    f_00f47380(void* p);                            // 0xf47380 operator delete
extern "C" float   f_00f3a120(int id);                             // 0xf3a120
extern "C" void*   f_0067caa0();                                   // 0x67caa0 SP::WindowManager
extern "C" void*   f_00435e90();                                   // 0x435e90 GetRecorderState
extern "C" void    f_00435ed0(unsigned key, void* state);          // 0x435ed0 KillSetiEffects
extern "C" void    f_005ca880(unsigned key, float v);              // 0x5ca880 SetGlobalProperty
extern "C" void*   f_005ca960(void* win);                          // 0x5ca960 interface_cast<IWinButton*>

// thiscall externals modelled as methods (MSVC rejects __thiscall on free functions).
struct Ext {
    void  f33bf0();                 // 0xf33bf0
    void  f34560();                 // 0xf34560
    void  f33710();                 // 0xf33710
    void  f32410();                 // 0xf32410
    void  f33580(float v);          // 0xf33580
    void  f335e0(int b);            // 0xf335e0
    void  f31de0(float v);          // 0xf31de0
    void  f31d80(float v);          // 0xf31d80
    void  f31ed0(int b);            // 0xf31ed0
    void  f32240(float v);          // 0xf32240
    void  bbe0(int a, int b);       // 0xefbbe0 ToggleHint
    void  eb80(int a, void* alloc); // 0x82eb80
    void* getalloc();               // 0x7f54d0 Resource::GetAllocator
};

// Small helper structs for external object layouts.
struct F8 { int v[8]; };                    // viewport ratios returned by FUN_0067dd50()->vfn[0x1c]
struct WString { wchar_t* begin; wchar_t* end; wchar_t* cap; };
struct ARef { void* p; };

struct ICoordSink {
    void Set(float value, int index);       // 0x82e340
};

namespace SP {
bool GetPropertyAsVector2(const void* props, unsigned key, float* out);  // 0x6a10c0
}

// ---------------------------------------------------------------------------
// Panel object.
// ---------------------------------------------------------------------------
struct Msg {
    char     pad0[8];
    unsigned id;        // +08
    float    f0c;       // +0c
    int      i10;       // +10
    int      i14;       // +14
};

struct CPanel {
    void* m00f3a470();                              // 0x00f3a470
    void  m00f3a4e0(int id, int value);             // 0x00f3a4e0
    void  m00f3a540(int arg);                       // 0x00f3a540
    char  m00f3a630(void* win);                     // 0x00f3a630
    void  m00f3aa30();                              // 0x00f3aa30
    char  m00f3ac00(void* win, Msg* msg);           // 0x00f3ac00
};

void m00f3a1e0(void* win, void* host);              // 0x00f3a1e0 (__cdecl)

// ===========================================================================
// 0x00f3a1e0 -- push the normalized bounding rect of `win` into the sink that
// lives under `host`'s parent chain (slot 0x5234b49).
// ===========================================================================
// @ 0x00f3a1e0
void m00f3a1e0(void* win, void* host)
{
    void* app = f_0067dd50();
    F8* src = (F8*)((PF_P0)VTOF(app)[0x1c / 4])(app);
    F8 m = *src;
    float rc[4];
    f_00808d20(rc, win, 0);

    float invx = 1.0f / (float)m.v[0];
    float invy = 1.0f / (float)m.v[1];

    float xa = (invx * rc[0] - 0.5f) * 2.0f;
    if (xa < -1.0f) xa = -1.0f;
    if (xa > 1.0f) xa = 1.0f;

    float ya = (invy * rc[1] - 0.5f) * 2.0f;
    if (ya < -1.0f) ya = -1.0f;
    if (ya > 1.0f) ya = 1.0f;

    float y0 = -ya;

    float xb = (invx * rc[2] - 0.5f) * 2.0f;
    if (xb < -1.0f) xb = -1.0f;
    if (xb > 1.0f) xb = 1.0f;

    float yb = (invy * rc[3] - 0.5f) * 2.0f;
    if (yb < -1.0f) yb = -1.0f;
    if (yb > 1.0f) yb = 1.0f;

    float y1 = -yb;

    void* sink = ((PF_P0)VTOF(host)[0x4c / 4])(host);
    if (sink)
        sink = ((PF_P1u)VTOF(sink)[0xc / 4])(sink, 0x5234b49);

    ICoordSink* s = (ICoordSink*)sink;
    s->Set((xa > xb) ? xb : xa, 0);
    s->Set((y0 > y1) ? y1 : y0, 1);
    s->Set((xb > xa) ? xb : xa, 2);
    s->Set((y1 > y0) ? y1 : y0, 3);
    s->Set(fabsf(1.0f / (xb - xa)), 4);
    s->Set(fabsf(1.0f / (y0 - y1)), 5);
}

// ===========================================================================
// 0x00f3a470 -- constructor: installs both vtables, zeroes the members.
// ===========================================================================
// @ 0x00f3a470
void* CPanel::m00f3a470()
{
    char* s = (char*)this;
    *(int*)(s + 4) = 0;
    // The base-vftable store is overwritten on the next line but retail /O2 keeps it
    // (vptr stores are opaque to the optimizer); force it through a volatile slot.
    *(void* volatile*)(s + 8) = &g_14426a0;
    *(void**)(s + 0) = &g_148d22c;
    *(void**)(s + 8) = &g_148d210;
    *(int*)(s + 0xc) = 0;
    *(int*)(s + 0x10) = 0;
    *(float*)(s + 0x2c) = 0.0f;
    *(char*)(s + 0x34) = 0;
    *(float*)(s + 0x38) = 0.0f;
    return s;
}

// ===========================================================================
// 0x00f3a4e0 -- resolve window `id` and set its text to the localized `value`.
// ===========================================================================
// @ 0x00f3a4e0
void CPanel::m00f3a4e0(int id, int value)
{
    char* s = (char*)this;
    wchar_t buf[0x28];
    void* wm = *(void**)(s + 0xc);
    if (wm == 0)
        return;
    void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, id, 1);
    if (w == 0)
        return;
    buf[0] = 0;
    f_00881ae0(value, 0, (char*)buf, 0x28);
    ((PF_Void1p)VTOF(w)[0x80 / 4])(w, buf);
}

// ===========================================================================
// 0x00f3a540 -- window `arg` becomes the active drag target: its parent gets
// slot 0x28 = 4 and the four child ids get slot 0x7c = (1, arg).
// ===========================================================================
// @ 0x00f3a540
void CPanel::m00f3a540(int arg)
{
    char* s = (char*)this;
    void* wm = *(void**)(s + 0xc);
    void* a = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x899eb157, 1);
    if (a == 0)
        return;
    void* b = ((PF_P1u)VTOF(a)[0xc / 4])(a, 0x8ed27e7a);
    if (b == 0)
        return;
    ((PF_Void2ii)VTOF(b)[0x28 / 4])(b, 4, arg);

    unsigned ids[4] = { 0x7ab9c60, 0x7ab9c61, 0x7ab9c62, 0x7ab9c63 };
    for (int i = 0; i < 4; i++) {
        void* w2 = ((PF_P2ii)VTOF(*(void**)(s + 0xc))[0xf0 / 4])(*(void**)(s + 0xc), ids[i], 1);
        if (w2)
            ((PF_Void2ii)VTOF(w2)[0x7c / 4])(w2, 1, arg);
    }
}

// ===========================================================================
// 0x00f3a630 -- panel setup.  Takes over the window manager, reads the panel
// placement properties, lays out the child windows, sets the minimap material
// and the button-bounce resource, then refreshes the layout.
// ===========================================================================
// @ 0x00f3a630
char CPanel::m00f3a630(void* win)
{
    char* s = (char*)this;
    void* old = *(void**)(s + 0xc);
    if (win != old) {
        if (win)
            ((PF_Void0)VTOF(win)[0])(win);
        *(void**)(s + 0xc) = win;
        if (old)
            ((PF_Void0)VTOF(old)[1])(old);
    }

    ARef prop;
    prop.p = 0;
    ARef img;
    img.p = 0;

    void* pm = f_0067de30();
    void* prev = prop.p;
    if (prev != 0) {
        prop.p = 0;
        ((PF_Void0)VTOF(prev)[1])(prev);
    }

    if (((PF_Char3uup)VTOF(pm)[0x2c / 4])(pm, 0xe0fa461e, 0x2be327a9, &prop.p)) {
        if (prop.p != 0) {
            SP::GetPropertyAsVector2(prop.p, 0x328a115, (float*)(s + 0x14));
            SP::GetPropertyAsVector2(prop.p, 0x328a12f, (float*)(s + 0x24));
            SP::GetPropertyAsVector2(prop.p, 0x1730d549, (float*)(s + 0x1c));
        }
    }

    void* wm = *(void**)(s + 0xc);

    // panel offset (top-left)
    {
        void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x71842d8, 1);
        if (w != 0)
            w = ((PF_P1u)VTOF(w)[0xc / 4])(w, 0xf00a8a0);
        ((PF_Void2ii)VTOF(w)[0x24 / 4])(w, (int)(*(float*)(s + 0x14) * 100.0f), 0);
        ((PF_Void2ii)VTOF(w)[0x2c / 4])(w, (int)(*(float*)(s + 0x18) * 100.0f), 0);
    }
    // panel size
    {
        void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x7183c38, 1);
        if (w != 0)
            w = ((PF_P1u)VTOF(w)[0xc / 4])(w, 0xf00a8a0);
        ((PF_Void2ii)VTOF(w)[0x24 / 4])(w, 0, 0);
        ((PF_Void2ii)VTOF(w)[0x2c / 4])(w, 4, 0);
    }
    // panel frame
    {
        void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x72ff8e8, 1);
        if (w != 0)
            w = ((PF_P1u)VTOF(w)[0xc / 4])(w, 0xf00a8a0);
        ((PF_Void2ii)VTOF(w)[0x24 / 4])(w, (int)(*(float*)(s + 0x1c) * 100.0f), 0);
        ((PF_Void2ii)VTOF(w)[0x2c / 4])(w, (int)(*(float*)(s + 0x20) * 100.0f), 0);
    }

    char* sub = s + 8;
    void* mini = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x7393e58, 1);
    f_00808ad0(mini, &g_147fb4c, 1);
    ((PF_Void0)VTOF(mini)[0x90 / 4])(mini);
    ((PF_Void1p)VTOF(mini)[0x104 / 4])(mini, sub);

    unsigned ids[3] = { 0xdb774579, 0x2f7d0004, 0x8a7be0c0 };
    void* imgp = 0;
    f_00806230(ids, &imgp, 0, -1, -1);
    if (imgp != 0) {
        void* holder = *(void**)((char*)imgp + 4);
        void* bounce = 0;
        if (holder != 0)
            bounce = ((PF_P1u)VTOF(holder)[0xc / 4])(holder, (unsigned)&g_147d84e);
        void* was = *(void**)(s + 0x10);
        if (bounce != was) {
            if (bounce)
                ((PF_Void0)VTOF(bounce)[0])(bounce);
            *(void**)(s + 0x10) = bounce;
            if (was)
                ((PF_Void0)VTOF(was)[1])(was);
        }
        f_00957c20((int)*(void**)(s + 0x10), 1);
        void* parent = ((PF_P0)VTOF(mini)[0x4c / 4])(mini);
        void* obj = 0;
        if (parent)
            obj = ((PF_P1u)VTOF(parent)[0xc / 4])(parent, 0x5234b49);
        void* alloc = ((Ext*)*(void**)(s + 0x10))->getalloc();
        ((Ext*)obj)->eb80(1, alloc);
    }

    {
        void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x73bec90, 1);
        if (w != 0) {
            ((PF_Void1u)VTOF(w)[0x78 / 4])(w, 0x747d67b);
            float* pf = ((PF_Pf0)VTOF(w)[0x34 / 4])(w);
            *(float*)(s + 0x38) = pf[2] - pf[0];
            ((PF_Void1p)VTOF(w)[0x104 / 4])(w, sub);
        }
    }
    {
        void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x74261f8, 1);
        if (w != 0)
            ((PF_Void1p)VTOF(w)[0x104 / 4])(w, sub);
    }
    {
        void* w = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x899eb157, 1);
        if (w != 0)
            ((PF_Void1p)VTOF(w)[0x104 / 4])(w, sub);
    }
    ((PF_Void1p)VTOF(wm)[0x104 / 4])(wm, sub);

    if (img.p != 0)
        ((PF_Void0)VTOF(img.p)[1])(img.p);
    if (prop.p != 0)
        ((PF_Void0)VTOF(prop.p)[1])(prop.p);
    return 1;
}

// ===========================================================================
// 0x00f3aa30 -- per-frame HUD refresh: minimap colour vector from the in-game
// time-of-day and the clock text.
// ===========================================================================
// @ 0x00f3aa30
void CPanel::m00f3aa30()
{
    char* s = (char*)this;
    char* game = *(char**)((char*)g_16c7aa4 + 0x18);
    float t = *(float*)(game + 0xd4);

    void* mini = ((PF_P2ii)VTOF(*(void**)(s + 0xc))[0xf0 / 4])(*(void**)(s + 0xc), 0x7393e58, 1);
    if (mini != 0) {
        float v[4];
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 1.0f;
        v[3] = g_15b02e0 - t * g_16c87b8;
        f_00808230(mini, v);
        ((PF_Void0)VTOF(mini)[0x90 / 4])(mini);
    }

    void* clock = ((PF_P2ii)VTOF(*(void**)(s + 0xc))[0xf0 / 4])(*(void**)(s + 0xc), 0x7393f20, 1);
    if (game == 0 || clock == 0)
        return;

    float hours = t * g_13f1164;
    if (hours < 0.0f) hours = 0.0f;
    if (hours > g_148d25c) hours = g_148d25c;

    void* w = ((PF_P2ii)VTOF(*(void**)(s + 0xc))[0xf0 / 4])(*(void**)(s + 0xc), 0x7393f20, 1);
    if (w == 0)
        return;

    WString str;
    str.begin = (wchar_t*)&g_1667bac;
    str.end = (wchar_t*)&g_1667bac;
    str.cap = (wchar_t*)&g_1667bae;
    f_0041e050(&str, &g_148d248, (int)hours, (int)fmod((double)(t * 1440.0f), 60.0));
    ((PF_Void1p)VTOF(w)[0x80 / 4])(w, str.begin);
    if ((((int)((char*)str.cap - (char*)str.begin) & ~1) > 2) && str.begin != 0)
        f_00f47380(str.begin);
}

// ===========================================================================
// 0x00f3ac00 -- panel message handler (ECX == this+8).  Returns whether the
// message was handled.  Member offsets below are relative to the object base,
// so `b` is this-8.
// ===========================================================================
// @ 0x00f3ac00
char CPanel::m00f3ac00(void* win, Msg* msg)
{
    char* b = (char*)this - 8;
    CPanel* self = (CPanel*)((char*)this - 8);
    char* game = *(char**)((char*)g_16c7aa4 + 0x18);
    Ext* gm = (Ext*)game;
    bool result = false;

    switch (msg->id) {
    case 6:
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) != 0x73bec90)
            break;
        {
            void* wm = f_0067caa0();
            ((PF_Void2ip)VTOF(wm)[0x58 / 4])(wm, 1, win);
            ((PF_Void1u)VTOF(win)[0x78 / 4])(win, 0x747d67c);
            *(char*)(b + 0x34) = 1;
            *(float*)(b + 0x30) = *(float*)(game + 0xd4);
            *(float*)(b + 0x2c) = msg->f0c;
            if (*(char*)(b + 0x3c) != 0)
                break;
            gm->f33bf0();
            *(char*)(b + 0x3c) = 1;
            return result;
        }
    case 7:
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) != 0x73bec90)
            break;
        if (*(char*)(b + 0x34) == 0)
            break;
        {
            void* wm = f_0067caa0();
            ((PF_Void2ip)VTOF(wm)[0x5c / 4])(wm, 1, win);
            ((PF_Void1u)VTOF(win)[0x78 / 4])(win, 0x747d67b);
            *(char*)(b + 0x34) = 0;
            ((Ext*)*(void**)((char*)g_16c7aa4 + 0xd4))->bbe0(0xa1, 0xa2);
            if (*(char*)(b + 0x3c) == 0)
                break;
            gm->f34560();
            *(char*)(b + 0x3c) = 0;
            return result;
        }
    case 8:
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) != 0x73bec90)
            break;
        if (*(char*)(b + 0x34) == 0)
            break;
        {
            float v = (msg->f0c - *(float*)(b + 0x2c)) * (-1.0f / *(float*)(b + 0x38)) * g_15b02d8
                      + *(float*)(b + 0x30);
            gm->f33580(v - (float)floor(v));
            self->m00f3aa30();
            return result;
        }
    case 12:
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) != 0x7393e58)
            break;
        ((PF_Void0)VTOF(win)[0x90 / 4])(win);
        return result;
    case 13:
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) != 0x7393e58)
            break;
        {
            void* wm = *(void**)(b + 0xc);
            void* w2 = ((PF_P2ii)VTOF(wm)[0xf0 / 4])(wm, 0x73a7978, 1);
            m00f3a1e0(w2, win);
        }
        return result;
    case 0x7a44749:
        {
            int id = msg->i10;
            if (id != 0x7183c38 && id != 0x71842d8 && id != 0x72ff8e8)
                break;
            if (msg->i14 == msg->i10) {
                gm->f32410();
                return 1;
            }
            if (id == 0x72ff8e8)
                gm->f33710();
            gm->f34560();
            return 1;
        }
    case 0x7a4489c:
        {
            int id = msg->i10;
            if (id == 0x7183c38 || id == 0x71842d8 || id == 0x72ff8e8) {
                gm->f33bf0();
                result = true;
            }
        }
        break;
    case 0x287259f6:
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) == 0x74261f8) {
            void* child = ((PF_P1u)VTOF(win)[0xc / 4])(win, 0x8ed27e7a);
            if (child == 0)
                break;
            bool bb = ((((PF_U0)VTOF(child)[0x20 / 4])(child) >> 2) & 1) != 0;
            f_00435ed0(bb ? 0x9316596c : 0x72b10481, f_00435e90());
            gm->f33bf0();
            gm->f335e0(bb);
            gm->f34560();
            return result;
        }
        if (((PF_U0)VTOF(win)[0x1c / 4])(win) == 0x899eb157) {
            void* btn = f_005ca960(win);
            if (btn == 0)
                break;
            bool bb = ((((PF_U0)VTOF(btn)[0x20 / 4])(btn) >> 2) & 1) != 0;
            f_00435ed0(0xe76c9b4f, f_00435e90());
            self->m00f3a540(bb);
            gm->f33bf0();
            gm->f31ed0(bb);
            gm->f34560();
            return result;
        }
        break;
    case 0xef00a884:
        {
            int id = msg->i10;
            if (id == 0x7183c38) {
                gm->f31d80(f_00f3a120(msg->i14));
                self->m00f3a4e0(0x73a5598, msg->i14);
                return 1;
            }
            if (id == 0x71842d8) {
                gm->f31de0((float)msg->i14 * g_13eb960);
                self->m00f3a4e0(0x73a5550, msg->i14);
                return 1;
            }
            if (id == 0x72ff8e8) {
                int v = msg->i14;
                gm->f32240((float)v * g_13eb960);
                self->m00f3a4e0(0x73a55a0, msg->i14);
                f_005ca880(0x2d06b2b4, (float)v * g_13eb960);
                return 1;
            }
        }
        break;
    }
    return result;
}
