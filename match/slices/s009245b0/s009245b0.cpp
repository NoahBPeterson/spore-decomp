// EA::Trace (0x009245B0..0x00925730). The module is EA's 2008 EAThread/EATrace library.
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <new>
#include <intrin.h>

// ---- shared EA::Thread::Mutex stub (declarations only: callees are relocations)
namespace EA { namespace Thread {
struct EAMutexData { unsigned __int64 mData[4]; int mnLockCount; bool mbIntraProcess; void* mThreadId; };
class Mutex {
public:
    EAMutexData mMutexData;
    void Lock(unsigned* pTimeout);
    int  Unlock();
    ~Mutex();
};
}}
extern unsigned g_timeout_143dc78;
extern unsigned g_timeout_143dc64;
extern unsigned g_timeout_143dffc;

namespace EA { namespace Trace {

extern "C" void* __cdecl eanew(int a1, int a2, int a3, const char* name, int a5, int a6, int a7, int a8);
extern "C" void* __cdecl eanew6(int size, const char* name, int a, int b, int c, int d);
extern "C" void __cdecl eadelete(void* p);            // operator delete[] (0x00f47380)

// ------------------------------------------------------------------ tractable pieces
struct EnabledValue { char pad[0x10]; unsigned field; };
extern EnabledValue* g_01668ea0;
// @ 0x009250C0
void SetTraceDialogEnabled(char b) { g_01668ea0->field = (unsigned)(b != 0); }

// @ 0x00925000  TracerDialogThread::MessageBoxThreadStart
int __stdcall MessageBoxThreadStart(unsigned* p) {
    int r = MessageBoxA(0, (LPCSTR)p[0], (LPCSTR)p[1], 0x12132);
    switch (r) {
    case 3: p[2] = 1; return 0;
    case 5: p[2] = 2; return 0;
    default: p[2] = 0; return 0;
    }
}

// @ 0x00925730  EA::AutoOSGlobalPtr<EATraceDialogEnabledValue,15615573>::Create
void* CreateEnabledValue() {
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) { p[1] = 0; p[0] = 0; p[4] = 1; return p; }
    return 0;
}

// ------------------------------------------------------------------ shared interface stubs
struct IObj {                       // IRefCount-style: AddRef, Release, ?, Cast
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    virtual void v2();              // +0x08
    virtual void* Cast(unsigned id); // +0x0c
};
struct ILogFilter : IObj {
    virtual void v4();
    virtual void v5();
    virtual void SetName(const char*);   // +0x18
    virtual const char* GetName();       // +0x1c
    virtual ILogFilter* Clone();         // +0x20
};
struct ILogFormatter : IObj {
    virtual void v4();
    virtual void SetName(const char*);   // +0x14
    virtual void v6();
    virtual ILogFormatter* Clone();      // +0x1c
};
struct ILogReporter : IObj {
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual const char* GetName();             // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void SetFilter(ILogFilter*);       // +0x2c
    virtual ILogFilter* GetFilter();           // +0x30
    virtual void SetFormatter(ILogFormatter*); // +0x34
    virtual ILogFormatter* GetFormatter();     // +0x38
};

struct LogRecordInfo { int pad0[3]; int level; const char* group; const char* file; int line; const char* func; };
struct ILogRecord {
    virtual void v0(); virtual void v1();
    virtual const char* GetGroup();   // +0x08
    virtual const char* GetText();    // +0x0c
    int pad4, pad8;
    LogRecordInfo* mpInfo;            // +0x0c (object field)
};

// fixed_string<char,N,1> reduced to the three pointers
struct FString {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void push_back(char c);                              // 0x00924c60
    void append(const char* b, const char* e);           // 0x00942e50 / 0x009199c0
    void reserve(unsigned n);                            // 0x00887090
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
void __cdecl FormatInto(FString* s, const char* fmt, ...);  // 0x00923dc0
inline unsigned CharStrlen(const char* p) { const char* q = p; const char* b = p + 1; while (*q++) {} return (unsigned)(q - b); }
#define cstrend(p) ((p) + CharStrlen(p))

struct Stopwatch {
    int pad[6];
    unsigned __int64 GetElapsedTime();   // 0x0093a5e0
    void Restart();                      // 0x00571e80
};

// ------------------------------------------------------------------ LogFormatterFancy / Simple
struct LogFormatterFancy : ILogFormatter {
    int mnRefCount;
    char mName[0x21c - 8];
    unsigned short mnFlags;              // +0x21c
    char pad21e[2];
    int mnFileInfoLevel;                 // +0x220
    int pad224;
    Stopwatch mTimer;                    // +0x228
    FString mLine;                       // +0x240
    LogFormatterFancy(const char* name); // 0x009244d0
    ILogFormatter* Clone();
    const char* FormatRecord(ILogRecord* r);
};
// @ 0x009245B0
ILogFormatter* LogFormatterFancy::Clone() {
    void* m = eanew6(0xa58, "EATrace/LogFormatterFancy/LogFormatterFancy", 0, 0, 0, 0);
    LogFormatterFancy* r = m ? new (m) LogFormatterFancy(*(const char**)((char*)this + 8)) : 0;
    r->mnFlags = mnFlags;
    r->mnFileInfoLevel = mnFileInfoLevel;
    return r;
}

struct LogFormatterSimple : ILogFormatter {
    char pad[0x81c - 4];
    FString mLine;                       // +0x81c
    LogFormatterSimple(const char* name); // 0x009243d0
    const char* FormatRecord(ILogRecord* r);
};
// @ 0x00924D10
const char* LogFormatterSimple::FormatRecord(ILogRecord* r) {
    const char* text = r->GetText();
    mLine.append(text, cstrend(text));
    unsigned n = mLine.size();
    if (n == 0 || mLine.mpBegin[n - 1] != '\n') mLine.push_back('\n');
    LogRecordInfo* info = r->mpInfo;
    if (info->level >= 100) FormatInto(&mLine, "%s(%d): %s\n", info->file, info->line, info->func);
    return mLine.mpBegin;
}

// @ 0x00924D90
const char* LogFormatterFancy::FormatRecord(ILogRecord* r) {
    LogRecordInfo* info = r->mpInfo;
    const char* text = r->GetText();
    if (mnFlags != 0 || info->level >= mnFileInfoLevel) {
        if (mLine.mpBegin != mLine.mpEnd) { *mLine.mpBegin = 0; mLine.mpEnd = mLine.mpBegin; }
        if (mnFlags & 3) {
            unsigned __int64 t = mTimer.GetElapsedTime();
            __time64_t secs = (__time64_t)(t / 1000);
            unsigned ms = (unsigned)(t % 1000);
            struct tm* tmv = _gmtime64(&secs);
            char buf[32];
            if (mnFlags & 4) {
                size_t n = strftime(buf, 32, "%H:%M:%S", tmv);
                sprintf(buf + n, ":%03d ", ms);
            } else {
                strftime(buf, 32, "%H:%M:%S ", tmv);
            }
            mLine.append(buf, cstrend(buf));
            if (mnFlags & 2) mTimer.Restart();
        }
        if (mnFlags & 8) {
            __time64_t now = _time64(0);
            struct tm* tmv = _localtime64(&now);
            char buf[32];
            strftime(buf, 32, "%b %d %H:%M:%S ", tmv);
            mLine.append(buf, cstrend(buf));
        }
        if (mnFlags & 0x10) {
            const char* g = info->group;
            mLine.append(g, cstrend(g));
            mLine.push_back(' ');
        }
        if (mnFlags & 0x20) {
            const char* g = r->GetGroup();
            mLine.append(g, cstrend(g));
            mLine.push_back(' ');
        }
        mLine.append(text, cstrend(text));
        unsigned n = mLine.size();
        if (n == 0 || mLine.mpBegin[n - 1] != '\n') mLine.push_back('\n');
        if (info->level >= mnFileInfoLevel)
            FormatInto(&mLine, "%s(%d): %s\n", info->file, info->line, info->func);
        text = mLine.mpBegin;
    }
    return text;
}

// @ 0x00924C60  fixed-string push_back (grow when full, then store the char and the terminator)
void FString::push_back(char c) {
    if (mpEnd + 1 == mpCapacity) {
        unsigned nSize = mpEnd - mpBegin;
        unsigned nCap = mpCapacity - mpBegin;
        unsigned a = (nCap - 1 > 8) ? (nCap - 1) * 2 : 8;
        unsigned b = nSize + 1;
        const unsigned& m1 = (a < b) ? b : a;
        a = m1;
        unsigned s2 = nSize;
        const unsigned& m2 = (s2 < a) ? a : s2;
        unsigned want = m2 + 1;
        if (want > nCap) reserve(want);
    }
    *mpEnd = c;
    ++mpEnd;
    *mpEnd = 0;
}

// ------------------------------------------------------------------ LogFilterGroupLevels
struct RBNodeBase { RBNodeBase* mpNodeRight; RBNodeBase* mpNodeLeft; RBNodeBase* mpNodeParent; int mColor; };
struct RBNode : RBNodeBase { const char* key; int value; };
struct RBIter { RBNode* mpNode; };
struct GroupLevelMap {                   // eastl::map<const char*, int, KeyLess, EASTLCoreAllocator>
    void find(RBIter* out, const char** key);                 // 0x00923ac0
    void DoInsertValue(void* out, void* val, int flag);       // 0x00924060
};
RBNodeBase* __cdecl RBTreeIncrement(RBNodeBase* n);                   // 0x00921580
struct ICoreAllocator { static ICoreAllocator* GetDefaultAllocator(); };  // 0x00925cb0

struct LogFilterGroupLevels : ILogFilter {
    int mnRefCount;                      // +0x04
    char* mNameBegin;                    // +0x08
    char* mNameEnd;                      // +0x0c
    char* mNameCap;                      // +0x10
    int pad14;
    int mGlobalLevel;                    // +0x18
    int mapBase;                         // +0x1c: GroupLevelMap object
    RBNodeBase mAnchor;                  // +0x20
    int mnSize;                          // +0x30
    ICoreAllocator* mAllocator;          // +0x34
    int mnFlags;                         // +0x38
    LogFilterGroupLevels(const char* name);   // 0x00923f30
    __declspec(noinline) void AddGroupLevel(const char* group, int level);
    void RemoveGroupLevel(const char* group);                 // 0x00923bc0
    ILogFilter* Clone();
};
extern char g_empty_01667bac[];
extern char g_vtbl_LogFilterGroupLevels[];  // 0x0143dd9c

// @ 0x00924600
void LogFilterGroupLevels::AddGroupLevel(const char* group, int level) {
    if (group && *group) {
        RBIter it;
        const char* key = group;
        ((GroupLevelMap*)&mapBase)->find(&it, &key);
        if ((RBNodeBase*)it.mpNode == &mAnchor) {
            size_t n = strlen(group) + 1;
            char* copy = (char*)eanew6((int)n, "EATrace/LogFilterGroupLevels/GroupContainer/char[]", 0, 0, 0, 0);
            int off = (int)(copy - group);
            const char* s = group;
            char c;
            do { c = *s; ((char*)s)[off] = c; ++s; } while (c != 0);
            struct { const char* k; int v; } val = { copy, level };
            char out[8];
            ((GroupLevelMap*)&mapBase)->DoInsertValue(out, &val, 0);
        } else {
            it.mpNode->value = level;
        }
    } else {
        mGlobalLevel = level;
    }
}

// @ 0x009246C0
ILogFilter* LogFilterGroupLevels::Clone() {
    LogFilterGroupLevels* p = (LogFilterGroupLevels*)eanew6(0x3c, "EATrace/LogFilterGroupLevels/LogFilterGroupLevels", 0, 0, 0, 0);
    if (p) {
        *(void**)p = g_vtbl_LogFilterGroupLevels;
        p->mnRefCount = 0;
        p->mNameBegin = g_empty_01667bac;
        p->mNameEnd = g_empty_01667bac;
        p->mNameCap = g_empty_01667bac + 1;
        p->mGlobalLevel = 1;
        ICoreAllocator* a = ICoreAllocator::GetDefaultAllocator();
        RBNodeBase* an = &p->mAnchor;
        an->mpNodeLeft = 0;
        an->mpNodeParent = 0;
        an->mColor = 0;
        p->mAllocator = a;
        p->mnFlags = 0;
        an->mpNodeRight = an;
        an->mpNodeLeft = an;
        an->mpNodeParent = 0;
        *(char*)&an->mColor = 0;
        p->mnSize = 0;
    }
    LogFilterGroupLevels* r = p ? p : 0;
    r->SetName(GetName());
    char nul = 0;
    r->AddGroupLevel(&nul, mGlobalLevel);
    RBNodeBase* n = mAnchor.mpNodeLeft;
    while (n != &mAnchor) {
        r->AddGroupLevel(((RBNode*)n)->key, ((RBNode*)n)->value);
        n = RBTreeIncrement(n);
    }
    return r;
}

// ------------------------------------------------------------------ Server / reporters
template<class T> struct AutoRef { T* p; ~AutoRef() { if (p) p->Release(); } };
struct ILogReporterVec {
    ILogReporter** mpBegin; ILogReporter** mpEnd; ILogReporter** mpCapacity;
    void erase(ILogReporter** first, ILogReporter** last);   // 0x00e25bd0
    void DoInsertValue(ILogReporter** pos, ILogReporter** v); // 0x00a0a360
    ~ILogReporterVec();                                       // 0x00ae6970
};
struct IServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void ApplyReporters();                              // +0x18
    virtual bool AddLogReporter(ILogReporter* r);               // +0x1c
    virtual void RemoveReporter(ILogReporter* r);               // +0x20
    virtual void v9(); virtual void v10();
    virtual bool FindReporter(const char* name, ILogReporter** out);  // +0x2c
    ~IServer() {}
};
struct ITracerBase { virtual void t0(); ~ITracerBase() {} };
#pragma pack(push, 4)
struct Server : IServer, ITracerBase {
    int pad8;
    char* mpHeapBuffer;                   // +0x0c
    int pad10, pad14;
    ILogReporterVec mLogReporters;        // +0x18
    int pad24, pad28;
    AutoRef<ILogFilter> mpFilter;         // +0x2c
    AutoRef<ILogFormatter> mpFormatter;   // +0x30
    int pad34;
    EA::Thread::Mutex mMutex;             // +0x38
    void Init();
    virtual bool AddLogReporter(ILogReporter* r);
    bool SetOutputLevel(const char* name, const char* group, int level);
    ~Server();
    void RemoveAllLogReporters();
};
#pragma pack(pop)
struct LogReporter { LogReporter(const char* name); };      // 0x00924170
extern char g_vtbl_ReporterDebugger[], g_vtbl_ReporterDialog[], g_vtbl_Server_b[], g_vtbl_base[];

// @ 0x00924A50
void Server::RemoveAllLogReporters() {
    mMutex.Lock(&g_timeout_143dc78);
    mLogReporters.erase(mLogReporters.mpBegin, mLogReporters.mpEnd);
    mMutex.Unlock();
}

// @ 0x00924790
void Server::Init() {
    mMutex.Lock(&g_timeout_143dc78);
    if (!mpFilter.p) {
        void* m = eanew6(0x3c, "EATrace/Server/DefaultFilter/LogFilterGroupLevels", 0, 0, 0, 0);
        ILogFilter* f = m ? (ILogFilter*)new (m) LogFilterGroupLevels("DefaultFilter") : 0;
        ILogFilter* old = mpFilter.p;
        if (f != old) {
            if (f) f->AddRef();
            mpFilter.p = f;
            if (old) old->Release();
        }
    }
    if (!mpFormatter.p) {
        void* m = eanew6(0x1030, "EATrace/Server/DefaultFormatter/LogFormatterSimple", 0, 0, 0, 0);
        ILogFormatter* f = m ? (ILogFormatter*)new (m) LogFormatterSimple("DefaultFormatter") : 0;
        ILogFormatter* old = mpFormatter.p;
        if (f != old) {
            if (f) f->AddRef();
            mpFormatter.p = f;
            if (old) old->Release();
        }
    }
    if (mLogReporters.mpBegin == mLogReporters.mpEnd) {
        ILogReporter* r;
        void* m = eanew6(0x24, "EATrace/Server/LogReporterDebugger", 0, 0, 0, 0);
        if (m) { new (m) LogReporter("AppDebugger"); *(void**)m = g_vtbl_ReporterDebugger; r = (ILogReporter*)m; } else r = 0;
        AddLogReporter(r);
        m = eanew6(0x24, "EATrace/Server/LogReporterDialog", 0, 0, 0, 0);
        if (m) { new (m) LogReporter("AppAlertDialog"); *(void**)m = g_vtbl_ReporterDialog; r = (ILogReporter*)m; } else r = 0;
        AddLogReporter(r);
    }
    ApplyReporters();
    mMutex.Unlock();
}

// @ 0x009248F0
bool Server::AddLogReporter(ILogReporter* rep) {
    EA::Thread::Mutex* mtx = &mMutex;
    mtx->Lock(&g_timeout_143dc78);
    ILogReporter* existing = 0;
    if (FindReporter(rep->GetName(), &existing)) {
        if (existing == rep) goto done;
        RemoveReporter(existing);
        if (existing) { ILogReporter* e = existing; existing = 0; e->Release(); }
    }
    if (!rep->GetFormatter() && mpFormatter.p) {
        ILogFormatter* f = mpFormatter.p->Clone();
        f->SetName(rep->GetName());
        rep->SetFormatter(f);
    }
    if (!rep->GetFilter() && mpFilter.p) {
        ILogFilter* f = mpFilter.p->Clone();
        f->SetName(rep->GetName());
        rep->SetFilter(f);
    }
    {
        ILogReporter* tmp = rep;
        rep->AddRef();
        if (mLogReporters.mpEnd < mLogReporters.mpCapacity) {
            ILogReporter** p = mLogReporters.mpEnd;
            mLogReporters.mpEnd = p + 1;
            if (p) { *p = tmp; tmp->AddRef(); }
        } else {
            mLogReporters.DoInsertValue(mLogReporters.mpEnd, &tmp);
        }
        if (tmp) tmp->Release();
    }
done:
    if (existing) existing->Release();
    mtx->Unlock();
    return true;
}

// @ 0x00924A80  Server::SetOutputLevel
bool Server::SetOutputLevel(const char* name, const char* group, int level) {
    mMutex.Lock(&g_timeout_143dc78);
    bool ok = true;
    if (name) {
        ILogReporter* rep = 0;
        if (FindReporter(name, &rep)) {
            ILogFilter* f = rep->GetFilter();
            if (f) {
                LogFilterGroupLevels* lg = (LogFilterGroupLevels*)f->Cast(0x2e9e25fe);
                if (lg) {
                    if (level == 0) lg->RemoveGroupLevel(group);
                    else lg->AddGroupLevel(group, level);
                }
            }
        } else {
            ok = false;
        }
        if (rep) rep->Release();
    } else {
        ILogFilter* df = mpFilter.p;
        if (df) {
            LogFilterGroupLevels* lg = (LogFilterGroupLevels*)df->Cast(0x2e9e25fe);
            if (lg) {
                if (level == 0) lg->RemoveGroupLevel(group);
                else lg->AddGroupLevel(group, level);
            }
        }
        ILogReporter** it = mLogReporters.mpBegin;
        ILogReporter** end = mLogReporters.mpEnd;
        for (; it != end; ++it) {
            ILogFilter* f = (*it)->GetFilter();
            if (f) {
                LogFilterGroupLevels* lg = (LogFilterGroupLevels*)f->Cast(0x2e9e25fe);
                if (lg) {
                    if (level == 0) lg->RemoveGroupLevel(group);
                    else lg->AddGroupLevel(group, level);
                }
            }
        }
    }
    mMutex.Unlock();
    return ok;
}

// @ 0x00924BD0
Server::~Server() {
    eadelete(mpHeapBuffer);
    mMutex.Lock(&g_timeout_143dc78);
    mLogReporters.erase(mLogReporters.mpBegin, mLogReporters.mpEnd);
    mMutex.Unlock();
}

// ------------------------------------------------------------------ TraceHelper / TraceHelperTable
struct ITracer;
struct TraceHelper {
    bool mbActive, mbEnabled, mbDisabled;       // +0, +1, +2
    unsigned mType;                             // +4
    int mField8;                                // +8
    int mField0c;                               // +0xc
    const char* mName;                          // +0x10
    int mLoc[3];                                // +0x14
    ITracer* mTracer;                           // +0x20
    TraceHelper(unsigned type, const char* name, int level, const int* loc);
};
struct TraceHelperTableBase {
    virtual void v0();
    virtual void v1();
    virtual ~TraceHelperTableBase() {}                          // +0x08
    virtual void v3();
    virtual void UpdateTracerRaw(void* p);                      // +0x10
    virtual void v5();
    virtual void RegisterHelper(TraceHelper* h);                // +0x18
    virtual void ReleaseHelper(TraceHelper* h);                 // +0x1c
};
struct HelperVec {
    char** mpBegin; char** mpEnd; char** mpCapacity;
    int pad[3];
    ~HelperVec() { if (mpBegin && ((int*)mpBegin)[-1]) eadelete(mpBegin); }
};
struct TraceHelperTable : TraceHelperTableBase {
    void* mTracer;                                // +0x04
    HelperVec mHelpers;                           // +0x08
    EA::Thread::Mutex mMutex;                     // +0x20
    volatile int mnRefCount;                      // +0x50
    TraceHelperTable();
    ~TraceHelperTable() {}
    void UpdateTracerV();                         // 0x009250B0
    void UpdateTracer(ITracer* pTracer);
    int  Release();
    TraceHelper* ReserveHelper(unsigned type, const char* name, int level, const int* loc);
};
struct HelperTableHolder { char pad[0x10]; TraceHelperTable* field; };
extern HelperTableHolder* g_01668e9c;

// @ 0x009250B0
void TraceHelperTable::UpdateTracerV() { UpdateTracerRaw(mTracer); }

// @ 0x009251D0  TraceHelperTable::UpdateTracer(ITracer*)
void TraceHelperTable::UpdateTracer(ITracer* pTracer) {
    mMutex.Lock(&g_timeout_143dffc);
    mTracer = pTracer;
    char** it = mHelpers.mpBegin;
    char** end = mHelpers.mpEnd;
    for (; it != end; ++it) {
        TraceHelper* h = (TraceHelper*)*it;
        h->mTracer = (ITracer*)mTracer;
        h->mbEnabled = true;
        h->mbDisabled = false;
    }
    mMutex.Unlock();
}

// @ 0x00925060  TraceHelperTable::Release
int TraceHelperTable::Release() {
    int n = _InterlockedExchangeAdd((volatile long*)&mnRefCount, -1);
    if (--n == 0) {
        _InterlockedExchange((volatile long*)&mnRefCount, 1);
        if (this) delete this;
        return 0;
    }
    return n;
}

// @ 0x00925220
TraceHelper::TraceHelper(unsigned type, const char* name, int level, const int* loc) {
    mbActive = true; mbEnabled = true; mbDisabled = false;
    mType = type;
    mField8 = 0;
    mField0c = level;
    mName = name;
    mLoc[0] = loc[0]; mLoc[1] = loc[1]; mLoc[2] = loc[2];
    mTracer = 0;
    switch (type) {
    case 0: case 1:
        mField8 = 3;
        if (level == 0) mField0c = 0x96;
        break;
    case 2:
        mField8 = 1;
        if (level == 0) mField0c = 0x19;
        break;
    case 3:
        mField8 = 3;
        mField0c = 0x96;
        break;
    default:
        mField8 = 1;
        break;
    }
    if (name == 0) mName = "Assert";
    TraceHelperTable* t = g_01668e9c->field;
    if (t) {
        t->RegisterHelper(this);
    } else {
        mbActive = false;
        mbDisabled = true;
    }
}

// @ 0x00925420  TraceHelperTable::ReserveHelper
TraceHelper* TraceHelperTable::ReserveHelper(unsigned type, const char* name, int level, const int* loc) {
    mMutex.Lock(&g_timeout_143dffc);
    void* m = eanew6(0x24, "EATrace/TraceHelper", 0, 0, 0, 0);
    TraceHelper* h = m ? new (m) TraceHelper(type, name, level, loc) : 0;
    mMutex.Unlock();
    return h;
}

// @ 0x009255A0  TraceHelperTable scalar deleting destructor (compiler-generated from ~TraceHelperTable;
// the ctor below only forces the vtable and the deleting destructor to be emitted)
TraceHelperTable::TraceHelperTable() {}

// @ 0x00925100  DisplayTraceDialog
extern const char g_dialogTail_143e008[0x45];
int DisplayTraceDialog(const char* msg) {
    if (g_01668ea0->field == 1) {
        char buf[0x200];
        strncpy(buf, msg, 0x200);
        buf[0x1ff] = 0;
        size_t len = strlen(buf);
        if (0x200 - len >= 0x45) memcpy(buf + len, g_dialogTail_143e008, 0x45);
        unsigned args[3];
        args[0] = (unsigned)buf;
        args[1] = (unsigned)msg;
        args[2] = 0;
        HANDLE h = CreateThread(0, 0x10000, (LPTHREAD_START_ROUTINE)MessageBoxThreadStart, args, 0, 0);
        if (h) {
            WaitForSingleObject(h, (DWORD)-1);
            CloseHandle(h);
        }
        return args[2];
    }
    return 0;
}

// ------------------------------------------------------------------ trace helper log-manager holder
struct ILogManager : IObj {};
ILogManager* GetLogManager();                 // 0x00697fa0
struct TraceLogManagerRef {
    int f0, f4, f8, fc;
    ILogManager* mpLogManager;                // +0x10
    TraceLogManagerRef();
};
// @ 0x00925540
TraceLogManagerRef::TraceLogManagerRef() {
    f4 = 0; f0 = 0; mpLogManager = 0;
    ILogManager* m = GetLogManager();
    ILogManager* old = mpLogManager;
    if (m != old) {
        if (m) m->AddRef();
        mpLogManager = m;
        if (old) old->Release();
    }
    g_01668e9c->field->UpdateTracerRaw(mpLogManager);
}

// ------------------------------------------------------------------ hashtable DoRehash / TempTraceHelperMap
struct HNode { int key; int* pObj; HNode* mpNext; };
struct TraceHashtable {
    int pad0;
    HNode** mpBucketArray;           // +4
    unsigned mnBucketCount;          // +8
    int pad0c, pad10, pad14, pad18;
    HNode* mpFreeList;               // +0x1c
    int pad20;
    char* mpPoolBegin;               // +0x24
    char* mpPoolEnd;                 // +0x28
    int pad2c;
    HNode** mpInlineBuckets;         // +0x30
    HNode** DoAllocateBuckets(unsigned n);   // 0x00925300
    void DoRehash(unsigned nNewBucketCount);
};
// @ 0x00925370
void TraceHashtable::DoRehash(unsigned nNewBucketCount) {
    HNode** pNewBucketArray = DoAllocateBuckets(nNewBucketCount);
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        HNode* pNode;
        while ((pNode = mpBucketArray[i]) != 0) {
            int k2 = pNode->pObj ? *pNode->pObj : 0;
            unsigned nNewBucketIndex = (unsigned)(pNode->key + k2) % nNewBucketCount;
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pNewBucketArray[nNewBucketIndex];
            pNewBucketArray[nNewBucketIndex] = pNode;
        }
    }
    if (mnBucketCount > 1 && (HNode**)mpBucketArray != mpInlineBuckets) {
        if ((char*)mpBucketArray >= mpPoolBegin && (char*)mpBucketArray < mpPoolEnd) {
            *(HNode**)mpBucketArray = mpFreeList;
            mpFreeList = (HNode*)mpBucketArray;
            mpBucketArray = pNewBucketArray;
            mnBucketCount = nNewBucketCount;
            return;
        }
        eadelete(mpBucketArray);
    }
    mpBucketArray = pNewBucketArray;
    mnBucketCount = nNewBucketCount;
}

