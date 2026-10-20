// T2K / tsi font engine, slice s008b6400 (0x008b6400-0x008b71a0).
// sniffer.obj (0x008b6400-0x008b6870): font-format sniffers + the sniffer dispatcher.
// t1.obj (0x008b68c0-0x008b71a0): Type 1 charstring helpers (glyph extent scans, number parsing,
// eexec decryption, encoding-vector name lookup, Adobe-code mapping).
//
// The t1.obj helpers are translation-unit-local statics in the original and several of them use the
// compiler's register parameter convention (ATOFixed: string in eax + int on the stack; ATOI: string
// in ecx; TransformData: eax/ebx/edi + stack arg; DecryptData: string in esi + length on the stack;
// GetGlyphYMax/Min: object in eax; PSNameToCode/GetNthName: class in ebx).  Their call sites live in
// other slices of the same object, so those functions are behaviour-complete here, not byte-exact
// (see nonmatching.txt).
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;
struct InputStream;

extern "C" __declspec(dllimport) int __cdecl strncmp(const char*, const char*, unsigned int);
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)

// ---- callees (addresses in comments) ------------------------------------------------------------
extern "C" int   Seek_InputStream(InputStream*, int);                          // 0x008cc580
extern "C" int   PeekInt16(InputStream*, void*, int);                          // 0x008cc220
extern "C" tsiMemObject* tsi_NewMemhandler(void*);                             // 0x008d11f0
extern "C" void* tsi_AllocMem(tsiMemObject*, uint32);                          // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject*, void*);                         // 0x008d1440
extern "C" void  tsi_DeleteMemhandler(tsiMemObject*);                          // 0x008d1570
extern "C" void  tsi_EmergencyShutDown(tsiMemObject*);                         // 0x008d1210
extern "C" int   util_FixDiv(int, int);                                        // 0x008d16d0
extern "C" void* New_sfnt_OffsetTable(tsiMemObject*, InputStream*);            // 0x008cd860
extern "C" void  Delete_sfnt_OffsetTable(void*);                               // 0x008cd910
extern "C" void* GetTableDirEntry_sfntClass(void*, uint32);                    // 0x008cebe0
extern "C" int   setjmp3(void*, int);                                          // 0x011e0cac

// ---- font-format sniffers (sniffer.obj) ---------------------------------------------------------

// @ 0x008b6400
static int IsPFR(InputStream* s)
{
    char buf[10];
    int result;
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 10);
    if (buf[0] == 'P' && buf[1] == 'F' && buf[2] == 'R') {
        result = 1;
        Seek_InputStream(s, 0);
    } else {
        result = 0;
        Seek_InputStream(s, 0);
    }
    return result;
}

// @ 0x008b6460
static int IsOTF(InputStream* s)
{
    int ok = 0;
    int mh;
    char buf[10];
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 10);
    if (buf[0] == 0) {
        if ((buf[1] != 1 && buf[1] != 2) || buf[2] != 0 || buf[3] != 0)
            goto fail;
    } else if (buf[0] != 'O' || buf[1] != 'T' || buf[2] != 'T' || buf[3] != 'O') {
        goto fail;
    }
    Seek_InputStream(s, 0);
    {
        tsiMemObject* mem = tsi_NewMemhandler(&mh);
        void** table = (void**)tsi_AllocMem(mem, 0xf8);
        *table = New_sfnt_OffsetTable(mem, s);
        ok = GetTableDirEntry_sfntClass(table, 0x44534947) != 0;    // 'DSIG'
        if (!ok)
            ok = GetTableDirEntry_sfntClass(table, 0x43464620) != 0; // ' CFF'
        Delete_sfnt_OffsetTable(*table);
        tsi_DeAllocMem(mem, table);
        tsi_DeleteMemhandler(mem);
    }
    Seek_InputStream(s, 0);
    return ok;
fail:
    Seek_InputStream(s, 0);
    return ok;
}

