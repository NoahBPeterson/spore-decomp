// slice s00754310 -- SP::RegisterModel / CreateModelInstance / model-instance jobs.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2.  Byte-exact: CreateModelInstance.
// The remaining functions are complete translations (not byte-exact yet).

#include "types.h"

// ---------------------------------------------------------------------------
// Callees (masked relocations): signatures/conventions only.
// ---------------------------------------------------------------------------
bool FUN_00754960(void*, void*, void*);
void FUN_006acfe0(void*, void*);
void FUN_0067dd60();
void FUN_007004d0();

class RefT_007545b0 {
 public:
  virtual int AddRef();
  virtual int Release();
};

// Virtual-call helpers: call the vtable slot at byte offset `off` (thiscall).
typedef int(__thiscall* VF0)(void*);
typedef int(__thiscall* VF1)(void*, int);
typedef int(__thiscall* VF2)(void*, int, int);
typedef int(__thiscall* VF3)(void*, int, int, int);
typedef int(__thiscall* VF8)(void*, int, int, int, int, int, int, int, int);
typedef int(__thiscall* VF6)(void*, int, int, int, int, int, int);
#define VSLOT(o, off) ((*(void***)(o))[(off) / 4])
static inline int vc0(void* o, int off) { return ((VF0)VSLOT(o, off))(o); }
static inline int vc1(void* o, int off, int a) { return ((VF1)VSLOT(o, off))(o, a); }
static inline int vc2(void* o, int off, int a, int b) { return ((VF2)VSLOT(o, off))(o, a, b); }
static inline int vc3(void* o, int off, int a, int b, int c) { return ((VF3)VSLOT(o, off))(o, a, b, c); }
static inline int vc6(void* o, int off, int a, int b, int c, int d, int e, int f) {
  return ((VF6)VSLOT(o, off))(o, a, b, c, d, e, f);
}
static inline int vc8(void* o, int off, int a, int b, int c, int d, int e, int f, int g, int h) {
  return ((VF8)VSLOT(o, off))(o, a, b, c, d, e, f, g, h);
}

// EA::AutoRefCount whose Release is vtable slot 1 (+4).
struct Ref {
  void* p;
  Ref() : p(0) {}
  explicit Ref(void* q) : p(q) {
    if (p) vc0(p, 0);
  }
  ~Ref() {
    if (p) vc0(p, 4);
  }
  void reset() {
    void* o = p;
    if (o) {
      p = 0;
      vc0(o, 4);
    }
  }
};

void* operator new(unsigned int, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, int, int);

struct Key {
  uint32_t a, b, c;
};

// EA::Variant (20 bytes: 16 data bytes, flags, type id).
struct Variant {
  uint32_t data[4];
  uint16_t mFlags;
  uint16_t mTypeId;
  Variant() : mFlags(0), mTypeId(0) {}
  ~Variant() {
    if (mFlags & 4) Destruct(0);
  }
  void SetKey(const Key* k);  // 0x422f40 operator=<Key>
  void Destruct(int a);  // 0x93db80
  void Set(int type, int a, const void* src, int n, int m);  // 0x93dd80
};

// Intrusively counted resource (refcount at +4, destroy via vtable slot 0).
struct Res {
  virtual void Destroy(int flag);
  int rc;
  char pad[0x100 - 8];
  Res();  // 0x740e90
  void Attach(void* ref);  // 0x742b30
  bool Load(void* ref);  // 0x741a40
  void ReleaseOut();  // 0x73a820
};
struct ResPtr {
  Res* p;
  explicit ResPtr(Res* q) : p(q) {
    if (p) p->rc++;
  }
  ~ResPtr() {
    if (p) {
      if (--p->rc == 0) {
        p->rc = 1;
        p->Destroy(1);
      }
    }
  }
};

void* __cdecl PropertyManager();  // 0x67de30
void* __cdecl GetManager();  // 0x67dcd0 (EA::ResourceMan)
void* __cdecl MessageServer();  // 0x67dcc0
bool __cdecl GetPropertyAsKey(void* list, uint32_t id, Key* out);  // 0x6a1250
bool __cdecl FUN_006ad030(const Key* k);
bool __cdecl FUN_006acfe0_k(const Key* k, void* res);  // 0x6acfe0
bool __cdecl GetRwModelAsGameMeshesNoCache(void* obj);  // 0x757d20
void* __cdecl FUN_00759280(void* obj);
void __cdecl SetCachingType(int type, void* obj);  // 0x6ac040
bool __cdecl FUN_007542b0(void* out, Res* r);

