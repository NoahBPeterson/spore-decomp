// Slice s008eebb0: EA::XHTML::Layout::RenderingContext::DrawTextLine (retail layout; offsets from the asm).
// Built /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

namespace eastl {
struct Link { Link* mpNext; };
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    struct NoInit {};
    fixed_pool_base() : mpHead(0) {}
    fixed_pool_base(NoInit) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};
// fixed_pool_with_overflow: 0x14 bytes
class fixed_pool_with_overflow : public fixed_pool_base { public:
    void* mpPoolBegin;     // +8
    void* mpPoolEnd;       // +0xc
    uint32_t mnNodeSize;   // +0x10
    __forceinline fixed_pool_with_overflow() : fixed_pool_base(NoInit()) {}
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
    RectTree() {}                          // initialised by RectSetExt::Init
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
    RectSetExt* Init(const RectAlloc& pool);  // 0x008eed10
};
RectNode* RBTreeIncrement(RectNode* p);   // 0x00921580

struct LineLayoutHdr {};
struct AnalysisInfo { struct TextStyle* mpTextStyle; void* mpFont; int mBits; };
struct TextStyle { char pad[0x224]; unsigned mColor; char pad2[0x238 - 0x228]; unsigned mDecorations; };

template <typename T> struct cvec { T* mpBegin; T* mpEnd; T* mpCapacity; void* mpAllocator; int mFlags; };
class LineLayout { public:
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

// Typesetter position triple (12 bytes) - base of Typesetter
struct TripleFloat {
    float mX, mY, mZ;
    void Set(float x, float y, float z);                 // 0x00897640
};

// EA::Text::Typesetter (0x530 bytes: 12 bytes of TripleFloat + 0x524 of state)
class Typesetter : public TripleFloat {
public:
    char mState[0x524];
    Typesetter(int a);                                   // 0x0089d820
    unsigned GetType();                                  // 0x00897680
    unsigned GetLineType();                             // 0x0089cf10
    LineLayout* GetLineLayout();                         // 0x008976a0
    void FinalizeLine();                                 // 0x0089d9a0
    void NextLine(int a);                                // 0x0089c5d0
    void Reset(int a);                                   // 0x0089cdf0
    void SetRunStyle(int a);                             // 0x0089b360
    void AddTextRun(const wchar_t* s, unsigned n);       // 0x0089b1e0
    void AddLineBreak(const wchar_t* s, unsigned n, int a, int b);   // 0x0089b250
};
}}

namespace EA { namespace Drawing {
class IDrawContext { public:
    virtual void v0();
    virtual void SetColor(unsigned c);                    // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11();
    virtual void DrawGlyphs(const uint16_t* g, const EA::Text::GlyphLayoutInfo* info, unsigned n);   // +0x30
    virtual void v13();
    virtual void FillRect(float x1, float y1, float x2, float y2);   // +0x38
    virtual void v15(); virtual void v16(); virtual void v17();
    // +0x48: draw four offset quads (retail FUN_008eebb0 receiver)
    virtual void DrawQuadSet(const float* p1, void* v1, const float* p2, void* v2,
                             const float* p3, void* v3, const float* p4, void* v4);
    virtual void v19(); virtual void v20(); virtual void v21();
    // +0x58: textured rectangle (retail FUN_008eec80 receiver)
    virtual void DrawImage(const float* rect, void* tex, const float* uv);
};
}}

namespace EA { namespace XHTML { namespace Layout {
class RenderingContext;
class Background { public:
    char pad[0x44];
    void Draw(RenderingContext* ctx, const float* pen, const float* rect);   // 0x008e6710
};
class InlineItem { public:
    char pad0[0x3c];
    unsigned mColor;                // +0x3c
    char pad1[0x44 - 0x40];
    Background* mpBackground;       // +0x44
    char pad2[0x50 - 0x48];
    InlineItem* mpNext;             // +0x50
    unsigned mBegin;                // +0x54
    unsigned mEnd;                  // +0x58
    InlineItem* mpNextFloat;        // +0x5c (float list link)
    char pad4[0x70 - 0x60];
    float mfFloatBottom;            // +0x70
};
struct ContextRectF { float mfOffsetX, mfOffsetY, mfWidth, mfHeight; };
class RenderingContext { public:
    EA::Drawing::IDrawContext* mpDC;       // +0
    EA::Text::Typesetter mTypesetter;      // +4  (0x530 bytes)
    union {
        struct { float mfOffsetX, mfOffsetY, mfWidth, mfHeight; };   // +0x534
        ContextRectF mRect;
    };
    float mPen[4];                         // +0x544 (pen origin passed to Background::Draw)
    float mfLineHeight;                    // +0x554
    float mfBaseline;                      // +0x558
    float mYPos;                           // +0x55c
    union { unsigned mSelectionStart; float mfSelectionStart; };   // +0x560
    unsigned mSelectionEnd;                // +0x564
    unsigned mLineBaseIndex;               // +0x568
    InlineItem* mpFloatHead;               // +0x56c
    InlineItem* mpFloatTail;               // +0x570
    union { InlineItem* mpActiveSpans; unsigned char mFlag574; };  // +0x574