// @ 0x008b6570
static int IsTT(InputStream* s)
{
    int mh;
    char buf[10];
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 10);
    int found = 0;
    if (buf[0] == 0) {
        if ((buf[1] != 1 && buf[1] != 2) || buf[2] != 0 || buf[3] != 0)
            goto fail;
    } else if (buf[0] == 'O') {
        if (buf[1] != 'T' || buf[2] != 'T' || buf[3] != 'O')
            goto fail;
    } else {
        goto check_true;
    }
    Seek_InputStream(s, 0);
    {
        tsiMemObject* mem = tsi_NewMemhandler(&mh);
        void** table = (void**)tsi_AllocMem(mem, 0xf8);
        *table = New_sfnt_OffsetTable(mem, s);
        found = GetTableDirEntry_sfntClass(table, 0x6c6f6361) != 0; // 'acol'
        if (!found)
            found = GetTableDirEntry_sfntClass(table, 0x736c6f63) != 0; // 'cols'
        if (!found)
            found = GetTableDirEntry_sfntClass(table, 0x45424454) != 0; // 'TDBE'
        if (!found)
            found = GetTableDirEntry_sfntClass(table, 0x626c6f63) != 0; // 'colb'
        Delete_sfnt_OffsetTable(*table);
        tsi_DeAllocMem(mem, table);
        tsi_DeleteMemhandler(mem);
        if (found)
            goto done;
    }
check_true:
    if (buf[0] == 't') {
        if (buf[1] == 't') {
            if (buf[2] == 'c' && buf[3] == 'f') {
                Seek_InputStream(s, 0);
                return 1;
            }
        } else if (buf[1] == 'r' && buf[2] == 'u' && buf[3] == 'e') {
            Seek_InputStream(s, 0);
            return 1;
        }
    }
fail:
    found = 0;
done:
    Seek_InputStream(s, 0);
    return found;
}

// @ 0x008b6710
static int IsT1(InputStream* s)
{
    char buf[16];
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 16);
    char i = 0;
    while (buf[i] != '%' && i < 13) {
        ++i;
    }
    if (buf[i] == '%' && buf[i + 1] == '!') {
        Seek_InputStream(s, 0);
        return 1;
    }
    Seek_InputStream(s, 0);
    return 0;
}

// @ 0x008b6780
static int IsCFF(InputStream* s)
{
    uint8 buf[0x96];
    int result = 1;
    Seek_InputStream(s, 0);
    PeekInt16(s, buf, 0x96);
    if (buf[0] != 1
        || buf[2] + 4 >= 0x96
        || buf[buf[2] + 4] == 0
        || (int)buf[buf[2] + 4] >= 0x92 - buf[2]
        || buf[buf[buf[2] + 4] + buf[2] + 4] != 0)
        result = 0;
    Seek_InputStream(s, 0);
    return result;
}

// @ 0x008b6800
int ff_FontTypeFromStream(InputStream* s)
{
    if (IsOTF(s))
        return 7;
    if (IsTT(s))
        return 2;
    if (IsPFR(s))
        return 3;
    if (IsCFF(s))
        return 0x16;
    if (IsT1(s))
        return 1;
    return -1;
}

// @ 0x008b6870
#pragma optimize("y", off)
extern "C" short FF_FontTypeFromStream(int hdr, int* out)
{
    int r = setjmp3((void*)(*(int*)(hdr + 0x22c) + 0x10), 0);
    *out = r;
    if (r == 0)
        return (short)ff_FontTypeFromStream((InputStream*)hdr);
    tsi_EmergencyShutDown(*(tsiMemObject**)(hdr + 0x22c));
    return (short)*out;
}
#pragma optimize("y", on)

// ---- Type 1 charstring helpers (t1.obj) ---------------------------------------------------------

// Glyph point view used by the extent scans: signed count at +0x38, int16 coordinate array at +0x48.
struct GlyphPoints {
    char   pad00[0x38];
    int16  count;                 // 0x38
    char   pad3a[0x48 - 0x3a];
    int16* pts;                   // 0x48
};

// @ 0x008b68c0
static int16 GetGlyphYMax(GlyphPoints* g)
{
    int16* p = g->pts;
    int n = g->count;
    int16 m = p[0];
    int i = 1;
    if (n > 1) {
        do {
            int16 v = p[i];
            if (m < v)
                m = v;
            ++i;
        } while (i < n);
    }
    return m;
}

