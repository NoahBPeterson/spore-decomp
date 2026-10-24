// Slice s008e7230 (batch gold7) -- 0x008e7da0..0x008e8047.
//
// Three EA::XHTML::Layout members of the Block item: GetPickBox (fills the DOM
// placement result from the border rect), MoveTo (moves the four box rects plus
// the pick rect to a new top-left) and the Block constructor (the Item base ctor
// call, the empty child list, the element/style pointers and the zeroed rects).
//
// The layouts are the dev-PDB ones (EA::XHTML::Layout::Block is 0xc4 bytes in the
// dev PDB too, so no retail delta): Item puts its vfptr first, so the intrusive
// list node it derives from starts at +0x04 and ContainerItem's member block at
// +0x18.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (EA::XHTML module, no /EHsc).
#include "types.h"
#include <math.h>
#include <stddef.h>
#include <new>

typedef unsigned int uint;

// ------------------------------- EASTL -------------------------------------
namespace eastl {

struct intrusive_list_node {
    intrusive_list_node* mpNext;  // +0x00
    intrusive_list_node* mpPrev;  // +0x04
};

class intrusive_list_base {
public:
    intrusive_list_node mAnchor;  // +0x00

    __forceinline intrusive_list_base() { mAnchor.mpNext = mAnchor.mpPrev = &mAnchor; }
};

template <typename T>
class intrusive_list : public intrusive_list_base {
public:
    typedef T node_type;
};

}  // namespace eastl

namespace EA {

template <typename T>
class RectT {
public:
    T mLeft, mTop, mRight, mBottom;  // +0x00..+0x0c

    RectT() {}
    RectT(T l, T t, T r, T b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
};

namespace Text {
class Typesetter;
}

namespace Style {
class Rule;
}  // namespace Style

namespace XHTML {

namespace DOM {
class Element;
class Page;
}

namespace Layout {

using EA::RectT;

class Item;
class ContainerItem;
class Block;
class Border;
class Background;
class Page;

// dom element placement result: size, a float, a top offset and the width again (0x14 bytes).
struct PickBox {
    float mLeft, mTop, mRight, mBottom, mExtra;
};

// The shared 0.5 rounding constant the pick-box baseline is snapped with.
extern const float gRoundHalf;  // 0x01471064 (0.5f)

enum ItemType { kItemNone = 0, kItemBlock = 1 };

// The linked-list node lives 4 bytes into every Item (the vfptr is first), so list
// iteration walks the node chain and subtracts 4 to recover the owning Item.
class Item : public eastl::intrusive_list_node {
public:
    Item(Page* pPage, int nType);                                             // 0x008eae40
    virtual ~Item();                                                          // +0x00
    virtual void v04(unsigned int nColor);                                    // +0x04
    virtual void Measure(void* pSizing, void* pStyle);                        // +0x08
    virtual void LayoutFlow(void* pCtx, void* pStyle);                        // +0x0c
    virtual void PlaceControls(unsigned int nArg);                            // +0x10
    virtual void Render(void* pCtx);                                          // +0x14
    virtual bool Pick(void* pCtx, void* pEntry);                              // +0x18
    virtual void v1c();                                                       // +0x1c
    virtual void MeasureContent(void* pSizing, void* pStyle);                 // +0x20
    virtual void v24(void* pCtx, void* pStyle);                               // +0x24
    virtual void PlaceControlsContent(unsigned int nArg);                     // +0x28
    virtual void RenderContent(void* pArg);                                   // +0x2c
    virtual bool PickContent(void* pCtx, void* pEntry);                       // +0x30
    virtual void Layout(void* pCtx, void* pStyle);                            // +0x34
    virtual void Scroll(RectT<float> rect);                                   // +0x38
    virtual void PlaceOutOfFlow(void* pCtx, void* pStyle);                    // +0x3c

    Page* mpPage;                   // +0x0c
    ItemType mItemType;             // +0x10
    unsigned int mSelectableIndex;  // +0x14
};

typedef eastl::intrusive_list<Item> ItemList;

class ContainerItem : public Item {
public:
    __forceinline ContainerItem(Page* pPage, const DOM::Element* pElement, int nType)
        : Item(pPage, nType)
    {
        mpElement = (DOM::Element*)pElement;
    }
    virtual void MeasureContent(void* pSizing, void* pStyle);                 // +0x20
    virtual void LayoutFlow(void* pCtx, void* pStyle);                        // +0x0c
    virtual void Render(void* pCtx);                                          // +0x14
    virtual bool Pick(void* pCtx, void* pEntry);                              // +0x18

