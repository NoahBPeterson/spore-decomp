// Slice s008edc30 (batch gold4, slice 9) -- EA::XHTML::Layout picking/rendering contexts.
//   0x008edc30  Page::CreatePageLayout
//   0x008edc90  Page::SetDocument
//   0x008edd30  style ctor forward (StyleCtor, 2 args)
//   0x008edd50  scrollbar style setter
//   0x008edd80  scrollbar style getter
//   0x008eddb0  PickingContext::RefreshMargins
//   0x008ede40  PickingContext::SetContextRect
//   0x008edeb0  PickingContext::SetContextRectRelative
//   0x008edf60  PickingContext::PlaceFloat
//   0x008edfc0  eastl::lower_bound
//   0x008ee010  PickingContext::Flush
//   0x008ee240  PickingContext::PickingContext (from screen rect)
//   0x008ee2f0  PickingContext::PickingContext (copy)
//   0x008ee400  PickingContext::PickTextItem
//   0x008ee4a0  PickingContext::FlushAll
//   0x008ee720  scrollbar style setter (this+4)
//   0x008ee740  scrollbar style getter (this+4)
//   0x008ee770  scrollbar style getter 2 (this+4)
//   0x008ee7a0  this->mpScroll->release helper
//   0x008ee7b0  RenderingContext::ScrollViewport
//   0x008ee810  RenderingContext::RenderingContext (from rects)
//   0x008ee8c0  RenderingContext::RenderingContext (copy)
//   0x008ee990  RenderingContext::Place
//   0x008eea30  RenderingContext::RefreshMargins
//   0x008eeac0  RenderingContext::TestRect
//   0x008eeb30  RenderingContext::ScrollRect
// Object file: EAWebKit XHTML layout (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include

#include "types.h"

