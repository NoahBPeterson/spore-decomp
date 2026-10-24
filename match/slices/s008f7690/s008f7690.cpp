// Slice s008f7690 -- EA::XHTML::Style::CSSParser property parsers.
//
// This region parses individual CSS property values ("padding", "border-width",
// "border-color", "border-style", "border-spacing", "list-style", ...) and
// appends a Property setter to the caller's PropertyList.  Each parser shares
// the same shape: read a value (or a keyword), consume any trailing whitespace
// and hand the value to a CreatePropertyFunc<...> / SetEdgeProperties<...>
// instantiation from the same translation unit.
//
// Includes the older ParseBoxHeight body (0x008f7f20) that was already present.
#include "types.h"
#include <stddef.h>
#include <wchar.h>

namespace EA {
namespace Allocator {
class StackAllocator;
}  // namespace Allocator
}  // namespace EA

inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator& allocator) throw();

namespace EA {
namespace XHTML {
namespace Style {

using EA::Allocator::StackAllocator;

enum Units {
    Unit_Number = 0, Unit_Pixels = 1, Unit_Points = 2, Unit_Picas = 3, Unit_Millimeters = 4,
    Unit_Centimeters = 5, Unit_Inches = 6, Unit_Ems = 7, Unit_Exs = 8, Unit_Percentage = 9,
    Unit_Auto = 10, Unit_Inherit = 11, Unit_BorderSize = 12, Unit_Unset = 13
};

struct Length {  // size 0x8
    Length() : mValue(0.0f), mUnits(Unit_Number) {}
    Length(float value, Units units) : mValue(value), mUnits(units) {}
    float mValue;  // +0x0
    Units mUnits;  // +0x4
};

class StyleState;

// The setter is a pointer to a StyleState member formed while StyleState is still incomplete, so it
// uses MSVC's 16-byte general (unknown-inheritance) form. A member of this type fixes that layout.
class SetterHolder {
public:
    void (StyleState::*mSetter)(Length);
};

class Property {  // size 0x8
public:
    virtual void Apply(StyleState* pState) const;
    Property* mpNext;  // +0x4
};

class PropertyList {  // size 0x4
public:
    void Add(Property* p) {
        p->mpNext = mpFirst;
        mpFirst = p;
    }
    Property* mpFirst;  // +0x0
};

// Built from the setter pointer, the allocator and the value. Defined in another slice (0x008f3090).
template <class T>
Property* CreatePropertyFunc(StackAllocator* pAllocator, void (StyleState::*pSetter)(T), T arg);

class StyleState {
public:
    void SetHeight(Length len);  // 0x008f2c10: writes mHeight (+0x374 value, +0x378 units)
    void SetBoxWidth(Length len);            // 0x008f2bf0
    void SetPadding(Length len);             // 0x008f2a20
    void SetBorderWidth(Length len, int e);  // 0x008f2a90
    void SetBorderColor(unsigned c, int e);  // 0x008f2b00
    void SetBorderStyle(unsigned s, int e);  // 0x008f2b40
    void SetBoxOffset(Length len, int e);    // 0x008f2c60
    void SetPosition(unsigned p);            // 0x008f2c50
    void SetListStyleType(unsigned t);       // 0x008f2cb0
    void SetBorderSpacingX(Length len);      // 0x008f2b80
    void SetBorderSpacingY(Length len);      // 0x008f2ba0
    void SetBorderSpacing(Length len);       // 0x008f2bc0
    void SetFontSmoothThresh(Length len);    // 0x008f27c0
};

struct MatchText {  // eastl::basic_string<wchar_t> (only the begin pointer is used here)
    const wchar_t* mpBegin;  // +0x0
    char mRest[0xc];         // +0x4
};

// Token kinds produced by the CSS token reader (mToken at +0x28).
enum Token {
    TokenWS     = 2,   // whitespace run, held in mTokenValue
    TokenIdent  = 3,   // identifier, held in mTokenValue
};

class CSSParser {
public:
    // --- already present in this slice (older body) ---
    bool ParseBoxHeight(PropertyList* pList);  // 0x008f7f20

