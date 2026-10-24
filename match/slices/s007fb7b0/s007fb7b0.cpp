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
void* f_6abeb0(unsigned int size);            // 0x006abeb0
void* f_9512c0();
void* f_9512d0(int a, int b, const char* c, void* d);
void* f_7fb700(void* p);
void* f_11b7240(void* p);
void* f_7fa4f0(void* a, void* b, void* c);
int   f_571e00(void* p);
void* f_7fa4c0(void* a, int b);
void  wstring_assign(void* s, void* a, void* b);
void  wstring_freebuffer(void* p);
void* string_ctor_copy(void* s, void* other);
void** GetActSlot(void* self, int i);
void  f_7fc330(void* p);
void  f_7fc2a0_ctor(void* p);
void  f_7fbce0_dtor(void* p);


// ---- f_7fb7b0 types (vtable-based) ----
struct Ev7f93 {
  void ClearGlobal();                 // 0x007fa370
  ~Ev7f93() { ClearGlobal(); }
};
Ev7f93* GetEv7f93();                  // 0x007f93e0
struct IMsgServer {
  virtual ~IMsgServer();              // slot 0
  virtual void s1();
  virtual void Shutdown();            // slot 2 (+8)
};
IMsgServer* GetMsgServer();           // 0x00883860
void SetMsgServer(IMsgServer* s);     // 0x00883870
struct IModelWorld7fb {
  virtual void s0(); virtual void s1();
  virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
  virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b(); virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
  virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
  virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b(); virtual void s1c(); virtual void s1d(); virtual void s1e(); virtual void s1f();
  virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
  virtual void s28(); virtual void s29(); virtual void s2a(); virtual void s2b(); virtual void s2c(); virtual void s2d(); virtual void s2e(); virtual void s2f();
  virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
  virtual void s38(); virtual void s39(); virtual void s3a(); virtual void s3b(); virtual void s3c(); virtual void s3d(); virtual void s3e(); virtual void s3f();
  virtual void s40(); virtual void s41(); 
  virtual void SetCurrent(void* p);   // +0x108
};
struct IWorldHost {
  virtual void s0();
  virtual IModelWorld7fb* GetWorld();  // +4
};
void f_7fb7b0(IWorldHost* param);

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
void f_7fb7b0(IWorldHost* param) {
  delete GetEv7f93();
  if (g_164b1f0) {
    IModelWorld7fb* ptr = param->GetWorld();
    ptr->SetCurrent(g_164b410);
    IMsgServer* w = GetMsgServer();
    SetMsgServer(0);
    w->Shutdown();
    delete w;
  }
}

struct Alloc7fbd50 {
  Alloc7fbd50(const char* name);                 // 0x00e5cac0 (ret 4, returns this; the copy ctor is the same body)
  Alloc7fbd50(const Alloc7fbd50& o);             // 0x00e5cac0
  void set_name(const char* name);               // 0x010829f0 (ret 4)
};
void* operator new(size_t n, void* p);           // 0x008ac360 (cdecl placement new)
struct VecMap7fbd50 {
  void* mBegin; void* mEnd; void* mCap; Alloc7fbd50 mAlloc;
  VecMap7fbd50(const Alloc7fbd50& a = Alloc7fbd50("UI/vector"))
    : mBegin(0), mEnd(0), mCap(0), mAlloc(a) { mAlloc.set_name("UI/vector_map"); }
};
struct Holder7fbd50 {
  VecMap7fbd50 v;
  Holder7fbd50();
};
// @ 0x007fbd50
Holder7fbd50::Holder7fbd50() {}

