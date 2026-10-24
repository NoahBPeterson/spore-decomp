// slice s007553c0 -- cGameModelWriteJob / cJob load/cache helpers.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2.
// Byte-exact: FUN_00755520, FUN_00755d40, FUN_00755fe0.  The rest are
// best-effort translations.

#include "types.h"

// ---- intrinsics (MSVC) -----------------------------------------------------
extern "C" long __stdcall _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __stdcall _InterlockedExchange(volatile long*, long);

// ---------------------------------------------------------------------------
// Callees (masked relocations): signatures/conventions only.
// ---------------------------------------------------------------------------
char FUN_007559a0(int, int, char);
char FUN_006b4b60(void*, void*, int, int);
void* GetManager_755d40();
void FUN_007553b0();
void FUN_00755560();
void FUN_00753fa0();
void FUN_00429e00(int, unsigned int, int);
int FUN_006df700(int, int, int);
void FUN_0059c410(int, int);
void* FUN_006f43e0(void*, void*, void*);
void FUN_007140e0(void*, void*, int);
void* FUN_0067dd60();
void FUN_00700670(void*, void*, void*);
void FUN_00d018d0(void*, void*, void*);
void FUN_0041f270(void*);
void FUN_0041f320(void*, void*);
void FUN_007552e0(void*, void*);
char FUN_00754310(void*, int, int);
char FUN_006a1250(void*, int, void*);
char FUN_006b2090(int, char);
int FUN_00fc7e50(void*);
char FUN_0068f9f0(void*, void*, void*);   // cJob::Continuation
void FUN_006913c0(void*, void*);          // cJob::AddWeakDependency
void* FUN_007004d0(void*);
void FUN_0072c100(int, void*, int, int);
void* operator_new_f473a0(unsigned, const char*, int, int, int, int);
void operator_delete_f47380(void*);
void __stdcall vec_dtor_iter_(void*, unsigned, int, void*);
void FUN_00472520(void*);
void FUN_007a9610(void*);

// ---------------------------------------------------------------------------
// ABI shims: this-in-ecx + stack args (declared as struct members so MSVC
// emits the thiscall form).  Symbol names are relocation-masked.
// ---------------------------------------------------------------------------
struct Callee {
  void  v0();
  void  v1(void* a);
  void  v2(void* a, void* b);
  void  v3(void* a, void* b, void* c);
  void  v5(void* a, void* b, void* c, void* d, void* e);
  void  v8(void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
  void* p0();
  void* p1(void* a);
  char  c2(void* a, void* b);
  char  c3(void* a, void* b, void* c);
  char  c5(void* a, void* b, void* c, void* d, void* e);
  char  c6(void* a, void* b, void* c, void* d, void* e, void* f);
};

// vtable dispatch on a raw object pointer (indirect; no symbol to resolve).
#define VTSLOT(p, off) ((*(void***)(p))[((off) / 4)])

// named this-in-ecx callees whose `this` is a sub-object of the class.
struct TC0 { void FUN_0041f270(); };
struct TC1 { void FUN_0041f320(void* a); void FUN_007552e0(void* a); };
struct TC2 { void FUN_00700670(void* a, void* b); void FUN_00d018d0(void* a, void* b);
            void FUN_004243e0(void* a, void* b); };

typedef void (__thiscall *PFN_v)(void*);

// managed-object AddRef/Release by vtable slot; base either at +0 or +4.
static inline void Add0(void* o) { if (o) ((PFN_v)(*(void***)o)[0])(o); }
static inline void Rel0(void* o) { if (o) ((PFN_v)(*(void***)o)[1])(o); }
static inline void Add4(void* o) { if (o) { void* b = (char*)o + 4; ((PFN_v)(*(void***)b)[0])(b); } }
static inline void Rel4(void* o) { if (o) { void* b = (char*)o + 4; ((PFN_v)(*(void***)b)[1])(b); } }

// intrusive refcount release (refcount at obj+4); clears the slot first.
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

// intrusive refcount release without clearing the field.
static inline void RefReleaseCore(void* o) {
  if (!o) return;
  volatile long* rc = (volatile long*)((char*)o + 4);
  long old = _InterlockedExchangeAdd(rc, -1);
  if (old == 1) {
    _InterlockedExchange(rc, 1);
    ((void(__thiscall*)(void*, int))(*(void***)o)[0])(o, 1);
  }
}

// AutoRefCount element vector clear: release the range and reset mpEnd.
static inline void ClearRefVec(void** pBegin, void** pEnd) {
  void* r = (void*)FUN_006df700((int)*pEnd, (int)*pEnd, (int)*pBegin);
  FUN_0059c410((int)r, (int)*pEnd);
  *pEnd = *pBegin;
}

static inline void FreeBuffer(void* p) {
  if (p && *(int*)((char*)p - 4) != 0) operator_delete_f47380(p);
}

// ---------------------------------------------------------------------------
// 007553c0 base class (also used by 00755470 / 00755c80).
// ---------------------------------------------------------------------------
struct CS553 {
  void* mpV0;         // +0x00
  void* mpV1;         // +0x04
  int   mAtom;        // +0x08
  void* mpBegin;      // +0x0c
  void* mpEnd;        // +0x10
  void* mpCap;        // +0x14
  void* m18;          // +0x18
  void* m1c;          // +0x1c
  void* m20;          // +0x20
  void* mInline[16];  // +0x24 .. +0x63
  void* m64;          // +0x64
  void* m68;          // +0x68

