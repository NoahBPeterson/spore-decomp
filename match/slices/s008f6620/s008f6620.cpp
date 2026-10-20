// match/slices/s008f6620/s008f6620.cpp
// Object file: UTFSpore_Win32/CSSParser.obj (EA::XHTML::Style::CSSParser property parsers)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /Isrc/game/include /vmg /vmv

#include "game/types.h"
#include <wchar.h>
#include <new>

// ---- token codes (EA::XHTML::Style::CSSToken) --------------------------------
enum CSSToken {
    TokenWS     = 2,
    TokenIdent  = 3,
    TokenSlash  = 0x17
};

// ---- units (EA::XHTML::Style::Units) ----------------------------------------
enum Units {
    Unit_Percentage = 9,
    Unit_Auto       = 10,
    Unit_Inherit    = 11,
    Unit_Unset      = 13
};

// ---- symbol tables in .rdata (address of the table, not of an entry) --------
extern "C" const char gTableBgRepeat[];      // 0x0154da78  ("normal")
extern "C" const char gTableFontStyle[];     // 0x0154d7d8  ("italic"/"oblique")
extern "C" const char gTableFontWeight[];    // 0x0154d7f0  ("bold")
extern "C" const char gTableFontSize[];      // 0x0154d810  float keywords
extern "C" const char gTableVAlign[];        // 0x0154d900  ("baseline")
extern "C" const char gTableTextDecor[];     // 0x0154d8e0  ("blink".."baseline")

