// T2K / tsi font engine, slice s008b81a0 (0x008b81a0-0x008b8f30).
// t1.obj (Type 1 charstring/dictionary engine): Adobe-code -> glyph-index lookup, per-glyph
// charstring build, dictionary array/fixed-array/name readers, font matrix + metrics extraction,
// advance-width query, subr table build, and the hash-class name comparison callback.
//
// Several of these are translation-unit-local statics that use the compiler's register parameter
// convention (GetT1FontMatrix: object in ebx; BuildMetricsEtc: object in eax; BuildSubrs: object in
// esi; tsi_T1GetArray / tsi_T1GetArray_2 / tsi_T1GetFixedArray: object in eax and name in edx, with
// the remaining arguments on the stack).  Their call sites live in other slices of the same object,
// so those functions are behaviour-complete here, not byte-exact (see nonmatching.txt).
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;

// strncmp must resolve through the import table (C linkage -> __imp__strncmp).
extern "C" __declspec(dllimport) int __cdecl strncmp(const char*, const char*, unsigned int);

// ---- callees (addresses in comments) ------------------------------------------------------------
extern "C" void* New_GlyphClass(tsiMemObject*, int, int, int, int);   // 0x008b0480
extern "C" void  glyph_CloseContour(void*);                           // 0x008afde0
extern "C" void  Delete_GlyphClass(void*);                            // 0x008b0280
extern "C" void  Type1BuildChar(void*, uint8*, int, int, void*, int); // 0x008b71c0
extern "C" int16 backwardsATOI(const uint8*);                         // 0x008b6b50
extern "C" int16 ATOI(const uint8*);                                  // 0x008b6a20
extern "C" int   ATOFixed(const uint8*, int);                         // 0x008b6a70
extern "C" char* tsi_T1Find(void*, const char*, int, int);            // 0x008b6e90
extern "C" void* tsi_AllocMem(tsiMemObject*, uint32);                 // 0x008d1260
extern "C" int16 GetGlyphYMax(void*);                                 // 0x008b68c0 (object in eax)
extern "C" int16 GetGlyphYMin(void*);                                 // 0x008b68f0 (object in eax)
extern "C" void  FlipContourDirection(void*);                         // 0x008b6920
extern "C" char* GetNthNameFromEncodingVector(void*, int);            // 0x008b7130 (object in ebx)
extern "C" int   get_using_uint16_hashClass(void*, int, void*);       // 0x008d1ac0

// ---- object layouts -----------------------------------------------------------------------------

// Glyph outline accumulator: point count at +0x38, x/y coordinate arrays at +0x44/+0x48.
struct GlyphBuilder {
    char   pad00[0x34];
    int16  f34;                  // 0x34
    int16  compFlag;             // 0x36
    int16  contour;              // 0x38
    char   pad3a[0x44 - 0x3a];
    int16* xPts;                 // 0x44
    int16* yPts;                 // 0x48
};

// Hash-class bucket entry: a 32-bit prefix then a 16-bit key and a 16-bit payload.
struct T1HashEntry {
    int32  pad;                  // 0x00
    int16  code;                 // 0x04
    int16  value;                // 0x06
};

// Hash class: bucket array at +0x24, element count at +0x2c.
struct T1Hash {
    char          pad00[0x24];
    T1HashEntry*  table;         // 0x24
    int32         pad28;         // 0x28
    int32         count;         // 0x2c
};

