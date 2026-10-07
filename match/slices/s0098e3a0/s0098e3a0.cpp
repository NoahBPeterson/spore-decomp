// UTFWinControls::WinTextEdit / IWinTextEdit (0x98e3a0-0x98f330) and WinTreeView::Init (0x98f3d0).
// Retail layout is the 2008 PDB layout shifted (+0x14 from mDirtyFlags on), so offsets come from the
// disassembly. IWinTextEdit is a polymorphic secondary base embedded at WinTextEdit+0x20c; the fields
// that the PDB lists on WinTextEdit live at the offsets below relative to it (named after the PDB).
#include "types.h"
#include <stddef.h>

#pragma pack(4)
#define CHK(name, expr) typedef char chk_##name[(expr) ? 1 : -1]

namespace EA { namespace Text {
struct TextStyle {
    uint32_t d[0x9e];
    TextStyle();                                             // 0x8941d0
    TextStyle& operator=(const TextStyle&);                  // 0x894280
};
struct StyleManager {
    const TextStyle* GetStyle(uint32_t id, int flag);        // 0x894670
};
struct LineLayout {
    uint32_t pad0;
    const wchar_t* mBegin;
    const wchar_t* mEnd;
    float GetXForIndex(int index, int a, int b);             // 0x898090
    int HitTest(float x, float y, int a, int b, int* out, int c);   // 0x897e00
};
struct Typesetter {
    void Reset(bool b);                                      // 0x89cdf0
    void AddTextRun(const wchar_t* p, uint32_t n);           // 0x89b1e0
    LineLayout* GetLineLayout();                             // 0x8976a0
    void FinalizeLine();                                     // 0x89d9a0
    void NextLine(bool b);                                   // 0x89c5d0
    void SetStyle(const void* style);                        // 0x8981f0
    int GetState();                                          // 0x897680
    void SetBounds(float w, float x, float y);               // 0x897640
};
struct FontServer {
    virtual void fs0(); virtual void fs1(); virtual void fs2(); virtual void fs3(); virtual void fs4(); virtual void fs5();
    virtual int GetFonts(const TextStyle* s, void* out, uint32_t a, uint32_t b, uint32_t c, int d); // slot 6 (+0x18)
};
StyleManager* GetStyleManager(bool create);                  // 0x885bd0
FontServer* GetFontServer(bool create);                      // 0x885a60
void GetMaxFontMetrics(void* fonts, float* a, float* b);     // 0x8985b0

struct TextRunInfo { const wchar_t* text; uint32_t length; };
struct CharBreakIterator {          // 0x20 bytes (the original reserves 0x20 for it on the stack)
    uint32_t d[7];
    uint32_t mnPosition;                // +0x1c, zeroed by the caller before SetPosition
    void SetTextRunArray(const TextRunInfo* runs, uint32_t n, uint32_t a, uint32_t b, int c);  // 0x88f790
    uint32_t SetPosition(uint32_t p);                        // 0x888220
    uint32_t GetNextCharBreak();                             // 0x888240
    uint32_t GetPrevCharBreak();                             // 0x8884b0
};
}}

// Scratch font set (ctor 0x89a570, dtor = rbtree DoNukeSubtree 0x88fda0).
struct FontScratch { uint32_t d[8]; FontScratch(); ~FontScratch(); };

