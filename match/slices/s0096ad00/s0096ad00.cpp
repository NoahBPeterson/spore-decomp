// Slice s0096ad00 - EA::UTFWinControls dialog / console-window family
// (0x96ad00..0x96bdb0, 27 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region).
//
// The small "invalidate" helpers live on a sub-object 0x20c bytes into the complete
// WinDialog (its primary vtable is at this-0x20c); one lives on the IWindow
// sub-object at +4. They are modelled with matching stub classes.

#include "types.h"

// In-place construction helper (placement new).
inline void* operator new(unsigned int, void* p) { return p; }

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

template <class T>
class AutoRefCount { public:
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

class StyleManager;
struct ICoreAllocator;

struct TextStyle {
    wchar_t  mFamilyNameArray[32][8]; // +0x000
    float    mfSize;                  // +0x200
    int      mStyle;                  // +0x204
    float    mfWeight;                // +0x208
    int      mVariant;                // +0x20c
    int      mPitch;                  // +0x210
    int      mSmooth;                 // +0x214
    int      mEffect;                 // +0x218
    float    mfEffectX;               // +0x21c
    float    mfEffectY;               // +0x220
    uint32_t mColor;                  // +0x224
    uint32_t mColorBackground;        // +0x228
    uint32_t mEffectBaseColor;        // +0x22c
    uint32_t mEffectColor;            // +0x230
    uint32_t mHighLightColor;         // +0x234
    uint32_t mnDecorationFlags;       // +0x238
    int      mDirection;              // +0x23c
    int      mOrientation;            // +0x240
    int      mHAlignment;             // +0x244
    int      mVAlignment;             // +0x248
    int      mJustify;                // +0x24c
    int      mTextWrap;               // +0x250
    int      mTextOverflow;           // +0x254
    int      mEmphasisStyle;          // +0x258
    int      mEmphasisPosition;       // +0x25c
    int      mDigitSubstitution;      // +0x260
    int      mPasswordMode;           // +0x264
    float    mfStretch;               // +0x268
    float    mfLetterSpacing;         // +0x26c
    float    mfWordSpacing;           // +0x270
    float    mfLineSpace;             // +0x274

    TextStyle();                   // 0x008941d0
};

class StyleManager { public:
    TextStyle* GetStyle(uint32_t styleId, int alloc);   // 0x00894670
    void       AddStyle(uint32_t styleId, TextStyle* style); // 0x00894970
};

// 0x00885bd0
StyleManager* GetStyleManager(bool);

} // namespace Text

namespace UTFWin {

class IWindow;
class IWindowMgr;

class RenderContext { public:
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

class Message { public:
    IWindow* source;
    int      field_04;
    int      eventType;
    int      param0;
    int      param1;
    int      param2;
    void*    pData;
};

class IWindowMgr { public:
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    virtual void  GetPoint(void* pPoint);          // +0x3c
    PV(16); PV(17); PV(18); PV(19); PV(20);
    virtual void* GetCapture2(int);                // +0x54
    virtual void  SetCapture(int, void*);          // +0x58
    virtual void  SetCapture2(int, void*);         // +0x5c
};

// Second interface on the component container at WinDialog+0x38.
struct CompContainerSub {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12); PV(13); PV(14);
    PV(15); PV(16); PV(17); PV(18); PV(19); PV(20); PV(21);
    PV(22); PV(23); PV(24); PV(25); PV(26); PV(27); PV(28);
    PV(29); PV(30); PV(31); PV(32); PV(33); PV(34); PV(35);
    PV(36); PV(37); PV(38); PV(39); PV(40); PV(41); PV(42);
    PV(43); PV(44); PV(45); PV(46); PV(47); PV(48);
    virtual void DrawPoint(const EA::Vec2* pPoint); // +0xc4
};

class IWindow { public:
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

class IWinText { public:
    virtual int   AddRef();
    virtual int   Release();
    PV(2); PV(3);
    virtual void* ToWindow();                                     // +0x10
    PV(5); PV(6); PV(7); PV(8); PV(9);
    virtual void  SetTextColor(uint32_t color);                   // +0x28
    PV(11); PV(12); PV(13);
    virtual void  SetTextBorders(float, float, float, float);     // +0x38
};

class IWinButton { public:
    virtual int   AddRef();
    virtual int   Release();
    PV(2);
    virtual void* Cast(uint32_t type);                            // +0x0c
};

} // namespace UTFWinControls

} // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWindowMgr;
using EA::UTFWin::CompContainerSub;
using EA::UTFWinControls::IWinText;
using EA::UTFWinControls::IWinButton;

