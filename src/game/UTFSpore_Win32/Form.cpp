// src/game/UTFSpore_Win32/Form.cpp -- migrated from slice(s) s008fc670, s008e4310, s008fb7e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Form.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/TextStyle.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_00f473a0(unsigned int nSize, const char* pName, int nFlags,
                                      int nDebugFlags, const char* pFile, int nLine);
extern "C" void  __cdecl FUN_00f47380(void* p);
extern "C" void* __cdecl FUN_011e073e(void* p, int nVal, unsigned int nSize);
#include <new>
#include "EA/XHTML/DOM/Document.h"
#include "EA/XHTML/DOM/IFormControlMgr.h"
#include "EA/IO/FileStream.h"
#include <intrin.h>

// ---- items of slice s008fb7e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Page;
namespace Style {
enum Unit { Unit_Auto = 10, Unit_Pixels = 1 };
}
namespace Style {
struct Length {
    float mValue;   // +0
    int   mUnits;   // +4
};
}
namespace Style {
struct FontMetrics {
    float mfFontSize;   // +0
    float mfEmSize;     // +4
    float mfExSize;     // +8
    float mfAscent;     // +0xc
    float mfDescent;    // +0x10
};
}
namespace Style {
class TextStyle {
public:
    TextStyle();                        // 0x008941d0
    TextStyle(const TextStyle&);        // 0x008945a0
    uint8_t _pad[0x278];
};
}
namespace Style {
struct RehashPolicy {
    float    mfMaxLoadFactor;   // +0x00
    float    mfGrowthFactor;    // +0x04
    uint32_t mnNextResize;      // +0x08
    struct Result {
        unsigned char mbFlag;           // +0
        unsigned int  mnNewBucketCount; // +4
    };
    void FUN_00921440(Result* pOut, unsigned int nBucketCount, unsigned int nElementCount, int nArg);  // 0x00921440
};
}
namespace Style {
struct CounterMap {
    struct node { const wchar_t* key; int value; node* mpNext; };
    struct iterator {
        node* mpNode;       // +0
        node** mpBucket;    // +4
        iterator(node* n, node** b) : mpNode(n), mpBucket(b) {}
        iterator() {}
        iterator(node** b) : mpNode(*b), mpBucket(b) {}
        iterator(const iterator& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
    };
    struct InsertResult {
        node* mpNode;       // +0
        node** mpBucket;    // +4
        bool mbInserted;    // +8
    };
    struct value_type { const wchar_t* first; int second; };

    uint32_t mField00;          // +0x00
    node**   mpBucketArray;     // +0x04
    uint32_t mnBucketCount;     // +0x08
    uint32_t mnElementCount;    // +0x0c
    RehashPolicy mRehashPolicy; // +0x10
    uint32_t mField1c;          // +0x1c

    node* FUN_005d6a90(node* pHead, const wchar_t* const& k, unsigned int nHash);  // 0x005d6a90
    void  FUN_00693230(node** pBuckets, unsigned int nCount);                      // 0x00693230
    void  DoRehash(unsigned int nNewBucketCount);                                  // 0x008fbac0
    iterator find(const wchar_t* const& k);                                        // 0x008fbbf0
    InsertResult insert(const value_type& value, const wchar_t* pKey);             // 0x008fbc80
    void mFieldsInit()
    {
        mRehashPolicy.mfMaxLoadFactor = 1.0f;
        mRehashPolicy.mfGrowthFactor = 2.0f;
        mnBucketCount = 1;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
        mpBucketArray = (node**)0x154df28;
    }
};
}
namespace Style {
struct Edge {                       // 0x20 bytes
    Length mBorder;                 // +0x00
    Length mPadding;                // +0x08
    Length mMargin;                 // +0x10
    uint32_t mBorderColor;          // +0x18
    uint32_t mBorderStyle;          // +0x1c
};
}
namespace Style {
class StyleState {
public:
    StyleState(Page* pPage);                        // 0x008fbe00
    StyleState(const StyleState& src);              // 0x008fc130

    void SetFontSizeKeyword(unsigned int kw);       // 0x008fb8a0
    void FUN_008fb9c0();                            // 0x008fb9c0
    bool FUN_008fb9e0();                            // 0x008fb9e0
    bool FUN_008fba80();                            // 0x008fba80
    void ClearCounterReset();                       // 0x008fbbc0
    int  GetCounter(const wchar_t* name);           // 0x008fbda0

