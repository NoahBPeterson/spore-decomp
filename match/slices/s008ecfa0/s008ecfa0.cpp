// Slice s008ecfa0 (batch op3_big) — 0x008ecfa0, 3208 bytes.
//
// EA::XHTML::Layout::Page::CreateLayoutItems(DOM::Element*, const Style::StyleState&, bool)
//   (__thiscall, ret 0xc; the dev PDB's Page::CreateLayoutItems is 3872 bytes in Page.obj)
//
// Builds the layout item tree for one DOM element, recursively: computes the element's
// style (matching rules are copied into the page's StackAllocator), picks the item class
// from the CSS display type, creates border/background helpers, converts child elements
// (recursion) and text nodes (TextItems, with white-space collapsing and trailing
// white-space trimming of the previous text run), then fixes up tables (wraps runs of
// non-cells into anonymous cells and runs of cells into anonymous rows) and wraps runs of
// inline children of a block that also has block children into anonymous boxes.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (EA XHTML module, no /EHsc: StyleState has a
// destructor but the function has no EH frame).

#include "types.h"
#include <string.h>

// ---- EASTL (intrusive_list as in EASTL 3: node_type == T, so iterator steps static_cast) ----
namespace eastl {

struct intrusive_list_node {
    intrusive_list_node* mpNext;
    intrusive_list_node* mpPrev;
};

template <typename T>
struct intrusive_list_iterator {
    T* mpNode;
    intrusive_list_iterator() {}
    explicit intrusive_list_iterator(T* pNode) : mpNode(pNode) {}
    intrusive_list_iterator(const intrusive_list_iterator& x) : mpNode(x.mpNode) {}
    __forceinline T& operator*() const { return *mpNode; }
    __forceinline T* operator->() const { return mpNode; }
    __forceinline intrusive_list_iterator& operator++()
    {
        mpNode = static_cast<T*>(mpNode->mpNext);
        return *this;
    }
    __forceinline bool operator==(const intrusive_list_iterator& x) const { return mpNode == x.mpNode; }
    __forceinline bool operator!=(const intrusive_list_iterator& x) const { return mpNode != x.mpNode; }
};

class intrusive_list_base {
public:
    intrusive_list_node mAnchor;
    __forceinline intrusive_list_base() { mAnchor.mpNext = mAnchor.mpPrev = &mAnchor; }
};

template <typename T>
class intrusive_list : public intrusive_list_base {
public:
    typedef T node_type;
    typedef intrusive_list_iterator<T> iterator;

    __forceinline iterator begin() { return iterator(static_cast<T*>(mAnchor.mpNext)); }
    __forceinline iterator end() { return iterator(static_cast<T*>(&mAnchor)); }

    __forceinline void push_back(T& x)
    {
        x.mpPrev = mAnchor.mpPrev;
        x.mpNext = &mAnchor;
        mAnchor.mpPrev = &x;
        x.mpPrev->mpNext = &x;
    }

    __forceinline iterator insert(iterator pos, T& x)
    {
        node_type& next = *pos.mpNode;
        node_type& prev = *static_cast<node_type*>(next.mpPrev);
        prev.mpNext = next.mpPrev = &x;
        x.mpPrev = &prev;
        x.mpNext = &next;
        return iterator(&x);
    }

    __forceinline void splice(iterator pos, intrusive_list& /*x*/, iterator first, iterator last)
    {
        if (first != last) {
            node_type& insertPrev = *first.mpNode;
            node_type& insertNext = *static_cast<node_type*>(last.mpNode->mpPrev);

            insertNext.mpNext->mpPrev = insertPrev.mpPrev;
            insertPrev.mpPrev->mpNext = insertNext.mpNext;

            node_type& next = *pos.mpNode;
            node_type& prev = *static_cast<node_type*>(next.mpPrev);

            prev.mpNext = &insertPrev;
            insertPrev.mpPrev = &prev;
            insertNext.mpNext = &next;
            next.mpPrev = &insertNext;
        }
    }
};

// eastl::fixed_vector<T, N, true> (overflow to the default allocator: operator delete[]).
struct allocator {
    allocator() {}
    void deallocate(void* p) { delete[] (char*)p; }
};

template <typename T, int N>
class fixed_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mOverflowAllocator;
    T* mpPoolBegin;
    uint32_t mUnused;
    T mBuffer[N];

