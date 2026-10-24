// src/game/SPEngine/SPAppVolumeDescription.cpp -- migrated from slice(s) s007eed10, s007ee060 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppVolumeDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cArguments.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s007ee060 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CommandBase {
  void* vtable;
};
void CommandBaseCtor(CommandBase*);
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
static void* ArgToVec3(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0xb0))(dst, arg);
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
}
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
// The live effect state edited by the volume ArgScript commands (VolumeCmd's +0x0c target).
struct VolumeEffectParams {
  uint8_t mUnknown00[0x1c]; // +0x00
  float mSliceSpacing;      // +0x1c
  Vec3f mColor;             // +0x20
  float mAlpha;             // +0x2c
};
struct VolumeCmd {
  uint8_t mUnknown00[0x04];    // +0x00
  void* mArgConverter;         // +0x04  ArgScript value converter (vtable +0x98 float, +0xb0 Vec3)
  uint8_t mUnknown08[0x04];    // +0x08
  VolumeEffectParams* mParams; // +0x0c  live effect being edited
  void Alpha(EA::ArgScript::cArguments_s007e_e060* args);
  void Color(EA::ArgScript::cArguments_s007e_e060* args);
  void SliceSpacing(EA::ArgScript::cArguments_s007e_e060* args);
};struct MapDescription {
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
struct VolumeRegistrar {
  void Register(char flag);
};
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007ee060 end

// ---- items of slice s007eed10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  cErrorCtor(void* buf, const char* msg);   // 0x0052df30
extern void  CxxThrow(void* obj, void* info);          // 0x011e0912
extern char  TypeInfo_cError;                          // 0x014f9174
struct HeapNode {
  double d;
  uint32_t x, y;
};
inline bool operator<(const HeapNode& a, const HeapNode& b) { return a.d < b.d; }
struct EString {
  char* mpBegin;  // +0
  char* mpEnd;    // +4
  char* mpCap;    // +8
  ~EString() {
    if (mpCap - mpBegin > 1 && mpBegin != 0) operator delete[](mpBegin);
  }
};
struct cVolumeDescLite {
  virtual ~cVolumeDescLite() {}
  int mRef;
};
struct cBlockCommandBase {
  virtual ~cBlockCommandBase() throw();   // 0x0083cd90
  char pad[0x34];
};
struct cVolumeStateLite {
  char pad[8];
  cVolumeDescLite mDesc;   // +0x40 in the derived object
  void InitDesc(const void* src);   // 0x007ee7f0
  char pad2[0x130 - 0x48];
};
struct cVolumeEffectCommand : cBlockCommandBase {
  cVolumeStateLite mVolumeState;  // +0x38
  EString mDescName;              // +0x130
  virtual void Execute(void* args);
};
struct ArgErrBuf { void* m[4]; };
#define ARG_THROW(msg) do { ArgErrBuf _eb; cErrorCtor(&_eb, (msg)); CxxThrow(&_eb, (void*)&TypeInfo_cError); } while (0)
namespace EA {
namespace ArgScript {
  int ParseEnum(void* s, const char* name);                      // 0x00840bb0
}
}
namespace EA {
namespace ArgScript {
  struct cArguments_s007e_ed10 {
    void* MainArguments(int* out, int a, int b);                 // 0x00838020
  };
}
}
namespace EA {
namespace Swarm {
  class cEffectsParser { public:
    void* GetInheritedDescription(void* args, int n, int size);  // 0x00a6f090
  };
}
}
namespace SP {
  struct cVolumeDescription_s007e_ed10 {
    cVolumeDescription_s007e_ed10();                                        // 0x007ee540
    char pad[0x24];
  };
}
struct EStringLite {
  void assign(const char* first, const char* last);              // 0x00454cb0
};
struct cVolumeSetCommand {
  virtual void Execute(EA::ArgScript::cArguments_s007e_ed10* args);
};
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
  char const* const* p = ((EA::ArgScript::cArguments*)args)->MainArguments(1);
  mParams->mAlpha = ArgToFloat(mArgConverter, (void*)const_cast<char*>(*p));
}

// @ 0x007ee730
void VolumeCmd::Color(EA::ArgScript::cArguments_s007e_e060* args)
{
  char const* const* p = ((EA::ArgScript::cArguments*)args)->MainArguments(1);
  Vec3f tmp;
  Vec3f* r = (Vec3f*)ArgToVec3(mArgConverter, &tmp, (void*)const_cast<char*>(*p));
  mParams->mColor = *r;
}

