// Slice s0068e670: Simulator/EA job-lock, thread-mutex and small utility helpers
// (0x0068e670..0x0068f600). Module compiled /O2 /MD /Gy /EHsc /TP (no SSE).
#include "types.h"
#include <intrin.h>

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
extern "C" void __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" void* __cdecl MutexLock(void* self, void* name);       // 0x09221b0
extern "C" void* __cdecl MutexUnlock(void* self);                 // 0x0922270
extern "C" void  __cdecl HandleClose(void* h);                    // 0x0922610
extern "C" void* __cdecl SemaphorePost(void* self, int n);        // 0x0922740

// ---- global job-lock singleton accessors / callees (out-of-slice) ----
extern "C" int* __cdecl GetStatus(void* p);                       // 0x0690120
extern "C" void* __cdecl FUN_0068f950(void* p);                   // 0x068f950
extern "C" void* __cdecl FUN_006913c0(void* p);                   // 0x06913c0
extern "C" int*  __cdecl FUN_0068f4d0();                          // 0x068f4d0
extern "C" void* __cdecl FUN_0068f9f0(void* p, void* fn, void* a); // 0x068f9f0
extern "C" void* __cdecl FUN_0068f9b0(void* p);                   // 0x068f9b0
extern "C" void  __cdecl FUN_00753fb0(void* p);                   // 0x0753fb0

// =====================================================================
// @ 0x0068e670  job/event processor (partial)
// @ 0x0068e8a0  vector<bool>-style DoInsertValues wrapper (partial)
// @ 0x0068e8f0  bitmap alloc/init (partial)
// @ 0x0068e9a0  job-lock deserialize (partial)
// @ 0x0068eb50  job-lock serialize/setup (partial)
// @ 0x0068eca0  job-lock helper (partial)
// @ 0x0068ed70  job-lock helper (partial)
// @ 0x0068eef0  job-lock helper (partial)
// =====================================================================
extern "C" void FUN_68E670(void* a) { (void)a; }
extern "C" void FUN_68E8A0(void* a, uint32_t b, void* c) { (void)a; (void)b; (void)c; }
extern "C" void FUN_68E8F0(void* a, int b, int c, int d, int e) { (void)a; (void)b; (void)c; (void)d; (void)e; }
extern "C" int  FUN_68E9A0(void* a, void* b) { (void)a; (void)b; return 0; }
extern "C" void FUN_68EB50(void* a) { (void)a; }
extern "C" void FUN_68ECA0(void* a) { (void)a; }
extern "C" void FUN_68ED70(void* a) { (void)a; }
extern "C" void FUN_68EEF0(void* a) { (void)a; }

// =====================================================================
// @ 0x0068eff0  ctor: {vtbl, refcount, Mutex @+8, count @+0x38}
// =====================================================================
struct Mutex { uint32_t _[12]; void Lock(void*); void Unlock(); };
struct CAbility {
    void* vtbl;             // +0x00
    volatile int mRef;      // +0x04
    Mutex mMutex;           // +0x08
    int mCount;             // +0x38
    CAbility();
    ~CAbility();
};
CAbility::CAbility() {
    mRef = 0;
    mCount = 0;
}

// =====================================================================
// @ 0x0068f050  dtor
// =====================================================================
CAbility::~CAbility() {
    if (mCount != 0)
        GetStatus((void*)mCount);
}

// =====================================================================
// @ 0x0068f0b0  swap/replace a cJob under mutex
// =====================================================================
struct CJobHolder {
    uint32_t pad0[2];
    Mutex mMutex;           // +0x08 (0x30 bytes)
    void* mJob;             // +0x38
    void SetJob(void* job, void* arg2);
};
void CJobHolder::SetJob(void* job, void* arg2) {
    (void)arg2;
    mMutex.Lock((void*)0x014036f0);
    void* old = mJob;
    if (old) FUN_0068f950(old);
    if (job != mJob) {
        if (job) FUN_0068f950(job);
        mJob = job;
        if (mJob) GetStatus(mJob);
    }
    mMutex.Unlock();
    FUN_006913c0(old);
    if (old) GetStatus(old);
}

// =====================================================================
// @ 0x0068f180  set job + continuation if it succeeded
// =====================================================================
struct CJob180 { void* Continuation(void* fn, void* arg); };
struct CJobHolder2 {
    uint32_t f0, f4, f8;
    CJobHolder* mHolder;    // +0x0c
    void* mArg;             // +0x10
    bool Attach(void* job);
};
bool CJobHolder2::Attach(void* job) {
    mHolder->SetJob(job, mArg);
    if (mHolder != 0) {
        ((CJob180*)job)->Continuation((void*)0x00753fb0, this);
        return true;
    }
    return false;
}

// =====================================================================
// @ 0x0068f1d0  ctor of a job-lock object (partial: vtables/refcounts)
// =====================================================================
struct JobLock {
    void* vtbl0;            // +0x00
    void* vtbl1;            // +0x04
    void* f08;              // +0x08
    void* mRefObj;          // +0x0c
    void* mJob;             // +0x10
    JobLock(void* a, int b, void* c);
};
JobLock::JobLock(void* a, int b, void* c) {
    (void)a; (void)b; (void)c;
}

