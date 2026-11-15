// src/game/UTFSpore_Win32/_at_00910000.cpp -- migrated from slice(s) s0091f520, s0091d6b0, s0091b5d0, s0091a680, s00916960 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00910000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stddef.h>
#include <string.h>
#include "EA/IO/FileStream.h"
#include <intrin.h>
#include "EA/Dasm/DisassemblerX86.h"
#include "EA/Debug/ReportWriter.h"

// ---- items of slice s00916960 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SpriteList {
  unsigned int *mCur;    // +0x00
  unsigned int mUsed;    // +0x04
  unsigned int mMax;     // +0x08

  void Push(const unsigned int *item);   // 0x00917770
};
// ---- items of slice s00916960 end

// ---- items of slice s0091a680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gOne;                    // 0x01485720 (_HK_REAL_ONE)
extern const float gTwo;                    // 0x01470f1c (2.0f)
struct cWString {
    uint16_t* mpBegin;                  // +0x00
    uint16_t* mpCapacityEnd;            // +0x04
    uint16_t* mpEnd;                    // +0x08
    uint16_t* mpSSOBuffer;              // +0x0c
    void Assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
};
struct cLookupNode {
    cLookupNode* mpNext;                // +0x00
    cLookupNode* mpPrev;                // +0x04
    void* mpValue;                      // +0x08
};
struct cStrNode {
    cStrNode* mpNext;                   // +0x00
    cStrNode* mpPrev;                   // +0x04
    cWString mString;                   // +0x08
};
struct cStrList {
    cStrNode* mpListNext;               // +0x00 (sentinel head)
    cStrNode* mpListPrev;               // +0x04
    void DoClear();                     // 0x0091a750
};
struct cEntryFlags {
    union {
        struct {
            int      mKind   : 4;       // +0x40, bits 0..3
            int      mInfo   : 12;      // +0x40, bits 4..15
            uint32_t mUnused : 16;      // +0x42
        };
        struct {
            uint16_t mPadLow;           // +0x40
            uint16_t mExtra;            // +0x42
        };
    };
};
struct cAddressRepEntry {
    cWString mBlocks[4];                // +0x00..0x3f
    cEntryFlags mFlags;                 // +0x40
};
struct cHashNode {
    const void* mpKey;                  // +0x00
    cAddressRepEntry mValue;            // +0x04
    cHashNode* mpNext;                  // +0x48
    cHashNode(const void* const& pKey, const cAddressRepEntry& value);   // 0x0091a6d0
    void CopyFrom(const cHashNode* pSource);                            // 0x0091a620
};
struct cAddressRepLookupSet {
    bool mbEnableAutoDatabaseFind;      // +0x00
    bool mbLookedForDBFiles;            // +0x01
    uint8_t mPad02[2];                  // +0x02
    cLookupNode mListHead;              // +0x04 (sentinel)
    cStrList mSourceDirList;            // +0x10 (sentinel)
    uint32_t mPad18;                    // +0x18
    uint32_t mnSourceCodeFailureCount;  // +0x1c
    uint32_t mnSourceContextLineCount;  // +0x20
    void PushBack(void* pValue);                                        // 0x0091a680
    int  GetSymbolInfoTypeFromDatabase(const void* pDatabase);          // 0x0091a200
    bool AddDatabaseFile(const void* pDatabase, void* pA, void* pB, int bFlag); // 0x0091a7a0
    void AutoDatabaseAdd();                                             // 0x0091a8a0
    int  GetAddressRepSource(cAddressRepEntry* pEntry, int* pLine);      // 0x0091a970
    uint32_t GetAddressRepFromSet(uint32_t nFlags, const void* pAddress,
                                  cAddressRepEntry* pEntry, int* pLine); // 0x0091a490
    uint32_t GetAddressRep(uint32_t nFlags, const void* pAddress,
                           cAddressRepEntry* pEntry, int* pLine);        // 0x0091ae20
    void Shutdown();                                                    // 0x0091a430
};
struct cAddressRepCache {
    uint32_t mField00;                  // +0x00
    cHashNode** mpBucketArray;          // +0x04
    uint32_t mnBucketCount;             // +0x08
    uint32_t mnElementCount;            // +0x0c
    float mfMaxLoadFactor;              // +0x10
    float mfGrowthFactor;               // +0x14
    uint32_t mField18;                  // +0x18
    uint8_t mPad1C[4];                  // +0x1c
    cAddressRepLookupSet mLookupSet;    // +0x20
    cAddressRepCache();                                                 // 0x0091b2f0
    ~cAddressRepCache();                                                // 0x0091b090
    cAddressRepEntry* operator[](const void* const& pKey);              // 0x0091af40
    void DoFreeNodes(cHashNode** ppBuckets, uint32_t nBucketCount);     // 0x0091aeb0
    void DoInsert(void** ppIter, const cHashNode* pSource, uint32_t bFlag); // 0x0091ad30
    void DoRehash(uint32_t nBucketCount);                               // 0x0091a380
    void SetAddressRep(int nIndex, const void* const& pKey, const char* pText,
                       int nLen, int nValue);                           // 0x0091b000
    uint32_t GetAddressRep(uint32_t nMask, const void* const& pKey, int* pRep,
                           int* pLine, char bBuild);                    // 0x0091b0f0
};
// ---- items of slice s0091a680 end

