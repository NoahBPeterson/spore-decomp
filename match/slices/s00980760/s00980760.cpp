// Slice 60: EA::UTFWinControls Navigator/RelativeNavigator/RotateEffect + WinScrollbar,
// IWinScrollbar, ScrollbarDrawable  (0x980760-0x9818c0).
//
// Retail layout notes (derived from the WinScrollbar ctor 0x983790):
//   window base has two vtable pointers: +0x000 (primary) and +0x004 (secondary base,
//   "IWindow": InvalidateLayout/GetCapture/Notify/SendMessage live there), mpWinMgr at
//   +0x034, mId/mCommandId at +0x080/+0x084.  The IWinScrollbar subobject starts at
//   +0x20c (its own vtable).  Window-base methods take `this` = window; the secondary-base
//   methods take `this` = window+4; IWinScrollbar methods take `this` = window+0x20c.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

inline void* operator new(size_t, void* p) { return p; }

typedef void (__thiscall *VFn0)(void*);
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])

void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0 (cdecl)

// external thiscall targets (byte offsets are relocations, names are irrelevant)
struct XWin { void SerUpdate(); void InvalidateLayout(); };            // 009614a0 / 009609b0
void __fastcall Navigator_dtor(void* p);                               // 00980420
void __fastcall Navigator_baseCtor(void* p);                           // 00980430
void __fastcall FadeEffect_ctor(void* p);                              // 00963db0
struct XCM {
    void SetX(float v);                                                // 0095eb00
    void SetY(float v);                                                // 0095ec30
    void SetZ(float v);                                                // 0095ed60
    void SetRotationAtLeast2(float* face, float v);                    // 0095f5c0
};
struct XStopwatch {
    void Restart();                                                    // 00571e80
    void Init(int a, int b);                                           // 0093a560
    void SetUnits(int u);                                              // 0093a1a0
    int64_t GetElapsed();                                              // 0093a5e0
    int64_t GetElapsedFloat();                                         // 0093a3a0
};
struct XPropList { void SetBoolProperty(); };                          // 0093a2e0

struct Image {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[6];
    int w, h;                                                          // +0x1c, +0x20
};