    // --- property parsers added by this slice ---
    void  ParsePadding(void* pList);                  // 0x008f7690
    bool  ParseBorderWidthEdge(PropertyList* pList, void* pEdge);   // 0x008f7740
    void  ParseBorderWidth(void* pList);              // 0x008f7820
    bool  ParseBorderColorEdge(PropertyList* pList, void* pEdge);   // 0x008f7a00
    void  ParseBorderColor(void* pList);              // 0x008f7a70
    bool  ParseBorderStyleEdge(PropertyList* pList, void* pEdge);   // 0x008f7b00
    void  ParseBorderStyle(void* pList);              // 0x008f7b70
    bool  ParseBorder(void* pList, void* pEdge);      // 0x008f7c30
    bool  ParseBorderStyle2(PropertyList* pList);     // 0x008f7e50
    bool  ParseListStyle(PropertyList* pList);        // 0x008f81b0
    bool  ParsePosition(void* pList);                 // 0x008f82d0
    bool  ParseBoxEdge(PropertyList* pList, void* pEdge);           // 0x008f8340
    bool  ParseBorderSpacing(PropertyList* pList);    // 0x008f8400
    bool  ParseFontSmooth(PropertyList* pList);       // 0x008f8510

private:
    void Advance();                     // 0x008f3d90
    bool MatchLength(Length* pLength);  // 0x008f5560
    bool MatchColor(unsigned* pColor);  // 0x008f55f0
    bool MatchStyleSymbol(const void* pTable, unsigned* pStyle);  // 0x008f5140 MatchSymbol<...,144>
    bool MatchSymbolSize7(const void* pTable, int* pValue);       // 0x008f5320 MatchSymbol<...,7>
    bool MatchKeyword(const wchar_t* pWord);                      // 0x008f43a0
    bool LookupListStyleType(unsigned* pType);
    bool ParseListStyleImage(PropertyList* pList);
    bool ParseListStylePosition(PropertyList* pList);
    void SkipWhitespace();

