// src/game/UTFSpore_Win32/Document.cpp -- migrated from slice(s) s008e4310, s008e2dd0, s008e1d50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Document.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/Thread/Mutex.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
extern char vtbl_Manager[];     // 0x1436ae8
extern char vtbl_ZBase[];       // 0x13effb8
extern void* gEmptyBuckets[];   // 0x154df28
extern const wchar_t* gTagSysGui;       // 0x154c5f8
extern const wchar_t* gTagObject;       // 0x154c5f4
extern const wchar_t* gTagForm;         // 0x154c5f0
extern const wchar_t* gTagInput;        // 0x154c5ec
extern const wchar_t* gTagButton;       // 0x154c5e8
extern const wchar_t* gTagSelect;       // 0x154c5e4
extern const wchar_t* gTagTextArea;     // 0x154c5e0
extern char vtbl_ElemSysGui[];          // 0x1436da8
#include <new>
#include <intrin.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/DOM/IFormControlMgr.h"

// ---- items of slice s008e1d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __cdecl wcslen(const wchar_t* s);
extern "C" __declspec(dllimport) int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
typedef unsigned short wchar16;
struct IObj;
struct XElem { const wchar_t* GetAttrValue(int id); };   // 0x008e45b0 EA::XHTML::DOM::Element::GetAttrValue (thiscall)
void __cdecl operator_delete(void* p);
void __cdecl operator_delete__(void* p);
void __cdecl FUN_00928dc0(void* alloc);
void __cdecl FUN_00620230(void* p);
void __cdecl FUN_011e0744(void* d, const void* s, unsigned n);
struct IKV { int m0; int m4; char m8; char pad9[7]; int m10; };
struct Obj6 {
    virtual void v0(int);
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9(void* ctx, int flag);
    virtual void v10();
    virtual void v11();
};
struct DocX {
    char pad0[0x2c];
    uint8_t mFlag;          // +0x2c
    char pad1[0xb];
    void* mpOther;          // +0x38
    char pad2[4];
    int   mVal40;           // +0x40
    void SetChild(int v);
    void CallA();
    void CallB();
    void* FindBody();
    void SetAt(unsigned idx, IObj* o);
    void RemoveAllChildren();
    bool CheckFlag(bool flag);
    int LookupStyle();
    void RemoveAttr(IKV* kv);
};
struct SA {
    char pad0[8];
    void* m8;       // end
    void* mc;       // cur
    void* m10;
    bool AllocateNewBlock(unsigned n);     // 0x00928ba0 EA::Allocator::StackAllocator::AllocateNewBlock
};
inline void* RawAlloc(SA* a, unsigned n)
{
    if ((int)((char*)a->m8 - (char*)a->mc) - (int)n < 0) {
        if (!a->AllocateNewBlock(n))
            return 0;
    }
    char* p = (char*)a->mc;
    a->mc = p + n;
    a->m10 = p + n;
    return p;
}
struct Der43;
struct Der4f;
struct Holder {
    char pad[8];
    SA sa;          // +0x08
    wchar_t* AppendWStr(const wchar_t* s, int len);
    Der43* CreateDer43(const wchar_t* a, const wchar_t* b, bool convert);
    Der4f* CreateDer4f(const wchar_t* s, int len, bool convert);
    void* CreateNodeA(const wchar_t* s, int len, bool convert);
    void* CreateElement(const wchar_t* name, const struct AttrSrc* attrs, unsigned nAttrs, bool convert);
};
struct Base24 {
    virtual void bv();
    char pad[0x14];
    Base24(void*, int);
};
struct Der43 : Base24 {
    void* m18;
    void* m1c;
    __declspec(noinline) Der43(void* a, void* b, void* c);
};
struct Der4f : Base24 {
    void* m18;
    void* m1c;
    __declspec(noinline) Der4f(void* a, void* b, void* c);
};
struct DNodeA { __declspec(noinline) DNodeA(void*, void*, void*); };   // 0x008e55d0
struct Child40 { void* FindChild(const wchar_t* name, int flag); };
struct IObj {
    virtual void AddRef();
    virtual void Release();
};
struct InList { InList* mpNext; InList* mpPrev; };
struct VI { virtual void v0(); virtual void v1(); virtual void v2(void*); };
struct B29 {
    virtual void v();
    char pad[0x40];
    B29(void*, void*);
};
struct D29a : B29 {
    void* m44;
    __declspec(noinline) D29a(void* a, void* b);
};
struct D29b : B29 {
    void* m44;
    __declspec(noinline) D29b(void* a, void* b);
};
struct C2b0 {
    virtual void v0();
    virtual void v1();
    virtual void v2(int);
};
struct Vec2b {
    IObj** mpBegin;     // +0
    IObj** mpEnd;       // +4
    char pad[8];
    IObj** mpInline;    // +0x10
    void Free();
};
struct B2b6 {
    virtual void v();
    B2b6(void*, int, void*);
};
struct D2b6 : B2b6 {
    __declspec(noinline) D2b6(void* a, void* b);
};
struct CAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);   // +8
    virtual void Free(void* p, unsigned size);                              // +0xc
};
struct IFactory {
    virtual void* Del(unsigned flags);
    virtual void OnAdded();
    virtual void OnRemoved();
    volatile long mRef;     // +4
};
struct FEntry {
    IFactory* mp;
    int mPriority;
};
struct FactoryVec {
    FEntry* mpBegin;    // +0
    FEntry* mpEnd;      // +4
    FEntry* mpCap;      // +8
    CAlloc* mpAlloc;    // +0xc
    int mFlags;         // +0x10
    FactoryVec(CAlloc* a) : mpBegin(0), mpEnd(0), mpCap(0), mpAlloc(a), mFlags(0) {}
    void insert(FEntry* where, const FEntry& v);        // 0x8e1690
    void DoInsertValue(FEntry* where, const FEntry& v); // 0x8e12c0
    void DestroyRange(FEntry* first, FEntry* last);     // 0x8dede0
    ~FactoryVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin)
            mpAlloc->Free(mpBegin, (unsigned)(((char*)mpCap - (char*)mpBegin) >> 3) * 8);
    }
};
struct ZBase {
    void* vt;
    ~ZBase() { vt = vtbl_ZBase; }
};
struct RBAnchor {
    void* right;
    void* left;
    void* parent;
    int color;
    RBAnchor() : left(0), parent(0), color(0) {}
};
struct RBSet {
    uint8_t mCompare;       // +0 (padded to 4)
    RBAnchor mAnchor;       // +4
    int mnSize;             // +0x14
    CAlloc* mpAlloc;        // +0x18
    int mnFlags;            // +0x1c
    void DoNuke(void* root);    // 0x8de4f0
    RBSet(CAlloc* a) : mCompare(0), mpAlloc(a), mnFlags(0)
    {
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
        mAnchor.parent = 0;
        *(char*)&mAnchor.color = 0;
        mnSize = 0;
    }
    ~RBSet() { DoNuke(mAnchor.parent); }
};
struct HTBase {
    uint32_t pad0;
    void** mpBuckets;       // +4
    unsigned mnBuckets;     // +8
    unsigned mnElems;       // +0xc
    float mfMaxLoad;        // +0x10
    float mfGrowth;         // +0x14
    unsigned mnNextResize;  // +0x18
    CAlloc* mpAlloc;        // +0x1c
    int mFlags;             // +0x20
    HTBase(CAlloc* a) : mnBuckets(1), mnElems(0), mfMaxLoad(1.0f), mfGrowth(2.0f), mnNextResize(0), mpAlloc(a), mFlags(0)
    {
        mpBuckets = gEmptyBuckets;
    }
};
template <int N>
struct HT : HTBase {
    HT(CAlloc* a) : HTBase(a) {}
    void DoFreeNodes(void** buckets, unsigned n);
    ~HT()
    {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElems = 0;
        if (mnBuckets > 1)
            mpAlloc->Free(mpBuckets, mnBuckets * 4 + 4);
    }
};
struct IDBList {
    char d[0x78];
    IDBList(CAlloc* a);     // 0x8de8e0
    ~IDBList();             // 0x8e1420
};
struct StackAllocator {
    char d[0x20];
    StackAllocator(CAlloc* a, unsigned size, unsigned align);   // 0x925f30
    ~StackAllocator();                                          // 0x925e60
};
struct Mutex2 {
    char d[0x30];
    Mutex2(void*, bool);    // 0x9222a0
    ~Mutex2();              // 0x922130
};
struct ZBase1 : ZBase {
    ZBase1() { vt = vtbl_Manager; }
};
struct ManagerX : ZBase1 {
    bool mbInitialized;             // +4
    CAlloc* mpAllocator;            // +8
    RBSet mFunctionInfoSet;         // +0xc
    IDBList* mpDatabaseList;        // +0x2c
    HT<1> mTypeToFactoryMap;        // +0x30
    HT<2> mResourceToRecordMap;     // +0x54
    HT<3> mTable78;                 // +0x78
    FactoryVec mFactories;          // +0x9c (pair<AutoRefCount<Factory>,int> vector)
    HT<4> mTableB0;                 // +0xb0
    StackAllocator mStack;          // +0xd4
    HT<5> mNameMap;                 // +0xf4
    Mutex2 mNameMutex;              // +0x118
    Mutex2 mMutex;                  // +0x148

