// Slice s00f47ed0 -- SporeApp startup entry points and a state destructor.
// Region is /O2 (no frame pointer); float locals via movss.

typedef unsigned int uint32_t;

struct CommandLine {
    CommandLine(const char* cmdLine) throw();
    ~CommandLine() throw();
    int FindSwitch(const wchar_t* name, int a = 0, int b = 0, int c = 0);
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

int SteamAPI_Init();
struct CommandLine;

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

struct cSporeApp {
    cSporeApp();
    bool Init(CommandLine* cmdLine);
    void Run();
    void Shutdown();
    void Release();
    int mExitCode;
    char pad[0x38];
};

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
// PARTIAL: the single largest startup initializer in this module; the bulk of
// the ~60 subsystem hook-ups are not reproduced.
bool cSporeApp::Init(CommandLine* cmdLine)
{
    if (!SteamAPI_Init())
        return false;
    if (cmdLine->FindSwitch(L"demo", 0, 0, 0) != -1) {
        // demo mode
    }
    return false;
}
