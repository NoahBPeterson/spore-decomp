// Slice s008f55f0 -- EA::XHTML::Style::CSSParser color and selector parsing (SporeApp.exe).
//
//  0x008f55f0 CSSParser::MatchColor          -- #rgb/#rgba/#rrggbb/#rrggbbaa or rgb(r,g,b) or a color keyword
//  0x008f5960 CSSParser::ParseSimpleSelector -- `ident` or `*`, followed by #id, .class, :pseudo, [attr...]
//  0x008f5f70 CSSParser::ParseSelector       -- simple selectors joined by ' ', '>' and '+'
//  0x008f61f0 CSSParser::ParseSelectorList   -- comma separated selectors -> stylesheet rule nodes
//  0x008f6420 CSSParser::ParseFontWeight     -- <number> | bold/bolder/lighter keywords
//  0x008f64f0 CSSParser::ParseFontSize       -- <length> | size keywords | larger/smaller
//
// Retail layouts (2008 PDB names/offsets agree around here):
//   CSSParser { mpSourceURI +0, CharStream mReader +4 (mScanPos +4, mScanEnd +8, mMatchText +0x14),
//   mToken +0x28, mTokenValue +0x38, mpErrorListener +0x48, mAllocator +0x4c }.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// msvcr90 imports (calls go through the .rdata IAT slots at 0x13cc514 / 0x13cc4a8).
extern "C" __declspec(dllimport) double __cdecl wcstod(const wchar_t* s, wchar_t** end);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t* s, wchar_t** end, int base);

namespace EA {
namespace Allocator {
class StackAllocator {  // size 0x24
public:
    bool AllocateNewBlock(unsigned int nSize);  // 0x00928ba0
    unsigned int mnDefaultBlockSize;            // +0x0
    void* mpCurrentBlock;                       // +0x4
    char* mpCurrentBlockEnd;                    // +0x8
    char* mpCurrentObjectBegin;                 // +0xc
    char* mpCurrentObjectEnd;                   // +0x10
};
}  // namespace Allocator
}  // namespace EA

// Allocates from the parser's stack allocator, 8-byte granular (0x008e2540; sometimes inlined).
inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator* a) {  // 0x008e2540
    nSize = (nSize + 7) & ~7u;
    if ((int)(a->mpCurrentBlockEnd - a->mpCurrentObjectBegin - nSize) < 0) {
        if (!a->AllocateNewBlock(nSize))
            return 0;
    }
    char* p = a->mpCurrentObjectBegin;
    a->mpCurrentObjectBegin = p + nSize;
    a->mpCurrentObjectEnd = a->mpCurrentObjectBegin;
    return p;
}

