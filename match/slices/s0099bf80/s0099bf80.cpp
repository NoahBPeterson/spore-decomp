// Slice s0099bf80 (bfs4 #36): vector/quaternion math helpers, anim bind-record helpers,
// and a few intrusive-container utilities. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedDecrement, _InterlockedExchange, _InterlockedExchangeAdd)

typedef unsigned int uint;

extern "C" void  operator_delete(void*);  // 0x00f47380
extern "C" __declspec(dllimport) double modf(double, double*);
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
extern "C" double acos(double);
extern "C" double sin(double);
#pragma intrinsic(acos, sin)
extern const float g_eps;    // 0x013ebca0  0.0001f

struct Vec4 { float x, y, z, w; Vec4* Normalize(float* out); };

// SSE constants (addresses are masked relocations)
extern const float g_one;    // 0x01485720  1.0f
extern const float g_zero;   // 0x01485378  0.0f
extern const float g_two;    // 0x01470f1c  2.0f
extern const float g_negone; // 0x013eb1bc

// ===========================================================================
// @ 0x0099bf80  recursive refcounted-list destructor
// ===========================================================================
struct RefObj {
  virtual void destroy(int);
  int mRefCount;     // +0x04
};
struct RefNode {
  RefNode* mpLeft;   // +0x00
  RefNode* mpRight;  // +0x04
  char     pad[0x0c];
  RefObj*  mpRef;    // +0x14
};
struct ListHead { void f(RefNode* node); };
void ListHead::f(RefNode* node) {
  while (node != 0) {
    f(node->mpLeft);
    RefObj* obj = node->mpRef;
    RefNode* next = node->mpRight;
    if (obj != 0) {
      long n = _InterlockedDecrement((volatile long*)&obj->mRefCount);
      if (n == 0) {
        _InterlockedExchange((volatile long*)&obj->mRefCount, 1);
        if (obj != 0) obj->destroy(1);
      }
    }
    operator_delete(node);
    node = next;
  }
}

// ===========================================================================
// @ 0x0099bfe0  FractionalPart(float)  (x87)
// ===========================================================================
double FUN_0099bfe0(float f) {
  double ip;
  double r = modf((double)f, &ip);
  if (!(f >= g_zero)) r = 1.0 - r;
  return r;
}

// ===========================================================================
// @ 0x0099c020  Vec4::Normalize(float* lengthOut)
// ===========================================================================
Vec4* Vec4::Normalize(float* out) {
  float len = (float)sqrt(x * x + y * y + z * z + w * w);
  if (out != 0) *out = len;
  if (len != 0.0f) {
    float inv = 1.0f / len;
    x *= inv; y *= inv; z = inv * z; w = inv * w;
  }
  return this;
}

// ===========================================================================
// @ 0x0099c0b0  quaternion multiply  out = a * b
// ===========================================================================
void FUN_0099c0b0(float* out, const float* a, const float* b) {
  float b0 = b[0];
  float b3 = b[3];
  float a3 = a[3];
  float a2 = a[2];
  float b2 = b[2];
  float a1 = a[1];
  float b1 = b[1];
  out[0] = ((b0 * a3 + a[0] * b3) - b[1] * a2) + b2 * a1;
  float a0 = a[0];
  out[1] = ((a2 * b0 + b1 * a3) + a1 * b3) - b2 * a0;
  float c1 = b[1];
  float c2 = a[2];
  out[2] = ((a[2] * b3 - a1 * b0) + b2 * a3) + b[1] * a0;
  out[3] = ((a3 * b3 - b0 * a0) - a1 * c1) - b2 * c2;
}

// ===========================================================================
// @ 0x0099c1a0  rotate vector by quaternion (variant A)
// ===========================================================================
void FUN_0099c1a0(float* out, const float* q, const float* v) {
  float qx = q[0], qy = q[1], qz = q[2], qw = q[3];
  float vx = v[0], vy = v[1], vz = v[2];
  out[0] = (((-(qz * qz) + -(qy * qy)) * vx + (qz * qx + qy * qw) * vz) +
            (qy * qx - qz * qw) * vy) * g_two + vx;
  out[1] = (((qy * qx + qz * qw) * vx + (qz * qy - qx * qw) * vz) +
            (-(qz * qz) + -(qx * qx)) * vy) * g_two + vy;
  out[2] = (((qz * qx - qy * qw) * vx + (-(qy * qy) + -(qx * qx)) * vz) +
            (qz * qy + qx * qw) * vy) * g_two + vz;
}

