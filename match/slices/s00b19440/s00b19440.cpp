// Slice s00b19440 (gold1): simulator input-message handlers, ArgScript/Script helpers, EASTL
// container instances (vector<0x38-byte element> alloc/copy, rbtree<...> key lookups) and the resource
// loader for the input layer (0x00b19440-0x00b1a5a0).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);  // 0x00f47380
void operator delete(void* p);    // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" unsigned __cdecl strlen(const char*);
extern "C" int __cdecl memcmp(const void*, const void*, unsigned int);
#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)
#pragma intrinsic(memcmp)

#define EASTL_ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define SPORE_ALLOC(n) operator new((n), "Simulator", 0, 0, EASTL_ALLOC_FILE, 0xd1)

inline void* operator new(unsigned int, void* p) { return p; }
extern char gEmptyString[];  // 0x01667bac

// ------------------------------------------------------------------ basic_string<char>
char* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);  // 0x011e0744 (memcpy helper)
struct string8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void RangeInitialize(unsigned n);  // 0x00475ab0
  string8() {
    mpBegin = gEmptyString;
    mpEnd = gEmptyString;
    mpCapacity = gEmptyString + 1;
  }
  string8(const char* b, const char* e) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    unsigned n = (unsigned)(e - b);
    RangeInitialize(n + 1);
    FUN_011e0744(mpBegin, b, n);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  string8& assign(const char* b, const char* e);  // 0x00454cb0
  int Find(const char* lit, int pos) const;       // 0x00841d00
};
string8 __cdecl operator+(const string8& a, const string8& b);  // 0x00618890

extern "C" int __cdecl sscanf(const char*, const char*, ...);
extern "C" __declspec(dllimport) __declspec(nothrow) long __cdecl atol(const char*);

// eastl string vs char-literal equality (the "DoFindNode<char const*, equal_to_2>" helper)
bool __cdecl StringEqLit(const string8* s, const char* lit);  // 0x00555020

// ------------------------------------------------------------------ Elem38: 0x38-byte vector element
struct Elem38 {
  string8 name;                    // +0x00
  int pad0c;                       // +0x0c (not copied by operator=)
  int f10, f14, f18, f1c, f20;     // +0x10
  char f24;                        // +0x24
  char pad25[3];
  int f28, f2c, f30, f34;          // +0x28
  Elem38(const Elem38& o);                                   // 0x00b1a0f0
  Elem38& __thiscall operator=(const Elem38& o);             // 0x00b19d40
};

Elem38* __cdecl Elem38_Copy(Elem38* first, Elem38* last, Elem38* dest);          // 0x00b19df0
Elem38* __cdecl Elem38_CopyBackward(Elem38* first, Elem38* last, Elem38* dest);  // 0x00b19e70
Elem38* __cdecl Elem38_UninitCopy5(void* tmp, Elem38* first, Elem38* last, Elem38* dest, const void* vec);  // 0x00b1a1d0

struct Elem38Vector {
  Elem38* mpBegin;
  Elem38* mpEnd;
  Elem38* mpCapacity;
  Elem38Vector* __thiscall DoAllocate(unsigned n, void* a);  // 0x00b199f0
  Elem38* __thiscall DoAllocateAndCopy(unsigned n, Elem38* first, Elem38* last);  // 0x00b1a540
  Elem38Vector(const Elem38Vector& x);  // 0x00b1a350
};

// ------------------------------------------------------------------ rbtree plumbing (EASTL layout)
struct RBNodeBase {
  RBNodeBase* mpNodeRight;   // +0
  RBNodeBase* mpNodeLeft;    // +4
  RBNodeBase* mpNodeParent;  // +8
  char mColor;               // +0xc
};
RBNodeBase* __cdecl RBTreeIncrement(RBNodeBase* p);  // 0x00921580
int __cdecl FUN_005f7870(const char* a, const char* b, unsigned n);  // 0x005f7870 (eastl::Compare)

