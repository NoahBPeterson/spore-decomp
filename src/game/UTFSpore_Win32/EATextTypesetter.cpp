// src/game/UTFSpore_Win32/EATextTypesetter.cpp -- migrated from slice(s) s011e0560, s0089d3b0, s0089b520, s007046e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextTypesetter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <xmmintrin.h>
#include <math.h>
#define __PLACEMENT_NEW_INLINE   // slice placement new/delete win over <new> (manual: tool guard misses the size_t_ spelling)
#include <new>
#include "EA/Text/Typesetter.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/GlyphInfo.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/TextStyle.h"
#include "rw/core/arena/Arena.h"
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s007046e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Quad16 { uint32_t w[4]; };
// ---- items of slice s007046e0 end

// ---- items of slice s0089b520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern wchar_t gEmptyWStr[2];   // 0x01667bac: shared empty-string storage
extern const wchar_t kWhitespaceChars[];   // 0x0142ef80 (L" \r\n\t")
typedef unsigned int size_t_;
void operator delete(void* p) throw();
inline void operator delete(void*, void*) throw() {}
namespace EA {
namespace Allocator {
struct ICoreAllocator_s0089_b520 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Free(void* p, unsigned size);   // +0xc
    static ICoreAllocator_s0089_b520* GetDefaultAllocator();   // 0x00925cb0
};
}
}
using EA::Allocator::ICoreAllocator_s0089_b520;
namespace EA {
namespace Text {
ICoreAllocator_s0089_b520* GetAllocator();   // 0x008859d0
}
}
namespace EA {
namespace Text {
struct GlyphInfo_s0089_b520 { uint32_t mBits; uint8_t mScriptFlags; uint8_t mLookupFlags; uint16_t pad; };   // 8 bytes
}
}
namespace EA {
namespace Text {
struct GlyphLayoutInfo_s0089_b520 {
    void* mpFont; float mfPenX; float mfPenY; float mfAdvance;
    float mfX1; float mfY1; float mfX2; float mfY2;
};   // 0x20
}
}
namespace EA {
namespace Text {
struct AnalysisInfo_s0089_b520 { void* mpTextStyle; void* mpFont; int32_t mBits; };   // 0xc
}
}
namespace EA {
namespace Text {
struct Rectangle { float mLeft, mTop, mRight, mBottom; };
}
}
namespace EA {
namespace Text {
struct Span { float mfBegin, mfEnd; };
}
}
namespace EA {
namespace Text {
struct RunInfo_s0089_b520 { int32_t mScript; int32_t mnBidiLevel; uint32_t mnCharBegin; uint32_t mnCharEnd; };
}
}
namespace EA {
namespace Text {
struct FontMetrics { float f[0x11]; };   // only the pairs at +0x2c/+0x30, +0x34/+0x38, +0x3c/+0x40 are used
}
}
namespace EA {
namespace Text {
struct IFont {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void GetFontMetrics(FontMetrics* out);   // +0x30
};
}
}
namespace EA {
namespace Text {
template <typename T>
struct cvec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    ICoreAllocator_s0089_b520* mpAllocator;
    int mFlags;

    unsigned size() const { return mpEnd - mpBegin; }
    unsigned capacity() const { return mpCapacity - mpBegin; }
    T* DoAllocateAndCopy(unsigned n, const T* first, const T* last);   // out-of-line
    cvec& operator=(const cvec& x) { return DoAssign(x); }
    // operator= body; force-inlined so the 0x0089ba90/0x0089bc80 wrappers below carry it
    __forceinline cvec& DoAssign(const cvec& x)
    {
        if (&x != this) {
            const T* pBegin = x.mpBegin;
            T* pDst = mpBegin;
            T* pCap = mpCapacity;
            const T* pEnd = x.mpEnd;
            unsigned n = pEnd - pBegin;
            if ((unsigned)(pCap - pDst) < n) {
                T* p = DoAllocateAndCopy(n, pBegin, pEnd);
                if (mpBegin) mpAllocator->Free(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
                mpCapacity = p + n;
                mpBegin = p;
                mpEnd = p + n;
                return *this;
            }
            unsigned nCur = mpEnd - pDst;
            if (nCur < n) {
                memcpy(pDst, pBegin, nCur * sizeof(T));
                const T* pMid = x.mpBegin + (mpEnd - mpBegin);
                memcpy(mpEnd, pMid, (char*)x.mpEnd - (char*)pMid);
                mpEnd = mpBegin + n;
                return *this;
            }
            memcpy(pDst, pBegin, (char*)pEnd - (char*)pBegin);
            mpEnd = mpBegin + n;
        }
        return *this;
    }
};
}
}
namespace EA {
namespace Text {
struct RectNode { RectNode* mpRight; RectNode* mpLeft; RectNode* mpParent; int mColor; };
}
}
namespace EA {
namespace Text {
struct RectNodeV : RectNode { Rectangle mValue; };
}
}
namespace EA {
namespace Text {
struct RectIter { RectNode* p; };
}
}
namespace EA {
namespace Text {
struct RectSet {
    int pad0;
    RectNode mAnchor;       // +4 (sentinel; leftmost node at +8)
    unsigned mnSize;        // +0x14
    RectIter erase(RectNode* pos);                                              // 0x00898b20
    void DoInsertValue(void* result, const Rectangle& v, bool bForceToLeft);    // 0x0089a7d0
};
}
}
namespace EA {
namespace Text {
RectNode* RBTreeIncrement(RectNode* p);   // 0x00921580 (eastl::RBTreeIncrement)
}
}
namespace EA {
namespace Text {
struct FixedUIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);   // 0x00899480
};
}
}
namespace EA {
namespace Text {
struct LineLayout_s0089_b520 {
    ICoreAllocator_s0089_b520* mpCoreAllocator;                // +0x00
    struct WString {
        wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
        ICoreAllocator_s0089_b520* mpAllocator; int mFlags;
        WString& assign(const wchar_t* first, const wchar_t* last);   // 0x008888b0
    } mCharArray;                                   // +0x04
    cvec<AnalysisInfo_s0089_b520> mAnalysisInfoArray;          // +0x18
    cvec<uint16_t> mGlyphArray;                     // +0x2c
    cvec<GlyphInfo_s0089_b520> mGlyphInfoArray;                // +0x40
    cvec<GlyphLayoutInfo_s0089_b520> mGlyphLayoutInfoArray;    // +0x54
    cvec<uint32_t> mGlyphIndexArray;                // +0x68
    cvec<uint32_t> mCharIndexArray;                 // +0x7c
    uint32_t mLineMetrics[8];                       // +0x90: length, visLength, space, visSpace, baseline, descent, +2

