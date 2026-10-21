// slice s00a7c630 -- EA::Swarm particle/effect geometry helpers.
//
//   00a7c630  EA::Swarm::SquareToCircle        map a square sample (a,b) onto the unit disk
//   00a7c7c0  OctantClassify                   classify a 3-vector into one of six face regions
//   00a7c860  SquareToSphere                   map a cube sample (a,b,c) onto the unit sphere
//   00a7ca40  ZeroStub                          __stdcall 3-float stub returning 0.0
//   00a7ca50  Xform::InverseRotate             rotate a vector by the transpose of the matrix
//   00a7cb00  SubtractEdges                    per-face edge subtraction / mask select
//   00a7cb80  ClipSegmentToQuad                ray/segment vs quad test with refracted exit point
//   00a7cf50  DistanceFromPlaneSurface         distance from a point to the surface in front
//   00a7cfb0  ClampToShell                      push a point onto a spherical shell
//   00a7d1a0  RandomSpawnSeed                   seed a random colour sample
//   00a7d210  BuildOrthonormalFrame             build an orthonormal frame from a normal
//   00a7d280  EA::Swarm::ParseSurfaceOptions    parse surface emitter options from ArgScript
//   00a7d540  SurfaceSpec::Assign                copy-assign a surface spec
//   00a7d580  SurfaceSpec::Swap                  ref-swap assign a surface spec
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char uint8;
typedef unsigned int  uint32;

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};


// PDB cSPTransform: flags(+0), modification count(+2), translation(+4), scale(+0x10),
// rotation 3x3(+0x14) -- size 0x38.
struct Matrix3 { Vector3 row[3]; };
struct cSPTransform {
  uint16_t mFlags;
  uint16_t mModificationCount;
  Vector3 mTranslation;
  float mScale;
  Matrix3 mRotation;

  void InverseRotate(Vector3& v);                 // 0x00a7ca50
};

// ------------------------------------------------------------ runtime constants
// The square/sphere maps read a runtime-filled 16-entry table of (sin, cos) pairs and
// several write-once scalars; modelled here as the constants the retail loader installs.
static const float kCenterX   = 1.0f;    // 0x01677520
static const float kCenterY   = 1.0f;    // 0x01677524
static const float kCenterZ   = 1.0f;    // 0x016774f0 / f4 / f8 (one per axis)
extern const float kZero;                // 0x01485378
extern const float kOne;                 // 0x01485720
extern const float kNegEps5;             // 0x01457c8c  (-1e-5f)
extern const float kEps6;                // 0x013f11c8  (1e-6f)
extern const float kPoint8;              // 0x01486374  (0.8f)
extern const float kNegPoint8;           // 0x01457c90  (-0.8f)
extern const float kPiQuarter;           // 0x01564c44  (pi/4)
extern const float kPi;                  // 0x01564c4c  (pi)

struct SinCos { float sinv, cosv; };
extern const SinCos kSinCosTable[16];    // 0x01677840

extern char sRandom[];                                             // 0x016778dc

// Out-of-slice ArgScript/random helpers.  These are __thiscall in the original; each is
// invoked here through a __fastcall function pointer (this = first arg, unused edx arg).
static uint32 RandomUint32Uniform(void* self, uint32 n)
{ return ((uint32 (__fastcall*)(void*, int, uint32))0x00a68fb0)(self, 0, n); }

static bool HasFlag(void* args, const char* name)
{ return ((bool (__fastcall*)(void*, int, const char*))0x008380b0)(args, 0, name); }

static const char** OptionArguments(void* args, const char* name, int n)
{ return ((const char** (__fastcall*)(void*, int, const char*, int))0x00838330)(args, 0, name, n); }

static const char** OptionArguments2(void* args, const char* name, void* out, int a, int b)
{ return ((const char** (__fastcall*)(void*, int, const char*, void*, int, int))0x00838130)
             (args, 0, name, out, a, b); }

static uintptr_t MapFindA(void* self, const char* name)
{ return ((uintptr_t (__fastcall*)(void*, int, const char*))0x00a6eaf0)(self, 0, name); }

