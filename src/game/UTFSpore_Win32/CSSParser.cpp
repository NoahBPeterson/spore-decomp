// src/game/UTFSpore_Win32/CSSParser.cpp -- migrated from slice(s) s008f85e0, s008f43f0, s008f2660, s008f16c0, s008f9220, s008f7690, s008f55f0, s008f3530 by tools/migrate/rewrite.py
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
__declspec(dllimport) int __cdecl iswctype(unsigned int ch, unsigned int kind);
#include <stddef.h>
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/Text/Typesetter.h"
#include <math.h>

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
__declspec(dllimport) int __cdecl iswctype(unsigned int ch, unsigned int kind);
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
}
}
}
// ---- items of slice s008f9220 end

// ---- items of slice s008f16c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace XHTML {
namespace Layout {
class PropNodeX {
public:
    uint32_t mVtable;                      // +0x00
    uint32_t mField04;                     // +0x04
    uint32_t mField08;                     // +0x08
    uint32_t mField0c;                     // +0x0c
    int mLength;                           // +0x10

    PropNodeX* F_8f2440(int a, const uint16_t* str);        // 0x008f2440
    PropNodeX* F_8f24a0(int a, const uint16_t* str);        // 0x008f24a0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct ListNodeX {
    uint32_t mField0;                      // +0x00
    uint32_t mField4;                      // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class HeadTailX {
public:
    ListNodeX* mpHead;                     // +0x00
    ListNodeX* mpTail;                     // +0x04

    void F_8f24f0(ListNodeX* node);                         // 0x008f24f0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PoolX {
public:
    uint8_t pad00[0x08];
    int mField08;                          // +0x08
    int mField0c;                          // +0x0c
    int mField10;                          // +0x10
    uint8_t pad14[0x04];

    bool F_928ba0(uint32_t size);                           // 0x00928ba0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PoolNodeX {
public:
    uint32_t mVtable;                      // +0x00
    uint32_t mField04;                     // +0x04
    uint32_t mField08;                     // +0x08
    uint32_t mField0c;                     // +0x0c
    uint32_t mField10;                     // +0x10
    uint32_t mField14;                     // +0x14
    uint32_t mField18;                     // +0x18
    uint32_t mField1c;                     // +0x1c

    void F_8f25b0(int offset);             // 0x008f25b0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
PoolNodeX* FUN_008f2550(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
PoolNodeX* FUN_008f25f0(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);
}
}
}
// ---- items of slice s008f16c0 end