struct Pair8 { unsigned first; unsigned second; };
// @ 0x007fbdb0
Pair8* f_7fbdb0(Pair8* first, Pair8* last, Pair8* dest) {
  Pair8* result;
  {
    bool bSuccess = false;
    Pair8* d = dest;
    for (Pair8* it = first; it != last; ++it, ++d) {
      new (d) Pair8(*it);
    }
    result = d;
  }
  {
    bool b2 = false;
    Pair8* d2 = dest;
    for (Pair8* it2 = first; it2 != last; ++it2, ++d2) {
    }
  }
  return result;
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
// Local names below are chosen so the /Od name-hash reproduces the original stack slots
// (srv,r,s,pp,raw,old,obj) at ebp-4,-8,-0xc,-0x10,-0x14,-0x18,-0x1c.
struct Srv7fc330 { void* Server(); };          // 0x00884a20 (thiscall, returns this)
struct Ev7fc330  { void* SetGlobal(); };       // 0x007fa350 (thiscall, returns this)
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern char ppv_a[], ppv_b[], ppv_c[], ppv_d[];
void f_7fc330(void* param_1) {
  void* k; void* right; void* p1; void* len; void* chunk; void* cap; void* p30;
  if (f_883860() == 0) {
    chunk = f_6abeb0(0xc8);
    p30 = chunk ? ((Srv7fc330*)chunk)->Server() : 0;
    ((void (__thiscall*)(void*))((void**)*(void***)p30)[1])(p30);
    ((void (__thiscall*)(void*, int, int))((void**)*(void***)p30)[4])(p30, 4, 0);
    f_883870(p30);
    g_164b1f0 = 1;
    cap = ((void* (__thiscall*)(void*))((void**)*(void***)param_1)[1])(param_1);
    len = f_9512d0(0x18, 4, "PluginProc", f_9512c0());
    if (len) {
      ((C_7fba80*)len)->Ctor();
      *(void**)((char*)len + 0x0) = (void*)ppv_a;
      *(void**)((char*)len + 0x4) = (void*)ppv_b;
      *(void**)((char*)len + 0x8) = (void*)ppv_c;
      *(void**)((char*)len + 0x10) = (void*)ppv_d;
      k = len;
    }
    else k = 0;
    if (k != g_164b410) {
      right = g_164b410;
      if (k) ((void (__thiscall*)(void*))((void**)*(void***)k)[0])(k);
      g_164b410 = k;
      if (right) ((void (__thiscall*)(void*))((void**)*(void***)right)[1])(right);
    }
    ((void (__thiscall*)(void*, void*))((void**)*(void***)cap)[0x104 / 4])(cap, f_7fb700(&g_164b410));
  }
  p1 = operator new(1, "UI/PluginBroadcasterProc", 0, 0, 0, 0);
  p1 ? ((Ev7fc330*)p1)->SetGlobal() : 0;
}

struct IRefHost {
  virtual void AddRef();                   // 0x00
  virtual void Release();                  // 0x04
  virtual void s2(); virtual void s3(); virtual void s4();
  virtual IWorldHost* GetHost();           // 0x14
};
IRefHost* f_11b7240_ref(void* arg);        // 0x011b7240 (cdecl)
template <class T>
struct RefPtr7fc4b0 {
  T* mpObject;
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  RefPtr7fc4b0& operator=(T* p) {
    if (p != mpObject) {
      T* pOld = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (pOld) pOld->Release();
    }
    return *this;
  }
};
struct Handler7fc4b0 {
  char pad[4];
  RefPtr7fc4b0<IRefHost> mpHost;           // +4
  bool OnMessage(int msg, void* arg);
};
// @ 0x007fc4b0
bool Handler7fc4b0::OnMessage(int msg, void* arg) {
  switch (msg) {
    case 0x11:
      mpHost = f_11b7240_ref(arg);
      if (g_164b1f4++ == 0)
        f_7fc330(mpHost->GetHost());
      break;
    case 0x12:
      if (--g_164b1f4 == 0 && mpHost)
        f_7fb7b0(mpHost->GetHost());
      mpHost = 0;
      break;
  }
  return false;
}

struct Msg7fc600 {
  char pad30[0x30];
  void* mArg;                                     // +0x30 (message argument read after the fill call)
  char pad34[0x18];
};
struct ISub7fc600 {
  virtual void s0();
  virtual void Notify(void* a, void* b);          // +0x04
};
struct Obj7fc600 { bool f_7fc600(int a, int b); };
// @ 0x007fc600
bool Obj7fc600::f_7fc600(int a, int b) {
  Msg7fc600 msg;
  ((C_7fc2a0*)&msg)->Ctor();
  void* r = f_7fa4f0(&msg, (void*)a, (void*)b);
  ((ISub7fc600*)((char*)this + 0x10))->Notify(msg.mArg, r);
  bool ok = false;
  ((C_7fbce0*)&msg)->Dtor();
  return ok;
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
