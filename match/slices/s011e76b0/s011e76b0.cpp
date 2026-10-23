// Slice s011e76b0 -- RenderWare 4 core: rw::core::filesys stream/request teardown helpers and
// rw::core::timer::Stopwatch (unit setup, frequency calibration, start/stop/elapsed).
//
// This address range (0x011e2000-0x0120bc50) is RenderWare 4 core, built with VC .NET 2003
// (cl 13.10) and /GL + /LTCG (see symbols/renderware4_core.txt).  A single-object compile cannot
// reproduce the /LTCG cross-call register allocation, so byte-exactness is only achievable for
// leaf functions (and the small Stopwatch accessors below).  Everything else is a complete
// behavioural reconstruction recorded in nonmatching.txt with an equivalence verdict.
//
// Compiled with: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include <intrin.h>
#include <stddef.h>

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned __int64 u64;

// ---------------------------------------------------------------------------
// out-of-slice helpers (real addresses)
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p);   // kernel32
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(long long* p); // kernel32
extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) u32   __stdcall GetPriorityClass(void* h);
extern "C" __declspec(dllimport) void* __stdcall GetCurrentThread();
extern "C" __declspec(dllimport) int   __stdcall GetThreadPriority(void* h);
extern "C" __declspec(dllimport) int   __stdcall SetPriorityClass(void* h, u32 c);
extern "C" __declspec(dllimport) int   __stdcall SetThreadPriority(void* h, int p);
extern "C" __declspec(dllimport) u32   __stdcall SleepEx(u32 ms, int alertable);

// ---- image globals ---------------------------------------------------------
extern float g_one;             // 0x01485720  1.0f
extern char  g_stopwatchVtbl[]; // 0x014f6570
extern u64   g_swFreq;          // 0x015d0358  measured QueryPerformanceFrequency
extern u64   g_cpuFreq;         // 0x015d0360  measured CPU (TSC) frequency
extern u32   g_cpuRatio;        // 0x015d0368  cpuFreq / swFreq

extern float g_f18;  // 0x016f4b18
extern float g_f1c;  // 0x016f4b1c
extern float g_f20;  // 0x016f4b20
extern float g_f24;  // 0x016f4b24
extern float g_f28;  // 0x016f4b28
extern float g_f2c;  // 0x016f4b2c
extern float g_f30;  // 0x016f4b30
extern float g_f34;  // 0x016f4b34
extern float g_f38;  // 0x016f4b38
extern float g_f3c;  // 0x016f4b3c
extern float g_f40;  // 0x016f4b40
extern float g_f44;  // 0x016f4b44
extern float g_f48;  // 0x016f4b48
extern float g_f4c;  // 0x016f4b4c
extern float g_f50;  // 0x016f4b50
extern float g_f54;  // 0x016f4b54
extern float g_f58;  // 0x016f4b58
extern float g_f5c;  // 0x016f4b5c
extern float g_f60;  // 0x016f4b60
extern float g_f64;  // 0x016f4b64
extern u64   g_overhead;        // 0x016f4b68  QPC read overhead (cycles)
extern u64   g_cycleOverhead;   // 0x016f4b70  TSC read overhead (cycles)

void GetFrequencies(u64* swFreq, u64* cpuFreq);   // 0x011e7d90
void TimerInitialize();                           // 0x011e80a0

// ---------------------------------------------------------------------------
// rw::core::timer::Stopwatch
// ---------------------------------------------------------------------------
struct Stopwatch {
    void* vftable;      // 0x00
    u32   pad4;         // 0x04
    int   mUnits;       // 0x08
    u32   padc;         // 0x0c
    u64   mStartTime;   // 0x10
    u64   mTotal;       // 0x18
    float mCoeff;       // 0x20

    Stopwatch(int units, bool start);
    void  SetUnits(int units);
    void  Stop();
    float GetElapsedTime();
};

// @ 0x011e7fe0
void Stopwatch::SetUnits(int units)
{
    mUnits = units;
    switch (units) {
    case 2: mCoeff = g_f24; break;
    case 3: mCoeff = g_f50; break;
    case 4: mCoeff = g_f48; break;
    case 5: mCoeff = g_f34; break;
    case 6: mCoeff = g_f5c; break;
    case 0: case 1: case 1000: mCoeff = g_one; break;
    }
}

