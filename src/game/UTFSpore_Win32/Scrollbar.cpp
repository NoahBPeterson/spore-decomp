// src/game/UTFSpore_Win32/Scrollbar.cpp -- migrated from slice(s) s00981980, s00980760, s00982780 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Scrollbar.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <xmmintrin.h>
#include "EA/UTFWinControls/IScrollbarDrawable.h"

// ---- items of slice s00982780 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct Image_s0098_2780 { char pad0[0x1c]; int width; int height; };
}
}
namespace EA {
namespace UTFWin {
struct Vec2 { float x, y; };
}
}
namespace EA {
namespace UTFWin {
struct Canvas {
    virtual void v0();
    virtual void SetColor(uint32_t argb);                       // +4
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void v14();
    virtual void FillQuad(const Vec2* a, const Vec2* b, const Vec2* c, const Vec2* d); // +0x3c
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual void DrawImage(const float* rect, Image_s0098_2780* img, const float* uv);            // +0x58
};
}
}
namespace EA {
namespace UTFWin {
struct RenderContext_s0098_2780 { Canvas* Begin2D(int); };
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl BltEdgeStretch(Canvas*, const float* rect, const float* edge, Image_s0098_2780* img,
                            const float* uv, Vec2 scale);
}
}
}
namespace EA {
namespace UTFWinControls {
using namespace EA::UTFWin;
}
}
namespace EA {
namespace UTFWinControls {
struct DrawInfo { uint32_t flags; uint32_t part; };
}
}
namespace EA {
namespace UTFWinControls {
static inline void Quad(Canvas* c, float ax, float ay, float bx, float by,
                        float cx, float cy, float dx, float dy)
{
    Vec2 a = { ax, ay }, b = { bx, by }, cc = { cx, cy }, d = { dx, dy };
    c->FillQuad(&a, &b, &cc, &d);
}
}
}
namespace EA {
namespace UTFWinControls {
class ScrollbarDrawable { public:
    char pad[0x10];
    Image_s0098_2780* mComponentImage[7];

    // @ 0x00982780
    void __thiscall Paint(RenderContext_s0098_2780* rc, const float* r, const DrawInfo* info);
};
}
}
// ---- items of slice s00982780 end