namespace EA {
namespace XHTML {
namespace Style {

struct Length;

// EA::XHTML::Style::StyleState.  StyleState is a virtual base of its own class
// hierarchy, so a pointer-to-member function on it is the full 16-byte
// {pfn, adjustor, vtordisp, vbtable} form -- which is what every
// CreatePropertyFunc<T> call site builds.  Those sites compile with /vmg
// (see the manifest); /vmg alone gives the 12-byte form, so a base that makes
// the floor the virtual-inheritance form is needed here.  That base is declared
// as a POD with a const member because /vmg + a class-type base with virtual
// members forces the "most general" (virtual) representation, whose pointer to
// member is 16 bytes and whose constants/words cl emits exactly as retail does.
#pragma pack(push, 1)
class StyleStateBase {
public:
    const int mDummy;   // non-polymorphic; never constructed, never touched
};
#pragma pack(pop)

class StyleState : public virtual StyleStateBase {
public:
    void FUN_008f2700(unsigned v);              // 0x008f2700
    void SetFontVariant(unsigned v);            // 0x008f2720
    void SetFontSizeFloat(float v);             // 0x008f2740
    void SetFontWeight(unsigned v);             // 0x008f2760
    void SetFontSize(Length v);                 // 0x008f2780
    void SetStretch(float v);                   // 0x008f27a0
    void SetColor(unsigned v);                  // 0x008f27e0
    void SetBackgroundColor(unsigned v);        // 0x008f27f0
    void SetBackgroundPositionX(Length v);      // 0x008f2840
    void SetBackgroundPositionY(Length v);      // 0x008f2860
    void SetWordSpacing(Length v);              // 0x008f2880
    void SetLetterSpacing(Length v);            // 0x008f28a0
    void SetDecorationFlags(unsigned short a, unsigned short b);  // 0x008f28c0
    void SetVerticalAlign(Length v);            // 0x008f2910
    void FUN_008f2940(unsigned v);              // 0x008f2940
    void SetTextIndent(Length v);               // 0x008f2970
    void SetLineHeight(Length v);               // 0x008f2990
    void SetMargin(Length v, int edge);         // 0x008f29b0
    void SetPadding(Length v, int edge);        // 0x008f2a20
    void SetFontSize2(unsigned v);              // 0x008fb8a0
};

// EA::XHTML::Style::Length -- 8 bytes
struct Length {
    Length() {}
    Length(float value, int units) : mValue(value), mUnits(units) {}
    float mValue;   // +0x0
    int   mUnits;   // +0x4
};

// EA::XHTML::Style::Property -- has a vtable; +0x4 is the list link
class Property {
public:
    virtual void Apply(StyleState* pState);   // slot 0
    Property* mpNext;                          // +0x4 (set by PropertyList::Add)
};

// EA::XHTML::Style::PropertyList -- 4 bytes
class PropertyList {
public:
    void Add(Property* p) {
        p->mpNext = mpFirst;
        mpFirst = p;
    }
    Property* mpFirst;   // +0x0
};

// EA::Allocator::StackAllocator (size 0x24)
class StackAllocator {
public:
    StackAllocator() {}
    bool AllocateNewBlock(unsigned int nSize);   // 0x00928ba0
    void* Allocate(unsigned int nSize) {
        if ((int)(mpCurrentBlockEnd - mpCurrentObjectBegin - (int)nSize) < 0) {
            if (!AllocateNewBlock(nSize))
                return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + nSize;
        mpCurrentObjectEnd = p + nSize;
        return p;
    }
    unsigned int mnDefaultBlockSize;   // +0x00
    void* mpCurrentBlock;              // +0x04
    char* mpCurrentBlockEnd;           // +0x08
    char* mpCurrentObjectBegin;        // +0x0c
    char* mpCurrentObjectEnd;          // +0x10
    char mPad[0x14];                   // +0x14..0x23 (size 0x24)
};

// EA::XHTML::Style::PropertyFunc<T> -- allocated size 0x20
// NOTE: created while StyleState is incomplete, so the member pointer is the
// 16-byte (unknown-inheritance) form: {pfn, adjustor} = {imm32, 0, 0, 0}.
template <class T>
class PropertyFunc : public Property {
public:
    PropertyFunc() {}
    void (StyleState::*mpSetter)(T);   // +0x8, 16 bytes
    T mValue;                          // +0x18
    int mPad;                          // +0x1c (placement allocation: 0x20)
};

// ---- CreatePropertyFunc<T> -- out-of-line instantiations in this object file.
// The setter is the 16-byte {pfn, adjustor, vtordisp, vbtable} member-pointer
// image; it is passed as a small value type so every call site materialises it
// as one 16-byte stack block, exactly like retail.
struct Setter {
    Setter(uint32_t fn) {
        mWords[0] = fn;
        mWords[1] = 0;
        mWords[2] = 0;
        mWords[3] = 0;
    }
    uint32_t mWords[4];
};

// (PropertyFunc<T>: vptr +0x0, mpNext +0x4, mpSetter +0x8 (16 bytes), mValue +0x18)
Property* CreatePropertyFunc_f(StackAllocator* a, Setter s, float value);                 // 0x008f3020
Property* CreatePropertyFunc_u(StackAllocator* a, Setter s, unsigned value);              // 0x008f33a0
Property* CreatePropertyFunc_L(StackAllocator* a, Setter s, Length value);                // 0x008f3090
Property* CreatePropertyFunc_u16(StackAllocator* a, Setter s,
                                 unsigned short c1, unsigned short c2);                   // 0x008f3100
Property* CreatePropertyFunc_LI(StackAllocator* a, Setter s, Length value, int edge);      // 0x008f3170

// ---- CSSTokenReader::mMatchText (eastl::basic_string<wchar_t>) ---------------
struct String {
    wchar_t* mpBegin;      // +0x0
    wchar_t* mpEnd;        // +0x4
    wchar_t* mpCapacity;   // +0x8
    void*    mpAllocName;   // +0xc
    void swap(String& x) {
        wchar_t* t;
        t = mpBegin;    mpBegin = x.mpBegin;       x.mpBegin = t;
        t = mpEnd;      mpEnd = x.mpEnd;           x.mpEnd = t;
        t = mpCapacity; mpCapacity = x.mpCapacity; x.mpCapacity = t;
    }
    void Empty() {
        if (mpBegin != mpEnd) {
            *mpBegin = L'\0';
            mpEnd = mpBegin;
        }
    }
};

// CSSTokenReader (base CharStream<wchar_t>), 0x24 bytes
struct Reader {
    wchar_t* mScanPos;     // +0x0
    wchar_t* mScanEnd;     // +0x4
    int      mLineBegin;   // +0x8
    int      mCurrentLine; // +0xc
    String   mMatchText;   // +0x10
    int      mResult;      // +0x20
};

class PropertyList;

// EA::XHTML::Style::CSSParser (0x50 bytes)
class CSSParser {
public:
    bool ParseStretch(PropertyList* pList);             // 0x008f6620
    void ParseFont(PropertyList* pList);                // 0x008f66a0
    bool ParseColor(PropertyList* pList);               // 0x008f69a0
    bool ParseBackgroundColor(PropertyList* pList);     // 0x008f6a00
    bool ParseBackgroundPosition(PropertyList* pList);  // 0x008f6ad0
    bool ParseBackground(PropertyList* pList);          // 0x008f6da0
    bool ParseWordSpacing(PropertyList* pList);         // 0x008f6eb0
    bool ParseLetterSpacing(PropertyList* pList);       // 0x008f6f50
    bool ParseTextDecoration(PropertyList* pList);      // 0x008f6ff0
    bool ParseVerticalAlign(PropertyList* pList);       // 0x008f7130
    bool ParseTextIndent(PropertyList* pList);          // 0x008f72e0
    bool ParseLineHeight(PropertyList* pList);          // 0x008f7380
    bool ParseMarginEdge(PropertyList* pList, int edge);   // 0x008f7430
    void ParseMargin(PropertyList* pList);              // 0x008f7500
    bool ParsePaddingEdge(PropertyList* pList, int edge);  // 0x008f7610

private:
    bool ParseBackgroundImage(PropertyList* pList);     // 0x008f4890
    bool ParseBackgroundRepeat(PropertyList* pList);    // 0x008f6a60
    bool ParseBackgroundAttachment(PropertyList* pList);// 0x008f4930
    void Advance();                                        // 0x008f3d90
    bool SkipSpace();                                      // 0x008f4290
    bool MatchKeyword(const wchar_t* pKeyword);            // 0x008f43a0
    void Error(unsigned int code);                         // 0x008f2f10
    bool MatchColor(unsigned* pColor);                     // 0x008f55f0
    bool MatchLength(Length* pLength);                     // 0x008f5560
    void ParseFontFamily(PropertyList* pList);             // 0x008f4600
    bool MatchSymbolWeight(const void* pTable, unsigned* pValue);   // 0x008f52c0
    bool MatchSymbolBgRepeat(const void* pTable, float* pValue);    // 0x008f53e0
    bool MatchSymbolSize(const void* pTable, Length* pValue);       // 0x008f5320
    bool MatchSymbolFontSize(const void* pTable, unsigned* pValue); // 0x008f5380
    bool MatchSymbolVAlign(const void* pTable, unsigned* pValue);   // 0x008f5440
    bool MatchSymbolTextDecor(const void* pTable, unsigned* pValue);// 0x008f54a0
    void SetEdgeProperties(PropertyList* pList, const Length* pLengths, int nCount, Setter s);  // 0x008f31f0

