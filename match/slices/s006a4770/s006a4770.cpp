// Slice s006a4770: one eastl::vector-like constructor (element size 0x18,
// value = { FLT_MAX x3, -FLT_MAX x3 }) filled by an out-of-line helper 0x00511990.
#include "../../include/types.h"
#include <float.h>

static const char kAllocPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

extern "C" void* EA_Alloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  Fill18(void* dst, int n, const void* value, int m);                                  // 0x00511990

struct Box18 { float x, y, z; float nx, ny, nz; };

struct Vec18 {
    void* begin; void* end; void* cap;
    Vec18* Init(unsigned n, const void* alloc);
};

// @ 0x006a4770
Vec18* Vec18::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x18, "App", 0, 0, kAllocPath, 0xd1) : 0;
    cap = p + n * 0x18;
    Box18 v;
    v.x = FLT_MAX;
    v.y = FLT_MAX;
    v.z = FLT_MAX;
    v.nx = -FLT_MAX;
    v.ny = -FLT_MAX;
    v.nz = -FLT_MAX;
    begin = p;
    end = p;
    Fill18(p, n, &v, n);
    end = (char*)begin + n * 0x18;
    return this;
}
