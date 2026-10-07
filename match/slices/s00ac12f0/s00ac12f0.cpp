// Slice s00ac12f0: cube-sphere (planet) cell helpers: neighbor lookup, cube-face cell mapping,
// water-aware distance, plus a few small copy / heap helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include <xmmintrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// externals
struct ISphereHost;
namespace SP {
struct cITerrainSphere;
class cPlanetModel {
 public:
  uint32_t pad00[9];
  ::ISphereHost* mpISphere;  // +0x24
  uint32_t pad28[9];
  uint32_t* mpCubeCells;          // +0x4c: 128x128x6 packed cell words
  uint32_t pad50[12];
  char* mpFaceNodes;              // +0x80: array of 0x18-byte nodes (object ptr at +0x14)
  uint32_t pad84[4];
  char* mpCoarseGrid;             // +0x94: 64x64x6 node index bytes
  float GetWaterHeight();         // 0xb7e390
};
cPlanetModel* __cdecl PlanetModel();  // 0xb3d350
int __cdecl WrapCubeFace(int size, uint32_t* face, uint32_t* x, uint32_t* y, int a, int b);  // 0x684ca0
struct cMessageServer {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void Register(void* handler, uint32_t id);  // vtable +0x20
};
cMessageServer* __cdecl MessageServer();  // 0x67dcc0
}  // namespace SP

struct SphereInfo {
  uint32_t pad[13];
  float outerRadius;  // +0x34
  float innerRadius;  // +0x38
};
struct ISphereHost {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual SphereInfo* GetInfo();  // vtable +0xc
};

extern float g_FltMax;       // 0x1565ba4
extern float g_CubeTexel;    // 0x1565be8 (1/64)
extern uint8_t g_FaceAxes[]; // 0x1459dfc
extern int g_NeighborFaceChanges;  // 0x167a2c8
extern char g_flag_1565b14;        // 0x1565b14

// ---------------------------------------------------------------------------
// Cube-map face/cell of a direction: returns face 0..5 and writes (u, v) in [0, N).
template <int N>
static __forceinline int CubeCell(const float* p, int* pu, int* pv) {
  float x = p[0];
  float ax = (float)fabs(x);
  float y = p[1];
  float ay = (float)fabs(y);
  float z = p[2];
  float az = (float)fabs(z);
  int u, v, face;
  if (az >= ax && az >= ay) {
    u = (int)((x / z + 1.0f) * (float)N);
    v = (int)((y / az + 1.0f) * (float)N);
    if (z < 0.0f)
      face = 1;
    else
      face = 0;
  } else if (ay < ax) {
    u = (int)((y / x + 1.0f) * (float)N);
    v = (int)((z / ax + 1.0f) * (float)N);
    face = 2;
    if (x < 0.0f) face = 3;
  } else {
    u = (int)((z / y + 1.0f) * (float)N);
    v = (int)((x / ay + 1.0f) * (float)N);
    if (y < 0.0f)
      face = 5;
    else
      face = 4;
  }
  if (u == 2 * N) u = 2 * N - 1;
  if (v == 2 * N) v = 2 * N - 1;
  *pu = u;
  *pv = v;
  return face;
}