    wchar_t* mpSourceURI;          // +0x00
    Reader   mReader;              // +0x04
    int      mToken;               // +0x28
    int      mTokenLine;           // +0x2c
    unsigned int mTokenLineStart;  // +0x30
    unsigned int mTokenPos;        // +0x34
    String   mTokenValue;          // +0x38
    void*    mpErrorListener;      // +0x48
    StackAllocator* mAllocator;    // +0x4c
};

// @ 0x008f6620
bool CSSParser::ParseStretch(PropertyList* pList)
{
    float value = 1.0f;
    if (MatchSymbolBgRepeat(gTableBgRepeat, &value)) {
        pList->Add(CreatePropertyFunc_f(mAllocator, Setter(0x8f27a0), value));
        return true;
    }
    return false;
}

// @ 0x008f66a0
void CSSParser::ParseFont(PropertyList* pList)
{
    unsigned style;
    if (MatchSymbolWeight(gTableFontStyle, &style)) {
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f2700), style));
        SkipSpace();
    }
    if (mToken == TokenIdent && wcscmp(L"normal", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f2720), 0));
        SkipSpace();
    } else if (MatchKeyword(L"small-caps")) {
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f2720), 1));
        SkipSpace();
    }
    unsigned weight;
    Length len;
    len.mValue = 0.0f;
    len.mUnits = 0;
    if (MatchSymbolSize(gTableFontWeight, &len)) {
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f2760), len.mUnits));
    } else {
        bool hasLength = MatchLength(&len);
        if (hasLength && len.mUnits == 0) {
            pList->Add(CreatePropertyFunc_f(mAllocator, Setter(0x8f2740), len.mValue));
            SkipSpace();
        } else if (!hasLength) {
            SkipSpace();
        }
        if (MatchLength(&len)) {
            pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2780), len));
        } else {
            if (MatchSymbolFontSize(gTableFontSize, &weight))
                pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8fb8a0), weight));
            else
                Error(0x23b0022);
        }
    }
    SkipSpace();
    if (mToken == TokenSlash) {
        mTokenValue.swap(mReader.mMatchText);
        Advance();
        if (MatchLength(&len))
            pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2990), len));
        else
            Error(0x23b0022);
    }
    SkipSpace();
    ParseFontFamily(pList);
}

