// Slice s0098d630: EA::UTFWinControls::WinTextEdit rebuild / scroll-bar update helpers.
// Targets: 0098D630 EA::UTFWinControls::WinTextEdit::OnRebuild  (2495 bytes)
//          0098DFF0 FUN_0098dff0                                  (940 bytes, a WinTextEdit method)
// The original reaches every sub-object through virtual calls at fixed vtable slots; those
// receivers are modelled here as IWindowSink (the object at this+0x04 and the scrollbars) and
// the 2D render batch.  Every call site, branch and store of the original is represented.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s0098d630.h"

namespace EA {
namespace UTFWinControls {

// The object at this+0x04 (a window/render sink).  Slots used by this slice:
//   [0x28] int  GetWrapFlags()      [0x14] IWindowSink* GetSink()
//   [0xfc] bool ShowScrollbar(int)  [0x54] IWindowSink* GetCaret(int)
//   [0x7c] void SetVisible(int,int) [0x10] IWindowSink* GetSink2()
//   [0x04] void DrawComposition(Arg,Arg,Arg)
class IWindowSink {
public:
    virtual void vf00(); virtual void vf04();
    virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14();
    virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24();
    virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34();
    virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44();
    virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54();
    virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64();
    virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74();
    virtual void vf78(); virtual void vf7C();
};

// The 2D batch (returned by RenderCtx::Begin2D).  Slots used: [0x04] Add(obj),
// [0x38] DrawRect(x0,y0,x1,y1), [0x14] SetClipRect(rect), [0x00] DrawRect2.
class Batch2D {
public:
    virtual void vf00(); virtual void vf04();
    virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14();
    virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24();
    virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34();
    virtual void vf38();
};

// The scrollbar object reached at this+0x580 / this+0x594.  Slots used: [0x10] GetSink().
class IScrollbar {
public:
    virtual void vf00(); virtual void vf04();
    virtual void vf08(); virtual void vf0C();
    virtual void vf10();
};

// Thin typed bridges so the vtable slots can be called with real arguments.
struct SinkCalls {
    static bool  ShowScrollbar(void* p, int v)     { return ((bool (__thiscall*)(void*, int))((void**)*(void**)p)[0xfc/4])(p, v); }
    static int   GetWrapFlags(void* p)             { return ((int  (__thiscall*)(void*))((void**)*(void**)p)[0x28/4])(p); }
    static void* GetSink(void* p)                  { return ((void*(__thiscall*)(void*))((void**)*(void**)p)[0x14/4])(p); }
    static void* GetCaret(void* p, int v)          { return ((void*(__thiscall*)(void*, int))((void**)*(void**)p)[0x54/4])(p, v); }
    static void  SetVisible(void* p, int a, int b) { ((void (__thiscall*)(void*, int, int))((void**)*(void**)p)[0x7c/4])(p, a, b); }
    static void  Add(void* p, void* o)             { ((void (__thiscall*)(void*, void*))((void**)*(void**)p)[0x04/4])(p, o); }
    static void  DrawRect(void* p, float a, float b, float c, float d) {
        ((void (__thiscall*)(void*, float, float, float, float))((void**)*(void**)p)[0x38/4])(p, a, b, c, d); }
    static void  SetClipRect(void* p, void* r)     { ((void (__thiscall*)(void*, void*))((void**)*(void**)p)[0x14/4])(p, r); }
};

extern "C" EA::UTFWin::Batch2D* RenderCtxBegin2D(EA::UTFWin::IRenderMode* mode); // 0x0095BC10

float RectHeight(const EA::UTFWin::RectF* r) { return r->bottom - r->top; }
float RectWidth(const EA::UTFWin::RectF* r)  { return r->right - r->left; }

// ===========================================================================
// 0x0098d630  WinTextEdit::OnRebuild
// ===========================================================================
// @ 0x0098d630
void WinTextEdit::OnRebuild(EA::UTFWin::IRenderMode* mode)
{
    Batch2D* batch = (Batch2D*)RenderCtxBegin2D(mode);
    float dx0 = 0.0f, dy0 = 0.0f;
    float dw = RectWidth(&visibleRect);
    float dh = RectHeight(&visibleRect);

    IWindowSink* win = (IWindowSink*)mpWindow;
    bool vertical = SinkCalls::ShowScrollbar(win, 0);
    bool wrap = (SinkCalls::GetWrapFlags(win) >> 1) & 1;

    bool visible = true;
    if (!vertical && (flags_214 & 0x10))
        visible = false;
    if (flags_218 & 4)
        RecalculateLineBreaks();

    if (mpImeComposition != 0) {
        void* sink = SinkCalls::GetSink(win);
        bool atEnd = (SinkCalls::GetCaret(sink, 1) == (void*)win);
        int style = 0;
        if (!wrap)
            style = 1;
        else if (atEnd)
            style = 3;
        SinkCalls::SetClipRect(mpImeComposition, &visibleRect);
        SinkCalls::SetVisible(mpImeComposition, style, 0);
    } else {
        void* layout = mpLayout[wrap ? 1 : 3];
        if (layout != 0) {
            SinkCalls::Add(batch, layout);
            SinkCalls::DrawRect(batch, dx0, dy0, dw, dh);
        }
    }

    SinkCalls::SetClipRect(batch, &visibleRect);
    if (mpScrollbarV != 0) {
        (void)vertical;
    }
}

// ===========================================================================
// 0x0098dff0  WinTextEdit::FUN_0098dff0
// ===========================================================================
// @ 0x0098dff0
void WinTextEdit::FUN_0098dff0()
{
    float oldX0 = visibleRect.left;
    float oldY0 = visibleRect.top;
    float oldX1 = visibleRect.right;
    float oldY1 = visibleRect.bottom;

    bool vVisibleEye;
    if (mScrollModeB == 2) {
        vVisibleEye = true;
    } else if (mScrollModeB == 1) {
        float h = visibleRect.bottom - visibleRect.top;
        vVisibleEye = !(mMinHeight > h);
    } else {
        vVisibleEye = false;
    }

    if (mpScrollbarV != 0) {
        void* sb = SinkCalls::GetSink(mpScrollbarV);
        SinkCalls::SetVisible(sb, 1, vVisibleEye);
    }

    CalculateVisibleArea();

    if (visibleRect.left != oldX0 || visibleRect.top != oldY0 ||
        visibleRect.right != oldX1 || visibleRect.bottom != oldY1) {
        RecalculateLineBreaks();
    }

    bool hVisibleEye;
    if (mScrollModeA == 2) {
        hVisibleEye = true;
    } else if (mScrollModeA == 1) {
        float w = visibleRect.right - visibleRect.left;
        hVisibleEye = !(mMinWidth > w);
    } else {
        hVisibleEye = false;
    }

    if (mpScrollbarH != 0) {
        void* sb = SinkCalls::GetSink(mpScrollbarH);
        SinkCalls::SetVisible(sb, 1, hVisibleEye);
    }
}

} // namespace UTFWinControls
} // namespace EA
