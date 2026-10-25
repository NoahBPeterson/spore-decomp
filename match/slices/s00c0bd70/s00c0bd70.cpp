// Slice s00c0bd70 — Simulator::cGameData/cCreatureBase/cCreatureLocomotion helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

void* __cdecl SP_GetCurrentGameMode();                 // 0xb5b800
void* __cdecl FUN_00b3d4c0();                          // 0xb3d4c0
void* __cdecl SP_NounManager();                        // 0xb3d300
void* __cdecl SP_PlanetModel();                        // 0xb3d350
void* __cdecl FUN_00401090();                          // 0x401090
void* __cdecl FUN_004df420();                          // 0x4df420
void  __cdecl FUN_00ef1930(void*, float);              // 0xef1930
int   __cdecl FUN_00ebfd50(int, int);                  // 0xebfd50
bool  __cdecl FUN_00c0b1c0(void*, void*, int);         // 0xc0b1c0
bool  __cdecl FUN_00c0b220(void*, void*);              // 0xc0b220
void* __cdecl FUN_00d2e340();                          // 0xd2e340
void* __cdecl FUN_00b3d320();                          // 0xb3d320
void* __cdecl FUN_00c0c320(void*);                     // 0xc0c320

extern float  gF_150c8b8, gF_150c8b4, gF_150c8cc, gF_1485720, gF_146a32c, gF_146a330;
extern float  gF_1687a10, gF_1572040;
extern uint8_t g_169e37c;
extern void*  g_16c7aa4;
extern void*  g_168d900;
extern float  g_168d910, g_168d914, g_168d918;
extern int    g_15716d8[];
extern void*  g_156c208, *g_15816b8;

struct cVarListSerializer {
  uint32_t mData[0xa14 / 4];
  cVarListSerializer(void* owner, void* list, uint32_t sig);   // 0x00692f90
  int GetFields(void* fields);                                 // 0x00695960
};

struct GameDataFields {
  int GetFieldValues(void* fields);                            // 0x00b18420
};
struct LocoFields {
  int GetFieldValues(void* fields);                            // 0x00c0af90
};
struct CreatureBaseMgr {
  int FUN_00ba3f90(void* key, void* avatar, void* self);       // 0x00ba3f90
};
struct GameNounManager {
  void* GetAvatar();                                           // 0x00b1fdb0
};
struct DatabasePackedFile {
  void* GetLocation();                                         // 0x00a42730
};
struct behavior_stimuli {
  void* Play(uint32_t a, uint32_t b);                           // 0x00bc96a0
  void* Set(void* stimulus, uint32_t value, float timeout, void* obj); // 0x00bc97f0
  void  ClearAll(uint32_t a, uint32_t b);                       // 0x00bc98f0
};

struct GameModeObject {
  void* Get();                                                 // 0x00c04750
};
struct PlanetModelObj {
  float FUN_00b7e490();                                        // 0x00b7e490
};
struct Object1734 {
  void FUN_009ce720(int*, int*);                               // 0x009ce720
};
struct OrderManagerExec {
  int FindSlot(int, int, void*, int);                          // 0x00bca0c0
};
struct LocomotiveObject {
  float* GetVelocity();                                        // 0x00d20610
};
struct RandomLCG {
  uint32_t RandomUint32Uniform(uint32_t n);                    // 0x00a68fb0
};

struct Entity388 { uint8_t mPad0[0x388]; uint8_t m388; };

struct CreatureFields {
  uint8_t  mPad0[0xb20];
  void*    mB20;
  uint8_t  mPadB24[4];
  void*    mB28;
  uint8_t  mPadB2c[0xb4c - 0xb2c];
  void*    mB4c;
  uint8_t  mPadB50[0xb58 - 0xb50];
  uint32_t mB58;
};
struct CreatureB20    { uint8_t mPad0[0x544]; int m544; };
struct GameModeResult { uint8_t mPad0[0x490]; float m490; };
struct StimulusResult {
  uint8_t mPad0[0xc];
  int m0c;
  int m10;
  uint8_t mPad14[0x2c - 0x14];
  int m2c;
};
struct TransitionObject {
  uint8_t mPad0[0x135];
  uint8_t m135;
  uint8_t mPad136[0x5a8 - 0x136];
  uint8_t mSub5a8[4];
  uint8_t mPad5ac[0xb5e - 0x5ac];
  uint8_t mB5e;
};
struct TransitionState {
  float m0, m4, m8;
  uint8_t mPad0c[0x3c - 0xc];
  void* m3c;
  void* m40;
};
struct Global169e370 { uint8_t mPad0[0xf]; uint8_t mF; uint8_t m10; uint8_t m11; };

