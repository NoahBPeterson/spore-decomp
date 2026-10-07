// Slice s0089b520: EA::Text Typesetter / LineLayout (retail layout; offsets taken from the asm).
// Built /O2 /MD /Gy /TP /arch:SSE /GS-   (no /EHsc: no unwind tables in this module)
#include "types.h"

typedef unsigned int size_t_;
void operator delete(void* p) throw();
inline void* operator new(size_t_, void* p) { return p; }
inline void operator delete(void*, void*) throw() {}
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
extern wchar_t gEmptyWStr[2];   // 0x01667bac: shared empty-string storage

namespace EA { namespace Allocator {
struct ICoreAllocator {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Free(void* p, unsigned size);   // +0xc
    static ICoreAllocator* GetDefaultAllocator();   // 0x00925cb0
};
}}
using EA::Allocator::ICoreAllocator;

namespace EA { namespace Text {
ICoreAllocator* GetAllocator();   // 0x008859d0

// ---- value types -------------------------------------------------------
struct GlyphInfo { uint32_t mBits; uint8_t mScriptFlags; uint8_t mLookupFlags; uint16_t pad; };   // 8 bytes
struct GlyphLayoutInfo {
    void* mpFont; float mfPenX; float mfPenY; float mfAdvance;
    float mfX1; float mfY1; float mfX2; float mfY2;
};   // 0x20
struct AnalysisInfo { void* mpTextStyle; void* mpFont; int32_t mBits; };   // 0xc
struct Rectangle { float mLeft, mTop, mRight, mBottom; };
struct Span { float mfBegin, mfEnd; };
struct RunInfo { int32_t mScript; int32_t mnBidiLevel; uint32_t mnCharBegin; uint32_t mnCharEnd; };

struct FontMetrics { float f[0x11]; };   // only the pairs at +0x2c/+0x30, +0x34/+0x38, +0x3c/+0x40 are used
struct IFont {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void GetFontMetrics(FontMetrics* out);   // +0x30
};

// ---- EASTL vector with EASTLCoreAllocator (0x14 bytes) ------------------
template <typename T>
struct cvec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    ICoreAllocator* mpAllocator;
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

// ---- rectangle set (eastl::set<Rectangle> with fixed node pool) --------
struct RectNode { RectNode* mpRight; RectNode* mpLeft; RectNode* mpParent; int mColor; };
struct RectNodeV : RectNode { Rectangle mValue; };
struct RectIter { RectNode* p; };
struct RectSet {
    int pad0;
    RectNode mAnchor;       // +4 (sentinel; leftmost node at +8)
    unsigned mnSize;        // +0x14
    RectIter erase(RectNode* pos);                                              // 0x00898b20
    void DoInsertValue(void* result, const Rectangle& v, bool bForceToLeft);    // 0x0089a7d0
};
RectNode* RBTreeIncrement(RectNode* p);   // 0x00921580 (eastl::RBTreeIncrement)

// ---- fixed_vector<uint32, 64> scratch used by Justify -------------------
struct FixedUIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);   // 0x00899480
};

// ---- LineLayout (retail, 0xb0 bytes) ------------------------------------
struct LineLayout {
    ICoreAllocator* mpCoreAllocator;                // +0x00
    struct WString {
        wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
        ICoreAllocator* mpAllocator; int mFlags;
        WString& assign(const wchar_t* first, const wchar_t* last);   // 0x008888b0
    } mCharArray;                                   // +0x04
    cvec<AnalysisInfo> mAnalysisInfoArray;          // +0x18
    cvec<uint16_t> mGlyphArray;                     // +0x2c
    cvec<GlyphInfo> mGlyphInfoArray;                // +0x40
    cvec<GlyphLayoutInfo> mGlyphLayoutInfoArray;    // +0x54
    cvec<uint32_t> mGlyphIndexArray;                // +0x68
    cvec<uint32_t> mCharIndexArray;                 // +0x7c
    uint32_t mLineMetrics[8];                       // +0x90: length, visLength, space, visSpace, baseline, descent, +2

