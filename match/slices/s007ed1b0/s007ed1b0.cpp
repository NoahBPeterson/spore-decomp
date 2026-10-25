// Slice s007ed1b0: EA::Swarm effect (`cDistributeEffect`-family) internals:
// scale-curve vector ops, ArgScript parameter commands (color/scale/etc.),
// effect read/write, transforms, and the effect object ctor/dtor/update.
// Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line); // 0x00f473a0
void operator delete(void* p, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // matching placement delete
void operator delete(void* p); // 0x00f47380
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
extern "C" void* memcpy(void* d, const void* s, unsigned int n);
extern "C" __declspec(dllimport) char* __cdecl StrStr(const char* s, const char* sub); // IAT strstr
extern "C" size_t __cdecl strlen(const char* s);
extern const float kInv255;   // 0x13eecd4  0.003921569f

namespace EA {
namespace IO {
void ReadInt32(void* r, void* d, int n, int f);
void ReadTriple(void* r, void* d, int n, int f);
}  // namespace IO
namespace ArgScript {
class cArguments {
 public:
  char** MainArguments(int* count, int minCount, int maxCount);  // 0x00838020
  char* operator[](int index);                                  // 0x00837f20
  bool HasFlag(const char* name);                               // 0x008380b0
};
}  // namespace ArgScript
}  // namespace EA

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
static float ArgToFloat(void* iface, void* arg) {
  typedef float(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0x98))(iface, arg);
}
static void* ArgToVec3(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*, void*);
  return ((F0)VSLOT(iface, 0xb0))(iface, dst, arg);
}

struct Vec3 {
  float x, y, z;
};
struct Vec3Vec {
  Vec3* mpBegin;     // +0x0
  Vec3* mpEnd;       // +0x4
  Vec3* mpCapacity;  // +0x8
  void PushBack(Vec3* value);
  void ScaleCurve(Vec3* pos, Vec3* value);
  void erase(Vec3* first, Vec3* last);   // 0x009E0480
};

// float vector embedded in an effect description (eastl::vector<float>)
struct FloatVec {
  float* mpBegin;      // +0x00
  float* mpEnd;        // +0x04
  float* mpCapacity;   // +0x08
  void erase(float* first, float* last);
  void push_back(const float& value);
  void push_back_slow(float* end, const float& value);   // 0x00455660
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  float& operator[](uint32_t i) { return mpBegin[i]; }
};
void __cdecl ScaleVec3Vec(float scale, Vec3Vec* vec);            // 0x007ECC30

// description shared by the ArgScript effect commands (0x80 bytes)
struct EffectDesc {
  void*    vt;           // +0x00
  uint32_t f04;          // +0x04
  uint32_t f08;          // +0x08
  uint32_t f0c;          // +0x0c
  uint32_t mFlags;       // +0x10
  uint32_t f14;          // +0x14
  uint32_t f18;          // +0x18
  uint32_t f1c;          // +0x1c
  uint32_t f20;          // +0x20
  uint32_t f24;          // +0x24
  uint32_t f28;          // +0x28
  uint32_t f2c;          // +0x2c
  uint32_t f30;          // +0x30
  uint32_t f34;          // +0x34
  uint32_t f38;          // +0x38
  uint32_t f3c;          // +0x3c
  uint32_t f40;          // +0x40
  uint32_t f44;          // +0x44
  uint32_t f48;          // +0x48
  Vec3Vec  mColorVec;    // +0x4c
  uint32_t f58;          // +0x58
  uint32_t f5c;          // +0x5c
  FloatVec mScaleVec;    // +0x60
  uint32_t f6c;          // +0x6c
  uint32_t f70;          // +0x70
  FloatVec mParentVec;   // +0x74
  EffectDesc();                           // 0x007EC5E0
  ~EffectDesc();                          // 0x007EC660
  EffectDesc(const EffectDesc& x);        // 0x007ED7C0
  int CopyFrom(const EffectDesc& other);  // 0x007ED740
};

inline void FloatVec::erase(float* first, float* last) {
  memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
  mpEnd = mpEnd - (last - first);
}
inline void FloatVec::push_back(const float& value) {
  if (mpEnd < mpCapacity) {
    float* p = mpEnd;
    mpEnd = p + 1;
    if (p != 0) *p = value;
  } else {
    push_back_slow(mpEnd, value);
  }
}

