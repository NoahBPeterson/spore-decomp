// Slice s00897790: EA::Text::Typesetter::GetGlyphsForChar (UTFSpore manager2.obj family,
// /O2 /MD /Gy /TP /arch=SSE /fp=fast, no /EHsc).

#include "types.h"

typedef wchar_t Char;
typedef unsigned short GlyphId;

struct Font {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    // slot 14 (offset 0x38)
    virtual unsigned int GetGlyphIds(Char const* pCharArray, unsigned int nCharArrayCount,
                                     GlyphId* pGlyphIdArray, bool bUseReplacementGlyph,
                                     const unsigned int nGlyphIdStride);
};

struct AnalysisInfo {
    void* mpTextStyle;      // +0x00
    Font* mpFont;           // +0x04
};

struct Typesetter {
    unsigned int GetGlyphsForChar(Char const* pChar, unsigned int count,
                                  AnalysisInfo const* pAnalysisInfo, GlyphId* pGlyphIdArray,
                                  unsigned int& glyphIdCount, Char const* pFallbackOptions,
                                  unsigned int fallbackOptionCount);
};

// @ 0x00897790
unsigned int Typesetter::GetGlyphsForChar(Char const* pChar, unsigned int /*count*/,
                                          AnalysisInfo const* pAnalysisInfo, GlyphId* pGlyphIdArray,
                                          unsigned int& glyphIdCount, Char const* pFallbackOptions,
                                          unsigned int fallbackOptionCount)
{
    Char const* p = pChar;
    Char const c = *p;
    if (c != (Char)0xfffc) {
        unsigned int i = 0;
        if (pAnalysisInfo->mpFont->GetGlyphIds(p, 1, pGlyphIdArray,
                                               fallbackOptionCount == 0,
                                               sizeof(GlyphId)) == 0) {
            p = pFallbackOptions;
            while (i < fallbackOptionCount) {
                ++i;
                if (pAnalysisInfo->mpFont->GetGlyphIds(p, 1, pGlyphIdArray,
                                                       i < fallbackOptionCount,
                                                       sizeof(GlyphId)) != 0)
                    break;
                p += 1;
            }
        }
    } else {
        *pGlyphIdArray = 0xffff;
    }
    ++glyphIdCount;
    return 1;
}