// @ 0x011e82d0
Stopwatch::Stopwatch(int units, bool start)
{
    vftable = g_stopwatchVtbl;
    mUnits = 0;
    mStartTime = 0;
    mTotal = 0;
    mCoeff = 1.0f;
    if (g_swFreq <= 1)
    {
        GetFrequencies(&g_swFreq, &g_cpuFreq);
        TimerInitialize();
    }
    SetUnits(units);
    if (start)
    {
        if (mUnits == 1)
        {
            mStartTime = __rdtsc();
        }
        else
        {
            long long t;
            QueryPerformanceCounter(&t);
            mStartTime = t;
        }
    }
}

// @ 0x011e8080
u64 GetStopwatchCycle()
{
    u64 t;
    QueryPerformanceCounter((long long*)&t);
    return t;
}

// @ 0x011e83a0
void Stopwatch::Stop()
{
    if (mStartTime != 0)
    {
        u64 now;
        if (mUnits == 1) { now = __rdtsc(); }
        else { long long t; QueryPerformanceCounter(&t); now = t; }
        u64 delta = now - mStartTime;
        if (delta > g_overhead)
            mTotal += delta - g_overhead;
        else
            mTotal += 1;
        mStartTime = 0;
    }
}

// @ 0x011e8440
float Stopwatch::GetElapsedTime()
{
    u64 total = mTotal;
    if (mStartTime != 0)
    {
        u64 now;
        if (mUnits == 1) { now = __rdtsc(); }
        else { long long t; QueryPerformanceCounter(&t); now = t; }
        u64 delta = now - mStartTime;
        if (delta > g_overhead)
            total += delta - g_overhead;
        else
            total += 1;
    }
    return (float)(__int64)total * mCoeff;
}

// @ 0x011e7d90
void GetFrequencies(u64* swFreq, u64* cpuFreq)
{
    void* hProcess = GetCurrentProcess();
    u32   oldClass = GetPriorityClass(hProcess);
    void* hThread = GetCurrentThread();
    int   oldPrio = GetThreadPriority(hThread);
    SetPriorityClass(hProcess, 0x100);
    SetThreadPriority(hThread, 0xf);

    *cpuFreq = 0;
    int tries = 0;
    for (;;)
    {
        long long qpc;
        QueryPerformanceCounter(&qpc);
        u64 tsc = __rdtsc();
        double ratio = (double)tsc / (double)(u64)qpc;
        if (ratio > 0.98 && ratio < 1.02)
        {
            QueryPerformanceFrequency((long long*)cpuFreq);
            break;
        }
        if (++tries >= 5)
            break;
    }

    if (*cpuFreq == 0)
    {
        long long qpcFreq;
        long long qpc0;
        QueryPerformanceFrequency(&qpcFreq);
        QueryPerformanceCounter(&qpc0);
        u64 tsc0 = __rdtsc();
        long long qpc1;
        u64 tsc1;
        double ratio;
        do
        {
            SleepEx(50, 1);
            QueryPerformanceCounter(&qpc1);
            tsc1 = __rdtsc();
            ratio = (double)(tsc1 - tsc0) / (double)(u64)(qpc1 - qpc0);
        } while (ratio < 0.25);
        *cpuFreq = (u64)(ratio * (double)qpcFreq);
    }

    QueryPerformanceFrequency((long long*)swFreq);
    SetPriorityClass(hProcess, oldClass);
    SetThreadPriority(hThread, oldPrio);
}

