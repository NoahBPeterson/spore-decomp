// Slice s00769f20: SP::cGraphicsResourceFactory async job setup / CanConvert /
// CreateResourceAsync helpers. /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void* __cdecl Node8F4d0(void);                                             // 0x68f4d0
void  __cdecl FUN_0068f9b0(void* p);
void  __cdecl FUN_006909b0(void* p);
void  __cdecl FUN_00691380(void* a, void* b);
void  __cdecl FUN_006913c0(void* a, void* b);
void* __cdecl FUN_0068f350(void* a, void* b);
void* __cdecl FUN_0067de70();                                              // 0x67de70
bool  __cdecl FUN_006af150(void* a, void* b, void* c);                     // 0x6af150
void  __cdecl FUN_0068f950(void* p);                                       // 0x68f950
void  __cdecl FUN_0068f9b0b(void* p);
char  __cdecl ReadResourceFromStreamStub(void* self, void* a, void* b, void* c); // 0x769d80
void* __cdecl FUN_00768370v(void* a, void* b, void* c, void* d, void* e);  // 0x768370
char  __cdecl FUN_007666a0v(void* a, void* b, void* c);                    // 0x7666a0
char  __cdecl FUN_00769d80v(void* a, void* b, void* c, void* d);           // 0x769d80
char  __cdecl FUN_00765b30v(void* a, void* b);                             // 0x765b30
char  __cdecl FUN_00765d30v(void* a, void* b);                             // 0x765d30
char  __cdecl FUN_007652c0v(void* a, void* b);                             // 0x7652c0
char  __cdecl FUN_007637d0v(void* a, void* b, int c, void* d);             // 0x7637d0
char  __cdecl FUN_007655f0b(void* a, void* b, void* c);   // 0x7655f0
bool  __fastcall ArmDecodeB(void* self, int, int);         // 0x7677c0
char  __cdecl FUN_0076a940v(void* a, void* b, void* c, void* d, void* e);   // 0x76a940
}

struct M69d80 { char Meth(int a, int b, int c); };
struct C69f { char pad0[0xfc]; int mFC; };
struct C69a9 { char pad0[0x10]; void* m10; char pad14[4]; int m18; char pad1c[0x18]; };

// ---------------------------------------------------------------------------
// shared SP::cJob / job-manager protocol used by the async chains below.
// (Declarations only: every call binds to its retail address through the
//  matching-sector symbol table.)
// ---------------------------------------------------------------------------
struct cJob;
struct JobRefL;

struct cJob {
    void* mpCallback;              // +0x00
    void* mpCallbackData;          // +0x04
    char pad08[0x10];
    uint32_t mFlags;               // +0x18
    void SetCallback(void* f, void* d) { mpCallback = f; mpCallbackData = d; }
    int  AddRef();                 // 0x0068f950
    int  Release();                // 0x00690120
    void SetExtra(void* owner);    // 0x0068f9b0
    void Submit();                 // 0x006909b0
    void AddDependency(cJob* other);       // 0x00691380
    void AddWeakDependency(cJob* other);   // 0x006913c0
};

struct JobRefL {
    cJob* p;
    JobRefL() : p(0) {}
    ~JobRefL() { Reset(); }
    void Reset() { if (p) { cJob* t = p; p = 0; t->Release(); } }
};

struct IJobMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool CreateJob(JobRefL* out);     // slot 4 (+0x10)
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Lock();                      // slot 8 (+0x20)
    virtual void Unlock();                    // slot 9 (+0x24)
};

struct JobLockTable {
    bool TryLockJobs(JobRefL* a, JobRefL* b); // 0x0068f350
};

struct RecInfo { uint32_t f0, f4; };
struct IConvCtx {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual RecInfo* Info();          // slot 4 (+0x10)
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Begin();             // slot 8 (+0x20)
    virtual void End();               // slot 9 (+0x24)
};

struct IRefObj { virtual void AddRef(); virtual void Release(); };