// command objects registered by the "effect" script command
struct string8 {
  char* mpBegin;      // +0x00
  char* mpEnd;        // +0x04
  char* mpCapacity;   // +0x08
  uint32_t mAllocator; // +0x0c
  void assign(const char* first, const char* last);   // 0x00454CB0
};
struct CommandBaseA {
  // implicit vptr at +0x00
  void* mIface;        // +0x04
  uint32_t f08;        // +0x08
  uint32_t f0c;        // +0x0c
  uint32_t f10;        // +0x10
  uint32_t f14;        // +0x14
  uint32_t f18;        // +0x18
  uint32_t f1c;        // +0x1c
  uint32_t f20;        // +0x20
  uint32_t f24;        // +0x24
  uint32_t f28;        // +0x28
  virtual void Execute(EA::ArgScript::cArguments* args);
  CommandBaseA();      // 0x0083CDD0
};
struct CommandBaseB {
  // implicit vptr at +0x00
  uint32_t f04;        // +0x04
  uint32_t f08;        // +0x08
  uint32_t f0c;        // +0x0c
  virtual void Execute(EA::ArgScript::cArguments* args);
  CommandBaseB();      // 0x0083C800
};
struct EffectsParser {
  EffectDesc* GetInheritedDescription(char** args, int count, int flag); // 0x00A6F090
  void RegisterInherited(const char* name, int flag, EffectDesc* desc);  // 0x00A6F9C0
};
extern void* g_vtTextEffect;     // 0x014143C8
extern void* g_vtGroupText;      // 0x01414370
extern char  g_emptyString;      // 0x01667BAC
extern char  g_emptyStringEnd;   // 0x01667BAD
extern void* g_scriptGlobals;    // 0x0153FD3C

struct U32Init {
  uint32_t v;
  U32Init(uint32_t x) : v(x) {}
};

struct TextEffectCommand : CommandBaseA {
  uint32_t f2c;          // +0x2c
  void* mParser;         // +0x30
  uint32_t f34;          // +0x34
  U32Init f38;           // +0x38
  uint32_t f3c;          // +0x3c
  EffectDesc mDesc;      // +0x40
  void* mParserCopy;     // +0xc0
  uint32_t fC4;          // +0xc4
  string8 mString;       // +0xc8
  __forceinline TextEffectCommand() : f38(0x6254f2e) {
    mString.mpBegin = &g_emptyString;
    mString.mpEnd = &g_emptyString;
    mString.mpCapacity = &g_emptyStringEnd;
  }
  void EffectCommand(EA::ArgScript::cArguments* args);   // 0x007ED980
  void SyncInherited(char flag);                         // 0x007EDA60
};

struct GroupTextCommand : CommandBaseB {
  GroupTextCommand() {}
};

// command object whose description is shared through +0xc
struct BattleCommand {
  void* vt;               // +0x00
  void* mIface;           // +0x04
  void* mField8;          // +0x08
  EffectDesc* mDesc;      // +0x0c
  void ColorCommand(EA::ArgScript::cArguments* args);           // 0x007ED490
  void FloatListCommand(EA::ArgScript::cArguments* args);       // 0x007ED560
  void FloatListParentCommand(EA::ArgScript::cArguments* args); // 0x007ED670
};

