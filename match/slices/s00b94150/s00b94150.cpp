// match/slices/s00b94150/s00b94150.cpp
// Object file: unknown module (falls in the modmap gap 00b938d0..00b9c5c0, between
// SPGameEditInputStrategy.obj and SPMission.obj), VS2008 SP1.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// This slice is the cTribe tool-authoring path: FUN_00b94150 spawns a tribe and
// stamps its tools, FUN_00b94420 / FUN_00b94670 are the "is this spot free" tests
// over the planet's point lists, and CA is a small (lo,hi) radius helper object
// (vtable 0x1465a34) that emits transform/orientation messages.  CB is a
// refcounted holder (vtable 0x1465a58, base vtable 0x13ec458).
//
// Every callee below is unnamed in the retail image; the stub structs only exist
// so the compiler can produce a `call` at the right address/convention (chk.py
// compiles to .obj, so an unresolved declaration is enough).

#include "game/types.h"
#include <math.h>

// ---- globals (address in the comment) ----
extern int   g_169ca74;                                  // 0x169ca74
extern float g_1688890;                                  // 0x1688890  Vec3 sentinel .x
extern float g_1688894;                                  // 0x1688894  Vec3 sentinel .y
extern float g_1688898;                                  // 0x1688898  Vec3 sentinel .z
extern float g_1485720;                                  // 0x1485720  1.0f
extern char  g_1688924[];                                // 0x1688924  Matrix33 const
extern float g_1688948;                                  // 0x1688948  RandomRange hi
extern int   g_1465a0c[10];                              // 0x1465a0c  tool type ids
extern float g_1465968;                                  // 0x1465968  20.0f
extern char  g_168894c[];                                // 0x168894c  Vec3 const
extern float g_168897c;                                  // 0x168897c
extern float g_1688980;                                  // 0x1688980
extern float g_1688984;                                  // 0x1688984
extern float g_1471064;                                  // 0x1471064
extern double g_1465a50;                                 // 0x1465a50  2*pi
extern float g_140eba8;                                  // 0x140eba8  6.0f
extern float g_13f5650;                                  // 0x13f5650  4.0f
extern float g_140ebb0;                                  // 0x140ebb0  10.0f

// RandomLinearCongruential singleton (0x1601760); RandomDoubleUniform is 0x9360d0.
namespace EA { namespace Random {
struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 0x9360d0
}}
extern EA::Random::RandomLinearCongruential g_1601760;

// ---- free callees ----
void* __cdecl SP_NounManager();                          // 0xb3d300
void* __cdecl SP_PlanetModel();                          // 0xb3d350
void* __cdecl SP_PropertyManager();                      // 0x67de30
void* __cdecl SP_CreateTribe(void*, int, int, int, int, int);   // 0xc93160
void  __cdecl operator_delete_(void*);                   // 0xf47380

float* __cdecl Matrix3FromQuaternion(void* dest, const void* quat);      // 0x59c190
float* __cdecl QuaternionFromMatrix33(void* dest, const void* m, float w); // 0x472b80
float* __cdecl FUN_0059aed0(void* dest, const void* a, const void* b);   // 0x59aed0
float* __cdecl SP_QuaternionToMatrix(void* dest, const void* q);         // 0x4a9b40
char   __cdecl FUN_00b90cb0(float* pos, float r);                        // 0xb90cb0

// ---- stub types ----
struct Vec3 { float x, y, z; };
struct Matrix33 { float m[9]; };

// cSPTransformOps (this slice only uses its Assign slot).
struct cSPTransformOps {
  char raw[0x40];
  void* Assign(const void* src);                         // 0x537dc0
};

// Planet model (thiscall callees off the SP::PlanetModel singleton).
struct cPlanetModel {
  char raw[0x400];
  float* FUN_00b7ee70(void* dest, void* src);            // 0xb7ee70
  char   FUN_00b832d0(float* pos, float v);              // 0xb832d0
  void*  FUN_00b81a40(void* dest, void* src);            // 0xb81a40
  void*  BuildSurfaceOrientation(void* dest, void* src); // 0xb7f190
  void*  BuildSurfaceOrientation2(void* out, void* pos, void* dir); // 0xb7f250
};

