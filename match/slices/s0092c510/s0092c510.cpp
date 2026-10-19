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
void* __cdecl memset_thunk(void*, int, unsigned);          // 0x011e073e (memset)
void* __cdecl operator_new_named(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0

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
        int ci = *s;
        uint8_t* q = sub;
        while (ci != 0) {
            ci = *q;
            if (ci == 0) return s;
            if (tolower((unsigned char)q[delta]) != tolower(ci)) break;
            ++q;
            ci = q[delta];
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

// @ 0x0092cd20
uint8_t* BitmaskFind(uint8_t* s, uint8_t* sub, uint32_t** out)
{
    if (s == 0) {
        s = (uint8_t*)*out;
        if (s == 0)
            return 0;
    }
    uint32_t mask = 0;
    uint32_t n = 0;
    for (uint8_t* d = sub; *d != 0; ++d) {
        mask |= 0x80000000u >> (*d & 0x1f);
        ++n;
    }
    for (;;) {
        if (*s == 0) {
            *out = 0;
            return 0;
        }
        if ((int32_t)(mask << (*s & 0x1f)) >= 0)
            break;
        uint32_t i;
        for (i = 0; i < n && sub[i] != *s; ++i) { }
        if (i >= n)
            break;
        ++s;
    }
    uint8_t* token = s;
    for (;;) {
        if (*s == 0) {
            *out = 0;
            return token;
        }
        if ((int32_t)(mask << (*s & 0x1f)) < 0 && n != 0) {
            uint32_t i = 0;
            do {
                if (sub[i] == *s) {
                    *s = 0;
                    *out = (uint32_t*)(s + 1);
                    return token;
                }
                ++i;
            } while (i < n);
        }
        ++s;
    }
}

// ---------------------------------------------------------------- large cores (partial)
int __cdecl Refpack_iCompress(int, int, int, int, int, int);
void __cdecl WriteToBigEndian(void* dst, unsigned value, int size); // 0x0092c2d0
void* operator new[](unsigned int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void operator delete[](void*);                                      // 0x00f47380
// @ 0x0092c8e0
int __cdecl Refpack_DeflateBuf(int dst, int dstEnd, int src, int srcLen, int flag)
{
    (void)dstEnd;
    unsigned int hdr = 0x10fb;
    int hsize = 3;
    int maxOff = 0x1ffff;
    if (srcLen >= 0x1000000) { hdr = 0x90fb; hsize = 4; }
    if ((flag & 1) == 0) { hdr |= 0x4000; maxOff = 0x3fff; }
    uint32_t* hash = new("EACompression/HashTable/uint[]", 0, 0, 0, 0) uint32_t[0x10000];
    uint32_t* link = new("EACompression/Link/uint[]", 0, 0, 0, 0) uint32_t[maxOff + 1];
    int r;
    if (dst != 0) {
        *(unsigned short*)dst = _byteswap_ushort((unsigned short)hdr);
        WriteToBigEndian((void*)(dst + 2), srcLen, hsize);
        r = Refpack_iCompress(dst + 2 + hsize, src, srcLen, maxOff, (int)hash, (int)link);
    } else {
        r = Refpack_iCompress(0, src, srcLen, maxOff, (int)hash, (int)link);
    }
    operator delete[](hash);
    operator delete[](link);
    return r + hsize + 2;
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

// @ 0x0092d120
unsigned long long ParseInt64(uint8_t* s, uint8_t** end, unsigned base, char clamp)
{
    uint8_t* p = s;
    uint8_t c = *p;
    uint8_t sign = '+';
    bool anyDigit = false;
    bool overflow = false;
    unsigned long long number = 0;

    while (isspace(c))
        c = *++p;
    if (c == '-' || c == '+') {
        sign = c;
        c = *++p;
    }
    if ((int)base < 0 || base == 1 || base > 0x24) {
        if (end) *end = s;
        return 0;
    }
    if (base == 0) {
        if (c != '0') {
            base = 10;
        } else if (p[1] == 'x' || p[1] == 'X') {
            base = 16;
        } else {
            base = 8;
        }
    }
    if (base == 16 && c == '0' && (p[1] == 'x' || p[1] == 'X')) {
        c = p[2];
        p += 2;
    }

    unsigned long long limit = 0xFFFFFFFFFFFFFFFFull / base;
    unsigned long long rem = 0xFFFFFFFFFFFFFFFFull % base;
    for (;;) {
        unsigned digit;
        if (isdigit(c)) {
            digit = (unsigned)(int)(char)c - 0x30;
        } else if (isalpha(c)) {
            digit = (unsigned)toupper(c) - 0x37;
        } else {
            break;
        }
        if (digit >= base)
            break;
        anyDigit = true;
        if (number < limit || (number == limit && digit <= rem))
            number = number * base + digit;
        else
            overflow = true;
        c = *++p;
    }

    if (!anyDigit) {
        p = s;
    } else if (overflow) {
        if (clamp != 0)
            number = 0xFFFFFFFFFFFFFFFFull;
        else if (sign == '-')
            number = 0x8000000000000000ull;
        else
            number = 0x7FFFFFFFFFFFFFFFull;
        *_errno() = 0x22;
    } else if (clamp == 0) {
        if (sign == '-') {
            if (number > 0x8000000000000000ull) {
                number = 0x8000000000000000ull;
                *_errno() = 0x22;
            }
        } else if (sign == '+') {
            if (number > 0x7FFFFFFFFFFFFFFFull) {
                number = 0x7FFFFFFFFFFFFFFFull;
                *_errno() = 0x22;
            }
        }
    }

    if (end) *end = p;
    if (sign == '-')
        number = (unsigned long long)(-(long long)number);
    return number;
}