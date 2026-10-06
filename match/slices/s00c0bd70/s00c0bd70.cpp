// Slice s00c0bd70 — Simulator::cGameData/cCreatureBase/cCreatureLocomotion helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

void* __cdecl SP_GetCurrentGameMode();                 // 0xb5b800
void* __cdecl FUN_00b3d4c0();                          // 0xb3d4c0
void* __cdecl SP_NounManager(void*);                   // 0xb3d300
void* __cdecl FUN_00401090();                          // 0x401090
void* __cdecl FUN_004df420();                          // 0x4df420
void  __cdecl FUN_00ef1930(void*, float);              // 0xef1930
void  __cdecl FUN_00ebfd50();                          // 0xebfd50
bool  __cdecl FUN_00c0b1c0(void*, void*, int);         // 0xc0b1c0
bool  __cdecl FUN_00c0b220(void*, void*);              // 0xc0b220
bool  __cdecl FUN_00c0bb90();                          // 0xc0bb90
int   __cdecl FUN_00bca0c0(int,int,void*,int);         // 0xbca0c0
int   __cdecl FUN_00d2e340();                          // 0xd2e340
int   __cdecl FUN_009ce720(int*, int*);                // 0x9ce720
void  __cdecl FUN_00b3d320();                          // 0xb3d320
uint32_t __cdecl EA_RandUint32(int);                   // 0xa68fb0
void  __cdecl FUN_00c04750();                          // 0xc04750
void  __cdecl FUN_00c0c320();                          // 0xc0c320

extern float  gF_150c8b8, gF_150c8b4, gF_150c8cc, gF_1485720, gF_146a32c, gF_146a330;
extern float  gF_1687a10, gF_1572040;
extern uint8_t g_169e37c;
extern void*  g_16c7aa4;
extern void*  g_168d900;
extern float  g_168d910, g_168d914, g_168d918;
extern int    g_15716d8[];
extern void*  g_156c208, *g_15816b8;

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
  void __thiscall CopyRec(void* src);
  void __thiscall QuatHalf(float a);
  bool __thiscall C5b0(int a, int b, int* out);
  int  __thiscall RelationIndex(int idx, char b);
  int  __thiscall Cdb0();
  int  __thiscall C200(float f);
  int  __thiscall C0bd70(int x);
  void __thiscall C0bee0(int a, int b);
  void __thiscall C0bf10(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,char l);
  void __thiscall C0c250_();
  void __thiscall C0c630(char b,int* p3,int* p4,int* p5);
  void __thiscall C0c4b0(float a);
  void __thiscall C0ccc0(float f);
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
void __thiscall C::CopyRec(void* srcv) {
  uint32_t* s = (uint32_t*)srcv;
  uint32_t* d = (uint32_t*)this;
  d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3]; d[4]=s[4]; d[5]=s[5];
  *(uint8_t*)(d+6) = *(uint8_t*)(s+6);
  d[7]=s[7];
  void* o = (void*)s[8];
  d[8]=(uint32_t)o;
  if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
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
void __thiscall C::QuatHalf(float a) {
  float* q = (float*)this;
  float x=q[0], y=q[1], z=q[2], w=q[3];
  float c = cosf(a * 0.5f);
  float s = sinf(a * 0.5f);
  q[0] = ((w*c + x*0.0f) - y*s) + z*0.0f;
  q[1] = ((x*c + z*s) + y*0.0f) - w*0.0f;
  q[2] = ((y*c - x*0.0f) + w*s) + z*0.0f;
  q[3] = ((z*c - w*0.0f) - x*s) - y*0.0f;
}

// @ 0x00c0c5b0
bool __thiscall C::C5b0(int a, int b, int* out) {
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10) {
    int r = 0; FUN_00ebfd50(); r = 0;
    *out = r;
    return r != b;
  }
  return false;
}

// @ 0x00c0c200
int __thiscall C::C200(float f) {
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10 && *(int*)((char*)g_16c7aa4 + 0xcc) == 2) {
    if (this) FUN_00ef1930((char*)this + 0x5a8, f);
    else FUN_00ef1930(0, f);
  }
  return 0;
}

// @ 0x00c0cdb0
int __thiscall C::Cdb0() {
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10) {
    if (this) (*(void(__thiscall*)(void*, int))((*(void***)this)[0xc/4]))(this, 0xd0036e08);
    FUN_00c04750();
  }
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
void __thiscall C::C0c250_() {
  bool b = false;
  void* p = FUN_00b3d4c0();
  if (p) {
    void* nm = SP_NounManager(this);
    void* av = (*(void*(__thiscall*)(void*))((*(void***)nm)[0]))(nm);
    (void)av;
  }
  (void)b;
}

// @ 0x00c0ccc0
void __thiscall C::C0ccc0(float f) { (void)f; }

// @ 0x00c0bea0 placeholder body needs a real method: use Preda0 already
// @ 0x00c0bd70
int __thiscall C::C0bd70(int x) { (void)x; return 0; }
// @ 0x00c0bee0
struct CCommunityStub { void __thiscall func60h(int,int); };
void __thiscall C::C0bee0(int a, int b) {
  ((CCommunityStub*)this)->func60h(a, b);
  *(uint8_t*)((char*)this + 0xa9d) = 1;
}
// @ 0x00c0bf10
void __thiscall C::C0bf10(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,char l) {
  (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)i;(void)j;(void)k;(void)l;
}
// @ 0x00c0c630
void __thiscall C::C0c630(char b,int* p3,int* p4,int* p5) { (void)b;(void)p3;(void)p4;(void)p5; }

// 0x00c0ca00 free
bool __cdecl FUN_00c0ca00(float* p1, float* p2, float angle, float* out, float* axis) {
  (void)p1;(void)p2;(void)angle;(void)out;(void)axis; return false;
}
