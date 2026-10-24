// src/game/UTFSpore_Win32/CSSParser.cpp -- migrated from slice(s) s008f9220, s008f7690, s008f55f0, s008f3530 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/CSSParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" char    gTokStart[];         // 0x01667b04
extern "C" int     gTokFlag;            // 0x01667b08
extern "C" char    gIdentPred[];        // 0x01439ac4
extern "C" char Fn8f2e10(void* key, void* elem);   // 0x008f2e10
extern "C" char Fn8f2e90(void* elem, void* key);   // 0x008f2e90
extern "C" char Fn8f34d0(void* pred);              // 0x008f34d0
extern "C" char Fn8f3480(void* pred);              // 0x008f3480
extern "C" int  iswctype(unsigned short c, int t);
#include <stddef.h>
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"

// ---- items of slice s008f3530 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
extern "C" wchar16 gEmptyStr[1];        // 0x01667bac
extern "C" wchar16 gEmptyStrEnd;        // 0x01667bae
extern "C" char    gTokStart[];         // 0x01667b04
extern "C" int     gTokFlag;            // 0x01667b08
extern "C" char    gIdentPred[];        // 0x01439ac4
extern "C" char Fn8f2e10(void* key, void* elem);   // 0x008f2e10
extern "C" char Fn8f2e90(void* elem, void* key);   // 0x008f2e90
extern "C" char Fn8f34d0(void* pred);              // 0x008f34d0
extern "C" char Fn8f3480(void* pred);              // 0x008f3480
extern "C" int  iswctype(unsigned short c, int t);
struct WStr2 { void push_back(wchar16 c); };       // 0x004f6510 (eastl wstring)
struct CharStream {
    wchar16* scanPos;   // +0
    wchar16* scanEnd;   // +4
    wchar16* lineBegin; // +8
    int      lineCount; // +0xc

    void* Fn8f38b0(wchar16* s);  // ctor from string
    int   Fn8f35d0(void* pred);  // skip to ';' or '}'
    void  Fn8f36c0();            // consume one EOL
    char  Fn8f3830();            // skip whitespace
    int   Fn8f3640(void* pred);  // skip until pred matches
    int   Fn8f3710(void* pred);  // skip until pred matches
    char  Fn8f39e0(int c);       // match a single wchar
    char  Fn8f3a10(int);         // match a digit
    void  Fn8f3a40(int);         // match digits while in range
    int   Fn8f3d20(int c);       // match a string up to terminator c
    char  Fn8f3a80();            // MatchEscape (stub)
};
struct CSSParser {
    void* Fn8f3900(int p1, wchar16* begin, wchar16* end);
    void* Fn8f3970(int p1, wchar16* begin, int count);
    __declspec(noinline) char Fn8f4290();
    void  Fn8f42d0();
    void  Fn8f4320();
    char  Fn8f4360(int tok);
    char  Fn8f43a0(wchar16* str);
    __declspec(noinline) void Fn8f3d90();            // Advance (stub)
};
// ---- items of slice s008f3530 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" wchar16 gEmptyStr[1];        // 0x01667bac
extern "C" wchar16 gEmptyStrEnd;        // 0x01667bae

