// src/game/UTFSpore_Win32/INetDateTime.cpp -- migrated from slice(s) s00946dc0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/INetDateTime.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPMultipartFormDataPostBodyStream.h"
#include "tm.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#ifndef S00946DC0_H
#endif
#include <intrin.h>

// ---- items of slice s00946dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl sscanf(const char*, const char*, ...);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
namespace eastl {
extern const char kEastlPathAddr[];              // 0x013ebb38
}
namespace eastl {
struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;

    StrStub() {}
    StrStub(const StrStub& other);               // 0x0057cb10
    StrStub(const char* first, const char* last) {
        unsigned n = (unsigned)(last - first);
        char* p;
        if (n + 1 < 2) {
            p = (char*)0x1667bac;
            mpCapacity = p + 1;
        } else {
            p = (char*)operator new(n + 1, "EASTL", 0, 0, (int)kEastlPathAddr, 0xd1);
            mpCapacity = p + n + 1;
        }
        memcpy(p, first, n);
        mpBegin = p;
        mpEnd = p + n;
        *mpEnd = 0;
    }

    void assign(const char* first, const char* last);     // 0x00454cb0
    void append(const char* first, const char* last);     // 0x00455d60
    void RangeInitialize(unsigned n);                      // 0x00475ab0
    unsigned find(char c, unsigned pos) const;             // 0x00607580
};
}
namespace eastl {
struct StrDtor {
    void Destroy();                              // 0x00530670
};
}
int  GetDateTypeFromString(const eastl::StrStub* s);            // 0x00947540
int  MonthStringToInteger(const char* str);                     // 0x00947500
#define S_(a) ((const char*)(a))
static const char* const kLongWeekdays = S_(0x143f4e8);   // "Monday"...
static const char* const kShortWeekdays = S_(0x143f530);  // "Mon"...
static const char* const kShortMonths = S_(0x143f54c);    // "Jan"...
// ---- items of slice s00946dc0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) __int64 __cdecl _mktime64(struct tm*);

// @ 0x00947410
namespace EA {
namespace Internet {
unsigned int TimeToSeconds(unsigned int weekday, unsigned int day, unsigned int month, unsigned int year, unsigned int yday, unsigned int hour, unsigned int minute, unsigned int second)
{
    struct tm t = { second, minute, hour, day, month - 1, year - 1900,
                    weekday - 1, yday - 1, 1 };
    return _mktime64(&t);
}
}
}  // namespace EA::Internet

// @ 0x00947480
namespace EA {
namespace Internet {
unsigned int WeekdayStringToInteger(char const * str, bool longNames)
{
    if (longNames) {
        unsigned off = 0;
        const char* p = kLongWeekdays;
        int n = 0;
        do {
            if (_stricmp(str, p) == 0)
                return n + 1;
            off += 10;
            n++;
            p += 10;
        } while (off < 0x46);
        return 0;
    } else {
        unsigned off = 0;
        const char* p = kShortWeekdays;
        int n = 0;
        do {
            if (_stricmp(str, p) == 0)
                return n + 1;
            off += 4;
            n++;
            p += 4;
        } while (off < 0x1c);
    }
    return 0;
}
}
}  // namespace EA::Internet

// @ 0x00947500
int MonthStringToInteger(const char* str)
{
    unsigned i = 0;
    const char* p = kShortMonths;
    do {
        if (_stricmp(str, p) == 0)
            return i + 1;
        i++;
        p += 4;
    } while (i < 12);
    return 0;
}

// @ 0x00947540
int GetDateTypeFromString(const eastl::StrStub* s)
{
    char b[8][44];
    const char* src = s->mpBegin;
    unsigned len = (unsigned)(s->mpEnd - s->mpBegin);
    int comma = -1;
    if (len != 0) {
        const char* p = src;
        while (p != s->mpEnd) {
            if (*p == ',')
                break;
            p++;
        }
        if (p != s->mpEnd)
            comma = (int)(p - src);
    }
    if (len < 0x30) {
        if ((unsigned)comma < len) {
            if (comma == 3) {
                if (len != 0x1d)
                    return 0;
                if (sscanf(src, S_(0x143f5b8), b[0], b[1], b[2], b[3], b[4], b[5]) != 6) {
                    eastl::StrStub tmp(*s);
                    tmp.mpBegin[0xb] = ' ';
                    tmp.mpBegin[7] = ' ';
                    if (sscanf(tmp.mpBegin, S_(0x143f5b8), b[0], b[1], b[2], b[3], b[4], b[5]) != 6) {
                        ((eastl::StrDtor*)&tmp)->Destroy();
                        return 0;
                    }
                    ((eastl::StrDtor*)&tmp)->Destroy();
                }
                return 1;
            }
            if (len - 0x1e <= 5) {
                if (sscanf(src, S_(0x143f5ac), b[0], b[1], b[2], b[3]) == 4) {
                    if (b[1][1] == 0)
                        return 2;
                    if (b[1][3] == 0)
                        return 3;
                }
            }
            return 0;
        }
        if (len == 0x18) {
            if (sscanf(src, S_(0x143f5c8), b[0], b[1], b[2], b[3], b[4]) == 5)
                return 4;
        }
    }
    return 0;
}
