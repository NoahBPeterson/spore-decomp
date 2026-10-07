// Slice s00929a70 (bfs4 #15), 32-bit MSVC 2008.
// EA::CallbackSystem (timer callback + processor thread), EA::Clipboard, and a split-file stream writer.
// Names inferred (no PDB types for CallbackSystem); offsets confirmed against the disassembly.
#include "types.h"
#include <intrin.h>
#include <new>

typedef unsigned int size_t;

extern "C" void* memcpy(void*, const void*, size_t);
extern "C" void* memset(void*, int, size_t);
void* operator new(size_t, const char*, int, int, int, int);
void  EA_operator_delete(void* p);                         // 0xf47380
void  EA_operator_delete_cdecl(void* p);

// ---------------------------------------------------------------------------
// EA::Thread / EA::Stopwatch / EA::Random (external)
// ---------------------------------------------------------------------------
extern unsigned g_timeNone;                                // 0x143e340
extern unsigned g_timeClip;                                // 0x143e3a0

namespace EA {

namespace Thread {
struct MutexParameters {
    unsigned pad[5];
    MutexParameters(bool intraProcess, const char* name);  // 0x921e00
};
struct Mutex {
    unsigned __int64 data[6];
    Mutex() {}
    Mutex(const MutexParameters* p, bool bDefault);        // 0x9222a0
    ~Mutex();                                              // 0x922130
    bool Init(const MutexParameters* p);                   // 0x922150
    int  Lock(unsigned* pTimeout);                         // 0x9221b0
    int  Unlock();                                         // 0x922270
};
struct ThreadParameters {
    unsigned pad[5];
    const char* mpName;                                    // +0x14
    ThreadParameters();                                    // 0x922900
};
struct IRunnable {
    virtual ~IRunnable() {}
    virtual int Run(void* ctx) = 0;
};
struct Thread {
    void Wake();                                           // 0x922d10
    void WaitForEnd(unsigned* pTimeout, int a);            // 0x922940
    void Begin(IRunnable* r, void* ctx, ThreadParameters* p, int prio);  // 0x9231a0
};
Thread* Thread_Create();                                   // 0x922bd0
int  Thread_DefaultPriority();                             // 0x922930
void Thread_Free(Thread* t);                               // 0x923330
void ThreadSleep(unsigned* pMs);                           // 0x921df0
}

struct Stopwatch {
    Stopwatch(int units, bool run);                        // 0x93a560
    unsigned __int64 GetElapsedTime();                     // 0x93a5e0
};

namespace Random {
struct RandomLinearCongruential {
    unsigned mnSeed;
    RandomLinearCongruential(unsigned seed) { SetSeed(seed); }
    void SetSeed(unsigned s);                              // 0x936090
    unsigned RandomUint32Uniform(unsigned limit);          // 0xa68fb0
};
}

} // namespace EA

extern const float kFloatOne;                              // 0x1485720

