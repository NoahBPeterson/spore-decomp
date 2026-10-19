// src/game/SPEngine/SPAppSystem.cpp -- migrated from slice(s) s007ea440, s007e9a00, s007e8ba0, s007e7d00, s007e70b0, s007e6210, s007e5220 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/CommandLine.h"
#include "EA/Variant.h"
#include "EA/ResourceMan/Key.h"
#include "EA/SSL/SSLManager.h"
#include "EA/Stopwatch.h"
#include "SP/cAppStateManager.h"
#include "SP/cCommandServer.h"
#include "SP/cConfigManager.h"
#include "SP/cGraphicsSystem.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cTelemetry.h"
#include "EA/Allocator/ICoreAllocator.h"
#include <intrin.h>
#include "SP/cAsyncResourceManager.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/Messaging/Server.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t gSleepMs;               // 0x153fb30

// ---- items of slice s007e5220 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned long DWORD;
typedef int BOOL;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HHOOK;
typedef unsigned long ULONG_PTR;
typedef long LRESULT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef short SHORT;
extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentProcessId(void);
extern "C" __declspec(dllimport) HANDLE __stdcall OpenProcess(DWORD, BOOL, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall GetProcessAffinityMask(HANDLE, ULONG_PTR*, ULONG_PTR*);
extern "C" __declspec(dllimport) BOOL __stdcall SetProcessAffinityMask(HANDLE, ULONG_PTR);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) HWND __stdcall GetForegroundWindow(void);
extern "C" __declspec(dllimport) DWORD __stdcall GetWindowThreadProcessId(HWND, DWORD*);
extern "C" __declspec(dllimport) SHORT __stdcall GetAsyncKeyState(int);
extern "C" __declspec(dllimport) HHOOK __stdcall SetWindowsHookExA(int, void*, HMODULE, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall UnhookWindowsHookEx(HHOOK);
extern "C" __declspec(dllimport) LRESULT __stdcall CallNextHookEx(HHOOK, int, WPARAM, LPARAM);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(const char*);
struct MServer {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14();
  virtual void SendMessage(int a, int b, int c, int d);  // +0x18, thiscall (4 args)
};
MServer* SP_MessageServer();
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
struct IPropertyList {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18();
  virtual char HasProperty(int id);   // +0x1c
  int GetIntProperty(int id);
};
extern IPropertyList* gAppProperties;   // 0x15fd918
extern uint32_t gSleepMs;               // 0x153fb30
void ThreadSleep(uint32_t* ms);         // EA::Thread::ThreadSleep
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
void FUN_00777ae0(int id, void* obj, int v);
void* FUN_0067dd50();
HHOOK gSuppressAppSwitchHook;   // 0x16393a4
IPropertyList* gAppProperties;  // 0x15fd918
uint32_t gSleepMs;              // 0x153fb30
// ---- items of slice s007e5220 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentProcessId(void);
extern "C" __declspec(dllimport) HANDLE __stdcall OpenProcess(DWORD, BOOL, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall GetProcessAffinityMask(HANDLE, ULONG_PTR*, ULONG_PTR*);
extern "C" __declspec(dllimport) BOOL __stdcall SetProcessAffinityMask(HANDLE, ULONG_PTR);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) HWND __stdcall GetForegroundWindow(void);
extern "C" __declspec(dllimport) DWORD __stdcall GetWindowThreadProcessId(HWND, DWORD*);
extern "C" __declspec(dllimport) SHORT __stdcall GetAsyncKeyState(int);
extern "C" __declspec(dllimport) HHOOK __stdcall SetWindowsHookExA(int, void*, HMODULE, DWORD);
extern "C" __declspec(dllimport) BOOL __stdcall UnhookWindowsHookEx(HHOOK);
extern "C" __declspec(dllimport) LRESULT __stdcall CallNextHookEx(HHOOK, int, WPARAM, LPARAM);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(const char*);
extern IPropertyList* gAppProperties;   // 0x15fd918
extern HHOOK gSuppressAppSwitchHook;   // 0x16393a4

// ---- items of slice s007e6210 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete__(void* p);
extern int32_t gDefaultWatcherValue;
extern void* gPTR_DAT_0153f85c;
extern void* gPTR_DAT_0153f860;
struct PropListBase {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20();
  virtual char vf24(void* a, void* b);   // +0x24
};
struct CPropList { int GetModificationCount(); };
struct PropWatcher {
  uint32_t f0;   // +0
  void*    f4;   // +4  (wraps the PropListBase)
  void*    f8;   // +8  (owner passed to vf24)
  int      fc;   // +0xc cached modification count
  void* f10;     // +0x10 (property list at wrapper+0x30)
  bool Check();
  void Read(void* p2);
};
uint32_t* FUN_004e41c0();
struct JobManagerVtbl_ {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18();
  virtual void vf7(void* thread, void* sw, int b);   // +0x1c
  virtual void vf8(); virtual void vf9();
  virtual void vf10(void* a);                          // +0x28
  virtual void vf11();                                 // +0x2c
};
void* FUN_00921d70();
struct PtrDel { void* p; void del(); };
struct Stopwatch {
  char pad[0x20];
  void ctor(int a, int b);
  void SetTimeLimit(int limit, int b);
};
void FUN_008d5d10(int); void FUN_0067e090(int); void FUN_006ae940();
void FUN_00762f00(int); void FUN_0068c460();
void FUN_0067df00(int); void FUN_0067df30(int);
void FUN_007c79e0(); void FUN_00c2e4e0();
void* SP_CheatManager2();
typedef void (__thiscall *VF0)(void*);
typedef void (__thiscall *VF1)(void*, int);
typedef void (__thiscall *VF3)(void*, void*, int, int);
__forceinline void VC0(void* o, int off) { ((VF0)*(void**)((char*)*(void**)o + off))(o); }
__forceinline void VC1(void* o, int off, int a) { ((VF1)*(void**)((char*)*(void**)o + off))(o, a); }
__forceinline void VC3(void* o, int off, void* a, int b, int c) { ((VF3)*(void**)((char*)*(void**)o + off))(o, a, b, c); }
void __cdecl FUN_0067df30(void*);
// ---- items of slice s007e6210 end

// ---- items of slice s007e70b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl atol(const char*);
struct PLBase32 {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
  virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
  virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
  virtual void v90(); virtual void v94(); virtual void v98();
  virtual char vf24(void* a, void* b);   // +0x24
  int   vf18(int a);                     // +0x18
};
struct PropWatcher32 {
  uint32_t f0; void* f4; void* f8; int fc;
  PropWatcher32* ctor(void* list, void* owner, uint32_t value);
  void Read(void* p2);
};
void* gAllocator_13ebc58;
void* gVtbl_13eb90c;
void* gVtbl_13eb844;
void* operator_new(uint32_t sz, void* alloc, int a, int b, int c, int d);
struct Arguments {
    char HasFlag(const char* name);
    const char*** MainArguments(int* count, int a, int b);
};
struct MsgObj {
    void* vt;      // +0
    int   ref;     // +4
    int   val;     // +8
    char  pad_c[0x30 - 0xc];
    int   f30;     // +0x30
    char  pad34[0x38 - 0x34];
    int   f38;     // +0x38
};
struct QuitCheat { void Execute(Arguments* args); };
// ---- items of slice s007e70b0 end

// ---- items of slice s007e7d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const wchar_t*, const wchar_t*, size_t);
extern wchar_t gEmptyWStr[2];  // 0x1667bac: shared empty-string sentinel
extern const wchar_t* gRegSporeKey;      // 0x153f850 L"SOFTWARE\\Electronic Arts\\SPORE"
extern const wchar_t* gRegDataDirValue;  // 0x153f854 L"DataDir"
extern const wchar_t* gDllMask;          // 0x153f84c L"*.dll"
extern const char kEastlAllocFile[];  // 0x013ebb38 "...EASTL/allocator.h"
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);  // 0x00f473a0
enum NoInit { kNoInit };
struct WString_s007e_7d00 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WString_s007e_7d00() : mpBegin(gEmptyWStr), mpEnd(gEmptyWStr), mpCapacity(gEmptyWStr + 1) {}
    WString_s007e_7d00(NoInit) {}
    WString_s007e_7d00(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    WString_s007e_7d00(const WString_s007e_7d00& o);  // defined below (EASTL copy ctor, "App" allocator)
    ~WString_s007e_7d00() {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            operator_delete__(mpBegin);
    }
    void RangeInitialize(const wchar_t* p);                       // 0x579a90
    void assign(const wchar_t* first, const wchar_t* last);       // 0x423650
    void append(const wchar_t* first, const wchar_t* last);       // 0x429580
    void appendC(const wchar_t* s);                               // 0x5c3d90 (path-string append)
    int find(wchar_t ch, size_t pos);                             // 0x4f6ab0
    void assignC(const wchar_t* s) { const wchar_t* e = s; while (*e) ++e; assign(s, s + (e - s)); }
    void appendRaw(const wchar_t* s) { const wchar_t* e = s; while (*e) ++e; append(s, s + (e - s)); }
    bool empty() const { return mpBegin == mpEnd; }
};
WString_s007e_7d00* __cdecl StrConcat(WString_s007e_7d00* out, const WString_s007e_7d00* a, const wchar_t* b);  // 0x57cba0 (operator+)
struct FilePath {
    wchar_t mPath[0x208];
    FilePath(const wchar_t* p);                                    // 0x930f60
    void GetFileName(wchar_t* out, int n);                         // 0x930cb0
    void GetDriveAndDirectory(wchar_t* out, int n);                // 0x930d20
};
struct CommandLine_s007e_7d00 {
    const wchar_t** GetArgument(int idx);                          // 0x92b1b0
    int FindSwitch(const wchar_t* name, int a, WString_s007e_7d00* out, int b);  // 0x92b300
};
namespace EA {
namespace IO {
namespace File {
 bool Exists(const wchar_t* path); 
}
}
}
namespace EA {
namespace IO {
namespace Directory {
 void GetCurrentWorkingDirectory(wchar_t* out); 
}
}
}
void __cdecl SetDirFromID(uint32_t id, const wchar_t* path, int flags);      // 0x688bb0
bool __cdecl GetDirOverride(uint32_t id, WString_s007e_7d00* out, int flags);            // 0x688830
const wchar_t* __cdecl GetDirFromID(uint32_t id);                             // 0x6886b0
const wchar_t* __cdecl GetDataDir();                                          // 0x688cb0
const wchar_t* __cdecl FUN_00688cd0();                                        // 0x688cd0
bool __cdecl FindDirectoryUp(WString_s007e_7d00* path);                                  // 0x6baec0
bool __cdecl RegistryGetString(uint32_t hive, const wchar_t* key, const wchar_t* val, WString_s007e_7d00* out);  // 0x6ab840
bool __cdecl GetElemWStr(int idx, WString_s007e_7d00* out);                              // 0x686250
bool __cdecl FUN_00685520(bool b);                                            // 0x685520
void __cdecl FUN_009309b0(wchar_t* out, const wchar_t* name, const wchar_t* dir, int n);  // 0x9309b0
void __cdecl GetSystemPath(int id, wchar_t* out, int flags);                  // 0x9323c0
void __cdecl EnsureDirectoryExists(const wchar_t* path);                      // 0x932ae0
const wchar_t* __cdecl EntryFindFirst(const wchar_t* dir, const wchar_t* mask, int a, int b);  // 0x0092e730
int __cdecl EntryFindNext(const wchar_t* entry, int a);  // 0x0092e8e0
void __cdecl EntryFindFinish(const wchar_t* entry);  // 0x0092e9b0
inline WString_s007e_7d00::WString_s007e_7d00(const WString_s007e_7d00& o) {
    size_t n = o.mpEnd - o.mpBegin;
    size_t cap = n + 1;
    wchar_t* p;
    if (cap > 1) {
        p = (wchar_t*)operator_new(cap * 2, "App", 0, 0, kEastlAllocFile, 0xd1);
        mpCapacity = p + cap;
    } else {
        p = gEmptyWStr;
        mpCapacity = gEmptyWStr + 1;
    }
    memcpy(p, o.mpBegin, n * 2);
    mpBegin = p;
    mpEnd = p + n;
    *mpEnd = 0;
}
struct PluginRegistry {  // subobject at cAppSystem+0xd0 (SharedLibraryRegistry)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Load(const wchar_t* path, int flag);  // +0x10
};
struct cAppSystem_s007e_7d00 {
    char pad00[0xd0];
    PluginRegistry mPluginLibraries;  // +0xd0
    char pad_d4[0x138 - 0xd4];
    WString_s007e_7d00 mPublicDirName;   // +0x138
    uint32_t pad_a;           // +0x144 (allocator)
    WString_s007e_7d00 mPrivateDirName;  // +0x148
    uint32_t pad_b;           // +0x154
    bool mMinimize;           // +0x158
    bool mToggleFullscreen;   // +0x159
    char pad_15a[0x188 - 0x15a];
    bool mServerCheatFlag;    // +0x188

