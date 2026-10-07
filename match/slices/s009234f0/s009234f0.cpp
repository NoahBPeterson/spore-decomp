// Slice s009234f0 (bfs4 #16), 32-bit MSVC 2008.
// EA::Trace::Server / LogReporter / LogFilterGroupLevels / LogFormatterSimple/Fancy.
// Class layouts taken from the 2008 dev-build PDB, offsets confirmed against the disassembly.
#include "types.h"
#include <intrin.h>
#include <new>

typedef unsigned int size_t;
extern "C" size_t strlen(const char*);

extern "C" char DAT_01667bac;
extern unsigned g_timeoutP;

// ---------------------------------------------------------------------------
// EA::Thread::Mutex
// ---------------------------------------------------------------------------
namespace EA { namespace Thread {
struct Mutex {
    unsigned __int64 mData[4];  // +0
    int  mnLockCount;           // +0x20
    bool mbIntraProcess;        // +0x24
    void* mThreadId;            // +0x28
    void Lock(unsigned* pTimeout);
    int  Unlock();
    Mutex() {}
    Mutex(int name, int intraProcess);
};
}}

// ---------------------------------------------------------------------------
// eastl / CRT helpers
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
extern "C" {
void  EA_operator_delete(void* p);                                   // 0xf47380
void* EA_operator_new(unsigned size, const char* name, int f1, int f2, int f3, int f4); // 0xf473a0
void* EA_GetDefaultAllocator();                                      // 0x925cb0
int   Vsnprintf8(char* buf, size_t n, const char* fmt, void* ap);    // 0x938400
}
void EA_DisplayTraceDialog(const char* title, void* msg);            // 0x925100
struct EaStringInit {
    void FUN_0057cc10(const char* s);   // 0x57cc10 (basic_string(const char*) init)
};
struct VaString {
    void FUN_0091a530(const char* fmt, char* ap);   // 0x91a530 (string append_sprintf_va_list)
};
struct SimpleStringOps { void assign(const char* first, const char* last); }; // 0x942e50
struct FancyStringOps {
    void assign(const char* first, const char* last);   // 0x60a150
};
struct Stopwatch {
    void* Stopwatch_ctor(int units, int start);   // 0x93a560 (EA::Stopwatch::Stopwatch, thiscall)
};

// eastl free helpers
void* eastl_RBTreeIncrement(void* node);                             // 0x921580 (returns node)
void eastl_RBTreeErase(void* z, void* anchor);                       // 0x921880
void eastl_RBTreeInsert(void* node, void* parent, void* anchor, int color); // 0x9216a0
void* eastl_RBTreeDecrement(void* node);                             // 0x9215c0
void eastl_RBTreeErase_Insert(void* a, void* b, void* c, void* d);   // placeholder
void eastl_copy_impl(void* first, void* last, void* dest);           // 0x6782c0
struct EaStringOps { void assign(const char* first, const char* last); };       // 0x454cb0

// ---------------------------------------------------------------------------
// interfaces (only used so the concrete classes get vtables)
// ---------------------------------------------------------------------------
namespace EA { namespace Trace {

struct IUnknown32 {
    virtual ~IUnknown32() {}
    virtual void AddRef() {}
    virtual void Release() {}
    virtual void QueryInterface() {}
};

struct ILogFilter : IUnknown32 {
    virtual void f2() {}
    virtual void f3() {}
    virtual int  IsFiltered(void* rec) { (void)rec; return 0; }  // +0x14
};

struct ILogFormatter : IUnknown32 {
    virtual void f2() {}
    virtual void f3() {}
    virtual void f4() {}
    virtual void f5() {}
    virtual void f6() {}
};

struct ILogReporter : IUnknown32 {
    virtual void r2() {}
    virtual void r3() {}
    virtual void r4() {}
    virtual void r5() {}
    virtual const char* GetName() { return 0; }   // +0x1c
};

struct ILogFilterForward;
struct ILogFormatterForward;

// AutoRefCount<T>: single pointer
template <class T> struct AutoRefCount {
    T* mpObject;   // +0
};

// ---------------------------------------------------------------------------
// eastl::basic_string<char,eastl::allocator> — 16 bytes (ptr, ptr-cap, ptr-end)
// ---------------------------------------------------------------------------
struct EaString {
    char* mpBegin;     // +0
    char* mpEnd;       // +4
    char* mpCapacity;  // +8
    void* mAllocator;  // +0xc
};
// ---------------------------------------------------------------------------
// eastl fixed_string backing store (2048 / 512) used by the formatters
// ---------------------------------------------------------------------------
struct FixedString512 {
    char* mpBegin;     // +0
    char* mpEnd;       // +4
    char* mpCapacity;  // +8
    void* mpAlloc;     // +0xc
    void* mpPool;      // +0x10
    char buffer[512];  // +0x14
};
struct FixedString2048 {
    char* mpBegin;     // +0
    char* mpEnd;       // +4
    char* mpCapacity;  // +8
    void* mpAlloc;     // +0xc
    void* mpPool;      // +0x10
    char buffer[2048]; // +0x14
};

// ---------------------------------------------------------------------------
// rbtree node + map
// ---------------------------------------------------------------------------
struct RBNodeBase {
    RBNodeBase* mpLeft;    // +0
    RBNodeBase* mpRight;   // +4
    RBNodeBase* mpParent;  // +8
    char mColor;           // +0xc
};
struct RBNode {
    RBNode* mpLeft;        // +0
    RBNode* mpRight;       // +4
    RBNode* mpParent;      // +8
    char mColor;           // +0xc
    char pad[3];
    const char* mpKey;     // +0x10
    int mnValue;           // +0x14
};
// map layout: +0 pool, +4 anchor(left,right,parent,color), +0x14 size, +0x18 allocator, +0x1c flags
struct RBTreeMap {
    void* mpPool;          // +0
    RBNodeBase mAnchor;    // +4
    int mnSize;            // +0x14
    void* mpAllocator;     // +0x18
    void* mpAllocator2;    // +0x1c

