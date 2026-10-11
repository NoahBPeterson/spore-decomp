// gold1 slice 44 (s008f9220) -- EA::XHTML::Style CSS parser / selector matching internals.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (no /EHsc -- the original has no C++
// unwind frame in the Stylesheet ctor / deleting dtor; /GS- -- Clear's 0x560 stack
// scratch has no /GS cookie; /fp:fast -- required for Length::ToPixels byte-exactness.)
#include "types.h"

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" int wcscmp(const wchar_t*, const wchar_t*);
extern "C" int wmemcmp(const wchar_t*, const wchar_t*, unsigned int);

namespace EA {
namespace Allocator {
class StackAllocator {  // size 0x24
public:
    StackAllocator() {}
    StackAllocator(int, int, int, int, int);    // 0x00928cd0
    ~StackAllocator() { Reset(); }
    bool AllocateNewBlock(unsigned int nSize);   // 0x00928ba0
    void Init(int, int, int, int, int);          // 0x00928b00
    void Reset();                                // 0x00928dc0
    unsigned int mnDefaultBlockSize;  // +0x0
    void* mpCurrentBlock;             // +0x4
    char* mpCurrentBlockEnd;          // +0x8
    char* mpCurrentObjectBegin;       // +0xc
    char* mpCurrentObjectEnd;         // +0x10
    char _padExtra[0x10];             // +0x14..0x23 (size 0x24)
};
}  // namespace Allocator
}  // namespace EA

// 8-byte granular stack-allocation helper (normally inlined).
inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator* a) {
    nSize = (nSize + 7) & ~7u;
    if ((int)(a->mpCurrentBlockEnd - a->mpCurrentObjectBegin - nSize) < 0) {
        if (!a->AllocateNewBlock(nSize))
            return 0;
    }
    char* p = a->mpCurrentObjectBegin;
    a->mpCurrentObjectBegin = p + nSize;
    a->mpCurrentObjectEnd = p + nSize;
    return p;
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
};

}  // namespace DOM

namespace Style {

using EA::XHTML::DOM::Node;

// ============================ selector node hierarchy ============================
// vtable = [ dtor (slot 0) | Match (slot 1, +4) | Slot2 (slot 2, +8) ], mpNext at +4.
class Selector {
public:
    Selector() : mpNext(0) {}
    virtual ~Selector();
    virtual bool Match(Node* pNode, bool bDeep);
    virtual void* Slot2() { return 0; }
    void Append(Selector* p);   // 0x008f9fa0
    Selector* mpNext;           // +0x4
};

class TagSelector : public Selector {
public:
    virtual ~TagSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};

class ClassSelector : public Selector {  // vtable 0x014399e8
public:
    virtual ~ClassSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
    int mLength;           // +0xc
};

class IdSelector : public Selector {  // vtable 0x014399f4
public:
    virtual ~IdSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};

class DescendantSelector : public Selector {
public:
    virtual ~DescendantSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    Selector* mChild;  // +0x8
};

class ChildSelector : public Selector {
public:
    virtual ~ChildSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    Selector* mChild;  // +0x8
};

class AttrExistsSelector : public Selector {  // vtable 0x01439a24
public:
    virtual ~AttrExistsSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};

class AttrEqualsSelector : public Selector {  // vtable 0x01439a30
public:
    virtual ~AttrEqualsSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
};

class AttrIncludesSelector : public Selector {  // vtable 0x01439a3c
public:
    virtual ~AttrIncludesSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
    int mValueLen;          // +0x10
};

class AttrDashSelector : public Selector {  // vtable 0x01439a48
public:
    virtual ~AttrDashSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
    int mValueLen;          // +0x10
};

class PseudoSelector : public Selector {
public:
    virtual ~PseudoSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    int mKind;  // +0x8
};

class TypeSelector : public Selector {  // vtable 0x014399dc
public:
    TypeSelector(const wchar_t* name) : mName(name) {}
    virtual ~TypeSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};

// ============================ Length ============================
struct LengthContext {
    int mReserved;  // +0x0
    float mEm;      // +0x4
    float mEx;      // +0x8
};

struct Length {
    float mValue;  // +0x0
    int mUnits;    // +0x4
    float ToPixels(float fRelative, const LengthContext* pCtx) const;        // 0x008f95c0
    float ToPixelsNonNeg(float fRelative, const LengthContext* pCtx) const;  // 0x008f9660
};

// ============================ StringContains ============================
// Register-parameter static: pString in eax, nLen in ebx, pSub/ch on the stack.
// @ 0x008f9710 StringContains
__declspec(noinline) static bool StringContains(const wchar_t* pString, const wchar_t* pSub, unsigned int nLen, wchar_t ch) {
    const wchar_t* p = pString;
    if (pString != 0 && nLen > 0) {
        const wchar_t* tok = 0;
        for (;;) {
            wchar_t c = *p;
            if (c == ch || c == 0) {
                if (tok != 0) {
                    int len = (int)(p - tok);
                    if (len == nLen && wmemcmp(pSub, tok, (unsigned int)len) == 0)
                        return true;
                    tok = 0;
                }
                if (c == 0)
                    break;
            } else if (tok == 0) {
                tok = p;
            }
            ++p;
        }
    }
    return false;
}

// ============================ Stylesheet ============================
class StylesheetBase {
public:
    StylesheetBase() : mField4(0) {}
    virtual ~StylesheetBase() {}
    int mField4;  // +0x4
};

class RuleNode {
public:
    RuleNode(Selector* pSel, void* pDecl, int x);  // 0x008eb720
    void* mpNext;      // +0x0
    void* mpDecl;      // +0x4
    void* mpSel;       // +0x8
    void* mFieldc;     // +0xc
};

struct DeclHolder {  // 8-byte declaration holder
    void* a;  // +0x0
    void* b;  // +0x4
    DeclHolder() : a(0), b(0) {}
};

class Stylesheet : public StylesheetBase {
public:
    Stylesheet(void* p);
    // @ 0x008f9e20 Stylesheet::~Stylesheet (deleting dtor inlined)
    virtual ~Stylesheet() {
        mAllocator.Reset();
        if (mVecBegin != 0 && mVecBegin != (void**)mField44)
            operator delete(mVecBegin);
    }
    void AddRule(const wchar_t* pName, void* pDecl);  // 0x008f9cd0
    void AddRule2(Selector* pSel, void* pDecl);       // 0x008f9c20
    void AppendNode(void* pNode);                     // 0x008f9bf0
    void Clear();                                     // 0x008f9ed0
    void InsertRuleAt(void** pos, void** val);  // 0x00899480

