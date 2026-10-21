// Slice s008eb250 (batch gold3) — 0x008eb250..0x008ec351.
//
// EA::XHTML::Layout list-item / page / eastl-hashtable functions.  The Layout classes
// (Item/ContainerItem/Block/ListItem/Page) are the same ones established by slice
// s008ecfa0 (0x008ecfa0 Page::CreateLayoutItems); repeated here so this TU stands alone.
//
// ListItem has a second polymorphic base (an EA image-requester object) at +0xc4: the ctor
// stores its vtable there and PlaceContent passes &this[0xc4] to the image-request helper.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (EA XHTML module, no /EHsc)

#include "types.h"
#include <string.h>

namespace eastl {

struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
    void Destroy();  // 0x00620230
};

}  // namespace eastl

namespace EA {
namespace Allocator {

class StackAllocator {
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
};

}  // namespace Allocator
}  // namespace EA

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
};

}  // namespace Style

namespace Text {

struct TextStyle { uint32_t mData[0x27c / 4]; };

class Typesetter {
public:
    uint32_t mData[0x240 / 4];
    void Reset(bool bReset);
    void SetWidth(float fLineWidth, float x, float y);
    int LayoutLine(const wchar_t* pText, unsigned int nLength, float fLineWidth, float fY,
                   const TextStyle* pStyle);
    void* GetLineLayout();
};

}  // namespace Text

namespace Layout {

class Page;
class Item;
class ContainerItem;
class Block;
class ListItem;
class Border;
class Background;
class TextStyleHashtable;

// Second polymorphic base of ListItem (image requester), occupies +0xc4.. in ListItem.
class ImageRequester {
public:
    virtual ~ImageRequester();
    virtual void vf04();
    virtual void OnImageRequest(void* pArg);
    void* mpVf1;            // +0x04
    unsigned int mnJobId;   // +0x08
};

class Item : public eastl::intrusive_list_node {
public:
    Item(Page* pPage, int itemType);  // 0x008EAE40
    virtual ~Item();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();

    Page* mpPage;                   // +0x0c
    int mItemType;                  // +0x10
    unsigned int mSelectableIndex;  // +0x14
};

class TextItem : public Item {
public:
    TextItem(Page* pPage, const wchar_t* pText, int nLength);  // 0x008EB6F0
    wchar_t* mpCharData;  // +0x18
    int mLength;          // +0x1c
    void* mpTextStyle;    // +0x20
};

class ContainerItem : public Item {
public:
    __forceinline ContainerItem(Page* pPage, int type) : Item(pPage, type) {}
    eastl::intrusive_list_node mChildItems;  // +0x18
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

class Block : public ContainerItem {
public:
    Block(Page* pPage, void* pElement, int type);  // 0x008E7F90
    uint32_t pad50[(0xc4 - 0x50) / 4];
};

class InlineItem : public ContainerItem {
public:
    InlineItem(Page* pPage, void* pElement, int type);  // 0x008EBC50
    uint32_t pad50[(0x5c - 0x50) / 4];
};

class ListItem : public Block, public ImageRequester {
public:
    ListItem(Page* pPage, void* pElement);  // 0x008EB250
    ~ListItem();                            // 0x008EB2E0

    void FormatMarkerText(unsigned int index);                            // 0x008EB350
    void PlaceContent(void* pLayoutContext, const Style::StyleState& s);  // 0x008EB520

