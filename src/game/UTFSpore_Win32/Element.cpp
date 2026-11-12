// src/game/UTFSpore_Win32/Element.cpp -- migrated from slice(s) s008e4310 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Element.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/XHTML/DOM/IFormControlMgr.h"

// unnamed retail callees and globals (address in the comment)
extern "C" char g_vtbl_element[];      // 0x01436f60  Element vftable
extern "C" char g_w_013f3858[];        // 0x013f3858  L"id"    (literal in AppendAttr)
extern "C" char g_w_01436c8c[];        // 0x01436c8c  L"class" (literal in AppendAttr)
extern "C" void* g_wcsicmpPtr;         // 0x013cc50c  msvcr90!_wcsicmp
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern "C" void  operator_delete__(void* p);             // 0x00f47380
#pragma intrinsic(wcscmp)
#pragma pack(push, 4)
#pragma pack(pop)

// ---- items of slice s008e4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
extern "C" char g_vtbl_element[];      // 0x01436f60  Element vftable
extern "C" char g_w_013f3858[];        // 0x013f3858  L"id"    (literal in AppendAttr)
extern "C" char g_w_01436c8c[];        // 0x01436c8c  L"class" (literal in AppendAttr)
extern "C" void* g_wcsicmpPtr;         // 0x013cc50c  msvcr90!_wcsicmp
extern "C" const u16* g_pAttrId;        // 0x0154c604  -> L"id"
extern "C" const u16* g_pAttrClass;     // 0x0154c608  -> L"class"
extern "C" const u16* g_pAttrHref;      // 0x0154c60c  -> L"href"
extern "C" const u16* g_pAttrTarget;    // 0x0154c610  -> L"target"
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
void* Fn8e25d0(void* p, void* s, int f);                 // 0x008e25d0
u32   Fnfc7e50(void* n);                                 // 0x00fc7e50  Node::Type (free spelling)
void  Fn8e52e0(void* node);                              // 0x008e52e0  Node::~Node (thiscall)
void  Fn620230(void* list);                              // 0x00620230  IntrusiveList::~IntrusiveList (thiscall)
void  Fn1154f90(void* p);                                // 0x01154f90
void  Fn10829f0(void* self, void* v);                    // 0x010829f0
void* Fn8e2540(u32 n, void* alloc);                      // 0x008e2540 operator new(size, allocator*)
extern "C" void  operator_delete__(void* p);             // 0x00f47380
void* Fn8e52b0(void* self, void* doc, int type);         // 0x008e52b0  Node::Init (thiscall)
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
static __forceinline Node* ListHead(IntList* l) {
    void* p = l->link0;
    return (Node*)(p ? (char*)p - 4 : 0);
}
static __forceinline Node* ListNext(Node* n) {
    void* p = n->link0;
    return (Node*)(p ? (char*)p - 4 : 0);
}
static __forceinline Node* ListEndP(void* sentinel) {
    return (Node*)(sentinel ? (char*)sentinel - 4 : 0);
}
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

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" const u16* g_pAttrId;        // 0x0154c604  -> L"id"
extern "C" const u16* g_pAttrClass;     // 0x0154c608  -> L"class"
extern "C" const u16* g_pAttrHref;      // 0x0154c60c  -> L"href"
extern "C" const u16* g_pAttrTarget;    // 0x0154c610  -> L"target"
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);

// @ 0x008e4310
void Element::HandleEvent(void* ev, int phase)
{
    Element* self = this;
    if (phase != 1)
        return;
    if (self->mpParent != 0) {
        Element* p = (Element*)self->mpParent;
        ((void (__thiscall*)(Element*, void*, int))(*(void***)p)[0x24 / 4])(p, ev, 1);
        return;
    }
    void* doc = self->mpDocument;
    if (doc == 0)
        return;
    void* l = *(void**)((char*)doc + 0x3c);
    if (l == 0)
        return;
    ((void (__thiscall*)(void*, void*))(*(void***)l)[0x10 / 4])(l, ev);
}

