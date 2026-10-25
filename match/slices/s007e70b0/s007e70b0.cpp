// Slice s007e70b0: SP::cAppSystem constructor/destructor, message handler, configure
// and the logging-directory setup helper, plus PropWatcher32's constructor and the
// crash cheat.  Self-contained (the shared cAppSystem header's offsets differ from the
// raw disassembly of this slice).  All seven functions are complete reconstructions;
// they are listed in nonmatching.txt.
#include "types.h"

// ---------------------------------------------------------------------------
// allocator
// ---------------------------------------------------------------------------
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void __cdecl operator_delete__(void* p);                                                   // 0x00f47380

extern "C" {
__declspec(dllimport) long __cdecl atol(const char* text);
__declspec(dllimport) int __cdecl swscanf(const wchar_t* text, const wchar_t* fmt, ...);
}

// ---------------------------------------------------------------------------
// image globals referenced by address
// ---------------------------------------------------------------------------
extern char gEmptyString[];        // 0x01667bac shared empty-string sentinel
extern char gCrashFlagName[];      // 0x01413a38 "crash"
extern char gAllocatorName[];      // 0x013ebc58
extern char gVtbl13eb90c[];        // 0x013eb90c
extern char gVtbl13eb844[];        // 0x013eb844
extern char gVtbl13eb384[];        // 0x013eb384 cListenerBase vftable
extern char gVtbl13ef094[];        // 0x013ef094 hkReferencedObject vftable
extern char gVtbl1413ae0[];        // 0x01413ae0 cAppSystem vftable
extern char gVtbl1413ad0[];        // 0x01413ad0 IHandlerRC vftable
extern char gVtbl1413acc[];        // 0x01413acc RefCountTemplate vftable
extern char gVtbl1413914[];        // 0x01413914 effect-collection IDs
extern char gVtbl141391c[];        // 0x0141391c effect-collection vector
extern char gVtbl13eb394[];        // 0x013eb394 PaintSystem vftable
extern char gVtbl13eb938[];        // 0x013eb938 ITracerBase vftable
extern char gWatcherList[];        // 0x01639470 PropWatcher registry list
extern char gEmptyWatcherName[];   // 0x013ec468 empty trace name
extern void* gAppProperties;       // 0x015fd918
extern void* gDefaultCameraRaster; // 0x015d0838

// ---------------------------------------------------------------------------
// helper entry points (defined elsewhere in the retail image)
// ---------------------------------------------------------------------------
struct ResourceManager;
struct ResourceObj;
struct MessageServer;
struct MsgData;
struct ResLocal;
struct Canvas;
struct CommandLine;
struct IConfigManager;
struct IGraphicsSystem;
struct Viewer;
struct TraceServer;
struct LogTarget;
struct Mutex;
struct SharedLibraryRegistry;
struct PropWatcher32;
struct WStr;
struct CStr;
struct RefVec;
struct WStrVec;
struct IRefCounted;
struct Telemetry;
struct LocaleManager;

ResourceManager* __cdecl GetResourceManager();                 // 0x0067dcd0
IGraphicsSystem* __cdecl GetGraphicsManager();                 // 0x0067dd50
MessageServer* __cdecl SP_MessageServer();                     // 0x0067dcc0
void __cdecl ThreadSleep(int* milliseconds);                   // 0x00921df0
void __cdecl ReportGraphicsFailure(const char* text, int line, int a, int b);  // 0x006bb1c0
void __cdecl SP_AutomateEntry(CommandLine* cmd, char* result);  // 0x007db570
bool __cdecl TryGetUIntProperty(void* props, unsigned id, int* out);   // 0x00410370
bool __cdecl GetBoolProperty(void* props, unsigned id, char* out);     // 0x00407190

void __cdecl GetDirString(unsigned id, WStr* out, int flags);  // 0x00688830
WStr* __cdecl PathJoin(WStr* out, const WStr* base, const wchar_t* name);  // 0x0057cba0
bool __cdecl FileExists(const wchar_t* path);                  // 0x00931fa0
void __fastcall WStr_Assign(WStr* self, int unused, const wchar_t* first, const wchar_t* last);  // 0x00423650
void __fastcall WStr_RangeInitialize(WStr* self, int unused, const wchar_t* text);  // 0x00579a90
void __cdecl CStrSprintf(CStr* out, const char* fmt, const wchar_t* arg);  // 0x00472fe0

