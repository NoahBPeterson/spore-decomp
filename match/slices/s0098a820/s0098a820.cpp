// UTFWinControls::WinTextEdit helpers: word/line scanning, SelectWordAt, scrollbar setters,
// OnKeyDown, EASTL upper_bound / deque DoReallocPtrArray instances (0x98a820-0x98b700).
// Retail layout: WinTextEdit = Window (0x20c bytes, text buffer begin/end at +0xb0/+0xb4)
// followed by the IWinTextEdit subobject at +0x20c (vtable calls on it go through slot casts).
#include "types.h"

#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])

extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned short c, unsigned short mask);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);

void* operator_new(size_t size, const char* name, int flags, unsigned dbgFlags, const char* file, int line);  // 00F473A0
void operator_delete__(void* p);                                                                               // 00F47380

namespace EA {
namespace Text {
struct TextRun { const wchar_t* text; void* style; };
struct TextRunIterator {
    uint32_t pad[7];
    void SetTextRunArray(const TextRun* runs, unsigned count, unsigned a, unsigned b, unsigned c);   // 0088F790
};
struct BreakIteratorBase : TextRunIterator {
    uint32_t f1c;
    unsigned SetPosition(unsigned pos);                 // 00888220
};
struct CharacterBreakIterator : BreakIteratorBase {
    unsigned GetNextCharBreak();                        // 00888240
    unsigned GetPrevCharBreak();                        // 008884B0
};
}
}
namespace EA { namespace Clipboard {
struct IData {
    virtual void m0(); virtual void m4();
    virtual void Release();                         // 0x08
    virtual void mc();
    virtual const wchar_t* GetData();               // 0x10
    virtual unsigned GetSize();                     // 0x14
};
IData* CreateTextData(const wchar_t* text, int len);                        // 0092AB60
struct Clipboard {
    bool SetClipboardData(IData* d, int flag);                              // 0092ABB0
    bool GetClipboardData(int fmt, IData** out);                            // 0092A8D0
};
Clipboard* GetClipboard(int which);                                         // 0092AD50
}}

namespace EA { namespace UTFWinControls {

struct IWinTextEdit;

struct TextMsg {
    uint32_t w0, w1;
    uint32_t type, src, w4;
    int length;
    const wchar_t* text;
};

struct TextWinPrim {
    virtual void p00();
};

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

struct TextWindow : TextWinPrim, TextIWin {
    uint32_t p08[(0xb0 - 8) / 4];
    wchar_t* textBegin;                         // +0xb0
    wchar_t* textEnd;                           // +0xb4
    uint32_t pb8[(0x20c - 0xb8) / 4];
    unsigned TextLength() const { return (unsigned)(textEnd - textBegin); }
};

struct IUnk { virtual void AddRef(); virtual void Release(); };

struct ScrollbarSlot {
    IUnk* scrollbar;                            // +0
    int enabled;                                // +4
    uint32_t p08[3];
};

struct IWinTextEdit {
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

struct WinTextEdit : TextWindow, IWinTextEdit {
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

// @ 0x98a820
void WinTextEdit::FindSentenceEnd(unsigned pos) {
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

// @ 0x98a910
void WinTextEdit::FindWordStart(unsigned pos) {
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

// @ 0x98a9f0
void WinTextEdit::FindLineEnd(unsigned pos) {
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

// @ 0x98aa80
unsigned WinTextEdit::FindLineStart(unsigned pos) {
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

// @ 0x98ab40
void WinTextEdit::SelectWordAt(unsigned pos) {
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

// @ 0x98acb0
void IWinTextEdit::SetScrollbar(int idx, IUnk* p) {
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

// @ 0x98ad10
void IWinTextEdit::SetScrollbarEnabled(int idx, int v) {
    sb[idx].enabled = v;
    WinTextEdit* w = (WinTextEdit*)((char*)this - 0x20c);
    w->F98A090(1);
    w->F98A090(0);
}

// @ 0x98ad40
bool WinTextEdit::OnKeyDown(int a1, int key, unsigned mods) {
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

// ---------------------------------------------------------------- EASTL instances
struct Paragraph {
    uint32_t textIndex, textLength;
    int textLines;
    float extentX, extentY;
    float yPos;
    struct YPosComparator {
        bool operator()(float y, const Paragraph& p) const { return y < p.yPos; }
    };
    struct TextIndexComparator {
        bool operator()(unsigned i, const Paragraph& p) const { return i < p.textIndex; }
    };
};

}}  // namespace

namespace eastl {
template <typename ForwardIterator, typename T, typename Compare>
ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare) {
    int d = (int)(last - first);
    while (d > 0) {
        ForwardIterator i = first;
        int d2 = d >> 1;
        i += d2;
        if (!compare(value, *i)) {
            first = ++i;
            d -= d2 + 1;
        } else
            d = d2;
    }
    return first;
}
}

namespace EA { namespace UTFWinControls {
// @ 0x98b650
const Paragraph* UpperBoundByY(const Paragraph* first, const Paragraph* last, const float& v) {
    return eastl::upper_bound(first, last, v, Paragraph::YPosComparator());
}
// @ 0x98b6b0
const Paragraph* UpperBoundByIndex(const Paragraph* first, const Paragraph* last, const unsigned& v) {
    return eastl::upper_bound(first, last, v, Paragraph::TextIndexComparator());
}
}}

namespace eastl {

template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }

// eastl::deque<T*, allocator, 64>: DequeBase::DoReallocPtrArray (0x98b700)
struct DequeIterator {
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

struct DequeBase {
    void*** mpPtrArray;
    unsigned mnPtrArraySize;
    DequeIterator mItBegin;
    DequeIterator mItEnd;
    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(unsigned nAdditionalCapacity, Side allocationSide);
};

// @ 0x98b700
void DequeBase::DoReallocPtrArray(unsigned nAdditionalCapacity, Side allocationSide) {
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

}
