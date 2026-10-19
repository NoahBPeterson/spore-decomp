// src/game/UTFSpore_Win32/Form.cpp -- migrated from slice(s) s008fb7e0 by tools/migrate/rewrite.py
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

// ---- items of slice s008fb7e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00f473a0(unsigned int nSize, const char* pName, int nFlags,
                                      int nDebugFlags, const char* pFile, int nLine);
extern "C" void  __cdecl FUN_00f47380(void* p);
extern "C" void* __cdecl FUN_011e073e(void* p, int nVal, unsigned int nSize);
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
