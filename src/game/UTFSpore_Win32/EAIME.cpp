// src/game/UTFSpore_Win32/EAIME.cpp -- migrated from slice(s) s0084af40, s00849f70 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAIME.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00849f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HWND;
typedef void* HIMC;
typedef int BOOL;
typedef unsigned long DWORD;
typedef void* LPVOID;
typedef long LONG;
extern "C" HIMC __stdcall ImmGetContext(HWND);
extern "C" BOOL __stdcall ImmReleaseContext(HWND, HIMC);
extern "C" BOOL __stdcall ImmNotifyIME(HIMC, DWORD, DWORD, DWORD);
extern "C" LONG __stdcall ImmGetCompositionStringW(HIMC, DWORD, LPVOID, DWORD);
void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380
void  DoInsertValue(void* dst, const void* src, unsigned n);   // 0x011e0744 (memcpy-ish)
void  VecFill(unsigned n, const void* value);                  // 0x0068e8a0
void* EA_Messaging_GetServer();                                // 0x00883860
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
struct IMEWindow {
virtual void w00();
virtual void w01();
virtual void w02();
virtual void w03();
virtual void w04();
virtual void w05();
virtual void w06();
virtual void w07();
virtual void w08();
virtual void w09();
virtual void w10();
virtual void w11();
    virtual void w12(void* form);
};
struct CanvasStub {
virtual void c00();
virtual void c01();
virtual void c02();
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
    virtual void* c25();
virtual void c26();
virtual void c27();
virtual void c28();
virtual void c29();
virtual void c30();
virtual void c31();
virtual void c32();
virtual void c33();
virtual void c34();
virtual void c35();
    virtual void c36();
    virtual void* c37();
};
struct IHandler {
    virtual void h00() = 0;      // slot 1 -> _purecall, matching the image vtable at 0x13eb394
    virtual ~IHandler();         // slot 0 -> ??_GIHandler; the empty body inlines to the vptr reset
};
IHandler::~IHandler() {}
class IMEServer {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
    virtual void v05(int);              // +0x14
virtual void v06();
virtual void v07();
virtual void v08();
    virtual bool v09();                 // +0x24
virtual void v10();
virtual void v11();
virtual void v12();
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
    IMEServerWin32();          // image ctor 0x0084b2e0 (only defined to emit the class vtable)
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
    // Scalar deleting dtor (??_G, image 0x0084acf0). The image ctor emits the vtable, so the
    // inline body lands in ??_G together with the IMEServer base-dtor call and the delete.
    virtual ~IMEServerWin32() {
        if (mbInitialized) {
            mbInitialized = false;
            mpMessageServer = 0;
            SetEnabled(false);                     // derived slot-5 target (0x0084a230)
        }
    }
    bool AssignComposition(const wchar_t* s, int len);   // @ 0084aab0
    bool SetCompositionData(const wchar_t* s, int len);  // @ 0084ab80
};
IMEServerWin32::IMEServerWin32() {
}
// ---- items of slice s00849f70 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" HIMC __stdcall ImmGetContext(HWND);
extern "C" BOOL __stdcall ImmReleaseContext(HWND, HIMC);
extern "C" BOOL __stdcall ImmNotifyIME(HIMC, DWORD, DWORD, DWORD);
extern "C" LONG __stdcall ImmGetCompositionStringW(HIMC, DWORD, LPVOID, DWORD);

// ---- items of slice s0084af40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);   // 0x011e0744
extern "C" void* __cdecl memset(void*, int, unsigned int);           // 0x011e073e
extern "C" unsigned __stdcall ImmGetCandidateListW(void* hIMC, unsigned nIndex, void* pBuf, unsigned nBufLen); // 0x01209528
extern "C" __declspec(dllimport) int   __stdcall ImmSetOpenStatus(void* hIMC, int bOpen);
extern "C" __declspec(dllimport) int   __stdcall ImmDisableTextFrameService(unsigned dwThreadId);
extern "C" __declspec(dllimport) long  __stdcall DefWindowProcA(void* hWnd, unsigned uMsg, unsigned wParam, long lParam);
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsncpy(wchar_t*, const wchar_t*, unsigned);
typedef unsigned int   uint32;
void* __cdecl EAAllocate(uint32 n, const char* pName, int a, int b, const char* pFile, int line); // 0x00f473a0
void  __cdecl PoolFree(void* p);                                                               // 0x00f47380
struct WString_s0084_af40 {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    unsigned mAllocator; // +0x0c (empty eastl::allocator padding; element stride 0x10)