namespace EA {
namespace XHTML {
namespace Layout {

struct Vec2 {
    float x, y;
};

// ---- XHTML node / layout object shapes used by this slice ----
struct FloatEntry {                 // 0x74
    uint32_t mPad00[0x54 / 4];      // +0x00
    int      mKind;                 // +0x54
    uint32_t mPad58;                // +0x58
    FloatEntry* mpNext;             // +0x5c
    uint32_t mPad60;                // +0x60
    float    mSizeBig;              // +0x64
    float    mSizeSmall;            // +0x68
    float    mSizeOther;            // +0x6c
    float    mMaxY;                 // +0x70
    uint32_t mPad74;
};

struct TranslationEntry {           // 0x0c
    int mValue;                     // +0x00
    int mIndex;                     // +0x04
    int mExtra;                     // +0x08
};

struct TranslationVector {          // eastl vector<TranslationEntry>, 0x14
    TranslationEntry* mpBegin;      // +0x00
    TranslationEntry* mpEnd;        // +0x04
    TranslationEntry* mpCapacity;   // +0x08
    uint32_t mAllocator[2];         // +0x0c
};

struct ScrollInfo {                 // the refcounted scroll/viewport object
    int mVtbl;                      // +0x00
};

// ---- external callees (addresses in comments) ----
void* __fastcall Page_CreatePageLayout(void* self, int);         // 0x008e2810
void  __fastcall Page_Reset(void* self, int);                    // 0x008eb7a0
void  __fastcall Page_DestroyLayout(void* self, int, void* layout); // 0x008ebd50
char  __fastcall Document_Destroy(void* self, int, int one);     // 0x008e29e0
void  __cdecl PageLayoutCtor(void* dst, void* a);                // 0x008fbe00
void  __cdecl PageLayoutDtor(void* p);                           // 0x008e8650
void* __cdecl PageLayout_Build(void* self, void* layout, void* a, int b); // 0x008ecfa0
void  __cdecl ScrollVectorClear(void* a, void* b);               // 0x00e25bd0
void  __fastcall Node_SetFlag(void* node, int, int flag);        // 0x00928c40

void* __fastcall StyleCtor(void* self, int, void* rect, int a, int b);  // 0x0089b250
char  __fastcall StyleSet(void* self, int, void* a);             // 0x008eaf30
void  __fastcall StyleAssign(void* self, int, void* v);          // 0x0089b360
void  __fastcall StyleAssign2(void* self, int, int a, int b);    // 0x0089b1e0
void  __fastcall StyleCopyRange(void* self, int, void* v);       // 0x00a27910
void  __fastcall StyleGet(void* self, int, int a, int b, void* out); // 0x008e69b0

void* __cdecl  ScrollAppGet(void);                               // 0x006e64f0
void* __fastcall ScrollGlobalList(void* a);                      // 0x008976a0
void  __fastcall Scroll_SetViewport(void* self, int, float a, float b, float c); // 0x00897640
int   __fastcall Scroll_GetState(void* self, int);               // 0x0089cf10
int   __fastcall Scroll_GetState2(void* self, int);              // 0x00897680
void  __fastcall Scroll_Begin(void* self, int);                  // 0x0089d9a0
void  __fastcall Scroll_Stop(void* self, int, int);              // 0x0089c5d0
void  __fastcall Scroll_End(void* self, int, int);               // 0x0089cdf0
void  __fastcall Scroll_BaseCtor(void* self, int, int);          // 0x0089d820
int   __fastcall Scroll_ContentSize(void* self, int);            // 0x00897690
void  __fastcall RectHitTest(void* node, int, float a, float b, void* out,
                             int c, int d);                      // 0x008e69b0
void* __fastcall Page_Rect(void* rootStyle, int, float x, float y, float a, int b,
                           int c, int d, void* out);             // 0x00897e00

// float identity / rounding helpers (x87 double round-trips)
float __cdecl DblToFlt(double v);                                // 0x013cc4bc
float __cdecl RoundF(double v);                                  // 0x011e0906

// ---- PickingContext ----
class PickingContext { public:                     // 0xb84
    int      mVtbl0000;                     // +0x0000
    uint32_t mPad04[8];                     // +0x0004
    void*    mpNode24;                      // +0x0024
    uint32_t mPad28[5];                     // +0x0028
    void*    mpLayout3c;                    // +0x003c
    int      mVal40;                        // +0x0040
    TranslationVector mBlocks44;            // +0x0044
    uint32_t mPad58[(0x264 - 0x58) / 4];
    int      mVal264;                       // +0x0264
    uint32_t mPad268[(0x530 - 0x268) / 4];
    float    mX530;                         // +0x0530
    float    mY534;                         // +0x0534
    float    mX538;                         // +0x0538
    float    mY53c;                         // +0x053c
    int      mVal540;                       // +0x0540
    float    mX544;                         // +0x0544
    float    mY548;                         // +0x0548
    float    mW54c;                         // +0x054c
    float    mH550;                         // +0x0550
    float    mMarginX554;                   // +0x0554
    float    mMarginY558;                   // +0x0558
    float    mExtra55c;                     // +0x055c
    int      mCount560;                     // +0x0560
    TranslationEntry* mVecBegin564;         // +0x0564
    TranslationEntry* mVecEnd568;           // +0x0568
    TranslationEntry* mVecCap56c;           // +0x056c
    uint32_t mPad570;                       // +0x0570
    void*    mpInline574;                   // +0x0574
    uint32_t mPad578[(0xb7c - 0x578) / 4];
    FloatEntry* mpFloatHeadB7c;             // +0x0b7c
    FloatEntry* mpFloatTailB80;             // +0x0b80

