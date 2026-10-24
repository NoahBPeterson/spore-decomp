// Slice s011ea070 (gold7) -- RenderWare core (rw::core::stdc / rw::core::filesys)
// support routines.  The slice id is shared with the older Vsnprintf work in
// s011ea070.cpp; that file and its 011ea070 nonmatching row are left untouched.
//
// gold7 functions:
//   011ea770  vsnprintf-style variadic trampoline (engine at 011e9a10)
//   011ea790  _vsnprintf-style trampoline (Vsnprintf at 011ea070)
//   011ea7d0  filesys open + size != 0 test
//   011ea850  filesys open + 64-bit size/position pair
//   011ea910  stdc memcpy (returns one-past-end, like the original)
//   011eaa50  register three callbacks with fixed descriptors
//   011eaa80  unregister the same three callbacks
//   011eaaa0  register three callback descriptors (second family)
//   011eaad0  unregister the second family
//   011eaaf0  array-owner init (count = 0, allocator = arg)
//   011eab10  sum of 16-bit ranges (m10 - m12) over an Elem** array
//   011eab40  sum of 32-bit ranges (m4 - m0) over an Elem** array
//   011eab70  release every element and the array through the allocator vtable
//   011eabe0  build an open-addressed string map inside a caller buffer
//   011eaca0  string map insert (FNV hash, linear probing)
//   011eadb0  string map find
//   011eae90  string map find-or-insert
//   011eaf10  copy every live entry of one map into another
//   011eaf50  rebase four pointers plus the self-pointer by the holder address
//
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-  (VS2008-era cl, no stack cookie)

#include "types.h"
#include <string.h>
#include <stdarg.h>

// ---------------------------------------------------------------------------
// External data / callees
// ---------------------------------------------------------------------------
extern "C" int  Engine3(char* dst, unsigned remain, char* ap);          // 0x011e9a10
extern "C" int  Vsnprintf(char* dst, unsigned remain, const char* fmt, char* ap); // 0x011ea070
extern "C" void* RwAlloc(uint32_t size);                                // 0x011e6d20
extern "C" void* ResolvePath(const char* path, int flags);              // 0x011e5ff0
extern "C" uint32_t HashString(const char* s, uint32_t seed);           // 0x011e4590

extern "C" void RegA(void* p);   // 0x011ed320
extern "C" void RegB(void* p);   // 0x011ed330
extern "C" void RegC(void* p);   // 0x011ed340
extern "C" void RegD(void* p);   // 0x011e5830
extern "C" void RegE(void* p);   // 0x011e5840
extern "C" void RegF(void* p);   // 0x011e5850

extern char g_11ed630;   // 0x011ed630
extern char g_11ed640;   // 0x011ed640
extern char g_11ed650;   // 0x011ed650
extern char g_11ed660;   // 0x011ed660
extern char g_11ed670;   // 0x011ed670
extern char g_11ed680;   // 0x011ed680

extern uint32_t g_14f64ac;        // 0x014f64ac  FNV-1a offset basis
extern void* g_rwFsAllocator;     // 0x016f4b10  filesys allocator object

// ---------------------------------------------------------------------------
// Allocator interface used by the filesys stream code.
// The original calls vtable slot 2 with a 16-byte descriptor; the first dword
// is the allocation to release, the remaining three are zero.
// ---------------------------------------------------------------------------
struct FreeDesc {
  void* mPtr;        // +0x00
  uint32_t mZero0;   // +0x04
  uint32_t mZero1;   // +0x08
  uint32_t mZero2;   // +0x0c
};

typedef void (__thiscall* AllocFreeFn)(void* self, FreeDesc* desc);

static inline void AllocatorFree(void* alloc, FreeDesc* desc) {
  void** vtbl = *(void***)alloc;
  ((AllocFreeFn)vtbl[2])(alloc, desc);
}

