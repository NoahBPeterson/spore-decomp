// Slice s00847200: EA::ArgScript::cParser ctor/dtor + EA::App::Canvas window message
// handlers.  Two object files: the cParser half is UTFSpore_Win32/Parser.obj
// (/O2 /MD /Gy /EHsc /TP /GS-), the Canvas half is UTFSpore_Win32/EACanvas.obj.
#include "types.h"

// ---------------------------------------------------------------------------
// Win32
// ---------------------------------------------------------------------------
typedef void* HWND;
typedef void* HDC;
typedef void* HBRUSH;
typedef void* HGDIOBJ;
typedef void* HICON;
typedef void* HINSTANCE;
typedef void* HMONITOR;
typedef void* HMODULE;
typedef void* FARPROC;
typedef const char* LPCSTR;
typedef unsigned short WCHAR;
typedef int BOOL;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef unsigned long DWORD;

struct RECT { long left, top, right, bottom; };
struct POINT { long x, y; };
struct WNDCLASSEXA {
    UINT   cbSize;
    UINT   style;
    void*  lpfnWndProc;
    int    cbClsExtra;
    int    cbWndExtra;
    HINSTANCE hInstance;
    HICON  hIcon;
    void*  hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
    HICON  hIconSm;
};
struct TRACKMOUSEEVENT { DWORD cbSize; DWORD dwFlags; HWND hwndTrack; DWORD dwHoverTime; };

#define MAKELONG(a, b) ((LPARAM)(((DWORD)(a)) | (((DWORD)(b)) << 16)))

extern "C" {
__declspec(dllimport) HICON __stdcall LoadIconA(HINSTANCE, LPCSTR);
__declspec(dllimport) BOOL __stdcall ValidateRect(HWND, const RECT*);
__declspec(dllimport) BOOL __stdcall InvalidateRect(HWND, const RECT*, BOOL);
__declspec(dllimport) BOOL __stdcall UpdateWindow(HWND);
__declspec(dllimport) HDC __stdcall GetDC(HWND);
__declspec(dllimport) int __stdcall ReleaseDC(HWND, HDC);
__declspec(dllimport) BOOL __stdcall GetClientRect(HWND, RECT*);
__declspec(dllimport) int __stdcall FillRect(HDC, const RECT*, HBRUSH);
__declspec(dllimport) HWND __stdcall GetActiveWindow(void);
__declspec(dllimport) HWND __stdcall SetActiveWindow(HWND);
__declspec(dllimport) BOOL __stdcall IsWindowVisible(HWND);
__declspec(dllimport) BOOL __stdcall ShowWindow(HWND, int);
__declspec(dllimport) HWND __stdcall GetAncestor(HWND, UINT);
__declspec(dllimport) BOOL __stdcall IsIconic(HWND);
__declspec(dllimport) BOOL __stdcall IsZoomed(HWND);
__declspec(dllimport) HMONITOR __stdcall MonitorFromWindow(HWND, DWORD);
__declspec(dllimport) HMODULE __stdcall GetModuleHandleA(LPCSTR);
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
__declspec(dllimport) BOOL __stdcall SystemParametersInfoA(UINT, UINT, void*, UINT);
__declspec(dllimport) BOOL __stdcall ShowCursor(BOOL);
__declspec(dllimport) BOOL __stdcall PostMessageA(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) short __stdcall GetAsyncKeyState(int);
__declspec(dllimport) BOOL __stdcall KillTimer(HWND, UINT);
__declspec(dllimport) BOOL __stdcall DestroyWindow(HWND);
__declspec(dllimport) BOOL __stdcall UnregisterClassA(LPCSTR, HINSTANCE);
__declspec(dllimport) BOOL __stdcall DeleteObject(HGDIOBJ);
__declspec(dllimport) BOOL __stdcall GetWindowRect(HWND, RECT*);
__declspec(dllimport) BOOL __stdcall ClientToScreen(HWND, POINT*);
__declspec(dllimport) DWORD __stdcall SetThreadExecutionState(DWORD);
__declspec(dllimport) int __stdcall GetLocaleInfoW(DWORD, DWORD, WCHAR*, int);
__declspec(dllimport) unsigned long __cdecl wcstoul(const WCHAR*, WCHAR**, int);
}

// globals used by the TrackMouseEvent lazy binding
extern FARPROC g_01650380;         // 0x01650380
extern unsigned g_01650384;        // 0x01650384
extern char* g_01650388;           // 0x01650388