    // 16-byte context rectangle covering +0x534..+0x543

    void DrawTextLine(EA::Text::LineLayout* pLine);   // 0x008eeee0
    void RefreshMargins();                           // 0x008eea30
    void SetContextRect(const ContextRectF* r);      // 0x008eed80
    void SetContextRectRelative(float l, float t, float r, float b);   // 0x008eedb0
    void PlaceFloat(InlineItem* item);               // 0x008eee30
    void DrawQuadSet2(const float* p1, void* v1, const float* p2, void* v2,
                      const float* p3, void* v3, const float* p4, void* v4);  // 0x008eebb0
    void DrawImage2(float x, float y, float w, float h, void* tex);          // 0x008eec80
    void BeginContent();                             // 0x008ef550
    void Reset();                                    // 0x008ef6d0
    void AddTextRun(const wchar_t* s, unsigned n, int style);      // 0x008efa50
    void AddLineBreak(const wchar_t* s, unsigned n, int style);    // 0x008efa90
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

// ===========================================================================
// Remaining RenderingContext / SizingContext slice functions.
// ===========================================================================
namespace Simulator { struct cGameData { char mPad[0x348]; int mMode; }; }

// float constants referenced by the sizing pass

namespace EA { namespace XHTML { namespace Layout {
class SizingContext : public EA::Text::Typesetter {
public:
    float mfMaxHeight;   // +0x530
    float mfMaxWidth;    // +0x534
    float mfHeight;      // +0x538

