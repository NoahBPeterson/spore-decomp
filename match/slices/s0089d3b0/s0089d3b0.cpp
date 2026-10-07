#include "types.h"

extern "C" double __cdecl ceil(double);
extern "C" double __cdecl FloorThunk_011e0906(double);   // 0x011e0906: floor() through a local thunk
void operator_delete__(void*);                            // 0x00f47380

inline void* operator new(unsigned int, void* p) throw() { return p; }

namespace EA { namespace Text {

enum BidiClass { };

struct ScheduleLocation { uint32_t mnScheduleIndex, mnCharBase, mnCharOffset; };

struct RunInfo { uint32_t mScript; int mnBidiLevel; uint32_t mnCharBegin; uint32_t mnCharEnd; };

// eastl::fixed_vector<RunInfo,4,true>, retail layout
struct RunVec {
    RunInfo* mpBegin; RunInfo* mpEnd; RunInfo* mpCapacity; uint32_t pad0;
    RunInfo* mpPoolBegin; uint32_t pad1; RunInfo mBuffer[4];
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 4; }
    RunVec& operator=(const RunVec& o);                        // 0x0089d2b0
    void DoInsertValue(RunInfo* pos, const RunInfo& v);        // 0x008996d0
    void resize(uint32_t n);                                   // 0x0089be20
};

// eastl::fixed_vector<unsigned,16,true>
struct IdxVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t* mpPoolBegin; uint32_t mBuffer[16];
    void DoInsertValue(uint32_t* pos, const uint32_t& v);      // 0x0060a600
};

// eastl::fixed_vector<const TextStyle*,8,true>
struct StyleVec {
    struct TextStyle** mpBegin; struct TextStyle** mpEnd; struct TextStyle** mpCapacity; uint32_t pad0;
    void* mpPoolBegin; uint32_t pad1; struct TextStyle* mBuffer[8];
    void resize(uint32_t n);                                   // 0x0089cb60
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 8; }
};

struct Vec { char* mpBegin; char* mpEnd; char* mpCapacity; void* mpAllocator; uint32_t pad; };  // 0x14
struct StringVec : Vec { void resize(uint32_t n); };      // 0x00898a30
struct AnalysisVec : Vec { void resize(uint32_t n); };    // 0x0089bc00
struct GlyphVec : Vec { void resize(uint32_t n); };       // 0x00893480
struct GlyphInfoVec : Vec { void resize(uint32_t n); };   // 0x0089bd50
struct GlyphLayoutVec : Vec { void resize(uint32_t n); }; // 0x0089bdb0
struct UIntVec : Vec { void resize(uint32_t n); };        // 0x00887240

struct GlyphLayoutInfo { uint32_t pad0; float mfX; uint32_t pad1; float mfAdvance; uint32_t pad2[4]; };  // 0x20

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

struct LineLayout : LineLayoutBase {
    LineLayout(const LineLayoutBase* src);                                  // 0x0089bf70
    ~LineLayout();                                                          // 0x008323d0
};

struct TextStyle {
    char data[0x278];
    TextStyle();                                    // 0x008941d0
    TextStyle(const TextStyle& s);                  // 0x008945a0
    TextStyle& operator=(const TextStyle& s);       // 0x00894280
};
// fields of TextStyle read by the typesetter
inline float StyleSize(const TextStyle* s)      { return *(const float*)(s->data + 0x200); }
inline int   StyleHAlign(const TextStyle* s)    { return *(const int*)(s->data + 0x244); }
inline int   StyleVAlign(const TextStyle* s)    { return *(const int*)(s->data + 0x248); }
inline int   StyleWrap(const TextStyle* s)      { return *(const int*)(s->data + 0x250); }
inline int   StyleOverflow(const TextStyle* s)  { return *(const int*)(s->data + 0x254); }
inline float StyleLineSpace(const TextStyle* s) { return *(const float*)(s->data + 0x274); }

