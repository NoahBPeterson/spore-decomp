// Slice s009350f0 -- EA::IO::IniFile core + EA OSGlobal manager + EA::Process spawn/search/open.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <string.h>

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

class EA_IO_IniFile {
public:
    EA_IO_IniFile* ctor(int path, uint8_t flag);
    EA_IO_IniFile* scalar_deleting_destructor(uint8_t flag);
    bool     SetPath(const wchar_t* path);   // 0x00933040
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

// =====================================================================
// eastl-style wide string shared by the Process open helpers and IniFile.
// =====================================================================
extern wchar_t gEmptyWString[];   // 0x01667bac

const wchar_t* __cdecl CharTypeStringFindFirstNotOf(const wchar_t* p1Begin, const wchar_t* p1End,
                                                    const wchar_t* p2Begin, const wchar_t* p2End);  // 0x005497e0
extern "C" __declspec(dllimport) int __cdecl tolower(int);

struct WString {
    typedef unsigned size_type;
    static const size_type npos = (size_type)-1;

    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;

    WString() {
        mpBegin = gEmptyWString;
        mpEnd = gEmptyWString;
        mpCapacity = gEmptyWString + 1;
    }
    WString(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) {
        RangeInitialize(p);
    }
    ~WString() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }

    static size_type CharStrlen(const wchar_t* p) {
        const wchar_t* q = p;
        while (*q) ++q;
        return (size_type)(q - p);
    }

    void RangeInitialize(const wchar_t* p);                          // 0x00579a90
    WString& assign(const wchar_t* first, const wchar_t* last);      // 0x00423650
    void make_lower();                                               // 0x005e8e80
    void rtrim();                                                    // 0x005541e0
    int  find(const wchar_t* p, size_type position);                 // 0x00608340
    void insert(wchar_t* position, const wchar_t* first, const wchar_t* last);  // 0x005f7da0
    void append(const wchar_t* first, const wchar_t* last);          // 0x00429580

    void insert(wchar_t* position, const wchar_t* p) {
        insert(position, p, p + CharStrlen(p));
    }
    void append(const wchar_t* p) {
        append(p, p + CharStrlen(p));
    }

    size_type find_first_not_of(const wchar_t* p, size_type position, size_type n) const {
        if (position <= (size_type)(mpEnd - mpBegin)) {
            const wchar_t* result = CharTypeStringFindFirstNotOf(mpBegin + position, mpEnd, p, p + n);
            if (result != mpEnd)
                return (size_type)(result - mpBegin);
        }
        return npos;
    }
    size_type find_first_not_of(const wchar_t* p) const {
        return find_first_not_of(p, 0, CharStrlen(p));
    }
    size_type find_first_not_of(const wchar_t* p, size_type position) const;  // 0x00579af0

    WString& erase(size_type position, size_type n) {
        const size_type length = (size_type)(mpEnd - mpBegin);
        if (position < length) {
            size_type count = n;
            if (count > length - position)
                count = length - position;
            wchar_t* dest = mpBegin + position;
            wchar_t* src = dest + count;
            if (src != dest) {
                memmove(dest, src, (size_type)(mpEnd - src + 1) * sizeof(wchar_t));
                mpEnd -= count;
            }
        }
        return *this;
    }
};

inline void* operator new(unsigned int, void* p) { return p; }

struct ArrayCookie { uint32_t mSize; };   // operator new[] cookie before the payload

// =====================================================================
// EA::Process open helpers
// =====================================================================
__declspec(dllimport) unsigned __stdcall ShellExecuteW(void* hwnd, const wchar_t* op,
                                                      const wchar_t* file, const wchar_t* params,
                                                      const wchar_t* dir, int show);
extern "C" void* gShell32Module;   // 0x01669940
typedef unsigned (__stdcall* ShellExecuteWPtr)(void*, const wchar_t*, const wchar_t*,
                                               const wchar_t*, const wchar_t*, int);
extern "C" ShellExecuteWPtr gShellExecuteWPtr;   // 0x0166993c

int __cdecl ConvertString8ToWide(wchar_t* dst, int dstLen, const char* src, int srcLen);  // 0x0093cf60

namespace EA { namespace Process {

// @ 0x00935e60
bool OpenFile(const wchar_t* path) {
    WString temp(path);
    unsigned result = 0;
    gShell32Module = LoadLibraryW(L"shell32.dll");
    if (gShell32Module)
        gShellExecuteWPtr = (ShellExecuteWPtr)GetProcAddress(gShell32Module, "ShellExecuteW");
    if (gShellExecuteWPtr) {
        if (temp.find(L"http://", 0) == 0) {
            temp.insert(temp.mpBegin, L"url:");
            result = gShellExecuteWPtr(0, L"open", temp.mpBegin, 0, 0, 1);
        } else {
            result = gShellExecuteWPtr(0, L"open", path, 0, 0, 1);
        }
    }
    if (gShell32Module)
        FreeLibrary(gShell32Module);
    return result > 0x20;
}

// @ 0x00935f80
void OpenFile(const char* path) {
    wchar_t buffer[260];
    ConvertString8ToWide(buffer, 260, path, -1);
    OpenFile((const wchar_t*)buffer);
}

// @ 0x00935fb0
bool OpenBrowser(const wchar_t* url, int flag) {
    bool result = false;
    WString temp(L"url:");
    temp.append(url);
    if (ShellExecuteW(0, L"open", url, 0, 0, 1) > 0x20)
        result = true;
    return result;
}
}}

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
    this->SetPath((const wchar_t*)path);
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

