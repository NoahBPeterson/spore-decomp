// Slice s00d7a5c0 -- Simulator creature behavior-tree Decide/Tick/Deactivate helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast /Isrc/game/include

#include <stddef.h>

typedef unsigned int uint;

// ---- globals ---------------------------------------------------------------
extern float g_1485720;         // 1.0f
extern float g_1687a00;         // 1.0f
extern float g_1687a0c;         // threshold
extern float g_1473c70;         // 10.0f
extern float g_1486110;         // 5.0f

// ---- opaque services / callees ---------------------------------------------
struct Stimuli {
  void __thiscall GetAny();                 // 0x00d997e0
};

struct LayoutMgr {
  bool __thiscall LookupA(void*, int, float*);
};
LayoutMgr* __cdecl CreateLayoutManager();

struct BStim {
  char pad[8];
  int  __thiscall Play(int a, int f);       // 0x00bc96a0
  void __thiscall ClearAll(int a, int f);   // 0x00bc98f0
};

struct Iter {
  bool  __thiscall AtBegin();               // 0x00bc9b50
  void* __thiscall Cur();                   // 0x00bc9b10
};

struct TerrainEditor {
  bool __thiscall Sub(int, int*);
};

extern "C" {
void* __cdecl FUN_00d999d0(void*);
void* __cdecl FUN_00d998d0(void*, int);
void* __cdecl FUN_00d99a10(void*);
void* __cdecl FUN_00d998f0(void*);
void* __cdecl FUN_00d99980(void*);
void* __cdecl FUN_00d99500(void*);
float __cdecl FUN_00d99ac0(void*, void*, int);
float __cdecl FUN_00d38a30(int, void*);
void* __cdecl FUN_00ac80d0(void*, void*);
void* __cdecl FUN_00b3d300();
void* __fastcall FUN_00989360(void*);
void* __fastcall FUN_00f67d90(void*);
int   __fastcall FUN_00c02c70(void*);
}

// ---- raw creature layout ---------------------------------------------------
// Flags word at cSPCreatureBase+0xb58, read as bitfields by name in the original.
struct GeneralFlagsB58 {
  unsigned int mBit0 : 1, mBit1 : 1, mBit2 : 1, mBit3 : 1, mBit4 : 1, mBit5 : 1, mBit6 : 1,
               mBit7 : 1, mBit8 : 1, mBit9 : 1, mBit10 : 1, mBit11 : 1, mBit12 : 1, mBit13 : 1,
               mBit14 : 1, mBit15 : 1, mBit16 : 1, mBit17 : 1, mBit18 : 1, mBit19 : 1,
               mBit20 : 1, mBit21 : 1, mBit22 : 1, mBit23 : 1, mBit24 : 1, mBit25 : 1,
               mBit26 : 1, mBit27 : 1, mBit28 : 1, mBit29 : 1, mBit30 : 1, mBit31 : 1;
};

// Object at cSPCreatureBase+0xb4c: a creature sub-object at +8 carrying the
// behaviour stimuli, and a flags word at +0x5fc.
struct StimuliContainer {
  uint pad0_5fc[0x5fc / 4];
  unsigned int mFlags5fc;                   // +0x5fc
};

struct CB {
  char pad0[0x110];
  unsigned int mFlags;                      // +0x110
  char pad114[0x137 - 0x114];
  unsigned char mb137;                      // +0x137
  char pad138[0x5a8 - 0x138];
  char mStim5a8[0x38];                      // +0x5a8
  float m_5e0;                              // +0x5e0
  char pad5e4[0xb20 - 0x5e4];
  void* mpSpecies;                          // +0xb20
  char padb24[0xb4c - 0xb24];
  StimuliContainer* mp_b4c;                 // +0xb4c
  char padb50[0xb58 - 0xb50];
  union {
    unsigned int mGeneralFlags;             // +0xb58
    GeneralFlagsB58 mFlagBitsB58;           // +0xb58
  };
  char padb5c[0xb5e - 0xb5c];
  unsigned char mbDead;                     // +0xb5e

