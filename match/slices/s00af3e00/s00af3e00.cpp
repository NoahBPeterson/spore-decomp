// Slice s00af3e00: terrain-sphere ray marching against the cube-map height field, plus one copy-assign.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

// Cube-map image holders: +8 = dimension (texels per face side), +0x10 = data.
struct HeightImg { char pad[0x10]; uint16_t* data; };               // +0x10
struct ColorImg { char pad[8]; int dim; char pad2[4]; uint32_t* data; };  // +8 dim, +0x10 data
// The map object returned by cITerrainSphere vtable slot 3 (+0xc).
struct TerrainMap {
    char pad0[8];
    HeightImg* height;   // +8
    ColorImg* color;     // +0xc
    char pad10[0x34 - 0x10];
    float radius;        // +0x34
    float heightScale;   // +0x38
    char pad3c[0x4c - 0x3c];
    float minAlpha;      // +0x4c
};
struct cITerrainSphere {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual TerrainMap* GetMap();  // +0xc
};
struct cPlanetModel {
    char pad[0x24];
    cITerrainSphere* mpISphere;  // +0x24
    char pad28[0xf0 - 0x28];
    bool mbF0;                   // +0xf0
    float __thiscall GetWaterHeight();                         // 0xb7e390
    float __thiscall GetRadiusAt(const Vec3* p);               // 0xb7ef70
    Vec3* __thiscall ToSurface(Vec3* out, const Vec3* in);     // 0xb81630
};
cPlanetModel* SP_PlanetModel();  // 0xb3d350

void __cdecl FUN_00af1610(void* a, cPlanetModel* pm, Vec3* p0, Vec3* p1, Vec3* p2, Vec3* p3, Vec3* p4, float f);
void __cdecl FUN_00af1570(void* a, cPlanetModel* pm, Vec3* p0, Vec3* p1, float f, int z0, int z1);

// Cube-map texel index of a direction: the dominant axis picks the face, the other two give (u,v).
static __forceinline int CubeIndex(float x, float y, float z, int dim, int dimSq, float half) {
  float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
  int u, v, face;
  if (!(az < ax) && !(az < ay)) {
    u = (int)((x / z + 1.0f) * half);
    v = (int)((y / az + 1.0f) * half);
    face = (z >= 0.0f) ? 0 : 1;
  } else if (!(ay < ax)) {
    u = (int)((z / y + 1.0f) * half);
    v = (int)((x / ay + 1.0f) * half);
    face = (y >= 0.0f) ? 4 : 5;
  } else {
    u = (int)((y / x + 1.0f) * half);
    v = (int)((z / ax + 1.0f) * half);
    face = (x >= 0.0f) ? 2 : 3;
  }
  if (u == dim) u--;
  if (v == dim) v--;
  return face * dimSq + u + v * dim;
}

// A base object (copied by FUN_00af1910) with a float and a Vec3 appended at +0xf0.
struct cRayQueryBase {
  char pad[0xf0];
  float mValue;  // +0xf0
  Vec3 mPoint;   // +0xf4
  void __thiscall AssignBase(const cRayQueryBase& src);  // 0xaf1910
  cRayQueryBase& __thiscall Assign(const cRayQueryBase& src);
};

// @ 0x00af3e00
cRayQueryBase& cRayQueryBase::Assign(const cRayQueryBase& src) {
  AssignBase(src);
  mValue = src.mValue;
  mPoint = src.mPoint;
  return *this;
}

struct ProbeRay {
  Vec3 dir;
  Vec3 start;
  float t;
};

