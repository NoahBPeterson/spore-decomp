// match/slices/s00a52080/s00a52080.cpp
// Object file: Eapd acoustics/control/group externals + eastl vector bodies
// (VS2008 SP1).  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
// The "acoustics" family are Max/MSP-style externals: each <name>_new allocates
// a pd object and attaches a float outlet; control/group add voice callbacks.

#include "game/types.h"
#include <math.h>

// ---- EAPD pd API ----
struct t_symbol { const char* s_name; int s_thing; };   // 8 bytes

namespace EA { namespace Audio { namespace Eapd {

void* __cdecl pd_new(void* cls);                                   // 0xa49390
void  __cdecl pd_free(void* obj);                                  // 0xa493d0
void* __cdecl outlet_new(void* obj, t_symbol* s, int a);           // 0xa49d30
void  __cdecl outlet_float(void* out, float f);                    // 0xa49570
void* __cdecl class_new(t_symbol* s, t_symbol* help, void* makefn,
                        void* freefn, int size, int flags, int a1, int a2); // 0xa48e50
void* __cdecl class_new7(t_symbol* s, t_symbol* help, void* makefn,
                         void* freefn, int size, int flags, int a1);        // 0xa48e50 (7-arg)
unsigned char __cdecl class_doaddfloat(void* cls, void* fn);       // 0xa47f30
unsigned char __cdecl class_addbang(void* cls, void* fn);          // 0xa47f10
unsigned char __cdecl class_addsymbol(void* cls, void* fn);        // 0xa47f50
unsigned char __cdecl class_addanything(void* cls, void* fn);      // 0xa47f90
unsigned char __cdecl class_addmethod(void* cls, void* fn, t_symbol* s, int a1); // 0xa48a30/0xa48a80
void  __cdecl class_sethelpsymbol(void* cls, int a, int b);        // 0xa47fc0
t_symbol* __cdecl gensym(t_symbol* out, const char* name);         // 0xa675f0
void* __cdecl canvas_getcurrentinstance();                         // 0xa4a450
void* __cdecl GetVoiceManager();                                   // 0xa67d00

}}}  // namespace

// Voice-manager vtable: +0x14 add, +0x18 (5-arg), +0x1c (4-arg).
struct VoiceManager {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4();
  virtual char Add(int sym, int a, void* out);   // +0x14
  virtual void S18(int o, int a, int b, int c, int d);  // +0x18
  virtual void S19(int o, int a, int b);                // +0x1c
};

// ---- globals ----
extern int   gOutletCount;          // 0x167545c
extern void* spMtofClass;           // 0x167550c
extern void* spFtomClass;           // 0x1675500
extern void* spPowtodbClass;        // 0x1675504
extern void* spRmstodbClass;        // 0x1675510
extern void* spDbtopowClass;        // 0x1675514
extern void* spDbtormsClass;        // 0x1675508
extern void* spControlClass;        // 0x1675518
extern void* spGroupClass;          // 0x1675520
extern void* spGroupsizeClass;      // 0x167551c
extern t_symbol gFloatSymbol;       // 0x16758c4
extern int   gOutletDstA;           // 0x16758c8
extern t_symbol gEmptySymbol;       // 0x167589c
extern int   gEmptyA;               // 0x16758a0
extern float gUnitA; extern float gUnitB;                   // 0x1454f44 / 0x1454f40
extern float gA521;                                 // 0x1454f3c
extern float gA522; extern float gA523;             // 0x1454f38 / 0x13ec4d0
extern float gF521a;                                // 0x1454f4c
extern float gF521b; extern float gF521c;           // 0x1454f48 / 0x1485378
extern float gF523a, gF523b;                        // 0x1454f58 / 0x1454f5c
extern float gF524a, gF524b;                        // 0x1454f60 / 0x1454f64
extern unsigned gF524c;                             // 0x13f4fd0
extern void* gVtblA52b40;                           // 0x1403934

// Helper objects used only by this slice's thiscall helpers.
struct CM_Hash { char pad[0x18]; int v18; int v1c; void* __thiscall GetPair(void* out); };
struct GroupObj { void* p0; int i1; int i2; int i3; };       // +0x18/+0x1c view
struct AnyObj { void* vtbl; void* p4; int p8;
  int  __thiscall Call6(int a, int b);
  void __thiscall Call4(int a);
  void __thiscall CallC(int a);
};
struct IdxVec { const char* begin; const char* end; char* cap; void __thiscall Get(t_symbol* out, unsigned idx); };
struct PairVec { int* begin; int* cur; int* cap; int* alloc;
  void __thiscall Insert(int pos, unsigned n, int* value);
  void __thiscall Resize(unsigned n);
};
struct GroupHelp { int v0, v1, v2, dummy, v10, v14;
  void* __thiscall Init(int b);
};