  char* GetStim5a8() { return mStim5a8; }        // inline accessor

  void* __thiscall Get();                        // 00c04590
  int   __thiscall GetSpeciesProfile();          // 00c0bbd0
  void* __thiscall GetTargetAsCreature();        // 00c0ee70
  void  __thiscall ClampHunger(float);           // 00c0b9d0
  bool  __thiscall Prox(void*, float, float);    // 00c0d560
  bool  __thiscall AnimationFinished(int);       // 00c123f0
  bool  __thiscall AnimationFinishedX(int);      // 00c12400
  int   __thiscall InterruptAnimation(int, int, int);  // 00c12310
  void  __thiscall Sub01(int);                   // 00c14750
  bool  __thiscall CheckA(void*);                // 00c0b860
  bool  __thiscall CheckB(void*);                // 00c0b8a0
};

struct St {
  char pad0[4];
  int m4;                                   // +4
  unsigned char m8;                         // +8
  char pad9[0xc - 9];
  int mc;                                   // +0xc
  unsigned char m10;                        // +0x10
  unsigned char m11;                        // +0x11
  unsigned char m12;                        // +0x12
};

#define BS(cb) ((BStim*)((char*)(cb)->mp_b4c + 8))

// @ 0x00d7a5c0
float __cdecl FUN_00d7a5c0(void* p)
{
  if (!CreateLayoutManager()->LookupA(p, 1, 0)) return 1.0f;
  return 0.0f;
}

