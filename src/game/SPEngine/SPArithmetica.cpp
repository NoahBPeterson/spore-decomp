// src/game/SPEngine/SPArithmetica.cpp -- migrated from slice(s) s007f2340, s007f1220 by tools/migrate/rewrite.py
// Object file: SPEngine/SPArithmetica.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void EAWriteUint32(void* w, void* s, int n, int f);
#include <new>
#include <intrin.h>
#include "EA/Text/TextStyle.h"
#include <string.h>
#include <math.h>

// ---- items of slice s007f1220 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
struct E16 {
  uint32_t a, b, c, d;
};
bool ArithmeticaWriteResource(void* prog, void* writer);
struct ResBase {
  virtual ~ResBase() {}
  volatile long mRef;  // +0x04
  ResBase() { _InterlockedExchange(&mRef, 0); }
};
struct ResDerived : ResBase {
  virtual ~ResDerived() {}
};
struct Resource {
  virtual void Dummy();
  volatile long mRef;      // +0x04
  int mKey0, mKey1, mKey2; // +0x08
  void* mRelease;          // +0x14
  Resource() {
    _InterlockedExchange(&mRef, 0);
    mKey0 = 0;
    mKey1 = 0;
    mKey2 = 0;
    mRelease = 0;
  }
};
struct VecPtr {
  void* b;  // +0
  void* e;  // +4
  void* c;  // +8
  VecPtr() : b(0), e(0), c(0) {}
};
class cArithmeticaProgram : public Resource { public:
  VecPtr mTokens;        // +0x18
  int pad24;             // +0x24
  int pad28;
  VecPtr mVariables;     // +0x2c
  int pad38, pad3c;
  VecPtr mInstructions;  // +0x40
  int pad4c, pad50, pad54;
  VecPtr mStack;         // +0x58
  int pad64, pad68;
  VecPtr mGosubStack;    // +0x6c
  int pad78, pad7c;
  VecPtr mLabels;        // +0x80
  int pad8c, pad90;
  cArithmeticaProgram();
  void* CompileToByteCode(void* out);
  void Destroy();
  void Copy(const cArithmeticaProgram& other);
};
struct ProgStub {
  void CompileToByteCode(void* out);  // __thiscall ret 4
};
extern void EAWriteUint32(void* w, void* s, int n, int f);
struct VFactory {
  bool Create(void* param2, void* out, void* param4, void* param5);
};
// ---- items of slice s007f1220 end

