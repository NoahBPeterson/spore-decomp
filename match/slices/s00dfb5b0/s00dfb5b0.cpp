// Slice s00dfb5b0 (batch bfs0, slice 30). Region 0xdfb5b0-0xdfc5ad.
// EASTL container helpers (vectors of 0x24/0x34/0x38/0x44-byte elements), a large UI
// class constructor/destructor and update methods. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------------------
// External callees (bodies elsewhere; references are masked relocations).
// ----------------------------------------------------------------------------------------
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     const char* file, int line);        // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                                // 0xf47380
extern "C" void  __cdecl MemThunk(void* dst, const void* src, uint32_t n); // 0x11e0744

extern "C" void  __cdecl FUN_00e00630();
extern "C" void  __cdecl FUN_00810000(void*);
extern "C" void  __cdecl FUN_0093a560(void*, int, int);
extern "C" void  __cdecl FUN_00f257b0(void*);
extern "C" void  __cdecl FUN_00811fe0(void*);
extern "C" void* __cdecl FUN_00ef19f0();
extern "C" void  __cdecl FUN_00de4850(void*);
extern "C" void* __cdecl FUN_00401010();
extern "C" void* __cdecl FUN_0067dd20();
extern "C" char  __cdecl FUN_00f56f0(wchar_t c);
extern "C" char  __cdecl FUN_005bf0e0(void* self, void** out);
extern "C" void  __cdecl FUN_005bf3a0(void* self, void* a, void** out, int b);
extern "C" void  __cdecl FUN_00eebf90(void* a, void* b);
extern "C" char  __cdecl FUN_006419f0(void* self);
extern "C" uint32_t __cdecl FUN_00eecba0(void* self);
extern "C" void  __cdecl FUN_00646370(void*, void*, void*, void*, uint32_t, int);
extern "C" void  __cdecl FUN_00dfa370();
extern "C" void  __cdecl FUN_00dfa790(int);
extern "C" void  __cdecl FUN_00df9fc0();
extern "C" char  __cdecl FUN_00de46e0();
extern "C" void  __cdecl FUN_00de7010(void*);
extern "C" void  __cdecl FUN_00ddb760();
extern "C" void  __cdecl FUN_00dfab20(int);
extern "C" void* __cdecl Vec38_AllocCopy(void* self, int n, void* first, void* last); // 0xdfb1b0
extern "C" void  __cdecl Vec38_Copy(void* first, void* last, void* dest);             // 0xdfb210
extern "C" void* __cdecl CopyRangeB(void* first, void* last, void* dest);             // 0xdfc170
extern "C" void* __cdecl UninitCopyD(void* out, const void* first, const void* last, void* dest); // 0xdfb8e0
extern "C" void* __cdecl UninitCopyA(void* out, const void* first, const void* last, void* dest);
extern "C" void  __cdecl FUN_0050f740(void* a, void* b, void* c);
extern "C" void  __cdecl VecInsertKey(void* self, void* pos, void* val);
struct SubVec38 {                                  // 12-byte eastl vector at TypeB+0x1c
  uint32_t b, e, c;
  void assign_00473460(const void* src);           // 0x473460 (thiscall, 1 arg)
  void assign_00473500(const void* src);           // 0x473500 (thiscall, 1 arg)
};
extern "C" void  __cdecl FUN_00473460(void* dst, const void* src);   // 0x473460 (cdecl form)
extern "C" void  __cdecl FUN_00473500(void* dst, const void* src);   // 0x473500 (cdecl form)
struct Swarm {                                     // global swarm container (0xdd9190)
  int  GetLinkCount(int id);                       // 0xdda060
  char IsReady();                                  // 0xdd91a0
};
extern "C" Swarm* __cdecl FUN_00dd9190();          // 0xdd9190

extern wchar_t gEmptyA_1667bac;   // 0x1667bac
extern wchar_t gEmptyB_1667bae;   // 0x1667bae

static inline void** Vt(void* p) { return *(void***)p; }

