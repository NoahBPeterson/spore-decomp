// Slice s007ec220: telemetry de/serialization plus Swarm-editor ArgScript
// command handlers (screen filter/length, terrain script) and text-font commands.
// Flags: /O2 /MD /Gy /EHsc /TP (x87 float copies: no /arch:SSE).
#include "types.h"
#include <xmmintrin.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p);  // 0x00f47380

namespace EA {
namespace IO {
void ReadInt32(void* reader, void* dst, int n, int flags);
void WriteUint32(void* writer, void* src, int n, int flags);
void WriteUint16(void* writer, void* src, int n, int flags);
void ReadTriple(void* reader, void* dst, int n, int flags);  // 0x0093A800
}  // namespace IO
namespace DateTime {
class DateTime {
 public:
  int64_t mnSeconds;
  void Set(int);
};
}  // namespace DateTime
namespace ArgScript {
class cArguments;
void** MainArguments(cArguments* self, int n);
void** OptionArguments(cArguments* self, const char* name, int n);
bool HasFlag(cArguments* self, const char* name);
}  // namespace ArgScript
}  // namespace EA

// ---------------------------------------------------------------------------
// vtable-call helpers (offsets from the original disassembly).
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

static void* TelemetryReader(void* iface) {
  typedef void* (__thiscall * F0)(void*);
  void* a = ((F0)VSLOT(iface, 0x20))(iface);
  return ((F0)VSLOT(a, 0x18))(a);
}
static uint32_t TelemetryVersion(void* iface) {
  typedef uint32_t(__thiscall * F0)(void*);
  return ((F0)VSLOT(iface, 0x3c))(iface);
}
static float ArgToFloat(void* iface, void* arg) {
  typedef float(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0x98))(iface, arg);
}
static void ArgToVec3(void* iface, void* dst, void* arg) {
  typedef void*(__thiscall * F0)(void*, void*);
  ((F0)VSLOT(iface, 0xa4))(dst, arg);
}
static void WriteBytes(void* writer, void* p, int n) {
  typedef void(__thiscall *F0)(void*, void*, int);
  ((F0)VSLOT(writer, 0x38))(writer, p, n);
}

// ---------------------------------------------------------------------------
namespace SP {
class cTelemetryItem { public:
  EA::DateTime::DateTime mSystemTime;  // +0x0
  uint32_t mType;                      // +0x8
  float* mDataBegin;                   // +0xc
  float* mDataEnd;                     // +0x10
  float* mDataCap;                     // +0x14
  const char* mDataName;               // +0x18
  uint32_t mDataFlags;                 // +0x1c
  ~cTelemetryItem() {
    if (mDataBegin && *(uint32_t*)((char*)mDataBegin - 4)) ::operator delete(mDataBegin);
  }
};
struct TItemListNode;
// The bucket head is the node itself: list links live at node +0x0/+0x4 and
// the value at node +0x8 (see TItemList::AllocNode).
struct TItemList {
  TItemListNode* mpNext;  // +0x0
  TItemListNode* mpPrev;  // +0x4
  TItemListNode* AllocNode(const cTelemetryItem& item);  // 0x007EB720
};
struct TItemListNode {
  TItemListNode* mpNext;  // +0x0
  TItemListNode* mpPrev;  // +0x4
  cTelemetryItem mValue;  // +0x8
};
// eastl::vector<float>
struct VecFloat {
  float* mpBegin;     // +0x0
  float* mpEnd;       // +0x4
  float* mpCapacity;  // +0x8
  // eastl::vector<float>::DoInsertValues, 0x007EB430. VecFloat is a different type than the
  // SP::IntVector that the definition in the s007eb430 TU belongs to, so the original call names
  // the mangled symbol directly instead of resolving through the __thiscall helper it normally uses
  // for thiscall calls to mangled definitions (see 0x007EC220's call to 0x007EBFD0).
  void Insert(float* pos, uint32_t n, const float& value);  // 0x007EB430
};
struct TItemMap {
  uint32_t mHash;               // +0x0
  void** mpBucketArray;        // +0x4
  uint32_t mnBucketCount;       // +0x8
  uint32_t mnElementCount;      // +0xc
  float mfMaxLoadFactor;        // +0x10
  float mfGrowthFactor;         // +0x14
  uint32_t mnNextResize;        // +0x18
  uint32_t mAllocator;          // +0x1c
};
// The telemetry object whose map is being read/written.
struct cTelemetryReader {
  void* vtbl;                 // +0x0
  TItemMap mStats;            // +0x4
  uint32_t mPad24;            // +0x24
  int64_t mSession;           // +0x28
  char Read(void* iface);     // 0x007EC220
};
}  // namespace SP

