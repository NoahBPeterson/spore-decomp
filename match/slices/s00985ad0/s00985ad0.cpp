// Slice 61: EA::UTFWinControls WinSlider ctor, SliderDrawable factory, and the WinSpinner
// window whose IWinSpinner interface subobject sits at window+0x20c  (0x985ad0-0x9865c0).
//
// The window base is polymorphic so MSVC places the secondary IWindow subobject at +4 and the
// IWinSpinner subobject at +0x20c (window size 0x27c):
//   +0x000 primary vptr, +0x004 IWindow vptr, +0x034 winMgr, +0x080 id0, +0x084 id1,
//   +0x1d8 state0, +0x1dc state1, +0x1e0 drawable, +0x20c IWinSpinner subobject.
// IWinSpinner (this == window+0x20c): +0x04 current, +0x08 minVal, +0x0c maxVal,
//   +0x10 deltaPerTick, +0x14 tickPeriod, +0x18 hlComp, +0x19 selComp, +0x1a f1a,
//   +0x1c mode, +0x20 refresh, +0x24 stopwatch (0x18), +0x3c compDrawable, +0x40 compArea[3][4].
#include "types.h"

inline void* operator new(size_t, void* p) { return p; }

typedef void (__thiscall *VFn0)(void*);
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])

void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0 (cdecl)

namespace EA {
#pragma pack(push, 4)
class Stopwatch { public:
    uint64_t mnStartTime;                   // +0x00 (tested as one 64-bit value)
    uint64_t mnTotalElapsedTime;            // +0x08
    int      mnUnits;                       // +0x10
    float    mfCyclesToUnitsCoefficient;    // +0x14
    int64_t GetElapsedTime();               // 0093A5E0
    void    Restart();                      // 00571E80
    void    SetBoolProperty();              // 0093A2E0
};
#pragma pack(pop)
}

