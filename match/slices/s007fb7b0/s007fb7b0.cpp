// Spore decompilation — batch w2g6, slice s007fb7b0.
// cSPUIBehaviour adapter/event region, /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include <cstddef>

template<int N> inline void ScratchSlots(){ unsigned int s[N]; }
struct RCObj { virtual void AddRef(); virtual void Release(); };

// ---- externs used by the complete (non-byte-exact) functions ----
void* f_7f93e0();
void  f_7fa370(void* p);
void  eastl_deallocate(void* p);
extern unsigned char g_164b1f0;
extern void* g_164b410;
extern int   g_164b1f4;
void* f_883860();
void  f_883870(void* p);
void* f_e5cac0(const char* name);
void  f_10829f0(void* p);
void* f_8ac360(int n, void* p);
void* f_6abeb0();
void* f_884a20(void* p);
void* f_9512c0();
void* f_9512d0(int a, int b, const char* c, void* d);
void* f_7fb700(void* p);
void  f_7fa350_init(void* p);
void* f_11b7240(void* p);
void* f_7fa4f0(void* a, void* b, void* c);
int   f_571e00(void* p);
void* f_7fa4c0(void* a, int b);
void  wstring_assign(void* s, void* a, void* b);
void  wstring_freebuffer(void* p);
void* string_ctor_copy(void* s, void* other);
void** GetActSlot(void* self, int i);
void  f_7fc330(void* p);
void  f_7fb7b0(void* p);
void  f_7fc2a0_ctor(void* p);
void  f_7fbce0_dtor(void* p);
void  f_7fba80_init(void* p);

// ===========================================================================
// Byte-exact functions.
// ===========================================================================

// @ 0x007fb880
extern char tf_a[], tf_b[], tf_c[], tf_d[];
struct C_7fb880 { char pad[4]; void BaseCtor(); void* Ctor(); };
void* C_7fb880::Ctor() {
  BaseCtor();
  *(void**)this = (void*)tf_a;
  void** rc = (void**)((char*)this + 4);
  rc[0] = (void*)tf_b;
  rc[1] = 0;
  *(void**)this = (void*)tf_c;
  *(void**)((char*)this + 4) = (void*)tf_d;
  *(float*)((char*)this + 0xc) = 1.0f;
  *(float*)((char*)this + 0x10) = 1.0f;
  *(float*)((char*)this + 0x14) = 0.0f;
  *(float*)((char*)this + 0x18) = 0.0f;
  *(float*)((char*)this + 0x1c) = 0.0f;
  *(float*)((char*)this + 0x20) = 0.0f;
  *(float*)((char*)this + 0x24) = 0.0f;
  *(float*)((char*)this + 0x28) = 0.0f;
  *(float*)((char*)this + 0x2c) = 0.0f;
  *(float*)((char*)this + 0x30) = 0.0f;
  *(float*)((char*)this + 0x34) = 0.0f;
  *(char*)((char*)this + 0x38) = 0;
  *(char*)((char*)this + 0x39) = 0;
  *(char*)((char*)this + 0x3a) = 1;
  *(float*)((char*)this + 0x3c) = 0.0f;
  *(float*)((char*)this + 0x40) = 0.0f;
  *(float*)((char*)this + 0x44) = 0.0f;
  return this;
}

// @ 0x007fba00
extern char vi_a[], vi_b[], vi_c[], vi_d[];
struct C_7fba00 { char pad[4]; void BaseCtor(); void* Ctor(); };
void* C_7fba00::Ctor() {
  BaseCtor();
  *(void**)this = (void*)vi_a;
  void** p = (void**)((char*)this + 4);
  p[0] = (void*)vi_b;
  p[1] = 0;
  *(void**)this = (void*)vi_c;
  *(void**)((char*)this + 4) = (void*)vi_d;
  return this;
}

// @ 0x007fbb20
extern char v2_a[], v2_b[], v2_c[], v2_d[];
struct C_7fbb20 { char pad[4]; void BaseCtor(); void* Ctor(); };
void* C_7fbb20::Ctor() {
  BaseCtor();
  *(void**)this = (void*)v2_a;
  void** p = (void**)((char*)this + 4);
  p[0] = (void*)v2_b;
  p[1] = 0;
  *(void**)this = (void*)v2_c;
  *(void**)((char*)this + 4) = (void*)v2_d;
  *(void**)((char*)this + 0xc) = (void*)1;
  *(char*)((char*)this + 0x10) = 0;
  *(void**)((char*)this + 0x14) = 0;
  return this;
}