// Defined in slice s007eb430's translation unit (masked relocations).
SP::TItemList* ItemMapIndex(SP::TItemMap* map, const uint32_t& key);  // 0x007EBFD0

// @ 0x007EC220
// Telemetry deserialize: reads a version, then buckets 7..version of telemetry items.
char SP::cTelemetryReader::Read(void* iface) {
  uint32_t sourceId;
  EA::IO::ReadInt32(TelemetryReader(iface), &sourceId, 1, 0);
  uint32_t version = 0xc;
  if (TelemetryVersion(iface) < 0x1c0012)
    version = 9;
  else if (TelemetryVersion(iface) < 0x1c0013)
    version = 0xf;
  for (uint32_t key = 7; key <= version; ++key) {
    SP::TItemList* pList = (SP::TItemList*)ItemMapIndex(&mStats, key);
    uint32_t count;
    EA::IO::ReadInt32(TelemetryReader(iface), &count, 1, 0);
    for (uint32_t i = 0; i < count; ++i) {
      SP::TItemListNode* pNew;
      {
        SP::cTelemetryItem item;
        item.mSystemTime.Set(2);
        item.mDataBegin = 0;
        item.mDataEnd = 0;
        item.mDataCap = 0;
        pNew = pList->AllocNode(item);
        pNew->mpNext = (SP::TItemListNode*)pList;
        pNew->mpPrev = pList->mpPrev;
        pNew->mpPrev->mpNext = pNew;
        pList->mpPrev = pNew;
      }
      EA::IO::ReadInt32(TelemetryReader(iface), &pNew->mValue.mType, 1, 0);
      int64_t time;
      EA::IO::ReadTriple(TelemetryReader(iface), &time, 1, 0);
      uint32_t nData;
      EA::IO::ReadInt32(TelemetryReader(iface), &nData, 1, 0);
      pNew->mValue.mSystemTime.mnSeconds = time;
      SP::VecFloat* vec = (SP::VecFloat*)&pNew->mValue.mDataBegin;
      uint32_t have = (uint32_t)(vec->mpEnd - vec->mpBegin);
      if (have < nData) {
        float zero = 0.0f;
        vec->Insert(vec->mpEnd, nData - have, zero);
      } else {
        vec->mpEnd = vec->mpBegin + nData;
      }
      ((void(__thiscall*)(void*, void*, int))VSLOT(iface, 0x34))(iface, vec->mpBegin,
                                                               (int)(nData * 4));
      if (TelemetryVersion(iface) <= 0x230001 && key >= 7 && key <= 0xb) {
        uint32_t want = nData + 1;
        uint32_t have2 = (uint32_t)(vec->mpEnd - vec->mpBegin);
        if (have2 < want) {
          float zero = 0.0f;
          vec->Insert(vec->mpEnd, want - have2, zero);
        } else {
          vec->mpEnd = vec->mpBegin + want;
        }
        vec->mpBegin[11] = 10.0f;
      }
    }
  }
  EA::IO::ReadTriple(TelemetryReader(iface), (char*)this + 0x28, 1, 0);
  return 1;
}

// @ 0x007EC550  eastl::uninitialized_copy<Vector3>
struct Vec3 {
  float x, y, z;
};
Vec3* CopyVec3Range(Vec3* first, Vec3* last, Vec3* result) {
  for (; first != last; first = (Vec3*)((char*)first + 0xc)) {
    if (result) {
      result->x = first->x;
      result->y = first->y;
      result->z = first->z;
    }
    result = (Vec3*)((char*)result + 0xc);
  }
  return result;
}

