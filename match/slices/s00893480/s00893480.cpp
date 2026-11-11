// Slice s00893480 -- EA::Text GlyphVec::resize (eastl vector of uint16 glyphs).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned);   // 0x011e0744 (static CRT memmove)

struct GlyphVec {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    void* mpAllocator;
    uint32_t pad;

    void insert(uint16_t* pos, unsigned n, const uint16_t& v);   // 0x008931d0 (fill-insert)
    void resize(unsigned n);
};

// @ 0x00893480
void GlyphVec::resize(unsigned n)
{
    unsigned sz = (unsigned)(mpEnd - mpBegin);
    if (n > sz) {
        uint16_t v = 0;
        insert(mpEnd, n - sz, v);
    } else {
        uint16_t* f = mpBegin + n;
        uint16_t* l = mpEnd;
        memcpy(f, l, (char*)mpEnd - (char*)l);
        mpEnd -= (l - f);
    }
}