// @ 0x011e80a0
void TimerInitialize()
{
    float swInv = (float)(1.0 / (double)g_swFreq);
    g_f34 = swInv;
    g_f5c = swInv * 0.016666668f;
    g_f18 = 1.0f / g_f5c;
    g_f30 = 1.0f / swInv;
    g_f48 = swInv * 1000.0f;
    g_f40 = 1.0f / g_f48;
    g_f50 = swInv * 1000000.0f;
    g_f24 = swInv * 1000000000.0f;
    g_f58 = 1.0f / g_f50;
    g_f38 = 1.0f / g_f24;

    u64 best = 0xffffffffffffffffull;
    for (int i = 8; i != 0; --i)
    {
        long long t0, t1;
        QueryPerformanceCounter(&t0);
        QueryPerformanceCounter(&t1);
        u64 d = (u64)t1 - (u64)t0;
        if (d < best)
            best = d;
    }
    g_overhead = best;

    float cpuInv = (float)(1.0 / (double)g_cpuFreq);
    g_f3c = cpuInv;
    g_f20 = cpuInv * 0.016666668f;
    g_f2c = cpuInv * 1000.0f;
    g_f1c = cpuInv * 1000000.0f;
    g_f4c = cpuInv * 1000000000.0f;
    g_f28 = 1.0f / g_f4c;
    g_f64 = 1.0f / g_f1c;
    g_f54 = 1.0f / g_f2c;
    g_f60 = 1.0f / cpuInv;
    g_f44 = 1.0f / g_f20;

    u64 best2 = 0xffffffffffffffffull;
    for (int i = 8; i != 0; --i)
    {
        u64 a = __rdtsc();
        u64 b = __rdtsc();
        u64 d = b - a;
        if (d < best2)
            best2 = d;
    }
    g_cycleOverhead = best2;

    g_cpuRatio = (u32)(g_cpuFreq / g_swFreq);
}

// ===========================================================================
// rw::core::filesys -- Stream / StreamImpl / AsyncOp
// ===========================================================================
// Same RenderWare 4 core range (/GL + /LTCG, symbols/renderware4_core.txt):
// equivalence-only.  Every function below is a complete behavioural
// reconstruction using the literal object offsets seen in the disassembly;
// the two small leaf helpers (AsyncOp ctor / Reset) are byte-exact.
struct Mutex {
    void Lock(void* name);      // 0x011ec170
    void Unlock();              // 0x011ec230
    void Destroy();             // 0x011ec0f0
};

struct RAllocator {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Free(void* p); // vtable +0x08
};
extern RAllocator* g_rwFsAllocator;     // 0x016f4b10  ?g_rwFsAllocator@@3PAXA

extern char g_fsWaitName[];             // 0x014f6558
extern char g_fsSleepName[];            // 0x014f6554

struct FreeBlk { void* p; void* a; void* b; void* c; };
static void FreePtr(void* p)
{
    FreeBlk blk;
    blk.p = p;
    blk.a = 0;
    blk.b = 0;
    blk.c = 0;
    g_rwFsAllocator->Free(&blk);
}

// ---- out-of-slice filesys callees (real addresses) ------------------------
void* StreamImpl_operator_new(u32 size);      // 0x011e6d20
struct StreamImpl {
    StreamImpl* Init(u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6);   // 0x011e7410
    void FreeRequest(void* rec);                                        // 0x011e6730
};
void  DecBufferUsage(u32 n);                                                          // 0x011e6600
void  RestartStream(void* impl, u32 arg);                                             // 0x011e7100
void* GetFsManager();                                                                 // 0x011e58f0
void  ThreadSleep(void* name);                                                        // 0x011ec7e0
void  NoOpCallback(void* op);                                                         // 0x011fb220

struct AsyncOp;
struct Device {
    char pad[0x120];
    void* mDriver;                      // 0x120
    int InsertOp(AsyncOp* op);          // 0x011e6340
};
struct StreamIo {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual int  s14(void* key, void* buf, u32 want, void* drv, void* ctx);
    virtual int  s18(void* key, void* buf, u32 count, void* drv, void* ctx);
    virtual u64  s1c(void* key, u64 pos, u32 flags, void* drv, void* ctx);
    virtual u64  s20(void* key);
    virtual void s24();
    virtual void s28();
    virtual u32  s2c();
};
struct IoCtx {
    char  pad0[8];
    void* mDriverKey;                   // 0x08
    Device* mpDevice;                   // 0x0c
    char  pad2[0x10];
    u64   mLeadPos;                     // 0x20
};
struct IoStream {
    char      pad0[4];
    IoCtx*    mpContext;                // 0x04
    void*     mDriverKey;               // 0x08
    Device*   mpDevice;                 // 0x0c
    StreamIo* mpIo;                     // 0x10
    char      pad14[4];
    u64       mWritePos;                // 0x18
};