// @ 0x007fba80
extern char ba_a[], ba_b[], ba_c[], ba_d[], ba_e[], ba_f[], ba_g[], ba_h[];
struct Base4 { void Ctor(); };
struct C_7fba80 { char pad[4]; void BaseCtor0(); void* Ctor(); };
void* C_7fba80::Ctor() {
  BaseCtor0();
  *(void**)this = (void*)ba_a;
  ((Base4*)((char*)this + 4))->Ctor();
  void** a = (void**)((char*)this + 8);
  a[0] = (void*)ba_b;
  a[1] = 0;
  void** b = (void**)((char*)this + 0x10);
  b[0] = (void*)ba_c;
  b[0] = (void*)ba_d;
  *(void**)this = (void*)ba_e;
  *(void**)((char*)this + 4) = (void*)ba_f;
  *(void**)((char*)this + 8) = (void*)ba_g;
  *(void**)((char*)this + 0x10) = (void*)ba_h;
  void** c = (void**)((char*)this + 0x14);
  c[0] = 0;
  return this;
}

#pragma pack(push,1)
struct C_7fbce0 {
  char pad0[8];
  struct E { RCObj* p; void* q; } elems[4];
  char pad1[0x18];
  char flags[4];
  void BaseDtor();
  void Dtor();
};
#pragma pack(pop)
extern char bce0_vt[];
// @ 0x007fbce0
void C_7fbce0::Dtor() {
  *(void**)this = (void*)bce0_vt;
  ScratchSlots<1>();
  for (int i = 0; i < 4; i++) {
    if (flags[i] && elems[i].p) elems[i].p->Release();
  }
  BaseDtor();
}

// @ 0x007fbe70
struct C_7fbe70 { int GetClassId(); };
int C_7fbe70::GetClassId() { return 0x24b899e; }

// @ 0x007fc860
struct C_7fc860 { void g(int a, int b); void f(int a, int b); };
void C_7fc860::f(int a, int b) { g(a, b); }

// ===========================================================================
// Complete behaviour, not byte-exact.
// ===========================================================================

// @ 0x007fbbc0
extern char pb_a[], pb_b[], pb_c[], pb_d[], pb_e[], pb_f[], pb_g[];
struct C_7fbbc0 { char pad[4]; void BaseCtor(); void** GetSlot(int i); void* Ctor(); };
void* C_7fbbc0::Ctor() {
  BaseCtor();
  *(void**)this = (void*)pb_a;
  void** x = (void**)((char*)this + 4);
  x[0] = (void*)pb_b;
  x[1] = 0;
  void** y = (void**)((char*)this + 0xc);
  y[0] = (void*)pb_c;
  y[0] = (void*)pb_d;
  *(void**)this = (void*)pb_e;
  *(void**)((char*)this + 4) = (void*)pb_f;
  *(void**)((char*)this + 0xc) = (void*)pb_g;
  *(void**)((char*)this + 0x10) = 0;
  *(void**)((char*)this + 0x34) = (void*)0xffffffff;
  *(void**)((char*)this + 0x38) = 0;
  *(void**)((char*)this + 0x14) = (void*)((char*)this + 0x24);
  *(void**)((char*)this + 0x18) = (void*)((char*)this + 0x28);
  *(void**)((char*)this + 0x1c) = (void*)((char*)this + 0x2c);
  *(void**)((char*)this + 0x20) = (void*)((char*)this + 0x30);
  for (int m = 0; m < 4; m++) *(void**)GetSlot(m) = 0;
  return this;
}

// @ 0x007fbed0
extern char bed0_vt[];
struct SerItem { void* type; void* base; unsigned count; void* extra; };
struct VSer {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void* vf();
};
struct C_7fbed0 : VSer { void f(SerItem* p); };
void C_7fbed0::f(SerItem* p) {
  p->type = (void*)bed0_vt;
  p->base = (char*)this - 4;
  p->count = 1;
  p->extra = vf();
}

// @ 0x007fb7b0
void f_7fb7b0(void* param) {
  void* q = f_7f93e0();
  if (q) {
    f_7fa370(q);
    eastl_deallocate(q);
  }
  if (g_164b1f0) {
    void** pv = *(void***)param;
    void* r = ((void* (__thiscall*)(void*, int))pv[1])(param, 0);
    void** vt = *(void***)r;
    ((void (__thiscall*)(void*, void*))vt[0x108 / 4])(r, g_164b410);
    void* srv = f_883860();
    f_883870(0);
    void** svt = *(void***)srv;
    ((void (__thiscall*)(void*))svt[2])(srv);
    if (srv) ((void (__thiscall*)(void*, int))svt[0])(srv, 1);
  }
}

// @ 0x007fbd50
void* f_7fbd50(void* self) {
  void* t = f_e5cac0("UI/vector");
  *(void**)((char*)self + 0) = 0;
  *(void**)((char*)self + 4) = 0;
  *(void**)((char*)self + 8) = 0;
  f_e5cac0((const char*)t);
  f_10829f0((char*)self + 0xc);
  return self;
}