struct IntStrPair {  // eastl::pair<int, string8> (node payload at +0x10)
  int first;
  string8 second;
  void CopyFrom(const IntStrPair* src);  // 0x00b20b90
};
struct IntStringNode : RBNodeBase {  // map<int, string8>, node size 0x24
  int first;                         // +0x10
  string8 second;                    // +0x14
  char pad[4];
};
struct IntStringMap {
  int mDummy;
  IntStringNode* __thiscall DoCreateNodeCopy(const IntStringNode* src, IntStringNode* parent);  // 0x00b1a5a0
};

struct StrTree {  // map<string8, V>
  int mDummy;
  RBNodeBase mAnchor;  // +4: right, +8: left, +0xc: parent
  void __thiscall LowerBound(RBNodeBase** out, const string8* key);  // 0x00b19cb0
};

// ------------------------------------------------------------------ variant / map-instance helpers
struct Variant {
  char pad[0x10];
  unsigned short w10;  // +0x10
  unsigned short w12;  // +0x12
  void Set(int a, int b, int c, int d, int e);  // 0x0093dd80
  Variant* __thiscall SetInt(int arg);
};

struct Map15680cc {
  void __thiscall Find(RBNodeBase** out, const string8* key);  // 0x00b20930
};

// ------------------------------------------------------------------ globals
extern int g_167be88;                 // 0x0167be88 (last input id)
extern int g_169dda0;                 // 0x0169dda0
extern float g_13eb8a0;               // 0x013eb8a0 (repeat threshold)
extern char g_14365d8[];              // 0x014365d8 (value prefix literal)
extern char g_14129c4[];              // 0x014129c4 ("%x")
extern char g_1414a90;                // 0x01414a90 (object-prefix char)
extern char g_141c920[];              // 0x0141c920 ("Windows")
extern char g_145d228[];              // 0x0145d228 ("TerrainObject")
extern char g_15680cc[];              // 0x015680cc (map<string128,int> instance)
extern char g_15680d0[];              // 0x015680d0 (its anchor)
struct NameValue { const char* name; int value; };
extern NameValue g_tbl15681c0[];      // 0x015681c0 (9 entries)
extern NameValue g_tbl1568208[];      // 0x01568208 (11 entries)
extern NameValue g_tbl1568260[];      // 0x01568260 (10 entries)
extern NameValue g_tbl15680e8[];      // 0x015680e8 (27 entries)

struct Stopwatch {
  unsigned lo, hi, zero1, zero2;  // +0x00..+0x0c
  int mode;                       // +0x10
  float scale;                    // +0x14
  long long GetElapsedTime();     // 0x0093a3a0
};
extern Stopwatch g_sw;  // 0x0167c280

extern "C" int __stdcall QueryPerformanceCounter(__int64* lpPerformanceCount);  // kernel32
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

// ------------------------------------------------------------------ interfaces
struct IObj;
struct IRootB {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12();
  virtual IObj* Get34();              // +0x34
  virtual void v14();
  virtual void Get3c(void* out, int z);  // +0x3c
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24();
  virtual int Get64(unsigned id);     // +0x64
};
extern IRootB* __cdecl GetRoot();     // 0x00b3d240
extern void __cdecl FUN_00b3d230();   // 0x00b3d230

struct IObj {
  virtual void o0(); virtual void o1(); virtual void o2();
  virtual IObj* Query(unsigned id);   // +0x0c
  virtual void o4(); virtual void o5(); virtual void o6(); virtual void o7();
  virtual void o8(); virtual void o9(); virtual void o10();
  virtual bool Is();                  // +0x2c
  virtual void o12();
  int GetObjId(int arg);              // 0x00b18e70
};

struct Msg {
  int a0, a4, a8, ac;
  void* key;             // +0x10
  char c18;              // +0x18
  char c19;              // +0x19
  unsigned short w1a;    // +0x1a
  char pad1c[8];
};
struct cMsgMgr {
  int __thiscall Dispatch(Msg* m, int flag);  // 0x008d3e30
};
extern cMsgMgr g_msgMgr;  // 0x0167bef0

