// T2K (Type 2000) Type 1 font engine: New_T1kernSubTable0Data (0x008b9400, 2438 B).
// Parses the AFM-style kerning section of a Type 1 font ("StartKernPairs" N, then N records of
// the forms "KP name1 name2 x y", "KPH <hex1> <hex2> x y", "KPX name1 name2 x", "KPY name1 name2 y")
// into a sorted table of (leftGlyph << 16 | rightGlyph, xValue) pairs.
//
// The record scanners are inlined string loops (skip a character class, copy a token, ATOI, glyph
// index lookup).  Reproduced faithfully including the original's quirks: the number-skip loops count
// with the pair index, the KPH first hex digit reads A-F / a-f from the other token buffer, KPY
// stores the glyph indices left over from the previous KPX record, and un-parsable hex digits keep
// the previous value.
//
// FindString (0x008b9390) is a static helper of the same translation unit that takes its start
// offset in eax; it is reproduced as a static function so cl picks its own convention.
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;

extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);                                      // 0x008d1260
extern "C" uint32 tsi_PSNameToAppleCode(uint8* name, uint16* code, uint16* a, uint16* b);           // 0x008b6f90
extern "C" void  FUN_008cfac0(void* pairs, int n);                                                  // 0x008cfac0

struct T1Class {
    tsiMemObject* mem;           // 0x00
    char   pad04[0x30 - 4];
    int16  numGlyphs;            // 0x30
    char   pad32[6];
    int16* adobeCodes;           // 0x38
};

struct KernPair {
    uint32 key;                  // left << 16 | right glyph index
    int16  value;
    int16  pad;
};

struct kernSubTable0Data {
    tsiMemObject* mem;           // 0x00
    uint16 numPairs;             // 0x04
    uint16 pad6;                 // 0x06
    uint16 pad8;                 // 0x08
    uint16 pad10;                // 0x0a
    KernPair* pairs;             // 0x0c
};

// ATOI (0x008b6a20 as an out-of-line copy): skip to the first digit or '-', then read decimal digits.
static int ATOI(const uint8* p)
{
    uint16 v = 0;
    uint8 sign;
    for (;;) {
        sign = *p;
        if (sign >= '0' && sign <= '9')
            break;
        if (sign == '-')
            break;
        ++p;
    }
    if (sign == '-')
        ++p;
    uint8 c = *p;
    while (c >= '0' && c <= '9') {
        v = (uint16)(v * 10 + c - '0');
        c = *++p;
    }
    int r = (int16)v;
    if (sign == '-')
        r = -r;
    return r;
}

// FindString (0x008b9390): offset of needle inside hay[start .. n), returns pointer past the match.
static uint8* FindString(uint8* hay, const char* needle, int n, int start)
{
    int len = 0;
    while (needle[len])
        ++len;
    for (int i = start; i < n; ++i) {
        if (hay[i] != (uint8)needle[0])
            continue;
        int k = 1;
        while (k < len) {
            if (hay[i + k] != (uint8)needle[k])
                break;
            ++k;
        }
        if (k >= len)
            return hay + i + k;
    }
    return 0;
}

static inline unsigned HexDigitValue(uint8 c, unsigned dflt)
{
    if ((uint8)(c - '0') <= 9)
        return (uint16)((int16)(char)c - 0x30);
    if ((uint8)(c - 'A') <= 5)
        return (uint16)((int16)(char)c - 0x37);
    if ((uint8)(c - 'a') <= 5)
        return (uint16)((int16)(char)c - 0x57);
    return dflt;
}

#define SKIP_CHAR(ch)  for (; *s == (ch) && n < limit; ++n) ++s;
#define COPY_TOKEN(buf, term)                \
    {                                        \
        uint8 c_ = *s;                       \
        int k_ = 0;                          \
        for (; c_ != (term) && k_ < 0x3f; ++k_) { \
            ++s;                             \
            (buf)[k_] = c_;                  \
            c_ = *s;                         \
        }                                    \
        (buf)[k_] = 0;                       \
    }
#define FIND_INDEX(out, tblp, count, val)            \
    {                                                \
        int ix_ = 0;                                 \
        for (; ix_ < (count); ++ix_)                 \
            if ((tblp)[ix_] == (int16)(val)) break;  \
        (out) = ix_;                                 \
    }
#define SKIP_TO_SPACE_COUNTING_PAIR()                                  \
    for (; *s != ' ' && (int)i < limit; ++i) ++s;
#define STORE_PAIR(hi, lo, val)                                       \
    {                                                                 \
        result->pairs[i].key = ((uint32)(uint16)(hi) << 16) | (uint16)(lo); \
        result->pairs[i].value = (val);                               \
    }

