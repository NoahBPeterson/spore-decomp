// Slice s008491a0, 0x008491a0-0x00849e30 (EA::App::Canvas window class + arithmetica).
// Optimized module (/O2).
#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------- win32
typedef void* HWND;
typedef void* HDC;
typedef void* HBRUSH;
typedef void* HCURSOR;
typedef void* HICON;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HMENU;
typedef void* HKL;
typedef const char* LPCSTR;
typedef const wchar_t* LPCWSTR;
typedef unsigned short WCHAR;
typedef unsigned short ATOM;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef long LRESULT;
typedef unsigned long DWORD;
typedef long LONG;
typedef long LONG_PTR;

struct POINT { long x, y; };

struct WNDCLASSEXA {
    UINT      cbSize;
    UINT      style;
    void*     lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    void*     hCursor;
    HBRUSH    hbrBackground;
    LPCSTR    lpszMenuName;
    LPCSTR    lpszClassName;
    HICON     hIconSm;
};

struct WNDCLASSEXW {
    UINT      cbSize;
    UINT      style;
    void*     lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    void*     hCursor;
    HBRUSH    hbrBackground;
    LPCWSTR   lpszMenuName;
    LPCWSTR   lpszClassName;
    HICON     hIconSm;
};

extern "C" {
__declspec(dllimport) int __stdcall SetWindowTextW(void* hwnd, const wchar_t* text);
__declspec(dllimport) LONG __stdcall GetWindowLongA(HWND, int);
__declspec(dllimport) LONG __stdcall SetWindowLongW(HWND, int, LONG);
__declspec(dllimport) LRESULT __stdcall DefWindowProcW(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) HCURSOR __stdcall SetCursor(HCURSOR);
__declspec(dllimport) HWND __stdcall GetForegroundWindow(void);
__declspec(dllimport) BOOL __stdcall ClientToScreen(HWND, POINT*);
__declspec(dllimport) BOOL __stdcall SetCursorPos(int, int);
__declspec(dllimport) HKL __stdcall GetKeyboardLayout(DWORD);
__declspec(dllimport) int __stdcall GetLocaleInfoW(DWORD, DWORD, WCHAR*, int);
__declspec(dllimport) unsigned long __cdecl wcstoul(const WCHAR*, WCHAR**, int);
__declspec(dllimport) HBRUSH __stdcall CreateSolidBrush(DWORD);
__declspec(dllimport) HMODULE __stdcall GetModuleHandleA(LPCSTR);
__declspec(dllimport) HCURSOR __stdcall LoadCursorA(HINSTANCE, LPCSTR);
__declspec(dllimport) BOOL __stdcall EnumResourceNamesA(
    HMODULE, LPCSTR,
    int (__stdcall*)(HINSTANCE, void*, LPCSTR, WNDCLASSEXA*), LONG_PTR);
__declspec(dllimport) ATOM __stdcall RegisterClassExW(const WNDCLASSEXW*);
__declspec(dllimport) HWND __stdcall CreateWindowExW(DWORD, LPCWSTR, LPCWSTR, DWORD,
                                                    int, int, int, int, HWND, HMENU,
                                                    HINSTANCE, void*);
__declspec(dllimport) BOOL __stdcall ShowWindow(HWND, int);
__declspec(dllimport) BOOL __stdcall UpdateWindow(HWND);
__declspec(dllimport) unsigned __stdcall SetTimer(HWND, unsigned, UINT, void*);
__declspec(dllimport) BOOL __stdcall SystemParametersInfoA(UINT, UINT, void*, UINT);
}

#define CW_USEDEFAULT ((int)0x80000000)

// 0x00847950: EnumResourceNamesA callback that installs the canvas resource names.
int __stdcall FUN_00847950(HINSTANCE, void*, LPCSTR, WNDCLASSEXA*);

// ---------------------------------------------------------------- EASTL-ish
void* EAAllocate(unsigned size, const char* name, int a, int b, int file, int line);  // 0x00f473a0
void EASTL_allocator_deallocate(void* p);   // 0x00f47380

