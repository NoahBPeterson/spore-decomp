// Slice s007e2520: eastl::vector<AutoRef> copy-construction of another vector.
// Allocates room for src's elements, copies them with the uninitialized_copy
// helper and publishes the new end pointer.
// Status: not byte-exact -- the original carries the no-frame-pointer EH prologue
// `push -1; push handler; mov eax,fs:[0]; push eax; mov fs:[0],esp; push ecx`
// whose handler funclet (0x120f188) just rethrows (catch-all around the body).
// cl 15 only emits `push ebp; mov ebp,esp` first for every try/catch,
// __try/__except and __try/__finally spelling tried here.  See nonmatching.txt.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct AllocFunction {                          // eastl::allocator's AllocateFunction
    void* Allocate(int n, int flags, const char* name);   // 0x00f473a0
};

struct AllocatorRef {                           // eastl::allocator
    AllocFunction* mpAllocate;                  // +0x00
};

struct VecCopy2 {
    char*         mpBegin;                      // +0x00
    char*         mpEnd;                        // +0x04
    char*         mpCapacity;                   // +0x08
    AllocatorRef  mAllocator;                   // +0x0c

    void growCopy(const VecCopy2* src);         // 0x007e2520
};

extern "C" void* eastl_uninitialized_copy(void** out, void* first, void* last, void* dst, void* alloc); // 0x007e17a0

// @ 0x007e2520
void VecCopy2::growCopy(const VecCopy2* src)
{
    try {
        int n = (int)((src->mpEnd - src->mpBegin) >> 3);
        mpBegin = (char*)src->mAllocator.mpAllocate->Allocate(n * 8, 0x13ebc58, (const char*)0x13ebb38);
        mpCapacity = mpBegin + n * 8;
        void* out = 0;
        eastl_uninitialized_copy(&out, src->mpBegin, src->mpEnd, mpBegin, (void*)src);
        mpEnd = (char*)out;
    } catch (...) {
        throw;
    }
}