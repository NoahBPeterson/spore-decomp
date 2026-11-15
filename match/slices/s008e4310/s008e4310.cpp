// Slice s008e4310 -- EA::XHTML::DOM Element / Attr / Form (SporeApp.exe)
// Reconstructed from the PDB layouts and the retail disassembly.
// Build: /O2 /MD /Gy /TP /arch:SSE /GR- /fp:fast

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

// ---- globals (absolute VAs) -----------------------------------------------
extern "C" char g_vtbl_element[];      // 0x01436f60  Element vftable
extern "C" char g_vft_008e49e0[];      // 0x01436f60  (shared Element ctor vftable)
extern "C" char g_vtbl_element2[];      // 0x013fcc88  Form-ish vftable
extern "C" char g_vtbl_element3[];      // 0x01436d60
extern "C" char g_vtbl_node[];      // 0x01436fd0  Node vftable
extern "C" char g_w_013f3858[];        // 0x013f3858  L"id"    (literal in AppendAttr)
extern "C" char g_w_01436c8c[];        // 0x01436c8c  L"class" (literal in AppendAttr)
extern "C" char g_wstr_src[];        // 0x0154c6ec  "src" attribute name
extern "C" char g_defs_b[];             // 0x0154c618
extern "C" char g_defs_c[];             // 0x0154c6e8
extern "C" void* g_wcsicmpPtr;         // 0x013cc50c  msvcr90!_wcsicmp

// Attribute-name pointer variables (retail dereferences these const wchar_t*).
extern "C" const u16* g_pAttrId;        // 0x0154c604  -> L"id"
extern "C" const u16* g_pAttrClass;     // 0x0154c608  -> L"class"
extern "C" const u16* g_pAttrHref;      // 0x0154c60c  -> L"href"
extern "C" const u16* g_pAttrTarget;    // 0x0154c610  -> L"target"
extern "C" const u16* g_pAttrDisabled;  // 0x0154c6f4  -> L"disabled"
extern "C" const u16* g_pAttrName;      // 0x0154c6f8  -> L"name"
extern "C" const u16* g_pAttrType;      // 0x0154c6fc  -> L"type"
extern "C" const u16* g_pAttrValue;     // 0x0154c700  -> L"value"
extern "C" const u16* g_pAttrChecked;   // 0x0154c704  -> L"checked"
extern "C" const u16* g_pAttrCheckbox;  // 0x0154c714  -> L"checkbox"
extern "C" const u16* g_pAttrRadio;     // 0x0154c718  -> L"radio"
extern "C" u16 g_wEmpty[];              // 0x01667bac  L""
extern "C" u16 g_wEmptyLiteral[];       // 0x013ec468  L""
extern "C" void* g_pEmptyBuckets[2];    // 0x0154df28  eastl empty bucket array {0, -1}

// ---- CRT imports ----------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)

// ---- real callees ---------------------------------------------------------
void* Fn8e25d0(void* p, void* s, int f);                 // 0x008e25d0
u32   Fnfc7e50(void* n);                                 // 0x00fc7e50  Node::Type (free spelling)

void  Fn8f3790(void* out, const void* first, const void* last, const void* key); // 0x008f3790
void  Fn8e52e0(void* node);                              // 0x008e52e0  Node::~Node (thiscall)
void  Fn620230(void* list);                              // 0x00620230  IntrusiveList::~IntrusiveList (thiscall)
void  Fn1154f90(void* p);                                // 0x01154f90
void  Fn10829f0(void* self, void* v);                    // 0x010829f0
void* Fn8e2540(u32 n, void* alloc);                      // 0x008e2540 operator new(size, allocator*)
void* Fn8e3fa0(void** a, u16* b, u16* c);                // 0x008e3fa0
void  Fn429580(void* wstr, const u16* b, const u16* e);  // 0x00429580  WStr::Append
void  Fn011e0744(void* d, const void* s, u32 n);         // 0x011e0744 memcpy

extern "C" void  operator_delete__(void* p);             // 0x00f47380
void* Fn8e52b0(void* self, void* doc, int type);         // 0x008e52b0  Node::Init (thiscall)

// ---- layouts (PDB-derived, retail offsets) --------------------------------
#pragma pack(push, 4)
struct Node;
struct Element;
struct Attr;
struct Document;
struct IFormControlMgr;
struct WStr16;

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
// eastl intrusive-list iterator helpers, spelled out so the compiler emits the
// same `lea reg,[p-4]` / `test reg,reg` shape as the original.
// The original keeps `end = (Node*)((char*)this + off)` in a register and does
// the `-4` at each comparison; these helpers mirror that when used inline.
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

