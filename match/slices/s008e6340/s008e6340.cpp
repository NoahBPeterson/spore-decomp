// Slice s008e6340 -- EA::XHTML::Layout background tiling + Block/ContainerItem drawing helpers
// (EA XHTML layout engine: Image/BltTiled.cpp, Background.cpp, Block.cpp, ListItem.cpp).
//
//  0x008e6340 BltTiled             -- tiles an image over a rect (BackgroundRepeat mode switch)
//  0x008e6710 Background::Draw     -- positions + blits a background image for a box
//  0x008e68f0 Background::SetStyle -- pulls the background style out of a StyleState, starts a load
//  0x008e69b0 Fn8e69b0             -- builds a small hit-test target from a node + a point
//  0x008e6a20 Block::DrawContent   -- draws a control/content element or the children
//  0x008e6b70 Block::PickContent   -- hit-tests a point against a block, then its children
//  0x008e6c60 Block::PlaceControls -- offsets rects the element wants placed (controls)
//  0x008e6d30 Block::Layout        -- places a block in a StackingContext and grows its bounds
//
// Retail layouts: EA::Text::Typesetter is 0x530 bytes in retail (0x548 in the 2008 dev PDB), so
// members after it in RenderingContext/PickingContext/StackingContext sit 0x18 lower than the PDB
// documents.  Background derives from ImageRequester (vftable +0, mpNextLoading +4, mnJobId +8),
// so mpPage is at +0xc and the background style block at +0x14.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc: no EH frame on the locals here).
#include "types.h"
#include <math.h>

namespace EA {

template <typename T>
struct RectT {
    T mLeft, mTop, mRight, mBottom;
    RectT() {}
    RectT(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    RectT(const RectT& x) : mLeft(x.mLeft), mTop(x.mTop), mRight(x.mRight), mBottom(x.mBottom) {}
    RectT& operator=(const RectT& x)
    {
        mLeft = x.mLeft; mTop = x.mTop; mRight = x.mRight; mBottom = x.mBottom;
        return *this;
    }
    T Width() const { return mRight - mLeft; }
    T Height() const { return mBottom - mTop; }
};

template <typename T>
struct SizeT {
    T w, h;
    SizeT(T aw, T ah) : w(aw), h(ah) {}
};

template <typename T>
struct Point2DT {
    T mX, mY;
    Point2DT() {}
    Point2DT(T x, T y) : mX(x), mY(y) {}
};

namespace COM {
// EA::COM::IUnknown32 (src/game/include/EA/COM/IUnknown32.h): vtable slot +0xc is AsInterface.
class IUnknown32 {
public:
    virtual void v00();                                      // +0x0
    virtual void v04();                                      // +0x4
    virtual void v08();                                      // +0x8
    virtual IUnknown32* AsInterface(uint32_t interfaceId);   // +0xc
};
}  // namespace COM

namespace XHTML {

namespace Text {
class Typesetter {
public:
    ~Typesetter();
    uint32_t mData[0x530 / 4];
};
}  // namespace Text

namespace Style {

enum Units { kUnitsPixels = 1, kUnitsPercentage = 9, kUnitsAuto = 10 };
enum BackgroundRepeat { kNoRepeat = 0, kRepeatX = 1, kRepeatY = 2, kRepeatXY = 3 };
enum BackgroundAttachment { kBackgroundScroll = 0, kBackgroundFixed = 1 };

struct FontMetrics {
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};

struct Length {
    float mValue;   // +0
    int mUnits;     // +4
    float ToPixels(float reference, const FontMetrics& fm) const;   // 0x008f95c0
};

struct ParagraphStyle {
    uint32_t mData[2];
};

class Rule;

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

}  // namespace Style

namespace DOM {
// XHTML DOM node/element.  vtable: +0xc AsInterface (IUnknown32), +0x10 GetIntrinsicSize,
// +0x14/+0x18 predicates, +0x20 rect sink.  Type()/Parent() are non-virtual (0xfc7e50 / 0xff0420).
class Element {
public:
    virtual void v00();                                    // +0x00
    virtual void v04();                                    // +0x04
    virtual void v08();                                    // +0x08
    virtual void v0c();                                    // +0x0c
    virtual void GetIntrinsicSize(SizeT<float>* pSize);    // +0x10
    virtual bool v14();                                    // +0x14
    virtual bool v18();                                    // +0x18
    virtual void v1c();                                    // +0x1c
    virtual void v20(RectT<float>* pRect);                 // +0x20

