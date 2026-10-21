// Slice s008f43f0 -- EA::XHTML::Style::CSSParser URL / font / list / counter / direction /
// text-overflow property parsers plus the wide-string symbol matchers they use (SporeApp.exe).
//
//  0x008f43f0 CSSParser::MatchURL              -- "url(" token -> mTokenValue (ret 0 single arg, bool)
//  0x008f4600 CSSParser::ParseFontFamily       -- comma-separated family names into a font prop list
//  0x008f47e0 CSSParser::ParseFontVariant      -- normal | small-caps
//  0x008f4890 CSSParser::ParseBackgroundImage  -- url() | none
//  0x008f4930 CSSParser::ParseBackgroundAttachment -- scroll | fixed
//  0x008f49e0 CSSParser::ParseListStyleImage   -- url() | none
//  0x008f4aa0 CSSParser::ParseListStylePosition-- inside | outside
//  0x008f4b80 CSSParser::ParseCounterReset     -- none | inherit | <ident> [<int>] ...
//  0x008f4da0 CSSParser::ParseCounterIncrement -- same shape (different setter fns)
//  0x008f4fc0 CSSParser::ParseDirection        -- ltr | rtl | inherit
//  0x008f5080 CSSParser::ParseTextOverflow     -- clip | ellipsis | ellipsis-word
//  0x008f53e0 CSSParser::MatchSymbolBackgroundRepeat -- equal_range over the repeat table
//  0x008f5560 CSSParser::MatchLength           -- number + optional units
//
// Retail layouts recovered from the disassembly (2008 PDB names/offsets agree around here):
//   CSSParser { mpSourceURI +0, CharStream mReader +4 (mScanPos +4, mScanEnd +8, mLineBegin +0xc,
//   mCurrentLine +0x10, mMatchText String +0x14, mResult +0x20), mToken +0x28, mTokenLine +0x2c,
//   mTokenLineStart +0x30, mTokenPos +0x34, mTokenValue String +0x38, mpErrorListener +0x48,
//   mAllocator +0x4c, mExtra String +0x50, mDefaultUnits +0x60 }.
//   FontFamily property object (0x40): vtable +0, next +4, setter +8, context +0xc, arg0 +0x10,
//   arg1 +0x14, wchar_t* mNames[8] +0x18, mCount +0x38.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// msvcr90 imports (calls go through the .rdata IAT slots at 0x13cc52c / 0x13cc514).
__declspec(dllimport) int __cdecl iswctype(unsigned int ch, unsigned int kind);
__declspec(dllimport) double __cdecl wcstod(const wchar_t* s, wchar_t** end);
extern "C" void* memcpy(void* dst, const void* src, unsigned int n);   // 0x011e0744 thunk
// No dllimport: cl 15 inlines the literal-first two-wide-char comparison used for "url", "normal", ...
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);

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

typedef EA::Allocator::StackAllocator_s0092_8b00 StackAllocator;

enum CSSToken { TokenWS = 2, TokenIdent = 3, TokenNumber = 4, TokenString = 5,
                TokenOpenParen = 0xb, TokenComma = 0x13, TokenPercent = 0x18 };

// Fixed 12-byte wide string (begin/end/capacity) used for the parser's token scan buffers.
struct String {
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

    void swap(String& o)
    {
        wchar_t* t;
        t = mpBegin; mpBegin = o.mpBegin; o.mpBegin = t;
        t = mpEnd; mpEnd = o.mpEnd; o.mpEnd = t;
        t = mpCapacity; mpCapacity = o.mpCapacity; o.mpCapacity = t;
    }

    void push_back(wchar_t c);   // 0x004f6510
    void trim();                 // 0x0057eda0
};

// A single property linked-list node (also the head of the list built by the parsers).
class Property { public:
    void*     mpVtable;   // +0
    Property* mpNext;     // +4
    void*     mpSetter;   // +8
    void*     mpContext;  // +0xc
    void*     mpArg0;     // +0x10
    void*     mpArg1;     // +0x14
};

// The 16-byte setter/context bundle the property builders take by value.
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

// The 0x40-byte object ParseFontFamily builds (a font-family property).
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

struct Length {
    float mValue;   // +0
    int   mUnits;   // +4
};

}  // namespace Style
}  // namespace XHTML
}  // namespace EA

