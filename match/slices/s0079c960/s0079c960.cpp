// slice s0079c960: sphere clipper over a triangle list (mesh clipping against a sphere)
#include "types.h"
#include <new>

extern const uint32_t g_bitMask[];   // 0x0140f544: low-bit masks, indexed by bit count

// packed array: element i is at data + stride * i, value = *(T*)(..) & g_bitMask[bits]
struct Packed {
  int unk0;
  char* data;
  uint16_t bits;
  uint16_t stride;
  int pad;
};

struct VertexElement {     // 0x20 bytes
  int a, b, c, d;
  Packed packed;
};

struct RemapEntry { short a; short packedIndex; };

struct Stream {            // 0x8c bytes
  int pad0;
  char* data;              // +4
  uint16_t bits;           // +8
  uint16_t stride;         // +0xa
  int pad0c, pad10;
  const RemapEntry* remapTab; // +0x14: 4-byte entries, short at +2 selects a Packed in remapBegin
  uint32_t pad18[11];
  Packed* remapBegin;      // +0x44
  Packed* remapEnd;        // +0x48
  uint32_t pad4c[0x10];
};

struct Mesh {
  int pad0, pad4;
  VertexElement* elemBegin;  // +8
  VertexElement* elemEnd;    // +0xc
  int pad10, pad14, pad18;
  Stream* streams;           // +0x1c
};

struct TriRange {
  int pad0;
  int stream;                // +4
  int start;                 // +8
  int end;                   // +0xc
};