// ---- items of slice s0091b5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int   __stdcall UnDecorateSymbolName(const char*, char*, unsigned, unsigned);
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
void  StrRangeInit(void* s, unsigned n);                    // 0x00475ab0
void  StrAppend(void* s, const char* b, const char* e);     // 0x00455d60
struct EStr {
    char* mpBegin;   // 0
    char* mpEnd;     // 4
    char* mpCap;     // 8
};
struct DisassemblerX86 {
    void* vftable;                       // 0x000
    void* Ctor2();                       // 0x0091b5d0
    void* Dasm(const u8* start, const u8* end, u32 u3, u32 u4); // 0x0091b6d0
    void  Dtor();                        // 0x0091b6b0
    int   Undecorate(char* out, const char* sym, u32 len, u32 flags); // 0x0091b840
    u8*   ScalarDtor(u8 flags);          // 0x0091b810
};
struct MapFile {
    u8    mOpened;          // 0x00
    u32   mKind;            // 0x04
    void* mpStream;         // 0x08
    void* mpStr0;           // 0x0c
    void* mpStr0End;        // 0x10
    void* mpStr0Cap;        // 0x14
    u8    mPad18[4];        // 0x18
    void* mpStr1;           // 0x1c
    void* mpStr1End;        // 0x20
    void* mpStr1Cap;        // 0x24
    u8    mPad28[0x10];     // 0x28
    u32   mBase38;          // 0x38
    u32   mBase3c;          // 0x3c
    u16   mStride;          // 0x4a
    u16   mCount;           // 0x4c
    u16   mSel;             // 0x4e

    u8    Open(void* source);                       // 0x0091bd40
    u8    ReadSymbolBytes(int idx, u8* dst);        // 0x0091bd70
    u8    Parse(u8* buf);                           // 0x0091bb00
    u8    ReadRecord(u8* dst);                      // 0x0091bc30
    u8*   FindByAddress(u8* dst, u32 addr);         // 0x0091bdd0
    u8    CompareName(const char* other, u8* scratch); // 0x0091bce0
    u8    Reset();                                  // 0x0091beb0
    void* CtorEmpty();                              // 0x0091c0a0
    void  FreeStringsA();                           // 0x0091c0c0
    void  FreeStringsB();                           // 0x0091c100
    void* StrStubInit(const char* b, const char* e); // 0x0091c2d0
    void* RbtreeValCtor(u32* key, const void* src);  // 0x0091c310
    void* ListPushString(const char* s);             // 0x0091c330
    void  ListClear();                               // 0x0091c380
};
// ---- items of slice s0091b5d0 end