    int mListStyleType;              // +0xd0
    const wchar_t* mMarkerImageURI;  // +0xd4
    wchar_t* mMarkerTextBegin;       // +0xd8
    wchar_t* mMarkerTextEnd;         // +0xdc
    wchar_t* mMarkerTextCapacity;    // +0xe0
    uint32_t pade4[(0xec - 0xe4) / 4];
    float mMarkerWidth;  // +0xec
    uint32_t padf0[2];
    void* mpTextStyle;    // +0xf8
    int mImageTableIndex;  // +0xfc
};

class TableCell : public Block {
public:
    TableCell(Page* pPage, void* pElement);  // 0x008EBCA0
    int mRowSpan;      // +0xc4
    int mColSpan;      // +0xc8
    int mRow;          // +0xcc
    int mCol;          // +0xd0
    float mMinWidth;   // +0xd4
    float mMaxWidth;   // +0xd8
};

class TableRow : public ContainerItem {
public:
    TableRow(Page* pPage, void* pElement);  // 0x008EC170
    uint32_t pad50[(0x5c - 0x50) / 4];
    void* mpCellsBegin;     // +0x5c
    void* mpCellsEnd;       // +0x60
    void* mpCellsCapacity;  // +0x64
};

class TableGroup : public ContainerItem {
public:
    TableGroup(Page* pPage, void* pElement, int type);  // 0x008EBD00
    uint32_t pad50[3];
    void* mpField5c;  // +0x5c
};

class RefItem {
public:
    virtual void vf0();
    virtual void Release(int flag);
};

class Page {
public:
    EA::Allocator::StackAllocator mAllocator;  // +0x00
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

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA

// ---------------------------------------------------------------------------
// External helpers (EA XHTML / EASTL / EAText)
// ---------------------------------------------------------------------------
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
};

WString* WStr_Assign(WString* pStr, const wchar_t* pSrc);                      // 0x005C3D90
void WStr_PushBack(WString* pStr, wchar_t c);                                  // 0x004F6510
void WStr_Append(WString* pStr, const wchar_t* pFirst, const wchar_t* pLast);  // 0x00429580
void WStr_Format(WString* pStr, const wchar_t* pFmt, ...);                     // 0x0041E050

int StyleState_GetCounter(const EA::XHTML::Style::StyleState* pState, const wchar_t* pName);  // 0x008FBDA0

void CreateAttributeStyleFn(unsigned int a, unsigned int b, void* pPage, const void* pState,
                            int flag, void* pListener);
unsigned int StyleAttr_GetKind(void* pAttr);

void ImageRequest_Request(void* pRequester, const wchar_t* pURI);              // 0x008EC5E0
void PlaceBlock(const EA::XHTML::Style::StyleState& s, void* pLayoutContext);  // 0x008EAAF0
void RenderingContext_Ctor(void* pCtx, void* pTS, const float* pRect, const void* pState);  // 0x008EE810
void Typesetter_Dtor(void* pCtx);          // 0x0089C540
void* Page_GetSelectionInterface(void* pPage);  // 0x008E2810
unsigned int ComputeStyleHash(const void* pStyle);  // 0x00894440
bool TextStyle_Equals(const void* a, const void* b);  // 0x008942A0
void* TextStyle_CopyCtor(void* pDst, const void* pSrc);  // 0x008945A0
void IntrusiveList_Dtor(void* pList);      // 0x00620230 (eastl::intrusive_list_node::Destroy)
void* EAAllocate(unsigned int nSize, const char* pName, int a, int b, const char* pFile, int line);

extern const wchar_t kStr_None[];        // 0x01437CE8
extern const wchar_t kStr_Disc[];        // 0x01437CE4
extern const wchar_t kStr_Circle[];      // 0x01437CE0
extern const wchar_t kStr_Square[];      // 0x01437CDC
extern const wchar_t kStr_DecimalFmt[];  // 0x01437CD8
extern const wchar_t kStr_list[];        // 0x013F58AC  L"list"

extern const unsigned short kRomanSizes[];     // 0x0154CF5C
extern const wchar_t* const kRomanUpperStr[];  // 0x0154CFC4
extern const wchar_t* const kRomanLowerStr[];  // 0x0154CF90

using namespace EA::XHTML;
using namespace EA::XHTML::Layout;
using EA::XHTML::Style::StyleState;

// ===========================================================================
// 0x008EB250  EA::XHTML::Layout::ListItem::ListItem
// ===========================================================================
// @ 0x008eb250
ListItem::ListItem(Page* pPage, void* pElement) : Block(pPage, pElement, 5)
{
    ImageRequester::mnJobId = 0;
    ImageRequester::mpVf1 = 0;
    mListStyleType = 0;
    mMarkerImageURI = 0;
    mMarkerTextBegin = (wchar_t*)kStr_None;
    mMarkerTextEnd = (wchar_t*)kStr_None;
    mMarkerTextCapacity = (wchar_t*)((char*)kStr_None + 2);
    mpTextStyle = 0;
    mImageTableIndex = -1;
}

// ===========================================================================
// 0x008EB2E0  EA::XHTML::Layout::ListItem::~ListItem
// ===========================================================================
// @ 0x008eb2e0
ListItem::~ListItem()
{
    if (mMarkerTextBegin) {
        unsigned int nBytes = (unsigned int)((char*)mMarkerTextCapacity - (char*)mMarkerTextBegin);
        if ((nBytes & 0xfffffffe) > 2)
            operator delete[]((char*)mMarkerTextBegin);
    }
    mMarkerImageURI = kStr_None;
    mMarkerTextBegin = (wchar_t*)kStr_None;
}

// ===========================================================================
// 0x008EB350  EA::XHTML::Layout::ListItem::FormatMarkerText
// ===========================================================================
// @ 0x008eb350
void ListItem::FormatMarkerText(unsigned int index)
{
    WString* pStr = (WString*)((char*)this + 0xd8);
    switch (mListStyleType) {
    case 0:
    case 1:
        WStr_Assign(pStr, kStr_None);
        return;
    case 2:
        WStr_Assign(pStr, kStr_Disc);
        return;
    case 3:
        WStr_Assign(pStr, kStr_Circle);
        return;
    case 4:
        WStr_Format(pStr, kStr_DecimalFmt, index);
        return;
    case 5:
    case 6:
    {
        const wchar_t* const* pTable = (mListStyleType != 6) ? kRomanLowerStr : kRomanUpperStr;
        wchar_t* pBegin = mMarkerTextBegin;
        if (pBegin != mMarkerTextEnd) {
            *pBegin = 0;
            mMarkerTextEnd = pBegin;
        }
        const unsigned short* pSizes = kRomanSizes;
        for (int i = 0; i < 13; i++) {
            while (index >= (unsigned int)pSizes[i]) {
                const wchar_t* pCur = *pTable;
                const wchar_t* pCurEnd = pCur;
                while (*pCurEnd)
                    pCurEnd++;
                WStr_Append(pStr, pCur, pCurEnd);
                index -= pSizes[i];
            }
            pTable++;
        }
        WStr_PushBack(pStr, L'.');
        return;
    }
    case 7:
    {
        wchar_t* pBegin = mMarkerTextBegin;
        if (pBegin != mMarkerTextEnd) {
            *pBegin = 0;
            mMarkerTextEnd = pBegin;
        }
        if (index - 1 < 0x1a) {
            WStr_PushBack(pStr, (wchar_t)(index + 0x60));
            WStr_PushBack(pStr, L'.');
            return;
        }
        WStr_PushBack(pStr, L'?');
        WStr_PushBack(pStr, L'.');
        return;
    }
    case 8:
    {
        wchar_t* pBegin = mMarkerTextBegin;
        if (pBegin != mMarkerTextEnd) {
            *pBegin = 0;
            mMarkerTextEnd = pBegin;
        }
        if (index - 1 < 0x1a) {
            WStr_PushBack(pStr, (wchar_t)(index + 0x40));
            WStr_PushBack(pStr, L'.');
            return;
        }
        WStr_PushBack(pStr, L'?');
        WStr_PushBack(pStr, L'.');
        return;
    }
    default:
        return;
    }
}

// ===========================================================================
// 0x008EB520  EA::XHTML::Layout::ListItem::PlaceContent
// ===========================================================================
// @ 0x008eb520
void ListItem::PlaceContent(void* pLayoutContext, const Style::StyleState& s)
{
    int counter = StyleState_GetCounter(&s, kStr_list);

    mListStyleType = s.mListStyleType;
    mMarkerImageURI = s.mListStyleImage;

    if (mMarkerImageURI) {
        bool bUseImage = false;
        if (mImageTableIndex != -1) {
            void* pRes = mpPage->GetResource(mImageTableIndex);
            if (pRes)
                bUseImage = (*(int (**)(void*, int))(*(int*)pRes + 0xc))(pRes, 0xee3f516e) != 0;
        }
        if (!bUseImage) {
            if (!ImageRequester::mnJobId)
                ImageRequest_Request((char*)this + 0xc4, mMarkerImageURI);
        }

        if (mImageTableIndex != -1) {
            void* pRes = mpPage->GetResource(mImageTableIndex);
            if (pRes) {
                void* pImg = (void*)(*(int (**)(void*, int))(*(int*)pRes + 0xc))(pRes, 0xee3f516e);
                if (pImg) {
                    mMarkerWidth = 16.0f;
                    int val = (*(int (**)(void*, int))(*(int*)pImg + 0xc))(pImg, 0x2f84737);
                    if (val)
                        mMarkerWidth = (float)*(int*)(val + 4);
                }
            }
        }
        PlaceBlock(s, (char*)pLayoutContext);
        return;
    }

    if (mListStyleType) {
        mpTextStyle = mpPage->GetTextStyle(s);
        FormatMarkerText((unsigned int)counter);

        char* pBase = (char*)pLayoutContext;
        Text::Typesetter* pTS = (Text::Typesetter*)(pBase + 4);
        pTS->Reset(true);
        pTS->SetWidth(*(float*)(pBase + 0x558) - *(float*)(pBase + 0x554), *(float*)(pBase + 0x554),
                      *(float*)(pBase + 0x538));
        pTS->LayoutLine(mMarkerTextBegin, (int)(mMarkerTextEnd - mMarkerTextBegin), 0.0f, 0.0f,
                        (const Text::TextStyle*)mpTextStyle);
        unsigned char* pLine = (unsigned char*)pTS->GetLineLayout();
        mMarkerWidth = *(float*)(pLine + 0x98);
        pTS->Reset(true);
    }
    PlaceBlock(s, (char*)pLayoutContext);
}

// ===========================================================================
// 0x008EB6F0  EA::XHTML::Layout::TextItem::TextItem
// ===========================================================================
// @ 0x008eb6f0
TextItem::TextItem(Page* pPage, const wchar_t* pText, int nLength) : Item(pPage, 1)
{
    mpCharData = (wchar_t*)pText;
    mLength = nLength;
    mpTextStyle = 0;
}

// ===========================================================================
// 0x008EB720  EA::XHTML::Layout::... size accumulator ctor
// ===========================================================================
// @ 0x008eb720
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

// ===========================================================================
// 0x008EB760  IsSpace(wchar_t)
// ===========================================================================
// @ 0x008eb760
bool IsSpace(wchar_t c)
{
    unsigned short u = (unsigned short)c;
    return u == 0x20 || u == 9 || u == 0x0c || u == 0x0d || u == 0x0a || u == 0x200b;
}

// ===========================================================================
// 0x008EB7A0  Page::NotifyImagesAbandoned
// ===========================================================================
// @ 0x008eb7a0
void Page::NotifyImagesAbandoned()
{
    if (mpImageRequester) {
        void* p = mpResources;
        while (p) {
            void* pArg = *(void**)((char*)p + 8);
            ((ImageRequester*)mpImageRequester)->OnImageRequest(pArg);
            p = mpResources;
        }
    }
}

// ===========================================================================
// 0x008EB7E0  Page::SetImageRequester
// ===========================================================================
// @ 0x008eb7e0
void Page::SetImageRequester(void* pNew, int flag)
{
    if (mpFocusItem) {
        *(int*)((char*)mpFocusItem + 0xc) = 1;
    }
    mpFocusItem = pNew;
    if (pNew) {
        *(int*)((char*)pNew + 0xc) = flag;
    }
}

// ===========================================================================
// 0x008EB870  EA::XHTML::Layout::Page::Render
// ===========================================================================
// @ 0x008eb870
void Page::Render(Text::Typesetter* pTS, const float* pRect, const void* pState)
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

// ===========================================================================
// 0x008EB910  Page::SetChildItem
// ===========================================================================
// @ 0x008eb910
void Page::SetChildItem(unsigned int index, void* pItem)
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
        ((RefItem*)pItem)->vf0();
    *pSlot = pItem;
    if (pOld)
        ((RefItem*)pOld)->Release(1);
}

// ===========================================================================
// 0x008EB980  Page::ImageRequestCallback
// ===========================================================================
// @ 0x008eb980
void Page::ImageRequestCallback(int* pMsg)
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

// ===========================================================================
// 0x008EBA20  Page::SetSelectionRange
// ===========================================================================
// @ 0x008eba20
namespace {
inline const unsigned int& RefMin(const unsigned int& x, const unsigned int& y)
{
    return y < x ? y : x;
}
inline const unsigned int& RefMax(const unsigned int& x, const unsigned int& y)
{
    return x < y ? y : x;
}
}  // namespace

void Page::SetSelectionRange(unsigned int a, unsigned int b)
{
    mSelStart = a;
    mSelEnd = b;
    mSelMin = RefMin(a, b);
    mSelMax = RefMax(a, b);
}

// ===========================================================================
// 0x008EBA70  IntRange equal
// ===========================================================================
// @ 0x008eba70
struct IntRange {
    int* mpBegin;
    int* mpEnd;
};

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

// ===========================================================================
// 0x008EBC50  EA::XHTML::Layout::InlineItem::InlineItem
// ===========================================================================
// @ 0x008ebc50
InlineItem::InlineItem(Page* pPage, void* pElement, int type) : ContainerItem(pPage, type)
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
    *(void**)this = (void*)0x1437dc4;
}

