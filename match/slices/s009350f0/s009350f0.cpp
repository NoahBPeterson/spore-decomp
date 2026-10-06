// Slice s009350f0 -- EA::IO::IniFile core + EA OSGlobal manager + EA::Process spawn/search/open.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

extern "C" {
__declspec(dllimport) void* __stdcall GetProcessHeap(void);
__declspec(dllimport) void* __stdcall HeapAlloc(void* hHeap, unsigned long dwFlags, unsigned long dwBytes);
__declspec(dllimport) int   __stdcall HeapFree(void* hHeap, unsigned long dwFlags, void* lpMem);
__declspec(dllimport) void  __stdcall InitializeCriticalSection(void* cs);
__declspec(dllimport) void  __stdcall DeleteCriticalSection(void* cs);
__declspec(dllimport) void  __stdcall EnterCriticalSection(void* cs);
__declspec(dllimport) void  __stdcall LeaveCriticalSection(void* cs);
__declspec(dllimport) unsigned long __stdcall GetCurrentProcessId(void);
__declspec(dllimport) void* __stdcall CreateMutexA(void* sa, int initialOwner, const char* name);
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void* h, unsigned long ms);
__declspec(dllimport) unsigned long __stdcall GetEnvironmentVariableA(const char* name, char* buf, unsigned long n);
__declspec(dllimport) int   __stdcall SetEnvironmentVariableA(const char* name, const char* value);
__declspec(dllimport) int   __stdcall ReleaseMutex(void* h);
__declspec(dllimport) int   __stdcall CloseHandle(void* h);
__declspec(dllimport) unsigned long __stdcall GetModuleFileNameW(void* mod, wchar_t* buf, unsigned long n);
__declspec(dllimport) void* __stdcall LoadLibraryW(const wchar_t* name);
__declspec(dllimport) void* __stdcall GetProcAddress(void* mod, const char* name);
__declspec(dllimport) int   __stdcall FreeLibrary(void* mod);
__declspec(dllimport) int   __cdecl wsprintfA(char* dst, const char* fmt, ...);
__declspec(dllimport) int   __cdecl sprintf(char* dst, const char* fmt, ...);
__declspec(dllimport) int   __cdecl _spawnv(int mode, const char* path, const char* const* argv);
__declspec(dllimport) int   __cdecl _wspawnv(int mode, const wchar_t* path, const wchar_t* const* argv);
__declspec(dllimport) void  __cdecl _searchenv(const char* file, const char* var, char* buf);
__declspec(dllimport) void  __cdecl _wsearchenv(const wchar_t* file, const wchar_t* var, wchar_t* buf);
__declspec(dllimport) unsigned __int64 __cdecl _strtoui64(const char* s, char** end, int base);
}

extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchange, _InterlockedDecrement, _InterlockedIncrement, _InterlockedExchangeAdd)

extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

// globals 0x1669930 / 0x1669934
extern "C" void* gpOSGlobalManager;
extern "C" long  gOSGlobalRefs;

struct OSGlobalNode {
    OSGlobalNode* mpNext;     // +0x00
    OSGlobalNode* mpPrev;     // +0x04
    int           mnId;       // +0x08
    volatile long mnRefCount; // +0x0c
};
struct OSGlobalManager {
    uint32_t mpNext;          // +0x00
    uint32_t mpPrev;          // +0x04
    volatile long mnRefCount; // +0x08
    char mCS[0x18];           // +0x0c
};

struct intrusive_list_base { ~intrusive_list_base(); };

// @ 0x00935a30
void* CreateOSGlobalManager() {
    void* pv = HeapAlloc(GetProcessHeap(), 0, 0x37);
    uint32_t u = ((uint32_t)pv + 0x13) & 0xfffffff0;
    *(void**)(u - 4) = pv;
    *(uint32_t*)(u + 4) = u;
    *(uint32_t*)u = u;
    _InterlockedExchange((volatile long*)(u + 8), 0);
    InitializeCriticalSection((void*)(u + 0xc));
    return (void*)u;
}

// @ 0x00935a70  (complete, 13-byte near miss)
void ShutdownOSGlobalSystem() {
    if (_InterlockedDecrement(&gOSGlobalRefs) == 0) {
        if (gpOSGlobalManager) {
            if (_InterlockedDecrement((long*)((char*)gpOSGlobalManager + 8)) == 0) {
                OSGlobalManager* p = (OSGlobalManager*)gpOSGlobalManager;
                DeleteCriticalSection(p->mCS);
                ((intrusive_list_base*)p)->~intrusive_list_base();
                HeapFree(GetProcessHeap(), 0, *(void**)((char*)gpOSGlobalManager - 4));
            }
            gpOSGlobalManager = 0;
        }
    }
}