// @ 0x008b9400
kernSubTable0Data* New_T1kernSubTable0Data(T1Class* t, tsiMemObject* mem, uint8* p, int length)
{
    uint8 buf1[64];
    uint8 buf2[64];
    uint32 a4 = 0;         // current Apple/hex code (low 16 bits written by tsi_PSNameToAppleCode)
    uint32 v9c = 0;        // low hex digit
    uint32 v88 = 0;        // first glyph index (16 bit) of the current record
    uint32 a0 = 0;         // glyph code table, then the second glyph index
    int v8c;               // glyph count / scratch output of tsi_PSNameToAppleCode
    uint8 v98[4];          // scratch output of tsi_PSNameToAppleCode
    int a8;                // first glyph index
    int cnt;
    int n;
    int limit;
    uint8* s;
    uint8* cursor;
    bool found;
    uint16 i;
    int numPairsIn;

    kernSubTable0Data* result = (kernSubTable0Data*)tsi_AllocMem(mem, 0x10);
    uint8* end = p + length;
    result->mem = mem;
    result->numPairs = 0;
    result->pairs = 0;

    cursor = FindString(p, "StartKernPairs", length, 0);
    if (cursor != 0) {
        int count = (int16)ATOI(cursor);
        result->pad6 = 0;
        result->numPairs = (uint16)count;
        result->pad8 = 0;
        result->pad10 = 0;
        numPairsIn = count;
        result->pairs = (KernPair*)tsi_AllocMem(mem, (uint32)(uint16)count * 8);
        i = 0;
        if (0 < count) {
            do {
                if (cursor + 0x50 > end) {
                    limit = (int)(end - cursor);
                    if (limit <= 10)
                        break;
                } else {
                    limit = 0x50;
                }
                found = false;
                n = 0;

                // ---- "KP " name1 name2 x y ----------------------------------------------------
                s = FindString(cursor, "KP ", limit - 2, 0);
                if (s) {
                    found = true;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf1, ' ')
                    tsi_PSNameToAppleCode(buf1, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    cnt = t->numGlyphs;
                    a0 = (uint32)t->adobeCodes;
                    FIND_INDEX(a8, (int16*)a0, cnt, a4)
                    v88 = (uint16)a8;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf2, ' ')
                    tsi_PSNameToAppleCode(buf2, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    {
                        int ix;
                        FIND_INDEX(ix, (int16*)a0, cnt, a4)
                        a0 = (uint16)ix;
                    }
                    SKIP_CHAR(' ')
                    {
                        int16 value = (int16)ATOI(s);
                        SKIP_TO_SPACE_COUNTING_PAIR()
                        STORE_PAIR(a8, a0, value)
                    }
                    cursor = s;
                    if (s + 0x50 > end) {
                        limit = (int)(end - s);
                        if (limit <= 10)
                            break;
                    } else {
                        limit = 0x50;
                    }
                }

                // ---- "KPH" <hex> <hex> x y ----------------------------------------------------
                n = 0;
                s = FindString(cursor, "KPH", limit - 3, 0);
                if (s) {
                    unsigned hi, v1, v2;
                    int16* tbl;
                    found = true;
                    SKIP_CHAR(' ')
                    SKIP_CHAR('<')
                    COPY_TOKEN(buf1, '>')
                    hi = (uint8)(buf1[0] - '0') <= 9 ? (uint16)((int16)(char)buf1[0] - 0x30)
                       : (uint8)(buf1[0] - 'A') <= 5 ? (uint16)((int16)(char)buf2[0] - 0x37)
                       : (uint8)(buf1[0] - 'a') <= 5 ? (uint16)((int16)(char)buf2[0] - 0x57)
                       : a4;
                    v9c = HexDigitValue(buf1[1], v9c);
                    v1 = (uint16)(((v9c & 0xf) | (hi << 4)));
                    tbl = t->adobeCodes;
                    v8c = t->numGlyphs;
                    FIND_INDEX(a8, tbl, v8c, v1)
                    v88 = (uint16)a8;
                    SKIP_CHAR('>')
                    SKIP_CHAR(' ')
                    SKIP_CHAR('<')
                    COPY_TOKEN(buf2, '>')
                    hi = HexDigitValue(buf2[0], v1);
                    v9c = HexDigitValue(buf2[1], v9c);
                    v2 = (uint16)(((v9c & 0xf) | (hi << 4)));
                    a4 = v2;
                    {
                        int ix;
                        FIND_INDEX(ix, tbl, v8c, v2)
                        a0 = (uint16)ix;
                    }
                    SKIP_CHAR('>')
                    for (; *s == ' ' && (int)i < limit; ++i) ++s;
                    {
                        int16 value = (int16)ATOI(s);
                        SKIP_TO_SPACE_COUNTING_PAIR()
                        STORE_PAIR(a8, a0, value)
                    }
                    cursor = s;
                    if (s + 0x50 > end) {
                        limit = (int)(end - s);
                        if (limit <= 10)
                            break;
                    } else {
                        limit = 0x50;
                    }
                }

                // ---- "KPX" name1 name2 x ------------------------------------------------------
                n = 0;
                s = FindString(cursor, "KPX", limit - 3, 0);
                if (s) {
                    found = true;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf1, ' ')
                    tsi_PSNameToAppleCode(buf1, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    cnt = t->numGlyphs;
                    a0 = (uint32)t->adobeCodes;
                    FIND_INDEX(a8, (int16*)a0, cnt, a4)
                    v88 = (uint16)a8;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf2, ' ')
                    tsi_PSNameToAppleCode(buf2, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    {
                        int ix;
                        FIND_INDEX(ix, (int16*)a0, cnt, a4)
                        a0 = (uint16)ix;
                    }
                    SKIP_CHAR(' ')
                    {
                        int16 value = (int16)ATOI(s);
                        STORE_PAIR(a8, a0, value)
                    }
                    cursor = s;
                    if (s + 0x50 > end) {
                        limit = (int)(end - s);
                        if (limit <= 10)
                            break;
                    } else {
                        limit = 0x50;
                    }
                }

                // ---- "KPY" name1 name2 y (y ignored; glyph indices left over from the last KPX) --
                n = 0;
                s = FindString(cursor, "KPY", limit - 3, 0);
                if (s == 0) {
                    if (!found)
                        break;
                } else {
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf1, ' ')
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf2, ' ')
                    SKIP_CHAR(' ')
                    STORE_PAIR(v88, a0, 0)
                    cursor = s;
                    if (s + 0x50 > end && (int)(end - s) <= 10)
                        break;
                }
                ++i;
            } while ((int)i < numPairsIn);

            if (i == 0)
                return result;
            result->numPairs = i;
            FUN_008cfac0(result->pairs, i);
            return result;
        }
    }
    return result;
}