namespace EA { namespace UTFWinControls {

// ---------------------------------------------------------------- vtables (relocated)
extern void* vt_1444368[];
extern void* vt_1444350[];
extern void* vt_1444314[];
extern void* vt_1444458[];
extern void* vt_1444434[];
extern void* vt_1443f78[];
extern void* vt_1443f5c[];
extern void* vt_1443f38[];
extern void* vt_1444238[];
extern void* vt_1444220[];
extern void* vt_1442188[];
extern void* vt_1442170[];
extern void* vt_async_13fa72c[];
extern void* vt_gme_13eb938[];

// ---------------------------------------------------------------- Navigator (0x980330..0x980b60)
struct Navigator {
    void* vt0;                                                         // +0x00
    void* vt4;                                                         // +0x04
    int   f08;                                                         // +0x08
    void* vtc;                                                         // +0x0c
    int   f10;                                                         // +0x10
    int   f14;                                                         // +0x14
    int   f18;                                                         // +0x18
    int   mode;                                                        // +0x1c
    bool Navigate(void* mgr, int cmd);                                 // 00980760
};

// iterator-like interface returned by mgr->vt[0x48]
struct NavIter { virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
                 virtual void* i10(); virtual void i14(); virtual void i18(); virtual void i1c(); };

// ---------------------------------------------------------------- RotateEffect
struct RotateEffect {
    void* vt0;                                                         // +0x00
    void* vt4;                                                         // +0x04
    int   f08;                                                         // +0x08
    void* vtc;                                                         // +0x0c
    int   f10;                                                         // +0x10
    int   f14;                                                         // +0x14
    int   f18;                                                         // +0x18
    int   f1c;                                                         // +0x1c
    char  pad20[0x60 - 0x20];
    void* vt60;                                                        // +0x60
    float fx;                                                          // +0x64
    float fy;                                                          // +0x68
    float fz;                                                          // +0x6c
    float scale;                                                       // +0x70
    RotateEffect();                                                    // 00980e30
    ~RotateEffect();                                                   // 00980c00
    void SetRotation(void* unused, XCM* cm, float deg);               // 00980cf0
};

struct BasicFactory_RelativeNavigator {
    Navigator* CreateInstance(int unused, void* alloc);                // 00980b70
};
struct BasicFactory_RotateEffect {
    RotateEffect* CreateInstance(int unused, void* alloc);             // 00980ea0
};

// ---------------------------------------------------------------- WinScrollbar
struct WinScrollbar;
struct SBMsg { int w0, w1; uint32_t type; uint32_t src; int from; int to; int pad; };

struct IWinScrollbar {
    void* vt;                                                          // +0x00 (abs 0x20c)
    int current;                                                       // +0x04 (0x210)
    int minVal;                                                        // +0x08 (0x214)
    int maxVal;                                                        // +0x0c (0x218)
    int visibleRange;                                                  // +0x10 (0x21c)
    int pageOverlap;                                                   // +0x14 (0x220)
    int arrowDelta;                                                    // +0x18 (0x224)
    int pageDelta;                                                     // +0x1c (0x228)
    int minThumbSize;                                                  // +0x20 (0x22c)
    int orientation;                                                   // +0x24 (0x230)
    uint8_t hlComp;                                                    // +0x28 (0x234)
    uint8_t selComp;                                                   // +0x29 (0x235)
    uint8_t pad02a[2];
    float thumbOffset;                                                 // +0x2c (0x238)
    uint8_t refresh;                                                   // +0x30 (0x23c)
    uint8_t pad031[3];
    int flags;                                                         // +0x34 (0x240)
    int f244;                                                          // +0x38 (0x244)
    uint8_t timer[0x18];                                               // +0x3c (0x248)
    float compArea[7][4];                                              // +0x54 (0x260)
    WinScrollbar* win();
    void SetOrientation(int o);                                        // 00981000
    void SetFlags(uint32_t mask, char on);                             // 00981030
    void SetDrawable(void* d);                                         // 00981060
    void SetValue(int v, char notify);                                 // 009810a0
    void SetMinimumValue(int v, int notify);                           // 00981130
    void SetMaximumValue(int v, int notify);                           // 00981170
    void SetVisibleRange(int v, int notify);                           // 009811b0
    void SetPageOverlap(int v);                                        // 00981200
};

struct WinScrollbar {
    void* vt0;                                                         // +0x000
    void* vtIW;                                                        // +0x004
    char  pad008[0x34 - 8];
    void* winMgr;                                                      // +0x034
    char  pad038[0x80 - 0x38];
    int   id0;                                                         // +0x080
    int   id1;                                                         // +0x084
    char  pad088[0x20c - 0x88];
    IWinScrollbar sb;                                                  // +0x20c
    void* iw() { return (char*)this + 4; }
    void  UpdateAndSync();                                             // 00980fa0
    int   IsActive();                                                  // 009816e0
    void  SetRefreshFlag(char on);                                     // 00981700
    void  SetRefresh(char on);                                         // 00981770
    bool  OnMouseDown(float x, float y, int a3, int button);           // 00981220
    bool  OnMouseUp(float x, float y, int a3, int flags);              // 00981430
    bool  OnFocusChange(int state, void* w);                           // 009814c0
    bool  OnTick();                                                    // 00981500
};

inline WinScrollbar* IWinScrollbar::win() { return (WinScrollbar*)((char*)this - 0x20c); }

// secondary-base view of the window (this = window+4): its own virtual slot 0x94
struct IWinSB2 {
    void InvalidateLayoutNoArgs();                                     // 009816c0
};

// ---------------------------------------------------------------- ScrollbarDrawable
struct IScrollbarDrawable {
    void* vt;                                                          // +0x00
    Image* images[7];                                                  // +0x04
    void SetComponentImage(uint32_t idx, Image* p);                    // 00981860
};
struct ScrollbarDrawable {
    void* vt0;                                                         // +0x00
    void* vt4;                                                         // +0x04
    int   f08;                                                         // +0x08
    void* vtc;                                                         // +0x0c
    Image* images[7];                                                  // +0x10
    bool GetNaturalSize(float* out, int unused, int idx);              // 00981800
};

}}  // namespace

using namespace EA::UTFWinControls;

// ================================================================ Navigator

