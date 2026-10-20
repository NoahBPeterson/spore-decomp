// Slice s008825f0 (0x8825f0..0x882b22) - EA::Locale::CRTGetLocale.
//
// Reads the current CRT locale (setlocale(LC_ALL,0)) and converts the narrow
// "lang_country.code" ANSI name into the internal 16-wchar LocT buffer used by the
// locale tables. When that lookup succeeds it returns the locale's own name; on any
// miss it falls back to the default locale string (0x15490e4).
//
// LocT<16> is eastl::fixed_string<wchar_t,16,1>: the 0x14-byte basic_string base
// (begin/end/capacity/allocator) then the fixed_allocator pool begin/end and the
// 16-wchar inline buffer at +0x18. Only the default ctor, clear() and the heap
// release are inlined; append/assign/copy-ctor are out-of-line (relocations are
// masked by the verifier).
//
// Flags: /O2 /MD /GS- /GR- /TP /Iwork/match/scratch_s008825f0_inc

#include "types.h"

extern "C" __declspec(dllimport) char* __cdecl setlocale(int category, const char* locale);

// ---------------------------------------------------------------------------
// LocT<16> - eastl::fixed_string<wchar_t,16,1> layout only
// ---------------------------------------------------------------------------
typedef unsigned short wchar16_t;

struct LocT16
{
    wchar16_t* mpBegin;      // +0x00
    wchar16_t* mpEnd;        // +0x04
    wchar16_t* mpCapacity;   // +0x08
    void*      mAlloc;       // +0x0c
    wchar16_t* mpPoolBegin;  // +0x10
    wchar16_t  mBuf[16];     // +0x18