struct Stopwatch {
    uint64_t mStart;
    uint64_t mElapsed;
    int mUnits;
    float mScale;
    int64_t GetElapsedTimeFloat();                           // 0x93a3a0
    void Restart();                                          // 0x571e80
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(uint64_t* p);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

namespace EA { namespace UTFWinControls {

struct Paragraph {
    uint32_t mTextIndex;
    uint32_t mTextLength;
    int mTextLines;
    float mExtentX, mExtentY;
    float mYPos;
};
struct YPosComparator {};
struct TextIndexComparator {};

// eastl::upper_bound instantiations (0x98b650 / 0x98b6b0 / 0x9212c0)
const Paragraph* UpperBoundY(const Paragraph* first, const Paragraph* last, const float& v, YPosComparator c);  // 0x98b650
const Paragraph* UpperBoundIndex(const Paragraph* first, const Paragraph* last, const uint32_t& v, TextIndexComparator c);  // 0x98b6b0
const uint32_t* UpperBoundLine(const uint32_t* first, const uint32_t* last, const uint32_t& v);  // 0x9212c0

template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
// Forces a fresh load of a member (the original re-reads the vector begin after its bounds check).
template <class T> inline T Reload(const T& v) { return *(const volatile T*)&v; }

struct Point2 { float x, y; };
using EA::Text::LineLayout;

struct WinTextEdit;

// Secondary interface, embedded at WinTextEdit+0x20c.
struct IWinTextEdit {
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
    EA::Text::TextStyle mActualStyle;   // +0x80
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
    Stopwatch mCaretTimer;     // +0x3cc
    float mCaretLeft;          // +0x3e4
    float mCaretTop;           // +0x3e8
    float mCaretRight;         // +0x3ec
    float mCaretBottom;        // +0x3f0
    uint8_t mCaretVisible;     // +0x3f4

    WinTextEdit* Owner() { return (WinTextEdit*)((char*)this - 0x20c); }

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

struct WinTextEditBase4 {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35();
    virtual void OnCursorMoved();                             // slot 36 (+0x90)
};

struct WinTextEdit {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void OnStyleChanged();                            // slot 36 (+0x90)
    uint32_t pad04[(0xb0 - 4) / 4];
    const wchar_t* mTextBegin; // +0xb0
    const wchar_t* mTextEnd;   // +0xb4
    uint32_t padb8;
    uint32_t mStyleId;         // +0xbc
    uint32_t mStyleId2;        // +0xc0
    uint32_t padc4[(0x20c - 0xc4) / 4];
    IWinTextEdit mIWin;        // +0x20c

    EA::Text::Typesetter* GetTypesetter();                    // 0x95fba0
    void SetBaseStyle(uint32_t id);                           // 0x95fa40
    void RefreshParagraphs();                                 // 0x98d110
    void SetParagraphCache(const Paragraph* p);               // 0x98cd00
    const Paragraph* FindParagraphForIndex(uint32_t index);   // 0x98b910
    LineLayout* LayoutLine(const Paragraph* p, uint32_t line, uint32_t* a, uint32_t* b);   // 0x98ceb0
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
CHK(a, offsetof(IWinTextEdit, mDirtyFlags) == 0x0c);
CHK(b, offsetof(IWinTextEdit, mCursorIndex) == 0x5c);
CHK(c, offsetof(IWinTextEdit, mActualStyle) == 0x80);
CHK(d, offsetof(IWinTextEdit, mFontHeight) == 0x2f8);
CHK(e, offsetof(IWinTextEdit, mScrollX) == 0x39c);
CHK(f, offsetof(IWinTextEdit, mCaretTimer) == 0x3cc);
CHK(g, offsetof(IWinTextEdit, mCaretLeft) == 0x3e4);
CHK(h, offsetof(WinTextEdit, mIWin) == 0x20c);

// ------------------------------------------------------------ IWinTextEdit

// @ 0x98e7b0
int IWinTextEdit::GetParagraphCount()
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    return (int)(mParaEnd - mParaBegin);
}

// @ 0x98e7e0
uint32_t IWinTextEdit::GetParagraphTextIndex(uint32_t i)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    if (i >= (uint32_t)(mParaEnd - mParaBegin))
        return 0xffffffff;
    return Reload(mParaBegin)[i].mTextIndex;
}

// @ 0x98e830
float IWinTextEdit::GetParagraphYPos(uint32_t i)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    if (i >= (uint32_t)(mParaEnd - mParaBegin))
        return 0.0f;
    return Reload(mParaBegin)[i].mYPos;
}

// @ 0x98e880
uint32_t IWinTextEdit::GetParagraphLength(uint32_t i)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    if (i >= (uint32_t)(mParaEnd - mParaBegin))
        return 0xffffffff;
    return Reload(mParaBegin)[i].mTextLength;
}

// @ 0x98e8d0
int IWinTextEdit::GetParagraphAtTextIndex(uint32_t index)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    uint32_t value = index;
    const Paragraph* p = UpperBoundIndex(mParaBegin, mParaEnd, value, TextIndexComparator());
    return (int)((p - 1) - mParaBegin);
}

