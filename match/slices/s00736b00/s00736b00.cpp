// Slice s00736b00 -- mesh tangent-frame generation (0x00736B00, 4150 bytes).
//
// For a mesh with float3 positions (usage 1), float3 normals (usage 2) and float2 texcoords
// (usage 8):
//   1. for every sub-mesh that references all three streams, walk its triangle-list batches
//      (type 4), compute a per-triangle tangent frame (FUN_00732cb0) and add it to the
//      per-vertex accumulators of the triangle's first and third vertex (the original never
//      touches the second vertex; reproduced as is), going through the sub-mesh's optional
//      index buffer and per-stream remap tables;
//   2. Gram-Schmidt the accumulated tangent against the normal, normalise it and write it to a
//      float3 tangent stream (usage 3), reusing an existing stream of the right size or
//      creating a new vertex buffer ("Graphics" heap);
//   3. register the new stream with the mesh and every qualifying sub-mesh.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- (old-style EH frame, no cookie)

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- ref-counted stream view

struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};

extern const uint32_t kIndexMasks[];  // 0x0140d4e0, indexed by index format

struct VertexStreamRef {  // 0x10
  int mCount;           // +0x00
  void* mData;          // +0x04
  uint16_t mFormat;     // +0x08
  uint16_t mStride;     // +0x0a
  RefCounted* mpOwner;  // +0x0c

  VertexStreamRef() : mCount(0), mData(0), mFormat(0), mStride(0), mpOwner(0) {}
  VertexStreamRef(const VertexStreamRef& o)
      : mCount(o.mCount), mData(o.mData), mFormat(o.mFormat), mStride(o.mStride),
        mpOwner(o.mpOwner) {
    if (mpOwner)
      mpOwner->AddRef();
  }
  ~VertexStreamRef() {
    if (mpOwner)
      mpOwner->Release();
  }
  __forceinline VertexStreamRef& operator=(const VertexStreamRef& o) {
    mCount = o.mCount;
    mData = o.mData;
    mFormat = o.mFormat;
    mStride = o.mStride;
    RefCounted* p = o.mpOwner;
    if (p != mpOwner) {
      RefCounted* old = mpOwner;
      if (p)
        p->AddRef();
      mpOwner = p;
      if (old)
        old->Release();
    }
    return *this;
  }

  float* Elem(uint32_t i) const { return (float*)((char*)mData + mStride * i); }
  uint32_t Index(uint32_t i) const {
    return *(uint32_t*)((char*)mData + mStride * i) & kIndexMasks[mFormat];
  }
};

// ---------------------------------------------------------------- mesh layout

struct MeshStream {  // 0x20
  int mUsage;          // +0x00
  int mUsageIndex;     // +0x04
  int mFormat;         // +0x08
  int mType;           // +0x0c
  VertexStreamRef mRef;  // +0x10

  MeshStream(int usage, int usageIndex, int format, int type, const VertexStreamRef& ref)
      : mUsage(usage), mUsageIndex(usageIndex), mFormat(format), mType(type), mRef(ref) {}
};

struct MeshStreamVec {
  MeshStream* mBegin;
  MeshStream* mEnd;
  MeshStream* mCap;
  void push_back(const MeshStream& s);  // 0x0041f7d0
};

struct StreamUse {
  short mStream;
  short mRemap;
};

struct StreamUseVec {
  StreamUse* mBegin;
  StreamUse* mEnd;
};

struct SubMesh {  // 0x8c
  VertexStreamRef mIndices;     // +0x00
  uint32_t f10;                 // +0x10
  StreamUseVec mStreams;        // +0x14
  uint32_t pad_1c[10];          // +0x1c
  VertexStreamRef* mRemapBegin; // +0x44
  VertexStreamRef* mRemapEnd;   // +0x48
  uint32_t pad_4c[16];          // +0x4c
};

struct Batch {  // 0x14
  int mType;     // +0x00 (4 = triangle list)
  int mSubMesh;  // +0x04
  int mStart;    // +0x08
  int mEnd;      // +0x0c
  int f10;       // +0x10
};

struct Mesh {
  uint32_t f00;
  uint32_t f04;
  MeshStreamVec mStreams;  // +0x08
  uint32_t f14;
  uint32_t f18;
  SubMesh* mSubBegin;      // +0x1c
  SubMesh* mSubEnd;        // +0x20
  uint32_t f24[3];
  Batch* mBatchBegin;      // +0x30
  Batch* mBatchEnd;        // +0x34
};

