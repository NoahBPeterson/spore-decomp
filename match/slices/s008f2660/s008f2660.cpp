// Slice s008f2660 -- EA::XHTML::Style property setters + CSSParser property builders,
// and the wide-string compare/match helpers they use (SporeApp.exe).
//
//  0x008f2660 Fn8f2660                       -- property-apply helper (fn ptr + edge table, thiscall)
//  0x008f26b0 StyleState::SetFontFamilies    -- fills the 8 font-family wide buffers, marks changed
//  0x008f2740 StyleState::SetFontWeight(float)    0x008f2760 StyleState::SetFontWeight(int)
//  0x008f2780 StyleState::SetFontSize        -- Length -> mFontSize
//  0x008f27a0 StyleState::SetStretch         0x008f27c0 StyleState::SetFontSmoothThresh
//  0x008f27f0 StyleState::SetBackgroundColor 0x008f28c0 StyleState::SetDecorationFlags
//  0x008f2910 StyleState::SetVerticalAlign
//  0x008f29b0 SetMargin  0x008f2a20 SetPadding  0x008f2a90 SetBorderWidth
//  0x008f2b00 SetBorderColor  0x008f2b40 SetBorderStyle  0x008f2bc0 SetBorderSpacing
//  0x008f2c60 SetBoxOffset   0x008f2ce0 MakeColor
//  0x008f2d10 CopyWideLine   0x008f2d70..0x008f2df0 PropertyFunc::Apply thunks
//  0x008f2e10/0x008f2e90      -- case-insensitive wide-string order predicates
//  0x008f2f10 Fn8f2f10        -- emit a text run through a presenter vtable
//  0x008f2f80 CSSParser::TokenValue
//  0x008f2fe0/0x008f3000      -- CharStream next/match char
//  0x008f3020..0x008f3410     -- CreatePropertyFunc<T[,EdgeIndex]> instantiations
//  0x008f31f0/0x008f32d0      -- CSSParser::SetEdgeProperties<Length>/<unsigned int>
//  0x008f3480/0x008f34d0      -- CharStream ascii/wide string match
//
// Retail layouts recovered from the disassembly (2008 PDB names/offsets agree around here):
// StyleState { mpBase +0, mpPage +4, mbFontChanged +8, TextStyle mTextStyle +0xc (0x278),
// mFontSize +0x284, ... mVerticalAlign +0x2d4, mVerticalAlignKW +0x2dc, Edge mEdges[4] +0x2ec,
// mBoxOffset[4] +0x388, mBorderSpacingH +0x41c, mBorderSpacingV +0x424 }.  Edge is 0x20 bytes.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// msvcr90 imports (calls go through the .rdata IAT at 0x13cc2ec / the memcpy thunk at 0x11e0744).
__declspec(dllimport) int __cdecl tolower(int);
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk

namespace EA {
namespace Allocator {

// 0x00928ba0  ?AllocateNewBlock@StackAllocator_s0092_8b00@Allocator@EA@@QAE_NI@Z
class StackAllocator_s0092_8b00 {
public:
    bool AllocateNewBlock(unsigned int size);

    void* Allocate(unsigned int size)
    {
        if ((int)(mEnd - mCur) - (int)size < 0) {
            if (!AllocateNewBlock(size))
                return 0;
        }
        void* p = (void*)mCur;
        mCur = (uint32_t)p + size;
        mPos = (uint32_t)p + size;
        return p;
    }