    ItemList mChildItems;     // +0x18
    DOM::Element* mpElement;  // +0x20
    Style::Rule** mStyleRules;  // +0x24
    unsigned int mnRuleCount;   // +0x28
    int mDisplay;               // +0x2c
    int mPosition;              // +0x30
    int mPlacement;             // +0x34
    unsigned int mFgColor;      // +0x38
    unsigned int mBgColor;      // +0x3c
    Border* mpBorder;           // +0x40
    Background* mpBackground;   // +0x44
    uint32_t mParaStyle[2];     // +0x48 (Style::ParagraphStyle, opaque here)
};

class Block : public ContainerItem {
public:
    Block(Page* pPage, const DOM::Element* pElement, int nType);              // 0x008e7f90
    virtual void Measure(void* pSizing, void* pStyle);                        // +0x08
    virtual void Render(void* pCtx);                                          // +0x14
    virtual bool Pick(void* pCtx, void* pEntry);                              // +0x18

    void GetPickBox(PickBox* pBox);                                           // 0x008e7da0

protected:
    void MoveTo(float x, float y);                                            // 0x008e7e00

public:
    bool mbOutOfFlow;             // +0x50
    int mFloat;                   // +0x54
    float mVerticalOffset;        // +0x58
    Block* mpNextFloat;           // +0x5c
    Block* mpNextOOF;             // +0x60
    RectT<float> mOuterRect;      // +0x64
    RectT<float> mBorderRect;     // +0x74
    RectT<float> mPaddingRect;    // +0x84
    RectT<float> mContentRect;    // +0x94
    RectT<float> mPickRect;       // +0xa4
    RectT<float> mBorderWidth;    // +0xb4
};

// @ 0x008e7da0
void Block::GetPickBox(PickBox* pBox)
{
    pBox->mLeft = mBorderRect.mRight - mBorderRect.mLeft;
    pBox->mTop = mBorderRect.mBottom - mBorderRect.mTop;
    pBox->mRight = 0.0f;
    pBox->mBottom = (float)floor(double(mVerticalOffset) + pBox->mTop + (double)gRoundHalf);
    pBox->mExtra = pBox->mLeft;
}

// @ 0x008e7e00
void Block::MoveTo(float x, float y)
{
    float dx = x - mOuterRect.mLeft;
    mOuterRect.mLeft += dx;
    float dy = y - mOuterRect.mTop;
    mOuterRect.mTop += dy;
    mOuterRect.mRight += dx;
    mOuterRect.mBottom += dy;

    mBorderRect.mLeft += dx;
    mBorderRect.mTop += dy;
    mBorderRect.mRight += dx;
    mBorderRect.mBottom += dy;

    mPaddingRect.mLeft += dx;
    mPaddingRect.mTop += dy;
    mPaddingRect.mRight += dx;
    mPaddingRect.mBottom += dy;

    mContentRect.mLeft += dx;
    mContentRect.mTop += dy;
    mContentRect.mRight += dx;
    mContentRect.mBottom += dy;

    mPickRect.mLeft += dx;
    mPickRect.mTop += dy;
    mPickRect.mRight += dx;
    mPickRect.mBottom += dy;
}

// @ 0x008e7f90
Block::Block(Page* pPage, const DOM::Element* pElement, int nType)
    : ContainerItem(pPage, pElement, nType)
{
    mStyleRules = 0;
    mnRuleCount = 0;
    mPlacement = 0;
    mFgColor = 0;
    mBgColor = 0;
    mpBorder = 0;
    mpBackground = 0;
    mpNextFloat = 0;

    mOuterRect.mLeft = 0.0f;
    mOuterRect.mTop = 0.0f;
    mOuterRect.mRight = 0.0f;
    mOuterRect.mBottom = 0.0f;
    mBorderRect.mLeft = 0.0f;
    mBorderRect.mTop = 0.0f;
    mBorderRect.mRight = 0.0f;
    mBorderRect.mBottom = 0.0f;
    mPaddingRect.mLeft = 0.0f;
    mPaddingRect.mTop = 0.0f;
    mPaddingRect.mRight = 0.0f;
    mPaddingRect.mBottom = 0.0f;
    mContentRect.mLeft = 0.0f;
    mContentRect.mTop = 0.0f;
    mContentRect.mRight = 0.0f;
    mContentRect.mBottom = 0.0f;
}

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA
