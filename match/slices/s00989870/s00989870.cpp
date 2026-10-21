// Slice 62: EA::UTFWinControls::WinTextEdit interface + window methods (0x989870-0x98a7f0).
//
// Retail layout (settled by the neighbouring slice s0098a820):
//   TextWindow occupies 0x20c bytes: primary vptr +0x000, IWindow vptr +0x004, id0/id1 at
//   +0x080/+0x084, area[4] at +0x088, text buffer begin/end at +0x0b0/+0x0b4.
//   The IWinTextEdit subobject is the secondary base at +0x20c, so for an interface method
//   `this` is window+0x20c and the window is this-0x20c; IWindow is at window+4.
//   ScrollbarSlot stride 0x14 at interface+0x374 (window+0x580): scrollbar / drawable /
//   enabled / f0c / f10.
#include "types.h"

#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])
#define WIN(iface) ((TextWindow*)((char*)(iface) - 0x20c))
#define IFACE(win) ((IWinTextEdit*)((char*)(win) + 0x20c))

extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned short c, unsigned short mask);

void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0
bool  FUN_006ab760(void* vecField, const wchar_t* str);                            // 006AB760
typedef int (*HashHookFn)(void*, const wchar_t*, int, unsigned);
extern HashHookFn g_hashHook;                                                      // 0166B210

namespace EA {
#pragma pack(push, 4)
struct Stopwatch {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int      mnUnits;
    float    mfCyclesToUnitsCoefficient;
    void Restart();                                 // 00571E80
};
#pragma pack(pop)
}

namespace EA { namespace Text {
struct TextRun { const wchar_t* text; void* style; };
struct TextRunIterator {
    uint32_t pad[7];
    void SetTextRunArray(const TextRun* runs, unsigned count, unsigned a, unsigned b, unsigned c);  // 0088F790
};
struct BreakIteratorBase : TextRunIterator {
    uint32_t f1c;
    unsigned SetPosition(unsigned pos);             // 00888220
};
struct CharacterBreakIterator : BreakIteratorBase {
    unsigned GetNextCharBreak();                    // 00888240
    unsigned GetPrevCharBreak();                    // 008884B0
};
}}

namespace EA { namespace UTFWinControls {

struct TextVector {
    void DoInsertValue(unsigned idx, void* at, unsigned nbytes);   // 011E0744
};

struct TextMsg {
    uint32_t w0, w1;
    uint32_t type, src, w4;
    int length;
    const wchar_t* text;
};

struct IWindow { void* vt; };
struct IUnk { };
struct ScrollbarSlot {
    IUnk*  scrollbar;                                 // +0x00
    IUnk*  drawable;                                  // +0x04
    int    enabled;                                   // +0x08
    float  f0c;                                       // +0x0c
    float  f10;                                       // +0x10
};

// window primary/secondary subobjects + data, 0x20c bytes total
struct TextWindow {
    void* vtPrimary;                                  // +0x000
    void* vtIWindow;                                  // +0x004
    uint32_t p08[(0x80 - 0x08) / 4];                  // +0x008
    int id0, id1;                                     // +0x080, +0x084
    float area[4];                                    // +0x088
    uint32_t p98[(0xb0 - 0x98) / 4];                  // +0x098
    wchar_t* textBegin;                               // +0x0b0
    wchar_t* textEnd;                                 // +0x0b4
    uint32_t pB8[(0x20c - 0xb8) / 4];                 // +0x0b8
    unsigned TextLength() const { return (unsigned)(textEnd - textBegin); }
};

// secondary base at window+0x20c; `this` is the interface pointer
struct IWinTextEdit {
    void* vt;                                         // +0x000
    uint32_t p04;                                     // +0x004
    uint32_t flags;                                   // +0x008
    uint32_t flags2;                                  // +0x00c
    uint32_t lineMode;                                // +0x010
    float mRect[4];                                   // +0x014
    float mColors[4];                                 // +0x024
    uint32_t p34[(0x5c - 0x34) / 4];                  // +0x034
    unsigned cursor;                                  // +0x05c
    unsigned anchor;                                  // +0x060
    uint32_t p64[(0x2e8 - 0x64) / 4];                 // +0x064
    uint32_t f2e8;                                    // +0x2e8
    uint32_t p2ec[(0x374 - 0x2ec) / 4];               // +0x2ec
    ScrollbarSlot sb[2];                              // +0x374
    float mScrollX;                                   // +0x39c
    float mScrollY;                                   // +0x3a0
    uint32_t f3a4;                                    // +0x3a4
    float viewExtent;                                 // +0x3a8
    uint32_t p3ac[(0x3cc - 0x3ac) / 4];               // +0x3ac
    EA::Stopwatch caretTimer;                         // +0x3cc
    uint32_t p3e4[(0x440 - 0x3e4) / 4];               // +0x3e4
    uint8_t  byte440;                                 // +0x440

