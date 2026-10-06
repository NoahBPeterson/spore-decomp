// Slice s00936090 -- EA::Random (LCG + Mersenne Twister) and EA::SharedLibrary /
// SharedLibraryRegistry (UTF dynamic library management).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

namespace EA {
namespace Random {

// Declaration-only shim so cl cannot assume InitState/Reload preserve this
// (retail had them in a separate EAStdC translation unit).
struct MTOpsShim {
    void Reload();
    void InitState(uint32_t seed);
};

// ---------------------------------------------------------------------------
// RandomLinearCongruential
// ---------------------------------------------------------------------------
class RandomLinearCongruential {
public:
    void     SetSeed(uint32_t seed);          // 0x00936090
    uint64_t RandomUint32Uniform();           // 0x009360B0
    float    RandomDoubleUniform();           // 0x009360D0

    uint32_t mnSeed;   // +0x00
};

// @ 0x00936090
void RandomLinearCongruential::SetSeed(uint32_t seed) {
    if (seed == 0xffffffff || seed == 0)
        seed = (uint32_t)__rdtsc();
    mnSeed = seed;
}

// @ 0x009360B0
uint64_t RandomLinearCongruential::RandomUint32Uniform() {
    uint64_t v = (uint64_t)mnSeed * 0x41c64e6d + 0x3039;
    mnSeed = (uint32_t)v;
    return v >> 16;
}

// @ 0x009360D0
float RandomLinearCongruential::RandomDoubleUniform() {
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    uint32_t v = mnSeed * 0x278dde6d;
    mnSeed = v;
    float f = (float)(int)v * 2.3283064e-10f + 0.5f;
    if (f >= 1.0f)
        return 0.0f;
    return f;
}

// ---------------------------------------------------------------------------
// MersenneTwister (MT19937)
// ---------------------------------------------------------------------------
class RandomMersenneTwister {
public:
    void Reload();                              // 0x00936110
    void InitState(uint32_t seed);              // 0x009361F0
    uint32_t Generate();                        // 0x00936250
    uint32_t GenerateUInt32(uint32_t max);      // 0x009362B0
    double GenerateDouble();                    // 0x009362D0
    RandomMersenneTwister* SetSeed(uint32_t seed);  // 0x00936300

    uint32_t  mState[0x270];   // +0x000
    uint32_t* mpNext;          // +0x9c0
    int       mnCount;         // +0x9c4
};

// @ 0x00936110
void RandomMersenneTwister::Reload() {
    uint32_t* p = mState;
    for (int i = 0; i < 227; i++) {
        uint32_t y = (p[i] & 0x80000000) | (p[i + 1] & 0x7fffffff);
        p[i] = p[i + 397] ^ (y >> 1) ^ (-(int32_t)(y & 1) & 0x9908b0df);
    }
    for (int i = 227; i < 623; i++) {
        uint32_t y = (p[i] & 0x80000000) | (p[i + 1] & 0x7fffffff);
        p[i] = p[i - 227] ^ (y >> 1) ^ (-(int32_t)(y & 1) & 0x9908b0df);
    }
    uint32_t y = (p[623] & 0x80000000) | (p[0] & 0x7fffffff);
    p[623] = p[396] ^ (y >> 1) ^ (-(int32_t)(y & 1) & 0x9908b0df);
    mnCount = 0x270;
    mpNext = p;
}

// @ 0x009361F0
void RandomMersenneTwister::InitState(uint32_t seed) {
    int n = 0x270;
    if (seed == 0xffffffff)
        seed = (uint32_t)__rdtsc();
    seed |= 1;
    uint32_t* p = mState;
    uint32_t s = seed;
    do {
        uint32_t t = s * 0x10dcd;
        *p = s & 0xffff0000;
        *p |= t >> 16;
        s = t * 0x10dcd + 0x10dce;
        p++;
    } while (--n);
    Reload();
}

// @ 0x00936250
uint32_t RandomMersenneTwister::Generate() {
    RandomMersenneTwister* self = this;
    if (--self->mnCount < 0) {
        ((MTOpsShim*)self)->Reload();
        self->mnCount--;
    }
    uint32_t v = *self->mpNext++;
    v ^= v >> 11;
    v ^= (v & 0xff3a58ad) << 7;
    v ^= (v & 0xffffdf8c) << 15;
    return v ^ (v >> 18);
}

// @ 0x009362B0
uint32_t RandomMersenneTwister::GenerateUInt32(uint32_t max) {
    return (uint32_t)(((uint64_t)Generate() * max) >> 32);
}

// @ 0x009362D0
double RandomMersenneTwister::GenerateDouble() {
    int v = (int)Generate();
    double f = (double)v * 2.3283064365386963e-10 + 0.5;
    if (f < 1.0)
        return f;
    return 0.0;
}

// @ 0x00936300
RandomMersenneTwister* RandomMersenneTwister::SetSeed(uint32_t seed) {
    mpNext = 0;
    mnCount = 0x270;
    ((MTOpsShim*)this)->InitState(seed);
    return this;
}

}  // namespace Random
}  // namespace EA

