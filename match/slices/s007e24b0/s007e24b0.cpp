// Slice s007e24b0: eastl::vector<SP::cAppStateManager::cActionMessage, eastl::sp_vector_allocator>
// destructor (MSVC 2008 SP1, /O2).
#include "types.h"

void operator_delete(void* p);   // 0x00f47380: EASTL operator delete (checks the header word itself)
void eastl_free(void* p);        // 0x007a41a0: vector<T>::DoFree for non-trivial T (any pointer)

namespace eastl {

struct sp_vector_allocator {
  uint32_t mData[2];
  void deallocate(void* p, size_t) {
    if (((uint32_t*)p)[-1])
      operator_delete(p);
  }
};

template <typename T, typename A = sp_vector_allocator>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  ~vector();
  void DoDestroyValues(T* first, T* last) {
    for (; first < last; ++first)
      first->~T();
  }
};

}  // namespace eastl

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  ~AutoRefCount() { if (mpObject) ReleaseObject(); }
  void ReleaseObject();
};
}  // namespace EA

namespace SP {

template <int> class MessageBasicRC;

class cAppStateManager {
 public:
  // sizeof 0x8
  struct cActionMessage {
    EA::AutoRefCount<MessageBasicRC<5> > mMessage;   // 0x000
    unsigned int mFlags;                             // 0x004
    ~cActionMessage();
  };
};

}  // namespace SP

// The reference-count interface behind the handle: slot 2 is Release().
class RefCountedObject {
 public:
  virtual void i00();
  virtual void i04();
  virtual void i08();
};

namespace EA {
// Out of line (a COMDAT cl can inline into the sink of a destructor is what makes it build an unwind arm).
template <typename T>
void AutoRefCount<T>::ReleaseObject() {
  if (mpObject)
    ((RefCountedObject*)mpObject)->i08();
}

}  // namespace EA

SP::cAppStateManager::cActionMessage::~cActionMessage() {}

namespace eastl {

// ---------------------------------------------------------------------------------------------
// 0x007e24b0: release every message handle, then hand the buffer back to the allocator.
// ---------------------------------------------------------------------------------------------
// @ 0x007e24b0
template <typename T, typename A>
vector<T, A>::~vector() {
  DoDestroyValues(mpBegin, mpEnd);
  if (mpBegin)
    eastl_free(mpBegin);
}

template vector<SP::cAppStateManager::cActionMessage, sp_vector_allocator>::~vector();

}  // namespace eastl
