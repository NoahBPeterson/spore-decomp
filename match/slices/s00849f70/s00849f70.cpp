// Slice s00849f70: EA::App::IMEServer / IMEServerWin32 IME plumbing
// (IMECompositionStringDataEx ctors/dtors, eastl wstring/vector helpers) and
// EA::App::Canvas::FlushInput.  Optimized module (/O2).
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- win32 / imm32
typedef void* HWND;
typedef void* HIMC;
typedef void* HKL;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef unsigned long* LPDWORD;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef long LONG;

struct POINT { long x, y; };
struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
};

// user32 is imported through the IAT (dllimport); imm32 through linker thunks.  All stdcall.
extern "C" __declspec(dllimport) BOOL __stdcall PeekMessageA(tagMSG*, HWND, UINT, UINT, UINT);
extern "C" __declspec(dllimport) BOOL __stdcall PostMessageA(HWND, UINT, WPARAM, LPARAM);
extern "C" __declspec(dllimport) HKL __stdcall GetKeyboardLayout(DWORD);
extern "C" HIMC __stdcall ImmGetContext(HWND);
extern "C" BOOL __stdcall ImmGetOpenStatus(HIMC);
extern "C" BOOL __stdcall ImmReleaseContext(HWND, HIMC);
extern "C" BOOL __stdcall ImmSetOpenStatus(HIMC, BOOL);
extern "C" BOOL __stdcall ImmSimulateHotKey(HWND, DWORD);
extern "C" BOOL __stdcall ImmGetConversionStatus(HIMC, LPDWORD, LPDWORD);
extern "C" BOOL __stdcall ImmSetConversionStatus(HIMC, DWORD, DWORD);
extern "C" BOOL __stdcall ImmNotifyIME(HIMC, DWORD, DWORD, DWORD);
extern "C" BOOL __stdcall ImmSetCompositionStringW(HIMC, DWORD, LPCVOID, DWORD, LPCVOID, DWORD);
extern "C" LONG __stdcall ImmGetCompositionStringW(HIMC, DWORD, LPVOID, DWORD);

// ---------------------------------------------------------------- EASTL-ish
void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380
void  DoInsertValue(void* dst, const void* src, unsigned n);   // 0x011e0744 (memcpy-ish)
void  VecFill(unsigned n, const void* value);                  // 0x0068e8a0

void* EA_Messaging_GetServer();                                // 0x00883860
void* FUN_008d3110();                                          // 0x008d3110
void  FUN_00849e30(tagMSG* vec, const tagMSG* msg);            // 0x00849e30 (push_back)

// 16-byte eastl::basic_string<wchar_t> (empty allocator).
struct WString {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8
    uint32_t mAllocPad;    // +c
    WString() { mpBegin = (wchar_t*)0x1667bac; mpEnd = (wchar_t*)0x1667bac; mpCapacity = (wchar_t*)0x1667bae; }
    WString(unsigned n, wchar_t c, const void* alloc = 0);  // @ 0084a780
    WString(const WString& o);        // @ 0084a7e0
    WString(wchar_t c);               // @ 0084aa60
    void AllocateSelf(unsigned n);    // 0x00429760
    WString& assign(const wchar_t* first, const wchar_t* last); // 0x00423650
    void resize(unsigned n);          // 0x00429520
};

inline void FreeWString(WString& s) {
    int n = (int)((char*)s.mpCapacity - (char*)s.mpBegin);
    if ((n & ~1) > 2) {
        if (s.mpBegin)
            EASTL_allocator_deallocate(s.mpBegin);
    }
}

struct ByteVector {      // eastl::vector<unsigned char>
    uint8_t* mpBegin; uint8_t* mpEnd; uint8_t* mpCapacity;
    ByteVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void resize(unsigned n);          // 0x004c0410
    void clear();
};

inline void ByteVector::clear() {
    uint8_t* first = mpBegin;
    uint8_t* last = mpEnd;
    DoInsertValue(first, last, (unsigned)(mpEnd - last));
    mpEnd -= (last - first);
}

struct WStringVector {   // eastl::vector<WString>
    WString* mpBegin; WString* mpEnd; WString* mpCapacity;
    ~WStringVector() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4))
            EASTL_allocator_deallocate(mpBegin);
    }
    void DoDestroyValues(WString* first, WString* last);   // @ 0084aad0
};

