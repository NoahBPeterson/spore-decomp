// Same shape as s004202f0's RefVector::~RefVector (0x00420600): walk the element
// range, run each intrusive_ptr's destructor, then the container teardown.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <intrin.h>
#include <new>

struct AtomicRefCounted_0051d180 {
    void* vtable;
    int pad;
    long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();   // 0x00402420
};

template <class T> struct intrusive_ptr_0051d180 {
    T* mpObject;
    intrusive_ptr_0051d180(const intrusive_ptr_0051d180& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_0051d180() { if (mpObject) mpObject->Release(); }
};

struct RefVector_0051d180 {
    intrusive_ptr_0051d180<AtomicRefCounted_0051d180>* mpBegin;
    intrusive_ptr_0051d180<AtomicRefCounted_0051d180>* mpEnd;
    intrusive_ptr_0051d180<AtomicRefCounted_0051d180>* mpCapacity;
    void Destroy();   // 0x004c0b80
    ~RefVector_0051d180();
};

// @ 0x000051d180
RefVector_0051d180::~RefVector_0051d180()
{
    typedef intrusive_ptr_0051d180<AtomicRefCounted_0051d180> Ref;
    Ref* last = mpEnd;
    Ref* first;
    int unusedTemp[3];   // reproduces the original frame size (inlined helper temporaries)
    for (first = mpBegin; first < last; ++first)
        first->~Ref();
    Destroy();
}
