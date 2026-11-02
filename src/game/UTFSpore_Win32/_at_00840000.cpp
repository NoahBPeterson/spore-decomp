// src/game/UTFSpore_Win32/_at_00840000.cpp -- migrated from slice(s) s0084faf0, s0084ebe0, s0084dcd0, s0084cd70, s00849f70, s00847200, s00840250 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00840000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <setjmp.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int   __cdecl _stricmp(const char* a, const char* b);
extern "C" __declspec(dllimport) unsigned __cdecl strspn(const char* s, const char* set);
extern "C" __declspec(dllimport) unsigned __cdecl strcspn(const char* s, const char* set);

// ---- items of slice s00840250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int   __cdecl _stricmp(const char* a, const char* b);
extern "C" __declspec(dllimport) unsigned __cdecl strspn(const char* s, const char* set);
extern "C" __declspec(dllimport) unsigned __cdecl strcspn(const char* s, const char* set);
// ---- items of slice s00840250 end

// ---- items of slice s00847200 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyStr[4];          // 0x01667bac: shared empty string storage
extern void* gEmptyBucketArray[1]; // 0x0154df28
extern void* gIncludeRecordVtbl;    // 0x0141ca24
extern void* gLocalizedStringFmt;   // 0x013f3da0
typedef void* HBRUSH;
typedef void* HICON;
typedef void* HINSTANCE;
typedef const char* LPCSTR;
typedef unsigned int UINT;
struct WNDCLASSEXA {
    UINT   cbSize;
    UINT   style;
    void*  lpfnWndProc;
    int    cbClsExtra;
    int    cbWndExtra;
    HINSTANCE hInstance;
    HICON  hIcon;
    void*  hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
    HICON  hIconSm;
};
extern "C" __declspec(dllimport) HICON __stdcall LoadIconA(HINSTANCE, LPCSTR);
void* EAAllocate(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void operator delete(void* p);                                                   // 0x00f47380
namespace eastl {
class allocator_s0084_7200 { public: unsigned char pad[4]; };
}
namespace eastl {
struct string8_s0084_7200 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0084_7200 mAllocator;

    string8_s0084_7200() { mpBegin = gEmptyStr; mpEnd = gEmptyStr; mpCapacity = gEmptyStr + 1; }
    ~string8_s0084_7200() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete(mpBegin); }
};
}
namespace eastl {
struct Hashtable {
    unsigned   mUninit0;       // +0x00
    void**     mpBucketArray;  // +0x04
    unsigned   mnBucketCount;  // +0x08
    unsigned   mnElementCount; // +0x0c
    float      mfMaxLoad;      // +0x10
    float      mfGrowth;       // +0x14
    unsigned   mnNextResize;   // +0x18
    unsigned   mUninit1c;      // +0x1c

