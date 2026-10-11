// Slice s0096ad00 - EA::UTFWinControls dialog / console-window family
// (0x96ad00..0x96bdb0, 27 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// The small "invalidate" helpers live on a sub-object 0x20c bytes into the complete
// WinDialog (its primary vtable is at this-0x20c); one lives on the IWindow
// sub-object at +4. They are modelled with matching stub classes.

#include "types.h"

#define PV(n) virtual void pv##n()

inline void* operator new(unsigned int, void* p) { return p; }

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

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* t = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (t) t->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct IRefCounted {
    virtual int AddRef();          // +0x00
    virtual int Release();         // +0x04
};

namespace Text {

struct StyleManager;
struct ICoreAllocator;

struct TextStyle {
    char pad00[0x1c];
    int  mfSize;                   // +0x1c
    char pad20[0x178];
    int  mHAlignment;
    char pad1fc[0x78];
    int  mTextWrap;

    TextStyle();                   // 0x008941d0
};

struct StyleManager {
    TextStyle* GetStyle(uint32_t styleId, int alloc);   // 0x00894670
    void       AddStyle(uint32_t styleId, TextStyle* style); // 0x00894970
};

// 0x00885bd0
StyleManager* GetStyleManager(bool);

} // namespace Text

namespace UTFWin {

struct IWindow;
struct IWindowMgr;

struct RenderContext {
    void* Begin2D(int mode);       // 0x0095bc10
    void  End2D();                 // 0x0095bb20

    // vtable slots touched through the returned interface pointer.
    PV(0); PV(1);
    virtual void v08(int);         // +0x04
    PV(3); PV(4);
    virtual void v14(void*);       // +0x14
    PV(6); PV(7); PV(8);
    virtual void v1c(int, int, float, float, int); // +0x1c
    PV(10); PV(11);
    virtual void v30(void*, void*, void*);         // +0x30
    PV(13);
    virtual void v38(int, int, int, int);          // +0x38
};

struct Message {
    IWindow* source;
    int      field_04;
    int      eventType;
    int      param0;
    int      param1;
    int      param2;
    void*    pData;
};

struct IWindowMgr {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    virtual void* GetCapture(int);                 // +0x3c
    PV(16); PV(17); PV(18); PV(19); PV(20);
    virtual void* GetCapture2(int);                // +0x54
    virtual void  SetCapture(int, void*);          // +0x58
    virtual void  SetCapture2(int, void*);         // +0x5c
};

struct IWindow {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20);
    PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29); PV(30);
    virtual void SetFlag(uint32_t flag, int value);    // +0x7c
    PV(32); PV(33); PV(34); PV(35);
    virtual int  Invalidate();                         // +0x90
};

// The primary Window vtable as far as this slice needs it.
struct WindowVt {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7); PV(8); PV(9);
    PV(10); PV(11); PV(12); PV(13); PV(14); PV(15); PV(16); PV(17); PV(18); PV(19);
    PV(20); PV(21); PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28); PV(29);
    PV(30); PV(31); PV(32); PV(33); PV(34);
    PV(35);
    virtual int  GetComponentAt(float x, float y);     // +0x90
    PV(37); PV(38); PV(39);
    virtual void UpdateLayout(int mode);               // +0xa0

    bool Window_Initialize();       // 0x00b1fbf0
    void Window_SerUpdate();        // 0x009614a0
    void Window_InvalidateLayout(); // 0x009609b0
    void Window_Shutdown();         // 0x00961e80
};

} // namespace UTFWin

namespace UTFWinControls {

struct IWinText {
    virtual int   AddRef();
    virtual int   Release();
    PV(2); PV(3);
    virtual void* ToWindow();                                     // +0x10
    PV(5); PV(6); PV(7); PV(8); PV(9);
    virtual void  SetTextColor(uint32_t color);                   // +0x28
    PV(11); PV(12); PV(13);
    virtual void  SetTextBorders(float, float, float, float);     // +0x38
};

struct IWinButton {
    virtual int   AddRef();
    virtual int   Release();
    PV(2);
    virtual void* Cast(uint32_t type);                            // +0x0c
};

} // namespace UTFWinControls

} // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWindowMgr;
using EA::UTFWin::IWindowMgr;
using EA::UTFWinControls::IWinText;
using EA::UTFWinControls::IWinButton;

