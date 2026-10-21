// src/game/UTFSpore_Win32/TextEdit.cpp -- migrated from slice(s) s0098e3a0, s0098a820, s0096e3a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/TextEdit.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "EA/UTFWinControls/IWinTextEdit.h"
#include "EA/Text/FontServer.h"
#include "EA/Text/LineLayout.h"
#include "EA/Stopwatch.h"
#include "EA/Text/TextStyle.h"
#include "EA/Text/Typesetter.h"
#include <stddef.h>
#pragma intrinsic(sqrt)

// ---- items of slice s0098a820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned short c, unsigned short mask);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
void* operator_new(size_t size, const char* name, int flags, unsigned dbgFlags, const char* file, int line);  // 00F473A0
void operator_delete__(void* p);                                                                               // 00F47380
namespace EA {
namespace Text {
struct TextRun { const wchar_t* text; void* style; };
}
}
namespace EA {
namespace Text {
class TextRunIterator { public:
    uint32_t pad[7];
    void SetTextRunArray(const TextRun* runs, unsigned count, unsigned a, unsigned b, unsigned c);   // 0088F790
};
}
}
namespace EA {
namespace Text {
class BreakIteratorBase : public TextRunIterator { public:
    uint32_t f1c;
    unsigned SetPosition(unsigned pos);                 // 00888220
};
}
}
namespace EA {
namespace Text {
class CharacterBreakIterator : public BreakIteratorBase { public:
    unsigned GetNextCharBreak();                        // 00888240
    unsigned GetPrevCharBreak();                        // 008884B0
};
}
}
namespace EA {
namespace Clipboard {
class IData { public:
virtual void m0();
virtual void m4();
    virtual void Release();                         // 0x08
    virtual void mc();
    virtual const wchar_t* GetData();               // 0x10
    virtual unsigned GetSize();                     // 0x14
};
}
}
namespace EA {
namespace Clipboard {
IData* CreateTextData(const wchar_t* text, int len);                        // 0092AB60
}
}
namespace EA {
namespace Clipboard {
class Clipboard { public:
    bool SetClipboardData(IData* d, int flag);                              // 0092ABB0
    bool GetClipboardData(int fmt, IData** out);                            // 0092A8D0
};
}
}
namespace EA {
namespace Clipboard {
Clipboard* GetClipboard(int which);                                         // 0092AD50
}
}
namespace EA {
namespace UTFWinControls {
struct IWinTextEdit_s0098_a820;
}
}
namespace EA {
namespace UTFWinControls {
struct TextMsg {
    uint32_t w0, w1;
    uint32_t type, src, w4;
    int length;
    const wchar_t* text;
};
}
}
namespace EA {
namespace UTFWinControls {
struct TextWinPrim {
    virtual void p00();
};
}
}
namespace EA {
namespace UTFWinControls {
struct TextIWin {
    virtual void w00();
    virtual void w04();
    virtual void w08();
    virtual void w0c();
    virtual void w10();
    virtual void w14();
    virtual void w18();
    virtual void w1c();
    virtual uint32_t GetId();                                   // 0x20
    virtual void w24();
    virtual uint32_t GetFlags();                                // 0x28
    virtual void w2c();
    virtual void w30();
    virtual void w34();
    virtual void w38();
    virtual void w3c();
    virtual void w40();
    virtual void w44();
    virtual void w48();
    virtual void w4c();
    virtual void w50();
    virtual void w54();
    virtual void w58();
    virtual void w5c();
    virtual void w60();
    virtual void w64();
    virtual void w68();
    virtual void w6c();
    virtual void w70();
    virtual void w74();
    virtual void w78();
    virtual void w7c();
    virtual void w80();
    virtual void w84();
    virtual void w88();
    virtual void w8c();
    virtual void w90();
    virtual void w94();
    virtual void w98();
    virtual void w9c();
    virtual void wa0();
    virtual void wa4();
    virtual void wa8();
    virtual void wac();
    virtual void wb0();
    virtual void wb4();
    virtual void wb8();
    virtual void wbc();
    virtual void wc0();
    virtual void wc4();
    virtual void wc8();
    virtual void wcc();
    virtual void wd0();
    virtual void wd4();
    virtual void wd8();
    virtual void wdc();
    virtual void we0();
    virtual void we4();
    virtual void we8();
    virtual void wec();
    virtual void wf0();
    virtual void wf4();
    virtual void wf8();
    virtual void wfc();
    virtual char IsDisabled(int which);                         // 0x100
    virtual void w104();
    virtual void w108();
    virtual void w10c();
    virtual void w110();
    virtual void SendMessage(TextMsg* m);                // 0x114
};
}
}
namespace EA {
namespace UTFWinControls {
struct TextWindow : TextWinPrim, TextIWin {
    uint32_t p08[(0xb0 - 8) / 4];
    wchar_t* textBegin;                         // +0xb0
    wchar_t* textEnd;                           // +0xb4
    uint32_t pb8[(0x20c - 0xb8) / 4];
    unsigned TextLength() const { return (unsigned)(textEnd - textBegin); }
};
}
}
namespace EA {
namespace UTFWinControls {
struct IUnk { virtual void AddRef(); virtual void Release(); };
}
}
namespace EA {
namespace UTFWinControls {
struct ScrollbarSlot {
    IUnk* scrollbar;                            // +0
    int enabled;                                // +4
    uint32_t p08[3];
};
}
}
namespace EA {
namespace UTFWinControls {
struct IWinTextEdit_s0098_a820 {
    virtual void t00();
    virtual void t04();
    virtual void t08();
    virtual void t0c();
    virtual void t10();
    virtual void t14();
    virtual void t18();
    virtual void t1c();
    virtual void t20();
    virtual void t24();
    virtual void t28();
    virtual void t2c();
    virtual void t30();
    virtual void t34();
    virtual void t38();
    virtual void t3c();
    virtual void t40();
    virtual void SetOption(int which, int on);                  // 0x44
    virtual char GetOption(int which);                          // 0x48
    virtual void t4c();
    virtual void* GetTextStyle();                               // 0x50
    virtual void t54();
    virtual void t58();
    virtual void t5c();
    virtual void t60();
    virtual void t64();
    virtual void t68();
    virtual void t6c();
    virtual void t70();
    virtual void InsertText(const wchar_t* text, int len, int flag);   // 0x74
    virtual void ReplaceRange(unsigned pos, int a, int b, int c, int d);  // 0x78
    virtual void t7c();
    virtual void t80();
    virtual void t84();
    virtual void t88();
    virtual void SetCursor(unsigned pos, int extend);           // 0x8c
    virtual void t90();
    virtual void SetSelection(unsigned a, unsigned b);          // 0x94
    virtual void t98();
    virtual char MoveCursor(int type, int dir, int extend);     // 0x9c
    virtual void ta0();
    virtual void ta4();
    virtual void ta8();
    virtual void tac();
    virtual void tb0();
    virtual void tb4();
    virtual void tb8();
    virtual void tbc();
    virtual void tc0();
    virtual char CanUndo();                                     // 0xc4
    virtual char CanRedo();                                     // 0xc8
    virtual void Undo();                                        // 0xcc
    virtual void Redo();                                        // 0xd0
    uint32_t p04;
    uint32_t flags;                             // +8   (0x214)
    uint32_t p0c;
    uint32_t lineMode;                          // +0x10 (0x21c)
    uint32_t p14[(0x5c - 0x14) / 4];
    unsigned cursor;                            // +0x5c (0x268)
    unsigned anchor;                            // +0x60 (0x26c)
    uint32_t p64[(0x378 - 0x64) / 4];
    ScrollbarSlot sb[2];                        // +0x378
    bool F989B70(int* a, int* b);               // 00989B70
    void SetScrollbar(int idx, IUnk* p);        // 0098ACB0
    void SetScrollbarEnabled(int idx, int v);   // 0098AD10
};
}
}
namespace EA {
namespace UTFWinControls {
class WinTextEdit : public TextWindow, public IWinTextEdit_s0098_a820 { public:
    unsigned SnapIndex(unsigned pos, int* pOut);        // 0098A430
    unsigned F98A4B0(unsigned pos);                     // 0098A4B0
    unsigned F98A570(unsigned pos);                     // 0098A570
    unsigned F98A660(unsigned pos);                     // 0098A660
    unsigned F98A730(unsigned pos);                     // 0098A730
    void F98A090(int flag);                             // 0098A090
    void Error(int code);                               // 00989240
    void FindSentenceEnd(unsigned pos);                 // 0098A820
    void FindWordStart(unsigned pos);                   // 0098A910
    void FindLineEnd(unsigned pos);                     // 0098A9F0
    unsigned FindLineStart(unsigned pos);               // 0098AA80
    void SelectWordAt(unsigned pos);                    // 0098AB40
    bool OnKeyDown(int a1, int key, unsigned mods);          // 0098AD40
};
}
}
namespace eastl {
template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace eastl {
struct DequeIterator_s0098_a820 {
    void** mpCurrent;
    void** mpBegin;
    void** mpEnd;
    void*** mpCurrentArrayPtr;
    void SetSubarray(void*** pArrayPtr) {
        mpCurrentArrayPtr = pArrayPtr;
        mpBegin = *pArrayPtr;
        mpEnd = mpBegin + 64;
    }
};
}
namespace eastl {
struct DequeBase_s0098_a820 {
    void*** mpPtrArray;
    unsigned mnPtrArraySize;
    DequeIterator_s0098_a820 mItBegin;
    DequeIterator_s0098_a820 mItEnd;
    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(unsigned nAdditionalCapacity, Side allocationSide);
};
}
// ---- items of slice s0098a820 end

// ---- items of slice s0098e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc();
#pragma pack(4)
#pragma intrinsic(__rdtsc)
namespace EA {
namespace Text {
struct TextStyle_s0098_e3a0 {
    uint32_t d[0x9e];
    TextStyle_s0098_e3a0();                                             // 0x8941d0
    TextStyle_s0098_e3a0& operator=(const TextStyle_s0098_e3a0&);                  // 0x894280
};
}
}
namespace EA {
namespace Text {
class StyleManager { public:
    const TextStyle_s0098_e3a0* GetStyle(uint32_t id, int flag);        // 0x894670
};
}
}
namespace EA {
namespace Text {
struct LineLayout_s0098_e3a0 {
    uint32_t pad0;
    const wchar_t* mBegin;
    const wchar_t* mEnd;
    float GetXForIndex(int index, int a, int b);             // 0x898090
    int HitTest(float x, float y, int a, int b, int* out, int c);   // 0x897e00
};
}
}
namespace EA {
namespace Text {
struct Typesetter_s0098_e3a0 {
    void Reset(bool b);                                      // 0x89cdf0
    void AddTextRun(const wchar_t* p, uint32_t n);           // 0x89b1e0
    LineLayout_s0098_e3a0* GetLineLayout();                             // 0x8976a0
    void FinalizeLine();                                     // 0x89d9a0
    void NextLine(bool b);                                   // 0x89c5d0
    void SetStyle(const void* style);                        // 0x8981f0
    int GetState();                                          // 0x897680
    void SetBounds(float w, float x, float y);               // 0x897640
};
}
}
namespace EA {
namespace Text {
struct FontServer_s0098_e3a0 {
    virtual void fs0(); virtual void fs1(); virtual void fs2(); virtual void fs3(); virtual void fs4(); virtual void fs5();
    virtual int GetFonts(const TextStyle_s0098_e3a0* s, void* out, uint32_t a, uint32_t b, uint32_t c, int d); // slot 6 (+0x18)
};
}
}
namespace EA {
namespace Text {
StyleManager* GetStyleManager(bool create);                  // 0x885bd0
}
}
namespace EA {
namespace Text {
FontServer_s0098_e3a0* GetFontServer(bool create);                      // 0x885a60
}
}
namespace EA {
namespace Text {
void GetMaxFontMetrics(void* fonts, float* a, float* b);     // 0x8985b0
}
}
struct FontScratch { uint32_t d[8]; FontScratch(); ~FontScratch(); };
struct Stopwatch_s0098_e3a0 {
    uint64_t mStart;
    uint64_t mElapsed;
    int mUnits;
    float mScale;
    int64_t GetElapsedTimeFloat();                           // 0x93a3a0
    void Restart();                                          // 0x571e80
};
namespace EA {
namespace UTFWinControls {
struct Paragraph {
    uint32_t mTextIndex;
    uint32_t mTextLength;
    int mTextLines;
    float mExtentX, mExtentY;
    float mYPos;
};
}
}
namespace EA {
namespace UTFWinControls {
struct YPosComparator {};
}
}
namespace EA {
namespace UTFWinControls {
struct TextIndexComparator {};
}
}
namespace EA {
namespace UTFWinControls {
const Paragraph* UpperBoundY(const Paragraph* first, const Paragraph* last, const float& v, YPosComparator c);  // 0x98b650
}
}
namespace EA {
namespace UTFWinControls {
const Paragraph* UpperBoundIndex(const Paragraph* first, const Paragraph* last, const uint32_t& v, TextIndexComparator c);  // 0x98b6b0
}
}
namespace EA {
namespace UTFWinControls {
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
}
}
namespace EA {
namespace UTFWinControls {
template <class T> inline T Reload(const T& v) { return *(const volatile T*)&v; }
}
}
namespace EA {
namespace UTFWinControls {
struct Point2 { float x, y; };
}
}
namespace EA {
namespace UTFWinControls {
using EA::Text::LineLayout_s0098_e3a0;
}
}
namespace EA {
namespace UTFWinControls {
struct WinTextEdit_s0098_e3a0;
}
}
namespace EA {
namespace UTFWinControls {
struct IWinTextEdit_s0098_e3a0 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual int GetTextLength();                              // slot 20 (+0x50)
    virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void SetCursorIndex(uint32_t index, uint32_t extend);   // slot 35 (+0x8c)
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void SetScrollPosition(const Point2* p);          // slot 54 (+0xd8)
    virtual void Update();                                    // slot 55 (+0xdc)