// ---- items of slice s008f2660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk
__declspec(dllimport) int __cdecl tolower(int);
namespace EA {
namespace Allocator {
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
};  // namespace Allocator
}
}
namespace EA {
namespace XHTML {
namespace Style {
extern uint32_t AppendWide(void* dst, const wchar_t* src, uint32_t maxChars);
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
extern const uint8_t gEdgeMap[];
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length_s008f_2660 {
    float mValue;   // +0
    int   mUnits;   // +4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Edge {           // size 0x20
    Length_s008f_2660       mMargin;       // +0x0
    Length_s008f_2660       mPadding;      // +0x8
    Length_s008f_2660       mBorder;       // +0x10
    int          mBorderStyle;  // +0x18
    unsigned int mBorderColor;  // +0x1c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState_s008f_2660 {
public:
    void SetFontFamilies(const wchar_t** names, int count);           // 0x008f26b0
    void SetFontWeight(float weight);                                 // 0x008f2740
    void SetFontWeight(int weight);                                   // 0x008f2760
    void SetFontSize(Length_s008f_2660 size);                                    // 0x008f2780
    void SetStretch(float stretch);                                   // 0x008f27a0
    void SetFontSmoothThresh(Length_s008f_2660 thresh);                          // 0x008f27c0
    void SetBackgroundColor(unsigned int color);                      // 0x008f27f0
    void SetDecorationFlags(unsigned short set, unsigned short mask); // 0x008f28c0
    void SetVerticalAlign(Length_s008f_2660 align);                              // 0x008f2910
    void SetMargin(Length_s008f_2660 len, int edge);                             // 0x008f29b0
    void SetPadding(Length_s008f_2660 len, int edge);                            // 0x008f2a20
    void SetBorderWidth(Length_s008f_2660 len, int edge);                        // 0x008f2a90
    void SetBorderColor(unsigned int color, int edge);                // 0x008f2b00
    void SetBorderStyle(int style, int edge);                         // 0x008f2b40
    void SetBorderSpacing(Length_s008f_2660 len);                                // 0x008f2bc0
    void SetBoxOffset(Length_s008f_2660 len, int index);                         // 0x008f2c60

    StyleState_s008f_2660* mpBase;         // +0x0
    void*       mpPage;         // +0x4
    bool        mbFontChanged;  // +0x8
    TextStyle   mTextStyle;     // +0xc
    Length_s008f_2660      mFontSize;      // +0x284
    unsigned int mFgColor;      // +0x28c
    Length_s008f_2660      mLineHeight;    // +0x290
    Length_s008f_2660      mFontSmoothThresh;   // +0x298
    wchar_t*    mpBackgroundImage;   // +0x2a0
    int         mBackgroundRepeat;   // +0x2a4
    int         mBackgroundAttachment; // +0x2a8
    Length_s008f_2660      mBackgroundPosX;     // +0x2ac
    Length_s008f_2660      mBackgroundPosY;     // +0x2b4
    unsigned int mBgColor;           // +0x2bc
    unsigned int mColorInherited;    // +0x2c0
    Length_s008f_2660      mWordSpacing;        // +0x2c4
    Length_s008f_2660      mLetterSpacing;      // +0x2cc
    Length_s008f_2660      mVerticalAlign;      // +0x2d4
    int         mVerticalAlignKW;    // +0x2dc
    int         mTextTransform;      // +0x2e0
    Length_s008f_2660      mTextIndent;         // +0x2e4
    Edge        mEdges[4];           // +0x2ec
    Length_s008f_2660      mBoxWidth;           // +0x36c
    Length_s008f_2660      mBoxHeight;          // +0x374
    int         mFloat;              // +0x37c
    int         mClearFloat;         // +0x380
    int         mPosition;           // +0x384
    Length_s008f_2660      mBoxOffset[4];       // +0x388
    int         mDisplay;            // +0x3a8
    int         mWhitespaceMode;     // +0x3ac
    int         mListStyleType;      // +0x3b0
    wchar_t*    mListStyleImage;     // +0x3b4
    int         mListStylePosition;  // +0x3b8
    uint32_t    pad3bc[(0x41c - 0x3bc) / 4];
    Length_s008f_2660      mBorderSpacingH;     // +0x41c
    Length_s008f_2660      mBorderSpacingV;     // +0x424
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Property_s008f_2660 { public:
    void*     mpVtable;   // +0
    Property_s008f_2660* mpNext;     // +4
    void*     mpSetter;   // +8
    void*     mpContext;  // +0xc
    void*     mpArg0;     // +0x10
    void*     mpArg1;     // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
extern char gPropVtable[];
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
Property_s008f_2660* CreatePropertyFunc_uint_EdgeIndex(EA::Allocator::StackAllocator_s0092_8b00* a,
                                            void* setter, void* ctx, void* p4, void* p5,
                                            unsigned int value, int edge);
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropFunc_Uint  : Property_s008f_2660 { uint32_t mValue; void Apply(int index); };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropFunc_Float : Property_s008f_2660 { float    mValue; void Apply(int index); };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropFunc_2UShort : Property_s008f_2660 { uint16_t mA; uint16_t mB; void Apply(int index); };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropFunc_3Uint : Property_s008f_2660 { uint32_t mA; uint32_t mB; uint32_t mC; void Apply(int index); };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropFunc_2Uint : Property_s008f_2660 { uint32_t mA; uint32_t mB; void Apply(int index); };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct CharStream_s008f_2660 {
    wchar_t* mpPos;   // +0
    wchar_t* mpEnd;   // +4
    wchar_t NextChar();               // 0x008f2fe0
    bool    MatchChar(unsigned int c);     // 0x008f3000
    bool    CopyWideLine(const wchar_t* src, wchar_t* dst, unsigned int maxLen);  // 0x008f2d10
    bool    MatchAscii(const char* s);    // 0x008f3480
    bool    MatchWide(const wchar_t* s);  // 0x008f34d0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class CSSParser_s008f_2660 {
public:
    wchar_t* TokenValue();                                // 0x008f2f80
    bool SetEdgePropertiesLength(int* list, Length_s008f_2660* values, int mode,
                                 void* p5, void* p6, void* p7, void* p8);   // 0x008f31f0
    bool SetEdgePropertiesUint(int* list, unsigned int* values, int mode,
                               void* p5, void* p6, void* p7, void* p8);     // 0x008f32d0

    uint32_t    pad0[(0x38) / 4];
    wchar_t*    mTokenBegin;   // +0x38
    wchar_t*    mTokenEnd;     // +0x3c
    uint32_t    pad40[(0x4c - 0x40) / 4];
    EA::Allocator::StackAllocator_s0092_8b00* mAllocator;   // +0x4c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
bool WStrLess_KeyElem(const wchar_t* key, const wchar_t** elem);
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
bool WStrLess_ElemKey(const wchar_t** elem, const wchar_t* key);
}
}
}
// ---- items of slice s008f2660 end

// ---- items of slice s008f43f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gFontFamilyVtable[];             // 0x01439a6c
extern const unsigned char gUnitsTable[];    // 0x0154d2e0
__declspec(dllimport) double __cdecl wcstod(const wchar_t* s, wchar_t** end);
namespace EA {
namespace XHTML {
namespace Style {
typedef EA::Allocator::StackAllocator_s0092_8b00 StackAllocator;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
enum CSSToken_s008f_43f0 { TokenWS = 2, TokenIdent_s008f_43f0 = 3, TokenNumber = 4, TokenString_s008f_43f0 = 5,
                TokenOpenParen = 0xb, TokenComma = 0x13, TokenPercent = 0x18 };
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct String_s008f_43f0 {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8

    void Empty()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }

    void swap(String_s008f_43f0& o)
    {
        wchar_t* t;
        t = mpBegin; mpBegin = o.mpBegin; o.mpBegin = t;
        t = mpEnd; mpEnd = o.mpEnd; o.mpEnd = t;
        t = mpCapacity; mpCapacity = o.mpCapacity; o.mpCapacity = t;
    }

    void push_back(wchar_t c);   // 0x004f6510
    void trim();                 // 0x0057eda0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Property_s008f_43f0 { public:
    void*     mpVtable;   // +0
    Property_s008f_43f0* mpNext;     // +4
    void*     mpSetter;   // +8
    void*     mpContext;  // +0xc
    void*     mpArg0;     // +0x10
    void*     mpArg1;     // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropCtx {
    void* mpFn;    // +0
    void* mpCtx;   // +4
    void* mpArg0;  // +8
    void* mpArg1;  // +0xc

