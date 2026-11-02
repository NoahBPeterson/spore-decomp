// src/game/SPGonzago/SPGonzagoDebug.cpp -- migrated from slice(s) s007ec220, s0061d240 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoDebug.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cError.h"
#include <xmmintrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)
#pragma intrinsic(memmove)

// ---- items of slice s0061d240 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
namespace SP {
namespace Pollen {
struct String8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
  String8* erase(unsigned int position, unsigned int n);
};
}
}
// ---- items of slice s0061d240 end

// ---- items of slice s007ec220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_swarm_1667bac, g_swarm_1667bae, g_swarm_1639970, g_swarm_1639974;
#undef REGISTER_TEXT_CMD
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p);  // 0x00f47380
namespace EA {
namespace IO {
void WriteUint32(void* writer, void* src, int n, int flags);
}
}
namespace EA {
namespace IO {
void WriteUint16(void* writer, void* src, int n, int flags);
}
}
namespace EA {
namespace ArgScript {
class cArguments_s007e_c220;
}
}
namespace EA {
namespace ArgScript {
void** MainArguments(cArguments_s007e_c220* self, int n);
}
}
namespace EA {
namespace ArgScript {
void** OptionArguments(cArguments_s007e_c220* self, const char* name, int n);
}
}
namespace EA {
namespace ArgScript {
bool HasFlag(cArguments_s007e_c220* self, const char* name);
}
}
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
static float ArgToFloat(void* iface, void* arg) {
  typedef float(__thiscall * F0)(void*, void*);
  return ((F0)VSLOT(iface, 0x98))(iface, arg);
}
static void WriteBytes(void* writer, void* p, int n) {
  typedef void(__thiscall *F0)(void*, void*, int);
  ((F0)VSLOT(writer, 0x38))(writer, p, n);
}
struct Vec3 {
  float x, y, z;
};
struct Vec3Vec {
  Vec3* mpBegin;  // +0x0
  Vec3* mpEnd;    // +0x4
};
struct SwarmEffect {
  virtual ~SwarmEffect();
  uint32_t f04, f08, f0c, f10, f14, f18, f1c, f20, f24;
  float f28;
  uint32_t f2c, f30, f34, f38, f3c, f40, f44, f48, f4c, f50, f54, f58, f5c,
      f60, f64, f68, f6c, f70, f74, f78, f7c;
  SwarmEffect();
  static void* operator new(size_t, void* p) { return p; }
};
struct Vec3VecFull {
  Vec3* mpBegin;  // +0x0
  Vec3* mpEnd;    // +0x4
  Vec3* mpCapacity;  // +0x8
  const char* mpName;  // +0xc
  uint32_t mFlags;     // +0x10
  uint32_t Vec3Insert(Vec3* position, uint32_t n, Vec3* value);
};
void Vec3Copy(Vec3* dst, Vec3* src) {
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
}
struct GroupModelCommand {
  char pad0[0x10];
  void Execute(void* args);
};
struct cError_s007e_c220 {
  cError_s007e_c220(const char* msg);  // 0x0052DF30
};
void WStr_Format(void* dst, const void* fmt, int arg);  // 0x0041E050
struct EffGuard {
  SwarmEffect* p;
  ~EffGuard() {
    if (p && --p->f04 == 0) {
      p->f04 = 1;
      ((void(__thiscall*)(void*, int))VSLOT(p, 0))(p, 1);
    }
  }
};
struct ArgsOps {
  void** MainArguments(void* out, int minArgs, int maxArgs);  // 0x838020
  void** OptionArguments(const char* name, int n);            // 0x838330
  char HasFlag(const char* name);                            // 0x8380b0
};
struct EffParserOps {
  void AddDescription(void* args, void* argv, int a, int b);      // 0xa6fc30
  void AddAnonDescription(void* args, int a, void* eff, int b);   // 0xa6fd40
};
    void operator delete(void*); // 0x00f47380
// ---- items of slice s007ec220 end

// @ 0x0061e200
namespace SP { namespace Pollen {
String8* String8::erase(unsigned int position, unsigned int n)
{
  unsigned int nRemaining = (unsigned int)(mpEnd - mpBegin) - position;
  if (n > nRemaining) n = nRemaining;
  char* pDst = mpBegin + position;
  char* pSrc = pDst + n;
  if (pDst != pSrc) {
    memmove(pDst, pSrc, (mpEnd - pSrc) + 1);
    mpEnd = (char*)mpEnd + (pDst - pSrc);
  }
  return this;
}
}}  // namespace SP::Pollen