// ---- items of slice s007f2340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*    __cdecl sub_f473a0(int size, const char* app, int a, int b, const char* file, int line);
extern "C" void     __cdecl sub_f47380(void* p);
extern "C" void     __cdecl sub_93a780(void* reader, int* out, int a, int b);   // EA::IO::ReadInt32
extern "C" void     __cdecl sub_705250(void* a, void* b, void* c);
extern "C" void     __cdecl sub_d018d0(void* a, void* b);
extern "C" void*    __cdecl sub_7c8b70(void* a, void* b, void* c);
extern "C" void     __cdecl sub_6a4950(void* a, void* b);
extern "C" void     __cdecl sub_67c8b0(void* a, void* b, int c);
extern "C" double   __cdecl sub_11e0906(double x);        // floor
extern "C" double   __cdecl sub_13cc4bc(double x);        // ceil
extern "C" double   __cdecl sub_11e08bc(double x);
extern "C" double   __cdecl sub_11e08c8(double x);
extern "C" double   __cdecl sub_11e08f0(double base, double e);   // pow
extern "C" double   __fastcall sub_9360d0(void* self);    // cRandomGlobal::RandomDouble
extern "C" char     g_01601760[];                         // EA::Random::cRandomGlobal
extern bool ArithReadThing(void* self, void* reader);
struct Vec4 {
  float* b;  // +0
  float* e;  // +4
  float* c;  // +8
  void SlowPush(float* end, const float* v);
  void push_back(const float& v);
  void resize(unsigned n);
  void sub_4b0a10(float* end, int n, const float* v);   // grow + fill (0x004b0a10)
  void sub_50d4e0(const Vec4& other);                   // assign (0x0050d4e0)
};
struct VecU {
  uint32_t* b;  // +0
  uint32_t* e;  // +4
  uint32_t* c;  // +8
  void SlowPush(uint32_t* end, const uint32_t* v);
  void push_back(const uint32_t& v);
  void sub_50d4e0(const VecU& other);                   // assign (0x0050d4e0)
};
struct ArithCode {
  uint32_t op;   // +0x0
  float    f1;   // +0x4
  uint32_t f2;   // +0x8
  uint32_t f3;   // +0xc
};
struct ArithCodeVec {
  ArithCode* b;  // +0
  ArithCode* e;  // +4
  ArithCode* c;  // +8
  void sub_7f1f60(int n);            // resize (0x007f1f60)
  void sub_553be0(int n);            // resize (0x00553be0)
};
struct EString {
  char*  begin;  // +0
  char*  end;    // +4
  char*  cap;    // +8
  void*  alloc;  // +0xc
  void sub_454cb0(const char* first, const char* last);   // assign (0x00454cb0)
};
struct ENameVec {
  EString* b;  // +0
  EString* e;  // +4
  EString* c;  // +8
  void sub_553cc0(const EString& s);        // push_back (0x00553cc0)
  void sub_6a4950(void* a, void* b);        // erase (0x006a4950)
};
struct PairVec {
  void* b;  // +0
  void* e;  // +4
  void* c;  // +8
  void sub_7cf630(int n);            // resize (0x007cf630)
  void sub_d018d0(void* a, void* b); // erase (0x00d018d0)
};
struct VMContext {
  Vec4 fs;         // +0x00  float operand stack
  char pad0c[8];   // +0x0c .. +0x14
  VecU us;         // +0x14  integer / return-address stack
  uint32_t Execute(const ArithCodeVec* code, float* mem, int start, int end);
};
struct VarMap {
  char pad0[0x18];      // +0x00 .. +0x18
  ENameVec mNames;      // +0x18  token-name strings (0x10-byte elements)
  char pad24[8];        // +0x24 .. +0x2c
  Vec4 mVariables;      // +0x2c  variables (floats)
  char pad38[8];        // +0x38 .. +0x40
  ArithCodeVec mCode;   // +0x40  arithmetica program (0x10-byte records)
  char pad4c[0xc];      // +0x4c .. +0x58
  VMContext mVM;        // +0x58  operand stacks
  char pad78[8];        // +0x78 .. +0x80
  PairVec mPair;        // +0x80  callback pairs

  unsigned GetTokenIndex(const char* name);
  float GetVar(const char* name);
  void SetVar(const char* name, float v);
  bool LoadProgram(const uint32_t* const* program);
  void sub_553be0(int n);           // resize helper (0x00553be0)
};
// ---- items of slice s007f2340 end

// @ 0x007f1600
int __stdcall ArithmeticaKeyRead(void** p, unsigned count)
{
  if (p) {
    if (count < 1) return 0;
    *p = (void*)0x0472329b;
  }
  return 1;
}

// @ 0x007f1630
void* cArithmeticaProgram::CompileToByteCode(void* out)
{
  (void)out;
  return 0;
}

// @ 0x007f1820
bool ArithmeticaWriteResource(void* prog, void* writer)
{
  struct Compiled {
    void* data;  // +0
    int size;    // +4
  } c;
  ((ProgStub*)prog)->CompileToByteCode(&c);
  int sz = c.size;
  EAWriteUint32(writer, &sz, 1, 0);
  ((void(__thiscall*)(void*, void*, int))VSLOT(writer, 0x38))(writer, c.data, c.size * 4);
  return true;
}

// @ 0x007f1870
void __stdcall ArithmeticaFactoryWrite(void* prog, void* mgr, int, int)
{
  void* writer = ((void*(__thiscall*)(void*))(*(void***)mgr)[0x18 / 4])(mgr);
  ArithmeticaWriteResource(prog, writer);
}

// @ 0x007f1890
E16** UninitCopy16(E16** result, E16* first, E16* last, E16* dst)
{
  *result = dst;
  if (first != last) {
    do {
      if (dst) *dst = *first;
      ++first;
      ++dst;
    } while (first != last);
    *result = dst;
  }
  return result;
}

// @ 0x007f18e0
ResDerived* CreateResDerived()
{
  return new ("App", 0, 0, 0, 0) ResDerived;
}

// @ 0x007f1ac0
void ArithmeticaAssignLabels(void* self, void* other)
{
  (void)self;
  (void)other;
}

// @ 0x007f1bf0
void ArithmeticaVec16Insert(void* self, void* pos, unsigned count, void* value)
{
  (void)self;
  (void)pos;
  (void)count;
  (void)value;
}

