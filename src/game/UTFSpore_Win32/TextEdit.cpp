// src/game/UTFSpore_Win32/TextEdit.cpp -- migrated from slice(s) s0098d630, s0098c880, s0098b910, s009886d0, s0098e3a0, s0098a820, s0096e3a0 by tools/migrate/rewrite.py
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
#include "EA/UTFWin/RenderContext.h"
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
class IWinTextEdit_s0098_a820;
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
class IWinTextEdit_s0098_a820 { public:
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

// ---- items of slice s009886d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define F(o, off)   (*(uint32_t*)((uint8_t*)(o) + (off)))
struct Iface {
    virtual void  s00();                             // slot 0
    virtual void  s01();                             // 0x04
    virtual void  s02();
    virtual void* s03();                             // 0x0c
    virtual void  s04();                             // 0x10
    virtual void* s05();                             // 0x14  returns object with vtable
    virtual void  s06();
    virtual uint8_t s07(uint32_t);                   // 0x1c
    virtual char  s08(void*, uint32_t, uint32_t);    // 0x20
    virtual void  s09();
    virtual uint32_t s10();                          // 0x28
virtual void  s11();
virtual void s12();
virtual void s13();
virtual void  s14();
virtual void s15();
    virtual void  s16(void*, int);                   // 0x40
virtual void  s17();
virtual void s18();
virtual void s19();
virtual void  s20();
virtual void s21();
virtual void s22();
    virtual void  s23(uint32_t, uint32_t);           // 0x5c
virtual void  s24();
virtual void s25();
virtual void s26();
    virtual void  s27(void*);                        // 0x6c
virtual void  s28();
virtual void s29();
virtual void s30();
virtual void  s31();
virtual void s32();
virtual void s33();
    virtual void  s34();
    virtual void  s35(uint32_t, void*);              // 0x8c
    virtual void  s36();                             // 0x90
virtual void  s37();
virtual void s38();
virtual void s39();
virtual void  s40();
virtual void s41();
virtual void s42();
virtual void  s43();
virtual void s44();
virtual void s45();
virtual void  s46();
virtual void s47();
virtual void s48();
virtual void  s49();
virtual void s50();
virtual void s51();
virtual void  s52();
virtual void s53();
virtual void s54();
virtual void  s55();
virtual void s56();
virtual void s57();
virtual void  s58();
virtual void s59();
virtual void s60();
virtual void  s61();
virtual void s62();
    virtual char  s63(int);                          // 0xfc
    virtual char  s64(uint32_t);                     // 0x100
virtual void  s65();
virtual void s66();
virtual void s67();
    virtual void  s68();
    virtual void  s69(void*);                        // 0x114
};
struct WinBase {
    virtual void  v00();                           // slot 0
virtual void  v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void  v05();
virtual void v06();
    virtual void* v07(uint32_t);                   // 0x1c
virtual void  v08();
virtual void v09();
    virtual uint32_t v10();                        // 0x28
virtual void  v11();
virtual void v12();
virtual void  v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void  v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void  v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void  v25();
virtual void v26();
virtual void v27();
virtual void v28();
    virtual void  v29();
    virtual void  v30(int, int, int, int, int);   // 0x78
virtual void  v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void  v35(uint32_t, void*);           // 0x8c
    virtual void  v36();                          // 0x90
    virtual void  v37(uint32_t, uint32_t);        // 0x94
};
struct SubWin {
    virtual void  c00();                           // slot 0
virtual void  c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void  c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void  c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void  c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void  c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void  c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void  c25();
virtual void c26();
    virtual void  c27(void*);                     // 0x6c
virtual void  c28();
virtual void c29();
virtual void c30();
virtual void c31();
virtual void  c32();
virtual void c33();
virtual void c34();
virtual void c35();
    virtual void  c36();                          // 0x90
};
struct WinText {
    WinBase w;                       // +0x000 vtable pair (base)