    void SetupDirectories(CommandLine_s007e_7d00* cmd);  // 0x007e7d00 (cAppSystem::SetupDirectories)
    bool LoadPlugins();  // 0x007e8760 (cAppSystem::LoadPlugins)
};
struct RCObj { virtual int AddRef(); virtual int Release(); };
RCObj** __cdecl RCCopyBackward(RCObj** first, RCObj** last, RCObj** destEnd);  // 0xac97a0
struct RCVec {
    RCObj** mpBegin;
    RCObj** mpEnd;
    RCObj** mpCapacity;
    void DoInsertValue(RCObj** position, RCObj* const* value);
};
    void EntryFindFinish(...); // 0x0092e9b0
    void EntryFindFirst(...); // 0x0092e730
    void EntryFindNext(...); // 0x0092e8e0
// ---- items of slice s007e7d00 end

// ---- items of slice s007e8ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(void*);
extern "C" __declspec(dllimport) long __cdecl wcstol(const wchar_t*, wchar_t**, int);
extern "C" __declspec(dllimport) long __cdecl _wtol(const wchar_t*);
extern wchar_t g_01667bac[2];
extern uint32_t g_0163939c;          // job priority
extern uint8_t  g_0154c478;          // multi-core flag
extern uint32_t g_01639470;
struct IPropertyList_s007e_8ba0 {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18();
  virtual char HasProperty(int id);   // +0x1c
  int GetIntProperty(int id);
  void SetBoolProperty(uint32_t id, bool v);   // 0x006a17e0 (cDirectPropertyList)
};
extern IPropertyList_s007e_8ba0* gAppProperties_s007e_8ba0;   // 0x15fd918
#define P1(x) virtual void x();
#define P4(x) P1(x##0) P1(x##1) P1(x##2) P1(x##3)
struct IRefObj {                    // AddRef = slot 0, Release = slot 1
  virtual void AddRef();
  virtual void Release();
  P1(v8) P1(vc)                     // slot 3 (+0xc) is called on the cheat manager
};
struct IJobMgr {
  P1(v0)
  virtual bool Start(uint32_t threadMask, void (*callback)());   // +4
  P1(v8) P1(vc) P1(v10)
  virtual void* CreateThread(int flags, int a, int b);           // +0x14
};
struct IServer {
  P1(v0)
  virtual void AddRef();                                         // +4
  P1(v8) P1(vc)
  virtual void Configure(int a, int b);                          // +0x10
};
struct IResMgr {
  P1(v0)
  virtual void AddRef();                                         // +4
  P4(a) P4(b) P4(c) P1(d0) P1(d1) P1(d2)
  virtual void RegisterFactory(int a, void* factory, int b);     // +0x44 (slot 17)
  P4(e) P4(f) P4(g) P4(h) P1(i0) P1(i1)
  virtual void RegisterExtension(uint32_t typeId, const wchar_t* ext);  // +0x90 (slot 36)
};
struct IAsyncResMgr {
  virtual void AddRef();                                         // +0
};
struct IPlainRes {                  // object returned by FUN_007f18e0
  P4(a)
  virtual void AddRef();                                         // +0x10
};
struct IPluginLibs {
  P1(v0)
  virtual bool Enumerate(bool (*callback)(), int a);             // +4
};
struct cAppSystem_s007e_8ba0 {
  char     pad00[0x10];
  Canvas*  mCanvas;            // +0x10
  struct IServer* mMessageServer; // +0x14
  void*    mInputManager;      // +0x18
  struct IResMgr* mResourceManager; // +0x1c
  struct IAsyncResMgr* mAsyncResourceManager; // +0x20
  void*    mLocaleManager;     // +0x24
  void*    mIDGen;             // +0x28
  void*    mPropertyManager;   // +0x2c
  struct IRefObj* mCheatManager; // +0x30
  void*    mAppStateManager;   // +0x34
  void*    mCommandServer;     // +0x38
  void*    mConfigManager;     // +0x3c
  struct IJobMgr* mJobManager;   // +0x40
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
  struct IRefObj* mApp;        // +0xc8  (CreateApp() result, AddRef/Release smart pointer)
  char     pad_cc[0xd0 - 0xcc];
  uint32_t mPluginLibraries;   // +0xd0  (vptr of an embedded plugin-library list object)
  char     pad_d4[0x128 - 0xd4];
  wchar_t* mDdfDirBegin;       // +0x128 (string begin)
  wchar_t* mDdfDirEnd;         // +0x12c (string end)
  char     pad_130[0x138 - 0x130];
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
  char     pad184[0x1e8 - 0x184];
  bool     mDemo;              // +0x1e8
  bool     mDev;               // +0x1e9