// @ 0x008e4350
void Element::AppendChild(Element* child)
{
    Element* self = this;
    *(u8*)((char*)self->mpDocument + 0x2c) = 1;
    void* p = child;
    void* s = (char*)self + 0x18;
    void* prev = *(void**)((char*)s + 4);
    *(void**)((char*)p + 8) = prev;
    void* link = (char*)p + 4;
    *(void**)link = s;
    *(void**)((char*)s + 4) = link;
    *(void**)*(void**)((char*)p + 8) = link;
    *(void**)((char*)p + 0x14) = self;
}

// @ 0x008e4380
void* Element::AppendAttr(Attr* attr)
{
    Element* self = this;
    int (__cdecl* wcsicmp)(const u16*, const u16*) = (int (__cdecl*)(const u16*, const u16*))g_wcsicmpPtr;
    *(u8*)((char*)self->mpDocument + 0x2c) = 1;
    void* prev = self->mAttributes.link1;
    void* sentinel = (char*)self + 0x20;
    *(void**)((char*)attr + 8) = prev;
    void* link = (char*)attr + 4;
    *(void**)link = sentinel;
    *(void**)((char*)sentinel + 4) = link;
    *(void**)*(void**)((char*)attr + 8) = link;
    if (wcsicmp(attr->mpName, (const u16*)g_w_013f3858) == 0) {
        self->mpIdValue = attr->mpValue;
    } else if (wcsicmp(attr->mpName, (const u16*)g_w_01436c8c) == 0) {
        self->mpNameValue = attr->mpValue;
    }
    ((void (__thiscall*)(Element*, u16*, u16*))(*(void***)self)[0x30 / 4])(self, attr->mpName, attr->mpValue);
    return attr;
}

// @ 0x008e4400
Element* Element::Ctor2(void* doc, void* tag)
{
    Element* self = this;
    ((void (__thiscall*)(void*, void*, int))Fn8e52b0)(self, doc, 1);
    self->vftable = (void*)g_vtbl_element;
    *(void**)((char*)self + 0x1c) = (char*)self + 0x18;
    *(void**)((char*)self + 0x18) = (char*)self + 0x18;
    *(void**)((char*)self + 0x24) = (char*)self + 0x20;
    *(void**)((char*)self + 0x20) = (char*)self + 0x20;
    self->mFlags30 = 0;
    self->mpIdValue = 0;
    self->mpNameValue = 0;
    self->mpExtra40 = 0;
    self->mpTagName = (const u16*)tag;
    self->mnAttrId = -1;
    self->mpClassName = (const u16*)doc;
    return self;
}

// @ 0x008e4450
void* Element::ScalarDeletingDtor(u8 flags)
{
    Element* self = this;
    ((void (__thiscall*)(void*))Fn620230)((char*)self + 0x20);
    ((void (__thiscall*)(void*))Fn620230)((char*)self + 0x18);
    ((void (__thiscall*)(void*))Fn8e52e0)(self);
    if ((flags & 1) != 0)
        operator_delete__(self);
    return self;
}

// @ 0x008e4480
Element* Element::FindChildNodeByName(const u16* name)
{
    Element* self = this;
    void* end = (char*)self + 0x18;
    IntList* list = (IntList*)end;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (Fnfc7e50(n) == 1) {
            Element* e = (Element*)n;
            const u16* a = e->mpTagName;
            const u16* b = name;
            int d;
            for (;;) {
                u16 c0 = *b;
                if (c0 != *a) { d = 1; goto done; }
                if (c0 == 0) { d = 0; goto done; }
                u16 c1 = b[1];
                if (c1 != a[1]) { d = 1; goto done; }
                b += 2; a += 2;
                if (c1 == 0) { d = 0; goto done; }
            }
        done:
            if (d == 0)
                return e;
        }
    }
    return 0;
}

