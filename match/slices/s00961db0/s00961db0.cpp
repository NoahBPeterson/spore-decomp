// Slice s00961db0: EA::UTFWin::Window / cGetChildWindowCache and hash_map helpers.
// Reconstructed from the annotated disassembly; real names where the 2008 PDB has them.
#include "types.h"

// ---------------------------------------------------------------------------
// generic stubs
// ---------------------------------------------------------------------------
struct RefObj {                 // object with a virtual Release() in vtable slot 1 (+4)
  virtual void r0();
  virtual void Release();
  virtual void r2();
};
struct AllocObj {               // allocator with a virtual deallocate(void*, unsigned) in slot 3
  virtual void a0();
  virtual void a1();
  virtual void a2();
  virtual void deallocate(void*, unsigned);
};
struct VObj4 {                  // object with virtuals; slot 3 (+0xc)
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual int v3(int);
};
struct VObj90 {                 // object with virtuals; slot 0x90/4 = 0x24
  virtual void x00(); virtual void x01(); virtual void x02(); virtual void x03();
  virtual void x04(); virtual void x05(); virtual void x06(); virtual void x07();
  virtual void x08(); virtual void x09(); virtual void x0a(); virtual void x0b();
  virtual void x0c(); virtual void x0d(); virtual void x0e(); virtual void x0f();
  virtual void x10(); virtual void x11(); virtual void x12(); virtual void x13();
  virtual void x14(); virtual void x15(); virtual void x16(); virtual void x17();
  virtual void x18(); virtual void x19(); virtual void x1a(); virtual void x1b();
  virtual void x1c(); virtual void x1d(); virtual void x1e(); virtual void x1f();
  virtual void x20(); virtual void x21(); virtual void x22(); virtual void x23();
  virtual void v90();
};

extern char g_166b190[];        // EA::UTFWin global cGetChildWindowCache singleton
extern void (*g_free_16f4aec)(void*);   // operator delete(void*) thunk in the IAT
extern void __stdcall FUN_00b6faa0(void*);
extern void FUN_00a7bf40(void*, void*);
extern void FUN_009615c0(void*, void*, int);
extern int  FUN_6ab760(void*, void*);
extern unsigned __stdcall FUN_011f3620(unsigned, unsigned, unsigned);
extern void* FUN_009512c0(...);
extern void FUN_011f2bc0();
extern void FUN_011ed910();
extern void FUN_011f4e90();
extern void FUN_011f3580();
extern void FUN_011f3130();
extern int  FUN_011f2e70(void*, void*);
extern void FUN_011f21a0();
extern int   g_16f8afc;
struct S95e7a0 { void f(); };
struct S925f30 { void f(void*); };
struct S962da0c { void f(); };
struct S11f36a0 { void f(); };
struct S925e60 { void f(); };
struct S620230 { void f(); };
struct Vtbl190 { char pad[0x190]; int (__stdcall *fn)(void*, int, int, int, int); };
struct Vtbl1a0 { char pad[0x1a0]; int (__stdcall *fn)(void*, int); };
struct Vtbl144 { char pad[0x144]; void (__stdcall *fn)(void*, int, int, int); };
struct Vtbl148 { char pad[0x148]; void (__stdcall *fn)(void*, int, int, int, int, int, int); };
struct VtblE0 { char pad[0xe0]; void (__thiscall *fn)(void*, int); };

// in-slice callees
struct S961a50 { void f(); };
struct S961db0 { void f(void**, unsigned); };
struct S961e80 { bool f(); };
struct S961f20 { void f(void*); };
struct S961fc0 { void f(void*); };
struct S962100 { int* f(void*); void g(void*); };
struct S962180 { void* f(void*, void*, void*); };
struct S962360 { void* f(int, int, int); };
struct S9625f0 { void f(void*); };
// out-of-slice callees
struct S959e00 { void f(void*); };
struct S959add0 { void f(void*); };
struct S960b40 { void f(); };
struct S960ae0 { void f(); };
struct S961450 { void f(); };
struct S961b40 { void f(void*); };
struct S965fcc0 { void* f(int, int, int); };
struct S961c80 { void f(void*, void*, int); };
struct S9613e0 { void f(); };
struct S645ed0 { void find(void*, void*); };
struct S423650 { void assign(wchar_t*, wchar_t*); };