// @ 0x98e930
int IWinTextEdit::GetParagraphAtPosition(float y)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    float value = y;
    const Paragraph* p = UpperBoundY(mParaBegin, mParaEnd, value, YPosComparator());
    return (int)((p - 1) - mParaBegin);
}

// @ 0x98e9a0
void IWinTextEdit::GetTextExtent(Point2* out)
{
    if (mDirtyFlags & 4)
        Owner()->RefreshParagraphs();
    out->x = mExtentX;
    out->y = mExtentY;
}

// @ 0x98ec70
bool IWinTextEdit::MoveCursor(int kind, int amount, uint32_t extend)
{
    WinTextEdit* te = Owner();
    uint32_t cursor = mCursorIndex;
    switch (kind) {
    case 0: {
        bool forward = true;
        int n = amount;
        if (n < 0) {
            n = -n;
            forward = false;
        }
        EA::Text::TextRunInfo info;
        info.text = te->mTextBegin;
        info.length = GetTextLength();
        EA::Text::CharBreakIterator it;
        it.SetTextRunArray(&info, 1, 0, 0, -1);
        it.mnPosition = 0;
        it.SetPosition(mCursorIndex);
        while (n > 0) {
            cursor = forward ? it.GetNextCharBreak() : it.GetPrevCharBreak();
            --n;
        }
        SetCursorIndex(cursor, extend);
        ((WinTextEditBase4*)((char*)this - 0x208))->OnCursorMoved();
        return true;
    }
    case 1:
        if (amount > 0) {
            int n = amount;
            do {
                --n;
                if ((uint32_t)(te->mTextEnd - te->mTextBegin) <= mCursorIndex)
                    break;
                SetCursorIndex(te->WordNext(mCursorIndex), extend);
            } while (n != 0);
        } else if (amount < 0) {
            int n = amount;
            do {
                ++n;
                if (mCursorIndex == 0)
                    break;
                SetCursorIndex(te->WordPrev(mCursorIndex), extend);
            } while (n != 0);
        }
        return true;
    case 2: {
        if (mDirtyFlags & 2)
            te->RecalculateCursorPosition();
        const Paragraph* para = te->FindParagraphForIndex(mCursorIndex);
        int line = (int)mCursorParaLine + amount;
        if (line < 0) {
            do {
                if (para <= mParaBegin) {
                    line = 0;
                    break;
                }
                --para;
                line += para->mTextLines;
            } while (line < 0);
        } else {
            int lines = para->mTextLines;
            if (line >= lines) {
                do {
                    if (para >= mParaEnd - 1) {
                        line = para->mTextLines - 1;
                        break;
                    }
                    ++para;
                    line -= lines;
                    lines = para->mTextLines;
                } while (line >= lines);
            }
        }
        te->SetParagraphCache(para);
        uint32_t lineLen, lineStart;
        LineLayout* layout = te->LayoutLine(para, (uint32_t)line, &lineStart, &lineLen);
        int unused;
        int hit = layout->HitTest(mCursorSeekX, 0.0f, 0, 0, &unused, 0);
        uint32_t idx = para->mTextIndex + hit + lineStart;
        if (idx != (uint32_t)GetTextLength())
            idx = te->SnapToLine(idx, 0);
        if ((uint32_t)hit == lineLen && te->mTextBegin[lineStart + lineLen - 1] == 0xa)
            --idx;
        SetCursorIndex(idx, extend);
        mDirtyFlags &= ~2u;
        return true;
    }
    case 3:
        if (amount > 0) {
            int n = amount;
            do {
                --n;
                if ((uint32_t)(te->mTextEnd - te->mTextBegin) <= mCursorIndex)
                    break;
                SetCursorIndex(te->LineNext(mCursorIndex), extend);
            } while (n != 0);
        } else if (amount < 0) {
            int n = amount;
            do {
                ++n;
                if (mCursorIndex == 0)
                    break;
                SetCursorIndex(te->LinePrev(mCursorIndex), extend);
            } while (n != 0);
        }
        return true;
    case 4:
        if (amount > 0) {
            int n = amount;
            do {
                --n;
                if ((uint32_t)(te->mTextEnd - te->mTextBegin) <= mCursorIndex)
                    break;
                SetCursorIndex(te->ParaNext(mCursorIndex), extend);
            } while (n != 0);
        } else if (amount < 0) {
            int n = amount;
            do {
                ++n;
                if (mCursorIndex == 0)
                    break;
                SetCursorIndex(te->ParaPrev(mCursorIndex), extend);
            } while (n != 0);
        }
        return true;
    case 6:
        SetCursorIndex(cursor - mCursorColumn, extend);
        return true;
    case 7: {
        const Paragraph* para = te->FindParagraphForIndex(cursor);
        te->SetParagraphCache(para);
        uint32_t start, len;
        te->GetLineRange(mCursorParaLine, &start, &len);
        uint32_t pos = len + start;
        if (pos < para->mTextLength)
            --pos;
        SetCursorIndex(para->mTextIndex + pos, extend);
        return true;
    }
    case 8:
        SetCursorIndex(0, extend);
        return true;
    case 9:
        SetCursorIndex((uint32_t)(te->mTextEnd - te->mTextBegin), extend);
        return true;
    default:
        return false;
    }
}

