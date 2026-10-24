// src/game/UTFSpore_Win32/EAClipboard.cpp -- migrated from slice(s) s0092abb0, s00929a70 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAClipboard.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"
#include "EA/Thread/Thread.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned g_timeClip;                                // 0x143e3a0
#include <intrin.h>
#include <new>

// ---- items of slice s00929a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void*, const void*, size_t);
extern "C" void* memset(void*, int, size_t);
void* operator new(size_t, const char*, int, int, int, int);
extern unsigned g_timeClip;                                // 0x143e3a0
namespace EA {
namespace Thread {
struct MutexParameters {
    unsigned pad[5];
    MutexParameters(bool intraProcess, const char* name);  // 0x921e00
};
}
}
namespace EA { namespace CallbackSystem { bool Init(); }}  // 0x0092a020 (defined below; used by a stub's inline body)
namespace EA {
namespace Thread {
struct Mutex_s0092_9a70 {
    unsigned __int64 data[6];
    Mutex_s0092_9a70() {}
    Mutex_s0092_9a70(const MutexParameters* p, bool bDefault);        // 0x9222a0
    ~Mutex_s0092_9a70();                                              // 0x922130
    bool Init(const MutexParameters* p);                   // 0x922150
    int  Lock(unsigned* pTimeout);                         // 0x9221b0
    int  Unlock();                                         // 0x922270
};
}
}
namespace EA {
namespace Clipboard {
class IData { public:
    virtual void slot0() = 0;
    virtual void AddRef() = 0;
    virtual void Release() = 0;
};
}
}
namespace EA {
namespace Clipboard {
class DataText16 : public IData { public:
    unsigned mnType;       // +4
    unsigned mnRefCount;   // +8
    unsigned mnDataSize;   // +0xc
    unsigned char mData[2];// +0x10
    DataText16(const wchar_t* s, int len);                      // 0x92aae0
    virtual void slot0();
    virtual void AddRef();
    virtual void Release();
};
}
}
namespace EA {
namespace Clipboard {
struct SPMemPool {
    void* LockedAlloc(unsigned size, int a, int b, int c, int d, int e);   // 0x9289f0
};
}
}
namespace EA {
namespace Clipboard {
extern SPMemPool* g_pMemPool;     // 0x16c8b44
}
}
namespace EA {
namespace Clipboard {
struct DataInfo {
    unsigned mnType;
    IData* mpData;
};
}
}
namespace EA {
namespace Clipboard {
class Clipboard { public:
    bool mbInitialized;       // +0
    unsigned mnId;            // +4
    void* mpOSData;           // +8
    DataInfo mDataInfoArray[33];  // +0xc
    EA::Thread::Mutex_s0092_9a70 mMutex; // +0x118
    int mnMaxTypes;           // +0x148
    bool mbOSSync;            // +0x14c

    Clipboard();                                                // 0x92a880
    bool GetClipboardData(unsigned type, IData** out);          // 0x92a8d0
    int  Clear(unsigned type);                                  // 0x92a940
};
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) int   __stdcall OpenClipboard(void*);
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) int   __stdcall EmptyClipboard();
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) int   __stdcall CloseClipboard();
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) void* __stdcall SetClipboardData(unsigned fmt, void* h);
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) void* __stdcall GlobalAlloc(unsigned flags, size_t bytes);
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) void* __stdcall GlobalLock(void* h);
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) int   __stdcall GlobalUnlock(void* h);
}
}
namespace EA {
namespace Clipboard {
extern "C" __declspec(dllimport) void* __stdcall GlobalFree(void* h);
}
}
namespace EA {
namespace Clipboard {
struct Win32Clipboard {
    bool mbEnabled;                 // +0
    int mnGettingText;              // +4
    int mnSettingText;              // +8
    bool WriteText(const wchar_t* text, int len);               // 0x92aa20
};
}
}
// ---- items of slice s00929a70 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* memcpy(void*, const void*, size_t);
extern "C" void* memset(void*, int, size_t);

