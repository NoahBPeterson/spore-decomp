// Slice s0092d3e0: EA::DateTime plus the CRT-style string <-> number helpers
// (wide strtoull, char/wchar float formatting, char/wchar strtod, leap-year).
// Reconstructed from the Spore disassembly.  Compiler: MSVC 2008 SP1 (/O2).
#include "types.h"

// ---------------------------------------------------------------------------
// CRT / helper imports used by this slice (declared with their real call forms;
// only the call relocation matters for matching).
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl iswctype(unsigned short c, int type);
extern "C" __declspec(dllimport) int __cdecl isspace(int c);
extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short c);
extern "C" int*     __cdecl _errno();                               // msvcr90!_errno
extern "C" int64_t  __stdcall _alldiv(int, int, int, int);          // lib_crt::alldiv
extern "C" int64_t  __stdcall _allrem(int, int, int, int);          // lib_crt::allrem
extern "C" int64_t  __stdcall _allmul(int, int, int, int);          // lib_crt::allmul
extern "C" __declspec(dllimport) char* __cdecl _fcvt(double value, int count, int* pDecpt, int* pSign);
extern "C" __declspec(dllimport) char* __cdecl _ltoa(long value, char* buffer, int radix);
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long value, wchar_t* buffer, int radix);
extern "C" double   __cdecl floor(double x);
extern "C" double   __cdecl fabs(double x);
extern "C" double   __cdecl log10(double x);
extern "C" double   __cdecl pow(double x, double y);

// EA::DateTime tables (month lengths and cumulative day-of-year, per leap/non-leap).
static const int* const kMonthDays     = (const int*)0x0143E49C;   // [2][13]
static const int* const kCumMonthDays  = (const int*)0x0143E494;   // [2][13]

