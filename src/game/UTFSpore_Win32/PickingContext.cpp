// src/game/UTFSpore_Win32/PickingContext.cpp -- migrated from slice(s) s008edc30 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/PickingContext.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/XHTML/Layout/Page.h"
#include "EA/Text/Typesetter.h"
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s008edc30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace XHTML {
namespace Layout {
struct Vec2 {
    float x, y;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct RectF {                      // a 16-byte float rect passed by value
    float x0, y0, x1, y1;
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
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
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct TranslationEntry {           // 0x0c
    int mValue;                     // +0x00
    int mIndex;                     // +0x04
    int mExtra;                     // +0x08
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
struct TranslationVector {          // eastl vector<TranslationEntry>, 0x14
    TranslationEntry* mpBegin;      // +0x00
    TranslationEntry* mpEnd;        // +0x04
    TranslationEntry* mpCapacity;   // +0x08
    uint32_t mAllocator[2];         // +0x0c
};
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __cdecl ScrollVectorClear(void* a, void* b);               // 0x00e25bd0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall StyleAssign(void* self, int, void* v);          // 0x0089b360
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall StyleAssign2(void* self, int, int a, int b);    // 0x0089b1e0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall StyleCopyRange(void* self, int, void* v);       // 0x00a27910
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void* __fastcall ScrollGlobalList(void* a);                      // 0x008976a0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall Scroll_SetViewport(void* self, int, float a, float b, float c); // 0x00897640
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
int   __fastcall Scroll_GetState(void* self, int);               // 0x0089cf10
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
int   __fastcall Scroll_GetState2(void* self, int);              // 0x00897680
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall Scroll_Begin(void* self, int);                  // 0x0089d9a0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall Scroll_Stop(void* self, int, int);              // 0x0089c5d0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall Scroll_End(void* self, int, int);               // 0x0089cdf0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall Scroll_BaseCtor(void* self, int, int);          // 0x0089d820
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
int   __fastcall Scroll_ContentSize(void* self, int);            // 0x00897690
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void  __fastcall RectHitTest(void* node, int, float a, float b, void* out,
                             int c, int d);                      // 0x008e69b0
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
void* __fastcall Page_Rect(void* rootStyle, int, float x, float y, float a, int b,
                           int c, int d, void* out);             // 0x00897e00
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
float __cdecl DblToFlt(double v);                                // 0x013cc4bc
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
float __cdecl RoundF(double v);                                  // 0x011e0906
}
}
}
namespace EA {
namespace XHTML {
namespace Layout {
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
    void SetContextRectRelative(RectF r);
    void PlaceFloat(FloatEntry* entry);
    static TranslationEntry* lower_bound(TranslationEntry* first, TranslationEntry* last,
                                         const int* value);
    char Flush(void* arg);
    char FlushAll(void* arg);
    char PickTextItem(void* item, int a, int b);
};
}
}
}
template <typename T> inline const T& tmax(const T& a, const T& b) { return (a < b) ? b : a; }
// ---- items of slice s008edc30 end

// @ 0x008eddb0
void EA::XHTML::Layout::PickingContext::RefreshMargins()
{
    mMarginX554 = mX544;
    mMarginY558 = mW54c;
    EA::XHTML::Layout::FloatEntry* e = mpFloatHeadB7c;
    while (e) {
        if (e->mKind == 1) {
            float v = e->mSizeOther + mX544;
            mMarginX554 = tmax(mMarginX554, v);
        } else {
            float v = e->mSizeBig + mX544;
            mMarginY558 = tmax(mMarginY558, v);
        }
        e = e->mpNext;
    }
}

// @ 0x008ede40
void EA::XHTML::Layout::PickingContext::SetContextRect(const float* rect)
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
void EA::XHTML::Layout::PickingContext::SetContextRectRelative(EA::XHTML::Layout::RectF r)
{
    r.x0 += mX544;
    r.y0 += mY548;
    r.x1 += mX544;
    r.y1 += mY548;
    mX544 = r.x0;
    mY548 = r.y0;
    mW54c = r.x1;
    mH550 = r.y1;
    RefreshMargins();
    mX538 = mX530 - mX544;
    mY53c = mY534 - mY548;
}

// @ 0x008edf60
void EA::XHTML::Layout::PickingContext::PlaceFloat(EA::XHTML::Layout::FloatEntry* entry)
{
    EA::XHTML::Layout::FloatEntry** head = &mpFloatHeadB7c;
    entry->mpNext = 0;
    if (*head == 0) {
        *head = entry;
    } else {
        mpFloatTailB80->mpNext = entry;
    }
    mpFloatTailB80 = entry;
    while (*head) {
        EA::XHTML::Layout::FloatEntry* e = *head;
        float y = mExtra55c;
        y += mY548;
        if (y >= e->mMaxY)
            *head = e->mpNext;
        else
            head = &e->mpNext;
    }
    RefreshMargins();
}

// @ 0x008edfc0
EA::XHTML::Layout::TranslationEntry* EA::XHTML::Layout::PickingContext::lower_bound(EA::XHTML::Layout::TranslationEntry* first, EA::XHTML::Layout::TranslationEntry* last, const int* value)
{
    int count = (int)((char*)last - (char*)first) / (int)sizeof(EA::XHTML::Layout::TranslationEntry);
    while (count > 0) {
        int half = count >> 1;
        EA::XHTML::Layout::TranslationEntry* mid = first + half;
        if ((unsigned int)mid->mExtra < (unsigned int)*value) {
            first = mid + 1;
            count -= half + 1;
        } else {
            count = half;
        }
    }
    return first;
}

// @ 0x008ee010
char EA::XHTML::Layout::PickingContext::Flush(void* arg)
{
    EA::XHTML::Layout::ScrollGlobalList(this);
    EA::XHTML::Layout::Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
    if (EA::XHTML::Layout::Scroll_GetState(this, 0) != 1)
        return 0;
    for (;;) {
        EA::XHTML::Layout::Scroll_Begin(this, 0);
        float a = EA::XHTML::Layout::DblToFlt(*(double*)((char*)arg + 0xa0));
        float b = EA::XHTML::Layout::RoundF(*(double*)((char*)arg + 0xa4));
        float newExtra = mExtra55c + (a - b);
        if (mY53c < 0.0f || newExtra > mY53c) {
            mExtra55c = newExtra;
            mCount560 += (*(int*)((char*)arg + 8) - *(int*)((char*)arg + 4)) >> 1;
            EA::XHTML::Layout::FloatEntry** head = &mpFloatHeadB7c;
            char changed = 0;
            while (*head) {
                EA::XHTML::Layout::FloatEntry* e = *head;
                if (mY548 + mExtra55c >= e->mMaxY) {
                    *head = e->mpNext;
                    changed = 1;
                } else {
                    head = &e->mpNext;
                }
            }
            if (changed)
                RefreshMargins();
            EA::XHTML::Layout::Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
            EA::XHTML::Layout::Scroll_Stop(this, 0, 0);
            if (EA::XHTML::Layout::Scroll_GetState(this, 0) == 1)
                continue;
            return 0;
        }
        {
            float local = mExtra55c;
            int r = *(int*)EA::XHTML::Layout::Page_Rect(arg, 0, mX530, mY53c, 0, 1, 0, 0, &local);
            int n = (mVecEnd568 - mVecBegin564) / 3;
            if (n == 0)
                return 0;
            int key = mCount560 + r + 1;
            EA::XHTML::Layout::TranslationEntry* it = lower_bound(mVecBegin564, mVecEnd568, &key);
            int base = mCount560;
            int v = it[-1].mIndex - it[-1].mExtra;
            EA::XHTML::Layout::RectHitTest(*(void**)((char*)arg), 0, (float)(base + v + r), 0.0f, 0, 0, 0);
            return 1;
        }
    }
}

// @ 0x008ee240
EA::XHTML::Layout::PickingContext::PickingContext(const EA::XHTML::Layout::Vec2* screenRect)
{
    EA::XHTML::Layout::Scroll_BaseCtor(this, 0, 0);
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
    mVecEnd568 = (EA::XHTML::Layout::TranslationEntry*)mpInline574;
    mVecBegin564 = (EA::XHTML::Layout::TranslationEntry*)mpInline574;
    mVecCap56c = (EA::XHTML::Layout::TranslationEntry*)((char*)mpInline574 + 0x600);
    mpFloatHeadB7c = 0;
    mpFloatTailB80 = 0;
}

// @ 0x008ee2f0
EA::XHTML::Layout::PickingContext::PickingContext(const EA::XHTML::Layout::PickingContext& src)
{
    EA::XHTML::Layout::Scroll_BaseCtor(this, 0, 0);
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
    mVecEnd568 = (EA::XHTML::Layout::TranslationEntry*)mpInline574;
    mVecBegin564 = (EA::XHTML::Layout::TranslationEntry*)mpInline574;
    mVecCap56c = (EA::XHTML::Layout::TranslationEntry*)((char*)mpInline574 + 0x600);
    mX538 = mX530 - mX544;
    mY53c = mY534 - mY548;
    mpFloatHeadB7c = 0;
    mpFloatTailB80 = 0;
}

// @ 0x008ee400
char EA::XHTML::Layout::PickingContext::PickTextItem(void* item, int a, int b)
{
    if ((char*)mVecEnd568 >= (char*)mVecCap56c) {
        EA::XHTML::Layout::TranslationEntry tmp;
        tmp.mValue = 0;
        tmp.mIndex = 0;
        tmp.mExtra = 0;
        EA::XHTML::Layout::StyleCopyRange(this, 0, &tmp);
    } else {
        EA::XHTML::Layout::TranslationEntry* slot = mVecEnd568;
        mVecEnd568 = slot + 1;
        if (slot) {
            slot->mValue = 0;
            slot->mIndex = 0;
            slot->mExtra = 0;
        }
    }
    EA::XHTML::Layout::TranslationEntry* e = mVecEnd568;
    e[-1].mValue = mVal540;
    e[-1].mIndex = *(int*)((char*)item + 0x14);
    e[-1].mExtra = EA::XHTML::Layout::Scroll_ContentSize(this, 0);
    EA::XHTML::Layout::StyleAssign(this, 0, (void*)a);
    EA::XHTML::Layout::StyleAssign2(this, 0, *(int*)((char*)item + 0x18), *(int*)((char*)item + 0x1c));
    (void)b;
    return (char)a;
}

// @ 0x008ee4a0
char EA::XHTML::Layout::PickingContext::FlushAll(void* arg)
{
    EA::XHTML::Layout::ScrollGlobalList(this);
    EA::XHTML::Layout::Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
    if (EA::XHTML::Layout::Scroll_GetState2(this, 0) == 2)
        goto done;
    for (;;) {
        EA::XHTML::Layout::Scroll_Begin(this, 0);
        float a = EA::XHTML::Layout::DblToFlt(*(double*)((char*)arg + 0xa0));
        float b = EA::XHTML::Layout::RoundF(*(double*)((char*)arg + 0xa4));
        float newExtra = mExtra55c + (a - b);
        if (mY53c < 0.0f || newExtra > mY53c) {
            mExtra55c = newExtra;
            mCount560 += (*(int*)((char*)arg + 8) - *(int*)((char*)arg + 4)) >> 1;
            EA::XHTML::Layout::FloatEntry** head = &mpFloatHeadB7c;
            char changed = 0;
            while (*head) {
                EA::XHTML::Layout::FloatEntry* e = *head;
                if (mY548 + mExtra55c >= e->mMaxY) {
                    *head = e->mpNext;
                    changed = 1;
                } else {
                    head = &e->mpNext;
                }
            }
            if (changed)
                RefreshMargins();
            EA::XHTML::Layout::Scroll_SetViewport(this, 0, mExtra55c, mW54c, mMarginY558 - mMarginX554);
            EA::XHTML::Layout::Scroll_Stop(this, 0, 0);
            if (EA::XHTML::Layout::Scroll_GetState2(this, 0) != 2)
                continue;
            break;
        }
        float local = mExtra55c;
        int r = *(int*)EA::XHTML::Layout::Page_Rect(arg, 0, mX530, mY53c, 0, 1, 0, 0, &local);
        if ((unsigned)r >= *(unsigned*)((char*)arg + 0x90))
            break;
        int n = (mVecEnd568 - mVecBegin564) / 3;
        if (n == 0)
            break;
        int key = mCount560 + r + 1;
        EA::XHTML::Layout::TranslationEntry* it = lower_bound(mVecBegin564, mVecEnd568, &key);
        if (it == mVecBegin564)
            break;
        int base = mCount560;
        int v = it[-1].mIndex - it[-1].mExtra;
        EA::XHTML::Layout::RectHitTest(*(void**)((char*)arg), 0, (float)(base + v + r), 0.0f, 0, 0, 0);
        return 1;
    }
done:
    EA::XHTML::Layout::Scroll_End(this, 0, 1);
    EA::XHTML::Layout::ScrollVectorClear(mVecBegin564, mVecEnd568);
    mCount560 = 0;
    return 0;
}