    int  F989A20();                                   // 00989A20
    int  F989A30(void* at, unsigned idx, unsigned n);    // 00989A30
    void F989B00(unsigned a, unsigned b);             // 00989B00
    char F989B70(unsigned* a, unsigned* b);           // 00989B70
    void F989BB0(uint32_t flag, char on);             // 00989BB0
    void SetScrollPosition(float* p);                 // 00989C60
    void* F989D10(int idx);                           // 00989D10
    int  F989D30(int idx);                            // 00989D30
    void F98A320(float* r);                           // 0098A320
    void F98A370(const wchar_t* str, int arg2);       // 0098A370
    void F98A3F0(int a, int b, int c);                // 0098A3F0
};

struct WinScrollbar { void* Construct(); };           // 00983790
struct ScrollbarDrawable { void* Construct(); };      // 009838A0

struct WinTextEdit : TextWindow, IWinTextEdit {
    void ShowCaret(int on);                           // 00989660
    int  DoMessageBase(int msg);                      // 00950BB0

    void CalculateVisibleArea();                      // 00989870
    void F9899B0();                                   // 009899B0
    char ValidateChange();                            // 00989A90
    char F989D70(int a1, int a2, int a3, int a4);     // 00989D70
    char OnFocusChange(int flag, void* other);        // 00989E60
    char OnKeyChar(int unused, unsigned key);         // 00989EC0
    int  DoMessage(int msg);                          // 00989FE0
    void F98A090(int idx);                            // 0098A090
    void F98A270(unsigned idx, int* outBegin, int* outLen);  // 0098A270
    void F98A2F0(int flag);                           // 0098A2F0
    unsigned SnapIndex(unsigned pos, int* out);       // 0098A430
    unsigned F98A4B0(unsigned pos);                   // 0098A4B0
    unsigned F98A570(unsigned pos);                   // 0098A570
    unsigned F98A660(unsigned pos);                   // 0098A660
    unsigned F98A730(unsigned pos);                   // 0098A730
};

template <class T> inline const T& emin(const T& a, const T& b) { return b < a ? b : a; }
template <class T> inline const T& emax(const T& a, const T& b) { return a < b ? b : a; }

}}  // namespace EA::UTFWinControls

using namespace EA::UTFWinControls;

// ================================================================ WinTextEdit window methods

// @ 0x989870
void WinTextEdit::CalculateVisibleArea() {
    IWinTextEdit* p = IFACE(this);
    float w = area[2] - area[0];
    float h = area[3] - area[1];
    p->mColors[2] = w;
    p->mColors[0] = 0.0f;
    p->mColors[1] = 0.0f;
    p->mColors[3] = h;
    p->mColors[0] = p->mRect[0] + p->mColors[0];
    p->mColors[1] = p->mRect[1] + p->mColors[1];
    p->mColors[2] = p->mColors[2] - p->mRect[2];
    p->mColors[3] = p->mColors[3] - p->mRect[3];
    if (VSLOT(char (__thiscall*)(void*, int), p, 0xf4)(p, 1))
        p->mColors[2] = p->mColors[2] - p->sb[1].f0c;
    if (VSLOT(char (__thiscall*)(void*, int), p, 0xf4)(p, 0))
        p->mColors[3] = p->mColors[3] - p->sb[0].f10;
    if (p->mColors[2] < p->mColors[0] || p->mColors[3] < p->mColors[1]) {
        p->mColors[2] = p->mColors[0];
        p->mColors[3] = p->mColors[1];
    }
}

// @ 0x9899b0
void WinTextEdit::F9899B0() {
    TextMsg m;
    m.type = 0x18;
    m.src = (uint32_t)id1;
    m.w4 = (uint32_t)id0;
    m.length = (int)(float)TextLength();
    m.text = textBegin;
    IWindow* iw = (IWindow*)((char*)this + 4);
    VSLOT(void (__thiscall*)(void*, TextMsg*), iw, 0x114)(iw, &m);
}