struct WStr16 {               // 0x0c, eastl::basic_string<wchar_t> header
    u16* mpBegin;             // 0x00
    u16* mpEnd;               // 0x04
    u16* mpCapacity;          // 0x08
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

struct Document {             // sizeof 0x50
    u32 mField00[2];          // 0x00
    u8  mAllocator[0x24];     // 0x08  allocator block (only its address is used)
    u8  mbDocumentChanged;    // 0x2c
    u8  _pad2d[3];            // 0x2d
    u32 mField30;             // 0x30
    u32 mField34;             // 0x34
    IFormControlMgr* mpFormControlMgr; // 0x38
    void* mpEventListener;    // 0x3c
    u32 mField40;             // 0x40
    u32 mField44;             // 0x44
    const u16* mpDocumentURI; // 0x48
    const u16* mpBaseURI;     // 0x4c
};

struct IFormControlMgr {
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14();
    virtual void GetValue(Element* elem, WStr16* value);      // +0x18
    virtual void SetValue(Element* elem, const u16* value);   // +0x1c
};

// eastl::hash_map<const wchar_t*, const wchar_t*> (0x20 bytes)
namespace Style {
struct CounterMap {
    struct node { const wchar_t* key; const wchar_t* value; node* mpNext; };
    struct iterator {
        node*  mpNode;        // +0
        node** mpBucket;      // +4
        iterator(node* n, node** b) : mpNode(n), mpBucket(b) {}
        iterator() {}
        iterator(node** b) : mpNode(*b), mpBucket(b) {}
        iterator(const iterator& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
    };
    u32    mField00;          // 0x00
    node** mpBucketArray;     // 0x04
    u32    mnBucketCount;     // 0x08
    u32    mnElementCount;    // 0x0c
    float  mfMaxLoadFactor;   // 0x10
    float  mfGrowthFactor;    // 0x14
    u32    mnNextResize;      // 0x18
    u32    mField1c;          // 0x1c
    iterator find(const wchar_t* const& k);                     // 0x008fbbf0
    const wchar_t*& operator[](const wchar_t* const& k);        // 0x008fc610
    void DoFreeBuckets(node** pBuckets, u32 nCount);            // 0x00693230
};
}

struct Form : Element {       // sizeof 0x48
    Element* mpActiveSubmit;  // 0x44
    void GatherControlValues(Element* elem, void* cb, void* ctx, void* arg4); // 0x008e4ce0
    void ResetControlValues(Element* elem, Style::CounterMap* map);          // 0x008e4f20
    void Reset();                                                            // 0x008e5130
    void ExcludeGroups(Element* elem, const u16* group, const u16* value);   // 0x008e4c00
    void HandleEvent(void* ev, int arg);                                     // 0x008e5210
};
#pragma pack(pop)

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
    if (a == 0)
        return 0;
    return a->mpValue;
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

// @ 0x008e48a0
void Element::ReleaseChildren()
{
    Element* self = this;
    void* end = (char*)self + 0x18;
    IntList* list = (IntList*)end;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (Fnfc7e50(n) == 1)
            ((void (__thiscall*)(Node*))(*(void***)n)[0x28 / 4])(n);
    }
}

// @ 0x008e48f0
void Element::ReleaseChildren2()
{
    Element* self = this;
    void* end = (char*)self + 0x18;
    IntList* list = (IntList*)end;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (Fnfc7e50(n) == 1)
            ((void (__thiscall*)(Node*))(*(void***)n)[0x2c / 4])(n);
    }
}

// @ 0x008e4940
Element* Element::Ctor1(void* doc, const u16* tag)
{
    Element* self = this;
    ((void (__thiscall*)(void*, void*, int))Fn8e52b0)(self, doc, 1);
    self->vftable = (void*)g_vtbl_element;
    *(void**)((char*)self + 0x1c) = (char*)self + 0x18;
    *(void**)((char*)self + 0x18) = (char*)self + 0x18;
    *(void**)((char*)self + 0x24) = (char*)self + 0x20;
    *(void**)((char*)self + 0x20) = (char*)self + 0x20;
    self->mpTagName = tag;
    self->mnAttrId = -1;
    self->mFlags30 = 0;
    self->mpIdValue = 0;
    self->mpNameValue = 0;
    self->mpExtra40 = 0;
    void* r;
    Fn8f3790(&r, g_defs_b, g_defs_c, &tag);
    if ((char*)r + 8 == *(char**)&r)
        self->mpTagName = *(const u16**)((char*)r + 4);
    else
        self->mpTagName = tag;
    return self;
}