    uint32_t pad0;    // +0
    uint32_t pad4;    // +4
    uint32_t mEnd;    // +8
    uint32_t mCur;    // +0xc
    uint32_t mPos;    // +0x10
};

}  // namespace Allocator

namespace XHTML {
namespace Style {

// 0x0092cb90  ?AppendWide@@YAIPAXPBGI@Z
extern uint32_t AppendWide(void* dst, const wchar_t* src, uint32_t maxChars);

enum Units { Unit_Number = 0, Unit_Pixels = 1, Unit_Points = 2, Unit_Em = 3, Unit_Percentage = 9, Unit_Auto = 10 };
enum BackgroundRepeat { Background_NoRepeat = 0, Background_RepeatX = 1, Background_RepeatY = 2, Background_RepeatXY = 3 };
enum EdgeIndex { Edge_Top = 0, Edge_Right = 1, Edge_Bottom = 2, Edge_Left = 3, Edge_All = 4 };

// 0x01439ab0: mode*4+i -> edge index table used by SetEdgeProperties.
extern const uint8_t gEdgeMap[];

struct Length {
    float mValue;   // +0
    int   mUnits;   // +4
};

struct Edge {           // size 0x20
    Length       mMargin;       // +0x0
    Length       mPadding;      // +0x8
    Length       mBorder;       // +0x10
    int          mBorderStyle;  // +0x18
    unsigned int mBorderColor;  // +0x1c
};

struct FontStyle {      // size 0x224
    wchar_t mFamilyName[8][32];   // +0x0 .. +0x200   8 names of 32 wchars
    float   mfSize;               // +0x200
    int     mStyle;               // +0x204
    float   mfWeight;             // +0x208
    int     mVariant;             // +0x20c
    int     mPitch;               // +0x210
    int     mSmooth;              // +0x214
    int     mEffect;              // +0x218
    float   mfEffectX;            // +0x21c
    float   mfEffectY;            // +0x220
};

struct TextStyle : FontStyle {    // size 0x278
    unsigned int mColor;            // +0x224
    unsigned int mColorBackground;  // +0x228
    unsigned int mEffectBaseColor;  // +0x22c
    unsigned int mEffectColor;      // +0x230
    unsigned int mHighLightColor;   // +0x234
    unsigned int mnDecorationFlags; // +0x238
    int mDirection;                 // +0x23c
    int mOrientation;               // +0x240
    int mHAlignment;                // +0x244
    int mVAlignment;                // +0x248
    int mJustify;                   // +0x24c
    int mTextWrap;                  // +0x250
    int mTextOverflow;              // +0x254
    int mEmphasisStyle;             // +0x258
    int mEmphasisPosition;          // +0x25c
    int mDigitSubstitution;         // +0x260
    int mPasswordMode;              // +0x264
    float mfStretch;                // +0x268
    float mfLetterSpacing;          // +0x26c
    float mfWordSpacing;            // +0x270
    float mfLineSpace;              // +0x274
};

class StyleState {
public:
    void SetFontFamilies(const wchar_t** names, int count);           // 0x008f26b0
    void SetFontWeight(float weight);                                 // 0x008f2740
    void SetFontWeight(int weight);                                   // 0x008f2760
    void SetFontSize(Length size);                                    // 0x008f2780
    void SetStretch(float stretch);                                   // 0x008f27a0
    void SetFontSmoothThresh(Length thresh);                          // 0x008f27c0
    void SetBackgroundColor(unsigned int color);                      // 0x008f27f0
    void SetDecorationFlags(unsigned short set, unsigned short mask); // 0x008f28c0
    void SetVerticalAlign(Length align);                              // 0x008f2910
    void SetMargin(Length len, int edge);                             // 0x008f29b0
    void SetPadding(Length len, int edge);                            // 0x008f2a20
    void SetBorderWidth(Length len, int edge);                        // 0x008f2a90
    void SetBorderColor(unsigned int color, int edge);                // 0x008f2b00
    void SetBorderStyle(int style, int edge);                         // 0x008f2b40
    void SetBorderSpacing(Length len);                                // 0x008f2bc0
    void SetBoxOffset(Length len, int index);                         // 0x008f2c60