// ----------------------------------------------------------------------------------------
// Element / helper types.
// ----------------------------------------------------------------------------------------
struct WString {                    // eastl::basic_string<wchar_t,eastl::allocator> (12 bytes)
  wchar_t* begin;                   // +0x00
  wchar_t* end;                     // +0x04
  wchar_t* cap;                     // +0x08
  void AllocateSelf(int n);                       // 0x429760
  void Assign(const wchar_t* b, const wchar_t* e); // 0x423650
  void push_back(wchar_t c);                      // 0x4f6510
  void RangeInitialize(const wchar_t* s);         // 0x579a90
};

struct CString {                    // SP::cString (0x14 bytes)
  uint32_t a0, a4, a8, ac, b0;
  void CStrCtor(const CString* src);   // 0x6b56f0
  CString* Assign(const CString* src); // 0x6b5430
};

struct TypeC {                      // 0x38 bytes
  CString  cs;       // +0x00
  WString  s1;       // +0x14
  uint32_t pad20;    // +0x20
  uint32_t f24;      // +0x24
  uint32_t f28;      // +0x28
  WString  s2;       // +0x2c
  TypeC* CopyCtor(const TypeC* src);   // 0xdfb280
  void   dtor_f280f0();                // 0xf280f0 (out of line)
};

struct TypeD {                      // 0x44 bytes
  uint32_t f0;       // +0x00
  TypeC    c;        // +0x04
  uint32_t pad3c;    // +0x3c
  uint32_t f40;      // +0x40
  TypeD* CopyCtor(const TypeD* src);   // element copy (inline TypeC + fields)
  void   Dtor();                        // element dtor
};

struct TypeA {                      // 0x24 bytes
  float    f0;       // +0x00
  uint32_t f4;       // +0x04
  uint32_t f8;       // +0x08
  uint8_t  fC;       // +0x0c
  uint8_t  pad[3];   // +0x0d
  WString  s;        // +0x10
  uint32_t f20;      // +0x20
  TypeA* CopyCtor(const TypeA* src);   // 0xdfb130
  void   Dtor();                        // element string dtor
};

struct TypeB {                      // 0x34 bytes
  float    f0;       // +0x00
  uint32_t f4, f8, fC, f10, f14, f18;  // +0x04..+0x1c
  SubVec38 v1c;                        // +0x1c eastl::vector (12 bytes)
  uint32_t pad28, pad2c;               // +0x28
  uint32_t f30;                        // +0x30
  TypeB* CopyCtorA(const TypeB* src);  // 0xdfb890
  TypeB* CopyCtorB(const TypeB* src);  // 0xdfbd00
};

struct Vec38 {                       // 0x38-byte element vector (12-byte header)
  uint32_t b, e, c;
  Vec38* Assign(const Vec38& x);      // 0xdfb720
};

struct VecA {                        // 0x24-byte element vector
  uint32_t b, e, c;
  void Insert(TypeA* position, const TypeA* value);  // 0xdfc000
};

// The large UI class (size > 0x174). Field access is offset based.
struct Big {
  void Init();          // 0xdfb9c0
  void Destroy();       // 0xdfbac0
  void DestroyVec18();  // 0xdfbb60
  void Update();        // 0xdfbd70
  void Update2(int);    // 0xdfc240
  char Check();         // 0xdfc500
  void sub_dfa370();    // 0xdfa370 (thiscall)
  void sub_df9fc0();    // 0xdf9fc0 (thiscall)
  void sub_dfa790(int); // 0xdfa790 (thiscall, 1 arg)
};

struct B3Obj {                     // object returned by 0x00b3d360
  char   pad[0x20];
  void*  head;                     // +0x20 (self-referential while empty)
  char   sub_de46e0();             // 0xde46e0 (thiscall)
};
struct Obj3c   { void sub_de7010(); };          // 0xde7010 (thiscall) on g_16a1344 + 0x3c
struct Ec43    { char sub_ec4320(); };          // 0xec4320 (thiscall)
struct Svc410  { void sub_e3e350(int, void*, int); };  // 0xe3e350 (thiscall, 3 args)
struct Stopwatch { long long sub_0093a3a0(); };        // 0x93a3a0 (thiscall, __int64 result)

extern "C" B3Obj*  __cdecl FUN_00b3d360();
extern "C" Svc410* __cdecl FUN_00b3d410();
extern "C" char*   g_16a1344;      // 0x16a1344
extern "C" char*   g_16c7aa4;      // 0x16c7aa4