struct UShortVec {
  uint16_t* mpBegin;
  uint16_t* mpEnd;
  uint16_t* mpCapacity;
  int pad[2];
  void __thiscall DoInsertValue(uint16_t* pos, const uint16_t& v);   // 0x006f5bc0
  inline void push_back(uint16_t value) {
    if (mpEnd < mpCapacity)
      ::new ((void*)mpEnd++) uint16_t(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

struct NewVertex {
  int a, b, c;
  float t;
};

struct ClipOut {
  int pad0;
  NewVertex* vBegin;         // +4
  NewVertex* vEnd;           // +8
  NewVertex* vCap;           // +0xc
  int pad10, pad14;
  UShortVec* indexSets;      // +0x18, stride 0x14
  int pad1c[4];
  int pad2c;
  int curSet;                // +0x30
  void __thiscall Pass(int stream, int v);                          // 0x0079b4b0
  void __thiscall Edge(int stream, int a, int b, float t);          // 0x0079b520
};

struct Sphere {
  float c[3];
  float r2;
  float __thiscall RayHit(const float* a, const float* b);          // 0x00799b50
};

int FindElement(Mesh* m, int a, int b, int c, int d);                // 0x0071ddc0 (cdecl)

struct Clipper {
  int pad0, pad4;
  int mode;                  // +8
  Sphere sphere;             // +0xc
  int keepOutside;           // +0x1c
  void __thiscall Run(Mesh* mesh, TriRange* range, UShortVec* out, ClipOut* co);
};

static inline int Far(const Sphere& s, const float* p) {
  float dx = p[0] - s.c[0];
  float dy = p[1] - s.c[1];
  float dz = p[2] - s.c[2];
  return ((dz * dz + dy * dy) + dx * dx) > s.r2;
}

static inline uint32_t Fetch(const Packed* p, uint32_t i) {
  return *(uint32_t*)(p->data + p->stride * i) & g_bitMask[p->bits];
}

static inline uint16_t Fetch16(const Stream* s, int i) {
  return *(uint16_t*)(s->data + s->stride * i) & (uint16_t)g_bitMask[s->bits];
}

// @ 0x0079c960
void __thiscall Clipper::Run(Mesh* mesh, TriRange* range, UShortVec* out, ClipOut* co) {
  int e = FindElement(mesh, 1, 0, 3, 14);
  Packed* pos = &mesh->elemBegin[e].packed;
  Stream* s = &mesh->streams[range->stream];
  for (int i = range->start; i < range->end; i += 3) {
    uint32_t i0, i1, i2;
    if (s->remapBegin == s->remapEnd) {
      uint32_t m = g_bitMask[s->bits];
      i0 = *(uint32_t*)(s->data + s->stride * i) & m;
      i1 = *(uint32_t*)(s->data + s->stride * (i + 1)) & m;
      i2 = *(uint32_t*)(s->data + s->stride * (i + 2)) & m;
    } else {
      uint32_t m = g_bitMask[s->bits];
      const Packed* r = &s->remapBegin[s->remapTab[e].packedIndex];
      i0 = Fetch(r, *(uint32_t*)(s->data + s->stride * i) & m);
      i1 = Fetch(r, *(uint32_t*)(s->data + s->stride * (i + 1)) & m);
      i2 = Fetch(r, *(uint32_t*)(s->data + s->stride * (i + 2)) & m);
    }
    const float* p0 = (const float*)(pos->data + pos->stride * i0);
    const float* p1 = (const float*)(pos->data + pos->stride * i1);
    const float* p2 = (const float*)(pos->data + pos->stride * i2);
    int n0 = Far(sphere, p0) == keepOutside;
    int n1 = Far(sphere, p1) == keepOutside;
    int n2 = Far(sphere, p2) == keepOutside;
    int sum = n1 + n2 + n0;
    bool emit;
    if (sum == (sum / 3) * 3) {
      if (n0 == sum % 3) continue;
      emit = true;
    } else if (mode == 0) {
      emit = true;
    } else if (mode == 2) {
      if (!(sum > 1)) continue;
      emit = true;
    } else if (mode == 3) {
      int count = (int)(co->vEnd - co->vBegin);
      uint16_t base = (uint16_t)count;
      int st = range->stream;
      if (n0 == 0) {
        if (n1 == 0) {
          co->Edge(st, i + 2, i, sphere.RayHit(p2, p0));
          co->Edge(st, i + 2, i + 1, sphere.RayHit(p2, p1));
          co->Pass(st, i + 2);
        } else {
          co->Edge(st, i + 1, i, sphere.RayHit(p1, p0));
          co->Pass(st, i + 1);
          if (n2 == 0) {
            co->Edge(st, i + 1, i + 2, sphere.RayHit(p1, p2));
          } else {
            co->Pass(st, i + 2);
            co->Edge(st, i + 2, i, sphere.RayHit(p2, p0));
          }
        }
      } else {
        co->Pass(st, i);
        if (n1 == 0) {
          co->Edge(st, i, i + 1, sphere.RayHit(p0, p1));
          if (n2 != 0) {
            co->Edge(st, i + 2, i + 1, sphere.RayHit(p2, p1));
            co->Pass(st, i + 2);
          } else {
            co->Edge(st, i, i + 2, sphere.RayHit(p0, p2));
          }
        } else {
          co->Pass(st, i + 1);
          co->Edge(st, i + 1, i + 2, sphere.RayHit(p1, p2));
          co->Edge(st, i, i + 2, sphere.RayHit(p0, p2));
        }
      }
      UShortVec* v = &co->indexSets[co->curSet];
      uint16_t a = base;
      v->push_back(a);
      uint16_t b = (uint16_t)(count + 1);
      co->indexSets[co->curSet].push_back(b);
      uint16_t c = (uint16_t)(count + 2);
      co->indexSets[co->curSet].push_back(c);
      if (sum > 1) {
        co->indexSets[co->curSet].push_back(a);
        co->indexSets[co->curSet].push_back(c);
        uint16_t d = (uint16_t)(count + 3);
        co->indexSets[co->curSet].push_back(d);
      }
      continue;
    } else {
      continue;
    }
    if (emit) {
      uint16_t v0 = Fetch16(s, i);
      out->push_back(v0);
      uint16_t v1 = Fetch16(s, i + 1);
      out->push_back(v1);
      uint16_t v2 = Fetch16(s, i + 2);
      out->push_back(v2);
    }
  }
}
