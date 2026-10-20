// Slice s00848210: EA::App::Canvas window-message handlers (UTFSpore_Win32/EACanvas.obj).
#include "types.h"

// ---------------------------------------------------------------------------
// Win32
// ---------------------------------------------------------------------------
typedef void* HWND;
typedef void* HDC;
typedef void* HBRUSH;
typedef void* HGDIOBJ;
typedef void* HMONITOR;
typedef void* HMODULE;
typedef void* FARPROC;
typedef void* HMENU;
typedef const char* LPCSTR;
typedef unsigned short WCHAR;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef unsigned long DWORD;
typedef long LONG;
typedef unsigned long ULONG_PTR;

struct RECT { long left, top, right, bottom; };
struct POINT { long x, y; };

struct MSG {
    HWND   hwnd;
    UINT   message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD  time;
    POINT  pt;
};

struct PAINTSTRUCT {
    HDC  hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    unsigned char rgbReserved[32];
};

extern "C" {
__declspec(dllimport) BOOL __stdcall PeekMessageW(MSG*, HWND, UINT, UINT, UINT);
__declspec(dllimport) BOOL __stdcall TranslateMessage(const MSG*);
__declspec(dllimport) LPARAM __stdcall DispatchMessageW(const MSG*);
__declspec(dllimport) BOOL __stdcall InvalidateRect(HWND, const RECT*, BOOL);
__declspec(dllimport) HDC __stdcall BeginPaint(HWND, PAINTSTRUCT*);
__declspec(dllimport) BOOL __stdcall EndPaint(HWND, const PAINTSTRUCT*);
__declspec(dllimport) BOOL __stdcall GetClientRect(HWND, RECT*);
__declspec(dllimport) int __stdcall FillRect(HDC, const RECT*, HBRUSH);
__declspec(dllimport) short __stdcall GetKeyState(int);
__declspec(dllimport) BOOL __stdcall ScreenToClient(HWND, POINT*);
__declspec(dllimport) BOOL __stdcall SystemParametersInfoA(UINT, UINT, void*, UINT);
__declspec(dllimport) HWND __stdcall SetCapture(HWND);
__declspec(dllimport) BOOL __stdcall ReleaseCapture(void);
__declspec(dllimport) BOOL __stdcall IntersectRect(RECT*, const RECT*, const RECT*);
__declspec(dllimport) int __stdcall GetSystemMetrics(int);
__declspec(dllimport) HMENU __stdcall GetMenu(HWND);
__declspec(dllimport) BOOL __stdcall AdjustWindowRectEx(RECT*, DWORD, BOOL, DWORD);
__declspec(dllimport) BOOL __stdcall MoveWindow(HWND, int, int, int, int, BOOL);
__declspec(dllimport) LONG __stdcall GetWindowLongA(HWND, int);
__declspec(dllimport) LONG __stdcall SetWindowLongA(HWND, int, LONG);
__declspec(dllimport) BOOL __stdcall SetWindowPos(HWND, HWND, int, int, int, int, UINT);
__declspec(dllimport) BOOL __stdcall ShowWindow(HWND, int);
__declspec(dllimport) BOOL __stdcall IsWindowVisible(HWND);
__declspec(dllimport) void __stdcall SetLastError(DWORD);
__declspec(dllimport) void __stdcall PostQuitMessage(int);
__declspec(dllimport) BOOL __stdcall EnumDisplayMonitors(HDC, const RECT*, void*, LPARAM);
}

namespace EA { namespace Thread {
void ThreadSleep(const int* milliseconds);
}}

// ---------------------------------------------------------------------------
// Canvas
// ---------------------------------------------------------------------------
struct Canvas;

struct CanvasEvent {
    unsigned mType;      // +0x00
    Canvas*  mpSender;   // +0x04
    void*    mpData;     // +0x08
};

struct Canvas {
    virtual void  v00(); virtual void  v01(); virtual void  v02(); virtual void  v03();
    virtual void  v04(); virtual void  v05(); virtual void  v06(); virtual void  v07();
    virtual void  v08(int); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void  v12(); virtual void  v13(); virtual void  v14();
    virtual RECT* v15(RECT* out);                                          // +0x3c
    virtual void  v16(int, int, unsigned, unsigned, int);                  // +0x40
    virtual bool  v17();                                                   // +0x44
    virtual void  v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void  v22();
    virtual bool  v23();                                                   // +0x5c
    virtual bool  v24();                                                   // +0x60
    virtual void  v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void  v29(); virtual void v30(); virtual void v31(); virtual void v32();
    virtual void  v33(); virtual void v34(); virtual void v35(); virtual void v36();
    virtual void  v37(); virtual void v38();
    virtual int   v39();                                                   // +0x9c