// =====================================================================
// @ 0x0068f2b0  dtor of the job-lock object (partial)
// =====================================================================
extern "C" void Dtor_68F2B0(JobLock* p) {
    if (p->mJob) GetStatus(p->mJob);
    void* r = p->mRefObj;
    if (r) {
        long* rc = (long*)((char*)r + 4);
        long n = _InterlockedExchangeAdd(rc, -1);
        if (n == 1) {
            _InterlockedExchange(rc, 1);
            ((void (__thiscall*)(void*, int))VT(r)[0])(r, 1);
        }
    }
}

// =====================================================================
// @ 0x0068f350  try-lock two jobs; on success create a JobLock (partial)
// =====================================================================
extern "C" int TryLockJobs(void* a, void* b, JobLock** out) {
    (void)a; (void)b; (void)out;
    int* p = FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return 0;
    p = FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return 0;
    return 1;
}

// =====================================================================
// @ 0x0068f450  EA::GetHighestBitPowerOf2
// =====================================================================
namespace EA {
int GetHighestBitPowerOf2(unsigned int v) {
    int n = 0;
    if (v & 0xffff0000) { n = 0x10; v >>= 0x10; }
    if (v & 0xff00) { n += 8; v >>= 8; }
    if (v & 0xf0) { n += 4; v >>= 4; }
    if (v & 0xc) { n += 2; v >>= 2; }
    if (v & 2) { n += 1; }
    return n;
}
}

// =====================================================================
// @ 0x0068f4a0  clear words and close handle at +8
// =====================================================================
struct HObj { void Close(); };
struct ClsF4A0 { uint32_t f0; uint32_t f4; HObj h; void Reset(); };
void ClsF4A0::Reset() {
    f0 = 0;
    f4 = 0;
    h.Close();
}

// =====================================================================
// @ 0x0068f4e0  ctor/dtor helper (partial, EH)
// =====================================================================
extern "C" void FUN_68F4E0(void* p) {
    void* o = *(void**)((char*)p + 0x20);
    (void)o;
    *(uint32_t*)((char*)p + 8) = 0;
    *(uint32_t*)((char*)p + 0xc) = 0;
}

// =====================================================================
// @ 0x0068f540  lock mutex @+8 and ++count @+0x38
// =====================================================================
struct ClsF540 { uint32_t f0, f4; Mutex m; int count; void Acquire(); void Release(); };
void ClsF540::Acquire() {
    m.Lock((void*)0x01403750);
    ++count;
}

// =====================================================================
// @ 0x0068f560  --count and unlock
// =====================================================================
void ClsF540::Release() {
    --count;
    m.Unlock();
}

// =====================================================================
// @ 0x0068f570  notify + virtual teardown call
// =====================================================================
struct Inner570 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(void*, int, int);       // slot 7 (0x1c)
};
struct Outer570 { uint32_t pad[10]; Inner570* mInner; };  // inner ptr at +0x28
extern "C" int FUN_68F570(Outer570* p) {
    void (*fn)(void*) = *(void (**)(void*))((char*)p->mInner + 0x1e0);
    if (fn)
        fn(p);
    ((Inner570*)p->mInner)->v7(p, 0, 0);
    return 0;
}

// =====================================================================
// @ 0x0068f5a0  invoke slot 0 of *b with a
// =====================================================================
extern "C" void FUN_68F5A0(void* a, void** b) {
    ((void (__cdecl*)(void*))((void**)*b)[0])(a);
}

// =====================================================================
// @ 0x0068f5b0  replace pointer, release old
// =====================================================================
struct VObj { virtual void v0(); virtual void v1(); };
struct ClsF5B0 { VObj* m; void Set(VObj* p); };
void ClsF5B0::Set(VObj* p) {
    VObj* old = m;
    m = p;
    if (old)
        old->v1();
}

// =====================================================================
// @ 0x0068f5d0  drain a list posting a semaphore for each detached node
// =====================================================================
struct ListNode { ListNode* next; ListNode* prev; uint32_t pad[2]; };
struct SemHolder { uint32_t pad[2]; };
extern "C" void FUN_68F5D0(ListNode* h) {
    while (h->next != h) {
        ListNode* n = h->next;
        ListNode* p = n->next;
        if (p != n) {
            ListNode* q = n->prev;
            p->prev = q;
            q->next = p;
            n->next = n;
            n->prev = n;
            SemaphorePost((char*)n + 0x10, 1);
        }
    }
}

// =====================================================================
// @ 0x0068f600  ctor of a semaphore-list container (partial, EH)
// =====================================================================
extern "C" void* FUN_68F600(void* p) {
    *(uint32_t*)((char*)p + 4) = 0;
    *(uint32_t*)((char*)p + 0) = 0;
    char* s = (char*)p + 8;
    *(uint32_t*)(s + 4) = 0;
    *(uint32_t*)(s + 0) = 0;
    *(void**)(s) = s;
    *(void**)(s + 4) = s;
    return p;
}