static __forceinline t_symbol* gensymS(const char* s) {
  t_symbol tmp;
  return EA::Audio::Eapd::gensym(&tmp, s);
}

// outlet list walk shared by every perform body: list head = [obj+0xc]->[8].
static __forceinline void OutletWalk(void* obj, float f) {
  char* e = *(char**)obj;
  ++gOutletCount;
  if (gOutletCount < 0x3e8) {
    char* n = *(char**)(*(char**)(e + 0xc) + 8);
    while (n) {
      EA::Audio::Eapd::outlet_float(*(void**)(n + 4), f);
      n = *(char**)n;
    }
  }
  --gOutletCount;
}

// @ 0x00a52080
void* __cdecl FUN_00a52080()
{
  void* p = EA::Audio::Eapd::pd_new(spMtofClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a520b0
void __cdecl FUN_00a520b0(void* obj, float a)
{
  if (gUnitA < a) {
    if (gUnitB < a)
      a = (float)log((double)gUnitB) * gA521;
    else
      a = (float)pow(2.0, (double)(a * gA522)) * gA523;
  } else {
    a = 0.0f;
  }
  OutletWalk(obj, a);
}

// @ 0x00a52170
void* __cdecl FUN_00a52170()
{
  void* p = EA::Audio::Eapd::pd_new(spFtomClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a521a0
void __cdecl FUN_00a521a0(void* obj, float a)
{
  if (gF521c < a)
    a = (float)log((double)a) * gF521a * gF521b;
  else
    a = gUnitA;
  OutletWalk(obj, a);
}

// @ 0x00a52230
void* __cdecl FUN_00a52230()
{
  void* p = EA::Audio::Eapd::pd_new(spRmstodbClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a52260
void __cdecl FUN_00a52260(void* obj, float a)
{
  if (0.0f < a) {
    float t = (float)log((double)a) * gA522 + gA523;
    if (0.0f < t)
      a = t;
  }
  OutletWalk(obj, a);
}

// @ 0x00a522f0
void* __cdecl FUN_00a522f0()
{
  void* p = EA::Audio::Eapd::pd_new(spPowtodbClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a52320
void __cdecl FUN_00a52320(void* obj, float a)
{
  if (0.0f < a) {
    float t = (float)log((double)a) * gF521a + gA523;
    if (0.0f < t)
      a = t;
  }
  OutletWalk(obj, a);
}

// @ 0x00a523b0
void* __cdecl FUN_00a523b0()
{
  void* p = EA::Audio::Eapd::pd_new(spDbtopowClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a523e0
void __cdecl FUN_00a523e0(void* obj, float a)
{
  if (0.0f < a) {
    if (gF523b < a)
      a = gF523b;
    a = (float)pow(2.0, (double)((a - gA523) * gF523a));
  } else {
    a = 0.0f;
  }
  OutletWalk(obj, a);
}

// @ 0x00a52490
void* __cdecl FUN_00a52490()
{
  void* p = EA::Audio::Eapd::pd_new(spDbtormsClass);
  if (p)
    EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  return p;
}

// @ 0x00a524c0
void __cdecl FUN_00a524c0(void* obj, float a)
{
  if (0.0f < a) {
    if (gF524b < a)
      a = gF524b;
    a = (float)pow(2.0, (double)((a - gA523) * gF524a));
  } else {
    a = 0.0f;
  }
  OutletWalk(obj, a);
}

// @ 0x00a52570
unsigned char __cdecl x_acoustics_setup()
{
  t_symbol* help = gensymS("acoustics.pd");
  int hs = help->s_thing;
  unsigned char r = 1;
  void* c;

  c = EA::Audio::Eapd::class_new7(gensymS("mtof"), help, (void*)&FUN_00a52080,
                                 0, 0x28, 0, 0);
  spMtofClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a520b0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("ftom"), help, (void*)&FUN_00a52170,
                                 0, 0x28, 0, 0);
  spFtomClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a521a0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("powtodb"), help, (void*)&FUN_00a522f0,
                                 0, 0x28, 0, 0);
  spPowtodbClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a52320);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("rmstodb"), help, (void*)&FUN_00a52230,
                                 0, 0x28, 0, 0);
  spRmstodbClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a52260);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("dbtopow"), help, (void*)&FUN_00a523b0,
                                 0, 0x28, 0, 0);
  spDbtopowClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a523e0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("dbtorms"), help, (void*)&FUN_00a52490,
                                 0, 0x28, 0, 0);
  spDbtormsClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a524c0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  return r;
}

// @ 0x00a52780
void __cdecl FUN_00a52780(char* obj)
{
  if (*(int*)(obj + 0x28) != (int)gEmptySymbol.s_name) {
    int r = ((VoiceManager*)EA::Audio::Eapd::GetVoiceManager())
              ->Add(*(int*)(obj + 0x28), *(int*)(obj + 0x2c), obj + 0x30);
    obj[0x34] = (char)r;
  }
}

// @ 0x00a527b0
void __cdecl FUN_00a527b0(char* obj, int sym, int a)
{
  obj[0x34] = 0;
  *(int*)(obj + 0x28) = sym;
  *(int*)(obj + 0x2c) = a;
  if (sym != (int)gEmptySymbol.s_name) {
    int r = ((VoiceManager*)EA::Audio::Eapd::GetVoiceManager())
              ->Add(*(int*)(obj + 0x28), *(int*)(obj + 0x2c), obj + 0x30);
    obj[0x34] = (char)r;
  }
}

// @ 0x00a527f0
void* __cdecl FUN_00a527f0(int sym, int a)
{
  char* p = (char*)EA::Audio::Eapd::pd_new(spControlClass);
  p[0x34] = 0;
  *(int*)(p + 0x28) = sym;
  *(int*)(p + 0x2c) = a;
  if (sym != (int)gEmptySymbol.s_name) {
    int r = ((VoiceManager*)EA::Audio::Eapd::GetVoiceManager())
              ->Add(sym, a, p + 0x30);
    p[0x34] = (char)r;
  }
  return p;
}

// @ 0x00a52840
void __cdecl FUN_00a52840(char* obj, int a, int b, int argc, int* argv)
{
  if (argc == 1 && obj[0x34] != 0) {
    VoiceManager* vm = (VoiceManager*)EA::Audio::Eapd::GetVoiceManager();
    if (*argv == 1)
      vm->S19(*(int*)(obj + 0x30), a, b);
    else if (*argv == 2)
      vm->S18(*(int*)(obj + 0x30), a, b, argv[1], argv[2]);
  }
}

// @ 0x00a528b0
void __cdecl FUN_00a528b0(char* obj, int a, int b, int argc, int* argv)
{
  if (argc >= 1 && *argv == 2)
    FUN_00a52840(obj, argv[1], argv[2], argc - 1, argv + 3);
}

// @ 0x00a528e0
unsigned char __cdecl a_control_setup()
{
  t_symbol* cls = gensymS("control");
  void* c = EA::Audio::Eapd::class_new(cls, (t_symbol*)0xc2e4e0,
                                       (void*)&FUN_00a527f0, 0, 0x38, 0, 6, 0);
  spControlClass = c;
  unsigned char r = (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_addanything(c, (void*)&FUN_00a52840);
  r &= EA::Audio::Eapd::class_addmethod(c, (void*)&FUN_00a528b0,
                                        gensymS("set"), 9);
  r &= EA::Audio::Eapd::class_addmethod(c, (void*)&FUN_00a527b0,
                                        gensymS("use"), 2);
  r &= EA::Audio::Eapd::class_addmethod(c, (void*)&FUN_00a52780,
                                        gensymS("reset"), 0);
  return r;
}

// @ 0x00a529c0
void* __thiscall CM_Hash::GetPair(void* out)
{
  int a = v18;
  *(int*)out = a;
  int b = v1c;
  *(int*)((char*)out + 4) = b;
  return out;
}

// group helpers: FUN_00a65470 is a __thiscall on [obj+0x38].
struct GroupHolder { char pad[0x38]; void* helper;
  void __thiscall Free();
};
struct GroupHelper {
  void __thiscall FreeGroup(int a, int b, int g);                 // 0xa65470
};
int   __cdecl FUN_00a65360(int, int, int, void*);
struct HashStub { void* __thiscall GetGroup(int a, int b); };

// @ 0x00a529e0
void* __cdecl FUN_00a529e0(int a, int b, int argc, int* argv)
{
  void* inst = EA::Audio::Eapd::canvas_getcurrentinstance();
  if (argc < 1 || *argv != 2)
    return 0;
  int v1 = argv[1];
  int v2 = argv[2];
  char* p = (char*)EA::Audio::Eapd::pd_new(spGroupClass);
  if (!p)
    return 0;
  void* out = EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  *(void**)(p + 0x28) = out;
  *(int*)(p + 0x2c) = v1;
  *(int*)(p + 0x30) = v2;
  int g = FUN_00a65360(v1, v2, argc - 1, argv + 3);
  *(int*)(p + 0x34) = g;
  *(void**)(p + 0x38) = inst;
  if (*(int*)(p + 0x28) != 0 && g != 0)
    return p;
  EA::Audio::Eapd::pd_free(p);
  return 0;
}

// @ 0x00a52a90
void __cdecl FUN_00a52a90(char* obj)
{
  if (*(int*)(obj + 0x34) != 0)
    ((GroupHelper*)*(void**)(obj + 0x38))
        ->FreeGroup(*(int*)(obj + 0x2c), *(int*)(obj + 0x30), *(int*)(obj + 0x34));
}

// @ 0x00a52ab0
void* __cdecl groupsize_new()
{
  char* p = (char*)EA::Audio::Eapd::pd_new(spGroupsizeClass);
  *(void**)(p + 0x28) =
      EA::Audio::Eapd::outlet_new(p, &gFloatSymbol, gOutletDstA);
  *(void**)(p + 0x2c) = EA::Audio::Eapd::canvas_getcurrentinstance();
  return p;
}

// @ 0x00a52af0
void __fastcall FUN_00a52af0(int* p)
{
  if (*p != 0)
    (*(void(__thiscall**)(void*))(p[3] + 0xc))(*(void**)p);
  p[3] = (int)&gVtblA52b40;
}

// @ 0x00a52b40
int __thiscall AnyObj::Call6(int a, int b)
{
  if (p4 != 0)
    return (*(int(__thiscall**)(int, int, int))(*(int*)p4 + 8))(a, b, 1);
  return 0;
}

// @ 0x00a52b70
void __thiscall AnyObj::Call4(int a)
{
  void* vt = vtbl;
  void (__thiscall *fn)(int, int) =
      *(void(__thiscall**)(int, int))((char*)vt + 4);
  fn(a, p8);
}

// @ 0x00a52b90
void __thiscall AnyObj::CallC(int a)
{
  if (p4 != 0)
    (*(void(__thiscall**)(int, int))(*(int*)p4 + 0xc))(a, 0);
}

// @ 0x00a52bb0
int __fastcall FUN_00a52bb0(void* self)
{
  char* s = (char*)self;
  return (int)(*(char**)(s + 4) - *(char**)s) >> 3;
}

// @ 0x00a52bc0
void __thiscall IdxVec::Get(t_symbol* out, unsigned idx)
{
  out->s_name = gEmptySymbol.s_name;
  out->s_thing = gEmptyA;
  int n = (int)(end - begin) >> 3;
  if (idx < (unsigned)n) {
    out->s_name = *(const char**)(begin + idx * 8);
    out->s_thing = *(int*)(begin + idx * 8 + 4);
  }
}

// @ 0x00a52c00
void __cdecl FUN_00a52c00(char* obj)
{
  if (!obj)
    return;
  char* g = *(char**)(obj + 0x34);
  if (!g || *(int*)(obj + 0x28) == 0)
    return;
  int n = (int)(*(char**)(g + 4) - *(char**)g) >> 3;
  float f = (float)n;
  if (n < 0)
    f += 4294967296.0f;
  OutletWalk(obj, f);
}

// @ 0x00a52c80
void __cdecl groupsize_symbol(char* obj, int a, int b)
{
  char* g = (char*)((HashStub*)*(void**)(obj + 0x2c))->GetGroup(a, b);
  if (!g)
    return;
  int n = (int)(*(char**)(g + 4) - *(char**)g) >> 3;
  float f = (float)n;
  if (n < 0)
    f += 4294967296.0f;
  OutletWalk(obj, f);
}

// @ 0x00a52d00
unsigned char __cdecl a_group_setup()
{
  t_symbol* cls = gensymS("group");
  void* c = EA::Audio::Eapd::class_new(cls, (t_symbol*)&FUN_00a529e0,
                                       (void*)&FUN_00a52a90, 0, 0x3c, 0, 9, 0);
  spGroupClass = c;
  unsigned char r = (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_addbang(c, (void*)&FUN_00a52c00);

  void* gs = EA::Audio::Eapd::class_new7(gensymS("groupsize"), cls,
                                        (void*)&groupsize_new, 0, 0x3c, 0, 0);
  spGroupsizeClass = gs;
  r &= (unsigned char)(gs != 0);
  r &= EA::Audio::Eapd::class_addsymbol(gs, (void*)&groupsize_symbol);
  return r;
}

// @ 0x00a52da0
void __cdecl FUN_00a52da0(int* first, int* last, int* value)
{
  for (; first != last; first += 2) {
    first[0] = value[0];
    first[1] = value[1];
  }
}

// eastl helpers used by the vector grow path.
void* __cdecl eastl_copy(void*, void*, void*, void*, void*);         // 0x76ffd0
void  __cdecl FUN_0073fe50(void*, void*, void*);                     // 0x73fe50
void  __cdecl FUN_006ac440(void*, unsigned, void*);                  // 0x6ac440
char* __cdecl FUN_0099efa0(char*, char*, char*);                     // 0x99efa0
void  __cdecl vector_erase_tail(void*, void*);                       // 0xd018d0

// @ 0x00a52dd0
void __thiscall PairVec::Insert(int pos, unsigned n, int* value)
{
  int cur = (int)this->cur;
  unsigned cap = (unsigned)(((char*)this->cap - (char*)cur) >> 3);
  char* pcur = (char*)this->cur;
  char* pbegin = (char*)this->begin;
  if (cap < n) {
    unsigned used = (unsigned)((pcur - pbegin) >> 3);
    unsigned grow = used * 2;
    if (used == 0)
      grow = 1;
    unsigned want = used + n;
    if (want < grow)
      want = grow;
    char* nb = 0;
    if (want != 0)
      nb = (char*)(*(void*(__thiscall**)(unsigned))((char*)alloc + 8))(want * 8);
    char* p = FUN_0099efa0(pbegin, (char*)pos, nb);
    {
      char* q = p;
      for (unsigned k = n; k != 0; --k) {
        if (q) {
          *(int*)(q + 0) = value[0];
          *(int*)(q + 4) = value[1];
        }
        q += 8;
      }
    }
    char* endp = FUN_0099efa0((char*)pos, pcur, p + n * 8);
    if (this->begin != 0)
      (*(void(__thiscall**)(int))((char*)alloc + 0xc))((int)this->begin);
    this->begin = (int*)nb;
    this->cur = (int*)endp;
    this->cap = (int*)(nb + want * 8);
  } else if (n != 0) {
    int tmp[2];
    tmp[0] = value[0];
    tmp[1] = value[1];
    unsigned tail = (unsigned)((pcur - (char*)pos) >> 3);
    if (n < tail) {
      unsigned off = n * 8;
      char* dst = pcur - off;
      eastl_copy((void*)pos, dst, pcur, pcur, dst);
      this->cur = (int*)(pcur + off);
      FUN_0073fe50((void*)pos, dst, pcur);
      FUN_00a52da0((int*)pos, (int*)((char*)pos + off), tmp);
      return;
    }
    unsigned extra = n - tail;
    FUN_006ac440(pcur, extra, tmp);
    this->cur = (int*)(pcur + extra * 8);
    eastl_copy((void*)pos, pcur, this->cur, this->cur, (void*)tail);
    this->cur = (int*)((char*)this->cur + tail * 8);
    FUN_00a52da0((int*)pos, (int*)pcur, tmp);
  }
}

// @ 0x00a52f70
void* __thiscall GroupHelp::Init(int b)
{
  v0 = 0;
  v1 = 0;
  v2 = 0;
  dummy = 0x1454fac;
  v10 = *(int*)(b + 4);
  v14 = (int)"EAPd/Group";
  return this;
}

// @ 0x00a52fa0
void __thiscall PairVec::Resize(unsigned n)
{
  unsigned have = (unsigned)(((char*)cur - (char*)begin) >> 3);
  if (have < n) {
    int tmp[2];
    Insert((int)cur, n - have, tmp);
    return;
  }
  vector_erase_tail((void*)((char*)begin + n * 8), (void*)cur);
}