    int Type();                                            // 0x00fc7e50
    Element* Parent();                                     // 0x00ff0420
    int Fn8e42d0();                                        // 0x008e42d0

    char mPad[0x3c];                                       // +0x04..+0x3f
    void* mpDocument;                                      // +0x40
};
}  // namespace DOM

namespace Layout {

class Page;
class Background;
class Block;
class Item;
class ContainerItem;
class RenderingContext;
class PickingContext;
class StackingContext;
class SizingContext;

class ImageRequester {
public:
    virtual void r00();
    void* mpNextLoading;    // +0x4
    uint32_t mnJobId;       // +0x8
};

class Page {
public:
    COM::IUnknown32* GetResource(unsigned int index);                    // 0x008eb960
    void LoadImage(ImageRequester* pRequester, const wchar_t* pURL);     // 0x008ec5e0
};

class RenderingContext {
public:
    void* mpDC;                            // +0x0
    Text::Typesetter mTypesetter;          // +0x4 (0x530 bytes)
    RectT<float> mContextRect;             // +0x534
    RectT<float> mViewRect;                // +0x544
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

class PickingContext {
public:
    uint32_t mData0[0x538 / 4];            // +0x0
    Point2DT<float> mRelPos;               // +0x538
    void* mpElement;                       // +0x540
    RectT<float> mContextRect;             // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c

    void SetContextRectRelative(float l, float t, float r, float b);     // 0x008edeb0
    void Fn8edd80(Style::ParagraphStyle* pOut);                          // 0x008edd80
    void Fn8edd50(const Style::ParagraphStyle& ps);                      // 0x008edd50
    bool Fn8ee4a0(void* p);                                              // 0x008ee4a0
};

class Item {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void MeasureContent(SizingContext& sc, Style::StyleState& style);   // +0x20
    virtual void LayoutChildren(StackingContext& sc, Style::StyleState& style); // +0x24
    virtual void PlaceControl(RectT<float>* pRect);                             // +0x28
    virtual void v0b(); virtual void v0c();
    virtual void Layout(StackingContext& sc, Style::StyleState& style);         // +0x34

    void* mpNext;                          // +0x4
    void* mpPrev;                          // +0x8
    Page* mpPage;                          // +0xc
    int mItemType;                         // +0x10
    unsigned int mSelectableIndex;         // +0x14
};

class ContainerItem : public Item {
public:
    void* mChildItems[2];                  // +0x18
    DOM::Element* mpElement;               // +0x20
    Style::Rule* mStyleRules;              // +0x24
    unsigned int mnRuleCount;              // +0x28
    int mDisplay;                          // +0x2c
    int mPosition;                         // +0x30
    uint32_t pad34[(0x48 - 0x34) / 4];
    Style::ParagraphStyle mParaStyle;      // +0x48
};

class StackingContext {
public:
    void SetParagraphStyle(const Style::ParagraphStyle& ps);   // 0x008ee740
    void SetContextRect(const RectT<float>& rect);             // 0x008efc80
    void Fn8efcd0(int arg);                                    // 0x008efcd0
    void Fn8f0010();                                           // 0x008f0010

    Item* mpContextRoot;                   // +0x0
    Text::Typesetter mTypesetter;          // +0x4
    RectT<float> mContextRect;             // +0x534
    RectT<float> mBoundsRect;              // +0x544
    float mMarginLeft;                     // +0x554
    float mMarginRight;                    // +0x558
    float mYPos;                           // +0x55c
    float mPendingCollapse;                // +0x560
    float mMaxBreak;                       // +0x564
    float mMinBreak;                       // +0x568
    float mFirstLineBaseline;              // +0x56c
    float mFirstLineHeight;                // +0x570
    bool mbAtLineBreak;                    // +0x574
    Block* mpFloatHead;                    // +0x578
    Block* mpFloatTail;                    // +0x57c
    Block* mpOutOfFlowList;                // +0x580
};

class Block : public ContainerItem {
public:
    virtual void SetMargins(StackingContext& sc, Style::StyleState& style);        // +0x38
    virtual void PlaceOutOfFlow(StackingContext& sc, Style::StyleState& style);    // +0x3c

