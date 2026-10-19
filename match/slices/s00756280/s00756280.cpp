// slice s00756280 -- SP model-region / material / job helpers (BuildRegionToInfoMap etc).
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2.
// See nonmatching.txt / partial.txt.

#include "types.h"

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)

// 6-arg EA operator new/delete: ??2@YAPAXIPBDHI0H@Z / the matching ??3 (0x00f47410).
// Declaring the matching placement operator delete is what makes cl emit the EH
// state stores around a 6-arg placement new (codegen.md 15, 0x697c40).
void* operator new(unsigned int, const char*, int, unsigned int, unsigned int, int);   // 0x00f473a0
void operator delete(void*);
void operator delete(void*, const char*, int, unsigned int, unsigned int, int);   // 0x00f47410

// ---------------------------------------------------------------------------
// cdecl callees (resolved by the hex address embedded in the name).
// ---------------------------------------------------------------------------
int   FUN_0071ddc0(void* self, int a, int b, int c, int d);
int   FUN_0071dd80(void* self, int a);
void  FUN_00720190(int n, int sz, void* out);
void* FUN_0067dd70();                          // SP::MaterialManager
void  FUN_0067dcd0();                          // EA::ResourceMan::GetManager
void* FUN_0072c0a0(void* a, void* b, int c, void* d);
char  FUN_006ac040(int a, void* b);            // SP::SetCachingType
char  FUN_006acfe0(unsigned int* s, char* obj);
void* FUN_006df700(void* a, void* b, void* c);void  FUN_00733f20(void* p);
void  FUN_007345c0(void* p);
char  FUN_00732360(void* p);
void  FUN_007387f0(void* p);
void  FUN_007389c0(void* p, int a);
void  FUN_00738900(void* p);
void  FUN_00728020(void* ctx, float f, int flag, void* p);
void  FUN_00753dc0(void* holder, int flags);
void  FUN_00753fe0(void** dst, void* src);
void  FUN_00755d20();
void  FUN_00755d30();
void  FUN_00753fb0();

// ---------------------------------------------------------------------------
// thiscall callees (methods of a dummy struct so ecx is the object pointer;
// each is resolved by the hex address embedded in the method name).
// ---------------------------------------------------------------------------
struct Ext {
  void   FUN_0041ee90(unsigned int);           // RefVector::resize
  void   FUN_006df280(void*);                  // RefPtr::AssignRefPtr
  void   FUN_0041d8b0(void*);
  void** FUN_00742f60(void const*);            // Map8::GetOrAdd
  void*  FUN_011edcf0(int);                    // D3D9GetShaderData
  void   FUN_00755570(unsigned int, int);      // V_755570::FUN_00755570
  void   FUN_0041f320(void*);                  // Vec_Elem7c_operator_assign
  void*  FUN_007552e0(void*);                  // GlyphVec::Assign
  void   FUN_0041f7d0(void*);                  // Vec_Elem20_push_back
  void*  FUN_004728e0(void*);
  void   FUN_00424f70(void*);                  // Handle_Assign
  int    FUN_00690120();                       // cJob::Release
  int    FUN_0068f950();                       // cJob::AddRef
  int    FUN_006909b0();                       // cJob::GetStatus
  int    FUN_00768530();                       // CB24::AddRef (refcount at +8)
  int    FUN_0067da30();                       // CB24::Release
  int    FUN_00432be0();                       // Obj140::AddRef (refcount at +4)
  int    FUN_00763250();                       // Obj140::Release
  void   FUN_0068f9b0(void*);                  // cJob::sub_68f9b0
  void   FUN_006913c0(void*);                  // cJob::AddWeakDependency
  bool   FUN_0068f9f0(void*, void*);           // cJob::Continuation
  void   FUN_0059c410(void*, void*);           // ReleaseAutoRefRange (ecx = &range)
};

// ---------------------------------------------------------------------------
// Ref-counted objects.
// ---------------------------------------------------------------------------
struct IObject {
  virtual int AddRef();
  virtual int Release();
};

// 0x58-byte mesh context.  Manual intrusive refcount at +4; vtable slot 0 is a
// deleting destructor taking the `delete` flag.
struct PartHolder {
  virtual void vfunc(int);
  int mRefCount;                        // +0x04
  char pad_08[0x58 - 8];
  PartHolder(PartHolder const* other);  // 0x0040f070
};

