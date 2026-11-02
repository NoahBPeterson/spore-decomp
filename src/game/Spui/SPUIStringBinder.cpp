// src/game/Spui/SPUIStringBinder.cpp -- migrated from slice(s) s00802a30, s008019f0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIStringBinder.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <intrin.h>
#include "cSPUILayout.h"

// ---- items of slice s008019f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete(void* p);
bool __stdcall Sub_8026b0(const wchar_t* name, void* info);
struct C_802870 { unsigned f(unsigned arg); };
unsigned C_802870::f(unsigned arg) {
  if (arg != 0x2f009dd0)
    return 0;
  return ((char*)this - 4) ? (unsigned)(unsigned)this : 0u;
}
struct FileStream {
  void Ctor(void* path);                  // 0x00??????
  int  Open(int a, int b, int c, int d);
  void Write(void* data, int n);
  void Close();
  void Dtor();
};
int  __cdecl f_932580(void* p, int a, int b, int c);
void __cdecl File_Remove(const wchar_t*);
int  __cdecl f_686430(void*, void*);
struct C_801d80 { uint8_t f(void* param_2, int param_3, int param_4); };
// ---- items of slice s008019f0 end

// ---- items of slice s00802a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char sb_a[], sb_b[], sb_c[];
#define VFN(p, off) (*(void***)(p))[((off) >> 2)]
void* __cdecl EA_UTFWin_GetManager();
struct C_803020 {
  char data[0x50];
  C_803020* Ctor();
};
struct CheatCtx { char pad[0x12]; uint8_t f11; };
struct Cmd {
  char data[0x40];
  void Handle(int cmd, void* ctx);
};
// ---- items of slice s00802a30 end

// @ 0x00802870
uint8_t C_801d80::f(void* param_2, int param_3, int param_4)
{
  uint8_t result = 0;
  if (param_4 == 0x2393756) {
    char pathbuf[520];
    char fs[0x100];
    f_932580(pathbuf, 0, 0, 0);
    ((FileStream*)fs)->Ctor(pathbuf);
    if (((FileStream*)fs)->Open(2, 6, 1, 0)) {
      void* a = ((void* (__thiscall*)(void*))((*(void***)this)[0x18 / 4]))(this);
      int n = ((int(__thiscall*)(void*))((*(void***)a)[0x1c / 4]))(a);
      char buf[5];
      f_686430((void*)n, buf);
      ((void(__thiscall*)(void*, int, int))((*(void***)a)[0x30 / 4]))(a, n, n);
      ((FileStream*)fs)->Write((void*)n, n);
      ((FileStream*)fs)->Close();
      result = (uint8_t)Sub_8026b0((wchar_t*)pathbuf, param_2);
      File_Remove((wchar_t*)pathbuf);
      if (n && *(int*)(n - 4))
        operator_delete((void*)n);
    }
    ((FileStream*)fs)->Dtor();
  }
  return result;
}

// @ 0x00803020
C_803020* C_803020::Ctor()
{
  char* p = (char*)this;
  *(void**)(p + 4) = (void*)sb_a;
  *(void**)(p + 8) = (void*)sb_b;
  *(void**)(p + 0xc) = 0;
  (void)sb_c;
  return this;
}

// @ 0x00803220
int cSPUIDebugConsole_DoMessage(void* self, void* msg, void* data)
{
  (void)self; (void)msg; (void)data;
  return 0;
}

// @ 0x00803730
void __cdecl f_803730(void* a, void* b)
{
  ((void (__thiscall*)(void*, void*, void*))VFN(a, 4))(a, *(void**)b, b);
}

// @ 0x00803750
void __cdecl f_803750(void* a, void* b)
{
  uint32_t buf[7];
  *(void**)((char*)buf + 8) = *(void**)b;
  *(void**)((char*)buf + 0x18) = b;
  void* mgr = EA_UTFWin_GetManager();
  ((void (__thiscall*)(void*, int, void*, void*, int))VFN(mgr, 0x10))(mgr, 0, a, buf, 0);
}

// @ 0x00803790
void Cmd::Handle(int cmd, void* ctx)
{
  char* p = (char*)this;
  CheatCtx* c = (CheatCtx*)ctx;
  uint32_t key = (uint32_t)cmd + 0xf841dbbc;
  if (key > 3)
    return;
  switch (key) {
    case 0:
      if (c->f11)
        return;
      c->f11 = 1;
      break;
    case 1:
      break;
    case 2:
      if (c->f11)
        c->f11 = 0;
      break;
    case 3:
      break;
  }
  (void)p;
}