// ---- items of slice s0091d6b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(strlen)
typedef void* HANDLE;
typedef int BOOL;
typedef unsigned long DWORD;
typedef const char* LPCSTR;
typedef unsigned __int64 DWORD64;
struct Context {
    char pad00[0xb8];
    void* Eip;                  // +0xb8
    char padbc[8];
    DWORD Esp;                  // +0xc4
};
struct ExceptionPointers {
    void* ExceptionRecord;      // +0
    Context* ContextRecord;     // +4
};
extern "C" __declspec(dllimport) DWORD __stdcall SymSetOptions(DWORD);
extern "C" __declspec(dllimport) BOOL  __stdcall SymInitialize(HANDLE, LPCSTR, BOOL);
extern "C" __declspec(dllimport) DWORD64 __stdcall SymLoadModule64(HANDLE, HANDLE, LPCSTR, LPCSTR, DWORD64, DWORD);
extern "C" __declspec(dllimport) BOOL  __stdcall SymCleanup(HANDLE);
extern "C" __declspec(dllimport) BOOL  __stdcall SymGetLineFromAddr64(HANDLE, DWORD64, DWORD*, void*);
extern "C" __declspec(dllimport) BOOL  __stdcall SymGetSymFromAddr64(HANDLE, DWORD64, DWORD64*, void*);
extern "C" __declspec(dllimport) BOOL  __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateEventA(void*, BOOL, BOOL, LPCSTR);
void EA_Text_StrncpyUTF8ToUTF16(void* dst, unsigned n, const void* src, int len); // 0x93cf10
unsigned __int64 FUN_0091a1d0();                     // 0x91a1d0
void* FUN_00932060(const void* name);                // 0x932060
void  FUN_00943570(void* p);                         // 0x943570
struct ReportWriter {
    virtual void r00();
    virtual void r01(void* dst, int n);        // +0x04
    virtual bool r02(const char* path);        // +0x08
    virtual void r03();                        // +0x0c
    virtual void r04(const char* section);     // +0x10
    virtual void r05();                        // +0x14
    virtual void r06(const char* section);     // +0x18
    virtual void r07(const char* section);     // +0x1c
    virtual void r08(const char* text, int v); // +0x20
    virtual void r09();                        // +0x24
    virtual void r10(const char* name, const char* value); // +0x28
virtual void r11();
virtual void r12();
virtual void r13();
    virtual int  r14();                        // +0x38

    // out-of-line members
    void WriteCallStack(Context* ctx);                         // 0x91fca0
    void WriteStackMemoryView(DWORD esp, unsigned n);          // 0x91fe60
    void WriteDisassembly(void* start, unsigned n, void* eip); // 0x91f400
    void WriteSystemInfo();                                    // 0x91ef30
    void WriteApplicationInfo();                               // 0x91f300
    void WriteRegisterValues(Context* ctx);                    // 0x91fa10
    void WriteModuleList();                                    // 0x91f7c0
    void WriteRegisterMemoryView(Context* ctx);                // 0x91fbd0
    int  GetTimeString(char* buf, unsigned n, void* tm);       // 0x91eca0
    int  GetDateString(char* buf, unsigned n, void* tm);       // 0x91ecf0
    int  GetAddressLocationString(void* addr, char* buf, unsigned n); // 0x91ee80
    void Construct();        // 0x91e970
    void Destroy();          // 0x91fe40

    char mPath[256];       // +0x04
    void* mpFile;          // +0x104
    char mBuffer[1024];    // +0x108
    int mnSectionDepth;    // +0x508
};
struct HandlerNode { HandlerNode* mpNext; HandlerNode* mpPrev; void* mClient; };
struct FixedVectorPtr {
    ReportWriter** mpBegin;      // +0
    ReportWriter** mpEnd;        // +4
    ReportWriter** mpCapacity;   // +8
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct ExceptionHandler {
    void* mpPlatformHandler;   // +0x00
    FixedVectorPtr mReportWriters; // +0x04
    char pad10[0x20];          // +0x10 .. +0x2f
    HandlerNode mNode;         // +0x30
    char* mpBuildDescEnd;      // +0x3c
    char pad40[0x0c];          // +0x40 .. +0x4b
    wchar_t mDir[255];         // +0x4c
    void NotifyClients(int action);          // @ 0091e3b0
    void SetReportDirectory(wchar_t* dir);   // @ 0091e040
};
struct ExceptionHandlerWin32 {
    ExceptionHandler* mpOwner;          // +0x00
    ReportWriter* mpReportWriter;       // +0x04
    bool mbEnabled;                     // +0x08
    char pad09[3];
    int mAction;                        // +0x0c
    int mnTerminateReturnValue;         // +0x10
    int mReportFieldMask;               // +0x14
    ExceptionPointers* mpExceptionPointers; // +0x18
    unsigned mpExceptionAddress;        // +0x1c
    void* mPreviousFilter;              // +0x20
    char mTime[0x24];                   // +0x24
    char mBaseReportName[0x40];         // +0x48

