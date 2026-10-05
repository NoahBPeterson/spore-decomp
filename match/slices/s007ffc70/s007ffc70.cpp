// Spore decompilation - batch w2g6, slice s007ffc70 (0x007FFC70..0x00801A0F).
// UTFWin UI behavior-predicate / cursor-attachment / layout helpers.
// Flags: /O2 /MD /Gy /TP (default; SSE2 is the cl 15.00 x86 default).
#include <new>
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// generic helpers (external; direct calls only, never defined here)
// ---------------------------------------------------------------------------
#define VFN(p, off) (*(void***)(p))[((off) >> 2)]

void* __stdcall f_9512c0();
void* __cdecl f_9512d0(unsigned size, int align, const char* name, void* alloc);
void  __cdecl f_951330(void* p);              // MultiHeapObject::operator delete
void* __cdecl f_883860();                     // EA::Messaging::GetServer
void* __cdecl f_920090();                     // messaging registration
void* __cdecl f_67dd00();                     // SP::AppSystem
void* __cdecl f_67dcf0();                     // SP::Canvas
void* __cdecl f_7ffa50();
uint8_t __cdecl f_809700(void* a, void* b, void* c);
void  __fastcall f_8027e0(void* self);
void  __cdecl f_804f10(float a, float b);
void  __cdecl f_804ed0(float* a, float* b);
bool  __cdecl f_806a60(void* a, void* b, int c, int d);
void* __cdecl f_805070(uint32_t id);          // SPUIHelpers::GetLayoutManager
void* __cdecl f_80620(void* manager);         // cSPUILayoutManager::GetWorldMainWindow
void* __cdecl f_962a10(void* p);              // UI::Window::Window
void  __fastcall f_800060_base(void* p);

struct IFactoryObj {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void* v3(uint32_t id);
};
struct MsgServer { virtual void m0(); virtual void Reg(const void* p, int flags); };
struct AppObj { virtual void a0();  virtual void a1();  virtual void a2();  virtual void a3();
                virtual void a4();  virtual void a5();  virtual void a6();  virtual void a7();
                virtual void a8();  virtual void a9();  virtual void a10(); virtual void a11();
                virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
                virtual void a16(); };
struct CanvasObj { virtual void c0();  virtual void c1();  virtual void c2();  virtual void c3();
                   virtual void c4();  virtual void c5();  virtual void c6();  virtual void c7();
                   virtual void c8();  virtual void c9();  virtual void c10(); virtual void c11();
                   virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
                   virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
                   virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
                   virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
                   virtual void c28(); virtual void c29(); virtual void c30(); };
struct RCBase { virtual void rc0(); virtual void Release(); };
struct cSPUILayout { void* FindWindowByID(uint32_t id, bool recursive); };

struct cSPUIFrameSequencer { cSPUIFrameSequencer(); };
struct cSPUIBehaviorWinEventBase { cSPUIBehaviorWinEventBase(int, int, int); };
struct cSPUIBehaviorWinBoolStateEvent { cSPUIBehaviorWinBoolStateEvent(int, int, int, int); };
struct cSPUIBehaviorTimeFunctionSmoothRamp { cSPUIBehaviorTimeFunctionSmoothRamp(float, float); };
struct cSPUIBehaviorTimeFunctionDampedPeriodic { cSPUIBehaviorTimeFunctionDampedPeriodic(int); };

extern float g_1471064;
extern bool  g_164bbd8;
extern bool  g_164bbd9;
extern float g_15435bc, g_15435c0;
extern char g_1543400[], g_1543404[], g_1543408[], g_154340c[];
extern char g_1543440[], g_154343c[], g_1543438[], g_1543410[], g_1543414[];
extern char g_1543418[], g_154341c[], g_1543420[], g_1543424[], g_154342c[];
extern char g_1543428[], g_1543430[], g_1543434[], g_1543444[], g_1543448[];
extern char g_154344c[], g_1543450[], g_1543454[], g_1543458[], g_154345c[];
extern char g_1543460[], g_1543464[], g_1543468[], g_154346c[], g_1543470[];
extern char dv_a[], dv_b[];
extern char ca_a[], ca_b[], ca_c[];
extern char cl_a[], cl_b[], cl_c[], cl_d[];

