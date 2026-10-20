// Slice s0096d2f0 - EA::UTFWinControls WinDialog / DialogDrawable (0x96d2f0..0x96e3a0, 9 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// Layout (retail): WinDialog primary vtable 0x1441fd8 at +0, secondary IWindow vtable
// 0x1441eb8 at +4, IWinDialog sub-object vtable 0x1441e48 at +0x20c.  The IWinDialog
// sub-object is modelled as a separate class so AutoSize / SetTitleText keep `this`
// == WinDialog+0x20c, exactly as the retail code does.

#include "types.h"

extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

#define PV(n) virtual void pv##n()

namespace EA {

struct RectF {
    float x1, y1, x2, y2;
    RectF() {}
    RectF(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    RectF(const RectF& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
    float Width() const  { return x2 - x1; }
    float Height() const { return y2 - y1; }
};

struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float a, float b) : x(a), y(b) {}
    Vec2& operator=(const Vec2& v) { x = v.x; y = v.y; return *this; }
};

struct IRefCounted {
    virtual int AddRef();          // +0x00
    virtual int Release();         // +0x04
};

} // namespace EA

namespace EA {
namespace UTFWin {

struct Image {
    char pad00[0x1c];
    int  mSizeX;                   // +0x1c
    int  mSizeY;                   // +0x20
};

struct IWindow;

struct WindowIterator {
    void* mpNode;                  // +0x00
    void* mpNode2;                 // +0x04
    void* mpNode3;                 // +0x08
};

struct IWindow {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6);
    virtual uint32_t GetId();                              // +0x1c  slot 7
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13);
    virtual const RectF& GetRealArea();                    // +0x38  slot 14
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void SetArea(const RectF& area);               // +0x60  slot 24
    PV(25);
    virtual void SetSize(float w, float h);                // +0x68  slot 26
    PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(uint32_t flag, bool value);       // +0x7c  slot 31
    PV(32); PV(33); PV(34); PV(35); PV(36);
    PV(37); PV(38); PV(39); PV(40); PV(41); PV(42); PV(43); PV(44); PV(45);
    PV(46); PV(47); PV(48); PV(49); PV(50);
    virtual WindowIterator ChildBegin();                   // +0xcc  slot 51
    virtual WindowIterator ChildEnd();                     // +0xd0  slot 52

    void WinSetFlag(uint32_t flag, int value);             // 0x00961760
};

struct Batch2D {
    PV(0);
    virtual void SetColor(uint32_t color);                 // +0x04  slot 1
    PV(2); PV(3); PV(4); PV(5); PV(6); PV(7); PV(8); PV(9); PV(10); PV(11);
    PV(12); PV(13);
    virtual void DrawRect(float x1, float y1, float x2, float y2);              // +0x38 slot 14
    virtual void DrawQuad(const Vec2* tl, const Vec2* tr, const Vec2* br, const Vec2* bl); // +0x3c slot 15
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21);
    virtual void DrawImage(const RectF* area, Image* img, const RectF* uv);     // +0x58 slot 22
};

struct RenderContext {
    Batch2D* Begin2D(int mode);                            // 0x0095bc10
};

} // namespace UTFWin
} // namespace EA

// UTFWin drawing helpers (free functions, cdecl).
void FUN_0095c5f0(EA::UTFWin::Batch2D*, const EA::RectF*, const EA::RectF*, EA::UTFWin::Image*,
                  float, float, float, float);
void BltEdgeStretch(EA::UTFWin::Batch2D*, const EA::RectF*, const EA::RectF*, EA::UTFWin::Image*,
                    const float*, float, float);
void FUN_0095ca40(EA::UTFWin::Batch2D*, const EA::RectF*, const EA::RectF*, EA::UTFWin::Image*,
                  const float*, float, float);

