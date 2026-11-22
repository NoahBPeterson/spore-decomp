// src/game/SPAudio/eapdgroup.cpp -- migrated from slice(s) s00a52080 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdgroup.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int   gEmptyA;               // 0x16758a0
extern void* gVtblA52b40;                           // 0x1403934
#include <math.h>

// ---- items of slice s00a52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   gOutletCount;          // 0x167545c
extern void* spGroupsizeClass;      // 0x167551c
struct t_symbol { const char* s_name; int s_thing; };   // 8 bytes
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl pd_new(void* cls);                                   // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl outlet_new(void* obj, t_symbol* s, int a);           // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl outlet_new(void* obj, t_symbol s);                    // 0xa49d30; by-value symbol
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl outlet_float(void* out, float f);                    // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl class_new(t_symbol* s, t_symbol* help, void* makefn,
                        void* freefn, int size, int flags, int a1, int a2); // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl class_new7(t_symbol* s, t_symbol* help, void* makefn,
                         void* freefn, int size, int flags, int a1);        // 0xa48e50 (7-arg)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned char __cdecl class_addbang(void* cls, void* fn);          // 0xa47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned char __cdecl class_addsymbol(void* cls, void* fn);        // 0xa47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* __cdecl gensym(t_symbol* out, const char* name);         // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl canvas_getcurrentinstance();                         // 0xa4a450
}
}
}
extern t_symbol gFloatSymbol;       // 0x16758c4
extern t_symbol gEmptySymbol;       // 0x167589c
struct AnyIface_a52b40 { virtual void v0(); virtual void v1(); virtual int Call(int a, int b, int c); };
struct AnyObj { void* vtbl; void* p4; const char* mpDefaultName;
  int  __thiscall Call6(int a, int b);
  void* __thiscall Call4(unsigned size);
  void __thiscall CallC(int a);
};
struct IdxVec { const char* begin; const char* end; char* cap; void __thiscall Get(t_symbol* out, unsigned idx); };
static __forceinline t_symbol* gensymS(const char* s) {
  t_symbol tmp;
  return EA::Audio::Eapd::gensym(&tmp, s);
}
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
struct HashStub { void* __thiscall GetGroup(int a, int b); };
struct GroupsizeObject {
  unsigned int mPdHeader[10];
  void* mpOutlet;  // +0x28
  void* mpCanvas;  // +0x2c
  unsigned int mOpaque30[3];
};
extern void* spGroupClass;          // 0x1675520
// ---- items of slice s00a52080 end

// unnamed retail callees and globals that name local stubs (address in the comment)

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

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* __cdecl FUN_00a529e0(int a, int b, int argc, int* argv);  // 0x00a529e0 (stays in the slice: not this object's)
void __cdecl FUN_00a52a90(char* obj);  // 0x00a52a90 (stays in the slice: not this object's)

// @ 0x00a52ab0
void* __cdecl groupsize_new()
{
  GroupsizeObject* p = (GroupsizeObject*)EA::Audio::Eapd::pd_new(spGroupsizeClass);
  p->mpOutlet = EA::Audio::Eapd::outlet_new(p, gFloatSymbol);
  p->mpCanvas = EA::Audio::Eapd::canvas_getcurrentinstance();
  return p;
}

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
namespace EA {
namespace Audio {
namespace Eapd {
bool a_group_setup()
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
}
}
}  // namespace EA::Audio::Eapd
