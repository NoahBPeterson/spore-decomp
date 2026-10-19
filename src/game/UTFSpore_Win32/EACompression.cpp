// src/game/UTFSpore_Win32/EACompression.cpp -- migrated from slice(s) s0092c510, s0092b840 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACompression.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// ---- items of slice s0092c510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned short __cdecl _byteswap_ushort(unsigned short);
extern "C" void __cdecl __stosd(unsigned long*, unsigned long, unsigned);
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(__stosd)
int __cdecl Refpack_DeflateBuf(int, int, int, int, int);
// ---- items of slice s0092c510 end

// @ 0x0092c2d0
namespace EA {
namespace Util {
void WriteToBigEndian(void * dst, unsigned int value, int size)
{
    if (size == 1) { *(unsigned char*)dst = (unsigned char)value; return; }
    if (size == 4) { *(unsigned*)dst = _byteswap_ulong(value); return; }
    unsigned char hi = (unsigned char)(value >> 8);
    if (size == 2) { *(unsigned short*)dst = _byteswap_ushort((unsigned short)value); return; }
    if (size == 3) {
        ((unsigned char*)dst)[0] = (unsigned char)(value >> 16);
        ((unsigned char*)dst)[1] = hi;
        ((unsigned char*)dst)[2] = (unsigned char)value;
    }
}
}
}  // namespace EA::Util

// @ 0x0092c340
int DecodeUnchecked(unsigned char* dst, unsigned hint, unsigned char* src)
{
    (void)dst; (void)hint; (void)src; return 0;
}

// @ 0x0092c510
__declspec(noinline) int Refpack_iCompress(int a1, int a2, int a3, int a4, int a5, int a6)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

// @ 0x0092c8e0
namespace EA {
namespace Refpack {
int DeflateBuf(void * dst, int dstEnd, void const * src, int srcLen, unsigned int flag)
{
    int src_v = (int)src;
    (void)dst; (void)dstEnd; (void)src_v; (void)srcLen; (void)flag;
    return 0;
}
}
}  // namespace EA::Refpack

// @ 0x0092c9f0
int __stdcall Refpack_CompressData(int a1, int a2, int a3, int a4, unsigned a5)
{
    if (a3 != 0)
        return Refpack_DeflateBuf(a3, a4, a1, a2, ~(a5 >> 1) & 1);
    if (a5 & 1)
        return ((unsigned)(a2 * 0x14) >> 4) + 0x20;
    return Refpack_DeflateBuf(0, 0, a1, a2, ~(a5 >> 1) & 1);
}