    LocT16()
    {
        mpPoolBegin = mBuf;
        mpEnd       = mBuf;
        mpBegin     = mBuf;
        mpCapacity  = mBuf + 16;
        mBuf[0]     = 0;
    }

    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }

    // inlined fixed_string heap release
    void ReleaseHeap()
    {
        wchar16_t* p = mpBegin;
        if ((((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpPoolBegin)
            Free(p);
    }

    void __thiscall AppendElement(const wchar16_t* first, const wchar16_t* last);  // 0x68cc10
    LocT16& __thiscall operator=(const LocT16& other);                            // 0x696320
    LocT16(const LocT16& other);                                                  // 0x696230
    LocT16(const wchar16_t* s);                                                   // 0x6962a0

private:
    static void __cdecl Free(void* p);   // 0xf47380  operator delete
};

// ---------------------------------------------------------------------------
// other fixed_string instantiations used through out-of-line calls only
// ---------------------------------------------------------------------------
struct LocT128 { char raw[0x104]; };   // fixed_string<wchar_t,128,1>: 0x14 + 0x100 buffer
struct LocT512 { char raw[0x404]; };   // fixed_string<wchar_t,512,1>

// ---------------------------------------------------------------------------
// external callees (out of slice; relocations masked by the verifier)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl ConvertName(LocT16* out, const wchar16_t* name);            // 0x87f210
extern "C" void* __fastcall TraitsInit(void* self);                                  // 0x87f100
extern "C" void  __cdecl GetLocaleTraits(void* out, const void* deflt);              // 0x882380
extern "C" void* __cdecl ConcatNames(LocT16* out, const void* a, const void* b);     // 0x87fe90
extern "C" void  __fastcall TraitsFree(void* self, void*);                           // 0x87dd10 (ecx=self)
extern "C" int   __cdecl SplitField(int idx, const wchar16_t* src, wchar16_t* dst, int cap, wchar16_t sep); // 0x87d620
extern "C" unsigned int __cdecl FindLower(const wchar16_t* src, wchar16_t* dst, int cap); // 0x87e230
extern "C" int   __cdecl FindInCht(const wchar16_t* src, wchar16_t* dst, int cap);   // 0x87db80
extern "C" int   __cdecl StrCmp(const char* a, const char* b);                       // inlined strcmp

// The original inlines the wide-string compare (two wchar per iteration).
static inline int CompareW(const wchar16_t* a, const wchar16_t* b)
{
    while (*a == *b) {
        if (*a == 0)
            return 0;
        ++a;
        ++b;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern wchar16_t*       g_pLocaleNameCached;   // 0x16510b8
extern wchar16_t*       g_pLocaleNameEnd;      // 0x16510bc
extern const wchar16_t* g_pLocaleNamesTable[]; // 0x1548fb8
extern const char       g_szEmbeddedVersion[]; // 0x1427914
extern LocT16           g_defaultLocale;       // 0x15490e4

// ---------------------------------------------------------------------------
// GetLocaleTraits output: a 0x11c0 object whose two interesting fixed strings sit
// at +0x1148 (country) and +0x1178 (language).
// ---------------------------------------------------------------------------
struct LocTraitsStr   // fixed_string<wchar_t,16,1> layout, no ctor
{
    wchar16_t* mpBegin;
    wchar16_t* mpEnd;
    wchar16_t* mpCapacity;
    void*      mAlloc;
    wchar16_t* mpPoolBegin;
    wchar16_t  mBuf[16];
};

struct LocTraits
{
    uint32_t     raw[0xca8 / 4];
    LocTraitsStr mCountry;   // +0xca8
    LocTraitsStr mLanguage;  // +0xce0
    uint32_t     tail[5];
};

// ---------------------------------------------------------------------------
// @ 0x008825f0
// ---------------------------------------------------------------------------
LocT16 __cdecl EA_Locale_CRTGetLocale()
{
    // Fast path: the locale name has already been cached.
    if (g_pLocaleNameCached != g_pLocaleNameEnd) {
        LocT16 conv;
        ConvertName(&conv, g_pLocaleNameCached);

        LocT16 tmp;
        tmp.clear();
        tmp.AppendElement(conv.mpBegin, conv.mpEnd);
        conv.ReleaseHeap();          // tmp's inline buffer is the source; release conv

        LocT16 out;
        out.AppendElement(tmp.mpBegin, tmp.mpEnd);
        tmp.ReleaseHeap();
        return out;
    }

    // Slow path: read the CRT locale.
    wchar16_t bufLang[128];
    wchar16_t bufCountry[128];
    wchar16_t bufField[128];
    wchar16_t bufWord[128];

    const char* szLocale = setlocale(0 /*LC_ALL*/, 0);
    if (szLocale != 0 && *szLocale != 0) {
        // Match the embedded version string, byte by byte.
        const char* pVers = g_szEmbeddedVersion;
        const char* p = szLocale;
        while (*p == *pVers && *p != 0) { ++p; ++pVers; }
        bool bVersion = (*p == 0) && (*pVers == 0);

        if (bVersion) {
            LocTraits traits;
            TraitsInit(&traits);
            GetLocaleTraits(&traits, &g_defaultLocale);
            if (traits.mCountry.mpBegin != traits.mCountry.mpEnd &&
                traits.mLanguage.mpBegin != traits.mLanguage.mpEnd) {
                LocT16 out;
                ConcatNames(&out, &traits.mCountry, &traits.mLanguage);
                TraitsFree(&traits, 0);
                return out;
            }
            LocT16 out(g_defaultLocale);   // copy of the default locale
            TraitsFree(&traits, 0);
            return out;
        }

        // Parse "lang_country.code" into bufLang / bufCountry.
        int nLang = 0;
        int nCountry = 0;
        bool bInLang = true;
        const char* q = szLocale;
        char c = *q;
        while (c != '.' && c != 0) {
            if (c == '_') {
                bufLang[nLang] = 0;
                nLang = 0;
                bInLang = false;
                ++q;
                bufCountry[nCountry] = (wchar16_t)(char)*q;
            } else if (bInLang) {
                bufLang[nLang] = (wchar16_t)(char)c;
            } else {
                bufCountry[nCountry] = (wchar16_t)(char)c;
            }
            c = q[1];
            ++q;
            if (bInLang) ++nLang; else ++nCountry;
        }
        bufCountry[nCountry] = 0;

        unsigned int iVar11 = FindLower(bufCountry, bufField, 0x80);
        int iVar7 = FindInCht(bufLang, bufField, 0x80);
        for (const wchar16_t** pp = g_pLocaleNamesTable; iVar11 < 0x80 && iVar7 < 0x80 && *pp != 0; ++pp) {
            if (SplitField(3, *pp, bufField, 0x80, L'^') <= 0)
                continue;
            int n = 0;
            if (SplitField(0, bufField, bufWord, 0x80, L'^') >= 0x80)
                continue;
            for (;;) {
                ++n;
                if (CompareW(bufWord, bufCountry)) {
                    if (SplitField(2, *pp, bufField, 0x80, L'^') >= 0x80)
                        break;
                    int m = 0;
                    if (SplitField(0, bufField, bufWord, 0x80, L'^') >= 0x80)
                        break;
                    for (;;) {
                        if (CompareW(bufWord, bufLang)) {
                            LocT16 tok;
                            tok = *(const LocT16*)*pp;
                            LocT16 out;
                            ConvertName(&out, tok.mpBegin);
                            tok.ReleaseHeap();
                            return out;
                        }
                        ++m;
                        if (SplitField(m, bufField, bufWord, 0x80, L'^') >= 0x80)
                            goto nextName;
                        ++n;
                        if (SplitField(n, bufField, bufWord, 0x80, L'^') < 0x80)
                            continue;
                        goto nextName;
                    }
                }
                if (SplitField(n, bufField, bufWord, 0x80, L'^') >= 0x80)
                    break;
            }
        nextName:;
        }
    }

    LocT16 out;
    out.AppendElement(g_defaultLocale.mpBegin, g_defaultLocale.mpEnd);
    return out;
}
