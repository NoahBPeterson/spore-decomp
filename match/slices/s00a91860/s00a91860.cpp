// slice s00a91860 (batch gold3, slice 53): EA::Swarm::cDistributeEffect state / render handling.
//   0x00a91860  cDistributeEffect::PinSamplesToSurface(sampleBegin, sampleEnd)
//   0x00a91bc0  cDistributeEffect::CreateRenderSet()  (FUN_00a91bc0)
//   0x00a91e40  cDistributeEffect::Start()            (FUN_00a91e40)
//   0x00a921c0  cDistributeEffect::Shutdown()
//   0x00a92310  cDistributeEffect::Start(renderSet)    (FUN_00a92310)
//   0x00a92360  cDistributeEffect::Stop(renderSet)     (FUN_00a92360)
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (scalar SSE, no /EHsc).
#include "types.h"

namespace EA {
namespace Swarm {

void BitVecDoInsert(void* begin, void* end, int value);      // 0x011e0744

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

// A reference-counted object; slot 0 releases, slot 1 frees.
struct RefObj {
  virtual void Release();              // +0
  virtual void Free();                 // +4
};

struct cSurfaceInfo {
  uint32_t mFlags[2];                  // +0x00
  float    mPinOffset;                 // +0x08
};

struct cSurface {
  virtual void sv0();
  virtual void sv1();
  virtual void sv2();
  virtual void sv3();
  // Returns non-zero when the sample position/orientation were written.
  virtual bool SampleSurface(float* orient, float* pos, float* tangent, void* state,
                             void* particles);                                    // +0x10
};

struct cSurfaceRec {
  cSurface*     mSurface;              // +0x00
  cSurfaceInfo* mSurfaceInfo;          // +0x04
  int           mNumStateBytes;        // +0x08
  int           mStateDataOffset;      // +0x0c
  int           mNumParticleBytes;     // +0x10
  int           mParticleDataOffset;   // +0x14
};

// Element of the effect's dynamic byte vector (large effect-owned buffer).
struct EffectBuffer {
  uint8_t* mpBegin;                    // +0x00
  uint8_t* mpEnd;                      // +0x04
  uint8_t* mpCapacity;                 // +0x08
};

struct RefPtrVec {
  void**   mpBegin;                    // +0x00
  void**   mpEnd;                      // +0x04
  void**   mpCapacity;                 // +0x08
  uint32_t mAlloc[2];                  // +0x0c

  int size() const { return (int)(mpEnd - mpBegin); }
  void** begin() { return mpBegin; }
  void** end() { return mpEnd; }
};

struct SampleVec {
  uint8_t* mpBegin;                    // +0x00
  uint8_t* mpEnd;                      // +0x04
  uint8_t* mpCapacity;                 // +0x08
};

struct SurfaceRecVec {
  cSurfaceRec* mpBegin;                // +0x00
  cSurfaceRec* mpEnd;                  // +0x04
  cSurfaceRec* mpCapacity;             // +0x08
  void erase(cSurfaceRec* first, cSurfaceRec* last);   // 0x00a8d020
};

// Renderer / render-set interfaces (only the slots this slice calls).
struct EffectVt {
  virtual void e0(); virtual void e1(); virtual void e2();
  virtual void e3(int v);              // +0x0c  (slot 3, one int argument)
};

// A released child object: slot 3 is the release, slot 1 the free.
struct ChildObj {
  virtual void v0();                   // +0x00
  virtual void v1();                   // +0x04
  virtual void v2();                   // +0x08
  virtual void v3();                   // +0x0c
};

// A live effect object released on shutdown: slot 1.
struct SampleObj {
  virtual void v0();                   // +0x00
  virtual void v1();                   // +0x04
};

// A dynamic bool/byte vector cleared on shutdown (erase(begin,end)).
struct BitVec {
  void* mpBegin;                       // +0x00
  void* mpEnd;                         // +0x04
  void* mpCapacity;                    // +0x08
  void* mAlloc[2];                     // +0x0c
  void erase(void* first, void* last)
  {
    BitVecDoInsert(mpBegin, mpEnd, 0);
    mpEnd = (void*)((int)mpEnd + ((int)first - (int)last));
  }
};
struct cRenderTarget {
  virtual void t0();
  virtual void t1();
  virtual void t2();
  virtual void t3();
  virtual void t4();
  virtual void t5();
};

struct cRenderSet {
  virtual void rs0();
  virtual void rs1();
  virtual void rs2();
  virtual void rs3();
  virtual void rs4();
  virtual void rs5();
  virtual void rs6();
  virtual void rs7(int arg);      // +0x1c
  virtual void rs8();
  virtual void rs9();
  virtual void rs10();
  virtual void rs11();
  virtual void rs12(int arg);     // +0x30
  virtual void rs13();
};

struct cRenderer {
  virtual void rv0();
  virtual void rv1();
  virtual void rv2();
  virtual void rv3();
  virtual void rv4();
  virtual void rv5();
  virtual void rv6();
  virtual void rv7();
  virtual cRenderSet*   GetRenderSet();       // +0x20
  virtual cRenderer*    GetById(int id);      // +0x24
  virtual cRenderTarget* GetTarget();         // +0x30
};

// A sample is 0x4c bytes: transform (0x38) + colour/scale (0x10) + index (0x4).
struct cDistributeSample {
  uint8_t mTransform[0x38];
  float   mColor[4];                   // +0x38
  int     mIndex;                      // +0x48
};

// cDistributeEffect, offset-addressed view (the original field names are not
// recovered; the offsets below are what the disassembly touches).
struct cDistributeEffect {
  uint8_t p[0x180];