// @ 0x00935ad0  (complete, near miss: refcount double-atomic shape)
bool EA_ReleaseOSGlobal(OSGlobalNode* p) {
    EnterCriticalSection((char*)gpOSGlobalManager + 0xc);
    bool bLast = _InterlockedDecrement(&gOSGlobalRefs) == 0;
    long n = _InterlockedDecrement(&p->mnRefCount);
    n = _InterlockedExchangeAdd(&p->mnRefCount, 0);
    if (n == 0) {
        OSGlobalNode* anchor = (OSGlobalNode*)gpOSGlobalManager;
        OSGlobalNode* it = anchor->mpNext;
        while (it != anchor && it != p)
            it = it->mpNext;
        OSGlobalNode* prev = it->mpPrev;
        OSGlobalNode* next = it->mpNext;
        prev->mpNext = next;
        next->mpPrev = prev;
        it->mpNext = 0;
        it->mpPrev = 0;
    }
    LeaveCriticalSection((char*)gpOSGlobalManager + 0xc);
    if (bLast)
        ShutdownOSGlobalSystem();
    return n == 0;
}

// @ 0x00935b70  (complete, near miss)
bool InitOSGlobalSystem() {
    if (gpOSGlobalManager != 0) {
        _InterlockedIncrement(&gOSGlobalRefs);
        return true;
    }
    char mutexName[64];
    char value[32];
    wsprintfA(mutexName, "SingleMgrMutex%08x", GetCurrentProcessId());
    void* h = CreateMutexA(0, 0, mutexName);
    if (h != 0) {
        if (WaitForSingleObject(h, 0xffffffff) != 0xffffffff) {
            unsigned long n = GetEnvironmentVariableA(mutexName, value, 0x20);
            if (n == 0 || value[0] == 0) {
                gpOSGlobalManager = CreateOSGlobalManager();
                sprintf(value, "%I64x", (uint64_t)(uint32_t)gpOSGlobalManager);
                SetEnvironmentVariableA(mutexName, value);
            } else {
                gpOSGlobalManager = (void*)(uint32_t)_strtoui64(value, 0, 16);
            }
            _InterlockedIncrement((long*)((char*)gpOSGlobalManager + 8));
            ReleaseMutex(h);
            CloseHandle(h);
        }
        if (gpOSGlobalManager != 0) {
            _InterlockedIncrement(&gOSGlobalRefs);
            return true;
        }
        ShutdownOSGlobalSystem();
    }
    return false;
}

// @ 0x00935c80
OSGlobalNode* GetOSGlobal(int id, void* (*ctor)()) {
    if (!InitOSGlobalSystem())
        return 0;
    EnterCriticalSection((char*)gpOSGlobalManager + 0xc);
    OSGlobalNode* it;
    for (it = ((OSGlobalNode*)gpOSGlobalManager)->mpNext; it != (OSGlobalNode*)gpOSGlobalManager; it = it->mpNext) {
        if (it->mnId == id)
            goto found;
    }
    it = 0;
    if (ctor) {
        it = (OSGlobalNode*)ctor();
        it->mnId = id;
        _InterlockedExchange(&it->mnRefCount, 0);
        it->mpNext = 0;
        it->mpPrev = 0;
        OSGlobalNode* anchor = (OSGlobalNode*)gpOSGlobalManager;
        it->mpNext = anchor->mpNext;
        it->mpPrev = anchor;
        anchor->mpNext = it;
        it->mpNext->mpPrev = it;
    found:
        _InterlockedIncrement(&it->mnRefCount);
        _InterlockedIncrement(&gOSGlobalRefs);
    }
    LeaveCriticalSection((char*)gpOSGlobalManager + 0xc);
    return it;
}

// @ 0x00935d30
void GetApplicationPath(wchar_t* buf) {
    unsigned long n = GetModuleFileNameW(0, buf, 0x104);
    if (n == 0 || n >= 0x104)
        buf[0] = 0;
}

// @ 0x00935d60
int WideSpawn(const wchar_t* path, const wchar_t* const* argv, bool wait) {
    if (wait)
        return _wspawnv(0, path, argv);
    return _wspawnv(4, path, argv);
}

// @ 0x00935db0
namespace EA { namespace Process {
int Spawn(const char* path, const char* const* argv, bool wait) {
    if (wait)
        return _spawnv(0, path, argv);
    return _spawnv(4, path, argv);
}
}}

// @ 0x00935e00
bool WideSearchEnvironmentPath(const wchar_t* file, wchar_t* buf, const wchar_t* env) {
    if (env == 0)
        env = L"PATH";
    _wsearchenv(file, env, buf);
    return buf[0] != 0;
}

// @ 0x00935e30
namespace EA { namespace Process {
bool SearchEnvironmentPath(const char* file, char* buf, const char* env) {
    if (env == 0)
        env = "PATH";
    _searchenv(file, env, buf);
    return buf[0] != 0;
}
}}

