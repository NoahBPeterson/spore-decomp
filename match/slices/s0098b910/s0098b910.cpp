// UTFWinControls::WinTextEdit undo/redo list management, paragraph lookup and lifecycle
// (0x98b910-0x98c860).
//
// Retail layout (established by neighbouring slices s00989870 / s0098a820):
//   Window occupies 0x20c bytes: text buffer begin/end live at +0x0b0/+0x0b4.
//   The IWinTextEdit subobject is a secondary base at +0x20c.  For an interface method
//   `this` is window+0x20c and the owning window is `this - 0x20c`; conversely a window
//   method reaches its interface through `window + 0x20c`.
//   Paragraph stride is 0x18 bytes.  The undo/redo deques use 0x100-byte blocks holding
//   0x40 pointers, matching eastl::deque<t*, allocator, 64>.
#include "types.h"

#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])
#define WIN(iface) ((WinTextEdit*)((char*)(iface) - 0x20c))

extern "C" void* __cdecl memcpy(void*, const void*, size_t);

void* operator_new(size_t size, const char* name, int flags, unsigned dbgFlags, const char* file, int line);  // 00F473A0
void operator_delete__(void* p);                                                                              // 00F47380

namespace EA { namespace UTFWinControls {

class WinTextEdit;
class IWinTextEdit;

// ---------------------------------------------------------------- shared helpers

// eastl::upper_bound instantiations live in slice s0098a820 (0x98b650 / 0x98b6b0); they
// are redeclared here so this translation unit can call them by their retail addresses.
struct Paragraph {
    uint32_t textIndex;                         // +0x00
    uint32_t textLength;                        // +0x04
    int      textLines;                         // +0x08
    float    extentX;                           // +0x0c
    float    extentY;                           // +0x10
    float    yPos;                              // +0x14
};
const Paragraph* UpperBoundByY(const Paragraph* first, const Paragraph* last, const float& v);       // 0098B650
struct TextIndexComparator {
    char dummy;                                  // empty functor; 1 byte, passed as a 4-byte value
    bool operator()(unsigned i, const Paragraph& p) const { return i < p.textIndex; }
};
const Paragraph* UpperBoundByIndex(const Paragraph* first, const Paragraph* last, const unsigned& v); // 0098B6B0
// Same instantiation reached with the (empty) comparator materialised on the stack by the caller.
const Paragraph* UpperBoundByIndexC(const Paragraph* first, const Paragraph* last, const unsigned& v,
                                    TextIndexComparator c);                                          // 0098B6B0

// cDropShadowDescriptor lives at window+0x624; SetMode1/SetMode2 are its only used methods.
struct cDropShadowDescriptor {
    uint32_t m2;                                // +0x00 (mode 1)
    uint32_t m6;                                // +0x04 (mode 2)
    void SetMode1(int v);                       // 00830280
    void SetMode2(int v);                       // 00830150
};

// eastl::deque<void*, allocator, 64>; the iterator and DequeBase live in the same namespace
// as WinTextEdit in the retail build.
struct DequeIterator {
    void**   mpCurrent;                         // +0x00
    void**   mpBegin;                           // +0x04
    void**   mpEnd;                             // +0x08
    void***  mpCurrentArrayPtr;                 // +0x0c
};

struct DequeBase {
    void***  mpPtrArray;                        // +0x00
    unsigned mnPtrArraySize;                    // +0x04
    DequeIterator mItBegin;                     // +0x08
    DequeIterator mItEnd;                       // +0x18
    uint8_t  pad[4];                            // +0x28 (instanced allocator tail)
    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(unsigned nAdditionalCapacity, Side allocationSide);   // 0x98b700
    void push_back(void* const& value);                                          // 0x98bb60
};

long DequeSize(const DequeBase& d) {
    const char* a = (const char*)d.mItEnd.mpCurrentArrayPtr;
    const char* b = (const char*)d.mItBegin.mpCurrentArrayPtr;
    return (((long)(a - b) >> 2) - 1) * 0x40 +
           ((long)((const char*)d.mItEnd.mpCurrent   - (const char*)d.mItEnd.mpBegin)   >> 2) +
           ((long)((const char*)d.mItBegin.mpEnd     - (const char*)d.mItBegin.mpCurrent) >> 2);
}

// EA::UTFWinControls::WinTextEdit::UndoAction, 0x34 bytes:
//   +0x00 uint index
//   +0x04 string newText (begin,end,capacity)
//   +0x14 string oldText
//   +0x24 oldCursorIndex
//   +0x28 oldAnchorIndex
//   +0x2c newCursorIndex
//   +0x30 newAnchorIndex
// eastl::vector<Paragraph, allocator>; 0x98bfc0 is its insert().
struct ParagraphVector {
    Paragraph* mpBegin;                         // +0x00
    Paragraph* mpEnd;                           // +0x04
    Paragraph* mpCap;                           // +0x08
    void insert(Paragraph* pos, const Paragraph& value);      // 0098BFC0
    void reserve(unsigned n);                                 // 0098BAB0
};

struct UndoAction {
    uint32_t index;                             // +0x00
    uint32_t nB, nE, nC;                        // +0x04 newText
    uint32_t oB, oE, oC;                        // +0x14 oldText
    uint32_t oldCursorIndex;                    // +0x24
    uint32_t oldAnchorIndex;                    // +0x28
    uint32_t newCursorIndex;                    // +0x2c
    uint32_t newAnchorIndex;                    // +0x30
    UndoAction* scalar_deleting_destructor(unsigned flags);    // 0098BC20
};

// Retail thiscall helpers, declared as members of a dummy struct so the compiler passes
// `self` in ecx (and nothing extra in edx).
struct WindowBase {
    void Ctor();                                    // 00962A10
    void Shutdown();                                // 00961E80
    void SetFlag(unsigned flag, char on);           // 00961760
    void SetCursor(unsigned id);                    // 00960020
    void SerUpdate();                               // 009614A0
};
struct StopwatchBase {
    void Ctor(int units, char a);                   // 0093A560
};
struct TextStyleBase {
    void Ctor();                                    // 008941D0
};
void FUN_0098b830(WinTextEdit* self, int a);                    // 0098B830
void FUN_0098a090(WinTextEdit* self, int flag);                 // 0098A090  (scrollbar slot rebuild)
void FUN_009899b0(WinTextEdit* self);                           // 009899B0
void WinText_Error(WinTextEdit* self, unsigned code);           // 00989240
char WinTextEdit_ValidateChange(WinTextEdit* self);             // 00989A90

#define WND(self)  ((WindowBase*)(self))
#define SW(self)   ((StopwatchBase*)(self))
#define TS(self)   ((TextStyleBase*)(self))
// EASTL paragraph-vector relocation helpers.
void* ParagraphRelocate(const void* first, const void* last, void* dst);   // 00989740
void  ParagraphMoveBack(const void* first, const void* last, void* dst);   // 009897D0
// eastl::basic_string<wchar_t>::assign / replace (__thiscall: the string object is `self`,
// passed in ecx; the second fastcall slot is unused).
void __fastcall WString_Assign(void* self, void*, const wchar_t* first, const wchar_t* last);   // 00423650
void __fastcall WString_Replace(void* self, void*, const wchar_t* first, const wchar_t* last,
                                const wchar_t* srcFirst, const wchar_t* srcLast);               // 005F8400
// Allocation.
void* EAAllocate(unsigned size, const char* name, int a, int b, const char* file, int line);  // 00F473A0

extern "C" __declspec(dllimport) unsigned __stdcall GetDoubleClickTime(void);   // USER32

__declspec(dllimport) float g_DefaultSpacing4;       // 0x14853E0  (4.0f)
__declspec(dllimport) float g_StopwatchUnitScale;    // 0x13EB8A0
__declspec(dllimport) float g_DoubleClickScale;      // 0x1471064
__declspec(dllimport) float g_MillisToSeconds;       // 0x13F9428
__declspec(dllimport) float g_UIntToFloatBias;       // 0x13F4FD0  (4294967296.0f)

// eastl::gEmptyString16 is the in-place SSO buffer used to initialise the UndoAction
// strings before any allocation: begin=+0, capacity=+2.
wchar_t g_EmptyString16[2];                          // 0x1667BAC

// ---------------------------------------------------------------- WinTextEdit layout
//
// Offsets used by this slice:
//   +0x0b0/+0x0b4  text buffer begin/end
//   +0x210         bool flag cleared by Shutdown
//   +0x214         window flags
//   +0x218         serialization-dirty flags
//   +0x234/+0x23c  visible-area top/bottom (float)
//   +0x244..+0x260 mColors[8]
//   +0x264         maxTextLength
//   +0x268/+0x26c  cursor / anchor
//   +0x27c..+0x284 paragraph vector begin/end/capacity
//   +0x290         inline EA::Text::TextStyle (0x278 bytes)
//   +0x318         mUndoHistorySize
//   +0x520         vertical-alignment mode
//   +0x530         mUndoList deque (0x2c bytes)
//   +0x55c         mRedoList deque (0x2c bytes)
class WinTextEdit { public:
    uint8_t  w00[0x0b0];
    wchar_t* textBegin;                         // +0x0b0
    wchar_t* textEnd;                           // +0x0b4
    uint8_t  wB8[0x210 - 0xb8];
    uint8_t  flag210;                           // +0x210
    uint8_t  w211[3];
    uint32_t flags;                             // +0x214
    uint32_t dirty;                             // +0x218
    uint8_t  w21C[0x234 - 0x21c];
    float    areaTop;                           // +0x234
    uint8_t  w238[0x23c - 0x238];
    float    areaBottom;                        // +0x23c
    uint8_t  w240[0x244 - 0x240];
    uint32_t colors[8];                         // +0x244
    uint32_t maxTextLength;                     // +0x264
    int      cursor;                            // +0x268
    int      anchor;                            // +0x26c
    uint8_t  w270[0x27c - 0x270];
    ParagraphVector paragraphs;                 // +0x27c
    uint8_t  w288[0x520 - 0x288];
    uint32_t valignMode;                        // +0x520
    uint32_t undoHistorySize;                   // +0x524
    DequeBase undoList;                         // +0x528..+0x553 (deque<void*,allocator,64> + 4B tail)
    DequeBase redoList;                         // +0x554..+0x57f
    void*    scrollH;                           // +0x580
    void*    scrollHDrawable;                   // +0x584
    void*    scrollV;                           // +0x588
    void*    scrollVDrawable;                   // +0x58c
    uint8_t  wd1[0x594 - 0x590];                // +0x590
    void*    extentDrawableA;                   // +0x594
    void*    extentDrawableB;                   // +0x598
    void*    ptr59c;                            // +0x59c
    uint8_t  w5A0[0x5a8 - 0x5a0];
    float    textExtentX;                       // +0x5a8
    float    textExtentY;                       // +0x5ac
    float    f5b0;                              // +0x5b0
    float    f5b4;                              // +0x5b4
    uint8_t  stopwatchA[0x20];                  // +0x5b8
    float    f5d0;                              // +0x5d0
    uint8_t  stopwatchB[0x20];                  // +0x5d8
    float    f5f0, f5f4, f5f8, f5fc;            // +0x5f0
    uint8_t  bool600;                           // +0x600
    uint8_t  w601[0x608 - 0x601];
    uint8_t  stopwatchC[0x20];                  // +0x608
    float    doubleClickInterval;               // +0x620
    cDropShadowDescriptor dropShadow;           // +0x624
    uint8_t  w64c;                              // +0x64c
    uint8_t  w64d[0x650 - 0x64d];
    uint32_t unk650;                            // +0x650