    StyleState* mpBase;         // +0x0
    void*       mpPage;         // +0x4
    bool        mbFontChanged;  // +0x8
    TextStyle   mTextStyle;     // +0xc
    Length      mFontSize;      // +0x284
    unsigned int mFgColor;      // +0x28c
    Length      mLineHeight;    // +0x290
    Length      mFontSmoothThresh;   // +0x298
    wchar_t*    mpBackgroundImage;   // +0x2a0
    int         mBackgroundRepeat;   // +0x2a4
    int         mBackgroundAttachment; // +0x2a8
    Length      mBackgroundPosX;     // +0x2ac
    Length      mBackgroundPosY;     // +0x2b4
    unsigned int mBgColor;           // +0x2bc
    unsigned int mColorInherited;    // +0x2c0
    Length      mWordSpacing;        // +0x2c4
    Length      mLetterSpacing;      // +0x2cc
    Length      mVerticalAlign;      // +0x2d4
    int         mVerticalAlignKW;    // +0x2dc
    int         mTextTransform;      // +0x2e0
    Length      mTextIndent;         // +0x2e4
    Edge        mEdges[4];           // +0x2ec
    Length      mBoxWidth;           // +0x36c
    Length      mBoxHeight;          // +0x374
    int         mFloat;              // +0x37c
    int         mClearFloat;         // +0x380
    int         mPosition;           // +0x384
    Length      mBoxOffset[4];       // +0x388
    int         mDisplay;            // +0x3a8
    int         mWhitespaceMode;     // +0x3ac
    int         mListStyleType;      // +0x3b0
    wchar_t*    mListStyleImage;     // +0x3b4
    int         mListStylePosition;  // +0x3b8
    uint32_t    pad3bc[(0x41c - 0x3bc) / 4];
    Length      mBorderSpacingH;     // +0x41c
    Length      mBorderSpacingV;     // +0x424
};

// 0x004f6510-style helper object used by Fn8f2660 (unnamed 0x3c-byte struct).
struct PropArg {
    uint32_t mPad0;    // +0
    uint32_t mPad4;    // +4
    void*    mpFn;     // +8
    uint32_t mCtx;     // +0xc
    uint32_t mTable;   // +0x10
    uint32_t mMode;    // +0x14
    char     mBuf18[0x20];  // +0x18
    uint32_t mArg38;   // +0x38
    void Fn8f2660(int arg);
};

// Property linked-list node built by CreatePropertyFunc<T>.
struct Property {
    void*     mpVtable;   // +0
    Property* mpNext;     // +4
    void*     mpSetter;   // +8
    void*     mpContext;  // +0xc
    void*     mpArg0;     // +0x10
    void*     mpArg1;     // +0x14
};

// vtable pointer stored into every property object (address is a masked relocation).
extern char gPropVtable[];

// Defined out-of-order below (0x008f3410) but used by SetEdgePropertiesUint (0x008f32d0).
Property* CreatePropertyFunc_uint_EdgeIndex(EA::Allocator::StackAllocator_s0092_8b00* a,
                                            void* setter, void* ctx, void* p4, void* p5,
                                            unsigned int value, int edge);

// 0x008f2d70..0x008f2df0  PropertyFunc::DoSet thunks (this = the property object).
struct PropFunc_Uint  : Property { uint32_t mValue; void Apply(int index); };
struct PropFunc_Float : Property { float    mValue; void Apply(int index); };
struct PropFunc_2UShort : Property { uint16_t mA; uint16_t mB; void Apply(int index); };
struct PropFunc_3Uint : Property { uint32_t mA; uint32_t mB; uint32_t mC; void Apply(int index); };
struct PropFunc_2Uint : Property { uint32_t mA; uint32_t mB; void Apply(int index); };

// CharStream: mpPos +0, mpEnd +4 (see slice s008f3530).
struct CharStream {
    wchar_t* mpPos;   // +0
    wchar_t* mpEnd;   // +4
    wchar_t NextChar();               // 0x008f2fe0
    bool    MatchChar(unsigned int c);     // 0x008f3000
    bool    CopyWideLine(const wchar_t* src, wchar_t* dst, unsigned int maxLen);  // 0x008f2d10
    bool    MatchAscii(const char* s);    // 0x008f3480
    bool    MatchWide(const wchar_t* s);  // 0x008f34d0
};

// CSSParser (see slice s008f3530): mTokenValue begin/end at +0x38/+0x3c, mAllocator +0x4c.
class CSSParser {
public:
    wchar_t* TokenValue();                                // 0x008f2f80
    bool SetEdgePropertiesLength(int* list, Length* values, int mode,
                                 void* p5, void* p6, void* p7, void* p8);   // 0x008f31f0
    bool SetEdgePropertiesUint(int* list, unsigned int* values, int mode,
                               void* p5, void* p6, void* p7, void* p8);     // 0x008f32d0