    void WriteHeader();                                       // @ 0091e250
    void WriteCallStack();                                    // @ 0091df70
    void WriteMiniDump();                                     // @ 0091e190
    void WriteExtraData();                                    // @ 0091e3e0
    void WriteExceptionReportInternal(ReportWriter* w);       // @ 0091e4b0
    int  GetReportFilePath(char* buf, unsigned n, int type);  // @ 0091e080
    void WriteExceptionReport();                              // @ 0091e5c0
    unsigned GetAddressInfo(unsigned char flags, unsigned long long addr, unsigned* out); // 0x0091d830
    int GetExceptionString(char* buf, unsigned n);            // 0x0091d950
};
struct SymbolEngine {
    virtual void s0();
    void* mHandle;       // +0x04
    unsigned mLo;        // +0x08
    unsigned mHi;        // +0x0c
    bool Load(const char* path, unsigned extra);  // @ 0091d6b0
    bool Cleanup();                               // @ 0091d760
    SymbolEngine();                               // @ 0091d7a0
    virtual ~SymbolEngine();                      // @ 0091d7d0
};
extern "C" __declspec(dllimport) size_t __cdecl strlen(const char*);
// ---- items of slice s0091d6b0 end

// ---- items of slice s0091f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void  __stdcall GetSystemTime(void*);
extern "C" __declspec(dllimport) int   __stdcall SystemTimeToFileTime(const void*, void*);
extern "C" __declspec(dllimport) __int64 __cdecl _mktime64(void*);
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
#pragma intrinsic(__readfsdword)
typedef unsigned short WORD;
struct tm_s0091_f520 {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;
};
struct SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
};
struct FILETIME { DWORD dwLowDateTime, dwHighDateTime; };
// ---- items of slice s0091f520 end

// @ 0x00917600
unsigned int LerpColor(unsigned int a, unsigned int b, float t)
{
  unsigned int a0 = a & 0xFF, a1 = (a >> 8) & 0xFF, a2 = (a >> 16) & 0xFF, a3 = (a >> 24) & 0xFF;
  unsigned int b0 = b & 0xFF, b1 = (b >> 8) & 0xFF, b2 = (b >> 16) & 0xFF, b3 = (b >> 24) & 0xFF;
  unsigned int r0 = (unsigned int)(int)((float)(int)(b0 - a0) * t) + a0;
  unsigned int r1 = (unsigned int)(int)((float)(int)(b1 - a1) * t) + a1;
  unsigned int r2 = (unsigned int)(int)((float)(int)(b2 - a2) * t) + a2;
  unsigned int r3 = (unsigned int)(int)((float)(int)(b3 - a3) * t) + a3;
  return (r0 & 0xFF) | ((r1 & 0xFF) << 8) | ((r2 & 0xFF) << 16) | (r3 << 24);
}

// @ 0x009176c0
float *LerpSpriteRect(float *out, float *a, float *b, float t)
{
  out[0] = (b[0] - a[0]) * t + a[0];
  out[1] = (b[1] - a[1]) * t + a[1];
  out[2] = (float)LerpColor(*(unsigned int *)&a[2], *(unsigned int *)&b[2], t);
  out[3] = (b[3] - a[3]) * t + a[3];
  out[4] = (b[4] - a[4]) * t + a[4];
  return out;
}