struct AnimCreatureExec {
  uint8_t mPad0[0x17c];
  void* m17c;
  uint8_t mPad180[0x188 - 0x180];
  void* m188;
  bool IsOrientStopAnim(uint32_t id);                           // 0x00a02740
  bool FUN_00a04940(void* p);                                   // 0x00a04940
};

struct OrderFlagsExec {
  uint8_t  mPad0[0x61c];
  uint32_t m61c;
  uint8_t  mPad620[0x698 - 0x620];
  uint32_t m698;
  uint32_t m69c;
  uint32_t m6a0;
};

struct LocomotionExec {
  uint8_t  mPad0[0x58];
  uint8_t  mSub58[0xc0 - 0x58];   // embedded vtable object
  uint8_t  mSubC0[4];             // embedded vtable object at +0xc0
  uint8_t  mPadC4[0x110 - 0xc4];
  uint32_t m110;
  uint8_t  mPad114[0x137 - 0x114];
  uint8_t  m137;
  uint8_t  mPad138[0xb20 - 0x138];
  OrderFlagsExec* mB20;
  uint8_t  mPadB24[0xb48 - 0xb24];
  OrderManagerExec* mB48;
  uint8_t  mPadB4c[0xb54 - 0xb4c];
  AnimCreatureExec* mB54;
  uint32_t mB58;
  uint8_t  mPadB5c[0xbbc - 0xb5c];
  float    mBbc;
  uint8_t  mPadBC0[0xe3c - 0xbc0];
  int      mE3c;
  uint8_t  mPadE40[0xe62 - 0xe40];
  uint8_t  mE62;
  uint8_t  mPadE63[0xe84 - 0xe63];
  Entity388* mE84;
  uint8_t  mPadE88[0xf98 - 0xe88];
  void*    mF98;
};

struct RefObj { virtual void s0(); virtual void s1(); virtual void s2(); };
static inline void Release(void* p){ if(p) (*(void(__thiscall*)(void*))((*(void***)p)[1]))(p); }

// =======================================================================
struct C {
  // simple accessors
  bool __thiscall Pred70(int x);
  bool __thiscall Preda0(int x);
  float __thiscall GetA();
  float __thiscall GetB();
  float __thiscall Get574();
  bool __thiscall Flag388();
  bool __thiscall Flag389();
  uint32_t __thiscall FlagF();
  void __thiscall SetE84(void* p);
  float __thiscall Speed1(char b);
  int  __thiscall FindIndex(int key);
  void __thiscall CallFind13();
  void __thiscall CallFind27();
  void __thiscall IsDefaultSpecies_();
  C*   __thiscall CopyRec(void* src);
  C*   __thiscall QuatHalf(float a);
  int  __thiscall RelationIndex(int idx, char b);
  __declspec(noinline) int __thiscall Cdb0();
  void __thiscall C200(float f);
  int  __thiscall C0bd70(void* fields);
  void __thiscall C0bee0(int a, int b);
  void __thiscall C0bf10(int a,int b,int c,int d,float e,int f,int g,int h,int i,int j,char k);
  int  __thiscall C0c250_();
  void __thiscall C0c630(char b,int* p3,int* p4,int* p5);
  void __thiscall C0c4b0(float a);
  bool __thiscall C0bb90();                                     // 0x00c0bb90
};