// 0x38-byte render description handed to vtable slot 5 of the object at +0x84.
struct Vec3g { float x, y, z; };
struct Mat3g {                        // 0x24 bytes (cSPMatrix3)
  float m[9];
  void CopyCtor_0041cb40(const Mat3g* src);   // 0x41cb40 (thiscall, 1 arg)
};
struct Desc38 {
  int16_t kind;                       // +0x00
  int16_t sub;                        // +0x02
  Vec3g   pos;                        // +0x04
  float   scale;                      // +0x10
  Mat3g   mat;                        // +0x14
};
extern "C" Vec3g g_vec_16a173c;       // 0x16a173c
extern "C" float g_scale_1485720;     // 0x1485720
extern "C" float g_depth_147eeac;     // 0x147eeac
extern "C" Mat3g g_mat_16a1718;       // 0x16a1718

// Larger class whose destructor appears at 0xdfbba0.
struct Huge {
  void Destroy();       // 0xdfbba0
};

// ----------------------------------------------------------------------------------------
// @ 0x00dfb5b0  build a display label from the current state name.
// ----------------------------------------------------------------------------------------
void* __fastcall FUN_00dfb5b0(int state_obj) {
  const wchar_t* names[12];
  names[0]  = L"Neutral";
  names[1]  = L"SelectingScenarioForPlay";
  names[2]  = L"SelectingAvatarForPlay";
  names[3]  = L"NamingAvatar";
  names[4]  = L"SelectingPosse";
  names[5]  = L"SelectingTerrainForEdit";
  names[6]  = L"SelectingAvatarForEdit";
  names[7]  = L"SelectingScenarioForEdit";
  names[8]  = L"WaitingForAutoPollinate";
  names[9]  = L"ReadyToLaunchScenarioForEdit";
  names[10] = L"ReadyToLaunchScenarioForPlay";
  names[11] = L"DoingModeSelectZoomIn";

  WString result;
  result.begin = &gEmptyA_1667bac;
  result.end   = &gEmptyA_1667bac;
  result.cap   = &gEmptyB_1667bae;
  const wchar_t* n = names[*(int*)(state_obj + 0x20)];
  result.RangeInitialize(n);
  return &result;
}

// @ 0x00dfb720  eastl::vector<0x38-byte>::operator=(const vector&)
Vec38* Vec38::Assign(const Vec38& x) {
  if (this != &x) {
    uint32_t n = (uint32_t)((x.e - x.b) / 0x38);
    if ((uint32_t)((c - b) / 0x38) < n) {
      void* nb = Vec38_AllocCopy(this, (int)n, (void*)x.b, (void*)x.e);
      if (b && *(int*)(b - 4) != 0) EA_Free((void*)b);
      b = (uint32_t)nb;
      c = (uint32_t)((char*)nb + n * 0x38);
    } else {
      uint32_t cur = (uint32_t)((e - b) / 0x38);
      if (cur < n) {
        Vec38_Copy((void*)x.b, (void*)(x.b + cur * 0x38), (void*)b);
        VecInsertKey(this, (void*)(b + cur * 0x38), 0);
      } else {
        Vec38_Copy((void*)x.b, (void*)x.e, (void*)b);
      }
    }
    e = b + n * 0x38;
  }
  return this;
}

// @ 0x00dfb890  TypeB copy constructor (sub-vector construct form)
TypeB* TypeB::CopyCtorA(const TypeB* o) {
  *(float*)&f0 = *(const float*)&o->f0;
  *(float*)&f4 = *(const float*)&o->f4;
  *(float*)&f8 = *(const float*)&o->f8;
  *(float*)&fC = *(const float*)&o->fC;
  *(float*)&f10 = *(const float*)&o->f10;
  *(float*)&f14 = *(const float*)&o->f14;
  *(float*)&f18 = *(const float*)&o->f18;
  v1c.assign_00473460(&o->v1c);
  f30 = o->f30;
  return this;
}

