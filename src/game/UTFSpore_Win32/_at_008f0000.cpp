// src/game/UTFSpore_Win32/_at_008f0000.cpp -- migrated from slice(s) s008ff610, s008fd6c0, s008fc670, s008fb7e0, s008f9220, s008f16c0, s008efad0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_008f0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/GlyphLayoutInfo.h"
#include "EA/Text/LineLayout.h"
#include "EA/Text/GlyphInfo.h"
#include "EA/Text/Typesetter.h"
#include <math.h>
#include "EA/XHTML/Layout/Page.h"
#include "EA/Allocator/StackAllocator.h"
#include "EA/XHTML/Style/Stylesheet.h"
#include "EA/Text/TextStyle.h"
#include <new>
#include "EA/IO/FileStream.h"
#include <intrin.h>
#include "EA/Internet/INetFileCache.h"
#include "EA/Internet/HTTPClient.h"
#include "EA/Internet/HTTPRequest.h"
#include "EA/Allocator/ICoreAllocator.h"
#include <string.h>

// ---- items of slice s008efad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
struct RectF { float l, t, r, b; };
struct StackingContext;
struct RunRecord {
    u32 mFlags;                         // +0x00
    u32 mValue;                         // +0x04
};
struct InlineBox {
    u32   mpItemAndFlags;               // +0x00
    u32   pad04[3];
    float mfX;                          // +0x10
    float mfY;                          // +0x14
    u32   pad18[2];
};
struct LineLayout {                     // +0x418 inside the Typesetter, 0x118 bytes
    u32        pad00[0x40 / 4];
    RunRecord* mpRunsBegin;             // +0x40
    RunRecord* mpRunsEnd;               // +0x44
    u32        pad48[(0x54 - 0x48) / 4];
    InlineBox* mpBoxes;                 // +0x54
    u32        pad58[(0xa0 - 0x58) / 4];
    float      mfHeight;                // +0xa0
    float      mfDescent;               // +0xa4
    u32        padA8;
    int        miFlagAC;                // +0xac
    u32        padB0[(0x118 - 0xb0) / 4];
};
struct TripleFloat {
    u32   pad00[0x3c0 / 4];
    float mfA;                          // +0x3c0
    float mfB;                          // +0x3c4
    float mfC;                          // +0x3c8
    void Set(float a, float b, float c);   // 0x00897640
};
struct Typesetter : TripleFloat {
    u32         pad3cc[(0x414 - 0x3cc) / 4];
    unsigned    mType;                  // +0x414
    LineLayout  mLineLayout;            // +0x418
    unsigned    GetType();              // 0x00897680
    LineLayout* GetLineLayout();        // 0x008976a0
    unsigned    ProcessLine();          // 0x0089cf10
    void        FinalizeLine();         // 0x0089d9a0
    void        NextLine(int a);        // 0x0089c5d0
    void        Reset(int a);           // 0x0089cdf0
};
struct FloatEntry {                     // 0x74 stride
    u32   pad00[0x54 / 4];
    int   mKind;                        // +0x54
    u32   pad58;
    FloatEntry* mpNext;                 // +0x5c
    u32   pad60;
    float mOuter;                       // +0x64
    float mSide;                        // +0x68
    float mSide2;                       // +0x6c
    float mTop;                         // +0x70
};
struct StackingContext {
    u32        pad00;                   // +0x00
    Typesetter mTypesetter;             // +0x04 .. +0x533
    float      mf534;                   // +0x534  rect left
    float      mf538;                   // +0x538  rect top
    float      mf53c;                   // +0x53c  rect right
    float      mf540;                   // +0x540  rect bottom
    float      mf544;                   // +0x544
    float      mf548;                   // +0x548
    float      mf54c;                   // +0x54c
    float      mf550;                   // +0x550
    float      mf554;                   // +0x554  line x
    float      mf558;                   // +0x558  line right
    float      mf55c;                   // +0x55c  y cursor
    float      mf560;                   // +0x560  pending margin
    float      mf564;                   // +0x564  min width
    float      mf568;                   // +0x568  max width
    float      mf56c;                   // +0x56c  last line height
    float      mf570;                   // +0x570  last line descent
    u8         mb574;                   // +0x574
    u8         pad575[3];
    FloatEntry* mpFloatsHead;           // +0x578
    FloatEntry* mpFloatsTail;           // +0x57c
    FloatEntry* mf580;                  // +0x580

