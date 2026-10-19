// src/game/SPEngine/SPAppVolumeDescription.cpp -- migrated from slice(s) s007eed10, s007ee060 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppVolumeDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s007ee060 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line); // 0x00f473a0
inline void* operator new(size_t, void* p) throw() { return p; }
namespace EA {
namespace IO {
void ReadInt32(void* r, void* d, int n, int f);
}
}
namespace EA {
namespace IO {
void ReadTriple(void* r, void* d, int n, int f);   // 0x0093A800
}
}
namespace EA {
namespace ArgScript {
class cArguments_s007e_e060;
}
}
namespace EA {
namespace ArgScript {
void** MainArguments(cArguments_s007e_e060* self, int n);
}
}
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
static float ArgToFloat(void* iface, void* arg) {
  typedef float(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0x98))(iface, arg);
}
static void ArgToVec3(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*);
  ((F0)VSLOT(iface, 0xb0))(dst, arg);
}
static void ReadBytes(void* r, void* p, int n) {
  typedef void(__thiscall *F0)(void*, void*, int);
  ((F0)VSLOT(r, 0x30))(r, p, n);
}
struct Vec3f {
  float x, y, z;
};
struct VolumeCorner {
  Vec3f mPos;    // +0x0
  Vec3f mNormal; // +0xc
};
namespace EA {
namespace Swarm {
struct cDescription_s007e_e060 {
  virtual ~cDescription_s007e_e060();
  int mRefCount;
  cDescription_s007e_e060() : mRefCount(0) {}
};  // namespace Swarm
}  // namespace EA
}
namespace SP {
struct cVolumeDescription : public EA::Swarm::cDescription_s007e_e060 {
  Vec3f mSeedPoint;               // +0x8
  float mSliceSpacing;            // +0x14
  Vec3f mColor;                   // +0x18
  float mAlpha;                   // +0x24
  uint64_t mResourceID;           // +0x28
  VolumeCorner mCorners[8];       // +0x30
  cVolumeDescription();
};  // namespace SP
}
struct VolumeCmd {
  void Alpha(EA::ArgScript::cArguments_s007e_e060* args);
  void Color(EA::ArgScript::cArguments_s007e_e060* args);
  void SliceSpacing(EA::ArgScript::cArguments_s007e_e060* args);
};
struct MapDescription {
  void* vt;
  int refcount;
  uint32_t f08;
  uint32_t f0c;
  uint32_t f10;
  uint32_t f14;
  uint32_t f18;
  uint32_t f1c;
  uint32_t f20;
  uint32_t f24;
  uint32_t f28;
  uint32_t f2c;
  VolumeCorner corners[8];
  void* Copy(int src);
};
struct CommandBase {
  void* vtable;
};
void CommandBaseCtor(CommandBase*);
struct VolumeRegistrar {
  void Register(char flag);
};
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007ee060 end

// ---- items of slice s007eed10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* ArgMainArguments(void* args, void* out, int a, int b);
extern int ArgParseEnum(void* s, const char* name);
extern void ArgThrow(void* err, const char* msg);
extern void* GetInherited(void* parser, void* args, int n, int size);
struct HeapNode {
  double d;
  uint32_t x, y;
};
inline bool operator<(const HeapNode& a, const HeapNode& b) { return a.d < b.d; }
// ---- items of slice s007eed10 end

// @ 0x007ee540
SP::cVolumeDescription::cVolumeDescription()
{
  mSeedPoint.x = 0.0f;
  mSeedPoint.y = 0.0f;
  mSeedPoint.z = 0.0f;
  mSliceSpacing = 0.25f;
  mColor.x = 1.0f;
  mColor.y = 1.0f;
  mColor.z = 1.0f;
  mAlpha = 1.0f;
  mResourceID = 0x554771e5;
  for (uint32_t u = 0; u < 8; ++u) {
    mCorners[u].mPos.x = (u & 1) ? 1.0f : -1.0f;
    mCorners[u].mPos.y = (u & 2) ? 1.0f : -1.0f;
    mCorners[u].mPos.z = (u & 4) ? 1.0f : -1.0f;
    mCorners[u].mNormal.x = (u & 1) ? 1.0f : 0.0f;
    mCorners[u].mNormal.y = (u & 2) ? 1.0f : 0.0f;
    mCorners[u].mNormal.z = (u & 4) ? 1.0f : 0.0f;
  }
}

// @ 0x007ee630
extern "C" void* VolumeRead(int* reader)
{
  SP::cVolumeDescription* v = (SP::cVolumeDescription*)operator new(0xf0, "Swarm", 0, 0, 0, 0);
  if (v) new (v) SP::cVolumeDescription();
  ReadBytes(reader, (char*)v + 8, 0xc);
  EA::IO::ReadInt32(reader, (char*)v + 0x14, 1, 0);
  EA::IO::ReadTriple(reader, (char*)v + 0x28, 1, 0);
  int p = (int)v + 0x3c;
  int n = 8;
  do {
    ReadBytes(reader, (void*)(p - 0xc), 0xc);
    ReadBytes(reader, (void*)p, 0xc);
    p += 0x18;
    --n;
  } while (n != 0);
  return v;
}

