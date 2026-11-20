// @ 0x00e255c0
// Flags: /O2 /Ob2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// cSPUIPosseItem constructor taking an owner object, a name string (hashed with FNV-1a into
// +0x54) and a caller type id kept at +0x5c beside the class type constant at +0x58.  Two base
// vptrs seeded by the inlined base constructors (a cResource at +0x04, a cListenerBase at +0x0c)
// are overwritten by the three derived vptrs, then the owner reference, the embedded layout
// object and the two inline-buffer vectors are initialised.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13eb384[];
extern "C" char g_13fa72c[];
extern "C" char g_148058c[];
extern "C" char g_148059c[];
extern "C" char g_14805b8[];
extern "C" char g_16ac238[];

#include "game/types.h"
#include <intrin.h>

typedef unsigned int  u32;
typedef unsigned char u8;
typedef void (__thiscall* TFv)(void*);

struct LayoutCtorC { void ctor(); };                    // 0x00810000  embedded layout constructor

u32 __cdecl FNV1_String16(const void* pName, u32 basis, int lower);   // 0x00932f30

struct cSPUIPosseItem_s00e255c0 {
  void* ctor(void* pOwner, const void* pName, u32 typeId);
};

void* cSPUIPosseItem_s00e255c0::ctor(void* pOwner, const void* pName, u32 typeId)
{
  // inlined base constructors, then the derived vptrs
  *(void* volatile*)((char*)this + 4) = (void*)g_13fa72c;
  *(u32* volatile*)((char*)this + 8) = 0;
  *(void* volatile*)((char*)this + 0xc) = (void*)g_13eb384;
  *(void**)((char*)this)      = (void*)g_14805b8;
  *(void**)((char*)this + 4)  = (void*)g_148059c;
  *(void**)((char*)this + 0xc) = (void*)g_148058c;

  // owner reference
  *(void**)((char*)this + 0x50) = pOwner;
  if (pOwner)
    ((TFv)(*(void***)pOwner)[0])(pOwner);

  // hashed name key, caller type id, class type constant
  u32 nameKey = FNV1_String16(pName, 0x811c9dc5, 1);
  *(u32 volatile*)((char*)this + 0x5c) = typeId;
  *(u32 volatile*)((char*)this + 0x54) = nameKey;
  *(u32 volatile*)((char*)this + 0x58) = 0x510a95b;

  // zeroed slots around the embedded layout object
  *(u32 volatile*)((char*)this + 0x60) = 0;
  *(u32 volatile*)((char*)this + 0x64) = 0;
  *(u32 volatile*)((char*)this + 0x68) = 0;
  *(u32 volatile*)((char*)this + 0x6c) = 0;

  _ReadWriteBarrier();

  *(u32 volatile*)((char*)this + 0x70) = 0;
  *(u32*)((char*)this + 0x74) = 0;
  *(u32*)((char*)this + 0x78) = 0;

  ((LayoutCtorC*)((char*)this + 0x7c))->ctor();

  *(u32*)((char*)this + 0x94) = 0;
  *(u32*)((char*)this + 0x98) = ++*(u32*)g_16ac238;    // global monotonic id
  *(u32*)((char*)this + 0x9c) = 0;
  *(u8*) ((char*)this + 0xa1) = 0;
  *(u8*) ((char*)this + 0xa2) = 0;
  *(u8*) ((char*)this + 0xa3) = 0;
  *(u32*)((char*)this + 0xb4) = 0;
  *(u8*) ((char*)this + 0xa0) = 1;
  *(float*)((char*)this + 0xb0) = 0.0f;
  *(float*)((char*)this + 0xd0) = 0.0f;

  _ReadWriteBarrier();

  // inline-buffer vector A: buffer at +0xec, 0x14 bytes
  {
    void* pBufA = (char*)this + 0xec;
    *(void**)((char*)this + 0xe4) = pBufA;
    *(void**)((char*)this + 0xd8) = pBufA;
    *(void**)((char*)this + 0xd4) = pBufA;
    *(void**)((char*)this + 0xdc) = (char*)pBufA + 0x14;
  }

  // inline-buffer vector B: buffer at +0x118, 0xc bytes
  {
    void* pBufB = (char*)this + 0x118;
    *(void**)((char*)this + 0x110) = pBufB;
    *(void**)((char*)this + 0x104) = pBufB;
    *(void**)((char*)this + 0x100) = pBufB;
    *(void**)((char*)this + 0x108) = (char*)pBufB + 0xc;
  }

  *(u32*)((char*)this + 0x124) = 0;
  *(u32*)((char*)this + 0x128) = 0;
  *(u32*)((char*)this + 0x12c) = 0;
  *(u32*)((char*)this + 0x13c) = 0;
  *(u8*) ((char*)this + 0x140) = 0;
  *(u32*)((char*)this + 0x144) = 0;
  *(float*)((char*)this + 0x148) = 0.0f;

  _ReadWriteBarrier();

  *(u32*)((char*)this + 0xa8) = 0;
  *(u32*)((char*)this + 0xac) = 0;

  return this;
}