  void DeactivateApp();  // 0x007e5ed0 (cAppSystem::DeactivateApp)
  void ToggleFullscreen();  // 0x007e5f00 (cAppSystem::ToggleFullscreen)
  void ToggleDisplay();  // 0x007e5f30 (cAppSystem::ToggleDisplay)
  void UnlockFromDevice();  // 0x007e6020 (cAppSystem::UnlockFromDevice)
  void LockToDevice();  // 0x007e5fd0 (cAppSystem::LockToDevice)
  void SetEffectCollectionIDs(uint32_t* ids, void* collections);  // 0x007e6050 (cAppSystem::SetEffectCollectionIDs)
  int  FUN_007e5e80();  // 0x007e5e80 (cAppSystem::FUN_007e5e80)
  void LoaderCommandHandler();  // 0x007e6090 (cAppSystem::LoaderCommandHandler)
  void RunJobs(int timeLimit);  // 0x007e6650 (cAppSystem::RunJobs)
  bool FUN_007e6630();  // 0x007e6630 (cAppSystem::FUN_007e6630)
  void FUN_007e65d0(bool add);  // 0x007e65d0 (cAppSystem::FUN_007e65d0)
  int  PreShutdown();  // 0x007e6470 (cAppSystem::PreShutdown)
  int  Init();  // 0x007e67a0 (cAppSystem::Init)
  bool LoadPlugins();  // 0x007e8760 (cAppSystem::LoadPlugins)
  bool InitPlugins(void* commandLine);  // 0x007e9300 (cAppSystem::InitPlugins)
  bool PreInit(struct CommandLine* cmd, int unused);  // 0x007e8ba0
  void SetupDirectories(struct CommandLine* cmd);     // 0x007e7d00
  void FUN_007e7b50();                                // 0x007e7b50
  void SetUserDirNames(wchar_t* publicDir, wchar_t* privateDir);  // 0x007e93d0 (cAppSystem::SetUserDirNames)
  void OpenURL(const wchar_t* url);
};
struct CommandLine {
  int FindSwitch(const wchar_t* name, int a, void* outValue, int b);   // 0x0092b300
};
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);   // 0x00f473a0
void operator delete(void* p, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);   // 0x00f47410
struct ZoneObject {
    static void* operator new(unsigned int n, const char* name, int flags = 0,
                              unsigned int debugFlags = 0, const char* file = 0, int line = 0);   // 0x00926020
    static void operator delete(void* p, const char* name, int flags, unsigned int debugFlags,
                                const char* file, int line);   // 0x00926060
};
struct Server {
    uint32_t pad[0xc8 / 4];
    Server();   // 0x00884a20
};
struct ResourceManager : ZoneObject {
    uint32_t pad[0x178 / 4];
    ResourceManager(int);   // 0x008e20c0
};
struct AsyncResourceManager {
    uint32_t pad[0x890 / 4];
    AsyncResourceManager();   // 0x006aedc0
};
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;
    WStr() : mpBegin(g_01667bac), mpEnd(g_01667bac), mpCapacity(g_01667bac + 1) {}
    ~WStr() {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
            FreeWString(mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
struct SYSTEM_INFO_ {
    uint32_t dwOemId;
    uint32_t dwPageSize;
    void*    lpMinimumApplicationAddress;
    void*    lpMaximumApplicationAddress;
    uint32_t dwActiveProcessorMask;
    uint32_t dwNumberOfProcessors;
    uint32_t dwProcessorType;
    uint32_t dwAllocationGranularity;
    uint16_t wProcessorLevel;
    uint16_t wProcessorRevision;
};
void  FUN_006926e0(void* teb);                 // stores the main thread's TEB
void  FUN_0067e050(void* p);                   // stores gAppProperties
void  FUN_0067df20(CommandLine* cmd);          // stores the command line
void  FUN_007e5d90();                          // LockToSingleCore
void  FUN_0068da90();                          // InstallNameCallbacks
void  FUN_00c2e4e0();                          // UTFWin::ILayoutElement::SetSerializer (empty)
void* FUN_0068c520();                          // creates the cGarbageMan
void  FUN_0067e0a0(void* p);
void  FUN_00762f00(char v);
void  FUN_0092a020();                          // EA::CallbackSystem::Init
IJobMgr* FUN_00690ae0();                       // creates the job manager
void  FUN_007e5de0();                          // job callback
void  FUN_0068f4c0(IJobMgr* p);
void  FUN_00883870(IServer* p);
void  FUN_0067deb0(IServer* p);
void  FUN_008de1b0(IResMgr* p);
void  FUN_0067dec0(IResMgr* p);
void  FUN_008d5d10(IAsyncResMgr* p);
void  FUN_0067e090(IAsyncResMgr* p);
IPlainRes* FUN_007f18e0();
int   FUN_00932370(wchar_t* buf);              // EA::IO::Directory::GetCurrentWorkingDirectory
bool  FUN_00931fa0(const wchar_t* path);       // EA::IO::File::Exists
void  FUN_00761190();
void  FUN_006adc90(IResMgr* p);
IRefObj* FUN_007d8dc0();                       // SP::CreateApp
void  FUN_0067df00(IRefObj* p);
IRefObj* FUN_0067fb50();                       // creates the cheat manager
void  FUN_0067e030(IRefObj* p);
void  FUN_007c79e0();                          // SP::CheatManager
const wchar_t* FUN_00688cb0();                 // SP::GetDataDir
bool  FUN_009322b0(const wchar_t* path);       // EA::IO::Directory::Exists
void  FUN_006baff0(const char* msg, int a, int b);   // SP::SporeAlert
bool  FUN_007e6100();                          // plugin enumeration callback
void  FUN_00936410(IPluginLibs* p);
void  FUN_0084ebc0();
void  FUN_0084eba0();
void  FUN_0084dc30();
void  FUN_0084dc10();
void  FUN_0084dc70();                          // EA::Gimex::AddPNGImport
void  FUN_0084dc50();
void  FUN_0084bc60();
void  FUN_0084bc40();
void  FUN_00a6c750();
void  FUN_00687590(IResMgr* mgr, const wchar_t* dir, int priority);
const wchar_t* FUN_006886b0(uint32_t id);      // SP::GetDirFromID
bool  FUN_00688830(uint32_t id, WStr* out, int a);
void  FUN_00687610(const wchar_t* dataDir, const wchar_t* a, const wchar_t* b, int c);   // SP::SetupResources
void  WStr_Format(WStr* dst, const wchar_t* fmt, ...);   // 0x0041e050
static inline void AssignRef(IRefObj*& slot, IRefObj* p) {
    IRefObj* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}
// ---- items of slice s007e8ba0 end

// @ 0x007e5d90
void LockToSingleCore()
{
    DWORD pid = GetCurrentProcessId();
    HANDLE h = OpenProcess(0x1f0fff, 0, pid);
    ULONG_PTR local_8[2];
    local_8[1] = 0;
    local_8[0] = 0;
    GetProcessAffinityMask(h, local_8 + 1, local_8);
    SetProcessAffinityMask(h, 1);
    CloseHandle(h);
}







// @ 0x007e5e10
void FUN_007e5e10()
{
    HWND hwnd = GetForegroundWindow();
    if (hwnd != 0) {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (GetCurrentProcessId() == pid)
            return;
    }
    if (gAppProperties->HasProperty(0x4b))
        gSleepMs = gAppProperties->GetIntProperty(0x4b);
    if (gSleepMs > 0)
        ThreadSleep(&gSleepMs);
}







// @ 0x007e5e80
int cAppSystem::FUN_007e5e80()
{
    return --mURLCount;
}







// @ 0x007e5ed0
void cAppSystem::DeactivateApp()
{
    mMinimize = true;
    if (mLockCount)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}







// @ 0x007e5f00
void cAppSystem::ToggleFullscreen()
{
    bool locked = mLockCount != 0;
    mToggleFullscreen = true;
    if (locked)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}







// @ 0x007e5f30
void cAppSystem::ToggleDisplay()
{
    bool locked = mLockCount != 0;
    mToggleDisplay = true;
    if (locked)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}







// @ 0x007e5f60
LRESULT __stdcall SuppressAppSwitchProc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code == 0) {
        KBDLLHOOKSTRUCT_* kb = (KBDLLHOOKSTRUCT_*)lParam;
        SHORT ctrl = GetAsyncKeyState(0x11);
        if ((kb->vkCode == 0x1b && ctrl < 0) ||
            (kb->vkCode == 9 && (kb->flags & 0x20)) ||
            (kb->vkCode == 0x1b && (kb->flags & 0x20))) {
            SP_AppSystem()->v60();
            return 1;
        }
    }
    return CallNextHookEx(gSuppressAppSwitchHook, code, wParam, lParam);
}