// ---------------------------------------------------------------------------
// CallbackSystem
// ---------------------------------------------------------------------------
namespace EA { namespace CallbackSystem {

struct IRefCount {
    virtual void AddRef() = 0;
    virtual void Release() = 0;
};

struct Callback;
struct CallbackProcessor;

extern CallbackProcessor* g_pProcA;    // 0x1668eec  (polled, no thread)
extern CallbackProcessor* g_pProcB;    // 0x1668ef0  (own thread)
extern Stopwatch*         g_pStopwatch;  // 0x1668ef4
extern int                g_counterA;    // 0x1668ef8
extern int                g_counterB;    // 0x1668efc

typedef void (__cdecl *CallbackFn)(void* ctx, int time, int delta);

struct Entry {
    int nextTime;
    int lastTime;
    Callback* cb;
    bool oneShot;
    char pad1, pad2, pad3;
};

struct EntryVec {
    Entry* b;
    Entry* e;
    Entry* c;
    EntryVec() : b(0), e(0), c(0) {}
    void reserve(unsigned n);                              // 0x929ef0
    void DoInsert(Entry* pos, const Entry* v);             // 0x92a100
    ~EntryVec()
    {
        if (b && ((int*)b)[-1] != 0) {
            EA_operator_delete_cdecl(b);
        }
    }
    void erase(Entry* first, Entry* last)
    {
        Entry* const lastSrc = e;
        Entry* dest = first;
        Entry* src = last;
        for (; src != lastSrc; ++src, ++dest) {
            *dest = *src;
        }
        e = e - (last - first);
    }
};

struct Clock {
    int now;
    int* pNextDue;
};

struct CallbackProcessor : EA::Thread::IRunnable {
    EntryVec mEntries;                    // +4
    int pad10[2];                         // +0x10 (vector allocator etc.)
    EA::Stopwatch* mpStopwatch;           // +0x18
    int* mpCounterA;                      // +0x1c
    int* mpCounterB;                      // +0x20
    bool mbRunning;                       // +0x24
    bool mbThreaded;                      // +0x25
    EA::Random::RandomLinearCongruential mRandom;  // +0x28
    float mfScale;                        // +0x2c
    int mLast0;                           // +0x30
    int mLast1;                           // +0x34
    int mNextDue0;                        // +0x38
    int mNextDue1;                        // +0x3c
    EA::Thread::Mutex mMutex;             // +0x40
    EA::Thread::Thread* mpThread;         // +0x70

    CallbackProcessor(int* ca, int* cb, EA::Stopwatch* sw, bool threaded);   // 0x929f80
    virtual ~CallbackProcessor();                                           // 0x92a4c0
    virtual int Run(void* ctx);                                             // 0x92a220
    bool Add(Callback* cb, bool oneShot);                                   // 0x92a5d0
    bool Remove(Callback* cb);                                              // 0x929bf0
};

struct Callback {
    int mProc;               // +4  (1 = threaded processor)
    int mTimeType;           // +8
    int mPeriod;             // +0xc
    int mJitter;             // +0x10
    CallbackFn mpFn;         // +0x14
    void* mpCtx;             // +0x18
    IRefCount* mpObj;        // +0x1c
    bool mbActive;           // +0x20

