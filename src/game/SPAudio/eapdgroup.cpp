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
struct AnyObj { void* vtbl; void* p4; int p8;
  int  __thiscall Call6(int a, int b);
  void __thiscall Call4(int a);
  void __thiscall CallC(int a);
};
struct IdxVec { const char* begin; const char* end; char* cap; void __thiscall Get(t_symbol* out, unsigned idx); };
// ---- items of slice s00a52080 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern t_symbol gEmptySymbol;       // 0x167589c

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
