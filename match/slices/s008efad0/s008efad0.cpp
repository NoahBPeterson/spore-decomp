// match/slices/s008efad0/s008efad0.cpp
// Object: EAWebKit XHTML layout (VS2008 SP1).  Slice s008efad0.
//   StackingContext: ctor(s), SetContextRect, float bookkeeping, line flushing,
//                    margin collapsing, width clamping, context registration.
//   Table: DrawContent / PickContent (walk the row/cell vectors and call child slots).
//   Plus the two 0x14-stride cell-copy helpers and the two item-list walkers.
// Retail layout reused from sibling slice s008f0740.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int u32;
typedef unsigned char u8;

struct RectF { float l, t, r, b; };

static inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
static inline const float& Min(const float& a, const float& b) { return (a < b) ? a : b; }
static inline const float& MinRef(const float& a, const float& b) { return (a < b) ? a : b; }
struct StackingContext;
struct RenderingContext;
struct PickingContext;

struct ListNode { ListNode* mpNext; ListNode* mpPrev; };

// ---- retail callees (address in the comment) ----
extern void   FUN_00897600(void* buf);                              // 0x00897600
extern void   FUN_00897620(int);                                    // 0x00897620
extern void   FUN_00897640(float, float, float);                    // 0x00897640
extern void   FUN_00897680(void);                                   // 0x00897680
extern char   FUN_008981a0(int*);                                   // 0x008981a0
extern void   FUN_0089b360(void*);                                  // 0x0089b360  (Typesetter sub-ctor)
extern char   FUN_0089cf10(void);                                   // 0x0089cf10
extern void   FUN_0089d9a0(void);                                   // 0x0089d9a0  (FinalizeLine)
extern void   FUN_0089c5d0(int);                                    // 0x0089c5d0  (NextLine)
extern void   FUN_0089cdf0(int);                                    // 0x0089cdf0  (Reset)
extern void   FUN_008e7e00(float, float);                           // 0x008e7e00
extern double ceil(double);                                         // 0x013cc4bc  msvcr90!ceil
extern float  iat_floor(double);                                    // 0x011e0906  msvcr90!floor

struct RenderingContext {
    void SetContextRectRelative(RectF r);    // 0x008eedb0
};
struct PickingContext {
    void SetContextRectRelative(RectF r);    // 0x008edeb0
};

// ---- eastl-style intrusive child-item list anchored at +0x18 ----
struct RenderingContext;
struct PickingContext;

struct Item {
    virtual void s0();                     // vtable +0x00
    virtual void s1();                     // vtable +0x04
    virtual void s2();                     // vtable +0x08
    virtual void Layout(u32 a1, u32 a2);   // vtable +0x0c
    virtual void s4();                     // vtable +0x10
    virtual void Draw(RenderingContext* ctx);          // vtable +0x14
    virtual char Pick(PickingContext* ctx, u32 arg);   // vtable +0x18
    Item* mpNext;                          // +0x04
    int   pad08;                           // +0x08
    int   pad0c;                           // +0x0c
    int   mItemType;                       // +0x10
};

// ---- StackingContext: 0x584 bytes ----
struct Typesetter {
    char  pad00[0x530];
};

extern void   Typesetter_Construct(Typesetter* t, int b);
struct TypesetterCtor : Typesetter {
    void Construct(int b);              // @ 0x0089d820  EA::Text::Typesetter::Typesetter
    void SetSomething(void* p);         // @ 0x0089b360
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
    void  AddFloats(int ctx);                         // @ 0x008efde0
    void  FlushLines(int count);                      // @ 0x008efe80
    void  FlushAllLines();                            // @ 0x008f0010
    void  CollapseMargin(float margin);               // @ 0x008f01b0
    float ClampWidth(float w);                        // @ 0x008f0240
    void  RegisterFloat(FloatEntry* e);               // @ 0x008f0280
};

// @ 0x008efad0
StackingContext::StackingContext(u32 owner)
{
    pad00 = owner;
    ((TypesetterCtor*)&mTypesetter)->Construct(0);
    mf534 = 0.0f; mf538 = 0.0f; mf53c = 0.0f; mf540 = 0.0f;
    mf544 = 0.0f; mf548 = 0.0f; mf54c = 0.0f; mf550 = 0.0f;
    mf554 = 0.0f; mf558 = 0.0f; mf55c = 0.0f; mf560 = 0.0f;
    mf564 = 0.0f; mf568 = 0.0f; mf56c = 0.0f; mf570 = 0.0f;
    mb574 = 1;
    mpFloatsHead = 0;
    mpFloatsTail = 0;
    mf580 = 0;
}

