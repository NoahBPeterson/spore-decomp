// slice s008997f0 (gold8 batch) - EASTL text-layout container helpers.
//
//   0x008997f0  basic_string<wchar_t, EASTLCoreAllocator>::set_capacity
//   0x00899900  vector<AnalysisInfo, EASTLCoreAllocator>::DoInsertValues
//   0x00899c90  ResizableVec<GlyphLayoutInfo>::insert(position, count, value)
//   0x0089a370  ResizableVec<GlyphLayoutInfo>::insert(position, first, last)
//   0x0089a5d0  vector<Typesetter::Item, EASTLCoreAllocator>::push_back()
//   0x0089a660  cvec<unsigned>::DoAllocateAndCopy
//   0x0089a6b0  red-black tree node clone helper
//   0x0089a790  cvec<unsigned short>::DoAllocateAndCopy
//
// The binary's EASTL predates the vendored 1.11 drop: set_capacity still uses the
// "allocate 2*n, copy, swap with a copy of *this" shrink, and the vector insert
// helpers still go through uninitialized_copy / uninitialized_fill_n instead of
// the later _ptr variants.
//
// Compile with /O2 /MT /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc.
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// ICoreAllocator: the first four vtable slots (Alloc at +0x08, Free at +0x0c).
// ---------------------------------------------------------------------------
struct ICoreAllocator {
    virtual void  Slot0();
    virtual void  Slot4();
    virtual void* Alloc(unsigned int size, unsigned int alignment, unsigned int flags);
    virtual void  Free(void* p, unsigned int size);
};

// ---------------------------------------------------------------------------
// 0x0089a660 / 0x0089a790: cvec<T>::DoAllocateAndCopy(count, first, last)
// ---------------------------------------------------------------------------
struct CvecU32 {
    unsigned int*  mpBegin;      // +0x00
    unsigned int*  mpEnd;        // +0x04
    unsigned int*  mpCapacity;   // +0x08
    ICoreAllocator* mpAllocator; // +0x0c
    unsigned int   mFlags;       // +0x10

    unsigned int* DoAllocateAndCopy(unsigned int count, const unsigned int* first, const unsigned int* last);
};

// @ 0x0089a660
unsigned int* CvecU32::DoAllocateAndCopy(unsigned int count, const unsigned int* first, const unsigned int* last)
{
    unsigned int* p = count ? (unsigned int*)mpAllocator->Alloc(count * sizeof(unsigned int), 0, mFlags) : 0;
    memcpy(p, first, (const char*)last - (const char*)first);
    return p;
}

struct CvecU16 {
    unsigned short* mpBegin;      // +0x00
    unsigned short* mpEnd;        // +0x04
    unsigned short* mpCapacity;   // +0x08
    ICoreAllocator* mpAllocator;  // +0x0c
    unsigned int    mFlags;       // +0x10

    unsigned short* DoAllocateAndCopy(unsigned int count, const unsigned short* first, const unsigned short* last);
};

// @ 0x0089a790
unsigned short* CvecU16::DoAllocateAndCopy(unsigned int count, const unsigned short* first, const unsigned short* last)
{
    unsigned short* p = count ? (unsigned short*)mpAllocator->Alloc(count * sizeof(unsigned short), 0, mFlags) : 0;
    memcpy(p, first, (const char*)last - (const char*)first);
    return p;
}

// ---------------------------------------------------------------------------
// 0x0089a5d0: vector<Typesetter::Item>::push_back() (the returned reference is
// discarded by the caller, so the copy in the binary is void).
// ---------------------------------------------------------------------------
struct TypesetterItem {
    unsigned char mData[0x2c];
};

struct VecItem {
    TypesetterItem* mpBegin;      // +0x00
    TypesetterItem* mpEnd;        // +0x04
    TypesetterItem* mpCapacity;   // +0x08
    ICoreAllocator* mpAllocator;  // +0x0c
    unsigned int    mFlags;       // +0x10

    void DoInsertValue(TypesetterItem* position, const TypesetterItem& value);  // 0x00899590
    void PushBackDefault();
};

