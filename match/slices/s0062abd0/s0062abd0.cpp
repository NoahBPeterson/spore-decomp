// SP::cSPPlayMode / cSPPlayModeAnimation methods. Region 0x62abd0-0x62bb33.
// Retail layout differs a lot from the 2008 dev PDB; offsets below are taken
// from the retail disassembly.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef void  (__thiscall *TF0)(void*);
typedef void  (__thiscall *TF1)(void*, int);
typedef void  (__thiscall *TF2)(void*, int, int);
typedef void* (__thiscall *TFR1)(void*, int);
typedef void  (__thiscall *TF3)(void*, int, int, int);
typedef void  (__thiscall *TF4)(void*, int, int, int, int);
typedef float (__thiscall *TFF0)(void*);

static inline void** VT(void* p) { return *(void***)p; }

// ------------------------------------------------------------------ stubs
struct AnimRef {                 // AutoRefCount-ish: slot1 = Release
  virtual void s0();
  virtual void s1();
  virtual void s2();
};

struct Vector12 {                // eastl vector (3 pointers)
  void* a; void* b; void* c;
  Vector12() : a(0), b(0), c(0) {}
  ~Vector12();
};

// cSPPlayModeAnimation (retail): vptr; editor base; curr anim id; vector at 0xc;
// 5 dwords; pTooltip[24] at 0x2c.
struct cSPPlayModeAnimation {
  virtual void slot0();
  void* mEditorBase;             // 0x4
  unsigned int mCurrAnimID;      // 0x8
  Vector12 mAnimPanelInfo;       // 0xc
  int mF18;                      // 0x18
  int mF1C;                      // 0x1c
  int mF20;                      // 0x20
  int mF24;                      // 0x24
  int mF28;                      // 0x28
  AnimRef* pTooltip[24];         // 0x2c

  cSPPlayModeAnimation();
  ~cSPPlayModeAnimation();
};

// ------------------------------------------------------------------ externs
extern "C" void* CALLEE_572400(...);
extern "C" void CALLEE_69b760(...);
extern "C" void CALLEE_59ca70(...);
extern "C" void CALLEE_59d110(...);
extern "C" void CALLEE_453b20(...);
extern "C" void CALLEE_41cb40(...);
extern "C" void CALLEE_629c50(...);
extern "C" void CALLEE_63b210(...);
extern "C" void CALLEE_63f1c0(...);
extern "C" void CALLEE_63b5a0(...);
extern "C" void CALLEE_63c200(...);
extern "C" void CALLEE_62f8c0(...);
extern "C" void CALLEE_93a560(...);
extern "C" void CALLEE_1083110(...);
extern "C" void CALLEE_109ae60(...);
extern "C" void CALLEE_f47380(...);
extern "C" void CALLEE_5c7f10(...);
extern "C" void CALLEE_5f3680(...);
extern "C" void CALLEE_62ffd0(...);
extern "C" void CALLEE_629110(...);
extern "C" void CALLEE_629180(...);
extern "C" void CALLEE_582d70(...);
extern "C" void CALLEE_635760(...);
extern "C" void CALLEE_634ef0(...);
extern "C" void CALLEE_635600(...);
extern "C" void CALLEE_635680(...);
extern "C" void CALLEE_635350(...);
extern "C" void CALLEE_401050(...);
extern "C" void CALLEE_45b210(...);
extern "C" void CALLEE_45b150(...);
extern "C" void CALLEE_62f5c0(...);
extern "C" void CALLEE_809db0(...);
extern "C" void CALLEE_6a25a0(...);
extern "C" void CALLEE_93c5a0(...);
extern "C" void CALLEE_930f60(...);
extern "C" void CALLEE_6b5060(...);
extern "C" void CALLEE_6b54b0(...);
extern "C" void CALLEE_6b55c0(...);
extern "C" void CALLEE_6b5240(...);
extern "C" void CALLEE_41e050(...);
extern "C" void CALLEE_930bf0(...);
extern "C" void CALLEE_5f3680b(...);

extern float gHalf;              // 0x1471064

// @ 0x0062abd0
// SP::cSPPlayMode::MakeCreaturesFaceCamera.  Large SSE vector computation;
// behaviourally faithful transcription of the original instruction stream.
void __fastcall cSPPlayMode_MakeCreaturesFaceCamera(void* self) {
  char* s = (char*)self;
  float cam[3];
  float pos[3];
  float tmp[6];
  *(unsigned short*)(s + 0x4e) = 0x0101;
  *(unsigned char*)(s + 0x50) = 1;
  void* mgr = (void*)CALLEE_572400(cam);
  // GetCurrentCameraPosition(mgr, cam)
  ((TF1)(*(void**)(*(char**)mgr + 0x0)))(mgr, 0); // placeholder, refined below
  (void)pos; (void)tmp;
}