    Hashtable()
    {
        mfMaxLoad = 1.0f;
        mfGrowth = 2.0f;
        mnBucketCount = 1;
        mpBucketArray = gEmptyBucketArray;
        mnElementCount = 0;
        mnNextResize = 0;
    }
    ~Hashtable()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1) operator delete(mpBucketArray);
    }
    void DoFreeNodes(void** pBucketArray, unsigned nBucketCount);
};
}
namespace eastl {
template <typename T>
struct vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s0084_7200 mAllocator;
    unsigned mExtra;
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vec() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete(mpBegin); }
};
}
using eastl::string8_s0084_7200;
using eastl::Hashtable;
using eastl::vec;
namespace EA {
namespace ArgScript {
class cArguments_s0084_7200 {
    public: unsigned char pad[0x44];
    cArguments_s0084_7200();
    ~cArguments_s0084_7200();
    void** MainArguments(int);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
};
}
}
namespace EA {
namespace ArgScript {
class cExpression_s0084_7200 { public: Hashtable mFunctions; cExpression_s0084_7200(); ~cExpression_s0084_7200() {} };
}
}
namespace EA {
namespace ArgScript {
struct IStream { virtual void v0(); virtual void v1(); virtual void Release(); };
}
}
namespace EA {
namespace ArgScript {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    void Release() {
        T* p = mpObject;
        if (p) p->Release();
    }
    ~AutoRefCount() { Release(); }
};
}
}
namespace EA {
namespace ArgScript {
class cIGlobalVariableSet { public: virtual void v0(); virtual void Release(); };
}
}
namespace EA {
namespace ArgScript {
struct cMetaEntry { void* mCommand; int mLine; };
}
}
namespace EA {
namespace ArgScript {
class cParser { public:
    void**   mvftable;          // +0x000
    unsigned mStateID;          // +0x004
    int      mRefCount;         // +0x008
    bool     mInitialized;      // +0x00c
    unsigned mFlags;            // +0x010
    AutoRefCount<IStream> mOutStream;    // +0x014
    AutoRefCount<IStream> mTraceStream;  // +0x018
    int      mMinVersion;       // +0x01c
    int      mMaxVersion;       // +0x020
    int      mScriptVersion;    // +0x024
    int      mUnknown28;        // +0x028
    Hashtable mCommands;        // +0x02c
    cExpression_s0084_7200 mExpression;    // +0x04c
    Hashtable mMacroDefinitions; // +0x06c
    Hashtable mVariables;       // +0x08c
    Hashtable mGlobalVariables; // +0x0ac
    AutoRefCount<cIGlobalVariableSet> mGlobalVariableSet;  // +0x0cc
    string8_s0084_7200  mIncludeBaseDir;   // +0x0d0
    string8_s0084_7200  mCurrentPath;      // +0x0e0
    int      mCurrentLine;      // +0x0f0
    string8_s0084_7200  mLineLocation;     // +0x0f4
    int      mBlockCommentDepth;// +0x0104
    vec<void*> mBlockCommandStack;   // +0x0108
    vec<cMetaEntry> mMetaCommandStack; // +0x011c
    string8_s0084_7200  mScope;            // +0x0130
    vec<int> mScopeOffsets;     // +0x0140
    string8_s0084_7200  mLastErrorString;  // +0x0154
    unsigned char mErrorStringHasFileQualification;  // +0x0164
    int      mTotalLinesParsed; // +0x0168
    cArguments_s0084_7200 mArgs;           // +0x016c
    string8_s0084_7200  mLCName;           // +0x01b0

    cParser();
    ~cParser();

    bool Shutdown();            // 0x00846db0
};
}
}
void* ObjectErrorSingleton();       // 0x008de1a0
void  cCommandBase_ctor(void* p);   // 0x0083c800
struct IncludeRecord {
    void*    mvftable;     // +0x00
    EA::ArgScript::cParser* mParser;      // +0x04
    int      mRefCount;    // +0x08
    void*    mField10;     // +0x10
    void*    mField14;     // +0x14
};
void WStr_Format(void* dest, void* fmt, ...);   // 0x0041e050
struct string16W {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    unsigned mPad;      // +0x0c
    string16W() {
        mpBegin = gEmptyStr;
        mpEnd = gEmptyStr;
        mpCapacity = gEmptyStr + 2;
    }
    ~string16W() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin)
            operator delete(mpBegin);
    }
};
// ---- items of slice s00847200 end