// ===========================================================================
// @ 0x007FFC70  cSPUIBehaviorPredicateWinState::Evaluate (vtable slot 6)
// ===========================================================================
struct cSPUIBehaviorPredicateWinState {
  char pad0[0x14];
  void* mpQueryWindow;        // +0x14
  uint32_t mWinStateQuery;    // +0x18
  char pad1c[0x8];
  uint32_t mQueryHexParam;    // +0x24
  char pad28[4];
  uint8_t Evaluate();
};
// @ 0x007ffc70
uint8_t cSPUIBehaviorPredicateWinState::Evaluate() {
  void* p = f_7ffa50();
  if (!p)
    return 0;
  void* p3 = (void*)((void* (__thiscall*)(void*))VFN(p, 0x14))(p);
  uint8_t r = 0;
  switch (mWinStateQuery) {
    case 0:
      return (uint8_t)(((uint32_t(__thiscall*)(void*))VFN(p, 0x28))(p) & 1);
    case 1:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x28))(p) >> 1) & 1);
    case 2:
      if (p3)
        return (uint8_t)(((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 1) == p);
      break;
    case 3:
      if (p3)
        return (uint8_t)(((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 0) == p);
      break;
    case 4:
      if (p3) {
        if (((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 0) == p)
          return 1;
        return (uint8_t)(((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 1) == p);
      }
      break;
    case 5:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 2) & 1);
    case 6: {
      uint32_t v = ((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p);
      if (!(v & 1))
        return 0;
      v = ((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p);
      if ((v & 0x1e) == 0)
        return 1;
      return 0;
    }
    case 7:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 3) & 1);
    case 8:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 1) & 1);
    case 9:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 4) & 1);
    case 10: {
      uint32_t stack20 = 0, stack1c = 0;
      ((void (__thiscall*)(void*, uint32_t*))VFN(p3, 0x3c))(p3, &stack20);
      ((void (__thiscall*)(void*, uint32_t*, uint32_t*, int))VFN(p, 0xc4))(p, &stack1c, &stack20, 0);
      uint32_t* q = (uint32_t*)((uint32_t* (__thiscall*)(void*))VFN(p, 0x38))(p);
      uint32_t s14 = q[0], s18 = q[1], s1c = q[2], s20 = q[3];
      return (uint8_t)f_809700(&s14, 0, 0);
    }
    case 0xb:
      if (mQueryHexParam != 0x7fffffff) {
        void* r2 = (void*)((void* (__thiscall*)(void*, uint32_t, int))VFN(p, 0xf0))(p, mQueryHexParam, 0);
        return (uint8_t)(r2 != 0);
      }
      break;
    case 0xc:
      if (mQueryHexParam != 0x7fffffff) {
        p = (void*)((void* (__thiscall*)(void*))VFN(p, 0x10))(p);
        if (p) {
          while (!r) {
            uint32_t id = ((uint32_t(__thiscall*)(void*))VFN(p, 0x1c))(p);
            r = (uint8_t)(id == mQueryHexParam);
          }
        }
      }
      break;
    case 0xd: {
      uint32_t id = ((uint32_t(__thiscall*)(void*))VFN(p, 0x30))(p);
      return (uint8_t)(mQueryHexParam == id);
    }
    case 0xe: {
      uint32_t id = ((uint32_t(__thiscall*)(void*))VFN(p, 0xa4))(p);
      return (uint8_t)(mQueryHexParam == id);
    }
    case 0xf:
      if (mpQueryWindow) {
        void* r2 = (void*)((void* (__thiscall*)(void*))VFN(mpQueryWindow, 0x44))(mpQueryWindow);
        return (uint8_t)(r2 != 0);
      }
      break;
    case 0x10:
    case 0x11:
    case 0x12: {
      void* a = mpQueryWindow ? (void*)((void* (__thiscall*)(void*))VFN(mpQueryWindow, 0x1c))(mpQueryWindow) : 0;
      void* b = mpQueryWindow ? (void*)((void* (__thiscall*)(void*))VFN(mpQueryWindow, 0x58))(mpQueryWindow) : 0;
      if (a && b) {
        if (mWinStateQuery == 0x10)
          return (uint8_t)((uint32_t(__thiscall*)(void*, void*))VFN(b, 0xf8))(b, a);
        uint32_t u = ((uint32_t(__thiscall*)(void*, void*))VFN(a, 0xf8))(a, b);
        if (mWinStateQuery == 0x11)
          return (uint8_t)u;
        if ((uint8_t)u)
          return 1;
        uint8_t c = (uint8_t)((uint32_t(__thiscall*)(void*, void*))VFN(b, 0xf8))(b, a);
        return c ? 1 : 0;
      }
      break;
    }
    case 0x13: {
      uint32_t s20 = 0;
      f_809700(p, 0, &s20);
      r = (uint8_t)s20;
      break;
    }
    default:
      break;
  }
  return r;
}