    virtual ~Callback();                                                    // 0x929d50 (body)
    Callback();                                                             // 0x929e00
    Callback(CallbackFn fn, void* ctx, int period, int jitter, int proc, int timeType, IRefCount* obj);  // 0x929e70
    bool Set(CallbackFn fn, void* ctx, IRefCount* obj);                     // 0x929da0
    inline void SetObj(IRefCount* obj)
    {
        IRefCount* old = mpObj;
        if (obj != old) {
            if (obj) {
                obj->AddRef();
            }
            mpObj = obj;
            if (old) {
                old->Release();
            }
        }
    }
    bool Cancel();                                                          // 0x929c60
    bool Schedule(bool oneShot);                                            // 0x92a7a0
    bool SetProcessor(int proc);                                            // 0x92a7d0
};

void CallbackCancel(Callback* cb);                                          // 0x929d10

inline CallbackProcessor* ProcFor(int proc)
{
    CallbackProcessor* p = g_pProcA;
    if (proc == 1) {
        p = g_pProcB;
    }
    return p;
}

// 0x929bd0
bool Update()
{
    g_pProcA->Run(0);
    return true;
}

// 0x929bf0
bool CallbackProcessor::Remove(Callback* cb)
{
    EA::Thread::Mutex* m = &mMutex;
    m->Lock(&g_timeNone);
    unsigned n = (unsigned)(mEntries.e - mEntries.b);
    unsigned i = 0;
    if (n > 0) {
        Entry* p = mEntries.b;
        while (p->cb != cb) {
            ++i;
            ++p;
            if (n <= i) {
                m->Unlock();
                return true;
            }
        }
        mEntries.b[i].cb = 0;
    }
    m->Unlock();
    return true;
}

// 0x929c60
bool Callback::Cancel()
{
    if (mbActive) {
        ProcFor(mProc)->Remove(this);
        mbActive = false;
        SetObj(0);
    }
    return true;
}

// 0x929ca0
bool Shutdown()
{
    if (g_pStopwatch) {
        if (g_pProcB) {
            delete g_pProcB;
        }
        g_pProcB = 0;
        if (g_pProcA) {
            delete g_pProcA;
        }
        g_pProcA = 0;
        _InterlockedExchange((long*)&g_counterA, 0);
        if (g_pStopwatch) {
            EA_operator_delete_cdecl(g_pStopwatch);
        }
        g_pStopwatch = 0;
    }
    return true;
}

// 0x929d10
void CallbackCancel(Callback* cb)
{
    cb->Cancel();
}

// 0x929d50
Callback::~Callback()
{
    Cancel();
    if (mpObj) {
        mpObj->Release();
    }
}

// 0x929da0
bool Callback::Set(CallbackFn fn, void* ctx, IRefCount* obj)
{
    if (fn == 0) {
        mpFn = (CallbackFn)CallbackCancel;
        mpCtx = this;
    } else {
        mpFn = fn;
        mpCtx = ctx;
    }
    SetObj(obj);
    return true;
}

// 0x929e00
Callback::Callback()
    : mProc(2), mTimeType(0), mPeriod(1000), mJitter(500), mpObj(0), mbActive(false)
{
    Set(0, 0, 0);
}

// @ 0x00929e70
Callback::Callback(CallbackFn fn, void* ctx, int period, int jitter, int proc, int timeType, IRefCount* obj)
    : mProc(proc), mTimeType(timeType), mPeriod(period), mJitter(jitter), mpObj(0), mbActive(false)
{
    Set(fn, ctx, obj);
}

// 0x929f80
CallbackProcessor::CallbackProcessor(int* ca, int* cb, EA::Stopwatch* sw, bool threaded)
    : mpStopwatch(sw), mpCounterA(ca), mpCounterB(cb), mbRunning(false), mbThreaded(threaded),
      mRandom((unsigned)-1), mfScale(kFloatOne), mLast0(0), mLast1(0), mNextDue0(0), mNextDue1(0),
      mMutex(0, true), mpThread(0)
{
    mEntries.reserve(0x20);
    EA::Thread::MutexParameters params(true, 0);
    mMutex.Init(&params);
    mbRunning = true;
}

// 0x92a020
bool Init()
{
    if (g_pStopwatch == 0) {
        void* m = operator new(0x18, "CallbackSystem/Stopwatch", 0, 0, 0, 0);
        if (m) {
            g_pStopwatch = new (m) EA::Stopwatch(4, true);
        } else {
            g_pStopwatch = 0;
        }
        void* p1 = operator new(0x78, "CallbackSystem/CallbackProcessor", 0, 0, 0, 0);
        if (p1) {
            g_pProcB = new (p1) CallbackProcessor(&g_counterA, &g_counterB, g_pStopwatch, true);
        } else {
            g_pProcB = 0;
        }
        void* p2 = operator new(0x78, "CallbackSystem/CallbackProcessor", 0, 0, 0, 0);
        if (p2) {
            g_pProcA = new (p2) CallbackProcessor(&g_counterA, &g_counterB, g_pStopwatch, false);
            return true;
        }
        g_pProcA = 0;
    }
    return true;
}

// 0x92a220
int CallbackProcessor::Run(void* ctx)
{
    (void)ctx;
    if (mbRunning) {
        do {
            mMutex.Lock(&g_timeNone);
            _InterlockedExchangeAdd((long*)mpCounterA, 1);
            if (mEntries.b != mEntries.e) {
                int c0 = _InterlockedExchangeAdd((long*)mpCounterA, 0);
                int now = (int)mpStopwatch->GetElapsedTime();
                int c1 = _InterlockedExchangeAdd((long*)mpCounterB, 0);
                if (mbThreaded && mLast0 + 1000 < now) {
                    mfScale = (float)(now - mLast0) / (float)(c0 - mLast1);
                    mLast0 = now;
                    mLast1 = c0;
                }
                int unused = 0;
                Clock k0, k1, k2;
                k0.now = now;
                k0.pNextDue = &mNextDue0;
                k1.now = c0;
                k1.pNextDue = &mNextDue1;
                k2.now = c1;
                k2.pNextDue = &unused;
                Entry* e = mEntries.b;
                while (e != mEntries.e) {
                    Callback* cb = e->cb;
                    Entry* next = e + 1;
                    Clock* pc = 0;
                    if (cb) {
                        switch (cb->mTimeType) {
                        case 0: pc = &k0; break;
                        case 1: pc = &k1; break;
                        case 2: pc = &k2; break;
                        }
                        int t = pc->now;
                        if (t >= e->nextTime) {
                            if (cb->mpFn) {
                                cb->mpFn(cb->mpCtx, t, t - e->lastTime);
                            }
                            if (e->cb == cb) {
                                e->lastTime = t;
                                if (!e->oneShot) {
                                    e->nextTime = cb->mPeriod + t;
                                    int j = cb->mJitter;
                                    if (j) {
                                        e->nextTime += (int)mRandom.RandomUint32Uniform(j * 2) - j;
                                    }
                                    if (mbThreaded) {
                                        int nt = e->nextTime;
                                        if (*pc->pNextDue > nt) {
                                            *pc->pNextDue = nt;
                                        }
                                    }
                                } else {
                                    cb->Cancel();
                                }
                            }
                        }
                    } else {
                        if (next < mEntries.e) {
                            Entry* s = next;
                            Entry* d = e;
                            do {
                                *d = *s;
                                ++s;
                                ++d;
                            } while (s != mEntries.e);
                        }
                        mEntries.e = mEntries.e - 1;
                        next = e;
                    }
                    e = next;
                }
            }
            mMutex.Unlock();
            if (!mbThreaded) {
                break;
            }
            int sleepMs = 0x7fffffff;
            if (mEntries.b != mEntries.e) {
                int el = (int)mpStopwatch->GetElapsedTime();
                int a = mNextDue0 - el;
                int b = (int)((float)(mNextDue1 - el) * mfScale);
                int v = (a < b) ? a : b;
                if (v < 0) {
                    v = 0;
                }
                sleepMs = v / 2;
            }
            if (mpThread) {
                unsigned ms = (unsigned)sleepMs;
                EA::Thread::ThreadSleep(&ms);
            }
        } while (mbRunning);
    }
    return 0;
}

// 0x92a4c0
CallbackProcessor::~CallbackProcessor()
{
    mMutex.Lock(&g_timeNone);
    mbRunning = false;
    mMutex.Unlock();
    if (mpThread) {
        mpThread->Wake();
        mpThread->WaitForEnd(&g_timeNone, 0);
        EA::Thread::Thread_Free(mpThread);
        mpThread = 0;
    }
    Entry* end = mEntries.e;
    for (Entry* p = mEntries.b; p != end; ++p) {
        Callback* cb = p->cb;
        if (cb && cb->mbActive) {
            cb->Cancel();
        }
    }
    mEntries.erase(mEntries.b, mEntries.e);
    // mMutex, then mEntries dtors run here
}

// 0x92a5d0
bool CallbackProcessor::Add(Callback* cb, bool oneShot)
{
    mMutex.Lock(&g_timeNone);
    int count = (int)(mEntries.e - mEntries.b);
    int freeIdx = -1;
    int i = 0;
    Entry* slot;
    int dummy = 0;
    int* pDue;
    int now = 0;
    bool found = false;
    Entry* base = mEntries.b;
    for (i = 0; i < count; ++i) {
        Callback* c = base[i].cb;
        if (c == cb) {
            found = true;
            break;
        }
        if (c == 0 && freeIdx < 0) {
            freeIdx = i;
        }
    }
    if (!found) {
        if (freeIdx < 0) {
            Entry tmp;
            tmp.cb = 0;
            if (mEntries.e < mEntries.c) {
                Entry* q = mEntries.e;
                mEntries.e = q + 1;
                if (q) {
                    *q = tmp;
                }
            } else {
                mEntries.DoInsert(mEntries.e, &tmp);
            }
            slot = mEntries.e - 1;
        } else {
            slot = base + freeIdx;
        }
        slot->cb = cb;
        slot->oneShot = oneShot;
        pDue = &dummy;
        if (cb->mTimeType == 0) {
            now = (int)mpStopwatch->GetElapsedTime();
            pDue = &mNextDue0;
        } else if (cb->mTimeType == 1) {
            now = _InterlockedExchangeAdd((long*)mpCounterA, 0);
            pDue = &mNextDue1;
        }
        slot->nextTime = cb->mPeriod + now;
        slot->lastTime = now;
        if (cb->mJitter) {
            int j = cb->mJitter;
            slot->nextTime += (int)mRandom.RandomUint32Uniform(j * 2) - j;
        }
        if (mbThreaded) {
            if (*pDue < slot->nextTime) {
                *pDue = slot->nextTime;
            }
        }
    }
    if (mbThreaded) {
        if (mpThread == 0) {
            mpThread = EA::Thread::Thread_Create();
            EA::Thread::ThreadParameters params;
            params.mpName = "CallbackProcessor";
            int prio = EA::Thread::Thread_DefaultPriority();
            mpThread->Begin(this, 0, &params, prio);
            mMutex.Unlock();
            return true;
        }
        unsigned __int64 el = mpStopwatch->GetElapsedTime();
        if (el > (unsigned)mNextDue0 ||
            _InterlockedExchangeAdd((long*)mpCounterA, 0) > mNextDue1) {
            mpThread->Wake();
        }
    }
    mMutex.Unlock();
    return true;
}

// 0x92a7a0
bool Callback::Schedule(bool oneShot)
{
    if (!mbActive) {
        mbActive = ProcFor(mProc)->Add(this, oneShot);
    }
    return true;
}

// 0x92a7d0
bool Callback::SetProcessor(int proc)
{
    if (proc != mProc) {
        bool wasActive = mbActive;
        if (wasActive) {
            Cancel();
        }
        mProc = proc;
        if (wasActive && !mbActive) {
            mbActive = ProcFor(proc)->Add(this, false);
        }
    }
    return true;
}

}} // namespace EA::CallbackSystem