namespace EA { namespace UTFWinControls {

// ---------------------------------------------------------------- vtables (relocated)
extern void* vtbl_Resource_Async[];
extern void* vtbl_SliderDrawable[];         // 0x01444c90
extern void* vtbl_SliderDrawable_1[];       // 0x01444c78
extern void* vtbl_SliderDrawable_3[];       // 0x01444c60

class WinSpinner;
struct SpinnerPrim;
struct SpinnerIWin;

struct Image {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[6];
    int w, h;                               // +0x1c, +0x20
};

struct SpinnerMsg { uint32_t w0, w1, type, src; int from, to; uint32_t w6; };

struct SpinnerDrawableIf {
    virtual void d00();
    virtual void d04();
    virtual void d08();
    virtual void* QueryInterface(uint32_t id);          // 0x0c
    virtual void Render(int g, float* rect, void* state);   // 0x10
    virtual void d14();
    virtual char GetSize(float* out, int mask, int idx);    // 0x18
};

struct SpinnerWinMgr {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28(); virtual void m2c();
    virtual void m30(); virtual void m34(); virtual void m38(); virtual void m3c();
    virtual void m40(); virtual void m44(); virtual void m48(); virtual void m4c();
    virtual void m50();
    virtual void* GetCapture(int which);                // 0x54
    virtual void SetCapture(int which, void* w);        // 0x58
    virtual void ReleaseCapture(int which, void* w);    // 0x5c
};

// 39-slot primary window vtable stub (Refresh/RenderComponent/PickComponent at 0x8c/0x90/0x94)
struct SpinnerPrim {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28(); virtual void p2c();
    virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3c();
    virtual void p40(); virtual void p44(); virtual void p48(); virtual void p4c();
    virtual void p50(); virtual void p54(); virtual void p58(); virtual void p5c();
    virtual void p60(); virtual void p64(); virtual void p68(); virtual void p6c();
    virtual void p70(); virtual void p74(); virtual void p78(); virtual void p7c();
    virtual void p80(); virtual void p84(); virtual void p88();
    virtual void Refresh();                             // 0x8c
    virtual void RenderComponent(int g, uint32_t idx);  // 0x90
    virtual int  PickComponent(float x, float y);       // 0x94
    virtual void p98();
};

// IWindow secondary (at window+4): slots 0x00..0x114
struct SpinnerIWin {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24();
    virtual uint8_t GetFlags();                         // 0x28
    virtual void w2c(); virtual void w30(); virtual void w34();
    virtual void w38(); virtual void w3c(); virtual void w40(); virtual void w44();
    virtual void w48(); virtual void w4c(); virtual void w50(); virtual void w54();
    virtual void w58(); virtual void w5c(); virtual void w60(); virtual void w64();
    virtual void w68(); virtual void w6c(); virtual void w70(); virtual void w74();
    virtual void w78(); virtual void w7c(); virtual void w80(); virtual void w84();
    virtual void w88(); virtual void w8c();
    virtual void Invalidate();                          // 0x90
    virtual void w94(); virtual void w98(); virtual void w9c(); virtual void wa0();
    virtual void wa4(); virtual void wa8(); virtual void wac();
    virtual void SetDrawable(void* d);                  // 0xb0
    virtual void wb4(); virtual void wb8(); virtual void wbc(); virtual void wc0();
    virtual void wc4(); virtual void wc8(); virtual void wcc(); virtual void wd0();
    virtual void wd4(); virtual void wd8(); virtual void wdc(); virtual void we0();
    virtual void we4(); virtual void we8(); virtual void wec(); virtual void wf0();
    virtual void wf4(); virtual void wf8(); virtual void wfc();
    virtual void w100(); virtual void w104(); virtual void w108(); virtual void w10c();
    virtual void w110();
    virtual void SendMessage(SpinnerMsg* m);            // 0x114
    void SetFlag(uint32_t flag, uint8_t on);            // 00961760
};

struct Window : SpinnerPrim, SpinnerIWin {
    uint32_t p08[(0x34 - 0x08) / 4];        // +0x008
    SpinnerWinMgr* mgr;                     // +0x034
    uint32_t p38[(0x80 - 0x38) / 4];        // +0x038
    int id0, id1;                           // +0x080, +0x084
    float area[4];                          // +0x088
    uint32_t p98[(0x1d8 - 0x98) / 4];       // +0x098
    uint32_t state0, state1;                // +0x1d8, +0x1dc
    SpinnerDrawableIf* drawable;            // +0x1e0
    uint32_t p1e4[(0x20c - 0x1e4) / 4];     // +0x1e4
    Window();                               // 00962A10
    void OnPaintBase(int g);                // 00960310
};

// the interface subobject at window+0x20c
class IWinSpinner { public:
    virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
    virtual void i10();
    virtual void SetValue(int v, char notify);          // 0x14
    virtual void i18(); virtual void i1c(); virtual void i20(); virtual void i24();
    virtual void i28();
    virtual void SetMinimumValue(int v, int notify);    // 0x2c
    virtual void i30();
    virtual void SetMaximumValue(int v, int notify);    // 0x34
    virtual void i38();
    virtual void SetMode(int v);                        // 0x3c
    virtual void i40();
    virtual void SetComponentDrawable(Image* p);        // 0x44
    virtual void i48();
    virtual void SetDrawable(void* d);                  // 0x4c
    virtual void* GetDrawable();                        // 0x50
    int current;                            // +0x04
    int minVal;                             // +0x08
    int maxVal;                             // +0x0c
    int deltaPerTick;                       // +0x10
    int tickPeriod;                         // +0x14
    uint8_t hlComp;                         // +0x18
    uint8_t selComp;                        // +0x19
    uint8_t f1a;                            // +0x1a
    uint8_t pad1b;
    int mode;                               // +0x1c
    uint8_t refresh;                        // +0x20
    uint8_t pad21[3];
    EA::Stopwatch timer;                    // +0x24
    Image* compDrawable;                    // +0x3c
    float compArea[3][4];                   // +0x40
    IWinSpinner() { minVal = 0; maxVal = 0; }
    WinSpinner*   win() { return (WinSpinner*)((char*)this - 0x20c); }
    SpinnerIWin*  iw()  { return (SpinnerIWin*)((char*)this - 0x208); }
};

struct RenderState { uint32_t flags, idx, s1, s0; };

class WinSpinner : public Window, public IWinSpinner { public:
    bool OnMouseDown(float x, float y, int a3, int button);   // 00985e50
    bool OnMouseUp(float x, float y, int a3, int flags);      // 00985f30
    bool OnMouseMove(float x, float y, int flags);            // 00985fc0
    bool OnTick();                                            // 00986000
    bool GetPreferredSize(int flag, float* out);              // 009861a0
    bool OnRebuild(int g);                                    // 009863c0
    void Refresh();                                           // 00987590 (override, external)
    void RenderComponent(int g, uint32_t idx);                // 00986420 (override)
    int  PickComponent(float x, float y);                     // 00986510 (override)
};

class WinSlider : public Window, public IWinSpinner { public:
    WinSlider();                                              // 00985ad0
};

// ---------------------------------------------------------------- SliderDrawable
struct ObjHead { void* vt; };
struct AsyncBase {
    void* vt4; int f8; void* vtc;
    AsyncBase() { vt4 = vtbl_Resource_Async; f8 = 0; vtc = vtbl_Resource_Async; }
};
class SliderDrawable : public ObjHead, public AsyncBase { public:
    int f[3];                               // +0x10, +0x14, +0x18
    SliderDrawable() {
        vt = vtbl_SliderDrawable;
        vt4 = vtbl_SliderDrawable_1;
        vtc = vtbl_SliderDrawable_3;
        f[0] = 0; f[1] = 0; f[2] = 0;
    }
};
class BasicFactory_SliderDrawable { public:
    SliderDrawable* CreateInstance(int unused, void* alloc);  // 00985bd0
};

// ---------------------------------------------------------------- SpinnerDrawable
class SpinnerDrawable { public:
    void* vt;                               // +0x00
    uint32_t p04[3];                        // +0x04
    Image* images[3];                       // +0x10
    bool GetNaturalSize(float* out, int unused, int idx);     // 00986120
};

template <class T> inline const T& smax(const T& a, const T& b) { return (a > b) ? a : b; }

}}  // namespace EA::UTFWinControls