  void ctor553(void* a1, void* a2);
  void dtor554();
  void f55c80(void* job);
};

// @ 0x007553c0  (160 bytes) EH constructor
void CS553::ctor553(void* a1, void* a2) {
  mpV0 = (void*)0x13f1ab0;
  mpV1 = (void*)0x13ef094;
  _InterlockedExchange((volatile long*)&mAtom, 0);
  mpV0 = (void*)0x140d9d8;
  mpV1 = (void*)0x140d9d4;
  void* base = &mInline[0];
  mpBegin = base;
  mpEnd = base;
  m20 = 0;
  mpCap = (void*)((char*)this + 0x64);
  m64 = a2;
  Add4(a2);
  m68 = a1;
  Add0(a1);
}

// @ 0x00755470  (143 bytes) EH destructor
void CS553::dtor554() {
  Rel0(m68);
  Rel4(m64);
  ((Callee*)&mpBegin)->v2(mpBegin, mpEnd);
  FreeBuffer(mpBegin);
  mpV1 = (void*)0x13ef094;
  mpV0 = (void*)0x13eb938;
}

// @ 0x00755c80  (153 bytes) job setup / ResourceMan swap
void CS553::f55c80(void* job) {
  void* mgr = GetManager_755d40();
  if (m20) { void* p = m20; m20 = 0; Rel0(p); }
  if (m1c) { void* p = m1c; m1c = 0; Rel0(p); }
  ((void(__thiscall*)(void*, void*, void*, void*, void*, void*, void*, void*, void*))VTSLOT(mgr, 0x10))
      (mgr, &mpBegin, &m1c, &m20, 0, 0, 0, 0, 0);
  void* r = m1c;
  if (r) {
    void* n = ((void*(__thiscall*)(void*, void*))VTSLOT(r, 0xc))(r, (void*)0x3a212ac);
    if (n) {
      int t = FUN_00fc7e50(n);
      FUN_006913c0(job, (void*)t);
    }
  }
  *(int*)((char*)job + 0x18) = 1;
  FUN_0068f9f0(job, (void*)FUN_00755560, this);
}

// ---------------------------------------------------------------------------
// 00755520 / 00755570 / 00755d40 / 00755fe0 : byte-exact.
// ---------------------------------------------------------------------------
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

// @ 0x00755520
struct cJob_755520 {
  char pad_0[0x18];
  int mThreadAffinity;  // +0x18
  bool Continuation(void* fn, void* arg);
};
struct X_755520 {
  bool FUN_00754770(cJob_755520* job);
  bool FUN_00755520(cJob_755520* job);
};
bool X_755520::FUN_00755520(cJob_755520* job) {
  if (FUN_00754770(job)) {
    return true;
  }
  job->mThreadAffinity = 0x80000000;
  return job->Continuation((void*)&FUN_007553b0, this);
}

// @ 0x00755570  (92 bytes) vector resize/insert
struct V_755570 {
  int* mBegin;
  int* mEnd;
  void FUN_00755570(unsigned int param_2, int param_3);
};
void V_755570::FUN_00755570(unsigned int param_2, int param_3) {
  int* param_1 = (int*)this;
  int iVar2 = param_1[1];
  unsigned int uVar3 = (unsigned int)(iVar2 - *param_1) >> 2;
  if (uVar3 < param_2) {
    FUN_00429e00(iVar2, param_2 - uVar3, param_3);
    return;
  }
  int iVar1 = *param_1 + param_2 * 4;
  int uVar4 = FUN_006df700(iVar2, iVar2, iVar1);
  FUN_0059c410(uVar4, param_1[1]);
  param_1[1] = param_1[1] + ((iVar2 - iVar1 >> 2) * -4);
}

// @ 0x00755d40
void FUN_00755d40(int param_1, int param_2, char param_3) {
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

// @ 0x00755fe0
class S_755fe0 {
 public:
  char pad_0[0x104];
  IFoo_755d40* m104;  // +0x104
  int m108;           // +0x108
  void FUN_00755fe0(void* arg);
};
void S_755fe0::FUN_00755fe0(void* arg) {
  (void)arg;
  GetManager_755d40();
  int uVar1 = m108;
  IFoo_755d40* piVar2 = m104;
  if (piVar2 != 0) {
    int iVar3 = piVar2->a3(0xe6bce5);
    if (iVar3 != 0) {
      FUN_007559a0(iVar3, uVar1, 1);
      return;
    }
  }
  FUN_006b4b60(piVar2, (void*)uVar1, 0, 0);
}

// ---------------------------------------------------------------------------
// 007555d0 cGameModelWriteJob::CacheGameModelToDiskJob_KDTree.
// ---------------------------------------------------------------------------
// model object with the texture RefVec at +0xf4/+0xf8.
struct CMdl {
  uint32_t pad00[6];    // +0x00 .. +0x17
  void* m18;            // +0x18
  void* m1c;            // +0x1c
  uint32_t pad20[0x11]; // +0x20 .. +0x63
  void* m64;            // +0x64
  void* m68;            // +0x68
  uint32_t pad6c[0x1d]; // +0x6c .. +0xdf
  void* mE0;            // +0xe0
  uint32_t pade4[4];    // +0xe4 .. +0xf3
  void* mF4;            // +0xf4
  void* mF8;            // +0xf8
  uint32_t padfc[3];    // +0xfc .. +0x107
  void* m108;           // +0x108
  uint32_t pad10c[0xc]; // +0x10c .. +0x13b
  int   m13c;           // +0x13c
};

struct CGMW {
  uint32_t pad00[3];       // +0x00 .. +0x0b
  void* mpTexBegin;        // +0x0c
  void* mpTexEnd;          // +0x10
  void* mpTexCap;          // +0x14
  uint32_t pad18[0x13];    // +0x18 .. +0x63
  void* mpResourceObject;  // +0x64
  void* mpModel;           // +0x68

  char CacheGameModelToDiskJob_KDTree(void* job);
};

// temporary pointer list used while collecting textures.
struct PtrList {
  void* mItems[256];
  int   mCount;
  void init() { mCount = 0; }
  bool contains(void* p) const {
    for (int i = 0; i < mCount; i++) if (mItems[i] == p) return true;
    return false;
  }
  void push(void* p) { if (mCount < 256) mItems[mCount++] = p; }
};

static inline void TexAddRef(void* t) {
  if (t) _InterlockedExchangeAdd((volatile long*)((char*)t + 8), 1);
}
static inline void TexAddRefMore(void* t) {
  if (t) _InterlockedExchangeAdd((volatile long*)((char*)t + 8), 1);
}

// @ 0x007555d0  (563 bytes)
char CGMW::CacheGameModelToDiskJob_KDTree(void* job) {
  CMdl* mdl = (CMdl*)mpModel;
  if (mdl->m13c != 0) {
    if (!FUN_006b4b60((void*)mdl->m13c, mpResourceObject, 0, 0)) {
      return 0;
    }
  }
  PtrList collected;
  collected.init();
  int n = (int)(((char*)mdl->mF8 - (char*)mdl->mF4) >> 2);
  for (int i = 0; i < n; i++) {
    void* node = *(void**)((char*)mdl->mF4 + i * 4);
    if (!node) continue;
    PtrList tmp;
    tmp.init();
    FUN_007140e0(node, &tmp, 0);
    for (int j = 0; j < tmp.mCount; j++) {
      void* t = tmp.mItems[j];
      if (!collected.contains(t)) {
        TexAddRef(t);
        TexAddRefMore(t);
        collected.push(t);
        if (t) RefReleaseCore(t);
      }
    }
  }
  *(int*)((char*)job + 0x1c) = 0;
  char r = FUN_0068f9f0(job, (void*)FUN_00753fa0, this);
  return r;
}

// ---------------------------------------------------------------------------
// 00755810 model construction / registration helper.
// ---------------------------------------------------------------------------
// @ 0x00755810  (388 bytes)
char FUN_00755810(int a1, int a2, int a3, void* a4, int a5, int a6) {
  CMdl* obj = 0;
  void* mem = operator_new_f473a0(0x140, "Graphics", 0, 0, 0, 0);
  if (mem) obj = (CMdl*)FUN_007004d0(mem);
  Add0(obj);
  FUN_0072c100(a1, obj, -1, 0);
  if (a4) {
    ClearRefVec(&obj->mF4, &obj->mF8);
    void* ref = a4;
    _InterlockedExchangeAdd((volatile long*)((char*)ref + 4), 1);
    int cnt = (int)(((char*)obj->m1c - (char*)obj->m18) >> 2);
    ((V_755570*)((char*)obj + 0xf4))->FUN_00755570((unsigned)cnt, (int)ref);
    RefReleaseCore(ref);
  }
  if (a5) ((TC1*)((char*)obj + 0x108))->FUN_0041f320((void*)a5);
  if (a6) ((TC1*)((char*)obj + 0xe0))->FUN_007552e0((void*)a6);
  char r = FUN_00754310(obj, a2, a3);
  Rel0(obj);
  return r;
}

// ---------------------------------------------------------------------------
// 007559a0 collect textures of a model and dispatch.
// ---------------------------------------------------------------------------
// @ 0x007559a0  (724 bytes)
char FUN_007559a0(int param_1, int param_2, char param_3) {
  char bOK = 1;
  GetManager_755d40();
  if (*(int*)(param_1 + 0x13c) != 0) {
    bOK = FUN_006b2090(*(int*)(param_1 + 0x13c), param_3) != 0;
  }
  PtrList collected;
  collected.init();
  int n = (int)((*(int*)(param_1 + 0xf8) - *(int*)(param_1 + 0xf4)) >> 2);
  for (int i = 0; i < n; i++) {
    void* node = *(void**)(*(int*)(param_1 + 0xf4) + i * 4);
    if (!node) continue;
    PtrList tmp;
    tmp.init();
    FUN_007140e0(node, &tmp, 0);
    for (int j = 0; j < tmp.mCount; j++) {
      if (!collected.contains(tmp.mItems[j])) collected.push(tmp.mItems[j]);
    }
  }
  if (collected.mCount != 0) {
    void* m = FUN_0067dd60();
    if (m && param_2 != 0) {
      for (int i = 0; i < collected.mCount; i++) {
        if (bOK) {
          char c = ((char(__thiscall*)(void*, void*, void*, void*))VTSLOT(m, 0x44))
                       (m, collected.mItems[i], (void*)param_2, (void*)param_3);
          if (c == 0) bOK = 0;
        } else {
          bOK = 0;
        }
      }
    }
  }
  char res = 0;
  if (param_3 == 0) {
    if (bOK) {
      void* mgr = GetManager_755d40();
      res = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*))VTSLOT(mgr, 0x20))
                (mgr, (void*)param_1, 0, (void*)param_2, 0, 0);
      if (!res) res = 0;
    }
  } else {
    if (bOK) res = FUN_006b4b60((void*)param_1, (void*)param_2, 0, 0);
  }
  return res;
}

