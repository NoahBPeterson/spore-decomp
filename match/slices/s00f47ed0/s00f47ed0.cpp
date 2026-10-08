// Slice s00f47ed0 -- SporeApp startup entry points and a state destructor.
// Region is /O2 (no frame pointer); float locals via movss.

typedef unsigned int uint32_t;

struct WString;

struct CommandLine {
    CommandLine(const char* cmdLine) throw();
    ~CommandLine() throw();
    int FindSwitch(const wchar_t* name, int a = 0, WString* value = 0, int c = 0);   // 0x0092b300
    uint32_t* GetArgs();                                                              // 0x0092b6c0
    uint32_t pad[0x38 / 4];
};

void EAAllocatorDeallocate(void* p);

int EAMain(CommandLine* cmdLine) throw();

// @ 0x00f48a20
int __stdcall WinMainThunk(void* hInstance, void* hPrevInstance, const char* lpCmdLine, int nCmdShow)
{
    CommandLine cmdLine(lpCmdLine);
    return EAMain(&cmdLine);
}

// @ 0x00f48b00
// cTerrainBrushState destructor: releases three heap blocks then resets the vptr.
inline void ReleaseBlock(void* p)
{
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        EAAllocatorDeallocate(p);
}

struct cTerrainBrushState {
    void* vtbl;                              // +0x00
    char pad00[0x2c - 4];                    // +0x04
    void* field2c;                           // +0x2c
    char pad2c[0x40 - 0x30];                 // +0x30
    void* field40;                           // +0x40
    char pad40[0x88 - 0x44];                 // +0x44
    void* field88;                           // +0x88
    ~cTerrainBrushState();
};

cTerrainBrushState::~cTerrainBrushState()
{
    ReleaseBlock(field88);
    ReleaseBlock(field40);
    ReleaseBlock(field2c);
    *(void**)this = (void*)0x13ef094;
}

// ---------------------------------------------------------------------------
// Startup routines.  The EA threading / exception / IO runtime types used by
// EAMain were not reconstructed, so these two functions are recorded as
// partial: only the observable call sequence is reproduced.
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// cSporeApp::Init (0x00f47ed0): the application start-up sequence.  Steam init, subsystem
// creation (factory registry, app system, editor, terrain, gonzago, audio, movie, UI main
// window), command-line driven setup and the final "AppInit" notification.
// ---------------------------------------------------------------------------

extern char gSinclude[];                                            // 0x0148d858 "sinclude \""

// Static empty string of eastl::wstring (begin == end, capacity one char).
extern wchar_t gEmptyWString[2];                                    // 0x01667bac

extern "C" void* memcpy(void* d, const void* s, unsigned n);
#pragma intrinsic(memcpy)