    ManagerX(CAlloc* alloc);
    ~ManagerX();
    bool RegisterFactory(bool bAdd, IFactory* f, int prio);
    void ResetAll();
};
struct ElemSysGui {
    void* vt;
    char pad[0x44];
    __declspec(noinline) ElemSysGui(void* doc, int kind, const wchar_t* name);   // 0x8e5370
};
struct ElemDefault {
    char pad[0x44];
    __declspec(noinline) ElemDefault(void* doc, const wchar_t* name);   // 0x8e4940
};
struct ElemAny {
    void AppendAttr(void* attr);   // 0x8e4380
};
struct AttrSrc {
    const wchar_t* name;
    const wchar_t* value;
};
// ---- items of slice s008e1d50 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* __cdecl AllocBlock(unsigned size, SA* a);  // 0x008e2540 (stays in the slice: not this object's)

// ---- items of slice s008e2dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  Fn8e25d0(void* p, int n);          // 0x008e25d0
extern char*    GetXHTMLResourceProvider();        // EA::XHTML::Resource::GetResourceProvider
extern "C" void Fn829110(void*, void*, void*, void*, void*);   // 0x00829110
extern "C" void Fnac97a0(void*, void*, void*);                 // 0x00ac97a0
extern "C" void* operator_new(int);                            // CRT new (0x00f473a0)
extern "C" void  Fn6782c0(void*, void*, void*);                // 0x006782c0 copy_impl::do_copy
extern "C" void* memcpy(void*, const void*, unsigned int);     // 0x011e0744
extern "C" const char   STR_ssfactory_1436e4c[];     // 0x01436e4c  "XHTML/Page/Style/Stylesheet"
extern "C" char  Fn8f9220(void* parser, void* stylesheet);          // 0x008f9220 CSSParser::Parse
extern "C" void* FnF473a0_new(int size, const char* file, int a, int b, int c, int d);  // 0x00f473a0
extern "C" void  Fn8e2ae0();                    // 0x008e2ae0  load callback
extern "C" void* Fn8e42d0_get(void* elem);                       // 0x008e42d0
extern "C" void  Fn8e3230(void* pos, void* val);                 // 0x008e3230
extern "C" void* Fn8e3620(void* vec, void* val);                 // 0x008e3620
typedef unsigned int   uint32;
static void FreeWCStr(char* begin, char* capacity)
{
    if (((capacity - begin) & ~1) > 2 && begin) {
        operator_delete__(begin);
    }
}
struct StackAllocator_s008e_2dd0 {
    void* ctor(void* a, uint32 b, void* c, void* d, void* e);   // 0x00928cd0
    void  Init(void* a, uint32 b, void* c, void* d, void* e);   // 0x00928b00
};
extern "C" const wchar16 STR_href_13f36b0[];         // 0x013f36b0  L"href"
extern "C" const wchar16 STR_rel_13f36a8[];          // 0x013f36a8  L"rel"
extern "C" const wchar16 STR_type_13f36bc[];         // 0x013f36bc  L"type"
extern "C" const wchar16 STR_textcss_1436e68[];      // 0x01436e68  L"text/css"
extern "C" const wchar16 STR_stylesheet_1436e34[];   // 0x01436e34  L"stylesheet"
extern "C" const wchar16 STR_src_1436bf8[];          // 0x01436bf8  L"src"
extern "C" wchar16      gEmptyString16_1667bac[];    // 0x01667bac  eastl::gEmptyString16
int  __fastcall Fn8e42c0(void* p);                                  // 0x008e42c0 (defined below)
void __fastcall Fn8e3100(void* pThis, int url, void* a, void* b, char c, int d);  // 0x008e3100
struct StylesheetQueueFwd {
    void Fn8e42e0(void* arg);       // @ 0x008e42e0
};
extern "C" int   Fn8e2580(void* elem, const wchar16* attr, const wchar16* val); // 0x008e2580 attr match (reg ABI)
extern "C" void* Fn8f3900(void* self, int a, wchar16* s);           // 0x008f3900
extern "C" void* Fn8f9db0(wchar16* base);                           // 0x008f9db0 Stylesheet::Stylesheet
struct FetchElem {
    virtual void* v0();
    virtual void* v1();
    virtual void* GetText(void* str);                 // vtable slot 2 (+0x08)
    char      _pad04[0x28 - 0x04];
    int       mElementType;                           // +0x28
    int       mResourceIndex;                         // +0x2c
    wchar16*  GetAttrValue(const wchar16* attr);      // 0x008e45b0
    int       Type();                                 // 0x00fc7e50
};
struct CSSParserLocal {
    char  _pad00[0x04];
    void* mpErrorListener;                            // +0x04
    char  _pad08[0x68 - 0x08];
};
struct Doc {
    char      _pad00[0x48];
    wchar16*  mpBaseURI;        // +0x48
    wchar16*  mpDocumentURI;    // +0x4c
    char      _pad50[0x118 - 0x50];
    void*     mpErrorListener;  // +0x118
    void Fn8e3380(void* elem, void* arg);   // @ 0x008e3380
    void Fn8e3600(void* arg);               // @ 0x008e3600
};
struct StackAlloc {
    char* mpCurrentObjectBegin;   // +0x00
    char* mpCurrentObjectEnd;     // +0x04
    char* mpCurrentBlockEnd;      // +0x08
    void* AllocateNewBlock(uint32 bytes);   // 0x00928ba0
};
struct ResourceDoc {
    char       _pad00[0x08];
    StackAlloc mAllocator;        // +0x08
    char       _pad14[0x34 - 0x14];
    void*      mpResourceProvider;  // +0x34
    char       _pad38[0x48 - 0x38];
    wchar16*   mpBaseURI;           // +0x48
    wchar16*   mpDocumentURI;       // +0x4c
    char       _pad50[0x100 - 0x50];
    void*      mResourceTableBegin; // +0x100
    void*      mResourceTableEnd;   // +0x104
    char       _pad108[0x118 - 0x108];
    void*      mpErrorListener;     // +0x118
};
struct ResourceProvider {
virtual void* r0();
virtual void* r1();
    virtual void* Load(void* out, void* url, void* cb, void* self,
                       void* listener, int flags);          // +0x04
};
struct AutoRef { void* mpObject; };      // +0x00
struct DomNode {
    void*     mpVtable;       // +0x00
    DomNode*  mpSiblingLink;  // +0x04
    char      _pad08[0x14 - 0x08];
    DomNode*  mpParent;       // +0x14  (child-list anchor: mpPrev)
    DomNode*  mChildHead;     // +0x18  (child-list anchor: mpNext)
    char      _pad1c[0x28 - 0x1c];
    int       mElementType;   // +0x28
    int       Type();         // 0x00fc7e50  Node::Type
};
static const int kElementType_Style = 7;
static const int kElementType_Link  = 8;
static const int kNodeType_Element  = 1;
struct Stylesheet {
    virtual void* sAddRef();     // +0x00
    virtual void* sRelease();    // +0x04
};
struct StylesheetProvider {
virtual void* p00();
virtual void* p01();
virtual void* p02();
    virtual Stylesheet* resolve(int key);        // +0x0c
};
struct StyleVec {
    void* mpBegin;              // +0x00
    void* mpEnd;                // +0x04
    void* mpCapacity;           // +0x08
    void  erase(void* first, void* last);        // 0x00e25bd0
};
struct DomElement {
    void* FindChildNodeByName(const wchar16* name, int flags);   // 0x008e4480
    wchar16* GetAttrValue(const wchar16* attr);                  // 0x008e45b0
};
static wchar16* Fn8e45b0_helper(DomNode* e, const wchar16* attr)
{
    return ((DomElement*)e)->GetAttrValue(attr);
}
extern "C" const wchar16 STR_head_1436e7c[];      // 0x01436e7c  L"head"
extern "C" const wchar16 STR_attr_a_13f36a8[];                   // 0x013f36a8  L"rel"
extern "C" const wchar16 STR_attr_b_13f36bc[];                   // 0x013f36bc  L"type"
struct Document {
    char          _pad00[0x2c];
    unsigned char mbDocumentChanged;  // +0x2c
    char          _pad2d[0x40 - 0x2d];
    DomElement*   mpDocumentElement;  // +0x40
    StyleVec      mStylesheets;       // +0x50
    char          _pad5c[0xa8 - 0x5c];
    StyleVec      mUserStylesheets;   // +0xa8
};
// ---- items of slice s008e2dd0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* Fn8e3fa0(void** out, wchar16* base, wchar16* rel);  // 0x008e3fa0 (stays in the slice: not this object's)