    void  DeallocNode(RBNode* node);
    void  DoNukeSubtree(RBNode* node);
    RBNode** find(RBNode** out, const char** key);
    RBNode** erase(RBNode** outNext, RBNode* pos);
    void  DoInsertValueImpl(RBNode** out, RBNode* parent, const void* value, char hasParent);
    void  DoInsertValue(RBNode** out, const void* value);
};

// ---------------------------------------------------------------------------
// LogReporter
// ---------------------------------------------------------------------------
struct LogReporter : ILogReporter {
    AutoRefCount<ILogFilter>    mFilter;    // +4
    AutoRefCount<ILogFormatter> mFormatter; // +8
    bool mIsEnabled;                        // +0xc
    char pad0[3];
    int  mnRefCount;                        // +0x10
    EaString mName;                         // +0x14

    LogReporter(const char* name);
    virtual ~LogReporter();
    void SetName(const char* name);

    int  FilterEnabled(void* rec);          // @ 0x923700
    int  FilterEnabled2(void* rec);         // @ 0x923740
    void ShowAlert(void* rec);              // @ 0x923a60
    int  DebugPrint(void* rec);             // @ 0x923aa0
    int  SkipFilter1(void* rec);            // @ 0x924270
    int  SkipFilter2(void* rec);            // @ 0x9242b0
    int  SkipFilter3(void* rec);            // @ 0x924350
    int  SkipFilter4(void* rec);            // @ 0x924390
    void* ScalarDeletingDtor(char flags);   // @ 0x9242f0
};

// ---------------------------------------------------------------------------
// LogFilterGroupLevels
// ---------------------------------------------------------------------------
struct LogFilterGroupLevels : ILogFilter {
    int      mnRefCount;     // +4
    EaString mName;          // +8
    int      mGlobalLevel;   // +0x18
    RBTreeMap mGroupLevelMap;// +0x1c

    LogFilterGroupLevels(void* cfg);
    virtual ~LogFilterGroupLevels();
    void SetName(const char* name);
    bool RemoveGroupLevel(const char* name);
    bool IsFiltered2(void* rec);
};

struct LogRecordFwd { int pad0[4]; };

// ---------------------------------------------------------------------------
// LogFormatterSimple / LogFormatterFancy
// ---------------------------------------------------------------------------
struct LogFormatterSimple : ILogFormatter {
    int  mnRefCount;             // +4
    FixedString2048 mName;       // +0x8  (0x814 bytes)
    FixedString2048 mLine;       // +0x81c

    LogFormatterSimple(const char* name);
    virtual ~LogFormatterSimple();
    void SetName(const char* name);
    void* Clone();
};

struct LogFormatterFancy : ILogFormatter {
    int  mnRefCount;             // +4
    FixedString512 mName;        // +0x8
    unsigned short mnFlags;      // +0x21c
    char pad0[2];
    int  mnFileInfoLevel;        // +0x220
    char pad1[4];
    char mTimer[0x18];           // +0x228 Stopwatch
    FixedString2048 mLine;       // +0x240

