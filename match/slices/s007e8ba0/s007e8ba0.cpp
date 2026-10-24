// Slice s007e8ba0.
#include "s007e8ba0.h"
#include <intrin.h>

// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE

extern "C" {
__declspec(dllimport) void __stdcall GetSystemInfo(void*);
__declspec(dllimport) long __cdecl wcstol(const wchar_t*, wchar_t**, int);
__declspec(dllimport) long __cdecl _wtol(const wchar_t*);
}

// EA global allocator new (0x00f473a0) and EA::Allocator::ZoneObject::operator new (0x00926020).
void FreeWString(void* p);   // 0x00f47380
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

// Objects built by PreInit (constructors are thiscall, defined elsewhere).
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

// Minimal EASTL wide string with the shared empty-string representation.
extern wchar_t g_01667bac[2];
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
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void append(const wchar_t* first, const wchar_t* last);   // 0x00429580
};

struct WStrNoDtor {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;
    WStrNoDtor() : mpBegin(g_01667bac), mpEnd(g_01667bac), mpCapacity(g_01667bac + 1) {}
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

// Free functions (addresses in the names; all __cdecl unless noted).
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

extern uint32_t g_0163939c;          // job priority
extern uint8_t  g_0154c478;          // multi-core flag
extern uint32_t g_01639470;

static inline void AssignRef(IRefObj*& slot, IRefObj* p) {
    IRefObj* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

// ---- vtable-slot call helpers used by cAppSystem::Shutdown (0x007E9450) ----
typedef void  (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF1)(void*, int);
typedef void  (__thiscall *VF2)(void*, int, int);
typedef void  (__thiscall *VF1P)(void*, void*);
typedef void* (__thiscall *VF0R)(void*);
typedef void* (__thiscall *VF1PR)(void*, void*);

static __forceinline void  VC0(void* o, int off) {
    ((VF0)*(void**)((char*)*(void**)o + off))(o);
}
static __forceinline void  VC1(void* o, int off, int a) {
    ((VF1)*(void**)((char*)*(void**)o + off))(o, a);
}
static __forceinline void  VC2(void* o, int off, int a, int b) {
    ((VF2)*(void**)((char*)*(void**)o + off))(o, a, b);
}
static __forceinline void  VC1P(void* o, int off, void* a) {
    ((VF1P)*(void**)((char*)*(void**)o + off))(o, a);
}
static __forceinline void* VC0R(void* o, int off) {
    return ((VF0R)*(void**)((char*)*(void**)o + off))(o);
}
static __forceinline void* VC1PR(void* o, int off, void* a) {
    return ((VF1PR)*(void**)((char*)*(void**)o + off))(o, a);
}

// ---- extra free functions called by cAppSystem::Shutdown ----
void  FUN_0067def0(int a);
void  FUN_006ad850(void* p);
void  FUN_006b4780();
void  FUN_0067dff0(int a);
void  FUN_0067e000(int a);
void  FUN_006bbb10(void* a, void* b);
void  FUN_0067dee0(int a);
void  FUN_008d3120(int a);
void  FUN_0067ded0(int a);
void  FUN_0067e0d0(int a);
void  FUN_0067df40(int a);
void  FUN_006b3610();
void  FUN_0067df10(int a);
void  FUN_0067e040(int a);
void  FUN_0067e0b0(int a);
void  FUN_006895c0(int a);
void  FUN_0067e060(int a);
void  FUN_0067e080(int a);
void  FUN_00929ca0();
void  FUN_007cdd80();
void* FUN_0094cd50(int a);
void* FUN_0094f0d0();
void  FUN_0094f0e0(int a);
void* FUN_006782c0(void* a, void* b, void* c);
void  FUN_006bb4b0(const wchar_t* a, void* b, int c);   // 0x006bb4b0
void  GetSystemPath(int id, wchar_t* out, int flags);   // 0x009323c0

// Direct (non-virtual) __thiscall helpers: MSVC rejects __thiscall on free
// functions, so each target address gets a member-function thunk whose receiver
// is the object pointer.
struct DirectCall {
    void call_7c3ba0();   // 0x007c3ba0  mMainViewer teardown step
    void call_7c4000();   // 0x007c4000  mMainViewer destructor
    void call_7db8b0();   // 0x007db8b0  mPackManager teardown step
    void call_7a41a0();   // 0x007a41a0  mPackManager destructor
    void call_695f00();   // 0x00695f00  mLocaleManager teardown step
    void call_695c30();   // 0x00695c30  mLocaleManager teardown step
    void call_68c4d0();   // 0x0068c4d0  mGarbageMan teardown step
    void call_68c4e0();   // 0x0068c4e0  mGarbageMan destructor
    void call_94fcc0();   // 0x0094fcc0  device teardown step
};

extern wchar_t g_01413dcc[];   // 0x1413dcc  L"\\home\\ehshell.exe"
extern int     g_013ec47c;     // 0x13ec47c  (nil descriptor passed to the writer)

// @ 0x007E8BA0  (cAppSystem::PreInit)
bool cAppSystem::PreInit(CommandLine* cmd, int unused) {
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
        gAppProperties->SetBoolProperty(0xce1c9372, true);
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

// @ 0x007E9300  (cAppSystem::InitPlugins)
bool cAppSystem::InitPlugins(void* cmd) {
    CommandLine* cl = (CommandLine*)cmd;
    if (cl->FindSwitch(L"noPlugins", 0, 0, 0) == -1) {
        if (cl->FindSwitch(L"safe", 0, 0, 0) == -1) {
            return LoadPlugins();
        }
    }
    return false;
}

// @ 0x007E93D0  (cAppSystem::SetUserDirNames)
void cAppSystem::SetUserDirNames(wchar_t* publicDir, wchar_t* privateDir) {
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

// @ 0x007E9450  (cAppSystem::Shutdown)
bool cAppSystem::Shutdown() {
    FUN_0067def0(0);

    if (mResourceManager) {
        for (int i = 0; i < 3; ++i)
            VC2(mResourceManager, 0x70, 0, 0);
        FUN_006ad850(mResourceManager);
    }

    FUN_006b4780();

    if (mEffectsManager) {
        FUN_0067dff0(0);
        if (mEffectsParser)
            VC1P(mEffectsManager, 0x68, VC0R(mEffectsParser, 0x38));

        void** begin = mEffectVecBegin;
        void** end = mEffectVecEnd;
        int n = (int)(end - begin);
        for (int i = 0; i < n; ++i)
            VC1P(mEffectsManager, 0x68, begin[i]);

        void** p = (void**)FUN_006782c0(end, end, begin);
        while (p < mEffectVecEnd) {
            if (*p)
                VC0(*p, 4);
            ++p;
        }
        mEffectVecEnd = (void**)((char*)end - n * 4);

        VC0(mEffectsManager, 4);
        if (mEffectsManager) {
            void* old = mEffectsManager;
            mEffectsManager = 0;
            VC0(old, 0xc);
        }
    }

    if (mEffectsParser) {
        FUN_0067e000(0);
        VC0(mEffectsParser, 0xc);
        if (mEffectsParser) {
            void* old = mEffectsParser;
            mEffectsParser = 0;
            VC0(old, 4);
        }
    }

    if (mGraphicsSystem) {
        VC0(mGraphicsSystem, 0x14);
        if (mGraphicsSystem) {
            void* old = mGraphicsSystem;
            mGraphicsSystem = 0;
            VC0(old, 4);
        }
    }

    if (mMainViewer) {
        ((DirectCall*)mMainViewer)->call_7c3ba0();
        void* view = mMainViewer;
        if (view) {
            ((DirectCall*)view)->call_7c4000();
            FreeWString(view);
        }
        mMainViewer = 0;
    }

    if (mCanvas) {
        FUN_006bbb10(VC1PR(mCanvas, 0x94, mpDropTarget), mpDropTarget);
        while (mLockCount)
            VC0(this, 0x70);
        FUN_0067dee0(0);
        VC0(mCanvas, 8);
        if (mCanvas)
            VC1(mCanvas, 0, 1);
        mCanvas = 0;
    }

    if (mInputManager) {
        FUN_008d3120(0);
        FUN_0067ded0(0);
        VC0(mInputManager, 8);
        if (mInputManager)
            VC1(mInputManager, 0, 1);
        mInputManager = 0;
    }

    if (mPackManager) {
        ((DirectCall*)mPackManager)->call_7db8b0();
        FUN_0067e0d0(0);
        void* pack = mPackManager;
        if (pack) {
            ((DirectCall*)pack)->call_7a41a0();
            FreeWString(pack);
        }
        mPackManager = 0;
    }

    if (mConfigManager) {
        FUN_0067df40(0);
        VC0(mConfigManager, 0x10);
        if (mConfigManager) {
            void* old = mConfigManager;
            mConfigManager = 0;
            VC0(old, 4);
        }
    }

    FUN_006b3610();

    if (mLocaleManager)
        ((DirectCall*)mLocaleManager)->call_695f00();

    if (mResourceManager) {
        FUN_008de1b0(0);
        FUN_0067dec0(0);
        VC0(mResourceManager, 8);
        if (mResourceManager)
            VC1(mResourceManager, 0, 1);
        mResourceManager = 0;
    }

    FUN_0067df10(0);

    if (mFieldCC) {
        void* old = mFieldCC;
        mFieldCC = 0;
        VC0(old, 4);
    }

    if (mPropertyManager) {
        FUN_0067e040(0);
        VC0(mPropertyManager, 0x14);
        if (mPropertyManager) {
            void* old = mPropertyManager;
            mPropertyManager = 0;
            VC0(old, 4);
        }
    }

    if (mTelemetry) {
        FUN_0067e0b0(0);
        VC0(mTelemetry, 8);
        if (mTelemetry) {
            void* old = mTelemetry;
            mTelemetry = 0;
            VC0((char*)old + 8, 4);
        }
    }

    if (mCommandServer) {
        FUN_006895c0(0);
        VC0(mCommandServer, 0x14);
        if (mCommandServer) {
            VC1(mCommandServer, 8, 1);
            mCommandServer = 0;
        }
    }

    if (mLocaleManager) {
        FUN_0067e060(0);
        ((DirectCall*)mLocaleManager)->call_695c30();
        if (mLocaleManager) {
            void* old = mLocaleManager;
            mLocaleManager = 0;
            VC0(old, 8);
        }
    }

    if (mCheatManager) {
        FUN_0067e030(0);
        VC0(mCheatManager, 0x10);
        if (mCheatManager) {
            void* old = mCheatManager;
            mCheatManager = 0;
            VC0(old, 4);
        }
    }

    if (mMessageServer) {
        FUN_00883870(0);
        FUN_0067deb0(0);
        VC0(mMessageServer, 8);
        if (mMessageServer)
            VC1(mMessageServer, 0, 1);
        mMessageServer = 0;
    }

    if (mJobManager) {
        VC0(mJobManager, 0xc);
        if (mJobManager)
            VC1(mJobManager, 0, 1);
        mJobManager = 0;
        FUN_0068f4c0(0);
    }

    if (mGarbageMan) {
        ((DirectCall*)mGarbageMan)->call_68c4d0();
        FUN_0067e0a0(0);
        void* gc = mGarbageMan;
        if (gc) {
            ((DirectCall*)gc)->call_68c4e0();
            FreeWString(gc);
        }
        mGarbageMan = 0;
    }

    FUN_00929ca0();

    if (mIDGen) {
        FUN_0067e080(0);
        if (mIDGen)
            VC1(mIDGen, 0, 1);
        mIDGen = 0;
    }

    FUN_00c2e4e0();
    FUN_007cdd80();
    FUN_00936410(0);

    VC1(&mPluginLibraries, 0x18, 1);
    VC0(&mPluginLibraries, 8);

    void* loader = FUN_0094cd50(0);
    if (loader) {
        VC0(loader, 8);
        VC1(loader, 0, 1);
    }
    void* device = FUN_0094f0d0();
    if (device) {
        ((DirectCall*)device)->call_94fcc0();
        FUN_0094f0e0(0);
        VC1(device, 0, 1);
    }

    if (mSaveUserDirs) {
        WStr   message;
        wchar_t path[260];
        GetSystemPath(2, path, 0);

        const wchar_t* e = path;
        while (*e) ++e;
        int n = (int)(e - path);
        message.assign(path, path + n);

        const wchar_t* tail = g_01413dcc;
        const wchar_t* te = tail;
        while (*te) ++te;
        int m = (int)(te - tail);
        message.append(tail, tail + m);

        FUN_006bb4b0(message.mpBegin, &g_013ec47c, 0);
    }

    return true;
}