// Complete dialog object; only the offsets this slice touches are named.
struct WinDialog : EA::UTFWin::WindowVt {
    uint32_t pad04[(0x88 - 0x04) / 4];        // +0x04
    EA::RectF mArea;                           // +0x88
    uint32_t pad98[(0x210 - 0x98) / 4];       // +0x98
    bool     mbRefresh;                        // +0x210
    uint32_t mnDialogFlags;                    // +0x214
    int      mnSelectedComponent;              // +0x218
    float    mnCursorOffsetX;                  // +0x21c
    float    mnCursorOffsetY;                  // +0x220
    void*    mpCloseButtonDrawable;            // +0x224
    void*    mpCloseButton;                    // +0x228
    void*    mpTitleText;                      // +0x22c

    void SetRefreshFlag(unsigned v);           // 0x0096b6a0
    bool OnMouseUp(int, int, int, unsigned flags); // 0x0096b600
    int  OnMouseDown(int, float px, float py, unsigned eventType); // 0x0096b460
};

// Sub-object at WinDialog+0x20c (its own primary vtable is at this-0x20c).
struct DlgSub20c {
    uint32_t pad00[2];                         // +0x00
    int      mFlags;                           // +0x08
    uint32_t pad0c[(0xd4 - 0x0c) / 4];         // +0x0c
    float    mLocalBorder[4];                  // +0x0d4
    float    mTitleBorder[4];                  // +0x0e4
    float    mCloseBorder[4];                  // +0x0f4
    float    mMaxW, mMaxH;                     // +0x104
    float    mMinW, mMinH;                     // +0x10c
    int      mTitleTextColor;                  // +0x114
    int      mTitleTextStyle;                  // +0x118

    void SetFlags(int f);                                     // 0x0096b400
    void SetLocalBorder(float, float, float, float);          // 0x0096b710
    void SetTitleBorder(float, float, float, float);          // 0x0096b7b0
    void SetCloseBorder(float, float, float, float);          // 0x0096b850
    void SetTitleTextStyle(int v);                            // 0x0096b770
    void SetTitleTextColor(int v);                            // 0x0096b900
    void SetMinSize(float w, float h);                        // 0x0096b930
    void SetMaxSize(float w, float h);                        // 0x0096b990
};

// Sub-object at WinDialog+4 (the IWindow interface vtable).
struct DlgSub4 {
    void InvalidateAndLayout();                               // 0x0096b680
};

// Hook holder used by 0x0096bd60.
struct DictIface {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14); PV(15);
    PV(16); PV(17); PV(18); PV(19); PV(20); PV(21); PV(22); PV(23);
    virtual void v60(void* n);                                // +0x60
    virtual void* v64();                                      // +0x64
};

struct DialogState {
    char  pad00[0x18];
    void* mpValue;                                            // +0x18
    void* mpHook;                                             // +0x1c

    void  SetValue(void* p);                                  // 0x0096bd60
    void* GetValue();                                         // 0x0096bdb0
};

// DialogDrawable (0x0096ba00 / 0x0096ba30).
struct DialogDrawable {
    char  pad00[0x18];
    void* mpImage0;                                           // +0x18
    void* mpImage1;                                           // +0x1c

    void* AsInterface(uint32_t type);                         // 0x0096ba00
    bool  GetNaturalSize(EA::Vec2* dst, int state, int index); // 0x0096ba30
    void* BaseAsInterface(uint32_t type);                     // 0x00951240
};

// Component-image table used by 0x0096bb10/50/60/70.
struct ImageTable {
    uint32_t pad00[1];
    void*    mpBackground;                                    // +0x04
    uint32_t mBlitMode;                                       // +0x08
    void*    mpImages[10];                                    // +0x0c