// ---- items of slice s00980760 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])
struct XWin { void SerUpdate(); void InvalidateLayout(); };            // 009614a0 / 009609b0
struct XStopwatch {
    bool IsRunning() const { return *(const int64_t*)this != 0; }
    void Restart();                                                    // 00571e80
    void Init(int a, int b);                                           // 0093a560
    void SetUnits(int u);                                              // 0093a1a0
    int64_t GetElapsed();                                              // 0093a5e0
    int64_t GetElapsedFloat();                                         // 0093a3a0
};
struct XPropList { void SetBoolProperty(); };                          // 0093a2e0
namespace EA {
namespace UTFWinControls {
class WinScrollbar_s0098_0760;
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarWindowInvalidation {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void Invalidate();
};
}
}
namespace EA {
namespace UTFWinControls {
class IWinScrollbar_s0098_0760 { public:
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
    WinScrollbar_s0098_0760* win();
    void SetOrientation(int o);                                        // 00981000
    void SetFlags(uint32_t mask, char on);                             // 00981030
    void SetDrawable(void* d);                                         // 00981060
    void SetValue(int v, char notify);                                 // 009810a0
    void SetMinimumValue(int v, int notify);                           // 00981130
    void SetMaximumValue(int v, int notify);                           // 00981170
    void SetVisibleRange(int v, int notify);                           // 009811b0
    void SetPageOverlap(int v);                                        // 00981200
};
}
}
namespace EA {
namespace UTFWinControls {
struct XWinMgr {                                  // window manager held at WinScrollbar +0x34
    virtual void wm00();
    virtual void wm04();
    virtual void wm08();
    virtual void wm0c();
    virtual void wm10();
    virtual void wm14();
    virtual void wm18();
    virtual void wm1c();
    virtual void wm20();
    virtual void wm24();
    virtual void wm28();
    virtual void wm2c();
    virtual void wm30();
    virtual void wm34();
    virtual void wm38();
    virtual void wm3c();
    virtual void wm40();
    virtual void wm44();
    virtual void wm48();
    virtual void wm4c();
    virtual void wm50();
    virtual void* GetMouseCapture(int which);     // +0x54
    virtual void wm58();
    virtual void ReleaseMouseCapture(int which, struct ScrollbarSecondaryCalls* w);   // +0x5c
};
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarActiveCall {
    virtual void active0();
    virtual void active1();
    virtual void active2();
    virtual void active3();
    virtual void active4();
    virtual void active5();
    virtual void active6();
    virtual void active7();
    virtual void active8();
    virtual void active9();
    virtual void active10();
    virtual void active11();
    virtual void active12();
    virtual void active13();
    virtual void active14();
    virtual void active15();
    virtual void active16();
    virtual void active17();
    virtual void active18();
    virtual void active19();
    virtual void active20();
    virtual void active21();
    virtual void active22();
    virtual void active23();
    virtual void active24();
    virtual void active25();
    virtual void active26();
    virtual void active27();
    virtual void active28();
    virtual void active29();
    virtual void active30();
    virtual void active31();
    virtual void active32();
    virtual void active33();
    virtual void active34();
    virtual bool IsActive();
};
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarPrimaryCalls {
    virtual void primary0();
    virtual void primary1();
    virtual void primary2();
    virtual void primary3();
    virtual void primary4();
    virtual void primary5();
    virtual void primary6();
    virtual void primary7();
    virtual void primary8();
    virtual void primary9();
    virtual void primary10();
    virtual void primary11();
    virtual void primary12();
    virtual void primary13();
    virtual void primary14();
    virtual void primary15();
    virtual void primary16();
    virtual void primary17();
    virtual void primary18();
    virtual void primary19();
    virtual void primary20();
    virtual void primary21();
    virtual void primary22();
    virtual void primary23();
    virtual void primary24();
    virtual void primary25();
    virtual void primary26();
    virtual void primary27();
    virtual void primary28();
    virtual void primary29();
    virtual void primary30();
    virtual void primary31();
    virtual void primary32();
    virtual void primary33();
    virtual void primary34();
    virtual int IsActive();
    virtual void SetRefreshFlag(char on);
    virtual void SetRefresh(char on);
    virtual void primary38();
    virtual void primary39();
    virtual char HitTestComponent(float x, float y);                   // +0xa0
};
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarSecondaryCalls {
    virtual void secondary0();
    virtual void secondary1();
    virtual void secondary2();
    virtual void secondary3();
    virtual void secondary4();
    virtual void secondary5();
    virtual void secondary6();
    virtual void secondary7();
    virtual void secondary8();
    virtual void secondary9();
    virtual void secondary10();
    virtual void secondary11();
    virtual void secondary12();
    virtual void secondary13();
    virtual void secondary14();
    virtual void secondary15();
    virtual void secondary16();
    virtual void secondary17();
    virtual void secondary18();
    virtual void secondary19();
    virtual void secondary20();
    virtual void secondary21();
    virtual void secondary22();
    virtual void secondary23();
    virtual void secondary24();
    virtual void secondary25();
    virtual void secondary26();
    virtual void secondary27();
    virtual void secondary28();
    virtual void secondary29();
    virtual void secondary30();
    virtual void SetFlag(unsigned mask, bool on);
};
}
}
namespace EA {
namespace UTFWinControls {
class WinScrollbar_s0098_0760 : public ScrollbarPrimaryCalls, public ScrollbarSecondaryCalls { public:
    char  pad008[0x34 - 8];
    void* winMgr;                                                      // +0x034
    char  pad038[0x80 - 0x38];
    int   id0;                                                         // +0x080
    int   id1;                                                         // +0x084
    char  pad088[0x20c - 0x88];
    IWinScrollbar_s0098_0760 sb;                                                  // +0x20c
    void* iw() { return (char*)this + 4; }
    void  UpdateAndSync();                                             // 00980fa0
    int   IsActive();                                                  // 009816e0
    void  SetRefreshFlag(char on);                                     // 00981700
    void  SetRefresh(char on);                                         // 00981770
    bool  OnMouseDown(float x, float y, int a3, int button);           // 00981220 0x00981220
    bool  OnMouseUp(float x, float y, int a3, int flags);              // 00981430 0x00981430
    bool  OnFocusChange(int state, void* w);                           // 009814c0 0x009814c0
    bool  OnTick();                                                    // 00981500 0x00981500
};
}
}
namespace EA {
namespace UTFWinControls {
inline WinScrollbar_s0098_0760* IWinScrollbar_s0098_0760::win() { return (WinScrollbar_s0098_0760*)((char*)this - 0x20c); }
}
}
namespace EA {
namespace UTFWinControls {
struct IWinSB2 {
    void InvalidateLayoutNoArgs();                                     // 009816c0
};
}
}
// ---- items of slice s00980760 end

