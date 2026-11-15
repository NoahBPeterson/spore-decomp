// src/game/UTFSpore_Win32/StylesheetDefault.cpp -- migrated from slice(s) s008f9220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StylesheetDefault.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"

// ---- items of slice s008f9220 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
}  // namespace EA
}
inline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator_s008f_9220* a) {
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
class TypeSelector : public Selector {  // vtable 0x014399dc
public:
    TypeSelector(const wchar_t* name) : mName(name) {}
    virtual ~TypeSelector();
    virtual bool Match(Node* pNode, bool bDeep);
    const wchar_t* mName;  // +0x8
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
class RuleNode {
public:
    RuleNode(Selector* pSel, void* pDecl, int x);  // 0x008eb720
    void* mpNext;      // +0x0
    void* mpDecl;      // +0x4
    void* mpSel;       // +0x8
    void* mFieldc;     // +0xc
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct DeclHolder {  // 8-byte declaration holder
    void* a;  // +0x0
    void* b;  // +0x4
    DeclHolder() : a(0), b(0) {}
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
    void AddRule2(Selector* pSel, void* pDecl);       // 0x008f9c20
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
class NameListPropBase {
public:
    NameListPropBase() : mField4(0) {}
    virtual ~NameListPropBase() {}
    int mField4;  // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
NameListProp* CreateNameListPropertyFunc(EA::Allocator::StackAllocator_s008f_9220* a, void* p2, void* p3, void* p4, void* p5,
                                         const wchar_t* name);
}
}
}
// ---- items of slice s008f9220 end

// @ 0x008f9c20
namespace EA { namespace XHTML { namespace Style {
void Stylesheet_s008f_9220::AddRule2(Selector* pSel, void* pDecl)
{
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f9cd0
namespace EA { namespace XHTML { namespace Style {
void Stylesheet_s008f_9220::AddRule(const wchar_t* pName, void* pDecl)
{
    TypeSelector* pSel = new (&mAllocator) TypeSelector(pName);
    AddRule2(pSel, pDecl);
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9db0
namespace EA { namespace XHTML { namespace Style {
Stylesheet_s008f_9220::Stylesheet_s008f_9220(void* p)
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
}}}  // namespace EA::XHTML::Style

// @ 0x008f9fa0
namespace EA { namespace XHTML { namespace Style {
void Selector::Append(Selector* p)
{
    Selector* q = this;
    while (q->mpNext != 0)
        q = q->mpNext;
    q->mpNext = p;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9fd0
namespace EA { namespace XHTML { namespace Style {
NameListProp* CreateNameListPropertyFunc(EA::Allocator::StackAllocator_s008f_9220* a, void* p2, void* p3, void* p4, void* p5, const wchar_t* name)
{
    NameListProp* p = new (a) NameListProp(p2, p3, p4, p5);
    if (p->mCount < 8) {
        p->mNames[p->mCount] = name;
        p->mCount++;
    }
    return p;
}
}}}  // namespace EA::XHTML::Style