  template <class T> T&    at(unsigned off) { return *(T*)(p + off); }
  template <class T> T     at(unsigned off) const { return *(const T*)(p + off); }

  uint32_t flags() const { return at<uint32_t>(0x28); }
  void     setFlags(uint32_t v) { at<uint32_t>(0x28) = v; }

  RefPtrVec&    effects()   { return at<RefPtrVec>(0xd8); }
  SampleVec&    samples()   { return at<SampleVec>(0xa8); }
  SurfaceRecVec& surfaceRecs() { return at<SurfaceRecVec>(0x11c); }

  void PinSamplesToSurface(int first, int last);
  void CreateRenderSet();
  void Start(void* a, void* b, int* counts);
  void Shutdown();
  void Start(int renderSet);
  void Stop(int renderSet);
};

// ---- external helpers from other translation units -------------------------------
void  eraseRange_RefPtr(void** first, void** last);           // 0x00a8c4e0
void  VectorCopySamples(void* dst, void* srcEnd, void* src);// eastl::copy_impl (0x00a8c9xx)
void  FUN_00a8d350(int v);                                    // 0x00a8d350
void  Memset(void* dst, int value, unsigned n);               // 0x004c10e0
void  ResizeArray(void* vec, int newSize, uint8_t* value);    // 0x004c10e0
void* EAAllocate(unsigned size, const char* tag, int a, int b, const char* file, int line);
void  EraseSurfaceRecs(void* begin, void* end);               // 0x00a8d020
void  ClearBitVector(void* begin, int end, void* endField);   // bit-vector erase (0x11e0744)

// Child parameter block stored at +0x24; has its own destructor and is heap-owned.
struct cEffectParams {
  uint8_t m[0x4c];
  ~cEffectParams();
};
void operator_delete(void* p);                                // ??3@YAXPAX@Z

}  // namespace Swarm
}  // namespace EA

using namespace EA::Swarm;

static const uint32_t kSurfaceMask = 0;