struct TempNode { int a, b, c; char* mpHelper; TempNode* mpNext; };
struct TempTraceHelperMap {
    EA::Thread::Mutex mMutex;                // +0
    struct {
        int pad0;
        TempNode** mpBucketArray;            // +0x34 (this+0x30 + 4)
        unsigned mnBucketCount;              // +0x38
        unsigned mnElementCount;             // +0x3c
        void DoFreeNodes(TempNode** begin, unsigned count);  // 0x007611f0
    } mTable;                                // +0x30
    char pad40[0x50 - 0x40];
    bool mbHelpersReserved;                  // +0x50
    void ReleaseHelpers();
};
// @ 0x009255F0
void TempTraceHelperMap::ReleaseHelpers() {
    mMutex.Lock(&g_timeout_143dffc);
    TempNode** pBucket = mTable.mpBucketArray;
    TempNode* pNode = *pBucket;
    if (!pNode) {
        do { ++pBucket; } while (*pBucket == 0);
        pNode = *pBucket;
    }
    TempNode* pEnd = mTable.mpBucketArray[mTable.mnBucketCount];
    while (pNode != pEnd) {
        char* h = pNode->mpHelper;
        if (h) {
            TraceHelperTable* t = g_01668e9c->field;
            if (t) t->ReleaseHelper((TraceHelper*)h);
            eadelete(h);
        }
        pNode = pNode->mpNext;
        if (!pNode) {
            do { pNode = pBucket[1]; ++pBucket; } while (!pNode);
        }
    }
    mTable.DoFreeNodes(mTable.mpBucketArray, mTable.mnBucketCount);
    mTable.mnElementCount = 0;
    mbHelpersReserved = false;
    mMutex.Unlock();
}

}} // namespace EA::Trace
