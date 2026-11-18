// Slice s00e25240 - heap sift-down (eastl::adjust_heap instantiation) over
// 8-byte pairs of intrusive ref-counted pointers.
// The tail re-inserts the moved element through the sift-up helper at
// 0x00e243f0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned char u8;
typedef unsigned int  u32;
typedef int           s32;

// vtable-call signature: slot 0 = AddRef, slot 1 = Release
typedef void  (__thiscall *TFv)(void*);
typedef u8    (__cdecl   *TPred)(void*, void*);

// Intrusive ref-counted pointer: the pointee's vtable slot 0 adds a
// reference, slot 1 drops one.
struct IPtr {
  void* p;
  IPtr(const IPtr& o) : p(o.p) { if (p) ((TFv)(*(void***)p)[0])(p); }
  ~IPtr() { if (p) ((TFv)(*(void***)p)[1])(p); }
  IPtr& operator=(const IPtr& o) {
    void* n = o.p;
    void* t = p;
    if (n != t) {
      if (n) ((TFv)(*(void***)n)[0])(n);
      p = n;
      if (t) ((TFv)(*(void***)t)[1])(t);
    }
    return *this;
  }
};

struct Pair {
  IPtr a;
  IPtr b;
  __forceinline Pair& operator=(const Pair& o) {
    a = o.a;
    b = o.b;
    return *this;
  }
};

// 0x00e243f0 - sift-up of the moved element after the hole reached the bottom
void __cdecl FUN_00e243f0(void* base, s32 top, s32 hole, Pair value, TPred pred);

// ======================================================================
// 0x00e25240 - adjust_heap(first, topIndex, len, holeIndex, value, compare)
// ======================================================================

// @ 0x00e25240
void __cdecl FUN_00e25240(Pair* first, s32 topIndex, s32 len, s32 holeIndex,
                          Pair value, TPred compare) {
  s32 child = 2 * holeIndex + 2;
  while (child < len) {
    if (compare(&first[child], &first[child - 1])) --child;
    first[holeIndex] = first[child];
    holeIndex = child;
    child = 2 * child + 2;
  }
  if (child == len) {
    first[holeIndex] = first[child - 1];
    holeIndex = child - 1;
  }
  FUN_00e243f0(first, topIndex, holeIndex, value, compare);
}
