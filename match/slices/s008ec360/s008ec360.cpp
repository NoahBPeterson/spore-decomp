// Slice s008ec360 (batch gold4) — 0x008ec360 .. 0x008ecc90.
//
// EA::XHTML::Layout::Page member functions (Layout / Pick / GetTextStyle / LoadImage /
// Page / ~Page / SetViewportSize / AddResourceSlot / CreateLayoutItems / SetCurrentNode)
// plus the TextStyleHashtable (eastl fixed_hash_set) constructor and the rule-list filter.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (EA XHTML module, no /EHsc)

#include "types.h"
#include <new>

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// eastl bits used across the module
// ---------------------------------------------------------------------------
namespace eastl {

struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};

struct allocator {
    allocator() {}
    void deallocate(void* p) { operator delete(p); }
};

template <typename T, int N>
class fixed_vector {
public:
    // eastl fixed_vector in-situ init: begin = end = pool = buffer, capacity = buffer + N.
    fixed_vector()
    {
        mpPoolBegin = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + N;
    }

    T* mpBegin;                    // +0x00
    T* mpEnd;                      // +0x04
    T* mpCapacity;                 // +0x08
    allocator mOverflowAllocator;  // +0x0c
    T* mpPoolBegin;                // +0x10
    u32 mUnused;                   // +0x14
    T mBuffer[N];                  // +0x18

    int size() const { return (int)(mpEnd - mpBegin); }

    // slow push (0x00899480): __thiscall, (T* pEnd, const T* pValue)
    void DoPushBack(T* pEnd, const T* pValue);

    // vector grow (0x00962210): __thiscall, (T* pEnd, void** pOut)
    void Grow(T* pEnd, void** pOut);

    // eastl::vector::erase (0x00E25BD0): __thiscall, (T* first, T* last)
    void erase(T* pFirst, T* pLast);

    // Vec2b::Free (0x008E2B20): __thiscall, ()
    void Free();

    void push_back(T& v)
    {
        T* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoPushBack(p, &v);
        }
    }
};

}  // namespace eastl

namespace EA {
namespace Allocator {

class StackAllocator {
public:
    StackAllocator(void* p, u32 a, void* f1, void* f2, void* ctx);  // 0x00928CD0
    ~StackAllocator();                                              // 0x00928DC0
    void Reset(void* p);                                            // 0x00928C40
    bool AllocateNewBlock(u32 nSize);                               // 0x00928BA0

    __forceinline void* Malloc(u32 nSize)
    {
        if ((mpCurrentBlockEnd - mpCurrentObjectBegin) - (int)nSize < 0) {
            if (!AllocateNewBlock(nSize))
                return 0;
        }
        char* p = mpCurrentObjectBegin;
        mpCurrentObjectBegin = p + nSize;
        mpCurrentObjectEnd = p + nSize;
        return p;
    }

    u32 mnDefaultBlockSize;          // +0x00
    void* mpCurrentBlock;            // +0x04
    char* mpCurrentBlockEnd;         // +0x08
    char* mpCurrentObjectBegin;      // +0x0c
    char* mpCurrentObjectEnd;        // +0x10
    void* mpCoreAllocationFunction;  // +0x14
    void* mpCoreFreeFunction;        // +0x18
    void* mpCoreFunctionContext;     // +0x1c
    void* mpTopBookmark;             // +0x20
};

}  // namespace Allocator
}  // namespace EA

namespace EA {
namespace Text {

class Typesetter {
public:
    ~Typesetter();  // 0x0089C540
    u32 mData[0x530 / 4];
};

}  // namespace Text
}  // namespace EA

