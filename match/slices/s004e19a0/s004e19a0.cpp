// Same shape as s004202f0's RefVector/TripleVector/SmallBuffer helpers (donor 0x0x004206f0).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <intrin.h>
#include <new>
#include "types.h"
#pragma intrinsic(_InterlockedIncrement)

extern "C" void __cdecl EASTL_allocator_deallocate_f47380(void* p);  // 0x00f47380

struct AtomicRefCounted_004e19a0 {
    void* vtable;
    int pad;
    long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
};

template <class T> struct intrusive_ptr_004e19a0 {
    T* mpObject;
    intrusive_ptr_004e19a0(const intrusive_ptr_004e19a0& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
};

struct Triple_004e19a0 { int a, b, c; };

struct TripleVector_004e19a0 {
    char pad0[4];
    Triple_004e19a0* mpEnd;
    Triple_004e19a0* mpCapacity;
    void DoPushBack_004e19a0(Triple_004e19a0* pos, const Triple_004e19a0* v);
    void push_back(const Triple_004e19a0& v);  // 0x4e3e10

};

// @ 0x00004e19a0
void TripleVector_004e19a0::push_back(const Triple_004e19a0& v)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) Triple_004e19a0(v);
    else
        DoPushBack_004e19a0(mpEnd, &v);
}
