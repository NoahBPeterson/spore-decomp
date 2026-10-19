// src/game/UTFSpore_Win32/EACallback.cpp -- migrated from slice(s) s00929a70 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACallback.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"
#include "EA/Thread/Thread.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned g_timeNone;                                // 0x143e340
extern const float kFloatOne;                              // 0x1485720
#include <intrin.h>
#include <new>

// ---- items of slice s00929a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t, const char*, int, int, int, int);
void  EA_operator_delete_cdecl(void* p);
extern unsigned g_timeNone;                                // 0x143e340
namespace EA {
namespace Thread {
struct MutexParameters {
    unsigned pad[5];
    MutexParameters(bool intraProcess, const char* name);  // 0x921e00
};
}
}
namespace EA { namespace CallbackSystem { bool Init(); }}  // 0x0092a020 (defined below; used by a stub's inline body)
namespace EA {
namespace Thread {
struct Mutex_s0092_9a70 {
    unsigned __int64 data[6];
    Mutex_s0092_9a70() {}
    Mutex_s0092_9a70(const MutexParameters* p, bool bDefault);        // 0x9222a0
    ~Mutex_s0092_9a70();                                              // 0x922130
    bool Init(const MutexParameters* p);                   // 0x922150
    int  Lock(unsigned* pTimeout);                         // 0x9221b0
    int  Unlock();                                         // 0x922270
};
}
}
namespace EA {
namespace Thread {
struct ThreadParameters {
    unsigned pad[5];
    const char* mpName;                                    // +0x14
    ThreadParameters();                                    // 0x922900
};
}
}
namespace EA {
namespace Thread {
struct IRunnable {
    virtual ~IRunnable() {}
    virtual int Run(void* ctx) = 0;
};
}
}
namespace EA {
namespace Thread {
struct Thread_s0092_9a70 {
    void Wake();                                           // 0x922d10
    void WaitForEnd(unsigned* pTimeout, int a);            // 0x922940
    void Begin(IRunnable* r, void* ctx, ThreadParameters* p, int prio);  // 0x9231a0
};
}
}
namespace EA {
namespace Thread {
void ThreadSleep(unsigned* pMs);                           // 0x921df0
}
}
namespace EA {
struct Stopwatch_s0092_9a70 {
    Stopwatch_s0092_9a70(int units, bool run);                        // 0x93a560
    unsigned __int64 GetElapsedTime();                     // 0x93a5e0
};
}
namespace EA {
namespace Random {
struct RandomLinearCongruential_s0092_9a70 {
    unsigned mnSeed;
    RandomLinearCongruential_s0092_9a70(unsigned seed) { SetSeed(seed); }
    void SetSeed(unsigned s);                              // 0x936090
    unsigned RandomUint32Uniform(unsigned limit);          // 0xa68fb0
};
}
}
extern const float kFloatOne;                              // 0x1485720
namespace EA {
namespace CallbackSystem {
struct IRefCount {
    virtual void AddRef() = 0;
    virtual void Release() = 0;
};
}
}
namespace EA {
namespace CallbackSystem {
struct Callback;
}
}
namespace EA {
namespace CallbackSystem {
struct CallbackProcessor;
}
}
namespace EA {
namespace CallbackSystem {
extern CallbackProcessor* g_pProcA;    // 0x1668eec  (polled, no thread)
}
}
namespace EA {
namespace CallbackSystem {
extern CallbackProcessor* g_pProcB;    // 0x1668ef0  (own thread)
}
}
namespace EA {
namespace CallbackSystem {
extern Stopwatch_s0092_9a70*         g_pStopwatch;  // 0x1668ef4
}
}
namespace EA {
namespace CallbackSystem {
extern int                g_counterA;    // 0x1668ef8
}
}
namespace EA {
namespace CallbackSystem {
extern int                g_counterB;    // 0x1668efc
}
}
namespace EA {
namespace CallbackSystem {
typedef void (__cdecl *CallbackFn)(void* ctx, int time, int delta);
}
}
namespace EA {
namespace CallbackSystem {
struct Entry {
    int nextTime;
    int lastTime;
    Callback* cb;
    bool oneShot;
    char pad1, pad2, pad3;
};
}
}
namespace EA {
namespace CallbackSystem {
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
}
}
namespace EA {
namespace CallbackSystem {
struct Clock {
    int now;
    int* pNextDue;
};
}
}
namespace EA {
namespace CallbackSystem {
struct CallbackProcessor : EA::Thread::IRunnable {
    EntryVec mEntries;                    // +4
    int pad10[2];                         // +0x10 (vector allocator etc.)
    EA::Stopwatch_s0092_9a70* mpStopwatch;           // +0x18
    int* mpCounterA;                      // +0x1c
    int* mpCounterB;                      // +0x20
    bool mbRunning;                       // +0x24
    bool mbThreaded;                      // +0x25
    EA::Random::RandomLinearCongruential_s0092_9a70 mRandom;  // +0x28
    float mfScale;                        // +0x2c
    int mLast0;                           // +0x30
    int mLast1;                           // +0x34
    int mNextDue0;                        // +0x38
    int mNextDue1;                        // +0x3c
    EA::Thread::Mutex_s0092_9a70 mMutex;             // +0x40
    EA::Thread::Thread_s0092_9a70* mpThread;         // +0x70

    CallbackProcessor(int* ca, int* cb, EA::Stopwatch_s0092_9a70* sw, bool threaded);   // 0x929f80
    virtual ~CallbackProcessor();                                           // 0x92a4c0
    virtual int Run(void* ctx);                                             // 0x92a220
    bool Add(Callback* cb, bool oneShot);                                   // 0x92a5d0
    bool Remove(Callback* cb);                                              // 0x929bf0
};
}
}
namespace EA {
namespace CallbackSystem {
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
}
}
// ---- items of slice s00929a70 end

// @ 0x00929f80
namespace EA { namespace CallbackSystem {
CallbackProcessor::CallbackProcessor(int* ca, int* cb, EA::Stopwatch_s0092_9a70* sw, bool threaded)
: mpStopwatch(sw), mpCounterA(ca), mpCounterB(cb), mbRunning(false), mbThreaded(threaded),
      mRandom((unsigned)-1), mfScale(kFloatOne), mLast0(0), mLast1(0), mNextDue0(0), mNextDue1(0),
      mMutex(0, true), mpThread(0)
{
    mEntries.reserve(0x20);
    EA::Thread::MutexParameters params(true, 0);
    mMutex.Init(&params);
    mbRunning = true;
}
}}  // namespace EA::CallbackSystem

// @ 0x0092a020
namespace EA { namespace CallbackSystem {
bool Init()
{
    if (g_pStopwatch == 0) {
        void* m = operator new(0x18, "CallbackSystem/Stopwatch", 0, 0, 0, 0);
        if (m) {
            g_pStopwatch = new (m) EA::Stopwatch_s0092_9a70(4, true);
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
}}  // namespace EA::CallbackSystem

// @ 0x0092a220
namespace EA { namespace CallbackSystem {
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
}}  // namespace EA::CallbackSystem