void* EAAllocate(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void operator delete(void* p);                                                   // 0x00f47380

// ---------------------------------------------------------------------------
// eastl (retail layout)
// ---------------------------------------------------------------------------
extern char gEmptyStr[4];          // 0x01667bac: shared empty string storage
extern void* gEmptyBucketArray[1]; // 0x0154df28

namespace eastl {
struct allocator { unsigned char pad[4]; };

struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    string8() { mpBegin = gEmptyStr; mpEnd = gEmptyStr; mpCapacity = gEmptyStr + 1; }
    ~string8() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete(mpBegin); }
};

struct Hashtable {
    unsigned   mUninit0;       // +0x00
    void**     mpBucketArray;  // +0x04
    unsigned   mnBucketCount;  // +0x08
    unsigned   mnElementCount; // +0x0c
    float      mfMaxLoad;      // +0x10
    float      mfGrowth;       // +0x14
    unsigned   mnNextResize;   // +0x18
    unsigned   mUninit1c;      // +0x1c

    Hashtable()
    {
        mfMaxLoad = 1.0f;
        mfGrowth = 2.0f;
        mnBucketCount = 1;
        mpBucketArray = gEmptyBucketArray;
        mnElementCount = 0;
        mnNextResize = 0;
    }
    ~Hashtable()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1) operator delete(mpBucketArray);
    }
    void DoFreeNodes(void** pBucketArray, unsigned nBucketCount);
};

template <typename T>
struct vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;
    unsigned mExtra;
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vec() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin); }
};
}  // namespace eastl

using eastl::string8;
using eastl::Hashtable;
using eastl::vec;

namespace EA { namespace ArgScript {

struct cArguments { unsigned char pad[0x44]; cArguments(); ~cArguments(); };

struct cExpression { Hashtable mFunctions; cExpression(); ~cExpression() {} };

struct IStream { virtual void v0(); virtual void v1(); virtual void Release(); };

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    void Release() {
        T* p = mpObject;
        if (p) p->Release();
    }
    ~AutoRefCount() { Release(); }
};

struct cIGlobalVariableSet { virtual void v0(); virtual void Release(); };

struct cMetaEntry { void* mCommand; int mLine; };

// cParser (retail layout, 0x1b8 bytes)
struct cParser {
    void**   mvftable;          // +0x000
    unsigned mStateID;          // +0x004
    int      mRefCount;         // +0x008
    bool     mInitialized;      // +0x00c
    unsigned mFlags;            // +0x010
    AutoRefCount<IStream> mOutStream;    // +0x014
    AutoRefCount<IStream> mTraceStream;  // +0x018
    int      mMinVersion;       // +0x01c
    int      mMaxVersion;       // +0x020
    int      mScriptVersion;    // +0x024
    int      mUnknown28;        // +0x028
    Hashtable mCommands;        // +0x02c
    cExpression mExpression;    // +0x04c
    Hashtable mMacroDefinitions; // +0x06c
    Hashtable mVariables;       // +0x08c
    Hashtable mGlobalVariables; // +0x0ac
    AutoRefCount<cIGlobalVariableSet> mGlobalVariableSet;  // +0x0cc
    string8  mIncludeBaseDir;   // +0x0d0
    string8  mCurrentPath;      // +0x0e0
    int      mCurrentLine;      // +0x0f0
    string8  mLineLocation;     // +0x0f4
    int      mBlockCommentDepth;// +0x0104
    vec<void*> mBlockCommandStack;   // +0x0108
    vec<cMetaEntry> mMetaCommandStack; // +0x011c
    string8  mScope;            // +0x0130
    vec<int> mScopeOffsets;     // +0x0140
    string8  mLastErrorString;  // +0x0154
    unsigned char mErrorStringHasFileQualification;  // +0x0164
    int      mTotalLinesParsed; // +0x0168
    cArguments mArgs;           // +0x016c
    string8  mLCName;           // +0x01b0

    cParser();
    ~cParser();

    bool Shutdown();            // 0x00846db0
};

}}  // namespace EA::ArgScript

using namespace EA::ArgScript;