__forceinline void PartAddRef(PartHolder* p) {
  if (p) _InterlockedExchangeAdd((volatile long*)&p->mRefCount, 1);
}
__forceinline void PartRelease(PartHolder* p) {
  if (!p) return;
  if (_InterlockedExchangeAdd((volatile long*)&p->mRefCount, -1) == 1) {
    _InterlockedExchange((volatile long*)&p->mRefCount, 1);
    p->vfunc(1);
  }
}

// 0x24-byte ref-counted job callback object.  Two vtable pointers (single
// inheritance chain): +0 = 0x0140d9b0, +4 = 0x0140d9ac.  Refcount at +8.
// AddRef/Release are the real vendor functions (0x00768530 / 0x0067da30).
struct cJobRef;
struct CB24 {
  void* mpVtbl;      // +0x00  (0x0140d9b0)
  void* mpVtbl2;     // +0x04  (0x0140d9ac)
  int   mRefCount;   // +0x08
  void* m0c;         // +0x0c
  int   m10;         // +0x10
  int   m14;         // +0x14
  void* m18;         // +0x18
  int   m1c;         // +0x1c
  int   m20;         // +0x20
  CB24();
  bool FUN_00756650(cJobRef* out, void* b, int c, void* d);
};
extern const char CB24_vtbl;    // 0x0140d9b0
extern const char CB24_vtbl2;   // 0x0140d9ac

// Intrusive ref-holder used by FUN_00756790 around the newly-built CB24.
struct CB24Ref {
  CB24* p;
  CB24Ref(CB24* o) : p(o) { if (p) ((Ext*)p)->FUN_00768530(); }
  ~CB24Ref() { if (p) ((Ext*)p)->FUN_0067da30(); }
};

// ---------------------------------------------------------------------------
// cJob / job manager.
// ---------------------------------------------------------------------------
struct cJob {
  void (*mpCallback)(void*);    // +0x00
  void* mpCallbackData;         // +0x04
  char pad_08[0x10];
  int mFlags;                   // +0x18
  int mSlot;                    // +0x1c
};

struct cJobRef {
  cJob* p;
  cJobRef() : p(0) {}
  cJobRef(cJobRef const& o) {
    p = o.p;
    if (p) ((Ext*)p)->FUN_0068f950();
  }
  ~cJobRef() { if (p) ((Ext*)p)->FUN_00690120(); }
  cJobRef& operator=(const cJobRef& o) {
    cJob* t = o.p;
    if (t != p) {
      if (t) ((Ext*)t)->FUN_0068f950();
      cJob* old = p;
      p = t;
      if (old) ((Ext*)old)->FUN_00690120();
    }
    return *this;
  }
};

struct IJobManager {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual bool CreateJob(void** out);   // +0x10
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void Lock();                  // +0x20
  virtual void Unlock();                // +0x24
};
IJobManager* FUN_0068f4d0();            // 0x0068f4d0

// ---------------------------------------------------------------------------
// The 0x6c-byte job-start object (ctor in slice s007553c0).
// ---------------------------------------------------------------------------
class X_7565a0 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2(int);
  char pad_0[0x6c - 4];
  X_7565a0(int, int);
  bool FUN_007564b0(cJobRef* out);
};

// ---------------------------------------------------------------------------
// The model-region object (`this` of 0x00756a20..0x00756fc0).
// ---------------------------------------------------------------------------
struct CModelRegion {
  char pad_00[0x0c];
  int  mField0c;          // +0x0c
  char pad_10[0x04];
  int  mSlotInt;          // +0x14  (array, stride 4)
  char pad_18[0x0c];
  float mSlotFloat;       // +0x24  (array, stride 4)
  char pad_28[0x0c];
  int  mSlotFlags;        // +0x34  (array, stride 4)
  char pad_38[0x0c];
  void* mSlotJob;         // +0x44  (array of IObject*, stride 4)
  char pad_48[0x0c];
  char mMeshCtx;          // +0x54
  char pad_55[0x2f];      // -> +0x84
  void** mpPtr84;         // +0x84
  char pad_88[0x10];      // -> +0x98
  int  mField98;          // +0x98
  char pad_9c[0x14];      // -> +0xb0
  char mFieldB0;          // +0xb0
  char pad_b1[0x03];
  void* mSlotHolder;      // +0xb4  (array of PartHolder*, stride 4)
  char pad_b8[0x0c];      // -> +0xc4
  char mFieldC4;          // +0xc4
  char mFieldC5;          // +0xc5
  char pad_c6[0x02];
  char mVecC8;            // +0xc8
  char pad_c9[0x13];      // -> +0xdc
  char mGlyphDC;          // +0xdc
  char pad_dd[0x03];      // -> +0xe0
  char mGlyphE0;          // +0xe0
  char pad_e1[0x13];      // -> +0xf4
  char mVecF4;            // +0xf4
  char pad_f5[0x0b];      // -> +0x100
  void* mp100;            // +0x100
  void* mField108;        // +0x108