// cTribe (only the two named helpers matter here).
struct cTribeBase {
  char raw[0x200];
  void* GetToolOfType(int t);                            // 0xc8f6e0
  void  ReserveToolsSlots(int n);                        // 0xc998c0
};

// The object FUN_00b94420 / FUN_00b94670 iterate over (its list accessors).
struct ListProvider {
  void  GetList(void* out);                              // 0xc73520
  void* GetPtrList();                                    // 0xc71010
};
struct Range { int* begin; int* end; };                  // {begin,end} pair

struct UintArray { void* Self(); };                      // 0x572590
struct Elem {
  float* Pos();                                          // 0x6e64f0 (returns elem+4)
};

// Matrix3 helper (assign a constant).
struct M3Op { void Assign(const void* src); };           // 0x41cb40

// ---- vtable-slot call helpers (emits `call [vt+off]`) ----
typedef void  (__thiscall *FnVoid)(void*);
typedef void* (__thiscall *FnPtr)(void*);
typedef void* (__thiscall *FnPtrI)(void*, int);
typedef void* (__thiscall *FnPtrFF)(void*, float, float);
typedef void  (__thiscall *FnVoidP)(void*, void*);
typedef void  (__thiscall *FnVoidPP)(void*, void*, void*);
typedef void  (__thiscall *FnVoidIII)(void*, int, int, void*);

static inline FnVoid   VtV(void* o, int off) { return *(FnVoid*)  (*(char**)o + off); }
static inline FnPtr    VtP(void* o, int off) { return *(FnPtr*)   (*(char**)o + off); }
static inline FnPtrI   VtPI(void* o, int off){ return *(FnPtrI*)  (*(char**)o + off); }
static inline FnVoidP  VtVP(void* o, int off){ return *(FnVoidP*) (*(char**)o + off); }
static inline FnVoidPP VtVPP(void* o, int off){return *(FnVoidPP*)(*(char**)o + off); }
static inline FnVoidIII VtVIII(void* o, int off){ return *(FnVoidIII*)(*(char**)o + off); }

// RandomRange: exactly the retail x87 shape (range*(r)+lo, clamped to [lo,hi]).
static double RandomRange(double lo, double hi) {
  double range = hi - lo;
  double r = g_1601760.RandomDoubleUniform();
  double v = r * range + lo;
  if (v > hi) v = hi;
  else if (v < lo) v = lo;
  return v;
}

// ===========================================================================
// message layout shared by the CA methods
// ===========================================================================
struct XformMsg {
  unsigned short flags;   // +0x00
  unsigned short seq;     // +0x02
  float x, y, z, w;       // +0x04
  Matrix33 mat;           // +0x14
};

// ===========================================================================
// CA : (lo,hi) radius helper, vtable 0x1465a34.
//   The retail ctor stores its own vptr only AFTER the base's +4 int store, which
//   is what a polymorphic base that owns an int member at +4 produces (the base
//   ctor zeroes it first, then the derived's vptr store replaces the base's).
// ===========================================================================
struct VBaseA {
  virtual ~VBaseA() {}
  int m4;
  VBaseA() : m4(0) {}
};

struct CA : VBaseA {
  float mLo;              // +0x08
  float mHi;              // +0x0c
  CA(float lo, float hi);
  void funcAC0(int param2, unsigned short* param3, void* param4);                 // 0xb94ac0
  void funcBE0(int param2, unsigned short* param3, unsigned short* param4);       // 0xb94be0
  void funcDE0(int param2, unsigned short* param3, cSPTransformOps* param4);      // 0xb94de0
};

// @ 0x00b94a90
CA::CA(float lo, float hi) : mLo(lo), mHi(hi) {}

// ===========================================================================
// CB : refcounted holder, vtable 0x1465a58 (base vtable 0x13ec458).
//   User-declared ctor/dtor reproduce the retail store order exactly.
// ===========================================================================
template <class T> struct Ref {
  T* mp;
  Ref() : mp(0) {}
  ~Ref() { if (mp && *(int*)((char*)mp - 4) != 0) operator_delete_(mp); }
};

struct VBaseB {
  virtual ~VBaseB() {}
  int m4;
  VBaseB() : m4(0) {}
};