// @ 0x008b68f0
static int16 GetGlyphYMin(GlyphPoints* g)
{
    int16* p = g->pts;
    int n = g->count;
    int16 m = p[0];
    int i = 1;
    if (n > 1) {
        do {
            int16 v = p[i];
            if (v < m)
                m = v;
            ++i;
        } while (i < n);
    }
    return m;
}

// Contour accumulator for FlipContourDirection: contour count at +0x36, start/end index arrays at
// +0x3c/+0x40, x/y coordinate arrays at +0x44/+0x48, on-curve flags at +0x4c.
struct ContourData {
    char   pad00[0x36];
    int16  numContours;           // 0x36
    char   pad38[0x3c - 0x38];
    int16* starts;                // 0x3c
    int16* ends;                  // 0x40
    int16* xPts;                  // 0x44
    int16* yPts;                  // 0x48
    uint8* flags;                 // 0x4c
};

// @ 0x008b6920
extern "C" void FlipContourDirection(ContourData* d)
{
    uint8* flags = d->flags;
    int16* xPts = d->xPts;
    int16* yPts = d->yPts;
    int c = 0;
    while (c < d->numContours) {
        int16 start = d->starts[c];
        int16 end = d->ends[c];
        int n = (int16)((end - start) / 2);
        int i = 0;
        while (i < n) {
            int16 lo = (int16)(start + 1 + i);
            int16 hi = (int16)(end - i);
            int16 sx = xPts[lo];
            int16 sy = yPts[lo];
            uint8 sf = flags[lo];
            xPts[lo] = xPts[hi];
            yPts[lo] = yPts[hi];
            flags[lo] = flags[hi];
            xPts[hi] = sx;
            yPts[hi] = sy;
            flags[hi] = sf;
            ++i;
        }
        ++c;
    }
}

// @ 0x008b6a20
static int16 ATOI(const uint8* p)
{
    uint16 v = 0;
    uint8 c;
    for (;;) {
        c = *p;
        if (c >= '0' && c <= '9')
            break;
        if (c == '-')
            break;
        ++p;
    }
    if (c == '-')
        ++p;
    uint8 d = *p;
    while (d >= '0' && d <= '9') {
        v = (uint16)(v * 10 + d - '0');
        d = *++p;
    }
    int r;
    if (c == '-')
        r = -(int16)v;
    else
        r = (int16)v;
    return r;
}

// @ 0x008b6a70
static int ATOFixed(const uint8* p, int exponent)
{
    int ipart = 0;
    uint8 c;
    for (;;) {
        c = *p;
        if (c >= '0' && c <= '9')
            break;
        if (c == '-')
            break;
        if (c == '.')
            break;
        ++p;
    }
    if (c == '-')
        ++p;
    uint8 d = *p;
    while (d >= '0' && d <= '9') {
        ipart = (d - '0') + ipart * 10;
        d = *++p;
    }
    int result = ipart << 16;
    if (*p == '.') {
        int frac = 0;
        int scale = 1;
        uint8 f = p[1];
        ++p;
        while (f >= '0' && f <= '9') {
            if (scale < 100000000) {
                scale *= 10;
                frac = (f - '0') + frac * 10;
            }
            f = p[1];
            ++p;
        }
        int e;
        if (*p == 'E' || *p == 'e')
            e = ATOI(p + 1);
        else
            e = 0;
        e += exponent;
        for (; e > 0; --e)
            frac *= 10;
        if (e < 0) {
            e = -e;
            do {
                scale *= 10;
                --e;
            } while (e != 0);
        }
        result += util_FixDiv(frac, scale);
    }
    if (c == '-')
        result = -result;
    return result;
}

// @ 0x008b6b50
extern "C" int16 backwardsATOI(const uint8* p)
{
    const uint8* q = p + 1;
    uint16 v = 0;
    while (*q == ' ')
        --q;
    while (*q >= '0' && *q <= '9')
        --q;
    ++q;
    while (*q >= '0' && *q <= '9') {
        v = (uint16)(v * 10 + (*q - '0'));
        ++q;
    }
    return (int16)v;
}

