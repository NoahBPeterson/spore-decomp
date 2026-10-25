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

// ---- deallocate (allocator header is 4 bytes in front of the block) ----
extern "C" void FUN_00f47380(void* p);   // 0x00f47380

// ---- EASTL rbtree node insert ----
struct RBTree {
  char pad0[0x14];
  int mCount;   // +0x14
  void Insert(void* out, void* parent, void* where, int flag);
};
extern "C" void FUN_009216a0(void* node, void* parent, void* header, int side); // 0x009216a0

// @ 0x0082C000
void RBTree::Insert(void* out, void* parent, void* where, int flag) {
  int right = 0;
  if ((unsigned char)flag == 0 && parent != (char*)this + 4 &&
      *(unsigned*)where >= *(unsigned*)((char*)parent + 0x10))
    right = 1;
  void* node = EA_New(0x14, (const char*)0x13f6b3c, 0, 0, (int)0x13ebb38, 0xd1);
  *(int*)((char*)node + 0x10) = *(int*)where;
  FUN_009216a0(node, parent, (char*)this + 4, right);
  mCount++;
  *(void**)out = node;
}

// ---- RLEHitMask (COM object; two vtable words + one owned buffer) ----
extern "C" char DATA_13ef094[];   // 0x13ef094  base subobject vtable
extern "C" char DATA_13eb938[];   // 0x13eb938  destroying vtable
extern "C" char DATA_141a380[];   // 0x141a380  derived vtable (+0)
extern "C" char DATA_141a37c[];   // 0x141a37c  derived vtable (+4)

struct RLEHitMask {
  void* mpVtbl00;     // +0x00
  void* mpVtbl04;     // +0x04
  int   m08;          // +0x08
  char  pad0c[8];     // +0x0c..0x13
  int   m14;          // +0x14  owned buffer (header word at -4)
  int   m18;          // +0x18
  int   m1c;          // +0x1c
  RLEHitMask();
};

// @ 0x0082C190
RLEHitMask::RLEHitMask() {
  mpVtbl04 = DATA_13ef094;
  m08      = 0;
  mpVtbl00 = DATA_141a380;
  mpVtbl04 = DATA_141a37c;
  m14 = 0;
  m18 = 0;
  m1c = 0;
}