    uint32_t mFlags;           // +0x04 (object +0x210)
    uint32_t mTextEditFlags;   // +0x08
    uint32_t mDirtyFlags;      // +0x0c
    uint32_t pad10;
    float mBorderLeft;         // +0x14
    uint32_t pad18[(0x24 - 0x18) / 4];
    float mVisLeft;            // +0x24
    float mVisTop;             // +0x28
    float mVisRight;           // +0x2c
    float mVisBottom;          // +0x30
    uint32_t mEditColor;       // +0x34
    uint32_t pad38[(0x5c - 0x38) / 4];
    uint32_t mCursorIndex;     // +0x5c
    uint32_t mAnchorIndex;     // +0x60
    uint32_t mCursorColumn;    // +0x64
    uint32_t mCursorParaLine;  // +0x68
    float mCursorSeekX;        // +0x6c
    Paragraph* mParaBegin;     // +0x70
    Paragraph* mParaEnd;       // +0x74
    uint32_t pad78[(0x80 - 0x78) / 4];
    EA::Text::TextStyle_s0098_e3a0 mActualStyle;   // +0x80
    int mFontHeight;           // +0x2f8
    uint32_t mLineHeight;      // +0x2fc
    const uint32_t* mLineBreaksBegin;   // +0x300
    const uint32_t* mLineBreaksEnd;     // +0x304
    uint32_t pad308[(0x39c - 0x308) / 4];
    float mScrollX;            // +0x39c
    float mScrollY;            // +0x3a0
    float mExtentX;            // +0x3a4
    float mExtentY;            // +0x3a8
    uint32_t pad3ac[(0x3c4 - 0x3ac) / 4];
    float mCaretPeriod;        // +0x3c4
    uint32_t pad3c8;
    Stopwatch_s0098_e3a0 mCaretTimer;     // +0x3cc
    float mCaretLeft;          // +0x3e4
    float mCaretTop;           // +0x3e8
    float mCaretRight;         // +0x3ec
    float mCaretBottom;        // +0x3f0
    uint8_t mCaretVisible;     // +0x3f4

