// slice s00a8b940 (batch gold3, slice 52): EA::Swarm distributed-mesh streaming.
//   0x00a8b940  Stream_Quad_V4F_N4F_G3F_C4B_T4B(cDistributeEffect*, IVertexStream*, uint8_t* offsets)
//   0x00a8bf10  RegisterMeshStreamers(bool)        installs the three streamer pointers
//   0x00a8bf60  vector<RefVertex>::reserve(unsigned)          (thiscall, ret 4)
//   0x00a8c070  uninitialized_copy<RefVertex>                 (free, cdecl)
//   0x00a8c0e0  cDistributeEffect::StreamModelParticles(IVertexStream*)  (thiscall, ret 4)
//   0x00a8c440  vector<RefVertex>::~vector()                  (thiscall)
//   0x00a8c480  vector<cDistributeSample>::vector(const vector&)  (thiscall, ret 4)
//   0x00a8c4e0  vector<RefPtr>::erase(first, last)             (thiscall, ret 8)
//   0x00a8c540  vector<RefVertex>::insert(position, const T&)  (thiscall, ret 8)
//   0x00a8c690  vector<RefPtr>::insert(position, n, const T&)  (thiscall, ret 0xc)
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE, no /EHsc).
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

// 0x38 bytes: flags, modification count, translation, uniform scale, rotation.
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
  cTransform          mTransform;        // +0x64 (ends at +0x9c)
  int                 mRenderCount;      // +0x9c
  uint8_t             pad_a0b[0xa8 - 0xa0];
  cDistributeSample*  mSamplesBegin;     // +0xa8
  cDistributeSample*  mSamplesEnd;       // +0xac
  uint8_t             pad_b0[0xd4 - 0xb0];
  int                 mDivisor;          // +0xd4
  uint8_t             pad_d8[0xf9 - 0xd8];
  uint8_t             mOffA;             // +0xf9  matrix stream byte offset
  uint8_t             mOffB;             // +0xfa  colour stream byte offset
  uint8_t             pad_fb[0x16c - 0xfb];
  float               mAlphaScale;       // +0x16c

  void StreamModelParticles(IVertexStream* stream);   // 0x00a8c0e0
};

struct V4F { float x, y, z, w; };
struct G3F { float x, y, z; };

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

// Min(Max(0, v) * 255, 255) rounded toward zero.
static __forceinline uint8_t ColorToByte(float v)
{
  __m128 x = _mm_max_ss(_mm_set_ss(0.0f), _mm_set_ss(v));
  x = _mm_mul_ss(x, _mm_set_ss(255.0f));
  x = _mm_min_ss(x, _mm_set_ss(255.0f));
  return (uint8_t)_mm_cvt_ss2si(x);
}

// One streamed quad corner: V4F position, N4F normal, G3F second normal,
// C4B packed colour and T4B packed texcoord.
static __forceinline void WriteVertex(uint8_t*& pPos, uint8_t*& pNrm, uint8_t*& pTan,
                                      uint8_t*& pCol, uint8_t*& pTex, int stride,
                                      const cTransform& xf, float t, uint32_t color, uint32_t uv)
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

  G3F& tn = *(G3F*)pTan;
  tn.x = xf.mRotation.row[0].x;
  tn.y = xf.mRotation.row[0].y;
  tn.z = xf.mRotation.row[0].z;
  pTan += stride;

  *(uint32_t*)pCol = color;
  pCol += stride;

  *(uint32_t*)pTex = uv;
  pTex += stride;
}