// @ 0x98f120
void IWinTextEdit::ScrollToCursor()
{
    if (mDirtyFlags & 5)
        Owner()->RecalculateCursorPosition();
    Point2 pt;
    pt.x = mScrollX;
    pt.y = mScrollY;
    pt.x = Min(pt.x, mExtentX - (mVisRight - mVisLeft));
    pt.x = Max(pt.x, mCaretRight - (mVisRight - mVisLeft));
    pt.x = Min(pt.x, mCaretLeft);
    pt.x = Max(pt.x, 0.0f);
    pt.y = Min(pt.y, mExtentY - (mVisBottom - mVisTop));
    pt.y = Max(pt.y, mCaretBottom - (mVisBottom - mVisTop));
    pt.y = Min(pt.y, mCaretTop);
    pt.y = Max(pt.y, 0.0f);
    if (pt.x != mScrollX || pt.y != mScrollY)
        SetScrollPosition(&pt);
}

// ------------------------------------------------------------------ obj-level

// @ 0x98e3a0
Point2 WinTextEdit::GetCursorPoint(int index)
{
    EA::Text::Typesetter* ts = GetTypesetter();
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
            EA::Text::LineLayout* layout = ts->GetLineLayout();
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

// @ 0x98e690
void WinTextEdit::SetTextStyle(uint32_t id)
{
    SetBaseStyle(id);
    mIWin.mTextEditFlags |= 5;
    EA::Text::StyleManager* sm = EA::Text::GetStyleManager(true);
    if (sm) {
        const EA::Text::TextStyle* style = sm->GetStyle(mStyleId, 0);
        EA::Text::TextStyle fallback;
        mIWin.mActualStyle = style ? *style : fallback;
        EA::Text::FontServer* fs = EA::Text::GetFontServer(true);
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

// @ 0x98e9d0
void WinTextEdit::RecalculateCursorPosition()
{
    if (mIWin.mDirtyFlags & 4)
        RefreshParagraphs();
    uint32_t cursor = mIWin.mCursorIndex;
    mIWin.mDirtyFlags &= ~1u;
    const Paragraph* para = UpperBoundIndex(mIWin.mParaBegin, mIWin.mParaEnd, cursor, TextIndexComparator()) - 1;
    SetParagraphCache(para);
    uint32_t rel = mIWin.mCursorIndex - para->mTextIndex;
    const uint32_t* lb = mIWin.mLineBreaksBegin;
    uint32_t line = (uint32_t)((UpperBoundLine(lb, mIWin.mLineBreaksEnd, rel) - 1) - lb);
    mIWin.mCursorParaLine = line;
    uint32_t lineOffset, found;
    EA::Text::LineLayout* layout = LayoutLine(para, line, &lineOffset, &found);
    mIWin.mCursorColumn = mIWin.mCursorIndex - para->mTextIndex - lineOffset;
    if (found == 0) {
        mIWin.mCaretLeft = 0.0f;
    } else {
        float x = layout->GetXForIndex((int)mIWin.mCursorColumn, 0, 0) - mIWin.mBorderLeft;
        float zero = 0.0f;
        mIWin.mCaretLeft = Max(zero, x);
    }
    float size = *(float*)&mIWin.mActualStyle.d[0x81];
    float width;
    if (size < 20.0f)
        width = 1.0f;
    else if (size < 40.0f)
        width = 2.0f;
    else
        width = size * 0.05f;
    uint32_t lh = mIWin.mLineHeight;
    float top = (float)(mIWin.mCursorParaLine * lh) + para->mYPos;
    mIWin.mCaretTop = top;
    mIWin.mCaretRight = mIWin.mCaretLeft + width;
    mIWin.mCaretBottom = top + (float)(int)lh;
    if (mIWin.mDirtyFlags & 2) {
        mIWin.mCursorSeekX = mIWin.mCaretLeft;
        mIWin.mDirtyFlags &= ~2u;
    }
    ShowCaret(true);
    if (mIWin.mCaretTimer.mUnits == 1) {
        mIWin.mCaretTimer.mStart = __rdtsc();
    } else {
        uint64_t t;
        QueryPerformanceCounter(&t);
        mIWin.mCaretTimer.mStart = t;
    }
    mIWin.mCaretTimer.mElapsed = 0;
}

// @ 0x98ebd0
bool WinTextEdit::OnTick()
{
    if ((mIWin.mDirtyFlags & 5) && mIWin.mEditColor == 0) {
        mIWin.Update();
        UpdateLayout();
    }
    if (mIWin.mTextEditFlags & 0x21) {
        mIWin.mCaretVisible = 0;
        return false;
    }
    Stopwatch& t = mIWin.mCaretTimer;
    if (mIWin.mCaretPeriod < (float)t.GetElapsedTimeFloat() * t.mScale) {
        ShowCaret(mIWin.mCaretVisible == 0);
        t.Restart();
    }
    return false;
}

// @ 0x98f330
struct TypeRegistry {
    virtual void v0();
    virtual void Register(void* type, int flags);
};
TypeRegistry* GetTypeRegistry();                              // 0x920090
extern void* g_WinTextEditType0;                              // 0x154fe5c
extern void* g_WinTextEditType1;                              // 0x154fe60
extern void* g_WinTextEditType2;                              // 0x154fe64

void RegisterWinTextEditTypes()
{
    GetTypeRegistry()->Register(&g_WinTextEditType0, 0);
    GetTypeRegistry()->Register(&g_WinTextEditType1, 0);
    GetTypeRegistry()->Register(&g_WinTextEditType2, 0);
}

// @ 0x98f3d0
struct UTFWindow { bool Initialize(); };                      // 0xb1fbf0
struct WinTreeView : UTFWindow {
    uint32_t pad[0x84];
    bool mInited;                                             // +0x210
    bool Init();
};
bool WinTreeView::Init()
{
    if (!mInited) {
        if (Initialize())
            mInited = true;
    }
    return mInited;
}

}} // namespace
