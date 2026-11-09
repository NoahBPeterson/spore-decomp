// src/game/UTFSpore_Win32/Page.cpp -- migrated from slice(s) s008ec360, s008eb250 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Page.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/Allocator/StackAllocator.h"
#include <string.h>
#include "EA/XHTML/DOM/Document.h"
#include "EA/XHTML/Style/Stylesheet.h"
#include "EA/Text/Typesetter.h"
#include <new>

// ---- items of slice s008eb250 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct intrusive_list_node_s008e_b250 {
    intrusive_list_node_s008e_b250* mpNext;
    intrusive_list_node_s008e_b250* mpPrev;
    void Destroy();  // 0x00620230
};  // namespace eastl
}
namespace EA {
namespace Allocator {
class StackAllocator_s008e_b250 {
public:
    unsigned int mnDefaultBlockSize;  // +0x00
    void* mpCurrentBlock;             // +0x04
    char* mpCurrentBlockEnd;          // +0x08
    char* mpCurrentObjectBegin;       // +0x0c
    char* mpCurrentObjectEnd;         // +0x10
    void* mpCoreAllocationFunction;   // +0x14
    void* mpCoreFreeFunction;         // +0x18
    void* mpCoreFunctionContext;      // +0x1c
    void* mpTopBookmark;              // +0x20
};  // namespace Allocator
}  // namespace EA
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState { public:
    uint32_t pad000[0x37c / 4];
    int mFloat;                      // +0x37c
    uint32_t pad380;
    int mPosition;                   // +0x384
    uint32_t pad388[(0x3a8 - 0x388) / 4];
    int mDisplay;                    // +0x3a8
    int mWhiteSpace;                 // +0x3ac
    int mListStyleType;              // +0x3b0
    const wchar_t* mListStyleImage;  // +0x3b4
    uint32_t pad3b8[(0x450 - 0x3b8) / 4];
};  // namespace Style
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
struct TextStyle { uint32_t mData[0x27c / 4]; };
}
}
}
namespace EA {
namespace XHTML {
namespace Text {
class Typesetter {
public:
    uint32_t mData[0x240 / 4];
    void Reset(bool bReset);
    void SetWidth(float fLineWidth, float x, float y);
    int LayoutLine(const wchar_t* pText, unsigned int nLength, float fLineWidth, float fY,
                   const TextStyle* pStyle);
    void* GetLineLayout();
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_b250;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Border;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Background;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TextStyleHashtable;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ImageRequester {
public:
    virtual ~ImageRequester();
    virtual void vf04();
    virtual void OnImageRequest(void* pArg);
    void* mpVf1;            // +0x04
    unsigned int mnJobId;   // +0x08
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item : public eastl::intrusive_list_node_s008e_b250 {
public:
    Item(Page_s008e_b250* pPage, int itemType);  // 0x008EAE40
    virtual ~Item();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();

    Page_s008e_b250* mpPage;                   // +0x0c
    int mItemType;                  // +0x10
    unsigned int mSelectableIndex;  // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TextItem : public Item {
public:
    TextItem(Page_s008e_b250* pPage, const wchar_t* pText, int nLength);  // 0x008EB6F0
    wchar_t* mpCharData;  // +0x18
    int mLength;          // +0x1c
    void* mpTextStyle;    // +0x20
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ContainerItem : public Item {
public:
    __forceinline ContainerItem(Page_s008e_b250* pPage, int type) : Item(pPage, type) {}
    eastl::intrusive_list_node_s008e_b250 mChildItems;  // +0x18
    void* mpElement;                         // +0x20
    void* mStyleRules;                       // +0x24
    unsigned int mnRuleCount;                // +0x28
    int mDisplay;                            // +0x2c
    int mPosition;                           // +0x30
    int mPlacement;                          // +0x34
    unsigned int mFgColor;                   // +0x38
    unsigned int mBgColor;                   // +0x3c
    Border* mpBorder;                        // +0x40
    Background* mpBackground;                // +0x44
    uint32_t mParaStyle[(0x50 - 0x48) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Block : public ContainerItem {
public:
    Block(Page_s008e_b250* pPage, void* pElement, int type);  // 0x008E7F90
    uint32_t pad50[(0xc4 - 0x50) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class InlineItem : public ContainerItem {
public:
    InlineItem(Page_s008e_b250* pPage, void* pElement, int type);  // 0x008EBC50
    uint32_t pad50[(0x5c - 0x50) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableCell : public Block {
public:
    TableCell(Page_s008e_b250* pPage, void* pElement);  // 0x008EBCA0
    int mRowSpan;      // +0xc4
    int mColSpan;      // +0xc8
    int mRow;          // +0xcc
    int mCol;          // +0xd0
    float mMinWidth;   // +0xd4
    float mMaxWidth;   // +0xd8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableRow : public ContainerItem {
public:
    TableRow(Page_s008e_b250* pPage, void* pElement);  // 0x008EC170
    uint32_t pad50[(0x5c - 0x50) / 4];
    void* mpCellsBegin;     // +0x5c
    void* mpCellsEnd;       // +0x60
    void* mpCellsCapacity;  // +0x64
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TableGroup : public ContainerItem {
public:
    TableGroup(Page_s008e_b250* pPage, void* pElement, int type);  // 0x008EBD00
    uint32_t pad50[3];
    void* mpField5c;  // +0x5c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class RefItem {
public:
    virtual void vf0();
    virtual void Release(int flag);
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_b250 {
public:
    EA::Allocator::StackAllocator_s008e_b250 mAllocator;  // +0x00
    uint32_t pad24[(0x3c - 0x24) / 4];
    Item* mpRootItem;  // +0x3c
    void* mpLastWS;    // +0x40
    uint32_t pad44[(0x258 - 0x44) / 4];
    void* mpResources;       // +0x258
    void* mpImageRequester;  // +0x25c
    void* mpFocusItem;       // +0x260
    uint32_t pad264[2];
    unsigned int mSelStart;  // +0x26c
    unsigned int mSelEnd;    // +0x270
    unsigned int mSelMin;    // +0x274
    unsigned int mSelMax;    // +0x278
    uint32_t pad27c[(0x2a0 - 0x27c) / 4];

    void Render(Text::Typesetter* pTS, const float* pRect, const void* pState);  // 0x008EB870
    void* GetResource(int index);                                                // 0x008EB960
    void* GetTextStyle(const Style::StyleState& s);                              // 0x008EC580
    void NotifyImagesAbandoned();                                                // 0x008EB7A0
    void SetImageRequester(void* pNew, int flag);                                // 0x008EB7E0
    void SetChildItem(unsigned int index, void* pItem);                          // 0x008EB910
    void ImageRequestCallback(int* pMsg);                                        // 0x008EB980
    void SetSelectionRange(unsigned int a, unsigned int b);                      // 0x008EBA20
    void CreateAttributeStyles(void* pElement, void* pOut);                      // 0x008EBDE0
    static void DestroyItem(ContainerItem* pItem);                               // 0x008EBD50
};
}
}
}
void CreateAttributeStyleFn(unsigned int a, unsigned int b, void* pPage, const void* pState,
                            int flag, void* pListener);
unsigned int StyleAttr_GetKind(void* pAttr);
void RenderingContext_Ctor(void* pCtx, void* pTS, const float* pRect, const void* pState);  // 0x008EE810
void Typesetter_Dtor(void* pCtx);          // 0x0089C540
void* Page_GetSelectionInterface(void* pPage);  // 0x008E2810
unsigned int ComputeStyleHash(const void* pStyle);  // 0x00894440
bool TextStyle_Equals(const void* a, const void* b);  // 0x008942A0
void* TextStyle_CopyCtor(void* pDst, const void* pSrc);  // 0x008945A0
void* EAAllocate(unsigned int nSize, const char* pName, int a, int b, const char* pFile, int line);
using EA::XHTML::Style::StyleState;
struct SizeNode {
    virtual void vf0();
    virtual void vf1();
    virtual int GetSize();
};
struct NodeSizeIter {
    int mValue;    // +0x00
    void* mpNode;  // +0x04
    int mCount;    // +0x08
    int mTotal;    // +0x0c
    NodeSizeIter* Init(void* pNode, int a, int b);
};
struct IntRange {
    int* mpBegin;
    int* mpEnd;
};
namespace EA {
namespace XHTML {
namespace Layout {
class TextStyleHashtable {
public:
    void DoRehash(unsigned int nNewBucketCount);                     // 0x008EBB30
    void* AllocNode(const void* pStyle);                            // 0x008EC0E0
    static void* __stdcall FindNodeInBucket(void* pNode, const void* pStyle,
                                           unsigned int hash);  // 0x008EC130
    void Find(void* pOut, const void* pStyle);                      // 0x008EC200
    void DoInsertValue(void* pOut, const void* pStyle);             // 0x008EC280
    void* Destroy(unsigned char flags);                             // 0x008EC1C0

    void* mVptr;                 // +0x00
    void** mpBuckets;            // +0x04
    unsigned int mnBucketCount;  // +0x08
    unsigned int mnSize;         // +0x0c
    uint32_t mAllocator0;        // +0x10
    uint32_t mAllocator1;        // +0x14
    void* mListNext;             // +0x18
    void* mpFreeList;            // +0x1c
    uint32_t pad20;              // +0x20
    uint32_t pad24;              // +0x24
    void* mpPoolEnd;             // +0x28
    unsigned int mPoolStorage;   // +0x2c
    void* mpPoolBegin;           // +0x30
    void* mpPoolBegin2;          // +0x34
    uint32_t pad38[(0x5c - 0x38) / 4];
    void* mpSecondary;           // +0x5c
};  // namespace Layout
}  // namespace XHTML
}  // namespace EA
}
using EA::XHTML::Layout::TextStyleHashtable;
int Hashtable_GetNextBucketCount(unsigned int nSize)
{
    return (int)nSize;
}
void Hashtable_GetRehashHint(void* pOut, unsigned int nBucketCount, unsigned int nSize, int a);
// ---- items of slice s008eb250 end

// ---- items of slice s008ec360 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
namespace eastl {
struct intrusive_list_node_s008e_c360 {
    intrusive_list_node_s008e_c360* mpNext;
    intrusive_list_node_s008e_c360* mpPrev;
};
}
namespace eastl {
class allocator_s008e_c360 { public:
    allocator_s008e_c360() {}
    void deallocate(void* p) { operator delete(p); }
};
}
namespace eastl {
template <typename T, int N>
class fixed_vector_s008e_c360 {
public:
    // eastl fixed_vector in-situ init: begin = end = pool = buffer, capacity = buffer + N.
    fixed_vector_s008e_c360()
    {
        mpPoolBegin = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + N;
    }

    T* mpBegin;                    // +0x00
    T* mpEnd;                      // +0x04
    T* mpCapacity;                 // +0x08
    allocator_s008e_c360 mOverflowAllocator;  // +0x0c
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
}
namespace EA {
namespace Allocator {
class StackAllocator_s008e_c360 {
public:
    StackAllocator_s008e_c360(void* p, u32 a, void* f1, void* f2, void* ctx);  // 0x00928CD0
    ~StackAllocator_s008e_c360();                                              // 0x00928DC0
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
};  // namespace Allocator
}
}
namespace EA {
namespace Text {
class Typesetter_s008e_c360 {
public:
    ~Typesetter_s008e_c360();  // 0x0089C540
    u32 mData[0x530 / 4];
};  // namespace Text
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_c360;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_c360;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickingContext;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class StackingContext;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ImageRequester_s008e_c360;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TextStyleHashtable_s008e_c360;
}
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Node;
}
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Element;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Selector;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Property;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Rule;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class PropertyList { public:
    Property* mpFirst;  // +0x00
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class PropertyCollection { public:
    PropertyList mList[2];  // +0x00, +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Property { public:
    u32 mKind;         // +0x00
    Property* mpNext;  // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Rule { public:
    Rule* mpNext;                // +0x00
    Selector* mpSelectors;       // +0x04
    PropertyCollection* mpProperties;  // +0x08
    int mSpecificity;            // +0x0c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StyleState_s008e_c360 {
public:
    StyleState_s008e_c360(const Layout::Page_s008e_c360* pPage);  // 0x008FBE00
    ~StyleState_s008e_c360();                          // 0x008E8650
    u8 mData[0x450];
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Selector {
public:
    virtual void vf00();
    virtual bool Matches(DOM::Element* pElement, int flag);  // +0x04
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct RectF {
    float l, t, r, b;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class IRefCounted {
public:
    virtual void vf00();
    virtual void vf04();
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Item_s008e_c360 : public eastl::intrusive_list_node_s008e_c360 {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c(StackingContext* ctx, Style::StyleState_s008e_c360* state);  // +0x0c
    virtual void vf10(RectF* pRect);                                    // +0x10
    virtual void vf14();
    virtual char vf18(PickingContext* ctx, u32* out);                   // +0x18

    Page_s008e_c360* mpPage;             // +0x0c
    int mItemType;            // +0x10
    u32 mSelectableIndex;     // +0x14
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class ImageRequester_s008e_c360 {
public:
    virtual void vf00();
    virtual void Request(char* pOut, const wchar_t* pURL, void* pCallback, void* pArg,
                         void* pListener, int flag);  // +0x04
    void* mpNextLoading;  // +0x04
    u32 mnJobId;          // +0x08
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct Stylesheet : public IRefCounted {
    u32 mPad[0x28 / 4];     // +0x04 .. +0x2b
    Style::Rule* mpFirst;   // +0x2c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TextStyleHashtable_s008e_c360 {
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

    TextStyleHashtable_s008e_c360(const HashTag&, const EqTag&);            // 0x008EC6B0
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
typedef eastl::fixed_vector_s008e_c360<Style::Rule*, 16> RuleVec;
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class Page_s008e_c360 : public EA::Allocator::StackAllocator_s008e_c360 {
public:
    Page_s008e_c360();    // 0x008EC790
    ~Page_s008e_c360();   // 0x008EC810

    void Layout();                                                          // 0x008EC360
    char Pick(const void* screenRect, u32* out);                            // 0x008EC4F0
    void* GetTextStyle(const Style::StyleState_s008e_c360* s);                         // 0x008EC580
    void LoadImage(ImageRequester_s008e_c360* pRequester, const wchar_t* pURL);        // 0x008EC5E0
    void SetViewportSize(float w, float h);                                 // 0x008EC8C0
    int AddResourceSlot();                                                  // 0x008EC910
    void CreateLayoutItems(DOM::Element* pElement, RuleVec* pOut);          // 0x008EC970
    void FilterRuleList(DOM::Element* pElement, RuleVec* pIn, RuleVec* pOut);  // 0x008ECC10
    char SetCurrentNode(DOM::Node* pNew);                                   // 0x008ECC90

    void NotifyImagesAbandoned();                                           // 0x008EB7A0
    void DestroyItem(Item_s008e_c360* pItem);                                          // 0x008EBD50
    void CreateAttributeStyles(DOM::Element* pElement, Style::PropertyList* pOut);  // 0x008EBDE0

    Document* mpDocument;                        // +0x24
    Stylesheet* mpBuiltInStyles;                 // +0x28
    int mViewportW;                              // +0x2c
    int mViewportH;                              // +0x30
    int mPageW;                                  // +0x34
    int mPageH;                                  // +0x38
    Item_s008e_c360* mpRootItem;                            // +0x3c
    Item_s008e_c360* mpLastWS;                              // +0x40
    eastl::fixed_vector_s008e_c360<void*, 127> mResourceTable;  // +0x44
    void* mpResources;                           // +0x258
    ImageRequester_s008e_c360* mpImageRequester;            // +0x25c
    Item_s008e_c360* mpFocusItem;                           // +0x260
    DOM::Node* mSelectableCount;                 // +0x264
    u32 mCursorPos;                              // +0x268
    u32 mSelStart;                               // +0x26c
    u32 mSelEnd;                                 // +0x270
    u32 mSelMin;                                 // +0x274
    u32 mSelMax;                                 // +0x278
    TextStyleHashtable_s008e_c360 mStyleCache;              // +0x27c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class StackingContext { public:
    u32 mOwner;                        // +0x000
    EA::Text::Typesetter_s008e_c360 mTypesetter;  // +0x004
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickingContext { public:
    PickingContext(const void* screenRect);    // 0x008EE240
    EA::Text::Typesetter_s008e_c360 mTypesetter;          // +0x000
    u32 mPad530[(0x564 - 0x530) / 4];
    void* mVecBegin564;                        // +0x564
    void* mVecEnd568;                          // +0x568
    void* mVecCap56c;                          // +0x56c
    u32 mPad570;
    void* mpInline574;                         // +0x574
    u32 mPad578[(0xb84 - 0x578) / 4];
};
}
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Element {
public:
    const wchar_t* GetAttrValue(const wchar_t* pName);  // 0x008E45B0
};
}
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Node {
public:
    Element* AsElement();  // 0x008E52F0
    Node* Parent();        // 0x00FF0420
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct FixedPool {
    void* mpHead;  // +0x00
    void init(void* pBegin, u32 nSize, u32 nNodeSize, u32 nAlign, u32 nFlags);  // 0x00921260
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void* Hashtable_PrimeRehash(u32 n);    // 0x00921340
}
}
}
using EA::XHTML::Style::StyleState_s008e_c360;
using EA::XHTML::Style::Rule;
using EA::XHTML::Style::PropertyList;
using EA::XHTML::Style::PropertyCollection;
using EA::XHTML::Style::Property;
// ---- items of slice s008ec360 end

// @ 0x008eb6f0
EA::XHTML::Layout::TextItem::TextItem(EA::XHTML::Layout::Page_s008e_b250* pPage, const wchar_t* pText, int nLength)
: EA::XHTML::Layout::Item(pPage, 1)
{
    mpCharData = (wchar_t*)pText;
    mLength = nLength;
    mpTextStyle = 0;
}

// @ 0x008eb720
NodeSizeIter* NodeSizeIter::Init(void* pNode, int a, int b)
{
    mValue = 0;
    mpNode = pNode;
    mCount = a;
    mTotal = b;
    while (pNode) {
        mTotal += ((SizeNode*)pNode)->GetSize();
        pNode = *(void**)((char*)pNode + 4);
    }
    return this;
}

// @ 0x008eb760
bool IsSpace(wchar_t c)
{
    unsigned short u = (unsigned short)c;
    return u == 0x20 || u == 9 || u == 0x0c || u == 0x0d || u == 0x0a || u == 0x200b;
}

// @ 0x008eb7a0
void EA::XHTML::Layout::Page_s008e_b250::NotifyImagesAbandoned()
{
    if (mpImageRequester) {
        void* p = mpResources;
        while (p) {
            void* pArg = *(void**)((char*)p + 8);
            ((EA::XHTML::Layout::ImageRequester*)mpImageRequester)->OnImageRequest(pArg);
            p = mpResources;
        }
    }
}

// @ 0x008eb7e0
void EA::XHTML::Layout::Page_s008e_b250::SetImageRequester(void* pNew, int flag)
{
    if (mpFocusItem) {
        *(int*)((char*)mpFocusItem + 0xc) = 1;
    }
    mpFocusItem = pNew;
    if (pNew) {
        *(int*)((char*)pNew + 0xc) = flag;
    }
}

// @ 0x008eb870
void EA::XHTML::Layout::Page_s008e_b250::Render(Text::Typesetter* pTS, const float* pRect, const void* pState)
{
    if (mpRootItem) {
        char ctx[0x578];
        RenderingContext_Ctor(ctx, pTS, pRect, pState);
        (*(void (**)(void*, void*))(*(int*)mpRootItem + 0x14))(mpRootItem, ctx);
        Typesetter_Dtor(ctx);
        return;
    }
    (*(void (**)(void*, int))(*(int*)pTS + 4))(pTS, 0x7fffffff);
    (*(void (**)(void*, float, float, float, float))(*(int*)pTS + 0x38))(pTS, pRect[0], pRect[1],
                                                                        pRect[2], pRect[3]);
}

// @ 0x008eb910
void EA::XHTML::Layout::Page_s008e_b250::SetChildItem(unsigned int index, void* pItem)
{
    char* pBase = *(char**)((char*)this + 0x44);
    int nCount = (int)((char*)*(void**)((char*)this + 0x48) - pBase) >> 2;
    if (index >= (unsigned int)nCount)
        return;
    void** pSlot = (void**)(pBase + index * 4);
    void* pOld = *pSlot;
    if (pItem == pOld)
        return;
    if (pItem)
        ((EA::XHTML::Layout::RefItem*)pItem)->vf0();
    *pSlot = pItem;
    if (pOld)
        ((EA::XHTML::Layout::RefItem*)pOld)->Release(1);
}

// @ 0x008eb980
void EA::XHTML::Layout::Page_s008e_b250::ImageRequestCallback(int* pMsg)
{
    char* pSlot = (char*)this + 0x258;
    if (!*(void**)pSlot)
        return;
    void* pNode = *(void**)pSlot;
    while (*(int*)((char*)pNode + 8) != pMsg[1]) {
        pSlot = (char*)pNode + 4;
        pNode = *(void**)pSlot;
        if (!pNode)
            return;
    }
    if (pMsg[0] == 2)
        (*(void (**)(void*, int))(*(int*)pNode + 4))(pNode, pMsg[4]);
    else
        (*(void (**)(void*, int))(*(int*)pNode + 4))(pNode, 0);
    if (pMsg[0] != 4 && ((char*)pMsg)[8] == 0) {
        void* pObj = Page_GetSelectionInterface(*(void**)((char*)this + 0x24));
        int local[2];
        local[0] = 6;
        local[1] = (int)pObj;
        (*(void (**)(void*, int*, int))(*(int*)pObj + 0x24))(pObj, local, 1);
    }
    *(void**)pSlot = *(void**)(*(char**)pSlot + 4);
}

// @ 0x008eba70
int IntRange_Equals(IntRange* a, IntRange* b)
{
    int nB = (int)((char*)b->mpEnd - (char*)b->mpBegin);
    int nA = (int)((char*)a->mpEnd - (char*)a->mpBegin);
    if (((nB ^ nA) & 0xfffffffc) != 0)
        return 1;
    int* p = a->mpBegin;
    int* pEnd = a->mpEnd;
    int* q = b->mpBegin;
    if (p != pEnd) {
        do {
            if (*p != *q)
                return 1;
            ++p;
            ++q;
        } while (p != pEnd);
    }
    return 0;
}

// @ 0x008ebb30
void EA::XHTML::Layout::TextStyleHashtable::DoRehash(unsigned int nNewBucketCount)
{
    void** pBucketsNew = (void**)Hashtable_GetNextBucketCount(nNewBucketCount);
    for (unsigned int i = 0; i < mnBucketCount; i++) {
        int nNode = (int)(uintptr_t)mpBuckets[i];
        while (nNode) {
            unsigned int h = ComputeStyleHash((void*)(nNode - 8));
            mpBuckets[i] = *(void**)(nNode + 0x278);
            *(void**)(nNode + 0x278) = pBucketsNew[h % nNewBucketCount];
            pBucketsNew[h % nNewBucketCount] = (void*)nNode;
            nNode = (int)(uintptr_t)mpBuckets[i];
        }
    }
    void** pOld = mpBuckets;
    if (mnBucketCount > 1 && pOld != (void**)mpPoolBegin2) {
        if ((void**)mpPoolBegin <= pOld && pOld < (void**)mpPoolEnd) {
            *pOld = mpFreeList;
            mpFreeList = pOld;
            mpBuckets = pBucketsNew;
            mnBucketCount = nNewBucketCount;
            return;
        }
        operator delete[](pOld);
    }
    mpBuckets = pBucketsNew;
    mnBucketCount = nNewBucketCount;
}

// @ 0x008ebc50
EA::XHTML::Layout::InlineItem::InlineItem(EA::XHTML::Layout::Page_s008e_b250* pPage, void* pElement, int type)
: EA::XHTML::Layout::ContainerItem(pPage, type)
{
    eastl::intrusive_list_node_s008e_b250* pAnchor = &mChildItems;
    pAnchor->mpPrev = pAnchor;
    pAnchor->mpNext = pAnchor;
    mStyleRules = 0;
    mnRuleCount = 0;
    mPlacement = 0;
    mFgColor = 0;
    mBgColor = 0;
    mpBorder = 0;
    mpBackground = 0;
    mpElement = pElement;
    *(void**)this = (void*)0x1437dc4;
}

// @ 0x008ebca0
EA::XHTML::Layout::TableCell::TableCell(EA::XHTML::Layout::Page_s008e_b250* pPage, void* pElement)
: EA::XHTML::Layout::Block(pPage, pElement, 7)
{
    mRowSpan = 1;
    mColSpan = 1;
    mRow = 0;
    mCol = 0;
    *(void**)this = (void*)0x1437e18;
    mMinWidth = 0.0f;
    mMaxWidth = 0.0f;
}

// @ 0x008ebd00
EA::XHTML::Layout::TableGroup::TableGroup(EA::XHTML::Layout::Page_s008e_b250* pPage, void* pElement, int type)
: EA::XHTML::Layout::ContainerItem(pPage, 9)
{
    eastl::intrusive_list_node_s008e_b250* pAnchor = &mChildItems;
    pAnchor->mpPrev = pAnchor;
    pAnchor->mpNext = pAnchor;
    mStyleRules = 0;
    mnRuleCount = 0;
    mPlacement = 0;
    mFgColor = 0;
    mBgColor = 0;
    mpBorder = 0;
    mpBackground = 0;
    mpElement = pElement;
    *(void**)this = (void*)0x1437e58;
    mpField5c = (void*)type;
}

// @ 0x008ebd50
void EA::XHTML::Layout::Page_s008e_b250::DestroyItem(EA::XHTML::Layout::ContainerItem* pItem)
{
    if (!pItem)
        return;
    if (pItem->mItemType <= 1)
        return;
    eastl::intrusive_list_node_s008e_b250* pNode = pItem->mChildItems.mpNext;
    eastl::intrusive_list_node_s008e_b250* pAnchor = &pItem->mChildItems;
    while (pNode != pAnchor) {
        eastl::intrusive_list_node_s008e_b250* pNext = pNode->mpNext;
        EA::XHTML::Layout::ContainerItem* pChild = (EA::XHTML::Layout::ContainerItem*)((char*)pNode - 8);
        EA::XHTML::Layout::Page_s008e_b250::DestroyItem(pChild);
        pNode = pNext;
    }
    (*(void (**)(EA::XHTML::Layout::ContainerItem*))(*(int*)pItem + 4))(pItem);
}

// @ 0x008ebde0
void EA::XHTML::Layout::Page_s008e_b250::CreateAttributeStyles(void* pElement, void* pOut)
{
    void* pListener = *(void**)((char*)*(void**)((char*)this + 0x24) + 0x44);
    char* pCur = (char*)pElement + 0x20;
    if (*(void**)pCur)
        pCur = *(char**)pCur - 4;
    else
        pCur = 0;
    for (;;) {
        char* pAnchor = (char*)pElement + 0x1c;
        if (pCur == pAnchor)
            return;
        unsigned int attr = *(unsigned int*)((char*)pElement + 0x28);
        unsigned int kind = StyleAttr_GetKind(pCur);
        switch (kind) {
        case 7:
            if (attr == 0x10 || attr == 0x11 || attr == 0x12 || attr == 9)
                CreateAttributeStyleFn(0x36, *(unsigned int*)(pCur + 0x1c), this, pOut, 1,
                                       pListener);
            break;
        case 8:
            if (attr == 0x10 || attr == 0x11 || attr == 0x12 || attr == 9)
                CreateAttributeStyleFn(0x37, *(unsigned int*)(pCur + 0x1c), this, pOut, 1,
                                       pListener);
            break;
        case 0x10:
            if (attr == 0xf)
                CreateAttributeStyleFn(4, *(unsigned int*)(pCur + 0x1c), this, pOut, 1, pListener);
            break;
        case 0x1d:
            if (attr == 0x10 || attr == 9)
                CreateAttributeStyleFn(0x2e, *(unsigned int*)(pCur + 0x1c), this, pOut, 1,
                                       pListener);
            break;
        case 0x1e:
            if (attr == 0x10 || attr == 0x11 || attr == 0x12)
                CreateAttributeStyleFn(0x48, *(unsigned int*)(pCur + 0x1c), this, pOut, 1,
                                       pListener);
            break;
        case 0x20:
            if (attr == 0x12)
                CreateAttributeStyleFn(0x12, *(unsigned int*)(pCur + 0x1c), this, pOut, 1,
                                       pListener);
            break;
        case 0x21:
            if (attr == 2 || attr == 0x10 || attr == 0x12)
                CreateAttributeStyleFn(10, *(unsigned int*)(pCur + 0x1c), this, pOut, 1, pListener);
            break;
        case 0x22:
            if (attr == 2 || attr == 0x10 || attr == 0x11 || attr == 0x12)
                CreateAttributeStyleFn(9, *(unsigned int*)(pCur + 0x1c), this, pOut, 1, pListener);
            break;
        case 0x23:
            if (attr == 2)
                CreateAttributeStyleFn(8, *(unsigned int*)(pCur + 0x1c), this, pOut, 1, pListener);
            break;
        case 0x27:
            if (attr == 0xe || attr == 0x10)
                CreateAttributeStyleFn(0x14, *(unsigned int*)(pCur + 0x1c), this, pOut, 1,
                                       pListener);
            break;
        case 0x28:
            if (attr == 0xf)
                CreateAttributeStyleFn(8, *(unsigned int*)(pCur + 0x1c), this, pOut, 1, pListener);
            break;
        case 0x29:
            if (attr == 0xf)
                CreateAttributeStyleFn(0, *(unsigned int*)(pCur + 0x1c), this, pOut, 1, pListener);
            break;
        default:
            break;
        }
        if (*(void**)(pCur + 4))
            pCur = *(char**)(pCur + 4) - 4;
        else
            pCur = 0;
    }
}

// @ 0x008ec0e0
void* EA::XHTML::Layout::TextStyleHashtable::AllocNode(const void* pStyle)
{
    void* pNode = mpFreeList;
    if (!pNode) {
        pNode = EAAllocate(mPoolStorage, "EASTL", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
                           "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    } else {
        mpFreeList = *(void**)pNode;
    }
    if (pNode)
        pNode = TextStyle_CopyCtor(pNode, pStyle);
    *(void**)((char*)pNode + 0x278) = 0;
    return pNode;
}

// @ 0x008ec130
void* EA::XHTML::Layout::TextStyleHashtable::FindNodeInBucket(void* pNode, const void* pStyle, unsigned int hash)
{
    for (;;) {
        if (!pNode)
            return 0;
        if (TextStyle_Equals(pStyle, pNode))
            break;
        pNode = *(void**)((char*)pNode + 0x278);
    }
    return pNode;
}

// @ 0x008ec170
EA::XHTML::Layout::TableRow::TableRow(EA::XHTML::Layout::Page_s008e_b250* pPage, void* pElement)
: EA::XHTML::Layout::ContainerItem(pPage, 8)
{
    mChildItems.mpNext = &mChildItems;
    mChildItems.mpPrev = &mChildItems;
    mStyleRules = 0;
    mnRuleCount = 0;
    mPlacement = 0;
    mFgColor = 0;
    mBgColor = 0;
    mpBorder = 0;
    mpBackground = 0;
    mpElement = pElement;
    *(void**)this = (void*)0x1437e8c;
    mpCellsBegin = 0;
    mpCellsEnd = 0;
    mpCellsCapacity = 0;
}

// @ 0x008ec200
void EA::XHTML::Layout::TextStyleHashtable::Find(void* pOut, const void* pStyle)
{
    unsigned int h = ComputeStyleHash(pStyle);
    unsigned int bucket = h % mnBucketCount;
    void* pNode = FindNodeInBucket(mpBuckets[bucket], pStyle, h);
    if (pNode) {
        *(void**)pOut = pNode;
        *(void**)((char*)pOut + 4) = &mpBuckets[bucket];
    } else {
        *(void**)pOut = mpBuckets[mnBucketCount];
        *(void**)((char*)pOut + 4) = &mpBuckets[mnBucketCount];
    }
}

// @ 0x008ec280
void EA::XHTML::Layout::TextStyleHashtable::DoInsertValue(void* pOut, const void* pStyle)
{
    unsigned int h = ComputeStyleHash(pStyle);
    unsigned int bucket = h % mnBucketCount;
    void* pNode = FindNodeInBucket(mpBuckets[bucket], pStyle, h);
    if (pNode) {
        *(void**)((char*)pOut + 4) = &mpBuckets[bucket];
        *(void**)pOut = pNode;
        *(char*)((char*)pOut + 8) = 0;
        return;
    }
    char local[8];
    Hashtable_GetRehashHint(local, mnBucketCount, mnSize, 1);
    void* pNew = AllocNode(pStyle);
    if (local[0]) {
        unsigned int nNew = *(unsigned int*)(local + 4);
        bucket = h % nNew;
        DoRehash(nNew);
    }
    *(void**)((char*)pNew + 0x278) = mpBuckets[bucket];
    mpBuckets[bucket] = pNew;
    mnSize += 1;
    *(void**)pOut = pNew;
    *(void**)((char*)pOut + 4) = &mpBuckets[bucket];
    *(char*)((char*)pOut + 8) = 1;
}

// @ 0x008ec6b0
EA::XHTML::Layout::TextStyleHashtable_s008e_c360::TextStyleHashtable_s008e_c360(const HashTag& h, const EqTag& e)
{
    EA::XHTML::Layout::FixedPool pool;
    pool.mpHead = 0;
    pool.init((char*)this + 0x138, 0x9f00, 0x27c, 4, 0);

    PoolDesc desc;
    desc.mpPoolBegin = (char*)this + 0x138;
    desc.mp04 = (char*)this + 0x138;
    desc.mp08 = (char*)this + 0xa038;
    desc.mp0c = 0;
    desc.mnNodeSize = 0x27c;
    desc.mpInlineBuckets = (char*)this + 0x34;

    void* pBuckets = EA::XHTML::Layout::Hashtable_PrimeRehash(0x40);
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

// @ 0x008ec8c0
void EA::XHTML::Layout::Page_s008e_c360::SetViewportSize(float w, float h)
{
    if (w != (float)mViewportW || h != (float)mViewportH) {
        mViewportW = (int)w;
        mViewportH = (int)h;
        if (mpRootItem)
            Layout();
    }
}
