// Slice s007ee060: SP::cVolumeDescription (Swarm volume effect descriptor) and
// its ArgScript commands, volume serialization, and the cVolumeEffectCommand
// registration helper.
// Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line); // 0x00f473a0
void operator delete(void* p);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

namespace EA {
namespace IO {
void ReadInt32(void* r, void* d, int n, int f);
void ReadTriple(void* r, void* d, int n, int f);   // 0x0093A800
void WriteUint32(void* w, void* s, int n, int f);
}  // namespace IO
namespace ArgScript {
class cArguments;
void** MainArguments(cArguments* self, int n);
}  // namespace ArgScript
}  // namespace EA

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
static float ArgToFloat(void* iface, void* arg) {
  typedef float(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0x98))(iface, arg);
}
static void ArgToVec3(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*);
  ((F0)VSLOT(iface, 0xb0))(dst, arg);
}
static void WriteBytes(void* w, void* p, int n) {
  typedef void(__thiscall *F0)(void*, void*, int);
  ((F0)VSLOT(w, 0x38))(w, p, n);
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
struct cDescription {
  virtual ~cDescription();
  int mRefCount;
  cDescription() : mRefCount(0) {}
};
}  // namespace Swarm
}  // namespace EA

namespace SP {
struct cVolumeDescription : public EA::Swarm::cDescription {
  Vec3f mSeedPoint;               // +0x8
  float mSliceSpacing;            // +0x14
  Vec3f mColor;                   // +0x18
  float mAlpha;                   // +0x24
  uint64_t mResourceID;           // +0x28
  VolumeCorner mCorners[8];       // +0x30
  cVolumeDescription();
};
}  // namespace SP

// @ 0x007EE060  cVolumeDescription-driven effect update
extern "C" int VolumeEffectUpdate(int* self, float dt) {
  extern void DispatchEffect(int, int, int, int, float, float, float, float, float, int, int);
  if (self[6] < 0) {
    extern void FUN_007edd80(int*);
    FUN_007edd80(self);
    if (self[6] < 0) {
      typedef void(__thiscall * F0)(void*, int);
      ((F0)VSLOT(self, 0xc))(self, 1);
      return 0;
    }
  }
  int src = self[3];
  float local = (float)self[7];
  float* pf = *(float**)(src + 0x6c);
  if (pf != *(float**)(src + 0x70)) {
    int i = (int)((*(int*)(src + 0x70) - (int)pf) >> 2) - 1;
    float v;
    if (i == 0)
      v = *pf;
    else {
      float fi = (float)i;
      if (i < 0) fi += 4.2949673e+09f;
      int k = (int)(fi * (float)self[0xb]);
      float frac = fi * (float)self[0xb] - (float)k;
      if (frac <= 0.0f)
        v = *(float*)(*(int*)(src + 0x6c) + k * 4);
      else {
        float a = *(float*)(*(int*)(src + 0x6c) + k * 4);
        v = (*(float*)(*(int*)(src + 0x6c) + 4 + k * 4) - a) * frac + a;
      }
    }
    local = v * local;
  }
  int s2 = self[3];
  float* pv = *(float**)(s2 + 0x44);
  float rx = 1.0f, ry = 1.0f, rz = 1.0f, rw = 1.0f;
  if (pv != *(float**)(s2 + 0x48)) {
    int i = (*(int*)(s2 + 0x48) - (int)pv) / 0xc - 1;
    if (i == 0) {
      rx = pv[0];
      ry = pv[1];
      rz = pv[2];
    } else {
      float fi = (float)i;
      if (i < 0) fi += 4.2949673e+09f;
      int k = (int)(fi * (float)self[0xb]);
      float fr = fi * (float)self[0xb] - (float)k;
      float* base = *(float**)(s2 + 0x44);
      float* e = base + k * 3;
      if (fr <= 0.0f) {
        rx = e[0];
        ry = e[1];
        rz = e[2];
      } else {
        rx = e[0] + (base[k * 3 + 3] - e[0]) * fr;
        ry = e[1] + (base[k * 3 + 4] - e[1]) * fr;
        rz = e[2] + (base[k * 3 + 5] - e[2]) * fr;
      }
    }
  }
  int s3 = self[3];
  float* pw = *(float**)(s3 + 0x58);
  if (pw != *(float**)(s3 + 0x5c)) {
    int i = (int)((*(int*)(s3 + 0x5c) - (int)pw) >> 2) - 1;
    if (i == 0)
      rw = *pw;
    else {
      float fi = (float)i;
      if (i < 0) fi += 4.2949673e+09f;
      int k = (int)(fi * (float)self[0xb]);
      float fr = fi * (float)self[0xb] - (float)k;
      float a = *(float*)(*(int*)(s3 + 0x58) + k * 4);
      if (fr <= 0.0f)
        rw = a;
      else
        rw = (*(float*)(*(int*)(s3 + 0x58) + 4 + k * 4) - a) * fr + a;
    }
  }
  DispatchEffect(self[6], self[8], self[9], self[10], local, rx, ry, rz, rw,
                 *(int*)(self[3] + 0x38), *(int*)(self[3] + 0x3c));
  float t = *(float*)(self[3] + 0x40) * dt + (float)self[0xb];
  self[0xb] = (int)t;
  if (t >= 1.0f) {
    if ((*(uint32_t*)(self[3] + 8) >> 1 & 1) != 0) {
      self[0xb] = 0x3f800000;
      return 0;
    }
    typedef void(__thiscall * F0)(void*, int);
    ((F0)VSLOT(self, 0xc))(self, 0);
  }
  return 0;
}