// @ 0x00c0be70
bool __cdecl FUN_00c0be70(int x) {
  return x == 0x25b3bc0 || x == 0x772ff58 || x == 0x7995fdc || x == 0x7982fb2 || x == 0x7b5063e;
}
// @ 0x00c0bea0
bool __cdecl FUN_00c0bea0(int x) {
  return x == 0x5261d56 || x == 0x5261d78 || x == 0x692e5bf || x == 0x5485a4c ||
         x == 0x77300f2 || x == 0x77300fb || x == 0x77300ff;
}
// @ 0x00c0c010
float __thiscall C::GetA() {
  void* p = *(void**)((char*)this + 0xe84);
  if (p) { float f = *(float*)((char*)p + 0x350); if (f >= 0.0f) return f; }
  return gF_150c8b8;
}
// @ 0x00c0c040
float __thiscall C::GetB() {
  void* p = *(void**)((char*)this + 0xe84);
  if (p) { float f = *(float*)((char*)p + 0x354); if (f >= 0.0f) return f; }
  return gF_150c8b4;
}
// @ 0x00c0c0d0
float __thiscall C::Get574() { return *(float*)((char*)*(void**)((char*)this + 0xa60) + 0x574); }
// @ 0x00c0c0e0
bool __thiscall C::Flag388() {
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x388) != 0;
}
// @ 0x00c0c100
bool __thiscall C::Flag389() {
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x389) != 0;
}
// @ 0x00c0c310
uint32_t __thiscall C::FlagF() { return (*(uint32_t*)((char*)this + 0xb58) >> 0xf) & 1; }
// @ 0x00c0c180
void __thiscall C::SetE84(void* p) {
  *(void**)((char*)this + 0xe84) = p;
  if (p) *(void**)((char*)this + 0xe80) = *(void**)((char*)p + 0x10);
}
// @ 0x00c0c1c0
float __thiscall C::Speed1(char b) {
  float v = 1.0f;
  if (*(int*)((char*)this + 0xb34) != 1 && b == 0) v = gF_150c8cc;
  return v;
}
// @ 0x00c0c080
int __thiscall C::FindIndex(int key) {
  uint32_t n = (*(uint32_t(__thiscall*)(void*))((*(void***)this)[0xb0/4]))(this);
  for (uint32_t i = 0; i < n; ++i) {
    void* e = (*(void*(__thiscall*)(void*, uint32_t))((*(void***)this)[0xb4/4]))(this, i);
    if (*(int*)((char*)e + 8) == key) return (int)i;
  }
  return -1;
}
// @ 0x00c0c140
void __thiscall C::CallFind13() { if (FindIndex(0xd) == -1) FindIndex(0x52); }
// @ 0x00c0c160
void __thiscall C::CallFind27() { if (FindIndex(0x27) == -1) FindIndex(0x50); }
// @ 0x00c0c2d0
void __thiscall C::IsDefaultSpecies_() {
  FUN_00401090();
  void* p = FUN_004df420();
  *(void**)((char*)this + 0); // no-op to keep this used
}

// @ 0x00c0c3e0  copy 0x24-byte record with refcount on +0x20
C* __thiscall C::CopyRec(void* srcv) {
  uint32_t* s = (uint32_t*)srcv;
  uint32_t* d = (uint32_t*)this;
  d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3]; d[4]=s[4];
  *(float*)(d+5) = *(float*)(s+5);
  *(uint8_t*)(d+6) = *(uint8_t*)(s+6);
  d[7]=s[7];
  void* o = (void*)s[8];
  d[8]=(uint32_t)o;
  if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
  return this;
}

// @ 0x00c0c440  copy records [first,last) to dst
void* __cdecl FUN_00c0c440(uint32_t* first, uint32_t* last, uint32_t* dst) {
  while (first != last) {
    if (dst) {
      dst[0]=first[0]; dst[1]=first[1]; dst[2]=first[2]; dst[3]=first[3];
      dst[4]=first[4]; dst[5]=first[5];
      *(uint8_t*)(dst+6) = *(uint8_t*)(first+6);
      dst[7]=first[7];
      void* o = (void*)first[8];
      dst[8]=(uint32_t)o;
      if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
    }
    first += 9; dst += 9;
  }
  return dst;
}

// @ 0x00c0c4b0  quaternion rotate by half angle
C* __thiscall C::QuatHalf(float a) {
  float* q = (float*)this;
  float x=q[0], y=q[1], z=q[2], w=q[3];
  float c = cosf(a * 0.5f);
  float s = sinf(a * 0.5f);
  q[0] = x*c + w*0.0f - z*s + y*0.0f;
  q[1] = y*c + w*s + z*0.0f - x*0.0f;
  q[2] = z*c - y*0.0f + x*s + w*0.0f;
  q[3] = w*c - x*0.0f - y*s - z*0.0f;
  return this;
}

