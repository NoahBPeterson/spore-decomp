// Slice s008eebb0: EA::XHTML::Layout::RenderingContext::DrawTextLine (retail layout; offsets from the asm).
// Built /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

namespace eastl {
struct Link { Link* mpNext; };
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    fixed_pool_base() : mpHead(0) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};
// fixed_pool_with_overflow: 0x14 bytes
struct fixed_pool_with_overflow : fixed_pool_base {
    void* mpPoolBegin;     // +8
    void* mpPoolEnd;       // +0xc
    uint32_t mnNodeSize;   // +0x10
    __forceinline fixed_pool_with_overflow(void* pMemory)
    {
        init(pMemory, 0x80, 0x20, 4, 0);
        mpPoolBegin = pMemory;
        mpPoolEnd = (char*)pMemory + 0x80;
        mnNodeSize = 0x20;
    }
};
}

namespace EA { namespace Text {
struct GlyphLayoutInfo { void* mpFont; float mfPenX; float mfPenY; float mfAdvance; float mfX1; float mfY1; float mfX2; float mfY2; };
struct Rectangle { float mLeft, mTop, mRight, mBottom; };

struct RectNode { RectNode* mpRight; RectNode* mpLeft; RectNode* mpParent; unsigned char mColor; };
struct RectNodeV : RectNode { Rectangle mValue; };   // value at +0x10

// eastl::set<Rectangle> with a fixed node pool; buffer lives inside the object (fixed_set)
typedef eastl::fixed_pool_with_overflow RectAlloc;
struct RectTree {
    int pad0;
    RectNode mAnchor;                  // +4
    unsigned mnSize;                   // +0x14
    RectAlloc mAlloc;                  // +0x18

    __forceinline RectTree(const RectAlloc& a)
        : mAlloc(a.mpHead)
    {
        mAnchor.mpRight = 0; mAnchor.mpLeft = 0; mAnchor.mpParent = 0; mAnchor.mColor = 0; mnSize = 0;
        mAnchor.mpLeft = &mAnchor;
        mAnchor.mpRight = &mAnchor;
        mAnchor.mpParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(RectNode* root);   // 0x00d3b370
    ~RectTree() { DoNukeSubtree(mAnchor.mpParent); }
};
struct RectSet : RectTree {
    char mBuffer[0x80];                // +0x2c
    __forceinline RectSet() : RectTree(RectAlloc(mBuffer)) {}
};
// same layout, constructed by the out-of-line constructor at 0x008eee90
struct RectSetExt : RectTree {
    char mBuffer[0x80];
    RectSetExt();                      // 0x008eee90
};
RectNode* RBTreeIncrement(RectNode* p);   // 0x00921580

struct LineLayoutHdr {};
struct AnalysisInfo { struct TextStyle* mpTextStyle; void* mpFont; int mBits; };
struct TextStyle { char pad[0x224]; unsigned mColor; char pad2[0x238 - 0x228]; unsigned mDecorations; };

template <typename T> struct cvec { T* mpBegin; T* mpEnd; T* mpCapacity; void* mpAllocator; int mFlags; };
struct LineLayout {
    void* mpCoreAllocator;                          // +0x00
    cvec<wchar_t> mCharArray;                       // +0x04
    cvec<AnalysisInfo> mAnalysisInfoArray;          // +0x18
    cvec<uint16_t> mGlyphArray;                     // +0x2c
    cvec<uint32_t> mGlyphInfoArray;                 // +0x40
    cvec<GlyphLayoutInfo> mGlyphLayoutInfoArray;    // +0x54
    cvec<uint32_t> mGlyphIndexArray;                // +0x68
    cvec<uint32_t> mCharIndexArray;                 // +0x7c
    float mLineMetrics[8];                          // +0x90: length, visLength, space, visSpace, baseline, descent, +2
    unsigned GetGlyphSelection(unsigned a, unsigned b, RectTree* out);        // 0x0089c110
    unsigned GetGlyphDecoration(int type, unsigned a, unsigned b, RectTree* out);   // 0x0089c2d0
};

// run iterator over analysis info (0x00897600 ctor, 0x008980d0 advance)
struct RunIter {
    LineLayout* mpLayout;
    unsigned mPos;
    RunIter(LineLayout* p);                              // 0x00897600
    bool Next(unsigned* pBegin, unsigned* pEnd);         // 0x008980d0
};
}}

namespace EA { namespace Drawing {
struct IDrawContext {
    virtual void v0();
    virtual void SetColor(unsigned c);                    // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11();
    virtual void DrawGlyphs(const uint16_t* g, const EA::Text::GlyphLayoutInfo* info, unsigned n);   // +0x30
    virtual void v13();
    virtual void FillRect(float x1, float y1, float x2, float y2);   // +0x38
};
}}

namespace EA { namespace XHTML { namespace Layout {
struct RenderingContext;
struct Background {
    char pad[0x44];
    void Draw(RenderingContext* ctx, const float* pen, const float* rect);   // 0x008e6710
};
struct InlineItem {
    char pad0[0x3c];
    unsigned mColor;                // +0x3c
    char pad1[0x44 - 0x40];
    Background* mpBackground;       // +0x44
    char pad2[0x50 - 0x48];
    InlineItem* mpNext;             // +0x50
    unsigned mBegin;                // +0x54
    unsigned mEnd;                  // +0x58
};
struct RenderingContext {
    EA::Drawing::IDrawContext* mpDC;       // +0
    char pad0[0x534 - 4];
    float mfOffsetX;                       // +0x534
    float mfOffsetY;                       // +0x538
    char pad1[0x544 - 0x53c];
    float mPen[4];                         // +0x544 (pen origin passed to Background::Draw)
    char pad2[0x55c - 0x554];
    float mYPos;                           // +0x55c
    unsigned mSelectionStart;              // +0x560
    unsigned mSelectionEnd;                // +0x564
    unsigned mLineBaseIndex;               // +0x568
    char pad3[0x574 - 0x56c];
    InlineItem* mpActiveSpans;             // +0x574