    uint32_t    pad0[(0x38) / 4];
    wchar_t*    mTokenBegin;   // +0x38
    wchar_t*    mTokenEnd;     // +0x3c
    uint32_t    pad40[(0x4c - 0x40) / 4];
    EA::Allocator::StackAllocator_s0092_8b00* mAllocator;   // +0x4c
};

// Text-run presenter object used by Fn8f2f10.
struct TextRun {
    void*    mpText0;      // +0
    uint32_t pad4[(0x2c - 0x4) / 4];
    int      mField2c;     // +0x2c
    wchar_t* mpTextBegin;  // +0x30
    wchar_t* mpTextEnd;    // +0x34
    uint32_t pad38[(0x48 - 0x38) / 4];
    void*    mpPresenter;  // +0x48
    void Fn8f2f10(void* arg);
};

// 0x008f2e10 / 0x008f2e90  case-insensitive wide-string order predicates.
bool WStrLess_KeyElem(const wchar_t* key, const wchar_t** elem);
bool WStrLess_ElemKey(const wchar_t** elem, const wchar_t* key);

// ---------------------------------------------------------------------------
// 0x008f2660  PropArg::Fn8f2660 -- apply a property fn (thiscall ret 4)
// ---------------------------------------------------------------------------
// @ 0x008f2660
void PropArg::Fn8f2660(int arg)
{
    typedef void (__thiscall* FnT)(void* self, void* a, void* b);
    void* self;
    if (mMode == 0) {
        self = (void*)(mCtx + arg);
    } else {
        int   slot  = *(int*)(mTable + arg);
        int   delta = *(int*)(slot + mMode);
        self = (void*)(mTable + arg + mCtx + delta);
    }
    ((FnT)mpFn)(self, mBuf18, (void*)mArg38);
}

// ---------------------------------------------------------------------------
// 0x008f26b0  StyleState::SetFontFamilies -- fill 8 family-name buffers
// ---------------------------------------------------------------------------
// @ 0x008f26b0
void StyleState::SetFontFamilies(const wchar_t** names, int count)
{
    for (unsigned int i = 0; i < 8; ++i) {
        wchar_t* dst = mTextStyle.mFamilyName[i];
        if (i < (unsigned int)count)
            EA::XHTML::Style::AppendWide(dst, names[i], 0x20);
        else
            dst[0] = 0;
    }
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f2740  StyleState::SetFontWeight(float)
// ---------------------------------------------------------------------------
// @ 0x008f2740
void StyleState::SetFontWeight(float weight)
{
    mTextStyle.mfWeight = weight;
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f2760  StyleState::SetFontWeight(int)
// ---------------------------------------------------------------------------
// @ 0x008f2760
void StyleState::SetFontWeight(int weight)
{
    mTextStyle.mfWeight = (float)weight;
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f2780  StyleState::SetFontSize
// ---------------------------------------------------------------------------
// @ 0x008f2780
void StyleState::SetFontSize(Length size)
{
    mFontSize.mValue = size.mValue;
    mFontSize.mUnits = size.mUnits;
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f27a0  StyleState::SetStretch
// ---------------------------------------------------------------------------
// @ 0x008f27a0
void StyleState::SetStretch(float stretch)
{
    mTextStyle.mfStretch = stretch;
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f27c0  StyleState::SetFontSmoothThresh
// ---------------------------------------------------------------------------
// @ 0x008f27c0
void StyleState::SetFontSmoothThresh(Length thresh)
{
    mFontSmoothThresh.mValue = thresh.mValue;
    mFontSmoothThresh.mUnits = thresh.mUnits;
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f27f0  StyleState::SetBackgroundColor
// ---------------------------------------------------------------------------
// @ 0x008f27f0
void StyleState::SetBackgroundColor(unsigned int color)
{
    mColorInherited = color;
    mBgColor = color;
}

// ---------------------------------------------------------------------------
// 0x008f28c0  StyleState::SetDecorationFlags
// ---------------------------------------------------------------------------
// @ 0x008f28c0
void StyleState::SetDecorationFlags(unsigned short set, unsigned short mask)
{
    mTextStyle.mnDecorationFlags = (unsigned int)set | (mTextStyle.mnDecorationFlags & ~(unsigned int)mask);
    mbFontChanged = 1;
}

// ---------------------------------------------------------------------------
// 0x008f2910  StyleState::SetVerticalAlign
// ---------------------------------------------------------------------------
// @ 0x008f2910
void StyleState::SetVerticalAlign(Length align)
{
    mVerticalAlign.mValue = align.mValue;
    mVerticalAlign.mUnits = align.mUnits;
    mVerticalAlignKW = 8;   // "length" keyword marker
}

// ---------------------------------------------------------------------------
// 0x008f29b0  StyleState::SetMargin
// ---------------------------------------------------------------------------
// @ 0x008f29b0
void StyleState::SetMargin(Length len, int edge)
{
    if (edge == 4) {
        mEdges[0].mMargin.mValue = len.mValue;
        mEdges[1].mMargin.mValue = len.mValue;
        mEdges[0].mMargin.mUnits = len.mUnits;
        mEdges[1].mMargin.mUnits = len.mUnits;
        mEdges[2].mMargin.mValue = len.mValue;
        mEdges[2].mMargin.mUnits = len.mUnits;
        mEdges[3].mMargin.mValue = len.mValue;
        mEdges[3].mMargin.mUnits = len.mUnits;
    } else {
        Length* p = &mEdges[edge].mMargin;
        p->mValue = len.mValue;
        p->mUnits = len.mUnits;
    }
}

// ---------------------------------------------------------------------------
// 0x008f2a20  StyleState::SetPadding
// ---------------------------------------------------------------------------
// @ 0x008f2a20
void StyleState::SetPadding(Length len, int edge)
{
    if (edge == 4) {
        mEdges[0].mPadding.mValue = len.mValue;
        mEdges[1].mPadding.mValue = len.mValue;
        mEdges[0].mPadding.mUnits = len.mUnits;
        mEdges[1].mPadding.mUnits = len.mUnits;
        mEdges[2].mPadding.mValue = len.mValue;
        mEdges[2].mPadding.mUnits = len.mUnits;
        mEdges[3].mPadding.mValue = len.mValue;
        mEdges[3].mPadding.mUnits = len.mUnits;
    } else {
        Length* p = &mEdges[edge].mPadding;
        p->mValue = len.mValue;
        p->mUnits = len.mUnits;
    }
}

// ---------------------------------------------------------------------------
// 0x008f2a90  StyleState::SetBorderWidth
// ---------------------------------------------------------------------------
// @ 0x008f2a90
void StyleState::SetBorderWidth(Length len, int edge)
{
    if (edge == 4) {
        mEdges[0].mBorder.mValue = len.mValue;
        mEdges[1].mBorder.mValue = len.mValue;
        mEdges[0].mBorder.mUnits = len.mUnits;
        mEdges[1].mBorder.mUnits = len.mUnits;
        mEdges[2].mBorder.mValue = len.mValue;
        mEdges[2].mBorder.mUnits = len.mUnits;
        mEdges[3].mBorder.mValue = len.mValue;
        mEdges[3].mBorder.mUnits = len.mUnits;
    } else {
        Length* p = &mEdges[edge].mBorder;
        p->mValue = len.mValue;
        p->mUnits = len.mUnits;
    }
}

// ---------------------------------------------------------------------------
// 0x008f2b00  StyleState::SetBorderColor
// ---------------------------------------------------------------------------
// @ 0x008f2b00
void StyleState::SetBorderColor(unsigned int color, int edge)
{
    if (edge == 4) {
        for (int i = 0; i < 4; ++i)
            mEdges[i].mBorderColor = color;
    } else {
        mEdges[edge].mBorderColor = color;
    }
}

// ---------------------------------------------------------------------------
// 0x008f2b40  StyleState::SetBorderStyle
// ---------------------------------------------------------------------------
// @ 0x008f2b40
void StyleState::SetBorderStyle(int style, int edge)
{
    if (edge == 4) {
        for (int i = 0; i < 4; ++i)
            mEdges[i].mBorderStyle = style;
    } else {
        mEdges[edge].mBorderStyle = style;
    }
}

// ---------------------------------------------------------------------------
// 0x008f2bc0  StyleState::SetBorderSpacing
// ---------------------------------------------------------------------------
// @ 0x008f2bc0
void StyleState::SetBorderSpacing(Length len)
{
    mBorderSpacingH.mValue = len.mValue;
    mBorderSpacingH.mUnits = len.mUnits;
    mBorderSpacingV.mValue = len.mValue;
    mBorderSpacingV.mUnits = len.mUnits;
}

// ---------------------------------------------------------------------------
// 0x008f2c60  StyleState::SetBoxOffset
// ---------------------------------------------------------------------------
// @ 0x008f2c60
void StyleState::SetBoxOffset(Length len, int index)
{
    mBoxOffset[index].mValue = len.mValue;
    mBoxOffset[index].mUnits = len.mUnits;
}

// ---------------------------------------------------------------------------
// 0x008f2ce0  MakeColor -- pack four bytes into an RGBA word
// ---------------------------------------------------------------------------
// @ 0x008f2ce0
uint32_t MakeColor(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4)
{
    uint32_t v = p1;
    v = (v << 8) | p2;
    v = (v << 8) | p3;
    v = (v << 8) | p4;
    return v;
}

// ---------------------------------------------------------------------------
// 0x008f2d10  CopyWideLine -- copy src into dst until CR/LF or the bound
// ---------------------------------------------------------------------------
// @ 0x008f2d10
bool CharStream::CopyWideLine(const wchar_t* src, wchar_t* dst, unsigned int maxLen)
{
    if (src != 0) {
        unsigned int i = 0;
        if (maxLen > 1) {
            unsigned int n = i + 1;
            do {
                wchar_t c = src[i];
                if (c == 0xd || c == 0xa)
                    break;
                dst[i] = c;
                ++n;
                ++i;
            } while (n < maxLen);
        }
        dst[i] = 0;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x008f2d70  PropFunc_Uint::Apply
// ---------------------------------------------------------------------------
// @ 0x008f2d70
void PropFunc_Uint::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned int))mpSetter)((char*)mpContext + index, mValue);
}

// ---------------------------------------------------------------------------
// 0x008f2d90  PropFunc_Float::Apply
// ---------------------------------------------------------------------------
// @ 0x008f2d90
void PropFunc_Float::Apply(int index)
{
    ((void (__thiscall*)(void*, float))mpSetter)((char*)mpContext + index, mValue);
}

// ---------------------------------------------------------------------------
// 0x008f2db0  PropFunc_2UShort::Apply
// ---------------------------------------------------------------------------
// @ 0x008f2db0
void PropFunc_2UShort::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned short, unsigned short))mpSetter)((char*)mpContext + index, mA, mB);
}

// ---------------------------------------------------------------------------
// 0x008f2dd0  PropFunc_3Uint::Apply
// ---------------------------------------------------------------------------
// @ 0x008f2dd0
void PropFunc_3Uint::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned int, unsigned int, unsigned int))mpSetter)((char*)mpContext + index, mA, mB, mC);
}