    int      mStyle;                      // +0x04
    unsigned mnOptionFlags;               // +0x08
    unsigned char mbFullscreen;           // +0x0c
    unsigned char pad0d;                  // +0x0d
    unsigned char mbInMovingSizingLoop;   // +0x0e
    unsigned char mbInSizingLoop;         // +0x0f
    unsigned char mbInMovingLoop;         // +0x10
    unsigned char mbMouseInClientArea;    // +0x11
    unsigned char pad12[2];               // +0x12
    int      mnLastMouseX;                // +0x14
    int      mnLastMouseY;                // +0x18
    unsigned char mbEnablePaint;          // +0x1c
    unsigned char pad1d[3];               // +0x1d
    unsigned mnUpdateLockCount;           // +0x20
    unsigned char pad24[0x10];            // +0x24
    unsigned mnMinWidth;                  // +0x34
    unsigned mnMinHeight;                 // +0x38
    int      mRectDesiredLeft;            // +0x3c
    int      mRectDesiredTop;             // +0x40
    int      mRectDesiredRight;           // +0x44
    int      mRectDesiredBottom;          // +0x48
    unsigned char pad4c;                  // +0x4c
    unsigned char mbCursorShadowSupported; // +0x4d
    unsigned char mbMouseTrailsSupported;  // +0x4e
    unsigned char mbMouseSonarSupported;   // +0x4f
    unsigned char pad50[4];               // +0x50
    unsigned mnSystemLCID;                // +0x54
    unsigned mnSystemCodePage;            // +0x58
    void*    mpMessageServer;             // +0x5c
    void*    mpInputMan;                  // +0x60
    void (*mpCanvasEventCallback)(CanvasEvent*, void*);   // +0x64
    void*    mpCanvasEventCallbackContext;                // +0x68
    unsigned char mbLButtonDown;          // +0x6c
    unsigned char mbMButtonDown;          // +0x6d
    unsigned char mbRButtonDown;          // +0x6e
    unsigned char pad6f;                  // +0x6f
    unsigned short mClassAtom;            // +0x70
    unsigned short pad72;                 // +0x72
    HWND     mhWndParent;                 // +0x74
    unsigned char pad78[8];               // +0x78
    HBRUSH   mhBackgroundBrush;           // +0x80
    DWORD    mWin32Style;                 // +0x84
    DWORD    mWin32StyleEx;               // +0x88
    int      mCursorShadow;               // +0x8c
    int      mMouseTrails;                // +0x90
    int      mMouseSonar;                 // +0x94

    char Tick();
    void OnPaint(HWND hwnd);
    void SetClientRect();
    void TrackClientRect();
    void OnKeyDown(HWND, unsigned, unsigned, unsigned, unsigned);
    void OnKeyUp(HWND, unsigned, unsigned, unsigned, unsigned);
    void OnWChar(HWND, unsigned short, unsigned short);
    void OnMouseMove(HWND, int, int, unsigned);
    void OnMouseLeave(HWND);
    void OnMouseWheel(HWND, unsigned, int);
    void OnMouseButtonChange(int, unsigned char, unsigned, int, int, unsigned);
    void OnLButtonDown(HWND, unsigned, int, int, unsigned);
    void OnMButtonDown(HWND, unsigned, int, int, unsigned);
    void OnRButtonDown(HWND, unsigned, int, int, unsigned);
    void OnLButtonUp(HWND, int, int, unsigned);
    void OnMButtonUp(HWND, int, int, unsigned);
    void OnRButtonUp(HWND, int, int, unsigned);
    void OnClose(HWND);
    void OnSize(HWND, int, int, int);
    void OnExitSizeMove(int);
    void OnActivate(int, int);
    void SetFullscreen(char, int, int);
    void Show();
    void SendCanvasEvent(CanvasEvent*);
    void OnMouseEnter(HWND);
    void FUN_00848bb0(unsigned, int*);
    void FUN_00848d70(int, int, int, int);
    void FUN_00848de0(int, int, int);
    void FUN_00848e10(int, int, int, int);
    void FUN_00848e40(int, HWND);
    void FUN_00848ed0(int, int, int, int, int);
};

int  __cdecl FUN_00847f60(void* hmon, HDC hdc, RECT* rc, void* data);
int  __cdecl FUN_00847f90(unsigned char flags);