// @ 0x008e49e0
void Element::CollectText(void* wstr)
{
    Element* self = this;
    void* end = (char*)self + 0x18;
    IntList* list = (IntList*)end;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (Fnfc7e50(n) == 1) {
            ((void (__thiscall*)(Node*, void*))(*(void***)n)[0x8 / 4])(n, wstr);
        } else if (Fnfc7e50(n) == 2) {
            u16* b = *(u16**)((char*)n + 0x18);
            u16* e = (u16*)((char*)b + *(u32*)((char*)n + 0x1c) * 2);
            Fn429580(wstr, b, e);
        }
    }
}

// @ 0x008e4a70
void Element::OnAdded()
{
    Element* self = this;
    self->ReleaseChildren();
    void* l = *(void**)((char*)self->mpDocument + 0x38);
    ((void (__thiscall*)(void*, Element*))(*(void***)l)[0x10 / 4])(l, self);
}

// @ 0x008e4a90
void Element::OnRemoved()
{
    Element* self = this;
    self->ReleaseChildren2();
    void* l = *(void**)((char*)self->mpDocument + 0x38);
    ((void (__thiscall*)(void*, Element*))(*(void***)l)[0x14 / 4])(l, self);
}

// @ 0x008e4ab0
void Element::DispatchA(void* a)
{
    Element* self = this;
    void* l = *(void**)((char*)self->mpDocument + 0x38);
    ((void (__thiscall*)(void*, Element*, void*))(*(void***)l)[0x20 / 4])(l, self, a);
}

// @ 0x008e4ad0
u8 Element::DispatchB(void* a)
{
    Element* self = this;
    void* l = *(void**)((char*)self->mpDocument + 0x38);
    ((void (__thiscall*)(void*, Element*, void*))(*(void***)l)[0x24 / 4])(l, self, a);
    return 1;
}

// @ 0x008e4af0
void Element::DispatchC(void* a)
{
    Element* self = this;
    void* l = *(void**)((char*)self->mpDocument + 0x38);
    ((void (__thiscall*)(void*, Element*, void*))(*(void***)l)[0x28 / 4])(l, self, a);
}

// @ 0x008e4b10
u8 Element::AddSubElement(const u16* name)
{
    Element* self = this;
    const u16* v = self->GetAttrValue( (const u16*)g_wstr_src);
    if (v == 0)
        return 0;
    void* doc = self->mpDocument;
    if (doc == 0)
        return 0;
    void* p = *(void**)((char*)doc + 0x4c);
    void* q;
    if (p != 0) q = p; else q = *(void**)((char*)doc + 0x48);
    Fn8e3fa0((void**)q, (u16*)self, (u16*)v);
    return 1;
}

// @ 0x008e4ba0
void Element::Dtor2()
{
    Element* self = this;
    *(void* volatile*)&self->vftable = (void*)g_vtbl_element2;
    void* p = *(void* volatile*)((char*)self + 0x44);
    if (p != 0)
        ((void (__thiscall*)(void*))(*(void***)p)[0x4 / 4])(p);
    ((void (__thiscall*)(void*))Fn620230)((char*)self + 0x20);
    ((void (__thiscall*)(void*))Fn620230)((char*)self + 0x18);
    ((void (__thiscall*)(void*))Fn8e52e0)(self);
}

// @ 0x008e4bd0
void Element::Dtor1()
{
    Element* self = this;
    void* pf = (void*)g_vtbl_element3;
    ((void (__thiscall*)(void*))Fn620230)((char*)self + 0x20);
    *(void* volatile*)&self->vftable = pf;
    ((void (__thiscall*)(void*))Fn620230)((char*)self + 0x18);
    ((void (__thiscall*)(void*))Fn8e52e0)(self);
}