struct PtrVector {       // eastl::vector<wchar_t*>
    void* mpBegin; void* mpEnd; void* mpCapacity;
    ~PtrVector() {
        if (mpBegin && *(int*)((char*)mpBegin - 4))
            EASTL_allocator_deallocate(mpBegin);
    }
};

// ---------------------------------------------------------------- IME data
struct IMECompositionStringDataEx {
    wchar_t* mpStringData;          // +0x00
    uint8_t* mpTextAttributeData;   // +0x04
    uint32_t mnDataLength;          // +0x08
    uint32_t mnCaretPosition;       // +0x0c
    wchar_t  mLocale[12];           // +0x10
    WString  mStringData;           // +0x28
    WString  mResultStringData;     // +0x38
    ByteVector mTextAttributeData;  // +0x48
    uint32_t mPad54;                // +0x54
    uint32_t mPad58;                // +0x58
    bool mbCompositionStarted;      // +0x5c
    bool mbResultSuccess;           // +0x5d
    char  mPad5e[2];
    IMECompositionStringDataEx();   // @ 0084a700
    ~IMECompositionStringDataEx();  // @ 0084a6a0
    void Reset();                   // @ 0084ac50
};

// ---------------------------------------------------------------- stubs
struct IMECompositionTarget {
    virtual void q00(); virtual void q01(); virtual void q02(); virtual void q03();
    virtual void q04(); virtual void q05(); virtual void q06(); virtual void q07();
    virtual void q08();
    virtual void q09(void*, unsigned);
    virtual void q10();
    virtual void q11(void*, unsigned, unsigned);
};

struct IMEWindow {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(void* form);
};

struct CanvasStub {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04();
    virtual void c05(); virtual void c06(); virtual void c07(); virtual void c08(); virtual void c09();
    virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14();
    virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24();
    virtual void* c25();
    virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
    virtual void c31(); virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
    virtual void c36();
    virtual void* c37();
};

struct IHandler {
    virtual void h00(); virtual ~IHandler();
};

// ---------------------------------------------------------------- IMEServer
class IMEServer {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(int);              // +0x14
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual bool v09();                 // +0x24
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual bool v13();                 // +0x34
    virtual ~IMEServer();               // declared last so the slots above keep their offsets

    bool mbInitialized;        // +0x04
    bool mbEnabled;            // +0x05
    char mPad06[2];
    void* mpMessageServer;     // +0x08
    IMECompositionStringDataEx mCompData;  // +0x0c (0x60 bytes)
    char mPad6c[0x24];                     // +0x6c .. +0x8f
    WStringVector mStringArray;            // +0x90
    char mPad9c[8];                        // +0x9c .. +0xa3
    PtrVector mDataPointers;               // +0xa4
    char mPadB0[0x0c];                     // +0xb0 .. +0xbb (0xbc = derived IHandler)

    bool EnsureInitialized();                      // @ 0084a590
    bool Shutdown();                               // @ 0084a5d0
    void WriteCompositionString(HWND hwnd, int a, int b, unsigned flags); // @ 0084ad40
};

class IMEServerWin32 : public IMEServer, public IHandler {
public:
    HWND  mhWnd;               // +0xc0
    unsigned mC4;              // +0xc4
    unsigned mC8;              // +0xc8
    CanvasStub* mpCanvas;      // +0xcc
    void* mD0;                 // +0xd0

    void SetEnabled(bool b);                       // @ 0084a230
    bool IsOpen();                                 // @ 0084a360
    bool SetOpenEnabled(bool b);                   // @ 0084a3a0
    bool NotifyClosed(bool b);                     // @ 0084a470
    bool SetConversion(bool b);                    // @ 0084a4d0
    void SetCompositionWindow(unsigned short a, unsigned short b, int c); // @ 0084a540
    void SetFlag(bool b);                          // @ 0084a600
    bool SetCandidateSelection(unsigned idx);      // @ 0084a640
    virtual ~IMEServerWin32();
    bool AssignComposition(const wchar_t* s, int len);   // @ 0084aab0
    bool SetCompositionData(const wchar_t* s, int len);  // @ 0084ab80
};

// ---------------------------------------------------------------- WString bodies
// @ 0x0084a780
WString::WString(unsigned n, wchar_t c, const void*) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    AllocateSelf(n + 1);
    wchar_t* d = mpBegin;
    wchar_t* e = mpBegin + n;
    if (d < e) {
        for (; d < e; ++d)
            *d = c;
    }
    mpEnd = e;
    *e = 0;
}

