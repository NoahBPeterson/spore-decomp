// src/game/UTFSpore_Win32/RenderingContext.cpp -- migrated from slice(s) s008edc30, s008eebb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/RenderingContext.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/TextStyle.h"
#include <math.h>
#include "EA/XHTML/Layout/Page.h"
#include "EA/Text/Typesetter.h"
#include <intrin.h>

// ---- items of slice s008eebb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct Link { Link* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    struct NoInit {};
    fixed_pool_base() : mpHead(0) {}
    fixed_pool_base(NoInit) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset); // 0x00921260
};
}
namespace eastl {
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
namespace EA {
namespace Text {
struct GlyphLayoutInfo_s008e_ebb0 { void* mpFont; float mfPenX; float mfPenY; float mfAdvance; float mfX1; float mfY1; float mfX2; float mfY2; };
}
}
namespace EA {
namespace Text {
struct Rectangle { float mLeft, mTop, mRight, mBottom; };
}
}
namespace EA {
namespace Text {
struct RectNode { RectNode* mpRight; RectNode* mpLeft; RectNode* mpParent; unsigned char mColor; };
}
}
namespace EA {
namespace Text {
struct RectNodeV : RectNode { Rectangle mValue; };   // value at +0x10
}
}
namespace EA {
namespace Text {
typedef eastl::fixed_pool_with_overflow RectAlloc;
}
}
namespace EA {
namespace Text {
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
}
}
namespace EA {
namespace Text {
struct RectSet : RectTree {
    char mBuffer[0x80];                // +0x2c
    __forceinline RectSet() : RectTree(RectAlloc(mBuffer)) {}
};
}
}
namespace EA {
namespace Text {
struct RectSetExt : RectTree {
    char mBuffer[0x80];
    RectSetExt();                      // 0x008eee90
    RectSetExt* Init(const RectAlloc& pool);  // 0x008eed10
};
}
}
namespace EA {
namespace Text {
RectNode* RBTreeIncrement(RectNode* p);   // 0x00921580
}
}
namespace EA {
namespace Text {
struct AnalysisInfo_s008e_ebb0 { struct TextStyle_s008e_ebb0* mpTextStyle; void* mpFont; int mBits; };
}
}
namespace EA {
namespace Text {
struct TextStyle_s008e_ebb0 { char pad[0x224]; unsigned mColor; char pad2[0x238 - 0x228]; unsigned mDecorations; };
}
}
namespace EA {
namespace Text {
template <typename T> struct cvec { T* mpBegin; T* mpEnd; T* mpCapacity; void* mpAllocator; int mFlags; };
}
}
namespace EA {
namespace Text {
class LineLayout_s008e_ebb0 { public:
    void* mpCoreAllocator;                          // +0x00
    cvec<wchar_t> mCharArray;                       // +0x04
    cvec<AnalysisInfo_s008e_ebb0> mAnalysisInfoArray;          // +0x18
    cvec<uint16_t> mGlyphArray;                     // +0x2c
    cvec<uint32_t> mGlyphInfoArray;                 // +0x40
    cvec<GlyphLayoutInfo_s008e_ebb0> mGlyphLayoutInfoArray;    // +0x54
    cvec<uint32_t> mGlyphIndexArray;                // +0x68
    cvec<uint32_t> mCharIndexArray;                 // +0x7c
    float mLineMetrics[8];                          // +0x90: length, visLength, space, visSpace, baseline, descent, +2
    unsigned GetGlyphSelection(unsigned a, unsigned b, RectTree* out);        // 0x0089c110
    unsigned GetGlyphDecoration(int type, unsigned a, unsigned b, RectTree* out);   // 0x0089c2d0
};
}
}
namespace EA {
namespace Text {
struct RunIter {
    LineLayout_s008e_ebb0* mpLayout;
    unsigned mPos;
    RunIter(LineLayout_s008e_ebb0* p);                              // 0x00897600
    bool Next(unsigned* pBegin, unsigned* pEnd);         // 0x008980d0
};
}
}
namespace EA {
namespace Text {
struct TripleFloat {
    float mX, mY, mZ;
    void Set(float x, float y, float z);                 // 0x00897640
};
}
}
namespace EA {
namespace Text {
class Typesetter_s008e_ebb0 : public TripleFloat {
public:
    char mState[0x524];
    Typesetter_s008e_ebb0(int a);                                   // 0x0089d820
    unsigned GetType();                                  // 0x00897680
    unsigned GetLineType();                             // 0x0089cf10
    LineLayout_s008e_ebb0* GetLineLayout();                         // 0x008976a0
    void FinalizeLine();                                 // 0x0089d9a0
    void NextLine(int a);                                // 0x0089c5d0
    void Reset(int a);                                   // 0x0089cdf0
    void SetRunStyle(int a);                             // 0x0089b360
    void AddTextRun(const wchar_t* s, unsigned n);       // 0x0089b1e0
    void AddLineBreak(const wchar_t* s, unsigned n, int a, int b);   // 0x0089b250
};
}
}
namespace EA {
namespace Drawing {
class IDrawContext_s008e_ebb0 { public:
    virtual void v0();
    virtual void SetColor(unsigned c);                    // +4
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void DrawGlyphs(const uint16_t* g, const EA::Text::GlyphLayoutInfo_s008e_ebb0* info, unsigned n);   // +0x30
    virtual void v13();
    virtual void FillRect(float x1, float y1, float x2, float y2);   // +0x38
virtual void v15();
virtual void v16();
virtual void v17();
    // +0x48: draw four offset quads (retail FUN_008eebb0 receiver)
    virtual void DrawQuadSet(const float* p1, void* v1, const float* p2, void* v2,
                             const float* p3, void* v3, const float* p4, void* v4);
virtual void v19();
virtual void v20();
virtual void v21();
    // +0x58: textured rectangle (retail FUN_008eec80 receiver)
    virtual void DrawImage(const float* rect, void* tex, const float* uv);
};
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
class Background { public:
    char pad[0x44];
    void Draw(RenderingContext* ctx, const float* pen, const float* rect);   // 0x008e6710
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct ContextRectF { float mfOffsetX, mfOffsetY, mfWidth, mfHeight; };
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext { public:
    EA::Drawing::IDrawContext_s008e_ebb0* mpDC;       // +0
    EA::Text::Typesetter_s008e_ebb0 mTypesetter;      // +4  (0x530 bytes)
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

    void DrawTextLine(EA::Text::LineLayout_s008e_ebb0* pLine);   // 0x008eeee0
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
}
}
}
template <typename T> inline const T& tmax(const T& a, const T& b) { return (a < b) ? b : a; }
template <typename T> inline const T& tmin(const T& a, const T& b) { return (b < a) ? b : a; }
// ---- items of slice s008eebb0 end

// ---- items of slice s008edc30 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_ReadWriteBarrier)
namespace EA {
namespace XHTML {
namespace Layout {
struct Vec2 {
    float x, y;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct FloatEntry {                 // 0x74
    uint32_t mPad00[0x54 / 4];      // +0x00
    int      mKind;                 // +0x54
    uint32_t mPad58;                // +0x58
    FloatEntry* mpNext;             // +0x5c
    uint32_t mPad60;                // +0x60
    float    mSizeBig;              // +0x64
    float    mSizeSmall;            // +0x68
    float    mSizeOther;            // +0x6c
    float    mMaxY;                 // +0x70
    uint32_t mPad74;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct TranslationEntry {           // 0x0c
    int mValue;                     // +0x00
    int mIndex;                     // +0x04
    int mExtra;                     // +0x08
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct TranslationVector {          // eastl vector<TranslationEntry>, 0x14
    TranslationEntry* mpBegin;      // +0x00
    TranslationEntry* mpEnd;        // +0x04
    TranslationEntry* mpCapacity;   // +0x08
    uint32_t mAllocator[2];         // +0x0c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct ScrollInfo {
    void** mpVtbl;                  // +0x00
    void Release();                 // 0x008ee7a0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Typesetter {
public:
    void AddLineBreak(void* item, const void* pickBox);          // 0x0089b250
    void AddTextRun(const wchar_t* s, unsigned n);               // 0x0089b1e0
    void StyleAssign(void* v);                                   // 0x0089b360
    int  ContentSize();                                          // 0x00897690
    void* GetApp();                                              // 0x006e64f0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct LayoutItem {
    char IntersectSelection(unsigned int* begin, unsigned int* end,
                            unsigned int extra);                 // 0x008eaf30
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall StyleAssign(void* self, int, void* v);          // 0x0089b360
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall Scroll_BaseCtor(void* self, int, int);          // 0x0089d820
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RenderingContext_s008e_dc30 { public:
    ScrollInfo* mpScroll00;                 // +0x0000
    uint32_t mPad04[8];                     // +0x0004
    void*    mpNode24;                      // +0x0024
    uint32_t mPad28[5];                     // +0x0028
    void*    mpLayout3c;                    // +0x003c
    int      mVal40;                        // +0x0040
    TranslationVector mBlocks44;            // +0x0044
    uint32_t mPad58[(0x264 - 0x58) / 4];
    int      mVal264;                       // +0x0264
    uint32_t mPad268[(0x530 - 0x268) / 4];
    float    mX530;                         // +0x0530
    float    mY534;                         // +0x0534
    float    mX538;                         // +0x0538
    float    mY53c;                         // +0x053c
    int      mVal540;                       // +0x0540
    float    mX544;                         // +0x0544
    float    mY548;                         // +0x0548
    float    mW54c;                         // +0x054c
    float    mH550;                         // +0x0550
    float    mMarginX554;                   // +0x0554
    float    mMarginY558;                   // +0x0558
    float    mExtra55c;                     // +0x055c
    uint32_t mCount560;                     // +0x0560
    uint32_t mMax564;                       // +0x0564
    uint32_t mVal568;                       // +0x0568
    FloatEntry* mpFloatHead56c;             // +0x056c
    uint32_t mPad570;                       // +0x0570
    void*    mpInline574;                   // +0x0574

    RenderingContext_s008e_dc30(void* scroll, const float* screenRect, const float* marginRect);
    RenderingContext_s008e_dc30(const RenderingContext_s008e_dc30& src);
    void Place(void* item, int style);
    void RefreshMargins();  // 0x008eea30 (EA::XHTML::Layout::RenderingContext::RefreshMargins)
    int TestRect(float x0, float y0, float x1, float y1);
    void ScrollViewport(float x0, float y0, float x1, float y1);  // 0x008ee7b0 (EA::XHTML::Layout::RenderingContext::ScrollViewport)
    void ScrollRect(float x0, float y0, float x1, float y1);
    void SubStyleSet(void* a, void* b);          // 0x008ee720 (uses this+4)
    void SubStyleSetValue(const Vec2* value);    // 0x008ee740 (uses this+4)
    void SubStyleGet(Vec2* out);                 // 0x008ee770 (uses this+4)
    void ReleaseScroll();                        // 0x008ee7a0 (uses *(this))
};
}
}
}
template <typename T> inline const T& tmin_s008e_dc30(const T& a, const T& b) { return (a < b) ? a : b; }
// ---- items of slice s008edc30 end

// @ 0x008ee810
EA::XHTML::Layout::RenderingContext_s008e_dc30::RenderingContext_s008e_dc30(void* scroll, const float* screenRect, const float* marginRect)
{
    mpScroll00 = (EA::XHTML::Layout::ScrollInfo*)scroll;
    EA::XHTML::Layout::Scroll_BaseCtor((char*)this + 4, 0, 0);
    mY534 = screenRect[0];
    mX538 = screenRect[1];
    mY53c = screenRect[2];
    mVal540 = (int)screenRect[3];
    mX544 = marginRect[0];
    mY548 = marginRect[1];
    mW54c = marginRect[2];
    mH550 = marginRect[3];
    mMax564 = 0;
    mVal568 = 0;
    mpFloatHead56c = 0;
    mPad570 = 0;
    mpInline574 = 0;
    mMarginX554 = 0.0f;
    mMarginY558 = 0.0f;
    mExtra55c = 0.0f;
    mCount560 = -1;
}

// @ 0x008ee8c0
EA::XHTML::Layout::RenderingContext_s008e_dc30::RenderingContext_s008e_dc30(const EA::XHTML::Layout::RenderingContext_s008e_dc30& src)
{
    mpScroll00 = src.mpScroll00;
    EA::XHTML::Layout::Scroll_BaseCtor((char*)this + 4, 0, 0);
    mY534 = src.mY534;
    mX538 = src.mX538;
    mY53c = src.mY53c;
    mVal540 = src.mVal540;
    mX544 = src.mX544;
    mY548 = src.mY548;
    mW54c = src.mW54c;
    mH550 = src.mH550;
    mMax564 = 0;
    mVal568 = 0;
    mpFloatHead56c = 0;
    mPad570 = 0;
    mpInline574 = 0;
    mMarginX554 = 0.0f;
    mMarginY558 = 0.0f;
    mExtra55c = 0.0f;
    mCount560 = -1;
}

// @ 0x008ee990
void EA::XHTML::Layout::RenderingContext_s008e_dc30::Place(void* item, int style)
{
    unsigned int a, b;
    if (((EA::XHTML::Layout::LayoutItem*)item)->IntersectSelection(&a, &b, *(unsigned int*)((char*)item + 0x1c))) {
        int size = ((EA::XHTML::Layout::Typesetter*)((char*)this + 4))->ContentSize();
        unsigned int e = a + (unsigned int)size;
        mCount560 = tmin_s008e_dc30(e, mCount560);
        unsigned int e2 = b + (unsigned int)size;
        mMax564 = tmax(mMax564, e2);
    }
    EA::XHTML::Layout::Typesetter* sub = (EA::XHTML::Layout::Typesetter*)((char*)this + 4);
    sub->StyleAssign((void*)style);
    sub->AddTextRun((const wchar_t*)*(int*)((char*)item + 0x18),
                    *(unsigned int*)((char*)item + 0x1c));
}

// @ 0x008eea30
void EA::XHTML::Layout::RenderingContext_s008e_dc30::RefreshMargins()
{
    mMarginX554 = mY534;
    mMarginY558 = mY53c;
    EA::XHTML::Layout::FloatEntry* e = mpFloatHead56c;
    while (e) {
        if (e->mKind == 1) {
            float v = e->mSizeOther + mY534;
            mMarginX554 = tmax(mMarginX554, v);
        } else {
            float v = e->mSizeBig + mY534;
            mMarginY558 = tmax(mMarginY558, v);
        }
        e = e->mpNext;
    }
}

// @ 0x008eeac0
int EA::XHTML::Layout::RenderingContext_s008e_dc30::TestRect(float a, float b, float c, float d)
{
    float v[4];
    v[0] = c + mY534;
    v[1] = a + mY534;
    v[2] = b + mX538;
    v[3] = d + mX538;
    if (v[0] > mX544 && mW54c > v[1] && v[3] > mY548 && mH550 > v[2])
        return 1;
    return 0;
}

// @ 0x008eeb30
void EA::XHTML::Layout::RenderingContext_s008e_dc30::ScrollRect(float a, float b, float c, float d)
{
    float bX = mY534;
    float bY = mX538;
    EA::XHTML::Layout::ScrollInfo* s = mpScroll00;
    (*(void(__thiscall**)(EA::XHTML::Layout::ScrollInfo*, float, float, float, float))(
        *(int*)s + 0x38))(s, a + bX, b + bY, c + bX, d + bY);
}

// @ 0x008eebb0
void EA::XHTML::Layout::RenderingContext::DrawQuadSet2(const float* p1, void* v1, const float* p2, void* v2, const float* p3, void* v3, const float* p4, void* v4)
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
void EA::XHTML::Layout::RenderingContext::DrawImage2(float x, float y, float w, float h, void* tex)
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
EA::Text::RectSetExt* EA::Text::RectSetExt::Init(const EA::Text::RectAlloc& pool)
{
    mAnchor = EA::Text::RectNode();
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
void EA::XHTML::Layout::RenderingContext::SetContextRect(const EA::XHTML::Layout::ContextRectF* r)
{
    mfOffsetX = r->mfOffsetX;
    mfOffsetY = r->mfOffsetY;
    mfWidth = r->mfWidth;
    mfHeight = r->mfHeight;
    RefreshMargins();
}

// @ 0x008eedb0
void EA::XHTML::Layout::RenderingContext::SetContextRectRelative(float l, float t, float r, float b)
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
void EA::XHTML::Layout::RenderingContext::PlaceFloat(EA::XHTML::Layout::InlineItem* item)
{
    item->mpNextFloat = 0;
    if (mpFloatHead == 0)
        mpFloatHead = item;
    else
        mpFloatTail->mpNextFloat = item;
    mpFloatTail = item;
    EA::XHTML::Layout::InlineItem** pp = &mpFloatHead;
    while (*pp) {
        if (mYPos >= (*pp)->mfFloatBottom)
            *pp = (*pp)->mpNextFloat;
        else
            pp = &(*pp)->mpNextFloat;
    }
    RefreshMargins();
}

// @ 0x008eee90
EA::Text::RectSetExt::RectSetExt()
: EA::Text::RectTree()
{
    EA::Text::RectAlloc pool(mBuffer);
    Init(pool);
}

// @ 0x008eeee0
void EA::XHTML::Layout::RenderingContext::DrawTextLine(EA::Text::LineLayout_s008e_ebb0* pLine)
{
    unsigned lineEnd = ((pLine->mCharArray.mpEnd - pLine->mCharArray.mpBegin)) + mLineBaseIndex;
    float y = mYPos + mfOffsetY;
    EA::XHTML::Layout::InlineItem** pp = &mpActiveSpans;
    while (*pp) {
        EA::XHTML::Layout::InlineItem* span = *pp;
        unsigned lo = tmax(mLineBaseIndex, span->mBegin);
        unsigned hi = tmin(lineEnd, span->mEnd);
        if (lo < hi) {
            EA::Text::RectSet set;
            pLine->GetGlyphSelection(lo - mLineBaseIndex, hi - mLineBaseIndex, &set);
            float h = (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
            if (span->mpBackground) {
                mpDC->SetColor(span->mColor);
                for (EA::Text::RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = EA::Text::RBTreeIncrement(n)) {
                    const EA::Text::Rectangle& r = ((EA::Text::RectNodeV*)n)->mValue;
                    float rc[4];
                    rc[0] = r.mLeft - mfOffsetX;
                    rc[1] = y - mfOffsetY;
                    rc[2] = r.mRight - mfOffsetX;
                    rc[3] = (h + y) - mfOffsetY;
                    span->mpBackground->Draw(this, mPen, rc);
                }
            } else if (span->mColor & 0xff000000) {
                mpDC->SetColor(span->mColor);
                for (EA::Text::RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = EA::Text::RBTreeIncrement(n)) {
                    const EA::Text::Rectangle& r = ((EA::Text::RectNodeV*)n)->mValue;
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
            EA::Text::RectSetExt set;
            pLine->GetGlyphSelection(lo - mLineBaseIndex, hi - mLineBaseIndex, &set);
            mpDC->SetColor(0x7fcfcfff);
            float h = (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
            h += y;
            for (EA::Text::RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = EA::Text::RBTreeIncrement(n)) {
                const EA::Text::Rectangle& r = ((EA::Text::RectNodeV*)n)->mValue;
                mpDC->FillRect(r.mLeft, y, r.mRight, h);
            }
        }
    }
    EA::Text::RunIter it(pLine);
    unsigned b, e;
    while (it.Next(&b, &e)) {
        EA::Text::TextStyle_s008e_ebb0* style = pLine->mAnalysisInfoArray.mpBegin[b].mpTextStyle;
        if (style) {
            mpDC->SetColor(style->mColor);
            mpDC->DrawGlyphs(pLine->mGlyphArray.mpBegin + b, pLine->mGlyphLayoutInfoArray.mpBegin + b, e - b);
            unsigned deco = style->mDecorations;
            while (deco) {
                EA::Text::RectSet set;
                unsigned bit = (0u - deco) & deco;
                deco &= ~bit;
                pLine->GetGlyphDecoration(bit, b, e, &set);
                for (EA::Text::RectNode* n = set.mAnchor.mpLeft; n != &set.mAnchor; n = EA::Text::RBTreeIncrement(n)) {
                    const EA::Text::Rectangle& r = ((EA::Text::RectNodeV*)n)->mValue;
                    float y2 = (float)ceil((double)r.mBottom);
                    float y1 = (float)ceil((double)r.mTop);
                    mpDC->FillRect(r.mLeft, y1, r.mRight, y2);
                }
            }
        }
    }
}

// @ 0x008ef550
void EA::XHTML::Layout::RenderingContext::BeginContent()
{
    EA::Text::LineLayout_s008e_ebb0* pLine = mTypesetter.GetLineLayout();
    mTypesetter.Set(mfBaseline - mfLineHeight, mfLineHeight, mfOffsetY + mYPos);
    while (mTypesetter.GetLineType() == 1) {
        mTypesetter.FinalizeLine();
        DrawTextLine(pLine);
        mYPos += (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
        EA::XHTML::Layout::InlineItem** pp = &mpFloatHead;
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
void EA::XHTML::Layout::RenderingContext::Reset()
{
    EA::Text::LineLayout_s008e_ebb0* pLine = mTypesetter.GetLineLayout();
    mTypesetter.Set(mfBaseline - mfLineHeight, mfLineHeight, mfOffsetY + mYPos);
    while (mTypesetter.GetType() != 2) {
        mTypesetter.FinalizeLine();
        DrawTextLine(pLine);
        mYPos += (float)ceil((double)pLine->mLineMetrics[4]) - (float)floor((double)pLine->mLineMetrics[5]);
        EA::XHTML::Layout::InlineItem** pp = &mpFloatHead;
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