Viewer* __fastcall Viewer_Construct(Viewer* self, int unused);           // 0x007c3f70
void __fastcall Viewer_Init(Viewer* self, int unused, bool flag);        // 0x007c4dd0
void __fastcall Viewer_Clear(const Viewer* self, int unused, unsigned flags);  // 0x007c3c50
void __fastcall Viewer_Run(Viewer* self, int unused);                    // 0x007c3ba0
void __fastcall Viewer_Destroy(Viewer* self, int unused);                // 0x007c4000
int __cdecl ResetVertexShader();                                         // 0x011f8160
void __cdecl RestoreVertexShader();                                      // 0x011f81d0
void __cdecl ShowRaster(void* raster);                                   // 0x011f8120

void __fastcall Mutex_Construct(Mutex* self, int unused, void* params, bool locked);  // 0x009222a0
void __fastcall Mutex_Destruct(Mutex* self, int unused);                              // 0x00922130
void __fastcall SharedLibraryRegistry_Construct(SharedLibraryRegistry* self, int unused);  // 0x009368f0
void __fastcall SharedLibraryRegistry_Destruct(SharedLibraryRegistry* self, int unused);   // 0x00936740
void __fastcall DoDestroyValues(WStrVec* vec, int unused, void* begin, void* end);    // 0x0084aad0
void __fastcall RefVec_Destroy(RefVec* vec, int unused);                              // 0x00a23920

TraceServer* __cdecl Trace_GetServer();                                               // 0x009234c0
void __fastcall TraceServer_SetNames(TraceServer* self, int unused, void* name, const wchar_t* a, const wchar_t* b);  // 0x00698030

PropWatcher32* __fastcall PropWatcher32_Construct(PropWatcher32* self, int unused,
                                                  void* list, void* owner, unsigned value);  // 0x007e7260

// ---------------------------------------------------------------------------
// basic interfaces
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual void v00();   // +0x00
    virtual void v04();   // +0x04
    virtual void v08();   // +0x08
    virtual void v0c();   // +0x0c
};

struct Canvas {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(int state);                       // +0x50
};

struct IConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual bool v28();                                // +0x28
};

struct IGraphicsSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual bool v14(int width, int height, int a, int b);   // +0x14
    virtual void v18(int mode, int width, int height, int extra);  // +0x18
};

struct MessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void v14(unsigned msg, MsgData* data, int flags);   // +0x14
    virtual void v18(unsigned msg, void* object, int a, int b); // +0x18
};

struct LogTarget {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(char* line);                      // +0x20
};

struct LocaleManager {
    virtual void v00(); virtual void v04(); virtual void v08();
};

// ---------------------------------------------------------------------------
// strings / containers
// ---------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAllocator;   // +0x0c
};

struct CStr {
    char* mpBegin;         // +0x00
    char* mpEnd;           // +0x04
    char* mpCapacity;      // +0x08
    int   mAllocator;      // +0x0c
};

struct RefVec {
    void* mpBegin;         // +0x00
    void* mpEnd;           // +0x04
    void* mpCapacity;      // +0x08
    int   mAllocator;      // +0x0c
};

struct WStrVec {
    void* mpBegin;         // +0x00
    void* mpEnd;           // +0x04
    void* mpCapacity;      // +0x08
    int   mAllocator;      // +0x0c
};

struct EastlAllocHeader {
    int mAllocSize;        // dword stored immediately before an eastl allocation
};

struct Mutex { char mData[0x30]; };
struct SharedLibraryRegistry { char mData[0x50]; };
struct Viewer { char mData[0x174]; };

struct PLBase32 {
    virtual void v00();
};

struct PropWatcher32 {
    unsigned mValue;       // +0x00
    void*    mpList;       // +0x04
    void*    mpOwner;      // +0x08
    int      mField0c;     // +0x0c

    PropWatcher32* ctor(void* list, void* owner, unsigned value);
    void Read(void* list);                             // 0x007e6720
};

// ---------------------------------------------------------------------------
// resource manager / message data
// ---------------------------------------------------------------------------
struct ResLocal {
    unsigned mField00;     // +0x00 (from MsgData +0x18)
    unsigned mField04;     // +0x04 (from MsgData +0x08)
    unsigned mField08;     // +0x08 (from MsgData +0x10)
};