// functions defined here
struct S962580 { void f(int, int); };
struct S9625b0 { int f(int, int, int); };
struct S962530 { void f(int, int); };
struct S962d10 { void f(); };
struct S9628f0 { void f(void*); };
struct S962840 { bool f(void*); };
struct S962740 { void f(); };
struct S962950 { void f(); };
struct S962a10 { S962a10* f(); };
struct S962da0 { bool f(); };
struct S962e80 { unsigned f(unsigned, unsigned); };
struct S962f00 { void f(); };

// field-bearing helper structs
struct HNode { int k0; int k1; RefObj* a; RefObj* b; HNode* next; };
struct Cln_e { void f(); };
struct Cln_4e { void f(); };
struct Cln_35 { void f(); };
struct Cln_31 { void f(); };

// globals used by the ImmediateMode / D3D state code
extern void* g_16f89d0;         // d3d device object pointer
extern void* g_16f65a0;         // active vertex descriptor
extern int   g_16f9110;         // soft-state dirty flags
extern int   g_16f9138;
extern int   g_16f913c;
extern int   g_16f9140;
extern void* g_16f6568;         // shader state object pointer

// ---------------------------------------------------------------------------
// @ 0x00961db0  hashtable::DoFreeNodes(bucketArray, bucketCount)
// ---------------------------------------------------------------------------
void S961db0::f(void** pbuckets, unsigned count) {
  HNode** buckets = (HNode**)pbuckets;
  for (unsigned i = 0; i < count; i++) {
    HNode* p = buckets[i];
    while (p) {
      HNode* node = p;
      RefObj* r = node->b;
      HNode* next = p->next;
      if (r) r->Release();
      r = node->a;
      if (r) r->Release();
      ((AllocObj*)*(void**)((char*)this + 0x1c))->deallocate(node, 0x18);
      p = next;
    }
    buckets[i] = 0;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00961e20
// ---------------------------------------------------------------------------
bool FUN_00961e20(void* a, void* b) {
  void* obj = *(void**)((char*)a + 4);
  ((S961a50*)obj)->f();
  unsigned n = *(unsigned*)((char*)b + 8);
  char* p = (char*)(*(int*)((char*)b + 4) + n * 4 - 4);
  while (n) {
    void* q = *(void**)p;
    n--;
    p -= 4;
    if (q) {
      int r = ((int(__thiscall*)(void*, int))((void**)(*(void***)q))[3])(q, (int)0x2f009dd0);
      if (r) {
        void* base = (char*)obj + 4;
        ((void(__thiscall*)(void*, int))((void**)(*(void***)base))[0x41])(base, r);
      }
    }
  }
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00961e80  EA::UTFWin::Window::Shutdown()
// ---------------------------------------------------------------------------
bool S961e80::f() {
  ((S961a50*)this)->f();
  char* self = (char*)this;
  int* lst = (int*)(self + 0x3c);
  if (lst[1] != (int)lst) {
    char* base = self + 4;
    do {
      char* v = *(char**)(self + 0x40);
      char* adj;
      if (v) { v -= 8; adj = v ? v + 4 : 0; }
      else adj = 0;
      ((VtblE0*)*(void**)base)->fn(base, (int)(size_t)adj);
    } while (lst[1] != (int)lst);
  }
  RefObj* p;
  p = *(RefObj**)(self + 0x1e0);
  if (p) { *(void**)(self + 0x1e0) = 0; p->Release(); }
  p = *(RefObj**)(self + 0x1e8);
  if (p) { *(void**)(self + 0x1e8) = 0; p->Release(); }
  p = *(RefObj**)(self + 0x1e4);
  if (p) { *(void**)(self + 0x1e4) = 0; p->Release(); }
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x00961f20
// ---------------------------------------------------------------------------
void S961f20::f(void* key) {
  char* self = (char*)this;
  if (FUN_6ab760(self + 0xac, key)) return;
  wchar_t* k = (wchar_t*)key;
  wchar_t* e = k;
  while (*e) e++;
  ((S423650*)(self + 0xac))->assign(k, e);
  ((VObj90*)self)->v90();
  int* m = *(int**)(self + 0x30);
  if (m) {
    void* base = self;
    int tmp[2];
    tmp[0] = 0xe; tmp[1] = 2;
    ((void(__thiscall*)(void*, int, int, void*, int))((void**)(*(void***)m))[4])(
        m, (int)(uint32_t)(size_t)base, (int)(uint32_t)(size_t)base, tmp, 0);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00961fc0
// ---------------------------------------------------------------------------
void S961fc0::f(void* win) {
  char* self = (char*)this;
  int* head = (int*)(self + 0x60);
  int* it = *(int**)head;
  int best = (int)0x80000000;
  int* bestIt = head;
  int prio = ((int(__thiscall*)(void*))((void**)(*(void***)win))[4])(win);
  if (it != head) {
    do {
      void* n = *(void**)((char*)it + 8);
      if (n != (void*)0x154ef48) {
        if (n == win) {
          int old = *(int*)((char*)it + 0xc);
          int v = ((int(__thiscall*)(void*))((void**)(*(void***)win))[5])(win);
          *(int*)((char*)it + 0xc) = v;
          if (((v ^ old) & 2) == 0) return;
          ((S9613e0*)self)->f();
          return;
        }
        int p = ((int(__thiscall*)(void*))((void**)(*(void***)n))[4])(n);
        if (p <= prio && best < p) { bestIt = it; best = p; }
      }
      it = *(int**)it;
    } while (it != head);
  }
  ((void(__thiscall*)(void*))((void**)(*(void***)win))[0])(win);
  int v = ((int(__thiscall*)(void*))((void**)(*(void***)win))[5])(win);
  void* b = *(void**)(self + 0x68);
  int* node = (int*)((void*(__thiscall*)(void*, int, int, int))((void**)(*(void***)b))[2])(
      b, 0x10, 0, *(int*)(self + 0x6c));
  if (node + 2) { node[2] = (int)(size_t)win; node[3] = v; }
  *node = (int)(size_t)bestIt;
  node[1] = bestIt[1];
  *(int*)bestIt[1] = (int)(size_t)node;
  bestIt[1] = (int)(size_t)node;
  ((S9613e0*)self)->f();
  ((void(__thiscall*)(void*, int, int))((void**)(*(void***)win))[6])(win, (int)(uint32_t)(size_t)self, 0);
  if (*(int*)(self + 0x30) != 0)
    ((void(__thiscall*)(void*, int, int))((void**)(*(void***)win))[6])(win, (int)(uint32_t)(size_t)self, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00962100  eastl::hash_map<unsigned,AutoRefCount<...>>::operator[]
// ---------------------------------------------------------------------------
int* S962100::f(void* key) {
  char* self = (char*)this;
  int found;
  ((S645ed0*)self)->find(&found, key);
  int cnt = *(int*)(self + 8);
  int* buckets = *(int**)(self + 4);
  if ((void*)(uint32_t)found != (void*)buckets[cnt])
    return (int*)((char*)(uint32_t)found + 4);
  int k = *(int*)key;
  int local[3];
  FUN_009615c0(local, &k, 0);
  return (int*)((char*)(uint32_t)local[0] + 4);
}

// ---------------------------------------------------------------------------
// @ 0x00962180  hashtable::DoEraseNode / free one node
// ---------------------------------------------------------------------------
void* S962180::f(void* a_, void* b_, void* c_) {
  int* a = (int*)a_;
  char* b = (char*)b_;
  int* c = (int*)c_;
  int iVar1 = *(int*)(b + 0x10);
  a[1] = (int)(size_t)c;
  *a = iVar1;
  while (iVar1 == 0) {
    a[1] += 4;
    iVar1 = *(int*)(size_t)a[1];
    *a = iVar1;
  }
  int iVar2 = *c;
  if (iVar2 == (int)(size_t)b) {
    *c = *(int*)(iVar2 + 0x10);
  } else {
    int i3 = *(int*)(iVar2 + 0x10);
    while (i3 != (int)(size_t)b) { iVar2 = i3; i3 = *(int*)(i3 + 0x10); }
    *(int*)(iVar2 + 0x10) = *(int*)(i3 + 0x10);
  }
  RefObj* r;
  r = *(RefObj**)(b + 0xc);
  if (r) r->Release();
  r = *(RefObj**)(b + 8);
  if (r) r->Release();
  ((AllocObj*)*(void**)((char*)this + 0x1c))->deallocate(b, 0x18);
  *(int*)((char*)this + 0xc) -= 1;
  return a_;
}

// ---------------------------------------------------------------------------
// @ 0x00962360  hashtable insert with AutoRefCount value
// ---------------------------------------------------------------------------
void* S962360::f(int a, int b, int c) {
  char* self = (char*)this;
  int local_1c = a;
  unsigned local_20 = (unsigned)b;
  FUN_00a7bf40(&local_1c, &local_1c);
  while ((void*)(uint32_t)local_1c != (void*)*(int*)(*(int*)(self + 4) + *(int*)(self + 8) * 4)) {
    void* node = (void*)(uint32_t)local_1c;
    int v = *(int*)((char*)node + 0xc);
    int id = ((int(__thiscall*)(void*))((void**)(*(void***)*(void**)((char*)node + 8))[4]))(*(void**)((char*)node + 8));
    if (id == v) return *(void**)((char*)node + 8);
    if (*(RefObj**)((char*)node + 8)) ((RefObj*)*(void**)((char*)node + 8))->r0();
    if (*(RefObj**)((char*)node + 0xc)) ((RefObj*)*(void**)((char*)node + 0xc))->r0();
    int tmp[1];
    ((S962180*)self)->f(tmp, node, (void*)(size_t)local_20);
    if (*(RefObj**)((char*)node + 0xc)) ((RefObj*)*(void**)((char*)node + 0xc))->Release();
    if (*(RefObj**)((char*)node + 8)) ((RefObj*)*(void**)((char*)node + 8))->Release();
    FUN_00a7bf40(&local_1c, &local_1c);
  }
  void* found = ((S965fcc0*)self)->f(a, b, c);
  return found;
}

// ---------------------------------------------------------------------------
// @ 0x00962580
// ---------------------------------------------------------------------------
void S962580::f(int a, int b) {
  int t = (int)(size_t)this;
  int adj = (t - 4) ? t : 0;
  ((S962360*)g_166b190)->f(adj, a, b);
}

// ---------------------------------------------------------------------------
// @ 0x009625b0
// ---------------------------------------------------------------------------
int S9625b0::f(int a, int b, int c) {
  int t = (int)(size_t)this;
  int adj = (t - 4) ? t : 0;
  void* p = ((S962360*)g_166b190)->f(adj, a, c);
  if (p) return ((VObj4*)p)->v3(b);
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00962530
// ---------------------------------------------------------------------------
void S962530::f(int a, int b) {
  char* self = (char*)this + 0x1e8;
  if (b != 0) {
    int* slot = ((S962100*)self)->f(&a);
    int old = *slot;
    if (b != old) {
      ((RefObj*)b)->r0();
      *slot = b;
      if (old) ((RefObj*)old)->Release();
    }
  } else {
    ((S962100*)self)->g(&a);
  }
}

// ---------------------------------------------------------------------------
// @ 0x009625f0  EA::UTFWin::cGetChildWindowCache::Remove
// ---------------------------------------------------------------------------
void S9625f0::f(void* win) {
  char* self = (char*)this;
  int local_vec[64];
  int* vecBegin = local_vec;
  int* vecEnd = local_vec;
  int** buckets = *(int***)(self + 4);
  int* it = *buckets;
  int** bit = buckets;
  if (!it) {
    bit = buckets + 1;
    it = buckets[1];
    while (!it) { bit++; it = *bit; }
  }
  int count = *(int*)(self + 8);
  if ((void*)it != (void*)buckets[count]) {
    do {
      int* next = *(int**)((char*)it + 0x10);
      int** bit2 = bit;
      while (!next) { bit2++; next = *(int**)bit2; }
      char* ci = (char*)it + 8;
      if (*(void**)it == win || *(void**)(ci + 0) == win || *(void**)(ci + 4) == win) {
        int w = *(int*)(ci + 0);
        if (vecEnd < local_vec + 64) { *vecEnd++ = w; if (w) ((RefObj*)(uint32_t)w)->r0(); }
        else { int tmp[2]; tmp[0] = w; ((S9613e0*)self)->f(); }
        int wp = *(int*)(ci + 4);
        if (vecEnd < local_vec + 64) { *vecEnd++ = wp; if (wp) ((RefObj*)(uint32_t)wp)->r0(); }
        else { int tmp[2]; tmp[0] = wp; ((S9613e0*)self)->f(); }
        ((S962180*)self)->f(0, it, bit2);
      }
      bit = bit2;
      it = next;
    } while ((void*)it != (void*)buckets[count]);
  }
  volatile int dummy = 0; (void)dummy;
}

// ---------------------------------------------------------------------------
// @ 0x00962740  EA::UTFWin::Window::~Window (base subobject releaser)
// ---------------------------------------------------------------------------
void S962740::f() {
  int* self = (int*)this;
  *self = (int)0x1440b44;
  *(int*)((char*)self + 4) = (int)0x14431f8;
  ((S961e80*)self)->f();
  ((S961db0*)((char*)self + 0x1ec))->f((void**)*(void**)((char*)self + 0x1f0), *(unsigned*)((char*)self + 0x1f4));
  *(int*)((char*)self + 0x1f8) = 0;
  if (*(unsigned*)((char*)self + 0x1f4) > 1) g_free_16f4aec(*(void**)((char*)self + 0x1f0));
  RefObj* p;
  p = *(RefObj**)((char*)self + 0x1e8); if (p) p->Release();
  p = *(RefObj**)((char*)self + 0x1e4); if (p) p->Release();
  p = *(RefObj**)((char*)self + 0x1e0); if (p) p->Release();
  int b = *(int*)((char*)self + 0xb0);
  if ((2 < (*(int*)((char*)self + 0xb8) - b)) && b) g_free_16f4aec((void*)b);
  char* head = (char*)self + 0x64;
  char* it = *(char**)((char*)self + 0x64);
  while (it != head) {
    char* nx = *(char**)it;
    void* b = *(void**)((char*)self + 0x6c);
    ((void(__thiscall*)(void*, void*, int))((void**)(*(void***)b))[3])(b, it, 0x10);
    it = nx;
  }
  ((S925e60*)((char*)self + 0x44))->f();
  ((S620230*)((char*)self + 0x3c))->f();
  *(int*)((char*)self + 4) = (int)0x13eb938;
  *self = (int)0x13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x00962840  EA::UTFWin::Window::ChildAdd
// ---------------------------------------------------------------------------
bool S962840::f(void* win) {
  char* self = (char*)this;
  ((S9625f0*)g_166b190)->f(win);
  char* obj;
  if (win) obj = (char*)win - 4; else obj = 0;
  ((void(__thiscall*)(void*))((void**)(*(void***)obj))[0])(obj);
  *(int*)(obj + 0x38) = (int)((char*)self - 4);
  int* it = *(int**)(self + 0x38);
  int* head = (int*)(self + 0x38);
  while (it != head) {
    int* n = it ? it - 2 : 0;
    if ((*(unsigned char*)((char*)n + 0x2c) & 0x40) == 0) break;
    it = *(int**)it;
  }
  int* p2 = (int*)it[1];
  int* p4 = (int*)(obj + 8);
  it[1] = (int)(size_t)p4;
  *p2 = (int)(size_t)p4;
  *(int*)(obj + 0xc) = (int)(size_t)p2;
  *p4 = (int)(size_t)it;
  int mgr = *(int*)(self + 0x30);
  if (mgr) ((S959add0*)mgr)->f(obj);
  if (((bool(__thiscall*)(void*))((void**)(*(void***)obj))[6])(obj)) {
    ((S960b40*)((char*)self - 4))->f();
    ((S960ae0*)((char*)self - 4))->f();
    ((S961450*)((char*)self - 4))->f();
    return true;
  }
  ((void(__thiscall*)(void*, int))((void**)(*(void***)self))[0x38])(self, (int)(size_t)p4 + 4);
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x009628f0  EA::UTFWin::Window::ChildRemove
// ---------------------------------------------------------------------------
void S9628f0::f(void* win) {
  ((S9625f0*)g_166b190)->f(win);
  char* obj;
  if (win) obj = (char*)win - 4;
  else obj = 0;
  int mgr = *(int*)((char*)this + 0x30);
  if (mgr) ((S959e00*)mgr)->f(obj);
  int n = *(int*)(obj + 0xc);
  int p = *(int*)(obj + 8);
  *(int*)n = p;
  *(int*)(p + 4) = n;
  *(int*)(obj + 8) = 0;
  *(int*)(obj + 0xc) = 0;
  RefObj* r = *(RefObj**)obj;
  *(int*)(obj + 0x38) = 0;
  r->Release();
}

// ---------------------------------------------------------------------------
// @ 0x00962950
// ---------------------------------------------------------------------------
void S962950::f() {
  char* self = (char*)this;
  int tmp[8];
  ((S961b40*)tmp)->f(self);
  ((S961db0*)self)->f((void**)*(void**)(self + 4), *(unsigned*)(self + 8));
  *(int*)(self + 0xc) = 0;
  if (*(unsigned*)(self + 8) > 1) {
    void* alloc = *(void**)(self + 0x1c);
    ((void(__thiscall*)(void*, void*, int))((void**)(*(void***)alloc))[3])(alloc, *(void**)(self + 4),
                                                                            *(int*)(self + 8) * 4 + 4);
  }
  *(void**)(self + 0x1c) = FUN_009512c0();
  *(int*)(self + 0x10) = 0x3f800000;
  *(int*)(self + 0x14) = 0x40000000;
  *(int*)(self + 0x20) = 0;
  *(int*)(self + 8) = 1;
  *(int*)(self + 4) = (int)0x154df28;
  *(int*)(self + 0xc) = 0;
  *(int*)(self + 0x18) = 0;
  unsigned n = *(unsigned*)((char*)tmp + 8);
  if (n > 1) {
    void* alloc = *(void**)((char*)tmp + 0x10);
    ((void(__thiscall*)(void*, void*, unsigned))((void**)(*(void***)alloc))[3])(
        alloc, *(void**)((char*)tmp + 4), n * 4 + 4);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00962a10  EA::UTFWin::Window::Window()
// ---------------------------------------------------------------------------
S962a10* S962a10::f() {
  char* self = (char*)this;
  *(int*)(self + 0xc) = 0; *(int*)(self + 8) = 0;
  *(int*)(self + 0x14) = 0; *(int*)(self + 0x10) = 0;
  *(int*)(self + 0x1c) = 0; *(int*)(self + 0x18) = 0;
  *(int*)(self + 0x24) = 0; *(int*)(self + 0x20) = 0;
  *(int*)(self + 4) = (int)0x13f1ab0;
  *(int*)(self) = (int)0x1440b44;
  *(int*)(self + 4) = (int)0x14431f8;
  *(int*)(self + 0x28) = 0;
  *(unsigned char*)(self + 0x31) &= 0xf0;
  *(int*)(self + 0x2c) = 3;
  *(unsigned char*)(self + 0x30) = 0;
  *(int*)(self + 0x34) = 0;
  *(int*)(self + 0x38) = 0;
  *(int*)(self + 0x40) = (int)(self + 0x3c);
  *(int*)(self + 0x3c) = (int)(self + 0x3c);
  void* t = FUN_009512c0(0x10, 0x10);
  ((S925f30*)(self + 0x44))->f(t);
  *(int*)(self + 0x70) = 0;
  *(int*)(self + 0x6c) = (int)(self + 0x44);
  *(int*)(self + 0x64) = (int)(self + 0x64);
  *(int*)(self + 0x68) = (int)(self + 0x64);
  *(int*)(self + 0x74) = 0; *(int*)(self + 0x78) = 0; *(int*)(self + 0x7c) = 0;
  *(int*)(self + 0x80) = 0; *(int*)(self + 0x84) = 0;
  for (int i = 0; i < 8; i++) *(float*)(self + 0x88 + i * 4) = 0.0f;
  *(int*)(self + 0xa8) = 0; *(int*)(self + 0xac) = 0;
  *(int*)(self + 0xb8) = (int)0x1667bae;
  *(int*)(self + 0xb0) = (int)0x1667bac;
  *(int*)(self + 0xb4) = (int)0x1667bac;
  *(int*)(self + 0x1d4) = 0; *(int*)(self + 0x1dc) = 0;
  *(int*)(self + 0x1d8) = -1;
  *(int*)(self + 0xc0) = 1;
  *(int*)(self + 0x1e0) = 0; *(int*)(self + 0x1e4) = 0; *(int*)(self + 0x1e8) = 0;
  *(float*)(self + 0x1fc) = 1.0f;
  *(float*)(self + 0x200) = 2.0f;
  *(int*)(self + 0x1f8) = 0;
  *(int*)(self + 0x204) = 0;
  *(int*)(self + 0x1f4) = 1;
  *(int*)(self + 0x1f0) = (int)0x154df28;
  ((S95e7a0*)(self + 0xc4))->f();
  for (int i = 0; i < 0x11; i++) {
    *(int*)(self + 0x108 + i * 4) = *(int*)(self + 0xc4 + i * 4);
    *(int*)(self + 0x14c + i * 4) = *(int*)(self + 0xc4 + i * 4);
    *(int*)(self + 0x190 + i * 4) = *(int*)(self + 0xc4 + i * 4);
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x00962d10
// ---------------------------------------------------------------------------
void S962d10::f() {
  int* self = (int*)this;
  if (self[1]) { ((Cln_e*)self[1])->f(); g_free_16f4aec((void*)self[1]); self[1] = 0; }
  if (self[8]) { g_free_16f4aec((void*)self[8]); self[8] = 0; }
  if (self[7]) { ((Cln_4e*)self[7])->f(); g_free_16f4aec((void*)self[7]); self[7] = 0; }
  if (self[6]) { ((Cln_35*)self[6])->f(); g_free_16f4aec((void*)self[6]); self[6] = 0; }
  if (self[2]) { ((Cln_31*)self[2])->f(); g_free_16f4aec((void*)self[2]); self[2] = 0; }
}

// ---------------------------------------------------------------------------
// @ 0x00962da0
// ---------------------------------------------------------------------------
bool S962da0::f() {
  char* self = (char*)this;
  void* dev = g_16f89d0;
  void* vd = *(void**)(self + 8);
  if (g_16f65a0 == 0 || !FUN_011f2e70(g_16f65a0, vd))
    g_16f9110 |= 0x100000;
  g_16f65a0 = vd;
  ((S962da0c*)vd)->f();
  int a = *(int*)(*(int*)(self + 0x18) + 4);
  unsigned s = *(unsigned char*)(*(int*)(self + 8) + 0xf);
  if (g_16f9138 != a || g_16f913c != 0 || g_16f9140 != s) {
    int r = ((Vtbl190*)*(void**)dev)->fn(dev, 0, a, 0, (int)s);
    if (r < 0) return false;
    g_16f9138 = a; g_16f913c = 0; g_16f9140 = s;
  }
  int i = 1;
  unsigned off = 0xc;
  do {
    if (*(int*)((char*)&g_16f9138 + off) != 0) {
      int r = ((Vtbl190*)*(void**)dev)->fn(dev, i, 0, 0, 0);
      if (r < 0) return false;
      *(int*)((char*)&g_16f9138 + off) = 0;
      *(int*)((char*)&g_16f913c + off) = 0;
      *(int*)((char*)&g_16f9140 + off) = 0;
    }
    off += 0xc;
    i++;
  } while (off < 0x30);
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x00962e80
// ---------------------------------------------------------------------------
unsigned S962e80::f(unsigned a, unsigned b) {
  char* self = (char*)this;
  *(unsigned*)(self + 0xc) = a;
  unsigned old0 = *(unsigned*)(self + 0x10);
  *(unsigned*)(self + 0x14) = b;
  if (old0 + b > 0x1000) {
    *(unsigned*)(self + 0x10) = 0;
    if (b > 0x1000) return 0;
  }
  unsigned old = *(unsigned*)(self + 0x10);
  int* p = *(int**)(self + 0x18);
  unsigned flags = ((old != 0) * 4u + 4u) | 2u;
  unsigned n = b ? b : (unsigned)p[3];
  unsigned char stride = *(unsigned char*)((size_t)p[0] + 0xf);
  return FUN_011f3620(flags, (unsigned)(p[2] + old) * stride, (unsigned)stride * n);
}

// ---------------------------------------------------------------------------
// @ 0x00962f00  EA::UTFWin::ImmediateModeEx::EndBatch
// ---------------------------------------------------------------------------
void S962f00::f() {
  char* self = (char*)this;
  ((S11f36a0*)*(void**)(self + 0x18))->f();
  void* dev = g_16f89d0;
  FUN_011f21a0();
  void* shader = g_16f6568;
  int (*sfn)(int) = *(int(**)(int))((char*)shader + 0x14);
  if (!sfn(*(int*)(self + 0x20))) return;
  g_16f9110 = 0;
  int idx = 0;
  if (*(int*)(self + 0xc) == 2) idx = *(int*)*(int**)(self + 0x1c);
  if (g_16f8afc != idx) {
    if (((Vtbl1a0*)*(void**)dev)->fn(dev, idx) < 0) return;
    g_16f8afc = idx;
  }
  switch (*(int*)(self + 0xc)) {
    case 0:
      ((Vtbl144*)*(void**)dev)->fn(dev, 2, *(int*)(self + 0x10), (int)(*(unsigned*)(self + 0x14) >> 1));
      break;
    case 1:
      ((Vtbl144*)*(void**)dev)->fn(dev, 4, *(int*)(self + 0x10), (int)(*(unsigned*)(self + 0x14) / 3));
      break;
    case 2:
      ((Vtbl148*)*(void**)dev)->fn(dev, 4, *(int*)(self + 0x10), 0, *(int*)(self + 0x14),
                                    *(int*)(*(int*)(self + 0x1c) + 4),
                                    (int)(*(unsigned*)(self + 0x14) >> 1));
      break;
  }
  *(int*)(self + 0x10) += *(int*)(self + 0x14);
}