    EA::Allocator::StackAllocator mAllocator;  // +0x8
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

// rbtree helpers for Stylesheet::Clear.  They are __thiscall with the rbtree
// map in ecx; modelled as member functions so the calling convention matches
// (free functions cannot use __thiscall).
struct RbtreeInsertResult { void* mpNode; int mbInserted; };  // 8 bytes -> sret
struct RbtreeTrueType {};  // empty tag: MSVC pushes 1 byte, upper stack bytes uninitialised
struct RbtreeMap {
    RbtreeInsertResult FUN_009c1700(const void* pValue, RbtreeTrueType t);  // 0x009c1700
    void FUN_008f9e70();                                                    // 0x008f9e70
    void FUN_00d3b370(void* pNode);                                         // 0x00d3b370
};

// ============================ NameList property ============================
class NameListPropBase {
public:
    NameListPropBase() : mField4(0) {}
    virtual ~NameListPropBase() {}
    int mField4;  // +0x4
};

class NameListProp : public NameListPropBase {
public:
    NameListProp(void* a, void* b, void* c, void* d) {
        m0 = a; m1 = b; m2 = c; m3 = d; mCount = 0;
    }
    void* m0;                  // +0x8
    void* m1;                  // +0xc
    void* m2;                  // +0x10
    void* m3;                  // +0x14
    const wchar_t* mNames[8];  // +0x18
    int mCount;                // +0x38
};

NameListProp* CreateNameListPropertyFunc(EA::Allocator::StackAllocator* a, void* p2, void* p3, void* p4, void* p5,
                                         const wchar_t* name);

// ============================ CSS parser ============================
struct String {  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;     // +0x0
    wchar_t* mpEnd;       // +0x4
    wchar_t* mpCapacity;  // +0x8
    void* mpAllocName;    // +0xc
    void swap(String& x) {
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

struct Reader {  // CSSTokenReader, size 0x24
    wchar_t* mScanPos;    // +0x0
    wchar_t* mScanEnd;    // +0x4
    int mLineBegin;       // +0x8
    int mCurrentLine;     // +0xc
    String mMatchText;    // +0x10
    int mResult;          // +0x20
    void SetDefault(void* pStatic);        // 0x008f35d0
    void SetConsume(const wchar_t* pEnd);  // 0x008f3640
};

class CSSParser {
public:
    bool Parse(Stylesheet* pSheet);  // 0x008f9220

private:
    void Advance();                                     // 0x008f3d90
    bool SkipSpace();                                   // 0x008f4290
    bool ParseImportURL();                              // 0x008f43f0
    wchar_t* TokenValue();                              // 0x008f2f80
    void Error(unsigned int code);                      // 0x008f2f10
    void* ParseSelectorList(Stylesheet* pSheet);        // 0x008f61f0
    bool ParsePropertyCollection(void* pSelectorList);  // 0x008f8e00

    wchar_t* mpSourceURI;          // +0x00
    Reader mReader;                // +0x04
    int mToken;                    // +0x28
    int mTokenLine;                // +0x2c
    unsigned int mTokenLineStart;  // +0x30
    unsigned int mTokenPos;        // +0x34
    String mTokenValue;            // +0x38
    void* mpErrorListener;         // +0x48
    EA::Allocator::StackAllocator* mAllocator;  // +0x4c
};

static char sImportStatic[16];

// ============================================================================

// @ 0x008f95c0 Length::ToPixels
float Length::ToPixels(float fRelative, const LengthContext* pCtx) const {
    switch (mUnits) {
    case 1:
    case 2:
        return mValue;
    case 3:
        return mValue * 12.0f;
    case 6:
        return mValue * 72.0f;
    case 4:
        return mValue * 28.346401f;
    case 5:
        return mValue * 2.83464f;
    case 7:
        return pCtx->mEm * mValue;
    case 8:
        return pCtx->mEx * mValue;
    case 9:
        return mValue * fRelative * 0.01f;
    case 0:
        return mValue * fRelative;
    default:
        return 0.0f;
    }
}

// @ 0x008f9660 Length::ToPixelsNonNeg
float Length::ToPixelsNonNeg(float fRelative, const LengthContext* pCtx) const {
    float f = ToPixels(fRelative, pCtx);
    return f < 0.0f ? 0.0f : f;
}

// @ 0x008f96a0 wmemcmp
int wmemcmp(const wchar_t* p1, const wchar_t* p2, unsigned int n) {
    while (n > 0) {
        if (*p1 != *p2)
            return (*p1 < *p2) ? -1 : 1;
        ++p1;
        ++p2;
        --n;
    }
    return 0;
}

// @ 0x008f96e0 Selector::Match
bool Selector::Match(Node* pNode, bool bDeep) {
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9780 TagSelector::Match
bool TagSelector::Match(Node* pNode, bool bDeep) {
    const wchar_t* pTag = pNode->mpTagName;
    if (_wcsicmp(pTag, mName) != 0)
        return false;
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f97d0 ClassSelector::Match
bool ClassSelector::Match(Node* pNode, bool bDeep) {
    const wchar_t* pAttr = pNode->GetAttrValue(L"class");
    if (!StringContains(pAttr, mName, mLength, L' '))
        return false;
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9830 IdSelector::Match
bool IdSelector::Match(Node* pNode, bool bDeep) {
    if (pNode->mpId == 0 || wcscmp(pNode->mpId, mName) != 0)
        return false;
    return mpNext == 0 || mpNext->Match(pNode, bDeep);
}

// @ 0x008f98a0 DescendantSelector::Match
bool DescendantSelector::Match(Node* pNode, bool bDeep) {
    Node* p = pNode->Parent();
    while (p != 0) {
        if (mChild->Match(p, bDeep))
            return !(mpNext != 0 && !mpNext->Match(p, bDeep));
        p = p->Parent();
    }
    return false;
}

// @ 0x008f9910 ChildSelector::Match
bool ChildSelector::Match(Node* pNode, bool bDeep) {
    Node* p = pNode->Parent();
    if (p == 0 || mChild == 0)
        return false;
    return mChild->Match(p, bDeep) && (mpNext == 0 || mpNext->Match(pNode, bDeep));
}

// @ 0x008f9970 AttrExistsSelector::Match
bool AttrExistsSelector::Match(Node* pNode, bool bDeep) {
    return pNode->GetAttrValue(mName) != 0 && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f99c0 AttrEqualsSelector::Match
bool AttrEqualsSelector::Match(Node* pNode, bool bDeep) {
    const wchar_t* v = pNode->GetAttrValue(mName);
    return v != 0 && wcscmp(v, mValue) == 0 && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9a40 AttrIncludesSelector::Match
bool AttrIncludesSelector::Match(Node* pNode, bool bDeep) {
    const wchar_t* pAttr = pNode->GetAttrValue(mName);
    return StringContains(pAttr, mValue, mValueLen, L' ') && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9aa0 AttrDashSelector::Match
bool AttrDashSelector::Match(Node* pNode, bool bDeep) {
    const wchar_t* pAttr = pNode->GetAttrValue(mName);
    return StringContains(pAttr, mValue, mValueLen, L'-') && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9b00 PseudoSelector::Match
bool PseudoSelector::Match(Node* pNode, bool bDeep) {
    if (bDeep)
        return true;
    void* d = pNode->mpField40;
    switch (mKind) {
    case 0:
        return Selector::Match(pNode, false);
    case 1:
        return false;
    case 2: {
        Node* par = pNode->Parent();
        int v = *(int*)((char*)par + 0x18);
        if (v != 0 && (Node*)(v - 4) == pNode)
            return Selector::Match(pNode, false);
        return false;
    }
    case 3:
        if (d != 0 && *(int*)((char*)d + 8) == 1)
            return Selector::Match(pNode, false);
        return false;
    case 4:
        if (d != 0 && *(int*)((char*)d + 8) == 1 && *(int*)((char*)d + 0xc) == 3)
            return Selector::Match(pNode, false);
        return false;
    case 5:
        if (d != 0 && *(int*)((char*)d + 8) == 1 && *(int*)((char*)d + 0xc) == 4)
            return Selector::Match(pNode, false);
        if (pNode->mField30 == 1)
            return Selector::Match(pNode, false);
        return false;
    case 6:
        if (d != 0 && *(int*)((char*)d + 8) == 1 && *(int*)((char*)d + 0xc) == 2)
            return Selector::Match(pNode, false);
        return false;
    default:
        return false;
    }
}

// @ 0x008f9fa0 Selector::Append
void Selector::Append(Selector* p) {
    Selector* q = this;
    while (q->mpNext != 0)
        q = q->mpNext;
    q->mpNext = p;
}

// @ 0x008f9bf0 Stylesheet::AppendNode
void Stylesheet::AppendNode(void* pNode) {
    *(void**)pNode = 0;
    if (mpLast != 0) {
        *(void**)mpLast = pNode;
        mpLast = pNode;
    } else {
        mpFirst = pNode;
        mpLast = pNode;
    }
}

// @ 0x008f9c20 Stylesheet::AddRule2
void Stylesheet::AddRule2(Selector* pSel, void* pDecl) {
    if (pDecl == 0) {
        pDecl = new (&mAllocator) DeclHolder();
    }
    RuleNode* r = new (&mAllocator) RuleNode(pSel, pDecl, 0);
    *(void**)r = 0;
    if (mpLast != 0) {
        *(void**)mpLast = r;
        mpLast = r;
    } else {
        mpFirst = r;
        mpLast = r;
    }
}

// @ 0x008f9cd0 Stylesheet::AddRule
void Stylesheet::AddRule(const wchar_t* pName, void* pDecl) {
    TypeSelector* pSel = new (&mAllocator) TypeSelector(pName);
    AddRule2(pSel, pDecl);
}

// @ 0x008f9db0 Stylesheet::Stylesheet
Stylesheet::Stylesheet(void* p)
    : mAllocator(0, -1, 0, 0, 0) {
    mpFirst = 0;
    mpLast = 0;
    char* buf = (char*)this + 0x4c;
    mField44 = buf;
    mVecEnd = (void**)buf;
    mVecBegin = (void**)buf;
    mVecCap = (void**)(buf + 0x20);
    mField6c = p;
    mAllocator.Init(0, 0, 0, 0, 0);
}

// @ 0x008f9e20 Stylesheet::~Stylesheet  (defined inline in the class above)

// @ 0x008f9ed0 Stylesheet::Clear
void Stylesheet::Clear() {
    char tree[0x560];
    RbtreeMap* map = (RbtreeMap*)tree;
    map->FUN_008f9e70();
    for (void* rule = mpFirst; rule != 0; rule = *(void**)rule) {
        void** lst = *(void***)((char*)rule + 8);
        for (Selector* s = (Selector*)lst[0]; s != 0; s = s->mpNext) {
            void* v = s->Slot2();
            if (v)
                map->FUN_009c1700(&v, RbtreeTrueType());
        }
        for (Selector* s = (Selector*)lst[1]; s != 0; s = s->mpNext) {
            void* v = s->Slot2();
            if (v)
                map->FUN_009c1700(&v, RbtreeTrueType());
        }
    }
    map->FUN_00d3b370(*(void**)(tree + 0xc));
}

// @ 0x008f9fd0 CreateNameListPropertyFunc
NameListProp* CreateNameListPropertyFunc(EA::Allocator::StackAllocator* a, void* p2, void* p3, void* p4, void* p5,
                                         const wchar_t* name) {
    NameListProp* p = new (a) NameListProp(p2, p3, p4, p5);
    if (p->mCount < 8) {
        p->mNames[p->mCount] = name;
        p->mCount++;
    }
    return p;
}

// @ 0x008f9220 CSSParser::Parse
bool CSSParser::Parse(Stylesheet* pSheet) {
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

}  // namespace Style
}  // namespace XHTML
}  // namespace EA
