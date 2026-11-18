// @ 0x00e25460
// Flags: /O2 /Ob2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// cSPUIPosse (slice s00e24700 family) constructor: two base vptrs seeded by the inlined base
// constructors (a cResource at +0x04, a cListenerBase at +0x0c) are overwritten by the three
// derived vptrs, then the owner reference, the resource key, the embedded layout object and the
// two inline-buffer vectors are initialised.
#include "game/types.h"
#include <intrin.h>

typedef unsigned int  u32;
typedef unsigned char u8;
typedef void (__thiscall* TFv)(void*);

struct LayoutCtorC { void ctor(); };                    // 0x00810000  embedded layout constructor

struct cSPUIPosse_s00e25460 {
  void* ctor(void* pOwner, const u32* pKey);
};

void* cSPUIPosse_s00e25460::ctor(void* pOwner, const u32* pKey)
{
  // inlined base constructors, then the derived vptrs
  *(void* volatile*)((char*)this + 4) = (void*)0x13fa72c;
  *(u32* volatile*)((char*)this + 8) = 0;
  *(void* volatile*)((char*)this + 0xc) = (void*)0x13eb384;
  *(void**)((char*)this)      = (void*)0x14805b8;
  *(void**)((char*)this + 4)  = (void*)0x148059c;
  *(void**)((char*)this + 0xc) = (void*)0x148058c;

  // owner reference
  *(void**)((char*)this + 0x50) = pOwner;
  if (pOwner)
    ((TFv)(*(void***)pOwner)[0])(pOwner);

  // resource key (three dwords)
  *(u32*)((char*)this + 0x54) = pKey[0];
  *(u32*)((char*)this + 0x58) = pKey[1];
  *(u32*)((char*)this + 0x5c) = pKey[2];

  // zeroed slots around the embedded layout object
  *(u32*)((char*)this + 0x60) = 0;
  *(u32*)((char*)this + 0x64) = 0;
  *(u32*)((char*)this + 0x68) = 0;
  *(u32*)((char*)this + 0x6c) = 0;

  _ReadWriteBarrier();

  *(u32*)((char*)this + 0x70) = 0;
  *(u32*)((char*)this + 0x74) = 0;
  *(u32*)((char*)this + 0x78) = 0;

  ((LayoutCtorC*)((char*)this + 0x7c))->ctor();

  *(u32*)((char*)this + 0x94) = 0;
  *(u32*)((char*)this + 0x98) = ++*(u32*)0x16ac238;    // global monotonic id
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