// ------------------------------------------------------------------ input owner (this for group A)
struct cInput {
  virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
  virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
  virtual void Fn20(int a, int b, int c);                                        // +0x20
  virtual void c24(); virtual void c28(); virtual void c2c();
  virtual void Fn30(int type, int id, void* e, void* buf, int flags);            // +0x30
  virtual void o34();                                                            // pad to data
  char pad[0x68 - 4];
  float f68;             // +0x68 (last position x)
  float f6c;             // +0x6c (last position y)
  float f70;             // +0x70 (repeat radius)
  char pad74[0xdc - 0x74];
  char* pdc;             // +0xdc
  char* pe0;             // +0xe0
  char padE4[0xec - 0xe4];
  string8 strEC;         // +0xec

  bool F19440(int a, int b);                          // 0x00b19440
  bool F194d0(int a, int b, int c, int d);            // 0x00b194d0
  bool F195f0(int a, int b, int c, int d);            // 0x00b195f0
  bool F196a0(float x, float y, int key);             // 0x00b196a0
  bool F197b0(int a, int b, int c, int d);            // 0x00b197b0
  bool F19810(int a, char b);                         // 0x00b19810
  void F19890(int a, int b);                          // 0x00b19890
  bool LoadResource(const char* name, void* owner, char flag);  // 0x00b19f70
};

// ================================================================== @ 0x00b19440
bool cInput::F19440(int a, int b) {
  FUN_00b3d230();
  IObj* e = GetRoot()->Get34();
  char buf[0x10];
  GetRoot()->Get3c(buf, 0);
  int f = e->GetObjId(b);
  Fn30(5, b, e, buf, f);

  Msg m;
  m.a0 = 0; m.a4 = 0;
  m.key = (void*)b;
  m.w1a = (unsigned short)b;
  m.c19 = 0; m.c18 = 0;
  g_msgMgr.Dispatch(&m, 0);
  return false;
}

// ================================================================== @ 0x00b194d0
bool cInput::F194d0(int a, int b, int c, int d) {
  int type = 1;
  if (a == g_167be88) {
    double elapsed = (double)g_sw.GetElapsedTime();
    if (elapsed * g_sw.scale > (double)g_13eb8a0) type = 2;
  }
  g_167be88 = a;

  if (g_sw.mode == 1) {
    unsigned __int64 t = __rdtsc();
    g_sw.lo = (unsigned)t;
    g_sw.hi = (unsigned)(t >> 32);
  } else {
    __int64 q;
    QueryPerformanceCounter(&q);
    g_sw.lo = (unsigned)q;
    g_sw.hi = (unsigned)(q >> 32);
  }
  g_sw.zero1 = 0;
  g_sw.zero2 = 0;

  IObj* e = GetRoot()->Get34();
  char buf[0x10];
  GetRoot()->Get3c(buf, 0);

  Msg m;
  m.a0 = 0; m.a4 = 0;
  m.key = (void*)a;
  m.w1a = (unsigned short)d;
  m.c19 = 0; m.c18 = 0;
  g_msgMgr.Dispatch(&m, 1);

  int f = e->GetObjId(d);
  Fn30(type, a, e, buf, f);
  return false;
}

// ================================================================== @ 0x00b195f0
bool cInput::F195f0(int a, int b, int c, int d) {
  IObj* e = GetRoot()->Get34();
  if (e != 0) {
    IObj* x = e->Query(0x17f243b);
    if (x != 0 && x->Is()) e = 0;
  }
  char buf[0x10];
  GetRoot()->Get3c(buf, 0);
  int f = e->GetObjId(d);
  Fn30(3, b, e, buf, f);

  Msg m;
  m.a0 = 0; m.a4 = 0;
  m.key = (void*)b;
  m.w1a = (unsigned short)d;
  m.c19 = 0; m.c18 = 0;
  g_msgMgr.Dispatch(&m, 0);
  return false;
}