// ---- items of slice s008e4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_vtbl_element[];      // 0x01436f60  Element vftable
extern "C" char g_vtbl_node[];      // 0x01436fd0  Node vftable
extern "C" char g_defs_b[];             // 0x0154c618
extern "C" char g_defs_c[];             // 0x0154c6e8
#pragma intrinsic(wcscmp)
#pragma pack(push, 4)
#pragma pack(pop)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
extern "C" const u16* g_pAttrName;      // 0x0154c6f8  -> L"name"
extern "C" const u16* g_pAttrValue;     // 0x0154c700  -> L"value"
u32   Fnfc7e50(void* n);                                 // 0x00fc7e50  Node::Type (free spelling)
void  Fn8f3790(void* out, const void* first, const void* last, const void* key); // 0x008f3790
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
// ---- items of slice s008e4310 end

// @ 0x008e2430
Der43::Der43(void* a, void* b, void* c)
: Base24(a, 3) { m18 = b; m1c = c; }

// @ 0x008e24f0
Der4f::Der4f(void* a, void* b, void* c)
: Base24(a, 4) { m18 = b; m1c = c; }

// @ 0x008e2540
void* __cdecl AllocBlock(unsigned size, SA* a)
{
    unsigned n = (size + 7) & ~7u;
    return RawAlloc(a, n);
}