// @ 0x007f1d90
void cArithmeticaProgram::Destroy()
{}

// @ 0x007f1e60
cArithmeticaProgram::cArithmeticaProgram()
{}

// @ 0x007f1ed0
bool VFactory::Create(void* param2, void* out, void* param4, void* param5)
{
  cArithmeticaProgram* prog = new ("App/cArithmeticaFactory", 0, 0, 0, 0) cArithmeticaProgram;
  int* key = (int*)((void*(__thiscall*)(void*))VSLOT(param2, 0x10))(param2);
  prog->mKey0 = key[0];
  prog->mKey1 = key[1];
  prog->mKey2 = key[2];
  if (((bool(__thiscall*)(void*, void*, void*, void*, void*))VSLOT(this, 0x24))(
          this, param2, prog, param4, param5)) {
    *(void**)out = prog;
    ((void(__thiscall*)(void*))VSLOT(prog, 0))(prog);
    return true;
  }
  ((void(__thiscall*)(void*, int))VSLOT(prog, 8))(prog, 1);
  return false;
}

// @ 0x007f1f60
void ArithmeticaVecResize(void* self, unsigned n)
{
  (void)self;
  (void)n;
}

// @ 0x007f1fe0
void ArithmeticaVec16Assign(void* self, void* other)
{
  (void)self;
  (void)other;
}

// @ 0x007f20d0
void ArithmeticaLookupRun(void* self, void* key)
{
  (void)self;
  (void)key;
}

// @ 0x007f21d0
void cArithmeticaProgram::Copy(const cArithmeticaProgram& other)
{
  (void)other;
}

// @ 0x007f2240
bool LoadArithmeticaFile(void* arg1, void* arg2)
{
  (void)arg1;
  (void)arg2;
  return false;
}

// @ 0x007f2340
unsigned VarMap::GetTokenIndex(const char* name)
{
  unsigned count = (unsigned)(((char*)mNames.e - (char*)mNames.b) >> 4);
  for (unsigned i = 0; i < count; i++) {
    const char* s = mNames.b[i].begin;
    if (s && strcmp(s, name) == 0)
      return i;
  }
  unsigned len = (unsigned)strlen(name);
  char* buf;
  if (len + 1 > 1)
    buf = (char*)sub_f473a0((int)(len + 1), (const char*)0x13ebc58, 0, 0, (const char*)0x13ebb38, 0xd1);
  else
    buf = (char*)0x1667bac;                        // eastl::gEmptyString16
  memcpy(buf, name, len);                          // the original copies even a zero-length name
  buf[len] = 0;
  EString tmp;
  tmp.begin = buf;
  tmp.end   = buf + len;
  tmp.cap   = buf + len + 1;
  tmp.alloc = 0;
  mNames.sub_553cc0(tmp);
  if ((unsigned)(tmp.cap - tmp.begin) > 1 && tmp.begin)
    sub_f47380(tmp.begin);

  unsigned nc = (unsigned)(((char*)mNames.e - (char*)mNames.b) >> 4);
  unsigned vn = (unsigned)(mVariables.e - mVariables.b);
  if (nc > vn) {
    float zero = 0.0f;
    mVariables.sub_4b0a10(mVariables.e, (int)(nc - vn), &zero);
  } else {
    mVariables.e = mVariables.b + nc;
  }
  return nc - 1;
}

// @ 0x007f2500
void __fastcall ArithReset(VarMap* self)
{
  Vec4 emptyF;
  emptyF.b = emptyF.e = emptyF.c = 0;
  VecU emptyU;
  emptyU.b = emptyU.e = emptyU.c = 0;
  self->mVM.fs.sub_50d4e0(emptyF);
  self->mVM.us.sub_50d4e0(emptyU);
  self->mVM.Execute(&self->mCode, self->mVariables.b, -1, -1);
}

// @ 0x007f2590
float VarMap::GetVar(const char* name)
{
  unsigned i = GetTokenIndex(name);
  if (i <= (unsigned)(mVariables.e - mVariables.b))
    return mVariables.b[i];
  return 0.0f;
}

// @ 0x007f25c0
void VarMap::SetVar(const char* name, float v)
{
  unsigned i = GetTokenIndex(name);
  Vec4* mv = &mVariables;
  if ((unsigned)(mv->e - mv->b) < i + 1)
    mv->resize(i + 1);
  mv->b[i] = v;
}