class cPropertyList {
 public:
  cPropertyList();  // 0x6a1c40
  void SetParent(void* parent);  // 0x6a1710
};

struct XNode {
  int Type();  // 0xfc7e50 EA::XHTML::DOM::Node::Type
};

struct cJob {
  char pad[0x18];
  uint32_t m18;
  uint32_t mSlot;  // +0x1c
  void Continuation(void* fn, void* arg);  // 0x68f9f0
  void FUN_006913c0(int v);
};

// @ 0x00754310  SP::RegisterModel (cdecl): registers the model's property list under (id, 0xe6bce5, instance)
bool SP_RegisterModel_00754310(void* self, uint32_t id, uint32_t instance) {
  Key key;
  key.a = id;
  key.b = 0xe6bce5;
  key.c = instance;
  Ref list;
  void* pm = PropertyManager();
  list.reset();
  if (!(char)vc3(pm, 0x2c, 0xf5895eae, 0x44a7f6af, (int)&list.p)) return false;
  if (!FUN_006acfe0_k(&key, self)) return false;
  Ref plr(new ("Graphics", 0, 0, 0, 0) cPropertyList());
  cPropertyList* pl = (cPropertyList*)plr.p;
  pl->SetParent(list.p);
  {
    Variant v;
    v.SetKey(&key);
    vc2(pl, 0x14, 0xf9efbb, (int)&v);
  }
  vc3(PropertyManager(), 0x34, (int)pl, id, instance);
  return true;
}

// @ 0x007544e0  (193 bytes): cdecl(src, id, instance); builds a model, adopts `src`, registers it
struct S_007544e0 {
  char pad_11c[0x11c];
  char m11c[0x18];  // +0x11c .. 0x134
  char m134[4];
  void* m138;  // +0x138 (counted)
  char pad_13c[4];
  S_007544e0();  // FUN_007004d0
};
void FUN_007544e0(void* src, uint32_t id, uint32_t instance) {
  S_007544e0* m = new ("Graphics", 0, 0, 0, 0) S_007544e0();
  void* old = m->m138;
  if (src != old) {
    if (src) vc0(src, 0);
    m->m138 = src;
    if (old) vc0(old, 4);
  }
  vc2(src, 0x14, (int)m->m11c, (int)m->m134);
  SP_RegisterModel_00754310(m, id, instance);
}

// @ 0x007545b0  (102 bytes) refcounted swap into this->m44+0x13c
struct S_007545b0 {
  char pad_0[0x44];
  void* m044;  // +0x44
  char pad_48[0x100 - 0x48];
  RefT_007545b0* m100;  // +0x100
  bool FUN_007545b0(int param_2);
};
bool S_007545b0::FUN_007545b0(int param_2) {
  int v = *(int*)(param_2 + 0x1c);
  if (v == 0) {
    if (m100 != 0) {
      FUN_006acfe0((char*)this + 0xf4, m100);
      int* slot = (int*)(*(int*)((char*)this + 0x44) + 0x13c);
      RefT_007545b0* piVar2 = m100;
      RefT_007545b0* piVar3 = (RefT_007545b0*)*slot;
      if (piVar2 != piVar3) {
        if (piVar2 != 0) piVar2->AddRef();
        *slot = (int)piVar2;
        if (piVar3 != 0) piVar3->Release();
      }
    }
  }
  return true;
}

// @ 0x00754620  (296 bytes) cdecl(id, instance): register a property list's keys, or the plain key if absent
bool FUN_00754620(uint32_t id, uint32_t instance) {
  Ref list;
  void* pm = PropertyManager();
  list.reset();
  if ((char)vc3(pm, 0x2c, id, instance, (int)&list.p)) {
    void* pm2 = PropertyManager();
    vc1(pm2, 0x38, (int)list.p);
    Key k;
    k.a = 0;
    k.b = 0;
    k.c = 0;
    for (int i = 0; i < 4; i++) {
      if (GetPropertyAsKey(list.p, 0xf9efbb + i, &k)) FUN_006ad030(&k);
    }
    return true;
  }
  Key key;
  key.a = id;
  key.b = 0xe6bce5;
  key.c = instance;
  return FUN_006ad030(&key);
}