    PickingContext(const Vec2* screenRect);
    PickingContext(const PickingContext& src);
    void RefreshMargins();
    void SetContextRect(const float* rect);
    void SetContextRectRelative(float x0, float y0, float x1, float y1);
    void PlaceFloat(FloatEntry* entry);
    TranslationEntry* lower_bound(TranslationEntry* first, TranslationEntry* last,
                                  const int* value);
    char Flush(void* arg);
    char FlushAll(void* arg);
    char PickTextItem(void* item, int a, int b);
};

// ---- RenderingContext (its PickingContext fields share the same offsets) ----
class RenderingContext { public:
    ScrollInfo* mpScroll00;                 // +0x0000
    uint32_t mPad04[8];                     // +0x0004
    void*    mpNode24;                      // +0x0024
    uint32_t mPad28[5];                     // +0x0028
    void*    mpLayout3c;                    // +0x003c
    int      mVal40;                        // +0x0040
    TranslationVector mBlocks44;            // +0x0044
    uint32_t mPad58[(0x264 - 0x58) / 4];
    int      mVal264;                       // +0x0264
    uint32_t mPad268[(0x530 - 0x268) / 4];
    float    mX530;                         // +0x0530
    float    mY534;                         // +0x0534
    float    mX538;                         // +0x0538
    float    mY53c;                         // +0x053c
    int      mVal540;                       // +0x0540
    float    mX544;                         // +0x0544
    float    mY548;                         // +0x0548
    float    mW54c;                         // +0x054c
    float    mH550;                         // +0x0550
    float    mMarginX554;                   // +0x0554
    float    mMarginY558;                   // +0x0558
    float    mExtra55c;                     // +0x055c
    int      mCount560;                     // +0x0560
    TranslationEntry* mVecBegin564;         // +0x0564
    TranslationEntry* mVecEnd568;           // +0x0568
    TranslationEntry* mVecCap56c;           // +0x056c
    uint32_t mPad570;                       // +0x0570
    void*    mpInline574;                   // +0x0574
    uint32_t mPad578[(0xb7c - 0x578) / 4];
    FloatEntry* mpFloatHeadB7c;             // +0x0b7c
    FloatEntry* mpFloatTailB80;             // +0x0b80

    RenderingContext(void* scroll, const float* screenRect, const float* marginRect);
    RenderingContext(const RenderingContext& src);
    char Place(void* item, int a, int b);
    void RefreshMargins();
    int TestRect(float x0, float y0, float x1, float y1);
    void ScrollViewport(float x0, float y0, float x1, float y1);
    void ScrollRect(float x0, float y0, float x1, float y1);
    void SubStyleSet(void* a, void* b);          // 0x008ee720 (uses this+4)
    void SubStyleSetValue(const Vec2* value);    // 0x008ee740 (uses this+4)
    void SubStyleGet(Vec2* out);                 // 0x008ee770 (uses this+4)
    void ReleaseScroll();                        // 0x008ee7a0 (uses *(this))
};

// ---- Page ----
class Page { public:
    uint32_t mPad00[0x24 / 4];
    void*    mpNode24;                      // +0x24
    uint32_t mPad28[(0x3c - 0x28) / 4];
    void*    mpLayout3c;                    // +0x3c
    int      mVal40;                        // +0x40
    TranslationVector mBlocks44;            // +0x44
    uint32_t mPad58[(0x260 - 0x58) / 4];
    int      mVal260;                       // +0x260
    int      mVal264;                       // +0x264
    int      mVal268;                       // +0x268

    void CreatePageLayout();
    void SetDocument(void* document);
};

}  // namespace Layout
}  // namespace XHTML
}  // namespace EA

using namespace EA::XHTML::Layout;

// ============================ function bodies ============================

// @ 0x008edc30
void Page::CreatePageLayout()
{
    if (mpLayout3c)
        return;
    void* layout = Page_CreatePageLayout(mpNode24, 0);
    if (!layout)
        return;
    char stack[0x450];
    PageLayoutCtor(stack, this);
    mVal40 = 0;
    mVal268 = 0;
    mpLayout3c = PageLayout_Build(this, layout, stack, 1);
    PageLayoutDtor(stack);
}