    wchar_t* mpSourceURI;      // +0x00
    char mReaderStream[0x10];  // +0x04 CSSTokenReader: stream, mLineBegin, mCurrentLine
    MatchText mMatchText;      // +0x14 CSSTokenReader::mMatchText
    char mReaderResult[4];     // +0x24 CSSTokenReader::mResult
    int mToken;                // +0x28 CSSToken
    int mPad_2c;               // +0x2c
    int mPad_30;               // +0x30
    void* mPad_34;             // +0x34
    wchar_t* mpTokenValueBegin;// +0x38 mTokenValue.mpBegin
    wchar_t* mpTokenValueEnd;  // +0x3c mTokenValue.mpEnd
    char mTokenValueRest[0xc]; // +0x40
    StackAllocator* mAllocator;  // +0x4c
};

// ===========================================================================
// Helpers from the same translation unit (defined in other slices).
// ===========================================================================

// SetEdgeProperties<T>: expands the 1..4 parsed edge values over the four CSS
// edges.  The setter/allocator are template parameters, so only the runtime
// arguments appear here.
void SetEdgePropertiesLen(CSSParser* pParser, void* pList, Length* pValues,
                          int nCount);  // 0x008f31f0  SetEdgeProperties<Length>
void SetEdgePropertiesUint(CSSParser* pParser, void* pList, unsigned* pValues,
                           int nCount);  // 0x008f32d0  SetEdgeProperties<unsigned>

// CreatePropertyFunc<T> family.  Each instantiation is a distinct retail symbol.
Property* CreatePropLen(StackAllocator* pAlloc, void (StyleState::*pSetter)(Length),
                        Length value);  // 0x008f3090
Property* CreatePropLenIdx(StackAllocator* pAlloc, void (StyleState::*pSetter)(Length, int),
                           Length value, int index);  // 0x008f3170
Property* CreatePropUintIdx(StackAllocator* pAlloc, void (StyleState::*pSetter)(unsigned, int),
                            unsigned value, int index);  // 0x008f3410
Property* CreatePropUint(StackAllocator* pAlloc, void (StyleState::*pSetter)(unsigned),
                         unsigned value);  // 0x008f33a0

// eastl::equal_range over a (first,last) table of IStaticDefinition entries.
void StaticDefEqualRange(void* pBeginOut, const void* pTableBegin, const void* pTableEnd,
                         void* pKeyPtr);  // 0x008f3790

// Table lookups for the wide keyword/table matches.
extern const char gListStyleTypeTable[];      // 0x0154da10
extern const char gListStylePositionTable[];  // 0x0154da58
extern const char gPositionTable[];           // 0x0154da58
extern const char gBorderStyleTable[];        // 0x0154d980
extern const char gBorderStyleEnd[];          // 0x0154d9c8

// ===========================================================================
// Whitespace skip: clears the pending run and advances the reader.
// ===========================================================================
inline void CSSParser::SkipWhitespace() {
    while (mToken == TokenWS) {
        wchar_t* pBegin = mpTokenValueBegin;
        if (pBegin != mpTokenValueEnd) {
            *pBegin = L'\0';
            mpTokenValueEnd = mpTokenValueBegin;
        }
        Advance();
    }
}

// ===========================================================================
// 0x008f7690  EA::XHTML::Style::CSSParser::ParsePadding
// ===========================================================================
// @ 0x008f7690  EA::XHTML::Style::CSSParser::ParsePadding
void CSSParser::ParsePadding(void* pList) {
    Length values[4];
    int n = 0;
    do {
        if (!MatchLength(&values[n]))
            break;
        SkipWhitespace();
        ++n;
    } while (n < 4);
    SetEdgePropertiesLen(this, pList, values, n);
}

// ===========================================================================
// 0x008f7740  EA::XHTML::Style::CSSParser::ParseBorderWidthEdge
// ===========================================================================
// @ 0x008f7740  EA::XHTML::Style::CSSParser::ParseBorderWidthEdge
bool CSSParser::ParseBorderWidthEdge(PropertyList* pList, void* pEdge) {
    Length len(0.0f, Unit_Number);
    if (!MatchLength(&len)) {
        if (MatchKeyword(L"thin")) {
            len.mValue = 1.0f;
        } else if (MatchKeyword(L"medium")) {
            len.mValue = 2.0f;
        } else if (MatchKeyword(L"thick")) {
            len.mValue = 3.0f;
        } else {
            return false;
        }
        len.mUnits = Unit_BorderSize;  // 0xc
    }
    Property* p = CreatePropLenIdx(mAllocator, &StyleState::SetBorderWidth, len, (int)(intptr_t)pEdge);
    p->mpNext = pList->mpFirst;
    pList->mpFirst = p;
    return true;
}

// ===========================================================================
// 0x008f7820  EA::XHTML::Style::CSSParser::ParseBorderWidth
// ===========================================================================
// @ 0x008f7820  EA::XHTML::Style::CSSParser::ParseBorderWidth
void CSSParser::ParseBorderWidth(void* pList) {
    Length values[4] = {Length(0.0f, Unit_Number), Length(0.0f, Unit_Number),
                        Length(0.0f, Unit_Number), Length(0.0f, Unit_Number)};
    int n = 0;
    Length* p = values;
    do {
        if (mToken == TokenIdent) {
            const wchar_t* pText = mMatchText.mpBegin;
            if (wcscmp(pText, L"thin") == 0) {
                Advance();
                *p = Length(1.0f, Unit_BorderSize);
            } else if (wcscmp(pText, L"medium") == 0) {
                Advance();
                *p = Length(2.0f, Unit_BorderSize);
            } else if (wcscmp(pText, L"thick") == 0) {
                Advance();
                *p = Length(3.0f, Unit_BorderSize);
            } else if (!MatchLength(p)) {
                break;
            }
            SkipWhitespace();
        } else if (!MatchLength(p)) {
            break;
        } else {
            SkipWhitespace();
        }
        ++n;
        ++p;
    } while (n < 4);
    SetEdgePropertiesLen(this, pList, values, n);
}

// ===========================================================================
// 0x008f7a00  EA::XHTML::Style::CSSParser::ParseBorderColorEdge
// ===========================================================================
// @ 0x008f7a00  EA::XHTML::Style::CSSParser::ParseBorderColorEdge
bool CSSParser::ParseBorderColorEdge(PropertyList* pList, void* pEdge) {
    unsigned color;
    if (MatchColor(&color)) {
        Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderColor, color, (int)(intptr_t)pEdge);
        p->mpNext = pList->mpFirst;
        pList->mpFirst = p;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x008f7a70  EA::XHTML::Style::CSSParser::ParseBorderColor
// ===========================================================================
// @ 0x008f7a70  EA::XHTML::Style::CSSParser::ParseBorderColor
void CSSParser::ParseBorderColor(void* pList) {
    int n = 0;
    unsigned colors[4];
    unsigned* p = colors;
    do {
        if (!MatchColor(p))
            break;
        SkipWhitespace();
        ++n;
        ++p;
    } while (n < 4);
    SetEdgePropertiesUint(this, pList, colors, n);
}

// ===========================================================================
// 0x008f7b00  EA::XHTML::Style::CSSParser::ParseBorderStyleEdge
// ===========================================================================
// @ 0x008f7b00  EA::XHTML::Style::CSSParser::ParseBorderStyleEdge
bool CSSParser::ParseBorderStyleEdge(PropertyList* pList, void* pEdge) {
    unsigned style;
    if (MatchStyleSymbol(&gBorderStyleTable, &style)) {
        Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderStyle, style, (int)(intptr_t)pEdge);
        p->mpNext = pList->mpFirst;
        pList->mpFirst = p;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x008f7b70  EA::XHTML::Style::CSSParser::ParseBorderStyle
// ===========================================================================
// @ 0x008f7b70  EA::XHTML::Style::CSSParser::ParseBorderStyle
void CSSParser::ParseBorderStyle(void* pList) {
    unsigned styles[4];
    int n = 0;
    do {
        if (mToken != TokenIdent)
            break;
        const wchar_t* pText = mMatchText.mpBegin;
        unsigned style = 0;
        (void)pText;
        if (!MatchStyleSymbol(&gBorderStyleTable, &style))
            break;
        styles[n] = style;
        Advance();
        SkipWhitespace();
        ++n;
    } while (n < 4);
    SetEdgePropertiesUint(this, pList, styles, n);
}

// ===========================================================================
// 0x008f7c30  EA::XHTML::Style::CSSParser::ParseBorder
// ===========================================================================
// @ 0x008f7c30  EA::XHTML::Style::CSSParser::ParseBorder
bool CSSParser::ParseBorder(void* pList, void* pEdge) {
    PropertyList* pl = (PropertyList*)pList;
    bool bWidth = false, bStyle = false, bColor = false;
    for (;;) {
        if (ParseBorderWidthEdge(pl, pEdge)) {
            bWidth = true;
        } else if (mToken == TokenIdent) {
            const wchar_t* pText = mMatchText.mpBegin;
            unsigned style = 0;
            (void)pText;
            if (!MatchStyleSymbol(&gBorderStyleTable, &style)) {
                if (MatchColor(&(unsigned&)pEdge)) {
                    Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderColor,
                                                    (unsigned)(intptr_t)pEdge, (int)(intptr_t)pEdge);
                    p->mpNext = pl->mpFirst;
                    bColor = true;
                    pl->mpFirst = p;
                } else {
                    if (!bWidth) {
                        Property* p = CreatePropLenIdx(mAllocator, &StyleState::SetBorderWidth,
                                                       Length(2.0f, Unit_Pixels), 1);
                        p->mpNext = pl->mpFirst;
                        pl->mpFirst = p;
                    }
                    if (!bStyle) {
                        Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderStyle,
                                                        0, (int)(intptr_t)pEdge);
                        p->mpNext = pl->mpFirst;
                        pl->mpFirst = p;
                    }
                    if (!bColor) {
                        Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderColor,
                                                        0, (int)(intptr_t)pEdge);
                        p->mpNext = pl->mpFirst;
                        pl->mpFirst = p;
                    }
                    return bWidth || bStyle || bColor;
                }
            } else {
                Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderStyle,
                                                style, (int)(intptr_t)pEdge);
                p->mpNext = pl->mpFirst;
                bStyle = true;
                pl->mpFirst = p;
            }
        } else if (MatchColor((unsigned*)&pEdge)) {
            Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderColor,
                                            (unsigned)(intptr_t)pEdge, (int)(intptr_t)pEdge);
            p->mpNext = pl->mpFirst;
            bColor = true;
            pl->mpFirst = p;
        } else {
            if (!bWidth) {
                Property* p = CreatePropLenIdx(mAllocator, &StyleState::SetBorderWidth,
                                               Length(2.0f, Unit_Pixels), 1);
                p->mpNext = pl->mpFirst;
                pl->mpFirst = p;
            }
            if (!bStyle) {
                Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderStyle, 0,
                                                (int)(intptr_t)pEdge);
                p->mpNext = pl->mpFirst;
                pl->mpFirst = p;
            }
            if (!bColor) {
                Property* p = CreatePropUintIdx(mAllocator, &StyleState::SetBorderColor, 0,
                                                (int)(intptr_t)pEdge);
                p->mpNext = pl->mpFirst;
                pl->mpFirst = p;
            }
            return bWidth || bStyle || bColor;
        }
        // trailing whitespace skip
        while (mToken == TokenWS) {
            wchar_t* pB = mpTokenValueBegin;
            if (pB != mpTokenValueEnd) {
                *pB = L'\0';
                mpTokenValueEnd = pB;
            }
            Advance();
        }
    }
}