    unsigned TextLength() const { return (unsigned)(textEnd - textBegin); }

    // this slice
    const Paragraph* FindParagraphByTextIndex(unsigned idx);        // 0098B910
    int      GetVAlignmentOffset();                                 // 0098B940
    void     ApplyUndoRedo(UndoAction* a);                          // 0098BC80
    void     ApplyRedoUndo(UndoAction* a);                          // 0098BD00
    void     TrimUndoList(unsigned n);                              // 0098BD80
    void     TrimRedoList(unsigned n);                              // 0098BEA0
    int      Replace(void* text, unsigned a, unsigned b, unsigned c, unsigned d);  // 0098C5A0
    void     SerUpdate();                                           // 0098C4B0
    void     Shutdown();                                            // 0098C520
    WinTextEdit();                                                  // 0098C110
};

class IWinTextEdit { public:
    uint8_t  i00[0x20c];
    uint32_t flags;                             // +0x20c == window+0x214
    uint32_t dirty;                             // +0x210 == window+0x218
    void     SetUndoHistorySize(unsigned n);    // 0098C860
    int      GetText(void* out, unsigned idx, unsigned n);   // 0098BBD0
    // window fields reached through the secondary-base relationship (window+0xb0/+0xb4)
    char* TextBegin() const { return *(char**)((char*)this - 0x15c); }
    char* TextEnd()   const { return *(char**)((char*)this - 0x158); }
};

}}  // namespace EA::UTFWinControls