// @ 0x008edc90
void Page::SetDocument(void* document)
{
    if (mpNode24 == document)
        return;
    Page_Reset(this, 0);
    Page_DestroyLayout(this, 0, mpLayout3c);
    ScrollVectorClear(mBlocks44.mpBegin, mBlocks44.mpEnd);
    Node_SetFlag(this, 0, 0);
    void* old = mpNode24;
    if (document != old) {
        if (document)
            (*(void(__thiscall**)(void*))(*(int*)document))(document);   // AddRef
        mpNode24 = document;
        if (old)
            (*(void(__thiscall**)(void*))(*(int*)old + 4))(old);    // Release
    }
    mpLayout3c = 0;
    mVal260 = 0;
    mVal264 = 0;
    if (mpNode24 && !Document_Destroy(mpNode24, 0, 1))
        CreatePageLayout();
}

// @ 0x008edd30
void* __stdcall StyleCtorForward(void* self, void* rect)
{
    return StyleCtor(self, 0, rect, 0, 0);
}

// @ 0x008edd50
void __stdcall ScrollbarStyleSet(const Vec2* value)
{
    char* p = (char*)ScrollAppGet() + 0xf8;
    *(int*)(p + 0x250) = *(int*)&value->x;
    *(int*)(p + 0x244) = *(int*)&value->y;
}

// @ 0x008edd80
void __stdcall ScrollbarStyleGet(Vec2* out)
{
    char* p = (char*)ScrollAppGet();
    int a = *(int*)(p + 0x348);
    p += 0xf8;
    *(int*)&out->x = a;
    *(int*)&out->y = *(int*)(p + 0x244);
}

// @ 0x008eddb0
void PickingContext::RefreshMargins()
{
    float base = mX544;
    mMarginY558 = mW54c;
    FloatEntry* e = mpFloatHeadB7c;
    if (!e)
        return;
    do {
        if (e->mKind == 1) {
            float v = e->mSizeOther + base;
            mMarginX554 = (v > mMarginX554) ? v : mMarginX554;
        } else {
            float v = e->mSizeBig + base;
            mMarginY558 = (v > mMarginY558) ? v : mMarginY558;
        }
        e = e->mpNext;
    } while (e);
}

// @ 0x008ede40
void PickingContext::SetContextRect(const float* rect)
{
    mX544 = rect[0];
    mY548 = rect[1];
    mW54c = rect[2];
    mH550 = rect[3];
    RefreshMargins();
    mX538 = mX530 - mX544;
    mY53c = mY534 - mY548;
}

// @ 0x008edeb0
void PickingContext::SetContextRectRelative(float x0, float y0, float x1, float y1)
{
    float bx = mX544;
    float by = mY548;
    mX544 = x0 + bx;
    mY548 = y0 + by;
    mW54c = x1 + bx;
    mH550 = y1 + by;
    RefreshMargins();
    mX538 = mX530 - mX544;
    mY53c = mY534 - mY548;
}

// @ 0x008edf60
void PickingContext::PlaceFloat(FloatEntry* entry)
{
    FloatEntry** head = &mpFloatHeadB7c;
    entry->mpNext = 0;
    if (*head == 0) {
        *head = entry;
    } else {
        mpFloatTailB80->mpNext = entry;
    }
    mpFloatTailB80 = entry;
    while (*head) {
        FloatEntry* e = *head;
        if (mY548 + mExtra55c >= e->mMaxY)
            *head = e->mpNext;
        else
            head = &e->mpNext;
    }
    RefreshMargins();
}

// @ 0x008edfc0
TranslationEntry* PickingContext::lower_bound(TranslationEntry* first, TranslationEntry* last,
                                              const int* value)
{
    int count = (int)((char*)last - (char*)first) / (int)sizeof(TranslationEntry);
    int want = *value;
    while (count > 0) {
        int half = count >> 1;
        TranslationEntry* mid = first + half;
        if (mid->mExtra < want) {
            first = mid + 1;
            count += ~half;
        } else {
            count = half;
        }
    }
    return first;
}

