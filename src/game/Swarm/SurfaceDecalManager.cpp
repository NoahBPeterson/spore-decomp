// src/game/Swarm/SurfaceDecalManager.cpp -- migrated from slice(s) s00a81110, s00a80240, s00a7f2e0 by tools/migrate/rewrite.py
// Object file: Swarm/SurfaceDecalManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include "EA/Swarm/cVisualEffect.h"
#include <math.h>

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
