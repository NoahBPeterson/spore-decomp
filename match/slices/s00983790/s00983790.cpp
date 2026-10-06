// UTFWinControls: WinScrollbar ctor/factory, WinSlider, SliderDrawable (0x983790-0x984880).
// Window is an offset-faithful stub (vtable calls go through slot casts).
// WinSlider = Window (0x20c bytes) + IWinSlider subobject at +0x20c; IWinSlider methods get
// `this` = window + 0x20c (the IWindow subobject is at this-0x208).
#include "types.h"
#include <xmmintrin.h>

inline void* operator new(size_t, void* p) { return p; }

typedef void (__thiscall *VFn0)(void*);
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])

extern void* vtbl_WinScrollbar[];
extern void* vtbl_WinScrollbar_IWindow[];
extern void* vtbl_IWinScrollbar_base[];
extern void* vtbl_IWinScrollbar[];
extern void* vtbl_Resource_Async[];
extern void* vtbl_ScrollbarDrawable[];
extern void* vtbl_ScrollbarDrawable_1[];
extern void* vtbl_ScrollbarDrawable_3[];

void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0 (cdecl)

namespace EA {
struct Stopwatch {
    uint32_t pad[6];
    void Init(int a, int b);                // 0093A560 (ctor)
    void SetUnits(int units);               // 0093A1A0
};
}