// @ 0x00847490
cParser::cParser()
{
    mStateID = 0x8ba83acb;
    mRefCount = 0;
    mInitialized = false;
    mFlags = 0;
    mMinVersion = -1;
    mMaxVersion = -1;
    mScriptVersion = -1;
    mUnknown28 = 0;
    mCurrentLine = 0;
    mBlockCommentDepth = 0;
    mErrorStringHasFileQualification = 0;
    mTotalLinesParsed = 0;
}

// @ 0x00847200
cParser::~cParser()
{
    if (mInitialized)
        Shutdown();
}

// ---------------------------------------------------------------------------
// Canvas (EA::App::Canvas)
// ---------------------------------------------------------------------------
struct Canvas;

struct CanvasEvent {
    unsigned mType;      // +0x00
    Canvas*  mpSender;   // +0x04
    void*    mpData;     // +0x08
};

struct Canvas {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
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
    void (*mpCanvasEventCallback)(CanvasEvent*, void*);   // +0x64
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

    void LockUpdate(bool bLock);
    void Update();
    void Clear();
    void SetOptions(unsigned opts);
    bool IsActive();
    void SetActive(bool bActive);
    bool GetVisible();
    void SetVisible(bool bVisible);
    bool IsMinimized();
    bool IsMaximized();
    unsigned short GetClassAtom();
    HMONITOR GetActiveMonitor();
    int  OnEraseBackground(HWND hwnd, HDC hdc);
    void OnMouseEnter(HWND hwnd);
    void FUN_00847c70(int, int);
    void OnSizing(HWND hwnd, int edge, RECT* rc);
    void FUN_00847da0(int, unsigned flag, int);
    void FUN_00847e20(unsigned short lcid);
    void SendCanvasEvent(CanvasEvent* ev);
    void SetSystemCursorVisible(bool bVisible);
    void SetSystemCursorPosition(unsigned short x, unsigned short y);
    void SetSystemCursorShape(LPARAM shape);
    bool Shutdown();
    void GetMinClientArea(unsigned* out);
    void SetMinClientArea(unsigned w, unsigned h);
    void GetClientArea(long* out);
};

// @ 0x00847950
int __stdcall FUN_00847950(HINSTANCE hInstance, void* p2, LPCSTR name, WNDCLASSEXA* wc)
{
    (void)p2;
    wc->hIcon = LoadIconA(hInstance, name);
    return 0;
}

// @ 0x00847970
void Canvas::LockUpdate(bool bLock)
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
void Canvas::Update()
{
    mbEnablePaint = true;
    if (mnUpdateLockCount == 0) {
        InvalidateRect(mhWndParent, 0, 0);
        UpdateWindow(mhWndParent);
    }
}

// @ 0x008479f0
void Canvas::Clear()
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
void Canvas::SetOptions(unsigned opts)
{
    mnOptionFlags = opts;
    if (opts & 2)
        SetThreadExecutionState(0x80000000);
    else
        SetThreadExecutionState(0x80000003);
}

// @ 0x00847a70
bool Canvas::IsActive()
{
    return GetActiveWindow() == mhWndParent;
}

// @ 0x00847a90
void Canvas::SetActive(bool bActive)
{
    SetActiveWindow(bActive ? mhWndParent : 0);
}

// @ 0x00847ab0
bool Canvas::GetVisible()
{
    return IsWindowVisible(mhWndParent) != 0;
}

// @ 0x00847ad0
void Canvas::SetVisible(bool bVisible)
{
    ShowWindow(mhWndParent, bVisible ? 1 : 0);
}

// @ 0x00847af0
bool Canvas::IsMinimized()
{
    return IsIconic(GetAncestor(mhWndParent, 3)) != 0;
}

// @ 0x00847b10
bool Canvas::IsMaximized()
{
    return IsZoomed(GetAncestor(mhWndParent, 3)) != 0;
}

// @ 0x00847b40
unsigned short Canvas::GetClassAtom()
{
    return mClassAtom;
}

// @ 0x00847b50
HMONITOR Canvas::GetActiveMonitor()
{
    return MonitorFromWindow(mhWndParent, 0);
}

// @ 0x00847b60
int Canvas::OnEraseBackground(HWND hwnd, HDC hdc)
{
    if (!mbEnablePaint && !b0c) {
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, mhBackgroundBrush);
    }
    return 1;
}

