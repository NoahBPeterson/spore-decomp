// Slice s00729bd0 — vertex-buffer / span helpers around the UV pipeline.
// Simple accessors/constructors reconstructed; the large bulk/copy routines are partial.
#include "types.h"

void operator_delete(void* p);   // 0x00f47380

extern "C" {
    void* FUN_00f473a0(unsigned size, const char* name, int f, int df, const char* file, int line);
    int   FUN_011f4f20(int a, void* b);
    void  FUN_011f4fd0(void* a);
    void  FUN_00720010(unsigned size);
    void  FUN_0042f0a0(int a, int b, int c, int d);
    void  FUN_0071ddc0(void* p, int a, int b, int c, int d);
}

// @ 0x0072a130  iterator/span-ctor (thiscall, ret 4)
struct SpanIter {
    int   count;   // +0
    int   base;    // +4
    short a;       // +8
    short b;       // +0xa
    int*  owner;   // +0xc
};

struct SpanOwner {
    void*  vptr;   // +0
    char   pad4[8];
    int*   mpBegin;   // +0xc
    int*   mpEnd;     // +0x10
    SpanIter* MakeIter(SpanIter* out);
};

SpanIter* SpanOwner::MakeIter(SpanIter* out)
{
    int base = (int)mpBegin;
    out->count = ((int)mpEnd - base) / 0x30;
    *(short*)((char*)out + 0xa) = 0x30;
    out->base = base;
    *(short*)(out + 2) = 0x30;
    out->owner = (int*)this;
    (*(void(**)(void))vptr)();
    return out;
}

// @ 0x0072a180  release a span buffer unless it aliases the inline storage (fastcall)
void __fastcall FUN_0072a180(int* self)
{
    int* p = (int*)self[0];
    if (p != 0 && p != (int*)self[4])
        operator_delete(p);
}

// @ 0x0072a1a0  vector-like span ctor (thiscall, ret 8)
struct SpanAlloc {
    int* mpBegin;   // +0
    int* mpEnd;     // +4
    int* mpCap;     // +8
    int  pad0;      // +0xc
    int  stride;    // +0x10
    SpanAlloc* Init(int n, int* other);
};

SpanAlloc* SpanAlloc::Init(int n, int* other)
{
    stride = other[1];
    if (n != 0) {
        int* p = (int*)FUN_00f473a0(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        mpBegin = p;
        mpEnd   = p;
        mpCap   = p + n;
        return this;
    }
    mpBegin = 0;
    mpEnd   = 0;
    mpCap   = mpBegin + n;
    return this;
}

// @ 0x0072a080  bounds reset (PARTIAL — SSE stack-roundtrip form not reproduced)
struct Bounds {
    char  pad[0x10];
    float f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c;
};
void FUN_0072a080(Bounds* self)
{
    const float kMax =  3.402823466e+38F;
    const float kMin = -3.402823466e+38F;
    self->f10 = kMax;
    self->f14 = kMax;
    self->f18 = kMax;
    self->f1c = kMin;
    self->f20 = kMin;
    self->f24 = kMin;
    self->f28 = kMax;
    self->f2c = kMax;
    self->f34 = kMin;
    self->f30 = kMax;
    self->f38 = kMin;
    self->f3c = kMin;
}

// ---------------------------------------------------------------------------
// large functions (partial)
// ---------------------------------------------------------------------------

// @ 0x00729bd0  (PARTIAL)
void* FUN_00729bd0(int a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    return 0;
}

// @ 0x00729c60  (PARTIAL)
void FUN_00729c60(void* p, float* a, float* b)
{
    (void)p; (void)a; (void)b;
}

// @ 0x00729de0  (PARTIAL)
void FUN_00729de0(void* a, void* b)
{
    (void)a; (void)b;
}

// @ 0x0072a200  (PARTIAL)
int FUN_0072a200(void* a, void* b, void* c, void* d, unsigned e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x0072a8c0  (PARTIAL)
int FUN_0072a8c0(void* a, int b, int c, unsigned d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x0072aa80  (PARTIAL)
void* FUN_0072aa80(void* self, int n, int a, int b)
{
    (void)self; (void)n; (void)a; (void)b;
    return self;
}