    void SetImage(unsigned idx, void* p);                     // 0x0096bb10
    void GetBackground(void** out);                           // 0x0096bb50
    void SetBlitMode(unsigned mode);                          // 0x0096bb60
    void GetBlitMode(void** out);                             // 0x0096bb70
};

// ---------------------------------------------------------------------------
// External helpers (declarations only; resolved to the real addresses).
// ---------------------------------------------------------------------------
namespace Console {

void InitChannelColors(void* sub, int arg);   // 0x009677d0
void ResizeBuffers(void* sub, int count, int arg); // 0x009676f0

} // namespace Console

void __fastcall Window_ctor(void*);   // 0x00962a10

// ConsoleWindow (0x0096ad00 / 0x0096b0b0). Layout accessed via raw offsets.
struct ConsoleWindow {
    ConsoleWindow(bool param2);                          // 0x0096b0b0
    int  OnRebuild(EA::UTFWin::RenderContext* ctx);      // 0x0096ad00
    char mDummy;
};

namespace EA {
namespace Text {

struct Typesetter {
    Typesetter(bool unicode);      // 0x0089d820
};

struct LineLayout {
    LineLayout(bool unicode);      // 0x00898bd0
    void Clear(bool arg);          // 0x0089cbc0
};

} // namespace Text
} // namespace EA