    StackingContext(u32 owner);                       // @ 0x008efad0
    void  Init(u32 owner, u32 a1, u32 a2);            // @ 0x008efba0
    void  SetContextRect(const RectF& r);             // @ 0x008efc80
    void  InsertFloat(int kind);                      // @ 0x008efcd0
    void  RecomputeFloatLimits();                     // @ 0x008efd50
    void  AddFloats(LineLayout* line);                // @ 0x008efde0
    void  FlushLines(int count);                      // @ 0x008efe80
    void  FlushAllLines();                            // @ 0x008f0010
    void  CollapseMargin(float margin);               // @ 0x008f01b0
    float ClampWidth(float w);                        // @ 0x008f0240
    void  RegisterFloat(FloatEntry* e);               // @ 0x008f0280
};
// ---- items of slice s008efad0 end

// ---- items of slice s008f16c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace XHTML {
namespace Layout {
class PageText {
public:
    uint32_t GetTextStyle(void* arg);                       // 0x008ec580
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class StyleOwner {
public:
    void ApplyStyleA(void* a, int b, uint32_t c);           // 0x008efa50
    void ApplyStyleB(void* a, int b, uint32_t c);           // 0x008ef8d0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class TextItemX {
public:
    uint8_t pad00[0x0c];
    PageText* mpPage;                      // +0x0c
    uint8_t pad10[0x08];
    void* mpStyle;                         // +0x18
    int mLength;                           // +0x1c
    uint32_t mTextStyle;                   // +0x20

    void F_8f2350(void* owner, void* styleArg);             // 0x008f2350
    void F_8f2380(void* owner, void* styleArg);             // 0x008f2380
    void F_8f23b0(void* owner);                             // 0x008f23b0
    bool F_8f23d0(void* owner, void* unused);               // 0x008f23d0
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PickCtxX {
public:
    void PickTextA(TextItemX* item, uint32_t style);        // 0x008ee400
    void PickTextB(TextItemX* item, uint32_t style);        // 0x008ee990
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
class PropNodeX {
public:
    uint32_t mVtable;                      // +0x00
    uint32_t mField04;                     // +0x04
    uint32_t mField08;                     // +0x08
    uint32_t mField0c;                     // +0x0c
    int mLength;                           // +0x10

    PropNodeX* F_8f2440(int a, const uint16_t* str);        // 0x008f2440
    PropNodeX* F_8f24a0(int a, const uint16_t* str);        // 0x008f24a0
};
}
}
}
// ---- items of slice s008f16c0 end

// ---- items of slice s008f9220 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Allocator {
class StackAllocator_s008f_9220 {  // size 0x24
public:
    StackAllocator_s008f_9220() {}
    StackAllocator_s008f_9220(int, int, int, int, int);    // 0x00928cd0
    ~StackAllocator_s008f_9220() { Reset(); }
    bool AllocateNewBlock(unsigned int nSize);   // 0x00928ba0
    void Init(int, int, int, int, int);          // 0x00928b00
    void Reset();                                // 0x00928dc0
    unsigned int mnDefaultBlockSize;  // +0x0
    void* mpCurrentBlock;             // +0x4
    char* mpCurrentBlockEnd;          // +0x8
    char* mpCurrentObjectBegin;       // +0xc
    char* mpCurrentObjectEnd;         // +0x10
    char _padExtra[0x10];             // +0x14..0x23 (size 0x24)
};  // namespace Allocator
}
}
namespace EA {
namespace XHTML {
namespace DOM {
class Node {  // non-polymorphic DOM node (layout only)
public:
    Node* Parent();                                    // 0xff0420
    const wchar_t* GetAttrValue(const wchar_t* name);  // 0x8e45b0
    char _pad0[0x14];
    Node* mpParent;              // +0x14
    char _pad1[0x18];            // +0x18..0x2f
    int mField30;                // +0x30
    const wchar_t* mpTagName;    // +0x34
    const wchar_t* mpId;         // +0x38
    char _pad2[4];               // +0x3c
    void* mpField40;             // +0x40
};  // namespace DOM
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
using EA::XHTML::DOM::Node;
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Selector {
public:
    Selector() : mpNext(0) {}
    virtual ~Selector();
    virtual bool Match(Node* pNode, bool bDeep);
    virtual void* Slot2() { return 0; }
    void Append(Selector* p);   // 0x008f9fa0
    Selector* mpNext;           // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct LengthContext {
    int mReserved;  // +0x0
    float mEm;      // +0x4
    float mEx;      // +0x8
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct Length {
    float mValue;  // +0x0
    int mUnits;    // +0x4
    float ToPixels(float fRelative, const LengthContext* pCtx) const;        // 0x008f95c0
    float ToPixelsNonNeg(float fRelative, const LengthContext* pCtx) const;  // 0x008f9660
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class StylesheetBase {
public:
    StylesheetBase() : mField4(0) {}
    virtual ~StylesheetBase() {}
    int mField4;  // +0x4
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
class Stylesheet_s008f_9220 : public StylesheetBase {
public:
    Stylesheet_s008f_9220(void* p);
    // @ 0x008f9e20 Stylesheet::~Stylesheet (deleting dtor inlined)
    virtual ~Stylesheet_s008f_9220() {
        mAllocator.Reset();
        if (mVecBegin != 0 && mVecBegin != (void**)mField44)
            operator delete(mVecBegin);
    }
    void AddRule(const wchar_t* pName, void* pDecl);  // 0x008f9cd0
    void AddRule2(Selector* pSel, void* pDecl);       // 0x008f9c20
    void AppendNode(void* pNode);                     // 0x008f9bf0
    void Clear();                                     // 0x008f9ed0
    void InsertRuleAt(void** pos, void** val);  // 0x00899480

    EA::Allocator::StackAllocator_s008f_9220 mAllocator;  // +0x8
    void* mpFirst;      // +0x2c
    void* mpLast;       // +0x30
    void** mVecBegin;   // +0x34
    void** mVecEnd;     // +0x38
    void** mVecCap;     // +0x3c
    void* mField40;     // +0x40
    void* mField44;     // +0x44
    void* mField48;     // +0x48
    char mInline[0x20]; // +0x4c
    void* mField6c;     // +0x6c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct RbtreeInsertResult { void* mpNode; int mbInserted; };  // 8 bytes -> sret
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct RbtreeTrueType {};  // empty tag: MSVC pushes 1 byte, upper stack bytes uninitialised
}
}
}
namespace EA {
namespace XHTML {
namespace Style {
struct RbtreeMap {
    RbtreeInsertResult FUN_009c1700(const void* pValue, RbtreeTrueType t);  // 0x009c1700
    void FUN_008f9e70();                                                    // 0x008f9e70
    void FUN_00d3b370(void* pNode);                                         // 0x00d3b370
};
}
}
}
// ---- items of slice s008f9220 end

// ---- items of slice s008fb7e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Page;
namespace Style {
enum Unit { Unit_Auto = 10, Unit_Pixels = 1 };
}
namespace Style {
struct Length_s008f_b7e0 {
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
    Length_s008f_b7e0 mBorder;                 // +0x00
    Length_s008f_b7e0 mPadding;                // +0x08
    Length_s008f_b7e0 mMargin;                 // +0x10
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
    Length_s008f_b7e0      mFontSize;              // +0x284
    uint32_t    mFgColor;               // +0x28c
    Length_s008f_b7e0      mLineHeight;            // +0x290
    Length_s008f_b7e0      mFontSmoothThresh;      // +0x298
    void*       mpBackgroundImage;      // +0x2a0
    uint32_t    mBackgroundRepeat;      // +0x2a4
    uint32_t    mBackgroundAttachment;  // +0x2a8
    Length_s008f_b7e0      mBackgroundPosX;        // +0x2ac
    Length_s008f_b7e0      mBackgroundPosY;        // +0x2b4
    uint32_t    mBgColor;               // +0x2bc
    uint32_t    mColorInherited;        // +0x2c0
    Length_s008f_b7e0      mWordSpacing;           // +0x2c4
    Length_s008f_b7e0      mLetterSpacing;         // +0x2cc
    Length_s008f_b7e0      mVerticalAlign;         // +0x2d4
    uint32_t    mVerticalAlignKW;       // +0x2dc
    uint32_t    mTextTransform;         // +0x2e0
    Length_s008f_b7e0      mTextIndent;            // +0x2e4
    Edge        mEdges[4];              // +0x2ec .. +0x36b
    Length_s008f_b7e0      mBoxX;                  // +0x36c
    Length_s008f_b7e0      mBoxY;                  // +0x374
    uint32_t    mField37c;              // +0x37c
    uint32_t    mField380;              // +0x380
    uint32_t    mField384;              // +0x384
    Length_s008f_b7e0      mBoxOffset[4];          // +0x388 .. +0x3a7
    uint32_t    mTableAlign;            // +0x3a8
    uint32_t    mField3ac;              // +0x3ac
    uint32_t    mField3b0;              // +0x3b0
    uint32_t    mField3b4;              // +0x3b4
    uint32_t    mField3b8;              // +0x3b8
    CounterMap  mCounters;              // +0x3bc
    CounterMap  mCounterIncrement;      // +0x3dc
    CounterMap  mCounterReset;          // +0x3fc
    Length_s008f_b7e0      mBorderSpacingH;        // +0x41c
    Length_s008f_b7e0      mBorderSpacingV;        // +0x424
    uint32_t    mField42c;              // +0x42c
    FontMetrics mFontMetrics;           // +0x430
    uint32_t    mField444;              // +0x444
    uint32_t    mField448;              // +0x448
    uint32_t    mField44c;              // +0x44c
};
}
// ---- items of slice s008fb7e0 end

// ---- items of slice s008fc670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma function(memcpy)
#pragma intrinsic(strcmp)
struct HTTPx {
    char pad0[0x1d0];
    uint8_t mb1d0;      // +0x1d0
    char pad1[3];
    float  mf1d4;       // +0x1d4

    void SetFlagBool(bool b, float f);
};
// ---- items of slice s008fc670 end

// ---- items of slice s008fd6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __cdecl strlen(const char* s);
#pragma intrinsic(strlen)
struct Ratio {
    char pad0[0x144];
    unsigned m144;          // +0x144
    unsigned m148;          // +0x148
    uint16_t m14c;          // +0x14c
    void Set(int v, uint16_t den);
};
// ---- items of slice s008fd6c0 end

// ---- items of slice s008ff610 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IUnk {
    virtual void AddRef();
    virtual void Release();
};
struct IRC {  // refcounted interface (dtor, AddRef, Release)
    virtual void v0(int);
    virtual void AddRef();
    virtual void Release();
};
struct ResourceRequest;
typedef void (__cdecl *ReqCb)(void* evt, void* ctx);
struct ILogListener;
struct ResourceRequest {
    ResourceRequest* mpNext;        // +0
    ResourceRequest* mpPrev;        // +4
    ILogListener* mpErrorListener;  // +8
    const uint16_t* mpURL;          // +0xc
    char* mTypeBegin;               // +0x10
    char* mTypeEnd;                 // +0x14
    char* mTypeCap;                 // +0x18
    int mTypePad;                   // +0x1c
    IUnk* mpResource;               // +0x20
    int mEncoding;                  // +0x24
    int mEncodingSource;            // +0x28
    bool mCacheable;                // +0x2c
    ReqCb mpCallback;               // +0x30
    void* mpContext;                // +0x34
    unsigned mRequestId;            // +0x38
    IRC* mpStream;                  // +0x3c