static void MarkAllProcessed(void* args)
{ ((void (__fastcall*)(void*, int))0x00837f60)(args, 0); }

// @ 0x00a7c630
// EA::Swarm::SquareToCircle: warp a square sample (param_2,param_3) onto the unit disk.
void __cdecl SquareToCircle(float* out, float a, float b)
{
  float x = b * 2.0f - kCenterY;          // -1..1
  float y = a * 2.0f - kCenterX;
  float ax = -x;                          // xmm2 = -x

  float t, r;
  if (y <= ax) {
    // left half
    if (y < x) {
      r = x;
      t = (x / y + 4.0f) * (3.14159274f * 0.25f);
      ax = -y;
    } else {
      r = x;
      t = 0.0f;
      if (x != 0.0f)
        t = (6.0f - y / x) * (3.14159274f * 0.25f);
    }
  } else if (x < y) {
    r = y;
    t = (x / y) * (3.14159274f * 0.25f);
  } else {
    r = y;
    t = (2.0f - y / x) * (3.14159274f * 0.25f);
  }

  float s = 2.54647899f * t + 12582912.0f;        // bias to integer range
  unsigned e = (unsigned&)s & 0xf;
  float cs = kSinCosTable[e].sinv;
  float sn = kSinCosTable[e].cosv;
  float q  = t - (float)((int)s + (int)0xb4c00000) * 0.392699093f;

  out[0] = (sn - ((sn * q) * 0.5f + cs) * q) * r;
  out[1] = ((sn - (cs * q) * 0.5f) * q + cs) * r;
}

// @ 0x00a7c7c0
// Classify |a|,|b|,|c| into one of six cube-face regions (0..5).
int __cdecl OctantClassify(float a, float b, float c)
{
  float aa = fabsf(a);
  float ab = fabsf(b);
  float ac = fabsf(c);
  if (aa <= ab) {
    if (ac < ab) {
      if (b > kZero)
        return 1;
      return 4;
    }
  } else if (ac < aa) {
    if (a > kZero)
      return 0;
    return 3;
  }
  if (c > kZero)
    return 2;
  return 5;
}

// @ 0x00a7c860
// EA::Swarm::SquareToSphere: map a cube sample (a,b,c) onto the unit sphere.
void __cdecl SquareToSphere(float* out, float a, float b, float c)
{
  float x = a * 2.0f - kCenterZ;
  float y = b * 2.0f - kCenterZ;
  float z = c * 2.0f - kCenterZ;

  switch (OctantClassify(x, y, z)) {
  case 0:
  case 3: {
    float r = x;
    float sy = sinf(y * (0.785398185f / r));
    float sz = sinf(z * (0.785398185f / r));
    out[0] = sqrtf((1.0f - sy * sy) - sz * sz) * r;
    out[1] = r * sy;
    out[2] = r * sz;
    return;
  }
  case 1:
  case 4: {
    float r = y;
    float sx = sinf(x * (0.785398185f / r));
    float sz = sinf(z * (0.785398185f / r));
    out[0] = r * sx;
    out[1] = sqrtf((1.0f - sx * sx) - sz * sz) * r;
    out[2] = r * sz;
    return;
  }
  case 2:
  case 5: {
    float r = z;
    float sx = sinf(x * (0.785398185f / r));
    float sy = sinf(y * (0.785398185f / r));
    out[0] = r * sx;
    out[1] = sy * r;
    out[2] = r * sqrtf((1.0f - sx * sx) - sy * sy);
    return;
  }
  default:
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    return;
  }
}

// @ 0x00a7ca40
// __stdcall stub taking three floats and yielding 0.0 (used as a default sampler).
float __stdcall ZeroStub(float, float, float)
{
  return 0.0f;
}

// @ 0x00a7ca50
// Rotates v by the transpose of this transform's rotation matrix (inverse rotation).
void cSPTransform::InverseRotate(Vector3& v)
{
  if (!(mFlags & 2))
    return;
  float vy = v.y, vz = v.z, vx = v.x;
  v.x = (mRotation.row[0].x * vy + mRotation.row[1].x * vz) + mRotation.row[2].x * vx;
  v.y = (mRotation.row[0].y * vy + mRotation.row[1].y * vz) + mRotation.row[2].y * vx;
  v.z = (mRotation.row[0].z * vy + mRotation.row[1].z * vz) + vx * (mRotation.row[2].z);
}

