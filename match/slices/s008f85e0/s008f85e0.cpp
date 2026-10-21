// Slice s008f85e0 -- EA::XHTML::Style::CSSParser: CSS property value dispatch and the
// property-collection parsers (SporeApp.exe 0x008f85e0 .. 0x008f9220).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <stddef.h>

typedef unsigned short wchar16;

namespace EA {
namespace Allocator {
class StackAllocator;
}  // namespace Allocator
}  // namespace EA

// The static empty wide string (an empty eastl::basic_string's begin/end, capacity one past).
extern "C" wchar16 gEmptyString[1];  // 0x01667bac
extern "C" wchar16 gEmptyStringEnd;  // 0x01667bae
// CSS property-name -> CSSPropertyID table searched by MatchSymbol.
extern "C" const char gPropertyTable[];  // 0x0154d020
// L"important".
extern "C" const wchar16 gImportant[];  // 0x01439bd0

// 0x008e2ed0: CSSParser destructor.  The shipping exe spells it as a free __fastcall void(void*).
void __fastcall Fn8e2ed0(void* pThis);

extern "C" int wcscmp(const wchar16* a, const wchar16* b);

namespace EA {
namespace XHTML {
namespace Style {

using EA::Allocator::StackAllocator;

enum Units {
    Unit_Number = 0, Unit_Pixels = 1, Unit_Points = 2, Unit_Picas = 3, Unit_Millimeters = 4,
    Unit_Centimeters = 5, Unit_Inches = 6, Unit_Ems = 7, Unit_Exs = 8, Unit_Percentage = 9,
    Unit_Auto = 10, Unit_Inherit = 11, Unit_BorderSize = 12, Unit_Unset = 13
};

// eastl-style pointer swap used by String::swap (its three field swaps).
static inline void SwapPtr(wchar16*& a, wchar16*& b) {
    wchar16* t = a; a = b; b = t;
}

// eastl::basic_string<wchar16> -- begin/end/capacity plus a per-string allocator name.
struct String {              // size 0x10
    wchar16* mpBegin;        // +0x00
    wchar16* mpEnd;          // +0x04
    wchar16* mpCapacity;     // +0x08
    void* mpAllocName;       // +0x0c
    void swap(String& x) {
        SwapPtr(mpBegin, x.mpBegin);
        SwapPtr(mpEnd, x.mpEnd);
        SwapPtr(mpCapacity, x.mpCapacity);
    }
    void Empty() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};

// A compiled CSS declaration (the game's Property): polymorphic, chained through mpNext.
class Property { public:        // size 0x8
    void* mpVptr;        // +0x00
    Property* mpNext;    // +0x04
};

// A single-linked list of Property (declaration set).
class PropertyList {  // size 0x4
public:
    PropertyList() : mpFirst(0) {}
    Property* mpFirst;  // +0x00
};

// CharStream: the character reader embedded in the parser.  (0x008f38b0 is its constructor
// from a source string.)
struct CharStream {          // size 0x24
    wchar16* mpScanPos;      // +0x00
    wchar16* mpScanEnd;      // +0x04
    wchar16* mpLineBegin;    // +0x08
    int mLineCount;          // +0x0c
    String mMatchText;       // +0x10
    int mResult;             // +0x20
    void* Fn8f38b0(wchar16* pSource);  // 0x008f38b0
};

class CSSParser {
public:
    // -- the five functions of this slice -----------------------------------------------
    bool ParsePropertyValue(int propID, PropertyList* pList);  // 0x008f85e0
    static bool ParsePropertyByID(int propID, wchar16* pSource, StackAllocator* pAllocator,
                                  PropertyList* pList, Units units,
                                  void* pErrorListener);  // 0x008f8cb0
    bool ParseProperty(PropertyList* pList);              // 0x008f8d50
    bool ParsePropertyCollection(void* pRule);            // 0x008f8e00
    static bool ParsePropertyCollectionFrom(wchar16* pSource, StackAllocator* pAllocator,
                                            Property** ppHeads,
                                            void* pErrorListener);  // 0x008f9000

private:
    // -- parser infrastructure ----------------------------------------------------------
    void Advance();                            // 0x008f3d90
    void Error(unsigned int nCode);            // 0x008f2f10
    bool SkipSpace();                          // 0x008f4290
    void Fn8f42d0();                           // 0x008f42d0
    bool Fn8f4360(int token);                  // 0x008f4360
    bool MatchSymbol(const void* pDef, int* pOut);  // 0x008f5500

