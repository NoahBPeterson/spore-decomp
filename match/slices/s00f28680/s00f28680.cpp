// Slice s00f28680.  Scenario/building-data helpers.  Built /O2 /MD /Gy /TP.

typedef unsigned int uint;
typedef unsigned int size_t;
extern "C" size_t __cdecl wcslen(const wchar_t*);

extern "C" char A_01667bac;   // eastl::gEmptyString16  (empty wide buffer)
extern "C" char B_01667bae;   // gEmptyString16 + 2 bytes

// ---------------------------------------------------------------------------
// Callees.  Resolved to original VAs by hex-name / annotation.

void* FUN_00f25ea0(void* first, void* last, void* dst);              // uninitialized_copy
void* FUN_00f28040(void* dst, uint count, const void* value);        // uninitialized_fill
void  FUN_00dfa3c0(void* a, void* b, void* c, void* d, void* e);     // move range
void  FUN_00f28350(void* a, void* b, void* c);
void  FUN_00f27400(void* a, void* b, void* c);                       // destroy range
void  FUN_00cc8b50(void* a, void* b, void* c);                       // copy_backward
void* FUN_00720200(void* first, void* last, void* dst);              // uninitialized_copy (0x18)
void* FUN_00f473a0(uint size, const char* name, int a, int b,
                   const char* file, int line);                      // allocator allocate
void  FUN_00f47380(void* p);                                         // allocator deallocate
int   FUN_00ef1990(void* a, void* b);
void  FUN_0093aa70(void* io, const void* src, uint n, int byteOrder); // EA::IO::WriteUint32
int   FUN_00f26770(void* ser, const wchar_t* name, int flag, const wchar_t* type);
int   FUN_00f26810(void* ser, const wchar_t* name, int flag, const wchar_t* type);
int   FUN_00eeea50(void* self, void* out);

// eastl::basic_string<char16_t> / basic_string<wchar_t> plumbing.
struct String16 { unsigned short* b; unsigned short* e; unsigned short* c; };

struct WStr {
  wchar_t* b; wchar_t* e; wchar_t* c;
  void ctor(const String16* src);                          // 0x0056e2d0
  void assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  void append(const wchar_t* s);                           // 0x005c3d90
  void range_initialize(const wchar_t* first);             // 0x00579a90
};

void FUN_0093c5a0(String16* out, const char* src, int n);            // 0x0093c5a0 ConvertToString16

// eastl::vector<cSPVector3> (0xc bytes).
struct Vec3 {
  void* b; void* e; void* c;
  void ctor(const Vec3& other);                                      // 0x00473460
};

// SP::cVarListSerializer (0xa14 bytes).
struct ListSer {
  char pad[0xa14];
  void ctor(const void* src, void* generic, uint sig);               // 0x00692f90
  char Read(void* stream);                                           // 0x00693e10
  void Serialize(void* ser);                                         // 0x00692900
};

extern "C" char g_015aff90;
extern "C" char g_015aefd0;

// ---------------------------------------------------------------------------
// Serializer interfaces.

struct IOut {
  virtual void o0();
  virtual void o1();
  virtual void o2();
  virtual void o3();
  virtual void o4();
  virtual void o5();
  virtual void* o6();
};

struct ISer {
  virtual void s0(const wchar_t*);
  virtual void s1(const wchar_t*);
  virtual void s2();
  virtual void s3(const wchar_t*);
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual IOut* s8();
};

// SP::cString (0x14).
struct CS {
  int r0;                       // +0x00
  void* pLocal;                 // +0x04
  const wchar_t* pSrc;          // +0x08
  int pid;                      // +0x0c
  char hasTokens;               // +0x10
  char f11;                     // +0x11
  short pad;                    // +0x12
  const wchar_t* GetText();                     // 0x006b55c0
  void ctor(uint id, uint table, const wchar_t* s);  // 0x006b5770
  CS& operator=(const CS& other);               // 0x006b5430
  void dtor();                                  // 0x006b5240
  ~CS() { dtor(); }
};

