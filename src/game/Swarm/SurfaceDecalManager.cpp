// src/game/Swarm/SurfaceDecalManager.cpp -- migrated from slice(s) s00a81110, s00a80240, s00a7f2e0 by tools/migrate/rewrite.py
// Object file: Swarm/SurfaceDecalManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include "EA/Swarm/cVisualEffect.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_00539440(void* a, void* b);   // EA::Swarm::normalized

// ---- items of slice s00a7f2e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00539440(void* a, void* b);   // EA::Swarm::normalized
struct ObjFE20 {
    virtual char v10(void*, void*, float*, int, int, int);   // slot 0x10
};
struct Owner {
    char  pad0[0x10];
    ObjFE20* p10;     // +0x10
    char  pad1[0x5c];
    float f70;        // +0x70
    void  FUN_00a7fe20(void* arg);
};
// ---- items of slice s00a7f2e0 end

// ---- items of slice s00a80240 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s00a80240 end

// ---- items of slice s00a81110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float DAT_01485720;                       // 1.0f
extern const float DAT_013eb1bc;
extern const char DAT_01457d88[];                      // "Swarm/SurfaceDecals"
typedef unsigned int   u32;
typedef unsigned short u16;
struct ExtCallees {
    void* __thiscall ctorCell();                       // 0x00a80920
    void* __thiscall ctorSurfaceDecals();              // 0x00a80ac0
    void* __thiscall mapInsert(u32 key);               // 0x00a810a0
    void* __thiscall mapFind(void** out, u32 key);     // 0x00a7bf40  (ret 8)
    void  __thiscall resize(int n);                    // 0x004c0410  (ret 4)
    void* __thiscall assign(const void* src);          // 0x00537dc0  (ret 4)
    void* __thiscall insert(void* pos, void** val);    // 0x00a80dd0  (ret 8)
};
extern "C" void* EAAllocate(u32 size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
namespace EA {
namespace Swarm {
class cSurfaceDecalManager {                           // size 0xa8 (dev layout)
public:
    void* AddDecal(int unused, u32 key, const void* xform, float scale);  // 0x00a81110
    void  SetSurface(void* surface, void* transform);  // 0x00a81310
};
}
}
using EA::Swarm::cSurfaceDecalManager;
// ---- items of slice s00a81110 end

// ---- items of slice s00a80240_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_167776c;          // 0x0167776c
extern float g_1677770;          // 0x01677770
extern float g_1677774;          // 0x01677774
extern float g_1564cc8;          // 0x01564cc8
extern float g_1457d54;          // 0x01457d54 (raw 0xce6e6b28, -1e9f)
extern float g_1470f1c;          // 0x01470f1c (raw 0x40000000, 2.0f)
extern void* g_staticBuckets;    // 0x0154df28 (one-element static bucket array)
extern void* g_vtblSurfaceDecals;      // 0x01457d58
extern void* g_vtblSurfaceDecalsEx;    // 0x01457d64
extern void* g_vtblSurfaceDecalsEx2;   // 0x01457d60
extern void* g_vtblIEventModifier;     // 0x013ef094
extern void  FreeMem(void* p);                            // 0x00f47380
struct Matrix33 {
  float m[9];
  void Assign(const Matrix33* src);                        // 0x0041cb40
};
extern Matrix33 g_identity33;                              // 0x01677818
struct IntrusiveList {
  IntrusiveList* mNext;   // +0x00
  IntrusiveList* mPrev;   // +0x04
  ~IntrusiveList();                                        // 0x00620230
};
struct Particle {
  uint32_t m0;        // +0x00
  uint32_t m4;        // +0x04
  uint16_t m8;        // +0x08
  uint16_t mA;        // +0x0a
  float    mC;        // +0x0c
  float    m10;       // +0x10
  float    m14;       // +0x14
  float    m18;       // +0x18
  Matrix33 mMatrix;   // +0x1c
  float    m40, m44, m48, m4c;   // +0x40
  float    m50, m54, m58, m5c;   // +0x50
  float    m60, m64;             // +0x60
  uint32_t m68, m6c;             // +0x68

  Particle* Ctor();                                          // 0x00a80920
};
struct SurfaceDecalState;
struct DecalNode {
  uint32_t mPad00;            // +0x00
  uint32_t mNext;             // +0x04 (link pointer to the next node's mNext)
  uint32_t mPrev;             // +0x08
  int32_t  mIndex;            // +0x0c
  uint8_t  mPad10[0x18];      // +0x10
  Particle mParticle;         // +0x28 .. +0x97
  SurfaceDecalState* mState;  // +0x98
};
struct CellDataNode {
  CellDataNode* mNext;        // +0x00
  CellDataNode* mPrev;        // +0x04
  uint8_t mData[0x90];        // +0x08 .. +0x97
  SurfaceDecalState* mState;  // +0x98
};
struct SimpleVector {
  CellDataNode** mBegin;      // +0x00
  CellDataNode** mEnd;        // +0x04
  CellDataNode** mCap;        // +0x08

  void DoInsertValue(CellDataNode** pos, CellDataNode** value); // 0x00a80dd0
};
struct SurfaceDecalState {
  uint8_t mPad00[0x0c];       // +0x00
  int32_t mIndex;             // +0x0c
  uint8_t mPad10[0x04];       // +0x10
  SimpleVector mVector;       // +0x14 (begin +0, end +4, cap +8)
};
struct HashNode {
  uint32_t mKey[4];           // +0x00
  HashNode* mNext;            // +0x10
};
struct RehashResult {
  uint8_t mFlag;              // +0x00
  uint8_t mPad[3];            // +0x01
  uint32_t mCount;            // +0x04
};
struct RehashPolicy {
  float mMaxLoad;             // +0x00
  float mGrowth;              // +0x04
  uint32_t mNextResize;       // +0x08

  bool NeedRehash(RehashResult* out, uint32_t bucketCount,
                  uint32_t elementCount, bool grow);        // 0x00921440
};
struct InsertResult {
  HashNode*  mNode;           // +0x00
  HashNode** mBucket;         // +0x04
  uint8_t    mFlag;           // +0x08
};
struct HashTable {
  uint32_t mUnused;           // +0x00
  HashNode** mBuckets;        // +0x04
  uint32_t mBucketCount;      // +0x08
  uint32_t mElementCount;     // +0x0c
  RehashPolicy mPolicy;       // +0x10

  void DoFreeNodes(HashNode** buckets, uint32_t count);     // 0x007611f0
  void Rehash(uint32_t newCount);                           // 0x00a7bd70
  InsertResult* Insert(InsertResult* out, const uint32_t* key,
                       uint32_t unused);                    // 0x00a80c00
};
struct SurfaceDecals {
  void*    mVtbl0;            // +0x00
  void*    mVtbl4;            // +0x04
  uint32_t m8;                // +0x08
  int32_t  mC;                // +0x0c
  void*    mObj10;            // +0x10
  void*    mObj14;            // +0x14
  uint32_t m18;               // +0x18
  uint32_t m1c;               // +0x1c
  int32_t  m20;               // +0x20
  int32_t  m24;               // +0x24
  float    m28, m2c, m30;     // +0x28
  float    m34, m38, m3c;     // +0x34
  float    m40, m44, m48, m4c;// +0x40
  int32_t  m50, m54;          // +0x50
  void*    mArray58;          // +0x58
  uint32_t m5c;               // +0x5c
  uint32_t m60;               // +0x60
  uint32_t m64;               // +0x64
  uint32_t m68;               // +0x68
  uint32_t m6c;               // +0x6c
  void*    mArray70;          // +0x70
  uint32_t m74;               // +0x74
  uint32_t m78;               // +0x78
  uint32_t m7c;               // +0x7c
  uint32_t m80;               // +0x80
  HashTable mHash;            // +0x84
  uint32_t mListA0;           // +0xa0
  IntrusiveList mListA4;      // +0xa4
  IntrusiveList mListAC;      // +0xac

  SurfaceDecals* BaseCtor();                                  // 0x00a80ac0
  SurfaceDecals* DerivedCtor();                               // 0x00a80ee0
  void Destroy();                                             // 0x00a80d10
  void VisitParticles();                                      // 0x00a809d0
  void ClearParticles();                                      // 0x00a80a40
  bool Reset();                                               // 0x00a80b80
  void RemoveCell(CellDataNode* cell);                        // 0x00a80fe0
};
typedef void (__thiscall* VtFn0)(void* self);
typedef void (__thiscall* VtFn1)(void* self, int a);
typedef void (__thiscall* VtFn3)(void* self, int a, void* b, float c);
static inline void* VtblOf(void* obj) {
  return *(void**)obj;
}
static inline void* VtSlot(void* vtable, uint32_t byteOffset) {
  return *(void**)((char*)vtable + byteOffset);
}
static inline void FreeArray(void* p) {
  if (p != 0 && ((int*)p)[-1] != 0)
    FreeMem(p);
}
// ---- items of slice s00a80240_g7 end

// @ 0x00a7fe20
void Owner::FUN_00a7fe20(void* arg)
{
    char* p = (arg != 0) ? ((char*)arg - 8) : 0;

    unsigned short w = *(unsigned short*)(p + 0xa);
    if (*(unsigned short*)(p + 0xa0) == w)
        return;

    *(unsigned short*)(p + 0xa0) = w;
    *(unsigned int*)(p + 0x80) = *(unsigned int*)(p + 0x1c);
    *(unsigned int*)(p + 0x84) = *(unsigned int*)(p + 0x20);
    *(unsigned int*)(p + 0x88) = *(unsigned int*)(p + 0x24);
    *(unsigned int*)(p + 0x8c) = *(unsigned int*)(p + 0x28);
    *(unsigned int*)(p + 0x90) = *(unsigned int*)(p + 0x2c);
    *(unsigned int*)(p + 0x94) = *(unsigned int*)(p + 0x30);

    float* pf = (float*)(p + 0x74);
    if (p10 == 0) {
        *pf = *(float*)(p + 0xc);
        *(unsigned int*)(p + 0x78) = *(unsigned int*)(p + 0x10);
        *(unsigned int*)(p + 0x7c) = *(unsigned int*)(p + 0x14);
        *(unsigned int*)(p + 0x7c) = 0;
    } else {
        float fVar3 = this->f70;
        float buf[3];
        buf[0] = 0.0f; buf[1] = 0.0f; buf[2] = 0.0f;
        int f70bits = *(int*)&fVar3;
        char cVar5 = p10->v10(p + 0xc, pf, buf, 0, f70bits, 0);
        if (cVar5 != 0) {
            float out[3];
            float a0 = buf[0];
            float a1 = fVar3;
            float a2 = 0.0f;
            float left  = a0 * *(float*)(p + 0x8c) + (*(float*)(p + 0x94) * a1 + *(float*)(p + 0x90) * a2);
            float right = (*(float*)(p + 0x88) * a1 + *(float*)(p + 0x84) * a2) + *(float*)(p + 0x80) * a0;
            float fabsL = left < 0.0f ? -left : left;
            float fabsR = right < 0.0f ? -right : right;
            float* puVar6;
            if (fabsL <= fabsR) {
                out[0] = *(float*)(p + 0x90) * a1 - *(float*)(p + 0x94) * a2;
                puVar6 = (float*)FUN_00539440(buf, out);
                *(float*)(p + 0x80) = puVar6[0];
                *(float*)(p + 0x84) = puVar6[1];
                *(float*)(p + 0x88) = puVar6[2];
                *(float*)(p + 0x8c) = *(float*)(p + 0x88) * a2 - *(float*)(p + 0x84) * a1;
                *(float*)(p + 0x90) = *(float*)(p + 0x80) * a1 - *(float*)(p + 0x88) * a0;
                *(float*)(p + 0x94) = *(float*)(p + 0x84) * a0 - *(float*)(p + 0x80) * a2;
            } else {
                out[0] = *(float*)(p + 0x88) * a2 - *(float*)(p + 0x84) * a1;
                puVar6 = (float*)FUN_00539440(buf, out);
                *(float*)(p + 0x8c) = puVar6[0];
                *(float*)(p + 0x90) = puVar6[1];
                *(float*)(p + 0x94) = puVar6[2];
                *(float*)(p + 0x80) = *(float*)(p + 0x90) * a1 - *(float*)(p + 0x94) * a2;
                *(float*)(p + 0x84) = *(float*)(p + 0x94) * a0 - *(float*)(p + 0x8c) * a1;
                *(float*)(p + 0x88) = *(float*)(p + 0x8c) * a2 - *(float*)(p + 0x90) * a0;
            }
            float fVar2 = *(float*)(p + 0x70);
            *pf = fVar2 * a0 + *pf;
            *(float*)(p + 0x78) = fVar2 * a2 + *(float*)(p + 0x78);
            *(float*)(p + 0x7c) = fVar2 * a1 + *(float*)(p + 0x7c);
        }
    }

    int iv = *(int*)(p + 0x98);
    if (iv != 0) {
        if (*pf < *(float*)(iv + 0x28))
            *(float*)(iv + 0x28) = *pf;
        if (*(float*)(iv + 0x34) < *pf)
            *(float*)(iv + 0x34) = *pf;
        if (*(float*)(p + 0x78) < *(float*)(iv + 0x2c))
            *(float*)(iv + 0x2c) = *(float*)(p + 0x78);
        if (*(float*)(iv + 0x38) < *(float*)(p + 0x78))
            *(float*)(iv + 0x38) = *(float*)(p + 0x78);
        if (*(float*)(p + 0x7c) < *(float*)(iv + 0x30))
            *(float*)(iv + 0x30) = *(float*)(p + 0x7c);
        if (*(float*)(iv + 0x3c) < *(float*)(p + 0x7c))
            *(float*)(iv + 0x3c) = *(float*)(p + 0x7c);
    }
}

// @ 0x00a80240
void BillboardEffect::WriteQuads(VertexStream* stream)
{
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

// @ 0x00a80920
Particle* Particle::Ctor()
{
  m4 = 0;
  m0 = 0;
  uint32_t zA = m0;
  uint32_t z8 = m0;
  mA = (uint16_t)zA;
  m8 = (uint16_t)z8;
  mC = g_167776c;
  m10 = g_1677770;
  m14 = g_1677774;
  m18 = 1.0f;
  mMatrix.Assign(&g_identity33);
  m40 = 1.0f;
  m44 = 1.0f;
  m48 = 1.0f;
  m4c = 1.0f;
  m50 = 1.0f;
  m54 = 1.0f;
  m58 = 1.0f;
  m5c = 1.0f;
  m60 = 0.0f;
  m64 = 0.0f;
  m68 = 0;
  m6c = 0;
  return this;
}

// @ 0x00a809d0
void SurfaceDecals::VisitParticles()
{
  DecalNode* node = mListA4.mNext
      ? (DecalNode*)((char*)mListA4.mNext - 4) : 0;
  DecalNode* end = (DecalNode*)((char*)&mListA4 - 4);
  while (node != end) {
    if (node->mIndex >= 0) {
      void* owner = mObj14;
      VtFn3 fn = (VtFn3)VtSlot(VtblOf(owner), 0x20);
      fn(owner, node->mIndex, &node->mParticle, 0.0f);
    }
    node = node->mNext
        ? (DecalNode*)((char*)node->mNext - 4) : 0;
  }
}

// @ 0x00a80a40
void SurfaceDecals::ClearParticles()
{
  DecalNode* node = mListA4.mNext
      ? (DecalNode*)((char*)mListA4.mNext - 4) : 0;
  DecalNode* end = (DecalNode*)((char*)&mListA4 - 4);
  while (node != end) {
    if (node->mIndex >= 0) {
      void* owner = mObj14;
      VtFn1 fn = (VtFn1)VtSlot(VtblOf(owner), 0x1c);
      fn(owner, node->mIndex);
      node->mIndex = -1;
    }
    node = node->mNext
        ? (DecalNode*)((char*)node->mNext - 4) : 0;
  }
  void* owner = mObj14;
  if (owner != 0) {
    mObj14 = 0;
    VtFn0 fn = (VtFn0)VtSlot(VtblOf(owner), 0x04);
    fn(owner);
  }
}

// @ 0x00a80ac0
SurfaceDecals* SurfaceDecals::BaseCtor()
{
  float v = g_1564cc8;
  m8 = 0;
  mVtbl4 = 0;
  mVtbl0 = &g_vtblSurfaceDecals;
  mC = -1;
  mObj14 = 0;
  m18 = 0;
  m1c = 0;
  m28 = v;
  m2c = v;
  m30 = v;
  float nv = -v;
  m34 = nv;
  m38 = nv;
  m3c = nv;
  return this;
}

// @ 0x00a80b80
bool SurfaceDecals::Reset()
{
  if (mObj14 != 0)
    ClearParticles();

  IntrusiveList* anchor = &mListAC;
  while (anchor->mPrev != anchor) {
    CellDataNode* first = (CellDataNode*)anchor->mNext;
    CellDataNode* next = first->mNext;
    next->mPrev = (CellDataNode*)anchor;
    anchor->mNext = (IntrusiveList*)next;
    if (first != (CellDataNode*)anchor) {
      first->mPrev = 0;
      first->mNext = 0;
    }
    if (first != 0)
      FreeMem(first);
  }

  IntrusiveList* anchorA4 = &mListA4;
  uint32_t* p = (uint32_t*)mListA4.mNext;
  if (p != (uint32_t*)anchorA4) {
    do {
      uint32_t next = *p;
      p[1] = 0;
      p[0] = 0;
      p = (uint32_t*)next;
    } while (p != (uint32_t*)anchorA4);
  }
  mListA4.mPrev = anchorA4;
  mListA4.mNext = anchorA4;
  return true;
}

// @ 0x00a80d10
void SurfaceDecals::Destroy()
{
  mVtbl0 = &g_vtblSurfaceDecalsEx;
  mVtbl4 = &g_vtblSurfaceDecalsEx2;
  mListAC.~IntrusiveList();
  mListA4.~IntrusiveList();

  mHash.DoFreeNodes(mHash.mBuckets, mHash.mBucketCount);
  mHash.mElementCount = 0;
  if (mHash.mBucketCount > 1)
    FreeMem(mHash.mBuckets);

  FreeArray(mArray70);
  FreeArray(mArray58);

  if (mObj14 != 0) {
    void* owner = mObj14;
    VtFn0 fn = (VtFn0)VtSlot(VtblOf(owner), 0x04);
    fn(owner);
  }
  if (mObj10 != 0) {
    void* owner = mObj10;
    VtFn0 fn = (VtFn0)VtSlot(VtblOf(owner), 0x00);
    fn(owner);
  }
  mVtbl4 = &g_vtblIEventModifier;
}

// @ 0x00a80ee0
SurfaceDecals* SurfaceDecals::DerivedCtor()
{
  mVtbl4 = &g_vtblIEventModifier;
  m8 = 0;
  mVtbl0 = &g_vtblSurfaceDecalsEx;
  mVtbl4 = &g_vtblSurfaceDecalsEx2;
  mC = 0;
  mObj10 = 0;
  mObj14 = 0;
  m30 = 0.0f;
  m34 = 0.0f;
  m38 = 0.0f;
  m40 = 0.0f;
  m44 = 0.0f;
  m48 = 0.0f;
  m18 = 0;
  m4c = g_1457d54;
  m28 = 1.0f;
  m2c = 1.0f;
  m3c = 1.0f;
  m20 = -1;
  m24 = -1;
  m50 = -1;
  m54 = -1;
  mArray58 = 0;
  m5c = 0;
  m60 = 0;
  mArray70 = 0;
  m74 = 0;
  m78 = 0;
  mHash.mPolicy.mMaxLoad = 1.0f;
  mHash.mPolicy.mGrowth = g_1470f1c;
  mHash.mElementCount = 0;
  mHash.mPolicy.mNextResize = 0;
  mHash.mBucketCount = 1;
  mHash.mBuckets = (HashNode**)&g_staticBuckets;
  mListA4.mPrev = &mListA4;
  mListA4.mNext = &mListA4;
  mListAC.mPrev = &mListAC;
  mListAC.mNext = &mListAC;
  return this;
}

// @ 0x00a80fe0
void SurfaceDecals::RemoveCell(CellDataNode* cell)
{
  if (mListAC.mPrev == &mListAC)
    return;

  CellDataNode* node = (CellDataNode*)((char*)cell - 8);
  SurfaceDecalState* state = node->mState;
  CellDataNode** begin = state->mVector.mBegin;
  CellDataNode** end = state->mVector.mEnd;
  int count = (int)(end - begin);
  for (int i = 0; i < count; ++i) {
    if (begin[i] == node) {
      CellDataNode** dst = begin + i;
      CellDataNode** src = dst + 1;
      if (src < end)
        memcpy(dst, src, (char*)end - (char*)src);
      state->mVector.mEnd = end - 1;
      break;
    }
  }

  state = node->mState;
  if (state->mVector.mBegin == state->mVector.mEnd && state->mIndex >= 0) {
    void* owner = mObj14;
    VtFn1 fn = (VtFn1)VtSlot(VtblOf(owner), 0x1c);
    fn(owner, state->mIndex);
    state->mIndex = -1;
  }

  CellDataNode* next = node->mNext;
  CellDataNode* prev = node->mPrev;
  prev->mNext = next;
  next->mPrev = prev;
  node->mNext = 0;
  node->mPrev = 0;
  FreeMem(node);
}

// @ 0x00a81110
void* EA::Swarm::cSurfaceDecalManager::AddDecal(int /*unused*/, u32 key, const void* xform, float scale)
{
    char* self = (char*)this;

    char* cell;
    void* mem = EAAllocate(0xa4, DAT_01457d88, 0, 0, 0, 0);
    if (mem) cell = (char*)((ExtCallees*)mem)->ctorCell();
    else     cell = 0;

    // intrusive list insert of `cell` into the list anchored at self+0xac (mDecals)
    {
        void* anchor = self + 0xac;
        void* next = *(void**)anchor;
        *(void**)(cell + 0x00) = next;
        *(void**)(cell + 0x04) = anchor;
        *(void**)anchor = cell;
        *(void**)((char*)*(void**)cell + 4) = cell;
    }

    void* map = self + 0x84;
    void* node = 0;
    ((ExtCallees*)map)->mapFind(&node, key);

    void** buckets = *(void***)((char*)map + 4);
    int    index   = *(int*)((char*)map + 8);
    if (node == buckets[index]) {
        // not found: create the quad set and register it
        char* sd;
        void* m2 = EAAllocate(0x40, DAT_01457d88, 0, 0, 0, 0);
        if (m2) sd = (char*)((ExtCallees*)m2)->ctorSurfaceDecals();
        else     sd = 0;

        void* anchor = self + 0xa4;                    // mQuadSets
        char* n2 = sd + 4;
        *(void**)(n2 + 0) = *(void**)anchor;
        *(void**)(sd + 8) = anchor;
        *(void**)anchor = n2;
        *(void**)((char*)*(void**)n2 + 4) = n2;

        void* slot = ((ExtCallees*)map)->mapInsert(key);
        *(void**)slot = sd;
        *(void**)(cell + 0x98) = sd;
    } else {
        *(void**)(cell + 0x98) = *(void**)((char*)node + 8);
    }

    // notify the renderer if the surface quad has not been created yet
    void* rend = *(void**)(self + 0x14);
    char* sd = *(char**)(cell + 0x98);
    if (rend != 0 && *(int*)(sd + 0xc) < 0) {
        void** vt = *(void***)rend;
        char ok = ((char(__thiscall*)(void*, void*, u32, void*))vt[6])(rend, sd, key, sd + 0xc);
        if (ok) {
            ((void(__thiscall*)(void*, void*, int))vt[9])(rend, *(void**)(sd + 0xc), 1);
            float box[6];
            box[0] = DAT_013eb1bc; box[1] = DAT_013eb1bc; box[2] = DAT_013eb1bc;
            box[3] = DAT_01485720; box[4] = DAT_01485720; box[5] = DAT_01485720;
            ((void(__thiscall*)(void*, void*, float*, int))vt[8])(rend, *(void**)(sd + 0xc), box, 0);
            ((void(__thiscall*)(void*, int, void*))vt[4])(rend, 0, sd + 0x10);
        }
    }

    // push the new cell onto the quad set's cell vector
    {
        char* vec = sd + 0x14;
        void* end = *(void**)(vec + 4);
        if (end < *(void**)(vec + 8)) {
            *(void**)(vec + 4) = (char*)end + 4;
            if (end) *(void**)end = cell;
        } else {
            void* tmp = cell;
            ((ExtCallees*)vec)->insert(end, &tmp);
            cell = (char*)tmp;
        }
    }

    char* xf = cell + 8;
    ((ExtCallees*)xf)->assign(xform);
    *(float*)(cell + 0x50) = scale;
    *(u16*)(cell + 0xa0) = 0xffff;
    *(float*)(cell + 0x70) = *(float*)(sd + 0x10);

    // this->vtable[5](xf)
    void** vt = *(void***)self;
    ((void(__thiscall*)(void*, void*))vt[5])(self, xf);
    return xf;
}