// ================================================================== @ 0x00b196a0
bool cInput::F196a0(float x, float y, int key) {
  IObj* e = GetRoot()->Get34();
  char buf[0x10];
  GetRoot()->Get3c(buf, 0);
  if (e != 0) g_169dda0 = (int)e->Query(0x2ee8eeb);
  else g_169dda0 = 0;

  int f = e->GetObjId(key);
  Fn30(6, 0, e, buf, f);

  if (f70 == 0.0f) {
    f68 = x;
    f6c = y;
    return false;
  }
  float dx = x - f68;
  float dy = y - f6c;
  if (dx * dx + dy * dy > f70 * f70) {
    f = e->GetObjId(key);
    Fn30(7, 0, e, buf, f);
    f70 = 0.0f;
  }
  return false;
}

// ================================================================== @ 0x00b197b0
bool cInput::F197b0(int a, int b, int c, int d) {
  IObj* e = GetRoot()->Get34();
  char buf[0x10];
  GetRoot()->Get3c(buf, 0);
  int f = e->GetObjId(d);
  Fn30(8, b, e, buf, f);
  return false;
}

// ================================================================== @ 0x00b19810
bool cInput::F19810(int a, char b) {
  if (b != 0) GetRoot()->Get64(0x703d8d99);
  IObj* e = GetRoot()->Get34();
  char buf[0x10];
  GetRoot()->Get3c(buf, 0);
  int f = e->GetObjId(0);
  Fn30(9, b, e, buf, f);
  return false;
}

// ================================================================== @ 0x00b19890
void cInput::F19890(int a, int b) {
  char* p = pdc;
  if (p != pe0) {
    *p = 0;
    pe0 = pdc;
  }
  Fn20(a, b, b);
}

// ================================================================== @ 0x00b198d0
extern void* g_vtbl145d210;  // 0x0145d210
struct cArgCommandBase { void __thiscall BaseCtor(); };  // 0x0083c800
// EA::ArgScript command object constructor: run the base ctor, store the payload,
// then install the derived vtable.
struct cArgCommandCtor {
  void* __thiscall Init(int a);  // 0x00b198d0
};
void* cArgCommandCtor::Init(int a) {
  ((cArgCommandBase*)this)->BaseCtor();
  *(int*)((char*)this + 0x10) = a;
  *(void**)this = &g_vtbl145d210;
  return this;
}

// ================================================================== @ 0x00b198f0
// @ 0x00b198f0
bool __cdecl FUN_00b198f0(const char* lit, const string8* s) {
  unsigned n = strlen(lit);
  if (n != (unsigned)(s->mpEnd - s->mpBegin)) return false;
  return memcmp(lit, s->mpBegin, n) == 0;
}

// ================================================================== @ 0x00b199f0
Elem38Vector* Elem38Vector::DoAllocate(unsigned n, void* a) {
  Elem38* data;
  if (n != 0) data = (Elem38*)SPORE_ALLOC(n * 0x38);
  else data = 0;
  mpBegin = data;
  mpEnd = data;
  mpCapacity = data + n;
  return this;
}

// ================================================================== @ 0x00b19a50 / a90 / ad0
int __cdecl FUN_00b19a50(const string8* s) {
  for (unsigned i = 0; i < 9; i++)
    if (StringEqLit(s, g_tbl15681c0[i].name)) return g_tbl15681c0[i].value;
  return 0;
}
int __cdecl FUN_00b19a90(const string8* s) {
  for (unsigned i = 0; i < 0xb; i++)
    if (StringEqLit(s, g_tbl1568208[i].name)) return g_tbl1568208[i].value;
  return 0;
}
int __cdecl FUN_00b19ad0(const string8* s) {
  for (unsigned i = 0; i < 0xa; i++)
    if (StringEqLit(s, g_tbl1568260[i].name)) return g_tbl1568260[i].value;
  return 0;
}

