// UTFWinControls::WinTextEdit / IWinTextEdit (0x98c880-0x98d5ff).
// Retail layout comes from the disassembly: WinTextEdit : Window (vptr +0), Base4 (vptr +4),
// then its own members from +8; the polymorphic IWinTextEdit subobject is a member at +0x20c.
// All field offsets below are absolute (WinTextEdit-relative) and asserted with CHK.
#include "types.h"
#include <stddef.h>

#pragma pack(4)
#define CHK(name, expr) typedef char chk_##name[(expr) ? 1 : -1]

// ---------------------------------------------------------------- EA::Text
namespace EA { namespace Text {

struct TextStyle {
    uint32_t d[0x9e];
};

class LineLayout { public:
    uint32_t pad0;                  // +0x00
    const wchar_t* mBegin;          // +0x04
    const wchar_t* mEnd;            // +0x08
    uint32_t padC[(0x9c - 0x0c) / 4];
    float mExtentX;                 // +0x9c
    int HitTest(float x, float y, int a, int b, int* out, int c);   // 0x897e00
};

class Typesetter { public:
    void Reset(bool b);                                     // 0x89cdf0
    void SetStyle(const void* style);                       // 0x8981f0
    void AddTextRun(const wchar_t* p, uint32_t n);          // 0x89b1e0
    void SetBounds(float w, float x, float y);              // 0x897640
    int  GetState();                                        // 0x897680
    void FinalizeLine();                                    // 0x89d9a0
    LineLayout* GetLineLayout();                            // 0x8976a0
    void NextLine(bool b);                                  // 0x89c5d0
};

struct TextRunInfo { const wchar_t* text; uint32_t length; };

class TextRunIterator { public:
    uint32_t d[5];                  // +0x00
    uint32_t mnPosition;            // +0x14
    uint32_t mnEndPosition;         // +0x18
    uint32_t pad1c;                 // +0x1c
    void SetTextRunArray(const TextRunInfo* runs, uint32_t n, uint32_t a, uint32_t b, int c); // 0x88f790
    uint32_t Next();                                        // 0x8883a0
};

}} // namespace EA::Text

// ---------------------------------------------------------------- utilities
struct Stopwatch {
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

namespace EA { namespace UTFWinControls {

struct Paragraph {
    uint32_t mTextIndex;            // +0x00
    uint32_t mTextLength;           // +0x04
    int      mTextLines;            // +0x08
    float    mExtentX;              // +0x0c
    float    mExtentY;              // +0x10
    float    mYPos;                 // +0x14
};
struct YPosComparator {};
struct TextIndexComparator {};

const Paragraph* UpperBoundY(const Paragraph* first, const Paragraph* last, const float& v, YPosComparator c); // 0x98b650

// eastl-style vectors (begin/end/cap triple).
struct ParagraphVector {
    Paragraph* mpBegin;             // +0x00
    Paragraph* mpEnd;               // +0x04
    Paragraph* mpCap;               // +0x08
    void reserve(uint32_t n);                               // 0x98bab0
    void push_back(const Paragraph& v);                     // 0x98cb20
    void DoInsertValue(Paragraph* pos, const Paragraph& v); // 0x98bfc0
};

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

// eastl::deque of 4-byte values, 64-element blocks (the disassembly uses these slots).
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

void RebuildParagraphs(Paragraph* a, Paragraph* b, Paragraph* c);   // 0x989790

struct Base4Obj {
    virtual void o00(); virtual void o01(); virtual void o02(); virtual void o03(); virtual void o04();
    virtual void o05(); virtual void o06(); virtual void o07(); virtual void o08(); virtual void o09();
    virtual void o10(); virtual void o11(); virtual void o12(); virtual void o13(); virtual void o14();
    virtual void o15(); virtual void o16(); virtual void o17(); virtual void o18(); virtual void o19();
    virtual void o20(); virtual void o21();
    virtual void Notify(int flag, void* self);              // slot 22 (+0x58)
};

struct Base4 {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
    virtual Base4Obj* GetObj();                             // slot 5  (+0x14)
    virtual void b06(); virtual void b07(); virtual void b08(); virtual void b09(); virtual void b10();
    virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15();
    virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20();
    virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25();
    virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30();
    virtual void b31(); virtual void b32();
    virtual void SetStyleId(uint32_t id);                   // slot 33 (+0x84)
    virtual void b34(); virtual void b35();
    virtual void OnCursorMoved();                           // slot 36 (+0x90)
    virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41();
    virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46();
    virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51();
    virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual void b56();
    virtual void b57(); virtual void b58(); virtual void b59(); virtual void b60(); virtual void b61();
    virtual void b62(); virtual void b63();
    virtual bool OnMouseMoveEvent(int flag);                // slot 64 (+0x100)
    virtual void b65(); virtual void b66(); virtual void b67(); virtual void b68();
    virtual void Dispatch(void* msg);                       // slot 69 (+0x114)
};

struct Window {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual ~Window();
    bool Initialize();                                      // 0x0b1fbf0
};

class WinTextEdit;

class IWinTextEdit { public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int  GetTextLength();                           // slot 20 (+0x50)
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void SetCursorIndex(uint32_t index, uint32_t extend);   // slot 35 (+0x8c)
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();

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
    ParagraphVector mParagraphList; // +0x70
    uint32_t pad7c;
    EA::Text::TextStyle mActualStyle;   // +0x80
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
    Stopwatch mCaretTimer;          // +0x3cc
    float mCaretLeft;               // +0x3e4
    float mCaretTop;                // +0x3e8
    float mCaretRight;              // +0x3ec
    float mCaretBottom;             // +0x3f0
    uint32_t pad3f4[(0x3fc - 0x3f4) / 4];
    Stopwatch mDoubleClickTimer;    // +0x3fc
    float mDoubleClickInterval;     // +0x414
    uint32_t pad418[(0x444 - 0x418) / 4];
    int mField650;                  // +0x444