struct LSSub { LSSub(); };                          // 0x0089a570
struct LayoutSettings {
    char pad0[0x14];
    LSSub mSub;                                     // +0x14
    char pad1[0xf8 - 0x15];
    TextStyle mTextStyleDefault;                    // +0xf8
    uint32_t pad370;
    float mfYScale;                                 // +0x374
    uint32_t pad378;
    LayoutSettings& operator=(const LayoutSettings& o);   // 0x0089d300
};
extern LayoutSettings gDefaultLayoutSettings;       // 0x01549840

void* GetAllocator();                               // 0x008859d0
void* GetDefaultAllocator();                        // 0x00925cb0

struct Typesetter {
    void* mpCoreAllocator;              // +0x000
    LayoutSettings mLayoutSettings;     // +0x004
    void* mpFontServer;                 // +0x380
    StyleVec mTextStyleArray;           // +0x384
    TextStyle* mpCurrentTextStyle;      // +0x3bc
    float mfLayoutWidth;                // +0x3c0
    float mfLayoutX;                    // +0x3c4
    float mfLayoutY;                    // +0x3c8
    bool mbEllipsize;                   // +0x3cc
    uint8_t pad3cd;
    uint16_t mPasswordChar;             // +0x3ce
    void* mSchedBegin; void* mSchedEnd; void* mSchedCap; void* mSchedAlloc; void* mSchedPad; // +0x3d0
    ScheduleLocation mLineBegin;        // +0x3e4
    ScheduleLocation mLineEnd;          // +0x3f0
    ScheduleLocation mAnalysisEnd;      // +0x3fc
    ScheduleLocation mScheduleEnd;      // +0x408
    uint32_t mLineState;                // +0x414  0 partial, 1 full, 2 complete
    LineLayoutBase mLineLayout;         // +0x418
    uint32_t mnLastLineEndIndex;        // +0x4c8
    RunVec mBidiRunInfoArray;           // +0x4cc
    bool mbNonGeneralScriptPresent;     // +0x524
    uint8_t pad525[3];
    float mfPenX;                       // +0x528
    float mfPenXMax;                    // +0x52c

    Typesetter(void* allocator);                                            // 0x0089d820
    void Reset(int);                                                        // 0x0089cdf0
    void AddTextRun(const wchar_t* text, uint32_t len);                     // 0x0089b1e0
    void AddParagraphBreak();                                               // 0x0089b300
    void NextLine(int);                                                     // 0x0089c5d0
    void SubstituteEllipsis();                                              // 0x0089cf80
    void AdjustWhitespaceEmbedding();                                       // 0x0089b7e0
    void AdjustPositioning();                                               // 0x0089c950
    void ReverseGlyphs(GlyphLayoutInfo* first, GlyphLayoutInfo* last, float a, float b);  // 0x008978b0
    void GetScheduleLocationFromCharIndex(uint32_t idx, ScheduleLocation* out, int);      // 0x00898230
    void FUN_0089cf10();                                                    // 0x0089cf10
    void ReorderBidiRunInfoArray(RunVec* out);                              // 0x0089d3b0
    void OrderGlyphs();                                                     // 0x0089d610
    void FinalizeLine();                                                    // 0x0089d9a0
    int LayoutLine(const wchar_t* text, uint32_t len, float x, float y, const TextStyle* style);  // 0x0089db20
    int LayoutParagraph(const wchar_t* text, uint32_t len, float x, float y, float x1, float y1,
                        const TextStyle* style, LineLayoutBase* out, void* arg9);                 // 0x0089dc00
};

inline void IdxPush(IdxVec& v, const uint32_t& x)
{
    if (v.mpEnd < v.mpCapacity) { uint32_t* p = v.mpEnd++; if (p) *p = x; }
    else v.DoInsertValue(v.mpEnd, x);
}