// @ 0x008e2580
bool EqAttr(void* elem, int id, const wchar_t* s)
{
    const wchar_t* v = ((XElem*)elem)->GetAttrValue(id);
    if (v == s)
        return true;
    if (v != 0 && s != 0)
        return _wcsicmp(v, s) == 0;
    return false;
}

// @ 0x008e25d0
wchar_t* Holder::AppendWStr(const wchar_t* s, int len)
{
    if (len == -1)
        len = (int)wcslen(s);
    unsigned nbytes = (unsigned)len * 2;
    char* p = (char*)RawAlloc(&sa, (nbytes + 9) & ~7u);
    FUN_011e0744(p, s, nbytes);
    *(wchar16*)(nbytes + (char*)p) = 0;
    return (wchar_t*)p;
}

// @ 0x008e2650
Der43* Holder::CreateDer43(const wchar_t* a, const wchar_t* b, bool convert)
{
    void* y;
    void* x;
    if (convert) {
        x = AppendWStr(a, -1);
        y = AppendWStr(b, -1);
    } else {
        x = (void*)a;
        y = (void*)b;
    }
    if (!x || !y)
        return 0;
    Der43* p = (Der43*)RawAlloc(&sa, 0x20);
    if (!p)
        return 0;
    return new (p) Der43((void*)this, x, y);
}

// @ 0x008e26e0
void* Holder::CreateNodeA(const wchar_t* s, int len, bool convert)
{
    if (len == -1)
        len = (int)wcslen(s);
    void* x = (void*)s;
    if (convert)
        x = AppendWStr(s, len);
    if (!x)
        return 0;
    DNodeA* p = (DNodeA*)RawAlloc(&sa, 0x20);
    if (!p)
        return 0;
    return new (p) DNodeA((void*)this, x, (void*)len);
}