namespace EA {
namespace XHTML {
namespace Style {

using EA::Allocator::StackAllocator;

enum CSSToken {  // only the tokens used here
    TokenWS = 2, TokenIdent = 3, TokenNumber = 4, TokenString = 5, TokenPound = 6, TokenColon = 9,
    TokenOpenParen = 0xb, TokenCloseParen = 0xc, TokenOpenBracket = 0xf, TokenCloseBracket = 0x10,
    TokenEquals = 0x11, TokenDot = 0x12, TokenComma = 0x13, TokenPlus = 0x14, TokenGreater = 0x15,
    TokenStar = 0x16, TokenPercent = 0x18, TokenIncludes = 0x19, TokenDashMatch = 0x1a
};

struct String {  // eastl::basic_string<wchar_t, eastl::allocator>, size 0x10
    wchar_t* mpBegin;     // +0x0
    wchar_t* mpEnd;       // +0x4
    wchar_t* mpCapacity;  // +0x8
    void* mpAllocName;    // +0xc
    void push_back(wchar_t c);  // 0x004f6510
    void Empty() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    void swap(String& x) {
        wchar_t* t;
        t = mpBegin; mpBegin = x.mpBegin; x.mpBegin = t;
        t = mpEnd; mpEnd = x.mpEnd; x.mpEnd = t;
        t = mpCapacity; mpCapacity = x.mpCapacity; x.mpCapacity = t;
    }
};

struct Reader {  // CSSTokenReader, size 0x24
    wchar_t* mScanPos;   // +0x0
    wchar_t* mScanEnd;   // +0x4
    int mLineBegin;      // +0x8
    int mCurrentLine;    // +0xc
    String mMatchText;   // +0x10
    int mResult;         // +0x20
    bool MatchEscape();  // 0x008f3a80
};

// Tracks the one-time initialisation of three function-local statics that the inlined name scan holds.
struct Once {
    Once() {}
};

__forceinline void NameScanStatics() {
    static Once s1;
    static Once s2;
    static Once s3;
}

class Selector {  // base of every selector node, size 0x8
public:
    Selector() : mpNext(0) {}
    virtual ~Selector() {}          // vtable +0x0
    virtual void Matches() {}       // vtable +0x4
    virtual int GetLength() { return 0; }  // vtable +0x8, length of the selector text
    Selector* mpNext;  // +0x4
};

class TypeSelector : public Selector {  // vtable 0x014399dc
public:
    TypeSelector(const wchar_t* name) : mName(name) {}
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
};
class IdSelector : public Selector {  // vtable 0x014399f4
public:
    IdSelector(const wchar_t* name) : mName(name) {}
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
};
class PseudoSelector : public Selector {  // vtable 0x01439a00
public:
    PseudoSelector(int kind) : mKind(kind) {}
    virtual void Matches() {}
    int mKind;  // +0x8
};
class AttrExistsSelector : public Selector {  // vtable 0x01439a24
public:
    AttrExistsSelector(const wchar_t* name) : mName(name) {}
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
};
class ClassSelector : public Selector {  // vtable 0x014399e8, caches the length of the name
public:
    __forceinline ClassSelector(const wchar_t* name) : mName(name) {
        const wchar_t* p = name;
        if (p) {
            while (*p++) {}
            mLength = (int)(p - (name + 1));
        } else {
            mLength = -1;
        }
    }
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
    int mLength;           // +0xc
};
// These three have their constructors out of line (0x008f2420 / 0x008f2440 / 0x008f24a0).
class AttrEqualsSelector : public Selector {  // vtable 0x01439a30
public:
    AttrEqualsSelector(const wchar_t* name, const wchar_t* value);  // 0x008f2420
    virtual void Matches() {}
    const wchar_t* mName;
    const wchar_t* mValue;
};
class AttrIncludesSelector : public Selector {  // vtable 0x01439a3c
public:
    AttrIncludesSelector(const wchar_t* name, const wchar_t* value);  // 0x008f2440
    virtual void Matches() {}
    const wchar_t* mName;
    const wchar_t* mValue;
    int mValueLen;
};
class AttrDashSelector : public Selector {  // vtable 0x01439a48
public:
    AttrDashSelector(const wchar_t* name, const wchar_t* value);  // 0x008f24a0
    virtual void Matches() {}
    const wchar_t* mName;
    const wchar_t* mValue;
    int mValueLen;
};

class SelectorList { public:  // head/tail of a singly linked node list
    SelectorList() : mpFirst(0), mpLast(0) {}
    Selector* mpFirst;  // +0x0
    Selector* mpLast;   // +0x4
    void swap(SelectorList& o) {
        Selector* t = mpFirst;
        mpFirst = o.mpFirst;
        o.mpFirst = t;
        t = mpLast;
        mpLast = o.mpLast;
        o.mpLast = t;
    }
    void Append(Selector* p);  // 0x008f24f0
    void AppendInline(Selector* p) {
        if (mpLast) {
            mpLast->mpNext = p;
            mpLast = p;
        } else {
            mpFirst = p;
            mpLast = p;
        }
    }
};

// Combinator nodes built by ParseSelector: the head of the selector chain parsed so far sits at +0x8.
class ChildSelector : public Selector {  // vtable 0x01439a18, '>' combinator
public:
    ChildSelector(Selector* pChild) : mChild(pChild) {}
    virtual void Matches() {}
    Selector* mChild;  // +0x8
};
class DescendantSelector : public Selector {  // vtable 0x01439a0c, ' ' and '+' combinators
public:
    DescendantSelector(Selector* pChild) : mChild(pChild) {}
    virtual void Matches() {}
    Selector* mChild;  // +0x8
};

// ---------------------------------------------------------------------------
// Property list side of the parser (the font weight / font size parsers).
// ---------------------------------------------------------------------------
struct Length {
    float mValue;  // +0x0
    int   mUnits;  // +0x4
};

class Property {  // has a vtable; +0x4 is the list link
public:
    virtual void Apply(void* pState);  // slot 0
    Property* mpNext;                  // +0x4 (set by PropertyList::Add)
};

class PropertyList {
public:
    void Add(Property* p) {
        p->mpNext = mpFirst;
        mpFirst = p;
    }
    Property* mpFirst;  // +0x0
};

// The 16-byte {pfn, adjustor, vtordisp, vbtable} image of a pointer to a StyleState member
// that every CreatePropertyFunc<T> call site materialises on the stack.
struct Setter {
    Setter(uint32_t fn) {
        mWords[0] = fn;
        mWords[1] = 0;
        mWords[2] = 0;
        mWords[3] = 0;
    }
    uint32_t mWords[4];
};

// 8-byte head node of one selector group (zeroed on allocation)
class SelectorGroup {
public:
    SelectorGroup() : mpField0(0), mpField4(0) {}
    void* mpField0;  // +0x0
    void* mpField4;  // +0x4
};

// 16-byte stylesheet rule: selector chain + its group + combined selector text length
class RuleNode {
public:
    RuleNode(Selector* pSelector, SelectorGroup* pGroup)
        : mpNext(0), mpSelector(pSelector), mpGroup(pGroup), mLength(0) {}
    void* mpNext;          // +0x0 (linked by Stylesheet::AppendNode)
    Selector* mpSelector;  // +0x4
    SelectorGroup* mpGroup; // +0x8
    int mLength;           // +0xc
};

class Stylesheet {
public:
    void AppendNode(void* pNode);  // 0x008f9bf0
};

class CSSParser {
public:
    bool MatchColor(unsigned* pColor);              // 0x008f55f0
    bool ParseSimpleSelector(SelectorList* pList);  // 0x008f5960
    bool ParseSelector(SelectorList* pList);        // 0x008f5f70
    void* ParseSelectorList(Stylesheet* pSheet);    // 0x008f61f0
    bool ParseFontWeight(PropertyList* pList);      // 0x008f6420
    bool ParseFontSize(PropertyList* pList);        // 0x008f64f0

private:
    void Advance();                                 // 0x008f3d90
    wchar_t* TokenValue();                          // 0x008f2f80
    bool SkipSpace();                               // 0x008f4290
    bool MatchToken(int token);                     // 0x008f4360
    bool MatchKeyword(const wchar_t* pKeyword);     // 0x008f43a0
    void Error(unsigned int code);                  // 0x008f2f10
    void SkipRestOfRule();                          // 0x008f4320
    bool MatchSymbol(const void* pTable, int* pValue);  // 0x008f5200
    bool MatchSymbolPseudo(const void* pTable, unsigned* pValue);    // 0x008f51a0
    bool MatchSymbolWeight(const void* pTable, unsigned* pValue);    // 0x008f5320
    bool MatchSymbolFontSize(const void* pTable, float* pValue);     // 0x008f5380
    bool MatchLength(Length* pLength);                               // 0x008f5560
    void Consume() {
        mTokenValue.swap(mReader.mMatchText);
        Advance();
    }