// @ 0x008e4c00
void Form::ExcludeGroups(Element* elem, const u16* group, const u16* value)
{
    Form* self = this;
    IFormControlMgr* mgr = (IFormControlMgr*)((Document*)self->mpDocument)->mpFormControlMgr;
    if (((u8 (__thiscall*)(Element*))(*(void***)elem)[0x18 / 4])(elem) != 0 &&
        elem->mElementType == 0x17) {
        const u16* type = elem->GetAttrValue(g_pAttrType);
        const u16* name = elem->GetAttrValue(g_pAttrName);
        if (_wcsicmp((const wchar_t*)type, (const wchar_t*)g_pAttrRadio) == 0 &&
            _wcsicmp((const wchar_t*)group, (const wchar_t*)name) == 0)
            mgr->SetValue(elem, value);
    }
    IntList* list = &elem->mChildNodes;
    void* end = (char*)elem + 0x18;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (n->Type() == 1)
            self->ExcludeGroups((Element*)n, group, value);
    }
}

typedef void (__cdecl* GatherCallback)(const u16*, const u16*, void*);

// @ 0x008e4ce0
void Form::GatherControlValues(Element* elem, void* cb, void* ctx, void* arg4)
{
    Form* self = this;
    IFormControlMgr* mgr;
    WStr16 str;
    u32 elementType;
    const u16* type;
    const u16* value;
    const u16* name;

    if (((u8 (__thiscall*)(Element*))(*(void***)elem)[0x18 / 4])(elem) == 0)
        goto children;
    if (elem->GetAttr(g_pAttrDisabled) != 0)
        goto children;
    mgr = (IFormControlMgr*)((Document*)elem->mpDocument)->mpFormControlMgr;
    elementType = elem->mElementType;
    str.mpBegin = g_wEmpty;
    str.mpEnd = g_wEmpty;
    str.mpCapacity = g_wEmpty + 1;
    if (elementType == 0x17) {
        type = elem->GetAttrValue(g_pAttrType);
        if (type == 0) goto collect;
        if (_wcsicmp((const wchar_t*)type, L"text") == 0) goto collect;
        if (_wcsicmp((const wchar_t*)type, L"password") == 0) goto collect;
        if (_wcsicmp((const wchar_t*)type, L"hidden") == 0) goto collect;
        if (_wcsicmp((const wchar_t*)type, L"checkbox") == 0) goto collectChecked;
        if (_wcsicmp((const wchar_t*)type, L"radio") == 0) goto collectChecked;
        if (_wcsicmp((const wchar_t*)type, L"submit") != 0) {
            if (_wcsicmp((const wchar_t*)type, L"file") != 0)
                _wcsicmp((const wchar_t*)type, L"image");
            goto done;
        }
        value = elem->GetAttrValue(g_pAttrValue);
        name = elem->GetAttrValue(g_pAttrName);
        if (value == 0 || name == 0 || elem != self->mpActiveSubmit)
            goto done;
        ((GatherCallback)cb)(name, value, ctx);
        goto done;
    } else if (elementType != 0x18 && elementType != 0x1a) {
        goto done;
    }
collect:
    mgr->GetValue(elem, &str);
    ((GatherCallback)cb)(elem->GetAttrValue(g_pAttrName), str.mpBegin, ctx);
    goto done;
collectChecked:
    mgr->GetValue(elem, &str);
    if (str.mpBegin != str.mpEnd)
        ((GatherCallback)cb)(elem->GetAttrValue(g_pAttrName), str.mpBegin, ctx);
done:
    if ((int)(((u32)str.mpCapacity - (u32)str.mpBegin) & 0xfffffffeu) > 2 && str.mpBegin != 0)
        operator_delete__(str.mpBegin);
children:
    {
        IntList* list = &elem->mChildNodes;
        void* end = (char*)elem + 0x18;
        for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
            if (n->Type() == 1)
                self->GatherControlValues((Element*)n, cb, ctx, arg4);
        }
    }
}

// @ 0x008e4f00
void Element::GatherValues(void* a, void* b)
{
    Element* self = this;
    ((Form*)self)->GatherControlValues(self, a, b, 0);
}

