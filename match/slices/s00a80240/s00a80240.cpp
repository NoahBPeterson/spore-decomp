// slice s00a80240: Swarm billboard particle effect, write one camera-facing quad (4 vertices) per
// live particle into a locked vertex stream (0x00a80240). Class and member names are coined; the
// field roles come from usage. The particle carries a position (+0x74), a rotation angle (+0x50),
// two basis vectors (+0x80, +0x8c), a width/height pair (+0x18, +0x54), an RGBA colour (+0x40) and
// a UV rectangle (+0x58..+0x64). The angle goes through a table-driven sine/cosine.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <xmmintrin.h>

extern float gSinCosAngleScale;   // 0x01677804
extern float gSinCosInvStep;      // 0x01677768
extern float gSinCosStep;         // 0x016777f0
extern float gSinCosTable[32];    // 0x01677840 {sin, cos} per step

static inline void FastSinCos(float a, float& s, float& c) {
  float t = a * gSinCosInvStep + 12582912.0f;
  int bits = *(int*)&t;
  float r = a - (float)(bits - 0x4b400000) * gSinCosStep;
  int i = (bits & 0xf) * 2;
  float s0 = gSinCosTable[i];
  float c0 = gSinCosTable[i + 1];
  c = c0 - (r * c0 * 0.5f + s0) * r;
  s = (c0 - r * s0 * 0.5f) * r + s0;
}

struct VertexStream {
  virtual int Lock(int count, char** pBase, int* pStride);   // slot 0
  virtual void Slot1();
  virtual void Unlock();                                     // slot 2
};

struct Vector2 { float x, y; Vector2() {} Vector2(float _x, float _y) : x(_x), y(_y) {} };
struct Vector3 { float x, y, z; Vector3() {} Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {} };

static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }

struct BillboardParticle {
  uint32_t pad0[6];      // +0x00
  float size;            // +0x18
  uint32_t pad1[9];      // +0x1c
  float r, g, b, a;      // +0x40
  float angle;           // +0x50
  float aspect;          // +0x54
  float uvW, uvH;        // +0x58, +0x5c
  float u0, v0;          // +0x60, +0x64
  uint32_t pad2[3];      // +0x68
  Vector3 pos;           // +0x74
  Vector3 axisX;         // +0x80
  Vector3 axisY;         // +0x8c
};

struct BillboardEffect {
  uint8_t pad0[0x10];
  uint8_t posOffset;     // +0x10 vertex position offset
  uint8_t colorOffset;   // +0x11
  uint8_t uvOffset;      // +0x12
  uint8_t pad1;
  BillboardParticle** mpBegin;   // +0x14
  BillboardParticle** mpEnd;     // +0x18

  void WriteQuads(VertexStream* stream);
};

static inline int ToByte(float x) {
  __m128 v = _mm_max_ss(_mm_set_ss(0.0f), _mm_load_ss(&x));
  v = _mm_mul_ss(v, _mm_set_ss(255.0f));
  v = _mm_min_ss(v, _mm_set_ss(255.0f));
  return _mm_cvtss_si32(v);
}

static inline void PutVertex(char* v, const BillboardEffect* fx, const Vector3& pos,
                             uint32_t color, const Vector2& uv) {
  *(Vector3*)(v + fx->posOffset) = pos;
  *(uint32_t*)(v + fx->colorOffset) = color;
  *(Vector2*)(v + fx->uvOffset) = uv;
}

// @ 0x00a80240
void BillboardEffect::WriteQuads(VertexStream* stream) {
  BillboardParticle** cur = mpBegin;
  int remaining = (int)(mpEnd - mpBegin);
  while (remaining > 0) {
    char* v;
    int stride;
    int n = stream->Lock(remaining, &v, &stride);
    if (n == 0)
      break;
    remaining -= n;
    for (; n > 0; --n) {
      BillboardParticle* p = *cur;
      Vector3 pos = p->pos;
      float s, c;
      FastSinCos(p->angle * gSinCosAngleScale, s, c);
      Vector3 up = p->axisY * c - p->axisX * s;
      Vector3 fw = p->axisX * c + p->axisY * s;
      float sz = p->size;
      Vector3 q = up * (p->aspect * sz);
      uint32_t color = ((((uint32_t)ToByte(p->a) & 0xff) << 8 | (ToByte(p->r) & 0xff)) << 8
                        | (ToByte(p->g) & 0xff)) << 8 | (ToByte(p->b) & 0xff);
      Vector3 a = pos - fw * sz;
      Vector3 b = fw * sz + pos;
      PutVertex(v, this, a + q, color, Vector2(p->u0, p->v0));
      v += stride;
      PutVertex(v, this, a - q, color, Vector2(p->u0, p->v0 + p->uvH));
      v += stride;
      PutVertex(v, this, b - q, color, Vector2(p->u0 + p->uvW, p->v0 + p->uvH));
      v += stride;
      PutVertex(v, this, b + q, color, Vector2(p->u0 + p->uvW, p->v0));
      v += stride;
      ++cur;
    }
    stream->Unlock();
  }
}