// ---------------------------------------------------------------- tangent accumulators

struct TangentFrame {  // 0x24
  float v[9];

  TangentFrame operator+(const TangentFrame& o) const {
    TangentFrame r;
    r.v[0] = v[0] + o.v[0];
    r.v[1] = v[1] + o.v[1];
    r.v[2] = v[2] + o.v[2];
    r.v[3] = v[3] + o.v[3];
    r.v[4] = v[4] + o.v[4];
    r.v[5] = v[5] + o.v[5];
    r.v[6] = v[6] + o.v[6];
    r.v[7] = v[7] + o.v[7];
    r.v[8] = v[8] + o.v[8];
    return r;
  }
};

struct Vec3 {
  float x, y, z;
  Vec3 operator*(float s) const {
    Vec3 r;
    r.x = x * s;
    r.y = y * s;
    r.z = z * s;
    return r;
  }
};

void __cdecl operator_delete__(void* p);  // 0x00f47380

struct TangentVec {
  TangentFrame* mBegin;
  TangentFrame* mEnd;
  TangentFrame* mCap;

  TangentVec() : mBegin(0), mEnd(0), mCap(0) {}
  ~TangentVec() {
    if (mBegin && ((int*)mBegin)[-1] != 0)
      operator_delete__(mBegin);
  }
  void resize(uint32_t n, const TangentFrame& v);  // 0x00735f30
};

extern const TangentFrame kZeroTangentFrame;  // 0x0162b67c

// ---------------------------------------------------------------- helpers

// 0x0071ded0: finds (or reports) the streams with the given usages/formats.
bool __cdecl FindMeshStreams(Mesh* mesh, int n, int* outIdx, const int* usages, int* usageIdx,
                             const int* formats, int* extra);
// 0x0071e230: does the sub-mesh reference all n streams?  Optionally returns their positions.
bool __cdecl SubMeshHasStreams(StreamUseVec* uses, int n, const int* idx, int* outPos);
// 0x0071ed30: adds n stream indices to the sub-mesh's stream list.
void __cdecl SubMeshAddStreams(StreamUseVec* uses, int n, const int* idx);
// 0x00732cb0: per-triangle tangent frame from positions and texcoords.
void __cdecl ComputeTriangleTangent(const float* p0, const float* p1, const float* p2,
                                    const float* t0, const float* t1, const float* t2,
                                    TangentFrame* out);

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

struct Float3Buffer : RefCounted {
  uint32_t pad[8];
  Float3Buffer(int count);   // 0x007335c0
  VertexStreamRef GetRef();  // 0x007217c0
};

