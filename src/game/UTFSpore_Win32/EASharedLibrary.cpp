// src/game/UTFSpore_Win32/EASharedLibrary.cpp -- migrated from slice(s) s00936090, s008dd0d0, s005c1d70 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EASharedLibrary.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cSPEditorColorPicker.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPSwatch.h"
#include "SP/cSPEditorVerbIconTray.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)
#include <new>
#include <string.h>
#include "EA/AutoRefCount.h"
#include "EA/SharedLibrary.h"
#include "EA/SharedLibraryRegistry.h"
#include "EA/Thread/Mutex.h"
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s005c1d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005c_1d70 {
 public:
  T* mpObject;
  AutoRefCount_s005c_1d70() : mpObject(0) {}
  AutoRefCount_s005c_1d70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_1d70(const AutoRefCount_s005c_1d70& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_1d70() { if (mpObject) mpObject->Release(); }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace eastl {
template <typename T>
struct copy_impl_do {
  static T* do_copy(T* first, T* last, T* result);  // copy_impl<0,random_access>::do_copy
};
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
  T* insert(T* position, const T& value);
  T* erase(T* first, T* last) {  // trivially copyable T
    EASTL_memmove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};
}
namespace eastl {
template <typename T>
inline T* copy(T* first, T* last, T* result) {
  return copy_impl_do<T>::do_copy(first, last, result);
}
}
namespace eastl {
template <typename T>
inline void destruct(T* first, T* last) {
  for (; first < last; ++first)
    first->~T();
}
}
namespace eastl {
template <typename T>
class sp_ref_vector : public sp_vector<EA::AutoRefCount_s005c_1d70<T> > {
 public:
  typedef EA::AutoRefCount_s005c_1d70<T> value_type;
  ~sp_ref_vector();  // FUN_005c7f10 (out of line)
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};
}
namespace SP {
class cSPPalettePage_s005c_1d70 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Shutdown();  // FUN_005c7ed0
  char pad04[0x58 - 4];
  uint32_t mSequenceNumber;  // +0x58
  uint32_t mPackID;          // +0x5c
  uint32_t mRegionFilter;    // +0x60
};
}
// ---- items of slice s005c1d70 end

// ---- items of slice s008dd0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
// ---- items of slice s008dd0d0 end

// ---- items of slice s00936090 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc(void);
extern "C" void FreeMem(void*);   // 0x00f47380 (equiv t2)
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryW(const wchar_t*);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
extern "C" __declspec(dllimport) int   __stdcall FreeLibrary(void*);
#pragma intrinsic(__rdtsc)
namespace EA {
namespace Thread {
class Mutex_s0093_6090 {
public:
    void Construct(int a, int b);
    void Destroy();
    void Lock(const void* name);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
    char mData[0x30];
};
}
}
namespace EA {
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
}
namespace EA {
extern "C" void FreeMem(void*);
}
namespace EA {
struct WPathString {
    wchar_t* mpBegin;     // +0x00
    wchar_t* mpEnd;       // +0x04
    wchar_t* mpCapacity;  // +0x08
    uint32_t mAllocator;  // +0x0c (stateless EAIOPathStringCoreAllocator)
    WPathString(const WPathString& other);          // 0x0056e2d0
    WPathString& append(const wchar_t* s);          // 0x005c3d90
    WPathString& operator=(const WPathString& o);   // 0x0057cb60
    void DeallocateSelf();                          // 0x00933960
    __forceinline void DeallocateSelfInline() {
        wchar_t* b = mpBegin;
        if ((int)((int)mpCapacity - (int)b & 0xfffffffeU) > 2 && b)
            FreeMem(b);
    }
};
}
namespace EA {
class SharedLibrary_s0093_6090 : public ILibraryCommand {
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
    Thread::Mutex_s0093_6090 mMutex;   // +0x30

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
    SharedLibrary_s0093_6090(uint32_t a, uint32_t b);        // 0x00936C80
    ~SharedLibrary_s0093_6090();                             // 0x00936CE0
    bool SetPath(const wchar_t* path, bool flag);  // 0x00936950
};
}
namespace EA {
struct ObjectVector {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08
    void erase(void* first, void* last);   // 0x00d018d0 (equiv t2)
    void Destruct();   // 0x005c7f10 (equiv t3)
    void push_back_impl(void* value);
    void insert_pair(void* pos, void* value);   // 0x009a0c50 (8-byte elements)
};
}
namespace EA {
extern void* gpRegistryMutexName;   // 0x0143e98c
}
EA::SharedLibrary_s0093_6090::SharedLibrary_s0093_6090(uint32_t a, uint32_t b) {
    Construct(a, b);
}
extern "C" void* gpSharedLibraryRegistry;   // 0x01669948
extern "C" const char kDefaultSharedLibraryVersionInfo[];   // 0x0143e990
// ---- items of slice s00936090 end

// @ 0x005c2170
namespace eastl {
template <typename T> EA::AutoRefCount_s005c_1d70<T>* sp_ref_vector<T>::erase(value_type* first, value_type* last)
{
  value_type* const position = eastl::copy(last, this->mpEnd, first);
  destruct(position, this->mpEnd);
  this->mpEnd -= (last - first);
  return first;
}
template EA::AutoRefCount_s005c_1d70<SP::cSPPalettePage_s005c_1d70>* sp_ref_vector<SP::cSPPalettePage_s005c_1d70>::erase(EA::AutoRefCount_s005c_1d70<SP::cSPPalettePage_s005c_1d70>*, EA::AutoRefCount_s005c_1d70<SP::cSPPalettePage_s005c_1d70>*);
}  // namespace eastl

// @ 0x008dd1c0
int EA::SharedLibrary::Release()
{
    int n = _InterlockedExchangeAdd((volatile long*)((char*)this + 4), -1);
    --n;
    if (n == 0) {
        _InterlockedExchange((volatile long*)((char*)this + 4), 1);
        if (this != 0)
            ((void (__thiscall*)(void*, int))(*(void***)this)[0])(this, 1);
        n = 0;
    }
    return n;
}

// @ 0x00936330
bool EA::SharedLibrary::CanUnload() const
{
    void* p = 0;
    if (IsLoaded()) {
        if (!ExecuteCommand("CanSharedLibraryUnload", &p, 0, 0, 0) || p == 0)
            return false;
    }
    return true;
}

// @ 0x00936380
bool EA::SharedLibrary::Reload(bool flag)
{
    if (!Unload(flag))
        return false;
    return Load();
}

// @ 0x009363b0
EA::SharedLibrary::VersionInfo const * EA::SharedLibrary::GetVersionInfo() const
{
    void** p = 0;
    if (IsLoaded() && ExecuteCommand("GetSharedLibraryVersion", &p, 0, 0, 0) && p != 0)
        return (EA::SharedLibrary::VersionInfo const *)p;
    return (EA::SharedLibrary::VersionInfo const *)kDefaultSharedLibraryVersionInfo;
}

// @ 0x00936440
bool __cdecl EA_generic_command_function(const char* name, void* self, void** out, int a, int b, int c)
{
    if (self != 0) {
        struct Entry { void* fn; void* user; };
        Entry* it = *(Entry**)((char*)self + 0x1c);
        Entry* end = *(Entry**)((char*)self + 0x20);
        for (; it < end; it++) {
            typedef bool (__cdecl *Fn)(const char*, void*, void**, int, int, int);
            Fn fn = (Fn)it->fn;
            void* user = it->user;
            if (fn(name, user, out, a, b, c))
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

// @ 0x009364f0
bool EA::SharedLibraryRegistry::RemoveAllLibraries(bool flag)
{
    mMutex.Lock(*(unsigned int const *)&gpRegistryMutexName);
    void** begin = (void**)mSharedLibraries.mpBegin;
    void** end = (void**)mSharedLibraries.mpEnd;
    if (begin != end) {
        while (((char*)end - (char*)begin) >> 2 > 1) {
            void* lib = begin[1];
            RemoveLibrary((EA::SharedLibrary *)lib, flag);
            begin = (void**)mSharedLibraries.mpBegin;
            end = (void**)mSharedLibraries.mpEnd;
        }
    }
    mMutex.Unlock();
    return true;
}

// @ 0x00936550
unsigned int EA::SharedLibraryRegistry::ExecuteCommandAll(char const * a, void * b, void * c, void * d, void * e)
{
    mMutex.Lock(*(unsigned int const *)&gpRegistryMutexName);
    int count = 0;
    unsigned int n = (unsigned int)(((char*)mSharedLibraries.mpEnd - (char*)mSharedLibraries.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; i++) {
        EA::SharedLibrary* lib = ((EA::SharedLibrary**)mSharedLibraries.mpBegin)[i];
        if (lib->ExecuteCommand((const char*)a, b, c, d, e))
            count++;
    }
    mMutex.Unlock();
    return count;
}

// @ 0x009365d0
EA::SharedLibrary * EA::SharedLibraryRegistry::GetMainLibrary()
{
    return *(EA::SharedLibrary**)mSharedLibraries.mpBegin;
}

// @ 0x009365e0
bool EA::SharedLibrary::Load()
{
    if (IsLoaded())
        return true;
    if (mPath.mpBegin == mPath.mpEnd)
        return false;
    void* h = LoadLibraryW(mPath.mpBegin);
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

// @ 0x009366d0
bool EA::SharedLibrary_s0093_6090::Unregister(void* fn)
{
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

// @ 0x00936710
bool EA::SharedLibrary::ExecuteCommand(char const * name, void * a, void * b, void * c, void * d) const
{
    int d_v = (int)d;
    int c_v = (int)c;
    int b_v = (int)b;
    return EA_generic_command_function(name, (void*)this, (void**)a, b_v, c_v, d_v);
}

// @ 0x00936740
EA::SharedLibraryRegistry::~SharedLibraryRegistry()
{
    (void)0;
}

// @ 0x00936950
bool EA::SharedLibrary_s0093_6090::SetPath(const wchar_t* path, bool flag)
{
    if (path == 0)
        return false;
    if (CanReload()) {
        void* h = LoadLibraryW(path);
        if (h != 0) {
            bool ok = GetProcAddress(h, "EASharedLibraryStartupFunction") != 0;
            FreeLibrary(h);
            if (ok) {
                WPathString& p = *(WPathString*)&mpPathBegin;
                WPathString temp(p);
                p.append(path);
                if (flag == 0 || v14(0)) {
                    temp.DeallocateSelfInline();
                    return true;
                }
                p = temp;
                temp.DeallocateSelf();
            }
        }
    }
    return false;
}

// @ 0x00936b70
bool EA::SharedLibrary_s0093_6090::Unload(int force)
{
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

// @ 0x00936c00
bool EA::SharedLibrary_s0093_6090::Register(void* fn, void* user)
{
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
    struct HandlerPair { void* fn; void* user; };
    HandlerPair pair;
    pair.fn = fn;
    pair.user = user;
    if (mHandlerEnd < mHandlerCap) {
        HandlerPair* slot = (HandlerPair*)mHandlerEnd;
        mHandlerEnd = (char*)(slot + 1);
        if (slot != 0)
            *slot = pair;                 // one 8-byte entry: {fn, user}
        return true;
    }
    ((ObjectVector*)&mHandlerBegin)->insert_pair(mHandlerEnd, &pair);
    return true;
}

// @ 0x00936ce0
EA::SharedLibrary_s0093_6090::~SharedLibrary_s0093_6090()
{
    if (mHandle != 0 || mHandlerBegin != mHandlerEnd)
        Unload(1);
    mMutex.Destroy();
    if (mHandlerBegin != 0 && ((int*)mHandlerBegin)[-1] != 0)
        FreeMem(mHandlerBegin);
    wchar_t* p = mpPathBegin;
    if ((((char*)mpPathCap - (char*)p) & 0xfffffffe) > 2 && p != 0)
        FreeMem(p);
}

// @ 0x00936e10
bool EA::SharedLibraryRegistry::Shutdown()
{
    RemoveAllLibraries(1);
    mMutex.Lock(*(unsigned int const *)&gpRegistryMutexName);
    mSharedLibraries.erase(mSharedLibraries.mpBegin, mSharedLibraries.mpEnd);
    mMutex.Unlock();
    return true;
}
