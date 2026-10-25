// Slice s0096f3f0 - EA::UTFWinControls::FrameDrawable / GlideEffect / WinGrid
// (0x96f3f0..0x970540, 12 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region, see s0096c6f0).
//
// CreateRenderables (0x96f3f0, 2620 bytes) is a full 2D frame/outline renderer: it is
// reconstructed completely (all 11 style cases) but not instruction-exactly; see
// nonmatching.txt for the residual diff.  OnMouseMove (0x970460) updates the
// row-extra-data hash map and is likewise only approximated.

#include "types.h"
#include <intrin.h>

namespace EA {

namespace UTFWin {

struct RenderContext_s0096_f3f0 {
    RenderContext_s0096_f3f0* Begin2D(int mode);   // 0x0095bc10
    void End2D();                       // 0x0095bb20
};

// A float rectangle as used by the 2D drawing layer (left/top/right/bottom).
struct RectF_s96 {
    float mLeft;    // +0x00
    float mTop;     // +0x04
    float mRight;   // +0x08
    float mBottom;  // +0x0c
};

// The 2D canvas returned by RenderCtx::Begin2D; the frame renderer only needs slots
// +0x04 (solid colour) and +0x38 (axis-aligned rectangle).
struct Canvas_s96 {
    virtual void v00();                                        // +0x00
    virtual void SetColor(unsigned int color);                 // +0x04
    virtual void v08();                                        // +0x08
    virtual void v0c();                                        // +0x0c
    virtual void v10();                                        // +0x10
    virtual void v14();                                        // +0x14
    virtual void v18();                                        // +0x18
    virtual void v1c();                                        // +0x1c
    virtual void v20();                                        // +0x20
    virtual void v24();                                        // +0x24
    virtual void v28();                                        // +0x28
    virtual void v2c();                                        // +0x2c
    virtual void v30();                                        // +0x30
    virtual void v34();                                        // +0x34
    virtual void DrawRect(float l, float t, float r, float b); // +0x38
};

// The render context passed in the first stack slot (Begin2D entry point).
struct RenderCtx_s96 {
    Canvas_s96* Begin2D(int mode);                             // 0x0095bc10
};

// Frame description passed in the third stack slot.
struct FrameInfo_s96 {
    int          mStyleIndex;    // +0x00  index handed to FrameDrawable::GetStyle
    unsigned int mPad04;         // +0x04
    unsigned int mOutlineColor;  // +0x08  non-zero: stroke the outer rect first
};

// Style record returned by FrameDrawable::GetStyle.
struct FrameStyle_s96 {
    int          mStyle;         // +0x00  switch selector 0..10
    unsigned int mColor;         // +0x04  base colour, four Lerp variants are derived
    unsigned int mUnknown08;     // +0x08
    unsigned int mReserved[0x15];// +0x0c
    unsigned int mEdgeColor;     // +0x5c  slant-edge colour for styles 9 and 10
};

} // namespace UTFWin

namespace UTFWinControls {

// ---------------------------------------------------------------------------
// External helpers.
// ---------------------------------------------------------------------------
int   __cdecl FUN_009512c0();                                                  // 0x009512c0
void* __cdecl FUN_009512d0(int size, int align, const char* type, void* fac);  // 0x009512d0
void  __fastcall FadeEffect_ctor(void*);                                       // 0x00963db0
UTFWin::FrameStyle_s96* __fastcall FUN_0096f280(void* this_, int unused, int arg); // 0x0096f280
unsigned int __cdecl Color_Lerp(unsigned int a, unsigned int b, float t);       // 0x007f5eb0
void __cdecl Drawing_GradientBox(UTFWin::Canvas_s96* canvas,                    // 0x0095d540
                                 const float* outer, const float* inner,
                                 const float* colOuter, const float* colInner);
void __fastcall FUN_0096f1b0(UTFWin::Canvas_s96* canvas, float* unused,        // 0x0096f1b0
                             float* rect, float v);
double __cdecl iat_floor(double x);                                             // 0x011e0906

struct FloatSink {
    void Push(float* v);          // 0x0095e890
};

#define PV(n) virtual void pv##n()

// The sub-object embedded at WinGrid+0x20c; slots +0x78 (wheel) and +0x19c (mouse-move
// hit test) are used here.
struct WinGridSub {
    PV(0);PV(1);PV(2);PV(3);PV(4);PV(5);PV(6);PV(7);PV(8);PV(9);
    PV(10);PV(11);PV(12);PV(13);PV(14);PV(15);PV(16);PV(17);PV(18);PV(19);
    PV(20);PV(21);PV(22);PV(23);PV(24);PV(25);PV(26);PV(27);PV(28);PV(29);
    virtual void OnWheel(int delta);   // +0x78
    PV(31);PV(32);PV(33);PV(34);PV(35);PV(36);PV(37);PV(38);PV(39);
    PV(40);PV(41);PV(42);PV(43);PV(44);PV(45);PV(46);PV(47);PV(48);PV(49);
    PV(50);PV(51);PV(52);PV(53);PV(54);PV(55);PV(56);PV(57);PV(58);PV(59);
    PV(60);PV(61);PV(62);PV(63);PV(64);PV(65);PV(66);PV(67);PV(68);PV(69);
    PV(70);PV(71);PV(72);PV(73);PV(74);PV(75);PV(76);PV(77);PV(78);PV(79);
    PV(80);PV(81);PV(82);PV(83);PV(84);PV(85);PV(86);PV(87);PV(88);PV(89);
    PV(90);PV(91);PV(92);PV(93);PV(94);PV(95);PV(96);PV(97);PV(98);PV(99);
    PV(100);PV(101);PV(102);
    virtual bool OnHitTest(float x, float y, float* py, void* out);   // +0x19c
};

// The vtable reached through WinGrid+4 (the CustomWindow base); slots +0x90 and +0x114.
struct WinGridVt {
    PV(0);PV(1);PV(2);PV(3);PV(4);PV(5);PV(6);PV(7);PV(8);PV(9);
    PV(10);PV(11);PV(12);PV(13);PV(14);PV(15);PV(16);PV(17);PV(18);PV(19);
    PV(20);PV(21);PV(22);PV(23);PV(24);PV(25);PV(26);PV(27);PV(28);PV(29);
    PV(30);PV(31);PV(32);PV(33);PV(34);PV(35);
    virtual void OnSelChanged();          // +0x90
    PV(37);PV(38);PV(39);
    PV(40);PV(41);PV(42);PV(43);PV(44);PV(45);PV(46);PV(47);PV(48);PV(49);
    PV(50);PV(51);PV(52);PV(53);PV(54);PV(55);PV(56);PV(57);PV(58);PV(59);
    PV(60);PV(61);PV(62);PV(63);PV(64);PV(65);PV(66);PV(67);PV(68);
    virtual void OnInsert(void* iter);    // +0x114
};

// ---------------------------------------------------------------------------
// 0x0096fe30  EA::UTFWinControls::FrameDrawable::FrameDrawable
// ---------------------------------------------------------------------------
class FrameDrawable { public:
    void* vtbl;            // +0x00
    void* vtblSer;         // +0x04
    int   mRefCount;       // +0x08
    int   field0c;         // +0x0c
    int   field10;         // +0x10
    int   states[14];      // +0x14 .. +0x48
    float mBorderWidth[4]; // +0x4c .. +0x58
    int   mOutlineColor;   // +0x5c