    // Members used through byte offsets by the bodies below.
    // 0x009886d0
    void __thiscall m_9886d0(int* p);
    // 0x00988710
    void __thiscall m_988710(uint32_t flag, uint8_t value);
    // 0x00988760
    void __thiscall m_988760(void* p);
    // 0x00988780
    void __thiscall m_988780(int v);
    // 0x009887b0
    void __thiscall m_9887b0(float v);
    // 0x009887e0
    void __thiscall m_9887e0(float a, float b, float c, float d);
    // 0x00988860
    void __thiscall m_988860(uint32_t v);
    // 0x00988890
    void __thiscall m_988890();
    // 0x009888c0
    void __thiscall m_9888c0(uint32_t v);
    // 0x00988920
    uint8_t __thiscall m_988920(void* ctx, Iface* styleMgr);
    // 0x00988ad0
    uint8_t __thiscall m_988ad0(uint32_t p2, float* out);
    // 0x00988c40
    void __thiscall m_988c40(uint32_t p2);
    // 0x00988c90
    void __thiscall m_988c90(uint32_t p2);
    // 0x00988cd0
    uint8_t __thiscall m_988cd0(float* out, uint8_t p3, uint8_t p4);
    // 0x00988f60
    char __thiscall m_988f60(uint32_t p2, float* p3);
    // 0x00988f90
    void __thiscall m_988f90();
    // 0x00989000
    WinText* __thiscall m_989000();
    // 0x009890d0
    WinText* __thiscall m_9890d0(uint8_t p2);
    // 0x00989130
    static WinText* __cdecl Factory(void* p1);
    // 0x00989240
    void __thiscall m_989240(uint32_t p2);
    // 0x00989290
    uint32_t __thiscall m_989290(uint32_t i);
    // 0x009892b0
    void __thiscall m_9892b0(uint32_t i, uint32_t v);
    // 0x00989370
    void __thiscall m_989370(uint32_t v);
    // 0x00989390
    void __thiscall m_989390(uint32_t a, uint32_t b, uint32_t c);
    // 0x009893b0
    void __thiscall m_9893b0(uint32_t a, uint32_t b);
    // 0x009893d0
    void __thiscall m_9893d0(uint32_t a);
    // 0x00989410
    void __thiscall m_989410(uint32_t a, uint8_t flag);
    // 0x00989450
    int __thiscall m_989450(int, int, int, int, int);
    // 0x00989460
    void __thiscall m_989460(uint32_t v);
    // 0x009894a0
    uint32_t __thiscall m_9894a0(uint32_t i);
    // 0x009894c0
    char __thiscall m_9894c0(int, int, int, int);
    // 0x00989500
    uint32_t __thiscall m_989500(uint32_t p2, uint32_t p3);
    // 0x00989660
    void __thiscall m_989660(uint8_t p2);
};
struct AllocIface_9896d0 {
    virtual void* alloc(uint32_t size, uint32_t align);   // slot 0
};
// ---- items of slice s009886d0 end

// ---- items of slice s0098b910 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])
#define WIN(iface) ((WinTextEdit_s0098_b910*)((char*)(iface) - 0x20c))
namespace EA {
namespace UTFWinControls {
class WinTextEdit_s0098_b910;
}
}
namespace EA {
namespace UTFWinControls {
class IWinTextEdit_s0098_b910;
}
}
namespace EA {
namespace UTFWinControls {
struct Paragraph_s0098_b910 {
    uint32_t textIndex;                         // +0x00
    uint32_t textLength;                        // +0x04
    int      textLines;                         // +0x08
    float    extentX;                           // +0x0c
    float    extentY;                           // +0x10
    float    yPos;                              // +0x14
};
}
}
namespace EA {
namespace UTFWinControls {
const Paragraph_s0098_b910* UpperBoundByY(const Paragraph_s0098_b910* first, const Paragraph_s0098_b910* last, const float& v);       // 0098B650
}
}
namespace EA {
namespace UTFWinControls {
struct TextIndexComparator_s0098_b910 {
    char dummy;                                  // empty functor; 1 byte, passed as a 4-byte value
    bool operator()(unsigned i, const Paragraph_s0098_b910& p) const { return i < p.textIndex; }
};
}
}
namespace EA {
namespace UTFWinControls {
const Paragraph_s0098_b910* UpperBoundByIndexC(const Paragraph_s0098_b910* first, const Paragraph_s0098_b910* last, const unsigned& v,
                                    TextIndexComparator_s0098_b910 c);                                          // 0098B6B0
}
}
namespace EA {
namespace UTFWinControls {
struct cDropShadowDescriptor {
    uint32_t m2;                                // +0x00 (mode 1)
    uint32_t m6;                                // +0x04 (mode 2)
    void SetMode1(int v);                       // 00830280
    void SetMode2(int v);                       // 00830150
};
}
}
namespace EA {
namespace UTFWinControls {
struct DequeIterator {
    void**   mpCurrent;                         // +0x00
    void**   mpBegin;                           // +0x04
    void**   mpEnd;                             // +0x08
    void***  mpCurrentArrayPtr;                 // +0x0c
};
}
}
namespace EA {
namespace UTFWinControls {
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
}
}
namespace EA {
namespace UTFWinControls {
long DequeSize(const DequeBase& d) {
    const char* a = (const char*)d.mItEnd.mpCurrentArrayPtr;
    const char* b = (const char*)d.mItBegin.mpCurrentArrayPtr;
    return (((long)(a - b) >> 2) - 1) * 0x40 +
           ((long)((const char*)d.mItEnd.mpCurrent   - (const char*)d.mItEnd.mpBegin)   >> 2) +
           ((long)((const char*)d.mItBegin.mpEnd     - (const char*)d.mItBegin.mpCurrent) >> 2);
}
}
}
namespace EA {
namespace UTFWinControls {
struct ParagraphVector {
    Paragraph_s0098_b910* mpBegin;                         // +0x00
    Paragraph_s0098_b910* mpEnd;                           // +0x04
    Paragraph_s0098_b910* mpCap;                           // +0x08
    void insert(Paragraph_s0098_b910* pos, const Paragraph_s0098_b910& value);      // 0098BFC0
    void reserve(unsigned n);                                 // 0098BAB0
};
}
}
namespace EA {
namespace UTFWinControls {
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
}
}
namespace EA {
namespace UTFWinControls {
struct WindowBase {
    void Ctor();                                    // 00962A10
    void Shutdown();                                // 00961E80
    void SetFlag(unsigned flag, char on);           // 00961760
    void SetCursor(unsigned id);                    // 00960020
    void SerUpdate();                               // 009614A0
};
}
}
namespace EA {
namespace UTFWinControls {
struct StopwatchBase {
    void Ctor(int units, char a);                   // 0093A560
};
}
}
namespace EA {
namespace UTFWinControls {
struct TextStyleBase {
    void Ctor();                                    // 008941D0
};
}
}
namespace EA {
namespace UTFWinControls {
void FUN_0098b830(WinTextEdit_s0098_b910* self, int a);                    // 0098B830
}
}
namespace EA {
namespace UTFWinControls {
void FUN_0098a090(WinTextEdit_s0098_b910* self, int flag);                 // 0098A090  (scrollbar slot rebuild)
}
}
namespace EA {
namespace UTFWinControls {
void FUN_009899b0(WinTextEdit_s0098_b910* self);                           // 009899B0
}
}
namespace EA {
namespace UTFWinControls {
void WinText_Error(WinTextEdit_s0098_b910* self, unsigned code);           // 00989240
}
}
namespace EA {
namespace UTFWinControls {
char WinTextEdit_ValidateChange(WinTextEdit_s0098_b910* self);             // 00989A90
}
}
namespace EA {
namespace UTFWinControls {
#define WND(self)  ((WindowBase*)(self))
}
}
namespace EA {
namespace UTFWinControls {
#define SW(self)   ((StopwatchBase*)(self))
}
}
namespace EA {
namespace UTFWinControls {
#define TS(self)   ((TextStyleBase*)(self))
}
}
namespace EA {
namespace UTFWinControls {
void* ParagraphRelocate(const void* first, const void* last, void* dst);   // 00989740
}
}
namespace EA {
namespace UTFWinControls {
void  ParagraphMoveBack(const void* first, const void* last, void* dst);   // 009897D0
}
}
namespace EA {
namespace UTFWinControls {
void __fastcall WString_Assign(void* self, void*, const wchar_t* first, const wchar_t* last);   // 00423650
}
}
namespace EA {
namespace UTFWinControls {
void __fastcall WString_Replace(void* self, void*, const wchar_t* first, const wchar_t* last,
                                const wchar_t* srcFirst, const wchar_t* srcLast);               // 005F8400
}
}
namespace EA {
namespace UTFWinControls {
extern "C" __declspec(dllimport) unsigned __stdcall GetDoubleClickTime(void);   // USER32
}
}
namespace EA {
namespace UTFWinControls {
__declspec(dllimport) float g_DefaultSpacing4;       // 0x14853E0  (4.0f)
}
}
namespace EA {
namespace UTFWinControls {
__declspec(dllimport) float g_StopwatchUnitScale;    // 0x13EB8A0
}
}
namespace EA {
namespace UTFWinControls {
__declspec(dllimport) float g_DoubleClickScale;      // 0x1471064
}
}
namespace EA {
namespace UTFWinControls {
__declspec(dllimport) float g_MillisToSeconds;       // 0x13F9428
}
}
namespace EA {
namespace UTFWinControls {
__declspec(dllimport) float g_UIntToFloatBias;       // 0x13F4FD0  (4294967296.0f)
}
}
namespace EA {
namespace UTFWinControls {
wchar_t g_EmptyString16[2];                          // 0x1667BAC
}
}
namespace EA {
namespace UTFWinControls {
class WinTextEdit_s0098_b910 { public:
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
    const Paragraph_s0098_b910* FindParagraphByTextIndex(unsigned idx);        // 0098B910
    int      GetVAlignmentOffset();                                 // 0098B940
    void     ApplyUndoRedo(UndoAction* a);                          // 0098BC80
    void     ApplyRedoUndo(UndoAction* a);                          // 0098BD00
    void     TrimUndoList(unsigned n);                              // 0098BD80 0x0098bd80
    void     TrimRedoList(unsigned n);                              // 0098BEA0 0x0098bea0
    int      Replace(void* text, unsigned a, unsigned b, unsigned c, unsigned d);  // 0098C5A0 0x0098c5a0
    void     SerUpdate();                                           // 0098C4B0 0x0098c4b0
    void     Shutdown();                                            // 0098C520 0x0098c520
    WinTextEdit_s0098_b910();                                                  // 0098C110
};
}
}
namespace EA {
namespace UTFWinControls {
class IWinTextEdit_s0098_b910 { public:
    uint8_t  i00[0x20c];
    uint32_t flags;                             // +0x20c == window+0x214
    uint32_t dirty;                             // +0x210 == window+0x218
    void     SetUndoHistorySize(unsigned n);    // 0098C860
    int      GetText(void* out, unsigned idx, unsigned n);   // 0098BBD0
    // window fields reached through the secondary-base relationship (window+0xb0/+0xb4)
    char* TextBegin() const { return *(char**)((char*)this - 0x15c); }
    char* TextEnd()   const { return *(char**)((char*)this - 0x158); }
};
}
}
// ---- items of slice s0098b910 end

// ---- items of slice s0098c880 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
struct TextStyle_s0098_c880 {
    uint32_t d[0x9e];
};
}
}
namespace EA {
namespace Text {
class LineLayout_s0098_c880 { public:
    uint32_t pad0;                  // +0x00
    const wchar_t* mBegin;          // +0x04
    const wchar_t* mEnd;            // +0x08
    uint32_t padC[(0x9c - 0x0c) / 4];
    float mExtentX;                 // +0x9c
    int HitTest(float x, float y, int a, int b, int* out, int c);   // 0x897e00
};
}
}
namespace EA {
namespace Text {
class Typesetter_s0098_c880 { public:
    void Reset(bool b);                                     // 0x89cdf0
    void SetStyle(const void* style);                       // 0x8981f0
    void AddTextRun(const wchar_t* p, uint32_t n);          // 0x89b1e0
    void SetBounds(float w, float x, float y);              // 0x897640
    int  GetState();                                        // 0x897680
    void FinalizeLine();                                    // 0x89d9a0
    LineLayout_s0098_c880* GetLineLayout();                            // 0x8976a0
    void NextLine(bool b);                                  // 0x89c5d0
};
}
}
namespace EA {
namespace Text {
struct TextRunInfo { const wchar_t* text; uint32_t length; };
}
}
namespace EA {
namespace Text {
class TextRunIterator_s0098_c880 { public:
    uint32_t d[5];                  // +0x00
    uint32_t mnPosition;            // +0x14
    uint32_t mnEndPosition;         // +0x18
    uint32_t pad1c;                 // +0x1c
    void SetTextRunArray(const TextRunInfo* runs, uint32_t n, uint32_t a, uint32_t b, int c); // 0x88f790
    uint32_t Next();                                        // 0x8883a0
};
}
}
struct Stopwatch_s0098_c880 {
    uint64_t mStart;                // +0x00
    uint64_t mElapsed;              // +0x08
    int      mUnits;                // +0x10
    float    mScale;                // +0x14
    uint64_t GetElapsedTime();                              // 0x93a5e0
    void Restart();                                         // 0x571e80
};
struct RefObj {
    virtual void r0();
    virtual void Release();
};
void MemFree(void* p);                                      // 0x00f47380
void VectorClear(void* begin, void* end, void* zero);       // 0x011e0744
double Floor(double v);                                     // 0x011e0906
namespace EA {
namespace UTFWinControls {
struct Paragraph_s0098_c880 {
    uint32_t mTextIndex;            // +0x00
    uint32_t mTextLength;           // +0x04
    int      mTextLines;            // +0x08
    float    mExtentX;              // +0x0c
    float    mExtentY;              // +0x10
    float    mYPos;                 // +0x14
};
}
}
namespace EA {
namespace UTFWinControls {
const Paragraph_s0098_c880* UpperBoundY_s0098_c880(const Paragraph_s0098_c880* first, const Paragraph_s0098_c880* last, const float& v, YPosComparator c); // 0x98b650
}
}
namespace EA {
namespace UTFWinControls {
struct ParagraphVector_s0098_c880 {
    Paragraph_s0098_c880* mpBegin;             // +0x00
    Paragraph_s0098_c880* mpEnd;               // +0x04
    Paragraph_s0098_c880* mpCap;               // +0x08
    void reserve(uint32_t n);                               // 0x98bab0
    void push_back(const Paragraph_s0098_c880& v);                     // 0x98cb20
    void DoInsertValue(Paragraph_s0098_c880* pos, const Paragraph_s0098_c880& v); // 0x98bfc0
};
}
}
namespace EA {
namespace UTFWinControls {
struct UIntVector {
    uint32_t* mpBegin;              // +0x00
    uint32_t* mpEnd;                // +0x04
    uint32_t* mpCap;                // +0x08
    void DoInsertValue(uint32_t* pos, const uint32_t& v);   // 0x04558a0
    void push_back(uint32_t v)
    {
        if (mpEnd < mpCap) {
            *mpEnd = v;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
}
}
namespace EA {
namespace UTFWinControls {
struct Deque {
    void** mpPtrArray;              // +0x00
    uint32_t mnPtrArraySize;        // +0x04
    void** mpCurrent;               // +0x08
    void** mpBlockBegin;            // +0x0c
    void** mpBlockEnd;              // +0x10
    void*** mpCurrentArrayPtr;      // +0x14
    void** mpEndCurrent;            // +0x18
    uint32_t pad1c[(0x2c - 0x1c) / 4];