// @ 0x00917770
void SpriteList::Push(const unsigned int *item)
{
  if (mUsed < mMax) {
    unsigned int *dst = mCur;
    dst[0] = item[0];
    dst[1] = item[1];
    dst[2] = item[2];
    dst[3] = item[3];
    dst[4] = item[4];
    mCur += 5;
  }
  mUsed += 1;
}

// @ 0x0091b2f0
cAddressRepCache::cAddressRepCache()
: mfMaxLoadFactor(gOne)
    , mfGrowthFactor(gTwo)
{
    mpBucketArray = (cHashNode**)0x0154df28;
    mnElementCount = 0;
    mField18 = 0;
    mnBucketCount = 1;
    mLookupSet.mbEnableAutoDatabaseFind = true;
    mLookupSet.mbLookedForDBFiles = false;
    mLookupSet.mListHead.mpNext = &mLookupSet.mListHead;
    mLookupSet.mListHead.mpPrev = &mLookupSet.mListHead;
    mLookupSet.mSourceDirList.mpListNext = (cStrNode*)&mLookupSet.mSourceDirList;
    mLookupSet.mSourceDirList.mpListPrev = (cStrNode*)&mLookupSet.mSourceDirList;
    mLookupSet.mnSourceCodeFailureCount = 0;
    mLookupSet.mnSourceContextLineCount = 8;
}

// @ 0x0091b840
int DisassemblerX86::Undecorate(char* out, const char* sym, u32 bufLen, u32 flags)
{
    *out = 0;
    if (flags == 1) {
        if (UnDecorateSymbolName(sym, out, 0x2e0, bufLen) == 0)
            *out = 0;
    }
    char* p = out;
    char* start = out;
    do {
        ++p;
    } while (p[-1] != 0);
    return (int)(p - (start + 1));
}

// @ 0x0091ba90
EStr* StrConcat3(EStr* out, const char* mid, EStr* pre, const char* suffix)
{
    const char* e = suffix;
    do {
        ++e;
    } while (e[-1] != 0);
    u32 nSuffix = (u32)(e - suffix) - 1;
    u32 nPre = (u32)(pre->mpEnd - pre->mpBegin);
    u32 nMid = (u32)(e - (const char*)mid) - 1;
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCap = 0;
    StrRangeInit(out, nMid + nPre + 1);
    *out->mpEnd = 0;
    StrAppend(out, pre->mpBegin, pre->mpEnd);
    StrAppend(out, mid, (char*)mid + nMid);
    return out;
}

// @ 0x0091bb00
u8 MapFile::Parse(u8* buf)
{
    void* stream = mpStream;
    void** vtbl = *(void***)stream;
    if (((u8 (__thiscall*)(void*, int, int))vtbl[0x28 / 4])(stream, 0, 0) == 0)
        return 0;
    if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, buf, 0x10) != 0x10)
        return 0;
    if (!(buf[0] == 0x7f && buf[1] == 0x45 && buf[2] == 0x4c && buf[3] == 0x46))
        return 0;
    u32 kind = buf[4];
    mKind = kind;
    if (kind == 1) {
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, buf, 0x24) != 0x24)
            return 0;
    } else if (kind == 2) {
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, buf + 0x10, 0x30) != 0x30)
            return 0;
    } else {
        return 0;
    }
    return 1;
}