// ================================================================== @ 0x00b19b10
int __cdecl FUN_00b19b10(void* container, const char* key) {
  RBNodeBase* end = (RBNodeBase*)((char*)container + 4);
  RBNodeBase* n = *(RBNodeBase**)((char*)container + 8);
  while (n != end) {
    if (StringEqLit((const string8*)((char*)n + 0x14), key)) return *(int*)((char*)n + 0x10);
    n = RBTreeIncrement(n);
  }
  return -1;
}

// ================================================================== @ 0x00b19b60
struct cSPEditorPaintTheme {
  bool __thiscall GetMostFrequentPaintFromMapList();
};
bool cSPEditorPaintTheme::GetMostFrequentPaintFromMapList() {
  char* map = *(char**)((char*)this + 0x10);
  if (map == 0) return false;

  RBNodeBase* end = (RBNodeBase*)(map + 4);
  RBNodeBase* n = *(RBNodeBase**)(map + 8);
  while (n != end) {
    Elem38* begin = *(Elem38**)((char*)n + 0x14);
    Elem38* vend = *(Elem38**)((char*)n + 0x18);
    unsigned count = (unsigned)(vend - begin);
    for (unsigned i = 0; i < count; i++) {
      unsigned key = *(unsigned*)((char*)begin + i * 0x38 + 0x10);
      if (key == 0xfffffffeu || key == 0xfffffffdu) continue;

      RBNodeBase* cur = *(RBNodeBase**)(map + 0xc);
      RBNodeBase* lb = end;
      while (cur) {
        unsigned ck = *(unsigned*)((char*)cur + 0x10);
        if (ck < key) cur = cur->mpNodeRight;
        else { lb = cur; cur = cur->mpNodeLeft; }
      }
      if (lb == end || key < *(unsigned*)((char*)lb + 0x10)) return false;
    }
    n = RBTreeIncrement(n);
    map = *(char**)((char*)this + 0x10);
    end = (RBNodeBase*)(map + 4);
  }
  return true;
}

// ================================================================== @ 0x00b19c80
Variant* Variant::SetInt(int arg) {
  w10 = 0;
  w12 = 0;
  Set(0x11, 0x29, arg, 4, 1);
  return this;
}

// ================================================================== @ 0x00b19cb0
void StrTree::LowerBound(RBNodeBase** out, const string8* key) {
  RBNodeBase* anchor = &mAnchor;
  RBNodeBase* x = mAnchor.mpNodeParent;
  if (x == 0) {
    *out = anchor;
    return;
  }
  const char* kBegin = key->mpBegin;
  int kLen = (int)(key->mpEnd - kBegin);
  RBNodeBase* y = anchor;
  do {
    const char* nBegin = *(const char**)((char*)x + 0x10);
    int nLen = (int)(*(char**)((char*)x + 0x14) - nBegin);
    int minLen = nLen < kLen ? nLen : kLen;
    int r = FUN_005f7870(nBegin, kBegin, (unsigned)minLen);
    if (r == 0) {
      if (nLen < kLen) x = x->mpNodeRight;
      else { y = x; x = x->mpNodeLeft; }
    } else if (r < 0) {
      x = x->mpNodeRight;
    } else {
      y = x;
      x = x->mpNodeLeft;
    }
  } while (x != 0);
  *out = y;
}

// ================================================================== @ 0x00b19d40
Elem38& Elem38::operator=(const Elem38& o) {
  if (&o != this) name.assign(o.name.mpBegin, o.name.mpEnd);
  f10 = o.f10; f14 = o.f14; f18 = o.f18; f1c = o.f1c; f20 = o.f20;
  f24 = o.f24;
  f28 = o.f28; f2c = o.f2c; f30 = o.f30; f34 = o.f34;
  return *this;
}

// ================================================================== @ 0x00b19df0
Elem38* __cdecl Elem38_Copy(Elem38* first, Elem38* last, Elem38* dest) {
  if (first != last) {
    do {
      if (first != dest) dest->name.assign(first->name.mpBegin, first->name.mpEnd);
      dest->f10 = first->f10; dest->f14 = first->f14; dest->f18 = first->f18;
      dest->f1c = first->f1c; dest->f20 = first->f20;
      dest->f24 = first->f24;
      dest->f28 = first->f28; dest->f2c = first->f2c; dest->f30 = first->f30;
      dest->f34 = first->f34;
      ++first;
      ++dest;
    } while (first != last);
  }
  return dest;
}