    FrameDrawable();                                                        // 0x0096fe30
    void CreateRenderables(UTFWin::RenderCtx_s96* ctx,
                          const UTFWin::RectF_s96* pClip,
                          const UTFWin::FrameInfo_s96* pInfo);                  // 0x0096f3f0
};

// @ 0x0096fe30
FrameDrawable::FrameDrawable()
{
    const float one = *(const float*)0x01485720;
    *(void* volatile*)((char*)this + 4) = (void*)0x013fa72c;
    *(void**)((char*)this + 0) = (void*)0x014424d4;
    *(void* volatile*)((char*)this + 4) = (void*)0x014424bc;
    _ReadWriteBarrier();
    int zero = 0;
    *(int*)((char*)this + 8) = zero;
    *(float*)((char*)this + 0x4c) = one;
    *(float*)((char*)this + 0x50) = one;
    *(float*)((char*)this + 0x54) = one;
    *(float*)((char*)this + 0x58) = one;
    *(int*)((char*)this + 0x5c) = (int)0xff000000;
    *(int*)((char*)this + 0x18) = zero;
    *(int*)((char*)this + 0x14) = zero;
    *(int*)((char*)this + 0x20) = zero;
    *(int*)((char*)this + 0x1c) = zero;
    *(int*)((char*)this + 0x28) = zero;
    *(int*)((char*)this + 0x24) = zero;
    *(int*)((char*)this + 0x30) = zero;
    *(int*)((char*)this + 0x2c) = zero;
    *(int*)((char*)this + 0x38) = zero;
    *(int*)((char*)this + 0x34) = zero;
    *(int*)((char*)this + 0x40) = zero;
    *(int*)((char*)this + 0x3c) = zero;
    *(int*)((char*)this + 0x48) = zero;
    *(int*)((char*)this + 0x44) = zero;
    *(int*)((char*)this + 0x10) = -1;
    *(int*)((char*)this + 0x0c) = 2;
}

// The border-width block of FrameDrawable (+0x4c..+0x58) with per-edge names.
struct FrameBorderView_s96 {
    char  pad00[0x4c];
    float mBorderLeft;    // +0x4c
    float mBorderTop;     // +0x50
    float mBorderRight;   // +0x54
    float mBorderBottom;  // +0x58
};

// Colours are handed to the drawing layer as float slots holding the packed u32 bits.
static inline float s96_colorSlot(unsigned int color)
{
    union { unsigned int mBits; float mValue; } slot;
    slot.mBits = color;
    return slot.mValue;
}

// @ 0x0096f3f0
void FrameDrawable::CreateRenderables(UTFWin::RenderCtx_s96* ctx,
                                     const UTFWin::RectF_s96* pClip,
                                     const UTFWin::FrameInfo_s96* pInfo)
{
    UTFWin::Canvas_s96* canvas = ctx->Begin2D(0);
    canvas->SetColor(0xffffffffu);

    UTFWin::FrameStyle_s96* style = FUN_0096f280(this, 0, pInfo->mStyleIndex);

    // ---- border widths, clamped so that opposite borders never exceed the extent
    float borderLeft   = ((FrameBorderView_s96*)this)->mBorderLeft;
    float borderTop    = ((FrameBorderView_s96*)this)->mBorderTop;
    float borderRight  = ((FrameBorderView_s96*)this)->mBorderRight;
    float borderBottom = ((FrameBorderView_s96*)this)->mBorderBottom;

    float extentX = pClip->mRight - pClip->mLeft;
    if (extentX < borderLeft + borderRight) {
        float half = (float)iat_floor((double)(extentX * 0.5f));
        if (half < borderLeft)
            borderLeft = half;
        borderRight = extentX - borderLeft;
    }
    float extentY = pClip->mBottom - pClip->mTop;
    if (extentY < borderTop + borderBottom) {
        float half = (float)iat_floor((double)(extentY * 0.5f));
        if (half < borderTop)
            borderTop = half;
        borderBottom = extentY - borderTop;
    }

    // ---- inner (content) rect; style 9 shrinks it by one pixel on every side
    float innerLeft   = pClip->mLeft;
    float innerTop    = pClip->mTop;
    float innerRight  = pClip->mRight;
    float innerBottom = pClip->mBottom;
    if (style->mStyle == 9) {
        innerLeft   += 1.0f;
        innerTop    += 1.0f;
        innerRight  -= 1.0f;
        innerBottom -= 1.0f;
    }

    // ---- outer rect = inner rect grown by the border widths
    float outerLeft   = innerLeft + borderLeft;
    float outerTop    = innerTop + borderTop;
    float outerRight  = innerRight - borderRight;
    float outerBottom = innerBottom - borderBottom;

    float gradLeft   = outerLeft;
    float gradTop    = outerTop;
    float gradRight  = outerRight;
    float gradBottom = outerBottom;

    // style 10 additionally shrinks the stroked outer rect by one pixel
    if (style->mStyle == 10) {
        outerLeft   += 1.0f;
        outerTop    += 1.0f;
        outerRight  -= 1.0f;
        outerBottom -= 1.0f;
    }

    // ---- optional outline stroke of the (unshrunk) outer rect
    if (pInfo->mOutlineColor != 0) {
        canvas->SetColor(pInfo->mOutlineColor);
        canvas->DrawRect(gradLeft, gradTop, gradRight, gradBottom);
    }

    // ---- the four frame colours derived from the style colour
    unsigned int color = style->mColor;
    unsigned int darkLow  = Color_Lerp(color, color & 0xff000000u, 0.2f);
    unsigned int darkHigh = Color_Lerp(color, color & 0xff000000u, 0.6f);
    unsigned int litLow   = Color_Lerp(color, color | 0x00ffffffu, 0.2f);
    unsigned int litHigh  = Color_Lerp(color, color | 0x00ffffffu, 0.6f);

    float innerRect[4] = { innerLeft, innerTop, innerRight, innerBottom };
    float outerRect[4] = { outerLeft, outerTop, outerRight, outerBottom };
    // Two colour pairs as expected by Drawing::GradientBox (two packed colours per pair).
    float shadePair[4] = { s96_colorSlot(litLow), s96_colorSlot(litLow),
                           s96_colorSlot(litHigh), s96_colorSlot(litHigh) };
    float lightPair[4] = { s96_colorSlot(darkLow), s96_colorSlot(darkLow),
                           s96_colorSlot(darkHigh), s96_colorSlot(darkHigh) };

    switch (style->mStyle) {
    case 0:
    case 2: {
        // Flat frame: three solid bands plus a zero-height top edge.
        canvas->SetColor(color);
        canvas->DrawRect(innerLeft, innerTop, innerRight, outerTop);
        canvas->DrawRect(innerLeft, outerBottom, innerRight, innerBottom);
        canvas->DrawRect(innerLeft, outerTop, outerLeft, innerBottom);
        canvas->DrawRect(outerRight, outerTop, innerRight, innerBottom);
        break;
    }
    case 3:
    case 4: {
        // Dashed frame, dash length = scale * border width, two dash lengths per stride.
        float scale = (style->mStyle == 4) ? 3.0f : 1.0f;
        canvas->SetColor(color);

        float step = scale * borderTop;
        if (innerLeft + step <= innerRight) {
            float stride = step * 2.0f;
            float x = innerLeft;
            do {
                float end = x + step;
                if (end + step > innerRight)
                    end = innerRight;
                canvas->DrawRect(x, innerTop, end, outerTop);
                x = stride + x;
            } while (x <= innerRight);
        }

        step = scale * borderBottom;
        if (innerLeft + step <= innerRight) {
            float stride = step * 2.0f;
            float x = innerLeft;
            do {
                float end = x + step;
                if (end + step > innerRight)
                    end = innerRight;
                canvas->DrawRect(x, outerBottom, end, innerBottom);
                x = stride + x;
            } while (x <= innerRight);
        }

        step = scale * borderLeft;
        float y = step + outerTop;
        if (y <= outerBottom) {
            float stride = step * 2.0f;
            do {
                float end = y + step;
                if (end + step > outerBottom)
                    end = outerBottom;
                canvas->DrawRect(innerLeft, y, outerLeft, end);
                y = stride + y;
            } while (y <= outerBottom);
        }

        step = scale * borderRight;
        y = step + outerTop;
        if (y <= outerBottom) {
            float stride = step * 2.0f;
            do {
                float end = y + step;
                if (end + step > outerBottom)
                    end = outerBottom;
                canvas->DrawRect(outerRight, y, innerRight, end);
                y = stride + y;
            } while (y <= outerBottom);
        }
        break;
    }
    case 5:
        canvas->SetColor(0xffffffffu);
        Drawing_GradientBox(canvas, innerRect, outerRect, shadePair, lightPair);
        break;
    case 6:
        canvas->SetColor(0xffffffffu);
        Drawing_GradientBox(canvas, innerRect, outerRect, lightPair, shadePair);
        break;
    case 7:
    case 8: {
        // Two-stage gradient through the mid ring between the inner and outer rects.
        float midRect[4];
        midRect[0] = (outerLeft + innerLeft) * 0.5f;
        midRect[1] = (outerTop + innerTop) * 0.5f;
        midRect[2] = (outerRight + innerRight) * 0.5f;
        midRect[3] = (outerBottom + innerBottom) * 0.5f;
        canvas->SetColor(0xffffffffu);
        if (style->mStyle == 8) {
            Drawing_GradientBox(canvas, innerRect, midRect, lightPair, lightPair);
            Drawing_GradientBox(canvas, midRect, outerRect, shadePair, shadePair);
        } else {
            Drawing_GradientBox(canvas, innerRect, midRect, shadePair, shadePair);
            Drawing_GradientBox(canvas, midRect, outerRect, lightPair, lightPair);
        }
        break;
    }
    case 9:
        canvas->SetColor(0xffffffffu);
        Drawing_GradientBox(canvas, innerRect, outerRect, shadePair, lightPair);
        canvas->SetColor(style->mEdgeColor);
        FUN_0096f1b0(canvas, 0, innerRect, 1.0f);
        break;
    case 10:
        canvas->SetColor(0xffffffffu);
        Drawing_GradientBox(canvas, innerRect, outerRect, lightPair, shadePair);
        canvas->SetColor(style->mEdgeColor);
        FUN_0096f1b0(canvas, 0, outerRect, 1.0f);
        break;
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// GlideEffect (0x970010, 0x970060, 0x9700b0, 0x970100)
// ---------------------------------------------------------------------------
class GlideEffect { public:
    char  pad00[0x60];
    void* field60;         // +0x60
    float field64;         // +0x64
    float field68;         // +0x68

    void Set(float* src);                              // 0x00970060
    void Scale(void* a, FloatSink* obj, float scale);  // 0x00970010
};

// @ 0x00970060
void GlideEffect::Set(float* src)
{
    *(float*)((char*)this + 4) = src[0];
    *(float*)((char*)this + 8) = src[1];
}

// @ 0x00970010
void GlideEffect::Scale(void*, FloatSink* obj, float scale)
{
    float local[3];
    local[0] = *(float*)((char*)this + 0x64) * scale;
    local[1] = *(float*)((char*)this + 0x68) * scale;
    local[2] = 0.0f;
    obj->Push(local);
}

// @ 0x009700b0
void* __fastcall FUN_009700b0(char* param_1)
{
    FadeEffect_ctor(param_1);
    const float zero = 0.0f;
    *(void* volatile*)(param_1 + 0x60) = (void*)0x014426a0;
    *(void**)(param_1 + 0) = (void*)0x014425d8;
    *(void**)(param_1 + 4) = (void*)0x014425c0;
    *(void**)(param_1 + 0x0c) = (void*)0x01442584;
    *(void* volatile*)(param_1 + 0x60) = (void*)0x014426bc;
    *(float*)(param_1 + 0x64) = zero;
    *(float*)(param_1 + 0x68) = zero;
    return param_1;
}

// @ 0x00970100
class BasicFactory_GlideEffect { public:
    void* CreateInstance(int param1, void* param2);
};

// @ 0x00970100
void* BasicFactory_GlideEffect::CreateInstance(int, void* param2)
{
    if (param2 == 0)
        param2 = (void*)FUN_009512c0();
    char* obj = (char*)FUN_009512d0(0x70, 8,
                                    "UTFWin/EA::UTFWinControls::GlideEffect", param2);
    if (obj != 0) {
        FadeEffect_ctor(obj);
        const float zero = 0.0f;
        *(void* volatile*)(obj + 0x60) = (void*)0x014426a0;
        *(void**)(obj + 0) = (void*)0x014425d8;
        *(void**)(obj + 4) = (void*)0x014425c0;
        *(void**)(obj + 0x0c) = (void*)0x01442584;
        *(void* volatile*)(obj + 0x60) = (void*)0x014426bc;
        *(float*)(obj + 0x64) = zero;
        *(float*)(obj + 0x68) = zero;
        return obj;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x970190 / 0x9701c0 / 0x970210  EA::UTFWinControls::IWinGrid::CellFormat
// ---------------------------------------------------------------------------
namespace IWinGrid {

struct CellFormat {
    int  nTextStyle;       // +0x00
    int  nColor[8];        // +0x04 .. +0x20
    char nWrapping;        // +0x24
    char nHAlignment;      // +0x25
    char nVAlignment;      // +0x26
    char field27;          // +0x27
    int  nBorder;          // +0x28
    int  nBorderColor;     // +0x2c
    float field30;         // +0x30
    float field34;         // +0x34

    CellFormat();                              // 0x00970190
    CellFormat* InitInvalid();                 // 0x009701c0
    CellFormat* InitFrom(const void* src);     // 0x00970210
};

// @ 0x00970190
CellFormat::CellFormat()
{
    nTextStyle = 0;
    *(char*)((char*)this + 0x24) = (char)0xff;
    *(char*)((char*)this + 0x25) = 0;
    *(char*)((char*)this + 0x26) = 0;
    nBorder = 0;
    nBorderColor = 0;
    nColor[0] = 0;
    nColor[1] = 0;
    nColor[2] = 0;
    nColor[3] = 0;
    nColor[6] = 0;
    nColor[7] = 0;
    nColor[4] = 0;
    nColor[5] = 0;
}

// @ 0x009701c0
CellFormat* CellFormat::InitInvalid()
{
    const float fNegOne = *(const float*)0x013eb1bc;
    *(int*)((char*)this + 0) = 0;
    *(char*)((char*)this + 0x24) = (char)0xff;
    *(char*)((char*)this + 0x25) = 0;
    *(char*)((char*)this + 0x26) = 0;
    *(int*)((char*)this + 0x28) = 0;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 4) = 0;
    *(int*)((char*)this + 8) = 0;
    *(int*)((char*)this + 0x0c) = 0;
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x1c) = 0;
    *(int*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x18) = 0;
    *(float*)((char*)this + 0x30) = fNegOne;
    *(float*)((char*)this + 0x34) = fNegOne;
    return this;
}

// @ 0x00970210
CellFormat* CellFormat::InitFrom(const void* src)
{
    const float fNegOne = *(const float*)0x013eb1bc;
    *(int*)((char*)this + 0) = 0;
    *(char*)((char*)this + 0x25) = 0;
    *(char*)((char*)this + 0x26) = 0;
    *(int*)((char*)this + 0x28) = 0;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 4) = 0;
    *(int*)((char*)this + 8) = 0;
    *(int*)((char*)this + 0x0c) = 0;
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x1c) = 0;
    *(int*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x18) = 0;
    *(char*)((char*)this + 0x24) = (char)0xff;
    *(float*)((char*)this + 0x30) = fNegOne;
    *(float*)((char*)this + 0x34) = fNegOne;
    memcpy(this, src, 0x30);
    return this;
}

} // namespace IWinGrid

// ---------------------------------------------------------------------------
// 0x009702b0  EA::UTFWinControls::WinGrid::SetDefaultFormatting
// ---------------------------------------------------------------------------
class WinGrid { public:
    char sub20c[0x20c];