// @ 0x008e2770
Der4f* Holder::CreateDer4f(const wchar_t* s, int len, bool convert)
{
    if (len == -1)
        len = (int)wcslen(s);
    void* x = (void*)s;
    if (convert)
        x = AppendWStr(s, len);
    if (!x)
        return 0;
    Der4f* p = (Der4f*)RawAlloc(&sa, 0x20);
    if (!p)
        return 0;
    return new (p) Der4f((void*)this, x, (void*)len);
}

// @ 0x008e2800
void DocX::SetChild(int v)
{
    mFlag = 1;
    mVal40 = v;
}

// @ 0x008e2810
void* DocX::FindBody()
{
    void* c = *(void**)((char*)this + 0x40);
    if (!c)
        return c;
    if (wcscmp(*(const wchar_t**)((char*)c + 0x34), L"html") == 0)
        return ((Child40*)c)->FindChild(L"body", 0);
    return c;
}

// @ 0x008e2870
void DocX::CallA()
{
    if (mpOther != 0 && mVal40 != 0)
        ((Obj6*)mVal40)->v10();
}

// @ 0x008e2890
void EA::XHTML::DOM::Document::DestroyFormControls()
{
    if (mpFormControlMgr != 0 && mpDocumentElement != 0)
        ((Obj6*)mpDocumentElement)->v11();
}

// @ 0x008e28b0
void DocX::SetAt(unsigned idx, IObj* o)
{
    IObj** begin = *(IObj***)((char*)this + 0x108);
    IObj** end = *(IObj***)((char*)this + 0x10c);
    if (idx >= (unsigned)(end - begin))
        return;
    IObj* old = begin[idx];
    if (o == old)
        return;
    if (o)
        o->AddRef();
    begin[idx] = o;
    if (old)
        old->Release();
}

// @ 0x008e2930
void DocX::RemoveAllChildren()
{
    InList* head = (InList*)((char*)this + 0x100);
    while (*(void**)((char*)this + 0x104) != (void*)head) {
        VI* p = *(VI**)((char*)this + 0x34);
        void* n = *(void**)((char*)this + 0x104);
        p->v2(*(void**)((char*)n + 0x14));
    }
}

// @ 0x008e2960
D29a::D29a(void* a, void* b)
: B29(a, b) { m44 = 0; }

// @ 0x008e2990
D29b::D29b(void* a, void* b)
: B29(a, b) { m44 = 0; }

// @ 0x008e29e0
bool DocX::CheckFlag(bool flag)
{
    InList* head = (InList*)((char*)this + 0x100);
    void* p = *(void**)head;
    while (p != (void*)head) {
        if (!flag)
            return true;
        if (*((uint8_t*)p + 0xc) != 0)
            return true;
        p = *(void**)p;
    }
    return false;
}

// @ 0x008e2a10
void DocX::RemoveAttr(IKV* kv)
{
    void** head = (void**)((char*)this + 0x100);
    void** node = (void**)*head;
    if (node == head)
        return;
    do {
        if (*(int*)((char*)node + 0x14) == kv->m4)
            goto found;
        node = (void**)*node;
    } while (node != head);
    return;
found:
    unsigned idx = *(unsigned*)((char*)node + 0x10);
    IObj** begin = *(IObj***)((char*)this + 0x108);
    IObj** slot = begin + idx;
    IObj* ov = *slot;
    IObj* nv = (IObj*)kv->m10;
    if (nv != ov) {
        if (nv)
            nv->AddRef();
        *slot = nv;
        if (ov)
            ov->Release();
    }
    void** prev = (void**)node[1];
    void** next = (void**)node[0];
    *prev = next;
    next[1] = prev;
    node[0] = 0;
    node[1] = 0;
    if (kv->m0 != 4) {
        *(uint8_t*)((char*)this + 0x2c) = 1;
        if (kv->m8 == 0) {
            struct { Obj6* p; int k; } ctx;
            Obj6* p = *(Obj6**)((char*)this + 0x40);
            ctx.k = 6;
            ctx.p = p;
            p->v9(&ctx, 1);
        }
    }
}

// @ 0x008e2af0
int __fastcall Release2(C2b0* p)
{
    volatile long* c = (volatile long*)((char*)p + 4);
    int n = _InterlockedDecrement(c);
    if (n != 0)
        return n;
    _InterlockedExchange(c, 1);
    if (p)
        p->v2(1);
    return 0;
}

// @ 0x008e2b20
void Vec2b::Free()
{
    IObj** end = mpEnd;
    for (IObj** it = mpBegin; it < end; ++it) {
        if (*it)
            (*it)->Release();
    }
    if (mpBegin != 0 && mpBegin != mpInline)
        operator_delete__(mpBegin);
}

// @ 0x008e2b60
D2b6::D2b6(void* a, void* b)
: B2b6(a, 10, b) {}

// @ 0x008e2b90
void ManagerX::ResetAll()
{
    // frees three intrusive sub-lists (+0x108, +0xa8, +0x50), destroys the
    // list anchor (+0x100) and resets the stack allocator at +8
    Vec2b* v1 = (Vec2b*)((char*)this + 0x108);
    Vec2b* v2 = (Vec2b*)((char*)this + 0xa8);
    Vec2b* v3 = (Vec2b*)((char*)this + 0x50);
    v1->Free();
    FUN_00620230((char*)this + 0x100);
    v2->Free();
    v3->Free();
    FUN_00928dc0((char*)this + 8);
}