// ===========================================================================
// EA::SharedLibrary
// ===========================================================================
namespace EA {

namespace Thread {
class Mutex {
public:
    void Construct(int a, int b);
    void Destroy();
    void Lock(const void* name);
    void Unlock();
    char mData[0x30];
};
}

struct ILibraryCommand {
    virtual void v0();                                        // +0x00
    virtual int  AddRef();                                    // +0x04
    virtual int  Release();                                   // +0x08
    virtual void v10();                                       // +0x0c
    virtual bool v11();                                       // +0x10
    virtual char v14(int);                                    // +0x14
    virtual char v18(int);                                    // +0x18
    virtual int  IsLoaded();                                  // +0x1c
    virtual char CanReload();                                 // +0x20
    virtual void v24(void*, void*);                           // +0x24
    virtual void v28();                                       // +0x28
    virtual bool ExecuteCommand(const char*, void*, int, int, int);  // +0x2c
    virtual void v30();                                       // +0x30
    virtual const wchar_t* GetName();                         // +0x34
    virtual void v38();                                       // +0x38
};

struct SharedLibraryVector {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
};

class SharedLibrary : public ILibraryCommand {
public:
    int    mnRefCount;      // +0x04  (atomic)
    void*  mHandle;         // +0x08
    wchar_t* mpPathBegin;   // +0x0c
    wchar_t* mpPathEnd;     // +0x10
    wchar_t* mpPathCap;     // +0x14
    int    m18;             // +0x18
    void*  mHandlerBegin;   // +0x1c
    void*  mHandlerEnd;     // +0x20
    void*  mHandlerCap;     // +0x24
    int    m28;             // +0x28
    int    m2c;             // +0x2c
    Thread::Mutex mMutex;   // +0x30

    void Construct(uint32_t a, uint32_t b);
    bool Load();                                  // 0x009365E0
    bool Reload(int flag);                        // 0x00936380
    bool CanUnload();                             // 0x00936330
    const void* GetVersionInfo();                 // 0x009363B0
    int  IsLoaded();                              // 0x00936420
    bool Unregister(void* fn);                    // 0x009366D0
    bool ExecuteCmd(const char* name, void* a, int b, int c, int d);  // 0x00936710
    bool Unload(int force);                       // 0x00936B70
    bool Register(void* fn, void* user);          // 0x00936C00
    SharedLibrary(uint32_t a, uint32_t b);        // 0x00936C80
    ~SharedLibrary();                             // 0x00936CE0
    bool SetPath(const wchar_t* path, char flag); // 0x00936950
};

}  // namespace EA

extern "C" void* gpSharedLibraryRegistry;   // 0x01669948
extern "C" const char kDefaultSharedLibraryVersionInfo[];   // 0x0143e990
extern "C" void FreeMem(void*);
extern "C" {
__declspec(dllimport) void* __stdcall LoadLibraryW(const wchar_t*);
__declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
__declspec(dllimport) int   __stdcall FreeLibrary(void*);
}
int __cdecl wcscmp_lib(const wchar_t*, const wchar_t*);
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
void* __cdecl operator_new_args(unsigned int);

namespace EA {

inline char IsLoadedV(void* self) {
    return (*(char(__thiscall**)(void*))((char*)*(void**)self + 0x1c))(self);
}

// @ 0x00936330
bool SharedLibrary::CanUnload() {
    void* p = 0;
    if (IsLoadedV(this)) {
        if (!ExecuteCommand("CanSharedLibraryUnload", &p, 0, 0, 0) || p == 0)
            return false;
    }
    return true;
}

// @ 0x00936380
bool SharedLibrary::Reload(int flag) {
    if (!v18(flag))
        return false;
    return v11();
}

// @ 0x009363B0
const void* SharedLibrary::GetVersionInfo() {
    void** p = 0;
    if (IsLoadedV(this) && ExecuteCommand("GetSharedLibraryVersion", &p, 0, 0, 0) && p != 0)
        return p;
    return kDefaultSharedLibraryVersionInfo;
}

// @ 0x00936420
int SharedLibrary::IsLoaded() {
    if (mHandle == 0 && mHandlerBegin == mHandlerEnd)
        return 0;
    return 1;
}

}  // namespace EA

