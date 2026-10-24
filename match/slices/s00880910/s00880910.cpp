// Slice s00880910 - EA::Locale::GetLocaleInfoString (0x880910, 2308 bytes).
//
// Returns one piece of locale information (language / country / locale names, date and time
// field lists, currency, measurement system ...) as a wide string, selected by `type`.
// For the "system"/current locale the answers come straight from the EA::Locale globals;
// for any other locale they are looked up in the language / country data maps through
// GetLanguageDataString / GetCountryDataString, with a built-in English table as the last fallback.
//
// Flags: /O2 /MD /GS- /GR- /TP /Iscratch_s00880170_inc (vendored EAWebKit EASTL headers, the same
// set the neighbouring EA::Locale slices use). No /EHsc: the fixed_string temporaries are destroyed
// without an EH frame.

#include "types.h"

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#include <wchar.h>
#include <EASTL/fixed_string.h>

typedef eastl::fixed_string<wchar_t, 16, 1> LocString;   // 0x34 bytes
typedef eastl::fixed_string<wchar_t, 512, 1> LocString512;  // map value string

namespace EA {
namespace Locale {

// ---- callees (out of slice; relocations are masked) -----------------------
bool      MakeLocaleAvailable(const LocString& a, const LocString& b);                       // 0x87d9a0
LocString GetLanguageFromLocale(const LocString& locale);                                    // 0x87ed70
LocString GetCountryFromLocale(const LocString& locale);                                     // 0x87edd0
LocString CanonicalLocale(const LocString& locale);                                          // 0x87f350
int       GetDataField(int index, const wchar_t* src, wchar_t* dst, int cap, wchar_t sep);   // 0x87d620
int       GetCountryDataString(const LocString& field, int index, bool direct, const LocString& locale,
                               wchar_t* out, size_t cap);                                    // 0x880750
int       GetLanguageDataString(const LocString& field, int index, bool direct, const LocString& locale,
                                wchar_t* out, size_t cap);                                   // 0x880830

// ---- date/time format support ---------------------------------------------
struct FmtElem {                 // 0x4c bytes, one parsed format directive
    LocString      s;            // +0x00 formatted text
    int            flags;        // +0x34
    int            type;         // +0x38
    unsigned       width;        // +0x3c
    unsigned       prec;         // +0x40
    const wchar_t* begin;        // +0x44
    const wchar_t* end;          // +0x48
};
struct LocScan { const wchar_t* cur; unsigned len; };

char          FUN_0087d6d0(wchar_t* s, FmtElem* fields, int* pCount, wchar_t** pOut);  // 0x87d6d0
char          FUN_0087f370(FmtElem* dst, int count, const wchar_t* str);               // 0x87f370
int           FUN_008804d0(wchar_t* out, int cap, LocScan* v, FmtElem* first, int count); // 0x8804d0
LocString     FUN_0087f210(const wchar_t* s);                                          // 0x87f210
LocString*    __fastcall FUN_0087e080(LocString* self, void*, const wchar_t* s);       // 0x87e080
struct LocaleMap {
    LocString512* Find(const LocString* key);                                          // 0x880610 (map::operator[])
};
void          FUN_0092d060(int lo, int hi, wchar_t* out);                              // 0x92d060
extern "C" __declspec(dllimport) wchar_t* __cdecl _ltow(long, wchar_t*, int);
extern const wchar_t DAT_014278e4[];      // default English fallback string

static inline unsigned WcsLen(const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e) ++e;
    return (unsigned)(e - s);
}

// ---- globals ---------------------------------------------------------------
extern const LocString kSystemLocale;     // 0x15490e4
extern LocString gLanguage;               // 0x16503a0
extern LocString gCountry;                // 0x16503d4
extern LocString gLocale;                 // 0x1650408
extern LocString gField165043c, gField1650470, gField16504a4, gField16504d8, gField165050c,
                 gField1650540, gField1650574, gField16505a8, gField16505dc, gField1650610,
                 gField1650644, gField1650678, gField16506ac, gField16506e0, gField1650714,
                 gField1650748, gField165077c, gField16507b0, gField16507e4, gField1650818;
extern LocString gDataLocale;             // 0x165085c

// Built-in English locale record (the fallback for date/time field lists).
static const wchar_t kDefaultLocaleData[] =
    L"en^English^English^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^"
    L"Mon.,Tue.,Wed.,Thur.,Fri.,Sat.,Sun.^"
    L"January,February,March,April,May,June,July,August,September,October,November,December^"
    L"Jan.,Feb.,Mar.,Apr.,May,June,July,Aug.,Sept.,Oct.,Nov.,Dec.^0^%f %l^";

// @ 0x00880910
int GetLocaleInfoString(int type, int index, wchar_t* pResult, size_t resultCapacity,
                        const LocString& locale)
{
    if (MakeLocaleAvailable(locale, kSystemLocale) && MakeLocaleAvailable(gLocale, kSystemLocale))
        return -1;

    wchar_t buf[128] = { 0 };
    bool direct = MakeLocaleAvailable(locale, gLocale) || MakeLocaleAvailable(locale, kSystemLocale);

    switch (type) {
    case 0: {
        LocString s(direct ? gLanguage : GetLanguageFromLocale(locale));
        wcsncpy(pResult, s.c_str(), resultCapacity);
        pResult[resultCapacity - 1] = 0;
        return (int)s.size();
    }
    case 1: {
        LocString s(direct ? gCountry : GetCountryFromLocale(locale));
        wcsncpy(pResult, s.c_str(), resultCapacity);
        pResult[resultCapacity - 1] = 0;
        return (int)s.size();
    }
    case 2: {
        LocString s(direct ? gLocale : CanonicalLocale(locale));
        wcsncpy(pResult, s.c_str(), resultCapacity);
        pResult[resultCapacity - 1] = 0;
        return (int)s.size();
    }
    case 3:
        return GetCountryDataString(gField165043c, 6, direct, locale, pResult, resultCapacity);
    case 28:
        if (GetCountryDataString(gField1650818, 5, direct, locale, buf, 128) > 0)
            return GetDataField(0, buf, pResult, resultCapacity, L',');
        break;
    case 29:
        if (GetCountryDataString(gField1650818, 5, direct, locale, buf, 128) > 0)
            return GetDataField(1, buf, pResult, resultCapacity, L',');
        break;
    case 4:
        return GetCountryDataString(gField1650470, 7, direct, locale, pResult, resultCapacity);
    case 5:
        return GetCountryDataString(gField16504a4, 8, direct, locale, pResult, resultCapacity);
    case 6:
        return GetCountryDataString(gField16504d8, 12, direct, locale, pResult, resultCapacity);
    case 7:
        return GetCountryDataString(gField165050c, 13, direct, locale, pResult, resultCapacity);
    case 10:
        return GetLanguageDataString(gField16505a8, 8, direct, locale, pResult, resultCapacity);
    case 8:
        return GetCountryDataString(gField1650540, 16, direct, locale, pResult, resultCapacity);
    case 9:
        return GetCountryDataString(gField1650574, 17, direct, locale, pResult, resultCapacity);
    case 11:
        if (GetCountryDataString(gField16505dc, 3, direct, locale, buf, 128) > 0)
            return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
        // fall through
    case 12:
        if (GetCountryDataString(gField1650610, 3, direct, locale, buf, 128) > 0)
            return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
        // fall through
    case 14:
        if (GetCountryDataString(gField1650678, 3, direct, locale, buf, 128) > 0)
            return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
        // fall through
    case 13:
        if (GetCountryDataString(gField1650644, 3, direct, locale, buf, 128) > 0)
            return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
        // fall through
    case 15:
        GetDataField(3, kDefaultLocaleData, buf, 128, L'^');
        return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
    case 16:
        GetDataField(4, kDefaultLocaleData, buf, 128, L'^');
        return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
    case 17:
        GetDataField(5, kDefaultLocaleData, buf, 128, L'^');
        return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
    case 18:
        GetDataField(6, kDefaultLocaleData, buf, 128, L'^');
        return GetDataField(index - 1, buf, pResult, resultCapacity, L',');
    case 19:
        return GetLanguageDataString(gField16506ac, 2, direct, locale, pResult, resultCapacity);
    case 20:
        return GetCountryDataString(gField16506e0, 2, direct, locale, pResult, resultCapacity);
    case 21:
        return GetLanguageDataString(gField1650714, 1, direct, locale, pResult, resultCapacity);
    case 22:
        return GetCountryDataString(gField1650748, 1, direct, locale, pResult, resultCapacity);
    case 23:
        return GetCountryDataString(gField165077c, 9, direct, locale, pResult, resultCapacity);
    case 24:
        return GetCountryDataString(gField16507b0, 10, direct, locale, pResult, resultCapacity);
    case 25:
        return GetCountryDataString(gField16507e4, 11, direct, locale, pResult, resultCapacity);
    case 26: {
        LocString s(direct ? GetLanguageFromLocale(gDataLocale)
                           : GetLanguageFromLocale(CanonicalLocale(locale)));
        const wchar_t* src = s.c_str();
        wchar_t* dst = pResult;
        while ((*dst++ = *src++) != 0) {}
        return (int)s.size();
    }
    case 27: {
        LocString s(direct ? GetCountryFromLocale(gDataLocale)
                           : GetCountryFromLocale(CanonicalLocale(locale)));
        const wchar_t* src = s.c_str();
        wchar_t* dst = pResult;
        while ((*dst++ = *src++) != 0) {}
        return (int)s.size();
    }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// @ 0x00881220  EA::Locale::GetLocaleInfoInt
//   Insert "canonical locale key -> raw name" pairs into the two global maps.
// ---------------------------------------------------------------------------
void GetLocaleInfoInt(const wchar_t* a, const wchar_t* b)
{
    LocString key;

    key = FUN_0087f210(a);

    LocString512* v = ((LocaleMap*)0x1549180)->Find(&key);
    if (v->c_str() != a) {
        v->clear();
        v->assign(a, a + WcsLen(a));
    }

    key = FUN_0087f210(b);

    LocString512* v2 = ((LocaleMap*)0x154919c)->Find(&key);
    if (v2->c_str() != b) {
        v2->clear();
        v2->assign(b, b + WcsLen(b));
    }
}

// ---------------------------------------------------------------------------
// @ 0x008813e0  EA::Locale::SetDateString
//   Format day/month/year through the parsed date format elements.
// ---------------------------------------------------------------------------
int SetDateString(int day, int month, int year, wchar_t* out, int cap,
                  const wchar_t* str, const wchar_t* fmt)
{
    FmtElem  elems[16];
    int      count = 16;
    wchar_t* pOut = 0;
    int      ret = -1;

    if (fmt != 0) {
        if (FUN_0087d6d0((wchar_t*)fmt, elems, &count, &pOut) != 0) {
            if (pOut == 0) {
                FUN_0087f370(elems, 16, str);

                LocScan scan;
                scan.cur = fmt;
                scan.len = WcsLen(fmt);

                wchar_t buf[128];
                wchar_t num[128];
                for (int i = 0; i < count; ++i) {
                    FmtElem* el = &elems[i];
                    if ((el->flags & 0x20) != 0)
                        continue;

                    const wchar_t* src;
                    switch (el->type) {
                    case 9: {           // day of month
                        if ((el->flags & 0x40) != 0) {
                            _ltow(day, num, 10);
                            src = num;
                        } else {
                            int id = ((el->flags & 4) != 0) ? 11 : 12;
                            int n = GetLocaleInfoString(id, day, buf, 0x80, kSystemLocale);
                            if (n > 0x80 || n < 0) {
                                const short* d = (const short*)DAT_014278e4;
                                short* o = (short*)buf;
                                for (;;) {
                                    short c = *d++;
                                    *o++ = c;
                                    if (c == 0)
                                        break;
                                }
                            }
                            src = buf;
                        }
                        break;
                    }
                    case 10: {          // month
                        if ((el->flags & 0x40) != 0) {
                            _ltow(month, num, 10);
                            src = num;
                        } else {
                            int id = ((el->flags & 4) != 0) ? 13 : 14;
                            int n = GetLocaleInfoString(id, month, buf, 0x80, kSystemLocale);
                            if (n > 0x80 || n < 0) {
                                const short* d = (const short*)DAT_014278e4;
                                short* o = (short*)buf;
                                for (;;) {
                                    short c = *d++;
                                    *o++ = c;
                                    if (c == 0)
                                        break;
                                }
                            }
                            src = buf;
                        }
                        break;
                    }
                    case 11: {          // year
                        if ((int)el->width < 1) {
                            _ltow(year, num, 10);
                            src = num;
                        } else {
                            wchar_t ybuf[32];
                            FUN_0092d060(year, year >> 31, ybuf);
                            const wchar_t* e = ybuf;
                            while (*e) ++e;
                            unsigned len = (unsigned)(e - ybuf);
                            if (el->width < len)
                                src = ybuf + (len - el->width);
                            else
                                src = ybuf;
                        }
                        break;
                    }
                    default:
                        continue;
                    }
                    FUN_0087e080(&el->s, 0, src);
                }
                ret = FUN_008804d0(out, cap, &scan, elems, 16);
            }
        }
    }
    return ret;
}

// ---------------------------------------------------------------------------
// @ 0x00881720  date-string wrapper (supplies the global date format)
// ---------------------------------------------------------------------------
void FUN_00881720(int day, int month, int year, wchar_t* out, int cap,
                  const wchar_t* str)
{
    SetDateString(day, month, year, out, cap, str, gField1650470.c_str());
}

}  // namespace Locale
}  // namespace EA