// @ 0x007EE3E0  allocate + construct a volume-effect object
extern "C" void* AllocVolumeEffect(void* manager, void* arg) {
  char* p = (char*)operator new(0x48, "Swarm", 0, 0, 0, 0);
  if (p) {
    extern void* EffectObjectCtor(void*, void*);
    return EffectObjectCtor(p, arg);
  }
  return 0;
}

// @ 0x007EE450  register the volume-effect factory
extern void* g_1676498;
extern void* g_167649c;
extern uint32_t g_16764a8, g_16764ac;
extern "C" void RegisterVolumeFactory() {
  g_1676498 = (void*)&AllocVolumeEffect;
  extern void FUN_007edbc0();
  g_167649c = (void*)&FUN_007edbc0;
  g_16764a8 = 1;
  g_16764ac = 1;
}

// @ 0x007EE480  write a cVolumeDescription
extern "C" void WriteVolumeDescription(int iface, int* writer) {
  WriteBytes(writer, (void*)(iface + 8), 0xc);
  uint32_t zero = 0;
  EA::IO::WriteUint32(writer, &zero, 1, 0);
  EA::IO::WriteUint32(writer, &zero, 2, 0);
  int p = iface + 0x3c;
  int n = 8;
  do {
    WriteBytes(writer, (void*)(p - 0xc), 0xc);
    WriteBytes(writer, (void*)p, 0xc);
    p += 0x18;
    --n;
  } while (n != 0);
}

// @ 0x007EE540  cVolumeDescription::cVolumeDescription
SP::cVolumeDescription::cVolumeDescription() {
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

// @ 0x007EE630  SP::VolumeRead
extern "C" void* VolumeRead(int* reader) {
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

// @ 0x007EE6D0  copy six floats (user element-copy callback)
struct SixFloats {
  float v[6];
  void Assign(const SixFloats* src) {
    for (int i = 0; i < 6; ++i) v[i] = src->v[i];
  }
};
extern "C" void CopySix(void* dst, void* src) {
  ((SixFloats*)dst)->Assign((const SixFloats*)src);
}

// @ 0x007EE700  "alpha" command
extern "C" void VolumeAlphaCommand(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  int iface = **(int**)((char*)self + 4);
  *(float*)(*(char**)((char*)self + 0xc) + 0x2c) = ArgToFloat((void*)iface, *p);
}

// @ 0x007EE730  "color" command
extern "C" void VolumeColorCommand(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  int iface = **(int**)((char*)self + 4);
  Vec3f tmp;
  ArgToVec3((void*)iface, &tmp, *p);
  int dst = *(int*)((char*)self + 0xc);
  *(float*)(dst + 0x20) = tmp.x;
  *(float*)(dst + 0x24) = tmp.y;
  *(float*)(dst + 0x28) = tmp.z;
}

// @ 0x007EE780  "slicespacing" command
extern "C" void VolumeSliceSpacingCommand(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  int iface = **(int**)((char*)self + 4);
  *(float*)(*(char**)((char*)self + 0xc) + 0x1c) = ArgToFloat((void*)iface, *p);
}

// @ 0x007EE7B0  "material" command (resource id)
extern "C" void VolumeMaterialCommand(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  extern uint32_t HashName(const char*, uint32_t, int);   // 0x00932e80 (equiv t3)
  void* arg = *p;
  uint32_t h = HashName((const char*)arg, 0x811c9dc5, 1);
  int dst = *(int*)((char*)self + 0xc);
  *(uint32_t*)(dst + 0x30) = h;
  *(uint32_t*)(dst + 0x34) = 0;
}

// @ 0x007EE7F0  copy a cVolumeDescription (0xe8 bytes)
extern "C" void CopyVolumeDescription(int dst, int src) {
  for (int off = 8; off <= 0xe8; off += 4) *(uint32_t*)(dst + off) = *(uint32_t*)(src + off);
}

// @ 0x007EE9F0  cVolumeDescription copy-constructor
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
};
extern "C" void* MapDescriptionCopy(MapDescription* self, int src) {
  self->refcount = 0;
  self->f08 = *(uint32_t*)(src + 8);
  self->f0c = *(uint32_t*)(src + 0xc);
  self->f10 = *(uint32_t*)(src + 0x10);
  self->f14 = *(uint32_t*)(src + 0x14);
  self->f18 = *(uint32_t*)(src + 0x18);
  self->f1c = *(uint32_t*)(src + 0x1c);
  self->f20 = *(uint32_t*)(src + 0x20);
  self->f24 = *(uint32_t*)(src + 0x24);
  self->f28 = *(uint32_t*)(src + 0x28);
  self->f2c = *(uint32_t*)(src + 0x2c);
  extern void CopyArray(void*, void*, int, int, void*);
  CopyArray(&self->corners, (void*)(src + 0x30), 0x18, 8, (void*)&CopySix);
  return self;
}

// @ 0x007EEA90  cVolumeEffectCommand::OnRegister (register ArgScript commands)
struct CommandBase {
  void* vtable;
};
void CommandBaseCtor(CommandBase*);
extern "C" void VolumeEffectOnRegister(char* font, void* arg, int param3) {
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

// @ 0x007EEC80  register a cVolumeDescription on the manager (if newly created)
extern "C" void RegisterVolumeDescription(int self, char flag) {
  if (flag == 0) {
    char* p = (char*)operator new(0xf0, "Swarm", 0, 0, 0, 0);
    void* v = p ? MapDescriptionCopy((MapDescription*)p, self + 0x40) : 0;
    extern void FUN_00a6f9c0(int, int, void*);
    FUN_00a6f9c0(*(int*)(self + 0x130), 0x28, v);
  }
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void MainArguments(void*, int); // 0x00838020
};
}