// @ 0x980760
bool Navigator::Navigate(void* mgr, int cmd) {
    void* it = VSLOT(void*(__thiscall*)(void*, int), mgr, 0x48)(mgr, cmd);
    if (!it) return false;
    void* p;
    switch (mode) {
    case 0: case 1: case 2: case 3: {
        void* list = VSLOT(void*(__thiscall*)(void*), it, 0x10)(it);
        if (!list) return false;
        void** a = (void**)VSLOT(void*(__thiscall*)(void*, void*), list, 0xd0)(list, (char*)this - 0x30 + 0x30);
        void** b = (void**)VSLOT(void*(__thiscall*)(void*, void*), list, 0xcc)(list, (char*)this - 0x30 + 0x30);
        if (*a == *b) return false;
        VSLOT(void(__thiscall*)(void*, void*, void*), list, 0xd4)(list, (char*)this - 0x30 + 0x30, it);
        void** c = (void**)VSLOT(void*(__thiscall*)(void*, void*), list, 0xd0)(list, (char*)this - 0x30 + 0x30);
        if ((void*)this == 0) {}
        if (*c == (void*)this) { (void)0; }
        p = 0;
        break;
    }
    case 6: {
        p = VSLOT(void*(__thiscall*)(void*), it, 0x10)(it);
        break;
    }
    default:
        return true;
    }
    if (p) VSLOT(void(__thiscall*)(void*, void*, void*), mgr, 0x4c)(mgr, p, it);
    (void)mgr;
    return true;
}

// ================================================================ factories

// @ 0x980b70
Navigator* BasicFactory_RelativeNavigator::CreateInstance(int unused, void* alloc) {
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x20, 4, "UTFWin/EA::UTFWinControls::RelativeNavigator", alloc);
    if (mem != 0) {
        Navigator_baseCtor(mem);
        ((void**)mem)[6] = vt_async_13fa72c;
        ((void**)mem)[0] = vt_1444238;
        ((void**)mem)[1] = vt_1444220;
        ((void**)mem)[3] = vt_1442188;
        ((void**)mem)[6] = vt_1442170;
        ((void**)mem)[7] = (void*)1;
        return (Navigator*)mem;
    }
    return 0;
}

// ================================================================ RotateEffect

// @ 0x980c00
RotateEffect::~RotateEffect() {
    *(void**)this = vt_1444368;
    *(void**)((char*)this + 4) = vt_1444350;
    *(void**)((char*)this + 0xc) = vt_1444314;
    *(void**)((char*)this + 0x60) = vt_gme_13eb938;
    Navigator_dtor(this);
}

// @ 0x980e30
RotateEffect::RotateEffect() {
    FadeEffect_ctor(this);
    *(void**)((char*)this + 0x60) = vt_1444434;
    *(void**)this = vt_1444368;
    *(void**)((char*)this + 4) = vt_1444350;
    *(void**)((char*)this + 0xc) = vt_1444314;
    *(void**)((char*)this + 0x60) = vt_1444458;
    fx = 0.0f;
    fz = 0.0f;
    fy = 1.0f;
    scale = 45.0f;
}

// @ 0x980ea0
RotateEffect* BasicFactory_RotateEffect::CreateInstance(int unused, void* alloc) {
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x78, 8, "UTFWin/EA::UTFWinControls::RotateEffect", alloc);
    if (mem != 0) {
        return new (mem) RotateEffect();
    }
    return 0;
}

// @ 0x980cf0
void RotateEffect::SetRotation(void* unused, XCM* cm, float deg) {
    (void)unused;
    int axis = 0;
    int count = 0;
    if (fabsf(fx) > 1.1920929e-07f) count = 1;
    if (fabsf(fy) > 1.1920929e-07f) { axis = 1; count++; }
    if (fabsf(fz) > 1.1920929e-07f) { axis = 2; count++; }
    if (count > 1) axis = 3;
    if (count <= 0) return;
    switch (axis) {
    case 0: cm->SetX(scale * deg * 0.017453292f); return;
    case 1: cm->SetY(scale * deg * 0.017453292f); return;
    case 2: cm->SetZ(scale * deg * 0.017453292f); return;
    case 3: cm->SetRotationAtLeast2(&fx, scale * deg * 0.017453292f); return;
    }
}

// ================================================================ WinScrollbar / IWinScrollbar

// @ 0x980fa0
void WinScrollbar::UpdateAndSync() {
    VSLOT(void(__thiscall*)(void*, int), this, 0x94)(this, 1);
    ((XWin*)this)->SerUpdate();
}

// @ 0x981000
void IWinScrollbar::SetOrientation(int o) {
    if (o == orientation) return;
    orientation = o;
    WinScrollbar* w = win();
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
}

// @ 0x981030
void IWinScrollbar::SetFlags(uint32_t mask, char on) {
    if (on) flags |= (int)mask;
    else flags &= ~(int)mask;
}

// @ 0x981060
void IWinScrollbar::SetDrawable(void* d) {
    void* iwv = (char*)this - 0x208;
    VSLOT(void(__thiscall*)(void*, void*), iwv, 0xb0)(iwv, d);
    WinScrollbar* w = (WinScrollbar*)((char*)this - 0x20c);
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
}