    void DrawTextLine(EA::Text::LineLayout* pLine);   // 0x008eeee0
};
}}}

using namespace EA::Text;
using namespace EA::XHTML::Layout;

template <typename T> inline const T& tmax(const T& a, const T& b) { return (a < b) ? b : a; }
template <typename T> inline const T& tmin(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x008eeee0
void RenderingContext::DrawTextLine(LineLayout* pLine)
{
    unsigned lineEnd = ((pLine->mCharArray.mpEnd - pLine->mCharArray.mpBegin)) + mLineBaseIndex;
    float y = mYPos + mfOffsetY;
    InlineItem** pp = &mpActiveSpans;
    while (*pp) {
        InlineItem* span = *pp;
        unsigned lo = tmax(mLineBaseIndex, span->mBegin);
        unsigned hi = tmin(lineEnd, span->mEnd);
        if (lo < hi) {
            RectSet set;
            pLine->GetGlyphSelection(lo - mLineBaseIndex, hi - mLineBaseIndex, &set);
            float h = (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
            if (span->mpBackground) {
                mpDC->SetColor(span->mColor);
                for (RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = RBTreeIncrement(n)) {
                    const Rectangle& r = ((RectNodeV*)n)->mValue;
                    float rc[4];
                    rc[0] = r.mLeft - mfOffsetX;
                    rc[1] = y - mfOffsetY;
                    rc[2] = r.mRight - mfOffsetX;
                    rc[3] = (h + y) - mfOffsetY;
                    span->mpBackground->Draw(this, mPen, rc);
                }
            } else if (span->mColor & 0xff000000) {
                mpDC->SetColor(span->mColor);
                for (RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = RBTreeIncrement(n)) {
                    const Rectangle& r = ((RectNodeV*)n)->mValue;
                    mpDC->FillRect(r.mLeft, y, r.mRight, h + y);
                }
            }
        }
        if (span->mEnd > lineEnd)
            pp = &span->mpNext;
        else
            *pp = span->mpNext;
    }
    if (mSelectionStart < mSelectionEnd && mSelectionEnd > mLineBaseIndex) {
        unsigned lo = tmax(mSelectionStart, mLineBaseIndex);
        unsigned hi = tmin(lineEnd, mSelectionEnd);
        if (lo < hi) {
            RectSetExt set;
            pLine->GetGlyphSelection(lo - mLineBaseIndex, hi - mLineBaseIndex, &set);
            mpDC->SetColor(0x7fcfcfff);
            float h = (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
            h += y;
            for (RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = RBTreeIncrement(n)) {
                const Rectangle& r = ((RectNodeV*)n)->mValue;
                mpDC->FillRect(r.mLeft, y, r.mRight, h);
            }
        }
    }
    RunIter it(pLine);
    unsigned b, e;
    while (it.Next(&b, &e)) {
        TextStyle* style = pLine->mAnalysisInfoArray.mpBegin[b].mpTextStyle;
        if (style) {
            mpDC->SetColor(style->mColor);
            mpDC->DrawGlyphs(pLine->mGlyphArray.mpBegin + b, pLine->mGlyphLayoutInfoArray.mpBegin + b, e - b);
            unsigned deco = style->mDecorations;
            while (deco) {
                RectSet set;
                unsigned bit = (0u - deco) & deco;
                deco &= ~bit;
                pLine->GetGlyphDecoration(bit, b, e, &set);
                for (RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = RBTreeIncrement(n)) {
                    const Rectangle& r = ((RectNodeV*)n)->mValue;
                    float y2 = (float)ceil((double)r.mBottom);
                    float y1 = (float)ceil((double)r.mTop);
                    mpDC->FillRect(r.mLeft, y1, r.mRight, y2);
                }
            }
        }
    }
}
