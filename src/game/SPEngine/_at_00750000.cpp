// src/game/SPEngine/_at_00750000.cpp -- migrated from slice(s) s00756280, s007553c0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00750000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __stdcall _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __stdcall _InterlockedExchange(volatile long*, long);

// ---- items of slice s007553c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __stdcall _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __stdcall _InterlockedExchange(volatile long*, long);
char FUN_007559a0(int, int, char);
char FUN_006b4b60(void*, void*, int, int);
void* GetManager_755d40();
int FUN_006df700(int, int, int);
void __stdcall FUN_0059c410(int, int);
void FUN_00700670(void*, void*, void*);
void FUN_00d018d0(void*, void*, void*);
void FUN_0041f270(void*);
void operator_delete_f47380(void*);
void __stdcall vec_dtor_iter_(void*, unsigned, int, void*);
void FUN_00472520(void*);
void FUN_007a9610(void*);
struct TC0 { void FUN_0041f270(); };
struct TC2 { void FUN_00700670(void* a, void* b); void FUN_00d018d0(void* a, void* b);
            void FUN_004243e0(void* a, void* b); };
typedef void (__thiscall *PFN_v)(void*);
static inline void Rel0(void* o) { if (o) ((PFN_v)(*(void***)o)[1])(o); }
static inline void Rel4(void* o) { if (o) { void* b = (char*)o + 4; ((PFN_v)(*(void***)b)[1])(b); } }
static inline void RefReleaseSlot(void** slot) {
  void* o = *slot;
  if (!o) return;
  *slot = 0;
  volatile long* rc = (volatile long*)((char*)o + 4);
  long old = _InterlockedExchangeAdd(rc, -1);
  if (old == 1) {
    _InterlockedExchange(rc, 1);
    ((void(__thiscall*)(void*, int))(*(void***)o)[0])(o, 1);
  }
}
static inline void RefReleaseCore(void* o) {
  if (!o) return;
  volatile long* rc = (volatile long*)((char*)o + 4);
  long old = _InterlockedExchangeAdd(rc, -1);
  if (old == 1) {
    _InterlockedExchange(rc, 1);
    ((void(__thiscall*)(void*, int))(*(void***)o)[0])(o, 1);
  }
}
static inline void ClearRefVec(void** pBegin, void** pEnd) {
  void* r = (void*)FUN_006df700((int)*pEnd, (int)*pEnd, (int)*pBegin);
  FUN_0059c410((int)r, (int)*pEnd);
  *pEnd = *pBegin;
}
static inline void FreeBuffer(void* p) {
  if (p && *(int*)((char*)p - 4) != 0) operator_delete_f47380(p);
}
class IFoo_755d40 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual int a3(unsigned int id);
  virtual void a4();
  virtual void a5();
  virtual void a6();
  virtual void a7();
  virtual void a8(void*, int, int, int, int);
};
struct CS755da0 {
  void* mpV0;         // +0x00
  void* mpV1;         // +0x04
  uint32_t pad08[15]; // +0x08 .. +0x43
  void* m44[4];       // +0x44 .. +0x53
  uint32_t pad54[12]; // +0x54 .. +0x83
  void* m84;          // +0x84
  void* m88;          // +0x88
  uint32_t pad8c[3];  // +0x8c .. +0x97
  void* m98;          // +0x98
  void* m9c;          // +0x9c
  void* ma0;          // +0xa0
  uint32_t pada4[4];  // +0xa4 .. +0xb3
  void* mB4[4];       // +0xb4 .. +0xc3
  uint32_t padc4[1];  // +0xc4 .. +0xc7
  void* mC8;          // +0xc8
  void* mCC;          // +0xcc
  uint32_t padd0[3];  // +0xd0 .. +0xdb
  void* mDC;          // +0xdc
  void* mE0;          // +0xe0
  uint32_t pade4[7];  // +0xe4 .. +0xff
  void* m100;         // +0x100
  void* m104;         // +0x104
  void* m108;         // +0x108

  void dtor755da0();
};
// ---- items of slice s007553c0 end