// @ 0x00dfb8e0  uninitialized_copy of 0x44-byte TypeD elements
void* UninitCopyD(void* outP, const void* firstP, const void* lastP, void* dest) {
  TypeD** out = (TypeD**)outP;
  const TypeD* first = (const TypeD*)firstP;
  const TypeD* last = (const TypeD*)lastP;
  *out = (TypeD*)dest;
  while (first != last) {
    TypeD* d = *out;
    if (d) { d->f0 = first->f0; d->c.CopyCtor(&first->c); d->f40 = first->f40; }
    *out = (TypeD*)((char*)*out + 0x44);
    first = (const TypeD*)((const char*)first + 0x44);
  }
  return outP;
}

// @ 0x00dfb930  copy-assign a range of TypeD elements
TypeD* CopyAssignD(TypeD* first, TypeD* last, TypeD* dest) {
  if (first != last) {
    do {
      dest->f0 = first->f0;
      dest->c.cs.Assign(&first->c.cs);
      if (&dest->c.s1 != &first->c.s1)
        dest->c.s1.Assign(first->c.s1.begin, first->c.s1.end);
      dest->c.f24 = first->c.f24;
      dest->c.f28 = first->c.f28;
      if (&dest->c.s2 != &first->c.s2)
        dest->c.s2.Assign(first->c.s2.begin, first->c.s2.end);
      dest->f40 = first->f40;
      first = (TypeD*)((char*)first + 0x44);
      dest  = (TypeD*)((char*)dest + 0x44);
    } while (first != last);
  }
  return dest;
}

// @ 0x00dfb9c0  Big::Init
void Big::Init() {
  char* self = (char*)this;
  FUN_00e00630();
  *(void**)(self + 0x08) = (void*)0x140b5a0;
  *(wchar_t**)(self + 0x38) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x3c) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x40) = &gEmptyB_1667bae;
  *(void**)self = (void*)0x147ee50;
  *(void**)(self + 0x08) = (void*)0x147ee4c;
  for (int i = 3; i <= 5; ++i)  *(uint32_t*)(self + i*4) = 0;   // 0x0c..0x14
  *(uint32_t*)(self + 0x20) = 0;
  *(uint32_t*)(self + 0x28) = 0;
  *(uint32_t*)(self + 0x30) = 0;
  *(uint32_t*)(self + 0x34) = 0;
  FUN_00810000(self + 0x48);
  FUN_0093a560(self + 0x60, 0, 0);
  *(uint8_t*)(self + 0x7e) = 0;
  *(uint8_t*)(self + 0x7f) = 0;
  *(uint8_t*)(self + 0x80) = 0;
  for (int i = 0; i < 14; ++i) *(uint32_t*)(self + 0x84 + i*4) = 0;
  for (int i = 2; i >= 0; --i) FUN_00f257b0(self + 0xc0 + i*0x38);
  *(wchar_t**)(self + 0x168) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x16c) = &gEmptyA_1667bac;
  *(wchar_t**)(self + 0x170) = &gEmptyB_1667bae;
}

// @ 0x00dfbac0  Big::Destroy
void Big::Destroy() {
  char* self = (char*)this;
  wchar_t* p = *(wchar_t**)(self + 0x168);
  if ((int)((char*)*(wchar_t**)(self + 0x170) - (char*)p) > 2 && p) EA_Free(p);
  void* q = *(void**)(self + 0x88);
  if (q) ((void(__thiscall*)(void*))Vt(q)[1])(q);
  q = *(void**)(self + 0x84);
  if (q) ((void(__thiscall*)(void*))Vt(q)[1])(q);
  FUN_00811fe0(self + 0x48);
  {
    wchar_t* a = *(wchar_t**)(self + 0x38);
    if ((int)((char*)*(wchar_t**)(self + 0x40) - (char*)a) > 2 && a) EA_Free(a);
  }
  {
    TypeA* b0 = *(TypeA**)(self + 0x0c);
    TypeA* e0 = *(TypeA**)(self + 0x10);
    for (TypeA* t = b0; t < e0; ++t) t->Dtor();

    if (b0 && *(int*)((char*)b0 - 4) != 0) EA_Free(b0);
  }
  *(void**)self = (void*)0x147dba8;
}

// @ 0x00dfbb60  Big::DestroyVec18
void Big::DestroyVec18() {
  char* self = (char*)this;
  char* b = *(char**)(self + 0x18);
  char* e = *(char**)(self + 0x1c);
  for (char* p = b; p < e; p += 0x44) ((TypeC*)(p + 4))->dtor_f280f0();
  b = *(char**)(self + 0x18);
  if (b && *(int*)(b - 4) != 0) EA_Free(b);
}

