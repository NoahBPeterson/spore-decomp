// Slice s00ac3110: terrain-travel cost queries on the cube-sphere planet grid.
//   FUN_00ac3110 / FUN_00ac38d0 : distance from a direction to a cell, using the terrain
//       height of both cells plus a per-cell "water depth" correction (variant with the
//       coarse-grid lookup in FUN_00ac38d0).
//   FUN_00ac3540 : signed height difference between two cells' terrain.
//   FUN_00ac3db0 / FUN_00ac3e30 : plain distance between two cells' face directions.
//   FUN_00ac3ef0 : count equal keys in a hash bucket.
//   FUN_00ac3fa0 : sift-down driver over an 8-byte-entry heap.
// Names are Claude-coined from behaviour; the class layout and the cube-cell mapping come
// from the neighbouring slice s00ac12f0.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

struct ISphereHost;
namespace SP {
class cPlanetModel {
 public:
  uint32_t pad00[9];
  ::ISphereHost* mpISphere;  // +0x24
  uint32_t pad28[9];
  uint32_t* mpCubeCells;     // +0x4c: 128x128x6 packed cell words
  uint32_t pad50[12];
  char* mpFaceNodes;         // +0x80
  uint32_t pad84[4];
  char* mpCoarseGrid;        // +0x94
  float SampleTerrainHeight(const float* dir);   // 0xb830b0
  float* Project(float* out, const float* in);   // 0xb81630
};
cPlanetModel* __cdecl PlanetModel();  // 0xb3d350
}  // namespace SP

struct SphereInfo {
  uint32_t pad0;      // +0x0
  uint32_t pad1;      // +0x4
  uint32_t pad2;      // +0x8
  void*    mpFaceNodes;  // +0xc  (has count at +8, byte data at +0x10)
  uint32_t pad[9];
  float outerRadius;  // +0x34
  float innerRadius;  // +0x38
  float pad3c;        // +0x3c
};
struct ISphereHost {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual SphereInfo* GetInfo();  // vtable +0xc
};

// direction on a cube face for cell (x, y): writes 3 floats
void __cdecl FUN_00ac1510(uint32_t face, int x, int y, float* out);   // 0x00ac1510
// travel cost from a to b, scaled by what the endpoints stand on
float __cdecl FUN_00ac1b30(const float* a, const float* b);           // 0x00ac1b30
// heap sift-down on 8-byte {key, value} entries
void __cdecl FUN_00ac2060(void* first, int top, int len, int hole, uint32_t a, uint32_t b, uint32_t c);  // 0x00ac2060

extern const float kOne;        // 0x1485720  (1.0f)
extern const float kScale64;    // 0x140f334  (64.0f)
extern const float kZero;       // 0x1485378  (0.0f)
extern const float kInv32768;   // 0x140d4f8  (1/32768)
extern const float kTen;        // 0x1459e28  (10.0f)
extern const float kSixteen;    // 0x1459e24  (16.0f)
extern const float kEight;      // 0x13eeda0  (8.0f)
extern const float kInv255;     // 0x13eecd4  (1/255)
extern const float kHalf;       // 0x1471064  (0.5f)
extern const float kThousand;   // 0x13ec5b4  (1000.0f)
extern const float kOneOver128; // 0x1459e14  (1/128)
extern float g_FltMax;          // 0x1565ba4

// Cube-map face/cell of a direction: returns face 0..5, writes (u, v) in [0, N).
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

// @ 0x00ac3110
float __cdecl FUN_00ac3110(const float* pos, uint32_t cell) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  SphereInfo* info = pm->mpISphere->GetInfo();
  uint32_t* cells = pm->mpCubeCells;
  uint32_t cw = cells[(((cell >> 8 & 0xff) + (cell >> 17) * 0x80) * 0x80) + (cell & 0xff)];
  bool bFlag = false;
  if ((cw & 0x18000000) != 0) {
    int u, v;
    int face = CubeCell<64>(pos, &u, &v);
    if ((cells[((face * 0x80 + v) * 0x80) + u] & 0x18000000) == 0) return g_FltMax;
    bFlag = true;
  }
  float height = (float)(int)((cw & 0xffff) - 0x8000) * info->innerRadius * kInv32768 + info->outerRadius;
  float fh = (float)pm->SampleTerrainHeight(pos);
  float inv = 1.0f / (float)sqrt((double)((pos[2] * pos[2] + pos[1] * pos[1]) + pos[0] * pos[0]));
  float p0 = pos[0] * inv * fh;
  float p1 = pos[1] * inv * fh;
  float p2 = pos[2] * inv * fh;
  float d[3];
  FUN_00ac1510(cell >> 17, cell & 0xff, (cell >> 8) & 0xff, d);
  float ex = d[0] * height - p0;
  float ey = d[1] * height - p1;
  float ez = d[2] * height - p2;
  float dist = (float)sqrt((double)(ex * ex + (ey * ey + ez * ez)));
  if (fh < height) dist = (height - fh) * kEight + dist;
  if ((cw & 0x4000000) != 0) dist = dist * kTen;
  if (bFlag) dist = dist * kSixteen;
  if (dist != g_FltMax) {
    float d2[3];
    FUN_00ac1510(cell >> 17, cell & 0xff, (cell >> 8) & 0xff, d2);
    float proj[3];
    pm->Project(proj, d2);
    float r = FUN_00ac1b30(pos, proj);
    if (r != 0.0f) return r;
  }
  return dist;
}