// ===========================================================================
// 0x008EBCA0  EA::XHTML::Layout::TableCell::TableCell
// ===========================================================================
// @ 0x008ebca0
TableCell::TableCell(Page* pPage, void* pElement) : Block(pPage, pElement, 7)
{
    mRowSpan = 1;
    mColSpan = 1;
    mRow = 0;
    mCol = 0;
    *(void**)this = (void*)0x1437e18;
    mMinWidth = 0.0f;
    mMaxWidth = 0.0f;
}

// ===========================================================================
// 0x008EBD00  EA::XHTML::Layout::TableGroup::TableGroup
// ===========================================================================
// @ 0x008ebd00
TableGroup::TableGroup(Page* pPage, void* pElement, int type) : ContainerItem(pPage, 9)
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
    *(void**)this = (void*)0x1437e58;
    mpField5c = (void*)type;
}

// ===========================================================================
// 0x008EC170  EA::XHTML::Layout::TableRow::TableRow
// ===========================================================================
// @ 0x008ec170
TableRow::TableRow(Page* pPage, void* pElement) : ContainerItem(pPage, 8)
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

// ===========================================================================
// 0x008EBD50  recursive item-list-tree destructor
// ===========================================================================
// @ 0x008ebd50
void Page::DestroyItem(ContainerItem* pItem)
{
    if (!pItem)
        return;
    if (pItem->mItemType <= 1)
        return;
    eastl::intrusive_list_node* pNode = pItem->mChildItems.mpNext;
    eastl::intrusive_list_node* pAnchor = &pItem->mChildItems;
    while (pNode != pAnchor) {
        eastl::intrusive_list_node* pNext = pNode->mpNext;
        ContainerItem* pChild = (ContainerItem*)((char*)pNode - 8);
        Page::DestroyItem(pChild);
        pNode = pNext;
    }
    (*(void (**)(ContainerItem*))(*(int*)pItem + 4))(pItem);
}