using namespace EA::UTFWinControls;

// ================================================================ WinSlider ctor

// @ 0x985ad0
WinSlider::WinSlider() {
    deltaPerTick = 0x100;
    tickPeriod = 2;
    hlComp = 0xff;
    selComp = 0xff;
    f1a = 1;
    iw()->SetFlag(8, 1);
}

// ================================================================ SliderDrawable factory

// @ 0x985bd0
SliderDrawable* BasicFactory_SliderDrawable::CreateInstance(int unused, void* alloc) {
    (void)unused;
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x1c, 4, "UTFWin/EA::UTFWinControls::SliderDrawable", alloc);
    if (mem) return new (mem) SliderDrawable();
    return 0;
}

// ================================================================ IWinSpinner

// @ 0x985cf0
void IWinSpinner::SetDrawable(void* d) {
    void* r;
    if (d) r = VSLOT(void*(__thiscall*)(void*), d, 0x10)(d);
    else r = 0;
    iw()->SetDrawable(r);
    refresh = 1;
}

// @ 0x985d30
void IWinSpinner::SetValue(int v, char notify) {
    int old = current;
    if (v > maxVal) v = maxVal;
    if (v < minVal) v = minVal;
    if (v == old) return;
    current = v;
    if (notify) {
        SpinnerMsg m;
        m.type = 0xaf0b6441;
        WinSpinner* w = win();
        m.src = w->id1 ? w->id1 : w->id0;
        m.from = old;
        m.to = v;
        iw()->SendMessage(&m);
    }
    refresh = 1;
}

// @ 0x985dc0
void IWinSpinner::SetMinimumValue(int v, int notify) {
    if (minVal != v) {
        int c = current;
        minVal = v;
        SetValue(c, notify);
        refresh = 1;
    }
}

// @ 0x985df0
void IWinSpinner::SetMaximumValue(int v, int notify) {
    if (maxVal != v) {
        int c = current;
        maxVal = v;
        SetValue(c, notify);
        refresh = 1;
    }
}

// @ 0x985e20
void IWinSpinner::SetMode(int v) {
    if (v != mode) {
        mode = v;
        refresh = 1;
    }
}

// @ 0x986360
void* IWinSpinner::GetDrawable() {
    SpinnerDrawableIf* d = win()->drawable;
    if (d) return d->QueryInterface(0x6f0631df);
    return 0;
}

// @ 0x986380
void IWinSpinner::SetComponentDrawable(Image* p) {
    Image* old = compDrawable;
    if (p != old) {
        if (p) p->AddRef();
        compDrawable = p;
        if (old) old->Release();
    }
    refresh = 1;
}

// ================================================================ WinSpinner

// @ 0x985e50
bool WinSpinner::OnMouseDown(float x, float y, int a3, int button) {
    (void)a3;
    if (button == 8) {
        timer.SetBoolProperty();
        uint8_t c = (uint8_t)PickComponent(x, y);
        selComp = c;
        if (c != 0xff) {
            SpinnerIWin* iw = (SpinnerIWin*)((char*)this + 4);
            if (mgr->GetCapture(1) != iw) mgr->SetCapture(1, iw);
            switch (selComp) {
            case 1:
                SetValue(current + deltaPerTick, 1);
                timer.Restart();
                break;
            case 2:
                SetValue(current - deltaPerTick, 1);
                timer.Restart();
                break;
            }
            iw->Invalidate();
        }
        return true;
    }
    return false;
}

