// Slice s007f3380: Sims3::UI IME composition / candidate-list / proxy methods.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>
#include <intrin.h>

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

// ---------------------------------------------------------------------------
// Sims3::UI::IMEComposition::HandleMessage: ecx is a secondary subobject whose
// primary object lives at this-0x658.
// ---------------------------------------------------------------------------
struct IMEComp {
  bool HandleMessage(int msg, void* arg);
};

// @ 0x007F36E0
bool IMEComp::HandleMessage(int msg, void* arg) {
  switch (msg) {
    case 0x2ac44c14: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x94))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44c1a: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x98))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44c1b: {
      void* s = (char*)this - 0x658;
      ((void(__thiscall*)(void*))VSLOT(s, 0x8c))(s);
      break;
    }
    default:
      break;
  }
  return true;
}

// ---------------------------------------------------------------------------
// Sims3::UI::IMECandidateList::HandleMessage: primary object at this-0x20c.
// ---------------------------------------------------------------------------
struct IMECand {
  bool HandleMessage(int msg, void* arg);
};

// @ 0x007F4170
bool IMECand::HandleMessage(int msg, void* arg) {
  switch (msg) {
    case 0x2ac44ed8: {
      void* s = (char*)this - 0x20c;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x88))(s, *(int*)((char*)arg + 8));
      break;
    }
    case 0x2ac44ef0: {
      void* s = (char*)this - 0x20c;
      ((void(__thiscall*)(void*, int))VSLOT(s, 0x8c))(s, *(int*)((char*)arg + 8));
      break;
    }
    default:
      break;
  }
  return true;
}

// ---------------------------------------------------------------------------
// 0x007F3BE0: push a subobject value through its vtable.
// ---------------------------------------------------------------------------
struct SubObj {
  void* Get();
};

struct IMEComp3 {
  char pad[0x20c];
  SubObj mSub;  // +0x20c
  void Helper(int param);
};

// @ 0x007F3BE0
void IMEComp3::Helper(int param) {
  if (param) {
    SubObj* p = &mSub;
    void* r = p->Get();
    ((void(__thiscall*)(void*, void*, int))VSLOT(p, 0x8c))(p, r, 1);
  }
}

// ---------------------------------------------------------------------------
// Sims3::UI::IMEProxy::Shutdown.
// ---------------------------------------------------------------------------
struct IMEProxy2 {
  char pad0[8];
  bool mbInitialized;          // +0x08
  char pad1[7];
  void* mpMessageServer;       // +0x10
  char pad2[0xc];
  void* mpIMEServer;           // +0x20
  void* mpWinMgr;              // +0x24
  char pad3[8];
  void* mpWinComposition;      // +0x30
  char pad4[8];
  void* mpWinCandidateList;    // +0x3c
  void ShutdownCandidateList();
  void ShutdownCandidateListImpl();
  void ShutdownComposition();
  bool Shutdown();
};

// @ 0x007F4250
bool IMEProxy2::Shutdown() {
  if (!mbInitialized) return true;
  bool hasCand = mpWinCandidateList != 0;
  mbInitialized = false;
  if (hasCand) ShutdownCandidateList();
  if (mpWinComposition) ShutdownComposition();
  ((void(__thiscall*)(void*, int))VSLOT(mpIMEServer, 0x14))(mpIMEServer, 0);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44c0e, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44c11, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44ed1, 0xffffd8f1);
  ((void(__thiscall*)(void*, void*, int, int))VSLOT(mpMessageServer, 0x2c))(
      mpMessageServer, this, 0x2ac44ed4, 0xffffd8f1);
  return true;
}

// ---------------------------------------------------------------------------
// 0x007F3B00 - static text-size helper.
// ---------------------------------------------------------------------------
struct TS {
  void LayoutLine(int text, int style, float a, float b, int len);
  void* GetLineLayout();
};

// @ 0x007F3B00
void* CalculateTextSize(void* out, int text, int style, int len, void* typesetter) {
  if (text != 0 && len != 0) {
    TS* ts = (TS*)typesetter;
    ts->LayoutLine(text, style, 0.0f, 0.0f, len);
    char* ll = (char*)ts->GetLineLayout();
    *(float*)out = *(float*)(ll + 0x98);
    *(float*)((char*)out + 4) = *(float*)(ll + 0xa0) - *(float*)(ll + 0xa4);
    return out;
  }
  *(float*)out = 0.0f;
  *(float*)((char*)out + 4) = 0.0f;
  return out;
}

