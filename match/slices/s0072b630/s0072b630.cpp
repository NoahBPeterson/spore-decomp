// Slice s0072b630 — mesh -> Rw compilation dispatch helpers.
// The three small dispatchers are reconstructed; the big compiler and the fixed-vector
// ctor are partial.
#include "types.h"

extern "C" {
    __declspec(noinline) void FUN_0072b630(void* mesh, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
    void FUN_00729c60(void* p, float* a, float* b);
    void FUN_004c6560(void* dst, void* src, void* n);
    void FUN_0011e0744(void* a, void* b, int c);
}

// @ 0x0072c040
void FUN_0072c040(int* vec, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9)
{
    int n = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n; ++i)
        FUN_0072b630((void*)((int*)vec[0])[i], a2, a3, a4, a5, a6, a7, a8, a9);
}

// @ 0x0072c0a0
void FUN_0072c0a0(void* a, char* b, void* p3, void* p4)
{
    FUN_0072b630(a, p4, b + 0x18, b + 0xb8, b + 0xf4, b + 0x68, b + 0x90, b + 0x40, p3);
    FUN_00729c60(a, (float*)(b + 0x11c), (float*)(b + 0x134));
}

// @ 0x0072c100
void FUN_0072c100(int* vec, int base, void* p3, void* p4)
{
    char* b = (char*)base;
    FUN_0072c040(vec, p4, b + 0x18, b + 0xb8, b + 0xf4, b + 0x68, b + 0x90, b + 0x40, p3);
    int n = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n; ++i)
        FUN_00729c60((void*)((int*)vec[0])[i], (float*)(b + 0x11c), (float*)(b + 0x134));
}

// @ 0x0072b630  SP::CompileToRwMeshes  (PARTIAL)
// An empty body would let cl elide every call to it, collapsing the dispatchers above,
// so the skeleton performs one opaque store (its own bytes are not matched anyway).
volatile int g_sink_72b630;
__declspec(noinline)
void FUN_0072b630(void* mesh, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h)
{
    g_sink_72b630 = 1;
    (void)mesh; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
}

// @ 0x0072c1e0  (PARTIAL: eastl fixed_vector ctor with EH)
void* FUN_0072c1e0(void* self, int n, void* a)
{
    (void)self; (void)n; (void)a;
    return self;
}