// @ 0x007fbdb0
void* f_7fbdb0(void** begin, void** end, void* out) {
  void** it = begin;
  char* p = (char*)out;
  for (; it != end; it += 2, p += 8) {
    void* m = f_8ac360(8, it);
    if (m) {
      *(void**)m = it[0];
      *((void**)m + 1) = it[1];
    }
  }
  void** q = begin;
  for (; q != end; q += 2) {}
  return p;
}

// @ 0x007fbf40
struct Sub18 { void Ctor(); void RemoveAllPredicates(); void RemoveAllActions(); void BaseDtor(); };
struct Sub68 { void FreeBuffer(); };
struct WinProcInit { void Dtor(); };
struct Tag { char c; Tag(const char* n); };
void eastl_string_ctor(void* s, Tag tag);
extern char eb_a[], eb_b[], eb_c[], eb_d[], eb_e[], eb_f[], eb_g[];
struct C_7fbf40 { char pad[4]; void BaseCtor(); void** PredSlot(int i); void** ActSlot(int i); void* Ctor(); };
void* C_7fbf40::Ctor() {
  BaseCtor();
  Sub18* p = (Sub18*)((char*)this + 0x18);
  p->Ctor();
  *(void**)p = (void*)eb_a;
  *(void**)p = (void*)eb_b;
  *(void**)this = (void*)eb_c;
  *(void**)((char*)this + 4) = (void*)eb_d;
  *(void**)((char*)this + 8) = (void*)eb_e;
  *(void**)((char*)this + 0x10) = (void*)eb_f;
  *(void**)((char*)this + 0x18) = (void*)eb_g;
  *(char*)((char*)this + 0x5c) = 0;
  *(void**)((char*)this + 0x60) = (void*)0xffffffff;
  *(void**)((char*)this + 0x64) = 0;
  eastl_string_ctor((char*)this + 0x68, Tag("UI/basic_string"));
  *(void**)((char*)this + 0x78) = 0;
  *(void**)((char*)this + 0x1c) = (void*)((char*)this + 0x2c);
  *(void**)((char*)this + 0x20) = (void*)((char*)this + 0x30);
  *(void**)((char*)this + 0x24) = (void*)((char*)this + 0x34);
  *(void**)((char*)this + 0x28) = (void*)((char*)this + 0x38);
  for (int i = 0; i < 4; i++) *(void**)PredSlot(i) = 0;
  *(void**)((char*)this + 0x3c) = (void*)((char*)this + 0x4c);
  *(void**)((char*)this + 0x40) = (void*)((char*)this + 0x50);
  *(void**)((char*)this + 0x44) = (void*)((char*)this + 0x54);
  *(void**)((char*)this + 0x48) = (void*)((char*)this + 0x58);
  for (int j = 0; j < 4; j++) *(void**)ActSlot(j) = 0;
  return this;
}

// @ 0x007fc200
extern char ed_a[], ed_b[], ed_c[], ed_d[], ed_e[];
struct C_7fc200 { char pad[4]; void Dtor(); };
void C_7fc200::Dtor() {
  *(void**)this = (void*)ed_a;
  *(void**)((char*)this + 4) = (void*)ed_b;
  *(void**)((char*)this + 8) = (void*)ed_c;
  *(void**)((char*)this + 0x10) = (void*)ed_d;
  *(void**)((char*)this + 0x18) = (void*)ed_e;
  ((Sub18*)((char*)this + 0x18))->RemoveAllPredicates();
  ((Sub18*)((char*)this + 0x18))->RemoveAllActions();
  RCObj** pv = (RCObj**)((char*)this + 0x78);
  if (*pv) (*pv)->Release();
  ((Sub68*)((char*)this + 0x68))->FreeBuffer();
  ((Sub18*)((char*)this + 0x18))->BaseDtor();
  ((WinProcInit*)this)->Dtor();
}

// @ 0x007fc2a0
extern char bm_a[], bm_b[], bm_c[];
struct C_7fc2a0 { char pad[4]; void BaseCtor(); void* Ctor(); };
void* C_7fc2a0::Ctor() {
  void* p = (char*)this + 8;
  *(void**)((char*)p + 0x28) = 0;
  BaseCtor();
  *(void**)this = (void*)bm_a;
  *(void**)this = (void*)bm_b;
  *(void**)((char*)this + 0x38) = 0;
  *(void**)this = (void*)bm_c;
  *(void**)((char*)this + 0x40) = 0;
  return this;
}