  bool FUN_00756a20(cJob* job);
  bool FUN_00756b50(cJob* job);
  bool FUN_00756c70(cJob* job);
  bool FUN_00756d80(cJob* job);
};

// 0x140-byte model object created by FUN_00756d80.  vtable 0x0140c464
// (slot0 AddRef 0x00432be0, slot1 Release 0x00763250), refcount at +4.
struct Obj140 {
  void* mpVtbl;               // +0x00  (0x0140c464)
  int   mRefCount;            // +0x04
  char pad_08[0x18 - 8];
  void* mVecBegin18;          // +0x18
  void* mVecEnd1c;            // +0x1c
  char pad_20[0xf4 - 0x20];
  char mVecF4;                // +0xf4
  char pad_f5[0x13];          // -> +0x108
  char mVec108;               // +0x108
  char pad_109[0x37];         // -> +0x140
  Obj140* FUN_007004d0();     // 0x007004d0
};

// Ref-holder for the 0x140-byte model object (AddRef/Release via the object's
// own vtable, slot 0/1 -- the original dispatches indirectly, not by address).
struct VObj {
  virtual void AddRef();
  virtual void Release();
};

struct Obj140Ref {
  Obj140* p;
  Obj140Ref(Obj140* o) : p(o) { if (p) ((VObj*)p)->AddRef(); }
  ~Obj140Ref() { if (p) ((VObj*)p)->Release(); }
};

struct Tmp56280 {
  int   a;      // +0x00
  int   b;      // +0x04
  int   c;      // +0x08
  int   d;      // +0x0c
  int   e;      // +0x10
  void* base;   // +0x14
  uint16_t g;   // +0x18
  uint16_t stride;  // +0x1a
  void* p;      // +0x1c
};

// 0x10-byte record slot inside the region source; also the shape FUN_004728e0
// fills in (count/field/word/word/intrusive-ref at +0xc).
struct Slot7562 {
  int   m10;       // +0x00
  int   m14;       // +0x04
  uint16_t m18;    // +0x08
  uint16_t m1a;    // +0x0a
  IObject* mpRef;  // +0x0c
};

struct RegionSrc {
  char pad_00[8];
  void* mRecords;      // +0x08 (stride 0x20)
  char pad_0c[0x30 - 0x0c];
  void* mVec30;        // +0x30
  void* mVec34;        // +0x34
};

// 0x0041ee90 RefVector::resize / 0x00742f60 Map8::GetOrAdd share begin/end.
struct RefVector {
  void* mBegin;   // +0
  void* mEnd;     // +4
};

// Three consecutive dwords copied as a unit (this+0xf4 -> target+8).
struct F3 {
  int a;   // +0
  int b;   // +4
  int c;   // +8
  F3& operator=(F3 const& o) { a = o.a; b = o.b; c = o.c; return *this; }
};

// MaterialManager vtable (slot 10 @ 0x28).
struct IMaterialMgr {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9();
  virtual void* m10(unsigned int id);   // +0x28
};

// param_2 of FUN_00756860: vtable slot 42 @ 0xa8.
struct IVtA8 {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
  virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
  virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
  virtual void v40(); virtual void v41();
  virtual void* m42(int a, unsigned int b);   // +0xa8
};

// IntVecObj created by FUN_00756280 (ctor ??0IntVecObj@@QAE@HPBH@Z).
struct IntVecObj {
  IntVecObj(int a, int const* b);       // 0x00723720
};

CB24::CB24()
    : m0c(0), m10(0), m14(0), m1c(0), m20(0) {
  mpVtbl = (void*)&CB24_vtbl;
  mpVtbl2 = (void*)&CB24_vtbl2;
  _InterlockedExchange((volatile long*)&mRefCount, 0);
}