// @ 0x007e5fd0
void cAppSystem::LockToDevice()
{
    if (mLockCount++ == 0) {
        if (SP_Canvas()->v54())
            gSuppressAppSwitchHook = SetWindowsHookExA(0xd, (void*)&SuppressAppSwitchProc,
                                                       GetModuleHandleA(0), 0);
    }
}







// @ 0x007e6020
void cAppSystem::UnlockFromDevice()
{
    if (--mLockCount == 0 && gSuppressAppSwitchHook) {
        UnhookWindowsHookEx(gSuppressAppSwitchHook);
        gSuppressAppSwitchHook = 0;
    }
}







// @ 0x007e6050
void cAppSystem::SetEffectCollectionIDs(uint32_t* ids, void* collections)
{
    mEffectCollectionIDs = ids;
    if (collections)
        mEffectCollections = collections;
}







// @ 0x007e6090
void cAppSystem::LoaderCommandHandler()
{
    mFieldC0 = (mURLCount > 0) ? 1.0f : 0.0f;
    mFieldC4 = mCanvas->v44() ? 1.0f : 0.0f;
    FUN_00777ae0(0x248, &mGameInfoPaused, 0);
    LoaderVtbl* p = (LoaderVtbl*)FUN_0067dd50();
    if (p)
        p->vf15(0);
}