// payloads fed through CanvasEvent::mpData (opaque 32-byte blobs)
struct KeyPayload {
    unsigned mKind;        // +0x00
    unsigned mZero;        // +0x04
    unsigned mSub;         // +0x08
    int      mCode;        // +0x0c
    unsigned char mMods;   // +0x10
    unsigned char mDown;   // +0x11
    unsigned short mExtra; // +0x12
    unsigned char pad[0x0c];
};

struct MousePayload {
    unsigned mKind;        // +0x00
    unsigned mZero;        // +0x04
    unsigned mSub;         // +0x08
    int      mCode;        // +0x0c
    union { unsigned char b; int i; float f; } m10;  // +0x10
    int      m14;          // +0x14
    int      m18;          // +0x18
    union { unsigned char b; unsigned u; } m1c;      // +0x1c
};

struct SizePayload {
    unsigned mFlags;       // +0x00
    RECT     mRect;        // +0x04
};

// @ 0x00848210
char Canvas::Tick()
{
    if (mnOptionFlags & 8) {
        if (v23()) {
            int t = 200;
            EA::Thread::ThreadSleep(&t);
        } else {
            mbEnablePaint = true;
            if (mnUpdateLockCount == 0)
                InvalidateRect(mhWndParent, 0, 0);
        }
    }
    if (mnOptionFlags & 0x20) {
        MSG msg;
        while (PeekMessageW(&msg, 0, 0, 0, 1)) {
            if (msg.message == 0x12)
                return 0;
            CanvasEvent ev;
            ev.mType = 0x1ee100b;
            ev.mpSender = this;
            ev.mpData = &msg;
            SendCanvasEvent(&ev);
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    return 1;
}

// @ 0x00848340
void Canvas::OnPaint(HWND hwnd)
{
    if (!v17() && (mnOptionFlags & 4)) {
        int t = 15;
        EA::Thread::ThreadSleep(&t);
    }
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    if (mbEnablePaint) {
        if (mnUpdateLockCount != 0) {
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, mhBackgroundBrush);
            EndPaint(hwnd, &ps);
            return;
        }
        mbEnablePaint = false;
        if (((unsigned char)~(mnOptionFlags >> 6) & 1) && !mbFullscreen) {
            int r = v39();
            if (r) {
                struct { int a; HBRUSH b; } info;
                info.a = r;
                info.b = mhBackgroundBrush;
                EnumDisplayMonitors(hdc, 0, (void*)FUN_00847f60, (LPARAM)&info);
            }
        }
        CanvasEvent ev;
        ev.mType = 0x1ee100a;
        ev.mpSender = this;
        ev.mpData = 0;
        SendCanvasEvent(&ev);
    }
    EndPaint(hwnd, &ps);
}

// @ 0x00848450
void Canvas::SetClientRect()
{
    if (mbFullscreen)
        return;
    if (v24())
        return;
    if (v23())
        return;
    RECT rc;
    rc.left = mRectDesiredLeft;
    rc.top = mRectDesiredTop;
    rc.right = mRectDesiredRight;
    rc.bottom = mRectDesiredBottom;
    AdjustWindowRectEx(&rc, mWin32Style, GetMenu(mhWndParent) != 0, mWin32StyleEx);
    MoveWindow(mhWndParent, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 1);
}

// @ 0x008484f0
void Canvas::TrackClientRect()
{
    if (mbFullscreen)
        return;
    if (v24())
        return;
    if (v23())
        return;
    RECT rc;
    RECT* p = v15(&rc);
    mRectDesiredLeft = p->left;
    mRectDesiredTop = p->top;
    mRectDesiredRight = p->right;
    mRectDesiredBottom = p->bottom;
}

// @ 0x00848540
void Canvas::OnKeyDown(HWND hwnd, unsigned vk, unsigned scan, unsigned flags, unsigned extra)
{
    KeyPayload data;
    data.mKind = 4;
    data.mSub = 1;
    data.mZero = 0;
    data.mDown = 1;
    data.mCode = (int)vk;
    unsigned mods = 0;
    if (GetKeyState(0x10) & 0x8000) mods = 1;
    if (GetKeyState(0x11) & 0x8000) mods |= 2;
    if (GetKeyState(0x12) & 0x8000) mods |= 4;
    if ((GetKeyState(0x5b) & 0x8000) || (GetKeyState(0x5c) & 0x8000)) mods |= 0x10;
    data.mMods = (unsigned char)mods;
    data.mExtra = (extra & 0x4000) ? 2 : 1;
    CanvasEvent ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848620
void Canvas::OnKeyUp(HWND hwnd, unsigned vk, unsigned scan, unsigned flags, unsigned extra)
{
    KeyPayload data;
    data.mKind = 4;
    data.mSub = 1;
    data.mZero = 0;
    data.mDown = 0;
    data.mCode = (int)vk;
    unsigned mods = 0;
    if (GetKeyState(0x10) & 0x8000) mods = 1;
    if (GetKeyState(0x11) & 0x8000) mods |= 2;
    if (GetKeyState(0x12) & 0x8000) mods |= 4;
    if ((GetKeyState(0x5b) & 0x8000) || (GetKeyState(0x5c) & 0x8000)) mods |= 0x10;
    data.mMods = (unsigned char)mods;
    data.mExtra = 1;
    CanvasEvent ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x008486f0
void Canvas::OnWChar(HWND hwnd, unsigned short ch, unsigned short flags)
{
    KeyPayload data;
    data.mZero = 0;
    data.mMods = 0;
    data.mCode = ch;
    data.mExtra = flags;
    data.mKind = 4;
    data.mSub = 2;
    CanvasEvent ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848750
void Canvas::OnMouseMove(HWND hwnd, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    MousePayload data;
    data.mKind = 2;
    data.mSub = 7;
    data.mZero = 0;
    data.mCode = x;
    data.m10.i = y;
    data.m14 = x - mnLastMouseX;
    data.m18 = y - mnLastMouseY;
    data.m1c.b = (unsigned char)FUN_00847f90((unsigned char)flags);
    mnLastMouseX = x;
    mnLastMouseY = y;
    CanvasEvent ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x008487f0
void Canvas::OnMouseLeave(HWND hwnd)
{
    mbMouseInClientArea = false;
    if (mbCursorShadowSupported)
        SystemParametersInfoA(0x101b, 0, (void*)mCursorShadow, 0);
    if (mbMouseTrailsSupported)
        SystemParametersInfoA(0x5d, mMouseTrails, 0, 0);
    if (mbMouseSonarSupported)
        SystemParametersInfoA(0x101d, 0, (void*)mMouseSonar, 0);
    CanvasEvent ev;
    ev.mType = 0x1ee1002;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848870
void Canvas::OnMouseWheel(HWND hwnd, unsigned wParam, int lParam)
{
    OnMouseEnter(hwnd);
    POINT pt;
    pt.x = (short)lParam;
    pt.y = (short)((unsigned)lParam >> 16);
    ScreenToClient(hwnd, &pt);
    int lines = (int)(short)(wParam >> 16);
    unsigned delta = 1;
    SystemParametersInfoA(0x68, 0, &delta, 0);
    float f = (float)delta;
    if ((int)delta < 0)
        f += 4294967296.0f;
    float wheel = (f * (float)lines) * 0.008333334f;
    MousePayload data;
    data.mKind = 2;
    data.mSub = 6;
    data.mZero = 0;
    data.mCode = lines;
    data.m10.f = wheel;
    data.m14 = pt.x;
    data.m18 = pt.y;
    data.m1c.b = (unsigned char)FUN_00847f90((unsigned char)(wParam & 0xffff));
    CanvasEvent ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848960
void Canvas::OnMouseButtonChange(int code, unsigned char button, unsigned unused, int x, int y, unsigned flags)
{
    MousePayload data;
    data.mKind = 2;
    data.mSub = 5;
    data.mZero = 0;
    data.mCode = code;
    data.m10.b = button;
    data.m14 = x;
    data.m18 = y;
    data.m1c.b = (unsigned char)FUN_00847f90((unsigned char)flags);
    CanvasEvent ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x008489e0
void Canvas::OnLButtonDown(HWND hwnd, unsigned unused, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    SetCapture(hwnd);
    mbLButtonDown = 1;
    OnMouseButtonChange(0x3e8, 1, unused, x, y, flags);
}

// @ 0x00848a20
void Canvas::OnMButtonDown(HWND hwnd, unsigned unused, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    SetCapture(hwnd);
    mbMButtonDown = 1;
    OnMouseButtonChange(0x3e9, 1, unused, x, y, flags);
}

// @ 0x00848a60
void Canvas::OnRButtonDown(HWND hwnd, unsigned unused, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    SetCapture(hwnd);
    mbRButtonDown = 1;
    OnMouseButtonChange(0x3ea, 1, unused, x, y, flags);
}

// @ 0x00848aa0
void Canvas::OnLButtonUp(HWND hwnd, int x, int y, unsigned flags)
{
    unsigned char wasM = mbMButtonDown;
    mbLButtonDown = 0;
    if (!wasM && !mbRButtonDown)
        ReleaseCapture();
    OnMouseButtonChange(0x3e8, 0, 0, x, y, flags);
}

// @ 0x00848ae0
void Canvas::OnMButtonUp(HWND hwnd, int x, int y, unsigned flags)
{
    unsigned char wasL = mbLButtonDown;
    mbMButtonDown = 0;
    if (!wasL && !mbRButtonDown)
        ReleaseCapture();
    OnMouseButtonChange(0x3e9, 0, 0, x, y, flags);
}

// @ 0x00848b20
void Canvas::OnRButtonUp(HWND hwnd, int x, int y, unsigned flags)
{
    unsigned char wasL = mbLButtonDown;
    mbRButtonDown = 0;
    if (!wasL && !mbMButtonDown)
        ReleaseCapture();
    OnMouseButtonChange(0x3ea, 0, 0, x, y, flags);
}

// @ 0x00848b60
void Canvas::OnClose(HWND hwnd)
{
    char close = 1;
    CanvasEvent ev = { 0x1ee1009, this };
    ev.mpData = &close;
    SendCanvasEvent(&ev);
    if (close) {
        ShowWindow(hwnd, 0);
        PostQuitMessage(0);
    }
}

// @ 0x00848bb0
void Canvas::FUN_00848bb0(unsigned unused, int* out)
{
    RECT rc;
    rc.left = mRectDesiredLeft;
    rc.top = mRectDesiredTop;
    rc.right = mRectDesiredRight;
    rc.bottom = mRectDesiredBottom;
    AdjustWindowRectEx(&rc, mWin32Style, 0, mWin32StyleEx);
    out[6] = mnMinWidth - mRectDesiredRight - rc.left + rc.right + mRectDesiredLeft;
    out[7] = mRectDesiredTop - mRectDesiredBottom + mnMinHeight - rc.top + rc.bottom;
}

// @ 0x00848c20
void Canvas::OnSize(HWND hwnd, int type, int a, int b)
{
    SizePayload data;
    data.mFlags = 2;
    v15(&data.mRect);
    switch (type) {
    case 0:
        if (mbInMovingSizingLoop) {
            data.mFlags |= 0x10;
            mbInSizingLoop = true;
        }
        break;
    case 1:
        data.mFlags |= 8;
        data.mRect.left = 0;
        data.mRect.top = 0;
        data.mRect.right = 0;
        data.mRect.bottom = 0;
        break;
    case 2:
        data.mFlags |= 4;
        break;
    default:
        return;
    }
    TrackClientRect();
    CanvasEvent ev = { 0x1ee1003, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848cb0
void Canvas::OnExitSizeMove(int unused)
{
    if (!mbInMovingSizingLoop)
        return;
    unsigned flags = (mbInSizingLoop ? 2u : 0u) | (mbInMovingLoop ? 1u : 0u) | 0x20;
    mbInMovingSizingLoop = false;
    mbInSizingLoop = false;
    mbInMovingLoop = false;
    TrackClientRect();
    SizePayload data;
    data.mFlags = flags;
    RECT rc;
    data.mRect = *v15(&rc);
    CanvasEvent ev = { 0x1ee1003, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848d40
void Canvas::OnActivate(int active, int minimized)
{
    CanvasEvent ev;
    ev.mType = (minimized != 0) ? 0x1ee1010 : 0x1ee1011;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848d70
void Canvas::FUN_00848d70(int a, int b, int c, int d)
{
    CanvasEvent ev;
    ev.mType = (b != 0) ? 0x1ee100e : 0x1ee100f;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
    if (b != 0 && d != 0) {
        CanvasEvent ev2;
        ev2.mType = 0x1ee1008;
        ev2.mpSender = this;
        ev2.mpData = 0;
        SendCanvasEvent(&ev2);
    }
}

// @ 0x00848de0
void Canvas::FUN_00848de0(int a, int b, int c)
{
    CanvasEvent ev;
    ev.mType = (b != 0) ? 0x1ee1006 : 0x1ee1007;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848e10
void Canvas::FUN_00848e10(int a, int b, int c, int d)
{
    CanvasEvent ev;
    ev.mType = 0x1ee100d;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848e40
void Canvas::FUN_00848e40(int a, HWND wnd)
{
    if (wnd != mhWndParent) {
        if (mbLButtonDown) {
            int x = mnLastMouseX;
            int y = mnLastMouseY;
            mbLButtonDown = 0;
            OnMouseButtonChange(0x3e8, 0, 0, x, y, 0);
        }
        if (mbMButtonDown) {
            int x = mnLastMouseX;
            int y = mnLastMouseY;
            mbMButtonDown = 0;
            OnMouseButtonChange(0x3e9, 0, 0, x, y, 0);
        }
        if (mbRButtonDown) {
            mbRButtonDown = 0;
            OnMouseButtonChange(0x3ea, 0, 0, mnLastMouseX, mnLastMouseY, 0);
        }
    }
    if (mbInMovingSizingLoop)
        OnExitSizeMove(a);
}

// @ 0x00848ed0
void Canvas::FUN_00848ed0(int x, int y, int w, int h, int unused5)
{
    w = mRectDesiredLeft + w;
    h = mRectDesiredTop + h;
    mRectDesiredRight = w;
    mRectDesiredBottom = h;
    if (x != 0x7fffffff) {
        mRectDesiredBottom = (h - mRectDesiredTop) + y;
        mRectDesiredRight = (w - mRectDesiredLeft) + x;
        mRectDesiredLeft = x;
        mRectDesiredTop = y;
        SetClientRect();
        return;
    }
    int cw = w - mRectDesiredLeft;
    int ch = h - mRectDesiredTop;
    RECT work;
    SystemParametersInfoA(0x30, 0, &work, 0);
    RECT scr;
    scr.left = 0;
    scr.top = 0;
    scr.right = GetSystemMetrics(0);
    scr.bottom = GetSystemMetrics(1);
    RECT out;
    if (IntersectRect(&out, &work, &scr)) {
        work = out;
    }
    int l = work.left + ((work.right - work.left) - cw) / 2;
    int t = ((work.bottom - work.top) - ch) / 2 + work.top;
    mRectDesiredLeft = l;
    mRectDesiredTop = t;
    mRectDesiredRight = l + cw;
    mRectDesiredBottom = t + ch;
    SetClientRect();
}

// @ 0x00848fe0
void Canvas::SetFullscreen(char on, int w, int h)
{
    if (on) {
        if (mbFullscreen)
            return;
        mbFullscreen = true;
        SetLastError(0);
        DWORD style = (DWORD)GetWindowLongA(mhWndParent, -0x10);
        DWORD ex = (DWORD)GetWindowLongA(mhWndParent, -0x14);
        DWORD newStyle = (style & 0xff38ffff) | 0x80080000;
        DWORD newEx = ex & 0xfffffcff;
        SetWindowLongA(mhWndParent, -0x10, (LONG)newStyle);
        SetWindowLongA(mhWndParent, -0x14, (LONG)newEx);
        ShowWindow(mhWndParent, 9);
        if (w > 0 && h > 0)
            SetWindowPos(mhWndParent, (HWND)-1, 0, 0, w, h, 0x20);
        else
            SetWindowPos(mhWndParent, (HWND)-1, 0, 0, 0, 0, 0x23);
        ShowWindow(mhWndParent, 3);
    } else {
        if (!mbFullscreen)
            return;
        mbFullscreen = false;
        SetLastError(0);
        v08(-1);
        SetClientRect();
    }
}

// @ 0x008490d0
void Canvas::Show()
{
    if (mbFullscreen)
        return;
    SetLastError(0);
    DWORD style = (DWORD)GetWindowLongA(mhWndParent, -0x10);
    DWORD ex = (DWORD)GetWindowLongA(mhWndParent, -0x14);
    if (((style & 0x80cf0000) != mWin32Style) || ((ex & 0x300) != mWin32StyleEx)) {
        SetClientRect();
        DWORD newStyle = (style & 0x7f30ffff) | mWin32Style;
        DWORD newEx = (ex & 0xfffffcff) | mWin32StyleEx;
        SetLastError(0);
        SetWindowLongA(mhWndParent, -0x10, (LONG)newStyle);
        SetWindowLongA(mhWndParent, -0x14, (LONG)newEx);
        SetWindowPos(mhWndParent, (HWND)-2, 0, 0, 0, 0, 0x23);
        bool vis = IsWindowVisible(mhWndParent) != 0;
        ShowWindow(mhWndParent, vis ? 1 : 0);
    }
}
