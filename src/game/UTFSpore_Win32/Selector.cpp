// src/game/UTFSpore_Win32/Selector.cpp -- migrated from slice(s) s008f9220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Selector.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" int wcscmp(const wchar_t*, const wchar_t*);
extern "C" int wmemcmp(const wchar_t*, const wchar_t*, unsigned int);

// ---- items of slice s008f9220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" int wcscmp(const wchar_t*, const wchar_t*);
extern "C" int wmemcmp(const wchar_t*, const wchar_t*, unsigned int);
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
class Selector {
public:
    Selector() : mpNext(0) {}
    virtual ~Selector();
    virtual bool Match(Node* pNode, bool bDeep);
    virtual void* Slot2() { return 0; }
    void Append(Selector* p);   // 0x008f9fa0
    Selector* mpNext;           // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class TagSelector : public Selector {
public:
    virtual ~TagSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class ClassSelector : public Selector {  // vtable 0x014399e8
public:
    virtual ~ClassSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
    int mLength;           // +0xc
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class IdSelector : public Selector {  // vtable 0x014399f4
public:
    virtual ~IdSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class DescendantSelector : public Selector {
public:
    virtual ~DescendantSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    Selector* mChild;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class ChildSelector : public Selector {
public:
    virtual ~ChildSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    Selector* mChild;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrExistsSelector : public Selector {  // vtable 0x01439a24
public:
    virtual ~AttrExistsSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrEqualsSelector : public Selector {  // vtable 0x01439a30
public:
    virtual ~AttrEqualsSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrIncludesSelector : public Selector {  // vtable 0x01439a3c
public:
    virtual ~AttrIncludesSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
    int mValueLen;          // +0x10
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class AttrDashSelector : public Selector {  // vtable 0x01439a48
public:
    virtual ~AttrDashSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;   // +0x8
    const wchar_t* mValue;  // +0xc
    int mValueLen;          // +0x10
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class PseudoSelector : public Selector {
public:
    virtual ~PseudoSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    int mKind;  // +0x8
};
}
}
}
// ---- items of slice s008f9220 end

// @ 0x008f96a0
namespace EA { namespace XHTML { namespace Style {
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f96e0
namespace EA { namespace XHTML { namespace Style {
bool Selector::Match(Node* pNode, bool bDeep)
{
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9710
namespace EA { namespace XHTML { namespace Style {
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f9780
namespace EA { namespace XHTML { namespace Style {
bool TagSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pTag = pNode->mpTagName;
    if (_wcsicmp(pTag, mName) != 0)
        return false;
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f97d0
namespace EA { namespace XHTML { namespace Style {
bool ClassSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pAttr = pNode->GetAttrValue(L"class");
    if (!StringContains(pAttr, mName, mLength, L' '))
        return false;
    return !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9830
namespace EA { namespace XHTML { namespace Style {
bool IdSelector::Match(Node* pNode, bool bDeep)
{
    if (pNode->mpId == 0 || wcscmp(pNode->mpId, mName) != 0)
        return false;
    return mpNext == 0 || mpNext->Match(pNode, bDeep);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f98a0
namespace EA { namespace XHTML { namespace Style {
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f9910
namespace EA { namespace XHTML { namespace Style {
bool ChildSelector::Match(Node* pNode, bool bDeep)
{
    Node* p = pNode->Parent();
    if (p == 0 || mChild == 0)
        return false;
    return mChild->Match(p, bDeep) && (mpNext == 0 || mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9970
namespace EA { namespace XHTML { namespace Style {
bool AttrExistsSelector::Match(Node* pNode, bool bDeep)
{
    return pNode->GetAttrValue(mName) != 0 && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f99c0
namespace EA { namespace XHTML { namespace Style {
bool AttrEqualsSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* v = pNode->GetAttrValue(mName);
    return v != 0 && wcscmp(v, mValue) == 0 && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9a40
namespace EA { namespace XHTML { namespace Style {
bool AttrIncludesSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pAttr = pNode->GetAttrValue(mName);
    return StringContains(pAttr, mValue, mValueLen, L' ') && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9aa0
namespace EA { namespace XHTML { namespace Style {
bool AttrDashSelector::Match(Node* pNode, bool bDeep)
{
    const wchar_t* pAttr = pNode->GetAttrValue(mName);
    return StringContains(pAttr, mValue, mValueLen, L'-') && !(mpNext != 0 && !mpNext->Match(pNode, bDeep));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9b00
namespace EA { namespace XHTML { namespace Style {
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
