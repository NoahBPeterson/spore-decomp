// src/game/SPEngine/SPAppSystem.cpp -- migrated from slice(s) s011cd0f0, s011c5230, s007ea440, s007e9a00, s007e8ba0, s007e7d00, s007e70b0, s007e6210, s007e5220 by tools/migrate/rewrite.py
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
extern bool gCanvasHighFlag;                               // 0x0153fb34
extern unsigned int gPrefsVersion;                         // 0x0141390c
extern char gSSLGlobal[];                                  // 0x0153fb2c
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
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PADV CAT_(vpad, __COUNTER__)
#define P1_s007e_6210 virtual void PADV();
#define P2 P1_s007e_6210 P1_s007e_6210
#define P4_s007e_6210 P2 P2
#define P8 P4_s007e_6210 P4_s007e_6210
#define P16 P8 P8
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
namespace AppInit {
struct CommandLine_s007e_6210 {
    int FindSwitch(const wchar_t* name, int a, int b, int c);                   // 0x0092b300 (ret 0x10)
};
}
namespace AppInit {
struct cLocaleManager {
    P1_s007e_6210 virtual void AddRef(); virtual void Release();
    char pad4[0x6c];
    cLocaleManager();                                                           // 0x00696420
    void Init(CommandLine_s007e_6210* cmd, const wchar_t* dir);                            // 0x006964c0
};
}
namespace AppInit {
struct NameMap {                                                                // id generator, 0x40 bytes
    char pad[0x40];
    NameMap();                                                                  // 0x0068db70
};
}
namespace AppInit {
struct cCommandServer {
    P4_s007e_6210 virtual void Start();                                                    // +0x10
};
}
namespace AppInit {
struct cTelemetry {
    P1_s007e_6210 virtual void Method1();                                                  // +4
    uint32_t pad4;
    struct RefSub { virtual void AddRef(); virtual void Release(); } mRef;      // +8
    char padc[0x40 - 0xc];
    cTelemetry();                                                               // 0x007ec0a0
    void Configure(bool dump);                                                  // 0x007eaf20 (ret 4)
    void AddRef() { mRef.AddRef(); }
    void Release() { mRef.Release(); }
};
}
namespace AppInit {
struct cPropertyManager {
    virtual void AddRef(); virtual void Release();
    virtual void SetFlag(bool b);                                               // +8
    virtual void Start();                                                       // +0xc
    P4_s007e_6210 P2 P1_s007e_6210
    virtual bool GetPropertyList(uint32_t id, uint32_t group, void* out);       // +0x2c
};
}
namespace AppInit {
struct Property {
    char pad[0x12];
    short mType;                                                                // +0x12
    uint32_t* GetUInt();                                                        // 0x0041ea00
    bool* GetBool();                                                            // 0x0041e920
};
}
namespace AppInit {
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;                                                            // +0x10
    uint16_t mType;                                                             // +0x12
    uint16_t mSize;                                                             // +0x14
    uint16_t mExtra;                                                            // +0x16
    Variant() { mFlags = 0; mExtra = 0; }
    ~Variant() { if (mFlags & 4) Destruct(0); }
    void SetInt(const unsigned int* v);                                         // 0x00427fd0
    void Destruct(int a);                                                       // 0x0093db80
};
}
namespace AppInit {
struct ResourceKey { uint32_t a, b, c; };
}
namespace AppInit {
struct cPropertyList {                                                          // 0x38 bytes
    virtual void AddRef(); virtual void Release();
    P2 P1_s007e_6210
    virtual void SetProperty(uint32_t id, Variant* v);                          // +0x14
    virtual void RemoveProperty(uint32_t id);                                   // +0x18
    P2
    virtual bool GetProperty(uint32_t id, Property** out);                      // +0x24
    P1_s007e_6210
    virtual void CopyFrom(cPropertyList* other);                                // +0x2c
    uint32_t pad4;
    ResourceKey mKey;                                                           // +8
    char pad14[0x38 - 0x14];
    cPropertyList();                                                            // 0x006a1c40
};
}
namespace AppInit {
struct PropListRef {                                                            // EA::AutoRefCount<cPropertyList>
    cPropertyList* mpObject;
    PropListRef() : mpObject(0) {}
    ~PropListRef() { if (mpObject) mpObject->Release(); }
};
}
namespace AppInit {
struct cResourceHolder {                                                        // release at +8
    P1_s007e_6210 virtual void AddRef(); virtual void Release();
    P4_s007e_6210 P2
    virtual void Close();                                                       // +0x24
};
}
namespace AppInit {
struct ResHolderRef {
    cResourceHolder* mpObject;
    ResHolderRef() : mpObject(0) {}
    ~ResHolderRef() { if (mpObject) mpObject->Release(); }
};
}
namespace AppInit {
struct cResourceReader {                                                        // returned by resmgr+0x48
    P4_s007e_6210 P2 P1_s007e_6210
    virtual void Read(cResourceHolder* src, void* outRef, int a, uint32_t typeID);   // +0x1c
};
}
namespace AppInit {
struct cResourceManager {
    P16 P2
    virtual cResourceReader* GetReader(uint32_t typeID, int a);                 // +0x48
};
}
namespace AppInit {
struct cSaveArea {
    P8 P4_s007e_6210 P1_s007e_6210
    virtual bool Open(const ResourceKey* key, ResHolderRef* out, int a, int b, int c, int d);   // +0x34
};
}
namespace AppInit {
struct cPackManager {
    char pad[0x14];
    cPackManager();                                                             // 0x00b7d170
    void Init();                                                                // 0x007db650
};
}
namespace AppInit {
struct InputMan {
    P1_s007e_6210 virtual void AddRef();
    char pad[0x37c - 8];
    InputMan();                                                                 // 0x008d32f0
};
}
namespace AppInit {
struct AppCanvas {
    P1_s007e_6210 virtual void AddRef();
    P4_s007e_6210 P2
    virtual void SetX(int v);                                                   // +0x20
    P1_s007e_6210
    virtual void SetFlags(uint32_t flags);                                      // +0x28
    P8 P4_s007e_6210 P2 P1_s007e_6210
    virtual void SetMessageServer(void* server);                                // +0x68
    P8 P2
    virtual void* GetDropTarget();                                              // +0x94
    char pad[0x98 - 4];
    AppCanvas();                                                                // 0x00849a40
};
}
namespace AppInit {
struct cGraphicsSystem {
    virtual void AddRef(); virtual void Release();
    virtual bool Start();                                                       // +8
};
}
namespace AppInit {
struct cAppStateManager {
    virtual void AddRef(); virtual void Release();
    P2
    virtual void Init(int a);                                                   // +0x10
};
}
namespace AppInit {
struct cConfigManager {
    virtual void AddRef(); virtual void Release();
    P1_s007e_6210
    virtual void Setup(CommandLine_s007e_6210* cmd, bool needDefaults);                    // +0xc
    P2 P1_s007e_6210
    virtual void SetCurrent(uint32_t id, int a);                                // +0x1c
};
}
namespace AppInit {
struct SocketsManager { char pad[0x1cc]; SocketsManager(); };                   // 0x0094c260
}
namespace AppInit {
struct SocketsGlobal { P1_s007e_6210 virtual void Start(); };                              // +4
}
namespace AppInit {
struct SSLManager {
    char pad[0x190];
    SSLManager(void* allocator);                                                // 0x0094fc40
    void Init();                                                                // 0x0094fed0
    void SetLoading(const void* a, int b);                                      // 0x0094f080 (ret 8)
    void SetCAFile(const wchar_t* path);                                        // 0x0094f0b0 (ret 4)
};
}
namespace AppInit {
struct AppProps {
    virtual void Start();                                                       // +0
    void SetBoolProperty(uint32_t id, bool v);                                  // 0x006a17e0
};
}
namespace AppInit {
struct SSLFileSystemGlobal { const wchar_t* GetCAFileName(); };                 // 0x007c78a0
}
void __cdecl FUN_0067e080(void*);   // register id generator
void __cdecl FUN_0067e060(void*);   // register locale manager
void* __cdecl FUN_0068c0d0();       // creates the command server
void __cdecl FUN_006895c0(void*);
void __cdecl FUN_0067e0b0(void*);   // register telemetry
void __cdecl FUN_006bae50();
void* __cdecl FUN_006ab650();       // creates the property manager
void __cdecl FUN_0067e040(void*);
void __cdecl InitAppEffects();      // 0x007cec80
void __cdecl FUN_0094cd50(void*);
AppInit::SocketsGlobal* __cdecl FUN_0094cd40();
void __cdecl FUN_0094f0e0(void*);
AppInit::SSLManager* __cdecl GetSSLManager();                       // 0x0094f0d0
void* __cdecl GetDefaultAllocator();                       // 0x00925cb0
void __cdecl FUN_006b1d40(bool);
void __cdecl CreateDefaultSaveAreas();                     // 0x006b37d0
AppInit::cSaveArea* __cdecl GetSaveArea(uint32_t id);               // 0x006b1f90
void __cdecl FUN_006b2400(uint32_t id);
void __cdecl SaveNamedResource(AppInit::cPropertyList* prefs, const wchar_t* name, AppInit::cResourceHolder* area);   // 0x006b4010
void __cdecl FUN_0067df10(void*);
void __cdecl FUN_0067e0d0(void*);
void __cdecl FUN_008d3120(void*);
void __cdecl FUN_0067ded0(void*);
void __cdecl FUN_0067dee0(void*);
void __cdecl FUN_006bbb60(void* dropTarget, void* slot);
AppInit::cGraphicsSystem* __cdecl FUN_007a67e0();
void __cdecl FUN_006bb1c0(const char* msg, int code, int a, int b);
void __cdecl FUN_006894d0();
void __cdecl FUN_00689510(int);
AppInit::cAppStateManager* __cdecl FUN_007e57c0();
void __cdecl FUN_0067df30(void*);
AppInit::cConfigManager* __cdecl FUN_007cc390();
void __cdecl FUN_0067df40(void*);
void __cdecl FUN_006b4730();
void __cdecl FUN_0067def0(void*);
extern AppInit::SSLFileSystemGlobal gSSLFileSystem_s007e_6210;                 // 0x0153fb2c
#define MF(T, off) (*(T*)((char*)this + (off)))
template <class T> __forceinline void SetRef(T*& slot, T* p)
{
    T* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}