// @ 0x0089d3b0
void Typesetter::ReorderBidiRunInfoArray(RunVec* out)
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
        RunInfo* b = out->mpBegin;
        RunInfo* e = out->mpEnd;
        for (RunInfo* d = b, *src = e; src != e; ++src, ++d) *d = *src;
        out->mpEnd -= (e - b);
    }
    uint32_t cnt = (uint32_t)(idx.mpEnd - idx.mpBegin);
    for (uint32_t i = 0; i < cnt; ++i) {
        RunInfo* src = runs.mpBegin + idx.mpBegin[i];
        if (out->mpEnd < out->mpCapacity) { RunInfo* p = out->mpEnd++; if (p) *p = *src; }
        else out->DoInsertValue(out->mpEnd, *src);
    }
    if (idx.mpBegin && idx.mpBegin != idx.mBuffer)
        operator_delete__(idx.mpBegin);
}

inline uint32_t GlyphIndexOf(LineLayoutBase& L, uint32_t charIdx)
{
    uint32_t cnt = (uint32_t)((L.mGlyphIndexArray.mpEnd - L.mGlyphIndexArray.mpBegin) >> 2);
    if (charIdx < cnt) return ((uint32_t*)L.mGlyphIndexArray.mpBegin)[charIdx];
    return (uint32_t)((L.mGlyphArray.mpEnd - L.mGlyphArray.mpBegin) >> 1);
}

