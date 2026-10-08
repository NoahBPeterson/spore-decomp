// slice s011ea070 -- RenderWare core (rw::core::stdc) printf engine: Vsnprintf (1788 bytes).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-  (VS2008 defaults, no stack cookie).
//
// The original TU keeps its format-spec parsers and string emitters as static helpers with
// register calling conventions (eax = format/source pointer, edx/esi = out flags, edi = &remain,
// ebx = &count).  They are written here as ordinary static functions.  The numeric converters
// (ConvertIToA, ConvertI64ToA, ConvertfToA, ...) are separate exported functions with a normal
// stack convention and are declared extern at their original addresses.
#include "types.h"
#include <intrin.h>

namespace rw { namespace core { namespace stdc {
char* ConvertIToA(int value, char* buf, int radix);                                      // 0x011ED0F0 (cdecl)
char* ConvertI64ToA(uint32_t lo, uint32_t hi, char* buf, int radix, int isUnsigned);    // 0x011ED190 (cdecl)
char* ConvertfToA(char* buf, double v, int precision);                                   // 0x011E8F10 (cdecl)
} } }

char* FormatE(char* buf, double v, int precision);                       // 0x011E9090 (cdecl)  "%e"
char* FormatEUpper(char* buf, double v, int precision);                  // 0x011E9100 (cdecl)  "%E"
char* ConvertUToHex(uint32_t v, char* buf, int lower);                   // 0x011ED230 (cdecl)
char* Hex64Upper(char* buf, uint32_t lo, uint32_t hi);                   // 0x011E9950 (cdecl)
char* Hex64Lower(char* buf, uint32_t lo, uint32_t hi);                   // 0x011E99B0 (cdecl)
int   StrLen(const char* s);                                             // 0x011E8C40 (cdecl)
wchar_t* WidenAscii(wchar_t* dst, const char* src);                      // 0x011ED270 (cdecl)

#define VA_ARG(ap, T) (*(T*)((ap += sizeof(T)) - sizeof(T)))

static const char kNullText[7] = { '(', 'n', 'u', 'l', 'l', ')', 0 };    // 0x0149C914

// ---------------------------------------------------------------- format-spec parsers
// 0x011E9270: consumes at most one flag character.
__declspec(noinline) static const char* ParseFlags(const char* p, bool* zeroPad, bool* rightJustify)
{
    *zeroPad = false;
    *rightJustify = true;
    switch (*p) {
    case ' ':
    case '#':
    case '+':
        return p + 1;
    case '-':
        *rightJustify = false;
        return p + 1;
    case '0':
        *zeroPad = true;
        return p + 1;
    }
    return p;
}

// 0x011E92C0
__declspec(noinline) static const char* ParseWidth(const char* p, int* width)
{
    *width = 0;
    while (*p >= '0' && *p <= '9') {
        *width = *width * 10;
        *width = *width + (*p - '0');
        ++p;
    }
    return p;
}

// 0x011E9300
__declspec(noinline) static const char* ParsePrecision(const char* p, int* precision)
{
    *precision = 6;
    if (*p != '.')
        return p;
    ++p;
    *precision = 0;
    while (*p >= '0' && *p <= '9') {
        *precision = *precision * 10;
        *precision = *precision + (*p - '0');
        ++p;
    }
    if (*precision > 10)
        *precision = 10;
    return p;
}

// ---------------------------------------------------------------- string emitters
// 0x011E9350: copies src (narrow, or wide when `wide`) to dst, no padding.  A null src prints "(null)".
__declspec(noinline) static char* EmitPlain(char* dst, bool wide, const char* src, int* count, unsigned* remain)
{
    char nullText[7];
    for (int i = 0; i < 7; ++i) nullText[i] = kNullText[i];
    if (wide) {
        wchar_t wnull[8];
        const wchar_t* w = WidenAscii(wnull, nullText);
        const wchar_t* s = (const wchar_t*)src;
        if (!s) s = w;
        while (*s) {
            if (*remain > 0) {
                *dst++ = (char)*s;
                --*remain;
            }
            ++*count;
            ++s;
        }
    } else {
        if (!src) src = nullText;
        while (*src) {
            if (*remain > 0) {
                *dst++ = *src;
                --*remain;
            }
            ++*count;
            ++src;
        }
    }
    return dst;
}