namespace EA {
namespace UTFWinControls {

using EA::RectF;
using EA::Vec2;
using EA::UTFWin::IWindow;
using EA::UTFWin::WindowIterator;
using EA::UTFWin::Batch2D;
using EA::UTFWin::RenderContext;
using EA::UTFWin::Image;

enum {
    kDialogTitleText   = 0x04,
    kDialogTitleBar    = 0x08,
    kDialogCloseButton = 0x10,
    kDialogComponents  = 0x20
};

enum {
    kComponentClient = 0, kComponentTitle, kComponentLeft, kComponentRight, kComponentTop,
    kComponentBottom, kComponentTopLeft, kComponentTopRight, kComponentBottomLeft,
    kComponentBottomRight, kComponentCount
};

// The WinDialog primary vtable: ISerializable/Window slots 0..34, then the WinDialog
// dialog virtuals copied from the retail vtable 0x1441fd8.
struct WinDialogBase {
    PV(0);  PV(1);  PV(2);  PV(3);  PV(4);  PV(5);  PV(6);  PV(7);  PV(8);  PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34);
    virtual bool Refresh();                                // +0x8c  slot 35 (0x0096c6f0)
    PV(36);                                                // +0x90  slot 36
    virtual void SetSize(float w, float h);                // +0x94  slot 37 (0x0096d2f0)
    virtual void GetMinSize(float& w, float& h);           // +0x98  slot 38 (0x0096d3f0)
    virtual void GetMaxSize(float& w, float& h);           // +0x9c  slot 39 (0x0096d500)
    virtual void SetRefreshFlag(unsigned v);               // +0xa0  slot 40 (0x0096b6a0)

    void WindowCtor();                                     // 0x00962a10
    void WindowDtor();                                     // 0x00962740
};

class WinDialog : public WinDialogBase, public IWindow {
public:
    uint32_t pad08[(0x210 - 0x08) / 4];   // +0x08
    bool     mbRefresh;                   // +0x210
    char     pad211[3];
    uint32_t mnDialogFlags;               // +0x214
    uint32_t mnSelectedComponent;         // +0x218
    float    mnCursorOffsetX;             // +0x21c
    float    mnCursorOffsetY;             // +0x220
    EA::IRefCounted* mpCloseButtonDrawable; // +0x224
    EA::IRefCounted* mpCloseButton;       // +0x228
    EA::IRefCounted* mpTitleText;         // +0x22c
    RectF    mrComponentArea[10];         // +0x230
    RectF    mrClientArea;                // +0x2d0
    RectF    mfClientAreaBorder;          // +0x2e0
    RectF    mfTitleTextBorder;           // +0x2f0
    RectF    mfCloseButtonBorder;         // +0x300
    float    mfMaxW;                      // +0x310
    float    mfMaxH;                      // +0x314
    float    mfMinW;                      // +0x318
    float    mfMinH;                      // +0x31c
    uint32_t mnTitleTextColor;            // +0x320
    uint32_t mnTitleTextStyle;            // +0x324

    WinDialog* Init();                    // 0x0096e0c0
    void       Destroy();                 // 0x0096e260

    // Override the same-named virtuals in both bases.
    void SetSize(float w, float h);       // 0x0096d2f0
    void GetMinSize(float& w, float& h);  // 0x0096d3f0
    void GetMaxSize(float& w, float& h);  // 0x0096d500
};

// eastl::basic_string<wchar_t>::assign (0x00423650).
struct WString {
    const wchar_t* mpBegin;               // +0x00
    const wchar_t* mpEnd;                 // +0x04
    const wchar_t* mpCapacity;            // +0x08
    void assign(const wchar_t* first, const wchar_t* last);
};

// IWinDialog sub-object (this == WinDialog+0x20c).
struct IWinDialogSub {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    virtual void AutoSize();                              // +0x20  slot 8  (0x0096dc70)
    PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16);
    virtual void SetTitleText(const wchar_t* p);          // +0x44  slot 17 (0x0096e350)
    PV(18); PV(19); PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27);

    char     pad04[4];                    // +0x04
    uint32_t mnDialogFlags;               // +0x08
    uint32_t mnSelectedComponent;         // +0x0c
    float    mnCursorOffsetX;             // +0x10
    float    mnCursorOffsetY;             // +0x14
    void*    mpCloseButtonDrawable;       // +0x18
    void*    mpCloseButton;               // +0x1c
    void*    mpTitleText;                 // +0x20
    RectF    mrComponentArea[10];         // +0x24
    RectF    mrClientArea;                // +0xc4
    RectF    mfClientAreaBorder;          // +0xd4
    RectF    mfTitleTextBorder;           // +0xe4
    RectF    mfCloseButtonBorder;         // +0xf4
    float    mfMaxW;                      // +0x104
    float    mfMaxH;                      // +0x108
    float    mfMinW;                      // +0x10c
    float    mfMinH;                      // +0x110
    uint32_t mnTitleTextColor;            // +0x114
    uint32_t mnTitleTextStyle;            // +0x118
    WString  msTitleText;                 // +0x11c
};