// @ 0x007e6210
void LoadGameInfoProperties(void* data)
{
    // Reads "game info" AppProperties; incomplete (see partial.txt).
    (void)data;
}






// @ 0x007e6470
int cAppSystem::PreShutdown()
{
    VC0(*(void**)((char*)this + 0xc8), 0x1c);
    if (mJobManager) { VC0(mJobManager, 8); mBaseThread = 0; }
    if (mAsyncResourceManager) {
        FUN_008d5d10(0); FUN_0067e090(0); FUN_006ae940();
        VC0(mAsyncResourceManager, 4); mAsyncResourceManager = 0;
    }
    if (mGarbageMan) { FUN_00762f00(0); FUN_0068c460(); }
    VC1(SP_CheatManager2(), 0x1c, (int)gPTR_DAT_0153f85c);
    VC1(SP_CheatManager2(), 0x1c, (int)gPTR_DAT_0153f860);
    FUN_007c79e0();
    FUN_00c2e4e0();
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0xf62add, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, (int)0xae1cfe73, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0x255abf5, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0x212d3e7, 0xffffd8f1);
    void* pc = *(void**)((char*)this + 0xc8);
    if (pc) {
        VC0(pc, 0x10);
        FUN_0067df00(0);
        void* q = *(void**)((char*)this + 0xc8);
        if (q) { *(void**)((char*)this + 0xc8) = 0; VC0(q, 4); }
    }
    void* am = mAppStateManager;
    if (am) {
        VC0(am, 0x14);
        FUN_0067df30(0);
        void* q = *(void**)((char*)this + 0x34);
        if (q) { mAppStateManager = 0; VC0(q, 4); }
    }
    void* gs = mGraphicsSystem;
    if (gs) VC0(gs, 0x10);
    return 1;
}






// @ 0x007e65d0
void cAppSystem::FUN_007e65d0(bool add)
{
    if (add) {
        if (_InterlockedIncrement((volatile long*)&mJobRefCount) == 1)
            ((JobManagerVtbl_*)mJobManager)->vf10(FUN_00921d70());
    } else {
        if (_InterlockedDecrement((volatile long*)&mJobRefCount) == 0)
            ((JobManagerVtbl_*)mJobManager)->vf11();
    }
}






// @ 0x007e6630
bool cAppSystem::FUN_007e6630()
{
    long old = _InterlockedExchangeAdd((volatile long*)&mJobRefCount, 0);
    return old > 0;
}






// @ 0x007e6650
void cAppSystem::RunJobs(int timeLimit)
{
    Stopwatch sw;
    sw.ctor(4, 0);
    sw.SetTimeLimit(timeLimit, 1);
    JobManagerVtbl_* jm = (JobManagerVtbl_*)mJobManager;
    jm->vf7(mBaseThread, &sw, 1);
}






// @ 0x007e6690
void PtrDel::del()
{
    operator_delete__(p);
}






// @ 0x007e66a0
bool PropWatcher::Check()
{
    int* w = (int*)f4;
    if (w) {
        int mc = (int)w[0xc] ? ((CPropList*)w[0xc])->GetModificationCount() : 0;
        if ((int)fc != (int)w[0xd] + mc) {
            int mc2 = (int)w[0xc] ? ((CPropList*)w[0xc])->GetModificationCount() : 0;
            fc = (int)w[0xd] + mc2;
            PropListBase* pb = (PropListBase*)w;
            PropWatcher* local = this;
            if (pb->vf24(f8, &local)) {
                uint32_t v = *FUN_004e41c0();
                if (f0 != v) {
                    f0 = v;
                    return true;
                }
            }
        }
    }
    return false;
}






