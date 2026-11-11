// Slice s00892bc0 -- EA::Text::PolygonFont::GetGlyphMetrics (retail EAText).
//
// Looks the glyph id up in the glyph-metrics hash map at this+0x12c and, when
// present, copies the 5-float GlyphMetrics value into the caller's output.
// The map's find is the out-of-line retail helper at 0x00886430.
// Flags: /O2 /MD /GS- /GR- /TP /arch:SSE
#include "types.h"

struct GlyphMetrics_00892bc0 {
    float mfSizeX;          // +0x00
    float mfSizeY;          // +0x04
    float mfHBearingX;      // +0x08
    float mfHBearingY;      // +0x0c
    float mfHAdvanceX;      // +0x10
};

struct GlyphNode_00892bc0 {
    unsigned short         mGlyphId;    // +0x00
    GlyphMetrics_00892bc0  mValue;      // +0x04
    GlyphNode_00892bc0*    mpNext;      // +0x18
};

struct GlyphIterator_00892bc0 {
    GlyphNode_00892bc0*  mpNode;        // +0x00
    GlyphNode_00892bc0** mpBucket;      // +0x04
};

struct GlyphMap_00892bc0 {
    unsigned              mFunctors;    // +0x00
    GlyphNode_00892bc0**  mpBuckets;    // +0x04
    unsigned              mnBucketCount;// +0x08

    // 0x00886430: find(iterator out, const GlyphId* key)
    GlyphIterator_00892bc0* Find(GlyphIterator_00892bc0* out, const unsigned short* key);
};

struct PolygonFont_00892bc0 {
    char           pad_000[0x12c];
    GlyphMap_00892bc0 mGlyphMetricsMap; // +0x12c

    bool GetGlyphMetrics(unsigned short glyphId, GlyphMetrics_00892bc0* pGlyphMetrics);
};

// @ 0x00892bc0
bool PolygonFont_00892bc0::GetGlyphMetrics(unsigned short glyphId, GlyphMetrics_00892bc0* pGlyphMetrics)
{
    GlyphMap_00892bc0* map = &mGlyphMetricsMap;
    GlyphIterator_00892bc0 it;
    GlyphIterator_00892bc0* pit = map->Find(&it, &glyphId);
    if (pit->mpNode != map->mpBuckets[map->mnBucketCount]) {
        *pGlyphMetrics = pit->mpNode->mValue;
        return true;
    }
    return false;
}