namespace EA {
namespace XHTML {

namespace Layout {
class Page;
class Item;
class PickingContext;
class StackingContext;
class ImageRequester;
class TextStyleHashtable;
class StyleNode;
}  // namespace Layout

namespace DOM {
class Node;
class Element;
}  // namespace DOM

namespace Style {

class Selector;
struct Property;
class Rule;

struct PropertyList {
    Property* mpFirst;  // +0x00
};

struct PropertyCollection {
    PropertyList mList[2];  // +0x00, +0x04
};

struct Property {
    u32 mKind;         // +0x00
    Property* mpNext;  // +0x04
};

struct Rule {
    Rule* mpNext;                // +0x00
    Selector* mpSelectors;       // +0x04
    PropertyCollection* mpProperties;  // +0x08
    int mSpecificity;            // +0x0c
};

class StyleState {
public:
    StyleState(const Layout::Page* pPage);  // 0x008FBE00
    ~StyleState();                          // 0x008E8650
    u8 mData[0x450];
};

class Selector {
public:
    virtual void vf00();
    virtual bool Matches(DOM::Element* pElement, int flag);  // +0x04
};

}  // namespace Style
}  // namespace XHTML
}  // namespace EA

namespace EA {
namespace XHTML {

namespace Layout {

struct RectF {
    float l, t, r, b;
};

// A simple ref-counted base (vtable slot +4 is the release call used all over this module).
class IRefCounted {
public:
    virtual void vf00();
    virtual void vf04();
};

class Item : public eastl::intrusive_list_node {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c(StackingContext* ctx, Style::StyleState* state);  // +0x0c
    virtual void vf10(RectF* pRect);                                    // +0x10
    virtual void vf14();
    virtual char vf18(PickingContext* ctx, u32* out);                   // +0x18

    Page* mpPage;             // +0x0c
    int mItemType;            // +0x10
    u32 mSelectableIndex;     // +0x14
};

class ImageRequester {
public:
    virtual void vf00();
    virtual void Request(char* pOut, const wchar_t* pURL, void* pCallback, void* pArg,
                         void* pListener, int flag);  // +0x04
    void* mpNextLoading;  // +0x04
    u32 mnJobId;          // +0x08
};

struct Stylesheet : public IRefCounted {
    u32 mPad[0x28 / 4];     // +0x04 .. +0x2b
    Style::Rule* mpFirst;   // +0x2c
};

struct Document : public IRefCounted {
    u32 mPad0[0x20 / 4];    // +0x04 .. +0x23
    void* mField24;         // +0x24
    u32 mPad28;             // +0x28
    void* mField2c;         // +0x2c
    u32 mPad30[0x14 / 4];   // +0x30 .. +0x43
    void* mField44;         // +0x44
    void* mField48;         // +0x48
    void* mField4c;         // +0x4c
};

class TextStyleHashtable {
public:
    // Empty eastl hash/predicate tags. A user-provided (no-op) default constructor stops the
    // compiler from materialising and zero-initialising the temporaries the enclosing ctor
    // passes by reference (which would clobber ecx in Page::Page).
    struct HashTag { HashTag() {} };
    struct EqTag { EqTag() {} };

    // Node-pool descriptor handed to CommitInit (0x008EC020).
    struct PoolDesc {
        void* mpPoolBegin;      // +0x00
        void* mp04;             // +0x04
        void* mp08;             // +0x08
        void* mp0c;             // +0x0c
        u32   mnNodeSize;       // +0x10
        void* mpInlineBuckets;  // +0x14
    };

    // eastl::prime_rehash_policy (a temporary copy is used to size the table).
    struct Policy {
        float mfMaxLoad;  // +0x00
        float mfGrowth;   // +0x04
        u32   mVal08;     // +0x08

        u32 NextBucketCount(u32 nElementCount);  // 0x009213C0
    };

    TextStyleHashtable(const HashTag&, const EqTag&);            // 0x008EC6B0
    void DoRehash(u32 nNewBucketCount);                          // 0x008EBB30
    void DoInsertValue(void* pOut, const void* pKey, const void* pFlag); // 0x008EC280
    void Find(void* pOut, const void* pKey);                     // 0x008EC200
    void DoFreeNodes(void* pBuckets, u32 count);                 // 0x008EBBE0
    void CommitInit(void* pBuckets, void* a2, void* a3, void* a4, void* a5,
                    void* a6, PoolDesc* pDesc);                  // 0x008EC020

