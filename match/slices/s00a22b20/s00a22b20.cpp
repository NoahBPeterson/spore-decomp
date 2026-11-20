// SharedHolder destructor (0x00a22b20): the compiler-inlined release of the shared reference
// member, then the tracer-interface vtable restored by the inlined base destructor.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
// (no /GS cookie: the destructor keeps no buffer on the stack, and the sibling destructor at
//  0x00a227d0 in this translation unit has none either)

#include <intrin.h>

namespace EA { namespace Trace {

// Tracing interface the resource derives from.  Its destructor only writes the interface
// vtable back into the object, which is the store at the end of 0x00a22b20 (the unwind
// funclet at 0x01218590 jumps to the out-of-line copy at 0x00a16a20).
class ITracerBase {
public:
    virtual ~ITracerBase() {}
};

} }

// Reference-counted base embedded in a shared allocation: the allocation has one word in
// front of it, so the counted base sits at allocation + 4 and the count at allocation + 8.
struct SharedCountBaseA22 {
    virtual void Destroy(int deleting);
    volatile long mReferenceCount;

    __forceinline void Release() {
        volatile long* count = &mReferenceCount;
        long remaining = _InterlockedDecrement(count);
        if (remaining == 0) {
            _InterlockedExchange(count, 1);
            if (this)
                Destroy(1);
        }
    }
};

struct SharedAllocationA22 {
    unsigned int mAllocationHeader;
    SharedCountBaseA22 mCounted;
};

// Strong reference held by the object; its destructor is what the object destructor inlines.
struct SharedReferenceA22 {
    SharedAllocationA22* mpAllocation;

    ~SharedReferenceA22() {
        if (mpAllocation)
            mpAllocation->mCounted.Release();
    }
};

// @ 0x00a22b20  SharedHolder::~SharedHolder
class SharedHolder : public EA::Trace::ITracerBase {
public:
    unsigned int mUnidentified[9];   // +0x04 .. +0x27 (after the base vtable pointer)
    SharedReferenceA22 mShared;      // +0x28
};

// The destructor is implicit (the original class never declares one).  A global object makes
// the compiler emit it and bind it into the class vtable; no helper definition follows the
// marker above, so the marker binds to the destructor itself.
SharedHolder gSharedHolder;