// Complete dialog object; only the offsets this slice touches are named.
struct WinDialog : EA::UTFWin::WindowVt {
    uint32_t pad04[(0x34 - 0x04) / 4];        // +0x04
    IWindowMgr* mpWindowMgr;                   // +0x34
    void*       mpCompContainer;               // +0x38
    uint32_t pad3c[(0x88 - 0x3c) / 4];         // +0x3c
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

// Channel-color storage at ConsoleWindow+0x20c (S_9677d0/S_9676f0 family).
struct ChannelColors {
    uint32_t mData[4];                                        // +0x00 .. +0x0f

    uint32_t* InitChannelColors(int arg);                     // 0x009677d0
    void      ResizeBuffers(unsigned count, int arg);         // 0x009676f0
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
void __fastcall Window_ctor(void*);   // 0x00962a10

// The Window base sub-object whose non-virtual SetFlag the constructor calls.
struct WindowBase {
    void SetFlag(unsigned flag, unsigned char value);       // 0x00961760
};

namespace EA {
namespace Text {

class Typesetter { public:
    char mData[0x530];

    Typesetter() {}
    Typesetter(bool unicode);      // 0x0089d820
    void* LayoutParagraph(const wchar_t* text, uint32_t len, float x, float y,
                          float x1, float y1, const TextStyle* style,
                          void* out, void* arg9);              // 0x0089dc00
};

class LineLayout { public:
    char mData[0x2c];

    LineLayout() {}
    LineLayout(bool unicode);      // 0x00898bd0
    void Clear(bool arg);          // 0x0089cbc0
};

} // namespace Text
} // namespace EA

// Render batch returned by RenderContext::Begin2D.
struct Batch2D {
    PV(0);
    virtual void SetColor(uint32_t c);                       // +0x04
    PV(2); PV(3); PV(4);
    virtual void SetClipRect(const EA::RectF* r);             // +0x14
    PV(6);
    virtual void DrawRect5(float, float, float, float, float); // +0x1c
    PV(8); PV(9); PV(10); PV(11);
    virtual void DrawText(void*, void*, void*);               // +0x30
    PV(13);
    virtual void FillRect(float, float, float, float);        // +0x38
};

// Scrollbar object at ConsoleWindow+0x864 and the interface it returns.
struct ScrollHost {
    PV(0); PV(1); PV(2); PV(3);
    virtual void* GetContent();                              // +0x10
};
struct ScrollContent {
    PV(0); PV(1); PV(2); PV(3); PV(4); PV(5); PV(6); PV(7);
    PV(8); PV(9); PV(10); PV(11); PV(12);
    virtual const EA::RectF* GetBounds();                    // +0x34
};

// One console line: circular-list node plus its text payload.
struct ConsoleLine {
    ConsoleLine* mpNext;                                     // +0x00
    ConsoleLine* mpPrev;                                     // +0x04
    char*        mpKey;                                      // +0x08
    int          mnHeight;                                   // +0x0c
    uint32_t     mnLength;                                   // +0x10
    wchar_t      mText[1];                                   // +0x14
};

// Channel-color hash map at ConsoleWindow+0x238 (eastl hashtable subset).
struct ConsoleMap {
    void*     mp0;                                           // +0x00
    uint32_t* mpBuckets;                                     // +0x04
    int       mnBucketCount;                                 // +0x08
    int       mn0c;                                          // +0x0c
    float     mf10;                                          // +0x10
    float     mf14;                                          // +0x14
    int       mn18;                                          // +0x18
    int       mn1c;                                          // +0x1c

    int* Find(int* out, void** pkey);                        // 0x0096ab90
};

// ConsoleWindow (0x0096ad00 / 0x0096b0b0).
struct ConsoleWindow {
    uint32_t mPad000[0x88 / 4];                              // +0x000
    EA::RectF mArea;                                         // +0x088
    uint32_t mPad098;                                        // +0x098
    float    mRenderTop;                                     // +0x09c
    float    mRenderMid;                                     // +0x0a0
    float    mRenderBottom;                                  // +0x0a4
    char     mPad0a8[0x20c - 0x0a8];                         // +0x0a8
    ChannelColors mChannels;                                 // +0x20c
    int      mnScrollRange;                                  // +0x21c
    int      mnPageSize;                                     // +0x220
    int      mnScrollOffset;                                 // +0x224
    int      mnContentHeight;                                // +0x228
    ConsoleLine* mpListHead;                                 // +0x22c
    ConsoleLine* mpListTail;                                 // +0x230
    int      mnLineCount;                                    // +0x234
    ConsoleMap mMap;                                         // +0x238
    EA::Text::Typesetter mTypesetter;                        // +0x258
    EA::Text::LineLayout mLineLayout;                        // +0x788
    void*    mpDrawArg1;                                     // +0x7b4
    char     mPad7b8[0x7dc - 0x7b8];                         // +0x7b8
    void*    mpDrawArg2;                                     // +0x7dc
    char     mPad7e0[0x838 - 0x7e0];                         // +0x7e0
    float    mf838;                                          // +0x838
    float    mf83c;                                          // +0x83c
    float    mf840;                                          // +0x840
    float    mf844;                                          // +0x844
    int      mn848;                                          // +0x848
    float    mfInsetLeft;                                    // +0x84c
    float    mfInsetTop;                                     // +0x850
    float    mfInsetRight;                                   // +0x854
    float    mfInsetBottom;                                  // +0x858
    int      mnColorMask;                                    // +0x85c
    bool     mbFlag860;                                      // +0x860
    bool     mbNeedLayout;                                   // +0x861
    char     mPad862[2];                                     // +0x862
    void*    mpScrollBar;                                    // +0x864
    bool     mbHasScrollBar;                                 // +0x868
    char     mPad869[3];                                     // +0x869
    float    mf86c;                                          // +0x86c