// @ 0x0089a5d0
void VecItem::PushBackDefault()
{
    TypesetterItem* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 1;
        if (end)
            memset(end, 0, sizeof(TypesetterItem));
    } else {
        TypesetterItem temp;
        memset(&temp, 0, sizeof(temp));
        DoInsertValue(end, temp);
    }
}

// ---------------------------------------------------------------------------
// 0x0089a6b0: recursive clone of a red-black-tree node chain.
//
// The node's value is a ref-counted pointer constructed in place; MSVC keeps
// the placement-new null check on `&node->mValue`, which is what distinguishes
// the retail inlined allocation block (0x0089a701) from a plain store.
// ---------------------------------------------------------------------------
struct RefCounted {
    virtual void Slot0();     // +0x00
    virtual void Slot4();     // +0x04
    virtual void AddRef();    // +0x08
};

struct RBValue {
    RefCounted* mpPtr;        // +0x00

    RBValue(const RBValue& x) : mpPtr(x.mpPtr)
    {
        if (mpPtr)
            mpPtr->AddRef();
    }
};

inline void* operator new(unsigned int, void* p) { return p; }

struct RBNode {
    RBNode*       mpRight;   // +0x00  free-list next / right child
    RBNode*       mpLeft;    // +0x04  left child
    RBNode*       mpParent;  // +0x08
    unsigned char mColor;    // +0x0c
    unsigned char mPad[3];   // +0x0d
    RBValue       mValue;    // +0x10
};

void* EAOperatorNew(unsigned int size, const char* name, int flags, int alignment, const char* file, int line);  // 0x00f473a0

struct RBTree {
    unsigned char mPad0[0x18];   // +0x00
    RBNode*       mpFreeList;    // +0x18
    unsigned char mPad1[0x0c];   // +0x1c
    unsigned int  mNodeSize;     // +0x28

    __declspec(noinline) RBNode* DoCreateNode(const RBValue* pValue);   // 0x0088c690
    RBNode* DoCreateNodeInline(const RBValue* pValue);
    RBNode* DoCopySubtree(RBNode* pNodeSource, RBNode* pNodeDest);
};

RBNode* RBTree::DoCreateNode(const RBValue* pValue)
{
    RBNode* node = mpFreeList;
    if (node)
        mpFreeList = node->mpRight;
    else
        node = (RBNode*)EAOperatorNew(mNodeSize, "EASTL", 0, 0, "allocator", 0xd1);
    new (&node->mValue) RBValue(*pValue);
    return node;
}

inline RBNode* RBTree::DoCreateNodeInline(const RBValue* pValue)
{
    RBNode* node = mpFreeList;
    if (node)
        mpFreeList = node->mpRight;
    else {
        unsigned int size = mNodeSize;
        node = (RBNode*)EAOperatorNew(size, "EASTL", 0, 0, "allocator", 0xd1);
    }
    new (&node->mValue) RBValue(*pValue);
    return node;
}

// @ 0x0089a6b0
RBNode* RBTree::DoCopySubtree(RBNode* pNodeSource, RBNode* pNodeDest)
{
    RBNode* pNewNodeRoot = DoCreateNode(&pNodeSource->mValue);
    pNewNodeRoot->mpRight  = 0;
    pNewNodeRoot->mpLeft   = 0;
    pNewNodeRoot->mpParent = pNodeDest;
    pNewNodeRoot->mColor   = pNodeSource->mColor;

    if (pNodeSource->mpRight)
        pNewNodeRoot->mpRight = DoCopySubtree(pNodeSource->mpRight, pNewNodeRoot);

    RBNode* pNewNodeLeft;

    for (pNodeSource = pNodeSource->mpLeft, pNodeDest = pNewNodeRoot;
         pNodeSource;
         pNodeSource = pNodeSource->mpLeft, pNodeDest = pNewNodeLeft)
    {
        pNewNodeLeft = DoCreateNodeInline(&pNodeSource->mValue);
        pNewNodeLeft->mpRight  = 0;
        pNewNodeLeft->mpLeft   = 0;
        pNewNodeLeft->mpParent = pNodeDest;
        pNewNodeLeft->mColor   = pNodeSource->mColor;

        pNodeDest->mpLeft = pNewNodeLeft;

        if (pNodeSource->mpRight)
            pNewNodeLeft->mpRight = DoCopySubtree(pNodeSource->mpRight, pNewNodeLeft);
    }

    return pNewNodeRoot;
}

