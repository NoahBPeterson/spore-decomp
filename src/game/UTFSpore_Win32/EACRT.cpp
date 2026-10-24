// src/game/UTFSpore_Win32/EACRT.cpp -- migrated from slice(s) s0092d3e0, s0092c510 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACRT.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/DateTime/DateTime.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int  __cdecl tolower(int);
extern "C" __declspec(dllimport) int  __cdecl towlower(int);
extern "C" __declspec(dllimport) char* __cdecl _ecvt(double, int, int*, int*);
extern "C" __declspec(dllimport) char* __cdecl _fcvt(double, int, int*, int*);
extern "C" unsigned short __cdecl _byteswap_ushort(unsigned short);
extern "C" void __cdecl __stosd(unsigned long*, unsigned long, unsigned);
extern "C" void* __cdecl EastlInsert(void*, const void*, unsigned); // 0x011e0744
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(__stosd)

// ---- items of slice s0092c510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int  __cdecl tolower(int);
extern "C" __declspec(dllimport) int  __cdecl towlower(int);
extern "C" __declspec(dllimport) char* __cdecl _ecvt(double, int, int*, int*);
extern "C" __declspec(dllimport) char* __cdecl _fcvt(double, int, int*, int*);
extern "C" void* __cdecl EastlInsert(void*, const void*, unsigned); // 0x011e0744
// ---- items of slice s0092c510 end

// ---- items of slice s0092d3e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned short c, int type);
extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short c);
extern "C" int*     __cdecl _errno();                               // msvcr90!_errno
extern "C" __declspec(dllimport) char* __cdecl _ltoa(long value, char* buffer, int radix);
extern "C" double   __cdecl floor(double x);
extern "C" double   __cdecl fabs(double x);
extern "C" double   __cdecl log10(double x);
extern "C" double   __cdecl pow(double x, double y);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long value, wchar_t* buffer, int radix);
// ---- items of slice s0092d3e0 end

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
    uint32_t len = (uint32_t)(p - src - 1);
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
    int delta = (int)s - (int)sub;              // original keeps s - sub and indexes q + delta
    do {
        unsigned short c = (unsigned short)*s;
        short* q = sub;
        while (c != 0) {
            c = (unsigned short)*q;
            if (c == 0) return s;
            unsigned short a = (unsigned short)*(short*)(delta + (int)q);
            unsigned short la = (unsigned short)towlower(a);   // original moves zero-extended
            unsigned short lb = (unsigned short)towlower(c);
            if (la != lb) break;
            ++q;
            c = (unsigned short)*(short*)(delta + (int)q);
        }
        if (*q == 0) return s;
        ++s;
        delta += 2;
    } while (*s != 0);
    return 0;
}

// @ 0x0092cd20
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

