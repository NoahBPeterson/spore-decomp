// Slice s007e2600: SP::cAppStateManager::cActions default constructor (MSVC 2008 SP1, /O2).
#include "types.h"

namespace eastl {

class allocator {
 public:
  const char* mpName;
};
struct sp_vector_allocator : public allocator { private:};

template <typename A, int N> struct vector_allocator_slot { A mAllocator; unsigned char mPad[8 - N]; };
template <typename A> struct vector_allocator_slot<A, 8> { A mAllocator; };

template <typename T, typename A = allocator>
struct VectorBase { private:
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  vector_allocator_slot<A, sizeof(A)> mAllocatorSlot;   // +0xc, 8 bytes
  // The retail vector constructors touch begin/end/capacity only: the 8-byte allocator slot is
  // a member subobject that is never written (tools/migrate/leafsizes.py).
  VectorBase(T* b, T* e, T* c, const A&) : mpBegin(b), mpEnd(e), mpCapacity(c) {}
};

template <typename T, typename A = allocator>
class vector : public VectorBase<T, A> {
 public:
  explicit vector(const A& a)       // begin/end/capacity only, as the retail constructors do
      : VectorBase<T, A>(0, 0, 0, a) {}
  ~vector();                        // library instantiation, defined elsewhere in the image
};

// eastl::basic_string: begin/end/capacity + the 4-byte allocator.
template <typename T, typename A = allocator>
class basic_string {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
};

}  // namespace eastl

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
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
  };
  // sizeof 0x8
  struct cAppFlagSetting {
    int mFlag;                                       // 0x000
    bool mSetting;                                   // 0x004
  };
  // sizeof 0x50
  struct cActions {
    eastl::vector<cActionMessage, eastl::sp_vector_allocator> mEntryMessages;    // 0x000
    eastl::vector<cActionMessage, eastl::sp_vector_allocator> mExitMessages;     // 0x014
    eastl::vector<cAppFlagSetting, eastl::sp_vector_allocator> mEffectAppFlags;  // 0x028
    eastl::basic_string<wchar_t, eastl::allocator> mDescription;                 // 0x03c
    unsigned int mNextState;                                                     // 0x04c
    cActions();
  };
};

// The shared empty eastl::string16 buffer, 0x01667bac (eastl::gEmptyString16): begin and end point
// at it, capacity at the byte just past its terminator (0x01667bad).
extern wchar_t gEmptyString16[];   // 0x01667bac

// ---------------------------------------------------------------------------------------------
// 0x007e2600: three empty vectors, a description string pointing at the shared empty buffer,
// and "no next state".
// ---------------------------------------------------------------------------------------------
// @ 0x007e2600
cAppStateManager::cActions::cActions()
    : mEntryMessages(eastl::sp_vector_allocator()),
      mExitMessages(eastl::sp_vector_allocator()),
      mEffectAppFlags(eastl::sp_vector_allocator())
{
    mDescription.mpBegin = gEmptyString16;
    mDescription.mpEnd = gEmptyString16;
    mDescription.mpCapacity = (wchar_t*)(gEmptyString16 + 1);   // 0x01667bad
    mNextState = 0xffffffff;
}

}  // namespace SP