// ---------------------------------------------------------------------------
// 0x008f2df0  PropFunc_2Uint::Apply
// ---------------------------------------------------------------------------
// @ 0x008f2df0
void PropFunc_2Uint::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned int, unsigned int))mpSetter)((char*)mpContext + index, mA, mB);
}

// ---------------------------------------------------------------------------
// 0x008f2e10  WStrLess_KeyElem -- tolower-order compare, key vs element
// ---------------------------------------------------------------------------
// @ 0x008f2e10
bool WStrLess_KeyElem(const wchar_t* key, const wchar_t** elem)
{
    const wchar_t* e = *elem;
    wchar_t c = *key;
    while (c != 0) {
        wchar_t ck = c;
        if (ck <= 0xff)
            ck = (wchar_t)tolower((unsigned char)ck);
        wchar_t ce = *e;
        if (ce <= 0xff)
            ce = (wchar_t)tolower((unsigned char)ce);
        if (ck != ce)
            break;
        c = *++key;
        ++e;
    }
    return *key < *e;
}

// ---------------------------------------------------------------------------
// 0x008f2e90  WStrLess_ElemKey -- tolower-order compare, element vs key
// ---------------------------------------------------------------------------
// @ 0x008f2e90
bool WStrLess_ElemKey(const wchar_t** elem, const wchar_t* key)
{
    const wchar_t* e = *elem;
    wchar_t c = *e;
    while (c != 0) {
        wchar_t ce = c;
        if (ce <= 0xff)
            ce = (wchar_t)tolower((unsigned char)ce);
        wchar_t ck = *key;
        if (ck <= 0xff)
            ck = (wchar_t)tolower((unsigned char)ck);
        if (ce != ck)
            break;
        c = *++e;
        ++key;
    }
    return *e < *key;
}