struct CB : VBaseB {
  Ref<void>  m8;          // +0x08
  void*      mC;          // +0x0c
  void*      m10;         // +0x10
  char       pad14[8];    // +0x14
  Ref<void>  m1c;         // +0x1c
  void*      m20;         // +0x20
  void*      m24;         // +0x24
  CB();
  ~CB();
};

// @ 0x00b95050
CB::CB() : mC(0), m10(0), m20(0), m24(0) {}

// @ 0x00b95070
CB::~CB() {}

// @ 0x00b94150
void* __cdecl FUN_00b94150(void* p1, void* p2, void* p3, char p4)
{
  (void)p2; (void)p3;
  unsigned short msg[4 + 12 + 18];   // scratch for the transform message (0x38 bytes)
  (void)msg;

  SP_NounManager();
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  void* q = *(void**)((char*)pm + 0x24);   // local_a4._4_4_

  int n = g_169ca74;
  char toolEnable[16] = {0};
  toolEnable[10] = 1;

  cTribeBase* tribe = (cTribeBase*)SP_CreateTribe(p1, 0, n, n * 10, 0, 0);

  void* prop = 0;                          // local_a4._0_4_ (smart pointer)
  if (p4 == 0) {
    void* pmgr = SP_PropertyManager();
    if (prop) {
      void* t = prop;
      prop = 0;
      (*VtV(t, 4))(t);
    }
    (*VtVIII(pmgr, 0x2c))(pmgr, 0x3bce99e9, 0x302a1c9, &prop);
    if (prop) {
      XformMsg m;
      m.flags = 0;
      m.seq = 0;
      m.x = g_1688890;
      m.y = g_1688894;
      m.z = g_1688898;
      m.w = g_1485720;
      ((M3Op*)&m.mat)->Assign(g_1688924);

      char* sub = (char*)tribe + 0x120;
      float* p = (float*)(*VtP(sub, 0x2c))(sub);
      m.x = p[0];
      m.y = p[1];
      m.z = p[2];
      m.flags |= 4;
      m.seq++;
      void* quat = (*VtP(sub, 0x30))(sub);
      float mtmp[9];
      float* mm = Matrix3FromQuaternion(mtmp, quat);
      for (int i = 0; i < 9; i++)
        ((float*)&m.mat)[i] = mm[i];
      m.flags |= 2;
      m.seq++;
      (*VtVPP(q, 0x54))(q, &m, prop);

      void* t2 = prop;
      prop = 0;
      (*VtV(t2, 4))(t2);
    }
  }

  for (unsigned off = 0; off < 0x28; off += 4) {
    int tt = g_1465a0c[off >> 2];
    if (toolEnable[tt] == 0)
      continue;
    if (tribe->GetToolOfType(tt) != 0)
      continue;
    void* tool = (*VtPI(tribe, 0xb4))(tribe, tt);
    if (tool == 0)
      continue;
    (*VtVP(tool, 0x64))(tool, tribe);

    double r0 = RandomRange(0.0, (double)g_1688948);
    double r1 = RandomRange(4.0, 10.0);
    float f1 = (float)r1;
    float f0 = (float)r0;
    char* sub = (char*)tribe + 0x120;
    void* pos = (*(FnPtrFF*)(*(char**)sub + 0x2c))(sub, f1, f0);
    char buf[0x40];
    pm->FUN_00b81a40(buf, pos);

    char* toolSub = (char*)tool + 0x34;
    (*VtVP(toolSub, 0x38))(toolSub, buf);
    void* p2 = (*VtP(toolSub, 0x2c))(toolSub);
    void* orient = pm->BuildSurfaceOrientation(buf, p2);
    (*VtVP(toolSub, 0x3c))(toolSub, orient);
  }

  tribe->ReserveToolsSlots(0);
  return tribe;
}