// ===========================================================================
// 0x008f7e50  EA::XHTML::Style::CSSParser::ParseBorderStyle2
// ===========================================================================
// @ 0x008f7e50  EA::XHTML::Style::CSSParser::ParseBorderStyle2
bool CSSParser::ParseBorderStyle2(PropertyList* pList) {
    Length value(0.0f, Unit_Auto);
    if (mToken == TokenIdent && wcscmp(L"auto", mMatchText.mpBegin) == 0) {
        Advance();
    } else if (!MatchLength(&value)) {
        return false;
    }
    Property* p = CreatePropLen(mAllocator, &StyleState::SetBoxWidth, value);
    p->mpNext = pList->mpFirst;
    pList->mpFirst = p;
    return true;
}

// ===========================================================================
// 0x008f81b0  EA::XHTML::Style::CSSParser::ParseListStyle
// ===========================================================================
// @ 0x008f81b0  EA::XHTML::Style::CSSParser::ParseListStyle
bool CSSParser::ParseListStyle(PropertyList* pList) {
    bool bAny = false;
    for (;;) {
        if (mToken == TokenIdent) {
            const wchar_t* pText = mMatchText.mpBegin;
            unsigned listType = 0;
            (void)pText;
            if (LookupListStyleType(&listType)) {
                Advance();
                Property* p = CreatePropUint(mAllocator, &StyleState::SetListStyleType, listType);
                p->mpNext = pList->mpFirst;
                pList->mpFirst = p;
            } else if (!ParseListStyleImage(pList)) {
                if (!ParseListStylePosition(pList))
                    return false;
            }
        } else if (!ParseListStyleImage(pList)) {
            if (!ParseListStylePosition(pList))
                return false;
        }
        SkipWhitespace();
        bAny = true;
    }
}