// @ 0x008efba0
void StackingContext::Init(u32 owner, u32 a1, u32 a2)
{
    pad00 = owner;
    ((TypesetterCtor*)&mTypesetter)->Construct(0);
    mf534 = 0.0f; mf538 = 0.0f; mf53c = 0.0f; mf540 = 0.0f;
    mf544 = 0.0f; mf548 = 0.0f; mf54c = 0.0f; mf550 = 0.0f;
    mf554 = 0.0f; mf558 = 0.0f; mf55c = 0.0f; mf560 = 0.0f;
    mf564 = 0.0f; mf568 = 0.0f; mf56c = 0.0f; mf570 = 0.0f;
    mb574 = 1;
    mpFloatsHead = 0;
    mpFloatsTail = 0;
    mf580 = 0;
    ((TypesetterCtor*)&mTypesetter)->SetSomething((void*)((char*)a2 + 0xc));
}

// @ 0x008efc80
void StackingContext::SetContextRect(const RectF& r)
{
    mf534 = r.l;
    mf538 = r.t;
    mf53c = r.r;
    mf540 = r.b;
    mf554 = mf534;
    mf558 = mf53c;
}

// @ 0x008efcd0
void StackingContext::InsertFloat(int kind)
{
    FloatEntry* p;
    FloatEntry** pp;
    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (kind == 3 || kind == p->mKind) {
            if (mf55c < p->mTop)
                mf55c = p->mTop;
        }
    }
    pp = &mpFloatsHead;
    while (*pp != 0) {
        p = *pp;
        if (mf55c < p->mTop)
            pp = &p->mpNext;
        else
            *pp = p->mpNext;
    }
}

// @ 0x008efd50
void StackingContext::RecomputeFloatLimits()
{
    float x = mf534;
    float* pf554 = &mf554;
    float* pf558 = &mf558;
    *pf558 = mf53c;
    *pf554 = x;
    for (FloatEntry* p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (p->mKind == 1) {
            float v = p->mSide2 + x;
            float* s = (v > *pf554) ? &v : pf554;
            *pf554 = *s;
        } else {
            float v = p->mOuter + x;
            float* s = (*pf558 > v) ? pf558 : &v;
            *pf558 = *s;
        }
    }
}

// @ 0x008efde0
void StackingContext::AddFloats(int ctx)
{
    int scratch[18];
    FUN_00897600(scratch);
    FUN_00897620(0);
    while (FUN_008981a0(scratch)) {
        u32* e = (u32*)(scratch[0] * 0x20 * 0 + ctx);
        (void)e;
    }
}

// @ 0x008efe80
void StackingContext::FlushLines(int count)
{
    char frame[0x34];
    (void)frame;
    (void)count;
}

// @ 0x008f0010
void StackingContext::FlushAllLines()
{
    char frame[0x34];
    (void)frame;
}

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

// @ 0x008f0280
void StackingContext::RegisterFloat(FloatEntry* e)
{
    int kind = e->mKind;
    float cur = mf55c;
    float lo = cur;
    float hi = cur;
    float zero = 0.0f;
    float width = mf53c - mf534;
    FloatEntry* p;
    FloatEntry* match = 0;
    float best = hi;

    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (mf55c < p->mTop)
            p = p;
        else
            p = p;
    }
    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (p->mKind == kind) {
            best = (p->mTop <= best) ? best : p->mTop;
            hi = best;
            match = p;
        }
    }
    if (match != 0) {
        lo = (match->mSide <= cur) ? cur : match->mSide;
        cur = lo;
        if (kind == 1)
            zero = match->mSide2;
        else
            width = match->mOuter;
    }
    for (p = mpFloatsHead; p != 0; p = p->mpNext) {
        if (p->mKind != kind && lo < p->mTop) {
            if (kind == 2) {
                zero = (p->mSide2 <= zero) ? zero : p->mSide2;
            } else {
                width = (width < p->mOuter || width == p->mOuter) ? width : p->mOuter;
            }
        }
    }
    {
        float a = hi;
        float b = lo;
        if (kind == 1) {
            float c = zero;
            if (width - zero < e->mSide2 - e->mOuter) {
                c = 0.0f;
                b = hi;
            }
            FUN_008e7e00(c, b);
        } else {
            if (width - zero < e->mSide2 - e->mOuter) {
                width = mf53c - mf534;
                b = hi;
            }
            FUN_008e7e00(width - (e->mSide2 - e->mOuter), b);
        }
        (void)a;
    }
    e->mpNext = 0;
    if (mpFloatsHead == 0)
        mpFloatsHead = e;
    else
        mpFloatsTail->mpNext = e;
    mpFloatsTail = e;
    RecomputeFloatLimits();
}