// ---------------------------------------------------------------------------
// Raw-storage helpers shared by the three insert algorithms below.  Each
// `uninitialized_copy` returns an iterator by value (hidden sret pointer) and
// takes the empty false_type tag as a trailing stack slot, which is why the
// retail call sites push five dwords for a four-argument helper.
// ---------------------------------------------------------------------------
struct AnalysisInfo {
    unsigned int mData[3];       // 12 bytes
};

struct GlyphLayoutInfo {
    unsigned int mData[8];       // 32 bytes
};

struct Iter12 {
    AnalysisInfo* mpCurrent;
    Iter12() : mpCurrent(0) {}
};

struct Iter32 {
    GlyphLayoutInfo* mpCurrent;
    Iter32() : mpCurrent(0) {}
};

Iter12 AIUninitCopy12(const AnalysisInfo* first, const AnalysisInfo* last, AnalysisInfo* dest, const void* tag);  // 0x00898b80
void   AIFillN12(AnalysisInfo* dest, unsigned int n, const AnalysisInfo* value);                                  // 0x006e5760
void   AIFill12(AnalysisInfo* first, AnalysisInfo* last, const AnalysisInfo* value);                              // 0x00a177f0
void   AICopyBackward12(AnalysisInfo* first, AnalysisInfo* last, AnalysisInfo* dest);                             // 0x00abced0
AnalysisInfo* AICopyRaw12(const AnalysisInfo* first, const AnalysisInfo* last, AnalysisInfo* dest);               // 0x00a11310

Iter32 AIUninitCopy32(const GlyphLayoutInfo* first, const GlyphLayoutInfo* last, GlyphLayoutInfo* dest, const void* tag);  // 0x00c04920
void   AIFillN32(GlyphLayoutInfo* dest, unsigned int n, const GlyphLayoutInfo* value);                                      // 0x00898550
void   AIFill32(GlyphLayoutInfo* first, GlyphLayoutInfo* last, const GlyphLayoutInfo* value);                              // 0x00898520
void   AICopyBackward32(const GlyphLayoutInfo* first, const GlyphLayoutInfo* last, GlyphLayoutInfo* dest);                 // 0x00898f90
void   AICopy32(const GlyphLayoutInfo* first, const GlyphLayoutInfo* last, GlyphLayoutInfo* dest);                         // 0x00c06600
GlyphLayoutInfo* AICopyRaw32(const GlyphLayoutInfo* first, const GlyphLayoutInfo* last, GlyphLayoutInfo* dest);            // 0x00c033a0

// ---------------------------------------------------------------------------
// 0x00899900: vector<AnalysisInfo>::DoInsertValues(position, n, value)
// ---------------------------------------------------------------------------
struct VecAnalysis {
    AnalysisInfo*   mpBegin;      // +0x00
    AnalysisInfo*   mpEnd;        // +0x04
    AnalysisInfo*   mpCapacity;   // +0x08
    ICoreAllocator* mpAllocator;  // +0x0c
    unsigned int    mFlags;       // +0x10

    void DoInsertValues(AnalysisInfo* position, unsigned int n, const AnalysisInfo& value);
};