// @ 0x00754770  (495 bytes) thiscall(out): load the job's model resource and hand it to FUN_007542b0
struct S_00754770 {
  uint32_t m00, m04, m08;
  uint32_t m0c;
  uint32_t m10;
  uint32_t m14;
  uint32_t m18;
  void* m1c;
  void* m20;
  bool FUN_00754770(void* out);
};
bool S_00754770::FUN_00754770(void* out) {
  void* prov = m1c;
  if (prov && !m20) {
    Ref* r = (Ref*)&m20;
    r->reset();
    vc1(prov, 0x14, (int)&m20);
  }
  if (!m20) return false;
  ResPtr res(new ("Graphics", 0, 0, 0, 0) Res());
  bool ok;
  if (m10 == 0xe6bce5) {
    res.p->Attach(m20);
    ok = FUN_007542b0(out, res.p);
  } else if (m10 == 0x2f4e681b) {
    void* obj = m20;
    if (!(m18 & 1) && GetRwModelAsGameMeshesNoCache(obj)) {
      void* x = FUN_00759280(obj);
      Key k;
      k.a = m0c;
      k.b = m10;
      k.c = m14;
      k.b = 0xe6bce5;
      FUN_006acfe0_k(&k, x);
      SetCachingType(2, obj);
      SetCachingType(4, x);
      res.p->Attach(x);
      ok = FUN_007542b0(out, res.p);
    } else {
      SetCachingType(4, obj);
      if (!res.p->Load(obj)) return false;
      ok = FUN_007542b0(out, res.p);
    }
  } else {
    return false;
  }
  return ok;
}

// @ 0x00754960  (561 bytes) cdecl(key, out, flags): resolve `key` and build the model resource into *out
bool FUN_00754960_impl(Key* key, Res** out, uint32_t flags) {
  Ref ref;
  void* mgr = GetManager();
  ref.reset();
  if (!(char)vc6(mgr, 0x0c, (int)key, (int)&ref.p, 0, 0, 0, 0)) return false;
  ResPtr res(new ("Graphics", 0, 0, 0, 0) Res());
  if (key->b == 0xe6bce5) {
    res.p->Attach(ref.p);
  } else if (key->b == 0x2f4e681b) {
    void* obj = ref.p;
    if (!(flags & 1) && GetRwModelAsGameMeshesNoCache(obj)) {
      void* x = FUN_00759280(obj);
      Key k = *key;
      k.b = 0xe6bce5;
      FUN_006acfe0_k(&k, x);
      SetCachingType(2, obj);
      SetCachingType(4, x);
      res.p->Attach(x);
    } else {
      SetCachingType(4, obj);
      if (!res.p->Load(obj)) return false;
    }
  } else {
    return false;
  }
  *out = res.p;
  res.p->rc++;
  return true;
}

// @ 0x00754ba0  SP::CreateModelInstance
bool CreateModelInstance_00754ba0(int a1, int a2, int a3, int a4) {
  struct K {
    int a;
    int b;
    int c;
  } k;
  k.a = a1;
  k.b = 0xe6bce5;
  k.c = a2;
  if (FUN_00754960(&k, (void*)a3, (void*)a4)) {
    return true;
  }
  k.b = 0x2f4e681b;
  return FUN_00754960(&k, (void*)a3, (void*)a4);
}

// @ 0x00754c20  (114 bytes) job continuation: step through the key list, then continue
struct S_00754c20 {
  char pad[0xc];
  uint32_t* mpBegin;  // +0xc
  uint32_t* mpEnd;  // +0x10
  char pad14[0x64 - 0x14];
  void* m64;  // +0x64
  void FUN_00754c20(cJob* job);
};
void S_00754c20::FUN_00754c20(cJob* job) {
  uint32_t slot = job->mSlot;
  uint32_t n = (uint32_t)(mpEnd - mpBegin);
  if (slot < n) {
    void* srv = (void*)((void* (__cdecl*)())FUN_0067dd60)();
    if (!(m64 && srv) || (char)vc3(srv, 0x44, (int)mpBegin[slot], (int)m64, 1)) {
      job->mSlot = slot + 1;
      job->Continuation((void*)0x753fa0, this);
    }
  } else {
    job->Continuation((void*)0x754300, this);
  }
}

// @ 0x00754ca0  SP::CompileToPropertyModel (725 bytes, EH): push the model's keys/values into its property list
struct Msg {
  void* vtbl;  // +0
  volatile long rc;  // +4
  uint32_t f08, f0c, f10, f14, f18, f1c;
  uint32_t pad20[4];
  uint32_t id;  // +0x30
  uint32_t pad34;
  uint32_t f38;  // +0x38
  void Destruct();  // 0x421cf0
};
extern char vtbl_BehaviorMessage[];  // 0x13eb90c
extern char vtbl_MessageBasicRC5[];  // 0x13eb844
extern float g_Zero;  // 0x1485378