// @ 0x007e6720
void PropWatcher::Read(void* p2)
{
    PropListBase* pb = (PropListBase*)p2;
    if (pb->vf24(f8, &p2)) {
        int* q = (int*)p2;
        short t = *(short*)((char*)q + 0x12);
        int* src;
        if (t == 9 || t == 0x10) {
            if ((*(uint8_t*)((char*)q + 0x10) & 0x30) == 0)
                src = (int*)(-(uint32_t)(t != 0) & (uint32_t)q);
            else
                src = (int*)*q;
        } else {
            src = &gDefaultWatcherValue;
        }
        f0 = (uint32_t)*src;
    }
    int* w = (int*)f4;
    if (w[0xc]) {
        fc = (int)w[0xd] + ((CPropList*)w[0xc])->GetModificationCount();
        return;
    }
    fc = (int)w[0xd];
}





// @ 0x007e70b0
int cAppSystemHandleMessage(cAppSystem* self, uint32_t msg, int data)
{
    // Custom message dispatch (ResourceMan / effect messages); not reconstructed.
    (void)self; (void)msg; (void)data;
    return 0;
}





// @ 0x007e7260
PropWatcher32* PropWatcher32::ctor(void* list, void* owner, uint32_t value)
{
    f0 = value;
    f4 = list;
    if (list)
        ((PLBase32*)list)->v00();
    f8 = owner;
    fc = 0;
    if (list)
        Read(list);
    return this;
}





// @ 0x007e72d0
void QuitCheat::Execute(Arguments* args)
{
    if (args->HasFlag("crash"))
        *(int*)0 = 0;
    int count = 0;
    const char*** argv = args->MainArguments(&count, 0, 1);
    long v = 0;
    if (count > 0)
        v = atol((const char*)argv[0]);
    MsgObj* m = (MsgObj*)operator_new(0x40, &gAllocator_13ebc58, 0, 0, 0, 0);
    if (m) {
        m->f30 = 0;
        m->vt = &gVtbl_13eb90c;
        m->ref = 0;
        m->vt = &gVtbl_13eb844;
        m->f38 = 0;
    }
    m->val = (int)v;
    SP_MessageServer()->SendMessage(0x153c326, (int)m, 0, 0);
}





// @ 0x007e7380
int cAppSystemConfigure(void* self, void* a, int b)
{
    (void)self; (void)a; (void)b;
    return 0;
}





// @ 0x007e7630
void cAppSystemCtor(void* self, void* a)
{ (void)self; (void)a; }





// @ 0x007e78d0
void cAppSystemDtor(void* self)
{ (void)self; }





// @ 0x007e7b50
void FUN_007e7b50(void* self)
{ (void)self; }




// @ 0x007e7d00
void cAppSystem_s007e_7d00::SetupDirectories(CommandLine_s007e_7d00* cmd)
{
    wchar_t exeName[260];
    wchar_t cwdDir[260];
    wchar_t exeDir[260];
    wchar_t cwdFull[260];
    wchar_t cfgBuf[256];
    wchar_t sysPath[256];

    // Directory of the exe, or of the cwd if the exe name exists there.
    FilePath exePath(*cmd->GetArgument(0));
    exePath.GetFileName(exeName, 0x104);
    EA::IO::Directory::GetCurrentWorkingDirectory(cwdFull);
    FilePath cwdPath(cwdFull);
    cwdPath.GetDriveAndDirectory(cwdDir, 0x104);
    WString_s007e_7d00 candidate(cwdDir);
    candidate.appendRaw(exeName);
    FilePath* chosen = EA::IO::File::Exists(candidate.mpBegin) ? &cwdPath : &exePath;
    chosen->GetDriveAndDirectory(exeDir, 0x104);
    SetDirFromID(0xa0214a, exeDir, 0);

    WString_s007e_7d00 dataDir;
    bool bDev = cmd->FindSwitch(L"devDirs", 0, 0, 0) != -1;
    bool bShip = cmd->FindSwitch(L"shipDirs", 0, 0, 0) != -1;
    bool useRegistry = true;
    if (bDev) useRegistry = false;
    if (bShip) useRegistry = true;

    bool bDataDirSwitch = cmd->FindSwitch(L"dataDir", 0, &dataDir, 0) != -1;
    if (!bDataDirSwitch) {
        if (useRegistry) {
            if (RegistryGetString(0x80000002, gRegSporeKey, gRegDataDirValue, &dataDir)) {
                int q = dataDir.find(L'"', 1);
                if (q != -1) dataDir.assign(dataDir.mpBegin + 1, dataDir.mpBegin + q);
            }
        } else if (dataDir.empty()) {
            dataDir.appendC(L"Data/");
            if (!FindDirectoryUp(&dataDir)) dataDir.appendC(L"./");
        }
    }
    if (!useRegistry) {
        if (cmd->FindSwitch(L"baseGame", 0, 0, 0) != -1) mMinimize = true;
        if (mMinimize) {
            dataDir.assignC(L"BaseData");
            if (!FindDirectoryUp(&dataDir) && !dataDir.empty()) {
                *dataDir.mpBegin = 0;
                dataDir.mpEnd = dataDir.mpBegin;
            }
        }
    }
    SetDirFromID(0xa02149, dataDir.mpBegin, 0);
    dataDir.assignC(GetDataDir());

    WString_s007e_7d00 localeDir;
    {
        WString_s007e_7d00 tmp(kNoInit);
        WString_s007e_7d00* r = StrConcat(&tmp, &dataDir, L"Locale/");
        if (r != &localeDir) localeDir.assign(r->mpBegin, r->mpEnd);
    }
    SetDirFromID(0x45962cc, localeDir.mpBegin, 0);

    WString_s007e_7d00 configDir;
    if (useRegistry) {
        WString_s007e_7d00 reg;
        bool got = GetElemWStr(2, &reg);
        if (FUN_00685520(got ? true : false)) {
            configDir.assign(reg.mpBegin, reg.mpEnd);
        } else {
            configDir.assignC(L"Data/");
            if (!FindDirectoryUp(&configDir)) configDir.appendC(L"./");
        }
    } else {
        if (mMinimize) {
            configDir.assignC(L"BaseData/");
            if (!FindDirectoryUp(&configDir)) configDir.appendC(L"Data/");
        } else {
            configDir.assignC(L"Data/");
        }
        if (!FindDirectoryUp(&configDir)) configDir.appendC(L"./");
    }
    FUN_009309b0(cfgBuf, L"Config/", configDir.mpBegin, 4);
    SetDirFromID(0xa0214f, cfgBuf, 0);

    WString_s007e_7d00 userDir(L"UserData/");
    mToggleFullscreen = false;
    if (cmd->FindSwitch(L"devDirs", 0, 0, 0) != -1) mToggleFullscreen = true;
    if (cmd->FindSwitch(L"shipDirs", 0, 0, 0) != -1) mToggleFullscreen = false;
    if (cmd->FindSwitch(L"userDataDir", 0, &userDir, 0) == -1) {
        if (mToggleFullscreen) {
            userDir.assignC(L"UserData/");
            WString_s007e_7d00 tmp(kNoInit);
            WString_s007e_7d00* r = StrConcat(&tmp, &dataDir, L"../UserData/");
            if (r != &userDir) userDir.assign(r->mpBegin, r->mpEnd);
        } else {
            GetSystemPath(10, sysPath, 0);
            userDir.assignC(sysPath);
            userDir.append(mPublicDirName.mpBegin, mPublicDirName.mpEnd);
        }
    }
    SetDirFromID(0xa0214b, userDir.mpBegin, 0);
    if (mToggleFullscreen) {
        SetDirFromID(0xa02151, userDir.mpBegin, 0);
    } else {
        GetSystemPath(8, sysPath, 0);
        WString_s007e_7d00 appData(sysPath);
        appData.append(mPrivateDirName.mpBegin, mPrivateDirName.mpEnd);
        SetDirFromID(0xa02151, appData.mpBegin, 0);
    }

    WString_s007e_7d00 dbDir;
    bool bDbSwitch = cmd->FindSwitch(L"dataBaseDir", 0, &dbDir, 0) != -1;
    bool skip = false;
    if (!bDbSwitch && mToggleFullscreen && !mMinimize) {
        dbDir.appendC(L"BaseData");
        if (!FindDirectoryUp(&dbDir)) {
            if (!dbDir.empty()) {
                *dbDir.mpBegin = 0;
                dbDir.mpEnd = dbDir.mpBegin;
            }
            skip = true;
        }
    }
    if (!skip && !dbDir.empty()) {
        SetDirFromID(0x6cbed39, dbDir.mpBegin, 0);
        localeDir.assignC(GetDirFromID(0x6cbed39));
        localeDir.appendRaw(L"Locale/");
        SetDirFromID(0x6cbed3a, localeDir.mpBegin, 0);
    }

    WString_s007e_7d00 tempDir;
    GetDirOverride(0xa02151, &tempDir, 0);
    tempDir.appendRaw(L"Temp/");
    SetDirFromID(0x60ba02f, tempDir.mpBegin, 0);
    EnsureDirectoryExists(tempDir.mpBegin);
    if (cmd->FindSwitch(L"mce", 0, 0, 0) != -1) mServerCheatFlag = true;
}