    LogFormatterFancy(const char* name);
    virtual ~LogFormatterFancy();
    void SetName(const char* name);
};

// ---------------------------------------------------------------------------
// Server
// ---------------------------------------------------------------------------
struct IServer {
    virtual void AddRef() {}
    virtual int  Release() { return 0; }
    virtual void QueryInterface() {}
    virtual void s3() {}
    virtual void s4() {}
    virtual void s5() {}
    virtual void s6() {}
    virtual void s7() {}
    virtual void s8() {}
    virtual void s9() {}
    virtual void s10() {}
    virtual void s11() {}
    virtual void s12() {}
    virtual void s13() {}
    virtual void s14() {}
    virtual void s15() {}
    virtual void s16() {}
    virtual void s17() {}
    virtual void s18() {}
    virtual void s19() {}
    virtual void s20() {}
};

struct ITracer {
    virtual void t0() {}
    virtual void t1() {}
    virtual void t2() {}
    virtual void t3() {}
    virtual void t4() {}
    virtual void t5() {}
    virtual void t6() {}
    virtual void t7() {}
    virtual void t8() {}
    virtual void t9() {}
};

struct Server : IServer, ITracer {
    bool mbIsReporting;      // +0x8
    char pad0[3];
    char* mpHeapBuffer;      // +0xc
    int   mnHeapBufferSize;  // +0x10
    int   mLogRecordCounter; // +0x14
    void* mpVecBegin;        // +0x18
    void* mpVecEnd;          // +0x1c
    void* mpVecCapacity;     // +0x20
    char pad1[4];
    void* mDefaultFilter;    // +0x28
    void* mDefaultFormatter; // +0x2c
    int   mUnknown30;        // +0x30
    int   mnRefCount;        // +0x34
    EA::Thread::Mutex mMutex;// +0x38

    Server();
    ~Server();
    const char* GetLevelName(int level);
    Server* AsInterface(int id);
    int Release();
    bool GetLogReporter(char* name, int* out);
    unsigned EnumerateLogReporters(void** out, unsigned max);
    bool RemoveLogReporter(ILogReporter* p);
};

}} // namespace EA::Trace

using namespace EA::Trace;

// ===========================================================================
// implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// ITracer subobject view of Server (Server + 4): TraceVaList / Trace are ITracer-side members, so
// `this` in the original is Server+4 and the Server itself is `this - 4` (see lea ecx,[esi-4]).
// ---------------------------------------------------------------------------
namespace EA { namespace Trace {

struct IReporterView {
    virtual void a0() = 0;
    virtual void a1() = 0;
    virtual void a2() = 0;
    virtual void a3() = 0;
    virtual bool Skips(void* rec) = 0;              // +0x10
    virtual bool IsFiltered(void* rec) = 0;         // +0x14
    virtual unsigned Report(void* rec) = 0;         // +0x18
};

struct TraceRecord {                                 // 0x18 bytes, vtable 0x143dc7c
    virtual void rv0() {}
    int         mnZero;                              // +4
    int         mnCounter;                           // +8
    void*       mpSender;                            // +0xc
    const char* mpMessage;                           // +0x10
    const char* mpLevelName;                         // +0x14
};

struct ServerTracer {
    virtual void t0() = 0;
    virtual void t1() = 0;
    virtual void t2() = 0;
    virtual void t3() = 0;
    virtual unsigned TraceString(void* sender, const char* msg) = 0;   // +0x10
    bool  mbIsReporting;           // +4
    char  pad5[3];
    char* mpHeapBuffer;            // +8
    int   mnHeapBufferSize;        // +0xc
    int   mLogRecordCounter;       // +0x10
    IReporterView** mpReportersBegin;   // +0x14
    IReporterView** mpReportersEnd;     // +0x18
    IReporterView** mpReportersCap;     // +0x1c
    char  pad6[4];                      // +0x20
    void* mDefaultFilter;               // +0x24
    void* mDefaultFormatter;            // +0x28
    int   mUnknown2c;                   // +0x2c
    int   mnRefCount;                   // +0x30
    char  mMutex[0x2c];                 // +0x34 EA::Thread::Mutex (raw: its 8-byte alignment would pad the vfptr)
    EA::Thread::Mutex* M() { return (EA::Thread::Mutex*)mMutex; }

    unsigned TraceVaList(void* sender, const char* fmt, void* ap);     // @ 0x9234f0
    unsigned Trace(void* sender, const char* msg);                     // @ 0x923990
    bool IsFiltered(void* rec);                                        // @ 0x923930 (Server::IsFiltered, ITracer side)
};

}} // namespace EA::Trace