// @ 0x0089d610
void Typesetter::OrderGlyphs()
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
    GlyphLayoutInfo* gl = (GlyphLayoutInfo*)mLineLayout.mGlyphLayoutInfoArray.mpBegin;
    float pen = gl->mfX;
    RunInfo* run = ordered.mpBegin;
    int count = (int)(ordered.mpEnd - ordered.mpBegin);
    if (count != 0) {
        for (int r = 0; r < count; ++r, ++run) {
            uint32_t first = run->mnCharBegin, last = run->mnCharEnd;
            if (last > first) {
                uint32_t g0 = GlyphIndexOf(mLineLayout, first);
                GlyphLayoutInfo* base = (GlyphLayoutInfo*)mLineLayout.mGlyphLayoutInfoArray.mpBegin;
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

// @ 0x0089d820
Typesetter::Typesetter(void* allocator) : mpCoreAllocator(0)
{
    mLayoutSettings = gDefaultLayoutSettings;
    mpFontServer = 0;
    mTextStyleArray.Init();
    mTextStyleArray.resize(1);
    mpCurrentTextStyle = 0;
    mfLayoutWidth = 0.0f;
    mfLayoutX = 0.0f;
    mfLayoutY = 0.0f;
    mbEllipsize = false;
    mPasswordChar = 0x25cf;
    mSchedAlloc = GetDefaultAllocator();
    mSchedBegin = 0; mSchedEnd = 0; mSchedCap = 0; mSchedPad = 0;
    mLineBegin.mnScheduleIndex = 0; mLineBegin.mnCharBase = 0; mLineBegin.mnCharOffset = 0;
    mLineEnd.mnScheduleIndex = 0; mLineEnd.mnCharBase = 0; mLineEnd.mnCharOffset = 0;
    mAnalysisEnd.mnScheduleIndex = 0; mAnalysisEnd.mnCharBase = 0; mAnalysisEnd.mnCharOffset = 0;
    mScheduleEnd.mnScheduleIndex = 0; mScheduleEnd.mnCharBase = 0; mScheduleEnd.mnCharOffset = 0;
    mLineState = 2;
    new (&mLineLayout) LineLayoutBase(0);
    mnLastLineEndIndex = 0;
    mBidiRunInfoArray.Init();
    mbNonGeneralScriptPresent = false;
    mfPenX = 0.0f;
    mfPenXMax = 0.0f;
    if (allocator == 0) allocator = GetAllocator();
    mpCoreAllocator = allocator;
    mSchedAlloc = allocator;
    mLineLayout.SetAllocator(allocator);
}

// @ 0x0089d9a0
void Typesetter::FinalizeLine()
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
        RunInfo* run = mBidiRunInfoArray.mpBegin;
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

// @ 0x0089db20
int Typesetter::LayoutLine(const wchar_t* text, uint32_t len, float x, float y, const TextStyle* style)
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

// @ 0x0089dc00
int Typesetter::LayoutParagraph(const wchar_t* text, uint32_t len, float x, float y, float x1, float y1,
                                const TextStyle* style, LineLayoutBase* out, void* arg9)
{
    float width = x1 - x;
    float height = y1 - y;
    float fontSize = StyleSize(style);
    float total = 0.0f;
    float maxW = 0.0f;
    uint32_t maxLines = 100000;
    if (StyleOverflow(style) == 2) {
        LineLayout tmpLayout(out);
        TextStyle tmpStyle(*style);
        *(int*)(tmpStyle.data + 0x254) = 0;
        LayoutParagraph(text, len, x, y, x1, y1, &tmpStyle, &tmpLayout, 0);
        float ratio;
        if (StyleLineSpace(&tmpStyle) > 0.0f) ratio = StyleLineSpace(&tmpStyle) / StyleSize(&tmpStyle);
        else ratio = 1.0f;
        float a0 = (float)FloorThunk_011e0906(tmpLayout.mfA0);
        float a4 = (float)ceil(tmpLayout.mfA4);
        maxLines = tmpLayout.mLineCount;
        fontSize = (a0 - a4) * ratio;
        float b0 = (float)FloorThunk_011e0906(tmpLayout.mfA0);
        float b4 = (float)ceil(tmpLayout.mfA4);
        total = -(fontSize - (b0 - b4));
        if (StyleWrap(&tmpStyle) != 2 && StyleWrap(&tmpStyle) != 1)
            maxW = tmpLayout.mfWidth;
    }
    Reset(1);
    mfLayoutWidth = width;
    mfLayoutX = x;
    mfLayoutY = 0.0f;
    mLayoutSettings.mTextStyleDefault = *style;
    *mTextStyleArray.mpBegin = &mLayoutSettings.mTextStyleDefault;
    mpCurrentTextStyle = *mTextStyleArray.mpBegin;
    AddTextRun(text, len);
    if (StyleHAlign(style) == 3 && len != 0 && text[len - 1] != 10)
        AddParagraphBreak();
    uint32_t state = mLineState;
    uint32_t lineLimit = maxLines;
    if (StyleOverflow(style) == 2) lineLimit = (uint32_t)(int)(height / fontSize);
    if (lineLimit == 0) lineLimit = 1;
    if (state != 2) {
        for (;;) {
            bool ellipsize;
            if (StyleOverflow(mpCurrentTextStyle) == 2 && (maxLines > lineLimit || maxW > width)) {
                ellipsize = true;
                mbEllipsize = true;
            } else {
                ellipsize = false;
            }
            FinalizeLine();
            mLineLayout.mfA0 = (float)ceil(mLineLayout.mfA0);
            mLineLayout.mfA4 = (float)FloorThunk_011e0906(mLineLayout.mfA4);
            float d = (float)FloorThunk_011e0906(mLineLayout.mfA0) - (float)ceil(mLineLayout.mfA4);
            float scale;
            if (mpCurrentTextStyle && StyleLineSpace(mpCurrentTextStyle) > 0.0f)
                scale = StyleLineSpace(mpCurrentTextStyle) / StyleSize(mpCurrentTextStyle);
            else
                scale = 1.0f;
            total = (float)FloorThunk_011e0906(d * scale) + total;
            mfLayoutWidth = width;
            mfLayoutX = x;
            mfLayoutY = total * mLayoutSettings.mfYScale;
            mLineLayout.FUN_0089cc00(out, arg9);
            ++out->mLineCount;
            NextLine(0);
            if (ellipsize) break;
            if (mLineState == 2) break;
        }
    }
    float outY = y;
    int va = StyleVAlign(style);
    if (va == 1) outY = ((height - total) * 0.5f) * mLayoutSettings.mfYScale + y;
    else if (va == 2) outY = mLayoutSettings.mfYScale * total + y;
    out->OffsetSegment(0.0f, outY, 0, (out->mGlyphLayoutInfoArray.mpEnd - out->mGlyphLayoutInfoArray.mpBegin) >> 5);
    return (int)(out->mGlyphArray.mpEnd - out->mGlyphArray.mpBegin) >> 1;
}

// @ 0x0089e040
int GetSpaceProperties(wchar_t c)
{
    switch ((unsigned short)c) {
    case 9: return 0x15;
    case 10: case 11: case 12: case 13: return 0x14;
    case 0x20: case 0x2000: case 0x2001: case 0x2002: case 0x2003: case 0x2004: case 0x2005: case 0x2006:
    case 0x2008: case 0x2009: case 0x200a: case 0x3000: return 5;
    case 0xa0: case 0x2007: return 9;
    case 0x200b: case 0x200c: return 6;
    case 0x200d: case 0x2060: case 0xfeff: return 10;
    }
    return 0;
}
// @ 0x0089e0e0
bool IsSpace(wchar_t c, int mask, bool all)
{
    int p = GetSpaceProperties(c);
    if (all)
        return (p & mask) == mask;
    return (p & mask) != 0;
}
struct MirrorEntry { unsigned short from, to; };
extern MirrorEntry* gMirrorTable;
extern int gMirrorTableLast;
// @ 0x0089e110
wchar_t GetMirrorChar(wchar_t c)
{
    int lo = 0, hi = gMirrorTableLast;
    if (hi >= 0) {
        do {
            int mid = (hi + lo) / 2;
            if (c == gMirrorTable[mid].from) return gMirrorTable[mid].to;
            if (c < gMirrorTable[mid].from) hi = mid - 1; else lo = mid + 1;
        } while (lo <= hi);
    }
    return c;
}
extern unsigned char gBidiClassTable256[256];
extern unsigned char gBidiClassTableArabic[256];
// @ 0x0089e170
BidiClass GetBidiClass(wchar_t c)
{
    unsigned short ch = c;
    if (ch < 0x100) return (BidiClass)gBidiClassTable256[ch];
    unsigned u = ch;
    if (u - 0x3400 <= 0x6bbb) return (BidiClass)1;
    if (u - 0xac00 <= 0x2ba3) return (BidiClass)1;
    if (u - 0xff10 <= 9) return (BidiClass)4;
    if (u - 0x2000 <= 10 || ch == 0x2028 || ch == 0x3000) return (BidiClass)12;
    if (u - 0x300 <= 0x6f) return (BidiClass)6;
    if (ch == 0x202f || ch == 0x60c) return (BidiClass)7;
    if (u - 0x20a0 <= 0x2f) return (BidiClass)9;
    if (u - 0xe34 <= 6) return (BidiClass)6;
    if (u - 0xe47 <= 7) return (BidiClass)6;
    if (ch == 0xe31) return (BidiClass)6;
    if (u - 0x590 <= 0x6f)
        return (BidiClass)((((ch < 0x5c5) ? -1 : 0) & 4) + 2);
    if (u - 0x600 <= 0xff) return (BidiClass)gBidiClassTableArabic[u];
    if (ch == 0xfeff) return (BidiClass)10;
    if (u - 0x200b <= 2) return (BidiClass)10;
    if (u - 0x2060 <= 3) return (BidiClass)10;
    if (u - 0x2018 <= 5) return (BidiClass)10;
    if (u - 0x202a <= 4) {
        switch (ch) {
        case 0x202a: return (BidiClass)0x11;
        case 0x202b: return (BidiClass)0xf;
        case 0x202c: return (BidiClass)0x12;
        case 0x202d: return (BidiClass)0x10;
        case 0x202e: return (BidiClass)0xe;
        }
    }
    if (u - 0xeb4 <= 5) return (BidiClass)6;
    if (u - 0xebb <= 1) return (BidiClass)6;
    if (u - 0xec8 <= 5) return (BidiClass)6;
    return (BidiClass)((((ch != 0xeb1) - 1) & 5) + 1);
}
}}