// Type 1 font class.  base/len/off/limit describe the in-memory font buffer; codes (+0x34) and
// adobeCodes (+0x38) are per-glyph 16-bit code tables; charStrings (+0x3c) is the per-glyph
// charstring pointer table; the metrics live from +0xcc.
struct T1Class {
    tsiMemObject* mem;           // 0x00
    int32   f04;                 // 0x04
    int32   base;                // 0x08
    int32   len;                 // 0x0c
    int32   off;                 // 0x10
    int32   limit;               // 0x14
    int32   curX;                // 0x18
    int32   curY;                // 0x1c
    int32   inFlex;              // 0x20
    int32   flexCount;           // 0x24
    int16   charBase;            // 0x28
    int16   pad2a;               // 0x2a
    char*   str;                 // 0x2c
    int16   numGlyphs;           // 0x30
    int16   pad32;               // 0x32
    int16*  codes;               // 0x34
    int16*  adobeCodes;          // 0x38
    void**  charStrings;         // 0x3c
    int16   numSubrs;            // 0x40
    int16   pad42;               // 0x42
    void**  subrs;               // 0x44
    int16   sp;                  // 0x48
    int16   pad4a;               // 0x4a
    int32   stack[0x20];         // 0x4c
    int32   numMasters;          // 0xcc
    int32   m_d0;                // 0xd0
    int32   weights[16];         // 0xd4
    int32   blueValues[14];      // 0x114
    int32   m_14c;               // 0x14c
    int32   m_150;               // 0x150
    int32   m_154;               // 0x154
    int32   m_158;               // 0x158
    int32   stemSnapH[12];       // 0x15c
    int32   m_18c;               // 0x18c
    int32   stemSnapV[12];       // 0x190
    int32   m_1c0;               // 0x1c0
    int32   m_1c4;               // 0x1c4
    int32   m_1c8;               // 0x1c8
    GlyphBuilder* glyph;         // 0x1cc
    int32   sbx;                 // 0x1d0
    int32   sby;                 // 0x1d4
    int32   wx;                  // 0x1d8
    int32   wy;                  // 0x1dc
    int32   m_1e0;               // 0x1e0
    int32   m_1e4;               // 0x1e4
    int32   m_1e8;               // 0x1e8
    int32   m_1ec;               // 0x1ec
    int32   m_1f0;               // 0x1f0
    int32   m_1f4;               // 0x1f4
    int32   m_1f8;               // 0x1f8
    int32   m_1fc;               // 0x1fc
    int32   m_200;               // 0x200
    int32   m_204;               // 0x204
    int32   m_208;               // 0x208
    int32   m_20c;               // 0x20c
    int32   m_210;               // 0x210
    int32   m_214;               // 0x214
    char    pad218[0x21c - 0x218];
    T1Hash* hashClass;           // 0x21c
    int32   found;               // 0x220
};

// Adobe standard-encoding name table (0x14338d4, 16 bytes per entry, name pointer first).
struct T1NameEntry {
    const char* name;            // 0x00
    char        pad04[12];
};
extern "C" T1NameEntry g_t1NameTable[];   // 0x014338d4

// ---- functions ----------------------------------------------------------------------------------

// @ 0x008b81a0
extern "C" int tsi_T1CodeToGlyphIndex(T1Class* t, int16 code)
{
    int16* codes = t->codes;
    int n = t->numGlyphs;
    int i = 0;
    if (n > 0) {
        do {
            if (codes[i] == code)
                break;
            ++i;
        } while (i < n);
    }
    t->found = (i < n);
    if (i < n)
        return i;

    T1Hash* h = t->hashClass;
    int cnt = h->count;
    i = 0;
    if (cnt != 0) {
        if (cnt > 0) {
            T1HashEntry* e = h->table;
            do {
                if (e->code == code)
                    break;
                ++i;
                e = (T1HashEntry*)((char*)e + 8);
            } while (i < h->count);
        }
        t->found = (i < cnt);
        if (i < cnt)
            return h->table[i].value;
    }
    return 0;
}