// @ 0x00ac12f0   the 8 neighbors of a packed cell word (face<<17 | y<<8 | x), wrapping across faces
int __cdecl FUN_00ac12f0(uint32_t cell, uint32_t* out) {
  if ((((cell >> 8) & 0xff) - 1 < 0x7e) && ((cell & 0xff) - 1 < 0x7e)) {
    cell = cell & 0xfffeffff;
    out[2] = cell + 1;
    out[1] = cell - 0x100;
    out[4] = cell - 0x101;
    out[0] = cell - 1;
    out[6] = cell + 0x101;
    out[3] = cell + 0x100;
    out[5] = cell - 0xff;
    out[7] = cell + 0xff;
    return 8;
  }
  int count = 0;
  uint32_t x, y;
  uint32_t buf[17];  // buf[0] = face, buf[1..16] = the 8 (dx, dy) neighbor offsets
  buf[1] = 0xffffffff; buf[2] = 0;
  buf[3] = 0;          buf[4] = 0xffffffff;
  buf[5] = 1;          buf[6] = 0;
  buf[7] = 0;          buf[8] = 1;
  buf[9] = 0xffffffff; buf[10] = 0xffffffff;
  buf[11] = 1;         buf[12] = 0xffffffff;
  buf[13] = 1;         buf[14] = 1;
  buf[15] = 0xffffffff; buf[16] = 1;
  uint32_t result = cell;
  for (int i = 0; i < 8; ++i) {
    x = (cell & 0xff) + buf[i * 2 + 1];
    y = ((cell >> 8) & 0xff) + buf[i * 2 + 2];
    buf[0] = cell >> 17;
    if ((((x | y) & 0xffffff80) == 0) || SP::WrapCubeFace(0x80, &buf[0], &x, &y, 0, 0) < 2) {
      ++count;
      if (buf[0] != (cell >> 17)) ++g_NeighborFaceChanges;
      result = (result & 0x10000) | (((y & 0xff) | (buf[0] << 9)) << 8) | (x & 0xff);
      out[i] = result;
    } else {
      out[i] = 0xe0000;
    }
  }
  return count;
}

// @ 0x00ac1490   fill n 16-byte blocks with one float (non-temporal stores)
void __cdecl FUN_00ac1490(float* first, float value, int n) {
  float* last = first + n;
  __m128 v = _mm_set1_ps(value);
  for (; first != last; first += 4) _mm_stream_ps(first, v);
  _mm_sfence();
}

// @ 0x00ac14d0
extern void* vtbl_01459e50[];
struct VtblObj {
  void* vtbl;
  uint32_t f04;
  VtblObj();
};
VtblObj::VtblObj() {
  vtbl = vtbl_01459e50;
  f04 = 0;
}

// @ 0x00ac14e0   register this-4 (the primary base) with the message server
void __fastcall FUN_00ac14e0(char* self) {
  SP::MessageServer()->Register(self - 4, 0x1a0219e);
}

// @ 0x00ac1500
void FUN_00ac1500() { g_flag_1565b14 = 1; }

// @ 0x00ac1510   unit direction on a cube face for cell (x, y): writes 3 floats
void __cdecl FUN_00ac1510(uint32_t face, int x, int y, float* out) {
  float fx = ((float)x + 0.5f) * g_CubeTexel - 1.0f;
  float fy = ((float)y + 0.5f) * g_CubeTexel - 1.0f;
  float s = (fx * fx + 1.0f) + fy * fy;
  uint32_t signBits = face << 31;
  __m128 vs = _mm_set_ss(s);
  __m128 r = _mm_rsqrt_ss(vs);
  // one Newton-Raphson step: r = r * (1.5 - ((s * 0.5) * r) * r)
  __m128 t = _mm_mul_ss(_mm_mul_ss(_mm_mul_ss(_mm_set_ss(0.5f), vs), r), r);
  r = _mm_mul_ss(r, _mm_sub_ss(_mm_set_ss(1.5f), t));
  __m128 sr = _mm_xor_ps(_mm_load_ss((const float*)&signBits), r);
  face = face & 0xfe;
  uint8_t a1 = g_FaceAxes[face * 2 + 1];
  uint8_t a0 = g_FaceAxes[face * 2];
  _mm_store_ss(&out[g_FaceAxes[face * 2 + 2]], sr);
  _mm_store_ss(&out[a1], _mm_mul_ss(_mm_set_ss(fy), r));
  _mm_store_ss(&out[a0], _mm_mul_ss(_mm_set_ss(fx), sr));
}

// @ 0x00ac15e0
int __fastcall FUN_00ac15e0(char* self) { return (*(int*)(self + 0x48))++; }

// @ 0x00ac1610   true if two directions are in the same terrain cell (or farther than 7.04)
bool __cdecl FUN_00ac1610(const float* a, const float* b, int unused, float dist) {
  if (dist > 7.04f) return true;
  SP::cPlanetModel* pm = SP::PlanetModel();
  int au, av, bu, bv;
  int af = CubeCell<64>(a, &au, &av);
  int bf = CubeCell<64>(b, &bu, &bv);
  uint32_t cb = pm->mpCubeCells[((bf * 0x80 + bv) * 0x80) + bu];
  if ((cb & 0x18000000) != 0) return false;
  uint32_t ca = pm->mpCubeCells[((af * 0x80 + av) * 0x80) + au];
  return ((cb ^ ca) & 0x3ff0000) == 0;
}