// @ 0x007f2600
bool VarMap::LoadProgram(const uint32_t* const* program)
{
  const uint32_t* p = *program;
  if (p[0] != 0x41525448 || p[1] != 1)
    return false;

  // --- reset the program / callback / token / variable vectors ---------------
  sub_705250(mCode.e, mCode.e, mCode.b);
  mCode.e = mCode.b;
  sub_d018d0(mPair.b, mPair.e);
  mPair.e = mPair.b;
  {
    void* nb = mNames.b;
    void* ne = mNames.e;
    void* u = sub_7c8b70((void*)(uintptr_t)ne, (void*)(uintptr_t)ne, nb);
    sub_6a4950(u, mNames.e);
    mNames.e = mNames.b;
  }
  sub_67c8b0(mVariables.b, mVariables.e, 0);
  mVariables.e = mVariables.b;

  // --- program records -------------------------------------------------------
  uint32_t count = p[4];
  mCode.sub_7f1f60((int)count);

  uint32_t done = 0;
  if ((int)count >= 4) {
    uint32_t iters = ((count - 4) >> 2) + 1;
    done = iters * 4;
    const uint32_t* s = p + 5;
    uint32_t off = 0;
    do {
      for (uint32_t k = 0; k < 4; k++) {
        const uint32_t* r = s + 4 * k;
        ArithCode& d = mCode.b[off + k];
        d.f3 = r[0];
        d.f1 = *(const float*)(r + 1);
        d.f2 = r[2];
        d.op = r[3];
      }
      s += 16;
      off += 4;
    } while (--iters);
  }
  if (done < count) {
    const uint32_t* s = p + 5 + 4 * done;
    for (uint32_t r = done; r < count; r++) {
      ArithCode& d = mCode.b[r];
      d.f3 = s[0];
      d.f1 = *(const float*)(s + 1);
      d.f2 = s[2];
      d.op = s[3];
      s += 4;
    }
  }
  uint32_t cur = 1 + 4 * count;      // dword index of the last record

  // --- callback-pair table ---------------------------------------------------
  mPair.sub_7cf630((int)p[cur + 4]);
  cur += 5;
  uint32_t nPairs = (uint32_t)((char*)mPair.e - (char*)mPair.b) >> 3;
  for (uint32_t k = 0; k < nPairs; k++) {
    ((uint32_t*)mPair.b)[2 * k]     = p[cur];
    ((uint32_t*)mPair.b)[2 * k + 1] = p[cur + 1];
    cur += 2;
  }

  sub_553be0((int)p[cur]);
  uint32_t nVars = p[cur + 1];
  uint32_t have = (uint32_t)(mVariables.e - mVariables.b);
  if (have < nVars) {
    float zero = 0.0f;
    mVariables.sub_4b0a10(mVariables.e, (int)(nVars - have), &zero);
  } else {
    mVariables.e = mVariables.b + nVars;
  }
  cur += 2;

  // --- token strings ---------------------------------------------------------
  const char* s = (const char*)(p + cur);
  uint32_t nNames = (uint32_t)(((char*)mNames.e - (char*)mNames.b) >> 4);
  for (uint32_t k = 0; k < nNames; k++) {
    EString& e = mNames.b[k];
    const char* e2 = s;
    while (*e2) e2++;
    e.sub_454cb0(s, e2);
    s = s + (e.end - e.begin) + 1;
  }
  return true;
}

// @ 0x007f2960
bool __cdecl ArithReadThing(void* self, void* reader)
{
  int count = 0;                   // written by ReadInt32
  sub_93a780(reader, &count, 1, 0);
  uint32_t* buf = (uint32_t*)sub_f473a0(count * 4, (const char*)0x13ebc58, 0, 0, 0, 0);
  ((void(__thiscall*)(void*, void*, int))VSLOT(reader, 0x30))(reader, buf, count * 4);
  ((VarMap*)self)->LoadProgram((const uint32_t* const*)&buf);
  sub_f47380(buf);
  return true;
}

// @ 0x007f29e0
void __stdcall ArithReadWrapper(void* mgr, void* reader, int, int)
{
  ((void(__thiscall*)(void*))VSLOT(mgr, 0x1c))(mgr);
  void* r = ((void*(__thiscall*)(void*))VSLOT(mgr, 0x18))(mgr);
  ArithReadThing(reader, r);
}

