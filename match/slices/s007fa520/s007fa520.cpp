// Spore decompilation — batch w2g6, slice s007fa520.
// cSPUIBehaviour serialization/adapter region, compiled /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
// Two functions in this slice are compiled /O2 (007fb0e0, 007fb220) and live in s007fa520_o2.cpp.
#include <cstddef>
#include <math.h>

// ---------------------------------------------------------------------------
// Small ref-counted / virtual stubs used across many of these helpers.
// ---------------------------------------------------------------------------
struct RCObj {
  virtual void AddRef();   // +0
  virtual void Release();  // +4
};

struct Pred {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5();
  virtual bool v6();               // +0x18
  virtual void v7();
  virtual int v8();                // +0x20
  virtual void v9();
  virtual unsigned char v10();     // +0x28
};

// f53c0: return *(int*)(b + 0x10) + this->off
struct C53 { char pad0[4]; unsigned off; int M(int b); };

// ---------------------------------------------------------------------------
// 007fa520 — combine a list of predicate results (see FUN_007fa520).
// ---------------------------------------------------------------------------
// @ 0x007fa520
bool f_7fa520(Pred*** arr, int n, int* counter) {
  if (*counter == 0) { return true; } else { *counter = 0; }
  bool result = true;
  int combine = -1;
  for (int i = 0; i < n; i++) {
    Pred** e = arr[i];
    if (*e) {
      (*counter)++;
      int mode = (*e)->v8();
      bool val = (*e)->v6();
      if ((*e)->v10()) val = (val == 0);
      if (combine == -1) {
        int m = mode; if (m == -1 || m == 1) m = 2; combine = m; result = val;
        continue;
      }
      if (mode != 1) combine = mode;
      switch (combine) {
        case 2: result = result && val; break;
        case 3: result = result || val; break;
      }
    }
  }
  return result;
}

// ---------------------------------------------------------------------------
// 007fa690 / 007fa6d0 — small 4-slot ref-counted array accessors.
// ---------------------------------------------------------------------------
#pragma pack(push,1)
struct C_7fa690 {
  char pad0[8];
  struct E { RCObj* p; void* q; } elems[4];   // +0x08, stride 8
  char pad1[0x18];                            // +0x28 .. +0x40
  char flags[4];                              // +0x40
  RCObj* GetAt(int i);
  bool SetAt(int i, RCObj* p);
};
#pragma pack(pop)

// @ 0x007fa690
RCObj* C_7fa690::GetAt(int i) {
  if (i >= 0 && i < 4 && flags[i]) return elems[i].p;
  return 0;
}