// ---- items of slice s00981980 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectF { float left, top, right, bottom; bool Contains(float x, float y); };
struct RenderParam { uint32_t flags, component, dim1, dim2; };
class IScrollbarDrawable { public:
    virtual void   v00();
    virtual void   v04();
    virtual void   v08();
    virtual void*  FindComponent(uint32_t type);                                          // +0x0c
    virtual void   RenderComponent(void* window, const RectF* rect,
                                   const RenderParam* param);                             // +0x10
    virtual void   v14();
    virtual bool   GetNaturalSize(float* out, int flags, int idx);                        // +0x18
};
struct Window_s0095_ff20 { void OnPaint(void* param); };
class WinScrollbar;
class IWinScrollbar { public:
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
    RectF compArea[7];                                                 // +0x54 (0x260)
    WinScrollbar* win();
    IScrollbarDrawable* GetDrawable();                                 // 00981b60
};
class WinScrollbar { public:
    void* vt0;                                                         // +0x000
    void* vtIW;                                                        // +0x004
    char  pad008[0x34 - 8];
    void* winMgr;                                                      // +0x034
    char  pad038[0x80 - 0x38];
    int   id0;                                                         // +0x080
    int   id1;                                                         // +0x084
    float clientLeft;                                                  // +0x088
    float clientTop;                                                   // +0x08c
    float clientRight;                                                 // +0x090
    float clientBottom;                                                // +0x094
    char  pad098[0x1e0 - 0x98];
    IScrollbarDrawable* mpDrawable;                                    // +0x1e0
    char  pad1e4[0x20c - 0x1e4];
    IWinScrollbar sb;                                                  // +0x20c
    void* iw() { return (char*)this + 4; }
    bool  ComputeContentSize(int arg, float* out);                     // 00981980
    bool  OnMouseMove(float x, float y, float z);                      // 00981b70
    bool  OnRebuild(void* param);                                      // 00981cc0
    void  RenderComponent(void* window, uint32_t component);           // 00981d50
    int   PickComponent(float x, float y);                             // 00981e10
    void  Refresh();                                                   // 00981f80
};
inline WinScrollbar* IWinScrollbar::win() { return (WinScrollbar*)((char*)this - 0x20c); }
// ---- items of slice s00981980 end

// @ 0x00980fa0
void EA::UTFWinControls::WinScrollbar_s0098_0760::UpdateAndSync()
{
    VSLOT(void(__thiscall*)(void*, int), this, 0x94)(this, 1);
    ((XWin*)this)->SerUpdate();
}

// @ 0x00981030
void EA::UTFWinControls::IWinScrollbar_s0098_0760::SetFlags(uint32_t mask, char on)
{
    if (on) flags |= (int)mask;
    else flags &= ~(int)mask;
}

// @ 0x00981060
void EA::UTFWinControls::IWinScrollbar_s0098_0760::SetDrawable(void* d)
{
    void* iwv = (char*)this - 0x208;
    VSLOT(void(__thiscall*)(void*, void*), iwv, 0xb0)(iwv, d);
    EA::UTFWinControls::WinScrollbar_s0098_0760* w = (EA::UTFWinControls::WinScrollbar_s0098_0760*)((char*)this - 0x20c);
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
}

// @ 0x00981200
void EA::UTFWinControls::IWinScrollbar_s0098_0760::SetPageOverlap(int v)
{
    int d = visibleRange - v;
    pageOverlap = v;
    pageDelta = d;
    if (d < 1) pageDelta = 1;
}