// @ 0x0084a7e0
WString::WString(const WString& o) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    unsigned n = (unsigned)(o.mpEnd - o.mpBegin);
    AllocateSelf(n + 1);
    wchar_t* d = mpBegin;
    DoInsertValue(d, o.mpBegin, n * 2);
    mpEnd = d + n;
    *mpEnd = 0;
}

// @ 0x0084aa60
WString::WString(wchar_t c) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    AllocateSelf(2);
    wchar_t* d = mpBegin;
    wchar_t* e = mpBegin + 1;
    if (d < e) {
        for (; d < e; ++d)
            *d = c;
    }
    mpEnd = e;
    e[0] = 0;
}

// @ 0x0084a830  construct a run of WStrings at *ppDst from [first,last)
void ConstructWStrings(WString** ppDst, const WString* first, const WString* last, WString* pos) {
    *ppDst = pos;
    for (; first != last; first = (const WString*)((const char*)first + 0x10)) {
        WString* d = *ppDst;
        if (d) {
            d->mpBegin = 0;
            d->mpEnd = 0;
            d->mpCapacity = 0;
            unsigned n = (unsigned)(first->mpEnd - first->mpBegin);
            if (n + 1 < 2) {
                d->mpBegin = (wchar_t*)0x1667bac;
                d->mpEnd = (wchar_t*)0x1667bac;
                d->mpCapacity = (wchar_t*)0x1667bae;
            } else {
                unsigned bytes = (n + 1) * 2;
                uint8_t* p = (uint8_t*)EASTL_allocator_allocate(bytes, "EASTL", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                d->mpBegin = (wchar_t*)p;
                d->mpEnd = (wchar_t*)p;
                d->mpCapacity = (wchar_t*)(p + bytes);
            }
            wchar_t* dst = d->mpBegin;
            DoInsertValue(dst, first->mpBegin, n * 2);
            d->mpEnd = dst + n;
            *d->mpEnd = 0;
        }
        *ppDst = (WString*)((char*)*ppDst + 0x10);
    }
}

// @ 0x0084a8f0  construct count WStrings at dst from the same source
void ConstructWStringsN(WString* dst, unsigned count, const WString* src) {
    if (count == 0)
        return;
    WString* p = dst;
    do {
        p->mpBegin = 0;
        p->mpEnd = 0;
        p->mpCapacity = 0;
        unsigned n = (unsigned)(src->mpEnd - src->mpBegin);
        if (n + 1 < 2) {
            p->mpBegin = (wchar_t*)0x1667bac;
            p->mpEnd = (wchar_t*)0x1667bac;
            p->mpCapacity = (wchar_t*)0x1667bae;
        } else {
            unsigned bytes = (n + 1) * 2;
            uint8_t* q = (uint8_t*)EASTL_allocator_allocate(bytes, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            p->mpBegin = (wchar_t*)q;
            p->mpEnd = (wchar_t*)q;
            p->mpCapacity = (wchar_t*)(q + bytes);
        }
        wchar_t* d = p->mpBegin;
        DoInsertValue(d, src->mpBegin, n * 2);
        p->mpEnd = d + n;
        *p->mpEnd = 0;
        p = (WString*)((char*)p + 0x10);
        --count;
    } while (count != 0);
}

// @ 0x0084a9a0  eastl::uninitialized_copy(first,last,dst) for WString
WString* UninitializedCopyWStrings(const WString* first, const WString* last, WString* dst) {
    if (first == last)
        return dst;
    do {
        if (dst) {
            dst->mpBegin = 0;
            dst->mpEnd = 0;
            dst->mpCapacity = 0;
            unsigned n = (unsigned)(first->mpEnd - first->mpBegin);
            if (n + 1 < 2) {
                dst->mpBegin = (wchar_t*)0x1667bac;
                dst->mpEnd = (wchar_t*)0x1667bac;
                dst->mpCapacity = (wchar_t*)0x1667bae;
            } else {
                unsigned bytes = (n + 1) * 2;
                uint8_t* q = (uint8_t*)EASTL_allocator_allocate(bytes, "EASTL", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                dst->mpBegin = (wchar_t*)q;
                dst->mpEnd = (wchar_t*)q;
                dst->mpCapacity = (wchar_t*)(q + bytes);
            }
            wchar_t* d = dst->mpBegin;
            DoInsertValue(d, first->mpBegin, n * 2);
            dst->mpEnd = d + n;
            *dst->mpEnd = 0;
        }
        first = (const WString*)((const char*)first + 0x10);
        dst = (WString*)((char*)dst + 0x10);
    } while (first != last);
    return dst;
}

// @ 0x0084ab10  eastl::fill / uninitialized_fill over WStrings
void FillWStrings(WString* first, WString* last, const WString* value) {
    for (; first != last; first = (WString*)((char*)first + 0x10)) {
        if (value != first)
            first->assign(value->mpBegin, value->mpEnd);
    }
}

// @ 0x0084ab40  eastl::copy_impl<0,...>::do_copy<WString*,WString*>
WString* CopyWStrings(const WString* first, const WString* last, WString* dst) {
    for (; first != last; first = (const WString*)((const char*)first + 0x10),
                         dst = (WString*)((char*)dst + 0x10)) {
        if (first != dst)
            dst->assign(first->mpBegin, first->mpEnd);
    }
    return dst;
}

// ---------------------------------------------------------------- IME data bodies
// @ 0x0084a6a0
IMECompositionStringDataEx::~IMECompositionStringDataEx() {
    if (mTextAttributeData.mpBegin && *(int*)((char*)mTextAttributeData.mpBegin - 4))
        EASTL_allocator_deallocate(mTextAttributeData.mpBegin);
    FreeWString(mResultStringData);
    FreeWString(mStringData);
}

// @ 0x0084a700
IMECompositionStringDataEx::IMECompositionStringDataEx() {
    mbCompositionStarted = false;
    mbResultSuccess = false;
    const wchar_t* s = L"en-us";
    wchar_t* d = mLocale;
    wchar_t ch;
    do {
        ch = *s++;
        *d++ = ch;
    } while (ch != 0);
    mnCaretPosition = 0;
    if (mStringData.mpBegin == mStringData.mpEnd) {
        mpStringData = 0;
        mpTextAttributeData = 0;
        mnDataLength = 0;
    } else {
        mpStringData = mStringData.mpBegin;
        mpTextAttributeData = mTextAttributeData.mpBegin;
        mnDataLength = (unsigned)(mStringData.mpEnd - mStringData.mpBegin);
    }
}

// @ 0x0084aad0
void WStringVector::DoDestroyValues(WString* first, WString* last) {
    for (; first < last; first = (WString*)((char*)first + 0x10)) {
        FreeWString(*first);
    }
}

// @ 0x0084ac50
void IMECompositionStringDataEx::Reset() {
    if (mStringData.mpBegin != mStringData.mpEnd) {
        *mStringData.mpBegin = 0;
        mStringData.mpEnd = mStringData.mpBegin;
    }
    mTextAttributeData.clear();
    mbCompositionStarted = false;
    if (mStringData.mpBegin == mStringData.mpEnd) {
        mpStringData = 0;
        mpTextAttributeData = 0;
        mnDataLength = 0;
    } else {
        mpStringData = mStringData.mpBegin;
        mpTextAttributeData = mTextAttributeData.mpBegin;
        mnDataLength = (unsigned)(mStringData.mpEnd - mStringData.mpBegin);
    }
}

// ---------------------------------------------------------------- IMEServer bodies
// @ 0x0084a590
bool IMEServer::EnsureInitialized() {
    if (!mbInitialized) {
        mbInitialized = true;
        if (mpMessageServer == 0)
            mpMessageServer = EA_Messaging_GetServer();
        if (mbEnabled) {
            mbEnabled = false;
            v05(1);
        }
    }
    return true;
}

// @ 0x0084a5d0
bool IMEServer::Shutdown() {
    if (mbInitialized) {
        mbInitialized = false;
        mpMessageServer = 0;
        v05(0);
    }
    return true;
}

// @ 0x0084abd0
IMEServer::~IMEServer() {
    if (mbInitialized) {
        mbInitialized = false;
        mpMessageServer = 0;
        v05(0);
    }
    // mDataPointers, mStringArray and mCompData are destroyed by the compiler
}

// @ 0x0084ad40
void IMEServer::WriteCompositionString(HWND hwnd, int a, int b, unsigned flags) {
    HIMC h = ImmGetContext(hwnd);
    if (h == 0)
        return;
    if (flags & 0x10) {
        LONG n = ImmGetCompositionStringW(h, 0x10, 0, 0);
        mCompData.mTextAttributeData.resize((unsigned)n);
        if (n > 0)
            ImmGetCompositionStringW(h, 0x10, mCompData.mTextAttributeData.mpBegin,
                                     (unsigned)(mCompData.mTextAttributeData.mpEnd - mCompData.mTextAttributeData.mpBegin));
        uint8_t* p = mCompData.mTextAttributeData.mpBegin;
        unsigned cnt = (unsigned)(mCompData.mTextAttributeData.mpEnd - p);
        for (unsigned i = 0; i < cnt; ++i) {
            switch (p[i]) {
            case 0: p[i] = 1; break;
            case 1: p[i] = 2; break;
            case 4: p[i] = 3; break;
            default: p[i] = 0; break;
            }
        }
    }
    if (flags & 8) {
        LONG n = ImmGetCompositionStringW(h, 8, 0, 0);
        mCompData.mStringData.resize((unsigned)n >> 1);
        if (n > 0)
            ImmGetCompositionStringW(h, 8, mCompData.mStringData.mpBegin,
                                     (unsigned)(mCompData.mStringData.mpEnd - mCompData.mStringData.mpBegin));
        if ((unsigned)(mCompData.mTextAttributeData.mpEnd - mCompData.mTextAttributeData.mpBegin) <
            (unsigned)(mCompData.mStringData.mpEnd - mCompData.mStringData.mpBegin)) {
            unsigned c = (unsigned)(mCompData.mStringData.mpEnd - mCompData.mStringData.mpBegin);
            uint8_t zero = 0;
            VecFill(c, &zero);
        }
    }
    if (flags & 0x800) {
        LONG n = ImmGetCompositionStringW(h, 0x800, 0, 0);
        mCompData.mResultStringData.resize((unsigned)n >> 1);
        if (n > 0)
            ImmGetCompositionStringW(h, 0x800, mCompData.mResultStringData.mpBegin,
                                     (unsigned)(mCompData.mResultStringData.mpEnd - mCompData.mResultStringData.mpBegin));
        if ((unsigned)(mCompData.mTextAttributeData.mpEnd - mCompData.mTextAttributeData.mpBegin) <
            (unsigned)(mCompData.mResultStringData.mpEnd - mCompData.mResultStringData.mpBegin)) {
            unsigned c = (unsigned)(mCompData.mResultStringData.mpEnd - mCompData.mResultStringData.mpBegin);
            uint8_t zero = 0;
            VecFill(c, &zero);
        }
        mCompData.mbCompositionStarted = true;
    }
    if (flags & 0x80) {
        LONG n = ImmGetCompositionStringW(h, 0x80, 0, 0);
        mCompData.mnCaretPosition = (unsigned)n;
        unsigned len = (unsigned)(mCompData.mStringData.mpEnd - mCompData.mStringData.mpBegin);
        if (len < (unsigned)n)
            mCompData.mnCaretPosition = len;
    }
    if (mCompData.mStringData.mpBegin == mCompData.mStringData.mpEnd) {
        mCompData.mpStringData = 0;
        mCompData.mpTextAttributeData = 0;
        mCompData.mnDataLength = 0;
        ImmReleaseContext(hwnd, h);
        return;
    }
    mCompData.mpStringData = mCompData.mStringData.mpBegin;
    mCompData.mpTextAttributeData = mCompData.mTextAttributeData.mpBegin;
    mCompData.mnDataLength = (unsigned)(mCompData.mStringData.mpEnd - mCompData.mStringData.mpBegin);
    ImmReleaseContext(hwnd, h);
}

// ---------------------------------------------------------------- IMEServerWin32 bodies
// @ 0x0084a230
void IMEServerWin32::SetEnabled(bool b) {
    if (mbEnabled != b) {
        mbEnabled = b;
        if (b == false) {
            if (mpCanvas != 0) {
                if (mpCanvas->c25() != 0) {
                    IMECompositionTarget* q = (IMECompositionTarget*)mpCanvas->c25();
                    q->q11((void*)((char*)this + 0xbc), 0x1ee100c, 0xffffd8f1);
                }
            }
            mhWnd = 0;
        } else {
            if (mhWnd == 0) {
                if (mpCanvas != 0)
                    mhWnd = mpCanvas->c37();
            }
            if (mpCanvas != 0) {
                if (mpCanvas->c25() != 0) {
                    IMECompositionTarget* q = (IMECompositionTarget*)mpCanvas->c25();
                    q->q09((void*)((char*)this + 0xbc), 0x1ee100c);
                }
            }
            if (mD0 == 0)
                mD0 = FUN_008d3110();
            HIMC h = ImmGetContext(mhWnd);
            if (h != 0) {
                ImmGetConversionStatus(h, (LPDWORD)((char*)this + 0xc4), (LPDWORD)((char*)this + 0xc8));
                ImmReleaseContext(mhWnd, h);
            }
        }
    }
}

// @ 0x0084a360
bool IMEServerWin32::IsOpen() {
    HIMC h = ImmGetContext(mhWnd);
    if (h != 0) {
        BOOL r = ImmGetOpenStatus(h);
        ImmReleaseContext(mhWnd, h);
        return r != 0;
    }
    return false;
}

// @ 0x0084a3a0
bool IMEServerWin32::SetOpenEnabled(bool b) {
    bool isKana = ((unsigned)GetKeyboardLayout(0) & 0x3ff) == 0x12;
    HIMC h = ImmGetContext(mhWnd);
    if (h != 0) {
        if (b != 0) {
            b = ImmSetOpenStatus(h, 1) != 0;
            if (isKana)
                ImmSimulateHotKey(mhWnd, 0x52);
            else
                ImmSetConversionStatus(h, mC4 | 1, mC8);
        } else {
            if (isKana)
                ImmSimulateHotKey(mhWnd, 0x52);
            else
                ImmGetConversionStatus(h, (LPDWORD)((char*)this + 0xc4), (LPDWORD)((char*)this + 0xc8));
            b = ImmSetOpenStatus(h, 0) != 0;
        }
        ImmReleaseContext(mhWnd, h);
        return b;
    }
    return false;
}

// @ 0x0084a470
bool IMEServerWin32::NotifyClosed(bool b) {
    if (b != v09() && b == false) {
        HIMC h = ImmGetContext(mhWnd);
        if (h != 0) {
            BOOL r = ImmNotifyIME(h, 0x15, 4, 0);
            ImmReleaseContext(mhWnd, h);
            return r != 0;
        }
    }
    return true;
}

// @ 0x0084a4d0
bool IMEServerWin32::SetConversion(bool b) {
    if (b != v13()) {
        HIMC h = ImmGetContext(mhWnd);
        if (h != 0) {
            BOOL r = ImmNotifyIME(h, (b == false) + 0x10, 0, 0);
            ImmReleaseContext(mhWnd, h);
            return r != 0;
        }
        return false;
    }
    return true;
}

// @ 0x0084a540
void IMEServerWin32::SetCompositionWindow(unsigned short a, unsigned short b, int c) {
    if (mD0 != 0) {
        struct Form {
            int f0; int f1; int f2; int f3;
            unsigned char f4; unsigned char pad11; unsigned short f5;
            uint32_t pad[3];
        };
        Form form;
        form.f1 = 0;
        form.f4 = 0;
        form.f3 = a;
        form.f5 = b;
        form.f0 = 4;
        form.f2 = 2;
        ((IMEWindow*)mD0)->w12(&form);
    }
}

// @ 0x0084a600
void IMEServerWin32::SetFlag(bool b) {
    if (mbEnabled != b)
        mbEnabled = b;
}

// @ 0x0084a640
bool IMEServerWin32::SetCandidateSelection(unsigned idx) {
    if (idx < (unsigned)(mStringArray.mpEnd - mStringArray.mpBegin)) {
        HIMC h = ImmGetContext(mhWnd);
        if (h != 0) {
            BOOL r = ImmNotifyIME(h, 0x12, 0, idx);
            ImmReleaseContext(mhWnd, h);
            return r != 0;
        }
    }
    return false;
}

// @ 0x0084acf0
IMEServerWin32::~IMEServerWin32() {}

// @ 0x0084aab0
bool IMEServerWin32::AssignComposition(const wchar_t* s, int len) {
    mCompData.mStringData.assign(s, s + len);
    return true;
}

// @ 0x0084ab80
bool IMEServerWin32::SetCompositionData(const wchar_t* s, int len) {
    if (mhWnd != 0) {
        HIMC h = ImmGetContext(mhWnd);
        if (ImmSetCompositionStringW(h, 9, s, len * 2, 0, 0) != 0) {
            mCompData.mStringData.assign(s, s + len);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------- Canvas
// @ 0x00849f70
int Canvas_FlushInput() {
    // Drain WM_KEY* messages (up to 0x400) and repost the survivors.
    tagMSG msg;
    int count = 0;
    while (count < 0x400 && PeekMessageA(&msg, 0, 0x100, 0x109, 1)) {
        ++count;
        PostMessageA(msg.hwnd, msg.message, msg.wParam, msg.lParam);
    }
    return 0;
}