// @ 0x989a90
char WinTextEdit::ValidateChange() {
    struct Rec {
        wchar_t* text;          // +0x00
        int      len;           // +0x04
        uint8_t  one;           // +0x08
        uint8_t  pad09[3];      // +0x09
        void*    f0c;           // +0x0c
        uint32_t id;            // +0x14
        uint8_t  pad18[0xc];    // +0x18
        void*    self;          // +0x24
    };
    Rec rec;
    rec.text = textBegin;
    rec.len = (int)(textEnd - textBegin);
    rec.one = 1;
    rec.id = 0x9b1552da;
    rec.self = &rec;
    IWindow* iw = (IWindow*)((char*)this + 4);
    if (VSLOT(int (__thiscall*)(void*), iw, 0x14)(iw)) {
        void* obj = VSLOT(void* (__thiscall*)(void*), iw, 0x14)(iw);
        VSLOT(void (__thiscall*)(void*, void*, void*, void*, int), obj, 0x10)(obj, iw, iw, &rec.f0c, 0);
    }
    return (char)rec.one;
}

// @ 0x989d70
char WinTextEdit::F989D70(int a1, int a2, int a3, int a4) {
    (void)a1; (void)a2; (void)a3;
    IWindow* iw = (IWindow*)((char*)this + 4);
    if (VSLOT(char (__thiscall*)(void*, int), iw, 0x100)(iw, 1)) return 0;
    IWinTextEdit* p = IFACE(this);
    float pair[2];
    pair[0] = p->mScrollX;
    pair[1] = p->mScrollY - (float)(a4 / 4);
    pair[1] = emin(pair[1], (p->viewExtent - (p->mColors[3] - p->mColors[1])) + 3.0f);
    pair[1] = emax(0.0f, pair[1]);
    if (pair[0] != p->mScrollX || pair[1] != p->mScrollY)
        VSLOT(void (__thiscall*)(void*, float*), p, 0xd8)(p, pair);
    return 0;
}

// @ 0x989e60
char WinTextEdit::OnFocusChange(int flag, void* other) {
    if (flag == 0) {
        IWindow* p = this ? (IWindow*)((char*)this + 4) : 0;
        if (other == p) {
            ShowCaret(1);
            ((EA::Stopwatch*)((char*)this + 0x5d8))->Restart();
            IWindow* iw = (IWindow*)((char*)this + 4);
            VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
            return 0;
        }
        ShowCaret(0);
        IWindow* iw = (IWindow*)((char*)this + 4);
        VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
    }
    return 0;
}

// @ 0x989ec0
char WinTextEdit::OnKeyChar(int unused, unsigned key) {
    (void)unused;
    IWinTextEdit* p = IFACE(this);
    if (p->flags & 1) return 1;
    if ((unsigned short)key < 0x20) {
        switch ((unsigned short)key) {
        case 9:
            return 0;
        case 10:
            if (!(p->flags & 2)) return 0;
            break;
        case 13:
            if (!(p->flags & 2)) return 0;
            key = 10;
            break;
        default:
            return 0;
        }
    }
    unsigned sel = emin(p->cursor, p->anchor);
    if (sel == emax(p->cursor, p->anchor)) sel = p->cursor;
    if (p->byte440) {
        HashHookFn hook = g_hashHook;
        if (hook && !hook(&key, textBegin, (int)TextLength(), sel)) return 1;
    }
    if (p->cursor == p->anchor && (p->flags & 8)) {
        VSLOT(void (__thiscall*)(void*, unsigned, int, unsigned*, int, int), p, 0x78)
            (p, p->cursor, 1, &key, 1, 1);
        return 1;
    }
    VSLOT(void (__thiscall*)(void*, unsigned*, int, int), p, 0x74)(p, &key, 1, 1);
    return 1;
}

// @ 0x989fe0
int WinTextEdit::DoMessage(int msg) {
    if (*(uint32_t*)((char*)msg + 8) != 0x8ef0c8dd) return DoMessageBase(msg);
    IWinTextEdit* p = IFACE(this);
    float x = p->sb[0].scrollbar
        ? (float)VSLOT(int (__thiscall*)(void*), p->sb[0].scrollbar, 0x28)(p->sb[0].scrollbar) : 0.0f;
    float y = p->sb[1].scrollbar
        ? (float)VSLOT(int (__thiscall*)(void*), p->sb[1].scrollbar, 0x28)(p->sb[1].scrollbar) : 0.0f;
    if (x != p->mScrollX || y != p->mScrollY) {
        p->mScrollX = x;
        p->mScrollY = y;
        IWindow* iw = (IWindow*)((char*)this + 4);
        VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
    }
    return 1;
}

