// slice s00a8aec0: EA::Swarm quad streamers of cDistributeEffect (free functions, namespace scope):
//   0x00a8aec0  Stream_Quad_V4F_N4F_C4B_T2F
//   0x00a8b420  Stream_Quad_V4F_N4F_C4B_T4B
// void (cDistributeEffect* effect, IVertexStream* stream, unsigned char* offsets)
// For every distribute sample they post-transform the sample transform by the effect transform and
// stream a camera-facing quad: V4F position (transform translation + the age fraction in .w), N4F
// normal (rotation row 2 + the scale in .w), C4B packed colour and a T2F/T4B texcoord holding the
// four quad corners.  Acquire() is vtable slot 0, Commit() slot 2.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE).
#include <xmmintrin.h>
#include "types.h"

namespace EA {
namespace Swarm {

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Matrix3 {
  Vector3 row[3];
  Matrix3() {}
  Matrix3(const Matrix3& m) { row[0] = m.row[0]; row[1] = m.row[1]; row[2] = m.row[2]; }
};

// 0x38 bytes: flags, modification count, translation, scale, rotation.
struct cTransform {
  uint16_t mFlags;      // +0x00
  uint16_t mModCount;   // +0x02
  Vector3  mOffset;     // +0x04
  float    mScale;      // +0x10
  Matrix3  mRotation;   // +0x14
  cTransform() {}
  cTransform(const cTransform& t)
      : mFlags(t.mFlags), mModCount(t.mModCount), mOffset(t.mOffset), mScale(t.mScale),
        mRotation(t.mRotation) {}
  void PostTransformBy(const cTransform& parent);   // 0x00a8a140
};

// 0x4c bytes: transform, colour, sample index.
struct cDistributeSample {
  cTransform mTransform;   // +0x00
  float      mColor[4];    // +0x38
  int        mIndex;       // +0x48
};

struct IVertexStream {
  virtual int  Acquire(int count, uint8_t** ppBuffer, int* pStride);   // slot 0
  virtual void Slot1();                                                // slot 1
  virtual void Commit();                                               // slot 2
};

struct cDistributeEffect {
  uint8_t             pad00[0x64];
  cTransform          mTransform;        // +0x64
  uint8_t             pad_a0[0xa8 - 0x9c];
  cDistributeSample*  mSamplesBegin;     // +0xa8
  cDistributeSample*  mSamplesEnd;       // +0xac
  uint8_t             pad_b0[0xd4 - 0xb0];
  int                 mDivisor;          // +0xd4
};

struct V4F { float x, y, z, w; };
struct T2F { float u, v; };

static __forceinline float Min(float a, float b)
{
  return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline float Max(float a, float b)
{
  return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

static __forceinline int FloatToInt(float v)
{
  return _mm_cvt_ss2si(_mm_set_ss(v));
}

// Min(Max(0, v) * 255, 255) as a byte.
static __forceinline uint8_t ColorToByte(float v)
{
  __m128 x = _mm_max_ss(_mm_set_ss(0.0f), _mm_set_ss(v));
  x = _mm_mul_ss(x, _mm_set_ss(255.0f));
  x = _mm_min_ss(x, _mm_set_ss(255.0f));
  return (uint8_t)_mm_cvt_ss2si(x);
}

static __forceinline void WriteVertex(uint8_t*& pPos, uint8_t*& pNrm, uint8_t*& pCol, uint8_t*& pTex,
                                      int stride, const cTransform& xf, float t, uint32_t color,
                                      const T2F& uv)
{
  V4F& v = *(V4F*)pPos;
  v.x = xf.mOffset.x;
  v.y = xf.mOffset.y;
  v.z = xf.mOffset.z;
  v.w = t;
  pPos += stride;

  V4F& nm = *(V4F*)pNrm;
  nm.x = xf.mRotation.row[2].x;
  nm.y = xf.mRotation.row[2].y;
  nm.z = xf.mRotation.row[2].z;
  nm.w = xf.mScale;
  pNrm += stride;

  *(uint32_t*)pCol = color;
  pCol += stride;

  *(T2F*)pTex = uv;
  pTex += stride;
}

static __forceinline void WriteVertex(uint8_t*& pPos, uint8_t*& pNrm, uint8_t*& pCol, uint8_t*& pTex,
                                      int stride, const cTransform& xf, float t, uint32_t color,
                                      uint32_t uv)
{
  V4F& v = *(V4F*)pPos;
  v.x = xf.mOffset.x;
  v.y = xf.mOffset.y;
  v.z = xf.mOffset.z;
  v.w = t;
  pPos += stride;

  V4F& nm = *(V4F*)pNrm;
  nm.x = xf.mRotation.row[2].x;
  nm.y = xf.mRotation.row[2].y;
  nm.z = xf.mRotation.row[2].z;
  nm.w = xf.mScale;
  pNrm += stride;

  *(uint32_t*)pCol = color;
  pCol += stride;

  *(uint32_t*)pTex = uv;
  pTex += stride;
}

// @ 0x00a8aec0
void Stream_Quad_V4F_N4F_C4B_T2F(cDistributeEffect* effect, IVertexStream* stream, uint8_t* offsets)
{
  int remaining = (int)(effect->mSamplesEnd - effect->mSamplesBegin);
  float inv = 1.0f / (float)effect->mDivisor;
  int sampleIndex = 0;

  T2F uv0; uv0.u = 0.0f; uv0.v = 0.0f;
  T2F uv1; uv1.u = 1.0f; uv1.v = 0.0f;
  T2F uv2; uv2.u = 1.0f; uv2.v = 1.0f;
  T2F uv3; uv3.u = 0.0f; uv3.v = 1.0f;

  while (remaining > 0) {
    uint8_t* buffer;
    int stride;
    int n = stream->Acquire(remaining, &buffer, &stride);

    uint8_t* pPos = buffer + offsets[0];
    uint8_t* pNrm = buffer + offsets[1];
    uint8_t* pCol = buffer + offsets[2];
    uint8_t* pTex = buffer + offsets[3];

    if (n > 0) {
      cDistributeSample* sample = effect->mSamplesBegin + sampleIndex;
      sampleIndex += n;
      for (int k = 0; k < n; ++k) {
        cTransform xf(sample->mTransform);
        xf.PostTransformBy(effect->mTransform);

        float t = ((float)sample->mIndex + 0.5f) * inv;

        uint8_t r = ColorToByte(sample->mColor[0]);
        uint8_t g = ColorToByte(sample->mColor[1]);
        uint8_t b = ColorToByte(sample->mColor[2]);
        uint8_t a = ColorToByte(sample->mColor[3]);
        uint32_t color = ((((uint32_t)a << 8 | r) << 8 | g) << 8) | b;

        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv0);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv1);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv2);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, uv3);
        ++sample;
      }
    }