    wchar_t* mpSourceURI;      // +0x00
    Reader mReader;            // +0x04
    int mToken;                // +0x28
    int mTokenLine;            // +0x2c
    unsigned int mTokenLineStart;  // +0x30
    unsigned int mTokenPos;    // +0x34
    String mTokenValue;        // +0x38
    void* mpErrorListener;     // +0x48
    StackAllocator* mAllocator;  // +0x4c
};

extern const char gPseudoTable[];        // 0x0154d7a8  (ParseSimpleSelector's :pseudo table)
extern const char gPseudoClassTable[];   // 0x0154d328  (MatchColor's PseudoClass keyword table)
extern const char gFontWeightTable[];    // 0x0154d7f0  ("bold"/"bolder"/"lighter"/...)
extern const char gFontSizeTable[];      // 0x0154d810  size keyword -> float
extern const float kf255;                // 0x013f2100  255.0f
extern const float kPercentScale;        // 0x0142ef14  2.55f

// Property builders (out-of-line instantiations of CreatePropertyFunc<T>).
Property* CreatePropertyFunc_f(StackAllocator* a, Setter s, float value);          // 0x008f3020
Property* CreatePropertyFunc_u(StackAllocator* a, Setter s, unsigned value);       // 0x008f33a0
Property* CreatePropertyFunc_L(StackAllocator* a, Setter s, Length value);         // 0x008f3090
Property* CreatePropertyFunc_v(StackAllocator* a, Setter s);                       // 0x008f2550
unsigned MakeColor(unsigned a, unsigned r, unsigned g, unsigned b);                // 0x008f2ce0

// CSSParser::ParseSimpleSelector @ 0x008f5960
bool CSSParser::ParseSimpleSelector(SelectorList* pList) {
    bool bStar = false;
    if (mToken == TokenIdent) {
        mTokenValue.swap(mReader.mMatchText);
        Advance();
        pList->AppendInline(new (mAllocator) TypeSelector(TokenValue()));
    } else if (mToken == TokenStar) {
        Consume();
        bStar = true;
    }

    for (;;) {
        if (mToken == TokenPound) {
            NameScanStatics();
            // MatchName: collect name characters (and escapes) into mMatchText
            if (mReader.mMatchText.mpBegin != mReader.mMatchText.mpEnd) {
                *mReader.mMatchText.mpBegin = 0;
                mReader.mMatchText.mpEnd = mReader.mMatchText.mpBegin;
            }
            do {
                while (mReader.mScanPos < mReader.mScanEnd) {
                    unsigned int c = (unsigned short)*mReader.mScanPos;
                    if (!(c - 0x61 < 0x1a || c - 0x41 < 0x1a || c == 0x5f || c - 0x30 < 10 || c - 0xa1 < 0x5f ||
                          c == 0x2d))
                        break;
                    mReader.mMatchText.push_back((wchar_t)c);
                    mReader.mScanPos += 1;
                }
            } while (mReader.MatchEscape());
            if ((mReader.mMatchText.mpEnd - mReader.mMatchText.mpBegin) != 0) {
                mTokenValue.swap(mReader.mMatchText);
                pList->AppendInline(new (mAllocator) IdSelector(TokenValue()));
                Advance();
            } else {
                Error(0x23b0007);
                Advance();
            }
        } else if (mToken == TokenDot) {
            Consume();
            if (mToken == TokenIdent) {
                Consume();
                pList->AppendInline(new (mAllocator) ClassSelector(TokenValue()));
            } else {
                Error(0x23b0007);
            }
        } else if (mToken == TokenColon) {
            Consume();
            int kind;
            if (MatchSymbol(gPseudoTable, &kind))
                pList->AppendInline(new (mAllocator) PseudoSelector(kind));
            else
                Error(0x23b0009);
        } else if (mToken == TokenOpenBracket) {
            Consume();
            SkipSpace();
            if (MatchToken(TokenIdent)) {
                wchar_t* name = TokenValue();
                SkipSpace();
                Selector* node;
                if (MatchToken(TokenEquals)) {
                    SkipSpace();
                    if (!MatchToken(TokenIdent) && !MatchToken(TokenString)) {
                        Error(0x23b0008);
                        goto closeBracket;
                    }
                    node = new (mAllocator) AttrEqualsSelector(name, TokenValue());
                } else if (MatchToken(TokenIncludes)) {
                    SkipSpace();
                    if (!MatchToken(TokenIdent) && !MatchToken(TokenString)) {
                        Error(0x23b0008);
                        goto closeBracket;
                    }
                    node = new (mAllocator) AttrIncludesSelector(name, TokenValue());
                } else if (MatchToken(TokenDashMatch)) {
                    SkipSpace();
                    if (!MatchToken(TokenIdent) && !MatchToken(TokenString)) {
                        Error(0x23b0008);
                        goto closeBracket;
                    }
                    node = new (mAllocator) AttrDashSelector(name, TokenValue());
                } else {
                    node = new (mAllocator) AttrExistsSelector(name);
                }
                pList->Append(node);
            }
        closeBracket:
            SkipSpace();
            if (!MatchToken(TokenCloseBracket))
                Error(0x23b0004);
        } else {
            break;
        }
    }
    if (!bStar && pList->mpFirst == 0)
        return false;
    return true;
}

// Two function-local statics held by the inlined hex scanner of MatchColor: retail tests and sets
// guard bits 0 and 1 of one dword (0x01667b0c) before scanning.
__forceinline void ColorStatics() {
    static Once s1;
    static Once s2;
}

// Clamp one rgb() channel into 0..255 before the byte conversion.
static __forceinline float ClampChannel(float v) {
    if (v < 0.0f)
        return 0.0f;
    if (v > kf255)
        return kf255;
    return v;
}

// ---------------------------------------------------------------------------
// 0x008f55f0  CSSParser::MatchColor -- #rgb / #rgba / #rrggbb / #rrggbbaa, rgb(r,g,b) or a keyword
// ---------------------------------------------------------------------------
// @ 0x008f55f0
bool CSSParser::MatchColor(unsigned* pColor) {
    if (mToken == TokenPound) {
        ColorStatics();
        mReader.mMatchText.Empty();
        int nDigits = 0;
        do {
            if (mReader.mScanPos >= mReader.mScanEnd)
                break;
            wchar_t ch = *mReader.mScanPos;
            if (ch - L'0' <= 9 || ch - L'a' <= 5 || ch - L'A' <= 5) {
                mReader.mMatchText.push_back(ch);
                mReader.mScanPos += 1;
                nDigits++;
            } else {
                break;
            }
        } while (nDigits < 6);
        unsigned long value = wcstoul(mReader.mMatchText.mpBegin, 0, 16);
        int nChars = (int)(mReader.mMatchText.mpEnd - mReader.mMatchText.mpBegin);
        switch (nChars) {
        case 3:
            *pColor = ((((((value & 0xf00) << 4) + (value & 0xf0)) << 4) + (value & 0xf)) * 0x11) | 0xff000000;
            break;
        case 4:
            *pColor = (((((((value & 0xf000) << 4) + (value & 0xf00)) << 4) + (value & 0xf0)) << 4) +
                       (value & 0xf)) * 0x11;
            break;
        case 6:
            *pColor = value | 0xff000000;
            break;
        case 8:
            break;
        default:
            Error(0x23b0003);
            Advance();
            return false;
        }
        Advance();
        return true;
    }

    if (!MatchKeyword(L"rgb"))
        return MatchSymbolPseudo(gPseudoClassTable, pColor);

    if (!MatchToken(TokenOpenParen)) {
        Error(0x23b0003);
        return false;
    }

    float channels[3];
    int i = 0;
    do {
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
        if (mToken == TokenNumber) {
            float v = (float)wcstod(mReader.mMatchText.mpBegin, 0);
            Advance();
            if (mToken == TokenPercent) {
                mTokenValue.swap(mReader.mMatchText);
                Advance();
                v *= kPercentScale;
            }
            channels[i] = v;
            i++;
            SkipSpace();
            if (mToken != TokenComma)
                break;
            mTokenValue.swap(mReader.mMatchText);
            Advance();
        }
    } while (i < 3);

    SkipSpace();
    if (i != 3 || !MatchToken(TokenCloseParen)) {
        Error(0x23b0003);
        return false;
    }

    *pColor = MakeColor(0xff, (unsigned char)ClampChannel(channels[0]),
                        (unsigned char)ClampChannel(channels[1]),
                        (unsigned char)ClampChannel(channels[2]));
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f5f70  CSSParser::ParseSelector -- simple selectors joined by ' ', '>' and '+'
// ---------------------------------------------------------------------------
// @ 0x008f5f70
bool CSSParser::ParseSelector(SelectorList* pList) {
    SkipSpace();
    if (!ParseSimpleSelector(pList))
        return false;

    for (;;) {
        bool bSpace = false;
        if (mToken == TokenWS) {
            do {
                mTokenValue.Empty();
                Advance();
            } while (mToken == TokenWS);
            bSpace = true;
        }

        if (mToken == TokenGreater) {
            Consume();
            while (mToken == TokenWS) {
                mTokenValue.Empty();
                Advance();
            }
            SelectorList child;
            if (!ParseSimpleSelector(&child))
                goto syntaxError;
            child.swap(*pList);
            pList->AppendInline(new (mAllocator) ChildSelector(child.mpFirst));
            continue;
        }

        if (mToken == TokenPlus) {
            Consume();
            while (mToken == TokenWS) {
                mTokenValue.Empty();
                Advance();
            }
            // The '+' continuation is parsed into its own list in retail and not linked in.
            SelectorList sibling;
            if (!ParseSimpleSelector(&sibling))
                goto syntaxError;
            continue;
        }

        if (!bSpace)
            break;

        SelectorList descendant;
        if (!ParseSimpleSelector(&descendant))
            break;
        descendant.swap(*pList);
        pList->AppendInline(new (mAllocator) DescendantSelector(descendant.mpFirst));
    }
    return true;

syntaxError:
    Error(0x23b000a);
    return false;
}

// ---------------------------------------------------------------------------
// 0x008f61f0  CSSParser::ParseSelectorList -- comma separated selectors into stylesheet rule nodes
// ---------------------------------------------------------------------------
// @ 0x008f61f0
void* CSSParser::ParseSelectorList(Stylesheet* pSheet) {
    SelectorGroup* pGroup = 0;
    SelectorList list;
    if (!ParseSelector(&list))
        return 0;

    for (;;) {
        if (pGroup == 0)
            pGroup = new (mAllocator) SelectorGroup();

        RuleNode* pNode = new (mAllocator) RuleNode(list.mpFirst, pGroup);
        for (Selector* pSel = list.mpFirst; pSel != 0; pSel = pSel->mpNext)
            pNode->mLength += pSel->GetLength();
        pSheet->AppendNode(pNode);

        if (mToken != TokenComma)
            return pGroup;

        Consume();
        list.mpFirst = 0;
        list.mpLast = 0;
        if (!ParseSelector(&list)) {
            Error(0x23b000a);
            SkipRestOfRule();
            return 0;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x008f6420  CSSParser::ParseFontWeight -- <number> | bold / bolder / lighter keywords
// ---------------------------------------------------------------------------
// @ 0x008f6420
bool CSSParser::ParseFontWeight(PropertyList* pList) {
    // The numeric weight and the matched keyword share one stack slot in retail (the float's
    // bits are what CreatePropertyFunc<unsigned> forwards for the keyword case).
    float weight;
    if (mToken == TokenNumber) {
        weight = (float)wcstod(mReader.mMatchText.mpBegin, 0);
        Advance();
        pList->Add(CreatePropertyFunc_f(mAllocator, Setter(0x8f2740), weight));
        return true;
    }
    if (MatchSymbolWeight(gFontWeightTable, (unsigned*)&weight)) {
        unsigned bits = *(const unsigned*)&weight;
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8f2760), bits));
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x008f64f0  CSSParser::ParseFontSize -- <length> | size keywords | larger / smaller
// ---------------------------------------------------------------------------
// @ 0x008f64f0
bool CSSParser::ParseFontSize(PropertyList* pList) {
    Length length = { 0.0f, 0 };
    if (MatchLength(&length)) {
        pList->Add(CreatePropertyFunc_L(mAllocator, Setter(0x8f2780), length));
        return true;
    }

    // The size keyword reuses the length's value slot in retail.
    if (MatchSymbolFontSize(gFontSizeTable, &length.mValue)) {
        unsigned bits = *(const unsigned*)&length.mValue;
        pList->Add(CreatePropertyFunc_u(mAllocator, Setter(0x8fb8a0), bits));
        return true;
    }

    uint32_t setter;
    if (MatchKeyword(L"larger")) {
        setter = 0x8fb9a0;
    } else if (MatchKeyword(L"smaller")) {
        setter = 0x8fb9c0;
    } else {
        return false;
    }
    pList->Add(CreatePropertyFunc_v(mAllocator, Setter(setter)));
    return true;
}

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