// ---- items of slice s00756280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char CB24_vtbl;    // 0x0140d9b0
extern const char CB24_vtbl2;   // 0x0140d9ac
extern const char CB24Base_vtbl;    // 0x013f1ab0
extern const char CB24Base_vtbl2;   // 0x013ef094
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange)
void* operator new(unsigned int, const char*, int, unsigned int, unsigned int, int);   // 0x00f473a0
void operator delete(void*, const char*, int, unsigned int, unsigned int, int);   // 0x00f47410
int   FUN_0071ddc0(void* self, int a, int b, int c, int d);
void* FUN_0067dd70();                          // SP::MaterialManager
void  FUN_0067dcd0();                          // EA::ResourceMan::GetManager
void  FUN_007387f0(void* p);
void  FUN_007389c0(void* p, int a);
void  FUN_00738900(void* p);
void  FUN_00728020(void* ctx, float f, int flag, void* p);
char  FUN_00732360(void* p);
void  FUN_00733f20(void* p);
void  FUN_007345c0(void* p);
void  FUN_00755d20();
void  FUN_00755d30();
void  FUN_00753fb0();
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
struct IObject {
  virtual int AddRef();
  virtual int Release();
};
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
struct cJobRef;
struct CB24Base {
  void* mpVtbl;      // +0x00
  void* mpVtbl2;     // +0x04
  int   mRefCount;   // +0x08
  CB24Base();
};
struct CB24 : CB24Base {
  void* m0c;         // +0x0c
  int   m10;         // +0x10
  int   m14;         // +0x14
  void* m18;         // +0x18
  int   m1c;         // +0x1c
  int   m20;         // +0x20
  CB24();
  bool FUN_00756650(cJobRef* out, void* b, int c, void* d);
};
struct CB24Ref {
  CB24* p;
  CB24Ref(CB24* o) : p(o) { if (p) ((void(__thiscall*)(void*))(*(void***)p)[0])(p); }
  ~CB24Ref() { if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p); }
};
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
  cJob** Out() {
    if (p) {
      cJob* o = p;
      p = 0;
      ((Ext*)o)->FUN_00690120();
    }
    return &p;
  }
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
class X_7565a0 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2(int);
  char pad_0[0x6c - 4];
  X_7565a0(int, int);
  bool FUN_007564b0(cJobRef* out);
};
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
struct RegionSrc {
  char pad_00[8];
  void* mRecords;      // +0x08 (stride 0x20)
  char pad_0c[0x30 - 0x0c];
  void* mVec30;        // +0x30
  void* mVec34;        // +0x34
};
struct RefVector {
  void* mBegin;   // +0
  void* mEnd;     // +4
};
struct IMaterialMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
  virtual void* m10(unsigned int id);   // +0x28
};
struct IVtA8 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
  virtual void* m42(int a, unsigned int b);   // +0xa8
};
CB24Base::CB24Base() {
  mpVtbl = (void*)&CB24Base_vtbl;
  mpVtbl2 = (void*)&CB24Base_vtbl2;
  volatile long* rc = (volatile long*)&mRefCount;
  _InterlockedExchange(rc, 0);
}
CB24::CB24() {
  mpVtbl = (void*)&CB24_vtbl;
  mpVtbl2 = (void*)&CB24_vtbl2;
  m0c = 0; m10 = 0; m14 = 0; m1c = 0; m20 = 0;
}
// ---- items of slice s00756280 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool FUN_007565a0(int param_1, int param_2, cJobRef* param_3);  // 0x007565a0 (stays in the slice: not this object's)

// @ 0x00755d40
void FUN_00755d40(int param_1, int param_2, char param_3)
{
  if (param_1 != 0) {
    int r = ((IFoo_755d40*)param_1)->a3(0xe6bce5);
    if (r != 0) {
      FUN_007559a0(r, param_2, param_3);
      return;
    }
  }
  if (param_3 != 0) {
    FUN_006b4b60((void*)param_1, (void*)param_2, 0, 0);
    return;
  }
  IFoo_755d40* mgr = (IFoo_755d40*)GetManager_755d40();
  mgr->a8((void*)param_1, 0, param_2, 0, 0);
}

// @ 0x00755da0
void CS755da0::dtor755da0()
{
  mpV0 = (void*)0x140d9c4;
  mpV1 = (void*)0x140d9c0;
  ClearRefVec(&m84, &m88);
  ((TC2*)&mC8)->FUN_00700670(mC8, mCC);
  ((TC2*)&mDC)->FUN_00d018d0(mDC, mE0);
  for (int i = 0; i < 4; i++) RefReleaseSlot(&mB4[i]);
  Rel4(m108);
  Rel0(m104);
  Rel0(m100);
  FreeBuffer(mDC);
  ((TC0*)&mC8)->FUN_0041f270();
  vec_dtor_iter_((void*)mB4, 4u, 4, (void*)FUN_00472520);
  FUN_0059c410((int)m9c, (int)ma0);
  FreeBuffer(m9c);
  RefReleaseCore(m98);
  ((TC2*)&m84)->FUN_004243e0(m84, m88);
  FreeBuffer(m84);
  vec_dtor_iter_((void*)m44, 4u, 4, (void*)FUN_007a9610);
  mpV1 = (void*)0x13ef094;
  mpV0 = (void*)0x13eb938;
}

// @ 0x007564b0
bool X_7565a0::FUN_007564b0(cJobRef* out)
{
  cJobRef job;
  IJobManager* mgr = FUN_0068f4d0();
  if (!mgr->CreateJob((void**)job.Out())) {
    return false;
  }
  cJob* j = job.p;
  j->mpCallback = (void (*)(void*))&FUN_00755d20;
  j->mpCallbackData = this;
  job.p->mFlags = 1;
  ((Ext*)job.p)->FUN_0068f9b0(this);
  out->p = job.p;
  job.p = 0;
  return true;
}