// @ 0x009234F0  (ITracer::TraceVaList)
unsigned ServerTracer::TraceVaList(void* sender, const char* fmt, void* ap)
{
    char buf[256];
    if (fmt == 0) {
        return 0;
    }
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)((char*)this + 0x34);
    m->Lock((unsigned*)&g_timeoutP);
    if (mbIsReporting) {
        m->Unlock();
        return 0;
    }
    unsigned r;
    int n = Vsnprintf8(buf, 0x100, fmt, ap);
    buf[255] = 0;
    if (n >= -1) {
        if (n >= 0) {
            if (n < 0x100) {
                r = TraceString(sender, buf);
                goto done;
            }
            int sz = mnHeapBufferSize;
            if (sz <= n) {
                if (sz < n) {
                    do {
                        sz = mnHeapBufferSize * 2;
                        mnHeapBufferSize = sz;
                    } while (sz < n);
                }
                EA_operator_delete(mpHeapBuffer);
                mpHeapBuffer = (char*)EA_operator_new((unsigned)mnHeapBufferSize, "EATrace/Server/HeapBuffer/char[]", 0, 0, 0, 0);
            }
        }
        n = Vsnprintf8(mpHeapBuffer, (size_t)mnHeapBufferSize, fmt, ap);
        mpHeapBuffer[mnHeapBufferSize - 1] = 0;
        if (n >= -1) {
            r = TraceString(sender, mpHeapBuffer);
            goto done;
        }
    }
    r = 0;
done:
    m->Unlock();
    return r;
}

// @ 0x00923990  (ITracer::Trace)
unsigned ServerTracer::Trace(void* sender, const char* msg)
{
    unsigned flags = 0;
    if (msg != 0) {
        EA::Thread::Mutex* m = (EA::Thread::Mutex*)((char*)this + 0x34);
        m->Lock((unsigned*)&g_timeoutP);
        if (!mbIsReporting) {
            TraceRecord rec;
            rec.mnCounter = mLogRecordCounter++;
            mbIsReporting = true;
            rec.mpSender = sender;
            rec.mnZero = 0;
            rec.mpMessage = msg;
            rec.mpLevelName = ((Server*)((char*)this - 4))->GetLevelName(*(int*)((char*)sender + 0xc));
            IReporterView** p = mpReportersBegin;
            IReporterView** end = mpReportersEnd;
            for (; p != end; ++p) {
                IReporterView* rep = *p;
                if (!rep->Skips(&rec)) {
                    flags |= rep->Report(&rec);
                }
            }
            mbIsReporting = false;
        }
        m->Unlock();
    }
    return flags;
}

// @ 0x00923630
const char* Server::GetLevelName(int level)
{
    if (level <= 0xa)  return "Private";
    if (level <= 0x19) return "Debug";
    if (level <= 0x32) return "Info";
    if (level <= 0x64) return "Warn";
    if (level <= 0x96) return "Error";
    return "Fatal";
}

// @ 0x00923680
Server* Server::AsInterface(int id)
{
    Server* self = this;
    if (id == 0x23ab34a1)
        return self;
    if (id != 0x6c7ca8e4)
        return (id == (int)0xee3f516e) ? self : 0;
    if (self)
        return (Server*)((char*)self + 4);
    return 0;
}

// @ 0x009236D0
int Server::Release()
{
    int n = _InterlockedExchangeAdd((volatile long*)&mnRefCount, -1);
    --n;
    if (n == 0) {
        _InterlockedExchange((volatile long*)&mnRefCount, 1);
        if (this)
            ((void(__thiscall*)(void*, int))(*(void***)this)[2])(this, 1);
        return 0;
    }
    return n;
}

// @ 0x00923700
int LogReporter::FilterEnabled(void* rec)
{
    LogReporter* self = this;
    if (self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool r = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[5])(self->mFilter.mpObject, rec);
        if (!r)
            return 0;
    }
    return 1;
}

// @ 0x00923740
int LogReporter::FilterEnabled2(void* rec)
{
    LogReporter* self = this;
    if (self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool r = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[4])(self->mFilter.mpObject, rec);
        if (!r)
            return 0;
    }
    return 1;
}

// @ 0x00923A60
void LogReporter::ShowAlert(void* rec)
{
    void* fmt = ((void*(__thiscall*)(void*, void*))(*(void***)mFormatter.mpObject)[4])(mFormatter.mpObject, rec);
    const char* name = ((const char*(__thiscall*)(void*))(*(void***)rec)[2])(rec);
    if (name == 0)
        name = "Alert";
    EA_DisplayTraceDialog(name, fmt);
}