    fixed_vector()
    {
        mpBegin = mpEnd = mpPoolBegin = mBuffer;
        mpCapacity = mBuffer + N;
    }
    ~fixed_vector()
    {
        if (mpBegin) {
            if (mpBegin != mpPoolBegin)
                mOverflowAllocator.deallocate(mpBegin);
        }
    }
    __forceinline T* begin() { return mpBegin; }
    __forceinline T* end() { return mpEnd; }
    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    __forceinline T* erase(T* first, T* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
};

}  // namespace eastl

namespace EA {
namespace Allocator {

class StackAllocator {  // size 0x24 (PDB)
public:
    bool AllocateNewBlock(unsigned int nSize);  // 0x00928BA0

    __forceinline void* Malloc(unsigned int nSize)
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

__forceinline void* operator new(unsigned int nSize, EA::Allocator::StackAllocator& allocator) throw()
{
    return allocator.Malloc(nSize);
}
inline void operator delete(void*, EA::Allocator::StackAllocator&) throw() {}

namespace EA {
namespace XHTML {

namespace Layout { class Page; }

namespace DOM {

class Node : public eastl::intrusive_list_node {
public:
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual bool vf14();
    virtual bool vf18();
    uint32_t pad0c[(0x18 - 0x0c) / 4];

    int Type();                                        // 0x00FC7E50 (1 = element, 2 = text)
};

class Element : public Node {
public:
    eastl::intrusive_list<Node> mChildNodes;           // +0x18
    uint32_t pad20[2];
    int mTag;                                          // +0x28
};

class Text : public Node {
public:
    wchar_t* mpText;                                   // +0x18
    int mLength;                                       // +0x1c
};

}  // namespace DOM

namespace Style {

class Rule;

class StyleState {  // retail size 0x450
public:
    explicit StyleState(const StyleState& parent);    // 0x008FC130
    ~StyleState();                                     // 0x008E8650
    bool HasBorder() const;                            // 0x008FBA80
    bool HasBackground() const;                        // 0x008FBA70

    uint32_t pad000[0x37c / 4];
    int mFloat;                                        // +0x37c
    uint32_t pad380;
    int mPosition;                                     // +0x384
    uint32_t pad388[(0x3a8 - 0x388) / 4];
    int mDisplay;                                      // +0x3a8
    int mWhiteSpace;                                   // +0x3ac
    uint32_t pad3b0[(0x450 - 0x3b0) / 4];
};

}  // namespace Style

namespace Layout {

enum ItemType {
    Item_None = 0, Item_Text = 1, Item_Inline = 2, Item_Block = 3, Item_AnonymousBox = 4,
    Item_ListItem = 5, Item_Table = 6, Item_TableCell = 7, Item_TableRow = 8, Item_TableGroup = 9
};

class Background {
public:
    explicit Background(Page* pPage);                  // 0x008E6130
    uint32_t mData[0x48 / 4];
};

class Border {
public:
    uint32_t mData[0x34 / 4];
};

class Item : public eastl::intrusive_list_node {
public:
    Item(Page* pPage, ItemType type);                  // 0x008EAE40
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual int GetPlacement();                        // +0x1c

    Page* mpPage;                                      // +0x0c
    ItemType mItemType;                                // +0x10
    unsigned int mSelectableIndex;                     // +0x14
};

typedef eastl::intrusive_list<Item> ItemList;

class LineBreakItem : public Item {                    // 0x18 bytes
public:
    __forceinline explicit LineBreakItem(Page* pPage) : Item(pPage, Item_None) {}
};

class TextItem : public Item {                         // 0x24 bytes
public:
    TextItem(Page* pPage, const wchar_t* pText, int nLength);   // 0x008EB6F0
    wchar_t* mpCharData;                               // +0x18
    int mLength;                                       // +0x1c
    void* mpTextStyle;                                 // +0x20
};

class ContainerItem : public Item {
public:
    __forceinline ContainerItem(Page* pPage, ItemType type)
        : Item(pPage, type), mpElement(0), mStyleRules(0), mnRuleCount(0), mPlacement(0),
          mFgColor(0), mBgColor(0), mpBorder(0), mpBackground(0) {}