    StyleState* mpBase;                 // +0x000
    Page*       mpPage;                 // +0x004
    bool        mbFontChanged;          // +0x008
    uint8_t     _pad009[3];             // +0x009
    TextStyle   mTextStyle;             // +0x00c
    Length      mFontSize;              // +0x284
    uint32_t    mFgColor;               // +0x28c
    Length      mLineHeight;            // +0x290
    Length      mFontSmoothThresh;      // +0x298
    void*       mpBackgroundImage;      // +0x2a0
    uint32_t    mBackgroundRepeat;      // +0x2a4
    uint32_t    mBackgroundAttachment;  // +0x2a8
    Length      mBackgroundPosX;        // +0x2ac
    Length      mBackgroundPosY;        // +0x2b4
    uint32_t    mBgColor;               // +0x2bc
    uint32_t    mColorInherited;        // +0x2c0
    Length      mWordSpacing;           // +0x2c4
    Length      mLetterSpacing;         // +0x2cc
    Length      mVerticalAlign;         // +0x2d4
    uint32_t    mVerticalAlignKW;       // +0x2dc
    uint32_t    mTextTransform;         // +0x2e0
    Length      mTextIndent;            // +0x2e4
    Edge        mEdges[4];              // +0x2ec .. +0x36b
    Length      mBoxX;                  // +0x36c
    Length      mBoxY;                  // +0x374
    uint32_t    mField37c;              // +0x37c
    uint32_t    mField380;              // +0x380
    uint32_t    mField384;              // +0x384
    Length      mBoxOffset[4];          // +0x388 .. +0x3a7
    uint32_t    mTableAlign;            // +0x3a8
    uint32_t    mField3ac;              // +0x3ac
    uint32_t    mField3b0;              // +0x3b0
    uint32_t    mField3b4;              // +0x3b4
    uint32_t    mField3b8;              // +0x3b8
    CounterMap  mCounters;              // +0x3bc
    CounterMap  mCounterIncrement;      // +0x3dc
    CounterMap  mCounterReset;          // +0x3fc
    Length      mBorderSpacingH;        // +0x41c
    Length      mBorderSpacingV;        // +0x424
    uint32_t    mField42c;              // +0x42c
    FontMetrics mFontMetrics;           // +0x430
    uint32_t    mField444;              // +0x444
    uint32_t    mField448;              // +0x448
    uint32_t    mField44c;              // +0x44c
};
}
// ---- items of slice s008fb7e0 end

// ---- items of slice s008e4310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_vtbl_element2[];      // 0x013fcc88  Form-ish vftable
extern "C" char g_vtbl_element3[];      // 0x01436d60
extern "C" void* g_pEmptyBuckets[2];    // 0x0154df28  eastl empty bucket array {0, -1}
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern "C" void  operator_delete__(void* p);             // 0x00f47380
#pragma intrinsic(wcscmp)
#pragma pack(push, 4)
#pragma pack(pop)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
extern "C" const u16* g_pAttrDisabled;  // 0x0154c6f4  -> L"disabled"
extern "C" const u16* g_pAttrName;      // 0x0154c6f8  -> L"name"
extern "C" const u16* g_pAttrType;      // 0x0154c6fc  -> L"type"
extern "C" const u16* g_pAttrValue;     // 0x0154c700  -> L"value"
extern "C" const u16* g_pAttrChecked;   // 0x0154c704  -> L"checked"
extern "C" const u16* g_pAttrCheckbox;  // 0x0154c714  -> L"checkbox"
extern "C" const u16* g_pAttrRadio;     // 0x0154c718  -> L"radio"
extern "C" u16 g_wEmpty[];              // 0x01667bac  L""
extern "C" u16 g_wEmptyLiteral[];       // 0x013ec468  L""
void  Fn8e52e0(void* node);                              // 0x008e52e0  Node::~Node (thiscall)
void  Fn620230(void* list);                              // 0x00620230  IntrusiveList::~IntrusiveList (thiscall)
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
virtual void Vf00();
virtual void Vf04();
virtual void Vf08();
virtual void Vf0c();
virtual void Vf10();
virtual void Vf14();
    virtual void GetValue(Element* elem, WStr16* value);      // +0x18
    virtual void SetValue(Element* elem, const u16* value);   // +0x1c
};
namespace Style {
struct CounterMap_s008e_4310 {
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
    void ResetControlValues(Element* elem, Style::CounterMap_s008e_4310* map);          // 0x008e4f20
    void Reset();                                                            // 0x008e5130
    void ExcludeGroups(Element* elem, const u16* group, const u16* value);   // 0x008e4c00
    void HandleEvent(void* ev, int arg);                                     // 0x008e5210
};
typedef void (__cdecl* GatherCallback)(const u16*, const u16*, void*);
// ---- items of slice s008e4310 end

// ---- items of slice s008fc670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" double __cdecl floor(double);
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma function(memcpy)
#pragma intrinsic(strcmp)
struct Box5 {
    union {
        float v[5];
        uint32_t u[5];
    };
};
struct UnitA { int v; float Resolve(float base, const Box5* box); };   // 0x8f9660
struct UnitB { int v; float Resolve(float base, const Box5* box); };   // 0x8f95c0
struct FontMetrics_s008f_c670 {
    int f0;
    int f4;
    int f8;
    int fc;
    float f10;      // +0x10
    float f14;      // +0x14
    int f18, f1c, f20;
    float f24;      // +0x24
    int pad[4];
};
struct FontObj {
virtual void o0();
virtual void o1();
virtual void o2();
    virtual void Release();                                   // +0xc
virtual void o4();
virtual void o5();
virtual void o6();
virtual void o7();
virtual void o8();
virtual void o9();
virtual void o10();
virtual void o11();
    virtual bool GetMetrics(FontMetrics_s008f_c670* m);                  // +0x30
};
struct FontServer {
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
    virtual FontObj* GetFont(void* spec, int a, int b, int c, int d, int e);   // +0x1c
};
FontServer* __cdecl GetFontServer(int);
struct HNodeA { const void* key; const void* val; HNodeA* next; };
struct HItA { HNodeA* node; HNodeA** bucket; HItA() {} HItA(const HItA& o) : node(o.node), bucket(o.bucket) {} };
struct HMapA {
    int al;
    HNodeA** mpBucketArray;
    unsigned mnBucketCount;
    char pad[0x20 - 12];
    HItA begin();                                   // 0x594410
    const void*& operator[](const void* const& key);    // 0x8fc610
};
struct HNodeB { const void* key; int val; HNodeB* next; };
struct HItB {
    HNodeB* node; HNodeB** bucket;
    HItB() {}
    HItB(const HItB& o) : node(o.node), bucket(o.bucket) {}
    void increment()
    {
        node = node->next;
        while (node == 0)
            node = *++bucket;
    }
};
struct HMapB {
    int al;
    HNodeB** mpBucketArray;
    unsigned mnBucketCount;
    char pad[0x20 - 12];
    HItB find(const void* const& key);              // 0x8fbbf0
    HItB insert(const HNodeB& v, bool tag);         // 0x8fbc80
    HItB begin()
    {
        HItB it;
        it.bucket = mpBucketArray;
        it.node = *it.bucket;
        if (it.node == 0) {
            do {
                ++it.bucket;
            } while (*it.bucket == 0);
            it.node = *it.bucket;
        }
        return it;
    }
    HNodeB* end() { return mpBucketArray[mnBucketCount]; }
    int& operator[](const void* const& key)
    {
        HItB it = find(key);
        if (it.node == end()) {
            HNodeB v;
            v.key = key;
            v.val = 0;
            it = insert(v, false);
        }
        return it.node->val;
    }
};
template <typename T> inline const T& Clamp(const T& v, const T& lo, const T& hi)
{
    return (v > hi) ? hi : ((lo > v) ? lo : v);
}
unsigned __cdecl BlendColor(unsigned c, unsigned d);            // 0x8fb7e0
struct TextStyle_s008f_c670 {
    TextStyle_s008f_c670* parent;          // +0
    int pad4;
    uint8_t dirty;              // +8
    char pad9[3];
    char font[0x20c - 0xc];     // +0xc (font spec)
    float size;                 // +0x20c
    char pad210[0x220 - 0x210];
    int flag220;                // +0x220
    char pad224[0x230 - 0x224];
    int m230;                   // +0x230
    char pad234[0x278 - 0x234];
    float f278, f27c, f280;
    UnitA u284;                 // +0x284
    int m288;
    int m28c;
    UnitA u290;
    int pad294;
    UnitA u298;
    int m29c;
    char pad2a0[0x2bc - 0x2a0];
    unsigned color;             // +0x2bc
    unsigned color2;            // +0x2c0
    UnitB u2c4;
    int pad2c8;
    UnitB u2cc;
    char pad2d0[0x3a8 - 0x2d0];
    int m3a8;
    char pad3ac[0x3bc - 0x3ac];
    HMapA tbl3bc;               // +0x3bc
    HMapB tbl3dc;               // +0x3dc
    HMapA tbl3fc;               // +0x3fc
    char pad41c[0x430 - 0x41c];
    Box5 box;                   // +0x430
    void Update();
};
// ---- items of slice s008fc670 end

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
void Form::ResetControlValues(Element* elem, Style::CounterMap_s008e_4310* map)
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
                    Style::CounterMap_s008e_4310::iterator it = map->find(name);
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
    Style::CounterMap_s008e_4310 map;
    map.mfMaxLoadFactor = 1.0f;
    map.mfGrowthFactor = 2.0f;
    map.mnBucketCount = 1;
    map.mpBucketArray = (Style::CounterMap_s008e_4310::node**)g_pEmptyBuckets;
    map.mnElementCount = 0;
    map.mnNextResize = 0;
    ResetControlValues(this, &map);