struct cAppSystemEx : cAppSystem {
    bool Init(AppInit::CommandLine_s007e_6210* cmd);
};
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

// ---- items of slice s011c5230 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
extern const u32 g_des_sp[8][64];      // 0x014f1aa8: 8 precomputed S-box/permutation tables
#define ROR32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
struct DES_key_schedule {
    u32 ks[32];
};
#define DES_ROUND(dst, src, k)                                                 \
    {                                                                          \
        u32 u = (src) ^ (k)[0];                                                \
        u32 t = ROR32((src) ^ (k)[1], 4);                                      \
        (dst) ^= g_des_sp[0][(u >> 2) & 0x3f] ^ g_des_sp[2][(u >> 10) & 0x3f] ^ \
                 g_des_sp[4][(u >> 18) & 0x3f] ^ g_des_sp[6][(u >> 26) & 0x3f] ^ \
                 g_des_sp[1][(t >> 2) & 0x3f] ^ g_des_sp[3][(t >> 10) & 0x3f] ^ \
                 g_des_sp[5][(t >> 18) & 0x3f] ^ g_des_sp[7][(t >> 26) & 0x3f]; \
    }
struct BIGNUM {
    u32* d;         // +0x00
    int top;        // +0x04
    int dmax;       // +0x08
    int neg;        // +0x0c
    int flags;      // +0x10
};
typedef int BN_CTX;
struct BN_RECP_CTX {
    BIGNUM N;       // +0x00
    BIGNUM Nr;      // +0x14
    int num_bits;   // +0x28
    int shift;      // +0x2c
    int flags;      // +0x30
};
void BN_CTX_start(BN_CTX* ctx);
BIGNUM* BN_CTX_get(BN_CTX* ctx);
void BN_CTX_end(BN_CTX* ctx);
int BN_ucmp(const BIGNUM* a, const BIGNUM* b);
int BN_set_word(BIGNUM* a, u32 w);
int BN_copy(BIGNUM* a, const BIGNUM* b);
int BN_num_bits(const BIGNUM* a);
int BN_reciprocal(BIGNUM* r, BIGNUM* d, int len, BN_CTX* ctx);
int BN_rshift(BIGNUM* r, const BIGNUM* a, int n);
int BN_mul(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, BN_CTX* ctx);
int BN_usub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
int BN_add_word(BIGNUM* a, u32 w);
void ERR_put_error(int lib, int func, int reason, const char* file, int line);
struct UI_METHOD;
struct UI {
    UI_METHOD* meth;    // +0x00
    void* strings;      // +0x04
};
struct UI_STRING {
    int type;           // +0x00
    UI* ui;             // +0x04
    const char* prompt; // +0x08
    int min;            // +0x0c
    int max;            // +0x10
    int result_buf;     // +0x14
    int extra;          // +0x18
    int freeable;       // +0x1c
};
void* CRYPTO_malloc(int num, const char* file, int line);
int sk_push(void* st, void* p);
void* sk_new_null();
void free_string(void* str);
// ---- items of slice s011c5230 end