    LineLayout_s0089_b520(const LineLayout_s0089_b520& x);                // 0x0089bf70
    ~LineLayout_s0089_b520();                                  // 0x008323d0
    void NewLine();                                 // 0x0089b080
    void OffsetSegment(float dx, float dy, unsigned first, unsigned last);   // 0x00897b40
    void GetGlyphRangeFromCharRange(unsigned a, unsigned b, unsigned& g0, unsigned& g1) const;   // 0x00897ae0
    unsigned GetGlyphSelection(unsigned a, unsigned b, RectSet* out);        // 0x0089c110
    unsigned GetGlyphDecoration(int type, unsigned a, unsigned b, RectSet* out);   // 0x0089c2d0
};
}
}
namespace EA {
namespace Text {
struct FixedRunVec {
    RunInfo_s0089_b520* mpBegin;
    RunInfo_s0089_b520* mpEnd;
    RunInfo_s0089_b520* mpCapacity;
    unsigned mAllocPad;
    RunInfo_s0089_b520* mpPoolBegin;                                      // +0x10
    void push_back(const RunInfo_s0089_b520& v);                          // 0x0089a620
    void DoInsertValue(RunInfo_s0089_b520* pos, const RunInfo_s0089_b520& v);        // 0x008996d0
    void DoInsertValues(RunInfo_s0089_b520* pos, unsigned n, const RunInfo_s0089_b520& v);   // 0x00899e10
    void resize(unsigned n);                                   // 0x0089be20
    void erase(RunInfo_s0089_b520* first, RunInfo_s0089_b520* last);
    ~FixedRunVec()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete(mpBegin);
    }
};
}
}
namespace EA {
namespace Text {
struct FontSelectionTree {
    unsigned char pad0[0xc];
    void* mpRoot;                                   // +0xc
    void DoNukeSubtree(void* root);                 // 0x0088fda0
    ~FontSelectionTree() { DoNukeSubtree(mpRoot); }
};
}
}
namespace EA {
namespace Text {
struct TextStyleVec {
    void* mpBegin;                                  // +0
    unsigned char pad0[0xc];
    void* mpPool;                                   // +0x10
    ~TextStyleVec()
    {
        if (mpBegin && mpBegin != mpPool)
            operator delete(mpBegin);
    }
};
}
}
namespace EA {
namespace Text {
struct ScheduleVec : cvec<unsigned char> {
    ~ScheduleVec()
    {
        unsigned char* p = mpBegin;
        if (p)
            mpAllocator->Free(p, ((mpCapacity - p) / 0x2c) * 0x2c);
    }
};
}
}
namespace EA {
namespace Text {
struct Typesetter_s0089_b520 {
    unsigned char pad0[0x14];
    int mDirection;                                 // +0x14
    FontSelectionTree mFontSelection;               // +0x18 (root at +0x24)
    unsigned char pad2[0x384 - 0x28];
    TextStyleVec mTextStyleArray;                   // +0x384 (pool at +0x394)
    unsigned char pad4[0x3c0 - 0x398];
    float mfLayoutPenX;                             // +0x3c0
    unsigned char pad5[0x3d0 - 0x3c4];
    ScheduleVec mSchedule;                          // +0x3d0 (Item is 0x2c bytes)
    unsigned char pad6[0x418 - 0x3e4];
    LineLayout_s0089_b520 mLineLayout;                         // +0x418
    unsigned char pad7[0x4cc - 0x4c8];
    FixedRunVec mBidiRunInfoArray;                  // +0x4cc (fixed_vector<RunInfo,4>)
    unsigned char pad8[0x524 - 0x4e0];
    bool mbNonGeneralScriptPresent;                 // +0x524

    ~Typesetter_s0089_b520();                                  // 0x0089c540
    void AdjustWhitespaceEmbedding();               // 0x0089b7e0
    void Justify();                                 // 0x0089b900
    void ShapeLine();                               // 0x0089b520
    void UpdateFontSelection(unsigned a, unsigned b);   // 0x00898630
    void ShapeGeneral(unsigned a, unsigned b);          // 0x008a3430
    void ShapeText(int script, unsigned a, unsigned b); // 0x008976b0
};
}
}
unsigned CharTypeStringRFindFirstNotOf(const wchar_t* pEnd, const wchar_t* pBegin, const wchar_t* pSet, const wchar_t* pSetEnd);   // 0x00897a60 (cdecl)
template <typename T>
struct ResizableVec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void insert(T* pos, unsigned n, const T& v);   // fill-insert (out of line)
    void erase(T* first, T* last);                 // out of line
    void resize(unsigned n) { DoResize(n); }
    // resize body; force-inlined so the 0x0089bdb0 wrapper below carries it
    __forceinline void DoResize(unsigned n)
    {
        T* b = mpBegin;
        if (n > (unsigned)(mpEnd - b)) {
            T v;
            memset_zero(&v);
            insert(mpEnd, n - (mpEnd - b), v);
            return;
        }
        erase(b + n, mpEnd);
    }
    static void memset_zero(T* p) { unsigned* q = (unsigned*)p; for (unsigned i = 0; i < sizeof(T) / 4; ++i) q[i] = 0; }
};
void EA::Text::FixedRunVec::erase(EA::Text::RunInfo_s0089_b520* first, EA::Text::RunInfo_s0089_b520* last)
{
    extern EA::Text::RunInfo_s0089_b520* RunInfoCopy(EA::Text::RunInfo_s0089_b520* a, EA::Text::RunInfo_s0089_b520* b, EA::Text::RunInfo_s0089_b520* c);   // 0x00705250 (cdecl do_copy)
    RunInfoCopy(last, last, first);
    mpEnd = mpEnd + -((int)(last - first)) ;
}
struct SpanNode { SpanNode* mpNext; SpanNode* mpPrev; EA::Text::Span mValue; };
struct SpanList {   // eastl::fixed_list<Span,16,1>
    SpanNode mAnchor;       // sentinel (next, prev)
    unsigned mnSize;
    SpanNode* mpFreeHead;   // +8 of the pool bookkeeping
    SpanNode* mpPoolBegin;
    SpanNode* mpPoolEnd;
    SpanNode mBuffer[16];
    SpanList();                                  // 0x00898ce0
    static void insert(EA::Text::Span* s, SpanList* l);    // 0x0089aed0 (cdecl)
};
// ---- items of slice s0089b520 end

