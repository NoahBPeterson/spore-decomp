// Slice s0092c510 - EA::Refpack compression/decompression and small string/number helpers.
// Optimized (/O2, no /GS cookies). Large compressor cores are approximated (partial).
#include "types.h"

// ---------------------------------------------------------------- CRT / intrinsics
extern "C" {
__declspec(dllimport) int  __cdecl tolower(int);
__declspec(dllimport) int  __cdecl towlower(int);
__declspec(dllimport) int  __cdecl isspace(int);
__declspec(dllimport) int  __cdecl isdigit(int);
__declspec(dllimport) int  __cdecl isalpha(int);
__declspec(dllimport) int  __cdecl toupper(int);
__declspec(dllimport) char* __cdecl _ecvt(double, int, int*, int*);
__declspec(dllimport) char* __cdecl _fcvt(double, int, int*, int*);
int* __cdecl _errno();
unsigned short __cdecl _byteswap_ushort(unsigned short);
void __cdecl __stosd(unsigned long*, unsigned long, unsigned);
}
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(__stosd)

typedef unsigned short ushort;
int __cdecl Refpack_DeflateBuf(int, int, int, int, int);

// out of slice
extern "C" int   __cdecl ReadBigEndian(void*, int);       // 0x0092c270
extern "C" int   __cdecl DecodeUnchecked(int, int, void*);// 0x0092c340
extern "C" void* __cdecl EastlInsert(void*, const void*, unsigned); // 0x011e0744
void* __cdecl op_delete(void*);                            // 0x00f47380
void* __cdecl op_new__(void*, int, unsigned);              // 0x011e073e

// ---------------------------------------------------------------- refpack glue
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
uint32_t __stdcall Refpack_Decompress(ushort* src, int a2, int a3, uint32_t a4, int a5)
{
    ushort b = _byteswap_ushort(*src);
    if ((b & 0x1fff) == 0x10fb) {
        uint32_t v = (uint32_t)ReadBigEndian(src + 1, ((b & 0x8000) == 0x8000) ? 4 : 3);
        if (a3 == 0)
            return v;
        if (v <= a4)
            return (uint32_t)DecodeUnchecked(a3, (int)a4, src);
    }
    return 0xffffffff;
}

// @ 0x0092cb00
uint32_t* Memset32(uint32_t* dst, uint32_t value, int count)
{
    uint32_t* end = dst + count;
    for (uint32_t* p = dst; p < end; ++p)
        *p = value;
    return dst;
}

// @ 0x0092cb30
uint32_t AppendNarrow(void* dst, const char* src, uint32_t cap)
{
    const char* p = src;
    do { } while (*p++);
    uint32_t len = (uint32_t)(p - src - 1);
    if (len < cap) {
        EastlInsert(dst, src, len + 1);
    } else if (cap != 0) {
        EastlInsert(dst, src, cap - 1);
        ((char*)dst)[cap - 1] = 0;
        return len;
    }
    return len;
}

// @ 0x0092cb90
uint32_t AppendWide(void* dst, const uint16_t* src, uint32_t cap)
{
    const uint16_t* p = src;
    do { } while (*p++);
    uint32_t len = (uint32_t)((p - src - 1) >> 1);
    if (len < cap) {
        EastlInsert(dst, src, len * 2 + 2);
    } else if (cap != 0) {
        EastlInsert(dst, src, cap * 2 - 2);
        *(uint16_t*)((char*)dst + cap * 2 - 2) = 0;
        return len;
    }
    return len;
}

// @ 0x0092cc00
uint8_t* StrIStr(uint8_t* s, uint8_t* sub)
{
    if (*sub == 0) return s;
    if (*s == 0) return 0;
    int delta = (int)s - (int)sub;
    do {
        uint8_t c = *s;
        uint8_t* q = sub;
        while (c != 0) {
            c = *q;
            if (c == 0) return s;
            int a = tolower((unsigned char)q[delta]);
            int b = tolower(c);
            if (a != b) break;
            ++q;
            c = q[delta];
        }
        if (*q == 0) return s;
        ++s;
        ++delta;
    } while (*s != 0);
    return 0;
}

// @ 0x0092cc90
short* StrIStrW(short* s, short* sub)
{
    if (*sub == 0) return s;
    if (*s == 0) return 0;
    int delta = (int)s - (int)sub;
    do {
        short c = *s;
        short* q = sub;
        while (c != 0) {
            c = *q;
            if (c == 0) return s;
            int a = towlower(*(short*)(delta + (int)q));
            int b = towlower(c);
            if (a != b) break;
            ++q;
            c = *(short*)(delta + (int)q);
        }
        if (*q == 0) return s;
        ++s;
        delta += 2;
    } while (*s != 0);
    return 0;
}

// @ 0x0092ce00
char* EcvtCopy(double v, int n, int* dp, int* sign, char* out)
{
    char* p = _ecvt(v, n, dp, sign);
    char* o = out;
    char c;
    do { c = *p++; *o++ = c; } while (c != 0);
    return out;
}

// @ 0x0092ce40
char* FcvtCopy(double v, int n, int* dp, int* sign, char* out)
{
    char* p = _fcvt(v, n, dp, sign);
    char* o = out;
    char c;
    do { c = *p++; *o++ = c; } while (c != 0);
    return out;
}