// 0x00847ff0: out-of-line eastl::copy<tagMSG> (7 dwords per element, returns dest end).
struct tagMSG;
tagMSG* CopyMsgs(tagMSG* first, tagMSG* last, tagMSG* dest);

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

// Minimal 12-byte canvas event (command, sender, payload) used by
// Canvas::Init's notification.
struct CanvasEventSmall {
    uint32_t mCommand;    // +0x00
    Canvas*  mpSender;    // +0x04
    void*    mpData;      // +0x08
};

struct CanvasEvent {
    uint32_t        mCommand;    // +0x00
    Canvas*         mpSender;    // +0x04
    void*           mpData;      // +0x08
    uint32_t        mPad;        // +0x0c
    CanvasEventData mResult;     // +0x10
    CanvasEventData mExtra;      // +0x20
};

// Win32-message event forwarded to the canvas message server (+0x5c) by the
// window procedure.  mpPayload points at mhWnd so the four wnd-proc arguments
// are contiguous.
struct CanvasWinMsgEvent {
    uint32_t mCommand;    // +0x00  0x1ee100c
    Canvas*  mpSender;    // +0x04
    void*    mpPayload;   // +0x08  -> &mhWnd
    HWND     mhWnd;       // +0x0c
    UINT     mMessage;    // +0x10
    WPARAM   mWParam;     // +0x14
    LPARAM   mLParam;     // +0x18
    LRESULT  mResult;     // +0x1c
    uint8_t  mbHandled;   // +0x20
    uint8_t  mPad[3];     // +0x21
};

// Message-server virtual slot +0x14: (command, event, reserved).
typedef void (__fastcall *MsgServerDispatch)(void* self, void* edx, uint32_t command,
                                             void* ev, void* reserved);

struct Canvas {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual char v09();                                   // vftable +0x24
    virtual void v10(int);                                // vftable +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual CanvasEventData* v15(CanvasEventData* out);   // vftable +0x3c
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual char v21();                                   // vftable +0x54
    virtual void v22();
    virtual char v23();                                   // vftable +0x5c

    int      mStyle;                 // +0x04
    int      m08;                    // +0x08
    uint8_t  mbFullscreen;           // +0x0c
    uint8_t  pad0d;                  // +0x0d
    uint8_t  mbInMovingSizingLoop;   // +0x0e
    uint8_t  mbInSizingLoop;         // +0x0f
    uint8_t  mbInMovingLoop;         // +0x10
    uint8_t  mbMouseInClientArea;    // +0x11
    uint16_t w12;                    // +0x12
    int      m14;                    // +0x14
    int      m18;                    // +0x18
    uint8_t  b1c;                    // +0x1c
    uint8_t  pad1d[3];               // +0x1d
    int      m20;                    // +0x20
    WString  msCaption;              // +0x24
    int      m34, m38;               // +0x34
    int      mRectDesiredLeft;       // +0x3c
    int      mRectDesiredTop;        // +0x40
    int      mRectDesiredRight;      // +0x44
    int      mRectDesiredBottom;     // +0x48
    uint8_t  mbCursorVisible;        // +0x4c
    uint8_t  mbCursorShadowSupported;// +0x4d
    uint8_t  mbMouseTrailsSupported; // +0x4e
    uint8_t  mbMouseSonarSupported;  // +0x4f
    int      mnIdleTimerIntervalMs;  // +0x50
    uint32_t mnSystemLCID;           // +0x54
    uint32_t mnSystemCodePage;       // +0x58
    void*    mpMessageServer;        // +0x5c
    int      m60, m64, m68;          // +0x60
    uint8_t  mbLButtonDown;          // +0x6c
    uint8_t  mbMButtonDown;          // +0x6d
    uint8_t  mbRButtonDown;          // +0x6e
    uint16_t mClassAtom;             // +0x70
    uint16_t pad72;                  // +0x72
    void*    mhWndParent;            // +0x74  (created top-level window)
    void*    mhWndOwner;             // +0x78  (hWndParent passed to CreateWindowExW)
    HCURSOR  mhCursor;               // +0x7c
    HBRUSH   mhBackgroundBrush;      // +0x80
    uint32_t mWin32StyleEx;          // +0x84
    uint32_t mWin32Style;            // +0x88
    int      mCursorShadow;          // +0x8c
    int      mMouseTrails;           // +0x90
    int      mMouseSonar;            // +0x94