// ---- items of slice s0089d3b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator_delete__(void*);                            // 0x00f47380
namespace EA {
namespace Text {
struct ScheduleLocation_s0089_d3b0 { uint32_t mnScheduleIndex, mnCharBase, mnCharOffset; };
}
}
namespace EA {
namespace Text {
struct RunInfo_s0089_d3b0 { uint32_t mScript; int mnBidiLevel; uint32_t mnCharBegin; uint32_t mnCharEnd; };
}
}
namespace EA {
namespace Text {
struct RunVec {
    RunInfo_s0089_d3b0* mpBegin; RunInfo_s0089_d3b0* mpEnd; RunInfo_s0089_d3b0* mpCapacity; uint32_t pad0;
    RunInfo_s0089_d3b0* mpPoolBegin; uint32_t pad1; RunInfo_s0089_d3b0 mBuffer[4];
    void Init() { RunInfo_s0089_d3b0* b = mBuffer; mpPoolBegin = b; mpEnd = b; mpBegin = b; mpCapacity = b + 4; }
    RunVec& operator=(const RunVec& o);                        // 0x0089d2b0
    void DoInsertValue(RunInfo_s0089_d3b0* pos, const RunInfo_s0089_d3b0& v);        // 0x008996d0
    void resize(uint32_t n);                                   // 0x0089be20
};
}
}
namespace EA {
namespace Text {
struct IdxVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t* mpPoolBegin; uint32_t mBuffer[16];
    void DoInsertValue(uint32_t* pos, const uint32_t& v);      // 0x0060a600
};
}
}
namespace EA {
namespace Text {
struct StyleVec {
    struct TextStyle_s0089_d3b0** mpBegin; struct TextStyle_s0089_d3b0** mpEnd; struct TextStyle_s0089_d3b0** mpCapacity; uint32_t pad0;
    void* mpPoolBegin; uint32_t pad1; struct TextStyle_s0089_d3b0* mBuffer[8];
    void resize(uint32_t n);                                   // 0x0089cb60
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 8; }
};
}
}
namespace EA {
namespace Text {
struct Vec { char* mpBegin; char* mpEnd; char* mpCapacity; void* mpAllocator; uint32_t pad; };  // 0x14
}
}
namespace EA {
namespace Text {
struct StringVec : Vec {
    void resize(uint32_t n);   // 0x00898a30
};
}
}
namespace EA {
namespace Text {
struct AnalysisVec : Vec {
    void resize(uint32_t n);   // 0x0089bc00
};
}
}
namespace EA {
namespace Text {
struct GlyphVec : Vec {
    void resize(uint32_t n);   // 0x00893480
};
}
}
namespace EA {
namespace Text {
struct GlyphInfoVec : Vec {
    void resize(uint32_t n);   // 0x0089bd50
};
}
}
namespace EA {
namespace Text {
struct GlyphLayoutVec : Vec {
    void resize(uint32_t n);   // 0x0089bdb0
};
}
}
namespace EA {
namespace Text {
struct UIntVec : Vec {
    void resize(uint32_t n);   // 0x00887240
};
}
}
namespace EA {
namespace Text {
struct GlyphLayoutInfo_s0089_d3b0 { uint32_t pad0; float mfX; uint32_t pad1; float mfAdvance; uint32_t pad2[4]; };  // 0x20
}
}
namespace EA {
namespace Text {
struct LineLayoutBase {
    void* mpCoreAllocator;       // +0x00
    StringVec mCharArray;              // +0x04  wchar_t
    AnalysisVec mAnalysisInfoArray;      // +0x18
    GlyphVec mGlyphArray;             // +0x2c  uint16
    GlyphInfoVec mGlyphInfoArray;         // +0x40
    GlyphLayoutVec mGlyphLayoutInfoArray;   // +0x54  GlyphLayoutInfo
    UIntVec mGlyphIndexArray;        // +0x68  uint32
    UIntVec mCharIndexArray;         // +0x7c  uint32
    uint32_t mnLength;           // +0x90
    uint32_t pad94;
    float mfWidth;               // +0x98
    uint32_t pad9c;
    float mfA0;                  // +0xa0
    float mfA4;                  // +0xa4
    uint32_t mLineCount;         // +0xa8
    uint32_t padac;

    LineLayoutBase() {}
    void SetAllocator(void* a) {
        mpCoreAllocator = a; mCharArray.mpAllocator = a; mAnalysisInfoArray.mpAllocator = a;
        mGlyphArray.mpAllocator = a; mGlyphInfoArray.mpAllocator = a; mGlyphLayoutInfoArray.mpAllocator = a;
        mGlyphIndexArray.mpAllocator = a; mCharIndexArray.mpAllocator = a;
    }
    LineLayoutBase(void* arg);                                              // 0x00898bd0
    void FUN_00897d60();                                                    // 0x00897d60
    void OffsetSegment(float dx, float dy, uint32_t first, uint32_t last);  // 0x00897b40
    void FUN_0089cc00(LineLayoutBase* dst, void* arg);                      // 0x0089cc00
};
}
}
namespace EA {
namespace Text {
struct TextStyle_s0089_d3b0 {
    char data[0x278];
    TextStyle_s0089_d3b0();                                    // 0x008941d0
    TextStyle_s0089_d3b0(const TextStyle_s0089_d3b0& s);                  // 0x008945a0
    TextStyle_s0089_d3b0& operator=(const TextStyle_s0089_d3b0& s);       // 0x00894280
};
}
}
namespace EA {
namespace Text {
inline int   StyleOverflow(const TextStyle_s0089_d3b0* s)  { return *(const int*)(s->data + 0x254); }
}
}
namespace EA {
namespace Text {
struct LSSub { LSSub(); };                          // 0x0089a570
}
}
namespace EA {
namespace Text {
struct LayoutSettings_s0089_d3b0 {
    char pad0[0x14];
    LSSub mSub;                                     // +0x14
    char pad1[0xf8 - 0x15];
    TextStyle_s0089_d3b0 mTextStyleDefault;                    // +0xf8
    uint32_t pad370;
    float mfYScale;                                 // +0x374
    uint32_t pad378;
    LayoutSettings_s0089_d3b0& operator=(const LayoutSettings_s0089_d3b0& o);   // 0x0089d300
};
}
}
namespace EA {
namespace Text {
struct Typesetter_s0089_d3b0 {
    void* mpCoreAllocator;              // +0x000
    LayoutSettings_s0089_d3b0 mLayoutSettings;     // +0x004
    void* mpFontServer;                 // +0x380
    StyleVec mTextStyleArray;           // +0x384
    TextStyle_s0089_d3b0* mpCurrentTextStyle;      // +0x3bc
    float mfLayoutWidth;                // +0x3c0
    float mfLayoutX;                    // +0x3c4
    float mfLayoutY;                    // +0x3c8
    bool mbEllipsize;                   // +0x3cc
    uint8_t pad3cd;
    uint16_t mPasswordChar;             // +0x3ce
    void* mSchedBegin; void* mSchedEnd; void* mSchedCap; void* mSchedAlloc; void* mSchedPad; // +0x3d0
    ScheduleLocation_s0089_d3b0 mLineBegin;        // +0x3e4
    ScheduleLocation_s0089_d3b0 mLineEnd;          // +0x3f0
    ScheduleLocation_s0089_d3b0 mAnalysisEnd;      // +0x3fc
    ScheduleLocation_s0089_d3b0 mScheduleEnd;      // +0x408
    uint32_t mLineState;                // +0x414  0 partial, 1 full, 2 complete
    LineLayoutBase mLineLayout;         // +0x418
    uint32_t mnLastLineEndIndex;        // +0x4c8
    RunVec mBidiRunInfoArray;           // +0x4cc
    bool mbNonGeneralScriptPresent;     // +0x524
    uint8_t pad525[3];
    float mfPenX;                       // +0x528
    float mfPenXMax;                    // +0x52c