// @ 0x007e8760
bool cAppSystem_s007e_7d00::LoadPlugins()
{
    WString_s007e_7d00 dir;
    if (!GetDirOverride(0x39b84d3, &dir, 0)) dir.assignC(FUN_00688cd0());
    const wchar_t* name = EntryFindFirst(dir.mpBegin, gDllMask, 0, 0);
    if (name) {
        do {
            if (_wcsnicmp(name, L"msvc", 4) != 0) {
                WString_s007e_7d00 full(dir);
                full.appendRaw(name);
                mPluginLibraries.Load(full.mpBegin, 1);
            }
        } while (EntryFindNext(name, 0));
        EntryFindFinish(name); // 0x0092e9b0
    }
    return true;
}




// @ 0x007e89c0
void RCVec::DoInsertValue(RCObj** position, RCObj* const* value)
{
    if (mpEnd != mpCapacity) {
        RCObj* const* pValue = value;
        if (value >= position && value < mpEnd) ++pValue;
        RCObj** pEnd = mpEnd;
        if (pEnd) {
            *pEnd = pEnd[-1];
            if (*pEnd) (*pEnd)->AddRef();
        }
        RCCopyBackward(position, mpEnd - 1, mpEnd);
        RCObj* nv = *pValue;
        RCObj* old = *position;
        if (nv != old) {
            if (nv) nv->AddRef();
            *position = nv;
            if (old) old->Release();
        }
        ++mpEnd;
        return;
    }
    size_t n = mpEnd - mpBegin;
    size_t newCap = n ? n * 2 : 1;
    RCObj** p = newCap ? (RCObj**)operator_new(newCap * 4, "App", 0, 0, kEastlAllocFile, 0xd1) : 0;
    size_t before = (char*)position - (char*)mpBegin;
    RCObj** newPos = (RCObj**)memcpy(p, mpBegin, before) + (before >> 2);
    if (newPos) {
        *newPos = *value;
        if (*newPos) (*newPos)->AddRef();
    }
    size_t after = (char*)mpEnd - (char*)position;
    RCObj** newEnd = (RCObj**)memcpy(newPos + 1, position, after) + (after >> 2);
    if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin);
    mpEnd = newEnd;
    mpBegin = p;
    mpCapacity = p + newCap;
}



