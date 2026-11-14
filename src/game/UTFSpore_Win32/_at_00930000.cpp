// src/game/UTFSpore_Win32/_at_00930000.cpp -- migrated from slice(s) s0093e5f0, s0093d740, s0093c950, s0093b9e0, s0093a9d0, s00939a60, s00936090, s009350f0, s009323c0, s00931460 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00930000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <direct.h>
#include <sys/stat.h>
#include "EA/IO/IStream.h"
#include "EA/Thread/Mutex.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Random/RandomMersenneTwister.h"
#include "EA/SharedLibrary.h"
#include "EA/SharedLibraryRegistry.h"
#include <intrin.h>
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/IO/MemoryStream.h"
#include <new>
#include "EA/Stopwatch.h"
#include "EA/LimitStopwatch.h"
#include "SP/cDirectPropertyList.h"

// ---- items of slice s00931460 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct FixedPathString {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAllocPad;    // +0x0c
    wchar_t* mpFixed;      // +0x10  the in-object buffer
    wchar_t  mBuffer[260]; // +0x14

    FixedPathString() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 260;
        mpFixed = mBuffer;
        mBuffer[0] = 0;
    }
    void assign(const wchar_t* b, const wchar_t* e);           // 0x0088c3d0
    void make_lower();                                         // 0x005e8e80
    void erase(unsigned pos, unsigned n);                      // 0x008e3a70
    void DeallocateSelf() {
        wchar_t* b = mpBegin;
        if ((int)((int)mpCapacity - (int)b & 0xfffffffeU) > 2 && b && b != mpFixed)
            operator delete[](b);
    }
};
bool operator==(const FixedPathString& s, const wchar_t* p);   // 0x006ab760
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void push_back(wchar_t c);   // 0x004f6510
};
// ---- items of slice s00931460 end

// ---- items of slice s009323c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall RemoveDirectoryW(const wchar_t*);
extern "C" __declspec(dllimport) int __stdcall DeleteFileW(const wchar_t*);
extern "C" __declspec(dllimport) unsigned int __stdcall GetWindowsDirectoryW(wchar_t*, unsigned int);
extern "C" __declspec(dllimport) int __stdcall SHGetFolderPathW(void*, int, void*, unsigned int, wchar_t*);
extern "C" uint32_t g_folderTable[];
extern "C" uint64_t g_crc64Table[256];   // 0x0154e288
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);   // 0x011e0744
extern "C" __declspec(dllimport) unsigned int __stdcall GetFileAttributesW_s0093_23c0(const wchar_t*);
namespace EA {
namespace IO {
bool IsFilePathSeparator(wchar_t c);
}
}
extern "C" __declspec(dllimport) unsigned int __stdcall GetTempPathW_s0093_23c0(unsigned int, wchar_t*);
extern "C" __declspec(dllimport) void* __stdcall GetModuleHandleA_s0093_23c0(const char*);
extern "C" __declspec(dllimport) unsigned int __stdcall GetModuleFileNameW_s0093_23c0(void*, wchar_t*, unsigned int);
extern "C" __declspec(dllimport) unsigned int __stdcall GetFullPathNameW_s0093_23c0(const wchar_t*, unsigned int, wchar_t*, wchar_t**);
bool DeleteDirectoryContents(wchar_t* path, uint32_t len);
struct ICoreAllocator;
struct WString_s0093_23c0 {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAlloc;       // +0x0c
};
struct Entry {
    int      mType;      // +0x00  1 = directory, 2 = file
    WString_s0093_23c0  mName;      // +0x04
    int      mPad;       // +0x14
    int64_t  mTimes[3];  // +0x18  create / write / access, seconds
};
struct DequeIter {
    Entry*  mpCurrent;          // +0x00
    Entry*  mpBegin;            // +0x04
    Entry*  mpEnd;              // +0x08
    Entry** mpCurrentArrayPtr;  // +0x0c

    DequeIter& operator++() {
        if (++mpCurrent == mpEnd) {
            ++mpCurrentArrayPtr;
            mpBegin = *mpCurrentArrayPtr;
            mpEnd = mpBegin + 4;
            mpCurrent = mpBegin;
        }
        return *this;
    }
    bool operator!=(const DequeIter& other) const { return mpCurrent != other.mpCurrent; }
    Entry& operator*() const { return *mpCurrent; }
};
struct Deque {
    Entry**         mpPtrArray;      // +0x00
    unsigned        mnPtrArraySize;  // +0x04
    DequeIter       mItBegin;        // +0x08
    DequeIter       mItEnd;          // +0x18
    ICoreAllocator* mpAllocator;     // +0x28
    const char*     mpName;          // +0x2c

    void DoInit(unsigned n);            // 0x005f8840
    void InitAlloc(ICoreAllocator* a);  // 0x005f9680
    void Destroy();                     // 0x005f96c0
};
struct DirectoryIterator {
    uint32_t mnListSize;            // +0x00
    int      mnRecursionIndex;      // +0x04
    wchar_t* mpBaseDirectory;       // +0x08
    uint32_t mBaseDirectoryLength;  // +0x0c

    unsigned Read(const wchar_t* dir, Deque* list, const wchar_t* pattern,   // 0x0092ef40
                  unsigned flags, unsigned maxCount, bool wantTimes);
};
extern "C" ICoreAllocator* __cdecl GetDefaultAllocatorX();       // 0x00925cb0
static inline bool IsPathSeparator(wchar_t c) {
    return c == L'\\' || c == L'/' || c == L':';
}
// ---- items of slice s009323c0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
uint32_t RemoveDirectoryRecursive(const wchar_t* path, char recursive);   // defined at 0x00932890, called earlier in the TU

// ---- items of slice s009350f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int   __cdecl _wspawnv(int mode, const wchar_t* path, const wchar_t* const* argv);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(_InterlockedExchange, _InterlockedDecrement, _InterlockedIncrement, _InterlockedExchangeAdd)
#pragma intrinsic(__rdtsc)
extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameW_s0093_50f0(void* mod, wchar_t* buf, unsigned long n);
// ---- items of slice s009350f0 end

// ---- items of slice s00936090 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Random {
struct MTOpsShim {
    void Reload();
    void InitState(uint32_t seed);
};
}
}
namespace EA {
namespace Random {
class RandomMersenneTwister_s0093_6090 {
public:
    uint32_t Reload();                          // 0x00936110 (eax = mState[0] on return)
    void InitState(uint32_t seed);              // 0x009361F0
    uint32_t Generate();                        // 0x00936250
    uint32_t GenerateUInt32(uint32_t max);      // 0x009362B0
    double GenerateDouble();                    // 0x009362D0
    RandomMersenneTwister_s0093_6090* SetSeed(uint32_t seed);  // 0x00936300

    uint32_t  mState[0x270];   // +0x000
    uint32_t* mpNext;          // +0x9c0
    int       mnCount;         // +0x9c4
};
}
}
// ---- items of slice s00936090 end

// ---- items of slice s00939a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned short _byteswap_ushort(unsigned short);
extern "C" unsigned long  _byteswap_ulong(unsigned long);
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong)
class IOStream {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual int  v14();
    virtual void v18();
    virtual unsigned v1c();
    virtual void v20();
    virtual void* v24(int);
    virtual void v28(int, int);
    virtual unsigned v2c();
    virtual int  v30(void* buf, int n);
    virtual void v34();
    virtual bool v38(void* buf, int n);
};
// ---- items of slice s00939a60 end

// ---- items of slice s0093a9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned int size_type;
namespace EA {
namespace IO {
class IStream_s0093_a9d0 {
public:
    virtual             ~IStream_s0093_a9d0() {}                 // +00 dtor
    virtual int         AddRef();                    // +04
    virtual int         Release();                   // +08
    virtual uint32      GetType() const;             // +0c
    virtual int         GetAccessFlags() const;      // +10
    virtual int         GetState() const;            // +14
    virtual bool        Close();                     // +18
    virtual size_type   GetSize() const;             // +1c
    virtual bool        SetSize(size_type size);      // +20
    virtual int         GetPosition(int type) const; // +24
    virtual bool        SetPosition(int distance, int type); // +28
    virtual int         GetAvailable() const;        // +2c
    virtual int         Read(void* pData, size_t nSize);     // +30
    virtual bool        Flush();                     // +34
    virtual bool        Write(const void* pData, size_t nSize); // +38
};
}
}
namespace EA {
namespace IO {
class FixedMemoryStream : public IStream_s0093_a9d0 {
public:
    virtual int       AddRef();
    virtual int       Release();
    virtual uint32    GetType() const;
    virtual int       GetAccessFlags() const;
    virtual int       GetState() const;
    virtual bool      Close();
    virtual size_type GetSize() const;
    virtual bool      SetSize(size_type size);
    virtual int       GetPosition(int type) const;
    virtual bool      SetPosition(int distance, int type);
    virtual int       GetAvailable() const;
    virtual int       Read(void* pData, size_t nSize);
    virtual bool      Flush();
    virtual bool      Write(const void* pData, size_t nSize);

    bool SetData(const void* pData, size_type nSize);

    void*     mpData;      // +04
    int       mnRefCount;  // +08
    size_type mnSize;      // +0c
    size_type mnCapacity;  // +10
    size_type mnPosition;  // +14
};
}
}
// ---- items of slice s0093a9d0 end

