// Slice s01012730 -- SP::cSimulatorUniverse grob-shock helpers (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t size);

namespace eastl {

struct cIntArray {
    int* mpBegin;                                            // +0x00
    int* mpEnd;                                              // +0x04
    void Reserve(int count, const void* allocator);          // 0x00b93c60
};

struct cArrayCopySrc {
    int      mKey;                                           // +0x00
    cIntArray mValues;                                       // +0x04
    uint32_t  mPad0c;                                        // +0x0c
    cIntArray mAllocator;                                    // +0x10
};

struct cArrayCopyDst {
    int      mKey;                                           // +0x00
    cIntArray mValues;                                       // +0x04
    cArrayCopyDst* Assign(const cArrayCopySrc& src);
};

// @ 0x01012f30
cArrayCopyDst* cArrayCopyDst::Assign(const cArrayCopySrc& src)
{
    mKey = src.mKey;
    int bytes = (int)((char*)src.mValues.mpEnd - (char*)src.mValues.mpBegin);
    mValues.Reserve(bytes >> 2, &src.mAllocator);
    int* dst = mValues.mpBegin;
    memcpy(dst, src.mValues.mpBegin, (size_t)bytes);
    mValues.mpEnd = dst + (bytes >> 2);
    return this;
}

} // namespace eastl