// @ 0x00923AA0
int LogReporter::DebugPrint(void* rec)
{
    const char* s = ((const char*(__thiscall*)(void*, void*))(*(void***)mFormatter.mpObject)[4])(mFormatter.mpObject, rec);
    OutputDebugStringA(s);
    return 0;
}

// @ 0x00923D40
Server::Server()
{
    mbIsReporting = 0;
    mpHeapBuffer = (char*)EA_operator_new(0x1000, "EATrace/Server/HeapBuffer/char[]", 0, 0, 0, 0);
    mnHeapBufferSize = 0x1000;
    mLogRecordCounter = 0;
    mpVecBegin = 0;
    mpVecEnd = 0;
    mpVecCapacity = 0;
    mDefaultFilter = 0;
    mDefaultFormatter = 0;
    mUnknown30 = 0;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    new (&mMutex) EA::Thread::Mutex(0, 1);
}

// @ 0x00923DC0
void* FUN_00923dc0(void* out, const char* fmt, ...)
{
    char* ap = (char*)&fmt + sizeof(fmt);
    ((VaString*)out)->FUN_0091a530(fmt, ap);
    return out;
}

// @ 0x00923E70
LogFormatterSimple::~LogFormatterSimple()
{
    FixedString2048* line = &mLine;
    if ((line->mpCapacity - line->mpBegin) > 1 && line->mpBegin != 0 && line->mpBegin != line->mpPool)
        EA_operator_delete(line->mpBegin);
    FixedString2048* nm = &mName;
    if ((nm->mpCapacity - nm->mpBegin) > 1 && nm->mpBegin != 0 && nm->mpBegin != nm->mpPool)
        EA_operator_delete(nm->mpBegin);
}

// @ 0x00923ED0
LogFormatterFancy::~LogFormatterFancy()
{
    FixedString2048* line = &mLine;
    if ((line->mpCapacity - line->mpBegin) > 1 && line->mpBegin != 0 && line->mpBegin != line->mpPool)
        EA_operator_delete(line->mpBegin);
    FixedString512* nm = &mName;
    if ((nm->mpCapacity - nm->mpBegin) > 1 && nm->mpBegin != 0 && nm->mpBegin != nm->mpPool)
        EA_operator_delete(nm->mpBegin);
}

// @ 0x00923CF0
LogReporter::~LogReporter()
{
    _ReadWriteBarrier();
    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        EA_operator_delete(mName.mpBegin);
    if (mFormatter.mpObject)
        ((void(__thiscall*)(void*))(*(void***)mFormatter.mpObject)[1])(mFormatter.mpObject);
    if (mFilter.mpObject)
        ((void(__thiscall*)(void*))(*(void***)mFilter.mpObject)[1])(mFilter.mpObject);
}

// @ 0x00923F30
LogFilterGroupLevels::LogFilterGroupLevels(void* cfg)
{
    mnRefCount = 0;
    mName.mpBegin = 0;
    mName.mpEnd = 0;
    mName.mpCapacity = 0;
    ((EaStringInit*)&mName)->FUN_0057cc10((const char*)cfg);
    mGlobalLevel = 1;
    void* alloc = EA_GetDefaultAllocator();
    RBNodeBase* anchor = &mGroupLevelMap.mAnchor;
    // the original zeroes anchor dwords +4..+0xc (color and its padding as one dword) first
    struct Zero3 { int a, b, c; };
    *(Zero3*)((int*)anchor + 1) = Zero3();
    mGroupLevelMap.mpAllocator = alloc;
    mGroupLevelMap.mpAllocator2 = 0;
    anchor->mpParent = 0;
    anchor->mColor = 0;
    mGroupLevelMap.mnSize = 0;
    anchor->mpRight = anchor;
    anchor->mpLeft = anchor;
}

// @ 0x00923F90
LogFilterGroupLevels::~LogFilterGroupLevels()
{
    _ReadWriteBarrier();
    mGlobalLevel = 1;
    char dummy = 0;
    RemoveGroupLevel(&dummy);
    RBNode* root = (RBNode*)mGroupLevelMap.mAnchor.mpParent;
    mGroupLevelMap.DoNukeSubtree(root);
    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        EA_operator_delete(mName.mpBegin);
}

// @ 0x00923FE0
void LogFilterGroupLevels::SetName(const char* name)
{
    ((EaStringOps*)&mName)->assign(name, name + strlen(name));
}

