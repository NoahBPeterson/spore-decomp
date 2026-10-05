// Slice s0072f830 — mesh materialisation entry points.
//   00730210 is reconstructed; the others are partial.
#include "types.h"

// @ 0x0072f830  (PARTIAL — skeleton; opaque sink so callers are not collapsed)
volatile int g_sink_72f830;
__declspec(noinline)
void FUN_0072f830(int count, int base, int b8, int a4, int a5)
{
    g_sink_72f830 = count + base + b8 + a4 + a5;
}

// @ 0x00730210
void FUN_00730210(int* p, int param_2)
{
    int  b8    = *(int*)((char*)p + 0xb8);
    int  base  = p[6];
    int  count = (p[7] - base) >> 2;
    FUN_0072f830(count, base, b8, param_2, (int)p);
}

// @ 0x0072f8d0  (PARTIAL)
void FUN_0072f8d0(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
}

// @ 0x0072f9b0  SP::HasCPUBlendShape  (PARTIAL)
void FUN_0072f9b0(void* a, void* b)
{
    (void)a; (void)b;
}

// @ 0x0072fff0  (PARTIAL)
void FUN_0072fff0(void* a)
{
    (void)a;
}