// Relocatable vtable / string symbols (addresses are irrelevant to the byte
// comparison; cmpobj masks DIR32 relocations).
extern void* g_vt_async;
extern void* g_vt_lru;
extern void* g_vt_dd0;
extern void* g_vt_dd1;
extern void* g_vt_dd2;
extern void* g_vt_sub20c_b;
extern void* g_vt_wd0;
extern void* g_vt_wd1;
extern void* g_vt_sub20c;
extern void* g_vt_editorRes;
extern wchar_t gEmptyString16[];

struct DrawParam {
    int field0;
    int index;                            // +0x04
};

struct DialogDrawable {
    uint32_t pad00[4];                    // +0x00 (vptrs / refcount)
    uint32_t mnBackgroundFillColor;       // +0x10
    uint32_t mnBackImageBlitMode;         // +0x14
    Image*   mComponentImage[10];         // +0x18

    void Init();                                                          // 0x0096e000
    void CreateRenderables(RenderContext*, const RectF*, const DrawParam*); // 0x0096d6d0
};

// @ 0x0096d2f0
void WinDialog::SetSize(float w, float h)
{
    Refresh();

    const uint32_t flags = mnDialogFlags;
    const RectF* const r = mrComponentArea;
    if (flags & kDialogComponents) {
        w = w + (r[kComponentRight].x2 - r[kComponentRight].x1)
              + (r[kComponentLeft].x2 - r[kComponentLeft].x1);
        if (flags & kDialogTitleBar)
            h = ((r[kComponentBottom].y2 - r[kComponentBottom].y1)
               + (r[kComponentTop].y2 - r[kComponentTop].y1)
               + (r[kComponentTitle].y2 - r[kComponentTitle].y1)) + h;
        else
            h = ((r[kComponentBottom].y2 - r[kComponentBottom].y1)
               + (r[kComponentTop].y2 - r[kComponentTop].y1)) + h;
    } else {
        if (flags & kDialogTitleBar)
            h = (r[kComponentTitle].y2 - r[kComponentTitle].y1) + h;
    }

    static_cast<IWindow*>(this)->SetSize(
        (mfClientAreaBorder.x2 + mfClientAreaBorder.x1) + w,
        (mfClientAreaBorder.y2 + mfClientAreaBorder.y1) + h);
}

// @ 0x0096d3f0
void WinDialog::GetMinSize(float& w, float& h)
{
    Refresh();
    w = mfMinW;
    h = mfMinH;

    const uint32_t flags = mnDialogFlags;
    const RectF* const r = mrComponentArea;
    if (flags & kDialogComponents) {
        w -= (r[kComponentRight].x2 - r[kComponentRight].x1)
           + (r[kComponentLeft].x2 - r[kComponentLeft].x1);
        if (flags & kDialogTitleBar)
            h -= ((r[kComponentBottom].y2 - r[kComponentBottom].y1)
                + (r[kComponentTop].y2 - r[kComponentTop].y1))
                + (r[kComponentTitle].y2 - r[kComponentTitle].y1);
        else
            h -= (r[kComponentBottom].y2 - r[kComponentBottom].y1)
               + (r[kComponentTop].y2 - r[kComponentTop].y1);
    } else if (flags & kDialogTitleBar) {
        h = h - (r[kComponentTitle].y2 - r[kComponentTitle].y1);
    }
    w -= mfClientAreaBorder.x2 + mfClientAreaBorder.x1;
    h -= mfClientAreaBorder.y2 + mfClientAreaBorder.y1;
}