// @ 0x98a090
void WinTextEdit::F98A090(int idx) {
    IWinTextEdit* p = IFACE(this);
    ScrollbarSlot* s = &p->sb[idx];
    if (s->enabled == 0) {
        if (s->scrollbar) {
            IWindow* iw = (IWindow*)((char*)this + 4);
            VSLOT(void (__thiscall*)(void*, void*), iw, 0xe0)
                (iw, VSLOT(void* (__thiscall*)(void*), s->scrollbar, 0x10)(s->scrollbar));
            if (s->scrollbar) {
                IUnk* old = s->scrollbar;
                s->scrollbar = 0;
                VSLOT(void (__thiscall*)(void*), old, 4)(old);
            }
        }
        return;
    }

    if (s->scrollbar == 0) {
        void* mem = AllocAligned(0x2d0, 8, "UTFWin/WinTextEdit/Scrollbar", GetDefaultAllocator());
        IUnk* ni = 0;
        if (mem) {
            void* ws = ((WinScrollbar*)mem)->Construct();
            if (ws) ni = (IUnk*)((char*)ws + 0x20c);
        }
        IUnk* old = s->scrollbar;
        if (ni != old) {
            if (ni) VSLOT(void (__thiscall*)(void*), ni, 0)(ni);
            s->scrollbar = ni;
            if (old) VSLOT(void (__thiscall*)(void*), old, 4)(old);
        }
        void* o = VSLOT(void* (__thiscall*)(void*), s->scrollbar, 0x10)(s->scrollbar);
        VSLOT(void (__thiscall*)(void*, int, int), o, 0x7c)(o, 0x200, 1);
        VSLOT(void (__thiscall*)(void*, int), s->scrollbar, 0x14)(s->scrollbar, idx == 1 ? 2 : 1);
        IWindow* iw = (IWindow*)((char*)this + 4);
        VSLOT(void (__thiscall*)(void*, void*), iw, 0xd8)
            (iw, VSLOT(void* (__thiscall*)(void*), s->scrollbar, 0x10)(s->scrollbar));
        void* o2 = VSLOT(void* (__thiscall*)(void*), s->scrollbar, 0x10)(s->scrollbar);
        VSLOT(void (__thiscall*)(void*, int), o2, 0x78)(o2, 0x1002);
    }

    if (s->drawable == 0) {
        void* mem = AllocAligned(0x2c, 4, "UTFWin/WinTextEdit/ScrollbarDrawable", GetDefaultAllocator());
        void* d = mem ? ((ScrollbarDrawable*)mem)->Construct() : 0;
        VSLOT(void (__thiscall*)(void*, void*), s->scrollbar, 0x5c)(s->scrollbar, d);
    }

    s->f0c = 20.0f;
    s->f10 = 20.0f;

    struct Rec {
        uint8_t  pad00[4];      // +0x00
        void*    f04;           // +0x04
        uint32_t type;          // +0x08 = 0x16
        uint32_t f0c;           // +0x0c = 0
        uint8_t  pad10[8];      // +0x10
        void*    f18;           // +0x18 = &s->f0c
    };
    Rec rec;
    rec.type = 0x16;
    rec.f0c = 0;
    rec.f18 = &s->f0c;
    IWindow* iw = (IWindow*)((char*)this + 4);
    if (VSLOT(int (__thiscall*)(void*), iw, 0x14)(iw)) {
        void* obj = VSLOT(void* (__thiscall*)(void*), iw, 0x14)(iw);
        void* a = VSLOT(void* (__thiscall*)(void*, void*, int), s->scrollbar, 0x10)(s->scrollbar, &rec.f04, 0);
        void* b = VSLOT(void* (__thiscall*)(void*), s->scrollbar, 0x10)(s->scrollbar);
        VSLOT(void (__thiscall*)(void*, void*, void*), obj, 0x10)(obj, b, a);
    }
}