    bool Undo();                                            // 0x98c880
    bool Redo();                                            // 0x98c9d0
};

struct TextMsg {
    uint32_t w0;                    // +0x00 (uninitialised in the original)
    uint32_t w1;                    // +0x04
    uint32_t type;                  // +0x08
    void*    src;                   // +0x0c
    uint32_t w4;                    // +0x10
    int      length;                // +0x14
    const wchar_t* text;            // +0x18
};

class WinTextEdit : public Window, public Base4 { public:
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
    IWinTextEdit mIWin;             // +0x20c

    EA::Text::Typesetter* GetTypesetter();                  // 0x95fba0
    void Shutdown();                                        // 0x98c520
    void ShowCaret(bool show);                              // 0x989660
    uint32_t SnapToLine(uint32_t idx, uint32_t flag);       // 0x98a430
    void SelectWordAt(uint32_t idx);                        // 0x98ab40
    void PostEditChange();                                  // 0x9899b0
    float GetBaselineOffset();                              // 0x98b940
    void ApplyUndo(void* action);                           // 0x98bc80
    void ApplyRedo(void* action);                           // 0x98bd00

    bool Init();                                            // 0x98cc70
    ~WinTextEdit();                                         // 0x98cbb0
    void SetParagraphCache(const Paragraph* p);             // 0x98cd00
    EA::Text::LineLayout* LayoutLine(const Paragraph* p, uint32_t line, uint32_t* outOffset, uint32_t* outChars); // 0x98ceb0
    int HitTest(Paragraph* p, float* pt, bool flag);        // 0x98cfd0
    void RecalculateLineBreaks();                           // 0x98d110
    int Pick(float x, float y, bool flag);                   // 0x98d320
    bool OnMouseDown(float x, float y, uint32_t a, uint8_t extend); // 0x98d420
    bool OnMouseMove(float x, float y, uint32_t a);         // 0x98d540
    bool OnAutoSize(uint32_t a, float* out);                // 0x98d5b0
};

CHK(a, offsetof(IWinTextEdit, mInited) == 0x04);
CHK(b, offsetof(IWinTextEdit, mDirtyFlags) == 0x0c);
CHK(c, offsetof(IWinTextEdit, mMaxTextLength) == 0x58);
CHK(d, offsetof(IWinTextEdit, mParagraphList) == 0x70);
CHK(e, offsetof(IWinTextEdit, mActualStyle) == 0x80);
CHK(f, offsetof(IWinTextEdit, mLineHeight) == 0x2fc);
CHK(g, offsetof(IWinTextEdit, mLineBreaks) == 0x300);
CHK(h, offsetof(IWinTextEdit, mUndoList) == 0x31c);
CHK(i, offsetof(IWinTextEdit, mRedoList) == 0x348);
CHK(j, offsetof(IWinTextEdit, mScrollX) == 0x39c);
CHK(k, offsetof(IWinTextEdit, mCaretTimer) == 0x3cc);
CHK(l, offsetof(IWinTextEdit, mDoubleClickTimer) == 0x3fc);
CHK(m, offsetof(IWinTextEdit, mField650) == 0x444);
CHK(n, sizeof(IWinTextEdit) == 0x448);
CHK(o, offsetof(WinTextEdit, mTextBegin) == 0xb0);
CHK(p, offsetof(WinTextEdit, mIWin) == 0x20c);
CHK(q, sizeof(Deque) == 0x2c);
CHK(r, sizeof(Stopwatch) == 0x18);

// ------------------------------------------------------------------ ParagraphVector

// @ 0x98cb20
void ParagraphVector::push_back(const Paragraph& v)
{
    Paragraph* e = mpEnd;
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

// ------------------------------------------------------------------ IWinTextEdit

// @ 0x98c880
bool IWinTextEdit::Undo()
{
    if (mUndoList.mpCurrent == mUndoList.mpEndCurrent)
        return false;
    void* action = mUndoList.pop_front();
    WinTextEdit* te = (WinTextEdit*)((char*)this - 0x20c);
    te->ApplyUndo(action);
    mRedoList.push_front(action);

    Base4* b4 = (Base4*)te;
    mDirtyFlags |= 7;
    b4->OnCursorMoved();

    TextMsg msg;
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

// @ 0x98c9d0
bool IWinTextEdit::Redo()
{
    if (mRedoList.mpCurrent == mRedoList.mpEndCurrent)
        return false;
    void* action = mRedoList.pop_front();
    WinTextEdit* te = (WinTextEdit*)((char*)this - 0x20c);
    te->ApplyRedo(action);
    mUndoList.push_front(action);

    Base4* b4 = (Base4*)te;
    mDirtyFlags |= 7;
    b4->OnCursorMoved();

    TextMsg msg;
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

// ------------------------------------------------------------------ WinTextEdit

// @ 0x98cbb0
WinTextEdit::~WinTextEdit()
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

// @ 0x98cc70
bool WinTextEdit::Init()
{
    if (!mIWin.mInited) {
        if (Initialize()) {
            mIWin.mParagraphList.reserve(0x10);
            Paragraph p;
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

// @ 0x98cd00
void WinTextEdit::SetParagraphCache(const Paragraph* p)
{
    VectorClear(mIWin.mLineBreaks.mpBegin, mIWin.mLineBreaks.mpEnd, 0);
    mIWin.mLineBreaks.mpEnd = mIWin.mLineBreaks.mpBegin;

    Paragraph* para = (Paragraph*)p;
    para->mExtentX = 0.0f;
    para->mExtentY = 0.0f;

    EA::Text::Typesetter* ts = GetTypesetter();
    ts->Reset(true);
    ts->SetStyle(&mIWin.mActualStyle.d[1]);
    ts->AddTextRun(mTextBegin + para->mTextIndex, para->mTextLength);
    ts->SetBounds((mIWin.mVisRight - mIWin.mVisLeft) - (mIWin.mCaretRight - mIWin.mCaretLeft),
                  mIWin.mVisLeft, 0.0f);

    uint32_t offset = 0;
    if (ts->GetState() != 2) {
        do {
            ts->FinalizeLine();
            EA::Text::LineLayout* layout = ts->GetLineLayout();
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

// @ 0x98ceb0
EA::Text::LineLayout* WinTextEdit::LayoutLine(const Paragraph* p, uint32_t line, uint32_t* outOffset, uint32_t* outChars)
{
    VectorClear(mIWin.mLineBreaks.mpBegin, mIWin.mLineBreaks.mpEnd, 0);
    mIWin.mLineBreaks.mpEnd = mIWin.mLineBreaks.mpBegin;

    EA::Text::Typesetter* ts = GetTypesetter();
    ts->Reset(true);
    ts->SetStyle(&mIWin.mActualStyle.d[1]);
    ts->AddTextRun(mTextBegin + p->mTextIndex, p->mTextLength);
    ts->SetBounds((mIWin.mVisRight - mIWin.mVisLeft) - (mIWin.mCaretRight - mIWin.mCaretLeft),
                  mIWin.mVisLeft, 0.0f);

    *outOffset = 0;
    EA::Text::LineLayout* layout = ts->GetLineLayout();
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

// @ 0x98cfd0
int WinTextEdit::HitTest(Paragraph* p, float* pt, bool flag)
{
    int line = (int)Floor((double)(pt[1] / (float)mIWin.mLineHeight));
    uint32_t outOffset, outChars;
    EA::Text::LineLayout* layout = LayoutLine(p, (uint32_t)line, &outOffset, &outChars);

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

// @ 0x98d110
void WinTextEdit::RecalculateLineBreaks()
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

    Paragraph* begin = mIWin.mParagraphList.mpBegin;
    Paragraph* end = mIWin.mParagraphList.mpEnd;
    RebuildParagraphs(end, end, begin);
    mIWin.mParagraphList.mpEnd = mIWin.mParagraphList.mpEnd + (end - begin);

    EA::Text::TextRunInfo run;
    run.text = mTextBegin;
    run.length = (uint32_t)textLen;
    EA::Text::TextRunIterator it;
    it.SetTextRunArray(&run, 1, 0, 0, -1);
    it.pad1c = 0;
    uint32_t prev = 0;
    while (it.mnPosition != it.mnEndPosition) {
        uint32_t pos = it.Next();
        Paragraph p;
        p.mTextIndex = prev;
        p.mTextLength = pos - prev;
        mIWin.mParagraphList.push_back(p);
        prev = pos;
    }

    bool append;
    if (mIWin.mParagraphList.mpBegin == mIWin.mParagraphList.mpEnd) {
        append = true;
    } else {
        const Paragraph* last = mIWin.mParagraphList.mpEnd - 1;
        append = last->mTextLength > 0 &&
                 mTextBegin[last->mTextIndex + last->mTextLength - 1] == L'\n';
    }
    if (append) {
        Paragraph p;
        p.mTextIndex = (uint32_t)textLen;
        p.mTextLength = 0;
        mIWin.mParagraphList.push_back(p);
    }

    EA::Text::Typesetter* ts = GetTypesetter();
    ts->Reset(true);
    ts->SetStyle(&mIWin.mActualStyle.d[1]);

    mIWin.mTextExtentX = 0.0f;
    mIWin.mTextExtentY = 0.0f;
    Paragraph* pend = mIWin.mParagraphList.mpEnd;
    for (Paragraph* p = mIWin.mParagraphList.mpBegin; p != pend; ++p) {
        p->mYPos = mIWin.mTextExtentY;
        SetParagraphCache(p);
        if (p->mExtentX > mIWin.mTextExtentX)
            mIWin.mTextExtentX = p->mExtentX;
        mIWin.mTextExtentY = p->mExtentY + mIWin.mTextExtentY;
    }
}

// @ 0x98d320
int WinTextEdit::Pick(float x, float y, bool flag)
{
    if (mIWin.mDirtyFlags & 4)
        RecalculateLineBreaks();
    x += mIWin.mScrollX;
    float yy = (mIWin.mScrollY - GetBaselineOffset()) + y;
    if (yy < 0.0f)
        return flag ? 0 : -1;
    if (yy < mIWin.mTextExtentY) {
        const Paragraph* p = UpperBoundY(mIWin.mParagraphList.mpBegin, mIWin.mParagraphList.mpEnd, yy, YPosComparator()) - 1;
        SetParagraphCache(p);
        float pt[2];
        pt[0] = x;
        pt[1] = yy;
        return HitTest((Paragraph*)p, pt, flag) + (int)p->mTextIndex;
    }
    if (flag)
        return (int)(mTextEnd - mTextBegin);
    return -1;
}

// @ 0x98d420
bool WinTextEdit::OnMouseDown(float x, float y, uint32_t a, uint8_t extend)
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

// @ 0x98d540
bool WinTextEdit::OnMouseMove(float x, float y, uint32_t a)
{
    if (OnMouseMoveEvent(1) &&
        (((mIWin.mTextEditFlags >> 6) & 1) || !(mIWin.mTextEditFlags & 1))) {
        int idx = Pick(x, y, 1);
        mIWin.SetCursorIndex((uint32_t)idx, 1);
    }
    return true;
}

// @ 0x98d5b0
bool WinTextEdit::OnAutoSize(uint32_t a, float* out)
{
    RecalculateLineBreaks();
    if (mIWin.mMaxTextLength != 0xffffffffu)
        out[0] = (float)(uint32_t)(mIWin.mMaxTextLength * 10u);
    else
        out[0] = 200.0f;
    out[1] = (float)(uint32_t)mIWin.mField650 + mIWin.mLineHeight + mIWin.mBorderBottom + mIWin.mBorderTop;
    return true;
}

}} // namespace EA::UTFWinControls
