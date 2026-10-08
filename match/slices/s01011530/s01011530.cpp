// Slice s01011530: EASTL adjust_heap instance for SP::cSimulatorUniverse::tGrobShockData (0x01011900).
// Algorithm and memory traffic follow the original: sift the hole down choosing the larger child with
// comp(first[child], first[child-1]), handle the single-child tail, then promote the saved value
// (promote_heap, cdecl, value passed by value), then run the element destructor on the temporary.
// Element copies move only the data words; the 8-byte elapsed field at +8 is not copied during the sift.

namespace SP {
namespace cSimulatorUniverse {

// 40-byte element: vptr-like word at +0, refcount-like word at +4, elapsed u64 at +8, base u64 at +0x10,
// two data dwords at +0x18/+0x1c, a flag byte at +0x20 and a trailing dword at +0x24.
struct tGrobShockData {
  void*    vptr;       // +0x00
  int      refCount;   // +0x04
  unsigned __int64 elapsed;    // +0x08 (not copied by sift moves)
  unsigned __int64 base;       // +0x10
  int      d18;        // +0x18
  int      d1c;        // +0x1c
  unsigned char flag;  // +0x20
  int      d24;        // +0x24
};

typedef bool (__cdecl* tGrobShockCompare)(const tGrobShockData&, const tGrobShockData&);

// Element move used by the sift loop: copies every data word except elapsed (+8..+0xf).
static inline void MoveGrob(tGrobShockData* dst, const tGrobShockData* src) {
  dst->vptr = src->vptr;
  dst->refCount = src->refCount;
  dst->base = src->base;
  dst->d18 = src->d18;
  dst->d1c = src->d1c;
  dst->flag = src->flag;
  dst->d24 = src->d24;
}

// eastl::promote_heap<tGrobShockData*, int, tGrobShockData, comp>. Value is passed by value (40 bytes).
__declspec(noinline) void __cdecl promote_heap_grob(tGrobShockData* first, int topPosition, int position,
                                                    tGrobShockData value, tGrobShockCompare comp) {
  int parent = (position - 1) / 2;
  while (position > topPosition && comp(first[parent], value)) {
    MoveGrob(&first[position], &first[parent]);
    position = parent;
    parent = (position - 1) / 2;
  }
  MoveGrob(&first[position], &value);
}

// eastl::adjust_heap<tGrobShockData*, int, tGrobShockData, comp>
void __cdecl adjust_heap_grob(tGrobShockData* first, int topPosition, int heapSize, int position,
                              tGrobShockData value, tGrobShockCompare comp) {
  int child = 2 * position + 2;
  if (child < heapSize) {
    do {
      if (comp(first[child], first[child - 1]))
        --child;
      MoveGrob(&first[position], &first[child]);
      position = child;
      child = 2 * child + 2;
    } while (child < heapSize);
  }
  if (child == heapSize) {
    MoveGrob(&first[position], &first[child - 1]);
    position = child - 1;
  }
  promote_heap_grob(first, topPosition, position, value, comp);
}

}  // namespace cSimulatorUniverse
}  // namespace SP