// ---- helpers implemented in other translation units -----------------------------
void* EAAllocate(unsigned size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
void* EANew(const char* tag, int align, unsigned size);                                    // 0x011e073e
void  OperatorDelete(void* p);                                                             // 0x00f47380
void* UninitCopyVec(void* out, void* first, void* last, void* dst, void* alloc);           // 0x00a89e40
void* VectorDoAllocate(void* self, unsigned n, void* alloc);                               // 0x00a89840
void* UninitCopyPtr(void* first, void* last, void* dst);                                   // 0x00a88250
void* MovePtr(void* first, void* last, void* dst);                                         // 0x00a882a0
void* MoveBackPtr(void* first, void* last, void* dstEnd);                                  // 0x00a882f0
void  UninitMovePtr(void* out, void* first, void* last, void* dst);                        // 0x00a898a0
void  CopyPtrAssign(void* first, void* last, void* value);                                 // 0x00a898f0
void  UninitFillPtr(void* dst, unsigned n, void* value);                                   // 0x00a89940
void* MemMove(void* dst, const void* src, unsigned n);                                     // 0x011e0744
void  FUN_00a8a450(cDistributeEffect* effect, IVertexStream* stream);                      // 0x00a8a450
void  FUN_00a8a8b0();                                                                      // 0x00a8a8b0
void  Stream_Quad_V4F_N4F_C4B_T2F(cDistributeEffect*, IVertexStream*, uint8_t*);           // 0x00a8aec0
void  Stream_Quad_V4F_N4F_C4B_T4B(cDistributeEffect*, IVertexStream*, uint8_t*);           // 0x00a8b420

static const char* const kEASTLFile = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char* const kEASTLTag  = "EASTL";

static inline void FreeBlock(void* p)
{
  if (p != 0 && ((int*)p)[-1] != 0)
    OperatorDelete(p);
}

// ================================================================================
// @ 0x00a8b940
// Streams a camera-facing quad per distribute sample: V4F position (translation
// plus the age fraction in .w), N4F normal (rotation row 2 plus the scale in .w),
// G3F (rotation row 0), C4B colour and a T4B texcoord holding the quad corner.
void Stream_Quad_V4F_N4F_G3F_C4B_T4B(cDistributeEffect* effect, IVertexStream* stream, uint8_t* offsets)
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
    uint8_t* pTan = buffer + offsets[2];
    uint8_t* pCol = buffer + offsets[3];
    uint8_t* pTex = buffer + offsets[4];

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

        int32_t seed = (int32_t)((uint32_t)sample->mIndex * 0x41c64e6d + 0x3039);
        int32_t rnd = seed >> 16;
        uint32_t corner = (uint32_t)(rnd << 24) | ((uint32_t)(rnd >> 8) & 0xff);

        WriteVertex(pPos, pNrm, pTan, pCol, pTex, stride, xf, t, color, corner);
        WriteVertex(pPos, pNrm, pTan, pCol, pTex, stride, xf, t, color, corner | 0xff0000);
        WriteVertex(pPos, pNrm, pTan, pCol, pTex, stride, xf, t, color, corner | 0xffff00);
        WriteVertex(pPos, pNrm, pTan, pCol, pTex, stride, xf, t, color, corner | 0xff00);
        ++sample;
      }
    }

    stream->Commit();
    remaining -= n;
  }
}

// ================================================================================
// @ 0x00a8bf10  installs the streamer table (0x80-byte block at 0x016781b0).
void RegisterMeshStreamers(bool install)
{
  if (install) {
    EANew((const char*)0x016781b0, 0, 0x80);
    *(void**)0x016781b0 = (void*)&FUN_00a8a8b0;
    *(void**)0x016781b8 = (void*)&Stream_Quad_V4F_N4F_C4B_T2F;
    *(void**)0x016781bc = (void*)&Stream_Quad_V4F_N4F_C4B_T4B;
    *(void**)0x016781c0 = (void*)&Stream_Quad_V4F_N4F_G3F_C4B_T4B;
  }
}

// ================================================================================
// Ref-counted object pointer: releases through vtable slot 1 / 0.
struct RefCounted {
  virtual void AddRef();    // +0x34 slot used by move
  virtual void Release();   // +0x38 slot used by move
};

// 0x18-byte streamed vertex: a referenced vertex buffer plus its parameter.
struct RefVertex {
  void*    mp;        // +0x00  referenced object
  uint32_t mPad[5];   // +0x04  vertex parameter block
};

// eastl vector<T> with the sp_vector_allocator (0x14 bytes).
template <class T>
struct SpVector {
  T*       mpBegin;        // +0x00
  T*       mpEnd;          // +0x04
  T*       mpCapacity;     // +0x08
  uint32_t mAllocator[2];  // +0x0c

  unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
  void reserve(unsigned n);                       // 0x00a8bf60
  void insert(T* position, const T& value);       // 0x00a8c540
  ~SpVector();                                    // 0x00a8c440
};

// @ 0x00a8bf60
template <class T>
void SpVector<T>::reserve(unsigned n)
{
  if (size() < n) {
    T* pNew = 0;
    if (n)
      pNew = (T*)EAAllocate(n * sizeof(T), kEASTLTag, 0, 0, kEASTLFile, 0xd1);
    UninitCopyPtr(mpBegin, mpEnd, pNew);
    FreeBlock(mpBegin);
    unsigned nOld = size();
    mpBegin = pNew;
    mpEnd = pNew + nOld;
    mpCapacity = pNew + n;
  }
}

