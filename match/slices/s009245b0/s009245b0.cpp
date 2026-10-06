// EA::Trace (0x009245B0..0x00925730). The module is EA's 2008 EAThread/EATrace library; only a
// handful of small functions are byte-exact. The large formatter/server bodies are reconstructed
// behaviourally where possible and left as skeletons otherwise (see nonmatching.txt / partial.txt).
#include <windows.h>
#include <stddef.h>
#include <string.h>

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

// ------------------------------------------------------------------ tractable pieces
struct EnabledValue { char pad[0x10]; unsigned field; };
extern EnabledValue* g_01668ea0;
// @ 0x009250C0
void SetTraceDialogEnabled(char b) { g_01668ea0->field = (unsigned)(b != 0); }

extern EnabledValue* g_01668e9c;

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

// ------------------------------------------------------------------ Server / reporters
struct ILogReporter;
struct LogReporterVec {
    char* mpBegin;   // +0
    char* mpEnd;     // +4
    char* mpCapacity; // +8
    void erase(char* first, char* last);
};
struct Server {
    char pad0[0x18];
    LogReporterVec mLogReporters;                 // +0x18
    char pad1[0x38 - 0x24];
    EA::Thread::Mutex mMutex;                     // +0x38
    void RemoveAllLogReporters();
};
// @ 0x00924A50
void Server::RemoveAllLogReporters() {
    mMutex.Lock(&g_timeout_143dc78);
    mLogReporters.erase(mLogReporters.mpBegin, mLogReporters.mpEnd);
    mMutex.Unlock();
}

// ------------------------------------------------------------------ TraceHelperTable pieces
struct ITraceHelperTable {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(void* p);
};
struct TraceHelperTable : ITraceHelperTable {
    void* mTracer;                                // +0x04
    void UpdateTracerV();                         // 0x009250B0
};
// @ 0x009250B0
void TraceHelperTable::UpdateTracerV() { v4(mTracer); }

// @ 0x009251D0  TraceHelperTable::UpdateTracer(ITracer*)
struct TraceHelperVector { char* mpBegin; char* mpEnd; char* mpCapacity; };
struct ITracer;
struct TraceHelperTable2 {
    char pad0[4];
    ITracer* mTracer;                             // +0x04
    TraceHelperVector mHelpers;                   // +0x08
    char pad1[0x20 - 0x14];
    EA::Thread::Mutex mMutex;                     // +0x20
    void UpdateTracer(ITracer* pTracer);
};
void TraceHelperTable2::UpdateTracer(ITracer* pTracer) {
    mMutex.Lock(&g_timeout_143dffc);
    mTracer = pTracer;
    char** it = (char**)mHelpers.mpBegin;
    char** end = (char**)mHelpers.mpEnd;
    for (; it != end; ++it) {
        char* h = *it;
        *(ITracer**)(h + 0x20) = pTracer;
        *(char*)(h + 1) = 1;
        *(char*)(h + 2) = 0;
    }
    mMutex.Unlock();
}

// @ 0x00925060  TraceHelperTable::Release
int ReleaseTraceHelperTable(TraceHelperTable* t) {
    int old = (int)(*(volatile int*)((char*)t + 0x50) -= 1);
    if (old == 1) {
        *(volatile int*)((char*)t + 0x50) = 1;
        if (t) ((void (__thiscall*)(void*, int))(*(void***)t)[2])(t, 1);
        return 0;
    }
    return old;
}

}} // namespace EA::Trace

// ================================================================== skeletons (partial)
// These EA::Trace library bodies (log formatters, server init, hashtable rehash, RTTI/refcount
// helpers) are reconstructed only in outline; see partial.txt.
namespace EA { namespace Trace {
struct Skeleton { char dummy; };
void FUN_009245b0(Skeleton*) {}
void FUN_00924600(Skeleton*) {}
void FUN_009246c0(Skeleton*) {}
void FUN_00924790(Skeleton*) {}
void FUN_009248f0(Skeleton*) {}
void FUN_00924a80(Skeleton*) {}
void FUN_00924bd0(Skeleton*) {}
void FUN_00924c60(Skeleton*) {}
void FUN_00924d10(Skeleton*) {}
void FUN_00924d90(Skeleton*) {}
void FUN_00925100(Skeleton*) {}
void FUN_00925220(Skeleton*) {}
void FUN_00925370(Skeleton*) {}
void FUN_00925420(Skeleton*) {}
void FUN_00925540(Skeleton*) {}
void FUN_009255a0(Skeleton*) {}
void FUN_009255f0(Skeleton*) {}
}}