// ---- items of slice s011cd0f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char* s_OpenSSL_default_name;
extern const void* s_openssl_ui_methods;
extern const char* s_WIN32_name;
extern const void* s_win32_ui_methods;
extern "C" int   strcmp(const char* a, const char* b);
extern "C" const void* BIO_s_file(void);
extern "C" void       ERR_clear_error(void);
extern "C" void       EVP_MD_CTX_init(void* ctx);
extern "C" int        EVP_MD_CTX_cleanup(void* ctx);
extern "C" const char* OBJ_nid2sn(int nid);
extern "C" int        EVP_DigestUpdate(void* ctx, const void* d, unsigned long cnt);
extern "C" void       OPENSSL_cleanse(void* ptr, unsigned long len);
extern "C" void       CRYPTO_free(void* ptr);
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
struct BIGNUM;
struct BN_CTX_s011c_d0f0;
struct BUF_MEM
{
    int   length;
    char* data;
    int   max;
};
struct ASN1_ITEM;
struct ASN1_OBJECT;
struct ASN1_OCTET_STRING
{
    int   length;
    uchar* data;
};
struct EVP_MD;
struct ENGINE;
struct BIO;
struct UI_METHOD_s011c_d0f0;
struct X509_EXT_INFO
{
    int m_cert_info;      // 0x00
    int m_crl_info;       // 0x04
    int m_issuer;         // 0x08
    int m_ref;            // 0x0c
    int m_pad[4];         // 0x10
    int m_extensions;     // 0x20
    int m_aux;            // 0x24
    int m_ex_flags;       // 0x28
};
struct UI_METHOD_s011c_d0f0
{
    const char* m_name;
    const void* m_methods;
    int         m_data;
};
extern "C" BIO*  BIO_new(const void* type);
unsigned pem_parse_block(uchar* in, int* consumed, int* lens, uchar* extra, int avail);
int      pem_finish(X509_EXT_INFO* info, BIO* bio, X509_EXT_INFO** out, uchar* payload,
                    int payloadLen, const char* name, const char* nameOut, int nameLen,
                    const char* header);