// @ 0x00736B00
bool __cdecl GenerateMeshTangents(Mesh* mesh) {
  int usages[3];
  int formats[3];
  int idx[3];
  usages[0] = 1;
  usages[1] = 2;
  usages[2] = 8;
  formats[0] = 3;
  formats[1] = 3;
  formats[2] = 2;
  if (!FindMeshStreams(mesh, 3, idx, usages, 0, formats, 0))
    return false;

  VertexStreamRef* posRef = &mesh->mStreams.mBegin[idx[0]].mRef;
  VertexStreamRef* nrmRef = &mesh->mStreams.mBegin[idx[1]].mRef;
  VertexStreamRef* uvRef = &mesh->mStreams.mBegin[idx[2]].mRef;

  TangentVec accum;

  int numSub = (int)(mesh->mSubEnd - mesh->mSubBegin);
  for (int s = 0; s < numSub; ++s) {
    int pos[3];
    if (!SubMeshHasStreams(&mesh->mSubBegin[s].mStreams, 3, idx, pos))
      continue;

    VertexStreamRef ib(mesh->mSubBegin[s].mIndices);
    SubMesh* sub = &mesh->mSubBegin[s];
    bool remap = sub->mRemapBegin != sub->mRemapEnd;
    VertexStreamRef posMap;
    VertexStreamRef nrmMap;
    VertexStreamRef uvMap;
    if (remap) {
      sub = &mesh->mSubBegin[s];
      posMap = sub->mRemapBegin[sub->mStreams.mBegin[pos[0]].mRemap];
      sub = &mesh->mSubBegin[s];
      nrmMap = sub->mRemapBegin[sub->mStreams.mBegin[pos[1]].mRemap];
      sub = &mesh->mSubBegin[s];
      uvMap = sub->mRemapBegin[sub->mStreams.mBegin[pos[2]].mRemap];
    }

    int numBatches = (int)(mesh->mBatchEnd - mesh->mBatchBegin);
    for (int b = 0; b < numBatches; ++b) {
      Batch* batch = &mesh->mBatchBegin[b];
      if (batch->mSubMesh != s || batch->mType != 4)
        continue;
      if (accum.mBegin == accum.mEnd)
        accum.resize(nrmRef->mCount, kZeroTangentFrame);

      for (int i = batch->mStart; i < batch->mEnd; i += 3) {
        uint32_t i0 = i;
        uint32_t i1 = i + 1;
        uint32_t i2 = i + 2;
        if (ib.mData) {
          i0 = ib.Index(i0);
          i1 = ib.Index(i1);
          i2 = ib.Index(i2);
        }

        TangentFrame tf;
        if (remap) {
          ComputeTriangleTangent(posRef->Elem(posMap.Index(i0)), posRef->Elem(posMap.Index(i1)),
                                 posRef->Elem(posMap.Index(i2)), uvRef->Elem(uvMap.Index(i0)),
                                 uvRef->Elem(uvMap.Index(i1)), uvRef->Elem(uvMap.Index(i2)), &tf);
          uint32_t n0 = nrmMap.Index(i0);
          accum.mBegin[n0] = accum.mBegin[n0] + tf;
          uint32_t n2 = nrmMap.Index(i2);
          accum.mBegin[n2] = accum.mBegin[n2] + tf;
        } else {
          ComputeTriangleTangent(posRef->Elem(i0), posRef->Elem(i1), posRef->Elem(i2),
                                 uvRef->Elem(i0), uvRef->Elem(i1), uvRef->Elem(i2), &tf);
          accum.mBegin[i0] = accum.mBegin[i0] + tf;
          accum.mBegin[i2] = accum.mBegin[i2] + tf;
        }
      }
    }
  }

  if (accum.mBegin == accum.mEnd)
    return false;

  int outUsages[2];
  int outFormats[2];
  int outIdx[2];
  outUsages[0] = 3;
  outUsages[1] = 4;
  outFormats[0] = 3;
  outFormats[1] = 3;
  outIdx[0] = -1;
  outIdx[1] = -1;
  FindMeshStreams(mesh, 2, outIdx, outUsages, 0, outFormats, 0);

  VertexStreamRef tan;
  tan.mFormat = 0xc;
  tan.mStride = 0xc;
  bool create = true;
  if (outIdx[0] >= 0) {
    tan = mesh->mStreams.mBegin[outIdx[0]].mRef;
    if (tan.mData != 0 && nrmRef->mCount == tan.mCount)
      create = false;
  }
  if (create) {
    Float3Buffer* buf = new ("Graphics", 0, 0, 0, 0) Float3Buffer(nrmRef->mCount);
    tan = buf->GetRef();
  }

  int n = (int)(accum.mEnd - accum.mBegin);
  char* dst = (char*)tan.mData;
  for (int v = 0; v < n; ++v) {
    const float* nrm = nrmRef->Elem(v);
    const TangentFrame& f = accum.mBegin[v];
    float tx = f.v[0];
    float ty = f.v[1];
    float tz = f.v[2];
    float nx = nrm[0];
    float ny = nrm[1];
    float nz = nrm[2];
    float len2 = nx * nx + ny * ny + nz * nz + 1e-08f;
    float inv = 1.0f / sqrtf(len2);
    nx *= inv;
    ny *= inv;
    nz *= inv;
    float d = nx * tx + ny * ty + nz * tz;
    Vec3 t;
    t.x = tx - nx * d;
    t.y = ty - ny * d;
    t.z = tz - nz * d;
    float tlen2 = t.x * t.x + t.y * t.y + t.z * t.z + 1e-08f;
    float inv2 = 1.0f / sqrtf(tlen2);
    *(Vec3*)dst = t * inv2;
    dst += tan.mStride;
  }

  if (outIdx[0] < 0) {
    outIdx[0] = (int)(mesh->mStreams.mEnd - mesh->mStreams.mBegin);
    mesh->mStreams.push_back(MeshStream(outUsages[0], 0, outFormats[0], 2, tan));
  }

  int numSub2 = (int)(mesh->mSubEnd - mesh->mSubBegin);
  for (int s = 0; s < numSub2; ++s) {
    StreamUseVec* uses = &mesh->mSubBegin[s].mStreams;
    if (SubMeshHasStreams(uses, 3, idx, 0))
      SubMeshAddStreams(uses, 2, outIdx);
  }
  return true;
}