    void* mVptr;             // +0x00
    void** mpBuckets;        // +0x04
    u32 mnBucketCount;       // +0x08
    u32 mnSize;              // +0x0c
    float mfMaxLoad;         // +0x10
    float mfGrowth;          // +0x14
    u32 mVal18;              // +0x18
    void* mpFreeList;        // +0x1c
    u32 mPad20;              // +0x20
    void* mpPoolBegin;       // +0x24
    void* mpPoolEnd;         // +0x28
    u32 mnNodeSize;          // +0x2c
    void* mpInlineBuckets;   // +0x30
    u32 mPad34[0x41];        // +0x34 .. +0x137
    u8 mPool[0x9f00];        // +0x138
};

typedef eastl::fixed_vector<Style::Rule*, 16> RuleVec;

class Page : public EA::Allocator::StackAllocator {
public:
    Page();    // 0x008EC790
    ~Page();   // 0x008EC810

    void Layout();                                                          // 0x008EC360
    char Pick(const void* screenRect, u32* out);                            // 0x008EC4F0
    void* GetTextStyle(const Style::StyleState* s);                         // 0x008EC580
    void LoadImage(ImageRequester* pRequester, const wchar_t* pURL);        // 0x008EC5E0
    void SetViewportSize(float w, float h);                                 // 0x008EC8C0
    int AddResourceSlot();                                                  // 0x008EC910
    void CreateLayoutItems(DOM::Element* pElement, RuleVec* pOut);          // 0x008EC970
    void FilterRuleList(DOM::Element* pElement, RuleVec* pIn, RuleVec* pOut);  // 0x008ECC10
    char SetCurrentNode(DOM::Node* pNew);                                   // 0x008ECC90

    void NotifyImagesAbandoned();                                           // 0x008EB7A0
    void DestroyItem(Item* pItem);                                          // 0x008EBD50
    void CreateAttributeStyles(DOM::Element* pElement, Style::PropertyList* pOut);  // 0x008EBDE0

    Document* mpDocument;                        // +0x24
    Stylesheet* mpBuiltInStyles;                 // +0x28
    int mViewportW;                              // +0x2c
    int mViewportH;                              // +0x30
    int mPageW;                                  // +0x34
    int mPageH;                                  // +0x38
    Item* mpRootItem;                            // +0x3c
    Item* mpLastWS;                              // +0x40
    eastl::fixed_vector<void*, 127> mResourceTable;  // +0x44
    void* mpResources;                           // +0x258
    ImageRequester* mpImageRequester;            // +0x25c
    Item* mpFocusItem;                           // +0x260
    DOM::Node* mSelectableCount;                 // +0x264
    u32 mCursorPos;                              // +0x268
    u32 mSelStart;                               // +0x26c
    u32 mSelEnd;                                 // +0x270
    u32 mSelMin;                                 // +0x274
    u32 mSelMax;                                 // +0x278
    TextStyleHashtable mStyleCache;              // +0x27c
};

struct StackingContext {
    u32 mOwner;                        // +0x000
    EA::Text::Typesetter mTypesetter;  // +0x004
    RectF mContextRect;                // +0x534
    float mf544;                       // +0x544
    RectF mBoundsRect;                 // +0x548
    float mf558;                       // +0x558
    float mf55c;                       // +0x55c
    float mf560;                       // +0x560
    float mf564;                       // +0x564
    float mf568;                       // +0x568
    float mf56c;                       // +0x56c
    float mf570;                       // +0x570
    u8 mb574;                          // +0x574
    u8 mPad575[3];                     // +0x575
    void* mpFloatsHead;                // +0x578
    void* mpFloatsTail;                // +0x57c
    void* mf580;                       // +0x580

