// Slice s00892540 -- EA::Text::PolygonFont::SetAllocator (retail EAText).
// Calls the Font base setter (0x00fcc140 writes the allocator at +8) and then
// forwards the same allocator into the three glyph maps' allocator slots.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

struct Font_00892540 {
    char  pad_000[8];
    void* mpAllocator;                          // +0x08
    void  SetAllocator(void* pAllocator);       // 0x00fcc140
};

struct PolygonFont_00892540 : Font_00892540 {
    char  pad_00c[0x148 - 0x0c];
    void* mpGlyphMetricsAllocator;              // +0x148
    char  pad_14c[0x16c - 0x14c];
    void* mpCharGlyphAllocator;                 // +0x16c
    char  pad_170[0x18c - 0x170];
    void* mpPolygonGlyphAllocator;              // +0x18c

    void SetAllocator(void* pAllocator);
};

// @ 0x00892540
void PolygonFont_00892540::SetAllocator(void* pAllocator)
{
    Font_00892540::SetAllocator(pAllocator);
    mpGlyphMetricsAllocator = pAllocator;
    mpCharGlyphAllocator    = pAllocator;
    mpPolygonGlyphAllocator = pAllocator;
}
