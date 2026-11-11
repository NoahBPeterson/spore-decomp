// EA::Text::OutlineFont::IsCharSupported -- flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast
#include "game/types.h"

struct FontBase {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual bool IsCharSupported(wchar_t c, unsigned script);   // slot 15 (+0x3c)
};

namespace EA {
namespace Text {

struct OutlineFont : FontBase {
    uint8_t mData[0x164];                                  // +0x000
    bool IsCharSupported(wchar_t c, unsigned script);      // 0x00891430
};

}
}

extern "C" int FF_GlyphExists(char* p, int ch, unsigned flags, int* out);   // 0x008c20d0

typedef unsigned int u32;

struct Bitset64 {
    u32 mWords[2];
    bool test(u32 i) const { return i < 64 ? (mWords[i >> 5] & (1u << (i & 0x1f))) != 0 : false; }
};

// @ 0x00891430
bool EA::Text::OutlineFont::IsCharSupported(wchar_t c, unsigned script)
{
    if (c < 0x0080)
        return true;
    if (script < 0x1f) {
        if (script != 0x1e && script != 0 && script != 0x15)
            goto bits;
    } else {
        if (script != (unsigned)-1)
            goto bits;
        if (c == 0xffff)
            return true;
    }
    return FF_GlyphExists(*(char**)(mData + 0x15c), (unsigned short)c, 0,
                          (int*)(mData + 0x160)) != 0;
bits:
    return ((const Bitset64*)(mData + 0x18))->test(script);
}