// @ 0x00924010
void LogReporter::SetName(const char* name)
{
    ((EaStringOps*)&mName)->assign(name, name + strlen(name));
    if (mFilter.mpObject)
        ((void(__thiscall*)(void*, const char*))(*(void***)mFilter.mpObject)[6])(mFilter.mpObject, name);
    if (mFormatter.mpObject)
        ((void(__thiscall*)(void*, const char*))(*(void***)mFormatter.mpObject)[5])(mFormatter.mpObject, name);
}

// @ 0x00924170
LogReporter::LogReporter(const char* name)
{
    mFilter.mpObject = 0;
    mFormatter.mpObject = 0;
    mIsEnabled = true;
    mnRefCount = 0;
    mName.mpBegin = (char*)&DAT_01667bac;
    mName.mpEnd = (char*)&DAT_01667bac;
    mName.mpCapacity = (char*)&DAT_01667bac + 1;
    ((EaStringOps*)&mName)->assign(name, name + strlen(name));
    if (mFilter.mpObject)
        ((void(__thiscall*)(void*, const char*))(*(void***)mFilter.mpObject)[6])(mFilter.mpObject, name);
    if (mFormatter.mpObject)
        ((void(__thiscall*)(void*, const char*))(*(void***)mFormatter.mpObject)[5])(mFormatter.mpObject, name);
}