// @ 0x00b94420
char __cdecl FUN_00b94420(void* self, float* pos, float r1, float r2, float r3)
{
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float local[3];
  float* p = pm->FUN_00b7ee70(local, pos);
  float len = (float)sqrt((double)p[0] * (double)p[0] +
                          (double)p[1] * (double)p[1] +
                          (double)p[2] * (double)p[2]);

  char bl;
  if (r3 <= len)
    bl = 0;
  else if (pm->FUN_00b832d0(pos, 15.0f))
    bl = 0;
  else
    bl = pm->FUN_00b832d0(pos, 20.0f) ? 1 : 0;

  Range arr;
  ((ListProvider*)self)->GetList(&arr);
  int n = (int)(((char*)arr.end - (char*)arr.begin) >> 2);
  if (n > 0 && bl) {
    for (int i = 0; i < n; i++) {
      float* pf = (float*)((UintArray*)arr.begin[i])->Self();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz > r1 * r1)
          bl = 1;
        else
          bl = 0;
      }
    }
  }

  Range* arr2 = (Range*)((ListProvider*)self)->GetPtrList();
  int n2 = (int)(((char*)arr2->end - (char*)arr2->begin) >> 2);
  if (n2 > 0 && bl) {
    for (int i = 0; i < n2; i++) {
      float* pf = ((Elem*)arr2->begin[i])->Pos();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz > r2 * r2)
          bl = 1;
        else
          bl = 0;
      }
    }
  }

  if (FUN_00b90cb0(pos, g_1465968))
    bl = 0;

  if (arr.begin && *(int*)((char*)arr.begin - 4) != 0)
    operator_delete_(arr.begin);

  return bl;
}

// @ 0x00b94670
bool __cdecl FUN_00b94670(void* self, float* pos, float r1, float r2, float r3,
                          float r4, float r5)
{
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float local[3];
  float* p = pm->FUN_00b7ee70(local, pos);
  float len = (float)sqrt((double)p[0] * (double)p[0] +
                          (double)p[1] * (double)p[1] +
                          (double)p[2] * (double)p[2]);

  char result = (len < r5) ? 1 : 0;

  Range arr;
  ((ListProvider*)self)->GetList(&arr);
  int n = (int)(((char*)arr.end - (char*)arr.begin) >> 2);
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      if (!result)
        break;
      float* pf = (float*)((UintArray*)arr.begin[i])->Self();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz <= r1 * r1)
          result = 0;
        else
          result = 1;
      }
    }
  }

  char hasAny = 0;
  char outside = 0;
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      if (!result)
        break;
      float* pf = (float*)((UintArray*)arr.begin[i])->Self();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        hasAny = 1;
        if (dx * dx + dy * dy + dz * dz >= r2 * r2)
          outside = 0;
        else
          outside = 1;
      }
    }
    if (hasAny && result && !outside)
      result = 0;
  }

  Range* arr2 = (Range*)((ListProvider*)self)->GetPtrList();
  int n2 = (int)(((char*)arr2->end - (char*)arr2->begin) >> 2);
  if (n2 > 0) {
    for (int i = 0; i < n2; i++) {
      if (!result)
        break;
      float* pf = ((Elem*)arr2->begin[i])->Pos();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz <= r3 * r3)
          result = 0;
      }
    }
  }

  char hasAny2 = 0;
  char outside2 = 0;
  if (n2 > 0) {
    for (int i = 0; i < n2; i++) {
      if (!result || hasAny2)
        break;
      float* pf = ((Elem*)arr2->begin[i])->Pos();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        hasAny2 = 1;
        if (dx * dx + dy * dy + dz * dz >= r4 * r4)
          outside2 = 0;
        else
          outside2 = 1;
      }
    }
  }

  if (FUN_00b90cb0(pos, 20.0f))
    result = 0;

  if (hasAny2 && result && !outside2)
    result = 0;

  if (arr.begin && *(int*)((char*)arr.begin - 4) != 0)
    operator_delete_(arr.begin);

  return result != 0;
}

// @ 0x00b94ac0
void CA::funcAC0(int param2, unsigned short* param3, void* param4)
{
  float f = (float)RandomRange(mLo, mHi);
  float zero = 0.0f;

  float q[4];
  float* qp = QuaternionFromMatrix33(q, (char*)param2 + 0x14, zero);

  float v[3] = { 0.0f, f, 0.0f };   // retail builds {0,f,0} and rotates it
  float out[3];
  float* op = FUN_0059aed0(out, v, qp);

  float x = op[0] + *(float*)(param2 + 4);
  float y = *(float*)(param2 + 8) + op[1];
  float z = *(float*)(param2 + 0xc) + op[2];

  param3[0] |= 4;
  param3[1]++;
  *(float*)(param3 + 2) = x;
  *(float*)(param3 + 4) = y;
  *(float*)(param3 + 6) = z;

  ((cSPTransformOps*)param4)->Assign(param3);
}