    SizingContext(float h);                                 // 0x008ef870
    void Clear();                                           // 0x008ef8b0
    void AddRun(const wchar_t* s, unsigned n, int style);    // 0x008ef8d0
    void Finish();                                          // 0x008ef900
    Simulator::cGameData* GetGameData();                    // 0x006e64f0
};
}}}

// @ 0x008eebb0
void RenderingContext::DrawQuadSet2(const float* p1, void* v1, const float* p2, void* v2,
                                    const float* p3, void* v3, const float* p4, void* v4)
{
    float r[8];
    r[0] = p4[0] + mfOffsetX;
    r[1] = p4[1] + mfOffsetY;
    r[2] = p3[0] + mfOffsetX;
    r[3] = p3[1] + mfOffsetY;
    r[4] = p2[0] + mfOffsetX;
    r[5] = p2[1] + mfOffsetY;
    r[6] = p1[0] + mfOffsetX;
    r[7] = p1[1] + mfOffsetY;
    mpDC->DrawQuadSet(&r[6], v1, &r[4], v2, &r[2], v3, &r[0], v4);
}

// @ 0x008eec80
void RenderingContext::DrawImage2(float x, float y, float w, float h, void* tex)
{
    if (tex == 0)
        return;
    float uv[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
    float rc[4];
    rc[0] = x + mfOffsetX;
    rc[1] = y + mfOffsetY;
    rc[2] = rc[0] + w;
    rc[3] = rc[1] + h;
    mpDC->DrawImage(rc, tex, uv);
}

// @ 0x008eed10
RectSetExt* RectSetExt::Init(const RectAlloc& pool)
{
    mAnchor = RectNode();
    mnSize = 0;
    void* pMemory = pool.mpHead;
    mAlloc.mpHead = 0;
    mAlloc.init(pMemory, 0x80, 0x20, 4, 0);
    mAlloc.mpPoolBegin = pMemory;
    mAlloc.mnNodeSize = 0x20;
    mAlloc.mpPoolEnd = (char*)pMemory + 0x80;
    mAnchor.mpLeft = &mAnchor;
    mAnchor.mpRight = &mAnchor;
    mAnchor.mpParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
    return this;
}

// @ 0x008eed80
void RenderingContext::SetContextRect(const ContextRectF* r)
{
    mfOffsetX = r->mfOffsetX;
    mfOffsetY = r->mfOffsetY;
    mfWidth = r->mfWidth;
    mfHeight = r->mfHeight;
    RefreshMargins();
}

// @ 0x008eedb0
void RenderingContext::SetContextRectRelative(float l, float t, float r, float b)
{
    float v[4];
    v[0] = l + mfOffsetX;
    v[1] = t + mfOffsetY;
    v[2] = r + mfOffsetX;
    v[3] = b + mfOffsetY;
    mfOffsetX = v[0];
    mfOffsetY = v[1];
    mfWidth = v[2];
    mfHeight = v[3];
    RefreshMargins();
}

// @ 0x008eee30
void RenderingContext::PlaceFloat(InlineItem* item)
{
    item->mpNextFloat = 0;
    if (mpFloatHead == 0)
        mpFloatHead = item;
    else
        mpFloatTail->mpNextFloat = item;
    mpFloatTail = item;
    InlineItem** pp = &mpFloatHead;
    while (*pp) {
        if (mYPos >= (*pp)->mfFloatBottom)
            *pp = (*pp)->mpNextFloat;
        else
            pp = &(*pp)->mpNextFloat;
    }
    RefreshMargins();
}

// @ 0x008eee90
RectSetExt::RectSetExt() : RectTree()
{
    RectAlloc pool(mBuffer);
    Init(pool);
}

// @ 0x008ef550
void RenderingContext::BeginContent()
{
    EA::Text::LineLayout* pLine = mTypesetter.GetLineLayout();
    mTypesetter.Set(mfBaseline - mfLineHeight, mfLineHeight, mfOffsetY + mYPos);
    while (mTypesetter.GetLineType() == 1) {
        mTypesetter.FinalizeLine();
        DrawTextLine(pLine);
        mYPos += (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
        InlineItem** pp = &mpFloatHead;
        bool changed = false;
        while (*pp) {
            if (mYPos >= (*pp)->mfFloatBottom) {
                *pp = (*pp)->mpNextFloat;
                changed = true;
            } else {
                pp = &(*pp)->mpNextFloat;
            }
        }
        if (changed)
            RefreshMargins();
        mLineBaseIndex += pLine->mCharArray.mpEnd - pLine->mCharArray.mpBegin;
        mTypesetter.Set(mfBaseline - mfLineHeight, mfLineHeight, mfOffsetY + mYPos);
        mTypesetter.NextLine(0);
    }
}

// @ 0x008ef6d0
void RenderingContext::Reset()
{
    EA::Text::LineLayout* pLine = mTypesetter.GetLineLayout();
    mTypesetter.Set(mfBaseline - mfLineHeight, mfLineHeight, mfOffsetY + mYPos);
    while (mTypesetter.GetType() != 2) {
        mTypesetter.FinalizeLine();
        DrawTextLine(pLine);
        mYPos += (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
        InlineItem** pp = &mpFloatHead;
        bool changed = false;
        while (*pp) {
            if (mYPos >= (*pp)->mfFloatBottom) {
                *pp = (*pp)->mpNextFloat;
                changed = true;
            } else {
                pp = &(*pp)->mpNextFloat;
            }
        }
        if (changed)
            RefreshMargins();
        mLineBaseIndex += pLine->mCharArray.mpEnd - pLine->mCharArray.mpBegin;
        mTypesetter.Set(mfBaseline - mfLineHeight, mfLineHeight, mfOffsetY + mYPos);
        mTypesetter.NextLine(0);
    }
    mTypesetter.Reset(1);
    mSelectionStart = 0xffffffffu;
    mSelectionEnd = 0;
    mLineBaseIndex = 0;
}

// @ 0x008ef870
SizingContext::SizingContext(float h) : EA::Text::Typesetter(0)
{
    mfMaxHeight = 0.0f;
    mfMaxWidth = 0.0f;
    mfHeight = h;
    Reset(1);
}

// @ 0x008ef8b0
void SizingContext::Clear()
{
    float z = 0.0f;
    mfMaxHeight = z;
    mfMaxWidth = z;
    Reset(1);
}

// @ 0x008ef8d0
void SizingContext::AddRun(const wchar_t* s, unsigned n, int style)
{
    SetRunStyle(style);
    AddTextRun(s, n);
}

// @ 0x008ef900
void SizingContext::Finish()
{
    EA::Text::LineLayout* pLine = GetLineLayout();
    GetGameData()->mMode = 3;
    Set(*(const float*)0x013f6d90, 0.0f, 0.0f);
    while (GetType() != 2) {
        FinalizeLine();
        mfMaxHeight = tmax(mfMaxHeight, (float)ceil((double)pLine->mLineMetrics[2]));
        NextLine(0);
    }
    Reset(0);
    GetGameData()->mMode = 3;
    Set(0.0f, 0.0f, 0.0f);
    while (GetType() != 2) {
        FinalizeLine();
        mfMaxWidth = tmax(mfMaxWidth, pLine->mLineMetrics[2]);
        NextLine(0);
    }
    if (mfMaxWidth == *(const float*)0x01485378)
        mfMaxWidth = mfMaxHeight;
    Reset(1);
}

// @ 0x008efa50
void RenderingContext::AddTextRun(const wchar_t* s, unsigned n, int style)
{
    mTypesetter.SetRunStyle(style);
    mTypesetter.AddTextRun(s, n);
    mFlag574 = 0;
    mfSelectionStart = 0.0f;
}

// @ 0x008efa90
void RenderingContext::AddLineBreak(const wchar_t* s, unsigned n, int style)
{
    mTypesetter.SetRunStyle(style);
    mTypesetter.AddLineBreak(s, n, 0, 0);
    mFlag574 = 0;
    mfSelectionStart = 0.0f;
}


