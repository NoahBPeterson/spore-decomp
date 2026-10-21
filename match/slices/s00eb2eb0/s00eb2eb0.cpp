// Slice s00eb2eb0 (gold4 #84).
// Terrain-camera spring / interpolation helpers: three small "spring" value classes
// (3-float and 4-float lerp groups) plus the property-driven initialiser.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned char u8;
typedef unsigned int  u32;

struct Vec3u { u32 a, b, c; };
struct Vec4u { u32 a, b, c, d; };

// ---------------------------------------------------------------------------
// external constants / globals (address in the comment)
extern const float g_one;      // 0x1485720 = 1.0f
extern const float g_zero;     // 0x1485378 = 0.0f  (used as the zero multiplier)
extern const float g_q;        // 0x148862c = 0.25f
extern const float g_three_q;  // 0x1488630 = 0.75f
extern const float g_4over3;   // 0x1454fd8 = 1.3333334f
extern const float g_8over3;   // 0x1488698 = 2.6666667f
extern const float g_5over6;   // 0x1488694 = 0.8333333f
extern const float g_1over6;   // 0x1440f84 = 0.16666667f
extern const float g_point1;   // 0x1488628 = 0.1f
extern const float g_eps;      // 0x1488690 = 1.5258789e-05f
extern const float g_pi;       // 0x15a9408 = 3.1415927f
extern const float g_deg2rad;  // 0x1488678 = 0.017453292f
extern const float g_ms;       // 0x13ec5b4 = 1000.0f
extern const u32   g_vec3[3];   // 0x16c7284, 0x16c7288, 0x16c728c
extern char g_defProp[];       // 0x15d1168 default property placeholder

// ---------------------------------------------------------------------------
// helpers / callees
extern "C" float* RotateTowards(float* out, float* a, float* b, float t);  // 0xb0fd00
extern "C" void   Vector3_Normalize(float* out, float* v);                 // 0x436ce0
extern "C" char*  PlanetModel();                                          // 0xb3d350
struct cTerrainMapSet {
  char pad[0x34];
  float m34, m38, m3c;                    // +0x34..+0x3c
  float GetHeightAt(float* v);            // 0xf927c0 (thiscall, ret 4)
};
struct IPlanetWorld {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual cTerrainMapSet* GetTerrainMapSet();   // slot 3 (+0xc)
};

// property container reached through the +0x10 pointer
struct IPropHolder {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6();
  virtual bool HasProperty(int id);                    // slot 7  (+0x1c)
  virtual void v8();
  virtual bool GetProperty(int id, void** out);        // slot 9  (+0x24)
  virtual void* GetProperty2(int id);                  // slot 10 (+0x28)
};
struct Property {
  char pad[0x10];
  u8   mFlags;            // +0x10
  char pad11;
  unsigned short mType;   // +0x12
  float* GetFloat();      // 0x41ea70 (thiscall)
};

// ---------------------------------------------------------------------------
// A: 3-vector spring used by the point/terrain placement code
namespace SP {
struct Spring3 {
  float m00, m04, m08;    // +0x00 out
  float m0c, m10, m14;    // +0x0c start
  float m18, m1c, m20;    // +0x18 target
  u8    b24;              // +0x24
  char  pad25[3];
  float m28;              // +0x28 t
  float m2c, m30, m34;    // +0x2c
  void Init();                                   // 0x00eb2eb0
  void Set(int unused, float t, bool smooth);    // 0x00eb3490
};
}
using SP::Spring3;

// ---------------------------------------------------------------------------
// H: 3-float lerp group (from, out, to, t)
struct Lerp3 {
  float m00, m04, m08, mt;   // +0x00,+0x04,+0x08,+0x0c
  void Set(int unused, float t, bool smooth);      // 0x00eb3250
  void SetWrap(int unused, float t, bool smooth);  // 0x00eb3340
};