    WinTextEdit_s0098_e3a0* Owner() { return (WinTextEdit_s0098_e3a0*)((char*)this - 0x20c); }

    int GetParagraphCount();                                  // 0x98e7b0
    uint32_t GetParagraphTextIndex(uint32_t i);               // 0x98e7e0
    float GetParagraphYPos(uint32_t i);                       // 0x98e830
    uint32_t GetParagraphLength(uint32_t i);                  // 0x98e880
    int GetParagraphAtTextIndex(uint32_t index);              // 0x98e8d0
    int GetParagraphAtPosition(float y);                      // 0x98e930
    void GetTextExtent(Point2* out);                          // 0x98e9a0
    bool MoveCursor(int kind, int amount, uint32_t extend);   // 0x98ec70
    void ScrollToCursor();                                    // 0x98f120
};
}
}
namespace EA {
namespace UTFWinControls {
struct WinTextEdit_s0098_e3a0 {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void OnStyleChanged();                            // slot 36 (+0x90)
    uint32_t pad04[(0xb0 - 4) / 4];
    const wchar_t* mTextBegin; // +0xb0
    const wchar_t* mTextEnd;   // +0xb4
    uint32_t padb8;
    uint32_t mStyleId;         // +0xbc
    uint32_t mStyleId2;        // +0xc0
    uint32_t padc4[(0x20c - 0xc4) / 4];
    IWinTextEdit_s0098_e3a0 mIWin;        // +0x20c