extern "C" int        ERR_put_error_s011c_d0f0(int lib, int func, int reason, const char* file, int line);
extern "C" ulong      ERR_peek_error(void);
extern "C" BN_CTX_s011c_d0f0*    BN_CTX_new(void);
extern "C" void       BN_CTX_free(BN_CTX_s011c_d0f0*);
extern "C" int        BN_sqr(BIGNUM* r, const BIGNUM* a, BN_CTX_s011c_d0f0* ctx);
extern "C" int        OBJ_obj2nid(const ASN1_OBJECT* o);
extern "C" const EVP_MD* EVP_get_digestbyname(const char* name);
extern "C" int        EVP_DigestInit_ex(void* ctx, const EVP_MD* type, ENGINE* impl);
extern "C" int        EVP_DigestFinal_ex(void* ctx, uchar* md, uint* s);
extern "C" int        ASN1_item_i2d(void* val, uchar** out, const ASN1_ITEM* it);
extern "C" BUF_MEM*   BUF_MEM_new(void);
extern "C" int        BUF_MEM_grow(BUF_MEM* str, unsigned long len);
extern "C" void       BUF_MEM_free(BUF_MEM* a);
extern "C" int        BIO_read(BIO* b, void* data, int len);
struct BN_MOD_METHOD
{
    int (*bn_mod)(BIGNUM* r, const BIGNUM* a, const BIGNUM* m, BN_CTX_s011c_d0f0* ctx);
};
// ---- items of slice s011cd0f0 end

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

