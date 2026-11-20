// EA::Trace zone allocation: the pooled allocator wrapper and the ZoneObject allocation hooks.
// Object file: UTFSpore_Win32/ZoneObject.obj.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_143e104[];

#include "game/types.h"
#include "EA/Allocator/ZoneObject.h"
#include "EA/Allocator/ICoreAllocator.h"

namespace EA {
namespace Trace {
// Fixed-pool allocator token (its layout is opaque here; 0x00925f30 initialises it).
struct C25f30 { C25f30* F(int a2, int a3, int a4); };
}
}
namespace EA {
namespace Trace {
// A 0x20-byte pool allocator (0x00925f30 initialises it) that falls back to a core
// allocator for requests above mLimit and counts those fallbacks.
struct ZoneAllocWrap {
    int w0;                                      // +0x00
    EA::Allocator::ICoreAllocator* mpFallback;   // +0x04
    int w8, wc, w10;                             // +0x08
    unsigned mLimit;                             // +0x14
    int w18;                                     // +0x18
    int mFallbackCount;                          // +0x1c
    void* Inner(unsigned size, int a, int b, int c, int d);  // 0x00925dc0
    void* Alloc(unsigned size, int a, int b);                // 0x00925f90
};
}
}

// @ 0x00925f30
// In-place initialiser of a 0x20-byte fixed-pool allocator: installs the vtable at +0x00
// and sets the free-list/block fields.  Retail's name for the type is not in any header,
// so the fields stay positional.
namespace EA { namespace Trace {
C25f30* C25f30::F(int a2, int a3, int a4)
{
    int* p = (int*)this;
    p[1] = a2;              // +0x04
    p[5] = a4;              // +0x14  allocation unit
    p[2] = 0; p[3] = 0; p[4] = 0;
    p[6] = a3;              // +0x18
    *p = (int)g_143e104;        // +0x00  vtable (address in the retail image)
    p[7] = 0;               // +0x1c
    return this;
}
}}  // namespace EA::Trace

// @ 0x00925f90
namespace EA { namespace Trace {
void* ZoneAllocWrap::Alloc(unsigned size, int a, int b)
{
    if (size <= mLimit) return Inner(size, a, b, 0, 0);
    ++mFallbackCount;
    return mpFallback->Alloc(size, (char const*)a, b, 0, 0);
}
}}  // namespace EA::Trace

// @ 0x00925fe0
namespace EA { namespace Allocator {
void* ZoneObject::operator new(unsigned size, EA::Allocator::ICoreAllocator* alloc, char const* name)
{
    if (!alloc) alloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
    int* r = (int*)alloc->Alloc(size + 8, name, 0, 4, 0);
    if (r) { *r = (int)alloc; return r + 2; }
    return 0;
}
}}  // namespace EA::Allocator

// @ 0x00926020
namespace EA { namespace Allocator {
void* ZoneObject::operator new(unsigned size, char const* name, int flags, int, char const*, int)
{
    EA::Allocator::ICoreAllocator* alloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
    int* r = (int*)alloc->Alloc(size + 8, name, flags, 4, 0);
    if (r) { *r = (int)alloc; return r + 2; }
    return 0;
}
}}  // namespace EA::Allocator

// @ 0x00926060
namespace EA { namespace Trace {
void ZoneObject_delete(void* p)
{
    if (p) {
        void* base = (char*)p - 8;
        (*(EA::Allocator::ICoreAllocator**)base)->Free(base, 0);
    }
}
}}  // namespace EA::Trace
