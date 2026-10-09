// Slice s007ed1b0: EA::Swarm effect (`cDistributeEffect`-family) internals:
// scale-curve vector ops, ArgScript parameter commands (color/scale/etc.),
// effect read/write, transforms, and the effect object ctor/dtor/update.
// Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p); // 0x00f47380
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
extern "C" void* memcpy(void* d, const void* s, unsigned int n);

namespace EA {
namespace IO {
void ReadInt32(void* r, void* d, int n, int f);
void ReadTriple(void* r, void* d, int n, int f);
}  // namespace IO
namespace ArgScript {
class cArguments;
void** MainArguments(cArguments* self, int n);
void** OptionArguments(cArguments* self, const char* name, int n);
bool HasFlag(cArguments* self, const char* name);
char* GetArg(cArguments* self, int i);
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

struct Vec3 {
  float x, y, z;
};
struct Vec3Vec {
  Vec3* mpBegin;     // +0x0
  Vec3* mpEnd;       // +0x4
  Vec3* mpCapacity;  // +0x8
};

// @ 0x007ED1B0  EA::Swarm::ScaleCurve
extern "C" void ScaleCurve(Vec3Vec* v, Vec3* pos, Vec3* value) {
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

// @ 0x007ED2E0  register the "TextEffect" ArgScript command
struct CommandBase {
  void* vtable;
};
void CommandBaseCtor(CommandBase*);
extern int g_swarm_1667bac, g_swarm_1667bad;
extern "C" void RegisterTextEffect(void* reg, void* parser) {
  char* obj = (char*)operator new(0xd8, "ArgScript/TextEffect", 0, 0, 0, 0);
  if (obj) {
    // vector<float> ctor + vtable + fields (see 0x007EC5E0)
    *(uint32_t*)(obj + 0xe * 4) = 0x6254f2e;
    extern void SwarmEffect(void*);
    SwarmEffect(obj);
    *(uint32_t*)(obj + 0x32 * 4) = (uint32_t)(size_t)&g_swarm_1667bac;
    *(uint32_t*)(obj + 0x33 * 4) = (uint32_t)(size_t)&g_swarm_1667bac;
    *(uint32_t*)(obj + 0x34 * 4) = (uint32_t)(size_t)&g_swarm_1667bad;
  }
  void* cmd = operator new(0x10, "ArgScript/GroupText", 0, 0, 0, 0);
  CommandBaseCtor((CommandBase*)cmd);
  (void)reg;
  (void)parser;
}

// @ 0x007ED3E0  vector<Vec3>::push_back
extern "C" void Vec3PushBack(Vec3Vec* v, Vec3* value) {
  Vec3* p = v->mpEnd;
  if (p < v->mpCapacity) {
    v->mpEnd = p + 1;
    if (p != 0) {
      *p = *value;
      return;
    }
  } else {
    ScaleCurve(v, value, value);
  }
}

// @ 0x007ED490  "color" command
extern "C" void ColorCommand(int* self, EA::ArgScript::cArguments* args) {
  void* list = EA::ArgScript::MainArguments(args, 0);
  int count = 0;
  (void)list;
  (void)count;
  Vec3Vec* v = (Vec3Vec*)(*(char**)((char*)self + 0xc) + 0x4c);
  v->mpEnd = v->mpBegin;
  for (int i = 0; i < count; ++i) {
    Vec3 tmp;
    ArgToVec3(*(void**)((char*)self + 4), &tmp, 0);
    Vec3PushBack(v, &tmp);
  }
  (void)args;
}

// @ 0x007ED560  float-vector command (engine scale)
extern "C" void FloatListCommand(int* self, EA::ArgScript::cArguments* args) {
  EA::ArgScript::MainArguments(args, 0);
  (void)self;
}

// @ 0x007ED670  float-vector command with parentScale flag
extern "C" void FloatListParentCommand(int* self, EA::ArgScript::cArguments* args) {
  EA::ArgScript::MainArguments(args, 0);
  if (EA::ArgScript::HasFlag(args, "parentScale"))
    *(uint32_t*)(*(char**)((char*)self + 0xc) + 0x10) |= 1;
}

// @ 0x007ED740  copy effect description fields
extern "C" int CopyEffectDesc(char* dst, char* src) {
  *(uint32_t*)(dst + 8) = *(uint32_t*)(src + 8);
  if (src + 0xc != dst + 0xc) {
    extern void StringAssign(void*, void*);
    StringAssign(*(void**)(src + 0xc), *(void**)(src + 0x10));
  }
  for (int off = 0x20; off <= 0x40; off += 4) *(uint32_t*)(dst + off) = *(uint32_t*)(src + off);
  extern void CopyVec(void*, void*);
  CopyVec(src + 0x44, dst + 0x44);
  CopyVec(src + 0x58, dst + 0x58);
  CopyVec(src + 0x6c, dst + 0x6c);
  return (int)dst;
}

// @ 0x007ED7C0  construct effect from another
extern "C" char* CloneEffect(char* dst, char* src) {
  *(uint32_t*)(dst + 4) = 0;
  *(uint32_t*)(dst + 8) = *(uint32_t*)(src + 8);
  *(uint32_t*)(dst + 0xc) = 0;
  *(uint32_t*)(dst + 0x10) = 0;
  *(uint32_t*)(dst + 0x14) = 0;
  void* pv = *(void**)(src + 0xc);
  uint32_t n = (uint32_t)(*(int*)(src + 0x10) - (int)pv) >> 1;
  extern void* AllocStr(uint32_t);
  void* d = AllocStr(n + 1);
  memcpy(d, pv, n * 2);
  *(uint32_t*)(dst + 0xc) = (uint32_t)(size_t)d;
  *(uint32_t*)(dst + 0x10) = (uint32_t)(size_t)((char*)d + n * 2);
  *(uint16_t*)((char*)d + n * 2) = 0;
  for (int off = 0x20; off <= 0x40; off += 4) *(uint32_t*)(dst + off) = *(uint32_t*)(src + off);
  extern void CloneTail(char*, char*);
  CloneTail(dst, src);
  return dst;
}

// @ 0x007ED920  read vector<Vec3>
extern "C" void* ReadVec3Vec(void* reader, Vec3Vec* v) {
  uint32_t n = 0;
  EA::IO::ReadInt32(reader, &n, 1, 0);
  extern void Vec3Resize(Vec3Vec*, uint32_t);
  Vec3Resize(v, n);
  uint32_t i = 0;
  while (i < n) {
    typedef void(__thiscall * F0)(void*, void*, int);
    ((F0)VSLOT(reader, 0x30))(reader, (char*)v->mpBegin + i * 0xc, 0xc);
    ++i;
  }
  return reader;
}

// @ 0x007ED980  "effect" command execute
extern "C" void EffectCommand(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  (void)p;
  (void)self;
}

// @ 0x007EDA60  sync inherited description
extern "C" void SyncInherited(int self, char flag) {
  if (flag == 0) {
    void* obj = operator new(0x80, "Swarm", 0, 0, 0, 0);
    (void)obj;
  }
}

// @ 0x007EDAF0  read an effect from a stream
extern "C" void ReadEffect(void* reader, void* unused, char* dst) {
  uint32_t flags = 0;
  EA::IO::ReadInt32(reader, &flags, 1, 0);
  *(uint32_t*)(dst + 8) = flags & 0xf;
  uint32_t n = 0;
  EA::IO::ReadInt32(reader, &n, 1, 0);
  extern void WStringResize(void*, uint32_t);
  WStringResize(dst, n);
  extern void ReadRaw(void*, void*, uint32_t, int);   // 0x0093a700 (equiv t3)
  ReadRaw(reader, *(void**)(dst + 0xc), n, 0);
  EA::IO::ReadTriple(reader, dst + 0x20, 1, 0);
  EA::IO::ReadInt32(reader, dst + 0x28, 1, 0);
  EA::IO::ReadTriple(reader, dst + 0x30, 1, 0);
  typedef void(__thiscall * F0)(void*, void*, int);
  ((F0)VSLOT(reader, 0x30))(reader, dst + 0x38, 8);
  EA::IO::ReadInt32(reader, dst + 0x40, 1, 0);
  ReadVec3Vec(reader, (Vec3Vec*)(dst + 0x44));
  extern void ReadPlaneVec(void*, void*);   // 0x007d27d0 (equiv t3)
  ReadPlaneVec(reader, dst + 0x58);
  ReadPlaneVec(reader, dst + 0x6c);
}

// @ 0x007EDC40  set member from vcall (3-arg callback ABI: ret 0xc)
struct VcallHolder {
  char pad[0x14];
  void SetFromVcall(void* a, void* b, void* c);
};
void VcallHolder::SetFromVcall(void* a, void* b, void* c) {
  typedef uint32_t(__thiscall * F0)(void*);
  *(uint32_t*)((char*)this + 0x10) = ((F0)VSLOT(a, 0x20))(a);
}

// @ 0x007EDC70  set an enable flag
struct FlagSub {  // object at [this+0x10]
  void Recv(uint32_t a, uint32_t v);
};
struct FlagHolder {
  char pad[0x10];
  FlagSub* f10;   // +0x10
  uint8_t f14;    // +0x14
  uint8_t f15;    // +0x15
  uint32_t f18;   // +0x18
  void SetFlag(uint32_t v);
};
void FlagHolder::SetFlag(uint32_t v) {
  f15 = (uint8_t)v;
  if (f14 != 0) f10->Recv(f18, v);
}

// @ 0x007EDC90  destructor
extern "C" void EffectDtor(void** self) {
  if (self[0x11]) {
    typedef void(__thiscall * F0)(void*);
    ((F0)VSLOT(self[0x11], 4))(self[0x11]);
  }
  extern void StringBase(void*);
  StringBase((char*)self + 0xc);
}

// @ 0x007EDD10  activate
extern "C" void Activate(int self) {
  if (*(char*)(self + 0x14) == 0) {
    int p = *(int*)(self + 0xc);
    *(char*)(self + 0x14) = 1;
    if ((*(uint32_t*)(p + 0x20) & *(uint32_t*)(p + 0x24)) != 0xffffffff) {
      extern void StringLoad(int, uint64_t);
      StringLoad(self + 0x30, 0);
    }
  }
}

// @ 0x007EDD50  deactivate
struct DeactSub {
  void Recv(int a);
};
struct ActiveObject {
  char pad[0x10];
  DeactSub* f10;  // +0x10
  uint8_t f14;    // +0x14
  uint8_t f15;
  int32_t f18;  // +0x18
  void Deactivate(int unused);
};
void ActiveObject::Deactivate(int unused) {
  if (f14 != 0) {
    f14 = 0;
    if (f18 >= 0) {
      f10->Recv(f18);
      f18 = -1;
    }
  }
}

// @ 0x007EDD80  update
extern "C" void EffectUpdate(int self) {
  int p = *(int*)(self + 0x44);
  uint16_t val;
  if (p == 0) {
    p = *(int*)(self + 0xc);
    if ((*(uint32_t*)(p + 0x20) & *(uint32_t*)(p + 0x24)) == 0xffffffff) return;
    val = 0;
  } else {
    val = *(uint16_t*)(p + 0xc);
  }
  int q = *(int*)(self + 0xc);
  extern char FUN_006f1770(int, int, int, int, int);
  char ok = FUN_006f1770(val, *(int*)(q + 0x30), *(int*)(q + 0x34), *(int*)(q + 0x28),
                         self + 0x18);
  if (ok) {
    extern void Propagate(int, uint32_t);
    Propagate(*(int*)(self + 0x18), *(uint8_t*)(self + 0x15));
  }
}

// @ 0x007EDDE0  constructor
struct EffectObject {
  void* vt;  // +0x0
  void* vt2;
  uint32_t f08;
  uint32_t f0c;
  uint32_t f10;
  uint8_t f14;
  uint8_t f15;
  int32_t f18;
  float f1c;
  uint32_t f20;
  uint32_t f24;
  uint32_t f28;
  uint32_t f2c;
  char cString[0x14];  // +0x30
  uint32_t f44;
  EffectObject(void* p);
};
extern "C" EffectObject* EffectObjectCtor(EffectObject* self, void* p) {
  self->f08 = 0;
  self->f1c = 1.0f;
  self->f0c = (uint32_t)(size_t)p;
  self->f10 = 0;
  self->f14 = 0;
  self->f15 = 1;
  self->f18 = -1;
  self->f20 = 0;
  self->f24 = 0;
  self->f28 = 0;
  self->f2c = 0;
  self->f44 = 0;
  return self;
}

// @ 0x007EDEB0  transform update
extern "C" void TransformUpdate(char* self, char* src, uint8_t* params) {
  *(uint32_t*)(self + 0x20) = *(uint32_t*)(src + 4);
  *(uint32_t*)(self + 0x24) = *(uint32_t*)(src + 8);
  *(uint32_t*)(self + 0x28) = *(uint32_t*)(src + 0xc);
  if ((*params & 2) != 0) {
    float m1 = *(float*)(self + 0x24), m2 = *(float*)(self + 0x28), m0 = *(float*)(self + 0x20);
    float p7 = *(float*)(params + 0x24), p8 = *(float*)(params + 0x18);
    float p3 = *(float*)(params + 0x30), p4 = *(float*)(params + 0x1c);
    float p5 = *(float*)(params + 0x28), p6 = *(float*)(params + 0x34);
    *(float*)(self + 0x20) =
        (*(float*)(params + 0x20) * m1 + *(float*)(params + 0x2c) * m2) +
        *(float*)(params + 0x14) * m0;
    *(float*)(self + 0x24) = (p8 * m0 + p7 * m1) + p3 * m2;
    *(float*)(self + 0x28) = (p4 * m0 + p5 * m1) + p6 * m2;
  }
  float s = *(float*)(params + 0x10);
  float y = s * *(float*)(self + 0x24);
  *(float*)(self + 0x24) = y;
  float z = s * *(float*)(self + 0x28);
  *(float*)(self + 0x28) = z;
  float x = *(float*)(self + 0x20) * s;
  *(float*)(self + 0x20) = x;
  *(float*)(self + 0x20) = x + *(float*)(params + 4);
  *(float*)(self + 0x24) = *(float*)(params + 8) + y;
  *(float*)(self + 0x28) = *(float*)(params + 0xc) + z;
  if ((*(uint8_t*)(*(int*)(self + 0xc) + 8) & 1) != 0)
    *(float*)(self + 0x1c) = *(float*)(src + 0x10) * *(float*)(params + 0x10);
}

// @ 0x007EDFF0  message handler
extern "C" uint32_t EffectHandler(int self, int msg, int* obj) {
  uint32_t eax = 0;
  if (msg == 8) {
    typedef int*(__thiscall * F0)(void*);
    int* p = ((F0)VSLOT(obj, 0xc))(0);
    int* old = *(int**)(self + 0x44);
    if (p != old) {
      if (p) ((void(__thiscall*)(void*))VSLOT(p, 0))(p);
      *(int**)(self + 0x44) = p;
      if (old) ((void(__thiscall*)(void*))VSLOT(old, 4))(old);
    }
    eax = *(uint32_t*)(self + 0x18);
    if ((int)eax >= 0) {
      extern void FUN_006ee940(int);
      FUN_006ee940(eax);
      *(int*)(self + 0x18) = -1;
      EffectUpdate(self);
      eax = *(uint32_t*)(self + 0x18);
    }
  }
  return eax & 0xffffff00;
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