    EA::Text::Typesetter_s0098_e3a0* GetTypesetter();                    // 0x95fba0
    void SetBaseStyle(uint32_t id);                           // 0x95fa40
    void RefreshParagraphs();                                 // 0x98d110
    void SetParagraphCache(const Paragraph* p);               // 0x98cd00
    const Paragraph* FindParagraphForIndex(uint32_t index);   // 0x98b910
    LineLayout_s0098_e3a0* LayoutLine(const Paragraph* p, uint32_t line, uint32_t* a, uint32_t* b);   // 0x98ceb0
    float GetBaselineOffset();                                // 0x98b940
    void ShowCaret(bool show);                                // 0x989660
    void UpdateLayout();                                      // 0x98dff0
    uint32_t WordNext(uint32_t idx);                          // 0x98a4b0
    uint32_t WordPrev(uint32_t idx);         // 0x98a570
    uint32_t LineNext(uint32_t idx);         // 0x98a820
    uint32_t LinePrev(uint32_t idx);         // 0x98a910
    uint32_t ParaNext(uint32_t idx);         // 0x98a9f0
    uint32_t ParaPrev(uint32_t idx);         // 0x98aa80
    uint32_t SnapToLine(uint32_t idx, uint32_t flag);         // 0x98a430
    void GetLineRange(uint32_t line, uint32_t* start, uint32_t* len);   // 0x98a270