    Style::CounterMap_s008e_4310::node** pb = map.mpBucketArray;
    Style::CounterMap_s008e_4310::node* p = *pb;
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

// @ 0x008fb7e0
namespace Style {
unsigned __cdecl BlendColor(unsigned c, unsigned d)
{
    unsigned a = c >> 24;
    int rb = (int)((c >> 16) & 0xff) - (int)((d >> 16) & 0xff);
    unsigned b = (unsigned)(rb * (int)a / 255 + (int)((d >> 16) & 0xff));
    int rg = (int)((c >> 8) & 0xff) - (int)((d >> 8) & 0xff);
    unsigned g = (unsigned)(rg * (int)a / 255 + (int)((d >> 8) & 0xff));
    int rr = (int)(c & 0xff) - (int)(d & 0xff);
    unsigned r = (unsigned)(rr * (int)a / 255 + (int)(d & 0xff));
    return (d & 0xff000000u) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
}
}  // namespace Style

// @ 0x008fbac0
namespace Style {
void CounterMap::DoRehash(unsigned int nNewBucketCount)
{
    unsigned int nSize = nNewBucketCount * 4;
    node** pBucketArray = (node**)FUN_00f473a0(nSize + 4, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    FUN_011e073e(pBucketArray, 0, nSize);
    *(node**)((char*)pBucketArray + nSize) = (node*)(unsigned int)~0;
    unsigned int i = 0;
    if (mnBucketCount != 0) {
        do {
            node* pNode = mpBucketArray[i];
            while (pNode) {
                const unsigned short* c = (const unsigned short*)pNode->key;
                unsigned int h = 0x811c9dc5u;
                unsigned int ch;
                while ((ch = *c++) != 0)
                    h = (h * 0x1000193u) ^ ch;
                mpBucketArray[i] = pNode->mpNext;
                pNode->mpNext = pBucketArray[h % nNewBucketCount];
                pBucketArray[h % nNewBucketCount] = pNode;
                pNode = mpBucketArray[i];
            }
            ++i;
        } while (i < mnBucketCount);
    }
    if (mnBucketCount >= 2)
        FUN_00f47380(mpBucketArray);
    mpBucketArray = pBucketArray;
    mnBucketCount = nNewBucketCount;
}
}  // namespace Style

// @ 0x008fbbc0
namespace Style {
void StyleState::ClearCounterReset()
{
    CounterMap* m = &mCounterReset;
    m->FUN_00693230(m->mpBucketArray, m->mnBucketCount);
    m->mnElementCount = 0;
}
}  // namespace Style

// @ 0x008fbbf0
namespace Style {
CounterMap::iterator CounterMap::find(const wchar_t* const& k)
{
    const unsigned short* c = (const unsigned short*)k;
    unsigned int h = 0x811c9dc5u;
    unsigned int ch;
    while ((ch = *c++) != 0)
        h = (h * 0x1000193u) ^ ch;
    unsigned int cnt = mnBucketCount;
    unsigned int n = h % cnt;
    node** arr = mpBucketArray;
    node** pBucket = arr + n;
    node* pNode = FUN_005d6a90(arr[n], k, h);
    iterator it;
    if (pNode != 0) {
        it.mpNode = pNode;
        it.mpBucket = pBucket;
    } else {
        it.mpNode = arr[cnt];
        it.mpBucket = arr + cnt;
    }
    return it;
}
}  // namespace Style

// @ 0x008fbc80
namespace Style {
CounterMap::InsertResult CounterMap::insert(const value_type& value, const wchar_t* pKey)
{
    const unsigned short* c = (const unsigned short*)value.first;
    unsigned int h = 0x811c9dc5u;
    unsigned int ch;
    while ((ch = *c++) != 0)
        h = (h * 0x1000193u) ^ ch;
    unsigned int cnt = mnBucketCount;
    unsigned int n = h % cnt;
    node** pBucket = mpBucketArray + n;
    node* pNode = FUN_005d6a90(*pBucket, value.first, h);
    InsertResult res;
    if (pNode == 0) {
        RehashPolicy::Result rr;
        ((RehashPolicy*)((char*)this + 0x10))->FUN_00921440(&rr, cnt, mnElementCount, 1);
        node* pNew = (node*)FUN_00f473a0(0xc, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        if (pNew != 0) {
            pNew->key = value.first;
            pNew->value = value.second;
        }
        pNew->mpNext = 0;
        if (rr.mbFlag) {
            n = h % rr.mnNewBucketCount;
            DoRehash(rr.mnNewBucketCount);
        }
        node** pSlot = mpBucketArray + n;
        pNew->mpNext = *pSlot;
        *pSlot = pNew;
        ++mnElementCount;
        res.mpNode = pNew;
        res.mpBucket = mpBucketArray + n;
        res.mbInserted = true;
    } else {
        res.mpNode = pNode;
        res.mpBucket = pBucket;
        res.mbInserted = false;
    }
    return res;
}
}  // namespace Style

// @ 0x008fbda0
namespace Style {
int StyleState::GetCounter(const wchar_t* name)
{
    StyleState* q = this;
    if (q) {
        CounterMap* m = &q->mpBase->mCounters;
        CounterMap::node* end = m->mpBucketArray[m->mnBucketCount];
        do {
            CounterMap::iterator it = m->find(name);
            if (it.mpNode != end)
                return it.mpNode->value;
            q = q->mpBase;
        } while (q);
    }
    return 0;
}
}  // namespace Style

// @ 0x008fbe00
namespace Style {
StyleState::StyleState(Page* pPage)
: mpBase(0), mpPage(pPage), mbFontChanged(false), mTextStyle()
{
    mFontSize.mValue = 0.0f;
    mFontSize.mUnits = Unit_Auto;
    mFgColor = 0xff000000;
    mLineHeight.mValue = 0.0f;
    mLineHeight.mUnits = Unit_Auto;
    mFontSmoothThresh.mValue = 0.0f;
    mFontSmoothThresh.mUnits = Unit_Auto;
    mpBackgroundImage = 0;
    mBackgroundRepeat = 3;
    mBackgroundAttachment = 0;
    mBackgroundPosX.mValue = 0.0f;
    mBackgroundPosX.mUnits = Unit_Pixels;
    mBackgroundPosY.mValue = 0.0f;
    mBackgroundPosY.mUnits = Unit_Pixels;
    mBgColor = 0;
    mColorInherited = 0;
    mWordSpacing.mValue = 0.0f;
    mWordSpacing.mUnits = Unit_Auto;
    mLetterSpacing.mValue = 0.0f;
    mLetterSpacing.mUnits = Unit_Auto;
    mVerticalAlign.mValue = 0.0f;
    mVerticalAlign.mUnits = Unit_Auto;
    mVerticalAlignKW = 0;
    mTextTransform = 0;
    mTextIndent.mValue = 0.0f;
    mTextIndent.mUnits = Unit_Auto;
    mBoxX.mValue = 0.0f;
    mBoxX.mUnits = Unit_Auto;
    mBoxY.mValue = 0.0f;
    mBoxY.mUnits = Unit_Auto;
    mField37c = 0;
    mField380 = 0;
    mField384 = 0;
    mTableAlign = 1;
    mField3ac = 0;
    mField3b0 = 1;
    mField3b4 = 0;
    mField3b8 = 1;
    mCounters.mFieldsInit();
    mCounterIncrement.mFieldsInit();
    mCounterReset.mFieldsInit();
    mBorderSpacingH.mValue = 0.0f;
    mBorderSpacingH.mUnits = Unit_Auto;
    mBorderSpacingV.mValue = 0.0f;
    mBorderSpacingV.mUnits = Unit_Auto;
    mField42c = 0;
    mField44c = 0;
    mEdges[0].mMargin.mValue = 0.0f;  mEdges[0].mMargin.mUnits = Unit_Auto;
    mEdges[0].mPadding.mValue = 0.0f; mEdges[0].mPadding.mUnits = Unit_Auto;
    mEdges[0].mBorder.mValue = 0.0f;  mEdges[0].mBorder.mUnits = Unit_Auto;
    mEdges[0].mBorderStyle = 0;
    mEdges[0].mBorderColor = 0;
    mBoxOffset[0].mValue = 0.0f;      mBoxOffset[0].mUnits = Unit_Auto;
    mEdges[1].mMargin.mValue = 0.0f;  mEdges[1].mMargin.mUnits = Unit_Auto;
    mEdges[1].mPadding.mValue = 0.0f; mEdges[1].mPadding.mUnits = Unit_Auto;
    mEdges[1].mBorder.mValue = 0.0f;  mEdges[1].mBorder.mUnits = Unit_Auto;
    mEdges[1].mBorderStyle = 0;
    mEdges[1].mBorderColor = 0;
    mBoxOffset[1].mValue = 0.0f;      mBoxOffset[1].mUnits = Unit_Auto;
    mEdges[2].mMargin.mValue = 0.0f;  mEdges[2].mMargin.mUnits = Unit_Auto;
    mEdges[2].mPadding.mValue = 0.0f; mEdges[2].mPadding.mUnits = Unit_Auto;
    mEdges[2].mBorder.mValue = 0.0f;  mEdges[2].mBorder.mUnits = Unit_Auto;
    mEdges[2].mBorderStyle = 0;
    mEdges[2].mBorderColor = 0;
    mBoxOffset[2].mValue = 0.0f;      mBoxOffset[2].mUnits = Unit_Auto;
    mEdges[3].mMargin.mValue = 0.0f;  mEdges[3].mMargin.mUnits = Unit_Auto;
    mEdges[3].mPadding.mValue = 0.0f; mEdges[3].mPadding.mUnits = Unit_Auto;
    mEdges[3].mBorder.mValue = 0.0f;  mEdges[3].mBorder.mUnits = Unit_Auto;
    mEdges[3].mBorderStyle = 0;
    mEdges[3].mBorderColor = 0;
    mBoxOffset[3].mValue = 0.0f;      mBoxOffset[3].mUnits = Unit_Auto;
    mFontMetrics.mfFontSize = 11.0f;
    mFontMetrics.mfEmSize = 0.0f;
    mFontMetrics.mfExSize = 0.0f;
    mFontMetrics.mfAscent = 0.0f;
    mFontMetrics.mfDescent = 0.0f;
}
}  // namespace Style

// @ 0x008fc130
namespace Style {
StyleState::StyleState(const StyleState& src)
{
    mpBase = (StyleState*)&src;
    mpPage = src.mpPage;
    new (&mTextStyle) TextStyle(src.mTextStyle);
    mFontSize = src.mFontSize;
    mFgColor = src.mFgColor;
    mLineHeight = src.mLineHeight;
    mFontSmoothThresh = src.mFontSmoothThresh;
    mpBackgroundImage = 0;
    mBackgroundAttachment = 0;
    mBackgroundRepeat = 3;
    mBackgroundPosX.mValue = 0.0f;
    mBackgroundPosX.mUnits = Unit_Pixels;
    mBackgroundPosY.mValue = 0.0f;
    mBackgroundPosY.mUnits = Unit_Pixels;
    mBgColor = 0;
    mColorInherited = src.mColorInherited;
    mWordSpacing = src.mWordSpacing;
    mLetterSpacing = src.mLetterSpacing;
    mVerticalAlign = src.mVerticalAlign;
    mVerticalAlignKW = src.mVerticalAlignKW;
    mTextTransform = src.mTextTransform;
    mTextIndent = src.mTextIndent;
    mBoxX.mValue = 0.0f;
    mBoxX.mUnits = Unit_Auto;
    mBoxY.mValue = 0.0f;
    mBoxY.mUnits = Unit_Auto;
    mField37c = 0;
    mField380 = 0;
    mField384 = 0;
    mTableAlign = 3;
    mField3ac = src.mField3ac;
    mField3b0 = src.mField3b0;
    mField3b4 = src.mField3b4;
    mField3b8 = src.mField3b8;
    mCounters.mFieldsInit();
    mCounterIncrement.mFieldsInit();
    mCounterReset.mFieldsInit();
    mBorderSpacingH = src.mBorderSpacingH;
    mBorderSpacingV = src.mBorderSpacingV;
    mField42c = src.mField42c;
    mFontMetrics = src.mFontMetrics;
    mField44c = src.mField44c;
    for (int i = 0; i < 4; ++i) {
        mEdges[i].mMargin.mValue = 0.0f;
        mEdges[i].mMargin.mUnits = Unit_Auto;
        mEdges[i].mPadding.mValue = 0.0f;
        mEdges[i].mPadding.mUnits = Unit_Auto;
        mEdges[i].mBorder.mValue = 0.0f;
        mEdges[i].mBorder.mUnits = Unit_Auto;
        mEdges[i].mBorderStyle = 0;
        mEdges[i].mBorderColor = 0;
        mBoxOffset[i].mValue = 0.0f;
        mBoxOffset[i].mUnits = Unit_Auto;
    }
}
}  // namespace Style

// @ 0x008fc670
void TextStyle_s008f_c670::Update()
{
    if (m3a8 == 0)
        return;
    if (dirty) {
        m230 = m28c;
        Box5 base;
        if (parent) {
            base.u[0] = parent->box.u[0];
            base.u[1] = parent->box.u[1];
            base.u[2] = parent->box.u[2];
            base.u[3] = parent->box.u[3];
            base.u[4] = parent->box.u[4];
        } else {
            base.v[0] = 10.0f;
            base.v[1] = 10.0f;
            base.v[2] = 10.0f;
            base.v[3] = 10.0f;
            base.v[4] = 0.0f;
        }
        float sz;
        if (m288 == 10)
            sz = base.v[0];
        else
            sz = (float)floor((double)u284.Resolve(base.v[0], &base) + 0.5f);
        float lineSz;
        if (m29c == 10)
            lineSz = 12.0f;
        else
            lineSz = u298.Resolve(base.v[0], &base);
        const float& r = Clamp(sz, 6.0f, 256.0f);
        size = r;
        flag220 = lineSz < r;
        box.v[0] = r;
        box.v[2] = r;
        box.v[1] = r;
        box.v[3] = r;
        box.v[4] = 0.0f;
        FontServer* srv = GetFontServer(0);
        if (srv) {
            FontObj* fo = srv->GetFont(font, 0, 0, 0xffff, -1, 1);
            if (fo) {
                FontMetrics_s008f_c670 m;
                m.f4 = 0;
                if (fo->GetMetrics(&m)) {
                    box.v[2] = m.f24;
                    box.v[1] = m.f24;
                    box.v[3] = m.f10;
                    box.v[4] = m.f14;
                }
                fo->Release();
            }
        }
        f278 = (float)floor((double)u2cc.Resolve(base.v[0], &base));
        f27c = (float)floor((double)u2c4.Resolve(base.v[0], &base));
        f280 = (float)floor((double)u290.Resolve(base.v[0], &base));
        dirty = 0;
    }
    unsigned c = color;
    if ((c >> 24) != 0xff)
        c = BlendColor(c, color2);
    color2 = c;
    if (parent) {
        HItA it = tbl3fc.begin();
        HNodeA* node = it.node;
        HNodeA** bucket = it.bucket;
        if (node != tbl3fc.mpBucketArray[tbl3fc.mnBucketCount]) {
            do {
                const void* val = node->val;
                parent->tbl3bc[node->key] = val;
                node = node->next;
                while (node == 0)
                    node = *++bucket;
            } while (node != tbl3fc.mpBucketArray[tbl3fc.mnBucketCount]);
        }
        HItB it2 = tbl3dc.begin();
        while (it2.node != tbl3dc.end()) {
            HMapB* m = (HMapB*)&parent->tbl3bc;
            (*m)[it2.node->key] += it2.node->val;
            it2.increment();
        }
    }
}