// A cString followed by a wide string and two 4-byte ids.
struct TextObj {
  CS cs;                        // +0x00
  WStr ws;                      // +0x14
  int a20;                      // +0x20
  uint id24;                    // +0x24
  uint id28;                    // +0x28
  int fn28c50(void* stream);
};

// Object whose cString view sits at +0x04 (as passed to 00f289d0).
struct ObjD {
  int f00;                      // +0x00
  TextObj t;                    // +0x04
};

// ---------------------------------------------------------------------------
// Existing byte-exact members.

struct Str {
  char _pad[0x10];
  int Assign(const wchar_t* p, const wchar_t* e);
};

struct CStrCtor {
  char _pad[0x14];
  void ctor();
};

struct Obj8c {
  int f00;
  CStrCtor cs;          // +0x04
  int a18, a1c, a20;    // +0x18
  int _g24;             // +0x24
  int a28, a2c;         // +0x28
  int a30, a34, a38;    // +0x30
  int _g3c;
  int a40;              // +0x40
  Obj8c* init();
};

// @ 0x00f28b30
Obj8c* Obj8c::init() {
  f00 = 0;
  cs.ctor();
  a18 = (int)&A_01667bac;
  a1c = (int)&A_01667bac;
  a20 = (int)&B_01667bae;
  a28 = 0;
  a2c = 0;
  a30 = (int)&A_01667bac;
  a34 = (int)&A_01667bac;
  a38 = (int)&B_01667bae;
  a40 = 0;
  return this;
}

struct ObjC {
  char _pad[0x14];
  Str s;                // +0x14
  int f24;              // +0x24
  ObjC* fn28c10(short* p);
};

// @ 0x00f28c10
ObjC* ObjC::fn28c10(short* p) {
  f24 = 0;
  const wchar_t* q = (const wchar_t*)p;
  while (*q) ++q;
  int len = (int)(q - (const wchar_t*)p);
  s.Assign((const wchar_t*)p, (const wchar_t*)p + len);
  return this;
}

struct ObjB {
  char _pad[0x279c];
  Str s;                // +0x279c
  int f27ac;            // +0x27ac
  void fn293b0(short* p);
};

// @ 0x00f293b0
void ObjB::fn293b0(short* p) {
  f27ac = 0;
  const wchar_t* q = (const wchar_t*)p;
  while (*q) ++q;
  int len = (int)(q - (const wchar_t*)p);
  s.Assign((const wchar_t*)p, (const wchar_t*)p + len);
}

// ---------------------------------------------------------------------------
// Reconstructed bodies.

static void buildName(const char* name, String16* src, WStr* out) {
  if (name != 0) {
    FUN_0093c5a0(src, name, -1);
  } else {
    src->b = (unsigned short*)&A_01667bac;
    src->e = src->b;
    src->c = (unsigned short*)&B_01667bae;
  }
  out->ctor(src);
}

static void freeString16(String16& s) {
  if (s.b != 0 && (((uint)((char*)s.e - (char*)s.b) & 0xfffffffeu) > 2))
    FUN_00f47380(s.b);
}

static void freeWStr(WStr& s) {
  if (s.b != 0 && (((uint)((char*)s.e - (char*)s.b) & 0xfffffffeu) > 2))
    FUN_00f47380(s.b);
}

// @ 0x00f28680
int fn28680(void* ser, const char* name, int flag) {
  if (flag == 0) return 1;
  String16 src;
  WStr w;
  buildName(name, &src, &w);
  freeString16(src);
  int r = FUN_00f26770(ser, (w.b != w.e) ? w.b : 0, flag, L"cScenarioGoal");
  freeWStr(w);
  return r;
}

// @ 0x00f28780
int fn28780(void* ser, const char* name, int flag) {
  if (flag == 0) return 1;
  String16 src;
  WStr w;
  buildName(name, &src, &w);
  freeString16(src);
  int r = FUN_00f26810(ser, (w.b != w.e) ? w.b : 0, flag, L"cScenarioClassAct");
  freeWStr(w);
  return r;
}