// @ 0x00ac3540
float __cdecl FUN_00ac3540(uint32_t cellA, uint32_t cellB) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  SphereInfo* info = pm->mpISphere->GetInfo();
  uint32_t* cells = pm->mpCubeCells;
  uint32_t cwB = cells[(((cellB >> 8 & 0xff) + (cellB >> 17) * 0x80) * 0x80) + (cellB & 0xff)];
  bool bFlag = false;
  if ((int)cwB < 0) return g_FltMax;
  if ((cwB & 0x18000000) != 0) {
    if ((cells[(((cellA >> 8 & 0xff) + (cellA >> 17) * 0x80) * 0x80) + (cellA & 0xff)] & 0x18000000) == 0)
      return g_FltMax;
    bFlag = true;
  }
  float hA = (float)(int)((cells[(((cellA >> 8 & 0xff) + (cellA >> 17) * 0x80) * 0x80) + (cellA & 0xff)] & 0xffff) - 0x8000) *
                 info->innerRadius * kInv32768 + info->outerRadius;
  float hB = (float)(int)((cwB & 0xffff) - 0x8000) * info->innerRadius * kInv32768 + info->outerRadius;
  float a[3], b[3];
  FUN_00ac1510(cellA >> 17, cellA & 0xff, (cellA >> 8) & 0xff, a);
  float ax = a[0] * hA, ay = a[1] * hA, az = a[2] * hA;
  FUN_00ac1510(cellB >> 17, cellB & 0xff, (cellB >> 8) & 0xff, b);
  float ex = b[0] * hB - ax;
  float ey = b[1] * hB - ay;
  float ez = b[2] * hB - az;
  float dist = (float)sqrt((double)(ex * ex + (ey * ey + ez * ez)));
  if (hA < hB) {
    dist = (hB - hA) * kSixteen + dist;
    float base = info->pad3c * info->innerRadius + info->outerRadius;
    float depth = hB - base;
    if (depth > kTen) {
      void* fp = info->mpFaceNodes;
      int n = *(int*)((char*)fp + 8);
      int u = (int)((float)n * kOneOver128);
      const uint8_t* px = *(const uint8_t**)((char*)fp + 0x10);
      float land = (float)px[3 + (((cellB >> 17) * n + ((cellB >> 8) & 0xff) * u) * n + (cellB & 0xff) * u) * 4] * kInv255;
      if (land > kHalf) dist = (depth - kTen) * kThousand + dist;
    }
  }
  if ((cwB & 0x4000000) != 0) dist = dist * kTen;
  if (bFlag) dist = dist * kSixteen;
  if (dist != g_FltMax) {
    float d1[3], d2[3];
    float pa[3], pb[3];
    FUN_00ac1510(cellB >> 17, cellB & 0xff, (cellB >> 8) & 0xff, d1);
    pm->Project(pa, d1);
    FUN_00ac1510(cellA >> 17, cellA & 0xff, (cellA >> 8) & 0xff, d2);
    pm->Project(pb, d2);
    float r = FUN_00ac1b30(pa, pb);
    if (r != 0.0f) return r;
  }
  return dist;
}