// @ 0x007fc330
void f_7fc330(void* param_1) {
  if (f_883860() == 0) {
    void* s = f_6abeb0();
    void* srv = 0;
    if (s) srv = f_884a20(s);
    void** vt = *(void***)srv;
    ((void (__thiscall*)(void*))vt[1])(srv);
    ((void (__thiscall*)(void*, int, int))vt[4])(srv, 4, 0);
    f_883870(srv);
    g_164b1f0 = 1;
    RCObj* r = (RCObj*)((void* (__thiscall*)(void*, int))(*(void***)param_1)[1])(param_1, 0);
    void* tag = f_9512c0();
    void* pp = f_9512d0(0x18, 4, "PluginProc", tag);
    void* obj = 0;
    if (pp) {
      f_7fba80_init(pp);
      obj = pp;
    }
    void* old = g_164b410;
    if (obj != old) {
      if (obj) ((void (__thiscall*)(void*))**(void***)obj)(obj);
      g_164b410 = obj;
      if (old) ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
    }
    void* v = (void*)f_7fb700(&g_164b410);
    ((void (__thiscall*)(void*, void*))(*(void***)r)[0x104 / 4])(r, v);
  }
  f_7fa350_init(0);
}

// @ 0x007fc4b0
unsigned f_7fc4b0(void* self, int* msg, void* arg) {
  if (msg == (int*)0x11) {
    void* p = f_11b7240(arg);
    RCObj** slot = (RCObj**)((char*)self + 4);
    if (p != *slot) {
      RCObj* old = *slot;
      if (p) ((void (__thiscall*)(void*))**(void***)p)(p);
      *slot = (RCObj*)p;
      if (old) old->Release();
    }
    int n = g_164b1f4;
    g_164b1f4 = n + 1;
    if (n == 0) {
      void* o = *(void**)((char*)self + 4);
      void* r = (void*)((void* (__thiscall*)(void*, int))(*(void***)o)[5])(o, 0);
      f_7fc330(r);
    }
  } else if (msg == (int*)0x12) {
    int n = g_164b1f4 - 1;
    g_164b1f4 = n;
    if (n == 0 && *(void**)((char*)self + 4) != 0) {
      void* o = *(void**)((char*)self + 4);
      void* r = (void*)((void* (__thiscall*)(void*, int))(*(void***)o)[5])(o, 0);
      f_7fb7b0(r);
    }
    RCObj** slot = (RCObj**)((char*)self + 4);
    if (*slot) {
      RCObj* old = *slot;
      *slot = 0;
      if (old) old->Release();
    }
  }
  return 0;
}

// @ 0x007fc600
unsigned f_7fc600(void* self, int a, int b) {
  char buf[0x50];
  f_7fc2a0_ctor(buf);
  void* r = f_7fa4f0(buf, (void*)a, (void*)b);
  void** vt = *(void***)((char*)self + 0x10);
  ((void (__thiscall*)(void*, void*, void*))vt[1])((char*)self + 0x10, 0, r);
  f_7fbce0_dtor(buf);
  return 0;
}

// @ 0x007fc690
int f_7fc690(void* self, void* param) {
  char s[0x10];
  string_ctor_copy(s, (char*)self + 0x50);
  void* end = (char*)param + f_571e00(param) * 2;
  wstring_assign((char*)self + 0x50, param, end);
  char msg[0x48];
  f_7fc2a0_ctor(msg);
  void* u = (void*)f_7fa4c0(msg, 0x24f6efb);
  for (int i = 0; i < 4; i++) {
    void** slot = (void**)GetActSlot((char*)self - 0x18, i);
    if (*slot) {
      void* obj = (void*)((void* (__thiscall*)(void*))(*(void***)(*slot))[0x2c / 4])(*slot);
      ((void (__thiscall*)(void*, void*, void*))(*(void***)obj)[1])(obj, u, 0);
    }
  }
  f_7fbce0_dtor(msg);
  wstring_freebuffer(s);
  return 1;
}

// @ 0x007fc790
int f_7fc790(void* self, void* param) {
  void* old = *(void**)((char*)self + 0x4c);
  *(void**)((char*)self + 0x4c) = param;
  (void)old;
  char msg[0x48];
  f_7fc2a0_ctor(msg);
  void* u = (void*)f_7fa4c0(msg, 0x24f6efa);
  for (int i = 0; i < 4; i++) {
    void** slot = (void**)GetActSlot((char*)self - 0x18, i);
    if (*slot) {
      void* obj = (void*)((void* (__thiscall*)(void*))(*(void***)(*slot))[0x2c / 4])(*slot);
      ((void (__thiscall*)(void*, void*, void*))(*(void***)obj)[1])(obj, u, 0);
    }
  }
  f_7fbce0_dtor(msg);
  return 1;
}