// filesys stream handle (0x28 bytes); only the fields the two helpers read.
struct FsHandle {
  uint8_t  m00[0x08];   // +0x00
  int32_t  m08;         // +0x08
  uint8_t  m0c[0x0c];   // +0x0c
  int32_t  m18;         // +0x18
  int32_t  m1c;         // +0x1c

  FsHandle* Construct(const char* path, int flags, void* resolved); // 0x011ecdf0
  void Cleanup();                                                   // 0x011ecf40
};

// ---------------------------------------------------------------------------
// Array owner (011eaaf0 / 011eab70) and Elem array (011eab10 / 011eab40)
// ---------------------------------------------------------------------------
struct Elem {
  void* mData;          // +0x00
};

struct H16 {
  uint8_t  m00[0x10];   // +0x00
  uint16_t m10;         // +0x10
  uint16_t m12;         // +0x12
};

struct H32 {
  int32_t m00;          // +0x00
  int32_t m04;          // +0x04
};

struct ArrayOwner {
  Elem**    mArray;     // +0x00
  uint32_t  mCount;     // +0x04
  void*     mAlloc;     // +0x08

  void Init(void* alloc);       // 0x011eaaf0
  void Clear();                 // 0x011eab70
  int  Sum16();                 // 0x011eab10
  int  Sum32();                 // 0x011eab40
};

// ---------------------------------------------------------------------------
// Open-addressed string map (011eabe0 .. 011eaf10)
// The header lives at the caller-provided buffer; mBase points at buffer+0x18.
// ---------------------------------------------------------------------------
struct MapHeader {
  char*      mBase;      // +0x00  string storage
  char*      mCursor;    // +0x04  next free byte
  uint32_t*  mOffsets;   // +0x08  one offset per entry (-1 = empty)
  uint16_t*  mSlots;     // +0x0c  hash slot -> entry (-1 = empty)
  uint16_t   mSize;      // +0x10  slot/entry count
  uint16_t   mFree;      // +0x12  remaining entries
  uint16_t   mNext;      // +0x14  next entry index to scan
};

struct StringMap {
  MapHeader* mData;      // +0x00

  void Init(void* buffer, int offset, int count);         // 0x011eabe0
  void Insert(const char* str, uint16_t index);          // 0x011eaca0
  bool Find(const char* str, uint16_t* out);             // 0x011eadb0
  uint16_t FindOrInsert(const char* str);                // 0x011eae90
  void CopyTo(StringMap* target);                        // 0x011eaf10
};

static int MapStrcmp(const char* a, const char* b) {
  for (;;) {
    unsigned char ca = (unsigned char)*a;
    unsigned char cb = (unsigned char)*b;
    if (ca != cb)
      return ca < cb ? -1 : 1;
    if (ca == 0)
      return 0;
    ++a;
    ++b;
  }
}

// ---------------------------------------------------------------------------
// 0x011ea770 -- variadic trampoline into the engine at 011e9a10
// ---------------------------------------------------------------------------
// @ 0x011ea770
int Wrapper770(char* dst, unsigned remain, ...) {
  va_list ap;
  va_start(ap, remain);
  int r = Engine3(dst, remain, ap);
  va_end(ap);
  return r;
}

// ---------------------------------------------------------------------------
// 0x011ea790 -- _vsnprintf-style trampoline; -1 becomes remain-1
// ---------------------------------------------------------------------------
// @ 0x011ea790
int Wrapper790(char* dst, unsigned remain, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int r = Vsnprintf(dst, remain, fmt, ap);
  va_end(ap);
  if (r == -1)
    r = (int)remain - 1;
  return r;
}

// ---------------------------------------------------------------------------
// 0x011ea7d0 -- open a filesys stream and report whether it is non-empty
// ---------------------------------------------------------------------------
// @ 0x011ea7d0
bool FileIsNonEmpty(const char* path) {
  FsHandle* mem = (FsHandle*)RwAlloc(0x28);
  FsHandle* h = 0;
  if (mem != 0)
    h = mem->Construct(path, 0, ResolvePath(path, 0));
  int size = h->m08;
  h->Cleanup();
  FreeDesc desc;
  desc.mPtr = h;
  desc.mZero0 = 0;
  desc.mZero1 = 0;
  desc.mZero2 = 0;
  AllocatorFree(g_rwFsAllocator, &desc);
  return size != 0;
}