// @ 0x00c0c5b0  water reflection helper (cdecl: object passed on the stack)
bool __cdecl C5b0(int obj, int b, int* out) {
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    int r = FUN_00ebfd50(obj, b);
    *out = r;
    return r != b;
  }
  void* p = *(void**)((char*)obj + 0xe84);
  if (p && *(char*)((char*)p + 0x388) != 0) {
    void* mgr = *(void**)0x168d900;
    if (FUN_00c0b1c0((void*)b, (void*)out, *(int*)((char*)mgr + 0x1c))) return true;
  }
  return FUN_00c0b220((void*)b, (void*)out);
}

// @ 0x00c0c200
void __thiscall C::C200(float f) {
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10 && *(int*)((char*)g_16c7aa4 + 0xcc) == 2) {
    if (this) FUN_00ef1930((char*)this + 0x5a8, f);
    else FUN_00ef1930(0, f);
  }
}

// @ 0x00c0cdb0
int __thiscall C::Cdb0() {
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    void* obj = 0;
    if (this) obj = (*(void*(__thiscall*)(void*, int))((*(void***)this)[0xc/4]))(this, 0xd0036e08);
    GameModeResult* r = (GameModeResult*)((GameModeObject*)obj)->Get();
    if (r) return (int)r->m490;
  }
  CreatureB20* p = (CreatureB20*)((CreatureFields*)this)->mB20;
  if (p) return p->m544;
  return 0;
}

// @ 0x00c0ce30
int __thiscall C::RelationIndex(int idx, char b) {
  if (*(int*)((char*)this + 0xb20) == 0) return 0;
  if (idx == 0) return 0;
  int v = Cdb0() + g_15716d8[idx];
  if (b == 0) v += *(int*)((char*)this + 0xfa0);
  if (v < 0) return 0;
  return v < 6 ? v : 5;
}

// @ 0x00c0c250
int __thiscall C::C0c250_() {
  CreatureFields* cf = (CreatureFields*)this;
  bool b = false;
  void* p = FUN_00b3d4c0();
  if (p) {
    void* nm = SP_NounManager();
    void* av = ((GameNounManager*)nm)->GetAvatar();
    b = ((CreatureBaseMgr*)p)->FUN_00ba3f90(&cf->mB28, av, this) == 6;
  }
  if (((cf->mB58 >> 7) & 1) == 0 && !b) {
    bool def = (*(bool(__thiscall*)(void*))((*(void***)this)[0xd0/4]))(this);
    if (!def) return 0;
    if (SP_GetCurrentGameMode() != (void*)0x1654c10) return 1;
    return 0;
  }
  return 1;
}

// @ 0x00c0ccc0
char __cdecl FUN_00c0ccc0(float* p, float dt) {
  TransitionState* s = (TransitionState*)p;
  TransitionObject* pre = (TransitionObject*)s->m3c;
  void* obj = pre ? (void*)(*(void*(__thiscall*)(void*, int))((*(void***)pre)[0xc/4]))(pre, 0xce9f6639) : 0;
  TransitionObject* o = (TransitionObject*)obj;
  char c = (*(char(__thiscall*)(void*))((*(void***)o)[0x2c/4]))(o);
  if (c == 0 && o->mB5e == 0 && o->m135 != 0) {
    if (s->m4 >= s->m0) {
      void* ent = 0;
      if (s->m40 != 0) ent = FUN_00c0c320(&s->m40);
      int u = -1;
      if (ent) u = (*(int(__thiscall*)(void*))((*(void***)ent)[0x10/4]))(ent);
      void* vt = *(void**)o->mSub5a8;
      float f = s->m8 * s->m0;
      (*(void(__thiscall*)(void*, float, int, int, void*, void*))((*(void***)vt)[0x18/4]))(
          o->mSub5a8, f, u, 7, (void*)0x168d910, ent);
      s->m4 = 0.0f;
      return 1;
    } else {
      s->m4 += dt;
      return 1;
    }
  }
  return 0;
}