    StackingContext(u32 owner);                // 0x008EFAD0
    void SetContextRect(const RectF& r);       // 0x008EFC80
};

struct PickingContext {
    PickingContext(const void* screenRect);    // 0x008EE240
    EA::Text::Typesetter mTypesetter;          // +0x000
    u32 mPad530[(0x564 - 0x530) / 4];
    void* mVecBegin564;                        // +0x564
    void* mVecEnd568;                          // +0x568
    void* mVecCap56c;                          // +0x56c
    u32 mPad570;
    void* mpInline574;                         // +0x574
    u32 mPad578[(0xb84 - 0x578) / 4];
};

struct WString {
    wchar_t* mpBegin;     // +0x00
    wchar_t* mpEnd;       // +0x04
    wchar_t* mpCapacity;  // +0x08
};

// 0x008E37E0: returns a {begin,end} vector of Stylesheet* for the carried style list.
struct SheetVec {
    Stylesheet** mpBegin;
    Stylesheet** mpEnd;
};

class StyleNode {
public:
    SheetVec* GetStylesheets();  // 0x008E37E0
};

}  // namespace Layout

namespace DOM {

class Element {
public:
    const wchar_t* GetAttrValue(const wchar_t* pName);  // 0x008E45B0
};

class Node {
public:
    Element* AsElement();  // 0x008E52F0
    Node* Parent();        // 0x00FF0420
};

void ResolveRelativeURL(Layout::WString* pOut, const void* pBase, const wchar_t* pURL);  // 0x008E3FA0

}  // namespace DOM

namespace Style {

bool CSSParser_ParsePropertyCollection(const wchar_t* pStr, Layout::Page* pPage,
                                       void* pBuf, void* pListener);  // 0x008F9000

}  // namespace Style

namespace Layout {

void* GetResourceProvider();                      // 0x008FE480
int IntRange_Equals(void* a, void* b);            // 0x008EBA70
void ImageRequestCallback_8ec010();               // 0x008EC010

// fixed_pool_base used by the style-cache hashtable.
struct FixedPool {
    void* mpHead;  // +0x00
    void init(void* pBegin, u32 nSize, u32 nNodeSize, u32 nAlign, u32 nFlags);  // 0x00921260
};

void* Hashtable_PrimeRehash(u32 n);    // 0x00921340

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA

using namespace EA::XHTML;
using namespace EA::XHTML::Layout;
using EA::XHTML::Style::StyleState;
using EA::XHTML::Style::Rule;
using EA::XHTML::Style::PropertyList;
using EA::XHTML::Style::PropertyCollection;
using EA::XHTML::Style::Property;

// ===========================================================================
// 0x008EC360  EA::XHTML::Layout::Page::Layout
// ===========================================================================
// @ 0x008ec360
void Page::Layout()
{
    if (!mpRootItem)
        return;
    if (mViewportW <= 0)
        return;
    if (mViewportH <= 0)
        return;

    StackingContext ctx((u32)mpRootItem);
    RectF rect;
    rect.l = 0.0f;
    rect.t = 0.0f;
    rect.r = (float)mViewportW;
    rect.b = (float)mViewportH;
    mPageH = 0;
    mPageW = 0;
    ctx.SetContextRect(rect);

    StyleState state(this);
    mpRootItem->vf0c(&ctx, &state);

    rect.l = 0.0f;
    rect.t = 0.0f;
    rect.r = (float)mViewportW;
    rect.b = (float)mViewportH;
    mpRootItem->vf10(&rect);

    if (mpRootItem->mItemType == 3) {
        rect = ctx.mBoundsRect;
        float w = *(float*)((char*)mpRootItem + 0x7c) - *(float*)((char*)mpRootItem + 0x74);
        float h = *(float*)((char*)mpRootItem + 0x70) - *(float*)((char*)mpRootItem + 0x68);
        mPageW = (int)(w > rect.r ? w : rect.r);
        mPageH = (int)(h > rect.b ? h : rect.b);
    }
}

// ===========================================================================
// 0x008EC4F0  EA::XHTML::Layout::Page::Pick
// ===========================================================================
// @ 0x008ec4f0
char Page::Pick(const void* screenRect, u32* out)
{
    out[0] = 0;
    out[1] = 0;
    out[4] = 0;
    out[5] = 0;
    out[6] = 0;
    if (!mpRootItem)
        return 0;
    PickingContext ctx(screenRect);
    char r = mpRootItem->vf18(&ctx, out);
    if (ctx.mVecBegin564 && ctx.mVecBegin564 != ctx.mpInline574)
        operator delete(ctx.mVecBegin564);
    return r;
}

// ===========================================================================
// 0x008EC580  EA::XHTML::Layout::Page::GetTextStyle
// ===========================================================================
// @ 0x008ec580
void* Page::GetTextStyle(const StyleState* s)
{
    void* local[3];
    TextStyleHashtable* pCache = &mStyleCache;
    const void* key = (const char*)s + 0xc;
    pCache->Find(local, key);
    if (local[0] == ((void**)pCache->mpBuckets)[pCache->mnBucketCount]) {
        ((unsigned char*)&s)[0] = 0;
        pCache->DoInsertValue(local, key, (const void*)s);
    }
    return local[0];
}

// ===========================================================================
// 0x008EC5E0  EA::XHTML::Layout::Page::LoadImage
// ===========================================================================
// @ 0x008ec5e0
void Page::LoadImage(ImageRequester* pRequester, const wchar_t* pURL)
{
    if (!mpImageRequester)
        return;

    wchar_t buf[96];
    WString url;
    url.mpBegin = buf;
    url.mpEnd = buf;
    url.mpCapacity = buf + 96;
    buf[0] = 0;
    const wchar_t* pBuf = buf;

    const wchar_t* pBase = (const wchar_t*)mpDocument->mField4c;
    if (!pBase)
        pBase = (const wchar_t*)mpDocument->mField48;
    DOM::ResolveRelativeURL(&url, pBase, pURL);

    pRequester->mpNextLoading = mpResources;
    mpResources = pRequester;

    mpImageRequester->Request((char*)pRequester + 8, url.mpBegin,
                              (void*)&ImageRequestCallback_8ec010, this,
                              mpDocument->mField44, 0);

    if (url.mpBegin && url.mpBegin != pBuf &&
        (int)(((char*)url.mpCapacity - (char*)url.mpBegin) & 0xfffffffe) > 2)
        operator delete(url.mpBegin);
}

// ===========================================================================
// 0x008EC6B0  eastl::fixed_hash_set<EA::Text::TextStyle,...>::fixed_hash_set
// ===========================================================================
// @ 0x008ec6b0
TextStyleHashtable::TextStyleHashtable(const HashTag& h, const EqTag& e)
{
    FixedPool pool;
    pool.mpHead = 0;
    pool.init((char*)this + 0x138, 0x9f00, 0x27c, 4, 0);

    PoolDesc desc;
    desc.mpPoolBegin = (char*)this + 0x138;
    desc.mp04 = (char*)this + 0x138;
    desc.mp08 = (char*)this + 0xa038;
    desc.mp0c = 0;
    desc.mnNodeSize = 0x27c;
    desc.mpInlineBuckets = (char*)this + 0x34;

    void* pBuckets = Hashtable_PrimeRehash(0x40);
    this->CommitInit(pBuckets, (void*)&h, (void*)&desc, (void*)&desc, (void*)&e,
                     (void*)&desc, &desc);

    Policy pol;
    pol.mfMaxLoad = 10000.0f;
    pol.mfGrowth = 2.0f;
    pol.mVal08 = 0;
    mfMaxLoad = 10000.0f;
    mfGrowth = 2.0f;
    mVal18 = 0;
    u32 n = pol.NextBucketCount(mnSize);
    if (n > mnBucketCount)
        DoRehash(n);
}

// ===========================================================================
// 0x008EC790  EA::XHTML::Layout::Page::Page
// ===========================================================================
// @ 0x008ec790
Page::Page()
    : EA::Allocator::StackAllocator(0, 0xffffffffu, 0, 0, 0),
      mpDocument(0),
      mpBuiltInStyles(0),
      mpRootItem(0),
      mResourceTable(),
      mpResources(0),
      mpImageRequester((ImageRequester*)GetResourceProvider()),
      mpFocusItem(0),
      mSelectableCount(0),
      mSelStart(0),
      mSelEnd(0),
      mSelMin(0),
      mSelMax(0),
      mStyleCache(TextStyleHashtable::HashTag(), TextStyleHashtable::EqTag())
{
}

// ===========================================================================
// 0x008EC810  EA::XHTML::Layout::Page::~Page
// ===========================================================================
// @ 0x008ec810
Page::~Page()
{
    NotifyImagesAbandoned();
    DestroyItem(mpRootItem);

    eastl::fixed_vector<void*, 127>& table = mResourceTable;
    TextStyleHashtable& c = mStyleCache;

    table.erase(table.mpBegin, table.mpEnd);

    EA::Allocator::StackAllocator::Reset(0);

    c.DoFreeNodes(c.mpBuckets, c.mnBucketCount);

    void* pBuckets = c.mpBuckets;
    c.mnSize = 0;
    if (c.mnBucketCount > 1 && pBuckets != c.mpInlineBuckets) {
        if (pBuckets >= c.mpPoolBegin && pBuckets < c.mpPoolEnd) {
            *(void**)pBuckets = c.mpFreeList;
            c.mpFreeList = pBuckets;
        } else {
            operator delete(pBuckets);
        }
    }

    table.Free();

    if (mpBuiltInStyles)
        mpBuiltInStyles->vf04();
    if (mpDocument)
        mpDocument->vf04();
}

// ===========================================================================
// 0x008EC8C0  EA::XHTML::Layout::Page::SetViewportSize
// ===========================================================================
// @ 0x008ec8c0
void Page::SetViewportSize(float w, float h)
{
    if (w != (float)mViewportW || h != (float)mViewportH) {
        mViewportW = (int)w;
        mViewportH = (int)h;
        if (mpRootItem)
            Layout();
    }
}

// ===========================================================================
// 0x008EC910  EA::XHTML::Layout::Page::AddResourceSlot
// ===========================================================================
// @ 0x008ec910
int Page::AddResourceSlot()
{
    eastl::fixed_vector<void*, 127>* pv = &mResourceTable;
    void** pEnd = pv->mpEnd;
    IRefCounted* pObj = 0;
    int n = (int)(pv->mpEnd - pv->mpBegin);
    if (pEnd < pv->mpCapacity) {
        pv->mpEnd = pEnd + 1;
        if (pEnd)
            *pEnd = 0;
    } else {
        pv->Grow(pEnd, (void**)&pObj);
        if (pObj)
            pObj->vf04();
    }
    return n;
}

// ===========================================================================
// 0x008EC970  EA::XHTML::Layout::Page::CreateLayoutItems
// ===========================================================================
// @ 0x008ec970
void Page::CreateLayoutItems(DOM::Element* pElement, RuleVec* pOut)
{
    SheetVec* pSheets = ((StyleNode*)*(void**)((char*)pElement + 0x10))->GetStylesheets();

    Stylesheet* pBuiltIn = mpBuiltInStyles;
    if (pBuiltIn) {
        for (Rule* r = pBuiltIn->mpFirst; r; r = r->mpNext) {
            if (r->mpSelectors->Matches(pElement, 1))
                pOut->push_back(r);
        }
    }

    if (pSheets->mpBegin != pSheets->mpEnd) {
        for (Stylesheet** it = pSheets->mpBegin; it != pSheets->mpEnd; ++it) {
            for (Rule* r = (*it)->mpFirst; r; r = r->mpNext) {
                if (r->mpSelectors->Matches(pElement, 1))
                    pOut->push_back(r);
            }
        }
    }

    PropertyList props;
    props.mpFirst = 0;
    CreateAttributeStyles(pElement, &props);
    if (props.mpFirst) {
        PropertyCollection* pc = (PropertyCollection*)this->Malloc(8);
        if (pc) {
            pc->mList[0].mpFirst = 0;
            pc->mList[1].mpFirst = 0;
        }
        if (props.mpFirst) {
            Property* p = props.mpFirst;
            while (p->mpNext)
                p = p->mpNext;
            p->mpNext = pc->mList[0].mpFirst;
            pc->mList[0].mpFirst = props.mpFirst;
        }
        Rule* pRule = (Rule*)this->Malloc(0x10);
        if (pRule) {
            pRule->mpNext = 0;
            pRule->mpSelectors = 0;
            pRule->mpProperties = pc;
            pRule->mSpecificity = 0;
        }
        pOut->push_back(pRule);
    }

    const wchar_t* pStyle = pElement->GetAttrValue(L"style");
    if (!pStyle)
        return;

    PropertyCollection* pcInline = (PropertyCollection*)this->Malloc(8);
    if (pcInline) {
        pcInline->mList[0].mpFirst = 0;
        pcInline->mList[1].mpFirst = 0;
    }
    if (!EA::XHTML::Style::CSSParser_ParsePropertyCollection(pStyle, this, pcInline,
                                                             mpDocument->mField44))
        return;

    Rule* pRule = (Rule*)this->Malloc(0x10);
    if (pRule) {
        pRule->mpNext = 0;
        pRule->mpSelectors = 0;
        pRule->mpProperties = pcInline;
        pRule->mSpecificity = 0x3e8;
    }
    pOut->push_back(pRule);
}

// ===========================================================================
// 0x008ECC10  EA::XHTML::Layout::Page::FilterRuleList
// ===========================================================================
// @ 0x008ecc10
void Page::FilterRuleList(DOM::Element* pElement, RuleVec* pIn, RuleVec* pOut)
{
    for (int i = 0; i < pIn->size(); ++i) {
        Rule* r = pIn->mpBegin[i];
        Style::Selector* pSel = r->mpSelectors;
        if (!pSel || pSel->Matches(pElement, 0))
            pOut->push_back(r);
    }
}

// ===========================================================================
// 0x008ECC90  EA::XHTML::Layout::Page::SetCurrentNode
// ===========================================================================
// @ 0x008ecc90
char Page::SetCurrentNode(DOM::Node* pNew)
{
    if (pNew == mSelectableCount)
        return 0;

    char bChanged = 0;

    for (DOM::Node* n = mSelectableCount; n; n = n->Parent()) {
        DOM::Element* e = n->AsElement();
        if (!e)
            continue;

        RuleVec rules, a, b;

        CreateLayoutItems(e, &rules);
        FilterRuleList(e, &rules, &a);
        *(int*)((char*)e + 0x30) = 0;
        FilterRuleList(e, &rules, &b);
        if (IntRange_Equals(&a, &b))
            bChanged = 1;

        if (a.mpBegin && a.mpBegin != a.mpPoolBegin)
            operator delete(a.mpBegin);
        if (b.mpBegin && b.mpBegin != b.mpPoolBegin)
            operator delete(b.mpBegin);
        if (rules.mpBegin && rules.mpBegin != rules.mpPoolBegin)
            operator delete(rules.mpBegin);
    }

    mSelectableCount = pNew;
    if (!pNew)
        return bChanged;

    for (DOM::Node* n = pNew; n; n = n->Parent()) {
        DOM::Element* e = n->AsElement();
        if (!e)
            continue;

        RuleVec rules, a, b;

        CreateLayoutItems(e, &rules);
        FilterRuleList(e, &rules, &a);
        *(int*)((char*)e + 0x30) = 1;
        FilterRuleList(e, &rules, &b);

        int nA = (int)((char*)a.mpEnd - (char*)a.mpBegin);
        int nB = (int)((char*)b.mpEnd - (char*)b.mpBegin);
        if (((nA ^ nB) & 0xfffffffc) != 0) {
            bChanged = 1;
        } else {
            int* p = (int*)b.mpBegin;
            int* pEnd = (int*)b.mpEnd;
            int* q = (int*)((char*)p + ((char*)a.mpBegin - (char*)b.mpBegin));
            while (p != pEnd) {
                if (*p != *q) {
                    bChanged = 1;
                    break;
                }
                ++p;
                ++q;
            }
        }

        if (b.mpBegin && b.mpBegin != b.mpPoolBegin)
            operator delete(b.mpBegin);
        if (a.mpBegin && a.mpBegin != a.mpPoolBegin)
            operator delete(a.mpBegin);
        if (rules.mpBegin && rules.mpBegin != rules.mpPoolBegin)
            operator delete(rules.mpBegin);
    }

    return bChanged;
}