struct AsyncOp {
    void* next;                       // 0x00
    int   mStatus;                    // 0x04
    bool  mCancelled;                 // 0x08
    bool  mIsRead;                    // 0x09
    int   mPriority;                  // 0x0c
    void* mFileHandle;                // 0x10
    void* mContext;                   // 0x14
    void (*mCallbackFunc)(AsyncOp*);  // 0x18
    u64   mValue;                     // 0x20
    u64   mAmount;                    // 0x28
    void* mData;                      // 0x30
    u64   mTotalBytes;                // 0x38
    void* mDevice;                    // 0x40
    void* mExecFunc;                  // 0x44

    AsyncOp();
    void Reset();
    void SetPriority(int prio);                                        // 0x011e8710
    int  GetStatus(const u32& wait);                                   // 0x011e8740
    void Close(IoStream* stream, void* cb, void* ctx, int prio);       // 0x011e89e0
};

// ---------------------------------------------------------------------------
// StreamImpl list teardown
// ---------------------------------------------------------------------------
// @ 0x011e76b0
void __fastcall StreamImpl_ClearLists(void* implPtr, int)
{
    char* s = (char*)implPtr;
    char* node;

    // --- list A: head 0x50 / tail 0x54 / count 0x58 ---
    node = *(char**)(s + 0x50);
    if (node != 0)
    {
        if (node == *(char**)(s + 0x54)) { *(u32*)(s + 0x50) = 0; *(u32*)(s + 0x54) = 0; }
        else *(char**)(s + 0x50) = *(char**)node;
        *(int*)(s + 0x58) -= 1;
        *(u32*)node = 0;
        while (node != 0)
        {
            *(u32*)node = 0;
            FreePtr(node);
            node = *(char**)(s + 0x50);
            if (node == 0) break;
            if (node == *(char**)(s + 0x54)) { *(u32*)(s + 0x50) = 0; *(u32*)(s + 0x54) = 0; }
            else *(char**)(s + 0x50) = *(char**)node;
            *(int*)(s + 0x58) -= 1;
            *(u32*)node = 0;
        }
    }

    // --- list B: head 0x38 / tail 0x3c / count 0x40 ---
    node = *(char**)(s + 0x38);
    if (node != 0)
    {
        if (node == *(char**)(s + 0x3c)) { *(u32*)(s + 0x38) = 0; *(u32*)(s + 0x3c) = 0; }
        else *(char**)(s + 0x38) = *(char**)node;
        *(int*)(s + 0x40) -= 1;
        *(u32*)node = 0;
        while (node != 0)
        {
            *(u32*)(node + 8) = 0;
            *(u32*)node = 0;
            FreePtr(node);
            node = *(char**)(s + 0x38);
            if (node == 0) break;
            if (node == *(char**)(s + 0x3c)) { *(u32*)(s + 0x38) = 0; *(u32*)(s + 0x3c) = 0; }
            else *(char**)(s + 0x38) = *(char**)node;
            *(int*)(s + 0x40) -= 1;
            *(u32*)node = 0;
        }
    }

    // --- list C: head 0x44 / tail 0x48 / count 0x4c ---
    node = *(char**)(s + 0x44);
    if (node != 0)
    {
        if (node == *(char**)(s + 0x48)) { *(u32*)(s + 0x44) = 0; *(u32*)(s + 0x48) = 0; }
        else *(char**)(s + 0x44) = *(char**)node;
        *(int*)(s + 0x4c) -= 1;
        *(u32*)node = 0;
        while (node != 0)
        {
            *(u32*)(node + 4) = 0;
            *(u32*)(node + 0x10) = 0;
            *(u32*)node = 0;
            FreePtr(node);
            node = *(char**)(s + 0x44);
            if (node == 0) break;
            if (node == *(char**)(s + 0x48)) { *(u32*)(s + 0x44) = 0; *(u32*)(s + 0x48) = 0; }
            else *(char**)(s + 0x44) = *(char**)node;
            *(int*)(s + 0x4c) -= 1;
            *(u32*)node = 0;
        }
    }

    // --- request table at 0x30 and the rest of the scalar state ---
    FreePtr(*(void**)(s + 0x30));
    *(u32*)(s + 0x30) = 0;
    *(u32*)(s + 0x5c) = 0;
    *(u32*)(s + 0x60) = 0;
    *(u32*)(s + 0x64) = 0;
    *(u32*)(s + 0x80) = 0;
    *(u32*)(s + 0x84) = 0;
    *(u32*)(s + 0x88) = 0;
    *(u32*)(s + 0x8c) = 0;
    *(u32*)(s + 0x90) = 0;
    *(u32*)(s + 0x94) = 0;
    *(u32*)(s + 0x98) = 0;
    *(u32*)(s + 0xa0) = 0;
    *(u32*)(s + 0x1a4) = 0;
    ((AsyncOp*)(s + 0x1b0))->Reset();

    // --- null the residual chains (lists are empty by now; mirrors the retail epilogue) ---
    node = *(char**)(s + 0x50);
    if (node != 0)
        while (*(char**)node != 0) { char* nxt = *(char**)node; *(u32*)node = 0; node = nxt; }
    *(u32*)(s + 0x54) = 0; *(u32*)(s + 0x50) = 0; *(u32*)(s + 0x58) = 0;

    node = *(char**)(s + 0x44);
    if (node != 0)
        while (*(char**)node != 0) { char* nxt = *(char**)node; *(u32*)node = 0; node = nxt; }
    *(u32*)(s + 0x48) = 0; *(u32*)(s + 0x44) = 0; *(u32*)(s + 0x4c) = 0;

    node = *(char**)(s + 0x38);
    if (node != 0)
        while (*(char**)node != 0) { char* nxt = *(char**)node; *(u32*)node = 0; node = nxt; }
    *(u32*)(s + 0x3c) = 0; *(u32*)(s + 0x38) = 0; *(u32*)(s + 0x40) = 0;

    ((Mutex*)(s + 4))->Destroy();
}

