// Slice s007f2340: EA::Arithmetica token/variable table and IME proxy helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

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
// Token/variable table.  mVariables is a 4-byte-element vector at +0x2c.
// ---------------------------------------------------------------------------
struct VarMap {
  char pad0[0x2c];
  Vec4 mVariables;  // +0x2c
  char pad1[8];     // +0x38 .. +0x40

  unsigned GetTokenIndex(const char* name);
  float GetVar(const char* name);
  void SetVar(const char* name, float v);
};

// @ 0x007F2590
float VarMap::GetVar(const char* name) {
  unsigned i = GetTokenIndex(name);
  int n = ((int)mVariables.e - (int)mVariables.b) >> 2;
  if ((int)i <= n)
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

// ---------------------------------------------------------------------------
// 0x007F29E0 - wrapper that forwards two virtual calls plus the writer.
// ---------------------------------------------------------------------------
extern int ArithReadThing(void* unused, void* reader);

// @ 0x007F29E0
void __stdcall ArithReadWrapper(void* mgr, void* reader, int, int) {
  ((void(__thiscall*)(void*))VSLOT(mgr, 0x1c))(mgr);
  void* r = ((void*(__thiscall*)(void*))VSLOT(mgr, 0x18))(mgr);
  ArithReadThing(reader, r);
}

// ---------------------------------------------------------------------------
// Sims3::UI::IMEProxy (sizes: fields at +8, +0x10, +0x20, +0x24).
// ---------------------------------------------------------------------------
extern void* SPGetMessageServer();
extern void* UTFWinGetManager();

struct IMEProxy {
  char pad0[8];
  bool mbInitialized;      // +0x08
  char pad1[7];
  void* mpMessageServer;   // +0x10
  char pad2[0xc];
  void* mpIMEServer;       // +0x20
  void* mpWinMgr;          // +0x24
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

// @ 0x007F3320 (approximate: releases a secondary object through its vtable)
void IMEProxy::Shutdown() {
  void* p = mpIMEServer;
  if (p) {
    void* a = ((void*(__thiscall*)(void*))VSLOT(*(void**)((char*)p + 0x20c), 0x10))(*(void**)((char*)p + 0x20c));
    void* b = ((void*(__thiscall*)(void*))VSLOT(mpWinMgr, 4))(mpWinMgr);
    ((void(__thiscall*)(void*))VSLOT(p, 0x1c))(p);
    ((void(__thiscall*)(void*, void*))VSLOT(b, 0xdc))(b, a);
    mpIMEServer = 0;
    ((void(__thiscall*)(void*, int))VSLOT(p, 4))(p, 1);
  }
}

// ===========================================================================
// Remaining slice functions: skeletons (partial.txt).
// ===========================================================================

// @ 0x007F2340  token interning / lookup (free skeleton; the member stays
// declared-only so VarMap::GetVar/SetVar keep their out-of-line calls)
unsigned ArithTokenIndexSkeleton(const char* name) {
  (void)name;
  return 0;
}

// @ 0x007F2500  reset arithmetic state
void ArithReset(void* self) {
  (void)self;
}

// @ 0x007F2960  read-token helper (free skeleton; the wrapper keeps calling the
// declared-only ArithReadThing so its call stays out-of-line)
int ArithReadThingSkeleton(void* unused, void* reader) {
  (void)unused;
  (void)reader;
  return 1;
}

// @ 0x007F2600  (864-byte) arithmetic stack-machine run/validate
void ArithRun(void* self, void* code) {
  (void)self;
  (void)code;
}

// @ 0x007F2A70  (1632-byte) arithmetic stack-machine execute
void ArithExecute(void* self, void* code, int a, int b) {
  (void)self;
  (void)code;
  (void)a;
  (void)b;
}

// @ 0x007F31E0  Sims3::UI::IMEProxy::SetupDefaultFonts
void IMEProxy::SetupDefaultFonts() {}

// @ 0x007F3320 is defined above.

// ---------------------------------------------------------------------------
// 4-byte-element vector of integers (code stream).
// ---------------------------------------------------------------------------
struct VecU {
  uint32_t* b;  // +0
  uint32_t* e;  // +4
  uint32_t* c;  // +8
  void SlowPush(uint32_t* end, const uint32_t* v);
  void push_back(const uint32_t& v);
};

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