// ---------------------------------------------------------------------------
// 00755da0 derived destructor.
// ---------------------------------------------------------------------------
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

// @ 0x00755da0  (561 bytes)
void CS755da0::dtor755da0() {
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

// ---------------------------------------------------------------------------
// 00756030 property-key scan driver.
// ---------------------------------------------------------------------------
typedef char (__cdecl *PFN_d40)(int, int, char);
static inline char Call755d40(int a, int b, char c) {
  return ((PFN_d40)FUN_00755d40)(a, b, c);
}

// @ 0x00756030  (592 bytes)
char FUN_00756030(int param_1, int param_2) {
  void* mgr = GetManager_755d40();
  int key[3];
  key[0] = param_1;
  key[1] = 0xb1b104;
  key[2] = param_2;
  void* holder = 0;
  char ok = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*, void*))VTSLOT(mgr, 0xc))
              (mgr, (void*)key, &holder, 0, 0, 0, 0);
  if (ok == 0) {
    key[1] = 0xe6bce5;
    if (holder) { void* p = holder; holder = 0; Rel0(p); }
    void* obj2 = 0;
    char f2 = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*, void*))VTSLOT(mgr, 0xc))
                  (mgr, (void*)key, &obj2, 0, 0, 0, 0);
    if (f2 != 0) {
      char r = Call755d40((int)obj2, key[0], (char)key[1]);
      if (obj2) Rel0(obj2);
      return r;
    }
    if (obj2) Rel0(obj2);
    return 0;
  }
  char state = 1;
  char pc = (char)param_2;
  void* cur = 0;
  for (int i = 0; i < 4; i++) {
    int key2[3];
    if (FUN_006a1250(holder, i + 0xf9efbb, key2)) {
      if (cur) { void* p = cur; cur = 0; Rel0(p); }
      char c = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*, void*))VTSLOT(mgr, 0xc))
                   (mgr, (void*)key2, &cur, 0, 0, 0, 0);
      if (c != 0) {
        char r = Call755d40((int)cur, param_1, pc);
        if (r == 0 || state == 0) state = 0; else state = 1;
      }
    }
  }
  char fin;
  bool dispatched = false;
  if (holder) {
    int r2 = ((IFoo_755d40*)holder)->a3(0xe6bce5);
    if (r2 != 0) {
      fin = FUN_007559a0(r2, param_1, pc);
      dispatched = true;
    }
  }
  if (!dispatched) {
    if (pc == 0) {
      void* m2 = GetManager_755d40();
      fin = ((char(__thiscall*)(void*, void*, void*, void*, void*, void*))VTSLOT(m2, 0x20))
                (m2, (void*)holder, 0, (void*)param_1, 0, 0);
    } else {
      fin = FUN_006b4b60((void*)holder, (void*)key, 0, 0);
    }
  }
  char out = (fin != 0 && state != 0) ? 1 : 0;
  if (cur) Rel0(cur);
  if (holder) Rel0(holder);
  return out;
}