// @ 0x00d7a5e0
float __cdecl FUN_00d7a5e0(CB* p)
{
  if (CreateLayoutManager()->LookupA(p, 1, 0)) {
    p->ClampHunger(g_1687a0c);
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7a620
float __cdecl FUN_00d7a620(CB* p)
{
  return *(int*)((char*)p->Get() + 0x80) != -1 ? g_1485720 : 0.0f;
}

// @ 0x00d7a660
float __cdecl FUN_00d7a660(CB* cb)
{
  int r = BS(cb)->Play(0x40000, 0);
  if (r != 0) {
    CB* m = (CB*)FUN_00d999d0((void*)r);
    if (m != 0 && m->mbDead != 0 && m->mpSpecies != cb->mpSpecies)
      return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7a6b0
float __cdecl FUN_00d7a6b0(CB* cb)
{
  int r = BS(cb)->Play(0, 0x100);
  if (r != 0) {
    int* p = (int*)FUN_00d998d0((void*)r, 0x61494bd);
    if (p != 0 && p[0x108 / 4] >= 2 && p[0x108 / 4] <= 4) return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7a700
bool __cdecl FUN_00d7a700(void* a, CB* b)
{
  if (((Iter*)a)->AtBegin()) return false;
  b->Get();
  CB* c = (CB*)((Iter*)a)->Cur();
  if (c->mpSpecies != b->mpSpecies) return false;
  if (b->Prox(c, 1.0f, 0.0f) ||
      ((bool (__thiscall*)(CB*, void*, float, float))(*(void***)b)[0xc0 / 4])(b, c, 1.0f, 0.0f))
    return true;
  return false;
}

// @ 0x00d7a780
float __cdecl FUN_00d7a780(CB* cb)
{
  int r = (int)FUN_00d998f0(FUN_00d99a10((void*)BS(cb)->Play(0x400, 0)));
  if (r != 0) return 1.0f;
  BS(cb)->ClearAll(0x400, 0);
  return 0.0f;
}

// @ 0x00d7a7d0
float __cdecl FUN_00d7a7d0(CB* cb, int, int, uint flags, void* st, char* out)
{
  if (flags & 0x80000000) return 0.0f;
  int* p = (int*)BS(cb)->Play(0x400, 0);
  if (p != 0 && p[3] != 3) {
    void* v = FUN_00d998f0(FUN_00d99a10((void*)p));
    if (v != 0) {
      if (st != 0) ((Stimuli*)st)->GetAny();
      *out = 1;
      *(void**)((char*)st + 4) = v;
      return 1.0f;
    }
    BS(cb)->ClearAll(0x400, 0);
  }
  return 0.0f;
}

// @ 0x00d7a850
float __cdecl FUN_00d7a850(CB* cb, int, int, uint, void* st, char* out)
{
  int r = BS(cb)->Play(0x400, 0);
  if (r != 0) {
    CB* v = (CB*)FUN_00d99a10((void*)r);
    if (v != 0) {
      CB* w = (CB*)((void* (__thiscall*)(CB*))(*(void***)v)[0xc / 4])(v);
      if (w != 0) {
        void* t = ((void* (__thiscall*)(CB*))(*(void***)w)[0x20 / 4])(w);
        if (t == (void*)0x18eb45e) {
          if (w->mbDead != 0) return 0.0f;
        } else {
          CB* x = (CB*)FUN_00ac80d0(w, (void*)0x18eb4b7);
          if (x != 0) {
            if (x->mbDead != 0) return 0.0f;
          } else {
            if (FUN_00ac80d0(w, (void*)0x18c6de8) != 0) goto L;
            if (FUN_00ac80d0(w, (void*)0x436f342) != 0) goto L;
            if (FUN_00ac80d0(w, (void*)0x18ebadc) == 0) return 0.0f;
          }
        }
      L:
        if (st != 0) ((Stimuli*)st)->GetAny();
        *out = 1;
        *(void**)((char*)st + 4) = v;
        return 1.0f;
      }
    }
  }
  return 0.0f;
}

// @ 0x00d7a920
float __cdecl FUN_00d7a920(CB* cb, int, int, uint, void* st, char* out)
{
  int* p = (int*)BS(cb)->Play(0x80000, 0);
  if (p == 0) return 0.0f;
  bool eq1 = p[3] == 1;
  CB* v = (CB*)FUN_00d99980((void*)p);
  if (v == 0 || v->mbDead != 0 || eq1 || v->mpSpecies == cb->mpSpecies)
    return 0.0f;
  float d = FUN_00d38a30(1, cb);
  d = FUN_00d38a30(2, cb);
  if (!cb->Prox(v, d, 0.0f) &&
      !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, v, d, 0.0f))
    return 0.0f;
  float dd = FUN_00d99ac0((char*)v + 0xc0, (char*)cb + 0xc0, 1);
  float thr = FUN_00d38a30(5, cb);
  if (thr < dd) return 0.0f;
  if (st != 0) ((Stimuli*)st)->GetAny();
  *out = 1;
  *(void**)((char*)st + 4) = &v->mStim5a8;
  BS(cb)->ClearAll(0x80000, 0);
  return 1.0f;
}

// @ 0x00d7aa50
float __cdecl FUN_00d7aa50(CB* cb)
{
  CB* t = (CB*)cb->GetTargetAsCreature();
  if (t != 0) {
    float d1 = FUN_00d38a30(1, cb);
    float d2 = FUN_00d38a30(2, cb);
    CB* t2 = (CB*)cb->GetTargetAsCreature();
    if (!cb->Prox(t2, d2, 0.0f) &&
        !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, t2, d2, 0.0f))
      return 1.0f;
    return 0.0f;
  }
  return 1.0f;
}

// @ 0x00d7aad0
float __cdecl FUN_00d7aad0(CB* cb)
{
  int r = BS(cb)->Play(0, 0x4000);
  if (r != 0) {
    if ((int)FUN_00d998f0(FUN_00d99a10((void*)r)) != 0) return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7ab10
float __cdecl FUN_00d7ab10(CB* cb, int, int, uint, void* st, char* out)
{
  int pr = BS(cb)->Play(0, 0x4000);
  if (pr == 0) return 0.0f;
  int* v = (int*)FUN_00d998f0(FUN_00d99a10((void*)pr));
  if (v != 0) {
    void* p = ((void* (__thiscall*)(void*))(*(void***)v)[8 / 4])(v);
    float d = FUN_00d99ac0((char*)cb + 0xc0, p, 1);
    if (d <= g_1473c70) return 0.0f;
    if (st != 0) ((Stimuli*)st)->GetAny();
    *(float*)((char*)st + 8) = ((float (__thiscall*)(void*))(*(void***)v)[0xc / 4])(v);
    void* p2 = ((void* (__thiscall*)(void*))(*(void***)v)[8 / 4])(v);
    float a = ((float (__thiscall*)(void*))(*(void***)p2)[0x74 / 4])(p2);
    float b = ((float (__thiscall*)(void*))(*(void***)((char*)cb + 0xc0))[0x74 / 4])((char*)cb + 0xc0);
    long long q = (long long)(a + b + g_1486110);
    *(int*)((char*)st + 0x1c) = 1;
    *(int*)((char*)st + 0x20) = 0;
    *(int*)((char*)st + 0x18) = (int)q;
    *out = 1;
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7ac10
float __cdecl FUN_00d7ac10(CB* cb, int, int, uint, void* st, char* out)
{
  int p = BS(cb)->Play(0, 0x4000);
  if (p != 0) {
    int r = (int)FUN_00d998f0(FUN_00d99a10((void*)p));
    if (r != 0) {
      if (st != 0) ((Stimuli*)st)->GetAny();
      *out = 1;
      *(void**)((char*)st + 4) = (void*)r;
      return 1.0f;
    }
  }
  return 0.0f;
}

// @ 0x00d7ac70
bool __cdecl FUN_00d7ac70(CB* cb)
{
  ((void (__thiscall*)(void*))(*(void***)((char*)cb + 0xc0))[0xec / 4])((char*)cb + 0xc0);
  return true;
}

// @ 0x00d7ac90
float __cdecl FUN_00d7ac90(CB* cb, int, int, uint flags, void* st, char* out)
{
  int* p = (int*)BS(cb)->Play(0x200, 0);
  if (p != 0) {
    CB* a = (CB*)FUN_00d99980((void*)p);
    if (a != 0 && p[3] == 1) {
      CB* q = *(CB**)((char*)p + 0x10);
      if (q == 0) {
        q = (CB*)FUN_00d999d0((void*)BS(a)->Play(0x400, 0));
        if (q == 0) return 0.0f;
      }
      bool b = ((bool (__thiscall*)(void*))(*(void***)((char*)q + 0xc0))[0x58 / 4])((char*)q + 0xc0);
      if (b && (flags & 0x6000000) != 0) return 0.0f;
      if (cb == q) return 0.0f;
      if (q->mbDead != 0) return 0.0f;
      float d = FUN_00d38a30(1, cb);
      d = FUN_00d38a30(2, cb);
      if (!cb->Prox(q, d, 0.0f) &&
          !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, q, d, 0.0f))
        return 0.0f;
      if (st != 0) ((Stimuli*)st)->GetAny();
      *out = 1;
      *(void**)((char*)st + 4) = &q->mStim5a8;
      return 1.0f;
    }
  }
  return 0.0f;
}

// @ 0x00d7adc0
float __cdecl FUN_00d7adc0(CB* cb)
{
  float a = g_1687a00 * cb->m_5e0;
  float b = ((float (__thiscall*)(void*))(*(void***)((char*)cb + 0x5a8))[0x58 / 4])((char*)cb + 0x5a8);
  return a / b < g_1687a0c ? g_1485720 : 0.0f;
}

// @ 0x00d7ae20
float __cdecl FUN_00d7ae20(CB* cb, int, int, uint, void* st, char* out)
{
  CB* m = (CB*)FUN_00d999d0((void*)BS(cb)->Play(0x100, 0));
  if (m != 0) {
    if (st != 0) ((Stimuli*)st)->GetAny();
    *out = 1;
    *(void**)((char*)st + 4) = m->GetStim5a8();
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7ae80
float __cdecl FUN_00d7ae80(CB* cb, int, int, uint, void* st, char* out)
{
  CB* m = (CB*)FUN_00d999d0((void*)BS(cb)->Play(0, 8));
  if (m != 0) {
    if (st != 0) ((Stimuli*)st)->GetAny();
    *out = 1;
    *(void**)((char*)st + 4) = m->GetStim5a8();
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7aed0
float __cdecl FUN_00d7aed0(CB* cb, int, int, uint, void* st, char* out)
{
  CB* a = (CB*)FUN_00d99500((void*)FUN_00d99980((void*)BS(cb)->Play(0x80000000, 0)));
  if (a != 0) {
    float f2 = FUN_00d38a30(2, cb);
    float f1 = FUN_00d38a30(1, cb);
    float d = FUN_00d99ac0((char*)cb + 0xc0, (char*)a + 0xc0, 1);
    if (!cb->Prox(a, f1, d) &&
        !((bool (__thiscall*)(CB*, void*, float, float))(*(void***)cb)[0xc0 / 4])(cb, a, f2, d))
      return 0.0f;
    if (st != 0) ((Stimuli*)st)->GetAny();
    *out = 1;
    *(void**)((char*)st + 4) = &a->mStim5a8;
    return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7afb0
float __cdecl FUN_00d7afb0(CB* cb)
{
  unsigned int f = cb->mGeneralFlags;
  if (((f >> 8) & 1) == 0 && ((f >> 4) & 1) != 0) {
    CB* a = (CB*)FUN_00d99500((void*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0)));
    if (a != 0) return 1.0f;
  }
  return 0.0f;
}

// @ 0x00d7b000
float __cdecl FUN_00d7b000(CB* cb)
{
  if (!cb->mFlagBitsB58.mBit8) {
    CB* a = (CB*)FUN_00d99500((void*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0)));
    if (a != 0 && (a->mp_b4c->mFlags5fc & 0x1000) != 0)
      return 1.0f;
  }
  return 0.0f;
}

namespace SP {

// @ 0x00d7b060
float __cdecl CURIOUS_Deactivate(CB* cb, int, int, uint, void* st, char* out)
{
  CB* o = (CB*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0));
  if (o != 0) {
    if (o->GetSpeciesProfile() != cb->GetSpeciesProfile()) {
      if (cb->Prox(o, 1.0f, 0.0f) && cb->CheckA(o)) {
        if (st != 0) ((Stimuli*)st)->GetAny();
        *out = 1;
        *(void**)((char*)st + 4) = &o->mStim5a8;
        BS(cb)->ClearAll(0x800, 0);
        return 1.0f;
      }
    }
  }
  return 0.0f;
}

// @ 0x00d7b110
float __cdecl FRIENDLY_Deactivate(CB* cb, int, int, uint, void* st, char* out)
{
  CB* o = (CB*)FUN_00d99980((void*)BS(cb)->Play(0x800, 0));
  if (o != 0) {
    if (o->GetSpeciesProfile() != cb->GetSpeciesProfile()) {
      if (cb->CheckB(o)) {
        if (st != 0) ((Stimuli*)st)->GetAny();
        *out = 1;
        *(void**)((char*)st + 4) = &o->mStim5a8;
        BS(cb)->ClearAll(0x800, 0);
        return 1.0f;
      }
    }
  }
  return 0.0f;
}

// @ 0x00d7b1a0
float __cdecl FUN_00d7b1a0(CB* cb)
{
  if (FUN_00c02c70(cb) <= 0) return 0.0f;
  void* a = FUN_00989360(FUN_00b3d300());
  if (cb->Get() != a) return 1.0f;
  void* te = FUN_00f67d90(FUN_00b3d300());
  if (te == 0) return 1.0f;
  int local = 0;
  if (((TerrainEditor*)te)->Sub(0x514a219, &local)) return 0.0f;
  return 1.0f;
}

}  // namespace SP

// @ 0x00d7b290
bool __cdecl FUN_00d7b290(void* a, CB* b)
{
  if (((Iter*)a)->AtBegin()) return false;
  CB* c = (CB*)((Iter*)a)->Cur();
  int d = (int)b->Get();
  int e = (int)c->Get();
  if (c->mpSpecies != b->mpSpecies) return false;
  if (e != d) return false;
  return true;
}

// @ 0x00d7b2e0
float __cdecl FUN_00d7b2e0(void* self, int, int, uint, void* st, char* out)
{
  if (st != 0) ((Stimuli*)st)->GetAny();
  *out = 1;
  *(void**)st = 0;
  return 1.0f;
}

// @ 0x00d7b310
bool __cdecl FUN_00d7b310(void* a, void* b)
{
  if (!((Iter*)a)->AtBegin()) {
    CB* c = (CB*)((Iter*)a)->Cur();
    return ((CB*)c)->Get() == ((CB*)b)->Get();
  }
  return false;
}

// @ 0x00d7b350
bool __cdecl FUN_00d7b350(CB* cb)
{
  bool r = ((bool (__thiscall*)(void*))(*(void***)((char*)cb + 0xc0))[0xf8 / 4])((char*)cb + 0xc0);
  cb->mGeneralFlags |= 4;
  cb->Sub01(r ? 0 : 1);
  int v = ((int (__thiscall*)(void*))(*(void***)((char*)cb + 0x58))[0x20 / 4])((char*)cb + 0x58);
  return v != 0;
}

// @ 0x00d7b3a0
void __cdecl FUN_00d7b3a0(CB* cb)
{
  cb->mGeneralFlags &= 0xfffffffb;
  ((void (__thiscall*)(void*))(*(void***)((char*)cb + 0x58))[0x34 / 4])((char*)cb + 0x58);
}

// @ 0x00d7b3c0
bool __cdecl FUN_00d7b3c0(CB* cb)
{
  if (cb->AnimationFinished(0x65d31ac)) {
    ((void (__thiscall*)(CB*, int))(*(void***)cb)[0xc8 / 4])(cb, 0);
  }
  return true;
}

// @ 0x00d7b3f0
void __cdecl FUN_00d7b3f0(CB* cb)
{
  cb->mGeneralFlags &= 0xfffffffb;
}

// @ 0x00d7b400
bool __cdecl FUN_00d7b400(CB* cb, int, int, uint, void*, St* st)
{
  if (BS(cb)->Play(0x1000, 0) != 0) {
    if (st->m12 != 0) {
      if (cb->mb137 != 0 || (cb->mFlags & 0x1000) != 0) {
        st->mc = cb->InterruptAnimation(0x2481e14, -1, 0);
        st->m12 = 0;
      }
      return true;
    }
    if (st->m8 != 0) {
      if (cb->AnimationFinished(st->m4)) {
        BS(cb)->ClearAll(0x1000, 0);
        return false;
      }
      return true;
    }
    if (st->m10 != 0 || st->m11 != 0) {
      if (cb->AnimationFinishedX(st->mc)) return false;
    }
    return true;
  }
  return false;
}

// @ 0x00d7b4c0
void __cdecl FUN_00d7b4c0(CB* cb, int, int, uint, void*, St* st)
{
  BS(cb)->ClearAll(0x1000, 0);
  if (st->m8 != 0) {
    cb->Sub01(0);
    return;
  }
  if (st->m10 == 0 && st->m11 == 0)
    cb->InterruptAnimation(0x74339a43, -1, 0);
}

// @ 0x00d7b510
bool __cdecl FUN_00d7b510(CB* cb)
{
  BS(cb)->ClearAll(0, 0x4000000);
  return false;
}

// @ 0x00d7b530
bool __cdecl FUN_00d7b530(CB* cb)
{
  BS(cb)->ClearAll(0x100000, 0);
  return false;
}
