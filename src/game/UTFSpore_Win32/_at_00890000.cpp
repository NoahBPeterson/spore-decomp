// src/game/UTFSpore_Win32/_at_00890000.cpp -- migrated from slice(s) s0089e350, s00890010 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00890000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/AnalysisInfo.h"
#include "EA/Text/Font.h"
#include "EA/Text/FontServer.h"
#include "EA/Text/LayoutSettings.h"
#include "EA/Text/TextStyle.h"
#include <string.h>

// ---- items of slice s00890010 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
struct FontMetrics {              // 0x44 bytes
    float mfSize;                 // +0x00
    int32_t mPitch;               // +0x04
    float mfHAdvanceXMax;         // +0x08
    float mfVAdvanceYMax;         // +0x0c
    float mfAscent;               // +0x10
    float mfDescent;              // +0x14
    float mfLeading;              // +0x18
    float mfBaseline;             // +0x1c
    uint32_t mPad20[9];           // +0x20
};
}
}
namespace EA {
namespace Text {
struct TextStyle_s0089_0010 {                // 0x278 bytes (only ever constructed elsewhere)
    uint32_t mData[0x8f];         // +0x000 .. FontStyle + colours + decoration flags
    int32_t  mDirection;          // +0x23c
    int32_t  mOrientation;        // +0x240
    int32_t  mHAlignment;         // +0x244
    int32_t  mVAlignment;         // +0x248
    int32_t  mJustify;            // +0x24c
    int32_t  mTextWrap;           // +0x250
    int32_t  mTextOverflow;       // +0x254
    int32_t  mEmphasisStyle;      // +0x258
    int32_t  mEmphasisPosition;   // +0x25c
    int32_t  mDigitSubstitution;  // +0x260
    int32_t  mPasswordMode;       // +0x264
    float    mfStretch;           // +0x268
    float    mfLetterSpacing;     // +0x26c
    float    mfWordSpacing;       // +0x270
    float    mfLineSpace;         // +0x274
};
}
}
namespace EA {
namespace Text {
struct Font_s0089_0010;
}
}
namespace EA {
namespace Text {
struct FontNode {                 // eastl rbtree node, 20 bytes
    FontNode* mpNodeRight;        // +0x00
    FontNode* mpNodeLeft;         // +0x04
    FontNode* mpNodeParent;       // +0x08
    bool      mbColor;            // +0x0c (padded to 4)
    Font_s0089_0010*     mpFont;             // +0x10 (EA::AutoRefCount<Font>)
};
}
}
namespace EA {
namespace Text {
struct FontTreeAnchor {           // 16 bytes
    FontNode* mpNodeRight;        // +0x00
    FontNode* mpNodeLeft;         // +0x04
    FontNode* mpNodeParent;       // +0x08
    bool      mbColor;            // +0x0c (padded to 4)
};
}
}
namespace EA {
namespace Text {
struct FontSelection {
    uint32_t       mCompare;      // +0x00
    FontTreeAnchor mAnchor;       // +0x04
    uint32_t       mnSize;        // +0x14
    void*          mpPoolHead;    // +0x18
    void*          mpPoolNext;    // +0x1c
    void*          mpPoolBegin;   // +0x20
    void*          mpPoolEnd;     // +0x24
    uint32_t       mnNodeSize;    // +0x28
    uint32_t       mBuffer[0x2d]; // +0x2c (9 * 20 bytes)

    FontNode* begin() const { return (FontNode*)mAnchor.mpNodeLeft; }
    FontNode* end() const { return (FontNode*)&mAnchor; }
    void DoNukeSubtree(FontNode* pNode);                     // 0x0088fda0
    void clear()
    {
        DoNukeSubtree((FontNode*)mAnchor.mpNodeParent);
        mAnchor.mpNodeRight = (FontNode*)&mAnchor;
        mAnchor.mpNodeLeft = (FontNode*)&mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mbColor = 0;
        mnSize = 0;
    }
    ~FontSelection() { DoNukeSubtree((FontNode*)mAnchor.mpNodeParent); }
};
}
}
namespace EA {
namespace Text {
struct Font_s0089_0010 {
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
virtual void f7();
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
    virtual bool GetFontMetrics(FontMetrics* pOut);          // +0x30
};
}
}
namespace EA {
namespace Text {
struct LayoutSettings_s0089_0010 {           // 0x37c bytes
    wchar_t mLocale[6];           // +0x000
    int32_t mScript;              // +0x00c
    int32_t mDirection;           // +0x010
    FontSelection mFontSelection; // +0x014
    bool mbDynamicFontSelection;  // +0x0f4
    TextStyle_s0089_0010 mTextStyleDefault;  // +0x0f8
    bool mbEnableAutoHyphenation; // +0x370
    bool mbCellTopPosition;       // +0x371
    float mfYScale;               // +0x374
    bool mbEnableLigatures;       // +0x378
    bool mbHideControlCharacters; // +0x379
    bool mbDisplayZWG;            // +0x37a