// ---------------------------------------------------------------------------
// 0x92a860: intrusive release helper (refcount at +8, deletes when it would reach zero)
// ---------------------------------------------------------------------------
struct RefHolder {
    virtual ~RefHolder() {}
    int pad4;
    unsigned mnRefCount;         // +8
    int Release();
};
// 0x92a860
int RefHolder::Release()
{
    if (mnRefCount > 1) {
        mnRefCount = mnRefCount - 1;
        return mnRefCount;
    }
    delete this;
    return 0;
}

// ---------------------------------------------------------------------------
// EA::Clipboard
// ---------------------------------------------------------------------------
namespace EA { namespace Clipboard {

struct IData {
    virtual void slot0() = 0;
    virtual void AddRef() = 0;
    virtual void Release() = 0;
};

struct DataText16 : IData {
    unsigned mnType;       // +4
    unsigned mnRefCount;   // +8
    unsigned mnDataSize;   // +0xc
    unsigned char mData[2];// +0x10
    DataText16(const wchar_t* s, int len);                      // 0x92aae0
    virtual void slot0();
    virtual void AddRef();
    virtual void Release();
};

struct SPMemPool {
    void* LockedAlloc(unsigned size, int a, int b, int c, int d, int e);   // 0x9289f0
};
extern SPMemPool* g_pMemPool;     // 0x16c8b44

struct DataInfo {
    unsigned mnType;
    IData* mpData;
};

struct Clipboard {
    bool mbInitialized;       // +0
    unsigned mnId;            // +4
    void* mpOSData;           // +8
    DataInfo mDataInfoArray[33];  // +0xc
    EA::Thread::Mutex mMutex; // +0x118
    int mnMaxTypes;           // +0x148
    bool mbOSSync;            // +0x14c