// Body of 0x0092cf60.  The original helper is TU-static and gets cl's register
// convention for the wrappers' direct calls; the VA's external entry point below
// keeps the original's caller-visible shape (four cdecl slots + base in eax).
static __declspec(noinline) char* UInt64ToStrImpl(int lo, int hi, char* buf, int sign, int base)
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
    long long divisor = base;                       // original sign-extends the base (cdq)
    unsigned long long d = (unsigned long long)divisor;
    do {
        unsigned r = (unsigned)(v % d);
        v /= d;
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

// @ 0x0092cf60  (static in the original: the base argument arrives in eax, not on the stack)
char* UInt64ToStr(int lo, int hi, char* buf, int sign, int base)
{
    int inBase;
    __asm { mov inBase, eax }           // the original's caller puts the base in eax
    (void)base;                         // the fifth cdecl slot is never read
    return UInt64ToStrImpl(lo, hi, buf, sign, inBase);
}

// @ 0x0092cff0
char* UInt64ToStrAuto(int lo, int hi, char* buf, int base)
{
    __int64 v = ((__int64)hi << 32) | (unsigned)lo;
    if (base == 10 && v < 0)
        return UInt64ToStrImpl(lo, hi, buf, 1, base);
    return UInt64ToStrImpl(lo, hi, buf, 0, base);
}

// @ 0x0092d040
char* UInt64ToStrNoSign(int lo, int hi, char* buf, int base)
{
    return UInt64ToStrImpl(lo, hi, buf, 0, base);
}

// @ 0x0092d060
void UInt64ToStrW(int lo, int hi, uint16_t* out, int base)
{
    char buf[0x30];
    __int64 v = ((__int64)hi << 32) | (unsigned)lo;
    int neg = (base == 10 && v < 0) ? 1 : 0;
    UInt64ToStrImpl(lo, hi, buf, neg, base);
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
    UInt64ToStrImpl(lo, hi, buf, 0, base);
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

// @ 0x0092d120
__declspec(noinline) unsigned long long ParseInt64(uint8_t* s, uint8_t** end, unsigned base, char clamp)
{
    (void)s; (void)base; (void)clamp;
    if (end) *end = s;
    return 0;
}

// @ 0x0092d3e0
uint64_t __cdecl StrtoU64Common16(const wchar_t* nptr, const wchar_t** endptr, unsigned int base, char group)
{
    const wchar_t* s = nptr;
    wchar_t c = *s;
    wchar_t sign = L'+';
    uint64_t number = 0;
    bool bDigits = false;
    bool bOver = false;

    while (iswctype(c, 8)) {        // _SPACE
        ++s;
        c = *s;
    }
    if (c == L'-' || c == L'+') {
        sign = c;
        c = s[1];
        ++s;
    }
    if ((int)base < 0 || base == 1 || base > 36) {
        if (endptr)
            *endptr = nptr;
        return 0;
    }
    if (base == 0) {
        if (c != L'0') {
            base = 10;
        } else if (s[1] == L'x' || s[1] == L'X') {
            base = 16;
            c = s[2];
            s += 2;
        } else {
            base = 8;
        }
    } else if (c == L'0' && (s[1] == L'x' || s[1] == L'X')) {
        c = s[2];
        s += 2;
    }

    uint64_t maxQuot = ~(uint64_t)0 / base;
    uint64_t maxRem  = ~(uint64_t)0 % base;

    for (;;) {
        uint64_t digit;
        if (iswctype(c, 4)) {           // _DIGIT
            digit = (uint64_t)(unsigned int)c - L'0';
        } else if (iswctype(c, 0x103)) { // _HEX
            digit = (uint64_t)(unsigned int)towupper(c) - (L'A' - 10);
        } else {
            break;
        }
        if (digit >= base)
            break;
        bDigits = true;
        if (number < maxQuot || (number == maxQuot && digit <= maxRem)) {
            number = number * base + digit;
        } else {
            bOver = true;
        }
        c = *s;
        ++s;
    }
    --s;

    if (!bDigits) {
        s = nptr;
    } else if (bOver) {
        if (group != 0) {
            number = ~(uint64_t)0;
        } else if (sign == L'-') {
            number = (uint64_t)0x8000000000000000ull;
        } else {
            number = (uint64_t)0x7fffffffffffffffull;
        }
        *_errno() = 0x22;               // ERANGE
    } else if (group == 0) {
        if (sign == L'-') {
            if (number > (uint64_t)0x8000000000000000ull) {
                number = (uint64_t)0x8000000000000000ull;
                *_errno() = 0x22;
            }
        } else if (sign == L'+') {
            if (number > (uint64_t)0x7fffffffffffffffull) {
                number = (uint64_t)0x7fffffffffffffffull;
                *_errno() = 0x22;
            }
        }
    }
    if (endptr)
        *endptr = s;
    if (sign == L'-')
        number = (uint64_t)(-(int64_t)number);
    return number;
}

// @ 0x0092d730
__declspec(noinline) char* __cdecl FUN_0092d730(double value, char* buffer, int size, int precision, char sci)
{
    int n = 0;
    int pos = 0;

    if (size < 1)
        return 0;
    if (value == 0.0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }
    if (sci != 0) {
        int exp = (int)floor(log10(fabs(value)));
        if (precision <= exp || exp < -4) {
            int scale = 10;
            int digits = 1;
            if (exp > 9) {
                do {
                    scale *= 10;
                    ++digits;
                } while (scale <= exp);
            }
            double scaled = value * pow(10.0, (double)(-(exp)));
            int r = (int)(size_t)FUN_0092d730(scaled, buffer, size - digits - 2,
                                             precision - 1, 0);
            if (r == 0)
                return 0;
            char* p = buffer;
            while (*p)
                ++p;
            *p = 'e';
            p[1] = (exp < 0 ? '-' : '+');
            _ltoa((long)(exp < 0 ? -exp : exp), p + 2, 10);
            return buffer;
        }
    }

    int decpt;
    int signFlag;
    char* digits = _fcvt(value, 0x40, &decpt, &signFlag);
    if (signFlag != 0) {
        if (size < 1) {
            buffer[0] = '\0';
            return 0;
        }
        buffer[0] = '-';
        n = 1;
    }
    if (fabs(value) < 1.0) {
        if (size <= n)
            goto Overflow;
        buffer[n] = '0';
        ++n;
    }
    if (0 < decpt) {
        do {
            if (digits[pos] == '\0')
                break;
            if (size <= n)
                goto Overflow;
            buffer[n] = digits[pos];
            ++pos;
            ++n;
        } while (pos < decpt);
    }
    char* p = digits + pos;
    char cp = *p;
    if (cp != '\0') {
        int lastNonZero = pos;
        do {
            if (cp != '0')
                lastNonZero = (int)(p - digits) + 1;
            cp = p[1];
            ++p;
        } while (cp != '\0');
        if (pos < lastNonZero && 0 < precision) {
            if (size <= n)
                goto Overflow;
            buffer[n] = '.';
            for (; n = n + 1, decpt < 0; decpt = decpt + 1) {
                if (size <= n)
                    goto Overflow;
                buffer[n] = '0';
            }
            int cnt = 0;
            if (0 < precision) {
                do {
                    if (lastNonZero <= pos || digits[pos] == '\0')
                        break;
                    if (size <= n) {
                        unsigned int u = ((unsigned int)(n - 1) < 1) - 1 & (unsigned int)(n - 1);
                        buffer[u] = '\0';
                        n = (int)u - 1;
                        if (n < 1)
                            return 0;
                        do {
                            if (buffer[n] != '0')
                                return 0;
                            buffer[n] = '\0';
                            n = n - 1;
                        } while (0 < n);
                        return 0;
                    }
                    buffer[n] = digits[pos];
                    ++cnt;
                    ++n;
                    ++pos;
                } while (cnt < precision);
            }
        }
    }
    if (n < size) {
        buffer[n] = '\0';
        return buffer;
    }

Overflow:
    buffer[((unsigned int)(n - 1) < 1) - 1 & (unsigned int)(n - 1)] = '\0';
    return 0;
}

// @ 0x0092d9b0
namespace  {
wchar_t * FtoaEnglish16(double value, wchar_t * buffer, int size, int precision, bool sci)
{
    int n = 0;
    int pos = 0;

    if (size < 1)
        return 0;
    if (value == 0.0) {
        buffer[0] = L'0';
        buffer[1] = 0;
        return buffer;
    }
    if (sci != 0) {
        int exp = (int)floor(log10(fabs(value)));
        if (precision <= exp || exp < -4) {
            int scale = 10;
            int digits = 1;
            if (exp > 9) {
                do {
                    scale *= 10;
                    ++digits;
                } while (scale <= exp);
            }
            double scaled = value * pow(10.0, (double)(-(exp)));
            int r = (int)(size_t)FtoaEnglish16(scaled, buffer, size - digits - 2,
                                               precision - 1, 0);
            if (r == 0)
                return 0;
            wchar_t* p = buffer;
            while (*p)
                ++p;
            *p = L'e';
            p[1] = (exp < 0 ? L'-' : L'+');
            _ltow((long)(exp < 0 ? -exp : exp), p + 2, 10);
            return buffer;
        }
    }

    int decpt;
    int signFlag;
    char* digits = _fcvt(value, 0x40, &decpt, &signFlag);
    if (signFlag != 0) {
        if (size < 1) {
            buffer[0] = 0;
            return 0;
        }
        buffer[0] = L'-';
        n = 1;
    }
    if (fabs(value) < 1.0) {
        if (size <= n)
            goto Overflow;
        buffer[n] = L'0';
        ++n;
    }
    if (0 < decpt) {
        do {
            if (digits[pos] == '\0')
                break;
            if (size <= n)
                goto Overflow;
            buffer[n] = (wchar_t)(unsigned char)digits[pos];
            ++pos;
            ++n;
        } while (pos < decpt);
    }
    char* p = digits + pos;
    char cp = *p;
    if (cp != '\0') {
        int lastNonZero = pos;
        do {
            if (cp != '0')
                lastNonZero = (int)(p - digits) + 1;
            cp = p[1];
            ++p;
        } while (cp != '\0');
        if (pos < lastNonZero && 0 < precision) {
            if (size <= n)
                goto Overflow;
            buffer[n] = L'.';
            for (; n = n + 1, decpt < 0; decpt = decpt + 1) {
                if (size <= n)
                    goto Overflow;
                buffer[n] = L'0';
            }
            int cnt = 0;
            if (0 < precision) {
                do {
                    if (lastNonZero <= pos || digits[pos] == '\0')
                        break;
                    if (size <= n)
                        goto Overflow;
                    buffer[n] = (wchar_t)(unsigned char)digits[pos];
                    ++cnt;
                    ++n;
                    ++pos;
                } while (cnt < precision);
            }
        }
    }
    if (n < size) {
        buffer[n] = 0;
        return buffer;
    }

Overflow:
    buffer[((unsigned int)(n - 1) < 1) - 1 & (unsigned int)(n - 1)] = 0;
    return 0;
}
}  // namespace 