struct ResourceObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool v18(ResLocal* local, IRefCounted** handle);   // +0x18
};

struct ResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool v18(ResLocal* local, IRefCounted* handle, int a, int b, int c);  // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual unsigned v2c(unsigned id);                                 // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();
    virtual ResourceObj* v68(ResLocal* local);                         // +0x68
};

struct MsgData {
    unsigned mField00;     // +0x00
    unsigned mField04;     // +0x04
    unsigned mField08;     // +0x08
    unsigned mField0c;     // +0x0c
    unsigned mField10;     // +0x10
    unsigned mField14;     // +0x14
    unsigned mField18;     // +0x18
    unsigned mField1c;     // +0x1c
    unsigned mField20;     // +0x20
    unsigned mField24;     // +0x24
    unsigned mField28;     // +0x28
};

struct Telemetry {
    char mPad00[8];        // +0x00
    IRefCounted mRefCounted;  // +0x08
};

// ---------------------------------------------------------------------------
// command line
// ---------------------------------------------------------------------------
struct CommandLine {
    int FindSwitch(const wchar_t* name, int a, WStr* out, int b);  // 0x0092b300
};

// ---------------------------------------------------------------------------
// SP::cAppSystem
// ---------------------------------------------------------------------------
struct AppSys {
    void* mVtbl00;                  // +0x00
    void* mVtbl04;                  // +0x04
    void* mVtbl08;                  // +0x08
    int   mRefCount;                // +0x0c
    Canvas* mCanvas;                // +0x10
    void* mMessageServer;           // +0x14
    void* mInputManager;            // +0x18
    void* mResourceManager;         // +0x1c
    void* mAsyncResourceManager;    // +0x20
    LocaleManager* mLocaleManager;  // +0x24
    void* mIDGenerator;             // +0x28
    IRefCounted* mPropertyManager;  // +0x2c
    LogTarget* mCheatManager;       // +0x30
    IRefCounted* mAppStateManager;  // +0x34
    void* mCommandServer;           // +0x38
    IConfigManager* mConfigManager; // +0x3c
    void* mJobManager;              // +0x40
    void* mBaseThread;              // +0x44
    Telemetry* mTelemetry;          // +0x48
    void* mPackManager;             // +0x4c
    void* mGarbageMan;              // +0x50
    IRefCounted* mpDropTarget;      // +0x54
    void* mMainViewer;              // +0x58
    IRefCounted* mGraphicsSystem;   // +0x5c
    IRefCounted* mEffectsManager;   // +0x60
    IRefCounted* mEffectsParser;    // +0x64
    float mParticleDensity;         // +0x68
    float mParticleScale;           // +0x6c
    float mParticleDamping;         // +0x70
    float mLODOffset;               // +0x74
    float mLODSoftTransition;       // +0x78
    unsigned char mLODSoftFlag;     // +0x7c
    char  mPad7d[3];                // +0x7d
    float mMaxTimeDelta;            // +0x80
    int   mMaxSamples;              // +0x84
    PropWatcher32 mPropWatcher;     // +0x88
    void* mEffectCollectionIDs;     // +0x98
    void* mEffectCollections;       // +0x9c
    RefVec mRefVec;                 // +0xa0
    char  mPadB0[2];                // +0xb0
    unsigned char mFieldB2;         // +0xb2
    char  mPadB3[1];                // +0xb3
    union {
        float mAsFloat;             // +0xb4
        struct {
            unsigned char mByte;    // +0xb4
            unsigned char mPadB5;   // +0xb5
            unsigned char mByteB6;  // +0xb6
            unsigned char mPadB7;   // +0xb7
        } mAsBytes;
    } mFieldB4;
    float mFieldB8;                 // +0xb8
    int   mFieldBC;                 // +0xbc
    int   mFieldC0;                 // +0xc0
    int   mFieldC4;                 // +0xc4
    IRefCounted* mFieldC8;          // +0xc8
    IRefCounted* mFieldCC;          // +0xcc
    SharedLibraryRegistry mPluginLibraries;  // +0xd0
    int   mField120;                // +0x120
    unsigned char mField124;        // +0x124
    char  mPad125[3];               // +0x125
    WStr  mDir128;                  // +0x128
    WStr  mDir138;                  // +0x138
    WStr  mDir148;                  // +0x148
    unsigned char mField158;        // +0x158
    unsigned char mField159;        // +0x159
    char  mPad15a[2];               // +0x15a
    int   mField15c;                // +0x15c
    int   mField160;                // +0x160
    float mField164;                // +0x164
    int   mField168;                // +0x168
    int   mField16c;                // +0x16c
    unsigned char mField170;        // +0x170
    unsigned char mField171;        // +0x171
    unsigned char mField172;        // +0x172
    char  mPad173[1];               // +0x173
    WStrVec mWStrVec;               // +0x174
    char  mPad184[4];               // +0x184
    unsigned char mField188;        // +0x188
    char  mPad189[3];               // +0x189
    void* mField18c;                // +0x18c
    IRefCounted* mField190;         // +0x190
    CStr  mStr194;                  // +0x194
    CStr  mStr1a4;                  // +0x1a4
    char  mPad1b4[4];               // +0x1b4
    Mutex mMutex;                   // +0x1b8
    unsigned char mField1e8;        // +0x1e8
    unsigned char mField1e9;        // +0x1e9
};