// @ 0x008e2c10
void* Holder::CreateElement(const wchar_t* name, const AttrSrc* attrs, unsigned nAttrs, bool convert)
{
    if (convert)
        name = AppendWStr(name, -1);
    if (!name)
        return 0;
    void* e;
    if (_wcsicmp(name, gTagSysGui) == 0) {
        e = RawAlloc(&sa, 0x48);
        if (!e)
            return 0;
        new (e) ElemSysGui(this, 9, name);
        *(void**)e = vtbl_ElemSysGui;
    } else if (_wcsicmp(name, gTagObject) == 0) {
        e = AllocBlock(0x44, &sa);
        if (!e)
            return 0;
        e = new (e) D2b6(this, (void*)name);
    } else if (_wcsicmp(name, gTagForm) == 0) {
        e = AllocBlock(0x48, &sa);
        if (!e)
            return 0;
        e = new (e) D29b(this, (void*)name);
    } else if (_wcsicmp(name, gTagInput) == 0 || _wcsicmp(name, gTagButton) == 0 ||
               _wcsicmp(name, gTagSelect) == 0 || _wcsicmp(name, gTagTextArea) == 0) {
        e = AllocBlock(0x50, &sa);
        if (!e)
            return 0;
        e = new (e) D29a(this, (void*)name);
    } else {
        e = AllocBlock(0x44, &sa);
        if (!e)
            return 0;
        e = new (e) ElemDefault(this, name);
    }
    if (e && nAttrs > 0) {
        do {
            ((ElemAny*)e)->AppendAttr(CreateDer43(attrs->name, attrs->value, convert));
            ++attrs;
        } while (--nAttrs);
    }
    return e;
}

// @ 0x008e2dd0
void* __fastcall Fn8e2dd0(int* pThis, int param_2)
{
    void** p = (void**)pThis;
    p[0] = (void*)0x01436d94;                 // CSSParser vtable (AddRef form)
    p[1] = 0;                                 // reference count
    p[0] = (void*)0x01436ddc;                 // CSSParser vtable (final)
    StackAllocator_s008e_2dd0* pool = (StackAllocator_s008e_2dd0*)(p + 2);
    pool->ctor(0, 0xffffffffu, 0, 0, 0);
    ((unsigned char*)p)[0x2c] = 0;
    p[0xc] = 0;
    p[0xd] = GetXHTMLResourceProvider();
    p[0xe] = 0;
    p[0xf] = 0;
    p[0x10] = 0;
    p[0x11] = 0;
    p[0x12] = 0;
    p[0x13] = 0;

    p[0x14] = p + 0x1a;                       // string free-list heads
    p[0x15] = p + 0x1a;
    p[0x18] = p + 0x1a;
    p[0x16] = p + 0x2a;

    p[0x2a] = p + 0x30;
    p[0x2b] = p + 0x30;
    p[0x2e] = p + 0x30;
    p[0x2c] = p + 0x40;

    p[0x40] = p + 0x40;
    p[0x41] = p + 0x40;

    p[0x42] = p + 0x48;
    p[0x43] = p + 0x48;
    p[0x46] = p + 0x48;
    p[0x44] = p + 199;

    pool->Init(0, 0, 0, 0, 0);
    if (param_2 != 0)
        p[0x12] = (void*)Fn8e25d0((void*)param_2, -1);
    return p;
}

// @ 0x008e2ed0
void __fastcall Fn8e2ed0(void* pThis)
{
    char* c = (char*)pThis;
    FreeWCStr(*(char**)(c + 0x50), *(char**)(c + 0x58));
    FreeWCStr(*(char**)(c + 0x38), *(char**)(c + 0x40));
    FreeWCStr(*(char**)(c + 0x14), *(char**)(c + 0x1c));
}

// @ 0x008e2f30
void Fn8e2f30(int* pThis, char* first, char* last, char* pos)
{
    if (last == pos)
        return;
    int*  end = (int*)pThis[1];
    uint32 n  = (uint32)((pos - last) >> 2);

    if (n <= (uint32)(((char*)pThis[2] - (char*)end) >> 2)) {
        // enough spare capacity
        uint32 off = (uint32)(((char*)end - first) >> 2);
        if (off <= n) {
            char* mid = last + off * 4;
            Fn829110(0, mid, pos, (void*)end, last);
            pThis[1] = (int)((char*)pThis[1] + (n - off) * 4);
            Fn829110(0, first, (void*)end, (void*)pThis[1], last);
            pThis[1] = (int)((char*)pThis[1] + off * 4);
            Fnac97a0(last, mid, first + off * 4);
            return;
        }
        uint32 offBytes = n * 4;
        char*  split    = (char*)end - offBytes;
        Fn829110(0, split, (void*)end, (void*)end, last);
        pThis[1] = (int)((char*)pThis[1] + offBytes);
        Fnac97a0(first, split, (void*)end);
        Fn6782c0(last, pos, first);
        return;
    }

    // grow: newCap = max(used*2 (or 1), used+n)
    uint32 used   = (uint32)(((char*)end - (char*)pThis[0]) >> 2);
    uint32 newCap = used * 2;
    if (used == 0)
        newCap = 1;
    uint32 want = n + used;
    if (want < newCap)
        want = newCap;

    int* nb = (want == 0) ? 0 : (int*)operator_new((int)want * 4);
    uint32 headBytes = (uint32)(first - (char*)pThis[0]);
    char*  headEnd   = (char*)nb + (headBytes >> 2) * 4;
    if (headBytes != 0)
        memcpy(nb, (void*)pThis[0], headBytes);
    Fn829110(0, last, pos, headEnd, last);          // insert [last,pos)
    uint32 tailBytes = (uint32)((char*)pThis[1] - first);
    char*  tailStart = headEnd + (n * 4);
    if (tailBytes != 0)
        memcpy(tailStart, first, tailBytes);

    int* old = (int*)pThis[0];
    if (old != 0 && old != (int*)pThis[4])
        operator_delete__(old);
    pThis[1] = (int)(tailStart + (tailBytes >> 2) * 4);
    pThis[0] = (int)nb;
    pThis[2] = (int)((char*)nb + want * 4);
}

