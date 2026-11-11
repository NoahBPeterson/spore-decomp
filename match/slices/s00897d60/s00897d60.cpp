// Slice s00897d60 -- EA::Text::LineLayoutBase trailing-space trim (retail EAText).
//
// Walks the line's Char array from the end, dropping trailing spaces
// (0x20, 0xa0, 0x3000), stores the trimmed length at +0x94, then picks the
// glyph layout entry for that character and writes its (x + advance) as the
// line width, or 0 when the line is empty.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /Isrc/game/include
#include "types.h"

struct GlyphLayoutInfo_00897d60 {
    uint32_t pad0;          // +0x00
    float    mfX;           // +0x04
    uint32_t pad1;          // +0x08
    float    mfAdvance;     // +0x0c
    uint32_t pad2[4];       // +0x10
};

struct WideString_00897d60 {
    const uint16_t* mpBegin;           // +0x00
    const uint16_t* mpEnd;             // +0x04
    const uint16_t* mpCapacity;        // +0x08
};

struct UintVec_00897d60 {
    const uint32_t* mpBegin;           // +0x00
    const uint32_t* mpEnd;             // +0x04
    const uint32_t* mpCapacity;        // +0x08
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct GlyphLayoutVec_00897d60 {
    const GlyphLayoutInfo_00897d60* mpBegin;    // +0x00
    const GlyphLayoutInfo_00897d60* mpEnd;      // +0x04
    const GlyphLayoutInfo_00897d60* mpCapacity; // +0x08
};

struct LineLayoutBase_00897d60 {
    void*    mpCoreAllocator;          // +0x00
    WideString_00897d60 mCharArray;    // +0x04
    char     pad10[0x2c - 0x10];
    uint16_t* mpGlyphBegin;            // +0x2c
    uint16_t* mpGlyphEnd;              // +0x30
    uint16_t* mpGlyphCapacity;         // +0x34
    uint32_t pad38;                    // +0x38
    char     pad3c[0x54 - 0x3c];
    GlyphLayoutVec_00897d60 mGlyphLayoutInfoArray;   // +0x54
    char     pad60[0x68 - 0x60];
    UintVec_00897d60 mGlyphIndexArray;               // +0x68
    char     pad74[0x90 - 0x74];
    uint32_t mnLength;                 // +0x90
    uint32_t mnTrimmedLength;          // +0x94
    float    mfWidth;                  // +0x98
    float    mfWidthAlt;               // +0x9c

    void FUN_00897d60();
};

extern float g_1485378;   // 0x01485378

// @ 0x00897d60
void LineLayoutBase_00897d60::FUN_00897d60()
{
    LineLayoutBase_00897d60* const self = this;
    uint32_t n = self->mnLength;
    if (n > 0) {
        const uint16_t* p = self->mCharArray.mpBegin + n - 1;
        do {
            uint16_t c = *p;
            if (c != 0x20 && c != 0xa0 && c != 0x3000)
                break;
            --n;
            --p;
        } while (n > 0);
    }
    self->mnTrimmedLength = n;
    if (n < self->mGlyphIndexArray.size())
        n = self->mGlyphIndexArray.mpBegin[n];
    else
        n = (uint32_t)(self->mpGlyphEnd - self->mpGlyphBegin);
    float x;
    if (n != 0) {
        const GlyphLayoutInfo_00897d60* info = self->mGlyphLayoutInfoArray.mpBegin + (n - 1);
        float advance = info->mfAdvance;
        x = info->mfX;
        if (advance > g_1485378)
            x = x + advance;
    } else {
        x = 0.0f;
    }
    self->mfWidthAlt = x;
}