// @ 0x007ee700
void VolumeCmd::Alpha(EA::ArgScript::cArguments_s007e_e060* args)
{
  int* self = (int*)this;
  void** p = EA::ArgScript::MainArguments(args, 1);
  int iface = **(int**)((char*)self + 4);
  *(float*)(*(char**)((char*)self + 0xc) + 0x2c) = ArgToFloat((void*)iface, *p);
}

// @ 0x007ee730
void VolumeCmd::Color(EA::ArgScript::cArguments_s007e_e060* args)
{
  int* self = (int*)this;
  void** p = EA::ArgScript::MainArguments(args, 1);
  int iface = **(int**)((char*)self + 4);
  Vec3f tmp;
  ArgToVec3((void*)iface, &tmp, *p);
  int dst = *(int*)((char*)self + 0xc);
  *(float*)(dst + 0x20) = tmp.x;
  *(float*)(dst + 0x24) = tmp.y;
  *(float*)(dst + 0x28) = tmp.z;
}

// @ 0x007ee7b0
extern "C" void VolumeMaterialCommand(int* self, EA::ArgScript::cArguments_s007e_e060* args)
{
  void** p = EA::ArgScript::MainArguments(args, 1);
  extern uint32_t HashName(const char*, uint32_t, int);   // 0x00932e80 (equiv t3)
  void* arg = *p;
  uint32_t h = HashName((const char*)arg, 0x811c9dc5, 1);
  int dst = *(int*)((char*)self + 0xc);
  *(uint32_t*)(dst + 0x30) = h;
  *(uint32_t*)(dst + 0x34) = 0;
}

// @ 0x007ee7f0
extern "C" void CopyVolumeDescription(int dst, int src)
{
  for (int off = 8; off <= 0xe8; off += 4) *(uint32_t*)(dst + off) = *(uint32_t*)(src + off);
}

// @ 0x007eea90
extern "C" void VolumeEffectOnRegister(char* font, void* arg, int param3)
{
  int v = (param3 == 0) ? 0 : param3 - 0xc;
  *(int*)(font + 4) = v;
  extern void FUN_0083c780(void*, int);
  FUN_0083c780(arg, param3);
  const char* names[] = {"alpha", "color", "slicespacing", "material", "volumeset"};
  for (int i = 0; i < 5; ++i) {
    void* cmd = operator new(0x10, "ArgScript/Volume", 0, 0, 0, 0);
    CommandBaseCtor((CommandBase*)cmd);
    typedef void(__thiscall * F0)(void*, const char*, void*);
    ((F0)VSLOT(font, 0x18))(font, names[i], cmd);
  }
}

// @ 0x007eec80
void VolumeRegistrar::Register(char flag)
{
  int self = (int)(size_t)this;
  if (flag == 0) {
    char* p = (char*)operator new(0xf0, "Swarm", 0, 0, 0, 0);
    void* v = p ? ((MapDescription*)p)->Copy(self + 0x40) : 0;
    extern void FUN_00a6f9c0(int, int, void*);
    FUN_00a6f9c0(*(int*)(self + 0x130), 0x28, v);
  }
}

// @ 0x007eed10
void VolumeSetExecute(void* self, void* args)
{
  int count = 0;
  void** a = (void**)ArgMainArguments(args, &count, 2, 8);
  int sel = ArgParseEnum(a[0], "corner");
  switch (sel) {
    case 0: {
      if (count < 5) ArgThrow(0, "Wrong number of arguments.");
      int* dst = *(int**)((char*)self + 0xc);
      dst[0] = 0;  // corner 0
      break;
    }
    case 1:
    case 2:
    case 3:
      if (count < 2) ArgThrow(0, "Wrong number of arguments.");
      break;
    default:
      break;
  }
}

// @ 0x007ef080
void VolumeEffectExecute(void* self, void* args)
{
  int count = 0;
  void** a = (void**)ArgMainArguments(args, &count, 1, 3);
  const char* name = (const char*)a[0];
  int n = 0;
  while (name[n] != 0) ++n;
  ((void(__thiscall*)(void*, const char*, int))VSLOT((char*)self + 0x130, 0))(0, name, n);
  if (count > 1) {
    void* inh = GetInherited(*(void**)((char*)self + 0x30), a, count, 0x28);
    (void)inh;
  }
  ((void(__thiscall*)(void*))VSLOT(*(void**)((char*)self + 4), 0x8c))(self);
}