// @ 0x008e3100
void __fastcall Fn8e3100(void* pThis, int param_2, void* param_3, void* param_4, char param_5, int param_6)
{
    ResourceDoc* doc = (ResourceDoc*)pThis;
    if (doc->mpResourceProvider == 0)
        return;

    wchar16* url[2];                       // eastl fixed string on the stack
    url[0] = 0;
    url[1] = 0;
    wchar16* base = doc->mpBaseURI;
    if (base == 0)
        base = doc->mpDocumentURI;
    Fn8e3fa0((void**)url, base, (wchar16*)param_2);

    AutoRef* ref;
    if ((doc->mAllocator.mpCurrentBlockEnd - doc->mAllocator.mpCurrentObjectBegin) >= 0x18) {
        ref = (AutoRef*)doc->mAllocator.mpCurrentObjectBegin;
        doc->mAllocator.mpCurrentObjectBegin = (char*)ref + 0x18;
        doc->mAllocator.mpCurrentObjectEnd   = (char*)ref + 0x18;
        if (ref != 0) {
            ref[1].mpObject = 0;
            ref[0].mpObject = 0;
        }
    } else {
        ref = (AutoRef*)doc->mAllocator.AllocateNewBlock(0x18);
    }

    ref[2].mpObject = param_3;
    ref[4].mpObject = param_4;
    *(char*)&ref[3].mpObject = param_5;
    ref[5].mpObject = 0;
    ref[1].mpObject = doc->mResourceTableEnd;
    ref[0].mpObject = (void*)&doc->mResourceTableBegin;
    doc->mResourceTableEnd = ref;
    *(void**)(ref[1].mpObject) = ref;

    void* listener = doc->mpErrorListener;
    void* self = doc;
    ((ResourceProvider*)doc->mpResourceProvider)->Load(&ref[5], (void*)url, (void*)&Fn8e2ae0,
                                                       self, listener, param_6);
    if (listener != 0 && listener != (void*)&Fn8e2ae0 && listener != self)
        operator_delete__(listener);
}

// @ 0x008e3380
__declspec(noinline) void Doc::Fn8e3380(void* elem, void* arg)
{
    FetchElem* e = (FetchElem*)elem;

    if (e->mElementType == 6) {                       // Element_Base
        wchar16* href = e->GetAttrValue(STR_href_13f36b0);
        if (href != 0)
            this->mpBaseURI = href;
        return;
    }

    if (e->mElementType == 7) {                       // Element_Style
        if (Fn8e42c0(e) != 0)
            return;
        wchar16* type = e->GetAttrValue(STR_type_13f36bc);
        if (type != STR_textcss_1436e68 &&
            (type == 0 || _wcsicmp((const wchar_t*)type, (const wchar_t*)STR_textcss_1436e68) != 0))
            return;

        wchar16* str[3];
        str[0] = gEmptyString16_1667bac;
        str[1] = gEmptyString16_1667bac;
        str[2] = gEmptyString16_1667bac + 1;
        e->GetText(str);                              // vtable slot 2 fills the string

        void* blob = FnF473a0_new(0x70, STR_ssfactory_1436e4c, 0, 0, 0, 0);
        void* sheet = 0;
        if (blob != 0) {
            wchar16* base = this->mpBaseURI;
            if (base == 0)
                base = this->mpDocumentURI;
            sheet = Fn8f9db0(base);
        }
        Fn8f3900((char*)sheet + 8, (int)(size_t)this, str[0]);

        CSSParserLocal parser;
        parser.mpErrorListener = this->mpErrorListener;
        char parsed = Fn8f9220(&parser, sheet);
        if (parsed == 0) {
            if (sheet != 0)
                (*(void(__fastcall**)(int))(*(int*)sheet + 8))(1);
            sheet = 0;
        }
        ((StylesheetQueueFwd*)e)->Fn8e42e0(0);            // (thiscall on the element)
        Fn8e2ed0(&parser);

        if (str[0] != gEmptyString16_1667bac && str[0] != 0)
            operator_delete__(str[0]);
        return;
    }

    if (e->mElementType == 8) {                       // Element_Link
        wchar16* href = e->GetAttrValue(STR_href_13f36b0);
        if (Fn8e42c0(e) != 0)
            return;
        int ok = Fn8e2580(e, STR_rel_13f36a8, (wchar16*)STR_stylesheet_1436e34);
        if (ok == 0 &&
            Fn8e2580(e, STR_type_13f36bc, (wchar16*)STR_textcss_1436e68) == 0)
            return;
        ((StylesheetQueueFwd*)e)->Fn8e42e0(0);
        if (href == 0)
            return;
        Fn8e3100(this, (int)(size_t)href, 0, (void*)(size_t)e->mResourceIndex, 1, (int)(size_t)arg);
        return;
    }

    if (e->mElementType == 9) {                       // Element_Image
        wchar16* src = e->GetAttrValue(STR_src_1436bf8);
        if (Fn8e42c0(e) != 0)
            return;
        ((StylesheetQueueFwd*)e)->Fn8e42e0(0);
        if (src == 0)
            return;
        Fn8e3100(this, (int)(size_t)src, (void*)1, (void*)(size_t)e->mResourceIndex, 0, (int)(size_t)arg);
        return;
    }

    // generic element: recurse into the sibling chain of the child list
    void* anchorLink = *(void**)((char*)e + 0x18);
    void* stop       = (char*)e + 0x14;
    FetchElem* child = anchorLink != 0 ? (FetchElem*)((char*)anchorLink - 4) : 0;
    for (;;) {
        if (child == stop)
            break;
        if (child->Type() == 1)
            this->Fn8e3380(child, arg);
        void* next = *(void**)((char*)child + 4);
        child = next != 0 ? (FetchElem*)((char*)next - 4) : 0;
    }
}