// ---------------------------------------------------------------------------
// 0x011ea850 -- open a filesys stream and return its 64-bit size pair
// ---------------------------------------------------------------------------
// @ 0x011ea850
uint64_t FileSizePair(const char* path) {
  FsHandle* mem = (FsHandle*)RwAlloc(0x28);
  FsHandle* h = 0;
  if (mem != 0)
    h = mem->Construct(path, 0, ResolvePath(path, 0));
  uint32_t lo = 0;
  uint32_t hi = 0;
  if (h->m08 != 0) {
    lo = (uint32_t)h->m18;
    hi = (uint32_t)h->m1c;
  }
  h->Cleanup();
  FreeDesc desc;
  desc.mPtr = h;
  desc.mZero0 = 0;
  desc.mZero1 = 0;
  desc.mZero2 = 0;
  AllocatorFree(g_rwFsAllocator, &desc);
  return ((uint64_t)hi << 32) | lo;
}

// ---------------------------------------------------------------------------
// 0x011ea910 -- stdc memcpy; returns one-past-end like the original
// ---------------------------------------------------------------------------
// @ 0x011ea910
uint64_t RwMemcpy(void* dst, const void* src, size_t count) {
  unsigned char* d = (unsigned char*)dst;
  const unsigned char* s = (const unsigned char*)src;
  size_t n = count;

  if (n < 0x200) {
    while (n >= 8) {
      *(uint32_t*)d = *(const uint32_t*)s;
      *(uint32_t*)(d + 4) = *(const uint32_t*)(s + 4);
      d += 8;
      s += 8;
      n -= 8;
    }
    while (n != 0) {
      *d++ = *s++;
      --n;
    }
    return ((uint64_t)(uintptr_t)s << 32) | (uintptr_t)d;
  }

  uint32_t align = (uint32_t)(uintptr_t)d & 3;
  if (align != 0) {
    if ((align & 1) != 0 && (int)n > 0) {
      *d++ = *s++;
      --n;
    }
    if ((align & 2) != 0 && (int)n > 1) {
      *(uint16_t*)d = *(const uint16_t*)s;
      d += 2;
      s += 2;
      n -= 2;
    }
    if ((align & 4) != 0 && (int)n > 3) {
      *(uint32_t*)d = *(const uint32_t*)s;
      d += 4;
      s += 4;
      n -= 4;
    }
  }

  while ((int)(n - 0x20) >= 0) {
    *(uint32_t*)(d + 0x00) = *(const uint32_t*)(s + 0x00);
    *(uint32_t*)(d + 0x04) = *(const uint32_t*)(s + 0x04);
    *(uint32_t*)(d + 0x08) = *(const uint32_t*)(s + 0x08);
    *(uint32_t*)(d + 0x0c) = *(const uint32_t*)(s + 0x0c);
    *(uint32_t*)(d + 0x10) = *(const uint32_t*)(s + 0x10);
    *(uint32_t*)(d + 0x14) = *(const uint32_t*)(s + 0x14);
    *(uint32_t*)(d + 0x18) = *(const uint32_t*)(s + 0x18);
    *(uint32_t*)(d + 0x1c) = *(const uint32_t*)(s + 0x1c);
    d += 0x20;
    s += 0x20;
    n -= 0x20;
  }

  while ((int)(n - 8) >= 0) {
    *(uint32_t*)(d + 0) = *(const uint32_t*)(s + 0);
    *(uint32_t*)(d + 4) = *(const uint32_t*)(s + 4);
    d += 8;
    s += 8;
    n -= 8;
  }

  if (n != 0) {
    if (n > 3) {
      *(uint32_t*)d = *(const uint32_t*)s;
      d += 4;
      s += 4;
      n -= 4;
    }
    if (n > 1) {
      *(uint16_t*)d = *(const uint16_t*)s;
      d += 2;
      s += 2;
      n -= 2;
    }
    if (n != 0)
      *d++ = *s++;
  }
  return ((uint64_t)(uintptr_t)s << 32) | (uintptr_t)d;
}