// ---------------------------------------------------------------------------
// 0x007F3A90 - IMEComposition::SetWindowColors.
// ---------------------------------------------------------------------------
struct IMECompColors {
  char pad0[4];
  char mAt4[4];        // +0x04 (subobject with a vtable)
  char pad1[0x20c - 8];
  char mAt20c[4];      // +0x20c (subobject with a vtable)
  char pad2[0x6a8 - 0x210];
  int c6a8;            // +0x6a8
  int c6ac;            // +0x6ac
  int c6b0;            // +0x6b0
  int c6b4;            // +0x6b4
  void SetWindowColors();
};

// @ 0x007F3A90
void IMECompColors::SetWindowColors() {
  char* p = mAt20c;
  c6ac = (int)0xff000000;
  c6b0 = (int)0xff000000;
  c6a8 = 0xffffffff;
  c6b4 = 0xff0000f0;
  ((void(__thiscall*)(void*, int, int))VSLOT(p, 0x20))(p, 0, (int)0xff000000);
  ((void(__thiscall*)(void*, int, int))VSLOT(p, 0x20))(p, 1, (int)0xffefefef);
  ((void(__thiscall*)(void*, int))VSLOT(mAt4, 0xac))(mAt4, -1);
}

// ---------------------------------------------------------------------------
// 0x007F3B70 - IMEComposition::OnChar.
// ---------------------------------------------------------------------------
extern void* UTFWinGetMgr();

struct IMEC {
  char pad[0x68c];
  void* p68c;   // +0x68c
  bool OnChar(int, unsigned short ch);
};

// @ 0x007F3B70
bool IMEC::OnChar(int, unsigned short ch) {
  if (p68c) {
    struct L {
      int a;
      int b;
      int ch;
      int c;
    } l;
    l.a = 5;
    l.b = 0;
    l.ch = ch;
    l.c = 0;
    void* mgr = UTFWinGetMgr();
    ((void(__thiscall*)(void*, int, void*, void*, int))VSLOT(mgr, 0x10))(
        mgr, 0, (char*)p68c + 4, &l, 0);
    ((void(__thiscall*)(void*))VSLOT(this, 0x8c))(this);
  }
  return true;
}

// @ 0x007F3380
void IMEProxy2::ShutdownCandidateListImpl() {
  if (mpWinCandidateList != 0) {
    void* cand4 = (char*)mpWinCandidateList + 4;
    void* r = ((void*(__thiscall*)(void*))VSLOT(mpWinMgr, 4))(mpWinMgr);
    ((void(__thiscall*)(void*))VSLOT(mpWinCandidateList, 0x1c))(mpWinCandidateList);
    ((void(__thiscall*)(void*, void*))VSLOT(r, 0xdc))(r, cand4);
    void* p = mpWinCandidateList;
    if (p != 0) {
      mpWinCandidateList = 0;
      ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
    }
  }
}

// ===========================================================================
// Sims3::UI IME reconstruction (0x007F33D0 .. 0x007F423E).
//
// Objects come from the retail EA::UTFWin::Window / WinTextEdit hierarchy.
// The embedded window subobject's vptr lives at +4 and a second Window-derived
// subobject at +0x20c; virtual slots go through VSLOT so the emitted call
// sequences match the originals.  Class names are placeholders.
// ===========================================================================

struct Vec2   { float x, y; };
struct RectF  { float x, y, w, h; };
struct Vec4f  { float x, y, z, w; };
struct Rect5  { float x, y, z, w, h; };

