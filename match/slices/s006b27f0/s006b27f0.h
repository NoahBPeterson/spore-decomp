#pragma once
// Stub declarations for slice s006b27f0 (SP save-area registration).
#include "types.h"

// AutoRefCount pair value (cSPSaveArea) - same shape as slice 4's RefPair.
struct RefVt5 { virtual void AddRef(); virtual void Release(); };
struct RefA5 { uint32_t pad0; RefVt5 ref; };
struct RefB5 { virtual void AddRef(); virtual void Release(); };
struct RefPair5 { RefA5* a; RefB5* b; };

// eastl rbtree node holding a RefPair5 value at +0x14.
struct RBNode5 {
  RBNode5* left;    // +0x00
  RBNode5* right;   // +0x04
  uint32_t m8;      // +0x08
  uint32_t mc;      // +0x0c
  uint32_t m10;     // +0x10
  RefPair5 val;     // +0x14
};

// object stored per save area (vtable slots 0x08 and 0x1c used here).
struct SaveObj5 {
  virtual void v0();
  virtual void v1();
  virtual void Call08();     // 0x08
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void Call1c();     // 0x1c
};

// global save-area map (base 0x0152fdc4).
struct SaveMap5 {
  uint32_t f0;       // +0x00
  uint32_t head;     // +0x04
  uint32_t root;     // +0x08
  uint32_t nukep;    // +0x0c
  uint32_t f10;      // +0x10
  uint32_t f14;      // +0x14
  void Nuke(RBNode5* n);   // 0x6b2aa0 (thiscall, this ignored)
};
extern SaveMap5 g_m5;

extern "C" void* RBTreeIncrement(void*);   // 0x00921580
extern void EFree5(void*);                 // 0x00f47380