    void SetDefaultFormatting();                                    // 0x009702b0
    void OnMouseWheel(int, int, int, int delta);                    // 0x00970540
    virtual bool OnMouseMove(float x, float y, unsigned int param); // 0x00970460
};

// @ 0x009702b0
void WinGrid::SetDefaultFormatting()
{
    char* ecx = (char*)this;
    unsigned edx = 0;
    const int esi = (int)0xff000000;
    int eax = -1;

    if (*(int*)(ecx + 0x354) == (int)edx) *(int*)(ecx + 0x354) = esi;
    if (*(int*)(ecx + 0x358) == (int)edx) *(int*)(ecx + 0x358) = eax;
    if (*(int*)(ecx + 0x364) == (int)edx) *(int*)(ecx + 0x364) = eax;
    if (*(int*)(ecx + 0x368) == (int)edx) *(int*)(ecx + 0x368) = esi;
    if (*(int*)(ecx + 0x36c) == (int)edx) *(int*)(ecx + 0x36c) = eax;
    if (*(int*)(ecx + 0x370) == (int)edx) *(int*)(ecx + 0x370) = esi;
    if (*(int*)(ecx + 0x35c) == (int)edx) *(int*)(ecx + 0x35c) = (int)0xffc0c0c0;
    if (*(int*)(ecx + 0x360) == (int)edx) *(int*)(ecx + 0x360) = eax;
    if (*(unsigned char*)(ecx + 0x374) == 0xff) *(unsigned char*)(ecx + 0x374) = 1;
    if (*(unsigned char*)(ecx + 0x375) == (unsigned char)edx) *(unsigned char*)(ecx + 0x375) = 2;
    if (*(unsigned char*)(ecx + 0x376) == (unsigned char)edx) *(unsigned char*)(ecx + 0x376) = 6;
    if (*(int*)(ecx + 0x378) == (int)edx) *(int*)(ecx + 0x378) = edx;
    if (*(int*)(ecx + 0x37c) == (int)edx) *(int*)(ecx + 0x37c) = esi;
    if (*(int*)(ecx + 0x458) == (int)edx) *(int*)(ecx + 0x458) = esi;
    if (*(int*)(ecx + 0x45c) == (int)edx) *(int*)(ecx + 0x45c) = eax;
    if (*(int*)(ecx + 0x468) == (int)edx) *(int*)(ecx + 0x468) = esi;
    eax = (int)0xffdcdcff;
    if (*(int*)(ecx + 0x46c) == (int)edx) *(int*)(ecx + 0x46c) = eax;
    if (*(int*)(ecx + 0x470) == (int)edx) *(int*)(ecx + 0x470) = esi;
    if (*(int*)(ecx + 0x474) == (int)edx) *(int*)(ecx + 0x474) = eax;
    if (*(int*)(ecx + 0x460) == (int)edx) *(int*)(ecx + 0x460) = (int)0xff808080;
    if (*(int*)(ecx + 0x464) == (int)edx) *(int*)(ecx + 0x464) = (int)0xffdcdcdc;
    if (*(unsigned char*)(ecx + 0x478) == 0xff) *(unsigned char*)(ecx + 0x478) = 1;
    if (*(unsigned char*)(ecx + 0x479) == (unsigned char)edx) *(unsigned char*)(ecx + 0x479) = 2;
    if (*(unsigned char*)(ecx + 0x47a) == (unsigned char)edx) *(unsigned char*)(ecx + 0x47a) = 6;
    if (*(int*)(ecx + 0x47c) == (int)edx) *(int*)(ecx + 0x47c) = edx;
    if (*(int*)(ecx + 0x480) == (int)edx) *(int*)(ecx + 0x480) = esi;
    *(int*)(ecx + 0x274) = esi;
    *(int*)(ecx + 0x278) = esi;
    *(int*)(ecx + 0x27c) = esi;
}

// @ 0x00970540
void WinGrid::OnMouseWheel(int, int, int, int delta)
{
    ((WinGridSub*)((char*)this + 0x20c))->OnWheel(delta / -100);
}

// @ 0x00970460
bool WinGrid::OnMouseMove(float x, float y, unsigned int param)
{
    char* base = (char*)this;

    // 0x30-byte scratch frame: first the hit-test output, then the row-extra-data
    // key / node passed to the inlined hashtable insert.
    struct Row {
        unsigned k0, k1;             // +0x00 .. +0x04  (hit-test output)
        unsigned key0, key1, key2;   // +0x08 .. +0x10  (map key)
        unsigned it0, it1;           // +0x14 .. +0x18  (insert iterator result)
        unsigned hash;               // +0x1c
        void*    value;              // +0x20
        unsigned pad0, pad1;         // +0x24 .. +0x28
        void*    keyPtr;             // +0x2c
    } row;

    WinGridSub* sub = (WinGridSub*)(base + 0x20c);
    if (!sub->OnHitTest(x, y, &y, &row))
        return false;

    unsigned a = *(unsigned*)&y;
    unsigned b = row.k0;
    unsigned c = row.k1;
    if (a == *(unsigned*)(base + 0x3a8) &&
        b == *(unsigned*)(base + 0x3ac) &&
        c == *(unsigned*)(base + 0x3b0))
        return true;

    row.key0 = a;
    *(unsigned*)(base + 0x3a8) = a;
    row.key1 = b;
    row.key2 = c;
    *(unsigned*)(base + 0x3ac) = b;
    *(unsigned*)(base + 0x3b0) = c;
    row.hash = 0x9a1552d6;
    void* v = *(void**)(base + 0x84);
    row.value = v ? v : *(void**)(base + 0x80);
    row.keyPtr = &row.key0;

    WinGridVt* vt = (WinGridVt*)(base + 4);
    vt->OnInsert(&row.it0);
    vt->OnSelChanged();
    return true;
}

} // namespace UTFWinControls

} // namespace EA