// @ 0x008e4f20
void Form::ResetControlValues(Element* elem, Style::CounterMap* map)
{
    Form* self = this;
    IFormControlMgr* mgr = (IFormControlMgr*)((Document*)self->mpDocument)->mpFormControlMgr;
    if (((u8 (__thiscall*)(Element*))(*(void***)elem)[0x18 / 4])(elem) != 0) {
        switch (elem->mElementType) {
        case 0x17: {
            const u16* type = elem->GetAttrValue(g_pAttrType);
            const u16* value = elem->GetAttrValue(g_pAttrValue);
            if (_wcsicmp((const wchar_t*)type, (const wchar_t*)g_pAttrCheckbox) == 0) {
                const u16* checked = elem->GetAttrValue(g_pAttrChecked);
                mgr->SetValue(elem, checked != 0 ? value : 0);
            } else if (_wcsicmp((const wchar_t*)type, (const wchar_t*)g_pAttrRadio) == 0) {
                const wchar_t* name = (const wchar_t*)elem->GetAttrValue(g_pAttrName);
                const u16* checked = elem->GetAttrValue(g_pAttrChecked);
                if (name != 0 && value != 0) {
                    Style::CounterMap::iterator it = map->find(name);
                    if (it.mpNode == map->mpBucketArray[map->mnBucketCount] || checked != 0)
                        (*map)[name] = (const wchar_t*)value;
                }
            } else {
                mgr->SetValue(elem, value != 0 ? value : g_wEmptyLiteral);
            }
            break;
        }
        case 0x18: {
            const u16* value = elem->GetAttrValue(g_pAttrValue);
            mgr->SetValue(elem, value != 0 ? value : g_wEmptyLiteral);
            break;
        }
        case 0x1a: {
            void (__thiscall* collect)(Element*, WStr16*) =
                (void (__thiscall*)(Element*, WStr16*))(*(void***)elem)[0x8 / 4];
            WStr16 str;
            str.mpBegin = g_wEmpty;
            str.mpEnd = g_wEmpty;
            str.mpCapacity = g_wEmpty + 1;
            collect(elem, &str);
            mgr->SetValue(elem, str.mpBegin);
            if ((int)(((u32)str.mpCapacity - (u32)str.mpBegin) & 0xfffffffeu) > 2 && str.mpBegin != 0)
                operator_delete__(str.mpBegin);
            break;
        }
        }
    }
    IntList* list = &elem->mChildNodes;
    void* end = (char*)elem + 0x18;
    for (Node* n = ListHead(list); n != ListEndP(end); n = ListNext(n)) {
        if (n->Type() == 1)
            self->ResetControlValues((Element*)n, map);
    }
}

// @ 0x008e5130
void Form::Reset()
{
    Style::CounterMap map;
    map.mfMaxLoadFactor = 1.0f;
    map.mfGrowthFactor = 2.0f;
    map.mnBucketCount = 1;
    map.mpBucketArray = (Style::CounterMap::node**)g_pEmptyBuckets;
    map.mnElementCount = 0;
    map.mnNextResize = 0;
    ResetControlValues(this, &map);

    Style::CounterMap::node** pb = map.mpBucketArray;
    Style::CounterMap::node* p = *pb;
    if (p == 0) {
        ++pb;
        while (*pb == 0)
            ++pb;
        p = *pb;
    }
    while (p != map.mpBucketArray[map.mnBucketCount]) {
        ExcludeGroups(this, (const u16*)p->key, (const u16*)p->value);
        p = p->mpNext;
        if (p == 0) {
            while ((p = *++pb) == 0) {}
        }
    }
    map.DoFreeBuckets(map.mpBucketArray, map.mnBucketCount);
    map.mnElementCount = 0;
    if (map.mnBucketCount > 1)
        operator_delete__(map.mpBucketArray);
}

// @ 0x008e5210
void Form::HandleEvent(void* ev, int arg)
{
    Form* self = this;
    u32 phase = ((u32*)ev)[1];
    if (phase == 3) {
        self->mpActiveSubmit = 0;
        self->Reset();
        return;
    }
    if (phase == 2) {
        self->mpActiveSubmit = (Element*)((u32*)ev)[0];
        ((u32*)ev)[1] = 4;
        ((u32*)ev)[0] = (u32)self;
    } else if (phase == 5) {
        Element* elem = (Element*)((u32*)ev)[0];
        if (elem != 0) {
            const u16* name = elem->GetAttrValue(g_pAttrName);
            const u16* value = elem->GetAttrValue(g_pAttrValue);
            if (name != 0 && value != 0)
                self->ExcludeGroups(self, name, value);
        }
        return;
    }
    Element::HandleEvent(ev, arg);
}

// @ 0x008e52b0
void* Node::Init(void* doc, int type)
{
    Node* self = this;
    *(void* volatile*)&self->link1 = 0;
    *(void* volatile*)&self->link0 = 0;
    self->mnType = (u32)type;
    self->vftable = (void*)g_vtbl_node;
    self->mpDocument = doc;
    self->mpParent = 0;
    return self;
}

// @ 0x008e52f0
Element* Node::AsElement()
{
    Node* self = this;
    return self->mnType == 1 ? (Element*)self : 0;
}