// Real entry points (relocations are masked by chk; equiv binds by VA).
void __cdecl WindowCtor(void* self);                       // 0x00962a10
void __cdecl WindowDtor(void* self);                       // 0x00962740
void __cdecl WindowShutdown(void* self);                   // 0x00961e80
void __cdecl WinTextEditInit(void* self);                  // 0x0098cc70
void __cdecl WinTextEditShutdown(void* self);              // 0x0098c520
void __cdecl WindowInitialize(void* self);                 // 0x00b1fbf0
void* __cdecl GetStyleManagerStub(int a);                  // 0x00885bd0
const void* __cdecl GetStyleStub();                        // 0x00894670
void* __cdecl GetMessageServerStub();                      // 0x0067dcc0
void* __cdecl GetFontServerStub(int a);                    // 0x00885a60
void* __cdecl Fun9512c0();                                 // 0x009512c0
void* __cdecl Fun9512d0(int size, int a, const char* name, void* b);  // 0x009512d0
void* __cdecl WinGridCtor(void* self);                     // 0x009770e0
void* __cdecl Fun95fba0(void* self);                       // 0x0095fba0
void* __cdecl TypesetterGetLineLayout(void* self);         // 0x008976a0
void __cdecl TypesetterLayoutLine();                       // 0x0089db20
void __cdecl TypesetterPos90();                            // 0x0098e3a0
void __cdecl OperatorDelete(void* p);                      // 0x00f47380

// @ 0x007F33D0  Sims3::UI::IMEComposition::Init
bool __fastcall IMECompositionInit(void* self, void* /*unused*/, int /*arg*/) {
  if (!*(unsigned char*)((char*)self + 0x660)) {
  *(unsigned char*)((char*)self + 0x660) = 1;
  *(unsigned char*)((char*)self + 0x600) = 1;
  ((void(__thiscall*)(void*))WinTextEditInit)(self);
  void* sm = GetStyleManagerStub(1);
  const void* st = ((const void*(__thiscall*)(void*, unsigned, void*))GetStyleStub)(
      sm, *(unsigned*)((char*)self + 0xc0), 0);
  *(const void**)((char*)self + 0x6b8) = st;
  char* win = (char*)self + 4;
  void* w = ((void*(__thiscall*)(void*))VSLOT(win, 0x14))(win);
  void* q = ((void*(__thiscall*)(void*, int))VSLOT(w, 0x48))(w, 0);
  void* r = q ? ((void*(__thiscall*)(void*, unsigned))VSLOT(q, 0xc))(q, 0xeeee8218) : 0;
  void* a = r ? (void*)((char*)r - 4) : 0;
  void* old = *(void**)((char*)self + 0x688);
  if (a != old) {
    if (a) ((void(__thiscall*)(void*))VSLOT(a, 0))(a);
    *(void**)((char*)self + 0x688) = a;
    if (old) ((void(__thiscall*)(void*))VSLOT(old, 4))(old);
  }
  if (*(void**)((char*)self + 0x688)) {
    void* r2 = q ? ((void*(__thiscall*)(void*, unsigned))VSLOT(q, 0xc))(q, 0xcf428691) : 0;
    void* b = r2 ? (void*)((char*)r2 - 0x20c) : 0;
    void* old2 = *(void**)((char*)self + 0x68c);
    if (b != old2) {
      if (b) ((void(__thiscall*)(void*))VSLOT(b, 0))(b);
      *(void**)((char*)self + 0x68c) = b;
      if (old2) ((void(__thiscall*)(void*))VSLOT(old2, 4))(old2);
    }
    if (!*(void**)((char*)self + 0x68c)) {
      *(unsigned char*)((char*)self + 0x660) = 0;
      void* p = *(void**)((char*)self + 0x688);
      if (p) {
        *(void**)((char*)self + 0x688) = 0;
        ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
      }
      return false;
    }
    char* comp = (char*)*(void**)((char*)self + 0x68c);
    unsigned char ok = ((unsigned char(__thiscall*)(void*, int))VSLOT(comp + 0x20c, 0x48))(
        comp + 0x20c, 0x80);
    ((void(__thiscall*)(void*, int, int))VSLOT((char*)self + 0x20c, 0x44))(
        (char*)self + 0x20c, 0x80, ok);
    if (ok) ((void(__thiscall*)(void*, int))VSLOT(win, 0x5c))(win, 0);
  }
  ((void(__thiscall*)(void*))VSLOT(self, 0x90))(self);
  ((void(__thiscall*)(void*))VSLOT(self, 0x8c))(self);
  w = ((void*(__thiscall*)(void*))VSLOT(win, 0x14))(win);
  ((void(__thiscall*)(void*, void*, int))VSLOT(w, 0x4c))(w, win, 0);
  void* ms = GetMessageServerStub();
  *(void**)((char*)self + 0x65c) = ms;
  void* h = (char*)self + 0x658;
  ((void(__thiscall*)(void*, void*, int))VSLOT(ms, 0x24))(ms, h, 0x2ac44c14);
  ((void(__thiscall*)(void*, void*, int))VSLOT(ms, 0x24))(ms, h, 0x2ac44c1a);
  ((void(__thiscall*)(void*, void*, int))VSLOT(ms, 0x24))(ms, h, 0x2ac44c1b);
  }
  return true;
}