// @ 0x98a270
void WinTextEdit::F98A270(unsigned idx, int* outBegin, int* outLen) {
    int* vec = *(int**)((char*)this + 0x50c);
    int* vend = *(int**)((char*)this + 0x510);
    int  total = *(int*)((char*)this + 0x520);
    unsigned n = (unsigned)(vend - vec);
    if (idx >= n) {
        *outBegin = total;
        *outLen = 0;
        return;
    }
    int v = vec[idx];
    *outBegin = v;
    if (idx < n - 1)
        *outLen = vec[idx + 1] - v;
    else
        *outLen = total - v;
}

// @ 0x98a2f0
void WinTextEdit::F98A2F0(int flag) {
    (void)flag;
    F98A090(1);
    F98A090(0);
    CalculateVisibleArea();
    IFACE(this)->flags2 |= 4;
}

// @ 0x98a430
unsigned WinTextEdit::SnapIndex(unsigned pos, int* out) {
    Text::TextRun run;
    run.text = textBegin;
    run.style = VSLOT(void* (__thiscall*)(void*), IFACE(this), 0x50)(IFACE(this));
    Text::CharacterBreakIterator it;
    it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
    it.f1c = 0;
    it.SetPosition(pos);
    unsigned a = it.GetNextCharBreak();
    unsigned b = it.GetPrevCharBreak();
    if (out) *out = (int)(a - b);
    return b;
}

// @ 0x98a4b0
unsigned WinTextEdit::F98A4B0(unsigned pos) {
    unsigned n = TextLength();
    bool was = false;
    for (; pos < n; pos++) {
        bool w = iswctype(textBegin[pos], 8) != 0;
        if (!w && was) break;
        was = w;
    }
    Text::TextRun run;
    run.text = textBegin;
    run.style = VSLOT(void* (__thiscall*)(void*), IFACE(this), 0x50)(IFACE(this));
    Text::CharacterBreakIterator it;
    it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
    it.f1c = 0;
    it.SetPosition(pos);
    it.GetNextCharBreak();
    return it.GetPrevCharBreak();
}

// @ 0x98a570
unsigned WinTextEdit::F98A570(unsigned pos) {
    bool word = true;
    while (pos != 0) {
        pos--;
        bool w = iswctype(textBegin[pos], 8) != 0;
        if (w && !word) { pos++; break; }
        word = w;
    }
    Text::TextRun run;
    run.text = textBegin;
    run.style = VSLOT(void* (__thiscall*)(void*), IFACE(this), 0x50)(IFACE(this));
    Text::CharacterBreakIterator it;
    it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
    it.f1c = 0;
    it.SetPosition(pos);
    it.GetNextCharBreak();
    return it.GetPrevCharBreak();
}

// @ 0x98a660
unsigned WinTextEdit::F98A660(unsigned pos) {
    unsigned n = TextLength();
    bool was = false;
    while (pos < n) {
        bool w = iswctype(textBegin[pos], 8) != 0;
        if (w && !was) break;
        pos++;
        was = w;
    }
    if (pos >= n) return n;
    Text::TextRun run;
    run.text = textBegin;
    run.style = VSLOT(void* (__thiscall*)(void*), IFACE(this), 0x50)(IFACE(this));
    Text::CharacterBreakIterator it;
    it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
    it.f1c = 0;
    it.SetPosition(pos);
    it.GetNextCharBreak();
    return it.GetPrevCharBreak();
}

// @ 0x98a730
unsigned WinTextEdit::F98A730(unsigned pos) {
    bool word = true;
    while (pos != 0) {
        pos--;
        bool w = iswctype(textBegin[pos], 8) != 0;
        if (!w && word) { pos++; break; }
        word = w;
    }
    Text::TextRun run;
    run.text = textBegin;
    run.style = VSLOT(void* (__thiscall*)(void*), IFACE(this), 0x50)(IFACE(this));
    Text::CharacterBreakIterator it;
    it.SetTextRunArray(&run, 1, 0, 0, 0xffffffff);
    it.f1c = 0;
    it.SetPosition(pos);
    it.GetNextCharBreak();
    return it.GetPrevCharBreak();
}

// ================================================================ IWinTextEdit interface methods

// @ 0x989a20
int IWinTextEdit::F989A20() {
    return (int)WIN(this)->TextLength();
}

// @ 0x989a30
int IWinTextEdit::F989A30(void* at, unsigned idx, unsigned n) {
    TextWindow* w = WIN(this);
    unsigned len = w->TextLength();
    if (idx >= len) return 0;
    const unsigned& c = emin(n, len - idx);
    ((TextVector*)w->textBegin)->DoInsertValue(idx, at, c * 2);
    return (int)c;
}