// ---------------------------------------------------------------------------
// rw::core::filesys::Stream::Create
// ---------------------------------------------------------------------------
// @ 0x011e7910
void* Stream_Create(u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6)
{
    StreamImpl* impl = (StreamImpl*)StreamImpl_operator_new(0x210);
    if (impl != 0)
        impl = impl->Init(a1, a2, a3, a4, a5, a6);
    return *(void**)((char*)impl + 0x44);
}

// ---------------------------------------------------------------------------
// list-B push (reuses the free head node, else allocates 0x10)
// ---------------------------------------------------------------------------
// @ 0x011e7950
void __fastcall Stream_ListPushBack(void* self, int, u32 a, u32 b, u32 c)
{
    char* impl = *(char**)((char*)self + 4);
    char* node = *(char**)(impl + 0x38);
    if (*(u32*)(node + 4) == 0)
    {
        if (node != 0)
        {
            if (node == *(char**)(impl + 0x3c)) { *(u32*)(impl + 0x38) = 0; *(u32*)(impl + 0x3c) = 0; }
            else *(char**)(impl + 0x38) = *(char**)node;
            *(int*)(impl + 0x40) -= 1;
            *(u32*)node = 0;
        }
        *(u32*)(node + 4) = b;
        *(u32*)(node + 8) = c;
        *(u32*)(node + 0xc) = a;
    }
    else
    {
        node = (char*)StreamImpl_operator_new(0x10);
        if (node == 0)
            node = 0;
        else
        {
            *(u32*)(node + 4) = b;
            *(u32*)node = 0;
            *(u32*)(node + 8) = c;
            *(u32*)(node + 0xc) = a;
        }
    }
    char* tail = *(char**)(impl + 0x3c);
    *(u32*)node = 0;
    *(char**)(impl + 0x3c) = node;
    *(int*)(impl + 0x40) += 1;
    if (tail == 0) *(char**)(impl + 0x38) = node;
    else *(char**)tail = node;
}

// ---------------------------------------------------------------------------
// list-C append (allocates a 0x14 stream wrapper {next, impl, seq, 0, 0})
// ---------------------------------------------------------------------------
// @ 0x011e79f0
void __fastcall Stream_ListAppend(void* self, int)
{
    char* impl = *(char**)((char*)self + 4);
    char* node = (char*)StreamImpl_operator_new(0x14);
    if (node != 0)
    {
        u32 seq = *(u32*)(impl + 0x4c);
        *(u32*)node = 0;
        *(void**)(node + 4) = impl;
        *(u32*)(node + 8) = seq + 1;
        *(u32*)(node + 0xc) = 0;
        *(u32*)(node + 0x10) = 0;
    }
    else
        node = 0;
    char* tail = *(char**)(impl + 0x48);
    *(u32*)node = 0;
    *(int*)(impl + 0x4c) += 1;
    *(char**)(impl + 0x48) = node;
    if (tail == 0) *(char**)(impl + 0x44) = node;
    else *(char**)tail = node;
}