// ================================================================================
// @ 0x00a91860
// Pins samples [first,last) of the effect's sample array onto the first surface
// record whose info flags intersect the global surface mask.
void cDistributeEffect::PinSamplesToSurface(int first, int last)
{
  cSurfaceRec* rec = this->surfaceRecs().mpBegin;
  cSurfaceRec* end = this->surfaceRecs().mpEnd;
  {
    uint32_t mask = *(uint32_t*)0x01565030;
    while (rec != end && ((rec->mSurfaceInfo->mFlags[0] & mask) == 0))
      ++rec;
  }

  // Grow / shrink the dynamic particle-data buffer to numSamples * recSize.
  uint32_t filled = this->at<uint32_t>(0xf0) - (uint32_t)this->at<int>(0x144);
  uint32_t want = (uint32_t)((this->at<uint8_t*>(0xc0) - this->at<uint8_t*>(0xbc)) / 0x4c) *
                  (uint32_t)this->at<int>(0x158);
  if (want <= filled) {
    if (filled != want) {
      uint8_t zero = 0;
      ResizeArray(this->at<void*>(0x148), (int)(filled - want), &zero);
    }
  } else {
    uint8_t zero = 0;
    Memset(this->at<void*>(0xf0), 0, 0);
    ResizeArray(&this->at<uint32_t>(0xf0), (int)(want - filled), &zero);
  }

  if (rec == end)
    return;

  uint32_t pinToOffset = (this->at<int>(0x14) ? 0u : 0u);  // mFlags>>0xf & 1, see below
  pinToOffset = ((*(uint32_t*)(unsigned)this->at<int>(0x14)) >> 0xf) & 1;

  uint8_t* state = 0;
  if (rec->mNumStateBytes != 0)
    state = (uint8_t*)(unsigned)this->at<int>(0x130) + rec->mStateDataOffset;

  int base = this->at<int>(0x144);
  for (int i = first; i < last; ++i) {
    int parts = 0;
    if (rec->mNumParticleBytes != 0)
      parts = base + i * this->at<int>(0x158) + rec->mParticleDataOffset;

    cDistributeSample* sample = this->at<cDistributeSample*>(0xbc) + i;
    float* orient = sample->mColor;

    float pos[3], tangent[3], normal[3];
    if (rec->mSurface->SampleSurface(orient, pos, tangent, state, (void*)(int)parts)) {
      float off = rec->mSurfaceInfo->mPinOffset;
      (void)pinToOffset;

      float px = pos[0] + tangent[0] * off;
      float py = pos[1] + tangent[1] * off;
      float pz = pos[2] + tangent[2] * off;

      float nx = normal[0], ny = normal[1], nz = normal[2];
      float xx = nx * nx, xy = nx * ny, xz = nx * nz;
      float yy = ny * ny, yz = ny * nz, zz = nz * nz;

      float* m = orient + 1;
      m[0] = 1.0f - (yy + zz) * 2.0f;
      m[1] = (xy + nz) * 2.0f;
      m[2] = (xz - ny) * 2.0f;
      m[3] = (xy - nz) * 2.0f;
      m[4] = 1.0f - (xx + zz) * 2.0f;
      m[5] = (yz + nx) * 2.0f;
      m[6] = (xz + ny) * 2.0f;
      m[7] = (yz - nx) * 2.0f;
      m[8] = 1.0f - (xx + yy) * 2.0f;

      *(uint16_t*)((uint8_t*)sample + 0x30) |= 2;
      *(float*)((uint8_t*)sample + 0x3c) = px;
      *(float*)((uint8_t*)sample + 0x40) = py;
      *(float*)((uint8_t*)sample + 0x44) = pz;
      *(uint16_t*)((uint8_t*)sample + 0x30) |= 4;
    }
  }
}

// ================================================================================
// @ 0x00a91bc0
// Creates (or re-creates) the render set for the effect and copies the current
// state snapshot into the renderer.
void cDistributeEffect::CreateRenderSet()
{
  if ((this->flags() >> 0xb & 1) != 0) {
    this->at<int>(0xd4) = *(int*)(unsigned)(this->at<int>(0x14) + 0xc);
    return;
  }

  int desc = this->at<int>(0x14);
  uint32_t descFlags = *(uint32_t*)(unsigned)(desc + 8);

  if ((descFlags >> 0xe & 1) != 0) {
    cRenderTarget* tgt = this->at<cRenderer*>(0x1c)->GetTarget();
    (void)tgt;
    *(int*)(unsigned)this->at<int>(0x18) =
        *(int*)(unsigned)(desc + 0x10);
    (void)tgt;
  }

  if ((descFlags & 0x100) == 0)
    this->setFlags(this->flags() & ~0x4000u);
  else
    this->setFlags(this->flags() | 0x4000u);

  // Snapshot 8 dwords of [desc+0x138] and merge with the effect buffer range.
  uint32_t snap[8];
  for (int i = 0; i < 8; ++i)
    snap[i] = *(uint32_t*)(unsigned)(desc + 0x138 + i * 4);

  uint32_t lo = this->at<uint32_t>(0xf0);
  uint32_t hi = this->at<uint32_t>(0xf4);

  if ((lo & hi) == 0xffffffffu) {
    if (snap[0] == 0 && snap[1] == 0)
      goto done;
  } else if ((descFlags & 0x100) == 0 && (uint8_t)(snap[2] >> 8) == 0x0f &&
             ((snap[6] & snap[7]) != 0xffffffffu)) {
    snap[6] = lo;
    snap[7] = hi;
    if (lo == 0 && hi == 0)
      goto done;
  } else {
    snap[0] = lo;
    snap[1] = hi;
    if (lo == 0 && hi == 0)
      goto done;
  }

  {
    cRenderTarget* target = this->at<cRenderer*>(0x1c)->GetTarget();
    cRenderTarget* rt = target;
    (void)rt;

    if ((this->flags() & 1) && (this->flags() >> 1 & 1) && this->at<int>(0xd4) > 0 &&
        this->at<int>(0xd4) == this->at<int>(0xd0))
      this->at<int>(0xec) = this->at<int>(0xec);  // renderer slot invoked below

    this->at<uint8_t>(0xf8) = (uint8_t)snap[0];
    *(uint32_t*)(unsigned)this->at<int>(0x14) = this->at<uint32_t>(0xf8);
    this->at<int>(0xd4) = *(int*)(unsigned)(this->at<int>(0x14) + 0xc);
  }

done:
  if (this->at<int>(0xec) < 0) {
    this->at<int>(0xd4) = 0;
    FUN_00a8d350(0);
    uint8_t* b = this->samples().mpBegin;
    SampleVec& sv = this->samples();
    VectorCopySamples(sv.mpEnd, sv.mpEnd, b);
    sv.mpEnd += (int)((sv.mpEnd - b)) / 0x4c * 0x4c;
  }
}