    Typesetter_s0089_d3b0(void* allocator);                                            // 0x0089d820
    void Reset(int);                                                        // 0x0089cdf0
    void AddTextRun(const wchar_t* text, uint32_t len);                     // 0x0089b1e0
    void AddParagraphBreak();                                               // 0x0089b300
    void NextLine(int);                                                     // 0x0089c5d0
    void SubstituteEllipsis();                                              // 0x0089cf80
    void AdjustWhitespaceEmbedding();                                       // 0x0089b7e0
    void AdjustPositioning();                                               // 0x0089c950
    void ReverseGlyphs(GlyphLayoutInfo_s0089_d3b0* first, GlyphLayoutInfo_s0089_d3b0* last, float a, float b);  // 0x008978b0
    void GetScheduleLocationFromCharIndex(uint32_t idx, ScheduleLocation_s0089_d3b0* out, int);      // 0x00898230
    void FUN_0089cf10();                                                    // 0x0089cf10
    void ReorderBidiRunInfoArray(RunVec* out);                              // 0x0089d3b0
    void OrderGlyphs();                                                     // 0x0089d610
    void FinalizeLine();                                                    // 0x0089d9a0
    int LayoutLine(const wchar_t* text, uint32_t len, float x, float y, const TextStyle_s0089_d3b0* style);  // 0x0089db20
    int LayoutParagraph(const wchar_t* text, uint32_t len, float x, float y, float x1, float y1,
                        const TextStyle_s0089_d3b0* style, LineLayoutBase* out, void* arg9);                 // 0x0089dc00
};
}
}
namespace EA {
namespace Text {
inline void IdxPush(IdxVec& v, const uint32_t& x)
{
    if (v.mpEnd < v.mpCapacity) { uint32_t* p = v.mpEnd++; if (p) *p = x; }
    else v.DoInsertValue(v.mpEnd, x);
}
}
}
namespace EA {
namespace Text {
inline uint32_t GlyphIndexOf(LineLayoutBase& L, uint32_t charIdx)
{
    uint32_t cnt = (uint32_t)((L.mGlyphIndexArray.mpEnd - L.mGlyphIndexArray.mpBegin) >> 2);
    if (charIdx < cnt) return ((uint32_t*)L.mGlyphIndexArray.mpBegin)[charIdx];
    return (uint32_t)((L.mGlyphArray.mpEnd - L.mGlyphArray.mpBegin) >> 1);
}
}
}
// ---- items of slice s0089d3b0 end