// @ 0x008f69a0
bool CSSParser::ParseColor(PropertyList* pList)
{
    unsigned color;
    if (MatchColor(&color)) {
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f27e0), color));
        return true;
    }
    return false;
}

// @ 0x008f6a00
bool CSSParser::ParseBackgroundColor(PropertyList* pList)
{
    unsigned color;
    if (MatchColor(&color)) {
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f27f0), color));
        return true;
    }
    return false;
}

// @ 0x008f6ad0
bool CSSParser::ParseBackgroundPosition(PropertyList* pList)
{
    Length x;
    Length y;
    if (MatchLength(&x)) {
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2840), x));
        if (MatchLength(&y))
            pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2860), y));
        return true;
    }
    bool bFound = false;
    x = Length(0.0f, Unit_Unset);
    y = Length(0.0f, Unit_Unset);
    for (int i = 0; i < 2; i++) {
        if (mToken == TokenIdent) {
            if (wcscmp(L"left", mReader.mMatchText.mpBegin) == 0) {
                Advance();
                x = Length(0.0f, Unit_Percentage);
                goto next;
            } else if (wcscmp(L"right", mReader.mMatchText.mpBegin) == 0) {
                Advance();
                x = Length(100.0f, Unit_Percentage);
                goto next;
            }
        }
        if (MatchKeyword(L"top")) {
            y = Length(0.0f, Unit_Percentage);
        } else if (MatchKeyword(L"bottom")) {
            y = Length(100.0f, Unit_Percentage);
        } else if (MatchKeyword(L"center")) {
            if (x.mUnits == Unit_Unset)
                x = Length(50.0f, Unit_Percentage);
            if (y.mUnits == Unit_Unset)
                y = Length(50.0f, Unit_Percentage);
        } else {
            break;
        }
next:
        bFound = true;
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
    }
    if (x.mUnits != Unit_Unset)
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2840), x));
    if (y.mUnits != Unit_Unset)
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2860), y));
    return bFound;
}

// @ 0x008f6da0
bool CSSParser::ParseBackground(PropertyList* pList)
{
    bool bFound = false;
    for (;;) {
        unsigned color;
        if (MatchColor(&color)) {
            void* pMem = mAllocator->Allocate(sizeof(PropertyFunc<unsigned>));
            if (pMem) {
                PropertyFunc<unsigned>* pFunc =
                    new (pMem) PropertyFunc<unsigned>();
                pFunc->mpSetter = &StyleState::SetBackgroundColor;
                pFunc->mValue = color;
            }
            pList->Add((Property*)pMem);
        } else if (!ParseBackgroundImage(pList) && !ParseBackgroundRepeat(pList) &&
                   !ParseBackgroundAttachment(pList) && !ParseBackgroundPosition(pList)) {
            return bFound;
        }
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
        bFound = true;
    }
}

// @ 0x008f6eb0
bool CSSParser::ParseWordSpacing(PropertyList* pList)
{
    Length len;
    len.mValue = 0.0f;
    len.mUnits = 0;
    if (MatchLength(&len)) {
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2880), len));
        return true;
    }
    if (!MatchKeyword(L"normal"))
        return false;
    len.mValue = 0.0f;
    len.mUnits = Unit_Auto;
    pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2880), len));
    return true;
}