// @ 0x00756650
bool CB24::FUN_00756650(cJobRef* out, void* b, int c, void* d)
{
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
bool FUN_00756790(cJobRef* out, void* b, int c, void* d)
{
  CB24* obj = new ("Graphics", 0, 0, 0, 0) CB24();
  CB24Ref ref(obj);
  bool r = obj->FUN_00756650(out, b, c, d);
  return r;
}

// @ 0x00756860
bool FUN_00756860(RefVector* map, IVtA8* pObj, int param_3, RegionSrc* src)
{
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
bool CModelRegion::FUN_00756a20(cJob* job)
{
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
bool CModelRegion::FUN_00756b50(cJob* job)
{
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

// ---- items of slice s0075a550 (verbatim; no canonical class) ----
struct B4 { unsigned char b[4]; };

struct Controller {
    void*    mpFrameList;       // +0x00
    void*    mpVtbl;            // +0x04
    char*    mpData;            // +0x08
    B4       mFlags;            // +0x0c
    int      mFrameStride;      // +0x10  bytes per frame
    int      mNumFrames;        // +0x14
    int      mDirty;            // +0x18
    void* Alloc(unsigned size, int nAdd, int numFrames, B4 flags, int hasFrames);  // 0x011fda60
};

// rw::BaseResourceDescriptor: {size, alignment}; its ctor/dtor are out of line so that arrays of
// it go through __ehvec_ctor / __ehvec_dtor as in the original.
struct BaseResourceDescriptor {
    unsigned mSize;
    unsigned mAlign;
    BaseResourceDescriptor();            // 0x006c0fa0
    ~BaseResourceDescriptor();           // 0x00c2e4e0
};
struct ResourceDescriptor { BaseResourceDescriptor d[4]; };

// an interpolator element (stride mInterpolatorStride).  A 4-byte non-polymorphic
// base puts the vfptr at +4, matching the original's `mov edx,[ecx+4]` virtual calls.
struct InterpBase { int dummy; };
struct Interp : InterpBase {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual float Virt16();
    virtual void  Virt14(float);
    char* mpFrameData;   // +0x08
    B4    mFlags;        // +0x0c
    int   mFrameStride;  // +0x10
    int   mNumFrames;    // +0x14
    int   mDirty;        // +0x18
    void* mp1c;      // +0x1c
    float mf20;      // +0x20
    void Fb220();
    void Fb600(float);
    void* FrameAt(int frame);   // 0x011fda50
    static ResourceDescriptor GetResourceDescriptor(int n, B4 flags, int x);   // 0x011fe550
};



struct cMultiBlender : Controller {
    unsigned m_maxNumQuats;         // +0x1c
    void*    m_BlendCallBack;       // +0x20
    float*   mWeights;              // +0x24
    bool*    mAnimating;            // +0x28
    bool*    mBlending;             // +0x2c
    char*    mInterpolators;        // +0x30
    char*    mPoseKeys;             // +0x34
    int      mMaxAnims;             // +0x38
    unsigned mInterpolatorStride;   // +0x3c
    int      mNumAnims;             // +0x40
    float    mTotalWeight;          // +0x44
    int      mFirstBlend;           // +0x48
    int      mFirstAdd;             // +0x4c
    bool     mLooping;              // +0x50

    Interp* At(int i) { return (Interp*)(mInterpolators + i * (int)mInterpolatorStride); }

    bool  AnyAnimating();           // 0075a6e0
    int   AddWeight();              // 0075a710
    void  F690(float arg);          // 0075a690
    int   F780(float arg);          // 0075a780
    int   F7d0(float arg);          // 0075a7d0
    float SumWeight();              // 0075a820
    void  F880(float arg);          // 0075a880
    void  F8c0(B4 arg);             // 0075a8c0
    int   F900(void* arg);          // 0075a900
    void  Fb410();                  // 0075b410
    int   Fb440(float arg);         // 0075b440
    static ResourceDescriptor GetResourceDescriptor(int n, B4 flags, int count, int addA, int addB);  // 0075b190
};

// @ 0x0075a6e0
bool cMultiBlender::AnyAnimating() {
    int n = mNumAnims;
    for (int i = 0; i < n; ++i) {
        if (mAnimating[i] != 0) return true;
    }
    return false;
}

// 0x0075a690: not byte-exact; the byte-exact version is the lifted one in match/slices/s0075a690/s0075a690.cpp
void cMultiBlender::F690(float arg) {
    int n = mNumAnims;
    if (n > 0) {
        for (int i = 0; i < n; ++i) At(i)->Fb600(arg);
    }
    *(int*)((char*)this + 0x18) = 0;
}