// @ 0x00f28880
int fn28880(ISer* ser, const char* name, TextObj* obj) {
  if (obj != 0) {
    bool empty;
    if (obj->id28 == 0 || obj->id24 == 0) {
      empty = (obj->ws.b == obj->ws.e);
    } else {
      const wchar_t* p = obj->cs.GetText();
      empty = (p[0] == 0);
    }
    if (!empty) {
      String16 src;
      WStr w;
      buildName(name, &src, &w);
      freeString16(src);
      if (w.b != w.e) ser->s0(w.b);
      const wchar_t* val =
          (obj->id28 != 0 && obj->id24 != 0) ? obj->cs.GetText() : obj->ws.b;
      ser->s3(val);
      if (w.b != w.e) ser->s1(w.b);
      freeWStr(w);
    }
  }
  return 1;
}

// @ 0x00f289d0
int fn289d0(ISer* ser, const char* name, ObjD* q) {
  if (q != 0) {
    TextObj* obj = &q->t;
    bool empty;
    if (obj->id28 == 0 || obj->id24 == 0) {
      empty = (obj->ws.b == obj->ws.e);
    } else {
      const wchar_t* p = obj->cs.GetText();
      empty = (p[0] == 0);
    }
    if (!empty) {
      String16 src;
      WStr w;
      buildName(name, &src, &w);
      freeString16(src);
      if (w.b != w.e) ser->s0(w.b);
      ser->s0(L"cScenarioDialog");
      fn28880(ser, "text", obj);
      ser->s1(L"cScenarioDialog");
      if (w.b != w.e) ser->s1(w.b);
      freeWStr(w);
    }
  }
  return 1;
}

// ---------------------------------------------------------------------------
// Large object holding a cString view at +0x2788.

struct BigObj {
  char _pad[0x2788];
  TextObj txt;          // +0x2788
  int fn28b80(WStr* out);
};

// @ 0x00f28b80
int BigObj::fn28b80(WStr* out) {
  TextObj* obj = &txt;
  bool empty;
  if (obj->id28 == 0 || obj->id24 == 0) {
    empty = (obj->ws.b == obj->ws.e);
  } else {
    const wchar_t* p = obj->cs.GetText();
    empty = (p[0] == 0);
  }
  if (!empty) {
    const wchar_t* s =
        (obj->id28 != 0 && obj->id24 != 0) ? obj->cs.GetText() : obj->ws.b;
    const wchar_t* e = s;
    while (*e != 0) ++e;
    out->assign(s, e);
    return 1;
  }
  return FUN_00eeea50(this, out);
}

// @ 0x00f28c50
int TextObj::fn28c50(void* stream) {
  ListSer ser;
  ser.ctor(this, &g_015aff90, 0x1a80d26);
  if (!ser.Read(stream)) return 0;
  if (id24 != 0 && id28 != 0) {
    CS tmp;
    tmp.ctor(id24, id28, 0);
    cs = tmp;
    tmp.dtor();
    ws.append((const wchar_t*)0x13ec468);
  }
  return 1;
}

// ---------------------------------------------------------------------------
// Raw container helpers.

// @ 0x00f28ce0
void fn28ce0(ISer* ser, int* vec) {
  char* end = (char*)vec[1];
  char* pos;
  if ((uint)vec[5] < 0x3fffffff) pos = (char*)vec[0] + vec[5] * 0x238;
  else pos = end;

  uint count = (uint)FUN_00ef1990(pos, end);
  IOut* out = ser->s8();
  void* io = out->o6();
  FUN_0093aa70(io, &count, 1, 0);

  char* p;
  if ((uint)vec[5] < 0x3fffffff) p = (char*)vec[0] + vec[5] * 0x238;
  else p = end;

  while (p != end) {
    ListSer buf;
    buf.ctor(p + 4, &g_015aefd0, 0x1a80d26);
    buf.Serialize(ser);
    for (;;) {
      uint u = *(uint*)p;
      p += 0x238;
      if ((u >> 0x1e) & 1) break;
      if (*(int*)p >= 0) break;
    }
  }
  ser->s7();
}

