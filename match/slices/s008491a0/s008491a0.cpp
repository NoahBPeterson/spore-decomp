// Slice s008491a0, 0x008491a0-0x00849e30 (EA::App::Canvas window class + arithmetica).
// Optimized module (/O2).
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- win32
extern "C" __declspec(dllimport) int __stdcall SetWindowTextW(void* hwnd, const wchar_t* text);

// ---------------------------------------------------------------- EASTL-ish
void EASTL_allocator_deallocate(void* p);   // 0x00f47380

// EA's own wide-string length (inlined, not the CRT intrinsic).
inline size_t EAStrLenW(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (size_t)(p - s);
}

// 16-byte eastl::basic_string<wchar_t> (empty allocator).
struct WString {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8
    uint32_t mAllocPad;    // +c
    WString& assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

struct Canvas;

// Payload carried by EA::App::Canvas events (16 bytes).
struct CanvasEventData { uint32_t v[4]; };

struct CanvasEvent {
    uint32_t        mCommand;    // +0x00
    Canvas*         mpSender;    // +0x04
    void*           mpData;      // +0x08
    uint32_t        mPad;        // +0x0c
    CanvasEventData mResult;     // +0x10
    CanvasEventData mExtra;      // +0x20
};

struct Canvas {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual CanvasEventData* v15(CanvasEventData* out);   // vftable +0x3c
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22();
    virtual char v23();                                   // vftable +0x5c

    int      mStyle;              // +0x04
    int      m08;                 // +0x08
    uint8_t  b0c, b0d, b0e, b0f;  // +0x0c
    uint8_t  b10, b11;            // +0x10
    uint16_t w12;                 // +0x12
    int      m14;                 // +0x14
    int      m18;                 // +0x18
    uint8_t  b1c;                 // +0x1c
    uint8_t  pad1d[3];            // +0x1d
    int      m20;                 // +0x20
    WString  msCaption;           // +0x24
    int      m34, m38, m3c, m40, m44, m48;   // +0x34
    uint8_t  b4c, b4d, b4e, b4f;  // +0x4c
    int      m50;                 // +0x50
    int      m54, m58, m5c, m60, m64, m68;   // +0x54
    uint8_t  b6c, b6d, b6e;       // +0x6c
    uint16_t w70;                 // +0x70
    uint16_t pad72;               // +0x72
    void*    mhWndParent;         // +0x74
    int      m78, m7c;            // +0x78
    int      m80;                 // +0x80
    uint32_t mWin32StyleEx;       // +0x84
    uint32_t mWin32Style;         // +0x88
    int      m8c, m90, m94;       // +0x8c

    void Show();                  // 0x008490d0
    void Shutdown();              // 0x00848020
    void TrackClientRect();       // 0x008484f0
    void SendCanvasEvent(CanvasEvent* ev);   // 0x00847e70

    Canvas();                              // @ 0x00849a40
    void OnInput(int, int, int);           // @ 0x008491a0
    void SetStyle(int style);              // @ 0x00849d20
    Canvas* ScalarDtor(unsigned flags);    // @ 0x00849da0
    void SetCaption(const wchar_t* cap);   // @ 0x00849df0
};

// @ 0x00849a40
Canvas::Canvas()
{
    mStyle = 0xf;
    m08 = 0x2a;
    b0c = 0; b0d = 0; b0e = 0; b0f = 0;
    b10 = 0; b11 = 0;
    m14 = 0;
    m18 = 0;
    b1c = 0;
    m20 = 0;
    msCaption.mpCapacity = (wchar_t*)0x1667bae;
    msCaption.mpBegin = (wchar_t*)0x1667bac;
    msCaption.mpEnd = (wchar_t*)0x1667bac;
    m34 = 0; m38 = 0; m3c = 0; m40 = 0; m44 = 0; m48 = 0;
    b4c = 1; b4d = 0; b4e = 0; b4f = 0;
    m50 = 0x7d0;
    m54 = 0; m58 = 0; m5c = 0; m60 = 0; m64 = 0; m68 = 0;
    b6c = 0; b6d = 0; b6e = 0;
    w70 = 0;
    mhWndParent = 0;
    m78 = 0; m7c = 0;
    m80 = 0;
    mWin32StyleEx = 0xc80000;
    mWin32Style = 0;
    m8c = 0; m90 = 0; m94 = 0;
}

// @ 0x008491a0
void Canvas::OnInput(int, int, int)
{
    uint32_t code = 1;
    if (b0e) {
        code = 0x11;
        b10 = 1;
    }
    TrackClientRect();
    if (!v23()) {
        CanvasEventData tmp;
        CanvasEventData* p = v15(&tmp);
        CanvasEvent ev;
        ev.mCommand = 0x1ee1003;
        ev.mpSender = this;
        ev.mpData = &ev.mExtra;
        ev.mPad = 0;
        ev.mResult = *p;
        SendCanvasEvent(&ev);
    }
}

// @ 0x00849d20
void Canvas::SetStyle(int style)
{
    if (style != -1)
        mStyle = style;
    unsigned s = (unsigned)mStyle;
    mWin32StyleEx = 0x80000;
    mWin32Style = 0;
    if (s & 2)
        mWin32StyleEx = 0xa0000;
    if (s & 4)
        mWin32StyleEx |= 0x10000;
    if (s & 1) {
        mWin32StyleEx |= 0x40000;
        mWin32Style = 0x300;
    }
    if (s & 8)
        mWin32StyleEx |= 0xc00000;
    if (mhWndParent)
        Show();
}

// @ 0x00849da0
Canvas* Canvas::ScalarDtor(unsigned flags)
{
    *(void**)this = (void*)0x141ca70;   // vftable
    Shutdown();
    int n = (int)((char*)msCaption.mpCapacity - (char*)msCaption.mpBegin);
    if ((n & ~1) > 2 && msCaption.mpBegin)
        EASTL_allocator_deallocate(msCaption.mpBegin);
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x00849df0
void Canvas::SetCaption(const wchar_t* cap)
{
    msCaption.assign(cap, cap + EAStrLenW(cap));
    SetWindowTextW(mhWndParent, cap);
}

// ---------------------------------------------------------------------------
// Not reconstructed (see partial.txt): these are very large / rely on large
// inlined interpreter and EASTL templates whose exact bodies are not recovered.
// ---------------------------------------------------------------------------

// @ 0x00849230  (EA::App::Canvas::WindowProc, 2058 bytes)
void __cdecl FUN_00849230() {}
// @ 0x00849b10  (EA::App::Canvas::Init, 515 bytes)
void __cdecl FUN_00849b10() {}
// @ 0x00849e30  (eastl::vector<tagMSG>::insert, 318 bytes)
void __cdecl FUN_00849e30() {}