// @ 0x007e67a0
bool cAppSystemEx::Init(AppInit::CommandLine_s007e_6210* cmd)
{
    AppInit::NameMap* idgen = new("App", 0, 0, 0, 0) AppInit::NameMap();
    MF(AppInit::NameMap*, 0x28) = idgen;
    FUN_0067e080(idgen);

    AppInit::cLocaleManager* locale = new("App", 0, 0, 0, 0) AppInit::cLocaleManager();
    SetRef(MF(AppInit::cLocaleManager*, 0x24), locale);
    MF(AppInit::cLocaleManager*, 0x24)->Init(cmd, (MF(wchar_t*, 0x128) == MF(wchar_t*, 0x12c)) ? 0 : MF(wchar_t*, 0x128));
    FUN_0067e060(MF(AppInit::cLocaleManager*, 0x24));

    MF(AppInit::cCommandServer*, 0x38) = (AppInit::cCommandServer*)FUN_0068c0d0();
    FUN_006895c0(MF(AppInit::cCommandServer*, 0x38));
    MF(AppInit::cCommandServer*, 0x38)->Start();

    bool dumpTelemetry = cmd->FindSwitch(L"dumptelemetry", 0, 0, 0) != -1;
    AppInit::cTelemetry* tele = new("App", 0, 0, 0, 0) AppInit::cTelemetry();
    SetRef(MF(AppInit::cTelemetry*, 0x48), tele);
    MF(AppInit::cTelemetry*, 0x48)->Method1();
    FUN_0067e0b0(MF(AppInit::cTelemetry*, 0x48));
    MF(AppInit::cTelemetry*, 0x48)->Configure(dumpTelemetry);

    ((AppInit::AppProps*)gAppProperties)->Start();
    FUN_006bae50();
    SetRef(MF(AppInit::cPropertyManager*, 0x2c), (AppInit::cPropertyManager*)FUN_006ab650());
    FUN_0067e040(MF(AppInit::cPropertyManager*, 0x2c));
    MF(AppInit::cPropertyManager*, 0x2c)->SetFlag(MF(bool, 0x159));
    MF(AppInit::cPropertyManager*, 0x2c)->Start();
    InitAppEffects();

    FUN_0094cd50(new("App", 0, 0, 0, 0) AppInit::SocketsManager());
    FUN_0094cd40()->Start();

    AppInit::SSLManager* ssl = new("App", 0, 0, 0, 0) AppInit::SSLManager(GetDefaultAllocator());
    FUN_0094f0e0(ssl);
    GetSSLManager()->SetLoading(gSSLGlobal, 1);
    GetSSLManager()->Init();
    GetSSLManager()->SetCAFile(gSSLFileSystem_s007e_6210.GetCAFileName());

    FUN_006b1d40(MF(bool, 0x159) == false);
    CreateDefaultSaveAreas();
    AppInit::cSaveArea* area = GetSaveArea(0x11ac192);
    AppInit::ResourceKey key;
    key.a = 0xd9bd3ca1;
    key.b = 0xb1b104;
    key.c = 0x11ac192;
    AppInit::cResourceReader* reader = MF(AppInit::cResourceManager*, 0x1c)->GetReader(0xb1b104, -1);

    bool safe = cmd->FindSwitch(L"safe", 0, 0, 0) != -1;
    if (!safe && area && reader) {
        AppInit::ResHolderRef holder;
        if (area->Open(&key, &holder, 1, 3, 1, 0)) {
            AppInit::cPropertyList*& prefsSlot = MF(AppInit::cPropertyList*, 0xcc);
            if (prefsSlot) {
                prefsSlot = 0;
            }
            reader->Read(holder.mpObject, &MF(AppInit::cPropertyList*, 0xcc), 0, key.b);
            holder.mpObject->Close();
        }
    }

    AppInit::cPropertyList* prefs = MF(AppInit::cPropertyList*, 0xcc);
    if (prefs) {
        AppInit::Property* prop;
        if (!prefs->GetProperty(0x4754439, &prop) || prop->mType != 10 || *prop->GetUInt() != 9) {
            AppInit::cPropertyList* old = MF(AppInit::cPropertyList*, 0xcc);
            if (old) {
                MF(AppInit::cPropertyList*, 0xcc) = 0;
                old->Release();
            }
        }
    }
    bool needDefaults = MF(AppInit::cPropertyList*, 0xcc) == 0;

    if (MF(AppInit::cPropertyList*, 0xcc)) {
        AppInit::Property* prop;
        if (!MF(AppInit::cPropertyList*, 0xcc)->GetProperty(0x43f2ae3, &prop) || prop->mType != 1 || !*prop->GetBool())
            goto afterPrefs;
        FUN_006b2400(0x11ac1ac);
        MF(AppInit::cPropertyList*, 0xcc)->RemoveProperty(0x43f2ae3);
    } else {
        AppInit::cPropertyList* fresh = new("App", 0, 0, 0, 0) AppInit::cPropertyList();
        SetRef(MF(AppInit::cPropertyList*, 0xcc), fresh);
        AppInit::cPropertyList* cur = MF(AppInit::cPropertyList*, 0xcc);
        cur->mKey.a = key.a;
        cur->mKey.b = key.b;
        cur->mKey.c = key.c;
        AppInit::PropListRef defaults;
        if (MF(AppInit::cPropertyManager*, 0x2c)->GetPropertyList(0x4483e856, 0, &defaults.mpObject))
            MF(AppInit::cPropertyList*, 0xcc)->CopyFrom(defaults.mpObject);
        else
            FUN_006bb1c0("Could not find the default preferences.\n\nThe data directory is missing or corrupt.", 0x3ec, 0, 0);
        AppInit::Variant v;
        v.SetInt(&gPrefsVersion);
        MF(AppInit::cPropertyList*, 0xcc)->SetProperty(0x4754439, &v);
    }
    if (area)
        SaveNamedResource(MF(AppInit::cPropertyList*, 0xcc), L"Preferences", (AppInit::cResourceHolder*)area);
afterPrefs:
    FUN_0067df10(MF(AppInit::cPropertyList*, 0xcc));

    AppInit::cPackManager* packs = new("App", 0, 0, 0, 0) AppInit::cPackManager();
    MF(AppInit::cPackManager*, 0x4c) = packs;
    packs->Init();
    FUN_0067e0d0(MF(AppInit::cPackManager*, 0x4c));

    AppInit::InputMan* input = new("App", 0, 0, 0, 0) AppInit::InputMan();
    MF(AppInit::InputMan*, 0x18) = input;
    input->AddRef();
    FUN_008d3120(MF(AppInit::InputMan*, 0x18));
    FUN_0067ded0(MF(AppInit::InputMan*, 0x18));

    AppInit::AppCanvas* canvas = new("App", 0, 0, 0, 0) AppInit::AppCanvas();
    MF(AppInit::AppCanvas*, 0x10) = canvas;
    canvas->SetMessageServer(MF(void*, 0x14));
    MF(AppInit::AppCanvas*, 0x10)->AddRef();
    uint32_t flags = 0x2a;
    if (gCanvasHighFlag)
        flags = 0x6a;
    if (cmd->FindSwitch(L"flock", 0, 0, 0) != -1)
        flags |= 0x80;
    MF(AppInit::AppCanvas*, 0x10)->SetFlags(flags);
    MF(AppInit::AppCanvas*, 0x10)->SetX(0xe);
    FUN_0067dee0(MF(AppInit::AppCanvas*, 0x10));
    FUN_006bbb60(MF(AppInit::AppCanvas*, 0x10)->GetDropTarget(), &MF(void*, 0x54));

    SetRef(MF(AppInit::cGraphicsSystem*, 0x5c), FUN_007a67e0());
    if (!MF(AppInit::cGraphicsSystem*, 0x5c)->Start()) {
        FUN_006bb1c0("Could not start the renderer.\nPlease ensure your display is set to 32 bits.", 0x3e9, 2, 0);
        return false;
    }

    MF(float, 0xb8) = 0.0f;
    MF(float, 0xbc) = 0.0f;
    FUN_006894d0();
    FUN_00689510(0);

    SetRef(MF(AppInit::cAppStateManager*, 0x34), FUN_007e57c0());
    if (MF(AppInit::cAppStateManager*, 0x34)) {
        MF(AppInit::cAppStateManager*, 0x34)->Init(0);
        FUN_0067df30(MF(AppInit::cAppStateManager*, 0x34));
    }

    SetRef(MF(AppInit::cConfigManager*, 0x3c), FUN_007cc390());
    MF(AppInit::cConfigManager*, 0x3c)->Setup(cmd, needDefaults);
    FUN_0067df40(MF(AppInit::cConfigManager*, 0x3c));
    MF(AppInit::cConfigManager*, 0x3c)->SetCurrent(0x9a06678c, 0);

    if (cmd->FindSwitch(L"vSync", 0, 0, 0) != -1)
        ((AppInit::AppProps*)gAppProperties)->SetBoolProperty(0xd77e97, true);
    if (cmd->FindSwitch(L"noVSync", 0, 0, 0) != -1)
        ((AppInit::AppProps*)gAppProperties)->SetBoolProperty(0xd77e97, false);
    FUN_006b4730();
    FUN_0067def0(this);
    return true;
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

// @ 0x011c5230
void des_encrypt1(u32* data, DES_key_schedule* ks, int enc)
{
    u32 l = (data[0] << 3) | (data[0] >> 29);
    u32 r = (data[1] << 3) | (data[1] >> 29);
    int i;

    if (enc)
    {
        const u32* s = &ks->ks[0];
        for (i = 0; i < 16; i += 4)
        {
            DES_ROUND(r, l, s);
            DES_ROUND(l, r, s + 2);
            DES_ROUND(r, l, s + 4);
            DES_ROUND(l, r, s + 6);
            s += 8;
        }

    }
    else
    {
        // the reverse schedule is consumed from ks[30] downwards
        const u32* s = &ks->ks[28];
        for (i = 0; i < 16; i += 4)
        {
            DES_ROUND(r, l, s + 2);
            DES_ROUND(l, r, s);
            DES_ROUND(r, l, s - 2);
            DES_ROUND(l, r, s - 4);
            s -= 8;
        }

    }

    data[0] = ROR32(r, 3);
    data[1] = ROR32(l, 3);
}

// @ 0x011c6c40
void des_set_key_unchecked(const u8* key, u32* schedule)
{
    static const u8 shifts2[16] =
        { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 };

    // The key is read big-endian.
    u32 c = ((u32)key[0] << 24) | ((u32)key[1] << 16) | ((u32)key[2] << 8) | key[3];
    u32 d = ((u32)key[4] << 24) | ((u32)key[5] << 16) | ((u32)key[6] << 8) | key[7];

    // PC1, done with the usual 60 simple operations (the parity bits drop out).
    u32 t;
    t = ((d >> 4) ^ c) & 0x0f0f0f0f; c ^= t; d ^= t << 4;
    t = ((c << 18) ^ c) & 0xcccc0000; c ^= t ^ (t >> 18);
    t = ((d << 18) ^ d) & 0xcccc0000; d ^= t ^ (t >> 18);
    t = ((d >> 1) ^ c) & 0x55555555; c ^= t; d ^= t << 1;
    t = ((c >> 8) ^ d) & 0x00ff00ff; d ^= t; c ^= t << 8;
    t = ((d >> 1) ^ c) & 0x55555555; c ^= t; d ^= t << 1;

    d = ((d & 0x000000ff) << 16) | (d & 0x0000ff00) |
        ((d & 0x00ff0000) >> 16) | ((c & 0xf0000000) >> 4);
    c &= 0x0fffffff;

    for (int i = 0; i < 16; i++)
    {
        if (shifts2[i])
        {
            c = (c >> 2) | (c << 26);
            d = (d >> 2) | (d << 26);
        }
        else
        {
            c = (c >> 1) | (c << 27);
            d = (d >> 1) | (d << 27);
        }
        c &= 0x0fffffff;
        d &= 0x0fffffff;

        // PC2: the 48 selected bits are packed into the two round-key words so
        // that the round function finds them at bits 2..7, 10..15, 18..23 and
        // 26..31 of (R ^ key) and of ROTATE(R ^ key, 4) respectively.
        static const u8 pc2[48] = {
            14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
            26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
            51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
        };
        u64 cd = (((u64)c) << 28) | d;
        u32 out = 0;
        for (int j = 0; j < 48; j++)
            out = (out << 1) | (u32)((cd >> (56 - pc2[j])) & 1);

        u32 k0 = 0;
        u32 k1 = 0;
        for (int g = 0; g < 4; g++)
        {
            u32 six = (out >> (42 - 6 * g)) & 0x3f;    // groups 0..3 -> first word
            u32 top = (out >> (18 - 6 * g)) & 0x3f;    // groups 4..7 -> second word
            k0 |= six << (2 + 8 * g);
            k1 |= top << (6 + 8 * g);
        }
        // The last group wraps around the right-rotation by four.
        u32 last = out & 0x3f;
        k1 |= ((last & 3) << 30) | ((last >> 2) & 0xf);
        schedule[0] = k0;
        schedule[1] = k1;
        schedule += 2;
    }
}

// @ 0x011c85a0
int BN_div_recp(BIGNUM* dv, BIGNUM* rem, const BIGNUM* m, BN_RECP_CTX* recp, BN_CTX* ctx)
{
    BIGNUM* a;
    BIGNUM* b;
    int i, j;
    int ret = 0;

    BN_CTX_start(ctx);
    a = BN_CTX_get(ctx);
    b = BN_CTX_get(ctx);
    if (dv == 0)
        dv = BN_CTX_get(ctx);
    if (rem == 0)
        rem = BN_CTX_get(ctx);
    if (a == 0 || b == 0 || dv == 0 || rem == 0)
        goto end;

    if (BN_ucmp(m, &recp->N) < 0)
    {
        BN_set_word(dv, 0);
        if (!BN_copy(rem, m))
            goto end;
        BN_CTX_end(ctx);
        return 1;
    }

    i = BN_num_bits(m);
    j = recp->num_bits * 2;
    if (i < j)
        i = j;
    if (i != recp->shift)
        recp->shift = BN_reciprocal(&recp->Nr, &recp->N, i, ctx);
    if (recp->shift == -1)
        goto end;

    if (!BN_rshift(a, m, recp->num_bits))
        goto end;
    if (!BN_mul(b, a, &recp->Nr, ctx))
        goto end;
    if (!BN_rshift(dv, b, i - recp->num_bits))
        goto end;
    dv->neg = 0;

    if (!BN_mul(b, &recp->N, dv, ctx))
        goto end;
    if (!BN_usub(rem, m, b))
        goto end;
    rem->neg = 0;

    i = 0;
    while (BN_ucmp(rem, &recp->N) >= 0)
    {
        if (i > 2)
        {
            ERR_put_error(3, 0x82, 0x65, 0, 0);
            goto end;
        }
        if (!BN_usub(rem, rem, &recp->N))
            goto end;
        if (!BN_add_word(dv, 1))
            goto end;
        i++;
    }

    rem->neg = (rem->top == 0) ? 0 : m->neg;
    ret = 1;
    dv->neg = m->neg ^ recp->N.neg;

end:
    BN_CTX_end(ctx);
    return ret;
}

// @ 0x011c88e0
UI_STRING* general_allocate_prompt(UI* ui, const char* prompt, int prompt_freeable, int type, int result_buf, int min, int max)
{
    if (ui == 0)
    {
        ERR_put_error(0x28, 0x6d, 0x43, 0, 0);
        return 0;
    }
    if ((type == 1 || type == 2 || type == 3) && min == 0)
    {
        ERR_put_error(0x28, 0x6d, 0x69, 0, 0);
        return 0;
    }

    UI_STRING* str = (UI_STRING*)CRYPTO_malloc(0x20, ".\\crypto\\ui\\ui_lib.c", 0x99);
    if (str != 0)
    {
        str->ui = ui;
        str->prompt = prompt;
        str->type = type;
        str->min = min;
        str->freeable = (prompt_freeable != 0);
    }
    return str;
}

// @ 0x011c8960
int general_allocate_string(UI* ui, const char* prompt, int prompt_freeable, int type, int result_buf, int min, int max)
{
    UI_STRING* str = general_allocate_prompt(ui, prompt, prompt_freeable, type, result_buf, min, max);
    if (str == 0)
        return -1;

    if (ui->strings == 0)
    {
        ui->strings = sk_new_null();
        if (ui->strings == 0)
        {
            free_string(str);
            return -1;
        }
    }

    str->max = result_buf;
    str->result_buf = min;
    str->extra = max;

    int r = sk_push(ui->strings, str);
    if (r < 1)
        return r - 1;
    return r;
}

// @ 0x011c89e0
int UI_add_input_string(UI* ui, const char* prompt, int flags, int min, int max)
{
    return general_allocate_string(ui, prompt, flags, 1, min, max, 0);
}

// @ 0x011c8a10
int UI_add_verify_string(UI* ui, const char* prompt, int flags, int min, int max, int check)
{
    return general_allocate_string(ui, prompt, flags, 2, min, max, check);
}

// @ 0x011cd0f0
int BN_mod_sqr(BN_MOD_METHOD* method, BIGNUM* r, const BIGNUM* a, BN_CTX_s011c_d0f0* ctx)
{
    int ret = 0;
    BN_CTX_s011c_d0f0* new_ctx = 0;

    if (method == 0 || r == 0 || a == 0)
    {
        ERR_put_error_s011c_d0f0(0x10, 0xc9, 0x86, 0, 0);
        return 0;
    }

    if (ctx == 0)
    {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == 0)
            return 0;
    }

    BIGNUM* m = (BIGNUM*)((char*)method + 0x48);

    if (BN_sqr(r, a, ctx) != 0 &&
        method->bn_mod(r, r, m, ctx) != 0)
        ret = 1;

    if (new_ctx != 0)
    {
        BN_CTX_free(new_ctx);
        return ret;
    }
    return ret;
}

