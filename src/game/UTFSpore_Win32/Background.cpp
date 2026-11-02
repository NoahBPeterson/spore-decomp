// src/game/UTFSpore_Win32/Background.cpp -- migrated from slice(s) s008e6340, s008e5320 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Background.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include "EA/XHTML/Layout/Page.h"
#include <math.h>

// ---- items of slice s008e5320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectF {
    float x0, y0, x1, y1;
    bool Intersect(const RectF& a, const RectF& b);  // 0x00634b60
};
// ---- items of slice s008e5320 end

// ---- items of slice s008e6340 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
template <typename T>
class RectT_s008e_6340 { public:
    T mLeft, mTop, mRight, mBottom;
    RectT_s008e_6340() {}
    RectT_s008e_6340(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT_s008e_6340(const RectT_s008e_6340& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT_s008e_6340& operator=(const RectT_s008e_6340& x)
    {
        mLeft = x.mLeft; mTop = x.mTop; mRight = x.mRight; mBottom = x.mBottom;
        return *this;
    }
    T Width() const { return mRight - mLeft; }
    T Height() const { return mBottom - mTop; }
};
}
namespace EA {
template <typename T>
struct SizeT {
    T w, h;
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};
}
namespace EA {
template <typename T>
class Point2DT { public:
    T mX, mY;
    Point2DT() {}
    Point2DT(T x, T y) : mX(x), mY(y) {}
};
}
namespace EA {
namespace COM {
class IUnknown32_s008e_6340 {
public:
    virtual void v00();                                      // +0x0
    virtual void v04();                                      // +0x4
    virtual void v08();                                      // +0x8
    virtual IUnknown32_s008e_6340* AsInterface(uint32_t interfaceId);   // +0xc
};  // namespace COM
}
}
namespace EA {
namespace XHTML {
namespace Text {
class Typesetter {
public:
    ~Typesetter();
    uint32_t mData[0x530 / 4];
};  // namespace Text
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum Units { kUnitsPixels = 1, kUnitsPercentage = 9, kUnitsAuto = 10 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum BackgroundRepeat { kNoRepeat = 0, kRepeatX = 1, kRepeatY = 2, kRepeatXY = 3 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum BackgroundAttachment { kBackgroundScroll = 0, kBackgroundFixed = 1 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class FontMetrics { public:
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length {
    float mValue;   // +0
    int mUnits;     // +4
    float ToPixels(float reference, const FontMetrics& fm) const;   // 0x008f95c0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct ParagraphStyle {
    uint32_t mData[2];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState {
public:
    StyleState* mpBase;                    // +0x0
    uint32_t pad004[(0x2a0 - 0x4) / 4];
    const wchar_t* mpBackgroundImage;      // +0x2a0
    int mBackgroundRepeat;                 // +0x2a4
    int mBackgroundAttachment;             // +0x2a8
    Length mBackgroundPosX;                // +0x2ac
    Length mBackgroundPosY;                // +0x2b4
    uint32_t pad2bc[(0x374 - 0x2bc) / 4];
    Length mBoxHeight;                     // +0x374  (units at +0x378)
    uint32_t pad37c[(0x430 - 0x37c) / 4];
    FontMetrics mFontMetrics;              // +0x430
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_6340;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Background;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ImageRequester {
public:
    virtual void r00();
    void* mpNextLoading;    // +0x4
    uint32_t mnJobId;       // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_6340 {
public:
    COM::IUnknown32_s008e_6340* GetResource(unsigned int index);                    // 0x008eb960
    void LoadImage(ImageRequester* pRequester, const wchar_t* pURL);     // 0x008ec5e0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext {
public:
    void* mpDC;                            // +0x0
    Text::Typesetter mTypesetter;          // +0x4 (0x530 bytes)
    RectT_s008e_6340<float> mContextRect;             // +0x534
    RectT_s008e_6340<float> mViewRect;                // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c

    void SetContextRectRelative(float l, float t, float r, float b);     // 0x008eedb0
    void Fn8ee7a0(int arg);                                              // 0x008ee7a0
    void Fn8ee770(Style::ParagraphStyle* pOut);                          // 0x008ee770
    void SetParagraphStyle(const Style::ParagraphStyle& ps);             // 0x008ee740
    void Fn8eec80(float l, float t, float r, float b, void* p);          // 0x008eec80
    void Fn8ef6d0();                                                     // 0x008ef6d0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Background : public ImageRequester {
public:
    bool Draw(RenderingContext& ctx, const RectT_s008e_6340<float>& pen, const RectT_s008e_6340<float>& rect);   // 0x008e6710
    void SetStyle(Style::StyleState& style);                                               // 0x008e68f0

    Page_s008e_6340* mpPage;                          // +0xc
    unsigned int mImageTableIndex;         // +0x10
    const wchar_t* mpImageURL;             // +0x14
    Style::BackgroundRepeat mRepeat;       // +0x18
    int mAttachment;                       // +0x1c
    Style::Length mPosX;                   // +0x20
    Style::Length mPosY;                   // +0x28
    Style::FontMetrics mFontMetrics;       // +0x30
    bool mbDraw;                           // +0x44
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void Fn8e61b0(void** pp, RectT_s008e_6340<float> r, void* p6, RectT_s008e_6340<float>* p7);
}
}
}
// ---- items of slice s008e6340 end

// @ 0x008e61b0
void Fn8e61b0(void** pp, RectF r, void* p6, RectF* p7)
{
    if (p7->x0 <= r.x0 && r.x1 <= p7->x1 && p7->y0 <= r.y0 && r.y1 <= p7->y1) {
        RectF out;
        out.x0 = 0.0f;
        out.y0 = 0.0f;
        out.x1 = 1.0f;
        out.y1 = 1.0f;
        (*(void (__thiscall**)(void*, const RectF*, void*, RectF*))
             ((*(int*)*pp) + 0x58))(*pp, &r, p6, &out);
        return;
    }
    float w = r.x1 - r.x0;
    float h = r.y1 - r.y0;
    if (w >= 1.0f && h >= 1.0f) {
        RectF inter = r;
        inter.Intersect(r, *p7);
        if (inter.x0 != inter.x1 && inter.y0 != inter.y1) {
            float u = 1.0f / w;
            float v = 1.0f / h;
            RectF out;
            out.x0 = (inter.x0 - r.x0) * u;
            out.y0 = (inter.y0 - r.y0) * v;
            out.x1 = (inter.x1 - r.x0) * u;
            out.y1 = (inter.y1 - r.y0) * v;
            (*(void (__thiscall**)(void*, const RectF*, void*, RectF*))
                 ((*(int*)*pp) + 0x58))(*pp, &inter, p6, &out);
        }
    }
}

// @ 0x008e6340
namespace EA { namespace XHTML { namespace Layout {
void BltTiled(RenderingContext& ctx, RectT_s008e_6340<float> rect, COM::IUnknown32_s008e_6340* pImage, Point2DT<float> scale, Point2DT<float> offset, Style::BackgroundRepeat repeat)
{
    if (pImage == 0)
        return;

    SizeT<int>* pSize = (SizeT<int>*)pImage->AsInterface(0x2f84737);
    if (pSize == 0)
        return;

    float tileW = scale.mX * (float)pSize->w;
    float tileH = scale.mY * (float)pSize->h;
    if (tileW < 1.0f)
        return;
    if (tileH < 1.0f)
        return;

    if (repeat == Style::kRepeatX || repeat == Style::kRepeatXY) {
        if (offset.mX > 0.0f) {
            offset.mX -= (float)ceil((double)offset.mX / (double)tileW) * tileW;
        } else if (tileW >= offset.mX) {
            offset.mX = (float)floor(-((double)offset.mX / (double)tileW)) * tileW + offset.mX;
        }
    }
    if (repeat == Style::kRepeatY || repeat == Style::kRepeatXY) {
        if (offset.mY > 0.0f) {
            offset.mY -= (float)ceil((double)offset.mY / (double)tileH) * tileH;
        } else if (tileH >= offset.mY) {
            offset.mY = (float)floor(-((double)offset.mY / (double)tileH)) * tileH + offset.mY;
        }
    }

    rect.mLeft += ctx.mContextRect.mLeft;
    rect.mTop += ctx.mContextRect.mTop;
    rect.mRight += ctx.mContextRect.mLeft;
    rect.mBottom += ctx.mContextRect.mTop;

    float x = rect.mLeft + offset.mX;
    float y = rect.mTop + offset.mY;

    switch (repeat) {
    case Style::kNoRepeat:
        Fn8e61b0((void**)&ctx, RectT_s008e_6340<float>(x, y, x + tileW, y + tileH), pImage, &rect);
        break;
    case Style::kRepeatX:
        for (float cx = x; cx < rect.mRight; cx += tileW)
            Fn8e61b0((void**)&ctx, RectT_s008e_6340<float>(cx, y, cx + tileW, y + tileH), pImage, &rect);
        break;
    case Style::kRepeatY:
        // Retail (and dev) bug: y is never advanced inside the loop, so once entered this
        // degenerate loop re-blits the same tile forever.  Kept verbatim to match the bytes.
        for (float cy = y; cy < rect.mBottom; )
            Fn8e61b0((void**)&ctx, RectT_s008e_6340<float>(x, cy, x + tileW, cy + tileH), pImage, &rect);
        break;
    case Style::kRepeatXY:
        for (float cy = y; cy < rect.mBottom; cy += tileH)
            for (float cx = x; cx < rect.mRight; cx += tileW)
                Fn8e61b0((void**)&ctx, RectT_s008e_6340<float>(cx, cy, cx + tileW, cy + tileH), pImage, &rect);
        break;
    }
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008e6710
namespace EA { namespace XHTML { namespace Layout {
bool Background::Draw(RenderingContext& ctx, const RectT_s008e_6340<float>& pen, const RectT_s008e_6340<float>& rect)
{
    if (!mbDraw)
        return false;
    if (rect.mLeft == rect.mRight)
        return false;
    if (rect.mTop == rect.mBottom)
        return false;

    COM::IUnknown32_s008e_6340* pRes = mpPage->GetResource(mImageTableIndex);
    if (pRes == 0)
        return false;
    COM::IUnknown32_s008e_6340* pImage = pRes->AsInterface(0xee3f516e);
    if (pImage == 0)
        return false;
    SizeT<int>* pSize = (SizeT<int>*)pImage->AsInterface(0x2f84737);
    if (pSize == 0)
        return false;

    float w = (rect.mRight - rect.mLeft) - (float)pSize->w;
    float x;
    if (mPosX.mUnits == Style::kUnitsAuto)
        x = w * 0.5f;
    else
        x = mPosX.ToPixels(w, mFontMetrics);

    float h = (rect.mBottom - rect.mTop) - (float)pSize->h;
    float y;
    if (mPosY.mUnits == Style::kUnitsAuto)
        y = h * 0.5f;
    else
        y = mPosY.ToPixels(h, mFontMetrics);

    x = (float)floor((double)x);
    y = (float)floor((double)y);

    if (mAttachment == Style::kBackgroundFixed) {
        x -= pen.mLeft;
        y -= pen.mTop;
    }

    ctx.Fn8ee7a0(-1);
    BltTiled(ctx, rect, pImage, Point2DT<float>(1.0f, 1.0f), Point2DT<float>(x, y), mRepeat);
    return true;
}
}}}  // namespace EA::XHTML::Layout