// ===========================================================================
// 0x008EBDE0  EA::XHTML::Layout::Page::CreateAttributeStyles
// ===========================================================================
// @ 0x008ebde0
void Page::CreateAttributeStyles(void* pElement, void* pOut)
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

// ===========================================================================
// eastl::hashtable<EA::Text::TextStyle, ...> — the fixed-hashtable instance used by
// Layout for its attribute-style table (node size 0x27c: 0x278 of TextStyle + next link).
// ===========================================================================
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
};

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA

using EA::XHTML::Layout::TextStyleHashtable;

// 0x008EBAC0 — prime-rehash-policy bucket count for a requested size.
int Hashtable_GetNextBucketCount(unsigned int nSize)
{
    return (int)nSize;
}

// @ 0x008ebb30
void TextStyleHashtable::DoRehash(unsigned int nNewBucketCount)
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

// @ 0x008ec0e0
void* TextStyleHashtable::AllocNode(const void* pStyle)
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
void* TextStyleHashtable::FindNodeInBucket(void* pNode, const void* pStyle, unsigned int hash)
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

// @ 0x008ec1c0
void* TextStyleHashtable::Destroy(unsigned char flags)
{
    if (mpSecondary && *(int*)((char*)mpSecondary - 4) != 0)
        operator delete[]((char*)mpSecondary);
    IntrusiveList_Dtor((char*)this + 0x18);
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x008ec200
void TextStyleHashtable::Find(void* pOut, const void* pStyle)
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

// 0x00921440 — prime_rehash_policy: decides whether a rehash is needed.
void Hashtable_GetRehashHint(void* pOut, unsigned int nBucketCount, unsigned int nSize, int a);

// @ 0x008ec280
void TextStyleHashtable::DoInsertValue(void* pOut, const void* pStyle)
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