// @ 0x007fa6d0
bool C_7fa690::SetAt(int i, RCObj* p) {
  if (i >= 0 && i < 4) {
    if (flags[i] && elems[i].p) elems[i].p->Release();
    elems[i].p = p;
    if (p) p->AddRef();
    flags[i] = 1;
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------
// 007fa780 / 007fa840 / 007fa8e0 — SerMarshaller<>::Read helpers.
// ---------------------------------------------------------------------------
struct Creator {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual RCObj* Create(int tag);   // +0x0c
};
struct P2 { char pad0[4]; RCObj** c; };                     // +0x04
struct P3 { char pad0[0x10]; int off; unsigned count; };    // +0x14 = count
extern char g_tag_7fa780[];

// @ 0x007fa780
bool f_7fa780(C53* self, P2* p2, P3* p3) {
  RCObj** c = p2->c;
  RCObj** it = (RCObj**)self->M((int)p3);
  for (unsigned i = 0; i < p3->count; i++, it++, c++) {
    RCObj* created = 0;
    RCObj* old = *it;
    if (old) old->Release();
    Creator* src = (Creator*)*c;
    if (src) {
      created = src->Create((int)g_tag_7fa780);
      if (created) created->AddRef();
    }
    *it = created;
  }
  return true;
}

struct IAlloc { virtual void* alloc(int n, int align); };
struct Y { char pad0[0x14]; unsigned count; };
extern char g_serconst_7fa840[];

// @ 0x007fa840
bool f_7fa840(void** p, C53* a, Y* b, IAlloc* c) {
  int* src = (int*)a->M((int)b);
  int* dst = (int*)c->alloc((int)(b->count * 4), 4);
  if (dst) {
    p[1] = dst;
    p[2] = (void*)b->count;
    p[0] = (void*)g_serconst_7fa840;
    for (unsigned i = 0; i < b->count; i++, src++, dst++) {
      *dst = *src;
    }
    return true;
  }
  return false;
}

extern char g_serconst_7fa8e0[];

// @ 0x007fa8e0
bool f_7fa8e0(void** p, C53* a, Y* b) {
  p[0] = (void*)g_serconst_7fa8e0;
  p[1] = (void*)a->M((int)b);
  p[2] = (void*)b->count;
  return true;
}

// ---------------------------------------------------------------------------
// Generic 22-slot vtable for the tiny forwarding thunks.
// ---------------------------------------------------------------------------
struct VC22 {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
  virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
};

// @ 0x007fa950
void f_7fa950(VC22* p) { p->v21(); }
// @ 0x007fa9b0
void f_7fa9b0(VC22* p) { p->v15(); }
// @ 0x007faa10
void f_7faa10(VC22* p) { p->v18(); }
// @ 0x007fb0b0
void f_7fb0b0(VC22* p) { p->v09(); }

// ---------------------------------------------------------------------------
// 007faa30 / 007fb250 / 007fb2e0 / 007fb440 — SerItem bind helpers.
// ---------------------------------------------------------------------------
struct SerItem { void* type; void* base; unsigned count; void* extra; };
struct VSer {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void* vf();   // +0x14
};

extern char g_sc_7faa30[];
struct C_7faa30 : VSer { void f(SerItem* p); };
// @ 0x007faa30
void C_7faa30::f(SerItem* p) {
  p->type = (void*)g_sc_7faa30;
  p->base = this;
  p->count = 1;
  p->extra = vf();
}

extern char g_sc_7fb250[];
struct C_7fb250 : VSer { void f(SerItem* p); };
// @ 0x007fb250
void C_7fb250::f(SerItem* p) {
  p->type = (void*)g_sc_7fb250;
  p->base = this;
  p->count = 1;
  p->extra = vf();
}

extern char g_sc_7fb2e0[];
struct C_7fb2e0 : VSer { void f(SerItem* p); };
// @ 0x007fb2e0
void C_7fb2e0::f(SerItem* p) {
  p->type = (void*)g_sc_7fb2e0;
  p->base = this;
  p->count = 1;
  p->extra = vf();
}

extern char g_sc_7fb440[];
struct C_7fb440 : VSer { void f(SerItem* p); };
// @ 0x007fb440   (complete; not byte-exact: +4 base forces a different vcall schedule)
void C_7fb440::f(SerItem* p) {
  p->type = (void*)g_sc_7fb440;
  p->base = (char*)this - 4;
  p->count = 1;
  p->extra = vf();
}

// ---------------------------------------------------------------------------
// Destructors (real member bodies; the vtables are masked relocations).
// ---------------------------------------------------------------------------
extern char g_7faa70_a[], g_7faa70_b[], g_7faa70_c[];
struct C_7faa70 { char pad[4]; void Base(); void Dtor(); };
// @ 0x007faa70
void C_7faa70::Dtor() {
  *(void**)this = (void*)g_7faa70_a;
  *(void**)((char*)this + 4) = (void*)g_7faa70_b;
  *(void**)((char*)this + 4) = (void*)g_7faa70_c;
  Base();
}

extern char g_7fb000_a[], g_7fb000_b[], g_7fb000_c[];
struct C_7fb000 { char pad[4]; void Base(); void Dtor(); };
// @ 0x007fb000
void C_7fb000::Dtor() {
  *(void**)this = (void*)g_7fb000_a;
  *(void**)((char*)this + 4) = (void*)g_7fb000_b;
  *(void**)((char*)this + 4) = (void*)g_7fb000_c;
  Base();
}

extern char g_7fb290_a[], g_7fb290_b[], g_7fb290_c[];
struct C_7fb290 { char pad[4]; void Base(); void Dtor(); };
// @ 0x007fb290
void C_7fb290::Dtor() {
  *(void**)this = (void*)g_7fb290_a;
  *(void**)((char*)this + 4) = (void*)g_7fb290_b;
  *(void**)((char*)this + 4) = (void*)g_7fb290_c;
  Base();
}

extern char g_7fb320_a[], g_7fb320_b[], g_7fb320_c[], g_7fb320_d[];
struct SubC_7fb320 { void Dtor(); };
struct C_7fb320 { char pad[4]; void Mid(); void Base(); void Dtor(); };
// @ 0x007fb320
void C_7fb320::Dtor() {
  *(void**)this = (void*)g_7fb320_a;
  *(void**)((char*)this + 4) = (void*)g_7fb320_b;
  *(void**)((char*)this + 0xc) = (void*)g_7fb320_c;
  Mid();
  ((SubC_7fb320*)((char*)this + 0xc))->Dtor();
  *(void**)((char*)this + 4) = (void*)g_7fb320_d;
  Base();
}

struct IWindow { virtual void a0(); virtual void Release(); };
extern char g_7fb110_a[], g_7fb110_b[], g_7fb110_c[], g_7fb110_d[], g_7fb110_c2[];
struct Sub10_7fb110 { void Dtor(); };
struct Sub4_7fb110 { void Dtor(); };
struct C_7fb110 {
  char pad[4];
  void Base();
  void Dtor();
};
// @ 0x007fb110
void C_7fb110::Dtor() {
  *(void**)this = (void*)g_7fb110_a;
  *(void**)((char*)this + 4) = (void*)g_7fb110_b;
  *(void**)((char*)this + 8) = (void*)g_7fb110_c;
  *(void**)((char*)this + 0x10) = (void*)g_7fb110_d;
  void** pv = (void**)((char*)this + 0x14);
  if (*(IWindow**)pv) ((IWindow*)*(IWindow**)pv)->Release();
  ((Sub10_7fb110*)((char*)this + 0x10))->Dtor();
  *(void**)((char*)this + 8) = (void*)g_7fb110_c2;
  ((Sub4_7fb110*)((char*)this + 4))->Dtor();
  Base();
}

// ---------------------------------------------------------------------------
// cSPUIBehaviorTimeFunction-like object.
// ---------------------------------------------------------------------------
struct VT_TF {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual float v6();                     // +0x18
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
  virtual void v19(); virtual void v20(); virtual void v21();
  virtual float v22(float f);             // +0x58
  virtual void v23();
  virtual void v24();                     // +0x60
};

struct C_TF : VT_TF {
  char pad0[8];
  float duration;      // +0x0c
  char pad1[8];        // +0x10 .. +0x18
  float easein;        // +0x18
  float easeout;       // +0x1c
  char pad2[0x19];     // +0x20 .. +0x39
  bool negated;        // +0x39
  bool dirty;          // +0x3a
  char pad3[1];
  float mtime;         // +0x3c
  float workfrom;      // +0x40
  void Update();
  float Evaluate(float f);
  float f20();
  float f40();
  float f60();
  bool IsValid();
  bool IsValid2();
  void* GetMember(int i);
  float Ease(float f);
  void SetNegated(unsigned char b);
};

// @ 0x007faad0
float C_TF::Evaluate(float f) {
  if (dirty) Update();
  float r = v22(f);
  if (negated) return 1.0f - r;
  return r;
}
// @ 0x007fab20
float C_TF::f20() { return Evaluate(mtime); }
// @ 0x007fab40
float C_TF::f40() { return Evaluate(duration); }
// @ 0x007fab60
float C_TF::f60() { return Evaluate(0.0f); }

// @ 0x007facf0
bool C_TF::IsValid() {
  if (dirty) Update();
  return 1e9f > duration;
}
// @ 0x007fad40
bool C_TF::IsValid2() {
  if (dirty) Update();
  return mtime > duration;
}
// @ 0x007fad90
void* C_TF::GetMember(int i) {
  if (dirty) Update();
  void* p = 0;
  switch (i) {
    case 0: p = (char*)this + 0xc; break;
    case 1: p = (char*)this + 0x10; break;
    case 2: p = (char*)this + 0x18; break;
    case 3: p = (char*)this + 0x1c; break;
    case 4: p = (char*)this + 0x14; break;
    case 5: p = (char*)this + 0x20; break;
    case 6: p = (char*)this + 0x24; break;
    case 10: p = (char*)this + 0x28; break;
    case 11: p = (char*)this + 0x2c; break;
    case 12: p = (char*)this + 0x30; break;
    case 13: p = (char*)this + 0x34; break;
  }
  return p;
}
// @ 0x007fae90
float C_TF::Ease(float f) {
  if (dirty) Update();
  if (f != 0.0f && f != 1.0f && (easein + easeout) != 0.0f) {
    float k = 1.0f / ((2.0f - easein) - easeout);
    if (easein > f) f = ((k / easein) * f) * f;
    else {
      if (1.0f - easeout > f) f = (2.0f * f - easein) * k;
      else f = 1.0f - ((k / easeout) * (1.0f - f)) * (1.0f - f);
    }
  }
  return f;
}
// @ 0x007fab80   (complete; not byte-exact)
void C_TF::SetNegated(unsigned char b) {
  if (dirty) v24();
  if (b == negated) return;
  int n = 0x14d;
  float step = duration / (float)(n - 0x21);
  float t = workfrom;
  float eps = 0.001f;
  float target = v6();
  negated = b;
  float cur = Evaluate(t);
  unsigned char rising = cur > target;
  while (fabsf(target - cur) >= eps && --n != 0) {
    t += step;
    cur = Evaluate(t);
    if (rising != (cur > target)) {
      rising = !rising;
      step *= -0.47f;
    }
  }
  mtime = t;
}

// ---------------------------------------------------------------------------
// 007fb040 / 007fb1a0 — SerItem bind helpers.
// ---------------------------------------------------------------------------
extern char g_serconst_7fb040[];
// @ 0x007fb040
void f_7fb040(void** p, void* a) {
  p[0] = (void*)g_serconst_7fb040;
  p[1] = a;
  p[2] = (void*)1;
}
extern char g_serconst_7fb1a0[];
// @ 0x007fb1a0
void f_7fb1a0(void** p, void* a) {
  p[0] = (void*)g_serconst_7fb1a0;
  p[1] = a;
  p[2] = (void*)1;
}

// ---------------------------------------------------------------------------
// 007fb3b0 — set "enabled".
// ---------------------------------------------------------------------------
struct VT16 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual unsigned char v6();   // +0x18
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14();
  virtual bool v15(int a, int b);                  // +0x3c
};
struct C_7fb3b0 : VT16 { bool f(unsigned char b); };
// @ 0x007fb3b0
bool C_7fb3b0::f(unsigned char b) {
  unsigned char a = v6();
  bool r = f_7fa520((Pred***)((char*)this + 0x14), 4, (int*)((char*)this + 0x34));
  if (r) v15(1, b); else if (b == 0) v15(1, 0);
  return b == v6();
}

// ---------------------------------------------------------------------------
// 007fb6a0 — vector-of-8 teardown.
// ---------------------------------------------------------------------------
struct Alloc_7fb6a0 { void Free(void* p, unsigned n); };
#pragma pack(push,1)
struct C_7fb6a0 {
  char* begin;
  char* end;
  char* cap;
  Alloc_7fb6a0 alloc;
  void Clear();
};
#pragma pack(pop)
template<int N> inline void ScratchSlots(){ unsigned int s[N]; }
// @ 0x007fb6a0
void C_7fb6a0::Clear() {
  ScratchSlots<1>();
  char* p = begin;
  for (; p < end; p += 8) {}
  if (begin)
    alloc.Free(begin, (unsigned)(((int)(cap - begin) >> 3) << 3));
}

// ---------------------------------------------------------------------------
// 007fb480 — event sub-object "set active". This is a multiple-inheritance
// subobject method (this = real object + 0x18); written with the real field
// offsets. Complete behaviour, not byte-exact.
// ---------------------------------------------------------------------------
struct EvtAction {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
  virtual void a4(); virtual void a5(); virtual unsigned char a6();   // +0x18
  virtual void a7(unsigned char);                                     // +0x1c
};
// base of the enclosing object (event object); this method is a sub-object at +0x18
void* f_7f93d0(void* base, int i);
void* f_7fa750(void* p);
void* f_65c480(int n);

// @ 0x007fb480   (complete; not byte-exact — multiple-inheritance sub-object method)
bool f_7fb480(char* self, unsigned char b) {
  char* base = self - 0x18;
  char prev = self[0x44];
  bool active;
  if (b != 0 && f_7fa520((Pred***)(self + 4), 4, (int*)(self + 0x48))) active = true;
  else active = false;
  self[0x44] = active ? 1 : 0;
  for (int i = 0; i < 4; i++) {
    EvtAction* a = *(EvtAction**)f_7f93d0(base, i);
    if (a && a->a6() == 0 && self[0x44] != 0)
      a->a7(self[0x44]);
  }
  if (self[0x44] == 0 && *(void**)(self + 0x60) != 0) {
    void* p = *(void**)(self + 0x60);
    *(void**)(self + 0x60) = 0;
    if (p) ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
  }
  if (*(void**)(self - 4) != 0 && prev != self[0x44]) {
    void* srcp = *(void**)(self - 4);
    void** vt = *(void***)srcp;
    void* a0 = f_7fa750((void*)(self - 0x18));
    ((void (__thiscall*)(void*, void*))vt[0x104 / 4])(srcp, a0);
    void* child = ((void* (__thiscall*)(void*))vt[0x14 / 4])(srcp);
    if (child != 0) {
      void* d = f_65c480(0xc);
      void** cvt = *(void***)child;
      ((void (__thiscall*)(void*, int, void*, void*, int))cvt[0x10 / 4])(child, 0, *(void**)(self - 4), d, 0);
    }
  }
  return true;
}
