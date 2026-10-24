// Slice s00b06e10 -- glyph-run array copy (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cGlyphVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
    void operator=(const cGlyphVector& other);               // 0x00ac44a0
};

struct cGlyphRun {
    uint32_t     mKey;                                       // +0x00
    uint8_t      mFlag;                                      // +0x04
    uint8_t      mPad05[3];                                  // +0x05 .. +0x07
    cGlyphVector mGlyphs;                                    // +0x08
    uint32_t     mPad14[2];                                  // +0x14 .. +0x1b
    uint32_t     mValue1c;                                   // +0x1c
    uint32_t     mValue20;                                   // +0x20
};

// @ 0x00b072d0
void __cdecl CopyGlyphRuns(cGlyphRun* dst, cGlyphRun* end, const cGlyphRun* src)
{
    if (dst != end) {
        do {
            dst->mFlag = src->mFlag;
            dst->mGlyphs = src->mGlyphs;
            dst->mValue1c = src->mValue1c;
            dst->mValue20 = src->mValue20;
            ++dst;
        } while (dst != end);
    }
}

struct cBigElement {
    void*    mpVtable;                                       // +0x00
    uint8_t  mPad04[0x7c];                                   // +0x04 .. +0x7f
};

struct cBigVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void Erase(void* first, void* last);
};

void* __cdecl destroy_range_big(void* src, void* end, void* dst); // 0x00b03f10

// @ 0x00b07140
void cBigVector::Erase(void* first, void* last)
{
    cBigElement* p = (cBigElement*)destroy_range_big(last, mpEnd, first);
    cBigElement* end = (cBigElement*)mpEnd;
    while (p < end) {
        ((void (__thiscall*)(cBigElement*, int))((void**)p->mpVtable)[2])(p, 0);
        p = (cBigElement*)((char*)p + 0x80);
    }
    mpEnd = (void*)((char*)mpEnd + (((char*)last - (char*)first) >> 7) * -0x80);
}