// @ 0x00705250
Quad16* copy_705250(const Quad16* first, const Quad16* last, Quad16* result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// @ 0x0089b520
void EA::Text::Typesetter_s0089_b520::ShapeLine()
{
    EA::Text::LineLayout_s0089_b520& L = mLineLayout;
    if (L.mCharArray.mpBegin == L.mCharArray.mpEnd) return;
    L.NewLine();
    void* style = *(void**)L.mAnalysisInfoArray.mpBegin;
    unsigned n = L.mCharArray.mpEnd - L.mCharArray.mpBegin;
    unsigned runStart = 0;
    unsigned i = 0;
    if (n != 0) {
        unsigned k = 1;
        int off = 0;
        do {
            void* cur = *(void**)((char*)L.mAnalysisInfoArray.mpBegin + off);
            bool last = (k == n);
            if (last) { ++i; off += 0xc; ++k; }
            if (style != cur || last) {
                UpdateFontSelection(runStart, i);
                style = cur;
                runStart = i;
            }
            ++k; ++i; off += 0xc;
        } while (i < n);
        i = 0;
    }
    if (!mbNonGeneralScriptPresent) {
        unsigned len = L.mCharArray.mpEnd - L.mCharArray.mpBegin;
        EA::Text::RunInfo_s0089_b520 r = { 0x1e, 0, i, len };
        if (mBidiRunInfoArray.mpEnd < mBidiRunInfoArray.mpCapacity) {
            EA::Text::RunInfo_s0089_b520* p = mBidiRunInfoArray.mpEnd;
            mBidiRunInfoArray.mpEnd = p + 1;
            if (p) *p = r;
        } else {
            mBidiRunInfoArray.DoInsertValue(mBidiRunInfoArray.mpEnd, r);
        }
        ShapeGeneral(0, len);
        return;
    }
    // non-general scripts: split into runs of equal script and bidi level
    {
        EA::Text::RunInfo_s0089_b520 r = { -1, 0, 0, 0 };
        if (mBidiRunInfoArray.mpEnd < mBidiRunInfoArray.mpCapacity) {
            EA::Text::RunInfo_s0089_b520* p = mBidiRunInfoArray.mpEnd;
            mBidiRunInfoArray.mpEnd = p + 1;
            if (p) *p = r;
        } else {
            mBidiRunInfoArray.DoInsertValue(mBidiRunInfoArray.mpEnd, r);
            i = 0;
        }
    }
    EA::Text::RunInfo_s0089_b520* pRun = mBidiRunInfoArray.mpBegin;
    int bits0 = L.mAnalysisInfoArray.mpBegin[0].mBits;
    int prevLevel = (bits0 << 16) >> 28;
    unsigned count = L.mCharArray.mpEnd - L.mCharArray.mpBegin;
    unsigned runBegin = 0;
    int prevScript = (bits0 << 25) >> 25;
    unsigned idx = 0;
    unsigned byteOff = 0;
    bool haveChars = count != 0;
    do {
        int script;
        int level;
        if (haveChars) script = (L.mAnalysisInfoArray.mpBegin[idx].mBits << 25) >> 25;
        else script = -1;
        if (idx < count) level = (L.mAnalysisInfoArray.mpBegin[idx].mBits << 16) >> 28;
        else level = -1;
        bool levelChanged = level != prevLevel;
        if (idx == count || script != prevScript || levelChanged) {
            pRun->mnBidiLevel = prevLevel;
            pRun->mScript = prevScript;
            pRun->mnCharEnd = idx;
            ShapeText(prevScript, runBegin, idx);
            prevScript = script;
            prevLevel = level;
            runBegin = idx;
            if (levelChanged && idx != count) {
                EA::Text::RunInfo_s0089_b520 nr = { script, level, idx, idx };
                if (mBidiRunInfoArray.mpEnd < mBidiRunInfoArray.mpCapacity) {
                    EA::Text::RunInfo_s0089_b520* p = mBidiRunInfoArray.mpEnd;
                    mBidiRunInfoArray.mpEnd = p + 1;
                    if (p) *p = nr;
                } else {
                    mBidiRunInfoArray.DoInsertValue(mBidiRunInfoArray.mpEnd, nr);
                }
                pRun = mBidiRunInfoArray.mpEnd - 1;
            }
        }
        ++idx;
        byteOff += 0xc;
        haveChars = idx < count;
    } while (idx <= count);
}

// @ 0x0089b7e0
void EA::Text::Typesetter_s0089_b520::AdjustWhitespaceEmbedding()
{
    if (mBidiRunInfoArray.mpBegin == mBidiRunInfoArray.mpEnd) return;
    EA::Text::RunInfo_s0089_b520* pBack = mBidiRunInfoArray.mpEnd - 1;
    int embedding = pBack->mnBidiLevel % 2;
    if (embedding == mDirection) return;

    const wchar_t* pSet = kWhitespaceChars;
    const wchar_t* pSetEnd = pSet;
    while (*pSetEnd) ++pSetEnd;
    pSetEnd = pSet + (pSetEnd - pSet);
    wchar_t* pBegin = mLineLayout.mCharArray.mpBegin;
    unsigned len = mLineLayout.mCharArray.mpEnd - pBegin;
    int idx;
    wchar_t* pFound = 0;
    if (len != 0) {
        unsigned npos = (unsigned)-1;
        unsigned pos = len - 1;
        const unsigned& m = (pos > npos) ? npos : pos;
        pFound = (wchar_t*)(size_t_)CharTypeStringRFindFirstNotOf(pBegin + m + 1, pBegin, pSet, pSetEnd);
    }
    if (len == 0 || pFound == pBegin) idx = -1;
    else idx = (int)(((char*)pFound - (char*)pBegin) - 2) >> 1;

    unsigned lastIdx = (mLineLayout.mCharArray.mpEnd - mLineLayout.mCharArray.mpBegin) - 1;
    if ((unsigned)idx != lastIdx) {
        if (idx == -1) {
            mBidiRunInfoArray.mpEnd = mBidiRunInfoArray.mpEnd - 1;
            idx = 0;
        } else {
            ++idx;
            pBack->mnCharEnd = idx;
        }
        EA::Text::RunInfo_s0089_b520 r;
        r.mScript = -1;
        r.mnBidiLevel = mDirection;
        r.mnCharBegin = idx;
        r.mnCharEnd = mLineLayout.mCharArray.mpEnd - mLineLayout.mCharArray.mpBegin;
        mBidiRunInfoArray.push_back(r);
    }
}

// @ 0x0089b900
void EA::Text::Typesetter::Justify()
{
    float remaining = mfLayoutSpace - *(float*)((char*)this + 0x4b4);   // minus LineMetrics.mfVisibleSpace
    if (remaining < 0.0f) return;

    uint32_t buffer[64];
    FixedUIntVec spaces;
    spaces.mpBegin = buffer;
    spaces.mpEnd = buffer;
    spaces.mpCapacity = buffer + 64;
    unsigned nChars = *(uint32_t*)((char*)this + 0x4ac);   // LineMetrics.mnVisibleLineLength
    for (uint32_t i = 0; i < nChars; ++i) {
        wchar_t* pc = mLineLayout.mCharArray.mpBegin + i;
        wchar_t c = *pc;
        if (c == L' ' || c == 0xa0 || c == 0x3000 ||
            (c == 0x200b && i != 0 && (uint16_t)(pc[-1] - 0xe00) < 0x80)) {
            if (spaces.mpEnd < spaces.mpCapacity) {
                uint32_t* p = spaces.mpEnd;
                spaces.mpEnd = p + 1;
                if (p) *p = i;
            } else {
                spaces.DoInsertValue(spaces.mpEnd, i);
            }
        }
    }
    if (spaces.mpBegin != spaces.mpEnd) {
        unsigned nSpaces = spaces.mpEnd - spaces.mpBegin;
        float perSpace = remaining / (float)nSpaces;
        for (unsigned k = 0; k < nSpaces; ++k) {
            unsigned next = spaces.mpBegin[k] + 1;
            unsigned glyph;
            if (next < mLineLayout.mGlyphIndexArray.size()) glyph = mLineLayout.mGlyphIndexArray.mpBegin[next];
            else glyph = mLineLayout.mGlyphArray.size();
            mLineLayout.OffsetSegment(perSpace, 0.0f, glyph, mLineLayout.mGlyphLayoutInfoArray.size());
        }
    }
    if (spaces.mpBegin && spaces.mpBegin != buffer) operator delete(spaces.mpBegin);
}

// @ 0x0089ba90
EA::Text::cvec<uint32_t>& __fastcall UIntVec_assign(EA::Text::cvec<uint32_t>* self, int, const EA::Text::cvec<uint32_t>& x)
{ return self->DoAssign(x); }

// @ 0x0089bc80
EA::Text::cvec<uint16_t>& __fastcall UShortVec_assign(EA::Text::cvec<uint16_t>* self, int, const EA::Text::cvec<uint16_t>& x)
{ return self->DoAssign(x); }

// @ 0x0089bdb0
void __fastcall GlyphLayoutInfoVec_resize(ResizableVec<EA::Text::GlyphLayoutInfo_s0089_b520>* self, int, unsigned n)
{ self->DoResize(n); }

// @ 0x0089be20
void EA::Text::FixedRunVec::resize(unsigned n)
{
    EA::Text::RunInfo_s0089_b520* e = mpEnd;
    unsigned sz = e - mpBegin;
    if (n > sz) {
        EA::Text::RunInfo_s0089_b520 v;
        v.mScript = -1;
        v.mnBidiLevel = 0;
        v.mnCharBegin = 0;
        v.mnCharEnd = 0;
        DoInsertValues(e, n - sz, v);
        return;
    }
    EA::Text::RunInfo_s0089_b520* newEnd = mpBegin + n;
    erase(newEnd, e);
}

// @ 0x0089bea0
void AddRectangleToRectangleSet(EA::Text::Rectangle* rect, EA::Text::RectSet* set)
{
    EA::Text::Rectangle r = *rect;
    EA::Text::RectNode* pEnd = &set->mAnchor;
    EA::Text::RectNode* p = *(EA::Text::RectNode**)((char*)set + 8);   // leftmost node
    while (p != pEnd) {
        const EA::Text::Rectangle& q = ((EA::Text::RectNodeV*)p)->mValue;
        if (q.mTop == r.mTop && q.mBottom == r.mBottom && q.mLeft <= r.mRight && r.mLeft <= q.mRight) {
            if (q.mLeft < r.mLeft) r.mLeft = q.mLeft;
            if (r.mRight < q.mRight) r.mRight = q.mRight;
            EA::Text::RectIter it = set->erase(p);
            p = it.p;
        } else {
            p = EA::Text::RBTreeIncrement(p);
        }
    }
    unsigned char result[8];
    set->DoInsertValue(result, r, false);
}

// @ 0x0089bf70
EA::Text::LineLayout_s0089_b520::LineLayout_s0089_b520(const EA::Text::LineLayout_s0089_b520& x)
{
    mCharArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mCharArray.mFlags = 0;
    mCharArray.mpBegin = gEmptyWStr;
    mCharArray.mpEnd = gEmptyWStr;
    mCharArray.mpCapacity = gEmptyWStr + 1;
    mAnalysisInfoArray.mpBegin = 0; mAnalysisInfoArray.mpEnd = 0; mAnalysisInfoArray.mpCapacity = 0;
    mAnalysisInfoArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mAnalysisInfoArray.mFlags = 0;
    mGlyphArray.mpBegin = 0; mGlyphArray.mpEnd = 0; mGlyphArray.mpCapacity = 0;
    mGlyphArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mGlyphArray.mFlags = 0;
    mGlyphInfoArray.mpBegin = 0; mGlyphInfoArray.mpEnd = 0; mGlyphInfoArray.mpCapacity = 0;
    mGlyphInfoArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mGlyphInfoArray.mFlags = 0;
    mGlyphLayoutInfoArray.mpBegin = 0; mGlyphLayoutInfoArray.mpEnd = 0; mGlyphLayoutInfoArray.mpCapacity = 0;
    mGlyphLayoutInfoArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mGlyphLayoutInfoArray.mFlags = 0;
    mGlyphIndexArray.mpBegin = 0; mGlyphIndexArray.mpEnd = 0; mGlyphIndexArray.mpCapacity = 0;
    mGlyphIndexArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mGlyphIndexArray.mFlags = 0;
    mCharIndexArray.mpBegin = 0; mCharIndexArray.mpEnd = 0; mCharIndexArray.mpCapacity = 0;
    mCharIndexArray.mpAllocator = ICoreAllocator_s0089_b520::GetDefaultAllocator();
    mCharIndexArray.mFlags = 0;
    ICoreAllocator_s0089_b520* a = EA::Text::GetAllocator();
    mpCoreAllocator = a;
    mCharArray.mpAllocator = a;
    mAnalysisInfoArray.mpAllocator = a;
    mGlyphArray.mpAllocator = a;
    mGlyphInfoArray.mpAllocator = a;
    mGlyphLayoutInfoArray.mpAllocator = a;
    mGlyphIndexArray.mpAllocator = a;
    mCharIndexArray.mpAllocator = a;

    if (&x.mCharArray != &mCharArray) mCharArray.assign(x.mCharArray.mpBegin, x.mCharArray.mpEnd);
    mAnalysisInfoArray = x.mAnalysisInfoArray;
    mGlyphArray = x.mGlyphArray;
    mGlyphInfoArray = x.mGlyphInfoArray;
    mGlyphLayoutInfoArray = x.mGlyphLayoutInfoArray;
    mGlyphIndexArray = x.mGlyphIndexArray;
    mCharIndexArray = x.mCharIndexArray;
    mLineMetrics[0] = x.mLineMetrics[0];
    mLineMetrics[1] = x.mLineMetrics[1];
    mLineMetrics[2] = x.mLineMetrics[2];
    mLineMetrics[3] = x.mLineMetrics[3];
    mLineMetrics[4] = x.mLineMetrics[4];
    mLineMetrics[5] = x.mLineMetrics[5];
    mLineMetrics[6] = x.mLineMetrics[6];
    mLineMetrics[7] = x.mLineMetrics[7];
}

// @ 0x0089c110
unsigned EA::Text::LineLayout_s0089_b520::GetGlyphSelection(unsigned a, unsigned b, EA::Text::RectSet* out)
{
    SpanList list;
    unsigned g0 = a < mGlyphIndexArray.size() ? mGlyphIndexArray.mpBegin[a] : mGlyphArray.size();
    unsigned g1 = b < mGlyphIndexArray.size() ? mGlyphIndexArray.mpBegin[b] : mGlyphArray.size();
    EA::Text::GlyphLayoutInfo_s0089_b520* pLayout = mGlyphLayoutInfoArray.mpBegin + g0;
    EA::Text::GlyphLayoutInfo_s0089_b520* pLayoutEnd = mGlyphLayoutInfoArray.mpBegin + g1;
    EA::Text::GlyphInfo_s0089_b520* pInfo = mGlyphInfoArray.mpBegin + g0;
    if (pLayout < pLayoutEnd) {
        unsigned n = ((((char*)pLayoutEnd - (char*)pLayout) - 1) >> 5) + 1;
        float* pPen = &pLayout->mfPenX;
        do {
            float adv = pPen[2] / (float)((pInfo->mBits >> 12) & 3);
            float x1 = pPen[0];
            float x2 = x1 + adv;
            EA::Text::Span s;
            s.mfBegin = (x1 <= x2) ? x1 : x2;
            s.mfEnd = (x2 <= x1) ? x1 : x2;
            SpanList::insert(&s, &list);
            pPen += 8;
            ++pInfo;
        } while (--n != 0);
    }
    SpanNode* node = list.mAnchor.mpNext;
    while (node != &list.mAnchor) {
        EA::Text::Rectangle r;
        r.mLeft = node->mValue.mfBegin;
        r.mTop = *(float*)((char*)this + 0xa0);
        r.mRight = node->mValue.mfEnd;
        r.mBottom = *(float*)((char*)this + 0xa4);
        unsigned char result[8];
        out->DoInsertValue(result, r, false);
        node = node->mpNext;
    }
    unsigned count = out->mnSize;
    node = list.mAnchor.mpNext;
    while (node != &list.mAnchor) {
        SpanNode* next = node->mpNext;
        if (node >= list.mpPoolBegin && node < list.mpPoolEnd) {
            node->mpNext = list.mpFreeHead;
            list.mpFreeHead = node;
        } else {
            operator delete(node);
        }
        node = next;
    }
    return count;
}

// @ 0x0089c2d0
unsigned EA::Text::LineLayout_s0089_b520::GetGlyphDecoration(int type, unsigned a, unsigned b, EA::Text::RectSet* out)
{
    if (type == 0) return out->mnSize;
    // the glyph range is written back into the (now dead) char-range parameters
    unsigned& g0 = b;
    unsigned& g1 = a;
    GetGlyphRangeFromCharRange(a, b, g0, g1);
    EA::Text::GlyphLayoutInfo_s0089_b520* base = mGlyphLayoutInfoArray.mpBegin;
    EA::Text::GlyphLayoutInfo_s0089_b520* pLayout = base + g0;
    EA::Text::GlyphLayoutInfo_s0089_b520* pLayoutEnd = base + g1;
    EA::Text::GlyphInfo_s0089_b520* pInfo = mGlyphInfoArray.mpBegin + g0;
    float rect[4] = { 0, 0, 0, 0 };
    EA::Text::FontMetrics metrics;
    metrics.f[0] = 0;
    if (pLayout >= pLayoutEnd) return out->mnSize;
    do {
        float adv = pLayout->mfAdvance / (float)((pInfo->mBits >> 12) & 3);
        float x1 = pLayout->mfPenX;
        float x2 = x1 + adv;
        rect[0] = (x1 <= x2) ? x1 : x2;
        rect[2] = (x2 <= x1) ? x1 : x2;
        EA::Text::GlyphLayoutInfo_s0089_b520* ref = pLayout;
        if (pInfo->mBits & 0x10) {
            EA::Text::GlyphLayoutInfo_s0089_b520* pl = pLayout;
            EA::Text::GlyphInfo_s0089_b520* pi = pInfo;
            bool found = false;
            EA::Text::GlyphLayoutInfo_s0089_b520* pBase = mGlyphLayoutInfoArray.mpBegin;
            if (pl >= base) {
                while (pl >= base) {
                    if (!(pi->mBits & 0x10)) { ref = pl; found = true; break; }
                    --pl; --pi;
                }
            }
            if (!found) {
                EA::Text::GlyphLayoutInfo_s0089_b520* pEnd = pBase + mGlyphLayoutInfoArray.size();
                pl = pLayout; pi = pInfo;
                while (pl < pEnd) {
                    if (!(pi->mBits & 0x10)) { ref = pl; found = true; break; }
                    ++pl; ++pi;
                }
            }
            if (!found) ref = 0;
        }
        if (ref) {
            ((EA::Text::IFont*)ref->mpFont)->GetFontMetrics(&metrics);
            float pos, thick;
            switch (type) {
                case 1:
                    pos = metrics.f[0x2c / 4]; thick = metrics.f[0x30 / 4];
                    goto compute;
                case 2:
                    pos = metrics.f[0x34 / 4]; thick = metrics.f[0x38 / 4];
                    goto compute;
                case 4:
                    pos = metrics.f[0x3c / 4]; thick = metrics.f[0x40 / 4];
                compute:
                    thick *= 0.5f;
                    rect[1] = -pos - thick;
                    rect[3] = thick - pos;
                    break;
                default:
                    break;
            }
            rect[1] = ref->mfPenY + rect[1];
            rect[3] = ref->mfPenY + rect[3];
            AddRectangleToRectangleSet((EA::Text::Rectangle*)rect, out);
        }
        ++pLayout;
        ++pInfo;
    } while (pLayout < pLayoutEnd);
    return out->mnSize;
}

// @ 0x0089c540
EA::Text::Typesetter_s0089_b520::~Typesetter_s0089_b520()
{
}

// @ 0x0089d3b0
namespace EA { namespace Text {
void Typesetter_s0089_d3b0::ReorderBidiRunInfoArray(RunVec* out)
{
    RunVec& runs = mBidiRunInfoArray;
    if ((((char*)runs.mpEnd - (char*)runs.mpBegin) & 0xfffffff0) == 0x10 && runs.mpBegin->mnBidiLevel % 2 == 0) {
        *out = runs;
        return;
    }
    IdxVec idx;
    idx.mpBegin = idx.mpEnd = idx.mBuffer; idx.mpPoolBegin = idx.mBuffer; idx.mpCapacity = idx.mBuffer + 16;
    int maxLevel = (int)0x80000000;
    int lowestOdd = 0x7fffffff;
    uint32_t n = (uint32_t)(runs.mpEnd - runs.mpBegin);
    for (uint32_t i = 0; i < n; ++i) {
        int level = runs.mpBegin[i].mnBidiLevel;
        IdxPush(idx, i);
        if (level > maxLevel) maxLevel = level;
        if (level % 2 != 0 && level < lowestOdd) lowestOdd = level;
    }
    if (maxLevel == (int)0x80000000) maxLevel = 0;
    if (lowestOdd == 0x7fffffff) lowestOdd = 1;
    for (int lvl = maxLevel - 1; lvl >= lowestOdd; --lvl) {
        uint32_t* it = idx.mpBegin;
        uint32_t* end = idx.mpEnd;
        while (it != end) {
            while (it != end && runs.mpBegin[*it].mnBidiLevel < lvl) ++it;
            if (it == end) break;
            uint32_t* e = it;
            while (e != end && runs.mpBegin[*e].mnBidiLevel >= lvl) ++e;
            uint32_t* last = e;
            while (it < --last) { uint32_t t = *it; *it = *last; *last = t; ++it; }
            it = e;
        }
    }
    // out->erase(out->begin(), out->end()): mpEnd -= (end - begin) elements
    {
        RunInfo_s0089_d3b0* b = out->mpBegin;
        RunInfo_s0089_d3b0* e = out->mpEnd;
        for (RunInfo_s0089_d3b0* d = b, *src = e; src != e; ++src, ++d) *d = *src;
        out->mpEnd -= (e - b);
    }
    uint32_t cnt = (uint32_t)(idx.mpEnd - idx.mpBegin);
    for (uint32_t i = 0; i < cnt; ++i) {
        RunInfo_s0089_d3b0* src = runs.mpBegin + idx.mpBegin[i];
        if (out->mpEnd < out->mpCapacity) { RunInfo_s0089_d3b0* p = out->mpEnd++; if (p) *p = *src; }
        else out->DoInsertValue(out->mpEnd, *src);
    }
    if (idx.mpBegin && idx.mpBegin != idx.mBuffer)
        operator_delete__(idx.mpBegin);
}
}}  // namespace EA::Text

// @ 0x0089d610
namespace EA { namespace Text {
void Typesetter_s0089_d3b0::OrderGlyphs()
{
    if (!mbNonGeneralScriptPresent) return;
    uint32_t n = (uint32_t)(mBidiRunInfoArray.mpEnd - mBidiRunInfoArray.mpBegin);
    uint32_t i = 0;
    if (n == 0) return;
    for (;;) {
        if (mBidiRunInfoArray.mpBegin[i].mnBidiLevel % 2 != 0) break;
        ++i;
        if (i >= n) return;
    }
    RunVec ordered;
    ordered.mpBegin = ordered.mpEnd = ordered.mBuffer; ordered.mpPoolBegin = ordered.mBuffer;
    ordered.mpCapacity = ordered.mBuffer + 4;
    ReorderBidiRunInfoArray(&ordered);
    GlyphLayoutInfo_s0089_d3b0* gl = (GlyphLayoutInfo_s0089_d3b0*)mLineLayout.mGlyphLayoutInfoArray.mpBegin;
    float pen = gl->mfX;
    RunInfo_s0089_d3b0* run = ordered.mpBegin;
    int count = (int)(ordered.mpEnd - ordered.mpBegin);
    if (count != 0) {
        for (int r = 0; r < count; ++r, ++run) {
            uint32_t first = run->mnCharBegin, last = run->mnCharEnd;
            if (last > first) {
                uint32_t g0 = GlyphIndexOf(mLineLayout, first);
                GlyphLayoutInfo_s0089_d3b0* base = (GlyphLayoutInfo_s0089_d3b0*)mLineLayout.mGlyphLayoutInfoArray.mpBegin;
                float left = base[g0].mfX;
                float adv0 = base[g0].mfAdvance;
                float shift = pen - base[g0].mfX;
                float l = left;
                if (!(adv0 > 0.0f)) l = left + adv0;
                uint32_t g1 = GlyphIndexOf(mLineLayout, last);
                float right = base[g1 - 1].mfX;
                if (base[g1 - 1].mfAdvance > 0.0f) right = right + base[g1 - 1].mfAdvance;
                float width = right - l;
                mLineLayout.OffsetSegment(shift, 0.0f, g0, g1);
                if (run->mnBidiLevel % 2 != 0)
                    ReverseGlyphs(base + g0, base + g1, pen, width + pen);
                pen = width + pen;
            }
        }
    }
    if (ordered.mpBegin && ordered.mpBegin != ordered.mBuffer)
        operator_delete__(ordered.mpBegin);
}
}}  // namespace EA::Text

// @ 0x0089d9a0
namespace EA { namespace Text {
void Typesetter_s0089_d3b0::FinalizeLine()
{
    if (mLineState == 0 && mAnalysisEnd.mnScheduleIndex != mScheduleEnd.mnScheduleIndex)
        FUN_0089cf10();
    mLineLayout.FUN_00897d60();
    uint32_t len = mLineLayout.mnLength;
    uint32_t curLen = (uint32_t)((mLineLayout.mCharArray.mpEnd - mLineLayout.mCharArray.mpBegin) >> 1);
    if (curLen != len) {
        uint32_t gi = GlyphIndexOf(mLineLayout, len);
        mLineLayout.mGlyphArray.resize(gi);
        mLineLayout.mGlyphInfoArray.resize(gi);
        mLineLayout.mGlyphLayoutInfoArray.resize(gi);
        mLineLayout.mCharIndexArray.resize(gi);
        mLineLayout.mCharArray.resize(len);
        mLineLayout.mAnalysisInfoArray.resize(len);
        mLineLayout.mGlyphIndexArray.resize(len);
        uint32_t n = (uint32_t)(mBidiRunInfoArray.mpEnd - mBidiRunInfoArray.mpBegin);
        RunInfo_s0089_d3b0* run = mBidiRunInfoArray.mpBegin;
        for (uint32_t i = 0; i < n; ) {
            ++i;
            if (run->mnCharEnd >= len) {
                run->mnCharEnd = len;
                mBidiRunInfoArray.resize(i);
                break;
            }
            ++run;
        }
    }
    GetScheduleLocationFromCharIndex(mLineBegin.mnCharOffset + mLineBegin.mnCharBase + mLineLayout.mnLength,
                                     &mLineEnd, 0);
    mAnalysisEnd.mnScheduleIndex = mLineEnd.mnScheduleIndex;
    mnLastLineEndIndex += mLineLayout.mnLength;
    mAnalysisEnd.mnCharBase = mLineEnd.mnCharBase;
    mAnalysisEnd.mnCharOffset = mLineEnd.mnCharOffset;
    mLineState = 1;
    if (mbEllipsize) SubstituteEllipsis();
    AdjustWhitespaceEmbedding();
    AdjustPositioning();
    OrderGlyphs();
}
}}  // namespace EA::Text

// @ 0x0089db20
namespace EA { namespace Text {
int Typesetter_s0089_d3b0::LayoutLine(const wchar_t* text, uint32_t len, float x, float y, const TextStyle_s0089_d3b0* style)
{
    Reset(1);
    mfLayoutWidth = 100000.0f;
    mfLayoutX = x;
    mfLayoutY = y;
    if (style) {
        mLayoutSettings.mTextStyleDefault = *style;
        *mTextStyleArray.mpBegin = &mLayoutSettings.mTextStyleDefault;
        mpCurrentTextStyle = *mTextStyleArray.mpBegin;
    }
    *(int*)((char*)&mLayoutSettings + 0x33c) = 0;      // mTextStyleDefault.mHAlignment
    AddTextRun(text, len);
    if (StyleOverflow(style) == 2) mbEllipsize = true;
    FinalizeLine();
    mLineLayout.OffsetSegment(0.0f, 0.0f, 0, (mLineLayout.mGlyphLayoutInfoArray.mpEnd - mLineLayout.mGlyphLayoutInfoArray.mpBegin) >> 5);
    return (int)(mLineLayout.mGlyphArray.mpEnd - mLineLayout.mGlyphArray.mpBegin) >> 1;
}
}}  // namespace EA::Text

// @ 0x011e0906
double iat_floor(double x)
{ return x; }