    void Fn8eab50(RenderingContext& ctx);                     // 0x008eab50
    bool Fn8eaba0(PickingContext& pc, void* pArg);            // 0x008eaba0
    void DrawContent(RenderingContext& ctx);                  // 0x008e6a20
    bool PickContent(PickingContext& pc, void* pArg);         // 0x008e6b70
    void PlaceControls(Point2DT<float>& pos);                 // 0x008e6c60
    void Layout(StackingContext& sc, Style::StyleState& style);   // 0x008e6d30

    bool mbOutOfFlow;                      // +0x50
    int mFloat;                            // +0x54
    float mVerticalOffset;                 // +0x58
    Block* mpNextFloat;                    // +0x5c
    Block* mpNextOOF;                      // +0x60
    RectT<float> mOuterRect;               // +0x64
    RectT<float> mBorderRect;              // +0x74
    RectT<float> mPaddingRect;             // +0x84
    RectT<float> mContentRect;             // +0x94
    RectT<float> mPickRect;                // +0xa4
    RectT<float> mBorderWidth;             // +0xb4
};

class Background : public ImageRequester {
public:
    bool Draw(RenderingContext& ctx, const RectT<float>& pen, const RectT<float>& rect);   // 0x008e6710
    void SetStyle(Style::StyleState& style);                                               // 0x008e68f0