// @ 0x008ee010
char PickingContext::Flush(void* arg)
{
    ScrollGlobalList(this);
    Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
    if (Scroll_GetState(this, 0) != 1)
        return 0;
    for (;;) {
        Scroll_Begin(this, 0);
        float a = DblToFlt(*(double*)((char*)arg + 0xa0));
        float b = RoundF(*(double*)((char*)arg + 0xa4));
        float newExtra = mExtra55c + (a - b);
        if (mY53c < 0.0f || newExtra > mY53c) {
            mExtra55c = newExtra;
            mCount560 += (*(int*)((char*)arg + 8) - *(int*)((char*)arg + 4)) >> 1;
            FloatEntry** head = &mpFloatHeadB7c;
            char changed = 0;
            while (*head) {
                FloatEntry* e = *head;
                if (mY548 + mExtra55c >= e->mMaxY) {
                    *head = e->mpNext;
                    changed = 1;
                } else {
                    head = &e->mpNext;
                }
            }
            if (changed)
                RefreshMargins();
            Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
            Scroll_Stop(this, 0, 0);
            if (Scroll_GetState(this, 0) == 1)
                continue;
            return 0;
        }
        {
            float local = mExtra55c;
            int r = *(int*)Page_Rect(arg, 0, mX530, mY53c, 0, 1, 0, 0, &local);
            int n = (mVecEnd568 - mVecBegin564) / 3;
            if (n == 0)
                return 0;
            int key = mCount560 + r + 1;
            TranslationEntry* it = lower_bound(mVecBegin564, mVecEnd568, &key);
            int base = mCount560;
            int v = it[-1].mIndex - it[-1].mExtra;
            RectHitTest(*(void**)((char*)arg), 0, (float)(base + v + r), 0.0f, 0, 0, 0);
            return 1;
        }
    }
}

// @ 0x008ee240
PickingContext::PickingContext(const Vec2* screenRect)
{
    Scroll_BaseCtor(this, 0, 0);
    mX530 = screenRect->x;
    mY534 = screenRect->y;
    mX538 = screenRect->x;
    mY53c = screenRect->y;
    mVal540 = 0;
    mX544 = 0.0f;
    mY548 = 0.0f;
    mW54c = 0.0f;
    mH550 = 0.0f;
    mCount560 = 0;
    mMarginX554 = 0.0f;
    mMarginY558 = 0.0f;
    mExtra55c = 0.0f;
    mpInline574 = (char*)this + 0x57c;
    mVecEnd568 = (TranslationEntry*)mpInline574;
    mVecBegin564 = (TranslationEntry*)mpInline574;
    mVecCap56c = (TranslationEntry*)((char*)mpInline574 + 0x600);
    mpFloatHeadB7c = 0;
    mpFloatTailB80 = 0;
}

// @ 0x008ee2f0
PickingContext::PickingContext(const PickingContext& src)
{
    Scroll_BaseCtor(this, 0, 0);
    mX530 = src.mX530;
    mY534 = src.mY534;
    mX538 = src.mX530;
    mY53c = src.mY534;
    mVal540 = src.mVal540;
    mX544 = src.mX544;
    mY548 = src.mY548;
    mW54c = src.mW54c;
    mH550 = src.mH550;
    mMarginX554 = 0.0f;
    mMarginY558 = 0.0f;
    mExtra55c = 0.0f;
    mCount560 = 0;
    mpInline574 = (char*)this + 0x57c;
    mVecEnd568 = (TranslationEntry*)mpInline574;
    mVecBegin564 = (TranslationEntry*)mpInline574;
    mVecCap56c = (TranslationEntry*)((char*)mpInline574 + 0x600);
    mX538 = mX530 - mX544;
    mY53c = mY534 - mY548;
    mpFloatHeadB7c = 0;
    mpFloatTailB80 = 0;
}