// @ 0x007ee7b0
extern "C" void VolumeMaterialCommand(int* self, EA::ArgScript::cArguments_s007e_e060* args)
{
  char const* const* p = ((EA::ArgScript::cArguments*)args)->MainArguments(1);
  extern uint32_t HashName(const char*, uint32_t, int);   // 0x00932e80 (equiv t3)
  void* arg = (void*)const_cast<char*>(*p);
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

// @ 0x007ee9f0
// 0x007EE6D0: the element-copy callback vector() invokes (thiscall, ecx=dst).
void FUN_007ee6d0();
void* MapDescription::Copy(int src)
{
  MapDescription* self = this;
  self->refcount = 0;
  self->vt = (void*)0x01453948;
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
  extern void __stdcall CopyArray(void*, void*, int, int, void*);
  CopyArray(&self->corners, (void*)(src + 0x30), 0x18, 8, (void*)&FUN_007ee6d0);
  return self;
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
void cVolumeSetCommand::Execute(EA::ArgScript::cArguments_s007e_ed10* args)
{
  int count;
  char** a = (char**)args->MainArguments(&count, 2, 8);
  int sel = EA::ArgScript::ParseEnum(a[0], "corner");
  void* mgr = *(void**)((char*)this + 4);
  char* data = *(char**)((char*)this + 0xc);
  switch (sel) {
  case 0: {
    if (count < 5) ARG_THROW("Wrong number of arguments.");
    unsigned n = ((unsigned(__thiscall*)(void*, void*))VSLOT(mgr, 0xa0))(mgr, a[1]);
    unsigned m = n;
    if ((int)n > 8) {
      m = 0;
      if (n & 1) m = 1;
      if (((int)n / 10) & 1) m |= 2;
      if ((int)n >= 100) m |= 4;
    }
    float f4 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[4]);
    float f3 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[3]);
    float f2 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[2]);
    unsigned off = m * 0x18;
    *(float*)(data + off + 0x38) = f2;
    *(float*)(data + off + 0x3c) = f3;
    *(float*)(data + off + 0x40) = f4;
    if (count >= 8) {
      float g7 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[7]);
      float g6 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[6]);
      float g5 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[5]);
      *(float*)(data + off + 0x44) = g5;
      *(float*)(data + off + 0x48) = g7;
      *(float*)(data + off + 0x4c) = g6;
    }
    break;
  }
  case 1: {
    if (count < 2) ARG_THROW("Wrong number of arguments.");
    float v = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[1]);
    *(float*)(data + 0x40) = v;
    *(float*)(data + 0x58) = v;
    *(float*)(data + 0x70) = v;
    *(float*)(data + 0x88) = v;
    if (count >= 3) {
      float w = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[2]);
      *(float*)(data + 0x4c) = w;
      *(float*)(data + 0x64) = w;
      *(float*)(data + 0x7c) = w;
      *(float*)(data + 0x94) = w;
    }
    break;
  }
  case 2: {
    if (count < 2) ARG_THROW("Wrong number of arguments.");
    float v = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[1]);
    *(float*)(data + 0xa0) = v;
    *(float*)(data + 0xb8) = v;
    *(float*)(data + 0xd0) = v;
    *(float*)(data + 0xe8) = v;
    if (count >= 3) {
      float w = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[2]);
      *(float*)(data + 0xac) = w;
      *(float*)(data + 0xc4) = w;
      *(float*)(data + 0xdc) = w;
      *(float*)(data + 0xf4) = w;
    }
    break;
  }
  case 3: {
    if (count < 2) ARG_THROW("Wrong number of arguments.");
    float h = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[1]) * 0.5f;
    *(float*)(data + 0x38) = -h;
    *(float*)(data + 0x3c) = -h;
    *(float*)(data + 0x50) = h;
    *(float*)(data + 0x54) = -h;
    *(float*)(data + 0x68) = -h;
    *(float*)(data + 0x6c) = h;
    *(float*)(data + 0x80) = h;
    *(float*)(data + 0x84) = h;
    *(float*)(data + 0x98) = -h;
    *(float*)(data + 0x9c) = -h;
    *(float*)(data + 0xb0) = h;
    *(float*)(data + 0xb4) = -h;
    *(float*)(data + 0xc8) = -h;
    *(float*)(data + 0xcc) = h;
    *(float*)(data + 0xe0) = h;
    *(float*)(data + 0xe4) = h;
    break;
  }
  default:
    break;
  }
}

// @ 0x007ef080
void cVolumeEffectCommand::Execute(void* args)
{
  int count = 0;
  char** a = (char**)((EA::ArgScript::cArguments_s007e_ed10*)args)->MainArguments(&count, 1, 3);
  const char* s = a[0];
  const char* e = s;
  while (*e != 0) ++e;
  ((EStringLite*)((char*)this + 0x130))->assign(s, e);
  SP::cVolumeDescription_s007e_ed10 tmp;
  void* t = &tmp;
  mVolumeState.InitDesc(t);
  if (count > 1) {
    void* inh = ((EA::Swarm::cEffectsParser*)(*(void**)((char*)this + 0x30)))->GetInheritedDescription(a, count, 0x28);
    if (inh) mVolumeState.InitDesc(inh);
  }
  void* mgr = *(void**)((char*)this + 4);
  ((void(__thiscall*)(void*, void*))VSLOT(mgr, 0x8c))(mgr, this);
}

// @ 0x007ef220
void rwForceEmit_cVolumeEffectCommand_sdtor() { (void)new cVolumeEffectCommand; }   // forces ??_GcVolumeEffectCommand@@UAEPAXI@Z (the slice's markerless ForceVolumeEffectNew did this)
void ForceVolumeEffect(cVolumeEffectCommand* p)
{
  delete p;
}