// @ 0x00b94be0
void CA::funcBE0(int param2, unsigned short* param3, unsigned short* param4)
{
  g_1601760.RandomDoubleUniform();   // retail burns one sample first

  // The two samples are doubles; len is squared in double too, so the loop test is exact.
  // Retail orders the exit tests as `if (len <= mLo) break; if (mHi > len) loop; break;`
  // (a NaN mLo/mHi therefore exits rather than spinning forever), so mirror that order.
  double a = 0.0, b = 0.0, len = 0.0;
  for (;;) {
    float hi = mHi;
    a = RandomRange(-(double)hi, (double)hi);
    b = RandomRange(-(double)hi, (double)hi);
    len = sqrt(a * a + b * b);
    // First test in the x87 register (extended len vs mLo); the second one rounds len to
    // float into memory and compares in SSE, exactly as retail's `fst dword` + `comiss` does.
    if (len <= (double)mLo) break;
    volatile float lenf = (float)len;
    if (mHi > lenf) continue;
    break;
  }

  float q[4];
  float* qp = QuaternionFromMatrix33(q, (char*)param2 + 0x14, 0.0f);

  float v[3] = { (float)b, (float)a, 0.0f };  // retail builds {(float)b,(float)a,0}
  float out[3];
  float* op = FUN_0059aed0(out, v, qp);

  float x = op[0] + *(float*)(param2 + 4);
  float y = *(float*)(param2 + 8) + op[1];
  float z = *(float*)(param2 + 0xc) + op[2];

  for (int i = 0; i < 9; i++) {
    ((float*)(param3 + 10))[i] = ((float*)(param2 + 0x14))[i];
    ((float*)(param4 + 10))[i] = ((float*)(param2 + 0x14))[i];
  }
  param3[0] |= 2;
  param3[1]++;
  param4[0] |= 2;
  param4[1]++;

  param3[1]++;
  param3[0] |= 4;
  *(float*)(param3 + 2) = x;
  *(float*)(param3 + 4) = y;
  *(float*)(param3 + 6) = z;

  param4[0] |= 4;
  param4[1]++;
  *(float*)(param4 + 2) = x;
  *(float*)(param4 + 4) = y;
  *(float*)(param4 + 6) = z;
}

// @ 0x00b94de0
void CA::funcDE0(int param2, unsigned short* param3, cSPTransformOps* param4)
{
  double ang = RandomRange(0.0, g_1465a50);
  float s = (float)sin(ang * 0.5);
  float c = (float)cos(ang * 0.5);

  float q[4];
  q[0] = s * g_168897c;
  q[1] = s * g_1688980;
  q[2] = s * g_1688984;
  q[3] = c;

  float qm[4];
  float* qmp = QuaternionFromMatrix33(qm, (char*)param2 + 0x14, 0.0f);

  float t1[3];
  float* r1 = FUN_0059aed0(t1, g_168894c, q);
  float t2[3];
  float* r2 = FUN_0059aed0(t2, r1, qmp);

  float r = (float)RandomRange(mLo, mHi);
  float x = *(float*)(param2 + 4) + r2[0] * r;
  float y = *(float*)(param2 + 8) + r2[1] * r;
  float z = *(float*)(param2 + 0xc) + r2[2] * r;

  param3[0] |= 4;
  param3[1]++;
  *(float*)(param3 + 2) = x;
  *(float*)(param3 + 4) = y;
  *(float*)(param3 + 6) = z;

  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float* mat = (float*)(param2 + 0x14);
  Matrix33 m;
  if (pm != 0) {
    float dir[3];
    dir[0] = *(float*)(param2 + 4) - x;
    dir[1] = *(float*)(param2 + 8) - y;
    dir[2] = *(float*)(param2 + 0xc) - z;
    float posv[3];
    posv[0] = x; posv[1] = y; posv[2] = z;
    float orient[4];
    void* o = pm->BuildSurfaceOrientation2(orient, posv, dir);
    mat = SP_QuaternionToMatrix(m.m, o);
  }

  for (int i = 0; i < 9; i++)
    ((float*)(param3 + 10))[i] = mat[i];

  param3[0] |= 2;
  param3[1]++;

  param4->Assign((void*)param2);
}