// @ 0x985f30
bool WinSpinner::OnMouseUp(float x, float y, int a3, int flags) {
    (void)a3;
    if (!(flags & 8)) {
        SpinnerIWin* iw = this;
        if (mgr->GetCapture(1) == iw) {
            SpinnerIWin* p = (SpinnerIWin*)((char*)this + 4);
            mgr->ReleaseCapture(1, p);
        }
        selComp = 0xff;
        hlComp = (uint8_t)PickComponent(x, y);
        timer.SetBoolProperty();
        ((SpinnerIWin*)((char*)this + 4))->Invalidate();
        return true;
    }
    return false;
}

// @ 0x985fc0
bool WinSpinner::OnMouseMove(float x, float y, int flags) {
    (void)flags;
    uint8_t h = PickComponent(x, y);
    if (hlComp != h) {
        hlComp = h;
        ((SpinnerIWin*)((char*)this + 4))->Invalidate();
    }
    return true;
}

// @ 0x986000
bool WinSpinner::OnTick() {
    Refresh();
    if (timer.mnStartTime) {
        if ((uint64_t)timer.GetElapsedTime() > (uint64_t)(uint32_t)tickPeriod) {
            uint8_t c = selComp;
            if (c == hlComp) {
                switch (c) {
                case 1: SetValue(current + deltaPerTick, 1); break;
                case 2: SetValue(current - deltaPerTick, 1); break;
                }
            }
            timer.Restart();
        }
    }
    return true;
}

// @ 0x986120
bool SpinnerDrawable::GetNaturalSize(float* out, int unused, int idx) {
    (void)unused;
    uint32_t u = (uint32_t)idx;
    if (u <= 0 || u > 2 || images[idx] == 0) return false;
    out[0] = (float)images[idx]->w * 0.25f;
    out[1] = (float)images[idx]->h;
    return true;
}

// @ 0x9861a0
bool WinSpinner::GetPreferredSize(int flag, float* out) {
    (void)flag;
    Refresh();
    if (drawable) {
        float w1 = compArea[1][2] - compArea[1][0];
        float a, b;
        if (mode == 1) {
            a = w1 + (compArea[2][2] - compArea[2][0]);
            b = compArea[1][3] - compArea[1][1];
            if (compArea[2][3] - compArea[2][1] > b) b = compArea[2][3] - compArea[2][1];
        } else {
            b = (compArea[2][3] - compArea[2][1]) + (compArea[1][3] - compArea[1][1]);
            a = w1;
            if (compArea[2][2] - compArea[2][0] > a) a = compArea[2][2] - compArea[2][0];
        }
        out[0] = smax(a, 14.0f);
        out[1] = smax(b, 14.0f);
        return true;
    }
    return false;
}

// @ 0x9863c0
bool WinSpinner::OnRebuild(int g) {
    if (drawable) {
        RenderComponent(g, 0);
        RenderComponent(g, 1);
        RenderComponent(g, 2);
        return true;
    }
    ((Window*)this)->OnPaintBase(g);
    return true;
}

// @ 0x986420
void WinSpinner::RenderComponent(int g, uint32_t idx) {
    SpinnerDrawableIf* d = drawable;
    if (d != 0 && d->QueryInterface(0x6f0631df)) {
        RenderState st;
        st.s1 = state1;
        st.flags = 0;
        st.idx = idx;
        st.s0 = state0;
        if (hlComp == idx && selComp == idx) st.flags = 3;
        else if (hlComp == idx) st.flags = 2;
        uint8_t wf = ((SpinnerIWin*)((char*)this + 4))->GetFlags();
        if (!(wf & 2) || (current == maxVal && idx == 1) || (current == minVal && idx == 2))
            st.flags = 1;
        if (mode == 2) st.flags |= 0x80;
        drawable->Render(g, &compArea[idx][0], &st);
    }
}

// @ 0x986510
int WinSpinner::PickComponent(float x, float y) {
    if (x >= compArea[1][0] && y >= compArea[1][1] && x < compArea[1][2] && y < compArea[1][3]) return 1;
    if (x >= compArea[2][0] && y >= compArea[2][1] && x < compArea[2][2] && y < compArea[2][3]) return 2;
    if (x >= compArea[0][0] && y >= compArea[0][1] && x < compArea[0][2] && y < compArea[0][3]) return 0;
    return -1;
}

// --- equivalence checker address annotations
namespace __equiv_ann {
}
