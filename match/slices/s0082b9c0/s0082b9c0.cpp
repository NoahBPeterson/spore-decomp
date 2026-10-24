// Slice s0082b9c0 (batch w2g7, slice 28).
// cSPUISerializeHelper::WriteHitmaskInline, the RLEHitMask COM object and its
// EASTL rbtree / vector instantiations.  The large serializer bodies are not
// reconstructed (see partial.txt).
#include "types.h"
#include <new>

// ---- byte-element vector (EASTL vector<unsigned short>) ----
struct U16Vec {
  unsigned short* mpBegin;    // +0x00
  unsigned short* mpEnd;      // +0x04
  unsigned short* mpEndCap;   // +0x08
  __declspec(noinline) U16Vec* Setup(unsigned n, const void* alloc);
  U16Vec* Init(unsigned n, const void* alloc);
  void AddZero();
  void InsertAt(void* pos, const void* value);  // 0x0082c970 (thiscall)
};
void* EA_New(unsigned int size, const char* group, int, int, int, int); // 0x00f473a0

// @ 0x0082BFA0
U16Vec* U16Vec::Setup(unsigned n, const void* alloc) {
  if (n != 0) {
    unsigned short* p = (unsigned short*)EA_New(n * 2, (const char*)0x13f6b3c, 0, 0, 0x13ebb38, 0xd1);
    mpBegin = p;
    mpEnd = p;
    mpEndCap = p + n;
  } else {
    mpBegin = 0;
    mpEnd = 0;
    mpEndCap = 0;
  }
  return this;
}

// @ 0x0082CC60
U16Vec* U16Vec::Init(unsigned n, const void* alloc) {
  Setup(n, alloc);
  if (n != 0) {
    unsigned short* p = mpBegin;
    unsigned short* e = p + n;
    while (p < e) *p++ = 0;
  }
  mpEnd = mpBegin + n;
  return this;
}

// @ 0x0082CCB0
void U16Vec::AddZero() {
  unsigned short* e = mpEnd;
  if (e < mpEndCap) {
    mpEnd = (unsigned short*)((char*)e + 4);
    if (e != 0)
      *(unsigned int*)e = 0;
  } else {
    unsigned int v = 0;
    InsertAt(e, &v);
  }
}

// ---- EASTL rbtree node insert ----
struct RBTree {
  char pad0[0x14];
  int mCount;   // +0x14
  void Insert(void* node, void* parent, void* where, int flag);
};

// @ 0x0082C000
void RBTree::Insert(void* node, void* parent, void* where, int flag) {
  (void)node; (void)parent; (void)where; (void)flag;
}

// ---- RLEHitMask ----
struct RLEHitMask {
  char pad0[0x14];
  int m14;            // +0x14
  int m18;            // +0x18
  int m1c;            // +0x1c
  RLEHitMask();
};

// @ 0x0082C190
RLEHitMask::RLEHitMask() : m14(0), m18(0), m1c(0) {
}

// @ 0x0082B9C0
void SerializeHelperProcessTokens2() {
}
// @ 0x0082C1D0
void RLEHitMaskDestroy(RLEHitMask* p) { (void)p; }
// @ 0x0082C210
void WriteHitmaskInline() {
}
// @ 0x0082C420
void SerializeHelperWrite2() {
}
// @ 0x0082C550
void SerializeHelperNuke() {
}
// @ 0x0082C5A0
void SerializeHelperNuke2() {
}
// @ 0x0082C770
void SerializeHelperWrite3() {
}
// @ 0x0082C810
void SerializeHelperWrite4() {
}