// @ 0x00981220
bool EA::UTFWinControls::WinScrollbar_s0098_0760::OnMouseDown(float x, float y, int a3, int button)
{
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

// @ 0x00981430
bool EA::UTFWinControls::WinScrollbar_s0098_0760::OnMouseUp(float x, float y, int a3, int flags)
{
    (void)a3;
    if ((flags & 8) == 0) {
        void* iwv = this ? (char*)this + 4 : 0;
        if (((EA::UTFWinControls::XWinMgr*)winMgr)->GetMouseCapture(1) == iwv)
            ((EA::UTFWinControls::XWinMgr*)winMgr)->ReleaseMouseCapture(1, this);
        sb.selComp = 0xff;
        sb.hlComp = (uint8_t)HitTestComponent(x, y);
        SetRefreshFlag(0);
        VSLOT(void(__thiscall*)(void*), (char*)this + 4, 0x90)((char*)this + 4);
        return true;
    }
    return false;
}

// @ 0x009814c0
bool EA::UTFWinControls::WinScrollbar_s0098_0760::OnFocusChange(int state, void* w)
{
    if (state == 1) {
        void* iwv = this ? (char*)this + 4 : 0;
        if (w != iwv && static_cast<signed char>(sb.hlComp) != -1) {
            sb.hlComp = 0xff;
            ((EA::UTFWinControls::ScrollbarWindowInvalidation*)((char*)this + 4))->Invalidate();
        }
    }
    return true;
}

// @ 0x00981500
bool EA::UTFWinControls::WinScrollbar_s0098_0760::OnTick()
{
    VSLOT(void(__thiscall*)(void*), this, 0x98)(this);
    int64_t* tstamp = (int64_t*)((char*)this + 0x248);
    if (*tstamp == 0) return true;
    if ((sb.flags & 1) && (sb.selComp == 1 || sb.selComp == 6)) {
        int64_t e = ((XStopwatch*)((char*)this + 0x248))->GetElapsedFloat();
        float f = (float)((double)e * (double)*(float*)((char*)this + 0x25c));
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
        if ((uint32_t)((uint64_t)e >> 32) == 0 && (uint32_t)e <= 0x96) return true;
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

// @ 0x009816c0
void EA::UTFWinControls::IWinSB2::InvalidateLayoutNoArgs()
{
    void* w = (char*)this - 4;
    VSLOT(void(__thiscall*)(void*, int), w, 0x94)(w, 1);
    ((XWin*)this)->InvalidateLayout();
}

// @ 0x009816e0
int EA::UTFWinControls::WinScrollbar_s0098_0760::IsActive()
{
    if (sb.refresh != 0 || *(int64_t*)((char*)this + 0x248) != 0)
        return 1;
    return 0;
}

// @ 0x00981700
void EA::UTFWinControls::WinScrollbar_s0098_0760::SetRefreshFlag(char on)
{
    XStopwatch* sw = (XStopwatch*)((char*)this + 0x248);
    const bool old = sw->IsRunning();
    if (on) sw->Restart();
    else ((XPropList*)sw)->SetBoolProperty();
    if (old != sw->IsRunning())
        SetFlag(8, ((EA::UTFWinControls::ScrollbarActiveCall*)this)->IsActive());
}

// @ 0x00981770
void EA::UTFWinControls::WinScrollbar_s0098_0760::SetRefresh(char on)
{
    if (sb.refresh == (uint8_t)on) return;
    sb.refresh = (uint8_t)on;
    SetFlag(8, ((EA::UTFWinControls::ScrollbarActiveCall*)this)->IsActive());
}

// @ 0x00981980
bool WinScrollbar::ComputeContentSize(int arg, float* out)
{
    if (arg != 0) return false;
    VSLOT(void(__thiscall*)(void*), this, 0x98)(this);
    if (mpDrawable == 0) return false;

    float sizeX = 0.0f, sizeY = 0.0f, thick = 0.0f;
    bool none = true;
    if (sb.orientation == 1) {
        for (unsigned i = 0; i < 7; i++) {
            if (i == 0) continue;
            float sz[2];
            if (!mpDrawable->GetNaturalSize(sz, 0, i)) continue;
            if (sz[1] > sizeY) sizeY = sz[1];
            if (i == 1 || i == 6) sizeX += sz[0];
            if (i == 3 || i == 4) thick = (sz[0] > thick) ? sz[0] : thick;
            none = false;
        }
        sizeX += thick;
    } else {
        for (unsigned i = 0; i < 7; i++) {
            if (i == 0) continue;
            float sz[2];
            if (!mpDrawable->GetNaturalSize(sz, 0, i)) continue;
            if (sz[0] > sizeX) sizeX = sz[0];
            if (i == 1 || i == 6) sizeY += sz[1];
            if (i == 3 || i == 4) thick = (sz[1] > thick) ? sz[1] : thick;
            none = false;
        }
        sizeY += thick;
    }
    if (none) return false;
    out[0] = (14.0f > sizeX) ? 14.0f : sizeX;
    out[1] = (14.0f > sizeY) ? 14.0f : sizeY;
    return true;
}

// @ 0x00981b60
IScrollbarDrawable* IWinScrollbar::GetDrawable()
{ return win()->mpDrawable; }

// @ 0x00981b70
bool WinScrollbar::OnMouseMove(float x, float y, float z)
{
    (void)z;
    void* iwv = this ? (char*)this + 4 : 0;
    void* cap = VSLOT(void*(__thiscall*)(void*, int), winMgr, 0x54)(winMgr, 1);
    if (cap == iwv) {
        switch (sb.selComp) {
        case 3: {
            int range = sb.maxVal - sb.visibleRange - sb.minVal;
            float a, b, arg;
            if (sb.orientation == 1) {
                a = sb.compArea[4].right;
                b = sb.compArea[3].right;
                arg = x;
                a -= sb.compArea[4].left;
                b -= sb.compArea[3].left;
            } else {
                a = sb.compArea[4].bottom;
                b = sb.compArea[3].bottom;
                arg = y;
                a -= sb.compArea[4].top;
                b -= sb.compArea[3].top;
            }
            arg -= sb.thumbOffset;
            a -= b;
            if (a > 0.0f) {
                int v = (int)((float)range * arg / a) + sb.minVal;
                VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, v, 1);
            } else {
                VSLOT(void(__thiscall*)(void*, int, int), &sb, 0x24)(&sb, sb.minVal, 1);
            }
            return true;
        }
        case 1: case 2: case 5: case 6:
            break;
        default:
            return true;
        }
    }
    char c = VSLOT(char(__thiscall*)(void*, float, float), this, 0xa0)(this, x, y);
    if (sb.hlComp != (uint8_t)c) {
        sb.hlComp = (uint8_t)c;
        VSLOT(void(__thiscall*)(void*), (char*)this + 4, 0x90)((char*)this + 4);
    }
    return true;
}

// @ 0x00981cc0
bool WinScrollbar::OnRebuild(void* param)
{
    if (mpDrawable != 0) {
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 0);
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 4);
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 3);
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 1);
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 6);
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 2);
        VSLOT(void(__thiscall*)(void*, void*, int), this, 0x9c)(this, param, 5);
    } else {
        ((Window_s0095_ff20*)this)->OnPaint(param);
    }
    return true;
}

