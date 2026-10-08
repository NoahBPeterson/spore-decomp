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
void cAppSystemShutdown(void* self) {
    // 1453-byte shutdown sequence not reconstructed; see partial.txt.
    (void)self;
}