// @ 0x0096d500
void WinDialog::GetMaxSize(float& w, float& h)
{
    Refresh();
    w = mfMaxW;
    h = mfMaxH;

    const uint32_t flags = mnDialogFlags;
    const RectF* const r = mrComponentArea;
    if (flags & kDialogComponents) {
        w -= (r[kComponentRight].x2 - r[kComponentRight].x1)
           + (r[kComponentLeft].x2 - r[kComponentLeft].x1);
        if (flags & kDialogTitleBar)
            h -= ((r[kComponentBottom].y2 - r[kComponentBottom].y1)
                + (r[kComponentTop].y2 - r[kComponentTop].y1))
                + (r[kComponentTitle].y2 - r[kComponentTitle].y1);
        else
            h -= (r[kComponentBottom].y2 - r[kComponentBottom].y1)
               + (r[kComponentTop].y2 - r[kComponentTop].y1);
    } else if (flags & kDialogTitleBar) {
        h = h - (r[kComponentTitle].y2 - r[kComponentTitle].y1);
    }
    w -= mfClientAreaBorder.x2 + mfClientAreaBorder.x1;
    h -= mfClientAreaBorder.y2 + mfClientAreaBorder.y1;
}

// @ 0x0096d6d0
void DialogDrawable::CreateRenderables(RenderContext* rc, const RectF* area, const DrawParam* p)
{
    Batch2D* b = rc->Begin2D(0);
    b->SetColor(0xffffffffu);

    Image* img = mComponentImage[p->index];
    switch (p->index) {
    case kComponentClient:
        if (img) {
            switch (mnBackImageBlitMode) {
            case 0: {
                RectF uv(0.0f, 0.0f, 1.0f, 1.0f);
                b->DrawImage(area, img, &uv);
                return;
            }
            case 1: {
                RectF rect(1.0f, 1.0f, 0.0f, 0.0f);
                FUN_0095c5f0(b, area, &rect, img, 1.0f, 1.0f, 0.0f, 0.0f);
                return;
            }
            case 2: {
                RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
                float uv[4] = { 0.33333334f, 0.33333334f, 0.66666669f, 0.66666669f };
                BltEdgeStretch(b, area, &rect, img, uv, 1.0f, 1.0f);
                return;
            }
            case 3: {
                RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
                float uv[4] = { 0.33333334f, 0.33333334f, 0.66666669f, 0.66666669f };
                FUN_0095ca40(b, area, &rect, img, uv, 1.0f, 1.0f);
                return;
            }
            }
        } else {
            b->SetColor(mnBackgroundFillColor);
            b->DrawRect(area->x1, area->y1, area->x2, area->y2);
            return;
        }
        break;

    case kComponentTitle:
        if (!img) {
            b->SetColor(0xffefebd6u);
            Vec2 p0(area->x1, area->y1), p1(area->x2, area->y1);
            Vec2 p2(area->x1, area->y2), p3(area->x2, area->y2);
            b->DrawQuad(&p0, &p1, &p2, &p3);
            return;
        } else {
            const int halfW = img->mSizeX / 4;
            const float w = (float)halfW;

            RectF uv(0.0f, 0.0f, 0.25f, 1.0f);
            RectF r0(area->x1, area->y1, area->x1 + w, area->y2);
            b->DrawImage(&r0, img, &uv);

            uv = RectF(0.75f, 0.0f, 1.0f, 1.0f);
            r0 = RectF(area->x2 - w, area->y1, area->x2, area->y2);
            b->DrawImage(&r0, img, &uv);

            uv = RectF(0.25f, 0.0f, 0.75f, 1.0f);
            r0 = RectF(area->x1 + w, area->y1, area->x2 - w, area->y2);
            b->DrawImage(&r0, img, &uv);
            return;
        }

    case kComponentLeft:
    case kComponentRight:
    case kComponentTop:
    case kComponentBottom:
        b->SetColor(0xffaca899u);
        {
            Vec2 p0(area->x1, area->y1), p1(area->x2, area->y1);
            Vec2 p2(area->x2, area->y2), p3(area->x1, area->y2);
            b->DrawQuad(&p0, &p1, &p2, &p3);
        }
        break;

    default:
        break;
    }
}