    stream->Commit();
    remaining -= n;
  }
}

// @ 0x00a8b420
void Stream_Quad_V4F_N4F_C4B_T4B(cDistributeEffect* effect, IVertexStream* stream, uint8_t* offsets)
{
  int remaining = (int)(effect->mSamplesEnd - effect->mSamplesBegin);
  float inv = 1.0f / (float)effect->mDivisor;
  int sampleIndex = 0;

  while (remaining > 0) {
    uint8_t* buffer;
    int stride;
    int n = stream->Acquire(remaining, &buffer, &stride);

    uint8_t* pPos = buffer + offsets[0];
    uint8_t* pNrm = buffer + offsets[1];
    uint8_t* pCol = buffer + offsets[2];
    uint8_t* pTex = buffer + offsets[3];

    if (n > 0) {
      cDistributeSample* sample = effect->mSamplesBegin + sampleIndex;
      sampleIndex += n;
      for (int k = 0; k < n; ++k) {
        cTransform xf(sample->mTransform);
        xf.PostTransformBy(effect->mTransform);

        float t = ((float)sample->mIndex + 0.5f) * inv;

        uint8_t r = ColorToByte(sample->mColor[0]);
        uint8_t g = ColorToByte(sample->mColor[1]);
        uint8_t b = ColorToByte(sample->mColor[2]);
        uint8_t a = ColorToByte(sample->mColor[3]);
        uint32_t color = ((((uint32_t)a << 8 | r) << 8 | g) << 8) | b;

        int32_t frame = (int32_t)sample->mIndex * 0x41c64e6d + 0x3039;
        uint32_t corner = (uint32_t)(frame >> 24 & 0xff) | (uint32_t)(frame >> 16) << 24;

        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner | 0xff0000);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner | 0xffff00);
        WriteVertex(pPos, pNrm, pCol, pTex, stride, xf, t, color, corner | 0xff00);
        ++sample;
      }
    }

    stream->Commit();
    remaining -= n;
  }
}

}  // namespace Swarm
}  // namespace EA