// 0x38-byte element (14 dwords).
struct E38 { int w[14]; };

struct Vec38 {
  E38* b; E38* e; E38* c;
  E38* erase(E38* first, E38* last);
  void insert(char* pos, uint count, char* value);
  void insertOne(char* pos, char* value);
};

// @ 0x00f28dd0  eastl::vector<SP::cBuildingData,eastl::sp_vector_allocator>::erase
E38* Vec38::erase(E38* first, E38* last) {
  E38* stop = e;
  E38* d = first;
  for (E38* s = last; s != stop; ++s) { *d = *s; ++d; }
  e = stop - (last - first);
  return first;
}

// @ 0x00f28e40
void Vec38::insert(char* pos, uint count, char* value) {
  uint spare = (uint)(((char*)c - (char*)e) / 0x38);
  if (spare < count) {
    uint used = (uint)(((char*)e - (char*)b) / 0x38);
    uint cap = used * 2;
    if (used == 0) cap = 1;
    uint want = used + count;
    if (want < cap) want = cap;
    E38* buf;
    if (want == 0) buf = 0;
    else buf = (E38*)FUN_00f473a0(want * 0x38, "Simulator", 0, 0,
                                  (const char*)0x13ebb38, 0xd1);
    E38* p = (E38*)FUN_00f25ea0(b, pos, buf);
    FUN_00f28040(p, count, value);
    E38* p2 = (E38*)FUN_00f25ea0(pos, e, p + count);
    if (b != 0 && *(int*)((char*)b - 4) != 0) FUN_00f47380(b);
    b = buf; e = p2; c = buf + want;
  } else if (count != 0) {
    E38 tmp = *(E38*)value;
    E38 tmp2;
    E38* stop = e;
    uint after = (uint)(((char*)stop - pos) / 0x38);
    if (count < after) {
      E38* mid = (E38*)((char*)stop - count * 0x38);
      FUN_00dfa3c0(&tmp, mid, stop, stop, pos);
      e = (E38*)((char*)e + count * 0x38);
      FUN_00f28350(pos, mid, stop);
      FUN_00f27400(pos, (char*)pos + count * 0x38, &tmp);
    } else {
      uint rem = count - after;
      FUN_00f28040(stop, rem, &tmp);
      e = (E38*)((char*)e + rem * 0x38);
      FUN_00dfa3c0(&tmp2, pos, stop, e, pos);
      e = (E38*)((char*)e + after * 0x38);
      FUN_00f27400(pos, stop, &tmp);
    }
  }
}

// @ 0x00f29030
void Vec38::insertOne(char* pos, char* value) {
  E38* stop = e;
  if (stop != c) {
    if (pos <= value && value < (char*)stop) value += 0x38;
    if (stop != 0) *stop = *(E38*)((char*)stop - 0x38);
    E38* p = stop;
    for (;;) {
      *p = *(E38*)((char*)p - 0x38);
      if ((char*)p - 0x38 == pos) break;
      p = (E38*)((char*)p - 0x38);
    }
    *(E38*)pos = *(E38*)value;
    e = (E38*)((char*)e + 0x38);
    return;
  }
  uint used = (uint)(((char*)e - (char*)b) / 0x38);
  uint want;
  if (used == 0) want = 1;
  else { want = used * 2; if (want == 0) want = 0; }
  E38* buf;
  if (want == 0) buf = 0;
  else buf = (E38*)FUN_00f473a0(want * 0x38, "Simulator", 0, 0,
                                (const char*)0x13ebb38, 0xd1);
  E38* p = (E38*)FUN_00f25ea0(b, pos, buf);
  if (p != 0) *p = *(E38*)value;
  E38* p2 = (E38*)FUN_00f25ea0(pos, e, p + 1);
  if (b != 0 && *(int*)((char*)b - 4) != 0) FUN_00f47380(b);
  e = p2;
  b = buf;
  c = buf + want;
}