// ---------------------------------------------------------------------------
// 0x008f2f10  TextRun::Fn8f2f10 -- hand a text run to the presenter
// ---------------------------------------------------------------------------
// @ 0x008f2f10
void TextRun::Fn8f2f10(void* arg)
{
    if (mpPresenter == 0)
        return;
    wchar_t* text = mpTextBegin;
    wchar_t buf[0x100];
    buf[0] = 0;
    ((CharStream*)((char*)this + 4))->CopyWideLine(text, buf, 0x100);
    void** vt = *(void***)mpPresenter;
    typedef void (__thiscall* PresentFn)(void*, void*, void*, int, int, void*);
    ((PresentFn)vt[1])(mpPresenter, arg, mpText0, mField2c,
                       (unsigned int)((const char*)mpTextEnd - (const char*)text) >> 1,
                       text != 0 ? (void*)buf : 0);
}

// ---------------------------------------------------------------------------
// 0x008f2f80  CSSParser::TokenValue -- copy the token into the stack allocator
// ---------------------------------------------------------------------------
// @ 0x008f2f80
wchar_t* CSSParser::TokenValue()
{
    EA::Allocator::StackAllocator_s0092_8b00* a = mAllocator;
    unsigned int nBytes = (unsigned int)(((char*)mTokenEnd - (char*)mTokenBegin) >> 1) * 2;
    unsigned int size = (nBytes + 9) & 0xfffffff8;
    void* p;
    if ((int)(a->mEnd - a->mCur) - (int)size < 0 && !a->AllocateNewBlock(size)) {
        p = 0;
    } else {
        p = (void*)a->mCur;
        a->mCur = (uint32_t)p + size;
        a->mPos = (uint32_t)p + size;
    }
    memcpy(p, mTokenBegin, nBytes);
    *(wchar_t*)((char*)p + nBytes) = 0;
    return (wchar_t*)p;
}