    bool Init();                     // 0x00849b10
    void Show();                     // 0x008490d0
    void Shutdown();                 // 0x00848020
    void TrackClientRect();          // 0x008484f0
    void SendCanvasEvent(CanvasEvent* ev);   // 0x00847e70

    void OnPaint(HWND hwnd);                                        // 0x00848340
    int  OnEraseBackground(HWND hwnd, HDC hdc);                     // 0x00847b60
    void FUN_00847c70(int hwnd, int flag);                          // 0x00847c70
    void FUN_00847cc0(HWND hwnd, int edge, void* rc);               // 0x00847cc0
    void FUN_00847da0(int hwnd, unsigned flag, int value);          // 0x00847da0
    void FUN_00847e20(unsigned short lcid);                         // 0x00847e20
    void FUN_00848bb0(unsigned hwnd, int* rc);                      // 0x00848bb0
    void FUN_00848d70(int hwnd, int lo, int lparam, int hi);        // 0x00848d70
    void FUN_00848de0(int hwnd, int wparam, int lparam);            // 0x00848de0
    void FUN_00848e10(int hwnd, int wparam, int lo, int hi);        // 0x00848e10
    void FUN_00848e40(int hwnd, HWND shape);                        // 0x00848e40

    void OnKeyDown(HWND, unsigned, unsigned, unsigned, unsigned);   // 0x00848540
    void OnKeyUp(HWND, unsigned, unsigned, unsigned, unsigned);     // 0x00848620
    void OnWChar(HWND, unsigned short, unsigned short);             // 0x008486f0
    void OnMouseMove(HWND, int, int, unsigned);                     // 0x00848750
    void OnMouseLeave(HWND);                                        // 0x008487f0
    void OnMouseWheel(HWND, unsigned, int);                         // 0x00848870
    void OnLButtonDown(HWND, unsigned, int, int, unsigned);         // 0x008489e0
    void OnMButtonDown(HWND, unsigned, int, int, unsigned);         // 0x00848a20
    void OnRButtonDown(HWND, unsigned, int, int, unsigned);         // 0x00848a60
    void OnLButtonUp(HWND, int, int, unsigned);                     // 0x00848aa0
    void OnMButtonUp(HWND, int, int, unsigned);                     // 0x00848ae0
    void OnRButtonUp(HWND, int, int, unsigned);                     // 0x00848b20
    void OnClose(HWND);                                             // 0x00848b60
    void OnSize(HWND, int, int, int);                               // 0x00848c20
    void OnExitSizeMove(int);                                       // 0x00848cb0
    void OnActivate(int, int);                                      // 0x00848d40

    Canvas();                              // @ 0x00849a40
    void OnInput(int, int, int);           // @ 0x008491a0
    void SetStyle(int style);              // @ 0x00849d20
    Canvas* ScalarDtor(unsigned flags);    // @ 0x00849da0
    void SetCaption(const wchar_t* cap);   // @ 0x00849df0
};

extern char* g_01650388;   // 0x01650388: global window/message-server slot holder

LRESULT __stdcall CanvasWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 32-byte tagMSG element queued by Canvas::FlushInput.
struct tagMSG {
    HWND   hwnd;        // +0x00
    UINT   message;     // +0x04
    WPARAM wParam;      // +0x08
    LPARAM lParam;      // +0x0c
    DWORD  time;        // +0x10
    POINT  pt;          // +0x14
};

