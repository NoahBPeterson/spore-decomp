// src/game/SPAudio/eapdgroup.cpp -- migrated from slice(s) s00a52080 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdgroup.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int   gEmptyA;               // 0x16758a0
extern void* gVtblA52b40;                           // 0x1403934
#include <math.h>

// ---- items of slice s00a52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct t_symbol { const char* s_name; int s_thing; };   // 8 bytes
extern t_symbol gEmptySymbol;       // 0x167589c
extern int   gEmptyA;               // 0x16758a0
extern void* gVtblA52b40;                           // 0x1403934
struct AnyIface_a52b40 { virtual void v0(); virtual void v1(); virtual int Call(int a, int b, int c); };
struct AnyObj { void* vtbl; void* p4; const char* mpDefaultName;
  int  __thiscall Call6(int a, int b);
  void* __thiscall Call4(unsigned size);
  void __thiscall CallC(int a);
};
struct IdxVec { const char* begin; const char* end; char* cap; void __thiscall Get(t_symbol* out, unsigned idx); };
// ---- items of slice s00a52080 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern t_symbol gEmptySymbol;       // 0x167589c

// Destructor of an allocator-owned buffer (0x00a52af0): the data block goes back through the allocator's free slot
// (slot 3), then the allocator member restores its base vtable (0x1403934).
struct EapdAllocator_a52af0 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void Free(void* p);
  ~EapdAllocator_a52af0() { (void)this; }
};
struct EapdBuffer_a52af0 {
  void* mpData;                     // +0x00
  int   m4, m8;
  EapdAllocator_a52af0 mAllocator;  // +0x0c
  ~EapdBuffer_a52af0();
};

// @ 0x00a52af0
EapdBuffer_a52af0::~EapdBuffer_a52af0()
{
  if (mpData != 0)
    mAllocator.Free(mpData);
}

// @ 0x00a52b40
int __thiscall AnyObj::Call6(int a, int b)
{
  if (p4 != 0)
    return ((AnyIface_a52b40*)p4)->Call(a, b, 1);
  return 0;
}

// @ 0x00a52b70
void* __thiscall AnyObj::Call4(unsigned size)
{
  void* vt = vtbl;
  void* (__thiscall *fn)(AnyObj*, unsigned, const char*) =
      *(void*(__thiscall**)(AnyObj*, unsigned, const char*))((char*)vt + 4);
  return fn(this, size, mpDefaultName);
}

// @ 0x00a52b90
void __thiscall AnyObj::CallC(int a)
{
  if (p4 != 0)
    (*(void(__thiscall**)(void*, int, int))(*(int*)p4 + 0xc))(p4, a, 0);
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
  unsigned n = (unsigned)((int)(end - begin) >> 3);
  if (idx < n) {
    const char* const* p = (const char* const*)begin;
    out->s_name = p[idx * 2];
    out->s_thing = (int)(size_t)p[idx * 2 + 1];
  }
}