// ---------------------------------------------------------------------------
// 0x008f2fe0  CharStream::NextChar
// ---------------------------------------------------------------------------
// @ 0x008f2fe0
wchar_t CharStream::NextChar()
{
    wchar_t* p = mpPos;
    if (p < mpEnd) {
        wchar_t c = *p;
        mpPos = p + 1;
        return c;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x008f3000  CharStream::MatchChar
// ---------------------------------------------------------------------------
// @ 0x008f3000
bool CharStream::MatchChar(unsigned int c)
{
    wchar_t* p = mpPos;
    if (p < mpEnd && c == (unsigned int)*p) {
        mpPos = p + 1;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x008f3020  CreatePropertyFunc<float>
// ---------------------------------------------------------------------------
// @ 0x008f3020
Property* CreatePropertyFunc_float(EA::Allocator::StackAllocator_s0092_8b00* a,
                                   void* setter, void* ctx, void* p4, void* p5, float value)
{
    unsigned int size = (sizeof(Property) + sizeof(float) + 7) & ~7u;
    Property* p = (Property*)a->Allocate(size);
    if (p != 0) {
        p->mpNext = 0;
        p->mpVtable = (void*)gPropVtable;
        p->mpSetter = setter;
        p->mpContext = ctx;
        p->mpArg0 = p4;
        p->mpArg1 = p5;
        *(float*)((char*)p + 0x18) = value;
    }
    return p;
}

// ---------------------------------------------------------------------------
// 0x008f3090  CreatePropertyFunc<EA::XHTML::Style::Length>
// ---------------------------------------------------------------------------
// @ 0x008f3090
Property* CreatePropertyFunc_Length(EA::Allocator::StackAllocator_s0092_8b00* a,
                                    void* setter, void* ctx, void* p4, void* p5, Length value)
{
    unsigned int size = (sizeof(Property) + sizeof(Length) + 7) & ~7u;
    Property* p = (Property*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(Length*)((char*)p + 0x18) = value;
    return p;
}

// ---------------------------------------------------------------------------
// 0x008f3100  CreatePropertyFunc<unsigned short, unsigned short>
// ---------------------------------------------------------------------------
// @ 0x008f3100
Property* CreatePropertyFunc_ushort_ushort(EA::Allocator::StackAllocator_s0092_8b00* a,
                                           void* setter, void* ctx, void* p4, void* p5,
                                           unsigned short v, unsigned short u)
{
    unsigned int size = (sizeof(Property) + 2 + 2 + 7) & ~7u;
    Property* p = (Property*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(unsigned short*)((char*)p + 0x18) = v;
    *(unsigned short*)((char*)p + 0x1a) = u;
    return p;
}

// ---------------------------------------------------------------------------
// 0x008f3170  CreatePropertyFunc<EA::XHTML::Style::Length, EdgeIndex>
// ---------------------------------------------------------------------------
// @ 0x008f3170
Property* CreatePropertyFunc_Length_EdgeIndex(EA::Allocator::StackAllocator_s0092_8b00* a,
                                              void* setter, void* ctx, void* p4, void* p5,
                                              Length value, int edge)
{
    unsigned int size = (sizeof(Property) + sizeof(Length) + sizeof(int) + 7) & ~7u;
    Property* p = (Property*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(Length*)((char*)p + 0x18) = value;
    *(int*)((char*)p + 0x20) = edge;
    return p;
}

// ---------------------------------------------------------------------------
// 0x008f31f0  CSSParser::SetEdgeProperties<EA::XHTML::Style::Length>
// ---------------------------------------------------------------------------
// @ 0x008f31f0
bool CSSParser::SetEdgePropertiesLength(int* list, Length* values, int mode,
                                        void* p5, void* p6, void* p7, void* p8)
{
    if (mode == 0)
        return false;
    if (mode == 1) {
        Property* p = CreatePropertyFunc_Length_EdgeIndex(mAllocator, p5, p6, p7, p8, values[0], 4);
        p->mpNext = (Property*)*list;
        *list = (int)p;
        return true;
    }
    for (int i = 0; i < 4; ++i) {
        int edge = gEdgeMap[mode * 4 + i];
        Property* p = CreatePropertyFunc_Length_EdgeIndex(mAllocator, p5, p6, p7, p8, values[edge], i);
        p->mpNext = (Property*)*list;
        *list = (int)p;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f32d0  CSSParser::SetEdgeProperties<unsigned int>
// ---------------------------------------------------------------------------
// @ 0x008f32d0
bool CSSParser::SetEdgePropertiesUint(int* list, unsigned int* values, int mode,
                                      void* p5, void* p6, void* p7, void* p8)
{
    if (mode == 0)
        return false;
    if (mode == 1) {
        Property* p = CreatePropertyFunc_uint_EdgeIndex(mAllocator, p5, p6, p7, p8, values[0], 4);
        p->mpNext = (Property*)*list;
        *list = (int)p;
        return true;
    }
    for (int i = 0; i < 4; ++i) {
        int edge = gEdgeMap[mode * 4 + i];
        Property* p = CreatePropertyFunc_uint_EdgeIndex(mAllocator, p5, p6, p7, p8, values[edge], i);
        p->mpNext = (Property*)*list;
        *list = (int)p;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f33a0  CreatePropertyFunc<unsigned int>
// ---------------------------------------------------------------------------
// @ 0x008f33a0
Property* CreatePropertyFunc_uint(EA::Allocator::StackAllocator_s0092_8b00* a,
                                  void* setter, void* ctx, void* p4, void* p5, unsigned int value)
{
    unsigned int size = (sizeof(Property) + sizeof(unsigned int) + 7) & ~7u;
    Property* p = (Property*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(unsigned int*)((char*)p + 0x18) = value;
    return p;
}

// ---------------------------------------------------------------------------
// 0x008f3410  CreatePropertyFunc<unsigned int, EdgeIndex>
// ---------------------------------------------------------------------------
// @ 0x008f3410
Property* CreatePropertyFunc_uint_EdgeIndex(EA::Allocator::StackAllocator_s0092_8b00* a,
                                            void* setter, void* ctx, void* p4, void* p5,
                                            unsigned int value, int edge)
{
    unsigned int size = (sizeof(Property) + sizeof(unsigned int) + sizeof(int) + 7) & ~7u;
    Property* p = (Property*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(unsigned int*)((char*)p + 0x18) = value;
    *(int*)((char*)p + 0x1c) = edge;
    return p;
}

// ---------------------------------------------------------------------------
// 0x008f3480  CharStream::MatchAscii
// ---------------------------------------------------------------------------
// @ 0x008f3480
bool CharStream::MatchAscii(const char* s)
{
    int i = 0;
    char c = s[0];
    if (c != 0) {
        wchar_t* end = mpEnd;
        wchar_t* p = mpPos;
        do {
            unsigned short ch = (p < end) ? (unsigned short)*p : 0;
            if ((int)(signed char)c != (int)ch)
                return false;
            c = s[i + 1];
            ++i;
            ++p;
        } while (c != 0);
    }
    mpPos += i;
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f34d0  CharStream::MatchWide
// ---------------------------------------------------------------------------
// @ 0x008f34d0
bool CharStream::MatchWide(const wchar_t* s)
{
    int i = 0;
    if (s[0] != 0) {
        wchar_t* end = mpEnd;
        wchar_t* base = mpPos;
        do {
            wchar_t ch = (base + i < end) ? base[i] : 0;
            if (s[i] != ch)
                return false;
            ++i;
        } while (s[i] != 0);
    }
    mpPos += i;
    return true;
}

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