// ---------------------------------------------------------------------------
// rw::core::filesys::Stream::CancelRequest
// ---------------------------------------------------------------------------
// @ 0x011e7a40
void __fastcall Stream_CancelRequest(void* self, int, u32 requestId)
{
    char* impl = *(char**)((char*)self + 4);
    ((Mutex*)(impl + 4))->Lock(g_fsWaitName);
    u32 idx = requestId & 0xff;
    if ((int)idx < *(int*)(impl + 0x34))
    {
        char* rec = *(char**)(impl + 0x30) + idx * 0x138;
        if (requestId == *(u32*)rec)
        {
            u32 st = *(u32*)(rec + 4);
            if (st != 0 && st != 4)
            {
                if (st == 1)
                {
                    ((StreamImpl*)impl)->FreeRequest(rec);
                    ((Mutex*)(impl + 4))->Unlock();
                    return;
                }
                *(u32*)(rec + 4) = 4;
                char* node = *(char**)(impl + 0x50);
                bool any = false;
                if (node != 0)
                {
                    do
                    {
                        if (*(u32*)(node + 4) == *(u32*)rec && *(u32*)(node + 0x10) == 0)
                        {
                            u32 n = *(u32*)(node + 0x14);
                            char* w = *(char**)(impl + 0x44);
                            while (--n != 0) w = *(char**)w;
                            any = true;
                            *(u32*)(w + 0xc) -= *(u32*)(node + 8);
                            DecBufferUsage(*(u32*)(node + 8));
                            *(u32*)(node + 0x10) = 2;
                        }
                        node = *(char**)node;
                    } while (node != 0);

                    if (any)
                    {
                        for (char* w = *(char**)(impl + 0x44); w != 0; w = *(char**)w)
                        {
                            if (*(int*)(w + 0xc) < 1)
                                *(u32*)(w + 0x10) = 0;
                            else if (*(int*)(*(char**)(w + 0x10) + 0x10) != 0)
                            {
                                char* p = *(char**)(impl + 0x50);
                                while (*(u32*)(p + 0x14) != *(u32*)(w + 8) || *(u32*)(p + 0x10) != 0)
                                    p = *(char**)p;
                                *(u32*)(w + 0x10) = (u32)(size_t)p;
                            }
                        }
                    }
                }
            }
        }
    }
    ((Mutex*)(impl + 4))->Unlock();
}

// ---------------------------------------------------------------------------
// rw::core::filesys::Stream::Kill
// ---------------------------------------------------------------------------
// @ 0x011e7b70
void __fastcall Stream_Kill(void* self, int)
{
    char* impl = *(char**)((char*)self + 4);
    char* node = *(char**)(impl + 0x94);
    if (node != 0)
    {
        while (*(u32*)(node + 4) == 1 || *(u32*)(node + 4) == 2)
        {
            Stream_CancelRequest(self, 0, *(u32*)node);
            node = *(char**)(impl + 0x94);
        }
        while (*(char**)(impl + 0x8c) != *(char**)(impl + 0x90))
            ((StreamImpl*)impl)->FreeRequest(*(char**)(impl + 0x8c));
        *(u32*)(*(char**)(impl + 0x90) + 4) = 4;
        for (char* w = *(char**)(impl + 0x44); w != 0; w = *(char**)w)
            *(u32*)(w + 0xc) = 0;

        u32 old = *(u32*)(impl + 0x7c);
        ((Mutex*)(impl + 4))->Lock(g_fsWaitName);
        u32 cur = *(u32*)(impl + 0x7c);
        *(u32*)(impl + 0x7c) = cur - old;
        ((Mutex*)(impl + 4))->Unlock();

        u32 thr = *(u32*)(impl + 0x74);
        if ((int)old >= (int)thr && (int)(cur - old) < (int)thr)
        {
            *(u8*)(impl + 0x78) = 1;
            if (*(u32*)(impl + 0x68) == 1)
                ((AsyncOp*)(impl + 0x1b0))->SetPriority(*(int*)(impl + 0x70));
        }
        for (char* w = *(char**)(impl + 0x50); w != 0; w = *(char**)w)
            *(u32*)(w + 0x10) = 2;
        if (*(u32*)(impl + 0x68) == 2)
            *(u32*)(impl + 0x68) = 0;
    }
}