// @ 0x00756280
void FUN_00756280(int* self, uint32_t value) {
  int idx = FUN_0071ddc0(self, 0x15, 0, 6, 8);
  if (idx < 0) {
    int n = FUN_0071dd80(self, 8);
    if (n == 0) {
      int cnt = (*(int*)((char*)self + 0x34) - *(int*)((char*)self + 0x30)) / 0x14;
      n = 0;
      if (cnt > 0) {
        int* p = (int*)(*(int*)((char*)self + 0x30) + 0x10);
        do {
          if (n < *p) n = *p;
          p = (int*)((char*)p + 0x14);
          cnt--;
        } while (cnt != 0);
      }
      n = n + 1;
    }
    Tmp56280 tmp;
    tmp.a = 0x15; tmp.b = 0; tmp.c = 6; tmp.d = 8;
    tmp.e = 0; tmp.base = 0; tmp.g = 0; tmp.stride = 0; tmp.p = 0;
    FUN_00720190(n, 4, &tmp.e);
    for (int i = 0; i < n; i++) {
      int off = (uint32_t)tmp.stride * i;
      *(uint32_t*)(off + (int)tmp.base) = value;
    }
    ((Ext*)((char*)self + 8))->FUN_0041f7d0(&tmp);   // vector push_back
    if (tmp.p) ((IObject*)tmp.p)->Release();
  } else {
    char* rec = (char*)(*(int*)((char*)self + 8)) + idx * 0x20;
    int f10 = *(int*)(rec + 0x10);
    IObject* ref = *(IObject**)(rec + 0x1c);
    if (ref) ref->AddRef();
    uint32_t v = value;
    IntVecObj* iv = new ("Graphics", 0, 0, 0, 0) IntVecObj(f10, (int const*)&v);
    Slot7562 buf;
    ((Ext*)iv)->FUN_004728e0(&buf);
    ((Ext*)(rec + 0x10))->FUN_00424f70(&buf);
    if (buf.mpRef) buf.mpRef->Release();
    if (ref) ref->Release();
  }
}

// @ 0x007564b0
bool X_7565a0::FUN_007564b0(cJobRef* out) {
  cJobRef job;
  IJobManager* mgr = FUN_0068f4d0();
  if (!mgr->CreateJob((void**)&job.p)) {
    return false;
  }
  job.p->mpCallback = (void (*)(void*))&FUN_00755d20;
  job.p->mpCallbackData = this;
  job.p->mFlags = 1;
  ((Ext*)job.p)->FUN_0068f9b0(this);
  out->p = job.p;
  job.p = 0;
  return true;
}

// @ 0x007565a0
bool FUN_007565a0(int param_1, int param_2, cJobRef* param_3) {
  if (param_1 != 0 && param_2 != 0) {
    X_7565a0* p = new ("Graphics", 0, 0, 0, 0) X_7565a0(param_1, param_2);
    if (p != 0) {
      if (p->FUN_007564b0(param_3)) {
        return 1;
      }
      p->a2(1);
    }
  }
  return 0;
}

// @ 0x00756650
bool CB24::FUN_00756650(cJobRef* out, void* b, int c, void* d) {
  m0c = b;
  m10 = 0xe6bce5;
  m14 = c;
  m18 = d;
  cJobRef job;
  IJobManager* mgr = FUN_0068f4d0();
  if (!mgr->CreateJob((void**)&job)) {
    return false;
  }
  job.p->mpCallback = (void (*)(void*))&FUN_00755d30;
  job.p->mpCallbackData = this;
  job.p->mFlags = (int)0x80000000;
  ((Ext*)job.p)->FUN_0068f9b0(this);
  ((Ext*)job.p)->FUN_006909b0();
  cJobRef tmp(job);
  *out = tmp;
  return true;
}

// @ 0x00756790
bool FUN_00756790(cJobRef* out, void* b, int c, void* d) {
  CB24* obj = new ("Graphics", 0, 0, 0, 0) CB24();
  CB24Ref ref(obj);
  bool r = obj->FUN_00756650(out, b, c, d);
  return r;
}