// ===========================================================================
// @ 0x0099c310  rotate vector by quaternion (variant B)
// ===========================================================================
void FUN_0099c310(float* out, const float* q, const float* v) {
  float qx = q[0], qy = q[1], qz = q[2], qw = q[3];
  float vx = v[0], vy = v[1], vz = v[2];
  out[0] = (((-(qz * qz) + -(qy * qy)) * vx + (qz * qx + -(qy * qw)) * vz) +
            (qy * qx - -(qz * qw)) * vy) * g_two + vx;
  out[1] = (((qy * qx + -(qz * qw)) * vx + (qz * qy - -(qx * qw)) * vz) +
            (-(qz * qz) + -(qx * qx)) * vy) * g_two + vy;
  out[2] = (((qz * qx - -(qy * qw)) * vx + (-(qy * qy) + -(qx * qx)) * vz) +
            (qz * qy + -(qx * qw)) * vy) * g_two + vz;
}

// ===========================================================================
// @ 0x0099c470  find index of key in {count, (key,..)*5} table
// ===========================================================================
struct S99c470 {
  uint mCount;   // +0x00
  uint Find(uint key);
};
uint S99c470::Find(uint key) {
  uint i = 0;
  if (mCount > 0) {
    char* p = (char*)this + 4;
    do {
      if (*(uint*)p == key) return i;
      ++i;
      p += 0x14;
    } while (i < mCount);
  }
  return 0xffffffff;
}

// ===========================================================================
// @ 0x0099c4a0  add-or-update (key, val, f0, f1)
// ===========================================================================
struct S99c4a0 {
  uint mCount;   // +0x00
  bool Add(uint key, uint val, float f0, float f1);
};
bool S99c4a0::Add(uint key, uint val, float f0, float f1) {
  uint count = mCount;
  uint i = 0;
  if (count > 0) {
    char* p = (char*)this + 4;
    do {
      if (*(uint*)p == key) goto found;
      ++i;
      p += 0x14;
    } while (i < count);
  }
  i = 0xffffffff;
found:
  if (i < count) {
    char* e = (char*)this + i * 0x14;
    *(float*)(e + 0xc) = f0 + *(float*)(e + 0xc);
    *(uint*)(e + 8) = val;
    *(float*)(e + 0x14) = f1 + *(float*)(e + 0x14);
    return true;
  }
  if (count < 8) {
    mCount = count + 1;
    char* e = (char*)this + count * 0x14;
    *(uint*)(e + 4) = key;
    *(float*)(e + 0xc) = f0;
    *(uint*)(e + 8) = val;
    *(float*)(e + 0x14) = f1;
    return true;
  }
  return false;
}

// ===========================================================================
// @ 0x0099c540  add-or-update (key, val, f0, f1, f2)
// ===========================================================================
struct S99c540 {
  uint mCount;   // +0x00
  bool Add(uint key, uint val, float f0, float f1, float f2);
};
bool S99c540::Add(uint key, uint val, float f0, float f1, float f2) {
  uint count = mCount;
  uint i = 0;
  if (count > 0) {
    char* p = (char*)this + 4;
    do {
      if (*(uint*)p == key) goto found;
      ++i;
      p += 0x14;
    } while (i < count);
  }
  i = 0xffffffff;
found:
  if (i < count) {
    char* e = (char*)this + i * 0x14;
    *(float*)(e + 0xc) = f0 + *(float*)(e + 0xc);
    *(float*)(e + 0x10) = f1 + *(float*)(e + 0x10);
    *(uint*)(e + 8) = val;
    *(float*)(e + 0x14) = f2 + *(float*)(e + 0x14);
    return true;
  }
  if (count < 8) {
    mCount = count + 1;
    char* e = (char*)this + count * 0x14;
    *(float*)(e + 0xc) = f0;
    *(uint*)(e + 4) = key;
    *(float*)(e + 0x10) = f1;
    *(uint*)(e + 8) = val;
    *(float*)(e + 0x14) = f2;
    return true;
  }
  return false;
}