void __cdecl operator delete[](void* p);                            // 0x00f47380
void* operator new[](unsigned size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0
void* operator new(unsigned size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);    // 0x00f473a0
void* operator new(unsigned size, unsigned align, const char* pName, void* alloc);                                   // 0x009512d0

struct EASTLAllocator {};                                           // empty allocator (name stripped in retail)

struct WString {                                                    // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    EASTLAllocator mAllocator;
    WString() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
    WString(const wchar_t* p)
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        RangeInitialize(p);
    }
    ~WString() { DeallocateSelf(); }
    void RangeInitialize(const wchar_t* p);                         // 0x00579a90
    void operator+=(const wchar_t* p);                              // 0x00599bb0
    void DeallocateSelf()
    {
        if (((((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2 && mpBegin)
            operator delete[](mpBegin);
    }
};

struct NString {                                                    // eastl::basic_string<char>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    EASTLAllocator mAllocator;
    ~NString();                                                     // 0x00530670
    __forceinline void RangeInitialize(char* b, char* e)
    {
        unsigned n = (unsigned)(e - b);
        unsigned sz = n + 1;
        char* p = (char*)operator new[](sz, "EASTL", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        mpBegin = p;
        mpCapacity = p + sz;
        *(unsigned*)(mpBegin + 0) = *(unsigned*)(b + 0);
        *(unsigned*)(mpBegin + 4) = *(unsigned*)(b + 4);
        *(unsigned short*)(mpBegin + 8) = *(unsigned short*)(b + 8);
        mpEnd = p + n;
        *mpEnd = 0;
    }
    void append(const char* b, const char* e);                      // 0x00455d60
    void append(const char* p);                                     // 0x0060c4e0
};

NString* __cdecl ConvertToString8(NString* out, const WString* in);   // 0x0093c570

struct Variant {                                                    // EA::Variant
    char data[0x10];
    unsigned short flags;
    unsigned short pad;
    Variant(const WString* s);                                      // 0x005a74a0
    void Destruct(int a);                                           // 0x0093db80
    ~Variant()
    {
        if (flags & 4)
            Destruct(0);
    }
};

template <class T>
struct AutoRefCount {                                               // inline EA::AutoRefCount
    T* mpObject;
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct IAppObj;

struct IProfiler {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void Begin(const char* name, int a, int b, int c, int d);  // +0x20
};

struct IAppSystem {
    virtual void AddRef();  // +0x0
    virtual void Release();  // +0x4
    virtual void s08();
    virtual void SetDirs(const wchar_t* playerDir, const wchar_t* appDir);  // +0xc
    virtual bool InitDDF(CommandLine* cmd, const wchar_t* ddfList);  // +0x10
    virtual bool Init14(CommandLine* cmd);  // +0x14
    virtual void Init18(CommandLine* cmd);  // +0x18
    virtual bool Init1c(CommandLine* cmd);  // +0x1c
    virtual bool Init20(CommandLine* cmd, int a);  // +0x20
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void Fn74(const void* a, const void* b);  // +0x74
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual IProfiler* GetProfiler();  // +0x88
};

struct IAudioSystem {
    virtual bool Init0(CommandLine* cmd);  // +0x0
    virtual bool Init4(CommandLine* cmd);  // +0x4
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void Release();  // +0x14
};

struct IEditorSystem {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual bool Init10(CommandLine* cmd);  // +0x10
    virtual bool Init14(CommandLine* cmd);  // +0x14
};

struct ITerrainSystem {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual bool Init0c(CommandLine* cmd);  // +0xc
    virtual bool Init10(CommandLine* cmd);  // +0x10
};

struct IGonzago {
    void Fn5d870(unsigned a);                          // 0x00b5d870
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void Fn10();  // +0x10
    virtual void Fn14();  // +0x14
    virtual void Fn18();  // +0x18
    virtual void s1c();
    virtual void s20();
    virtual void Fn24();  // +0x24
};

struct IMessageServer {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void Fn14(unsigned id, int a, int b);  // +0x14
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void AddListener(void* handler, unsigned id);  // +0x24
};

struct ICameraMgr {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void RegisterFactory(unsigned id, void (*fn)());  // +0x20
    virtual void RegisterController(unsigned id, void* ctl, const wchar_t* name);  // +0x24
    virtual void Fn28();  // +0x28
    virtual void s2c();
    virtual void s30();
    virtual void Fn34(unsigned id);  // +0x34
};

struct IAppObj {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void Fn14();  // +0x14
    virtual void Fn18();  // +0x18
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void Fn40(int a);  // +0x40
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual ICameraMgr* GetSub50();  // +0x50
};

struct ICanvas {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void Fn30(const wchar_t* s);  // +0x30
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void Fn84();  // +0x84
};

struct IConfigManager {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void Fn20(int a);  // +0x20
};

struct IMaterialManager {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual bool Fn1c();  // +0x1c
};

struct IObj67dde0 {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void Fn20();  // +0x20
};

struct IObj67dd20 {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void Fn1c(unsigned id, int a, CommandLine* cmd, int b);  // +0x1c
};

struct ICheatManager {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void RunScript(const char* text);  // +0x20
};

struct IMainWin {
    void SetMode(int m);                               // 0x0077f010
    void SetFocusObj(IAppObj* a);                      // 0x00813260
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void Fn18();  // +0x18
};

struct IMovie {
    virtual void s00();
    virtual void Fn04();
};


// Out-of-line AutoRefCount<T>::operator=(T*) instantiations (the callee addresses differ by T).
struct AudioRef {
    IAudioSystem* mpObject;
    void operator=(IAudioSystem* p);                                // 0x00f475f0
};
struct EditorRef {
    IEditorSystem* mpObject;
    void operator=(IEditorSystem* p);                               // 0x00f47630
};
struct GonzagoRef {
    IGonzago* mpObject;
    void operator=(IGonzago* p);                                    // 0x00f47630
};
struct TerrainRef {
    ITerrainSystem* mpObject;
    void operator=(ITerrainSystem* p);                              // 0x00b5f950
};
struct MainWinRef {
    IMainWin* mpObject;
    void operator=(IMainWin* p);                                    // 0x00b5f950
};

struct cDirectPropertyList {
    void SetBoolProperty(unsigned id, bool value);                  // 0x006a17e0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void SetProperty(unsigned id, Variant* v);              // +0x14
};

struct FactoryRegistry {
    FactoryRegistry();                                              // 0x009206d0
    char pad[0x148];
};
struct cEditorSystem : IEditorSystem {
    cEditorSystem();                                                // 0x005d67f0
    char pad[0x48 - 4];
};
struct cMouseCameraController {
    cMouseCameraController(int a);                                  // 0x007d9fb0
    char pad[0x124];
};
struct cSPUIMainWin : IMainWin {
    cSPUIMainWin();                                                 // 0x008141b0
    char pad[0x2e0 - 4];
};
struct cProfilerStub {
    cProfilerStub();                                                // 0x006249b0
    char pad[4];
};

// callees (cdecl unless a member)
bool SteamAPI_Init();                                               // 0x006b4f20 (import thunk)
void NoOp();                                                        // 0x00c2e4e0 (empty)
bool __cdecl RegisterAppCallback(void (*fn)(), void* ctx);          // 0x0081d470
void Fn8054f0();                                                    // 0x008054f0
void __cdecl SetFactoryRegistry(FactoryRegistry* r);                // 0x009200a0
void __cdecl SetFactoryRegistry2(FactoryRegistry* r);               // 0x0067cb90
void Fn692ee0();                                                    // 0x00692ee0
void __cdecl Fn687a00(int a, const void* b);                        // 0x00687a00
void ProfEnableAffinityMasks();                                     // 0x00687c20
IAppSystem* GetAppSystem();                                         // 0x007e8950
void __cdecl GetRegistryString(const wchar_t* key, WString* out);   // 0x006aba80
void Fn685540();                                                    // 0x00685540
void* GetManager();                                                 // 0x0067dcd0
void __cdecl IteratePackages(void* mgr);                            // 0x006875b0
IAudioSystem* __cdecl CreateAudioSystem(CommandLine* cmd);          // 0x00a45f30
IEditorSystem* GetEditorSystemX();
ITerrainSystem* CreateTerrainSystem();                              // 0x00fc1e10
IGonzago* CreateGonzago();                                          // 0x00b5e020
IGonzago** GetGonzagoGlobal();                                      // 0x00b3d220
IAppObj* App();                                                     // 0x0067dd10
ICanvas* Canvas();                                                  // 0x0067dcf0
IConfigManager* ConfigManager();                                    // 0x0067dd30
IMessageServer* MessageServer();                                    // 0x0067dcc0
void Fn82e470();                                                    // 0x0082e470
IMaterialManager* MaterialManager();                                // 0x0067dd70
void __cdecl SetAudioGlobal(IAudioSystem* a);                       // 0x0067cc00
IMovie* GetMovieSystem();                                             // 0x00fd8140
void __cdecl SetMovieGlobal(IMovie* a);                               // 0x0067cc10
void* GetAllocator();                                               // 0x009512c0
void __cdecl SetProfilerGlobal(cProfilerStub* p);                   // 0x0067cc60
IObj67dde0* Fn67dde0();                                             // 0x0067dde0
IObj67dd20* Fn67dd20();                                             // 0x0067dd20
unsigned __int64 Fn571e60();                                        // 0x00571e60
unsigned __int64 GetStopwatchFrequency();                           // 0x0093a470
ICheatManager* CheatManager();                                      // 0x0067de20
void __cdecl GetFolderPath(unsigned id, WString* out, int a);       // 0x00688830
struct DemoFlag { bool v; };
void __cdecl BuildStringTokenTranslator(DemoFlag demo, WString* out);    // 0x00f47ca0
void CreateMouseCameraController();                                 // 0x007da790
void CreateSmoothCameraController();                                // 0x007df710

extern cDirectPropertyList* sAppProperties;                         // 0x015fd918
extern CommandLine* gCommandLine;                                   // 0x015fd920
extern char gUnk148d7c8;                                            // 0x0148d7c8
extern char gUnk148d7e0;                                            // 0x0148d7e0
extern char gUnk15b0834;                                            // 0x015b0834
extern char gUnk153c326;                                            // 0x0153c326
extern float gF1000;                                                // 0x013ec5b4
extern float gF0001;                                                // 0x013f9428

struct cSporeApp {
    void* mVtbl0;                       // +0x00 IHandler
    void* mVtbl4;                       // +0x04 RefCountVTemplate
    int mRefCount;                      // +0x08
    bool mAppRunning;                   // +0x0c
    bool mFlag0d;                       // +0x0d
    unsigned __int64 mReferenceCycle;   // +0x10
    float mMSPerCycle;                  // +0x18
    float mCyclesPerMS;                 // +0x1c
    AutoRefCount<IAppSystem> mAppSystem;    // +0x20
    FactoryRegistry* mFactoryRegistry;  // +0x24
    MainWinRef mUIMainWin;              // +0x28
    AudioRef mAudioSystem;              // +0x2c
    IMovie* mMovieSystem;               // +0x30
    EditorRef mEditorSystem;            // +0x34
    TerrainRef mTerrainSystem;          // +0x38
    GonzagoRef mGonzagoSystem;          // +0x3c
    int mExitCode;                      // +0x40
    void* mProfiler;                    // +0x44

    cSporeApp();
    bool Init(CommandLine* cmdLine);
    void Run();
    void Shutdown();                        // 0x00f47700
    void Release();
    void SetupShipDirsFromCommandLine();    // 0x00f47d80
    void Fn47550();                         // 0x00f47550
};

struct Mutex {
    Mutex() throw();
    ~Mutex() throw();
    void Init();
    int Lock();
    void Unlock();
};

struct ExceptionHandler {
    ExceptionHandler();
    ~ExceptionHandler();
    void SetReportDirectory(const char* dir);
};

struct FilePath {
    static void GetDriveAndDirectory(char* buffer, uint32_t size);
};

void NamedMutexCreate();
void SporeAlert(const char* message, int priority, int timeout);
void InitExceptionHandler(const char* name);
void InitSearchPath();
void InitModules(int a, int b);

// @ 0x00f48850
// PARTIAL: EA runtime object types (Mutex, ExceptionHandler, FilePath, the
// cSporeApp inlined constructor) were not reconstructed.
int EAMain(CommandLine* cmdLine) throw()
{
    int multipleInstances = cmdLine->FindSwitch(L"multipleInstances", 0, 0, 0);
    Mutex mutex;
    if (multipleInstances == -1) {
        NamedMutexCreate();
        mutex.Init();
        if (mutex.Lock() == -2) {
            SporeAlert("Another instance of the game is already running", 2, 1000);
            return -1;
        }
    }

    ExceptionHandler handler;
    InitExceptionHandler("Spore");
    InitSearchPath();
    char reportDirectory[0x104];
    FilePath::GetDriveAndDirectory(reportDirectory, 0x104);
    handler.SetReportDirectory(reportDirectory);
    InitModules(2, -1);

    cSporeApp* app = new cSporeApp();
    if (app != 0) {
        if (app->Init(cmdLine)) {
            app->Run();
            app->Shutdown();
        }
    }
    int exitCode = app->mExitCode;
    app->Release();
    if (multipleInstances == -1)
        mutex.Unlock();
    handler.~ExceptionHandler();
    return exitCode;
}



// @ 0x00f47ed0
bool cSporeApp::Init(CommandLine* cmdLine)
{
    if (!SteamAPI_Init()) {
        NoOp();
        return false;
    }
    if (!RegisterAppCallback(NoOp, this))
        return false;
    mFlag0d = true;
    DemoFlag demo;
    demo.v = cmdLine->FindSwitch(L"demo", 0, 0, 0) != -1;
    Fn8054f0();
    FactoryRegistry* registry = new("App", 0, 0, 0, 0) FactoryRegistry();
    mFactoryRegistry = registry;
    SetFactoryRegistry(registry);
    SetFactoryRegistry2(mFactoryRegistry);
    Fn692ee0();
    Fn687a00(5, &gUnk148d7e0);

    bool noDevDirs = true;
    if (cmdLine->FindSwitch(L"devDirs", 0, 0, 0) != -1)
        noDevDirs = false;
    int shipDirs = cmdLine->FindSwitch(L"shipDirs", 0, 0, 0);
    if (shipDirs != -1 || noDevDirs)
        ProfEnableAffinityMasks();

    mAppSystem = GetAppSystem();
    mAppSystem.mpObject->Fn74(&gUnk148d7c8, &gUnk15b0834);

    WString playerDir(L"My Spore Creations");
    WString appDir(L"Spore");
    GetRegistryString(L"HKEY_LOCAL_MACHINE\\Software\\Electronic Arts\\SPORE\\PlayerDir", &playerDir);
    GetRegistryString(L"HKEY_LOCAL_MACHINE\\Software\\Electronic Arts\\SPORE\\AppDir", &appDir);
    mAppSystem.mpObject->SetDirs(playerDir.mpBegin, appDir.mpBegin);
    if (!mAppSystem.mpObject->InitDDF(cmdLine, L"Spore_DDFList.txt"))
        return false;

    cDirectPropertyList* props = sAppProperties;
    props->SetBoolProperty(0x46, false);
    SetupShipDirsFromCommandLine();
    NoOp();
    if (gCommandLine->FindSwitch(L"baseGame", 0, 0, 0) != -1)
        Fn685540();
    IteratePackages(GetManager());
    mAudioSystem = CreateAudioSystem(cmdLine);
    if (!mAudioSystem.mpObject->Init0(cmdLine)) {
        IAudioSystem* old = mAudioSystem.mpObject;
        if (old) {
            mAudioSystem.mpObject = 0;
            old->Release();
        }
    }
    mEditorSystem = new("Editor", 0, 0, 0, 0) cEditorSystem();
    if (!mEditorSystem.mpObject->Init10(cmdLine))
        return false;
    mTerrainSystem = CreateTerrainSystem();
    if (!mTerrainSystem.mpObject->Init0c(cmdLine))
        return false;
    mAppSystem.mpObject->Init18(cmdLine);
    Fn47550();
    mGonzagoSystem = CreateGonzago();
    IGonzago* gonzago = mGonzagoSystem.mpObject;
    *GetGonzagoGlobal() = gonzago;
    mGonzagoSystem.mpObject->Fn10();
    mGonzagoSystem.mpObject->Fn24();
    App()->Fn14();
    if (!mAppSystem.mpObject->Init14(cmdLine))
        return false;

    ICanvas* canvas = Canvas();
    WString tokens;
    BuildStringTokenTranslator(demo, &tokens);
    canvas->Fn30(tokens.mpBegin);
    if (cmdLine->FindSwitch(L"automation", 0, 0, 0) == -1)
        ConfigManager()->Fn20(1);
    if (!mAppSystem.mpObject->Init1c(cmdLine)) {
        Shutdown();
        return false;
    }
    IMessageServer* server = MessageServer();
    server->AddListener(this, 0x1ee100a);
    server->AddListener(this, 0x1ee1003);
    server->AddListener(this, 0x44edd9c);
    if (!mAppSystem.mpObject->Init20(cmdLine, 0)) {
        Shutdown();
        return false;
    }
    Fn82e470();
    if (!MaterialManager()->Fn1c())
        return false;

    IAppObj* app = App();
    ICameraMgr* cameras = app->GetSub50();
    if (cameras) {
        cMouseCameraController* mouse = new("App", 0, 0, 0, 0) cMouseCameraController(0);
        cameras->RegisterController(0xa2f095, mouse, L"mouse");
        cameras->Fn34(0xa2f095);
        cameras->RegisterFactory(0xedd3bb, CreateMouseCameraController);
        cameras->RegisterFactory(0xf47a49, CreateSmoothCameraController);
    }
    if (mAudioSystem.mpObject) {
        bool ok = mAudioSystem.mpObject->Init4(cmdLine);
        IAudioSystem* audio = mAudioSystem.mpObject;
        if (ok) {
            SetAudioGlobal(audio);
        } else if (audio) {
            mAudioSystem.mpObject = 0;
            audio->Release();
        }
    }
    mMovieSystem = GetMovieSystem();
    if (mMovieSystem) {
        mMovieSystem->Fn04();
        SetMovieGlobal(mMovieSystem);
    }
    mUIMainWin = new(8, "UI/MainWin", GetAllocator()) cSPUIMainWin();
    mUIMainWin.mpObject->SetMode(3);
    mUIMainWin.mpObject->Fn18();
    mUIMainWin.mpObject->SetFocusObj(app);
    Canvas()->Fn84();
    if (!mEditorSystem.mpObject->Init14(cmdLine))
        return false;
    if (!mTerrainSystem.mpObject->Init10(cmdLine))
        return false;
    server->AddListener(this, (unsigned)(unsigned long)&gUnk153c326);
    mGonzagoSystem.mpObject->Fn14();
    mGonzagoSystem.mpObject->Fn5d870(*cmdLine->GetArgs());
    SetProfilerGlobal(new("App", 0, 0, 0, 0) cProfilerStub());
    mAppSystem.mpObject->GetProfiler()->Begin("AppInit", 0, 0, 0, 0);
    app->Fn18();
    app->GetSub50()->Fn28();
    IObj67dde0* o = Fn67dde0();
    if (o)
        o->Fn20();
    mGonzagoSystem.mpObject->Fn18();
    app->Fn40(0);
    Fn67dd20()->Fn1c(0xd6396913, 0, cmdLine, 1);
    props->SetBoolProperty(0x2a, false);
    mReferenceCycle = Fn571e60();
    double freq1 = (double)GetStopwatchFrequency();
    mMSPerCycle = (float)(gF1000 / freq1);
    double freq2 = (double)GetStopwatchFrequency();
    mCyclesPerMS = (float)(freq2 * gF0001);

    WString hostIP;
    WString clientIP;
    props->SetBoolProperty(0x3d, false);
    props->SetBoolProperty(0x3e, false);
    if (cmdLine->FindSwitch(L"hostIP", 0, &hostIP, 0) != -1) {
        props->SetBoolProperty(0x3e, true);
        Variant v(&hostIP);
        props->SetProperty(0x3cf54da, &v);
    }
    if (cmdLine->FindSwitch(L"clientIP", 0, &clientIP, 0) != -1) {
        props->SetBoolProperty(0x3e, true);
        Variant v(&clientIP);
        props->SetProperty(0x3cf54eb, &v);
    }
    if (cmdLine->FindSwitch(L"isHost", 0, 0, 0) != -1)
        props->SetBoolProperty(0x3d, true);

    ICheatManager* cheats = CheatManager();
    if (cheats) {
        WString cheatFile;
        GetFolderPath(0xa0214f, &cheatFile, 0);
        cheatFile += L"localCheats.txt";
        NString script;
        script.mpBegin = 0;
        script.mpEnd = 0;
        script.mpCapacity = 0;
        script.RangeInitialize(gSinclude, gSinclude + 10);
        {
            NString narrow;
            NString* conv = ConvertToString8(&narrow, &cheatFile);
            script.append(conv->mpBegin, conv->mpEnd);
        }
        script.append("\"");
        cheats->RunScript(script.mpBegin);
    }
    server->Fn14(0x49790b2, 0, 0);
    mAppRunning = true;
    return true;
}
