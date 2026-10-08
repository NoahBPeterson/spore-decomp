// EA::XHTML::Style::CSSParser::ParseSimpleSelector (0x008f5960): parses a CSS simple selector
// (`ident` or `*`, followed by any number of `#id`, `.class`, `:pseudo`, `[attr...]` parts) and
// appends the selector nodes (allocated from the parser's StackAllocator) to a node list.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

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
    TokenIdent = 3, TokenColon = 9, TokenCloseBracket = 0x10, TokenEquals = 0x11, TokenDot = 0x12,
    TokenOpenBracket = 0xf, TokenStar = 0x16, TokenString = 5, TokenIncludes = 0x19, TokenDashMatch = 0x1a,
    TokenPound = 6
};

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
    virtual void Matches() {}
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

struct SelectorList {  // head/tail of a singly linked node list
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

class CSSParser {
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

extern const char gPseudoTable[];  // 0x0154d7a8

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

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