// @ 0x008ee400
char PickingContext::PickTextItem(void* item, int a, int b)
{
    if ((char*)mVecEnd568 >= (char*)mVecCap56c) {
        TranslationEntry tmp;
        tmp.mValue = 0;
        tmp.mIndex = 0;
        tmp.mExtra = 0;
        StyleCopyRange(this, 0, &tmp);
    } else {
        TranslationEntry* slot = mVecEnd568;
        mVecEnd568 = slot + 1;
        if (slot) {
            slot->mValue = 0;
            slot->mIndex = 0;
            slot->mExtra = 0;
        }
    }
    TranslationEntry* e = mVecEnd568;
    e[-1].mValue = mVal540;
    e[-1].mIndex = *(int*)((char*)item + 0x14);
    e[-1].mExtra = Scroll_ContentSize(this, 0);
    StyleAssign(this, 0, (void*)a);
    StyleAssign2(this, 0, *(int*)((char*)item + 0x18), *(int*)((char*)item + 0x1c));
    (void)b;
    return (char)a;
}

// @ 0x008ee4a0
char PickingContext::FlushAll(void* arg)
{
    ScrollGlobalList(this);
    Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
    if (Scroll_GetState2(this, 0) == 2)
        goto done;
    for (;;) {
        Scroll_Begin(this, 0);
        float a = DblToFlt(*(double*)((char*)arg + 0xa0));
        float b = RoundF(*(double*)((char*)arg + 0xa4));
        float newExtra = mExtra55c + (a - b);
        if (mY53c < 0.0f || newExtra > mY53c) {
            mExtra55c = newExtra;
            mCount560 += (*(int*)((char*)arg + 8) - *(int*)((char*)arg + 4)) >> 1;
            FloatEntry** head = &mpFloatHeadB7c;
            char changed = 0;
            while (*head) {
                FloatEntry* e = *head;
                if (mY548 + mExtra55c >= e->mMaxY) {
                    *head = e->mpNext;
                    changed = 1;
                } else {
                    head = &e->mpNext;
                }
            }
            if (changed)
                RefreshMargins();
            Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
            Scroll_Stop(this, 0, 0);
            if (Scroll_GetState2(this, 0) != 2)
                continue;
            break;
        }
        float local = mExtra55c;
        int r = *(int*)Page_Rect(arg, 0, mX530, mY53c, 0, 1, 0, 0, &local);
        if ((unsigned)r >= *(unsigned*)((char*)arg + 0x90))
            break;
        int n = (mVecEnd568 - mVecBegin564) / 3;
        if (n == 0)
            break;
        int key = mCount560 + r + 1;
        TranslationEntry* it = lower_bound(mVecBegin564, mVecEnd568, &key);
        if (it == mVecBegin564)
            break;
        int base = mCount560;
        int v = it[-1].mIndex - it[-1].mExtra;
        RectHitTest(*(void**)((char*)arg), 0, (float)(base + v + r), 0.0f, 0, 0, 0);
        return 1;
    }
done:
    Scroll_End(this, 0, 1);
    ScrollVectorClear(mVecBegin564, mVecEnd568);
    mCount560 = 0;
    return 0;
}

// @ 0x008ee720
void RenderingContext::SubStyleSet(void* a, void* b)
{
    StyleCtor((char*)this + 4, 0, a, 0, 0);
    (void)b;
}

// @ 0x008ee740
void RenderingContext::SubStyleSetValue(const Vec2* value)
{
    char* p = (char*)ScrollAppGet() + 0xf8;
    *(int*)(p + 0x250) = *(int*)&value->x;
    *(int*)(p + 0x244) = *(int*)&value->y;
}

// @ 0x008ee770
void RenderingContext::SubStyleGet(Vec2* out)
{
    char* p = (char*)ScrollAppGet();
    int a = *(int*)(p + 0x348);
    p += 0xf8;
    *(int*)&out->x = a;
    *(int*)&out->y = *(int*)(p + 0x244);
}

// @ 0x008ee7a0
void RenderingContext::ReleaseScroll()
{
    ScrollInfo* s = mpScroll00;
    (*(void(__thiscall**)(ScrollInfo*))(*(int*)s + 4))(s);
}

// @ 0x008ee7b0
void RenderingContext::ScrollViewport(float a, float b, float c, float d)
{
    ScrollInfo* s = mpScroll00;
    float bX = mY534;
    float bY = mX538;
    (*(void(__thiscall**)(ScrollInfo*, float, float, float, float))(
        *(int*)s + 0x38))(s, bX + a, bY + b, bX + c, bY + d);
}