    ItemList mChildItems;                              // +0x18
    DOM::Element* mpElement;                           // +0x20
    Style::Rule** mStyleRules;                         // +0x24
    unsigned int mnRuleCount;                          // +0x28
    int mDisplay;                                      // +0x2c
    int mPosition;                                     // +0x30
    int mPlacement;                                    // +0x34
    unsigned int mFgColor;                             // +0x38
    unsigned int mBgColor;                             // +0x3c
    Border* mpBorder;                                  // +0x40
    Background* mpBackground;                          // +0x44
    uint32_t mParaStyle[(0x50 - 0x48) / 4];            // +0x48
};

class InlineItem : public ContainerItem {              // 0x5c bytes
public:
    InlineItem(Page* pPage, DOM::Element* pElement, ItemType type);   // 0x008EBC50
    uint32_t pad50[3];
};

class Block : public ContainerItem {                   // 0xc4 bytes
public:
    Block(Page* pPage, DOM::Element* pElement, ItemType type);        // 0x008E7F90
    uint32_t pad50[(0xc4 - 0x50) / 4];
};

class ListItem : public Block {                        // 0x100 bytes
public:
    ListItem(Page* pPage, DOM::Element* pElement);                    // 0x008EB250
    uint32_t padc4[(0x100 - 0xc4) / 4];
};

class Table : public Block {                           // 0x10c bytes
public:
    Table(Page* pPage, DOM::Element* pElement);                       // 0x008F1120
    uint32_t padc4[(0x10c - 0xc4) / 4];
};

class TableCell : public Block {                       // 0xf8 bytes
public:
    TableCell(Page* pPage, DOM::Element* pElement);                   // 0x008EBCA0
    __forceinline explicit TableCell(Page* pPage)
        : Block(pPage, 0, Item_TableCell), mRowSpan(1), mColSpan(1), mRow(0), mCol(0),
          mMinWidth(0.0f), mMaxWidth(0.0f) {}
    int mRowSpan;                                      // +0xc4
    int mColSpan;                                      // +0xc8
    int mRow;                                          // +0xcc
    int mCol;                                          // +0xd0
    float mMinWidth;                                   // +0xd4
    float mMaxWidth;                                   // +0xd8
    uint32_t paddc[(0xf8 - 0xdc) / 4];
};

class TableRow : public ContainerItem {                // 0x80 bytes
public:
    TableRow(Page* pPage, DOM::Element* pElement);                    // 0x008EC170
    __forceinline explicit TableRow(Page* pPage) : ContainerItem(pPage, Item_TableRow), mpCellsBegin(0), mpCellsEnd(0), mpCellsCapacity(0) {}
    uint32_t pad50[(0x5c - 0x50) / 4];
    void* mpCellsBegin;                                // +0x5c
    void* mpCellsEnd;                                  // +0x60
    void* mpCellsCapacity;                             // +0x64
    uint32_t pad68[(0x80 - 0x68) / 4];
};

class TableGroup : public ContainerItem {              // 0x60 bytes
public:
    TableGroup(Page* pPage, DOM::Element* pElement, int groupType);   // 0x008EBD00
    uint32_t pad50[4];
};

class AnonymousBox : public Item {                     // 0x40 bytes
public:
    __forceinline explicit AnonymousBox(Page* pPage) : Item(pPage, Item_AnonymousBox) {}
    ItemList mChildItems;                              // +0x18
    uint32_t pad20[(0x40 - 0x20) / 4];
};

void* operator_new(unsigned int nSize, Page* pPage);

class Page {
public:
    EA::Allocator::StackAllocator mAllocator;          // +0x00
    uint32_t pad24[(0x40 - 0x24) / 4];
    TextItem* mpLastWS;                                // +0x40
    uint32_t pad44[(0x268 - 0x44) / 4];
    unsigned int mCursorPos;                           // +0x268

    // Collects the stylesheet rules matching pElement (0x008EC970; pdb_names aligns the dev name
    // CreateLayoutItems here, but the dev CreateLayoutItems is 3872 bytes, like 0x008ECFA0).
    void CollectMatchingRules(DOM::Element* pElement, eastl::fixed_vector<Style::Rule*, 16>& rules);  // 0x008EC970
    ContainerItem* CreateLayoutItems(DOM::Element* pElement, const Style::StyleState& parentState, bool bCollapseWS);  // 0x008ECFA0