// ---- items of slice s008f55f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Allocator {
class StackAllocator_s008f_55f0 {  // size 0x24
public:
    bool AllocateNewBlock(unsigned int nSize);  // 0x00928ba0
    unsigned int mnDefaultBlockSize;            // +0x0
    void* mpCurrentBlock;                       // +0x4
    char* mpCurrentBlockEnd;                    // +0x8
    char* mpCurrentObjectBegin;                 // +0xc
    char* mpCurrentObjectEnd;                   // +0x10
};  // namespace Allocator
}
}
inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator_s008f_55f0* a) {  // 0x008e2540
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
using EA::Allocator::StackAllocator_s008f_55f0;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum CSSToken {  // only the tokens used here
    TokenIdent = 3, TokenColon = 9, TokenCloseBracket = 0x10, TokenEquals = 0x11, TokenDot = 0x12,
    TokenOpenBracket = 0xf, TokenStar = 0x16, TokenString = 5, TokenIncludes = 0x19, TokenDashMatch = 0x1a,
    TokenPound = 6
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct String {  // eastl::basic_string<wchar_t, eastl::allocator>, size 0x10
    wchar_t* mpBegin;     // +0x0
    wchar_t* mpEnd;       // +0x4
    wchar_t* mpCapacity;  // +0x8
    void* mpAllocName;    // +0xc
    void push_back(wchar_t c);  // 0x004f6510
    void swap(String& x) {
        wchar_t* t;
        t = mpBegin; mpBegin = x.mpBegin; x.mpBegin = t;
        t = mpEnd; mpEnd = x.mpEnd; x.mpEnd = t;
        t = mpCapacity; mpCapacity = x.mpCapacity; x.mpCapacity = t;
    }
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Reader {  // CSSTokenReader, size 0x24
    wchar_t* mScanPos;   // +0x0
    wchar_t* mScanEnd;   // +0x4
    int mLineBegin;      // +0x8
    int mCurrentLine;    // +0xc
    String mMatchText;   // +0x10
    int mResult;         // +0x20
    bool MatchEscape();  // 0x008f3a80
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Once {
    Once() {}
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
__forceinline void NameScanStatics() {
    static Once s1;
    static Once s2;
    static Once s3;
}
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Selector {  // base of every selector node, size 0x8
public:
    Selector() : mpNext(0) {}
    virtual void Matches() {}
    Selector* mpNext;  // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class TypeSelector : public Selector {  // vtable 0x014399dc
public:
    TypeSelector(const wchar_t* name) : mName(name) {}
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class IdSelector : public Selector {  // vtable 0x014399f4
public:
    IdSelector(const wchar_t* name) : mName(name) {}
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class PseudoSelector : public Selector {  // vtable 0x01439a00
public:
    PseudoSelector(int kind) : mKind(kind) {}
    virtual void Matches() {}
    int mKind;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrExistsSelector : public Selector {  // vtable 0x01439a24
public:
    AttrExistsSelector(const wchar_t* name) : mName(name) {}
    virtual void Matches() {}
    const wchar_t* mName;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrEqualsSelector : public Selector {  // vtable 0x01439a30
public:
    AttrEqualsSelector(const wchar_t* name, const wchar_t* value);  // 0x008f2420
    virtual void Matches() {}
    const wchar_t* mName;
    const wchar_t* mValue;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrIncludesSelector : public Selector {  // vtable 0x01439a3c
public:
    AttrIncludesSelector(const wchar_t* name, const wchar_t* value);  // 0x008f2440
    virtual void Matches() {}
    const wchar_t* mName;
    const wchar_t* mValue;
    int mValueLen;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrDashSelector : public Selector {  // vtable 0x01439a48
public:
    AttrDashSelector(const wchar_t* name, const wchar_t* value);  // 0x008f24a0
    virtual void Matches() {}
    const wchar_t* mName;
    const wchar_t* mValue;
    int mValueLen;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class SelectorList { public:  // head/tail of a singly linked node list
    Selector* mpFirst;  // +0x0
    Selector* mpLast;   // +0x4
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class CSSParser_s008f_55f0 {
public:
    bool ParseSimpleSelector(SelectorList* pList);  // 0x008f5960

private:
    void Advance();                                 // 0x008f3d90
    wchar_t* TokenValue();                          // 0x008f2f80
    bool SkipSpace();                               // 0x008f4290
    bool MatchToken(int token);                     // 0x008f4360
    void Error(unsigned int code);                  // 0x008f2f10
    bool MatchSymbol(const void* pTable, int* pValue);  // 0x008f5200
    void Consume() {
        mTokenValue.swap(mReader.mMatchText);
        Advance();  // 0x008f3d90 (EA::XHTML::Style::CSSParser::Advance)
    }

    wchar_t* mpSourceURI;      // +0x00
    Reader mReader;            // +0x04
    int mToken;                // +0x28
    int mTokenLine;            // +0x2c
    unsigned int mTokenLineStart;  // +0x30
    unsigned int mTokenPos;    // +0x34
    String mTokenValue;        // +0x38
    void* mpErrorListener;     // +0x48
    StackAllocator_s008f_55f0* mAllocator;  // +0x4c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
extern const char gPseudoTable[];  // 0x0154d7a8
}
}
}
// ---- items of slice s008f55f0 end

// ---- items of slice s008f7690 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Allocator {
class StackAllocator_s008f_7690;  // namespace Allocator
}
}
namespace EA {
namespace XHTML {
namespace Style {
using EA::Allocator::StackAllocator_s008f_7690;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum Units {
    Unit_Number = 0, Unit_Pixels = 1, Unit_Points = 2, Unit_Picas = 3, Unit_Millimeters = 4,
    Unit_Centimeters = 5, Unit_Inches = 6, Unit_Ems = 7, Unit_Exs = 8, Unit_Percentage = 9,
    Unit_Auto = 10, Unit_Inherit = 11, Unit_BorderSize = 12, Unit_Unset = 13
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length {  // size 0x8
    Length(float value, Units units) : mValue(value), mUnits(units) {}
    float mValue;  // +0x0
    Units mUnits;  // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Property {  // size 0x8
public:
    virtual void Apply(StyleState* pState) const;
    Property* mpNext;  // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class PropertyList {  // size 0x4
public:
    void Add(Property* p) {
        p->mpNext = mpFirst;
        mpFirst = p;
    }
    Property* mpFirst;  // +0x0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
template <class T>
Property* CreatePropertyFunc(StackAllocator_s008f_7690* pAllocator, void (StyleState::*pSetter)(T), T arg);
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState {
public:
    void SetHeight(Length len);  // 0x008f2c10: writes mHeight (+0x374 value, +0x378 units)
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct MatchText {  // eastl::basic_string<wchar_t> (only the begin pointer is used here)
    const wchar_t* mpBegin;  // +0x0
    char mRest[0xc];         // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class CSSParser_s008f_7690 {
public:
    bool ParseBoxHeight(PropertyList* pList);  // 0x008f7f20

private:
    void Advance();                     // 0x008f3d90
    bool MatchLength(Length* pLength);  // 0x008f5560

    wchar_t* mpSourceURI;      // +0x00
    char mReaderStream[0x10];  // +0x04 CSSTokenReader: stream, mLineBegin, mCurrentLine
    MatchText mMatchText;      // +0x14 CSSTokenReader::mMatchText
    char mReaderResult[4];     // +0x24 CSSTokenReader::mResult
    int mToken;                // +0x28 CSSToken
    char mTokenRest[0x20];     // +0x2c
    StackAllocator_s008f_7690* mAllocator;  // +0x4c
};
}
}
}
// ---- items of slice s008f7690 end

// ---- items of slice s008f9220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int wcscmp(const wchar_t*, const wchar_t*);
namespace EA {
namespace Allocator {
class StackAllocator_s008f_9220 {  // size 0x24
public:
    StackAllocator_s008f_9220() {}
    StackAllocator_s008f_9220(int, int, int, int, int);    // 0x00928cd0
    ~StackAllocator_s008f_9220() { Reset(); }
    bool AllocateNewBlock(unsigned int nSize);   // 0x00928ba0
    void Init(int, int, int, int, int);          // 0x00928b00
    void Reset();                                // 0x00928dc0
    unsigned int mnDefaultBlockSize;  // +0x0
    void* mpCurrentBlock;             // +0x4
    char* mpCurrentBlockEnd;          // +0x8
    char* mpCurrentObjectBegin;       // +0xc
    char* mpCurrentObjectEnd;         // +0x10
    char _padExtra[0x10];             // +0x14..0x23 (size 0x24)
};  // namespace Allocator
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Node {  // non-polymorphic DOM node (layout only)
public:
    Node* Parent();                                    // 0xff0420
    const wchar_t* GetAttrValue(const wchar_t* name);  // 0x8e45b0
    char _pad0[0x14];
    Node* mpParent;              // +0x14
    char _pad1[0x18];            // +0x18..0x2f
    int mField30;                // +0x30
    const wchar_t* mpTagName;    // +0x34
    const wchar_t* mpId;         // +0x38
    char _pad2[4];               // +0x3c
    void* mpField40;             // +0x40
};  // namespace DOM
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
using EA::XHTML::DOM::Node;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Selector_s008f_9220 {
public:
    Selector_s008f_9220() : mpNext(0) {}
    virtual ~Selector_s008f_9220();
    virtual bool Match(Node* pNode, bool bDeep);
    virtual void* Slot2() { return 0; }
    void Append(Selector_s008f_9220* p);   // 0x008f9fa0
    Selector_s008f_9220* mpNext;           // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StylesheetBase {
public:
    StylesheetBase() : mField4(0) {}
    virtual ~StylesheetBase() {}
    int mField4;  // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Stylesheet_s008f_9220 : public StylesheetBase {
public:
    Stylesheet_s008f_9220(void* p);
    // @ 0x008f9e20 Stylesheet::~Stylesheet (deleting dtor inlined)
    virtual ~Stylesheet_s008f_9220() {
        mAllocator.Reset();
        if (mVecBegin != 0 && mVecBegin != (void**)mField44)
            operator delete(mVecBegin);
    }
    void AddRule(const wchar_t* pName, void* pDecl);  // 0x008f9cd0
    void AddRule2(Selector_s008f_9220* pSel, void* pDecl);       // 0x008f9c20
    void AppendNode(void* pNode);                     // 0x008f9bf0
    void Clear();                                     // 0x008f9ed0
    void InsertRuleAt(void** pos, void** val);  // 0x00899480

    EA::Allocator::StackAllocator_s008f_9220 mAllocator;  // +0x8
    void* mpFirst;      // +0x2c
    void* mpLast;       // +0x30
    void** mVecBegin;   // +0x34
    void** mVecEnd;     // +0x38
    void** mVecCap;     // +0x3c
    void* mField40;     // +0x40
    void* mField44;     // +0x44
    void* mField48;     // +0x48
    char mInline[0x20]; // +0x4c
    void* mField6c;     // +0x6c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct String_s008f_9220 {  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;     // +0x0
    wchar_t* mpEnd;       // +0x4
    wchar_t* mpCapacity;  // +0x8
    void* mpAllocName;    // +0xc
    void swap(String_s008f_9220& x) {
        wchar_t* t;
        t = mpBegin; mpBegin = x.mpBegin; x.mpBegin = t;
        t = mpEnd; mpEnd = x.mpEnd; x.mpEnd = t;
        t = mpCapacity; mpCapacity = x.mpCapacity; x.mpCapacity = t;
    }
    void Empty() {
        if (mpBegin != mpEnd) {
            *mpBegin = L'\0';
            mpEnd = mpBegin;
        }
    }
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Reader_s008f_9220 {  // CSSTokenReader, size 0x24
    wchar_t* mScanPos;    // +0x0
    wchar_t* mScanEnd;    // +0x4
    int mLineBegin;       // +0x8
    int mCurrentLine;     // +0xc
    String_s008f_9220 mMatchText;    // +0x10
    int mResult;          // +0x20
    void SetDefault(void* pStatic);        // 0x008f35d0
    void SetConsume(const wchar_t* pEnd);  // 0x008f3640
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class CSSParser_s008f_9220 {
public:
    bool Parse(Stylesheet_s008f_9220* pSheet);  // 0x008f9220

private:
    void Advance();                                     // 0x008f3d90
    bool SkipSpace();                                   // 0x008f4290
    bool ParseImportURL();                              // 0x008f43f0
    wchar_t* TokenValue();                              // 0x008f2f80
    void Error(unsigned int code);                      // 0x008f2f10
    void* ParseSelectorList(Stylesheet_s008f_9220* pSheet);        // 0x008f61f0
    bool ParsePropertyCollection(void* pSelectorList);  // 0x008f8e00

    wchar_t* mpSourceURI;          // +0x00
    Reader_s008f_9220 mReader;                // +0x04
    int mToken;                    // +0x28
    int mTokenLine;                // +0x2c
    unsigned int mTokenLineStart;  // +0x30
    unsigned int mTokenPos;        // +0x34
    String_s008f_9220 mTokenValue;            // +0x38
    void* mpErrorListener;         // +0x48
    EA::Allocator::StackAllocator_s008f_9220* mAllocator;  // +0x4c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
static char sImportStatic[16];
}
}
}
// ---- items of slice s008f9220 end

// @ 0x008f3530
wchar16** Fn8f3530(char* begin, char* end, void* key)
{
    int n = (int)(end - begin) >> 3;
    if (n <= 0) return (wchar16**)begin;
    do {
        int mid = n >> 1;
        char* elem = begin + mid * 8;
        if (!Fn8f2e10(*(wchar16**)key, elem)) {
            begin = elem + 8;
            n = n + (-1 - mid);
        } else {
            n = mid;
        }
    } while (n > 0);
    return (wchar16**)begin;
}

// @ 0x008f3580
wchar16** Fn8f3580(char* begin, char* end, void* key)
{
    int n = (int)(end - begin) >> 3;
    if (n <= 0) return (wchar16**)begin;
    do {
        int mid = n >> 1;
        char* elem = begin + mid * 8;
        if (Fn8f2e90(elem, *(wchar16**)key)) {
            begin = elem + 8;
            n = n + (-1 - mid);
        } else {
            n = mid;
        }
    } while (n > 0);
    return (wchar16**)begin;
}

// @ 0x008f35d0
int CharStream::Fn8f35d0(void* pred)
{
    (void)pred;
    for (;;) {
        wchar16* p = scanPos;
        short s = (short)*p;
        if (s == 0x3b) return 1;
        if (s == 0x7d) break;
        wchar16* e = scanEnd;
        if (e <= p) return 0;
        if (s == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
        } else {
            if (s == 10) {
                lineCount = lineCount + 1;
                scanPos = p + 1;
                lineBegin = p + 1;
            } else {
                scanPos = p + 1;
            }
        }
    }
    return 1;
}

// @ 0x008f3640
int CharStream::Fn8f3640(void* pred)
{
    for (;;) {
        if (Fn8f34d0(pred) != 0) return 1;
        wchar16* p = scanPos;
        wchar16* e = scanEnd;
        if (e <= p) return 0;
        if (*p == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
        } else {
            if (e <= p) return 0;
            if (*p == 10) {
                lineCount = lineCount + 1;
                scanPos = p + 1;
                lineBegin = p + 1;
            } else {
                if (e <= p) return 0;
                scanPos = p + 1;
            }
        }
    }
}

// @ 0x008f36c0
void CharStream::Fn8f36c0()
{
    for (;;) {
        wchar16* p = scanPos;
        if (scanEnd <= p) return;
        if (*p == 0xd) {
            scanPos = p + 1;
            wchar16* q = scanPos;
            if (q < scanEnd && *q == 10) scanPos = q + 1;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
            return;
        }
        if (*p == 10) {
            lineCount = lineCount + 1;
            scanPos = p + 1;
            lineBegin = p + 1;
            return;
        }
        scanPos = p + 1;
    }
}

// @ 0x008f3710
int CharStream::Fn8f3710(void* pred)
{
    for (;;) {
        if (Fn8f3480(pred) != 0) return 1;
        wchar16* p = scanPos;
        wchar16* e = scanEnd;
        if (e <= p) return 0;
        if (*p == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
        } else {
            if (e <= p) return 0;
            if (*p == 10) {
                lineCount = lineCount + 1;
                scanPos = p + 1;
                lineBegin = p + 1;
            } else {
                if (e <= p) return 0;
                scanPos = p + 1;
            }
        }
    }
}

// @ 0x008f3790
void Fn8f3790(void* out, const void* first, const void* last, const void* key)
{
    (void)first; (void)last;
    *(void**)out = *(void**)key;
    *((void**)out + 1) = *(void**)key;
}

// @ 0x008f3830
char CharStream::Fn8f3830()
{
    char any = 0;
    for (;;) {
        wchar16* p = scanPos;
        wchar16* e = scanEnd;
        if (e <= p) return any;
        if (*p == 0xd) {
            wchar16* q = p + 1;
            scanPos = q;
            if (q < e && *q == 10) scanPos = p + 2;
            lineCount = lineCount + 1;
            lineBegin = scanPos;
            any = 1;
        } else if (*p == 10) {
            lineCount = lineCount + 1;
            scanPos = p + 1;
            lineBegin = p + 1;
            any = 1;
        } else {
            if (iswctype(*p, 8) == 0) return any;
            scanPos = p + 1;
            any = 1;
        }
    }
}

// @ 0x008f38b0
void* CharStream::Fn8f38b0(wchar16* s)
{
    char* c = (char*)this;
    wchar16* e = s;
    while (*e != 0) e++;
    *(void**)(c + 4) = e;
    *(void**)(c + 0) = s;
    *(void**)(c + 8) = s;
    *(int*)(c + 0xc) = 1;
    void* g = (void*)gEmptyStr;
    *(void**)(c + 0x10) = g;
    *(void**)(c + 0x14) = g;
    *(void**)(c + 0x18) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x20) = 0;
    return this;
}

// @ 0x008f3900
void* CSSParser::Fn8f3900(int p1, wchar16* begin, wchar16* end)
{
    char* c = (char*)this;
    *(int*)(c + 0) = 0;
    *(void**)(c + 4) = begin;
    *(void**)(c + 0xc) = begin;
    *(int*)(c + 0x10) = 1;
    *(void**)(c + 8) = end;
    void* ga = (void*)gEmptyStr;
    *(void**)(c + 0x14) = ga;
    *(void**)(c + 0x18) = ga;
    *(void**)(c + 0x1c) = (void*)&gEmptyStrEnd;
    *(int*)(c + 0x24) = 0;
    *(int*)(c + 0x28) = 0;
    *(int*)(c + 0x2c) = 0;
    *(int*)(c + 0x30) = 0;
    *(int*)(c + 0x34) = 0;
    *(void**)(c + 0x40) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x38) = ga;
    *(void**)(c + 0x3c) = ga;
    *(int*)(c + 0x4c) = p1;
    *(int*)(c + 0x48) = 0;
    *(void**)(c + 0x58) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x50) = ga;
    *(void**)(c + 0x54) = ga;
    *(int*)(c + 0x60) = 0;
    return this;
}

// @ 0x008f3970
void* CSSParser::Fn8f3970(int p1, wchar16* begin, int count)
{
    char* c = (char*)this;
    *(int*)(c + 0) = 0;
    *(void**)(c + 4) = begin;
    *(void**)(c + 0xc) = begin;
    *(int*)(c + 0x10) = 1;
    *(void**)(c + 8) = begin + count;
    void* ga = (void*)gEmptyStr;
    *(void**)(c + 0x14) = ga;
    *(void**)(c + 0x18) = ga;
    *(void**)(c + 0x1c) = (void*)&gEmptyStrEnd;
    *(int*)(c + 0x24) = 0;
    *(int*)(c + 0x28) = 0;
    *(int*)(c + 0x2c) = 0;
    *(int*)(c + 0x30) = 0;
    *(int*)(c + 0x34) = 0;
    *(void**)(c + 0x40) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x38) = ga;
    *(void**)(c + 0x3c) = ga;
    *(int*)(c + 0x4c) = p1;
    *(int*)(c + 0x48) = 0;
    *(void**)(c + 0x58) = (void*)&gEmptyStrEnd;
    *(void**)(c + 0x50) = ga;
    *(void**)(c + 0x54) = ga;
    *(int*)(c + 0x60) = 0;
    return this;
}

// @ 0x008f39e0
char CharStream::Fn8f39e0(int c)
{
    if (scanPos < scanEnd) {
        wchar16 ch = *scanPos;
        if (c == (int)ch) {
            ((WStr2*)((char*)this + 0x10))->push_back(ch);
            scanPos = scanPos + 1;
            return 1;
        }
    }
    return 0;
}

// @ 0x008f3a10
char CharStream::Fn8f3a10(int)
{
    if (scanPos < scanEnd) {
        wchar16 ch = *scanPos;
        if ((unsigned)(ch - 0x30) <= 9) {
            ((WStr2*)((char*)this + 0x10))->push_back(ch);
            scanPos = scanPos + 1;
            return 1;
        }
    }
    return 0;
}

// @ 0x008f3a40
void CharStream::Fn8f3a40(int)
{
    if (scanPos < scanEnd) {
        do {
            wchar16 ch = *scanPos;
            if ((unsigned)(ch - 0x30) > 9) break;
            ((WStr2*)((char*)this + 0x10))->push_back(ch);
            scanPos = scanPos + 1;
        } while (scanPos < scanEnd);
    }
}

// @ 0x008f3a80
char CharStream::Fn8f3a80()
{
    return 0;
}

// @ 0x008f3c40
int Fn8f3c40(void* self, int a)
{
    (void)a;
    return *(volatile int*)((char*)self + 0x28);
}

// @ 0x008f3d20
int CharStream::Fn8f3d20(int c)
{
    char* r = (char*)this;
    wchar16* b = *(wchar16**)(r + 0x10);
    if (b != *(wchar16**)(r + 0x14)) {
        *b = 0;
        *(wchar16**)(r + 0x14) = b;
    }
    wchar16 term = (wchar16)c;
    for (;;) {
        wchar16* p = *(wchar16**)(r + 0);
        if (p < *(wchar16**)(r + 4) && *p == term) {
            *(wchar16**)(r + 0) = p + 1;
            return 1;
        }
        if (Fn8f3a80()) continue;
        p = *(wchar16**)(r + 0);
        if (p >= *(wchar16**)(r + 4)) return 0;
        ((WStr2*)(r + 0x10))->push_back(*p);
        *(wchar16**)(r + 0) = p + 1;
    }
}

// @ 0x008f3d90
void CSSParser::Fn8f3d90()
{
    *(volatile int*)((char*)this + 0x28) = *(volatile int*)((char*)this + 0x28);
}

// @ 0x008f4290
char CSSParser::Fn8f4290()
{
    char* c = (char*)this;
    char r = 0;
    if (*(int*)(c + 0x28) == 2) {
        do {
            wchar16* b = *(wchar16**)(c + 0x38);
            if (b != *(wchar16**)(c + 0x3c)) {
                *b = 0;
                *(wchar16**)(c + 0x3c) = b;
            }
            Fn8f3d90();
        } while (*(int*)(c + 0x28) == 2);
        r = 1;
    }
    return r;
}

// @ 0x008f42d0
void CSSParser::Fn8f42d0()
{
    char* c = (char*)this;
    if ((gTokFlag & 1) == 0) gTokFlag = gTokFlag | 1;
    ((CharStream*)(c + 4))->Fn8f35d0(&gTokStart);
    wchar16* p = *(wchar16**)(c + 4);
    if (p < *(wchar16**)(c + 8) && *p == 0x3b) *(void**)(c + 4) = p + 1;
    Fn8f4290();
}

// @ 0x008f4320
void CSSParser::Fn8f4320()
{
    char* c = (char*)this;
    ((CharStream*)(c + 4))->Fn8f3640(&gIdentPred);
    wchar16* p = *(wchar16**)(c + 4);
    if (p < *(wchar16**)(c + 8) && *p == 0x7d) *(void**)(c + 4) = p + 1;
    Fn8f4290();
    Fn8f3d90();
}

// @ 0x008f4360
char CSSParser::Fn8f4360(int tok)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x28) != tok) return 0;
    void* t;
    t = *(void**)(c + 0x38); *(void**)(c + 0x38) = *(void**)(c + 0x14); *(void**)(c + 0x14) = t;
    t = *(void**)(c + 0x3c); *(void**)(c + 0x3c) = *(void**)(c + 0x18); *(void**)(c + 0x18) = t;
    t = *(void**)(c + 0x40); *(void**)(c + 0x40) = *(void**)(c + 0x1c); *(void**)(c + 0x1c) = t;
    Fn8f3d90();
    return 1;
}

// @ 0x008f43a0
char CSSParser::Fn8f43a0(wchar16* str)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x28) != 3) return 0;
    wchar16* q = *(wchar16**)(c + 0x14);
    int r;
    for (;;) {
        wchar16 a = str[0];
        if (a != q[0]) { r = (a < q[0]) ? -1 : 1; break; }
        if (a == 0) { r = 0; break; }
        wchar16 b = str[1];
        if (b != q[1]) { r = (b < q[1]) ? -1 : 1; break; }
        str += 2; q += 2;
        if (b == 0) { r = 0; break; }
    }
    if (r != 0) return 0;
    Fn8f3d90();
    return 1;
}

// @ 0x008f5960
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_55f0::ParseSimpleSelector(SelectorList* pList)
{
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f7f20
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_7690::ParseBoxHeight(PropertyList* pList)
{
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f9220
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_9220::Parse(Stylesheet_s008f_9220* pSheet)
{
    if (mToken == 0)
        Advance();
    SkipSpace();
    for (;;) {
        if (mToken == 0) {
            pSheet->Clear();
            return true;
        }
        if (mToken == 1)
            return false;
        if (mToken == 7) {  // '@'
            mTokenValue.swap(mReader.mMatchText);
            Advance();
            if (mToken != 3 || wcscmp(L"import", mReader.mMatchText.mpBegin) != 0) {
                Error(0x23b0024);
                mReader.SetDefault(sImportStatic);
                if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L';')
                    mReader.mScanPos += 1;
                while (mToken == 2) {
                    mTokenValue.Empty();
                    Advance();
                }
            } else {
                Advance();
                while (mToken == 2) {
                    mTokenValue.Empty();
                    Advance();
                }
                if (!ParseImportURL()) {
                    if (mToken != 5) {
                        Error(0x23b000b);
                        return false;
                    }
                    mTokenValue.swap(mReader.mMatchText);
                    Advance();
                }
                void* v = TokenValue();
                while (mToken == 2) {
                    mTokenValue.Empty();
                    Advance();
                }
                if (mToken == 10) {  // ';'
                    mTokenValue.swap(mReader.mMatchText);
                    Advance();
                    SkipSpace();
                    if (pSheet->mVecEnd < pSheet->mVecCap) {
                        void** p = pSheet->mVecEnd;
                        pSheet->mVecEnd = p + 1;
                        *p = v;
                    } else {
                        pSheet->InsertRuleAt(pSheet->mVecEnd, &v);
                    }
                } else {
                    Error(0x23b000b);
                    mReader.SetDefault(sImportStatic);
                    if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L';')
                        mReader.mScanPos += 1;
                    SkipSpace();
                }
            }
        } else {
            void* pSel = ParseSelectorList(pSheet);
            if (pSel == 0) {
                Error(0x23b000a);
                mReader.SetConsume(L"}");
                if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L'}')
                    mReader.mScanPos += 1;
                while (mToken == 2) {
                    mTokenValue.Empty();
                    Advance();
                }
                Advance();
            } else if (!ParsePropertyCollection(pSel)) {
                mReader.SetConsume(L"}");
                if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L'}')
                    mReader.mScanPos += 1;
                while (mToken == 2) {
                    mTokenValue.Empty();
                    Advance();
                }
                Advance();
            } else {
                while (mToken == 2) {
                    mTokenValue.Empty();
                    Advance();
                }
            }
        }
    }
}
}}}  // namespace EA::XHTML::Style