// @ 0x008b8230
extern "C" void* tsi_T1GetGlyphByIndex(T1Class* t, uint16 idx, int16* outX, int16* outW, int p5, int p6)
{
    int16 numGlyphs = t->numGlyphs;
    GlyphBuilder* g = (GlyphBuilder*)New_GlyphClass(t->mem, 0, 0, 0, 0);
    t->glyph = g;
    g->f34 = 3;
    t->sp = 0;
    if (idx < (uint16)numGlyphs) {
        void* cs = t->charStrings[idx];
        if (cs != 0) {
            int16 n = backwardsATOI((const uint8*)cs - 5);
            int16 cb = t->charBase;
            int len = (int)n - (int)cb;
            t->curX = 0;
            t->curY = 0;
            t->inFlex = 0;
            if (p5 == 0) {
                p5 = 0;
                p6 = 0;
            }
            Type1BuildChar(t, (uint8*)cs + cb, len, 0, (void*)p5, p6);
            glyph_CloseContour(t->glyph);
        }
    }
    g = t->glyph;
    int16* yPts = g->yPts;
    int16* xPts = g->xPts;
    int c = g->contour;
    yPts[c] = 0;
    xPts[c] = 0;
    yPts[c + 1] = (int16)t->wy;
    xPts[c + 1] = (int16)t->wx;
    *outX = (int16)t->wx;
    int x0 = xPts[c];
    int x1 = xPts[c + 1];
    int mid = (x0 + x1) >> 1;
    int maxY = (uint16)yPts[0];
    int i = 1;
    if (c > 1) {
        do {
            int16 v = yPts[i];
            if ((int16)maxY < v)
                maxY = (uint16)v;
            ++i;
        } while (i < c);
    }
    int16 em = (int16)t->m_1e0;
    yPts[c + 2] = (int16)(maxY + em / 10);
    xPts[c + 2] = (int16)mid;
    yPts[c + 3] = (int16)(yPts[c + 2] - em);
    xPts[c + 3] = (int16)mid;
    *outW = em;
    t->glyph = 0;
    FlipContourDirection(g);
    return g;
}

// @ 0x008b83d0
extern "C" int tsi_T1GetArray(T1Class* t, const char* name, int maxcount, int* out)
{
    char* s = tsi_T1Find(t, name, t->off, t->limit);
    if (s == 0)
        return 0;
    int i = 0;
    while (*s != '[' && i < 0x20) {
        ++s;
        ++i;
    }
    ++s;
    int n = 0;
    if (maxcount < 1)
        return 0;
    char c = *s;
    for (;;) {
        while (c == ' ' && i < 0x200) {
            ++s;
            ++i;
            c = *s;
        }
        if (*s == ']')
            return n;
        char* q = s;
        uint16 v = 0;
        char d = *q;
        while (d < '0' || d > '9') {
            if (d == '-')
                break;
            ++q;
            d = *q;
        }
        if (d == '-')
            ++q;
        char e = *q;
        while (e >= '0' && e <= '9') {
            v = (uint16)(v * 10 + e - '0');
            e = *++q;
        }
        int16 val = (int16)v;
        if (d == '-')
            val = (int16)-val;
        out[n] = val;
        ++n;
        c = *s;
        for (;;) {
            if (c == ' ')
                break;
            if (i >= 0x200)
                break;
            ++i;
            if (c == ']')
                break;
            c = s[1];
            ++s;
        }
        if (n >= maxcount)
            return n;
    }
}

// @ 0x008b84d0
extern "C" int tsi_T1GetArray_2(T1Class* t, const char* name, int maxcount, int* out)
{
    char* s = tsi_T1Find(t, name, t->off, t->limit);
    if (s == 0)
        return 0;
    int i = 0;
    char c = *s;
    while (c != '{' && c != '[' && i < 0x20) {
        c = s[1];
        ++s;
        ++i;
    }
    ++s;
    int n = 0;
    if (maxcount < 1)
        return 0;
    c = *s;
    for (;;) {
        while (c == ' ' && i < 0x200) {
            ++s;
            ++i;
            c = *s;
        }
        if (*s == '}' || *s == ']')
            return n;
        char* q = s;
        uint16 v = 0;
        char d = *q;
        while (d < '0' || d > '9') {
            if (d == '-')
                break;
            ++q;
            d = *q;
        }
        if (d == '-')
            ++q;
        char e = *q;
        while (e >= '0' && e <= '9') {
            v = (uint16)(v * 10 + e - '0');
            e = *++q;
        }
        int16 val = (int16)v;
        if (d == '-')
            val = (int16)-val;
        out[n] = val;
        ++n;
        c = *s;
        for (;;) {
            if (c == ' ')
                break;
            if (i >= 0x200)
                break;
            ++i;
            if (c == ']' || c == '}')
                break;
            c = s[1];
            ++s;
        }
        if (n >= maxcount)
            return n;
    }
}

