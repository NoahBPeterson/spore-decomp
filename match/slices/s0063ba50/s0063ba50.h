// Shared declarations for the PlayMode movie / YouTube module (retail layout).
#pragma once
#include "types.h"
#include <string.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
void* operator new(size_t size, int align, const char* name, void* alloc);   // 0x009512D0
inline void* operator new(size_t, void* p) { return p; }

namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
struct allocator {
    void deallocate(void* p) { operator delete[](p); }
};
template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;
}

namespace EA { eastl::string16 ConvertToString16(const char* p, int length = -1); }   // 0x0093C5A0

// ref-counted COM-like base
struct IRefCounted { virtual int AddRef(); virtual int Release(); };
template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

struct IWindow {   // UTFWin window (slots used by this module)
    virtual int AddRef();
    virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual uint32_t GetControlID();   // +0x1C
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void SetFlag(int flag, int on);                    // +0x7C
    virtual void SetCaption(const wchar_t* text);              // +0x80
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42();
    virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
    virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57();
    virtual void s58(); virtual void s59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recurse);   // +0xF0
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
    virtual void RemoveWinProc(void* proc);                       // +0x108
};

struct cSPUILayout {   // 0x18 bytes (retail)
    uint32_t pad[6];
    IWindow* FindWindowByID(uint32_t id, bool recurse);   // 0x008105B0
    void Shutdown(bool b);                                // 0x00811AD0
    cSPUILayout();                                        // 0x00810000
};

struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
};
IMessageServer* GetMessageServer();   // 0x0067DCC0

struct cSPVector4 { float x, y, z, w; cSPVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

float GetElapsedSeconds();                          // 0x00805080
void  BeginModal(IWindow* w, int a, int b);         // 0x008099A0 (cdecl)
void  EndModal(IWindow* w, int a, int b);           // 0x00809C50 (cdecl)

// UTFWin custom window proc base (+0 IWinProc, +4 ISerializable, +8 refcount)
struct IWinProc {
    virtual int AddRef(); virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual void s07(); virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
};
struct ISerializable { virtual int s0(); virtual int s1(); };
struct CustomWinProc : IWinProc, ISerializable {
    int mRefCount;
    CustomWinProc() : mRefCount(0) {}
};