    // -- property value parsers ---------------------------------------------------------
    bool ParseFontFamily(PropertyList* pList);          // 0x008f4600
    bool ParseFontVariant(PropertyList* pList);         // 0x008f47e0
    bool ParseFontWeight(PropertyList* pList);          // 0x008f6420
    bool ParseFontSize(PropertyList* pList);            // 0x008f64f0
    bool ParseFontSmooth(PropertyList* pList);          // 0x008f8510
    bool ParseFont(PropertyList* pList);                // 0x008f66a0
    bool ParseColor(PropertyList* pList);               // 0x008f69a0
    bool ParseBackgroundColor(PropertyList* pList);     // 0x008f6a00
    bool ParseBackgroundImage(PropertyList* pList);     // 0x008f4890
    bool ParseBackgroundRepeat(PropertyList* pList);    // 0x008f6a60
    bool ParseBackgroundAttachment(PropertyList* pList);  // 0x008f4930
    bool ParseBackgroundPosition(PropertyList* pList);  // 0x008f6ad0
    bool ParseBackground(PropertyList* pList);          // 0x008f6da0
    bool ParseWordSpacing(PropertyList* pList);         // 0x008f6eb0
    bool ParseLetterSpacing(PropertyList* pList);       // 0x008f6f50
    bool ParseTextDecoration(PropertyList* pList);      // 0x008f6ff0
    bool ParseVerticalAlign(PropertyList* pList);       // 0x008f7130
    bool ParseTextIndent(PropertyList* pList);          // 0x008f72e0
    bool ParseTextOverflow(PropertyList* pList);        // 0x008f5080
    bool ParseLineHeight(PropertyList* pList);          // 0x008f7380
    bool ParseMarginEdge(PropertyList* pList, int iEdge);   // 0x008f7430
    bool ParseMargin(PropertyList* pList);              // 0x008f7500
    bool ParsePaddingEdge(PropertyList* pList, int iEdge);  // 0x008f7610
    bool ParsePadding(PropertyList* pList);             // 0x008f7690
    bool ParseBorderWidthEdge(PropertyList* pList, int iEdge);  // 0x008f7740
    bool ParseBorderWidth(PropertyList* pList);         // 0x008f7820
    bool ParseBorderColorEdge(PropertyList* pList, int iEdge);  // 0x008f7a00
    bool ParseBorderColor(PropertyList* pList);         // 0x008f7a70
    bool ParseBorderStyle(PropertyList* pList);         // 0x008f7e50
    bool ParseBoxHeight(PropertyList* pList);           // 0x008f7f20
    bool ParseListStyleImage(PropertyList* pList);      // 0x008f49e0
    bool ParseListStylePosition(PropertyList* pList);   // 0x008f4aa0
    bool ParseListStyle(PropertyList* pList);           // 0x008f81b0
    bool ParsePosition(PropertyList* pList);            // 0x008f82d0
    bool ParseBoxEdge(PropertyList* pList, int iEdge);  // 0x008f8340
    bool ParseBorderSpacing(PropertyList* pList);       // 0x008f8400
    bool ParseDirection(PropertyList* pList);           // 0x008f4fc0

    bool Fn8f6340(PropertyList* pList);                 // 0x008f6340
    bool Fn8f63b0(PropertyList* pList);                 // 0x008f63b0
    bool Fn8f6620(PropertyList* pList);                 // 0x008f6620
    bool Fn8f7200(PropertyList* pList);                 // 0x008f7200
    bool Fn8f7270(PropertyList* pList);                 // 0x008f7270
    bool Fn8f7b00(PropertyList* pList, int iEdge);      // 0x008f7b00
    bool Fn8f7b70(PropertyList* pList);                 // 0x008f7b70
    bool Fn8f7c30(PropertyList* pList, int iEdge);      // 0x008f7c30
    bool Fn8f7ff0(PropertyList* pList);                 // 0x008f7ff0
    bool Fn8f8060(PropertyList* pList);                 // 0x008f8060
    bool Fn8f80d0(PropertyList* pList);                 // 0x008f80d0
    bool Fn8f8140(PropertyList* pList);                 // 0x008f8140
    bool Fn8f4b80(PropertyList* pList);                 // 0x008f4b80
    bool Fn8f4da0(PropertyList* pList);                 // 0x008f4da0