// @ 0x00981d50
void WinScrollbar::RenderComponent(void* window, uint32_t component)
{
    if (mpDrawable == 0) return;
    RenderParam p;
    p.dim1 = *(uint32_t*)((char*)this + 0x1dc);
    p.flags = 0;
    p.component = component;
    p.dim2 = *(uint32_t*)((char*)this + 0x1d8);
    if (sb.hlComp == component && sb.selComp == component) p.flags = 3;
    else if (sb.hlComp == component) p.flags = 2;
    uint32_t m = VSLOT(uint32_t(__thiscall*)(void*), (char*)this + 4, 0x28)((char*)this + 4);
    if ((m & 2) == 0) p.flags = 1;
    if (sb.orientation == 2) p.flags |= 0x80;
    mpDrawable->RenderComponent(window, &sb.compArea[component], &p);
}

// @ 0x00981e10
int WinScrollbar::PickComponent(float x, float y)
{
    if (x >= sb.compArea[3].left && y >= sb.compArea[3].top &&
        x < sb.compArea[3].right && y < sb.compArea[3].bottom) return 3;
    if (x >= sb.compArea[5].left && y >= sb.compArea[5].top &&
        x < sb.compArea[5].right && y < sb.compArea[5].bottom) return 5;
    if (x >= sb.compArea[2].left && y >= sb.compArea[2].top &&
        x < sb.compArea[2].right && y < sb.compArea[2].bottom) return 2;
    if (x >= sb.compArea[6].left && y >= sb.compArea[6].top &&
        x < sb.compArea[6].right && y < sb.compArea[6].bottom) return 6;
    if (x >= sb.compArea[1].left && y >= sb.compArea[1].top &&
        x < sb.compArea[1].right && y < sb.compArea[1].bottom) return 1;
    if (sb.compArea[4].Contains(x, y)) return 4;
    return sb.compArea[0].Contains(x, y) ? 0 : -1;
}