// destroy an eastl vector of 0x44-byte elements (TypeC at +4)
static void DestroyVec44(char* v) {
  char* e = *(char**)(v + 4);
  char* b = *(char**)(v);
  for (char* q = b; q < e; q += 0x44) ((TypeC*)(q + 4))->dtor_f280f0();
  b = *(char**)(v);
  if (b && *(int*)(b - 4) != 0) EA_Free(b);
}

// @ 0x00dfbba0  Huge::Destroy
void Huge::Destroy() {
  char* self = (char*)this;
  void* p = *(void**)(self + 0x4cc);
  if (p && *(int*)((char*)p - 4) != 0) EA_Free(p);
  ((TypeC*)(self + 0x448))->dtor_f280f0();
  DestroyVec44(self + 0x2dc);
  DestroyVec44(self + 0x170);
  DestroyVec44(self + 0x04);
}

// @ 0x00dfbc80  uninitialized_copy of 0x34-byte TypeB elements
// @ 0x00dfbc80  uninitialized_copy of 0x34-byte TypeB elements
void* UninitCopyB(void* out, const void* first, const void* last, void* dest) {
  TypeB* d = (TypeB*)dest;
  TypeB* f = (TypeB*)first;
  TypeB* l = (TypeB*)last;
  for (; f != l; ++f) {
    if (d) d->CopyCtorA(f);
    d = (TypeB*)((char*)d + 0x34);
  }
  return out;
}

// @ 0x00dfbd00  TypeB copy constructor (sub-vector assignment form)
TypeB* TypeB::CopyCtorB(const TypeB* o) {
  f0 = o->f0; f4 = o->f4; f8 = o->f8; fC = o->fC; f10 = o->f10; f14 = o->f14; f18 = o->f18;
  v1c.assign_00473500(&o->v1c);
  f30 = o->f30;
  return this;
}

// @ 0x00dfbd70  Big::Update
void Big::Update() {
  char* self = (char*)this;
  uint32_t* out = (uint32_t*)FUN_00ef19f0();
  if (*(uint32_t*)(self + 0x20) == 9) {
    out[0] = *(uint32_t*)(self + 0x8c);
    out[1] = *(uint32_t*)(self + 0x90);
    out[2] = *(uint32_t*)(self + 0x94);
    out[3] = *(uint32_t*)(self + 0xb0);
    out[4] = *(uint32_t*)(self + 0xb4);
    out[5] = *(uint32_t*)(self + 0xb8);
    out[9] = 1;
    out[10] = 0;
    FUN_00de4850(*(void**)self);
  } else {
    FUN_00de4850(*(void**)self);
    out[0] = *(uint32_t*)(self + 0x8c);
    out[1] = *(uint32_t*)(self + 0x90);
    out[2] = *(uint32_t*)(self + 0x94);
    out[9] = 2;
    out[10] = 1;
    FUN_0050f740(out + 0xc, (void*)out[0xc], (void*)out[0xd]);
    uint32_t cnt = *(uint32_t*)(self + 0x30);
    for (uint32_t i = 0; i < cnt; ++i) {
      char* e = self + 0xc0 + i * 0x38;
      if (*(uint8_t*)(e + 0x20) == 0) {
        uint32_t* dst = (uint32_t*)out[0xd];
        if (dst < (uint32_t*)out[0xe]) {
          out[0xd] = (uint32_t)(dst + 3);
          if (dst) { dst[0] = *(uint32_t*)e; dst[1] = *(uint32_t*)(e+4); dst[2] = *(uint32_t*)(e+8); }
        } else {
          VecInsertKey(out + 0xc, dst, e);
        }
      }
    }
    if (*(uint8_t*)(self + 0x7c)) {
      char* q = self + 0xa4;
      if (FUN_00eecba0(q) != 0x4178b8e8)
        FUN_00646370(q, q + 4, q + 8, q, 0x4178b8e8, 1);
      void* tmp = 0;
      if (!FUN_005bf0e0(q, &tmp)) {
        if (tmp) { ((void(__thiscall*)(void*))Vt(tmp)[1])(tmp); tmp = 0; }
        FUN_005bf3a0(q, (void*)0x15a44c0, &tmp, 0);
        FUN_00eebf90(tmp, self + 0x168);
      }
      if (FUN_006419f0(q)) {
        void* ms = FUN_0067dd20();
        ((void(__thiscall*)(void*, uint32_t, void*, int))Vt(ms)[5])(ms, 0x73e46f6, q, 0);
      }
      if (tmp) ((void(__thiscall*)(void*))Vt(tmp)[1])(tmp);
    }
    out[6] = *(uint32_t*)(self + 0xa4);
    out[7] = *(uint32_t*)(self + 0xa8);
    out[8] = *(uint32_t*)(self + 0xac);
  }
  *(uint32_t*)(self + 0x20) = 0;
  void* r = *(void**)(self + 0x84);
  if (r) {
    ((void(__thiscall*)(void*, int))Vt(r)[3])(r, 1);
    r = *(void**)(self + 0x84);
    if (r) { *(void**)(self + 0x84) = 0; ((void(__thiscall*)(void*))Vt(r)[1])(r); }
  }
  FUN_00dfab20(0);
  r = *(void**)(self + 0x88);
  if (r) {
    ((void(__thiscall*)(void*, int))Vt(r)[3])(r, 1);
    r = *(void**)(self + 0x88);
    if (r) { *(void**)(self + 0x88) = 0; ((void(__thiscall*)(void*))Vt(r)[1])(r); }
  }
  FUN_00dd9190();
  FUN_00ddb760();
  void* w = FUN_0067dd20();
  ((void(__thiscall*)(void*, uint32_t))Vt(w)[10])(w, 0x21851ebe);
}