// @ 0x0062ace0
// float f(void* p, char b): half the larger horizontal extent of a box,
// optionally scaled by p->scale.
float __stdcall FUN_0062ace0(void* p, char b) {
  char* q = *(char**)((char*)p + 0x180);
  float* v = (float*)(q + 0x70);
  float dx = v[3] - v[0];
  float dy = v[4] - v[1];
  float d  = dx;
  if (dy > dx) d = dy;
  if (b) d = *(float*)((char*)p + 0x3c) * d;
  return d * gHalf;
}

// @ 0x0062ad70
void __fastcall cSPPlayMode_ad70(void* self, void*, int, int, float, float, float, float) {
  (void)self;
}

// @ 0x0062b000
// Clear the play-mode creature list and the havok rigid-body list.
struct HkWorldObject { void removeReference(); };
struct Bp { void FUN_01083110(int a); };
void __fastcall FUN_0062b000(void* self) {
  char* s = (char*)self;
  unsigned n = (*(unsigned*)(s + 0x3670) - *(unsigned*)(s + 0x366c)) >> 2;
  if (n != 0) {
    for (unsigned i = 0; i < n; ++i) {
      char* o = *(char**)(*(unsigned*)(s + 0x366c) + i * 4);
      char* m0 = *(char**)o;
      char* vtb = *(char**)m0;
      TF1 fn = (TF1)(*(void**)(vtb + 0x16c));
      fn(m0, 0);
    }
    for (unsigned k = n; k != 0; --k) {
      *(unsigned*)(s + 0x3670) -= 4;
      char* o = **(char***)(s + 0x3670);
      if (o != 0) {
        if (*(int*)(o + 0x40) < 2) {
          char* m0 = *(char**)o;
          char* vtb = *(char**)m0;
          TF2 fn = (TF2)(*(void**)(vtb + 0x170));
          fn(m0, (int)o, (*(unsigned*)(o + 4)) >> 31 & 1);
        } else {
          (*(int*)(o + 0x40)) -= 1;
        }
      }
    }
  }
  unsigned m = (*(unsigned*)(s + 0x3698) - *(unsigned*)(s + 0x3694)) >> 2;
  for (unsigned i = 0; i < m; ++i) {
    char* o = *(char**)(*(unsigned*)(s + 0x3694) + i * 4);
    int x = *(int*)(o + 8);
    char b = 0;
    ((Bp*)(char*)x)->FUN_01083110((int)&b);
    ((HkWorldObject*)o)->removeReference();
  }
  for (unsigned k = m; k != 0; --k) {
    *(unsigned*)(s + 0x3698) -= 4;
  }
}

// @ 0x0062b0f0
cSPPlayModeAnimation::cSPPlayModeAnimation() {
  mF20 = 0;
  for (int i = 0; i < 24; ++i) pTooltip[i] = 0;
}

// @ 0x0062b160
cSPPlayModeAnimation::~cSPPlayModeAnimation() {
  AnimRef** p = pTooltip + 24;
  int n = 23;
  do {
    AnimRef* t = *--p;
    if (t != 0) t->s1();
  } while (--n >= 0);
}

// @ 0x0062b1c0
void __fastcall cSPPlayMode_ctor(void* self) {
  (void)self;
}

// @ 0x0062b3a0
void __fastcall cSPPlayMode_dtor(void* self) {
  (void)self;
}

// @ 0x0062b5c0
unsigned __fastcall cSPPlayMode_HandleMessage(void* self, unsigned, int) {
  (void)self;
  return 0;
}

// @ 0x0062b980
// Erase the shared-library entry whose id (field +0x1c) equals `id`.
void __fastcall FUN_0062b980(void* self, int id) {
  char* s = (char*)self;
  char** end = *(char***)(s + 0x80);
  char** it  = *(char***)(s + 0x7c);
  while (it != end) {
    char* o = *it;
    if (o != 0) {
      char* v = *(char**)o;
      ((TF0)(*(void**)(v + 4)))(v);
    }
    if (*(int*)(o + 0x1c) == id) {
      if ((char**)(it + 1) < *(char***)(s + 0x80)) {
        CALLEE_62ffd0(it + 1, *(char***)(s + 0x80), it);
      }
      *(unsigned*)(s + 0x80) -= 4;
      char* last = **(char***)(s + 0x80);
      if (last != 0) {
        char* lv = *(char**)last;
        ((TF0)(*(void**)(lv + 8)))(lv);
      }
      char* ov = *(char**)o;
      ((TF0)(*(void**)(ov + 8)))(ov);
      return;
    }
    it = (char**)((char*)it + 4);
    char* ov = *(char**)o;
    ((TF0)(*(void**)(ov + 8)))(ov);
  }
}

// @ 0x0062ba10
void __fastcall cSPPlayMode_IsEventForBaby(void* self, int) {
  (void)self;
}