// ---------------------------------------------------------------------------
// rw::core::filesys::Stream::ReleaseChunk
// ---------------------------------------------------------------------------
// @ 0x011e7c70
void __fastcall Stream_ReleaseChunk(void* self, int, char* chunk)
{
    char* impl = *(char**)((char*)self + 4);
    *(u32*)(chunk + 0xc) = 2;
    DecBufferUsage(*(u32*)(chunk + 4));
    ((Mutex*)(impl + 4))->Lock(g_fsWaitName);
    u32 st = *(u32*)(impl + 0x68);
    if (st == 2)
        *(u32*)(impl + 0x68) = 1;
    ((Mutex*)(impl + 4))->Unlock();
    if (st == 2)
    {
        if (*(char*)(impl + 0x78))
            RestartStream(impl, *(u32*)(impl + 0x70));
        else
            RestartStream(impl, *(u32*)(impl + 0x6c));
    }
}

// ---------------------------------------------------------------------------
// rw::core::filesys::Stream destructor
// ---------------------------------------------------------------------------
// @ 0x011e7cf0
void __fastcall Stream_Destroy(void* self, int)
{
    char* impl = *(char**)((char*)self + 4);
    Stream_Kill(self, 0);
    while (*(u32*)(impl + 0x68) == 1)
        ThreadSleep(g_fsSleepName);
    *(u32*)impl = 0;
    if (*(void**)(impl + 0x1a4) != 0)
    {
        ((AsyncOp*)(impl + 0x1b0))->Close(*(IoStream**)(impl + 0x1a4), 0, 0, 0);
        ((AsyncOp*)(impl + 0x1b0))->GetStatus(*(const u32*)g_fsWaitName);
    }
    StreamImpl_ClearLists(impl, 0);
    FreePtr(impl);
}

// ---------------------------------------------------------------------------
// rw::core::filesys::AsyncOp ctor / Reset
// ---------------------------------------------------------------------------
// @ 0x011e84f0
AsyncOp::AsyncOp()
{
    mStatus = -3;
    next = 0;
    mCancelled = false;
    mIsRead = false;
    mPriority = 0;
    mFileHandle = 0;
    mContext = 0;
    mCallbackFunc = (void (*)(AsyncOp*))NoOpCallback;
    mValue = 0;
    mAmount = 0;
    mData = 0;
    mTotalBytes = 0;
    mDevice = 0;
    mExecFunc = 0;
}

// @ 0x011e8530
void AsyncOp::Reset()
{
    mFileHandle = 0;
    mContext = 0;
    mData = 0;
    mDevice = 0;
    next = 0;
}

// ---------------------------------------------------------------------------
// AsyncOp read exec callback
// ---------------------------------------------------------------------------
// @ 0x011e8550
int AsyncOpDoRead(AsyncOp* op)
{
    IoStream* stream = (IoStream*)op->mFileHandle;
    stream->mpContext->mLeadPos = stream->mpIo->s1c(stream->mDriverKey, op->mValue, 0,
                                                    stream->mpContext->mpDevice->mDriver,
                                                    stream->mpContext->mDriverKey);
    u32 want = stream->mpIo->s2c();
    char* fs = (char*)GetFsManager();
    if ((u32)op->mAmount < want)
        want = (u32)op->mAmount;
    if (*(u32*)(fs + 0xc) <= want)
        want = *(u32*)(fs + 0xc);
    u32 got = (u32)stream->mpIo->s14(stream->mDriverKey, op->mData, want,
                                     stream->mpContext->mpDevice->mDriver,
                                     stream->mpContext->mDriverKey);
    op->mAmount -= got;
    op->mValue += got;
    op->mTotalBytes += got;
    op->mData = (char*)op->mData + got;
    if (op->mAmount != 0 && got == want)
    {
        ((Device*)op->mDevice)->InsertOp(op);
        return 0;
    }
    return 1;
}