// ---------------------------------------------------------------------------
// @ 0x0092df40 : is-leap-year (returns 1 for a leap year, else 0)
// ---------------------------------------------------------------------------
int __cdecl FUN_0092df40(unsigned int year)
{
    if ((((year & 3) != 0) || (year % 100) == 0) && (year % 400) != 0)
        return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x0092df80 : EA::DateTime::DateTime::GetParameter(which)
// ---------------------------------------------------------------------------
class DateTime {
public:
    int64_t mnSeconds;   // +0x00

    __declspec(noinline) int GetParameter(int which);                 // 0x92df80
    void SetDate(unsigned int year, unsigned int month, int day, int hour,
                 int minute, unsigned int second);                    // 0x92e200
};

static inline int Lo(int64_t v) { return *(const int*)&v; }
static inline int Hi(int64_t v) { return *((const int*)&v + 1); }

__declspec(noinline) int DateTime::GetParameter(int which)
{
    switch (which) {
    case 1: {
        int64_t days  = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0x15180, 0);
        int64_t years = _alldiv(Lo(days), Hi(days), 0x16d, 0);
        int64_t y0    = years - 1;
        int64_t q400  = _alldiv(Lo(y0), Hi(y0), 400, 0);
        int64_t q100  = _alldiv(Lo(y0), Hi(y0), 100, 0);
        int64_t q4    = _alldiv(Lo(y0), Hi(y0), 4, 0);
        days = days + ((q100 - q400) - q4);
        int64_t doy = _alldiv(Lo(days - 1), Hi(days - 1), 0x16d, 0);
        return (int)doy + 1;
    }
    case 2: {
        int year       = GetParameter(1);
        unsigned int dayOfYear = (unsigned int)GetParameter(5);
        unsigned int leap = (unsigned int)FUN_0092df40((unsigned int)year);
        const int* p = kMonthDays + (leap & 0xff) * 0xd;
        int i = 1;
        do {
            if (dayOfYear <= (unsigned int)*p)
                return i;
            ++i;
            ++p;
        } while (i < 0xd);
        /* falls through */
    }
    case 5: {
        int year = GetParameter(1);
        unsigned int y = (unsigned int)(year - 1);
        int64_t days = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0x15180, 0);
        return (((int)days - (int)(y / 400)) + (int)(y * -0x16d) - (int)(y >> 2))
               + (int)(y / 100);
    }
    case 3:
        return (GetParameter(5) - 1U) / 7 + 1;
    case 4:
        return (GetParameter(6) - 1U) / 7 + 1;
    case 6: {
        int year  = GetParameter(1);
        int month = GetParameter(2);
        int doy   = GetParameter(5);
        unsigned int leap = (unsigned int)FUN_0092df40((unsigned int)year);
        return doy - kCumMonthDays[(leap & 0xff) * 0xd + month];
    }
    case 7: {
        int64_t days = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0x15180, 0);
        return (int)_allrem(Lo(days), Hi(days), 7, 0) + 1;
    }
    case 8: {
        int64_t hours = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0xe10, 0);
        return (int)_allrem(Lo(hours), Hi(hours), 0x18, 0);
    }
    case 9: {
        int64_t mins = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0x3c, 0);
        return (int)_allrem(Lo(mins), Hi(mins), 0x3c, 0);
    }
    case 10:
        return (int)_allrem(Lo(mnSeconds), Hi(mnSeconds), 0x3c, 0);
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0092e200 : EA::DateTime::DateTime::SetDate(year, month, day, hour, minute, second)
// ---------------------------------------------------------------------------
void DateTime::SetDate(unsigned int year, unsigned int month, int day, int hour,
                      int minute, unsigned int second)
{
    if (year == 0xffffffff || year == 0)
        year = (unsigned int)GetParameter(1);
    if (month == 0xffffffff || month == 0)
        month = (unsigned int)GetParameter(2);
    if (day == -1 || day == 0) {
        int y = GetParameter(1);
        unsigned int leap = (unsigned int)FUN_0092df40((unsigned int)y);
        int m = GetParameter(2);
        int doy = GetParameter(5);
        day = doy - kCumMonthDays[(leap & 0xff) * 0xd + m];
    }
    if (hour == -1) {
        int64_t h = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0xe10, 0);
        hour = (int)_allrem(Lo(h), Hi(h), 0x18, 0);
    }
    if (minute == -1) {
        int64_t m = _alldiv(Lo(mnSeconds), Hi(mnSeconds), 0x3c, 0);
        minute = (int)_allrem(Lo(m), Hi(m), 0x3c, 0);
    }
    if (second == 0xffffffff)
        second = (unsigned int)_allrem(Lo(mnSeconds), Hi(mnSeconds), 0x3c, 0);

    if (0xc < month)
        year += (month - 1) / 0xc;

    unsigned int y = year - 1;
    unsigned int days = (y / 400 - y / 100) + y * 0x16d + (y >> 2);
    unsigned int leap = (unsigned int)FUN_0092df40(year);
    int md = kCumMonthDays[(int)(leap & 0xff) * 0xd + (month - 1) % 0xc + 1];

    uint32_t mdpls = (uint32_t)(md + day);
    uint32_t carry = (mdpls + days < mdpls) ? 1u : 0u;
    uint64_t secs = (uint64_t)_allmul((int)(mdpls + days), (int)carry, 0x15180, 0);
    uint64_t res = secs + (uint64_t)(uint32_t)(hour * 0xe10);
    res += (uint64_t)(uint32_t)(minute * 0x3c);
    res += (uint64_t)second;
    mnSeconds = (int64_t)res;
}

// ---------------------------------------------------------------------------
// @ 0x0092d3e0 : wide strtoull (base 2..36, optional grouping / sign handling)
// ---------------------------------------------------------------------------
uint64_t __cdecl StrtoU64Common16(const wchar_t* nptr, const wchar_t** endptr,
                                  unsigned int base, char group)
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

// ---------------------------------------------------------------------------
// @ 0x0092d730 : char-buffer float formatter (like _gcvt / _ecvt based)
//   FUN_0092d730(value, buffer, size, precision, useScientific)
// ---------------------------------------------------------------------------
__declspec(noinline)
char* __cdecl FUN_0092d730(double value, char* buffer, int size, int precision, char sci)
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

// ---------------------------------------------------------------------------
// @ 0x0092d9b0 : wide-buffer float formatter (wide counterpart of FUN_0092d730)
// ---------------------------------------------------------------------------
__declspec(noinline)
wchar_t* __cdecl FtoaEnglish16(double value, wchar_t* buffer, int size,
                               int precision, char sci)
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