// ---------------------------------------------------------------------------
// B: the terrain-camera "scratch" object
struct CTerrainCam {
  float m00, m04, m08;      // +0x00
  float m0c;                // +0x0c
  IPropHolder* mProps;      // +0x10
  float m14;                // +0x14
  float m18, m1c, m20;      // +0x18 target
  u8    b24;                // +0x24
  char  pad25[3];
  float m28;                // +0x28
  float m2c, m30, m34;      // +0x2c
  char  pad38[0x40 - 0x38];
  float m40, m44, m48;      // +0x40
  char  pad4c[0x54 - 0x4c];
  u32   m54, m58, m5c;      // +0x54 (dword-copied)
  u32   m60, m64, m68;      // +0x60
  u32   m6c, m70, m74;      // +0x6c
  u8    b78;                // +0x78
  char  pad79[0x8c - 0x79];
  u32   m8c, m90, m94;      // +0x8c
  u32   m98, m9c, ma0;      // +0x98
  u32   ma4, ma8, mac;      // +0xa4
  char  padb0[0xc4 - 0xb0];
  float mc4, mc8, mcc;      // +0xc4
  char  padd0[0xd8 - 0xd0];
  float md8, mdc, me0;      // +0xd8
  char  pade4[0xec - 0xe4];
  float mec, mf0, mf4;      // +0xec
  char  padf8[0x100 - 0xf8];
  float m100, m104;         // +0x100
  char  pad108[0x10a - 0x108];
  u8    b10a, b10b;         // +0x10a,+0x10b
  char  pad10c[0x110 - 0x10c];
  int   i110;               // +0x110
  int   m114;               // +0x114
  char  pad118[0x124 - 0x118];
  u32   m124, m128, m12c;   // +0x124
  u32   m130, m134, m138, m13c;   // +0x130
  u32   m140, m144, m148, m14c;   // +0x140
  u32   m150, m154, m158, m15c;   // +0x150

  void Sync();                                        // 0x00eb2f50
  void SetZ(float v);                                 // 0x00eb30a0
  void SetQuad(u32 a, u32 b, u32 c, u32 d);           // 0x00eb30d0
  void SetTri(u32 a, u32 b, u32 c);                   // 0x00eb3160
  void ZeroVectors();                                 // 0x00eb3190
  void SetTime(float v);                              // 0x00eb31d0
  void InitProps();                                   // 0x00eb39f0
};

// ---------------------------------------------------------------------------
// @ 0x00eb2eb0
void Spring3::Init()
{
  u32* d = (u32*)this;
  d[0] = g_vec3[0];
  d[1] = g_vec3[1];
  d[2] = g_vec3[2];
  d[3] = g_vec3[0];
  d[4] = g_vec3[1];
  d[6] = d[0];
  d[5] = g_vec3[2];
  d[7] = d[1];
  d[8] = d[2];
  *(float*)(d + 10) = 0.0f;
  d[0xb] = g_vec3[0];
  d[0xc] = g_vec3[1];
  d[0xd] = g_vec3[2];
  *(u8*)(d + 9) = 0;
}

// @ 0x00eb2f50
void CTerrainCam::Sync()
{
  *(Vec3u*)&m60 = *(Vec3u*)&m54;
  *(Vec3u*)&m6c = *(Vec3u*)&m54;

  *(Vec3u*)&m98 = *(Vec3u*)&m8c;
  *(Vec3u*)&ma4 = *(Vec3u*)&m8c;

  *(Vec4u*)&m150 = *(Vec4u*)&m140;
  m130 = m140; m134 = m144; m138 = m148; m13c = m14c;

  m18 = m20 = m1c;
  m2c = m34 = m30;
  m40 = m48 = m44;

  md8 = me0 = mdc;
  mc4 = mcc = mc8;
  mec = mf4 = mf0;
}

// @ 0x00eb30a0
void CTerrainCam::SetZ(float v)
{
  if (b10a)
    mf0 = v;
  mf4 = v;
  mec = mf0;
}

// @ 0x00eb30d0
void CTerrainCam::SetQuad(u32 a, u32 b, u32 c, u32 d)
{
  if (b10a) {
    m140 = a; m144 = b; m148 = c; m14c = d;
  }
  m150 = a; m154 = b; m158 = c; m15c = d;
  if (b10b || b10a) {
    *(Vec4u*)&m130 = *(Vec4u*)&m140;
  }
}

// @ 0x00eb3160
void CTerrainCam::SetTri(u32 a, u32 b, u32 c)
{
  m124 = a;
  m128 = b;
  m12c = c;
}

// @ 0x00eb3190
void CTerrainCam::ZeroVectors()
{
  m30 = 0; m34 = 0; m2c = 0;
  m1c = 0; m20 = 0; m18 = 0;
  m44 = 0; m48 = 0; m40 = 0;
}

