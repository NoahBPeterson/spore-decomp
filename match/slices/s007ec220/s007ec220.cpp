// Slice s007ec220: telemetry de/serialization plus Swarm-editor ArgScript
// command handlers (screen filter/length, terrain script) and text-font commands.
// Flags: /O2 /MD /Gy /EHsc /TP (x87 float copies: no /arch:SSE).
#include "types.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line);
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p); // 0x00f47380
void operator delete[](void* p);

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
struct cTelemetryItem {
  EA::DateTime::DateTime mSystemTime;  // +0x0
  uint32_t mType;                      // +0x8
  float* mDataBegin;                   // +0xc
  float* mDataEnd;                     // +0x10
  float* mDataCap;                     // +0x14
  const char* mDataName;               // +0x18
  uint32_t mDataFlags;                 // +0x1c
};
struct TItemListNode {
  TItemListNode* mpNext;  // +0x0
  TItemListNode* mpPrev;  // +0x4
  cTelemetryItem mValue;  // +0x8
};
struct TItemList {
  TItemListNode* mpNext;  // +0x0
  TItemListNode* mpPrev;  // +0x4
  uint32_t mnSize;        // +0x8
};
struct TItemMapNode {
  uint32_t mKey;         // +0x0
  TItemList mList;       // +0x4
  TItemMapNode* mpNext;  // +0x10
};
struct TItemMap {
  uint32_t mHash;               // +0x0
  TItemMapNode** mpBucketArray; // +0x4
  uint32_t mnBucketCount;       // +0x8
  uint32_t mnElementCount;      // +0xc
  float mfMaxLoadFactor;        // +0x10
  float mfGrowthFactor;         // +0x14
  uint32_t mnNextResize;        // +0x18
  uint32_t mAllocator;          // +0x1c
};
// The telemetry object whose map is being read/written.
struct cTelemetryReader {
  void* vtbl;                       // +0x0
  int32_t mRefCount;                // +0x4
  void* vtbl2;                      // +0x8
  TItemMap mStats;                  // +0xc
  int64_t mSession;                 // +0x30
  bool mbFileDump;                  // +0x38
  void* mpStream;                   // +0x3c
};
}  // namespace SP

// Helpers defined in slice s007eb430's translation unit (masked relocations).
SP::TItemMapNode* ItemMapIndex(SP::TItemMap* map, const uint32_t& key);  // 0x007EBFD0
SP::TItemListNode* ItemListAdd(SP::TItemList* list, SP::cTelemetryItem* item);  // 0x007EB720
void IntVecInsert(int* pos, uint32_t n, int* value);  // 0x007EB430

// @ 0x007EC220
// Telemetry deserialize: reads a version, then 7 buckets of telemetry items.
extern "C" int TelemetryRead(SP::cTelemetryReader* self, void* iface) {
  uint32_t version = 0xc;
  EA::IO::ReadInt32(TelemetryReader(iface), &version, 1, 0);
  uint32_t v = TelemetryVersion(iface);
  if (v < 0x1c0012)
    version = 9;
  else {
    v = TelemetryVersion(iface);
    if (v < 0x1c0013) version = 0xf;
  }
  uint32_t key = 7;
  if (version > 6) {
    do {
      SP::TItemMapNode* pNode = ItemMapIndex(&self->mStats, key);
      void* reader = TelemetryReader(iface);
      uint32_t count = 0;
      EA::IO::ReadInt32(reader, &count, 1, 0);
      uint32_t i = 0;
      if (count != 0) {
        do {
          SP::cTelemetryItem item;
          item.mSystemTime.Set(2);
          item.mDataBegin = 0;
          item.mDataEnd = 0;
          item.mDataCap = 0;
          SP::TItemListNode* pNew = ItemListAdd((SP::TItemList*)&pNode->mList, &item);
          pNew->mpNext = pNode->mList.mpNext;
          pNew->mpPrev = (SP::TItemListNode*)&pNode->mList;
          pNode->mList.mpNext->mpPrev = pNew;
          pNode->mList.mpNext = pNew;
          ++pNode->mList.mnSize;
          if (item.mDataBegin && *(uint32_t*)((char*)item.mDataBegin - 4))
            operator delete(item.mDataBegin); // 0x00f47380
          SP::TItemListNode* pItem = pNode->mList.mpNext;
          EA::IO::ReadInt32(TelemetryReader(iface), (char*)pItem + 0x10, 1, 0);
          int64_t time = 0;
          EA::IO::ReadTriple(TelemetryReader(iface), &time, 1, 0);
          uint32_t nData = 0;
          EA::IO::ReadInt32(TelemetryReader(iface), &nData, 1, 0);
          *(int64_t*)((char*)pItem + 8) = time;
          float* begin = *(float**)((char*)pItem + 0x14);
          float* end = *(float**)((char*)pItem + 0x18);
          uint32_t have = (uint32_t)(end - begin);
          if (have < nData) {
            int zero = 0;
            IntVecInsert((int*)end, nData - have, &zero);
          } else {
            *(float**)((char*)pItem + 0x18) = begin + nData;
          }
          WriteBytes(iface, begin, (int)(nData * 4));
          v = TelemetryVersion(iface);
          if (v < 0x230002 && key >= 7 && key <= 0xb) {
            float* e2 = *(float**)((char*)pItem + 0x18);
            uint32_t want = nData + 1;
            uint32_t have2 = (uint32_t)(e2 - *(float**)((char*)pItem + 0x14));
            if (have2 < want) {
              int zero = 0;
              IntVecInsert((int*)e2, want - have2, &zero);
            }
            *(float*)(*(float**)((char*)pItem + 0x14) + 0xb) = 10.0f;
          }
          ++i;
        } while (i < count);
      }
      ++key;
    } while (key <= version);
  }
  int64_t tail = 0;
  EA::IO::ReadTriple(TelemetryReader(iface), &tail, 1, 0);
  *(int64_t*)((char*)self + 0x28) = tail;
  return 1;
}