// subset of SP::cGraphicsResourceFactory touched by this slice
struct Grf {
    char pad0[0xc];
    void* pC;                      // +0x0c
    IConvCtx* p10;                 // +0x10
    char pad14[4];
    uint32_t type18;               // +0x18
    char pad1c[0xe0];
    uint32_t stateFC;              // +0xfc
};

struct ConvObj { void* Init(void* res, void* a, void* b, void* c, void* d); }; // 0x00768370
struct AsyncResMgr { bool AllocateRequest(void* type, IRefObj** req, JobRefL* job); }; // 0x006af150

// retail-shaped entry points for the async request starters (ecx = self,
// single stack argument, callee pops it).
char __fastcall StartReqA(void* self, int, void** out);   // 0x007652c0
char __fastcall StartReqB(void* self, int, void** out);   // 0x00765b30
char __fastcall StartReqC(void* self, int, void** out);   // 0x00765d30
char __fastcall CreateByType(void* self, int, void** out, void* p5, uint32_t type); // 0x007666a0

static __forceinline IJobMgr* GetJobManager() { return (IJobMgr*)Node8F4d0(); }

static __forceinline bool CreateJobInto(IJobMgr* jm, JobRefL& r) {
    r.Reset();
    return jm->CreateJob(&r);
}

static __forceinline JobLockTable* LockTable(void* self) {
    return *(JobLockTable**)((char*)*(void**)((char*)self + 0xc) + 8);
}

// ===========================================================================
// @ 0x00769f20  async job chain setup (3 sub-jobs + a callback job)
// ===========================================================================
bool __fastcall SetupJobChain(void* self, int, void** out) {
    Grf* s = (Grf*)self;
    s->stateFC = 3;
    IJobMgr* jm = GetJobManager();
    jm->Lock();

    JobRefL j1, j2, j3, j4;
    if (!CreateJobInto(GetJobManager(), j1)) { jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager(), j2)) { j1.Reset(); jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager(), j3)) { j2.Reset(); j1.Reset(); jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager(), j4)) { j3.Reset(); j2.Reset(); j1.Reset(); jm->Unlock(); return false; }

    JobRefL l1, l2;
    if (!LockTable(self)->TryLockJobs(&l1, &l2)) {
        l2.Reset(); l1.Reset();
        j4.Reset(); j3.Reset(); j2.Reset(); j1.Reset();
        jm->Unlock();
        return false;
    }

    j1.p->SetCallback((void*)0x767330, self);
    j1.p->mFlags = 4;
    j1.p->SetExtra(self);
    j1.p->Submit();

    j2.p->SetCallback((void*)0x767340, self);
    j2.p->mFlags = 0x80000000;
    j2.p->SetExtra(self);
    j2.p->AddDependency(j1.p);
    j2.p->Submit();

    l1.p->AddDependency(j2.p);
    l1.p->Submit();

    j3.p->SetCallback((void*)0x765190, self);
    j3.p->mFlags = 4;
    j3.p->SetExtra(self);
    j3.p->AddDependency(l1.p);
    j3.p->Submit();

    j4.p->SetCallback((void*)0x769d70, self);
    j4.p->mFlags = 1;
    j4.p->SetExtra(self);
    j4.p->AddDependency(j3.p);
    j4.p->Submit();

    l2.p->AddDependency(j4.p);
    l2.p->Submit();

    *out = j4.p;
    j4.p = 0;

    l2.Reset(); l1.Reset();
    j4.Reset(); j3.Reset(); j2.Reset(); j1.Reset();
    jm->Unlock();
    return true;
}

// ===========================================================================
// @ 0x0076a300  load a "simple" async resource request
// ===========================================================================
char __fastcall Func76a300(void* self, int, int unused) {
    (void)unused;
    char* s = (char*)self;
    void* obj = *(void**)(s + 0x10);
    int uVar5 = *(int*)(s + 0x18);
    int a14 = *(int*)(s + 0x14);
    int a28 = *(int*)(s + 0x28);
    int ebp = *(int*)(s + 0xc);
    int v = ((int(__thiscall**)(void*, int))*(void***)obj)[4](obj, uVar5);
    char c = ((M69d80*)ebp)->Meth(a28, a14, v);
    if (c)
        *(char*)(s + 0x334) = 1;
    return c;
}