// @ 0x007f2a70
uint32_t VMContext::Execute(const ArithCodeVec* code, float* mem, int start, int end)
{
  if (start == -1) start = 0;
  if (end == -1) end = (int)(code->e - code->b);
  int i = start;
  if (i >= end)
    return (uint32_t)i;
  do {
    uint32_t op = code->b[i].op;
    switch (op) {
      case 0x00: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(a + b);
      } break;
      case 0x01: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(a - b);
      } break;
      case 0x02: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(a * b);
      } break;
      case 0x03: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(a / b);
      } break;
      case 0x04: {                                   // pow(a, b)
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back((float)sub_11e08f0((double)a, (double)b));
      } break;
      case 0x05:                                     // push immediate
        fs.push_back(code->b[i].f1);
        break;
      case 0x06:                                     // push variable
        fs.push_back(mem[code->b[i].f2]);
        break;
      case 0x07:
      case 0x08:                                     // store variable
        mem[code->b[i].f2] = fs.e[-1];
        fs.e -= 1;
        break;
      case 0x09:
      case 0x13:                                     // nop
        break;
      case 0x0a:                                     // push random [0,1)
        fs.push_back((float)sub_9360d0((void*)g_01601760));
        break;
      case 0x0b: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(a > b ? 1.0f : 0.0f);
      } break;
      case 0x0c: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(b > a ? 1.0f : 0.0f);
      } break;
      case 0x0d: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(a >= b ? 1.0f : 0.0f);
      } break;
      case 0x0e: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(b >= a ? 1.0f : 0.0f);
      } break;
      case 0x0f: {                                   // approx-equal (tolerance 1e-4)
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(fabsf(a - b) < 0.0001f ? 1.0f : 0.0f);
      } break;
      case 0x10: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back(fabsf(a - b) > 0.0001f ? 1.0f : 0.0f);
      } break;
      case 0x11: {                                   // conditional (if)
        float top = fs.e[-1];
        fs.e -= 1;
        if (top < 1.0f) {
          uint32_t n = (uint32_t)(code->e - code->b);
          i++;
          int nest = 0;
          for (;;) {
            uint32_t o = (uint32_t)i < n ? code->b[i].op : 0;
            if (((uint32_t)i >= n || o == 0x12 || o == 0x13) && nest <= 0)
              break;
            if (o == 0x11) nest++;
            else if (o == 0x13) nest--;
            i++;
          }
        }
      } break;
      case 0x12: {                                   // else / end-if skip
        uint32_t n = (uint32_t)(code->e - code->b);
        i++;
        int nest = 0;
        while ((uint32_t)i < n) {
          uint32_t o = code->b[i].op;
          if (o == 0x11) nest++;
          else if (o == 0x13) { if (nest <= 0) break; nest--; }
          i++;
        }
      } break;
      case 0x14: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back((b > 1e-05f && a > 0.0001f) ? 1.0f : 0.0f);
      } break;
      case 0x15: {
        float a = fs.e[-2], b = fs.e[-1];
        fs.e -= 2;
        fs.push_back((b > 1e-05f || a > 0.0001f) ? 1.0f : 0.0f);
      } break;
      case 0x16:                                     // jump
        i = (int)code->b[i].f2 - 1;
        break;
      case 0x17:                                     // call
        us.push_back((uint32_t)i);
        i = (int)code->b[i].f2 - 1;
        break;
      case 0x18:                                     // return
        if (us.e == us.b)
          return (uint32_t)(i + 1);
        i = (int)us.e[-1];
        us.e -= 1;
        break;
      case 0x19: fs.e[-1] = (float)sub_11e0906((double)fs.e[-1]); break;
      case 0x1a: fs.e[-1] = (float)sub_13cc4bc((double)fs.e[-1]); break;
      case 0x1b: fs.e[-1] = sinf(fs.e[-1]);  break;
      case 0x1c: fs.e[-1] = cosf(fs.e[-1]);  break;
      case 0x1d: fs.e[-1] = tanf(fs.e[-1]);  break;
      case 0x1e: fs.e[-1] = (float)sub_11e08bc((double)fs.e[-1]); break;
      case 0x1f: fs.e[-1] = (float)sub_11e08c8((double)fs.e[-1]); break;
      case 0x20: fs.e[-1] = atanf(fs.e[-1]); break;
      default:
        break;
    }
    i++;
  } while (i < end);
  return (uint32_t)i;
}
