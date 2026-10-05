// slice s00697c40 — EA::Trace server bootstrap/locale-string plumbing and the SP quaternion
// direction helpers. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <math.h>

void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

// ---------------------------------------------------------------------------------------------
namespace eastl {

// basic_string<wchar_t, eastl::allocator>: 0 mpBegin, 4 mpEnd, 8 mpCapacity, 0xc allocator.
struct WString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  unsigned int mAllocator;

  WString& assign(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x423650
};

inline size_t WStrlen(const wchar_t* p) {
  const wchar_t* q = p;
  while (*q) ++q;
  return (size_t)(q - p);
}

}  // namespace eastl

// ---------------------------------------------------------------------------------------------
namespace EA {
namespace Trace {

// @ 0x00698030 (ret 0xc, __thiscall): assign three strings at +0x68/+0x78/+0x88 then re-run
// the assert/locale refresh.
void ServerRefreshAsserts(void* self);  // 0x697bb0

class Server {
 public:
  char pad0[0x68];
  eastl::WString mName0;  // +0x68
  eastl::WString mName1;  // +0x78
  eastl::WString mName2;  // +0x88

  __declspec(noinline) void RefreshAsserts();
  void SetNames(const wchar_t* a, const wchar_t* b, const wchar_t* c);
};

__declspec(noinline) void Server::RefreshAsserts() { ServerRefreshAsserts(this); }

// @ 0x00698030
void Server::SetNames(const wchar_t* a, const wchar_t* b, const wchar_t* c) {
  mName0.assign(a, a + eastl::WStrlen(a));
  mName1.assign(b, b + eastl::WStrlen(b));
  mName2.assign(c, c + eastl::WStrlen(c));
  RefreshAsserts();
}

}  // namespace Trace
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// @ 0x00697c40 (partial: skeleton) — EA::Trace::Server default filter/formatter bootstrap.
namespace EA {
namespace Trace {
void ServerBootstrap(void* self) { (void)self; }
}  // namespace Trace
}  // namespace EA

// @ 0x00697e00 (partial: skeleton) — EA::Trace::CreateDefaultTracer.
namespace EA {
namespace Trace {
void* CreateDefaultTracer(void* mem) { return mem; }
}  // namespace Trace
}  // namespace EA

// @ 0x00697ee0 (partial: skeleton) — EA::Trace::LogManager destructor.
namespace EA {
namespace Trace {
void DestroyLogManager(void* self) { (void)self; }
}  // namespace Trace
}  // namespace EA

// @ 0x00697fa0 (partial: skeleton) — EA::Trace::GetLogManager singleton.
namespace EA {
namespace Trace {
void* GetLogManager() { return 0; }
}  // namespace Trace
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// SP orientation helpers (x87/SSE heavy; partial skeletons).
namespace SP {
struct Vector3 {
  float x, y, z;
};
struct Quaternion {
  float x, y, z, w;
};
struct Matrix3 {
  float m[9];
};

// @ 0x00698180 (partial: skeleton)
void QuaternionFromDirections(Quaternion* out, const Vector3* a, const Vector3* b) {
  (void)out;
  (void)a;
  (void)b;
}

// @ 0x006983a0 (partial: skeleton)
void MatrixFromDirection(Matrix3* out, const Vector3* dir) {
  (void)out;
  (void)dir;
}

// @ 0x006985b0
void OrthogonalVector(Vector3* out, const Vector3* v) {
  if (fabsf(v->y) <= fabsf(v->x)) {
    if (fabsf(v->y) < fabsf(v->z)) {
      out->x = -v->z;
      out->y = 0.0f;
      out->z = v->x;
      return;
    }
  } else if (fabsf(v->x) < fabsf(v->z)) {
    out->x = 0.0f;
    out->y = v->z;
    out->z = -v->y;
    return;
  }
  out->x = v->y;
  out->y = -v->x;
  out->z = 0.0f;
}

// @ 0x00698650 (partial: skeleton)
void MatrixFromQuaternion(Matrix3* out, const Quaternion* q) {
  (void)out;
  (void)q;
}

// @ 0x00698880 — ray/AABB slab test. `box` is min[3] followed by max[3].
bool RayBoxIntersect(const float* origin, const float* dir, const float* box, float* outT) {
  float invX = 1.0f / dir[0];
  float invY = 1.0f / dir[1];
  unsigned int nx = (dir[0] < 0.0f);
  unsigned int ny = (dir[1] < 0.0f);
  float t1 = (box[nx * 3 + 0] - origin[0]) * invX;
  float t2 = (box[3 - nx * 3] - origin[0]) * invX;
  float t3 = (box[4 - ny * 3] - origin[1]) * invY;
  float t4 = (box[ny * 3 + 1] - origin[1]) * invY;
  if (t1 <= t3 && t4 <= t2) {
    if (t1 < t4) t1 = t4;
    if (t3 < t2) t2 = t3;
    unsigned int nz = (dir[2] < 0.0f);
    float invZ = 1.0f / dir[2];
    float t5 = (box[5 - nz * 3] - origin[2]) * invZ;
    float t6 = (box[nz * 3 + 2] - origin[2]) * invZ;
    if (t1 <= t5 && t6 <= t2) {
      if (t1 < t6) t1 = t6;
      if (t5 < t2) t2 = t5;
      if (0.0f <= t2) {
        if (outT) *outT = (0.0f <= t1) ? t1 : 0.0f;
        return true;
      }
    }
  }
  return false;
}

// @ 0x006989d0 — segment/AABB slab test; parameters are the two segment endpoints.
bool SegmentBoxIntersect(const float* p1, const float* p2, const float* box, float* outT) {
  float dx = p2[0] - p1[0];
  float dy = p2[1] - p1[1];
  float dz = p2[2] - p1[2];
  float invX = 1.0f / dx;
  float invY = 1.0f / dy;
  float invZ = 1.0f / dz;
  unsigned int nx = (dx < 0.0f);
  unsigned int ny = (dy < 0.0f);
  unsigned int nz = (dz < 0.0f);
  float t1 = (box[nx * 3 + 0] - p1[0]) * invX;
  float t2 = (box[3 - nx * 3] - p1[0]) * invX;
  float t3 = (box[4 - ny * 3] - p1[1]) * invY;
  float t4 = (box[ny * 3 + 1] - p1[1]) * invY;
  if (t1 <= t3 && t4 <= t2) {
    if (t1 < t4) t1 = t4;
    if (t3 < t2) t2 = t3;
    float t5 = (box[5 - nz * 3] - p1[2]) * invZ;
    float t6 = (box[nz * 3 + 2] - p1[2]) * invZ;
    if (t1 <= t5 && t6 <= t2) {
      if (t1 < t6) t1 = t6;
      if (t5 < t2) t2 = t5;
      if (0.0f <= t2 && t1 < 1.0f) {
        if (outT) *outT = (0.0f <= t1) ? t1 : 0.0f;
        return true;
      }
    }
  }
  return false;
}

// @ 0x00698b30 (partial: skeleton)
void QuaternionSlerp(Quaternion* out, const Quaternion* a, const Quaternion* b, float t) {
  (void)out;
  (void)a;
  (void)b;
  (void)t;
}
}  // namespace SP