// @ 0x0082B9C0
extern "C" char __fastcall SerializeHelperProcessTokens2(void* self, int /*dummy*/,
                                                         void* data, int len) {
  (void)self; (void)data; (void)len;
  return 0;
}
// @ 0x0082C1D0
extern "C" RLEHitMask* __fastcall RLEHitMaskDestroy(RLEHitMask* self, int /*dummy*/, int flag) {
  int buf = self->m14;
  if (buf != 0 && *(int*)(buf - 4) != 0)
    FUN_00f47380((void*)buf);
  if (flag & 1) {
    self->mpVtbl04 = DATA_13ef094;
    self->mpVtbl00 = DATA_13eb938;
    FUN_00f47380(self);
  } else {
    self->mpVtbl04 = DATA_13ef094;
    self->mpVtbl00 = DATA_13eb938;
  }
  return self;
}
// @ 0x0082C210
void WriteHitmaskInline() {
}
// @ 0x0082C420
extern "C" char __fastcall SerializeHelperWrite2(void* self, int /*dummy*/, void* a1) {
  int local;
  void* writer = *(void**)self;            // +0x00  output interface
  void** wv = *(void***)writer;
  local = *(int*)a1;
  ((void (__thiscall*)(void*, void*, int))wv[0xe])(writer, &local, 4);
  local = *(unsigned short*)((char*)a1 + 4);
  ((void (__thiscall*)(void*, void*, int))wv[0xe])(writer, &local, 2);
  local = *(unsigned short*)((char*)a1 + 6);
  ((void (__thiscall*)(void*, void*, int))wv[0xe])(writer, &local, 2);
  int saved = ((int (__thiscall*)(void*, int))wv[9])(writer, 0);
  if (*(unsigned short*)((char*)a1 + 4) == 0x14) {
    local = 0;
    ((void (__thiscall*)(void*, void*, int))wv[0xe])(writer, &local, 4);
  }
  int base = ((int (__thiscall*)(void*, int))wv[9])(writer, 0);
  int count = *(unsigned short*)((char*)a1 + 6);
  int off = 0;
  for (int i = 0; i < count; i++) {
    if (!SerializeHelperProcessTokens2(self, 0, (char*)*(void**)((char*)a1 + 8) + off,
                                       *(unsigned short*)((char*)a1 + 4)))
      return 0;
    off += 0x20;
  }
  int end = ((int (__thiscall*)(void*, int))wv[9])(writer, 0);
  if (*(unsigned short*)((char*)a1 + 4) == 0x14) {
    ((void (__thiscall*)(void*, int, int))wv[0xa])(writer, saved, 0);
    int diff = end - base;
    ((void (__thiscall*)(void*, void*, int))wv[0xe])(writer, &diff, 4);
    ((void (__thiscall*)(void*, int, int))wv[0xa])(writer, end, 0);
  }
  return 1;
}
// ---- serializer helper object A ----
extern "C" char DATA_13ec47c[];   // 0x13ec47c
extern "C" char DATA_14613b8[];   // 0x14613b8
extern "C" char DATA_141a320[];   // 0x141a320
extern "C" void __fastcall FUN_006b5060(void* self, int /*dummy*/);   // 0x006b5060
extern "C" void __fastcall FUN_006b5240(void* self, int /*dummy*/);   // 0x006b5240
extern "C" void __fastcall FUN_00833790(void* self, int /*dummy*/);   // 0x00833790
extern "C" void __fastcall FUN_00833a80(void* self, int /*dummy*/);   // 0x00833a80
extern "C" void __fastcall FUN_008e2b20(void* self, int /*dummy*/);   // 0x008e2b20
extern "C" void __fastcall FUN_00928cd0(void* self, int /*dummy*/, int a, int b, int c, int d, int e); // 0x00928cd0
extern "C" void __fastcall FUN_00928dc0(void* self, int /*dummy*/);   // 0x00928dc0

struct Sub228 { char d[0x14]; };
struct Sub240 { char d[0x24]; };
struct Sub264 { char d[0x10]; };
struct SerHelperA {
  void*   mpVtbl00;    // +0x000
  int     m04;         // +0x004
  void*   mp08;        // +0x008
  void*   mp0c;        // +0x00c
  void*   mp10;        // +0x010
  char    pad14[4];    // +0x014
  void*   mp18;        // +0x018
  char    pad1c[4];    // +0x01c
  unsigned char mBuf20[0x200]; // +0x020..0x21f
  void*   mpVtbl220;   // +0x220
  int     m224;        // +0x224
  Sub228  m228;        // +0x228
  void*   mpVtbl23c;   // +0x23c
  Sub240  m240;        // +0x240
  Sub264  m264;        // +0x264
};

// @ 0x0082C770
extern "C" SerHelperA* __fastcall SerializeHelperWrite3(SerHelperA* self, int /*dummy*/,
                                                        void* a1, int a2) {
  self->mpVtbl00 = a1;
  if (a1)
    ((void (__thiscall*)(void*))((*(void***)a1)[1]))(a1);
  self->m04 = a2;
  void* buf = self->mBuf20;
  self->mp18 = buf;
  self->mp0c = buf;
  self->mp08 = buf;
  self->mp10 = (char*)buf + 0x200;
  self->mpVtbl220 = DATA_13ec47c;
  self->m224 = 0;
  FUN_006b5060(&self->m228, 0);
  FUN_00928cd0(&self->m240, 0, 0, -1, 0, 0, 0);
  self->mpVtbl23c = DATA_14613b8;
  FUN_00833790(&self->m264, 0);
  self->mpVtbl23c = DATA_141a320;
  void** vt = *(void***)&self->m264;
  ((void (__thiscall*)(void*))vt[0])(&self->m264);
  return self;
}