// ===========================================================================
// 0x008f82d0  EA::XHTML::Style::CSSParser::ParsePosition
// ===========================================================================
// @ 0x008f82d0  EA::XHTML::Style::CSSParser::ParsePosition
bool CSSParser::ParsePosition(void* pList) {
    int value = 0;
    if (MatchSymbolSize7(&gPositionTable, &value)) {
        Property* p = CreatePropUint(mAllocator, &StyleState::SetPosition, (unsigned)value);
        p->mpNext = ((PropertyList*)pList)->mpFirst;
        ((PropertyList*)pList)->mpFirst = p;
        return true;
    }
    MatchKeyword(L"inherit");
    return false;
}

// ===========================================================================
// 0x008f8340  EA::XHTML::Style::CSSParser::ParseBoxEdge
// ===========================================================================
// @ 0x008f8340  EA::XHTML::Style::CSSParser::ParseBoxEdge
bool CSSParser::ParseBoxEdge(PropertyList* pList, void* pEdge) {
    Length value(0.0f, Unit_Number);
    if (!MatchLength(&value)) {
        if (MatchKeyword(L"auto")) {
            value.mUnits = Unit_Auto;  // 0xa
        } else if (MatchKeyword(L"inherit")) {
            value.mUnits = Unit_Inherit;  // 0xb
        } else {
            return false;
        }
        value.mValue = 0.0f;
    }
    Property* p = CreatePropLenIdx(mAllocator, &StyleState::SetBoxOffset, value,
                                   (int)(intptr_t)pEdge);
    p->mpNext = pList->mpFirst;
    pList->mpFirst = p;
    return true;
}