// ================================================================================
// @ 0x00a91e40
// Advances every child effect in the list, then (if the render flag is set)
// disposes and rebuilds the render set, computing the bounding box and scale of
// everything that will be drawn.
void cDistributeEffect::Start(void* a, void* b, int* counts)
{
  this->setFlags(this->flags() | 0x1000u);

  RefPtrVec& fx = this->effects();
  int n = fx.size();
  for (int i = 0; i < n; ++i) {
    int* child = (int*)fx.mpBegin[i];
    if (child[0x34] != child[0x35]) {
      ((void (*)(int*, void*, void*, int))*(void**)(*child + 0x14))(child, a, b, 0);
      (void)counts;
      if (child[0x34] != child[0x35])
        this->setFlags(this->flags() & ~0x1000u);
    }
  }

  if (this->flags() >> 0xc & 1) {
    if (this->at<int>(0xec) >= 0) {
      cRenderTarget* rt = this->at<cRenderer*>(0x1c)->GetTarget();
      if ((this->flags() >> 0xe & 1) == 0)
        rt->t2();          // slot 0x1c
      else
        rt->t5();          // slot 0x30
      (void)rt;
      this->at<int>(0xec) = -1;
    }

    CreateRenderSet();

    if (this->at<int>(0xec) >= 0) {
      float fMin = *(float*)0x01565020;
      float fMax = fMin;
      float loX = fMax, hiX = -fMin;
      float loY = fMax, hiY = -fMin;
      float loZ = fMax, hiZ = -fMin;
      float maxW = 0.0f;

      int m = fx.size();
      for (int i = 0; i < m; ++i) {
        uint8_t* child = (uint8_t*)this->effects().mpBegin[i];
        int cBegin = *(int*)(child + 0xa8);
        int cEnd = *(int*)(child + 0xac);
        int cN = (cEnd - cBegin) / 0x4c;
        float s0 = this->at<float>(0xbc + 0x38);
        (void)s0;
        for (int j = 0; j < cN; ++j) {
          float* v = (float*)(unsigned)(cBegin + j * 0x4c + 0xc);
          if (v[-2] < loX) loX = v[-2];
          if (hiX < v[-2]) hiX = v[-2];
          if (v[-1] < loY) loY = v[-1];
          if (hiY < v[-1]) hiY = v[-1];
          if (v[0] < loZ) loZ = v[0];
          if (hiZ < v[0]) hiZ = v[0];
          if (v[1] > maxW) maxW = v[1];
        }
      }

      cRenderTarget* rt = this->at<cRenderer*>(0x1c)->GetTarget();
      if ((this->flags() >> 0xe & 1) == 0) {
        if (loX != fMax) {
          rt->t0();
          rt->t1();
        }
      } else if (loX != fMax) {
        rt->t4();
        rt->t5();
      }
      (void)rt;
    }
  }

  counts[2] += fx.size();
}