// @ 0x00a7cb00
// For each of the eight quad corners subtract the reference point, selecting which edges
// are emitted according to the mask `face` (0/1/2).
void __cdecl SubtractEdges(int face, const float* verts, const float* ref, float* out)
{
  int i = 0;                          // edx
  float* dst = out;                   // edi
  const float* p = verts + 2;         // ecx, walks -8/-4/0 then +0xc
  do {
    int n = 0;                        // eax
    if (face != 0) {
      *dst = p[-2] - ref[0];
      n = 1;
    }
    if (face != 1) {
      out[i + n] = p[-1] - ref[1];
      n = n + 1;
    }
    if (face != 2) {
      out[n + i] = p[0] - ref[2];
    }
    i += 2;
    p += 3;
    dst += 2;
  } while (i < 8);
}

// @ 0x00a7cb80
// Tests the segment (ray origin param_2, point param_3) against the quad `param_5`, writing
// the exit point to param_4 and param_3. Returns true when the segment crosses the quad.
bool __cdecl ClipSegmentToQuad(float t, const float* src, float* hit, float* exitPt,
                               const float* quad)
{
  float qx = quad[0], qy = quad[1], qz = quad[2];
  float px = src[0], py = src[1], pz = src[2];
  float ex = src[4], ey = src[5], ez = src[6];

  float denom = qx * (hit[0] - px) + qz * (hit[2] - pz) + qy * (hit[1] - py);
  if (!(denom < kNegEps5))
    return false;

  float c = -(((quad[2] * pz + quad[1] * py) + quad[0] * px) + quad[3]);
  float invD = kOne / denom;
  float s = (c + t) * invD;
  if (s > kOne)
    return false;
  if (s < kZero && !(kZero <= invD * c))
    return false;

  float dx = (hit[0] - px) * s;
  float dy = (hit[1] - py) * s;
  float dz = (hit[2] - pz) * s;

  float local[3];
  local[0] = (px + dx) - qx * t;
  local[1] = (py + dy) - qy * t;
  local[2] = (pz + dz) - qz * t;

  float tbl[8];
  SubtractEdges((int)quad[0x1e], quad + 4, local, tbl);

  unsigned cnt = 0;
  // edge 0
  if (tbl[2] * tbl[5] < kZero) {
    if ((tbl[1] >= kZero && tbl[4] >= kZero) ||
        (fabsf(tbl[5] - tbl[2]) > kEps6 &&
         (tbl[1] - ((tbl[4] - tbl[1]) / (tbl[5] - tbl[2])) * tbl[2] >= kZero)))
      cnt = 1;
  }
  // edge 1
  if (tbl[6] * tbl[5] < kZero) {
    if (tbl[4] >= kZero || tbl[7] >= kZero) {
      if (fabsf(tbl[6] - tbl[5]) > kEps6 &&
          (tbl[4] - ((tbl[7] - tbl[4]) / (tbl[6] - tbl[5])) * tbl[5] >= kZero))
        cnt ^= 1;
    } else {
      cnt++;
    }
  }
  // edge 2
  if (tbl[0] * tbl[6] < kZero) {
    if (tbl[7] >= kZero || tbl[3] >= kZero) {
      if (fabsf(tbl[0] - tbl[6]) > kEps6 &&
          (tbl[7] - ((tbl[3] - tbl[7]) / (tbl[0] - tbl[6])) * tbl[6] >= kZero))
        cnt ^= 1;
    } else {
      cnt++;
    }
  }
  // edge 3
  if (tbl[0] * tbl[2] < kZero) {
    if (tbl[3] >= kZero || tbl[1] >= kZero) {
      if (fabsf(tbl[2] - tbl[0]) > kEps6 &&
          (tbl[3] - ((tbl[1] - tbl[3]) / (tbl[2] - tbl[0])) * tbl[0] >= kZero))
        cnt ^= 1;
    } else {
      cnt++;
    }
  }

  if (cnt & 1) {
    exitPt[0] = quad[0];
    exitPt[1] = quad[1];
    exitPt[2] = quad[2];
    float fy = dy + src[1];
    float fz = src[2];
    hit[0] = src[0] + dx;
    hit[1] = fy;
    hit[2] = fz + dz;
    return true;
  }
  return false;
}