// ===========================================================================
// @ 0x00800060  deleting destructor (vtable slot 2)
// ===========================================================================
struct C_800060 { void* ScalarDtor(uint8_t flags); };
// @ 0x00800060
void* C_800060::ScalarDtor(uint8_t flags) {
  *(void**)this = (void*)dv_a;
  *(void**)((char*)this + 4) = (void*)dv_b;
  _ReadWriteBarrier();
  RCBase* p = *(RCBase**)((char*)this + 0x1c);
  if (p) {
    *(void**)((char*)this + 0x1c) = 0;
    p->Release();
  }
  p = *(RCBase**)((char*)this + 0x1c);
  if (p)
    p->Release();
  f_800060_base(this);
  if (flags & 1)
    f_951330(this);
  return this;
}

// ===========================================================================
// @ 0x008005F0  UI registration one-time initializer
// ===========================================================================
#define REGMSG(g) ((MsgServer*)f_920090())->Reg((g), 0)
// @ 0x008005f0
void f_8005f0() {
  if (!g_164bbd9) {
    g_164bbd9 = true;
    g_164bbd8 = (f_883860() == 0);
    REGMSG(g_1543400);
    REGMSG(g_1543404);
    REGMSG(g_1543408);
    REGMSG(g_154340c);
    REGMSG(g_1543440);
    REGMSG(g_154343c);
    REGMSG(g_1543438);
    REGMSG(g_1543410);
    REGMSG(g_1543414);
    REGMSG(g_1543418);
    REGMSG(g_154341c);
    REGMSG(g_1543420);
    REGMSG(g_1543424);
    REGMSG(g_154342c);
    REGMSG(g_1543428);
    REGMSG(g_1543430);
    REGMSG(g_1543434);
    REGMSG(g_1543444);
    REGMSG(g_1543448);
    REGMSG(g_154344c);
    REGMSG(g_1543450);
    REGMSG(g_1543454);
    REGMSG(g_1543458);
    REGMSG(g_154345c);
    REGMSG(g_1543460);
    REGMSG(g_1543464);
    REGMSG(g_1543468);
    REGMSG(g_154346c);
    REGMSG(g_1543470);
  }
}