    WString_s0084_af40() {}                                                 // trivial
    WString_s0084_af40(wchar_t c);                                          // 0x0084aa60
    __forceinline WString_s0084_af40(const wchar_t* p, unsigned n)
    {
        unsigned nAlloc = n + 1;
        if (nAlloc > 1) {
            mpBegin = (wchar_t*)EAAllocate(nAlloc * 2, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
            mpEnd = mpBegin + n;
            mpCapacity = mpBegin + nAlloc;
            memcpy(mpBegin, p, n * 2);
            *mpEnd = 0;
        } else {
            mpBegin = (wchar_t*)0x01667bac;
            mpEnd = (wchar_t*)0x01667bac;
            mpCapacity = (wchar_t*)0x01667bae;
        }
    }
    WString_s0084_af40& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
    WString_s0084_af40& operator=(const WString_s0084_af40& o)
    {
        if (this != &o)
            assign(o.mpBegin, o.mpEnd);
        return *this;
    }
};
struct WStringVec {
    WString_s0084_af40* mpBegin;    // +0x00
    WString_s0084_af40* mpEnd;      // +0x04
    WString_s0084_af40* mpCapacity; // +0x08
};
struct CharPtrVec {
    wchar_t** mpBegin;   // +0x00
    wchar_t** mpEnd;     // +0x04
    wchar_t** mpCapacity;// +0x08
};
struct IMECompositionStringDataEx_s0084_af40 {
    // The candidate vector lives at +0x90 absolute, i.e. at +0x24 of this object.  The two vector
    // helpers (ResizeCandidates / InsertCandidates) are given the vector itself as `this`, so this
    // alias names the vector's three pointers when the object is viewed from its start.
    union {
        struct {
            wchar_t**  mpStringDataArray;       // +0x00
            unsigned   mnStringDataArrayLength; // +0x04
            unsigned   mnSelectionPosition;     // +0x08
        };
        WStringVec mVectorAtZero;  // +0x00 (view used by ResizeCandidates/InsertCandidates)
    };
    wchar_t    mLocale[12];    // +0x0c
    WStringVec mCandidates;    // +0x24 (wstring vector that FUN_0084af40 rebuilds)
    int        mPad30;
    int        mPad34;
    CharPtrVec mPtrs;          // +0x38 (pointer vector the candidate list feeds)
    char       mPad44[0x08];
    char       mFlag4c;        // +0x4c

    void RebuildCandidates();                                       // 0x0084af40
    void Reset();                                                   // 0x0084b1a0
    void Clear();                                                   // 0x0084b1f0
    void ResizeCandidates(unsigned nCount);                         // 0x0084b260
    void* InsertCandidates(WString_s0084_af40* pWhere, unsigned nCount, const WString_s0084_af40* pValue);  // 0x0084afc0
};
struct CANDIDATELIST {
    unsigned dwSize;       // +0x00
    unsigned dwStyle;      // +0x04
    unsigned dwCount;      // +0x08
    unsigned dwSelection;  // +0x0c
    unsigned dwPageStart;  // +0x10
    unsigned dwPageSize;   // +0x14
    unsigned dwOffset[1];  // +0x18
};
struct IMEServerWin32_s0084_af40 {
    void*   mpVtbl0;          // +0x00
    char    mByte04;          // +0x04
    char    mByte05;          // +0x05
    short   mPad06;           // +0x06
    int     mInt08;           // +0x08
    char    mCompData[0x60];  // +0x0c .. +0x6b
    IMECompositionStringDataEx_s0084_af40 mCandidateData;  // +0x6c .. +0xbb
    void*   mpHandlerVtbl;    // +0xbc
    int     mIntC0;           // +0xc0
    int     mIntC4;           // +0xc4
    int     mIntC8;           // +0xc8
    int     mIntCc;           // +0xcc
    int     mIntD0;           // +0xd0
    char    mByteD4;          // +0xd4