// @ 0x007EC550  eastl::uninitialized_copy<Vector3>
struct Vec3 {
  float x, y, z;
};
void CopyVec3Range(Vec3* first, Vec3* last, Vec3* result) {
  for (; first != last; first = (Vec3*)((char*)first + 0xc)) {
    if (result) {
      result->x = first->x;
      result->y = first->y;
      result->z = first->z;
    }
    result = (Vec3*)((char*)result + 0xc);
  }
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

// @ 0x007EC7F0  eastl::vector<Vector3>::DoInsertValues
struct Vec3VecFull {
  Vec3* mpBegin;  // +0x0
  Vec3* mpEnd;    // +0x4
  Vec3* mpCapacity;  // +0x8
  const char* mpName;  // +0xc
  uint32_t mFlags;     // +0x10
};
void Vec3Copy(Vec3* dst, Vec3* src) {
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
}
extern "C" void Vec3Insert(Vec3VecFull* v, Vec3* position, uint32_t n, Vec3* value) {
  uint32_t nPosition = (uint32_t)((char*)position - (char*)v->mpBegin) / 0xc;
  uint32_t nCount = (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc;
  if ((uint32_t)((char*)v->mpCapacity - (char*)v->mpEnd) / 0xc < n) {
    uint32_t nOldCap = (uint32_t)((char*)v->mpCapacity - (char*)v->mpBegin) / 0xc;
    uint32_t nNewCap = nOldCap * 2;
    if (nOldCap == 0) nNewCap = 1;
    uint32_t nNeed = nOldCap + n;
    if (nNeed < nNewCap) nNeed = nNewCap;
    Vec3* data = nNeed ? (Vec3*)operator new[](nNeed * 0xc, "App", 0, 0, "allocator.h", 0xd1) : 0;
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

// @ 0x007EC9E0  cGroupTerrainScriptCommand::Execute
extern "C" void GroupTerrainScriptExecute(int* self, EA::ArgScript::cArguments* args) {
  EA::ArgScript::MainArguments(args, 0);
  (void)self;
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
  if (count > 0) {
    uint32_t i = 0;
    uint32_t off = 0;
    do {
      Vec3* e = (Vec3*)((char*)v->mpBegin + off);
      e->x *= s;
      e->y *= s;
      e->z *= s;
      ++i;
      off += 0xc;
    } while (i < (uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) / 0xc);
  }
}

// @ 0x007ECCD0  register the ArgScript text commands (Font)
struct CommandBase {
  void* vtable;  // +0x0 (cCommandBase)
};
void CommandBaseCtor(CommandBase*);  // EA::ArgScript::cCommandBase::cCommandBase
struct Font {
  void* vtable;  // +0x0
  char pad[0x8];
};
extern "C" void FontSetupCommands(Font* font, int arg, int param3) {
  int v = (param3 == 0) ? 0 : param3 - 0xc;
  *(int*)((char*)font + 0x4) = v;
  extern void FUN_0083c780(int, int);
  FUN_0083c780(arg, param3);
  *(int*)((char*)font + 8) = (int)((char*)font + 0x8);
  (void)v;
}

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
