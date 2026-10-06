// Slice s0082acb0 (batch w2g7, slice 27).
// UTFWin UI serialization helpers: cSPUISerializeHelper / cSPUIDeserializeHelper,
// the temporary StackAllocator and small serialization/allocator helpers.
#include "types.h"
#include <new>
#include <math.h>

// Generic object with a serialization virtual at slot 14 (byte offset +0x38).
struct SerObj {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14(unsigned* p, int n);
};

// A pointer-slot wrapper: this + 0x00 is the object pointer.
struct RefSlot {
  SerObj* mp;                        // +0x00
  void Write8(unsigned a);
  void Write16(unsigned a);
  void Write32(unsigned a);
  void Write64(unsigned a, unsigned b);
};

// @ 0x0082B880
void RefSlot::Write8(unsigned a)  { mp->m14(&a, 1); }
// @ 0x0082B8A0
void RefSlot::Write16(unsigned a) { mp->m14(&a, 2); }
// @ 0x0082B8C0
void RefSlot::Write32(unsigned a) { mp->m14(&a, 4); }
// @ 0x0082B8E0
void RefSlot::Write64(unsigned a, unsigned b) { mp->m14(&a, 8); (void)b; }

// ---- temporary StackAllocator (EA::Allocator::StackAllocator) ----
struct TempAlloc {
  char pad0[8];
  uint32_t mLimit;    // +0x08
  uint32_t mCur;      // +0x0c
  uint32_t mCur2;     // +0x10
  char pad14[0xc];
  void* mpTop;        // +0x20
  bool Grow(uint32_t n);                              // calls 0x928ba0
  void* MallocAligned(uint32_t a, uint32_t b, int c, int d);  // calls 0x928d40
};

struct Pair16 { uint32_t a, b, c, d; };
struct Tri12 { uint32_t a, b, c; };

struct Pool16 {
  char pad0[0x10];
  TempAlloc mAlloc;   // +0x10
  Pair16* NewPair();
};
struct Pool12 {
  char pad0[0x10];
  TempAlloc mAlloc;   // +0x10
  Tri12* NewTri();
};

// @ 0x0082B920
Pair16* Pool16::NewPair() {
  if ((int)(mAlloc.mLimit - mAlloc.mCur) - 0x10 < 0) {
    if (!mAlloc.Grow(0x10)) {
      Pair16* p = 0;
      p->a = 0; p->b = 0; p->c = 0; p->d = 0;
      return 0;
    }
  }
  Pair16* p = (Pair16*)mAlloc.mCur;
  uint32_t nxt = (uint32_t)p + 0x10;
  mAlloc.mCur = nxt;
  mAlloc.mCur2 = nxt;
  p->a = 0; p->b = 0; p->c = 0; p->d = 0;
  return p;
}

// @ 0x0082B970
Tri12* Pool12::NewTri() {
  if ((int)(mAlloc.mLimit - mAlloc.mCur) - 0x10 < 0) {
    if (!mAlloc.Grow(0x10)) {
      Tri12* p = 0;
      p->a = 0; p->b = 0; p->c = 0;
      return 0;
    }
  }
  Tri12* p = (Tri12*)mAlloc.mCur;
  uint32_t nxt = (uint32_t)p + 0x10;
  mAlloc.mCur = nxt;
  mAlloc.mCur2 = nxt;
  p->a = 0; p->b = 0; p->c = 0;
  return p;
}

// ---- cSPUISerializeHelper / cSPUIDeserializeHelper (large members) ----
struct Value20 { uint8_t raw[0x20]; };
struct SerializeHelper {
  char pad0[0x10];
  TempAlloc mTemp;    // +0x10
  Value20* NewArrayValue(int count);
  void ParseValue();
  void SkipProperty();
  void ReadProperty();
};

// @ 0x0082ACB0 : ParseValue
void SerializeHelper::ParseValue() {
  // Full recursive-descent serializer not reconstructed.
}

