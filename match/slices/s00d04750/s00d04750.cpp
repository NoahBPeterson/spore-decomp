// Decompiled slice s00d04750 -- SP UI-layout / relationship objects.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include "types.h"

void operator_delete_array(void* p);                     // 0x00f47380

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct Sub04 {
  uint8_t mData[0x0c];                                   // +0x04 .. +0x0f
  void FUN_00d03b10(void* arg);                          // 0x00d03b10 (ecx=this, stack arg)
  void FUN_00d048a0(void* src);                          // 0x00d048a0 (ecx=this, stack arg)
};

struct Elem20 {                                          // 0x20-byte vector element
  int      mKey;        // +0x00
  Sub04    mSub;        // +0x04
  void*    mField10;    // +0x10
  uint8_t  mTail[0x0c]; // +0x14 .. +0x1f
};

struct Pair { uint32_t mKey; };                          // key/value pair passed to vec ops

Elem20* FUN_00d04f90(void* a, Elem20* end, void* b);      // 0x00d04f90 (cdecl)
Elem20* FUN_00d01210(Elem20* begin, Elem20* end, Pair* key, uint8_t flag); // 0x00d01210 (cdecl)

struct Vec20 {
  Elem20*  mpBegin;     // +0x00
  Elem20*  mpEnd;       // +0x04
  Elem20*  mpCap;       // +0x08
  uint32_t mField0c;    // +0x0c
  uint32_t mField10;    // +0x10
  uint8_t  mField14;    // +0x14

  int   FUN_00d051e0(void* a1, void* a2);                // 0x00d051e0
  void  FUN_00d05240(Elem20* pos, Pair* value);          // 0x00d05240
  Elem20* FUN_00d05380(Elem20* pos, Pair* value);        // 0x00d05380
  int   FUN_00d05560(Pair* key);                         // 0x00d05560
};

// ---------------------------------------------------------------------------
// @ 0x00d04e60
// AddRef: increments the intrusive reference count stored immediately before
// the object pointer (the object base sits 4 bytes past the count).
struct RefCountHeader { int mCount; };                   // mCount at -4 from the object

int __fastcall AddRef(RefCountHeader* p)
{
  int n = (p - 1)->mCount;
  ++n;
  (p - 1)->mCount = n;
  return n;
}

// @ 0x00d04a60
// Destroys a vector of 0x20-byte elements (destroying each element's +0x04
// sub-object) and frees the backing array.
void __fastcall FUN_00d04a60(Vec20* v)
{
  Elem20* end = v->mpEnd;
  for (Elem20* p = v->mpBegin; p < end; ++p)
    p->mSub.FUN_00d03b10(p->mField10);
  if (v->mpBegin)
    operator_delete_array(v->mpBegin);
}

// @ 0x00d051e0
// Destroys every element from the position returned by FUN_00d04f90 up to the
// vector end and shrinks the end pointer by the erased range.
int Vec20::FUN_00d051e0(void* a1, void* a2)
{
  Elem20* e = FUN_00d04f90(a2, mpEnd, a1);
  if (e < mpEnd) {
    unsigned n = (((unsigned)((char*)mpEnd - (char*)e)) - 1 >> 5) + 1;
    Elem20* p = e;
    do {
      p->mSub.FUN_00d03b10(p->mField10);
      ++p;
    } while (--n);
  }
  int d = (int)a2 - (int)a1;
  d >>= 5;
  d = -d;
  d <<= 5;
  mpEnd = (Elem20*)((char*)mpEnd + d);
  return (int)a1;
}

// @ 0x00d05380
// Inserts value before pos, appending in place when pos is the end and the
// capacity allows; otherwise forwards to FUN_00d05240.
Elem20* Vec20::FUN_00d05380(Elem20* pos, Pair* value)
{
  Elem20* end = mpEnd;
  int idx = (int)((char*)pos - (char*)mpBegin) >> 5;
  if (pos == end && end != mpCap) {
    mpEnd = end + 1;
    if (end != 0) {
      end->mKey = value->mKey;
      end->mSub.FUN_00d048a0(value + 1);
      return mpBegin + idx;
    }
  } else {
    FUN_00d05240(pos, value);
  }
  return mpBegin + idx;
}

// @ 0x00d05560
// Erases the element matching key (found through FUN_00d01210) and destroys it.
int Vec20::FUN_00d05560(Pair* key)
{
  Elem20* end = mpEnd;
  Elem20* p = FUN_00d01210(mpBegin, end, key, mField14);
  if (p == end || key->mKey < p->mKey || p == p + 1)
    p = end;
  if (p != end) {
    if (p + 1 < end)
      FUN_00d04f90(p + 1, end, p);
    mpEnd = mpEnd - 1;
    Elem20* q = mpEnd;
    q->mSub.FUN_00d03b10(q->mField10);
    return 1;
  }
  return 0;
}