// @ 0x007ED1B0  EA::Swarm::ScaleCurve
void Vec3Vec::ScaleCurve(Vec3* pos, Vec3* value) {
  Vec3Vec* v = this;
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
  Vec3* data = cap ? (Vec3*)operator new[](cap * 0xc, "App", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
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
void __cdecl RegisterTextEffect(void* cmdReg, void* effectReg) {
  typedef void(__thiscall * F0)(void*, void*, void*);
  TextEffectCommand* effect =
      new ("ArgScript/TextEffect", 0, 0, 0, 0) TextEffectCommand;
  ((F0)VSLOT(effectReg, 0x14))(effectReg, g_scriptGlobals, effect);

  GroupTextCommand* cmd =
      new ("ArgScript/GroupText", 0, 0, 0, 0) GroupTextCommand;
  ((F0)VSLOT(cmdReg, 0x18))(cmdReg, g_scriptGlobals, cmd);
}

// @ 0x007ED3E0  vector<Vec3>::push_back
void Vec3Vec::PushBack(Vec3* value) {
  Vec3Vec* v = this;
  Vec3* p = v->mpEnd;
  if (p < v->mpCapacity) {
    v->mpEnd = p + 1;
    if (p != 0) {
      p->x = value->x;
      p->y = value->y;
      p->z = value->z;
      return;
    }
  } else {
    ScaleCurve(p, value);
  }
}

// inlined copy of Vec3Vec::PushBack for the command Execute bodies
inline void PushBackInline(Vec3Vec* v, Vec3* value) {
  Vec3* p = v->mpEnd;
  if (p < v->mpCapacity) {
    v->mpEnd = p + 1;
    if (p != 0) {
      p->x = value->x;
      p->y = value->y;
      p->z = value->z;
      return;
    }
  } else {
    v->ScaleCurve(p, value);
  }
}

// @ 0x007ED490  "color" command
void BattleCommand::ColorCommand(EA::ArgScript::cArguments* args) {
  int count;
  char** list = args->MainArguments(&count, 1, 0x7fffffff);
  Vec3Vec& colors = mDesc->mColorVec;
  colors.erase(colors.mpBegin, colors.mpEnd);
  Vec3 tmp;
  for (int i = 0; i < count; ++i) {
    Vec3* value = (Vec3*)ArgToVec3(mIface, &tmp, list[i]);
    PushBackInline(&mDesc->mColorVec, value);
  }
  char* text = (*args)[0];
  if (StrStr(text, "255") != 0)
    ScaleVec3Vec(kInv255, &mDesc->mColorVec);
}

// @ 0x007ED560  float-vector command (engine scale)
void BattleCommand::FloatListCommand(EA::ArgScript::cArguments* args) {
  int count;
  char** list = args->MainArguments(&count, 1, 0x7fffffff);
  FloatVec& sv = mDesc->mScaleVec;
  sv.erase(sv.mpBegin, sv.mpEnd);
  for (int i = 0; i < count; ++i)
    mDesc->mScaleVec.push_back(ArgToFloat(mIface, list[i]));
  char* text = (*args)[0];
  if (StrStr(text, "255") != 0) {
    const float k = kInv255;
    FloatVec& v = mDesc->mScaleVec;
    for (uint32_t i = 0; i < v.size(); ++i) v[i] *= k;
  }
}

// @ 0x007ED670  float-vector command with parentScale flag
void BattleCommand::FloatListParentCommand(EA::ArgScript::cArguments* args) {
  int count;
  char** list = args->MainArguments(&count, 0, 0x7fffffff);
  FloatVec& pv = mDesc->mParentVec;
  pv.erase(pv.mpBegin, pv.mpEnd);
  for (int i = 0; i < count; ++i) {
    float value = ArgToFloat(mIface, list[i]);
    mDesc->mParentVec.push_back(value);
  }
  if (args->HasFlag("parentScale"))
    mDesc->mFlags |= 1;
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
void TextEffectCommand::EffectCommand(EA::ArgScript::cArguments* args) {
  int count;
  char** list = args->MainArguments(&count, 1, 3);
  char* text = list[0];
  mString.assign(text, text + strlen(text));
  mDesc.CopyFrom(EffectDesc());
  mParserCopy = mParser;
  if (count > 1) {
    EffectDesc* inherited =
        ((EffectsParser*)mParser)->GetInheritedDescription(list, count, 0x2f);
    if (inherited != 0)
      mDesc.CopyFrom(*inherited);
  }
  typedef void(__thiscall * F0)(void*, void*);
  ((F0)VSLOT(mIface, 0x8c))(mIface, this);
}

// @ 0x007EDA60  sync inherited description
void TextEffectCommand::SyncInherited(char flag) {
  if (flag == 0) {
    EffectDesc* cloned = new ("Swarm", 0, 0, 0, 0) EffectDesc(mDesc);
    ((EffectsParser*)mParser)->RegisterInherited(mString.mpBegin, 0x2f, cloned);
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

extern void* gEffectVtable;                 // 0x01414618  GmeIComponent vtable (ctor)
extern void* gEffectModifierVtable;         // 0x01414614  SP::Audio::IEventModifier vtable (ctor)
extern void* gEffectFinalVtable;            // 0x013f21d4  GmeIComponent vtable (destroyed)
extern void* gEffectModifierFinalVtable;    // 0x013ef094  SP::Audio::IEventModifier vtable (destroyed)
extern float gEffectExtent[3];              // 0x01639c18  default extents (x, y, z)
extern void StringCtor();                   // 0x006b5060  cString::cString
extern void StringDtor();                   // 0x006b5240  cString::~cString

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
  float f20;
  float f24;
  float f28;
  float f2c;
  char cString[0x14];  // +0x30
  uint32_t f44;
  EffectObject* Init(void* p);
  void Destroy();
  void Update();
  bool Handler(int msg, int* obj);
};

// @ 0x007EDC90  destructor
void EffectObject::Destroy() {
  void** self = (void**)this;
  *(void**)self = &gEffectVtable;
  *(void**)((char*)self + 4) = &gEffectModifierVtable;
  if (self[0x11]) {
    typedef void(__thiscall * F0)(void*);
    ((F0)VSLOT(self[0x11], 4))(self[0x11]);
  }
  typedef void(__thiscall * FStr)(void*);
  ((FStr)&StringDtor)((char*)self + 0x30);
  *(void**)self = &gEffectFinalVtable;
  *(void**)((char*)self + 4) = &gEffectModifierFinalVtable;
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
void EffectObject::Update() {
  int self = (int)(size_t)this;
  int p = *(int*)(self + 0x44);
  uint32_t idx;
  if (p != 0) {
    idx = *(uint32_t*)(p + 0xc);
  } else {
    p = *(int*)(self + 0xc);
    if ((*(uint32_t*)(p + 0x20) & *(uint32_t*)(p + 0x24)) == 0xffffffff) {
      idx = *(uint32_t*)(p + 0xc);
    } else {
      typedef int (__thiscall * FText)(void*);
      extern int StringGetText();  // 0x006b55c0  cString::GetText
      idx = (uint32_t)((FText)&StringGetText)((char*)self + 0x30);
    }
  }
  int q = *(int*)(self + 0xc);
  typedef bool (__thiscall * FAdd)(void*, uint32_t, int, int, float, int*);
  extern bool FUN_006f1770();  // 0x006f1770
  bool ok = ((FAdd)&FUN_006f1770)(*(void**)(self + 0x10), idx, *(int*)(q + 0x30),
                                  *(int*)(q + 0x34), *(float*)(q + 0x28),
                                  (int*)(self + 0x18));
  if (ok) {
    typedef void (__thiscall * FProp)(void*, int, uint8_t);
    extern void FUN_006e7aa0();  // 0x006e7aa0
    ((FProp)&FUN_006e7aa0)(*(void**)(self + 0x10), *(int*)(self + 0x18),
                           *(uint8_t*)(self + 0x15));
  }
}

// @ 0x007EDDE0  constructor
EffectObject* EffectObject::Init(void* p) {
  EffectObject* self = this;
  *(void**)self = &gEffectVtable;
  *(void**)((char*)self + 4) = &gEffectModifierVtable;
  self->f08 = 0;
  self->f1c = 1.0f;
  self->f0c = (uint32_t)(size_t)p;
  self->f10 = 0;
  self->f14 = 0;
  self->f15 = 1;
  self->f18 = -1;
  self->f20 = gEffectExtent[0];
  self->f24 = gEffectExtent[1];
  self->f28 = gEffectExtent[2];
  self->f2c = 0.0f;
  typedef void(__thiscall * FStr)(void*);
  ((FStr)&StringCtor)((char*)self + 0x30);
  self->f44 = 0;
  return self;
}

// @ 0x007EDEB0  transform update
struct TransformObj {
  void Update(char* src, uint8_t* params);
};
void TransformObj::Update(char* src, uint8_t* params) {
  char* self = (char*)this;
  *(uint32_t*)(self + 0x20) = *(uint32_t*)(src + 4);
  *(uint32_t*)(self + 0x24) = *(uint32_t*)(src + 8);
  *(uint32_t*)(self + 0x28) = *(uint32_t*)(src + 0xc);
  if ((*params & 2) != 0) {
    float m1 = *(float*)(self + 0x24), m2 = *(float*)(self + 0x28), m0 = *(float*)(self + 0x20);
    *(float*)(self + 0x20) =
        (*(float*)(params + 0x20) * m1 + *(float*)(params + 0x2c) * m2) +
        *(float*)(params + 0x14) * m0;
    *(float*)(self + 0x24) =
        (*(float*)(params + 0x18) * m0 + *(float*)(params + 0x24) * m1) +
        *(float*)(params + 0x30) * m2;
    *(float*)(self + 0x28) =
        (*(float*)(params + 0x1c) * m0 + *(float*)(params + 0x28) * m1) +
        *(float*)(params + 0x34) * m2;
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
bool EffectObject::Handler(int msg, int* obj) {
  int self = (int)(size_t)this;
  if (msg == 8) {
    typedef int* (__thiscall * F0)(void*, int);
    int* p = ((F0)VSLOT(obj, 0xc))(obj, 0);
    int* old = *(int**)(self + 0x44);
    if (p != old) {
      if (p) ((void(__thiscall*)(void*))VSLOT(p, 0))(p);
      *(int**)(self + 0x44) = p;
      if (old) ((void(__thiscall*)(void*))VSLOT(old, 4))(old);
    }
    uint32_t eax = *(uint32_t*)(self + 0x18);
    if ((int)eax >= 0) {
      typedef void (__thiscall * F1)(void*, int);
      extern void FUN_006ee940();  // 0x006ee940
      ((F1)&FUN_006ee940)(*(void**)(self + 0x10), eax);
      *(int*)(self + 0x18) = -1;
      Update();
    }
  }
  return false;
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