// ================================================================================
// @ 0x00a8c070  uninitialized copy of 0x18-byte ref-counted vertices.
RefVertex* UninitCopyVertex(RefVertex* first, RefVertex* last, RefVertex* dst)
{
  if (first == last)
    return dst;
  do {
    void* nv = first->mp;
    void* ov = dst->mp;
    if (nv != ov) {
      if (nv)
        ((RefCounted*)nv)->AddRef();
      dst->mp = nv;
      if (ov)
        ((RefCounted*)ov)->Release();
    }
    dst->mPad[0] = first->mPad[0];
    dst->mPad[1] = first->mPad[1];
    dst->mPad[2] = first->mPad[2];
    dst->mPad[3] = first->mPad[3];
    dst->mPad[4] = first->mPad[4];
    ++first;
    ++dst;
  } while (first != last);
  return dst;
}

// ================================================================================
// @ 0x00a8c0e0
__declspec(noinline) void cDistributeEffect::StreamModelParticles(IVertexStream* stream)
{
  if ((*(uint32_t*)((uint8_t*)this + 0x14) >> 0xe) & 1) {
    FUN_00a8a450(this, stream);
    return;
  }

  int remaining = (int)(mSamplesEnd - mSamplesBegin);
  int sampleIndex = 0;

  while (remaining > 0) {
    uint8_t* buffer;
    int stride;
    int n = stream->Acquire(remaining, &buffer, &stride);
    remaining -= n;

    if (n > 0) {
      cDistributeSample* sample = mSamplesBegin + sampleIndex;
      sampleIndex += n;

      uint8_t* pMat = buffer + mOffA;
      uint8_t* pCol = buffer + mOffB;

      for (int k = 0; k < n; ++k) {
        cTransform xf(sample->mTransform);
        xf.PostTransformBy(mTransform);

        float s = xf.mScale;
        float* m = (float*)pMat;
        for (int r = 0; r < 3; ++r) {
          m[0] = xf.mRotation.row[r].x * s;
          m[1] = xf.mRotation.row[r].y * s;
          m[2] = xf.mRotation.row[r].z * s;
          m += 4;
        }
        m[0] = xf.mOffset.x;
        m[1] = xf.mOffset.y;
        m[2] = xf.mOffset.z;
        pMat += stride;

        float* c = (float*)pCol;
        c[0] = sample->mColor[0];
        c[1] = sample->mColor[1];
        c[2] = sample->mColor[2];
        c[3] = sample->mColor[3] * mAlphaScale;
        pCol += stride;

        ++sample;
      }
    }

    stream->Commit();
  }
  ++mRenderCount;
}

// ================================================================================
// @ 0x00a8c440  releases every referenced vertex then frees the block.
template <class T>
SpVector<T>::~SpVector()
{
  T* p = mpBegin;
  T* end = mpEnd;
  if (p < end) {
    do {
      void* obj = ((RefVertex*)p)->mp;
      if (obj)
        ((RefCounted*)obj)->Release();
      p = (T*)((uint8_t*)p + sizeof(T));
    } while (p < end);
  }
  FreeBlock(mpBegin);
}

// ================================================================================
// vector<cDistributeSample> (0x4c-byte elements) copy constructor.
struct SampleVector {
  cDistributeSample* mpBegin;      // +0x00
  cDistributeSample* mpEnd;        // +0x04
  cDistributeSample* mpCapacity;   // +0x08
  uint32_t           mAllocator[2];// +0x0c

  SampleVector(const SampleVector& src);   // 0x00a8c480
};

// @ 0x00a8c480
SampleVector::SampleVector(const SampleVector& src)
{
  VectorDoAllocate(this, (unsigned)(src.mpEnd - src.mpBegin), (void*)&src.mAllocator[0]);
  UninitCopyVec(&mpEnd, src.mpBegin, src.mpEnd, mpBegin, (void*)&src.mAllocator[0]);
}

// ================================================================================
// vector<RefPtr> (4-byte reference-counted pointers) helpers.
struct RefPtr {
  void* mp;   // +0x00
};

struct PtrVector {
  RefPtr*  mpBegin;        // +0x00
  RefPtr*  mpEnd;          // +0x04
  RefPtr*  mpCapacity;     // +0x08
  uint32_t mAllocator[2];  // +0x0c

  RefPtr* erase(RefPtr* first, RefPtr* last);                   // 0x00a8c4e0
  void    insert(RefPtr* position, unsigned n, const RefPtr& v); // 0x00a8c690
};

// @ 0x00a8c4e0
RefPtr* PtrVector::erase(RefPtr* first, RefPtr* last)
{
  RefPtr* p = (RefPtr*)MovePtr(first, mpEnd, last);
  RefPtr* end = mpEnd;
  while (p < end) {
    if (p->mp)
      ((RefCounted*)p->mp)->Release();
    ++p;
  }
  mpEnd -= (last - first);
  return first;
}