struct S_00754ca0 {
  char pad0[0xc];
  uint32_t m0c;  // +0xc
  uint32_t pad10;
  uint32_t m14[4];  // +0x14: per-slot key instance
  float m24[4];  // +0x24: per-slot weights
  char pad34[0x44 - 0x34];
  char* m44;  // +0x44 model data
  char pad48[0x104 - 0x48];
  void* m104;  // +0x104 property list
  bool FUN_00754ca0(int unused);
};

struct Mask5 {
  uint32_t d[4];
  uint32_t z;
};

bool S_00754ca0::FUN_00754ca0(int) {
  for (int i = 0; i < 4; i++) {
    if (m24[i] != 0.0f) {
      Key k;
      k.a = m0c;
      k.b = 0xe6bce5;
      k.c = m14[i];
      Variant v;
      v.data[0] = k.a;
      v.data[1] = k.b;
      v.data[2] = k.c;
      v.mTypeId = 0x20;
      v.mFlags = 0;
      vc2(m104, 0x14, 0xf9efbb + i, (int)&v);
    }
  }
  char* model = m44;
  if (model) {
    void* p = m104;
    {
      Variant tmp;
      Variant* r = ((Variant * (__thiscall*)(Variant*, void*)) 0x754250)(&tmp, model + 0x11c);
      vc2(p, 0x14, 0xf9efba, (int)r);
    }
    {
      Variant f;
      *(float*)&f.data[0] = *(float*)(model + 0x134);
      f.mTypeId = 0xd;
      f.mFlags = 2;
      vc2(m104, 0x14, 0xf9efb9, (int)&f);
    }
  }
  Mask5 mask;
  mask.d[0] = mask.d[1] = mask.d[2] = mask.d[3] = 0;
  mask.z = 0;
  for (int i = 0; i < 4; i++) {
    uint32_t bits = 0;
    Variant* pv;
    if (m104 && (char)vc2(m104, 0x24, 0x452027c + i, (int)&pv) && pv->mTypeId == 0xa) {
      uint32_t* q = (uint32_t*)pv;
      if (pv->mFlags & 0x30) q = *(uint32_t**)pv;
      bits = *q;
    }
    if (bits & 2) mask.d[i] = 0xffffffff;
  }
  Variant out;
  out.Set(9, 0x98, &mask, 4, 5);
  vc2(m104, 0x14, 0x60cbbef, (int)&out);
  Msg msg;
  msg.id = 0xf62def;
  msg.vtbl = vtbl_BehaviorMessage;
  msg.rc = 0;
  msg.vtbl = vtbl_MessageBasicRC5;
  msg.f38 = 0;
  char* plc = (char*)m104;
  msg.f08 = *(uint32_t*)(plc + 0xc);
  msg.f18 = *(uint32_t*)(plc + 8);
  msg.f10 = *(uint32_t*)(plc + 0x10);
  vc3(MessageServer(), 0x14, 0xf62def, (int)&msg, 0);
  msg.Destruct();
  return true;
}