using namespace EA::UTFWinControls;


namespace EA { namespace UTFWinControls {

// ============================================================ 0x98b910
// @ 0x98b910
const Paragraph* WinTextEdit::FindParagraphByTextIndex(unsigned idx) {
    TextIndexComparator cmp = { 0 };
    return (const Paragraph*)((const char*)UpperBoundByIndexC(paragraphs.mpBegin, paragraphs.mpEnd, idx, cmp) - 0x18);
}

// ============================================================ 0x98b940
// @ 0x98b940
int WinTextEdit::GetVAlignmentOffset() {
    float base = textExtentY;
    const Paragraph* first = UpperBoundByY(paragraphs.mpBegin, paragraphs.mpEnd, base);
    float target = (areaBottom - areaTop) + base;
    const Paragraph* last = UpperBoundByY(paragraphs.mpBegin, paragraphs.mpEnd, target);

    float acc = 0.0f;
    for (const Paragraph* p = (const Paragraph*)((const char*)first - 0x18); p != last;
         p = (const Paragraph*)((const char*)p + 0x18)) {
        if (acc != p->yPos) acc = (p->yPos - acc) + acc;
        acc = p->extentY + acc;
    }

    if (acc <= (areaBottom - areaTop) ||
        ((unsigned)(((const char*)last - (const char*)first) / 0x18) == 1 &&
         ((const Paragraph*)((const char*)first - 0x18))->textLines == 1)) {
        if (valignMode == 1) return (unsigned)(((areaBottom - areaTop) - acc) * 0.5f);
        if (valignMode == 2) return (unsigned)((areaBottom - areaTop) - acc);
    }
    return (unsigned)acc;
}

// ============================================================ 0x98bab0
// @ 0x98bab0
void ParagraphVector::reserve(unsigned n) {
    if ((unsigned)(((char*)mpCap - (char*)mpBegin) / 0x18) < n) {
        Paragraph* mem;
        if (n == 0) {
            mem = 0;
        } else {
            mem = (Paragraph*)operator_new(n * 0x18, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        }
        ParagraphRelocate(mpBegin, mpEnd, mem);
        Paragraph* old = mpBegin;
        if (old != 0 && ((int*)old)[-1] != 0) operator_delete__(old);
        mpBegin = mem;
        mpEnd = (Paragraph*)((char*)mem + ((unsigned)((char*)mpEnd - (char*)old) / 0x18) * 0x18);
        mpCap = (Paragraph*)((char*)mem + n * 0x18);
    }
}

// ============================================================ 0x98bbd0
// @ 0x98bbd0
int IWinTextEdit::GetText(void* out, unsigned idx, unsigned n) {
    unsigned len = (unsigned)((TextEnd() - TextBegin()) >> 1);
    if (idx >= len) return 0;
    unsigned avail = len - idx;
    const unsigned& c = (avail < n) ? avail : n;
    const wchar_t* p = (const wchar_t*)TextBegin() + idx;
    WString_Assign(out, 0, p, p + c);
    return (int)c;
}

// ============================================================ 0x98bb60
// eastl::deque<void*, allocator, 64>::push_back (0x98bb60).
// @ 0x98bb60
void DequeBase::push_back(void* const& value) {
    void* v = value;
    if (mItBegin.mpCurrentArrayPtr == mpPtrArray)
        DoReallocPtrArray(1, kSideFront);

    char* block = (char*)operator_new(0x100, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    void*** pa = mItBegin.mpCurrentArrayPtr;
    pa[-1] = (void**)block;
    void*** np = pa - 1;
    mItBegin.mpCurrentArrayPtr = np;
    void* p = *np;
    mItBegin.mpBegin = (void**)p;
    void** e = (void**)((char*)p + 0x100);
    mItBegin.mpEnd = e;
    void** cur = e - 1;
    mItBegin.mpCurrent = cur;
    if (cur != 0)
        *cur = v;
}

// ============================================================ 0x98bc20
// @ 0x98bc20
UndoAction* UndoAction::scalar_deleting_destructor(unsigned flags) {
    uint32_t* oB = (uint32_t*)((char*)this + 0x14);
    uint32_t* nB = (uint32_t*)((char*)this + 4);
    int ocnt = (int)(oB[2] - oB[0]) & 0xfffffffe;
    if (ocnt > 2 && oB[0] != 0) operator_delete__((void*)oB[0]);
    int ncnt = (int)(nB[2] - nB[0]) & 0xfffffffe;
    if (ncnt > 2 && nB[0] != 0) operator_delete__((void*)nB[0]);
    if (flags & 1) operator_delete__(this);
    return this;
}

// ============================================================ 0x98bc80
// @ 0x98bc80
void WinTextEdit::ApplyUndoRedo(UndoAction* a) {
    uint32_t* w = (uint32_t*)a;
    uint32_t idx = w[0];
    uint32_t tail = ((textEnd - textBegin) >> 1) - idx;
    uint32_t cnt = (w[6] - w[5]) >> 1;
    const uint32_t& mn = (cnt <= tail) ? cnt : tail;
    WString_Replace((char*)this + 0xb0, 0, textBegin + idx, textBegin + (mn + idx),
                    (wchar_t*)w[1], (wchar_t*)w[2]);
    cursor = (int)w[9];
    anchor = (int)w[0xb];
}

// ============================================================ 0x98bd00
// @ 0x98bd00
void WinTextEdit::ApplyRedoUndo(UndoAction* a) {
    uint32_t* w = (uint32_t*)a;
    uint32_t idx = w[0];
    uint32_t cnt = (w[2] - w[1]) >> 1;
    uint32_t tail = ((textEnd - textBegin) >> 1) - idx;
    const uint32_t& mn = (cnt <= tail) ? cnt : tail;
    WString_Replace((char*)this + 0xb0, 0, textBegin + idx, textBegin + (mn + idx),
                    (wchar_t*)w[5], (wchar_t*)w[6]);
    cursor = (int)w[10];
    anchor = (int)w[0xc];
}

// ============================================================ 0x98bd80
// @ 0x98bd80
void WinTextEdit::TrimUndoList(unsigned n) {
    unsigned u = (unsigned)DequeSize(undoList);
    if (n >= u) return;
    unsigned count = u - n;
    do {
        void** cur = undoList.mItEnd.mpCurrent;
        if (cur == undoList.mItEnd.mpBegin) {
            void*** ap = undoList.mItEnd.mpCurrentArrayPtr - 1;
            undoList.mItEnd.mpCurrentArrayPtr = ap;
            cur = (void**)*ap + 0x40;
        }
        UndoAction* a = (UndoAction*)cur[-1];
        if (a != 0) {
            uint32_t* nB = (uint32_t*)((char*)a + 4);
            uint32_t* oB = (uint32_t*)((char*)a + 0x14);
            if (((int)((nB[2] - nB[0]) & 0xfffffffeu) > 2) && nB[0] != 0) operator_delete__((void*)nB[0]);
            if (((int)((oB[2] - oB[0]) & 0xfffffffeu) > 2) && oB[0] != 0) operator_delete__((void*)oB[0]);
            operator_delete__(a);
        }
        void** c2 = undoList.mItEnd.mpCurrent;
        void** b2 = undoList.mItEnd.mpBegin;
        if (c2 != b2) {
            undoList.mItEnd.mpCurrent = c2 - 1;
        } else {
            if (b2 != 0) operator_delete__(b2);
            void*** ap2 = undoList.mItEnd.mpCurrentArrayPtr - 1;
            undoList.mItEnd.mpCurrentArrayPtr = ap2;
            void** b = (void**)*ap2;
            undoList.mItEnd.mpBegin = b;
            void** e = b + 0x40;
            undoList.mItEnd.mpEnd = e;
            undoList.mItEnd.mpCurrent = e - 1;
        }
        count--;
    } while (count != 0);
}

// ============================================================ 0x98bea0
// @ 0x98bea0
void WinTextEdit::TrimRedoList(unsigned n) {
    unsigned u = (unsigned)DequeSize(redoList);
    if (n >= u) return;
    unsigned count = u - n;
    do {
        void** cur = redoList.mItEnd.mpCurrent;
        if (cur == redoList.mItEnd.mpBegin) {
            void*** ap = redoList.mItEnd.mpCurrentArrayPtr - 1;
            redoList.mItEnd.mpCurrentArrayPtr = ap;
            cur = (void**)*ap + 0x40;
        }
        UndoAction* a = (UndoAction*)cur[-1];
        if (a != 0) {
            uint32_t* nB = (uint32_t*)((char*)a + 4);
            uint32_t* oB = (uint32_t*)((char*)a + 0x14);
            if (((int)((nB[2] - nB[0]) & 0xfffffffeu) > 2) && nB[0] != 0) operator_delete__((void*)nB[0]);
            if (((int)((oB[2] - oB[0]) & 0xfffffffeu) > 2) && oB[0] != 0) operator_delete__((void*)oB[0]);
            operator_delete__(a);
        }
        void** c2 = redoList.mItEnd.mpCurrent;
        void** b2 = redoList.mItEnd.mpBegin;
        if (c2 != b2) {
            redoList.mItEnd.mpCurrent = c2 - 1;
        } else {
            if (b2 != 0) operator_delete__(b2);
            void*** ap2 = redoList.mItEnd.mpCurrentArrayPtr - 1;
            redoList.mItEnd.mpCurrentArrayPtr = ap2;
            void** b = (void**)*ap2;
            redoList.mItEnd.mpBegin = b;
            void** e = b + 0x40;
            redoList.mItEnd.mpEnd = e;
            redoList.mItEnd.mpCurrent = e - 1;
        }
        count--;
    } while (count != 0);
}

// ============================================================ 0x98bfc0
// @ 0x98bfc0
void ParagraphVector::insert(Paragraph* pos, const Paragraph& value) {
    if (pos != mpEnd) {
        Paragraph* v = (Paragraph*)&value;
        if (pos <= v && v < mpEnd) v = (Paragraph*)((char*)v + 0x18);
        if (mpEnd != 0) {
            mpEnd[0] = *(Paragraph*)((char*)mpEnd - 0x18);
        }
        ParagraphMoveBack(pos, (char*)mpEnd - 0x18, mpEnd);
        *pos = *v;
        mpEnd = mpEnd + 1;
        return;
    }

    int count = (int)(((char*)mpEnd - (char*)mpBegin) / 0x18);
    int cap;
    if (count == 0) {
        cap = 1;
    } else {
        cap = count * 2;
        if (cap == 0) cap = 1;
    }
    Paragraph* mem = (Paragraph*)operator_new(cap * 0x18, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    Paragraph* p = (Paragraph*)ParagraphRelocate(mpBegin, pos, mem);
    if (p != 0) *p = value;
    Paragraph* e = (Paragraph*)ParagraphRelocate(pos, mpEnd, (char*)p + 0x18);
    Paragraph* old = mpBegin;
    if (old != 0 && ((int*)old)[-1] != 0) operator_delete__(old);
    mpBegin = mem;
    mpEnd = e;
    mpCap = (Paragraph*)((char*)mem + cap * 0x18);
}

// ============================================================ 0x98c110
// @ 0x98c110
WinTextEdit::WinTextEdit() {
    WND(this)->Ctor();
    flag210 = 0;
    flags = 0x54;
    dirty = 0;
    *(uint32_t*)((char*)this + 0x21c) = 0;
    *(float*)((char*)this + 0x220) = g_DefaultSpacing4;
    *(float*)((char*)this + 0x224) = g_DefaultSpacing4;
    *(float*)((char*)this + 0x228) = g_DefaultSpacing4;
    *(float*)((char*)this + 0x22c) = g_DefaultSpacing4;
    *(float*)((char*)this + 0x230) = 0.0f;
    areaTop = 0.0f;
    *(float*)((char*)this + 0x238) = 0.0f;
    areaBottom = 0.0f;
    *(uint32_t*)((char*)this + 0x240) = 0;
    maxTextLength = 0xffffffff;
    cursor = 0;
    anchor = 0;
    *(uint32_t*)((char*)this + 0x270) = 0;
    *(uint32_t*)((char*)this + 0x274) = 0;
    *(float*)((char*)this + 0x278) = 0.0f;
    paragraphs.mpBegin = 0;
    paragraphs.mpEnd = 0;
    paragraphs.mpCap = 0;
    TS((char*)this + 0x290)->Ctor();
    *(uint32_t*)((char*)this + 0x508) = 0;
    *(uint32_t*)((char*)this + 0x50c) = 0;
    *(uint32_t*)((char*)this + 0x510) = 0;
    *(uint32_t*)((char*)this + 0x514) = 0;
    valignMode = 0;
    undoHistorySize = 0xa;
    *(uint32_t*)((char*)this + 0x528) = 0;
    *(uint32_t*)((char*)this + 0x52c) = 0;
    *(uint64_t*)((char*)this + 0x530) = 0;
    *(uint32_t*)((char*)this + 0x538) = 0;
    *(uint32_t*)((char*)this + 0x53c) = 0;
    *(uint32_t*)((char*)this + 0x540) = 0;
    *(uint32_t*)((char*)this + 0x544) = 0;
    *(uint32_t*)((char*)this + 0x548) = 0;
    *(uint32_t*)((char*)this + 0x54c) = 0;
    *(uint64_t*)((char*)this + 0x550) = 0;
    *(uint64_t*)((char*)this + 0x558) = 0;
    FUN_0098b830(this, 0);
    *(uint64_t*)((char*)this + 0x560) = 0;
    *(uint32_t*)((char*)this + 0x568) = 0;
    *(uint32_t*)((char*)this + 0x56c) = 0;
    *(uint32_t*)((char*)this + 0x570) = 0;
    *(uint32_t*)((char*)this + 0x574) = 0;
    *(uint32_t*)((char*)this + 0x578) = 0;
    FUN_0098b830(this, 0);
    *(uint64_t*)((char*)this + 0x580) = 0;
    *(uint32_t*)((char*)this + 0x588) = 0;
    *(uint32_t*)((char*)this + 0x58c) = 0;
    *(uint32_t*)((char*)this + 0x590) = 0;
    textExtentX = 0.0f;
    textExtentY = 0.0f;
    extentDrawableA = 0;
    extentDrawableB = 0;
    f5b0 = 0.0f;
    f5b4 = 0.0f;
    SW(stopwatchA)->Ctor(5, 0);
    f5d0 = g_StopwatchUnitScale;
    SW(stopwatchB)->Ctor(5, 0);
    f5f0 = 0.0f;
    f5f4 = 0.0f;
    f5f8 = 0.0f;
    f5fc = 0.0f;
    bool600 = 1;
    SW(stopwatchC)->Ctor(5, 0);
    doubleClickInterval = g_DoubleClickScale;
    *(uint32_t*)((char*)&dropShadow + 0) = 0;
    *(uint32_t*)((char*)&dropShadow + 4) = 2;
    *(uint32_t*)((char*)&dropShadow + 8) = 3;
    *(float*)((char*)&dropShadow + 0xc) = 0.0f;
    *(float*)((char*)&dropShadow + 0x10) = 0.0f;
    *(float*)((char*)&dropShadow + 0x14) = 0.0f;
    *(float*)((char*)&dropShadow + 0x18) = 0.0f;
    *(uint32_t*)((char*)&dropShadow + 0x24) = 0;
    dropShadow.SetMode2(2);
    w64c = 1;
    unk650 = 0;
    colors[0] = 0xff000000;
    colors[1] = 0xffffffff;
    colors[2] = 0xff808080;
    colors[3] = 0xffffffff;
    colors[4] = 0xff0080ff;
    colors[5] = 0xffc0c0ff;
    colors[6] = 0xff00ff00;
    colors[7] = 0xff000000;
    if (extentDrawableB != 0) {
        void* p = extentDrawableB;
        extentDrawableB = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (extentDrawableA != 0) {
        void* p = extentDrawableA;
        extentDrawableA = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    ptr59c = 0;
    if (scrollVDrawable != 0) {
        void* p = scrollVDrawable;
        scrollVDrawable = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (scrollV != 0) {
        void* p = scrollV;
        scrollV = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    scrollHDrawable = 0;
    WND((char*)this + 4)->SetFlag(8, 1);
    WND((char*)this + 4)->SetCursor(0x1004);
    unsigned dt = GetDoubleClickTime();
    float f = (float)(int)dt;
    if ((int)dt < 0) f = f + g_UIntToFloatBias;
    doubleClickInterval = f * g_MillisToSeconds;
}

// ============================================================ 0x98c4b0
// @ 0x98c4b0
void WinTextEdit::SerUpdate() {
    TrimUndoList(0);
    TrimRedoList(0);
    FUN_0098a090(this, 1);
    FUN_0098a090(this, 0);
    void* iwin = (char*)this + 0x4;
    void* vt = *(void**)iwin;
    uint32_t arg = *(uint32_t*)((char*)this + 0xc0);
    VSLOT(void (__thiscall*)(void*, uint32_t), iwin, 0x84)(iwin, arg);
    dirty |= 4;
    dropShadow.SetMode1(*(int*)&dropShadow.m2);
    dropShadow.SetMode2(*(int*)&dropShadow.m6);
    WND(this)->SerUpdate();
}

// ============================================================ 0x98c520
// @ 0x98c520
void WinTextEdit::Shutdown() {
    TrimUndoList(0);
    TrimRedoList(0);
    if (extentDrawableA != 0) {
        void* p = extentDrawableA;
        extentDrawableA = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (extentDrawableB != 0) {
        void* p = extentDrawableB;
        extentDrawableB = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (scrollH != 0) {
        void* p = scrollH;
        scrollH = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    if (scrollHDrawable != 0) {
        void* p = scrollHDrawable;
        scrollHDrawable = 0;
        VSLOT(void (__thiscall*)(void*), p, 4)(p);
    }
    flag210 = 0;
    WND(this)->Shutdown();
}

// ============================================================ 0x98c5a0
// @ 0x98c5a0
// this==the IWinTextEdit interface pointer (WinTextEdit + 0x20c); the body is written with the
// interface-relative offsets the original uses.
int WinTextEdit::Replace(void* src, unsigned count0, unsigned count1, unsigned count2, unsigned rem) {
    int len = (int)((*(uint32_t*)((char*)this - 0x158) - *(uint32_t*)((char*)this - 0x15c)) >> 1);
    const unsigned& idx = ((unsigned)len < count0) ? *(const unsigned*)&len : count0;
    unsigned avail = (unsigned)len - idx;
    const unsigned& cnt = (avail < count1) ? avail : count1;
    if (cnt == 0 && count2 == 0) return 0;

    unsigned newLen = ((unsigned)len - cnt) + rem;
    if (newLen > (unsigned)len && newLen > *(uint32_t*)((char*)this + 0x58)) {
        WinText_Error((WinTextEdit*)((char*)this - 0x20c), 3);
        return 0;
    }

    void* raw = operator_new(0x34, "UTFWin/WinTextEdit/UndoAction", 0, 0, 0, 0);
    UndoAction* u = (UndoAction*)raw;
    if (u != 0) {
        u->nB = (uint32_t)g_EmptyString16;
        u->nE = u->nB;
        u->nC = (uint32_t)(g_EmptyString16 + 1);
        u->oB = u->nB;
        u->oE = u->nB;
        u->oC = u->nC;
    } else {
        u = 0;
    }
    u->index = idx;
    const wchar_t* tb = (const wchar_t*)*(uint32_t*)((char*)this - 0x15c);
    WString_Assign(&u->nB, 0, tb + idx, tb + idx + cnt);
    WString_Assign(&u->oB, 0, (const wchar_t*)src, (const wchar_t*)src + rem);
    u->oldCursorIndex = *(uint32_t*)((char*)this + 0x5c);
    u->oldAnchorIndex = *(uint32_t*)((char*)this + 0x60);
    u->newCursorIndex = (idx + cnt <= *(uint32_t*)((char*)this + 0x5c))
        ? (*(uint32_t*)((char*)this + 0x5c) - cnt + rem) : (idx + rem);
    u->newAnchorIndex = (idx + cnt <= *(uint32_t*)((char*)this + 0x60))
        ? (*(uint32_t*)((char*)this + 0x60) - cnt + rem) : (idx + rem);
    WinTextEdit* self = (WinTextEdit*)((char*)this - 0x20c);
    self->ApplyRedoUndo(u);
    if (*(uint32_t*)((char*)this + 0x34) == 0 && !WinTextEdit_ValidateChange(self)) {
        self->ApplyUndoRedo(u);
        u->scalar_deleting_destructor(1);
        return 0;
    }
    if (*(uint8_t*)((char*)this + 4) == 0 || *(uint32_t*)((char*)this + 0x318) == 0) {
        u->scalar_deleting_destructor(1);
    } else {
        self->TrimRedoList(0);
        self->undoList.push_back(*(void**)&u);
        self->TrimUndoList(*(uint32_t*)((char*)this + 0x318));
        if (rem != 0) {
            FUN_009899b0(self);
        }
    }
    uint32_t flags = *(uint32_t*)((char*)this + 0xc) | 7;
    *(uint32_t*)((char*)this + 0xc) = flags;
    {
        void* iwin = (char*)this - 0x208;
        VSLOT(void (__thiscall*)(void*), iwin, 0x90)(iwin);
    }
    return 1;
}

// ============================================================ 0x98c860
// @ 0x98c860
void IWinTextEdit::SetUndoHistorySize(unsigned n) {
    *(uint32_t*)((char*)this + 0x318) = n;
    WIN(this)->TrimUndoList(n);
}

}}  // namespace EA::UTFWinControls