// @ 0x00756860  SP::BuildRegionToInfoMap
bool FUN_00756860(RefVector* map, IVtA8* pObj, int param_3, RegionSrc* src) {
  int idx = FUN_0071ddc0(src, 0x15, 0, 6, 0xe);
  if (idx < 0) return false;
  char* rec = (char*)(*(int*)((char*)src + 8)) + idx * 0x20;
  int f14 = *(int*)(rec + 0x14);
  uint16_t w1a = *(uint16_t*)(rec + 0x1a);
  IObject* ref = *(IObject**)(rec + 0x1c);
  if (ref) ref->AddRef();
  int n = (*(int*)((char*)src + 0x34) - *(int*)((char*)src + 0x30)) / 0x14;
  int off = 0;
  while (n > 0) {
    uint32_t id = *(uint32_t*)(*(int*)(*(int*)((char*)src + 0x30) + 0x10 + off) * (uint32_t)w1a + (int)f14);
    IMaterialMgr* mgr = (IMaterialMgr*)FUN_0067dd70();
    void* r = mgr->m10(id);
    IObject* st = *(IObject**)((char*)r + 4);
    if (st != 0 && (*(uint8_t*)((char*)st + 8) & 8) != 0) {
      void* sd = ((Ext*)st)->FUN_011edcf0(0x20f);
      if (sd != 0) {
        void* x = pObj->m42(param_3, *(unsigned int*)sd);
        void** slot = ((Ext*)map)->FUN_00742f60(sd);
        void* old = *slot;
        if (x != old) {
          if (x) _InterlockedExchangeAdd((volatile long*)((char*)x + 4), 1);
          *slot = x;
          if (old) PartRelease((PartHolder*)old);
        }
      }
    }
    off += 0x14;
    n--;
  }
  if (map->mBegin != map->mEnd) {
    if (ref) ref->Release();
    return true;
  }
  if (ref) ref->Release();
  return false;
}

// @ 0x00756a20
bool CModelRegion::FUN_00756a20(cJob* job) {
  FUN_0067dcd0();
  int iVar1 = *(int*)((char*)this + 0x44 + job->mSlot * 4);
  if (iVar1 == 0) return false;
  IJobManager* mgr = FUN_0068f4d0();
  mgr->Lock();
  cJobRef newJob;
  bool c = FUN_007565a0(iVar1, *(int*)((char*)this + 0x108), &newJob);
  if (!c) {
    mgr->Unlock();
    return false;
  }
  ((Ext*)newJob.p)->FUN_006909b0();
  ((Ext*)job)->FUN_006913c0(newJob.p);
  bool r = ((Ext*)job)->FUN_0068f9f0((void*)&FUN_00753fb0, this);
  mgr->Unlock();
  return r;
}

// @ 0x00756b50
bool CModelRegion::FUN_00756b50(cJob* job) {
  int slot = job->mSlot;
  void* P = *(void**)((char*)this + 0x84);
  PartHolder* ph = new ("Graphics", 0, 0, 0, 0) PartHolder(*(PartHolder**)P);
  PartHolder** pslot = (PartHolder**)((char*)this + 0xb4 + slot * 4);
  PartHolder* old = *pslot;
  if (ph != old) {
    PartAddRef(ph);
    *pslot = ph;
    PartRelease(old);
  }
  int flags = *(int*)((char*)this + 0x34 + slot * 4);
  PartHolder* cur = *pslot;
  if (flags & 2) {
    FUN_007387f0(cur);
  } else if (flags & 4) {
    FUN_007389c0(cur, 1);
  }
  if (flags & 8) {
    FUN_00738900(cur);
  }
  FUN_00728020(cur, *(float*)((char*)this + 0x24 + slot * 4), flags & 1,
               (char*)this + 0x54);
  return true;
}

// @ 0x00756c70
bool CModelRegion::FUN_00756c70(cJob* job) {
  int slot = job->mSlot;
  void** pslot = (void**)((char*)this + 0xb4 + slot * 4);
  void* cur = *pslot;
  if (cur == 0) {
    if (*(int*)((char*)this + 0x34 + slot * 4) == 0) {
      ((Ext*)pslot)->FUN_006df280(*(void**)((char*)this + 0x84));
    } else {
      PartHolder* ph = new ("Graphics", 0, 0, 0, 0)
          PartHolder(*(PartHolder**)*(void**)((char*)this + 0x84));
      ((Ext*)pslot)->FUN_0041d8b0(ph);
      FUN_00753dc0(*pslot, *(int*)((char*)this + 0x34 + slot * 4));
    }
  }
  void* h = *pslot;
  void** p100 = (void**)((char*)this + 0x100);
  if (*p100) {
    IObject* t = (IObject*)*p100;
    *p100 = 0;
    t->Release();
  }
  FUN_00753fe0(p100, h);
  void* d = *p100;
  if (d) {
    *(F3*)((char*)d + 8) = *(F3*)((char*)this + 0xf4);
  }
  return true;
}

