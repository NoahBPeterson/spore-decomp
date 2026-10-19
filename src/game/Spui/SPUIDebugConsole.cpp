// src/game/Spui/SPUIDebugConsole.cpp -- migrated from slice(s) s00802a30, s008019f0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIDebugConsole.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <intrin.h>

// ---- items of slice s00802a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_164bee8;
#define VFN(p, off) (*(void***)(p))[((off) >> 2)]
void* __cdecl SP_WindowManager();
void  __cdecl FUN_00969ae0(float v);
struct cSPUILayout_s0080_2a30 {
  void* FindWindowByID(uint32_t id, int recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  bool Init();
  void Shutdown(bool recursive);  // 0x00811ad0 (cSPUILayout::Shutdown)
};
struct Dbg {
  char data[0x50];
  __declspec(noinline) void Show(int show);   // 0x00802a30
  __declspec(noinline) bool IsEnabled();      // 0x00802b20
  void OnShow(int a, int b);                  // 0x00802fd0
  void OnToggle(int a);                       // 0x00802ff0
};
struct C_802b80 { char data[0x50]; void f(); };
struct DbgOut { void Output(const char* a, const char* b); void Forward(const char* a); };
// ---- items of slice s00802a30 end

// @ 0x00802910
void __cdecl DebugConsole_Clear(void* self)
{
  (void)self;
}

// @ 0x00802950
void __cdecl DebugConsole_Output(void* self, char* a, char* b)
{
  (void)self; (void)a; (void)b;
}

// @ 0x00802a30
void Dbg::Show(int show)
{
  char* p = (char*)this;
  void* w = ((cSPUILayout_s0080_2a30*)(p + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w)
    return;
  if (((void* (__thiscall*)(void*))VFN(w, 0x1c))(w) != (void*)0x14a4606)
    w = (void*)((void* (__thiscall*)(void*, void*, int))VFN(w, 0xf0))(w, (void*)0x14a4606, 1);
  if (!w)
    return;
  ((void (__thiscall*)(void*, int, int))VFN(w, 0x7c))(w, 1, show);
  void* w2 = ((cSPUILayout_s0080_2a30*)(p + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w2)
    w2 = 0;
  else if (((void* (__thiscall*)(void*))VFN(w2, 0x1c))(w2) != (void*)0x14a4608)
    w2 = (void*)((void* (__thiscall*)(void*, void*, int))VFN(w2, 0xf0))(w2, (void*)0x14a4608, 1);
  void* wm = SP_WindowManager();
  if (!wm || !w2)
    return;
  if (show) {
    ((void (__thiscall*)(void*, int, void*))VFN(wm, 0x4c))(wm, 0, w2);
    return;
  }
  void* cur = (void*)((void* (__thiscall*)(void*, int))VFN(wm, 0x48))(wm, 0);
  if (w2 == cur) {
    void* vt = *(void**)wm;
    void* def = (void*)((void* (__thiscall*)(void*))((void**)vt)[0x84 / 4])(wm);
    ((void (__thiscall*)(void*, int, void*))VFN(wm, 0x4c))(wm, 0, def);
  }
}

// @ 0x00802b20
bool Dbg::IsEnabled()
{
  char* p = (char*)this;
  void* w = ((cSPUILayout_s0080_2a30*)(p + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w)
    return false;
  if (((void* (__thiscall*)(void*))VFN(w, 0x1c))(w) != (void*)0x14a4606)
    w = (void*)((void* (__thiscall*)(void*, void*, int))VFN(w, 0xf0))(w, (void*)0x14a4606, 1);
  if (!w)
    return false;
  return (((uint32_t(__thiscall*)(void*))VFN(w, 0x28))(w) & 1) != 0;
}

// @ 0x00802b80
void C_802b80::f()
{
  if (g_164bee8 == 1.0f)
    return;
  g_164bee8 = 1.0f;
  char* p = (char*)this;
  int* win0 = *(int**)(p + 0x2c);
  uint32_t col = ((uint32_t(__thiscall*)(void*))VFN(win0, 0xa4))(win0);
  uint32_t packed = (((((int)(g_164bee8 * 255.0f) & 0xff) << 8) | ((col >> 0x10) & 0xff)) << 8 |
                     ((col >> 8) & 0xff)) << 8 | (col & 0xff);
  ((void (__thiscall*)(void*, uint32_t))VFN(win0, 0xac))(win0, packed);
  ((void (__thiscall*)(void*, uint32_t))VFN(win0, 0x90))(win0, packed);
  void* w1 = (void*)((void* (__thiscall*)(void*))VFN(SP_WindowManager(), 4))(SP_WindowManager());
  ((void (__thiscall*)(void*, void*))VFN(w1, 0xf0))(w1, (void*)0x14a4606);
  void* w2 = (void*)((void* (__thiscall*)(void*))VFN(SP_WindowManager(), 4))(SP_WindowManager());
  void* arr[2];
  arr[1] = (void*)((void* (__thiscall*)(void*, int, int))VFN(w2, 0xf0))(w2, 0x1945b27, 1);
  for (int i = 0; i < 2; i++) {
    void* q = arr[i];
    if (q && ((void* (__thiscall*)(void*))VFN(q, 0x10))(q)) {
      if (g_164bee8 <= 0.5f)
        ((void (__thiscall*)(void*))VFN(q, 0xec))(q);
      else
        ((void (__thiscall*)(void*))VFN(q, 0xe8))(q);
    }
  }
  FUN_00969ae0(g_164bee8);
}

// @ 0x00802cd0
int cSPUIDebugConsole_Init(void* self)
{
  if (*(void**)((char*)self + 0x24))
    return 1;
  if (!((cSPUILayout_s0080_2a30*)((char*)self + 0x10))->Init())
    return 1;
  return 1;
}

// @ 0x00802fb0
void DbgOut::Forward(const char* a)
{
  Output(a, "Console");
}

// @ 0x00802fd0
void Dbg::OnShow(int a, int b)
{
  if (b == 1)
    this->Show(a);
}

// @ 0x00802ff0
void Dbg::OnToggle(int a)
{
  if (a == 1) {
    bool b = (this->IsEnabled() == 0);
    this->Show(b);
  }
}