// @ 0x0096dc70
void IWinDialogSub::AutoSize()
{
    WinDialog* const self = (WinDialog*)((char*)this - 0x20c);
    IWindow* const win = (IWindow*)((char*)self + 4);

    self->Refresh();

    RectF box(0.0f, 0.0f, 0.0f, 0.0f);
    WindowIterator it = win->ChildBegin();
    WindowIterator end = win->ChildEnd();
    for (; it.mpNode != end.mpNode; it.mpNode = *(void**)it.mpNode) {
        IWindow* const child = (IWindow*)((char*)it.mpNode - 4);
        if (child->GetId() == 0x4f0dd487u)
            continue;
        if (child->GetId() == 0xef3d61c5u)
            continue;
        const RectF& a = child->GetRealArea();
        if (box.x2 - box.x1 == 0.0f && box.y2 - box.y1 == 0.0f) {
            box = a;
        } else {
            if (a.x1 < box.x1) box.x1 = a.x1;
            if (a.y1 < box.y1) box.y1 = a.y1;
            if (box.x2 < a.x2) box.x2 = a.x2;
            if (box.y2 < a.y2) box.y2 = a.y2;
        }
        end = win->ChildEnd();
    }

    float w = box.Width()  + self->mfClientAreaBorder.x2 + self->mfClientAreaBorder.x1;
    float h = box.Height() + self->mfClientAreaBorder.y2 + self->mfClientAreaBorder.y1;
    const uint32_t flags = self->mnDialogFlags;
    if (flags & kDialogComponents) {
        w += (self->mrComponentArea[kComponentLeft].x2 - self->mrComponentArea[kComponentLeft].x1)
           + (self->mrComponentArea[kComponentRight].x2 - self->mrComponentArea[kComponentRight].x1);
        h += (self->mrComponentArea[kComponentTop].y2 - self->mrComponentArea[kComponentTop].y1)
           + (self->mrComponentArea[kComponentBottom].y2 - self->mrComponentArea[kComponentBottom].y1);
    }
    if (flags & kDialogTitleBar)
        h += self->mrComponentArea[kComponentTitle].y2 - self->mrComponentArea[kComponentTitle].y1;

    const float cx = w - box.x1;
    const float cy = h - box.y1;

    for (it = win->ChildBegin(), end = win->ChildEnd(); it.mpNode != end.mpNode;
         it.mpNode = *(void**)it.mpNode) {
        IWindow* const child = (IWindow*)((char*)it.mpNode - 4);
        if (child->GetId() == 0x4f0dd487u)
            continue;
        const RectF& a = child->GetRealArea();
        RectF dst(a.Width() + cx, a.Height() + cy,
                  (a.x2 - a.x1) + (a.Width() + cx), (a.y2 - a.y1) + (a.Height() + cy));
        child->SetArea(dst);
        end = win->ChildEnd();
    }

    win->SetSize(w, h);
}