// @ 0x0092ce80
uint16_t* EcvtW(double v, int n, int* dp, int* sign, uint16_t* out)
{
    char buf[0x160];
    EcvtCopy(v, n, dp, sign, buf);
    char* p = buf;
    uint16_t* o = out;
    while (buf[0] != 0) {
        uint16_t u = (uint16_t)(unsigned char)buf[0];
        buf[0] = p[1];
        ++p;
        *o++ = u;
    }
    *o = 0;
    return out;
}

// @ 0x0092cef0
uint16_t* FcvtW(double v, int n, int* dp, int* sign, uint16_t* out)
{
    char buf[0x160];
    FcvtCopy(v, n, dp, sign, buf);
    char* p = buf;
    uint16_t* o = out;
    while (buf[0] != 0) {
        uint16_t u = (uint16_t)(unsigned char)buf[0];
        buf[0] = p[1];
        ++p;
        *o++ = u;
    }
    *o = 0;
    return out;
}

// @ 0x0092cf60  (static -> base argument travels in eax)
static char* UInt64ToStr(int lo, int hi, char* buf, int sign, int base)
{
    char* p = buf;
    if (sign) {
        *p++ = '-';
        unsigned long long neg = (unsigned long long)((unsigned)lo);
        unsigned long long hv = (unsigned long long)(unsigned)hi;
        // 64-bit negate: (0 - value)
        unsigned long long v0 = (hv << 32) | neg;
        v0 = (unsigned long long)0 - v0;
        lo = (int)v0;
        hi = (int)(v0 >> 32);
    }
    char* start = p;
    unsigned long long v = ((unsigned long long)(unsigned)hi << 32) | (unsigned)lo;
    do {
        unsigned r = (unsigned)(v % (unsigned)base);
        v /= (unsigned)base;
        *p++ = (char)(r < 10 ? r + '0' : r + 'W');
    } while (v != 0);
    *p = 0;
    char* e = p - 1;
    while (start < e) {
        char t = *start;
        *start++ = *e;
        *e-- = t;
    }
    return buf;
}

// @ 0x0092cff0
char* UInt64ToStrAuto(int lo, int hi, char* buf, int base)
{
    __int64 v = ((__int64)hi << 32) | (unsigned)lo;
    if (base == 10 && v < 0)
        return UInt64ToStr(lo, hi, buf, 1, base);
    return UInt64ToStr(lo, hi, buf, 0, base);
}

// @ 0x0092d040
char* UInt64ToStrNoSign(int lo, int hi, char* buf, int base)
{
    return UInt64ToStr(lo, hi, buf, 0, base);
}

// @ 0x0092d060
void UInt64ToStrW(int lo, int hi, uint16_t* out, int base)
{
    char buf[0x30];
    __int64 v = ((__int64)hi << 32) | (unsigned)lo;
    int neg = (base == 10 && v < 0) ? 1 : 0;
    UInt64ToStr(lo, hi, buf, neg, base);
    char* p = buf;
    uint16_t* o = out;
    while (buf[0] != 0) {
        uint16_t u = (uint16_t)(unsigned char)buf[0];
        buf[0] = p[1];
        ++p;
        *o++ = u;
    }
    *o = 0;
}

// @ 0x0092d0d0
void UInt64ToStrW2(int lo, int hi, uint16_t* out, int base)
{
    char buf[0x30];
    UInt64ToStr(lo, hi, buf, 0, base);
    char* p = buf;
    uint16_t* o = out;
    while (buf[0] != 0) {
        uint16_t u = (uint16_t)(unsigned char)buf[0];
        buf[0] = p[1];
        ++p;
        *o++ = u;
    }
    *o = 0;
}

// @ 0x0092cd20  (character-bitmask substring matcher - approximated)
uint8_t* BitmaskFind(uint8_t* s, uint8_t* sub, uint32_t** out)
{
    unsigned mask = 0, len = 0;
    uint8_t* n = sub;
    while (*n) { mask |= 0x80000000u >> (*n & 0x1f); ++len; ++n; }
    uint8_t* p = s;
    while (*p) {
        if ((int)(mask << (*p & 0x1f)) < 0) {
            for (unsigned i = 0; i < len; ++i) {
                if (sub[i] == *p) {
                    *out = 0;
                    return 0;
                }
            }
        }
        ++p;
    }
    *out = 0;
    return 0;
}

// ---------------------------------------------------------------- large cores (partial)
// @ 0x0092c8e0
__declspec(noinline) int Refpack_DeflateBuf(int dst, int dstEnd, int src, int srcLen, int flag)
{
    (void)dst; (void)dstEnd; (void)src; (void)srcLen; (void)flag;
    return 0;
}

// @ 0x0092c510
__declspec(noinline) int Refpack_iCompress(int a1, int a2, int a3, int a4, int a5, int a6)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

// @ 0x0092d120
__declspec(noinline) unsigned long long ParseInt64(uint8_t* s, uint8_t** end, unsigned base, char clamp)
{
    (void)s; (void)base; (void)clamp;
    if (end) *end = s;
    return 0;
}