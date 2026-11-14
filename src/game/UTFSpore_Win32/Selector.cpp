// src/game/UTFSpore_Win32/Selector.cpp
// Object file: UTFSpore_Win32/Selector.obj.

#include "game/types.h"

// unnamed retail callees (address in the comment)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" int wcscmp(const wchar_t*, const wchar_t*);

namespace EA {
namespace XHTML {
namespace DOM {

// Non-polymorphic DOM node (layout only).
class Node {
public:
    Node* Parent();                                    // 0x00ff0420
    const wchar_t* GetAttrValue(const wchar_t* name);  // 0x008e45b0

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
}  // namespace XHTML
}  // namespace EA

namespace EA {
namespace XHTML {
namespace Style {

using EA::XHTML::DOM::Node;

class Selector {
public:
    Selector() : mpNext(0) {}
    virtual ~Selector();
    virtual bool Match(Node* pNode, bool bDeep);
    virtual void* Slot2() { return 0; }

    Selector* mpNext;  // +0x4
};

class TagSelector : public Selector {
public:
    virtual ~TagSelector();
    virtual bool Match(Node* pNode, bool bDeep);

    const wchar_t* mName;  // +0x8
};

// vtable 0x014399e8
class ClassSelector : public Selector {  // vtable 0x014399e8
public:
    virtual ~ClassSelector();
    virtual bool Match(Node* pNode, bool bDeep);

    const wchar_t* mName;  // +0x8
    int mLength;           // +0xc
};

// vtable 0x014399f4
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

// vtable 0x01439a24
class AttrExistsSelector : public Selector {  // vtable 0x01439a24
public:
    virtual ~AttrExistsSelector();
    virtual bool Match(Node* pNode, bool bDeep);

    const wchar_t* mName;  // +0x8
};

// vtable 0x01439a30
class AttrEqualsSelector : public Selector {  // vtable 0x01439a30
public:
    virtual ~AttrEqualsSelector();
    virtual bool Match(Node* pNode, bool bDeep);

    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
};

// vtable 0x01439a3c
class AttrIncludesSelector : public Selector {  // vtable 0x01439a3c
public:
    virtual ~AttrIncludesSelector();
    virtual bool Match(Node* pNode, bool bDeep);

    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
    int mValueLen;          // +0x10
};

// vtable 0x01439a48
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

}  // namespace Style
}  // namespace XHTML
}  // namespace EA

namespace EA { namespace XHTML { namespace Style {

// Whitespace between class names in a "class" attribute, and the level
// separator inside a dash-separated attribute value (as in lang="en-US").
static const wchar_t kClassSeparator = L' ';
static const wchar_t kDashSeparator  = L'-';

// @ 0x008f96a0
int wmemcmp(const wchar_t* p1, const wchar_t* p2, unsigned int n)
{
    while (n > 0) {
        if (*p1 != *p2)
            return (*p1 < *p2) ? -1 : 1;
        ++p1;
        ++p2;
        --n;
    }
    return 0;
}

// @ 0x008f96e0
bool Selector::Match(Node* pNode, bool bDeep)
{
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9710
// True when pSub occurs in pString as a whole token delimited by ch (or a terminator).
__declspec(noinline) static bool StringContains(const wchar_t* pString, const wchar_t* pSub, unsigned int nLen, wchar_t ch)
{
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

// @ 0x008f9780
bool TagSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pTag = pNode->mpTagName;
    if (_wcsicmp(pTag, mName) != 0)
        return false;
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f97d0
bool ClassSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pAttr = pNode->GetAttrValue(L"class");
    if (!StringContains(pAttr, mName, mLength, kClassSeparator))
        return false;
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9830
bool IdSelector::Match(Node* pNode, bool bDeep)
{
    if (pNode->mpId == 0 || wcscmp(pNode->mpId, mName) != 0)
        return false;
    return mpNext == 0 || mpNext->Match(pNode, bDeep);
}

// @ 0x008f98a0
bool DescendantSelector::Match(Node* pNode, bool bDeep)
{
    Node* p = pNode->Parent();
    while (p != 0) {
        if (mChild->Match(p, bDeep))
            return !(mpNext != 0 && !mpNext->Match(p, bDeep));
        p = p->Parent();
    }
    return false;
}

// @ 0x008f9910
bool ChildSelector::Match(Node* pNode, bool bDeep)
{
    Node* p = pNode->Parent();
    if (p == 0 || mChild == 0)
        return false;
    return mChild->Match(p, bDeep) && (mpNext == 0 || mpNext->Match(pNode, bDeep));
}

// @ 0x008f9970
bool AttrExistsSelector::Match(Node* pNode, bool bDeep)
{
    return pNode->GetAttrValue(mName) != 0 && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f99c0
bool AttrEqualsSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* v = pNode->GetAttrValue(mName);
    return v != 0 && wcscmp(v, mValue) == 0 && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9a40
bool AttrIncludesSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pAttr = pNode->GetAttrValue(mName);
    return StringContains(pAttr, mValue, mValueLen, kClassSeparator) && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9aa0
bool AttrDashSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pAttr = pNode->GetAttrValue(mName);
    return StringContains(pAttr, mValue, mValueLen, kDashSeparator) && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}

// @ 0x008f9b00
bool PseudoSelector::Match(Node* pNode, bool bDeep)
{
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

}}}  // namespace EA::XHTML::Style