// @ 0x00ac38d0
float __cdecl FUN_00ac38d0(const float* pos, uint32_t cell) {
  SP::cPlanetModel* pm = SP::PlanetModel();
  SphereInfo* info = pm->mpISphere->GetInfo();
  uint32_t* cells = pm->mpCubeCells;
  uint32_t cw = cells[(((cell >> 8 & 0xff) + (cell >> 17) * 0x80) * 0x80) + (cell & 0xff)];
  bool bFlag = false;
  if ((cw & 0x18000000) != 0) {
    int u, v;
    int face = CubeCell<64>(pos, &u, &v);
    if ((cells[((face * 0x80 + v) * 0x80) + u] & 0x18000000) == 0) return g_FltMax;
    bFlag = true;
  }
  float height = (float)(int)((cw & 0xffff) - 0x8000) * info->innerRadius * kInv32768 + info->outerRadius;
  float fh = (float)pm->SampleTerrainHeight(pos);
  float inv = 1.0f / (float)sqrt((double)((pos[2] * pos[2] + pos[1] * pos[1]) + pos[0] * pos[0]));
  float p0 = pos[0] * inv * fh;
  float p1 = pos[1] * inv * fh;
  float p2 = pos[2] * inv * fh;
  float d[3];
  FUN_00ac1510(cell >> 17, cell & 0xff, (cell >> 8) & 0xff, d);
  float ex = d[0] * height - p0;
  float ey = d[1] * height - p1;
  float ez = d[2] * height - p2;
  float dist = (float)sqrt((double)(ex * ex + (ey * ey + ez * ez)));
  if (fh < height) {
    dist = (height - fh) * kSixteen + dist;
    float base = info->pad3c * info->innerRadius + info->outerRadius;
    float depth = height - base;
    if (depth > kTen) {
      void* fp = info->mpFaceNodes;
      int n = *(int*)((char*)fp + 8);
      int u = (int)((float)n * kOneOver128);
      const uint8_t* px = *(const uint8_t**)((char*)fp + 0x10);
      float land = (float)px[3 + (((cell >> 17) * n + ((cell >> 8) & 0xff) * u) * n + (cell & 0xff) * u) * 4] * kInv255;
      if (land > kHalf) dist = (depth - kTen) * kThousand + dist;
    }
  }
  if ((cw & 0x4000000) != 0) dist = dist * kTen;
  if (bFlag) dist = dist * kSixteen;
  if (dist != g_FltMax) {
    float d2[3];
    FUN_00ac1510(cell >> 17, cell & 0xff, (cell >> 8) & 0xff, d2);
    float proj[3];
    pm->Project(proj, d2);
    float r = FUN_00ac1b30(pos, proj);
    if (r != 0.0f) return r;
  }
  return dist;
}

// @ 0x00ac3db0
float __cdecl FUN_00ac3db0(uint32_t cellA, uint32_t cellB) {
  float a[3], b[3];
  FUN_00ac1510(cellB >> 17, cellB & 0xff, (cellB >> 8) & 0xff, b);
  FUN_00ac1510(cellA >> 17, cellA & 0xff, (cellA >> 8) & 0xff, a);
  float dx = a[0] - b[0];
  float dy = a[1] - b[1];
  float dz = a[2] - b[2];
  return (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
}

// @ 0x00ac3e30
float __cdecl FUN_00ac3e30(const float* pos, uint32_t cell) {
  float d[3];
  FUN_00ac1510(cell >> 17, cell & 0xff, (cell >> 8) & 0xff, d);
  float x = pos[0], y = pos[1], z = pos[2];
  float inv = 1.0f / (float)sqrt((double)((x * x + y * y) + z * z));
  float dz = z * inv - d[2];
  float dy = y * inv - d[1];
  float dx = x * inv - d[0];
  return (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
}

struct HashCounter {
  uint32_t mUnknown0;
  const uint32_t** mpBuckets;   // +0x4
  uint32_t mBucketCount;        // +0x8
  uint32_t Count(const uint32_t* key);
};

// @ 0x00ac3ef0
uint32_t HashCounter::Count(const uint32_t* key) {
  const uint32_t k = *key;
  const uint32_t* node = mpBuckets[k % mBucketCount];
  int count = 0;
  for (; node != 0; node = (const uint32_t*)node[1]) {
    if (k == *node) ++count;
  }
  return count;
}

// @ 0x00ac3fa0
void __cdecl FUN_00ac3fa0(char* first, char* last, uint32_t ctx) {
  int n = (int)(last - first) >> 3;
  if (n < 2) return;
  int i = (n - 2 >> 1) + 1;
  char* p = first + i * 8;
  do {
    uint32_t b = *(uint32_t*)(p - 4);
    uint32_t a = *(uint32_t*)(p - 8);
    --i;
    FUN_00ac2060(first, i, n, i, a, b, ctx);
    p -= 8;
  } while (i != 0);
}