// @ 0x00a7cf50
// Distance from a point to the surface meshed ahead of it (0 when the test fails).
float __stdcall DistanceFromPlaneSurface(void* self, float* p)
{
  float tmp[3];
  typedef char (__thiscall *TestFn)(void*, float*);
  if (!((TestFn)(*(void***)self)[0x10 / 4])(self, p))
    return 0.0f;
  float dx = p[0] - tmp[0];
  float dy = p[1] - tmp[1];
  float dz = p[2] - tmp[2];
  return sqrtf(dz * dz + (dy * dy + dx * dx));
}

// @ 0x00a7cfb0
// Push a point onto a spherical shell of radius param_3 around the origin, writing the
// outward direction into param_4; returns true when the point was moved.
bool __cdecl ClampToShell(float* p, float* dir, float radius, void* unused)
{
  float x = p[0] - kNegPoint8;
  float y = p[1];
  float z = p[2] + kEps6;
  float r = sqrtf(z * z + y * y + x * x);
  float rr = radius + kOne;
  bool moved = false;
  if (r < rr) {
    float inv = kOne / r;
    dir[0] = inv * x;
    dir[1] = y * inv;
    dir[2] = z * inv;
    p[0] = dir[0] * rr - kPoint8;
    p[1] = dir[1] * rr;
    p[2] = dir[2] * rr;
    moved = true;
  }

  x = p[0] - kPoint8;
  y = p[1];
  z = p[2] + kEps6;
  r = sqrtf(z * z + y * y + x * x);
  if (r < rr) {
    float inv = kOne / r;
    dir[0] = inv * x;
    dir[1] = y * inv;
    dir[2] = z * inv;
    p[0] = dir[0] * rr + kPoint8;
    p[1] = dir[1] * rr;
    p[2] = dir[2] * rr;
    return true;
  }
  return moved;
}

// @ 0x00a7d1a0
// Draws a random colour sample: a random uniform value, a random 0/1 pair and a fixed 1.0.
unsigned __stdcall RandomSpawnSeed(void* arg, float* outv, void* target)
{
  uint32 r = RandomUint32Uniform(&sRandom, 4);
  outv[0] = (float)(int)r;
  float local[3];
  local[0] = (float)(r & 1);
  local[1] = (float)((int)r >> 1);
  local[2] = 1.0f;
  if (target != 0)
    ((void (__thiscall*)(void*, int, float*, int))(*(void***)target)[0x44 / 4])(target, 5, local, 3);
  return 0;
}

// @ 0x00a7d210
// Builds an orthonormal frame: copies param_1's x/y and param_3's z into param_2, and
// writes a zero/zero/one basis into param_4. Returns false when param_3 is null.
bool __stdcall BuildOrthonormalFrame(const Vector3* n, Vector3* out, Vector3* basis,
                                     float, float, const float* z)
{
  if (z == 0)
    return false;
  float zz = *z;
  out->x = n->x;
  out->y = n->y;
  out->z = zz;
  if (basis != 0) {
    basis->x = 0.0f;
    basis->y = 0.0f;
    basis->z = 1.0f;
  }
  return true;
}