// @ 0x008ee810
RenderingContext::RenderingContext(void* scroll, const float* screenRect,
                                   const float* marginRect)
{
    mpScroll00 = (ScrollInfo*)scroll;
    Scroll_BaseCtor((char*)this + 4, 0, 0);
    mY534 = screenRect[0];
    mX538 = screenRect[1];
    mY53c = screenRect[2];
    mVal540 = (int)screenRect[3];
    mX544 = marginRect[0];
    mY548 = marginRect[1];
    mW54c = marginRect[2];
    mH550 = marginRect[3];
    mVecBegin564 = 0;
    mVecEnd568 = 0;
    mVecCap56c = 0;
    mPad570 = 0;
    mpInline574 = 0;
    mMarginX554 = 0.0f;
    mMarginY558 = 0.0f;
    mExtra55c = 0.0f;
    mCount560 = -1;
}

// @ 0x008ee8c0
RenderingContext::RenderingContext(const RenderingContext& src)
{
    mpScroll00 = src.mpScroll00;
    Scroll_BaseCtor((char*)this + 4, 0, 0);
    mY534 = src.mY534;
    mX538 = src.mX538;
    mY53c = src.mY53c;
    mVal540 = src.mVal540;
    mX544 = src.mX544;
    mY548 = src.mY548;
    mW54c = src.mW54c;
    mH550 = src.mH550;
    mVecBegin564 = 0;
    mVecEnd568 = 0;
    mVecCap56c = 0;
    mPad570 = 0;
    mpInline574 = 0;
    mMarginX554 = 0.0f;
    mMarginY558 = 0.0f;
    mExtra55c = 0.0f;
    mCount560 = -1;
}

// @ 0x008ee990
char RenderingContext::Place(void* item, int a, int b)
{
    float v[2];
    if (StyleSet(item, 0, v)) {
        int delta = Scroll_ContentSize((char*)this + 4, 0);
        int e = (int)v[0] + delta;
        int cur = mCount560;
        mCount560 = (e < cur) ? cur : e;
        int e2 = (int)v[1] + delta;
        int cur2 = (int)(size_t)mVecBegin564;
        mVecBegin564 = (TranslationEntry*)(size_t)((e2 < cur2) ? cur2 : e2);
    }
    StyleAssign((char*)this + 4, 0, (void*)a);
    StyleAssign2((char*)this + 4, 0, *(int*)((char*)item + 0x18), *(int*)((char*)item + 0x1c));
    (void)b;
    return 0;
}

// @ 0x008eea30
void RenderingContext::RefreshMargins()
{
    float base = mY534;
    mMarginY558 = mY53c;
    FloatEntry* e = mpFloatHeadB7c;
    if (!e)
        return;
    do {
        if (e->mKind == 1) {
            float v = e->mSizeOther + base;
            mMarginX554 = (v > mMarginX554) ? v : mMarginX554;
        } else {
            float v = e->mSizeBig + base;
            mMarginY558 = (v > mMarginY558) ? v : mMarginY558;
        }
        e = e->mpNext;
    } while (e);
}

// @ 0x008eeac0
int RenderingContext::TestRect(float a, float b, float c, float d)
{
    if (c + mY534 <= mX544)
        return 0;
    if (mW54c <= a + mY534)
        return 0;
    if (d + mX538 <= mY548)
        return 0;
    if (mH550 <= b + mX538)
        return 0;
    return 1;
}

// @ 0x008eeb30
void RenderingContext::ScrollRect(float a, float b, float c, float d)
{
    float bX = mY534;
    float bY = mX538;
    ScrollInfo* s = mpScroll00;
    (*(void(__thiscall**)(ScrollInfo*, float, float, float, float))(
        *(int*)s + 0x38))(s, a + bX, b + bY, c + bX, d + bY);
}