// ---- items of slice s0092abb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned short __stdcall RegisterClassA(const void*);
extern void* g_ClipboardAutoPtr;   // 0x1668f00
typedef void* HWND;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* LPVOID;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long LONG;
typedef const char* LPCSTR;
extern "C" __declspec(dllimport) BOOL __stdcall ChangeClipboardChain(HWND, HWND);
extern "C" __declspec(dllimport) BOOL __stdcall DestroyWindow(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall OpenClipboard_s0092_abb0(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall CloseClipboard_s0092_abb0();
extern "C" __declspec(dllimport) BOOL __stdcall IsClipboardFormatAvailable(UINT);
extern "C" __declspec(dllimport) HANDLE __stdcall GetClipboardData(UINT);
extern "C" __declspec(dllimport) LPVOID __stdcall GlobalLock_s0092_abb0(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall GlobalUnlock_s0092_abb0(HANDLE);
extern "C" __declspec(dllimport) size_t __stdcall GlobalSize(HANDLE);
extern "C" __declspec(dllimport) HWND __stdcall SetClipboardViewer(HWND);
extern "C" __declspec(dllimport) LONG __stdcall SetWindowLongA(HWND, int, LONG);
extern "C" __declspec(dllimport) HWND __stdcall CreateWindowExA(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, void*, HMODULE, LPVOID);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(LPCSTR);
extern "C" __declspec(dllimport) DWORD __stdcall GetVersion();
void* operator_new(uint32_t n, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  operator_delete__(void* p);
void* FUN_006abeb0(unsigned n);              // 0x6abeb0
void  WString_Assign(void* s, const void* first, const void* last); // 0x423650
void  WStr_Append(void* s, const wchar_t* first, const wchar_t* last); // 0x429580
void  WStr_PushBack(void* s, wchar_t c);     // 0x4f6510
void* WStr_Find(const void* s, const wchar_t* sub, int start); // 0x608340
void  Mutex_Lock(void* m, void* name);       // 0x9221b0
void  Mutex_Unlock(void* m);                 // 0x922270
void  Win32Clipboard_WriteText(void* w, const wchar_t* t, int n); // 0x92aa20
void* FUN_009289f0(int size, int a, int b, int c, int d, int e); // 0x9289f0
void* FUN_0092aae0(void* text, int n);       // 0x92aae0
// EA::Clipboard::DataText16(const wchar_t*, int) built in place: thiscall on the raw storage
struct DataTextCtorStub {
    void* ctor(const wchar_t* text, int n);  // 0x92aae0
};
struct WString {
    wchar_t* mpBegin;    // +0
    wchar_t* mpEnd;      // +4
    wchar_t* mpCapacity; // +8
    void* mAlloc;        // +0xc
    WString() { mpBegin = mpEnd = (wchar_t*)0x1667bac; mpCapacity = (wchar_t*)0x1667bae; }
    void assign(const wchar_t* first, const wchar_t* last) { WString_Assign(this, first, last); }
    void append(const wchar_t* first, const wchar_t* last) { WStr_Append(this, first, last); }
    void push_back(wchar_t c) { WStr_PushBack(this, c); }
    long find(const wchar_t* s, int start) { return (long)WStr_Find(this, s, start); }
};
struct Mutex { char pad[0x14]; void Lock(void* name) { Mutex_Lock(this, name); } void Unlock() { Mutex_Unlock(this); } };
struct DataInfo_s0092_abb0 { unsigned mnType; void* mpData; };
struct IData_s0092_abb0 {
    virtual void i0();
    virtual void i1();                 // +0x04
    virtual void i2();
    virtual unsigned i3();             // +0x0c
    virtual const wchar_t* i4(int n);  // +0x10
    virtual unsigned i5();             // +0x14
};
struct Clipboard_s0092_abb0 {
    void** vftable;                 // +0
    int mnId;                       // +4
    void* mpOSData;                 // +8
    DataInfo_s0092_abb0 mDataInfoArray[0x20];  // +0xc
    char pad10c[0xc];               // +0x10c .. 0x117
    Mutex mMutex;                   // +0x118
    char pad12c[0x20];              // +0x12c .. 0x14b
    bool mbFlag;                    // +0x14c
    char pad14d[3];
    void Clear(unsigned type);                    // 0x92a940 (other slice)
    bool SetClipboardData(IData_s0092_abb0* pData, bool b);  // @ 0092abb0 0x0092abb0
    bool DestroyPlatform();                       // @ 0092ad10
    bool Clipboard_EnablePlatform();              // @ 0092b0b0
    void FUN_0092b0f0(int v);                     // @ 0092b0f0
    bool FUN_0092b140();                          // @ 0092b140
};
struct Win32Clipboard_s0092_abb0 {
    bool mbEnabled;      // +0
    char pad01[3];
    int mnGettingText;   // +4
    int mnSettingText;   // +8
    Clipboard_s0092_abb0* mpPrimary; // +0xc
    HWND mHWND;          // +0x10
    HWND mNextHWND;      // +0x14
    DWORD mnLocale;      // +0x18
    Win32Clipboard_s0092_abb0(Clipboard_s0092_abb0* owner);   // @ 0092afb0
    bool WindowProcedure(WString* text); // @ 0092adb0 0x0092adb0
};
// ---- items of slice s0092abb0 end

// @ 0x0092a880
namespace EA { namespace Clipboard {
Clipboard::Clipboard()
: mbInitialized(false), mnId(0), mpOSData(0), mMutex(0, true), mnMaxTypes(1000), mbOSSync(true)
{
    memset(mDataInfoArray, 0, 0x108);
    mDataInfoArray[32].mnType = 0;
    mDataInfoArray[32].mpData = 0;
}
}}  // namespace EA::Clipboard

// @ 0x0092a8d0
namespace EA { namespace Clipboard {
bool Clipboard::GetClipboardData(unsigned type, IData** out)
{
    mMutex.Lock(&g_timeClip);
    for (int i = 0; mDataInfoArray[i].mnType != 0; ++i) {
        if (mDataInfoArray[i].mnType == type) {
            if (out) {
                IData* d = mDataInfoArray[i].mpData;
                *out = d;
                d->AddRef();
            }
            mMutex.Unlock();
            return true;
        }
    }
    if (out) {
        *out = 0;
    }
    mMutex.Unlock();
    return false;
}
}}  // namespace EA::Clipboard

// @ 0x0092a940
namespace EA { namespace Clipboard {
int Clipboard::Clear(unsigned type)
{
    mMutex.Lock(&g_timeClip);
    int n = 0;
    if (type == (unsigned)-1) {
        if (mDataInfoArray[0].mnType != 0) {
            DataInfo* p = mDataInfoArray;
            do {
                IData* d = p->mpData;
                p->mnType = 0;
                d->Release();
                ++n;
                p->mpData = 0;
                p = &mDataInfoArray[n];
            } while (p->mnType != 0);
        }
        mMutex.Unlock();
        return n;
    }
    for (int i = 0; mDataInfoArray[i].mnType != 0; ++i) {
        if (mDataInfoArray[i].mnType == type) {
            mDataInfoArray[i].mpData->Release();
            ++i;
            n = 1;
            if (mDataInfoArray[i - 1].mnType != 0) {
                do {
                    mDataInfoArray[i - 1].mnType = mDataInfoArray[i].mnType;
                    mDataInfoArray[i - 1].mpData = mDataInfoArray[i].mpData;
                    ++i;
                } while (mDataInfoArray[i - 1].mnType != 0);
            }
            mMutex.Unlock();
            return n;
        }
    }
    mMutex.Unlock();
    return n;
}
}}  // namespace EA::Clipboard

// @ 0x0092aa20
namespace EA { namespace Clipboard {
bool Win32Clipboard::WriteText(const wchar_t* text, int len)
{
    bool ok = false;
    if (mbEnabled && mnGettingText == 0) {
        ++mnSettingText;
        if (OpenClipboard(0)) {
            EmptyClipboard();
            int bytes = len * 2;
            void* h = GlobalAlloc(2, bytes + 2);
            if (h) {
                char* p = (char*)GlobalLock(h);
                if (p) {
                    memcpy(p, text, bytes);
                    *(unsigned short*)(p + bytes) = 0;
                    GlobalUnlock(h);
                    if (SetClipboardData(13, h)) {
                        ok = true;
                        CloseClipboard();
                        --mnSettingText;
                        return ok;
                    }
                    GlobalFree(h);
                }
            }
            CloseClipboard();
        }
        --mnSettingText;
    }
    return ok;
}
}}  // namespace EA::Clipboard

// @ 0x0092aae0
namespace EA { namespace Clipboard {
DataText16::DataText16(const wchar_t* s, int len)
{
    mnRefCount = 0;
    mnDataSize = 0;
    mnType = 3;
    if (s) {
        if (len == -1) {
            const wchar_t* p = s;
            len = -1;
            do {
                ++len;
            } while (*p++ != 0);
        }
        memcpy(mData, s, len * 2);
    } else {
        len = 0;
    }
    mData[len * 2] = 0;
    mnDataSize = len * 2 + 2;
}
}}  // namespace EA::Clipboard

// @ 0x0092ab60
namespace EA { namespace Clipboard {
DataText16* CreateTextData(const wchar_t* s, int len)
{
    void* m = g_pMemPool->LockedAlloc(len * 2 + 0x1a, 0, 0, 0, 0, 0);
    if (m) {
        DataText16* d = new (m) DataText16(s, len);
        if (d) {
            ((IData*)d)->AddRef();
        }
        return d;
    }
    return 0;
}
}}  // namespace EA::Clipboard

// @ 0x0092abb0
bool Clipboard_s0092_abb0::SetClipboardData(IData_s0092_abb0* pData, bool b)
{
    mMutex.Lock((void*)0x143e3a0);
    if (b)
        Clear(0xffffffff);
    if (pData != 0) {
        pData->i1();
        unsigned type = pData->i3();
        Clear(type);
        unsigned i = 0;
        for (; i < 0x20; ++i) {
            if (mDataInfoArray[i].mnType == 0) {
                mDataInfoArray[i].mnType = type;
                mDataInfoArray[i].mpData = pData;
                break;
            }
        }
        if (i == 0x20) {
            Clear(mDataInfoArray[0].mnType);
            mDataInfoArray[0x1f].mnType = type;
            mDataInfoArray[0x1f].mpData = pData;
        }
        if (mnId == 1 && type == 3 && mpOSData != 0) {
            mMutex.Unlock();
            unsigned n = pData->i5();
            int len = (int)(n >> 1) - 1;
            const wchar_t* t = pData->i4(len);
            Win32Clipboard_WriteText(mpOSData, t, len);
            mMutex.Lock((void*)0x143e3a0);
        }
    }
    mMutex.Unlock();
    return true;
}

// @ 0x0092ac90
void* FUN_0092ac90(void* v)
{
    char* g = (char*)g_ClipboardAutoPtr;
    void* old = *(void**)(g + 0x10);
    *(void**)(g + 0x10) = v;
    return old;
}

// @ 0x0092acb0
bool SetClipboardText(Clipboard_s0092_abb0* clipboard, const wchar_t* s, int len)
{
    bool result = false;
    void* mem = EA::Clipboard::g_pMemPool->LockedAlloc(len * 2 + 0x1a, 0, 0, 0, 0, 0);
    if (mem != 0) {
        IData_s0092_abb0* obj = (IData_s0092_abb0*)((DataTextCtorStub*)mem)->ctor(s, len);
        if (obj != 0) {
            obj->i1();
            result = clipboard->SetClipboardData(obj, true);
            obj->i2();
        }
    }
    return result;
}

// @ 0x0092ad10
bool Clipboard_s0092_abb0::DestroyPlatform()
{
    char* o = (char*)this;
    char* p = *(char**)(o + 8);
    if (p != 0) {
        if (*(void**)(p + 0x10) != 0) {
            ChangeClipboardChain(*(HWND*)(p + 0x10), *(HWND*)(p + 0x14));
            DestroyWindow(*(HWND*)(p + 0x10));
        }
        operator_delete__(p);
        *(void**)(o + 8) = 0;
    }
    return true;
}

// @ 0x0092ad50
void* FUN_0092ad50(bool create)
{
    char* g = (char*)g_ClipboardAutoPtr;
    if (*(void**)(g + 0x10) == 0 && create) {
        void* mem = operator_new(0x150, "Clipboard", 0, 0, 0, 0);
        if (mem != 0) {
            void* obj = 0;
            (void)obj;
        }
    }
    return *(void**)(g + 0x10);
}

// @ 0x0092adb0
bool Win32Clipboard_s0092_abb0::WindowProcedure(WString* text)
{
    bool result = false;
    bool got = false;
    if (text->mpBegin != text->mpEnd) {
        *text->mpBegin = 0;
        text->mpEnd = text->mpBegin;
    }
    if (mbEnabled && mnSettingText == 0) {
        ++mnGettingText;
        if (OpenClipboard_s0092_abb0(0)) {
            if (IsClipboardFormatAvailable(0xd)) {
                HANDLE h = GetClipboardData(0xd);
                if (h != 0) {
                    wchar_t* p = (wchar_t*)GlobalLock_s0092_abb0(h);
                    if (p != 0) {
                        size_t n = GlobalSize(h) >> 1;
                        WString_Assign(text, text->mpBegin, text->mpEnd);
                        wchar_t* end = p + n;
                        while (p < end && *p != 0) {
                            text->push_back(*p);
                            ++p;
                        }
                        GlobalUnlock_s0092_abb0(h);
                        got = true;
                    }
                }
            }
            CloseClipboard_s0092_abb0();
        }
        --mnGettingText;
    }
    return result || got;
}

// @ 0x0092afb0
Win32Clipboard_s0092_abb0::Win32Clipboard_s0092_abb0(Clipboard_s0092_abb0* owner)
{
    mbEnabled = true;
    mnGettingText = 0;
    mnSettingText = 0;
    mpPrimary = owner;
    mHWND = 0;
    mNextHWND = 0;
    mnLocale = 0x409;
    GetVersion();
    if (mbEnabled != false) {
        char wc[0x28];
        *(void**)(wc + 0x0) = 0;
        *(void**)(wc + 0x4) = 0;
        *(void**)(wc + 0x8) = 0;
        *(void**)(wc + 0xc) = 0;
        *(void**)(wc + 0x10) = (void*)0x92ae80;
        *(void**)(wc + 0x14) = 0;
        *(void**)(wc + 0x18) = 0;
        *(void**)(wc + 0x1c) = (void*)4;
        *(void**)(wc + 0x20) = 0;
        *(void**)(wc + 0x24) = 0;
        RegisterClassA(wc);
        mHWND = CreateWindowExA(0, "EAClipboardClass", "EAClipboard", 0,
                                (int)0x80000000, (int)0x80000000, (int)0x80000000, (int)0x80000000,
                                0, 0, GetModuleHandleA(0), 0);
        if (mHWND != 0) {
            SetWindowLongA(mHWND, -0x15, (LONG)this);
            mNextHWND = SetClipboardViewer(mHWND);
        }
    }
}

// @ 0x0092b0b0
bool Clipboard_s0092_abb0::Clipboard_EnablePlatform()
{
    void* self = this;
    char* s = (char*)self;
    if (s[0x14c] != 0 && *(void**)(s + 8) == 0 && *(int*)(s + 4) == 1) {
        void* mem = FUN_006abeb0(0x1c);
        if (mem != 0) {
            *(void**)(s + 8) = new (mem) Win32Clipboard_s0092_abb0((Clipboard_s0092_abb0*)self);
            return true;
        }
        *(void**)(s + 8) = 0;
    }
    return true;
}