    wchar16* mpSourceURI;  // +0x00
    CharStream mReader;    // +0x04
    int mToken;            // +0x28  (CSSToken)
    int mTokenLine;        // +0x2c
    unsigned mTokenLineStart;  // +0x30
    unsigned mTokenPos;        // +0x34
    String mTokenValue;    // +0x38
    void* mpErrorListener;  // +0x48
    StackAllocator* mAllocator;  // +0x4c
    String mConvertedText;   // +0x50
    Units mDefaultUnits;     // +0x60
};

// =======================================================================================
// @ 0x008f85e0 CSSParser::ParsePropertyValue
// Dispatches one CSS property (already given its name) to the matching value parser.
bool CSSParser::ParsePropertyValue(int propID, PropertyList* pList) {
    bool ok;
    SkipSpace();
    switch (propID) {
    case 0x3a: ok = Fn8f6340(pList); break;
    case 0x00: ok = ParseFontFamily(pList); break;
    case 0x01: ok = Fn8f63b0(pList); break;
    case 0x02: ok = ParseFontVariant(pList); break;
    case 0x03: ok = ParseFontWeight(pList); break;
    case 0x04: ok = ParseFontSize(pList); break;
    case 0x06: ok = Fn8f6620(pList); break;
    case 0x07: ok = ParseFont(pList); break;
    case 0x08: ok = ParseColor(pList); break;
    case 0x09: ok = ParseBackgroundColor(pList); break;
    case 0x0a: ok = ParseBackgroundImage(pList); break;
    case 0x0b: ok = ParseBackgroundRepeat(pList); break;
    case 0x0c: ok = ParseBackgroundAttachment(pList); break;
    case 0x0d: ok = ParseBackgroundPosition(pList); break;
    case 0x0e: ok = ParseBackground(pList); break;
    case 0x0f: ok = ParseWordSpacing(pList); break;
    case 0x10: ok = ParseLetterSpacing(pList); break;
    case 0x11: ok = ParseTextDecoration(pList); break;
    case 0x12: ok = ParseVerticalAlign(pList); break;
    case 0x13: ok = Fn8f7200(pList); break;
    case 0x14: ok = Fn8f7270(pList); break;
    case 0x15: ok = ParseTextIndent(pList); break;
    case 0x17: ok = ParseLineHeight(pList); break;
    case 0x18: ok = ParseMarginEdge(pList, 0); break;
    case 0x19: ok = ParseMarginEdge(pList, 1); break;
    case 0x1a: ok = ParseMarginEdge(pList, 2); break;
    case 0x1b: ok = ParseMarginEdge(pList, 3); break;
    case 0x1c: ok = ParseMargin(pList); break;
    case 0x1d: ok = ParsePaddingEdge(pList, 0); break;
    case 0x1e: ok = ParsePaddingEdge(pList, 1); break;
    case 0x1f: ok = ParsePaddingEdge(pList, 2); break;
    case 0x20: ok = ParsePaddingEdge(pList, 3); break;
    case 0x21: ok = ParsePadding(pList); break;
    case 0x22: ok = ParseBorderWidthEdge(pList, 0); break;
    case 0x23: ok = ParseBorderWidthEdge(pList, 1); break;
    case 0x24: ok = ParseBorderWidthEdge(pList, 2); break;
    case 0x25: ok = ParseBorderWidthEdge(pList, 3); break;
    case 0x2e: ok = ParseBorderWidth(pList); break;
    case 0x26: ok = ParseBorderColorEdge(pList, 0); break;
    case 0x27: ok = ParseBorderColorEdge(pList, 1); break;
    case 0x28: ok = ParseBorderColorEdge(pList, 2); break;
    case 0x29: ok = ParseBorderColorEdge(pList, 3); break;
    case 0x2f: ok = ParseBorderColor(pList); break;
    case 0x2a: ok = Fn8f7b00(pList, 0); break;
    case 0x2b: ok = Fn8f7b00(pList, 1); break;
    case 0x2c: ok = Fn8f7b00(pList, 2); break;
    case 0x2d: ok = Fn8f7b00(pList, 3); break;
    case 0x30: ok = Fn8f7b70(pList); break;
    case 0x31: ok = Fn8f7c30(pList, 0); break;
    case 0x32: ok = Fn8f7c30(pList, 1); break;
    case 0x33: ok = Fn8f7c30(pList, 2); break;
    case 0x34: ok = Fn8f7c30(pList, 3); break;
    case 0x35: ok = Fn8f7c30(pList, 4); break;
    case 0x36: ok = ParseBorderStyle(pList); break;
    case 0x37: ok = ParseBoxHeight(pList); break;
    case 0x38: ok = Fn8f7ff0(pList); break;
    case 0x39: ok = Fn8f8060(pList); break;
    case 0x3b: ok = Fn8f80d0(pList); break;
    case 0x3c: ok = Fn8f8140(pList); break;
    case 0x3d: ok = ParseListStyleImage(pList); break;
    case 0x3e: ok = ParseListStylePosition(pList); break;
    case 0x3f: ok = ParseListStyle(pList); break;
    case 0x40: ok = ParsePosition(pList); break;
    case 0x41: ok = ParseBoxEdge(pList, 0); break;
    case 0x42: ok = ParseBoxEdge(pList, 1); break;
    case 0x43: ok = ParseBoxEdge(pList, 2); break;
    case 0x44: ok = ParseBoxEdge(pList, 3); break;
    case 0x47: ok = Fn8f4b80(pList); break;
    case 0x46: ok = Fn8f4da0(pList); break;
    case 0x48: ok = ParseBorderSpacing(pList); break;
    case 0x4e: ok = ParseDirection(pList); break;
    case 0x05: ok = ParseFontSmooth(pList); break;
    case 0x16: ok = ParseTextOverflow(pList); break;
    case 0x45:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4f:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
        Error(0x23b0023);
        Fn8f42d0();
        return false;
    default:
        Error(0x23b0021);
        Fn8f42d0();
        return false;
    }
    if (!ok) {
        Error(0x23b0022);
        Fn8f42d0();
        return false;
    }
    SkipSpace();
    return true;
}

// =======================================================================================
// @ 0x008f8cb0 CSSParser::ParsePropertyByID
// Builds a parser over one property's text and parses that single property value.
bool CSSParser::ParsePropertyByID(int propID, wchar16* pSource, StackAllocator* pAllocator,
                                  PropertyList* pList, Units units, void* pErrorListener) {
    CSSParser parser;
    parser.mpSourceURI = 0;
    parser.mReader.Fn8f38b0(pSource);
    parser.mTokenValue.mpBegin = gEmptyString;
    parser.mTokenValue.mpEnd = gEmptyString;
    parser.mTokenValue.mpCapacity = &gEmptyStringEnd;
    parser.mConvertedText.mpBegin = gEmptyString;
    parser.mConvertedText.mpEnd = gEmptyString;
    parser.mConvertedText.mpCapacity = &gEmptyStringEnd;
    parser.mDefaultUnits = units;
    parser.mToken = 0;
    parser.mTokenLine = 0;
    parser.mTokenLineStart = 0;
    parser.mTokenPos = 0;
    parser.mAllocator = pAllocator;
    parser.mpErrorListener = pErrorListener;
    parser.Advance();
    bool result = parser.ParsePropertyValue(propID, pList);
    Fn8e2ed0(&parser);
    return result;
}

// =======================================================================================
// @ 0x008f8d50 CSSParser::ParseProperty
// Parses "name: value" -- looks the name up in the property table and dispatches.
bool CSSParser::ParseProperty(PropertyList* pList) {
    int propID;
    SkipSpace();
    if (!MatchSymbol(gPropertyTable, &propID)) {
        if (mToken == 3) {
            Error(0x23b0021);
            return false;
        }
        Fn8f42d0();
        Error(0x23b0021);
        return false;
    }
    SkipSpace();
    if (mToken == 9) {
        mTokenValue.swap(mReader.mMatchText);
        Advance();
        return ParsePropertyValue(propID, pList);
    }
    Fn8f42d0();
    return true;
}

// =======================================================================================
// @ 0x008f8e00 CSSParser::ParsePropertyCollection
// Parses "{ name: value; ... }" into pRule's two lists (normal and !important).
bool CSSParser::ParsePropertyCollection(void* pRule) {
    Property** ppHeads = (Property**)pRule;
    SkipSpace();
    if (mToken == 0x0d) {  // TokenOpenBrace
        mTokenValue.swap(mReader.mMatchText);
        Advance();
        for (;;) {
            while (mToken == 2) {  // TokenWS
                mTokenValue.Empty();
                Advance();
            }
            if (mToken == 0x0e) {  // TokenCloseBrace
                mTokenValue.swap(mReader.mMatchText);
                Advance();
                return true;
            }
            PropertyList list;
            int sep = 0;
            ParseProperty(&list);
            if (mToken == 8) {  // TokenExclamation
                mTokenValue.swap(mReader.mMatchText);
                Advance();
                if (mToken == 3 && wcscmp((const wchar16*)gImportant, mReader.mMatchText.mpBegin) == 0) {
                    Advance();
                    sep = 1;
                }
            }
            if (list.mpFirst != 0) {
                Property* p = list.mpFirst;
                while (p->mpNext != 0)
                    p = p->mpNext;
                p->mpNext = ppHeads[sep];
                ppHeads[sep] = list.mpFirst;
            }
            while (mToken == 2) {
                mTokenValue.Empty();
                Advance();
            }
            if (mToken != 0x0a) {  // TokenSemicolon
                if (Fn8f4360(0x0e))
                    return true;
                Error(0x23b000b);
                return false;
            }
            mTokenValue.swap(mReader.mMatchText);
            Advance();
        }
    } else {
        Error(0x23b000c);
        return false;
    }
}

// =======================================================================================
// @ 0x008f9000 CSSParser::ParsePropertyCollectionFrom
// Builds a parser over a whole declaration block and parses it into ppHeads[0/1].
bool CSSParser::ParsePropertyCollectionFrom(wchar16* pSource, StackAllocator* pAllocator,
                                            Property** ppHeads, void* pErrorListener) {
    CSSParser parser;
    parser.mpSourceURI = 0;
    parser.mReader.Fn8f38b0(pSource);
    void* gs = (void*)gEmptyString;
    void* ge = (void*)&gEmptyStringEnd;
    parser.mTokenValue.mpBegin = (wchar16*)gs;
    parser.mTokenValue.mpEnd = (wchar16*)gs;
    parser.mConvertedText.mpBegin = (wchar16*)gs;
    parser.mConvertedText.mpEnd = (wchar16*)gs;
    parser.mTokenValue.mpCapacity = (wchar16*)ge;
    parser.mConvertedText.mpCapacity = (wchar16*)ge;
    parser.mToken = 0;
    parser.mTokenLine = 0;
    parser.mTokenLineStart = 0;
    parser.mTokenPos = 0;
    parser.mAllocator = pAllocator;
    parser.mDefaultUnits = Unit_Number;
    parser.mpErrorListener = pErrorListener;
    parser.Advance();
    for (;;) {
        if (parser.mToken == 0)
            break;
        if (parser.mToken == 1) {
            Fn8e2ed0(&parser);
            return false;
        }
        while (parser.mToken == 2) {
            parser.mTokenValue.Empty();
            parser.Advance();
        }
        PropertyList list;
        int sep = 0;
        parser.ParseProperty(&list);
        if (parser.mToken == 8) {
            parser.mTokenValue.swap(parser.mReader.mMatchText);
            parser.Advance();
            if (parser.mToken == 3 &&
                wcscmp((const wchar16*)gImportant, parser.mReader.mMatchText.mpBegin) == 0) {
                parser.Advance();
                sep = 1;
            }
        }
        if (list.mpFirst != 0) {
            Property* p = list.mpFirst;
            while (p->mpNext != 0)
                p = p->mpNext;
            p->mpNext = ppHeads[sep];
            ppHeads[sep] = list.mpFirst;
        }
        while (parser.mToken == 2) {
            parser.mTokenValue.Empty();
            parser.Advance();
        }
        if (parser.mToken != 0x0a)
            break;
        parser.mTokenValue.swap(parser.mReader.mMatchText);
        parser.Advance();
    }
    Fn8e2ed0(&parser);
    return true;
}

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