    LayoutSettings_s0089_0010();                                        // 0x0089b010
};
}
}
namespace EA {
namespace Text {
struct TextState {                        // one 32-bit word, 7 live bits
    int mnLevel                 : 4;      // +0x00
    int mbForcedDirection       : 1;
    int mbSwapInhibited         : 1;
    int mbDisableNationalDigits : 1;
};
}
}
namespace EA {
namespace Text {
struct Analysis {                         // 16 bytes
    uint32_t  mnPosition;                 // +0x00
    uint32_t  mnLength;                   // +0x04
    TextState mTextState;                 // +0x08
    uint32_t  mScript        : 7;         // +0x0c
    uint32_t  mnParity       : 1;
    uint32_t  mnParentParity : 1;
    uint32_t  mbJoinBefore   : 1;
    uint32_t  mbJoinAfter    : 1;
};
}
}
namespace EA {
namespace Text {
struct AnalysisArray {                    // eastl::vector<Analysis>, 24 bytes
    Analysis*   mpBegin;                  // +0x00
    Analysis*   mpEnd;                    // +0x04
    Analysis*   mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    Analysis&    back() { return mpEnd[-1]; }
    void         resize(unsigned int nNewSize);   // 0x00890490
};
}
}
namespace EA {
namespace Text {
struct AnalysisInfo_s0089_0010 {                     // 8 bytes
    const TextStyle_s0089_0010* mpTextStyle;         // +0x00
    Font_s0089_0010*            mpFont;              // +0x04
};
}
}
namespace EA {
namespace Text {
struct Cluster {                          // 16 bytes
    uint32_t mnCharBegin;                 // +0x00
    uint32_t mnCharCount;                 // +0x04
    uint32_t mnX;                         // +0x08
    uint32_t mnY;                         // +0x0c
};
}
}
namespace EA {
namespace Text {
struct ClusterArray {                     // eastl::vector<Cluster>, 24 bytes
    Cluster*    mpBegin;                  // +0x00
    Cluster*    mpEnd;                    // +0x04
    Cluster*    mpCapacity;               // +0x08
    const char* mpName;                   // +0x0c
    int32_t     mFlags;                   // +0x10
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
};
}
}
namespace EA {
namespace Text {
struct TextRun {                          // 8 bytes
    wchar_t*     mpText;                  // +0x00
    unsigned int mnTextSize;              // +0x04
};
}
}
namespace EA {
namespace Text {
struct GlyphAttributes {                  // 40 bytes in this build
    Font_s0089_0010*    mpFont;                      // +0x00
    float    mfPenX;                      // +0x04
    float    mfPenY;                      // +0x08
    float    mfX1;                        // +0x0c
    float    mfY1;                        // +0x10
    float    mfX2;                        // +0x14
    float    mfY2;                        // +0x18
    float    mfAdvance;                   // +0x1c
    uint16_t mGLA;                        // +0x20
    uint16_t mPad22;                      // +0x22
    uint32_t mGlyphId;                    // +0x24
};
}
}
namespace EA {
namespace Text {
struct GlyphAdvanceSlot {                 // 40 bytes
    float    mfValue;                     // +0x00
    uint32_t mPad[9];                     // +0x04
};
}
}
namespace EA {
namespace Text {
struct LayoutMetrics {                    // 28 bytes
    uint32_t mnSize;                      // +0x00
    float    mfSpace;                     // +0x04
    uint32_t mnVisibleSize;               // +0x08
    float    mfVisibleSpace;              // +0x0c
    float    mfBaseline;                  // +0x10
    float    mfDescent;                   // +0x14
    uint32_t mnLineCount;                 // +0x18
};
}
}
namespace EA {
namespace Text {
struct Layout;                            // 0x37c bytes
}
}
namespace EA {
namespace Text {
struct Layout {
    LayoutSettings_s0089_0010 mLayoutSettings;
    Layout();
    float GetMaxBaseline(const TextStyle_s0089_0010* pStyle);           // 0x00890d20
    float GetMinDescent(const TextStyle_s0089_0010* pStyle);            // 0x00890e20
    int   AnalyzeText(const AnalysisInfo_s0089_0010* pInfo, int nCount,
                      AnalysisArray* pOut, int unused);      // 0x00890500
    int   LayoutTextLine(int a1, int a2, float fX, float fY,
                         const TextStyle_s0089_0010* pStyle, GlyphAttributes* pGlyphs,
                         unsigned int nMaxGlyphs, LayoutMetrics* pMetrics);  // 0x00890570
    unsigned int LayoutText(const TextRun* pRuns, int nRuns, unsigned int nStart,
                            unsigned int nEnd, const int32_t* pGlyphIndex,
                            ClusterArray* pClusters, GlyphAdvanceSlot* pAdvances,
                            int32_t* pGlyphClusters, float fLineWidth,
                            unsigned int* pLineEnds, unsigned int nMaxLines,
                            float* pLineWidths);                 // 0x00890010
    int   LayoutTextParagraph(int a2, int a3, float fX1, float fY1, float fX2,
                              float fY2, const TextStyle_s0089_0010* pStyle, int a9,
                              unsigned int nMaxGlyphs, LayoutMetrics* pOut);  // 0x00890830
    float GetTextLayoutMetrics(int a1, int a2, const TextStyle_s0089_0010* pStyle,
                               LayoutMetrics* pOut);             // 0x00890cc0
};
}
}
namespace EA {
namespace Text {
struct IFontCompareTarget {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual bool HasFont(int32_t a, int32_t b);              // +0x28
    virtual void v11();
    virtual int32_t FindFont(int32_t a, int32_t b);          // +0x30
};
}
}
// ---- items of slice s00890010 end