// ===========================================================================
// factory thunks
// ===========================================================================
// @ 0x008008b0
void* __stdcall f_8008b0(int unused, void* alloc) {
  if (!alloc)
    alloc = f_9512c0();
  cSPUIFrameSequencer* p = (cSPUIFrameSequencer*)f_9512d0(0x60, 4, "UTFWin/cSPUIFrameSequencer", alloc);
  if (p) {
    p = new (p) cSPUIFrameSequencer();
    if (p)
      return ((IFactoryObj*)((char*)p + 8))->v3(0x105a94b);
  }
  return 0;
}
// @ 0x00800ea0
void* __stdcall f_800ea0(int unused, void* alloc) {
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorWinEventBase* p =
      (cSPUIBehaviorWinEventBase*)f_9512d0(0x8c, 4, "UTFWin/cSPUIBehaviorWinEventBase", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorWinEventBase(10, 0x7fffffff, 0);
    if (p)
      return ((IFactoryObj*)p)->v3(0x2f009dd0);
  }
  return 0;
}
// @ 0x00800ef0
void* __stdcall f_800ef0(int unused, void* alloc) {
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorWinBoolStateEvent* p =
      (cSPUIBehaviorWinBoolStateEvent*)f_9512d0(0x90, 4, "UTFWin/cSPUIBehaviorWinBoolStateEvent", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorWinBoolStateEvent(1, 10, 0x7fffffff, 0);
    if (p)
      return ((IFactoryObj*)p)->v3(0x2f009dd0);
  }
  return 0;
}
// @ 0x008010a0
void* __stdcall f_8010a0(int unused, void* alloc) {
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorTimeFunctionSmoothRamp* p =
      (cSPUIBehaviorTimeFunctionSmoothRamp*)f_9512d0(0x48, 4, "UTFWin/cSPUIBehaviorTimeFunctionSmoothRamp", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorTimeFunctionSmoothRamp(g_1471064, g_1471064);
    if (p)
      return ((IFactoryObj*)p)->v3(0xee3f516e);
  }
  return 0;
}
// @ 0x00801100
void* __stdcall f_801100(int unused, void* alloc) {
  if (!alloc)
    alloc = f_9512c0();
  cSPUIBehaviorTimeFunctionDampedPeriodic* p =
      (cSPUIBehaviorTimeFunctionDampedPeriodic*)f_9512d0(0x50, 4, "UTFWin/cSPUIBehaviorTimeFunctionDampedPeriodic", alloc);
  if (p) {
    p = new (p) cSPUIBehaviorTimeFunctionDampedPeriodic(1);
    if (p)
      return ((IFactoryObj*)p)->v3(0xee3f516e);
  }
  return 0;
}

// ===========================================================================
// @ 0x008011F0  cSPUICursorAttachmentLayout destructor
// ===========================================================================
struct cSPUIPropertyLayoutBase { void BaseDtor(); };
struct C_8011f0 : cSPUIPropertyLayoutBase { void Dtor(); };
// @ 0x008011f0
void C_8011f0::Dtor() {
  *(void**)this = (void*)ca_a;
  *(void**)((char*)this + 4) = (void*)ca_b;
  *(void**)((char*)this + 0x78) = (void*)ca_c;
  BaseDtor();
}

// ===========================================================================
// @ 0x00801210  adjustor thunk -> cSPUILayout::FindWindowByID
// ===========================================================================
struct C_801210 { void* Thunk(); };
// @ 0x00801210
void* C_801210::Thunk() {
  return ((cSPUILayout*)((char*)this - 0x6c))
      ->FindWindowByID(*(uint32_t*)((char*)this - 0x30), true);
}

// ===========================================================================
// @ 0x00801280  cSPUICursorAttachmentLayout constructor
// ===========================================================================
struct cSPUIPropertyLayoutCtor { void BaseCtor(); };
struct C_801280 : cSPUIPropertyLayoutCtor { void* Ctor(); };
// @ 0x00801280
void* C_801280::Ctor() {
  BaseCtor();
  *(void* volatile*)((char*)this + 0x78) = (void*)cl_a;
  *(void* volatile*)this = (void*)cl_b;
  *(void* volatile*)((char*)this + 4) = (void*)cl_c;
  *(void* volatile*)((char*)this + 0x78) = (void*)cl_d;
  return this;
}