// ---------------------------------------------------------------------------
// 0x011eaa50 -- register three fixed callbacks
// ---------------------------------------------------------------------------
// @ 0x011eaa50
void RegisterHooksA() {
  RegA(&g_11ed630);
  RegB(&g_11ed640);
  RegC(&g_11ed650);
}

// ---------------------------------------------------------------------------
// 0x011eaa80 -- unregister the same three callbacks
// ---------------------------------------------------------------------------
// @ 0x011eaa80
void UnregisterHooksA() {
  RegA(0);
  RegB(0);
  RegC(0);
}

// ---------------------------------------------------------------------------
// 0x011eaaa0 -- register the second callback family
// ---------------------------------------------------------------------------
// @ 0x011eaaa0
void RegisterHooksB() {
  RegD(&g_11ed660);
  RegE(&g_11ed670);
  RegF(&g_11ed680);
}

// ---------------------------------------------------------------------------
// 0x011eaad0 -- unregister the second callback family
// ---------------------------------------------------------------------------
// @ 0x011eaad0
void UnregisterHooksB() {
  RegD(0);
  RegE(0);
  RegF(0);
}

// ---------------------------------------------------------------------------
// 0x011eaaf0 -- array-owner init
// ---------------------------------------------------------------------------
// @ 0x011eaaf0
void ArrayOwner::Init(void* alloc) {
  mCount = 0;
  mAlloc = alloc;
}

// ---------------------------------------------------------------------------
// 0x011eab10 -- sum of 16-bit (m10 - m12) ranges
// ---------------------------------------------------------------------------
// @ 0x011eab10
int ArrayOwner::Sum16() {
  uint32_t n = mCount;
  int sum = 0;
  if (n != 0) {
    Elem** p = mArray;
    do {
      H16* h = (H16*)(*p)->mData;
      uint32_t d = 0;
      d = (uint16_t)(h->m10 - h->m12);
      sum += d;
      ++p;
    } while (--n);
  }
  return sum;
}

// ---------------------------------------------------------------------------
// 0x011eab40 -- sum of 32-bit (m04 - m00) ranges
// ---------------------------------------------------------------------------
// @ 0x011eab40
int ArrayOwner::Sum32() {
  uint32_t n = mCount;
  int sum = 0;
  if (n != 0) {
    Elem** p = mArray;
    do {
      H32* h = (H32*)(*p)->mData;
      sum += h->m04 - h->m00;
      ++p;
    } while (--n);
  }
  return sum;
}

// ---------------------------------------------------------------------------
// 0x011eab70 -- release every element and the array through the allocator
// ---------------------------------------------------------------------------
// @ 0x011eab70
void ArrayOwner::Clear() {
  if (mCount == 0)
    return;

  FreeDesc desc;
  for (uint32_t i = 0; i < mCount; ++i) {
    desc.mPtr = mArray[i];
    desc.mZero0 = 0;
    desc.mZero1 = 0;
    desc.mZero2 = 0;
    AllocatorFree(mAlloc, &desc);
  }

  desc.mPtr = mArray;
  desc.mZero0 = 0;
  desc.mZero1 = 0;
  desc.mZero2 = 0;
  AllocatorFree(mAlloc, &desc);
  mCount = 0;
}