// @ 0x00936440
bool __cdecl EA_generic_command_function(const char* name, void* self, void** out,
                                         int a, int b, int c) {
    if (self != 0) {
        struct Entry { void* fn; void* user; };
        Entry* it = *(Entry**)((char*)self + 0x1c);
        Entry* end = *(Entry**)((char*)self + 0x20);
        for (; it < end; it++) {
            typedef bool (__cdecl *Fn)(const char*, void*, void**, int, int, int);
            if (((Fn)it->fn)(name, it->user, out, a, b, c))
                return true;
        }
    }
    const char* s1 = name;
    const char* s2 = "GetSharedLibraryVersion";
    while (*s1 == *s2) {
        if (*s1 == 0)
            break;
        s1++;
        s2++;
    }
    bool equal = (*s1 == *s2);
    if (equal) {
        *out = (void*)kDefaultSharedLibraryVersionInfo;
        return true;
    }
    return false;
}

namespace EA {

// @ 0x00936710
bool SharedLibrary::ExecuteCmd(const char* name, void* a, int b, int c, int d) {
    return EA_generic_command_function(name, this, (void**)a, b, c, d);
}

}  // namespace EA

// ===========================================================================
// EA::SharedLibraryRegistry
// ===========================================================================
namespace EA {

struct ObjectVector {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08
    void erase(void* first, void* last);
    void Destruct();
    void push_back_impl(void* value);
};

extern void* gpRegistryMutexName;   // 0x0143e98c

class SharedLibraryRegistry {
public:
    virtual void v0();                            // +0x00
    virtual int  AddRef();                        // +0x04
    virtual int  Release();                       // +0x08
    virtual void v10();                           // +0x0c
    virtual void v11();                           // +0x10
    virtual void RemoveLibrary2(void*, int);      // +0x14
    virtual void Shutdown2(int);                  // +0x18
    virtual void v1c();                           // +0x1c
    virtual void v20();                           // +0x20
    virtual void* GetDefaultLibrary();            // +0x24
    virtual void v28();                           // +0x28
    virtual void v2c();                           // +0x2c

    int     m04;                    // +0x04
    ObjectVector mSharedLibraries;  // +0x08
    int     m14;                    // +0x14
    int     m18;                    // +0x18
    int     m1c;                    // +0x1c
    Thread::Mutex mMutex;           // +0x20

    SharedLibraryRegistry();                       // 0x009368F0
    ~SharedLibraryRegistry();                      // 0x00936740
    void* scalar_deleting_destructor(uint8_t f);   // 0x00936920
    bool RemoveAllLibraries(int flag);             // 0x009364F0
    int  ExecuteCommandAll(void* a, void* b, void* c, void* d, void* e); // 0x00936550
    void* GetFirst();                              // 0x009365D0
    bool RemoveLibrary(SharedLibrary* lib, char flag);  // 0x00936760
    int  GetLibraries(void** out, unsigned int n); // 0x00936820
    bool Init(uint32_t a, SharedLibrary* b);       // 0x00936D50
    bool Shutdown();                               // 0x00936E10
    SharedLibrary* LoadPath(const wchar_t* path, char flag);   // 0x00936E50
    bool AddLibraryRef(SharedLibrary* lib);        // 0x00937010
};

}  // namespace EA

// @ 0x009368F0
EA::SharedLibraryRegistry::SharedLibraryRegistry() {
    mSharedLibraries.mpBegin = 0;
    mSharedLibraries.mpEnd = 0;
    mSharedLibraries.mpCap = 0;
    mMutex.Construct(0, 1);
}

// @ 0x00936740
EA::SharedLibraryRegistry::~SharedLibraryRegistry() {
    mMutex.Destroy();
    mSharedLibraries.Destruct();
}

// @ 0x00936920
void* EA::SharedLibraryRegistry::scalar_deleting_destructor(uint8_t f) {
    mMutex.Destroy();
    mSharedLibraries.Destruct();
    if (f & 1)
        FreeMem(this);
    return this;
}