// ===========================================================================
// @ 0x00801330
// ===========================================================================
int __stdcall f_801330(void* p, unsigned n) {
  if (p) {
    if (n < 1)
      return 0;
    *(uint32_t*)p = 0x2393756;
  }
  return 1;
}

// ===========================================================================
// @ 0x00801360 / 0x00801380
// ===========================================================================
struct C_801360 { char pad[0x58]; int mCount; void Show(); void Hide(); };
// @ 0x00801360
void C_801360::Show() {
  if (++mCount == 1) {
    f_8027e0(this);
    void* a = f_67dd00();
    ((void (__thiscall*)(void*, int))VFN(a, 0x40))(a, 1);
  }
}
// @ 0x00801380
void C_801360::Hide() {
  if (mCount > 0) {
    if (--mCount == 0) {
      void* a = f_67dd00();
      ((void (__thiscall*)(void*, int))VFN(a, 0x40))(a, 0);
      f_8027e0(this);
    }
  }
}

// ===========================================================================
// @ 0x008013D0
// ===========================================================================
struct C_8013d0 { char pad[0x40]; uint8_t m40; bool Set40(uint8_t v); };
// @ 0x008013d0
bool C_8013d0::Set40(uint8_t v) {
  if (m40 != v) {
    m40 = v;
    void* c = f_67dcf0();
    ((void (__thiscall*)(void*, uint32_t))VFN(c, 0x78))(c, m40);
  }
  return true;
}

// ===========================================================================
// @ 0x00801420 / 0x00801450
// ===========================================================================
// @ 0x00801420
void __stdcall f_801420(int a, int b) {
  f_804f10((float)a, (float)b);
}
// @ 0x00801450
void __stdcall f_801450(int* p1, int* p2) {
  float x, y;
  f_804ed0(&y, &x);
  *p1 = (int)x;
  *p2 = (int)y;
}

// ===========================================================================
// @ 0x008014C0  cursor-attachment layout initialize
// ===========================================================================
struct C_8014c0 {
  char pad0[0x28];
  uint8_t m28;          // +0x28
  char pad29[0x23];
  void* m4c;            // +0x4c
  int Init();
};
// @ 0x008014c0
int C_8014c0::Init() {
  if (m28)
    return 1;
  void* mem = f_9512d0(0x20c, 4, "UI/UI/Cursor info parent window", f_9512c0());
  void* win = 0;
  if (mem) {
    f_962a10(mem);
    *(void**)mem = (void*)0;
    *(void**)((char*)mem + 4) = (void*)0;
    win = mem;
  }
  void* old = m4c;
  if (win != old) {
    if (win)
      ((void (__thiscall*)(void*))VFN(win, 0))(win);
    m4c = win;
    if (old)
      ((void (__thiscall*)(void*))VFN(old, 4))(old);
  }
  ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 0x10, 1);
  ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 1, 0);
  ((void (__thiscall*)(void*, int))VFN(m4c, 0xac))(m4c, 0);
  void* mainWin = f_80620(f_805070(0x5b598fa));
  ((void (__thiscall*)(void*, void*))VFN(mainWin, 0xd8))(mainWin, m4c);
  ((void (__thiscall*)(void*, float, float))VFN(m4c, 0x68))(m4c, 1.0f, 1.0f);
  m28 = 1;
  return 1;
}