// ===========================================================================
// @ 0x0076a340  SP::cGraphicsResourceFactory::ReadResource
// ===========================================================================
char __fastcall ReadResource(void* self, int, void* a1, void* a2, void* a3) {
    char* o = (char*)a1;
    void* p = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
    // triplet copy
    int t0 = *(int*)p, t1 = *(int*)((char*)p + 4), t2 = *(int*)((char*)p + 8);
    *(int*)(o + 8) = t0;
    *(int*)(o + 0xc) = (int)(size_t)a3;
    *(int*)(o + 0x10) = t2;
    if ((size_t)a3 == 0x2f4e681c) {
        void* q = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
        if (*(int*)((char*)q + 4) == 0x2f4e681b) {
            void* r = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
            void* u = (void*)((int(__thiscall**)(void*, void*, void*))*(void***)self)[7](self, a1, r);
            return FUN_007655f0b(u, a1, r);
        }
    }
    void* q = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
    void* t = *(void**)((char*)q + 4);
    void* u = (void*)((int(__thiscall**)(void*, void*, void**, void*))*(void***)self)[6](self, a1, &t, t);
    return FUN_00769d80v(u, a1, &t, t);
}

// ===========================================================================
// @ 0x0076a400  create a single async request job
// ===========================================================================
bool __fastcall CreateRequestJob(void* self, int, void* out) {
    void* n = Node8F4d0();
    int local = 0;
    (void)local;
    if (!((bool(__thiscall**)(void*, int*))*(void***)n)[4](n, &local))
        return false;
    char* lp = (char*)local;
    *(void**)(lp) = (void*)0;          // callback
    *(void**)(lp + 4) = self;
    *(int*)(lp + 0x18) = 1;
    FUN_0068f9b0(self);
    FUN_006909b0(lp);
    *(void**)out = lp;
    return true;
}

// ===========================================================================
// @ 0x0076a4d0  try-lock two jobs and chain a 4-step job
// ===========================================================================
bool __fastcall TryLockChain(void* self, int, void** out) {
    IJobMgr* jm = GetJobManager();
    jm->Lock();

    JobRefL j1, j2;
    if (!CreateJobInto(GetJobManager(), j1)) { jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager(), j2)) { j1.Reset(); jm->Unlock(); return false; }

    JobRefL a, b;
    if (!LockTable(self)->TryLockJobs(&a, &b)) {
        b.Reset(); a.Reset();
        j2.Reset(); j1.Reset();
        jm->Unlock();
        return false;
    }

    a.p->Submit();

    j1.p->SetCallback((void*)0x765190, self);
    j1.p->mFlags = 4;
    j1.p->SetExtra(self);
    j1.p->AddDependency(a.p);
    j1.p->Submit();

    j2.p->SetCallback((void*)0x76a3f0, self);
    j2.p->mFlags = 1;
    j2.p->SetExtra(self);
    j2.p->AddDependency(j1.p);
    j2.p->Submit();

    b.p->AddDependency(j2.p);
    b.p->Submit();

    *out = j2.p;
    j2.p = 0;

    b.Reset(); a.Reset();
    j2.Reset(); j1.Reset();
    jm->Unlock();
    return true;
}