// @ 0x989b00
void IWinTextEdit::F989B00(unsigned a, unsigned b) {
    TextWindow* w = WIN(this);
    int len = (int)w->TextLength();
    unsigned u1 = emin(a, (unsigned)len);
    unsigned u2 = emin(b, (unsigned)len);
    if (u1 != cursor || u2 != anchor) {
        flags2 |= 3;
        cursor = u1;
        anchor = u2;
        IWindow* iw = (IWindow*)((char*)this - 0x208);
        VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
    }
}

// @ 0x989b70
char IWinTextEdit::F989B70(unsigned* a, unsigned* b) {
    *a = emin(cursor, anchor);
    *b = emax(cursor, anchor);
    int r = (*a != *b);
    return r & 0xff;
}

// @ 0x989bb0
void IWinTextEdit::F989BB0(uint32_t flag, char on) {
    uint32_t old = flags;
    if (!on) flags = ~flag & flags;
    else     flags |= flag;
    uint32_t diff = flags ^ old;
    if ((diff & 0x21) && !(flags & 0x21))
        ((EA::Stopwatch*)((char*)this + 0x3cc))->Restart();
    f2e8 = (uint32_t)((uint8_t)(flags >> 7) & 1);
    if (diff & 0xb8) {
        IWindow* iw = (IWindow*)((char*)this - 0x208);
        VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
    }
}

// @ 0x989c60
void IWinTextEdit::SetScrollPosition(float* p) {
    if (mScrollX != p[0] || mScrollY != p[1]) {
        mScrollX = p[0];
        mScrollY = p[1];
        if (sb[1].scrollbar)
            VSLOT(void (__thiscall*)(void*, int, int), sb[1].scrollbar, 0x24)
                (sb[1].scrollbar, (int)p[1], 0);
        if (sb[0].scrollbar)
            VSLOT(void (__thiscall*)(void*, int, int), sb[0].scrollbar, 0x24)
                (sb[0].scrollbar, (int)p[0], 0);
        IWindow* iw = (IWindow*)((char*)this - 0x208);
        VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
    }
}

// @ 0x989d10
void* IWinTextEdit::F989D10(int idx) {
    return sb[idx].drawable;
}

// @ 0x989d30
int IWinTextEdit::F989D30(int idx) {
    IUnk* o = sb[idx].scrollbar;
    if (o) {
        void* o2 = VSLOT(void* (__thiscall*)(void*), o, 0x10)(o);
        if (VSLOT(uint32_t (__thiscall*)(void*), o2, 0x28)(o2) & 1) return 1;
    }
    return 0;
}

// @ 0x98a320
void IWinTextEdit::F98A320(float* r) {
    mRect[0] = r[0];
    mRect[1] = r[1];
    mRect[2] = r[2];
    mRect[3] = r[3];
    WinTextEdit* w = (WinTextEdit*)((char*)this - 0x20c);
    w->F98A090(1);
    w->F98A090(0);
    w->CalculateVisibleArea();
    flags2 |= 4;
}

// @ 0x98a370
void IWinTextEdit::F98A370(const wchar_t* str, int arg2) {
    TextWindow* w = WIN(this);
    if (FUN_006ab760(&w->textBegin, str)) return;
    const wchar_t* e = str;
    while (*e) e++;
    unsigned len = (unsigned)(e - str);
    VSLOT(void (__thiscall*)(void*, unsigned, unsigned, const wchar_t*, unsigned, int), this, 0x78)
        (this, 0, 0xffffffff, str, len, arg2);
    if (VSLOT(char (__thiscall*)(void*, int), this, 0x48)(this, 1))
        VSLOT(void (__thiscall*)(void*, int, int), this, 0x8c)(this, 0, 0);
    IWindow* iw = (IWindow*)((char*)this - 0x208);
    VSLOT(void (__thiscall*)(void*), iw, 0x90)(iw);
}

// @ 0x98a3f0
void IWinTextEdit::F98A3F0(int a, int b, int c) {
    unsigned lo = emin(cursor, anchor);
    unsigned hi = emax(cursor, anchor);
    VSLOT(void (__thiscall*)(void*, unsigned, unsigned, int, int, int), this, 0x78)
        (this, lo, hi - lo, a, b, c);
}
