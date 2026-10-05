// Slice s0061b3b0: SP::Pollen YouTube transactions, request/asset helpers and EASTL sort
// internals. Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

// ---- EASTL heap/quick-sort internals (comparator over unsigned indices in 0x118-byte recs) ----
struct sTimedRec {
  char pad[0x30];
  int64_t mTime;  // +0x30
  char pad2[0x118 - 0x38];
};
struct sTimedOwner {
  char pad[0x60];
  sTimedRec* mpTable;
};
struct TimeGreater {
  sTimedOwner* mpOwner;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
  }
};
const unsigned int& median(const unsigned int& a, const unsigned int& b, const unsigned int& c,
                           TimeGreater compare);  // 0x006168a0
unsigned int* get_partition(unsigned int* first, unsigned int* last, unsigned int pivot,
                            TimeGreater compare);  // 0x006189e0
void partial_sort(unsigned int* first, unsigned int* middle, unsigned int* last, TimeGreater compare);

// @ 0x0061bbc0
void quick_sort_impl(unsigned int* first, unsigned int* last, int kRecursionCount, TimeGreater compare) {
  while (((last - first) > 28) && (kRecursionCount > 0)) {
    unsigned int* const position = get_partition(
        first, last, median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
    quick_sort_impl(position, last, --kRecursionCount, compare);
    last = position;
  }
  if (kRecursionCount == 0) partial_sort(first, last, last, compare);
}

// ---------------------------------------------------------------------------------------------
// Request builders / result handlers / EASTL string+vector helpers.
// Only quick_sort_impl above is reconstructed in full; the rest are outlined (see partial.txt).
// ---------------------------------------------------------------------------------------------
class cYouTubeAuthenticationTransaction : public cITransaction {
 public:
  string8 mUsername;  // +0x8
  string8 mPassword;  // +0x18
  string8 mSource;    // +0x28
  bool mCheckRegistration;
  bool HandleResult(void** ppRequest);
};
class cYouTubeVideoUploadTransaction : public cITransaction {
 public:
  uint8_t pad[0x74 - 0x8];
  bool ConstructRequest(void** ppRequest);
};

// @ 0x0061b3b0
bool cYouTubeAuthenticationTransaction::HandleResult(void** ppRequest) {
  (void)ppRequest;
  return false;
}

// @ 0x0061b620
bool cYouTubeVideoUploadTransaction::ConstructRequest(void** ppRequest) {
  (void)ppRequest;
  return false;
}

// @ 0x0061b9a0
bool PollenRequestHelper(void* self, void* arg);
bool PollenRequestHelper(void* self, void* arg) {
  (void)self;
  (void)arg;
  return false;
}

// @ 0x0061bc50  (string swap)
void SwapString(void* a, void* b);
void SwapString(void* a, void* b) {
  (void)a;
  (void)b;
}

// @ 0x0061bcf0  (WritePropertyListAndPNG)
void WritePropertyListAndPNG(void* self, void* a, void* b, void* c);
void WritePropertyListAndPNG(void* self, void* a, void* b, void* c) {
  (void)self;
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x0061be80  (transaction ctor, vtable 0x13fc854)
void* PollenTransactionCtor(void* self, void* a, void* b, void* c, void* d, void* e, void* f);
void* PollenTransactionCtor(void* self, void* a, void* b, void* c, void* d, void* e, void* f) {
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  (void)e;
  (void)f;
  return self;
}

// @ 0x0061bf50
bool PollenHelper286(void* self, void* a);
bool PollenHelper286(void* self, void* a) {
  (void)self;
  (void)a;
  return false;
}

// @ 0x0061c070  (eastl vector assign/DoInsertValue helper)
void* VectorAssign8(void* self, void* src);
void* VectorAssign8(void* self, void* src) {
  (void)src;
  return self;
}

// @ 0x0061c1c0  (DoAllocate(n) + uninitialized_copy of 0x70-byte records)
void* AllocateAndCopy70(unsigned int n, void* a, void* b);
void* AllocateAndCopy70(unsigned int n, void* a, void* b) {
  (void)a;
  (void)b;
  if (n == 0) return 0;
  return EASTL_allocator_allocate(n * 0x70, "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
}

// @ 0x0061c280  (string set_capacity)
void StringSetCapacity(void* self, unsigned int n);
void StringSetCapacity(void* self, unsigned int n) {
  (void)self;
  (void)n;
}
}  // namespace Pollen
}  // namespace SP
