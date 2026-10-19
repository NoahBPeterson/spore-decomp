// src/game/SPEngine/SPAppCloudDescription.cpp -- migrated from slice(s) s00f54af0, s007ed1b0, s004553b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppCloudDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s004553b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
// ---- items of slice s004553b0 end

// ---- items of slice s007ed1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p); // 0x00f47380
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
struct Vec3Vec {
  Vec3* mpBegin;     // +0x0
  Vec3* mpEnd;       // +0x4
  Vec3* mpCapacity;  // +0x8
  void PushBack(Vec3* value);
};
    void operator delete(void*); // 0x00f47380
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007ed1b0 end

// @ 0x00455660
void* VectorPushBack3(int* self, Vec3* value)
{
    if (self[1] == self[2]) {
        // grow and append; outlined
    }
    return 0;
}

// @ 0x007ed1b0
extern "C" void ScaleCurve(Vec3Vec* v, Vec3* pos, Vec3* value)
{
  if (v->mpEnd != v->mpCapacity) {
    if (pos <= value && value < v->mpEnd) value = (Vec3*)((char*)value + 0xc);
    if (v->mpEnd) *v->mpEnd = v->mpEnd[-1];
    Vec3* dst = v->mpEnd;
    Vec3* src = v->mpEnd;
    while ((Vec3*)((char*)src - 0xc) != pos) {
      dst[-1] = src[-2];
      dst = (Vec3*)((char*)dst - 0xc);
      src = (Vec3*)((char*)src - 0xc);
    }
    *pos = *value;
    v->mpEnd = (Vec3*)((char*)v->mpEnd + 0xc);
    return;
  }
  uint32_t cap = (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  if (cap == 0) cap = 1;
  else cap = cap * 2;
  Vec3* data = cap ? (Vec3*)operator new[](cap * 0xc, "App", 0, 0, "allocator.h", 0xd1) : 0;
  Vec3* d = data;
  for (Vec3* p = v->mpBegin; p != pos; ++p, ++d) *d = *p;
  if (d) *d = *value;
  ++d;
  for (Vec3* p = pos; p != v->mpEnd; ++p, ++d) *d = *p;
  if (v->mpBegin) operator delete(v->mpBegin);
  v->mpBegin = data;
  v->mpEnd = d;
  v->mpCapacity = data + cap;
}

// @ 0x00f54ef0
namespace
{
class cCloudEffectCommand {
 public:
  void OnRegister();
};
void cCloudEffectCommand::OnRegister() {}
}