// =====================================================================
// EA::IO::IniFile -- vtable-based reconstruction of the section cache.
// Uses the same object layout as EA_IO_IniFile above, but with real
// virtual declarations so the helper calls go through the retail slots.
// =====================================================================
struct PosNode;
struct NameNode;
struct PairPos;
struct PairStr;

struct InsertResult {
    void* mpNode;
    uint8_t mbInserted;
    char mPad[3];
    InsertResult() {}
    InsertResult(const InsertResult& o) { mpNode = o.mpNode; mbInserted = o.mbInserted; }
};

struct PosIter {
    PosNode* p;
    PosIter() {}
    PosIter(const PosIter& o) { p = o.p; }
};

struct PosNode {                     // map<WString,long> node
    PosNode* mpLeft;                 // +0x00
    PosNode* mpRight;                // +0x04
    PosNode* mpParent;               // +0x08
    uint32_t mColor;                 // +0x0c
    WString  mKey;                   // +0x10
    long     mValue;                 // +0x20
};

struct PairPos {                     // pair<WString, long>
    WString first;
    long second;
    PairPos(const WString& a, const long& b);   // 0x008d6580
};

struct PairStr {                     // pair<const WString, WString>
    WString first;
    WString second;
    PairStr(const WString& a, const WString& b);   // 0x0088c0d0
    PairStr(const PairStr& o);                     // 0x00614990
};

struct PosMap {                      // map<WString,long>, 0x1c bytes
    uint32_t mPad00;                 // +0x00
    PosNode* mpAnchorSelf;           // +0x04
    PosNode* mpAnchorParent;         // +0x08
    PosNode* mpRoot;                 // +0x0c
    uint8_t  mColor;                 // +0x10
    char     mPad11[3];              // +0x11
    uint32_t mSize;                  // +0x14
    uint32_t mPad18;                 // +0x18

    void DoNukeSubtree(PosNode* node);                      // 0x00934460
    PosIter find(const WString& key);                       // 0x005e96f0
    InsertResult insert(const PairPos& value, bool bUnique); // 0x00934260
    char* end() { return (char*)&mpAnchorSelf; }

    void clear() {
        DoNukeSubtree(mpRoot);
        mpAnchorSelf = (PosNode*)&mpAnchorSelf;
        mpAnchorParent = (PosNode*)&mpAnchorSelf;
        mpRoot = 0;
        mColor = 0;
        mSize = 0;
    }
};

struct NameMap {                     // map<WString,WString>, 0x1c bytes
    uint32_t mPad00;                 // +0x00
    NameNode* mpAnchorSelf;          // +0x04
    NameNode* mpAnchorParent;        // +0x08
    NameNode* mpRoot;                // +0x0c
    uint8_t  mColor;                 // +0x10
    char     mPad11[3];              // +0x11
    uint32_t mSize;                  // +0x14
    uint32_t mPad18;                 // +0x18

    InsertResult insert(const PairStr& value, bool bUnique); // 0x00614f20
    char* end() { return (char*)&mpAnchorSelf; }
};

struct PairVec {                     // eastl::vector<PairStr>
    PairStr* mpBegin;                // +0x00
    PairStr* mpEnd;                  // +0x04
    PairStr* mpCapacity;             // +0x08

    PairVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~PairVec() {
        if (mpBegin) {
            DoDestroy(mpBegin, mpEnd);
            if (((ArrayCookie*)mpBegin - 1)->mSize != 0)
                EASTL_allocator_deallocate(mpBegin);
        }
    }

    void reserve(size_t n);                                // 0x009343c0
    void DoDestroy(PairStr* first, PairStr* last);         // 0x00933df0
    void insert(PairStr* position, const PairStr& value);  // 0x00934ef0

    void push_back(const PairStr& value) {
        if (mpEnd != mpCapacity) {
            if (mpEnd)
                new (mpEnd) PairStr(value);
            ++mpEnd;
        } else {
            insert(mpEnd, value);
        }
    }
};

struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual int  GetAccessFlags();                // +0x10
    virtual int  GetState();                      // +0x14
    virtual void Open();                          // +0x18
    virtual unsigned Size();                      // +0x1c
    virtual void SetSize(unsigned n);             // +0x20
    virtual int  GetPosition(int type);           // +0x24
    virtual bool SetPosition(int pos, int type);  // +0x28
};

