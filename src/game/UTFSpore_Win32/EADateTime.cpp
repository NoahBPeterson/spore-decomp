// src/game/UTFSpore_Win32/EADateTime.cpp -- migrated from slice(s) s0092e3d0, s0092d3e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EADateTime.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/DateTime/DateTime.h"
#include "EA/Allocator/ICoreAllocator.h"
#include <time.h>
#include <string.h>
#include <new>
#include <windows.h>

// unnamed retail callees and globals (address in the comment)
extern "C" int64_t  __stdcall _alldiv(int, int, int, int);          // lib_crt::alldiv
extern "C" int64_t  __stdcall _allrem(int, int, int, int);          // lib_crt::allrem
extern "C" int64_t  __stdcall _allmul(int, int, int, int);          // lib_crt::allmul

// ---- items of slice s0092d3e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int64_t  __stdcall _alldiv(int, int, int, int);          // lib_crt::alldiv
extern "C" int64_t  __stdcall _allrem(int, int, int, int);          // lib_crt::allrem
extern "C" int64_t  __stdcall _allmul(int, int, int, int);          // lib_crt::allmul
static const int* const kMonthDays     = (const int*)0x0143E49C;   // [2][13]
static const int* const kCumMonthDays  = (const int*)0x0143E494;   // [2][13]
class DateTime {
public:
    int64_t mnSeconds;   // +0x00

    __declspec(noinline) int GetParameter(int which);                 // 0x92df80
    void SetDate(unsigned int year, unsigned int month, int day, int hour,
                 int minute, unsigned int second);                    // 0x92e200
};
static inline int Hi(int64_t v) { return *((const int*)&v + 1); }
int __cdecl FUN_0092df40(unsigned int year);  // 0x0092df40 (defined below; used by a stub's inline body)
static inline int Lo(int64_t v);  // 0x0092df80 (defined below; used by a stub's inline body)
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
// ---- items of slice s0092d3e0 end

// ---- items of slice s0092e3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DateTime_s0092_e3d0 {
    int64_t mnSeconds;
    int  GetParameter(int which);   // 0x0092df80
    void SetDate(int year, int month, int day, int hour, int minute, int second);   // 0x0092e200
    void Set(int utc);  // 0x0092e3d0 (DateTime::Set)
    void Add(int unit, int amount);
};
// ---- items of slice s0092e3d0 end

// @ 0x0092df40
int __cdecl FUN_0092df40(unsigned int year)
{
    if ((((year & 3) != 0) || (year % 100) == 0) && (year % 400) != 0)
        return 0;
    return 1;
}

// @ 0x0092df80
static inline int Lo(int64_t v)
{ return *(const int*)&v; }

// @ 0x0092e200
void DateTime::SetDate(unsigned int year, unsigned int month, int day, int hour, int minute, unsigned int second)
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

// @ 0x0092e3d0
void DateTime_s0092_e3d0::Set(int utc)
{
    time_t t = _time64(0);
    tm* p;
    if (utc == 1)
        p = _gmtime64(&t);
    else
        p = _localtime64(&t);
    if (p)
        SetDate(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}