// ===========================================================================
// @ 0x0099c600  bit-length (position of highest set bit + 1)
// ===========================================================================
int FUN_0099c600(uint lo, uint hi) {
  int r = 0;
  if (hi != 0) { r = 0x20; lo = hi; hi = 0; }
  int c = 0;
  if (lo & 0xffff0000) { c = 0x10; lo >>= 0x10; }
  if (lo & 0xff00) { c += 8; lo >>= 8; }
  if (lo & 0xf0) { c += 4; lo >>= 4; }
  if (lo & 0xc) { c += 2; lo >>= 2; }
  int t = c + 1;
  if ((lo & 2) == 0) t = c;
  return t + r;
}

// ===========================================================================
// @ 0x0099c670  select result by flags field & 0x32
// ===========================================================================
uint FUN_0099c670(int a, int b, uint c) {
  switch (*(unsigned short*)(a + 0xac) & 0x32) {
    case 2:
      if (g_zero < *(float*)(b + 0x10c)) return 1;
      return 0;
    case 0x10:
      if (*(float*)(b + 0x10c) <= 0.0f) return 1;
      break;
    case 0x12:
      return (c == 0);
    case 0x20:
      break;
    case 0x21:
      return 1;
    default:
      return c;
  }
  return 0;
}

// ===========================================================================
// @ 0x0099c710  set bits in a channel mask
// ===========================================================================
extern bool (*g_chanTable[])(int);   // 0x01550bd8
bool FUN_0099c710(int self, uint mask, uint want) {
  uint bits = ~*(uint*)(self + 0x354) & mask;
  *(uint*)(self + 0x354) |= bits;
  while (bits != 0) {
    uint low = (uint)(-(int)bits) & bits;
    int idx = 0;
    uint v = low;
    if (low & 0xffff0000) { idx = 0x10; v >>= 0x10; }
    if (v & 0xff00) { idx += 8; v >>= 8; }
    if (v & 0xf0) { idx += 4; v >>= 4; }
    if (v & 0xc) { idx += 2; v >>= 2; }
    if (v & 2) ++idx;
    if (g_chanTable[idx](self))
      *(uint*)(self + 0x350) |= low;
    bits ^= low;
  }
  return (*(uint*)(self + 0x350) & mask) == want;
}

// ===========================================================================
// @ 0x0099c7b0  init channel (anim bind record)
// ===========================================================================
extern "C" int FUN_009b2340(void* buf, int mask, void* p4, void* rec, void* param, int zero);
extern "C" void MirrorSagittalContextTarget(void* src, void* out16);
struct S99c7b0Rec { char pad0[0x88]; uint8_t mFlags; char pad1[0x03]; uint8_t mKey[0x10]; uint32_t mCtx; int mCtx2; };
struct S99c7b0 {
  int*  mpOwner;         // +0x00 (array of record pointers at +0x148)
  void* mpP4;            // +0x04
  char  pad0[0x908];
  S99c7b0Rec* mpRec;     // +0x910
  char  mBuf[0x3fc];     // +0x914
  int   mResult;         // +0xd10
  int   mOther;          // +0xd14
  uint8_t mMatch;        // +0xd18
};
extern "C" int __cdecl memcmp(const void*, const void*, unsigned int);
#pragma intrinsic(memcmp)
// original: static local helper (ESI = this, EDX = index, param on the stack)
static void __stdcall InitChannel99(S99c7b0* self, int index, void* param) {
  S99c7b0Rec* rec = (*(S99c7b0Rec***)((char*)self->mpOwner + 0x148))[index];
  self->mpRec = rec;
  self->mResult = 0;
  self->mMatch = 0;
  self->mOther = -1;
  if ((rec->mFlags & 1) != 0) {
    uint32_t c = rec->mCtx & 0x100003;
    if (c <= 0x100002) {
      if ((c - 2 > 0xffffd) || c == 3) {
        self->mResult = FUN_009b2340(self->mBuf, 0xff, self->mpP4, &rec->mCtx, param, 0);
        uint32_t local[4];
        local[0] = 0; local[1] = 0; local[2] = 0; local[3] = 0;
        MirrorSagittalContextTarget(&self->mpRec->mCtx, local);
        self->mMatch = (memcmp(local, self->mpRec->mKey, 16) == 0);
      }
    } else if (c == 0x100003) {
      self->mOther = rec->mCtx2;
    }
  }
}
// keeps the static helper emitted (its real caller is in another slice)
void KeepInitChannel99(S99c7b0* self, int index, void* param) { InitChannel99(self, index, param); }