    Clipboard();                                                // 0x92a880
    bool GetClipboardData(unsigned type, IData** out);          // 0x92a8d0
    int  Clear(unsigned type);                                  // 0x92a940
};

extern "C" {
__declspec(dllimport) int   __stdcall OpenClipboard(void*);
__declspec(dllimport) int   __stdcall EmptyClipboard();
__declspec(dllimport) int   __stdcall CloseClipboard();
__declspec(dllimport) void* __stdcall SetClipboardData(unsigned fmt, void* h);
__declspec(dllimport) void* __stdcall GlobalAlloc(unsigned flags, size_t bytes);
__declspec(dllimport) void* __stdcall GlobalLock(void* h);
__declspec(dllimport) int   __stdcall GlobalUnlock(void* h);
__declspec(dllimport) void* __stdcall GlobalFree(void* h);
}

struct Win32Clipboard {
    bool mbEnabled;                 // +0
    int mnGettingText;              // +4
    int mnSettingText;              // +8
    bool WriteText(const wchar_t* text, int len);               // 0x92aa20
};

// 0x92a880
Clipboard::Clipboard()
    : mbInitialized(false), mnId(0), mpOSData(0), mMutex(0, true), mnMaxTypes(1000), mbOSSync(true)
{
    memset(mDataInfoArray, 0, 0x108);
    mDataInfoArray[32].mnType = 0;
    mDataInfoArray[32].mpData = 0;
}

// 0x92a8d0
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

// 0x92a940
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

// 0x92aa20
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

// 0x92aae0
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

// 0x92ab60
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

}} // namespace EA::Clipboard