// @ 0x0082B160 : cSPUIDeserializeHelper::SkipProperty
void SerializeHelper::SkipProperty() {
}

// @ 0x0082B310 : cSPUIDeserializeHelper::ReadProperty
void SerializeHelper::ReadProperty() {
}

// @ 0x0082B060
Value20* SerializeHelper::NewArrayValue(int count) {
  if (count == 0) return 0;
  uint32_t size = count * 0x20;
  if ((int)(mTemp.mLimit - mTemp.mCur) - (int)size < 0) {
    if (!mTemp.Grow(size)) return 0;
  }
  Value20* p = (Value20*)mTemp.mCur;
  uint32_t nxt = (uint32_t)p + size;
  mTemp.mCur = nxt;
  mTemp.mCur2 = nxt;
  return p;
}

// @ 0x0082B7F0 : cSPUISerializationAllocator::Allocate (8-byte object fast path)
struct SerAlloc {
  char pad0[4];
  TempAlloc mAlloc;   // +0x04
  void* Allocate(uint32_t align, uint32_t size);
};
void* SerAlloc::Allocate(uint32_t align, uint32_t size) {
  if (size > 8) {
    return mAlloc.MallocAligned(align, size, 0, 1);
  }
  uint32_t aligned = (align + 7) & 0xfffffff8u;
  if ((int)(mAlloc.mLimit - mAlloc.mCur) - (int)aligned < 0) {
    if (!mAlloc.Grow(aligned)) return 0;
  }
  uint32_t p = mAlloc.mCur;
  uint32_t nxt = p + aligned;
  mAlloc.mCur = nxt;
  mAlloc.mCur2 = nxt;
  return (void*)p;
}

// ---- EA::Allocator::StackAllocator::AllocateNewBlock (0x82b0d0) ----
struct Bookmark { void* mpNext; void* mpA; void* mpB; };
struct StackAlloc {
  char pad0[8];
  uint32_t mLimit;   // +0x08
  uint32_t mCur;     // +0x0c
  uint32_t mCur2;    // +0x10
  char pad14[0xc];
  void* mpTop;       // +0x20
  bool Grow(uint32_t n);
  void AllocateNewBlock(Bookmark* b);
};

// @ 0x0082B0D0
void StackAlloc::AllocateNewBlock(Bookmark* b) {
  uint32_t a, c;
  if (b) {
    a = (uint32_t)b;
    c = (uint32_t)b;
  } else {
    c = mCur;
    a = mCur2;
  }
  if (mCur != mCur2) {
    uint32_t t = (mCur2 + 7) & 0xfffffff8u;
    mCur2 = t;
    if (t > mLimit) mCur2 = mLimit;
    mCur = mCur2;
  }
  if ((int)(mLimit - mCur) - 0x10 < 0) {
    if (!Grow(0x10)) return;
  }
  uint32_t p = mCur;
  uint32_t nxt = p + 0x10;
  mCur = nxt;
  mCur2 = nxt;
  void** q = (void**)p;
  q[0] = mpTop;
  q[1] = (void*)a;
  q[2] = (void*)c;
  mpTop = (void*)p;
}

// @ 0x0082AFE0 : binary search of a static wide-string table, returns a 16-bit code.
extern const unsigned char g_strTable[];   // 0x141a1c0 pairs {char16* name; ushort code;}
static int CmpW(const unsigned short* a, const unsigned short* b) {
  while (*a == *b) { if (!*a) return 0; ++a; ++b; }
  return *a < *b ? -1 : 1;
}
// @ 0x0082AFE0
int LookupCode(const unsigned short* key) {
  int lo = 0, hi = 0x16;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    const unsigned short* name = *(const unsigned short**)(g_strTable + mid * 8);
    if (CmpW(key, name) == 0) return *(const unsigned short*)(g_strTable + mid * 8 + 4);
    if (CmpW(key, name) < 0) hi = mid; else lo = mid + 1;
  }
  return 0;
}