// ---------------------------------------------------------------------------
// Free property-builder helpers (global scope; the retail ones are free funs).
// ---------------------------------------------------------------------------
// 0x008f33a0  EA::XHTML::Style::CreatePropertyFunc<unsigned int>
EA::XHTML::Style::Property* CreatePropertyFunc_uint(
    EA::Allocator::StackAllocator_s0092_8b00* a, EA::XHTML::Style::PropCtx ctx, unsigned int value);

// 0x008f3410  EA::XHTML::Style::CreatePropertyFunc<unsigned int, EdgeIndex>
EA::XHTML::Style::Property* CreatePropertyFunc_uint_EdgeIndex(
    EA::Allocator::StackAllocator_s0092_8b00* a, EA::XHTML::Style::PropCtx ctx,
    unsigned int value, int index);

// 0x008f25f0  EA::XHTML::Style::CreateURLPropertyFunc
EA::XHTML::Style::Property* CreateURLPropertyFunc(
    EA::Allocator::StackAllocator_s0092_8b00* a, EA::XHTML::Style::PropCtx ctx, void* url);

// 0x008f2550  property builder with no value argument (the "none" cases)
EA::XHTML::Style::Property* CreatePropertyFunc_void(
    EA::Allocator::StackAllocator_s0092_8b00* a, EA::XHTML::Style::PropCtx ctx);

// 0x008f3790  eastl::equal_range over a sorted symbol table
void EqualRange(void* out, const void* first, const void* last, const void* key);

extern char gFontFamilyVtable[];             // 0x01439a6c
extern const unsigned char gUnitsTable[];    // 0x0154d2e0

namespace EA {
namespace XHTML {
namespace Style {

// CharStream base of the parser (owned by CSSParser at +4).
struct Reader {
    wchar_t* mScanPos;     // +0
    wchar_t* mScanEnd;     // +4
    wchar_t* mLineBegin;   // +8
    int      mCurrentLine; // +0xc
    String   mMatchText;   // +0x10
    int      mResult;      // +0x1c
    int      mPad20;       // +0x20

    char SkipWhitespace();   // 0x008f3830
    char MatchEscape();      // 0x008f3a80
};

class CSSParser {
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
    bool ParseFontFamily(Property** pList);                       // 0x008f4600
    bool ParseFontVariant(Property** pList);                      // 0x008f47e0
    bool ParseBackgroundImage(Property** pList);                  // 0x008f4890
    bool ParseBackgroundAttachment(Property** pList);             // 0x008f4930
    bool ParseListStyleImage(Property** pList);                   // 0x008f49e0
    bool ParseListStylePosition(Property** pList);                // 0x008f4aa0
    bool ParseCounterReset(Property** pList);                     // 0x008f4b80
    bool ParseCounterIncrement(Property** pList);                 // 0x008f4da0
    bool ParseDirection(Property** pList);                        // 0x008f4fc0
    bool ParseTextOverflow(Property** pList);                     // 0x008f5080
    bool MatchSymbolBackgroundRepeat(const void* pTable, float* pValue);  // 0x008f53e0
    bool MatchLength(Length* p);                                  // 0x008f5560