// @ 0x00a7d280
// EA::Swarm::ParseSurfaceOptions: reads surface-emitter options out of an ArgScript
// argument block into the option bitmask + float vector at param_3.
void __cdecl ParseSurfaceOptions(void* a, void* b, uint32* opts, int* owner)
{
  int* xf = (int*)owner[5];
  void* args = 0;
  bool ok = ((bool (__thiscall*)(void*, void*, void**))
             (*(void***)owner[0x23])[0x18 / 4])((void*)owner[0x23], a, &args);
  if (!ok) {
    if (((bool (__thiscall*)(void*, int))(*(void***)owner)[0x14 / 4])(owner, 2))
      return;
    opts[2] = 0xffffffffu;
    opts[3] = 0xffffffffu;
  }

#define HASFLAG(s) HasFlag(args, s)
#define OPT1(s)    OptionArguments(args, s, 1)
  if (HASFLAG("pin")) {
    *opts |= 2;
  } else if (HASFLAG("pinMove")) {
    *opts |= 4;
  } else if (HASFLAG("pinEmit")) {
    *opts |= 8;
    const char** o = (const char**)OPT1("surfaceOffset");
    if (o) {
      float v = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
      *(float*)&opts[8] = v;
    }
  } else {
    const char** o = (const char**)OptionArguments(args, "repel", 2);
    if (o) {
      *(float*)&opts[9]  = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, o[0]);
      *(float*)&opts[10] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, o[1]);
      const char** s;
      if ((s = (const char**)OPT1("scout")))
        *(float*)&opts[11] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *s);
      if ((s = (const char**)OPT1("vertical")))
        *(float*)&opts[12] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *s);
      if ((s = (const char**)OPT1("killHeight")))
        *(float*)&opts[13] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *s);
    } else if (HASFLAG("align")) {
      *opts |= 0x20;
    } else {
      const char** o2 = (const char**)OptionArguments2(args, "bounce", &a, 1, 2);
      if (o2) {
        *(float*)&opts[4] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o2);
        *opts |= 1;
        if ((o = (const char**)OPT1("slide")))
          *(float*)&opts[5] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
        if ((o = (const char**)OPT1("radius")))
          *(float*)&opts[6] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
        if ((o = (const char**)OPT1("death")))
          *(float*)&opts[7] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
        if ((o = (const char**)OPT1("collideEffect")))
          (uintptr_t&)opts[0xe] = MapFindA((void*)(uintptr_t)owner[5], *o);
        if ((o = (const char**)OPT1("deathEffect")))
          (uintptr_t&)opts[0xf] = MapFindA((void*)(uintptr_t)owner[5], *o);
      }
    }
  }

  if (HASFLAG("sourceSpace"))
    *opts |= 0x40;
  if (HASFLAG("worldSpace"))
    *opts |= 0x80;

  if (b != 0)
    ((void (__cdecl*)(void*, void*, uint32*))b)(xf, args, opts);
  MarkAllProcessed(args);
#undef HASFLAG
#undef OPT1
}

// @ 0x00a7d540
// SurfaceSpec::Assign: ref-count the incoming handle at +0 then copy the remaining fields.
struct SurfaceSpec {
  void*  mpRef;      // +0x00
  uint32 f04;        // +0x04
  uint32 f08;        // +0x08
  uint32 f0c;        // +0x0c
  uint32 f10;        // +0x10
  uint32 f14;        // +0x14

  SurfaceSpec* Assign(const SurfaceSpec& o);
  SurfaceSpec* SwapAssign(const SurfaceSpec& o);
};

SurfaceSpec* SurfaceSpec::Assign(const SurfaceSpec& o)
{
  mpRef = o.mpRef;
  if (mpRef != 0)
    ((void (__thiscall*)(void*))(*(void***)mpRef)[1])(mpRef);
  f04 = o.f04;
  f08 = o.f08;
  f0c = o.f0c;
  f10 = o.f10;
  f14 = o.f14;
  return this;
}

// @ 0x00a7d580
// SurfaceSpec::SwapAssign: release the old handle and adopt the incoming one.
SurfaceSpec* SurfaceSpec::SwapAssign(const SurfaceSpec& o)
{
  void* old = mpRef;
  void* src = o.mpRef;
  if (src != old) {
    if (src != 0)
      ((void (__thiscall*)(void*))(*(void***)src)[1])(src);
    mpRef = src;
    if (old != 0)
      ((void (__thiscall*)(void*))(*(void***)old)[0])(old);
  }
  f04 = o.f04;
  f08 = o.f08;
  f0c = o.f0c;
  f10 = o.f10;
  f14 = o.f14;
  return this;
}
