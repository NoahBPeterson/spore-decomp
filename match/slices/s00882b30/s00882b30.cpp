// Slice s00882b30 - EA::Locale::SetLocale (0x882b30, 3072 bytes).
//
// Selects a locale: resolves "system" through the OS LCID, maps the locale to language and
// country keys in the locale-data maps, publishes the language/country/locale strings and the
// per-locale format fields into the EA::Locale globals, and optionally switches the CRT locale.
// Falls back to the CRT alias table (recursing with the alias' canonical name).
//
// Flags: /O2 /MD /GS- /GR- /TP /Iscratch_s00880170_inc (vendored EAWebKit EASTL headers, the same
// set that reproduces the neighbouring map<fixed_string,fixed_string>::operator[] byte-exact).
// No /EHsc: the many fixed_string temporaries are destroyed without an EH frame.

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
#include <EASTL/map.h>

typedef eastl::fixed_string<wchar_t, 16, 1>  LocString;   // 0x34 bytes
typedef eastl::fixed_string<wchar_t, 512, 1> LocData;     // 0x414 bytes
typedef eastl::map<LocString, LocData, eastl::less<LocString>, eastl::allocator> LocMap;

namespace EA {
namespace Locale {

struct LocInfo { uint32_t lcid; uint16_t base; uint16_t script; };

// ---- callees (out of slice; relocations are masked) -----------------------
bool           GetSystemLocaleName(LocInfo* out, const LocString& name);             // 0x87da90
bool           FindByLcid(const LocInfo* info, LocString* out);                      // 0x87e130
LocString      GetLanguageFromLocale(const LocString& locale);                       // 0x87ed70
LocString      GetCountryFromLocale(const LocString& locale);                        // 0x87edd0
const wchar_t* CRTFindAliasDataByLocaleId(const LocString& locale);                  // 0x87f700
int            GetDataField(int index, const wchar_t* src, wchar_t* dst, int cap, wchar_t sep); // 0x87d620
int            GetDataFieldInt(int index, const wchar_t* src, wchar_t sep);          // 0x87d690
bool           SplitFieldInto(int index, const wchar_t* src, LocString* out, wchar_t sep); // 0x87de40
LocString      CRTGetLocale();                                                       // 0x8825f0
bool           CRTSetLocale(const LocString& locale);                                // 0x87f900

// ---- globals ---------------------------------------------------------------
extern const LocString kSystemLocale;     // 0x15490e4
extern LocMap    gLanguageMap;            // 0x1549180
extern LocMap    gCountryMap;             // 0x154919c

extern LocString gLanguage;               // 0x16503a0
extern LocString gCountry;                // 0x16503d4
extern LocString gLocale;                 // 0x1650408
extern LocString gField165043c, gField1650470, gField16504a4, gField16504d8, gField165050c,
                 gField1650540, gField1650574, gField16505a8, gField16505dc, gField1650610,
                 gField1650644, gField1650678, gField16506ac, gField16506e0, gField1650714,
                 gField1650748, gField165077c, gField16507b0, gField16507e4, gField1650818;
extern int       gMeasure165084c;         // 0x165084c
extern int       gMeasure1650850;         // 0x1650850
extern int       gInt1650854;             // 0x1650854
extern int       gFlag1650858;            // 0x1650858
extern LocString gDataLocale;             // 0x165085c
extern LocData   gLanguageData;           // 0x1650890
extern LocData   gCountryData;            // 0x1650ca4
extern LocData   gAliasData;              // 0x16510b8

// @ 0x00882b30
bool SetLocale(const LocString& locale, bool bSetCRTLocale, bool bForce)
{
    LocString name(locale);

    if (locale == kSystemLocale) {
        LocInfo info;
        if (GetSystemLocaleName(&info, kSystemLocale) && FindByLcid(&info, &name))
            return SetLocale(name, bSetCRTLocale, bForce);
        return false;
    }

    if (name == kSystemLocale)
        return true;

    LocString language = GetLanguageFromLocale(name);
    LocString country  = GetCountryFromLocale(name);

    if (gLanguageMap.find(name) != gLanguageMap.end())
        language = name;
    else if (gLanguageMap.find(language) == gLanguageMap.end()) {
        // No exact language entry: take the first one whose two-letter prefix matches.
        LocMap::iterator it = gLanguageMap.begin();
        LocString key;
        for (; it != gLanguageMap.end(); ++it) {
            key = it->first;
            if (key[0] == language[0] && key[1] == language[1])
                break;
        }
        if (it != gLanguageMap.end())
            language = key;
    }

    if (gLanguageMap.find(language) == gLanguageMap.end() ||
        gCountryMap.find(country) == gCountryMap.end())
    {
        const wchar_t* alias = CRTFindAliasDataByLocaleId(locale);
        if (alias) {
            wchar_t crtName[64];
            GetDataField(0, alias, crtName, sizeof(crtName), L'^');
            if (gLanguageMap.find(GetLanguageFromLocale(LocString(crtName))) != gLanguageMap.end() &&
                gCountryMap.find(GetCountryFromLocale(LocString(crtName))) != gCountryMap.end())
            {
                LocString canonical(crtName);
                return SetLocale(canonical, bSetCRTLocale, bForce);
            }
        }
        return false;
    }

    wchar_t languageData[512];
    wchar_t countryData[512];

    wcscpy(languageData, gLanguageMap[language].c_str());
    wcscpy(countryData, gCountryMap[country].c_str());

    gLanguage = language;
    gCountry  = country;
    gLocale   = name;

    const wchar_t* alias = CRTFindAliasDataByLocaleId(locale);
    if (!alias)
        return false;

    if (bSetCRTLocale) {
        wchar_t crtName[64];
        GetDataField(0, alias, crtName, sizeof(crtName), L'^');
        name = crtName;
        LocString current = CRTGetLocale();
        if (current == name && gLocale == name)
            return true;
        if (!CRTSetLocale(name) && !bForce)
            return false;
    }

    SplitFieldInto(3,    languageData, &gField16505dc, L'^');
    SplitFieldInto(4,    languageData, &gField1650610, L'^');
    SplitFieldInto(5,    languageData, &gField1650644, L'^');
    SplitFieldInto(6,    languageData, &gField1650678, L'^');
    SplitFieldInto(2,    languageData, &gField16506ac, L'^');
    SplitFieldInto(1,    languageData, &gField1650714, L'^');
    SplitFieldInto(6,    countryData,  &gField165043c, L'^');
    SplitFieldInto(8,    languageData, &gField16505a8, L'^');
    SplitFieldInto(0x10, countryData,  &gField1650540, L'^');
    SplitFieldInto(0x11, countryData,  &gField1650574, L'^');
    SplitFieldInto(7,    countryData,  &gField1650470, L'^');
    SplitFieldInto(8,    countryData,  &gField16504a4, L'^');
    SplitFieldInto(0xc,  countryData,  &gField16504d8, L'^');
    SplitFieldInto(0xd,  countryData,  &gField165050c, L'^');
    SplitFieldInto(2,    countryData,  &gField16506e0, L'^');
    SplitFieldInto(1,    countryData,  &gField1650748, L'^');
    SplitFieldInto(9,    countryData,  &gField165077c, L'^');
    SplitFieldInto(10,   countryData,  &gField16507b0, L'^');
    SplitFieldInto(0xb,  countryData,  &gField16507e4, L'^');
    SplitFieldInto(5,    countryData,  &gField1650818, L'^');

    LocString field;
    int v = 2;
    if (SplitFieldInto(3, countryData, &field, L'^') && field.begin() != field.end() &&
        towupper(field[0]) == L'L')
        v = 1;
    switch (v) {
        case 1:  gMeasure165084c = 1; break;
        default: gMeasure165084c = 2; break;
    }

    int v2 = 2;
    if (SplitFieldInto(4, countryData, &field, L'^') && field.begin() != field.end() &&
        towupper(field[0]) == L'E')
        v2 = 1;
    switch (v2) {
        case 1:  gMeasure1650850 = 1; break;
        default: gMeasure1650850 = 2; break;
    }

    gInt1650854 = GetDataFieldInt(4, alias, L'^');

    if (SplitFieldInto(9, languageData, &field, L'^') && field.begin() != field.end() &&
        field[0] == L'I')
        gFlag1650858 = 1;
    else
        gFlag1650858 = 0;

    const bool bSystemCountry = (GetCountryFromLocale(locale) == kSystemLocale);
    gDataLocale = bSystemCountry ? gLocale : locale;

    gLanguageData = languageData;
    gCountryData  = countryData;
    gAliasData    = alias;
    return true;
}

} // namespace Locale
} // namespace EA