// eastl::vector<tagMSG> (no allocator member; the first element is stamped).
struct MsgVec {
    tagMSG* mpBegin;      // +0x00
    tagMSG* mpEnd;        // +0x04
    tagMSG* mpCapacity;   // +0x08

    tagMSG* DoAllocate(unsigned n)
    {
        return n ? (tagMSG*)EAAllocate(n * 0x1c, "EASTL", 0, 0, 0x13ebb38, 0xd1) : 0;
    }
    void DoFree(tagMSG* p)
    {
        if (p && ((int*)p)[-1])
            EASTL_allocator_deallocate(p);
    }
    void insert(tagMSG* position, const tagMSG& value);   // 0x00849e30
};

// @ 0x00849a40
Canvas::Canvas()
{
    mStyle = 0xf;
    m08 = 0x2a;
    mbFullscreen = 0; pad0d = 0; mbInMovingSizingLoop = 0; mbInSizingLoop = 0;
    mbInMovingLoop = 0; mbMouseInClientArea = 0;
    m14 = 0;
    m18 = 0;
    b1c = 0;
    m20 = 0;
    msCaption.mpCapacity = (wchar_t*)0x1667bae;
    msCaption.mpBegin = (wchar_t*)0x1667bac;
    msCaption.mpEnd = (wchar_t*)0x1667bac;
    m34 = 0; m38 = 0;
    mRectDesiredLeft = 0; mRectDesiredTop = 0;
    mRectDesiredRight = 0; mRectDesiredBottom = 0;
    mbCursorVisible = 1; mbCursorShadowSupported = 0;
    mbMouseTrailsSupported = 0; mbMouseSonarSupported = 0;
    mnIdleTimerIntervalMs = 0x7d0;
    mnSystemLCID = 0; mnSystemCodePage = 0; mpMessageServer = 0;
    m60 = 0; m64 = 0; m68 = 0;
    mbLButtonDown = 0; mbMButtonDown = 0; mbRButtonDown = 0;
    mClassAtom = 0;
    mhWndParent = 0;
    mhWndOwner = 0; mhCursor = 0;
    mhBackgroundBrush = 0;
    mWin32StyleEx = 0xc80000;
    mWin32Style = 0;
    mCursorShadow = 0; mMouseTrails = 0; mMouseSonar = 0;
}

