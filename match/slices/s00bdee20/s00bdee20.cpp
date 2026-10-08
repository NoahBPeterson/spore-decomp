// Slice s00bdee20 -- eastl::vector<EA::AutoRefCount<ILogReporter>>::assign (00bdf600): copy-assigns a range
// into the vector, reallocating when the range exceeds capacity.
// Module flags (guess, verify): /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

// ---------------------------------------------------------------- 00bdf600 (eastl::vector<AutoRefCount<ILogReporter>>::assign)
struct ILogReporter;
struct ARCRef { ILogReporter* mpObject; };      // EA::AutoRefCount<ILogReporter>, size 4

struct ARCVectorTuning {                        // eastl::vector<EA::AutoRefCount<EA::Trace::ILogReporter>, sp_vector_allocator>
    ARCRef* mpBegin;                            // +0x0
    ARCRef* mpEnd;                              // +0x4
    ARCRef* mpCapacity;                         // +0x8
    uint32_t mAllocator;                        // +0xc
    ARCRef* mpSentinel;                         // +0x10 (outside VectorBase; compared before freeing)

    ARCRef* AllocCopy(uint32_t n, const ARCRef* first, const ARCRef* last);   // 0x00b95280, thiscall (ret 0xc)
    void DestroyRange(ARCRef* first, ARCRef* last);                            // 0x00b007f0, thiscall, ret 8
    void Assign(const ARCRef* first, const ARCRef* last, uint32_t tag);       // 0x00bdf600, thiscall, ret 0xc
};

ARCRef* DoCopy(const ARCRef* first, const ARCRef* last, ARCRef* dest);  // 0x006782c0, cdecl; eastl do_copy<AutoRefCount*>, returns end
void UninitCopy(ARCRef** outEnd, const ARCRef* first, const ARCRef* last, ARCRef* dest, const ARCRef* last2);  // 0x00829110, cdecl; end returned via outEnd

// @ 0x00bdf600
void ARCVectorTuning::Assign(const ARCRef* first, const ARCRef* last, uint32_t tag) {
    ARCRef* begin = mpBegin;
    uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - begin)) {
        ARCRef* p = AllocCopy(n, first, last);
        DestroyRange(mpBegin, mpEnd);
        ARCRef* old = mpBegin;
        if (old != 0 && old != mpSentinel) operator delete(old);
        mpBegin = p;
        mpEnd = p + n;
        mpCapacity = p + n;
        return;
    }
    uint32_t size = (uint32_t)(mpEnd - begin);
    if (n <= size) {
        ARCRef* newEnd = DoCopy(first, last, begin);
        DestroyRange(newEnd, mpEnd);
        mpEnd = newEnd;
        return;
    }
    const ARCRef* middle = first + size;
    DoCopy(first, middle, begin);
    ARCRef* end;
    UninitCopy(&end, middle, last, mpEnd, last);
    mpEnd = end;
}

}  // namespace SP