// @ 0x0082C550
extern "C" void __fastcall SerializeHelperNuke(SerHelperA* self, int /*dummy*/) {
  FUN_00833a80(&self->m264, 0);
  FUN_00928dc0(&self->m240, 0);
  self->mpVtbl23c = DATA_14613b8;
  FUN_006b5240(&self->m228, 0);
  FUN_008e2b20(&self->mp08, 0);
  void* p = self->mpVtbl00;
  if (p)
    ((void (__thiscall*)(void*))((*(void***)p)[2]))(p);
}
// ---- serializer helper object B ----
extern "C" void __fastcall FUN_009a9600(void* self, int /*dummy*/, void* p); // 0x009a9600

struct Cont {           // EASTL rbtree-backed container (0x1c bytes)
  int   m00;            // +0x00
  void* mp04;           // +0x04  (self-referential anchor)
  void* mp08;           // +0x08
  void* mp0c;           // +0x0c
  int   m10;            // +0x10
  int   m14;            // +0x14
  char  pad18[4];       // +0x18..0x1b
};
struct SerHelperB {
  void*   mpVtbl00;    // +0x000
  int     m04;         // +0x004
  int     m08;         // +0x008
  void*   mpVtbl0c;    // +0x00c
  char    m10[0x24];   // +0x010..0x033
  Cont    c34;         // +0x034..0x04f
  void*   mp50;        // +0x050
  int     m54;         // +0x054
  int     m58;         // +0x058
  char    pad5c[8];    // +0x05c..0x063
  void*   mp64;        // +0x064
  int     m68;         // +0x068
  int     m6c;         // +0x06c
  char    pad70[8];    // +0x070..0x077
  Cont    c78;         // +0x078..0x093
  Cont    c94;         // +0x094..0x0af
  Cont    cb0;         // +0x0b0..0x0cb
  Cont    ccc;         // +0x0cc..0x0e7
  Cont    ce8;         // +0x0e8..0x103
};

static void InitCont(Cont* c) {
  c->mp08 = 0;
  c->mp0c = 0;
  c->m10 = 0;
  c->mp0c = 0;
  c->m10 = 0;
  c->m14 = 0;
  c->mp04 = (void*)&c->mp04;
  c->mp08 = (void*)&c->mp04;
}

// @ 0x0082C810
extern "C" SerHelperB* __fastcall SerializeHelperWrite4(SerHelperB* self, int /*dummy*/,
                                                        void* a1, int a2) {
  self->mpVtbl00 = a1;
  if (a1)
    ((void (__thiscall*)(void*))((*(void***)a1)[1]))(a1);
  self->m04 = a2;
  self->m08 = a2;
  self->mpVtbl0c = DATA_14613b8;
  FUN_00928cd0(self->m10, 0, 0, -1, 0, 0, 0);
  self->mpVtbl0c = DATA_141a320;
  InitCont(&self->c34);
  self->mp50 = 0;
  self->m54 = 0;
  self->m58 = 0;
  self->mp64 = 0;
  self->m68 = 0;
  self->m6c = 0;
  InitCont(&self->c78);
  InitCont(&self->c94);
  InitCont(&self->cb0);
  InitCont(&self->ccc);
  InitCont(&self->ce8);
  return self;
}

// @ 0x0082C5A0
extern "C" void __fastcall SerializeHelperNuke2(SerHelperB* self, int /*dummy*/) {
  FUN_009a9600(&self->ce8, 0, self->ce8.mp0c);
  FUN_009a9600(&self->ccc, 0, self->ccc.mp0c);
  FUN_009a9600(&self->cb0, 0, self->cb0.mp0c);
  FUN_009a9600(&self->c94, 0, self->c94.mp0c);
  FUN_009a9600(&self->c78, 0, self->c78.mp0c);
  if (self->mp64 != 0 && *(int*)((char*)self->mp64 - 4) != 0)
    FUN_00f47380(self->mp64);
  if (self->mp50 != 0 && *(int*)((char*)self->mp50 - 4) != 0)
    FUN_00f47380(self->mp50);
  FUN_009a9600(&self->c34, 0, self->c34.mp0c);
  FUN_00928dc0(self->m10, 0);
  self->mpVtbl0c = DATA_14613b8;
  void* p = self->mpVtbl00;
  if (p)
    ((void (__thiscall*)(void*))((*(void***)p)[2]))(p);
}
