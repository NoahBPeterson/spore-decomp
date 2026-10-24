// slice s00697c40 — EA::Trace server bootstrap/locale-string plumbing and the SP quaternion
// direction helpers. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)
#define sqrtf(x) sqrt(x)
#define fabsf(x) fabs(x)

void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

// ---------------------------------------------------------------------------------------------
namespace eastl {

void FreeWStringBuffer(void* p) throw();   // operator delete(void*)

struct WStringAllocator {
  void deallocate(void* p, unsigned n) { FreeWStringBuffer(p); }
};

extern wchar_t gEmptyWString[1];

// basic_string<wchar_t, eastl::allocator>: 0 mpBegin, 4 mpEnd, 8 mpCapacity, 0xc allocator.
struct WString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  WStringAllocator mAllocator;

  WString() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
  void DoFree(wchar_t* p, unsigned n) { if (p) mAllocator.deallocate(p, n); }
  ~WString() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin)); }

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
// EA::Trace::Server default filter/formatter bootstrap.
namespace EA {
template <class T>
class AutoRefCount { public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) {
    if (mpObject)
      mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
namespace Trace {
struct IObj {
  virtual int AddRef();     // +0x00
  virtual int Release();    // +0x04
  virtual void v2();
  virtual void* Cast(unsigned id);
};
class ILogFilter : public IObj { public:
  virtual void v4();
  virtual void v5();
  virtual void v6();
};
class ILogFormatter : public IObj { public:
  virtual void v4();
  virtual void v5();
  virtual void v6();
};
class LogFilterGroupLevels : public ILogFilter { public:
  char pad[0x3c - 4];
  LogFilterGroupLevels(const char* name);   // 0x00923f30
};
class LogFormatterFancy : public ILogFormatter { public:
  char pad[0xa58 - 4];
  LogFormatterFancy(const char* name);      // 0x009244d0
  void SetFlags(unsigned short flags);      // 0x009233e0
};
class ILogReporter : public IObj { public:
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
  virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual ILogFormatter* GetFormatter();    // +0x38
};
struct ServerDefaults {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
  virtual void s10();
  virtual void GetReporter(const char* name, AutoRefCount<ILogReporter>* out);   // +0x2c
  virtual void SetGroupLevel(const char* group, int a, int level);               // +0x30
  unsigned pad04[10];
  AutoRefCount<ILogFilter> mDefaultFilter;        // +0x2c
  AutoRefCount<ILogFormatter> mDefaultFormatter;  // +0x30
  void Init();                                    // 0x00924790
  void InitDefaults();
};
}  // namespace Trace
}  // namespace EA
void* operator new(size_t, const char* name, int, unsigned, const char* file, int line);   // 0x00f473a0
void operator delete(void*, const char* name, int, unsigned, const char* file, int line);   // 0x00f47380

namespace EA {
namespace Trace {
// @ 0x00697c40
void ServerDefaults::InitDefaults() {
  if (mDefaultFilter == 0)
    mDefaultFilter = new ("Debug/EATrace/Server/DefaultFilter/LogFilterGroupLevels", 0, 0, 0, 0)
        LogFilterGroupLevels("DefaultFilter");
  if (mDefaultFormatter == 0)
    mDefaultFormatter = new ("Debug/EATrace/Server/DefaultFormatter/LogFormatterSimple", 0, 0, 0, 0)
        LogFormatterFancy("DefaultFormatter");
  Init();
  SetGroupLevel(0, 0, 0xfb);
  SetGroupLevel("AppDebugger", 0, 0x19);
  SetGroupLevel("AppAlertDialog", 0, 0x32);
  AutoRefCount<ILogReporter> reporter;
  GetReporter("AppDebugger", &reporter);
  {
    AutoRefCount<ILogFormatter> formatter(reporter->GetFormatter());
    ((LogFormatterFancy*)formatter.mpObject)->SetFlags(0x15);
  }
}
}  // namespace Trace
}  // namespace EA

namespace EA {
namespace Trace {

void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

struct ILogManager;

// The real EA::Trace::Server base is 0x68 bytes with two vtables (IServer, ITracer).
class IServer { public:
  virtual int AddRef();          // +0x00
  virtual int Release();         // +0x04
  virtual void s2();
  virtual void s3();
  virtual ILogManager* s4();     // +0x10
  virtual void s5();             // +0x14
  virtual void s6();
  virtual void s7();
};
class ITracer { public:
  virtual int AddRef();
  virtual int Release();
  virtual void t2();
  virtual void t3();
  virtual void t4();
};
// @ 0x00923d40 ctor, 0x00924bd0 dtor
struct ServerBase : IServer, ITracer {
  char pad[0x60];
  ServerBase();
  ~ServerBase();
};

// TempTraceHelperMap: 0x58 bytes (mutex + hash map + enable byte).
class TempTraceHelperMap { public:
  char pad[0x58];
  TempTraceHelperMap* Init();   // 0x009259d0
  void Destroy();               // 0x009257a0
};

// @ 0x00697e00 / 0x00697ee0 — Server(0x68) + three name strings + enable byte + helper map.
class LogManager : public ServerBase {
 public:
  LogManager();
  ~LogManager();
  eastl::WString mName0;          // +0x68
  eastl::WString mName1;          // +0x78
  eastl::WString mName2;          // +0x88
  bool mbField98;                 // +0x98
  char mPad99[7];
  TempTraceHelperMap mHelperMap;  // +0xa0
};
}  // namespace Trace
}  // namespace EA

// @ 0x00697e00
namespace EA {
namespace Trace {
LogManager::LogManager() {
  mbField98 = true;
  mHelperMap.Init();
}
}  // namespace Trace
}  // namespace EA

// @ 0x00697ee0
namespace EA {
namespace Trace {
LogManager::~LogManager() { mHelperMap.Destroy(); }
}  // namespace Trace
}  // namespace EA

// @ 0x00697fa0
namespace EA {
namespace Trace {
ILogManager* GetLogManager() {
  LogManager* p = new ("Debug/EATrace/LogManager", 0, 0, 0, 0) LogManager;
  p->s5();
  return p->s4();
}
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
  float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3 {
  float m[9];
};

static inline Vector3 Normalized(const Vector3& v) {
  float inv = 1.0f / (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  Vector3 r;
  r.x = v.x * inv;
  r.y = v.y * inv;
  r.z = v.z * inv;
  return r;
}

// @ 0x00698180
Quaternion* QuaternionFromDirections(Quaternion* out, const Vector3* a, const Vector3* b) {
  float a0 = a->x;
  float a1 = a->y;
  float a2 = a->z;
  volatile double inv = 1.0 / sqrt(((double)a0 * a0 + (double)a1 * a1) + (double)a2 * a2);
  volatile float invf = (float)inv;
  volatile float p = a0 * invf;
  volatile double lx = (double)a1 * inv;
  volatile double nx = (double)a2 * inv;
  float l = (float)lx;
  float n = (float)nx;
  float binv = 1.0f / sqrtf(b->x * b->x + b->y * b->y + b->z * b->z);
  float q = b->x * binv + p;
  float m = b->y * binv + l;
  float o = b->z * binv + n;
  if ((q * q + o * o) + m * m > 1e-4f) {
    volatile float s = 1.0f / sqrtf((q * q + o * o) + m * m);
    float ms = m * s;
    float os = o * s;
    float qs = q * s;
    out->x = os * l - ms * n;
    out->y = n * qs - os * p;
    out->z = ms * p - l * qs;
    out->w = (ms * l + os * n) + qs * p;
    return out;
  }
  if (!(fabs((double)p) > fabs((double)lx))) {
    volatile float s = (float)(1.0 / sqrt(lx * lx + nx * nx));
    out->x = 0.0f;
    out->y = -(n * s);
    out->z = l * s;
    out->w = 0.0f;
    return out;
  }
  volatile float s = (float)(1.0 / sqrt((double)p * (double)p + nx * nx));
  out->y = 0.0f;
  out->x = -(n * s);
  out->z = p * s;
  out->w = 0.0f;
  return out;
}

// @ 0x006983a0
void MatrixFromDirection(const Vector3* dir, Matrix3* out) {
  float s = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z + 1e-8f);
  float x = dir->x * s;
  float y = dir->y * s;
  float z = dir->z * s;
  out->m[6] = x;
  out->m[7] = y;
  out->m[8] = z;
  float v0, v1, v2, v3, v4, v5;
  if (!(fabsf(z) < 0.999)) {
    float k = 1.0f / sqrtf(x * x + z * z + 1e-8f);
    v0 = k * z;
    v1 = k * -0.0f;
    v2 = -x * k;
    v3 = v2 * y - v1 * z;
    v4 = v0 * z - v2 * x;
    v5 = v1 * x - v0 * y;
  } else {
    float k = 1.0f / sqrtf(x * x + y * y + 1e-8f);
    v0 = -y * k;
    v1 = x * k;
    v2 = k * -0.0f;
    v3 = v2 * y - v1 * z;
    v4 = v0 * z - v2 * x;
    v5 = v1 * x - v0 * y;
  }
  out->m[0] = v0;
  out->m[1] = v1;
  out->m[2] = v2;
  out->m[3] = v3;
  out->m[4] = v4;
  out->m[5] = v5;
  (void)*(volatile unsigned int*)&out->m[5];
}

// @ 0x006985b0
void OrthogonalVector(Vector3* out, const Vector3* v) {
  if (fabsf(v->x) < fabsf(v->y)) {
    if (fabsf(v->x) < fabsf(v->z)) {
      out->x = 0.0f;
      out->y = v->z;
      out->z = -v->y;
      return;
    }
    out->x = v->y;
    out->y = -v->x;
    out->z = 0.0f;
    return;
  }
  if (fabsf(v->y) < fabsf(v->z)) {
    out->x = -v->z;
    out->y = 0.0f;
    out->z = v->x;
    return;
  }
  out->x = v->y;
  out->y = -v->x;
  out->z = 0.0f;
}

// @ 0x00698650 — orthonormalise a 3x3 (row1 = normal, row2 orthogonalised against row1).
void MatrixFromQuaternion(Matrix3* m) {
  double inv = 1.0 / (sqrt((double)m->m[3] * m->m[3] + (double)m->m[4] * m->m[4] + (double)m->m[5] * m->m[5]) + 1e-8);
  volatile float t3 = (float)((double)m->m[3] * inv);
  volatile float t4 = (float)((double)m->m[4] * inv);
  volatile float t5 = (float)((double)m->m[5] * inv);
  m->m[3] = t3;
  m->m[4] = t4;
  m->m[5] = t5;
  volatile float p1 = m->m[5] * m->m[8];
  volatile float p2 = m->m[4] * m->m[7];
  volatile float p3 = m->m[3] * m->m[6];
  volatile float s12 = p1 + p2;
  volatile float d = s12 + p3;
  volatile float q3 = m->m[3] * d;
  volatile float q4 = m->m[4] * d;
  volatile float q5 = m->m[5] * d;
  m->m[6] = m->m[6] - q3;
  m->m[7] = m->m[7] - q4;
  m->m[8] = m->m[8] - q5;
  double inv2 = 1.0 / (sqrt((double)m->m[6] * m->m[6] + (double)m->m[7] * m->m[7] + (double)m->m[8] * m->m[8]) + 1e-8);
  m->m[6] = (float)((double)m->m[6] * inv2);
  m->m[7] = (float)((double)m->m[7] * inv2);
  m->m[8] = (float)((double)m->m[8] * inv2);
  volatile float u0 = m->m[8] * m->m[4];
  volatile float v0 = m->m[7] * m->m[5];
  m->m[0] = u0 - v0;
  volatile float u1 = m->m[6] * m->m[5];
  volatile float v1 = m->m[3] * m->m[8];
  m->m[1] = u1 - v1;
  volatile float u2 = m->m[3] * m->m[7];
  volatile float v2 = m->m[6] * m->m[4];
  m->m[2] = u2 - v2;
  volatile float s0 = m->m[0] * m->m[0];
  volatile float s1 = m->m[1] * m->m[1];
  volatile float s2 = m->m[2] * m->m[2];
  volatile float t01 = s0 + s1;
  volatile float len = t01 + s2;
  if (len < 0.95f) {
    Vector3 tmp;
    typedef Vector3* (*OrthoPtr)(Vector3*, const Vector3*);
    Vector3* r = ((OrthoPtr)OrthogonalVector)(&tmp, (const Vector3*)&m->m[3]);
    m->m[6] = r->x;
    m->m[7] = r->y;
    m->m[8] = r->z;
    volatile float w0 = m->m[8] * m->m[4];
    volatile float w1 = m->m[7] * m->m[5];
    m->m[0] = w0 - w1;
    volatile float w2 = m->m[6] * m->m[5];
    volatile float w3 = m->m[3] * m->m[8];
    m->m[1] = w2 - w3;
    volatile float w4 = m->m[3] * m->m[7];
    volatile float w5 = m->m[6] * m->m[4];
    m->m[2] = w4 - w5;
  }
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
  if (t1 > t3) return false;
  if (t4 > t2) return false;
  if (t1 < t4) t1 = t4;
  if (t3 < t2) t2 = t3;
  unsigned int nz = (dir[2] < 0.0f);
  float invZ = 1.0f / dir[2];
  float t5 = (box[5 - nz * 3] - origin[2]) * invZ;
  float t6 = (box[nz * 3 + 2] - origin[2]) * invZ;
  if (t1 > t5) return false;
  if (t6 > t2) return false;
  if (t1 < t6) t1 = t6;
  if (t5 < t2) t2 = t5;
  if (0.0f > t2) return false;
  if (outT) {
    if (t1 >= 0.0f)
      *outT = t1;
    else
      *outT = 0.0f;
  }
  return true;
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
  if (t1 > t3) return false;
  if (t4 > t2) return false;
  if (t1 < t4) t1 = t4;
  if (t3 < t2) t2 = t3;
  float t5 = (box[5 - nz * 3] - p1[2]) * invZ;
  float t6 = (box[nz * 3 + 2] - p1[2]) * invZ;
  if (t1 > t5) return false;
  if (t6 > t2) return false;
  if (t1 < t6) t1 = t6;
  if (t5 < t2) t2 = t5;
  if (0.0f > t2) return false;
  if (t1 >= 1.0f) return false;
  if (outT) {
    if (t1 >= 0.0f)
      *outT = t1;
    else
      *outT = 0.0f;
  }
  return true;
}

// @ 0x00698b30 — closest distance from point `p` to segment [a, b].
float DistanceToSegment(const Vector3* p, const Vector3* a, const Vector3* b) {
  float lc = p->x - a->x;
  float l8 = p->y - a->y;
  float l4 = p->z - a->z;
  float d10 = b->x - a->x;
  float d11 = b->y - a->y;
  float d12 = b->z - a->z;
  float dot = (l4 * d12 + l8 * d11) + lc * d10;
  if (0.0f < dot) {
    float len2 = (d12 * d12 + d11 * d11) + d10 * d10;
    if (len2 <= dot) {
      float dx = p->x - b->x;
      float dy = p->y - b->y;
      float dz = p->z - b->z;
      return sqrtf((dz * dz + dy * dy) + dx * dx);
    }
    float s = dot / len2;
    lc = p->x - (a->x + d10 * s);
    l8 = p->y - (d11 * s + a->y);
    l4 = p->z - (a->z + d12 * s);
  }
  return sqrtf(lc * lc + (l8 * l8 + l4 * l4));
}
}  // namespace SP