// @ 0x0091bc30
u8 MapFile::ReadRecord(u8* dst)
{
    if (mOpened == 0)
        return 0;
    if (mKind == 1) {
        void* stream = mpStream;
        void** vtbl = *(void***)stream;
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, dst, 0x40) != 0x40)
            return 0;
        return 1;
    }
    if (mKind == 2) {
        void* stream = mpStream;
        void** vtbl = *(void***)stream;
        u8 tmp[0x28];
        if (((u32 (__thiscall*)(void*, u8*, u32))vtbl[0x30 / 4])(stream, tmp, 0x28) != 0x28)
            return 0;
        *(u32*)(dst + 0x00) = *(u32*)(tmp + 0x00);
        *(u32*)(dst + 0x04) = *(u32*)(tmp + 0x04);
        *(u32*)(dst + 0x08) = *(u32*)(tmp + 0x08);
        *(u32*)(dst + 0x0c) = 0;
        *(u32*)(dst + 0x10) = *(u32*)(tmp + 0x0c);
        *(u32*)(dst + 0x14) = 0;
        *(u32*)(dst + 0x18) = *(u32*)(tmp + 0x10);
        *(u32*)(dst + 0x1c) = 0;
        *(u32*)(dst + 0x20) = *(u32*)(tmp + 0x14);
        *(u32*)(dst + 0x24) = 0;
        *(u32*)(dst + 0x28) = *(u32*)(tmp + 0x18);
        *(u32*)(dst + 0x2c) = *(u32*)(tmp + 0x1c);
        *(u32*)(dst + 0x30) = *(u32*)(tmp + 0x20);
        *(u32*)(dst + 0x34) = 0;
        *(u32*)(dst + 0x38) = *(u32*)(tmp + 0x24);
        *(u32*)(dst + 0x3c) = 0;
        return 1;
    }
    return 0;
}

// @ 0x0091bce0
u8 MapFile::CompareName(const char* other, u8* scratch)
{
    void* stream = mpStream;
    void** vtbl = *(void***)stream;
    ((u32 (__thiscall*)(void*, u8*, int))vtbl[0x30 / 4])(stream, scratch, 1);
    u8 c = *scratch;
    const char* p = other;
    if (c != 0) {
        if (*p == 0)
            goto done;
        if (c != *p)
            return 0;
        for (;;) {
            stream = mpStream;
            vtbl = *(void***)stream;
            ((u32 (__thiscall*)(void*, u8*, int))vtbl[0x30 / 4])(stream, scratch, 1);
            c = *scratch;
            ++p;
            if (c == 0)
                break;
            if (c != *p)
                return 0;
        }
    }
done:
    if (c == *p)
        return 1;
    return 0;
}

// @ 0x0091bd40
u8 MapFile::Open(void* source)
{
    if (mOpened == 0) {
        mpStream = source;
        mOpened = Parse((u8*)this + 0x10);
    }
    return mOpened;
}

// @ 0x0091bd70
u8 MapFile::ReadSymbolBytes(int idx, u8* dst)
{
    int count = 0;
    if (mOpened != 0 && (mBase38 | mBase3c) != 0 && mStride != 0)
        count = mCount;
    if (idx >= count)
        return 0;
    u8* cur = (u8*)(mBase38 + mStride * idx);
    void* stream = mpStream;
    void** vtbl = *(void***)stream;
    if (((u8 (__thiscall*)(void*, u8*, int))vtbl[0x28 / 4])(stream, cur, 0) == 0)
        return 0;
    return ReadRecord(dst);
}

// @ 0x0091bdd0
u8* MapFile::FindByAddress(u8* dst, u32 addr)
{
    if (mOpened == 0)
        return 0;
    u32 sel = mSel;
    u32 idx;
    u8 vb;
    if (sel < 0xff00) {
        idx = sel;
    } else if (sel == 0xffff) {
        if (!ReadSymbolBytes(0, dst))
            return 0;
        idx = *(u32*)(dst + 0x28);
    } else {
        return 0;
    }
    u8 rec[0x40];
    if (!ReadSymbolBytes(idx, rec))
        return 0;
    if (*(u32*)(rec + 4) == 8)
        return 0;
    u32 count = 0;
    if (mOpened != 0 && (mBase38 | mBase3c) != 0 && mStride != 0)
        count = mCount;
    for (int i = 0; i < (int)count; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!ReadSymbolBytes(i + j, dst))
                continue;
            u32 a = *(u32*)dst + *(u32*)(rec + 0x10);
            void* stream = mpStream;
            void** vtbl = *(void***)stream;
            if (((u8 (__thiscall*)(void*, u32, int))vtbl[0x28 / 4])(stream, a, 0) == 0)
                continue;
            if (CompareName((const char*)addr, &vb) != 0)
                return dst;
        }
    }
    return 0;
}