// @ 0x007F35D0  Sims3::UI::IMEComposition::Shutdown
void __fastcall IMECompositionShutdown(void* self) {
  if (*(unsigned char*)((char*)self + 0x660)) {
    char* win = (char*)self + 4;
    void* w = ((void*(__thiscall*)(void*))VSLOT(win, 0x14))(win);
    void* cl = *(void**)((char*)self + 0x688);
    if (cl) {
      if (w) {
        void* t = ((void*(__thiscall*)(void*))VSLOT((char*)cl + 4, 0x14))((char*)cl + 4);
        if (t) {
          void* r = ((void*(__thiscall*)(void*, int))VSLOT(w, 0x48))(w, 0);
          if (r == (void*)win ||
              ((unsigned char(__thiscall*)(void*, void*))VSLOT(w, 0x80))(w, r)) {
            void* arg = *(void**)((char*)self + 0x688);
            arg = arg ? (void*)((char*)arg + 4) : 0;
            ((void(__thiscall*)(void*, int, void*))VSLOT(w, 0x4c))(w, 0, arg);
          }
        }
      }
      if (*(void**)((char*)self + 0x688)) {
        void* p = *(void**)((char*)self + 0x688);
        *(void**)((char*)self + 0x688) = 0;
        ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
      }
    }
    if (*(void**)((char*)self + 0x68c)) {
      void* p = *(void**)((char*)self + 0x68c);
      *(void**)((char*)self + 0x68c) = 0;
      ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
    }
    void* h = (char*)self + 0x658;
    ((void(__thiscall*)(void*, void*, int, int))VSLOT(*(void**)((char*)self + 0x65c), 0x2c))(
        *(void**)((char*)self + 0x65c), h, 0x2ac44c14, 0xffffd8f1);
    ((void(__thiscall*)(void*, void*, int, int))VSLOT(*(void**)((char*)self + 0x65c), 0x2c))(
        *(void**)((char*)self + 0x65c), h, 0x2ac44c1a, 0xffffd8f1);
    ((void(__thiscall*)(void*, void*, int, int))VSLOT(*(void**)((char*)self + 0x65c), 0x2c))(
        *(void**)((char*)self + 0x65c), h, 0x2ac44c1b, 0xffffd8f1);
    *(unsigned char*)((char*)self + 0x660) = 0;
  }
  ((void(__thiscall*)(void*))WinTextEditShutdown)(self);
}