// @ 0x008f6f50
bool CSSParser::ParseLetterSpacing(PropertyList* pList)
{
    Length len;
    len.mValue = 0.0f;
    len.mUnits = 0;
    if (MatchLength(&len)) {
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f28a0), len));
        return true;
    }
    if (!MatchKeyword(L"normal"))
        return false;
    len.mValue = 0.0f;
    len.mUnits = Unit_Auto;
    pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f28a0), len));
    return true;
}

// @ 0x008f6ff0
bool CSSParser::ParseTextDecoration(PropertyList* pList)
{
    unsigned flags = 0;
    short none = 0;
    while (mToken == TokenIdent) {
        unsigned value;
        if (MatchSymbolTextDecor(gTableTextDecor, &value)) {
            Advance();
            flags |= value;
        } else if (wcscmp(L"none", mReader.mMatchText.mpBegin) == 0) {
            Advance();
            flags = 0;
            none = -1;
        } else {
            break;
        }
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
    }
    if ((short)flags != 0 || none != 0) {
        pList->Add(CreatePropertyFunc_u16(mAllocator, Setter(0x8f28c0),
                                        (unsigned short)flags, (unsigned short)none));
    }
    return true;
}

// @ 0x008f7130
bool CSSParser::ParseVerticalAlign(PropertyList* pList)
{
    Length len;
    len.mValue = 0.0f;
    len.mUnits = 0;
    if (MatchLength(&len)) {
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2910), len));
        return true;
    }
    if (MatchSymbolVAlign(gTableVAlign, (unsigned*)&len.mValue)) {
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f2940), *(unsigned*)&len.mValue));
        return true;
    }
    return false;
}

// @ 0x008f72e0
bool CSSParser::ParseTextIndent(PropertyList* pList)
{
    Length len;
    len.mValue = 0.0f;
    len.mUnits = 0;
    if (MatchLength(&len)) {
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2970), len));
        return true;
    }
    if (!MatchKeyword(L"inherit"))
        return false;
    len.mValue = 0.0f;
    len.mUnits = Unit_Inherit;
    pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2970), len));
    return true;
}

// @ 0x008f7380
bool CSSParser::ParseLineHeight(PropertyList* pList)
{
    Length len;
    len.mValue = 1.0f;
    len.mUnits = Unit_Auto;
    if (!MatchLength(&len)) {
        if (MatchKeyword(L"inherit")) {
            len.mValue = 0.0f;
            len.mUnits = Unit_Inherit;
        } else if (!MatchKeyword(L"normal")) {
            return false;
        }
    }
    pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2990), len));
    return true;
}

// @ 0x008f7430
bool CSSParser::ParseMarginEdge(PropertyList* pList, int edge)
{
    Length len;
    len.mValue = 0.0f;
    len.mUnits = Unit_Auto;
    if (mToken == TokenIdent && wcscmp(L"auto", mReader.mMatchText.mpBegin) == 0) {
        Advance();
    } else if (!MatchLength(&len)) {
        return false;
    }
    pList->Add(CreatePropertyFunc_LI(mAllocator, Setter(0x8f29b0), len, edge));
    return true;
}

// @ 0x008f7500
void CSSParser::ParseMargin(PropertyList* pList)
{
    Length lengths[4] = { Length(0.0f, 0), Length(0.0f, 0),
                          Length(0.0f, 0), Length(0.0f, 0) };
    int count = 0;
    for (; count < 4; count++) {
        if (mToken == TokenIdent && wcscmp(L"auto", mReader.mMatchText.mpBegin) == 0) {
            Advance();
            lengths[count] = Length(0.0f, Unit_Auto);
        } else if (!MatchLength(&lengths[count])) {
            break;
        }
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
    }
    SetEdgeProperties(pList, lengths, count, Setter(0x8f29b0));
}

// @ 0x008f7610
bool CSSParser::ParsePaddingEdge(PropertyList* pList, int edge)
{
    Length len;
    len.mValue = 0.0f;
    len.mUnits = 0;
    if (MatchLength(&len)) {
        pList->Add(CreatePropertyFunc_LI(mAllocator, Setter(0x8f2a20), len, edge));
        return true;
    }
    return false;
}
}
}
}