// ===========================================================================
// 0x008f8400  EA::XHTML::Style::CSSParser::ParseBorderSpacing
// ===========================================================================
// @ 0x008f8400  EA::XHTML::Style::CSSParser::ParseBorderSpacing
bool CSSParser::ParseBorderSpacing(PropertyList* pList) {
    Length first(0.0f, Unit_Number);
    Length second(0.0f, Unit_Number);
    if (!MatchLength(&first))
        return false;
    if (MatchLength(&second)) {
        Property* p = CreatePropLen(mAllocator, &StyleState::SetBorderSpacingX, first);
        p->mpNext = pList->mpFirst;
        pList->mpFirst = p;
        p = CreatePropLen(mAllocator, &StyleState::SetBorderSpacingY, second);
        p->mpNext = pList->mpFirst;
        pList->mpFirst = p;
        return true;
    }
    Property* p = CreatePropLen(mAllocator, &StyleState::SetBorderSpacing, first);
    p->mpNext = pList->mpFirst;
    pList->mpFirst = p;
    return true;
}

// ===========================================================================
// 0x008f8510  EA::XHTML::Style::CSSParser::ParseFontSmooth
// ===========================================================================
// @ 0x008f8510  EA::XHTML::Style::CSSParser::ParseFontSmooth
bool CSSParser::ParseFontSmooth(PropertyList* pList) {
    Length value(0.0f, Unit_Number);
    if (!MatchLength(&value)) {
        if (MatchKeyword(L"never")) {
            value = Length(1000000.0f, Unit_Pixels);  // 0x49742400, units 1
        } else if (MatchKeyword(L"always")) {
            value = Length(0.0f, Unit_Pixels);        // units 1
        } else if (MatchKeyword(L"auto")) {
            value = Length(0.0f, Unit_Auto);          // units 10
        } else {
            return false;
        }
        Property* p = CreatePropLen(mAllocator, &StyleState::SetFontSmoothThresh, value);
        p->mpNext = pList->mpFirst;
        pList->mpFirst = p;
    }
    return true;
}

// ===========================================================================
// Preserved older body (0x008f7f20).
// ===========================================================================
bool CSSParser::ParseBoxHeight(PropertyList* pList) {
    Length value(0.0f, Unit_Auto);
    bool bAuto = false;
    if (mToken == 3 /* TokenIdent */) {
        const wchar_t* pAuto = L"auto";
        const wchar_t* pText = mMatchText.mpBegin;
        bool bMismatch = false;
        wchar_t c;
        do {
            c = *pAuto;
            if (c != *pText) {
                bMismatch = true;
                break;
            }
            if (c == 0)
                break;
            c = pAuto[1];
            if (c != pText[1]) {
                bMismatch = true;
                break;
            }
            pAuto += 2;
            pText += 2;
        } while (c != 0);
        bAuto = !bMismatch;
    }
    if (bAuto) {
        Advance();
    } else if (!MatchLength(&value)) {
        return false;
    }
    pList->Add(CreatePropertyFunc(mAllocator, &StyleState::SetHeight, value));
    return true;
}

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