    void TrimLastWhiteSpace();
};

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA

// Out-of-line page allocation (0x008E2540): operator new(size_t, Page*).
void* operator new(unsigned int nSize, EA::XHTML::Layout::Page* pPage) throw();
inline void operator delete(void*, EA::XHTML::Layout::Page*) throw() {}

using namespace EA::XHTML;
using namespace EA::XHTML::Layout;

void ApplyStyles(DOM::Element* pElement, Style::Rule** pRules, int nRules, Style::StyleState& state);  // 0x008EAE80
bool IsSpace(wchar_t c);                                                                             // 0x008EB760

static __forceinline bool IsWhiteSpaceChar(wchar_t c)
{
    return c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\n' || c == 0x200b;
}

static __forceinline void SetAnonymous(ContainerItem* pItem)
{
    pItem->mPlacement = 2;
    pItem->mStyleRules = 0;
    pItem->mnRuleCount = 0;
    pItem->mDisplay = 0xe;
    pItem->mPosition = 0;
}

__forceinline void Page::TrimLastWhiteSpace()
{
    if (mpLastWS) {
        while (mpLastWS->mLength > 0) {
            if (!IsWhiteSpaceChar(mpLastWS->mpCharData[mpLastWS->mLength - 1]))
                break;
            mpLastWS->mLength--;
        }
        mpLastWS = 0;
    }
}

ContainerItem* Page::CreateLayoutItems(DOM::Element* pElement, const Style::StyleState& parentState, bool bCollapseWS)
{
    eastl::fixed_vector<Style::Rule*, 16> rules;
    Style::StyleState state(parentState);

    if (pElement->mTag == 0xb)
        return 0;

    rules.clear();
    CollectMatchingRules(pElement, rules);
    const int nRules = rules.size();
    Style::Rule** pRules = (Style::Rule**)mAllocator.Malloc((nRules * sizeof(Style::Rule*) + 7) & ~7);
    memcpy(pRules, rules.begin(), nRules * sizeof(Style::Rule*));
    ApplyStyles(pElement, pRules, nRules, state);

    if (pElement->mTag == 0xd) {
        if (state.mDisplay == 0)
            return 0;
        return (ContainerItem*)new (this) LineBreakItem(this);
    }

    int placement = 0;
    if (parentState.mDisplay == 1) {
        placement = 3;
        state.mDisplay = 2;
    } else if (state.mPosition == 2 || state.mPosition == 3) {
        placement = 5;
    } else if (state.mFloat != 0) {
        placement = 4;
    } else if (state.mDisplay == 3 || state.mDisplay == 7 || state.mDisplay == 4) {
        placement = 1;
    } else if (state.mDisplay != 0) {
        placement = 2;
    }

    const bool b14 = pElement->vf14();
    const bool b18 = pElement->vf18();

    ContainerItem* pItem;
    switch (state.mDisplay) {
    case 2:
    case 4:
    block:
        pItem = new (this) Block(this, pElement, Item_Block);
        break;
    case 3:
        if (placement != 1 || b14 || b18)
            goto block;
        pItem = new (this) InlineItem(this, pElement, Item_Inline);
        break;
    case 5:
        pItem = new (this) ListItem(this, pElement);
        break;
    case 6:
    case 7:
        pItem = new (this) Table(this, pElement);
        break;
    case 8:
        pItem = new (this) TableRow(this, pElement);
        break;
    case 9:
        pItem = new (this) TableGroup(this, pElement, 0);
        break;
    case 10:
        pItem = new (this) TableGroup(this, pElement, 1);
        break;
    case 11:
        pItem = new (this) TableGroup(this, pElement, 2);
        break;
    case 13:
        pItem = new (this) TableGroup(this, pElement, 3);
        break;
    case 14:
        pItem = new (this) TableCell(this, pElement);
        placement = 2;
        break;
    default:
        return 0;
    }

    if (pItem == 0)
        return 0;

    mCursorPos++;
    pItem->mStyleRules = pRules;
    pItem->mPlacement = placement;
    pItem->mnRuleCount = nRules;
    pItem->mDisplay = state.mDisplay;
    pItem->mPosition = state.mPosition;
    if (state.HasBorder())
        pItem->mpBorder = new (this) Border;
    if (state.HasBackground())
        pItem->mpBackground = new (this) Background(this);

    bool bCollapse = true;
    if (state.mWhiteSpace == 1 || state.mWhiteSpace == 2)
        bCollapse = false;
    if (bCollapseWS || state.mDisplay != 3)
        bCollapseWS = bCollapse;

    if (placement != 1)
        TrimLastWhiteSpace();

    for (eastl::intrusive_list<DOM::Node>::iterator itNode = pElement->mChildNodes.begin();
         itNode != pElement->mChildNodes.end(); ++itNode) {
        DOM::Node* pNode = itNode.mpNode;
        if (pNode->Type() == 1) {
            ContainerItem* pChild = CreateLayoutItems(static_cast<DOM::Element*>(pNode), state, bCollapseWS);
            bCollapseWS = bCollapse;
            if (pChild && pChild->mPlacement != 2)
                bCollapseWS = false;
            else
                TrimLastWhiteSpace();
            if (pChild)
                pItem->mChildItems.push_back(*pChild);
        } else if (pNode->Type() == 2) {
            DOM::Text* pTextNode = static_cast<DOM::Text*>(pNode);
            const wchar_t* pText = pTextNode->mpText;
            int nLength = pTextNode->mLength;
            if (bCollapseWS) {
                while (nLength > 0 && IsWhiteSpaceChar(*pText)) {
                    nLength--;
                    pText++;
                }
            }
            if (nLength > 0) {
                TextItem* pTextItem = new (this) TextItem(this, pText, nLength);
                mCursorPos += nLength;
                if (IsSpace(pText[nLength - 1])) {
                    bCollapseWS = bCollapse;
                    mpLastWS = pTextItem;
                } else {
                    mpLastWS = 0;
                    bCollapseWS = false;
                }
                if (pTextItem)
                    pItem->mChildItems.push_back(*pTextItem);
            }
        }
    }

    // Tables: wrap runs of non-cell children into anonymous cells ...
    if (state.mDisplay == 6 || state.mDisplay == 7 || state.mDisplay == 8) {
        ItemList::iterator it = pItem->mChildItems.begin();
        while (it != pItem->mChildItems.end()) {
            if (it->mItemType > Item_Table) {
                ++it;
                continue;
            }
            ItemList::iterator itEnd = it;
            while (itEnd != pItem->mChildItems.end() && itEnd->mItemType <= Item_Table)
                ++itEnd;
            TableCell* pCell = new (mAllocator) TableCell(this);
            SetAnonymous(pCell);
            pCell->mChildItems.splice(pCell->mChildItems.end(), pItem->mChildItems, it, itEnd);
            pItem->mChildItems.insert(itEnd, *pCell);
            it = itEnd;
        }
    }
    // ... and runs of cells into anonymous rows.
    if (state.mDisplay == 6 || state.mDisplay == 7) {
        ItemList::iterator it = pItem->mChildItems.begin();
        while (it != pItem->mChildItems.end()) {
            if (it->mItemType != Item_TableCell) {
                ++it;
                continue;
            }
            ItemList::iterator itEnd = it;
            while (itEnd != pItem->mChildItems.end() && itEnd->mItemType == Item_TableCell)
                ++itEnd;
            TableRow* pRow = new (mAllocator) TableRow(this);
            SetAnonymous(pRow);
            pRow->mChildItems.splice(pRow->mChildItems.end(), pItem->mChildItems, it, itEnd);
            pItem->mChildItems.insert(itEnd, *pRow);
            it = itEnd;
        }
    }

    // Blocks with both inline and block children: wrap inline runs into anonymous boxes.
    if (pItem->mPlacement != 1 && pItem->mPlacement != 0) {
        bool bHasInline = false;
        bool bHasBlock = false;
        ItemList::iterator it;
        for (it = pItem->mChildItems.begin(); it != pItem->mChildItems.end(); ++it) {
            if (it->GetPlacement() == 1)
                bHasInline = true;
            else if (it->GetPlacement() == 2)
                bHasBlock = true;
        }
        if (bHasInline && bHasBlock) {
            it = pItem->mChildItems.begin();
            while (it != pItem->mChildItems.end()) {
                if (it->GetPlacement() != 1) {
                    ++it;
                    continue;
                }
                ItemList::iterator itFirst = it;
                ItemList::iterator itRunEnd = it;
                while (it != pItem->mChildItems.end() && it->GetPlacement() != 2 && it->GetPlacement() != 5) {
                    if (it->GetPlacement() == 1) {
                        ++it;
                        itRunEnd = it;
                    } else {
                        ++it;
                    }
                }
                AnonymousBox* pBox = new (mAllocator) AnonymousBox(this);
                pBox->mChildItems.splice(pBox->mChildItems.end(), pItem->mChildItems, itFirst, itRunEnd);
                pItem->mChildItems.insert(itRunEnd, *pBox);
            }
        }
    }
    return pItem;
}