// @ 0x007ec550
Vec3* CopyVec3Range(Vec3* first, Vec3* last, Vec3* result)
{
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

// @ 0x007ec580
extern "C" void* WriteVec3Vec(void* writer, Vec3Vec* v)
{
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

// @ 0x007ec5e0
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

// @ 0x007ec660
SwarmEffect::~SwarmEffect()
{
  if (f6c && *(int*)(f6c - 4)) operator delete((void*)f6c);
  if (f58 && *(int*)(f58 - 4)) operator delete((void*)f58);
  if (f44 && *(int*)(f44 - 4)) operator delete((void*)f44);
  if (f0c && (int)((f14 - f0c) & 0xfffffffe) > 2) operator delete((void*)f0c);
}

// @ 0x007ec6d0
extern "C" void WriteSwarmEffect(void* writer, char* e)
{
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

// @ 0x007ec7f0
uint32_t Vec3VecFull::Vec3Insert(Vec3* position, uint32_t n, Vec3* value)
{
  Vec3VecFull* v = this;
  // The original divides the byte distances as *signed* ptrdiff_t by 12 (0x2aaaaaab magic).
  uint32_t nCount = (uint32_t)(int32_t)(((intptr_t)v->mpEnd - (intptr_t)v->mpBegin) / 0xc);
  uint32_t nFree = (uint32_t)(int32_t)(((intptr_t)v->mpCapacity - (intptr_t)v->mpEnd) / 0xc);
  if (nFree < n) {
    // eastl reallocation: the new capacity is twice the current *size* (1 when empty),
    // and the allocation must cover at least size + n elements.
    uint32_t nNewCap = nCount * 2;
    if (nCount == 0) nNewCap = 1;
    uint32_t nNeed = nCount + n;
    if (nNeed < nNewCap) nNeed = nNewCap;
    Vec3* data = nNeed ? (Vec3*)operator new[](nNeed * 0xc, "App", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    Vec3* d = data;
    for (Vec3* p = v->mpBegin; p != position; ++p, ++d) Vec3Copy(d, p);
    for (uint32_t i = 0; i < n; ++i, ++d) Vec3Copy(d, value);
    for (Vec3* p = position; p != v->mpEnd; ++p, ++d) Vec3Copy(d, p);
    if (v->mpBegin && *(uint32_t*)((char*)v->mpBegin - 4)) operator delete(v->mpBegin);
    v->mpBegin = data;
    v->mpEnd = d;
    v->mpCapacity = data + nNeed;
    return nNeed;
  }
  if (n == 0) return nFree;
  // The in-place paths snapshot the value before touching the array.
  Vec3 saved = *value;
  uint32_t nAfter = (uint32_t)(int32_t)(((intptr_t)v->mpEnd - (intptr_t)position) / 0xc);
  if (n >= nAfter) {
    Vec3* pOldEnd = v->mpEnd;
    uint32_t nNew = n - nAfter;
    for (uint32_t i = 0; i < nNew; ++i) Vec3Copy(pOldEnd + i, &saved);
    v->mpEnd = pOldEnd + nNew;
    for (uint32_t i = 0; i < nAfter; ++i) Vec3Copy(v->mpEnd + i, position + i);
    v->mpEnd = pOldEnd + n;
    for (uint32_t i = 0; i < nAfter; ++i) Vec3Copy(position + i, &saved);
    return (uint32_t)(uintptr_t)pOldEnd;
  } else {
    Vec3* pOldEnd = v->mpEnd;
    // (1) move the top n elements into the newly exposed tail
    for (uint32_t i = 0; i < n; ++i) Vec3Copy(pOldEnd + i, pOldEnd - n + i);
    v->mpEnd = pOldEnd + n;
    // (2) shift [position, oldEnd - n) right by n (copy_backward)
    uint32_t nMove = nAfter - n;
    for (uint32_t i = nMove; i > 0; --i)
      Vec3Copy(position + i - 1 + n, position + i - 1);
    // (3) fill the gap
    for (uint32_t i = 0; i < n; ++i) Vec3Copy(position + i, &saved);
    return (uint32_t)(uintptr_t)(position + n);
  }
}

// @ 0x007ec9e0
void GroupModelCommand::Execute(void* args)
{
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
      if (!opt) throw cError_s007e_c220("Need at least -string for anonymous text effect");
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