// @ 0x008491a0
void Canvas::OnInput(int, int, int)
{
    uint32_t code = 1;
    if (mbInMovingSizingLoop) {
        code = 0x11;
        mbInMovingLoop = 1;
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

// @ 0x00849230
LRESULT __stdcall CanvasWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Canvas* ths = (Canvas*)GetWindowLongA(hwnd, -0x15);
    if (!ths)
        return DefWindowProcW(hwnd, msg, wParam, lParam);

    // The Win32-message event and the 0x501 POINT share one stack slot
    // (their lifetimes are disjoint), as in the original frame.
    union {
        CanvasWinMsgEvent ev;
        POINT pt;
    } u;

    if (ths->mpMessageServer) {
        u.ev.mCommand = 0x1ee100c;
        u.ev.mpSender = ths;
        u.ev.mpPayload = &u.ev.mhWnd;
        u.ev.mhWnd = hwnd;
        u.ev.mMessage = msg;
        u.ev.mWParam = wParam;
        u.ev.mLParam = lParam;
        u.ev.mResult = 0;
        u.ev.mbHandled = 0;
        void* server = ths->mpMessageServer;
        (*(MsgServerDispatch)(*(void**)(*(char**)server + 0x14)))(server, 0, u.ev.mCommand, &u.ev, 0);
        if (u.ev.mbHandled)
            return u.ev.mResult;
    }

    switch (msg) {
    case 0x0f: ths->OnPaint(hwnd); return 0;
    case 0x14: return ths->OnEraseBackground(hwnd, (HDC)wParam);
    case 0x10: ths->OnClose(hwnd); return 0;
    case 0x24: ths->FUN_00848bb0((unsigned)hwnd, (int*)lParam); return 0;
    case 0x03: ths->OnInput((int)hwnd, (short)lParam,
                            (short)((unsigned)lParam >> 16)); return 0;
    case 0x05: ths->OnSize(hwnd, (int)wParam, (short)lParam,
                           (short)((unsigned)lParam >> 16)); return 0;
    case 0x06: ths->FUN_00848d70((int)hwnd, (int)(unsigned short)wParam, (int)lParam,
                                 (int)(wParam >> 16)); return 0;
    case 0x1c: ths->FUN_00848de0((int)hwnd, (int)wParam, (int)lParam); return 0;
    case 0x86:
        if (wParam == 0 && ths->v09() < 0 && ths->v21() != 0)
            return 0;
        ths->OnActivate((int)hwnd, wParam == 1);
        break;
    case 0x7e: ths->FUN_00848e10((int)hwnd, (int)wParam, (int)(unsigned short)lParam,
                                 (int)((unsigned)lParam >> 16)); return 0;
    case 0x1a: ths->FUN_00847da0((int)hwnd, wParam, (int)lParam); return 0;
    case 0x51:
        ths->FUN_00847e20((unsigned short)lParam);
        break;
    case 0x20:
        if (wParam != 0 && (unsigned short)lParam == 1) {
            if (ths->mhCursor)
                SetCursor(ths->mhCursor);
            return 1;
        }
        break;
    case 0x100: ths->OnKeyDown(hwnd, wParam, 1, (short)lParam,
                               (short)((unsigned)lParam >> 16)); return 0;
    case 0x104: ths->OnKeyDown(hwnd, wParam, 1, (short)lParam,
                               (short)((unsigned)lParam >> 16)); return 0;
    case 0x101: ths->OnKeyUp(hwnd, wParam, 0, (short)lParam,
                             (short)((unsigned)lParam >> 16)); return 0;
    case 0x105: ths->OnKeyUp(hwnd, wParam, 0, (short)lParam,
                             (short)((unsigned)lParam >> 16)); return 0;
    case 0x102: ths->OnWChar(hwnd, (unsigned short)wParam, (short)lParam); return 0;
    case 0x113: ths->FUN_00847c70((int)hwnd, (int)wParam); return 0;
    case 0x200: ths->OnMouseMove(hwnd, (short)lParam,
                                 (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x201: ths->OnLButtonDown(hwnd, 0, (short)lParam,
                                   (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x203: ths->OnLButtonDown(hwnd, 1, (short)lParam,
                                   (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x207: ths->OnMButtonDown(hwnd, 0, (short)lParam,
                                   (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x209: ths->OnMButtonDown(hwnd, 1, (short)lParam,
                                   (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x204: ths->OnRButtonDown(hwnd, 0, (short)lParam,
                                   (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x206: ths->OnRButtonDown(hwnd, 1, (short)lParam,
                                   (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x202: ths->OnLButtonUp(hwnd, (short)lParam,
                                 (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x208: ths->OnMButtonUp(hwnd, (short)lParam,
                                 (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x205: ths->OnRButtonUp(hwnd, (short)lParam,
                                 (short)((unsigned)lParam >> 16), wParam); return 0;
    case 0x214: ths->FUN_00847cc0(hwnd, (int)wParam, (void*)lParam); return 1;
    case 0x20a: ths->OnMouseWheel(hwnd, wParam, (int)lParam); return 0;
    case 0x215: ths->FUN_00848e40((int)hwnd, (HWND)lParam); return 0;
    case 0x120: {
        LRESULT r = DefWindowProcW(hwnd, msg, wParam, lParam);
        return r == 0 ? 0x10000 : r;
    }
    case 0x231: ths->mbInMovingSizingLoop = 1; return 0;
    case 0x2a3: ths->OnMouseLeave(hwnd); return 0;
    case 0x232: ths->OnExitSizeMove((int)hwnd); return 0;
    case 0x500:
        if (!lParam)
            return 0;
        ths->mhCursor = (HCURSOR)lParam;
        SetCursor((HCURSOR)lParam);
        return 0;
    case 0x501: {
        HWND wnd = (HWND)ths->mhWndParent;
        u.pt.x = (short)lParam;
        u.pt.y = (short)((unsigned)lParam >> 16);
        if (GetForegroundWindow() != wnd)
            return 0;
        ClientToScreen(wnd, &u.pt);
        SetCursorPos((int)u.pt.x, (int)u.pt.y);
        return 0;
    }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// @ 0x00849b10
bool Canvas::Init()
{
    if (mhWndParent)
        return true;

    HKL hkl = GetKeyboardLayout(0);
    mnSystemLCID = (unsigned short)(unsigned)hkl;
    WCHAR locale[128];
    GetLocaleInfoW(mnSystemLCID, 0x1004, locale, 0x80);
    mnSystemCodePage = wcstoul(locale, 0, 10);
    mhBackgroundBrush = CreateSolidBrush(0x41235f);

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(wc);
    wc.style = 8;
    wc.lpfnWndProc = (void*)CanvasWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(0);
    wc.hIcon = 0;
    wc.hCursor = LoadCursorA(0, (LPCSTR)0x7f00);
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"Canvas";
    wc.hIconSm = 0;
    EnumResourceNamesA(GetModuleHandleA(0), (LPCSTR)0xe, FUN_00847950, (LONG_PTR)&wc);
    mClassAtom = RegisterClassExW(&wc);

    mhWndParent = CreateWindowExW(mWin32Style, (LPCWSTR)(unsigned)mClassAtom, 0, mWin32StyleEx,
                                  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                  (HWND)mhWndOwner, 0, GetModuleHandleA(0), 0);
    mhCursor = LoadCursorA(0, (LPCSTR)0x7f00);
    SetWindowLongW(mhWndParent, -0x15, (LONG)this);
    ShowWindow(mhWndParent, 0);
    UpdateWindow(mhWndParent);

    CanvasEventData rc;
    CanvasEventData* p = v15(&rc);
    mRectDesiredLeft = p->v[0];
    mRectDesiredTop = p->v[1];
    mRectDesiredRight = p->v[2];
    mRectDesiredBottom = p->v[3];

    _ReadWriteBarrier();   // pin the mhWndParent load below the rect stores
    *(void**)(g_01650388 + 0x10) = mhWndParent;
    SetTimer(mhWndParent, 0, mnIdleTimerIntervalMs, 0);
    v10(0x2a);

    mbCursorShadowSupported = SystemParametersInfoA(0x101a, 0, &mCursorShadow, 0) != 0;
    mbMouseTrailsSupported = SystemParametersInfoA(0x5e, 0, &mMouseTrails, 0) != 0;
    mbMouseSonarSupported = SystemParametersInfoA(0x101c, 0, &mMouseSonar, 0) != 0;

    CanvasEventSmall ev;
    ev.mCommand = 0x1ee1004;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent((CanvasEvent*)&ev);
    return true;
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

// @ 0x00849e30
void MsgVec::insert(tagMSG* position, const tagMSG& value)
{
    if (mpEnd != mpCapacity) {
        const tagMSG* pValue = &value;
        if (&value >= position && &value < mpEnd)
            pValue = &value + 1;
        if (mpEnd)
            *mpEnd = *(mpEnd - 1);
        tagMSG* pDst = mpEnd;
        tagMSG* pSrc = mpEnd - 1;
        while (pSrc != position) {
            --pSrc;
            --pDst;
            *pDst = *pSrc;
        }
        *position = *pValue;
        mpEnd += 1;
        return;
    }

    unsigned oldSize = (unsigned)(mpEnd - mpBegin);
    unsigned newSize = oldSize ? oldSize * 2 : 1;
    tagMSG* pNewData = DoAllocate(newSize);
    tagMSG* p = CopyMsgs(mpBegin, position, pNewData);
    if (p)
        *p = value;
    tagMSG* pNewEnd = CopyMsgs(position, mpEnd, p + 1);
    DoFree(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + newSize;
}