// ================================================================== @ 0x00b19e70
Elem38* __cdecl Elem38_CopyBackward(Elem38* first, Elem38* last, Elem38* dest) {
  if (last != first) {
    do {
      --last;
      --dest;
      if (last != dest) dest->name.assign(last->name.mpBegin, last->name.mpEnd);
      dest->f10 = last->f10; dest->f14 = last->f14; dest->f18 = last->f18;
      dest->f1c = last->f1c; dest->f20 = last->f20;
      dest->f24 = last->f24;
      dest->f28 = last->f28; dest->f2c = last->f2c; dest->f30 = last->f30;
      dest->f34 = last->f34;
    } while (last != first);
  }
  return dest;
}

// ================================================================== @ 0x00b19ef0
int __cdecl FUN_00b19ef0(const string8* s) {
  int local = 0;
  for (unsigned i = 0; i < 0x1b; i++) {
    if (StringEqLit(s, g_tbl15680e8[i].name)) {
      local = g_tbl15680e8[i].value;
      break;
    }
  }
  if (local == 0) {
    if (s->Find(g_14365d8, 0) != -1) {
      sscanf(s->mpBegin, g_14129c4, &local);
    } else {
      local = (signed char)s->mpEnd[-1];
    }
  }
  return local;
}

// ================================================================== @ 0x00b19f70
extern void* __cdecl FUN_0067dcd0();                                        // 0x0067dcd0 (ResourceMan::GetManager)
extern void* __cdecl FUN_0093c5a0(void* out, const char* s, int n);         // 0x0093c5a0 (ConvertToString16)
extern void __cdecl FUN_00686490(void* a, void* b);                         // 0x00686490 (OpenRecordAsStream)
extern void __cdecl FUN_008d49b0(void* p);                                  // 0x008d49b0
extern void __cdecl FUN_008d5c50(void* a, void* b, void* c, const char* d); // 0x008d5c50
extern void __cdecl FUN_008d3b10(void* p);                                  // 0x008d3b10
extern void* __cdecl FUN_008d34f0(void* a, void* b, void* c, int d, int e, int f);  // 0x008d34f0
extern void __cdecl FUN_008d41b0(void* p);                                  // 0x008d41b0
extern void __cdecl FUN_00b18ef0();                                         // 0x00b18ef0

bool cInput::LoadResource(const char* name, void* owner, char flag) {
  int local[3] = {0, 0, 0};
  char wbuf[12];
  void* mgr = FUN_0067dcd0();
  void** w = (void**)FUN_0093c5a0(wbuf, name, -1);

  typedef void (__thiscall *LoadFn)(void*, void*, void*, int, int);
  ((LoadFn)((*(void***)mgr)[0x78 / 4]))(mgr, local, *w, 0x24a0e52, 0x24a4f5a);

  // free the temporary wide string
  {
    char* b = *(char**)(wbuf + 0);
    char* e = *(char**)(wbuf + 4);
    unsigned sz = (unsigned)(e - b) & 0xfffffffe;
    if (sz > 2 && b) operator delete[](b);
  }

  void* stream = 0;
  void* stream2 = 0;
  FUN_00686490(&stream, &stream2);

  {
    const char* q = name;
    const char* p;
    do { p = q; ++q; } while (*p != 0);
    strEC.assign(name, p);
  }
  if (flag != 0) FUN_008d49b0((char*)this + 0x90);

  if (stream == 0) return false;

  typedef int (__thiscall *SizeFn)(void*);
  typedef void (__thiscall *ReadFn)(void*, void*, int);
  int sz = ((SizeFn)((*(void***)stream)[0x1c / 4]))(stream);
  char* buf = (char*)SPORE_ALLOC(sz + 1);
  ((ReadFn)((*(void***)stream)[0x30 / 4]))(stream, buf, sz);

  FUN_008d5c50((char*)this + 0x90, buf, buf + sz, g_141c920);
  operator delete[](buf);

  char* dst = (char*)this + 0x74;
  FUN_008d3b10(dst);
  void* r = FUN_008d34f0((char*)this + 0x90, (void*)FUN_00b18ef0, this, 0, 0, -2);
  for (int i = 0; i < 7; i++) ((int*)dst)[i] = ((int*)r)[i];
  FUN_008d41b0(dst);

  if (owner != 0) {
    typedef void (__thiscall *NotifyFn)(void*, void*);
    ((NotifyFn)((*(void***)this)[0x28 / 4]))(this, owner);
  }
  return true;
}