static inline int ff_ishex(uint8 c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (uint8)(c - 'a') < 6;
}

static inline uint8 ff_nib(uint8 c)
{
    return c <= '9' ? (uint8)(c - '0') : (c <= 'F' ? (uint8)(c - 0x37) : (uint8)(c - 0x57));
}

// @ 0x008b6bb0
static int DecryptData(uint8* data, int len)
{
    uint16 r = 0xd971;
    uint16 r2 = 0;
    int16 count = 0;
    int i;
    uint8 X = 0, Y = 0, Z = 0;

    if (!ff_ishex(data[0]) || !ff_ishex(data[1]) || !ff_ishex(data[2]) || !ff_ishex(data[3])) {
        if (len <= 0)
            return len;
        for (i = 0; i < len; ++i) {
            uint8 Xp = X, Yp = Y, Zp = Z;
            uint8 b = data[i];
            uint8 dec = (uint8)(r >> 8) ^ b;
            uint16 sum = (uint16)(b + r);
            X = Yp;
            Z = Xp;
            r = (uint16)(0x58bf - sum * (uint16)0x3193);
            if (count == 0) {
                Y = dec;
                data[i] = dec;
                if (Zp == ' ' && dec == ' ') {
                    if ((Xp == 'R' && Yp == 'D') || (Xp == '-' && Yp == '|')) {
                        count = (int16)backwardsATOI(data + i - 4);
                        r2 = 0x10ea;
                    }
                }
            } else {
                uint8 dec2 = (uint8)(r2 >> 8) ^ dec;
                --count;
                r2 = (uint16)(0x58bf - (uint16)(dec + r2) * (uint16)0x3193);
                Y = dec2;
                data[i] = dec2;
            }
        }
        return len;
    }

    {
        int out = 0;
        i = 0;
        while (i < len) {
            uint8 c1;
            do { c1 = data[i++]; } while (c1 == ' ' || c1 == '\n' || c1 == '\r' || c1 == '\t');
            uint8 c2;
            do { c2 = data[i++]; } while (c2 == ' ' || c2 == '\n' || c2 == '\r' || c2 == '\t');
            uint8 b = (uint8)((ff_nib(c1) << 4) | ff_nib(c2));
            uint8 Xp = X, Yp = Y, Zp = Z;
            uint8 dec = (uint8)(r >> 8) ^ b;
            uint16 sum = (uint16)(b + r);
            X = Yp;
            Z = Xp;
            r = (uint16)(0x58bf - sum * (uint16)0x3193);
            if (count == 0) {
                Y = dec;
                data[out] = dec;
                if (Zp == ' ' && dec == ' ') {
                    if ((Xp == 'R' && Yp == 'D') || (Xp == '-' && Yp == '|')) {
                        count = (int16)backwardsATOI(data + out - 4);
                        r2 = 0x10ea;
                    }
                }
            } else {
                uint8 dec2 = (uint8)(r2 >> 8) ^ dec;
                --count;
                r2 = (uint16)(0x58bf - (uint16)(dec + r2) * (uint16)0x3193);
                Y = dec2;
                data[out] = dec2;
            }
            ++out;
        }
        return i;
    }
}

// A "T1 blob": mem at +0, a byte base at +8, a search limit at +0xc, a working offset at +0x10 and
// (for the encoding-vector helpers) the current text position at +0x2c.
struct T1Blob {
    tsiMemObject* mem;            // 0x00
    int   f4;                     // 0x04
    int   base;                   // 0x08
    int   limit;                  // 0x0c
    int   off;                    // 0x10
    char  pad14[0x2c - 0x14];
    char* str;                    // 0x2c
};

// @ 0x008b6e90
extern "C" char* tsi_T1Find(T1Blob* blob, const char* needle, int start, int limit)
{
    char* p = (char*)needle;
    while (*p++)
        ;
    int len = (int)(p - (char*)needle) - 1;
    if (limit <= start)
        return 0;
    char* base = (char*)blob->base;
    do {
        char* hay = base + start;
        if (*needle == *hay) {
            int k = 1;
            if (len <= 1)
                return base + start + k;
            while (hay[k] == needle[k]) {
                ++k;
                if (len <= k)
                    return base + start + k;
            }
        }
        ++start;
        if (limit <= start)
            return 0;
    } while (1);
}

