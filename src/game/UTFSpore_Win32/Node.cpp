// src/game/UTFSpore_Win32/Node.cpp -- migrated from slice(s) s008e4310 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Node.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/XHTML/DOM/IFormControlMgr.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
#pragma pack(push, 4)
#pragma pack(pop)

// ---- items of slice s008e4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Node;
struct Element;
struct Attr;
struct Node {                 // sizeof 0x18
    void* vftable;            // 0x00
    void* link0;              // 0x04
    void* link1;              // 0x08
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10  Document*
    void* mpParent;           // 0x14  Element*
    int      Type();                                // 0x00fc7e50
    Element* AsElement();                           // 0x008e52f0
    void*    Init(void* doc, int type);             // 0x008e52b0
};
struct IntList {
    void* link0;              // this+0 : first link
    void* link1;              // this+4 : last link
};
struct Link {                 // 0x14, Element::mpLink
    const u16* mpURI;         // 0x00
    const u16* mpName;        // 0x04
    u32        mLinkType;     // 0x08
    u32        mState;        // 0x0c
    u8         mbVisited;     // 0x10
    u8         _pad11[3];     // 0x11
};
struct Element : Node {       // sizeof 0x44
    IntList mChildNodes;      // 0x18
    IntList mAttributes;      // 0x20
    union {
        u32        mElementType;    // 0x28
        const u16* mpTagName;       // legacy alias used by the ctor bodies
    };
    union {
        u32 mResourceIndex;         // 0x2c
        int mnAttrId;
    };
    union {
        u32 mElementState;          // 0x30
        u32 mFlags30;
    };
    union {
        const u16* mpName;          // 0x34
        const u16* mpClassName;
    };
    union {
        const u16* mpId;            // 0x38
        const u16* mpIdValue;
    };
    union {
        const u16* mpClass;         // 0x3c
        const u16* mpNameValue;
    };
    union {
        Link* mpLink;               // 0x40
        void* mpExtra40;
    };

    __declspec(noinline) void HandleEvent(void* ev, int phase); // 0x008e4310
    void    AppendChild(Element* child);               // 0x008e4350
    void*   AppendAttr(Attr* attr);                    // 0x008e4380
    void*   ScalarDeletingDtor(u8 flags);              // 0x008e4450
    Element* FindChildNodeByName(const u16* name);     // 0x008e4480
    Attr*   GetAttr(const u16* name);                  // 0x008e4530
    __declspec(noinline) u16* GetAttrValue(const u16* name); // 0x008e45b0
    int     SetAttrValue(const u16*, const u16*, u8);  // 0x008e45d0
    void    SetAttrChecked(const u16*, const u16*);    // 0x008e46e0
    void    ReleaseChildren();                         // 0x008e48a0
    void    ReleaseChildren2();                        // 0x008e48f0
    void    CollectText(void* wstr);                   // 0x008e49e0
    void    OnAdded();                                 // 0x008e4a70
    void    OnRemoved();                               // 0x008e4a90
    void    DispatchA(void* a);                        // 0x008e4ab0
    u8      DispatchB(void* a);                        // 0x008e4ad0
    void    DispatchC(void* a);                        // 0x008e4af0
    u8      AddSubElement(const u16* name);            // 0x008e4b10
    void    Dtor2();                                   // 0x008e4ba0
    void    Dtor1();                                   // 0x008e4bd0
    void    GatherValues(void* a, void* b);            // 0x008e4f00
    Element* Ctor1(void* doc, const u16* tag);         // 0x008e4940
    Element* Ctor2(void* doc, void* tag);              // 0x008e4400
};
struct Attr {                 // sizeof 0x20
    void* vftable;            // 0x00
    void* link0;              // 0x04
    void* link1;              // 0x08
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10
    void* mpOwner;            // 0x14
    u16*  mpName;             // 0x18
    u16*  mpValue;            // 0x1c
};
// ---- items of slice s008e4310 end

// @ 0x008e52f0
Element* Node::AsElement()
{
    Node* self = this;
    return self->mnType == 1 ? (Element*)self : 0;
}
