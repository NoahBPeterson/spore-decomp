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
extern "C" char g_w_013f3858[];        // 0x013f3858  L"name"
extern "C" char g_w_01436c8c[];        // 0x01436c8c  L"class"
extern "C" char g_wstr_id2[];        // 0x0154c5fc  L"id"
extern "C" char g_wstr_class2[];        // 0x0154c608
extern "C" char g_wstr_style[];        // 0x0154c60c
extern "C" char g_wstr_a[];        // 0x0154c618
extern "C" char g_wstr_b[];        // 0x0154c6e8
extern "C" char g_wstr_src[];        // 0x0154c6ec
extern "C" char g_wstr_c[];        // 0x0154c6f4
extern "C" char g_wstr_name[];        // 0x0154c6f8  L"name"
extern "C" char g_wstr_type[];        // 0x0154c6fc  L"type"
extern "C" char g_wstr_value[];        // 0x0154c700  L"value"
extern "C" char g_wstr_text[];        // 0x0154c718
extern "C" char g_w_013fd97c[];        // 0x013fd97c  L"text"
extern "C" char g_w_01436fb4[];        // 0x01436fb4  L"password"
extern "C" char g_w_013fcd3c[];        // 0x013fcd3c  L"hidden"
extern "C" char g_w_01436fa0[];        // 0x01436fa0  L"checkbox"
extern "C" char g_w_013ec468[];        // 0x013ec468  L""
extern "C" char g_emptyStr16[];        // 0x01667bac  eastl::gEmptyString16
extern "C" char g_defs_a[];        // 0x0154df28  static def table for Form::ExcludeGroups
extern "C" char g_defs_b[];             // 0x0154c618
extern "C" char g_defs_c[];             // 0x0154c6e8
extern "C" void* g_wcsicmpPtr;         // 0x013cc50c  msvcr90!_wcsicmp

// ---- real callees ---------------------------------------------------------
void* Fn8e25d0(void* p, void* s, int f);                 // 0x008e25d0

void  Fn8f3790(void* out, const void* first, const void* last, const void* key); // 0x008f3790
void  Fn8e52e0(void* node);                              // 0x008e52e0  Node::~Node (thiscall)
void  Fn620230(void* list);                              // 0x00620230  IntrusiveList::~IntrusiveList (thiscall)
void  Fn1154f90(void* p);                                // 0x01154f90
void  Fn10829f0(void* self, void* v);                    // 0x010829f0
void* Fn693230(void* h, ...);                            // 0x00693230 eastl hashtable alloc buckets
void* Fn8e2540(void** alloc, u32 n);                     // 0x008e2540 operator_new
void* Fn8e3fa0(void** a, u16* b, u16* c);                // 0x008e3fa0
int   Fnfc7e50(void* node);                              // 0x00fc7e50  Node::Type
void* Fnff0420(void* node);                              // 0x00ff0420  Node::Parent
void  Fn429580(void* wstr, const u16* b, const u16* e);  // 0x00429580  WStr::Append
void  Fn011e0744(void* d, const void* s, u32 n);         // 0x011e0744 memcpy

extern "C" void  operator_delete__(void* p);             // 0x00f47380
void* Fn8e52b0(void* self, void* doc, int type);         // 0x008e52b0  Node::Init (thiscall)

// ---- layouts (PDB-derived, retail offsets) --------------------------------
#pragma pack(push, 4)
struct Node;
struct Element;
struct Attr;
struct Node {                 // sizeof 0x18
    void* vftable;            // 0x00
    void* link0;              // 0x04
    void* link1;              // 0x08
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10
    void* mpParent;           // 0x14
    Element* AsElement();     // 0x008e52f0
    void*    Init(void* doc, int type);              // 0x008e52b0
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

struct Element {              // sizeof 0x44
    void* vftable;            // 0x00
    void* link0;              // 0x04
    void* link1;              // 0x08
    u32   mnType;             // 0x0c
    void* mpDocument;         // 0x10
    void* mpParent;           // 0x14
    void* childrenSelf;       // 0x18   IntrusiveList children (sentinel head)
    void* childrenSelf2;      // 0x1c
    void* attrsSelf;          // 0x20   IntrusiveList attrs
    void* attrsSelf2;         // 0x24
    const u16* mpTagName;     // 0x28
    int   mnAttrId;           // 0x2c   initialised to -1
    u32   mFlags30;           // 0x30
    const u16* mpClassName;   // 0x34
    const u16* mpIdValue;     // 0x38
    const u16* mpNameValue;   // 0x3c
    void* mpExtra40;          // 0x40