    ResourceRequest(const uint16_t* url, ILogListener* el);
    bool SetEncoding(int enc, int src);
};
struct UPair {
    unsigned first;
    ResourceRequest* second;
};
UPair* __cdecl LowerBound(UPair* b, UPair* e, unsigned* key, uint8_t flag);  // 0x00d01260
struct UMap {
    UPair* mpBegin;     // +0
    UPair* mpEnd;       // +4
    UPair* mpCap;       // +8
    char pad[8];
    uint8_t mFlag;      // +0x14
    UMap()
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCap = 0;
    }
    unsigned erase(unsigned* key);
    ResourceRequest** GetOrInsert(unsigned* key);   // vector_map operator[] (named so the checker can find it)
    UPair* insert(UPair* pos, UPair* val);   // 0x009970e0
};
// ---- items of slice s008ff610 end

// @ 0x008f01b0
void StackingContext::CollapseMargin(float margin)
{
    float pending = mf560;
    if (pending < 0.0f) {
        if (0.0f <= margin) {
            mf55c = (mf55c + pending) + margin;
            mf560 = 0.0f;
            return;
        }
        mf55c += (margin < pending || margin == pending) ? margin : pending;
    } else {
        if (margin <= pending) {
            if (0.0f <= margin)
                goto Ldone;
            {
                float neg = -pending;
                mf55c += (neg < margin) ? margin : neg;
            }
        } else {
            mf55c += margin - pending;
        }
    }
Ldone:
    mf560 = 0.0f;
}

// @ 0x008f0240
float StackingContext::ClampWidth(float w)
{
    float* pf = (w > mf568) ? &w : &mf568;
    float v = *pf;
    if (v > mf564)
        return mf564;
    return v;
}

// @ 0x008f2350
namespace EA { namespace XHTML { namespace Layout {
void TextItemX::F_8f2350(void* owner, void* styleArg)
{
    if (mLength > 0) {
        mTextStyle = mpPage->GetTextStyle(styleArg);
        ((StyleOwner*)owner)->ApplyStyleA(mpStyle, mLength, mTextStyle);
    }
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f2380
namespace EA { namespace XHTML { namespace Layout {
void TextItemX::F_8f2380(void* owner, void* styleArg)
{
    if (mLength > 0) {
        mTextStyle = mpPage->GetTextStyle(styleArg);
        ((StyleOwner*)owner)->ApplyStyleB(mpStyle, mLength, mTextStyle);
    }
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f23b0
namespace EA { namespace XHTML { namespace Layout {
void TextItemX::F_8f23b0(void* owner)
{
    if (mLength > 0)
        ((PickCtxX*)owner)->PickTextB(this, mTextStyle);
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f23d0
namespace EA { namespace XHTML { namespace Layout {
bool TextItemX::F_8f23d0(void* owner, void* unused)
{
    if (mLength > 0)
        ((PickCtxX*)owner)->PickTextA(this, mTextStyle);
    return false;
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f2440
namespace EA { namespace XHTML { namespace Layout {
PropNodeX* PropNodeX::F_8f2440(int a, const uint16_t* str)
{
    mField04 = 0;
    mVtable = 0x01439a3c;
    mField08 = (uint32_t)a;
    mField0c = (uint32_t)str;
    if (str) {
        const uint16_t* p = str + 1;
        uint16_t c;
        do {
            c = *str;
            ++str;
        } while (c != 0);
        mLength = (int)(str - p);
    } else {
        mLength = -1;
    }
    return this;
}
}}}  // namespace EA::XHTML::Layout

// @ 0x008f95c0
namespace EA { namespace XHTML { namespace Style {
float Length::ToPixels(float fRelative, const LengthContext* pCtx) const
{
    switch (mUnits) {
    case 1:
    case 2:
        return mValue;
    case 3:
        return mValue * 12.0f;
    case 6:
        return mValue * 72.0f;
    case 4:
        return mValue * 28.346401f;
    case 5:
        return mValue * 2.83464f;
    case 7:
        return pCtx->mEm * mValue;
    case 8:
        return pCtx->mEx * mValue;
    case 9:
        return mValue * fRelative * 0.01f;
    case 0:
        return mValue * fRelative;
    default:
        return 0.0f;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9660
namespace EA { namespace XHTML { namespace Style {
float Length::ToPixelsNonNeg(float fRelative, const LengthContext* pCtx) const
{
    float f = ToPixels(fRelative, pCtx);
    return f < 0.0f ? 0.0f : f;
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9bf0
namespace EA { namespace XHTML { namespace Style {
void Stylesheet_s008f_9220::AppendNode(void* pNode)
{
    *(void**)pNode = 0;
    if (mpLast != 0) {
        *(void**)mpLast = pNode;
        mpLast = pNode;
    } else {
        mpFirst = pNode;
        mpLast = pNode;
    }
}
}}}  // namespace EA::XHTML::Style

// @ 0x008f9ed0
namespace EA { namespace XHTML { namespace Style {
void Stylesheet_s008f_9220::Clear()
{
    char tree[0x560];
    RbtreeMap* map = (RbtreeMap*)tree;
    map->FUN_008f9e70();
    for (void* rule = mpFirst; rule != 0; rule = *(void**)rule) {
        void** lst = *(void***)((char*)rule + 8);
        for (Selector* s = (Selector*)lst[0]; s != 0; s = s->mpNext) {
            void* v = s->Slot2();
            if (v)
                map->FUN_009c1700(&v, RbtreeTrueType());
        }
        for (Selector* s = (Selector*)lst[1]; s != 0; s = s->mpNext) {
            void* v = s->Slot2();
            if (v)
                map->FUN_009c1700(&v, RbtreeTrueType());
        }
    }
    map->FUN_00d3b370(*(void**)(tree + 0xc));
}
}}}  // namespace EA::XHTML::Style

// @ 0x008fb8a0
namespace Style {
void StyleState::SetFontSizeKeyword(unsigned int kw)
{
    switch (kw) {
    case 0: mFontSize.mUnits = 1; mFontSize.mValue = 6.0f;  mbFontChanged = true; return;
    case 1: mFontSize.mUnits = 1; mFontSize.mValue = 8.0f;  mbFontChanged = true; return;
    case 2: mFontSize.mUnits = 1; mFontSize.mValue = 10.0f; mbFontChanged = true; return;
    case 3: mFontSize.mUnits = 1; mFontSize.mValue = 12.0f; mbFontChanged = true; return;
    case 4: mFontSize.mUnits = 1; mFontSize.mValue = 14.0f; mbFontChanged = true; return;
    case 5: mFontSize.mUnits = 1; mFontSize.mValue = 16.0f; mbFontChanged = true; return;
    case 6: mFontSize.mUnits = 1; mFontSize.mValue = 20.0f; break;
    default: break;
    }
    mbFontChanged = true;
}
}  // namespace Style

// @ 0x008fb9c0
namespace Style {
void StyleState::FUN_008fb9c0()
{
    mFontSize.mValue *= 0.8f;
    mbFontChanged = true;
}
}  // namespace Style

// @ 0x008fb9e0
namespace Style {
bool StyleState::FUN_008fb9e0()
{
    if (mBoxX.mUnits != Unit_Auto && mBoxX.mValue != 0.0f)
        return true;
    if (mBoxY.mUnits != Unit_Auto && mBoxY.mValue != 0.0f)
        return true;
    int i = 0;
    int* p = (int*)&mEdges[0].mPadding.mUnits;
    while (i < 4) {
        if (p[2] != (int)Unit_Auto && *(float*)&p[1] != 0.0f)
            return true;
        if (p[-2] != (int)Unit_Auto && *(float*)&p[-3] != 0.0f)
            return true;
        if (p[0] != (int)Unit_Auto && *(float*)&p[-1] != 0.0f)
            return true;
        ++i;
        p += 8;
    }
    return false;
}
}  // namespace Style

// @ 0x008fba80
namespace Style {
bool StyleState::FUN_008fba80()
{
        int i = 0;
    int* p = (int*)&mEdges[0].mBorderColor;
    while (i < 4) {
        if (p[0] != 0 &&
            p[-1] != (int)Unit_Auto &&
            *(float*)&p[-2] != 0.0f)
            return true;
        ++i;
        p += 8;
    }
    return false;
}
}  // namespace Style

// @ 0x008fd050
void HTTPx::SetFlagBool(bool b, float f)
{
    mb1d0 = b;
    mf1d4 = f;
}

// @ 0x008fe380
void Ratio::Set(int v, uint16_t den)
{
    m148 = (unsigned)v;
    m148 = m14c ? m144 / m14c : 0;
    m14c = den;
    m148 = den ? m144 / den : 0;
}

// @ 0x008ffdf0
ResourceRequest** UMap::GetOrInsert(unsigned* key)
{
    UPair* b = mpBegin;
    UPair* e = mpEnd;
    UPair* it = LowerBound(b, e, key, mFlag);
    if (it == e || *key < it->first) {
        unsigned k = *key;
        UPair val;
        val.first = k;
        val.second = 0;
        if (it == e || k >= it->first)
            it = LowerBound(it, e, &val.first, mFlag);
        else
            it = LowerBound(b, it, &val.first, mFlag);
        if (it == e || k < it->first)
            it = insert(it, &val);
    }
    return &it->second;
}