// ---------------------------------------------------------------------------
// 0x011eabe0 -- build a string map inside a caller-provided buffer
// ---------------------------------------------------------------------------
// @ 0x011eabe0
void StringMap::Init(void* buffer, int offset, int count) {
  char* base = (char*)buffer;
  MapHeader* d = (MapHeader*)base;
  uint16_t n = (uint16_t)count;
  mData = d;
  d->mSize = n;
  d->mFree = n;
  d->mNext = 0;
  d->mBase = base + 0x18;
  d->mCursor = d->mBase;
  uint32_t* offsets = (uint32_t*)(base + offset - 4 * (int)n);
  d->mOffsets = offsets;
  for (uint32_t i = 0; i < (uint32_t)n; ++i)
    offsets[i] = 0xffffffff;
  uint16_t* slots = (uint16_t*)(base + offset - 6 * (int)n);
  d->mSlots = slots;
  for (uint32_t i = 0; i < (uint32_t)n; ++i)
    slots[i] = 0xffff;
}

// ---------------------------------------------------------------------------
// 0x011eaca0 -- insert a string under a caller-chosen entry index
// ---------------------------------------------------------------------------
// @ 0x011eaca0
void StringMap::Insert(const char* str, uint16_t index) {
  MapHeader* d = mData;
  uint32_t size = d->mSize;
  uint32_t h = HashString(str, g_14f64ac) % size;
  uint16_t slot = d->mSlots[h];
  while (slot != 0xffff) {
    const char* candidate = d->mBase + d->mOffsets[slot];
    if (MapStrcmp(str, candidate) == 0)
      return;
    h = (h + 1) % size;
    slot = d->mSlots[h];
  }

  d->mSlots[h] = index;
  d->mOffsets[index] = (uint32_t)(d->mCursor - d->mBase);

  int len = 0;
  while (str[len] != 0)
    ++len;
  for (int i = 0; i <= len; ++i)
    d->mCursor[i] = str[i];
  d->mCursor += len + 1;
  --d->mFree;
}

// ---------------------------------------------------------------------------
// 0x011eadb0 -- find a string; returns the slot in *out (or the empty slot)
// ---------------------------------------------------------------------------
// @ 0x011eadb0
bool StringMap::Find(const char* str, uint16_t* out) {
  MapHeader* d = mData;
  uint32_t size = d->mSize;
  uint32_t h = HashString(str, g_14f64ac) % size;
  uint32_t start = h;
  uint16_t slot = d->mSlots[h];
  *out = slot;
  if (slot == 0xffff)
    return false;

  for (;;) {
    const char* candidate = d->mBase + d->mOffsets[slot];
    if (MapStrcmp(str, candidate) == 0)
      return true;
    h = (h + 1) % size;
    if (h == start)
      return false;
    slot = d->mSlots[h];
    *out = slot;
    if (slot == 0xffff)
      return false;
  }
}

// ---------------------------------------------------------------------------
// 0x011eae90 -- find an existing entry or claim the next free index
// ---------------------------------------------------------------------------
// @ 0x011eae90
uint16_t StringMap::FindOrInsert(const char* str) {
  uint16_t slot;
  if (Find(str, &slot))
    return slot;

  MapHeader* d = mData;
  uint16_t index = d->mNext;
  while (d->mOffsets[index] != 0xffffffff)
    ++index;
  Insert(str, index);
  d->mNext = (uint16_t)(index + 1);
  return index;
}

// ---------------------------------------------------------------------------
// 0x011eaf10 -- copy every live entry of this map into the target map
// ---------------------------------------------------------------------------
// @ 0x011eaf10
void StringMap::CopyTo(StringMap* target) {
  MapHeader* d = mData;
  for (uint16_t i = 0; i < d->mSize; ++i) {
    int32_t off = (int32_t)d->mOffsets[i];
    if (off != -1)
      target->FindOrInsert(d->mBase + off);
  }
}

// ---------------------------------------------------------------------------
// 0x011eaf50 -- rebase pointers by the holder address, return the second arg
// ---------------------------------------------------------------------------
// @ 0x011eaf50
void* RelocateHolder(int* holder, void* value) {
  uint32_t base = (uint32_t)holder;
  ((uint32_t*)*holder)[0] -= base;
  ((uint32_t*)*holder)[1] -= base;
  ((uint32_t*)*holder)[2] -= base;
  ((uint32_t*)*holder)[3] -= base;
  *holder = (int)((uint32_t)*holder - base);
  return value;
}