// ---- items of slice s0089e350 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
typedef wchar_t Char;
}
}
namespace EA {
namespace Text {
enum CharCategory { };
}
}
namespace EA {
namespace Text {
struct CharCategoryInfo
{
    uint16_t mCode;         // starting code of the range
    uint8_t  mCharClass0;   // character class for 0 bits
    uint8_t  mCharClass1;   // character class for 1 bits
    uint8_t* mpBitMask;     // bitmask (can be NULL)
};
}
}
namespace EA {
namespace Text {
struct CharCategoryLess
{
    bool operator()(const CharCategoryInfo& a, const CharCategoryInfo& b) const
        { return a.mCode < b.mCode; }
};
}
}
namespace EA {
namespace Text {
extern CharCategoryInfo gCharCategoryTable[779];   // 0x0154a1a0 .. 0x0154b9f8
}
}
namespace EA {
namespace Text {
template <typename RandomAccessIterator, typename T, typename Compare>
RandomAccessIterator upper_bound(RandomAccessIterator first, RandomAccessIterator last,
                                 const T& value, Compare compare);   // 0x0089e5a0
}
}
// ---- items of slice s0089e350 end

// @ 0x00890f50
EA::Text::Layout::Layout()
{
}

// @ 0x00890f60
int __cdecl CompareFontCallback(EA::Text::IFontCompareTarget* pTarget, int32_t a2, int32_t a3, int32_t a4)
{
    if (pTarget->HasFont(a3, 0))
    {
        if (pTarget->FindFont(a2, a4) == a4)
            return 0;
    }
    return -1;
}

// @ 0x0089e5e0
namespace EA { namespace Text {
CharCategory GetCharCategory(Char nChar)
{
    const size_t           kCCTableSize = sizeof(gCharCategoryTable) / sizeof(gCharCategoryTable[0]);
    const CharCategoryInfo cciTemp      = { nChar, 0, 0, 0 };

    const CharCategoryInfo* const pCC = (EA::Text::upper_bound(gCharCategoryTable, gCharCategoryTable + kCCTableSize, cciTemp, CharCategoryLess()) - 1);

    if(pCC->mpBitMask == 0)
        return (CharCategory)pCC->mCharClass0;

    const int nBitIndex = nChar - pCC->mCode;
    return (CharCategory)((pCC->mpBitMask[nBitIndex >> 3] & (1 << (nBitIndex & 7))) ? pCC->mCharClass1 : pCC->mCharClass0);
}
}}  // namespace EA::Text