// @ 0x00847bb0
void Canvas::OnMouseEnter(HWND hwnd)
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
void Canvas::FUN_00847c70(int, int)
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
void Canvas::OnSizing(HWND hwnd, int edge, RECT* rc)
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
void Canvas::FUN_00847da0(int, unsigned flag, int)
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
void Canvas::FUN_00847e20(unsigned short lcid)
{
    mnSystemLCID = lcid;
    WCHAR buf[128];
    GetLocaleInfoW(lcid, 0x1004, buf, 0x80);
    mnSystemCodePage = wcstoul(buf, 0, 10);
}

// @ 0x00847e70
void Canvas::SendCanvasEvent(CanvasEvent* ev)
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
void Canvas::SetSystemCursorVisible(bool bVisible)
{
    if (mbCursorVisible != bVisible) {
        mbCursorVisible = bVisible;
        ShowCursor(bVisible);
    }
}

// @ 0x00847f10
void Canvas::SetSystemCursorPosition(unsigned short x, unsigned short y)
{
    PostMessageA(mhWndParent, 0x501, 0, MAKELONG(x, y));
}

// @ 0x00847f40
void Canvas::SetSystemCursorShape(LPARAM shape)
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
bool Canvas::Shutdown()
{
    if (mhWndParent) {
        CanvasEvent ev;
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
void Canvas::GetMinClientArea(unsigned* out)
{
    out[0] = mnMinWidth;
    out[1] = mnMinHeight;
}

// @ 0x00848120
void Canvas::SetMinClientArea(unsigned w, unsigned h)
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
void Canvas::GetClientArea(long* out)
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

// ---------------------------------------------------------------------------
// ArgScript: cParser command bootstrap helpers (complex / register-ABI)
// ---------------------------------------------------------------------------
void* ObjectErrorSingleton();       // 0x008de1a0
void  cCommandBase_ctor(void* p);   // 0x0083c800
extern void* gIncludeRecordVtbl;    // 0x0141ca24

// cCommandBase + IncludeRecord (retail 0x18 bytes)
struct IncludeRecord {
    void*    mvftable;     // +0x00
    cParser* mParser;      // +0x04
    int      mRefCount;    // +0x08
    void*    mField10;     // +0x10
    void*    mField14;     // +0x14
};

// @ 0x008476b0
char __cdecl FUN_008476b0(void*, void* a2)
{
    char result = 0;
    int* app = (int*)ObjectErrorSingleton();
    int* parser = (int*)((int(__thiscall*)(int*, void*))*(int*)(*app + 0x58))(app, a2);
    if (parser) {
        unsigned char local = 0;
        char ok = ((char(__thiscall*)(int*, void*, void*, int, int, int, int))*(int*)(*parser + 0x34))(
            parser, a2, &local, 1, 6, 1, 0);
        result = 0;
        if (ok) {
            IncludeRecord* rec = (IncludeRecord*)EAAllocate(0x18, "IncludeRecord", 0, 0, 0, 0);
            if (rec) {
                int* src = (int*)a2;
                cCommandBase_ctor(rec);
                rec->mvftable = &gIncludeRecordVtbl;
                rec->mField10 = (void*)src[2];
                rec->mField14 = (void*)src[1];
            }
            ((void(__thiscall*)(int*, int*))*(int*)(*parser + 0x18))(parser, (int*)rec);
            ((void(__thiscall*)(void*, const char*, void*))*(int*)(*(int*)parser + 0x14))(parser, "include", rec);
            ((void(__thiscall*)(void*, const char*, void*))*(int*)(*(int*)parser + 0x14))(parser, "sinclude", rec);
            ((void(__thiscall*)(void*))*(int*)(*(int*)parser + 0x30))(parser);
            char r = ((char(__thiscall*)(void*, void*))*(int*)(*(int*)parser + 0x4c))(parser, rec);
            ((void(__thiscall*)(void*, int))*(int*)(*(int*)parser + 0x34))(parser, r == 0);
            if (rec)
                ((void(__thiscall*)(void*))*(int*)(*(int*)rec + 0x10))(rec);
            result = r;
        }
        if (parser)
            ((void(__thiscall*)(void*))*(int*)(*parser + 8))(parser);
    }
    return result;
}

extern void* gLocalizedStringFmt;   // 0x013f3da0
void WStr_Format(void* dest, void* fmt, ...);   // 0x0041e050

// @ 0x00847810
void FUN_00847810(void* this_, cArguments* args)
{
    const char** a = (const char**)((const char**(__thiscall*)(cArguments*, int))*(int*)(*(int*)args + 0xc))(args, 1);
    (void)this_;
    (void)a;
}