// ===========================================================================
// @ 0x0099c910  byte remap helper
// ===========================================================================
struct S99c910Ctx {
  int*   mpCounts;     // +0x00
  uint8_t* mpOut;      // +0x04
  int*   mpRemaining;  // +0x08
  uint8_t* mpTable;    // +0x0c
  int    mStride;      // +0x10
  int*   mpOutCount;   // +0x14
};
// original passes ctx in EAX (link-time custom convention); natural form here
static void __stdcall FUN_0099c910(S99c910Ctx* ctx, uint8_t* p, uint8_t last) {
  uint8_t b = *p;
  if (b != 0xff) {
    do {
      ctx->mpCounts[b] = ctx->mpCounts[b] - 1;
      if (ctx->mpCounts[b] == 0) {
        ctx->mpOut[*ctx->mpOutCount] = b;
        *ctx->mpOutCount = *ctx->mpOutCount + 1;
      }
      *ctx->mpRemaining = *ctx->mpRemaining - 1;
      b = *++p;
    } while (b != 0xff);
    ctx->mpTable[last * ctx->mStride] = 0xff;
  }
}

// keeps the static helper emitted (its real caller lives in another slice)
void KeepFUN_0099c910(S99c910Ctx* ctx, uint8_t* p, uint8_t last) { FUN_0099c910(ctx, p, last); }

// ===========================================================================
// @ 0x0099c990  find table entry by (type, key)
// ===========================================================================
int FUN_0099c990(char* arr, uint count, uint type, int key) {
  uint i = 0;
  if (count > 0) {
    int* p = (int*)(arr + 4);
    do {
      if (((p[-1] & 0xf) == type) && (*p != 0) && (*p == key || key == -1))
        return (int)(arr + i * 0x20);
      ++i;
      p += 8;
    } while (i < count);
  }
  return 0;
}

// ===========================================================================
// @ 0x0099c9f0  index wrap helper
// ===========================================================================
static inline int WrapIndex99(int v, int n) {
  if (v < 0) {
    int r = -v % n;
    if (r != 0) r = n - r;
    return r;
  }
  return v % n;
}
void FUN_0099c9f0(int self, int* cur, int* outPrev, int* outNext, int* outOther) {
  int v = *cur;
  int n = *(int*)(self + 0xd4);
  if (v == n) {
    v = n - 1;
    *cur = v;
    *outNext = v;
  } else if (v != 0) {
    v = v - 1;
    *outNext = v;
  } else {
    *outNext = 0;
    v = 0;
  }
  if (0 < v) {
    v = v - 1;
  } else if ((*(unsigned char*)(*(int*)(self + 4) + 0x118) & 8) == 0) {
    v = *outNext;
  } else {
    v = WrapIndex99(*outNext - 2, n);
  }
  *outPrev = v;
  v = *cur;
  if (v < n - 1) {
    v = v + 1;
  } else if ((*(unsigned char*)(*(int*)(self + 4) + 0x118) & 8) != 0) {
    *outOther = WrapIndex99(v + 2, n);
    return;
  }
  *outOther = v;
}

// ===========================================================================
// @ 0x0099cab0  intrusive smart-pointer assign
// ===========================================================================
struct AddRefHelper { void addref(); };
struct ReleaseHelper { void release(); };
struct IntrusivePtr { void* mpPtr; IntrusivePtr* assign(void* p); };
IntrusivePtr* IntrusivePtr::assign(void* p) {
  void* old = mpPtr;
  if (p != old) {
    if (p != 0) ((AddRefHelper*)p)->addref();
    mpPtr = p;
    if (old != 0) ((ReleaseHelper*)old)->release();
  }
  return this;
}