    Page* mpPage;                          // +0xc
    unsigned int mImageTableIndex;         // +0x10
    const wchar_t* mpImageURL;             // +0x14
    Style::BackgroundRepeat mRepeat;       // +0x18
    int mAttachment;                       // +0x1c
    Style::Length mPosX;                   // +0x20
    Style::Length mPosY;                   // +0x28
    Style::FontMetrics mFontMetrics;       // +0x30
    bool mbDraw;                           // +0x44
};

inline float Min(float a, float b) { return (a < b) ? a : b; }
inline float Max(float a, float b) { return (a > b) ? a : b; }

// 0x008e61b0: clip-scatter helper (s008e5320).  RectF is layout-identical to RectT<float>.
void Fn8e61b0(void** pp, RectT<float> r, void* p6, RectT<float>* p7);

// @ 0x008e6340
void BltTiled(RenderingContext& ctx, RectT<float> rect, COM::IUnknown32* pImage,
              Point2DT<float> scale, Point2DT<float> offset, Style::BackgroundRepeat repeat)
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
        Fn8e61b0((void**)&ctx, RectT<float>(x, y, x + tileW, y + tileH), pImage, &rect);
        break;
    case Style::kRepeatX:
        for (float cx = x; cx < rect.mRight; cx += tileW)
            Fn8e61b0((void**)&ctx, RectT<float>(cx, y, cx + tileW, y + tileH), pImage, &rect);
        break;
    case Style::kRepeatY:
        // Retail (and dev) bug: y is never advanced inside the loop, so once entered this
        // degenerate loop re-blits the same tile forever.  Kept verbatim to match the bytes.
        for (float cy = y; cy < rect.mBottom; )
            Fn8e61b0((void**)&ctx, RectT<float>(x, cy, x + tileW, cy + tileH), pImage, &rect);
        break;
    case Style::kRepeatXY:
        for (float cy = y; cy < rect.mBottom; cy += tileH)
            for (float cx = x; cx < rect.mRight; cx += tileW)
                Fn8e61b0((void**)&ctx, RectT<float>(cx, cy, cx + tileW, cy + tileH), pImage, &rect);
        break;
    }
}

// @ 0x008e6710
bool Background::Draw(RenderingContext& ctx, const RectT<float>& pen, const RectT<float>& rect)
{
    if (!mbDraw)
        return false;
    if (rect.mLeft == rect.mRight)
        return false;
    if (rect.mTop == rect.mBottom)
        return false;

    COM::IUnknown32* pRes = mpPage->GetResource(mImageTableIndex);
    if (pRes == 0)
        return false;
    COM::IUnknown32* pImage = pRes->AsInterface(0xee3f516e);
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

// @ 0x008e68f0
void Background::SetStyle(Style::StyleState& style)
{
    mpImageURL = style.mpBackgroundImage;
    mRepeat = (Style::BackgroundRepeat)style.mBackgroundRepeat;
    mAttachment = style.mBackgroundAttachment;
    mPosX.mValue = style.mBackgroundPosX.mValue;
    mPosX.mUnits = style.mBackgroundPosX.mUnits;
    mPosY.mValue = style.mBackgroundPosY.mValue;
    mPosY.mUnits = style.mBackgroundPosY.mUnits;
    mFontMetrics = style.mFontMetrics;

    mbDraw = (mpImageURL != 0);
    if (mpImageURL != 0) {
        COM::IUnknown32* pRes = mpPage->GetResource(mImageTableIndex);
        if (pRes == 0 || pRes->AsInterface(0xee3f516e) == 0) {
            if (mnJobId == 0)
                mpPage->LoadImage(this, mpImageURL);
        }
    }
}

// Synthetic home for the unnamed 4-arg constructor/store helper.  Layout: +0 node, +4 document,
// +8/+0xc point, +0x10 zero, +0x14 arg2, +0x18 arg3.
struct Fn8e69b0Target {
    DOM::Element* mpNode;   // +0x0
    void* mpDocument;       // +0x4
    float mX;               // +0x8
    float mY;               // +0xc
    uint32_t mZero;         // +0x10
    uint32_t mArg2;         // +0x14
    void* mArg3;            // +0x18

    void Fn8e69b0(DOM::Element* pNode, uint32_t arg2, void* arg3, Point2DT<float>* pPos);
};

// @ 0x008e69b0
void Fn8e69b0Target::Fn8e69b0(DOM::Element* pNode, uint32_t arg2, void* arg3, Point2DT<float>* pPos)
{
    Fn8e69b0Target* self = this;
    self->mArg2 = arg2;
    self->mpNode = pNode;
    self->mZero = 0;
    self->mArg3 = arg3;
    self->mX = pPos->mX;
    self->mY = pPos->mY;
    self->mpDocument = 0;
    while (pNode != 0) {
        if (pNode->Type() == 1) {
            void* pDocument = pNode->mpDocument;
            self->mpDocument = pDocument;
            if (pDocument != 0)
                break;
        }
        pNode = pNode->Parent();
    }
}

// @ 0x008e6a20
void Block::DrawContent(RenderingContext& ctx)
{
    if (mpElement != 0) {
        if (mpElement->v14()) {
            int pControl = mpElement->Fn8e42d0();
            ctx.SetContextRectRelative(mContentRect.mLeft, mContentRect.mTop, mContentRect.mRight,
                                       mContentRect.mBottom);
            ctx.Fn8ee7a0(-1);
            if (pControl == 0)
                return;
            ctx.Fn8eec80(0.0f, 0.0f, mContentRect.mRight - mContentRect.mLeft,
                         mContentRect.mBottom - mContentRect.mTop, (void*)pControl);
            return;
        }
        if (mpElement->v18())
            return;
    }

    Style::ParagraphStyle saved;
    ctx.Fn8ee770(&saved);
    ctx.SetParagraphStyle(mParaStyle);
    ctx.SetContextRectRelative(mContentRect.mLeft, mContentRect.mTop, mContentRect.mRight,
                               mContentRect.mBottom);
    ctx.mYPos = 0.0f;
    Fn8eab50(ctx);
    ctx.Fn8ef6d0();
    ctx.SetParagraphStyle(saved);
}

// @ 0x008e6b70
bool Block::PickContent(PickingContext& pc, void* pArg)
{
    if (pc.mRelPos.mX < mPickRect.mLeft)
        return false;
    if (pc.mRelPos.mY < mPickRect.mTop)
        return false;
    if (mPickRect.mRight <= pc.mRelPos.mX)
        return false;
    if (mPickRect.mBottom <= pc.mRelPos.mY)
        return false;

    Style::ParagraphStyle saved;
    pc.Fn8edd80(&saved);
    pc.Fn8edd50(mParaStyle);
    pc.SetContextRectRelative(mContentRect.mLeft, mContentRect.mTop, mContentRect.mRight,
                              mContentRect.mBottom);
    pc.mYPos = 0.0f;
    if (Fn8eaba0(pc, pArg))
        return true;
    if (pc.Fn8ee4a0(pArg))
        return true;
    pc.Fn8edd50(saved);
    return false;
}

// @ 0x008e6c60
void Block::PlaceControls(Point2DT<float>& pos)
{
    RectT<float> rect(pos.mX + mContentRect.mLeft, mContentRect.mTop + pos.mY,
                      pos.mX + mContentRect.mRight, mContentRect.mBottom + pos.mY);
    if (mpElement != 0) {
        if (mpElement->v18()) {
            RectT<float> elementRect = rect;
            mpElement->v20(&elementRect);
        }
    }
    PlaceControl(&rect);
}

// @ 0x008e6d30
void Block::Layout(StackingContext& sc, Style::StyleState& style)
{
    const float padContentDiff = mPaddingRect.mBottom - mContentRect.mBottom;
    const float borderPadDiff = mBorderRect.mBottom - mPaddingRect.mBottom;
    const float outerBorderDiff = mOuterRect.mBottom - mBorderRect.mBottom;

    const RectT<float> savedContextRect(sc.mContextRect);

    RectT<float> contextRect(mContentRect.mLeft + sc.mContextRect.mLeft,
                             mContentRect.mTop + sc.mContextRect.mTop,
                             mContentRect.mRight + sc.mContextRect.mLeft,
                             mContentRect.mBottom + sc.mContextRect.mTop);
    sc.SetContextRect(contextRect);

    Block* pOutOfFlow = sc.mpOutOfFlowList;
    sc.mpOutOfFlowList = 0;
    const RectT<float> savedBounds(sc.mBoundsRect);
    sc.mBoundsRect.mLeft = 0.0f;
    sc.mBoundsRect.mTop = 0.0f;
    sc.mBoundsRect.mRight = 0.0f;
    sc.mBoundsRect.mBottom = 0.0f;
    sc.mYPos = 0.0f;

    if (mpElement != 0 && (mpElement->v14() || mpElement->v18())) {
        SizeT<float> intrinsic(16.0f, 16.0f);
        mpElement->GetIntrinsicSize(&intrinsic);
        sc.mYPos = intrinsic.h;
        sc.mFirstLineBaseline = 0.0f;
        sc.mFirstLineHeight = intrinsic.h;
    } else {
        LayoutChildren(sc, style);
        sc.Fn8f0010();
    }

    if (sc.mpContextRoot == this)
        sc.Fn8efcd0(3);

    if (style.mBoxHeight.mUnits == Style::kUnitsAuto)
        mContentRect.mBottom = mContentRect.mTop + sc.mYPos;

    mPaddingRect.mBottom = mContentRect.mBottom + padContentDiff;
    mBorderRect.mBottom = mPaddingRect.mBottom + borderPadDiff;
    mOuterRect.mBottom = mBorderRect.mBottom + outerBorderDiff;

    sc.mContextRect = mPaddingRect;
    sc.mContextRect.mLeft -= mContentRect.mLeft;
    sc.mContextRect.mTop -= mContentRect.mTop;
    sc.mContextRect.mRight -= mContentRect.mLeft;
    sc.mContextRect.mBottom -= mContentRect.mTop;

    for (Block* pBlock = sc.mpOutOfFlowList; pBlock != 0; pBlock = pBlock->mpNextOOF)
        pBlock->PlaceOutOfFlow(sc, style);

    if (sc.mBoundsRect.mLeft == sc.mBoundsRect.mRight ||
        sc.mBoundsRect.mTop == sc.mBoundsRect.mBottom) {
        sc.mBoundsRect = mBorderRect;
    } else {
        sc.mBoundsRect.mLeft += mContentRect.mLeft;
        sc.mBoundsRect.mTop += mContentRect.mTop;
        sc.mBoundsRect.mRight += mContentRect.mLeft;
        sc.mBoundsRect.mBottom += mContentRect.mTop;
        sc.mBoundsRect.mLeft = Min(mBorderRect.mLeft, sc.mBoundsRect.mLeft);
        sc.mBoundsRect.mTop = Min(mBorderRect.mTop, sc.mBoundsRect.mTop);
        sc.mBoundsRect.mRight = Max(mBorderRect.mRight, sc.mBoundsRect.mRight);
        sc.mBoundsRect.mBottom = Max(mBorderRect.mBottom, sc.mBoundsRect.mBottom);
    }

    mPickRect = sc.mBoundsRect;
    sc.mBoundsRect.mLeft = Min(savedBounds.mLeft, sc.mBoundsRect.mLeft);
    sc.mBoundsRect.mTop = Min(savedBounds.mTop, sc.mBoundsRect.mTop);
    sc.mBoundsRect.mRight = Max(savedBounds.mRight, sc.mBoundsRect.mRight);
    sc.mBoundsRect.mBottom = Max(savedBounds.mBottom, sc.mBoundsRect.mBottom);

    sc.SetContextRect(savedContextRect);
    sc.mpOutOfFlowList = pOutOfFlow;
    sc.mPendingCollapse = outerBorderDiff;
    sc.mYPos = mOuterRect.mBottom;
}

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA
