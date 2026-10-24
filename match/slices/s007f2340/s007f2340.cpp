// Slice s007f2340: EA::Arithmetica token/variable table and IME proxy helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>
#include <string.h>
#include <math.h>

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

// ---------------------------------------------------------------------------
// Original entry points referenced by these functions (resolved by the harness
// to their real addresses: cdecl by extern "C", thiscall by a struct member
// whose spelled name carries the address / a __thiscall function-pointer cast).
// ---------------------------------------------------------------------------
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
extern "C" uint32_t g_01541f8c;                           // EA::Text style id (_sIMETextStyle)

extern "C" void* __cdecl sub_885bd0(int a);               // EA::Text::GetStyleManager
extern "C" void  __cdecl sub_894670();                    // EA::Text::StyleManager::GetStyle
extern "C" uint32_t __cdecl sub_894970(void* mgr, uint32_t sid, void* style);  // StyleManagerAddStyle
extern "C" void  __cdecl sub_8941d0();                    // EA::Text::TextStyle::TextStyle
extern "C" void  __cdecl sub_8945a0();                    // EA::Text::TextStyle copy ctor
extern "C" void  __cdecl sub_894280();                    // EA::Text::TextStyle operator=
extern "C" void* __cdecl sub_957f30();                    // EA::UTFWin::GetManager

// ---------------------------------------------------------------------------
// 4-byte-element vector (variables / stack values).
// ---------------------------------------------------------------------------
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

// @ 0x007F2A10
void Vec4::push_back(const float& v) {
  float* p = e;
  if (p < c) {
    e = p + 1;
    if (p) *p = v;
  } else {
    SlowPush(p, &v);
  }
}

// ---------------------------------------------------------------------------
// 4-byte-element vector of integers (the VM's integer / call stack).
// ---------------------------------------------------------------------------
struct VecU {
  uint32_t* b;  // +0
  uint32_t* e;  // +4
  uint32_t* c;  // +8
  void SlowPush(uint32_t* end, const uint32_t* v);
  void push_back(const uint32_t& v);
  void sub_50d4e0(const VecU& other);                   // assign (0x0050d4e0)
};

// One 0x10-byte arithmetica program record.
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

// eastl::string stand-in (the token names) and its vector.
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

// vector<pair<callback, void*>> (8-byte elements) at +0x80.
struct PairVec {
  void* b;  // +0
  void* e;  // +4
  void* c;  // +8
  void sub_7cf630(int n);            // resize (0x007cf630)
  void sub_d018d0(void* a, void* b); // erase (0x00d018d0)
};

// Arithmetica execution context: float operand stack at +0, integer / return
// address stack at +0x14.
struct VMContext {
  Vec4 fs;         // +0x00  float operand stack
  char pad0c[8];   // +0x0c .. +0x14
  VecU us;         // +0x14  integer / return-address stack
  uint32_t Execute(const ArithCodeVec* code, float* mem, int start, int end);
};

// ---------------------------------------------------------------------------
// Token/variable table (the Arithmetica object).
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// eastl::string assign helper used while interning a token.
// ---------------------------------------------------------------------------

// @ 0x007F2590
float VarMap::GetVar(const char* name) {
  unsigned i = GetTokenIndex(name);
  if (i <= (unsigned)(mVariables.e - mVariables.b))
    return mVariables.b[i];
  return 0.0f;
}

// @ 0x007F25C0
void VarMap::SetVar(const char* name, float v) {
  unsigned i = GetTokenIndex(name);
  Vec4* mv = &mVariables;
  if ((unsigned)(mv->e - mv->b) < i + 1)
    mv->resize(i + 1);
  mv->b[i] = v;
}

// @ 0x007F2340
unsigned VarMap::GetTokenIndex(const char* name) {
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

// @ 0x007F2500
void __fastcall ArithReset(VarMap* self) {
  Vec4 emptyF;
  emptyF.b = emptyF.e = emptyF.c = 0;
  VecU emptyU;
  emptyU.b = emptyU.e = emptyU.c = 0;
  self->mVM.fs.sub_50d4e0(emptyF);
  self->mVM.us.sub_50d4e0(emptyU);
  self->mVM.Execute(&self->mCode, self->mVariables.b, -1, -1);
}

// ---------------------------------------------------------------------------
// ArithReadThing is called by the wrapper below before its out-of-line body.
// ---------------------------------------------------------------------------
extern bool ArithReadThing(void* self, void* reader);

// @ 0x007F29E0
void __stdcall ArithReadWrapper(void* mgr, void* reader, int, int) {
  ((void(__thiscall*)(void*))VSLOT(mgr, 0x1c))(mgr);
  void* r = ((void*(__thiscall*)(void*))VSLOT(mgr, 0x18))(mgr);
  ArithReadThing(reader, r);
}

// ---------------------------------------------------------------------------
// Program deserialization.  The blob is a flat dword stream:
//   [0]=0x41525448 magic, [1]=1 version, [2..3]=?, [4]=record count,
//   [5..]  = count program records (4 dwords each, stored {f3,f1,f2,op}),
//   then the callback-pair table, the variable count, and the NUL-terminated
//   token strings.
// (Reconstruction: matches the decompile's field permutation and cursor logic.)
// @ 0x007F2600
bool VarMap::LoadProgram(const uint32_t* const* program) {
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

// @ 0x007F2960
bool __cdecl ArithReadThing(void* self, void* reader) {
  int count = 0;                   // written by ReadInt32
  sub_93a780(reader, &count, 1, 0);
  uint32_t* buf = (uint32_t*)sub_f473a0(count * 4, (const char*)0x13ebc58, 0, 0, 0, 0);
  ((void(__thiscall*)(void*, void*, int))VSLOT(reader, 0x30))(reader, buf, count * 4);
  ((VarMap*)self)->LoadProgram((const uint32_t* const*)&buf);
  sub_f47380(buf);
  return true;
}

// ---------------------------------------------------------------------------
// Arithmetica bytecode VM.  Opcodes 0x00..0x20 (jump table at 0x007f3048).
// @ 0x007F2A70
uint32_t VMContext::Execute(const ArithCodeVec* code, float* mem, int start, int end) {
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

// ---------------------------------------------------------------------------
// Sims3::UI::IMEProxy (fields at +8, +0x10, +0x20, +0x24, +0x30, +0x3c).
// ---------------------------------------------------------------------------
extern void* SPGetMessageServer();
extern void* UTFWinGetManager();

struct TextStyle {
  float field0;          // +0x00
  char pad1[0x240];      // +0x04 .. +0x244
  uint32_t field244;     // +0x244
  uint32_t field248;     // +0x248
  char pad2[0x28];       // +0x24c .. +0x274
  TextStyle* ctor();            // 0x008941d0
  void copy(const TextStyle&);  // 0x008945a0
  void assign(const TextStyle&); // 0x00894280
};

struct IMEProxy {
  char pad0[8];
  bool mbInitialized;        // +0x08
  char pad1[7];
  void* mpMessageServer;     // +0x10
  char pad2[0xc];            // +0x14 .. +0x20
  void* mpIMEServer;         // +0x20
  void* mpWinMgr;            // +0x24
  char pad28[8];             // +0x28 .. +0x30
  void* mpWinComposition;    // +0x30
  char pad34[8];             // +0x34 .. +0x3c
  void* mpWinCandidateList;  // +0x3c
  bool Init(void* server, int);
  void Shutdown();
  void SetupDefaultFonts();
};

// @ 0x007F30E0
bool IMEProxy::Init(void* server, int) {
  if (mbInitialized) return true;
  mbInitialized = true;
  mpMessageServer = SPGetMessageServer();
  mpIMEServer = server;
  mpWinMgr = UTFWinGetManager();
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44c0e);
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44c11);
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44ed1);
  ((void(__thiscall*)(void*, void*, int))VSLOT(mpMessageServer, 0x20))(mpMessageServer, this, 0x2ac44ed4);
  return true;
}

// @ 0x007F3320
void IMEProxy::Shutdown() {
  void* p = mpWinComposition;
  if (!p) return;
  void* a = ((void*(__thiscall*)(void*))VSLOT((char*)p + 0x20c, 0x10))((char*)p + 0x20c);
  void* b = ((void*(__thiscall*)(void*))VSLOT(mpWinMgr, 4))(mpWinMgr);
  ((void(__thiscall*)(void*))VSLOT(p, 0x1c))(p);
  ((void(__thiscall*)(void*, void*))VSLOT(b, 0xdc))(b, a);
  if (!mpWinComposition) return;
  void* q = mpWinComposition;
  mpWinComposition = 0;
  ((void(__thiscall*)(void*))VSLOT(q, 4))(q);
}

// @ 0x007F31E0
void IMEProxy::SetupDefaultFonts() {
  typedef const void* (__thiscall* GetStyleFn)(void*, uint32_t, void*);
  void* sm = sub_885bd0(1);
  uint32_t sid = g_01541f8c;
  const void* st = ((GetStyleFn)sub_894670)(sm, sid, 0);
  if (!st) {
    TextStyle tmp;
    tmp.ctor();
    sid = sub_894970(sm, sid, &tmp);
    g_01541f8c = sid;
    st = ((GetStyleFn)sub_894670)(sm, sid, 0);
  }

  void* mgr = sub_957f30();
  uint32_t val;
  void* z = ((void*(__thiscall*)(void*, int))VSLOT(mgr, 0x48))(mgr, 0);
  if (z)
    z = ((void*(__thiscall*)(void*, int))VSLOT(z, 0xc))(z, 0xcf428691);
  if (!z) {
    void* p = mpWinComposition;
    if (p) {
      z = ((void*(__thiscall*)(void*, int))VSLOT(p, 0xc))(p, 0xcf428691);
      val = z ? ((uint32_t(__thiscall*)(void*))VSLOT(z, 0x14))(z) : 0xde808a42;
    } else {
      val = 0xde808a42;
    }
  } else {
    val = ((uint32_t(__thiscall*)(void*))VSLOT(z, 0x14))(z);
  }

  const void* st2 = ((GetStyleFn)sub_894670)(sm, val, 0);
  if (!st2)
    st2 = ((GetStyleFn)sub_894670)(sm, 0xde808a42, 0);

  TextStyle tmp2;
  tmp2.copy(*(const TextStyle*)st2);
  tmp2.field244 = 0;
  tmp2.field248 = 1;
  tmp2.field0 = 0.0f;
  ((TextStyle*)st)->assign(tmp2);

  if (mpWinComposition) {
    void* o = *(void**)((char*)mpWinComposition + 4);
    ((void(__thiscall*)(void*, uint32_t))VSLOT(o, 0x84))(o, g_01541f8c);
  }
  if (mpWinCandidateList) {
    void* o = *(void**)((char*)mpWinCandidateList + 4);
    ((void(__thiscall*)(void*, uint32_t))VSLOT(o, 0x84))(o, g_01541f8c);
  }
}

// @ 0x007F2A40
void VecU::push_back(const uint32_t& v) {
  uint32_t* p = e;
  if (p < c) {
    e = p + 1;
    if (p) *p = v;
  } else {
    SlowPush(p, &v);
  }
}