// Slice s007e7d00: SP::cAppSystem::SetupDirectories / LoadPlugins / vector<AutoRefCount>::DoInsert.
// Self-contained (does not use ../s007e5220 header; its cAppSystem offsets differ from the code here).
#include "types.h"

extern "C" {
void* __cdecl memcpy(void*, const void*, size_t);
__declspec(dllimport) int __cdecl _wcsnicmp(const wchar_t*, const wchar_t*, size_t);
}
void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);  // 0x00f473a0
void __cdecl operator_delete__(void* p);  // 0x00f47380

// ---- minimal EASTL wstring (12 bytes used here: begin/end/capacity) ----
extern wchar_t gEmptyWStr[2];  // 0x1667bac: shared empty-string sentinel
enum NoInit { kNoInit };
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WString() : mpBegin(gEmptyWStr), mpEnd(gEmptyWStr), mpCapacity(gEmptyWStr + 1) {}
    WString(NoInit) {}
    WString(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    WString(const WString& o);  // defined below (EASTL copy ctor, "App" allocator)
    ~WString() {
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
WString* __cdecl StrConcat(WString* out, const WString* a, const wchar_t* b);  // 0x57cba0 (operator+)

struct FilePath {
    wchar_t mPath[0x208];
    FilePath(const wchar_t* p);                                    // 0x930f60
    void GetFileName(wchar_t* out, int n);                         // 0x930cb0
    void GetDriveAndDirectory(wchar_t* out, int n);                // 0x930d20
};

struct CommandLine {
    const wchar_t** GetArgument(int idx);                          // 0x92b1b0
    int FindSwitch(const wchar_t* name, int a, WString* out, int b);  // 0x92b300
};

namespace EA { namespace IO {
namespace File { bool Exists(const wchar_t* path); }
namespace Directory { void GetCurrentWorkingDirectory(wchar_t* out); }
} }

// ---- SP helpers (cdecl) ----
void __cdecl SetDirFromID(uint32_t id, const wchar_t* path, int flags);      // 0x688bb0
bool __cdecl GetDirOverride(uint32_t id, WString* out, int flags);            // 0x688830
const wchar_t* __cdecl GetDirFromID(uint32_t id);                             // 0x6886b0
const wchar_t* __cdecl GetDataDir();                                          // 0x688cb0
const wchar_t* __cdecl FUN_00688cd0();                                        // 0x688cd0
bool __cdecl FindDirectoryUp(WString* path);                                  // 0x6baec0
bool __cdecl RegistryGetString(uint32_t hive, const wchar_t* key, const wchar_t* val, WString* out);  // 0x6ab840
bool __cdecl GetElemWStr(int idx, WString* out);                              // 0x686250
bool __cdecl FUN_00685520(bool b);                                            // 0x685520
void __cdecl FUN_009309b0(wchar_t* out, const wchar_t* name, const wchar_t* dir, int n);  // 0x9309b0
void __cdecl GetSystemPath(int id, wchar_t* out, int flags);                  // 0x9323c0
void __cdecl EnsureDirectoryExists(const wchar_t* path);                      // 0x932ae0
extern const wchar_t* gRegSporeKey;      // 0x153f850 L"SOFTWARE\\Electronic Arts\\SPORE"
extern const wchar_t* gRegDataDirValue;  // 0x153f854 L"DataDir"
extern const wchar_t* gDllMask;          // 0x153f84c L"*.dll"

// EA::IO entry iteration (0x92e730 / 0x92e8e0 / 0x92e9b0)
const wchar_t* __cdecl EntryFindFirst(const wchar_t* dir, const wchar_t* mask, int a, int b);  // 0x0092e730
int __cdecl EntryFindNext(const wchar_t* entry, int a);  // 0x0092e8e0
void __cdecl EntryFindFinish(const wchar_t* entry);  // 0x0092e9b0

extern const char kEastlAllocFile[];  // 0x013ebb38 "...EASTL/allocator.h"
inline WString::WString(const WString& o) {
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

struct cAppSystem {
    char pad00[0xd0];
    PluginRegistry mPluginLibraries;  // +0xd0
    char pad_d4[0x138 - 0xd4];
    WString mPublicDirName;   // +0x138
    uint32_t pad_a;           // +0x144 (allocator)
    WString mPrivateDirName;  // +0x148
    uint32_t pad_b;           // +0x154
    bool mMinimize;           // +0x158
    bool mToggleFullscreen;   // +0x159
    char pad_15a[0x188 - 0x15a];
    bool mServerCheatFlag;    // +0x188

    void SetupDirectories(CommandLine* cmd);
    bool LoadPlugins();
};

// @ 0x007E7D00  (SP::cAppSystem::SetupDirectories)
void cAppSystem::SetupDirectories(CommandLine* cmd) {
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
    WString candidate(cwdDir);
    candidate.appendRaw(exeName);
    FilePath* chosen = EA::IO::File::Exists(candidate.mpBegin) ? &cwdPath : &exePath;
    chosen->GetDriveAndDirectory(exeDir, 0x104);
    SetDirFromID(0xa0214a, exeDir, 0);

    WString dataDir;
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

    WString localeDir;
    {
        WString tmp(kNoInit);
        WString* r = StrConcat(&tmp, &dataDir, L"Locale/");
        if (r != &localeDir) localeDir.assign(r->mpBegin, r->mpEnd);
    }
    SetDirFromID(0x45962cc, localeDir.mpBegin, 0);

    WString configDir;
    if (useRegistry) {
        WString reg;
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

    WString userDir(L"UserData/");
    mToggleFullscreen = false;
    if (cmd->FindSwitch(L"devDirs", 0, 0, 0) != -1) mToggleFullscreen = true;
    if (cmd->FindSwitch(L"shipDirs", 0, 0, 0) != -1) mToggleFullscreen = false;
    if (cmd->FindSwitch(L"userDataDir", 0, &userDir, 0) == -1) {
        if (mToggleFullscreen) {
            userDir.assignC(L"UserData/");
            WString tmp(kNoInit);
            WString* r = StrConcat(&tmp, &dataDir, L"../UserData/");
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
        WString appData(sysPath);
        appData.append(mPrivateDirName.mpBegin, mPrivateDirName.mpEnd);
        SetDirFromID(0xa02151, appData.mpBegin, 0);
    }

    WString dbDir;
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

    WString tempDir;
    GetDirOverride(0xa02151, &tempDir, 0);
    tempDir.appendRaw(L"Temp/");
    SetDirFromID(0x60ba02f, tempDir.mpBegin, 0);
    EnsureDirectoryExists(tempDir.mpBegin);
    if (cmd->FindSwitch(L"mce", 0, 0, 0) != -1) mServerCheatFlag = true;
}

// @ 0x007E8760  (SP::cAppSystem::LoadPlugins)
bool cAppSystem::LoadPlugins() {
    WString dir;
    if (!GetDirOverride(0x39b84d3, &dir, 0)) dir.assignC(FUN_00688cd0());
    const wchar_t* name = EntryFindFirst(dir.mpBegin, gDllMask, 0, 0);
    if (name) {
        do {
            if (_wcsnicmp(name, L"msvc", 4) != 0) {
                WString full(dir);
                full.appendRaw(name);
                mPluginLibraries.Load(full.mpBegin, 1);
            }
        } while (EntryFindNext(name, 0));
        EntryFindFinish(name);
    }
    return true;
}

// @ 0x007E89C0  (eastl::vector<AutoRefCount<T>>::DoInsertValue: insert one element at position)
struct RCObj { virtual int AddRef(); virtual int Release(); };
RCObj** __cdecl RCCopyBackward(RCObj** first, RCObj** last, RCObj** destEnd);  // 0xac97a0

struct RCVec {
    RCObj** mpBegin;
    RCObj** mpEnd;
    RCObj** mpCapacity;
    void DoInsertValue(RCObj** position, RCObj* const* value);
};

void RCVec::DoInsertValue(RCObj** position, RCObj* const* value) {
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