// @ 0x00eb31d0
void CTerrainCam::SetTime(float v)
{
  v = v * g_ms;
  m114 = 0;
  i110 = _mm_cvtss_si32(_mm_set_ss(v));
}

struct Vec3f { float x, y, z; };

// @ 0x00eb3220
float __stdcall DistSq(Vec3f a, Vec3f b)
{
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  float dz = a.z - b.z;
  return dx * dx + dy * dy + dz * dz;
}

// @ 0x00eb3250
void Lerp3::Set(int, float t, bool smooth)
{
  float ab[2];
  if (t < g_one) { ab[0] = t; ab[1] = g_one; } else { ab[0] = g_one; ab[1] = t; }
  float v = g_zero > ab[0] ? g_zero : ab[0];
  v = ab[1] < v ? ab[1] : v;
  mt = v;
  if (smooth) {
    if (g_q <= mt) {
      if (g_three_q <= mt)
        mt = (g_4over3 - (mt - g_three_q) * g_8over3) * (mt - g_three_q) + g_5over6;
      else
        mt = (mt - g_q) * g_4over3 + g_1over6;
    } else {
      mt = (mt * mt) * g_8over3;
    }
  }
  m04 = (m08 - m00) * mt + m00;
}

// @ 0x00eb3340
void Lerp3::SetWrap(int, float t, bool smooth)
{
  float a, b;
  if (t < g_one) { a = t; b = g_one; } else { a = g_one; b = t; }
  float v = g_zero;
  if (v < a) v = a;
  if (v > b) v = b;
  mt = v;
  if (smooth) {
    if (g_q <= mt) {
      if (g_three_q <= mt)
        mt = (g_4over3 - (mt - g_three_q) * g_8over3) * (mt - g_three_q) + g_5over6;
      else
        mt = (mt - g_q) * g_4over3 + g_1over6;
    } else {
      mt = (mt * mt) * g_8over3;
    }
  }
  float negPi = -g_pi;
  float twoPi = g_pi - negPi;
  float d = m08 - m00;
  if (d < negPi) {
    do { d = twoPi + d; } while (d < negPi);
  } else if (d >= g_pi) {
    do { d = d - twoPi; } while (d >= g_pi);
  }
  m04 = mt * d + m00;
}

// @ 0x00eb3490
void Spring3::Set(int, float t, bool smooth)
{
  float ab[2];
  if (t < g_one) { ab[0] = t; ab[1] = g_one; } else { ab[0] = g_one; ab[1] = t; }
  float v = g_zero > ab[0] ? g_zero : ab[0];
  v = ab[1] < v ? ab[1] : v;
  m28 = v;
  if (smooth) {
    if (g_q <= m28) {
      if (g_three_q <= m28)
        m28 = (g_4over3 - (m28 - g_three_q) * g_8over3) * (m28 - g_three_q) + g_5over6;
      else
        m28 = (m28 - g_q) * g_4over3 + g_1over6;
    } else {
      m28 = (m28 * m28) * g_8over3;
    }
  }

  if (!b24) {
    float k = m28;
    m00 = (m0c - m18) * k + m18;
    m04 = (m10 - m1c) * k + m1c;
    m08 = (m14 - m20) * k + m20;
    return;
  }

  float dOut = m00 * m00 + m04 * m04 + m08 * m08;
  float dSrt = m0c * m0c + m10 * m10 + m14 * m14;
  if (dOut <= g_eps || dSrt <= g_eps) {
    m00 = m0c; m04 = m10; m08 = m14;
    return;
  }

  float nT0 = m18, nT1 = m1c, nT2 = m20;
  float invT = (float)(1.0 / sqrt((double)(nT2 * nT2 + (nT1 * nT1 + nT0 * nT0))));
  nT0 = invT * nT0;
  float nS0 = m0c, nS1 = m10, nS2 = m14;
  nT2 = invT * nT2;
  nT1 = invT * nT1;
  float invS = (float)(1.0 / sqrt((double)(nS2 * nS2 + (nS1 * nS1 + nS0 * nS0))));
  nS0 = invS * nS0;
  nS2 = invS * nS2;
  nS1 = invS * nS1;

  float near = 1;
  float dx = m18 - m0c; if (dx < 0.0f) dx = -dx;
  if (dx <= g_eps) {
    float dy = m1c - m10; if (dy < 0.0f) dy = -dy;
    if (dy <= g_eps) {
      float dz = m20 - m14; if (dz < 0.0f) dz = -dz;
      if (dz <= g_eps)
        near = 0;
    }
  }

  if (near) {
    float p[3], q[3], dst[3];
    p[0] = nS0; p[1] = nS1; p[2] = nS2;
    q[0] = nT0; q[1] = nT1; q[2] = nT2;
    float* r = RotateTowards(dst, q, p, m28);
    nT0 = r[0]; nT1 = r[1]; nT2 = r[2];
    float lo = (float)sqrt((double)(m0c * m0c + m10 * m10 + m14 * m14));
    float hi = (float)sqrt((double)(m18 * m18 + m1c * m1c + m20 * m20));
    float len = (hi - lo) * m28 + lo;
    nS0 = nT0 * len; nS1 = nT1 * len; nS2 = nT2 * len;
    m00 = nS0; m04 = nS1; m08 = nS2;
    Vector3_Normalize(&nS0, &m00);
    return;
  }

  // Straight-line case: normalise the (start-to-target) direction and re-derive.
  m00 = m0c; m04 = m10; m08 = m14;
  Vector3_Normalize(&nS0, &m00);
  IPlanetWorld* pw = *(IPlanetWorld**)(PlanetModel() + 0x24);
  cTerrainMapSet* tms = pw->GetTerrainMapSet();
  float h = tms->GetHeightAt(&m00);
  float water = tms->m3c * tms->m38 + tms->m34;
  float* pick = (h <= water) ? &water : &h;
  float lim = *pick + g_point1;
  if ((float)sqrt((double)(m00 * m00 + m04 * m04 + m08 * m08)) < lim) {
    m00 = nS0 * lim;
    m04 = nS1 * lim;
    m08 = nS2 * lim;
  }
  m0c = m00; m10 = m04; m14 = m08;
}