class IniFile {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual bool Close();                         // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual bool OpenForWrite(int mode);          // +0x48
    virtual void v19();
    virtual bool CacheSections(int mode);         // +0x50
    virtual void v21(); virtual void v22();
    virtual bool GetFileLine(WString* out);       // +0x5c
    virtual void WriteString(const wchar_t*, int);// +0x60

    wchar_t  mPath[260];          // +0x004
    char     mFileStream[0x22c];  // +0x20c
    IStream* mpStream;            // +0x438
    uint32_t mEncoding;           // +0x43c
    uint8_t  m440;                // +0x440
    uint8_t  m441;                // +0x441
    uint8_t  m442;                // +0x442
    uint8_t  m443;                // +0x443
    PosMap   mSectionPositionMap; // +0x444
    NameMap  mSectionNameMap;     // +0x460

    bool LoadSectionNames(int mode);
    int  EnumEntries(const wchar_t* section,
                     bool (__cdecl* callback)(const wchar_t*, const wchar_t*, void*),
                     void* user);
};

typedef bool (__cdecl* SectionEntryCallback)(const wchar_t*, const wchar_t*, void*);

// @ 0x009350f0
bool IniFile::LoadSectionNames(int mode) {
    mSectionPositionMap.clear();
    m442 = 0;
    if (!mpStream)
        return false;
    if (mpStream->GetAccessFlags() != mode) {
        if (!OpenForWrite(mode))
            return false;
    }

    WString line;
    WString section;
    WString lowerSection;

    mpStream->SetPosition(0, 0);
    for (;;) {
        long position = mpStream->GetPosition(0);
        if (!GetFileLine(&line))
            break;

        wchar_t whitespace[3] = { L' ', L'\t', 0 };
        line.erase(0, line.find_first_not_of(whitespace));

        if (line.mpBegin == line.mpEnd)
            continue;
        if (line.mpBegin[0] != L'[')
            continue;

        unsigned length = (unsigned)(line.mpEnd - line.mpBegin);
        if (length <= 1)
            continue;

        unsigned close = 1;
        while (close < length && line.mpBegin[close] != L']')
            ++close;
        if (close >= length)
            continue;
        if (close < 2)
            continue;

        section.assign(line.mpBegin + 1, line.mpBegin + close);
        lowerSection.assign(section.mpBegin, section.mpEnd);
        lowerSection.make_lower();

        {
            PairPos positionEntry(lowerSection, position);
            mSectionPositionMap.insert(positionEntry, false);
            PairStr nameEntry(lowerSection, section);
            mSectionNameMap.insert(nameEntry, false);
        }
    }

    m442 = 1;
    return true;
}

// @ 0x00935560
int IniFile::EnumEntries(const wchar_t* section, bool (__cdecl* callback)(const wchar_t*, const wchar_t*, void*), void* user) {
    WString key;
    WString line;
    WString lowerSection(section);
    int count = 0;

    if (!m442) {
        if (!CacheSections(1))
            count = -1;
    }

    if (count >= 0) {
        for (wchar_t* p = lowerSection.mpBegin; p != lowerSection.mpEnd; ++p) {
            uint32_t ch = (uint32_t)*p;
            if (ch <= 0xff)
                ch = (uint32_t)(uint16_t)tolower((int)(ch & 0xff));
            *p = (wchar_t)ch;
        }

        PosIter it = mSectionPositionMap.find(lowerSection);
        if (it.p != (PosNode*)mSectionPositionMap.end()) {
            if (mpStream->SetPosition(it.p->mValue, 0)) {
                if (GetFileLine(&line)) {
                    PairVec entries;
                    entries.reserve(0x40);

                    while (GetFileLine(&line)) {
                        wchar_t whitespace[3] = { L' ', L'\t', 0 };
                        line.erase(0, line.find_first_not_of(whitespace));

                        if (line.mpBegin == line.mpEnd)
                            continue;
                        if (line.mpBegin[0] == L';')
                            continue;
                        if (line.mpBegin[0] == L'[')
                            break;

                        wchar_t* equals = line.mpBegin;
                        while (equals != line.mpEnd && *equals != L'=')
                            ++equals;
                        if (equals == line.mpEnd)
                            continue;

                        unsigned equalsPos = (unsigned)(equals - line.mpBegin);
                        key.assign(line.mpBegin, line.mpBegin + equalsPos);
                        key.rtrim();
                        if (key.mpBegin == key.mpEnd)
                            continue;

                        line.erase(0, equalsPos + 1);

                        wchar_t valueWhitespace[3] = { L' ', L'\t', 0 };
                        line.erase(0, line.find_first_not_of(valueWhitespace, 0));
                        line.rtrim();

                        entries.push_back(PairStr(key, line));
                        ++count;
                    }

                    for (PairStr* entry = entries.mpBegin; entry != entries.mpEnd; ++entry) {
                        PairStr copy(*entry);
                        if (!callback(copy.first.mpBegin, copy.second.mpBegin, user))
                            break;
                    }
                }
            }
        }
    }

    if (!m441)
        Close();
    return count;
}