// 0x011E9400: left-justified: copy, then pad with spaces up to `width`.
__declspec(noinline) static char* EmitLeft(char* dst, int width, bool wide, const char* src, int* count, unsigned* remain)
{
    char nullText[7];
    for (int i = 0; i < 7; ++i) nullText[i] = kNullText[i];
    int len = 0;
    if (wide) {
        wchar_t wnull[8];
        const wchar_t* w = WidenAscii(wnull, nullText);
        const wchar_t* s = (const wchar_t*)src;
        if (!s) s = w;
        for (const wchar_t* q = s; *q; ++q) ++len;
        while (*s) {
            if (*remain > 0) {
                *dst++ = (char)*s;
                --*remain;
            }
            ++*count;
            ++s;
        }
    } else {
        if (!src) src = nullText;
        while (*src) {
            if (*remain > 0) {
                *dst++ = *src;
                --*remain;
            }
            ++*count;
            ++src;
            ++len;
        }
    }
    int pad = width - len;
    while (pad > 0) {
        if (*remain > 0) {
            *dst++ = ' ';
            --*remain;
        }
        ++*count;
        --pad;
    }
    return dst;
}

// 0x011E94F0: right-justified: pad (zeros or spaces) up to `width`, then copy.
__declspec(noinline) static char* EmitRight(char* dst, int* count, bool wide, bool zero, int width, const char* src, unsigned* remain)
{
    char nullText[7];
    for (int i = 0; i < 7; ++i) nullText[i] = kNullText[i];
    int len;
    const wchar_t* ws = 0;
    if (wide) {
        wchar_t wnull[8];
        const wchar_t* w = WidenAscii(wnull, nullText);
        ws = (const wchar_t*)src;
        if (!ws) ws = w;
        len = 0;
        for (const wchar_t* q = ws; *q; ++q) ++len;
    } else {
        if (!src) src = nullText;
        len = StrLen(src);
    }
    int pad = width - len;
    while (pad > 0) {
        if (*remain > 0) {
            --*remain;
            *dst++ = zero ? '0' : ' ';
        }
        ++*count;
        --pad;
    }
    if (wide) {
        while (*ws) {
            if (*remain > 0) {
                *dst++ = (char)*ws;
                --*remain;
            }
            ++*count;
            ++ws;
        }
    } else {
        while (*src) {
            if (*remain > 0) {
                *dst++ = *src;
                --*remain;
            }
            ++*count;
            ++src;
        }
    }
    return dst;
}

// ---------------------------------------------------------------- number helpers
// 0x011E98B0: appends the decimal digits of v (nothing for 0), returns the end.
static char* U64Digits(char* buf, unsigned __int64 v)
{
    if (v == 0)
        return buf;
    unsigned __int64 q = v / 10;
    char* p = U64Digits(buf, q);
    *p = (char)(v - q * 10) + '0';
    return p + 1;
}

// 0x011E9900: unsigned 64-bit decimal.
__declspec(noinline) static char* U64ToDec(char* buf, unsigned __int64 v)
{
    if (v == 0) {
        buf[0] = '0';
        buf[1] = 0;
        return buf;
    }
    char* p = U64Digits(buf, v);
    *p = 0;
    return buf;
}