    ConsoleWindow(bool param2);                              // 0x0096b0b0
    int  OnRebuild(EA::UTFWin::RenderContext* ctx);           // 0x0096ad00
    void LayoutLines();                                      // 0x0096a790
};

// Constants loaded from the image.
extern const float kf3;              // 0x01441a28
extern float       gColorSeed;       // 0x0166b1bc
extern const float kf169;            // 0x01441aa8
extern const float kf86;             // 0x01441aa4
extern const float kf145;            // 0x01441aa0
extern const float kf110;            // 0x01441a9c
extern const float kfOne;            // 0x01485720
extern const float kfTwo;            // 0x01470f1c
extern const float kfFour;           // 0x014853e0
extern const float kfWeight;         // 0x0142eae0
extern const float kfSize;           // 0x013f8734
extern const float kfTwoPow32;       // 0x013f4fd0
extern const wchar_t kConsoleFontName[]; // 0x01441ca0

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
    Window_ctor(this);

    *(void**)this = (void*)0x1441c18;            // primary vtable
    *(void**)((char*)this + 4) = (void*)0x1441af8; // IWindow vtable

    mChannels.InitChannelColors(0);

    mnScrollRange = 0x3e8;
    mnPageSize = 0x1000;
    mnScrollOffset = 0;
    mnContentHeight = 0;
    mpListHead = (ConsoleLine*)((char*)this + 0x22c);
    mpListTail = (ConsoleLine*)((char*)this + 0x22c);
    mnLineCount = 0;
    mMap.mpBuckets = (uint32_t*)0x154df28;
    mMap.mnBucketCount = 1;
    mMap.mn0c = 0;
    mMap.mf10 = kfOne;
    mMap.mf14 = kfTwo;
    mMap.mn18 = 0;

    new (&mTypesetter) EA::Text::Typesetter(false);
    new (&mLineLayout) EA::Text::LineLayout(false);

    mn848 = -1;
    float inset = kfFour;
    mfInsetLeft = inset;
    mfInsetTop = inset;
    mfInsetRight = inset;
    mfInsetBottom = inset;
    mnColorMask = -1;
    mbFlag860 = false;
    mbNeedLayout = false;
    mpScrollBar = 0;
    mbHasScrollBar = param2;
    mf86c = kfOne;
    mf838 = 0.0f;
    mf83c = 0.0f;
    mf840 = 0.0f;
    mf844 = 0.0f;