// ===========================================================================
// @ 0x0099cae0  Vec4b::NormalizeTo
// ===========================================================================
void FUN_0099cae0(float* out, const float* src, float* lenOut) {
  float v[4];
  v[0] = src[0]; v[1] = src[1]; v[2] = src[2]; v[3] = src[3];
  float len = (float)sqrt(v[3] * v[3] + v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  if (lenOut != 0) *lenOut = len;
  if (len != 0.0f) {
    float inv = 1.0f / len;
    v[0] = inv * v[0]; v[1] = inv * v[1]; v[2] = inv * v[2]; v[3] = v[3] * inv;
  }
  out[0] = v[0]; out[1] = v[1]; out[2] = v[2]; out[3] = v[3];
}

// ===========================================================================
// @ 0x0099cba0  component add/sub depending on dot sign
// ===========================================================================
void FUN_0099cba0(float* out, float* a, float* b) {
  float a0 = *a;
  float b0 = *b;
  float a1 = a[1];
  float b1 = b[1];
  float a2 = a[2];
  float b2 = b[2];
  float a3 = a[3];
  float b3 = b[3];
  if (((b0 * a0 + b1 * a1) + b2 * a2) + b3 * a3 < 0.0f) {
    out[1] = a1 - b1;
    out[2] = a2 - b2;
    out[3] = a3 - b3;
    *out = a0 - b0;
    return;
  }
  out[1] = b1 + a1;
  out[2] = b2 + a2;
  out[3] = b3 + a3;
  *out = b0 + a0;
}

// ===========================================================================
// @ 0x0099cc70  quaternion slerp
// ===========================================================================
void FUN_0099cc70(float* out, float* a, float* b, float t) {
  float b1 = b[1];
  float a0 = *a;
  float a1 = a[1];
  float b2 = b[2];
  float a2 = a[2];
  float b3 = b[3];
  float a3 = a[3];
  float b0 = *b;
  float d = ((b0 * a0 + b1 * a1) + b2 * a2) + b3 * a3;
  float sign = g_one;
  if (g_negone < d) {
    if (g_one < d) {
      d = g_one;
      goto L42;
    }
  } else {
    d = g_negone;
  }
  if (d < g_zero) {
    d = -d;
    sign = g_negone;
  }
L42:
  float s0;
  if (g_one - d <= g_eps) {
    s0 = g_one - t;
  } else {
    double theta = acos((double)d);
    double inv = 1.0 / sin(theta);
    s0 = (float)(sin((1.0 - (double)t) * theta) * inv);
    t = (float)(sin((double)t * theta) * inv);
  }
  s0 = s0 * sign;
  out[0] = a0 * s0 + b0 * t;
  out[1] = a1 * s0 + b1 * t;
  out[2] = a2 * s0 + b2 * t;
  out[3] = a3 * s0 + b3 * t;
}

// ===========================================================================
// @ 0x0099ce40  scale/unitize packed (Vec4, Vec4)
// ===========================================================================
void __fastcall FUN_0099ce40(float* p) {
  if (0.0f < p[3]) {
    float inv = 1.0f / p[3];
    p[0] = inv * p[0];
    p[1] = p[1] * inv;
    p[2] = p[2] * inv;
    p[3] = 1.0f;
  }
  if (0.0f < p[8]) {
    float w = p[7];
    float z = p[6];
    float y = p[5];
    float x = p[4];
    float len = (float)sqrt(((x * x + y * y) + z * z) + w * w);
    if (len != 0.0f) {
      float inv = 1.0f / len;
      p[4] = x * inv;
      p[5] = y * inv;
      p[6] = z * inv;
      p[7] = w * inv;
    }
    p[8] = 1.0f;
    return;
  }
  p[4] = 0.0f;
  p[5] = 0.0f;
  p[6] = 0.0f;
  p[7] = 1.0f;
}