// ---------------------------------------------------------------------------
// @ 0x0092dc50 : char strtod (returns extended precision)
// ---------------------------------------------------------------------------
long double __cdecl FUN_0092dc50(const char* nptr, const char** endptr)
{
    const char* s = nptr;
    char sign = '+';
    int c = isspace((int)(unsigned char)*s);
    while (c != 0) {
        ++s;
        c = isspace((int)(unsigned char)*s);
    }
    int d = (int)(signed char)*s;
    ++s;
    if (d == '-' || d == '+') {
        sign = (char)d;
        d = (int)(signed char)*s;
        ++s;
    }
    long double value = 0.0;
    while ((unsigned int)(d - 0x30) < 10) {
        value = value * 10.0 + (long double)(d - 0x30);
        d = (int)(signed char)*s;
        ++s;
    }
    long double scale = 1.0;
    if (d == '.') {
        d = (int)(signed char)*s;
        ++s;
        if ((unsigned int)(d - 0x30) < 10) {
            long double frac = scale;
            do {
                frac = frac * 0.1;
                d = (int)(signed char)*s;
                ++s;
                value = (long double)(d - 0x30) * frac + value;
                d = (int)(signed char)*s;
            } while ((unsigned int)(d - 0x30) < 10);
        }
    }
    if (d == 'e' || d == 'E') {
        int ec = (int)(signed char)*s;
        unsigned int exp = 0;
        int esign = '+';
        ++s;
        if (ec == '-' || ec == '+') {
            esign = (char)ec;
            ec = (int)(signed char)*s;
            ++s;
        }
        while ((unsigned int)(ec - 0x30) < 10) {
            exp = (unsigned int)(ec - 0x30) + exp * 10;
            ec = (int)(signed char)*s;
            ++s;
        }
        unsigned int e = exp;
        long double factor = 1.0;
        long double base = 10.0;
        if ((int)exp < 0)
            e = (unsigned int)-(int)exp;
        for (;;) {
            if ((e & 1) != 0)
                factor = factor * base;
            if ((e >> 1) == 0)
                break;
            base = base * base;
            e = e >> 1;
        }
        if ((int)exp < 0)
            factor = 1.0 / factor;
        if (esign == '-')
            value = value * (1.0 / factor);
        else
            value = value * factor;
    }
    if (endptr)
        *endptr = s - 1;
    if (sign == '-')
        value = -value;
    return value;
}

// ---------------------------------------------------------------------------
// @ 0x0092ddc0 : wide strtod (returns extended precision)
// ---------------------------------------------------------------------------
long double __cdecl FUN_0092ddc0(const wchar_t* nptr, const wchar_t** endptr)
{
    const wchar_t* s = nptr;
    unsigned short sign = L'+';
    int c = iswctype(*s, 8);
    while (c != 0) {
        ++s;
        c = iswctype(*s, 8);
    }
    unsigned int d = (unsigned int)*s;
    ++s;
    if (d == L'-' || d == L'+') {
        sign = (unsigned short)d;
        d = (unsigned int)*s;
        ++s;
    }
    long double value = 0.0;
    while (d - 0x30 < 10) {
        value = value * 10.0 + (long double)(int)(d - 0x30);
        d = (unsigned int)*s;
        ++s;
    }
    long double scale = 1.0;
    if (d == L'.') {
        d = (unsigned int)*s;
        ++s;
        if (d - 0x30 < 10) {
            long double frac = scale;
            do {
                frac = frac * 0.1;
                d = (unsigned int)*s;
                ++s;
                value = (long double)(int)(d - 0x30) * frac + value;
                d = (unsigned int)*s;
            } while (d - 0x30 < 10);
        }
    }
    if (d == L'e' || d == L'E') {
        unsigned int ec = (unsigned int)*s;
        unsigned int exp = 0;
        unsigned short esign = L'+';
        ++s;
        if (ec == L'-' || ec == L'+') {
            esign = (unsigned short)ec;
            ec = (unsigned int)*s;
            ++s;
        }
        while (ec - 0x30 < 10) {
            exp = (ec - 0x30) + exp * 10;
            ec = (unsigned int)*s;
            ++s;
        }
        unsigned int e = exp;
        long double factor = 1.0;
        long double base = 10.0;
        if ((int)exp < 0)
            e = (unsigned int)-(int)exp;
        for (;;) {
            if ((e & 1) != 0)
                factor = factor * base;
            if ((e >> 1) == 0)
                break;
            base = base * base;
            e = e >> 1;
        }
        if ((int)exp < 0)
            factor = 1.0 / factor;
        if (esign == L'-')
            value = value * (1.0 / factor);
        else
            value = value * factor;
    }
    if (endptr)
        *endptr = s - 1;
    if (sign == L'-')
        value = -value;
    return value;
}