// 0x011E8C90: splits |v| into mantissa in [1,10) and decimal exponent; exp == 999 means NaN/Inf/out of range.
__declspec(noinline) static void DecomposeDecimal(double v, int* exp, double* mant)
{
    *exp = 0;
    if (v == 0.0) {
        *mant = 0.0;
        return;
    }
    bool neg = false;
    if (v < 0.0) {
        v = v * -1.0;
        neg = true;
    }
    unsigned hi = ((unsigned*)&v)[1];
    if ((hi & 0x7fe00000) == 0x7fe00000) {
        *mant = 0.0;
        *exp = 999;
        return;
    }
    if (!(v < 1.0)) {
        if (!(v < 1e10)) {
            int e = 0;
            do {
                v = v * 1e-10;
                e += 10;
            } while (!(v < 1e10));
            *exp = e;
        }
        if (!(v < 10.0)) {
            int e = *exp;
            do {
                v = v * 0.1;
                ++e;
            } while (!(v < 10.0));
            *exp = e;
        }
    } else {
        if (!(1e-10 < v)) {
            int e = 0;
            do {
                v = v * 1e10;
                e -= 10;
            } while (!(1e-10 < v));
            *exp = e;
        }
        if (v < 1.0) {
            int e = *exp;
            do {
                v = v * 10.0;
                --e;
            } while (v < 1.0);
            *exp = e;
        }
    }
    if (*exp == -312) {
        *mant = 0.0;
        *exp = 999;
        return;
    }
    if (neg)
        v = v * -1.0;
    *mant = v;
}

// 0x011E9170: drops trailing zeros and a dangling '.'.
__declspec(noinline) static char* StripZeros(char* p)
{
    if (p[-1] == '0') {
        do {
            --p;
            *p = 0;
        } while (p[-1] == '0');
    }
    if (p[-1] == '.') {
        --p;
        *p = 0;
    }
    return p;
}

// 0x011E91A0: "%g" / "%G" (precision in ebx in the original).
__declspec(noinline) static char* FormatG(char* buf, double v, bool upper, int precision)
{
    int exp;
    double mant;
    DecomposeDecimal(v, &exp, &mant);
    if (exp >= -4 && exp < precision) {
        char* p = rw::core::stdc::ConvertfToA(buf, v, precision);
        return StripZeros(p);
    }
    char* p = rw::core::stdc::ConvertfToA(buf, mant, precision);
    if (p[-1] == '0') {
        do {
            --p;
            *p = 0;
        } while (p[-1] == '0');
    }
    if (p[-1] == '.') {
        --p;
        *p = 0;
    }
    *p = upper ? 'E' : 'e';
    ++p;
    if (exp == 999) {
        *p = '?';
        ++p;
        *p = '?';
        p[1] = 0;
        return p;
    }
    return rw::core::stdc::ConvertIToA(exp, p, 10);
}