// @ 0x008b6f00
static int TransformData(T1Blob* ctx, uint8* base, int length, int which)
{
    ctx->f4 = (int)base;
    ctx->base = (int)base;
    ctx->limit = length;
    ctx->off = length;
    char* p = tsi_T1Find(ctx, "ntfile eexec", 0, length);
    if (p == 0) {
        if (base != 0) {
            tsi_DeAllocMem(ctx->mem, base);
            ctx->base = 0;
        }
        return 0xffff;
    }
    ctx->off = 0;
    while (*p == '\r' || *p == '\n')
        ++p;
    int skip = (int)p - (int)base;
    ctx->off = skip;
    if (which == 0x14 && skip > 0) {
        int n = DecryptData((uint8*)p, length - skip);
        ctx->limit = n + skip;
    }
    return 0;
}

// Adobe standard-encoding name table entry (0x14338c8, 16 bytes each): three int16 codes then a name.
struct PSNameEntry {
    int16       code0;            // 0x00
    int16       code2;            // 0x02
    int16       code4;            // 0x04
    char        pad06[6];
    const char* name;             // 0x0c
};
extern "C" PSNameEntry g_psNameTable[];   // 0x014338c8

// @ 0x008b6f90
extern "C" unsigned short tsi_PSNameToAppleCode(const char* name, int16* code, int16* code4, int16* index)
{
    uint16 r = 0xffff;
    *code = (int16)r;
    for (uint32 i = 0; i < 0x120; ++i) {
        if (strcmp(g_psNameTable[i].name, name) == 0) {
            *code = g_psNameTable[i].code2;
            *code4 = g_psNameTable[i].code4;
            *index = (int16)i;
            return g_psNameTable[i].code0;
        }
    }
    return 0xffff;
}

// @ 0x008b7030
extern "C" int16 PSNameToCodeFromEncodingVector(T1Blob* ctx, const char* name, int16* out)
{
    char* p = ctx->str;
    int count = ATOI((const uint8*)p);
    char* ro = tsi_T1Find(ctx, "readonly", (int)(p - (char*)ctx->base), ctx->limit);
    int len = 0;
    while (name[len])
        ++len;
    int i = 0;
    if (count > 0) {
        do {
            char* q = tsi_T1Find(ctx, "dup ", (int)(p - (char*)ctx->base),
                                 (int)(ro - (char*)ctx->base));
            if (q == 0)
                return -1;
            if (q >= ro)
                return -1;
            int16 code = ATOI((const uint8*)q);
            while (*q != '/')
                ++q;
            ++q;
            int n = 0;
            while ((uint8)q[n] >= '!')
                ++n;
            if (n == len && strncmp(q, name, len) == 0) {
                *out = (int16)i;
                return code;
            }
            p = q;
            ++i;
        } while (i < count);
    }
    return -1;
}

// @ 0x008b7130
static char* GetNthNameFromEncodingVector(T1Blob* ctx, int n)
{
    char* p = ctx->str;
    int count = ATOI((const uint8*)p);
    int i = 0;
    if (count > 0) {
        do {
            char* q = tsi_T1Find(ctx, "dup ", (int)(p - (char*)ctx->base), ctx->limit);
            if (q == 0)
                return 0;
            while (*q != '/')
                ++q;
            ++q;
            if (i == n)
                return q;
            p = q;
            ++i;
        } while (i < count);
    }
    return 0;
}

// @ 0x008b71a0
extern "C" int tsi_T1GetGlyphIndexFromAdobeCode(int* t, int16 code)
{
    int n = *(int16*)((char*)t + 0x30);
    int16* codes = *(int16**)((char*)t + 0x38);
    int i = 0;
    if (n > 0) {
        do {
            if (codes[i] == code)
                return i;
            ++i;
        } while (i < n);
    }
    return i;
}