// @ 0x011cdba0
int ASN1_item_digest_alg(const ASN1_ITEM* it, ASN1_OBJECT** sigalg, ASN1_OCTET_STRING** md, void* data, ENGINE* engine)
{
    uchar* buf = 0;
    long   len;
    void*  ctx[4];
    int    ret = -1;

    EVP_MD_CTX_init(ctx);

    int nid = OBJ_obj2nid(*sigalg);
    const EVP_MD* type = EVP_get_digestbyname(OBJ_nid2sn(nid));

    if (type == 0)
    {
        ERR_put_error_s011c_d0f0(0xd, 0xc5, 0xa1, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return -1;
    }

    if (EVP_DigestInit_ex(ctx, type, engine) == 0)
    {
        ERR_put_error_s011c_d0f0(0xd, 0xc5, 6, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return 0;
    }

    len = ASN1_item_i2d(data, &buf, it);
    if (len == 0)
    {
        ERR_put_error_s011c_d0f0(0xd, 0xc5, 0x41, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return -1;
    }

    EVP_DigestUpdate(ctx, buf, len);
    OPENSSL_cleanse(buf, len);
    CRYPTO_free(buf);

    if (EVP_DigestFinal_ex(ctx, (uchar*)(*md)->data, (uint*)&(*md)->length) < 1)
    {
        ERR_put_error_s011c_d0f0(0xd, 0xc5, 6, 0, 0);
        EVP_MD_CTX_cleanup(ctx);
        return 0;
    }

    EVP_MD_CTX_cleanup(ctx);
    return 1;
}

// @ 0x011cdd10
int pem_read_bio_ex(BIO* bio, BUF_MEM** out)
{
    int depth = 0;
    int readPos = 0;
    int written = 0;
    int head = 0;
    int tail;
    uint flags;
    int len[5];
    uchar data[4];
    int i;

    BUF_MEM* buf = BUF_MEM_new();
    if (buf == 0)
    {
        ERR_put_error_s011c_d0f0(0xd, 0x6b, 0x41, 0, 0);
        return -1;
    }

    ERR_clear_error();

    for (;;)
    {
        if (8 >= readPos - written)
        {
            int need = (written - readPos) + 8;
            if (BUF_MEM_grow(buf, readPos + need) == 0)
            {
                ERR_put_error_s011c_d0f0(0xd, 0x6b, 0x41, 0, 0);
                BUF_MEM_free(buf);
                return -1;
            }
            i = BIO_read(bio, buf->data + readPos, need);
            if (i < 0 && readPos != written)
            {
                ERR_put_error_s011c_d0f0(0xd, 0x6b, 0x8e, 0, 0);
                BUF_MEM_free(buf);
                return -1;
            }
            if (i > 0)
                readPos += i;
        }

        uchar* start = (uchar*)buf->data + written;
        head = 0;
        flags = pem_parse_block(start, &head, len, data, readPos - written);

        if ((char)flags < 0)
        {
            ulong err = ERR_peek_error();
            if ((err & 0xfff) != 0x9b)
                break;
            ERR_clear_error();
        }

        written += head;

        if ((flags & 1) == 0)
        {
            if (depth != 0 && len[0] == 0 && len[4] == 0)
            {
                depth--;
            }
            else
            {
                if (readPos - written < len[0])
                {
                    int need = (len[0] - readPos) + written;
                    if (BUF_MEM_grow(buf, readPos + need) == 0)
                    {
                        ERR_put_error_s011c_d0f0(0xd, 0x6b, 0x41, 0, 0);
                        BUF_MEM_free(buf);
                        return -1;
                    }
                    for (; 0 < need; need -= i)
                    {
                        i = BIO_read(bio, buf->data + readPos, need);
                        if (i < 1)
                        {
                            ERR_put_error_s011c_d0f0(0xd, 0x6b, 0x8e, 0, 0);
                            BUF_MEM_free(buf);
                            return -1;
                        }
                        readPos += i;
                    }
                }
                written += len[0];
            }

            if (depth < 1)
            {
                *out = buf;
                return written;
            }
        }
        else
        {
            depth++;
        }
    }

    BUF_MEM_free(buf);
    return -1;
}

// @ 0x011ce070
X509_EXT_INFO* x509_ext_info_new(void)
{
    X509_EXT_INFO* info = (X509_EXT_INFO*)CRYPTO_malloc(0x2c, ".\\crypto\\asn1\\x_info.c", 0x45);
    if (info == 0)
    {
        ERR_put_error_s011c_d0f0(0xd, 0xaa, 0x41, 0, 0);
        return 0;
    }

    info->m_ref = 0;
    info->m_extensions = 0;
    info->m_aux = 0;
    info->m_ex_flags = 1;
    info->m_cert_info = 0;
    info->m_crl_info = 0;
    info->m_issuer = 0;
    return info;
}

// @ 0x011ce130
int pem_read_bio_x509_aux(BIO* bio, X509_EXT_INFO** out, const char* name, const char* header)
{
    int ret = 0;
    uchar* payload = 0;
    char*  nameOut = 0;
    int    nameLen = 0;
    int    payloadLen;
    X509_EXT_INFO* info;

    if (bio == 0)
    {
        bio = BIO_new(BIO_s_file());
        if (bio == 0)
        {
            ERR_put_error_s011c_d0f0(9, 0x74, 0x41, 0, 0);
            return ret;
        }
    }

    info = x509_ext_info_new();
    if (info == 0)
        return ret;

    if (BIO_read(bio, 0, 0) != 0)
    {
        if (strcmp((const char*)payload, "CERTIFICATE") == 0)
        {
            ret = pem_finish(info, bio, out, payload, payloadLen, name, nameOut, nameLen, header);
        }
    }
    return ret;
}

// @ 0x011ced70
int ui_method_openssl(UI_METHOD_s011c_d0f0* ui)
{
    if (ui == 0)
        return 0;
    ui->m_name = (const char*)&s_OpenSSL_default_name;
    ui->m_methods = &s_openssl_ui_methods;
    ui->m_data = 0;
    return 1;
}

// @ 0x011ceda0
int ui_method_win32(UI_METHOD_s011c_d0f0* ui)
{
    if (ui == 0)
        return 0;
    ui->m_name = (const char*)&s_WIN32_name;
    ui->m_methods = &s_win32_ui_methods;
    ui->m_data = 0;
    return 1;
}

// @ 0x011cedf0
int pem_header_measure(uchar* table, uchar* name, int* out)
{
    int i;
    BUF_MEM* buf = BUF_MEM_new();
    if (buf == 0)
        return 0;

    uchar* p = name;
    while (*p != 0)
        ++p;

    if (BUF_MEM_grow(buf, (p - name) + 1) == 0)
    {
        BUF_MEM_free(buf);
        return 0;
    }

    uchar* src = name;
    int len = 0;
    while (*src != 0)
    {
        uchar c = *src;
        ushort cls = *(ushort*)(table + (uint)c * 2);

        if (cls & 0x40)
        {
            ++src;
            uchar d = *src;
            cls = *(ushort*)(table + (uint)d * 2);
            while ((cls & 8) == 0 && d != c)
            {
                if (cls & 0x20)
                {
                    d = src[1];
                    ++src;
                    if ((*(ushort*)(table + (uint)d * 2) & 8) != 0)
                        break;
                }
                buf->data[len++] = (char)d;
                d = src[1];
                cls = *(ushort*)(table + (uint)d * 2);
            }
            src += 2;
            buf->data[len++] = (char)c;
        }
        else
        {
            buf->data[len++] = (char)c;
            ++src;
        }
    }

    buf->data[len] = 0;
    *out = len;
    return 1;
}