// @ 0x00a8c690
void PtrVector::insert(RefPtr* position, unsigned n, const RefPtr& value)
{
  unsigned nCapacity = (unsigned)(mpCapacity - mpEnd);
  if (n > nCapacity) {
    unsigned nPrev = (unsigned)(mpEnd - mpBegin);
    unsigned nGrow = (nPrev > 0) ? nPrev * 2 : 1;
    unsigned nNew = (nPrev + n > nGrow) ? (nPrev + n) : nGrow;
    RefPtr* pNew = nNew ? (RefPtr*)EAAllocate(nNew * sizeof(RefPtr), kEASTLTag, 0, 0, kEASTLFile, 0xd1) : 0;
    unsigned nPre = (unsigned)(position - mpBegin);
    unsigned nPost = (unsigned)(mpEnd - position);
    RefPtr* p = (RefPtr*)MemMove(pNew, mpBegin, nPre * sizeof(RefPtr));
    p = (RefPtr*)((uint8_t*)p + nPre * sizeof(RefPtr));
    UninitFillPtr(p, n, (void*)&value);
    RefPtr* pEnd = (RefPtr*)((uint8_t*)p + n * sizeof(RefPtr));
    MemMove(pEnd, position, nPost * sizeof(RefPtr));
    FreeBlock(mpBegin);
    mpBegin = pNew;
    mpEnd = (RefPtr*)((uint8_t*)pEnd + nPost * sizeof(RefPtr));
    mpCapacity = pNew + nNew;
    return;
  }

  if (n == 0)
    return;

  void* obj = value.mp;
  if (obj)
    ((RefCounted*)obj)->AddRef();

  unsigned nExtra = (unsigned)(mpEnd - position);
  if (n < nExtra) {
    RefPtr* newEnd = mpEnd + n;
    UninitMovePtr(&newEnd, mpEnd - n, mpEnd, mpEnd);
    mpEnd += n;
    MoveBackPtr(position, mpEnd - n, newEnd);
    CopyPtrAssign(position, position + n, (void*)&value);
  } else {
    UninitFillPtr(mpEnd, n - nExtra, (void*)&value);
    mpEnd += n - nExtra;
    UninitMovePtr(&mpEnd, position, mpEnd - (n - nExtra), mpEnd);
    mpEnd += nExtra;
    CopyPtrAssign(position, mpEnd - nExtra, (void*)&value);
  }

  if (obj)
    ((RefCounted*)obj)->Release();
}

// ================================================================================
// @ 0x00a8c540
template <class T>
void SpVector<T>::insert(T* position, const T& value)
{
  if (mpEnd != mpCapacity) {
    T* src = (T*)&value;
    if (src >= position && src < mpEnd)
      src = (T*)((uint8_t*)src + sizeof(T));
    if (mpEnd) {
      T* e = mpEnd;
      e->mp = mpEnd[-1].mp;
      e->mPad[0] = mpEnd[-1].mPad[0];
      e->mPad[1] = mpEnd[-1].mPad[1];
      e->mPad[2] = mpEnd[-1].mPad[2];
      e->mPad[3] = mpEnd[-1].mPad[3];
      e->mPad[4] = mpEnd[-1].mPad[4];
    }
    MemMove(position + 1, position, (uint8_t*)(mpEnd - 1) - (uint8_t*)position);
    position->mp = src->mp;
    position->mPad[0] = src->mPad[0];
    position->mPad[1] = src->mPad[1];
    position->mPad[2] = src->mPad[2];
    position->mPad[3] = src->mPad[3];
    position->mPad[4] = src->mPad[4];
    mpEnd += 1;
    return;
  }

  unsigned nPrev = size();
  unsigned nNew = (nPrev > 0) ? nPrev * 2 : 1;
  T* pNew = (T*)EAAllocate(nNew * sizeof(T), kEASTLTag, 0, 0, kEASTLFile, 0xd1);
  T* p = UninitCopyVertex((RefVertex*)mpBegin, (RefVertex*)position, (RefVertex*)pNew);
  if (p) {
    p->mp = value.mp;
    p->mPad[0] = value.mPad[0];
    p->mPad[1] = value.mPad[1];
    p->mPad[2] = value.mPad[2];
    p->mPad[3] = value.mPad[3];
    p->mPad[4] = value.mPad[4];
    p = (T*)((uint8_t*)p + sizeof(T));
  }
  T* pEnd = UninitCopyVertex((RefVertex*)position, (RefVertex*)mpEnd, (RefVertex*)p);
  FreeBlock(mpBegin);
  mpBegin = pNew;
  mpEnd = pEnd;
  mpCapacity = pNew + nNew;
}

template struct SpVector<RefVertex>;

}  // namespace Swarm
}  // namespace EA