// @ 0x008e3600
void Doc::Fn8e3600(void* arg)
{
    void* q = *(void**)((char*)this + 0x40);
    if (q) Fn8e3380(q, arg);
}

// @ 0x008e3660
void __fastcall Fn8e3660(void* pThis, void* elem)
{
    Document* doc = (Document*)pThis;
    DomNode*  e   = (DomNode*)elem;

    if (e->mElementType == kElementType_Style) {
        StylesheetProvider* q = (StylesheetProvider*)Fn8e42d0_get(e);
        if (q == 0)
            return;
        Stylesheet* s = q->resolve(0x23faacf);
        if (s == 0)
            return;
        s->sAddRef();
        Stylesheet** end = (Stylesheet**)doc->mStylesheets.mpEnd;
        if (end < (Stylesheet**)doc->mStylesheets.mpCapacity) {
            doc->mStylesheets.mpEnd = (void*)(end + 1);
            if (end != 0) {
                *end = s;
                s->sAddRef();
            }
        } else {
            Fn8e3230(end, &s);
        }
        if (s != 0)
            s->sRelease();
        return;
    }

    if (e->mElementType == kElementType_Link) {
        wchar16* v = Fn8e45b0_helper(e, STR_attr_a_13f36a8);
        bool ok;
        if (v == STR_stylesheet_1436e34)
            ok = true;
        else if (v != 0 && _wcsicmp((const wchar_t*)v, (const wchar_t*)STR_stylesheet_1436e34) == 0)
            ok = true;
        else {
            v = Fn8e45b0_helper(e, STR_attr_b_13f36bc);
            if (v == STR_textcss_1436e68)
                ok = true;
            else if (v == 0)
                ok = false;
            else
                ok = (_wcsicmp((const wchar_t*)v, (const wchar_t*)STR_textcss_1436e68) == 0);
        }
        if (!ok)
            return;
        StylesheetProvider* q = (StylesheetProvider*)Fn8e42d0_get(e);
        if (q == 0)
            return;
        Stylesheet* s = q->resolve(0x23faacf);
        if (s == 0)
            return;
        s->sAddRef();
        Fn8e3620(&doc->mStylesheets, &s);
        if (s != 0)
            s->sRelease();
        return;
    }

    // generic element: recurse into the sibling chain of the child list
    DomNode* stop = (DomNode*)((char*)e + 0x14);      // owner of the child anchor
    DomNode* child = e->mChildHead != 0 ? (DomNode*)((char*)e->mChildHead - 4) : 0;
    for (;;) {
        if (child == stop)
            break;
        if (child->Type() == kNodeType_Element)
            Fn8e3660(pThis, child);
        child = child->mpSiblingLink != 0 ? (DomNode*)((char*)child->mpSiblingLink - 4) : 0;
    }
}

// @ 0x008e37e0
void* __fastcall Fn8e37e0(Document* pThis)
{
    if (pThis->mbDocumentChanged != 0) {
        pThis->mStylesheets.erase(pThis->mStylesheets.mpBegin, pThis->mStylesheets.mpEnd);
        Fn8e2f30((int*)pThis->mStylesheets.mpEnd,
                 (char*)pThis->mUserStylesheets.mpBegin,
                 (char*)pThis->mUserStylesheets.mpEnd,
                 (char*)pThis);
        if (pThis->mpDocumentElement != 0) {
            void* head = pThis->mpDocumentElement->FindChildNodeByName(STR_head_1436e7c, 0);
            if (head != 0)
                Fn8e3660((void*)pThis, head);
        }
        pThis->mbDocumentChanged = 0;
    }
    return (void*)&pThis->mStylesheets;
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