// ================================================================== @ 0x00b1a0f0
Elem38::Elem38(const Elem38& o) : name(o.name.mpBegin, o.name.mpEnd) {
  f10 = o.f10; f14 = o.f14; f18 = o.f18; f1c = o.f1c; f20 = o.f20;
  f24 = o.f24;
  f28 = o.f28; f2c = o.f2c; f30 = o.f30; f34 = o.f34;
}

// ================================================================== @ 0x00b1a250
int __cdecl FUN_00b1a250(const string8* s) {
  RBNodeBase* it;
  ((Map15680cc*)g_15680cc)->Find(&it, s);
  if (it != (RBNodeBase*)g_15680d0) return *(int*)((char*)it + 0x20);
  return atol(s->mpBegin);
}

// ================================================================== @ 0x00b1a290
extern int __cdecl FUN_00b214e0(const char* s);  // 0x00b214e0
extern void __cdecl StrConcat(string8* out, const string8* a, const string8* b);  // 0x00618890
struct RawStr { char* mpBegin; char* mpEnd; char* mpCapacity; };
int __cdecl FUN_00b1a290(const string8* s) {
  if (StringEqLit(s, g_145d228)) return 0;

  char* buf = (char*)SPORE_ALLOC(2);
  buf[0] = (char)g_1414a90;
  buf[1] = 0;

  RawStr tmp;
  tmp.mpBegin = buf;
  tmp.mpEnd = buf + 1;
  tmp.mpCapacity = buf + 2;

  RawStr result;
  StrConcat((string8*)&result, (const string8*)&tmp, s);
  if (buf && (buf + 2 - buf) > 1) operator delete[](buf);

  int v = FUN_00b214e0(result.mpBegin);
  if (result.mpBegin && (result.mpCapacity - result.mpBegin) > 1)
    operator delete[](result.mpBegin);
  return v;
}

// ================================================================== @ 0x00b1a350
Elem38Vector::Elem38Vector(const Elem38Vector& o) {
  DoAllocate((unsigned)(o.mpEnd - o.mpBegin), (void*)((char*)&o + 0xc));
  Elem38* end;
  Elem38_UninitCopy5(&end, o.mpBegin, o.mpEnd, mpBegin, (const void*)&o);
  mpEnd = end;
}

// ================================================================== @ 0x00b1a540
Elem38* Elem38Vector::DoAllocateAndCopy(unsigned n, Elem38* first, Elem38* last) {
  Elem38* data = n ? (Elem38*)SPORE_ALLOC(n * 0x38) : 0;
  Elem38* end;
  Elem38_UninitCopy5(&end, first, last, data, (const void*)n);
  return data;
}

// ================================================================== @ 0x00b1a5a0
IntStringNode* IntStringMap::DoCreateNodeCopy(const IntStringNode* src, IntStringNode* parent) {
  IntStringNode* node = (IntStringNode*)SPORE_ALLOC(0x24);
  IntStrPair* dst = (IntStrPair*)&node->first;
  if (dst) dst->CopyFrom((const IntStrPair*)&src->first);
  node->mpNodeRight = 0;
  node->mpNodeLeft = 0;
  node->mpNodeParent = parent;
  node->mColor = src->mColor;
  return node;
}
