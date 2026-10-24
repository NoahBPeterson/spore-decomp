// Slice s008a2a00: EA::Text::Typesetter::PlaceGeneralGlyphCluster (retail EAText shape).
// Layouts and signatures: EA/Text reference headers (LineLayout +0x418, mfPenX +0x528).
#include "types.h"

namespace EA { namespace Text {

typedef unsigned short GlyphId;

struct TextStyle {
    unsigned char mPad00[0x26c];
    float mfLetterSpacing;                  // +0x26c
};

struct Font;

struct GlyphMetrics {
    float mfSizeX;                          // +0x00
    float mfSizeY;                          // +0x04
    float mfHBearingX;                      // +0x08
    float mfHBearingY;                      // +0x0c
    float mfHAdvanceX;                      // +0x10
};

struct Kerning {
    float mfX;                              // +0x00
    float mfY;                              // +0x04
};

// First dword packs GJC:4, mbGlyphIsObject:1 (0x10), mClusterPosition:3 (0xe0),
// mClusterSize:3, mClusterBreakable:1, mCharCount:2, mDirection:1 (bit 14).
struct GlyphInfo {
    uint32_t mBits;                         // +0x00
    uint8_t  mScriptFlags;                  // +0x04
    uint8_t  mOpenTypeLookupFlags;          // +0x05
    uint16_t mPad06;                        // +0x06
};

struct GlyphLayoutInfo {
    Font* mpFont;                           // +0x00
    float mfPenX;                           // +0x04
    float mfPenY;                           // +0x08
    float mfAdvance;                        // +0x0c
    float mfX1;                             // +0x10
    float mfY1;                             // +0x14
    float mfX2;                             // +0x18
    float mfY2;                             // +0x1c
};

struct AnalysisInfo {
    TextStyle* mpTextStyle;                 // +0x00
    Font* mpFont;                           // +0x04
    uint32_t mBits;                         // +0x08
};

class Font {
public:
    virtual void v00();                     // slot 0
    virtual void v01();                     // slot 1
    virtual void v02();                     // slot 2
    virtual void v03();                     // slot 3
    virtual void v04();                     // slot 4
    virtual void v05();                     // slot 5
    virtual void v06();                     // slot 6
    virtual void v07();                     // slot 7
    virtual void v08();                     // slot 8
    virtual void v09();                     // slot 9
    virtual void v10();                     // slot 10
    virtual void v11();                     // slot 11
    virtual void v12();                     // slot 12
    virtual bool GetGlyphMetrics(GlyphId glyph, GlyphMetrics& metrics);   // +0x34, slot 13
    virtual void v14();                     // slot 14
    virtual void v15();                     // slot 15
    virtual bool GetKerning(GlyphId prev, GlyphId cur, Kerning& kerning, int direction, bool flag); // +0x40, slot 16
};

// eastl::vector with EASTLCoreAllocator (0x14 bytes).
template <class T> struct cvec {
    T* mpBegin;                             // +0x00
    T* mpEnd;                               // +0x04
    T* mpCapacity;                          // +0x08
    void* mpAllocator;                      // +0x0c
    int mFlags;                             // +0x10
};

class LineLayout {
public:
    void GetGlyphRangeFromCharRange(unsigned a, unsigned b, unsigned& g0, unsigned& g1) const;   // 0x00897ae0

    unsigned char mPad00[0x18];
    cvec<AnalysisInfo> mAnalysisInfoArray;          // +0x18 (Typesetter +0x430)
    cvec<GlyphId> mGlyphArray;                      // +0x2c (Typesetter +0x444)
    cvec<GlyphInfo> mGlyphInfoArray;                // +0x40 (Typesetter +0x458)
    cvec<GlyphLayoutInfo> mGlyphLayoutInfoArray;    // +0x54 (Typesetter +0x46c)
};

class Typesetter {
public:
    void PlaceGeneralGlyphCluster(unsigned charIndex, unsigned charCount);
    void SetGlyphLayoutInfo(GlyphLayoutInfo& info, float x, const GlyphMetrics& metrics);   // 0x00897830
    void GetObjectMetrics(unsigned index, GlyphMetrics& metrics);                          // 0x00898300

    unsigned char mPad00[0x418];
    LineLayout mLineLayout;                 // +0x418
    unsigned char mPad01[0x528 - 0x418 - sizeof(LineLayout)];
    float mfPenX;                           // +0x528
    float mfPenXMax;                        // +0x52c
};

// @ 0x008a2d60
void Typesetter::PlaceGeneralGlyphCluster(unsigned charIndex, unsigned charCount)
{
    TextStyle* pStyle = mLineLayout.mAnalysisInfoArray.mpBegin[charIndex].mpTextStyle;
    float fLetterSpacing = pStyle ? pStyle->mfLetterSpacing : 0.0f;

    unsigned glyphEnd;
    mLineLayout.GetGlyphRangeFromCharRange(charIndex, charIndex + charCount, charCount, glyphEnd);

    unsigned prevGlyph = 0;
    for (unsigned glyphIndex = charCount; glyphIndex < glyphEnd; ++glyphIndex) {
        GlyphId glyphId = mLineLayout.mGlyphArray.mpBegin[glyphIndex];
        GlyphInfo& glyphInfo = mLineLayout.mGlyphInfoArray.mpBegin[glyphIndex];
        GlyphLayoutInfo& layoutInfo = mLineLayout.mGlyphLayoutInfoArray.mpBegin[glyphIndex];

        if (glyphIndex != charCount && (glyphInfo.mBits & 0x10) == 0) {
            Kerning kerning;
            if (layoutInfo.mpFont->GetKerning(prevGlyph, glyphId, kerning,
                                              (int)((glyphInfo.mBits >> 14) & 1), true))
                mfPenX = mfPenX + kerning.mfX;
        }

        GlyphMetrics metrics;
        if ((glyphInfo.mBits & 0x10) == 0)
            layoutInfo.mpFont->GetGlyphMetrics(glyphId, metrics);
        else
            GetObjectMetrics(glyphIndex, metrics);

        SetGlyphLayoutInfo(layoutInfo, mfPenX, metrics);

        if ((glyphInfo.mBits & 0xe0) == 0)
            metrics.mfHAdvanceX = metrics.mfHAdvanceX + fLetterSpacing;
        mfPenX = mfPenX + metrics.mfHAdvanceX;
        if (mfPenX > mfPenXMax)
            mfPenXMax = mfPenX;
        mfPenX = mfPenXMax;
        prevGlyph = glyphId;
    }
}

}}  // namespace EA::Text
