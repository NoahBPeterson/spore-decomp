#pragma once
// Shared stubs for slices s007e5220..s007ea440 (SporeApp cAppStateManager / cAppSystem).
#include "types.h"

// ---- minimal Win32 (no windows.h available) ----
typedef unsigned long DWORD;
typedef int BOOL;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HHOOK;
typedef void* HINSTANCE;
typedef unsigned int UINT;
typedef unsigned long ULONG_PTR;
typedef long LRESULT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef short SHORT;
typedef unsigned long ULONG;

extern "C" {
__declspec(dllimport) DWORD __stdcall GetCurrentProcessId(void);
__declspec(dllimport) HANDLE __stdcall OpenProcess(DWORD, BOOL, DWORD);
__declspec(dllimport) BOOL __stdcall GetProcessAffinityMask(HANDLE, ULONG_PTR*, ULONG_PTR*);
__declspec(dllimport) BOOL __stdcall SetProcessAffinityMask(HANDLE, ULONG_PTR);
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
__declspec(dllimport) HWND __stdcall GetForegroundWindow(void);
__declspec(dllimport) DWORD __stdcall GetWindowThreadProcessId(HWND, DWORD*);
__declspec(dllimport) SHORT __stdcall GetAsyncKeyState(int);
__declspec(dllimport) HHOOK __stdcall SetWindowsHookExA(int, void*, HMODULE, DWORD);
__declspec(dllimport) BOOL __stdcall UnhookWindowsHookEx(HHOOK);
__declspec(dllimport) LRESULT __stdcall CallNextHookEx(HHOOK, int, WPARAM, LPARAM);
__declspec(dllimport) HMODULE __stdcall GetModuleHandleA(const char*);
}

// ---- messaging server ----
struct MServer {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14();
  virtual void SendMessage(int a, int b, int c, int d);  // +0x18, thiscall (4 args)
};
MServer* SP_MessageServer();

// ---- canvas / app ----
struct Canvas {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40();
  virtual char v44();            // +0x44
  virtual void v48(); virtual void v4c();
  virtual void v50();
  virtual char v54();            // +0x54
};
Canvas* SP_Canvas();

struct AppSystemIface {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60();            // +0x60
};
AppSystemIface* SP_AppSystem();

// ---- minimum EASTL wide-string (16 bytes) ----
void FreeWString(void* p);
struct WString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void*    mAllocator;
  WString() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  WString(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~WString() {
    if (((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
      FreeWString(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);
  void assign(const wchar_t* first, const wchar_t* last);
  void push_back(wchar_t c);
};

struct WStringVec {
  WString* mpBegin;
  WString* mpEnd;
  WString* mpCapacity;
  void*    mAllocator;
  void push_back(const WString& s);
};

// ---- misc free functions ----
struct IPropertyList {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18();
  virtual char HasProperty(int id);   // +0x1c
  int GetIntProperty(int id);
};
extern IPropertyList* gAppProperties;   // 0x15fd918
extern uint32_t gSleepMs;               // 0x153fb30
void ThreadSleep(uint32_t* ms);         // EA::Thread::ThreadSleep

// ---- cAppSystem (retail offsets) ----
struct cAppSystem {
  char     pad00[0x10];
  Canvas*  mCanvas;            // +0x10
  void*    mMessageServer;     // +0x14
  void*    mInputManager;      // +0x18
  void*    mResourceManager;   // +0x1c
  void*    mAsyncResourceManager; // +0x20
  void*    mLocaleManager;     // +0x24
  void*    mIDGen;             // +0x28
  void*    mPropertyManager;   // +0x2c
  void*    mCheatManager;      // +0x30
  void*    mAppStateManager;   // +0x34
  void*    mCommandServer;     // +0x38
  void*    mConfigManager;     // +0x3c
  void*    mJobManager;        // +0x40
  void*    mBaseThread;        // +0x44
  void*    mTelemetry;         // +0x48
  void*    mPackManager;       // +0x4c
  void*    mGarbageMan;        // +0x50
  void*    mpDropTarget;       // +0x54
  void*    mMainViewer;        // +0x58
  void*    mGraphicsSystem;    // +0x5c
  void*    mEffectsManager;    // +0x60
  void*    mEffectsParser;     // +0x64
  char     pad68[0x98 - 0x68];
  uint32_t* mEffectCollectionIDs;  // +0x98
  void*    mEffectCollections;     // +0x9c
  char     pad_a0[0xb8 - 0xa0];
  int      mGameInfoPaused;    // +0xb8
  char     pad_bc[0xc0 - 0xbc];
  float    mFieldC0;           // +0xc0
  float    mFieldC4;           // +0xc4
  char     pad_c8[0x138 - 0xc8];
  WString  mPublicDirName;     // +0x138
  WString  mPrivateDirName;    // +0x148
  char     pad158[0x15c - 0x158];
  int      mJobRefCount;       // +0x15c
  int      mURLCount;          // +0x160
  char     pad164[0x16c - 0x164];
  int      mLockCount;         // +0x16c
  bool     mMinimize;          // +0x170
  bool     mToggleFullscreen;  // +0x171
  bool     mToggleDisplay;     // +0x172
  WStringVec mURLsToOpen;      // +0x174

  void DeactivateApp();
  void ToggleFullscreen();
  void ToggleDisplay();
  void UnlockFromDevice();
  void LockToDevice();
  void SetEffectCollectionIDs(uint32_t* ids, void* collections);
  int  FUN_007e5e80();
  void LoaderCommandHandler();
  void RunJobs(int timeLimit);
  bool FUN_007e6630();
  void FUN_007e65d0(bool add);
  int  PreShutdown();
  int  Init();
  bool LoadPlugins();
  bool InitPlugins(void* commandLine);
  void SetUserDirNames(wchar_t* publicDir, wchar_t* privateDir);
  void OpenURL(const wchar_t* url);
};

extern HHOOK gSuppressAppSwitchHook;   // 0x16393a4

struct KBDLLHOOKSTRUCT_ {
  uint32_t vkCode;
  uint32_t scanCode;
  uint32_t flags;
  uint32_t time;
  ULONG_PTR dwExtraInfo;
};
LRESULT __stdcall SuppressAppSwitchProc(int code, WPARAM wParam, LPARAM lParam);

struct LoaderVtbl {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38();
  virtual void vf15(int a);      // +0x3c
  virtual void v40();
};

// helper used by several functions
void FUN_00777ae0(int id, void* obj, int v);
void* FUN_0067dd50();