// @ 0x00ac1970   water-aware distance from a to b (FLT_MAX when b is below the water surface)
float __cdecl FUN_00ac1970(const float* a, const float* b) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  float rb2 = (b[0] * b[0] + b[1] * b[1]) + b[2] * b[2];
  float wh = pm->GetWaterHeight();
  if (wh * wh > rb2) return g_FltMax;
  float dx = b[0] - a[0];
  float dy = b[1] - a[1];
  float dz = b[2] - a[2];
  float dist = (float)sqrt((double)((dz * dz + dx * dx) + dy * dy));
  float ra2 = (a[0] * a[0] + (a[1] * a[1] + a[2] * a[2]));
  float h = (float)sqrt((double)rb2) - (float)sqrt((double)ra2);
  if (h > 0.0f) dist = h * 8.0f + dist;
  return dist;
}

// @ 0x00ac1a70   is the object within 75 units of either point?
struct PosObj {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
  virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18();
  virtual const float* GetPosition();  // vtable +0x64
  virtual void* GetSubObject();        // vtable +0x68 (placeholder)
  virtual void* GetEntity();           // vtable +0x6c
};
int __cdecl FUN_00ac1a70(PosObj* obj, const float* a, const float* b) {
  const float* p = obj->GetPosition();
  if (5625.0f > ((p[0] - a[0]) * (p[0] - a[0]) + (p[2] - a[2]) * (p[2] - a[2])) + (p[1] - a[1]) * (p[1] - a[1]) ||
      (p = obj->GetPosition(),
       5625.0f > ((p[2] - b[2]) * (p[2] - b[2]) + (p[1] - b[1]) * (p[1] - b[1])) + (p[0] - b[0]) * (p[0] - b[0])))
    return 1;
  return 0;
}

// @ 0x00ac1b30   travel cost from a to b, scaled by what the endpoints stand on
struct Entity {
  bool __thiscall Stands(const float* pos);  // 0xbec0f0
};
float __cdecl FUN_00ac1b30(const float* a, const float* b) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  int u, v;
  int face = CubeCell<32>(b, &u, &v);
  int idx = (int)pm->mpCoarseGrid[((face * 0x40 + v) * 0x40) + u];
  char* node = pm->mpFaceNodes + idx * 0x18;
  PosObj* obj = *(PosObj**)(node + 0x14);
  if (obj) {
    if (FUN_00ac1a70(obj, a, b)) {
      Entity* ent = (Entity*)obj->GetEntity();
      bool sa = ent->Stands(a);
      bool sb = ent->Stands(b);
      float f = FUN_00ac1970(a, b);
      if (f == g_FltMax) return f;
      if (sa) {
        if (sb) return f * 32.0f;
        return f * 4.0f;
      }
      if (!sb) return f + f;
      return f;
    }
  }
  return 0.0f;
}

// @ 0x00ac1dc0   0 if direction b lies in the same cell as packed cell word a, else 1
float __cdecl FUN_00ac1dc0(uint32_t cell, const float* b) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  uint32_t* cells = pm->mpCubeCells;
  uint32_t ca = cells[(((cell >> 8 & 0xff) + (cell >> 17) * 0x80) * 0x80) + (cell & 0xff)];
  int u, v;
  int face = CubeCell<64>(b, &u, &v);
  uint32_t cb = cells[((face * 0x80 + v) * 0x80) + u];
  if (((cb ^ ca) & 0x3ff0000) == 0) return 0.0f;
  return 1.0f;
}

// @ 0x00ac1fc0
struct Msg {
  uint32_t pad[2];
  int type;      // +8
  uint32_t pad2;
  struct MsgSrc* src;  // +0x10
};
struct MsgSrc {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void* GetType();  // vtable +0x20
};
extern char g_TypeTag_018c43e8[];
bool __stdcall FUN_00ac1fc0(int unused, Msg* m) {
  int t = m->type;
  MsgSrc* src = m->src;
  if (t == 3 || t == 4) {
    if (src->GetType() == (void*)g_TypeTag_018c43e8) g_flag_1565b14 = 1;
  }
  return false;
}