// @ 0x0096e000
void DialogDrawable::Init()
{
    uint32_t* const p = (uint32_t*)this;
    *(uint32_t volatile*)(p + 1) = (uint32_t)(void*)&g_vt_async;
    *(uint32_t volatile*)(p + 2) = 0;
    *(uint32_t volatile*)(p + 3) = (uint32_t)(void*)&g_vt_lru;
    p[0] = (uint32_t)(void*)&g_vt_dd0;
    p[1] = (uint32_t)(void*)&g_vt_dd1;
    p[3] = (uint32_t)(void*)&g_vt_dd2;
    p[4] = 0xff7f7f7fu;
    p[5] = 0;
    for (int i = 6; i < 16; ++i)
        p[i] = 0;
}

// @ 0x0096e0c0
WinDialog* WinDialog::Init()
{
    WindowCtor();

    *(void**)((char*)this + 0x20c) = (void*)&g_vt_sub20c_b;
    *(void**)((char*)this + 0x00) = (void*)&g_vt_wd0;
    *(void**)((char*)this + 0x04) = (void*)&g_vt_wd1;
    *(void**)((char*)this + 0x20c) = (void*)&g_vt_sub20c;
    mnDialogFlags = 0x3f;
    mnCursorOffsetX = 0.0f;
    mnCursorOffsetY = 0.0f;
    mbRefresh = false;
    mnSelectedComponent = 0xffffffffu;
    mpCloseButtonDrawable = 0;
    mpCloseButton = 0;
    mpTitleText = 0;
    mfClientAreaBorder.x1 = 3.0f;
    mfClientAreaBorder.y1 = 3.0f;
    mfClientAreaBorder.x2 = 3.0f;
    mfClientAreaBorder.y2 = 3.0f;
    mfTitleTextBorder.x1 = 3.0f;
    mfTitleTextBorder.y1 = 0.0f;
    mfTitleTextBorder.x2 = 0.0f;
    mfTitleTextBorder.y2 = 0.0f;
    mfCloseButtonBorder.x1 = 3.0f;
    mfCloseButtonBorder.y1 = 3.0f;
    mfCloseButtonBorder.x2 = 3.0f;
    mfCloseButtonBorder.y2 = 3.0f;
    mnTitleTextStyle = 0;
    mfMaxW = 10000.0f;
    mfMaxH = 10000.0f;
    mfMinW = 0.0f;
    mfMinH = 0.0f;
    mnTitleTextColor = 0xffffffffu;
    {
        WString* const s = (WString*)((char*)this + 0x328);
        s->mpBegin = (const wchar_t*)gEmptyString16;
        s->mpEnd = (const wchar_t*)gEmptyString16;
        s->mpCapacity = (const wchar_t*)(gEmptyString16 + 1);
    }
    if (mbRefresh != true) {
        mbRefresh = true;
        static_cast<IWindow*>(this)->SetFlag(8, true);
    }
    static_cast<IWindow*>(this)->WinSetFlag(4, 1);
    return this;
}

// @ 0x0096e260
void WinDialog::Destroy()
{
    *(void**)((char*)this + 0x000) = (void*)&g_vt_wd0;
    *(void**)((char*)this + 0x004) = (void*)&g_vt_wd1;
    *(void**)((char*)this + 0x20c) = (void*)&g_vt_sub20c;

    const WString* const s = (const WString*)((char*)this + 0x328);
    const char* const b = (const char*)s->mpBegin;
    const char* const c = (const char*)s->mpCapacity;
    if (((int)(c - b) & -2) > 2 && b)
        operator delete((void*)b);
    if (mpTitleText)
        mpTitleText->Release();
    if (mpCloseButton)
        mpCloseButton->Release();
    if (mpCloseButtonDrawable)
        mpCloseButtonDrawable->Release();

    *(void**)((char*)this + 0x20c) = (void*)&g_vt_editorRes;
    WindowDtor();
}

// @ 0x0096e350
void IWinDialogSub::SetTitleText(const wchar_t* p)
{
    const wchar_t* e = p;
    while (*e != 0)
        ++e;
    msTitleText.assign(p, &p[e - p]);
    ((WinDialog*)((char*)this - 0x20c))->SetRefreshFlag(1);
}

} // namespace UTFWinControls
} // namespace EA