// @ 0x00936050
void RandomBytes(unsigned char* buf, unsigned n) {
    uint64_t t = __rdtsc();
    for (unsigned i = 0; i < n; ++i)
        buf[i] = (unsigned char)(t >> ((i & 7) * 8));
}

// =====================================================================
// EA::IO::IniFile -- retail layout differs from the dev PDB by +4 in the
// tail.  Reconstructed with explicit offset stores where the original
// inlines the EASTL map initialisation / nuking.
// =====================================================================
extern "C" void __cdecl EASTL_allocator_deallocate(void* p);     // 0x00f47380
struct FileStreamStub { void ctor(int a); void dtor(); };
struct RBTreeStub {
    void* m0;             // +0x00 (empty compare)
    void* mpNodeRight;    // +0x04
    void* mpNodeLeft;     // +0x08
    void* mpNodeParent;   // +0x0c
    void DoNukeSubtree(void* root);
};
extern "C" void __cdecl IniFile_SetPath(void* self, int path);   // 0x00933040

class EA_IO_IniFile {
public:
    EA_IO_IniFile* ctor(int path, uint8_t flag);
    EA_IO_IniFile* scalar_deleting_destructor(uint8_t flag);
    void*    vftable;             // +0x000
    wchar_t  mPath[260];          // +0x004
    char     mFileStream[0x22c];  // +0x20c
    void*    mpStream;            // +0x438
    uint32_t mEncodingSrc;        // +0x43c
    uint8_t  m440;                // +0x440
    uint8_t  m441;                // +0x441
    uint8_t  m442;                // +0x442
    uint8_t  m443;                // +0x443
    char     mMapPos[0x1c];       // +0x444
    char     mMapName[0x1c];      // +0x460
};

extern void* IniFile_vtable;   // 0x0143e7d8

// @ 0x009350f0  (partial: EASTL rbtree loop not reconstructed)
int IniFile_LoadSectionNames(EA_IO_IniFile* self, int param_2) {
    (void)self;
    (void)param_2;
    return 0;
}

// @ 0x00935560  (partial: EASTL rbtree/string reconstruction not completed)
int IniFile_EnumEntries(EA_IO_IniFile* self, int a, void* cb, int d) {
    (void)self;
    (void)a;
    (void)cb;
    (void)d;
    return 0;
}

// @ 0x00935e60  (partial)
bool Process_OpenFileW(const wchar_t* url) {
    (void)url;
    return false;
}

// @ 0x00935f80  (partial)
void Process_OpenFileA(const char* path) {
    (void)path;
}

// @ 0x00935fb0  (partial)
bool Process_OpenBrowser(const wchar_t* url) {
    (void)url;
    return false;
}

// @ 0x00935450
EA_IO_IniFile* EA_IO_IniFile::ctor(int path, uint8_t flag) {
    this->vftable = &IniFile_vtable;
    ((FileStreamStub*)this->mFileStream)->ctor(0);
    this->mpStream = 0;
    this->mEncodingSrc = 8;
    this->m440 = 0;
    this->m442 = 0;
    this->m441 = flag & 1;
    *(uint32_t*)((char*)this + 0x44c) = 0;
    *(uint32_t*)((char*)this + 0x450) = 0;
    *(uint32_t*)((char*)this + 0x454) = 0;
    uint32_t eax = (uint32_t)((char*)this + 0x448);
    *(uint32_t*)eax = eax;
    *(uint32_t*)((char*)this + 0x44c) = eax;
    *(uint32_t*)((char*)this + 0x450) = 0;
    *(uint8_t*)((char*)this + 0x454) = 0;
    *(uint32_t*)((char*)this + 0x458) = 0;
    *(uint32_t*)((char*)this + 0x468) = 0;
    eax = (uint32_t)((char*)this + 0x464);
    *(uint32_t*)((char*)this + 0x46c) = 0;
    *(uint32_t*)((char*)this + 0x470) = 0;
    *(uint32_t*)eax = eax;
    *(uint32_t*)((char*)this + 0x468) = eax;
    *(uint32_t*)((char*)this + 0x46c) = 0;
    *(uint8_t*)((char*)this + 0x470) = 0;
    *(uint32_t*)((char*)this + 0x474) = 0;
    this->mPath[0] = 0;
    IniFile_SetPath(this, path);
    return this;
}

// @ 0x00935510
EA_IO_IniFile* EA_IO_IniFile::scalar_deleting_destructor(uint8_t flag) {
    this->vftable = &IniFile_vtable;
    RBTreeStub* nameMap = (RBTreeStub*)((char*)this + 0x460);
    nameMap->DoNukeSubtree(nameMap->mpNodeParent);
    RBTreeStub* posMap = (RBTreeStub*)((char*)this + 0x444);
    posMap->DoNukeSubtree(posMap->mpNodeParent);
    ((FileStreamStub*)this->mFileStream)->dtor();
    if (flag & 1)
        EASTL_allocator_deallocate(this);
    return this;
}