// @ 0x009364F0
bool EA::SharedLibraryRegistry::RemoveAllLibraries(int flag) {
    mMutex.Lock(&gpRegistryMutexName);
    void** begin = (void**)mSharedLibraries.mpBegin;
    void** end = (void**)mSharedLibraries.mpEnd;
    if (begin != end) {
        while (((char*)end - (char*)begin) >> 2 > 1) {
            void* lib = begin[1];
            RemoveLibrary2(lib, flag);
            begin = (void**)mSharedLibraries.mpBegin;
            end = (void**)mSharedLibraries.mpEnd;
        }
    }
    mMutex.Unlock();
    return true;
}

// @ 0x00936550
int EA::SharedLibraryRegistry::ExecuteCommandAll(void* a, void* b, void* c, void* d, void* e) {
    mMutex.Lock(&gpRegistryMutexName);
    int count = 0;
    unsigned int n = (unsigned int)(((char*)mSharedLibraries.mpEnd - (char*)mSharedLibraries.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; i++) {
        SharedLibrary* lib = ((SharedLibrary**)mSharedLibraries.mpBegin)[i];
        if (lib->ExecuteCommand((const char*)a, b, (int)c, (int)d, (int)e))
            count++;
    }
    mMutex.Unlock();
    return count;
}

// @ 0x009365D0
void* EA::SharedLibraryRegistry::GetFirst() {
    return *(void**)mSharedLibraries.mpBegin;
}

// @ 0x00936760
bool EA::SharedLibraryRegistry::RemoveLibrary(SharedLibrary* lib, char flag) {
    if (lib != 0 && GetDefaultLibrary() == lib)
        return false;
    mMutex.Lock(&gpRegistryMutexName);
    SharedLibrary** begin = (SharedLibrary**)mSharedLibraries.mpBegin;
    SharedLibrary** end = (SharedLibrary**)mSharedLibraries.mpEnd;
    SharedLibrary** it = begin;
    while (it < end && *it != lib)
        it++;
    if (it >= end) {
        mMutex.Unlock();
        return false;
    }
    if (flag != 0)
        (*it)->Reload(1);
    SharedLibrary* last = end[-1];
    SharedLibrary* old = *it;
    if (last != old) {
        if (last != 0)
            last->AddRef();
        *it = last;
        if (old != 0)
            old->Release();
    }
    mSharedLibraries.mpEnd = (char*)mSharedLibraries.mpEnd - 4;
    SharedLibrary* tail = *(SharedLibrary**)mSharedLibraries.mpEnd;
    if (tail != 0)
        tail->Release();
    mMutex.Unlock();
    return true;
}

// @ 0x00936820
int EA::SharedLibraryRegistry::GetLibraries(void** out, unsigned int n) {
    if (out == 0) {
        mMutex.Lock(&gpRegistryMutexName);
        int c = (int)(((char*)mSharedLibraries.mpEnd - (char*)mSharedLibraries.mpBegin) >> 2);
        mMutex.Unlock();
        return c;
    }
    mMutex.Lock(&gpRegistryMutexName);
    unsigned int total = (unsigned int)(((char*)mSharedLibraries.mpEnd - (char*)mSharedLibraries.mpBegin) >> 2);
    unsigned int count = total;
    if (n <= total)
        count = n;
    SharedLibrary** src = (SharedLibrary**)mSharedLibraries.mpBegin;
    for (unsigned int i = 0; i < count; i++) {
        SharedLibrary* a = src[i];
        SharedLibrary* b = (SharedLibrary*)out[i];
        if (a != b) {
            if (a != 0)
                a->AddRef();
            out[i] = a;
            if (b != 0)
                b->Release();
        }
    }
    mMutex.Unlock();
    return (int)total;
}

// @ 0x00936950
bool EA::SharedLibrary::SetPath(const wchar_t* path, char flag) {
    if (path == 0)
        return false;
    if (!CanReload())
        return false;
    void* h = LoadLibraryW(path);
    if (h == 0)
        return false;
    void* fn = GetProcAddress(h, "EASharedLibraryStartupFunction");
    FreeLibrary(h);
    if (fn == 0)
        return false;
    mpPathBegin = 0;
    mpPathEnd = 0;
    mpPathCap = 0;
    (void)flag;
    return true;
}

// @ 0x00936C80
void EA::SharedLibrary::Construct(uint32_t a, uint32_t b) {
    mnRefCount = 0;
    mHandle = 0;
    m18 = 0;
    mHandlerBegin = 0;
    mHandlerEnd = 0;
    mHandlerCap = 0;
    m28 = 0;
    m2c = 0;
    mMutex.Construct(0, 1);
    Register((void*)a, (void*)b);
}

EA::SharedLibrary::SharedLibrary(uint32_t a, uint32_t b) {
    Construct(a, b);
}

// @ 0x009365E0
bool EA::SharedLibrary::Load() {
    if (IsLoaded())
        return true;
    if (mpPathBegin == mpPathEnd)
        return false;
    void* h = LoadLibraryW(mpPathBegin);
    if (h == 0)
        return false;
    typedef bool (__cdecl *StartupFn)(void*, void*, void**, void**);
    StartupFn fn = (StartupFn)GetProcAddress(h, "EASharedLibraryStartupFunction");
    if (fn == 0) {
        FreeLibrary(h);
        return false;
    }
    void* registry = 0;
    if (gpSharedLibraryRegistry != 0)
        registry = (void*)(*(void*(__thiscall**)(void*))((char*)*(void**)gpSharedLibraryRegistry + 0x24))(gpSharedLibraryRegistry);
    void* ctx = 0;
    void* result = 0;
    if (fn(EA_generic_command_function, registry, &ctx, &result) && ctx != 0) {
        void* out = 0;
        if (!(*(bool(__cdecl**)(const char*, void*, void**, int, int, int))ctx)
                ("OnSharedLibraryLoad", result, (void**)&out, 0, 0, 0) || out != 0) {
            mHandle = h;
            (*(void(__thiscall**)(void*, void*, void*))((char*)*(void**)this + 0x24))(this, ctx, result);
            return true;
        }
    }
    FreeLibrary(h);
    return false;
}

// @ 0x009366D0
bool EA::SharedLibrary::Unregister(void* fn) {
    if (fn == 0)
        return false;
    char** begin = (char**)mHandlerBegin;
    char** end = (char**)mHandlerEnd;
    char** it = begin;
    while (it != end) {
        if (*it == fn)
            break;
        it += 2;
    }
    if (it == end)
        return false;
    it[0] = end[-2];
    it[1] = end[-1];
    mHandlerEnd = (char*)mHandlerEnd - 8;
    return true;
}

// @ 0x00936B70
bool EA::SharedLibrary::Unload(int force) {
    if (!IsLoaded())
        return true;
    char canReload = CanReload();
    if (force == 0 && canReload == 0)
        return false;
    if (mHandle == 0) {
        ((ObjectVector*)&mHandlerBegin)->erase(mHandlerBegin, mHandlerEnd);
    } else {
        int ctx = 0;
        ExecuteCommand("OnSharedLibraryUnload", &ctx, 0, 0, 0);
        ((ObjectVector*)&mHandlerBegin)->erase(mHandlerBegin, mHandlerEnd);
        void* h = mHandle;
        mHandle = 0;
        if (h != 0) {
            FreeLibrary(h);
            return true;
        }
    }
    return true;
}

// @ 0x00936C00
bool EA::SharedLibrary::Register(void* fn, void* user) {
    if (fn == 0)
        return false;
    char** begin = (char**)mHandlerBegin;
    char** end = (char**)mHandlerEnd;
    char** it = begin;
    while (it != end) {
        if (*it == fn)
            return true;
        it += 2;
    }
    if (mHandlerEnd < mHandlerCap) {
        char** slot = (char**)mHandlerEnd;
        mHandlerEnd = slot + 2;
        if (slot != 0) {
            slot[1] = (char*)user;
            slot[0] = (char*)fn;
        }
        return true;
    }
    ((ObjectVector*)&mHandlerBegin)->push_back_impl(&fn);
    return true;
}

// @ 0x00936CE0
EA::SharedLibrary::~SharedLibrary() {
    if (mHandle != 0 || mHandlerBegin != mHandlerEnd)
        Unload(1);
    mMutex.Destroy();
    if (mHandlerBegin != 0 && ((int*)mHandlerBegin)[-1] != 0)
        FreeMem(mHandlerBegin);
    wchar_t* p = mpPathBegin;
    if ((((char*)mpPathCap - (char*)p) & 0xfffffffe) > 2 && p != 0)
        FreeMem(p);
}

// @ 0x00936D50
static EA::SharedLibrary* MakeSharedLibrary(uint32_t a, uint32_t b) {
    EA::SharedLibrary* p = (EA::SharedLibrary*)operator new(
        0x60, "UTF/SharedLibraryRegistry/SharedLibrary", 0, 0, 0, 0);
    if (p != 0)
        p->Construct(a, b);
    return p;
}

bool EA::SharedLibraryRegistry::Init(uint32_t a, SharedLibrary* b) {
    mMutex.Lock(&gpRegistryMutexName);
    if (mSharedLibraries.mpBegin == mSharedLibraries.mpEnd) {
        SharedLibrary* lib = MakeSharedLibrary(a, (uint32_t)b);
        if (lib != 0)
            lib->AddRef();
        if (mSharedLibraries.mpEnd < mSharedLibraries.mpCap) {
            SharedLibrary** s = (SharedLibrary**)mSharedLibraries.mpEnd;
            mSharedLibraries.mpEnd = s + 1;
            if (s != 0) {
                *s = lib;
                if (lib != 0)
                    lib->AddRef();
            }
        } else {
            ((ObjectVector*)&mSharedLibraries)->push_back_impl(&lib);
        }
        if (lib != 0)
            lib->Release();
    }
    mMutex.Unlock();
    return true;
}

// @ 0x00936E10
bool EA::SharedLibraryRegistry::Shutdown() {
    Shutdown2(1);
    mMutex.Lock(&gpRegistryMutexName);
    mSharedLibraries.erase(mSharedLibraries.mpBegin, mSharedLibraries.mpEnd);
    mMutex.Unlock();
    return true;
}

// @ 0x00936E50
EA::SharedLibrary* EA::SharedLibraryRegistry::LoadPath(const wchar_t* path, char flag) {
    mMutex.Lock(&gpRegistryMutexName);
    SharedLibrary** begin = (SharedLibrary**)mSharedLibraries.mpBegin;
    SharedLibrary** end = (SharedLibrary**)mSharedLibraries.mpEnd;
    for (SharedLibrary** it = begin; it < end; it++) {
        SharedLibrary* cur = *it;
        const wchar_t* name = (cur != 0) ? cur->GetName() : 0;
        if (name != 0 && path != 0 && wcscmp_lib(name, path) == 0) {
            mMutex.Unlock();
            return cur;
        }
    }
    mMutex.Unlock();
    SharedLibrary* nu = MakeSharedLibrary(0, 0);
    if (nu != 0)
        nu->SetPath(path, flag);
    if (nu != 0 && (char)flag != 0 && !nu->IsLoaded()) {
        nu->Release();
        return 0;
    }
    if (nu != 0)
        nu->AddRef();
    mMutex.Lock(&gpRegistryMutexName);
    if (mSharedLibraries.mpEnd < mSharedLibraries.mpCap) {
        SharedLibrary** s = (SharedLibrary**)mSharedLibraries.mpEnd;
        mSharedLibraries.mpEnd = s + 1;
        if (s != 0) {
            *s = nu;
            if (nu != 0)
                nu->AddRef();
        }
    } else {
        ((ObjectVector*)&mSharedLibraries)->push_back_impl(&nu);
    }
    mMutex.Unlock();
    if (nu != 0)
        nu->Release();
    return nu;
}

// @ 0x00937010
bool EA::SharedLibraryRegistry::AddLibraryRef(SharedLibrary* lib) {
    mMutex.Lock(&gpRegistryMutexName);
    SharedLibrary** begin = (SharedLibrary**)mSharedLibraries.mpBegin;
    SharedLibrary** end = (SharedLibrary**)mSharedLibraries.mpEnd;
    for (SharedLibrary** it = begin; it < end; it++) {
        if (*it == lib) {
            mMutex.Unlock();
            return true;
        }
    }
    SharedLibrary** slot = &begin[(end - begin)];
    (void)slot;
    if (mSharedLibraries.mpEnd < mSharedLibraries.mpCap) {
        SharedLibrary** s = (SharedLibrary**)mSharedLibraries.mpEnd;
        mSharedLibraries.mpEnd = s + 1;
        if (s != 0)
            *s = lib;
        if (lib != 0)
            lib->AddRef();
    } else {
        ((ObjectVector*)&mSharedLibraries)->push_back_impl(&lib);
    }
    mMutex.Unlock();
    return true;
}