// @ 0x008b85e0
extern "C" int tsi_T1GetFixedArray(T1Class* t, const char* name, int maxcount, int* out)
{
    char* s = tsi_T1Find(t, name, t->off, t->limit);
    if (s == 0)
        return 0;
    int i = 0;
    while (*s != '[' && i < 0x20) {
        ++s;
        ++i;
    }
    ++s;
    int n = 0;
    if (maxcount > 0) {
        char c = *s;
        for (;;) {
            while (c == ' ' && i < 0x200) {
                ++s;
                ++i;
                c = *s;
            }
            if (*s == ']')
                return n;
            out[n] = ATOFixed((const uint8*)s, 0);
            c = *s;
            ++n;
            while (c != ' ' && i < 0x200) {
                c = s[1];
                ++s;
                ++i;
            }
            if (n >= maxcount)
                return n;
        }
    }
    return n;
}

// @ 0x008b8680
extern "C" void GetT1FontMatrix(T1Class* t)
{
    t->m_204 = 0x10000;
    t->m_210 = 0x10000;
    t->m_208 = 0;
    t->m_20c = 0;
    int i = 0;
    char* s = tsi_T1Find(t, "/FontMatrix ", t->off, t->limit);
    if (s == 0)
        return;
    while (*s != '[' && i < 0x100) {
        ++s;
        ++i;
    }
    ++s;
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_204 = ATOFixed((const uint8*)s, 3);
    while (*s != ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_20c = ATOFixed((const uint8*)s, 3);
    while (*s != ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_208 = ATOFixed((const uint8*)s, 3);
    while (*s != ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_210 = ATOFixed((const uint8*)s, 3);
}

// @ 0x008b87e0
extern "C" char* GetT1NameProperty(T1Class* t, int unused, int16 kind)
{
    const char* name;
    if (kind == 3)
        name = "/FamilyName";
    else if (kind == 4)
        name = "/FullName";
    else
        return 0;
    char* s = tsi_T1Find(t, name, 0, t->limit);
    if (s == 0)
        return 0;
    if (*s != '(') {
        ++s;
        if (*s != '(') {
            ++s;
            if (*s != '(') {
                ++s;
                if (*s != '(')
                    return 0;
            }
        }
    }
    ++s;
    int n = 0;
    while (*s != ')' && n < 0x50) {
        ++n;
        if (s[n] == ')')
            break;
    }
    char* out = (char*)tsi_AllocMem(t->mem, n + 1);
    int k = 0;
    if (n > 0) {
        char* dst = out;
        char* src = s;
        k = n;
        do {
            *dst = *src;
            ++dst;
            --n;
        } while (n != 0);
    }
    out[k] = 0;
    return out;
}

// @ 0x008b8890
extern "C" void BuildMetricsEtc(T1Class* t)
{
    int bbox[4];
    int16 s;
    int v;
    char* p;

    t->m_d0 = 0;
    t->numMasters = tsi_T1GetFixedArray(t, "/WeightVector", 0x10, t->weights);
    t->m_14c = tsi_T1GetArray(t, "/BlueValues", 0xe, t->blueValues);

    s = 1;
    p = tsi_T1Find(t, "/BlueFuzz ", 0, t->limit);
    if (p != 0)
        s = ATOI((const uint8*)p);
    t->m_150 = s;

    v = 0xb35;
    p = tsi_T1Find(t, "/BlueScale ", 0, t->limit);
    if (p != 0)
        v = ATOFixed((const uint8*)p, 0);
    t->m_158 = v;

    s = 7;
    p = tsi_T1Find(t, "/BlueShift ", 0, t->limit);
    if (p != 0)
        s = ATOI((const uint8*)p);
    t->m_154 = s;

    t->m_18c = tsi_T1GetArray(t, "/StemSnapH", 0xc, t->stemSnapH);
    t->m_1c0 = tsi_T1GetArray(t, "/StemSnapV", 0xc, t->stemSnapV);

    s = 0;
    p = tsi_T1Find(t, "/StdHW ", 0, t->limit);
    if (p != 0)
        s = ATOI((const uint8*)p);
    t->m_1c4 = s;

    s = 0;
    p = tsi_T1Find(t, "/StdVW ", 0, t->limit);
    if (p != 0)
        s = ATOI((const uint8*)p);
    t->m_1c8 = s;

    v = 0x3e8;
    p = tsi_T1Find(t, "/em ", 0, t->limit);
    if (p != 0)
        v = ATOI((const uint8*)p);
    t->m_1e0 = v;
    t->m_1e4 = 0;

    v = 0x7fff;
    p = tsi_T1Find(t, "/ascent ", 0, t->limit);
    if (p != 0)
        v = ATOI((const uint8*)p);
    t->m_1e8 = v;

    v = -0x7fff;
    p = tsi_T1Find(t, "/descent ", 0, t->limit);
    if (p != 0)
        v = ATOI((const uint8*)p);
    t->m_1ec = -v;

    v = 0;
    p = tsi_T1Find(t, "/UnderlinePosition ", 0, t->limit);
    if (p != 0)
        v = ATOI((const uint8*)p);
    t->m_1fc = v;

    v = 0;
    p = tsi_T1Find(t, "/UnderlineThickness ", 0, t->limit);
    if (p != 0)
        v = ATOI((const uint8*)p);
    t->m_200 = v;

    GetT1FontMatrix(t);

    v = 0;
    p = tsi_T1Find(t, "/ItalicAngle ", 0, t->limit);
    if (p != 0)
        v = ATOFixed((const uint8*)p, 0);
    t->m_1f8 = v;

    v = 0;
    p = tsi_T1Find(t, "/isFixedPitch ", 0, t->limit);
    if (p != 0)
        v = (*p == 't');
    t->m_214 = v;

    if (t->m_1e8 == 0x7fff || t->m_1ec == 0x7fff) {
        if (tsi_T1GetArray_2(t, "/FontBBox", 4, bbox) == 4) {
            if (t->m_1e8 == 0x7fff)
                t->m_1e8 = bbox[3];
            if (t->m_1ec == 0x7fff)
                t->m_1ec = bbox[1];
        }
    }

    if (t->m_1e8 == 0x7fff) {
        int16 code = (int16)tsi_T1CodeToGlyphIndex(t, 0x66);
        if (code != 0) {
            int16 gx, gw;
            void* g = tsi_T1GetGlyphByIndex(t, (uint16)code, &gx, &gw, 0, -1);
            if (g != 0) {
                t->m_1e8 = GetGlyphYMax(g);
                Delete_GlyphClass(g);
            }
        }
    }

    if (t->m_1ec == 0x7fff) {
        int16 code = (int16)tsi_T1CodeToGlyphIndex(t, 0x67);
        if (code != 0) {
            int16 gx, gw;
            void* g = tsi_T1GetGlyphByIndex(t, (uint16)code, &gx, &gw, 0, -1);
            if (g != 0) {
                t->m_1ec = GetGlyphYMin(g);
                Delete_GlyphClass(g);
            }
        }
    }

    t->m_1f4 = t->m_1e0;
    t->m_1e4 = 0x20;
    if (t->m_1e8 == 0x7fff)
        t->m_1e8 = 0x2ee;
    if (t->m_1ec == 0x7fff)
        t->m_1ec = 0xffffff06;
    v = t->m_1e0 - t->m_1e8 + t->m_1ec;
    t->m_1f0 = v;
    if (v < 0)
        t->m_1f0 = 0;
}

// @ 0x008b8c80
extern "C" short FF_GetAW_T1Class(T1Class* t, int16 idx)
{
    int16 outX = 0;
    int16 outW;
    void* g = tsi_T1GetGlyphByIndex(t, (uint16)idx, &outX, &outW, 0, -1);
    short result = 0;
    if (g != 0) {
        result = outX;
        Delete_GlyphClass(g);
    }
    return result;
}

// @ 0x008b8cc0
extern "C" void BuildSubrs(T1Class* t)
{
    t->numSubrs = 0;
    t->subrs = 0;
    char* p = tsi_T1Find(t, "/Subrs ", t->off, t->len);
    if (p == 0)
        return;

    int16 n = ATOI((const uint8*)p);
    t->numSubrs = n;
    t->subrs = (void**)tsi_AllocMem(t->mem, (uint32)((int)n * 4));

    int i = 0;
    if (n > 0) {
        do {
            t->subrs[i] = 0;
            ++i;
        } while (i < t->numSubrs);
    }
    if (t->numSubrs <= 0)
        return;

    int count = 0;
    char* cur = p;
    do {
        char* base = (char*)t->base;
        char* q = tsi_T1Find(t, "dup ", (int)(cur - base), t->len);
        uint16 v = 0;
        char b = *q;
        while (b < '0' || b > '9') {
            if (b == '-')
                break;
            ++q;
            b = *q;
        }
        if (b == '-')
            ++q;
        char c = *q;
        while (c >= '0' && c <= '9') {
            v = (uint16)(v * 10 + c - '0');
            c = *++q;
        }
        int16 idx = (int16)v;
        if (b == '-')
            idx = (int16)-idx;

        int off = (int)(cur - base);
        char* r = tsi_T1Find(t, "RD ", off, off + 0x10);
        if (r == 0)
            r = tsi_T1Find(t, "-| ", off, off + 0x10);
        int16 len = backwardsATOI((const uint8*)r - 5);
        t->subrs[idx] = r;
        ++count;
        cur = r + len;
    } while (count < t->numSubrs);
}

// @ 0x008b8e20
extern "C" int T1stringsAreEqual(T1Class* t, const char* name, int16 code)
{
    uint8 len = 0;
    if ((uint16)code == 0xfffe)
        return 0;

    char* candidate = 0;
    char first = *t->str;
    if (first >= '0' && first <= '9') {
        if ((int)(uint16)code < (int)ATOI((const uint8*)t->str)) {
            candidate = GetNthNameFromEncodingVector(t, (uint16)code);
            if (candidate != 0) {
                if (candidate[0] >= 0x21) {
                    len = 0;
                    do {
                        ++len;
                    } while ((uint8)candidate[len] >= 0x21);
                }
                goto compare;
            }
        }
    } else if ((uint16)code < 0x120) {
        candidate = (char*)g_t1NameTable[code].name;
        if (candidate != 0) {
            const char* q = candidate + 1;
            const char* r = candidate;
            do {
                ++r;
            } while (*r != 0);
            len = (uint8)(r - q);
            goto compare;
        }
    }

    if (t->hashClass->table != 0) {
        int out;
        return get_using_uint16_hashClass(t->hashClass, code, &out);
    }

compare:
    {
        int nl = 0;
        while (name[nl] != 0)
            ++nl;
        if (nl == (int)len && strncmp(name, candidate, len) == 0)
            return 1;
    }
    return 0;
}