    LineLayout(const LineLayout& x);                // 0x0089bf70
    ~LineLayout();                                  // 0x008323d0
    void NewLine();                                 // 0x0089b080
    void OffsetSegment(float dx, float dy, unsigned first, unsigned last);   // 0x00897b40
    void GetGlyphRangeFromCharRange(unsigned a, unsigned b, unsigned& g0, unsigned& g1) const;   // 0x00897ae0
    unsigned GetGlyphSelection(unsigned a, unsigned b, RectSet* out);        // 0x0089c110
    unsigned GetGlyphDecoration(int type, unsigned a, unsigned b, RectSet* out);   // 0x0089c2d0
};

struct FixedRunVec {
    RunInfo* mpBegin;
    RunInfo* mpEnd;
    RunInfo* mpCapacity;
    unsigned mAllocPad;
    RunInfo* mpPoolBegin;                                      // +0x10
    void push_back(const RunInfo& v);                          // 0x0089a620
    void DoInsertValue(RunInfo* pos, const RunInfo& v);        // 0x008996d0
    void DoInsertValues(RunInfo* pos, unsigned n, const RunInfo& v);   // 0x00899e10
    void resize(unsigned n);                                   // 0x0089be20
    void erase(RunInfo* first, RunInfo* last);
    ~FixedRunVec()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete(mpBegin);
    }
};

// ---- Typesetter (retail offsets) ---------------------------------------
// fixed_set<AutoRefCount<Font>> (Typesetter +0x18): anchor at +4, root (anchor parent) at +0xc
struct FontSelectionTree {
    unsigned char pad0[0xc];
    void* mpRoot;                                   // +0xc
    void DoNukeSubtree(void* root);                 // 0x0088fda0
    ~FontSelectionTree() { DoNukeSubtree(mpRoot); }
};
// fixed_vector of text styles (Typesetter +0x384): pool buffer pointer at +0x10
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
// vector<Item> with EASTLCoreAllocator (Typesetter +0x3d0), Item is 0x2c bytes
struct ScheduleVec : cvec<unsigned char> {
    ~ScheduleVec()
    {
        unsigned char* p = mpBegin;
        if (p)
            mpAllocator->Free(p, ((mpCapacity - p) / 0x2c) * 0x2c);
    }
};
struct Typesetter {
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
    LineLayout mLineLayout;                         // +0x418
    unsigned char pad7[0x4cc - 0x4c8];
    FixedRunVec mBidiRunInfoArray;                  // +0x4cc (fixed_vector<RunInfo,4>)
    unsigned char pad8[0x524 - 0x4e0];
    bool mbNonGeneralScriptPresent;                 // +0x524

    ~Typesetter();                                  // 0x0089c540
    void AdjustWhitespaceEmbedding();               // 0x0089b7e0
    void Justify();                                 // 0x0089b900
    void ShapeLine();                               // 0x0089b520
    void UpdateFontSelection(unsigned a, unsigned b);   // 0x00898630
    void ShapeGeneral(unsigned a, unsigned b);          // 0x008a3430
    void ShapeText(int script, unsigned a, unsigned b); // 0x008976b0
};
}}  // namespace EA::Text

using namespace EA::Text;