// @ 0x00ac1ff0   0x3c-byte record (a point/plane record: mostly floats)
struct Vec3f { float x, y, z; };
struct Rec3C {
  float f0, f1, f2, f3;
  int i4;
  float f5, f6, f7, f8, f9, f10, f11, f12, f13;
  uint8_t b;
  Rec3C(const Rec3C& o);   // 0x00ac1ff0
  Rec3C(const Vec3f& v);   // 0x00ac21d0
};
Rec3C::Rec3C(const Rec3C& o) {
  f0 = o.f0;
  f1 = o.f1;
  f2 = o.f2;
  f3 = o.f3;
  i4 = o.i4;
  f5 = o.f5;
  f6 = o.f6;
  f7 = o.f7;
  f8 = o.f8;
  f9 = o.f9;
  f10 = o.f10;
  f11 = o.f11;
  f12 = o.f12;
  f13 = o.f13;
  b = o.b;
}

// @ 0x00ac2060   heap sift-down on 8-byte {key, value} entries, then push-heap
struct HeapEnt { uint32_t key, val; };
extern void __cdecl PushHeap(HeapEnt* first, int top, int hole, uint32_t a, uint32_t b, uint32_t c);  // 0x6e6d40
void __cdecl FUN_00ac2060(HeapEnt* first, int top, int len, int hole, uint32_t a, uint32_t b, uint32_t c) {
  int secondChild = 2 * hole + 2;
  while (secondChild < len) {
    if (first[secondChild].key > first[secondChild - 1].key) --secondChild;
    first[hole] = first[secondChild];
    hole = secondChild;
    secondChild = 2 * (secondChild + 1);
  }
  if (secondChild == len) {
    first[hole] = first[secondChild - 1];
    hole = secondChild - 1;
  }
  PushHeap(first, top, hole, a, b, c);
}

// @ 0x00ac2130   uninitialized_copy of 0x3c-byte records
Rec3C* __cdecl FUN_00ac2130(Rec3C* first, Rec3C* last, Rec3C* dest) {
  for (; first != last; ++first, ++dest) {
    if (dest) {
      dest->f0 = first->f0;
      dest->f1 = first->f1;
      dest->f2 = first->f2;
      dest->f3 = first->f3;
      dest->i4 = first->i4;
      dest->f5 = first->f5;
      dest->f6 = first->f6;
      dest->f7 = first->f7;
      dest->f8 = first->f8;
      dest->f9 = first->f9;
      dest->f10 = first->f10;
      dest->f11 = first->f11;
      dest->f12 = first->f12;
      dest->f13 = first->f13;
      dest->b = first->b;
    }
  }
  return dest;
}

// @ 0x00ac21d0
Rec3C::Rec3C(const Vec3f& v) {
  f0 = v.x;
  f1 = v.y;
  f2 = v.z;
  f3 = 1.0f;
  i4 = 0;
  b = 0;
}

// @ 0x00ac2200   penalty for a direction being outside [lo, hi] of the distance to a cell center
float __cdecl FUN_00ac2200(uint32_t cell, const float* v, float lo, float hi) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  SphereInfo* si = pm->mpISphere->GetInfo();
  float c[3];
  FUN_00ac1510(cell >> 17, cell & 0xff, (cell >> 8) & 0xff, c);
  Vec3f w;
  w.x = v[0];
  w.y = v[1];
  w.z = v[2];
  float inv = 1.0f / (float)sqrt((double)((w.x * w.x + w.y * w.y) + w.z * w.z));
  float dz = w.z * inv - c[2];
  float dy = w.y * inv - c[1];
  float dx = w.x * inv - c[0];
  float d = (si->outerRadius - si->innerRadius) * (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
  if (d < lo) {
    float t = lo - d;
    return t + t;
  }
  if (hi < d) {
    float t = d - hi;
    return t + t;
  }
  return 0.0f;
}
