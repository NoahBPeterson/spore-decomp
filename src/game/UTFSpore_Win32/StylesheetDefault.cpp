// src/game/UTFSpore_Win32/StylesheetDefault.cpp -- migrated from slice(s) s008f9220 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StylesheetDefault.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"

// ---- items of slice s008f9220 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s008f9220 end

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