// ---------------------------------------------------------------- the printf engine
// @ 0x011EA070
int Vsnprintf(char* dst, unsigned remain, const char* fmt, char* ap)
{
    int count = 0;
    char buf[0x70];
    unsigned size = remain;
    if (remain == 0)
        return -1;
    if (fmt) {
        char c = *fmt;
        --remain;
        if (c) {
            for (;;) {
                if (remain == 0)
                    break;
                if (c != '%') {
                    *dst++ = c;
                    ++fmt;
                    ++count;
                    --remain;
                    c = *fmt;
                    if (c == 0) break;
                    continue;
                }
                bool zeroPad, rightJustify;
                int width, precision;
                const char* src = buf;
                bool emit = true;
                bool wideStr = false;
                bool numeric = false;
                bool is64 = false;

                ++fmt;
                fmt = ParseFlags(fmt, &zeroPad, &rightJustify);
                fmt = ParseWidth(fmt, &width);
                fmt = ParsePrecision(fmt, &precision);
                if (*fmt == 'I') {
                    ++fmt;
                    if (*fmt == '6') {
                        ++fmt;
                        if (*fmt == '4') {
                            ++fmt;
                            is64 = true;
                        }
                    }
                }

                switch (*fmt) {
                case '%':
                    *dst++ = '%';
                    ++count;
                    --remain;
                    emit = false;
                    break;
                case 'd':
                case 'i':
                    if (!is64) {
                        int v = VA_ARG(ap, int);
                        if (zeroPad && rightJustify && width > 0 && v < 0 && remain != 0) {
                            *dst++ = '-';
                            v = -v;
                            ++count;
                            --width;
                            --remain;
                        }
                        rw::core::stdc::ConvertIToA(v, buf, 10);
                    } else {
                        __int64 v = VA_ARG(ap, __int64);
                        if (zeroPad && rightJustify && width > 0 && v < 0 && remain != 0) {
                            *dst++ = '-';
                            v = -v;
                            ++count;
                            --width;
                            --remain;
                        }
                        rw::core::stdc::ConvertI64ToA((uint32_t)v, (uint32_t)(v >> 32), buf, 10, 0);
                    }
                    numeric = zeroPad;
                    break;
                case 'u':
                    if (!is64) {
                        uint32_t v = VA_ARG(ap, uint32_t);
                        rw::core::stdc::ConvertI64ToA(v, 0, buf, 10, 0);
                    } else {
                        unsigned __int64 v = VA_ARG(ap, unsigned __int64);
                        U64ToDec(buf, v);
                    }
                    numeric = zeroPad;
                    break;
                case 'o': {
                    int v = VA_ARG(ap, int);
                    rw::core::stdc::ConvertIToA(v, buf, 8);
                    numeric = zeroPad;
                    break;
                }
                case 'x':
                case 'X':
                    if (!is64) {
                        uint32_t v = VA_ARG(ap, uint32_t);
                        ConvertUToHex(v, buf, *fmt == 'x');
                    } else {
                        unsigned __int64 v = VA_ARG(ap, unsigned __int64);
                        uint32_t lo = (uint32_t)v;
                        uint32_t hi = (uint32_t)(v >> 32);
                        if ((lo | hi) == 0) {
                            buf[0] = '0';
                            buf[1] = 0;
                        } else {
                            char* e = (*fmt == 'x') ? Hex64Lower(buf, lo, hi) : Hex64Upper(buf, lo, hi);
                            *e = 0;
                        }
                    }
                    numeric = zeroPad;
                    break;
                case 'f': {
                    double v = VA_ARG(ap, double);
                    rw::core::stdc::ConvertfToA(buf, v, precision);
                    break;
                }
                case 'e': {
                    double v = VA_ARG(ap, double);
                    FormatE(buf, v, precision);
                    break;
                }
                case 'E': {
                    double v = VA_ARG(ap, double);
                    FormatEUpper(buf, v, precision);
                    break;
                }
                case 'g':
                case 'G': {
                    double v = VA_ARG(ap, double);
                    FormatG(buf, v, *fmt == 'G', precision);
                    break;
                }
                case 'c':
                    buf[0] = (char)VA_ARG(ap, int);
                    buf[1] = 0;
                    break;
                case 's':
                    src = VA_ARG(ap, const char*);
                    numeric = zeroPad;
                    break;
                case 'S':
                    src = VA_ARG(ap, const char*);
                    wideStr = true;
                    numeric = zeroPad;
                    break;
                case 'p': {
                    uint32_t v = VA_ARG(ap, uint32_t);
                    ConvertUToHex(v, buf, 0);
                    int len = StrLen(buf);
                    if (len < 8) {
                        int shift = 8 - len;
                        if (len >= 0) {
                            for (int i = len; i >= 0; --i)
                                buf[shift + i] = buf[i];
                        }
                        if (shift > 0) {
                            // inline memset(buf, '0', shift): rep stosd / rep stosb
                            __stosd((unsigned long*)buf, 0x30303030, (unsigned)shift >> 2);
                            __stosb((unsigned char*)buf + ((unsigned)shift & ~3u), '0', (unsigned)shift & 3);
                        }
                    }
                    break;
                }
                case 'n':
                    *VA_ARG(ap, int*) = count;
                    emit = false;
                    break;
                default:
                    ap += 4;
                    emit = false;
                    break;
                }

                if (*fmt != 0)
                    ++fmt;
                if (emit) {
                    if (width == 0)
                        dst = EmitPlain(dst, wideStr, src, &count, &remain);
                    else if (rightJustify)
                        dst = EmitRight(dst, &count, wideStr, numeric, width, src, &remain);
                    else
                        dst = EmitLeft(dst, width, wideStr, src, &count, &remain);
                    if ((int)size < count) {
                        count = -1;
                        break;
                    }
                }
                c = *fmt;
                if (c == 0) break;
            }
        }
    }
    *dst = 0;
    if (*fmt != 0 && remain == 0)
        count = -1;
    return count;
}