    // --- fields (absolute offsets from `this`) ---
    int         mPad00;           // +0x00
    Reader      mReader;          // +0x04 (size 0x24)
    int         mToken;           // +0x28
    int         mTokenLine;       // +0x2c
    wchar_t*    mTokenLineStart;  // +0x30
    wchar_t*    mTokenPos;        // +0x34
    String      mTokenValue;      // +0x38
    int         mPad44;           // +0x44
    void*       mpErrorListener;  // +0x48
    StackAllocator* mAllocator;   // +0x4c
    String      mExtra;           // +0x50
    int         mPad5c;           // +0x5c
    int         mDefaultUnits;    // +0x60
};

// ---------------------------------------------------------------------------
// 0x008f43f0  CSSParser::MatchURL -- parse a url( ... ) token into mTokenValue
// ---------------------------------------------------------------------------
// @ 0x008f43f0
bool CSSParser::MatchURL()
{
    SkipSpace();
    if (mToken != TokenIdent)
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

// ---------------------------------------------------------------------------
// 0x008f4600  CSSParser::ParseFontFamily -- a comma-separated list of family names
// ---------------------------------------------------------------------------
// @ 0x008f4600
bool CSSParser::ParseFontFamily(Property** pList)
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
        if (mToken == TokenIdent) {
            mTokenValue.swap(mReader.mMatchText);
        } else if (mToken == TokenString) {
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
    *pList = (Property*)prop;
    return count > 0;
}

// ---------------------------------------------------------------------------
// 0x008f47e0  CSSParser::ParseFontVariant -- normal | small-caps
// ---------------------------------------------------------------------------
// @ 0x008f47e0
bool CSSParser::ParseFontVariant(Property** pList)
{
    unsigned int v;
    if (mToken == TokenIdent && wcscmp(L"normal", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        v = 0;
    } else if (MatchIdent(L"small-caps")) {
        v = 1;
    } else {
        return false;
    }

    Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f2720, 0, 0, 0), v);
    p->mpNext = *pList;
    *pList = p;
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f4890  CSSParser::ParseBackgroundImage -- url(...) | none
// ---------------------------------------------------------------------------
// @ 0x008f4890
bool CSSParser::ParseBackgroundImage(Property** pList)
{
    Property* p;
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

// ---------------------------------------------------------------------------
// 0x008f4930  CSSParser::ParseBackgroundAttachment -- scroll | fixed
// ---------------------------------------------------------------------------
// @ 0x008f4930
bool CSSParser::ParseBackgroundAttachment(Property** pList)
{
    unsigned int v;
    if (mToken == TokenIdent && wcscmp(L"scroll", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        v = 0;
    } else {
        if (!MatchIdent(L"fixed"))
            return false;
        v = 1;
    }

    Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f2830, 0, 0, 0), v);
    p->mpNext = *pList;
    *pList = p;
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f49e0  CSSParser::ParseListStyleImage -- url(...) | none
// ---------------------------------------------------------------------------
// @ 0x008f49e0
bool CSSParser::ParseListStyleImage(Property** pList)
{
    if (MatchURL()) {
        Property* p = CreateURLPropertyFunc(mAllocator, PropCtx((void*)0x8f2cc0, 0, 0, 0), TokenValue());
        p->mpNext = *pList;
        *pList = p;
        return true;
    }

    if (MatchIdent(L"none")) {
        Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f2cb0, 0, 0, 0), 0);
        p->mpNext = *pList;
        *pList = p;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x008f4aa0  CSSParser::ParseListStylePosition -- inside | outside
// ---------------------------------------------------------------------------
// @ 0x008f4aa0
bool CSSParser::ParseListStylePosition(Property** pList)
{
    if (mToken == TokenIdent && wcscmp(L"inside", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f2cd0, 0, 0, 0), 0);
        p->mpNext = *pList;
        *pList = p;
        return true;
    }

    if (MatchIdent(L"outside")) {
        Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f2cd0, 0, 0, 0), 1);
        p->mpNext = *pList;
        *pList = p;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x008f4b80  CSSParser::ParseCounterReset -- none | inherit | <ident> [<int>] ...
// ---------------------------------------------------------------------------
// @ 0x008f4b80
bool CSSParser::ParseCounterReset(Property** pList)
{
    if (mToken == TokenIdent && wcscmp(L"none", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        Property* p = CreatePropertyFunc_void(mAllocator, PropCtx((void*)0x8fbb90, 0, 0, 0));
        p->mpNext = *pList;
        *pList = p;
        return true;
    }

    if (MatchIdent(L"inherit"))
        return true;

    for (;;) {
        if (mToken == TokenIdent) {
            mTokenValue.swap(mReader.mMatchText);
        } else if (mToken == TokenString) {
            mTokenValue.swap(mReader.mMatchText);
        } else {
            return true;
        }
        Advance();

        unsigned int nChars = (unsigned int)(mTokenValue.mpEnd - mTokenValue.mpBegin);
        unsigned int cbName = nChars * 2;
        wchar_t* name = (wchar_t*)mAllocator->Allocate((cbName + 9) & 0xfffffff8);
        memcpy(name, mTokenValue.mpBegin, cbName);
        *(wchar_t*)((char*)name + cbName) = 0;

        float f = 1.0f;
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
        if (mToken == TokenNumber) {
            f = (float)wcstod(mReader.mMatchText.mpBegin, 0);
            Advance();
        }

        Property* p = CreatePropertyFunc_uint_EdgeIndex(
            mAllocator, PropCtx((void*)0x8fca70, 0, 0, 0), (unsigned int)name, (int)f);
        p->mpNext = *pList;
        *pList = p;

        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x008f4da0  CSSParser::ParseCounterIncrement -- same shape as ParseCounterReset
// ---------------------------------------------------------------------------
// @ 0x008f4da0
bool CSSParser::ParseCounterIncrement(Property** pList)
{
    if (mToken == TokenIdent && wcscmp(L"none", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        Property* p = CreatePropertyFunc_void(mAllocator, PropCtx((void*)0x8fbbc0, 0, 0, 0));
        p->mpNext = *pList;
        *pList = p;
        return true;
    }

    if (MatchIdent(L"inherit"))
        return true;

    for (;;) {
        if (mToken == TokenIdent) {
            mTokenValue.swap(mReader.mMatchText);
        } else if (mToken == TokenString) {
            mTokenValue.swap(mReader.mMatchText);
        } else {
            return true;
        }
        Advance();

        unsigned int nChars = (unsigned int)(mTokenValue.mpEnd - mTokenValue.mpBegin);
        unsigned int cbName = nChars * 2;
        wchar_t* name = (wchar_t*)mAllocator->Allocate((cbName + 9) & 0xfffffff8);
        memcpy(name, mTokenValue.mpBegin, cbName);
        *(wchar_t*)((char*)name + cbName) = 0;

        float f = 1.0f;
        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
        if (mToken == TokenNumber) {
            f = (float)wcstod(mReader.mMatchText.mpBegin, 0);
            Advance();
        }

        Property* p = CreatePropertyFunc_uint_EdgeIndex(
            mAllocator, PropCtx((void*)0x8fca90, 0, 0, 0), (unsigned int)name, (int)f);
        p->mpNext = *pList;
        *pList = p;

        while (mToken == TokenWS) {
            mTokenValue.Empty();
            Advance();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x008f4fc0  CSSParser::ParseDirection -- ltr | rtl | inherit
// ---------------------------------------------------------------------------
// @ 0x008f4fc0
bool CSSParser::ParseDirection(Property** pList)
{
    unsigned int v;
    if (mToken == TokenIdent && wcscmp(L"ltr", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        v = 0;
    } else if (MatchIdent(L"rtl")) {
        v = 1;
    } else if (MatchIdent(L"inherit")) {
        v = 2;
    } else {
        return false;
    }

    Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f28f0, 0, 0, 0), v);
    p->mpNext = *pList;
    *pList = p;
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f5080  CSSParser::ParseTextOverflow -- clip | ellipsis | ellipsis-word
// ---------------------------------------------------------------------------
// @ 0x008f5080
bool CSSParser::ParseTextOverflow(Property** pList)
{
    unsigned int v;
    if (mToken == TokenIdent && wcscmp(L"clip", mReader.mMatchText.mpBegin) == 0) {
        Advance();
        v = 1;
    } else if (MatchIdent(L"ellipsis")) {
        v = 2;
    } else if (MatchIdent(L"ellipsis-word")) {
        v = 2;
    } else {
        return false;
    }

    Property* p = CreatePropertyFunc_uint(mAllocator, PropCtx((void*)0x8f2900, 0, 0, 0), v);
    p->mpNext = *pList;
    *pList = p;
    return true;
}

// ---------------------------------------------------------------------------
// 0x008f53e0  CSSParser::MatchSymbolBackgroundRepeat -- look the ident up in a table
// ---------------------------------------------------------------------------
// @ 0x008f53e0
bool CSSParser::MatchSymbolBackgroundRepeat(const void* pTable, float* pValue)
{
    if (mToken == TokenIdent) {
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

// ---------------------------------------------------------------------------
// 0x008f5560  CSSParser::MatchLength -- a number, with an optional unit keyword/percent
// ---------------------------------------------------------------------------
// @ 0x008f5560
bool CSSParser::MatchLength(Length* p)
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

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