// @ 0x00981f80
void WinScrollbar::Refresh()
{
    void* found = mpDrawable ? mpDrawable->FindComponent(0xeef3af8c) : 0;
    if (sb.refresh == 0 || found == 0) return;
    VSLOT(void(__thiscall*)(void*, int), this, 0x94)(this, 0);

    int t = sb.maxVal - sb.visibleRange;
    if (sb.current > t) sb.current = t;
    if (sb.current < sb.minVal) sb.current = sb.minVal;
    sb.pageDelta = sb.visibleRange - sb.pageOverlap;
    if (sb.pageDelta < 1) sb.pageDelta = 1;

    float sz[7][2];
    float w = 0.0f, h = 0.0f;
    for (int i = 0; i < 7; i++) {
        uint32_t flag = (uint32_t)((sb.orientation != 2) - 1) & 0x80;
        if (!mpDrawable->GetNaturalSize(&w, (int)flag, i)) {
            float* r = VSLOT(float*(__thiscall*)(void*), (char*)this + 4, 0x38)((char*)this + 4);
            w = r[2] - r[0];
            h = r[3] - r[1];
            if (i == 6 || i == 1) {
                if (sb.orientation == 1) {
                    w = (h > w * 0.33333334f) ? w * 0.33333334f : h;
                } else {
                    h = (w > h * 0.33333334f) ? h * 0.33333334f : w;
                }
            }
        }
        sz[i][0] = w;
        sz[i][1] = h;
    }

    float H = clientBottom - clientTop;
    float W = clientRight - clientLeft;

    if (sb.orientation == 1) {
        for (int i = 0; i < 7; i++) {
            float top = (H - sz[i][1]) * 0.5f;
            sb.compArea[i].top = top;
            sb.compArea[i].bottom = top + sz[i][1];
        }
    } else {
        for (int i = 0; i < 7; i++) {
            float left = (W - sz[i][0]) * 0.5f;
            sb.compArea[i].left = left;
            sb.compArea[i].right = left + sz[i][0];
        }
    }

    if (sb.orientation == 1) {
        sb.compArea[6].left = W - sz[6][0];
        sb.compArea[4].right = W - sz[6][0];
        sb.compArea[6].right = W;
        sb.compArea[1].left = 0.0f;
        sb.compArea[1].right = sz[1][0];
        sb.compArea[4].left = sz[1][0];
    } else {
        sb.compArea[6].top = H - sz[6][1];
        sb.compArea[4].bottom = H - sz[6][1];
        sb.compArea[6].bottom = H;
        sb.compArea[1].top = 0.0f;
        sb.compArea[1].bottom = sz[1][1];
        sb.compArea[4].top = sz[1][1];
    }

    sb.compArea[0].left = 0.0f;
    sb.compArea[0].right = W;
    sb.compArea[0].top = 0.0f;
    sb.compArea[0].bottom = H;

    int range = sb.maxVal - sb.minVal;
    if (range <= sb.visibleRange || range <= 0) {
        if (sb.orientation == 1) {
            sb.compArea[3].left = sb.compArea[4].left;
            sb.compArea[3].right = sb.compArea[4].right;
        } else {
            sb.compArea[3].top = sb.compArea[4].top;
            sb.compArea[3].bottom = sb.compArea[4].bottom;
        }
    } else {
        int extra = range - sb.visibleRange;
        if (sb.orientation == 1) {
            float thumb = (sb.compArea[4].right - sb.compArea[4].left) *
                          (float)sb.visibleRange / (float)range;
            if (thumb < (float)sb.minThumbSize) thumb = (float)sb.minThumbSize;
            float pos = ((sb.compArea[4].right - sb.compArea[4].left - thumb) *
                         (float)(sb.current - sb.minVal) + (float)(extra / 2)) /
                        (float)extra + sb.compArea[4].left;
            sb.compArea[3].left = pos;
            sb.compArea[3].right = pos + thumb;
        } else {
            float thumb = (sb.compArea[4].bottom - sb.compArea[4].top) *
                          (float)sb.visibleRange / (float)range;
            if (thumb < (float)sb.minThumbSize) thumb = (float)sb.minThumbSize;
            float pos = ((sb.compArea[4].bottom - sb.compArea[4].top - thumb) *
                         (float)(sb.current - sb.minVal) + (float)(extra / 2)) /
                        (float)extra + sb.compArea[4].top;
            sb.compArea[3].top = pos;
            sb.compArea[3].bottom = pos + thumb;
        }
    }

    if (sb.orientation == 1) {
        sb.compArea[2].left = sb.compArea[4].left;
        sb.compArea[2].right = sb.compArea[3].left;
        sb.compArea[5].left = sb.compArea[3].right;
        sb.compArea[5].right = sb.compArea[4].right;
    } else {
        sb.compArea[2].top = sb.compArea[4].top;
        sb.compArea[2].bottom = sb.compArea[3].top;
        sb.compArea[5].top = sb.compArea[3].bottom;
        sb.compArea[5].bottom = sb.compArea[4].bottom;
    }

    VSLOT(void(__thiscall*)(void*), (char*)this + 4, 0x90)((char*)this + 4);
}