// ---------------------------------------------------------------------------
// @ 0x007E7260  (PropWatcher32::ctor)
// ---------------------------------------------------------------------------
PropWatcher32* PropWatcher32::ctor(void* list, void* owner, unsigned value) {
    mValue = value;
    mpList = list;
    if (list)
        ((PLBase32*)list)->v00();
    mpOwner = owner;
    mField0c = 0;
    if (list)
        Read(list);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x007E72D0  (cQuitCheat::Execute)
// ---------------------------------------------------------------------------
struct Arguments {
    char HasFlag(const char* name);                                // 0x008380b0
    const char** MainArguments(int* count, int a, int b);          // 0x00838020
};
struct MsgObj {
    void* mVT;       // +0x00
    int   mRef;      // +0x04
    int   mValue;    // +0x08
    char  mPad0c[0x30 - 0x0c];
    int   mField30;  // +0x30
    char  mPad34[0x38 - 0x34];
    int   mField38;  // +0x38
};
struct QuitCheat {
    void Execute(Arguments* args);
};
void QuitCheat::Execute(Arguments* args) {
    if (args->HasFlag(gCrashFlagName))
        *(int*)0 = 0;
    int count = 0;
    const char** argv = args->MainArguments(&count, 0, 1);
    long value = 0;
    if (count > 0)
        value = atol(argv[0]);
    MsgObj* msg = (MsgObj*)operator_new(0x40, gAllocatorName, 0, 0, 0, 0);
    if (msg) {
        msg->mField30 = 0;
        msg->mVT = gVtbl13eb90c;
        msg->mRef = 0;
        msg->mVT = gVtbl13eb844;
        msg->mField38 = 0;
    }
    msg->mValue = (int)value;
    SP_MessageServer()->v18(0x153c326, msg, 0, 0);
}

// ---------------------------------------------------------------------------
// @ 0x007E70B0  (cAppSystem::HandleMessage)
// ---------------------------------------------------------------------------
bool __fastcall cAppSystemHandleMessage(AppSys* self, int unused, unsigned msg, MsgData* data) {
    (void)unused;
    if (msg > 0x255abf5u) {
        if (msg == 0xae1cfe73u)
            return true;
        return false;
    }
    if (msg == 0x255abf5u) {
        self->mFieldB2 = (data->mField08 != 0);
        return true;
    }
    if (msg == 0xf62add) {
        ResourceManager* manager = GetResourceManager();
        ResLocal local;
        local.mField00 = data->mField18;
        local.mField04 = data->mField08;
        local.mField08 = data->mField10;
        local.mField04 = manager->v2c(local.mField04);
        data->mField08 = local.mField04;
        ResourceObj* object = manager->v68(&local);
        if (object) {
            IRefCounted* handle = 0;
            if (object->v18(&local, &handle)) {
                for (int i = 10; i != 0; --i) {
                    if (manager->v18(&local, handle, data->mField28, data->mField20, 0))
                        break;
                    int milliseconds = 250;
                    ThreadSleep(&milliseconds);
                }
            }
            if (handle)
                handle->v04();
        }
        MessageServer* server = SP_MessageServer();
        if (server)
            server->v14(0xf62ade, data, 0);
        return true;
    }
    if (msg != 0x212d3e7u)
        return false;
    self->mFieldB8 = 0.0f;
    self->mFieldB4.mAsFloat = 0.0f;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007E7380  (cAppSystem::Configure)
// ---------------------------------------------------------------------------
bool __fastcall cAppSystemConfigure(AppSys* self, int unused, CommandLine* cmd) {
    (void)unused;
    union ModeFlags {
        int mDword;
        char mByte;
    };

    self->mCanvas->v50(0);
    IGraphicsSystem* graphics = GetGraphicsManager();
    if (graphics && !graphics->v14(0x280, 0x1e0, 0, 0)) {
        ReportGraphicsFailure("Could not create the Graphics Device.\nDirect X is unavailable.", 0x3ea, 2, 0);
        return false;
    }
    if (!self->mConfigManager->v28())
        return false;
    char automated = 0;
    SP_AutomateEntry(cmd, &automated);
    if (automated)
        return false;

    void* properties = gAppProperties;
    int width = 800;
    int height = 600;
    int third = 0;
    ModeFlags mode;
    mode.mDword = 0xCCCCCC00;
    int minWidth = 0;
    int minHeight = 0;
    TryGetUIntProperty(properties, 0x38d0a06, &width);
    TryGetUIntProperty(properties, 0x38d0a07, &height);
    TryGetUIntProperty(properties, 0x38d0a08, &third);
    GetBoolProperty(properties, 0x38d0a09, &mode.mByte);
    TryGetUIntProperty(properties, 0x46c0c15, &minWidth);
    TryGetUIntProperty(properties, 0x46c0c16, &minHeight);

    WStr sizeSwitch;
    sizeSwitch.mpBegin = (wchar_t*)gEmptyString;
    sizeSwitch.mpEnd = (wchar_t*)gEmptyString;
    sizeSwitch.mpCapacity = (wchar_t*)gEmptyString + 1;
    int parsedWidth;
    int parsedHeight;
    if (cmd->FindSwitch(L"r", 0, &sizeSwitch, 0) != -1 &&
        swscanf(sizeSwitch.mpBegin, L"%dx%d", &parsedWidth, &parsedHeight) == 2) {
        width = parsedWidth;
        height = parsedHeight;
    }
    if (width < minWidth || height < minHeight) {
        width = minWidth;
        height = minHeight;
    }
    if (cmd->FindSwitch(L"w", 0, 0, 0) != -1)
        mode.mByte = 0;
    if (cmd->FindSwitch(L"f", 0, 0, 0) != -1)
        mode.mByte = 1;
    if (graphics)
        graphics->v18(mode.mDword, width, height, third);
    self->mCanvas->v50(1);

    Viewer viewer;
    Viewer_Construct(&viewer, 0);
    Viewer_Init(&viewer, 0, false);
    if (ResetVertexShader()) {
        Viewer_Clear(&viewer, 0, 7);
        RestoreVertexShader();
    }
    ShowRaster(gDefaultCameraRaster);
    Viewer_Run(&viewer, 0);
    Viewer_Destroy(&viewer, 0);
    if ((((char*)sizeSwitch.mpCapacity - (char*)sizeSwitch.mpBegin) & ~1) > 2 && sizeSwitch.mpBegin)
        operator_delete__(sizeSwitch.mpBegin);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007E7630  (cAppSystem::cAppSystem)
// ---------------------------------------------------------------------------
AppSys* __fastcall cAppSystemCtor(AppSys* self, int unused) {
    (void)unused;
    self->mVtbl04 = gVtbl13eb384;
    self->mVtbl08 = gVtbl13ef094;
    self->mRefCount = 0;
    self->mVtbl00 = gVtbl1413ae0;
    self->mVtbl04 = gVtbl1413ad0;
    self->mVtbl08 = gVtbl1413acc;

    self->mCanvas = 0;
    self->mMessageServer = 0;
    self->mInputManager = 0;
    self->mResourceManager = 0;
    self->mLocaleManager = 0;
    self->mIDGenerator = 0;
    self->mPropertyManager = 0;
    self->mCheatManager = 0;
    self->mAppStateManager = 0;
    self->mCommandServer = 0;
    self->mConfigManager = 0;
    self->mJobManager = 0;
    self->mBaseThread = 0;
    self->mTelemetry = 0;
    self->mpDropTarget = 0;
    self->mMainViewer = 0;
    self->mGraphicsSystem = 0;
    self->mEffectsManager = 0;
    self->mEffectsParser = 0;

    self->mParticleDensity = 1.0f;
    self->mParticleScale = 1.0f;
    self->mParticleDamping = 0.9f;
    self->mLODOffset = 0.0f;
    self->mLODSoftTransition = 1.0f;
    self->mLODSoftFlag = 1;
    self->mMaxTimeDelta = 0.4f;
    self->mMaxSamples = 0;

    PropWatcher32_Construct(&self->mPropWatcher, 0, gWatcherList, (void*)0x3ebeecc, 1);

    self->mEffectCollectionIDs = gVtbl1413914;
    self->mEffectCollections = gVtbl141391c;
    self->mRefVec.mpBegin = 0;
    self->mRefVec.mpEnd = 0;
    self->mRefVec.mpCapacity = 0;

    self->mFieldB4.mAsBytes.mByte = 0;
    self->mFieldB4.mAsBytes.mByteB6 = 0;
    self->mFieldB8 = 0.0f;
    self->mFieldBC = 0;
    self->mFieldC0 = 0;
    self->mFieldC4 = 0;
    self->mFieldC8 = 0;
    self->mFieldCC = 0;

    SharedLibraryRegistry_Construct(&self->mPluginLibraries, 0);
    self->mField120 = 0;
    self->mField124 = 0;

    self->mDir128.mpBegin = (wchar_t*)gEmptyString;
    self->mDir128.mpEnd = (wchar_t*)gEmptyString;
    self->mDir128.mpCapacity = (wchar_t*)gEmptyString + 1;

    self->mDir138.mpBegin = 0;
    self->mDir138.mpEnd = 0;
    self->mDir138.mpCapacity = 0;
    WStr_RangeInitialize(&self->mDir138, 0, L"My Spore Creations/");
    self->mDir148.mpBegin = 0;
    self->mDir148.mpEnd = 0;
    self->mDir148.mpCapacity = 0;
    WStr_RangeInitialize(&self->mDir148, 0, L"Spore");

    self->mField158 = 0;
    self->mField159 = 0;
    self->mField15c = 0;
    self->mField160 = 0;
    self->mField164 = 1.0f;
    self->mField168 = 0;
    self->mField16c = 0;
    self->mField170 = 0;
    self->mField171 = 0;
    self->mField172 = 0;
    self->mWStrVec.mpBegin = 0;
    self->mWStrVec.mpEnd = 0;
    self->mWStrVec.mpCapacity = 0;
    self->mField188 = 0;
    self->mField18c = 0;
    self->mField190 = 0;

    self->mStr194.mpBegin = gEmptyString;
    self->mStr194.mpEnd = gEmptyString;
    self->mStr194.mpCapacity = gEmptyString + 1;
    self->mStr1a4.mpBegin = gEmptyString;
    self->mStr1a4.mpEnd = gEmptyString;
    self->mStr1a4.mpCapacity = gEmptyString + 1;

    Mutex_Construct(&self->mMutex, 0, 0, true);
    self->mField1e8 = 0;
    self->mField1e9 = 1;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x007E78D0  (cAppSystem::~cAppSystem)
// ---------------------------------------------------------------------------
void __fastcall cAppSystemDtor(AppSys* self, int unused) {
    (void)unused;
    self->mVtbl00 = gVtbl1413ae0;
    self->mVtbl04 = gVtbl1413ad0;
    self->mVtbl08 = gVtbl1413acc;

    Mutex_Destruct(&self->mMutex, 0);

    if (((char*)self->mStr1a4.mpCapacity - (char*)self->mStr1a4.mpBegin) > 1 && self->mStr1a4.mpBegin)
        operator_delete__(self->mStr1a4.mpBegin);
    if (((char*)self->mStr194.mpCapacity - (char*)self->mStr194.mpBegin) > 1 && self->mStr194.mpBegin)
        operator_delete__(self->mStr194.mpBegin);

    if (self->mField190)
        self->mField190->v04();
    operator_delete__(self->mField18c);

    DoDestroyValues(&self->mWStrVec, 0, self->mWStrVec.mpBegin, self->mWStrVec.mpEnd);
    void* vecBegin = self->mWStrVec.mpBegin;
    if (vecBegin && ((EastlAllocHeader*)vecBegin)[-1].mAllocSize != 0)
        operator_delete__(vecBegin);

    if ((((char*)self->mDir148.mpCapacity - (char*)self->mDir148.mpBegin) & ~1) > 2 && self->mDir148.mpBegin)
        operator_delete__(self->mDir148.mpBegin);
    if ((((char*)self->mDir138.mpCapacity - (char*)self->mDir138.mpBegin) & ~1) > 2 && self->mDir138.mpBegin)
        operator_delete__(self->mDir138.mpBegin);
    if ((((char*)self->mDir128.mpCapacity - (char*)self->mDir128.mpBegin) & ~1) > 2 && self->mDir128.mpBegin)
        operator_delete__(self->mDir128.mpBegin);

    SharedLibraryRegistry_Destruct(&self->mPluginLibraries, 0);

    if (self->mFieldCC)
        self->mFieldCC->v04();
    if (self->mFieldC8)
        self->mFieldC8->v04();
    RefVec_Destroy(&self->mRefVec, 0);
    if (self->mPropWatcher.mpList)
        ((IRefCounted*)self->mPropWatcher.mpList)->v04();
    if (self->mEffectsParser)
        self->mEffectsParser->v04();
    if (self->mEffectsManager)
        self->mEffectsManager->v0c();
    if (self->mGraphicsSystem)
        self->mGraphicsSystem->v04();
    if (self->mTelemetry)
        self->mTelemetry->mRefCounted.v04();
    if (self->mConfigManager)
        self->mConfigManager->v04();
    if (self->mAppStateManager)
        self->mAppStateManager->v04();
    if (self->mCheatManager)
        self->mCheatManager->v04();
    if (self->mPropertyManager)
        self->mPropertyManager->v04();
    if (self->mLocaleManager)
        self->mLocaleManager->v08();

    self->mVtbl08 = gVtbl13ef094;
    self->mVtbl04 = gVtbl13eb394;
    self->mVtbl00 = gVtbl13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x007E7B50  (SP::cAppSystem logging-directory setup)
// ---------------------------------------------------------------------------
void __fastcall FUN_007e7b50(AppSys* self, int unused) {
    (void)unused;
    TraceServer* server = Trace_GetServer();
    if (!server)
        return;

    WStr dir;
    dir.mpBegin = (wchar_t*)gEmptyString;
    dir.mpEnd = (wchar_t*)gEmptyString;
    dir.mpCapacity = (wchar_t*)gEmptyString + 1;
    GetDirString(0xa0214f, &dir, 0);

    WStr path;
    PathJoin(&path, &dir, L"LocalLogging.txt");
    if (!FileExists(path.mpBegin)) {
        WStr fallback;
        WStr* joined = PathJoin(&fallback, &dir, L"Logging.txt");
        if (joined != &path)
            WStr_Assign(&path, 0, joined->mpBegin, joined->mpEnd);
        if ((((char*)fallback.mpCapacity - (char*)fallback.mpBegin) & ~1) > 2 && fallback.mpBegin)
            operator_delete__(fallback.mpBegin);
    }
    if (FileExists(path.mpBegin)) {
        CStr line;
        line.mpBegin = gEmptyString;
        line.mpEnd = gEmptyString;
        line.mpCapacity = gEmptyString + 1;
        CStrSprintf(&line, "sinclude \"%ls\"", path.mpBegin);
        self->mCheatManager->v20(line.mpBegin);
        if (((char*)line.mpCapacity - (char*)line.mpBegin) > 1 && line.mpBegin)
            operator_delete__(line.mpBegin);
    }
    TraceServer_SetNames(server, 0, gEmptyWatcherName, dir.mpBegin, L"Spore");
    if ((((char*)path.mpCapacity - (char*)path.mpBegin) & ~1) > 2 && path.mpBegin)
        operator_delete__(path.mpBegin);
    if ((((char*)dir.mpCapacity - (char*)dir.mpBegin) & ~1) > 2 && dir.mpBegin)
        operator_delete__(dir.mpBegin);
}