// ================================================================================
// @ 0x00a921c0
// Shutdown(): stops the effect (vtable slot 3 with 1), releases the three child
// objects at +0x15c/+0x160/+0x164, deletes the child params at +0x24, releases the
// live effect objects at +0xd8 and then clears every dynamic vector.
void cDistributeEffect::Shutdown()
{
  ((EffectVt*)this)->e3(1);

  ChildObj* p0 = this->at<ChildObj*>(0x15c);
  if (p0) {
    p0->v3();
    p0 = this->at<ChildObj*>(0x15c);
    if (p0) {
      this->at<ChildObj*>(0x15c) = 0;
      p0->v1();
    }
  }
  ChildObj* p1 = this->at<ChildObj*>(0x160);
  if (p1) {
    p1->v3();
    p1 = this->at<ChildObj*>(0x160);
    if (p1) {
      this->at<ChildObj*>(0x160) = 0;
      p1->v1();
    }
  }
  ChildObj* p2 = this->at<ChildObj*>(0x164);
  if (p2) {
    p2->v3();
    p2 = this->at<ChildObj*>(0x164);
    if (p2) {
      this->at<ChildObj*>(0x164) = 0;
      p2->v1();
    }
  }

  cEffectParams* cp = this->at<cEffectParams*>(0x24);
  if (cp) {
    cp->~cEffectParams();
    operator_delete(cp);
    this->at<cEffectParams*>(0x24) = 0;
  }

  if (((uint8_t*)(unsigned)this->at<int>(0x14))[0x14] >= 1) {
    int n = (int)((this->at<int>(0xdc) - this->at<int>(0xd8)) >> 2);
    for (int i = 0; i < n; ++i) {
      SampleObj* o = ((SampleObj**)this->at<int>(0xd8))[i];
      o->v1();
    }
  }

  eraseRange_RefPtr((void**)this->at<int>(0xd8), (void**)this->at<int>(0xdc));
  {
    SurfaceRecVec* sv = &this->surfaceRecs();
    sv->erase(sv->mpBegin, sv->mpEnd);
  }
  BitVec& b0 = this->at<BitVec>(0x130);
  b0.erase(b0.mpBegin, b0.mpEnd);
  BitVec& b1 = this->at<BitVec>(0x144);
  b1.erase(b1.mpBegin, b1.mpEnd);
}

// ================================================================================
// @ 0x00a92310
void cDistributeEffect::Start(int renderSet)
{
  if (!(this->at<uint8_t>(0x28) & 1)) {
    this->at<uint32_t>(0x28) |= 1;
    uint32_t f = this->at<uint32_t>(0x28);
    if ((uint8_t)(f >> 0xd) & 1) {
      CreateRenderSet();
      return;
    }
    if (((uint8_t)(f >> 2) & 1) || *(int*)(this->at<int>(0x14) + 0x15c) != 0)
      this->at<int>(0xd4) = *(int*)(this->at<int>(0x14) + 0xc);
  }
}

// ================================================================================
// @ 0x00a92360
void cDistributeEffect::Stop(int renderSet)
{
  if (!(this->at<uint8_t>(0x28) & 1))
    return;
  this->setFlags(this->flags() & ~1u);

  int n = (this->at<int>(0xdc) - this->at<int>(0xd8)) >> 2;
  RefPtrVec* fx = &this->effects();
  for (int i = 0; i < n; ++i)
    (*(void (**)(int*, int))((*(int**)fx->mpBegin[i])[0] + 0xc))((int*)fx->mpBegin[i], renderSet);

  if (*(char*)(unsigned)(this->at<int>(0x14) + 0x14) == 0)
    eraseRange_RefPtr(fx->mpBegin, fx->mpEnd);

  this->setFlags(this->flags() & ~0x1000u);
  FUN_00a8d350(0);

  if (this->at<int>(0xec) >= 0) {
    cRenderer* r = this->at<cRenderer*>(0x1c);
    if ((uint8_t)(this->at<uint32_t>(0x28) >> 0xe) & 1) {
      cRenderSet* rs = r->GetRenderSet();
      rs->rs12(this->at<int>(0xec));
    } else {
      cRenderSet* rs = r->GetRenderSet();
      rs->rs7(this->at<int>(0xec));
    }
    this->at<int>(0xec) = -1;
  }

  SampleVec& sv = this->samples();
  uint8_t* b = sv.mpBegin;
  uint8_t* e = sv.mpEnd;
  VectorCopySamples(e, e, b);
  int nbytes = (int)(e - b) / -0x4c;
  sv.mpEnd += nbytes * 0x4c;
}
