// slice s008e4310 (part b): EA::XHTML::DOM element tree query.
//   0x008e4480  Element::FindChildNodeByName(const wchar_t* name, Node* start): walks the child
//               intrusive list (from the first child, or from the successor of `start`), compares each
//               element child's mpName two wchars at a time and returns Node::AsElement of the match.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GR- /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;

struct Element;

// eastl::intrusive_list_node lives at Node+4 (Node has a vftable at +0), so a link pointer maps to
// the containing Node by subtracting 4.  The list anchor itself is at the list address; the binary
// keeps it in a register and does the -4 at each comparison.
struct Node {                 // 0x18
    void* vftable;            // 0x00
    void* link0;              // 0x04  intrusive_list_node::mpNext
    void* link1;              // 0x08  intrusive_list_node::mpPrev
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10
    void* mpParent;           // 0x14
    u32      Type();          // 0x00fc7e50
    Element* AsElement();     // 0x008e52f0
};

struct IntList {
    void* link0;              // +0
    void* link1;              // +4
};

static __forceinline Node* ListHead(IntList* l)
{
    Node* n = (Node*)l->link0;
    return n ? (Node*)((char*)n - 4) : 0;
}
static __forceinline Node* ListNext(Node* n)
{
    void* p = n->link0;
    return (Node*)(p ? (char*)p - 4 : 0);
}
static __forceinline Node* ListEndP(void* sentinel)
{
    return (Node*)(sentinel ? (char*)sentinel - 4 : 0);
}

struct Element : Node {       // 0x44
    IntList mChildNodes;      // 0x18
    IntList mAttributes;      // 0x20
    u32     mElementType;     // 0x28
    u32     mResourceIndex;   // 0x2c
    u32     mElementState;    // 0x30
    u16*    mpName;           // 0x34
    u16*    mpId;             // 0x38
    u16*    mpClass;          // 0x3c
    void*   mpLink;           // 0x40

    Element* FindChildNodeByName(const u16* name, Node* start);   // 0x008e4480
};

// MSVC expands wcscmp inline (compiler intrinsic: two characters per pass, sbb result);
// the original's compare loop is that expansion.
#pragma intrinsic(wcscmp)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);

// @ 0x008e4480
Element* Element::FindChildNodeByName(const u16* name, Node* start)
{
    Node* n = ListHead((IntList*)((char*)this + 0x18));
    if (start)
        n = ListNext(start);

    for (; n != ListEndP((char*)this + 0x18); n = ListNext(n))
    {
        if (n->Type() == 1)
        {
            const u16* a = static_cast<Element*>(n)->mpName;
            if (wcscmp((const wchar_t*)name, (const wchar_t*)a) == 0)
                return n->AsElement();
        }
    }
    return 0;
}