// ---------------------------------------------------------------------------
// 0x929a70: split-file stream writer (a list of streams, each capped at 1 GiB)
// ---------------------------------------------------------------------------
namespace EA { namespace IO {

struct IStream {
    virtual void s0() = 0;
    virtual void s1() = 0;
    virtual void s2() = 0;
    virtual void s3() = 0;
    virtual void s4() = 0;
    virtual int  GetError() = 0;                       // +0x14
    virtual void s6() = 0;
    virtual void s7() = 0;
    virtual void s8() = 0;
    virtual unsigned GetPosition(int a) = 0;           // +0x24
    virtual void SetPosition(int a, int b) = 0;        // +0x28
    virtual void s11() = 0;
    virtual void s12() = 0;
    virtual void s13() = 0;
    virtual bool Write(const void* data, unsigned size) = 0;   // +0x38
};

struct MultiStreamWriter {
    IStream** mpBegin;       // +0
    IStream** mpEnd;         // +4
    char pad8[0xc];
    unsigned mCurrent;       // +0x14
    unsigned mPosition;      // +0x18
    char pad1c[0x418];
    unsigned mFlags;         // +0x434
    char pad438[0xc];
    int mError;              // +0x444

    bool AddNextStream();    // 0x929310
    void Cleanup();          // 0x9290a0
    bool Write(const void* data, unsigned size);        // 0x929a70
};

bool MultiStreamWriter::Write(const void* data, unsigned size)
{
    if (mpBegin == mpEnd) {
        mError = -2;
        return false;
    }
    if (!(mFlags & 2)) {
        mError = (int)0xcfde0006;
        return false;
    }
    const char* p = (const char*)data;
    while (true) {
        if (size <= 0x40000000 && mPosition + size <= 0x40000000) {
            if (!mpBegin[mCurrent]->Write(p, size)) {
                mError = mpBegin[mCurrent]->GetError();
                Cleanup();
                return false;
            }
            mPosition += size;
            return true;
        }
        unsigned room = 0x40000000 - mPosition;
        if (room != 0) {
            if (!mpBegin[mCurrent]->Write(p, room)) {
                mError = mpBegin[mCurrent]->GetError();
                mPosition = mpBegin[mCurrent]->GetPosition(0);
                return false;
            }
            mPosition += room;
            p += room;
            size -= room;
        }
        if (mpBegin + mCurrent + 1 == mpEnd && !AddNextStream()) {
            mPosition = mpBegin[mCurrent]->GetPosition(0);
            return false;
        }
        ++mCurrent;
        mPosition = 0;
        mpBegin[mCurrent]->SetPosition(0, 0);
    }
}

}} // namespace EA::IO
