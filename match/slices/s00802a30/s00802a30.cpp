// Spore decompilation - batch w2g6, slice s00802a30 (0x00802A30..0x00803A1F).
// cSPUIDebugConsole layout/init/message handling, cSPUIStringBinder ctor/dtor and the
// debug-console message thunks.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include <new>
#include "types.h"

#define VFN(p, off) (*(void***)(p))[((off) >> 2)]

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* f, int l);
void  __cdecl operator_delete(void* p);
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, int align, int a, int b, const char* f, int l);
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p);

void* __cdecl SP_WindowManager();
void* __cdecl EA_UTFWin_GetManager();
void  __cdecl FUN_00969ae0(float v);
void  __cdecl Vector_DoDestroyValues(void* a, void* b);

struct RCObj { virtual void r0(); virtual void Release(); };

// cSPUILayout interface (declared only)
struct cSPUILayout {
  void* FindWindowByID(uint32_t id, int recursive);
  bool Init();
  void Shutdown(bool recursive);
};
struct FixedBufferAlloc;

// ===========================================================================
// cSPUIDebugConsole core methods
// ===========================================================================
struct Dbg {
  char data[0x50];
  __declspec(noinline) void Show(int show);   // 0x00802a30
  __declspec(noinline) bool IsEnabled();      // 0x00802b20
  void OnShow(int a, int b);                  // 0x00802fd0
  void OnToggle(int a);                       // 0x00802ff0
};

// @ 0x00802a30
void Dbg::Show(int show) {
  char* p = (char*)this;
  void* w = ((cSPUILayout*)(p + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w)
    return;
  if (((void* (__thiscall*)(void*))VFN(w, 0x1c))(w) != (void*)0x14a4606)
    w = (void*)((void* (__thiscall*)(void*, void*, int))VFN(w, 0xf0))(w, (void*)0x14a4606, 1);
  if (!w)
    return;
  ((void (__thiscall*)(void*, int, int))VFN(w, 0x7c))(w, 1, show);
  void* w2 = ((cSPUILayout*)(p + 0x10))->FindWindowByID(0x14a4606, 1);
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
bool Dbg::IsEnabled() {
  char* p = (char*)this;
  void* w = ((cSPUILayout*)(p + 0x10))->FindWindowByID(0x14a4606, 1);
  if (!w)
    return false;
  if (((void* (__thiscall*)(void*))VFN(w, 0x1c))(w) != (void*)0x14a4606)
    w = (void*)((void* (__thiscall*)(void*, void*, int))VFN(w, 0xf0))(w, (void*)0x14a4606, 1);
  if (!w)
    return false;
  return (((uint32_t(__thiscall*)(void*))VFN(w, 0x28))(w) & 1) != 0;
}

// @ 0x00802fd0
void Dbg::OnShow(int a, int b) {
  if (b == 1)
    this->Show(a);
}

// @ 0x00802ff0
void Dbg::OnToggle(int a) {
  if (a == 1) {
    bool b = (this->IsEnabled() == 0);
    this->Show(b);
  }
}

// ===========================================================================
// @ 0x00802b80  apply the console alpha/colour
// ===========================================================================
extern float g_164bee8;
struct C_802b80 { char data[0x50]; void f(); };
void C_802b80::f() {
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

// ===========================================================================
// @ 0x00802cd0  cSPUIDebugConsole::Init  (partial skeleton)
// ===========================================================================
int cSPUIDebugConsole_Init(void* self) {
  if (*(void**)((char*)self + 0x24))
    return 1;
  if (!((cSPUILayout*)((char*)self + 0x10))->Init())
    return 1;
  return 1;
}

// ===========================================================================
// @ 0x00802fb0  one-arg Output forwarder
// ===========================================================================
struct DbgOut { void Output(const char* a, const char* b); void Forward(const char* a); };
void DbgOut::Forward(const char* a) {
  Output(a, "Console");
}

// ===========================================================================
// @ 0x00803020  cSPUIStringBinder::cSPUIStringBinder
// ===========================================================================
extern char sb_a[], sb_b[], sb_c[];
struct C_803020 {
  char data[0x50];
  C_803020* Ctor();
};
C_803020* C_803020::Ctor() {
  char* p = (char*)this;
  *(void**)(p + 4) = (void*)sb_a;
  *(void**)(p + 8) = (void*)sb_b;
  *(void**)(p + 0xc) = 0;
  (void)sb_c;
  return this;
}

// ===========================================================================
// @ 0x00803140  cSPUIDebugConsole destructor
// ===========================================================================
extern char dbg_c[], dbg_d[];
void  __cdecl cSPUILayout_Dtor_Extern(void*);
struct C_803140 {
  char data[0x50];
  void Dtor();
};
void C_803140::Dtor() {
  char* p = (char*)this;
  void* alloc = *(void**)(p + 0x48);
  *(void**)p = (void*)dbg_c;
  *(void**)(p + 4) = (void*)sb_b;
  *(void**)(p + 8) = (void*)dbg_d;
  if (alloc) {
    void* bi = *(void**)alloc;
    if (bi && (*(uint32_t*)((char*)bi + 0x10) & 0x40000000))
      ((void(__thiscall*)(void*))0x4bca10)(alloc);
    *(void**)alloc = 0;
    EASTL_allocator_deallocate(alloc);
  }
  EASTL_allocator_deallocate(*(void**)(p + 0x4c));
  Vector_DoDestroyValues(*(void**)(p + 0x30), *(void**)(p + 0x34));
  int v = *(int*)(p + 0x30);
  if (v && *(int*)(v - 4))
    EASTL_allocator_deallocate((void*)v);
  if (*(void**)(p + 0x2c)) ((RCObj*)*(void**)(p + 0x2c))->Release();
  if (*(void**)(p + 0x28)) ((RCObj*)*(void**)(p + 0x28))->Release();
  cSPUILayout_Dtor_Extern(p + 0x10);
  *(void**)(p + 8) = (void*)dbg_d;
  *(void**)(p + 4) = (void*)sb_b;
  *(void**)p = (void*)sb_b;
}

// ===========================================================================
// @ 0x00803220  cSPUIDebugConsole::DoMessage (partial skeleton)
// ===========================================================================
int cSPUIDebugConsole_DoMessage(void* self, void* msg, void* data) {
  (void)self; (void)msg; (void)data;
  return 0;
}

// ===========================================================================
// @ 0x00803730  message thunk: dispatch *msg to a's second virtual
// ===========================================================================
void __cdecl f_803730(void* a, void* b) {
  ((void (__thiscall*)(void*, void*, void*))VFN(a, 4))(a, *(void**)b, b);
}

// ===========================================================================
// @ 0x00803750  post a message through EA::UTFWin::GetManager
// ===========================================================================
void __cdecl f_803750(void* a, void* b) {
  uint32_t buf[7];
  *(void**)((char*)buf + 8) = *(void**)b;
  *(void**)((char*)buf + 0x18) = b;
  void* mgr = EA_UTFWin_GetManager();
  ((void (__thiscall*)(void*, int, void*, void*, int))VFN(mgr, 0x10))(mgr, 0, a, buf, 0);
}

// ===========================================================================
// @ 0x00803790  cSPUIDebugConsole cheat command handler (partial skeleton)
// ===========================================================================
struct CheatCtx { char pad[0x12]; uint8_t f11; };
struct Cmd {
  char data[0x40];
  void Handle(int cmd, void* ctx);
};
void Cmd::Handle(int cmd, void* ctx) {
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