// @ 0x9810a0
void IWinScrollbar::SetValue(int v, char notify) {
    int t = maxVal - visibleRange;
    if (v > t) v = t;
    if (v < minVal) v = minVal;
    int old = current;
    if (v == old) return;
    current = v;
    if (notify) {
        SBMsg m;
        WinScrollbar* w = (WinScrollbar*)((char*)this - 0x20c);
        m.type = 0x8ef0c8dd;
        m.src = w->id1 ? w->id1 : w->id0;
        m.from = old;
        void* iwv = (char*)this - 0x208;
        typedef void (__thiscall *SFn)(void*, SBMsg*);
        SFn fn = VSLOT(SFn, iwv, 0x114);
        m.to = v;
        fn(iwv, &m);
    }
    void* w2 = (char*)this - 0x20c;
    void** vt = *(void***)w2;
    void (__thiscall *fn)(void*, int) = (void(__thiscall*)(void*, int))vt[0x94 / 4];
    fn(w2, 1);
}

// @ 0x981130
void IWinScrollbar::SetMinimumValue(int v, int notify) {
    if (minVal == v) return;
    int old = current;
    minVal = v;
    VSLOT(void(__thiscall*)(void*, int, int), this, 0x24)(this, old, notify);
    WinScrollbar* w = win();
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
}

// @ 0x981170
void IWinScrollbar::SetMaximumValue(int v, int notify) {
    if (maxVal == v) return;
    int old = current;
    maxVal = v;
    VSLOT(void(__thiscall*)(void*, int, int), this, 0x24)(this, old, notify);
    WinScrollbar* w = win();
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
}

// @ 0x9811b0
void IWinScrollbar::SetVisibleRange(int v, int notify) {
    if (visibleRange == v) return;
    visibleRange = v;
    int d = v - pageOverlap;
    pageDelta = d;
    if (d < 1) pageDelta = 1;
    int old = current;
    VSLOT(void(__thiscall*)(void*, int, int), this, 0x24)(this, old, notify);
    WinScrollbar* w = win();
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
}

// @ 0x981200
void IWinScrollbar::SetPageOverlap(int v) {
    int d = visibleRange - v;
    pageOverlap = v;
    pageDelta = d;
    if (d < 1) pageDelta = 1;
}

// @ 0x981220
bool WinScrollbar::OnMouseDown(float x, float y, int a3, int button) {
    (void)a3;
    if (button != 8) return false;
    VSLOT(void(__thiscall*)(void*, int), this, 0x90)(this, 0);
    char c = VSLOT(char(__thiscall*)(void*, float, float), this, 0xa0)(this, x, y);
    sb.selComp = (uint8_t)c;
    if (c == -1) return true;
    void* mgr = winMgr;
    void* iwv = (char*)this + 4;
    if (VSLOT(void*(__thiscall*)(void*, int), mgr, 0x54)(mgr, 1) != iwv)
        VSLOT(void(__thiscall*)(void*, int, void*), mgr, 0x58)(mgr, 1, iwv);
    switch (sb.selComp) {
    case 1:
        if (!(sb.flags & 1))
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current - sb.arrowDelta, 1);
        break;
    case 2:
        VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current - sb.pageDelta, 1);
        break;
    case 3:
        if (sb.orientation == 1)
            sb.thumbOffset = (x - sb.compArea[4][0]) + sb.compArea[6][0];
        else
            sb.thumbOffset = (y - sb.compArea[4][1]) + sb.compArea[6][1];
        break;
    case 5:
        VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current + sb.pageDelta, 1);
        break;
    case 6:
        if (!(sb.flags & 1))
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current + sb.arrowDelta, 1);
        break;
    }
    VSLOT(void(__thiscall*)(void*, int), this, 0x90)(this, 1);
    VSLOT(void(__thiscall*)(void*), (char*)this + 4, 0x90)((char*)this + 4);
    return true;
}

// @ 0x981430
bool WinScrollbar::OnMouseUp(float x, float y, int a3, int flags) {
    (void)a3;
    if (flags & 8) return false;
    void* iwv = this ? (char*)this + 4 : 0;
    void* mgr = winMgr;
    if (VSLOT(void*(__thiscall*)(void*, int), mgr, 0x54)(mgr, 1) == iwv)
        VSLOT(void(__thiscall*)(void*, int, void*), mgr, 0x5c)(mgr, 1, (char*)this + 4);
    sb.selComp = 0xff;
    sb.hlComp = (uint8_t)VSLOT(char(__thiscall*)(void*, float, float), this, 0xa0)(this, x, y);
    VSLOT(void(__thiscall*)(void*, int), this, 0x90)(this, 0);
    VSLOT(void(__thiscall*)(void*), (char*)this + 4, 0x90)((char*)this + 4);
    return true;
}

