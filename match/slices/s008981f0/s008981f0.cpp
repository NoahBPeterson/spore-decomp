// Slice s008981f0 -- EA::Text::Typesetter::SetDefaultTextStyle(const TextStyle*):
// copy the style into the layout settings, point the style array at it and make it current.
// Local stand-in layout (retail offsets).
#include "types.h"

struct TextStyle981f0 {
    unsigned char mBytes[0x278];
    TextStyle981f0& operator=(const TextStyle981f0&);
};

struct LayoutSettings981f0 {
    unsigned char  pad000[0x0f8];
    TextStyle981f0 mTextStyleDefault;       // +0x0f8
    unsigned char  pad370[0x00c];           // sizeof(LayoutSettings) == 0x37c
};

struct TextStyleVec981f0 {
    TextStyle981f0** mpBegin;               // +0x00 (the inline pool follows)
    unsigned char    pad04[0x34];
};

struct Typesetter981f0 {
    unsigned char      pad000[0x004];
    LayoutSettings981f0 mLayoutSettings;    // +0x004
    void*              mpFontServer;        // +0x380
    TextStyleVec981f0  mTextStyleArray;     // +0x384
    TextStyle981f0*    mpCurrentTextStyle;  // +0x3bc

    void SetDefaultTextStyle(const TextStyle981f0* style);
};

// @ 0x008981f0
void Typesetter981f0::SetDefaultTextStyle(const TextStyle981f0* style)
{
    if (style) {
        mLayoutSettings.mTextStyleDefault = *style;
        *mTextStyleArray.mpBegin = &mLayoutSettings.mTextStyleDefault;
        mpCurrentTextStyle = *mTextStyleArray.mpBegin;
    }
}