    PropCtx(void* fn, void* ctx, void* arg0, void* arg1)
    {
        mpFn = fn; mpCtx = ctx; mpArg0 = arg0; mpArg1 = arg1;
    }
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct PropFontFamily {
    void*           mpVtable;    // +0
    PropFontFamily* mpNext;      // +4
    void*           mpSetter;    // +8
    void*           mpContext;   // +0xc
    void*           mpArg0;      // +0x10
    void*           mpArg1;      // +0x14
    wchar_t*        mNames[8];   // +0x18
    int             mCount;      // +0x38
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length_s008f_43f0 {
    float mValue;   // +0
    int   mUnits;   // +4
};
}
}
}
EA::XHTML::Style::Property_s008f_43f0* CreateURLPropertyFunc(
    EA::Allocator::StackAllocator_s0092_8b00* a, EA::XHTML::Style::PropCtx ctx, void* url);
void EqualRange(void* out, const void* first, const void* last, const void* key);
namespace EA {
namespace XHTML {
namespace Style {
struct Reader_s008f_43f0 {
    wchar_t* mScanPos;     // +0
    wchar_t* mScanEnd;     // +4
    wchar_t* mLineBegin;   // +8
    int      mCurrentLine; // +0xc
    String_s008f_43f0   mMatchText;   // +0x10
    int      mResult;      // +0x1c
    int      mPad20;       // +0x20