// @ 0x00756d80
bool CModelRegion::FUN_00756d80(cJob* job) {
  Obj140* p = 0;
  void** pslot = (void**)((char*)this + 0xb4 + job->mSlot * 4);
  if (*pslot == 0) {
    if (*(int*)((char*)this + 0x34 + job->mSlot * 4) == 0) {
      ((Ext*)pslot)->FUN_006df280(*(void**)((char*)this + 0x84));
    } else {
      void* P = *(void**)((char*)this + 0x84);
      PartHolder* ph = new ("Graphics", 0, 0, 0, 0) PartHolder(*(PartHolder**)P);
      ((Ext*)pslot)->FUN_0041d8b0(ph);
      FUN_00753dc0(*pslot, *(int*)((char*)this + 0x34 + job->mSlot * 4));
    }
  }
  p = new ("Graphics", 0, 0, 0, 0) Obj140;
  if (p) p = p->FUN_007004d0();
  Obj140Ref obj(p);
  FUN_006ac040(4, obj.p);
  void* ctx;
  if (mFieldB0 == 0) ctx = 0;
  else ctx = (char*)this + 0x9c;
  FUN_0072c0a0(*pslot, obj.p, -1, ctx);
  if (mField98 != 0) {
    int a = *(int*)((char*)obj.p + 0xf4);
    int b = *(int*)((char*)obj.p + 0xf8);
    void* cp = FUN_006df700((void*)b, (void*)b, (void*)a);
    ((Ext*)((char*)obj.p + 0xf4))->FUN_0059c410(cp, *(void**)((char*)obj.p + 0xf8));
    *(int*)((char*)obj.p + 0xf8) = *(int*)((char*)obj.p + 0xf8) + ((b - a) >> 2) * -4;
    ((Ext*)((char*)obj.p + 0xf4))->FUN_00755570(
        (unsigned int)((*(int*)((char*)obj.p + 0x1c) - *(int*)((char*)obj.p + 0x18)) >> 2),
        (int)((char*)this + 0x98));
  }
  if ((*(int*)((char*)this + 0x34 + job->mSlot * 4) & 2) == 0) {
    if (mFieldC4 != 0) {
      ((Ext*)((char*)obj.p + 0x108))->FUN_0041f320((void*)((char*)this + 0xc8));
    }
    if (mFieldC5 != 0) {
      ((Ext*)((char*)obj.p + 0xe0))->FUN_007552e0((void*)((char*)this + 0xdc));
    }
  }
  void* old = *(void**)((char*)this + 0x44 + job->mSlot * 4);
  if ((void*)obj.p != old) {
    if (obj.p) ((VObj*)obj.p)->AddRef();
    *(void**)((char*)this + 0x44 + job->mSlot * 4) = obj.p;
    if (old) ((VObj*)old)->Release();
  }
  unsigned int arr[3];
  arr[0] = *(unsigned int*)((char*)this + 0x0c);
  arr[1] = 0xe6bce5;
  arr[2] = *(unsigned int*)((char*)this + 0x14 + job->mSlot * 4);
  FUN_006acfe0(arr, (char*)obj.p);
  return true;
}

// @ 0x00756fc0
void FUN_00756fc0(RefVector* a, RefVector* b) {
  if (a != b) {
    ((Ext*)b)->FUN_0041ee90((unsigned int)(((int)a->mEnd - (int)a->mBegin) >> 2));
  }
  void** base = (void**)a->mBegin;
  unsigned int i = 0;
  if ((((int)a->mEnd - (int)a->mBegin) >> 2) != 0) {
    do {
      void* e = base[i];
      if (!FUN_00732360(e)) {
        void** dst = (void**)b->mBegin;
        void* old = dst[i];
        if (e != old) {
          PartAddRef((PartHolder*)e);
          dst[i] = e;
          PartRelease((PartHolder*)old);
        }
      } else {
        PartHolder* ph = new ("Graphics", 0, 0, 0, 0) PartHolder((PartHolder const*)e);
        PartAddRef(ph);
        FUN_00733f20(ph);
        FUN_007345c0(ph);
        void** dst = (void**)b->mBegin;
        void* old = dst[i];
        if (ph != (PartHolder*)old) {
          PartAddRef(ph);
          dst[i] = ph;
          PartRelease((PartHolder*)old);
        }
        PartRelease(ph);
      }
      base = (void**)a->mBegin;
      i++;
    } while (i < (unsigned int)(((int)a->mEnd - (int)a->mBegin) >> 2));
  }
}