// @ 0x9814c0
bool WinScrollbar::OnFocusChange(int state, void* w) {
    if (state == 1) {
        void* iwv = this ? (char*)this + 4 : 0;
        if (w != iwv && sb.hlComp != 0xff) {
            sb.hlComp = 0xff;
            VSLOT(void(__thiscall*)(void*), iwv, 0x90)(iwv);
        }
    }
    return true;
}

// @ 0x981500
bool WinScrollbar::OnTick() {
    VSLOT(void(__thiscall*)(void*), this, 0x98)(this);
    int64_t* tstamp = (int64_t*)((char*)this + 0x248);
    if (*tstamp == 0) return true;
    if ((sb.flags & 1) && (sb.selComp == 1 || sb.selComp == 6)) {
        int64_t e = ((XStopwatch*)((char*)this + 0x248))->GetElapsedFloat();
        float f = (float)(int)e * *(float*)((char*)this + 0x25c);
        float arrow = (float)sb.arrowDelta;
        float v = arrow * f * 0.001f;
        if (1.0f > v) return true;
        if (sb.selComp != sb.hlComp) goto notify;
        if (sb.selComp == 1)
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current - (int)v, 1);
        else
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, (int)v + sb.current, 1);
    } else {
        int64_t e = ((XStopwatch*)((char*)this + 0x248))->GetElapsed();
        if ((int)(e >> 32) <= 0 && (uint32_t)e <= 0x96) return true;
        if (sb.selComp != sb.hlComp) goto notify;
        switch (sb.selComp) {
        case 1:
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current - sb.arrowDelta, 1);
            break;
        case 2:
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current - sb.pageDelta, 1);
            break;
        case 5:
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current + sb.pageDelta, 1);
            break;
        case 6:
            VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.current + sb.arrowDelta, 1);
            break;
        }
    }
notify:
    VSLOT(void(__thiscall*)(void*, int), this, 0x90)(this, 1);
    return true;
}

// ================================================================ window-base helpers

// @ 0x9816c0  (this = window+4)
void IWinSB2::InvalidateLayoutNoArgs() {
    void* w = (char*)this - 4;
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
    ((XWin*)this)->InvalidateLayout();
}

// @ 0x9816e0
int WinScrollbar::IsActive() {
    if (sb.refresh != 0) return 1;
    if ((*(int*)((char*)this + 0x248) | *(int*)((char*)this + 0x24c)) != 0) return 1;
    return 0;
}

// @ 0x981700
void WinScrollbar::SetRefreshFlag(char on) {
    char old = 0;
    if (*(int*)((char*)this + 0x248) | *(int*)((char*)this + 0x24c)) old = 1;
    XStopwatch* sw = (XStopwatch*)((char*)this + 0x248);
    if (on) sw->Restart();
    else ((XPropList*)sw)->SetBoolProperty();
    char now = 0;
    if (*(int*)((char*)this + 0x248) | *(int*)((char*)this + 0x24c)) now = 1;
    if (old != now) {
        char active = (char)VSLOT(int(__thiscall*)(void*), this, 0x8c)(this);
        VSLOT(void(__thiscall*)(void*, int, int), (char*)this + 4, 0x7c)((char*)this + 4, 8, (uint8_t)active);
    }
}

// @ 0x981770
void WinScrollbar::SetRefresh(char on) {
    if (sb.refresh == (uint8_t)on) return;
    sb.refresh = (uint8_t)on;
    void* iwv = (char*)this + 4;
    char active = (char)VSLOT(int(__thiscall*)(void*), this, 0x8c)(this);
    VSLOT(void(__thiscall*)(void*, int, int), iwv, 0x7c)(iwv, 8, (uint8_t)active);
}

// ================================================================ ScrollbarDrawable

// @ 0x981800
bool ScrollbarDrawable::GetNaturalSize(float* out, int unused, int idx) {
    (void)unused;
    if (images[idx] != 0) {
        out[0] = (float)images[idx]->w;
        out[1] = (float)images[idx]->h;
        if (idx == 1 || idx == 6 || idx == 3) out[0] = out[0] * 0.25f;
        return true;
    }
    return false;
}

// @ 0x981860
void IScrollbarDrawable::SetComponentImage(uint32_t idx, Image* p) {
    if (idx < 7 && images[idx] != p) {
        if (p) p->AddRef();
        if (images[idx]) images[idx]->Release();
        images[idx] = p;
    }
}

// --- equivalence checker address annotations
namespace __equiv_ann {
}