    char SkipWhitespace();   // 0x008f3830
    char MatchEscape();      // 0x008f3a80
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class CSSParser_s008f_43f0 {
public:
    // --- external members defined in other translation units ---
    char     SkipSpace();                        // 0x008f4290
    void     Advance();                          // 0x008f3d90
    char     MatchIdent(const wchar_t* p);       // 0x008f43a0
    void     Error(int code);                    // 0x008f2f10
    wchar_t* TokenValue();                       // 0x008f2f80
    void     MatchSymbolUnits(const void* pTable, unsigned int* pOut);  // 0x008f5140

    // --- the functions in this slice ---
    bool MatchURL();                                              // 0x008f43f0
    bool ParseFontFamily(Property_s008f_43f0** pList);                       // 0x008f4600
    bool ParseFontVariant(Property_s008f_43f0** pList);                      // 0x008f47e0
    bool ParseBackgroundImage(Property_s008f_43f0** pList);                  // 0x008f4890
    bool ParseBackgroundAttachment(Property_s008f_43f0** pList);             // 0x008f4930
    bool ParseListStyleImage(Property_s008f_43f0** pList);                   // 0x008f49e0
    bool ParseListStylePosition(Property_s008f_43f0** pList);                // 0x008f4aa0
    bool ParseCounterReset(Property_s008f_43f0** pList);                     // 0x008f4b80
    bool ParseCounterIncrement(Property_s008f_43f0** pList);                 // 0x008f4da0
    bool ParseDirection(Property_s008f_43f0** pList);                        // 0x008f4fc0
    bool ParseTextOverflow(Property_s008f_43f0** pList);                     // 0x008f5080
    bool MatchSymbolBackgroundRepeat(const void* pTable, float* pValue);  // 0x008f53e0
    bool MatchLength(Length_s008f_43f0* p);                                  // 0x008f5560

    // --- fields (absolute offsets from `this`) ---
    int         mPad00;           // +0x00
    Reader_s008f_43f0      mReader;          // +0x04 (size 0x24)
    int         mToken;           // +0x28
    int         mTokenLine;       // +0x2c
    wchar_t*    mTokenLineStart;  // +0x30
    wchar_t*    mTokenPos;        // +0x34
    String_s008f_43f0      mTokenValue;      // +0x38
    int         mPad44;           // +0x44
    void*       mpErrorListener;  // +0x48
    StackAllocator* mAllocator;   // +0x4c
    String_s008f_43f0      mExtra;           // +0x50
    int         mPad5c;           // +0x5c
    int         mDefaultUnits;    // +0x60
};
}
}
}
// ---- items of slice s008f43f0 end

// ---- items of slice s008f85e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const char gPropertyTable[];  // 0x0154d020
namespace EA {
namespace Allocator {
class StackAllocator_s008f_85e0;  // namespace Allocator
}
}
extern "C" wchar16 gEmptyString[1];  // 0x01667bac
extern "C" wchar16 gEmptyStringEnd;  // 0x01667bae
void __fastcall Fn8e2ed0(void* pThis);
namespace EA {
namespace XHTML {
namespace Style {
using EA::Allocator::StackAllocator_s008f_85e0;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
static inline void SwapPtr(wchar16*& a, wchar16*& b) {
    wchar16* t = a; a = b; b = t;
}
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct String_s008f_85e0 {              // size 0x10
    wchar16* mpBegin;        // +0x00
    wchar16* mpEnd;          // +0x04
    wchar16* mpCapacity;     // +0x08
    void* mpAllocName;       // +0x0c
    void swap(String_s008f_85e0& x) {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Property_s008f_85e0 { public:        // size 0x8
    void* mpVptr;        // +0x00
    Property_s008f_85e0* mpNext;    // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class PropertyList_s008f_85e0 {  // size 0x4
public:
    PropertyList_s008f_85e0() : mpFirst(0) {}
    Property_s008f_85e0* mpFirst;  // +0x00
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct CharStream_s008f_85e0 {          // size 0x24
    wchar16* mpScanPos;      // +0x00
    wchar16* mpScanEnd;      // +0x04
    wchar16* mpLineBegin;    // +0x08
    int mLineCount;          // +0x0c
    String_s008f_85e0 mMatchText;       // +0x10
    int mResult;             // +0x20
    void* Fn8f38b0(wchar16* pSource);  // 0x008f38b0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class CSSParser_s008f_85e0 {
public:
    // -- the five functions of this slice -----------------------------------------------
    bool ParsePropertyValue(int propID, PropertyList_s008f_85e0* pList);  // 0x008f85e0
    static bool ParsePropertyByID(int propID, wchar16* pSource, StackAllocator_s008f_85e0* pAllocator,
                                  PropertyList_s008f_85e0* pList, Units units,
                                  void* pErrorListener);  // 0x008f8cb0
    bool ParseProperty(PropertyList_s008f_85e0* pList);              // 0x008f8d50
    bool ParsePropertyCollection(void* pRule);            // 0x008f8e00
    static bool ParsePropertyCollectionFrom(wchar16* pSource, StackAllocator_s008f_85e0* pAllocator,
                                            Property_s008f_85e0** ppHeads,
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
    bool ParseFontFamily(PropertyList_s008f_85e0* pList);          // 0x008f4600
    bool ParseFontVariant(PropertyList_s008f_85e0* pList);         // 0x008f47e0
    bool ParseFontWeight(PropertyList_s008f_85e0* pList);          // 0x008f6420
    bool ParseFontSize(PropertyList_s008f_85e0* pList);            // 0x008f64f0
    bool ParseFontSmooth(PropertyList_s008f_85e0* pList);          // 0x008f8510
    bool ParseFont(PropertyList_s008f_85e0* pList);                // 0x008f66a0
    bool ParseColor(PropertyList_s008f_85e0* pList);               // 0x008f69a0
    bool ParseBackgroundColor(PropertyList_s008f_85e0* pList);     // 0x008f6a00
    bool ParseBackgroundImage(PropertyList_s008f_85e0* pList);     // 0x008f4890
    bool ParseBackgroundRepeat(PropertyList_s008f_85e0* pList);    // 0x008f6a60
    bool ParseBackgroundAttachment(PropertyList_s008f_85e0* pList);  // 0x008f4930
    bool ParseBackgroundPosition(PropertyList_s008f_85e0* pList);  // 0x008f6ad0
    bool ParseBackground(PropertyList_s008f_85e0* pList);          // 0x008f6da0
    bool ParseWordSpacing(PropertyList_s008f_85e0* pList);         // 0x008f6eb0
    bool ParseLetterSpacing(PropertyList_s008f_85e0* pList);       // 0x008f6f50
    bool ParseTextDecoration(PropertyList_s008f_85e0* pList);      // 0x008f6ff0
    bool ParseVerticalAlign(PropertyList_s008f_85e0* pList);       // 0x008f7130
    bool ParseTextIndent(PropertyList_s008f_85e0* pList);          // 0x008f72e0
    bool ParseTextOverflow(PropertyList_s008f_85e0* pList);        // 0x008f5080
    bool ParseLineHeight(PropertyList_s008f_85e0* pList);          // 0x008f7380
    bool ParseMarginEdge(PropertyList_s008f_85e0* pList, int iEdge);   // 0x008f7430
    bool ParseMargin(PropertyList_s008f_85e0* pList);              // 0x008f7500
    bool ParsePaddingEdge(PropertyList_s008f_85e0* pList, int iEdge);  // 0x008f7610
    bool ParsePadding(PropertyList_s008f_85e0* pList);             // 0x008f7690
    bool ParseBorderWidthEdge(PropertyList_s008f_85e0* pList, int iEdge);  // 0x008f7740
    bool ParseBorderWidth(PropertyList_s008f_85e0* pList);         // 0x008f7820
    bool ParseBorderColorEdge(PropertyList_s008f_85e0* pList, int iEdge);  // 0x008f7a00
    bool ParseBorderColor(PropertyList_s008f_85e0* pList);         // 0x008f7a70
    bool ParseBorderStyle(PropertyList_s008f_85e0* pList);         // 0x008f7e50
    bool ParseBoxHeight(PropertyList_s008f_85e0* pList);           // 0x008f7f20
    bool ParseListStyleImage(PropertyList_s008f_85e0* pList);      // 0x008f49e0
    bool ParseListStylePosition(PropertyList_s008f_85e0* pList);   // 0x008f4aa0
    bool ParseListStyle(PropertyList_s008f_85e0* pList);           // 0x008f81b0
    bool ParsePosition(PropertyList_s008f_85e0* pList);            // 0x008f82d0
    bool ParseBoxEdge(PropertyList_s008f_85e0* pList, int iEdge);  // 0x008f8340
    bool ParseBorderSpacing(PropertyList_s008f_85e0* pList);       // 0x008f8400
    bool ParseDirection(PropertyList_s008f_85e0* pList);           // 0x008f4fc0

    bool Fn8f6340(PropertyList_s008f_85e0* pList);                 // 0x008f6340
    bool Fn8f63b0(PropertyList_s008f_85e0* pList);                 // 0x008f63b0
    bool Fn8f6620(PropertyList_s008f_85e0* pList);                 // 0x008f6620
    bool Fn8f7200(PropertyList_s008f_85e0* pList);                 // 0x008f7200
    bool Fn8f7270(PropertyList_s008f_85e0* pList);                 // 0x008f7270
    bool Fn8f7b00(PropertyList_s008f_85e0* pList, int iEdge);      // 0x008f7b00
    bool Fn8f7b70(PropertyList_s008f_85e0* pList);                 // 0x008f7b70
    bool Fn8f7c30(PropertyList_s008f_85e0* pList, int iEdge);      // 0x008f7c30
    bool Fn8f7ff0(PropertyList_s008f_85e0* pList);                 // 0x008f7ff0
    bool Fn8f8060(PropertyList_s008f_85e0* pList);                 // 0x008f8060
    bool Fn8f80d0(PropertyList_s008f_85e0* pList);                 // 0x008f80d0
    bool Fn8f8140(PropertyList_s008f_85e0* pList);                 // 0x008f8140
    bool Fn8f4b80(PropertyList_s008f_85e0* pList);                 // 0x008f4b80
    bool Fn8f4da0(PropertyList_s008f_85e0* pList);                 // 0x008f4da0

    wchar16* mpSourceURI;  // +0x00
    CharStream_s008f_85e0 mReader;    // +0x04
    int mToken;            // +0x28  (CSSToken)
    int mTokenLine;        // +0x2c
    unsigned mTokenLineStart;  // +0x30
    unsigned mTokenPos;        // +0x34
    String_s008f_85e0 mTokenValue;    // +0x38
    void* mpErrorListener;  // +0x48
    StackAllocator_s008f_85e0* mAllocator;  // +0x4c
    String_s008f_85e0 mConvertedText;   // +0x50
    Units mDefaultUnits;     // +0x60
};
}
}
}
// ---- items of slice s008f85e0 end

// @ 0x008f24a0
namespace EA { namespace XHTML { namespace Layout {
PropNodeX* PropNodeX::F_8f24a0(int a, const uint16_t* str)
{
    mField04 = 0;
    mVtable = 0x01439a48;
    mField08 = (uint32_t)a;
    mField0c = (uint32_t)str;
    if (str) {
        const uint16_t* p = str + 1;
        uint16_t c;
        do {
            c = *str;
            ++str;
        } while (c != 0);
        mLength = (int)(str - p);
    } else {
        mLength = -1;
    }
    return this;
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f24f0
namespace EA { namespace XHTML { namespace Layout {
void HeadTailX::F_8f24f0(ListNodeX* node)
{
    if (mpTail) {
        mpTail->mField4 = (uint32_t)node;
        mpTail = node;
    } else {
        mpHead = node;
        mpTail = node;
    }
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f2550
namespace EA { namespace XHTML { namespace Layout {
PoolNodeX* FUN_008f2550(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    if ((pool->mField08 - pool->mField0c) - 0x18 < 0) {
        if (!pool->F_928ba0(0x18))
            return 0;
    }
    PoolNodeX* node = (PoolNodeX*)pool->mField0c;
    pool->mField0c = (int)((char*)node + 0x18);
    pool->mField10 = (int)((char*)node + 0x18);
    if (!node)
        return 0;
    node->mField04 = 0;
    node->mVtable = 0x01439a54;
    node->mField08 = a;
    node->mField0c = b;
    node->mField10 = c;
    node->mField14 = d;
    return node;
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f25b0
namespace EA { namespace XHTML { namespace Layout {
void PoolNodeX::F_8f25b0(int offset)
{
    int index;
    if (mField14 == 0) {
        index = mField0c + offset;
    } else {
        char* entry = *(char**)(mField10 + offset);
        index = *(int*)(entry + mField14) + mField0c + mField10 + offset;
    }
    typedef void (__thiscall *Handler)(void* self, int arg);
    ((Handler)mField08)((void*)index, mField18);
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f25f0
namespace EA { namespace XHTML { namespace Layout {
PoolNodeX* FUN_008f25f0(PoolX* pool, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e)
{
    if ((pool->mField08 - pool->mField0c) - 0x20 < 0) {
        if (!pool->F_928ba0(0x20))
            return 0;
    }
    PoolNodeX* node = (PoolNodeX*)pool->mField0c;
    pool->mField0c = (int)((char*)node + 0x20);
    pool->mField10 = (int)((char*)node + 0x20);
    if (!node)
        return 0;
    node->mField04 = 0;
    node->mVtable = 0x01439a60;
    node->mField08 = a;
    node->mField0c = b;
    node->mField10 = c;
    node->mField14 = d;
    node->mField18 = e;
    return node;
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f2660
namespace EA { namespace XHTML { namespace Style {
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f26b0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetFontFamilies(const wchar_t** names, int count)
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f2740
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetFontWeight(float weight)
{
    mTextStyle.mfWeight = weight;
    mbFontChanged = 1;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2760
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetFontWeight(int weight)
{
    mTextStyle.mfWeight = (float)weight;
    mbFontChanged = 1;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2780
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetFontSize(Length_s008f_2660 size)
{
    mFontSize.mValue = size.mValue;
    mFontSize.mUnits = size.mUnits;
    mbFontChanged = 1;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f27a0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetStretch(float stretch)
{
    mTextStyle.mfStretch = stretch;
    mbFontChanged = 1;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f27c0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetFontSmoothThresh(Length_s008f_2660 thresh)
{
    mFontSmoothThresh.mValue = thresh.mValue;
    mFontSmoothThresh.mUnits = thresh.mUnits;
    mbFontChanged = 1;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f27f0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetBackgroundColor(unsigned int color)
{
    mColorInherited = color;
    mBgColor = color;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f28c0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetDecorationFlags(unsigned short set, unsigned short mask)
{
    mTextStyle.mnDecorationFlags = (unsigned int)set | (mTextStyle.mnDecorationFlags & ~(unsigned int)mask);
    mbFontChanged = 1;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2910
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetVerticalAlign(Length_s008f_2660 align)
{
    mVerticalAlign.mValue = align.mValue;
    mVerticalAlign.mUnits = align.mUnits;
    mVerticalAlignKW = 8;   // "length" keyword marker
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f29b0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetMargin(Length_s008f_2660 len, int edge)
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
        Length_s008f_2660* p = &mEdges[edge].mMargin;
        p->mValue = len.mValue;
        p->mUnits = len.mUnits;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2a20
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetPadding(Length_s008f_2660 len, int edge)
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
        Length_s008f_2660* p = &mEdges[edge].mPadding;
        p->mValue = len.mValue;
        p->mUnits = len.mUnits;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2a90
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetBorderWidth(Length_s008f_2660 len, int edge)
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
        Length_s008f_2660* p = &mEdges[edge].mBorder;
        p->mValue = len.mValue;
        p->mUnits = len.mUnits;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2b00
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetBorderColor(unsigned int color, int edge)
{
    if (edge == 4) {
        for (int i = 0; i < 4; ++i)
            mEdges[i].mBorderColor = color;
    } else {
        mEdges[edge].mBorderColor = color;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2b40
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetBorderStyle(int style, int edge)
{
    if (edge == 4) {
        for (int i = 0; i < 4; ++i)
            mEdges[i].mBorderStyle = style;
    } else {
        mEdges[edge].mBorderStyle = style;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2bc0
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetBorderSpacing(Length_s008f_2660 len)
{
    mBorderSpacingH.mValue = len.mValue;
    mBorderSpacingH.mUnits = len.mUnits;
    mBorderSpacingV.mValue = len.mValue;
    mBorderSpacingV.mUnits = len.mUnits;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2c60
namespace EA { namespace XHTML { namespace Style {
void StyleState_s008f_2660::SetBoxOffset(Length_s008f_2660 len, int index)
{
    mBoxOffset[index].mValue = len.mValue;
    mBoxOffset[index].mUnits = len.mUnits;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2ce0
namespace EA { namespace XHTML { namespace Style {
uint32_t MakeColor(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4)
{
    uint32_t v = p1;
    v = (v << 8) | p2;
    v = (v << 8) | p3;
    v = (v << 8) | p4;
    return v;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2d10
namespace EA { namespace XHTML { namespace Style {
bool CharStream_s008f_2660::CopyWideLine(const wchar_t* src, wchar_t* dst, unsigned int maxLen)
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f2d70
namespace EA { namespace XHTML { namespace Style {
void PropFunc_Uint::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned int))mpSetter)((char*)mpContext + index, mValue);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2d90
namespace EA { namespace XHTML { namespace Style {
void PropFunc_Float::Apply(int index)
{
    ((void (__thiscall*)(void*, float))mpSetter)((char*)mpContext + index, mValue);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2db0
namespace EA { namespace XHTML { namespace Style {
void PropFunc_2UShort::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned short, unsigned short))mpSetter)((char*)mpContext + index, mA, mB);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2dd0
namespace EA { namespace XHTML { namespace Style {
void PropFunc_3Uint::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned int, unsigned int, unsigned int))mpSetter)((char*)mpContext + index, mA, mB, mC);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2df0
namespace EA { namespace XHTML { namespace Style {
void PropFunc_2Uint::Apply(int index)
{
    ((void (__thiscall*)(void*, unsigned int, unsigned int))mpSetter)((char*)mpContext + index, mA, mB);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2e10
namespace EA { namespace XHTML { namespace Style {
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f2e90
namespace EA { namespace XHTML { namespace Style {
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f2f10
namespace EA { namespace XHTML { namespace Style {
void TextRun::Fn8f2f10(void* arg)
{
    if (mpPresenter == 0)
        return;
    wchar_t* text = mpTextBegin;
    wchar_t buf[0x100];
    buf[0] = 0;
    ((CharStream_s008f_2660*)((char*)this + 4))->CopyWideLine(text, buf, 0x100);
    void** vt = *(void***)mpPresenter;
    typedef void (__thiscall* PresentFn)(void*, void*, void*, int, int, void*);
    ((PresentFn)vt[1])(mpPresenter, arg, mpText0, mField2c,
                       (unsigned int)((const char*)mpTextEnd - (const char*)text) >> 1,
                       text != 0 ? (void*)buf : 0);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f2f80
namespace EA { namespace XHTML { namespace Style {
wchar_t* CSSParser_s008f_2660::TokenValue()
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f2fe0
namespace EA { namespace XHTML { namespace Style {
wchar_t CharStream_s008f_2660::NextChar()
{
    wchar_t* p = mpPos;
    if (p < mpEnd) {
        wchar_t c = *p;
        mpPos = p + 1;
        return c;
    }
    return 0;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f3000
namespace EA { namespace XHTML { namespace Style {
bool CharStream_s008f_2660::MatchChar(unsigned int c)
{
    wchar_t* p = mpPos;
    if (p < mpEnd && c == (unsigned int)*p) {
        mpPos = p + 1;
        return true;
    }
    return false;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f3020
namespace EA { namespace XHTML { namespace Style {
Property_s008f_2660* CreatePropertyFunc_float(EA::Allocator::StackAllocator_s0092_8b00* a, void* setter, void* ctx, void* p4, void* p5, float value)
{
    unsigned int size = (sizeof(Property_s008f_2660) + sizeof(float) + 7) & ~7u;
    Property_s008f_2660* p = (Property_s008f_2660*)a->Allocate(size);
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f3090
namespace EA { namespace XHTML { namespace Style {
Property_s008f_2660* CreatePropertyFunc_Length(EA::Allocator::StackAllocator_s0092_8b00* a, void* setter, void* ctx, void* p4, void* p5, Length_s008f_2660 value)
{
    unsigned int size = (sizeof(Property_s008f_2660) + sizeof(Length_s008f_2660) + 7) & ~7u;
    Property_s008f_2660* p = (Property_s008f_2660*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(Length_s008f_2660*)((char*)p + 0x18) = value;
    return p;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f3100
namespace EA { namespace XHTML { namespace Style {
Property_s008f_2660* CreatePropertyFunc_ushort_ushort(EA::Allocator::StackAllocator_s0092_8b00* a, void* setter, void* ctx, void* p4, void* p5, unsigned short v, unsigned short u)
{
    unsigned int size = (sizeof(Property_s008f_2660) + 2 + 2 + 7) & ~7u;
    Property_s008f_2660* p = (Property_s008f_2660*)a->Allocate(size);
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f3170
namespace EA { namespace XHTML { namespace Style {
Property_s008f_2660* CreatePropertyFunc_Length_EdgeIndex(EA::Allocator::StackAllocator_s0092_8b00* a, void* setter, void* ctx, void* p4, void* p5, Length_s008f_2660 value, int edge)
{
    unsigned int size = (sizeof(Property_s008f_2660) + sizeof(Length_s008f_2660) + sizeof(int) + 7) & ~7u;
    Property_s008f_2660* p = (Property_s008f_2660*)a->Allocate(size);
    if (p == 0)
        return 0;
    p->mpNext = 0;
    p->mpVtable = (void*)gPropVtable;
    p->mpSetter = setter;
    p->mpContext = ctx;
    p->mpArg0 = p4;
    p->mpArg1 = p5;
    *(Length_s008f_2660*)((char*)p + 0x18) = value;
    *(int*)((char*)p + 0x20) = edge;
    return p;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f31f0
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_2660::SetEdgePropertiesLength(int* list, Length_s008f_2660* values, int mode, void* p5, void* p6, void* p7, void* p8)
{
    if (mode == 0)
        return false;
    if (mode == 1) {
        Property_s008f_2660* p = CreatePropertyFunc_Length_EdgeIndex(mAllocator, p5, p6, p7, p8, values[0], 4);
        p->mpNext = (Property_s008f_2660*)*list;
        *list = (int)p;
        return true;
    }
    for (int i = 0; i < 4; ++i) {
        int edge = gEdgeMap[mode * 4 + i];
        Property_s008f_2660* p = CreatePropertyFunc_Length_EdgeIndex(mAllocator, p5, p6, p7, p8, values[edge], i);
        p->mpNext = (Property_s008f_2660*)*list;
        *list = (int)p;
    }
    return true;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f32d0
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_2660::SetEdgePropertiesUint(int* list, unsigned int* values, int mode, void* p5, void* p6, void* p7, void* p8)
{
    if (mode == 0)
        return false;
    if (mode == 1) {
        Property_s008f_2660* p = CreatePropertyFunc_uint_EdgeIndex(mAllocator, p5, p6, p7, p8, values[0], 4);
        p->mpNext = (Property_s008f_2660*)*list;
        *list = (int)p;
        return true;
    }
    for (int i = 0; i < 4; ++i) {
        int edge = gEdgeMap[mode * 4 + i];
        Property_s008f_2660* p = CreatePropertyFunc_uint_EdgeIndex(mAllocator, p5, p6, p7, p8, values[edge], i);
        p->mpNext = (Property_s008f_2660*)*list;
        *list = (int)p;
    }
    return true;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f33a0
namespace EA { namespace XHTML { namespace Style {
Property_s008f_2660* CreatePropertyFunc_uint(EA::Allocator::StackAllocator_s0092_8b00* a, void* setter, void* ctx, void* p4, void* p5, unsigned int value)
{
    unsigned int size = (sizeof(Property_s008f_2660) + sizeof(unsigned int) + 7) & ~7u;
    Property_s008f_2660* p = (Property_s008f_2660*)a->Allocate(size);
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f3410
namespace EA { namespace XHTML { namespace Style {
Property_s008f_2660* CreatePropertyFunc_uint_EdgeIndex(EA::Allocator::StackAllocator_s0092_8b00* a, void* setter, void* ctx, void* p4, void* p5, unsigned int value, int edge)
{
    unsigned int size = (sizeof(Property_s008f_2660) + sizeof(unsigned int) + sizeof(int) + 7) & ~7u;
    Property_s008f_2660* p = (Property_s008f_2660*)a->Allocate(size);
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f3480
namespace EA { namespace XHTML { namespace Style {
bool CharStream_s008f_2660::MatchAscii(const char* s)
{
    int i = 0;
    char c = s[0];
    if (c != 0) {
        wchar_t* end = mpEnd;
        wchar_t* p = mpPos;
        do {
            unsigned short ch = (p < end) ? (unsigned short)*p : 0;
            if (c != ch)
                return false;
            c = s[i + 1];
            ++i;
            ++p;
        } while (c != 0);
    }
    mpPos += i;
    return true;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f34d0
namespace EA { namespace XHTML { namespace Style {
bool CharStream_s008f_2660::MatchWide(const wchar_t* s)
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
}}}  // namespace EA::XHTML::Style

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

// @ 0x008f43f0
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_43f0::MatchURL()
{
    SkipSpace();
    if (mToken != TokenIdent_s008f_43f0)
        return false;
    if (wcscmp(L"url", mReader.mMatchText.mpBegin) != 0)
        return false;

    Advance();
    SkipSpace();
    if (mToken != TokenOpenParen)
        return false;

    mReader.SkipWhitespace();

    wchar_t quote = 0;
    if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L'"') {
        quote = L'"';
        mReader.mScanPos += 1;
    } else if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L'\'') {
        quote = L'\'';
        mReader.mScanPos += 1;
    }

    mReader.mMatchText.Empty();

    if (quote == 0) {
        while (mReader.mScanPos < mReader.mScanEnd) {
            if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L')') {
                mReader.mScanPos += 1;
                break;
            }
            if (!mReader.MatchEscape()) {
                if (mReader.mScanPos >= mReader.mScanEnd || iswctype(*mReader.mScanPos, 0x157) == 0) {
                    Error(0x23b0000);
                    break;
                }
                mReader.mMatchText.push_back(*mReader.mScanPos);
                mReader.mScanPos += 1;
            }
        }
        mReader.mMatchText.trim();
    } else {
        while (mReader.mScanPos < mReader.mScanEnd) {
            if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == quote) {
                mReader.mScanPos += 1;
                break;
            }
            if (!mReader.MatchEscape()) {
                if (mReader.mScanPos >= mReader.mScanEnd || iswctype(*mReader.mScanPos, 0x157) == 0) {
                    Error(0x23b0000);
                    break;
                }
                mReader.mMatchText.push_back(*mReader.mScanPos);
                mReader.mScanPos += 1;
            }
        }

        SkipSpace();
        if (mReader.mScanPos < mReader.mScanEnd && *mReader.mScanPos == L')')
            mReader.mScanPos += 1;
        else
            Error(0x23b0004);
    }

    mTokenValue.swap(mReader.mMatchText);
    Advance();
    return true;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f4600
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_43f0::ParseFontFamily(Property_s008f_43f0** pList)
{
    PropFontFamily* prop = (PropFontFamily*)mAllocator->Allocate(0x40);
    if (prop != 0) {
        prop->mpSetter  = (void*)0x8f26b0;
        prop->mpContext = 0;
        prop->mpArg0    = 0;
        prop->mpNext    = 0;
        prop->mpVtable  = gFontFamilyVtable;
        prop->mpArg1    = 0;
        prop->mCount    = 0;
    }

    int count = 0;
    for (;;) {
        if (mToken == TokenIdent_s008f_43f0) {
            mTokenValue.swap(mReader.mMatchText);
        } else if (mToken == TokenString_s008f_43f0) {
            mTokenValue.swap(mReader.mMatchText);
        } else {
            break;
        }
        Advance();

        unsigned int nChars = (unsigned int)(mTokenValue.mpEnd - mTokenValue.mpBegin);
        unsigned int cbName = nChars * 2;
        wchar_t* name = (wchar_t*)mAllocator->Allocate((cbName + 9) & 0xfffffff8);
        memcpy(name, mTokenValue.mpBegin, cbName);
        *(wchar_t*)((char*)name + cbName) = 0;

        if (prop->mCount < 8) {
            prop->mNames[prop->mCount] = name;
            prop->mCount++;
        }
        count++;

        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }

        if (mToken != TokenComma)
            break;

        mTokenValue.swap(mReader.mMatchText);
        Advance();

        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
    }

    prop->mpNext = (PropFontFamily*)*pList;
    *pList = (Property_s008f_43f0*)prop;
    return count > 0;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f4890
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_43f0::ParseBackgroundImage(Property_s008f_43f0** pList)
{
    Property_s008f_43f0* p;
    if (MatchURL()) {
        p = CreateURLPropertyFunc(mAllocator, PropCtx((void*)0x8f2810, 0, 0, 0), TokenValue());
    } else if (MatchIdent(L"none")) {
        p = CreateURLPropertyFunc(mAllocator, PropCtx((void*)0x8f2810, 0, 0, 0), 0);
    } else {
        return false;
    }

    p->mpNext = *pList;
    *pList = p;
    return true;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f53e0
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_43f0::MatchSymbolBackgroundRepeat(const void* pTable, float* pValue)
{
    if (mToken == TokenIdent_s008f_43f0) {
        const wchar_t* key = mReader.mMatchText.mpBegin;
        const void* range[2];
        EqualRange(range, pTable, (const char*)pTable + 0x58, &key);

        if ((const char*)range[0] + 8 == (const char*)range[1]) {
            *pValue = *(const float*)((const char*)range[0] + 4);
            Advance();
            return true;
        }
    }
    return false;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f5560
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_43f0::MatchLength(Length_s008f_43f0* p)
{
    if (mToken == TokenNumber) {
        p->mValue = (float)wcstod(mReader.mMatchText.mpBegin, 0);
        Advance();
        p->mUnits = mDefaultUnits;

        if (mToken == TokenPercent) {
            mTokenValue.swap(mReader.mMatchText);
            Advance();
            p->mUnits = 9;
        } else {
            MatchSymbolUnits(gUnitsTable, (unsigned int*)&p->mUnits);
        }
        return true;
    }
    return false;
}
}}}  // namespace EA::XHTML::Style

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

// @ 0x008f85e0
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_85e0::ParsePropertyValue(int propID, PropertyList_s008f_85e0* pList)
{
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f8cb0
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_85e0::ParsePropertyByID(int propID, wchar16* pSource, StackAllocator_s008f_85e0* pAllocator, PropertyList_s008f_85e0* pList, Units units, void* pErrorListener)
{
    CSSParser_s008f_85e0 parser;
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f8d50
namespace EA { namespace XHTML { namespace Style {
bool CSSParser_s008f_85e0::ParseProperty(PropertyList_s008f_85e0* pList)
{
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
                if ((gTokFlag & 1) == 0) gTokFlag = gTokFlag | 1;
                mReader.SetDefault(&gTokStart);
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
                        if (p) *p = v;      // retail stores only when the old end pointer is non-null
                    } else {
                        pSheet->InsertRuleAt(pSheet->mVecEnd, &v);
                    }
                } else {
                    Error(0x23b000b);
                    if ((gTokFlag & 1) == 0) gTokFlag = gTokFlag | 1;
                    mReader.SetDefault(&gTokStart);
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
