// Slice s01011530: EASTL adjust_heap instance for SP::cSimulatorUniverse::tGrobShockData (0x01011900).
// Algorithm and memory traffic follow the original: sift the hole down choosing the larger child with
// comp(first[child], first[child-1]), handle the single-child tail, then copy-construct the value for
// promote_heap (cdecl, 40-byte value passed by value), call the out-of-line promote_heap at 0x01010ea0
// and finally destroy the temporary's timer subobject (tail call to SP::cGonzagoTimer::~cGonzagoTimer).
// Element copies move only the data words; the 8-byte timer subobject at +8 is not copied during the sift.

namespace SP {
namespace cSimulatorUniverse {

// The 8-byte subobject at +0x08 of tGrobShockData: a vtable word followed by a flag word. The copy
// constructor of the element re-initialises it instead of copying it, and its destructor is what the
// original calls on the promote_heap temporary.
struct cGonzagoTimer {
  const void* vptr;     // +0x00, set to the vtable at 0x01464450 on construction
  int         flags;    // +0x04, zeroed on construction
  void Destroy();       // 0x00b638b0 -- SP::cGonzagoTimer::~cGonzagoTimer
};

// 40-byte element: vptr-like word at +0, refcount-like word at +4, the timer subobject at +8, base u64 at
// +0x10, two data dwords at +0x18/+0x1c, a flag byte at +0x20 and a trailing dword at +0x24.
struct tGrobShockData {
  void*           vptr;      // +0x00
  int             refCount;  // +0x04
  cGonzagoTimer   timer;     // +0x08 (not copied by the sift moves)
  unsigned __int64 base;     // +0x10
  int             d18;       // +0x18
  int             d1c;       // +0x1c
  unsigned char   flag;      // +0x20
  int             d24;       // +0x24
};

extern const char g_timerVTable[];                   // 0x01464450

typedef bool (__cdecl* tGrobShockCompare)(const tGrobShockData&, const tGrobShockData&);

// Element move used by the sift loop: copies every data word except the timer subobject (+8..+0xf).
static inline void MoveGrob(tGrobShockData* dst, const tGrobShockData* src) {
  dst->vptr = src->vptr;
  dst->refCount = src->refCount;
  dst->base = src->base;
  dst->d18 = src->d18;
  dst->d1c = src->d1c;
  dst->flag = src->flag;
  dst->d24 = src->d24;
}

// Inlined copy constructor of the element: the data words are copied, the timer subobject is
// re-initialised (vtable 0x01464450, zero flag word) rather than copied.
static inline void CopyGrob(tGrobShockData* dst, const tGrobShockData* src) {
  dst->vptr = src->vptr;
  dst->refCount = src->refCount;
  dst->timer.vptr = g_timerVTable;
  dst->timer.flags = 0;
  dst->base = src->base;
  dst->d18 = src->d18;
  dst->d1c = src->d1c;
  dst->flag = src->flag;
  dst->d24 = src->d24;
}

// eastl::promote_heap<tGrobShockData*, int, tGrobShockData, comp> -- out-of-line in the original, the
// value is passed by value (40 bytes) on the stack.
void __cdecl FUN_01010ea0_promote_heap(tGrobShockData* first, int topPosition, int position,
                                       tGrobShockData value, tGrobShockCompare comp);

// eastl::adjust_heap<tGrobShockData*, int, tGrobShockData, comp>
// @ 0x01011900 -- SP::cSimulatorUniverse::adjust_heap_grob
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
  // the promote_heap argument is a fresh copy of the value (timer re-initialised), and the destructor
  // of that temporary only has to destroy the timer subobject.
  tGrobShockData tmp;
  CopyGrob(&tmp, &value);
  FUN_01010ea0_promote_heap(first, topPosition, position, tmp, comp);
  tmp.timer.Destroy();
}

}  // namespace cSimulatorUniverse
}  // namespace SP