    void SetIMECandidateListData(void* hWnd, unsigned uMsg, unsigned nFlags, unsigned lParam); // 0x0084b390
    long WinProc(void* hWnd, unsigned uMsg, unsigned wParam, long lParam);   // 0x0084b600
};
void  __cdecl eastl_VectorResize(void* pVec, unsigned nCount);            // 0x00999fb0
void  __cdecl WStringPushBack(WString_s0084_af40* pStr, wchar_t ch);                 // 0x004f6510
void* __cdecl CopyWStrings(void* pDst, const void* pFirst, const void* pLast);  // 0x0084ab40
void  __cdecl VectorWStringDoDestroyValues(void* pVec, void* pFirst, void* pLast); // 0x0084aad0
void  __cdecl CopyBytes(void* pDst, const void* pSrc, unsigned n);        // 0x011e0744
void  __cdecl IMECompositionStringDataExCtor(void* pThis);                // 0x0084a700
extern "C" void* __stdcall ImmGetContext_s0084_af40(void* hWnd);                                        // 0x012094f2
extern "C" int   __stdcall ImmReleaseContext_s0084_af40(void* hWnd, void* hIMC);                        // 0x012094e6
// ---- items of slice s0084af40 end

// @ 0x0084a540
void IMEServerWin32::SetCompositionWindow(unsigned short a, unsigned short b, int c)
{
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

// @ 0x0084a590
bool IMEServer::EnsureInitialized()
{
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
bool IMEServer::Shutdown()
{
    if (mbInitialized) {
        mbInitialized = false;
        mpMessageServer = 0;
        v05(0);
    }
    return true;
}

// @ 0x0084a600
void IMEServerWin32::SetFlag(bool b)
{
    if (mbEnabled != b)
        mbEnabled = b;
}

// @ 0x0084a640
bool IMEServerWin32::SetCandidateSelection(unsigned idx)
{
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

// @ 0x0084a6a0
IMECompositionStringDataEx::~IMECompositionStringDataEx()
{
    if (mTextAttributeData.mpBegin && *(int*)((char*)mTextAttributeData.mpBegin - 4))
        EASTL_allocator_deallocate(mTextAttributeData.mpBegin);
    FreeWString(mResultStringData);
    FreeWString(mStringData);
}

// @ 0x0084a700
IMECompositionStringDataEx::IMECompositionStringDataEx()
{
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

// @ 0x0084a830
void ConstructWStrings(WString** ppDst, const WString* first, const WString* last, WString* pos)
{
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

// @ 0x0084a8f0
void ConstructWStringsN(WString* dst, unsigned count, const WString* src)
{
    if (count == 0)
        return;
    WString* p = dst;
    do {
        if (p) {
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
        }
        p = (WString*)((char*)p + 0x10);
        --count;
    } while (count != 0);
}

// @ 0x0084a9a0
WString* UninitializedCopyWStrings(const WString* first, const WString* last, WString* dst)
{
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

// @ 0x0084abd0
IMEServer::~IMEServer()
{
    if (mbInitialized) {
        mbInitialized = false;
        mpMessageServer = 0;
        // The dtor prologue stores IMEServer's vtable first, so MSVC devirtualizes
        // v05(0) into a direct call of the slot-5 target: SetFlag @ 0x0084a600.
        ((IMEServerWin32*)this)->SetFlag(false);
    }
    // mDataPointers, mStringArray and mCompData are destroyed by the compiler
}

// @ 0x0084ac50
void IMECompositionStringDataEx::Reset()
{
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

// @ 0x0084ad40
void IMEServer::WriteCompositionString(HWND hwnd, int a, int b, unsigned flags)
{
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

// @ 0x0084af40
void IMECompositionStringDataEx_s0084_af40::RebuildCandidates()
{
    if (mCandidates.mpEnd == mCandidates.mpCapacity) {
        mpStringDataArray = 0;
        mnStringDataArrayLength = 0;
        return;
    }
    unsigned nCount = (unsigned)(mCandidates.mpEnd - mCandidates.mpBegin);
    mnStringDataArrayLength = nCount;
    eastl_VectorResize(&mPtrs, nCount);

    for (unsigned i = 0; i < mnStringDataArrayLength; ++i) {
        WString_s0084_af40* pStr = &mCandidates.mpBegin[i];
        if (pStr->mpEnd == pStr->mpBegin || pStr->mpBegin[(pStr->mpEnd - pStr->mpBegin) - 1] != 0)
            WStringPushBack(pStr, 0);
        mPtrs.mpBegin[i] = pStr->mpBegin;
    }
    mpStringDataArray = mPtrs.mpBegin;
}

// @ 0x0084afc0
void* IMECompositionStringDataEx_s0084_af40::InsertCandidates(WString_s0084_af40* pWhere, unsigned nCount, const WString_s0084_af40* pValue)
{
    WString_s0084_af40* pOldEnd = mVectorAtZero.mpEnd;
    if (pWhere == pOldEnd) {
        for (unsigned i = 0; i < nCount; ++i) {
            mVectorAtZero.mpEnd[i] = *pValue;
            ++mVectorAtZero.mpEnd;
        }
    } else {
        WString_s0084_af40* pPos = pWhere + nCount;
        CopyWStrings(pPos, pWhere, pOldEnd);
        mVectorAtZero.mpEnd = pOldEnd + nCount;
        for (unsigned i = 0; i < nCount; ++i) pWhere[i] = *pValue;
    }
    return pWhere;
}

// @ 0x0084b1a0
void IMECompositionStringDataEx_s0084_af40::Reset()
{
    mCandidates.mpBegin = 0;
    mCandidates.mpEnd = 0;
    mCandidates.mpCapacity = 0;
    mPtrs.mpBegin = 0;
    mPtrs.mpEnd = 0;
    mPtrs.mpCapacity = 0;
    mFlag4c = 0;
    mnSelectionPosition = 0;

    const wchar_t* pSrc = L"en-us";
    wchar_t* pDst = mLocale;
    while ((*pDst++ = *pSrc++) != 0) {}

    RebuildCandidates();
}

// @ 0x0084b1f0
void IMECompositionStringDataEx_s0084_af40::Clear()
{
    WString_s0084_af40* pBegin = mCandidates.mpBegin;
    WString_s0084_af40* pEnd = mCandidates.mpEnd;
    eastl_VectorResize(&mCandidates, 0);
    (void)pBegin; (void)pEnd;
    mCandidates.mpEnd = mCandidates.mpBegin;
    CopyBytes(mPtrs.mpEnd, mPtrs.mpEnd, 0);
    mPtrs.mpEnd = mPtrs.mpBegin;
    RebuildCandidates();
}

// @ 0x0084b260
void IMECompositionStringDataEx_s0084_af40::ResizeCandidates(unsigned nCount)
{
    unsigned nHave = (unsigned)(mVectorAtZero.mpEnd - mVectorAtZero.mpBegin);
    if (nCount > nHave) {
        WString_s0084_af40 empty;
        empty.mpBegin = (wchar_t*)0x01667bac;
        empty.mpEnd = (wchar_t*)0x01667bac;
        empty.mpCapacity = (wchar_t*)0x01667bae;
        InsertCandidates(mVectorAtZero.mpEnd, nCount - nHave, &empty);
    } else {
        WString_s0084_af40* pPos = mVectorAtZero.mpBegin + nCount;
        WString_s0084_af40* pNewEnd = (WString_s0084_af40*)CopyWStrings(mVectorAtZero.mpBegin, mVectorAtZero.mpEnd, pPos);
        VectorWStringDoDestroyValues(&mVectorAtZero, pNewEnd, mVectorAtZero.mpEnd);
        mVectorAtZero.mpEnd = mVectorAtZero.mpEnd - (mVectorAtZero.mpEnd - pNewEnd);
    }
}

// @ 0x0084b2e0
void* IMEServerWin32Ctor(void* pThis)
{
    char* p = (char*)pThis;
    *(void**)p = (void*)0x0141cb28;
    p[4] = 0;
    p[5] = 1;
    *(int*)(p + 8) = 0;
    IMECompositionStringDataExCtor(p + 0xc);          // 0x0084a700
    ((IMECompositionStringDataEx_s0084_af40*)(p + 0x6c))->Reset();
    *(void**)(p + 0xbc) = (void*)0x013eb394;
    *(int*)(p + 0xc0) = 0;
    *(int*)(p + 0xc4) = 0;
    *(int*)(p + 0xc8) = 0;
    *(int*)(p + 0xcc) = 0;
    *(int*)(p + 0xd0) = 0;
    p[0xd4] = 0;
    wcsncpy((wchar_t*)(p + 0x1c), L"en-us", 12);
    *(void**)p = (void*)0x0141cb78;
    *(void**)(p + 0xbc) = (void*)0x0141cb6c;
    *(wchar_t*)(p + 0x1c + 0x16) = 0;
    wcsncpy((wchar_t*)(p + 0x78), L"en-us", 12);
    *(wchar_t*)(p + 0x78 + 0x16) = 0;
    ImmDisableTextFrameService(0xffffffff);
    return p;
}

// @ 0x0084b390
void IMEServerWin32_s0084_af40::SetIMECandidateListData(void* hWnd, unsigned uMsg, unsigned nFlags, unsigned lParam)
{
    (void)uMsg;
    (void)lParam;

    void* hIMC = ImmGetContext_s0084_af40(hWnd);
    if (hIMC != 0) {
        for (unsigned i = 0; i < 0x20; ++i) {
            if ((nFlags & (1u << i)) == 0)
                continue;

            unsigned nSize = ImmGetCandidateListW(hIMC, i, 0, 0);
            if (nSize == 0)
                continue;

            CANDIDATELIST* pList = (CANDIDATELIST*)EAAllocate(nSize, "EAApp/IME/pCandidateListData", 0, 0, 0, 0);
            memset(pList, 0, nSize);
            ImmGetCandidateListW(hIMC, i, pList, nSize);

            unsigned nSelection = pList->dwSelection;
            if (nSelection < pList->dwPageStart ||
                pList->dwCount + pList->dwPageStart <= nSelection) {
                if (pList->dwCount == 0)
                    pList->dwPageStart = 0;
                else
                    pList->dwPageStart = (nSelection / pList->dwCount) * pList->dwCount;
            }

            if (pList->dwStyle == 2 && pList->dwCount == 1) {
                ((IMECompositionStringDataEx_s0084_af40*)&mCandidateData.mCandidates)->ResizeCandidates(1);

                WString_s0084_af40 string((wchar_t)pList->dwOffset[0]);
                mCandidateData.mCandidates.mpBegin[0] = string;

                int nSpare = (int)((char*)string.mpCapacity - (char*)string.mpBegin) & 0xfffffffe;
                if (nSpare > 2 && string.mpBegin != 0)
                    PoolFree(string.mpBegin);
            } else {
                ((IMECompositionStringDataEx_s0084_af40*)&mCandidateData.mCandidates)->ResizeCandidates(pList->dwCount);

                for (unsigned j = 0; j < pList->dwCount; ++j) {
                    const wchar_t* pSrc = (const wchar_t*)((const char*)pList + pList->dwOffset[j]);
                    const wchar_t* pEnd = pSrc;
                    while (*pEnd != 0)
                        ++pEnd;

                    WString_s0084_af40 string(pSrc, (unsigned)(pEnd - pSrc));
                    mCandidateData.mCandidates.mpBegin[j] = string;

                    int nSpare = (int)((char*)string.mpCapacity - (char*)string.mpBegin) & 0xfffffffe;
                    if (nSpare > 2 && string.mpBegin != 0)
                        PoolFree(string.mpBegin);
                }
            }

            mCandidateData.mnSelectionPosition = pList->dwSelection;
            PoolFree(pList);
        }
        ImmReleaseContext_s0084_af40(hWnd, hIMC);
    }

    mCandidateData.RebuildCandidates();
}

// @ 0x0084b600
long IMEServerWin32_s0084_af40::WinProc(void* hWnd, unsigned uMsg, unsigned wParam, long lParam)
{
    if (uMsg == 0x281)   // WM_IME_COMPOSITION
        return 0;
    if (uMsg == 0x286) { // WM_IME_CHAR
        ImmSetOpenStatus(hWnd, 1);
        return 0;
    }
    if (uMsg == 7)       // WM_SETFOCUS
        return 0;
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}