// bea0 placeholder body needs a real method: use Preda0 already (definition above)
// @ 0x00c0bd70
int __thiscall C::C0bd70(void* fields) {
  int sum = ((GameDataFields*)this)->GetFieldValues(fields);
  {
    cVarListSerializer v((char*)this + 0x34, (void*)0x15816b8, 0x1a80d26);
    sum += v.GetFields(fields);
  }
  sum += ((LocoFields*)((char*)this + 0xc0))->GetFieldValues(fields);
  {
    cVarListSerializer v((char*)this + 0x5a8, (void*)0x1570858, 0x1a80d26);
    sum += v.GetFields(fields);
  }
  cVarListSerializer v3(this, (void*)0x1571798, 0x1a80d26);
  sum += v3.GetFields(fields);
  return sum;
}
// @ 0x00c0bee0
struct CCommunityStub { void __thiscall func60h(int,int); };
void __thiscall C::C0bee0(int a, int b) {
  ((CCommunityStub*)this)->func60h(a, b);
  *(uint8_t*)((char*)this + 0xa9d) = 1;
}
// @ 0x00c0bf10
void __thiscall C::C0bf10(int a,int b,int c,int d,float e,int f,int g,int h,int i,int j,char k) {
  CreatureFields* cf = (CreatureFields*)this;
  behavior_stimuli* bs = (behavior_stimuli*)((char*)cf->mB4c + 8);
  bs->ClearAll((~a) & c, (~b) & d);
  void* r = bs->Play(a, b);
  bool changed = r == 0;
  if (r != 0 && k != 0) {
    StimulusResult* rr = (StimulusResult*)r;
    changed = !(rr->m2c == j && rr->m10 == i);
  }
  if ((f != 0 || g != 0) && changed) {
    bs->Set((void*)f, (uint32_t)g, gF_146a32c, 0);
    if ((cf->mB58 >> 9) & 1) {
      void* p = FUN_00b3d320();
      if (((DatabasePackedFile*)p)->GetLocation() == (void*)0x1654c01) {
        g_169e37c = 0;
      } else {
        void* q = FUN_00b3d320();
        if (((DatabasePackedFile*)q)->GetLocation() == (void*)0x1654c10) g_169e37c = 0;
      }
    }
  }
  StimulusResult* e2 = (StimulusResult*)bs->Set((void*)a, (uint32_t)b, e, (void*)j);
  e2->m0c = h;
  e2->m10 = i;
}
// @ 0x00c0c630
void __thiscall C::C0c630(char bparam, int* p3, int* p4, int* p5) {
  LocomotionExec* o = (LocomotionExec*)this;
  uint8_t* sub58 = (uint8_t*)this + 0x58;
  uint8_t* subc0 = (uint8_t*)this + 0xc0;
  char cVar4 = (*(char(__thiscall*)(void*))((*(void***)subc0)[0x58/4]))(subc0);
  bool bVar3 = false;
  if (o->mE84 != 0 && o->mE84->m388 != 0) bVar3 = true;
  (*(void(__thiscall*)(void*))((*(void***)this)[0x20/4]))(this);
  *p5 = -1;
  *p4 = 0x2481de5;
  if (o->mE3c != -1) { *p4 = o->mE3c; return; }

  if (o->m137 == 0) {
    void* r58 = (*(void*(__thiscall*)(void*))((*(void***)sub58)[0x20/4]))(sub58);
    if (r58 != 0) {
      void* r58b = (*(void*(__thiscall*)(void*))((*(void***)sub58)[0x20/4]))(sub58);
      if ((*(int(__thiscall*)(void*))((*(void***)r58b)[0x1c/4]))(r58b) == 0x114242e6) {
        *p4 = 0x3cc7eb4;
        return;
      }
    }
    if (o->m110 & 0x1000) {
      if (bVar3) return;
      float v = (*(float(__thiscall*)(void*))((*(void***)subc0)[0xc8/4]))(subc0);
      *p4 = (v <= gF_146a330) ? 0x2e6ea7d : 0x293bb70;
      return;
    }
    if (o->mE62 != 0) { *p4 = 0x7982f7e; return; }
    OrderFlagsExec* m = o->mB20;
    if (m->m61c == 0) {
      *p4 = ((m->m6a0 != 0) ? 0xe019ea : 0) + 0x692e6a9;
      return;
    }
    if ((o->mB58 >> 9) & 1) *p4 = ((m->m698 != 0) ? 0xe01b3c : 0) + 0x692e5bf;
    else                    *p4 = ((m->m698 != 0) ? 0x24ce383 : 0) + 0x5261d78;
    return;
  }

  int a0 = 0, a1 = 0;
  AnimCreatureExec* ac = o->mB54;
  ((Object1734*)((char*)ac->m17c + 0x15b8))->FUN_009ce720(&a0, &a1);
  void* f98 = o->mF98;
  if (a0 == 2 && f98 == 0) {
    float* vel = ((LocomotiveObject*)subc0)->GetVelocity();
    float tmp[3];
    float* q = (*(float*(__thiscall*)(void*, void*))((*(void***)subc0)[0x5c/4]))(subc0, tmp);
    float dot = q[2]*vel[2] + q[1]*vel[1] + q[0]*vel[0];
    if (!(dot <= gF_1572040)) goto LRand;
  }
  if (ac->IsOrientStopAnim((uint32_t)*p3)) {
    if (bparam == 0) {
      if (!ac->FUN_00a04940(ac->m188)) {
        if (f98 == 0) goto LRand;
      }
    }
  }
  if (bVar3) goto L957;
  if (((C*)this)->C0bb90()) { *p4 = 0x2481deb; return; }
  if (o->mB48->FindSlot(0, 0, this, 0) != -1) { *p4 = 0x4adc8db; return; }
L957:
  if (cVar4 != 0 && gF_1687a10 > o->mBbc) { *p4 = 0x54ac987; return; }
  {
    Global169e370* r = (Global169e370*)FUN_00d2e340();
    if ((a0 != 0 && f98 != 0) ||
        (((o->mB58 >> 9) & 1) != 0 && r != 0 && r->m11 != 0 &&
         (r->mF != 0 || r->m10 != 0))) {
      if (*p3 == 0x4866dab) { *p4 = 0x4866dab; return; }
      *p4 = 0x4866d8e;
      *p5 = 0x4866dab;
    }
  }
  return;
LRand:
  if (ac->IsOrientStopAnim((uint32_t)*p3)) { *p4 = *p3; return; }
  {
    uint32_t rr = ((RandomLCG*)0x1601760)->RandomUint32Uniform(3);
    if (rr == 1) *p4 = 0x4866dcb;
    else if (rr == 2) *p4 = 0x4866dd4;
    else *p4 = 0x4866dc3;
  }
}