    __forceinline void* pop_front()
    {
        void* v = *mpCurrent;
        void** p = mpCurrent + 1;
        if (p != mpBlockEnd) {
            mpCurrent = p;
        } else {
            if (mpBlockBegin)
                MemFree(mpBlockBegin);
            mpBlockBegin = *++mpCurrentArrayPtr;
            mpBlockEnd = (void**)((char*)mpBlockBegin + 0x100);
            mpCurrent = mpBlockBegin;
        }
        return v;
    }
    __forceinline void push_front(void* v)
    {
        if (mpCurrent != mpBlockBegin) {
            void** p = mpCurrent - 1;
            mpCurrent = p;
            if (p)
                *p = v;
        } else {
            PushFrontSlow(&v);
        }
    }
    void PushFrontSlow(void** v);                           // 0x98bb60
    void Destroy();                                         // 0x98b5e0
};
}
}
namespace EA {
namespace UTFWinControls {
void RebuildParagraphs(Paragraph_s0098_c880* a, Paragraph_s0098_c880* b, Paragraph_s0098_c880* c);   // 0x989790
}
}
namespace EA {
namespace UTFWinControls {
struct Base4Obj {
virtual void o00();
virtual void o01();
virtual void o02();
virtual void o03();
virtual void o04();
virtual void o05();
virtual void o06();
virtual void o07();
virtual void o08();
virtual void o09();
virtual void o10();
virtual void o11();
virtual void o12();
virtual void o13();
virtual void o14();
virtual void o15();
virtual void o16();
virtual void o17();
virtual void o18();
virtual void o19();
virtual void o20();
virtual void o21();
    virtual void Notify(int flag, void* self);              // slot 22 (+0x58)
};
}
}
namespace EA {
namespace UTFWinControls {
struct Base4 {
virtual void b00();
virtual void b01();
virtual void b02();
virtual void b03();
virtual void b04();
    virtual Base4Obj* GetObj();                             // slot 5  (+0x14)
virtual void b06();
virtual void b07();
virtual void b08();
virtual void b09();
virtual void b10();
virtual void b11();
virtual void b12();
virtual void b13();
virtual void b14();
virtual void b15();
virtual void b16();
virtual void b17();
virtual void b18();
virtual void b19();
virtual void b20();
virtual void b21();
virtual void b22();
virtual void b23();
virtual void b24();
virtual void b25();
virtual void b26();
virtual void b27();
virtual void b28();
virtual void b29();
virtual void b30();
virtual void b31();
virtual void b32();
    virtual void SetStyleId(uint32_t id);                   // slot 33 (+0x84)
virtual void b34();
virtual void b35();
    virtual void OnCursorMoved();                           // slot 36 (+0x90)
virtual void b37();
virtual void b38();
virtual void b39();
virtual void b40();
virtual void b41();
virtual void b42();
virtual void b43();
virtual void b44();
virtual void b45();
virtual void b46();
virtual void b47();
virtual void b48();
virtual void b49();
virtual void b50();
virtual void b51();
virtual void b52();
virtual void b53();
virtual void b54();
virtual void b55();
virtual void b56();
virtual void b57();
virtual void b58();
virtual void b59();
virtual void b60();
virtual void b61();
virtual void b62();
virtual void b63();
    virtual bool OnMouseMoveEvent(int flag);                // slot 64 (+0x100)
virtual void b65();
virtual void b66();
virtual void b67();
virtual void b68();
    virtual void Dispatch(void* msg);                       // slot 69 (+0x114)
};
}
}
namespace EA {
namespace UTFWinControls {
struct Window {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
    virtual ~Window();
    bool Initialize();                                      // 0x0b1fbf0
};
}
}
namespace EA {
namespace UTFWinControls {
class WinTextEdit_s0098_c880;
}
}
namespace EA {
namespace UTFWinControls {
class IWinTextEdit_s0098_c880 { public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual int  GetTextLength();                           // slot 20 (+0x50)
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void SetCursorIndex(uint32_t index, uint32_t extend);   // slot 35 (+0x8c)
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();

    bool mInited;                   // +0x04
    uint32_t mTextEditFlags;        // +0x08
    uint32_t mDirtyFlags;           // +0x0c
    int      mLineWrapMode;         // +0x10
    float mBorderLeft;              // +0x14
    float mBorderTop;               // +0x18
    float mBorderRight;             // +0x1c
    float mBorderBottom;            // +0x20
    float mVisLeft;                 // +0x24
    float mVisTop;                  // +0x28
    float mVisRight;                // +0x2c
    float mVisBottom;               // +0x30
    uint32_t pad34[(0x58 - 0x34) / 4];
    uint32_t mMaxTextLength;        // +0x58
    uint32_t mCursorIndex;          // +0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    ParagraphVector_s0098_c880 mParagraphList; // +0x70
    uint32_t pad7c;
    EA::Text::TextStyle_s0098_c880 mActualStyle;   // +0x80
    int mFontHeight;                // +0x2f8
    int mLineHeight;                // +0x2fc
    UIntVector mLineBreaks;         // +0x300
    uint32_t pad30c[(0x314 - 0x30c) / 4];
    uint32_t mParaBreak;            // +0x314
    uint32_t pad318;
    Deque mUndoList;                // +0x31c
    Deque mRedoList;                // +0x348
    void* mRefObjA;                 // +0x374
    void* mRefObjB;                 // +0x378
    uint32_t pad37c[(0x388 - 0x37c) / 4];
    void* mRefObjC;                 // +0x388
    void* mRefObjD;                 // +0x38c
    uint32_t pad390[(0x39c - 0x390) / 4];
    float mScrollX;                 // +0x39c
    float mScrollY;                 // +0x3a0
    float mTextExtentX;             // +0x3a4
    float mTextExtentY;             // +0x3a8
    uint32_t pad3ac[(0x3cc - 0x3ac) / 4];
    Stopwatch_s0098_c880 mCaretTimer;          // +0x3cc
    float mCaretLeft;               // +0x3e4
    float mCaretTop;                // +0x3e8
    float mCaretRight;              // +0x3ec
    float mCaretBottom;             // +0x3f0
    uint32_t pad3f4[(0x3fc - 0x3f4) / 4];
    Stopwatch_s0098_c880 mDoubleClickTimer;    // +0x3fc
    float mDoubleClickInterval;     // +0x414
    uint32_t pad418[(0x444 - 0x418) / 4];
    int mField650;                  // +0x444