// @ 0x00755070  (445 bytes) constructor of the model-instance job object (0x10c bytes); returns this
struct E4a {
  uint32_t v;
  E4a();  // 0x743b50
  ~E4a();  // 0x7a9610
};
struct E4b {
  uint32_t v;
  E4b();  // 0x743b50
  ~E4b();  // 0x472520
};
struct Slot8 {
  float value;
  bool a, b, c;
};
extern char vtbl_job0[];  // 0x140d9c4
extern char vtbl_job4[];  // 0x140d9c0
extern float g_One;  // 0x1485720
struct JobObj {
  void* vt0;  // +0
  void* vt4;  // +4
  volatile long rc;  // +8
  uint32_t m0c, m10, m14, m18, m1c, m20;
  float m24, m28, m2c, m30;
  uint32_t m34, m38, m3c, m40;
  E4a arr44[4];  // +0x44
  Slot8 slots[6];  // +0x54..0x84
  uint32_t m84, m88, m8c;
  uint32_t pad90[2];
  uint32_t m98, m9c, ma0, ma4;
  uint32_t pada8[2];
  bool mb0;
  char padb1[3];
  E4b arrb4[4];  // +0xb4
  bool mc4, mc5;
  char padc6[2];
  uint32_t mc8, mcc, md0;
  uint32_t padd4[2];
  uint32_t mdc, me0, me4;
  uint32_t pade8[2];
  bool mf0;
  char padf1[3];
  uint32_t mf4, mf8, mfc, m100, m104, m108;
  JobObj* FUN_00755070();
};
JobObj* JobObj::FUN_00755070() {
  vt0 = vtbl_job0;
  vt4 = vtbl_job4;
  rc = 0;
  m0c = 0;
  m10 = 0;
  // arr44 constructed by the eh vector constructor iterator
  float one = g_One;
  for (int i = 0; i < 6; i++) {
    slots[i].value = one;
    slots[i].a = true;
    slots[i].b = false;
    slots[i].c = false;
  }
  m84 = 0;
  m88 = 0;
  m8c = 0;
  m98 = 0;
  m9c = 0;
  ma0 = 0;
  ma4 = 0;
  mb0 = false;
  mc4 = false;
  mc5 = false;
  mc8 = 0;
  mcc = 0;
  md0 = 0;
  mdc = 0;
  me0 = 0;
  me4 = 0;
  mf0 = false;
  mf4 = 0;
  mf8 = 0;
  mfc = 0;
  m100 = 0;
  m104 = 0;
  m108 = 0;
  m14 = 0;
  m34 = 0;
  m18 = 0;
  m38 = 0;
  m1c = 0;
  m3c = 0;
  m20 = 0;
  m40 = 0;
  m24 = 0.0f;
  m28 = 0.0f;
  m2c = 0.0f;
  m30 = 0.0f;
  return this;
}

// @ 0x00755240  cCreateModelInstanceJob::LoadAsArenaJob (160 bytes): thiscall(job)
struct S_00755240 {
  char pad[0xc];
  char key[0x4];  // +0xc (Key start)
  uint32_t m10;
  char pad14[8];
  void* m1c;  // +0x1c
  void* m20;  // +0x20
  void FUN_00755240(cJob* job);
};
void S_00755240::FUN_00755240(cJob* job) {
  m10 = 0x2f4e681b;
  void* mgr = GetManager();
  Ref* r20 = (Ref*)&m20;
  r20->reset();
  Ref* r1c = (Ref*)&m1c;
  r1c->reset();
  vc8(mgr, 0x10, (int)key, (int)&m1c, (int)&m20, 0, 0, 0, 0, 0);
  if (m1c) {
    void* node = (void*)vc1(m1c, 0x0c, 0x3a212ac);
    if (node) {
      int t = ((XNode*)node)->Type();
      job->FUN_006913c0(t);
    }
  }
  job->m18 = 1;
  job->Continuation((void*)0x754c10, this);
}

// @ 0x007552e0  (223 bytes) EASTL vector<GlyphInfo (8 bytes)>::operator=(const vector&)
struct GlyphInfo {
  uint32_t a, b;
};
GlyphInfo* __cdecl do_copy(GlyphInfo* first, GlyphInfo* last, GlyphInfo* dest);  // 0xac4440
void* __cdecl eastl_copy(void* sret, GlyphInfo* first, GlyphInfo* last, GlyphInfo* dest, const void* tag);  // 0x76ffd0
struct GlyphVec {
  GlyphInfo* mpBegin;
  GlyphInfo* mpEnd;
  GlyphInfo* mpCapacity;
  GlyphInfo* DoRealloc(unsigned n, GlyphInfo* first, GlyphInfo* last);  // 0x754f80
  GlyphVec& operator=(const GlyphVec& x);
};
GlyphVec& GlyphVec::operator=(const GlyphVec& x) {
  if (&x != this) {
    const unsigned nNewSize = (unsigned)(x.mpEnd - x.mpBegin);
    if (nNewSize > (unsigned)(mpCapacity - mpBegin)) {
      GlyphInfo* pNewData = DoRealloc(nNewSize, x.mpBegin, x.mpEnd);
      if (mpBegin && ((int*)mpBegin)[-1] != 0) delete[] mpBegin;
      mpBegin = pNewData;
      mpCapacity = pNewData + nNewSize;
      mpEnd = pNewData + nNewSize;
    } else if (nNewSize > (unsigned)(mpEnd - mpBegin)) {
      do_copy(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
      char sret[4];
      eastl_copy(sret, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
      mpEnd = mpBegin + nNewSize;
    } else {
      do_copy(x.mpBegin, x.mpEnd, mpBegin);
      mpEnd = mpBegin + nNewSize;
    }
  }
  return *this;
}