// ---------------------------------------------------------------------------
static float* PropFloatPtr(void* p)
{
  unsigned short type = *(unsigned short*)((char*)p + 0x12);
  if (type == 13 || type == 16) {
    if ((*(u8*)((char*)p + 0x10) & 0x30) == 0)
      return (float*)(type != 0 ? p : 0);
    return *(float**)p;
  }
  return (float*)g_defProp;
}

// @ 0x00eb39f0
void CTerrainCam::InitProps()
{
  if (mProps->HasProperty((int)0x00c7c4fb)) {
    float v = *PropFloatPtr(mProps->GetProperty2((int)0x00c7c4fb));
    mf0 = v;
    mec = mf0;
    mf4 = v;
  }
  if (mProps->HasProperty((int)0x00c7c4fc)) {
    float v = *PropFloatPtr(mProps->GetProperty2((int)0x00c7c4fc)) * g_deg2rad;
    m30 = v;
    m2c = m30;
    m34 = v;
  }
  if (mProps->HasProperty((int)0x00c7c4fd)) {
    float v = *PropFloatPtr(mProps->GetProperty2((int)0x00c7c4fd)) * g_deg2rad;
    m1c = v;
    m18 = m1c;
    m20 = v;
  }
  if (mProps->HasProperty((int)0x044c6220)) {
    float v = *PropFloatPtr(mProps->GetProperty2((int)0x044c6220));
    mdc = v;
    md8 = mdc;
    me0 = v;
  }
  {
    void* p = 0;
    if (mProps && mProps->GetProperty((int)0x01102b20, &p) &&
        *(unsigned short*)((char*)p + 0x12) == 13) {
      m100 = *((Property*)p)->GetFloat();
    }
  }
  {
    void* p = 0;
    if (mProps && mProps->GetProperty((int)0x01102b2f, &p) &&
        *(unsigned short*)((char*)p + 0x12) == 13) {
      m104 = *((Property*)p)->GetFloat();
    }
  }

  m54 = g_vec3[0]; m58 = g_vec3[1]; m5c = g_vec3[2];
  m60 = g_vec3[0]; m64 = g_vec3[1]; m68 = g_vec3[2];
  m6c = m54; m70 = m58; m74 = m5c;
  b78 = 0;
  m48 = 0.0f;
  m44 = 0.0f;
  m40 = 0.0f;
}