    Point2 GetCursorPoint(int index);                         // 0x98e3a0
    void SetTextStyle(uint32_t id);                           // 0x98e690
    void RecalculateCursorPosition();                         // 0x98e9d0
    bool OnTick();                                            // 0x98ebd0
};
}
}
// ---- items of slice s0098e3a0 end

// @ 0x0096f320
bool __cdecl FUN_0096f320(void* p1, char* p2, char* p3)
{
    unsigned* src = *(unsigned**)(p2 + 4);
    unsigned* dst = (unsigned*)(*(int*)((char*)p1 + 4) + *(int*)(p3 + 0x10));
    for (unsigned n = 0; n < *(unsigned*)(p3 + 0x14); n++) {
        unsigned val = *src;
        *dst = val;
        dst++;
        src++;
    }
    return true;
}

// @ 0x0098ab40
namespace EA { namespace UTFWinControls {
void WinTextEdit::SelectWordAt(unsigned pos)
{
    unsigned n = TextLength();
    if (n == 0) {
        SetCursor(0, 0);
        return;
    }
    if (pos >= n) pos = n - 1;
    unsigned start, end;
    if (pos > 1 && iswctype(textBegin[pos], 8) && iswctype(textBegin[pos - 1], 8)) {
        start = F98A730(pos + 1);
        end = F98A4B0(pos);
    } else {
        start = F98A570(pos + 1);
        end = F98A660(pos);
        if (end >= n) goto build;
        if (iswctype(textBegin[end], 8)) end++;
    }
    if (end < n) n = SnapIndex(end, 0);
build:
    {
        Text::TextRun run;
        run.text = textBegin;
        run.style = GetTextStyle();
        Text::CharacterBreakIterator it;
        it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
        it.f1c = 0;
        it.SetPosition(start);
        it.GetNextCharBreak();
        unsigned s = it.GetPrevCharBreak();
        SetSelection(s, n);
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098acb0
namespace EA { namespace UTFWinControls {
void IWinTextEdit_s0098_a820::SetScrollbar(int idx, IUnk* p)
{
    IUnk* old = sb[idx].scrollbar;
    if (p != old) {
        if (p) p->AddRef();
        sb[idx].scrollbar = p;
        if (old) old->Release();
    }
    WinTextEdit* w = (WinTextEdit*)((char*)this - 0x20c);
    w->F98A090(1);
    w->F98A090(0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098ad10
namespace EA { namespace UTFWinControls {
void IWinTextEdit_s0098_a820::SetScrollbarEnabled(int idx, int v)
{
    sb[idx].enabled = v;
    WinTextEdit* w = (WinTextEdit*)((char*)this - 0x20c);
    w->F98A090(1);
    w->F98A090(0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098ad40
namespace EA { namespace UTFWinControls {
bool WinTextEdit::OnKeyDown(int a1, int key, unsigned mods)
{
    bool shift = (mods & 1) != 0;
    bool ctrl = ((mods >> 1) & 1) != 0;
    bool alt = ((mods >> 2) & 1) != 0;
    bool readOnly = (flags & 1) != 0;
    bool bit6 = ((flags >> 6) & 1) != 0;
    bool selectable = bit6 || !readOnly;

    if ((GetFlags() >> 4) & 1) return false;

    switch (key) {
    case 0xd: { // enter
        if (flags & 2) return true;
        TextMsg m;
        m.type = 0x17;
        m.src = GetId();
        unsigned len = TextLength();
        float lenF = (float)len;
        m.length = (int)lenF;
        m.text = textBegin;
        SendMessage(&m);
        return false;
    }
    case 0x2d: { // insert
        if (!(flags & 4)) return false;
        SetOption(8, GetOption(8) == 0);
        return true;
    }
    case 8:     // backspace
        if (readOnly) return true;
        if (cursor != anchor) {
            InsertText(0, 0, 1);
            return true;
        }
        if (cursor > 0) {
            ReplaceRange(cursor - 1, 1, 0, 0, 1);
            return true;
        }
        Error(4);
        return true;
    case 0x2e: { // delete
        if (readOnly) return true;
        if (cursor != anchor) {
            InsertText(0, 0, 1);
            return true;
        }
        if (cursor < TextLength()) {
            int adj = 0;
            unsigned r = SnapIndex(cursor, &adj);
            ReplaceRange(r, adj, 0, 0, 1);
            return true;
        }
        Error(4);
        return true;
    }
    case 0x26: // up
        if (lineMode == 0) return true;
        if (!selectable) return true;
        if (!MoveCursor(2, -1, shift)) { Error(4); return true; }
        return true;
    case 0x28: // down
        if (lineMode == 0) return true;
        if (!selectable) return true;
        if (!MoveCursor(2, 1, shift)) { Error(4); return true; }
        return true;
    case 0x25: // left
    case 0x27: { // right
        if (!selectable) return true;
        int type = 0;
        if (ctrl) type = (alt ? 1 : 0) * 2 + 1;
        else if (alt) type = 4;
        if (!MoveCursor(type, key == 0x25 ? -1 : 1, shift)) {
            Error(4);
            return true;
        }
        return true;
    }
    case 0x24: // home
        if (!alt && !ctrl) {
            MoveCursor(6, 0, shift);
            return true;
        }
        MoveCursor(8, 0, shift);
        return true;
    case 0x23: // end
        if (!alt && !ctrl) {
            MoveCursor(7, 0, shift);
            return true;
        }
        MoveCursor(9, 0, shift);
        return true;
    case 0x21: // page up
        if (!selectable) return true;
        if (!MoveCursor(5, -1, shift)) { Error(4); return true; }
        return true;
    case 0x22: // page down
        if (!selectable) return true;
        if (!MoveCursor(5, 1, shift)) { Error(4); return true; }
        return true;
    case 0x1b:  // escape
        if (cursor == anchor) return false;
        SetCursor(cursor, 0);
        return true;
    case 0x43: // C
    case 0x58: { // X
        if (ctrl && !shift && !alt && bit6 && !((flags >> 7) & 1) && !IsDisabled(1)) {
            EA::Clipboard::Clipboard* clip = EA::Clipboard::GetClipboard(0);
            if (clip) {
                int selStart, selEnd;
                if (F989B70(&selStart, &selEnd)) {
                    EA::Clipboard::IData* d = EA::Clipboard::CreateTextData(textBegin + selStart, selEnd - selStart);
                    if (d) {
                        bool ok = clip->SetClipboardData(d, 1);
                        d->Release();
                        if (!ok) Error(6);
                    }
                    if (key == 0x58 && !readOnly) {
                        InsertText(0, 0, 1);
                        return true;
                    }
                }
            }
        }
        return true;
    }
    case 0x56: { // V
        if (ctrl && !shift && !alt && !IsDisabled(1)) {
            EA::Clipboard::Clipboard* clip = EA::Clipboard::GetClipboard(0);
            if (bit6 && !readOnly && clip) {
                EA::Clipboard::IData* d;
                if (clip->GetClipboardData(3, &d)) {
                    unsigned n = (d->GetSize() >> 1) - 1;
                    if (lineMode == 0) {
                        const wchar_t* p = d->GetData();
                        unsigned i = 0;
                        while (i < n) {
                            wchar_t c = p[i];
                            if (c == 0xa || c == 0xd || c == 0x85 || c == 0x2028 || c == 0x2029) {
                                n = i;
                                break;
                            }
                            i++;
                        }
                    }
                    InsertText(d->GetData(), n, 1);
                    d->Release();
                    return true;
                }
            }
        }
        return true;
    }
    case 0x5a: // Z
        if (ctrl && !alt) {
            if (CanUndo()) {
                Undo();
                return true;
            }
            Error(5);
        }
        return true;
    case 0x59: // Y
        if (ctrl && !alt) {
            if (CanRedo()) {
                Redo();
                return true;
            }
            Error(5);
        }
        return true;
    case 0x20:
    case 0x6a: case 0x6b: case 0x6d: case 0x6e: case 0x6f:
    case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbe: case 0xbf: case 0xc0:
    case 0xdb: case 0xdc: case 0xde:
        return true;
    case 9:     // tab
        return false;
    default:
        if ((unsigned)key >= 0x41 && (unsigned)key <= 0x5a) return true;
        if ((unsigned)key >= 0x30 && (unsigned)key <= 0x39) return true;
        if ((unsigned)key - 0x60 <= 9) return true;
        return false;
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098b700
namespace eastl {
void DequeBase_s0098_a820::DoReallocPtrArray(unsigned nAdditionalCapacity, Side allocationSide)
{
    const unsigned nUnusedPtrCountAtFront = (unsigned)(mItBegin.mpCurrentArrayPtr - mpPtrArray);
    const unsigned nUsedPtrCount = (unsigned)(mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) + 1;
    const unsigned nUsedPtrSpace = nUsedPtrCount * sizeof(void*);
    void*** pPtrArrayBegin;
    (void)nUnusedPtrCountAtFront;

    if (!(mnPtrArraySize > (nUsedPtrCount + nAdditionalCapacity) * 2)) {
        const unsigned nNewPtrArraySize = mnPtrArraySize + max_alt(mnPtrArraySize, nAdditionalCapacity) + 2;
        void*** const pNewPtrArray = (void***)operator_new(nNewPtrArraySize * sizeof(void*), "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        pPtrArrayBegin = pNewPtrArray + (mItBegin.mpCurrentArrayPtr - mpPtrArray) +
                         ((allocationSide == kSideFront) ? nAdditionalCapacity : 0);
        if (mpPtrArray)
            memcpy(pPtrArrayBegin, mItBegin.mpCurrentArrayPtr, nUsedPtrSpace);
        if (mpPtrArray)
            operator_delete__(mpPtrArray);
        mpPtrArray = pNewPtrArray;
        mnPtrArraySize = nNewPtrArraySize;
    } else {
        pPtrArrayBegin = mpPtrArray + ((mnPtrArraySize - (nUsedPtrCount + nAdditionalCapacity)) / 2) +
                         ((allocationSide == kSideFront) ? nAdditionalCapacity : 0);
        if (pPtrArrayBegin < mItBegin.mpCurrentArrayPtr)
            memcpy(pPtrArrayBegin, mItBegin.mpCurrentArrayPtr, nUsedPtrSpace);
        else
            memmove(pPtrArrayBegin + nUsedPtrCount - (nUsedPtrSpace >> 2), mItBegin.mpCurrentArrayPtr, nUsedPtrSpace);
    }
    mItBegin.SetSubarray(pPtrArrayBegin);
    mItEnd.SetSubarray(pPtrArrayBegin + nUsedPtrCount - 1);
}
}  // namespace eastl

// @ 0x0098e3a0
namespace EA { namespace UTFWinControls {
Point2 WinTextEdit_s0098_e3a0::GetCursorPoint(int index)
{
    EA::Text::Typesetter_s0098_e3a0* ts = GetTypesetter();
    Point2 result;
    result.x = 0.0f;
    result.y = 0.0f;
    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm && sm->GetStyle(mStyleId2, 0)) {
        if (mIWin.mDirtyFlags & 4)
            RefreshParagraphs();
        const Paragraph* pBegin = mIWin.mParaBegin;
        const Paragraph* pEnd = mIWin.mParaEnd;
        float top = mIWin.mScrollY;
        float bottom = (mIWin.mVisBottom - mIWin.mVisTop) + top;
        const Paragraph* last = UpperBoundY(pBegin, pEnd, bottom, YPosComparator());
        const Paragraph* p = UpperBoundY(pBegin, pEnd, top, YPosComparator()) - 1;
        for (; p != last; ++p) {
            ts->Reset(true);
            ts->SetStyle(&mIWin.mActualStyle.d[1]);
            ts->AddTextRun(mTextBegin + p->mTextIndex, p->mTextLength);
            EA::Text::LineLayout_s0098_e3a0* layout = ts->GetLineLayout();
            float baseY = GetBaselineOffset();
            float x = mIWin.mVisLeft - mIWin.mScrollX;
            float y = (p->mYPos + mIWin.mVisTop) - mIWin.mScrollY + baseY;
            int charBase = 0;
            result.x = x;
            result.y = y;
            while (ts->GetState() != 2) {
                result.y = y;
                ts->SetBounds((mIWin.mVisRight - mIWin.mVisLeft) - (mIWin.mCaretRight - mIWin.mCaretLeft), x, y);
                ts->FinalizeLine();
                int lineChars = (int)(float)(uint32_t)(layout->mEnd - layout->mBegin);
                if (charBase <= index && index <= charBase + lineChars) {
                    if (lineChars > 0) {
                        float cx = layout->GetXForIndex(index - charBase, 0, 0);
                        float zero = 0.0f;
                        x = Max(zero, cx);
                    }
                    Point2 r;
                    r.x = x;
                    r.y = y;
                    return r;
                }
                y = (float)(int)mIWin.mLineHeight + y;
                charBase += lineChars;
                ts->SetBounds((mIWin.mVisRight - mIWin.mVisLeft) - (mIWin.mCaretRight - mIWin.mCaretLeft), mIWin.mVisLeft, y);
                ts->NextLine(false);
            }
        }
    }
    return result;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e690
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_e3a0::SetTextStyle(uint32_t id)
{
    SetBaseStyle(id);
    mIWin.mTextEditFlags |= 5;
    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm) {
        const EA::Text::TextStyle_s0098_e3a0* style = sm->GetStyle(mStyleId, 0);
        EA::Text::TextStyle_s0098_e3a0 fallback;
        mIWin.mActualStyle = style ? *style : fallback;
        EA::Text::FontServer_s0098_e3a0* fs = EA::Text::GetFontServer(true);
        if (fs) {
            FontScratch fonts;
            if (fs->GetFonts(&mIWin.mActualStyle, &fonts, 0xffffffff, 0xffff, 0xffffffff, 1)) {
                float a = 0.0f, b = 0.0f;
                EA::Text::GetMaxFontMetrics(&fonts, &a, &b);
                float h = a - b;
                mIWin.mFontHeight = (int)h;
            }
        }
    }
    if (*(char*)&mIWin)
        OnStyleChanged();
    if ((mIWin.mFlags >> 7) & 1)
        mIWin.mActualStyle.d[0x99] = 1;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e7b0
namespace EA { namespace UTFWinControls {
int IWinTextEdit_s0098_e3a0::GetParagraphCount()
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    return (int)(mParaEnd - mParaBegin);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e7e0
namespace EA { namespace UTFWinControls {
uint32_t IWinTextEdit_s0098_e3a0::GetParagraphTextIndex(uint32_t i)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    if (i >= (uint32_t)(mParaEnd - mParaBegin))
        return 0xffffffff;
    return Reload(mParaBegin)[i].mTextIndex;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e830
namespace EA { namespace UTFWinControls {
float IWinTextEdit_s0098_e3a0::GetParagraphYPos(uint32_t i)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    if (i >= (uint32_t)(mParaEnd - mParaBegin))
        return 0.0f;
    return Reload(mParaBegin)[i].mYPos;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e880
namespace EA { namespace UTFWinControls {
uint32_t IWinTextEdit_s0098_e3a0::GetParagraphLength(uint32_t i)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    if (i >= (uint32_t)(mParaEnd - mParaBegin))
        return 0xffffffff;
    return Reload(mParaBegin)[i].mTextLength;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e8d0
namespace EA { namespace UTFWinControls {
int IWinTextEdit_s0098_e3a0::GetParagraphAtTextIndex(uint32_t index)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    uint32_t value = index;
    const Paragraph* p = UpperBoundIndex(mParaBegin, mParaEnd, value, TextIndexComparator());
    return (int)((p - 1) - mParaBegin);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e930
namespace EA { namespace UTFWinControls {
int IWinTextEdit_s0098_e3a0::GetParagraphAtPosition(float y)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    float value = y;
    const Paragraph* p = UpperBoundY(mParaBegin, mParaEnd, value, YPosComparator());
    return (int)((p - 1) - mParaBegin);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098e9a0
namespace EA { namespace UTFWinControls {
void IWinTextEdit_s0098_e3a0::GetTextExtent(Point2* out)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    out->x = mExtentX;
    out->y = mExtentY;
}
}}  // namespace EA::UTFWinControls