// @ 0x00dfc000  eastl::vector<TypeA>::DoInsertValue(position, value)
void VecA::Insert(TypeA* position, const TypeA* value) {
  char* s = (char*)this;
  uint32_t end = *(uint32_t*)(s + 4);
  const TypeA* val = value;
  if (end != *(uint32_t*)(s + 8)) {
    if ((uint32_t)val >= (uint32_t)position && (uint32_t)val < end)
      val = (TypeA*)((char*)val + 0x24);
    if (end) ((TypeA*)end)->CopyCtor((TypeA*)(end - 0x24));
    // copy_backward of [begin, end-0x24) into (position, end)
    char* src = (char*)end - 0x24;
    char* dst = (char*)end;
    while (src > (char*)position) {
      src -= 0x24; dst -= 0x24;
      ((TypeA*)dst)->CopyCtor((TypeA*)src);
      ((TypeA*)src)->Dtor();
    }
    position->f0 = val->f0; position->f4 = val->f4; position->f8 = val->f8;
    position->fC = val->fC;
    if (&position->s != &val->s) position->s.Assign(val->s.begin, val->s.end);
    position->f20 = val->f20;
    *(uint32_t*)(s + 4) = end + 0x24;
    return;
  }
  int n = (int)(((char*)end - *(char**)s) / 0x24);
  int cap = (n == 0) ? 1 : n * 2;
  void* buf = 0;
  if (cap != 0)
    buf = EA_Allocate(cap * 0x24, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  char* oldb = *(char**)s;
  char* o = (char*)buf;
  for (char* p = oldb; p != (char*)end; p += 0x24) {
    if (p == (char*)position) { ((TypeA*)o)->CopyCtor(val); }
    else ((TypeA*)o)->CopyCtor((TypeA*)p);
    o += 0x24;
  }
  if (position == (TypeA*)end) ((TypeA*)o)->CopyCtor(val);
  if (oldb && *(int*)(oldb - 4) != 0) EA_Free(oldb);
  *(void**)s = buf;
  *(void**)(s + 4) = (char*)buf + (n + 1) * 0x24;
  *(void**)(s + 8) = (char*)buf + cap * 0x24;
}

// @ 0x00dfc170  copy range of 0x34-byte TypeB elements (assignment form)
void* CopyRangeB(void* first, void* last, void* dest) {
  while (first != last) {
    *(float*)dest = *(float*)first;
    ((uint32_t*)dest)[1] = ((uint32_t*)first)[1];
    ((uint32_t*)dest)[2] = ((uint32_t*)first)[2];
    ((uint32_t*)dest)[3] = ((uint32_t*)first)[3];
    ((uint32_t*)dest)[4] = ((uint32_t*)first)[4];
    ((uint32_t*)dest)[5] = ((uint32_t*)first)[5];
    ((uint32_t*)dest)[6] = ((uint32_t*)first)[6];
    FUN_00473500((char*)dest + 0x1c, (char*)first + 0x1c);
    ((uint32_t*)dest)[0xc] = ((uint32_t*)first)[0xc];
    first = (char*)first + 0x34;
    dest  = (char*)dest + 0x34;
  }
  return dest;
}

// @ 0x00dfc1e0  allocate an array of n TypeD elements and uninitialized-copy into it
void* __stdcall AllocCopyD(int n, void* first, void* last) {
  void* buf = n ? EA_Allocate(n * 0x44, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
  // retail also pushes the element count as a fifth (unused) stack slot; our 4-arg
  // call leaves the same observable state
  UninitCopyD((void**)&n, first, last, buf);
  return buf;
}

// @ 0x00dfc240  Big::Update2(int)
void Big::Update2(int arg) {
  char* self = (char*)this;
  (void)arg;
  if (*(uint32_t*)(self + 0x20) == 0) {
    if (!FUN_00dd9190()->GetLinkCount(0)) sub_dfa370();
  }
  if (*(uint8_t*)(self + 0x7e)) { sub_df9fc0(); *(uint8_t*)(self + 0x7e) = 0; }
  if (*(uint32_t*)(self + 0x20) != 0xb) {
    void* obj84 = *(void**)(self + 0x84);
    if (obj84) {
      Desc38 d;
      Vec3g pos;
      pos = g_vec_16a173c;                   // defaults (overwritten below)
      d.pos = pos;
      d.scale = g_scale_1485720;
      d.mat.CopyCtor_0041cb40(&g_mat_16a1718);
      d.kind = 4;
      d.sub = 1;
      pos.x = 0.0f;
      pos.y = 0.0f;
      pos.z = g_depth_147eeac;
      d.pos = pos;
      d.scale = g_scale_1485720;
      d.mat = g_mat_16a1718;
      ((void(__thiscall*)(void*, Desc38*))Vt(obj84)[5])(obj84, &d);
    }
    if (*(uint8_t*)(self + 0x80) == 0) {
      uint32_t e = *(uint32_t*)(self + 0x28);
      if (e) { *(uint32_t*)(self + 0x28) = e - 1; return; }
      uint32_t st = *(uint32_t*)(self + 0x20);
      if (st == 10 || st == 9) { Update(); return; }
      if (FUN_00b3d360()->sub_de46e0()) { ((Obj3c*)(g_16a1344 + 0x3c))->sub_de7010(); return; }
    } else {
      if (*(uint32_t*)(self + 0x78) == 0) {
        double t = (double)((Stopwatch*)(self + 0x60))->sub_0093a3a0();
        if (t * *(float*)(self + 0x74) > 0.5f) {
          sub_dfa790(1);
          *(uint32_t*)(self + 0x78) = 1;
        }
      }
      if (*(uint32_t*)(self + 0x78) == 1) {
        B3Obj* g = FUN_00b3d360();
        int empty = ((int)g->head == (int)&g->head);
        void* w = FUN_00401010();
        int v = ((int(__thiscall*)(void*))Vt(w)[10])(w);
        char busy = ((Ec43*)(*(char**)(g_16c7aa4 + 0x1c)))->sub_ec4320();
        if (!busy && v < 1 && empty) *(uint32_t*)(self + 0x78) = 2;
      }
      if (*(uint32_t*)(self + 0x78) == 2) {
        if (FUN_00dd9190()->IsReady()) {
          *(uint8_t*)(self + 0x80) = 0;
          *(uint32_t*)(self + 0x28) = 10;
          void* r = *(void**)(self + 0x84);
          if (r) {
            ((void(__thiscall*)(void*, int))Vt(r)[3])(r, 1);
            r = *(void**)(self + 0x84);
            if (r) { *(void**)(self + 0x84) = 0; ((void(__thiscall*)(void*))Vt(r)[1])(r); }
          }
          uint32_t* o = (uint32_t*)FUN_00ef19f0();
          o[0] = *(uint32_t*)(self + 0x8c);
          o[1] = *(uint32_t*)(self + 0x90);
          o[2] = *(uint32_t*)(self + 0x94);
          o[6] = *(uint32_t*)(self + 0xa4);
          o[7] = *(uint32_t*)(self + 0xa8);
          o[8] = *(uint32_t*)(self + 0xac);
          FUN_00b3d410()->sub_e3e350(1, (void*)0x1654c10, 1);
          return;
        }
      }
    }
  }
}

// @ 0x00dfc500  Big::Check -- filter the stored string and return true if any char failed
char Big::Check() {
  char* self = (char*)this;
  WString tmp;
  tmp.begin = &gEmptyA_1667bac;
  tmp.end   = &gEmptyA_1667bac;
  tmp.cap   = &gEmptyB_1667bae;
  char res = 0;
  WString* src = (WString*)(self + 0x168);
  int n = (int)((char*)src->end - (char*)src->begin) >> 1;
  if (n != 0) {
    for (int i = 0; i < n; ++i) {
      wchar_t c = src->begin[i];
      if (!FUN_00f56f0(c)) res = 1;
      else tmp.push_back(c);
    }
    if (res && &tmp != src) src->Assign(tmp.begin, tmp.end);
  }
  if ((char*)tmp.cap - (char*)tmp.begin > 2 && tmp.begin) EA_Free(tmp.begin);
  return res;
}

// ----------------------------------------------------------------------------------------
// Element copy / destroy bodies (declared above).
// ----------------------------------------------------------------------------------------
CString* CString::Assign(const CString* src) {
  a0 = src->a0; a4 = src->a4; a8 = src->a8; ac = src->ac; b0 = src->b0;
  return this;
}

static void WStringCopyAssign(WString* d, const WString* s) {
  d->Assign(s->begin, s->end);
}

TypeC* TypeC::CopyCtor(const TypeC* o) {
  cs.CStrCtor(&o->cs);
  int n1 = (int)((char*)o->s1.end - (char*)o->s1.begin) >> 1;
  s1.begin = s1.end = s1.cap = 0;
  s1.AllocateSelf(n1 + 1);
  MemThunk(s1.begin, o->s1.begin, n1 * 2);
  s1.end = (wchar_t*)((char*)s1.begin + n1 * 2);
  *s1.end = 0;
  f24 = o->f24;
  f28 = o->f28;
  int n2 = (int)((char*)o->s2.end - (char*)o->s2.begin) >> 1;
  s2.begin = s2.end = s2.cap = 0;
  s2.AllocateSelf(n2 + 1);
  MemThunk(s2.begin, o->s2.begin, n2 * 2);
  s2.end = (wchar_t*)((char*)s2.begin + n2 * 2);
  *s2.end = 0;
  return this;
}

// TypeC::dtor_f280f0 is out of line (0xf280f0).


TypeA* TypeA::CopyCtor(const TypeA* o) {
  f0 = o->f0; f4 = o->f4; f8 = o->f8; fC = o->fC;
  int n = (int)((char*)o->s.end - (char*)o->s.begin) >> 1;
  s.begin = s.end = s.cap = 0;
  s.AllocateSelf(n + 1);
  MemThunk(s.begin, o->s.begin, n * 2);
  s.end = (wchar_t*)((char*)s.begin + n * 2);
  *s.end = 0;
  f20 = o->f20;
  return this;
}

void TypeA::Dtor() {
  if ((char*)s.cap - (char*)s.begin > 2 && s.begin) EA_Free(s.begin);
}

TypeD* TypeD::CopyCtor(const TypeD* o) {
  f0 = o->f0;
  c.CopyCtor(&o->c);
  f40 = o->f40;
  return this;
}

void TypeD::Dtor() { c.dtor_f280f0(); }

void* UninitCopyA(void* out, const void* first, const void* last, void* dest) {
  TypeA* d = (TypeA*)dest;
  TypeA* f = (TypeA*)first;
  TypeA* l = (TypeA*)last;
  for (; f != l; ++f) {
    if (d) d->CopyCtor(f);
    d = (TypeA*)((char*)d + 0x24);
  }
  return out;
}