// ===========================================================================
// @ 0x008016E0
// ===========================================================================
struct C_8016e0 { char pad[0x48]; void* m48; void* m4c; void Move(float x, float y); };
// @ 0x008016e0
void C_8016e0::Move(float x, float y) {
  if (!m4c)
    return;
  float px = g_15435bc + x;
  float py = g_15435c0 + y;
  void* mainWin = f_80620(f_805070(0x5b598fa));
  if (m48) {
    void* w = (void*)((void* (__thiscall*)(void*))VFN(m48, 0x18))(m48);
    if (w) {
      void* a = (void*)((void* (__thiscall*)(void*))VFN(w, 0x18))(w);
      void* b = (void*)((void* (__thiscall*)(void*))VFN(mainWin, 0x34))(mainWin);
      void* c = (void*)((void* (__thiscall*)(void*))VFN(a, 0x38))(a);
      float cw = *(float*)((char*)c + 8) + px;
      if (*(float*)((char*)b + 8) <= cw && cw != *(float*)((char*)b + 8))
        px = x - (*(float*)((char*)c + 8) + g_15435bc);
      float ch = *(float*)((char*)b + 0xc) - (*(float*)((char*)c + 0xc) + py);
      if (ch < 0.0f)
        py = ch + py;
    }
  }
  ((void (__thiscall*)(void*, float, float))VFN(m4c, 0x64))(m4c, px, py);
  ((void (__thiscall*)(void*, void*))VFN(mainWin, 0xe8))(mainWin, m4c);
}

// ===========================================================================
// @ 0x008017F0
// ===========================================================================
struct C_8017f0 { char pad[0x48]; void* m48; void* m4c; bool Set(void* p); };
// @ 0x008017f0
bool C_8017f0::Set(void* p) {
  void* cur = m48;
  if (p != cur) {
    if (cur) {
      void* w = (void*)((void* (__thiscall*)(void*))VFN(cur, 0x18))(cur);
      if (w) {
        ((void (__thiscall*)(void*, int, int))VFN(w, 0x7c))(w, 1, 0);
        ((void (__thiscall*)(void*, void*))VFN(m4c, 0xdc))(m4c, w);
      }
      ((void (__thiscall*)(void*))VFN(cur, 0x10))(cur);
    }
    ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 1, 0);
    if (m48) {
      void* old = m48;
      m48 = 0;
      ((void (__thiscall*)(void*))VFN(old, 4))(old);
    }
    if (p) {
      if (((uint8_t (__thiscall*)(void*))VFN(p, 0xc))(p)) {
        void* t = (void*)((void* (__thiscall*)(void*))VFN(p, 0x18))(p);
        if (t) {
          m48 = p;
          ((void (__thiscall*)(void*, void*))VFN(m4c, 0xd8))(m4c, t);
          ((void (__thiscall*)(void*, int, int))VFN(t, 0x7c))(t, 1, 1);
          ((void (__thiscall*)(void*, int, int))VFN(m4c, 0x7c))(m4c, 1, 1);
          return true;
        }
        ((void (__thiscall*)(void*))VFN(p, 0x10))(p);
      }
      return false;
    }
  }
  return true;
}

// ===========================================================================
// @ 0x00801950
// ===========================================================================
struct C_801950 { char pad[0x50]; void* m50; void* m54; bool Run(int a); };
// @ 0x00801950
bool C_801950::Run(int a) {
  if (m50 && m54)
    return f_806a60(m50, m54, a, -1);
  return false;
}

// ===========================================================================
// @ 0x00801980
// ===========================================================================
struct C_801980 { char pad[0x44]; uint8_t m44; char pad45[0xb]; void* m50; void Set(bool v); };
// @ 0x00801980
void C_801980::Set(bool v) {
  m44 = (uint8_t)v;
  if (m50) {
    if (v) {
      int a;
      ((void (__thiscall*)(void*, int*, int*))VFN(this, 0x34))(this, (int*)&v, &a);
      ((void (__thiscall*)(void*, float, float))VFN(m50, 0x64))(m50, (float)a, (float)*(int*)&v);
    } else {
      f_8027e0(this);
    }
    ((void (__thiscall*)(void*, int, int))VFN(m50, 0x7c))(m50, 1, m44);
  }
}