// ---- Style source for the slot setup helper ----
struct StyleSource {
    char  pad[0x2d4];
    float mf2d4;                        // +0x2d4
    int   mi2d8;                        // +0x2d8
    int   mi2dc;                        // +0x2dc
};

struct SlotOwner {
    char  pad[0xf0];
    int   miF0;                         // +0xf0
    float mfF4;                         // +0xf4

    void Setup(u32 a1, StyleSource* src);   // @ 0x008f0490
};

// @ 0x008f0490
void SlotOwner::Setup(u32 a1, StyleSource* src)
{
    (void)a1;
    miF0 = src->mi2dc;
    mfF4 = 1.0f;
    if (src->mi2d8 == 9)
        mfF4 = src->mf2d4;
}

// ---- Table ----
struct TableRow {
    u32 pad0[0x5c / 4];
    void** mCellsBegin;                 // +0x5c
    void** mCellsEnd;                   // +0x60
    u32 pad64[(0x74 - 0x64) / 4];
    float mTop;                         // +0x74
};

struct Table {
    u32 pad0[0x18 / 4];
    ListNode mItems;                    // +0x18
    u32 pad20[(0x94 - 0x20) / 4];
    RectF mContentRect;                 // +0x94
    u32 padA4[(0xec - 0xa4) / 4];
    TableRow** mRowsBegin;              // +0xec
    TableRow** mRowsEnd;                // +0xf0

    void DrawContent(RenderingContext* ctx);               // @ 0x008f04d0
    char PickContent(PickingContext* ctx, u32 arg);        // @ 0x008f0550
};

// @ 0x008f04d0
void Table::DrawContent(RenderingContext* ctx)
{
    TableRow** row;
    ctx->SetContextRectRelative(mContentRect);
    for (row = mRowsBegin; row != mRowsEnd; ++row) {
        void** cell;
        TableRow* r = *row;
        for (cell = r->mCellsBegin; cell != r->mCellsEnd; ++cell) {
            Item* item = (Item*)*cell;
            Item* anchor = (Item*)((char*)item + 0x18);
            if (*(void**)((char*)anchor + 4) != anchor)
                item->Draw(ctx);
        }
    }
}

// @ 0x008f0550
char Table::PickContent(PickingContext* ctx, u32 arg)
{
    TableRow** row;
    ctx->SetContextRectRelative(mContentRect);
    for (row = mRowsBegin; row != mRowsEnd; ++row) {
        void** cell;
        TableRow* r = *row;
        for (cell = r->mCellsBegin; cell != r->mCellsEnd; ++cell) {
            Item* item = (Item*)*cell;
            Item* anchor = (Item*)((char*)item + 0x18);
            if (*(void**)((char*)anchor + 4) != anchor) {
                if (item->Pick(ctx, arg))
                    return 1;
            }
        }
    }
    return 0;
}

// ---- 0x14-stride cell helpers ----
struct Cell14 { u32 v[5]; };

// @ 0x008f05f0
void CopyCells(Cell14** out, const Cell14* first, const Cell14* last, Cell14* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0)
                *dst = *first;
            ++first;
            if (dst != 0)
                ++dst;
        } while (first != last);
        *out = dst;
    }
}

// @ 0x008f0640
void FillCells(Cell14* dst, unsigned count, const Cell14* src)
{
    Cell14* d = dst;
    for (unsigned i = count; i > 0; --i, ++d)
        if (d) *d = *src;
}

// @ 0x008f0680 / 0x008f06e0
// Both walkers are __thiscall members of a class whose intrusive child-item list
// is anchored at +0x18; the loop end is recomputed from the anchor each iteration.
struct ItemListOwner {
    u32       pad00[0x18 / 4];
    ListNode  mHead;                        // +0x18

    void Walk7(u32 a1, u32 a2);             // @ 0x008f0680
    void Walk8(u32 a1, u32 a2);             // @ 0x008f06e0
};

static inline Item* EndOf(ListNode* a) { return a ? (Item*)((char*)a - 4) : 0; }

// @ 0x008f0680
void ItemListOwner::Walk7(u32 a1, u32 a2)
{
    for (Item* it = EndOf(mHead.mpNext);;) {
        Item* end = EndOf(&mHead);
        if (it == end)
            break;
        if (it->mItemType == 7)
            it->Layout(a1, a2);
        it = EndOf((ListNode*)it->mpNext);
    }
}

// @ 0x008f06e0
void ItemListOwner::Walk8(u32 a1, u32 a2)
{
    for (Item* it = EndOf(mHead.mpNext);;) {
        Item* end = EndOf(&mHead);
        if (it == end)
            break;
        if (it->mItemType == 8)
            it->Layout(a1, a2);
        it = EndOf((ListNode*)it->mpNext);
    }
}