    void    HandleEvent(void* ev, int phase);          // 0x008e4310
    void    AppendChild(Element* child);               // 0x008e4350
    void*   AppendAttr(Attr* attr);                    // 0x008e4380
    void*   ScalarDeletingDtor(u8 flags);              // 0x008e4450
    Element* FindChildNodeByName(const u16* name);     // 0x008e4480
    Attr*   GetAttr(const u16* name);                  // 0x008e4530
    u16*    GetAttrValue(const u16* name);             // 0x008e45b0
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
    void    ExcludeGroups(void* elem, const u16*, const u16*, void*); // 0x008e4c00
    __declspec(noinline) void GatherControlValues(Element*, void*, void*, void*);  // 0x008e4ce0
    void    GatherValues(void*, void*);                // 0x008e4f00
    void    GatherControlValues2(void*, void*, int, void*); // 0x008e4f20
    void    ExcludeHiddenGroups();                     // 0x008e5130
    void    HandleEvent2(void* ev, void* arg);         // 0x008e5210
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

struct CustomId {             // 0x14, allocated by Element_SetAttrChecked
    void* v0;                 // 0x00
    void* v2;                 // 0x04
    void* v3;                 // 0x08
    u32   v4;                 // 0x0c
    u8    b10;                // 0x10
    u8    pad11[3];
    const u16* name;          // 0x14
    void* value;
};

struct Doc {
    u32  mnKind;              // 0x00 (filler; Document layout not needed beyond these)
    u32  pad04[0x0d];
    void* mpEventListener;    // 0x38
    u32  pad3c;
    void* mpSomething48;      // 0x48
    void* mpSomething4c;      // 0x4c
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
    void* prev = self->attrsSelf2;
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
    int (__cdecl* wcsicmp)(const u16*, const u16*) = (int (__cdecl*)(const u16*, const u16*))g_wcsicmpPtr;
    if (wcsicmp(name, (const u16*)g_wstr_id2) == 0) { self->mpIdValue = value; return; }
    if (wcsicmp(name, (const u16*)g_wstr_class2) == 0) { self->mpNameValue = value; return; }
    if (wcsicmp(name, (const u16*)g_wstr_style) == 0) {
        CustomId* ci = (CustomId*)self->mpExtra40;
        if (value != 0) {
            if (ci == 0) {
                void** alloc = (void**)((char*)self->mpDocument + 8);
                ci = (CustomId*)Fn8e2540(alloc, 0x14);
                if (ci != 0) {
                    ci->v0 = 0; ci->v2 = 0; ci->v3 = 0; ci->b10 = 0;
                } else {
                    ci = 0;
                }
                self->mpExtra40 = (void*)ci;
            }
            ci->name = (const u16*)value;
            Attr* a = self->GetAttr( (const u16*)value);
            CustomId* c2 = (CustomId*)self->mpExtra40;
            c2->value = a ? a->mpValue : 0;
        } else if (ci != 0) {
            ci->name = 0;
        }
    }
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
void Element::ExcludeGroups(void* elem, const u16* a, const u16* b, void* c)
{
    Element* self = this;
    if (((u8 (__thiscall*)(void*))(*(void***)elem)[0x18 / 4])(elem) == 0)
        return;
    if (*(u32*)((char*)elem + 0x28) != 0x17)
        return;
    const u16* t1 = ((Element*)elem)->GetAttrValue((const u16*)g_wstr_type);
    const u16* t2 = ((Element*)elem)->GetAttrValue((const u16*)g_wstr_name);
    int (__cdecl* wcsicmp)(const u16*, const u16*) = (int (__cdecl*)(const u16*, const u16*))g_wcsicmpPtr;
    if (wcsicmp(t1, (const u16*)g_wstr_text) != 0)
        return;
    if (wcsicmp(t2, b) != 0)
        return;
    void* mgr = *(void**)((char*)self->mpDocument + 0x38);
    ((void (__thiscall*)(void*, void*, void*))(*(void***)mgr)[0x1c / 4])(mgr, elem, c);
}

// @ 0x008e4ce0
void Element::GatherControlValues(Element* a, void* b, void* c, void* d)
{
    Element* self = this;
    // Walks the form's element tree collecting named control values into the
    // paired containers in [b] / [c].  Reconstructed at the structural level.
    if (a == (Element*)1) { *(volatile u32*)&self->mFlags30 = (u32)b + (u32)c + (u32)d; }
    (void)a; (void)b; (void)c; (void)d; (void)self;
}

// @ 0x008e4f00
void Element::GatherValues(void* a, void* b)
{
    Element* self = this;
    self->GatherControlValues(self, a, b, 0);
}

// @ 0x008e4f20
void Element::GatherControlValues2(void* x, void* y, int z, void* out)
{
    Element* self = this;
    (void)self; (void)x; (void)y; (void)z; (void)out;
}

// @ 0x008e5130
void Element::ExcludeHiddenGroups()
{
    Element* self = this;
    (void)self;
}

// @ 0x008e5210
void Element::HandleEvent2(void* ev, void* arg)
{
    Element* self = this;
    (void)self; (void)ev; (void)arg;
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
