// @ 0x007d01d0
// W2::f — forwards to the city visualizer's allegiance update (0x007d00e0).
// Retail copies the two arguments into eax/edx, then loads the object's inner
// pointer through ecx and calls a two-argument __thiscall callee (ret 8).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
#include "types.h"
#include <intrin.h>

struct InnerD {
    char pad[0x40];
    void g(int, int);          // 0x007d00e0
};

struct W2 {
    InnerD* m;                 // +0x00
    void f(int a, int b);
};

void W2::f(int a, int b)
{
    m->g(a, b);
    _ReadWriteBarrier();
}