// @ 0x00899900
void VecAnalysis::DoInsertValues(AnalysisInfo* position, unsigned int n, const AnalysisInfo& value)
{
    if (n <= (unsigned int)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const AnalysisInfo temp = value;
            unsigned int nExtra = (unsigned int)(mpEnd - position);
            AnalysisInfo* const pEnd = mpEnd;

            if (n < nExtra) {
                AIUninitCopy12(mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                AICopyBackward12(position, pEnd - n, pEnd);
                AIFill12(position, position + n, &temp);
            } else {
                AIFillN12(mpEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                AIUninitCopy12(position, pEnd, mpEnd, position);
                mpEnd += nExtra;
                AIFill12(position, pEnd, &temp);
            }
        }
    } else {
        unsigned int nPrev = (unsigned int)(mpEnd - mpBegin);
        unsigned int cap2 = nPrev * 2;
        if (nPrev == 0)
            cap2 = 1;
        unsigned int want = nPrev + n;
        if (cap2 > want)
            want = cap2;

        AnalysisInfo* pNewData = want ? (AnalysisInfo*)mpAllocator->Alloc(want * sizeof(AnalysisInfo), 0, mFlags) : 0;
        AnalysisInfo* pNewEnd = AICopyRaw12(mpBegin, position, pNewData);
        AIFillN12(pNewEnd, n, &value);
        pNewEnd = AICopyRaw12(position, mpEnd, pNewEnd + n);
        if (mpBegin)
            mpAllocator->Free(mpBegin, (unsigned int)(mpCapacity - mpBegin) * sizeof(AnalysisInfo));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + want;
    }
}

// ---------------------------------------------------------------------------
// 0x00899c90: ResizableVec<GlyphLayoutInfo>::insert(position, n, value)
// ---------------------------------------------------------------------------
struct VecGlyph {
    GlyphLayoutInfo* mpBegin;      // +0x00
    GlyphLayoutInfo* mpEnd;        // +0x04
    GlyphLayoutInfo* mpCapacity;   // +0x08
    ICoreAllocator*  mpAllocator;  // +0x0c
    unsigned int     mFlags;       // +0x10

    void DoInsertValues(GlyphLayoutInfo* position, unsigned int n, const GlyphLayoutInfo& value);
    void InsertRange(GlyphLayoutInfo* position, const GlyphLayoutInfo* first, const GlyphLayoutInfo* last, const void* unused);
};

// @ 0x00899c90
void VecGlyph::DoInsertValues(GlyphLayoutInfo* position, unsigned int n, const GlyphLayoutInfo& value)
{
    if (n <= (unsigned int)(mpCapacity - mpEnd)) {
        if (n > 0) {
            unsigned int nExtra = (unsigned int)(mpEnd - position);
            const GlyphLayoutInfo temp = value;
            GlyphLayoutInfo* const pEnd = mpEnd;

            if (n < nExtra) {
                AIUninitCopy32(mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                AICopyBackward32(position, pEnd - n, pEnd);
                AIFill32(position, position + n, &temp);
            } else {
                AIFillN32(mpEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                AIUninitCopy32(position, pEnd, mpEnd, position);
                mpEnd += nExtra;
                AIFill32(position, pEnd, &temp);
            }
        }
    } else {
        unsigned int nPrev = (unsigned int)(mpEnd - mpBegin);
        unsigned int cap2 = nPrev * 2;
        if (nPrev == 0)
            cap2 = 1;
        unsigned int want = nPrev + n;
        if (cap2 > want)
            want = cap2;

        GlyphLayoutInfo* pNewData = want ? (GlyphLayoutInfo*)mpAllocator->Alloc(want * sizeof(GlyphLayoutInfo), 0, mFlags) : 0;
        GlyphLayoutInfo* pNewEnd = AICopyRaw32(mpBegin, position, pNewData);
        AIFillN32(pNewEnd, n, &value);
        pNewEnd = AICopyRaw32(position, mpEnd, pNewEnd + n);
        if (mpBegin)
            mpAllocator->Free(mpBegin, (unsigned int)(mpCapacity - mpBegin) * sizeof(GlyphLayoutInfo));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + want;
    }
}

// ---------------------------------------------------------------------------
// 0x0089a370: ResizableVec<GlyphLayoutInfo>::insert(position, first, last)
// ---------------------------------------------------------------------------
// @ 0x0089a370
void VecGlyph::InsertRange(GlyphLayoutInfo* position, const GlyphLayoutInfo* first, const GlyphLayoutInfo* last, const void* unused)
{
    if (first == last)
        return;

    unsigned int n = (unsigned int)(last - first);
    if (n <= (unsigned int)(mpCapacity - mpEnd)) {
        unsigned int nExtra = (unsigned int)(mpEnd - position);
        GlyphLayoutInfo* const pEnd = mpEnd;

        if (n < nExtra) {
            AIUninitCopy32(mpEnd - n, mpEnd, mpEnd, first);
            mpEnd += n;
            AICopyBackward32(position, pEnd - n, pEnd);
            AICopy32(first, last, position);
        } else {
            AIUninitCopy32(first + nExtra, last, mpEnd, first);
            mpEnd += n - nExtra;
            AIUninitCopy32(position, pEnd, mpEnd, first);
            mpEnd += nExtra;
            AICopyBackward32(first, first + nExtra, position + n);
        }
    } else {
        unsigned int nPrev = (unsigned int)(mpEnd - mpBegin);
        unsigned int cap2 = nPrev * 2;
        if (nPrev == 0)
            cap2 = 1;
        unsigned int want = cap2;
        if (nPrev + n >= want)
            want = nPrev + n;

        GlyphLayoutInfo* pNewData = want ? (GlyphLayoutInfo*)mpAllocator->Alloc(want * sizeof(GlyphLayoutInfo), 0, mFlags) : 0;
        GlyphLayoutInfo* pNewEnd = AICopyRaw32(mpBegin, position, pNewData);
        pNewEnd = AIUninitCopy32(first, last, pNewEnd, first).mpCurrent;
        pNewEnd = AICopyRaw32(position, mpEnd, pNewEnd);
        if (mpBegin)
            mpAllocator->Free(mpBegin, (unsigned int)(mpCapacity - mpBegin) * sizeof(GlyphLayoutInfo));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + want;
    }
}

// ---------------------------------------------------------------------------
// 0x008997f0: basic_string<wchar_t>::set_capacity (the pre-1.11 implementation).
// ---------------------------------------------------------------------------
struct WString {
    wchar_t*        mpBegin;      // +0x00
    wchar_t*        mpEnd;        // +0x04
    wchar_t*        mpCapacity;   // +0x08
    ICoreAllocator* mpAllocator;  // +0x0c
    unsigned int    mFlags;       // +0x10

    WString(const WString& x);
    ~WString();

    void RangeInitialize(const wchar_t* first, const wchar_t* last);  // 0x008885b0
    void resize(unsigned int n);                                     // 0x00898a30
    void swap(WString& other);                                       // 0x00898e60
    void set_capacity(unsigned int n);

    wchar_t* DoAllocate(unsigned int n)
    {
        return (wchar_t*)mpAllocator->Alloc(n * sizeof(wchar_t), 0, mFlags);
    }

    static wchar_t* CharStringUninitializedCopy(const wchar_t* first, const wchar_t* last, wchar_t* dest)
    {
        unsigned int n = (unsigned int)(last - first);
        memcpy(dest, first, n << 1);
        return (wchar_t*)((char*)dest + (n << 1));
    }

    void DeallocateSelf()
    {
        int n = (int)(mpCapacity - mpBegin);
        if ((n > 1) && mpBegin)
            mpAllocator->Free(mpBegin, n * sizeof(wchar_t));
    }
};

inline WString::WString(const WString& x)
    : mpBegin(0), mpEnd(0), mpCapacity(0), mpAllocator(x.mpAllocator), mFlags(x.mFlags)
{
    RangeInitialize(x.mpBegin, x.mpEnd);
}

inline WString::~WString()
{
    DeallocateSelf();
}

// @ 0x008997f0
void WString::set_capacity(unsigned int n)
{
    if ((n != (unsigned int)-1) && (n > (unsigned int)(mpEnd - mpBegin))) {
        // grow: allocate exactly n characters, copy the contents, terminate.
        wchar_t* pNewBegin = DoAllocate(n);
        wchar_t* pNewEnd   = CharStringUninitializedCopy(mpBegin, mpEnd, pNewBegin);
        *pNewEnd = 0;
        DeallocateSelf();
        mpBegin    = pNewBegin;
        mpEnd      = pNewEnd;
        mpCapacity = pNewBegin + n;
        return;
    }

    if (n < (unsigned int)(mpEnd - mpBegin))
        resize(n);

    WString temp(*this);
    swap(temp);
}
