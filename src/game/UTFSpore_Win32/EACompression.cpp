// src/game/UTFSpore_Win32/EACompression.cpp -- migrated from slice(s) s0092c510, s0092b840 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACompression.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// ---- items of slice s0092c510 begin (TODO(rewrite): local stubs, replace by canonical classes)
int __cdecl Refpack_DeflateBuf(int, int, int, int, int);
extern "C" unsigned short __cdecl _byteswap_ushort(unsigned short);
extern "C" void __cdecl __stosd(unsigned long*, unsigned long, unsigned);
extern "C" int   __cdecl ReadBigEndian(void*, int);       // 0x0092c270
extern "C" void* __cdecl EastlInsert(void*, const void*, unsigned); // 0x011e0744
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(__stosd)
typedef unsigned short ushort;
void* __cdecl memset_thunk(void*, int, unsigned);          // 0x011e073e (memset)
int __cdecl Refpack_iCompress(int, int, int, int, int, int);
void __cdecl WriteToBigEndian(void* dst, unsigned value, int size); // 0x0092c2d0
void* operator new[](unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void operator delete[](void*);                                      // 0x00f47380
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
int __cdecl Refpack_iCompress(int dst, int src, int srcLen, int maxOff, int hash, int link)
{
    uint8_t* _Src = (uint8_t*)src;
    uint8_t* cur = (uint8_t*)src;
    uint8_t* out = (uint8_t*)dst;
    uint32_t* hashT = (uint32_t*)hash;
    uint32_t* linkT = (uint32_t*)link;
    uint32_t uMaxOff = (uint32_t)maxOff;
    uint32_t lit = 0;
    uint32_t remain = (uint32_t)(srcLen - 4);

    memset_thunk(hashT, -1, 0x40000);
    for (;;) {
        if ((int)remain < 0) {
            uint32_t n = lit + 4 + remain;
            while (3 < n) {
                uint32_t chunk = n & 0xfffffffc;
                if (0x70 < (int)chunk) chunk = 0x70;
                n -= chunk;
                if (dst != 0) {
                    *out = (uint8_t)((chunk >> 2) - 0x21);
                    EastlInsert(out + 1, _Src, chunk);
                }
                _Src += chunk;
                out += chunk + 1;
            }
            if (dst != 0) *out = (uint8_t)(n - 4);
            out += 1;
            if (n != 0) {
                if (dst != 0) EastlInsert(out, _Src, n);
                out += n;
            }
            return (int)(out - (uint8_t*)dst);
        }

        uint32_t bestOff = 0;
        uint32_t bestLen = 2;
        uint32_t bestCode = 2;
        uint32_t maxCmp = remain;
        if (0x403 < (int)remain) maxCmp = 0x404;
        uint32_t h = ((uint32_t)cur[0] << 8 | cur[2]) ^ ((uint32_t)cur[1] << 4);
        uint32_t cand = hashT[h];
        uint32_t pos = (uint32_t)(cur - (uint8_t*)src);
        int32_t d = (int32_t)(pos - uMaxOff);
        uint32_t start = d < 1 ? 0 : (uint32_t)d;
        uint32_t uVar11 = cand;

        if ((int)start <= (int)cand) {
            do {
                uint8_t* p = (uint8_t*)src + uVar11;
                if (cur[bestLen] == p[bestLen] && maxCmp != 0) {
                    uint32_t off = (uint32_t)(cur - p);
                    uint32_t i = 0;
                    do {
                        uint8_t* q = p + off;
                        uint8_t c = *p;
                        p++;
                        if (*q != c) break;
                        i++;
                    } while (i < maxCmp);
                    if (bestLen < i) {
                        uint32_t off1 = off - 1;
                        uint32_t code;
                        if (off1 < 0x400 && i < 0xb) code = 2;
                        else if (0x3fff < off1 || (code = 3, 0x43 < i)) code = 4;
                        if ((bestLen - bestCode) + 4 < (i - code) + 4) {
                            bestLen = i;
                            bestCode = code;
                            bestOff = off1;
                            if (0x403 < i) break;
                        }
                    }
                }
                uVar11 = linkT[uVar11 & uMaxOff];
            } while ((int)start <= (int)uVar11);

            if ((bestCode < bestLen) && (3 < (int)remain)) {
                while (3 < lit) {
                    uint32_t chunk = lit & 0xfffffffc;
                    if (0x70 < (int)chunk) chunk = 0x70;
                    lit -= chunk;
                    if (dst != 0) {
                        *out = (uint8_t)((chunk >> 2) - 0x21);
                        EastlInsert(out + 1, _Src, chunk);
                    }
                    _Src += chunk;
                    out += chunk + 1;
                }
                uint8_t cLen = (uint8_t)bestLen;
                uint8_t cLit = (uint8_t)lit;
                uint8_t cOff = (uint8_t)bestOff;
                if (bestCode == 2) {
                    if (dst == 0) out += 2;
                    else {
                        *out = (uint8_t)(((bestOff >> 3) & 0xe0) + (cLen - 3) * 4 + cLit);
                        out[1] = cOff;
                        out += 2;
                    }
                } else {
                    uint8_t cOffHi = (uint8_t)(bestOff >> 8);
                    if (bestCode == 3) {
                        if (dst == 0) out += 3;
                        else {
                            *out = (uint8_t)(cLen + 0x7c);
                            out[1] = (uint8_t)(cOffHi + cLit * 0x40);
                            out[2] = cOff;
                            out += 3;
                        }
                    } else if (dst == 0) {
                        out += 4;
                    } else {
                        *out = (uint8_t)(((bestLen - 5 >> 6) & 0xfc) + ((bestOff >> 0xc) & 0xf0) + cLit - 0x40);
                        out[1] = cOffHi;
                        out[2] = cOff;
                        out[3] = (uint8_t)(bestLen - 5);
                        out += 4;
                    }
                }
                if (lit != 0) {
                    if (dst != 0) EastlInsert(out, _Src, lit);
                    out += lit;
                }
                lit = 0;
                uint32_t cnt = bestLen;
                if (0 < (int)cnt) {
                    do {
                        h = ((uint32_t)cur[0] << 8 | cur[2]) ^ ((uint32_t)cur[1] << 4);
                        cur++;
                        linkT[pos & uMaxOff] = hashT[h];
                        hashT[h] = pos;
                        pos++;
                        cnt--;
                    } while (cnt != 0);
                }
                remain -= bestLen;
                _Src = cur;
                continue;
            }
        }
        lit++;
        linkT[pos & uMaxOff] = cand;
        cur++;
        remain -= 1;
        hashT[h] = pos;
    }
}

// @ 0x0092c8e0
namespace EA {
namespace Refpack {
int DeflateBuf(void * dst, int dstEnd, void const * src, int srcLen, unsigned int flag)
{
    int src_v = (int)src;
    int dst_v = (int)dst;
    (void)dstEnd;
    unsigned int hdr = 0x10fb;
    int hsize = 3;
    int maxOff = 0x1ffff;
    if (srcLen >= 0x1000000) { hdr = 0x90fb; hsize = 4; }
    if ((flag & 1) == 0) { hdr |= 0x4000; maxOff = 0x3fff; }
    uint32_t* hash = new("EACompression/HashTable/uint[]", 0, 0, 0, 0) uint32_t[0x10000];
    uint32_t* link = new("EACompression/Link/uint[]", 0, 0, 0, 0) uint32_t[maxOff + 1];
    int r;
    if (dst_v != 0) {
        *(unsigned short*)dst_v = _byteswap_ushort((unsigned short)hdr);
        WriteToBigEndian((void*)(dst_v + 2), srcLen, hsize);
        r = Refpack_iCompress(dst_v + 2 + hsize, src_v, srcLen, maxOff, (int)hash, (int)link);
    } else {
        r = Refpack_iCompress(0, src_v, srcLen, maxOff, (int)hash, (int)link);
    }
    operator delete[](hash);
    operator delete[](link);
    return r + hsize + 2;
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

// @ 0x0092ca60
#pragma inline_depth(0)
uint32_t __stdcall Refpack_Decompress(ushort* src, int a2, int a3, uint32_t a4, int a5)
{
    ushort b = _byteswap_ushort(*src);
    if ((b & 0x1fff) == 0x10fb) {
        uint32_t v = (uint32_t)ReadBigEndian(src + 1, ((b & 0x8000) == 0x8000) ? 4 : 3);
        if (a3 == 0)
            return v;
        if (v <= a4)
            return (uint32_t)DecodeUnchecked((unsigned char*)a3, (unsigned)a4, (unsigned char*)src);
    }
    return 0xffffffff;
}
#pragma inline_depth()