    bool Undo();                                            // 0x98c880
    bool Redo();                                            // 0x98c9d0
};
}
}
namespace EA {
namespace UTFWinControls {
struct TextMsg_s0098_c880 {
    uint32_t w0;                    // +0x00 (uninitialised in the original)
    uint32_t w1;                    // +0x04
    uint32_t type;                  // +0x08
    void*    src;                   // +0x0c
    uint32_t w4;                    // +0x10
    int      length;                // +0x14
    const wchar_t* text;            // +0x18
};
}
}
namespace EA {
namespace UTFWinControls {
class WinTextEdit_s0098_c880 : public Window, public Base4 { public:
    uint32_t pad08[(0x80 - 0x08) / 4];
    void* mPtr80;                   // +0x80
    void* mPtr84;                   // +0x84
    uint32_t pad88[(0xb0 - 0x88) / 4];
    const wchar_t* mTextBegin;      // +0xb0
    const wchar_t* mTextEnd;        // +0xb4
    uint32_t padB8;
    uint32_t mStyleId;              // +0xbc
    uint32_t mStyleId2;             // +0xc0
    uint32_t padC4[(0x20c - 0xc4) / 4];
    IWinTextEdit_s0098_c880 mIWin;             // +0x20c

    EA::Text::Typesetter_s0098_c880* GetTypesetter();                  // 0x95fba0
    void Shutdown();                                        // 0x98c520
    void ShowCaret(bool show);                              // 0x989660
    uint32_t SnapToLine(uint32_t idx, uint32_t flag);       // 0x98a430
    void SelectWordAt(uint32_t idx);                        // 0x98ab40
    void PostEditChange();                                  // 0x9899b0
    float GetBaselineOffset();                              // 0x98b940
    void ApplyUndo(void* action);                           // 0x98bc80
    void ApplyRedo(void* action);                           // 0x98bd00

    bool Init();                                            // 0x98cc70
    ~WinTextEdit_s0098_c880();                                         // 0x98cbb0
    void SetParagraphCache(const Paragraph_s0098_c880* p);             // 0x98cd00
    EA::Text::LineLayout_s0098_c880* LayoutLine(const Paragraph_s0098_c880* p, uint32_t line, uint32_t* outOffset, uint32_t* outChars); // 0x98ceb0
    int HitTest(Paragraph_s0098_c880* p, float* pt, bool flag);        // 0x98cfd0
    void RecalculateLineBreaks();                           // 0x98d110
    int Pick(float x, float y, bool flag);                   // 0x98d320
    bool OnMouseDown(float x, float y, uint32_t a, uint8_t extend); // 0x98d420
    bool OnMouseMove(float x, float y, uint32_t a);         // 0x98d540
    bool OnAutoSize(uint32_t a, float* out);                // 0x98d5b0
};
}
}
// ---- items of slice s0098c880 end

// ---- items of slice s0098d630 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
class IRenderMode;
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0098_d630;
}
}
namespace EA {
namespace UTFWin {
struct Batch2D;
}
}
namespace EA {
namespace UTFWin {
struct RectF {
    float left;                                                     // 0x00
    float top;                                                      // 0x04
    float right;                                                    // 0x08
    float bottom;                                                   // 0x0c
};
}
}
namespace EA {
namespace UTFWinControls {
class WinTextEdit_s0098_d630 {
public:
    // Window base (at this+0x04 is the IWindow*); vtable slots are called by offset.
    uint32_t  pad_000;                                              // 0x000
    EA::UTFWin::IWindow_s0098_d630* mpWindow;                                  // 0x004
    uint32_t  pad_008[0x1e0/4 - 0x008/4 - 1];                       // 0x008..0x1e0
    void*     mpImeComposition;                                     // 0x1e0
    uint32_t  flags_214;                                            // 0x214
    uint32_t  flags_218;                                            // 0x218
    uint32_t  pad_21c[0x230/4 - 0x21c/4];                           // 0x21c..0x230
    EA::UTFWin::RectF visibleRect;                                  // 0x230 text viewport
    uint32_t  pad_240[2];                                           // 0x240..0x248
    void*     mpLayout[4];                                          // 0x244..0x254 (two labelled variants)
    uint32_t  pad_254[0x580/4 - 0x254/4];                           // 0x254..0x580
    void*     mpScrollbarH;                                         // 0x580
    uint32_t  pad_584;                                              // 0x584
    int       mScrollModeA;                                         // 0x588
    uint32_t  pad_58c;                                              // 0x58c
    uint32_t  pad_590;                                              // 0x590
    void*     mpScrollbarV;                                         // 0x594
    uint32_t  pad_598;                                              // 0x598
    int       mScrollModeB;                                         // 0x59c
    uint32_t  pad_5a0[0x5b0/4 - 0x5a0/4];                           // 0x5b0
    float     mMinWidth;                                            // 0x5b0
    float     mMinHeight;                                           // 0x5b4

