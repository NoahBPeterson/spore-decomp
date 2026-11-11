// src/game/UTFSpore_Win32/EACanvas.cpp -- migrated from slice(s) s00848210, s00847200, s00849f70, s008491a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACanvas.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __stdcall SetWindowTextW(void* hwnd, const wchar_t* text);

// ---- items of slice s008491a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall SetWindowTextW(void* hwnd, const wchar_t* text);
void EASTL_allocator_deallocate(void* p);   // 0x00f47380
inline size_t EAStrLenW(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (size_t)(p - s);
}
struct WString {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8
    uint32_t mAllocPad;    // +c
    WString& assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
struct Canvas;
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
// ---- items of slice s008491a0 end

// ---- items of slice s00849f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HWND;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
struct POINT { long x, y; };
struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
};
extern "C" __declspec(dllimport) BOOL __stdcall PeekMessageA(tagMSG*, HWND, UINT, UINT, UINT);
extern "C" __declspec(dllimport) BOOL __stdcall PostMessageA(HWND, UINT, WPARAM, LPARAM);
// ---- items of slice s00849f70 end

// ---- items of slice s00847200 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) short __stdcall GetAsyncKeyState(int);
extern unsigned g_01650384;        // 0x01650384
extern char* g_01650388;           // 0x01650388
typedef void* HDC;
typedef void* HBRUSH;
typedef void* HGDIOBJ;
typedef void* HINSTANCE;
typedef void* HMONITOR;
typedef void* HMODULE;
typedef void* FARPROC;
typedef const char* LPCSTR;
typedef unsigned short WCHAR;
struct RECT { long left, top, right, bottom; };
struct TRACKMOUSEEVENT { DWORD cbSize; DWORD dwFlags; HWND hwndTrack; DWORD dwHoverTime; };
#define MAKELONG(a, b) ((LPARAM)(((DWORD)(a)) | (((DWORD)(b)) << 16)))
extern "C" __declspec(dllimport) BOOL __stdcall ValidateRect(HWND, const RECT*);
extern "C" __declspec(dllimport) BOOL __stdcall InvalidateRect(HWND, const RECT*, BOOL);
extern "C" __declspec(dllimport) BOOL __stdcall UpdateWindow(HWND);
extern "C" __declspec(dllimport) HDC __stdcall GetDC(HWND);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(HWND, HDC);
extern "C" __declspec(dllimport) BOOL __stdcall GetClientRect(HWND, RECT*);
extern "C" __declspec(dllimport) int __stdcall FillRect(HDC, const RECT*, HBRUSH);
extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow(void);
extern "C" __declspec(dllimport) HWND __stdcall SetActiveWindow(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall IsWindowVisible(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND, int);
extern "C" __declspec(dllimport) HWND __stdcall GetAncestor(HWND, UINT);
extern "C" __declspec(dllimport) BOOL __stdcall IsIconic(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall IsZoomed(HWND);
extern "C" __declspec(dllimport) HMONITOR __stdcall MonitorFromWindow(HWND, DWORD);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(LPCSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
extern "C" __declspec(dllimport) BOOL __stdcall SystemParametersInfoA(UINT, UINT, void*, UINT);
extern "C" __declspec(dllimport) BOOL __stdcall ShowCursor(BOOL);
extern "C" __declspec(dllimport) BOOL __stdcall KillTimer(HWND, UINT);
extern "C" __declspec(dllimport) BOOL __stdcall DestroyWindow(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall UnregisterClassA(LPCSTR, HINSTANCE);
extern "C" __declspec(dllimport) BOOL __stdcall DeleteObject(HGDIOBJ);
extern "C" __declspec(dllimport) BOOL __stdcall GetWindowRect(HWND, RECT*);
extern "C" __declspec(dllimport) BOOL __stdcall ClientToScreen(HWND, POINT*);
extern "C" __declspec(dllimport) DWORD __stdcall SetThreadExecutionState(DWORD);
extern "C" __declspec(dllimport) int __stdcall GetLocaleInfoW(DWORD, DWORD, WCHAR*, int);
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const WCHAR*, WCHAR**, int);
extern FARPROC g_01650380;         // 0x01650380
struct Canvas_s0084_7200;
struct CanvasEvent_s0084_7200 {
    unsigned mType;      // +0x00
    Canvas_s0084_7200*  mpSender;   // +0x04
    void*    mpData;     // +0x08
};
struct Canvas_s0084_7200 {
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
    virtual void v15(RECT* out);                                    // +0x3c
    virtual void v16(int left, int top, unsigned w, unsigned h, int flag);   // +0x40

    int      mStyle;              // +0x04
    unsigned mnOptionFlags;       // +0x08
    unsigned char b0c;            // +0x0c
    unsigned char pad0d[4];       // +0x0d
    unsigned char mbMouseInClientArea;  // +0x11
    unsigned char pad12[10];      // +0x12
    unsigned char mbEnablePaint;  // +0x1c
    unsigned char pad1d[3];       // +0x1d
    unsigned mnUpdateLockCount;   // +0x20
    unsigned char pad24[0x10];    // +0x24
    unsigned mnMinWidth;          // +0x34
    unsigned mnMinHeight;         // +0x38
    int      mRectDesiredLeft;    // +0x3c
    int      mRectDesiredTop;     // +0x40
    unsigned char pad44[8];       // +0x44
    unsigned char mbCursorVisible;         // +0x4c
    unsigned char mbCursorShadowSupported; // +0x4d
    unsigned char mbMouseTrailsSupported;  // +0x4e
    unsigned char mbMouseSonarSupported;   // +0x4f
    unsigned char pad50[4];       // +0x50
    unsigned mnSystemLCID;        // +0x54
    unsigned mnSystemCodePage;    // +0x58
    void*    mpMessageServer;     // +0x5c
    void*    mpInputMan;          // +0x60
    void (*mpCanvasEventCallback)(CanvasEvent_s0084_7200*, void*);   // +0x64
    void*    mpCanvasEventCallbackContext;                // +0x68
    unsigned char pad6c[4];       // +0x6c
    unsigned short mClassAtom;    // +0x70
    unsigned short pad72;         // +0x72
    HWND     mhWndParent;         // +0x74
    unsigned char pad78[8];       // +0x78
    HBRUSH   mhBackgroundBrush;   // +0x80
    unsigned char pad84[8];       // +0x84
    int      mCursorShadow;       // +0x8c
    int      mMouseTrails;        // +0x90
    int      mMouseSonar;         // +0x94

    void LockUpdate(bool bLock);  // 0x00847970 (Canvas::LockUpdate)
    void Update();  // 0x008479c0 (Canvas::Update)
    void Clear();  // 0x008479f0 (Canvas::Clear)
    void SetOptions(unsigned opts);  // 0x00847a40 (Canvas::SetOptions)
    bool IsActive();  // 0x00847a70 (Canvas::IsActive)
    void SetActive(bool bActive);  // 0x00847a90 (Canvas::SetActive)
    bool GetVisible();  // 0x00847ab0 (Canvas::GetVisible)
    void SetVisible(bool bVisible);  // 0x00847ad0 (Canvas::SetVisible)
    bool IsMinimized();  // 0x00847af0 (Canvas::IsMinimized)
    bool IsMaximized();  // 0x00847b10 (Canvas::IsMaximized)
    unsigned short GetClassAtom();
    HMONITOR GetActiveMonitor();  // 0x00847b50 (Canvas::GetActiveMonitor)
    int  OnEraseBackground(HWND hwnd, HDC hdc);
    void OnMouseEnter(HWND hwnd);  // 0x00847bb0 (Canvas::OnMouseEnter)
    void FUN_00847c70(int, int);
    void OnSizing(HWND hwnd, int edge, RECT* rc);
    void FUN_00847da0(int, unsigned flag, int);
    void FUN_00847e20(unsigned short lcid);
    void SendCanvasEvent(CanvasEvent_s0084_7200* ev);  // 0x00847e70 (Canvas::SendCanvasEvent)
    void SetSystemCursorVisible(bool bVisible);  // 0x00847ef0 (Canvas::SetSystemCursorVisible)
    void SetSystemCursorPosition(unsigned short x, unsigned short y);  // 0x00847f10 (Canvas::SetSystemCursorPosition)
    void SetSystemCursorShape(LPARAM shape);  // 0x00847f40 (Canvas::SetSystemCursorShape)
    bool Shutdown();  // 0x00848020 (Canvas::Shutdown)
    void GetMinClientArea(unsigned* out);  // 0x00848100 (Canvas::GetMinClientArea)
    void SetMinClientArea(unsigned w, unsigned h);  // 0x00848120 (Canvas::SetMinClientArea)
    void GetClientArea(long* out);  // 0x00848190 (Canvas::GetClientArea)
};
// ---- items of slice s00847200 end

// ---- items of slice s00848210 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) short __stdcall GetKeyState(int);
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int);
extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int);
typedef void* HMENU;
typedef long LONG;
struct MSG {
    HWND   hwnd;
    UINT   message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD  time;
    POINT  pt;
};
extern "C" __declspec(dllimport) BOOL __stdcall PeekMessageW(MSG*, HWND, UINT, UINT, UINT);
extern "C" __declspec(dllimport) BOOL __stdcall TranslateMessage(const MSG*);
extern "C" __declspec(dllimport) LPARAM __stdcall DispatchMessageW(const MSG*);
extern "C" __declspec(dllimport) BOOL __stdcall ScreenToClient(HWND, POINT*);
extern "C" __declspec(dllimport) HWND __stdcall SetCapture(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall ReleaseCapture(void);
extern "C" __declspec(dllimport) BOOL __stdcall IntersectRect(RECT*, const RECT*, const RECT*);
extern "C" __declspec(dllimport) HMENU __stdcall GetMenu(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall AdjustWindowRectEx(RECT*, DWORD, BOOL, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall MoveWindow(HWND, int, int, int, int, BOOL);
extern "C" __declspec(dllimport) LONG __stdcall GetWindowLongA(HWND, int);
extern "C" __declspec(dllimport) LONG __stdcall SetWindowLongA(HWND, int, LONG);
extern "C" __declspec(dllimport) BOOL __stdcall SetWindowPos(HWND, HWND, int, int, int, int, UINT);
extern "C" __declspec(dllimport) void __stdcall SetLastError(DWORD);
namespace EA {
namespace Thread {
void ThreadSleep(const int* milliseconds);
}
}
struct Canvas_s0084_8210;
struct CanvasEvent_s0084_8210 {
    unsigned mType;      // +0x00
    Canvas_s0084_8210*  mpSender;   // +0x04
    void*    mpData;     // +0x08
};
struct Canvas_s0084_8210 {
virtual void  v00();
virtual void  v01();
virtual void  v02();
virtual void  v03();
virtual void  v04();
virtual void  v05();
virtual void  v06();
virtual void  v07();
virtual void  v08(int);
virtual void v09();
virtual void v10();
virtual void v11();
virtual void  v12();
virtual void  v13();
virtual void  v14();
    virtual RECT* v15(RECT* out);                                          // +0x3c
    virtual void  v16(int, int, unsigned, unsigned, int);                  // +0x40
    virtual bool  v17();                                                   // +0x44
virtual void  v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual void  v22();
    virtual bool  v23();                                                   // +0x5c
    virtual bool  v24();                                                   // +0x60
virtual void  v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void  v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void  v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void  v37();
virtual void v38();
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
    void (*mpCanvasEventCallback)(CanvasEvent_s0084_8210*, void*);   // +0x64
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

    char Tick();  // 0x00848210 (Canvas::Tick)
    void OnPaint(HWND hwnd);  // 0x00848340 (Canvas::OnPaint)
    void SetClientRect();  // 0x00848450 (Canvas::SetClientRect)
    void TrackClientRect();  // 0x008484f0 (Canvas::TrackClientRect)
    void OnKeyDown(HWND, unsigned, unsigned, unsigned, unsigned);  // 0x00848540 (Canvas::OnKeyDown)
    void OnKeyUp(HWND, unsigned, unsigned, unsigned, unsigned);  // 0x00848620 (Canvas::OnKeyUp)
    void OnWChar(HWND, unsigned short, unsigned short);  // 0x008486f0 (Canvas::OnWChar)
    void OnMouseMove(HWND, int, int, unsigned);  // 0x00848750 (Canvas::OnMouseMove)
    void OnMouseLeave(HWND);  // 0x008487f0 (Canvas::OnMouseLeave)
    void OnMouseWheel(HWND, unsigned, int);  // 0x00848870 (Canvas::OnMouseWheel)
    void OnMouseButtonChange(int, unsigned char, unsigned, int, int, unsigned);  // 0x00848960 (Canvas::OnMouseButtonChange)
    void OnLButtonDown(HWND, unsigned, int, int, unsigned);  // 0x008489e0 (Canvas::OnLButtonDown)
    void OnMButtonDown(HWND, unsigned, int, int, unsigned);  // 0x00848a20 (Canvas::OnMButtonDown)
    void OnRButtonDown(HWND, unsigned, int, int, unsigned);  // 0x00848a60 (Canvas::OnRButtonDown)
    void OnLButtonUp(HWND, int, int, unsigned);  // 0x00848aa0 (Canvas::OnLButtonUp)
    void OnMButtonUp(HWND, int, int, unsigned);  // 0x00848ae0 (Canvas::OnMButtonUp)
    void OnRButtonUp(HWND, int, int, unsigned);  // 0x00848b20 (Canvas::OnRButtonUp)
    void OnClose(HWND);  // 0x00848b60 (Canvas::OnClose)
    void OnSize(HWND, int, int, int);  // 0x00848c20 (Canvas::OnSize)
    void OnExitSizeMove(int);  // 0x00848cb0 (Canvas::OnExitSizeMove)
    void OnActivate(int, int);  // 0x00848d40 (Canvas::OnActivate)
    void SetFullscreen(char, int, int);  // 0x00848fe0 (Canvas::SetFullscreen)
    void Show();  // 0x008490d0 (Canvas::Show)
    void SendCanvasEvent(CanvasEvent_s0084_8210*);  // 0x00847e70 (Canvas::SendCanvasEvent)
    void OnMouseEnter(HWND);  // 0x00847bb0 (Canvas::OnMouseEnter)
    void FUN_00848bb0(unsigned, int*);
    void FUN_00848d70(int, int, int, int);
    void FUN_00848de0(int, int, int);
    void FUN_00848e10(int, int, int, int);
    void FUN_00848e40(int, HWND);
    void FUN_00848ed0(int, int, int, int, int);
};
int  __cdecl FUN_00847f90(unsigned char flags);
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
// ---- items of slice s00848210 end

// @ 0x00847970
void Canvas_s0084_7200::LockUpdate(bool bLock)
{
    if (bLock) {
        if (mnUpdateLockCount == 0 && mbEnablePaint)
            ValidateRect(mhWndParent, 0);
        ++mnUpdateLockCount;
        return;
    }
    if (mnUpdateLockCount > 0) {
        unsigned n = mnUpdateLockCount - 1;
        mnUpdateLockCount = n;
        if (n == 0) {
            mbEnablePaint = true;
            InvalidateRect(mhWndParent, 0, 0);
        }
    }
}

// @ 0x008479c0
void Canvas_s0084_7200::Update()
{
    mbEnablePaint = true;
    if (mnUpdateLockCount == 0) {
        InvalidateRect(mhWndParent, 0, 0);
        UpdateWindow(mhWndParent);
    }
}

// @ 0x008479f0
void Canvas_s0084_7200::Clear()
{
    HDC hdc = GetDC(mhWndParent);
    if (hdc) {
        RECT rc;
        GetClientRect(mhWndParent, &rc);
        FillRect(hdc, &rc, mhBackgroundBrush);
        ReleaseDC(mhWndParent, hdc);
    }
}

// @ 0x00847a40
void Canvas_s0084_7200::SetOptions(unsigned opts)
{
    mnOptionFlags = opts;
    if (opts & 2)
        SetThreadExecutionState(0x80000000);
    else
        SetThreadExecutionState(0x80000003);
}

// @ 0x00847a70
bool Canvas_s0084_7200::IsActive()
{
    return GetActiveWindow() == mhWndParent;
}

// @ 0x00847a90
void Canvas_s0084_7200::SetActive(bool bActive)
{
    SetActiveWindow(bActive ? mhWndParent : 0);
}

// @ 0x00847ab0
bool Canvas_s0084_7200::GetVisible()
{
    return IsWindowVisible(mhWndParent) != 0;
}

// @ 0x00847ad0
void Canvas_s0084_7200::SetVisible(bool bVisible)
{
    ShowWindow(mhWndParent, bVisible ? 1 : 0);
}

// @ 0x00847af0
bool Canvas_s0084_7200::IsMinimized()
{
    return IsIconic(GetAncestor(mhWndParent, 3)) != 0;
}

// @ 0x00847b10
bool Canvas_s0084_7200::IsMaximized()
{
    return IsZoomed(GetAncestor(mhWndParent, 3)) != 0;
}

// @ 0x00847b40
unsigned short Canvas_s0084_7200::GetClassAtom()
{
    return mClassAtom;
}

// @ 0x00847b50
HMONITOR Canvas_s0084_7200::GetActiveMonitor()
{
    return MonitorFromWindow(mhWndParent, 0);
}

// @ 0x00847b60
int Canvas_s0084_7200::OnEraseBackground(HWND hwnd, HDC hdc)
{
    if (!mbEnablePaint && !b0c) {
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, mhBackgroundBrush);
    }
    return 1;
}

// @ 0x00847bb0
void Canvas_s0084_7200::OnMouseEnter(HWND hwnd)
{
    if (mbMouseInClientArea)
        return;
    if (!(g_01650384 & 1)) {
        g_01650384 |= 1;
        g_01650380 = GetProcAddress(GetModuleHandleA("user32.dll"), "TrackMouseEvent");
    }
    FARPROC proc = g_01650380;
    if (!proc)
        return;
    TRACKMOUSEEVENT tme;
    tme.cbSize = 0;
    tme.dwFlags = 0;
    tme.hwndTrack = 0;
    tme.dwHoverTime = 0;
    mbMouseInClientArea = true;
    tme.cbSize = 0x10;
    tme.dwFlags = 2;
    tme.hwndTrack = hwnd;
    ((BOOL(__stdcall*)(TRACKMOUSEEVENT*))proc)(&tme);
    if (mbCursorShadowSupported) SystemParametersInfoA(0x101b, 0, 0, 0);
    if (mbMouseTrailsSupported)  SystemParametersInfoA(0x5d, 0, 0, 0);
    if (mbMouseSonarSupported)   SystemParametersInfoA(0x101d, 0, 0, 0);
}

// @ 0x00847c70
void Canvas_s0084_7200::FUN_00847c70(int, int)
{
    if (!(mnOptionFlags & 2)) {
        UINT n = 0;
        SystemParametersInfoA(0xe, 0, &n, 0);
        if ((int)n <= 0x3c) {
            n = 0x3c;
        }
        SystemParametersInfoA(0xf, n, 0, 0);
    }
}

// @ 0x00847cc0
void Canvas_s0084_7200::OnSizing(HWND hwnd, int edge, RECT* rc)
{
    if (!(mnOptionFlags & 1))
        return;
    RECT wr;
    GetWindowRect(hwnd, &wr);
    int dl = rc->left - wr.left;
    int dt = rc->top - wr.top;
    int dr = rc->right - wr.right;
    int db = rc->bottom - wr.bottom;
    switch (edge) {
    case 1:
        rc->top = wr.top + dl;
        break;
    case 2:
        rc->bottom = wr.bottom + dr;
        break;
    case 3:
        rc->left = dt + wr.left;
        break;
    case 4:
        rc->right = wr.right - dt;
        break;
    case 5:
        rc->right = wr.right + db;
        break;
    case 6:
        rc->left = wr.left - db;
        break;
    case 7:
    case 8:
        rc->right = wr.right + db;
        break;
    }
}

// @ 0x00847da0
void Canvas_s0084_7200::FUN_00847da0(int, unsigned flag, int)
{
    switch (flag) {
    case 0x5d:
        mbMouseTrailsSupported = SystemParametersInfoA(0x5e, 0, &mMouseTrails, 0) != 0;
        break;
    case 0x101b:
        mbCursorShadowSupported = SystemParametersInfoA(0x101a, 0, &mCursorShadow, 0) != 0;
        break;
    case 0x101d:
        mbMouseSonarSupported = SystemParametersInfoA(0x101c, 0, &mMouseSonar, 0) != 0;
        break;
    }
}

// @ 0x00847e20
void Canvas_s0084_7200::FUN_00847e20(unsigned short lcid)
{
    mnSystemLCID = lcid;
    WCHAR buf[128];
    GetLocaleInfoW(lcid, 0x1004, buf, 0x80);
    mnSystemCodePage = wcstoul(buf, 0, 10);
}

// @ 0x00847e70
void Canvas_s0084_7200::SendCanvasEvent(CanvasEvent_s0084_7200* ev)
{
    if (ev->mType == 0x1ee1001 && mpInputMan) {
        ((void(__thiscall*)(void*, void*))*(void**)(*(int*)mpInputMan + 0x30))(mpInputMan, ev->mpData);
        return;
    }
    if (mpMessageServer) {
        ((void(__thiscall*)(void*, unsigned, void*, int))*(void**)(*(int*)mpMessageServer + 0x14))(mpMessageServer, ev->mType, ev, 0);
        return;
    }
    if (mpCanvasEventCallback)
        mpCanvasEventCallback(ev, mpCanvasEventCallbackContext);
}

// @ 0x00847ef0
void Canvas_s0084_7200::SetSystemCursorVisible(bool bVisible)
{
    if (mbCursorVisible != bVisible) {
        mbCursorVisible = bVisible;
        ShowCursor(bVisible);
    }
}

// @ 0x00847f10
void Canvas_s0084_7200::SetSystemCursorPosition(unsigned short x, unsigned short y)
{
    PostMessageA(mhWndParent, 0x501, 0, MAKELONG(x, y));
}

// @ 0x00847f40
void Canvas_s0084_7200::SetSystemCursorShape(LPARAM shape)
{
    PostMessageA(mhWndParent, 0x500, 0, shape);
}

// @ 0x00847f60
int __stdcall FUN_00847f60(int a, HDC hdc, RECT* rc, int* p)
{
    if (a != p[0])
        FillRect(hdc, rc, (HBRUSH)p[1]);
    return 1;
}

// @ 0x00847f90
int __cdecl FUN_00847f90(unsigned char flags)
{
    int r = 0;
    if (flags & 4)
        r = 1;
    if (flags & 8)
        r |= 2;
    if (GetAsyncKeyState(0x12) & 0x8000)
        r |= 4;
    if ((GetAsyncKeyState(0x5b) & 0x8000) || (GetAsyncKeyState(0x5c) & 0x8000))
        r |= 0x10;
    return r;
}

// @ 0x00848020
bool Canvas_s0084_7200::Shutdown()
{
    if (mhWndParent) {
        CanvasEvent_s0084_7200 ev;
        ev.mType = 0x1ee1005;
        ev.mpSender = this;
        ev.mpData = 0;
        SendCanvasEvent(&ev);
        if (mhWndParent) {
            KillTimer(mhWndParent, 0);
            *(int*)(g_01650388 + 0x10) = 0;
            DestroyWindow(mhWndParent);
            mhWndParent = 0;
        }
        if (mClassAtom) {
            UnregisterClassA((LPCSTR)(unsigned)mClassAtom, GetModuleHandleA(0));
            mClassAtom = 0;
        }
        if (mhBackgroundBrush) {
            DeleteObject(mhBackgroundBrush);
            mhBackgroundBrush = 0;
        }
        if (mbCursorShadowSupported) SystemParametersInfoA(0x101b, 0, (void*)mCursorShadow, 0);
        if (mbMouseTrailsSupported)  SystemParametersInfoA(0x5d, mMouseTrails, 0, 0);
        if (mbMouseSonarSupported)   SystemParametersInfoA(0x101d, 0, (void*)mMouseSonar, 0);
    }
    return true;
}

// @ 0x00848100
void Canvas_s0084_7200::GetMinClientArea(unsigned* __restrict out)
{
    out[0] = mnMinWidth;
    out[1] = mnMinHeight;
}

// @ 0x00848120
void Canvas_s0084_7200::SetMinClientArea(unsigned w, unsigned h)
{
    mnMinWidth = w;
    mnMinHeight = h;
    RECT rc;
    v15(&rc);
    int rw = (int)(rc.right - rc.left);
    int rh = (int)(rc.bottom - rc.top);
    if (rw < (int)w || rh < (int)h) {
        if (rh <= (int)h) rh = (int)h;
        if (rw <= (int)w) rw = (int)w;
        v16(mRectDesiredLeft, mRectDesiredTop, (unsigned)rw, (unsigned)rh, 0);
    }
}

// @ 0x00848190
void Canvas_s0084_7200::GetClientArea(long* out)
{
    RECT rc;
    GetClientRect(mhWndParent, &rc);
    POINT tl;
    tl.x = rc.left;
    tl.y = rc.top;
    ClientToScreen(mhWndParent, &tl);
    POINT br;
    br.x = rc.right;
    br.y = rc.bottom;
    ClientToScreen(mhWndParent, &br);
    out[0] = tl.x;
    out[1] = tl.y;
    out[2] = br.x;
    out[3] = br.y;
}

// @ 0x00848210
char Canvas_s0084_8210::Tick()
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
            CanvasEvent_s0084_8210 ev;
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

// @ 0x00848450
void Canvas_s0084_8210::SetClientRect()
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
void Canvas_s0084_8210::TrackClientRect()
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
void Canvas_s0084_8210::OnKeyDown(HWND hwnd, unsigned vk, unsigned scan, unsigned flags, unsigned extra)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848620
void Canvas_s0084_8210::OnKeyUp(HWND hwnd, unsigned vk, unsigned scan, unsigned flags, unsigned extra)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x008486f0
void Canvas_s0084_8210::OnWChar(HWND hwnd, unsigned short ch, unsigned short flags)
{
    KeyPayload data;
    data.mZero = 0;
    data.mMods = 0;
    data.mCode = ch;
    data.mExtra = flags;
    data.mKind = 4;
    data.mSub = 2;
    CanvasEvent_s0084_8210 ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848750
void Canvas_s0084_8210::OnMouseMove(HWND hwnd, int x, int y, unsigned flags)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x008487f0
void Canvas_s0084_8210::OnMouseLeave(HWND hwnd)
{
    mbMouseInClientArea = false;
    if (mbCursorShadowSupported)
        SystemParametersInfoA(0x101b, 0, (void*)mCursorShadow, 0);
    if (mbMouseTrailsSupported)
        SystemParametersInfoA(0x5d, mMouseTrails, 0, 0);
    if (mbMouseSonarSupported)
        SystemParametersInfoA(0x101d, 0, (void*)mMouseSonar, 0);
    CanvasEvent_s0084_8210 ev;
    ev.mType = 0x1ee1002;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848870
void Canvas_s0084_8210::OnMouseWheel(HWND hwnd, unsigned wParam, int lParam)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848960
void Canvas_s0084_8210::OnMouseButtonChange(int code, unsigned char button, unsigned unused, int x, int y, unsigned flags)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1001, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x008489e0
void Canvas_s0084_8210::OnLButtonDown(HWND hwnd, unsigned unused, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    SetCapture(hwnd);
    mbLButtonDown = 1;
    OnMouseButtonChange(0x3e8, 1, unused, x, y, flags);
}

// @ 0x00848a20
void Canvas_s0084_8210::OnMButtonDown(HWND hwnd, unsigned unused, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    SetCapture(hwnd);
    mbMButtonDown = 1;
    OnMouseButtonChange(0x3e9, 1, unused, x, y, flags);
}

// @ 0x00848a60
void Canvas_s0084_8210::OnRButtonDown(HWND hwnd, unsigned unused, int x, int y, unsigned flags)
{
    OnMouseEnter(hwnd);
    SetCapture(hwnd);
    mbRButtonDown = 1;
    OnMouseButtonChange(0x3ea, 1, unused, x, y, flags);
}

// @ 0x00848aa0
void Canvas_s0084_8210::OnLButtonUp(HWND hwnd, int x, int y, unsigned flags)
{
    unsigned char wasM = mbMButtonDown;
    mbLButtonDown = 0;
    if (!wasM && !mbRButtonDown)
        ReleaseCapture();
    OnMouseButtonChange(0x3e8, 0, 0, x, y, flags);
}

// @ 0x00848ae0
void Canvas_s0084_8210::OnMButtonUp(HWND hwnd, int x, int y, unsigned flags)
{
    unsigned char wasL = mbLButtonDown;
    mbMButtonDown = 0;
    if (!wasL && !mbRButtonDown)
        ReleaseCapture();
    OnMouseButtonChange(0x3e9, 0, 0, x, y, flags);
}

// @ 0x00848b20
void Canvas_s0084_8210::OnRButtonUp(HWND hwnd, int x, int y, unsigned flags)
{
    unsigned char wasL = mbLButtonDown;
    mbRButtonDown = 0;
    if (!wasL && !mbMButtonDown)
        ReleaseCapture();
    OnMouseButtonChange(0x3ea, 0, 0, x, y, flags);
}

// @ 0x00848b60
void Canvas_s0084_8210::OnClose(HWND hwnd)
{
    char close = 1;
    CanvasEvent_s0084_8210 ev = { 0x1ee1009, this };
    ev.mpData = &close;
    SendCanvasEvent(&ev);
    if (close) {
        ShowWindow(hwnd, 0);
        PostQuitMessage(0);
    }
}

// @ 0x00848bb0
void Canvas_s0084_8210::FUN_00848bb0(unsigned unused, int* out)
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
void Canvas_s0084_8210::OnSize(HWND hwnd, int type, int a, int b)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1003, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848cb0
void Canvas_s0084_8210::OnExitSizeMove(int unused)
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
    CanvasEvent_s0084_8210 ev = { 0x1ee1003, this };
    ev.mpData = &data;
    SendCanvasEvent(&ev);
}

// @ 0x00848d40
void Canvas_s0084_8210::OnActivate(int active, int minimized)
{
    CanvasEvent_s0084_8210 ev;
    ev.mType = (minimized != 0) ? 0x1ee1010 : 0x1ee1011;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848d70
void Canvas_s0084_8210::FUN_00848d70(int a, int b, int c, int d)
{
    CanvasEvent_s0084_8210 ev;
    ev.mType = (b != 0) ? 0x1ee100e : 0x1ee100f;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
    if (b != 0 && d != 0) {
        CanvasEvent_s0084_8210 ev2;
        ev2.mType = 0x1ee1008;
        ev2.mpSender = this;
        ev2.mpData = 0;
        SendCanvasEvent(&ev2);
    }
}

// @ 0x00848de0
void Canvas_s0084_8210::FUN_00848de0(int a, int b, int c)
{
    CanvasEvent_s0084_8210 ev;
    ev.mType = (b != 0) ? 0x1ee1006 : 0x1ee1007;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848e10
void Canvas_s0084_8210::FUN_00848e10(int a, int b, int c, int d)
{
    CanvasEvent_s0084_8210 ev;
    ev.mType = 0x1ee100d;
    ev.mpSender = this;
    ev.mpData = 0;
    SendCanvasEvent(&ev);
}

// @ 0x00848e40
void Canvas_s0084_8210::FUN_00848e40(int a, HWND wnd)
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
void Canvas_s0084_8210::FUN_00848ed0(int x, int y, int w, int h, int unused5)
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
void Canvas_s0084_8210::SetFullscreen(char on, int w, int h)
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
void Canvas_s0084_8210::Show()
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

// @ 0x00849230
void __cdecl FUN_00849230()
{}

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

// @ 0x00849b10
void __cdecl FUN_00849b10()
{}

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
void __cdecl FUN_00849e30()
{}

// @ 0x00849f70
int Canvas_FlushInput()
{
    // Drain WM_KEY* messages (up to 0x400) and repost the survivors.
    tagMSG msg;
    int count = 0;
    while (count < 0x400 && PeekMessageA(&msg, 0, 0x100, 0x109, 1)) {
        ++count;
        PostMessageA(msg.hwnd, msg.message, msg.wParam, msg.lParam);
    }
    return 0;
}