// ===========================================================================
// @ 0x0076a720  SP::cGraphicsResourceFactory::CanConvert
// ===========================================================================
bool __fastcall CanConvert(void* self, int, void** out) {
    Grf* s = (Grf*)self;
    IJobMgr* jm = GetJobManager();
    jm->Lock();

    JobRefL job;
    uint32_t type = s->type18;
    char ok;
    if (type <= 0x2f4e681b) {
        if (type == 0x2f4e681b)
            ok = StartReqB(self, 0, (void**)&job.p);
        else if (type == 0xe6bce5)
            ok = SetupJobChain(self, 0, (void**)&job.p);
        else if (type == 0x1c135da)
            ok = TryLockChain(self, 0, (void**)&job.p);
        else
            ok = CreateRequestJob(self, 0, &job.p);
    } else if (type == 0x2f4e681c) {
        RecInfo* info = s->p10->Info();
        uint32_t sub = info->f4;
        if (sub <= 0x2f7d0004) {
            if (sub == 0x2f7d0004)
                ok = StartReqA(self, 0, (void**)&job.p);
            else if (sub == 0x2f4e681b)
                ok = StartReqC(self, 0, (void**)&job.p);
            else if (sub == 0x2f4e681c)
                ok = ArmDecodeB(self, 0, (int)(size_t)&job.p);
            else {
                jm->Unlock();
                return false;
            }
        } else if (sub == 0x2f7d0007) {
            ok = StartReqA(self, 0, (void**)&job.p);
        } else {
            jm->Unlock();
            return false;
        }
    } else {
        ok = CreateRequestJob(self, 0, &job.p);
    }

    if (!ok) {
        job.Reset();
        jm->Unlock();
        return false;
    }

    JobRefL j2;
    if (!CreateJobInto(GetJobManager(), j2)) {
        j2.Reset();
        job.Reset();
        jm->Unlock();
        return false;
    }

    j2.p->SetCallback((void*)0x765180, self);
    j2.p->SetExtra(self);
    j2.p->AddWeakDependency(job.p);

    *out = j2.p;
    j2.p = 0;

    job.Reset();
    jm->Unlock();
    return true;
}

// ===========================================================================
// @ 0x0076a940  SP::cGraphicsResourceFactory::CreateConvertedResourceAsync
// ===========================================================================
bool __cdecl CreateConvertedResourceAsync(void* out, void* a, void* b, IConvCtx* c, void* d) {
    void* mgr = FUN_0067de70();
    if (!mgr)
        return false;

    IRefObj* res = 0;
    RecInfo* info = c->Info();
    if (!CreateByType(a, 0, (void**)&res, d, info->f4)) {
        if (res)
            res->Release();
        return false;
    }

    void* mem = Alloc6(0x338, "Graphics", 0, 0, 0, 0);
    ConvObj* conv = mem ? (ConvObj*)((ConvObj*)mem)->Init(res, a, b, c, d) : 0;
    if (conv)
        ((IRefObj*)conv)->AddRef();

    c->Begin();

    IJobMgr* jm = GetJobManager();
    jm->Lock();

    JobRefL job;
    if (!CanConvert(conv, 0, (void**)&job.p)) {
        c->End();
        job.Reset();
        jm->Unlock();
        if (conv)
            ((IRefObj*)conv)->Release();
        if (res)
            res->Release();
        return false;
    }

    JobRefL jobcopy;
    jobcopy.p = job.p;
    if (jobcopy.p)
        jobcopy.p->AddRef();

    IRefObj* req = 0;
    bool ok = ((AsyncResMgr*)mgr)->AllocateRequest(b, &req, &jobcopy);
    job.p->Submit();

    if (!ok) {
        if (req)
            req->Release();
        jobcopy.Reset();
        job.Reset();
        jm->Unlock();
        if (conv)
            ((IRefObj*)conv)->Release();
        if (res)
            res->Release();
        return false;
    }

    *(void**)out = req;

    jobcopy.Reset();
    job.Reset();
    jm->Unlock();
    if (conv)
        ((IRefObj*)conv)->Release();
    if (res)
        res->Release();
    return true;
}

// ===========================================================================
// @ 0x0076ac30  SP::cGraphicsResourceFactory::CreateResourceAsync
// ===========================================================================
bool __fastcall CreateResourceAsync(void* self, int, void* out, void* unused2, int* param_4, void* p5, void* p6, int p7) {
    int* local = 0;
    if (p7 == 0)
        p7 = ((int(__thiscall**)(int*))*(void***)param_4)[4](param_4);
    char r = FUN_0076a940v(&local, self, (void*)p7, param_4, p6);
    if (!r) {
        if (local)
            ((void(__thiscall**)(int*))*(void***)local)[1](local);
        return false;
    }
    *(int**)out = local;
    (void)p5;
    (void)unused2;
    return true;
}
