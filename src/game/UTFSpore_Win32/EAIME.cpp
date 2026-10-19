// src/game/UTFSpore_Win32/EAIME.cpp -- migrated from slice(s) s00849f70 by tools/migrate/rewrite.py
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
extern "C" LONG __stdcall ImmGetCompositionStringW(HIMC, DWORD, LPVOID, DWORD);
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
// ---- items of slice s00849f70 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" HIMC __stdcall ImmGetContext(HWND);
extern "C" BOOL __stdcall ImmReleaseContext(HWND, HIMC);
extern "C" LONG __stdcall ImmGetCompositionStringW(HIMC, DWORD, LPVOID, DWORD);

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
