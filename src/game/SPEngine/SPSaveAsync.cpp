// src/game/SPEngine/SPSaveAsync.cpp -- migrated from slice(s) s006b47a0, s006b37d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPSaveAsync.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyList.h"
#include "SP/cString.h"
#include "EA/Thread/Mutex.h"
#include "SP/cJob.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t  g_1604b80;

// ---- items of slice s006b37d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SecBase6 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual uint32_t Call0c(uint32_t);
};
struct ObjSec6 { uint32_t pad0; SecBase6 sec; };
struct Mutex6 { Mutex6(int, int); ~Mutex6(); };
struct Job6 { void GetStatus(); };
struct JobPtr6 { void* p; JobPtr6() : p(0) {} ~JobPtr6(); };
struct JobHolder6 {
  JobPtr6 job;      // +0x00
  uint32_t pad;     // +0x04
  Mutex6 mutex;     // +0x08
  JobHolder6();
  ~JobHolder6();
};
extern JobHolder6 g_jobHolder6;   // 0x01604b48
extern uint32_t  g_1604b80;
inline void* operator new(uint32_t, void* p) { return p; }
#define V6(n) virtual void v##n();
struct IRefC { virtual void v0(); virtual void Release(); };
struct SvcBase6 {
  V6(0) V6(1) V6(2) V6(3) V6(4) V6(5) V6(6) V6(7) V6(8) V6(9) V6(10) V6(11) V6(12) V6(13) V6(14) V6(15)
  V6(16) V6(17)
  virtual uint32_t Detach();   // 0x48
};
struct SvcA6 : SvcBase6 {
  bool Check(void* key, uint32_t size);   // 0x008d8570
  bool Pack(void* data, uint32_t size, uint32_t* pOut, uint32_t* pLen, uint16_t* pFlag);   // 0x008d9850
  bool Unpack(void* key, uint32_t a, uint32_t b, uint32_t size, uint32_t flag);
};
struct SvcB6 : SvcBase6 {
  bool Check(void* key, uint32_t size);   // 0x006bc3e0
  bool Pack(void* data, uint32_t size, uint32_t* pOut, uint32_t* pLen, uint16_t* pFlag);   // 0x006bd580
  bool Unpack(void* key, uint32_t a, uint32_t b, uint32_t size, uint32_t flag);
};
struct Alloc6 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void Free(void* p, uint32_t n); };
struct AllocHolder6 { Alloc6* GetAllocator(); };
struct Provider6 {   // object at +4 of a SvcProvider
virtual void v0();
virtual void Release();
  virtual void v2();
  virtual void* Query(uint32_t id);   // 0x0c
};
struct ProvObj6 { uint32_t pad; Provider6 sec; };
struct ProvPtr6 {
  ProvObj6* p;
  ~ProvPtr6() { if (p) p->sec.Release(); }
};
struct Stream6 {
  ~Stream6();   // 0x0093bde0
  void* GetData();   // 0x0093ba70
  void Attach(int a, int b);   // 0x0093bf70
  void SetData(uint32_t p, uint32_t n, int a, int b, uint32_t c);   // 0x0093be30
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
  virtual void Flush();    // 0x18
  virtual uint32_t Size(); // 0x1c
  char d[0x24];
};
struct IRefPtr6 { IRefC* p; ~IRefPtr6() { if (p) p->Release(); } };
struct JobCtx6 {
  void Done(int n);   // 0x0068f9b0
};
struct BG6 { virtual void bg0(); virtual ~BG6() {} };
struct ER6 { virtual void er0(); virtual ~ER6() {} };
struct Job6B : ER6, BG6 {
  uint32_t pad8;
  IRefPtr6 m0c;
  uint32_t m10;
  uint32_t m14;
  uint32_t pad18;
  ProvPtr6 m1c;
  Stream6 strm;
  uint32_t m48, m4c, m50;
  uint16_t m54;
  ~Job6B();
  bool Prepare(JobCtx6* c);
  bool Finish(JobCtx6* c);
};
JobPtr6::~JobPtr6() {
  if (p != 0) {
    ((Job6*)p)->GetStatus();
  }
}
// ---- items of slice s006b37d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern JobHolder6 g_jobHolder6;   // 0x01604b48