// ---- items of slice s00849f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HWND;
typedef void* HIMC;
typedef void* HKL;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned long* LPDWORD;
extern "C" __declspec(dllimport) HKL __stdcall GetKeyboardLayout(DWORD);
extern "C" HIMC __stdcall ImmGetContext(HWND);
extern "C" BOOL __stdcall ImmGetOpenStatus(HIMC);
extern "C" BOOL __stdcall ImmReleaseContext(HWND, HIMC);
extern "C" BOOL __stdcall ImmSetOpenStatus(HIMC, BOOL);
extern "C" BOOL __stdcall ImmSimulateHotKey(HWND, DWORD);
extern "C" BOOL __stdcall ImmGetConversionStatus(HIMC, LPDWORD, LPDWORD);
extern "C" BOOL __stdcall ImmSetConversionStatus(HIMC, DWORD, DWORD);
extern "C" BOOL __stdcall ImmNotifyIME(HIMC, DWORD, DWORD, DWORD);
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380
void  DoInsertValue(void* dst, const void* src, unsigned n);   // 0x011e0744 (memcpy-ish)
void* FUN_008d3110();                                          // 0x008d3110
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
struct IMECompositionTarget {
virtual void q00();
virtual void q01();
virtual void q02();
virtual void q03();
virtual void q04();
virtual void q05();
virtual void q06();
virtual void q07();
    virtual void q08();
    virtual void q09(void*, unsigned);
    virtual void q10();
    virtual void q11(void*, unsigned, unsigned);
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

// ---- items of slice s0084cd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int           __stdcall gread(void* f, void* buf, unsigned n);   // 0x0087d4e0
extern "C" void*         __cdecl   png_get_io_ptr(void* png);      // 0x0086aeb0
extern "C" void          __cdecl   png_error(void* png, const char* msg); // 0x0086b250
// ---- items of slice s0084cd70 end

// ---- items of slice s0084dcd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __stdcall gwrite(void* h, const void* buf, unsigned int n); // 0x0087d510
extern "C" void*        __cdecl memset(void* dst, int v, unsigned int n);           // 0x011e073e
#pragma function(memset)
typedef unsigned int png_size_t;
typedef unsigned char* png_bytep;
typedef void* png_voidp;
struct png_struct_def;
typedef png_struct_def* png_structp;
struct png_struct_def { jmp_buf jmpbuf; };
extern "C" png_voidp   __cdecl png_get_io_ptr_s0084_dcd0(png_structp);                            // 0x0086aeb0
extern "C" void __cdecl PNGREAD_write_data(png_structp, png_bytep, png_size_t);        // 0x0084e520
// ---- items of slice s0084dcd0 end

// ---- items of slice s0084ebe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned char __stdcall gfree(void* p);                                 // 0x0087d4c0
#pragma pack(push, 1)
#pragma pack(pop)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
// ---- items of slice s0084ebe0 end

// ---- items of slice s0084faf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int  FUN_0084fa60(int);             // 0x0084fa60
extern void* galloc(int size);                           // 0x0087d4a0 __stdcall
extern int  gwrite_s0084_faf0(void* out, void* buf, unsigned len);  // 0x0087d510 __stdcall
extern int  gfree_s0084_faf0(void* p);                              // 0x0087d4c0 __stdcall
// ---- items of slice s0084faf0 end

// @ 0x008407c0
unsigned char __cdecl LookupName8(const char* name, int* table, int* out)
{
    int key = *table;
    for (;;) {
        if (key == 0)
            return 0;
        if (_stricmp(name, (const char*)key) == 0) {
            *out = table[1];
            return 1;
        }
        table += 2;
        key = *table;
    }
}

// @ 0x00840810
int __cdecl LookupInt8(int key, int* table)
{
    int k = *table;
    while (k) {
        if (key == table[1])
            return *table;
        table += 2;
        k = *table;
    }
    return 0;
}

// @ 0x00840840
unsigned char __cdecl LookupName12(const char* name, int* table, int* out)
{
    int key = *table;
    for (;;) {
        if (key == 0)
            return 0;
        if (_stricmp(name, (const char*)key) == 0) {
            *out = table[1];
            return 1;
        }
        table += 3;
        key = *table;
    }
}

// @ 0x00840890
const char* __cdecl NextToken(const char* s, int* len, const char* delims)
{
    unsigned a = (unsigned)strspn(s, delims);
    unsigned b = (unsigned)strcspn(s + a, delims);
    *len = (int)b;
    return b ? s + a : 0;
}

// @ 0x008476b0
char __cdecl FUN_008476b0(void*, void* a2)
{
    char result = 0;
    int* app = (int*)ObjectErrorSingleton();
    int* parser = (int*)((int(__thiscall*)(int*, void*))*(int*)(*app + 0x58))(app, a2);
    if (parser) {
        unsigned char local = 0;
        char ok = ((char(__thiscall*)(int*, void*, void*, int, int, int, int))*(int*)(*parser + 0x34))(
            parser, a2, &local, 1, 6, 1, 0);
        result = 0;
        if (ok) {
            IncludeRecord* rec = (IncludeRecord*)EAAllocate(0x18, "IncludeRecord", 0, 0, 0, 0);
            if (rec) {
                int* src = (int*)a2;
                cCommandBase_ctor(rec);
                rec->mvftable = &gIncludeRecordVtbl;
                rec->mField10 = (void*)src[2];
                rec->mField14 = (void*)src[1];
            }
            ((void(__thiscall*)(int*, int*))*(int*)(*parser + 0x18))(parser, (int*)rec);
            ((void(__thiscall*)(void*, const char*, void*))*(int*)(*(int*)parser + 0x14))(parser, "include", rec);
            ((void(__thiscall*)(void*, const char*, void*))*(int*)(*(int*)parser + 0x14))(parser, "sinclude", rec);
            ((void(__thiscall*)(void*))*(int*)(*(int*)parser + 0x30))(parser);
            char r = ((char(__thiscall*)(void*, void*))*(int*)(*(int*)parser + 0x4c))(parser, rec);
            ((void(__thiscall*)(void*, int))*(int*)(*(int*)parser + 0x34))(parser, r == 0);
            if (rec)
                ((void(__thiscall*)(void*))*(int*)(*(int*)rec + 0x10))(rec);
            result = r;
        }
        if (parser)
            ((void(__thiscall*)(void*))*(int*)(*parser + 8))(parser);
    }
    return result;
}

// @ 0x00847810
void __fastcall FUN_00847810(void* this_, void* dummy, EA::ArgScript::cArguments_s0084_7200* args)
{
    (void)dummy;
    typedef void  (__thiscall *PFN_78)(void*, void*, void*, void*, void*);
    typedef void* (__thiscall *PFN_58)(void*, void*);
    typedef char  (__thiscall *PFN_34)(void*, void*, void**, int, int, int, int);
    typedef unsigned (__thiscall *PFN_18)(void*);
    typedef void  (__thiscall *PFN_4C)(void*, unsigned);
    typedef void  (__thiscall *PFN_0)(void*);

    void** mainArgs = args->MainArguments(1);
    void* err = ObjectErrorSingleton();
    string16W str;
    WStr_Format(&str, &gLocalizedStringFmt, mainArgs[0]);

    unsigned ctx[3] = { 0, 0, 0 };
    ((PFN_78)*(unsigned*)(*(unsigned*)err + 0x78))(err, ctx, str.mpBegin,
        *(void**)((char*)this_ + 0x14), *(void**)((char*)this_ + 0x10));
    ctx[2] = (unsigned)*(void**)((char*)this_ + 0x10);
    ctx[1] = (unsigned)*(void**)((char*)this_ + 0x14);

    void* parser = ((PFN_58)*(unsigned*)(*(unsigned*)err + 0x58))(err, ctx);
    typedef void (__thiscall *PFN_REL)(void*);
    struct ObjRef {
        void* p;
        ObjRef() : p(0) {}
        ~ObjRef() { if (p) ((PFN_REL)*(unsigned*)(*(unsigned*)p + 8))(p); }
    };
    ObjRef out;
    if (parser) {
        if (((PFN_34)*(unsigned*)(*(unsigned*)parser + 0x34))(parser, ctx, &out.p, 1, 6, 1, 0)) {
            unsigned v = ((PFN_18)*(unsigned*)(*(unsigned*)out.p + 0x18))(out.p);
            void* parse = *(void**)((char*)this_ + 4);
            ((PFN_4C)*(unsigned*)(*(unsigned*)parse + 0x4c))(parse, v);
            ((PFN_0)*(unsigned*)(*(unsigned*)out.p + 0x24))(out.p);
        }
    }
}

// @ 0x00847950
int __stdcall FUN_00847950(HINSTANCE hInstance, void* p2, LPCSTR name, WNDCLASSEXA* wc)
{
    (void)p2;
    wc->hIcon = LoadIconA(hInstance, name);
    return 0;
}

// @ 0x0084a230
void IMEServerWin32::SetEnabled(bool b)
{
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
bool IMEServerWin32::IsOpen()
{
    HIMC h = ImmGetContext(mhWnd);
    if (h != 0) {
        BOOL r = ImmGetOpenStatus(h);
        ImmReleaseContext(mhWnd, h);
        return r != 0;
    }
    return false;
}

// @ 0x0084a3a0
bool IMEServerWin32::SetOpenEnabled(bool b)
{
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
bool IMEServerWin32::NotifyClosed(bool b)
{
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
bool IMEServerWin32::SetConversion(bool b)
{
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

// @ 0x0084dc90
void __cdecl PNG_read_data(void* png, void* buf, int len)
{
    void* io = png_get_io_ptr(png);
    if (gread(io, buf, len) != len)
        png_error(png, "Read Error");
}

// @ 0x0084e520
void __cdecl PNGREAD_write_data(png_structp png, png_bytep data, png_size_t size)
{
    void* io = png_get_io_ptr_s0084_dcd0(png);
    if (gwrite(io, data, size) != size)
        png_error(png, "Write Error");
}

// @ 0x0084fa40
int __stdcall TGA_free(void* p)
{
    int r = 0;
    if (p != 0)
        r = gfree(p);
    return r;
}

// @ 0x0084fa60
int TGA_display_check(u8* arr, int count, int elemsize)
{
    int i = 0;
    const u8* base = arr;
    if (count > 0x80)
        count = 0x80;
    else if (count < 1)
        return 0;
    do {
        u32 a = 0, b = 0;
        int cmp = 1;
        switch (elemsize) {
        case 1: a = arr[0]; b = base[0]; break;
        case 2: a = *(u16*)arr; b = *(u16*)base; break;
        case 4: a = *(u32*)arr; b = *(u32*)base; break;
        case 3:
            a = (u32)arr[2] << 8 | arr[1];
            a = a << 8 | arr[0];
            b = (u32)base[2] << 8 | base[1];
            b = b << 8 | base[0];
            break;
        default: cmp = 0; break;   // unknown depth: original skips the compare
        }
        if (cmp && a != b)
            return i;
        i++;
        arr += elemsize;
    } while (i < count);
    return i;
}

// @ 0x0084faf0
int EmitSamples(void* out, int count, int fmt, int table, int flag, int alpha, uint8_t* src)
{
    uint16_t uVar1;
    uint16_t* dst = (uint16_t*)out;

    if (fmt == 0xf)
        fmt = 0x10;

    if (flag != 0) {
        while (count > 0) {
            int n0 = FUN_0084fa60(count);
            if (n0 < 3) {
                int ok = (n0 < 2);
                if (!ok) {
                    int n1 = FUN_0084fa60(count - n0);
                    ok = (n1 < 2 && fmt < 9);
                }
                if (ok) {
                    int run = 1;
                    int rem = count;
                    if (count > 1) {
                        for (;;) {
                            --rem;
                            if (run > 0x7f)
                                break;
                            int n2 = FUN_0084fa60(rem);
                            if (n2 > 2)
                                break;
                            if (n2 > 1 && fmt > 8)
                                break;
                            ++run;
                            if (run >= count)
                                break;
                        }
                    }
                    if (count - 3 <= run)
                        run = count;
                    if (run > 0x80)
                        run = 0x80;
                    *(uint8_t*)dst = (uint8_t)(run - 1);
                    dst = (uint16_t*)((int)dst + 1);
                    int k = run;
                    while (k != 0) {
                        --k;
                        if (fmt == 0x20) {
                            *(uint8_t*)((int)dst + 3) = src[3];
                            *(uint8_t*)(dst + 1) = src[2];
                            *(uint8_t*)((int)dst + 1) = src[1];
                            *(uint8_t*)dst = src[0];
                            dst += 2;
                            src += 4;
                        } else if (fmt == 0x18) {
                            *(uint8_t*)(dst + 1) = src[2];
                            *(uint8_t*)((int)dst + 1) = src[1];
                            *(uint8_t*)dst = src[0];
                            dst = (uint16_t*)((int)dst + 3);
                            src += 4;
                        } else if (fmt == 0x10) {
                            uVar1 = 0xff;
                            if (alpha)
                                uVar1 = (uint16_t)(src[3] >> 7);
                            *dst = (uint16_t)(((((uint16_t)(src[2] >> 3) |
                                                 (uint16_t)(uVar1 << 5)) << 5 |
                                               (uint16_t)(src[1] >> 3)) << 5) |
                                              (uint16_t)(src[0] >> 3));
                            dst += 1;
                            src += 4;
                        } else if (fmt == 8) {
                            *(uint8_t*)dst = *(uint8_t*)((uint32_t)src[0] + table);
                            dst = (uint16_t*)((int)dst + 1);
                            src += 1;
                        }
                    }
                    count -= run;
                    continue;
                }
            }
            *(uint8_t*)dst = (uint8_t)(n0 - 1) | 0x80;
            uint16_t* p = (uint16_t*)((int)dst + 1);
            if (fmt == 0x20) {
                *(uint8_t*)p = src[0];
                *(uint8_t*)(dst + 1) = src[1];
                *(uint8_t*)((int)dst + 3) = src[2];
                *(uint8_t*)(dst + 2) = src[3];
                p = (uint16_t*)((int)dst + 5);
                src += n0 * 4;
            } else if (fmt == 0x18) {
                *(uint8_t*)p = src[0];
                *(uint8_t*)(dst + 1) = src[1];
                *(uint8_t*)((int)dst + 3) = src[2];
                p = dst + 2;
                src += n0 * 4;
            } else if (fmt == 0x10) {
                uVar1 = 0xff;
                if (alpha)
                    uVar1 = (uint16_t)(src[3] >> 7);
                *p = (uint16_t)(((((uint16_t)(src[2] >> 3) |
                                   (uint16_t)(uVar1 << 5)) << 5 |
                                 (uint16_t)(src[1] >> 3)) << 5) |
                                (uint16_t)(src[0] >> 3));
                p = (uint16_t*)((int)dst + 3);
                src += n0 * 4;
            } else if (fmt == 8) {
                *(uint8_t*)p = *(uint8_t*)((uint32_t)src[0] + table);
                p = dst + 1;
                src += n0;
            }
            count -= n0;
            dst = p;
        }
        return (int)dst - (int)out;
    }

    if (count > 0) {
        do {
            if (fmt == 0x20) {
                *(uint8_t*)(dst) = src[0];
                *(uint8_t*)((int)dst + 1) = src[1];
                *(uint8_t*)(dst + 1) = src[2];
                *(uint8_t*)((int)dst + 3) = src[3];
                dst += 2;
                src += 4;
            } else if (fmt == 0x18) {
                *(uint8_t*)(dst) = src[0];
                *(uint8_t*)((int)dst + 1) = src[1];
                *(uint8_t*)(dst + 1) = src[2];
                dst = (uint16_t*)((int)dst + 3);
                src += 4;
            } else if (fmt == 0x10) {
                uVar1 = 0xff;
                if (alpha)
                    uVar1 = (uint16_t)(src[3] >> 7);
                *dst = (uint16_t)(((((uint16_t)(src[2] >> 3) |
                                     (uint16_t)(uVar1 << 5)) << 5 |
                                   (uint16_t)(src[1] >> 3)) << 5) |
                                  (uint16_t)(src[0] >> 3));
                dst += 1;
                src += 4;
            } else if (fmt == 8) {
                *(uint8_t*)(dst) = *(uint8_t*)((uint32_t)src[0] + table);
                dst = (uint16_t*)((int)dst + 1);
                src += 1;
            }
            count--;
        } while (count != 0);
    }
    return (int)dst - (int)out;
}

// @ 0x0084feb0
int CheckUniformRun(int count, uint8_t* dst, uint8_t* src)
{
    int i = 0;
    int ok = 1;
    if (count > 0) {
        uint8_t* p = src + 2;
        do {
            if (p[1] != 0xff || *p != p[-1] || *p != p[-2])
                ok = 0;
            dst[i] = p[-1];
            ++i;
            p += 4;
        } while (i < count);
        if (ok == 0) {
            i = 0;
            do {
                dst[i] = (uint8_t)i;
                ++i;
            } while (i < count);
        }
    }
    return ok;
}

// @ 0x0084ff00
void EncodeMcuHuff(int* stream, int* cinfo = 0)
{
    int height    = cinfo[5];        // +0x14
    int width     = cinfo[4];        // +0x10
    int num_comps = cinfo[9];        // +0x24
    int data_prec = cinfo[0x10e];    // +0x438
    int prec;

    if (cinfo[7] < 9) {
        prec = 8;
    } else if (data_prec < 2 && cinfo[0x10f] < 6 && cinfo[0x110] < 6 &&
               cinfo[0x111] < 6) {
        prec = 0x10;
    } else if (data_prec == 0) {
        prec = 0x18;
    } else {
        prec = 0x20;
    }

    int iVar5 = 0;
    int iVar1 = 0x20;
    unsigned char bVar10 = (unsigned char)(((prec > 8) ? 1 : 0) + 1);
    int ok_flag = (num_comps != 0);
    int alpha = ok_flag;

    unsigned char buf[0x400];
    if (prec < 9) {
        iVar5 = CheckUniformRun(num_comps, buf, (unsigned char*)cinfo + 0x28);
        if (iVar5 != 0) {
            bVar10 = 3;
            alpha = 0;
        }
    }
    if (cinfo[0x10b] != 0)          // +0x42c
        bVar10 |= 8;

    if (alpha) {
        if (cinfo[0x10f] == 5 && cinfo[0x110] == 5 && cinfo[0x111] == 5 &&
            data_prec < 2) {
            int k = 0;
            iVar1 = 0x10;
            if (num_comps > 0) {
                unsigned char* p = (unsigned char*)(cinfo + 0xa + cinfo[8]);
                do {
                    unsigned short uVar4 = 0xff;
                    if (data_prec != 0)
                        uVar4 = (unsigned short)(*p >> 7);
                    *(unsigned short*)(buf + k * 2) =
                        (unsigned short)((((unsigned short)(*p >> 3) | (uVar4 << 5)) << 5 |
                                          (unsigned short)(p[-1] >> 3)) << 5 |
                                         (unsigned short)(p[-2] >> 3));
                    ++k;
                    p += 4;
                } while (k < num_comps);
            }
        } else if (data_prec == 8) {
            int k = 0;
            iVar1 = 0x20;
            if (num_comps > 0) {
                unsigned char* p = (unsigned char*)(cinfo + 0xa + cinfo[8]);
                do {
                    buf[k * 4]     = p[-2];
                    buf[k * 4 + 1] = p[-1];
                    buf[k * 4 + 2] = p[0];
                    buf[k * 4 + 3] = p[1];
                    ++k;
                    p += 4;
                } while (k < num_comps);
            }
        } else {
            iVar1 = 0x18;
            if (num_comps > 0) {
                unsigned char* q = buf + 1;
                unsigned char* p = (unsigned char*)(cinfo + 0xa + cinfo[8]);
                int left = num_comps;
                do {
                    q[-1] = p[-2];
                    q[0]  = p[-1];
                    q[1]  = p[0];
                    p += 4;
                    q += 3;
                } while (--left != 0);
            }
        }
    }

    // build the 0x12-byte JPEG scan header in a local image of the retail frame
    unsigned char hdr[0x12];
    hdr[0]  = 0;
    hdr[1]  = (unsigned char)alpha;
    hdr[2]  = bVar10;
    *(unsigned short*)(hdr + 3) = (unsigned short)prec;
    *(unsigned short*)(hdr + 5) = (unsigned short)height;
    *(unsigned short*)(hdr + 7) = (unsigned short)width;
    *(unsigned short*)(hdr + 9) = (unsigned short)num_comps;
    hdr[0xb] = (unsigned char)iVar1;
    *(unsigned short*)(hdr + 0xc) = *(unsigned short*)((char*)cinfo + 0x450);
    *(unsigned short*)(hdr + 0xe) = (unsigned short)cinfo[8];
    *(unsigned short*)(hdr + 0x10) = (unsigned short)-(short)*(short*)((char*)cinfo + 0x454);

    int res = gwrite_s0084_faf0(*(void**)((char*)stream + 0x10), hdr, 0x12);
    int count = 0;

    if (res != 0 && iVar5 == 0) {
        int n = (iVar1 * num_comps + ((iVar1 * num_comps >> 0x1f) & 7)) >> 3;
        if (n != 0)
            res = gwrite_s0084_faf0(*(void**)((char*)stream + 0x10), buf, n);
    }

    void* mem = galloc(((prec * width + ((prec * width) >> 0x1f & 7)) >> 3) * 3 + 0x10);
    if (mem != 0) {
        count = 0;
        while (count < height) {
            bool stop = (res == 0);
            res = 0;
            if (stop)
                break;
            unsigned outSize = EmitSamples(mem, width, prec, 0, cinfo[0x10b],
                                           data_prec, buf);
            res = gwrite_s0084_faf0(*(void**)((char*)stream + 0x10), mem, (int)outSize);
            ++count;
        }
        gfree_s0084_faf0(mem);
    }
    (void)iVar1;
    return;
}
