// Same shape as s004202f0's RefVector::push_back (0x00420660): an intrusive_ptr
// element vector that grows through its out-of-line DoPushBack.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <intrin.h>
#include <new>

struct AtomicRefCounted_0051d1e0 {
    void* vtable;
    int pad;
    long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();   // 0x00402420
};

template <class T> struct intrusive_ptr_0051d1e0 {
    T* mpObject;
    intrusive_ptr_0051d1e0(const intrusive_ptr_0051d1e0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_0051d1e0() { if (mpObject) mpObject->Release(); }
};

struct RefVector_0051d1e0 {
    intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>* mpBegin;
    intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>* mpEnd;
    intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>* mpCapacity;
    void DoPushBack(intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>* pos,
                    const intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>* v);   // 0x0051d300
    void push_back(const intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>& v);
};

// @ 0x000051d1e0
void RefVector_0051d1e0::push_back(const intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>& v)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) intrusive_ptr_0051d1e0<AtomicRefCounted_0051d1e0>(v);
    else
        DoPushBack(mpEnd, &v);
}