// @ 0x007F3750  IMEComposition text placement handler
void __fastcall IMECompositionBig(void* self) {
  char* win = (char*)self + 4;
  if (*(void**)((char*)self + 0x688) && *(void**)((char*)self + 0x68c)) {
    char* comp = (char*)*(void**)((char*)self + 0x68c);
    void* a = ((void*(__thiscall*)(void*))VSLOT(comp + 0x20c, 0x10))(comp + 0x20c);
    void* b = ((void*(__thiscall*)(void*))VSLOT(a, 0x14))(a);
    if (b) {
      ((void(__thiscall*)(void*))VSLOT(comp + 4, 0x38))(comp + 4);
      int idx = (int)((void*(__thiscall*)(void*))VSLOT(comp + 0x20c, 0x88))(comp + 0x20c);
      Vec2 pos;
      ((void(__thiscall*)(void*, Vec2*, int))TypesetterPos90)(comp, &pos, idx);
      char* cand = (char*)*(void**)((char*)self + 0x688);
      Vec2 tmp;
      float* g = (float*)((void*(__thiscall*)(void*, Vec2*))VSLOT(cand + 4, 0xc0))(cand + 4, &tmp);
      float gx = g[0];
      float gy = g[1];
      RectF unit;
      float k = *(float*)0x1470f1c;
      unit.x = k; unit.y = k; unit.w = k; unit.h = k;
      ((void(__thiscall*)(void*, RectF*))VSLOT((char*)self + 0x20c, 0x28))(
          (char*)self + 0x20c, &unit);
      void* ts = ((void*(__thiscall*)(void*))Fun95fba0)(self);
      const wchar_t* str = *(const wchar_t**)((char*)self + 0xb0);
      wchar_t buf[2];
      buf[0] = 0x5757;
      buf[1] = 0;
      int len = (*(int*)((char*)self + 0xb4) - (int)str) >> 1;
      if (!str || !str[0]) { str = buf; len = 2; }
      float fx = *(float*)((char*)self + 0x220);
      float fy = *(float*)((char*)self + 0x224);
      ((int(__thiscall*)(void*, const wchar_t*, int, float, float, const void*))TypesetterLayoutLine)(
          ts, str, len, fx, fy, *(const void**)((char*)self + 0x6b8));
      float* ll = (float*)((void*(__thiscall*)(void*))TypesetterGetLineLayout)(ts);
      float x1 = (*(float*)((char*)self + 0x228) + ll[0x98 / 4]) + *(float*)((char*)self + 0x220);
      float y1 = ((ll[0xa0 / 4] - ll[0xa4 / 4]) + *(float*)((char*)self + 0x22c)) +
                 *(float*)((char*)self + 0x224);
      Rect5 rr;
      rr.x = gx;
      rr.y = gy - fy;
      rr.w = gx + x1;
      rr.h = (gy - fy) + y1;
      ((void(__thiscall*)(void*, Rect5*))VSLOT(win, 0x6c))(win, &rr);
      goto tail;
    }
  }
  {
    float k = *(float*)0x1470f1c;
    ((void(__thiscall*)(void*, float, float))VSLOT(win, 0x70))(win, k, k);
  }
tail:
  void* o = ((void*(__thiscall*)(void*))VSLOT(win, 0x10))(win);
  float* ra = (float*)((void*(__thiscall*)(void*))VSLOT(o, 0x38))(o);
  float height = ra[3] - ra[1];
  o = ((void*(__thiscall*)(void*))VSLOT(win, 0x10))(win);
  float* rb = (float*)((void*(__thiscall*)(void*))VSLOT(o, 0x38))(o);
  float width = rb[2] - rb[0];
  float* rc = (float*)((void*(__thiscall*)(void*))VSLOT(win, 0x38))(win);
  Vec4f L;
  L.x = rc[0]; L.y = rc[1]; L.z = rc[2]; L.w = rc[3];
  bool changed = false;
  if (!(0.0f < L.x)) { L.x = 1.0f; changed = true; }
  if (!(0.0f < L.y)) { L.y = 1.0f; changed = true; }
  if (!(L.z < width)) {
    float d = -((L.z - width) + 1.0f);
    L.x = d + L.x;
    L.z = d + L.z;
    changed = true;
  }
  if (L.w < height) {
    if (changed) ((void(__thiscall*)(void*, Vec4f*))VSLOT(win, 0x6c))(win, &L);
  } else {
    float d = -((L.w - height) + 1.0f);
    L.y = d + L.y;
    L.w = d + L.w;
    ((void(__thiscall*)(void*, Vec4f*))VSLOT(win, 0x6c))(win, &L);
  }
  ((void(__thiscall*)(void*))VSLOT(win, 0x90))(win);
}

// @ 0x007F3C10  Sims3::UI::IMECandidateList::IMECandidateList
void* __fastcall IMECandidateListCtor(void* self) {
  ((void(__thiscall*)(void*))WindowCtor)(self);
  *(void* volatile*)((char*)self + 0x20c) = (void*)0x13eb394;
  _ReadWriteBarrier();
  *(unsigned char*)((char*)self + 0x214) = 0;
  *(void**)((char*)self + 0x218) = 0;
  *(void**)self = (void*)0x1414ce0;
  *(void**)((char*)self + 4) = (void*)0x1414bc0;
  *(void* volatile*)((char*)self + 0x20c) = (void*)0x1414bb4;
  _ReadWriteBarrier();
  *(void**)((char*)self + 0x234) = 0;
  *(void**)((char*)self + 0x238) = 0;
  *(void**)((char*)self + 0x23c) = 0;
  *(void**)((char*)self + 0x240) = 0;
  return self;
}

