// Flags: /O2 /MD /Gy /TP
#include <intrin.h>

extern void* vtbl_014ce514; // 0x014ce514

struct System {
    void Free(void* p, int flags); // 0x0112c850
};
extern System* g_pSystem; // 0x016e61a8

struct CMpegBase {
    void** mpVtbl;
    char mPad04[0x48 - 4];
    void* mpPolySynthHistory; // +0x48
    static void operator delete(void* p); // 0x00f47380
    void* FUN_01148d60(unsigned int flags);
};

// @ 0x01148d60
void* CMpegBase::FUN_01148d60(unsigned int flags)
{
    void* history = mpPolySynthHistory;
    _ReadWriteBarrier();
    mpVtbl = &vtbl_014ce514;
    if (history)
        g_pSystem->Free(history, 0);
    if (flags & 1)
        operator delete(this);
    return this;
}