    mChannels.ResizeBuffers(0x1000, 0);
    ((WindowBase*)((char*)this + 4))->SetFlag(0x10, 1);

    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm != 0) {
        if (sm->GetStyle(0xefe945b2, 0) == 0) {
            EA::Text::TextStyle style;
            wchar_t* dst = &style.mFamilyNameArray[0][0];
            int i = 0;
            wchar_t c;
            do {
                c = kConsoleFontName[i];
                dst[i] = c;
                ++i;
            } while (c != 0);
            style.mfSize = kfSize;
            style.mHAlignment = 0;
            style.mfWeight = kfWeight;
            style.mSmooth = 1;
            style.mTextWrap = 4;
            sm->AddStyle(0xefe945b2, &style);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x0096b460  EA::UTFWinControls::WinDialog::OnMouseDown
// ---------------------------------------------------------------------------
int WinDialog::OnMouseDown(int arg1, float px, float py, unsigned eventType)
{
    if (eventType != 8)
        return 0;

    int comp = GetComponentAt(*(float*)&arg1, px);
    mnSelectedComponent = comp;
    if (comp == -1)
        goto finish;

    if ((unsigned)comp <= 9) {
        switch (comp) {
        case 0:
        case 1:
            if ((mnDialogFlags & 1) == 0)
                mnSelectedComponent = -1;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if ((mnDialogFlags & 2) == 0)
                mnSelectedComponent = -1;
            break;
        }
    }
    if (mnSelectedComponent == -1)
        goto finish;

    {
        EA::Vec2 pt;
        mpWindowMgr->GetPoint(&pt);
        ((CompContainerSub*)((char*)mpCompContainer + 4))->DrawPoint(&pt);

        switch (mnSelectedComponent) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 6:
            mnCursorOffsetX = pt.x - mArea.x1;
            mnCursorOffsetY = pt.y - mArea.y1;
            break;
        case 3:
        case 5:
        case 9:
            mnCursorOffsetX = mArea.x2 - pt.x;
            mnCursorOffsetY = mArea.y2 - pt.y;
            break;
        case 7:
            mnCursorOffsetX = mArea.x2 - pt.x;
            mnCursorOffsetY = pt.y - mArea.y1;
            break;
        case 8:
            mnCursorOffsetX = pt.x - mArea.x1;
            mnCursorOffsetY = mArea.y2 - pt.y;
            break;
        }
    }

    {
        IWindow* pSelf = (IWindow*)((char*)this + 4);
        if (mpWindowMgr->GetCapture2(1) != pSelf)
            mpWindowMgr->SetCapture(1, pSelf);
    }

finish:
    ((IWindow*)((char*)this + 4))->Invalidate();
    return 1;
}

// ---------------------------------------------------------------------------
// 0x0096ad00  EA::UTFWinControls::ConsoleWindow::OnRebuild
// ---------------------------------------------------------------------------
int ConsoleWindow::OnRebuild(EA::UTFWin::RenderContext* volatile ctx)
{
    Batch2D* pBatch = (Batch2D*)ctx->Begin2D(0);

    EA::RectF rect;
    rect.x1 = 0.0f;
    rect.y1 = 0.0f;
    rect.x2 = mArea.x2 - mArea.x1;
    rect.y2 = mArea.y2 - mArea.y1;

    if (mbHasScrollBar) {
        ScrollContent* pContent =
            (ScrollContent*)((ScrollHost*)mpScrollBar)->GetContent();
        const EA::RectF* pBounds = pContent->GetBounds();
        rect.x2 -= (pBounds->x2 - pBounds->x1) + kf3;
    }

    uint32_t color1 = (((uint32_t)(unsigned char)(int)(gColorSeed * kf169 + kf86)) << 24) | 0x3d517f;
    pBatch->SetColor(color1 & (uint32_t)mnColorMask);
    pBatch->FillRect(0.0f, 0.0f, rect.x2 - rect.x1, rect.y2 - rect.y1);

    uint32_t color2 = (((uint32_t)(unsigned char)(int)(gColorSeed * kf145 + kf110)) << 24) | 0x8a9dc4;
    pBatch->SetColor(color2 & (uint32_t)mnColorMask);
    pBatch->DrawRect5(0.0f, 0.0f, rect.x2 - rect.x1, rect.y2 - rect.y1, kfTwo);

    rect.x1 += mfInsetLeft;
    rect.y1 += mfInsetTop;
    rect.x2 -= mfInsetRight;
    rect.y2 -= mfInsetBottom;
    pBatch->SetClipRect(&rect);

    if (mbNeedLayout) {
        mbNeedLayout = false;
        LayoutLines();
    }

    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm == 0) {
        ctx->End2D();
        return 1;
    }
    const EA::Text::TextStyle* pStyle = sm->GetStyle(0xefe945b2, 0);

    float base = mRenderBottom - mRenderTop - mfInsetBottom;
    float cur = base + (float)mnScrollOffset;
    if (cur > mfInsetTop) {
        ConsoleLine* sentinel = (ConsoleLine*)&mpListHead;
        ConsoleLine* end = sentinel->mpNext;
        ConsoleLine* node = sentinel;
        while (node != end) {
            ConsoleLine* line = node->mpPrev;
            float next = cur - (float)(unsigned)line->mnHeight;
            if (base < next) {
                uint32_t color;
                if (line->mpKey == 0) {
                    color = 0xffffffffu;
                } else {
                    int out[2];
                    ConsoleMap* pMap = &mMap;
                    int* pFound = pMap->Find(out, (void**)&line->mpKey);
                    void* found = (void*)pFound[0];
                    if (found == (void*)pMap->mpBuckets[pMap->mnBucketCount])
                        color = 0xffa7b8ffu;
                    else
                        color = *(uint32_t*)((char*)found + 4);
                }
                pBatch->SetColor(color);

                mLineLayout.Clear(true);
                void* pLayout = mTypesetter.LayoutParagraph(
                    line->mText, line->mnLength, rect.x1, cur, rect.x2,
                    cur + (float)(unsigned)line->mnHeight, pStyle, &mLineLayout, (void*)0x14);
                pBatch->DrawText(mpDrawArg1, mpDrawArg2, pLayout);
            }
            cur = next;
            node = node->mpPrev;
            if (!(cur > mfInsetTop))
                break;
        }
    }

    ctx->End2D();
    return 1;
}