// @ 0x00924270
int LogReporter::SkipFilter1(void* rec)
{
    void* r = rec;
    LogReporter* self = this;
    if ((*(unsigned char*)((char*)r + 8) & 1) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[5])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x009242B0
int LogReporter::SkipFilter2(void* rec)
{
    void* r = rec;
    LogReporter* self = this;
    if ((*(unsigned char*)(*(char**)((char*)r + 0xc) + 8) & 1) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[4])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x009242F0
void* LogReporter::ScalarDeletingDtor(char flags)
{
    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        EA_operator_delete(mName.mpBegin);
    if (mFormatter.mpObject)
        ((void(__thiscall*)(void*))(*(void***)mFormatter.mpObject)[1])(mFormatter.mpObject);
    if (mFilter.mpObject)
        ((void(__thiscall*)(void*))(*(void***)mFilter.mpObject)[1])(mFilter.mpObject);
    if (flags & 1)
        EA_operator_delete(this);
    return this;
}

// @ 0x00924350
int LogReporter::SkipFilter3(void* rec)
{
    void* r = rec;
    LogReporter* self = this;
    if ((*(unsigned char*)((char*)r + 8) & 2) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[5])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x00924390
int LogReporter::SkipFilter4(void* rec)
{
    void* r = rec;
    LogReporter* self = this;
    if ((*(unsigned char*)(*(char**)((char*)r + 0xc) + 8) & 2) != 0 && self->mIsEnabled && self->mFilter.mpObject != 0 && self->mFormatter.mpObject != 0) {
        bool ok = ((bool(__thiscall*)(void*, void*))(*(void***)self->mFilter.mpObject)[4])(self->mFilter.mpObject, r);
        if (!ok) return 0;
    }
    return 1;
}

// @ 0x009243D0
LogFormatterSimple::LogFormatterSimple(const char* name)
{
    FixedString2048* b = &mName;
    mnRefCount = 0;
    b->mpPool = b->buffer;
    b->mpEnd = b->buffer;
    b->mpBegin = b->buffer;
    b->mpCapacity = b->buffer + 0x800;
    b->buffer[0] = 0;
    ((SimpleStringOps*)&mName)->assign(name, name + strlen(name));
    FixedString2048* l = &mLine;
    l->mpPool = l->buffer;
    l->mpEnd = l->buffer;
    l->mpBegin = l->buffer;
    l->mpCapacity = l->buffer + 0x800;
    l->buffer[0] = 0;
}

// @ 0x00924450
void LogFormatterSimple::SetName(const char* name)
{
    FixedString2048* s = &mName;
    char* p = s->mpBegin;
    if (p != name) {
        if (p != s->mpEnd) {
            *p = 0;
            s->mpEnd = s->mpBegin;
        }
        ((SimpleStringOps*)s)->assign(name, name + strlen(name));
    }
}

// @ 0x00924490
void* LogFormatterSimple::Clone()
{
    LogFormatterSimple* p = (LogFormatterSimple*)EA_operator_new(0x1030, "EATrace/LogFormatterSimple/LogFormatterSimple", 0, 0, 0, 0);
    if (p != 0)
        return new (p) LogFormatterSimple(mName.mpBegin);
    return 0;
}

// @ 0x009244D0
LogFormatterFancy::LogFormatterFancy(const char* name)
{
    FixedString512* b = &mName;
    mnRefCount = 0;
    b->mpPool = b->buffer;
    b->mpEnd = b->buffer;
    b->mpBegin = b->buffer;
    b->mpCapacity = b->buffer + 0x200;
    b->buffer[0] = 0;
    ((FancyStringOps*)&mName)->assign(name, name + strlen(name));
    mnFlags = 0;
    mnFileInfoLevel = 100;
    ((Stopwatch*)&mTimer)->Stopwatch_ctor(4, 1);
    FixedString2048* l = &mLine;
    l->mpPool = l->buffer;
    l->mpEnd = l->buffer;
    l->mpBegin = l->buffer;
    l->mpCapacity = l->buffer + 0x800;
    l->buffer[0] = 0;
}

// @ 0x00924570
void LogFormatterFancy::SetName(const char* name)
{
    FixedString512* s = &mName;
    char* p = s->mpBegin;
    if (p != name) {
        if (p != s->mpEnd) {
            *p = 0;
            s->mpEnd = s->mpBegin;
        }
        ((FancyStringOps*)s)->assign(name, name + strlen(name));
    }
}

// @ 0x00923B40
void RBTreeMap::DoNukeSubtree(RBNode* node)
{
    while (node) {
        DoNukeSubtree(node->mpLeft);
        RBNode* next = node->mpRight;
        ((void(__thiscall*)(void*, RBNode*, int))(*(void***)mpAllocator)[3])(mpAllocator, node, 0x18);
        node = next;
    }
}

// @ 0x00923B80
RBNode** RBTreeMap::erase(RBNode** outNext, RBNode* pos)
{
    mnSize--;
    RBNode* next = (RBNode*)eastl_RBTreeIncrement(pos);
    eastl_RBTreeErase(pos, &mAnchor);
    ((void(__thiscall*)(void*, RBNode*, int))(*(void***)mpAllocator)[3])(mpAllocator, pos, 0x18);
    *outNext = next;
    return outNext;
}

// @ 0x00923AC0
RBNode** RBTreeMap::find(RBNode** out, const char** key)
{
    RBNode* end = (RBNode*)&mAnchor;
    RBNode* candidate = end;
    RBNode* node = (RBNode*)mAnchor.mpParent;
    while (node) {
        if (!(_stricmp(node->mpKey, *key) < 0)) {
            candidate = node;
            node = node->mpRight;
        } else {
            node = node->mpLeft;
        }
    }
    if (candidate != end && !(_stricmp(*key, candidate->mpKey) < 0)) {
        *out = candidate;
        return out;
    }
    *out = end;
    return out;
}

// @ 0x00923BC0
bool LogFilterGroupLevels::RemoveGroupLevel(const char* name)
{
    if (name == 0 || *name == 0) {
        RBNodeBase* end = &mGroupLevelMap.mAnchor;
        for (RBNode* n = (RBNode*)end->mpLeft; n != (RBNode*)end; n = (RBNode*)eastl_RBTreeIncrement(n))
            EA_operator_delete((void*)n->mpKey);
        RBNodeBase* root = (RBNodeBase*)end->mpParent;
        while (root) {
            mGroupLevelMap.DoNukeSubtree((RBNode*)((RBNode*)root)->mpRight);
            RBNodeBase* next = root->mpLeft;
            ((void(__thiscall*)(void*, RBNodeBase*, int))(*(void***)mGroupLevelMap.mpAllocator)[3])(mGroupLevelMap.mpAllocator, root, 0x18);
            root = next;
        }
        end->mpLeft = end;
        end->mpRight = end;
        end->mpParent = 0;
        end->mColor = 0;
        mGroupLevelMap.mnSize = 0;
        return false;
    }
    RBNode* found = 0;
    mGroupLevelMap.find(&found, &name);
    if (found != (RBNode*)&mGroupLevelMap.mAnchor) {
        EA_operator_delete((void*)found->mpKey);
        RBNode* next = 0;
        mGroupLevelMap.erase(&next, found);
        return true;
    }
    return false;
}

// @ 0x00923C90
bool LogFilterGroupLevels::IsFiltered2(void* rec)
{
    char* name = *(char**)((char*)rec + 0x10);
    if (name != 0 && *name != 0) {
        RBNode* it;
        RBNode* found = *mGroupLevelMap.find(&it, (const char**)&name);
        if (found != (RBNode*)&mGroupLevelMap.mAnchor)
            return *(int*)((char*)rec + 0xc) < found->mnValue;
    }
    return *(int*)((char*)rec + 0xc) < mGlobalLevel;
}

// @ 0x00923DE0
void RBTreeMap::DoInsertValueImpl(RBNode** out, RBNode* parent, const void* value, char hasParent)
{
    char color = 0;
    if (!hasParent && parent != (RBNode*)&mAnchor) {
        const char* k = *(const char**)value;
        if (_stricmp(k, parent->mpKey) >= 0)
            color = 1;
    }
    RBNode* node = (RBNode*)((void*(__thiscall*)(void*, int, int, int))(*(void***)mpAllocator)[2])(mpAllocator, 0x18, 0, (int)mpAllocator2);
    if (node) {
        node->mpKey = *(const char**)value;
        node->mnValue = *(int*)((char*)value + 4);
    }
    eastl_RBTreeInsert(node, parent, &mAnchor, color);
    mnSize++;
    if (out) *out = node;
}

// @ 0x00924060
void RBTreeMap::DoInsertValue(RBNode** out, const void* value)
{
    RBNode* node = (RBNode*)mAnchor.mpParent;
    RBNode* parent = (RBNode*)&mAnchor;
    char less = 1;
    while (node) {
        int c = _stricmp(*(const char**)value, node->mpKey);
        less = c < 0;
        parent = node;
        if (less) node = node->mpRight;
        else      node = node->mpLeft;
    }
    RBNode* spot = parent;
    if (less) {
        if (parent == (RBNode*)mAnchor.mpRight) {
            DoInsertValueImpl(out, parent, value, 0);
            return;
        }
        spot = (RBNode*)eastl_RBTreeDecrement(parent);
    }
    if (_stricmp(spot->mpKey, *(const char**)value) < 0) {
        DoInsertValueImpl(out, parent, value, 0);
    } else {
        if (out) *out = spot;
    }
}

// @ 0x009241F0
bool Server::RemoveLogReporter(ILogReporter* p)
{
    mMutex.Lock((unsigned*)&g_timeoutP);
    void** it = (void**)mpVecBegin;
    while (it != (void**)mpVecEnd) {
        if (*it == p)
            break;
        ++it;
    }
    if (it == (void**)mpVecEnd) {
        mMutex.Unlock();
        return false;
    }
    if ((char*)it + 4 < (char*)mpVecEnd) {
        eastl_copy_impl((char*)it + 4, mpVecEnd, it);
    }
    mpVecEnd = (char*)mpVecEnd - 4;
    ILogReporter* last = *(ILogReporter**)mpVecEnd;
    if (last)
        ((void(__thiscall*)(void*))(*(void***)last)[1])(last);
    mMutex.Unlock();
    return true;
}

// @ 0x009237C0
bool Server::GetLogReporter(char* name, int* out)
{
    mMutex.Lock((unsigned*)&g_timeoutP);
    *out = 0;
    void** it = (void**)mpVecBegin;
    void** end = (void**)mpVecEnd;
    while (it != end) {
        ILogReporter* p = *(ILogReporter**)*it;
        const char* s = ((const char*(__thiscall*)(void*))(*(void***)p)[7])(p);
        if (_stricmp(s, name) == 0) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            *out = (int)p;
            break;
        }
        ++it;
    }
    bool r = *out != 0;
    mMutex.Unlock();
    return r;
}

// @ 0x00923840
unsigned Server::EnumerateLogReporters(void** out, unsigned max)
{
    mMutex.Lock((unsigned*)&g_timeoutP);
    unsigned n = 0;
    if (out != 0) {
        void** it = (void**)mpVecBegin;
        void** end = (void**)mpVecEnd;
        while (it != end) {
            if (n >= max)
                break;
            ILogReporter* p = (ILogReporter*)*it;
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            out[n] = p;
            ++it;
            ++n;
        }
    }
    mMutex.Unlock();
    return n;
}

// @ 0x00923930  (Server::IsFiltered; an ITracer-side member, so `this` is Server+4)
bool ServerTracer::IsFiltered(void* rec)
{
    M()->Lock((unsigned*)&g_timeoutP);
    IReporterView** it = mpReportersBegin;
    IReporterView** end = mpReportersEnd;
    while (it != end) {
        if (!(*it)->IsFiltered(rec)) {
            M()->Unlock();
            return false;
        }
        ++it;
    }
    M()->Unlock();
    return true;
}

// ===========================================================================
// out-of-line / partial helpers kept for completeness
// ===========================================================================