// ---- items of slice s0093b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" int   fputs(const char*, void*);
extern "C" unsigned __cdecl strlen(const char*);
extern "C" unsigned __cdecl wcslen(const wchar_t*);
extern void* g_vtbl_c430;
#pragma intrinsic(strlen)
#pragma intrinsic(wcslen)
extern "C" void* __iob_func_s0093_b9e0();
namespace EA {
namespace IO {
class SharedPointer_s0093_b9e0 { public:
    // +4 is a second base subobject (hkReferencedObject): its own vptr then a refcount.
    struct SharedRef {
        void* vtable;            // +0 (SharedPointer +4)
        long  mnRefCount;        // +4 (SharedPointer +8)
    };
    void*     vtable;            // +0
    SharedRef base2;             // +4
    void*     mpAllocator;       // +0c
    long      field_10;          // +10
    unsigned char field_14;      // +14
    SharedPointer_s0093_b9e0(void* pData, unsigned char freeData, void* alloc);
    SharedPointer_s0093_b9e0* Init(void* pData, unsigned nSize);                        // 0x0093bca0
    SharedPointer_s0093_b9e0* InitWithAlloc(void* pData, void* alloc, unsigned nSize);  // 0x0093bcf0
    void* Destroy(unsigned char flags);                                      // 0x0093bd90
};
}
}
namespace EA {
namespace IO {
inline void SharedRelease(SharedPointer_s0093_b9e0* p)
{
    if (p != 0) {
        SharedPointer_s0093_b9e0::SharedRef* r = &p->base2;
        long remaining = _InterlockedDecrement(&r->mnRefCount);
        if (remaining == 0) {
            _InterlockedExchange(&r->mnRefCount, 1);
            if (r != 0) {
                // The second base's vtable slot 0 is its Release/delete hook; `this` is the
                // base subobject (p + 4), not the vptr value (hybrid crash at 0x93bd97).
                typedef void (__thiscall *Fn)(void*, int);
                Fn fn = *(Fn*)r->vtable;
                fn(r, 1);
            }
        }
    }
}
}
}
namespace EA {
namespace IO {
class IStream_s0093_b9e0 {
public:
    virtual ~IStream_s0093_b9e0() {}
    virtual int AddRef();
    virtual int Release();
    virtual uint32 GetType() const;
    virtual int GetAccessFlags() const;
    virtual int GetState() const;
    virtual bool Close();
    virtual size_type GetSize() const;
    virtual bool SetSize(size_type size);
    virtual int GetPosition(int type) const;
    virtual bool SetPosition(int distance, int type);
    virtual int GetAvailable() const;
    virtual int Read(void* pData, size_t nSize);
    virtual bool Flush();
    virtual int Write(const void* pData, size_t nSize);
};
}
}
namespace EA {
namespace IO {
class MemoryStream_s0093_b9e0 : public IStream_s0093_b9e0 {
public:
    MemoryStream_s0093_b9e0(void* pData, size_type nSize, unsigned char copy, int a, void* alloc, int unused);  // 0x0093c2c0 (EA::IO::MemoryStream::MemoryStream_s0093_b9e0)
    ~MemoryStream_s0093_b9e0();  // 0x0093c2c0 (EA::IO::MemoryStream::MemoryStream_s0093_b9e0)

    bool SetData(void* pData, size_type nSize, unsigned char copy, unsigned char freeData, void* alloc);  // 0x0093be30 (EA::IO::MemoryStream::SetData)
    bool Clear();
    bool Grow(size_type size);  // 0x0093c000 (EA::IO::MemoryStream::Grow)
    bool WriteBuffer(const void* pData, size_type nSize);  // 0x0093c150 (EA::IO::MemoryStream::WriteBuffer)
    int  ReadBuffer(void* pData, size_type nSize);
    bool SetSizeEx(size_type size);  // 0x0093c130 (EA::IO::MemoryStream::SetSizeEx)
    virtual bool SetSize(size_type size);
    virtual bool SetPosition(int distance, int type);  // 0x0093c0c0 (EA::IO::MemoryStream::SetPosition)
    virtual int  Write(const void* pData, size_t nSize);

    SharedPointer_s0093_b9e0* mpSharedPointer;  // +04
    int            mnRefCount;       // +08
    size_type      mnSize;           // +0c
    size_type      mnCapacity;       // +10
    size_type      mnPosition;       // +14
    bool           mbResizeEnabled;  // +18
    bool           mbLocked;         // +19
    float          mfResizeFactor;   // +1c
    int            mnResizeIncrement;// +20
};
}
}
namespace EA {
namespace IO {
class GraphicsFactoryAsyncRequest {
public:
    GraphicsFactoryAsyncRequest();
    GraphicsFactoryAsyncRequest(void* pData, void* nSize, int unused);

    float GetProperty(int index);
    void  SetProperty(int index, float value);
    bool  Attach(void* pData, size_type nSize);

    void*          mpVtbl;           // +00
    SharedPointer_s0093_b9e0* mpData;           // +04
    int            mnField08;        // +08
    size_type      mnSize;           // +0c
    size_type      mnCapacity;       // +10
    size_type      mnPosition;       // +14
    bool           mbFlag18;         // +18
    bool           mbFlag19;         // +19
    float          mfFactor;         // +1c
    int            mnIncrement;      // +20
};
}
}
// ---- items of slice s0093b9e0 end

// ---- items of slice s0093c950 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
struct WStr {
    wchar_t* mpBegin;     // +0
    wchar_t* mpEnd;       // +4
    wchar_t* mpCapacity;  // +8
    void AllocateSelf(unsigned int nCount);
    void Append(const wchar_t* pFirst, const wchar_t* pLast);
};
}
}
namespace EA {
namespace Text {
struct WStrCtor : public WStr {
    WStrCtor(const wchar_t* pSource, int nCount, int nExtra);
};
}
}
// ---- items of slice s0093c950 end

// ---- items of slice s0093d740 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_fn154eb48;                       // 0x0154eb48: EA::Variant type-proc
extern "C" void* __cdecl FUN_00f473a0(unsigned, const char*, int, int, const char*, int); // 0x00f473a0 allocator
extern "C" void  __cdecl FUN_00f47380(void*);                                            // 0x00f47380 deallocator
extern "C" void* __cdecl FUN_011e0744(void*, const void*, unsigned);  // 0x011e0744 memcpy thunk
extern "C" wchar_t WSTR_01667bac[];                                       // 0x01667bac EASTL empty wide string
typedef void* (__cdecl* MoveFn)(void*, const void*, unsigned);
namespace EA {
struct Variant_s0093_d740 {
    union {
        unsigned int   value0;  // +0x00
        unsigned short value0w; // +0x00 low word (SetVariant8 writes only the low word)
    };
    unsigned int   value1;      // +0x04
    unsigned int   value2;      // +0x08
    unsigned int   value3;      // +0x0c
    unsigned short mFlags;      // +0x10
    unsigned short mTypeId;     // +0x12