// @ 0x008e4530
Attr* Element::GetAttr(const u16* name)
{
    Element* self = this;
    void* end = (char*)self + 0x20;
    IntList* list = (IntList*)end;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        Attr* a = (Attr*)n;
        const u16* t = a->mpName;
        const u16* q = name;
        int d;
        for (;;) {
            u16 c0 = *q;
            if (c0 != *t) { d = 1; goto done; }
            if (c0 == 0) { d = 0; goto done; }
            u16 c1 = q[1];
            if (c1 != t[1]) { d = 1; goto done; }
            q += 2; t += 2;
            if (c1 == 0) { d = 0; goto done; }
        }
    done:
        if (d == 0)
            return a;
    }
    return 0;
}

// @ 0x008e45b0
u16* Element::GetAttrValue(const u16* name)
{
    Element* self = this;
    Attr* a = self->GetAttr( name);
    return a ? a->mpValue : 0;
}

// @ 0x008e45d0
int Element::SetAttrValue(const u16* name, const u16* value, u8 removeOrAdd)
{
    Element* self = this;
    Attr* a = self->GetAttr( name);
    if (value == 0) {
        if (a == 0)
            return 0;
        *(u8*)((char*)self->mpDocument + 0x2c) = 1;
        ((void (__thiscall*)(Element*, u16*, u16*))(*(void***)self)[0x30 / 4])(self, a->mpName, a->mpValue);
        *(void**)* (void**)((char*)a + 8) = *(void**)((char*)a + 4);
           *(void**)(*(u32*)((char*)a + 4) + 4) = *(void**)((char*)a + 8);
        *(u32*)((char*)a + 4) = 0;
        *(u32*)((char*)a + 8) = 0;
        Fn1154f90(a);
        return 0;
    }
    if (a != 0) {
        const u16* t = a->mpValue;
        const u16* q = value;
        int d;
        for (;;) {
            u16 c0 = *q;
            if (c0 != *t) { d = 1; goto done; }
            if (c0 == 0) { d = 0; goto done; }
            u16 c1 = q[1];
            if (c1 != t[1]) { d = 1; goto done; }
            q += 2; t += 2;
            if (c1 == 0) { d = 0; goto done; }
        }
    done:
        if (d == 0)
            return 0;
        if (removeOrAdd != 0) {
            void* doc = self->mpDocument;
            value = (const u16*)Fn8e25d0(doc, (void*)value, -1);
        }
        if (value == 0)
            return 0;
        Fn10829f0(self->mpDocument, a->mpValue);
    }
    return 0;
}

// @ 0x008e46e0
void Element::SetAttrChecked(const u16* name, const u16* value)
{
    Element* self = this;
    if (wcscmp((const wchar_t*)name, (const wchar_t*)g_pAttrId) == 0) {
        self->mpIdValue = value;
        return;
    }
    if (wcscmp((const wchar_t*)name, (const wchar_t*)g_pAttrClass) == 0) {
        self->mpNameValue = value;
        return;
    }
    if (wcscmp((const wchar_t*)name, (const wchar_t*)g_pAttrHref) == 0) {
        if (value != 0) {
            if (self->mpLink == 0) {
                Link* link = (Link*)Fn8e2540(0x14, (char*)self->mpDocument + 8);
                if (link != 0) {
                    link->mpURI = 0;
                    link->mLinkType = 0;
                    link->mState = 0;
                    link->mbVisited = 0;
                } else {
                    link = 0;
                }
                self->mpLink = link;
            }
            self->mpLink->mLinkType = 1;
            self->mpLink->mState = 1;
            self->mpLink->mpURI = value;
            Attr* a = self->GetAttr(g_pAttrTarget);
            self->mpLink->mpName = a != 0 ? a->mpValue : 0;
        } else if (self->mpLink != 0) {
            self->mpLink->mLinkType = 0;
            self->mpLink->mpURI = 0;
            self->mpLink->mpName = 0;
        }
        return;
    }
    if (wcscmp((const wchar_t*)name, (const wchar_t*)g_pAttrTarget) == 0 && self->mpLink != 0)
        self->mpLink->mpName = value;
}