// @ 0x007F3CC0  Sims3::UI::IMECandidateList::~IMECandidateList
void __fastcall IMECandidateListDtor(void* self) {
  *(void**)self = (void*)0x1414ce0;
  *(void**)((char*)self + 4) = (void*)0x1414bc0;
  *(void* volatile*)((char*)self + 0x20c) = (void*)0x1414bb4;
  void* p = *(void* volatile*)((char*)self + 0x240);
  if (p) ((void(__thiscall*)(void*))VSLOT(p, 0xc))(p);
  p = *(void* volatile*)((char*)self + 0x238);
  if (p) ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
  p = *(void* volatile*)((char*)self + 0x234);
  if (p) ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
  *(void* volatile*)((char*)self + 0x20c) = (void*)0x13eb394;
  ((void(__thiscall*)(void*))WindowDtor)(self);
}

// @ 0x007F3D20  Sims3::UI::IMECandidateList::Init
bool __fastcall IMECandidateListPaint(void* self, void* /*unused*/, int /*arg*/) {
  if (*(unsigned char*)((char*)self + 0x214)) return true;
  char* win = (char*)self + 4;
  RectF r;
  r.x = *(float*)0x1473c70;
  r.y = r.x;
  r.w = *(float*)0x13ec4d0;
  r.h = r.w;
  ((void(__thiscall*)(void*, RectF*))VSLOT(win, 0x6c))(win, &r);
  *(unsigned char*)((char*)self + 0x214) = 1;
  void* w = ((void*(__thiscall*)(void*))VSLOT(win, 0x14))(win);
  void* q = ((void*(__thiscall*)(void*, int))VSLOT(w, 0x48))(w, 0);
  void* a = q ? (void*)((char*)q - 4) : 0;
  void* old = *(void**)((char*)self + 0x234);
  if (a != old) {
    if (a) ((void(__thiscall*)(void*))VSLOT(a, 0))(a);
    *(void**)((char*)self + 0x234) = a;
    if (old) ((void(__thiscall*)(void*))VSLOT(old, 4))(old);
  }
  void* f = *(void**)((char*)self + 0x234);
  if (f) {
    float* rr = (float*)((void*(__thiscall*)(void*))VSLOT((char*)f + 4, 0x38))((char*)f + 4);
    ((void(__thiscall*)(void*, float, float))VSLOT(win, 0x70))(win, rr[0], rr[3]);
  } else {
    float c = *(float*)0x140c6e8;
    ((void(__thiscall*)(void*, float, float))VSLOT(win, 0x70))(win, c, c);
  }
  ((void(__thiscall*)(void*, int))VSLOT(win, 0xac))(win, (int)0x80808080);
  ((void(__thiscall*)(void*))WindowInitialize)(self);
  void* sm = GetStyleManagerStub(1);
  const void* st = ((const void*(__thiscall*)(void*, unsigned, void*))GetStyleStub)(
      sm, *(unsigned*)((char*)self + 0xc0), 0);
  *(const void**)((char*)self + 0x23c) = st;
  void* fs = GetFontServerStub(1);
  void* font = ((void*(__thiscall*)(void*, const void*, int, int, int, int, int))VSLOT(fs, 0x1c))(
      fs, st, 0, 0, 0xffff, -1, 1);
  old = *(void**)((char*)self + 0x240);
  if (font != old) {
    if (font) ((void(__thiscall*)(void*))VSLOT(font, 8))(font);
    *(void**)((char*)self + 0x240) = font;
    if (old) ((void(__thiscall*)(void*))VSLOT(old, 0xc))(old);
  }
  void* grid = Fun9512d0(0xa90, 8, "UI/IME/WinGrid", Fun9512c0());
  grid = grid ? WinGridCtor(grid) : 0;
  old = *(void**)((char*)self + 0x238);
  if (grid != old) {
    if (grid) ((void(__thiscall*)(void*))VSLOT(grid, 0))(grid);
    *(void**)((char*)self + 0x238) = grid;
    if (old) ((void(__thiscall*)(void*))VSLOT(old, 4))(old);
  }
  char* g = (char*)*(void**)((char*)self + 0x238) + 0x20c;
  ((void(__thiscall*)(void*, float, float, float, float))VSLOT(g, 0x58))(
      g, 0.0f, 0.0f, 0.0f, 0.0f);
  ((void(__thiscall*)(void*, int, int, int))VSLOT(g, 0x74))(g, 2, 1, 1);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 2, 0);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 4, 0);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 0x200, 1);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 0x20, 1);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 0x40, 0);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 0x1000, 1);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x2c))(g, 1, 0);
  void* w2 = ((void*(__thiscall*)(void*))VSLOT(g, 0x10))(g);
  ((void(__thiscall*)(void*, int, int))VSLOT(w2, 0x7c))(w2, 2, 0);
  void* w3 = ((void*(__thiscall*)(void*))VSLOT(g, 0x10))(g);
  ((void(__thiscall*)(void*, int))VSLOT(w3, 0xac))(w3, (int)0xffefefef);
  ((void(__thiscall*)(void*, int, int))VSLOT(g, 0x3c))(g, (int)0xffefefef, 1);
  void* w4 = ((void*(__thiscall*)(void*))VSLOT(g, 0x10))(g);
  ((void(__thiscall*)(void*, void*))VSLOT(win, 0xd8))(win, w4);
  void* ms = GetMessageServerStub();
  *(void**)((char*)self + 0x210) = ms;
  void* h = (char*)self + 0x20c;
  ((void(__thiscall*)(void*, void*, int))VSLOT(ms, 0x24))(ms, h, 0x2ac44ed8);
  ((void(__thiscall*)(void*, void*, int))VSLOT(ms, 0x24))(ms, h, 0x2ac44ef0);
  return true;
}