    Variant_s0093_d740() : mFlags(0), mTypeId(0) {}
    ~Variant_s0093_d740() {
        if (mFlags & 4)
            ((void(__cdecl*)(int, Variant_s0093_d740*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
    }

    void Destruct(char bFree);  // 0x0093db80 (EA::Variant::Destruct)
    // Real retail symbol at 0x0093dd80 (?Construct@Variant@EA@@IAE_NGGPBXII@Z). Declared only:
    // the setters must emit a real out-of-line call, so the byte diff and the call trace match.
    bool Construct(unsigned short type, unsigned short flags, const void* src, unsigned int width, unsigned int isAtomic); // 0x0093dd80
    Variant_s0093_d740* SetBool(const unsigned char* p);
    Variant_s0093_d740* SetUInt16(const unsigned short* p);
    Variant_s0093_d740* SetUInt8(const unsigned char* p);
    Variant_s0093_d740* SetInt8(const unsigned char* p);
    Variant_s0093_d740* SetUInt16b(const unsigned short* p);
    Variant_s0093_d740* SetU32(const unsigned int* p);  // 0x00422eb0 (EA::Variant::SetU32)
    Variant_s0093_d740* SetDouble(const double* p);
    Variant_s0093_d740* SetPtr(const unsigned short* p);
    Variant_s0093_d740* SetVariant8(const unsigned short* p);
};
}
namespace EA {
#define VAR_PRELUDE(N, W)                                                        \
    if (mFlags & 4) {                                                            \
        ((void(__cdecl*)(int, Variant_s0093_d740*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0); \
        if ((mFlags & 2) == 0) { mTypeId = 0; mFlags = 0; }                      \
    }                                                                            \
    unsigned short f = mFlags & 2;                                               \
    if (f != 0 && mTypeId != (N)) { Construct((N), 0, p, (W), 1); return this; }
}
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetBool(const unsigned char* p) {
    VAR_PRELUDE(2, 1)
    unsigned char v = *p;
    mFlags = f; mTypeId = 2;
    *(unsigned char*)&value0 = v;
    return this;
}
}
using EA::Variant_s0093_d740;
struct HashTable {
    unsigned int  field_0;      // +0x00
    unsigned int* mpBuckets;    // +0x04
    unsigned int  mnBucketCount;// +0x08
    unsigned int  mnElementCount;// +0x0c
    void*         mpAlloc;      // +0x10

    void Rehash(unsigned n);                       // 0x0093DCC0
    void* Find(void** out, const void* key);       // 0x0093E3F0
    void Insert(void** out, int* key);             // 0x0093E470
};
struct WStr_s0093_d740 {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpEndCap;  // +0x08
    void*    mpAlloc;   // +0x0c
};
struct WStrVec {
    WStr_s0093_d740* mpBegin;      // +0x00
    WStr_s0093_d740* mpEnd;        // +0x04
    WStr_s0093_d740* mpEndCap;     // +0x08
};
extern void __fastcall FUN_00553e60(WStrVec* self, int, unsigned n);      // 0x00553e60 vector<WStr>::resize
extern void __fastcall FUN_00423650(WStr_s0093_d740* self, int, const wchar_t* b, const wchar_t* e); // 0x00423650 WStr::Assign
extern void __fastcall FUN_00429520(WStr_s0093_d740* self, int, unsigned n);         // 0x00429520 WStr::Resize
static void WStr_EraseRange(WStr_s0093_d740* t, unsigned pos, unsigned n);  // 0x0093df20 (defined below; used by a stub's inline body)
static void WStr_StripQuotes(WStr_s0093_d740* t) {
    if (t->mpBegin != t->mpEnd && t->mpBegin[0] == 0x22 && t->mpEnd[-1] == 0x22) {
        unsigned len = (unsigned)(t->mpEnd - t->mpBegin);
        WStr_EraseRange(t, len - 1, 1);
        WStr_EraseRange(t, 0, 1);
    }
}
// ---- items of slice s0093d740 end

// ---- items of slice s0093e5f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) char*    __cdecl _ltoa(long value, char* buffer, int base);
extern "C" __declspec(dllimport) char*    __cdecl _ultoa(unsigned long value, char* buffer, int base);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long value, wchar_t* buffer, int base);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ultow(unsigned long value, wchar_t* buffer, int base);
extern char gEmptyString[];                                    // 0x01667bac (EASTL empty-string storage)
typedef unsigned int eastl_size_t;
void* operator new[](unsigned int size, const char* pName, int flags, unsigned debugFlags,
                     const char* pFile, int line);              // 0x00f473a0
void operator delete[](void* p);                               // 0x00f47380
namespace eastl {
class allocator_s0093_e5f0 { public:};
}
namespace eastl {
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0093_e5f0 mAllocator;

    string() : mpBegin(0), mpEnd(0), mpCapacity(0) {
        mpBegin = gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    string(const char* p, const allocator_s0093_e5f0& a = allocator_s0093_e5f0());                     // 0x0057ed80
    string(const char* p, eastl_size_t n, const allocator_s0093_e5f0& a = allocator_s0093_e5f0());     // 0x005e96a0
    string(eastl_size_t n, char c, const allocator_s0093_e5f0& a = allocator_s0093_e5f0());            // 0x005f8f30
    ~string();                                                                   // 0x00530670

    const char* data() const { return mpBegin; }
    eastl_size_t size() const { return (eastl_size_t)(mpEnd - mpBegin); }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    string& assign(const char* p, eastl_size_t n);                               // 0x0060bcd0
    string& append(eastl_size_t n, char c);                                      // 0x0047bf30
};
}
namespace eastl {
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator_s0093_e5f0 mAllocator;

    wstring() : mpBegin(0), mpEnd(0), mpCapacity(0) {
        mpBegin = (wchar_t*)gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    wstring(const wchar_t* p, const allocator_s0093_e5f0& a = allocator_s0093_e5f0());                 // 0x0041df50
    wstring(const wchar_t* p, eastl_size_t n, const allocator_s0093_e5f0& a = allocator_s0093_e5f0()); // 0x0093d6f0
    wstring(eastl_size_t n, wchar_t c, const allocator_s0093_e5f0& a = allocator_s0093_e5f0());        // 0x0084a780
    ~wstring();                                                                  // 0x00933960

    const wchar_t* data() const { return mpBegin; }
    eastl_size_t size() const { return (eastl_size_t)(mpEnd - mpBegin); }
    void clear();                                                                // 0x005726c0
    wstring& assign(const wchar_t* p, eastl_size_t n);                           // 0x006ab7e0
    wstring& append(eastl_size_t n, wchar_t c);                                  // 0x0042d2e0
};
}
namespace eastl {
__forceinline void DestroyString(string* s) {
    if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
        delete[] s->mpBegin;
}
}
namespace eastl {
__forceinline void DestroyString(wstring* s) {
    if ((s->mpCapacity - s->mpBegin) > 1 && s->mpBegin)
        delete[] s->mpBegin;
}
}
namespace EA {
namespace StdC {
int64_t  StrtoI64(const char* p, char** ppEnd, int base);             // 0x0092d6b0
}
}
namespace EA {
namespace StdC {
int64_t  StrtoI64(const wchar_t* p, wchar_t** ppEnd, int base);       // 0x0092d6d0
}
}
namespace EA {
namespace StdC {
uint64_t StrtoU64(const char* p, char** ppEnd, int base);             // 0x0092d6f0
}
}
namespace EA {
namespace StdC {
uint64_t StrtoU64(const wchar_t* p, wchar_t** ppEnd, int base);       // 0x0092d710
}
}
namespace EA {
namespace StdC {
char*    I64toa(int64_t value, char* buffer, int base);                // 0x0092cff0
}
}
namespace EA {
namespace StdC {
char*    U64toa(uint64_t value, char* buffer, int base);               // 0x0092d040
}
}
namespace EA {
namespace StdC {
wchar_t* I64tow(int64_t value, wchar_t* buffer, int base);             // 0x0092d060
}
}
namespace EA {
namespace StdC {
wchar_t* U64tow(uint64_t value, wchar_t* buffer, int base);            // 0x0092d0d0
}
}
namespace EA {
namespace StdC {
char*    FtoaEnglish(double value, char* buffer, int bufferLength, int precision, bool bExponentEnabled);      // 0x0092d730
}
}
namespace EA {
namespace StdC {
wchar_t* FtoaEnglish(double value, wchar_t* buffer, int bufferLength, int precision, bool bExponentEnabled);   // 0x0092d9b0
}
}
namespace EA {
namespace StdC {
double   Strtod(const char* p);                                        // 0x00692700 (strtod wrapper)
}
}
namespace EA {
namespace StdC {
double   Strtod(const wchar_t* p);                                     // 0x00622f20 (wcstod wrapper)
}
}
namespace EA {
class IUnknown32 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
namespace EA {
struct Variant_s0093_e5f0 {
    enum eTypeId {
        kTypeUndefined = 0, kTypeBool = 1, kTypeChar8 = 2, kTypeChar16 = 3, kTypeChar32 = 4,
        kTypeInt8 = 5, kTypeUint8 = 6, kTypeInt16 = 7, kTypeUint16 = 8, kTypeInt32 = 9,
        kTypeUint32 = 10, kTypeInt64 = 11, kTypeUint64 = 12, kTypeFloat = 13, kTypeDouble = 14,
        kTypePointer = 15, kTypeVoid = 16, kTypeIUnknown32 = 17, kTypeString8 = 18,
        kTypeString16 = 19, kTypeString32 = 20
    };
    enum eFlags {
        kfNone = 0, kfTypeConstruct = 1, kfInvariant = 2, kfDestruct = 4, kfConstruct = 8,
        kfCArray = 16, kfRawPointer = 32, kfPointerPtr = 64
    };
    struct Pointer {
        void* mpData;
        unsigned int mElementSize;
        unsigned int mElementCount;
    };

    union {
        unsigned char mGeneric[16];
        Pointer mPointer;
        unsigned short mUint16;
    };
    unsigned short mFlags;
    unsigned short mTypeId;

    Variant_s0093_e5f0() : mFlags(0), mTypeId(0) {}
    ~Variant_s0093_e5f0();                                                          // 0x00571ee0
    Variant_s0093_e5f0& operator=(const Variant_s0093_e5f0& x);                                // 0x00542b80
    Variant_s0093_e5f0& operator=(const eastl::string& x);                          // 0x004b5dd0
    Variant_s0093_e5f0& operator=(const eastl::wstring& x);                         // 0x004279d0
    void Assign(int typeId, int flags, const void* pData, unsigned elementSize, unsigned elementCount);  // 0x0093dd80
    void* GetData();                                                     // 0x00446ff0
    unsigned GetCount();                                                 // 0x00571ef0
};
}
namespace EA {
template <typename T>
class VariantT : public Variant_s0093_e5f0 { public:
    VariantT(const T& value);
};
}
namespace EA {
typedef bool (*TypeProc)(int op, Variant_s0093_e5f0* pThis, Variant_s0093_e5f0** ppArgs, int nArgs, Variant_s0093_e5f0** ppResults, int nResults);
}
namespace EA {
extern TypeProc gpVariantTypeProc;                                       // 0x0154eb48
}
namespace EA {
enum { kOpDestruct = 1, kOpConstruct = 2, kOpConvert = 3 };
}
namespace EA {
__forceinline void FromString(char* pDest, const char* p)              { *pDest = p[0]; }
}
namespace EA {
__forceinline void FromString(char* pDest, const wchar_t* p)           { *pDest = (char)p[0]; }
}
namespace EA {
__forceinline void FromString(wchar_t* pDest, const char* p)           { *pDest = (wchar_t)p[0]; }
}
namespace EA {
__forceinline void FromString(wchar_t* pDest, const wchar_t* p)        { *pDest = p[0]; }
}
namespace EA {
__forceinline void FromString(int8_t* pDest, const char* p)            { *pDest = (int8_t)StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int8_t* pDest, const wchar_t* p)         { *pDest = (int8_t)StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint8_t* pDest, const char* p)           { *pDest = (uint8_t)StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint8_t* pDest, const wchar_t* p)        { *pDest = (uint8_t)StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int16_t* pDest, const char* p)           { *pDest = (int16_t)StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int16_t* pDest, const wchar_t* p)        { *pDest = (int16_t)StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint16_t* pDest, const char* p)          { *pDest = (uint16_t)StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint16_t* pDest, const wchar_t* p)       { *pDest = (uint16_t)StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int32_t* pDest, const char* p)           { *pDest = (int32_t)StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int32_t* pDest, const wchar_t* p)        { *pDest = (int32_t)StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint32_t* pDest, const char* p)          { *pDest = (uint32_t)StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint32_t* pDest, const wchar_t* p)       { *pDest = (uint32_t)StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int64_t* pDest, const char* p)           { *pDest = StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(int64_t* pDest, const wchar_t* p)        { *pDest = StdC::StrtoI64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint64_t* pDest, const char* p)          { *pDest = StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(uint64_t* pDest, const wchar_t* p)       { *pDest = StdC::StrtoU64(p, 0, 10); }
}
namespace EA {
__forceinline void FromString(float* pDest, const char* p)             { *pDest = (float)StdC::Strtod(p); }
}
namespace EA {
__forceinline void FromString(float* pDest, const wchar_t* p)          { *pDest = (float)StdC::Strtod(p); }
}
namespace EA {
__forceinline void FromString(double* pDest, const char* p)            { *pDest = StdC::Strtod(p); }
}
namespace EA {
__forceinline void FromString(double* pDest, const wchar_t* p)         { *pDest = StdC::Strtod(p); }
}
namespace EA {
template <typename T>
__forceinline bool ConvertToScalar(Variant_s0093_e5f0* pDest, Variant_s0093_e5f0* pSrc, unsigned short srcType)
{
    T* pResult = (T*)pDest->GetData();
    if (!pResult) {
        T value = 0;
        *pDest = VariantT<T>(value);
        pResult = (T*)pDest->GetData();
    }

    switch (srcType) {
        case Variant_s0093_e5f0::kTypeBool: {
            const bool* p = (const bool*)pSrc->GetData();
            if (p) { *pResult = (T)(*(const char*)p != 0); return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeChar8: {
            const char* p = (const char*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeChar16: {
            const wchar_t* p = (const wchar_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeInt8: {
            const int8_t* p = (const int8_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeUint8: {
            const uint8_t* p = (const uint8_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeInt16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeUint16: {
            const uint16_t* p = (const uint16_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeInt32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeUint32: {
            const uint32_t* p = (const uint32_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p) { *pResult = (T)*p; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeString8: {
            const eastl::string* p = (const eastl::string*)pSrc->GetData();
            if (p && p->size()) { FromString(pResult, p->data()); return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeString16: {
            const eastl::wstring* p = (const eastl::wstring*)pSrc->GetData();
            if (p && p->size()) { FromString(pResult, p->data()); return true; }
            break;
        }
        default:
            return true;
    }

    *pResult = 0;
    return true;
}
}
namespace EA {
__forceinline bool ConvertToBool(Variant_s0093_e5f0* pDest, Variant_s0093_e5f0* pSrc, unsigned short srcType)
{
    bool* pResult = (bool*)pDest->GetData();
    if (!pResult) {
        bool value = true;
        *pDest = VariantT<bool>(value);
        pResult = (bool*)pDest->GetData();
    }

    switch (srcType) {
        case Variant_s0093_e5f0::kTypeUndefined:
            break;
        case Variant_s0093_e5f0::kTypeChar8:
        case Variant_s0093_e5f0::kTypeInt8:
        case Variant_s0093_e5f0::kTypeUint8: {
            const char* p = (const char*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeChar16:
        case Variant_s0093_e5f0::kTypeInt16:
        case Variant_s0093_e5f0::kTypeUint16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeInt32:
        case Variant_s0093_e5f0::kTypeUint32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p && *p != 0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p && *p != 0.0f) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p && *p != 0.0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeIUnknown32:
            *pResult = (pSrc->GetData() != 0);
            return true;
        case Variant_s0093_e5f0::kTypeString8: {
            const eastl::string* p = (const eastl::string*)pSrc->GetData();
            if (p && p->size() != 0) { *pResult = true; return true; }
            break;
        }
        case Variant_s0093_e5f0::kTypeString16: {
            const eastl::wstring* p = (const eastl::wstring*)pSrc->GetData();
            if (p && p->size() != 0) { *pResult = true; return true; }
            break;
        }
        default:
            return true;
    }

    *pResult = false;
    return true;
}
}
namespace EA {
__forceinline bool ConvertToString8(Variant_s0093_e5f0* pDest, Variant_s0093_e5f0* pSrc, unsigned short srcType)
{
    eastl::string* pResult = (eastl::string*)pDest->GetData();
    if (!pResult) {
        *pDest = VariantT<eastl::string>(eastl::string((eastl_size_t)0, (char)0));
        pResult = (eastl::string*)pDest->GetData();
    }

    char buffer[64];

    switch (srcType) {
        case Variant_s0093_e5f0::kTypeBool: {
            const bool* p = (const bool*)pSrc->GetData();
            if (p) *pDest = eastl::string(1, (char)(*(const char*)p ? 'T' : 0));
            break;
        }
        case Variant_s0093_e5f0::kTypeChar8:
            pResult->assign((const char*)pSrc->GetData(), pSrc->GetCount());
            break;
        case Variant_s0093_e5f0::kTypeChar16: {
            const wchar_t* p = (const wchar_t*)pSrc->GetData();
            unsigned n = pSrc->GetCount();
            pResult->clear();
            for (unsigned i = 0; i < n; ++i)
                pResult->append(1, (char)p[i]);
            break;
        }
        case Variant_s0093_e5f0::kTypeInt8: {
            const int8_t* p = (const int8_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ltoa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint8: {
            const uint8_t* p = (const uint8_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ultoa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeInt16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ltoa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint16: {
            const uint16_t* p = (const uint16_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ultoa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeInt32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ltoa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint32: {
            const uint32_t* p = (const uint32_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(_ultoa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::I64toa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::U64toa(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant_s0093_e5f0::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p) *pDest = eastl::string(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant_s0093_e5f0::kTypeString16: {
            const eastl::wstring* p = (const eastl::wstring*)pSrc->GetData();
            if (p) {
                const eastl_size_t n = p->size();
                if (n) {
                    for (const wchar_t* pc = p->data(), *pEnd = pc + n; pc < pEnd; ++pc)
                        pResult->append(1, (char)*pc);
                }
            }
            break;
        }
    }
    return true;
}
}
namespace EA {
__forceinline bool ConvertToString16(Variant_s0093_e5f0* pDest, Variant_s0093_e5f0* pSrc, unsigned short srcType)
{
    eastl::wstring* pResult = (eastl::wstring*)pDest->GetData();
    if (!pResult) {
        *pDest = VariantT<eastl::wstring>(eastl::wstring((eastl_size_t)0, (wchar_t)0));
        pResult = (eastl::wstring*)pDest->GetData();
    }

    wchar_t buffer[64];

    switch (srcType) {
        case Variant_s0093_e5f0::kTypeBool: {
            const bool* p = (const bool*)pSrc->GetData();
            if (p) {
                const char c = *(const char*)p ? 'T' : 0;
                *pDest = eastl::wstring(1, (wchar_t)c);
            }
            break;
        }
        case Variant_s0093_e5f0::kTypeChar8: {
            const char* p = (const char*)pSrc->GetData();
            unsigned n = pSrc->GetCount();
            pResult->clear();
            for (unsigned i = 0; i < n; ++i)
                pResult->append(1, (wchar_t)p[i]);
            break;
        }
        case Variant_s0093_e5f0::kTypeChar16:
            pResult->assign((const wchar_t*)pSrc->GetData(), pSrc->GetCount());
            break;
        case Variant_s0093_e5f0::kTypeInt8: {
            const int8_t* p = (const int8_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ltow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint8: {
            const uint8_t* p = (const uint8_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ultow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeInt16: {
            const int16_t* p = (const int16_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ltow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint16: {
            const uint16_t* p = (const uint16_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ultow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeInt32: {
            const int32_t* p = (const int32_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ltow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint32: {
            const uint32_t* p = (const uint32_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(_ultow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeInt64: {
            const int64_t* p = (const int64_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::I64tow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeUint64: {
            const uint64_t* p = (const uint64_t*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::U64tow(*p, buffer, 10));
            break;
        }
        case Variant_s0093_e5f0::kTypeFloat: {
            const float* p = (const float*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant_s0093_e5f0::kTypeDouble: {
            const double* p = (const double*)pSrc->GetData();
            if (p) *pDest = eastl::wstring(StdC::FtoaEnglish(*p, buffer, 64, 16, false));
            break;
        }
        case Variant_s0093_e5f0::kTypeString8: {
            const eastl::string* p = (const eastl::string*)pSrc->GetData();
            if (p) {
                const char* pc = p->mpBegin;
                const char* pEnd = p->mpEnd;
                if (pEnd - pc) {
                    for (; pc < pEnd; ++pc)
                        pResult->append(1, (wchar_t)*pc);
                }
            }
            break;
        }
    }
    return true;
}
}
// ---- items of slice s0093e5f0 end

// @ 0x00931770
bool EnsureTrailingBackslash(WString* s)
{
    wchar_t* b = s->mpBegin;
    if (b != s->mpEnd) {
        unsigned c = b[(s->mpEnd - b) - 1];
        if (c == '\\' || c == '/' || c == ':')
            return false;
    }
    s->push_back('\\');
    return true;
}

// @ 0x00931f20
namespace File {
bool Create(const wchar_t* path, bool truncate)
{
    SECURITY_ATTRIBUTES sa;
    sa.nLength = 12;
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = 0;
    HANDLE h = CreateFileW(path, 0x80000000, 3, &sa, 4, 0x80, 0);
    if (h != INVALID_HANDLE_VALUE) {
        if (truncate) {
            SetFilePointer(h, 0, 0, 0);
            SetEndOfFile(h);
        }
        CloseHandle(h);
        return true;
    }
    return false;
}
}  // namespace File

// @ 0x009323c0
int GetSystemPath(int type, wchar_t* buf, bool checkExists)
{
    if (type == 1) {
        bool ok = GetTempPathW_s0093_23c0(0x104, buf) != 0;
        if (!ok)
            return -1;
    } else if (type == 2) {
        bool ok = GetWindowsDirectoryW(buf, 0x104) != 0;
        if (!ok)
            return -1;
    } else if (type == 5) {
        wchar_t modbuf[260];
        void* h = GetModuleHandleA_s0093_23c0(0);
        if (GetModuleFileNameW_s0093_23c0(h, modbuf, 0x104) == 0)
            return -1;
        wchar_t* tail;
        if (GetFullPathNameW_s0093_23c0(modbuf, 0x104, buf, &tail) == 0)
            return -1;
        *tail = 0;
    } else {
        uint32_t flags = checkExists ? 0x8000 : 0;
        uint32_t csidl = g_folderTable[type * 2];
        if (csidl == 0 || SHGetFolderPathW(0, csidl | flags, 0, 0, buf) < 0) {
            csidl = g_folderTable[type * 2 + 1];
            if (csidl == 0)
                return -1;
            if (SHGetFolderPathW(0, csidl | flags, 0, 0, buf) < 0)
                return -1;
        }
        const wchar_t* p = buf;
        while (*p)
            p++;
        int len = (int)(p - buf);
        if (len != 0 && !EA::IO::IsFilePathSeparator(buf[len - 1])) {
            if (len > 0x102)
                return -1;
            buf[len] = L'\\';
            buf[len + 1] = 0;
        }
    }
    if (checkExists) {
        if (buf == 0 || buf[0] == 0)
            return -1;
        unsigned int a = GetFileAttributesW_s0093_23c0(buf);
        if (a == 0xffffffff || (a & 0x10) == 0)
            return -1;
    }
    const wchar_t* p = buf;
    while (*p)
        p++;
    return (int)(p - buf);
}

// @ 0x009326b0
bool DeleteDirectoryContents(wchar_t* path, uint32_t len)
{
    DirectoryIterator it = {};
    ICoreAllocator* alloc = GetDefaultAllocatorX();
    Deque list;
    list.mpPtrArray = 0;
    list.mnPtrArraySize = 0;
    list.mItBegin = DequeIter();
    list.mItEnd = DequeIter();
    list.mpAllocator = alloc;
    list.mpName = 0;
    list.DoInit(0);

    bool ok = true;
    if (it.Read(path, &list, 0, 3, 0x100000, 0)) {
        if (len != 0 && !IsPathSeparator(path[len - 1]) && len < 0x103) {
            path[len] = L'\\';
            len++;
        }
        for (DequeIter i = list.mItBegin; i != list.mItEnd; ++i) {
            Entry& e = *i;
            uint32_t n = (uint32_t)(e.mName.mpEnd - e.mName.mpBegin);
            if (len + n < 0x104) {
                memcpy(path + len, e.mName.mpBegin, n * 2);
                path[len + n] = 0;
                if (e.mType == 1) {
                    if (!DeleteDirectoryContents(path, len + n))
                        ok = false;
                } else if (!DeleteFileW(path)) {
                    ok = false;
                }
            } else {
                ok = false;
            }
        }
    }
    path[len] = 0;
    bool result = false;
    if (RemoveDirectoryRecursive(path, 0))
        result = ok;
    list.Destroy();
    return result;
}

// @ 0x00932890
uint32_t RemoveDirectoryRecursive(const wchar_t* path, char recursive)
{
    wchar_t buf[260];
    if (recursive != 0) {
        const wchar_t* s = path;
        wchar_t* d = buf;
        while ((*d++ = *s++) != 0)
            ;
        const wchar_t* q = buf;
        while (*q)
            q++;
        return DeleteDirectoryContents(buf, (int)(q - buf));
    }
    const wchar_t* p = path;
    while (*p)
        p++;
    wchar_t c = p[-1];
    if (c != L'\\' && c != L'/' && c != L':') {
        int r = RemoveDirectoryW(path);
        return (uint32_t)(r != 0);
    }
    const wchar_t* q = path;
    while (*q)
        q++;
    int r = RemoveDirectoryW(path);
    return (uint32_t)(r != 0);
}

// @ 0x00932df0
uint64_t CRC64(const uint8_t* p, int len, uint64_t crc, bool finalize)
{
    const uint8_t* end = p + len;
    for (; p < end; p++) {
        uint32_t idx = ((uint32_t)(crc >> 56) ^ (uint32_t)*p) & 0xff;
        crc = (crc << 8) ^ g_crc64Table[idx];
    }
    if (finalize)
        crc = ~crc;
    return crc;
}

// @ 0x00935d30
void GetApplicationPath(wchar_t* buf)
{
    unsigned long n = GetModuleFileNameW_s0093_50f0(0, buf, 0x104);
    if (n == 0 || n >= 0x104)
        buf[0] = 0;
}

// @ 0x00935d60
int WideSpawn(const wchar_t* path, const wchar_t* const* argv, bool wait)
{
    if (wait)
        return _wspawnv(0, path, argv);
    return _wspawnv(4, path, argv);
}

// @ 0x00936050
void RandomBytes(unsigned char* buf, unsigned n)
{
    uint64_t t = __rdtsc();
    for (unsigned i = 0; i < n; ++i)
        buf[i] = (unsigned char)(t >> ((i & 7) * 8));
}

// @ 0x00936110
namespace EA { namespace Random {
uint32_t RandomMersenneTwister_s0093_6090::Reload()
{
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
    // The retail tail leaves a leftover in eax: mState[0] (the first operand of the wrap-around y,
    // `mov eax,[mState]`) with its low byte masked by the scalar `and al,1` of that computation,
    // never reloaded before `ret`. Dead for the game, but LTCG callers can observe it, so hand
    // the same value back. The volatile read keeps cl from folding it into the earlier y code.
    return *(volatile uint32_t*)mState & 0xffffff01u;
}
}}  // namespace EA::Random

// @ 0x009361f0
namespace EA { namespace Random {
void RandomMersenneTwister_s0093_6090::InitState(uint32_t seed)
{
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
}}  // namespace EA::Random

// @ 0x00936250
namespace EA { namespace Random {
uint32_t RandomMersenneTwister_s0093_6090::Generate()
{
    RandomMersenneTwister_s0093_6090* self = this;
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
}}  // namespace EA::Random

// @ 0x009362b0
namespace EA { namespace Random {
uint32_t RandomMersenneTwister_s0093_6090::GenerateUInt32(uint32_t max)
{
    return (uint32_t)(((uint64_t)Generate() * max) >> 32);
}
}}  // namespace EA::Random

// @ 0x009362d0
namespace EA { namespace Random {
double RandomMersenneTwister_s0093_6090::GenerateDouble()
{
    int v = (int)Generate();
    double f = (double)v * 2.3283064365386963e-10 + 0.5;
    if (f < 1.0)
        return f;
    return 0.0;
}
}}  // namespace EA::Random

// @ 0x00936300
namespace EA { namespace Random {
RandomMersenneTwister_s0093_6090* RandomMersenneTwister_s0093_6090::SetSeed(uint32_t seed)
{
    mpNext = 0;
    mnCount = 0x270;
    ((MTOpsShim*)this)->InitState(seed);
    return this;
}
}}  // namespace EA::Random

// @ 0x0093a610
int StreamCopy(IOStream* src, IOStream* dst, unsigned count)
{
    uint32_t buf[0x200];
    unsigned size = src->v1c();
    if (size == 0xffffffffu) {
        count = size;
    } else if (count > size) {
        count = size;
    }
    unsigned total = count;
    while (total != 0) {
        unsigned chunk = total >= 0x800 ? 0x800 : total;
        int r = src->v30(buf, chunk);
        if (r == -1 || !dst->v38(buf, r))
            return -1;
        if (r == 0)
            break;
        total -= r;
    }
    return (int)(count - total);
}

// @ 0x0093a700
bool ReadUInt16(IOStream* s, unsigned short* buf, int count, int bigEndian)
{
    if (bigEndian != 1)
        s->v10();
    if (s->v14())
        return false;
    bool ok = false;
    if (s->v30(buf, count * 2) == count * 2) {
        if (bigEndian != 1) {
            while (count--) {
                *buf = _byteswap_ushort(*buf);
                ++buf;
            }
        }
        ok = true;
    }
    return ok;
}

// @ 0x0093b8b0
namespace EA { namespace IO {
int FixedMemoryStream::Release()
{
    if (mnRefCount > 1) {
        int n = mnRefCount - 1;
        mnRefCount = n;
        return n;
    }
    delete this;
    return 0;
}
}}  // namespace EA::IO

// @ 0x0093bab0
float __thiscall EA::IO::GraphicsFactoryAsyncRequest::GetProperty(int index)
{
    switch (index) {
    case 1: return mbFlag18 ? 1.0f : 0.0f;
    case 2: return mfFactor;
    case 3: return (float)mnIncrement;
    case 4: return mbFlag19 ? 1.0f : 0.0f;
    default: return 0.0f;
    }
}

// @ 0x0093bb40
void __thiscall EA::IO::GraphicsFactoryAsyncRequest::SetProperty(int index, float value)
{
    switch (index) {
    case 1:
        mbFlag18 = (value != 0.0f);
        return;
    case 2:
        if (value < 1.0f) value = 1.0f;
        mfFactor = value;
        return;
    case 3:
        if (value < 0.0f) value = 0.0f;
        mnIncrement = (int)value;
        return;
    case 4:
        mbFlag19 = (value != 0.0f);
        return;
    default:
        return;
    }
}

// @ 0x0093bbf0
int __thiscall EA::IO::MemoryStream_s0093_b9e0::ReadBuffer(void* pData, size_type nSize)
{
    if (nSize != 0) {
        size_type avail = mnSize - mnPosition;
        if (avail != 0) {
            if (avail < nSize)
                nSize = avail;
            MemCpyThunk(pData, (char*)mpSharedPointer->field_10 + mnPosition, nSize);
            mnPosition += nSize;
            return nSize;
        }
    }
    return 0;
}

// @ 0x0093c320
bool __thiscall EA::IO::MemoryStream_s0093_b9e0::Clear()
{
    SharedRelease(mpSharedPointer);
    mpSharedPointer = 0;
    mnCapacity = 0;
    mnSize = 0;
    mnPosition = 0;
    return true;
}

// @ 0x0093c3f0
int __fastcall FUN_0093c3f0(void** self)
{
    if ((int)(long)self[1] > 1) {
        int n = (int)(long)self[1] - 1;
        self[1] = (void*)(long)n;
        return n;
    }
    typedef void (__thiscall *Fn)(void*, int);
    (*(Fn*)self[0])(self, 1);
    return 0;
}

// @ 0x0093c430
void* __fastcall FUN_0093c430(void** self)
{
    *self = (void*)&g_vtbl_c430;
    self[1] = 0;
    return self;
}

// @ 0x0093c6f0
namespace EA {
void FUN_0093c6f0(const char* s)
{
    if (s != 0)
        fputs(s, (char*)__iob_func_s0093_b9e0() + 0x20);
}
}  // namespace EA

// @ 0x0093d0b0
namespace EA { namespace Text {
const char* GetTextLine(const char* pText, const char* pTextEnd, const char** ppNewText)
{
    if (pText < pTextEnd) {
        while ((pText < pTextEnd) && (*pText != '\r') && (*pText != '\n'))
            ++pText;

        if (ppNewText) {
            *ppNewText = pText;

            if (*ppNewText < pTextEnd) {
                if ((++*ppNewText < pTextEnd) && ((**ppNewText ^ *pText) == ('\r' ^ '\n')))
                    ++*ppNewText;
            }
        }
    } else if (ppNewText) {
        *ppNewText = pTextEnd;
    }
    return pText;
}
}}  // namespace EA::Text

// @ 0x0093d110
namespace EA { namespace Text {
bool GetToken(char* pText, char* pTextEnd, char cDelimiter, char** ppBegin, char** ppEnd, char** ppOut)
{
    int nQuote = 0;
    *ppBegin = pText;
    while (pText < pTextEnd) {
        char c = **ppBegin;
        if ((c != ' ') && (c != '\t'))
            break;
        pText = *ppBegin + 1;
        *ppBegin = pText;
    }
    *ppEnd = *ppBegin;
    if (*ppBegin < pTextEnd) {
        do {
            char* pCur = *ppEnd;
            char* pNext = pCur + 1;
            char c = *pCur;
            bool bLast = (pNext == pTextEnd);
            bool bFound;
            if (cDelimiter == ' ')
                bFound = (c == cDelimiter) || (c == '\t');
            else
                bFound = (c == cDelimiter);
            if (!bFound) {
                if (bLast) {
                    *ppEnd = pNext;
                    bFound = true;
                } else if (c == '"') {
                    ++nQuote;
                }
            }
            if (bFound && (((nQuote & 1) == 0) || bLast))
                goto Found;
            ++*ppEnd;
        } while (*ppEnd < pTextEnd);
    }
    if (ppOut)
        *ppOut = *ppEnd;
    return false;

Found:
    if (ppOut)
        *ppOut = *ppEnd;
    if ((cDelimiter != ' ') && (*ppEnd != pTextEnd) && (*ppEnd != *ppBegin)) {
        char* q;
        do {
            q = *ppEnd;
            char d = q[-1];
            --q;
            if ((d != ' ') && (d != '\t'))
                break;
            *ppEnd = q;
        } while (q != *ppBegin);
    }
    if ((*ppBegin != pTextEnd) && (**ppBegin == '"') && (*(*ppEnd - 1) == '"')) {
        ++*ppBegin;
        --*ppEnd;
    }
    return true;
}
}}  // namespace EA::Text

// @ 0x0093d6f0
namespace EA { namespace Text {
WStrCtor::WStrCtor(const wchar_t* pSource, int nCount, int /*nExtra*/)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    const wchar_t* pSourceEnd = pSource + nCount;
    const int n = (int)(pSourceEnd - pSource);
    AllocateSelf((unsigned int)(n + 1));
    wchar_t* pDst = mpBegin;
    memcpy(pDst, pSource, (unsigned int)(n * 2));
    mpEnd = pDst + n;
    *mpEnd = 0;
}
}}  // namespace EA::Text

// @ 0x0093d740
int VariantToString(const unsigned short* srcArg, int n, unsigned short sep, void** outVec, int f)
{
    const wchar_t* src = (const wchar_t*)srcArg;
    WStrVec* out = (WStrVec*)outVec;
    int count = 0;

    const wchar_t* end;
    if (n == -1) {
        const wchar_t* q = src;
        while (*q) ++q;
        end = q;
    } else {
        end = src + n;
    }

    const wchar_t* p = src;
    while (p < end && (*p == 0x20 || *p == 9)) ++p;
    if (p == end) return 0;

    const wchar_t* e = end - 1;
    while (e >= src && (*p == 0x20 || *p == 9)) --e;
    int len = (int)(e + 1 - p);

    wchar_t* buf;
    bool allocated = (len + 1 > 1);
    if (allocated) {
        buf = (wchar_t*)FUN_00f473a0((unsigned)((len + 1) * 2), (const char*)0x13ebb38, 0, 0, (const char*)0x13f2150, 0xd1);
    } else {
        buf = WSTR_01667bac;
    }
    FUN_011e0744(buf, p, (unsigned)(len * 2));
    buf[len] = 0;

    int totalLen = len;
    int i = 0;
    int start = 0;
    int quoteCount = 0;
    int byteOffset = 0;

    if (totalLen != 0) {
        for (;;) {
            if ((unsigned)count >= (unsigned)f) goto finalEmit;
            {
                wchar_t c = buf[i];
                bool isSep = (sep == 0x20) ? (c == sep || c == 9) : (c == sep);
                if (isSep) {
                    if ((quoteCount & 1) == 0) goto emitMid;
                    // odd quote count: this separator sits inside a quoted run
                } else if (c == 0x22) {
                    ++quoteCount;
                }
            }
        advance:
            ++i;
            if (i < totalLen) continue;
            goto finalEmit;
        }

    emitMid:
        {
            // A separator boundary always yields a token (possibly empty); the
            // trailing/final emit is the only one that skips empty tokens.
            if ((unsigned)(out->mpEnd - out->mpBegin) / 16 <= (unsigned)count)
                FUN_00553e60(out, 0, (unsigned)(count + 1));
            WStr_s0093_d740* t = &out->mpBegin[count];
            FUN_00423650(t, 0, buf + start, buf + i);
            if (sep != 0x20) {
                int tlen = (int)(t->mpEnd - t->mpBegin);
                int k = tlen - 1;
                while (k >= 0 && (t->mpBegin[k] == 0x20 || t->mpBegin[k] == 9)) --k;
                if (k < tlen - 1) FUN_00429520(t, 0, (unsigned)(k + 1));
            }
            WStr_StripQuotes(t);
            ++count;
            byteOffset += 16;
            if (i + 1 < totalLen) {
                int j = i + 1;
                while (j < totalLen && (buf[j] == 0x20 || buf[j] == 9)) ++j;
                i = j - 1;
            }
            start = i + 1;
            quoteCount = 0;
            goto advance;
        }
    }

finalEmit:
    {
        int tokenLen = i - start;
        if (tokenLen != 0 && (unsigned)count < (unsigned)f) {
            if ((unsigned)(out->mpEnd - out->mpBegin) / 16 <= (unsigned)count)
                FUN_00553e60(out, 0, (unsigned)(count + 1));
            WStr_s0093_d740* t = &out->mpBegin[count];
            FUN_00423650(t, 0, buf + start, buf + i);
            WStr_StripQuotes(t);
            ++count;
        }
    }

    (void)byteOffset;
    if (allocated) FUN_00f47380(buf);
    return count;
}

// @ 0x0093dbc0
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetVariant8(const unsigned short* p)
{
    Variant_s0093_d740* v = this;
    if (v->mFlags & 4) {
        ((void(__cdecl*)(int, Variant_s0093_d740*, int, int, int, int))g_fn154eb48)(1, v, 0, 0, 0, 0);
        if ((v->mFlags & 2) == 0) { v->mTypeId = 0; v->mFlags = 0; }
    }
    unsigned short f = v->mFlags & 2;
    if (f != 0 && v->mTypeId != 8) { v->Construct(8, 0, p, 2, 1); return v; }
    v->value0w = *p;
    v->mFlags = f; v->mTypeId = 8;
    return v;
}
}  // namespace EA

// @ 0x0093dcc0
void HashTable::Rehash(unsigned n)
{
    unsigned int size = n * 4;
    char* buckets = (char*)FUN_00f473a0(size + 4, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    buckets[size] = (char)0xff;
    *(unsigned int*)(buckets + size) = 0xffffffff;
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        int* node = (int*)mpBuckets[i];
        while (node) {
            unsigned b = ((unsigned)*(unsigned short*)((char*)node + 4) + (unsigned)node[0]) % n;
            mpBuckets[i] = node[3];
            node[3] = *(int*)(buckets + b * 4);
            *(int**)(buckets + b * 4) = node;
            node = (int*)mpBuckets[i];
        }
    }
    if (mnBucketCount > 1) FUN_00f47380(mpBuckets);
    mpBuckets = (unsigned int*)buckets;
    mnBucketCount = n;
}

// @ 0x0093dd80
bool EA::Variant_s0093_d740::Construct(unsigned short type, unsigned short flags, const void* src, unsigned int width, unsigned int isAtomic)
{
    unsigned int f = flags;
    bool convert = false;
    if ((mFlags & 2) != 0) {
        f |= 2;
        if (mTypeId != type) convert = true;
    }
    if (!convert) {
        if ((f & 8) != 0) {
            convert = true;
        } else if ((f & 0x20) != 0) {
            mTypeId = type;
            value1 = width;
            mFlags = (unsigned short)f;
            value2 = isAtomic;
            value0 = (unsigned int)(size_t)src;
            return true;
        } else {
            if ((f & 0x10) == 0) {
                unsigned int n = width * isAtomic;
                if (n <= 0x10) {
                    FUN_011e0744(this, src, n);
                    mTypeId = type;
                    mFlags = (unsigned short)f;
                    return true;
                }
                f |= 0x10;
            }
            f |= 8;
            convert = true;
        }
    }

    // Slow path: hand the source descriptor plus the requested type/flags to the
    // global Variant type-proc as a construct (op 2) request.
    Variant_s0093_d740 typeArg;
    typeArg.SetVariant8(&type);
    Variant_s0093_d740 flagsArg;
    flagsArg.SetVariant8((const unsigned short*)&f);
    Variant_s0093_d740 dataArg;
    dataArg.Construct(0x10, 0x20, src, width, isAtomic);
    Variant_s0093_d740* args[3];
    args[0] = &dataArg;
    args[1] = &typeArg;
    args[2] = &flagsArg;
    return ((bool(__cdecl*)(int, Variant_s0093_d740*, Variant_s0093_d740**, int, Variant_s0093_d740**, int))g_fn154eb48)(2, this, args, 3, 0, 0);
}

// @ 0x0093df20
static void WStr_EraseRange(WStr_s0093_d740* t, unsigned pos, unsigned n)
{
    wchar_t* dest = t->mpBegin + pos;
    unsigned size = (unsigned)(t->mpEnd - t->mpBegin);
    ((MoveFn)0x13cc480)(dest, dest + n, (size - pos - n) * 2 + 2);
    t->mpEnd -= n;
}

// @ 0x0093dfa0
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetUInt16(const unsigned short* p)
{
    VAR_PRELUDE(3, 2)
    unsigned short v = *p;
    mFlags = f;
    *(unsigned short*)&value0 = v;
    mTypeId = 3;
    return this;
}
}  // namespace EA

// @ 0x0093e020
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetUInt8(const unsigned char* p)
{
    VAR_PRELUDE(5, 1)
    unsigned char v = *p;
    mFlags = f;
    *(unsigned char*)&value0 = v;
    mTypeId = 5;
    return this;
}
}  // namespace EA

// @ 0x0093e0a0
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetInt8(const unsigned char* p)
{
    VAR_PRELUDE(6, 1)
    unsigned char v = *p;
    mFlags = f;
    *(unsigned char*)&value0 = v;
    mTypeId = 6;
    return this;
}
}  // namespace EA

// @ 0x0093e120
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetUInt16b(const unsigned short* p)
{
    VAR_PRELUDE(7, 2)
    unsigned short v = *p;
    mFlags = f;
    *(unsigned short*)&value0 = v;
    mTypeId = 7;
    return this;
}
}  // namespace EA

// @ 0x0093e1a0
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetPtr(const unsigned short* p)
{
    if (mFlags & 4) {
        ((void(__cdecl*)(int, Variant_s0093_d740*, int, int, int, int))g_fn154eb48)(1, this, 0, 0, 0, 0);
        if ((mFlags & 2) == 0) { mTypeId = 0; mFlags = 0; }
    }
    unsigned short f = mFlags & 2;
    if (f != 0 && mTypeId != 0xb) { Construct(0xb, 0, p, 8, 1); return this; }
    const unsigned int* q = (const unsigned int*)p;
    unsigned int a = q[0];
    unsigned int b = q[1];
    value0 = a;
    mFlags = f;
    value1 = b;
    mTypeId = 0xb;
    return this;
}
}  // namespace EA

// @ 0x0093e220
namespace EA {
Variant_s0093_d740* Variant_s0093_d740::SetDouble(const double* p)
{
    VAR_PRELUDE(0xe, 8)
    double v = *p;
    mFlags = f;
    *(double*)&value0 = v;
    mTypeId = 0xe;
    return this;
}
}  // namespace EA

// @ 0x0093e3f0
void* HashTable::Find(void** out, const void* key)
{
    const int* k = (const int*)key;
    unsigned u = ((unsigned)*(const unsigned short*)((const char*)key + 4) + (unsigned)k[0]) % mnBucketCount;
    int* node = (int*)mpBuckets[u];
    void** slot = (void**)&mpBuckets[u];
    while (node) {
        if (*k == node[0] && *(const unsigned short*)((const char*)key + 4) == *(unsigned short*)((char*)node + 4))
            goto found;
        node = (int*)node[3];
    }
    slot = (void**)&mpBuckets[mnBucketCount];
    node = (int*)*slot;
found:
    out[0] = node;
    out[1] = slot;
    return out;
}

// @ 0x0093e470
void HashTable::Insert(void** out, int* key)
{
    unsigned u = ((unsigned)*(unsigned short*)((char*)key + 4) + (unsigned)key[0]) % mnBucketCount;
    int* node = (int*)mpBuckets[u];
    while (node) {
        if (key[0] == node[0] && *(unsigned short*)((char*)key + 4) == *(unsigned short*)((char*)node + 4)) {
            *out = node; *(unsigned char*)(out + 2) = 0; out[1] = (void*)&mpBuckets[u];
            return;
        }
        node = (int*)node[3];
    }
    int* fresh = (int*)FUN_00f473a0(0x10, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    if (fresh) { fresh[0] = key[0]; fresh[1] = key[1]; fresh[2] = key[2]; }
    fresh[3] = 0;
    fresh[3] = *(int*)&mpBuckets[u];
    mpBuckets[u] = (unsigned int)fresh;
    ++mnElementCount;
    *out = fresh; *(unsigned char*)(out + 2) = 1; out[1] = (void*)&mpBuckets[u];
}

// @ 0x0093e5f0
namespace EA {
bool VariantDefaultTypeProc(int op, Variant_s0093_e5f0* pThis, Variant_s0093_e5f0** ppArgs, int nArgs, Variant_s0093_e5f0** ppResults, int nResults)
{
    (void)nArgs; (void)nResults;

    switch (op) {
        case kOpDestruct: {
            const unsigned short flags = pThis->mFlags;

            if (flags & Variant_s0093_e5f0::kfRawPointer) {
                if (pThis->mTypeId == Variant_s0093_e5f0::kTypeIUnknown32 && pThis->mPointer.mpData) {
                    if (flags & Variant_s0093_e5f0::kfPointerPtr) {
                        IUnknown32* pUnknown = *(IUnknown32**)pThis->mPointer.mpData;
                        if (pUnknown) {
                            pUnknown->Release();
                            pThis->mPointer.mpData = 0;
                        }
                    } else {
                        ((IUnknown32*)pThis->mPointer.mpData)->Release();
                        pThis->mPointer.mpData = 0;
                    }
                }
            } else if (flags & Variant_s0093_e5f0::kfCArray) {
                switch (pThis->mTypeId) {
                    case Variant_s0093_e5f0::kTypeIUnknown32: {
                        IUnknown32** pp = (IUnknown32**)pThis->mPointer.mpData;
                        for (IUnknown32** ppEnd = pp + pThis->mPointer.mElementCount; pp < ppEnd; ++pp) {
                            if (*pp)
                                (*pp)->Release();
                        }
                        break;
                    }
                    case Variant_s0093_e5f0::kTypeString8: {
                        eastl::string* p = (eastl::string*)pThis->mPointer.mpData;
                        for (eastl::string* pEnd = p + pThis->mPointer.mElementCount; p < pEnd; ++p)
                            eastl::DestroyString(p);
                        break;
                    }
                    case Variant_s0093_e5f0::kTypeString16: {
                        eastl::wstring* p = (eastl::wstring*)pThis->mPointer.mpData;
                        for (eastl::wstring* pEnd = p + pThis->mPointer.mElementCount; p < pEnd; ++p)
                            eastl::DestroyString(p);
                        break;
                    }
                }
                delete[] (char*)pThis->mPointer.mpData;
                pThis->mPointer.mpData = 0;
                pThis->mPointer.mElementCount = 0;
                pThis->mFlags &= ~Variant_s0093_e5f0::kfCArray;
                pThis->mFlags |= Variant_s0093_e5f0::kfRawPointer;
            } else {
                switch (pThis->mTypeId) {
                    case Variant_s0093_e5f0::kTypeString8:
                        eastl::DestroyString((eastl::string*)pThis);
                        break;
                    case Variant_s0093_e5f0::kTypeString16:
                        eastl::DestroyString((eastl::wstring*)pThis);
                        break;
                }
            }

            if (!(pThis->mFlags & Variant_s0093_e5f0::kfInvariant)) {
                pThis->mTypeId = 0;
                pThis->mFlags = 0;
            } else {
                pThis->mFlags &= ~Variant_s0093_e5f0::kfDestruct;
                if (!(pThis->mFlags & Variant_s0093_e5f0::kfTypeConstruct))
                    pThis->mFlags &= ~Variant_s0093_e5f0::kfConstruct;
            }
            return true;
        }

        case kOpConstruct: {
            const Variant_s0093_e5f0::Pointer* pSource = &ppArgs[0]->mPointer;
            const unsigned short typeId = ppArgs[1]->mUint16;
            const unsigned short flags = ppArgs[2]->mUint16;

            if ((pThis->mFlags & Variant_s0093_e5f0::kfInvariant) && typeId != pThis->mTypeId) {
                // An invariant Variant keeps its own type: (re)construct it empty if
                // needed, then convert the source value into it.
                if ((pThis->mFlags & Variant_s0093_e5f0::kfConstruct) && !(pThis->mFlags & Variant_s0093_e5f0::kfDestruct)) {
                    VariantT<unsigned short> typeArg(pThis->mTypeId);
                    VariantT<unsigned short> flagsArg(pThis->mFlags);
                    Variant_s0093_e5f0 dataArg;
                    dataArg.Assign(Variant_s0093_e5f0::kTypeVoid, Variant_s0093_e5f0::kfRawPointer, 0, 0, 0);
                    Variant_s0093_e5f0* args[3];
                    args[0] = &dataArg;
                    args[1] = &typeArg;
                    args[2] = &flagsArg;
                    gpVariantTypeProc(kOpConstruct, pThis, args, 3, 0, 0);
                }
                if (gpVariantTypeProc(kOpConvert, ppArgs[0], ppArgs + 1, 2, &pThis, 1))
                    pThis->mFlags |= Variant_s0093_e5f0::kfInvariant;
                return true;
            }

            pThis->mFlags = (unsigned short)(((pThis->mFlags ^ flags) & Variant_s0093_e5f0::kfInvariant) ^ flags);
            pThis->mTypeId = typeId;

            const unsigned size = pSource->mElementSize * pSource->mElementCount;
            if (!(flags & Variant_s0093_e5f0::kfCArray) && size > 16)
                pThis->mFlags |= Variant_s0093_e5f0::kfCArray;

            if (pThis->mFlags & Variant_s0093_e5f0::kfRawPointer) {
                pThis->mPointer.mElementSize = pSource->mElementSize;
                pThis->mPointer.mElementCount = pSource->mElementCount;
                pThis->mPointer.mpData = pSource->mpData;

                if (pSource->mpData && pThis->mTypeId == Variant_s0093_e5f0::kTypeIUnknown32) {
                    IUnknown32** ppUnknown = (IUnknown32**)&pThis->mPointer.mpData;
                    if (pThis->mFlags & Variant_s0093_e5f0::kfPointerPtr) {
                        ppUnknown = (IUnknown32**)pThis->mPointer.mpData;
                        if (!ppUnknown)
                            return true;
                    }
                    if (*ppUnknown) {
                        (*ppUnknown)->AddRef();
                        pThis->mFlags |= Variant_s0093_e5f0::kfDestruct;
                    }
                }
            } else if (pThis->mFlags & Variant_s0093_e5f0::kfCArray) {
                pThis->mPointer.mElementSize = pSource->mElementSize;
                pThis->mPointer.mElementCount = pSource->mElementCount;
                pThis->mPointer.mpData = new ("App/EAVariant/kfCArray", 0, 0, 0, 0) char[size];
                pThis->mFlags |= Variant_s0093_e5f0::kfDestruct;

                if (pSource->mpData) {
                    switch (pThis->mTypeId) {
                        case Variant_s0093_e5f0::kTypeIUnknown32: {
                            memcpy(pThis->mPointer.mpData, pSource->mpData, size);
                            IUnknown32** pp = (IUnknown32**)pThis->mPointer.mpData;
                            for (IUnknown32** ppEnd = pp + pSource->mElementCount; pp < ppEnd; ++pp) {
                                if (*pp)
                                    (*pp)->AddRef();
                            }
                            break;
                        }
                        case Variant_s0093_e5f0::kTypeString8: {
                            const eastl::string* pFrom = (const eastl::string*)pSource->mpData;
                            eastl::string* p = (eastl::string*)pThis->mPointer.mpData;
                            for (eastl::string* pEnd = p + pSource->mElementCount; p < pEnd; ++p, ++pFrom)
                                new (p) eastl::string(pFrom->data(), pFrom->size());
                            break;
                        }
                        case Variant_s0093_e5f0::kTypeString16: {
                            const eastl::wstring* pFrom = (const eastl::wstring*)pSource->mpData;
                            eastl::wstring* p = (eastl::wstring*)pThis->mPointer.mpData;
                            for (eastl::wstring* pEnd = p + pSource->mElementCount; p < pEnd; ++p, ++pFrom)
                                new (p) eastl::wstring(pFrom->data(), pFrom->size());
                            break;
                        }
                        default:
                            memcpy(pThis->mPointer.mpData, pSource->mpData, size);
                            break;
                    }
                }
            } else {
                switch (pThis->mTypeId) {
                    case Variant_s0093_e5f0::kTypeString8: {
                        const eastl::string* pFrom = (const eastl::string*)pSource->mpData;
                        if (pFrom)
                            new (pThis) eastl::string(pFrom->data(), pFrom->size());
                        else
                            new (pThis) eastl::string();
                        pThis->mFlags |= Variant_s0093_e5f0::kfDestruct;
                        break;
                    }
                    case Variant_s0093_e5f0::kTypeString16: {
                        const eastl::wstring* pFrom = (const eastl::wstring*)pSource->mpData;
                        if (pFrom)
                            new (pThis) eastl::wstring(pFrom->data(), pFrom->size());
                        else
                            new (pThis) eastl::wstring();
                        pThis->mFlags |= Variant_s0093_e5f0::kfDestruct;
                        break;
                    }
                    default:
                        memcpy(pThis, pSource->mpData, size);
                        break;
                }
            }
            return true;
        }

        case kOpConvert: {
            Variant_s0093_e5f0* pDest = ppResults[0];
            const unsigned short srcType = ppArgs[0]->mUint16;

            switch (pDest->mTypeId) {
                case Variant_s0093_e5f0::kTypeBool:     return ConvertToBool(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeChar8:    return ConvertToScalar<char>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeChar16:   return ConvertToScalar<wchar_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeInt8:     return ConvertToScalar<int8_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeUint8:    return ConvertToScalar<uint8_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeInt16:    return ConvertToScalar<int16_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeUint16:   return ConvertToScalar<uint16_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeInt32:    return ConvertToScalar<int32_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeUint32:   return ConvertToScalar<uint32_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeInt64:    return ConvertToScalar<int64_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeUint64:   return ConvertToScalar<uint64_t>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeFloat:    return ConvertToScalar<float>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeDouble:   return ConvertToScalar<double>(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeString8:  return ConvertToString8(pDest, pThis, srcType);
                case Variant_s0093_e5f0::kTypeString16: return ConvertToString16(pDest, pThis, srcType);
            }
            return true;
        }
    }
    return false;
}
}  // namespace EA