namespace EA { namespace UTFWinControls {

struct ScrollWinPrim {
    virtual void p00();
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual void p24();
    virtual void p28();
    virtual void p2c();
    virtual void p30();
    virtual void p34();
    virtual void p38();
    virtual void p3c();
    virtual void p40();
    virtual void p44();
    virtual void p48();
    virtual void p4c();
    virtual void p50();
    virtual void p54();
    virtual void p58();
    virtual void p5c();
    virtual void p60();
    virtual void p64();
    virtual void p68();
    virtual void p6c();
    virtual void p70();
    virtual void p74();
    virtual void p78();
    virtual void p7c();
    virtual void p80();
    virtual void p84();
    virtual void p88();
    virtual char GetFlags();                                    // 0x8c
};
struct ScrollWinIWin {
    virtual void w00();
    virtual void w04();
    virtual void w08();
    virtual void w0c();
    virtual void w10();
    virtual void w14();
    virtual void w18();
    virtual void w1c();
    virtual void w20();
    virtual void w24();
    virtual void w28();
    virtual void w2c();
    virtual void w30();
    virtual void w34();
    virtual void w38();
    virtual void w3c();
    virtual void w40();
    virtual void w44();
    virtual void w48();
    virtual void w4c();
    virtual void w50();
    virtual void w54();
    virtual void w58();
    virtual void w5c();
    virtual void w60();
    virtual void w64();
    virtual void w68();
    virtual void w6c();
    virtual void w70();
    virtual void w74();
    virtual void w78();
    virtual void Notify(int what, int value);                   // 0x7c
};

struct Window : ScrollWinPrim, ScrollWinIWin {
    uint32_t p08[(0x20c - 8) / 4];
    Window();                           // 00962A10
};

// ---------------------------------------------------------------- scrollbar
struct IWinScrollbar {
    virtual void i00();
    virtual void i04();
    virtual void i08();
    virtual void i0c();
    virtual void i10();
    virtual void v14(int a);                                    // 0x14
    virtual void i18();
    virtual void i1c();
    virtual void i20();
    virtual void v24(int a, int b);                             // 0x24
    virtual void i28();
    virtual void v2c(int a, int b);                             // 0x2c
    virtual void i30();
    virtual void v34(int a, int b);                             // 0x34
    virtual void i38();
    virtual void v3c(int a, int b);                             // 0x3c
    virtual void i40();
    virtual void i44();
    virtual void i48();
    virtual void i4c();
    virtual void i50();
    virtual void i54();
    virtual void i58();
    virtual void SetDrawable(void* d);                          // 0x5c
    int f210, f214, minThumbSize;
    int orientation;
    int hl, sel;
    int f228, f22c, f230;
    uint8_t hlComp, selComp;            // 0x234, 0x235
    uint8_t pad236[2];
    float thumbOffset;                  // 0x238
    uint8_t refresh;                    // 0x23c
    uint8_t pad23d[3];
    int f240, f244;
    IWinScrollbar() { hlComp = 0xff; selComp = 0xff; }
};

struct WinScrollbar : Window, IWinScrollbar {
    EA::Stopwatch timer;                // 0x248
    WinScrollbar();                     // 00983790
    static IWinScrollbar* CreateDefault(int a1, int a2, int a3, int a4);   // 009839B0
};

struct AsyncBase {
    void* vt4; int f8; void* vtc;
    AsyncBase() { vt4 = vtbl_Resource_Async; f8 = 0; vtc = vtbl_Resource_Async; }
};
struct ObjHead { void* vt; };
struct ScrollbarDrawable : ObjHead, AsyncBase {
    int f[7];
    ScrollbarDrawable() {               // 009838A0
        vt = vtbl_ScrollbarDrawable;
        vt4 = vtbl_ScrollbarDrawable_1;
        vtc = vtbl_ScrollbarDrawable_3;
        f[0] = 0; f[1] = 0; f[2] = 0; f[3] = 0; f[4] = 0; f[5] = 0; f[6] = 0;
    }
};

// @ 0x983790
WinScrollbar::WinScrollbar() : Window(), IWinScrollbar() {
    f210 = 0; f214 = 0;
    minThumbSize = 0x100; orientation = 0x10;
    hl = 1; sel = 1;
    f228 = 0xf; f22c = 8; f230 = 2;
    thumbOffset = 0.0f;
    refresh = 0;
    f240 = 0;
    timer.Init(0, 0);
    timer.SetUnits(4);
    if (refresh != 1) {
        char (__thiscall* getFlags)(void*) = VSLOT(char(__thiscall*)(void*), (ScrollWinPrim*)this, 0x8c);
        refresh = 1;
        void** ivt = *(void***)(ScrollWinIWin*)this;
        char c = getFlags((ScrollWinPrim*)this);
        ((void(__thiscall*)(void*, int, int))ivt[0x7c / 4])((ScrollWinIWin*)this, 8, (uint8_t)c);
    }
}

// @ 0x9838a0  (standalone constructor; the in-class ctor is inlined into the factories)
__declspec(noinline) ScrollbarDrawable* ConstructScrollbarDrawable(ScrollbarDrawable* self) {
    self->vt4 = vtbl_Resource_Async;
    self->f8 = 0;
    self->vtc = vtbl_Resource_Async;
    self->vt = vtbl_ScrollbarDrawable;
    self->vt4 = vtbl_ScrollbarDrawable_1;
    self->vtc = vtbl_ScrollbarDrawable_3;
    self->f[0] = 0; self->f[1] = 0; self->f[2] = 0; self->f[3] = 0; self->f[4] = 0; self->f[5] = 0; self->f[6] = 0;
    return self;
}

struct BasicFactory_ScrollbarDrawable {
    ScrollbarDrawable* CreateInstance(int unused, void* alloc);
};

// @ 0x983940
ScrollbarDrawable* BasicFactory_ScrollbarDrawable::CreateInstance(int unused, void* alloc) {
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x2c, 4, "UTFWin/EA::UTFWinControls::ScrollbarDrawable", alloc);
    if (mem) return new (mem) ScrollbarDrawable();
    return 0;
}

// @ 0x9839b0
IWinScrollbar* WinScrollbar::CreateDefault(int a1, int a2, int a3, int a4) {
    void* mem = AllocAligned(0x2d0, 8, "UTFWin/WinScrollbar", GetDefaultAllocator());
    if (!mem) return 0;
    WinScrollbar* w = new (mem) WinScrollbar();
    if (!w) return 0;
    IWinScrollbar* s = w;
    if (s) {
        s->v14(a1);
        s->v2c(a2, 1);
        s->v34(a3, 1);
        s->v3c(a4, 1);
        s->v24(a2, 0);
        void* dmem = AllocAligned(0x2c, 4, "UTFWin/ScrollbarDrawable", GetDefaultAllocator());
        ScrollbarDrawable* d = 0;
        if (dmem) d = new (dmem) ScrollbarDrawable();
        s->SetDrawable(d);
    }
    return s;
}

// ---------------------------------------------------------------- slider
// Real virtual classes: slot placeholders (sXX = byte offset of the slot) keep the vtable layout.
struct SliderMsg {
    uint32_t w0, w1;
    uint32_t type, src;
    int from, to;
    uint32_t w6;
};

struct SliderWinMgr {
    virtual void m00();
    virtual void m04();
    virtual void m08();
    virtual void m0c();
    virtual void m10();
    virtual void m14();
    virtual void m18();
    virtual void m1c();
    virtual void m20();
    virtual void m24();
    virtual void m28();
    virtual void m2c();
    virtual void m30();
    virtual void m34();
    virtual void m38();
    virtual void m3c();
    virtual void m40();
    virtual void m44();
    virtual void m48();
    virtual void m4c();
    virtual void m50();
    virtual void* GetCapture(int which);                        // 0x54
    virtual void SetCapture(int which, void* w);                // 0x58
    virtual void ReleaseCapture(int which, void* w);            // 0x5c
};

struct SliderPrim {
    virtual void p00();
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual void p24();
    virtual void p28();
    virtual void p2c();
    virtual void p30();
    virtual void p34();
    virtual void p38();
    virtual void p3c();
    virtual void p40();
    virtual void p44();
    virtual void p48();
    virtual void p4c();
    virtual void p50();
    virtual void p54();
    virtual void p58();
    virtual void p5c();
    virtual void p60();
    virtual void p64();
    virtual void p68();
    virtual void p6c();
    virtual void p70();
    virtual void p74();
    virtual void p78();
    virtual void p7c();
    virtual void p80();
    virtual void p84();
    virtual void p88();
    virtual void Layout();                                      // 0x8c
    virtual void OnPaintPart(int g, int part);                  // 0x90
    virtual int PickComponent(float x, float y);                // 0x94
    virtual int ComputeValueAtCursor(float x, float y);         // 0x98
};

struct SliderIWin {
    virtual void w00();
    virtual void w04();
    virtual void w08();
    virtual void w0c();
    virtual void w10();
    virtual void w14();
    virtual void w18();
    virtual void w1c();
    virtual uint32_t GetId();                                   // 0x20
    virtual void w24();
    virtual uint8_t GetFlags();                                 // 0x28
    virtual void w2c();
    virtual void w30();
    virtual void w34();
    virtual float* GetArea();                                   // 0x38
    virtual void w3c();
    virtual void w40();
    virtual void w44();
    virtual void w48();
    virtual void w4c();
    virtual void w50();
    virtual void w54();
    virtual void w58();
    virtual void w5c();
    virtual void w60();
    virtual void w64();
    virtual void w68();
    virtual void w6c();
    virtual void w70();
    virtual void w74();
    virtual void w78();
    virtual void w7c();
    virtual void w80();
    virtual void w84();
    virtual void w88();
    virtual void w8c();
    virtual void Invalidate();                                  // 0x90
    virtual void w94();
    virtual void w98();
    virtual void w9c();
    virtual void wa0();
    virtual void wa4();
    virtual void wa8();
    virtual void wac();
    virtual void SetDrawable(void* d);                          // 0xb0
    virtual void wb4();
    virtual void wb8();
    virtual void wbc();
    virtual void wc0();
    virtual void wc4();
    virtual void wc8();
    virtual void wcc();
    virtual void wd0();
    virtual void wd4();
    virtual void wd8();
    virtual void wdc();
    virtual void we0();
    virtual void we4();
    virtual void we8();
    virtual void wec();
    virtual void wf0();
    virtual void wf4();
    virtual void wf8();
    virtual void wfc();
    virtual char IsDisabled(int which);                         // 0x100
    virtual void w104();
    virtual void w108();
    virtual void w10c();
    virtual void w110();
    virtual void SendMessage(SliderMsg* m);                     // 0x114
};

struct SliderDrawableObj {
    virtual void d00();
    virtual void d04();
    virtual void d08();
    virtual void* QueryInterface(uint32_t id);                  // 0x0c
    virtual void Render(int g, float* rect, void* state);       // 0x10
    virtual void d14();
    virtual char GetSize(float* out, int mask, int idx);        // 0x18
};

struct SliderData : SliderPrim, SliderIWin {
    uint32_t p08[(0x34 - 8) / 4];
    SliderWinMgr* mgr;                  // +0x34
    uint32_t p38[(0x80 - 0x38) / 4];
    int id0, id1;                       // +0x80, +0x84
    float area[4];                      // +0x88
    uint32_t p98[(0x1d8 - 0x98) / 4];
    uint32_t state0, state1;            // +0x1d8, +0x1dc
    SliderDrawableObj* drawable;        // +0x1e0
    uint32_t p1e4[(0x20c - 0x1e4) / 4];
    void OnPaintBase(int g);            // 00960310
};

struct IWinSlider {
    virtual void i00();
    virtual void i04();
    virtual void i08();
    virtual void i0c();
    virtual void i10();
    virtual void i14();
    virtual void i18();
    virtual void SetValue(int v, char notify);                  // 0x1c
    int dragStart;                      // +4  (0x210)
    int cur, minV, maxV;                // +8, +0xc, +0x10
    int orient;                         // +0x14 (0x220)
    uint8_t hi, sel, dirty, pad;        // +0x18..0x1b (0x224..0x227)
    float rect[3][4];                   // +0x1c (0x228)
    SliderData* win() { return (SliderData*)((char*)this - 0x20c); }
    SliderIWin* iwin() { return (SliderIWin*)((char*)this - 0x208); }
    void SetOrientation(int o);                     // 00983B80
    void SetDrawable(void* d);                      // 00983BA0
    void SetMinimumValue(int v, int notify);        // 00983C60
    void SetMaximumValue(int v, int notify);        // 00983C90
    void* GetDrawable();                            // 009842C0
};

struct WinSlider : SliderData, IWinSlider {
    void SetHighlighted(uint8_t v) {
        if (hi != v) {
            hi = v;
            Invalidate();
        }
    }
    bool OnMouseDown(float x, float y, int a3, int button);     // 00983CC0
    bool OnMouseUp(float x, float y, int a3, int flags);        // 00983DD0
    bool OnMouseMove(float x, float y, int flags);              // 00983EA0
    bool OnFocusChange(int state, void* w);                     // 00983F50
    bool GetPreferredSize(int flag, float* out);                // 00984150
    bool OnRebuild(int g);                                      // 009842E0
    void RenderComponent(int g, uint32_t idx);                  // 00984340
    virtual int PickComponent(float x, float y);                // 00984410
    void Refresh();                                             // 009844C0
    virtual int ComputeValueAtCursor(float x, float y);         // 00984880
};

// @ 0x983b80
void IWinSlider::SetOrientation(int o) {
    if (o != orient) {
        orient = o;
        dirty = 1;
    }
}

// @ 0x983ba0
void IWinSlider::SetDrawable(void* d) {
    void* r;
    if (d) r = VSLOT(void*(__thiscall*)(void*), d, 0x10)(d);
    else r = 0;
    iwin()->SetDrawable(r);
    dirty = 1;
}

// @ 0x983be0
void IWinSlider::SetValue(int v, char notify) {
    int old = cur;
    if (v > maxV) v = maxV;
    if (v < minV) v = minV;
    if (v != old) {
        cur = v;
        if (notify) {
            SliderMsg m;
            m.type = 0xef00a884;
            m.src = win()->id1 ? win()->id1 : win()->id0;
            m.from = old;
            m.to = v;
            iwin()->SendMessage(&m);
        }
        dirty = 1;
    }
}

// @ 0x983c60
void IWinSlider::SetMinimumValue(int v, int notify) {
    if (minV != v) {
        int c = cur;
        minV = v;
        SetValue(c, notify);
        dirty = 1;
    }
}

// @ 0x983c90
void IWinSlider::SetMaximumValue(int v, int notify) {
    if (maxV != v) {
        int c = cur;
        maxV = v;
        SetValue(c, notify);
        dirty = 1;
    }
}

// @ 0x983cc0
bool WinSlider::OnMouseDown(float x, float y, int a3, int button) {
    if (button == 8) {
        char c = PickComponent(x, y);
        sel = c;
        if (c != -1) {
            dragStart = cur;
            SliderMsg m;
            m.type = 0x7a4489c;
            m.src = id1 ? id1 : id0;
            m.from = cur;
            m.to = cur;
            SliderIWin* iw = (SliderIWin*)((char*)this + 4);
            SendMessage(&m);
            if (mgr->GetCapture(1) != iw) mgr->SetCapture(1, iw);
            switch (sel) {
            case 2: {
                IWinSlider* s = this;
                s->SetValue(ComputeValueAtCursor(x, y), 1);
            }
            }
            Invalidate();
        }
        return true;
    }
    return false;
}

// @ 0x983dd0
bool WinSlider::OnMouseUp(float x, float y, int a3, int flags) {
    if (!(flags & 8) && sel != 0xff) {
        SliderIWin* iw = (SliderIWin*)((char*)this + 4);
        if (mgr->GetCapture(1) == iw) mgr->ReleaseCapture(1, iw);
        sel = 0xff;
        hi = PickComponent(x, y);
        Invalidate();
        SliderMsg m;
        m.type = 0x7a44749;
        m.src = id1 ? id1 : id0;
        m.from = dragStart;
        m.to = cur;
        SendMessage(&m);
        return true;
    }
    return false;
}

// @ 0x983ea0
bool WinSlider::OnMouseMove(float x, float y, int flags) {
    SliderIWin* iw = this;
    if (mgr->GetCapture(1) == iw) {
        switch (sel) {
        case 1: {
            IWinSlider* s = this;
            s->SetValue(ComputeValueAtCursor(x, y), 1);
            return true;
        }
        }
    } else {
        uint8_t h = PickComponent(x, y);
        if (hi != h) {
            hi = h;
            Invalidate();
        }
    }
    return true;
}

// @ 0x983f50
bool WinSlider::OnFocusChange(int state, void* w) {
    if (state == 1) {
        SliderIWin* iw = this;
        if (w != iw && hi != 0xff) {
            hi = 0xff;
            Invalidate();
        }
    }
    return true;
}

// @ 0x9842c0
void* IWinSlider::GetDrawable() {
    SliderDrawableObj* d = win()->drawable;
    if (d) return d->QueryInterface(0x4f00a9eb);
    return 0;
}

// ---------------------------------------------------------------- SliderDrawable
struct Image {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[6];
    int w, h;                           // +0x1c, +0x20
};

struct ISliderDrawable {
    void* vt;
    Image* img[3];
    void SetComponentImage(uint32_t idx, Image* p);     // 00984040
};

struct SliderDrawable {
    void* vt;
    uint32_t p04[3];
    Image* img[3];                      // +0x10
    bool GetNaturalSize(float* out, int unused, int idx);   // 00983FF0
};

// @ 0x983ff0
bool SliderDrawable::GetNaturalSize(float* out, int unused, int idx) {
    if (img[idx]) {
        out[0] = (float)img[idx]->w;
        out[1] = (float)img[idx]->h;
        if (idx == 1) out[0] = out[0] * 0.25f;
        return true;
    }
    return false;
}

// @ 0x984040
void ISliderDrawable::SetComponentImage(uint32_t idx, Image* p) {
    if (idx < 3 && img[idx] != p) {
        if (p) p->AddRef();
        if (img[idx]) img[idx]->Release();
        img[idx] = p;
    }
}

template <class T> inline const T& smax(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& smin(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x984150
bool WinSlider::GetPreferredSize(int flag, float* out) {
    Layout();
    if (flag) return false;
    float w = area[2] - area[0];
    out[0] = w;
    float h = area[3] - area[1];
    out[1] = h;
    if (!drawable) return false;
    if (orient == 1) {
        h = 0;
        if (h < rect[1][3] - rect[1][1]) h = rect[1][3] - rect[1][1];
        if (h < rect[2][3] - rect[2][1]) h = rect[2][3] - rect[2][1];
    } else {
        w = 0;
        if (w < rect[1][2] - rect[1][0]) w = rect[1][2] - rect[1][0];
        if (w < rect[2][2] - rect[2][0]) w = rect[2][2] - rect[2][0];
    }
    out[0] = smax(14.0f, w);
    out[1] = smax(14.0f, h);
    return true;
}

// @ 0x9842e0
bool WinSlider::OnRebuild(int g) {
    if (drawable) {
        OnPaintPart(g, 0);
        OnPaintPart(g, 2);
        OnPaintPart(g, 1);
        return true;
    }
    OnPaintBase(g);
    return true;
}

struct RenderState {
    uint32_t flags, idx, s1, s0;
};

// @ 0x984340
void WinSlider::RenderComponent(int g, uint32_t idx) {
    if (drawable) {
        RenderState st;
        st.s1 = state1;
        st.flags = 0;
        st.idx = idx;
        st.s0 = state0;
        if (hi == idx && sel == idx) st.flags = 3;
        else if (hi == idx) st.flags = 2;
        SliderIWin* iw = this;
        uint8_t wf = iw->GetFlags();
        if (!(wf & 2)) st.flags = 1;
        if (orient == 2) st.flags |= 0x80;
        if (hi == idx) st.flags |= 2;
        drawable->Render(g, &rect[idx][0], &st);
    }
}

// @ 0x984410
int WinSlider::PickComponent(float x, float y) {
    if (x >= rect[1][0] && y >= rect[1][1] && x < rect[1][2] && y < rect[1][3]) return 1;
    if (x >= rect[2][0] && y >= rect[2][1] && x < rect[2][2] && y < rect[2][3]) return 2;
    if (x >= rect[0][0] && y >= rect[0][1] && x < rect[0][2] && y < rect[0][3]) return 0;
    return -1;
}

// @ 0x9844c0
void WinSlider::Refresh() {
    void* iface = 0;
    if (drawable) iface = drawable->QueryInterface(0x4f00a9eb);
    if (dirty && iface) {
        dirty = 0;
        if (cur > maxV) cur = maxV;
        if (cur < minV) cur = minV;
        float sz[3][2];
        for (uint32_t i = 0; i < 3; i++) {
            float s[2];
            char ok = drawable->GetSize(s, (orient != 2) - 1 & 0x80, i);
            if (!ok) {
                SliderIWin* iw = this;
                float* r = iw->GetArea();
                if (orient == 1) {
                    float a = (r[2] - r[0]) * 0.5f;
                    float b = r[3] - r[1];
                    s[0] = smin(a, b);
                    s[1] = r[3] - r[1];
                } else {
                    s[0] = r[2] - r[0];
                    float a = (r[3] - r[1]) * 0.5f;
                    float b = r[2] - r[0];
                    s[1] = smin(a, b);
                }
            }
            sz[i][0] = s[0];
            sz[i][1] = s[1];
        }
        if (orient == 1) {
            rect[0][1] = ((area[3] - area[1]) - sz[0][1]) * 0.5f;
            rect[0][3] = sz[0][1] + rect[0][1];
            rect[1][1] = ((area[3] - area[1]) - sz[1][1]) * 0.5f;
            rect[1][3] = rect[1][1] + sz[1][1];
            rect[2][1] = ((area[3] - area[1]) - sz[2][1]) * 0.5f;
            rect[2][3] = sz[2][1] + rect[2][1];
        } else {
            rect[0][0] = ((area[2] - area[0]) - sz[0][0]) * 0.5f;
            rect[0][2] = sz[0][0] + rect[0][0];
            rect[1][0] = ((area[2] - area[0]) - sz[1][0]) * 0.5f;
            rect[1][2] = rect[1][0] + sz[1][0];
            rect[2][0] = ((area[2] - area[0]) - sz[2][0]) * 0.5f;
            rect[2][2] = sz[2][0] + rect[2][0];
        }
        int o = orient;
        if (o == 1) {
            rect[2][0] = 0;
            rect[2][2] = area[2] - area[0];
        } else {
            rect[2][1] = 0;
            rect[2][3] = area[3] - area[1];
        }
        float len;
        if (o == 1) len = (area[2] - area[0]) - sz[1][0];
        else len = (area[3] - area[1]) - sz[1][1];
        float frac = (float)(cur - minV) / (float)(maxV - minV);
        float pos = frac * len;
        if (o == 1) {
            pos = pos + rect[2][0];
            rect[1][0] = pos;
            rect[1][2] = pos + sz[1][0];
        } else {
            pos = (len - pos) + rect[2][1];
            rect[1][1] = pos;
            rect[1][3] = pos + sz[1][1];
        }
        SliderIWin* iw = this;
        iw->Invalidate();
    }
}

// @ 0x984880
int WinSlider::ComputeValueAtCursor(float x, float y) {
    Layout();
    float pos, range;
    int o = orient;
    if (o == 1) {
        float half = (rect[1][2] - rect[1][0]) * 0.5f;
        pos = x - half;
        range = (rect[2][2] - rect[2][0]) - (rect[1][2] - rect[1][0]);
    } else {
        float half = (rect[1][3] - rect[1][1]) * 0.5f;
        pos = y - half;
        range = (rect[2][3] - rect[2][1]) - (rect[1][3] - rect[1][1]);
    }
    if (0.0f > pos) pos = 0.0f;
    if (pos > range) pos = range;
    float frac = pos / range;
    int r;
    if (o == 1) {
        x = (float)(maxV - minV) * frac;
        __asm { cvtss2si eax, x }
        __asm { mov r, eax }
        return minV + r;
    }
    x = (float)(maxV - minV) * frac;
    __asm { cvtss2si eax, x }
    __asm { mov r, eax }
    return maxV - r;
}

}}  // namespace