// @ 0x00af3e50
// Marches a ray from origin along dir through the planet's cube-map terrain (heights plus a colour/normal map);
// on a hit refines with three probe rays and hands them to FUN_00af1610. Returns true when a hit was found.
bool FUN_00af3e50(const Vec3* origin, const Vec3* dir, float t0, float unused, float minHeight, float waterBias,
                  void* ctx, float* tMax, bool noWaterHit) {
  if (1.52587890625e-05f > *tMax) return false;
  bool found = false;
  cPlanetModel* pm = SP_PlanetModel();
  float water = pm->GetWaterHeight();
  TerrainMap* map = pm->mpISphere->GetMap();
  uint16_t* heights = map->height->data;
  int dim = map->color->dim;
  uint32_t* colors = map->color->data;
  int dimSq = dim * dim;
  float radius0 = map->radius;
  float hscale = map->heightScale;
  if (*tMax > radius0 * 2.0f) return false;
  float fdim = (float)dim;
  float cellLen = pm->GetRadiusAt(origin) * (1.0f / fdim);
  float waterTop = water + waterBias;
  float a = map->minAlpha > minHeight ? map->minAlpha : minHeight;
  float b = hscale > 1.0f ? hscale : 1.0f;
  float alphaThr = a / b;
  float t = cellLen + t0;
  if (!(*tMax > t)) return found;
  float half = fdim * 0.5f;
  for (;;) {
    Vec3 p;
    p.x = dir->x * t + origin->x;
    p.y = dir->y * t + origin->y;
    p.z = dir->z * t + origin->z;
    int idx = CubeIndex(p.x, p.y, p.z, dim, dimSq, half);
    float H = (float)((int)heights[idx] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
    float alpha = (float)(colors[idx] >> 24) * 0.003921568859368563f;
    bool hit;
    if (alpha > alphaThr && H > waterTop) {
      uint32_t c = colors[idx];
      float nx = (float)(c & 0xff) * 0.007843137718737125f - 1.0f;
      float ny = (float)((c >> 8) & 0xff) * 0.007843137718737125f - 1.0f;
      float nz = (float)((c >> 16) & 0xff) * 0.007843137718737125f - 1.0f;
      float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
      float ux = inv * p.x, uy = p.y * inv, uz = p.z * inv;
      // w = n x up, v = w x n
      float w0 = uz * ny - uy * nz;
      float w1 = nz * ux - uz * nx;
      float w2 = uy * nx - ny * ux;
      float v0 = w1 * nz - w2 * ny;
      float v1 = w2 * nx - w0 * nz;
      float v2 = w0 * ny - w1 * nx;
      hit = true;
      float vUp = v2 * uz + v1 * uy + v0 * ux;
      if (0.69f > vUp) {
        float vDir = v0 * dir->x + v2 * dir->z + v1 * dir->y;
        hit = vDir > 0.3f ? hit : false;
      }
    } else {
      hit = false;
    }
    bool refine;
    if (!pm->mbF0 && water >= H) {
      refine = !noWaterHit;
    } else {
      refine = hit;
    }
    if (refine) {
      found = true;
      float m = (t < 2.0f) ? t : 2.0f;
      Vec3 back;
      back.x = p.x - dir->x * m;
      back.y = p.y - dir->y * m;
      back.z = p.z - dir->z * m;
      Vec3 out;
      pm->ToSurface(&out, &back);
      float inv = 1.0f / sqrtf(p.x * p.x + p.z * p.z + p.y * p.y + 9.99999993922529e-09f);
      float ux = inv * p.x, uy = p.y * inv, uz = p.z * inv;
      float dx = dir->x, dy = dir->y, dz = dir->z;
      float q0 = dz * uy - dy * uz;
      float q1 = dx * uz - dz * ux;
      float q2 = dy * ux - dx * uy;
      ProbeRay probe[3];
      probe[0].dir.x = -q0; probe[0].dir.y = -q1; probe[0].dir.z = -q2;
      probe[1].dir.x = q0; probe[1].dir.y = q1; probe[1].dir.z = q2;
      probe[2].dir.x = dx; probe[2].dir.y = dy; probe[2].dir.z = dz;
      probe[0].t = cellLen;
      probe[1].t = cellLen;
      probe[2].t = cellLen;
      for (int i = 0; i < 3; i++) {
        ProbeRay& pr = probe[i];
        while (50.0f > pr.t) {
          Vec3 s;
          s.x = out.x + pr.t * pr.dir.x;
          s.y = out.y + pr.t * pr.dir.y;
          s.z = out.z + pr.t * pr.dir.z;
          int j = CubeIndex(s.x, s.y, s.z, dim, dimSq, half);
          float h2 = (float)((int)heights[j] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
          float a2 = (float)(colors[j] >> 24) * 0.003921568859368563f;
          bool above = (a2 > alphaThr && h2 > waterTop);
          if (h2 < water || above) {
            pr.t = pr.t + cellLen;
          } else {
            break;
          }
        }
        Vec3 pp;
        pp.x = pr.t * pr.dir.x + out.x;
        pp.y = pr.dir.y * pr.t + out.y;
        pp.z = pr.dir.z * pr.t + out.z;
        Vec3 tmp;
        pr.start = *pm->ToSurface(&tmp, &pp);
      }
      FUN_00af1610(ctx, pm, &out, &out, &probe[1].start, &probe[0].start, &probe[2].start, t0);
      return found;
    }
    t = t + cellLen;
    if (!(*tMax > t)) break;
  }
  return found;
}

// @ 0x00af4870
// Simpler variant: steps along the ray at a fixed step, finds the first sample above water and the extent of the
// above-water run, then reports the run's midpoint through FUN_00af1570 and updates *tMax.
bool FUN_00af4870(const Vec3* origin, const Vec3* dir, float t0, float step, void* ctx, float* tMax) {
  if (1.52587890625e-05f > *tMax) return false;
  bool found = false;
  cPlanetModel* pm = SP_PlanetModel();
  float water = pm->GetWaterHeight();
  TerrainMap* map = pm->mpISphere->GetMap();
  uint16_t* heights = map->height->data;
  int dim = map->color->dim;
  float hscale = map->heightScale;
  float radius0 = map->radius;
  int dimSq = dim * dim;
  float t = t0 + step;
  if (!(*tMax > t)) return found;
  float half = (float)dim * 0.5f;
  for (;;) {
    float px = origin->x + dir->x * t;
    float py = origin->y + dir->y * t;
    float pz = origin->z + dir->z * t;
    int idx = CubeIndex(px, py, pz, dim, dimSq, half);
    float H = (float)((int)heights[idx] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
    if (H > water) {
      found = true;
      float s = step;
      if (*tMax > t + s) {
        for (;;) {
          float qx = origin->x + dir->x * (t + s);
          float qy = origin->y + dir->y * (t + s);
          float qz = origin->z + dir->z * (t + s);
          int j = CubeIndex(qx, qy, qz, dim, dimSq, half);
          float h2 = (float)((int)heights[j] - 0x8000) * hscale * 3.0518509447574615e-05f + radius0;
          if (water > h2) break;
          s = s + step;
          if (!(*tMax > s + t)) break;
        }
      }
      float hs = s * 0.5f;
      Vec3 mid;
      mid.x = origin->x + dir->x * (hs + t);
      mid.y = origin->y + dir->y * (hs + t);
      mid.z = origin->z + dir->z * (hs + t);
      FUN_00af1570(ctx, pm, &mid, &mid, hs, 0, 0);
      *tMax = t;
      return found;
    }
    t = t + step;
    if (!(*tMax > t)) break;
  }
  return found;
}