    void OnRebuild(EA::UTFWin::IRenderMode* mode);                  // 0x0098D630
    void RecalculateLineBreaks();                                   // 0x0098D110
    void CalculateVisibleArea();                                    // 0x00989870
    void FUN_0098dff0();                                            // 0x0098DFF0
};
}
}
namespace EA {
namespace UTFWinControls {
void FUN_0098dff0(WinTextEdit_s0098_d630* self);                               // 0x0098DFF0 (ecx=this)
}
}
namespace EA {
namespace UTFWinControls {
class IWindowSink {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3C();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4C();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5C();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6C();
virtual void vf70();
virtual void vf74();
virtual void vf78();
virtual void vf7C();
};
}
}
namespace EA {
namespace UTFWinControls {
class Batch2D {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0C();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1C();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2C();
virtual void vf30();
virtual void vf34();
    virtual void vf38();
};
}
}
namespace EA {
namespace UTFWinControls {
struct SinkCalls {
    static bool  ShowScrollbar(void* p, int v)     { return ((bool (__thiscall*)(void*, int))((void**)*(void**)p)[0xfc/4])(p, v); }
    static int   GetWrapFlags(void* p)             { return ((int  (__thiscall*)(void*))((void**)*(void**)p)[0x28/4])(p); }
    static void* GetSink(void* p)                  { return ((void*(__thiscall*)(void*))((void**)*(void**)p)[0x14/4])(p); }
    static void* GetCaret(void* p, int v)          { return ((void*(__thiscall*)(void*, int))((void**)*(void**)p)[0x54/4])(p, v); }
    static void  SetVisible(void* p, int a, int b) { ((void (__thiscall*)(void*, int, int))((void**)*(void**)p)[0x7c/4])(p, a, b); }
    static void  Add(void* p, void* o)             { ((void (__thiscall*)(void*, void*))((void**)*(void**)p)[0x04/4])(p, o); }
    static void  DrawRect(void* p, float a, float b, float c, float d) {
        ((void (__thiscall*)(void*, float, float, float, float))((void**)*(void**)p)[0x38/4])(p, a, b, c, d); }
    static void  SetClipRect(void* p, void* r)     { ((void (__thiscall*)(void*, void*))((void**)*(void**)p)[0x14/4])(p, r); }
};
}
}
extern "C" EA::UTFWin::Batch2D* RenderCtxBegin2D(EA::UTFWin::IRenderMode* mode); // 0x0095BC10
namespace EA {
namespace UTFWinControls {
float RectHeight(const EA::UTFWin::RectF* r) { return r->bottom - r->top; }
}
}
namespace EA {
namespace UTFWinControls {
float RectWidth(const EA::UTFWin::RectF* r)  { return r->right - r->left; }
}
}
// ---- items of slice s0098d630 end

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

// @ 0x00989240
void __thiscall WinText::m_989240(uint32_t p2)
{
    uint32_t buf[7];
    buf[2] = 0x9b1552db;
    uint32_t v = F(this, 0x84);
    if (v == 0) v = F(this, 0x80);
    buf[3] = v;
    Iface* iface = (Iface*)((uint8_t*)this + 4);
    void (__thiscall* fn)(void*, void*) =
        *(void (__thiscall**)(void*, void*))((void**)*(void**)iface + (0x114 / 4));
    buf[4] = p2;
    fn(iface, buf);
}

// @ 0x00989290
uint32_t __thiscall WinText::m_989290(uint32_t i)
{
    if (i <= 7) return F(this, 0x38 + i * 4);
    return 0;
}

// @ 0x009892b0
void __thiscall WinText::m_9892b0(uint32_t i, uint32_t v)
{
    if (i <= 7 && F(this, 0x38 + i * 4) != v) {
        F(this, 0x38 + i * 4) = v;
        ((SubWin*)((uint8_t*)this - 0x208))->c36();
    }
}

// @ 0x00989370
void __thiscall WinText::m_989370(uint32_t v)
{
    if (v != F(this, 0x58)) {
        WinBase* b = (WinBase*)this;
        F(this, 0x58) = v;
        b->v30(v, -1, 0, 0, 1);
    }
}

// @ 0x00989390
void __thiscall WinText::m_989390(uint32_t a, uint32_t b, uint32_t c)
{
    ((WinBase*)this)->v30(F(this, 0x5c), 0, a, b, c);
}

// @ 0x009893b0
void __thiscall WinText::m_9893b0(uint32_t a, uint32_t b)
{
    ((WinBase*)this)->v30(F(this, 0x5c), a, 0, 0, b);
}

// @ 0x009893d0
void __thiscall WinText::m_9893d0(uint32_t a)
{
    ((WinBase*)this)->v30(0, -1, 0, 0, a);
}

// @ 0x00989410
void __thiscall WinText::m_989410(uint32_t a, uint8_t flag)
{
    WinBase* b = (WinBase*)this;
    if (flag) {
        b->v37(a, F(this, 0x60));
    } else {
        b->v37(a, a);
    }
}

// @ 0x00989450
int __thiscall WinText::m_989450(int, int, int, int, int)
{
    return -1;
}

// @ 0x00989460
void __thiscall WinText::m_989460(uint32_t v)
{
    F(this, 0xc) |= 4;
    F(this, 0x10) = v;
}

// @ 0x009894a0
uint32_t __thiscall WinText::m_9894a0(uint32_t i)
{
    return F(this, 0x37c + i * 0x14);
}

// @ 0x009894c0
char __thiscall WinText::m_9894c0(int, int, int, int)
{
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    if (sub->s64(1)) {
        void* o = sub->s05();
        ((void (__thiscall*)(void*, uint32_t, void*))((void**)*(void**)o)[0x5c / 4])(o, 1, sub);
    }
    return 1;
}

// @ 0x00989500
uint32_t __thiscall WinText::m_989500(uint32_t p2, uint32_t p3)
{
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    uint32_t r = sub->s10() >> 4;
    if (r & 1) {
        return r & 0xffffff00;
    }
    switch (p3) {
    case 8: case 0xd: case 0x1b: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25: case 0x26: case 0x27: case 0x28: case 0x2e:
    case 0x6a: case 0x6b: case 0x6d: case 0x6e: case 0x6f:
    case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbe: case 0xbf: case 0xc0:
    case 0xdb: case 0xdc: case 0xde:
        return 1;
    case 0x2d:
        return ((uint32_t)*(uint8_t*)((uint8_t*)this + 0x214) >> 2) & 1;
    default:
        if ((p3 < 0x41 || p3 > 0x5a) && p3 - 0x30 > 9) {
            return r & 0xffffff00;
        }
        return 1;
    }
}

// @ 0x00989660
void __thiscall WinText::m_989660(uint8_t p2)
{
    uint8_t b;
    if (F(this, 0x2c) & 1) b = p2; else b = 0;
    if (F(this, 0x214) & 0x21) b = 0;
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    if (!sub->s63(0)) {
        b = 0;
    }
    if (b != *(uint8_t*)((uint8_t*)this + 0x600)) {
        *(uint8_t*)((uint8_t*)this + 0x600) = b;
        sub->s36();
    }
}

// @ 0x009896d0
extern "C" char __cdecl sub_9896d0(uint32_t* out, int p2, int p3, uint32_t* allocObj)
{
    uint8_t* c = (uint8_t*)p3;
    uint32_t* src = (uint32_t*)(*(uint8_t**)((uint8_t*)p2 + 4) + *(int*)(c + 0x10));
    uint32_t* dst = (uint32_t*)((AllocIface_9896d0*)allocObj)->alloc(*(int*)(c + 0x14) * 4, 4);
    if (dst != 0) {
        out[1] = (uint32_t)dst;
        out[2] = *(uint32_t*)(c + 0x14);
        out[0] = ((uint32_t*)0x154eea0)[*(uint16_t*)(c + 0xc) & 0xfff];
        uint32_t* s = src;
        uint32_t* d = dst;
        for (uint32_t i = 0; i < *(uint32_t*)(c + 0x14); i++) {
            *d++ = *s++;
        }
        return 1;
    }
    return 0;
}

// @ 0x00989740
extern "C" void __cdecl sub_989740(uint32_t* first, uint32_t* last, uint32_t* dest)
{
    while (first != last) {
        if (dest != 0) {
            dest[0] = first[0];
            dest[1] = first[1];
            dest[2] = first[2];
            *(float*)(dest + 3) = *(float*)(first + 3);
            *(float*)(dest + 4) = *(float*)(first + 4);
            *(float*)(dest + 5) = *(float*)(first + 5);
        }
        first += 6;
        dest += 6;
    }
}

// @ 0x00989790
extern "C" void __cdecl sub_989790(uint32_t* first, uint32_t* last, uint32_t* dest)
{
    while (first != last) {
        dest[0] = first[0];
        dest[1] = first[1];
        dest[2] = first[2];
        *(float*)(dest + 3) = *(float*)(first + 3);
        *(float*)(dest + 4) = *(float*)(first + 4);
        *(float*)(dest + 5) = *(float*)(first + 5);
        first += 6;
        dest += 6;
    }
}

// @ 0x009897d0
extern "C" void __cdecl sub_9897d0(uint32_t* first, uint32_t* last, uint32_t* destEnd)
{
    while (last != first) {
        last -= 6;
        destEnd -= 6;
        destEnd[0] = last[0];
        destEnd[1] = last[1];
        destEnd[2] = last[2];
        *(float*)(destEnd + 3) = *(float*)(last + 3);
        *(float*)(destEnd + 4) = *(float*)(last + 4);
        *(float*)(destEnd + 5) = *(float*)(last + 5);
    }
}

// @ 0x0098a820
namespace EA { namespace UTFWinControls {
void WinTextEdit::FindSentenceEnd(unsigned pos)
{
    unsigned n = TextLength();
    int state = 0;
    if (pos >= n) goto tail;
    do {
        wchar_t c = textBegin[pos];
        pos++;
        switch (c) {
        case 10:
        case 0xd:
            state = 3;
            break;
        case 0x21:
        case 0x2e:
        case 0x3a:
        case 0x3b:
        case 0x3f:
            if (state == 3) goto done;
            state = 2;
            break;
        default:
            if (state == 3) goto done;
            if (iswctype(c, 8)) {
                if (state == 2) state = 1;
            } else {
                if (state == 1) goto done;
                state = 0;
            }
            break;
        }
    } while (pos < n);
    SnapIndex(pos, 0);
    return;
done:
    pos--;
tail:
    SnapIndex(pos, 0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098a910
namespace EA { namespace UTFWinControls {
void WinTextEdit::FindWordStart(unsigned pos)
{
    unsigned wasWord = 0;
    int found = -1;
    while (pos > 0) {
        wchar_t c = textBegin[pos - 1];
        pos--;
        switch (c) {
        case 10:
        case 0xd:
            if (found != -1) {
                SnapIndex(found, 0);
                return;
            }
            break;
        case 0x21:
        case 0x2e:
        case 0x3a:
        case 0x3b:
        case 0x3f:
            if (found != -1 && wasWord == 1) {
                SnapIndex(found, 0);
                return;
            }
            break;
        default:
            if (iswctype(c, 8)) {
                wasWord = 1;
                continue;
            }
            found = pos;
            break;
        }
        wasWord = 0;
    }
    SnapIndex(pos, 0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098a9f0
namespace EA { namespace UTFWinControls {
void WinTextEdit::FindLineEnd(unsigned pos)
{
    unsigned n = TextLength();
    if (pos < n) {
        const wchar_t* p = textBegin + pos;
        do {
            if (*p == 10) {
                SnapIndex(pos + 1, 0);
                return;
            }
            if (*p == 0xd) {
                if (pos + 1 < n && textBegin[pos + 1] == 10) {
                    SnapIndex(pos + 2, 0);
                    return;
                }
                SnapIndex(pos + 1, 0);
                return;
            }
            pos++;
            p++;
        } while (pos < n);
    }
    SnapIndex(n, 0);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098aa80
namespace EA { namespace UTFWinControls {
unsigned WinTextEdit::FindLineStart(unsigned pos)
{
    if (pos != 0) {
        const wchar_t* text = textBegin;
        if (text[pos - 1] == 10) pos--;
        if (pos != 0) {
            if (text[pos - 1] == 0xd) pos--;
            if (pos != 0) {
                const wchar_t* p = text + pos - 1;
                do {
                    if (*p == 0xd || *p == 10) {
                        Text::TextRun run;
                        run.text = text;
                        run.style = GetTextStyle();
                        Text::CharacterBreakIterator it;
                        it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
                        it.f1c = 0;
                        it.SetPosition(pos);
                        it.GetNextCharBreak();
                        return it.GetPrevCharBreak();
                    }
                    if (pos != 0 && *p == 0xd) {
                        pos--;
                        p--;
                    }
                    pos--;
                    p--;
                } while (pos != 0);
            }
        }
    }
    return 0;
}
}}  // namespace EA::UTFWinControls

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
    // retail keeps `shift` in a byte slot and pushes the whole dword over it, so the upper
    // three bytes are the harness stack fill (0xcc) rather than a zero-extended 1
    uint32_t extend;
    *(uint8_t*)&extend = (uint8_t)shift;
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
        if (!MoveCursor(2, -1, (int)extend)) { Error(4); return true; }
        return true;
    case 0x28: // down
        if (lineMode == 0) return true;
        if (!selectable) return true;
        if (!MoveCursor(2, 1, (int)extend)) { Error(4); return true; }
        return true;
    case 0x25: // left
    case 0x27: { // right
        if (!selectable) return true;
        int type = 0;
        if (ctrl) type = (alt ? 1 : 0) * 2 + 1;
        else if (alt) type = 4;
        if (!MoveCursor(type, key == 0x25 ? -1 : 1, (int)extend)) {
            Error(4);
            return true;
        }
        return true;
    }
    case 0x24: // home
        if (!alt && !ctrl) {
            MoveCursor(6, 0, (int)extend);
            return true;
        }
        MoveCursor(8, 0, (int)extend);
        return true;
    case 0x23: // end
        if (!alt && !ctrl) {
            MoveCursor(7, 0, (int)extend);
            return true;
        }
        MoveCursor(9, 0, (int)extend);
        return true;
    case 0x21: // page up
        if (!selectable) return true;
        if (!MoveCursor(5, -1, (int)extend)) { Error(4); return true; }
        return true;
    case 0x22: // page down
        if (!selectable) return true;
        if (!MoveCursor(5, 1, (int)extend)) { Error(4); return true; }
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

// @ 0x0098b910
namespace EA { namespace UTFWinControls {
const Paragraph_s0098_b910* WinTextEdit_s0098_b910::FindParagraphByTextIndex(unsigned idx)
{
    TextIndexComparator_s0098_b910 cmp = { 0 };
    return (const Paragraph_s0098_b910*)((const char*)UpperBoundByIndexC(paragraphs.mpBegin, paragraphs.mpEnd, idx, cmp) - 0x18);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098b940
namespace EA { namespace UTFWinControls {
int WinTextEdit_s0098_b910::GetVAlignmentOffset()
{
    float base = textExtentY;
    const Paragraph_s0098_b910* first = UpperBoundByY(paragraphs.mpBegin, paragraphs.mpEnd, base);
    float target = (areaBottom - areaTop) + base;
    const Paragraph_s0098_b910* last = UpperBoundByY(paragraphs.mpBegin, paragraphs.mpEnd, target);

    float acc = 0.0f;
    for (const Paragraph_s0098_b910* p = (const Paragraph_s0098_b910*)((const char*)first - 0x18); p != last;
         p = (const Paragraph_s0098_b910*)((const char*)p + 0x18)) {
        if (acc != p->yPos) acc = (p->yPos - acc) + acc;
        acc = p->extentY + acc;
    }

    if (acc <= (areaBottom - areaTop) ||
        ((unsigned)(((const char*)last - (const char*)first) / 0x18) == 1 &&
         ((const Paragraph_s0098_b910*)((const char*)first - 0x18))->textLines == 1)) {
        if (valignMode == 1) return (unsigned)(((areaBottom - areaTop) - acc) * 0.5f);
        if (valignMode == 2) return (unsigned)((areaBottom - areaTop) - acc);
    }
    return (unsigned)acc;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098bab0
namespace EA { namespace UTFWinControls {
void ParagraphVector::reserve(unsigned n)
{
    if ((unsigned)(((char*)mpCap - (char*)mpBegin) / 0x18) < n) {
        Paragraph_s0098_b910* mem;
        if (n == 0) {
            mem = 0;
        } else {
            mem = (Paragraph_s0098_b910*)operator_new(n * 0x18, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        }
        ParagraphRelocate(mpBegin, mpEnd, mem);
        Paragraph_s0098_b910* old = mpBegin;
        if (old != 0 && ((int*)old)[-1] != 0) operator_delete__(old);
        mpBegin = mem;
        mpEnd = (Paragraph_s0098_b910*)((char*)mem + ((unsigned)((char*)mpEnd - (char*)old) / 0x18) * 0x18);
        mpCap = (Paragraph_s0098_b910*)((char*)mem + n * 0x18);
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098bb60
namespace EA { namespace UTFWinControls {
void DequeBase::push_back(void* const& value)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098bbd0
namespace EA { namespace UTFWinControls {
int IWinTextEdit_s0098_b910::GetText(void* out, unsigned idx, unsigned n)
{
    unsigned len = (unsigned)((TextEnd() - TextBegin()) >> 1);
    if (idx >= len) return 0;
    unsigned avail = len - idx;
    const unsigned& c = (avail < n) ? avail : n;
    const wchar_t* p = (const wchar_t*)TextBegin() + idx;
    WString_Assign(out, 0, p, p + c);
    return (int)c;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098bc20
namespace EA { namespace UTFWinControls {
UndoAction* UndoAction::scalar_deleting_destructor(unsigned flags)
{
    uint32_t* oB = (uint32_t*)((char*)this + 0x14);
    uint32_t* nB = (uint32_t*)((char*)this + 4);
    int ocnt = (int)(oB[2] - oB[0]) & 0xfffffffe;
    if (ocnt > 2 && oB[0] != 0) operator_delete__((void*)oB[0]);
    int ncnt = (int)(nB[2] - nB[0]) & 0xfffffffe;
    if (ncnt > 2 && nB[0] != 0) operator_delete__((void*)nB[0]);
    if (flags & 1) operator_delete__(this);
    return this;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098bc80
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_b910::ApplyUndoRedo(UndoAction* a)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098bd00
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_b910::ApplyRedoUndo(UndoAction* a)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098bd80
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_b910::TrimUndoList(unsigned n)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098bea0
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_b910::TrimRedoList(unsigned n)
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098bfc0
namespace EA { namespace UTFWinControls {
void ParagraphVector::insert(Paragraph_s0098_b910* pos, const Paragraph_s0098_b910& value)
{
    if (pos != mpEnd) {
        Paragraph_s0098_b910* v = (Paragraph_s0098_b910*)&value;
        if (pos <= v && v < mpEnd) v = (Paragraph_s0098_b910*)((char*)v + 0x18);
        if (mpEnd != 0) {
            mpEnd[0] = *(Paragraph_s0098_b910*)((char*)mpEnd - 0x18);
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
    Paragraph_s0098_b910* mem = (Paragraph_s0098_b910*)operator_new(cap * 0x18, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    Paragraph_s0098_b910* p = (Paragraph_s0098_b910*)ParagraphRelocate(mpBegin, pos, mem);
    if (p != 0) *p = value;
    Paragraph_s0098_b910* e = (Paragraph_s0098_b910*)ParagraphRelocate(pos, mpEnd, (char*)p + 0x18);
    Paragraph_s0098_b910* old = mpBegin;
    if (old != 0 && ((int*)old)[-1] != 0) operator_delete__(old);
    mpBegin = mem;
    mpEnd = e;
    mpCap = (Paragraph_s0098_b910*)((char*)mem + cap * 0x18);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098c110
namespace EA { namespace UTFWinControls {
WinTextEdit_s0098_b910::WinTextEdit_s0098_b910()
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098c4b0
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_b910::SerUpdate()
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098c520
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_b910::Shutdown()
{
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
}}  // namespace EA::UTFWinControls

// @ 0x0098c5a0
namespace EA { namespace UTFWinControls {
int WinTextEdit_s0098_b910::Replace(void* src, unsigned count0, unsigned count1, unsigned count2, unsigned rem)
{
    int len = (int)((*(uint32_t*)((char*)this - 0x158) - *(uint32_t*)((char*)this - 0x15c)) >> 1);
    const unsigned& idx = ((unsigned)len < count0) ? *(const unsigned*)&len : count0;
    unsigned avail = (unsigned)len - idx;
    const unsigned& cnt = (avail < count1) ? avail : count1;
    if (cnt == 0 && count2 == 0) return 0;

    unsigned newLen = ((unsigned)len - cnt) + rem;
    if (newLen > (unsigned)len && newLen > *(uint32_t*)((char*)this + 0x58)) {
        WinText_Error((WinTextEdit_s0098_b910*)((char*)this - 0x20c), 3);
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
    WinTextEdit_s0098_b910* self = (WinTextEdit_s0098_b910*)((char*)this - 0x20c);
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
}}  // namespace EA::UTFWinControls

// @ 0x0098c860
namespace EA { namespace UTFWinControls {
void IWinTextEdit_s0098_b910::SetUndoHistorySize(unsigned n)
{
    *(uint32_t*)((char*)this + 0x318) = n;
    WIN(this)->TrimUndoList(n);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098c880
namespace EA { namespace UTFWinControls {
bool IWinTextEdit_s0098_c880::Undo()
{
    if (mUndoList.mpCurrent == mUndoList.mpEndCurrent)
        return false;
    void* action = mUndoList.pop_front();
    WinTextEdit_s0098_c880* te = (WinTextEdit_s0098_c880*)((char*)this - 0x20c);
    te->ApplyUndo(action);
    mRedoList.push_front(action);

    Base4* b4 = (Base4*)te;
    mDirtyFlags |= 7;
    b4->OnCursorMoved();

    TextMsg_s0098_c880 msg;
    msg.type = 0x9b1552d8;
    void* src = te->mPtr84;
    if (!src)
        src = te->mPtr80;
    msg.src = src;
    msg.length = (int)(float)(uint32_t)(te->mTextEnd - te->mTextBegin);
    msg.text = te->mTextBegin;
    b4->Dispatch(&msg);
    te->PostEditChange();
    return true;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098c9d0
namespace EA { namespace UTFWinControls {
bool IWinTextEdit_s0098_c880::Redo()
{
    if (mRedoList.mpCurrent == mRedoList.mpEndCurrent)
        return false;
    void* action = mRedoList.pop_front();
    WinTextEdit_s0098_c880* te = (WinTextEdit_s0098_c880*)((char*)this - 0x20c);
    te->ApplyRedo(action);
    mUndoList.push_front(action);

    Base4* b4 = (Base4*)te;
    mDirtyFlags |= 7;
    b4->OnCursorMoved();

    TextMsg_s0098_c880 msg;
    msg.type = 0x9b1552d8;
    void* src = te->mPtr84;
    if (!src)
        src = te->mPtr80;
    msg.src = src;
    msg.length = (int)(float)(uint32_t)(te->mTextEnd - te->mTextBegin);
    msg.text = te->mTextBegin;
    b4->Dispatch(&msg);
    te->PostEditChange();
    return true;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098cb20
namespace EA { namespace UTFWinControls {
void ParagraphVector_s0098_c880::push_back(const Paragraph_s0098_c880& v)
{
    Paragraph_s0098_c880* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 1;
        if (e) {
            e->mTextIndex = v.mTextIndex;
            e->mTextLength = v.mTextLength;
            e->mTextLines = v.mTextLines;
            e->mExtentX = v.mExtentX;
            e->mExtentY = v.mExtentY;
            e->mYPos = v.mYPos;
        }
    } else {
        DoInsertValue(e, v);
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098cbb0
namespace EA { namespace UTFWinControls {
WinTextEdit_s0098_c880::~WinTextEdit_s0098_c880()
{
    if (mIWin.mInited)
        Shutdown();
    if (mIWin.mRefObjD)
        ((RefObj*)mIWin.mRefObjD)->Release();
    if (mIWin.mRefObjC)
        ((RefObj*)mIWin.mRefObjC)->Release();
    if (mIWin.mRefObjB)
        ((RefObj*)mIWin.mRefObjB)->Release();
    if (mIWin.mRefObjA)
        ((RefObj*)mIWin.mRefObjA)->Release();
    mIWin.mRedoList.Destroy();
    mIWin.mUndoList.Destroy();
    if (mIWin.mLineBreaks.mpBegin && ((uint32_t*)mIWin.mLineBreaks.mpBegin)[-1] != 0)
        MemFree(mIWin.mLineBreaks.mpBegin);
    if (mIWin.mParagraphList.mpBegin && ((uint32_t*)mIWin.mParagraphList.mpBegin)[-1] != 0)
        MemFree(mIWin.mParagraphList.mpBegin);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098cc70
namespace EA { namespace UTFWinControls {
bool WinTextEdit_s0098_c880::Init()
{
    if (!mIWin.mInited) {
        if (Initialize()) {
            mIWin.mParagraphList.reserve(0x10);
            Paragraph_s0098_c880 p;
            p.mTextIndex = 0;
            p.mTextLength = 0;
            mIWin.mParagraphList.push_back(p);
            ((Base4*)this)->SetStyleId(mStyleId2);
            mIWin.mDirtyFlags |= 5;
            ShowCaret(true);
            mIWin.mCaretTimer.Restart();
            mIWin.mInited = 1;
        }
    }
    return mIWin.mInited;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098cd00
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_c880::SetParagraphCache(const Paragraph_s0098_c880* p)
{
    VectorClear(mIWin.mLineBreaks.mpBegin, mIWin.mLineBreaks.mpEnd, 0);
    mIWin.mLineBreaks.mpEnd = mIWin.mLineBreaks.mpBegin;

    Paragraph_s0098_c880* para = (Paragraph_s0098_c880*)p;
    para->mExtentX = 0.0f;
    para->mExtentY = 0.0f;

    EA::Text::Typesetter_s0098_c880* ts = GetTypesetter();
    ts->Reset(true);
    ts->SetStyle(&mIWin.mActualStyle.d[1]);
    ts->AddTextRun(mTextBegin + para->mTextIndex, para->mTextLength);
    ts->SetBounds((mIWin.mVisRight - mIWin.mVisLeft) - (mIWin.mCaretRight - mIWin.mCaretLeft),
                  mIWin.mVisLeft, 0.0f);

    uint32_t offset = 0;
    if (ts->GetState() != 2) {
        do {
            ts->FinalizeLine();
            EA::Text::LineLayout_s0098_c880* layout = ts->GetLineLayout();
            uint32_t len = (uint32_t)(layout->mEnd - layout->mBegin);
            para->mExtentY = (float)mIWin.mLineHeight + para->mExtentY;
            if (layout->mExtentX > para->mExtentX)
                para->mExtentX = layout->mExtentX;
            mIWin.mLineBreaks.push_back(offset);
            offset += len;
            ts->NextLine(false);
        } while (ts->GetState() != 2);
    }
    mIWin.mParaBreak = offset;
    para->mTextLines = (int)(mIWin.mLineBreaks.mpEnd - mIWin.mLineBreaks.mpBegin);
}
}}  // namespace EA::UTFWinControls

// @ 0x0098ceb0
namespace EA { namespace UTFWinControls {
EA::Text::LineLayout_s0098_c880* WinTextEdit_s0098_c880::LayoutLine(const Paragraph_s0098_c880* p, uint32_t line, uint32_t* outOffset, uint32_t* outChars)
{
    VectorClear(mIWin.mLineBreaks.mpBegin, mIWin.mLineBreaks.mpEnd, 0);
    mIWin.mLineBreaks.mpEnd = mIWin.mLineBreaks.mpBegin;

    EA::Text::Typesetter_s0098_c880* ts = GetTypesetter();
    ts->Reset(true);
    ts->SetStyle(&mIWin.mActualStyle.d[1]);
    ts->AddTextRun(mTextBegin + p->mTextIndex, p->mTextLength);
    ts->SetBounds((mIWin.mVisRight - mIWin.mVisLeft) - (mIWin.mCaretRight - mIWin.mCaretLeft),
                  mIWin.mVisLeft, 0.0f);

    *outOffset = 0;
    EA::Text::LineLayout_s0098_c880* layout = ts->GetLineLayout();
    int state = ts->GetState();
    while (state != 2) {
        ts->FinalizeLine();
        *outChars = (uint32_t)(layout->mEnd - layout->mBegin);
        if ((int)line <= 0)
            break;
        *outOffset += *outChars;
        ts->NextLine(false);
        --line;
        state = ts->GetState();
    }
    return ts->GetLineLayout();
}
}}  // namespace EA::UTFWinControls

// @ 0x0098cfd0
namespace EA { namespace UTFWinControls {
int WinTextEdit_s0098_c880::HitTest(Paragraph_s0098_c880* p, float* pt, bool flag)
{
    int line = (int)Floor((double)(pt[1] / (float)mIWin.mLineHeight));
    uint32_t outOffset, outChars;
    EA::Text::LineLayout_s0098_c880* layout = LayoutLine(p, (uint32_t)line, &outOffset, &outChars);

    if (pt[0] < 0.0f) {
        if (!flag)
            return -1;
        return (int)SnapToLine(outOffset, 0);
    }
    uint32_t idx = outOffset;
    if (outChars > 0) {
        int out;
        idx += (uint32_t)layout->HitTest(pt[0], pt[1], 0, 0, &out, 0);
    }
    if (idx != (uint32_t)mIWin.GetTextLength())
        idx = SnapToLine(idx, 0);
    if (outChars > 1 && idx > 0 && mTextBegin[idx - 1] == L'\n')
        --idx;
    return (int)idx;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098d110
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_c880::RecalculateLineBreaks()
{
    mIWin.mDirtyFlags &= ~4u;

    int textLen = (int)(mTextEnd - mTextBegin);
    int wrap = mIWin.mLineWrapMode;
    if (wrap >= 0) {
        if (wrap <= 1)
            mIWin.mActualStyle.d[0x95] = 0;
        else if (wrap == 2)
            mIWin.mActualStyle.d[0x95] = 4;
    }

    Paragraph_s0098_c880* begin = mIWin.mParagraphList.mpBegin;
    Paragraph_s0098_c880* end = mIWin.mParagraphList.mpEnd;
    RebuildParagraphs(end, end, begin);
    mIWin.mParagraphList.mpEnd = mIWin.mParagraphList.mpEnd + (end - begin);

    EA::Text::TextRunInfo run;
    run.text = mTextBegin;
    run.length = (uint32_t)textLen;
    EA::Text::TextRunIterator_s0098_c880 it;
    it.SetTextRunArray(&run, 1, 0, 0, -1);
    it.pad1c = 0;
    uint32_t prev = 0;
    while (it.mnPosition != it.mnEndPosition) {
        uint32_t pos = it.Next();
        Paragraph_s0098_c880 p;
        p.mTextIndex = prev;
        p.mTextLength = pos - prev;
        mIWin.mParagraphList.push_back(p);
        prev = pos;
    }

    bool append;
    if (mIWin.mParagraphList.mpBegin == mIWin.mParagraphList.mpEnd) {
        append = true;
    } else {
        const Paragraph_s0098_c880* last = mIWin.mParagraphList.mpEnd - 1;
        append = last->mTextLength > 0 &&
                 mTextBegin[last->mTextIndex + last->mTextLength - 1] == L'\n';
    }
    if (append) {
        Paragraph_s0098_c880 p;
        p.mTextIndex = (uint32_t)textLen;
        p.mTextLength = 0;
        mIWin.mParagraphList.push_back(p);
    }

    EA::Text::Typesetter_s0098_c880* ts = GetTypesetter();
    ts->Reset(true);
    ts->SetStyle(&mIWin.mActualStyle.d[1]);

    mIWin.mTextExtentX = 0.0f;
    mIWin.mTextExtentY = 0.0f;
    Paragraph_s0098_c880* pend = mIWin.mParagraphList.mpEnd;
    for (Paragraph_s0098_c880* p = mIWin.mParagraphList.mpBegin; p != pend; ++p) {
        p->mYPos = mIWin.mTextExtentY;
        SetParagraphCache(p);
        if (p->mExtentX > mIWin.mTextExtentX)
            mIWin.mTextExtentX = p->mExtentX;
        mIWin.mTextExtentY = p->mExtentY + mIWin.mTextExtentY;
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098d320
namespace EA { namespace UTFWinControls {
int WinTextEdit_s0098_c880::Pick(float x, float y, bool flag)
{
    if (mIWin.mDirtyFlags & 4)
        RecalculateLineBreaks();
    x += mIWin.mScrollX;
    float yy = (mIWin.mScrollY - GetBaselineOffset()) + y;
    if (yy < 0.0f)
        return flag ? 0 : -1;
    if (yy < mIWin.mTextExtentY) {
        const Paragraph_s0098_c880* p = UpperBoundY_s0098_c880(mIWin.mParagraphList.mpBegin, mIWin.mParagraphList.mpEnd, yy, YPosComparator()) - 1;
        SetParagraphCache(p);
        float pt[2];
        pt[0] = x;
        pt[1] = yy;
        return HitTest((Paragraph_s0098_c880*)p, pt, flag) + (int)p->mTextIndex;
    }
    if (flag)
        return (int)(mTextEnd - mTextBegin);
    return -1;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098d420
namespace EA { namespace UTFWinControls {
bool WinTextEdit_s0098_c880::OnMouseDown(float x, float y, uint32_t a, uint8_t extend)
{
    bool dbl = ((mIWin.mTextEditFlags >> 6) & 1) || !(mIWin.mTextEditFlags & 1);
    int idx = Pick(x, y, 1);
    if (!dbl)
        return true;
    if (mIWin.mDoubleClickTimer.mStart != 0) {
        uint64_t elapsed = mIWin.mDoubleClickTimer.GetElapsedTime();
        dbl = (double)mIWin.mDoubleClickInterval > (double)elapsed;
    } else {
        dbl = false;
    }
    mIWin.mDoubleClickTimer.Restart();
    if (idx == -1)
        return true;
    if (dbl && idx == (int)mIWin.mCursorIndex) {
        SelectWordAt((uint32_t)idx);
        return true;
    }
    mIWin.SetCursorIndex((uint32_t)idx, extend & 1);
    Base4* b4 = (Base4*)this;
    Base4Obj* o = b4->GetObj();
    o->Notify(1, b4);
    return true;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098d540
namespace EA { namespace UTFWinControls {
bool WinTextEdit_s0098_c880::OnMouseMove(float x, float y, uint32_t a)
{
    if (OnMouseMoveEvent(1) &&
        (((mIWin.mTextEditFlags >> 6) & 1) || !(mIWin.mTextEditFlags & 1))) {
        int idx = Pick(x, y, 1);
        mIWin.SetCursorIndex((uint32_t)idx, 1);
    }
    return true;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098d5b0
namespace EA { namespace UTFWinControls {
bool WinTextEdit_s0098_c880::OnAutoSize(uint32_t a, float* out)
{
    RecalculateLineBreaks();
    if (mIWin.mMaxTextLength != 0xffffffffu)
        out[0] = (float)(uint32_t)(mIWin.mMaxTextLength * 10u);
    else
        out[0] = 200.0f;
    out[1] = (float)(uint32_t)mIWin.mField650 + mIWin.mLineHeight + mIWin.mBorderBottom + mIWin.mBorderTop;
    return true;
}
}}  // namespace EA::UTFWinControls

// @ 0x0098d630
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_d630::OnRebuild(EA::UTFWin::IRenderMode* mode)
{
    Batch2D* batch = (Batch2D*)RenderCtxBegin2D(mode);
    float dx0 = 0.0f, dy0 = 0.0f;
    float dw = RectWidth(&visibleRect);
    float dh = RectHeight(&visibleRect);

    IWindowSink* win = (IWindowSink*)mpWindow;
    bool vertical = SinkCalls::ShowScrollbar(win, 0);
    bool wrap = (SinkCalls::GetWrapFlags(win) >> 1) & 1;

    bool visible = true;
    if (!vertical && (flags_214 & 0x10))
        visible = false;
    if (flags_218 & 4)
        RecalculateLineBreaks();

    if (mpImeComposition != 0) {
        void* sink = SinkCalls::GetSink(win);
        bool atEnd = (SinkCalls::GetCaret(sink, 1) == (void*)win);
        int style = 0;
        if (!wrap)
            style = 1;
        else if (atEnd)
            style = 3;
        SinkCalls::SetClipRect(mpImeComposition, &visibleRect);
        SinkCalls::SetVisible(mpImeComposition, style, 0);
    } else {
        void* layout = mpLayout[wrap ? 1 : 3];
        if (layout != 0) {
            SinkCalls::Add(batch, layout);
            SinkCalls::DrawRect(batch, dx0, dy0, dw, dh);
        }
    }

    SinkCalls::SetClipRect(batch, &visibleRect);
    if (mpScrollbarV != 0) {
        (void)vertical;
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x0098dff0
namespace EA { namespace UTFWinControls {
void WinTextEdit_s0098_d630::FUN_0098dff0()
{
    float oldX0 = visibleRect.left;
    float oldY0 = visibleRect.top;
    float oldX1 = visibleRect.right;
    float oldY1 = visibleRect.bottom;

    bool vVisibleEye;
    if (mScrollModeB == 2) {
        vVisibleEye = true;
    } else if (mScrollModeB == 1) {
        float h = visibleRect.bottom - visibleRect.top;
        vVisibleEye = !(mMinHeight > h);
    } else {
        vVisibleEye = false;
    }

    if (mpScrollbarV != 0) {
        void* sb = SinkCalls::GetSink(mpScrollbarV);
        SinkCalls::SetVisible(sb, 1, vVisibleEye);
    }

    CalculateVisibleArea();

    if (visibleRect.left != oldX0 || visibleRect.top != oldY0 ||
        visibleRect.right != oldX1 || visibleRect.bottom != oldY1) {
        RecalculateLineBreaks();
    }

    bool hVisibleEye;
    if (mScrollModeA == 2) {
        hVisibleEye = true;
    } else if (mScrollModeA == 1) {
        float w = visibleRect.right - visibleRect.left;
        hVisibleEye = !(mMinWidth > w);
    } else {
        hVisibleEye = false;
    }

    if (mpScrollbarH != 0) {
        void* sb = SinkCalls::GetSink(mpScrollbarH);
        SinkCalls::SetVisible(sb, 1, hVisibleEye);
    }
}
}}  // namespace EA::UTFWinControls

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