// ---- items of slice s006b47a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned          g_lockTimeout;    // 0x014099b8
extern int               g_saveJobReady;   // 0x01604b80
namespace EA {
namespace Thread {
class Mutex_s006b_47a0 {
public:
    char mData[0x30];
    int Lock(unsigned* pTimeout);   // 0x009221b0
    int Unlock();                   // 0x00922270
};  // namespace EA::Thread
}
}
extern EA::Thread::Mutex_s006b_47a0 g_saveMutex;      // 0x01604b50
struct cJob {
    void*    mpCallback;        // +0x00
    void*    mpCallbackData;    // +0x04
    void*    mpExtraObject;     // +0x08
    void*    mpDebugName;       // +0x0c
    int      mPriority;         // +0x10
    int      mStatus;           // +0x14
    uint32_t mThreadAffinity;   // +0x18
    int      mSlot;             // +0x1c
    void*    mpReturnValue;     // +0x20
    void*    mpCleanupValue;    // +0x24

    int  AddRef();                          // 0x0068f950
    int  Release();                         // 0x00690120
    void Wait();                            // 0x006926b0
    void AddWeakDependency(cJob* pOther);   // 0x006913c0
    void AddDependency(cJob* pOther);       // 0x00691380
    int  GetStatus();                       // 0x006909b0
    void SetResult(void* pValue);           // 0x0068f9b0
};
extern cJob* g_saveJob;   // 0x01604b48
struct MutexScopedLock {
    EA::Thread::Mutex_s006b_47a0* mpMutex;
    MutexScopedLock(EA::Thread::Mutex_s006b_47a0* m) : mpMutex(m) { m->Lock(&g_lockTimeout); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
};
void* __cdecl FUN_0067dcd0();      // 0x0067dcd0 EA::ResourceMan::GetManager
void* __cdecl FUN_0068f4d0();      // 0x0068f4d0 cJobManager getter
void* __cdecl ZoneObject_new(uint32_t nSize, const char* pName, int, int, int, int);  // 0x00926020
int   __cdecl FUN_00695cf0(void* p);   // 0x00695cf0
int   __cdecl FUN_006b4390(void** p);  // 0x006b4390
void  __cdecl FUN_006b4710();      // 0x006b4710
void  __cdecl FUN_006b4720();      // 0x006b4720
void  __cdecl FUN_006b4b50();      // 0x006b4b50
struct IRefC_s006b_47a0 {                 // refcounted interface (slot 0 = AddRef, slot 1 = Release)
    virtual void v0();         // +0x00
    virtual void v1();         // +0x04
    virtual void v2();         // +0x08
    virtual void v3();         // +0x0c
    virtual void v4();         // +0x10
    virtual void v5();         // +0x14
    virtual void v6();         // +0x18
    virtual void v7();         // +0x1c
};
struct ResMgr {                // EA::ResourceMan manager (0x0067dcd0)
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
virtual void m16();
virtual void m17();
    virtual void* FindResource(uint32_t a, uint32_t b);      // slot 0x12 / +0x48
virtual void m19();
virtual void m20();
virtual void m21();
    virtual void* GetByKey(void* key);                       // slot 0x16 / +0x58
};
struct JobMgr {                // SP::cJobManager (0x0068f4d0)
virtual void j0();
virtual void j1();
virtual void j2();
virtual void j3();
    virtual bool BeginJob(cJob** pOut);      // slot 4  / +0x10
virtual void j5();
virtual void j6();
virtual void j7();
    virtual void Lock();                     // slot 8  / +0x20
    virtual void Unlock();                   // slot 9  / +0x24
};
struct Key3 { uint32_t inst, type, group; };
struct ILocal2 {               // object returned by ILocal::Get
virtual void n0();
virtual void n1();
virtual void n2();
virtual void n3();
virtual void n4();
virtual void n5();
virtual void n6();
virtual void n7();
virtual void n8();
virtual void n9();
virtual void nA();
virtual void nB();
virtual void nC();
virtual void nD();
    virtual bool Write(void* pData, int nSize);   // slot 0xe / +0x38
};
struct ILocal {                // object produced by the resource provider
    virtual void l0();         // +0x00
    virtual void l1();         // +0x04
    virtual void Release();    // +0x08 (slot 2)
    virtual void l3();         // +0x0c
    virtual void l4();         // +0x10
    virtual void l5();         // +0x14
    virtual ILocal2* Get();    // +0x18 (slot 6)
    virtual void l7();         // +0x1c
    virtual void l8();         // +0x20
    virtual bool Check();      // +0x24 (slot 9)
};
struct IProv {                 // provider object at +0x1c
virtual void p0();
virtual void p1();
virtual void p2();
    virtual uint32_t GetKind();                       // slot 3 / +0x0c
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void pA();
virtual void pB();
    virtual void pC();
    virtual bool Make(void* pKey, void** ppOut);      // slot 0xd / +0x34
};
struct IResProv {              // param_3 in FUN_006b4b60
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
virtual void q8();
virtual void q9();
    virtual bool Run(void* pA, void* pB, int c, uint32_t d);   // slot 0xa / +0x28
};
struct GfarStream {            // EA::IO::GraphicsFactoryAsyncRequest at +0x20 (size 0x24)
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void Flush();      // slot 6 / +0x18
    virtual int  Size();       // slot 7 / +0x1c
    GfarStream(void* pData, void* pUnused, const char* pName);  // 0x0093c270
    void* GetData();                                            // 0x0093ba70
    void  SetProperty(int index, float value);                  // 0x0093bb40
    char mData[0x20];
};
struct JobBaseA {              // primary base (cILayer)
    virtual void AddRef();     // slot 0
    virtual void Release();    // slot 1
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
};
struct AsyncSave;
struct JobBaseB {              // secondary base at +4 (BG6)
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void b7();
virtual void b8();
    virtual bool Complete();       // slot 9 / +0x24; `this` is the +4 subobject
};
struct AsyncSave : JobBaseA, JobBaseB {
    uint32_t   m8;         // +0x08
    IRefC_s006b_47a0*     m0c;        // +0x0c
    Key3       m10;        // +0x10
    IProv*     m1c;        // +0x1c (provider, secondary interface at +4)
    GfarStream mStrm;      // +0x20
    uint32_t   m44;        // +0x44 (refcount)
    uint32_t   m48;        // +0x48
    uint32_t   m4c;        // +0x4c
    uint32_t   m50;        // +0x50
    uint16_t   m54;        // +0x54
    AsyncSave(IRefC_s006b_47a0* pTarget, void* pProvider, Key3* pKey);
    bool     Finish(cJob* c);
};
struct AutoRef {
    cJob* mpObject;
    AutoRef(cJob* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
// ---- items of slice s006b47a0 end

// @ 0x006b4340
JobHolder6::~JobHolder6()
{}

// @ 0x006b4390
uint32_t FUN_006b4390(ObjSec6** p)
{
  ObjSec6* o = *p;
  if (o != 0) {
    return o->sec.Call0c(0x6492c5f);
  }
  return 0;
}

// @ 0x006b43b0
JobHolder6::JobHolder6()
: mutex(0, 1) {}

// @ 0x006b4400
Job6B::~Job6B()
{}

// @ 0x006b4490
bool Job6B::Prepare(JobCtx6* c)
{
  void* data = strm.GetData();
  m50 = strm.Size();
  m54 = 0;
  m48 = 0;
  m4c = 0;
  switch (m14) {
  case 0x2f7d0002:
  case 0x2f7d0004:
  case 0x2f7d0007:
    break;
  default: {
    SvcBase6* svc;
    bool ok;
    char r;
    if (m1c.p) {
      SvcA6* a = (SvcA6*)m1c.p->sec.Query(0x226a25b);
      svc = a;
      if (a) {
        if (!a->Check(&m10, m50)) goto fail;
        r = a->Pack(data, m50, &m48, &m4c, &m54);
        goto common;
      }
    }
    if (m1c.p) {
      SvcB6* b = (SvcB6*)m1c.p->sec.Query(0x6492c5f);
      svc = b;
      if (b) {
        if (!b->Check(&m10, m50)) goto fail;
        r = b->Pack(data, m50, &m48, &m4c, &m54);
        goto common;
      }
    }
    goto fallback;
  common:
    ok = true;
    if (r) goto detach;
  fail:
    ok = false;
  detach:
    uint32_t d = svc->Detach();
    if (ok) {
      strm.Attach(0, 0);
      strm.SetData(m48, m4c, 1, 1, d);
      c->Done(0);
      return true;
    }
  }
  }
fallback:
  m48 = (uint32_t)data;
  m4c = m50;
  m54 = 0;
  c->Done(0);
  return true;
}

// @ 0x006b4610
bool Job6B::Finish(JobCtx6* c)
{
  bool ok = false;
  SvcA6* a = 0;
  if (m1c.p) a = (SvcA6*)m1c.p->sec.Query(0x226a25b);
  if (a) {
    ok = a->Unpack(&m10, m48, m4c, m50, m54);
  } else if (m1c.p) {
    SvcB6* b = (SvcB6*)m1c.p->sec.Query(0x6492c5f);
    if (b) ok = b->Unpack(&m10, m48, m4c, m50, m54);
    else goto tail;
  } else {
    goto tail;
  }
  if (ok && m1c.p) {
    AllocHolder6* h = (AllocHolder6*)m1c.p->sec.Query(0x498d9c1);
    if (h) h->GetAllocator()->Free(&m10, m4c);
  }
tail:
  m48 = 0;
  strm.Flush();
  if (m0c.p) { IRefC* t = m0c.p; m0c.p = 0; t->Release(); }
  if (m1c.p) { ProvObj6* t = m1c.p; m1c.p = 0; t->sec.Release(); }
  c->Done(0);
  return ok;
}

// @ 0x006b4730
void FUN_006b4730()
{
  g_1604b80 = 1;
  new (&g_jobHolder6) JobHolder6();
}

// @ 0x006b4780
void FUN_006b4780()
{
  g_jobHolder6.~JobHolder6();
  g_1604b80 = 0;
}

// @ 0x006b47a0
void __cdecl FUN_006b47a0(cJob* p)
{
    if (g_saveJobReady == 1) {
        MutexScopedLock lock(&g_saveMutex);
        p->AddWeakDependency(g_saveJob);
        if (p != g_saveJob) {
            cJob* old = g_saveJob;
            if (p)
                p->AddRef();
            g_saveJob = p;
            if (old)
                old->Release();
        }
    }
}

// @ 0x006b4840
void __cdecl FUN_006b4840()
{
    if (g_saveJobReady == 1) {
        g_saveMutex.Lock(&g_lockTimeout);
        AutoRef ref(g_saveJob);
        g_saveMutex.Unlock();
        if (ref.mpObject)
            ref.mpObject->Wait();
    }
}

// @ 0x006b48d0
AsyncSave::AsyncSave(IRefC_s006b_47a0* pTarget, void* pProvider, Key3* pKey)
: mStrm(0, 0, "UTF/MemoryStream")
{
    m8 = 0;
    m0c = pTarget;
    if (pTarget != 0)
        pTarget->v0();
    m10 = *pKey;
    m1c = (IProv*)pProvider;
    if (pProvider != 0)
        ((IRefC_s006b_47a0*)((char*)pProvider + 4))->v0();
    m54 = 0;
    m44 = 1;
    m48 = 0;
    m4c = 0;
    m50 = 0;
    mStrm.s1();
    mStrm.SetProperty(1, 1.0f);
    mStrm.SetProperty(2, 2.0f);
    mStrm.SetProperty(3, 15000.0f);
}

// @ 0x006b4a10
bool AsyncSave::Finish(cJob* c)
{
    void* data = mStrm.GetData();
    int   size = mStrm.Size();
    ILocal* obj = 0;
    if (!m1c->Make(&m10, (void**)&obj)) {
        if (obj)
            obj->Release();
        return false;
    }
    ILocal2* p = obj->Get();
    bool w = p->Write(data, size);
    bool chk = obj->Check();
    bool res = (chk && w);
    mStrm.Flush();
    if (obj) {
        obj->Release();
        obj = 0;
    }
    if (m0c) {
        IRefC_s006b_47a0* t = m0c;
        m0c = 0;
        t->v1();
    }
    if (m1c) {
        IRefC_s006b_47a0* t = (IRefC_s006b_47a0*)((char*)m1c + 4);
        m1c = 0;
        t->v1();
    }
    c->SetResult(0);
    return res;
}

// @ 0x006b4b60
char __cdecl FUN_006b4b60(void* pArg0, void* pArg1, IResProv* pArg2, Key3* pArg3)
{
    char result = 0;
    ResMgr* mgr = (ResMgr*)FUN_0067dcd0();
    if (pArg0 != 0) {
        Key3 key;
        if (pArg3 == 0) {
            key.inst  = *(uint32_t*)((char*)pArg0 + 8);
            key.type  = *(uint32_t*)((char*)pArg0 + 0xc);
            key.group = *(uint32_t*)((char*)pArg0 + 0x10);
        } else {
            key = *pArg3;
        }
        if (pArg1 == 0) {
            pArg1 = mgr->GetByKey(&key);
            if (pArg1 == 0)
                return 0;
        }
        if (pArg2 == 0) {
            pArg2 = (IResProv*)mgr->FindResource(key.type, *(uint32_t*)((char*)pArg0 + 0xc));
            if (pArg2 == 0)
                return 0;
        }
        AsyncSave* mem = (AsyncSave*)ZoneObject_new(0x58, "App/AsyncSave", 0, 0, 0, 0);
        AsyncSave* job = 0;
        if (mem != 0)
            job = new (mem) AsyncSave((IRefC_s006b_47a0*)pArg0, pArg1, &key);
        if (job != 0)
            job->AddRef();
        void* jsec = (job == 0) ? 0 : (void*)((char*)job + 4);
        result = pArg2->Run(pArg0, jsec, 0, key.type);
        if (result == 0)
            job->m44 = 0;
        else if (job != 0)
            job->Complete();
        job->Release();
    }
    return result;
}

// @ 0x006b4ce0
bool JobBaseB::Complete()
{
    AsyncSave* self = (AsyncSave*)((char*)this - 4);
    if (self->m44 == 0)
        return false;
    if (--self->m44 != 0)
        return true;
    JobMgr* mgr = (JobMgr*)FUN_0068f4d0();
    mgr->Lock();
    cJob* job1 = 0;
    if (!mgr->BeginJob(&job1)) {
        if (job1)
            job1->Release();
        mgr->Unlock();
        return false;
    }
    uint32_t kind = self->m1c->GetKind();
    bool pair;
    if (kind == 0x2a43bd44 || kind == 0x6492c68)
        pair = true;
    else if (kind == 0x498d9c1)
        pair = (FUN_00695cf0(&self->m1c) != 0 || FUN_006b4390((void**)&self->m1c) != 0);
    else
        pair = false;
    if (pair) {
        cJob* job2 = 0;
        if (!mgr->BeginJob(&job2)) {
            if (job2)
                job2->Release();
            if (job1)
                job1->Release();
            mgr->Unlock();
            return false;
        }
        job2->mThreadAffinity = 0x80000000;
        job2->mpCallback = (void*)&FUN_006b4710;
        job2->mpCallbackData = self;
        job2->SetResult(self);
        job1->AddDependency(job2);
        job1->mThreadAffinity = 4;
        job1->mpCallback = (void*)&FUN_006b4720;
        job1->mpCallbackData = self;
        job1->SetResult(self);
        job1->GetStatus();
        if (job2)
            job2->Release();
    } else {
        job1->mThreadAffinity = 4;
        job1->mpCallback = (void*)&FUN_006b4b50;
        job1->mpCallbackData = self;
        job1->SetResult(self);
    }
    FUN_006b47a0(job1);
    job1->GetStatus();
    if (job1)
        job1->Release();
    mgr->Unlock();
    return true;
}