// @ 0x0091d6b0
bool SymbolEngine::Load(const char* path, unsigned)
{
    char buf[0x104];
    EA_Text_StrncpyUTF8ToUTF16(buf, 0x104, path, -1);
    if ((mLo | mHi) == 0) {
        unsigned __int64 h = FUN_0091a1d0();
        mLo = (unsigned)h;
        mHi = (unsigned)(h >> 32);
    }
    void* mod = FUN_00932060(path);
    SymSetOptions(0x52);
    SymInitialize(mHandle, 0, 0);
    unsigned __int64 r = SymLoadModule64(mHandle, 0, buf, 0, ((unsigned __int64)mHi << 32) | mLo, (DWORD)mod);
    mLo = (unsigned)r;
    mHi = (unsigned)(r >> 32);
    if ((mLo | mHi) != 0)
        return true;
    return false;
}

// @ 0x0091d760
bool SymbolEngine::Cleanup()
{
    if (mHandle != 0) {
        SymCleanup(mHandle);
        CloseHandle(mHandle);
        mHandle = 0;
        mLo = 0;
        mHi = 0;
    }
    return true;
}

// @ 0x0091d7a0
SymbolEngine::SymbolEngine()
{
    mHandle = 0;
    mLo = 0;
    mHi = 0;
    mHandle = CreateEventA(0, 0, 0, 0);
}

// @ 0x0091d7d0
SymbolEngine::~SymbolEngine()
{
    *(void**)this = (void*)0x0143cf5c;
    if (mHandle != 0) {
        SymCleanup(mHandle);
        CloseHandle(mHandle);
        mHandle = 0;
        mLo = 0;
        mHi = 0;
    }
    *(void**)this = (void*)0x013f68c4;
}

// @ 0x0091d830
unsigned ExceptionHandlerWin32::GetAddressInfo(unsigned char flags, unsigned long long addr, unsigned* out)
{
    unsigned result = 0;
    if (flags & 1) {
        char line[0x18 + 0x40];
        *(unsigned*)line = 0x18;
        if (SymGetLineFromAddr64(0, addr, 0, line)) {
            FUN_00943570(*(void**)(line + 0x10));
            *out = *(unsigned*)(line + 0x14);
            result = 1;
        }
    }
    if (flags & 2) {
        char sym[0x800 + 0x20];
        *(unsigned*)sym = 0x20;
        *(unsigned*)(sym + 0x18) = 0x800;
        if (SymGetSymFromAddr64(0, addr, 0, sym)) {
            out[1] = *(unsigned*)(sym + 0x38);
            result |= 2;
        }
    }
    return result;
}

// @ 0x0091ff50
void GetUptime(unsigned* out)
{
    tm_s0091_f520 t;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_yday = 0;
    t.tm_isdst = 0;
    t.tm_mon = 0;
    t.tm_year = 0x69;
    t.tm_mday = 1;
    t.tm_wday = 6;
    __int64 a = _mktime64(&t);
    __int64 b = _time64(0);
    *out = (unsigned)((int)b - (int)a) & 0x7fffffff;
}

// @ 0x0091ffd0
void GetTickCount100ns(uint32_t* out)
{
    SYSTEMTIME now;
    FILETIME nowFt, epochFt;
    GetSystemTime(&now);
    SYSTEMTIME epoch;
    epoch.wYear = 0x7d5;
    epoch.wMonth = 1;
    epoch.wDayOfWeek = 6;
    epoch.wDay = 1;
    epoch.wHour = 0;
    epoch.wMinute = 0;
    epoch.wSecond = 0;
    epoch.wMilliseconds = 0;
    SystemTimeToFileTime(&now, &nowFt);
    SystemTimeToFileTime(&epoch, &epochFt);
    __int64 diff = *(__int64*)&nowFt - *(__int64*)&epochFt;
    diff = diff / 10;
    out[1] = (uint32_t)(diff >> 32) & 0x0fffffff;
    out[0] = (uint32_t)diff;
}