// @ 0x007F4090  Sims3::UI::IMECandidateList::Shutdown
void __fastcall IMECandidateListShutdown(void* self) {
  if (*(unsigned char*)((char*)self + 0x214)) {
    char* win = (char*)self + 4;
    void* w = ((void*(__thiscall*)(void*))VSLOT(win, 0x14))(win);
    void* f = *(void**)((char*)self + 0x234);
    if (f) {
      if (w) {
        void* t = ((void*(__thiscall*)(void*))VSLOT((char*)f + 4, 0x14))((char*)f + 4);
        if (t) {
          void* arg = *(void**)((char*)self + 0x234);
          arg = arg ? (void*)((char*)arg + 4) : 0;
          ((void(__thiscall*)(void*, int, void*))VSLOT(w, 0x4c))(w, 0, arg);
        }
      }
      if (*(void**)((char*)self + 0x234)) {
        void* p = *(void**)((char*)self + 0x234);
        *(void**)((char*)self + 0x234) = 0;
        ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
      }
    }
    win = (char*)self + 0x20c;
    ((void(__thiscall*)(void*, void*, int, int))VSLOT(*(void**)((char*)self + 0x210), 0x2c))(
        *(void**)((char*)self + 0x210), win, 0x2ac44ed8, 0xffffd8f1);
    ((void(__thiscall*)(void*, void*, int, int))VSLOT(*(void**)((char*)self + 0x210), 0x2c))(
        *(void**)((char*)self + 0x210), win, 0x2ac44ef0, 0xffffd8f1);
    *(unsigned char*)((char*)self + 0x214) = 0;
    _ReadWriteBarrier();
    if (*(void**)((char*)self + 0x240)) {
      void* p = *(void**)((char*)self + 0x240);
      *(void**)((char*)self + 0x240) = 0;
      ((void(__thiscall*)(void*))VSLOT(p, 0xc))(p);
    }
  }
  ((void(__thiscall*)(void*))WindowShutdown)(self);
}

// @ 0x007F4200  IMECandidateList scalar deleting destructor
void* __fastcall IMECandidateListScalarDtor(void* self, void* /*unused*/, unsigned flags) {
  *(void* volatile*)self = (void*)0x1414ba4;
  void* p = *(void* volatile*)((char*)self + 0x3c);
  if (p) ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
  p = *(void* volatile*)((char*)self + 0x30);
  if (p) ((void(__thiscall*)(void*))VSLOT(p, 4))(p);
  *(void* volatile*)self = (void*)0x13eb394;
  if (flags & 1) ((void(__cdecl*)(void*))OperatorDelete)(self);
  return self;
}