// ---------------------------------------------------------------------------
// 0x0096b3a0  EA::UTFWinControls::WinDialog::Init
// ---------------------------------------------------------------------------
bool __fastcall WinDialog_Init(WinDialog* this_)
{
    if (this_->Window_Initialize()) {
        this_->UpdateLayout(1);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x0096b380
// ---------------------------------------------------------------------------
void __fastcall Sub_b380(WinDialog* this_)
{
    this_->UpdateLayout(1);
    return this_->Window_SerUpdate();
}

// ---------------------------------------------------------------------------
// 0x0096b680
// ---------------------------------------------------------------------------
void DlgSub4::InvalidateAndLayout()
{
    ((EA::UTFWin::WindowVt*)((char*)this - 4))->UpdateLayout(1);
    return ((EA::UTFWin::WindowVt*)((char*)this))->Window_InvalidateLayout();
}

// ---------------------------------------------------------------------------
// 0x0096b400
// ---------------------------------------------------------------------------
void DlgSub20c::SetFlags(int f)
{
    if (mFlags != f) {
        mFlags = f;
        return ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
    }
}

// ---------------------------------------------------------------------------
// 0x0096b770
// ---------------------------------------------------------------------------
void DlgSub20c::SetTitleTextStyle(int v)
{
    mTitleTextStyle = v;
    return ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b900
// ---------------------------------------------------------------------------
void DlgSub20c::SetTitleTextColor(int v)
{
    mTitleTextColor = v;
    return ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b710
// ---------------------------------------------------------------------------
void DlgSub20c::SetLocalBorder(float a, float b, float c, float d)
{
    mLocalBorder[0] = a;
    mLocalBorder[1] = b;
    mLocalBorder[2] = c;
    mLocalBorder[3] = d;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b7b0
// ---------------------------------------------------------------------------
void DlgSub20c::SetTitleBorder(float a, float b, float c, float d)
{
    mTitleBorder[0] = a;
    mTitleBorder[1] = b;
    mTitleBorder[2] = c;
    mTitleBorder[3] = d;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b850
// ---------------------------------------------------------------------------
void DlgSub20c::SetCloseBorder(float a, float b, float c, float d)
{
    mCloseBorder[0] = a;
    mCloseBorder[1] = b;
    mCloseBorder[2] = c;
    mCloseBorder[3] = d;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b930
// ---------------------------------------------------------------------------
void DlgSub20c::SetMinSize(float w, float h)
{
    mMinW = w;
    mMinH = h;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b990
// ---------------------------------------------------------------------------
void DlgSub20c::SetMaxSize(float w, float h)
{
    mMaxW = w;
    mMaxH = h;
    ((EA::UTFWin::WindowVt*)((char*)this - 0x20c))->UpdateLayout(1);
}

// ---------------------------------------------------------------------------
// 0x0096b6a0
// ---------------------------------------------------------------------------
void WinDialog::SetRefreshFlag(unsigned v)
{
    if (*(unsigned char*)((char*)this + 0x210) != (unsigned char)v) {
        *(unsigned char*)((char*)this + 0x210) = (unsigned char)v;
        ((IWindow*)((char*)this + 4))->SetFlag(8, v);
    }
}

// ---------------------------------------------------------------------------
// 0x0096b660  EA::UTFWinControls::WinDialog::OnTick
// ---------------------------------------------------------------------------
bool __fastcall WinDialog_OnTick(WinDialog* this_)
{
    this_->pv35();
    return true;
}

// ---------------------------------------------------------------------------
// 0x0096b600  EA::UTFWinControls::WinDialog::OnMouseUp
// ---------------------------------------------------------------------------
bool WinDialog::OnMouseUp(int, int, int, unsigned flags)
{
    if ((flags & 8) == 0) {
        IWindow* pSelf = this ? (IWindow*)((char*)this + 4) : 0;
        if ((*(IWindowMgr**)((char*)this + 0x34))->GetCapture2(1) == (void*)pSelf)
            (*(IWindowMgr**)((char*)this + 0x34))->SetCapture2(1, (IWindow*)((char*)this + 4));

        *(int*)((char*)this + 0x218) = -1;
        ((IWindow*)((char*)this + 4))->Invalidate();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x0096bb10
// ---------------------------------------------------------------------------
void ImageTable::SetImage(unsigned idx, void* p)
{
    if (idx >= 10)
        return;
    if (mpImages[idx] == p)
        return;
    if (p)
        ((EA::IRefCounted*)p)->AddRef();
    EA::IRefCounted* old = (EA::IRefCounted*)mpImages[idx];
    if (old)
        old->Release();
    mpImages[idx] = p;
}

// ---------------------------------------------------------------------------
// 0x0096bb50
// ---------------------------------------------------------------------------
void ImageTable::GetBackground(void** out) { *out = mpBackground; }

// ---------------------------------------------------------------------------
// 0x0096bb60
// ---------------------------------------------------------------------------
void ImageTable::SetBlitMode(unsigned mode)
{
    if (mode <= 3)
        mBlitMode = mode;
}

// ---------------------------------------------------------------------------
// 0x0096bb70
// ---------------------------------------------------------------------------
void ImageTable::GetBlitMode(void** out) { *out = (void*)mBlitMode; }

// ---------------------------------------------------------------------------
// 0x0096bd00  EA::UTFWinControls::WinDialog::Shutdown
// ---------------------------------------------------------------------------
void __fastcall WinDialog_Shutdown(WinDialog* this_)
{
    if (*(EA::IRefCounted**)((char*)this_ + 0x224)) {
        EA::IRefCounted* p = *(EA::IRefCounted**)((char*)this_ + 0x224);
        *(void**)((char*)this_ + 0x224) = 0;
        p->Release();
    }
    if (*(EA::IRefCounted**)((char*)this_ + 0x228)) {
        EA::IRefCounted* p = *(EA::IRefCounted**)((char*)this_ + 0x228);
        *(void**)((char*)this_ + 0x228) = 0;
        p->Release();
    }
    if (*(EA::IRefCounted**)((char*)this_ + 0x22c)) {
        EA::IRefCounted* p = *(EA::IRefCounted**)((char*)this_ + 0x22c);
        *(void**)((char*)this_ + 0x22c) = 0;
        p->Release();
    }
    return this_->Window_Shutdown();
}

// ---------------------------------------------------------------------------
// 0x0096bd60
// ---------------------------------------------------------------------------
void DialogState::SetValue(void* p)
{
    EA::IRefCounted* old = (EA::IRefCounted*)mpValue;
    if (p != old) {
        if (p)
            ((EA::IRefCounted*)p)->AddRef();
        mpValue = p;
        if (old)
            old->Release();
    }
    DictIface* q = (DictIface*)mpHook;
    if (q)
        return q->v60(mpValue);
}

// ---------------------------------------------------------------------------
// 0x0096bdb0
// ---------------------------------------------------------------------------
void* DialogState::GetValue()
{
    DictIface* q = (DictIface*)mpHook;
    if (q)
        return q->v64();
    return mpValue;
}

// ---------------------------------------------------------------------------
// 0x0096ba00  EA::UTFWinControls::DialogDrawable::AsInterface
// ---------------------------------------------------------------------------
void* DialogDrawable::AsInterface(uint32_t type)
{
    if (type != 0x6f0c6ff6u) {
        if (type != 0xeec58382u)
            return BaseAsInterface(type);
        if (this)
            return (void*)((char*)this + 4);
        return 0;
    }
    return this;
}

// ---------------------------------------------------------------------------
// 0x0096ba30  EA::UTFWinControls::DialogDrawable::GetNaturalSize
// ---------------------------------------------------------------------------
bool DialogDrawable::GetNaturalSize(EA::Vec2* dst, int, int index)
{
    switch (index) {
    case 0:
        if (mpImage0) {
            dst->x = (float)*(int*)((char*)mpImage0 + 0x1c);
            dst->y = (float)*(int*)((char*)mpImage0 + 0x20);
        }
        return true;
    case 1:
        if (mpImage1) {
            dst->y = (float)*(int*)((char*)mpImage1 + 0x20);
            return true;
        }
        dst->y = 20.0f;
        return true;
    case 2:
    case 3:
        dst->x = 3.0f;
        return true;
    case 4:
    case 5:
        dst->y = 3.0f;
        return true;
    case 6:
    case 7:
    case 8:
    case 9:
        dst->x = 3.0f;
        dst->y = 3.0f;
        return true;
    default:
        return false;
    }
}

// ---------------------------------------------------------------------------
// 0x0096b2d0  BasicFactory_ConsoleWindow::CreateInstance
// ---------------------------------------------------------------------------
// 0x009512c0
int __cdecl FUN_009512c0();
// 0x009512d0
void* __cdecl FUN_009512d0(int size, int align, const char* type, void* factory);

// 0x0096b0b0  EA::UTFWinControls::ConsoleWindow::ConsoleWindow
void* __stdcall Factory_ConsoleWindow_CreateInstance(int param1, void* param2)
{
    if (param2 == 0)
        param2 = (void*)FUN_009512c0();
    char* obj = (char*)FUN_009512d0(0x870, 4,
                                    "UTFWin/EA::UTFWinControls::ConsoleWindow", param2);
    if (obj != 0) {
        void* r = ::new (obj) ConsoleWindow(true);
        if (r != 0)
            return (char*)r + 4;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0096b0b0  EA::UTFWinControls::ConsoleWindow::ConsoleWindow
// ---------------------------------------------------------------------------
ConsoleWindow::ConsoleWindow(bool param2)
{
    char* this_ = (char*)this;
    char* esi = this_;
    EA::UTFWin::WindowVt* self = (EA::UTFWin::WindowVt*)this_;

    // UTFWin::Window::Window(this) -- base construction.
    Window_ctor(this_);

    *(void**)esi = (void*)0x1441c18;            // primary vtable
    *(void**)(esi + 4) = (void*)0x1441af8;      // IWindow vtable

    Console::InitChannelColors(esi + 0x20c, 0);

    *(int*)(esi + 0x21c) = 0x3e8;
    *(int*)(esi + 0x220) = 0x1000;
    *(int*)(esi + 0x224) = 0;
    *(int*)(esi + 0x228) = 0;
    *(int*)(esi + 0x22c) = (int)(esi + 0x22c);
    *(int*)(esi + 0x230) = (int)(esi + 0x22c);
    *(int*)(esi + 0x234) = 0;
    *(float*)(esi + 0x248) = 0.0f;
    *(float*)(esi + 0x24c) = 0.0f;
    *(int*)(esi + 0x240) = 1;
    *(int*)(esi + 0x23c) = 0x154df28;
    *(int*)(esi + 0x244) = 0;
    *(int*)(esi + 0x250) = 0;
    *(float*)(esi + 0x838) = 0.0f;
    *(float*)(esi + 0x83c) = 0.0f;
    *(float*)(esi + 0x840) = 0.0f;
    *(float*)(esi + 0x844) = 0.0f;

    // Typesetter / LineLayout sub-objects.
    new (esi + 0x258) EA::Text::Typesetter(false);
    new (esi + 0x788) EA::Text::LineLayout(false);

    *(int*)(esi + 0x848)   = -1;
    *(float*)(esi + 0x84c) = 0.0f;
    *(float*)(esi + 0x850) = 0.0f;
    *(float*)(esi + 0x854) = 0.0f;
    *(float*)(esi + 0x858) = 0.0f;
    *(int*)(esi + 0x85c)   = -1;
    *(unsigned char*)(esi + 0x860) = 0;
    *(unsigned char*)(esi + 0x861) = 0;
    *(int*)(esi + 0x864)   = 0;
    *(unsigned char*)(esi + 0x868) = param2 ? 1 : 0;
    *(float*)(esi + 0x86c) = 0.0f;

    Console::ResizeBuffers(esi + 0x20c, 0x1000, 0);
    ((IWindow*)(esi + 4))->SetFlag(0x10, true);

    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm) {
        if (sm->GetStyle(0xefe945b2, 0) == 0) {
            EA::Text::TextStyle style;
            // name copied from L"Trebuchet MS"
            style.mfSize = 9.0f;
            style.mHAlignment = 0;
            style.mTextWrap = 0;
            sm->AddStyle(0xefe945b2, &style);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x0096b460  EA::UTFWinControls::WinDialog::OnMouseDown
// ---------------------------------------------------------------------------
int WinDialog::OnMouseDown(int, float px, float py, unsigned eventType)
{
    if (eventType != 8)
        return 0;
    (void)px;
    (void)py;

    char* esi = (char*)this;
    int comp = this->GetComponentAt(py, px);
    *(int*)(esi + 0x218) = comp;
    if (comp == -1)
        goto finish;

    if (comp <= 9) {
        switch (comp) {
        case 0:
        case 1:
            if ((*(unsigned char*)(esi + 0x214) & 1) == 0) {
                if ((*(unsigned char*)(esi + 0x214) & 2) == 0) {
                    *(int*)(esi + 0x218) = -1;
                }
            }
            break;
        default:
            if ((*(unsigned char*)(esi + 0x214) & 2) == 0) {
                *(int*)(esi + 0x218) = -1;
            }
            break;
        }
    }
    if (*(int*)(esi + 0x218) == -1)
        goto finish;

    {
        IWindowMgr* pMgr = *(IWindowMgr**)(esi + 0x34);
        char* pWin = *(char**)(esi + 0x38);
        void* pHit = pMgr ? pMgr->GetCapture(1) : 0;
        (void)pHit;

        EA::Vec2 local;
        pMgr->GetCapture(0);                   // placeholder for area query
        (void)pWin;
        (void)local;
    }
    {
        IWindowMgr* pMgr = *(IWindowMgr**)(esi + 0x34);
        IWindow* pIWin = (IWindow*)(esi + 4);
        if (pMgr->GetCapture2(1) != pIWin)
            pMgr->SetCapture2(1, pIWin);
    }

finish:
    ((IWindow*)(esi + 4))->Invalidate();
    return 1;
}

// ---------------------------------------------------------------------------
// 0x0096ad00  EA::UTFWinControls::ConsoleWindow::OnRebuild
// ---------------------------------------------------------------------------
int ConsoleWindow::OnRebuild(EA::UTFWin::RenderContext* ctx)
{
    EA::UTFWin::RenderContext* pRC = (EA::UTFWin::RenderContext*)ctx;
    pRC->Begin2D(0);
    return 1;
}