// @ 0x00982780
namespace EA { namespace UTFWinControls {
void ScrollbarDrawable::Paint(RenderContext_s0098_2780* rc, const float* r, const DrawInfo* info)
{
    Canvas* c = rc->Begin2D(0);
    c->SetColor(0xffffffff);
    uint32_t part = info->part;
    Image_s0098_2780* img = mComponentImage[part];
    float L, T, R, B;                    // read from r only on the paths that draw quads

    switch (part) {
    case 0:
        if (img) {
            float edge[4], uv[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
            edge[0] = 0.5f - 0.5f / (float)img->width;
            edge[1] = 0.5f - 0.5f / (float)img->height;
            edge[2] = 0.5f / (float)img->width + 0.5f;
            edge[3] = 0.5f / (float)img->height + 0.5f;
            Vec2 one = { 1.0f, 1.0f };
            Drawing::BltEdgeStretch(c, r, edge, img, uv, one);
        }
        break;

    case 1:
    case 3:
    case 6:
        if (img) {
            float u = 0.0f;
            switch (info->flags & 7) {
            case 0:
                if ((info->flags & 8) == 0) { u = 0.25f; break; }
                u = 0.75f;
                break;
            case 3: u = 0.75f; break;
            case 1: u = 0.0f; break;
            case 2: u = 0.5f; break;
            }
            float uv[4] = { u, 0.0f, u + 0.25f, 1.0f };
            if (part == 3) {
                float edge[4];
                edge[0] = 0.5f - 0.5f / (float)img->width;
                edge[1] = 0.5f - 0.5f / (float)img->height;
                edge[2] = 0.5f / (float)img->width + 0.5f;
                edge[3] = 0.5f / (float)img->height + 0.5f;
                Vec2 one = { 1.0f, 1.0f };
                Drawing::BltEdgeStretch(c, r, edge, img, uv, one);
                return;
            }
            c->DrawImage(r, img, uv);
            return;
        }

        L = r[0]; T = r[1]; R = r[2]; B = r[3];
        if ((info->flags & 7) == 3) {
            c->SetColor(0xffece9d8);
            Quad(c, L + 1.0f, T + 1.0f, R - 1.0f, T + 1.0f, R - 1.0f, B - 1.0f, L + 1.0f, B - 1.0f);
            c->SetColor(0xff716f64);
            Quad(c, L, T, R - 1.0f, T, R - 1.0f, T + 1.0f, L, T + 1.0f);
            Quad(c, L, T + 1.0f, L, B - 1.0f, L + 1.0f, B - 1.0f, L + 1.0f, T + 1.0f);
            Quad(c, R - 1.0f, T, R, T, R, B - 1.0f, R - 1.0f, B - 1.0f);
            Quad(c, L, B - 1.0f, R, B - 1.0f, R, B, L, B);
        } else {
            c->SetColor((info->flags & 2) ? 0xfffbfbf9u : 0xffece9d8u);
            Quad(c, L + 2.0f, T + 2.0f, R - 2.0f, T + 2.0f, R - 2.0f, B - 2.0f, L + 2.0f, B - 2.0f);
            c->SetColor(0xfff1efe2);
            Quad(c, L, T, R - 1.0f, T, R - 1.0f, T + 1.0f, L, T + 1.0f);
            Quad(c, L, T + 1.0f, L, B - 1.0f, L + 1.0f, B - 1.0f, L + 1.0f, T + 1.0f);
            c->SetColor(0xffffffff);
            Quad(c, L + 1.0f, T + 1.0f, R - 2.0f, T + 1.0f, R - 2.0f, T + 2.0f, L + 1.0f, T + 2.0f);
            Quad(c, L + 1.0f, T + 2.0f, L + 2.0f, T + 2.0f, L + 2.0f, B - 2.0f, L + 1.0f, B - 2.0f);
            c->SetColor(0xff716f64);
            Quad(c, R - 1.0f, T, R, T, R, B - 1.0f, R - 1.0f, B - 1.0f);
            Quad(c, L, B - 1.0f, R, B - 1.0f, R, B, L, B);
            c->SetColor(0xffaca899);
            Quad(c, R - 2.0f, T + 1.0f, R - 1.0f, T + 1.0f, R - 1.0f, B - 2.0f, R - 2.0f, B - 2.0f);
            Quad(c, L + 1.0f, B - 2.0f, R - 1.0f, B - 2.0f, R - 1.0f, B - 1.0f, L + 1.0f, B - 1.0f);
        }
        if (part == 1 || part == 6) {
            c->SetColor(0xff000000);
            float dx = (R - L) * 0.2857143f;
            float dy = (B - T) * 0.2857143f;
            float o = ((info->flags & 7) == 3) ? 1.0f : 0.0f;
            if (part == 1) {
                if (info->flags & 0x80) {
                    float x0 = L + o + dx;
                    float yb = (B - dy) + o;
                    Quad(c, x0, yb, ((R - L) * 0.5f + L) + o, (T + o) + dy,
                         (R - dx) + o, yb, x0, yb);
                } else {
                    float x0 = L + o + dx;
                    float x1 = (R - dx) + o;
                    float ym = ((B - T) * 0.5f + T) + o;
                    Quad(c, x0, ym, x1, (T + o) + dy, x1, (B - dy) + o, x0, ym);
                }
            } else {
                if (info->flags & 0x80) {
                    float x0 = L + o + dx;
                    float y0 = (o + dy) + T;
                    Quad(c, x0, y0, (R - dx) + o, y0, ((R - L) * 0.5f + L) + o, (B - dy) + o, x0, y0);
                } else {
                    float x0 = L + o + dx;
                    float y0 = (T + o) + dy;
                    Quad(c, x0, y0, (R - dx) + o, ((B - T) * 0.5f + T) + o, x0, (B - dy) + o, x0, y0);
                }
            }
        }
        break;

    case 4:
        if (img) {
            float edge[4], uv[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
            edge[0] = 0.5f - 0.5f / (float)img->width;
            edge[1] = 0.5f - 0.5f / (float)img->height;
            edge[2] = 0.5f / (float)img->width + 0.5f;
            edge[3] = 0.5f / (float)img->height + 0.5f;
            Vec2 one = { 1.0f, 1.0f };
            Drawing::BltEdgeStretch(c, r, edge, img, uv, one);
            return;
        }
        c->SetColor(0xffaca899);
        L = r[0]; T = r[1]; R = r[2]; B = r[3];
        Quad(c, L, T, R, T, R, B, L, B);
        return;
    }
}
}}  // namespace EA::UTFWinControls