// @ 0x00c0ca00
bool __cdecl FUN_00c0ca00(float* p1, float* p2, float t, float* out, float* vel) {
  PlanetModelObj* pm = (PlanetModelObj*)SP_PlanetModel();
  float g = pm->FUN_00b7e490();
  float dx = p2[0] - p1[0];
  float dy = p2[1] - p1[1];
  float dz = p2[2] - p1[2];
  float dist = sqrtf(dx*dx + dy*dy + dz*dz);
  float a1 = asinf(-((dist * g) / (t * t)));
  float bx = p2[0], by = p2[1], bz = p2[2];
  if (vel[0] != g_168d910 || vel[1] != g_168d914 || vel[2] != g_168d918) {
    float s1 = sinf(a1 * 0.5f);
    float f = (s1 * t + s1 * t) / -g;
    bx += vel[0] * f;
    by += vel[1] * f;
    bz += vel[2] * f;
  }
  dx = bx - p1[0];
  dy = by - p1[1];
  dz = bz - p1[2];
  dist = sqrtf(dx*dx + dy*dy + dz*dz);
  float inv = 1.0f / dist;
  float q = -((dist * g) / (t * t));
  if (q <= 1.0f && q >= -1.0f) {
    float ang = 0.5f * asinf(q);
    float s2 = sinf(ang) * t;
    float c2 = cosf(ang) * t;
    float invA = 1.0f / sqrtf(p1[0]*p1[0] + p1[1]*p1[1] + p1[2]*p1[2]);
    out[0] = (dx * inv) * c2 + (p1[0] * invA) * s2;
    out[1] = (dy * inv) * c2 + (p1[1] * invA) * s2;
    out[2] = (dz * inv) * c2 + (p1[2] * invA) * s2;
    return true;
  }
  return false;
}