// 0x18-byte element (6 dwords).
struct E18 { int w[6]; };

struct Vec18 {
  E18* b; E18* e; E18* c;
  void DoInsertSlow(char* pos, char* value);
};

// @ 0x00f29170
void Vec18::DoInsertSlow(char* pos, char* value) {
  E18* stop = e;
  if (stop != c) {
    if (pos <= value && value < (char*)stop) value += 0x18;
    if (stop != 0) *stop = *(E18*)((char*)stop - 0x18);
    FUN_00cc8b50(pos, (char*)e - 0x18, e);
    *(E18*)pos = *(E18*)value;
    e = (E18*)((char*)e + 0x18);
    return;
  }
  uint used = (uint)(((char*)e - (char*)b) / 0x18);
  uint want;
  if (used == 0) want = 1;
  else { want = used * 2; if (want == 0) want = 0; }
  E18* buf;
  if (want == 0) buf = 0;
  else buf = (E18*)FUN_00f473a0(want * 0x18, "Simulator", 0, 0,
                                (const char*)0x13ebb38, 0xd1);
  E18* p = (E18*)FUN_00720200(b, pos, buf);
  if (p != 0) *p = *(E18*)value;
  E18* p2 = (E18*)FUN_00720200(pos, e, p + 1);
  if (b != 0) FUN_00f47380(b);
  b = buf;
  e = p2;
  c = buf + want;
}

// 0x34-byte element: 7 floats, a vector<cSPVector3>, padding, one dword.
struct E34 {
  float f00, f04, f08, f0c, f10, f14, f18;
  Vec3 v;
  char pad[8];
  int f30;
};

// @ 0x00f292c0
void fn292c0(E34* dst, int n, E34* src) {
  if ((uint)n <= 0) return;
  E34* d = dst;
  do {
    if (d != 0) {
      d->f00 = src->f00; d->f04 = src->f04; d->f08 = src->f08; d->f0c = src->f0c;
      d->f10 = src->f10; d->f14 = src->f14; d->f18 = src->f18;
      d->v.ctor(src->v);
      d->f30 = src->f30;
    }
    --n;
    d = (E34*)((char*)d + 0x34);
  } while ((uint)n > 0);
}

// @ 0x00f29330
E34* fn29330(E34* first, E34* last, E34* out) {
  if (first == last) return out;
  E34* s = first;
  E34* d = out;
  do {
    if (d != 0) {
      d->f00 = s->f00; d->f04 = s->f04; d->f08 = s->f08; d->f0c = s->f0c;
      d->f10 = s->f10; d->f14 = s->f14; d->f18 = s->f18;
      d->v.ctor(s->v);
      d->f30 = s->f30;
    }
    s = (E34*)((char*)s + 0x34);
    d = (E34*)((char*)d + 0x34);
  } while (s != last);
  return d;
}

// 0x44-byte element (ObjD plus trailing space).
struct E44 {
  ObjD d;               // 0x30
  char pad[0x14];
};

// @ 0x00f29410
int fn29410(ISer* ser, const char* name, int* list) {
  char* begin = (char*)list[0];
  char* end = (char*)list[1];
  char flag = 1;
  if (begin != end) {
    String16 src;
    WStr w;
    buildName(name, &src, &w);
    freeString16(src);
    if (w.b != w.e) ser->s0(w.b);
    else ser->s0(L"list");
    char* tailEnd = (char*)list[1];
    for (char* p = (char*)list[0]; p != tailEnd; p += 0x44) {
      if (flag != 0) {
        if (fn289d0(ser, 0, (ObjD*)p)) flag = 1;
        else flag = 0;
      }
    }
    if (w.b != w.e) ser->s1(w.b);
    else ser->s1(L"list");
    freeWStr(w);
  }
  return flag;
}