// ===========================================================================
// 0x0089b520: Typesetter::ShapeLine (name from PDB candidate: ShapeText driver)
// ===========================================================================
void Typesetter::ShapeLine()
{
    LineLayout& L = mLineLayout;
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
        RunInfo r = { 0x1e, 0, i, len };
        if (mBidiRunInfoArray.mpEnd < mBidiRunInfoArray.mpCapacity) {
            RunInfo* p = mBidiRunInfoArray.mpEnd;
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
        RunInfo r = { -1, 0, 0, 0 };
        if (mBidiRunInfoArray.mpEnd < mBidiRunInfoArray.mpCapacity) {
            RunInfo* p = mBidiRunInfoArray.mpEnd;
            mBidiRunInfoArray.mpEnd = p + 1;
            if (p) *p = r;
        } else {
            mBidiRunInfoArray.DoInsertValue(mBidiRunInfoArray.mpEnd, r);
            i = 0;
        }
    }
    RunInfo* pRun = mBidiRunInfoArray.mpBegin;
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
                RunInfo nr = { script, level, idx, idx };
                if (mBidiRunInfoArray.mpEnd < mBidiRunInfoArray.mpCapacity) {
                    RunInfo* p = mBidiRunInfoArray.mpEnd;
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

// ===========================================================================
// 0x0089b7e0: Typesetter::AdjustWhitespaceEmbedding
// ===========================================================================
extern const wchar_t kWhitespaceChars[];   // 0x0142ef80 (L" \r\n\t")
unsigned CharTypeStringRFindFirstNotOf(const wchar_t* pEnd, const wchar_t* pBegin, const wchar_t* pSet, const wchar_t* pSetEnd);   // 0x00897a60 (cdecl)

void Typesetter::AdjustWhitespaceEmbedding()
{
    if (mBidiRunInfoArray.mpBegin == mBidiRunInfoArray.mpEnd) return;
    RunInfo* pBack = mBidiRunInfoArray.mpEnd - 1;
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
        RunInfo r;
        r.mScript = -1;
        r.mnBidiLevel = mDirection;
        r.mnCharBegin = idx;
        r.mnCharEnd = mLineLayout.mCharArray.mpEnd - mLineLayout.mCharArray.mpBegin;
        mBidiRunInfoArray.push_back(r);
    }
}

// ===========================================================================
// 0x0089b900: Typesetter::Justify
// ===========================================================================
void Typesetter::Justify()
{
    float remaining = mfLayoutPenX - *(float*)((char*)this + 0x4b4);   // minus LineMetrics.mfVisibleSpace
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

// ===========================================================================
// vector<uint32>::operator= (0x0089ba90) and vector<uint16>::operator= (0x0089bc80)
// ===========================================================================
// @ 0x0089ba90
cvec<uint32_t>& __fastcall UIntVec_assign(cvec<uint32_t>* self, int, const cvec<uint32_t>& x) { return self->DoAssign(x); }
// @ 0x0089bc80
cvec<uint16_t>& __fastcall UShortVec_assign(cvec<uint16_t>* self, int, const cvec<uint16_t>& x) { return self->DoAssign(x); }

// ===========================================================================
// vector::resize helpers (0x0089bd50, 0x0089bdb0, 0x0089be20)
// ===========================================================================
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
// @ 0x0089bd50
void __fastcall GlyphInfoVec_resize(ResizableVec<GlyphInfo>* self, int, unsigned n) { self->resize(n); }
// @ 0x0089bdb0
void __fastcall GlyphLayoutInfoVec_resize(ResizableVec<GlyphLayoutInfo>* self, int, unsigned n) { self->DoResize(n); }

// @ 0x0089be20: fixed_vector<RunInfo,4>::resize
void FixedRunVec::resize(unsigned n)
{
    RunInfo* e = mpEnd;
    unsigned sz = e - mpBegin;
    if (n > sz) {
        RunInfo v;
        v.mScript = -1;
        v.mnBidiLevel = 0;
        v.mnCharBegin = 0;
        v.mnCharEnd = 0;
        DoInsertValues(e, n - sz, v);
        return;
    }
    RunInfo* newEnd = mpBegin + n;
    erase(newEnd, e);
}
void FixedRunVec::erase(RunInfo* first, RunInfo* last)
{
    extern RunInfo* RunInfoCopy(RunInfo* a, RunInfo* b, RunInfo* c);   // 0x00705250 (cdecl do_copy)
    RunInfoCopy(last, last, first);
    mpEnd = mpEnd + -((int)(last - first)) ;
}

// ===========================================================================
// 0x0089bea0: AddRectangleToRectangleSet
// ===========================================================================
namespace {
void AddRectangleToRectangleSet(Rectangle* rect, RectSet* set)
{
    Rectangle r = *rect;
    RectNode* pEnd = &set->mAnchor;
    RectNode* p = *(RectNode**)((char*)set + 8);   // leftmost node
    while (p != pEnd) {
        const Rectangle& q = ((RectNodeV*)p)->mValue;
        if (q.mTop == r.mTop && q.mBottom == r.mBottom && q.mLeft <= r.mRight && r.mLeft <= q.mRight) {
            if (q.mLeft < r.mLeft) r.mLeft = q.mLeft;
            if (r.mRight < q.mRight) r.mRight = q.mRight;
            RectIter it = set->erase(p);
            p = it.p;
        } else {
            p = RBTreeIncrement(p);
        }
    }
    unsigned char result[8];
    set->DoInsertValue(result, r, false);
}
}  // namespace

// ===========================================================================
// 0x0089bf70: LineLayout copy constructor
// ===========================================================================
LineLayout::LineLayout(const LineLayout& x)
{
    mCharArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mCharArray.mFlags = 0;
    mCharArray.mpBegin = gEmptyWStr;
    mCharArray.mpEnd = gEmptyWStr;
    mCharArray.mpCapacity = gEmptyWStr + 1;
    mAnalysisInfoArray.mpBegin = 0; mAnalysisInfoArray.mpEnd = 0; mAnalysisInfoArray.mpCapacity = 0;
    mAnalysisInfoArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mAnalysisInfoArray.mFlags = 0;
    mGlyphArray.mpBegin = 0; mGlyphArray.mpEnd = 0; mGlyphArray.mpCapacity = 0;
    mGlyphArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mGlyphArray.mFlags = 0;
    mGlyphInfoArray.mpBegin = 0; mGlyphInfoArray.mpEnd = 0; mGlyphInfoArray.mpCapacity = 0;
    mGlyphInfoArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mGlyphInfoArray.mFlags = 0;
    mGlyphLayoutInfoArray.mpBegin = 0; mGlyphLayoutInfoArray.mpEnd = 0; mGlyphLayoutInfoArray.mpCapacity = 0;
    mGlyphLayoutInfoArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mGlyphLayoutInfoArray.mFlags = 0;
    mGlyphIndexArray.mpBegin = 0; mGlyphIndexArray.mpEnd = 0; mGlyphIndexArray.mpCapacity = 0;
    mGlyphIndexArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mGlyphIndexArray.mFlags = 0;
    mCharIndexArray.mpBegin = 0; mCharIndexArray.mpEnd = 0; mCharIndexArray.mpCapacity = 0;
    mCharIndexArray.mpAllocator = ICoreAllocator::GetDefaultAllocator();
    mCharIndexArray.mFlags = 0;
    ICoreAllocator* a = GetAllocator();
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

// ===========================================================================
// 0x0089c110: LineLayout::GetGlyphSelection
// ===========================================================================
struct SpanNode { SpanNode* mpNext; SpanNode* mpPrev; Span mValue; };
struct SpanList {   // eastl::fixed_list<Span,16,1>
    SpanNode mAnchor;       // sentinel (next, prev)
    unsigned mnSize;
    SpanNode* mpFreeHead;   // +8 of the pool bookkeeping
    SpanNode* mpPoolBegin;
    SpanNode* mpPoolEnd;
    SpanNode mBuffer[16];
    SpanList();                                  // 0x00898ce0
    static void insert(Span* s, SpanList* l);    // 0x0089aed0 (cdecl)
};

unsigned LineLayout::GetGlyphSelection(unsigned a, unsigned b, RectSet* out)
{
    SpanList list;
    unsigned g0 = a < mGlyphIndexArray.size() ? mGlyphIndexArray.mpBegin[a] : mGlyphArray.size();
    unsigned g1 = b < mGlyphIndexArray.size() ? mGlyphIndexArray.mpBegin[b] : mGlyphArray.size();
    GlyphLayoutInfo* pLayout = mGlyphLayoutInfoArray.mpBegin + g0;
    GlyphLayoutInfo* pLayoutEnd = mGlyphLayoutInfoArray.mpBegin + g1;
    GlyphInfo* pInfo = mGlyphInfoArray.mpBegin + g0;
    if (pLayout < pLayoutEnd) {
        unsigned n = ((((char*)pLayoutEnd - (char*)pLayout) - 1) >> 5) + 1;
        float* pPen = &pLayout->mfPenX;
        do {
            float adv = pPen[2] / (float)((pInfo->mBits >> 12) & 3);
            float x1 = pPen[0];
            float x2 = x1 + adv;
            Span s;
            s.mfBegin = (x1 <= x2) ? x1 : x2;
            s.mfEnd = (x2 <= x1) ? x1 : x2;
            SpanList::insert(&s, &list);
            pPen += 8;
            ++pInfo;
        } while (--n != 0);
    }
    SpanNode* node = list.mAnchor.mpNext;
    while (node != &list.mAnchor) {
        Rectangle r;
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

// ===========================================================================
// 0x0089c2d0: LineLayout::GetGlyphDecoration
// ===========================================================================
unsigned LineLayout::GetGlyphDecoration(int type, unsigned a, unsigned b, RectSet* out)
{
    if (type == 0) return out->mnSize;
    // the glyph range is written back into the (now dead) char-range parameters
    unsigned& g0 = b;
    unsigned& g1 = a;
    GetGlyphRangeFromCharRange(a, b, g0, g1);
    GlyphLayoutInfo* base = mGlyphLayoutInfoArray.mpBegin;
    GlyphLayoutInfo* pLayout = base + g0;
    GlyphLayoutInfo* pLayoutEnd = base + g1;
    GlyphInfo* pInfo = mGlyphInfoArray.mpBegin + g0;
    float rect[4] = { 0, 0, 0, 0 };
    FontMetrics metrics;
    metrics.f[0] = 0;
    if (pLayout >= pLayoutEnd) return out->mnSize;
    do {
        float adv = pLayout->mfAdvance / (float)((pInfo->mBits >> 12) & 3);
        float x1 = pLayout->mfPenX;
        float x2 = x1 + adv;
        rect[0] = (x1 <= x2) ? x1 : x2;
        rect[2] = (x2 <= x1) ? x1 : x2;
        GlyphLayoutInfo* ref = pLayout;
        if (pInfo->mBits & 0x10) {
            GlyphLayoutInfo* pl = pLayout;
            GlyphInfo* pi = pInfo;
            bool found = false;
            GlyphLayoutInfo* pBase = mGlyphLayoutInfoArray.mpBegin;
            if (pl >= base) {
                while (pl >= base) {
                    if (!(pi->mBits & 0x10)) { ref = pl; found = true; break; }
                    --pl; --pi;
                }
            }
            if (!found) {
                GlyphLayoutInfo* pEnd = pBase + mGlyphLayoutInfoArray.size();
                pl = pLayout; pi = pInfo;
                while (pl < pEnd) {
                    if (!(pi->mBits & 0x10)) { ref = pl; found = true; break; }
                    ++pl; ++pi;
                }
            }
            if (!found) ref = 0;
        }
        if (ref) {
            ((IFont*)ref->mpFont)->GetFontMetrics(&metrics);
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
            AddRectangleToRectangleSet((Rectangle*)rect, out);
        }
        ++pLayout;
        ++pInfo;
    } while (pLayout < pLayoutEnd);
    return out->mnSize;
}

// ===========================================================================
// 0x0089c540: Typesetter::~Typesetter
// ===========================================================================
// The body is empty: the members are destroyed in reverse declaration order (bidi runs,
// LineLayout, schedule, text styles, font-selection tree), which is the original's call order.
Typesetter::~Typesetter()
{
}
