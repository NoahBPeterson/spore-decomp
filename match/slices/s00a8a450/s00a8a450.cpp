// slice s00a8a450: EA::Swarm::Stream_Quad_V3F_C4B_T2F (0x00a8a450).
// For every sample of every instance of a distribute effect this writes a 4x3 scaled
// transform matrix (three rotation rows times the transform scale, then the translation)
// into the acquired vertex stream at byte offset +0xf9, and an RGBA record (the sample
// colour with its alpha scaled by +0x17c) at byte offset +0xfa.  The sample transform is
// post-transformed by the effect transform at +0x64.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE).
#include "types.h"

// ---------------------------------------------------------------- math
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

// one output row of the streamed matrix (three used floats + one unwritten pad).
struct OutRow {
  Vector3 v;
  float   w;
};

struct cDistributeEffect {
  uint8_t             pad00[0x64];
  cTransform          mTransform;        // +0x64
  int                 mRenderCount;      // +0x9c
  uint8_t             pad_a0[0x8];
  cDistributeSample*  mSamplesBegin;     // +0xa8
  cDistributeSample*  mSamplesEnd;       // +0xac
  uint8_t             pad_b0[0x28];
  cDistributeEffect** mInstancesBegin;   // +0xd8
  cDistributeEffect** mInstancesEnd;     // +0xdc
  uint8_t             pad_e0[0x19];
  uint8_t             mPosOffset;        // +0xf9
  uint8_t             mColorOffset;      // +0xfa
  uint8_t             pad_fb[0x17c - 0xfb];
  float               mAlphaScale;       // +0x17c

  void Stream_Quad_V3F_C4B_T2F(struct IVertexStream* stream);
};

struct IVertexStream {
  virtual int  Acquire(int count, uint8_t** ppBuffer, int* pStride);   // slot 0
  virtual void Commit();                                               // slot 1
};

// @ 0x00a8a450
void cDistributeEffect::Stream_Quad_V3F_C4B_T2F(IVertexStream* stream)
{
  int instanceCount = (int)(mInstancesEnd - mInstancesBegin);

  int total = 0;
  for (int i = 0; i < instanceCount; ++i)
    total += (int)(mInstancesBegin[i]->mSamplesEnd - mInstancesBegin[i]->mSamplesBegin);

  int remaining = total;
  int groupIndex = 0;
  int groupRemaining = 0;
  cDistributeSample* sample;
  uint8_t* buffer;
  int stride;

  while (remaining > 0) {
    int n = stream->Acquire(remaining, &buffer, &stride);
    remaining -= n;
    if (n <= 0) {
      stream->Commit();
      continue;
    }

    while (true) {
      if (groupRemaining == 0) {
        do {
          cDistributeEffect* p = mInstancesBegin[groupIndex++];
          sample = p->mSamplesBegin;
          groupRemaining = (int)(p->mSamplesEnd - sample);
        } while (groupRemaining == 0);
      }

      int take = (n < groupRemaining) ? n : groupRemaining;
      groupRemaining -= take;
      if (take <= 0)
        continue;

      for (int k = 0; k < take; ++k) {
        cTransform xf(sample->mTransform);
        xf.PostTransformBy(mTransform);

        OutRow* d = (OutRow*)(buffer + mPosOffset);
        d[0].v = Vector3(xf.mRotation.row[0].x * xf.mScale,
                         xf.mRotation.row[0].y * xf.mScale,
                         xf.mRotation.row[0].z * xf.mScale);
        d[1].v = Vector3(xf.mRotation.row[1].x * xf.mScale,
                         xf.mRotation.row[1].y * xf.mScale,
                         xf.mRotation.row[1].z * xf.mScale);
        d[2].v = Vector3(xf.mRotation.row[2].x * xf.mScale,
                         xf.mRotation.row[2].y * xf.mScale,
                         xf.mRotation.row[2].z * xf.mScale);
        d[3].v = xf.mOffset;

        OutRow* e = (OutRow*)(buffer + mColorOffset);
        e->v = Vector3(sample->mColor[0], sample->mColor[1], sample->mColor[2]);
        e->w = sample->mColor[3] * mAlphaScale;

        ++sample;
        buffer += stride;
      }
    }
  }

  ++mRenderCount;
}