// @ 0x007e8ba0
bool cAppSystem_s007e_8ba0::PreInit(CommandLine* cmd, int unused)
{
    FUN_006926e0((void*)__readfsdword(0x18));
    FUN_0067e050(&g_01639470);
    FUN_0067df20(cmd);
    if (cmd->FindSwitch(L"noMP", 0, 0, 0) != -1)
        FUN_007e5d90();
    FUN_0068da90();
    FUN_00c2e4e0();
    mGarbageMan = FUN_0068c520();
    FUN_0067e0a0(mGarbageMan);
    FUN_00762f00(1);
    FUN_0092a020();
    mJobManager = FUN_00690ae0();

    bool noBackground = cmd->FindSwitch(L"noBackground", 0, 0, 0) != -1;
    uint32_t mask = 0;
    if (!noBackground) {
        SYSTEM_INFO_ si = {0};
        GetSystemInfo(&si);
        int cpus = (int)si.dwNumberOfProcessors;
        int threads = cpus - 1;
        if (threads < 1) threads = 1;
        else if (threads > 3) threads = 3;
        {
            WStr jobThreads;
            if (cmd->FindSwitch(L"jobThreads", 0, &jobThreads, 0) != -1) {
                int n = wcstol(jobThreads.c_str(), 0, 10);
                if ((unsigned)n <= 20) threads = n;
            }
            bool multi = cpus > 1;
            if (!multi) g_0163939c = (uint32_t)-1;
            WStr jobPriority;
            if (cmd->FindSwitch(L"jobPriority", 0, &jobPriority, 0) != -1)
                g_0163939c = _wtol(jobPriority.c_str());
            g_0154c478 = multi;
            mask = (1u << threads) - 1;
        }
    }

    if (!mJobManager->Start(mask, FUN_007e5de0))
        return false;
    if (!noBackground)
        mJobManager->CreateThread(4, 1, -1);
    int flags = 3;
    if (mask == 0) flags = 0x80000003;
    if (noBackground) flags |= 4;
    mBaseThread = mJobManager->CreateThread(flags, 0, -1);
    FUN_0068f4c0(mJobManager);

    mMessageServer = (IServer*)new ("App", 0, 0, 0, 0) Server();
    mMessageServer->AddRef();
    mMessageServer->Configure(4, 0);
    FUN_00883870(mMessageServer);
    FUN_0067deb0(mMessageServer);

    mResourceManager = (IResMgr*)new ("App", 0, 0, 0, 0) ResourceManager(0);
    mResourceManager->AddRef();
    FUN_008de1b0(mResourceManager);
    FUN_0067dec0(mResourceManager);

    mAsyncResourceManager = (IAsyncResMgr*)new ("App", 0, 0, 0, 0) AsyncResourceManager();
    mAsyncResourceManager->AddRef();
    FUN_008d5d10(mAsyncResourceManager);
    FUN_0067e090(mAsyncResourceManager);

    IPlainRes* res = FUN_007f18e0();
    res->AddRef();
    mResourceManager->RegisterFactory(1, res, 0);

    wchar_t path[256];
    int len = FUN_00932370(path);
    if (len >= 0 && len + 9 < 256) {
        const wchar_t* src = L"demo.txt";
        wchar_t* dst = path + len;
        wchar_t c;
        do {
            c = *src++;
            *dst++ = c;
        } while (c);
        if (FUN_00931fa0(path))
            mDemo = true;
    }
    if (cmd->FindSwitch(L"demo", 0, 0, 0) != -1)
        mDemo = true;
    if (cmd->FindSwitch(L"noDemo", 0, 0, 0) != -1)
        mDemo = false;
    if (mDemo)
        mDev = false;
    if (cmd->FindSwitch(L"dev", 0, 0, 0) != -1)
        mDev = true;
    if (cmd->FindSwitch(L"noDev", 0, 0, 0) != -1)
        mDev = false;

    FUN_00761190();
    FUN_006adc90(mResourceManager);
    AssignRef(mApp, FUN_007d8dc0());
    FUN_0067df00(mApp);
    SetupDirectories(cmd);
    AssignRef(mCheatManager, FUN_0067fb50());
    mCheatManager->vc();
    FUN_0067e030(mCheatManager);
    FUN_00c2e4e0();
    FUN_007c79e0();
    FUN_007e7b50();

    if (!FUN_009322b0(FUN_00688cb0())) {
        FUN_006baff0("Could not find the Data directory, we cannot run.", 0x3ec, 2);
        return false;
    }

    IPluginLibs* libs = (IPluginLibs*)&mPluginLibraries;
    if (libs->Enumerate(FUN_007e6100, 0))
        FUN_00936410(libs);
    FUN_0084ebc0();
    FUN_0084eba0();
    FUN_0084dc30();
    FUN_0084dc10();
    FUN_0084dc70();
    FUN_0084dc50();
    FUN_0084bc60();
    FUN_0084bc40();
    FUN_00a6c750();
    if (cmd->FindSwitch(L"writeableData", 0, 0, 0) != -1)
        gAppProperties_s007e_8ba0->SetBoolProperty(0xce1c9372, true);
    mResourceManager->RegisterExtension(0xb1b104, L"prop");
    mResourceManager->RegisterExtension(0x24a0e52, L"txt");

    WStr ddf;
    if (mDdfDirBegin != mDdfDirEnd)
        WStr_Format(&ddf, L"DDFLists/%ls", mDdfDirBegin);
    const wchar_t* dir = FUN_006886b0(0x6cbed39);
    if (dir)
        FUN_00687590(mResourceManager, dir, -1000);
    WStr locale;
    WStr unusedTemp;   // constructed in the original but never used
    bool ok = FUN_00688830(0x3d1fee6, &locale, 0);
    const wchar_t* ddfName = ddf.empty() ? 0 : ddf.c_str();
    if (ok)
        FUN_00687610(FUN_00688cb0(), locale.c_str(), ddfName, 0);
    else
        FUN_00687610(FUN_00688cb0(), 0, ddfName, 0);
    return true;
}



// @ 0x007e9300
bool cAppSystem_s007e_8ba0::InitPlugins(void* cmd)
{
    CommandLine* cl = (CommandLine*)cmd;
    if (cl->FindSwitch(L"noPlugins", 0, 0, 0) == -1) {
        if (cl->FindSwitch(L"safe", 0, 0, 0) == -1) {
            return LoadPlugins();
        }
    }
    return false;
}



// @ 0x007e93d0
void cAppSystem_s007e_8ba0::SetUserDirNames(wchar_t* publicDir, wchar_t* privateDir)
{
    const wchar_t* e = publicDir;
    while (*e) ++e;
    int n = (int)(e - publicDir);
    mPublicDirName.assign(publicDir, publicDir + n);
    mPublicDirName.push_back(L'\\');
    e = privateDir;
    while (*e) ++e;
    n = (int)(e - privateDir);
    mPrivateDirName.assign(privateDir, privateDir + n);
    mPrivateDirName.push_back(L'\\');
}



// @ 0x007e9450
void cAppSystemShutdown(void* self)
{
    // 1453-byte shutdown sequence not reconstructed; see partial.txt.
    (void)self;
}


// @ 0x007e9a00
int cAppSystemLoadEffectCollections(void* self)
{
    // Effect-collection loading not reconstructed; see partial.txt.
    (void)self;
    return 0;
}


// @ 0x007e9d00
void cAppSystem::OpenURL(const wchar_t* url)
{
    {
        WString s(url);
        mURLsToOpen.push_back(s);
    }
    if (mLockCount)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}


// @ 0x007e9db0
void cAppSystemUpdate(void* self)
{
    // Main per-frame update not reconstructed; see partial.txt.
    (void)self;
}


// @ 0x007ea2f0
void FUN_007ea2f0(void* self)
{ (void)self; }

// @ 0x007ea440
void FUN_007ea440(void* self)
{ (void)self; }

// @ 0x007eaa10
int cAppSystemInitGraphics(void* self)
{ (void)self; return 0; }