// @ 0x007EC580  write vector<Vector3> (element count then raw bytes)
struct Vec3Vec {
  Vec3* mpBegin;  // +0x0
  Vec3* mpEnd;    // +0x4
};
extern "C" void* WriteVec3Vec(void* writer, Vec3Vec* v) {
  uint32_t n = (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  EA::IO::WriteUint32(writer, &n, 1, 0);
  if (n != 0) {
    uint32_t off = 0;
    do {
      WriteBytes(writer, (char*)v->mpBegin + off, 0xc);
      off += 0xc;
      --n;
    } while (n != 0);
  }
  return writer;
}

// @ 0x007EC5E0  Swarm effect constructor (0x80 bytes)
struct SwarmEffect {
  virtual ~SwarmEffect();
  uint32_t f04, f08, f0c, f10, f14, f18, f1c, f20, f24;
  float f28;
  uint32_t f2c, f30, f34, f38, f3c, f40, f44, f48, f4c, f50, f54, f58, f5c,
      f60, f64, f68, f6c, f70, f74, f78, f7c;
  SwarmEffect();
  static void* operator new(size_t, void* p) { return p; }
};
extern int g_swarm_1667bac, g_swarm_1667bae, g_swarm_1639970, g_swarm_1639974;

SwarmEffect::SwarmEffect()
    : f04(0), f08(0),
      f0c((uint32_t)(size_t)&g_swarm_1667bac),
      f10((uint32_t)(size_t)&g_swarm_1667bac),
      f14((uint32_t)(size_t)&g_swarm_1667bae),
      f18(0), f1c(0), f20(0xffffffff), f24(0xffffffff), f28(12.0f),
      f2c(0xffffffff), f30(0xffffffff), f34(0xffffffff),
      f38((uint32_t)g_swarm_1639970), f3c((uint32_t)g_swarm_1639974),
      f40(0), f44(0), f48(0), f4c(0), f50(0), f54(0), f58(0), f5c(0),
      f60(0), f64(0), f68(0), f6c(0), f70(0), f74(0) {}

// @ 0x007EC660  Swarm effect destructor
SwarmEffect::~SwarmEffect() {
  if (f6c && *(int*)(f6c - 4)) operator delete((void*)f6c);
  if (f58 && *(int*)(f58 - 4)) operator delete((void*)f58);
  if (f44 && *(int*)(f44 - 4)) operator delete((void*)f44);
  if (f0c && (int)((f14 - f0c) & 0xfffffffe) > 2) operator delete((void*)f0c);
}

// @ 0x007EC6D0  serialize a Swarm effect
extern "C" void WriteSwarmEffect(void* writer, char* e) {
  uint32_t t = *(uint32_t*)(e + 8);
  EA::IO::WriteUint32(writer, &t, 1, 0);
  int32_t n = (*(int*)(e + 0x10) - *(int*)(e + 0xc)) >> 1;
  t = (uint32_t)n;
  EA::IO::WriteUint32(writer, &t, 1, 0);
  EA::IO::WriteUint16(writer, *(void**)(e + 0xc), n, 0);
  int64_t v = *(int64_t*)(e + 0x20);
  EA::IO::WriteUint32(writer, &v, 1, 0);
  EA::IO::WriteUint32(writer, &v, 2, 0);
  t = *(uint32_t*)(e + 0x28);
  EA::IO::WriteUint32(writer, &t, 1, 0);
  v = *(int64_t*)(e + 0x30);
  EA::IO::WriteUint32(writer, &v, 2, 0);
  WriteBytes(writer, e + 0x38, 8);
  uint32_t zero = 0;
  EA::IO::WriteUint32(writer, &zero, 1, 0);
  WriteVec3Vec(writer, (Vec3Vec*)(e + 0x44));
  extern void WritePlane(void*, void*);  // 0x007D0250
  WritePlane(writer, e + 0x58);
  WritePlane(writer, e + 0x6c);
}

// eastl::vector<Vector3>::DoInsertValues (0x007EC7F0)
struct Vec3VecFull {
  Vec3* mpBegin;  // +0x0
  Vec3* mpEnd;    // +0x4
  Vec3* mpCapacity;  // +0x8
  const char* mpName;  // +0xc
  uint32_t mFlags;     // +0x10
  void Vec3Insert(Vec3* position, uint32_t n, Vec3* value);
};
void Vec3Copy(Vec3* dst, Vec3* src) {
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
}
// @ 0x007EC7F0
void Vec3VecFull::Vec3Insert(Vec3* position, uint32_t n, Vec3* value) {
  Vec3VecFull* v = this;
  uint32_t nPosition = (uint32_t)((char*)position - (char*)v->mpBegin) / 0xc;
  uint32_t nCount = (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  if ((uint32_t)((char*)v->mpCapacity - (char*)v->mpEnd) / 0xc < n) {
    uint32_t nOldCap = (uint32_t)((char*)v->mpCapacity - (char*)v->mpBegin) / 0xc;
    uint32_t nNewCap = nOldCap * 2;
    if (nOldCap == 0) nNewCap = 1;
    uint32_t nNeed = nOldCap + n;
    if (nNeed < nNewCap) nNeed = nNewCap;
    Vec3* data = nNeed ? (Vec3*)operator new[](nNeed * 0xc, "App", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    Vec3* d = data;
    for (Vec3* p = v->mpBegin; p != position; ++p, ++d) Vec3Copy(d, p);
    for (uint32_t i = 0; i < n; ++i, ++d) Vec3Copy(d, value);
    for (Vec3* p = position; p != v->mpEnd; ++p, ++d) Vec3Copy(d, p);
    if (v->mpBegin) operator delete(v->mpBegin);
    v->mpBegin = data;
    v->mpEnd = d;
    v->mpCapacity = data + nNeed;
  } else {
    uint32_t nAfter = nCount - nPosition;
    if (n >= nAfter) {
      Vec3* pOldEnd = v->mpEnd;
      uint32_t nNew = n - nAfter;
      v->mpEnd = v->mpEnd + nNew;
      for (uint32_t i = 0; i < nNew; ++i) Vec3Copy(pOldEnd + i, value);
      for (uint32_t i = 0; i < nAfter; ++i) Vec3Copy(v->mpEnd + i, position + i);
      for (uint32_t i = 0; i < nAfter; ++i) Vec3Copy(position + i, value);
    } else {
      Vec3* pOldEnd = v->mpEnd;
      uint32_t nMove = nAfter - n;
      for (uint32_t i = nMove; i > 0; --i) Vec3Copy(pOldEnd + i - 1 + n, pOldEnd + i - 1);
      for (uint32_t i = 0; i < n; ++i) Vec3Copy(position + i, value);
      v->mpEnd = pOldEnd + n;
    }
  }
}

// (declaration of the GroupModelCommand command type below)
struct GroupModelCommand {
  char pad0[0x10];
  void Execute(void* args);
};
struct cError {
  cError(const char* msg);  // 0x0052DF30
};
typedef void** (__thiscall* ArgsFn)(void*, void*, int, int);
typedef void** (__thiscall* Void2Fn)(void*, const char*, int);
void WStr_Format(void* dst, const void* fmt, int arg);  // 0x0041E050
// Refcount guard: releases the Swarm effect (running its destructor at zero) when
// the scope is left, including via the cError throw.
struct EffGuard {
  SwarmEffect* p;
  ~EffGuard() {
    if (p && --p->f04 == 0) {
      p->f04 = 1;
      ((void(__thiscall*)(void*, int))VSLOT(p, 0))(p, 1);
    }
  }
};
// @ 0x007EC9E0
// thiscall member-call handles for the parser / effect-parser entry points.
struct ArgsOps {
  void** MainArguments(void* out, int minArgs, int maxArgs);  // 0x838020
  void** OptionArguments(const char* name, int n);            // 0x838330
  char HasFlag(const char* name);                            // 0x8380b0
};
struct EffParserOps {
  void AddDescription(void* args, void* argv, int a, int b);      // 0xa6fc30
  void AddAnonDescription(void* args, int a, void* eff, int b);   // 0xa6fd40
};
void GroupModelCommand::Execute(void* args) {
  void* subArgs;
  GroupModelCommand* cmd = this;
  ArgsOps* A = (ArgsOps*)args;
  void** p = A->MainArguments(&subArgs, 0, 0x7fffffff);
  if (subArgs == 0) {
    SwarmEffect* eff = (SwarmEffect*)operator new(0x80, (const char*)0x13f1fdc, 0, 0, 0, 0);
    if (eff) new ((void*)eff) SwarmEffect();  // 0x007EC5E0
    if (eff) ++eff->f04;
    {
      EffGuard guard = {eff};
      void** opt = A->OptionArguments((const char*)0x1408a34, 1);
      if (!opt) throw cError("Need at least -string for anonymous text effect");
      WStr_Format((char*)eff + 0xc, (const void*)0x13f3da0, (int)*opt);
      void** q = A->OptionArguments((const char*)0x13f293c, 1);
      if (q) eff->f28 = ArgToFloat(*(void**)((char*)this + 4), *q);
      if (A->HasFlag((const char*)0x14143bc)) eff->f08 |= 1;
      ((EffParserOps*)*(void**)((char*)this + 0xc))->AddAnonDescription(args, 0x2f, eff, 0);
    }
    return;
  }
  ((EffParserOps*)*(void**)((char*)cmd + 0xc))->AddDescription(args, *p, 0x2f, 0);
}

// @ 0x007ECB50  cScreenFilterTextureCommand::Execute
struct ScreenEffect {
  char pad[0x50];
};
extern "C" void ScreenFilterTextureExecute(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  uint32_t count = *(uint32_t*)p;
  ScreenEffect* fx = *(ScreenEffect**)((char*)self + 0xc);
  extern void Vec3Resize(ScreenEffect*, uint32_t);
  Vec3Resize(fx, count);
  void** o = EA::ArgScript::OptionArguments(args, "factor", 1);
  if (o) *(float*)((char*)fx + 0x30) = ArgToFloat(*(void**)((char*)self + 4), *o);
}

// @ 0x007ECBB0  cScreenLengthCommand::Execute
extern "C" void ScreenLengthExecute(int* self, EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  float f = ArgToFloat(*(void**)((char*)self + 4), *p);
  ScreenEffect* fx = *(ScreenEffect**)((char*)self + 0xc);
  if (f <= 1e-06f)
    *(uint32_t*)((char*)fx + 0x48) = 0;
  else
    *(float*)((char*)fx + 0x48) = 1.0f / f;
  if (EA::ArgScript::HasFlag(args, "sustain")) *(uint32_t*)((char*)fx + 0x10) |= 2;
}

// @ 0x007ECC30  scale a vector<Vector3> by a factor
void ScaleVec3Vec(float s, Vec3Vec* v) {
  int32_t count = (int32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  if (count != 0) {
    uint32_t i = 0;
    uint32_t off = 0;
    __m128 sv = _mm_load_ss(&s);
    do {
      Vec3* e = (Vec3*)((char*)v->mpBegin + off);
      _mm_store_ss(&e->x, _mm_mul_ss(_mm_load_ss(&e->x), sv));
      _mm_store_ss(&e->y, _mm_mul_ss(_mm_load_ss(&e->y), sv));
      _mm_store_ss(&e->z, _mm_mul_ss(_mm_load_ss(&e->z), sv));
      ++i;
      off += 0xc;
    } while (i < (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc);
  }
}

// @ 0x007ECCD0  EA::Text::Font::SetupCommands: register the ArgScript text commands
struct cCommandBase {  // EA::ArgScript::cCommandBase
  void* vtable;        // +0x0
  void* mpField4;      // +0x4
  void* mpField8;      // +0x8
  void* mpFieldC;      // +0xc
};
extern const char* g_cmdname_153fd40;  // "string"
extern const char* g_cmdname_153fd44;  // "font"
extern const char* g_cmdname_153fd48;  // "style"
extern const char* g_cmdname_153fd4c;  // "life"
extern const char* g_cmdname_153fd50;  // "color"
extern const char* g_cmdname_153fd54;  // "colour"
extern const char* g_cmdname_153fd58;  // "color255"
extern const char* g_cmdname_153fd5c;  // "colour255"
extern const char* g_cmdname_153fd60;  // "alpha"
extern const char* g_cmdname_153fd64;  // "alpha255"
extern const char* g_cmdname_153fd68;  // "size"
extern char g_vtbl_cmd_string;    // 0x014143EC
extern char g_vtbl_cmd_font;      // 0x01414404
extern char g_vtbl_cmd_life;      // 0x0141441C
extern char g_vtbl_cmd_color;     // 0x01414434
extern char g_vtbl_cmd_alpha;     // 0x0141444C
extern char g_vtbl_cmd_size;      // 0x01414464

// Returns the cCommandBase subobject of the freshly allocated command (esi in the original).
cCommandBase* CommandBaseCtor(void* cmd);  // 0x0083C800
typedef void(__thiscall* RegFn)(void*, void*, cCommandBase*);
typedef void(__thiscall* CmdRegFn)(void*, const char*, void*);

struct Font {
  char pad0[0x30];
  void* mState;       // +0x30
  char pad34[0x4];    // +0x34
  char mUserData[0xc];// +0x38
  void SetupCommands(void* parser, char* state);
};

#define REGISTER_TEXT_CMD(type_, vtbl_, name_)                        \
  {                                                                   \
    cCommandBase* c = (cCommandBase*)::operator new(0x10, type_, 0, 0, 0, 0); \
    if (c) {                                                          \
      c = CommandBaseCtor(c);                                         \
      c->vtable = (void*)&vtbl_;                                      \
    }                                                                 \
    ((CmdRegFn)VSLOT(self, 0x18))(self, name_, c);                    \
  }

void Font::SetupCommands(void* parser, char* state) {
  cCommandBase* self = (cCommandBase*)this;
  ((Font*)self)->mState = state ? state - 0xc : 0;
  ((RegFn)0x83c780)(self, parser, (cCommandBase*)state);  // cCommandBase::Register
  ((void(__thiscall*)(void*, char*))0xfd9450)(self, ((Font*)self)->mUserData);
  (void)parser;
  REGISTER_TEXT_CMD("ArgScript/TextString", g_vtbl_cmd_string, g_cmdname_153fd40);
  REGISTER_TEXT_CMD("ArgScript/TextFont", g_vtbl_cmd_font, g_cmdname_153fd44);
  REGISTER_TEXT_CMD("ArgScript/TextStyle", g_vtbl_cmd_font, g_cmdname_153fd48);
  REGISTER_TEXT_CMD("ArgScript/TextLife", g_vtbl_cmd_life, g_cmdname_153fd4c);
  REGISTER_TEXT_CMD("ArgScript/TextColor", g_vtbl_cmd_color, g_cmdname_153fd50);
  REGISTER_TEXT_CMD("ArgScript/TextColor255", g_vtbl_cmd_color, g_cmdname_153fd58);
  REGISTER_TEXT_CMD("ArgScript/TextColour", g_vtbl_cmd_color, g_cmdname_153fd54);
  REGISTER_TEXT_CMD("ArgScript/TextColour255", g_vtbl_cmd_color, g_cmdname_153fd5c);
  REGISTER_TEXT_CMD("ArgScript/TextAlpha", g_vtbl_cmd_alpha, g_cmdname_153fd60);
  REGISTER_TEXT_CMD("ArgScript/TextAlpha255", g_vtbl_cmd_alpha, g_cmdname_153fd64);
  REGISTER_TEXT_CMD("ArgScript/TextSize", g_vtbl_cmd_size, g_cmdname_153fd68);
}
#undef REGISTER_TEXT_CMD

// @ 0x007ED090  EA::Swarm::cSphereSurface::ParseExtraOptions
struct SphereSurface {
  char pad[0x50];
};
extern "C" void SphereSurfaceParseExtraOptions(SphereSurface* self,
                                               EA::ArgScript::cArguments* args) {
  void** p = EA::ArgScript::MainArguments(args, 1);
  if (p) {
    extern void WStringAssign(void* dst, void* arg);   // 0x0041e050 (equiv t3)
    WStringAssign((char*)self + 0x14, *p);
  }
  p = EA::ArgScript::OptionArguments(args, "radius", 1);
  if (p) {
    extern void Vec3Resize(SphereSurface*, uint32_t);
    Vec3Resize(self, *(uint32_t*)p);
  }
  p = EA::ArgScript::OptionArguments(args, "factor", 1);
  if (p) {
    void* iface = *(void**)((char*)self + 0x4);
    *(float*)((char*)self + 0x30) = ArgToFloat(iface, *p);
  }
  p = EA::ArgScript::OptionArguments(args, "offset", 1);
  if (p) {
    void* iface = *(void**)((char*)self + 0x4);
    Vec3 tmp;
    ArgToVec3(iface, &tmp, *p);
    *(float*)((char*)self + 0x40) = tmp.x;
    *(float*)((char*)self + 0x44) = tmp.y;
  }
}
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void MainArguments(void*, int); // 0x00838020
};
}
